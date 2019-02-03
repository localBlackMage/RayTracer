#pragma once

#ifndef SHAPE_LIST_H
#define SHAPE_LIST_H

class Shape;

class ShapeList
{
protected:
    std::vector<Shape*> m_ShapeList;

public:
    ShapeList() {};
    ~ShapeList() {};

    void AddShape(Shape* a_pShape);

    bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

#endif //SHAPE_LIST_H