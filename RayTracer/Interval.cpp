#include "stdafx.h"

void SetMinMaxInterval(Interval & a_IntToSet, const Interval & a_OtherInt)
{
    if (a_OtherInt.m_fT0 > a_IntToSet.m_fT0)
    {
        a_IntToSet.m_fT0 = a_OtherInt.m_fT0;
        a_IntToSet.m_vNormal0 = a_OtherInt.m_vNormal0;
    }

    if (a_OtherInt.m_fT1 < a_IntToSet.m_fT1)
    {
        a_IntToSet.m_fT1 = a_OtherInt.m_fT1;
        a_IntToSet.m_vNormal1 = a_OtherInt.m_vNormal1;
    }
}

bool SetIntersectionFromLowestPositive(Intersection & a_Intersection, const Interval & a_Interval)
{
    if (a_Interval.m_fT0 < 0.f && a_Interval.m_fT1 < 0.f)
    {
        return false;
    }

    if (a_Interval.m_fT0 >= 0.f && a_Interval.m_fT1 >= 0.f)
    {
        if (a_Interval.m_fT0 < a_Interval.m_fT1)
        {
            a_Intersection.m_fT = a_Interval.m_fT0;
            a_Intersection.m_vNormal = a_Interval.m_vNormal0;
        }
        else
        {
            a_Intersection.m_fT = a_Interval.m_fT1;
            a_Intersection.m_vNormal = a_Interval.m_vNormal1;
        }
    }
    else if (a_Interval.m_fT0 >= 0.f)
    {
        a_Intersection.m_fT = a_Interval.m_fT0;
        a_Intersection.m_vNormal = a_Interval.m_vNormal0;
    }
    else
    {
        a_Intersection.m_fT = a_Interval.m_fT1;
        a_Intersection.m_vNormal = a_Interval.m_vNormal1;
    }
    return true;
}
