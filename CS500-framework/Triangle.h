#pragma once

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle :
    public Shape
{
protected:
    VertexData m_vdA, m_vdB, m_vdC;
    Vector3f m_vEdge0, m_vEdge1;

    void CreateBoundingBox();

public:
    Triangle(const VertexData& a_vdA, const VertexData& a_vdB, const VertexData& a_vdC, Material* a_pMaterial);
    virtual ~Triangle();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
    virtual void GetRandomIntersectionPoint(Intersection& a_Intersection) const;
};

#endif //TRIANGLE_H