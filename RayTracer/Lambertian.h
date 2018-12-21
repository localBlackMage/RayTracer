#pragma once

#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

class Lambertian :
    public Material
{
protected:
    Vec3 m_Albedo;

public:
    Lambertian(const Vec3& a_Albedo);
    ~Lambertian();

    virtual bool Scatter(const Ray& a_RayIn, const HitData& a_HitData, Vec3& a_vAttentuation, Ray& a_RayOut) const;
};

#endif //LAMBERTIAN_H