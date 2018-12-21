#pragma once

#ifndef METAL_H
#define METAL_H

class Metal :
    public Material
{
protected:
    Vec3 m_Albedo;
    float m_fRoughness;

public:
    Metal(const Vec3& a_Albedo, float a_fRoughness);
    ~Metal();

    virtual bool Scatter(const Ray& a_RayIn, const HitData& a_HitData, Vec3& a_vAttentuation, Ray& a_RayOut) const;
};

#endif //#define METAL_H
