//
// Created by kisly on 25.08.2025.
//

#include "ttf.hpp"
#include "../util/coders.hpp"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include <cstring>

#pragma region little-endian
//////////////////////////////////////////////////////////////////////////////////////
//      функции для чтения байтов в обратном порядке для little-endian системы      //
//////////////////////////////////////////////////////////////////////////////////////
static uint16_t readU16BE(std::ifstream& file) {                                    //
    uint8_t bytes[2];                                                               //
    file.read(reinterpret_cast<char*>(bytes), 2);                             //
    return (bytes[0] << 8) | bytes[1];                                              //
}                                                                                   //
                                                                                    //
static int16_t readI16BE(std::ifstream& file) {                                     //
    uint16_t value = readU16BE(file);                                            //
    return static_cast<int16_t>(value);                                             //
}                                                                                   //
                                                                                    //
static uint32_t readU32BE(std::ifstream& file) {                                    //
    uint8_t bytes[4];                                                               //
    file.read(reinterpret_cast<char*>(bytes), 4);                             //
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];        //
}                                                                                   //
                                                                                    //
static uint64_t readU64BE(std::ifstream& file) {                                    //
    uint8_t bytes[8];                                                               //
    file.read(reinterpret_cast<char*>(bytes), 8);                             //
    return (static_cast<uint64_t>(bytes[0]) << 56) |                                //
           (static_cast<uint64_t>(bytes[1]) << 48) |                                //
           (static_cast<uint64_t>(bytes[2]) << 40) |                                //
           (static_cast<uint64_t>(bytes[3]) << 32) |                                //
           (static_cast<uint64_t>(bytes[4]) << 24) |                                //
           (static_cast<uint64_t>(bytes[5]) << 16) |                                //
           (static_cast<uint64_t>(bytes[6]) << 8) |                                 //
           static_cast<uint64_t>(bytes[7]);                                         //
}                                                                                   //
//////////////////////////////////////////////////////////////////////////////////////
#pragma endregion

struct TableDirectoryEntry {
    char tag[4] = { 0, 0, 0, 0 };       // 4-байтовый идентификатор
    uint32_t checksum = 0;				                // контрольная сумма
    uint32_t offset = 0;				                // смещение от начала файла
    uint32_t length = 0;				                // длина таблицы
};

enum HeadFlags : int {
    BASELINE_AT_Y_0    = 0x0001, // Базовая линия на y=0
    LEFT_SIDEBEARING_AT_X_0 = 0x0002, // Левый sidebearing на x=0
    INSTRUCTIONS_DEPEND_ON_POINT_SIZE = 0x0004,
    FORCE_PPEM_TO_INTEGER = 0x0008,
    INSTRUCTIONS_MAY_ALTER_ADVANCE_WIDTH = 0x0010,
};

struct headTable
{
    uint32_t version;
    uint32_t fontRevision;
    uint32_t checkSumAdjustment;
    uint32_t magicNumber;
    HeadFlags flags;
    uint16_t unitsPerEm;
    uint64_t created;
    uint64_t modified;
    int16_t xMin;
    int16_t yMin;
    int16_t xMax;
    int16_t yMax;
    uint16_t macStyle;
    uint16_t lowestRecPPEM;
    int16_t fontDirectionHint;
    int16_t indexToLocFormat;
    int16_t glyphDataFormat;
};

