#pragma once

#ifndef SHAPE_H
#define SHAPE_H

class Material;

class Shape
{
protected:
    Material* m_pMaterial;

public:
    Shape(Material* a_pMaterial = nullptr);
    virtual ~Shape();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const = 0;
};

#endif //SHAPE_H