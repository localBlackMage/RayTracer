/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix3x3.h
Purpose: Provides a 3 x 3 Matrix and associated functionality
Language: C++
Project: GAM541
Author: Holden Profit
Creation date: 1/17/18
- End Header --------------------------------------------------------*/

//#pragma once

#ifndef MATRIX3X3_H
#define MATRIX3X3_H

//#include "Vector2D.h"
//#include "Vec3.h"
class Quaternion;
class Matrix3x3
{
public:
    float m_matrix[3][3];

public:
    Matrix3x3();
    Matrix3x3(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
    Matrix3x3(const Vec3 &compOne, const Vec3 &compTwo, const Vec3 &compThree);
    Matrix3x3(const Matrix3x3 &other); // Copy Ctor
    Matrix3x3& operator= (const Matrix3x3 &other); // Assignment Operator
    ~Matrix3x3();

    float Get(int row, int col) const;
    void Set(int row, int col, float val);
    void Transpose();
    void Zero();
    void Identity();
    float Determinant() const;
    void Print() const;

    static Matrix3x3 Zero3D();
    static Matrix3x3 Identity3D();
    static float Determinant(const Matrix3x3& other);
    static Matrix3x3 Translate(float x, float y);
    static Matrix3x3 Scale(float x, float y);
    static Matrix3x3 RotateDeg_Z(float degrees);
    static Matrix3x3 RotateRad_Z(float radians);
    //physics
    void setDiagonal(float a, float b, float c);
    //Sets the value of the matrix from inertia tensor values.
    void setInertiaTensorCoeffs(float ix, float iy, float iz, float ixy = 0, float ixz = 0, float iyz = 0);
    /**
      * Sets the value of the matrix as an inertia tensor of
      * a rectangular block aligned with the body's coordinate
      * system with the given axis half-sizes and mass.
      */
    void setBlockInertiaTensor(const Vec3 &halfSizes, float mass);
    /**
      * Sets the matrix to be a skew symmetric matrix based on
      * the given vector. The skew symmetric matrix is the equivalent
      * of the vector product. So if a,b are vectors. a x b = A_s b
      * where A_s is the skew symmetric form of a.
      */
    void setSkewSymmetric(const Vec3 vector);
    /**
      * Sets the matrix values from the given three vector components.
      * These are arranged as the three columns of the vector.
      */
    void setComponents(const Vec3 &compOne, const Vec3 &compTwo, const Vec3 &compThree);
    Vec3 transform(const Vec3 &vector);
    Vec3 transformTranspose(const Vec3 &vector) const;
    Vec3 getRowVector(int i) const;
    Vec3 getAxisVector(int i) const;
    void setInverse(const Matrix3x3 &m);
    Matrix3x3 inverse() const;
    void invert();
    void setTranspose(const Matrix3x3 &m);
    Matrix3x3 transpose() const;
    void setOrientation(const Quaternion &q);
    static Matrix3x3 linearInterpolate(const Matrix3x3& a, const Matrix3x3& b, float prop);


    bool operator== (const  Matrix3x3& other);
    bool operator!= (const  Matrix3x3& other);
    Matrix3x3 operator+ (const Matrix3x3& other);
    Matrix3x3 operator- (const Matrix3x3& other);
    Matrix3x3 operator* (const Matrix3x3& other);
    Matrix3x3 operator* (const float scalar);
    Matrix3x3 operator/ (const float divisor);

    Vec3 operator* (const Vec3& other);
    void operator*=(const Matrix3x3 &o);
    void operator*=(const float scalar);
    void operator+=(const Matrix3x3 &o);

};

#if TEST_MODE
void Matrix3x3Tests();
#endif

#endif