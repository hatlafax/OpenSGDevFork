/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGASSIMPSCENEFILETYPE_H_
#define _OSGASSIMPSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include <set>
#include <stack>
#include <vector>
#include <boost/optional/optional.hpp>
#include <boost/filesystem/fstream.hpp>

#include "OSGContribTechniquesDef.h"

#include "OSGBaseTypes.h"
#include "OSGSceneFileType.h"
#include "OSGImage.h"
#include "OSGTextureDesc.h"
#include "OSGAssimpOptions.h"

#ifdef OSG_WITH_ASSIMP
struct aiNode;
struct aiMaterial;
struct aiMesh;
struct aiScene;
struct aiTexture;

namespace Assimp
{
    class Exporter;
}

#endif

OSG_BEGIN_NAMESPACE

/*! \brief AssimpSceneFileType
    \ingroup GrpFileIOAssimp
    \ingroup GrpLibOSGFileIO
 */

class Geometry;
class Material;
class Image;

class DescMaterial;
class SimpleTexturedMaterial;
class SimpleMaterial;
class ChunkMaterial;

namespace Details
{
    struct MaterialParameters;
    struct TextureParameters;
}

class OSG_CONTRIBTECHNIQUES_DLLMAPPING AssimpSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static AssimpSceneFileType &the      (bool   override = false, 
                                          UInt32 overridePriority = 20);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AssimpSceneFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual const Char8 *getName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual 
    NodeTransitPtr read(      std::istream &is,
                        const Char8        *fileNameOrExtension,
                              Resolver      resolver  = NULL   ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual bool write(Node         * const  node, 
                       std::ostream         &os,
                       Char8          const *fileNameOrExtension) const;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                  Information                                 */
    /*! \{                                                                 */

    bool        supportExtension  (const Char8 *fileNameOrExtension, UInt32 flags) const;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::vector<std::string>                VecFormatIdsT;
    typedef std::map<std::string, VecFormatIdsT>    MapExtToFormatIdsT;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static const Char8                 *_suffixA[];     // Read
    static const Char8                 *_suffixB[];     // Write

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    AssimpSceneFileType(const Char8  *suffixArray[],
                             UInt16  suffixByteCount,
                             bool    override,
                             UInt32  overridePriority,
                             UInt32  flags);

    AssimpSceneFileType(const AssimpSceneFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    typedef SceneFileType Inherited;

    /* prohibit default function (move to 'public' if needed) */
    void operator =(const AssimpSceneFileType &source);

    typedef boost::optional<std::string>        OptStringT;
    typedef boost::optional<std::size_t>        OptIndexT;
    typedef boost::optional<BoostPath>          OptPathT;

    OptStringT  getExtension        (const Char8 *fileNameOrExtension) const;

    typedef std::vector<std::size_t>            VecIndicesT;
    typedef std::vector<Matrix>                 VectorMatricesT;
    typedef std::stack<Material*>               StackMaterialsT;

    typedef std::map<Geometry*,  VecIndicesT>   MapGeometriesT;
    typedef std::map<Material*,  std::size_t>   MapMaterialsT;
    typedef std::map<std::string, UInt32>       MapMaterialNamesT;

    typedef std::vector<TextureDescUnrecPtr>    TextureDescStore;

    typedef TextureDesc::SwizzleIndicesT        SwizzleIndicesT;

    typedef Image::PixelFormat                  PixelFormat;

#ifdef OSG_WITH_ASSIMP

    typedef std::vector<aiMesh*>                VecAiMeshesT;
    typedef std::vector<aiMaterial*>            VecAiMaterialsT;
    typedef std::vector<aiTexture*>             VecTexturesT;
    typedef boost::filesystem::ofstream         OutStreamT;
    typedef std::unique_ptr<OutStreamT>         OutStreamPtr;

    struct SceneWriteData
    {
        SceneWriteData(
            const AssimpOptions& options, 
            const std::string&   exporter, 
            const std::string&   formatId,
            const BoostPath&     destination,
            const BoostPath&     file) 
        : options               (options    )
        , exporter              (exporter   )
        , formatId              (formatId   )
        , destination           (destination)
        , file                  (file       )
        , vecMatrices           (           )
        , stackMaterials        (           )
        , stackOverrideMaterials(           )
        , mapGeometries         (           )
        , mapMaterials          (           )
        , mapMaterialNames      (           )
        , vecAiMeshes           (           )
        , vecAiMaterials        (           )
        , vecAiTextures         (           )
        , vecTextureDescs       (           )
        , vecCorrectFactor      (           )
        , setPrimaryMaterials   (           )
        , spMtyStream           (           )
        {}

        const AssimpOptions&    options;

        std::string             exporter;
        std::string             formatId;

        BoostPath               destination;
        BoostPath               file;

        VectorMatricesT         vecMatrices;
        StackMaterialsT         stackMaterials;
        StackMaterialsT         stackOverrideMaterials;

        MapGeometriesT          mapGeometries;
        MapMaterialsT           mapMaterials;
        MapMaterialNamesT       mapMaterialNames;

        VecAiMeshesT            vecAiMeshes;
        VecAiMaterialsT         vecAiMaterials;
        VecTexturesT            vecAiTextures;

        TextureDescStore        vecTextureDescs;
        std::vector<bool>       vecCorrectFactor;

        std::set<UInt32>        setPrimaryMaterials;

        OutStreamPtr            spMtyStream;
    };

    std::unique_ptr<aiScene> getAssimpScene (
                                Node* const          node, 
                                const AssimpOptions& options, 
                                const std::string&   exporter,
                                const std::string&   formatId,
                                const BoostPath&     destination,
                                const BoostPath&     file
                            ) const;

    void        handleAssociatedFiles               (SceneWriteData& data) const;
    void        handleAssociatedFilesOBJ            (SceneWriteData& data) const;

    aiNode*     handleNode                          (SceneWriteData& data, Node* const node, aiNode* parent) const;
    void        handleGeometry                      (SceneWriteData& data, Node* const node, aiNode* ai_node) const;
    VecIndicesT handleMeshes                        (SceneWriteData& data, Geometry* const geom) const;
    OptIndexT   handleMaterial                      (SceneWriteData& data) const;

    void        handleDescMaterial                  (SceneWriteData& data, const DescMaterial*           mat, aiMaterial* ai_mat) const;

    void        prepareDescMaterialTex              (SceneWriteData& data, const DescMaterial*           mat) const;
    void        mergeDescMaterialTex                (SceneWriteData& data, const DescMaterial*           mat) const;
    void        mergeDescMaterialTexPbrRoughMetal   (SceneWriteData& data, const DescMaterial*           mat) const;
    void        mergeDescMaterialTexPbrSpecularGloss(SceneWriteData& data, const DescMaterial*           mat) const;

    bool        validDescMaterialTexType            (SceneWriteData& data, const DescMaterial*           mat, UInt32 textureType) const;
    bool        validDescMaterialTexTypeOBJ         (SceneWriteData& data, const DescMaterial*           mat, UInt32 textureType) const;
    bool        validDescMaterialTexTypeGLTF        (SceneWriteData& data, const DescMaterial*           mat, UInt32 textureType) const;

    void        handleDescMaterialTex               (SceneWriteData& data, const DescMaterial*           mat, aiMaterial* ai_mat) const;

    void        handleSimpleTexturedMaterial        (SceneWriteData& data, const SimpleTexturedMaterial* mat, aiMaterial* ai_mat) const;
    void        handleSimpleMaterial                (SceneWriteData& data, const SimpleMaterial*         mat, aiMaterial* ai_mat) const;
    void        handleChunkMaterial                 (SceneWriteData& data, const ChunkMaterial*          mat, aiMaterial* ai_mat) const;

    void        prepareNonTexMaterialParamsGLTF2    (SceneWriteData& data, Details::MaterialParameters& params) const;
    void        prepareNonTexMaterialParamsOBJ      (SceneWriteData& data, Details::MaterialParameters& params) const;

    void        handleNonTexMaterialParamsCommon    (SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const;
    void        handleNonTexMaterialParamsGLTF2     (SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const;
    void        handleNonTexMaterialParamsOBJ       (SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const;

    void        finishNonTexMaterialParamsCommon    (SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const;
    void        finishNonTexMaterialParamsGLTF2     (SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const;
    void        finishNonTexMaterialParamsOBJ       (SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const;

    void        handleTexMaterialTextureParams      (SceneWriteData& data, Details::TextureParameters&  params, aiMaterial* ai_mat) const;
    void        handleTexMaterialTextureParamsGLTF2 (SceneWriteData& data, Details::TextureParameters&  params, aiMaterial* ai_mat) const;
    void        handleTexMaterialTextureParamsOBJ   (SceneWriteData& data, Details::TextureParameters&  params, aiMaterial* ai_mat) const;

    OptIndexT   getPrimaryMaterialData              (SceneWriteData& data, unsigned int materialIndex, Matrix& trafo) const;
    void        setPrimaryMaterialData              (SceneWriteData& data, unsigned int materialIndex, bool clear_trafo) const;

    OptIndexT   getExportFormatDescriptionIndex (const Char8 *fileNameOrExtension, const Assimp::Exporter& exporter, const AssimpOptions& options) const;

    TextureDescTransitPtr createTextureDesc       (UInt32 type, const TextureDesc* texDesc) const;
    TextureDescTransitPtr findTextureDesc         (UInt32 type, const TextureDescStore& store) const;
    void                  removeTextureDesc       (const TextureDesc* texDesc, TextureDescStore& store) const;
    bool                  bMergeableTextures      (const TextureDesc* texDesc1, const TextureDesc* texDesc2) const;
    bool                  bMergeableTextures      (const TextureDesc* texDesc1, const TextureDesc* texDesc2, const TextureDesc* texDesc3) const;


#endif // OSG_WITH_ASSIMP

    OptPathT        copyOrWriteTexture  (const BoostPath& file, const BoostPath& dst, const BoostPath& folder, Image* image) const;
    OptPathT        writeTexture        (                       const BoostPath& dst, const BoostPath& folder, Image* image) const;

    Int32           mergeImageDataType      (Image* image, Int32 other_data_type) const;
    
    bool            supportedMergeFormat    (Image* image) const;
    bool            supportedMergeFormats   (Image* image1, Image* image2) const;
    bool            supportedMergeFormats   (Image* image1, Image* image2, Image* image3) const;

    PixelFormat     reformatImagePixelFormat(Image* image) const;

    ImageTransitPtr createMergeableImages   (UInt32 pixelFormat, ImageUnrecPtr& img1) const;
    ImageTransitPtr createMergeableImages   (UInt32 pixelFormat, ImageUnrecPtr& img1, ImageUnrecPtr& img2) const;
    ImageTransitPtr createMergeableImages   (UInt32 pixelFormat, ImageUnrecPtr& img1, ImageUnrecPtr& img2, ImageUnrecPtr& img3) const;

    ImageTransitPtr mergeOcclRoughMetal     (const TextureDesc* texDescOccl, const TextureDesc* texDescRough, const TextureDesc* texDescMetal) const;
    ImageTransitPtr mergeOcclRoughMetal     (const TextureDesc* texDescOccl, const TextureDesc* texDescOther) const;

    ImageTransitPtr mergeRoughMetal         (const TextureDesc* texDescRough, const TextureDesc* texDescMetal) const;
    ImageTransitPtr mergeRoughMetal         (const TextureDesc* texDesc) const;

    ImageTransitPtr mergeSpecularGloss      (const TextureDesc* texDescSpecular, const TextureDesc* texDescOther) const;
    ImageTransitPtr mergeSpecularGloss      (const TextureDesc* texDescGloss) const;


    ImageTransitPtr resolveSwizzle          (ImageUnrecPtr image, const TextureDesc* texDesc) const;
    ImageTransitPtr resolveInvert           (ImageUnrecPtr image, const TextureDesc* texDesc) const;

    ImageTransitPtr swizzleChannels         (Image* image, SwizzleIndicesT swizzle) const;
    ImageTransitPtr invertColorChannels     (Image* image, bool isSRGB) const;

    std::string     getWriteFormatIdentifier(const std::string& suffix) const;
};

typedef AssimpSceneFileType* AssimpSceneFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGASSIMPSCENEFILETYPE_H_

