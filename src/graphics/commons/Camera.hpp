//
// Created by kisly on 14.07.2025.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../math/Vectors.hpp"
#include "../../math/Matrix4.hpp"

namespace core
{
    enum class CAM_MODE : int
    {
        DYNAMIC,
        STATIC
    };

    struct CameraInfo
    {
        math::Vec3 up = math::Vec3(0, 1, 0);
        math::Vec3 position = math::Vec3(0, 0, 4);
        math::Vec3 target = math::Vec3(0, 0, -1);
        float fov = 70.0f;
        float far = 100.0f;
        float near = 0.1f;
        CAM_MODE mode;

        CameraInfo();
    };

    /// @brief класс камеры
    class Camera
    {
    private:
        math::Vec3 startUP;
        math::Vec3 startTARGET;

        math::Vec3 up;
        math::Vec3 target;
        math::Vec3 pos;

        math::Mat4 rot = math::Mat4(1.0f);

        float fov;
        float far;
        float near;

        CAM_MODE mode;

        void update();

        Camera(float posX, float posY, float posZ, float fov = 70, float distance = 100);
        Camera(math::Vec3 pos, float fov = 70, float distance = 100);
        Camera(const CameraInfo &info);

    public:
        /// @brief создаёт камеру
        /// @param posX позиция камеры
        /// @param posY позиция камеры
        /// @param posZ позиция камеры
        /// @param fov угол обзора(в градусах)
        /// @param distance дистанция на которую будет видеть камера
        /// @return объект класса Camera
        static Camera create(float posX, float posY, float posZ, float fov = 70, float distance = 100);

        /// @brief создаёт камеру
        /// @param pos позиция камеры
        /// @param fov угол обзора(в градусах)
        /// @param distance дистанция на которую будет видеть камера
        /// @return объект класса Camera
        static Camera create(math::Vec3 pos, float fov = 70, float distance = 100);

        /// @brief создаёт камеру
        /// @param info объект структуры CameraInfo
        /// @return объект класса Camera
        static Camera create(const CameraInfo &info);

        /// @brief создаёт камеру
        /// @param posX позиция камеры
        /// @param posY позиция камеры
        /// @param posZ позиция камеры
        /// @param fov угол обзора(в градусах)
        /// @param distance дистанция на которую будет видеть камера
        /// @return указатель на объект класса Camera
        static Camera *ptrCreate(float posX, float posY, float posZ, float fov = 70, float distance = 100);

        /// @brief создаёт камеру
        /// @param pos позиция камеры
        /// @param fov угол обзора(в градусах)
        /// @param distance дистанция на которую будет видеть камера
        /// @return указатель на объект класса Camera
        static Camera *ptrCreate(math::Vec3 pos, float fov = 70, float distance = 100);

        /// @brief создаёт камеру
        /// @param info объект структуры CameraInfo
        /// @return указатель на объект класса Camera
        static Camera *ptrCreate(const CameraInfo &info);

        /// @brief устанавливает режим камеры
        /// @param mode (CAM_DYNAMIC - смотрит в одну точку, CAM_STATIC - смотрит в одном направлении)
        void setMode(const CAM_MODE &mode);

        /// @brief устанавливает угол обзора
        /// @param fov угол обзора(в градусах)
        void setFov(float fov);

        /// @brief устанавливает дальность видимости камеры
        /// @param distance дальность видимости 
        void setDistance(float distance);

        /// @brief поворачивает направление камеры(работает только при CAM_STATIC)
        /// @param x угол поворота по оси x в градусах
        /// @param y угол поворота по оси y в градусах
        /// @param z угол поворота по оси z в градусах
        void rotate(float x, float y, float z);

        /// @brief поворачивает направление камеры(работает только при CAM_STATIC)
        /// @param axis углы поворота в градусах, записанные в объект класса math::Vec3
        void rotate(const math::Vec3 &axis);

        /// @brief сбрасывает направление камеры в начальное
        void resetRotate();

        /// @brief перемещает камеру на указанные значения по трём осям
        /// @param x по x
        /// @param y по y
        /// @param z по z
        void move(float x, float y, float z);

        /// @brief перемещает камеру на указанные значения по трём осям
        /// @param vec3 значения, записанные в объект класса math::Vec3
        void move(const math::Vec3 vec3);

        /// @brief устанавливает положение камеры
        /// @param x позиция
        /// @param y позиция
        /// @param z позиция
        void setPos(float x, float y, float z);

        /// @brief устанавливает положение камеры
        /// @param pos объект класса math::Vec3
        void setPos(const math::Vec3 &pos);

        /// @brief устанавливает цель камеры(для CAM_STATIC - это направление, 
        /// @brief для CAM_DYNAMIC - это точка куда смотрит камера)
        /// @param x направление(точка) по x
        /// @param y направление(точка) по y
        /// @param z направление(точка) по z
        void setTarget(float x, float y, float z);

        /// @brief устанавливает цель камеры(для CAM_STATIC - это направление, 
        /// @brief для CAM_DYNAMIC - это точка куда смотрит камера)
        /// @param target вектор направления(координаты точки)
        void setTarget(const math::Vec3 &target);

        /// @brief получает позиция камеры
        /// @param x переменная для записи координаты по x
        /// @param y переменная для записи координаты по y
        /// @param z переменная для записи координаты по z
        void getPos(float &x, float &y, float &z) const;

        /// @brief получает позиция камеры
        /// @param pos ссылка на объект math::Vec3
        void getPos(math::Vec3 &pos) const;

        /// @brief возвращает начальную цель(- точка для CAM_DYNAMIC, - направление для CAM_STATIC) камеры
        /// @param x переменная для записи координаты по x
        /// @param y переменная для записи координаты по y
        /// @param z переменная для записи координаты по z
        void getSTarget(float &x, float &y, float &z) const;

        /// @brief возвращает начальную цель(- точка для CAM_DYNAMIC, - направление для CAM_STATIC) камеры
        /// @param target ссылка на объект math::Vec3
        void getSTarget(math::Vec3 &target) const;

        /// @brief возвращает текущую цель(- точка для CAM_DYNAMIC, - направление для CAM_STATIC) камеры
        /// @param x переменная для записи координаты по x
        /// @param y переменная для записи координаты по y
        /// @param z переменная для записи координаты по z
        void getTarget(float &x, float &y, float &z) const;

        /// @brief  возвращает текущую цель(- точка для CAM_DYNAMIC, - направление для CAM_STATIC) камеры
        /// @param target ссылка на объект math::Vec3
        void getTarget(math::Vec3 &target) const;

        /// @brief возвращает матрицу проекции
        /// @param windowWidth ширина окна
        /// @param windowHeight высота окна
        /// @return матрица
        math::Mat4 getProj(int windowWidth, int windowHeight) const;

        /// @brief возвращает матрицу проекции
        /// @param windowSize размер окна (объект структуры size2i)
        /// @return матрица
        math::Mat4 getProj(const struct Size2i &windowSize) const;

        /// @brief возвращает матрицу вида
        /// @return матрица
        math::Mat4 getView();
    };
}

#endif // CAMERA_HPP
