//
// Created by kisly on 13.07.2025.
//

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>

namespace core
{
    /// @brief класс для считывания изображений, форматы:
    /// @brief JPEG, PNG, TGA, BMP, PSD, GIF (не анимация), HDR, PIC, PNM
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
        static unsigned char* load(
                const char* path,
                int& width,
                int &height,
                int& channels,
                bool rotateImg = true,
                bool info = true
        );
        
        static Image load(const char* path, bool rotateImg = true, bool info = true);
        static Image *ptrLoad(const char* path, bool rotateImg = true, bool info = true);

        static void free(unsigned char* imgCode);
        static void free(Image& img);

        ~Image();

        [[nodiscard]] int getWidth() const;
        [[nodiscard]] int getHeight() const;
        [[nodiscard]] int getChannels() const;
        [[nodiscard]] const char* getPath();
        [[nodiscard]] unsigned char* getImageCode();
        [[nodiscard]] std::vector<unsigned char> getVectorImageCode();
    };
}

#endif //IMAGE_HPP
