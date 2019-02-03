#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

enum eMaterialType : uint32
{
    eMaterialType_Lambertian = 0,
    eMaterialType_Metal
};

class Material
{
public:
    Vector3f Kd, Ks;
    float alpha;
    unsigned int texid;
    eMaterialType eMatType;
    bool m_bIsLight;

    virtual bool isLight() { return false; }

    Material() : 
        Kd(Vector3f(1.0, 0.5, 0.0)), 
        Ks(Vector3f(1, 1, 1)), 
        alpha(1.0), 
        texid(0),
        eMatType(eMaterialType_Lambertian),
        m_bIsLight(false)
    {}
    Material(const Vector3f d, const Vector3f s, const float a, eMaterialType a_eMatType = eMaterialType_Lambertian, bool a_bIsLight = false) :
        Kd(d), Ks(s), alpha(a), texid(0),
        eMatType(a_eMatType),
        m_bIsLight(a_bIsLight)
    {}
    Material(Material& o) { Kd = o.Kd;  Ks = o.Ks;  alpha = o.alpha;  texid = o.texid; eMatType = o.eMatType; m_bIsLight = o.m_bIsLight; }
    virtual ~Material() {};

    void setTexture(const std::string path);
    //virtual void apply(const unsigned int program);

    bool Scatter(const Ray& a_RayIn, const Intersection& a_HitData, Vector3f& a_vAttentuation, Ray& a_RayOut) const;
};

////////////////////////////////////////////////////////////////////////
// Light: encapsulates a light and communiction with a shader.
////////////////////////////////////////////////////////////////////////
class Light : public Material
{
public:

    Light(const Vector3f e) : Material() { Kd = e; }
    virtual bool isLight() { return true; }
    //virtual void apply(const unsigned int program);
};

#endif //MATERIAL_H