#include "stdafx.h"

Ray::Ray()
{}

Ray::Ray(const Vec3 & a, const Vec3 & b) : 
    m_A(a),
    m_B(b)
{}

Ray::Ray(const Ray & rhs) : 
    m_A(rhs.m_A),
    m_B(rhs.m_B)
{}

Ray Ray::operator=(const Ray & rhs)
{
    m_A = rhs.m_A;
    m_B = rhs.m_B;
    return *this;
}

Ray::~Ray() {}

Vec3 Ray::PointAt(const float & a_fT) const
{
    return m_A + a_fT * m_B;
}
