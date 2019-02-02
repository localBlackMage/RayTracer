#include "stdafx.h"

Metal::Metal(const Vector3f & a_Albedo, float a_fRoughness) :
    Material(a_Albedo, Vector3f(1, 1, 1), 1.f),
    m_fRoughness(a_fRoughness)
{}

Metal::~Metal()
{}

bool Metal::Scatter(const Ray & a_RayIn, const Intersection & a_HitData, Vector3f & a_vAttentuation, Ray & a_RayOut) const
{
    Vector3f reflected = Reflect(a_RayIn.Direction().normalized(), a_HitData.m_vNormal);
    a_RayOut = Ray(a_HitData.m_vPoint, reflected + m_fRoughness * Rand_UnitSphere());
    a_vAttentuation = Kd;
    return (a_RayOut.Direction().dot(a_HitData.m_vNormal) > 0.f);
}
