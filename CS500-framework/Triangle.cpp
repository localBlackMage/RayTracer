#include "stdafx.h"

void Triangle::CreateBoundingBox()
{
    float maxX, maxY, maxZ, minX, minY, minZ;
    maxX = std::max(std::max(m_vdA.pnt.x(), m_vdB.pnt.x()), m_vdC.pnt.x());
    maxY = std::max(std::max(m_vdA.pnt.y(), m_vdB.pnt.y()), m_vdC.pnt.y());
    maxZ = std::max(std::max(m_vdA.pnt.z(), m_vdB.pnt.z()), m_vdC.pnt.z());

    minX = std::min(std::min(m_vdA.pnt.x(), m_vdB.pnt.x()), m_vdC.pnt.x());
    minY = std::min(std::min(m_vdA.pnt.y(), m_vdB.pnt.y()), m_vdC.pnt.y());
    minZ = std::min(std::min(m_vdA.pnt.z(), m_vdB.pnt.z()), m_vdC.pnt.z());

    if (maxX < minX) SwapValues(maxX, minX);
    if (maxY < minY) SwapValues(maxY, minY);
    if (maxZ < minZ) SwapValues(maxZ, minZ);
    
    m_BoundingBox = Bbox(Vector3f(minX, minY, minZ), Vector3f(maxX, maxY, maxZ));
}

Triangle::Triangle(const VertexData& a_vdA, const VertexData& a_vdB, const VertexData& a_vdC, Material * a_pMaterial) :
    Shape(a_pMaterial),
    m_vdA(a_vdA),
    m_vdB(a_vdB),
    m_vdC(a_vdC),
    m_vEdge0(a_vdB.pnt - a_vdA.pnt),
    m_vEdge1(a_vdC.pnt - a_vdA.pnt)
{
    CreateBoundingBox();
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
    Vector3f Q = S - m_vdA.pnt;

    float t = Q.cross(m_vEdge0).dot(m_vEdge1) / det;
    float alpha = D.cross(m_vEdge1).dot(Q) / det;

    if (alpha < 0.f || alpha > 1.f)
        return false; // no intersection, outside this tri

    float beta =    Q.cross(m_vEdge0).dot(D) / det;

    if (beta < 0.f || (alpha + beta) > 1.f)
        return false; // no intersection, outside this tri

    if (t < a_fTMax && t > a_fTMin)
    {
        a_Hit.m_vPoint = a_Ray.PointAt(t);
        a_Hit.m_vNormal = ((1.f - alpha - beta) * m_vdA.nrm + alpha * m_vdB.nrm + beta * m_vdC.nrm).normalized();
        a_Hit.m_fT = t;
        a_Hit.m_pMaterial = m_pMaterial;
        return true;
    }

    return false;
}
