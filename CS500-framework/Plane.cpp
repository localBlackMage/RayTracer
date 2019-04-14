#include "stdafx.h"

float PlaneIntersect(const RTPlane& a_Plane, const Ray & a_Ray)
{
    const Vector3f& D = a_Ray.Direction();
    const Vector3f& S = a_Ray.Origin();
    float nDotD = a_Plane.m_vNormal.dot(D);
    float nDotS = a_Plane.m_vNormal.dot(S);

    float S0 = nDotS + a_Plane.m_fD;

    if (nDotD != 0.f)
    {
        return -S0 / nDotD;
    }

    return -1.f;
}
