#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

class Vec3
{
public:
	float x, y, z, w;
	
	Vec3();
	Vec3(const Vec3& vec, const float& _w);
	Vec3(const float& _x, const float& _y, const float& _z, const float& _w = 1.f);
	Vec3(const Vec3 & rhs);
	Vec3& operator= (const Vec3& rhs);
	~Vec3();

	void Set(float _x, float _y, float _z);
	void Set(float _x, float _y, float _z, float _w);

    inline float r() const { return x; }
    inline float g() const { return y; }
    inline float b() const { return z; }
    inline float a() const { return w; }

	operator float*();
	bool operator== (const  Vec3& other) const;
	bool operator!= (const  Vec3& other) const;
	Vec3 operator+ (const Vec3& other) const;
	Vec3& operator+= (const Vec3& other);
	Vec3 operator- (const Vec3& other) const;
	Vec3& operator-= (const Vec3& other);
	Vec3 operator* (const float scalar) const;
    Vec3 operator* (const Vec3& other) const;
	Vec3 operator/ (const float divisor) const;
    Vec3 operator/ (const Vec3& other) const;
    Vec3& operator/= (const float divisor);
    float operator[](const int idx) const;
	float& operator[](const int idx);

	void Add(const Vec3& other);
	void Sub(const Vec3& other);
	void Mul(const float scalar);
	void Div(const float divisor);
	void Print() const;
	void FillValues(float&, float&, float&);

	float AngleRadians() const;
	float AngleDegrees() const;

	void Zero();
	void Negate();
	float SquareLength() const;
	float Length() const;
	Vec3& Normalize();
    float Dot(const Vec3& v) const;
	bool IsVectorZero(float error = EPSILON) const;

	static float SquareDistance(const Vec3& vector0, const Vec3& vector1);
	static float Distance(const Vec3& vector0, const Vec3& vector1);
	static Vec3 Normalize(const Vec3& vector);
	static float Dot(const Vec3& vector0, const Vec3& vector1);
	static Vec3 Cross(const Vec3& vector0, const Vec3& vector1);
	static Vec3 VectorFromAngleDegrees(float degrees);
	static Vec3 AngleRadians(float radians, Vec3& axis);
	static Vec3 AngleDegrees(float degrees, Vec3& axis);
};

Vec3 operator*(const float scalar, const Vec3& other);
std::ostream& operator<<(std::ostream& out, const Vec3& vec);

static const Vec3 XAXIS = Vec3(1, 0, 0, 0);
static const Vec3 YAXIS = Vec3(0, 1, 0, 0);
static const Vec3 ZAXIS = Vec3(0, 0, 1, 0);

void Vec3Tests();

#endif