namespace core
{
	TTF::TTF(const char* path)
	{
#pragma region var
        // Главный заголовок шрифта
		auto* head = new TableDirectoryEntry();

        // Таблица соответствия символов глифам
        auto* cmap = new TableDirectoryEntry();

        // Горизонтальный заголовок метрик
        auto* hhea = new TableDirectoryEntry();

        // Горизонтальные метрики глифов
        auto* hmtx = new TableDirectoryEntry();

        // Максимальные требования шрифта
        auto* maxp = new TableDirectoryEntry();

        // Таблица с именами шрифта
        auto* name = new TableDirectoryEntry();

        // Метрики для Windows
        auto* OS2 = new TableDirectoryEntry();

        // PostScript-информация
        auto* post = new TableDirectoryEntry();

        // Данные глифов (для TrueType)
        auto* glyf = new TableDirectoryEntry();

        // Индекс расположения глифов
        auto* loca = new TableDirectoryEntry();

        auto* containerFor4Bytes = new char[4];
        auto* containerFor2Bytes = new char[2];
        auto* flagsForTags = new bool[10]{
            false,                          // tag - head
            false,                          // tag - cmap
            false,                          // tag - hhea
            false,                          // tag - hmtx
            false,                          // tag - maxp
            false,                          // tag - name
            false,                          // tag - os/2
            false,                          // tag - post
            false,                          // tag - glyf
            false                           // tag - loca
        };
#pragma endregion
#pragma region openFile
		std::ifstream file = std::ifstream(path, std::ios::binary);
		if (!file.is_open()) throw coders(6, path);

		// получаем размер файла
		file.seekg(0, std::ios::end);
		std::streamsize fileSize = file.tellg();

		file.seekg(0, std::ios::beg);

        // проверяем является ли файл ttf-ом
        file.read(containerFor4Bytes, 4);
        if (
                containerFor4Bytes[0] != 0 ||
                containerFor4Bytes[1] != 1 ||
                containerFor4Bytes[2] != 0 ||
                containerFor4Bytes[3] != 0) throw coders(44, path);
#pragma endregion
#pragma region readTags
        size_t index = 0;
        for (; index < fileSize; index++)
        {
            file.read(containerFor4Bytes, 4);

            // считываем тег head
            if (
                    containerFor4Bytes[0] == 'h' &&
                    containerFor4Bytes[1] == 'e' &&
                    containerFor4Bytes[2] == 'a' &&
                    containerFor4Bytes[3] == 'd')
            {
                std::memcpy(head->tag, containerFor4Bytes, 4);
                flagsForTags[0] = true;

                head->checksum = readU32BE(file);
                head->offset = readU32BE(file);
                head->length = readU32BE(file);
            }
            else if (
                    containerFor4Bytes[0] == 'c' &&
                    containerFor4Bytes[1] == 'm' &&
                    containerFor4Bytes[2] == 'a' &&
                    containerFor4Bytes[3] == 'p')
            {
                std::memcpy(cmap->tag, containerFor4Bytes, 4);
                flagsForTags[1] = true;

                cmap->checksum = readU32BE(file);
                cmap->offset = readU32BE(file);
                cmap->length = readU32BE(file);
            }
            else if (
                    containerFor4Bytes[0] == 'h' &&
                    containerFor4Bytes[1] == 'h' &&
                    containerFor4Bytes[2] == 'e' &&
                    containerFor4Bytes[3] == 'a')
            {
                std::memcpy(hhea->tag, containerFor4Bytes, 4);
                flagsForTags[2] = true;

                hhea->checksum = readU32BE(file);
                hhea->offset = readU32BE(file);
                hhea->length = readU32BE(file);
            }
            else if (
                    containerFor4Bytes[0] == 'h' &&
                    containerFor4Bytes[1] == 'm' &&
                    containerFor4Bytes[2] == 't' &&
                    containerFor4Bytes[3] == 'x')
            {
                std::memcpy(hmtx->tag, containerFor4Bytes, 4);
                flagsForTags[3] = true;

                hmtx->checksum = readU32BE(file);
                hmtx->offset = readU32BE(file);
                hmtx->length = readU32BE(file);
            }
            else if (
                    containerFor4Bytes[0] == 'm' &&
                    containerFor4Bytes[1] == 'a' &&
                    containerFor4Bytes[2] == 'x' &&
                    containerFor4Bytes[3] == 'p')
            {
                std::memcpy(maxp->tag, containerFor4Bytes, 4);
                flagsForTags[4] = true;

                maxp->checksum = readU32BE(file);
                maxp->offset = readU32BE(file);
                maxp->length = readU32BE(file);
            }
            else if (
                    containerFor4Bytes[0] == 'n' &&
                    containerFor4Bytes[1] == 'a' &&
                    containerFor4Bytes[2] == 'm' &&
                    containerFor4Bytes[3] == 'e')
            {
                std::memcpy(name->tag, containerFor4Bytes, 4);
                flagsForTags[5] = true;

                name->checksum = readU32BE(file);
                name->offset = readU32BE(file);
                name->length = readU32BE(file);
            }
            else if (
                    containerFor4Bytes[0] == 'O' &&
                    containerFor4Bytes[1] == 'S' &&
                    containerFor4Bytes[2] == '/' &&
                    containerFor4Bytes[3] == '2')
            {
                std::memcpy(OS2->tag, containerFor4Bytes, 4);
                flagsForTags[6] = true;

                OS2->checksum = readU32BE(file);
                OS2->offset = readU32BE(file);
                OS2->length = readU32BE(file);
            }
            else if (
                    containerFor4Bytes[0] == 'p' &&
                    containerFor4Bytes[1] == 'o' &&
                    containerFor4Bytes[2] == 's' &&
                    containerFor4Bytes[3] == 't')
            {
                std::memcpy(post->tag, containerFor4Bytes, 4);
                flagsForTags[7] = true;

                post->checksum = readU32BE(file);
                post->offset = readU32BE(file);
                post->length = readU32BE(file);
            }
            else if (
                    containerFor4Bytes[0] == 'g' &&
                    containerFor4Bytes[1] == 'l' &&
                    containerFor4Bytes[2] == 'y' &&
                    containerFor4Bytes[3] == 'f')
            {
                std::memcpy(glyf->tag, containerFor4Bytes, 4);
                flagsForTags[8] = true;

                glyf->checksum = readU32BE(file);
                glyf->offset = readU32BE(file);
                glyf->length = readU32BE(file);
            }
            else if (
                    containerFor4Bytes[0] == 'l' &&
                    containerFor4Bytes[1] == 'o' &&
                    containerFor4Bytes[2] == 'c' &&
                    containerFor4Bytes[3] == 'a')
            {
                std::memcpy(loca->tag, containerFor4Bytes, 4);
                flagsForTags[9] = true;

                loca->checksum = readU32BE(file);
                loca->offset = readU32BE(file);
                loca->length = readU32BE(file);
            }


            if (
                    flagsForTags[0] && flagsForTags[1] && flagsForTags[2] && flagsForTags[3] &&
                    flagsForTags[4] && flagsForTags[5] && flagsForTags[6] && flagsForTags[7] &&
                    flagsForTags[8] && flagsForTags[9]) break;
        }
        delete[] flagsForTags;

        if (index == fileSize)
        {
            throw coders(43, path);
        }
#pragma endregion

        std::cout << "head: " << head->offset << std::endl;
        std::cout << "cmap: " << cmap->offset << std::endl;
        std::cout << "hhea: " << hhea->offset << std::endl;
        std::cout << "hmtx: " << hmtx->offset << std::endl;
        std::cout << "maxp: " << maxp->offset << std::endl;
        std::cout << "name: " << name->offset << std::endl;
        std::cout << "OS/2: " << OS2->offset << std::endl;
        std::cout << "post: " << post->offset << std::endl;
        std::cout << "glyf: " << glyf->offset << std::endl;
        std::cout << "loca: " << loca->offset << std::endl;

#pragma region readTableHead
        /////////////////////////////////////////////////////////////////////////////////////////
        // читаем таблицу head

        auto* objHeadTable = new headTable();

        file.seekg(head->offset, std::ios::beg);
        objHeadTable->version = readU32BE(file);
        objHeadTable->fontRevision = readU32BE(file);
        objHeadTable->checkSumAdjustment = readU32BE(file);
        objHeadTable->magicNumber = readU32BE(file);
        objHeadTable->flags = HeadFlags(readU16BE(file));
        objHeadTable->unitsPerEm = readU16BE(file);
        objHeadTable->created = readU64BE(file);
        objHeadTable->modified = readU64BE(file);
        objHeadTable->xMin = readI16BE(file);
        objHeadTable->yMin = readI16BE(file);
        objHeadTable->xMax = readI16BE(file);
        objHeadTable->yMax = readI16BE(file);
        objHeadTable->macStyle = readU16BE(file);
        objHeadTable->lowestRecPPEM = readU16BE(file);
        objHeadTable->fontDirectionHint = readI16BE(file);
        objHeadTable->indexToLocFormat = readI16BE(file);
        objHeadTable->glyphDataFormat = readI16BE(file);

        delete head;

#pragma endregion

        delete objHeadTable;

        // очистка ресурсов
        delete cmap;
        delete hhea;
        delete hmtx;
        delete maxp;
        delete name;
        delete OS2;
        delete post;
        delete glyf;
        delete loca;
        delete[] containerFor4Bytes;
        delete[] containerFor2Bytes;
        file.close();
	}

	TTF TTF::load(const char* path)
	{
		return TTF(path);
	}

	TTF* TTF::ptrLoad(const char* path)
	{
		return new TTF(path);
	}

	TTF::~TTF()
	{
	}
}