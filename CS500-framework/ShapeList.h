#pragma once

#ifndef SHAPE_LIST_H
#define SHAPE_LIST_H

class Shape;

class ShapeList
{
protected:
    typedef KdBVH<float, 3, Shape*> KDTree;

    std::vector<Shape*> m_ShapeList;
    KDTree m_Tree;

public:
    ShapeList() {};
    ~ShapeList() {};

    void AddShape(Shape* a_pShape);
    uint32 NumShapes() const { return m_ShapeList.size(); }
    void CreateTree();

    bool Hit(const Ray& a_Ray, float a_fTMin, float a_fTMax, Intersection& a_Hit) const;
};

#endif //SHAPE_LIST_H