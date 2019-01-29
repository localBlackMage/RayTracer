/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Holden Profit>
- End Header --------------------------------------------------------*/

#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

Quaternion QuatLerp(Quaternion Q1, Quaternion Q2, float interpolation_value);
Quaternion QuatSlerp(Quaternion Q1, Quaternion Q2, float interpolation_value);
Vec3 Lerp(const Vec3& vectorA, const Vec3& vectorB, float t, bool isEaseIn = false, bool isEaseOut = false);
float Lerp(float valueA, float valueB, float t, bool isEaseIn = false, bool isEaseOut = false);
float SinWave(float amplitude, float frequency, float phaseShift, float time);
float CosWave(float amplitude, float frequency, float phaseShift, float time);
float cot(float val);
float GetGaussianWeight(float width, float i);
unsigned int GetPascalEntry(unsigned short degree, unsigned short index);
float BezierInterpolation(const std::vector<Point>& points, const float& t);

// Given an angle in degrees, returns a value between -180 and +180
float ClampAngleTo180(float angle);
bool IsSimilar(float a, float b);

void SeedRand(unsigned int seed);
int Rand();
// Returns a (0 <= value <= 1)
float Rand_Zero_One();
// Returns a (0 <= value < 1)
float Rand_Zero_LT_One();
// Returns a Vec3([-0.5, 0.5], [-0.5, 0.5], [-0.5, 0.5])
Vec3 Rand_UnitSphere();
float RandomFloat(float min, float max);
int RandomInt(int min, int max);

// Reflects a_vA around a_vB, a_vB should be normalized
Vec3 Reflect(const Vec3& a_vA, const Vec3& a_vB);

bool AreSameSign(const float& a_fA, const float& a_fB);
template <typename T>
void SwapValues(T& a_A, T& a_B);

#endif

template<typename T>
inline void SwapValues(T & a_A, T & a_B)
{
    T tmp = a_A;
    a_A = a_B;
    a_B = tmp;
}

float GetDValueForPlane(const Vec3& a_vNormal, const Vec3& a_vPoint);
