#pragma once

#ifndef CYLLINDER_H
#define CYLLINDER_H

class Cyllinder :
    public Shape
{
protected:
    Vec3 m_vLocation;
    Vec3 m_vMiddle;
    float m_fLength;
    float m_fRadius;
    Quaternion m_qRotation;

public:
    Cyllinder(const Vec3& a_vLocation, float a_fLength, float a_fRadius, const Quaternion& a_qRotation, Material* a_pMaterial);
    virtual ~Cyllinder();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

#endif //CYLLINDER_H