#pragma once

#ifndef SLAB_H
#define SLAB_H

struct RTSlab {
    float m_fD0;
    float m_fD1;
    Vector3f m_vNormal;
};

Interval SlabIntersect(const RTSlab& a_Slab, const Ray& a_Ray);

#endif //SLAB_H