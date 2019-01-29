#include "stdafx.h"
#include "Cyllinder.h"

Cyllinder::Cyllinder(const Vec3 & a_vLocation, float a_fLength, float a_fRadius, const Quaternion & a_qRotation, Material * a_pMaterial) :
    Shape(a_pMaterial),
    m_vLocation(a_vLocation),
    m_vMiddle(a_qRotation.RotateVector(Vec3(0, 0, 1) * a_fLength)),
    m_fLength(a_fLength),
    m_fRadius(a_fRadius),
    m_qRotation(a_qRotation)
{
    float diameter = 2.f * m_fRadius;
    BoundingBox leftCap = BoundingBox(this, m_vLocation, diameter, diameter, diameter);
    BoundingBox rightCap = BoundingBox(this, m_vLocation + m_vMiddle, diameter, diameter, diameter);

    const Vec3& leftTopRightForward = leftCap.TopRightForward();
    const Vec3& leftBottomLeftBack = leftCap.BottomLeftBack();
    const Vec3& rightTopRightForward = rightCap.TopRightForward();
    const Vec3& rightBottomLeftBack = rightCap.BottomLeftBack();

    float maxX, maxY, maxZ, minX, minY, minZ;
    maxX = fabsf(std::max(leftTopRightForward.x, rightTopRightForward.x));
    minX = fabsf(std::max(leftBottomLeftBack.x, rightBottomLeftBack.x));

    maxY = fabsf(std::max(leftTopRightForward.y, rightTopRightForward.y));
    minY = fabsf(std::max(leftBottomLeftBack.y, rightBottomLeftBack.y));

    maxZ = fabsf(std::max(leftTopRightForward.z, rightTopRightForward.z));
    minZ = fabsf(std::max(leftBottomLeftBack.z, rightBottomLeftBack.z));

    if (maxX < minX) SwapValues(maxX, minX);
    if (maxY < minY) SwapValues(maxY, minY);
    if (maxZ < minZ) SwapValues(maxZ, minZ);

    float width = maxX - minX;
    float height = maxY - minY;
    float depth = maxZ - minZ;

    m_pBoundingBox = new BoundingBox(this, m_vLocation + (m_vMiddle * 0.5f), width, height, depth);
}

Cyllinder::~Cyllinder()
{
}

bool Cyllinder::Hit(const Ray & a_Ray, float a_fTMin, float a_fTMax, Intersection & a_Hit) const
{
    const Vec3& S = a_Ray.Origin();
    const Vec3& D = a_Ray.Direction();
    Vec3 Sprime = m_qRotation.RotateVector(S - m_vLocation);
    Vec3 Dprime = m_qRotation.RotateVector(D);

    Interval i;

    return false;
}
