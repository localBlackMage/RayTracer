#include "stdafx.h"
#include "RayTracer.h"

Color operator*(const Color& lhs, const Vector3f& rhs)
{
    return Color(rhs[0] * lhs[0], rhs[1] * lhs[1], rhs[2] * lhs[2]);
}

Color operator*(const Vector3f& lhs, const Color& rhs)
{
    return rhs * lhs;
}

Color operator*(const Color& lhs, const Color& rhs)
{
    return Color(rhs[0] * lhs[0], rhs[1] * lhs[1], rhs[2] * lhs[2]);
}

Color RayTracer::PathTrace(const Ray & a_Ray, int a_iDepth)
{
    // Initial Ray
    Intersection P, L, I, Q;
    Color C = Color(0, 0, 0); // Accumulated Color
    Vector3f W = Vector3f(1, 1, 1); // Accumulated Weight
    if (m_pWorld->Hit(a_Ray, P))
    {
        if (P.m_pMaterial->isSkyBox())
        {
            return static_cast<ImageBasedLight*>(P.m_pMaterial)->Radiance(P);
        }
        else if (P.m_pMaterial->isLight())
        {
            return static_cast<Light*>(P.m_pMaterial)->Radiance();
        }
        else
        {
            Vector3f omegaO = -(a_Ray.Direction().normalized());
            while (MersenneRandFloat() <= RUSSIAN_ROULETTE)
            {
                Vector3f omegaI;
                Color f;
                float p, q, wMis;
#pragma region Explicit light connection
                m_pLights->SampleLight(L); // Randomly chosen light, a randomly chosen point on that light and it's normal
                p = m_pLights->PDFLight(L) / GeometryFactor(P, L);

                // Probability the explicit light could be chosen implicitly
                q = P.m_pMaterial->PDF_BRDF(omegaO, P.m_vNormal, omegaI) * RUSSIAN_ROULETTE;
                wMis = (p * p) / (p * p + q * q);
                omegaI = (L.m_vPoint - P.m_vPoint).normalized();

                // Cast the shadow ray
                Ray explicitRay = Ray(P.m_vPoint, omegaI);
                if (p > 0.f && m_pWorld->Hit(explicitRay, I) && I.m_vPoint.isApprox(L.m_vPoint) && I.m_pShape == L.m_pShape)
                {
                    f = P.m_pMaterial->EvalScattering(omegaO, P.m_vNormal, omegaI, L.m_fT);
                    Color LightRadiance(0,0,0);
                    if (L.m_pMaterial->isSkyBox())
                    {
                        LightRadiance = static_cast<ImageBasedLight*>(L.m_pMaterial)->Radiance(L);
                    }
                    else if (L.m_pMaterial->isLight())
                    {
                        LightRadiance = static_cast<Light*>(L.m_pMaterial)->Radiance();
                    }

                    Color explicitRadiance = W * (f / p) * LightRadiance * wMis;
                    C += explicitRadiance;
                }
#pragma endregion

#pragma region Extend Path
                omegaI = P.m_pMaterial->SampleBRDF(omegaO, P.m_vNormal).normalized();
                Ray extendedRay = Ray(P.m_vPoint, omegaI);

                if (!m_pWorld->Hit(extendedRay, Q))
                    break;

                f = P.m_pMaterial->EvalScattering(omegaO, P.m_vNormal, omegaI, Q.m_fT);
                p = P.m_pMaterial->PDF_BRDF(omegaO, P.m_vNormal, omegaI) * RUSSIAN_ROULETTE;
                if (p < EPSILON)
                {
                    break; // avoid division by 0
                }
                W = W * (f / p);
#pragma endregion
                
#pragma region Implicit Light connection
                if (Q.m_pMaterial->isLight())
                {
                    // Probability the implicit light could be chosen explicitly
                    q = m_pLights->PDFLight(Q) / GeometryFactor(P, Q);
                    wMis = (p * p) / (p * p + q * q);
                    Color LightRadiance(0, 0, 0);
                    if (Q.m_pMaterial->isSkyBox())
                    {
                        LightRadiance = static_cast<ImageBasedLight*>(Q.m_pMaterial)->Radiance(Q);
                    }
                    else if (Q.m_pMaterial->isLight())
                    {
                        LightRadiance = static_cast<Light*>(Q.m_pMaterial)->Radiance();
                    }

                    Color implicitRadiance = W * LightRadiance * wMis;
                    C += implicitRadiance;

                    break;
                }
#pragma endregion

                // Step Forward
                P = Q;
                omegaO = -omegaI;
            }
        }
    }
    
    return C;
}

RayTracer::RayTracer() :
    m_pCamera(nullptr),
    m_pWorld(new ShapeList()),
    m_pLights(new ShapeList())
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

void RayTracer::SetCamera(const Vector3f & a_vEye, const Quaternionf & a_qOrientation, float a_fRY, float a_fDistToFocusPlane, float a_fSizeOfConfusionCircle)
{
    if (m_pCamera)
        delete m_pCamera;

    m_pCamera = new Camera(a_vEye, a_qOrientation, float(m_uScreenWidth), float(m_uScreenHeight), a_fRY, a_fDistToFocusPlane, a_fSizeOfConfusionCircle);
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
    float nx = float(m_uScreenWidth - 1);
    float ny = float(m_uScreenHeight - 1);
    float halfWidth = float(m_uScreenWidth) * 0.5f;
    float halfHeight = float(m_uScreenHeight) * 0.5f;

    float x = 2.f * (float(i) + MersenneRandFloat() - halfWidth) / nx;
    float y = 2.f * (float(j) + MersenneRandFloat() - halfHeight) / ny;

    Ray ray;
    if (m_pCamera->HasDOF())
    {
        ray = m_pCamera->GetBlurredRay(x, y);
    }
    else
    {
        ray = m_pCamera->GetRay(x, y);
    }
    return PathTrace(ray, 0);
}
