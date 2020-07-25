#include "../include/material.h"

namespace Rw
{
void Material::Struct::Read(Chunk *chunk, ChunkHeader *header, Stream *stream)
{
    Struct *struc = (Struct *)chunk;

    stream->Read(&struc->flags);
    stream->Read(&struc->color);
    stream->Read(&struc->unused);
    stream->Read(&struc->textured);
    stream->Read(&struc->surfaceProps);
}

void Material::Struct::Write(Chunk *chunk, Stream *stream)
{
    Struct *struc = (Struct *)chunk;

    stream->Write(&struc->flags);
    stream->Write(&struc->color);
    stream->Write(&struc->unused);
    stream->Write(&struc->textured);
    stream->Write(&struc->surfaceProps);
}

Material::Struct *Material::GetStruct() const
{
    return (Struct *)GetChildByType(ID_STRUCT);
}

void MaterialList::Struct::Read(Chunk *chunk, ChunkHeader *header, Stream *stream)
{
    Struct *struc = (Struct *)chunk;
    Int32 len;

    stream->Read(&len);

    for (Int32 i = 0; i < len; i++)
    {
        Int32 index;

        stream->Read(&index);
        struc->matindex.push_back(index);
    }
}

void MaterialList::Struct::Write(Chunk *chunk, Stream *stream)
{
    Struct *struc = (Struct *)chunk;
    Int32 len = (Int32)struc->matindex.size();

    stream->Write(&len);

    for (Int32 i = 0; i < len; i++)
    {
        Int32 index = struc->matindex[i];

        stream->Write(&index);
    }
}

MaterialList::Struct *MaterialList::GetStruct() const
{
    return (Struct *)GetChildByType(ID_STRUCT);
}

Material *MaterialList::GetMaterial(UInt32 index) const
{
    return (Material *)GetChildByType(ID_MATERIAL, index);
}

UInt32 MaterialList::MaterialCount() const
{
    return ChildCountByType(ID_MATERIAL);
}
}