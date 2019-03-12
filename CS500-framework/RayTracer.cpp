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
        if (P.m_pMaterial->isLight())
        {
            return static_cast<Light*>(P.m_pMaterial)->Radiance();
        }
        else
        {
            Vector3f omegaO = (-a_Ray.Direction()).normalized();
            while (MersenneRandFloat() <= RUSSIAN_ROULETTE)
            {
                Vector3f omegaI;
                Color f;
                float p;
#pragma region Explicit light connection
                m_pLights->SampleLight(L); // Randomly chosen light, a randomly chosen point on that light and it's normal
                p = m_pLights->PDFLight(L.m_pShape) / GeometryFactor(P, L);
                omegaI = (L.m_vPoint - P.m_vPoint).normalized();

                // Cast the shadow ray
                Ray explicitRay = Ray(P.m_vPoint, omegaI); ///* + (omegaI * EPSILON)*/
                if (p > 0.f && 
                    m_pWorld->Hit(explicitRay, I) && 
                    I.m_vPoint.isApprox(L.m_vPoint) && 
                    I.m_pShape == L.m_pShape)
                {
                    f = P.m_pMaterial->EvalScattering(omegaO, P.m_vNormal, omegaI);
                    C += W * (f / p) * static_cast<Light*>(L.m_pMaterial)->Radiance();
                }
#pragma endregion

#pragma region Extend Path
                omegaI = P.m_pMaterial->SampleBRDF(omegaO, P.m_vNormal);
                Ray extendedRay = Ray(P.m_vPoint, omegaI); /// + (omegaI * EPSILON)

                if (!m_pWorld->Hit(extendedRay, Q))
                    break;

                f = P.m_pMaterial->EvalScattering(omegaO, P.m_vNormal, omegaI);
                p = P.m_pMaterial->PdfBRDF(omegaO, P.m_vNormal, omegaI) * RUSSIAN_ROULETTE;
                if (p < EPSILON)
                    break; // avoid division by 0
                W = W * (f / p);
#pragma endregion
                
#pragma region Implicit Light connection
                if (Q.m_pMaterial->isLight())
                {
                    C += W * static_cast<Light*>(Q.m_pMaterial)->Radiance();
                    break;
                }
#pragma endregion

                // Step Forward
                P = Q;
                omegaO = -omegaI;
            }
            return C;
        }

        //return hData.m_pMaterial->Kd;
        //float depth = (hData.m_fT - 5.f) / 4.f;
        //return Color(depth, depth, depth);
        //return Vector3f(fabsf(hData.m_vNormal.x()), fabsf(hData.m_vNormal.y()), fabsf(hData.m_vNormal.z()));
    }
    // No intersection, return C as is
    return C;
}

RayTracer::RayTracer() :
    m_pCamera(nullptr),
    m_pWorld(new ShapeList()),
    m_pLights(new ShapeList()),
    m_fNumRaysPerPixel(8.f)
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
    float nx = float(m_uScreenWidth - 1);
    float ny = float(m_uScreenHeight - 1);
    float halfWidth = float(m_uScreenWidth) * 0.5f;
    float halfHeight = float(m_uScreenHeight) * 0.5f;

    float x = 2.f * (float(i) + MersenneRandFloat() - halfWidth) / nx;
    float y = 2.f * (float(j) + MersenneRandFloat() - halfHeight) / ny;

    Ray ray = m_pCamera->GetRay(x, y);
    return PathTrace(ray, 0);
}
