#pragma once

#ifndef SHAPE_H
#define SHAPE_H

class Material;

class Shape
{
protected:
    Material* m_pMaterial;
    Bbox m_BoundingBox;

    virtual void CreateBoundingBox() = 0;

public:
    Shape(Material* a_pMaterial = nullptr);
    virtual ~Shape();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const = 0;
    Bbox GetBoundingBox() const { return m_BoundingBox; }
};

Bbox bounding_box(const Shape* obj);

#endif //SHAPE_H