#pragma once

#ifndef RAY_H
#define RAY_H

class Ray
{
protected:
    Vector3f m_vOrigin, m_vDirection;

public:
    Ray();
    Ray(const Vector3f & a_vOrigin, const Vector3f & a_vDirection);
    Ray(const Ray& rhs);
    Ray operator=(const Ray& rhs);
    ~Ray();

    inline const Vector3f& Origin() const { return m_vOrigin; }
    inline const Vector3f& Direction() const { return m_vDirection; }
    
    Vector3f PointAt(const float& a_fT) const;
};

#endif //RAY_H