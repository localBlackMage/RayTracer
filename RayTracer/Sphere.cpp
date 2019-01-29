#include "stdafx.h"

Sphere::Sphere(Vec3 a_vCenter, float a_fRadius, Material* a_pMaterial) :
    Shape(a_pMaterial),
    m_vCenter(a_vCenter),
    m_fRadius(a_fRadius)
{
    float diameter = 2.f * m_fRadius;
    m_pBoundingBox = new BoundingBox(this, m_vCenter, diameter, diameter, diameter);
}

Sphere::~Sphere()
{}

bool Sphere::Hit(const Ray & a_Ray, float a_fTMin, float a_fTMax, Intersection & a_Hit) const
{
    Vec3 oc = a_Ray.Origin() - m_vCenter;
    float a = Vec3::Dot(a_Ray.Direction(), a_Ray.Direction());
    float b = Vec3::Dot(oc, a_Ray.Direction());
    float c = Vec3::Dot(oc, oc) - m_fRadius * m_fRadius;
    float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        float sqrtDisc = sqrtf(discriminant);
        float temp = (-b - sqrtDisc) / a;
        if (temp < a_fTMax && temp > a_fTMin)
        {
            a_Hit.m_fT = temp;
            a_Hit.m_vPoint = a_Ray.PointAt(temp);
            a_Hit.m_vNormal = (a_Hit.m_vPoint - m_vCenter) / m_fRadius;
            a_Hit.m_pMaterial = m_pMaterial;
            return true;
        }

        temp = (-b + sqrtDisc) / a;
        if (temp < a_fTMax && temp > a_fTMin)
        {
            a_Hit.m_fT = temp;
            a_Hit.m_vPoint = a_Ray.PointAt(temp);
            a_Hit.m_vNormal = (a_Hit.m_vPoint - m_vCenter) / m_fRadius;
            a_Hit.m_pMaterial = m_pMaterial;
            return true;
        }
    }
    return false;
}
