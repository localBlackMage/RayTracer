#include "stdafx.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Material.h"
#endif //STB_IMAGE_IMPLEMENTATION

eDirection IORDirection(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal)
{
    float omegaOdotN = a_vOmegaO.dot(a_vNormal);
    if (omegaOdotN > 0)
        return eDirection_InsideToOutside;
    else if (omegaOdotN < 0)
        return eDirection_OutsideToInside;
    else
        return eDirection_Parallel;
}

float CalculateIOR(eDirection a_Direction, float a_fIOR)
{
    switch (a_Direction)
    {
        case eDirection_InsideToOutside:
        {
            return 1.f / a_fIOR;
        }
        case eDirection_OutsideToInside:
        {
            return a_fIOR / 1.f;
        }
        case eDirection_Parallel:
        default:
        {
            return 1.f;
        }
    }
}

Color Material::LambertianScatter(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    return fabsf(a_vNormal.dot(a_vOmegaI)) * (Kd / PI);
}

Color Material::MetalScatter(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    return Color(0, 0, 0);
}

void Material::Initialize()
{
    m_pScatterFunctions[eMaterialType_Lambertian] = &Material::LambertianScatter;
    m_pScatterFunctions[eMaterialType_Metal] = &Material::MetalScatter;

    S = Vector3f(Kd).norm() + Vector3f(Ks).norm() + Vector3f(Kt).norm();
    Pd = Vector3f(Kd).norm() / S;
    Pr = Vector3f(Ks).norm() / S;
    Pt = Vector3f(Kt).norm() / S;

    m_fRoughnessExponent = 1.f / (alpha + 1.f);
}

void Material::Eta(eDirection a_Direction, float& a_fEtaI, float& a_fEtaO)
{
    switch (a_Direction)
    {
        case eDirection_InsideToOutside:
        {
            a_fEtaI = 1.f;
            a_fEtaO = m_IOR;
            break;
        }
        case eDirection_OutsideToInside:
        {
            a_fEtaI = m_IOR;
            a_fEtaO = 1.f;
            break;
        }
        case eDirection_Parallel:
        default:
        {
            a_fEtaI = 1.f;
            a_fEtaO = 1.f;
            break;
        }
    }
}

Color Material::Diffuse()
{
    return (Kd / PI);
}

Color Material::Reflection(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    Vector3f m = (a_vOmegaO + a_vOmegaI).normalized();
    float DTerm = BRDF_D(m, a_vNormal, alpha);
    float GTerm = BRDF_G(a_vOmegaO, a_vOmegaI, m, a_vNormal, alpha);
    Color FTerm = BRDF_F(a_vOmegaI, m, Ks);
    float denom = 4.f * fabsf(a_vOmegaI.dot(a_vNormal)) * fabsf(a_vOmegaO.dot(a_vNormal));
    if (AreSimilar(denom, 0.f))
    {
        return Color(0, 0, 0);
    }
    else
    {
        //if (isnan(DTerm))
        //    std::cout << "DTerm is NAN" << std::endl;
        //if (isnan(GTerm))
        //    std::cout << "GTerm is NAN" << std::endl;
        //if (IsColorNAN(FTerm))
        //    std::cout << "FTerm is NAN" << std::endl;
        return (DTerm * GTerm * FTerm) / denom;
    }
}

Color Material::Transmission(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    eDirection direction = IORDirection(a_vOmegaO, a_vNormal);
    float etaI, etaO;
    Eta(direction, etaI, etaO);
    float eta = etaI / etaO;
    Vector3f m = (-(etaO * a_vOmegaI + etaI * a_vOmegaO)).normalized();
    float omegaODotM = a_vOmegaO.dot(m);
    // radicand = 1 - eta^2 * (1 - (omegaO dot m)^2)
    float radicand = 1 - (eta * eta) * (1 - (omegaODotM * omegaODotM));

    return Color();
}

