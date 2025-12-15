//
// Created by kisly on 15.12.2025.
//

#include "ttf.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../config.hpp"
#include "../util/Coders.hpp"
#include "../util/console.hpp"
#include <iostream>

#define TTF_LOAD_INFO false

namespace core
{
    TTF::TTF(const char *path, bool flagDebuginfo)
    {
        FT_Init_FreeType(&ft);
        if (FT_New_Face(ft, path, 0, &face) != 0)
        {
            throw Coders(NONE_CODERS, "Failed: load font: " + std::string(path));
        }

        if (CORE_INFO && flagDebuginfo)
        {
            console::printTime();
            std::cout << "OK: load font: " << path << std::endl;
        }

#if TTF_LOAD_INFO == true
        printf("=== Font Information ===\n");
        printf("Family name: %s\n", face->family_name);
        printf("Style name: %s\n", face->style_name);
        printf("Number of faces in file: %ld\n", face->num_faces);
        printf("Face index: %ld\n", face->face_index);
        printf("Glyph count: %ld\n", face->num_glyphs);

        // Флаги
        printf("Scalable: %s\n", (face->face_flags & FT_FACE_FLAG_SCALABLE) ? "Yes" : "No");
        printf("Fixed sizes: %s\n", (face->face_flags & FT_FACE_FLAG_FIXED_SIZES) ? "Yes" : "No");
        printf("Kerning: %s\n", (face->face_flags & FT_FACE_FLAG_KERNING) ? "Yes" : "No");

        // Размеры
        printf("Units per EM: %d\n", face->units_per_EM);
        printf("Ascender: %d\n", face->ascender);
        printf("Descender: %d\n", face->descender);
        printf("Height: %d\n", face->height);
        printf("Underline position: %d\n", face->underline_position);
        printf("Underline thickness: %d\n", face->underline_thickness);
#endif //TTF_LOAD_INFO == true
    }

    TTF::~TTF()
    {
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    TTF TTF::load(const char *path, bool flagDebuginfo)
    {
        return TTF(path, flagDebuginfo);
    }

    TTF *TTF::ptrLoad(const char *path, bool flagDebuginfo)
    {
        return new TTF(path, flagDebuginfo);
    }

    } // namespace core

