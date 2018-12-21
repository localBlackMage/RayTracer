#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
public:
    Material();
    ~Material();

    virtual bool Scatter(const Ray& a_RayIn, const HitData& a_HitData, Vec3& a_vAttentuation, Ray& a_RayOut) const = 0;
};

#endif //MATERIAL_H