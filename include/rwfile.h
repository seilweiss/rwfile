#pragma once

#include "types.h"
#include "ids.h"
#include "chunk.h"
#include "stream.h"
#include "string.h"
#include "extension.h"
#include "texture.h"
#include "material.h"
#include "clump.h"
#include "geometry.h"
#include "hanim.h"
#include "binmesh.h"

namespace Rw
{
inline void RegisterDefaultChunkTypes()
{
    Stream::RegisterChunkType(ID_STRUCT, ID_NA, FALSE, NULL);

    Stream::RegisterChunkType(ID_STRING, ID_NA, FALSE, String::Construct,
                              String::Read, String::Write);

    Stream::RegisterChunkType(ID_EXTENSION, ID_NA, TRUE, Extension::Construct);
    Stream::RegisterChunkType(ID_CAMERA, ID_NA, TRUE, NULL);

    Stream::RegisterChunkType(ID_TEXTURE, ID_NA, TRUE, Texture::Construct);
    Stream::RegisterChunkType(ID_STRUCT, ID_TEXTURE, FALSE, Texture::Struct::Construct,
                              Texture::Struct::Read, Texture::Struct::Write);

    Stream::RegisterChunkType(ID_MATERIAL, ID_NA, TRUE, Material::Construct);
    Stream::RegisterChunkType(ID_STRUCT, ID_MATERIAL, FALSE, Material::Struct::Construct,
                              Material::Struct::Read, Material::Struct::Write);

    Stream::RegisterChunkType(ID_MATLIST, ID_NA, TRUE, MaterialList::Construct);
    Stream::RegisterChunkType(ID_STRUCT, ID_MATLIST, FALSE, MaterialList::Struct::Construct,
                              MaterialList::Struct::Read, MaterialList::Struct::Write);

    Stream::RegisterChunkType(ID_ATOMICSECT, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_PLANESECT, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_WORLD, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_SPLINE, ID_NA, FALSE, NULL);
    Stream::RegisterChunkType(ID_MATRIX, ID_NA, FALSE, NULL);

    Stream::RegisterChunkType(ID_FRAMELIST, ID_NA, TRUE, FrameList::Construct);
    Stream::RegisterChunkType(ID_STRUCT, ID_FRAMELIST, FALSE, FrameList::Struct::Construct,
                              FrameList::Struct::Read, FrameList::Struct::Write);

    Stream::RegisterChunkType(ID_GEOMETRY, ID_NA, TRUE, Geometry::Construct);
    Stream::RegisterChunkType(ID_STRUCT, ID_GEOMETRY, FALSE, Geometry::Struct::Construct,
                              Geometry::Struct::Read, Geometry::Struct::Write);

    Stream::RegisterChunkType(ID_CLUMP, ID_NA, TRUE, Clump::Construct);
    Stream::RegisterChunkType(ID_STRUCT, ID_CLUMP, FALSE, Clump::Struct::Construct,
                              Clump::Struct::Read, Clump::Struct::Write);

    Stream::RegisterChunkType(ID_LIGHT, ID_NA, TRUE, NULL);

    Stream::RegisterChunkType(ID_UNICODESTRING, ID_NA, FALSE, UnicodeString::Construct,
                              UnicodeString::Read, UnicodeString::Write);

    Stream::RegisterChunkType(ID_ATOMIC, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_TEXTURENATIVE, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_TEXDICTIONARY, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_ANIMDATABASE, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_IMAGE, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_SKINANIMATION, ID_NA, TRUE, NULL);

    Stream::RegisterChunkType(ID_GEOMETRYLIST, ID_NA, TRUE, GeometryList::Construct);
    Stream::RegisterChunkType(ID_STRUCT, ID_GEOMETRYLIST, FALSE, GeometryList::Struct::Construct,
                              GeometryList::Struct::Read, GeometryList::Struct::Write);

    Stream::RegisterChunkType(ID_ANIMANIMATION, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_TEAM, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_CROWD, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_DMORPHANIMATION, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_RIGHTTORENDER, ID_NA, FALSE, NULL);
    Stream::RegisterChunkType(ID_MTEFFECTNATIVE, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_MTEFFECTDICT, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_TEAMDICTIONARY, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_PITEXDICTIONARY, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_TOC, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_PRTSTDGLOBALDATA, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_ALTPIPE, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_PIPEDS, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_PATCHMESH, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_CHUNKGROUPSTART, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_CHUNKGROUPEND, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_UVANIMDICT, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_COLLTREE, ID_NA, TRUE, NULL);
    Stream::RegisterChunkType(ID_ENVIRONMENT, ID_NA, TRUE, NULL);

    Stream::RegisterChunkType(ID_PLUGIN_MORPH, ID_NA, FALSE, NULL);
    Stream::RegisterChunkType(ID_PLUGIN_SKYMIPMAPVAL, ID_NA, FALSE, NULL);

    Stream::RegisterChunkType(ID_PLUGIN_HANIM, ID_NA, FALSE, HAnimHierarchy::Construct,
                              HAnimHierarchy::Read, HAnimHierarchy::Write);

    Stream::RegisterChunkType(ID_PLUGIN_BINMESH, ID_NA, FALSE, BinMesh::Construct,
                              BinMesh::Read, BinMesh::Write);

    Stream::RegisterChunkType(ID_PLUGIN_NATIVEDATA, ID_NA, FALSE, NULL);
}
}