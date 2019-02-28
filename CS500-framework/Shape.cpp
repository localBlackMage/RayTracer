#include "stdafx.h"
#include "Shape.h"

Shape::Shape(Material * a_pMaterial/* = nullptr*/, float a_fArea/* = 0.f*/) :
    m_pMaterial(a_pMaterial),
    m_fArea(a_fArea)
{}

Shape::~Shape()
{
    delete m_pMaterial;
}

Bbox bounding_box(const Shape * obj)
{
    return obj->GetBoundingBox();
}
