#pragma once

#include "chunk.h"
#include "stream.h"

namespace Rw
{
struct String : Chunk
{
    Char *string;

    ~String();

    static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
    static void Write(Chunk *chunk, Stream *stream);

    inline static Chunk *Construct() { return new String; }
};

struct UnicodeString : Chunk
{
    Char *string;

    ~UnicodeString();

    static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
    static void Write(Chunk *chunk, Stream *stream);

    inline static Chunk *Construct() { return new UnicodeString; }
};
}