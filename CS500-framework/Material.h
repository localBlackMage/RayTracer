#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

enum eMaterialType : uint32
{
    eMaterialType_Lambertian = 0,
    eMaterialType_Metal,

    eMaterialType_MAX
};

enum eDirection : uint32 {
    eDirection_InsideToOutside = 0,
    eDirection_OutsideToInside,
    eDirection_Parallel
};

class Material
{
protected:
    float Pd, Pr, Pt, S, m_fRoughnessExponent;

    void Initialize();
    void Eta(eDirection a_Direction, float& a_fEtaI, float& a_fEtaO);
    Color Attenuation(float a_fT, const Vector3f& a_vOmegaO, const Vector3f & a_vNormal);

    Color Scattering_Diffuse();
    Color Scattering_Reflection(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI);
    Color Scattering_Transmission(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI, float a_fT);

    float PDF_Diffuse(const Vector3f& a_vNormal, const Vector3f& a_vOmegaI);
    float PDF_Reflection(const Vector3f & a_vOmegaO, const Vector3f& a_vNormal, const Vector3f& a_vOmegaI);
    float PDF_Transmission(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal, const Vector3f& a_vOmegaI);

    Vector3f BRDF_Diffuse(const Vector3f& a_vNormal);
    Vector3f BRDF_Reflection(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal);
    Vector3f BRDF_Transmission(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal);
public:
    Color Kd, Ks, Kt;
    float alpha, m_IOR;
    unsigned int texid;
    eMaterialType eMatType;
    bool m_bIsLight;

    virtual bool isLight() { return false; }
    virtual bool isSkyBox() { return false; }

    Material() : 
        Kd(Color(1.0, 0.5, 0.0)), 
        Ks(Color(1, 1, 1)),
        Kt(Color(1, 1, 1)),
        alpha(1.f), 
        m_IOR(1.f),
        texid(0),
        eMatType(eMaterialType_Lambertian),
        m_bIsLight(false)
    {
        Initialize();
    }
    Material(const Color d, const Color s, const Color t, const float a, const float ior, bool a_bIsLight = false) :
        Kd(d), Ks(s), Kt(t), alpha(a), m_IOR(ior), texid(0),
        eMatType(eMaterialType_Lambertian),
        m_bIsLight(a_bIsLight)
    {
        Initialize();
    }
    Material(Material& o) { Kd = o.Kd;  Ks = o.Ks; Kt = o.Kt; alpha = o.alpha; m_IOR = o.m_IOR; texid = o.texid; eMatType = o.eMatType; m_bIsLight = o.m_bIsLight; Initialize(); }
    virtual ~Material() {};

    Color EvalScattering(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal, const Vector3f& a_vOmegaI, float a_fT);

    float PDF_BRDF(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal, const Vector3f& a_vOmegaI);

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
    virtual bool isSkyBox() { return false; }
    //virtual void apply(const unsigned int program);

    virtual Color Radiance() const { return Kd; }
};

struct Pixel
{
    float r, g, b;
};

Color operator*(const Color& lhs, const Pixel& rhs);

Color operator*(const Pixel& lhs, const Color& rhs);

Color operator*(const Pixel& lhs, const float& rhs);

Color operator*(const float& lhs, const Pixel& rhs);

struct HDRImage {
    std::vector<Pixel> m_Data;
    int m_Width, m_Height, m_NumChannels;
    float* m_pBuffer;
    float* m_pUDist;
    float m_fAngle;

    void Preprocess();
};

class ImageBasedLight : public Material
{
protected:
    HDRImage m_Image;
    float m_fRadius;

    void LoadTexture(const std::string& _imageFileName);
public:
    ImageBasedLight(const std::string& _imageFileName);
    virtual bool isLight() { return true; }
    virtual bool isSkyBox() { return true; }

    void SetRadius(float a_fRadius) { m_fRadius = a_fRadius; }
    const HDRImage& Image() { return m_Image; }
    virtual Color Radiance(const Intersection & a_Intersection);
    void SampleAsLight(Intersection& a_Intersection);
    float PDFAsLight(const Intersection & a_Intersection);
};

#endif //MATERIAL_H