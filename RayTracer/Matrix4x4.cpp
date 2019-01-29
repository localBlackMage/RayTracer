/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Holden Profit>
- End Header --------------------------------------------------------*/

#include "stdafx.h"

Matrix4x4::Matrix4x4() {
	m_matrix[0][0] = 0;
	m_matrix[0][1] = 0;
	m_matrix[0][2] = 0;
	m_matrix[0][3] = 0;

	m_matrix[1][0] = 0;
	m_matrix[1][1] = 0;
	m_matrix[1][2] = 0;
	m_matrix[1][3] = 0;

	m_matrix[2][0] = 0;
	m_matrix[2][1] = 0;
	m_matrix[2][2] = 0;
	m_matrix[2][3] = 0;

	m_matrix[3][0] = 0;
	m_matrix[3][1] = 0;
	m_matrix[3][2] = 0;
	m_matrix[3][3] = 0;
}

Matrix4x4::Matrix4x4(
	float x1, float y1, float z1, float w1, 
	float x2, float y2, float z2, float w2, 
	float x3, float y3, float z3, float w3, 
	float x4, float y4, float z4, float w4)
{
	m_matrix[0][0] = x1;
	m_matrix[0][1] = y1;
	m_matrix[0][2] = z1;
	m_matrix[0][3] = w1;

	m_matrix[1][0] = x2;
	m_matrix[1][1] = y2;
	m_matrix[1][2] = z2;
	m_matrix[1][3] = w2;

	m_matrix[2][0] = x3;
	m_matrix[2][1] = y3;
	m_matrix[2][2] = z3;
	m_matrix[2][3] = w3;

	m_matrix[3][0] = x4;
	m_matrix[3][1] = y4;
	m_matrix[3][2] = z4;
	m_matrix[3][3] = w4;
}

//Matrix4x4::Matrix4x4(const D3DXMATRIX & D3DMatrix)
//{
//	m_matrix[0][0] = D3DMatrix._11;
//	m_matrix[0][1] = D3DMatrix._12;
//	m_matrix[0][2] = D3DMatrix._13;
//	m_matrix[0][3] = D3DMatrix._14;
//
//	m_matrix[1][0] = D3DMatrix._21;
//	m_matrix[1][1] = D3DMatrix._22;
//	m_matrix[1][2] = D3DMatrix._23;
//	m_matrix[1][3] = D3DMatrix._24;
//
//	m_matrix[2][0] = D3DMatrix._31;
//	m_matrix[2][1] = D3DMatrix._32;
//	m_matrix[2][2] = D3DMatrix._33;
//	m_matrix[2][3] = D3DMatrix._34;
//
//	m_matrix[3][0] = D3DMatrix._41;
//	m_matrix[3][1] = D3DMatrix._42;
//	m_matrix[3][2] = D3DMatrix._43;
//	m_matrix[3][3] = D3DMatrix._44;
//}

Matrix4x4::Matrix4x4(const Matrix4x4 &other)
{
	m_matrix[0][0] = other.m_matrix[0][0];
	m_matrix[0][1] = other.m_matrix[0][1];
	m_matrix[0][2] = other.m_matrix[0][2];
	m_matrix[0][3] = other.m_matrix[0][3];

	m_matrix[1][0] = other.m_matrix[1][0];
	m_matrix[1][1] = other.m_matrix[1][1];
	m_matrix[1][2] = other.m_matrix[1][2];
	m_matrix[1][3] = other.m_matrix[1][3];

	m_matrix[2][0] = other.m_matrix[2][0];
	m_matrix[2][1] = other.m_matrix[2][1];
	m_matrix[2][2] = other.m_matrix[2][2];
	m_matrix[2][3] = other.m_matrix[2][3];

	m_matrix[3][0] = other.m_matrix[3][0];
	m_matrix[3][1] = other.m_matrix[3][1];
	m_matrix[3][2] = other.m_matrix[3][2];
	m_matrix[3][3] = other.m_matrix[3][3];
}

Matrix4x4::Matrix4x4(const Matrix3x3 & other)
{
	m_matrix[0][0] = other.Get(0, 0);
	m_matrix[0][1] = other.Get(0, 1);
	m_matrix[0][2] = other.Get(0, 2);
	m_matrix[0][3] = 0.0f;

	m_matrix[1][0] = other.Get(1, 0);
	m_matrix[1][1] = other.Get(1, 1);
	m_matrix[1][2] = other.Get(1, 2);
	m_matrix[1][3] = 0.0f;

	m_matrix[2][0] = other.Get(2, 0);
	m_matrix[2][1] = other.Get(2, 1);
	m_matrix[2][2] = other.Get(2, 2);
	m_matrix[2][3] = 0.0f;

	m_matrix[3][0] = 0.0f;
	m_matrix[3][1] = 0.0f;
	m_matrix[3][2] = 0.0f;
	m_matrix[3][3] = 1.0f;
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other)
{
	m_matrix[0][0] = other.m_matrix[0][0];
	m_matrix[0][1] = other.m_matrix[0][1];
	m_matrix[0][2] = other.m_matrix[0][2];
	m_matrix[0][3] = other.m_matrix[0][3];

	m_matrix[1][0] = other.m_matrix[1][0];
	m_matrix[1][1] = other.m_matrix[1][1];
	m_matrix[1][2] = other.m_matrix[1][2];
	m_matrix[1][3] = other.m_matrix[1][3];

	m_matrix[2][0] = other.m_matrix[2][0];
	m_matrix[2][1] = other.m_matrix[2][1];
	m_matrix[2][2] = other.m_matrix[2][2];
	m_matrix[2][3] = other.m_matrix[2][3];

	m_matrix[3][0] = other.m_matrix[3][0];
	m_matrix[3][1] = other.m_matrix[3][1];
	m_matrix[3][2] = other.m_matrix[3][2];
	m_matrix[3][3] = other.m_matrix[3][3];
	return *this;
}

Matrix4x4::~Matrix4x4() {}

float Matrix4x4::Get(int row, int col) const
{
	return m_matrix[row][col];
}

