#pragma once

#pragma once

#include "chunk.h"
#include "stream.h"

namespace Rw
{
struct Extension : Chunk
{
    inline static Chunk *Construct() { return new Extension; }
};
}