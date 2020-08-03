#include "../include/clump.h"

namespace Rw
{
void Clump::Struct::Read(Chunk *, ChunkHeader *, Stream *stream)
{
    Int32 numAtomics, numLights, numCameras;

    stream->Read(&numAtomics);
    stream->Read(&numLights);
    stream->Read(&numCameras);
}

void Clump::Struct::Write(Chunk *chunk, Stream *stream)
{
    Struct *struc = (Struct *)chunk;
    Int32 numAtomics = 0;
    Int32 numLights = 0;
    Int32 numCameras = 0;

    if (struc->parent && struc->parent->type == ID_CLUMP)
    {
        Clump *clump = (Clump *)struc->parent;

        numAtomics = clump->AtomicCount();
        numLights = clump->LightCount();
        numCameras = clump->CameraCount();
    }

    stream->Write(&numAtomics);
    stream->Write(&numLights);
    stream->Write(&numCameras);
}

Clump::Struct *Clump::GetStruct() const
{
    return (Struct *)GetChildByType(ID_STRUCT);
}

FrameList *Clump::GetFrameList() const
{
    return (FrameList *)GetChildByType(ID_FRAMELIST);
}

GeometryList *Clump::GetGeometryList() const
{
    return (GeometryList *)GetChildByType(ID_GEOMETRYLIST);
}

Atomic *Clump::GetAtomic(UInt32 index) const
{
    return (Atomic *)GetChildByType(ID_ATOMIC, index);
}

UInt32 Clump::AtomicCount() const
{
    return ChildCountByType(ID_ATOMIC);
}

UInt32 Clump::LightCount() const
{
    return ChildCountByType(ID_LIGHT);
}

UInt32 Clump::CameraCount() const
{
    return ChildCountByType(ID_CAMERA);
}
}
