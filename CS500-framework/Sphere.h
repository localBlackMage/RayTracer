#pragma once

#ifndef SPHERE_H
#define SPHERE_H

class Sphere :
    public Shape
{
protected:
    Vector3f m_vCenter;
    float m_fRadius;

    virtual void CreateBoundingBox();

public:
    Sphere(Vector3f a_vCenter, float a_fRadius, Material* a_pMaterial);
    virtual ~Sphere();

    inline const Vector3f& Center() const { return m_vCenter; }
    inline float Radius() const { return m_fRadius; }

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

#endif //SPHERE_H