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
        return eDirection_InsideToOutside; // Leaves object
    else if (omegaOdotN < 0)
        return eDirection_OutsideToInside; // Enters object
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

void Material::Initialize()
{
    S = Vector3f(Kd).norm() + Vector3f(Ks).norm() + Vector3f(Kt).norm();
    Pd = Vector3f(Kd).norm() / S;
    Pr = Vector3f(Ks).norm() / S;
    Pt = Vector3f(Kt).norm() / S;

    m_fRoughnessExponent = 1.f / (alpha + 1.f);
}

Color Material::Attenuation(float a_fT, const Vector3f& a_vOmegaO, const Vector3f & a_vNormal)
{
    float omegaODotN = a_vOmegaO.dot(a_vNormal);
    if (omegaODotN < 0.f)
    {
        float r = pow(MATH_E, a_fT * log(Kt[0]));
        float g = pow(MATH_E, a_fT * log(Kt[1]));
        float b = pow(MATH_E, a_fT * log(Kt[2]));

        return Color(r, g, b);
    }
    else
    {
        return Color(1, 1, 1);
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
        return (DTerm * GTerm * FTerm) / denom;
    }
}

Color Material::Transmission(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI, float a_fT)
{
    eDirection direction = IORDirection(a_vOmegaO, a_vNormal);
    float etaI, etaO;
    Eta(direction, etaI, etaO);
    float eta = etaI / etaO;

    Vector3f m = (-(etaO * a_vOmegaI + etaI * a_vOmegaO)).normalized();
    float omegaODotM = a_vOmegaO.dot(m);
    // radicand = 1 - eta^2 * (1 - (omegaO dot m)^2)
    float radicand = 1 - (eta * eta) * (1 - (omegaODotM * omegaODotM));
    Color ATerm = Attenuation(a_fT, a_vOmegaO, a_vNormal); // Beer's Law = Attenuation factor A(t)

    // Total Internal Reflection
    if (radicand < 0)
    {
        m = (a_vOmegaO + a_vOmegaI).normalized();
        float DTerm = BRDF_D(m, a_vNormal, alpha);
        float GTerm = BRDF_G(a_vOmegaI, a_vOmegaO, m, a_vNormal, alpha);
        Color FTerm = BRDF_F(a_vOmegaI, m, Ks);
        float denom = 4.f * fabsf(a_vOmegaI.dot(a_vNormal)) * fabsf(a_vOmegaO.dot(a_vNormal));
        if (AreSimilar(denom, 0.f))
        {
            return Color(0, 0, 0);
        }
        else
        {
            return ATerm * (DTerm * GTerm * FTerm) / denom;
        }
    }
    // Normal Transmission
    else
    {
        float DTerm = BRDF_D(m, a_vNormal, alpha);
        float GTerm = BRDF_G(a_vOmegaO, a_vOmegaI, m, a_vNormal, alpha);
        //if (AreSimilar(DTerm, 0.f))
        //    std::cout << "DTerm is " << DTerm << std::endl;
        //if (AreSimilar(GTerm, 0.f))
        //    std::cout << "GTerm is " << GTerm << std::endl;


        Color FColor = BRDF_F(a_vOmegaI, m, Ks);

        //if (!AreSimilar(Kt[0], 0.f) && !AreSimilar(Kt[1], 0.f) && !AreSimilar(Kt[2], 0.f))
        //    std::cout << "Check" << std::endl;

        Color FTerm = Color(1.f - FColor[0], 1.f - FColor[1], 1.f - FColor[2]);
        float sum = fabsf(FTerm[0]) + fabsf(FTerm[1]) + fabsf(FTerm[2]);/*
        if (sum > 3.f)
            std::cout << "FTerm out of range: \n" << FTerm << std::endl;*/
        float denom = fabsf(a_vOmegaI.dot(a_vNormal)) * fabsf(a_vOmegaO.dot(a_vNormal));
        float RightTermNum = fabsf(a_vOmegaI.dot(m)) * fabsf(a_vOmegaO.dot(m)) * etaO * etaO;
        float RightTermDenom = etaO * a_vOmegaI.dot(m) + etaI * a_vOmegaO.dot(m);
        RightTermDenom *= RightTermDenom;

        if (AreSimilar(denom, 0.f) || AreSimilar(RightTermDenom, 0.f))
        {
            return Color(0, 0, 0);
        }
        else
        {
            return ATerm * ((DTerm * GTerm * FTerm) / denom) * (RightTermNum / RightTermDenom);
        }
    }
}

float Material::PDFDiffuse(const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    return fabsf(a_vNormal.dot(a_vOmegaI) / PI);
}

