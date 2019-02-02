#include "stdafx.h"

Shape::Shape(Material * a_pMaterial/* = nullptr*/) :
    m_pMaterial(a_pMaterial),
    m_pBoundingBox(nullptr)
{}

Shape::~Shape()
{
    delete m_pBoundingBox;
}
