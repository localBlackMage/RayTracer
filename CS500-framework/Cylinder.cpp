#include "stdafx.h"

Cylinder::Cylinder(const Vector3f & a_vLocation, const Vector3f& a_vAxis, float a_fRadius, Material * a_pMaterial) :
    Shape(a_pMaterial),
    m_vLocation(a_vLocation),
    m_vAxis(a_vAxis),
    m_fLength(a_vAxis.norm()),
    m_fRadius(a_fRadius),
    m_qRotation(Quaternionf::FromTwoVectors(m_vAxis, Vector3f(0, 0, 1)))
{
    float diameter = 2.f * m_fRadius;
    BoundingBox leftCap = BoundingBox(this, m_vLocation, diameter, diameter, diameter);
    BoundingBox rightCap = BoundingBox(this, m_vLocation + m_vAxis, diameter, diameter, diameter);

    const Vector3f& leftTopRightForward = leftCap.TopRightForward();
    const Vector3f& leftBottomLeftBack = leftCap.BottomLeftBack();
    const Vector3f& rightTopRightForward = rightCap.TopRightForward();
    const Vector3f& rightBottomLeftBack = rightCap.BottomLeftBack();

    float maxX, maxY, maxZ, minX, minY, minZ;
    maxX = fabsf(std::max(leftTopRightForward.x(), rightTopRightForward.x()));
    minX = fabsf(std::max(leftBottomLeftBack.x(), rightBottomLeftBack.x()));

    maxY = fabsf(std::max(leftTopRightForward.y(), rightTopRightForward.y()));
    minY = fabsf(std::max(leftBottomLeftBack.y(), rightBottomLeftBack.y()));

    maxZ = fabsf(std::max(leftTopRightForward.z(), rightTopRightForward.z()));
    minZ = fabsf(std::max(leftBottomLeftBack.z(), rightBottomLeftBack.z()));

    if (maxX < minX) SwapValues(maxX, minX);
    if (maxY < minY) SwapValues(maxY, minY);
    if (maxZ < minZ) SwapValues(maxZ, minZ);

    float width = maxX - minX;
    float height = maxY - minY;
    float depth = maxZ - minZ;

    m_pBoundingBox = new BoundingBox(this, m_vLocation + (m_vAxis * 0.5f), width, height, depth);

    m_Slab = { 0.f, -m_fLength, Vector3f(0, 0, 1) };
}

Cylinder::~Cylinder()
{
}

bool Cylinder::Hit(const Ray & a_Ray, float a_fTMin, float a_fTMax, Intersection & a_Hit) const
{
    const Vector3f& S = a_Ray.Origin();
    const Vector3f& D = a_Ray.Direction();
    Vector3f Sprime = m_qRotation._transformVector(S - m_vLocation);
    Vector3f Dprime = m_qRotation._transformVector(D); // * t

    Interval slabInterval, cylinderInterval, finalInterval;

#pragma region Slab Interval
    slabInterval.m_vNormal0 = slabInterval.m_vNormal1 = Vector3f(0, 0, 1);

    float nDotD = m_Slab.m_vNormal.dot(D);
    float nDotS = m_Slab.m_vNormal.dot(S);
    float S0 = nDotS + m_Slab.m_fD0;
    float S1 = nDotS + m_Slab.m_fD1;
    if (nDotD != 0.f)
    {
        float t0 = -S0 / nDotD;
        float t1 = -S1 / nDotD;
        if (t0 > t1)
            SwapValues(t0, t1);

        slabInterval.m_fT0 = t0;
        slabInterval.m_fT1 = t1;
    }
    else if (AreSameSign(S0, S1))
    {
        // outside the planes planes
        slabInterval.m_fT0 = 1.f;
        slabInterval.m_fT1 = 0.f;
    }
#pragma endregion

#pragma region Cylinder Interval
    float a = D.x() * D.x() + D.y() * D.y();
    float b = D.x() * S.x() + D.y() * S.y();
    float c = S.x() * S.x() + S.y() * S.y() - (m_fRadius * m_fRadius);
    float sqrtInner = (b * b - 4.f * a * c);

    // Intersection possible
    if (sqrtInner >= 0.f)
    {
        float den = 2.f * a;

        float t0 = (-b + sqrtf(sqrtInner)) / den;
        float t1 = (-b - sqrtf(sqrtInner)) / den;

        if (t0 > t1)
            SwapValues(t0, t1);

        cylinderInterval.m_fT0 = t0;
        cylinderInterval.m_fT1 = t1;
    }
#pragma endregion

    //finalInterval.m_fT0 = std::max(std::max(0.f, slabInterval.m_fT0), cylinderInterval.m_fT0);
    //finalInterval.m_fT1 = std::max(std::min(FLT_MAX, slabInterval.m_fT1), cylinderInterval.m_fT1);

    if (slabInterval.m_fT0 != 1.f && slabInterval.m_fT1 != 0.f)
    {
        SetMinMaxInterval(finalInterval, slabInterval);
    }

    if (cylinderInterval.m_fT0 != 1.f && cylinderInterval.m_fT1 != 0.f)
    {
        SetMinMaxInterval(finalInterval, cylinderInterval);
    }

    if (finalInterval.m_fT0 > finalInterval.m_fT1)
        return false;

    // smallest positive t value
    if (SetIntersectionFromLowestPositive(a_Hit, finalInterval))
    {
        a_Hit.m_vPoint = a_Ray.PointAt(a_Hit.m_fT);
        a_Hit.m_Interval = finalInterval;
        a_Hit.m_pMaterial = m_pMaterial;
        return true;
    }
    return false;
}
