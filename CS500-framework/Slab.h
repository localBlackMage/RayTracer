#pragma once

#ifndef SLAB_H
#define SLAB_H

class Slab :
    public Shape
{
protected:
    Vector3f m_vCenter;
    float m_fWidth;
    float m_fHalfWidth; // d0 and d1
    Vector3f m_vNormal;

public:
    Slab(Vector3f a_vCenter, float a_fWidth, Quaternionf a_qRotation, Material* a_pMaterial);
    virtual ~Slab();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

struct RTSlab {
    float m_fD0;
    float m_fD1;
    Vector3f m_vNormal;
};

#endif //SLAB_H