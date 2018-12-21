#pragma once

#ifndef RAY_H
#define RAY_H

class Ray
{
protected:
    Vec3 m_A, m_B;

public:
    Ray();
    Ray(const Vec3& a, const Vec3& b);
    Ray(const Ray& rhs);
    Ray operator=(const Ray& rhs);
    ~Ray();

    inline Vec3 Origin() const { return m_A; }
    inline Vec3 Direction() const { return m_B; }
    
    Vec3 PointAt(const float& a_fT) const;
};

#endif //RAY_H