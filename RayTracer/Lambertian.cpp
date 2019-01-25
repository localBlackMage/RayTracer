#include "stdafx.h"

Lambertian::Lambertian(const Vec3 & a_Albedo) : 
    m_Albedo(a_Albedo)
{}

Lambertian::~Lambertian()
{}

bool Lambertian::Scatter(const Ray & a_RayIn, const Intersection & a_HitData, Vec3 & a_vAttentuation, Ray & a_RayOut) const
{
    Vec3 target = a_HitData.m_vPoint + a_HitData.m_vNormal + Rand_UnitSphere();
    a_RayOut = Ray(a_HitData.m_vPoint, target - a_HitData.m_vPoint);
    a_vAttentuation = m_Albedo;
    return true;
}
