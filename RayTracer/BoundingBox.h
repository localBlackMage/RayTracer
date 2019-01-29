#pragma once

#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

class Shape;

class BoundingBox
{
protected:
    Vec3 m_vCenter, m_vTopRightForward, m_vBottomLeftBack;
    Shape* m_pOwningShape;

public:
    BoundingBox(Shape* a_pOwner, const Vec3& a_vCenter, float width, float height, float depth);
    virtual ~BoundingBox();

    const Vec3& Center() const { return m_vCenter; }
    const Vec3& TopRightForward() const { return m_vTopRightForward; }
    const Vec3& BottomLeftBack() const { return m_vBottomLeftBack; }
};

#endif //BOUNDING_BOX_H