//
// Created by kisly on 14.07.2025.
//

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>

namespace core
{
    enum TYPE_WRAPPING_TEXTURE : int;
    class image;

    struct texture
    {
    private:
        [[maybe_unused]] static std::vector<unsigned int> id;

    public:
        static void bind(unsigned int id, unsigned int Sample = 0);

        static unsigned int load(unsigned char* png_code, int width, int height, int channels, bool info = true);
        static unsigned int load(std::vector<unsigned char>& png_code, int width, int height, int channels, bool info = true);
        static unsigned int load(const char* path, bool info = true);
        static unsigned int load(image& img, bool info = true);

        static void setTypeWrapping(unsigned int textID, const TYPE_WRAPPING_TEXTURE& twt);

        static void Delete(unsigned int id);
        static void DeleteALL();
    };

    class Texture : private texture
    {
    private:
        unsigned int id;

        Texture(unsigned char* png_code, int width, int height, int channels);
        Texture(std::vector<unsigned char>& png_code, int width, int height, int channels);
        Texture(const char* path);
        Texture(image& img);
        Texture(unsigned int id);

    public:
        static Texture create(unsigned char* png_code, int width, int height, int channels);
        static Texture create(std::vector<unsigned char>& png_code, int width, int height, int channels);
        static Texture create(image& img);
        static Texture add(unsigned int id);

        static Texture *ptrCreate(unsigned char* png_code, int width, int height, int channels);

        static Texture load(const char* path);

        ~Texture();

        void bind(unsigned int Sample = 0) const;

        void setTypeWrapping(unsigned int textID, const TYPE_WRAPPING_TEXTURE& twt);

        unsigned int getID() const;
    };
}

#endif //TEXTURE_HPP
