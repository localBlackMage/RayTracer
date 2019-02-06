#pragma once

#ifndef INTERVAL_H
#define INTERVAL_H

class Material;

struct Interval
{
    float m_fT0 = 0.f, m_fT1 = FLT_MAX;
    Vector3f m_vNormal0, m_vNormal1;
};

void SetMinMaxInterval(Interval& a_IntToSet, const Interval& a_OtherInt);

struct Intersection
{
    float m_fT = INF, m_fMin = 0.0001f, m_fMax = INF;
    Vector3f m_vPoint;
    Vector3f m_vNormal;
    Material* m_pMaterial = nullptr;
    Interval m_Interval;
};

struct LowestPostiveIntersection
{
    bool m_bDidIntersect = false;
    float m_fT;
    Vector3f m_vNormal;
};

LowestPostiveIntersection FindLowestPositive(float a_fTMin, float a_fTMax, const Interval& a_Interval);

#endif