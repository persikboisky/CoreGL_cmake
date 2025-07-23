//
// Created by kisly on 14.07.2025.
//

#ifndef VAO_HPP
#define VAO_HPP

#include <vector>

namespace core
{
    enum PRIMITIVE : int;

    struct vao
    {
    private:
        static std::vector<unsigned int> idVAO;
        static std::vector<unsigned int> idVBO;
        static unsigned int selectID;

    protected:
        static unsigned int getSelectId();

    public:
        static void bind(unsigned int id);

        [[nodiscard]] static unsigned int create(float *data, int sizeOfByte);
        [[nodiscard]] static unsigned int create(std::vector<float> data);

        static void addAttribute(unsigned int id, int index, int n, int size, int indentation);

        static void Delete(unsigned int id);
        static void DeleteALL();

        static void draw(PRIMITIVE Primitive, int first_vert, int count_vert);
        static void draw(PRIMITIVE Primitive, unsigned int VAO, int first_vert, int count_vert);

        static void setSizePoints(float sizePixel);
        static void setWidthLine(float width);
    };

    class VAO : private vao
    {
    private:
        unsigned int id = 0;
        unsigned int elementToVert;
        int size;

        float widthLine = 1.0f;
        float sizePoint = 1.0f;

    public:
        VAO(float *data, int sizeOfByte, int elementToVert);
        VAO(std::vector<float> data, int elementToVert);

        ~VAO();

        void bind() const;

        void addAttribute(int index, int n, int indentation) const;

        void draw(PRIMITIVE Primitive, int first_vert = 0, int count_vert = 0) const;
        void setSizePoints(float sizePixel);
        void setWidthLine(float width);

        [[nodiscard]] unsigned int getId();
    };
}

#endif //VAO_HPP
