#include "stdafx.h"

Lambertian::Lambertian(const Vector3f & a_Albedo) : 
    Material(a_Albedo, Vector3f(1, 1, 1), 1.f)
{}

Lambertian::~Lambertian()
{}

bool Lambertian::Scatter(const Ray & a_RayIn, const Intersection & a_HitData, Vector3f & a_vAttentuation, Ray & a_RayOut) const
{
    Vector3f target = a_HitData.m_vPoint + a_HitData.m_vNormal + Rand_UnitSphere();
    a_RayOut = Ray(a_HitData.m_vPoint, target - a_HitData.m_vPoint);
    a_vAttentuation = Kd;
    return true;
}
