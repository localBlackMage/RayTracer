#pragma once

#ifndef CYLLINDER_H
#define CYLLINDER_H

class Cyllinder :
    public Shape
{
protected:
    Vector3f m_vLocation;
    Vector3f m_vMiddle;
    float m_fLength;
    float m_fRadius;
    Quaternionf m_qRotation;

public:
    Cyllinder(const Vector3f& a_vLocation, float a_fLength, float a_fRadius, const Quaternionf& a_qRotation, Material* a_pMaterial);
    virtual ~Cyllinder();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

#endif //CYLLINDER_H