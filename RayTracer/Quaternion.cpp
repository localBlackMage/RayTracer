#include "stdafx.h"

Quaternion::Quaternion() :
    r(1), 
    i(0), 
    j(0), 
    k(0) 
{}

Quaternion::Quaternion(const float & _r, const float & _i, const float & _j, const float & _k) :
    r(_r), 
    i(_i), 
    j(_j), 
    k(_k) 
{}

Quaternion::Quaternion(const Quaternion & rhs) : 
    r(rhs.r),
    i(rhs.i),
    j(rhs.j), 
    k(rhs.k) 
{}

Quaternion & Quaternion::operator=(const Quaternion & rhs)
{
    r = rhs.r;
    i = rhs.i;
    j = rhs.j;
    k = rhs.k;
    return *this;
}

#pragma region Operator Overrides

void Quaternion::operator *=(const Quaternion &multiplier)
{
    r = r*multiplier.r - i*multiplier.i -
        j*multiplier.j - k*multiplier.k;
    i = r*multiplier.i + i*multiplier.r +
        j*multiplier.k - k*multiplier.j;
    j = r*multiplier.j + j*multiplier.r +
        k*multiplier.i - i*multiplier.k;
    k = r*multiplier.k + k*multiplier.r +
        i*multiplier.j - j*multiplier.i;
}

Quaternion Quaternion::operator+(const Quaternion & Q2) const
{
    return Quaternion(
        r + Q2.r,
        i + Q2.i,
        j + Q2.j,
        k + Q2.k
    );
}

Quaternion Quaternion::operator+(const Vec3 & vec) const
{
    Quaternion q = Quaternion(0, vec.x, vec.y, vec.z) * (*this);    
    return Quaternion(
        r + q.r * 0.5f,
        i + q.i * 0.5f,
        j + q.j * 0.5f,
        k + q.k * 0.5f
    );
}

Quaternion Quaternion::operator-(const Quaternion & Q2) const
{
    return Quaternion(
        r - Q2.r,
        i - Q2.i,
        j - Q2.j,
        k - Q2.k
    );
}

Quaternion Quaternion::operator*(const Quaternion & Q2) const
{
    return Quaternion(
        r * Q2.r,
        i * Q2.i,
        j * Q2.j,
        k * Q2.k
    );
}

Quaternion Quaternion::operator*(const float & scalar) const
{
    return Quaternion(
        r * scalar,
        i * scalar,
        j * scalar,
        k * scalar
    );
}

Quaternion Quaternion::operator/(const float & div) const
{
    return Quaternion(
        r / div,
        i / div,
        j / div,
        k / div
    );
}

#pragma endregion

void Quaternion::Normalize()
{
    float d = r * r + i * i + j * j + k * k;

    // Check for zero length quaternion, and use the no-rotation
    // quaternion in that case.
    if (d < FLOAT_EPSILON) {
        r = 1;
        return;
    }

    d = ((float)1.0) / sqrtf(d);
    r *= d;
    i *= d;
    j *= d;
    k *= d;
}

void Quaternion::AddScaledVector(const Vec3& vector, float scale)
{
    Quaternion q(0,
        vector.x * scale,
        vector.y * scale,
        vector.z * scale);
    q *= *this;
    r += q.r * 0.5f;
    i += q.i * 0.5f;
    j += q.j * 0.5f;
    k += q.k * 0.5f;
}

void Quaternion::RotateByVector(const Vec3& vector)
{
    Quaternion q(0, vector.x, vector.y, vector.z);
    (*this) *= q;
}

void Quaternion::Identity()
{
    r = 1;
    i = j = k = 0;
}

float Quaternion::Length() const
{
    return sqrtf(r * r + i * i + j * j + k * k);
}

float Quaternion::Dot(const Quaternion& Q2)
{
    return r * Q2.r + i * Q2.i + j * Q2.j + k * Q2.k;
}

void Quaternion::Conjugate()
{
    i = -i;
    j = -j;
    k = -k;
}

void Quaternion::Negate()
{
    r = -r;
    i = -i;
    j = -j;
    k = -k;
}

