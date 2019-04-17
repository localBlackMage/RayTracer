#include "stdafx.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Material.h"
#endif //STB_IMAGE_IMPLEMENTATION

#define MATERIAL_TRANSMISSION_ENABLED true

Color operator*(const Color& lhs, const Pixel& rhs)
{
    return Color(rhs.r * lhs[0], rhs.g * lhs[1], rhs.b * lhs[2]);
}

Color operator*(const Pixel& lhs, const Color& rhs)
{
    return rhs * lhs;
}

Color operator*(const Pixel& lhs, const float& rhs)
{
    return Color(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs);
}

Color operator*(const float& lhs, const Pixel& rhs)
{
    return rhs * lhs;
}

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
#if MATERIAL_TRANSMISSION_ENABLED
    S = Vector3f(Kd).norm() + Vector3f(Ks).norm() + Vector3f(Kt).norm();
    Pd = Vector3f(Kd).norm() / S;
    Pr = Vector3f(Ks).norm() / S;
    Pt = Vector3f(Kt).norm() / S;
#else
    S = Vector3f(Kd).norm() + Vector3f(Ks).norm();
    Pd = Vector3f(Kd).norm() / S;
    Pr = Vector3f(Ks).norm() / S;
#endif


    m_fRoughnessExponent = 1.f / (alpha + 1.f);
}


Color Material::Attenuation(float a_fT, const Vector3f& a_vOmegaO, const Vector3f & a_vNormal)
{
    float KtSum = Kt[0] + Kt[1] + Kt[2];
    if (KtSum < 3.f)
    {
        float omegaODotN = a_vOmegaO.dot(a_vNormal);
        if (omegaODotN < 0.f)
        {
            float r = pow(MATH_E, a_fT * log(Kt[0]));
            float g = pow(MATH_E, a_fT * log(Kt[1]));
            float b = pow(MATH_E, a_fT * log(Kt[2]));

            return Color(r, g, b);
        }
    }
    return Color(1, 1, 1);
}

Color Material::Scattering_Diffuse()
{
    return (Kd / PI);
}

Color Material::Scattering_Reflection(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    eDirection direction = IORDirection(a_vOmegaO, a_vNormal);
    float etaI, etaO;
    Eta(direction, etaI, etaO);

    Vector3f m = (a_vOmegaO + a_vOmegaI).normalized();
    float DTerm = BRDF_D(m, a_vNormal, alpha);
    float GTerm = BRDF_G(a_vOmegaO, a_vOmegaI, m, a_vNormal, alpha);
    //Color FTerm = BRDF_F(a_vOmegaI, m, Ks);
    Color FTerm = BRDF_F_NotApprox(a_vOmegaI, m, Ks, etaI, etaO);
    float denom = 4.f * fabsf(a_vOmegaI.dot(a_vNormal)) * fabsf(a_vOmegaO.dot(a_vNormal));
    if (AreSimilar(denom, 0.f))
    {
        return Color(0, 0, 0);
    }
    else
    {
        return Color(DTerm * GTerm * FTerm) / denom;
    }
}

