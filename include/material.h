#pragma once

#include "chunk.h"
#include "stream.h"

#include <vector>

namespace Rw
{
struct Material : Chunk
{
    struct Struct : Chunk
    {
        Int32 flags; // unused always 0
        RGBA color;
        Int32 unused;
        Bool textured;
        SurfaceProperties surfaceProps;

        static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
        static void Write(Chunk *chunk, Stream *stream);

        inline static Chunk *Construct() { return new Struct; }
    };

    Struct *GetStruct() const;

    inline static Chunk *Construct() { return new Material; }
};

struct MaterialList : Chunk
{
    struct Struct : Chunk
    {
        std::vector<Int32> matindex;

        static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
        static void Write(Chunk *chunk, Stream *stream);

        inline static Chunk *Construct() { return new Struct; }
    };

    Struct *GetStruct() const;
    Material *GetMaterial(UInt32 index) const;
    UInt32 MaterialCount() const;

    inline static Chunk *Construct() { return new MaterialList; }
};
}