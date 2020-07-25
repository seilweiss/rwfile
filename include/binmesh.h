#pragma once

#include "chunk.h"
#include "stream.h"

#include <vector>

namespace Rw
{
struct BinMesh : Chunk
{
    struct Mesh
    {
        Int32 matIndex;
        std::vector<Int32> indices;
    };

    enum Flags
    {
        TRILIST = 0x0,
        TRISTRIP = 0x1,
        TRIFAN = 0x2,
        LINELIST = 0x4,
        POLYLINE = 0x8,
        POINTLIST = 0x10,
        PRIMMASK = 0xFF,
        UNINDEXED = 0x100
    };

    UInt32 flags;
    std::vector<Mesh> meshes;

    UInt32 TotalIndices() const;

    static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
    static void Write(Chunk *chunk, Stream *stream);

    inline static Chunk *Construct() { return new BinMesh; }
};
}