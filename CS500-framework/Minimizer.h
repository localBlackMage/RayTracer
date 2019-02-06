#pragma once

#ifndef MINIMIZER_H
#define MINIMIZER_H

bool PointInsideBBox(const Bbox& box, const Vector3f& point);

class Minimizer {
public:
    typedef float Scalar; // KdBVH needs Minimizer::Scalar defined
    Ray m_Ray;
    // ... Stuff to track the minimal t and its intersection info
    float m_fT;
    Intersection m_HitData;
    
    Minimizer(const Ray& a_Ray) :
        m_Ray(a_Ray),
        m_fT(INF),
        m_HitData(Intersection())
    {}
    
    // Called by BVMinimize to intersect the ray with a Shape.  This
    // should return the intersection t, but should also track
    // the minimum t and it's corresponding intersection info.
    // Return INF to indicate no intersection.
    Scalar minimumOnObject(Shape* obj);
    
    // Called by BVMinimize to intersect the ray with a Bbox and
    // returns the t value.  This should be similar to the already
    // written box (3 slab) intersection.  (The difference being: a                     
    // distance of zero should be returned if the ray starts within the Bbox.)
    // Return INF to indicate no intersection.
    Scalar minimumOnVolume(const Bbox& box);
};

#endif //MINIMIZER_H