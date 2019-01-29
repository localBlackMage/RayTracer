#pragma once

#ifndef RAY_H
#define RAY_H

class Ray
{
protected:
    Vec3 m_vOrigin, m_vDirection;

public:
    Ray();
    Ray(const Vec3 & a_vOrigin, const Vec3 & a_vDirection);
    Ray(const Ray& rhs);
    Ray operator=(const Ray& rhs);
    ~Ray();

    inline const Vec3& Origin() const { return m_vOrigin; }
    inline const Vec3& Direction() const { return m_vDirection; }
    
    Vec3 PointAt(const float& a_fT) const;
};

#endif //RAY_H