#pragma once

#include "chunk.h"
#include "stream.h"

namespace Rw
{
struct Texture : Chunk
{
    enum FilterMode
    {
        FILTER_NA = 0,
        FILTER_NEAREST,
        FILTER_LINEAR,
        FILTER_MIPNEAREST,
        FILTER_MIPLINEAR,
        FILTER_LINEARMIPNEAREST,
        FILTER_LINEARMIPLINEAR,
        FILTER_MASK = 0xFF
    };

    enum AddressMode
    {
        ADDRESS_NA = 0,
        ADDRESS_WRAP,
        ADDRESS_MIRROR,
        ADDRESS_CLAMP,
        ADDRESS_BORDER,
        ADDRESS_UMASK = 0xF00,
        ADDRESS_VMASK = 0xF000,
        ADDRESS_MASK = (ADDRESS_UMASK | ADDRESS_VMASK)
    };

    enum StreamFlags
    {
        STREAMFLAGS_NA = 0x0,
        STREAMFLAGS_USERMIPMAPS = 0x1
    };

    struct Struct : Chunk
    {
        FilterMode filtering;
        AddressMode addressingU;
        AddressMode addressingV;
        StreamFlags flags;

        static void Read(Chunk *chunk, ChunkHeader *header, Stream *stream);
        static void Write(Chunk *chunk, Stream *stream);

        inline static Chunk *Construct() { return new Struct; }
    };

    Struct *GetStruct() const;

    inline static Chunk *Construct() { return new Texture; }
};
}