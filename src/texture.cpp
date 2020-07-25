#include "../include/texture.h"

namespace Rw
{
void Texture::Struct::Read(Chunk *chunk, ChunkHeader *header, Stream *stream)
{
    Struct *struc = (Struct *)chunk;
    UInt32 filterAndAddress;

    stream->Read(&filterAndAddress);

    struc->filtering = (FilterMode)(filterAndAddress & FILTER_MASK);
    struc->addressingU = (AddressMode)(filterAndAddress >> 8 & 0xF);
    struc->addressingV = (AddressMode)(filterAndAddress >> 12 & 0xF);
    struc->flags = (StreamFlags)(filterAndAddress >> 16 & 0xFF);
}

void Texture::Struct::Write(Chunk *chunk, Stream *stream)
{
    Struct *struc = (Struct *)chunk;

    UInt32 filterAndAddress =
        (struc->filtering) |
        (struc->addressingU << 8) |
        (struc->addressingV << 12) |
        (struc->flags << 16);

    stream->Write(&filterAndAddress);
}

Texture::Struct *Texture::GetStruct() const
{
    return (Struct *)GetChildByType(ID_STRUCT);
}
}