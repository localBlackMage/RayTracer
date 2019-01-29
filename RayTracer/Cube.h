#pragma once

#ifndef CUBE_H
#define CUBE_H

class Cube :
    public Shape
{
protected:
    struct CubeSlab {
        float m_fD0;
        float m_fD1;
        Vec3 m_vNormal;
    };

    Vec3 m_vCenter;
    //Slab* m_pSlabA, *m_pSlabB, *m_pSlabC;
    CubeSlab m_Slabs[3];

public:
    Cube(Material* a_pMaterial) : Shape(a_pMaterial) {}
    Cube(Vec3 a_vCenter, float a_fWidth, float a_fHeight, float a_fDepth, Quaternion a_qRotation, Material* a_pMaterial);
    virtual ~Cube();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

class AABCube : public Cube
{
protected:
    Vec3 m_vCorner, m_vDiagonal;

public:
    AABCube(Vec3 a_vCorner, Vec3 a_vDiagonal, Material* a_pMaterial);
    virtual ~AABCube();

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

#endif //CUBE_H

