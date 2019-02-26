#include "stdafx.h"

Vector3f Reflect(const Vector3f & a_vA, const Vector3f & a_vB)
{
    return a_vA - 2.f * a_vA.dot(a_vB) * a_vB;
}

bool AreSameSign(const float & a_fA, const float & a_fB)
{
    return (a_fA >= 0.f && a_fB >= 0.f) || (a_fA < 0.f && a_fB < 0.f);
}

float GetDValueForPlane(const Vector3f & a_vNormal, const Vector3f & a_vPoint)
{
    return -a_vNormal.x() * a_vPoint.x() - a_vNormal.y() * a_vPoint.y() - a_vNormal.z() * a_vPoint.z();
}

float GeometryFactor(const Intersection & a_A, const Intersection & a_B)
{
    Vector3f D = a_A.m_vPoint - a_B.m_vPoint;
    float dDotD = D.dot(D);
    return (a_A.m_vNormal.dot(D) * a_B.m_vNormal.dot(D)) / (dDotD * dDotD); // Possibly absolute value?
}

Vector3f SampleLobe(const Vector3f & a_vNormal, float c, float phi)
{
    float s = sqrtf(1.f - c * c);
    Vector3f K = Vector3f(s * cosf(phi), s * sinf(phi), c);
    Quaternionf q = Quaternionf::FromTwoVectors(Vector3f::UnitZ(), a_vNormal);

    return q._transformVector(K);
}

float cot(float val)
{
    return cos(val) / sin(val);
}

long RT_Rand = 0;

void SeedRand(unsigned int seed)
{
    RT_Rand = (long)seed;
}

int Rand()
{
    RT_Rand = (RT_Rand * 214012L + 2531011L) >> 16;
    return RT_Rand & RT_RAND_MAX;
}

float Rand_Zero_One()
{
    float val = float(Rand());
    return val / float(RT_RAND_MAX);
}

float Rand_Zero_LT_One()
{
    float val = std::max(float(Rand() - 1), 0.f);
    return val / float(RT_RAND_MAX + 1);
}

float RandomFloat(float min, float max) 
{
    return (static_cast<float>(Rand()) / static_cast<float>(RT_RAND_MAX)) * (max - min) + min;
}

int RandomInt(int min, int max)
{
    if (min == max)
        return min;

    return Rand() % (max - min) + min;
}

uint32 RandomUInt(uint32 min, uint32 max)
{
    if (min == max)
        return min;

    return uint32(Rand()) % (max - min) + min;
}

Vector3f Rand_UnitSphere()
{
    float x = Rand_Zero_One() - 0.5f;
    float y = Rand_Zero_One() - 0.5f;
    float z = Rand_Zero_One() - 0.5f;
    return Vector3f(x, y, z);
}