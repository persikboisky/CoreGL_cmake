//
// Created by kisly on 14.07.2025.
//

#include "Camera.hpp"
#include "../../math/Vectors.hpp"
#include "../../math/Matrix4.hpp"
#include "../../math/math.hpp"
#include "../../window/Window.hpp"
#include "../../util/types.hpp"

using namespace core;
using namespace math;

cameraInfo::cameraInfo() : mode(CAM_DYNAMIC) {}

static inline float convertNumberToUnit(float number) 
{   
    if (number > 0) return 1;
    else if (number < 0) return -1;
    else return 0;
}

void Camera::update()
{
    if (this->mode == CAM_DYNAMIC)
    {
        this->up = Vector3(rot * Vector4(this->startUP, 1));
        this->target = Vector3(rot * Vector4(this->startTARGET, 1));
    }
    else 
    {
        this->up = Vector3(rot * Vector4(this->startUP, 1));
        this->target = Vector3(rot * Vector4(math::Vector3(
            convertNumberToUnit(this->startTARGET.x),
            convertNumberToUnit(this->startTARGET.y),
            convertNumberToUnit(this->startTARGET.z)
        ), 1.0f));
    }
}

Camera::Camera(float posX, float posY, float posZ, float fov, float distance) :
        far(distance), mode(CAM_STATIC), startUP(Vector3(0, 1, 0)), startTARGET(Vector3(0, 0, -1)),
        pos(Vector3(posX, posY, posZ)), fov(radians(fov)), near(0.1f)
{
    this->update();
}

Camera::Camera(Vector3 pos, float fov, float distance) :
        far(distance), mode(CAM_STATIC), startUP(Vector3(0, 1, 0)), startTARGET(Vector3(0, 0, -1)),
        pos(pos), fov(radians(fov)), near(0.1f)
{
    this->update();
}

Camera::Camera(const cameraInfo& info) :
        far(info.far), mode(info.mode), near(info.near), pos(info.position),
        startUP(info.up), startTARGET(info.target), fov(radians(info.fov))
{
    this->update();
}

void Camera::setMode(const CAM_MODE& mode)
{
    this->mode = mode;
}

void Camera::setFov(float fov)
{
    this->fov = radians(fov);
}

void Camera::setDistance(float distance)
{
    this->far = distance;
}

void Camera::rotate(float x, float y, float z)
{
    if (this->mode == CAM_STATIC)
    {
        this->rot = Matrix4::getRotate(radians(x), Vector3(1, 0, 0), this->rot);
        this->rot = Matrix4::getRotate(radians(y), Vector3(0, 1, 0), this->rot);
        this->rot = Matrix4::getRotate(radians(z), Vector3(0, 0, 1), this->rot);
        this->update();
    }
}

void Camera::rotate(const math::Vector3& axis)
{
    this->rotate(axis.x, axis.y, axis.z);
}

void Camera::resetRotate()
{
    this->rot = Matrix4(1.0f);
}

void Camera::move(float x, float y, float z)
{
    this->pos.x += x;
    this->pos.y += y;
    this->pos.z += z;
}

void Camera::move(const math::Vector3 vec3)
{
    this->pos += vec3;
}

void Camera::setPos(float x, float y, float z)
{
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
}

void Camera::setPos(const Vector3& pos)
{
    this->setPos(pos.x, pos.y, pos.z);
}

void Camera::setTarget(float x, float y, float z)
{
    this->target.x = x;
    this->target.y = y;
    this->target.z = z;
}

void Camera::setTarget(const Vector3& target)
{
    this->setTarget(target.x, target.y, target.z);
}

void Camera::getPos(float& x, float& y, float& z) const
{
    x = this->pos.x;
    y = this->pos.y;
    z = this->pos.z;
}

void Camera::getPos(Vector3& pos) const
{
    pos.x = this->pos.x;
    pos.y = this->pos.y;
    pos.z = this->pos.z;
}

void Camera::getSTarget(float& x, float& y, float& z) const
{
    x = this->startTARGET.x;
    y = this->startTARGET.y;
    z = this->startTARGET.z;
}

void Camera::getSTarget(math::Vector3& target) const
{
    target.x = this->startTARGET.x;
    target.y = this->startTARGET.y;
    target.z = this->startTARGET.z;
}

void Camera::getTarget(float& x, float& y, float& z) const
{
    x = this->target.x;
    y = this->target.y;
    z = this->target.z;
}

void core::Camera::getTarget(math::Vector3& target) const
{
    target.x = this->target.x;
    target.y = this->target.y;
    target.z = this->target.z;
}

Matrix4 Camera::getProj(int width, int height) const
{
    float aspect = (float)width / (float)height;
    return Matrix4::getPerspective(this->fov, aspect, this->near, this->far);
}

Matrix4 Camera::getView()
{
    if (this->mode == CAM_DYNAMIC)
    {
        return Matrix4::getLookAt(this->pos, this->target, this->up);
    }

    return Matrix4::getLookAt(this->pos, this->pos + this->target, this->up);
}