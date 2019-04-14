#pragma once

#ifndef PLANE_H
#define PLANE_H

struct RTPlaneIntersection {
    float a_fT;
};

struct RTPlane {
    float m_fD;
    Vector3f m_vNormal;
};

float PlaneIntersect(const RTPlane& a_Plane, const Ray& a_Ray);

#endif //SLAB_H