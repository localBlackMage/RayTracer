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
    float b = oc.dot(a_Ray.Direction());
    float c = oc.dot(oc) - m_fRadius * m_fRadius;
    float discriminant = b * b - a * c;

    if (discriminant > EPSILON)
    {
        float sqrtDisc = sqrtf(discriminant);
        float temp = (-b - sqrtDisc) / a;
        if (temp < a_fTMax && temp > a_fTMin)
        {
            a_Hit.m_fT = temp;
            a_Hit.m_vPoint = a_Ray.PointAt(temp);
            a_Hit.m_vNormal = (a_Hit.m_vPoint - m_vCenter) / m_fRadius;
            a_Hit.m_pMaterial = m_pMaterial;
            a_Hit.m_pShape = this;
            return true;
        }

        temp = (-b + sqrtDisc) / a;
        if (temp < a_fTMax && temp > a_fTMin)
        {
            a_Hit.m_fT = temp;
            a_Hit.m_vPoint = a_Ray.PointAt(temp);
            a_Hit.m_vNormal = (a_Hit.m_vPoint - m_vCenter) / m_fRadius;
            a_Hit.m_pMaterial = m_pMaterial;
            a_Hit.m_pShape = this;
            return true;
        }
    }
    return false;
}

void Sphere::GetRandomIntersectionPoint(Intersection & a_Intersection) const
{
    float a = MersenneRandFloat();
    float b = MersenneRandFloat();
    float z = 2.f * a - 1.f;
    float r = sqrtf(1.f - z * z);
    float c = PI_2 * b;

    a_Intersection.m_vNormal = Vector3f(r * cosf(c), r * sinf(c), z).normalized();
    a_Intersection.m_vPoint = m_vCenter + m_fRadius * a_Intersection.m_vNormal;
    a_Intersection.m_pShape = this;
    a_Intersection.m_pMaterial = m_pMaterial;
}