void Matrix4x4::Set(int row, int col, float val)
{
	m_matrix[row][col] = val;
}

void Matrix4x4::Transpose()
{
	Matrix4x4 transposed = Matrix4x4(
		0.0f,			m_matrix[1][0], m_matrix[2][0], m_matrix[3][0],
		m_matrix[0][1], 0.0f,			m_matrix[2][1], m_matrix[3][1],
		m_matrix[0][2], m_matrix[1][2], 0.0f,			m_matrix[3][2],
		m_matrix[0][3], m_matrix[1][3], m_matrix[2][3], 0.0f
	);

	m_matrix[0][1] = transposed.m_matrix[0][1];
	m_matrix[0][2] = transposed.m_matrix[0][2];
	m_matrix[0][3] = transposed.m_matrix[0][3];

	m_matrix[1][0] = transposed.m_matrix[1][0];
	m_matrix[1][2] = transposed.m_matrix[1][2];
	m_matrix[1][3] = transposed.m_matrix[1][3];

	m_matrix[2][0] = transposed.m_matrix[2][0];
	m_matrix[2][1] = transposed.m_matrix[2][1];
	m_matrix[2][3] = transposed.m_matrix[2][3];

	m_matrix[3][0] = transposed.m_matrix[3][0];
	m_matrix[3][1] = transposed.m_matrix[3][1];
	m_matrix[3][2] = transposed.m_matrix[3][2];
}

void Matrix4x4::Zero()
{
	m_matrix[0][0] = 0.0f;
	m_matrix[0][1] = 0.0f;
	m_matrix[0][2] = 0.0f;
	m_matrix[0][3] = 0.0f;

	m_matrix[1][0] = 0.0f;
	m_matrix[1][1] = 0.0f;
	m_matrix[1][2] = 0.0f;
	m_matrix[1][3] = 0.0f;

	m_matrix[2][0] = 0.0f;
	m_matrix[2][1] = 0.0f;
	m_matrix[2][2] = 0.0f;
	m_matrix[2][3] = 0.0f;

	m_matrix[3][0] = 0.0f;
	m_matrix[3][1] = 0.0f;
	m_matrix[3][2] = 0.0f;
	m_matrix[3][3] = 0.0f;
}

void Matrix4x4::Identity()
{
	m_matrix[0][0] = 1.0f;
	m_matrix[0][1] = 0.0f;
	m_matrix[0][2] = 0.0f;
	m_matrix[0][3] = 0.0f;

	m_matrix[1][0] = 0.0f;
	m_matrix[1][1] = 1.0f;
	m_matrix[1][2] = 0.0f;
	m_matrix[1][3] = 0.0f;

	m_matrix[2][0] = 0.0f;
	m_matrix[2][1] = 0.0f;
	m_matrix[2][2] = 1.0f;
	m_matrix[2][3] = 0.0f;

	m_matrix[3][0] = 0.0f;
	m_matrix[3][1] = 0.0f;
	m_matrix[3][2] = 0.0f;
	m_matrix[3][3] = 1.0f;
}

float Matrix4x4::Determinant() const
{
	float total = 0.0f;
	for (unsigned int headCol = 0; headCol < 4; headCol++) {
		Matrix3x3 x33;
		for (unsigned int currCol = 0; currCol < 4; currCol++) {
			if (currCol == headCol)
				continue;
			x33.Set(0, currCol, m_matrix[1][currCol]);
			x33.Set(1, currCol, m_matrix[2][currCol]);
			x33.Set(2, currCol, m_matrix[3][currCol]);
		}
		total += x33.Determinant();
	}
	return total;
}

void Matrix4x4::Print() const
{
	std::cout << "[ " << m_matrix[0][0] << ", " << m_matrix[0][1] << ", " << m_matrix[0][2] << ", " << m_matrix[0][3] << "]" << std::endl;
	std::cout << "[ " << m_matrix[1][0] << ", " << m_matrix[1][1] << ", " << m_matrix[1][2] << ", " << m_matrix[1][3] << "]" << std::endl;
	std::cout << "[ " << m_matrix[2][0] << ", " << m_matrix[2][1] << ", " << m_matrix[2][2] << ", " << m_matrix[2][3] << "]" << std::endl;
	std::cout << "[ " << m_matrix[3][0] << ", " << m_matrix[3][1] << ", " << m_matrix[3][2] << ", " << m_matrix[3][3] << "]" << std::endl;
}

//D3DXMATRIX Matrix4x4::ToD3DXMATRIX()
//{
//	return D3DXMATRIX(
//		m_matrix[0][0], m_matrix[0][1], m_matrix[0][2], m_matrix[0][3],
//		m_matrix[1][0], m_matrix[1][1], m_matrix[1][2], m_matrix[1][3],
//		m_matrix[2][0], m_matrix[2][1], m_matrix[2][2], m_matrix[2][3],
//		m_matrix[3][0], m_matrix[3][1], m_matrix[3][2], m_matrix[3][3]
//	);
//}

