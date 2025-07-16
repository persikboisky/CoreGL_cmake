//
// Created by kisly on 16.07.2025.
//

#ifndef OPENGL_TIME_HPP
#define OPENGL_TIME_HPP

namespace core
{
    class Timer
    {
    private:
        double time;
        double interval;

        Timer();

    public:

        /// @brief создаёт таймер, и возвращает его объект
        /// @return объект таймера (Timer)
        static Timer create();

        ~Timer();

        /// @brief запускает таймер
        void start();

        /// @brief останавливает таймер
        void stop();

        /// @brief сбрасывает таймер
        void reset();

        /// @brief возвращает время в секундах
        /// @return время
        [[nodiscard]] double getTime() const;

        void setTime(double time);
        void addTime(double time);
        void difTime(double time);
    };
} // core

#endif //OPENGL_TIME_HPP
