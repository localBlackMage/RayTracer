#include "stdafx.h"
#include "Slab.h"

Slab::Slab(Vector3f a_vCenter, float a_fWidth, Quaternionf a_qRotation, Material * a_pMaterial) :
    Shape(a_pMaterial),
    m_vCenter(a_vCenter),
    m_fWidth(a_fWidth),
    m_fHalfWidth(a_fWidth / 2.f),
    m_vNormal(Vector3f(0, 0, 1))
{
    m_vNormal = a_qRotation._transformVector(m_vNormal);
}

Slab::~Slab()
{
}

bool Slab::Hit(const Ray & a_Ray, float a_fTMin, float a_fTMax, Intersection & a_Hit) const
{
    const Vector3f& D = a_Ray.Direction();
    float nDotD = m_vNormal.dot(D);
    if (nDotD == 0.f)
        return false; // no collision

    const Vector3f& S = a_Ray.Origin();
    float nDotS = m_vNormal.dot(S);
    float S0 = nDotS + m_fHalfWidth;
    float S1 = nDotS - m_fHalfWidth;
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
