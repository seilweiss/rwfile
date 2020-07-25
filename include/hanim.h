#pragma once

#include "chunk.h"
#include "stream.h"

#include <vector>

namespace Rw
{
struct HAnimHierarchy : Chunk
{
    struct NodeInfo
    {
        Int32 nodeID;
        Int32 nodeIndex;
        Int32 flags;
    };

    enum Flags
    {
        SUBHIERARCHY = 0x1,
        NOMATRICES = 0x2,
        UPDATEMODELLINGMATRICES = 0x1000,
        UPDATELTMS = 0x2000,
        LOCALSPACEMATRICES = 0x4000
    };

    enum NodeInfoFlags
    {
        POPPARENTMATRIX = 0x1,
        PUSHPARENTMATRIX = 0x2
    };

    Int32 id;
    Int32 flags;
    Int32 maxInterpKeyFrameSize;

    std::vector<NodeInfo> nodes;

    static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
    static void Write(Chunk *chunk, Stream *stream);

    inline static Chunk *Construct() { return new HAnimHierarchy; }
};
}