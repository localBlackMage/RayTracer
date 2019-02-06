#include "stdafx.h"
#include "ShapeList.h"

void ShapeList::AddShape(Shape * a_pShape)
{
    m_ShapeList.push_back(a_pShape);
}

void ShapeList::CreateTree()
{
    m_ShapeList.shrink_to_fit();
    m_Tree = KDTree(m_ShapeList.begin(), m_ShapeList.end());
}

bool ShapeList::Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const
{
    //Intersection hData;
    //bool hitAnything = false;
    //float closestSoFar = a_fTMax;
    //uint32 uNumShapes = uint32(m_ShapeList.size());
    //for (uint32 i = 0; i < uNumShapes; ++i)
    //{
    //    if (m_ShapeList[i]->Hit(a_Ray, a_fTMin, closestSoFar, hData))
    //    {
    //        hitAnything = true;
    //        closestSoFar = hData.m_fT;
    //        a_Hit = hData;
    //    }
    //}
    //return hitAnything;

    Minimizer minimizer(a_Ray);
    float minDist = BVMinimize(m_Tree, minimizer);
    if (minDist >= 0.f && minDist < INF)
    {
        a_Hit = minimizer.m_HitData;
        return true;
    }
    return false;
}
