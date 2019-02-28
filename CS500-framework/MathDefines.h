#pragma once

#ifndef MATH_DEFINES_H
#define MATH_DEFINES_H

constexpr float     EPSILON = 0.0001f;
constexpr float     PI = 3.14159265358979323846f;       // pi
constexpr float     PI_2 = 2.f * PI;                    // pi * 2
constexpr float     PI_HALF = 1.57079632679489661923f;  // pi/2;
constexpr float     MATH_E = 2.71828f;

constexpr float     DEG_TO_RAD = (3.14159265358979323846f / 180.0f);
constexpr float     RAD_TO_DEG = (180.0f / 3.14159265358979323846f);

constexpr int       RT_RAND_MAX = 0x7FFF;
constexpr float     FLOAT_EPSILON = 2.2204460492503131e-016f;

constexpr float     RUSSIAN_ROULETTE = 0.8f;

constexpr float     MINIMUM = 0.0001f;

#endif
