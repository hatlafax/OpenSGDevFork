/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include <fstream>

#include "OSGBaseTypes.h"

#include "OSGAssimpMeshProcessor.h"
#include "OSGAssimpMaterialProcessor.h"
#include "OSGAssimpLog.h"

#include "OSGSceneFileHandler.h"

#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGGeoPositionsFields.h"
#include "OSGGeoProperty.h"

#ifdef OSG_WITH_ASSIMP
#pragma warning( push )
#pragma warning(disable : 4800)

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/ProgressHandler.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include <assimp/anim.h>
#include <assimp/metadata.h>
#include <assimp/vector3.h>
#include <assimp/color4.h>
#include <assimp/postprocess.h>

#pragma warning( pop )
#endif // OSG_WITH_ASSIMP

OSG_BEGIN_NAMESPACE

AssimpMeshProcessor::AssimpMeshProcessor(
    const AssimpOptions&            options,
    const std::string&              importer,
    const AssimpMaterialProcessor&  materialProcessor)
: _geometryMap()
, _options(options)
, _importer(importer)
, _materialProcessor(materialProcessor)
{
}

AssimpMeshProcessor::~AssimpMeshProcessor(void)
{
}

#ifdef OSG_WITH_ASSIMP
bool AssimpMeshProcessor::process(const aiScene* scene)
{
    OSG_ASSERT(scene && (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) == 0 && scene->mRootNode);

    //
    // End result: a map (_geometryMap) of Assimp geometry index to Geometry instances.
    //

    _geometryMap.clear();

    if (scene->HasMeshes())
    {
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
        {
            aiMesh* mesh = scene->mMeshes[i];

            //int N = scene->mNumMeshes;
            //int lower_bound = N/8+N/16+N/32 + 1;
            //int upper_bound = N/8+N/16+N/32 + 3;
            //if (!(lower_bound <= i  && i < upper_bound))
            //    continue;

            GeometryUnrecPtr geometry = process(mesh);
            _geometryMap.insert(GeometryMap::value_type(i, geometry));
        }
    }

    return true;
}

