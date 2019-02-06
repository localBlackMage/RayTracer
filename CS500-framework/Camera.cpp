#include "stdafx.h"

Camera::Camera(const Vector3f & a_vEye, const Quaternionf & a_qOrientation, float a_fWidth, float a_fHeight, float a_fRY) :
    m_vEye(a_vEye),
    m_qOrientation(a_qOrientation),
    m_fWidth(a_fWidth),
    m_fHeight(a_fHeight),
    m_fRY(a_fRY),
    m_fRX(a_fRY * (a_fWidth / a_fHeight))
{

    m_vX = m_qOrientation._transformVector(Vector3f::UnitX()) * m_fRX;
    m_vY = m_qOrientation._transformVector(Vector3f::UnitY()) * m_fRY;
    m_vZ = m_qOrientation._transformVector(Vector3f::UnitZ()) * -1.f;
}

Camera::~Camera()
{}

Ray Camera::GetRay(float a_fX, float a_fY)
{
    Vector3f direction = a_fX * m_vX + a_fY * m_vY + m_vZ;
    return Ray(m_vEye, direction.normalized());
}
