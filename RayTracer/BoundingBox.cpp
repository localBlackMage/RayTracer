#include "stdafx.h"

#include "BoundingBox.h"

BoundingBox::BoundingBox(Shape* a_pOwner, const Vec3 & a_vCenter, float width, float height, float depth) :
    m_pOwningShape(a_pOwner),
    m_vCenter(a_vCenter),
    m_vTopRightForward(a_vCenter),
    m_vBottomLeftBack(a_vCenter)
{
    float halfWidth = width / 2.f;
    float halfHeight = height / 2.f;
    float halfDepth = depth / 2.f;

    m_vTopRightForward += Vec3(halfWidth, halfDepth, halfHeight);
    m_vBottomLeftBack -= Vec3(halfWidth, halfDepth, halfHeight);
}

BoundingBox::~BoundingBox()
{
}
