#pragma once

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle :
    public Shape
{
protected:
    Vec3 m_vA, m_vB, m_vC;
    Vec3 m_vNormalA, m_vNormalB, m_vNormalC;
    Vec3 m_vEdge0, m_vEdge1;

public:
    Triangle(Vec3 a_vA, Vec3 a_vB, Vec3 a_vC, Vec3 a_vNormalA, Vec3 a_vNormalB, Vec3 a_vNormalC, Material* a_pMaterial);
    virtual ~Triangle();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

#endif //TRIANGLE_H