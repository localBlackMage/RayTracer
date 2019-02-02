#pragma once

#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

class Lambertian :
    public Material
{
protected:

public:
    Lambertian(const Vector3f& a_Albedo);
    ~Lambertian();

    virtual bool Scatter(const Ray& a_RayIn, const Intersection& a_HitData, Vector3f& a_vAttentuation, Ray& a_RayOut) const;
};

#endif //LAMBERTIAN_H