#pragma once

#ifndef SHAPE_LIST_H
#define SHAPE_LIST_H

class ShapeList : 
    public Shape
{
protected:
    Shape** m_ShapeList;
    uint32 m_uListSize;

public:
    ShapeList() {};
    ShapeList(Shape ** a_ShapeList, uint32 a_uNumShapes) :
        m_ShapeList(a_ShapeList),
        m_uListSize(a_uNumShapes)
    {}

    virtual bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

#endif //SHAPE_LIST_H