Color Material::Scattering_Transmission(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI, float a_fT)
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

    // Total Internal Scattering_Reflection
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
    // Normal Scattering_Transmission
    else
    {
        float DTerm = BRDF_D(m, a_vNormal, alpha);
        float GTerm = BRDF_G(a_vOmegaO, a_vOmegaI, m, a_vNormal, alpha);
        Color FColor = BRDF_F(a_vOmegaI, m, Ks);
        Color FTerm = Color(1.f - FColor[0], 1.f - FColor[1], 1.f - FColor[2]);

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

Color Material::EvalScattering(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI, float a_fT)
{
    Color Ed = Scattering_Diffuse();
    Color Er = Scattering_Reflection(a_vOmegaO, a_vNormal, a_vOmegaI);
#if MATERIAL_TRANSMISSION_ENABLED
    Color Et = Scattering_Transmission(a_vOmegaO, a_vNormal, a_vOmegaI, a_fT);
    return fabsf(a_vNormal.dot(a_vOmegaI)) * (Ed + Er + Et);
#else
    return fabsf(a_vNormal.dot(a_vOmegaI)) * (Ed + Er);
#endif
}



float Material::PDF_Diffuse(const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    return fabsf(a_vNormal.dot(a_vOmegaI) / PI);
}

float Material::PDF_Reflection(const Vector3f & a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    Vector3f m = (a_vOmegaO + a_vOmegaI).normalized();
    float DTerm = BRDF_D(m, a_vNormal, alpha);
    float newPR = DTerm * fabsf(m.dot(a_vNormal)) * (1.f / (4.f * fabsf(a_vOmegaI.dot(m))));

    if (isnan(newPR))
        newPR = 0.f;

    return newPR;
}

float Material::PDF_Transmission(const Vector3f & a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    eDirection direction = IORDirection(a_vOmegaO, a_vNormal);
    float etaI, etaO;
    Eta(direction, etaI, etaO);
    float eta = etaI / etaO;

    Vector3f m = -((etaO * a_vOmegaI + etaI * a_vOmegaO).normalized());
    float omegaODotM = a_vOmegaO.dot(m);
    float radicand = 1 - (eta * eta) * (1 - (omegaODotM * omegaODotM));
    float newPT = 0.f;
    // Total Internal Scattering_Reflection
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

float Material::PDF_BRDF(const Vector3f& a_vOmegaO, const Vector3f & a_vNormal, const Vector3f & a_vOmegaI)
{
    // Diffusion
    float newPD = PDF_Diffuse(a_vNormal, a_vOmegaI);

    // Reflection
    float newPR = PDF_Reflection(a_vOmegaO, a_vNormal, a_vOmegaI);

#if MATERIAL_TRANSMISSION_ENABLED
    // Transmission
    float newPT = PDF_Transmission(a_vOmegaO, a_vNormal, a_vOmegaI);

    return Pd * newPD + Pr * newPR + Pt * newPT;
#else
    return Pd * newPD + Pr * newPR;
#endif
}



Vector3f Material::BRDF_Diffuse(const Vector3f & a_vNormal)
{
    float a = MersenneRandFloat();
    float b = MersenneRandFloat();
    return SampleLobe(a_vNormal, sqrtf(a), PI_2 * b).normalized();
}

Vector3f Material::BRDF_Reflection(const Vector3f & a_vOmegaO, const Vector3f & a_vNormal)
{
    float a = MersenneRandFloat();
    float b = MersenneRandFloat();
    Vector3f m = SampleLobe(a_vNormal, powf(a, m_fRoughnessExponent), PI_2 * b).normalized();
    return 2.f * (a_vOmegaO.dot(m)) * m - a_vOmegaO;
}

Vector3f Material::BRDF_Transmission(const Vector3f & a_vOmegaO, const Vector3f & a_vNormal)
{
    float a = MersenneRandFloat();
    float b = MersenneRandFloat();
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
        return 2.f * (a_vOmegaO.dot(m)) * m - a_vOmegaO;
    }
    else
    {
        float leftA = eta * oDotM;
        float leftB = SignFN(a_vOmegaO.dot(a_vNormal)) * sqrtf(r);
        float left = leftA - leftB;
        return left * m - eta * a_vOmegaO;
    }
}

Vector3f Material::SampleBRDF(const Vector3f& a_vOmegaO, const Vector3f& a_vNormal)
{
    float phi = MersenneRandFloat();

#if MATERIAL_TRANSMISSION_ENABLED
    // Diffusion
    if (phi < Pd)
        return BRDF_Diffuse(a_vNormal);
    // Reflection
    else if (phi < Pr)
        return BRDF_Reflection(a_vOmegaO, a_vNormal);
    // Transmission
    else //if (phi < Pt)
        return BRDF_Transmission(a_vOmegaO, a_vNormal);
#else
    // Diffusion
    if (phi < Pd)
        return BRDF_Diffuse(a_vNormal);
    // Reflection
    else
        return BRDF_Reflection(a_vOmegaO, a_vNormal);
#endif
}


#pragma region IBL

ImageBasedLight::ImageBasedLight(const std::string & _imageFileName)
{
    LoadTexture(_imageFileName);
    m_Image.Preprocess();
    m_Image.m_fAngle = 0.f;
}

inline std::wstring s2ws(const char* a_pszStr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.from_bytes(a_pszStr);
}

void ImageBasedLight::LoadTexture(const std::string& _imageFileName)
{    
    DirectX::ScratchImage scratchImage;
    DirectX::TexMetadata meta;
    HRESULT hResult = DirectX::LoadFromHDRFile(s2ws(_imageFileName.c_str()).c_str(), &meta, scratchImage);

    if (FAILED(hResult))
    {
        std::cout << "Failed to load " << _imageFileName << std::endl;
    }

    byte* pixels = scratchImage.GetPixels();
    size_t numBytes = scratchImage.GetPixelsSize();

    m_Image.m_NumChannels = 3;

    if (meta.format == DXGI_FORMAT_R32G32B32A32_FLOAT)
    {
        float x = 0, y = 0;
        for (size_t offset = 0; offset < numBytes; offset += 16)
        {
            Pixel currentPixel;
            byte* curPixelChannel = pixels + offset;
            memcpy(&currentPixel.r, &pixels[offset], 12);
            m_Image.m_Data.push_back(currentPixel);
        }

        m_Image.m_Data.shrink_to_fit();
        m_Image.m_Height = meta.height;
        m_Image.m_Width = meta.width;
    }
    else
    {
        std::cout << "Unaccounted for format: " << meta.format << std::endl;
    }
}

float Luminence(const Pixel& a_Pixel)
{
    return 0.2126f * a_Pixel.r + 0.7152f * a_Pixel.g + 0.0722f * a_Pixel.b;
}

void HDRImage::Preprocess()
{
    m_pBuffer = new float[m_Width * (m_Height + 1)];
    m_pUDist = &m_pBuffer[m_Width * m_Height];
    float* pSinTheta = new float[m_Height];

    float angleFrac = PI / float(m_Height);
    float theta = angleFrac * 0.5f;

    for (uint32 i = 0; i < m_Height; i++, theta += angleFrac)
    {
        pSinTheta[i] = sinf(theta);
    }

    for (uint32 i = 0, m = 0; i < m_Width; i++, m += m_Height)
    {
        float * pVDist = &m_pBuffer[m];
        pVDist[0] = Luminence(m_Data[i]);
        pVDist[0] *= pSinTheta[0];

        for (uint32 j = 1, k = m_Width + i; j < m_Height; j++, k += m_Width)
        {
            float lum = Luminence(m_Data[k]);
            pVDist[j] = pVDist[j - 1] + lum * pSinTheta[j];
        }

        if (i == 0)
        {
            m_pUDist[i] = pVDist[m_Height - 1];
        }
        else
        {
            m_pUDist[i] = m_pUDist[i - 1] + pVDist[m_Height - 1];
        }
    }

}

Color ImageBasedLight::Radiance(const Intersection & a_Intersection)
{
    Vector3f P = a_Intersection.m_vPoint;
    P.normalize();
    double u = (/*m_Image.m_fAngle - */atan2(P[1], P[0])) / PI_2;
    u = u - floor(u);         // Wrap to be within 0...1
    double v = acos(P[2]) / PI;
    int i0 = floor(u*m_Image.m_Width);
    int j0 = floor(v*m_Image.m_Height);
    double uw[2], vw[2];
    uw[1] = u * m_Image.m_Width - i0;  uw[0] = 1.0 - uw[1];
    vw[1] = v * m_Image.m_Height - j0;  vw[0] = 1.0 - vw[1];
    Color r(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            int k = (((j0 + j) % m_Image.m_Height) * m_Image.m_Width + ((i0 + i) % m_Image.m_Width));
            r += uw[i] * vw[j] * m_Image.m_Data[k];
        }
    }
    Vector3f r2 = Vector3f(r);
    if (r2.norm() > 20.f)
        return r;
    return r;
}

