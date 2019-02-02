#include "stdafx.h"

//#include "BoundingBox.h"

Triangle::Triangle(Vector3f a_vA, Vector3f a_vB, Vector3f a_vC, Vector3f a_vNormalA, Vector3f a_vNormalB, Vector3f a_vNormalC, Material * a_pMaterial) :
    Shape (a_pMaterial),
    m_vA(a_vA),
    m_vB(a_vB),
    m_vC(a_vC),
    m_vNormalA(a_vNormalA),
    m_vNormalB(a_vNormalB),
    m_vNormalC(a_vNormalC),
    m_vEdge0(a_vB - a_vA),
    m_vEdge1(a_vC - a_vA)
{
    float maxX, maxY, maxZ, minX, minY, minZ;
    maxX = fabsf(std::max(std::max(a_vA.x(), a_vB.x()), a_vC.x()));
    maxY = fabsf(std::max(std::max(a_vA.y(), a_vB.y()), a_vC.y()));
    maxZ = fabsf(std::max(std::max(a_vA.z(), a_vB.z()), a_vC.z()));

    minX = fabsf(std::min(std::min(a_vA.x(), a_vB.x()), a_vC.x()));
    minY = fabsf(std::min(std::min(a_vA.y(), a_vB.y()), a_vC.y()));
    minZ = fabsf(std::min(std::min(a_vA.z(), a_vB.z()), a_vC.z()));

    if (maxX < minX) SwapValues(maxX, minX);
    if (maxY < minY) SwapValues(maxY, minY);
    if (maxZ < minZ) SwapValues(maxZ, minZ);

    m_pBoundingBox = new BoundingBox(this, (a_vA + a_vB + a_vC) / 3.f, maxX - minX, maxY - minY, maxZ - minZ);
}

Triangle::~Triangle()
{
}

bool Triangle::Hit(const Ray & a_Ray, float a_fTMin, float a_fTMax, Intersection & a_Hit) const
{
    const Vector3f& D = a_Ray.Direction();

    float det = D.cross(m_vEdge1).dot(m_vEdge0);
    if (det == 0)
        return false; // parallel, no intersection

    const Vector3f& S = a_Ray.Origin();
    Vector3f NegD = D * -1.f;
    Vector3f Q = S - m_vA;

    float t = Q.cross(m_vEdge0).dot(m_vEdge1) / det;
    float alpha = D.cross(m_vEdge1).dot(Q) / det;

    if (alpha < 0.f || alpha > 1.f)
        return false; // no intersection, outside this tri

    float beta =    Q.cross(m_vEdge0).dot(D) / det;

    if (beta < 0.f || (alpha + beta) > 1.f)
        return false; // no intersection, outside this tri

    a_Hit.m_vPoint = a_Ray.PointAt(t);
    a_Hit.m_vNormal = (1.f - alpha - beta) * m_vNormalA + alpha * m_vNormalB + beta * m_vNormalC;
    a_Hit.m_fT = t;
    a_Hit.m_pMaterial = m_pMaterial;

    return true;
}
