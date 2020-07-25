#include "../include/hanim.h"

namespace Rw
{
void HAnimHierarchy::Read(Chunk *chunk, ChunkHeader *header, Stream *stream)
{
    HAnimHierarchy *hanim = (HAnimHierarchy *)chunk;

    Int32 const256, numNodes;

    stream->Read(&const256);
    stream->Read(&hanim->id);
    stream->Read(&numNodes);

    if (numNodes > 0)
    {
        stream->Read(&hanim->flags);
        stream->Read(&hanim->maxInterpKeyFrameSize);

        for (Int32 i = 0; i < numNodes; i++)
        {
            NodeInfo node;

            stream->Read(&node.nodeID);
            stream->Read(&node.nodeIndex);
            stream->Read(&node.flags);

            hanim->nodes.push_back(node);
        }
    }
}

void HAnimHierarchy::Write(Chunk *chunk, Stream *stream)
{
    HAnimHierarchy *hanim = (HAnimHierarchy *)chunk;

    Int32 const256 = 256;
    Int32 numNodes = (Int32)hanim->nodes.size();

    stream->Write(&const256);
    stream->Write(&hanim->id);

    if (numNodes == 0 || (hanim->flags & SUBHIERARCHY))
    {
        numNodes = 0;
        stream->Write(&numNodes);
    }
    else
    {
        stream->Write(&numNodes);
        stream->Write(&hanim->flags);
        stream->Write(&hanim->maxInterpKeyFrameSize);

        for (Int32 i = 0; i < numNodes; i++)
        {
            NodeInfo &node = hanim->nodes[i];

            stream->Write(&node.nodeID);
            stream->Write(&node.nodeIndex);
            stream->Write(&node.flags);
        }
    }
}
}