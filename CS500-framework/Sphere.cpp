#include "stdafx.h"

void Sphere::CreateBoundingBox()
{
    Vector3f diag = Vector3f(m_fRadius, m_fRadius, m_fRadius);
    m_BoundingBox = Bbox(m_vCenter - diag, m_vCenter + diag);
}

Sphere::Sphere(Vector3f a_vCenter, float a_fRadius, Material* a_pMaterial) :
    Shape(a_pMaterial, 4.f * PI * (a_fRadius * a_fRadius)),
    m_vCenter(a_vCenter),
    m_fRadius(a_fRadius)
{
    CreateBoundingBox();
}

Sphere::~Sphere()
{}

bool Sphere::Hit(const Ray & a_Ray, float a_fTMin, float a_fTMax, Intersection & a_Hit) const
{
    Vector3f oc = a_Ray.Origin() - m_vCenter;
    float a = a_Ray.Direction().dot(a_Ray.Direction());
    float b = 2.f * oc.dot(a_Ray.Direction());
    float c = oc.dot(oc) - m_fRadius * m_fRadius;
    float discriminant = b * b - (4 * a * c);

    if (discriminant < EPSILON)
        return false;
    else
    {
        float sqrtDisc = sqrtf(discriminant);
        float t1 = (-b - sqrtDisc) / (2.f * a);
        float t2 = (-b + sqrtDisc) / (2.f * a);

        if (t1 < EPSILON && t2 < EPSILON)
            return false;

        if (t1 < 0 || t2 < 0)
            a_Hit.m_fT = std::max(t1, t2);
        else
            a_Hit.m_fT = std::min(t1, t2);

        a_Hit.m_vPoint = a_Ray.PointAt(a_Hit.m_fT);
        a_Hit.m_vNormal = (a_Hit.m_vPoint - m_vCenter).normalized();
        a_Hit.m_pMaterial = m_pMaterial;
        a_Hit.m_pShape = this;
        return true;
    }
    return false;
}

void Sphere::GetRandomIntersectionPoint(Intersection & a_Intersection) const
{
    float Xi1 = MersenneRandFloat();
    float Xi2 = MersenneRandFloat();

    float z = 2 * Xi1 - 1;
    float r = sqrt(1 - (z*z));
    float a = 2 * PI*Xi2;

    a_Intersection.m_vNormal = Vector3f(r*cos(a), r*sin(a), z).normalized();
    a_Intersection.m_vPoint = m_vCenter + (m_fRadius * a_Intersection.m_vNormal);
    a_Intersection.m_pShape = this;
    a_Intersection.m_pMaterial = m_pMaterial;
}
