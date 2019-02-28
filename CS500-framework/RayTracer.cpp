#include "stdafx.h"
#include "RayTracer.h"

Color operator*(const Color& lhs, const Vector3f& rhs)
{
    return Color(rhs[0] * lhs[0], rhs[1] * lhs[1], rhs[2] * lhs[2]);
}

Color operator*(const Vector3f& lhs, const Color& rhs)
{
    return Color(rhs[0] * lhs[0], rhs[1] * lhs[1], rhs[2] * lhs[2]);
}

Color operator*(const Color& lhs, const Color& rhs)
{
    return Color(rhs[0] * lhs[0], rhs[1] * lhs[1], rhs[2] * lhs[2]);
}

Color RayTracer::PathTrace(const Ray & a_Ray, int a_iDepth)
{
    // Initial Ray
    Intersection hData;
    Color C = Color(0, 0, 0); // Accumulated Color
    Vector3f W = Vector3f(1, 1, 1); // Accumulated Weight
    if (m_pWorld->Hit(a_Ray, hData))
    {
        if (hData.m_pMaterial->isLight())
        {
            return static_cast<Light*>(hData.m_pMaterial)->Radiance();
        }
        else
        {
            C = hData.m_pMaterial->Kd;
            while (MersenneRandFloat() < RUSSIAN_ROULETTE)
            {
                // Explicit light connection
                Intersection hDataL;
                m_pLights->SampleLight(hDataL); // Randomly chosen light, a randomly chosen point on that light and it's normal
                float p = m_pLights->PDFLight(hDataL.m_pShape) / GeometryFactor(hData, hDataL);
                Vector3f omegaI = (hDataL.m_vPoint - hData.m_vPoint).normalized();
                Color f;
                Intersection hDataI;
                // No intersections between this point and the light
                if (m_pWorld->Hit(Ray(hDataL.m_vPoint + (omegaI * 0.01f), omegaI), hDataI) &&
                    hDataI.m_pShape == hDataL.m_pShape && 
                    p > 0.f)
                {
                    f = hDataI.m_pMaterial->EvalScattering(hData.m_vNormal, omegaI);
                    C += W * static_cast<Light*>(hDataL.m_pMaterial)->Radiance() * f / p;
                }


                // Extend Path
                Intersection hDataQ;
                omegaI = hData.m_pMaterial->SampleBRDF(hData.m_vNormal);
                Ray scatterRay(hData.m_vPoint + (omegaI * 0.01f), omegaI);
                
                if (!m_pWorld->Hit(scatterRay, hDataQ))
                    break;

                f = hDataQ.m_pMaterial->EvalScattering(hDataQ.m_vNormal, omegaI);
                p = hDataQ.m_pMaterial->PDFBRDF(hDataQ.m_vNormal, omegaI) * RUSSIAN_ROULETTE;
                if (p < EPSILON)
                    continue; // avoid division by 0
                W = W * (f / p);
                
                // Implicit Light connection
                if (hDataQ.m_pMaterial->isLight())
                {
                    C += W * static_cast<Light*>(hDataQ.m_pMaterial)->Radiance();
                    break;
                }

                // Step Forward
                hData = hDataQ;
            }
            return C;
        }
        //return hData.m_pMaterial->Kd;
        //float depth = (hData.m_fT - 5.f) / 4.f;
        //return Color(depth, depth, depth);
        //return Vector3f(fabsf(hData.m_vNormal.x()), fabsf(hData.m_vNormal.y()), fabsf(hData.m_vNormal.z()));
    }
    // No intersection, return C as is
    else
    {
        //Vector3f unitDir = a_Ray.Direction().normalized();
        //float t = 0.5f * (unitDir.y() + 1.f);

        //return (1.f - t) * Vector3f(1, 1, 1) + t * Vector3f(0.5f, 0.7f, 1.f);
        return C;
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
