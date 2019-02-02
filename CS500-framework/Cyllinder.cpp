#include "stdafx.h"
#include "Cyllinder.h"

Cyllinder::Cyllinder(const Vector3f & a_vLocation, float a_fLength, float a_fRadius, const Quaternionf & a_qRotation, Material * a_pMaterial) :
    Shape(a_pMaterial),
    m_vLocation(a_vLocation),
    m_vMiddle(a_qRotation._transformVector(Vector3f(0, 0, 1) * a_fLength)),
    m_fLength(a_fLength),
    m_fRadius(a_fRadius),
    m_qRotation(a_qRotation)
{
    float diameter = 2.f * m_fRadius;
    BoundingBox leftCap = BoundingBox(this, m_vLocation, diameter, diameter, diameter);
    BoundingBox rightCap = BoundingBox(this, m_vLocation + m_vMiddle, diameter, diameter, diameter);

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

    m_pBoundingBox = new BoundingBox(this, m_vLocation + (m_vMiddle * 0.5f), width, height, depth);
}

Cyllinder::~Cyllinder()
{
}

bool Cyllinder::Hit(const Ray & a_Ray, float a_fTMin, float a_fTMax, Intersection & a_Hit) const
{
    const Vector3f& S = a_Ray.Origin();
    const Vector3f& D = a_Ray.Direction();
    Vector3f Sprime = m_qRotation._transformVector(S - m_vLocation);
    Vector3f Dprime = m_qRotation._transformVector(D);

    Interval i;

    return false;
}
