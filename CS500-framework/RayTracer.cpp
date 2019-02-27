#include "stdafx.h"
#include "RayTracer.h"

Color RayTracer::PathTrace(const Ray & a_Ray, int a_iDepth)
{
    Intersection hData;
    Color C = Color(0, 0, 0); // Accumulated Color
    Vector3f W = Vector3f(1, 1, 1); // Accumulated Weight
    if (m_pWorld->Hit(a_Ray, MINIMUM, INF, hData))
    {
        Ray scattered;
        if (hData.m_pMaterial->isLight())
        {
            return static_cast<Light*>(hData.m_pMaterial)->Radiance();
        }
        else
        {
            while (RandomFloat(0.f, 1.f) < RUSSIAN_ROULETTE)
            {
                Vector3f omegaI = hData.m_pMaterial->SampleBRDF(hData.m_vNormal);
                Ray scatterRay(hData.m_vPoint, omegaI);
                if (!m_pWorld->Hit(scatterRay, MINIMUM, INF, hData))
                    break;
                Vector3f f = hData.m_pMaterial->EvalScattering(hData.m_vNormal, omegaI);
            }
            return Color(0, 0, 0);
        }



        //return hData.m_pMaterial->Kd;
        //float depth = (hData.m_fT - 5.f) / 4.f;
        //return Color(depth, depth, depth);
        //return Vector3f(fabsf(hData.m_vNormal.x()), fabsf(hData.m_vNormal.y()), fabsf(hData.m_vNormal.z()));
    }
    else
    {
        //Vector3f unitDir = a_Ray.Direction().normalized();
        //float t = 0.5f * (unitDir.y() + 1.f);

        //return (1.f - t) * Vector3f(1, 1, 1) + t * Vector3f(0.5f, 0.7f, 1.f);
        return Color(0, 0, 0);
    }
}

RayTracer::RayTracer() :
    m_pCamera(nullptr),
    m_pWorld(new ShapeList()),
    m_pLights(new ShapeList()),
    m_fNumRaysPerPixel(10.f)
{
}

RayTracer::~RayTracer()
{
}

void RayTracer::SetScreenDimensions(uint32 a_uWidth, uint32 a_uHeight)
{
    m_uScreenWidth = a_uWidth;
    m_uScreenHeight = a_uHeight;
}

void RayTracer::SetCamera(const Vector3f & a_vEye, const Quaternionf & a_qOrientation, float a_fRY)
{
    if (m_pCamera)
        delete m_pCamera;

    m_pCamera = new Camera(a_vEye, a_qOrientation, float(m_uScreenWidth), float(m_uScreenHeight), a_fRY);
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

void RayTracer::AddTriangleMesh(MeshData * mesh, Material* mat)
{
    for (TriData& tri : mesh->triangles)
    {
        Triangle * pTri = new Triangle(mesh->vertices[tri[0]], mesh->vertices[tri[1]], mesh->vertices[tri[2]], mat);
        m_pWorld->AddShape(pTri);
        if (mat->isLight())
            m_pLights->AddShape(pTri);
    }
}

void RayTracer::Finish()
{
    m_pWorld->CreateTree();
    m_pLights->CreateTree();
}

Color RayTracer::GetColor(uint32 i, uint32 j)
{
    Color color(0, 0, 0);
    uint32 ns = uint32(m_fNumRaysPerPixel);
    float nx = float(m_uScreenWidth - 1);
    float ny = float(m_uScreenHeight - 1);
    float halfWidth = float(m_uScreenWidth) * 0.5f;
    float halfHeight = float(m_uScreenHeight) * 0.5f;

    for (uint32 s = 0; s < ns; ++s)
    {
        float x = 2.f * (float(i) + Rand_Zero_LT_One() - halfWidth) / nx;
        float y = 2.f * (float(j) + Rand_Zero_LT_One() - halfHeight) / ny;

        Ray ray = m_pCamera->GetRay(x, y);
        color += PathTrace(ray, 0);
    }

    return color / m_fNumRaysPerPixel;
}
