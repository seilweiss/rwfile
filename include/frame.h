#pragma once

#include "chunk.h"
#include "stream.h"

#include <vector>

namespace Rw
{
struct Frame
{
    V3d right, up, at, pos;
    Int32 parentIndex;
    UInt32 data;
};

struct FrameList : Chunk
{
    struct Struct : Chunk
    {
        std::vector<Frame> frames;

        static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
        static void Write(Chunk *chunk, Stream *stream);

        inline static Chunk *Construct() { return new Struct; }
    };

    Struct *GetStruct() const;
    Frame *GetFrame(UInt32 index) const;
    UInt32 FrameCount() const;

    inline static Chunk *Construct() { return new FrameList; }
};
}