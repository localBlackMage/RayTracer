#include "stdafx.h"

Quaternion::Quaternion(const Quaternion & rhs) : 
    w(rhs.w),
    x(rhs.x),
    y(rhs.y), 
    z(rhs.z) 
{}

Quaternion & Quaternion::operator=(const Quaternion & rhs)
{
    w = rhs.w;
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

#pragma region Operator Overrides

void Quaternion::operator *=(const Quaternion &multiplier)
{
    Quaternion q(
        w*multiplier.w - x * multiplier.x - y * multiplier.y - z * multiplier.z,
        w*multiplier.x + x * multiplier.w + y * multiplier.z - z * multiplier.y,
        w*multiplier.y + y * multiplier.w + z * multiplier.x - x * multiplier.z,
        w*multiplier.z + z * multiplier.w + x * multiplier.y - y * multiplier.x
    );
    
    w = q.w;
    x = q.x;
    y = q.y;
    z = q.z;
}

Quaternion Quaternion::operator+(const Quaternion & Q2) const
{
    return Quaternion(
        w + Q2.w,
        x + Q2.x,
        y + Q2.y,
        z + Q2.z
    );
}

Quaternion Quaternion::operator+(const Vec3 & vec) const
{
    Quaternion q = Quaternion(0, vec.x, vec.y, vec.z) * (*this);    
    return Quaternion(
        w + q.w * 0.5f,
        x + q.x * 0.5f,
        y + q.y * 0.5f,
        z + q.z * 0.5f
    );
}

Quaternion Quaternion::operator-(const Quaternion & Q2) const
{
    return Quaternion(
        w - Q2.w,
        x - Q2.x,
        y - Q2.y,
        z - Q2.z
    );
}

Quaternion Quaternion::operator*(const Quaternion & Q2) const
{
    return Quaternion(
        w*Q2.w - x * Q2.x - y * Q2.y - y * Q2.y,
        w*Q2.x + x * Q2.w + y * Q2.y - y * Q2.y,
        w*Q2.y + y * Q2.w + y * Q2.x - x * Q2.y,
        w*Q2.y + y * Q2.w + x * Q2.y - y * Q2.x
    );
}

Quaternion Quaternion::operator*(const float & scalar) const
{
    return Quaternion(
        w * scalar,
        x * scalar,
        y * scalar,
        z * scalar
    );
}

Quaternion Quaternion::operator/(const float & div) const
{
    return Quaternion(
        w / div,
        x / div,
        y / div,
        z / div
    );
}

#pragma endregion

Quaternion& Quaternion::Normalize()
{
    // compute the magnitude and divide through it
    const float mag = sqrt(x*x + y * y + z * z + w * w);
    if (mag)
    {
        const float invMag = 1.f / mag;
        x *= invMag;
        y *= invMag;
        z *= invMag;
        w *= invMag;
    }
    return *this;
}

void Quaternion::AddScaledVector(const Vec3& vector, float scale)
{
    Quaternion q(0,
        vector.x * scale,
        vector.y * scale,
        vector.z * scale);
    q *= *this;
    w += q.w * 0.5f;
    x += q.x * 0.5f;
    y += q.y * 0.5f;
    z += q.z * 0.5f;
}

void Quaternion::RotateByVector(const Vec3& vector)
{
    Quaternion q(0, vector.x, vector.y, vector.z);
    (*this) *= q;
}

void Quaternion::Identity()
{
    w = 1;
    x = y = z = 0;
}

float Quaternion::Length() const
{
    return sqrtf(w * w + x * x + y * y + z * z);
}

float Quaternion::Dot(const Quaternion& Q2)
{
    return w * Q2.w + x * Q2.x + y * Q2.y + z * Q2.z;
}

Quaternion& Quaternion::Conjugate()
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

void Quaternion::Negate()
{
    w = -w;
    x = -x;
    y = -y;
    z = -z;
}

Vec3 Quaternion::RotateVector(const Vec3 & vector) const
{
    Quaternion q2(0.f, vector.x, vector.y, vector.z), q = *this, qinv = q;
    q.Conjugate();

    q = q * q2 * qinv;
    return Vec3(q.x, q.y, q.z, vector.w);
}

Matrix3x3 Quaternion::Matrix()
{
    return Matrix3x3(
        (1.f) - (2.f) * (y * y + z * z), (2.f) * (x * y - z * w), (2.f) * (x * z + y * w),
        (2.f) * (x * y + z * w), (1.f) - (2.f) * (x * x + z * z), (2.f) * (y * z - x * w),
        (2.f) * (x * z - y * w), (2.f) * (y * z + x * w), (1.f) - (2.f) * (x * x + y * y)
    );
}

#pragma region Static Methods

Quaternion Quaternion::FromEulerAnglesRadians(float a_fYaw, float a_fPitch, float a_fRoll)
{
    // Abbreviations for the various angular functions
    float cy = cosf(a_fYaw * 0.5f);
    float sy = sinf(a_fYaw * 0.5f);
    float cp = cosf(a_fPitch * 0.5f);
    float sp = sinf(a_fPitch * 0.5f);
    float cr = cosf(a_fRoll * 0.5f);
    float sr = sinf(a_fRoll * 0.5f);

    return Quaternion(
        cy * cp * cr + sy * sp * sr, // w
        cy * cp * sr - sy * sp * cr, // x 
        sy * cp * sr + cy * sp * cr, // y
        sy * cp * cr - cy * sp * sr  // z
    ).Normalize();
}

Quaternion Quaternion::FromEulerAnglesDegrees(float a_fYaw, float a_fPitch, float a_fRoll)
{
    return FromEulerAnglesRadians(a_fYaw * DEG_TO_RAD, a_fPitch * DEG_TO_RAD, a_fRoll * DEG_TO_RAD);
}

Vec3 Quaternion::QuaternionToVec3(const Quaternion& q)
{
    Vec3 result;
    float ysqr = q.y * q.y;
    float t0 = -2.0f * (ysqr + q.z * q.z) + 1.0f;
    float t1 = +2.0f * (q.x * q.y - q.w * q.z);
    float t2 = -2.0f * (q.x * q.z + q.w * q.y);
    float t3 = +2.0f * (q.y * q.z - q.w * q.x);
    float t4 = -2.0f * (q.x * q.x + ysqr) + 1.0f;

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
        Q.w * value,
        Q.x * value,
        Q.y * value,
        Q.z * value
    );
}

