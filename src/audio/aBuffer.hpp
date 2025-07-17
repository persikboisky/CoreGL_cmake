//
// Created by kisly on 17.07.2025.
//

#ifndef ABUFFERS_HPP
#define ABUFFERS_HPP

namespace core
{
    class wav;

    namespace audio
    {
        class Buffer
        {
        private:
            unsigned int id;

            Buffer(const char *path);
            Buffer(wav& obj);

        public:
            ~Buffer();

            static Buffer create(const char *path);
            static Buffer create(wav& obj);

            static Buffer *ptrCreate(const char *path);
            static Buffer *ptrCreate(wav& obj);

            [[nodiscard]] unsigned int getID();
        };
    }
} // core

#endif //ABUFFERS_HPP
