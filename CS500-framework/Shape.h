#pragma once

#ifndef SHAPE_H
#define SHAPE_H

class Material;

class Shape
{
protected:
    Material* m_pMaterial;
    Bbox m_BoundingBox;
    float m_fArea;

    virtual void CreateBoundingBox() = 0;

public:
    Shape(Material* a_pMaterial = nullptr, float a_fArea = 0.f);
    virtual ~Shape();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const = 0;
    Bbox GetBoundingBox() const { return m_BoundingBox; }
    virtual void GetRandomIntersectionPoint(Intersection& a_Intersection) const = 0;
    virtual float Area() const { return m_fArea; }
};

Bbox bounding_box(const Shape* obj);

#endif //SHAPE_H