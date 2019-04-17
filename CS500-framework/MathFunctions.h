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
float MersenneRandFloat();
float RandomFloat(float min, float max);
int RandomInt(int min, int max);
uint32 RandomUInt(uint32 min, uint32 max);

// Reflects a_vA around a_vB, a_vB should be normalized
Vector3f Reflect(const Vector3f& a_vA, const Vector3f& a_vB);

bool AreSameSign(const float& a_fA, const float& a_fB);

bool AreSimilar(float a_fA, float a_fB);

template <typename T>
void SwapValues(T& a_A, T& a_B)
{
    T tmp = a_A;
    a_A = a_B;
    a_B = tmp;
}

float GetDValueForPlane(const Vector3f& a_vNormal, const Vector3f& a_vPoint);

struct Intersection;
float GeometryFactor(const Intersection& a_A, const Intersection& a_B);

// c = cosine of m_fAngle between vector and a_vNormal
// phi = m_fAngle around a_vNormal
Vector3f SampleLobe(const Vector3f& a_vNormal, float c, float phi);

float BRDF_D(const Vector3f& a_vM, const Vector3f& a_vNormal, float a_fAlpha);

float BRDF_G(const Vector3f& a_vOmegaO, const Vector3f& a_vOmegaI, const Vector3f& a_vM, const Vector3f& a_vNormal, float a_fAlpha);

Color BRDF_F(const Vector3f & a_vL, const Vector3f & a_vH, const Color& a_cKs);

Color BRDF_F_NotApprox(const Vector3f & a_vL, const Vector3f & a_vH, const Color& a_cKs, float a_fEtaI, float a_fEtaO);


float SignFN(float a_fVal);


bool IsColorNAN(const Color& a_cColor);

bool IsColorINF(const Color& a_cColor);

#endif