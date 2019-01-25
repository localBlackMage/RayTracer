#include "stdafx.h"

Metal::Metal(const Vec3 & a_Albedo, float a_fRoughness) :
    m_Albedo(a_Albedo),
    m_fRoughness(a_fRoughness)
{}

Metal::~Metal()
{}

bool Metal::Scatter(const Ray & a_RayIn, const Intersection & a_HitData, Vec3 & a_vAttentuation, Ray & a_RayOut) const
{
    Vec3 reflected = Reflect(Vec3::Normalize(a_RayIn.Direction()), a_HitData.m_vNormal);
    a_RayOut = Ray(a_HitData.m_vPoint, reflected + m_fRoughness * Rand_UnitSphere());
    a_vAttentuation = m_Albedo;
    return (Vec3::Dot(a_RayOut.Direction(), a_HitData.m_vNormal) > 0.f);
}
