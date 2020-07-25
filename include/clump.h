#pragma once

#include "chunk.h"
#include "stream.h"
#include "frame.h"
#include "geometry.h"
#include "atomic.h"

namespace Rw
{
struct Clump : Chunk
{
    struct Struct : Chunk
    {
        static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
        static void Write(Chunk *chunk, Stream *stream);

        inline static Chunk *Construct() { return new Struct; }
    };

    Struct *GetStruct() const;
    FrameList *GetFrameList() const;
    GeometryList *GetGeometryList() const;
    Atomic *GetAtomic(UInt32 index) const;

    UInt32 AtomicCount() const;
    UInt32 LightCount() const;
    UInt32 CameraCount() const;

    inline static Chunk *Construct() { return new Clump; }
};
}