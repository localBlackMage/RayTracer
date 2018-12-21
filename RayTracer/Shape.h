#pragma once

#ifndef SHAPE_H
#define SHAPE_H

class Material;

struct HitData
{
    float m_fT;
    Vec3 m_vPoint;
    Vec3 m_vNormal;
    Material* m_pMaterial;
};

class Shape
{
protected:
    Material* m_pMaterial;

public:
    Shape(Material* a_pMaterial = nullptr);
    virtual ~Shape();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, HitData& a_Hit) const = 0;
};

#endif //SHAPE_H