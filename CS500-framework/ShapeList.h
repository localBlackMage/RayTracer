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
    Shape* GetRandomObject() const;

    bool Hit(const Ray& a_Ray, Intersection& a_Hit, float a_fTMin = MINIMUM, float a_fTMax = INF) const;
    void SampleLight(Intersection& a_Intersection);
    float PDFLight(const Shape* a_pShape) const;
};

#endif //SHAPE_LIST_H