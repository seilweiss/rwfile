#include "../include/atomic.h"

#include "../include/clump.h"

namespace Rw
{
void Atomic::Struct::Read(Chunk *chunk, ChunkHeader *, Stream *stream)
{
    Struct *struc = (Struct *)chunk;

    stream->Read(&struc->frameIndex);
    stream->Read(&struc->geomIndex);
    stream->Read(&struc->flags);
    stream->Read(&struc->unused);
}

void Atomic::Struct::Write(Chunk *chunk, Stream *stream)
{
    Struct *struc = (Struct *)chunk;

    stream->Write(&struc->frameIndex);
    stream->Write(&struc->geomIndex);
    stream->Write(&struc->flags);
    stream->Write(&struc->unused);
}

Atomic::Struct *Atomic::GetStruct() const
{
    return (Struct *)GetChildByType(ID_STRUCT);
}

Frame *Atomic::GetFrame() const
{
    Struct *struc = this->GetStruct();

    if (struc && this->parent && this->parent->type == ID_CLUMP)
    {
        Clump *clump = (Clump *)this->parent;
        FrameList *frameList = clump->GetFrameList();

        if (frameList)
        {
            return frameList->GetFrame(struc->frameIndex);
        }
    }

    return NULL;
}

Geometry *Atomic::GetGeometry() const
{
    Struct *struc = GetStruct();

    if (struc && this->parent && this->parent->type == ID_CLUMP)
    {
        Clump *clump = (Clump *)this->parent;
        GeometryList *geomList = clump->GetGeometryList();

        if (geomList)
        {
            return geomList->GetGeometry(struc->geomIndex);
        }
    }

    return (Geometry *)GetChildByType(ID_GEOMETRY);
}
}