#pragma region Static Methods
Matrix4x4 Matrix4x4::Zero4D()
{
	return Matrix4x4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

Matrix4x4 Matrix4x4::Identity4D()
{
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

float Matrix4x4::Determinant(const Matrix4x4& other)
{
	float total = 0.0f;
	for (unsigned int headCol = 0; headCol < 4; headCol++) {
		Matrix3x3 x33;
		for (unsigned int currCol = 0; currCol < 4; currCol++) {
			if (currCol == headCol)
				continue;
			x33.Set(0, currCol, other.m_matrix[1][currCol]);
			x33.Set(1, currCol, other.m_matrix[2][currCol]);
			x33.Set(2, currCol, other.m_matrix[3][currCol]);
		}
		total += x33.Determinant();
	}
	return total;
}

Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& other)
{
	return Matrix4x4(
		other.m_matrix[0][0], other.m_matrix[1][0], other.m_matrix[2][0], other.m_matrix[3][0],
		other.m_matrix[0][1], other.m_matrix[1][1], other.m_matrix[2][1], other.m_matrix[3][1],
		other.m_matrix[0][2], other.m_matrix[1][2], other.m_matrix[2][2], other.m_matrix[3][2],
		other.m_matrix[0][3], other.m_matrix[1][3], other.m_matrix[2][3], other.m_matrix[3][3]
	);
}

Matrix4x4 Matrix4x4::Transpose3x3(const Matrix4x4& other)
{
	return Matrix4x4(
		other.m_matrix[0][0], other.m_matrix[1][0], other.m_matrix[2][0], 0,
		other.m_matrix[0][1], other.m_matrix[1][1], other.m_matrix[2][1], 0,
		other.m_matrix[0][2], other.m_matrix[1][2], other.m_matrix[2][2], 0,
		0, 0, 0, 1
	);
}

Matrix4x4 Matrix4x4::Inverse(const Matrix4x4& other)
{
	// TODO: Fix

	//float idet = 1.0f / other.Determinant();

	//return Matrix4x4(
	//	idet*(other.Get(1, 1) * other.Get(2, 2) - other.Get(2, 1) * other.Get(1, 2)), 
	//	-idet*(other.Get(0, 1) * other.Get(2, 2) - other.Get(2, 1) * other.Get(0, 2)),
	//	idet*(other.Get(0, 1) * other.Get(1, 2) - other.Get(1, 1) * other.Get(0, 2)),
	//	0.0f,
	//	-idet*(other.Get(1, 0) * other.Get(2, 2) - other.Get(2, 0) * other.Get(1, 2)),
	//	idet*(other.Get(0, 0) * other.Get(2, 2) - other.Get(2, 0) * other.Get(0, 2)),
	//	-idet*(other.Get(0, 0) * other.Get(1, 2) - other.Get(1, 0) * other.Get(0, 2)),
	//	0.0f,
	//	idet*(other.Get(1, 0) * other.Get(2, 1) - other.Get(2, 0) * other.Get(1, 1)),
	//	-idet*(other.Get(0, 0) * other.Get(2, 1) - other.Get(2, 0) * other.Get(0, 1)),
	//	idet*(other.Get(0, 0) * other.Get(1, 1) - other.Get(1, 0) * other.Get(0, 1)),
	//	0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	//);

	return Matrix4x4();
}

Matrix4x4 Matrix4x4::Inverse3x3(const Matrix4x4& other)
{
	float idet = 1.0f / (
			  other.m_matrix[0][0] * (other.m_matrix[1][1] * other.m_matrix[2][2] - other.m_matrix[2][1] * other.m_matrix[1][2])
			- other.m_matrix[0][1] * (other.m_matrix[1][0] * other.m_matrix[2][2] - other.m_matrix[2][0] * other.m_matrix[1][2])
			+ other.m_matrix[0][2] * (other.m_matrix[1][0] * other.m_matrix[2][1] - other.m_matrix[1][1] * other.m_matrix[2][0])
		);

	return Matrix4x4(
		idet*(other.m_matrix[1][1] * other.m_matrix[2][2] - other.m_matrix[2][1] * other.m_matrix[1][2]),
		-idet*(other.m_matrix[0][1] * other.m_matrix[2][2] - other.m_matrix[2][1] * other.m_matrix[0][2]),
		idet*(other.m_matrix[0][1] * other.m_matrix[1][2] - other.m_matrix[1][1] * other.m_matrix[0][2]),
		0.0f,

		-idet*(other.m_matrix[1][0] * other.m_matrix[2][2] - other.m_matrix[2][0] * other.m_matrix[1][2]),
		idet*(other.m_matrix[0][0] * other.m_matrix[2][2] - other.m_matrix[2][0] * other.m_matrix[0][2]),
		-idet*(other.m_matrix[0][0] * other.m_matrix[1][2] - other.m_matrix[1][0] * other.m_matrix[0][2]),
		0.0f,

		idet*(other.m_matrix[1][0] * other.m_matrix[2][1] - other.m_matrix[2][0] * other.m_matrix[1][1]),
		-idet*(other.m_matrix[0][0] * other.m_matrix[2][1] - other.m_matrix[2][0] * other.m_matrix[0][1]),
		idet*(other.m_matrix[0][0] * other.m_matrix[1][1] - other.m_matrix[1][0] * other.m_matrix[0][1]),
		0.0f,

		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::Rotate(const float degrees, const Vec3& axis)
{
	float x = axis.x, y = axis.y, z = axis.z,
		rad = degrees * DEG_TO_RAD,
		c = cosf(rad),
		a = (1 - c) / Vec3::Dot(axis, axis),
		b = sinf(rad) / axis.Length();

	return Matrix4x4(
		c + a*x*x, a*x*y - b*z, a*x*z + b*y, 0.0f,
		a*y*x + b*z, c + a*y*y, a*y*z - b*x, 0.0f,
		a*z*x - b*y, a*z*y + b*x, c + a*z*z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::Translate(const Vec3& amt)
{
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, amt.x,
		0.0f, 1.0f, 0.0f, amt.y,
		0.0f, 0.0f, 1.0f, amt.z,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::Scale(const Vec3 & scalar)
{
	return Matrix4x4(
		scalar.x, 0.0f, 0.0f, 0.0f,
		0.0f, scalar.y, 0.0f, 0.0f,
		0.0f, 0.0f, scalar.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::Scale(const float scalar)
{
	return Matrix4x4(
		scalar, 0.0f, 0.0f, 0.0f,
		0.0f, scalar, 0.0f, 0.0f,
		0.0f, 0.0f, scalar, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::Scale(const float scaleX, const float scaleY, const float scaleZ)
{
	return Matrix4x4(
		scaleX, 0.0f, 0.0f, 0.0f,
		0.0f, scaleY, 0.0f, 0.0f,
		0.0f, 0.0f, scaleZ, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::Perspective(const float fov, const float aspect, const float nearVal, const float farVal)
{
	float xymax = nearVal * tanf(fov * PI / 360.0f);
	float ymin = -xymax;
	float xmin = -xymax;
	
	float width = xymax - xmin;
	float height = xymax - ymin;
	 
	float depth = nearVal - farVal;
	float q = (nearVal + farVal) / depth;
	float qn = (2 * farVal * nearVal) / depth;
	
	float w = (2 * nearVal) / width;
	w = w / aspect;
	float h = (2 * nearVal) / height;
	
	return Matrix4x4(
		w, 0,  0, 0,
		0, h, 0,  0,
		0, 0, q, qn,
		0, 0, -1, 0
	);
	

	//float yScale = cot((fov * DEG_TO_RAD) / 2.f);
	//float xScale = yScale / aspect;
	//float depth = farVal - nearVal;
	//float q = farVal / depth;
	//float qn = (-nearVal * farVal) / depth;

	//return Matrix4x4(
	//	xScale, 0, 0, 0,
	//	0, yScale, 0, 0,
	//	0, 0, q, 1,
	//	0, 0, qn, 0
	//);
}

Matrix4x4 Matrix4x4::Perspective(const float fov, const float aspect, const float nearVal)
{
	Matrix4x4 perspM = Matrix4x4();
	perspM.Set(0, 0, 1.0f / tan(0.5f * DEG_TO_RAD * fov));
	perspM.Set(1, 1, aspect * perspM.Get(0, 0));
	perspM.Set(2, 2, -1.f);
	perspM.Set(2, 3, -2.f * nearVal);
	perspM.Set(3, 2, -1.f);

	return perspM;
}

Matrix4x4 Matrix4x4::Orthographic(const float width, const float height, const float nearVal, const float farVal)
{
	float w = 2.0f / width,
		h = 2.0f / height,
		nf = -2.0f / (farVal - nearVal),
		tnf = -((farVal + nearVal) / (farVal - nearVal));

	return Matrix4x4(
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, nf, tnf,
		0, 0, 0, 1
	);
}

Matrix4x4 Matrix4x4::Orthographic(const float width, const float height, const float nearVal)
{
	return Orthographic(width, height, nearVal, 1000.0f);
}

//physics
Matrix4x4 Matrix4x4::Phy_multiply_Matrix(const Matrix4x4 &o) const
{
  Matrix4x4 result = Matrix4x4(1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 0.f);
  result.m_matrix[0][0] = (o.m_matrix[0][0] * m_matrix[0][0]) + (o.m_matrix[1][0] * m_matrix[0][1]) + (o.m_matrix[2][0] * m_matrix[0][2]);
  result.m_matrix[1][0] = (o.m_matrix[0][0] * m_matrix[1][0]) + (o.m_matrix[1][0] * m_matrix[1][1]) + (o.m_matrix[2][0] * m_matrix[1][2]);
  result.m_matrix[2][0] = (o.m_matrix[0][0] * m_matrix[2][0]) + (o.m_matrix[1][0] * m_matrix[2][1]) + (o.m_matrix[2][0] * m_matrix[2][2]);

  result.m_matrix[0][1] = (o.m_matrix[0][1] * m_matrix[0][0]) + (o.m_matrix[1][1] * m_matrix[0][1]) + (o.m_matrix[2][1] * m_matrix[0][2]);
  result.m_matrix[1][1] = (o.m_matrix[0][1] * m_matrix[1][0]) + (o.m_matrix[1][1] * m_matrix[1][1]) + (o.m_matrix[2][1] * m_matrix[1][2]);
  result.m_matrix[2][1] = (o.m_matrix[0][1] * m_matrix[2][0]) + (o.m_matrix[1][1] * m_matrix[2][1]) + (o.m_matrix[2][1] * m_matrix[2][2]);

  result.m_matrix[0][2] = (o.m_matrix[0][2] * m_matrix[0][0]) + (o.m_matrix[1][2] * m_matrix[0][1]) + (o.m_matrix[2][2] * m_matrix[0][2]);
  result.m_matrix[1][2] = (o.m_matrix[0][2] * m_matrix[1][0]) + (o.m_matrix[1][2] * m_matrix[1][1]) + (o.m_matrix[2][2] * m_matrix[1][2]);
  result.m_matrix[2][2] = (o.m_matrix[0][2] * m_matrix[2][0]) + (o.m_matrix[1][2] * m_matrix[2][1]) + (o.m_matrix[2][2] * m_matrix[2][2]);

  result.m_matrix[0][3] = (o.m_matrix[0][3] * m_matrix[0][0]) + (o.m_matrix[1][3] * m_matrix[0][1]) + (o.m_matrix[2][3] * m_matrix[0][2]) + m_matrix[0][3];
  result.m_matrix[1][3] = (o.m_matrix[0][3] * m_matrix[1][0]) + (o.m_matrix[1][3] * m_matrix[1][1]) + (o.m_matrix[2][3] * m_matrix[1][2]) + m_matrix[1][3];
  result.m_matrix[2][3] = (o.m_matrix[0][3] * m_matrix[2][0]) + (o.m_matrix[1][3] * m_matrix[2][1]) + (o.m_matrix[2][3] * m_matrix[2][2]) + m_matrix[2][3];

  return result;
}
Vec3 Matrix4x4::Phy_multiply_Vector3(const Vec3 &vector) const
{
  return Vec3(
    vector.x * m_matrix[0][0] +
    vector.y * m_matrix[0][1] +
    vector.z * m_matrix[0][2] + m_matrix[0][3],

    vector.x * m_matrix[1][0] +
    vector.y * m_matrix[1][1] +
    vector.z * m_matrix[1][2] + m_matrix[1][3],

    vector.x * m_matrix[2][0] +
    vector.y * m_matrix[2][1] +
    vector.z * m_matrix[2][2] + m_matrix[2][3]
  );
}

void Matrix4x4::physicsConstructor()
{
  m_matrix[0][1] = m_matrix[0][2] = m_matrix[0][3] = m_matrix[1][0] = m_matrix[1][2] =
  m_matrix[1][3] = m_matrix[2][0] = m_matrix[2][1] = m_matrix[2][3] = 0;
  m_matrix[0][0] = m_matrix[1][1] = m_matrix[2][2] = 1;
}

Vec3 Matrix4x4::transform(const Vec3 &vector) const
{
  return (*this) * vector;
}

float Matrix4x4::getDeterminant() const
{
  return -m_matrix[2][0] * m_matrix[1][1] * m_matrix[0][2] +
    m_matrix[1][0] * m_matrix[2][1] * m_matrix[0][2] +
    m_matrix[2][0] * m_matrix[0][1] * m_matrix[1][2] -
    m_matrix[0][0] * m_matrix[2][1] * m_matrix[1][2] -
    m_matrix[1][0] * m_matrix[0][1] * m_matrix[2][2] +
    m_matrix[0][0] * m_matrix[1][1] * m_matrix[2][2];
}

void Matrix4x4::setDiagonal(float a, float b, float c)
{
  m_matrix[0][0] = a;
  m_matrix[1][1] = b;
  m_matrix[2][2] = c;
}

void Matrix4x4::setInverse(const Matrix4x4 &m)
{
  // Make sure the determinant is non-zero.
  float det = getDeterminant();
  if (det == 0) return;
  det = ((float)1.0) / det;

  m_matrix[0][0] = (-m.m_matrix[2][1] * m.m_matrix[1][2] + m.m_matrix[1][1] * m.m_matrix[2][2])*det;
  m_matrix[1][0] = (m.m_matrix[2][0] * m.m_matrix[1][2] - m.m_matrix[1][0] * m.m_matrix[2][2])*det;
  m_matrix[2][0] = (-m.m_matrix[2][0] * m.m_matrix[1][1] + m.m_matrix[1][0] * m.m_matrix[2][1])*det;

  m_matrix[0][1] = (m.m_matrix[2][1] * m.m_matrix[0][2] - m.m_matrix[0][1] * m.m_matrix[2][2])*det;
  m_matrix[1][1] = (-m.m_matrix[2][0] * m.m_matrix[0][2] + m.m_matrix[0][0] * m.m_matrix[2][2])*det;
  m_matrix[2][1] = (m.m_matrix[2][0] * m.m_matrix[0][1] - m.m_matrix[0][0] * m.m_matrix[2][1])*det;

  m_matrix[0][2] = (-m.m_matrix[1][1] * m.m_matrix[0][2] + m.m_matrix[0][1] * m.m_matrix[1][2])*det;
  m_matrix[1][2] = (+m.m_matrix[1][0] * m.m_matrix[0][2] - m.m_matrix[0][0] * m.m_matrix[1][2])*det;
  m_matrix[2][2] = (-m.m_matrix[1][0] * m.m_matrix[0][1] + m.m_matrix[0][0] * m.m_matrix[1][1])*det;

  m_matrix[0][3] = (m.m_matrix[2][1] * m.m_matrix[1][2] * m.m_matrix[0][3]
    - m.m_matrix[1][1] * m.m_matrix[2][2] * m.m_matrix[0][3]
    - m.m_matrix[2][1] * m.m_matrix[0][2] * m.m_matrix[1][3]
    + m.m_matrix[0][1] * m.m_matrix[2][2] * m.m_matrix[1][3]
    + m.m_matrix[1][1] * m.m_matrix[0][2] * m.m_matrix[2][3]
    - m.m_matrix[0][1] * m.m_matrix[1][2] * m.m_matrix[2][3])*det;
  m_matrix[1][3] = (-m.m_matrix[2][0] * m.m_matrix[1][2] * m.m_matrix[0][3]
    + m.m_matrix[1][0] * m.m_matrix[2][2] * m.m_matrix[0][3]
    + m.m_matrix[2][0] * m.m_matrix[0][2] * m.m_matrix[1][3]
    - m.m_matrix[0][0] * m.m_matrix[2][2] * m.m_matrix[1][3]
    - m.m_matrix[1][0] * m.m_matrix[0][2] * m.m_matrix[2][3]
    + m.m_matrix[0][0] * m.m_matrix[1][2] * m.m_matrix[2][3])*det;
  m_matrix[2][3] = (m.m_matrix[2][0] * m.m_matrix[1][1] * m.m_matrix[0][3]
    - m.m_matrix[1][0] * m.m_matrix[2][1] * m.m_matrix[0][3]
    - m.m_matrix[2][0] * m.m_matrix[0][1] * m.m_matrix[1][3]
    + m.m_matrix[0][0] * m.m_matrix[2][1] * m.m_matrix[1][3]
    + m.m_matrix[1][0] * m.m_matrix[0][1] * m.m_matrix[2][3]
    - m.m_matrix[0][0] * m.m_matrix[1][1] * m.m_matrix[2][3])*det;
}

/*float* Matrix4x4::physicsMatrix()
{
  return m_matrix;
}*/

Matrix4x4 Matrix4x4::inverse() const
{
  Matrix4x4 result = Matrix4x4(1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 0.f);;
  result.setInverse(*this);
  return result;
}

void Matrix4x4::invert()
{
  setInverse(*this);
}

Vec3 Matrix4x4::transformDirection(const Vec3 &vector) const
{
  return Vec3(
    vector.x * m_matrix[0][0] +
    vector.y * m_matrix[0][1] +
    vector.z * m_matrix[0][2],

    vector.x * m_matrix[1][0] +
    vector.y * m_matrix[1][1] +
    vector.z * m_matrix[1][2],

    vector.x * m_matrix[2][0] +
    vector.y * m_matrix[2][1] +
    vector.z * m_matrix[2][2]
  );
}


Vec3 Matrix4x4::transformInverseDirection(const Vec3 &vector) const
{
  return Vec3(
    vector.x * m_matrix[0][0] +
    vector.y * m_matrix[1][0] +
    vector.z * m_matrix[2][0],

    vector.x * m_matrix[0][1] +
    vector.y * m_matrix[1][1] +
    vector.z * m_matrix[2][1],

    vector.x * m_matrix[0][2] +
    vector.y * m_matrix[1][2] +
    vector.z * m_matrix[2][2]
  );
}


Vec3 Matrix4x4::transformInverse(const Vec3 &vector) const
{
  Vec3 tmp = vector;
  tmp.x -= m_matrix[0][3];
  tmp.y -= m_matrix[1][3];
  tmp.z -= m_matrix[2][3];
  return Vec3(
    tmp.x * m_matrix[0][0] +
    tmp.y * m_matrix[1][0] +
    tmp.z * m_matrix[2][0],

    tmp.x * m_matrix[0][1] +
    tmp.y * m_matrix[1][1] +
    tmp.z * m_matrix[2][1],

    tmp.x * m_matrix[0][2] +
    tmp.y * m_matrix[1][2] +
    tmp.z * m_matrix[2][2]
  );
}


Vec3 Matrix4x4::getAxisVector(int i) const
{
  return Vec3(m_matrix[0][i], m_matrix[1][i], m_matrix[2][i]);
}


void Matrix4x4::setOrientationAndPos(const Quaternion &q, const Vec3 &pos)
{
  m_matrix[0][0] = 1 - (2 * q.y*q.y + 2 * q.z*q.z);
  m_matrix[0][1] = 2 * q.x*q.y + 2 * q.z*q.w;
  m_matrix[0][2] = 2 * q.x*q.z - 2 * q.y*q.w;
  m_matrix[0][3] = pos.x;

  m_matrix[1][0] = 2 * q.x*q.y - 2 * q.z*q.w;
  m_matrix[1][1] = 1 - (2 * q.x*q.x + 2 * q.z*q.z);
  m_matrix[1][2] = 2 * q.y*q.z + 2 * q.x*q.w;
  m_matrix[1][3] = pos.y;

  m_matrix[2][0] = 2 * q.x*q.z + 2 * q.y*q.w;
  m_matrix[2][1] = 2 * q.y*q.z - 2 * q.x*q.w;
  m_matrix[2][2] = 1 - (2 * q.x*q.x + 2 * q.y*q.y);
  m_matrix[2][3] = pos.z;
}


void Matrix4x4::fillGLArray(float array[16]) const
{
  array[0] = (float)m_matrix[0][0];
  array[1] = (float)m_matrix[1][0];
  array[2] = (float)m_matrix[2][0];
  array[3] = (float)0;

  array[4] = (float)m_matrix[0][1];
  array[5] = (float)m_matrix[1][1];
  array[6] = (float)m_matrix[2][1];
  array[7] = (float)0;

  array[8] = (float)m_matrix[0][2];
  array[9] = (float)m_matrix[1][2];
  array[10] = (float)m_matrix[2][2];
  array[11] = (float)0;

  array[12] = (float)m_matrix[0][3];
  array[13] = (float)m_matrix[1][3];
  array[14] = (float)m_matrix[2][3];
  array[15] = (float)1;
}

#pragma endregion

#pragma region Operation Overrides
Matrix4x4::operator float*()
{
	return &(m_matrix[0][0]);
}

bool Matrix4x4::operator==(const Matrix4x4& other) const
{
	double d = 0.0f;

	d += fabs(m_matrix[0][0] - other.m_matrix[0][0]);
	d += fabs(m_matrix[0][1] - other.m_matrix[0][1]);
	d += fabs(m_matrix[0][2] - other.m_matrix[0][2]);
	d += fabs(m_matrix[0][3] - other.m_matrix[0][3]);

	d += fabs(m_matrix[1][0] - other.m_matrix[1][0]);
	d += fabs(m_matrix[1][1] - other.m_matrix[1][1]);
	d += fabs(m_matrix[1][2] - other.m_matrix[1][2]);
	d += fabs(m_matrix[1][3] - other.m_matrix[1][3]);

	d += fabs(m_matrix[2][0] - other.m_matrix[2][0]);
	d += fabs(m_matrix[2][1] - other.m_matrix[2][1]);
	d += fabs(m_matrix[2][2] - other.m_matrix[2][2]);
	d += fabs(m_matrix[2][3] - other.m_matrix[2][3]);

	d += fabs(m_matrix[3][0] - other.m_matrix[3][0]);
	d += fabs(m_matrix[3][1] - other.m_matrix[3][1]);
	d += fabs(m_matrix[3][2] - other.m_matrix[3][2]);
	d += fabs(m_matrix[3][3] - other.m_matrix[3][3]);
	return d < EPSILON;
}

bool Matrix4x4::operator!=(const Matrix4x4& other) const
{
	double d = 0.0f;

	d += fabs(m_matrix[0][0] - other.m_matrix[0][0]);
	d += fabs(m_matrix[0][1] - other.m_matrix[0][1]);
	d += fabs(m_matrix[0][2] - other.m_matrix[0][2]);
	d += fabs(m_matrix[0][3] - other.m_matrix[0][3]);

	d += fabs(m_matrix[1][0] - other.m_matrix[1][0]);
	d += fabs(m_matrix[1][1] - other.m_matrix[1][1]);
	d += fabs(m_matrix[1][2] - other.m_matrix[1][2]);
	d += fabs(m_matrix[1][3] - other.m_matrix[1][3]);

	d += fabs(m_matrix[2][0] - other.m_matrix[2][0]);
	d += fabs(m_matrix[2][1] - other.m_matrix[2][1]);
	d += fabs(m_matrix[2][2] - other.m_matrix[2][2]);
	d += fabs(m_matrix[2][3] - other.m_matrix[2][3]);

	d += fabs(m_matrix[3][0] - other.m_matrix[3][0]);
	d += fabs(m_matrix[3][1] - other.m_matrix[3][1]);
	d += fabs(m_matrix[3][2] - other.m_matrix[3][2]);
	d += fabs(m_matrix[3][3] - other.m_matrix[3][3]);
	return d >= EPSILON;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const
{
	return Matrix4x4(
		m_matrix[0][0] + other.m_matrix[0][0], m_matrix[0][1] + other.m_matrix[0][1], m_matrix[0][2] + other.m_matrix[0][2], m_matrix[0][3] + other.m_matrix[0][3],
		m_matrix[1][0] + other.m_matrix[1][0], m_matrix[1][1] + other.m_matrix[1][1], m_matrix[1][2] + other.m_matrix[1][2], m_matrix[1][3] + other.m_matrix[1][3],
		m_matrix[2][0] + other.m_matrix[2][0], m_matrix[2][1] + other.m_matrix[2][1], m_matrix[2][2] + other.m_matrix[2][2], m_matrix[2][3] + other.m_matrix[2][3],
		m_matrix[3][0] + other.m_matrix[3][0], m_matrix[3][1] + other.m_matrix[3][1], m_matrix[3][2] + other.m_matrix[3][2], m_matrix[3][3] + other.m_matrix[3][3]
	);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const
{
	return Matrix4x4(
		m_matrix[0][0] - other.m_matrix[0][0], m_matrix[0][1] - other.m_matrix[0][1], m_matrix[0][2] - other.m_matrix[0][2], m_matrix[0][3] - other.m_matrix[0][3],
		m_matrix[1][0] - other.m_matrix[1][0], m_matrix[1][1] - other.m_matrix[1][1], m_matrix[1][2] - other.m_matrix[1][2], m_matrix[1][3] - other.m_matrix[1][3],
		m_matrix[2][0] - other.m_matrix[2][0], m_matrix[2][1] - other.m_matrix[2][1], m_matrix[2][2] - other.m_matrix[2][2], m_matrix[2][3] - other.m_matrix[2][3],
		m_matrix[3][0] - other.m_matrix[3][0], m_matrix[3][1] - other.m_matrix[3][1], m_matrix[3][2] - other.m_matrix[3][2], m_matrix[3][3] - other.m_matrix[3][3]
	);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
{
	return Matrix4x4(
		(m_matrix[0][0] * other.m_matrix[0][0]) + (m_matrix[0][1] * other.m_matrix[1][0]) + (m_matrix[0][2] * other.m_matrix[2][0]) + (m_matrix[0][3] * other.m_matrix[3][0]),
		(m_matrix[0][0] * other.m_matrix[0][1]) + (m_matrix[0][1] * other.m_matrix[1][1]) + (m_matrix[0][2] * other.m_matrix[2][1]) + (m_matrix[0][3] * other.m_matrix[3][1]),
		(m_matrix[0][0] * other.m_matrix[0][2]) + (m_matrix[0][1] * other.m_matrix[1][2]) + (m_matrix[0][2] * other.m_matrix[2][2]) + (m_matrix[0][3] * other.m_matrix[3][2]),
		(m_matrix[0][0] * other.m_matrix[0][3]) + (m_matrix[0][1] * other.m_matrix[1][3]) + (m_matrix[0][2] * other.m_matrix[2][3]) + (m_matrix[0][3] * other.m_matrix[3][3]),

		(m_matrix[1][0] * other.m_matrix[0][0]) + (m_matrix[1][1] * other.m_matrix[1][0]) + (m_matrix[1][2] * other.m_matrix[2][0]) + (m_matrix[1][3] * other.m_matrix[3][0]),
		(m_matrix[1][0] * other.m_matrix[0][1]) + (m_matrix[1][1] * other.m_matrix[1][1]) + (m_matrix[1][2] * other.m_matrix[2][1]) + (m_matrix[1][3] * other.m_matrix[3][1]),
		(m_matrix[1][0] * other.m_matrix[0][2]) + (m_matrix[1][1] * other.m_matrix[1][2]) + (m_matrix[1][2] * other.m_matrix[2][2]) + (m_matrix[1][3] * other.m_matrix[3][2]),
		(m_matrix[1][0] * other.m_matrix[0][3]) + (m_matrix[1][1] * other.m_matrix[1][3]) + (m_matrix[1][2] * other.m_matrix[2][3]) + (m_matrix[1][3] * other.m_matrix[3][3]),

		(m_matrix[2][0] * other.m_matrix[0][0]) + (m_matrix[2][1] * other.m_matrix[1][0]) + (m_matrix[2][2] * other.m_matrix[2][0]) + (m_matrix[2][3] * other.m_matrix[3][0]),
		(m_matrix[2][0] * other.m_matrix[0][1]) + (m_matrix[2][1] * other.m_matrix[1][1]) + (m_matrix[2][2] * other.m_matrix[2][1]) + (m_matrix[2][3] * other.m_matrix[3][1]),
		(m_matrix[2][0] * other.m_matrix[0][2]) + (m_matrix[2][1] * other.m_matrix[1][2]) + (m_matrix[2][2] * other.m_matrix[2][2]) + (m_matrix[2][3] * other.m_matrix[3][2]),
		(m_matrix[2][0] * other.m_matrix[0][3]) + (m_matrix[2][1] * other.m_matrix[1][3]) + (m_matrix[2][2] * other.m_matrix[2][3]) + (m_matrix[2][3] * other.m_matrix[3][3]),

		(m_matrix[3][0] * other.m_matrix[0][0]) + (m_matrix[3][1] * other.m_matrix[1][0]) + (m_matrix[3][2] * other.m_matrix[2][0]) + (m_matrix[3][3] * other.m_matrix[3][0]),
		(m_matrix[3][0] * other.m_matrix[0][1]) + (m_matrix[3][1] * other.m_matrix[1][1]) + (m_matrix[3][2] * other.m_matrix[2][1]) + (m_matrix[3][3] * other.m_matrix[3][1]),
		(m_matrix[3][0] * other.m_matrix[0][2]) + (m_matrix[3][1] * other.m_matrix[1][2]) + (m_matrix[3][2] * other.m_matrix[2][2]) + (m_matrix[3][3] * other.m_matrix[3][2]),
		(m_matrix[3][0] * other.m_matrix[0][3]) + (m_matrix[3][1] * other.m_matrix[1][3]) + (m_matrix[3][2] * other.m_matrix[2][3]) + (m_matrix[3][3] * other.m_matrix[3][3])
	);
}

Matrix4x4 Matrix4x4::operator*(const float scalar) const
{
	return Matrix4x4(
		m_matrix[0][0] * scalar, m_matrix[0][1] * scalar, m_matrix[0][2] * scalar, m_matrix[0][3] * scalar,
		m_matrix[1][0] * scalar, m_matrix[1][1] * scalar, m_matrix[1][2] * scalar, m_matrix[1][3] * scalar,
		m_matrix[2][0] * scalar, m_matrix[2][1] * scalar, m_matrix[2][2] * scalar, m_matrix[2][3] * scalar,
		m_matrix[3][0] * scalar, m_matrix[3][1] * scalar, m_matrix[3][2] * scalar, m_matrix[3][3] * scalar
	);
}

Matrix4x4 Matrix4x4::operator/(const float divisor) const
{
	return Matrix4x4(
		m_matrix[0][0] / divisor, m_matrix[0][1] / divisor, m_matrix[0][2] / divisor, m_matrix[0][3] / divisor,
		m_matrix[1][0] / divisor, m_matrix[1][1] / divisor, m_matrix[1][2] / divisor, m_matrix[1][3] / divisor,
		m_matrix[2][0] / divisor, m_matrix[2][1] / divisor, m_matrix[2][2] / divisor, m_matrix[2][3] / divisor,
		m_matrix[3][0] / divisor, m_matrix[3][1] / divisor, m_matrix[3][2] / divisor, m_matrix[3][3] / divisor
	);
}


Vec3 Matrix4x4::operator*(const Vec3& other) const
{
	return Vec3(
		m_matrix[0][0] * other.x + m_matrix[0][1] * other.y + m_matrix[0][2] * other.z + m_matrix[0][3] * other.w,
		m_matrix[1][0] * other.x + m_matrix[1][1] * other.y + m_matrix[1][2] * other.z + m_matrix[1][3] * other.w,
		m_matrix[2][0] * other.x + m_matrix[2][1] * other.y + m_matrix[2][2] * other.z + m_matrix[2][3] * other.w,
		m_matrix[3][0] * other.x + m_matrix[3][1] * other.y + m_matrix[3][2] * other.z + m_matrix[3][3] * other.w
	);
}
#pragma endregion

#if TEST_MODE
void Matrix4x4Tests()
{
	std::cout << "\n========== Running Matrix3x3 tests ==========\n\n";

#pragma region Methods
	Matrix4x4 m0 = Matrix4x4();
	Matrix4x4 m1 = Matrix4x4();
	long i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			m0.Set(i, j, float(i * 2 + j));
			m1.Set(i, j, float(i + j * 2));
		}
	}

	m1.Transpose();
	std::cout << "Matrix4x4 Transpose: " << ((m0 == m1) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.Set(i, j, 0.0f);
	m1.Zero();
	std::cout << "Matrix4x4 Zero: " << ((m0 == m1) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.Set(i, j, i == j ? 1.0f : 0.0f);

	m1.Identity();
	std::cout << "Matrix4x4 Identity: " << ((m0 == m1) ? PASS : FAIL) << std::endl;
#pragma endregion
#pragma region StaticMethods
	m0.Zero();

	Matrix4x4 zero = Matrix4x4::Zero4D();
	std::cout << "Matrix4x4::Zero4D: " << ((zero == m0) ? PASS : FAIL) << std::endl;

	m0.Identity();

	Matrix4x4 identity = Matrix4x4::Identity4D();
	std::cout << "Matrix4x4::Identity4D: " << ((m0 == identity) ? PASS : FAIL) << std::endl;
#pragma endregion
#pragma region Operations

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float(i - j));
		}
	}
	std::cout << "Matrix4x4 == Matrix4x4 equal: " << ((m0 == m0) ? PASS : FAIL) << std::endl;

	std::cout << "Matrix4x4 == Matrix4x4 not equal: " << ((m0 == m1) ? FAIL : PASS);

	std::cout << "Matrix4x4 != Matrix4x4 not equal: " << ((m0 != m1) ? PASS : FAIL) << std::endl;

	std::cout << "Matrix4x4 != Matrix4x4 equal: " << ((m0 != m0) ? FAIL : PASS);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float(-(i + j)));
		}
	}
	std::cout << "Matrix4x4 + Matrix4x4: " << ((zero == m0 + m1) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float(i + j));
		}
	}
	std::cout << "Matrix4x4 - Matrix4x4: " << ((zero == m0 - m1) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float(i + j));
		}
	}
	Matrix4x4 result = Matrix4x4(
		14.0f, 20.0f, 26.0f, 32.0f,
		20.0f, 30.0f, 40.0f, 50.0f,
		26.0f, 40.0f, 54.0f, 68.0f,
		32.0f, 50.0f, 68.0f, 86.0f
	);
	std::cout << "Matrix4x4 * Matrix4x4: " << ((m0 * m1 == result) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float((i + j) * 2.0f));
		}
	}
	std::cout << "Matrix4x4 * scalar: " << (((m0 * 2.0f) == m1) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float((i + j) / 2.0f));
		}
	}
	std::cout << "Matrix4x4 / divisor: " << (((m0 / 2.0f) == m1) ? PASS : FAIL) << std::endl;
#pragma endregion
#pragma region Vec3
	std::cout << "\n========== Running Matrix4x4 - Vec3 tests ==========\n\n";
	Matrix4x4 x44 = Matrix4x4(
		1.0f, 2.0f, 3.0f, 4.0f, 
		5.0f, 6.0f, 7.0f, 8.0f, 
		9.0f, 8.0f, 7.0f, 6.0f,
		5.0f, 4.0f, 3.0f, 2.0f);
	Vec3 v3 = Vec3(1.0f, 2.0f, 3.0f, 1.0f);
	Vec3 v3Test = Vec3(18.0f, 46.0f, 52.0f, 24.0f);
	std::cout << "Matrix4x4 * Vec3: " << ((v3Test == (x44 * v3)) ? PASS : FAIL) << std::endl;
#pragma endregion
}
#endif