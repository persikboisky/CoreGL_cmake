//
// Created by kisly on 14.07.2025.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../math/Vectors.hpp"
#include "../../math/Matrix4.hpp"

namespace core
{
    enum KEY_CODE : int;
    enum CAM_MODE : int;

    class Shader;

    struct cameraInfo
    {
        math::Vector3 up = math::Vector3(0, 1, 0);
        math::Vector3 position = math::Vector3(0, 0, 4);
        math::Vector3 target = math::Vector3(0, 0, -1);
        float fov = 70.0f;
        float far = 100.0f;
        float near = 0.1f;
        CAM_MODE mode;

        cameraInfo();
    };

    /// @brief êëàññ äëÿ ðàáîòû ñ êàìåðîé
    class Camera
    {
    private:

        math::Vector3 startUP;
        math::Vector3 startTARGET;

        math::Vector3 up;
        math::Vector3 target;
        math::Vector3 pos;

        math::Matrix4 rot = math::Matrix4(1.0f);

        float fov;
        float far;
        float near;

        CAM_MODE mode;

        void update();

    public:
        /// @brief êîíñòðóêòîð êàìåðû
        /// @param posX ïîçèöèÿ êàìåðû ïî x
        /// @param posY ïîçèöèÿ êàìåðû ïî y
        /// @param posZ ïîçèöèÿ êàìåðû ïî z
        /// @param fov ïîëå çðåíèÿ â ãðàäóñàõ
        /// @param distance äàëüíîñòü çðåíèÿ
        Camera(float posX, float posY, float posZ, float fov = 70, float distance = 100);

        /// @brief êîíñòðóêòîð êàìåðû
        /// @param pos ïîçèöèÿ êàìåðû
        /// @param fov ïîëå çðåíèÿ â ãðàäóñàõ
        /// @param distance äàëüíîñòü çðåíèÿ
        Camera(math::Vector3 pos, float fov = 70, float distance = 100);

        //rf
        Camera(const cameraInfo& info);

        /// @brief óñòàíàâëèâàåò ðåæèì êàìåðû
        /// @param mode ðåæèì (Ïðèìåð: STATIC, DYNAMIC)
        void setMode(const CAM_MODE& mode);

        /// @brief óñòàíàâëèâàåò ïîëå çðåíèÿ
        /// @param fov ïîëå çðåíèÿ â ãðàäóñàõ
        void setFov(float fov);

        /// @brief óñòàíàâëèâàåò äàëüíîñòü çðåíèÿ
        /// @param distance äàëüíîñòü çðåíèÿ
        void setDistance(float distance);

        /// @brief ïîâîðà÷èâàåò êàìåðó ïî çàäàííûì îñÿì
        /// @param x óãîë ïîâîðîòà ïî îñè x â ãðàäóñàõ
        /// @param y óãîë ïîâîðîòà ïî îñè y â ãðàäóñàõ
        /// @param z óãîë ïîâîðîòà ïî îñè z â ãðàäóñàõ
        void rotate(float x, float y, float z);

        /// @brief ïîâîðà÷èâàåò êàìåðó ïî çàäàííûì îñÿì
        /// @param axis óãîë ïîâîðîòà ïî îñÿì â ãðàäóñàõ â âèäå âåêòîðà
        void rotate(const math::Vector3& axis);

        /// @brief îáíóëÿåò ïîâîðîò êàìåðû(âîçâðàùàåò â èñõîäíîå ïîëîæåíèå)
        void resetRotate();

        /// @brief ïåðåìåùàåò êàìåðó ïî çàäàííûì îñÿì
        /// @param x ñäâèã êàìåðû ïî x
        /// @param y ñäâèã êàìåðû ïî y
        /// @param z ñäâèã êàìåðû ïî z
        void move(float x, float y, float z);

        void move(const math::Vector3 vec3);

        /// @brief óñòàíàâëèâàåò êàìåðó íà çàäàííûå êîîðäèíàòû
        /// @param x êîîðäèíàòà x
        /// @param y êîîðäèíàòà y
        /// @param z êîîðäèíàòà z
        void setPos(float x, float y, float z);

        /// @brief óñòàíàâëèâàåò êàìåðó íà çàäàííûå êîîðäèíàòû
        /// @param pos âåêòîð ñ êîîðäèíàòàìè
        void setPos(const math::Vector3& pos);

        /// @brief óñòàíàâëèâàåò òî÷êó â êîòîðóþ ñìîòðèò êàìåðà
        /// @param x êîîðäèíàòà x
        /// @param y êîîðäèíàòà y
        /// @param z êîîðäèíàòà z
        void setTarget(float x, float y, float z);

        /// @brief óñòàíàâëèâàåò òî÷êó â êîòîðóþ ñìîòðèò êàìåðà
        /// @param target âåêòîð ñ êîîðäèíàòàìè
        void setTarget(const math::Vector3& target);

        /// @brief ïîëó÷àåò ïîçèöèþ êàìåðû
        /// @param x ïåðåìåííàÿ äëÿ õðàíåíèÿ êîîðäèíàòû x
        /// @param y ïåðåìåííàÿ äëÿ õðàíåíèÿ êîîðäèíàòû y
        /// @param z ïåðåìåííàÿ äëÿ õðàíåíèÿ êîîðäèíàòû z
        void getPos(float& x, float& y, float& z) const;

        /// @brief ïîëó÷àåò ïîçèöèþ êàìåðû
        /// @param pos âåêòîð äëÿ õðàíåíèÿ êîîðäèíàò
        void getPos(math::Vector3& pos) const;

        /// @brief ïîëó÷àåò êîîðäèíàòó êóäà ñìîòðèò êàìåðà
        /// @param x ïåðåìåííàÿ äëÿ õðàíåíèÿ êîîðäèíàòû x
        /// @param y ïåðåìåííàÿ äëÿ õðàíåíèÿ êîîðäèíàòû y
        /// @param z ïåðåìåííàÿ äëÿ õðàíåíèÿ êîîðäèíàòû z
        void getSTarget(float& x, float& y, float& z) const;

        /// @brief ïîëó÷àåò êîîðäèíàòó êóäà ñìîòðèò êàìåðà
        /// @param target âåêòîð äëÿ õðàíåíèÿ êîîðäèíàò
        void getSTarget(math::Vector3& target) const;

        void getTarget(float& x, float& y, float& z) const;
        void getTarget(math::Vector3& target) const;


        /// @brief ñîçäà¸ò ìàòðèöó ïðîåêöèè êàìåðû
        /// @param width øèðèíà îêíà
        /// @param height âûñîòà îêíà
        /// @return âîçâðàùàåò ìàòðèöó ïðîåêöèè
        math::Matrix4 getProj(int width, int height) const;

        /// @brief ñîçäà¸ò âèäîâóþ ìàòðèöó êàìåðû
        /// @return âîçâðàùàåò âèäîâóþ ìàòðèöó
        math::Matrix4 getView();
    };
}

#endif //CAMERA_HPP
