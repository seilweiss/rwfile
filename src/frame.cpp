#include "../include/frame.h"

namespace Rw
{
void FrameList::Struct::Read(Chunk *chunk, ChunkHeader *, Stream *stream)
{
    Struct *struc = (Struct *)chunk;
    Int32 numFrames;

    stream->Read(&numFrames);

    for (Int32 i = 0; i < numFrames; i++)
    {
        Frame frame;

        stream->Read(&frame.right);
        stream->Read(&frame.up);
        stream->Read(&frame.at);
        stream->Read(&frame.pos);
        stream->Read(&frame.parentIndex);
        stream->Read(&frame.data);

        struc->frames.push_back(frame);
    }
}

void FrameList::Struct::Write(Chunk *chunk, Stream *stream)
{
    Struct *struc = (Struct *)chunk;
    Int32 numFrames = (Int32)struc->frames.size();

    stream->Write(&numFrames);

    for (Int32 i = 0; i < numFrames; i++)
    {
        Frame &frame = struc->frames[i];

        stream->Write(&frame.right);
        stream->Write(&frame.up);
        stream->Write(&frame.at);
        stream->Write(&frame.pos);
        stream->Write(&frame.parentIndex);
        stream->Write(&frame.data);
    }
}

FrameList::Struct *FrameList::GetStruct() const
{
    return (Struct *)GetChildByType(ID_STRUCT);
}

Frame *FrameList::GetFrame(UInt32 index) const
{
    Struct *struc = GetStruct();

    if (struc)
    {
        return &struc->frames[index];
    }

    return NULL;
}

UInt32 FrameList::FrameCount() const
{
    Struct *struc = GetStruct();

    if (struc)
    {
        return (UInt32)struc->frames.size();
    }

    return 0;
}
}
