#pragma once

#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

float cot(float val);

void SeedRand(unsigned int seed);
int Rand();
// Returns a (0 <= value <= 1)
float Rand_Zero_One();
// Returns a (0 <= value < 1)
float Rand_Zero_LT_One();
// Returns a Vector3f([-0.5, 0.5], [-0.5, 0.5], [-0.5, 0.5])
Vector3f Rand_UnitSphere();
float RandomFloat(float min, float max);
int RandomInt(int min, int max);

// Reflects a_vA around a_vB, a_vB should be normalized
Vector3f Reflect(const Vector3f& a_vA, const Vector3f& a_vB);

bool AreSameSign(const float& a_fA, const float& a_fB);

template <typename T>
void SwapValues(T& a_A, T& a_B)
{
    T tmp = a_A;
    a_A = a_B;
    a_B = tmp;
}

float GetDValueForPlane(const Vector3f& a_vNormal, const Vector3f& a_vPoint);

#endif