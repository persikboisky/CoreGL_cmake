//
// Created by kisly on 13.07.2025.
//

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>

namespace core
{
    /// @brief класс для считывания изображений, форматы:
    /// @brief JPEG, PNG, TGA, BMP, PSD, GIF (без анимации), HDR, PIC, PNM
    class Image
    {
    private:
        int width;
        int height;
        int channels;
        unsigned char* ptrImageCode;

        const char* path;

        Image(const char* path, bool rotateImg, bool info);

    public:
        /// @brief загружает изображение
        /// @param path путь к изображению
        /// @param width переменная для записи ширины изображения
        /// @param height переменная для записи высоты изображения
        /// @param channels переменная для записи кол-ва цветовых каналов
        /// @param rotateImg нужно ли повернуть изображение на 180 градусов
        /// @param info разрешение на вывод debug информации
        /// @return указатель на массив, содержащий цвета пикселей
        static unsigned char* load(
                const char* path,
                int& width,
                int &height,
                int& channels,
                bool rotateImg = true,
                bool info = true
        );
        
        /// @brief загружает изображение
        /// @param path путь к изображению
        /// @param rotateImg нужно ли повернуть изображение на 180 градусов
        /// @param info разрешение на вывод debug информации
        /// @return объект класса Image
        static Image load(const char* path, bool rotateImg = true, bool info = true);

        /// @brief загружает изображение
        /// @param path путь к изображению
        /// @param rotateImg нужно ли повернуть изображение на 180 градусов
        /// @param info разрешение на вывод debug информации
        /// @return указатель на объект класса Image
        static Image *ptrLoad(const char* path, bool rotateImg = true, bool info = true);

        /// @brief удаляет изображение
        /// @param imgCode указатель на массив, содержащий цвета пикселей
        static void free(unsigned char* imgCode);

        /// @brief удаляет изображение
        /// @param img ссылка на объект класса Image
        static void free(Image& img);

        ~Image();

        /// @brief получает ширину изображения
        /// @return ширина
        [[nodiscard]] int getWidth() const;

        /// @brief получает высоту изображения
        /// @return высота
        [[nodiscard]] int getHeight() const;

        /// @brief получает кол-во цветовых каналов
        /// @return кол-во цветовых каналов
        [[nodiscard]] int getChannels() const;

        /// @brief путь к файлу изображения
        /// @return си-строку, путь к файлу
        [[nodiscard]] const char* getPath();

        /// @brief получает указатель на массив, содержащий цвета пикселей
        /// @return указатель на массив
        [[nodiscard]] unsigned char* getImageCode();

        /// @brief получает вектор, содержащий цвета пикселей
        /// @return вектор
        [[nodiscard]] std::vector<unsigned char> getVectorImageCode();

        size_t getSize() const;
    };
}

#endif //IMAGE_HPP
