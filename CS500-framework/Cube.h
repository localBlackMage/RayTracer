#pragma once

#ifndef CUBE_H
#define CUBE_H

class Cube :
    public Shape
{
protected:
    Vector3f m_vCenter;
    RTSlab m_Slabs[3];

    virtual void CreateBoundingBox();

public:
    Cube(Material* a_pMaterial) : Shape(a_pMaterial) {}
    Cube(Vector3f a_vCenter, float a_fWidth, float a_fHeight, float a_fDepth, Quaternionf a_qRotation, Material* a_pMaterial);
    virtual ~Cube();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

class AACube : public Cube
{
protected:
    Vector3f m_vCorner, m_vDiagonal;

    virtual void CreateBoundingBox();

public:
    AACube(Vector3f a_vCorner, Vector3f a_vDiagonal, Material* a_pMaterial);
    virtual ~AACube();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

#endif //CUBE_H

