#include "stdafx.h"

void Cylinder::CreateBoundingBox()
{
    Vector3f diag = Vector3f(m_fRadius, m_fRadius, m_fRadius);
    Bbox aBox = Bbox(m_vLocation + m_vAxis - diag, m_vLocation + m_vAxis + diag);
    Bbox bBox = Bbox(m_vLocation - diag, m_vLocation + diag);

    Vector3f aL = aBox.min();
    Vector3f aU = aBox.max();
    Vector3f bL = bBox.min();
    Vector3f bU = bBox.max();

    float minX = std::min(aL.x(), bL.x());
    float minY = std::min(aL.y(), bL.y());
    float minZ = std::min(aL.z(), bL.z());

    float maxX = std::max(aU.x(), bU.x());
    float maxY = std::max(aU.y(), bU.y());
    float maxZ = std::max(aU.z(), bU.z());

    m_BoundingBox = Bbox(Vector3f(minX, minY, minZ), Vector3f(maxX, maxY, maxZ));
}

Cylinder::Cylinder(const Vector3f & a_vLocation, const Vector3f& a_vAxis, float a_fRadius, Material * a_pMaterial) :
    Shape(a_pMaterial),
    m_vLocation(a_vLocation),
    m_vAxis(a_vAxis),
    m_fLength(a_vAxis.norm()),
    m_fRadius(a_fRadius),
    m_qRotation(Quaternionf::FromTwoVectors(m_vAxis, Vector3f::UnitZ()).normalized())
{
    m_Slab = { 0.f, -m_fLength, Vector3f(0, 0, 1) };
    CreateBoundingBox();
}

Cylinder::~Cylinder()
{
}

bool Cylinder::Hit(const Ray & a_Ray, float a_fTMin, float a_fTMax, Intersection & a_Hit) const
{
    const Vector3f Sprime = m_qRotation._transformVector(a_Ray.Origin() - m_vLocation);
    const Vector3f Dprime = m_qRotation._transformVector(a_Ray.Direction()); // * t

    Interval slabInterval, cylinderInterval, finalInterval;

#pragma region Slab Interval
    slabInterval.m_vNormal0 = Vector3f(0, 0, 1);
    slabInterval.m_vNormal1 = Vector3f(0, 0, -1);

    float nDotD = m_Slab.m_vNormal.dot(Dprime);
    float nDotS = m_Slab.m_vNormal.dot(Sprime);
    float S0 = nDotS + m_Slab.m_fD0;
    float S1 = nDotS + m_Slab.m_fD1;
    if (nDotD != 0.f)
    {
        float t0 = -S0 / nDotD;
        float t1 = -S1 / nDotD;
        if (t0 > t1)
        {
            SwapValues(t0, t1);
            slabInterval.m_vNormal0 = Vector3f(0, 0, -1);
            slabInterval.m_vNormal1 = Vector3f(0, 0, 1);
        }

        slabInterval.m_fT0 = t0;
        slabInterval.m_fT1 = t1;
        slabInterval.m_vNormal0 = m_qRotation.conjugate()._transformVector(slabInterval.m_vNormal0);
        slabInterval.m_vNormal1 = m_qRotation.conjugate()._transformVector(slabInterval.m_vNormal1);
    }
    else if (AreSameSign(S0, S1))
    {
        // outside the planes planes
        slabInterval.m_fT0 = 1.f;
        slabInterval.m_fT1 = 0.f;
    }
#pragma endregion

#pragma region Cylinder Interval
    float a = Dprime.x() * Dprime.x() + Dprime.y() * Dprime.y();
    float b = 2.f * (Dprime.x() * Sprime.x() + Dprime.y() * Sprime.y());
    float c = Sprime.x() * Sprime.x() + Sprime.y() * Sprime.y() - (m_fRadius * m_fRadius);
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

        cylinderInterval.m_vNormal0 = Sprime + t0 * Dprime;
        cylinderInterval.m_vNormal0.z() = 0;
        cylinderInterval.m_vNormal0.normalize();
        cylinderInterval.m_vNormal0 = m_qRotation.conjugate()._transformVector(cylinderInterval.m_vNormal0);

        cylinderInterval.m_vNormal1 = Sprime + t1 * Dprime;
        cylinderInterval.m_vNormal1.z() = 0;
        cylinderInterval.m_vNormal1.normalize();
        cylinderInterval.m_vNormal1 = m_qRotation.conjugate()._transformVector(cylinderInterval.m_vNormal1);
    }
    else
        return false;
#pragma endregion

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
    LowestPostiveIntersection lpi = FindLowestPositive(a_fTMin, a_fTMax, finalInterval);
    if (lpi.m_bDidIntersect)
    {
        a_Hit.m_fT = lpi.m_fT;
        a_Hit.m_vNormal = lpi.m_vNormal;
        a_Hit.m_vPoint = a_Ray.PointAt(a_Hit.m_fT);
        a_Hit.m_Interval = finalInterval;
        a_Hit.m_pMaterial = m_pMaterial;
        return true;
    }
    return false;
}
