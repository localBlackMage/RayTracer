#pragma once

#ifndef METAL_H
#define METAL_H

class Metal :
    public Material
{
protected:
    float m_fRoughness;

public:
    Metal(const Vector3f& a_Albedo, float a_fRoughness);
    ~Metal();

    virtual bool Scatter(const Ray& a_RayIn, const Intersection& a_HitData, Vector3f& a_vAttentuation, Ray& a_RayOut) const;
};

#endif //#define METAL_H