void ImageBasedLight::SampleAsLight(Intersection & a_Intersection)
{
    float u = MersenneRandFloat();
    float v = MersenneRandFloat();

    float maxUVal = m_Image.m_pUDist[m_Image.m_Width - 1];
    float* pUPos = std::lower_bound(m_Image.m_pUDist, m_Image.m_pUDist + m_Image.m_Width, u * maxUVal);

    int iu = pUPos - m_Image.m_pUDist;
    float* pVDist = &m_Image.m_pBuffer[m_Image.m_Height * iu];
    float* pVPos = std::lower_bound(pVDist, pVDist + m_Image.m_Height, v * pVDist[m_Image.m_Height - 1]);

    int iv = pVPos - pVDist;

    float phi = /*m_Image.m_fAngle - */PI_2 * (iu / float(m_Image.m_Width));
    float theta = PI * (iv / float(m_Image.m_Height));
    
    a_Intersection.m_vNormal = Vector3f(sinf(theta) * cosf(phi),
                                        sinf(theta) * sinf(phi),
                                        cosf(theta)).normalized();
}

float ImageBasedLight::PDFAsLight(const Intersection & a_Intersection)
{
    Vector3f P = a_Intersection.m_vPoint;
    P.normalize();
    double fu = (/*m_Image.m_fAngle - */atan2(P[1], P[0])) / PI_2;
    fu = fu - floor(fu);         // Wrap to be within 0...1
    int u = floor(double(m_Image.m_Width) * fu);
    int v = floor(float(m_Image.m_Height) * acosf(P[2]) / PI);
    float angleFrac = PI / float(m_Image.m_Height);
    float* pVDist = &m_Image.m_pBuffer[m_Image.m_Height*u];
    float pdfU = (u == 0) ? (m_Image.m_pUDist[0]) : (m_Image.m_pUDist[u] - m_Image.m_pUDist[u - 1]);
    pdfU /= m_Image.m_pUDist[m_Image.m_Width - 1];
    pdfU *= m_Image.m_Width / PI_2;
    float pdfV = (v == 0) ? (pVDist[0]) : (pVDist[v] - pVDist[v - 1]);
    pdfV /= pVDist[m_Image.m_Height - 1];
    pdfV *= m_Image.m_Height / PI;
    float theta = angleFrac * 0.5 + angleFrac * v;
    float pdf = pdfU * pdfV*sinf(theta) / (4.f*PI*m_fRadius*m_fRadius);

    //printf("(%f %f %f) %d %d %g\n", P[0], P[1], P[2], u, v, pdf);

    return pdf;
}

#pragma endregion