Quaternion Quaternion::ScalarDiv(Quaternion Q, float value)
{
    return Quaternion(
        Q.w / value,
        Q.x / value,
        Q.y / value,
        Q.z / value
    );
}

void Quaternion::Conjugate(Quaternion& Q)
{
    Q.x = -Q.x;
    Q.y = -Q.y;
    Q.z = -Q.z;
}

float Quaternion::Dot(Quaternion Q1, Quaternion Q2)
{
    return Q1.w * Q2.w + Q1.x * Q2.x + Q1.y * Q2.y + Q1.z * Q2.z;
}

float Quaternion::Length(const Quaternion& Q)
{
    return Q.Length();
}

Quaternion Quaternion::Inverse(Quaternion Q)
{
    float divided = Q.w * Q.w + Q.x * Q.x + Q.y * Q.y + Q.z * Q.z;

    Q.w = Q.w / divided;
    Q.x = -Q.x / divided;
    Q.y = -Q.y / divided;
    Q.z = -Q.z / divided;

    return Q;
}

void Quaternion::Interpolate(Quaternion & pOut, const Quaternion & pStart, const Quaternion & pEnd, float pFactor)
{
    // calc cosine theta
    float cosom = pStart.x * pEnd.x + pStart.y * pEnd.y + pStart.z * pEnd.z + pStart.w * pEnd.w;

    // adjust signs (if necessary)
    Quaternion end = pEnd;
    if (cosom < 0.f)
    {
        cosom = -cosom;
        end.x = -end.x;   // Reverse all signs
        end.y = -end.y;
        end.z = -end.z;
        end.w = -end.w;
    }

    // Calculate coefficients
    float sclp, sclq;
    if ((1.f - cosom) > 0.0001f) // 0.0001 -> some epsillon
    {
        // Standard case (slerp)
        float omega, sinom;
        omega = acos(cosom); // extract theta from dot product's cos theta
        sinom = sin(omega);
        sclp = sin((1.f - pFactor) * omega) / sinom;
        sclq = sin(pFactor * omega) / sinom;
    }
    else
    {
        // Very close, do linear interp (because it's faster)
        sclp = 1.f - pFactor;
        sclq = pFactor;
    }

    pOut.x = sclp * pStart.x + sclq * end.x;
    pOut.y = sclp * pStart.y + sclq * end.y;
    pOut.z = sclp * pStart.z + sclq * end.z;
    pOut.w = sclp * pStart.w + sclq * end.w;
}

Quaternion Quaternion::FromTwoVectors(const Vec3 & a_vA, const Vec3 & a_vB)
{
    Vec3 a = a_vA, b = a_vB;
    Vec3 v0 = a.Normalize();
    Vec3 v1 = b.Normalize();
    float c = v1.Dot(v0);

    // if dot == -1, vectors are nearly opposites
    // => accurately compute the rotation axis by computing the
    //    intersection of the two planes. This is done by solving:
    //       x^T v0 = 0
    //       x^T v1 = 0
    //    under the constraint:
    //       ||x|| = 1
    //    which yields a singular value problem
    if (c < -1.f + FLOAT_EPSILON)
    {
        c = numext::maxi(c, -1));
        Matrix<Scalar, 2, 3> m; m << v0.transpose(), v1.transpose();
        JacobiSVD<Matrix<Scalar, 2, 3> > svd(m, ComputeFullV);
        Vec3 axis = svd.matrixV().col(2);

        float w2 = (1.f + c) * 0.5f;
        this->w() = sqrtf(w2);
        this->vec() = axis * sqrtf(1.f) - w2);
        return derived();
    }
    Vec3 axis = v0.Cross(v1);
    float s = sqrtf(1.f + c)*2.f);
    float invs = 1.f / s;
    this->vec() = axis * invs;
    this->w = s * 0.5f;

    return derived();
}

#pragma endregion
