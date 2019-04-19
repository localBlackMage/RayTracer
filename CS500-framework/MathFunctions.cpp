#include "stdafx.h"

Vector3f Reflect(const Vector3f & a_vA, const Vector3f & a_vB)
{
    return a_vA - 2.f * a_vA.dot(a_vB) * a_vB;
}

bool AreSameSign(const float & a_fA, const float & a_fB)
{
    return (a_fA >= 0.f && a_fB >= 0.f) || (a_fA < 0.f && a_fB < 0.f);
}

bool AreSimilar(float a_fA, float a_fB)
{
    return fabsf(fabsf(a_fA) - fabsf(a_fB)) <= EPSILON;
}

float GetDValueForPlane(const Vector3f & a_vNormal, const Vector3f & a_vPoint)
{
    return -a_vNormal.x() * a_vPoint.x() - a_vNormal.y() * a_vPoint.y() - a_vNormal.z() * a_vPoint.z();
}

Vector3f SampleLobe(const Vector3f & a_vNormal, float c, float phi)
{
    float s = sqrtf(1.f - c * c);
    Vector3f K = Vector3f(s * cosf(phi), s * sinf(phi), c);
    Quaternionf q = Quaternionf::FromTwoVectors(Vector3f::UnitZ(), a_vNormal);

    return q._transformVector(K);
}

float BRDF_XPlus(float a_fD)
{
    if (a_fD > 0.f)
        return 1.f;
    return 0.f;
}

float BRDF_TanTheta(const Vector3f & a_vA, const Vector3f& a_vB)
{
    float aDotB = a_vA.dot(a_vB);
    if (AreSimilar(aDotB, 0.f))
        return 0.f;
    //return sqrtf(1.f - (aDotB * aDotB)) / fabsf(aDotB);
    return sqrtf(1.f - (aDotB * aDotB)) / aDotB;
}

float BRDF_D(const Vector3f & a_vM, const Vector3f& a_vNormal, float a_fAlpha)
{
    float mDotN = a_vM.dot(a_vNormal);
    float x = BRDF_XPlus(mDotN);

    // a_fAlpha = 1 to infinity, infinity is smoothest
    return x * ((a_fAlpha + 2.f) / PI_2) * pow(mDotN, a_fAlpha);
}

float BRDF_G1_A(float a_fA)
{
    if (a_fA < 1.6f)
    {
        float numerator = (3.535f * a_fA + 2.181f * (a_fA * a_fA));
        float denom = (1.f + 2.276f * a_fA + 2.577f * (a_fA * a_fA));
        if (AreSimilar(denom, 0.f))
            return 0.f;
        return numerator / denom;
    }
    else
        return 1.f;
}

float BRDF_G1(const Vector3f & a_vV, const Vector3f & a_vM, const Vector3f& a_vNormal, float a_fAlpha)
{
    float tanTheta = BRDF_TanTheta(a_vV, a_vNormal);
    if (AreSimilar(tanTheta, 0.f))
        return 1.f;

    float vDotN = a_vV.dot(a_vNormal);
    float vDotM = a_vV.dot(a_vM);
    if (vDotN > 1.f)
        return 1.f;

    float x;
    if (AreSimilar(vDotN, 0.f))
        return 0.f;
    else
        x = BRDF_XPlus(vDotM / vDotN);
    
    float a = sqrtf((a_fAlpha / 2.f + 1.f)) / tanTheta;

    return x * BRDF_G1_A(a);
}

float BRDF_G(const Vector3f& a_vOmegaO, const Vector3f& a_vOmegaI, const Vector3f & a_vM, const Vector3f & a_vNormal, float a_fAlpha)
{
    return BRDF_G1(a_vOmegaI, a_vM, a_vNormal, a_fAlpha) * BRDF_G1(a_vOmegaO, a_vM, a_vNormal, a_fAlpha);
}

Color BRDF_F(const Vector3f & a_vL, const Vector3f & a_vH, const Color& a_cKs)
{
    // F(L, H) = Ks + (1.f - Ks) *  pow(1.f - L.dot(H), 5)
    Color OneMinusKs = Color(1.f - a_cKs[0], 1.f - a_cKs[1], 1.f - a_cKs[2]);
    //float b = pow(1.f - fabsf(a_vL.normalized().dot(a_vH.normalized())), 5);
    float b = pow(1.f - fabsf(a_vL.normalized().dot(a_vH.normalized())), 5);
    return a_cKs + OneMinusKs * b;
}

Color BRDF_F_NotApprox(const Vector3f & a_vL, const Vector3f & a_vH, const Color & a_cKs, float a_fEtaI, float a_fEtaO)
{
    float c = fabsf(a_vL.dot(a_vH));
    float g = sqrtf(((a_fEtaO * a_fEtaO) / (a_fEtaI * a_fEtaI)) - 1.f + (c * c));
    float gMinusC = g - c;
    float gPlusC = g + c;

    if (AreSimilar(gPlusC, 0.f))
        return Color(0, 0, 0);

    float dNum = ((c * gPlusC) - 1.f) * ((c * gPlusC) - 1.f);
    float dDenom = ((c * gMinusC) - 1.f) * ((c * gMinusC) + 1.f);
    float d;
    if (AreSimilar(dDenom, 0.f))
        d = 0.f;
    else
        d = dNum / dDenom;

    return a_cKs * (0.5f * ((gMinusC * gMinusC) / (gPlusC * gPlusC)) * (1.f + d));
}

float SignFN(float a_fVal)
{
    return (a_fVal >= 0.f) ? 1.f : -1.f;
}

bool IsColorNAN(const Color & a_cColor)
{
    return isnan(a_cColor[0]) || isnan(a_cColor[1]) || isnan(a_cColor[2]);
}

bool IsColorINF(const Color & a_cColor)
{
    return isinf(a_cColor[0]) || isinf(a_cColor[1]) || isinf(a_cColor[2]);
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

std::mt19937_64 RNGen;
std::uniform_real_distribution<> MersenneTwisterRandom(0.0f, 1.0f);
// Call MersenneTwisterRandom(RNGen) to get a uniformly distributed random number in [0,1].

float MersenneRandFloat()
{
    return float(MersenneTwisterRandom(RNGen));
}
