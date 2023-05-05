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

#ifndef _OSGASSIMPMATERIALPROCESSOR_H_
#define _OSGASSIMPMATERIALPROCESSOR_H_

/*! \file OSGAssimpMaterialProcessor.h
    \ingroup GrpLoader
 */

#include <map>

#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"
#include "OSGIOFileTypeBase.h"
#include "OSGChunkMaterial.h"
#include "OSGImage.h"
#include "OSGHashKeyToFieldContainerMap.h"

#include "OSGAssimpOptions.h"

#ifdef OSG_WITH_ASSIMP

struct aiScene;
struct aiMaterial;
struct aiTexture;
enum aiTextureType;

#endif // OSG_WITH_ASSIMP

OSG_BEGIN_NAMESPACE

class MaterialDesc;
class TextureDesc;

class OSG_CONTRIBTECHNIQUES_DLLMAPPING AssimpMaterialProcessor
{
    /*==========================  PUBLIC  =================================*/
public:
    /*---------------------------------------------------------------------*/
    /*! \name Set/Get                                                      */
    /*! \{                                                                 */

    ChunkMaterial*  getMaterial (unsigned int idx) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name examine                                                      */
    /*! \{                                                                 */
#ifdef OSG_WITH_ASSIMP
    bool            process     (const aiScene* scene);
#endif
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor/Destructor                                       */
    /*! \{                                                                 */

    explicit  AssimpMaterialProcessor(
                            const AssimpOptions& options, 
                            const std::string&   importer,
                            const std::string&   directory);
             ~AssimpMaterialProcessor(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:
#ifdef OSG_WITH_ASSIMP
    ImageTransitPtr process     (const aiTexture*  texture);
    bool            process     (const aiScene* scene, const aiMaterial* mat, MaterialDesc* matDesc);
    void            process     (const aiScene* scene, const aiMaterial* mat, aiTextureType type, MaterialDesc* matDesc);

    void            adaptTextureImageFile   ();
    bool            checkORMTextureSupport  (const aiMaterial* mat) const;
#endif

private:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef AssimpMaterialProcessor      Self;

    typedef std::map<UInt32,      ChunkMaterialUnrecPtr> MaterialMap;
    typedef std::map<const void*, ImageUnrecPtr>         ImageMap;
    typedef std::vector<UInt8>                           UVDimensionStore;

    struct MeshInfo
    {
        MeshInfo()
            : hasNormals      (false)
            , hasPositions    (false)
            , hasTangents     (false)
            , numUVChannels   (0)
            , numColorChannels(0)
            , uvDimensions    () {}

        MeshInfo(const MeshInfo& rhs)
            : hasNormals      (rhs.hasNormals)
            , hasPositions    (rhs.hasPositions)
            , hasTangents     (rhs.hasTangents)
            , numUVChannels   (rhs.numUVChannels)
            , numColorChannels(rhs.numColorChannels)
            , uvDimensions    (rhs.uvDimensions) {}

        MeshInfo& operator=(const MeshInfo& rhs)
        {
            if (&rhs != this)
            {
                hasNormals       = rhs.hasNormals;
                hasPositions     = rhs.hasPositions;
                hasTangents      = rhs.hasTangents;
                numUVChannels    = rhs.numUVChannels;
                numColorChannels = rhs.numColorChannels;
                uvDimensions     = rhs.uvDimensions;
            }
            return *this;
        }

        bool             hasNormals;
        bool             hasPositions;
        bool             hasTangents;
        UInt32           numUVChannels;
        UInt32           numColorChannels;
        UVDimensionStore uvDimensions;
    };

    typedef UInt32 MaterialIndex;
    typedef std::map<MaterialIndex, MeshInfo> MeshInfoMap;
    typedef SFUnrecHashKeyToFieldContainerMapPtr SFImageMapType;

    typedef std::multimap<std::string, TextureDesc*> MapTexturesT;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

private:
    std::string     _directory;
    std::string     _filename;
    MaterialMap     _materialMap;
    ImageMap        _imageMap;
    SFImageMapType  _sfImageMap;;
    MeshInfoMap     _meshInfoMap;
    AssimpOptions   _options;
    std::string     _importer;
    bool            _hasORMTexture;
    MapTexturesT    _mapCheckTextures;
};

OSG_END_NAMESPACE

#include "OSGAssimpMaterialProcessor.inl"

#endif // _OSGASSIMPMATERIALPROCESSOR_H_
