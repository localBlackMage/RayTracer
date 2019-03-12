#include "stdafx.h"

Interval SlabIntersect(const RTSlab & a_Slab, const Ray& a_Ray)
{
    Interval interval;
    const Vector3f& D = a_Ray.Direction();
    const Vector3f& S = a_Ray.Origin();

    interval.m_vNormal0 = a_Slab.m_vNormal;
    interval.m_vNormal1 = -a_Slab.m_vNormal;

    float nDotD = a_Slab.m_vNormal.dot(D);
    float nDotS = a_Slab.m_vNormal.dot(S);
    float S0 = nDotS + a_Slab.m_fD0;
    float S1 = nDotS + a_Slab.m_fD1;
    if (nDotD != 0.f)
    {
        float t0 = -S0 / nDotD;
        float t1 = -S1 / nDotD;
        if (t0 > t1)
            SwapValues(t0, t1);

        interval.m_fT0 = t0;
        interval.m_fT1 = t1;
    }
    else if (AreSameSign(S0, S1))
    {
        // outside the planes planes
        interval.m_fT0 = 1.f;
        interval.m_fT1 = 0.f;
    }

    return interval;
}
