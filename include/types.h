#pragma once

#include <cstdint>

namespace Rw
{
typedef uint32_t UInt32;
typedef uint16_t UInt16;
typedef uint8_t UInt8;

typedef int32_t Int32;
typedef int16_t Int16;
typedef int8_t Int8;

typedef Int32 Bool;
typedef float Real;
typedef char Char;

struct V3d
{
    Real x, y, z;
};

struct Sphere
{
    V3d center;
    Real radius;
};

struct RGBA
{
    UInt8 red, green, blue, alpha;
};

struct TexCoords
{
    Real u, v;
};

struct SurfaceProperties
{
    Real ambient, specular, diffuse;
};
}

#define NULL 0
#define TRUE 1
#define FALSE 0