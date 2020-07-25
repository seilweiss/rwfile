#include "../include/stream.h"

#include "../include/ids.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define RW_LIBRARYID_PACK(version, buildNum)            \
    ( ((((version) - 0x30000) & 0x3FF00) << 14) |       \
      (((version) & 0x3F) << 16) |                      \
      ((buildNum) & 0xFFFF) )

#define RW_LIBRARYID_UNPACK_VERSION(libraryID)          \
    ( ((((libraryID) >> 14) & 0x3FF00) + 0x30000) |      \
      (((libraryID) >> 16) & 0x3F) )

#define RW_LIBRARYID_UNPACK_BUILDNUM(libraryID)         \
    ( (libraryID) & 0xFFFF )

namespace Rw
{
Bool CheckShouldSwap()
{
    Int32 x = 1;

    return (((Char *)&x)[0] == 0);
}

Bool shouldSwap = CheckShouldSwap();

template<class T>
inline void Swap(T *val)
{
    char *buffer = (char *)val;
    char tmp;

    switch (sizeof(*val))
    {
    case 1:
        break;
    case 2:
        tmp = buffer[0];

        buffer[0] = buffer[1];
        buffer[1] = tmp;

        break;
    case 4:
        tmp = buffer[0];

        buffer[0] = buffer[4];
        buffer[4] = tmp;

        tmp = buffer[1];

        buffer[1] = buffer[2];
        buffer[2] = tmp;

        break;
    }
}

std::map<UInt32, Stream::ChunkType> Stream::chunkTypes;

void Stream::Init()
{
    this->type = TYPE_NA;
    this->memory.buffer = NULL;
    this->memory.length = 0;
    this->memory.offset = 0;
    this->file.handle = NULL;
}

Stream::Stream()
{
    Init();
}

Stream::Stream(void *buffer, UInt32 length)
{
    Open(buffer, length);
}

Stream::Stream(const Char *filename, OpenMode openMode)
{
    Open(filename, openMode);
}

void Stream::RegisterChunkType(UInt32 type, UInt32 parentType, Bool isComplex,
                               ChunkConstructor constructor, ChunkRead read,
                               ChunkWrite write)
{
    ChunkType &chunkType = Stream::chunkTypes[type];

    chunkType.isComplex = isComplex;

    ChunkType::Callbacks &callbacks = chunkType.callbacks[parentType];
    
    callbacks.constructor = constructor;
    callbacks.read = read;
    callbacks.write = write;
}

void Stream::Open(void *buffer, UInt32 length)
{
    Close();

    this->type = TYPE_MEMORY;
    this->memory.buffer = (UInt8 *)buffer;
    this->memory.length = length;
    this->memory.offset = 0;
}

void Stream::Open(const Char *filename, OpenMode openMode)
{
    Close();

    this->type = TYPE_FILE;

    if (openMode == OPEN_READ)
    {
        fopen_s(&this->file.handle, filename, "rb");
    }
    else
    {
        fopen_s(&this->file.handle, filename, "wb");
    }
}

void Stream::Close()
{
    if (this->type == TYPE_FILE)
    {
        if (this->file.handle)
        {
            fclose(this->file.handle);
        }
    }

    Init();
}

void Stream::Seek(UInt32 offset)
{
    if (this->type == TYPE_MEMORY)
    {
        this->memory.offset = offset;
    }
    else if (this->type == TYPE_FILE)
    {
        fseek(this->file.handle, offset, SEEK_SET);
    }
}

UInt32 Stream::Tell()
{
    if (this->type == TYPE_MEMORY)
    {
        return this->memory.offset;
    }
    else if (this->type == TYPE_FILE)
    {
        return ftell(this->file.handle);
    }

    return 0;
}

void Stream::Read(void *buffer, UInt32 length)
{
    if (this->type == TYPE_MEMORY)
    {
        memcpy(buffer, this->memory.buffer + this->memory.offset, length);
        this->memory.offset += length;
    }
    else if (this->type == TYPE_FILE)
    {
        fread(buffer, length, 1, this->file.handle);
    }
}

template<class T>
void Stream::Read(T *val)
{
    Read((Char *)val, sizeof(*val));

    if (shouldSwap)
    {
        Swap(val);
    }
}

template void Stream::Read(UInt32 *val);
template void Stream::Read(UInt16 *val);
template void Stream::Read(UInt8 *val);
template void Stream::Read(Int32 *val);
template void Stream::Read(Int16 *val);
template void Stream::Read(Int8 *val);
template void Stream::Read(Real *val);
template void Stream::Read(Bool *val);

void Stream::Read(V3d *v)
{
    Read(&v->x);
    Read(&v->y);
    Read(&v->z);
}

void Stream::Read(Sphere *s)
{
    Read(&s->center);
    Read(&s->radius);
}

void Stream::Read(RGBA *rgba)
{
    Read(&rgba->red);
    Read(&rgba->green);
    Read(&rgba->blue);
    Read(&rgba->alpha);
}

void Stream::Read(TexCoords *tc)
{
    Read(&tc->u);
    Read(&tc->v);
}

void Stream::Read(SurfaceProperties *sp)
{
    Read(&sp->ambient);
    Read(&sp->specular);
    Read(&sp->diffuse);
}

void Stream::Write(const void *buffer, UInt32 length)
{
    if (this->type == TYPE_MEMORY)
    {
        memcpy(this->memory.buffer + this->memory.offset, buffer, length);
        this->memory.offset += length;
    }
    else if (this->type == TYPE_FILE)
    {
        fwrite(buffer, length, 1, this->file.handle);
    }
}

template<class T>
void Stream::Write(T *val)
{
    if (shouldSwap)
    {
        Swap(val);
    }

    Write((Char *)val, sizeof(*val));
}

template void Stream::Write(UInt32 *val);
template void Stream::Write(UInt16 *val);
template void Stream::Write(UInt8 *val);
template void Stream::Write(Int32 *val);
template void Stream::Write(Int16 *val);
template void Stream::Write(Int8 *val);
template void Stream::Write(Real *val);
template void Stream::Write(Bool *val);

void Stream::Write(V3d *v)
{
    Write(&v->x);
    Write(&v->y);
    Write(&v->z);
}

void Stream::Write(Sphere *s)
{
    Write(&s->center);
    Write(&s->radius);
}

void Stream::Write(RGBA *rgba)
{
    Write(&rgba->red);
    Write(&rgba->green);
    Write(&rgba->blue);
    Write(&rgba->alpha);
}

void Stream::Write(TexCoords *tc)
{
    Write(&tc->u);
    Write(&tc->v);
}

void Stream::Write(SurfaceProperties *sp)
{
    Write(&sp->ambient);
    Write(&sp->specular);
    Write(&sp->diffuse);
}

void Stream::ReadChunkHeader(ChunkHeader *header)
{
    Read(&header->type);
    Read(&header->length);
    Read(&header->libraryID);
}

Chunk *Stream::ReadChunk(Chunk *parent)
{
    Chunk *chunk = NULL;
    ChunkHeader header;

    ReadChunkHeader(&header);

    UInt32 version = RW_LIBRARYID_UNPACK_VERSION(header.libraryID);
    UInt32 buildNum = RW_LIBRARYID_UNPACK_BUILDNUM(header.libraryID);

    UInt32 end = Tell() + header.length;

    Bool isComplex = FALSE;

    if (Stream::chunkTypes.find(header.type) != Stream::chunkTypes.end())
    {
        ChunkType &chunkType = Stream::chunkTypes[header.type];
        ChunkType::Callbacks *callbacks = NULL;

        isComplex = chunkType.isComplex;

        UInt32 parentType = (parent) ? parent->type : ID_NA;

        if (chunkType.callbacks.find(parentType) != chunkType.callbacks.end())
        {
            callbacks = &chunkType.callbacks[parentType];
        }
        else if (chunkType.callbacks.find(ID_NA) != chunkType.callbacks.end())
        {
            callbacks = &chunkType.callbacks[ID_NA];
        }

        if (callbacks && callbacks->constructor)
        {
            chunk = callbacks->constructor();

            chunk->type = header.type;
            chunk->version = version;
            chunk->buildNum = buildNum;
            chunk->isUnknown = FALSE;
            chunk->parent = parent;
            chunk->next = NULL;
            chunk->child = NULL;

            if (callbacks->read)
            {
                callbacks->read(chunk, &header, this);
            }
        }
    }

    if (!chunk)
    {
        UnknownChunk *unknownChunk = new UnknownChunk;

        unknownChunk->type = header.type;
        unknownChunk->version = version;
        unknownChunk->buildNum = buildNum;
        unknownChunk->isUnknown = TRUE;
        unknownChunk->parent = parent;
        unknownChunk->next = NULL;
        unknownChunk->child = NULL;

        if (isComplex)
        {
            unknownChunk->data = NULL;
            unknownChunk->length = 0;
        }
        else
        {
            unknownChunk->data = (Char *)malloc(header.length);
            unknownChunk->length = header.length;

            if (unknownChunk->data)
            {
                Read(unknownChunk->data, header.length);
            }
        }

        chunk = unknownChunk;
    }

    if (isComplex)
    {
        while (Tell() < end)
        {
            Chunk *child = ReadChunk(chunk);
            chunk->AddChild(child);
        }
    }

    Seek(end);

    return chunk;
}

void Stream::WriteChunkHeader(ChunkHeader *header, UInt32 *outLengthOffset)
{
    Write(&header->type);
    
    if (outLengthOffset)
    {
        *outLengthOffset = Tell();
    }

    Write(&header->length);
    Write(&header->libraryID);
}

void Stream::WriteChunk(Chunk *chunk)
{
    ChunkHeader header;

    header.type = chunk->type;
    header.length = 0;
    header.libraryID = RW_LIBRARYID_PACK(chunk->version, chunk->buildNum);

    UInt32 lengthOffset;
    UInt32 start;

    WriteChunkHeader(&header, &lengthOffset);

    start = Tell();

    if (chunk->isUnknown)
    {
        UnknownChunk *unknownChunk = (UnknownChunk *)chunk;

        if (unknownChunk->data)
        {
            Write(unknownChunk->data, unknownChunk->length);
        }
    }
    else
    {
        if (Stream::chunkTypes.find(header.type) != Stream::chunkTypes.end())
        {
            ChunkType &chunkType = Stream::chunkTypes[header.type];
            ChunkType::Callbacks *callbacks = NULL;

            UInt32 parentType = (chunk->parent) ? chunk->parent->type : ID_NA;

            if (chunkType.callbacks.find(parentType) != chunkType.callbacks.end())
            {
                callbacks = &chunkType.callbacks[parentType];
            }
            else if (chunkType.callbacks.find(ID_NA) != chunkType.callbacks.end())
            {
                callbacks = &chunkType.callbacks[ID_NA];
            }

            if (callbacks && callbacks->write)
            {
                callbacks->write(chunk, this);
            }
        }
    }

    Chunk *child = chunk->child;

    while (child)
    {
        WriteChunk(child);
        child = child->next;
    }

    UInt32 end = Tell();
    UInt32 length = end - start;

    Seek(lengthOffset);
    Write(&length);
    Seek(end);
}
}