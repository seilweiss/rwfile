#pragma once

#include "chunk.h"
#include "stream.h"
#include "frame.h"
#include "geometry.h"

namespace Rw
{
struct Atomic : Chunk
{
    struct Struct : Chunk
    {
        Int32 frameIndex;
        Int32 geomIndex;
        Int32 flags;
        Int32 unused;

        static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
        static void Write(Chunk *chunk, Stream *stream);

        inline static Chunk *Construct() { return new Struct; }
    };

    Struct *GetStruct() const;
    Frame *GetFrame() const;
    Geometry *GetGeometry() const;

    inline static Chunk *Construct() { return new Atomic; }
};
}