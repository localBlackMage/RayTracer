#ifndef Quaternion_H
#define Quaternion_H

class Quaternion
{
public:
    //float r, i, j, k;
    //! w,x,y,z components of the quaternion
    float w, x, y, z;

    Quaternion() : w(1.0), x(), y(), z() {}
    Quaternion(float pw, float px, float py, float pz)
        : w(pw), x(px), y(py), z(pz) {}
    Quaternion(const Quaternion & rhs);
    Quaternion& operator= (const Quaternion& rhs);
    ~Quaternion() {};

    void operator *=(const Quaternion &multiplier);
    Quaternion operator+ (const Quaternion& Q2) const;
    Quaternion operator+ (const Vec3& vec) const;
    Quaternion operator- (const Quaternion& Q2) const;
    Quaternion operator* (const Quaternion& Q2) const;
    Quaternion operator* (const float& scalar) const;
    Quaternion operator/ (const float& div) const;

    Quaternion& Normalize();
    void AddScaledVector(const Vec3& vector, float scale);
    void RotateByVector(const Vec3& vector);
    void Identity();
    float Length() const;
    float Dot(const Quaternion& Q2);
    Quaternion& Conjugate();
    void Negate();
    Vec3 RotateVector(const Vec3& vector) const;
    Matrix3x3 Matrix();

#pragma region Static Methods
    static Quaternion FromEulerAnglesRadians(float a_fYaw, float a_fPitch, float a_fRoll);
    static Quaternion FromEulerAnglesDegrees(float a_fYaw, float a_fPitch, float a_fRoll);
    // Returns a Vec3 representation of a given Quaternion with angles measured in degrees
    static Vec3 QuaternionToVec3(const Quaternion& q);
    static Quaternion Vec3ToQuaternion(const Vec3& angle);
    static Quaternion IdentityQuaterion();
    static Quaternion ScalarMult(Quaternion Q, float value);
    static Quaternion ScalarDiv(Quaternion Q, float value);
    static void Conjugate(Quaternion & Q);
    static float Dot(Quaternion Q1, Quaternion Q2);
    static float Length(const Quaternion& Q);
    static Quaternion Inverse(Quaternion Q);
    static void Interpolate(Quaternion& pOut, const Quaternion& pStart, const Quaternion& pEnd, float pFactor);
    static Quaternion FromTwoVectors(const Vec3& a_vA, const Vec3& a_vB);
#pragma endregion
};
#endif