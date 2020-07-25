#pragma once

#include "chunk.h"
#include "stream.h"

#include <vector>

namespace Rw
{
struct Triangle
{
    UInt16 vertIndex[3];
    UInt16 matIndex;
};

struct MorphTarget
{
    Sphere boundingSphere;
    std::vector<V3d> verts;
    std::vector<V3d> normals;
};

struct Geometry : Chunk
{
    enum Flags
    {
        TRISTRIP = 0x1,
        POSITIONS = 0x2,
        TEXTURED = 0x4,
        PRELIT = 0x8,
        NORMALS = 0x10,
        LIGHT = 0x20,
        MODULATEMATERIALCOLOR = 0x40,
        TEXTURED2 = 0x80,
        NATIVE = 0x01000000,
        NATIVEINSTANCE = 0x02000000,
        FLAGSMASK = 0xFF,
        NATIVEFLAGSMASK = 0x0F000000,
        NUMTEXCOORDSMASK = 0xFF0000
    };

    struct Struct : Chunk
    {
        Int32 format;
        Int32 numVertices;

        std::vector<Triangle> triangles;
        std::vector<RGBA> preLitLum;
        std::vector<TexCoords> texCoords[8];
        std::vector<MorphTarget> morphTargets;

        inline Int32 GetFlags() const
        {
            return format & FLAGSMASK;
        }

        inline Int32 GetNumTexCoords() const
        {
            if (format & NUMTEXCOORDSMASK)
            {
                return (format & NUMTEXCOORDSMASK) >> 16;
            }

            if (format & TEXTURED2)
            {
                return 2;
            }

            if (format & TEXTURED)
            {
                return 1;
            }

            return 0;
        }

        static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
        static void Write(Chunk *chunk, Stream *stream);

        inline static Chunk *Construct() { return new Struct; }
    };

    inline Struct *GetStruct() const;

    inline static Chunk *Construct() { return new Geometry; }
};

struct GeometryList : Chunk
{
    struct Struct : Chunk
    {
        static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
        static void Write(Chunk *chunk, Stream *stream);

        inline static Chunk *Construct() { return new Struct; }
    };

    Struct *GetStruct() const;
    Geometry *GetGeometry(UInt32 index) const;
    UInt32 GeometryCount() const;
    
    inline static Chunk *Construct() { return new GeometryList; }
};
}