void Material::setTexture(const std::string path)
{
    //int width, height, n;
    //stbi_set_flip_vertically_on_load(true);
    //unsigned char* image = stbi_load(path.c_str(), &width, &height, &n, 0);

    //// Realtime code below:  This sends the texture in *image to the graphics card.
    //// The raytracer will not use this code (nor any features of OpenGL nor the graphics card).
    //glGenTextures(1, &texid);
    //glBindTexture(GL_TEXTURE_2D, texid);
    //glTexImage2D(GL_TEXTURE_2D, 0, n, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 100);
    //glGenerateMipmap(GL_TEXTURE_2D);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)GL_LINEAR);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)GL_LINEAR_MIPMAP_LINEAR);
    //glBindTexture(GL_TEXTURE_2D, 0);

    //stbi_image_free(image);
}

Color Material::EvalScattering(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    Color Ed = Diffuse();
    Color Er = Reflection(a_vOmegaO, a_vNormal, a_vOmegaI);
    Color Et = Transmission(a_vOmegaO, a_vNormal, a_vOmegaI);

    return fabsf(a_vNormal.dot(a_vOmegaI)) * (Ed + Er);
}

float Material::PdfBRDF(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    Vector3f halfVector = (a_vOmegaO + a_vOmegaI).normalized();
    Vector3f m = halfVector;

    // Diffusion
    float newPD = fabsf(a_vNormal.dot(a_vOmegaI) / PI);

    // Reflection
    float DTerm = BRDF_D(m, a_vNormal, alpha);
    float newPR = DTerm * (m.dot(a_vNormal)) * (1.f / (4.f * fabsf(a_vOmegaI.dot(m))));

    if (isnan(newPR))
        newPR = 0.f;

    // Transmission
    eDirection direction = IORDirection(a_vOmegaO, a_vNormal);
    float etaI, etaO;
    Eta(direction, etaI, etaO);
    float eta = etaI / etaO;

    m = (-(etaO * a_vOmegaI + etaI * a_vOmegaO)).normalized();
    float omegaODotM = a_vOmegaO.dot(m);
    // radicand = 1 - eta^2 * (1 - (omegaO dot m)^2)
    float radicand = 1 - (eta * eta) * (1 - (omegaODotM * omegaODotM));
    float newPt = 0.f;
    // Total Internal Reflection
    if (radicand < 0.f)
    {
        m = halfVector;
        newPt = BRDF_D(m, a_vNormal, alpha) * fabsf(a_vNormal.dot(m)) * (1.f / (4.f * fabsf(a_vOmegaI.dot(m))));
    }
    // Normal transmission
    else
    {
        float numerator = etaO * etaO * fabsf(a_vOmegaI.dot(m));
        float denominator = (etaO * a_vOmegaI.dot(m) + etaI * a_vOmegaO.dot(m));
        denominator *= denominator;
        newPt = BRDF_D(m, a_vNormal, alpha) * fabsf(a_vNormal.dot(m)) * (numerator / denominator);
    }

    return Pd * newPD + Pr * newPR + Pt * newPt;
}

Vector3f Material::SampleBRDF(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal)
{
    float phi = MersenneRandFloat();
    float a = MersenneRandFloat();
    float b = MersenneRandFloat();

    // Diffusion
    if (phi < Pd)
    {
        return SampleLobe(a_vNormal, sqrtf(a), PI_2 * b).normalized();
    }
    // Reflection
    else if (phi < Pr)
    {
        Vector3f m = SampleLobe(a_vNormal, powf(a, m_fRoughnessExponent), PI_2 * b).normalized();
        return 2.f * (a_vOmegaO.dot(m)) * m - a_vOmegaO; // omegaI
    }
    // Transmission
    else /*if (phi < Pt)*/
    {
        Vector3f m = SampleLobe(a_vNormal, powf(a, m_fRoughnessExponent), PI_2 * b).normalized();
        float oDotM = a_vOmegaO.dot(m);
        eDirection direction = IORDirection(a_vOmegaO, a_vNormal);
        float etaI, etaO;
        Eta(direction, etaI, etaO);
        float eta = etaI / etaO;
        float r = 1 - eta * eta * (1.f - (oDotM * oDotM));

        // Total internal refraction
        if (r < 0.f)
        {
            return 2.f * (a_vOmegaO.dot(m)) * m - a_vOmegaO; // omegaI
        }
        else
        {
            return  (eta * a_vOmegaO.dot(m) - SignFN(a_vOmegaO.dot(a_vNormal)) * sqrtf(r)) * m - eta * a_vOmegaO;
        }
    }
}