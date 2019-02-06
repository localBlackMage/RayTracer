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

LowestPostiveIntersection FindLowestPositive(float a_fTMin, float a_fTMax, const Interval & a_Interval)
{
    if (a_Interval.m_fT0 < 0.f && a_Interval.m_fT1 < 0.f)
    {
        return {false};
    }

    LowestPostiveIntersection lpi;

    if (a_Interval.m_fT0 >= 0.f && a_Interval.m_fT1 >= 0.f)
    {
        if (a_Interval.m_fT0 < a_Interval.m_fT1)
        {
            lpi.m_bDidIntersect = true;
            lpi.m_fT = a_Interval.m_fT0;
            lpi.m_vNormal = a_Interval.m_vNormal0;
        }
        else
        {
            lpi.m_bDidIntersect = true;
            lpi.m_fT = a_Interval.m_fT1;
            lpi.m_vNormal = a_Interval.m_vNormal1;
        }
    }
    else if (a_Interval.m_fT0 >= 0.f)
    {
        lpi.m_bDidIntersect = true;
        lpi.m_fT = a_Interval.m_fT0;
        lpi.m_vNormal = a_Interval.m_vNormal0;
    }
    else
    {
        lpi.m_bDidIntersect = true;
        lpi.m_fT = a_Interval.m_fT1;
        lpi.m_vNormal = a_Interval.m_vNormal1;
    }

    if (lpi.m_bDidIntersect && a_fTMin > lpi.m_fT || lpi.m_fT > a_fTMax)
    {
        lpi.m_bDidIntersect = false;
    }

    return lpi;
}
