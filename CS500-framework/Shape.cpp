#include "stdafx.h"

Shape::Shape(Material * a_pMaterial/* = nullptr*/) :
    m_pMaterial(a_pMaterial)
{}

Shape::~Shape()
{
    delete m_pMaterial;
}

Bbox bounding_box(const Shape * obj)
{
    return obj->GetBoundingBox();
}
