#include "stdafx.h"


Camera::Camera() :
    m_vLowerLeftCorner(Vector3f(-2.f, -1.f, -1.f)),
    m_vOrigin(Vector3f(0, 0, 0)),
    m_vHorizontal(Vector3f(4.f, 0.f, 0.f)),
    m_vVertical(Vector3f(0, 2.f, 0.f))
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
