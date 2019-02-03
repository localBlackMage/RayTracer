#pragma once

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
protected:
    Vector3f m_vEye;
    Vector3f m_vLowerLeftCorner;
    Vector3f m_vHorizontal;
    Vector3f m_vVertical;
    Quaternionf m_qOrientation;
    float m_fRY;

public:
    Camera(const Vector3f& a_vEye, const Quaternionf& a_qOrientation, const float a_fRY);
    ~Camera();

    Ray GetRay(float a_fU, float a_fV);
};

#endif //CAMERA_H