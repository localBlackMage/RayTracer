#include "stdafx.h"

bool AreSameSign(const float & a_fA, const float & a_fB)
{
    return (a_fA >= 0.f && a_fB >= 0.f) || (a_fA < 0.f && a_fB < 0.f);
}

float GetDValueForPlane(const Vector3f & a_vNormal, const Vector3f & a_vPoint)
{
    return -a_vNormal.x() * a_vPoint.x() - a_vNormal.y() * a_vPoint.y() - a_vNormal.z() * a_vPoint.z();
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

Vector3f Rand_UnitSphere()
{
    float x = Rand_Zero_One() - 0.5f;
    float y = Rand_Zero_One() - 0.5f;
    float z = Rand_Zero_One() - 0.5f;
    return Vector3f(x, y, z);
}