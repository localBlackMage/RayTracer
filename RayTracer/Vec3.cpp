#include "stdafx.h"

Vec3::Vec3() : 
    x(0.f), 
    y(0.f), 
    z(0.f), 
    w(1.f) 
{ }

Vec3::Vec3(const Vec3 & vec, const float & _w) : 
    x(vec.x), 
    y(vec.y),
    z(vec.z), 
    w(_w) 
{ }

Vec3::Vec3(const float& _x, const float& _y, const float& _z, const float& _w/* = 1.f*/) : 
    x(_x), 
    y(_y),
    z(_z),
    w(_w) 
{ }

Vec3::Vec3(const Vec3 & rhs) : 
    x(rhs.x), 
    y(rhs.y), 
    z(rhs.z), 
    w(rhs.w) 
{ }

Vec3& Vec3::operator=(const Vec3& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
}

Vec3::~Vec3() { }

void Vec3::Set(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

void Vec3::Set(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

#pragma region Operator Overrides
Vec3::operator float*()
{
    return &(x);
}

bool Vec3::operator==(const Vec3& other) const
{
    double d = 0.0f;

    d += fabs(x - other.x);
    d += fabs(y - other.y);
    d += fabs(z - other.z);
    d += fabs(w - other.w);

    return d < EPSILON;
}

bool Vec3::operator!=(const Vec3& other) const
{
    double d = 0.0f;

    d += fabs(x - other.x);
    d += fabs(y - other.y);
    d += fabs(z - other.z);
    d += fabs(w - other.w);

    return d >= EPSILON;
}

Vec3 Vec3::operator+(const Vec3& other) const
{
    return Vec3(
        x + other.x,
        y + other.y,
        z + other.z
    );
}

Vec3 & Vec3::operator+=(const Vec3 & other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3 Vec3::operator-(const Vec3& other) const
{
    return Vec3(
        x - other.x,
        y - other.y,
        z - other.z
    );
}

Vec3 & Vec3::operator-=(const Vec3 & other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vec3 Vec3::operator*(const float scalar) const
{
    return Vec3(
        x * scalar,
        y * scalar,
        z * scalar
    );
}

Vec3 Vec3::operator*(const Vec3 & other) const
{
    return Vec3(x * other.x, y * other.y, z * other.z, 0.f);
}

Vec3 Vec3::operator/(const float divisor) const
{
    return Vec3(
        x / divisor,
        y / divisor,
        z / divisor
    );
}

Vec3 Vec3::operator/(const Vec3 & other) const
{
    return Vec3(x / other.x, y / other.y, z / other.z, 0.f);
}

Vec3 & Vec3::operator/=(const float divisor)
{
    x /= divisor;
    y /= divisor;
    z /= divisor;
    return *this;
}

float Vec3::operator[](const int idx) const
{
    return *(&x + idx);
}

float& Vec3::operator[](const int idx)
{
    return *(&x + idx);
}
#pragma endregion

void Vec3::Add(const Vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}

void Vec3::Sub(const Vec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

void Vec3::Mul(const float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

void Vec3::Div(const float divisor)
{
    x /= divisor;
    y /= divisor;
    z /= divisor;
}

void Vec3::Print() const
{
    std::cout << "<X: " << x << ", Y: " << y << ", Z: " << z << ", W: " << w << ">" << std::endl;
}

void Vec3::FillValues(float & _x, float & _y, float & _z)
{
    _x = x;
    _y = y;
    _z = z;
}

void Vec3::Zero()
{
    x = y = z = 0.0f;
}

bool Vec3::IsVectorZero(float error) const {
    return (fabsf(x) < error && fabsf(y) < error && fabsf(z) < error);
}

void Vec3::Negate()
{
    x = -x;
    y = -y;
    z = -z;
}

float Vec3::SquareLength() const
{
    return x * x + y * y + z * z;
}

float Vec3::Length() const
{
    return sqrtf(SquareLength());
}

void Vec3::Normalize()
{
    if (x == 0 && y == 0 && z == 0)
        return;
    Div(Length());
}

float Vec3::AngleRadians() const {
    return atan2f(y, x);
}

float Vec3::AngleDegrees() const {
    return AngleRadians() * RAD_TO_DEG;
}

#pragma region Static Methods
float Vec3::SquareDistance(const Vec3& vector0, const Vec3& vector1)
{
    float x = vector1.x - vector0.x;
    float y = vector1.y - vector0.y;
    float z = vector1.z - vector0.z;
    return x * x + y * y + z * z;
}

float Vec3::Distance(const Vec3& vector0, const Vec3& vector1)
{
    return sqrtf(SquareDistance(vector0, vector1));
}

Vec3 Vec3::Normalize(const Vec3& vector)
{
    float length = vector.Length();
    if (length == 0.0f)
        return Vec3();
    return vector / length;
}

float Vec3::Dot(const Vec3& vector0, const Vec3& vector1)
{
    return vector0.x * vector1.x + vector0.y * vector1.y + vector0.z * vector1.z;
}

Vec3 Vec3::Cross(const Vec3& vector0, const Vec3& vector1)
{
    return Vec3(
        vector0.y * vector1.z - vector0.z * vector1.y,
        vector0.z * vector1.x - vector0.x * vector1.z,
        vector0.x * vector1.y - vector0.y * vector1.x,
        0.f
    );
}

Vec3 Vec3::AngleRadians(float radians, Vec3& axis)
{
    axis.Print();
    std::cout << "Radians: " << radians << std::endl;
    return Vec3();
}

Vec3 Vec3::AngleDegrees(float degrees, Vec3& axis)
{
    return AngleRadians(degrees * DEG_TO_RAD, axis);
}

Vec3 Vec3::VectorFromAngleDegrees(float degrees)
{
    float rad = degrees * DEG_TO_RAD;
    return Vec3(cosf(rad), sinf(rad), 0);
}
#pragma endregion

Vec3 operator*(const float scalar, const Vec3& other)
{
    return Vec3(
        other.x * scalar,
        other.y * scalar,
        other.z * scalar,
        other.w * scalar
    );
}

std::ostream & operator<<(std::ostream & out, const Vec3 & vec)
{
    out << "X: " << vec.x << ", Y: " << vec.y << ", Z: " << vec.z;
    return out;
}

#if TEST_MODE
void Vec3Tests()
{
    std::cout << "\n========== Running Vec3 tests ==========\n\n";

    Vec3 * createdVector = new Vec3();
    std::cout << "Created Vector(): " << ((createdVector->x == 0.0f && createdVector->y == 0.0f && createdVector->w == 1.0f) ? PASS : FAIL) << std::endl;
    delete createdVector;

    createdVector = new Vec3(1.0f, 2.0f, 3.0f);
    std::cout << "Created Vector(x, y): " << ((createdVector->x == 1.0f && createdVector->y == 2.0f && createdVector->z == 3.0f && createdVector->w == 1.0f) ? PASS : FAIL) << std::endl;
    delete createdVector;

    createdVector = new Vec3(2.0f, 3.0f, 4.0f, 0.0f);
    std::cout << "Created Vector(x, y, w): " << ((createdVector->x == 2.0f && createdVector->y == 3.0f && createdVector->z == 4.0f && createdVector->w == 0.0f) ? PASS : FAIL) << std::endl;
    delete createdVector;

    Vec3 v1, v2, v3, result;
    float scalar;

    v1.Set(1.0f, 2.0f, 3.0f);
    v2.Set(1.0f, 2.0f, 3.0f);
    std::cout << "Vec3 == equal: " << ((v1 == v2) ? PASS : FAIL) << std::endl;

    v2.x = 1.1f;
    std::cout << "Vec3 == not equal: " << ((v1 == v2) ? FAIL : PASS);

    v2.Set(2.0f, 3.0f, 4.0f);
    std::cout << "Vec3 != not equal: " << ((v1 != v2) ? PASS : FAIL) << std::endl;

    v2.Set(1.0f, 2.0f, 3.0f);
    std::cout << "Vec3 != equal: " << ((v1 != v2) ? FAIL : PASS);

    v1.Set(0.1f, 2.0f, 1.0f);
    v2.Set(1.0f, 3.5f, -3.0f);
    result.Set(1.1f, 5.5f, -2.0f);
    std::cout << "Vec3 +: " << ((v1 + v2 == result) ? PASS : FAIL) << std::endl;

    v1.Set(-0.1f, 1.0f, -1.0f);
    v2.Set(1.0f, -2.0f, 1.0f);
    result.Set(0.9f, -1.0f, 0.0f);
    std::cout << "Vec3 +: " << ((v1 + v2 == result) ? PASS : FAIL) << std::endl;

    v1.Set(1.0f, 2.0f, -1.0f);
    v2.Set(1.0f, -2.0f, -1.0f);
    result.Set(0.0f, 4.0f, 0.0f);
    std::cout << "Vec3 -: " << ((v1 - v2 == result) ? PASS : FAIL) << std::endl;

    v1.Set(-2.0f, 2.5f, 1.0f);
    v2.Set(-2.0f, 2.0f, -1.0f);
    result.Set(0.0f, 0.5f, 2.0f);
    std::cout << "Vec3 -: " << ((v1 - v2 == result) ? PASS : FAIL) << std::endl;

    v1.Set(-2.0f, 2.5f, 1.0f);
    scalar = 2.0f;
    result.Set(-4.0f, 5.0f, 2.0f);
    std::cout << "Vec3 *: " << ((v1 * scalar == result) ? PASS : FAIL) << std::endl;

    v1.Set(-2.0f, 2.5f, 1.0f);
    scalar = 0.5f;
    result.Set(-1.0f, 1.25f, 0.5f);
    std::cout << "Vec3 *: " << ((v1 * scalar == result) ? PASS : FAIL) << std::endl;

    v1.Set(-2.0f, 10.0f, 4.5f);
    scalar = 2.0f;
    result.Set(-1.0f, 5.0f, 2.25f);
    std::cout << "Vec3 /: " << ((v1 / scalar == result) ? PASS : FAIL) << std::endl;

    v1.Set(-2.0f, 10.0f, 1.0f);
    scalar = 0.5f;
    result.Set(-4.0f, 20.0f, 2.0f);
    std::cout << "Vec3 /: " << ((v1 / scalar == result) ? PASS : FAIL) << std::endl;

    v1.Set(0.1f, 2.0f, 1.0f);
    v2.Set(1.0f, 3.5f, -3.0f);
    result.Set(1.1f, 5.5f, -2.0f);
    v1.Add(v2);
    std::cout << "Vec3 Add: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(-0.1f, 1.0f, -1.0f);
    v2.Set(1.0f, -2.0f, 1.0f);
    result.Set(0.9f, -1.0f, 0.0f);
    v1.Add(v2);
    std::cout << "Vec3 Add: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(1.0f, 2.0f, -1.0f);
    v2.Set(1.0f, -2.0f, -1.0f);
    result.Set(0.0f, 4.0f, 0.0f);
    v1.Sub(v2);
    std::cout << "Vec3 Sub: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(-2.0f, 2.5f, 1.0f);
    v2.Set(-2.0f, 2.0f, -1.0f);
    result.Set(0.0f, 0.5f, 2.0f);
    v1.Sub(v2);
    std::cout << "Vec3 Sub: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(-2.0f, 2.5f, 1.0f);
    scalar = 2.0f;
    result.Set(-4.0f, 5.0f, 2.0f);
    v1.Mul(scalar);
    std::cout << "Vec3 Mul: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(-2.0f, 2.5f, 1.0f);
    scalar = 0.5f;
    result.Set(-1.0f, 1.25f, 0.5f);
    v1.Mul(scalar);
    std::cout << "Vec3 Mul: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(-2.0f, 10.0f, 4.5f);
    scalar = 2.0f;
    result.Set(-1.0f, 5.0f, 2.25f);
    v1.Div(scalar);
    std::cout << "Vec3 Div: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(-2.0f, 10.0f, 1.0f);
    scalar = 0.5f;
    result.Set(-4.0f, 20.0f, 2.0f);
    v1.Div(scalar);
    std::cout << "Vec3 Div: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(1.0f, 1.0f, 1.0f);
    result.Set(0.0f, 0.0f, 0.0f);
    v1.Zero();
    std::cout << "Vec3 Zero: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(0.0f, 0.0f, 0.0f);
    result.Set(1.0f, 2.0f, 3.0f);
    v1.Set(1.0f, 2.0f, 3.0f);
    std::cout << "Vec3 Set(x, y, z): " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(0.0f, 0.0f, 0.0f, 0.0f);
    result.Set(1.0f, 2.0f, 3.0f, 1.0f);
    v1.Set(1.0f, 2.0f, 3.0f, 1.0f);
    std::cout << "Vec3 Set(x, y, z, w): " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(1.0f, 2.0f, -3.0f, 1.0f);
    result.Set(-1.0f, -2.0f, 3.0f, 1.0f);
    v1.Negate();
    std::cout << "Vec3 Negate: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(1.0f, 0.0f, -3.0f, 1.0f);
    result.Set(-1.0f, 0.0f, 3.0f, 1.0f);
    v1.Negate();
    std::cout << "Vec3 Negate: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(-3.0f, 4.0f, 5.0f);
    std::cout << "Vec3 SquareLength: " << ((v1.SquareLength() == 50.0f) ? PASS : FAIL) << std::endl;

    v1.Set(-4.0f, 3.0f, -5.0f);
    std::cout << "Vec3 Length: " << ((v1.Length() == 7.0710678f) ? PASS : FAIL) << std::endl;

    v1.Set(-3.0f, 4.0f, 5.0f);
    v2.Set(3.0f, -4.0f, -5.0f);
    std::cout << "Vec3 SquareDistance: " << ((Vec3::SquareDistance(v1, v2) == 200.0f) ? PASS : FAIL) << std::endl;

    v1.Set(-3.0f, 4.0f, 5.0f);
    v2.Set(3.0f, -4.0f, -5.0f);
    std::cout << "Vec3 Distance: " << (((Vec3::Distance(v1, v2) - 14.1421356f) < EPSILON) ? PASS : FAIL) << std::endl;

    v1.Set(-3.0f, 4.0f, 5.0f);
    result.Set(-0.424264f, 0.565685f, 0.707107f);
    v1.Normalize();
    std::cout << "Vec3 Normalize: " << ((v1 == result) ? PASS : FAIL) << std::endl;

    v1.Set(-3.0f, 4.0f, -5.0f);
    v1.Normalize();
    std::cout << "Vec3 Normalize Length Check: " << ((v1.Length() == 1.0f) ? PASS : FAIL) << std::endl;

    v1.Set(-3.0f, 4.0f, 5.0f);
    result.Set(-0.424264f, 0.565685f, 0.707107f);
    std::cout << "Vec3 Normalize(vector): " << ((Vec3::Normalize(v1) == result) ? PASS : FAIL) << std::endl;

    v1.Set(-3.0f, 4.0f, -5.0f);
    std::cout << "Vec3 Normalize(vector) Length Check: " << ((Vec3::Normalize(v1).Length() == 1.0f) ? PASS : FAIL) << std::endl;

    v1.Set(2.0f, 3.0f, 3.0f);
    v2.Set(4.0f, 5.0f, 3.0f);
    std::cout << "Vec3 Dot: " << (((Vec3::Dot(v1, v2) - 32.0f) < EPSILON) ? PASS : FAIL) << std::endl;

    v1.Set(1.0f, 0.0f, 0.0f);
    v2.Set(0.0f, 1.0f, 0.0f);
    result.Set(0.0f, 0.0f, 1.0f);
    std::cout << "Vec3 Cross: " << ((Vec3::Cross(v1, v2) == result) ? PASS : FAIL) << std::endl;

    v1.Set(1.0f, 0.0f, 0.0f);
    v2.Set(0.0f, 0.0f, -1.0f);
    result.Set(0.0f, 1.0f, 0.0f);
    std::cout << "Vec3 Cross: " << ((Vec3::Cross(v1, v2) == result) ? PASS : FAIL) << std::endl;

    v1.Set(0.0f, 1.0f, 0.0f);
    v2.Set(0.0f, 0.0f, 1.0f);
    result.Set(1.0f, 0.0f, 0.0f);
    std::cout << "Vec3 Cross: " << ((Vec3::Cross(v1, v2) == result) ? PASS : FAIL) << std::endl;

#pragma region Rotation Tests

    //result.x = 0.707106f;	result.y = 0.707106f;	result.w = 1.0f;
    //angle = M_PI_4;
    //std::cout << "Vec3 AngleRadians (%f): %s\n", angle, (Vec3::AngleRadians(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = 0.0f;	result.y = 1.0f;	result.w = 1.0f;
    //angle = M_PI_2;
    //std::cout << "Vec3 AngleRadians (%f): %s\n", angle, (Vec3::AngleRadians(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = -1.0f;	result.y = 0.0f;	result.w = 1.0f;
    //angle = M_PI;
    //std::cout << "Vec3 AngleRadians (%f): %s\n", angle, (Vec3::AngleRadians(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = -1.0f;	result.y = 0.0f;	result.w = 1.0f;
    //angle = -M_PI;
    //std::cout << "Vec3 AngleRadians (%f): %s\n", angle, (Vec3::AngleRadians(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = 0.0f;	result.y = -1.0f;	result.w = 1.0f;
    //angle = 1.5f * M_PI;
    //std::cout << "Vec3 AngleRadians (%f): %s\n", angle, (Vec3::AngleRadians(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = 1.0f;	result.y = 0.0f;	result.w = 1.0f;
    //angle = 2.0f * M_PI;
    //std::cout << "Vec3 AngleRadians (%f): %s\n", angle, (Vec3::AngleRadians(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = 1.0f;	result.y = 0.0f;	result.w = 1.0f;
    //angle = 0.0f;
    //std::cout << "Vec3 AngleRadians (%f): %s\n", angle, (Vec3::AngleRadians(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = 0.707106f;	result.y = 0.707106f;	result.w = 1.0f;
    //angle = 45.0f;
    //std::cout << "Vec3 AngleDegrees (%f): %s\n", angle, (Vec3::AngleDegrees(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = 0.0f;	result.y = 1.0f;	result.w = 1.0f;
    //angle = 90.0f;
    //std::cout << "Vec3 AngleDegrees (%f): %s\n", angle, (Vec3::AngleDegrees(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = -1.0f;	result.y = 0.0f;	result.w = 1.0f;
    //angle = 180.0f;
    //std::cout << "Vec3 AngleDegrees (%f): %s\n", angle, (Vec3::AngleDegrees(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = -1.0f;	result.y = 0.0f;	result.w = 1.0f;
    //angle = -180.0f;
    //std::cout << "Vec3 AngleDegrees (%f): %s\n", angle, (Vec3::AngleDegrees(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = 0.0f;	result.y = -1.0f;	result.w = 1.0f;
    //angle = 270.0f;
    //std::cout << "Vec3 AngleDegrees (%f): %s\n", angle, (Vec3::AngleDegrees(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = 1.0f;	result.y = 0.0f;	result.w = 1.0f;
    //angle = 360.0f;
    //std::cout << "Vec3 AngleDegrees (%f): %s\n", angle, (Vec3::AngleDegrees(angle) == result) ? PASS : FAIL) << std::endl;

    //result.x = 1.0f;	result.y = 0.0f;	result.w = 1.0f;
    //angle = 0.0f;
    //std::cout << "Vec3 AngleDegrees (%f): %s\n", angle, (Vec3::AngleDegrees(angle) == result) ? PASS : FAIL) << std::endl;
#pragma endregion
}
#endif