GeometryTransitPtr AssimpMeshProcessor::process(const aiMesh* mesh)
{
    if (!mesh)
        return GeometryTransitPtr(NULL);

    if (!mesh->HasFaces() || !mesh->HasPositions())
        return GeometryTransitPtr(NULL);

    ChunkMaterial* pMaterial = _materialProcessor.getMaterial(mesh->mMaterialIndex);
    if (!pMaterial)
        return GeometryTransitPtr(NULL);

    GeometryUnrecPtr geo = Geometry::createLocal();
    geo->setMaterial(pMaterial);

    UInt32 numVertices = mesh->mNumVertices;

    if (mesh->HasPositions())
    {
        GeoPnt3fPropertyUnrecPtr points = GeoPnt3fProperty::createLocal();
        MFPnt3f& rPoints = *(points->editFieldPtr());
        rPoints.resize(numVertices);

        for (UInt32 i = 0; i < mesh->mNumVertices; ++i)
            rPoints[i] = toPnt3f(mesh->mVertices[i]);

        geo->setPositions(points);
    }

    if (mesh->HasNormals())
    {
        GeoVec3fPropertyUnrecPtr normals = GeoVec3fProperty::createLocal();
        MFVec3f& rNormals = *(normals->editFieldPtr());
        rNormals.resize(numVertices);

        for (UInt32 i = 0; i < mesh->mNumVertices; ++i)
            rNormals[i] = toVec3f(mesh->mNormals[i]);

        geo->setNormals  (normals);
    }

    if (mesh->HasTangentsAndBitangents())
    {
        GeoVec3fPropertyUnrecPtr   tangents = GeoVec3fProperty::createLocal();
        GeoVec3fPropertyUnrecPtr bitangents = GeoVec3fProperty::createLocal();

        MFVec3f&   rTangents = *(  tangents->editFieldPtr());
        MFVec3f& rBiTangents = *(bitangents->editFieldPtr());

          rTangents.resize(numVertices);
        rBiTangents.resize(numVertices);

        for (UInt32 i = 0; i < mesh->mNumVertices; ++i)
        {
              rTangents[i] = toVec3f(mesh->  mTangents[i]);
            rBiTangents[i] = toVec3f(mesh->mBitangents[i]);
        }

        geo->setProperty(tangents,   Geometry::Attribute5Index);
        geo->setProperty(bitangents, Geometry::Attribute6Index);
    }

    for (UInt32 j = 0, k = Geometry::TexCoordsIndex; 
         j < AI_MAX_NUMBER_OF_TEXTURECOORDS && k <= Geometry::TexCoords7Index; 
         ++j)
    {
        if (mesh->HasTextureCoords(j))
        {
            switch (mesh->mNumUVComponents[j])
            {
                case 1:
                    {
                        GeoVec1fPropertyUnrecPtr texcoords = GeoVec1fProperty::createLocal();

                        MFVec1f& rTexcoords = *(texcoords->editFieldPtr());
                        rTexcoords.resize(numVertices);

                        for (UInt32 i = 0; i < mesh->mNumVertices; ++i)
                            rTexcoords[i] = toVec1f(mesh->mTextureCoords[j][i]);

                        geo->setProperty(texcoords, k);

                        k++;
                    }
                    break;
                case 2:
                    {
                        GeoVec2fPropertyUnrecPtr texcoords = GeoVec2fProperty::createLocal();

                        MFVec2f& rTexcoords = *(texcoords->editFieldPtr());
                        rTexcoords.resize(numVertices);

                        for (UInt32 i = 0; i < mesh->mNumVertices; ++i)
                            rTexcoords[i] = toVec2f(mesh->mTextureCoords[j][i]);

                        geo->setProperty(texcoords, k);

                        k++;
                    }
                    break;
                case 3:
                    {
                        GeoVec3fPropertyUnrecPtr texcoords = GeoVec3fProperty::createLocal();

                        MFVec3f& rTexcoords = *(texcoords->editFieldPtr());
                        rTexcoords.resize(numVertices);

                        for (UInt32 i = 0; i < mesh->mNumVertices; ++i)
                            rTexcoords[i] = toVec3f(mesh->mTextureCoords[j][i]);

                        geo->setProperty(texcoords, k);

                        k++;
                    }
                    break;
            }
        }
    }

    for (UInt32 j = 0, k = Geometry::Attribute3Index; 
         j < AI_MAX_NUMBER_OF_COLOR_SETS && k <= Geometry::Attribute4Index; 
         ++j)
    {
        if (mesh->HasVertexColors(j))
        {
            GeoColor4fPropertyUnrecPtr colors = GeoColor4fProperty::createLocal();

            MFColor4f& rColors = *(colors->editFieldPtr());
            rColors.resize(numVertices);

            for (UInt32 i = 0; i < mesh->mNumVertices; ++i)
                rColors[i] = toColor4f(mesh->mColors[j][i]);

            geo->setProperty(colors, k);

            k++;
        }
    }

    UInt32 numIndices = 0;
    for (UInt32 i = 0; i < mesh->mNumFaces; ++i)
    {
        numIndices += mesh->mFaces[i].mNumIndices;
    }

    GeoUInt32PropertyUnrecPtr indices = GeoUInt32Property::createLocal();
    GeoUInt32PropertyUnrecPtr lengths = GeoUInt32Property::createLocal();
    GeoUInt8PropertyUnrecPtr  types   = GeoUInt8Property ::createLocal();

    MFUInt32& rIndices = *(indices->editFieldPtr());
    MFUInt32& rLengths = *(lengths->editFieldPtr());
    MFUInt8&  rTypes   = *(types  ->editFieldPtr());

    rIndices.resize(numIndices);
    rLengths.resize(mesh->mNumFaces);
    rTypes  .resize(mesh->mNumFaces);

    UInt32 idx = 0;

    for (UInt32 i = 0; i < mesh->mNumFaces; ++i)
    {
        const aiFace& face = mesh->mFaces[i];

        for (UInt32 j = 0; j < face.mNumIndices; ++j, ++idx)
        {
            rIndices[idx] = face.mIndices[j];
        }

        rLengths[i] = face.mNumIndices;

        UInt8 type = GL_NONE;

        switch (face.mNumIndices)
        {
            case 1:  type = GL_POINTS;    break;
            case 2:  type = GL_LINES;     break;
            case 3:  type = GL_TRIANGLES; break;
            default: type = GL_POLYGON;
        }

        rTypes[i] = type;
    }

    geo->setIndices(indices);
    geo->setLengths(lengths);
    geo->setTypes(types);

    return GeometryTransitPtr(geo);
}

inline Pnt3f AssimpMeshProcessor::toPnt3f(const aiVector3D& v)
{
    return Pnt3f(v.x, v.y, v.z);
}

inline Vec1f AssimpMeshProcessor::toVec1f(const aiVector3D& v)
{
    return Vec1f(v.x);
}

inline Vec2f AssimpMeshProcessor::toVec2f(const aiVector3D& v)
{
    return Vec2f(v.x, v.y);
}

inline Vec3f AssimpMeshProcessor::toVec3f(const aiVector3D& v)
{
    return Vec3f(v.x, v.y, v.z);
}

inline Color4f AssimpMeshProcessor::toColor4f(const aiColor4D& c)
{
    return Color4f(c.r, c.g, c.b, c.a);
}

#endif // OSG_WITH_ASSIMP

OSG_END_NAMESPACE
