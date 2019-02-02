#pragma once

#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

class Shape;

class BoundingBox
{
protected:
    Vector3f m_vCenter, m_vTopRightForward, m_vBottomLeftBack;
    Shape* m_pOwningShape;

public:
    BoundingBox(Shape* a_pOwner, const Vector3f& a_vCenter, float width, float height, float depth);
    virtual ~BoundingBox();

    const Vector3f& Center() const { return m_vCenter; }
    const Vector3f& TopRightForward() const { return m_vTopRightForward; }
    const Vector3f& BottomLeftBack() const { return m_vBottomLeftBack; }
};

#endif //BOUNDING_BOX_H