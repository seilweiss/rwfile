#pragma once

#include "types.h"

#include <vector>

namespace Rw
{
struct ChunkHeader
{
    UInt32 type;
    UInt32 length;
    UInt32 libraryID;
};

struct Chunk
{
    Chunk *parent;
    Chunk *next;
    Chunk *child;
    UInt32 type;
    UInt32 version;
    UInt32 buildNum;
    Bool isUnknown;

    void AddChild(Chunk *chunk);
    void RemoveChild(Chunk *chunk);
    Chunk *GetChild(UInt32 index) const;
    Chunk *GetChildByType(UInt32 type, UInt32 index = 0) const;
    UInt32 ChildCount() const;
    UInt32 ChildCountByType(UInt32 type) const;
    void SetParent(Chunk *newParent);
    void SetVersionRecursive(UInt32 version);
    void SetBuildNumRecursive(UInt32 buildNum);
};

struct UnknownChunk :  Chunk
{
    Char *data;
    UInt32 length;
};
}