Matrix3x3 Quaternion::Matrix()
{
    return Matrix3x3(
        (1.f) - (2.f) * (j * j + k * k), (2.f) * (i * j - k * r), (2.f) * (i * k + j * r),
        (2.f) * (i * j + k * r), (1.f) - (2.f) * (i * i + k * k), (2.f) * (j * k - i * r),
        (2.f) * (i * k - j * r), (2.f) * (j * k + i * r), (1.f) - (2.f) * (i * i + j * j)
    );
}

#pragma region Static Methods

Vec3 Quaternion::QuaternionToVec3(const Quaternion& q)
{
    Vec3 result;
    float ysqr = q.j * q.j;
    float t0 = -2.0f * (ysqr + q.k * q.k) + 1.0f;
    float t1 = +2.0f * (q.i * q.j - q.r * q.k);
    float t2 = -2.0f * (q.i * q.k + q.r * q.j);
    float t3 = +2.0f * (q.j * q.k - q.r * q.i);
    float t4 = -2.0f * (q.i * q.i + ysqr) + 1.0f;

    t2 = t2 > 1.0f ? 1.0f : t2;
    t2 = t2 < -1.0f ? -1.0f : t2;

    result.y = std::asin(t2) * RAD_TO_DEG;
    result.x = std::atan2(t3, t4) * RAD_TO_DEG;
    result.z = std::atan2(t1, t0) * RAD_TO_DEG;
    return result;
}

Quaternion Quaternion::Vec3ToQuaternion(const Vec3& angle)
{
    float x = sin(angle.y / 2.f * DEG_TO_RAD) * sin(angle.z / 2.f * DEG_TO_RAD) * cos(angle.x / 2.f * DEG_TO_RAD) + cos(angle.y / 2.f * DEG_TO_RAD)* cos(angle.z / 2.f * DEG_TO_RAD)* sin(angle.x / 2.f * DEG_TO_RAD);
    float y = sin(angle.y / 2.f * DEG_TO_RAD)* cos(angle.z / 2.f * DEG_TO_RAD)* cos(angle.x / 2.f * DEG_TO_RAD) + cos(angle.y / 2.f * DEG_TO_RAD)* sin(angle.z / 2.f * DEG_TO_RAD)* sin(angle.x / 2.f * DEG_TO_RAD);
    float z = cos(angle.y / 2.f * DEG_TO_RAD)* sin(angle.z / 2.f * DEG_TO_RAD)* cos(angle.x / 2.f * DEG_TO_RAD) - sin(angle.y / 2.f * DEG_TO_RAD)* cos(angle.z / 2.f * DEG_TO_RAD)* sin(angle.x / 2.f * DEG_TO_RAD);
    float w = cos(angle.y / 2.f * DEG_TO_RAD)* cos(angle.z / 2.f * DEG_TO_RAD)* cos(angle.x / 2.f * DEG_TO_RAD) - sin(angle.y / 2.f * DEG_TO_RAD)* sin(angle.z / 2.f * DEG_TO_RAD)* sin(angle.x / 2.f * DEG_TO_RAD);

    return Quaternion(w, x, y, z);
}

Quaternion Quaternion::IdentityQuaterion()
{
    return Quaternion(1.f, 0.f, 0.f, 0.f);
}

Quaternion Quaternion::ScalarMult(Quaternion Q, float value)
{
    return Quaternion(
        Q.r * value,
        Q.i * value,
        Q.j * value,
        Q.k * value
    );
}

Quaternion Quaternion::ScalarDiv(Quaternion Q, float value)
{
    return Quaternion(
        Q.r / value,
        Q.i / value,
        Q.j / value,
        Q.k / value
    );
}

void Quaternion::Conjugate(Quaternion& Q)
{
    Q.i = -Q.i;
    Q.j = -Q.j;
    Q.k = -Q.k;
}

float Quaternion::Dot(Quaternion Q1, Quaternion Q2)
{
    return Q1.r * Q2.r + Q1.i * Q2.i + Q1.j * Q2.j + Q1.k * Q2.k;
}

float Quaternion::Length(const Quaternion& Q)
{
    return Q.Length();
}

Quaternion Quaternion::Inverse(Quaternion Q)
{
    float divided = Q.r * Q.r + Q.i * Q.i + Q.j * Q.j + Q.k * Q.k;

    Q.r = Q.r / divided;
    Q.i = -Q.i / divided;
    Q.j = -Q.j / divided;
    Q.k = -Q.k / divided;

    return Q;
}

#pragma endregion
