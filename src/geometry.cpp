#include "../include/geometry.h"

namespace Rw
{
void Geometry::Struct::Read(Chunk *chunk, ChunkHeader *, Stream *stream)
{
    Struct *struc = (Struct *)chunk;
    Int32 numTriangles, numMorphTargets;

    stream->Read(&struc->format);
    stream->Read(&numTriangles);
    stream->Read(&struc->numVertices);
    stream->Read(&numMorphTargets);

    if (!(struc->format & NATIVE))
    {
        if (struc->numVertices)
        {
            if (struc->format & PRELIT)
            {
                for (Int32 i = 0; i < struc->numVertices; i++)
                {
                    RGBA rgba;

                    stream->Read(&rgba);
                    struc->preLitLum.push_back(rgba);
                }
            }

            Int32 numTexCoordSets = struc->GetNumTexCoords();

            for (Int32 i = 0; i < numTexCoordSets; i++)
            {
                for (Int32 j = 0; j < struc->numVertices; j++)
                {
                    TexCoords tc;

                    stream->Read(&tc);
                    struc->texCoords[i].push_back(tc);
                }
            }

            for (Int32 i = 0; i < numTriangles; i++)
            {
                UInt32 vertex01;
                UInt32 vertex2Mat;

                stream->Read(&vertex01);
                stream->Read(&vertex2Mat);

                Triangle tri;

                tri.vertIndex[0] = vertex01 >> 16;
                tri.vertIndex[1] = vertex01;
                tri.vertIndex[2] = vertex2Mat >> 16;
                tri.matIndex = vertex2Mat;

                struc->triangles.push_back(tri);
            }
        }
    }

    for (Int32 i = 0; i < numMorphTargets; i++)
    {
        MorphTarget mt;
        Bool pointsPresent, normalsPresent;

        stream->Read(&mt.boundingSphere);
        stream->Read(&pointsPresent);
        stream->Read(&normalsPresent);

        if (pointsPresent)
        {
            for (Int32 j = 0; j < struc->numVertices; j++)
            {
                V3d v;
                stream->Read(&v);
                mt.verts.push_back(v);
            }
        }

        if (normalsPresent)
        {
            for (Int32 j = 0; j < struc->numVertices; j++)
            {
                V3d v;
                stream->Read(&v);
                mt.normals.push_back(v);
            }
        }

        struc->morphTargets.push_back(mt);
    }
}

void Geometry::Struct::Write(Chunk *chunk, Stream *stream)
{
    Struct *struc = (Struct *)chunk;
    Int32 numTriangles = (Int32)struc->triangles.size();
    Int32 numMorphTargets = (Int32)struc->morphTargets.size();

    stream->Write(&struc->format);
    stream->Write(&numTriangles);
    stream->Write(&struc->numVertices);
    stream->Write(&numMorphTargets);

    if (!(struc->format & NATIVE))
    {
        if (struc->numVertices)
        {
            if (struc->format & PRELIT)
            {
                for (Int32 i = 0; i < struc->numVertices; i++)
                {
                    RGBA &rgba = struc->preLitLum[i];

                    stream->Write(&rgba);
                }
            }

            Int32 numTexCoordSets = struc->GetNumTexCoords();

            for (Int32 i = 0; i < numTexCoordSets; i++)
            {
                for (Int32 j = 0; j < struc->numVertices; j++)
                {
                    TexCoords &tc = struc->texCoords[i][j];

                    stream->Write(&tc);
                }
            }

            for (Int32 i = 0; i < numTriangles; i++)
            {
                Triangle &tri = struc->triangles[i];

                UInt32 vertex01 = tri.vertIndex[0] << 16 | tri.vertIndex[1];
                UInt32 vertex2Mat = tri.vertIndex[2] << 16 | tri.matIndex;

                stream->Write(&vertex01);
                stream->Write(&vertex2Mat);
            }
        }
    }

    for (Int32 i = 0; i < numMorphTargets; i++)
    {
        MorphTarget &mt = struc->morphTargets[i];

        stream->Write(&mt.boundingSphere);

        Bool pointsPresent, normalsPresent;

        if (struc->format & NATIVE)
        {
            pointsPresent = FALSE;
            normalsPresent = FALSE;
        }
        else
        {
            pointsPresent = (mt.verts.size() > 0);
            normalsPresent = (mt.normals.size() > 0);
        }

        stream->Write(&pointsPresent);
        stream->Write(&normalsPresent);

        if (pointsPresent)
        {
            for (Int32 j = 0; j < struc->numVertices; j++)
            {
                stream->Write(&mt.verts[j]);
            }
        }

        if (normalsPresent)
        {
            for (Int32 j = 0; j < struc->numVertices; j++)
            {
                stream->Write(&mt.normals[j]);
            }
        }
    }
}

Geometry::Struct *Geometry::GetStruct() const
{
    return (Struct *)GetChildByType(ID_STRUCT);
}

void GeometryList::Struct::Read(Chunk *, ChunkHeader *, Stream *stream)
{
    Int32 numGeoms;

    stream->Read(&numGeoms);
}

void GeometryList::Struct::Write(Chunk *chunk, Stream *stream)
{
    Struct *struc = (Struct *)chunk;
    Int32 numGeoms = 0;

    if (struc->parent && struc->parent->type == ID_GEOMETRYLIST)
    {
        GeometryList *geomList = (GeometryList *)struc->parent;
        numGeoms = geomList->GeometryCount();
    }

    stream->Write(&numGeoms);
}

GeometryList::Struct *GeometryList::GetStruct() const
{
    return (Struct *)GetChildByType(ID_STRUCT);
}

Geometry *GeometryList::GetGeometry(UInt32 index) const
{
    return (Geometry *)GetChildByType(ID_GEOMETRY, index);
}

UInt32 GeometryList::GeometryCount() const
{
    return ChildCountByType(ID_GEOMETRY);
}
}
