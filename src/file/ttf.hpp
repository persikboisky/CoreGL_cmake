//
// Created by kisly on 15.12.2025.
//

#ifndef TTF_HPP
#define TTF_HPP

typedef struct FT_LibraryRec_ *FT_Library;
typedef struct FT_FaceRec_ *FT_Face;

namespace core
{
    class TTF
    {
    private:
        FT_Library ft = nullptr;
        FT_Face face = nullptr;

        TTF(const char* path, bool flagDebuginfo);

    public:
        ~TTF();

        static TTF load(const char* path, bool flagDebuginfo = true);
        static TTF* ptrLoad(const char* path, bool flagDebuginfo = true);
    };
} // namespace core

#endif // TTF_HPP
