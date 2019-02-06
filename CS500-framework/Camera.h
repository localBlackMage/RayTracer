#pragma once

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
protected:
    Vector3f m_vEye;
    Vector3f m_vX, m_vY, m_vZ;

    Quaternionf m_qOrientation;
    float m_fWidth, m_fHeight, m_fRX, m_fRY;

public:
    Camera(const Vector3f & a_vEye, const Quaternionf & a_qOrientation, float a_fWidth, float a_fHeight, float a_fRY);
    ~Camera();

    Ray GetRay(float a_fX, float a_fY);
};

#endif //CAMERA_H