float Material::PDFReflection(const Vector3f & a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    Vector3f m = (a_vOmegaO + a_vOmegaI).normalized();
    float DTerm = BRDF_D(m, a_vNormal, alpha);
    float newPR = DTerm * fabsf(m.dot(a_vNormal)) * (1.f / (4.f * fabsf(a_vOmegaI.dot(m))));

    if (isnan(newPR))
        newPR = 0.f;

    return newPR;
}

float Material::PDFTransmission(const Vector3f & a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    eDirection direction = IORDirection(a_vOmegaO, a_vNormal);
    float etaI, etaO;
    Eta(direction, etaI, etaO);
    float eta = etaI / etaO;

    Vector3f m = -((etaO * a_vOmegaI + etaI * a_vOmegaO).normalized());
    float omegaODotM = a_vOmegaO.dot(m);
    float radicand = 1 - (eta * eta) * (1 - (omegaODotM * omegaODotM));
    float newPT = 0.f;
    // Total Internal Reflection
    if (radicand < 0.f)
    {
        m = (a_vOmegaO + a_vOmegaI).normalized();
        newPT = BRDF_D(m, a_vNormal, alpha) * fabsf(a_vNormal.dot(m)) * (1.f / (4.f * fabsf(a_vOmegaI.dot(m))));
    }
    // Normal transmission
    else
    {
        float numerator = etaO * etaO * fabsf(a_vOmegaI.dot(m));
        float denominator = (etaO * a_vOmegaI.dot(m) + etaI * a_vOmegaO.dot(m));
        denominator *= denominator;
        newPT = BRDF_D(m, a_vNormal, alpha) * fabsf(a_vNormal.dot(m)) * (numerator / denominator);

        //if (isnan(newPT))
        //{
        //    std::cout << "newPT is nan :: numerator : " << numerator << " :: denominator :: " << denominator << std::endl;
        //    std::cout << "EtaO : " << etaO << " :: EtaI : " << etaI << std::endl;
        //    std::cout << "M: " << m << std::endl;
        //    std::cout << "a_vOmegaI: " << a_vOmegaI << std::endl;
        //    std::cout << "a_vOmegaO: " << a_vOmegaO << std::endl;
        //}
    }

    if (isnan(newPT))
    {
        return 1.f;
    }
    else
    {
        return newPT;
    }
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

Color Material::EvalScattering(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI, float a_fT)
{
    Color Ed = Diffuse();
    Color Er = Reflection(a_vOmegaO, a_vNormal, a_vOmegaI);
    Color Et = Transmission(a_vOmegaO, a_vNormal, a_vOmegaI, a_fT);

    //if (IsColorNAN(Ed))
    //    std::cout << "Diffuse is NAN" << std::endl;
    //if (IsColorINF(Er))
    //    std::cout << "Reflection is INF" << std::endl;
    //if (IsColorNAN(Et))
    //    std::cout << "Transmission is NAN" << std::endl;

    //if (!AreSimilar(Et[0], 0.f) && !AreSimilar(Et[1], 0.f) && !AreSimilar(Et[2], 0.f))
    //    std::cout << "Transmission " << std::endl;

    //if (Et[0] < 0.f && Et[1] < 0.f && Et[2] < 0.f)
    //    std::cout << "Et negative: " << Et << std::endl;
    //else
    //    std::cout << "Et: " << Et << std::endl;

    return fabsf(a_vNormal.dot(a_vOmegaI)) * (Ed + Er +Et);
}

float Material::PdfBRDF(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    // Diffusion
    float newPD = PDFDiffuse(a_vNormal, a_vOmegaI);

    // Reflection
    float newPR = PDFReflection(a_vOmegaO, a_vNormal, a_vOmegaI);

    // Transmission
    float newPT = PDFTransmission(a_vOmegaO, a_vNormal, a_vOmegaI);

    return Pd * newPD + Pr * newPR + Pt * newPT;
}

Vector3f Material::SampleBRDF(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal)
{
    float phi = MersenneRandFloat();
    float a = MersenneRandFloat();
    float b = MersenneRandFloat();
    Vector3f omegaI;

    // Diffusion
    if (phi < Pd)
    {
        omegaI = SampleLobe(a_vNormal, sqrtf(a), PI_2 * b).normalized();
    }
    // Reflection
    else if (phi < Pr)
    {
        Vector3f m = SampleLobe(a_vNormal, powf(a, m_fRoughnessExponent), PI_2 * b).normalized();
        omegaI = 2.f * (a_vOmegaO.dot(m)) * m - a_vOmegaO; // omegaI
    }
    // Transmission
    else //if (phi < Pt)
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
            omegaI = 2.f * (a_vOmegaO.dot(m)) * m - a_vOmegaO; // omegaI
        }
        else
        {
            float leftA = eta * oDotM;
            float leftB = SignFN(a_vOmegaO.dot(a_vNormal)) * sqrtf(r);
            float left = leftA - leftB;
            omegaI = left * m - eta * a_vOmegaO;
        }
    }
    return omegaI;
}