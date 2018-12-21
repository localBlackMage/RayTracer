#pragma once

#ifndef SPHERE_H
#define SPHERE_H

class Sphere :
    public Shape
{
protected:
    Vec3 m_vCenter;
    float m_fRadius;

public:
    Sphere(Vec3 a_vCenter, float a_fRadius, Material* a_pMaterial);
    virtual ~Sphere();

    inline const Vec3& Center() const { return m_vCenter; }
    inline float Radius() const { return m_fRadius; }

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, HitData& a_Hit) const;
};

#endif //SPHERE_H