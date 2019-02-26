#include "stdafx.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif //STB_IMAGE_IMPLEMENTATION

//Color Material::LambertianScatter(const Ray & a_RayIn, const Intersection & a_HitData)
//{
//    //Vector3f target = a_HitData.m_vPoint + a_HitData.m_vNormal + Rand_UnitSphere();
//
//    //a_RayOut = Ray(a_HitData.m_vPoint, target - a_HitData.m_vPoint);
//
//    return (a_HitData.m_vNormal.dot(Vector3f::UnitZ())) *  Kd / PI; // needs omega sub i
//}
//
//Color Material::MetalScatter(const Ray & a_RayIn, const Intersection & a_HitData)
//{
//    return Color(0,0,0);
//}

Color Material::LambertianScatter(const Vector3f & a_vNormal, const Vector3f & a_vOmega)
{
    return (a_vNormal.dot(a_vOmega)) *  Kd / PI; // needs omega sub i
}

Color Material::MetalScatter(const Vector3f & a_vNormal, const Vector3f & a_vOmega)
{
    return Color(0, 0, 0);
}

void Material::Initialize()
{
    m_pScatterFunctions[eMaterialType_Lambertian] = &Material::LambertianScatter;
    m_pScatterFunctions[eMaterialType_Metal] = &Material::MetalScatter;
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

//Color Material::EvalScattering(const Ray & a_RayIn, const Intersection & a_HitData) const
//{
//    return m_pScatterFunctions[eMatType](a_RayIn, a_HitData);
//}

Color Material::EvalScattering(const Vector3f & a_vNormal, const Vector3f & a_vOmega)
{
    return (this->*m_pScatterFunctions[eMatType])(a_vNormal, a_vOmega);
}

Vector3f Material::SampleBRDF(const Vector3f a_vNormal)
{
    float a = RandomFloat(0.f, 1.f);
    float b = RandomFloat(0.f, 1.f); // I suspect these are Monte Carlo values, not random
    
    return SampleLobe(a_vNormal, sqrtf(a), PI_2 * b);
}
