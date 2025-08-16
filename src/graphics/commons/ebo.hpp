//
// Created by kisly on 14.07.2025.
//

#ifndef EBO_HPP
#define EBO_HPP

#include "Descriptor.hpp"
#include <vector>

namespace core
{
    enum PRIMITIVE : int;

    class VAO;

    struct ebo
    {
    private:
        [[maybe_unused]] static std::vector<unsigned int> id;
        [[maybe_unused]] static unsigned int SelectID;

        [[maybe_unused]] static unsigned int SelectVAO;

    public:
        /// @brief âêëþ÷àåò ebo ïî åãî äåñêðèïòîðó
        /// @param id äåñêðèïòîð
        static void bind(unsigned int id);
        static void unBind();

        /// @brief ñîçäà¸ò ebo
        /// @param indexes ìàññèâ èíäåêñîâ
        /// @param sizeOfByte ðàçìåð ìàññèâà â áàéòàõ
        /// @return äåñêðèïòîð
        static unsigned int create(unsigned int* indexes, unsigned int sizeOfByte);

        /// @brief ñîçäà¸ò ebo
        /// @param indexes âåêòîð èíäåêñîâ
        /// @return äåñêðèïòîð
        static unsigned int create(std::vector<unsigned int> indexes);

        /// @brief ðèñóåò ïðèìèòèâ, èñïîëüçóÿ äàííûå èç âêëþ÷åííîãî vao
        /// @param Primitive íàçâàíèå ïðèìèòèâà
        /// @param nVert êîë-âî âåðøèí
        static void draw(PRIMITIVE Primitive, unsigned int nVert);

        /// @brief ðèñóåò ïðèìèòèâ, èñïîëüçóÿ äàííûå èç âêëþ÷åííîãî vao
        /// @param Primitive íàçâàíèå ïðèìèòèâà
        /// @param ebo äåñêðèïòîð ebo
        /// @param nVert êîë-âî âåðøèí
        static void draw(PRIMITIVE Primitive, unsigned int ebo, unsigned int nVert);

        /// @brief ðèñóåò ïðèìèòèâ
        /// @param Primitive íàçâàíèå ïðèìèòèâà
        /// @param ebo äåñêðèïòîð ebo
        /// @param vao äåñêðèïòîð vao
        /// @param nVert êîë-âî âåðøèí
        static void draw(PRIMITIVE Primitive, unsigned int ebo, unsigned int vao, unsigned int nVert);

        /// @brief ðèñóåò ïðèìèòèâ
        /// @param Primitive íàçâàíèå ïðèìèòèâà
        /// @param ebo äåñêðèïòîð ebo
        /// @param vao îáúåêò vao
        /// @param nVert êîë-âî âåðøèí
        static void draw(PRIMITIVE Primitive, unsigned int ebo, VAO& vao, unsigned int nVert);

        /// @brief óäàëÿåò ebo ïî åãî äåñêðèïòîðó
        /// @param id äåñêðèïòîð
        static void Delete(unsigned int id);

        /// @brief óäàëÿåò âñå ebo
        static void DeleteALL();

        /// @brief óñòàíàâëèâàåò ðàçìåð òî÷êè, åñëè â êà÷åñòâå ïðèìèòèâà òî÷êà
        /// @param sizePixel ðàçìåð â ïèêñåëÿõ
        static void setSizePoints(float sizePixel);

        /// @brief óñòàíàâëèâàåò øèðèíó ëèíèè, åñëè â êà÷åñòâå ïðèìèòèâà ëèíèÿ(èè)
        /// @param width øèðèíà â ïèêñåëÿõ
        static void setWidthLine(float width);
    };


    class EBO
    {
    private:
        unsigned int vao;
        VAO* Vao;

        unsigned int nVert;
        unsigned int id;

        char typeVao = ' ';

        float widthLine = 1.0f;
        float sizePoint = 1.0f;

    public:
        EBO(unsigned int* indexes, unsigned int sizeOfByte);
        explicit EBO(std::vector<unsigned int> indexes);

        ~EBO();

        void linkVAO(unsigned int vao);
        void linkVAO(VAO& vao);

        void bind();
        void draw(PRIMITIVE Primitive, unsigned int nVert = 0);

        void setSizePoints(float sizePixel);
        void setWidthLine(float width);
    };
}

#endif //EBO_HPP
