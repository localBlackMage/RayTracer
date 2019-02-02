#include "stdafx.h"

Cube::Cube(Vector3f a_vCenter, float a_fWidth, float a_fHeight, float a_fDepth, Quaternionf a_qRotation, Material * a_pMaterial) :
    Shape(a_pMaterial),
    m_vCenter(a_vCenter)
{
    Vector3f d0 = Vector3f(0.5f, 0, 0);
    Vector3f d1 = Vector3f(-0.5f, 0, 0);
    Vector3f N = Vector3f(1, 0, 0);
    Vector3f NPrime = a_qRotation._transformVector(N).normalized();

    m_Slabs[0] = {
       GetDValueForPlane(NPrime, a_qRotation._transformVector(d0)),
       GetDValueForPlane(NPrime, a_qRotation._transformVector(d1)),
       NPrime
    };

    d0 = Vector3f(0, 0.5f, 0);
    d1 = Vector3f(0, -0.5f, 0);
    N = Vector3f(0, 1, 0);
    NPrime = a_qRotation._transformVector(N).normalized();

    m_Slabs[1] = {
       GetDValueForPlane(NPrime, a_qRotation._transformVector(d0)),
       GetDValueForPlane(NPrime, a_qRotation._transformVector(d1)),
       NPrime
    };

    d0 = Vector3f(0, 0, 0.5f);
    d1 = Vector3f(0, 0, -0.5f);
    N = Vector3f(0, 0, 1);
    NPrime = a_qRotation._transformVector(N).normalized();

    m_Slabs[2] = {
       GetDValueForPlane(NPrime, a_qRotation._transformVector(d0)),
       GetDValueForPlane(NPrime, a_qRotation._transformVector(d1)),
       NPrime
    };
}

Cube::~Cube()
{

}

bool Cube::Hit(const Ray & a_Ray, float a_fTMin, float a_fTMax, Intersection & a_Hit) const
{
    const Vector3f& D = a_Ray.Direction();
    const Vector3f& S = a_Ray.Origin();
    Interval interval[3];
    Interval maxInterval;
    maxInterval.m_fT0 = 0.f;
    maxInterval.m_fT1 = FLT_MAX;

    for (uint32 i = 0; i < 3; ++i)
    {
        interval[i].m_fT0 = 0.f;
        interval[i].m_fT1 = FLT_MAX;
        interval[i].m_vNormal0 = m_Slabs[i].m_vNormal;
        interval[i].m_vNormal1 = m_Slabs[i].m_vNormal;

        float nDotD = m_Slabs[i].m_vNormal.dot(D);
        float nDotS = m_Slabs[i].m_vNormal.dot(S);
        float S0 = nDotS + m_Slabs[i].m_fD0;
        float S1 = nDotS + m_Slabs[i].m_fD1;
        if (nDotD != 0.f)
        {
            float t0 = -S0 / nDotD;
            float t1 = -S1 / nDotD;
            if (t0 > t1)
                SwapValues(t0, t1);

            interval[i].m_fT0 = t0;
            interval[i].m_fT1 = t1;
        }
        else if (AreSameSign(S0, S1))
        { 
            // outside the planes planes
            interval[i].m_fT0 = 1.f;
            interval[i].m_fT1 = 0.f;
        }
    }

    for (uint32 i = 0; i < 3; ++i)
    {
        if (interval[i].m_fT0 == 1.f && interval[i].m_fT1 == 0.f)
            continue;
        SetMinMaxInterval(maxInterval, interval[i]);
    }

    if (maxInterval.m_fT0 > maxInterval.m_fT1)
        return false;

    // smallest positive t value
    if (SetIntersectionFromLowestPositive(a_Hit, maxInterval))
    {
        a_Hit.m_vPoint = a_Ray.PointAt(a_Hit.m_fT);
        a_Hit.m_Interval = maxInterval;
        a_Hit.m_pMaterial = m_pMaterial;
        return true;
    }
    return false;
}



AABCube::AABCube(Vector3f a_vCorner, Vector3f a_vDiagonal, Material * a_pMaterial) :
    Cube(a_pMaterial),
    m_vCorner(a_vCorner),
    m_vDiagonal(a_vDiagonal)
{
    m_Slabs[0] = {
       -a_vCorner.x(),
       -a_vCorner.x() - a_vDiagonal.x(),
       Vector3f(1,0,0)
    };

    m_Slabs[1] = {
       -a_vCorner.y(),
       -a_vCorner.y() - a_vDiagonal.y(),
       Vector3f(0,1,0)
    };

    m_Slabs[2] = {
       -a_vCorner.z(),
       -a_vCorner.z() - a_vDiagonal.z(),
       Vector3f(0,0,1)
    };
}

AABCube::~AABCube()
{
}

bool AABCube::Hit(const Ray & a_Ray, float a_fTMin, float a_fTMax, Intersection & a_Hit) const
{
    return Cube::Hit(a_Ray, a_fTMin, a_fTMax, a_Hit);
}
