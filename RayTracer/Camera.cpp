#include "stdafx.h"


Camera::Camera() :
    m_vLowerLeftCorner(Vec3(-2.f, -1.f, -1.f)),
    m_vOrigin(Vec3(0, 0, 0, 1)),
    m_vHorizontal(Vec3(4.f, 0.f, 0.f)),
    m_vVertical(Vec3(0, 2.f, 0.f))
{}

Camera::~Camera()
{}

Ray Camera::GetRay(float a_fU, float a_fV)
{
    return Ray(
        m_vOrigin, 
        m_vLowerLeftCorner + a_fU * m_vHorizontal + a_fV * m_vVertical - m_vOrigin
    );
}
