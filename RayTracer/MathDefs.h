#pragma once

#ifndef MATH_DEFINES_H
#define MATH_DEFINES_H

constexpr bool      TEST_MODE = false;
const std::string   PASS = "PASS";
const std::string   FAIL = "!!!!! FAIL !!!!!";
constexpr float     EPSILON = 0.0001f;
constexpr float     PI = 3.14159265358979323846f;      // pi
constexpr float     PI_HALF = 1.57079632679489661923f; // pi/2;

constexpr float     DEG_TO_RAD = (3.14159265358979323846f / 180.0f);
constexpr float     RAD_TO_DEG = (180.0f / 3.14159265358979323846f);

constexpr int       RT_RAND_MAX = 0x7FFF;
constexpr float     FLOAT_EPSILON = 2.2204460492503131e-016f;

struct Point {
	float x, y;
};

typedef std::vector<Point> ControlPoints;

struct InterpolationItem {
	ControlPoints points;	// Control Points for bezier curve interpolation between start and end
	float amplitude;		// How much of an offset to give the result from the curve
};

#endif
