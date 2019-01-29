#pragma once

#ifndef INTERVAL_H
#define INTERVAL_H

class Material;

struct Interval
{
    float m_fT0, m_fT1;
    Vec3 m_vNormal0, m_vNormal1;
};

void SetMinMaxInterval(Interval& a_IntToSet, const Interval& a_OtherInt);

struct Intersection
{
    float m_fT;
    Vec3 m_vPoint;
    Vec3 m_vNormal;
    Material* m_pMaterial;
    Interval m_Interval;
};

bool SetIntersectionFromLowestPositive(Intersection& a_Intersection, const Interval& a_Interval);

#endif