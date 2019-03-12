#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

enum eMaterialType : uint32
{
    eMaterialType_Lambertian = 0,
    eMaterialType_Metal,

    eMaterialType_MAX
};

class Material
{
protected:
    Color LambertianScatter(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal, const Vector3f& a_vOmegaI);
    Color MetalScatter(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal, const Vector3f& a_vOmegaI);

    Color(Material::*m_pScatterFunctions[eMaterialType_MAX])(const Vector3f &, const Vector3f &, const Vector3f &);

    float Pd, Pr, S, m_fRoughnessExponent;

    void Initialize();
public:
    Color Kd, Ks;
    float alpha;
    unsigned int texid;
    eMaterialType eMatType;
    bool m_bIsLight;

    virtual bool isLight() { return false; }

    Material() : 
        Kd(Color(1.0, 0.5, 0.0)), 
        Ks(Color(1, 1, 1)),
        alpha(1.0), 
        texid(0),
        eMatType(eMaterialType_Lambertian),
        m_bIsLight(false)
    {
        Initialize();
    }
    Material(const Color d, const Color s, const float a, bool a_bIsLight = false) :
        Kd(d), Ks(s), alpha(a), texid(0),
        eMatType(eMaterialType_Lambertian),
        m_bIsLight(a_bIsLight)
    {
        Initialize();
    }
    Material(Material& o) { Kd = o.Kd;  Ks = o.Ks;  alpha = o.alpha;  texid = o.texid; eMatType = o.eMatType; m_bIsLight = o.m_bIsLight; Initialize(); }
    virtual ~Material() {};

    void setTexture(const std::string path);
    //virtual void apply(const unsigned int program);

    //Color EvalScattering(const Ray& a_RayIn, const Intersection& a_HitData) const;
    Color EvalScattering(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal, const Vector3f& a_vOmegaI);

    float PdfBRDF(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal, const Vector3f& a_vOmegaI);

    // Returns omega sub i
    Vector3f SampleBRDF(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal);
};

////////////////////////////////////////////////////////////////////////
// Light: encapsulates a light and communiction with a shader.
////////////////////////////////////////////////////////////////////////
class Light : public Material
{
public:

    Light(const Color e) : Material() { m_bIsLight = true; Kd = e; }
    virtual bool isLight() { return true; }
    //virtual void apply(const unsigned int program);

    Color Radiance() const { return Kd; }
};

#endif //MATERIAL_H