#include "stdafx.h"

bool PointInsideBBox(const Bbox & box, const Vector3f & point)
{
    const Vector3f& L = box.min();  // Box corner
    const Vector3f& U = box.max();  // Box corner

    return (point.x() > L.x() && point.x() < U.x()) &&
        (point.y() > L.y() && point.y() < U.y()) &&
        (point.z() > L.z() && point.z() < U.z());
}

Minimizer::Scalar Minimizer::minimumOnObject(Shape * obj)
{
    Intersection hitData = m_HitData;
    if (obj->Hit(m_Ray, 0.0001f, INF, hitData))
    {
        if (hitData.m_fT < m_fT)
        {
            m_fT = hitData.m_fT;
            m_HitData = hitData;
        }
        return hitData.m_fT;
    }
    else
        return INF;
}

Minimizer::Scalar Minimizer::minimumOnVolume(const Bbox & box)
{
    if (PointInsideBBox(box, m_Ray.Origin()))
        return 0.f;

    const Vector3f& L = box.min();  // Box corner
    const Vector3f& U = box.max();  // Box corner
    Vector3f diag = U - L;

    AACube cube = AACube(L, diag, nullptr);
    Intersection hitData;
    if (cube.Hit(m_Ray, 0.0001f, INF, hitData))
        return hitData.m_fT;
    else
        return INF;
}
