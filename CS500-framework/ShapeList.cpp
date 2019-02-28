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

Shape * ShapeList::GetRandomObject() const
{
    uint32 index = RandomUInt(0, uint32(m_ShapeList.size()));
    return m_ShapeList[index];
}

bool ShapeList::Hit(const Ray& a_Ray, Intersection& a_Hit, float a_fTMin/* = MINIMUM*/, float a_fTMax/* = INF*/) const
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
    if (minDist >= a_fTMin && minDist < a_fTMax)
    {
        a_Hit = minimizer.m_HitData;
        return true;
    }
    return false;
}

void ShapeList::SampleLight(Intersection& a_Intersection)
{
    Shape * pShape = GetRandomObject();
    pShape->GetRandomIntersectionPoint(a_Intersection);
}

float ShapeList::PDFLight(const Shape* a_pShape) const
{
    return 1.f / (a_pShape->Area() * float(m_ShapeList.size()));
}
