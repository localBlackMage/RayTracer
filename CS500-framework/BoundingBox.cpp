#include "stdafx.h"

#include "BoundingBox.h"

BoundingBox::BoundingBox(Shape* a_pOwner, const Vector3f & a_vCenter, float width, float height, float depth) :
    m_pOwningShape(a_pOwner),
    m_vCenter(a_vCenter),
    m_vTopRightForward(a_vCenter),
    m_vBottomLeftBack(a_vCenter)
{
    float halfWidth = width / 2.f;
    float halfHeight = height / 2.f;
    float halfDepth = depth / 2.f;

    m_vTopRightForward += Vector3f(halfWidth, halfDepth, halfHeight);
    m_vBottomLeftBack -= Vector3f(halfWidth, halfDepth, halfHeight);
}

BoundingBox::~BoundingBox()
{
}
