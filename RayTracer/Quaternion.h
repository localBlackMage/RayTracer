#ifndef Quaternion_H
#define Quaternion_H

class Quaternion
{
public:
    float r, i, j, k;

    Quaternion();
    Quaternion(const float& _r, const float& _i, const float& _j, const float& _k);
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

    void Normalize();
    void AddScaledVector(const Vec3& vector, float scale);
    void RotateByVector(const Vec3& vector);
    void Identity();
    float Length() const;
    float Dot(const Quaternion& Q2);
    void Conjugate();
    void Negate();
    Matrix3x3 Matrix();

#pragma region Static Methods
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
#pragma endregion
};
#endif