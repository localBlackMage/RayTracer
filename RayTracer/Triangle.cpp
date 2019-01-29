#include "stdafx.h"

//#include "BoundingBox.h"

Triangle::Triangle(Vec3 a_vA, Vec3 a_vB, Vec3 a_vC, Vec3 a_vNormalA, Vec3 a_vNormalB, Vec3 a_vNormalC, Material * a_pMaterial) :
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
    maxX = fabsf(std::max(std::max(a_vA.x, a_vB.x), a_vC.x));
    maxY = fabsf(std::max(std::max(a_vA.y, a_vB.y), a_vC.y));
    maxZ = fabsf(std::max(std::max(a_vA.z, a_vB.z), a_vC.z));

    minX = fabsf(std::min(std::min(a_vA.x, a_vB.x), a_vC.x));
    minY = fabsf(std::min(std::min(a_vA.y, a_vB.y), a_vC.y));
    minZ = fabsf(std::min(std::min(a_vA.z, a_vB.z), a_vC.z));

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
    const Vec3& D = a_Ray.Direction();

    //float det =     Matrix3x3::Determinant(Matrix3x3(NegD, m_vEdge0, m_vEdge1));
    float det =     Vec3::Dot(Vec3::Cross(D, m_vEdge1), m_vEdge0);
    if (det == 0)
        return false; // parallel, no intersection

    const Vec3& S = a_Ray.Origin();
    Vec3 NegD = D * -1.f;
    Vec3 Q = S - m_vA;

    float t =       Vec3::Dot(Vec3::Cross(Q, m_vEdge0), m_vEdge1) / det;
    float alpha =   Vec3::Dot(Vec3::Cross(D, m_vEdge1), Q) / det;

    if (alpha < 0.f || alpha > 1.f)
        return false; // no intersection, outside this tri

    float beta =    Vec3::Dot(Vec3::Cross(Q, m_vEdge0), D) / det;

    if (beta < 0.f || (alpha + beta) > 1.f)
        return false; // no intersection, outside this tri
    
    //float t =       Matrix3x3::Determinant(Matrix3x3(S, m_vEdge0, m_vEdge1)) / det;
    //float alpha =   Matrix3x3::Determinant(Matrix3x3(NegD, S, m_vEdge1)) / det;
    //float beta =    Matrix3x3::Determinant(Matrix3x3(NegD, m_vEdge0, S)) / det;

    a_Hit.m_vPoint = a_Ray.PointAt(t);
    a_Hit.m_vNormal = (1.f - alpha - beta) * m_vNormalA + alpha * m_vNormalB + beta * m_vNormalC;
    a_Hit.m_fT = t;
    a_Hit.m_pMaterial = m_pMaterial;

    return true;
}
