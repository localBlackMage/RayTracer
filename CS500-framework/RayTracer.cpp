#include "stdafx.h"

Color RayTracer::PathTrace(const Ray & a_Ray, int a_iDepth)
{
    Intersection hData;
    if (m_pWorld->Hit(a_Ray, 0.0001f, FLT_MAX, hData))
    {
        //Ray scattered;
        //Vec3 attenuation;
        //if (a_iDepth < 50 && hData.m_pMaterial->Scatter(a_Ray, hData, attenuation, scattered))
        //{
        //    return attenuation * Color(scattered, a_World, a_iDepth + 1);
        //}
        //else
        //    return Vec3(0, 0, 0, 1);

        //return static_cast<Lambertian*>(hData.m_pMaterial)->Albedo();
        float depth = hData.m_fT / 10.f;
        return Color(depth, depth, depth);
        //return Vec3(fabsf(hData.m_vNormal.x), fabsf(hData.m_vNormal.y), fabsf(hData.m_vNormal.z));
    }
    else
    {
        Vector3f unitDir = a_Ray.Direction().normalized();
        float t = 0.5f * (unitDir.y() + 1.f);

        return (1.f - t) * Vector3f(1, 1, 1) + t * Vector3f(0.5f, 0.7f, 1.f);
    }
}

RayTracer::RayTracer() :
    m_pCamera(nullptr),
    m_pWorld(new ShapeList())
{
}

RayTracer::~RayTracer()
{
}

void RayTracer::SetCamera(const Vector3f & a_vEye, const Quaternionf & a_qOrientation, float a_fRY)
{
    if (m_pCamera)
        delete m_pCamera;

    m_pCamera = new Camera(a_vEye, a_qOrientation, a_fRY);
}

void RayTracer::AddSphere(const Vector3f & center, float r, Material * mat)
{
    Sphere* pSphere = new Sphere(center, r, mat);

    m_pWorld->AddShape(pSphere);
    if (mat->isLight())
        m_pLights->AddShape(pSphere);
}

void RayTracer::AddBox(const Vector3f & base, const Vector3f & diag, Material * mat)
{
    AACube* aaCube = new AACube(base, diag, mat);

    m_pWorld->AddShape(aaCube);
    if (mat->isLight())
        m_pLights->AddShape(aaCube);
}

void RayTracer::AddCylinder(const Vector3f & base, const Vector3f & axis, float radius, Material * mat)
{
    Cylinder * pCyllinder = new Cylinder(base, axis, radius, mat);

    m_pWorld->AddShape(pCyllinder);
    if (mat->isLight())
        m_pLights->AddShape(pCyllinder);
}

void RayTracer::AddTriangleMesh(MeshData * mesh)
{
}

Color RayTracer::GetColor(int i, int j)
{
    Color color(0, 0, 0);
    uint32 ns = uint32(m_fNumRaysPerPixel);
    float nx = float(m_uScreenX);
    float ny = float(m_uScreenY);

    for (uint32 s = 0; s < ns; ++s)
    {
        float u = float(i + Rand_Zero_LT_One()) / nx;
        float v = float(j + Rand_Zero_LT_One()) / ny;

        color += PathTrace(m_pCamera->GetRay(u, v), 0);
    }

    return color / m_fNumRaysPerPixel;

}
