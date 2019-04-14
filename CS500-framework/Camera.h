#pragma once

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
protected:
    Vector3f m_vEye;
    Vector3f m_vX, m_vY, m_vZ;
    float m_fDistToFocusPlane;      // D
    float m_fSizeOfConfusionCircle; // W

    Quaternionf m_qOrientation;
    float m_fWidth, m_fHeight, m_fRX, m_fRY;

public:
    Camera(const Vector3f & a_vEye, const Quaternionf & a_qOrientation, float a_fWidth, float a_fHeight, float a_fRY, float a_fDistToFocusPlane, float a_fSizeOfConfusionCircle);
    ~Camera();

    bool HasDOF() const { return m_fDistToFocusPlane > 0.f; }
    Ray GetRay(float a_fX, float a_fY);
    Ray GetBlurredRay(float a_fX, float a_fY);
    float GetDValue() const { return m_fDistToFocusPlane; }
};

#endif //CAMERA_H