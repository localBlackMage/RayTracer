#pragma once

#define NOMINMAX

#ifdef _WIN32
// Includes for Windows
#include <windows.h>
#include <cstdlib>
#include <limits>
#include <crtdbg.h>
#else
// Includes for Linux
#endif

// A good quality *thread-safe* Mersenne Twister random number generator.
#include <random>

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "float.h"

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;
#include <freeglut.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>






#include "rgbe.h"
#include "geom.h"

#include "NiceTypes.h"
#include "MathDefines.h"
#include "MathFunctions.h"

#include "Interval.h"
#include "BoundingBox.h"

#include "Ray.h"

#include "Shape.h"
#include "Sphere.h"
#include "Slab.h"
#include "Cube.h"
#include "Cyllinder.h"
#include "Triangle.h"

#include "ShapeList.h"

#include "Material.h"

#include "Camera.h"