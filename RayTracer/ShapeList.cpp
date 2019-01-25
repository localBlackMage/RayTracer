#include "stdafx.h"

bool ShapeList::Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const
{
    Intersection hData;
    bool hitAnything = false;
    float closestSoFar = a_fTMax;

    for (uint32 i = 0; i < m_uListSize; ++i)
    {
        if (m_ShapeList[i]->Hit(a_Ray, a_fTMin, closestSoFar, hData))
        {
            hitAnything = true;
            closestSoFar = hData.m_fT;
            a_Hit = hData;
        }
    }
    return hitAnything;
}
