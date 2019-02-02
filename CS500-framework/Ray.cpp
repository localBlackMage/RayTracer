#include "stdafx.h"

Ray::Ray()
{}

Ray::Ray(const Vector3f & a_vOrigin, const Vector3f & a_vDirection) :
    m_vOrigin(a_vOrigin),
    m_vDirection(a_vDirection)
{}

Ray::Ray(const Ray & rhs) : 
    m_vOrigin(rhs.m_vOrigin),
    m_vDirection(rhs.m_vDirection)
{}

Ray Ray::operator=(const Ray & rhs)
{
    m_vOrigin = rhs.m_vOrigin;
    m_vDirection = rhs.m_vDirection;
    return *this;
}

Ray::~Ray() {}

Vector3f Ray::PointAt(const float & a_fT) const
{
    return m_vOrigin + a_fT * m_vDirection;
}
