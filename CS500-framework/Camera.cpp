#include "stdafx.h"

Camera::Camera(const Vector3f & a_vEye, const Quaternionf & a_qOrientation, const float a_fRY) :
    m_vLowerLeftCorner(Vector3f(-2.f, -1.f, -1.f)),
    m_vEye(a_vEye),
    m_vHorizontal(Vector3f(4.f, 0.f, 0.f)),
    m_vVertical(Vector3f(0, 2.f, 0.f)),
    m_qOrientation(a_qOrientation),
    m_fRY(a_fRY)
{
}

Camera::~Camera()
{}

Ray Camera::GetRay(float a_fU, float a_fV)
{
    return Ray(
        m_vEye,
        m_vLowerLeftCorner + a_fU * m_vHorizontal + a_fV * m_vVertical - m_vEye
    );
}
