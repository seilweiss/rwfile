#pragma once

#include "types.h"
#include "chunk.h"
#include "ids.h"

#include <cstdio>
#include <map>

namespace Rw
{
class Stream
{
public:
    enum OpenMode
    {
        OPEN_READ,
        OPEN_WRITE
    };

    enum Type
    {
        TYPE_NA,
        TYPE_MEMORY,
        TYPE_FILE
    };

    typedef Chunk *(*ChunkConstructor)();
    typedef void (*ChunkRead)(Chunk *chunk, ChunkHeader *header, Stream *stream);
    typedef void (*ChunkWrite)(Chunk *chunk, Stream *stream);

    struct ChunkType
    {
        struct Callbacks
        {
            ChunkConstructor constructor;
            ChunkRead read;
            ChunkWrite write;
        };

        Bool isComplex;
        std::map<UInt32, Callbacks> callbacks;
    };

    Stream();
    Stream(void *buffer, UInt32 length);
    Stream(const Char *filename, OpenMode openMode);

    static void RegisterChunkType(UInt32 type, UInt32 parentType, Bool isComplex,
                                  ChunkConstructor constructor, ChunkRead read = NULL,
                                  ChunkWrite write = NULL);

    void Open(void *buffer, UInt32 length);
    void Open(const Char *filename, OpenMode openMode);
    void Close();
    void Seek(UInt32 offset);
    UInt32 Tell();

    void Read(void *buffer, UInt32 length);

    template<class T>
    void Read(T *val);

    void Read(V3d *v);
    void Read(Sphere *s);
    void Read(RGBA *rgba);
    void Read(TexCoords *tc);
    void Read(SurfaceProperties *sp);

    void Write(const void *buffer, UInt32 length);

    template<class T>
    void Write(T *val);

    void Write(V3d *v);
    void Write(Sphere *s);
    void Write(RGBA *rgba);
    void Write(TexCoords *tc);
    void Write(SurfaceProperties *sp);

    Chunk *ReadChunk(Chunk *parent = NULL);
    void WriteChunk(Chunk *chunk);

    void ReadChunkHeader(ChunkHeader *header);
    void WriteChunkHeader(ChunkHeader *header, UInt32 *outLengthOffset = NULL);

private:
    static std::map<UInt32, ChunkType> chunkTypes;

    Type type;

    union
    {
        struct
        {
            UInt8 *buffer;
            UInt32 length;
            UInt32 offset;
        } memory;

        struct
        {
            FILE *handle;
        } file;
    };

    void Init();
};
}