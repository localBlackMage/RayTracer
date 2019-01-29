#include "stdafx.h"
#include "Slab.h"

Slab::Slab(Vec3 a_vCenter, float a_fWidth, Quaternion a_qRotation, Material * a_pMaterial) :
    Shape(a_pMaterial),
    m_vCenter(a_vCenter),
    m_fWidth(a_fWidth),
    m_fHalfWidth(a_fWidth / 2.f),
    m_vNormal(Vec3(0, 0, 1))
{
    m_vNormal = a_qRotation.RotateVector(m_vNormal);
}

Slab::~Slab()
{
}

bool Slab::Hit(const Ray & a_Ray, float a_fTMin, float a_fTMax, Intersection & a_Hit) const
{
    const Vec3& D = a_Ray.Direction();
    float nDotD = Vec3::Dot(m_vNormal, D);
    if (nDotD == 0.f)
        return false; // no collision

    const Vec3& S = a_Ray.Origin();
    float S0 = Vec3::Dot(m_vNormal, S) + m_fHalfWidth;
    float S1 = Vec3::Dot(m_vNormal, S) - m_fHalfWidth;
    float t0 = -(S0 / nDotD);
    float t1 = -(S1 / nDotD);

    if (t0 > t1)
        return false; // no collision

    if (AreSameSign(S0, S1))
    {
        a_Hit.m_Interval.m_fT0 = 0.f;
        a_Hit.m_Interval.m_fT0 = FLT_MAX;
        return true; // empty interval, inside slab
    }

    return false;
}
