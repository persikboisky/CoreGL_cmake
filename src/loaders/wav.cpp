//
// Created by kisly on 17.07.2025.
//

#include "wav.hpp"
#include "../config.hpp"
#include "../util/Coders.hpp"
#include "../util/console.hpp"
#include "../util/vector.hpp"
#include <fstream>
#include <iostream>
#include <vector>

static std::vector<char> readWav(const char* path, core::wavInfo& info)
{
    std::ifstream file = std::ifstream(path, std::ios::binary);
    if (!file.is_open())
    {
        throw core::Coders(27, path);
    }

    char *containerFor4byte = new char[4];
    char *containerFor2byte = new char[2];

    // проверка имени чанка RIFF
    file.read(containerFor4byte, 4);
    if (
        containerFor4byte[0] != 'R' ||
        containerFor4byte[1] != 'I' ||
        containerFor4byte[2] != 'F' ||
        containerFor4byte[3] != 'F'
    ) throw core::Coders(28, path);

    // ChunkSize
    file.read(containerFor4byte, 4);

    // проверка формата wave
    file.read(containerFor4byte, 4);
    if (
        containerFor4byte[0] != 'W' ||
        containerFor4byte[1] != 'A' ||
        containerFor4byte[2] != 'V' ||
        containerFor4byte[3] != 'E'
    ) throw core::Coders(29, path);

    // subChunkId
    file.read(containerFor4byte, 4);
    if (
        containerFor4byte[0] != 'f' ||
        containerFor4byte[1] != 'm' ||
        containerFor4byte[2] != 't'
    ) throw core::Coders(30, path);

    // subChunkSize
    file.read(containerFor4byte, 4);

    // audioFormat
    file.read(containerFor2byte, 2);

    // numChannels;
    file.read((char*)&info.channels, 2);

    // sampleRate
    file.read((char*)&info.sampleRate, 4);

    // byteRate
    file.read((char*)&info.byteRate, 4);

    // blockAlign
    file.read((char*)&info.blockAlign, 2);

    // bitsPerSample
    file.read((char*)&info.bitsPerSample, 2);

    // data
    int i = 0;
    const char keyWord[4] = {'d', 'a', 't', 'a'};
    char *byte = new char[1];

    while (true)
    {
        try
        {
            // почему это работает, хм?
            if (i == 4) break;
            else if (
                file.read(byte, 1);     
                byte[0] == keyWord[0] ||
                byte[0] == keyWord[1] ||
                byte[0] == keyWord[2] ||
                byte[0] == keyWord[3]
            ) i++;
            else i = 0;
        }
        catch (...)
        {
            throw core::Coders(31);
        }
    }

    int dataSizeForByte;
    file.read((char*)& dataSizeForByte, 4);

    char* containerForDataChunk = new char[dataSizeForByte];
//    int savePer = -1;
//    for (int index = 0; index < dataSizeForByte; index++)
//    {
//        int per = int(float(index) / float(dataSizeForByte) * 100.0);
//        if(savePer != per)
//        {
//            core::console::printProgressBar(40, per);
//            savePer = per;
//            int x, y;
//            core::console::getPosCursor(x, y);
//            core::console::setPosCursor(0, y);
//        }
//
//
//        file.read((char*)&containerForDataChunk[index], 1);
//    }

    file.read(containerForDataChunk, dataSizeForByte);
    std::vector<char> data = core::vector::arrayToVector_char(containerForDataChunk, dataSizeForByte);

    delete[] byte;
    delete[] containerForDataChunk;
    delete[] containerFor4byte;
    delete[] containerFor2byte;
    file.close();

    if (CORE_INFO)
    {
        core::console::printTime();
        std::cout << "Ok: load " << path << std::endl;
        core::console::printTime();
        std::cout << "channels: " << info.channels << std::endl;
        core::console::printTime();
        std::cout << "data size: " << dataSizeForByte << " Bytes" << std::endl;
        core::console::printTime();
        std::cout << "sampling rate: " << info.sampleRate << "Hz" << std::endl;
        core::console::printTime();
        std::cout << "bits: " << info.blockAlign * 8 << std::endl;
    }

    return data;
}

namespace core
{

    wav::wav(const char *path)
    {
        this->info.path = path;
        this->info.data = readWav(path, this->info);
    }

    wav::~wav()
    {
    }

    std::vector<char> wav::read(const char *path, wavInfo& info)
    {
        return readWav(path, info);
    }

    wav wav::load(const char *path)
    {
        return wav(path);
    }

    wav *wav::ptrLoad(const char *path)
    {
        return new wav(path);
    }

    wavInfo wav::getInfo()
    {
        return this->info;
    }

    short wav::getChannels()
    {
        return this->info.channels;
    }

    short wav::getBitsPerSample()
    {
        return this->info.bitsPerSample;
    }

    std::vector<char> wav::getData()
    {
        return this->info.data;
    }

    int wav::getSampleRate()
    {
        return this->info.sampleRate;
    }

} // core

