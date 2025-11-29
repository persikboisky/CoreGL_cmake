//
// Created by kisly on 17.07.2025.
//

#ifndef SOURCE_HPP
#define SOURCE_HPP

namespace core
{
    struct Pos3f;

    namespace audio
    {
        class Buffer;

        class Source
        {
        private:
            unsigned int id;

            Source();

        public:
            ~Source();

            static Source create();
            static Source* ptrCreate();

            void linkBuffer(Buffer buffer) const;
            void setVolume(float value = 1.0f) const;
            void setSpeed(float value = 1.0f) const;
            void looping(bool flag = false) const;

            void play() const;
            void pause() const;
            void stop() const;
            void resume() const;

            bool isPlaying() const;

            void setPos(float x, float y, float z) const;
            void setPos(const Pos3f& pos) const;

            void setVelocity(float x, float y, float z) const;
        };
    }
} // core

#endif //SOURCE_HPP
