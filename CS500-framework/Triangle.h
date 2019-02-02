#pragma once

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle :
    public Shape
{
protected:
    Vector3f m_vA, m_vB, m_vC;
    Vector3f m_vNormalA, m_vNormalB, m_vNormalC;
    Vector3f m_vEdge0, m_vEdge1;

public:
    Triangle(Vector3f a_vA, Vector3f a_vB, Vector3f a_vC, Vector3f a_vNormalA, Vector3f a_vNormalB, Vector3f a_vNormalC, Material* a_pMaterial);
    virtual ~Triangle();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

#endif //TRIANGLE_H