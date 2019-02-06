#pragma once

using uint8     = unsigned char;
using uint16    = unsigned short;
using uint32    = unsigned int;
using uint64    = unsigned long long;
using int8      = signed char;
using int16     = short;
using int32     = int;
using int64     = long long;

using byte      = unsigned char;

#ifdef _WIN64       
using ulong = unsigned long long;
#else               
using ulong = unsigned long;
#endif

const float INF = std::numeric_limits<float>::max();