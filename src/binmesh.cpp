#include "../include/binmesh.h"

namespace Rw
{
UInt32 BinMesh::TotalIndices() const
{
    UInt32 total = 0;
    UInt32 numMeshes = (UInt32)this->meshes.size();

    for (UInt32 i = 0; i < numMeshes; i++)
    {
        const Mesh &m = this->meshes[i];

        total += (UInt32)m.indices.size();
    }

    return total;
}

void BinMesh::Read(Chunk *chunk, ChunkHeader *, Stream *stream)
{
    BinMesh *binmesh = (BinMesh *)chunk;
    UInt32 numMeshes, totalIndicesInMesh;

    stream->Read(&binmesh->flags);
    stream->Read(&numMeshes);
    stream->Read(&totalIndicesInMesh);

    for (UInt32 i = 0; i < numMeshes; i++)
    {
        Mesh m;
        UInt32 numIndices;

        stream->Read(&numIndices);
        stream->Read(&m.matIndex);

        for (UInt32 j = 0; j < numIndices; j++)
        {
            Int32 index;

            stream->Read(&index);
            m.indices.push_back(index);
        }

        binmesh->meshes.push_back(m);
    }
}

void BinMesh::Write(Chunk *chunk, Stream *stream)
{
    BinMesh *binmesh = (BinMesh *)chunk;
    UInt32 numMeshes = (UInt32)binmesh->meshes.size();
    UInt32 totalIndicesInMesh = binmesh->TotalIndices();

    stream->Write(&binmesh->flags);
    stream->Write(&numMeshes);
    stream->Write(&totalIndicesInMesh);

    for (UInt32 i = 0; i < numMeshes; i++)
    {
        Mesh &m = binmesh->meshes[i];
        UInt32 numIndices = (UInt32)m.indices.size();

        stream->Write(&numIndices);
        stream->Write(&m.matIndex);

        for (UInt32 j = 0; j < numIndices; j++)
        {
            Int32 index = m.indices[j];

            stream->Write(&index);
        }
    }
}
}
