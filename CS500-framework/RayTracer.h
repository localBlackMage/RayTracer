#pragma once

#ifndef RAY_TRACER_H
#define RAY_TRACER_H

class Camera;
struct MeshData;
class ShapeList;

class RayTracer
{
protected:
    Camera* m_pCamera;
    ShapeList* m_pWorld;
    ShapeList* m_pLights;
    uint32 m_uScreenWidth, m_uScreenHeight;

    Color PathTrace(const Ray& a_Ray, int a_iDepth);
public:
    RayTracer();
    ~RayTracer();

    void SetScreenDimensions(uint32 a_uWidth, uint32 a_uHeight);
    void SetCamera(const Vector3f& a_vEye, const Quaternionf& a_qOrientation, float a_fRY, float a_fDistToFocusPlane, float a_fSizeOfConfusionCircle);
    void SetAmbient() {};
    void AddSphere(const Vector3f& center, float r, Material* mat);
    void AddBox(const Vector3f& base, const Vector3f& diag, Material* mat);
    void AddCylinder(const Vector3f& base, const Vector3f& axis, float radius, Material* mat);
    void AddTriangleMesh(MeshData* mesh, Material * mat);
    uint32 NumShapes() const { return m_pWorld->NumShapes(); }
    void Finish();

    Color GetColor(uint32 i, uint32 j);
};

#endif //RAY_TRACER_H