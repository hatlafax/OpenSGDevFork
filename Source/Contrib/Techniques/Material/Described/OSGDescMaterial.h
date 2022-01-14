/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#ifndef _OSGDESCMATERIAL_H_
#define _OSGDESCMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGContribTechniquesDef.h"

#include "OSGImage.h"
#include "OSGBlendChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGTwoSidedLightingChunk.h"
//#include "OSGDepthChunk.h"
//#include "OSGLogicOpChunk.h"
#include "OSGShadeModelChunk.h"
//#include "OSGLineChunk.h"
#include "OSGShaderProgramVariableChunk.h"
#include "OSGUniformBufferObjStd140Chunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureTransformChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGTextureDesc.h"

#include "OSGCapabilitiesDesc.h"

#include "OSGDescMaterialBase.h"

OSG_BEGIN_NAMESPACE

class MaterialDesc;
class TextureDesc;

/*! \brief DescMaterial class. See \ref
           PageContribTechniquesDescMaterial for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING DescMaterial : public DescMaterialBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DescMaterialBase Inherited;
    typedef DescMaterial     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      State                                   */
    /*! \{                                                                 */

    virtual void rebuildState (void);
    virtual bool isTransparent(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Info                                   */
    /*! \{                                                                 */
    
    UInt32              getNumUVTextures        () const;
    bool                getHasAmbientOcclusion  () const;
    bool                getHasPostProcessColor  () const;
    bool                getHasImageBasedLight   () const;
    bool                getNeedTangentSpace     () const;

    UInt32              getMaxNumClipPlanes     () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Shader Code                               */
    /*! \{                                                                 */

    typedef std::pair<std::string, std::string> PairShadersT;

    std::string         getVertexProgramSnippet         () const;
    PairShadersT        getFragmentProgramSnippet       () const;

    const Char8*        getFragEnvUniformBlockName      () const;
    const Char8*        getFragUniformBlockName         () const;
    const Char8*        getVertUniformBlockName         () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 File IO support                              */
    /*! \{                                                                 */

    typedef std::vector<TextureDesc*>               TextureDescStore;

    const TextureDescStore&     getActiveTextureDescs       () const;
    const TextureDescStore&     getActiveTextureDescsEnv    () const;

    static TextureDesc*         searchNthTextureDesc        (
                                        const TextureDescStore& textureDescs, 
                                        UInt32 type, 
                                        UInt32 N);

    static TextureDesc*         searchNthTextureDesc        (
                                        const TextureDescStore& textureDescs, 
                                        std::vector<UInt32> types, 
                                        UInt32 N);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Custom Field Set                             */
    /*! \{                                                                 */

    SFUnrecEnvironmentDescPtr*  editSFEnvironmentDesc(void);
    SFUnrecMaterialDescPtr*     editSFMaterialDesc   (void);

    void                        setEnvironmentDesc(EnvironmentDesc* const value);
    void                        setMaterialDesc   (MaterialDesc*    const value);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    enum VertexOptVariants
    {
        NoTextures,
        FullImplementation,
        OptOnlyTransform,
        OptOnlyChannels,
        OptOnlyChannel0
    };

    //
    // Flags that gives answere if a particular texture is supported in the evaluated material
    // description. Only thoses textures generate a fragment shader uniform TexData entry.
    // See function DescriptionInfo::initialize() for details.
    //
    enum TexMapDetails
    {
        // Values Syncronized with TextureDesc::TextureType enumeration
        AlbedoTextures                       = 1 << TextureDesc::ALBEDO_TEXTURE,
        SpecularTextures                     = 1 << TextureDesc::SPECULAR_TEXTURE,
        EmissiveTextures                     = 1 << TextureDesc::EMISSIVE_TEXTURE,
        ShininessTextures                    = 1 << TextureDesc::SHININESS_TEXTURE,
        OpacityTextures                      = 1 << TextureDesc::OPACITY_TEXTURE,
        NormalsTextures                      = 1 << TextureDesc::NORMALS_TEXTURE,
        HeightTextures                       = 1 << TextureDesc::HEIGHT_TEXTURE,
        DisplacementTextures                 = 1 << TextureDesc::DISPLACEMENT_TEXTURE,
        ReflectionTextures                   = 1 << TextureDesc::REFLECTION_TEXTURE,
        RefractionTextures                   = 1 << TextureDesc::REFRACTION_TEXTURE,
        AnisotropyUTextures                  = 1 << TextureDesc::ANISOTROPY_U_TEXTURE,
        AnisotropyVTextures                  = 1 << TextureDesc::ANISOTROPY_V_TEXTURE,
        AnisotropyUVTextures                 = 1 << TextureDesc::ANISOTROPY_UV_TEXTURE,
        AmbientOcclusionTextures             = 1 << TextureDesc::AMBIENT_OCCLUSION_TEXTURE,
        RoughTextures                        = 1 << TextureDesc::ROUGH_TEXTURE,
        MetalTextures                        = 1 << TextureDesc::METAL_TEXTURE,
        RoughMetalTextures                   = 1 << TextureDesc::ROUGH_METAL_TEXTURE,
        OcclRoughMetalTextures               = 1 << TextureDesc::OCCL_ROUGH_METAL_TEXTURE,
        IrradianceTextures                   = 1 << TextureDesc::IRRADIANCE_TEXTURE,
        PreFilterTextures                    = 1 << TextureDesc::PRE_FILTER_TEXTURE,
        BrdfLutTextures                      = 1 << TextureDesc::BRDF_LUT_TEXTURE,
        StandardMaterialTextures             = 1 << TextureDesc::STANDARD_MATERIAL_TEXTURE,
        //SheenTextures                        = 1 << TextureDesc::SHEEN_TEXTURE,
        //ClearcoatTextures                    = 1 << TextureDesc::CLEARCOAT_TEXTURE,
        //TransmissionTextures                 = 1 << TextureDesc::TRANSMISSION_TEXTURE,
    };

    //
    // Flags that gives answere if a non texture fragment shader uniform block data entry
    // is present.
    //
    enum EnvBlockMemberDetails
    {
        ExposureBlockMember           = 1 << 1,
        KeyValueBlockMember           = 1 << 2,
        ApertureFNumberBlockMember    = 1 << 3,
        ShutterSpeedBlockMember       = 1 << 4,
        ISOBlockMember                = 1 << 5,
        WhiteLevelBlockMember         = 1 << 6,
        DragoBiasBlockMember          = 1 << 7,
        SaturationBlockMember         = 1 << 8,
        ContrastBlockMember           = 1 << 9,
        GammaBlockMember              = 1 << 10,
        FilterColorBlockMember        = 1 << 11,
        GlobalAmbientIntBlockMember   = 1 << 12,
        ClipPlaneBlockMember          = 1 << 13,

        AllEnvBlockMemberDetails      = 0xFFFFFFFF
    };

    enum MatBlockMemberDetails
    {
        SpecularStrengthBlockMember   = 1 << 1,
        EmissiveStrengthBlockMember   = 1 << 2,
        OpacityCutOffBlockMember      = 1 << 3,
        ReflectivityBlockMember       = 1 << 4,
        ReflectanceBlockMember        = 1 << 5,
        BumpScalingBlockMember        = 1 << 6,
        TransparentBlockMember        = 1 << 7,
        ReflectiveBlockMember         = 1 << 8,
        GoochCoolBlockMember          = 1 << 9,
        GoochWarmBlockMember          = 1 << 10,
        GoochMixinBlockMember         = 1 << 11,
        GoochCoolMixinBlockMember     = 1 << 12,
        GoochWarmMixinBlockMember     = 1 << 13,
        ToonLevelsBlockMember         = 1 << 14,

        AllMatBlockMemberDetails         = 0xFFFFFFFF
    };

    //
    // The fragments shader finally, works on an instance of a
    // Material structure. Each member of this structure does
    // have an entry in the following enumeration. The flags
    // are initialized DescriptionInfo::getMatMemDetails()
    // function and evaluated in the shader code generation
    // process.
    // See function getFragmentProgramMaterialStruct() for
    // details.
    //
    enum MaterialMemberDetails
    {
        TexCoordsMaterialMember              = 1 << 1,
        AlbedoMaterialMember                 = 1 << 2,
        DiffuseMaterialMember                = 1 << 3,
        SpecularMaterialMember               = 1 << 4,
        EmissiveMaterialMember               = 1 << 5,
        ShininessMaterialMember              = 1 << 6,
        OpacityMaterialMember                = 1 << 7,
        SpecularStrengthMaterialMember       = 1 << 8,
        EmissiveStrengthMaterialMember       = 1 << 9,
        NormalMaterialMember                 = 1 << 10,
        TangentMaterialMember                = 1 << 11,
        BitangentMaterialMember              = 1 << 12,
        ReflectionMaterialMember             = 1 << 13,
        RefractionMaterialMember             = 1 << 14,
        ReflectiveMaterialMember             = 1 << 15,
        AnisotropyUMaterialMember            = 1 << 16,
        AnisotropyVMaterialMember            = 1 << 17,
        RoughnessMaterialMember              = 1 << 18,
        MetalnessMaterialMember              = 1 << 19,
        IrradianceMaterialMember             = 1 << 20,
        PreFilterColorMaterialMember         = 1 << 21,
        BrdfMaterialMember                   = 1 << 22,
        ToonScaleMaterialMember              = 1 << 24,
        AmbientOcclusionMaterialMember       = 1 << 25,
        //SheenMaterialMember                  = 1 << 26,
        //ClearcoatMaterialMember              = 1 << 27,
        //TransmissionMaterialMember           = 1 << 28,

        AllMaterialMemberDetails             = 0xFFFFFFFF
    };

    typedef std::vector<TextureObjChunkUnrecPtr>        TextureObjChunkStore;
    typedef std::vector<TextureTransformChunkUnrecPtr>  TextureTransformChunkStore;
    typedef std::vector<TextureEnvChunkUnrecPtr>        TextureEnvChunkStore;
    typedef std::vector<bool>                           BooleanStore;
    typedef std::vector<UInt8>                          TextureCountStore;
    typedef std::vector< Int32>                         TextureUnitStore;

    struct DescriptionInfo
    {
        DescriptionInfo();
        DescriptionInfo(const DescriptionInfo& rhs);

        void                initialize              (MaterialDesc* materialDesc, EnvironmentDesc* environmentDesc, Int32 texUnitOffset, CapabilitiesDesc* capabilities);
        void                initTextureDescs        (CapabilitiesDesc* capabilities);
        UInt32              getTexMapDetails        (const TextureDescStore& textureDescs) const;
        UInt32              getBlockMemDetailsEnv   () const;
        UInt32              getBlockMemDetails      () const;
        UInt32              getMatMemDetails        () const;
        VertexOptVariants   getVertOptVariant       () const;
        UInt32              getShadingModel         () const;

        bool                hasSpecularGlossinessTexture    () const;
        bool                hasSpecularGlossinessWorkflow   () const;
        bool                hasMetalnessRoughnessWorkflow   () const;

        bool                hasAmbientOcclusion     () const;

        bool                hasTexMapDetail         (TexMapDetails         val) const;
        bool                hasMatBlockMember       (MatBlockMemberDetails val) const;
        bool                hasEnvBlockMember       (EnvBlockMemberDetails val) const;
        bool                hasMaterialMember       (MaterialMemberDetails val) const;

        bool                anyTexMapDetail         (TexMapDetails         val) const;
        bool                anyMatBlockMember       (MatBlockMemberDetails val) const;
        bool                anyEnvBlockMember       (EnvBlockMemberDetails val) const;
        bool                anyMaterialMember       (MaterialMemberDetails val) const;

        bool                needTangentSpace        () const;

        bool              invalid;
        EnvironmentDesc*  envDesc;
        MaterialDesc*     matDesc;
        TextureDescStore  textureDescs;
        TextureDescStore  textureDescsEnv;
        UInt32            texMapDetails;
        UInt32            blockMemDetailsEnv;
        UInt32            blockMemDetails;
        UInt32            matMemDetails;
        UInt32            numUVTextures;
        UInt32            numEnvTextures;
        UInt32            numEquiTextures;
        UInt32            numCubeTextures;
        UInt32            numUVChannels;
        Int32             maxTexUnit;
        TextureCountStore textureOccurrences;
        BooleanStore      textureSuppressed;
        BooleanStore      textureEnvMapIsCubeMap;
        BooleanStore      textureSupportFixedPipeline;
        bool              hasEnvironmentMaps;
        bool              hasEquirectangMaps;
        bool              hasCubeMaps;
        bool              hasStackTexData;
        bool              hasSingleTexData;
        Int32             idxFstUVTexture;
        Int32             idxFstEquiTexture;
        Int32             idxFstCubeTexture;
        VertexOptVariants vertOptVariant;
    };

  protected:
    // Variables should all be in DescMaterialBase.

    mutable DescriptionInfo             _info;

    static TextureCountStore            _textureMaxCounts;
    static BooleanStore                 _textureSupported;
    static BooleanStore                 _textureIsEnvMap;
    static BooleanStore                 _hasFragBlockColorEntry;

    UniformBufferObjStd140ChunkUnrecPtr _fragEnvironmentChunk;

    UniformBufferObjStd140ChunkUnrecPtr _vertMaterialChunk;
    UniformBufferObjStd140ChunkUnrecPtr _fragMaterialChunk;

    BlendChunkUnrecPtr                  _blendChunk;
    PolygonChunkUnrecPtr                _polygonChunk;
    TwoSidedLightingChunkUnrecPtr       _twoSidedLightChunk;
    //DepthChunkUnrecPtr                  _depthChunk;
    //LogicOpChunkUnrecPtr                _logicOpChunk;
    ShadeModelChunkUnrecPtr             _shadeModelChunk;
    //LineChunkUnrecPtr                   _lineChunk;

    ShaderProgramVariableChunkUnrecPtr  _shaderProgramVariableChunk;

    MaterialChunkUnrecPtr               _materialChunk;

    TextureObjChunkStore                _textureObjChunks;
    TextureObjChunkStore                _textureObjChunksEnv;
    TextureEnvChunkStore                _textureEnvChunks;
    TextureTransformChunkStore          _textureTransformChunks;

    BooleanStore                        _isSRGBTextures;
    TextureUnitStore                    _textureUnits;

    bool                                _isTransparent;
    bool                                _bUpdateMaterial;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DescMaterial(void);
    DescMaterial(const DescMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DescMaterial(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Material Desc                              */
    /*! \{                                                                 */

    void addMaterialDescObserver        ();
    void removeMaterialDescObserver     ();

    void addEnvironmentDescObserver     ();
    void removeEnvironmentDescObserver  ();

    void changedMaterialDesc            (
                                            FieldContainer*     pFC, 
                                            ConstFieldMaskArg   whichField, 
                                            UInt32              origin
                                        );

    void changedEnvironmentDesc         (
                                            FieldContainer*     pFC, 
                                            ConstFieldMaskArg   whichField, 
                                            UInt32              origin
                                        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      State                                   */
    /*! \{                                                                 */

    void                prepareLocalChunks          (MaterialDesc* matDesc);
    void                prepareLocalChunks          (TextureDesc*  texDesc);
    void                prepareLocalChunksEnv       (TextureDesc*  texDesc);

    //
    // The clip plane information
    //
    void                   addClipPlaneUniformVariables();
    void                updateClipPlaneUniformVariables(EnvironmentDesc* envDesc);

    //
    // The environment information
    //
    void                   addEnvShaderUniformVariables();
    void                updateEnvShaderUniformVariables(EnvironmentDesc* envDesc);

    std::size_t         calcEnvFragBufferSize          (EnvironmentDesc*    envDesc) const;
    std::vector<UInt8>  createEnvFragBuffer            (EnvironmentDesc*    envDesc) const;
    void                fillEnvFragBuffer              (EnvironmentDesc*    envDesc,
                                                        std::vector<UInt8>& buffer ) const;

    //
    // The primary material information
    //
    void                addShaderUniformVariables   ();
    void                updateShaderUniformVariables(MaterialDesc* matDesc);

    std::size_t         calcVertBufferSize          () const;
    std::vector<UInt8>  createVertBuffer            (MaterialDesc* matDesc) const;
    std::vector<UInt8>  createFragBuffer            (MaterialDesc* matDesc) const;

    typedef std::pair<TextureDesc*, UInt32>         TexDescPair;
    typedef std::vector<TexDescPair>                TexDescPairStore;
    typedef std::map<UInt32, TexDescPairStore>      TexDescPairStoreMap;
    typedef std::vector<ImageUnrecPtr>              ImageStore;

    void                initTexDescPairStoreMap     (TexDescPairStoreMap& mapTexDecs) const;

    std::size_t         calcFragBufferSize          (MaterialDesc*              matDesc,
                                                     const TexDescPairStoreMap& mapTexDecs) const;

    void                fillFragBuffer              (MaterialDesc*              matDesc,
                                                     std::vector<UInt8>&        buffer, 
                                                     const TexDescPairStoreMap& mapTexDecs) const;

    void                calcFragBufferTexDataSize   (std::size_t&               ao,
                                                     std::size_t&               bo,
                                                     UInt32                     texType,
                                                     const TexDescPairStoreMap& mapTexDecs) const;

    void                fillFragBufferTexData       (std::vector<UInt8>&        buffer, 
                                                     std::size_t&               ao,
                                                     std::size_t&               bo,
                                                     const Color3f&             baseColor,
                                                     UInt32                     texType,
                                                     const TexDescPairStoreMap& mapTexDecs) const;

    void                updateState                 (MaterialDesc* matDesc, EnvironmentDesc* envDesc);

    virtual void        resolveLinks                (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      sRGB                                    */
    /*! \{                                                                 */

    Color3f sRGBToLinear        (const Color3f& c) const;
    Real32  sRGBToLinear        (      Real32   x) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */

    Int32   getTexUnitOffsetRT  () const;
    
    bool    getImages           (const TextureDesc*         texDesc,
                                 ImageStore& images                   ) const;

    bool    setTexData          (const TextureDesc*         texDesc,
                                 Image*                     image,
                                 bool                       isSRGBTexture,
                                 TextureObjChunk*           objChunk  ) const;

    Color3f getBaseColor        (MaterialDesc* matDesc, UInt32 texType) const;
    bool    hasFragBlockEntry   (UInt32 texType, UInt32 texMapDetails ) const;

    bool    hasSpecularGlossinessTexture    () const;
    bool    hasSpecularGlossinessWorkflow   () const;
    bool    hasMetalnessRoughnessWorkflow   () const;

    bool    hasAmbientOcclusion             () const;

    bool    hasTexMapDetail     (TexMapDetails         val) const;
    bool    hasMatBlockMember   (MatBlockMemberDetails val) const;
    bool    hasEnvBlockMember   (EnvBlockMemberDetails val) const;
    bool    hasMaterialMember   (MaterialMemberDetails val) const;

    bool    anyTexMapDetail     (TexMapDetails         val) const;
    bool    anyMatBlockMember   (MatBlockMemberDetails val) const;
    bool    anyEnvBlockMember   (EnvBlockMemberDetails val) const;
    bool    anyMaterialMember   (MaterialMemberDetails val) const;

    bool    needTangentSpace    () const;


    enum TexTypeEvalInfo
    {
        DISCARD = 0,
        IS_COLOR_DATA,
        IS_SINGLE_DATA,
        IS_STACK_DATA,
        IS_ENV_DATA
    };

    TexTypeEvalInfo     evalFragtProgTexType    (UInt32 texType) const;

    bool    isFallbackFixedFunction         () const;
    bool    isFallbackShader2               () const;

    bool    hasSwitchSupport                () const;
    bool    hasBitOpsSupport                () const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            Modern Shader Detail                              */
    /*! \{                                                                 */

    void getVertexProgramSnippet                        (std::stringstream& ost) const;
    void getVertexProgramDetailNoTextures               (std::stringstream& ost) const;
    void getVertexProgramDetailFullImpl                 (std::stringstream& ost, UInt32 numTextures, UInt32 numChannels) const;
    void getVertexProgramDetailOnlyTransform            (std::stringstream& ost, UInt32 numTextures) const;
    void getVertexProgramDetailOnlyChannels             (std::stringstream& ost, UInt32 numTextures, UInt32 numChannels) const;
    void getVertexProgramDetailOnlyChannel0             (std::stringstream& ost, UInt32 numTextures) const;

    void getFragmentProgramSnippet                      (std::stringstream& ostDecl, std::stringstream& ostImpl) const;
    void getFragmentProgramPreamble                     (std::stringstream& ost) const;
    void getFragmentProgramUVInput                      (std::stringstream& ost) const;
    void getFragmentProgramEnvUniformBlock              (std::stringstream& ost) const;
    void getFragmentProgramBindTextures                 (std::stringstream& ost) const;
    void getFragmentProgramTextureAccessUtils           (std::stringstream& ost) const;
    void getFragmentProgramTextureAccessOpt             (std::stringstream& ost) const;
    void getFragmentProgramTextureAccess                (std::stringstream& ost) const;
    void getFragmentProgramTextureData                  (std::stringstream& ost) const;
    void getFragmentProgramMatUniformBlock              (std::stringstream& ost) const;
    void getFragmentProgramMatBlockEntry                (std::stringstream& ost, const std::string& spc, UInt32 texType, const char* name) const;
    void getFragmentProgramMaterialStruct               (std::stringstream& ost) const;
    void getFragmentProgramTextureConstants             (std::stringstream& ost) const;
    void getFragmentProgramTextureEvaluation            (std::stringstream& ost) const;
    void getFragmentProgramParallaxRemapTexureCoords    (std::stringstream& ost, const char* var, const char* channel) const;
    void getFragmentProgramMaterialEvaluation           (std::stringstream& ost) const;

    void getFragmentProgramMaterialAlbedo               (std::stringstream& ost) const;
    void getFragmentProgramMaterialSpecular             (std::stringstream& ost) const;
    void getFragmentProgramMaterialEmissive             (std::stringstream& ost) const;
    void getFragmentProgramMaterialShininess            (std::stringstream& ost) const;
    void getFragmentProgramMaterialOpacity              (std::stringstream& ost) const;
    void getFragmentProgramMaterialNormal               (std::stringstream& ost) const;
    void getFragmentProgramMaterialHeight               (std::stringstream& ost) const;
    void getFragmentProgramMaterialDisplacement         (std::stringstream& ost) const;
    void getFragmentProgramMaterialReflection           (std::stringstream& ost) const;
    void getFragmentProgramMaterialRefraction           (std::stringstream& ost) const;
    void getFragmentProgramMaterialAnisotropyU          (std::stringstream& ost) const;
    void getFragmentProgramMaterialAnisotropyV          (std::stringstream& ost) const;
    void getFragmentProgramMaterialAnisotropyUV         (std::stringstream& ost) const;
    void getFragmentProgramMaterialAmbientOccl          (std::stringstream& ost) const;
    void getFragmentProgramMaterialRoughness            (std::stringstream& ost) const;
    void getFragmentProgramMaterialMetalness            (std::stringstream& ost) const;
    void getFragmentProgramMaterialRoughMetal           (std::stringstream& ost) const;
    void getFragmentProgramMaterialOcclRoughMetal       (std::stringstream& ost) const;
    void getFragmentProgramMaterialRoughDisp            (std::stringstream& ost) const;
    void getFragmentProgramMaterialIrradiance           (std::stringstream& ost) const;
    void getFragmentProgramMaterialPreFilterColor       (std::stringstream& ost) const;
    void getFragmentProgramMaterialBrdf                 (std::stringstream& ost) const;
    void getFragmentProgramMaterialStandardMaterial     (std::stringstream& ost) const;
    //void getFragmentProgramMaterialSheen                (std::stringstream& ost) const;
    //void getFragmentProgramMaterialClearCoat            (std::stringstream& ost) const;
    //void getFragmentProgramMaterialTransmission         (std::stringstream& ost) const;

    void getFragmentProgramMaterialF0                   (std::stringstream& ost) const;

    void getFragmentProgramMaterialInitialization       (std::stringstream& ost) const;
    void getFragmentProgramMaterialShadingModel         (std::stringstream& ost) const;

    void getFragmentProgramMaterialModelIndirectShading (std::stringstream& ost) const;

    void getFragmentProgramMaterialModelNo              (std::stringstream& ost) const;
    void getFragmentProgramMaterialModelGouraud         (std::stringstream& ost) const;
    void getFragmentProgramMaterialModelPhong           (std::stringstream& ost) const;
    void getFragmentProgramMaterialModelBlinn           (std::stringstream& ost) const;
    void getFragmentProgramMaterialModelCookTorrance    (std::stringstream& ost) const;
    void getFragmentProgramMaterialModelOrenNayar       (std::stringstream& ost) const;
    void getFragmentProgramMaterialModelToon            (std::stringstream& ost) const;
    void getFragmentProgramMaterialModelGooch           (std::stringstream& ost) const;

    void getFragmentProgramImageBasedLightEmpty         (std::stringstream& ost) const;
    void getFragmentProgramPostProcessing               (std::stringstream& ost) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    const UInt32 cuiMaxTextureStackSize = 4;   // the max texture number of the same kind

    friend class FieldContainer;
    friend class DescMaterialBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DescMaterial &source);
};

typedef DescMaterial *DescMaterialP;

OSG_END_NAMESPACE

#include "OSGDescMaterialBase.inl"
#include "OSGDescMaterial.inl"

#endif /* _OSGDESCMATERIAL_H_ */
