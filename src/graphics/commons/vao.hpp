//
// Created by kisly on 14.07.2025.
//

#ifndef VAO_HPP
#define VAO_HPP

#include "Descriptor.hpp"
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

        static void setSeletId(unsigned int id);
        static unsigned int getSelectId();
    };

    class VAO : public Descriptor
    {
    private:
        unsigned int elementToVert;
        int size;

        float widthLine = 1.0f;
        float sizePoint = 1.0f;

        VAO(float *data, size_t sizeOfByte, int elementToVert);

    public:
        static VAO create(float *data, size_t sizeOfByte, int elementToVert);
        static VAO create(std::vector<float> data, int elementToVert);

        static VAO *ptrCreate(float *data, size_t sizeOfByte, int elementToVert);
        static VAO *ptrCreate(std::vector<float> data, int elementToVert);

        ~VAO();

        void bind() override;

        void addAttribute(int index, int n, int indentation) const;

        void draw(PRIMITIVE Primitive, int first_vert = 0, int count_vert = 0);
        void setSizePoints(float sizePixel);
        void setWidthLine(float width);

        unsigned int getId() override;
    };
}

#endif // VAO_HPP
