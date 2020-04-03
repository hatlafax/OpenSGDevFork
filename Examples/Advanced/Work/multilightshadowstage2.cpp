// OpenSG Tutorial Example: MultiLightShadowStage1
//
// This example primarily shows the usage of the MultiLightShadowStage core
// that allows to render shadows with various shadow mapping techniques.
// Additionally it shows the usage of the MultiLighGroup, and of the HDR2Stage
// for tonemapping. The example optionally, uses the AntTweakbar for tweaking
// most of the parameters involved. For that, the example is rather verbose
// but hopefulle structures enough to be able to grasp the basic concepts.
//
// The example consists essentially of the 'Example' class which is once
// instantiated in the global 'main' function. The constructor of 'Example'
// calls function 'initialize' which setup the complete scene.
//

#include <cstddef>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/random.hpp>

//#undef OSG_WITH_ANTTWEAKBAR
#ifdef OSG_WITH_ANTTWEAKBAR
#include <AntTweakBar.h>
#endif

#ifdef OSG_BUILD_ACTIVE
#include <OSGConfig.h>
#include <OSGBaseFunctions.h>
#include <OSGCallbackAlgorithm.h>
#include <OSGCallbackAlgorithmForeground.h>
#include <OSGChunkMaterial.h>
#include <OSGDescMaterial.h>
#include <OSGDescMaterialManager.h>
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGGroup.h>
#include <OSGHashKeyToFieldContainerMap.h>
#include <OSGHDR2Stage.h>
#include <OSGImageFileHandler.h>
#include <OSGLiSPSMTechnique.h>
#include <OSGMaterialChunkOverrideGroup.h>
#include <OSGMaterialDesc.h>
#include <OSGMatrixUtility.h>
#include <OSGMultiLight.h>
#include <OSGMultiLightGroup.h>
#include <OSGMultiLightShadowParameter.h>
#include <OSGMultiLightShadowParameterAdvanced.h>
#include <OSGMultiLightShadowStage.h>
#include <OSGMultiPropertySSBOChunk.h>
#include <OSGMultiPropertyUBOChunk.h>
#include <OSGPerspectiveCamera.h>
#include <OSGPolygonChunk.h>
#include <OSGSSAOStage.h>
#include <OSGShaderProgram.h>
#include <OSGShaderProgramChunk.h>
#include <OSGShaderProgramVariableChunk.h>
#include <OSGSimpleGeometry.h>
#include <OSGSimpleLightGeometry.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSkyBackground.h>
#include <OSGTextureDesc.h>
#include <OSGSolidBackground.h>
#include <OSGTextureObjChunk.h>
#include <OSGTransform.h>
#include <OSGTwoSidedLightingChunk.h>
#else
// Headers
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGCallbackAlgorithm.h>
#include <OpenSG/OSGCallbackAlgorithmForeground.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGDescMaterial.h>
#include <OpenSG/OSGDescMaterialManager.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGHashKeyToFieldContainerMap.h>
#include <OpenSG/OSGHDR2Stage.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGLiSPSMTechnique.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGMaterialDesc.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGMultiLight.h>
#include <OpenSG/OSGMultiLightGroup.h>
#include <OpenSG/OSGMultiLightShadowParameter.h>
#include <OpenSG/OSGMultiLightShadowParameterAdvanced.h>
#include <OpenSG/OSGMultiLightShadowStage.h>
#include <OpenSG/OSGMultiPropertySSBOChunk.h>
#include <OpenSG/OSGMultiPropertyUBOChunk.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGSSAOStage.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleLightGeometry.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSkyBackground.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGTextureDesc.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGTwoSidedLightingChunk.h>
#endif

const OSG::MultiLightShadowStage::Mode ceShadowMode = OSG::MultiLightShadowStage::SIMPLE_SHADOW_MAP;
//OSG::MultiLightShadowStage::NO_SHADOW_MAP
//OSG::MultiLightShadowStage::SIMPLE_SHADOW_MAP
//OSG::MultiLightShadowStage::ADVANCED_SHADOW_MAP
//OSG::MultiLightShadowStage::SIMPLE_TEST_SHADOW_MAP

const OSG::UInt32 window_width     = 1920; // 1600;  //1000;
const OSG::UInt32 window_height    = 1080; // 1200;  //800;

const OSG::UInt32 max_num_lights   = 4;

const OSG::UInt32 geom_start_index = 3;                     // A number of objects are treated special
const OSG::UInt32 num_geometries   = geom_start_index + 24; // We show that number of objects


const OSG::Real32 circle_radius    = 12.f;
const OSG::Real32 floor_size       = 200.f;
const OSG::Real32 center_box_size  = 1.5f;       // if used: see

const bool mixed_geometry          = false; // spheres and cubes
const bool use_center_box          = true;  // center box instead of torus and cylinder
const bool one_non_lit_geometry    = false; // test of geometry that does not interact with specific light
const bool excl_geom_from_shadows  = false; // test of geometry that does not produce shadows at all
const bool excl_floor_from_shadows = true;  // floor might not participate
const bool create_geom_for_lights  = false; 
//
// shader storage block binding points
//
const OSG::UInt32 light_binding_point        = 2;
const OSG::UInt32 shadow_data_binding_point  = 3;

//
// texture units
//
const OSG:: Int32 cube_array_texture_unit    = 6;
const OSG:: Int32 array_texture_unit         = 7;

//
// uniform block binding points
//
const OSG::UInt32 geom_binding_point         = 1;
const OSG::UInt32 shadow_param_binding_point = 2;
const OSG::UInt32 distribution_binding_point = 3;

const unsigned int redisplay_time       =  static_cast<unsigned int>(1000.0 / 120.0);
const int          timer_id             =  4711;

/*----- create_and_exe_dot_file ---------------------------------------------*/

//#define CREATE_AND_EXE_DOT_FILE

#include <boost/filesystem.hpp>

#ifdef OSG_BUILD_ACTIVE
#include <OSGDotFileGeneratorGraphOp.h>
#else
#include <OpenSG/OSGDotFileGeneratorGraphOp.h>
#endif

const char* graphviz_dot_executale = "d:/_xxx/Utils/Graphviz/bin/dot.exe";
const char* graphviz_output_file   = "d:/out.dot";

void create_and_exe_dot_file(OSG::Node* node)
{
#ifdef CREATE_AND_EXE_DOT_FILE
    using namespace OSG;

    namespace fs = ::boost::filesystem;

    fs::path dot_file(graphviz_output_file); dot_file.replace_extension(".dot");
    fs::path png_file(graphviz_output_file); png_file.replace_extension(".png");

    if (fs::exists(dot_file))
        fs::remove(dot_file);

    if (fs::exists(png_file))
        fs::remove(png_file);

    DotFileGeneratorGraphOpRefPtr go = DotFileGeneratorGraphOp::create();

    std::string param("filename=");
    go->setParams(param + dot_file.string());
    go->setParams("max_node_children=10 no_name_attachments=true no_ranks=true no_addresses=false");

    go->traverse(node);

    go = NULL;

    if (!fs::exists(dot_file))
        return;

    fs::path exe_file(graphviz_dot_executale);
    if (!fs::exists(exe_file))
        return;

    std::string cmd = exe_file.string();
    cmd += " -T png " + dot_file.string() + " -o " + png_file.string();

    system(cmd.c_str()) ;
#endif // CREATE_AND_EXE_DOT_FILE
}

/*---- HDRShaderData ------------------------------------------------------*/

struct HDRShaderData
{
    HDRShaderData();
    HDRShaderData(const HDRShaderData& rhs);

    HDRShaderData&  operator=   (const HDRShaderData& rhs);

    static HDRShaderData create_min_shader_data();
    static HDRShaderData create_max_shader_data();

    float bloomThreshold;
    float bloomMagnitude;
    int   toneMapTechnique;
    float exposure;
    float keyValue;
    int   autoExposure;
    float whiteLevel;
    float shoulderStrength;
    float linearStrength;
    float linearAngle;
    float toeStrength;
    float toeNumerator;
    float toeDenominator;
    float linearWhite;
    float lumSaturation;
    float bias;
    float tau;
    int   nTaps;
    float sigma;
    bool  useLinChromInterp;
};

/*---- Example ------------------------------------------------------------*/

class Example
{
public:
    static void displayCB   ()                                      { if (_pExample) _pExample->display(); }
    static void reshapeCB   (int w, int h)                          { if (_pExample) _pExample->reshape(w, h); }
    static void mouseCB     (int button, int state, int x, int y)   { if (_pExample) _pExample->mouse(button, state, x, y); }
    static void motionCB    (int x, int y)                          { if (_pExample) _pExample->motion(x, y); }
    static void keyboardCB  (unsigned char k, int x, int y)         { if (_pExample) _pExample->keyboard(k, x, y); }
    static void specialCB   (int k, int x, int y)                   { if (_pExample) _pExample->special(k, x, y); }
    static void timerCB     (int id)                                { if (_pExample) _pExample->timer(id); }

public:
            Example(int argc, char *argv[]);
           ~Example();

private:
    void                        initialize                          (int argc, char *argv[]);
    int                         setupGLUT                           (int *argc, char *argv[]);

    void                        display                             ();
    void                        reshape                             (int w, int h);
    void                        mouse                               (int button, int state, int x, int y);
    void                        motion                              (int x, int y);
    void                        keyboard                            (unsigned char k, int x, int y);
    void                        special                             (int key, int x, int y);
    void                        timer                               (int id);
    void                        tweakbar                            (OSG::DrawEnv* drawEnv);

    void                        initBackground                      ();
    void                        setupBackground                     ();

    void                        createMaterialManager               ();
    void                        initMaterialManager                 ();

    void                        initShader                          (OSG::ShaderProgram* shader);
    void                        updateShader                        (OSG::ShaderProgram* shader);

    void                        createMaterials                     ();

    void                        setupMaterialFloor                  ();
    void                        setupMaterialLights                 ();
    void                        setupMaterial0                      ();
    void                        setupMaterial1                      ();
    void                        setupMaterial2                      ();
    void                        setupMaterial3                      ();
    void                        setupMaterial4                      ();
    void                        setupMaterial5                      ();
    void                        setupMaterial6                      ();
    void                        setupMaterial7                      ();
    void                        setupMaterial8                      ();
    void                        setupMaterial9                      ();
    void                        setupMaterial10                     ();
    void                        setupMaterial11                     ();
    void                        setupMaterial12                     ();
    void                        setupMaterial13                     ();
    void                        setupMaterial14                     ();
    void                        setupMaterial15                     ();
    void                        setupMaterial16                     ();
    void                        setupMaterial17                     ();

    void                        setupRootScene                      ();
    void                        setupScene                          ();

    // SSAO stage
    void                        create_ssao_stage                    ();
    void                        setup_ssao_stage                     ();
    void                        enable_ssao_stage                    ();
    void                        disable_ssao_stage                   ();

    // HDR stage
    void                        create_hdr_stage                    ();
    void                        setup_hdr_stage                     ();
    void                        enable_hdr_stage                    ();
    void                        disable_hdr_stage                   ();

    void                        create_light_geometry               (bool frustum, const OSG::MultiLight& light, OSG::UInt32 light_idx, bool enable_geometry);
    void                        update_light_geometry               (const OSG::MultiLight& light);
    void                        create_lights                       (OSG::UInt32 requiredShadowFeatures);

    // Helper function
    void                        setLightFramePosition               (OSG::UInt32 idx, const OSG::Pnt3f& position);
    OSG::Pnt3f                  getLightFramePosition               (OSG::UInt32 idx) const;

    void                        MeasureFPS                          (bool to_title);
    float                       GetFps                              () const;

#ifdef OSG_WITH_ANTTWEAKBAR
private:
    void    setupTweakBar   ();

public:
    void    ResetParameters             ();
    void    SetSampleNumber             (int   value);                  int                 GetSampleNumber             () const;
    void    SetClearColor               (const OSG::Color3f& value);    const OSG::Color3f& GetClearColor               () const;
    void    SetForceBgnd                (bool  value);                  bool                GetForceBgnd                () const;
    void    SetAjustLuminance           (bool  value);                  bool                GetAjustLuminance           () const;
    void    SetSkyBgndIndex             (int   value);                  int                 GetSkyBgndIndex             () const;
    void    SetPerformBloom             (bool  value);                  bool                GetPerformBloom             () const;
    void    SetBloomBackground          (bool  value);                  bool                GetBloomBackground          () const;
    void    SetCarryDepth               (bool  value);                  bool                GetCarryDepth               () const;
    void    SetUseHDR                   (bool  value);                  bool                GetUseHDR                   () const;
    void    SetResultIndex              (int   value);                  int                 GetResultIndex              () const;
    void    SetRenderEmissive           (bool  value);                  bool                GetRenderEmissive           () const;
    void    SetRenderAmbient            (bool  value);                  bool                GetRenderAmbient            () const;
    void    SetRenderDiffuse            (bool  value);                  bool                GetRenderDiffuse            () const;
    void    SetRenderSpecular           (bool  value);                  bool                GetRenderSpecular           () const;
    void    SetAccurateGamma            (bool  value);                  bool                GetAccurateGamma            () const;
    void    SetGamma                    (bool  value);                  bool                GetGamma                    () const;
    void    SetUseITURBT709             (bool  value);                  bool                GetUseITURBT709             () const;
    void    SetMipmapLevel              (int   value);                  int                 GetMipmapLevel              () const;
    void    SetBloomThreshold           (float value);                  float               GetBloomThreshold           () const;
    void    SetBloomMagnitude           (float value);                  float               GetBloomMagnitude           () const;
    void    SetToneMapTechnique         (int   value);                  int                 GetToneMapTechnique         () const;
    void    SetExposure                 (float value);                  float               GetExposure                 () const;
    void    SetKeyValue                 (float value);                  float               GetKeyValue                 () const;
    void    SetAutoExposure             (int   value);                  int                 GetAutoExposure             () const;
    void    SetWhiteLevel               (float value);                  float               GetWhiteLevel               () const;
    void    SetShoulderStrength         (float value);                  float               GetShoulderStrength         () const;
    void    SetLinearStrength           (float value);                  float               GetLinearStrength           () const;
    void    SetLinearAngle              (float value);                  float               GetLinearAngle              () const;
    void    SetToeStrength              (float value);                  float               GetToeStrength              () const;
    void    SetToeNumerator             (float value);                  float               GetToeNumerator             () const;
    void    SetToeDenominator           (float value);                  float               GetToeDenominator           () const;
    void    SetLinearWhite              (float value);                  float               GetLinearWhite              () const;
    void    SetLumSaturation            (float value);                  float               GetLumSaturation            () const;
    void    SetBias                     (float value);                  float               GetBias                     () const;
    void    SetTau                      (float value);                  float               GetTau                      () const;
    void    SetNTaps                    (int   value);                  int                 GetNTaps                    () const;
    void    SetSigma                    (float value);                  float               GetSigma                    () const;
    void    SetUseLinChromInterp        (bool  value);                  bool                GetUseLinChromInterp        () const;
    void    SetCurrentLight             (OSG::UInt32 value);            OSG::UInt32         GetCurrentLight             () const;
    void    SetLightPosition            (const OSG::Pnt3f& value);      OSG::Pnt3f          GetLightPosition            () const;
    void    SetLightDirection           (const OSG::Vec3f& value);      OSG::Vec3f          GetLightDirection           () const;
    void    SetLightAmbient             (const OSG::Color3f& value);    OSG::Color3f        GetLightAmbient             () const;
    void    SetLightDiffuse             (const OSG::Color3f& value);    OSG::Color3f        GetLightDiffuse             () const;
    void    SetLightSpecular            (const OSG::Color3f& value);    OSG::Color3f        GetLightSpecular            () const;
    void    SetLightAttenuation         (const OSG::Vec3f& value);      OSG::Vec3f          GetLightAttenuation         () const;
    void    SetLightSpotlightAng        (OSG::Real32 value);            OSG::Real32         GetLightSpotlightAng        () const;
    void    SetLightSpotExponent        (OSG::Real32 value);            OSG::Real32         GetLightSpotExponent        () const;
    void    SetLightType                (int value);                    int                 GetLightType                () const;
    void    SetLightEnabled             (bool value);                   bool                GetLightEnabled             () const;
    void    SetLightShadow              (bool value);                   bool                GetLightShadow              () const;
    void    SetLightShadowBias          (OSG::Real32 value);            OSG::Real32         GetLightShadowBias          () const;
    void    SetLightShadowInt           (OSG::Real32 value);            OSG::Real32         GetLightShadowInt           () const;
    void    SetShadowOn                 (bool value);                   bool                GetShadowOn                 () const;
    void    SetShadowMode               (OSG::Int32 value);             OSG::Int32          GetShadowMode               () const;
    void    SetRenderSplitting          (bool  value);                  bool                GetRenderSplitting          () const;
    void    SetShadowBias               (OSG::Real32 value);            OSG::Real32         GetShadowBias               () const;
    void    SetShadowFactor             (OSG::Real32 value);            OSG::Real32         GetShadowFactor             () const;
    void    SetShadowCullFace           (bool value);                   bool                GetShadowCullFace           () const;
    void    SetShadowMapSize            (OSG::UInt32 value);            OSG::UInt32         GetShadowMapSize            () const;
    void    SetShadowTweakVol           (OSG::Real32 value);            OSG::Real32         GetShadowTweakVol           () const;
    void    SetShadowFilterMode         (OSG::Int32 value);             OSG::Int32          GetShadowFilterMode         () const;
    void    SetShadowFilterSize         (OSG::Int32 value);             OSG::Int32          GetShadowFilterSize         () const;
    void    SetShadowSearchSize         (OSG::Int32 value);             OSG::Int32          GetShadowSearchSize         () const;
    void    SetShadowFilterRadius       (OSG::Real32 value);            OSG::Real32         GetShadowFilterRadius       () const;
    void    SetShadowRandomRotate       (bool value);                   bool                GetShadowRandomRotate       () const;
    void    SetShadowUseBlockerSearch   (bool value);                   bool                GetShadowUseBlockerSearch   () const;
    void    SetShadowUsePCSS            (bool value);                   bool                GetShadowUsePCSS            () const;
    void    SetShadowFocusing           (bool value);                   bool                GetShadowFocusing           () const;
    void    SetShadowUseLiSP            (bool value);                   bool                GetShadowUseLiSP            () const;
    void    SetShadowLiSPMode           (OSG::Int32 value);             OSG::Int32          GetShadowLiSPMode           () const;
    void    SetShadowNbrOfSplits        (OSG::Int32 value);             OSG::Int32          GetShadowNbrOfSplits        () const;
    void    SetShadowUseGeomShader      (bool value);                   bool                GetShadowUseGeomShader      () const;
    void    SetShadowReduceSwimming     (bool value);                   bool                GetShadowReduceSwimming     () const;
    void    SetShadowLightSpaceAlign    (bool value);                   bool                GetShadowLightSpaceAlign    () const;
    void    SetShadowUseMinDepth        (bool value);                   bool                GetShadowUseMinDepth        () const;
    void    SetShadowUseBestResolSel    (bool value);                   bool                GetShadowUseBestResolSel    () const;
    void    SetShadowWarpParameter      (OSG::Real32 value);            OSG::Real32         GetShadowWarpParameter      () const;
    void    SetShadowSplitParameter     (OSG::Real32 value);            OSG::Real32         GetShadowSplitParameter     () const;
    void    SetShadowZNear              (OSG::Real32 value);            OSG::Real32         GetShadowZNear              () const;
    void    SetShadowPseudoNear         (OSG::Real32 value);            OSG::Real32         GetShadowPseudoNear         () const;
    void    SetShadowPseudoFar          (OSG::Real32 value);            OSG::Real32         GetShadowPseudoFar          () const;
    void    SetShadowUseHwPCF           (bool value);                   bool                GetShadowUseHwPCF           () const;
    void    SetShadowArbTest            (bool value);                   bool                GetShadowArbTest            () const;

    void    HandleShadowParamConstraints() const;
#endif

private:
    static Example*                         _pExample;  // Hack

    OSG::SimpleSceneManagerRefPtr           _mgr;

    OSG::DescMaterialManagerRefPtr          _materialManager;
    OSG::HashKeyToFieldContainerMapRefPtr   _imageMap;

    OSG::ChunkMaterialRefPtr                _floorMaterial;
    std::vector<OSG::ChunkMaterialRefPtr>   _vecMaterials;
    std::vector<OSG::ChunkMaterialRefPtr>   _vecMaterialsLights;
    std::vector<std::size_t>                _vecMaterialIdx;

    OSG::NodeRefPtr                         _hdrNode;
    OSG::HDR2StageRefPtr                    _hdrStage;
    OSG::GroupRefPtr                        _hdrGroup;

    OSG::NodeRefPtr                         _ssaoNode;
    OSG::SSAOStageRefPtr                    _ssaoStage;
    OSG::GroupRefPtr                        _ssaoGroup;

    OSG::NodeRefPtr                         _lightNode;
    OSG::MultiLightGroupRefPtr              _multiLightGroup;

    std::vector<OSG::TransformRefPtr>       _lightBeaconsTansforms;
    std::vector<OSG::UInt32>                _lightIndices;

    OSG::NodeRefPtr                         _shadowNode;
    OSG::MultiLightShadowStageRefPtr        _shadowStage;

    OSG::NodeRefPtr                         _sceneNode;
    OSG::NodeRefPtr                         _gazeSceneNode;

    OSG::NodeRefPtr                         _floorNode;
    OSG::TransformRefPtr                    _geom_trans[num_geometries];
    
    HDRShaderData                           _hdrShaderData;
    HDRShaderData                           _hdrShaderDataDefault;
    HDRShaderData                           _hdrShaderDataMin;
    HDRShaderData                           _hdrShaderDataMax;

    bool                                    _gamma;
    bool                                    _accurate_gamma;
    bool                                    _use_ITU_R_BT_709;
    int                                     _mipmap_level;
    int                                     _num_samples;

    OSG::Color3f                            _clear_color;
    bool                                    _force_bgnd;
    bool                                    _adjust_luminance;

    std::size_t                             _skyBgnd_index;
    bool                                    _backgroundIsSRGB;
    std::vector<std::string>                _skyFiles;

    int                                     _result_index;

    bool                                    _render_ambient;
    bool                                    _render_diffuse;
    bool                                    _render_specular;
    bool                                    _render_emissive;

    bool                                    _render_splitting;

    bool                                    _useHDRStage;
    bool                                    _useSSAOStage;
    bool                                    _useFlatShading;

    bool                                    _perform_bloom;
    bool                                    _bloom_background;
    bool                                    _carry_depth;

    bool                                    _pause;

    float                                   _fps;
    int                                     _fps_num_frames;
    OSG::Time                               _fps_time_point;

    typedef boost::mt19937 RNGType;
    typedef boost::uniform_int <OSG::UInt32> DistributionType;
    typedef boost::variate_generator<RNGType, DistributionType> GeneratorType;

    RNGType                                 _rng;
    DistributionType                        _material_dist;
    GeneratorType                           _material_idx_die;

#ifdef OSG_WITH_ANTTWEAKBAR
    OSG::UInt32                             _current_light_index;
    TwBar*                                  _tweakbar; 
#endif
};

/*---- Example ------------------------------------------------------------*/

Example* Example::_pExample = NULL;

Example::Example(int argc, char *argv[])
: _mgr(NULL)
, _materialManager(NULL)
, _imageMap(NULL)
, _floorMaterial(NULL)
, _vecMaterials()
, _vecMaterialsLights()
, _vecMaterialIdx()
, _hdrNode(NULL)
, _hdrStage(NULL)
, _hdrGroup(NULL)
, _ssaoNode(NULL)
, _ssaoStage(NULL)
, _ssaoGroup(NULL)
, _lightNode(NULL)
, _multiLightGroup(NULL)
, _lightBeaconsTansforms()
, _lightIndices()
, _shadowNode(NULL)
, _shadowStage(NULL)
, _sceneNode(NULL)
, _gazeSceneNode(NULL)
, _floorNode(NULL)
, _hdrShaderData()
, _hdrShaderDataDefault()
, _hdrShaderDataMin(HDRShaderData::create_min_shader_data())
, _hdrShaderDataMax(HDRShaderData::create_max_shader_data())
, _gamma(true)
, _accurate_gamma(true)
, _use_ITU_R_BT_709(true)
, _mipmap_level(-1)
, _num_samples(8)
, _clear_color(0.0f, 0.0f, 0.4f)
, _force_bgnd(true)
, _adjust_luminance(false)
, _skyBgnd_index(0)
, _backgroundIsSRGB(true)
, _skyFiles()
, _result_index(OSG::HDR2Stage::COMPOSITE_TEXTURE)
, _render_ambient(true)
, _render_diffuse(true)
, _render_specular(true)
, _render_emissive(false)
, _render_splitting(false)
, _useHDRStage(true)
, _useSSAOStage(true)
, _useFlatShading(false)
, _perform_bloom(false)
, _bloom_background(true)
, _carry_depth(true)
, _pause(true)
, _fps(0.f)
, _fps_num_frames(0)
, _fps_time_point(OSG::getSystemTime())
, _rng(time(0))
, _material_dist(0,0)
, _material_idx_die(_rng, _material_dist)
#ifdef OSG_WITH_ANTTWEAKBAR
, _current_light_index(0)
, _tweakbar(NULL)
#endif
{
    for (std::size_t i = 0; i < num_geometries; ++i)
    {
        _geom_trans[i] = NULL;
    }

    initialize(argc, argv);
}

Example::~Example()
{
    _pExample = NULL;
}

void Example::initialize(int argc, char *argv[])
{
    _pExample = this;

    //
    // This might be necessary depending on the
    // used platform to ensure that the corresponding
    // libraries get loaded.
    //
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    OSG::preloadSharedObject("OSGContribPLY");

    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

#ifdef OSG_WITH_ANTTWEAKBAR
    TwInit(TW_OPENGL_CORE, NULL);
#endif

    // the connection between GLUT and OpenSG
    OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->init();

    // create a callback for AntTweakBar drawing
    OSG::RenderFunctor functor = boost::bind(&Example::tweakbar, this, _1);

    OSG::CallbackAlgorithmRefPtr cbAlgorithm = OSG::CallbackAlgorithm::create();
    cbAlgorithm->setCallback(functor, "");

    // create a callback foreground for the AntTweackBar drawing callback
    OSG::CallbackAlgorithmForegroundRefPtr cbForeground = OSG::CallbackAlgorithmForeground::create();
    cbForeground->setCallbackAlgorithm(cbAlgorithm);


    // create the SimpleSceneManager helper
    _mgr = OSG::SimpleSceneManager::create();
    _mgr->setWindow(gwin);

    _mgr->addForeground(cbForeground);

    initBackground();

    setupRootScene();

    OSG::PerspectiveCameraRefPtr perspective_camera = OSG::PerspectiveCamera::create();
    if (perspective_camera)
    {
        _mgr->setCamera(perspective_camera);

        perspective_camera->setFov(OSG::osgDegree2Rad(45.f));
        perspective_camera->setFovMode(OSG::PerspectiveCamera::VerticalFoV);
        perspective_camera->setNear(0.1f);
        perspective_camera->setFar(1000.f);
        perspective_camera->setAspect(1.f);

        OSG::commitChanges();

        OSG::Vec3f min, max;
        _hdrNode->updateVolume();
        _sceneNode->getVolume().getBounds(min, max);

        OSG::Matrix rot1, rot2, trans;
        rot1.setRotate(OSG::Quaternion(OSG::Vec3f(1.f, 0.f, 0.f), OSG::osgDegree2Rad( 25.f)));
        rot2.setRotate(OSG::Quaternion(OSG::Vec3f(0.f, 1.f, 0.f), OSG::osgDegree2Rad(-40.f)));
        trans.setTranslate(0.f, 0.f, -15.f);

        rot1.mult(rot2);
        rot1.mult(trans);

        OSG::Vec3f up(0,1,0);
        OSG::Pnt3f at(0,0,0);
        OSG::Pnt3f from;        rot1.mult(at, from);

        _mgr->getNavigator()->set(from, at, up);
        _mgr->getNavigator()->setMotionFactor(0.5f);
    }

    setupBackground();

    create_and_exe_dot_file(_mgr->getRoot());

#ifdef OSG_WITH_ANTTWEAKBAR
    setupTweakBar();
#endif
}

void Example::create_light_geometry(bool frustum, const OSG::MultiLight& light, OSG::UInt32 light_idx, bool enable_geometry)
{
    if (!light.getBeacon()) return;

    if (!light.getEnabled())
        light.getBeacon()->setTravMask(0);

    //
    // The first material is reserved for the floor. The following materials are reserved for the lights.
    //
    OSG::ChunkMaterialRefPtr geomState = _vecMaterialsLights[light_idx];

    OSG::Real32 R = 0.f;

    if (frustum)
        R = 10.f; //light.getRangeCutOff();
    else
        R = 0.4f;
    
    switch (light.getType())
    {
        case OSG::MultiLight::POINT_LIGHT:
        {
            OSG::GeometryRefPtr  geometry = OSG::makeSphereGeo(3, R);
            OSG::NodeRefPtr      node     = OSG::makeNodeFor(geometry);

            if (!enable_geometry)
                node->setTravMask(0);

            light.getBeacon()->addChild(node);
        }
        break;

        case OSG::MultiLight::DIRECTIONAL_LIGHT:
        {
        }
        break;

        case OSG::MultiLight::SPOT_LIGHT:
        {
            OSG::Real32 h = R;

            OSG::GeometryRefPtr geometry = OSG::makeSpotGeo(h, OSG::osgDegree2Rad(light.getSpotlightAngle()), 24, 24);
            geometry->setMaterial(geomState);

            OSG::TransformRefPtr coneTrans = OSG::Transform::create();

            OSG::Matrix rotMat;
            OSG::MatrixRotateTowards(rotMat, OSG::Vec3f(0.f, 1.f, 0.f), light.getDirection());
            coneTrans->setMatrix(rotMat);

            OSG::NodeRefPtr coneTransNode  = OSG::makeNodeFor(coneTrans);
            OSG::NodeRefPtr coneNode       = OSG::makeNodeFor(geometry);

            if (!enable_geometry)
                coneTransNode->setTravMask(0);

            light.getBeacon()->addChild(coneTransNode);
            coneTransNode->addChild(coneNode);
        }
        break;

        case OSG::MultiLight::CINEMA_LIGHT:
        {
            OSG::Real32 h = R;

            OSG::GeometryRefPtr geometry = OSG::makeCinemaGeo(
                                                light.getOuterSuperEllipsesWidth(),
                                                light.getOuterSuperEllipsesHeight(),
                                                light.getSuperEllipsesRoundness(),
                                                OSG::osgDegree2Rad(light.getSuperEllipsesTwist()),
                                                h, 48, 48);
            geometry->setMaterial(geomState);

            OSG::Matrix matLSFromWS;

            OSG::Matrix matLightPos;
            matLightPos.setTranslate(light.getPosition());

            OSG::Matrix matLightDir;
            OSG::Quaternion rotLightDir(OSG::Vec3f(0.f, 0.f, 1.f), -light.getDirection());
            matLightDir.setRotate(rotLightDir);

            matLSFromWS.mult  (matLightPos);
            matLSFromWS.mult  (matLightDir);

            OSG::Matrix matRot;
            matRot.setRotate(OSG::Quaternion(OSG::Vec3f(1,0,0), -0.5*OSG::Pi));

            matLSFromWS.mult(matRot);

            OSG::TransformRefPtr coneTrans = OSG::Transform::create();
            coneTrans->setMatrix(matLSFromWS);

            OSG::NodeRefPtr coneTransNode  = OSG::makeNodeFor(coneTrans);
            OSG::NodeRefPtr coneNode       = OSG::makeNodeFor(geometry);

            if (!enable_geometry)
                coneTransNode->setTravMask(0);

            light.getBeacon()->addChild(coneTransNode);
            coneTransNode->addChild(coneNode);
        }
        break;

        default:
            break;
    }
}

void Example::update_light_geometry(const OSG::MultiLight& light)
{
    if (!light.getBeacon()) return;

    switch (light.getType())
    {
        case OSG::MultiLight::SPOT_LIGHT:
        {
            OSG::UInt32 N = light.getBeacon()->getNChildren();
            for (OSG::UInt32 i = 0; i < N; ++i)
            {
                OSG::Node* coneTransNode = light.getBeacon()->getChild(i);
                if (coneTransNode)
                {
                    OSG::Transform* coneTrans = dynamic_cast<OSG::Transform*>(coneTransNode->getCore());
                    if (coneTrans)
                    {
                        OSG::Matrix rotMat;
                        OSG::MatrixRotateTowards(rotMat, OSG::Vec3f(0.f, 1.f, 0.f), light.getDirection());
                        coneTrans->setMatrix(rotMat);
                    }
                }
            }
        }
        break;

        case OSG::MultiLight::CINEMA_LIGHT:
        {
            OSG::UInt32 N = light.getBeacon()->getNChildren();
            for (OSG::UInt32 i = 0; i < N; ++i)
            {
                OSG::Node* coneTransNode = light.getBeacon()->getChild(i);
                if (coneTransNode)
                {
                    OSG::Transform* coneTrans = dynamic_cast<OSG::Transform*>(coneTransNode->getCore());
                    if (coneTrans)
                    {
                        OSG::Matrix matLSFromWS;

                        OSG::Matrix matLightPos;
                        matLightPos.setTranslate(light.getPosition());

                        OSG::Matrix matLightDir;
                        OSG::Quaternion rotLightDir(OSG::Vec3f(0.f, 0.f, 1.f), -light.getDirection());
                        matLightDir.setRotate(rotLightDir);

                        matLSFromWS.mult  (matLightPos);
                        matLSFromWS.mult  (matLightDir);

                        OSG::Matrix matRot;
                        matRot.setRotate(OSG::Quaternion(OSG::Vec3f(1,0,0), -0.5*OSG::Pi));

                        matLSFromWS.mult(matRot);

                        coneTrans->setMatrix(matLSFromWS);
                    }
                }
            }
        }
        break;

        default:
            break;
    }
}

void Example::setupRootScene()
{
    // The hdr root node
    _hdrNode = OSG::Node::create();
    _hdrNode->setCore(OSG::Group::create());

    _ssaoNode = OSG::Node::create();
    _ssaoNode->setCore(OSG::Group::create());

    create_hdr_stage();
    create_ssao_stage();

    //
    // We create the shadow stage before the multi light group because
    // we have to use compatible light shader structure layout in the
    // shader program injected from the shadow stage and the shader program
    // defined in the application. Since the layout might be different for
    // different shadow techniques we must ask the shadow stage for the
    // layout details.
    //
    _shadowStage = OSG::MultiLightShadowStage::create();
    _shadowNode  = OSG::makeNodeFor(_shadowStage);

    //_shadowNode = OSG::Node::create();
    //_shadowNode->setCore(OSG::Group::create());

    //_shadowStage->setShadowMode(OSG::MultiLightShadowStage::NO_SHADOW_MAP);
    //_shadowStage->setShadowMode(OSG::MultiLightShadowStage::SIMPLE_SHADOW_MAP);
    //_shadowStage->setShadowMode(OSG::MultiLightShadowStage::ADVANCED_SHADOW_MAP);
    //_shadowStage->setShadowMode(OSG::MultiLightShadowStage::SIMPLE_TEST_SHADOW_MAP);

    _shadowStage->setShadowMode(ceShadowMode);

    //_shadowStage->setAutoExcludeTransparentNodes(false);

    //
    // The binding points and texture units for all buffers and textures can
    // separately be defined. This, however, might not be necessary, because
    // the shadow stage automatically determines these values counting from the
    // maximum allowed values down.
    //
    // Use texture units greater than 4 because otherwise OpenGL warnings
    // occure due to glEnable(target) with target either GL_TEXTURE_CUBE_MAP_ARRAY
    // or GL_TEXTURE_2D_ARRAY in TextureObjChunk line 1838. OpenSG does not use 
    // this glEnable call for texture units greater than 4. If no texture unit
    // is provided the texture units are initialized automaically (typically 30,31).
    //
    //_shadowStage->setSampler2DArrayTextureUnit(array_texture_unit);
    //_shadowStage->setSamplerCubeArrayTextureUnit(cube_array_texture_unit);

    //_shadowStage->setShadowDataBindingPnt(shadow_data_binding_point);
    //_shadowStage->setShadowParameterBindingPnt(shadow_param_binding_point);
    //_shadowStage->setDistributionBindingPnt(distribution_binding_point);

    _shadowStage->setShadowMapWidth (512);
    _shadowStage->setShadowMapHeight(512);

    //
    // The distribution sizes for blocker search and filtering can be specified.
    //
    //_shadowStage->setFilterDistributionSize(OSG::MultiLightShadowStage::PCF_BOX_8x8_POISSON_32);
    //_shadowStage->setSearchDistributionSize(OSG::MultiLightShadowStage::PCF_BOX_6x6_POISSON_25);


    OSG::UInt32 requiredShadowFeatures = _shadowStage->getRequiredMultiLightFeatures();

    createMaterialManager();

    create_lights(requiredShadowFeatures);

    setupScene();

    if (excl_floor_from_shadows)
        _shadowStage->editMFExcludeNodes()->push_back(_floorNode);  // floor should not generate a shadow!

    //
    // Because we exclude the floor the quality of the shadows increase substantial. However, if the
    // incident angle of the directional light is small enough with respect to the ground floor, the
    // belonging shadows get truncated. So we need a measure to moderate here. With the following
    // statement we push the far plane of the shadow volume further away and can so ease the problem.
    // However, this is a fundametal problem with shadow mapping and their is no perfect solution
    // and the end user must tweak between shadow map size, scene and enlargement parameter.
    //
    _shadowStage->setEnlargeShadowVolumeZ(2.f);

    _hdrNode     ->addChild(_ssaoNode);
    _ssaoNode    ->addChild(_lightNode);
    _lightNode   ->addChild(_shadowNode);
    _shadowNode  ->addChild(_sceneNode);

    OSG::commitChanges();
    
    _mgr->setRoot(_hdrNode);
}

void Example::setupScene()
{
    _sceneNode     = OSG::makeCoredNode<OSG::Group>();
    _gazeSceneNode = OSG::makeCoredNode<OSG::Group>();

    _sceneNode->addChild(_gazeSceneNode);

    OSG::GeometryRefPtr someGeo[num_geometries];

    for (std::size_t i = 0; i < num_geometries; ++i)
    {
        _geom_trans[i] = OSG::Transform::create();
        
        someGeo[i] = NULL;
    }

    OSG::UInt32 geo0_idx  = 0;
    OSG::UInt32 geo1_idx  = 1;
    OSG::UInt32 floor_idx = 2;

    if (use_center_box)
    {
        OSG::GeometryRefPtr centerGeo = OSG::makeBoxGeo(center_box_size, center_box_size, center_box_size, 1, 1, 1);
        OSG::NodeRefPtr     center    = OSG::Node::create();
        center->setCore(centerGeo);

        OSG::NodeRefPtr centerTransNode = OSG::Node::create();
        centerTransNode->setCore(_geom_trans[geo1_idx]);
        centerTransNode->addChild(center);

        OSG::TransformUnrecPtr centerMove   = OSG::Transform::create();
        OSG::Matrix m; m.setIdentity(); m.setTranslate(0.f, center_box_size, 0.f);
        centerMove->setMatrix(m);

        OSG::NodeRefPtr centerTransNodeMove = OSG::Node::create();
        centerTransNodeMove->setCore (centerMove);
        centerTransNodeMove->addChild(centerTransNode);

        _gazeSceneNode->addChild(centerTransNodeMove);

        someGeo[geo0_idx] = NULL;
        someGeo[geo1_idx] = centerGeo;
    }
    else
    {
        OSG::GeometryRefPtr   cylGeo = OSG::makeCylinderGeo( 1.4f, .3f, 24, true, true, true );
        OSG::GeometryRefPtr torusGeo = OSG::makeTorusGeo( .2f, 1, 24, 36 );

        OSG::NodeRefPtr   cyl = OSG::Node::create();
        OSG::NodeRefPtr torus = OSG::Node::create();

          cyl->setCore(  cylGeo);
        torus->setCore(torusGeo);

        OSG::NodeRefPtr   cylTransNode = OSG::Node::create();
        OSG::NodeRefPtr torusTransNode = OSG::Node::create();

          cylTransNode->setCore(_geom_trans[geo0_idx]);
        torusTransNode->setCore(_geom_trans[geo1_idx]);

          cylTransNode->addChild(  cyl);
        torusTransNode->addChild(torus);

        _gazeSceneNode->addChild(  cylTransNode);
        _gazeSceneNode->addChild(torusTransNode);

        someGeo[geo0_idx] =   cylGeo;
        someGeo[geo1_idx] = torusGeo;
    }

    OSG::GeometryRefPtr floorGeo  = OSG::makeBoxGeo(floor_size, 1.f, floor_size, 1, 1, 1);
                       _floorNode = OSG::Node::create();

    _floorNode->setCore(floorGeo);

    _geom_trans[floor_idx]->setMatrix(OSG::Matrix());

    OSG::NodeRefPtr floorTransNode = OSG::Node::create();
    floorTransNode->setCore(_geom_trans[floor_idx]);

    floorTransNode->addChild(_floorNode);
    _sceneNode->addChild(floorTransNode);

    someGeo[floor_idx] = floorGeo;

    for (std::size_t i = geom_start_index; i < num_geometries; ++i)
    {
        OSG::NodeRefPtr geomNode;

        if (!mixed_geometry || i % 2 == 0)
        {
            geomNode = OSG::Node::create();
            someGeo[i] = OSG::makeSphereGeo(3, 1.f);
        }
        else
        {
            geomNode = OSG::Node::create();
            someGeo[i] = OSG::makeBoxGeo(1.4f, 1.4f, 1.4f, 1, 1, 1);
        }

        geomNode->setCore(someGeo[i]);

        OSG::Real32 theta = (i-geom_start_index) * 2.f * OSG::Pi / (num_geometries - geom_start_index);

        OSG::Matrix m; m.setTranslate(OSG::Vec3f(circle_radius * OSG::osgCos(theta), 0.5f, circle_radius * OSG::osgSin(theta)));
        _geom_trans[i]->setMatrix(m);

        OSG::NodeRefPtr geomTransNode = OSG::Node::create();
        geomTransNode->setCore (_geom_trans[i]);
        geomTransNode->addChild(geomNode);

        _gazeSceneNode->addChild(geomTransNode);

        //
        // Test: One geometry should not cast a shadow
        //
        if (excl_geom_from_shadows && i == geom_start_index)
            _shadowStage->editMFExcludeNodes()->push_back(geomTransNode);
    }

    _vecMaterialIdx.clear();

    for (std::size_t i = 0; i < num_geometries; ++i)
    {
        if (someGeo[i] != NULL)
        {
            if (i == floor_idx)
            {
                someGeo[i]->setMaterial(_floorMaterial);
            }
            else
            {
                std::size_t mat_idx = _material_idx_die();

                _vecMaterialIdx.push_back(mat_idx);

                someGeo[i]->setMaterial(_vecMaterials[mat_idx]);
            }
        }
    }
}

int Example::setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(window_width, window_height);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshapeCB);
    glutDisplayFunc(displayCB);

    glutMouseFunc(mouseCB);
    glutMotionFunc(motionCB);
    glutPassiveMotionFunc(motionCB);
    glutKeyboardFunc(keyboardCB);
    glutSpecialFunc(specialCB);

#ifdef OSG_WITH_ANTTWEAKBAR
    TwGLUTModifiersFunc(glutGetModifiers);
#endif

    // call the redraw function whenever there's nothing else to do
    // glutIdleFunc(displayCB);

    glutTimerFunc(redisplay_time, timerCB, timer_id);


    return winid;
}

void Example::display()
{
    MeasureFPS(true);

    if (!_pause)
    {
        // create the matrix
        OSG::Matrix m;
        OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME );

        OSG::Matrix tr;
        OSG::Real32 y = 2.5f * OSG::osgAbs(OSG::osgSin(t / 2000.f));
        tr.setTranslate(0, y, 0);
    
        // set the transforms' matrices
        m.setTransform(OSG::Vec3f(0, 0, OSG::osgSin(t / 1000.f) * 1.5),
                       OSG::Quaternion( OSG::Vec3f (1, 0, 0), t / 500.f));

        m.multLeft(tr);
        _geom_trans[0]->setMatrix(m);
    
        m.setTransform(OSG::Vec3f(OSG::osgSin(t / 1000.f), 0, 0),
                       OSG::Quaternion( OSG::Vec3f (0, 0, 1), t / 1000.f));

        m.multLeft(tr);
        _geom_trans[1]->setMatrix(m);

        for (std::size_t i = geom_start_index; i < num_geometries; ++i)
        {
            OSG::Real32 theta = (i-geom_start_index) * 2.f * OSG::Pi / (num_geometries - geom_start_index);

            OSG::Real32 rad = circle_radius + 0.3 * circle_radius * OSG::osgSin(t / 2000.f);

            m.setIdentity();
            m.setTranslate(OSG::Vec3f(rad * OSG::osgCos(theta), y, rad * OSG::osgSin(theta)));
            _geom_trans[i]->setMatrix(m);
        }
    }

    OSG::commitChanges();
    
    _mgr->redraw();
}

void Example::reshape(int w, int h)
{
    _mgr->resize(w, h);

#ifdef OSG_WITH_ANTTWEAKBAR
    TwWindowSize(w, h);
#endif

    glutPostRedisplay();
}

//
// react to mouse button presses
//
void Example::mouse(int button, int state, int x, int y)
{
#ifdef OSG_WITH_ANTTWEAKBAR
    if(TwEventMouseButtonGLUT(button, state, x, y))
    {
        glutPostRedisplay();
        return;
    }
#endif

    if (state)
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

//
// react to mouse motions with pressed buttons
//
void Example::motion(int x, int y)
{
#ifdef OSG_WITH_ANTTWEAKBAR
    if(TwEventMouseMotionGLUT(x, y))
    {
        glutPostRedisplay();
        return;
    }
#endif

    _mgr->mouseMove(x, y);

    glutPostRedisplay();
}

//
// react to keys
//
void Example::keyboard(unsigned char k, int x, int y)
{
#ifdef OSG_WITH_ANTTWEAKBAR
    if(TwEventKeyboardGLUT(k, x, y))
    {
        glutPostRedisplay();
        return;
    }
#endif

    switch(k)
    {
        case 27:    
        {
            // clean up global variables
            _mgr = NULL;

            _imageMap = NULL;
            _materialManager = NULL;

            _floorMaterial = NULL;
            _vecMaterials.clear();
            _vecMaterialsLights.clear();

            for (std::size_t i = 0; i < num_geometries; ++i)
            {
                _geom_trans[i] = NULL;
            }

            _lightBeaconsTansforms.clear();
            _lightIndices.clear();

            _hdrNode                = NULL;
            _hdrStage               = NULL;
            _hdrGroup               = NULL;

            _ssaoNode               = NULL;
            _ssaoStage              = NULL;
            _ssaoGroup              = NULL;

            _lightNode              = NULL;
            _multiLightGroup        = NULL;
            _shadowNode             = NULL;
            _shadowStage            = NULL;
            _sceneNode              = NULL;
            _gazeSceneNode          = NULL;
            _floorNode              = NULL;

            OSG::osgExit();
            exit(0);
        }
        break;

        case 'm':
        {
            glutPostRedisplay();
        }
        break;

        case 's':
        {
            _mgr->setStatistics(!_mgr->getStatistics());
        }
        break;
    }
}

void Example::special(int key, int x, int y)
{
#ifdef OSG_WITH_ANTTWEAKBAR
    if(TwEventSpecialGLUT(key, x, y))
    {
        glutPostRedisplay();
        return;
    }
#endif
}

void Example::timer(int id)
{
    if (id == timer_id)
    {
        glutPostRedisplay();
        glutTimerFunc(redisplay_time, timerCB, timer_id);
    }
}

void Example::tweakbar(OSG::DrawEnv* drawEnv)
{
#ifdef OSG_WITH_ANTTWEAKBAR
    //
    // Save the current state
    //
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    //
    // execute the actual callback wrapped by this class
    //
    TwDraw();

    //
    // Restore the state
    //
    glPopAttrib();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
#endif
}

void Example::create_hdr_stage()
{
    if (_hdrNode)
    {
        _hdrStage = OSG::HDR2Stage::create();
        _hdrGroup = OSG::Group::create();

        setup_hdr_stage();

        _hdrNode->setCore(_hdrStage);
    }
}

void Example::setup_hdr_stage()
{
    if (_hdrStage)
    {
        _hdrStage->setApplyGamma                (_gamma);
        _hdrStage->setAccurateGamma             (_accurate_gamma);

        _hdrStage->setPerformBloom              (_perform_bloom);
        _hdrStage->setBloomBackground           (_bloom_background);

        _hdrStage->setForceBackground           (_force_bgnd);
        _hdrStage->setUse_ITU_R_BT_709          (_use_ITU_R_BT_709);
        _hdrStage->setMipmapLevel               (_mipmap_level);

        _hdrStage->setTarget                    (_result_index);
        _hdrStage->setCarryDepth                (_carry_depth);

        _hdrStage->setColorBufferInternalFormat (GL_RGBA16F);
        _hdrStage->setColorBufferPixelFormat    (GL_RGBA);
        _hdrStage->setColorBufferType           (GL_FLOAT);

        _hdrStage->setDepthBufferInternalFormat (GL_DEPTH24_STENCIL8);
        _hdrStage->setDepthBufferPixelFormat    (GL_DEPTH_STENCIL);
        _hdrStage->setDepthBufferType           (GL_UNSIGNED_INT_24_8);

        _hdrStage->setLumBufferInternalFormat   (GL_R32F);
        _hdrStage->setLumBufferPixelFormat      (GL_RED);
        _hdrStage->setLumBufferType             (GL_FLOAT);

        _hdrStage->setImageBufferInternalFormat (GL_RGB16F);
        _hdrStage->setImageBufferPixelFormat    (GL_RGB);
        _hdrStage->setImageBufferType           (GL_FLOAT);

        _hdrStage->setNumSamples                (_num_samples);

        _hdrStage->setBloomThreshold            (_hdrShaderData.bloomThreshold);
        _hdrStage->setBloomMagnitude            (_hdrShaderData.bloomMagnitude);
        _hdrStage->setToneMappingMode           (_hdrShaderData.toneMapTechnique);
        _hdrStage->setExposure                  (_hdrShaderData.exposure);
        _hdrStage->setKeyValue                  (_hdrShaderData.keyValue);
        _hdrStage->setAutoExposureMode          (_hdrShaderData.autoExposure);
        _hdrStage->setWhiteLevel                (_hdrShaderData.whiteLevel);
        _hdrStage->setFilmicShoulderStrenght    (_hdrShaderData.shoulderStrength);
        _hdrStage->setFilmicLinearStrength      (_hdrShaderData.linearStrength);
        _hdrStage->setFilmicLinearAngle         (_hdrShaderData.linearAngle);
        _hdrStage->setFilmicToeStrength         (_hdrShaderData.toeStrength);
        _hdrStage->setFilmicToeNumerator        (_hdrShaderData.toeNumerator);
        _hdrStage->setFilmicToeDenominator      (_hdrShaderData.toeDenominator);
        _hdrStage->setFilmicLinearWhite         (_hdrShaderData.linearWhite);
        _hdrStage->setSaturation                (_hdrShaderData.lumSaturation);
        _hdrStage->setDragoBias                 (_hdrShaderData.bias);
        _hdrStage->setTau                       (_hdrShaderData.tau);
        _hdrStage->setNumTaps                   (_hdrShaderData.nTaps);
        _hdrStage->setBlurGaussSigma            (_hdrShaderData.sigma);
        _hdrStage->setUseLinChromCorrection     (_hdrShaderData.useLinChromInterp);
    }
}

void Example::enable_hdr_stage()
{
    if (!_hdrStage)
    {
        create_hdr_stage();
    }
    else
    {
        _hdrNode->setCore(_hdrStage);
    }
}

void Example::disable_hdr_stage()
{
    if (!_hdrGroup)
    {
        _hdrGroup = OSG::Group::create();
    }

    _hdrNode->setCore(_hdrGroup);
}

void Example::create_ssao_stage()
{
    if (_ssaoNode)
    {
        _ssaoStage = OSG::SSAOStage::create();
        _ssaoGroup = OSG::Group::create();

        setup_ssao_stage();

        _ssaoNode->setCore(_ssaoStage);
    }
}

void Example::setup_ssao_stage()
{
    if (_ssaoStage)
    {
        _ssaoStage->setCalcPosFromDepth(true);
    }
}

void Example::enable_ssao_stage()
{
    if (!_ssaoStage)
    {
        create_ssao_stage();
    }
    else
    {
        _ssaoNode->setCore(_ssaoStage);
    }
}

void Example::disable_ssao_stage()
{
    if (!_ssaoGroup)
    {
        _ssaoGroup = OSG::Group::create();
    }

    _ssaoNode->setCore(_ssaoGroup);
}

void Example::createMaterialManager()
{
    OSG::ShaderProgramFunctor   initFunctor = boost::bind(&Example::initShader,   this, _1);
    OSG::ShaderProgramFunctor updateFunctor = boost::bind(&Example::updateShader, this, _1);

    _materialManager = OSG::DescMaterialManager::createDefault(initFunctor, "", updateFunctor, "");
    _materialManager->setWindow(_mgr->getWindow());

    OSG::BitVector mask = OSG::MaterialDesc::DescHashFieldMask
                        | OSG::MaterialDesc::OverrideShadingModelFieldMask
                        ;

    _materialManager->setExcludeHashingMask(mask);

    _imageMap = _materialManager->getImageMap();
}

void Example::initMaterialManager()
{
    _materialManager->setMultiLightGroup        (_multiLightGroup);
    _materialManager->setLightBindingPnt        (light_binding_point);
    _materialManager->setHDR2Stage              (_hdrStage);
    //_materialManager->setClusterShadingStage    (_clusterStage)
    _materialManager->setSSAOStage              (_ssaoStage);
    _materialManager->setMultiLightShadowStage  (_shadowStage);
    _materialManager->setHasClipPlanes          (false);

    createMaterials();
}

void Example::initShader(OSG::ShaderProgram* shader)
{
    if (shader && shader->getShaderType() == GL_VERTEX_SHADER)
    {
        // shader->addUniformVariable("testValue", testValue);
    }

    if (shader && shader->getShaderType() == GL_FRAGMENT_SHADER)
    {
        // shader->addUniformVariable("testValue", testValue);
    }
}

void Example::updateShader(OSG::ShaderProgram* shader)
{
    if (shader && shader->getShaderType() == GL_VERTEX_SHADER)
    {
        // shader->updateUniformVariable("testValue", testValue);
    }

    if (shader && shader->getShaderType() == GL_FRAGMENT_SHADER)
    {
        // shader->updateUniformVariable("testValue", testValue);
    }
}

void Example::createMaterials()
{
    _floorMaterial = NULL;
    _vecMaterials.clear();
    _vecMaterialsLights.clear();

    setupMaterialFloor ();
    setupMaterialLights();

    setupMaterial0 ();
    setupMaterial1 ();
    setupMaterial2 ();
    setupMaterial3 ();
    setupMaterial4 ();
    setupMaterial5 ();
    setupMaterial6 ();
    setupMaterial7 ();
    setupMaterial8 ();
    setupMaterial9 ();
    setupMaterial10();
    setupMaterial11();
    setupMaterial12();
    setupMaterial13();
    setupMaterial14();
    setupMaterial15();
    setupMaterial16();
    setupMaterial17();

    _material_dist    = DistributionType(0, static_cast<OSG::UInt32>(_vecMaterials.size())-1);
    _material_idx_die = GeneratorType(_rng, _material_dist);
}

void Example::create_lights(OSG::UInt32 requiredShadowFeatures)
{
    _multiLightGroup = OSG::MultiLightGroup::create();
    _multiLightGroup->setUsage(GL_DYNAMIC_DRAW);
    _multiLightGroup->setLayoutType(OSG::MultiLight::OPENGL_LAYOUT 
                                  | OSG::MultiLight:: RANGE_LAYOUT);

    _multiLightGroup->setFeatures(requiredShadowFeatures, true);
    _multiLightGroup->setAutoCalcRanges(true);
    _multiLightGroup->setLightBindingPnt(light_binding_point);

    _lightNode = OSG::makeNodeFor(_multiLightGroup);

    OSG::Int32           light1_idx, light2_idx, light3_idx, light4_idx;
    OSG::TransformRefPtr light1_trans, light2_trans, light3_trans, light4_trans;

    OSG::NodeRefPtr light1_beacon = OSG::makeCoredNode<OSG::Transform>(&light1_trans);
    OSG::NodeRefPtr light2_beacon = OSG::makeCoredNode<OSG::Transform>(&light2_trans);
    OSG::NodeRefPtr light3_beacon = OSG::makeCoredNode<OSG::Transform>(&light3_trans);
    OSG::NodeRefPtr light4_beacon = OSG::makeCoredNode<OSG::Transform>(&light4_trans);

    //
    // lights should not be shadow casters by itself
    //
    _shadowStage->editMFExcludeNodes()->push_back(light1_beacon);
    _shadowStage->editMFExcludeNodes()->push_back(light2_beacon);
    _shadowStage->editMFExcludeNodes()->push_back(light3_beacon);
    _shadowStage->editMFExcludeNodes()->push_back(light4_beacon);

    OSG::Int32 shadowParam1_idx, shadowParam2_idx, shadowParam3_idx, shadowParam4_idx;

    //
    // Default settings of the example
    //
    _current_light_index = 0;

    bool enabled_light1 = true;
    bool enabled_light2 = true;
    bool enabled_light3 = true;
    bool enabled_light4 = true;

    bool shadow_light1 = true;
    bool shadow_light2 = true;
    bool shadow_light3 = true;
    bool shadow_light4 = true;

    const OSG::Int32 nbrOfSplits1 = 1;
    const OSG::Int32 nbrOfSplits2 = 1;
    const OSG::Int32 nbrOfSplits3 = 1;
    const OSG::Int32 nbrOfSplits4 = 1;

    const bool useFocusing1 = true;
    const bool useFocusing2 = true;
    const bool useFocusing3 = true;
    const bool useFocusing4 = true;

    const bool useLiSP1 = true;
    const bool useLiSP2 = true;
    const bool useLiSP3 = true;
    const bool useLiSP4 = true;

    const OSG::Int32 filterMode1 = OSG::MultiLightShadowStage::PCF_MODE_DISABLED;
    const OSG::Int32 filterMode2 = OSG::MultiLightShadowStage::PCF_MODE_DISABLED;
    const OSG::Int32 filterMode3 = OSG::MultiLightShadowStage::PCF_MODE_DISABLED;
    const OSG::Int32 filterMode4 = OSG::MultiLightShadowStage::PCF_MODE_DISABLED;

    OSG::Real32 filterRadius1 = 0.12f;
    OSG::Real32 filterRadius2 = 0.12f;
    OSG::Real32 filterRadius3 = 0.12f;
    OSG::Real32 filterRadius4 = 0.12f;

    OSG::Real32 intensity1 = 1.f;   // 0.8f
    OSG::Real32 intensity2 = 1.f;   // 0.7
    OSG::Real32 intensity3 = 1.f;   // 0.7
    OSG::Real32 intensity4 = 1.f;   // 0.7

    //OSG::MultiLightShadowParameterRefPtr shadowParam1 = OSG::MultiLightShadowParameter::create();
    //OSG::MultiLightShadowParameterRefPtr shadowParam2 = OSG::MultiLightShadowParameter::create();
    //OSG::MultiLightShadowParameterRefPtr shadowParam3 = OSG::MultiLightShadowParameter::create();
    //OSG::MultiLightShadowParameterRefPtr shadowParam4 = OSG::MultiLightShadowParameter::create();

    OSG::MultiLightShadowParameterAdvancedRefPtr shadowParam1 = OSG::MultiLightShadowParameterAdvanced::create();
    OSG::MultiLightShadowParameterAdvancedRefPtr shadowParam2 = OSG::MultiLightShadowParameterAdvanced::create();
    OSG::MultiLightShadowParameterAdvancedRefPtr shadowParam3 = OSG::MultiLightShadowParameterAdvanced::create();
    OSG::MultiLightShadowParameterAdvancedRefPtr shadowParam4 = OSG::MultiLightShadowParameterAdvanced::create();

    shadowParam1->setBias(0.1f);
    shadowParam1->setIntensity(intensity1);

    shadowParam2->setBias(0.1f);
    shadowParam2->setIntensity(intensity2);

    shadowParam3->setBias(0.5f);
    shadowParam3->setIntensity(intensity3);

    shadowParam4->setBias(0.5f);
    shadowParam4->setIntensity(intensity4);

    shadowParam1->setNumberOfSplits(nbrOfSplits1);
    shadowParam2->setNumberOfSplits(nbrOfSplits2);
    shadowParam3->setNumberOfSplits(nbrOfSplits3);
    shadowParam4->setNumberOfSplits(nbrOfSplits4);

    shadowParam1->setFocusing(useFocusing1);
    shadowParam2->setFocusing(useFocusing2);
    shadowParam3->setFocusing(useFocusing3);
    shadowParam4->setFocusing(useFocusing4);

    shadowParam1->setUseLiSP(useLiSP1);
    shadowParam2->setUseLiSP(useLiSP2);
    shadowParam3->setUseLiSP(useLiSP3);
    shadowParam4->setUseLiSP(useLiSP4);

    shadowParam1->setFilterMode(filterMode1);
    shadowParam2->setFilterMode(filterMode2);
    shadowParam3->setFilterMode(filterMode3);
    shadowParam4->setFilterMode(filterMode4);

    shadowParam1->setFilterRadius(filterRadius1);
    shadowParam2->setFilterRadius(filterRadius2);
    shadowParam3->setFilterRadius(filterRadius3);
    shadowParam4->setFilterRadius(filterRadius4);
    

    shadowParam1_idx = _shadowStage->addShadowParameter(shadowParam1);
    shadowParam2_idx = _shadowStage->addShadowParameter(shadowParam2);
    shadowParam3_idx = _shadowStage->addShadowParameter(shadowParam3);
    shadowParam4_idx = _shadowStage->addShadowParameter(shadowParam4);

    OSG::MultiLight light1(OSG::MultiLight::POINT_LIGHT);
    light1.setAmbient (1.f, 1.f, 1.f);
    light1.setDiffuse (1.f, 1.f, 1.f);
    light1.setSpecular(1.f, 1.f, 1.f);
    light1.setBeacon(light1_beacon);
    light1.setEnabled(enabled_light1);
    light1.setShadow(shadow_light1);
    light1.setShadowParameterIndex(shadowParam1_idx);

    OSG::MultiLight light2(OSG::MultiLight::SPOT_LIGHT);
    light2.setDirection(OSG::Vec3f(0.f, 0.f, 0.f) - OSG::Vec3f(0.f, 7.f, 3.f));
    light2.setSpotlightAngle(35.f);    //45.f
    light2.setAmbient (1.f, 1.f, 1.f);
    light2.setDiffuse (1.f, 1.f, 1.f);
    light2.setSpecular(1.f, 1.f, 1.f);
    light2.setBeacon(light2_beacon);
    light2.setEnabled(enabled_light2);
    light2.setShadow(shadow_light2);
    light2.setShadowParameterIndex(shadowParam2_idx);
/*
    light2.setDirection(OSG::Vec3f(-0.000157111499f, -0.948618114f, -0.316423357f));
    light2.setSpotlightAngle(43.8141289f);    //45.f
    light2.setAmbient (1.f, 1.f, 1.f);
    light2.setDiffuse (1.f, 1.f, 1.f);
    light2.setSpecular(1.f, 1.f, 1.f);
    light2.setBeacon(light2_beacon);
    light2.setEnabled(enabled_light2);
    light2.setShadow(shadow_light2);
    light2.setShadowParameterIndex(shadowParam2_idx);
*/

    OSG::MultiLight light3(OSG::MultiLight::DIRECTIONAL_LIGHT);
    light3.setDirection(OSG::Vec3f(0.654f, -0.589f, -0.476f)); //(*)
    light3.setAmbient (1.f, 1.f, 1.f);
    light3.setDiffuse (1.f, 1.f, 1.f);
    light3.setSpecular(1.f, 1.f, 1.f);
    light3.setBeacon(light3_beacon);
    light3.setEnabled(enabled_light3);
    light3.setShadow(shadow_light3);
    light3.setShadowParameterIndex(shadowParam3_idx);

    OSG::MultiLight light4(OSG::MultiLight::DIRECTIONAL_LIGHT);
    light4.setDirection(OSG::Vec3f(0.654f, -0.589f, 0.476f)); //(*)
    light4.setAmbient (1.f, 1.f, 1.f);
    light4.setDiffuse (1.f, 1.f, 1.f);
    light4.setSpecular(1.f, 1.f, 1.f);
    light4.setBeacon(light4_beacon);
    light4.setEnabled(enabled_light4);
    light4.setShadow(shadow_light4);
    light4.setShadowParameterIndex(shadowParam4_idx);

    // (*) Old OpenGL stores the light direction in the 4D position parameter
    //     with w=0. A value of (1,0,0) represents a light at infinity in the
    //     positive x-direction. This light shines into the (-1,0,0) direction.
    //     In our multi light we provide the light direction directly, i.e.
    //     (-1,0,0) in the example.

    light1_trans->editMatrix().setTranslate(0.f, 4.f, 3.f);    //(0.f, 9.5f, 3.f); //(0.f, 4.f, 3.f);//(0.f, 5.0f, 0.f);
    light2_trans->editMatrix().setTranslate(0.f, 7.f, 3.f);    //(0.f, 7.f, 3.f);
    light3_trans->editMatrix().setTranslate(-light3.getDirection());
    light4_trans->editMatrix().setTranslate(-light4.getDirection());

    light1_idx = _multiLightGroup->addLight(light1);
    light2_idx = _multiLightGroup->addLight(light2);
    light3_idx = _multiLightGroup->addLight(light3);
    light4_idx = _multiLightGroup->addLight(light4);

    // This is placed here, because the create_lights function setups needed _multiLightGroup
    // and simultaneously creates geometry with material.
    initMaterialManager();

    if (create_geom_for_lights)
    {
        create_light_geometry(false, light1, light1_idx, true);
        create_light_geometry(false, light2, light2_idx, true);
        create_light_geometry(false, light3, light3_idx, true);
        create_light_geometry(false, light4, light4_idx, true);

        create_light_geometry(true, light1, light1_idx, false);
        create_light_geometry(true, light2, light2_idx, false);
        create_light_geometry(true, light3, light3_idx, false);
        create_light_geometry(true, light4, light4_idx, false);
    }

    _lightBeaconsTansforms.push_back(light1_trans);
    _lightBeaconsTansforms.push_back(light2_trans);
    _lightBeaconsTansforms.push_back(light3_trans);
    _lightBeaconsTansforms.push_back(light4_trans);

    _lightIndices.push_back(light1_idx);
    _lightIndices.push_back(light2_idx);
    _lightIndices.push_back(light3_idx);
    _lightIndices.push_back(light4_idx);

    //
    // the beacons are added to the _materialNode because of the light
    // animation geometry (see create_light_geometry above). This geometry
    // is also rendered by the shader program.
    //
    _shadowNode->addChild(light1_beacon);
    _shadowNode->addChild(light2_beacon);
    _shadowNode->addChild(light3_beacon);
    _shadowNode->addChild(light4_beacon);
}

void Example::setLightFramePosition(OSG::UInt32 idx, const OSG::Pnt3f& position)
{
    OSG::Transform* tansform = _lightBeaconsTansforms[idx];
    OSG::Matrix mat = tansform->getMatrix();

    mat.setTranslate(position);
    tansform->setMatrix(mat);

    _multiLightGroup->changedBeacon();
}

OSG::Pnt3f Example::getLightFramePosition(OSG::UInt32 idx) const
{
    OSG::Transform* tansform = _lightBeaconsTansforms[idx];
    const OSG::Matrix& mat = tansform->getMatrix();

    OSG::Vec3f      translation, scaleFactor;
    OSG::Quaternion rotation, scaleOrientation;

    mat.getTransform(translation, rotation, scaleFactor, scaleOrientation);

    return translation.addToZero();
}

void Example::MeasureFPS(bool to_title)
{
    OSG::Time now = OSG::getSystemTime();
    OSG::Time delta_time_fps = now - _fps_time_point;

    ++_fps_num_frames;
    if (delta_time_fps > 1.0)
    {
        _fps = _fps_num_frames / delta_time_fps;

        if (to_title) {
            char buffer[1024];
            sprintf_s(buffer, "FPS: %3.3f", _fps);
            glutSetWindowTitle(buffer);
        }

        _fps_time_point = OSG::getSystemTime();
        _fps_num_frames = 0;
    }
}

//
// Initialize GLUT & OpenSG and set up the scene
//
int main(int argc, char **argv)
{
    Example example(argc, argv);

    // GLUT main loop
    glutMainLoop();

#ifdef OSG_WITH_ANTTWEAKBAR
    TwTerminate();
#endif

    return 0;
}

/*---- HDRShaderData ------------------------------------------------------*/

HDRShaderData::HDRShaderData()
: bloomThreshold(2.0f)
, bloomMagnitude(0.0f)
, toneMapTechnique(4)
, exposure(0.0f)
, keyValue(0.18f)
, autoExposure(2)
, whiteLevel(5.0f)
, shoulderStrength(0.15f)
, linearStrength(0.5f)
, linearAngle(0.1f)
, toeStrength(0.2f)
, toeNumerator(0.02f)
, toeDenominator(0.3f)
, linearWhite(11.2f)
, lumSaturation(1.0f)
, bias(0.85f)
, tau(1.25f)
, nTaps(4)
, sigma(0.8f)
, useLinChromInterp(true)
{}

HDRShaderData::HDRShaderData(const HDRShaderData& rhs)
: bloomThreshold(rhs.bloomThreshold)
, bloomMagnitude(rhs.bloomMagnitude)
, toneMapTechnique(rhs.toneMapTechnique)
, exposure(rhs.exposure)
, keyValue(rhs.keyValue)
, autoExposure(rhs.autoExposure)
, whiteLevel(rhs.whiteLevel)
, shoulderStrength(rhs.shoulderStrength)
, linearStrength(rhs.linearStrength)
, linearAngle(rhs.linearAngle)
, toeStrength(rhs.toeStrength)
, toeNumerator(rhs.toeNumerator)
, toeDenominator(rhs.toeDenominator)
, linearWhite(rhs.linearWhite)
, lumSaturation(rhs.lumSaturation)
, bias(rhs.bias)
, tau(rhs.tau)
, nTaps(rhs.nTaps)
, sigma(rhs.sigma)
, useLinChromInterp(rhs.useLinChromInterp)
{}

HDRShaderData& HDRShaderData::operator=(const HDRShaderData& rhs)
{
    if (&rhs == this) return *this;

    bloomThreshold = rhs.bloomThreshold;
    bloomMagnitude = rhs.bloomMagnitude;
    toneMapTechnique = rhs.toneMapTechnique;
    exposure = rhs.exposure;
    keyValue = rhs.keyValue;
    autoExposure = rhs.autoExposure;
    whiteLevel = rhs.whiteLevel;
    shoulderStrength = rhs.shoulderStrength;
    linearStrength = rhs.linearStrength;
    linearAngle = rhs.linearAngle;
    toeStrength = rhs.toeStrength;
    toeNumerator = rhs.toeNumerator;
    toeDenominator = rhs.toeDenominator;
    linearWhite = rhs.linearWhite;
    lumSaturation = rhs.lumSaturation;
    bias = rhs.bias;
    tau = rhs.tau;
    nTaps = rhs.nTaps;
    sigma = rhs.sigma;
    useLinChromInterp = rhs.useLinChromInterp;

    return *this;
}

HDRShaderData HDRShaderData::create_min_shader_data()
{
    HDRShaderData data;

    data.bloomThreshold = 0.0;
    data.bloomMagnitude = 0.0;
    data.toneMapTechnique = 0;
    data.exposure = -10.0;
    data.keyValue = 0.0;
    data.autoExposure = 0;
    data.whiteLevel = 0.0;
    data.shoulderStrength = 0.0;
    data.linearStrength = 0.0;
    data.linearAngle = 0.0;
    data.toeStrength = 0.0;
    data.toeNumerator = 0.0;
    data.toeDenominator = 0.0;
    data.linearWhite = 0.0;
    data.lumSaturation = 0.0;
    data.bias = 0.0;
    data.tau = 0.0;
    data.nTaps = 2;
    data.sigma = 0.5;

    return data;
}

HDRShaderData HDRShaderData::create_max_shader_data()
{
    HDRShaderData data;

    data.bloomThreshold = 10.0;
    data.bloomMagnitude = 2.0;
    data.toneMapTechnique = 7;
    data.exposure = 10.0;
    data.keyValue = 1.0;
    data.autoExposure = 2;
    data.whiteLevel = 25.0;
    data.shoulderStrength = 2.0;
    data.linearStrength = 5.0;
    data.linearAngle = 1.0;
    data.toeStrength = 2.0;
    data.toeNumerator = 0.5;
    data.toeDenominator = 2.0;
    data.linearWhite = 20.0;
    data.lumSaturation = 4.0;
    data.bias = 1.0;
    data.tau = 40.0;
    data.nTaps = 10;
    data.sigma = 1.5;

    return data;
}

/*---- AntTweakBar --------------------------------------------------------*/

#ifdef OSG_WITH_ANTTWEAKBAR

std::string sGenTwDefinition(float vMin, float vMax, float steps, int precision, const char* keyinc, const char* keydec, const char* msg, const char* grp = NULL)
{
    std::string result;
    std::stringstream stream;

    stream << "min=" << vMin << " "
           << "max=" << vMax << " "
           << "step=" << (vMax - vMin)/steps << " "
           << "precision=" << precision << " "
           << "keyIncr=" << keyinc << " "
           << "keyDecr=" << keydec << " "
           << "help='" << msg << "'";

    if (grp)
        stream << " " << "group=" << grp;

    result = stream.str();

    return result;
}

std::string sGenTwDefinition(int vMin, int vMax, int delta, const char* keyinc, const char* keydec, const char* msg, const char* grp = NULL)
{
    std::string result;
    std::stringstream stream;

    stream << "min=" << vMin << " "
           << "max=" << vMax << " "
           << "step=" << delta << " "
           << "keyIncr=" << keyinc << " "
           << "keyDecr=" << keydec << " "
           << "help='" << msg << "'";

    if (grp)
        stream << " " << "group=" << grp;

    result = stream.str();

    return result;
}

void TW_CALL ResetParametersCB(void *clientData)
{ 
    Example* example = reinterpret_cast<Example*>(clientData);
    example->ResetParameters();
}

void TW_CALL SetSampleNumberCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetSampleNumber(*num);
}

void TW_CALL GetSampleNumberCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetSampleNumber();
}

void TW_CALL SetClearColorCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Color3f* num = reinterpret_cast<const OSG::Color3f*>(value);
    example->SetClearColor(*num);
}

void TW_CALL GetClearColorCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Color3f* num = reinterpret_cast<OSG::Color3f*>(value);
    *num = example->GetClearColor();
}

void TW_CALL SetForceBgndCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetForceBgnd(*num);
}

void TW_CALL GetForceBgndCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetForceBgnd();
}

void TW_CALL SetAjustLuminanceCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetAjustLuminance(*num);
}

void TW_CALL GetAjustLuminanceCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetAjustLuminance();
}
void TW_CALL SetSkyBgndIndexCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetSkyBgndIndex(*num);
}

void TW_CALL GetSkyBgndIndexCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetSkyBgndIndex();
}

void TW_CALL SetPerformBloomCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetPerformBloom(*num);
}

void TW_CALL GetPerformBloomCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetPerformBloom();
}

void TW_CALL SetBloomBackgroundCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetBloomBackground(*num);
}

void TW_CALL GetBloomBackgroundCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetBloomBackground();
}

void TW_CALL SetCarryDepthCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetCarryDepth(*num);
}

void TW_CALL GetCarryDepthCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetCarryDepth();
}

void TW_CALL SetUseHDRCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetUseHDR(*num);
}

void TW_CALL GetUseHDRCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetUseHDR();
}


void TW_CALL SetResultIndexCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetResultIndex(*num);
}

void TW_CALL GetResultIndexCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetResultIndex();
}

void TW_CALL SetRenderEmissiveCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetRenderEmissive(*num);
}

void TW_CALL GetRenderEmissiveCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetRenderEmissive();
}

void TW_CALL SetRenderAmbientCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetRenderAmbient(*num);
}

void TW_CALL GetRenderAmbientCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetRenderAmbient();
}

void TW_CALL SetRenderDiffuseCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetRenderDiffuse(*num);
}

void TW_CALL GetRenderDiffuseCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetRenderDiffuse();
}

void TW_CALL SetRenderSpecularCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetRenderSpecular(*num);
}

void TW_CALL GetRenderSpecularCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetRenderSpecular();
}

void TW_CALL SetAccurateGammaCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetAccurateGamma(*num);
}

void TW_CALL GetAccurateGammaCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetAccurateGamma();
}

void TW_CALL SetGammaCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetGamma(*num);
}

void TW_CALL GetGammaCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetGamma();
}

void TW_CALL SetUseITURBT709CB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetUseITURBT709(*num);
}

void TW_CALL GetUseITURBT709CB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetUseITURBT709();
}

void TW_CALL SetMipmapLevelCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetMipmapLevel(*num);
}

void TW_CALL GetMipmapLevelCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetMipmapLevel();
}

void TW_CALL SetBloomThresholdCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetBloomThreshold(*num);
}

void TW_CALL GetBloomThresholdCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetBloomThreshold();
}

void TW_CALL SetBloomMagnitudeCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetBloomMagnitude(*num);
}

void TW_CALL GetBloomMagnitudeCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetBloomMagnitude();
}

void TW_CALL SetToneMapTechniqueCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetToneMapTechnique(*num);
}

void TW_CALL GetToneMapTechniqueCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetToneMapTechnique();
}

void TW_CALL SetExposureCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetExposure(*num);
}

void TW_CALL GetExposureCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetExposure();
}

void TW_CALL SetKeyValueCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetKeyValue(*num);
}

void TW_CALL GetKeyValueCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetKeyValue();
}

void TW_CALL SetAutoExposureCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetAutoExposure(*num);
}

void TW_CALL GetAutoExposureCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetAutoExposure();
}

void TW_CALL SetWhiteLevelCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetWhiteLevel(*num);
}

void TW_CALL GetWhiteLevelCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetWhiteLevel();
}

void TW_CALL SetShoulderStrengthCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetShoulderStrength(*num);
}

void TW_CALL GetShoulderStrengthCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetShoulderStrength();
}

void TW_CALL SetLinearStrengthCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetLinearStrength(*num);
}

void TW_CALL GetLinearStrengthCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetLinearStrength();
}

void TW_CALL SetLinearAngleCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetLinearAngle(*num);
}

void TW_CALL GetLinearAngleCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetLinearAngle();
}

void TW_CALL SetToeStrengthCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetToeStrength(*num);
}

void TW_CALL GetToeStrengthCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetToeStrength();
}

void TW_CALL SetToeNumeratorCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetToeNumerator(*num);
}

void TW_CALL GetToeNumeratorCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetToeNumerator();
}

void TW_CALL SetToeDenominatorCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetToeDenominator(*num);
}

void TW_CALL GetToeDenominatorCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetToeDenominator();
}

void TW_CALL SetLinearWhiteCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetLinearWhite(*num);
}

void TW_CALL GetLinearWhiteCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetLinearWhite();
}

void TW_CALL SetLumSaturationCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetLumSaturation(*num);
}

void TW_CALL GetLumSaturationCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetLumSaturation();
}

void TW_CALL SetBiasCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetBias(*num);
}

void TW_CALL GetBiasCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetBias();
}

void TW_CALL SetTauCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetTau(*num);
}

void TW_CALL GetTauCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetTau();
}

void TW_CALL SetNTapsCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetNTaps(*num);
}

void TW_CALL GetNTapsCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetNTaps();
}

void TW_CALL SetSigmaCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetSigma(*num);
}

void TW_CALL GetSigmaCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetSigma();
}

void TW_CALL SetUseLinChromInterpCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetUseLinChromInterp(*num);
}

void TW_CALL GetUseLinChromInterpCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetUseLinChromInterp();
}

void TW_CALL SetCurrentLightCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::UInt32* num = reinterpret_cast<const OSG::UInt32*>(value);
    example->SetCurrentLight(*num);
}

void TW_CALL GetCurrentLightCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::UInt32* num = reinterpret_cast<OSG::UInt32*>(value);
    *num = example->GetCurrentLight();
}

void TW_CALL SetLightPositionCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Pnt3f* num = reinterpret_cast<const OSG::Pnt3f*>(value);
    example->SetLightPosition(*num);
}

void TW_CALL GetLightPositionCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Pnt3f* num = reinterpret_cast<OSG::Pnt3f*>(value);
    *num = example->GetLightPosition();
}

void TW_CALL SetLightDirectionCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Vec3f* num = reinterpret_cast<const OSG::Vec3f*>(value);
    example->SetLightDirection(*num);
}

void TW_CALL GetLightDirectionCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Vec3f* num = reinterpret_cast<OSG::Vec3f*>(value);
    *num = example->GetLightDirection();
}

void TW_CALL SetLightAmbientCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const  OSG::Color3f* num = reinterpret_cast<const  OSG::Color3f*>(value);
    example->SetLightAmbient(*num);
}

void TW_CALL GetLightAmbientCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Color3f* num = reinterpret_cast<OSG::Color3f*>(value);
    *num = example->GetLightAmbient();
}

void TW_CALL SetLightDiffuseCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const  OSG::Color3f* num = reinterpret_cast<const  OSG::Color3f*>(value);
    example->SetLightDiffuse(*num);
}

void TW_CALL GetLightDiffuseCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Color3f* num = reinterpret_cast<OSG::Color3f*>(value);
    *num = example->GetLightDiffuse();
}

void TW_CALL SetLightSpecularCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const  OSG::Color3f* num = reinterpret_cast<const  OSG::Color3f*>(value);
    example->SetLightSpecular(*num);
}

void TW_CALL GetLightSpecularCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Color3f* num = reinterpret_cast<OSG::Color3f*>(value);
    *num = example->GetLightSpecular();
}

void TW_CALL SetLightAttenuationCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Vec3f* num = reinterpret_cast<const OSG::Vec3f*>(value);
    example->SetLightAttenuation(*num);
}

void TW_CALL GetLightAttenuationCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Vec3f* num = reinterpret_cast<OSG::Vec3f*>(value);
    *num = example->GetLightAttenuation();
}

void TW_CALL SetLightSpotlightAngCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetLightSpotlightAng(*num);
}

void TW_CALL GetLightSpotlightAngCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetLightSpotlightAng();
}

void TW_CALL SetLightSpotExponentCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetLightSpotExponent(*num);
}

void TW_CALL GetLightSpotExponentCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetLightSpotExponent();
}

void TW_CALL SetLightTypeCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetLightType(*num);
}

void TW_CALL GetLightTypeCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetLightType();
}

void TW_CALL SetLightEnabledCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetLightEnabled(*num);
}

void TW_CALL GetLightEnabledCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetLightEnabled();
}

void TW_CALL SetLightShadowCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetLightShadow(*num);
}

void TW_CALL GetLightShadowCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetLightShadow();
}

void TW_CALL SetRenderSplittingCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetRenderSplitting(*num);
}

void TW_CALL GetRenderSplittingCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetRenderSplitting();
}

void TW_CALL SetLightShadowBiasCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetLightShadowBias(*num);
}

void TW_CALL GetLightShadowBiasCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetLightShadowBias();
}

void TW_CALL SetLightShadowIntCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetLightShadowInt(*num);
}

void TW_CALL GetLightShadowIntCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetLightShadowInt();
}

void TW_CALL SetShadowOnCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowOn(*num);
}

void TW_CALL GetShadowOnCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowOn();
}

void TW_CALL SetShadowModeCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Int32* num = reinterpret_cast<const OSG::Int32*>(value);
    example->SetShadowMode(*num);
}

void TW_CALL GetShadowModeCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Int32* num = reinterpret_cast<OSG::Int32*>(value);
    *num = example->GetShadowMode();
}

void TW_CALL SetShadowBiasCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetShadowBias(*num);
}

void TW_CALL GetShadowBiasCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetShadowBias();
}

void TW_CALL SetShadowFactorCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetShadowFactor(*num);
}

void TW_CALL GetShadowFactorCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetShadowFactor();
}

void TW_CALL SetShadowCullFaceCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowCullFace(*num);
}

void TW_CALL GetShadowCullFaceCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowCullFace();
}

void TW_CALL SetShadowMapSizeCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::UInt32* num = reinterpret_cast<const OSG::UInt32*>(value);
    example->SetShadowMapSize(*num);
}

void TW_CALL GetShadowMapSizeCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::UInt32* num = reinterpret_cast<OSG::UInt32*>(value);
    *num = example->GetShadowMapSize();
}

void TW_CALL SetShadowTweakVolCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetShadowTweakVol(*num);
}

void TW_CALL GetShadowTweakVolCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetShadowTweakVol();
}

void TW_CALL SetShadowFilterModeCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Int32* num = reinterpret_cast<const OSG::Int32*>(value);
    example->SetShadowFilterMode(*num);
}

void TW_CALL GetShadowFilterModeCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Int32* num = reinterpret_cast<OSG::Int32*>(value);
    *num = example->GetShadowFilterMode();
}

void TW_CALL SetShadowFilterSizeCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Int32* num = reinterpret_cast<const OSG::Int32*>(value);
    example->SetShadowFilterSize(*num);
}

void TW_CALL GetShadowFilterSizeCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Int32* num = reinterpret_cast<OSG::Int32*>(value);
    *num = example->GetShadowFilterSize();
}

void TW_CALL SetShadowSearchSizeCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Int32* num = reinterpret_cast<const OSG::Int32*>(value);
    example->SetShadowSearchSize(*num);
}

void TW_CALL GetShadowSearchSizeCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Int32* num = reinterpret_cast<OSG::Int32*>(value);
    *num = example->GetShadowSearchSize();
}

void TW_CALL SetShadowFilterRadiusCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetShadowFilterRadius(*num);
}

void TW_CALL GetShadowFilterRadiusCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetShadowFilterRadius();
}

void TW_CALL SetShadowRandomRotateCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowRandomRotate(*num);
}

void TW_CALL GetShadowRandomRotateCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowRandomRotate();
}

void TW_CALL SetShadowUseBlockerSearchCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowUseBlockerSearch(*num);
}

void TW_CALL GetShadowUseBlockerSearchCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowUseBlockerSearch();
}

void TW_CALL SetShadowUsePCSSCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowUsePCSS(*num);
}

void TW_CALL GetShadowUsePCSSCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowUsePCSS();
}

void TW_CALL SetShadowFocusingCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowFocusing(*num);
}

void TW_CALL GetShadowFocusingCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowFocusing();
}

void TW_CALL SetShadowUseLiSPCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowUseLiSP(*num);
}

void TW_CALL GetShadowUseLiSPCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowUseLiSP();
}

void TW_CALL SetShadowLiSPModeCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Int32* num = reinterpret_cast<const OSG::Int32*>(value);
    example->SetShadowLiSPMode(*num);
}

void TW_CALL GetShadowLiSPModeCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Int32* num = reinterpret_cast<OSG::Int32*>(value);
    *num = example->GetShadowLiSPMode();
}

void TW_CALL SetShadowNbrOfSplitsCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Int32* num = reinterpret_cast<const OSG::Int32*>(value);
    example->SetShadowNbrOfSplits(*num);
}

void TW_CALL GetShadowNbrOfSplitsCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Int32* num = reinterpret_cast<OSG::Int32*>(value);
    *num = example->GetShadowNbrOfSplits();
}

void TW_CALL SetShadowUseGeomShaderCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowUseGeomShader(*num);
}

void TW_CALL GetShadowUseGeomShaderCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowUseGeomShader();
}

void TW_CALL SetShadowReduceSwimmingCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowReduceSwimming(*num);
}

void TW_CALL GetShadowReduceSwimmingCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowReduceSwimming();
}

void TW_CALL SetShadowLightSpaceAlignCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowLightSpaceAlign(*num);
}

void TW_CALL GetShadowLightSpaceAlignCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowLightSpaceAlign();
}

void TW_CALL SetShadowUseMinDepthCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowUseMinDepth(*num);
}

void TW_CALL GetShadowUseMinDepthCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowUseMinDepth();
}

void TW_CALL SetShadowUseBestResolSelCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowUseBestResolSel(*num);
}

void TW_CALL GetShadowUseBestResolSelCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowUseBestResolSel();
}

void TW_CALL SetShadowWarpParameterCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetShadowWarpParameter(*num);
}

void TW_CALL GetShadowWarpParameterCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetShadowWarpParameter();
}

void TW_CALL SetShadowSplitParameterCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetShadowSplitParameter(*num);
}

void TW_CALL GetShadowSplitParameterCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetShadowSplitParameter();
}

void TW_CALL SetShadowZNearCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetShadowZNear(*num);
}

void TW_CALL GetShadowZNearCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetShadowZNear();
}

void TW_CALL SetShadowPseudoNearCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetShadowPseudoNear(*num);
}

void TW_CALL GetShadowPseudoNearCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetShadowPseudoNear();
}

void TW_CALL SetShadowPseudoFarCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Real32* num = reinterpret_cast<const OSG::Real32*>(value);
    example->SetShadowPseudoFar(*num);
}

void TW_CALL GetShadowPseudoFarCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Real32* num = reinterpret_cast<OSG::Real32*>(value);
    *num = example->GetShadowPseudoFar();
}

void TW_CALL SetShadowUseHwPCFCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowUseHwPCF(*num);
}

void TW_CALL GetShadowUseHwPCFCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowUseHwPCF();
}


void TW_CALL SetShadowArbTestCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetShadowArbTest(*num);
}

void TW_CALL GetShadowArbTestCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetShadowArbTest();
}

void Example::ResetParameters()
{
    _hdrShaderData = _hdrShaderDataDefault;

    if (_hdrStage)
        create_hdr_stage();

    glutPostRedisplay();
}

void Example::SetSampleNumber(int value)
{
    if (value < _num_samples)
    {
        switch (_num_samples)
        {
            case 0:
                break;
            case 4:
                _num_samples = 0;
                break;
            case 8:
                _num_samples = 4;
                break;
            case 16:
                _num_samples = 8;
                break;
            case 32:
                _num_samples = 16;
                break;
        }
    }
    else if (value > _num_samples)
    {
        switch (_num_samples)
        {
            case 0:
                _num_samples = 4;
                break;
            case 4:
                _num_samples = 8;
                break;
            case 8:
                _num_samples = 16;
                break;
            case 16:
                _num_samples = 32;
                break;
            case 32:
                break;
        }
    }

    if (_hdrStage)
        create_hdr_stage();

    glutPostRedisplay();
}

int Example::GetSampleNumber() const
{
    return _num_samples;
}

void Example::SetClearColor(const OSG::Color3f& value)
{
    _clear_color = value;

    OSG::SolidBackground* background = dynamic_cast<OSG::SolidBackground*>(_mgr->getBackground());
    if (background)
    {
        background->setColor(_clear_color);
    }

    glutPostRedisplay();
}

const OSG::Color3f& Example::GetClearColor() const
{
    return _clear_color;
}

void Example::SetForceBgnd(bool value)
{
    _force_bgnd = value;

    if (_hdrStage)
    _hdrStage->setForceBackground(_force_bgnd);

    glutPostRedisplay();
}

bool Example::GetForceBgnd() const
{
    return _force_bgnd;
}

void Example::SetAjustLuminance(bool value)
{
    _adjust_luminance = value;

    if (_hdrStage)
    _hdrStage->setAdjustLuminance(_adjust_luminance);

    glutPostRedisplay();
}

bool Example::GetAjustLuminance() const
{
    return _adjust_luminance;
}

void Example::SetPerformBloom(bool value)
{
    _perform_bloom = value;

    if (_hdrStage)
        create_hdr_stage();

    glutPostRedisplay();
}

bool Example::GetPerformBloom() const
{
    return _perform_bloom;
}

void Example::SetBloomBackground(bool value)
{
    _bloom_background = value;

    if (_hdrStage)
        _hdrStage->setBloomBackground(_bloom_background);

    glutPostRedisplay();
}

bool Example::GetBloomBackground() const
{
    return _bloom_background;
}

void Example::SetCarryDepth(bool value)
{
    _carry_depth = value;

    if (_hdrStage)
        create_hdr_stage();

    glutPostRedisplay();
}

bool Example::GetCarryDepth() const
{
    return _carry_depth;
}

void Example::SetUseHDR(bool value)
{
    if (value)
    {
        enable_hdr_stage();
    }
    else
    {
        disable_hdr_stage();
    }

    glutPostRedisplay();
}

bool Example::GetUseHDR() const
{
    bool using_hdr = false;

    if (_hdrNode)
    {
        OSG::HDR2Stage* hdrStage = dynamic_cast<OSG::HDR2Stage*>(_hdrNode->getCore());
        if (hdrStage)
            using_hdr = true;
    }

    return using_hdr;
}

void Example::SetSkyBgndIndex(int value)
{
    if (_skyBgnd_index != value)
    {
        _skyBgnd_index = value;

        setupBackground();

        glutPostRedisplay();
    }
}

int Example::GetSkyBgndIndex() const
{
    return static_cast<int>(_skyBgnd_index);
}

void Example::SetResultIndex(int value)
{
    if (_result_index != value)
    {
        _result_index = value;

        if (_hdrStage)
            _hdrStage->setTarget(_result_index);

        glutPostRedisplay();
    }
}

int Example::GetResultIndex() const
{
    return _result_index;
}

void Example::SetRenderEmissive(bool value)
{
    _render_emissive = value;
    glutPostRedisplay();
}

bool Example::GetRenderEmissive() const
{
    return _render_emissive;
}

void Example::SetRenderAmbient(bool value)
{
    _render_ambient = value;
    glutPostRedisplay();
}

bool Example::GetRenderAmbient() const
{
    return _render_ambient;
}

void Example::SetRenderDiffuse(bool value)
{
    _render_diffuse = value;
    glutPostRedisplay();
}

bool Example::GetRenderDiffuse() const
{
    return _render_diffuse;
}

void Example::SetRenderSpecular(bool value)
{
    _render_specular = value;
    glutPostRedisplay();
}

bool Example::GetRenderSpecular() const
{
    return _render_specular;
}

void Example::SetRenderSplitting(bool value)
{
    _render_splitting = value;
    glutPostRedisplay();
}

bool Example::GetRenderSplitting() const
{
    return _render_splitting;
}

void Example::SetAccurateGamma(bool value)
{
    _accurate_gamma = value;

    if (_hdrStage)
        _hdrStage->setAccurateGamma(_accurate_gamma);

    glutPostRedisplay();
}

bool Example::GetAccurateGamma() const
{
    return _accurate_gamma;
}

void Example::SetGamma(bool value)
{
    _gamma = value;

    if (_hdrStage)
        _hdrStage->setApplyGamma(_gamma);

    glutPostRedisplay();
}

bool Example::GetGamma() const
{
    return _gamma;
}

void Example::SetUseITURBT709(bool value)
{
    _use_ITU_R_BT_709 = value;

    if (_hdrStage)
        _hdrStage->setUse_ITU_R_BT_709(_use_ITU_R_BT_709);

    glutPostRedisplay();
}

bool Example::GetUseITURBT709() const
{
    return _use_ITU_R_BT_709;
}

void Example::SetMipmapLevel(int value)
{
    _mipmap_level = value;

    if (_hdrStage)
        _hdrStage->setMipmapLevel(_mipmap_level);

    glutPostRedisplay();
}

int Example::GetMipmapLevel() const
{
    return _mipmap_level;
}

void Example::SetBloomThreshold(float value)
{
    _hdrShaderData.bloomThreshold = value;

    if (_hdrStage)
        _hdrStage->setBloomThreshold(_hdrShaderData.bloomThreshold);

    glutPostRedisplay();
}

float Example::GetBloomThreshold() const
{
    return _hdrShaderData.bloomThreshold;
}

void Example::SetBloomMagnitude(float value)
{
    _hdrShaderData.bloomMagnitude = value;

    if (_hdrStage)
        _hdrStage->setBloomMagnitude(_hdrShaderData.bloomMagnitude);

    glutPostRedisplay();
}

float Example::GetBloomMagnitude() const
{
    return _hdrShaderData.bloomMagnitude;
}

void Example::SetToneMapTechnique(int value)
{
    _hdrShaderData.toneMapTechnique = value;

    if (_hdrStage)
        _hdrStage->setToneMappingMode(_hdrShaderData.toneMapTechnique);

    glutPostRedisplay();
}

int Example::GetToneMapTechnique() const
{
    return _hdrShaderData.toneMapTechnique;
}

void Example::SetExposure(float value)
{
    _hdrShaderData.exposure = value;

    if (_hdrStage)
        _hdrStage->setExposure(_hdrShaderData.exposure);

    glutPostRedisplay();
}

float Example::GetExposure() const
{
    return _hdrShaderData.exposure;
}

void Example::SetKeyValue(float value)
{
    _hdrShaderData.keyValue = value;

    if (_hdrStage)
        _hdrStage->setKeyValue(_hdrShaderData.keyValue);

    glutPostRedisplay();
}

float Example::GetKeyValue() const
{
    return _hdrShaderData.keyValue;
}

void Example::SetAutoExposure(int value)
{
    _hdrShaderData.autoExposure = value;

    if (_hdrStage)
        _hdrStage->setAutoExposureMode(_hdrShaderData.autoExposure);

    glutPostRedisplay();
}

int Example::GetAutoExposure() const
{
    return _hdrShaderData.autoExposure;
}

void Example::SetWhiteLevel(float value)
{
    _hdrShaderData.whiteLevel = value;

    if (_hdrStage)
        _hdrStage->setWhiteLevel(_hdrShaderData.whiteLevel);

    glutPostRedisplay();
}

float Example::GetWhiteLevel() const
{
    return _hdrShaderData.whiteLevel;
}

void Example::SetShoulderStrength(float value)
{
    _hdrShaderData.shoulderStrength = value;

    if (_hdrStage)
        _hdrStage->setFilmicShoulderStrenght(_hdrShaderData.shoulderStrength);

    glutPostRedisplay();
}

float Example::GetShoulderStrength() const
{
    return _hdrShaderData.shoulderStrength;
}

void Example::SetLinearStrength(float value)
{
    _hdrShaderData.linearStrength = value;

    if (_hdrStage)
        _hdrStage->setFilmicLinearStrength(_hdrShaderData.linearStrength);

    glutPostRedisplay();
}

float Example::GetLinearStrength() const
{
    return _hdrShaderData.linearStrength;
}

void Example::SetLinearAngle(float value)
{
    _hdrShaderData.linearAngle = value;

    if (_hdrStage)
        _hdrStage->setFilmicLinearAngle(_hdrShaderData.linearAngle);

    glutPostRedisplay();
}

float Example::GetLinearAngle() const
{
    return _hdrShaderData.linearAngle;
}

void Example::SetToeStrength(float value)
{
    _hdrShaderData.toeStrength = value;

    if (_hdrStage)
        _hdrStage->setFilmicToeStrength(_hdrShaderData.toeStrength);

    glutPostRedisplay();
}

float Example::GetToeStrength() const
{
    return _hdrShaderData.toeStrength;
}

void Example::SetToeNumerator(float value)
{
    _hdrShaderData.toeNumerator = value;

    if (_hdrStage)
        _hdrStage->setFilmicToeNumerator(_hdrShaderData.toeNumerator);

    glutPostRedisplay();
}

float Example::GetToeNumerator() const
{
    return _hdrShaderData.toeNumerator;
}

void Example::SetToeDenominator(float value)
{
    _hdrShaderData.toeDenominator = value;

    if (_hdrStage)
        _hdrStage->setFilmicToeDenominator(_hdrShaderData.toeDenominator);

    glutPostRedisplay();
}

float Example::GetToeDenominator() const
{
    return _hdrShaderData.toeDenominator;
}

void Example::SetLinearWhite(float value)
{
    _hdrShaderData.linearWhite =  value;

    if (_hdrStage)
        _hdrStage->setFilmicLinearWhite(_hdrShaderData.linearWhite);

    glutPostRedisplay();
}

float Example::GetLinearWhite() const
{
    return _hdrShaderData.linearWhite;
}

void Example::SetLumSaturation(float value)
{
    _hdrShaderData.lumSaturation = value;

    if (_hdrStage)
        _hdrStage->setSaturation(_hdrShaderData.lumSaturation);

    glutPostRedisplay();
}

float Example::GetLumSaturation() const
{
    return _hdrShaderData.lumSaturation;
}

void Example::SetBias(float value)
{
    _hdrShaderData.bias = value;

    if (_hdrStage)
        _hdrStage->setDragoBias(_hdrShaderData.bias);

    glutPostRedisplay();
}

float Example::GetBias() const
{
    return _hdrShaderData.bias;
}

void Example::SetTau(float value)
{
    _hdrShaderData.tau = value;

    if (_hdrStage)
        _hdrStage->setTau(_hdrShaderData.tau);

    glutPostRedisplay();
}

float Example::GetTau() const
{
    return _hdrShaderData.tau;
}

void Example::SetNTaps(int value)
{
    _hdrShaderData.nTaps = value;

    if (_hdrStage)
        _hdrStage->setNumTaps(_hdrShaderData.nTaps);

    glutPostRedisplay();
}

int Example::GetNTaps() const
{
    return _hdrShaderData.nTaps;
}

void Example::SetSigma(float value)
{
    _hdrShaderData.sigma = value;

    if (_hdrStage)
        _hdrStage->setBlurGaussSigma(_hdrShaderData.sigma);

    glutPostRedisplay();
}

float Example::GetSigma() const
{
    return _hdrShaderData.sigma;
}

void Example::SetUseLinChromInterp(bool value)
{
    _hdrShaderData.useLinChromInterp = value;

    if (_hdrStage)
        _hdrStage->setUseLinChromCorrection(_hdrShaderData.useLinChromInterp);

    glutPostRedisplay();
}

bool Example::GetUseLinChromInterp() const
{
    return _hdrShaderData.useLinChromInterp;
}

void Example::SetCurrentLight(OSG::UInt32 value)
{
    _current_light_index = value;
    HandleShadowParamConstraints();
    glutPostRedisplay();
}

OSG::UInt32 Example::GetCurrentLight() const
{
    return _current_light_index;
}

void Example::SetLightPosition(const OSG::Pnt3f& value)
{
    setLightFramePosition(_current_light_index, value);
    glutPostRedisplay();
}

OSG::Pnt3f Example::GetLightPosition() const
{
    return getLightFramePosition(_current_light_index);
}

void Example::SetLightDirection(const OSG::Vec3f& value)
{
    _multiLightGroup->setDirection(_current_light_index, value);

    update_light_geometry(_multiLightGroup->getLight(_current_light_index));

    glutPostRedisplay();
}

OSG::Vec3f Example::GetLightDirection() const
{
    return _multiLightGroup->getDirection(_current_light_index);
}

void Example::SetLightAmbient(const OSG::Color3f& value)
{
    _multiLightGroup->setAmbient(_current_light_index, value);
    glutPostRedisplay();
}

OSG::Color3f Example::GetLightAmbient() const
{
    return _multiLightGroup->getAmbient(_current_light_index);
}

void Example::SetLightDiffuse(const OSG::Color3f& value)
{
    _multiLightGroup->setDiffuse(_current_light_index, value);
    glutPostRedisplay();
}

OSG::Color3f Example::GetLightDiffuse() const
{
    return _multiLightGroup->getDiffuse(_current_light_index);
}

void Example::SetLightSpecular(const OSG::Color3f& value)
{
    _multiLightGroup->setSpecular(_current_light_index, value);
    glutPostRedisplay();
}

OSG::Color3f Example::GetLightSpecular() const
{
    return _multiLightGroup->getSpecular(_current_light_index);
}

void Example::SetLightAttenuation(const OSG::Vec3f& value)
{
    _multiLightGroup->setAttenuation(_current_light_index, value);
    glutPostRedisplay();
}

OSG::Vec3f Example::GetLightAttenuation() const
{
    return _multiLightGroup->getAttenuation(_current_light_index);
}

void Example::SetLightSpotlightAng(OSG::Real32 value)
{
    _multiLightGroup->setSpotlightAngle(_current_light_index, value);
    glutPostRedisplay();
}

OSG::Real32 Example::GetLightSpotlightAng() const
{
    return _multiLightGroup->getSpotlightAngle(_current_light_index);
}

void Example::SetLightSpotExponent(OSG::Real32 value)
{
    _multiLightGroup->setSpotlightExponent(_current_light_index, value);
    glutPostRedisplay();
}

OSG::Real32 Example::GetLightSpotExponent() const
{
    return _multiLightGroup->getSpotlightExponent(_current_light_index);
}

void Example::SetLightType(int value)
{
    _multiLightGroup->setType(_current_light_index, static_cast<OSG::MultiLight::Type>(value));
    glutPostRedisplay();
}

int Example::GetLightType() const
{
    return static_cast<int>(_multiLightGroup->getType(_current_light_index));
}

void Example::SetLightEnabled(bool value)
{
    _multiLightGroup->setEnabled(_current_light_index, value);
    HandleShadowParamConstraints();
    glutPostRedisplay();
}

bool Example::GetLightEnabled() const
{
    return _multiLightGroup->getEnabled(_current_light_index);
}

void Example::SetLightShadow(bool value)
{
    _multiLightGroup->setShadow(_current_light_index, value);
    HandleShadowParamConstraints();
    glutPostRedisplay();
}

bool Example::GetLightShadow() const
{
    return _multiLightGroup->getShadow(_current_light_index);
}

void Example::SetLightShadowBias(OSG::Real32 value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            pMLShadowParam->setBias(value);
            glutPostRedisplay();
        }
    }
}

OSG::Real32 Example::GetLightShadowBias() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            return pMLShadowParam->getBias();
        }
    }
    return 0.f;
}

void Example::SetLightShadowInt(OSG::Real32 value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            pMLShadowParam->setIntensity(value);
            glutPostRedisplay();
        }
    }
}

OSG::Real32 Example::GetLightShadowInt() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            return pMLShadowParam->getIntensity();
        }
    }
    return 0.f;
}

void Example::SetShadowOn(bool value)
{
    _shadowStage->setShadowOn(value);
    HandleShadowParamConstraints();
    glutPostRedisplay();
}

bool Example::GetShadowOn() const
{
    return _shadowStage->getShadowOn();
}

void Example::SetShadowMode(OSG::Int32 value)
{
    //
    // Remove the current shadow mode features from the light and ...
    //
    OSG::UInt32 requiredShadowFeatures = _shadowStage->getRequiredMultiLightFeatures();
    _multiLightGroup->setFeatures(requiredShadowFeatures, false);

    _shadowStage->setShadowMode(static_cast<OSG::MultiLightShadowStage::Mode>(value));

    //
    // ... establish the new features for the current shadow mode
    //
    requiredShadowFeatures = _shadowStage->getRequiredMultiLightFeatures();
    _multiLightGroup->setFeatures(requiredShadowFeatures, true);

    _materialManager->updateMaterials();

    HandleShadowParamConstraints();

    glutPostRedisplay();
}

OSG::Int32 Example::GetShadowMode() const
{
    return static_cast<OSG::Int32>(_shadowStage->getShadowMode());
}

void Example::SetShadowBias(OSG::Real32 value)
{
    _shadowStage->setOffsetBias(value);
    glutPostRedisplay();
}

OSG::Real32 Example::GetShadowBias() const
{
    return _shadowStage->getOffsetBias();
}

void Example::SetShadowFactor(OSG::Real32 value)
{
    _shadowStage->setOffsetFactor(value);
    glutPostRedisplay();
}

OSG::Real32 Example::GetShadowFactor() const
{
    return _shadowStage->getOffsetFactor();
}

void Example::SetShadowCullFace(bool value)
{
    _shadowStage->setCullFrontFace(value);
    glutPostRedisplay();
}

bool Example::GetShadowCullFace() const
{
    return _shadowStage->getCullFrontFace();
}

void Example::SetShadowMapSize(OSG::UInt32 value)
{
    OSG::UInt32 sz = static_cast<OSG::UInt32>(OSG::osgPow(2.f, static_cast<OSG::Real32>(value)));

    _shadowStage->setShadowMapWidth (sz);
    _shadowStage->setShadowMapHeight(sz);
    glutPostRedisplay();
}

OSG::UInt32 Example::GetShadowMapSize() const
{
    OSG::Real32 value = _shadowStage->getShadowMapWidth();
    OSG::Int32 sz = OSG::osgLog2Int(value);

    return static_cast<OSG::UInt32>(sz);
}

void Example::SetShadowTweakVol(OSG::Real32 value)
{
    _shadowStage->setEnlargeShadowVolumeZ(value);
    glutPostRedisplay();
}

OSG::Real32 Example::GetShadowTweakVol() const
{
    return _shadowStage->getEnlargeShadowVolumeZ();
}

void Example::SetShadowFilterMode(OSG::Int32 value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            pMLShadowParam->setFilterMode(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

OSG::Int32 Example::GetShadowFilterMode() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            return pMLShadowParam->getFilterMode();
        }
    }
    return 0;
}

void Example::SetShadowFilterSize(OSG::Int32 value)
{
    _shadowStage->setFilterDistributionSize(value);
    glutPostRedisplay();
}

OSG::Int32 Example::GetShadowFilterSize() const
{
    return _shadowStage->getFilterDistributionSize();
}

void Example::SetShadowSearchSize(OSG::Int32 value)
{
    _shadowStage->setSearchDistributionSize(value);
    glutPostRedisplay();
}

OSG::Int32 Example::GetShadowSearchSize() const
{
    return _shadowStage->getSearchDistributionSize();
}

void Example::SetShadowFilterRadius(OSG::Real32 value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            pMLShadowParam->setFilterRadius(value);
            glutPostRedisplay();
        }
    }
}

OSG::Real32 Example::GetShadowFilterRadius() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            return pMLShadowParam->getFilterRadius();
        }
    }
    return 0.f;
}

void Example::SetShadowRandomRotate(bool value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            pMLShadowParam->setRandomRotateFilter(value);
            glutPostRedisplay();
        }
    }
}

bool Example::GetShadowRandomRotate() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            return pMLShadowParam->getRandomRotateFilter();
        }
    }
    return false;
}

void Example::SetShadowUseBlockerSearch(bool value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            pMLShadowParam->setUseBlockerSearch(value);
            glutPostRedisplay();
        }
    }
}

bool Example::GetShadowUseBlockerSearch() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            return pMLShadowParam->getUseBlockerSearch();
        }
    }
    return false;
}

void Example::SetShadowUsePCSS(bool value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            pMLShadowParam->setUsePCSS(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

bool Example::GetShadowUsePCSS() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = _shadowStage->getShadowParameter(shadowParamIdx);
        if (pMLShadowParam)
        {
            return pMLShadowParam->getUsePCSS();
        }
    }
    return false;
}

void Example::SetShadowFocusing(bool value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setFocusing(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

bool Example::GetShadowFocusing() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getFocusing();
        }
    }
    return false;
}

void Example::SetShadowUseLiSP(bool value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setUseLiSP(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

bool Example::GetShadowUseLiSP() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getUseLiSP();
        }
    }
    return false;
}

void Example::SetShadowLiSPMode(OSG::Int32 value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setLiSPMode(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

OSG::Int32 Example::GetShadowLiSPMode() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getLiSPMode();
        }
    }
    return false;
}

void Example::SetShadowNbrOfSplits(OSG::Int32 value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setNumberOfSplits(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

OSG::Int32 Example::GetShadowNbrOfSplits() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getNumberOfSplits();
        }
    }
    return false;
}

void Example::SetShadowUseGeomShader(bool value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setUseGeometryShader(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

bool Example::GetShadowUseGeomShader() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getUseGeometryShader();
        }
    }
    return false;
}

void Example::SetShadowReduceSwimming(bool value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setReduceSwimming(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

bool Example::GetShadowReduceSwimming() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getReduceSwimming();
        }
    }
    return false;
}

void Example::SetShadowLightSpaceAlign(bool value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setLightSpaceAlignment(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

bool Example::GetShadowLightSpaceAlign() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getLightSpaceAlignment();
        }
    }
    return false;
}

void Example::SetShadowUseMinDepth(bool value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setUseMinDepth(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

bool Example::GetShadowUseMinDepth() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getUseMinDepth();
        }
    }
    return false;
}

void Example::SetShadowUseBestResolSel(bool value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setUseBestResSelection(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

bool Example::GetShadowUseBestResolSel() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getUseBestResSelection();
        }
    }
    return false;
}

void Example::SetShadowWarpParameter(OSG::Real32 value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            OSG::Real32 warpParam = OSG::osgExp(value / 100 * 0.18);
            if (value < std::numeric_limits<float>::infinity())
                pMLShadowParam->setWarpingParameter(warpParam);
            else 
                pMLShadowParam->setWarpingParameter(std::numeric_limits<float>::infinity());

            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

OSG::Real32 Example::GetShadowWarpParameter() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            OSG::Real32 value;
            OSG::Real32 warpParam = pMLShadowParam->getWarpingParameter();
            if (warpParam == std::numeric_limits<float>::infinity())
            {
                value = 6000;
            }
            else
            {
                value = OSG::osgLog(warpParam) * 100 / 0.18;
            }

            return pMLShadowParam->getWarpingParameter();
        }
    }
    return false;
}

void Example::SetShadowSplitParameter(OSG::Real32 value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setSplitParamterLambda(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

OSG::Real32 Example::GetShadowSplitParameter() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getSplitParamterLambda();
        }
    }
    return false;
}

void Example::SetShadowZNear(OSG::Real32 value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setZNear(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

OSG::Real32 Example::GetShadowZNear() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getZNear();
        }
    }
    return false;
}

void Example::SetShadowPseudoNear(OSG::Real32 value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setPseudoNear(value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

OSG::Real32 Example::GetShadowPseudoNear() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return pMLShadowParam->getPseudoNear();
        }
    }
    return false;
}

void Example::SetShadowPseudoFar(OSG::Real32 value)
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            pMLShadowParam->setPseudoFar(1.f - value);
            HandleShadowParamConstraints();
            glutPostRedisplay();
        }
    }
}

OSG::Real32 Example::GetShadowPseudoFar() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameterAdvanced* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParam)
        {
            return 1.f - pMLShadowParam->getPseudoFar();
        }
    }
    return false;
}

void Example::SetShadowUseHwPCF(bool value)
{
    _shadowStage->setUseHWPCF(value);
    glutPostRedisplay();
}

bool Example::GetShadowUseHwPCF() const
{
    return _shadowStage->getUseHWPCF();
}

void Example::SetShadowArbTest(bool value)
{
    _shadowStage->setArbTest(value);
    glutPostRedisplay();
}

bool Example::GetShadowArbTest() const
{
    return _shadowStage->getArbTest();
}

void Example::HandleShadowParamConstraints() const
{
    OSG::UInt32 shadowParamIdx = _multiLightGroup->getShadowParameterIndex(_current_light_index);
    if (shadowParamIdx != -1 && shadowParamIdx < _shadowStage->getNumShadowParameters())
    {
        OSG::MultiLightShadowParameter* pMLShadowParam = 
            dynamic_cast<OSG::MultiLightShadowParameter*>(
                _shadowStage->getShadowParameter(shadowParamIdx));
        if (pMLShadowParam)
        {
            OSG::Int32 filterMode = pMLShadowParam->getFilterMode();

            switch (filterMode)
            {
                case OSG::MultiLightShadowStage::PCF_MODE_DISABLED:
                    TwDefine("TweakBar/'Filter Radius'    visible=false");
                    TwDefine("TweakBar/'Random Rotate'    visible=false");
                    TwDefine("TweakBar/'Blocker Search'   visible=false");
                    TwDefine("TweakBar/'Use PCSS'         visible=false");
                    break;
                case OSG::MultiLightShadowStage::PCF_MODE_SIMPLE:
                case OSG::MultiLightShadowStage::PCF_MODE_BOX:
                case OSG::MultiLightShadowStage::PCF_MODE_POISSON:
                    TwDefine("TweakBar/'Filter Radius'    visible=true");
                    TwDefine("TweakBar/'Random Rotate'    visible=true");
                    TwDefine("TweakBar/'Blocker Search'   visible=true");
                    TwDefine("TweakBar/'Use PCSS'         visible=true");
            }
        }

        OSG::MultiLightShadowParameterAdvanced* pMLShadowParamAdv = 
            dynamic_cast<OSG::MultiLightShadowParameterAdvanced*>(
                _shadowStage->getShadowParameter(shadowParamIdx));

        if (pMLShadowParamAdv)
        {
            bool hasSplitting   = pMLShadowParamAdv->getNumberOfSplits() > 1;
            bool hasFocusing    = pMLShadowParamAdv->getFocusing();
            bool hasLiSP        = pMLShadowParamAdv->getUseLiSP();
            OSG::Int32 lispMode = pMLShadowParamAdv->getLiSPMode();

            if (hasLiSP)
            {
                TwDefine("TweakBar/'Focusing'           visible=false");
                TwDefine("TweakBar/'Reduce Swimming'    visible=false");
                TwDefine("TweakBar/'Light Space Align'  visible=false");

                TwDefine("TweakBar/'LiSP Mode'          visible=true");

                TwDefine("TweakBar/'Use Min Depth'      visible=true");

                switch (lispMode)
                {
                    case OSG::LiSPSMTechnique::NOPT:
                        TwDefine("TweakBar/'Pseudo Near'        visible=true");
                        TwDefine("TweakBar/'Pseudo Far'         visible=true");
                        TwDefine("TweakBar/'Warping Parameter'  visible=false");
                        break;
                    case OSG::LiSPSMTechnique::REPARAMETRIZED:
                        TwDefine("TweakBar/'Pseudo Near'        visible=false");
                        TwDefine("TweakBar/'Pseudo Far'         visible=false");
                        TwDefine("TweakBar/'Warping Parameter'  visible=false");
                        break;
                    case OSG::LiSPSMTechnique::ARBITRARY:
                        TwDefine("TweakBar/'Pseudo Near'        visible=false");
                        TwDefine("TweakBar/'Pseudo Far'         visible=false");
                        TwDefine("TweakBar/'Warping Parameter'  visible=true");
                        break;
                }
            }
            else
            {
                TwDefine("TweakBar/'Focusing'           visible=true");
                if (hasFocusing)
                {
                    TwDefine("TweakBar/'Reduce Swimming'    visible=true");
                    TwDefine("TweakBar/'Light Space Align'  visible=true");
                    TwDefine("TweakBar/'Use Min Depth'      visible=true");
                }
                else
                {
                    TwDefine("TweakBar/'Reduce Swimming'    visible=false");
                    TwDefine("TweakBar/'Light Space Align'  visible=false");
                    TwDefine("TweakBar/'Use Min Depth'      visible=false");
                }

                TwDefine("TweakBar/'LiSP Mode'          visible=false");
                TwDefine("TweakBar/'Warping Parameter'  visible=false");

                if (!hasSplitting)
                {
                    TwDefine("TweakBar/'Pseudo Near'        visible=false");
                    TwDefine("TweakBar/'Pseudo Far'         visible=false");
                }
            }

            if (hasSplitting)
            {
                TwDefine("TweakBar/'Focusing'           visible=false");

                TwDefine("TweakBar/'Pseudo Near'        visible=true");
                TwDefine("TweakBar/'Pseudo Far'         visible=true");

                TwDefine("TweakBar/'Use Geom Shader'    visible=true");
                TwDefine("TweakBar/'Use Best Resol'     visible=true");
                TwDefine("TweakBar/'Split Parameter'    visible=true");
            }
            else
            {
                TwDefine("TweakBar/'Use Geom Shader'    visible=false");
                TwDefine("TweakBar/'Use Best Resol'     visible=false");
                TwDefine("TweakBar/'Split Parameter'    visible=false");
            }
        }
    }

    if (_shadowStage->getShadowOn())
    {
        TwDefine("TweakBar/'Shadow Mode'        visible=true");
        TwDefine("TweakBar/'Shadow Caster'      visible=true");

        if (_multiLightGroup->getShadow(_current_light_index) && _multiLightGroup->getEnabled(_current_light_index))
        {
            switch (_shadowStage->getShadowMode())
            {
                case OSG::MultiLightShadowStage::NO_SHADOW_MAP:
                    TwDefine("TweakBar/'Shadow Parameter'   visible=false");
                    TwDefine("TweakBar/'Advanced Parameter' visible=false");
                    break;
                case OSG::MultiLightShadowStage::SIMPLE_SHADOW_MAP:
                    TwDefine("TweakBar/'Shadow Parameter'   visible=true");
                    TwDefine("TweakBar/'Advanced Parameter' visible=false");
                    break;
                case OSG::MultiLightShadowStage::ADVANCED_SHADOW_MAP:
                    TwDefine("TweakBar/'Shadow Parameter'   visible=true");
                    TwDefine("TweakBar/'Advanced Parameter' visible=true");
                    break;
                case OSG::MultiLightShadowStage::SIMPLE_TEST_SHADOW_MAP:
                    TwDefine("TweakBar/'Shadow Parameter'   visible=true");
                    TwDefine("TweakBar/'Advanced Parameter' visible=false");
            }
        }
        else
        {
            TwDefine("TweakBar/'Shadow Parameter'   visible=false");
            TwDefine("TweakBar/'Advanced Parameter' visible=false");
        }
    }
    else
    {
        TwDefine("TweakBar/'Shadow Mode'        visible=false");
        TwDefine("TweakBar/'Shadow Caster'      visible=false");
        TwDefine("TweakBar/'Shadow Parameter'   visible=false");
        TwDefine("TweakBar/'Advanced Parameter' visible=false");
    }
}

void Example::setupTweakBar()
{
    if (_tweakbar) return;

    _tweakbar = TwNewBar("TweakBar");

    TwDefine(" GLOBAL help='This example is about multi light shadows in OpenSG.' ");
    TwDefine(" TweakBar size='350 700' color='96 216 224' valueswidth=170");

    //
    // Global group
    //
    
    TwAddVarRW(_tweakbar, "Pause Animation", TW_TYPE_BOOLCPP, &_pause,  "key=SPACE help='Pause animation'");
    TwAddVarCB(_tweakbar, "Carry Depth",     TW_TYPE_BOOLCPP, SetCarryDepthCB, GetCarryDepthCB, this,  "help='Carry depth buffer to final render target'");
    TwAddVarCB(_tweakbar, "HDR",             TW_TYPE_BOOLCPP, SetUseHDRCB, GetUseHDRCB, this,  "help='Enable disable the HDR stage'");
    TwAddButton(_tweakbar, "Reset HDR Parameters", ResetParametersCB, this, "key=r     help='Reset all  parameters back to default values'");
    //
    // Group 'Luminance Adaption'
    //
    TwAddVarCB(_tweakbar, "Adjust Luminance", TW_TYPE_BOOLCPP, SetAjustLuminanceCB, GetAjustLuminanceCB, this,  "help='Toggle Luminance time dependent adjustment.' group='Luminance Adaption'");
    TwAddVarCB(_tweakbar, "Tau",              TW_TYPE_FLOAT,   SetTauCB, GetTauCB, this, sGenTwDefinition(_hdrShaderDataMin.tau, _hdrShaderDataMax.tau, 100, 2, "a", "A", "Luminance (eye) adaption time parameter.", "'Luminance Adaption'").c_str());

    //
    // Group 'Gamma Correction'
    //
    TwAddVarCB(_tweakbar, "Gamma",        TW_TYPE_BOOLCPP, SetGammaCB, GetGammaCB, this,          "key=g help='Apply Gamma correction at the end of the pipeline.' group='Gamma Correction'");
    TwAddVarCB(_tweakbar, "Accurate",     TW_TYPE_BOOLCPP, SetAccurateGammaCB, GetAccurateGammaCB, this, "key=G help='Use accurate Gamma to linear mapping.' group='Gamma Correction'");

    //
    // Group 'Bloom'
    //
    TwAddVarCB(_tweakbar, "Bloom Pass",      TW_TYPE_BOOLCPP, SetPerformBloomCB,    GetPerformBloomCB,    this, "help='Perform Bloom pass.' group=Bloom");
    TwAddVarCB(_tweakbar, "Bloom Background",TW_TYPE_BOOLCPP, SetBloomBackgroundCB, GetBloomBackgroundCB, this, "help='Perform Bloom pass.' group=Bloom");
    TwAddVarCB(_tweakbar, "Threshold",       TW_TYPE_FLOAT,   SetBloomThresholdCB,  GetBloomThresholdCB,  this, sGenTwDefinition(_hdrShaderDataMin.bloomThreshold, _hdrShaderDataMax.bloomThreshold, 100, 2, "t", "T", "Used by function CalcExposedColor of the Threshold shader: exposure -= bloomThreshold", "Bloom").c_str());
    TwAddVarCB(_tweakbar, "Magnitude",       TW_TYPE_FLOAT,   SetBloomMagnitudeCB,  GetBloomMagnitudeCB,  this, sGenTwDefinition(_hdrShaderDataMin.bloomMagnitude, _hdrShaderDataMax.bloomMagnitude, 100, 2, "u", "U", "Used by function main of the Composite shader: bloom *= bloomMagnitude", "Bloom").c_str());
    TwAddVarCB(_tweakbar, "Taps",            TW_TYPE_INT32,   SetNTapsCB,           GetNTapsCB,           this, sGenTwDefinition(_hdrShaderDataMin.nTaps, _hdrShaderDataMax.nTaps, 1, "p", "P", "Number if tap iterations used in the Bloom Blur shader.", "Bloom").c_str());
    TwAddVarCB(_tweakbar, "Sigma",           TW_TYPE_FLOAT,   SetSigmaCB,           GetSigmaCB,           this, sGenTwDefinition(_hdrShaderDataMin.sigma, _hdrShaderDataMax.sigma, 100, 2, "f", "F", "Used by function CalcGaussianWeight of the Blur shader.", "Bloom").c_str());

    //
    // Group 'Tonemapping'
    //
    TwAddVarCB(_tweakbar, "Luminance ITU-R-BT.709", TW_TYPE_BOOLCPP, SetUseITURBT709CB, GetUseITURBT709CB, this, "help='Calculate relative luminance according to ITU-R-BT.709.' group=Tonemapping");
    TwAddVarCB(_tweakbar, "Mipmap Level",           TW_TYPE_INT32,   SetMipmapLevelCB,  GetMipmapLevelCB,  this, sGenTwDefinition(-1, 12, 1, "z", "Z", "The Mipmap Level addresses the texture to be used for avg. luminance lookup. See Exposure render texture. Default is -1.", "Tonemapping").c_str());

    TwEnumVal toneMappingEnums[] = { {0, "None"}, {1, "Logarithmic"}, {2, "Exponential"}, {3, "Drago Logarithmic"}, {4, "Reinhard"}, {5, "Reinhard Modified"}, {6, "Filmic Hable"}, {7, "Filmic Uncharted2"} };
    TwType toneMappingType = TwDefineEnum("ToneMappingType", toneMappingEnums, 8);
    TwAddVarCB(_tweakbar, "Technique", toneMappingType, SetToneMapTechniqueCB, GetToneMapTechniqueCB, this, "help='The tone mapping algorithm.' group=Tonemapping");

    TwEnumVal autoExposureEnums[] = { {0, "Manual"}, {1, "Geom. mean of lumi. (KeyValue)"}, {2, "Geom. mean of lumi. (Auto KeyValue)"} };
    TwType autoExposureType = TwDefineEnum("AutoExposureType", autoExposureEnums, 3);
    TwAddVarCB(_tweakbar, "AutoExposure", autoExposureType, SetAutoExposureCB, GetAutoExposureCB, this, "help='Algorithm to determine the exposure value.' group=Tonemapping");

    TwAddVarCB(_tweakbar, "Exposure",           TW_TYPE_FLOAT,   SetExposureCB, GetExposureCB, this,      sGenTwDefinition(_hdrShaderDataMin.exposure,      _hdrShaderDataMax.exposure,      100, 2, "e", "E", "Manual exposure: The HDR pixel value is then scaled by 2^exposure.", "Tonemapping").c_str());
    TwAddVarCB(_tweakbar, "KeyValue",           TW_TYPE_FLOAT,   SetKeyValueCB, GetKeyValueCB, this,      sGenTwDefinition(_hdrShaderDataMin.keyValue,      _hdrShaderDataMax.keyValue,      100, 2, "k", "K", "Used in the geometric mean calculation of the luminance. a \"key value\" is user-controlled, and is meant to be chosen based on whether the scene is \"high-key\" (bright, low contrast) or \"low-key\" (dark, high contrast).", "Tonemapping").c_str());
    TwAddVarCB(_tweakbar, "White Level",        TW_TYPE_FLOAT,   SetWhiteLevelCB, GetWhiteLevelCB, this,    sGenTwDefinition(_hdrShaderDataMin.whiteLevel,    _hdrShaderDataMax.whiteLevel,  10000, 4, "w", "W", "Sets what pixels are pure white in the image, producing a result similar to how exposure functions in a camera.", "Tonemapping").c_str());
    TwAddVarCB(_tweakbar, "Saturation",         TW_TYPE_FLOAT,   SetLumSaturationCB, GetLumSaturationCB, this, sGenTwDefinition(_hdrShaderDataMin.lumSaturation, _hdrShaderDataMax.lumSaturation, 100, 2, "l", "L", "Luminance saturation.", "Tonemapping").c_str());
    TwAddVarCB(_tweakbar, "Linear Sat Interp.", TW_TYPE_BOOLCPP, SetUseLinChromInterpCB, GetUseLinChromInterpCB, this, "help='Perform linear interpolation on color correction.' group=Tonemapping");

    TwAddVarCB(_tweakbar, "Shoulder Strength",  TW_TYPE_FLOAT, SetShoulderStrengthCB, GetShoulderStrengthCB, this, sGenTwDefinition(_hdrShaderDataMin.shoulderStrength, _hdrShaderDataMax.shoulderStrength, 100, 2, "y", "Y", "Shoulder strength used in Uncharted2 Filmic Tonemapping.", "'Filmic Uncharted2'").c_str());
    TwAddVarCB(_tweakbar, "Linear Strength",    TW_TYPE_FLOAT, SetLinearStrengthCB, GetLinearStrengthCB, this,   sGenTwDefinition(_hdrShaderDataMin.linearStrength,   _hdrShaderDataMax.linearStrength,   100, 2, "x", "X", "Linear strength used in Uncharted2 Filmic Tonemapping.", "'Filmic Uncharted2'").c_str());
    TwAddVarCB(_tweakbar, "Linear Angle",       TW_TYPE_FLOAT, SetLinearAngleCB, GetLinearAngleCB, this,      sGenTwDefinition(_hdrShaderDataMin.linearAngle,      _hdrShaderDataMax.linearAngle,      100, 2, "c", "C", "Linear angle used in Uncharted2 Filmic Tonemapping.", "'Filmic Uncharted2'").c_str());
    TwAddVarCB(_tweakbar, "Toe Strength",       TW_TYPE_FLOAT, SetToeStrengthCB, GetToeStrengthCB, this,      sGenTwDefinition(_hdrShaderDataMin.toeStrength,      _hdrShaderDataMax.toeStrength,      100, 2, "v", "V", "Toe strength used in Uncharted2 Filmic Tonemapping.", "'Filmic Uncharted2'").c_str());
    TwAddVarCB(_tweakbar, "Toe Numerator",      TW_TYPE_FLOAT, SetToeNumeratorCB, GetToeNumeratorCB, this,     sGenTwDefinition(_hdrShaderDataMin.toeNumerator,     _hdrShaderDataMax.toeNumerator,     100, 2, "b", "B", "Toe numerator used in Uncharted2 Filmic Tonemapping.", "'Filmic Uncharted2'").c_str());
    TwAddVarCB(_tweakbar, "Toe Denominator",    TW_TYPE_FLOAT, SetToeDenominatorCB, GetToeDenominatorCB, this,   sGenTwDefinition(_hdrShaderDataMin.toeDenominator,   _hdrShaderDataMax.toeDenominator,   100, 2, "n", "N", "Toe denominator used in Uncharted2 Filmic Tonemapping.", "'Filmic Uncharted2'").c_str());
    TwAddVarCB(_tweakbar, "Linear White",       TW_TYPE_FLOAT, SetLinearWhiteCB, GetLinearWhiteCB, this,      sGenTwDefinition(_hdrShaderDataMin.linearWhite,      _hdrShaderDataMax.linearWhite,     1000, 2, "d", "D", "Linear white used in Uncharted2 Filmic Tonemapping.", "'Filmic Uncharted2'").c_str());

    TwAddVarCB(_tweakbar, "Bias", TW_TYPE_FLOAT, SetBiasCB, GetBiasCB, this, sGenTwDefinition(_hdrShaderDataMin.bias, _hdrShaderDataMax.bias, 100, 2, "i", "I", "Bias parameter of the Drago Logarithmic Tonemapping.", "'Drago Logarithmic'").c_str());

    TwDefine("TweakBar/'Filmic Uncharted2'   group=Tonemapping");
    TwDefine("TweakBar/'Drago Logarithmic'   group=Tonemapping");

    //
    // Group 'Environment'
    //
    TwAddVarCB(_tweakbar, "Sample Number",    TW_TYPE_INT32,   SetSampleNumberCB, GetSampleNumberCB, this, "help='Multisampling buffer sample number step=4' group=Environment");
    TwAddVarCB(_tweakbar, "Background Color", TW_TYPE_COLOR3F, SetClearColorCB,   GetClearColorCB,   this, "help='Background color used for rendering' group=Environment");
    TwAddVarCB(_tweakbar, "Force Background", TW_TYPE_BOOLCPP, SetForceBgndCB,    GetForceBgndCB,    this, "help='Force the background as defined by the user, i.e. do not allow tonemapping of the background.' group=Environment");

    std::vector<TwEnumVal> skyBoxeEnums;
    TwEnumVal val;

    val.Value = 0; val.Label = "No SkyBox";             skyBoxeEnums.push_back(val);
    val.Value = 1; val.Label = "Coit Tower";            skyBoxeEnums.push_back(val);
    val.Value = 2; val.Label = "Gamla Stan";            skyBoxeEnums.push_back(val);
    val.Value = 3; val.Label = "Niagara Falls";         skyBoxeEnums.push_back(val);
    val.Value = 4; val.Label = "Saint Lazarus Church";  skyBoxeEnums.push_back(val);
    val.Value = 5; val.Label = "San Francisco";         skyBoxeEnums.push_back(val);
    val.Value = 6; val.Label = "Newport Loft";          skyBoxeEnums.push_back(val);
    val.Value = 7; val.Label = "Mountain Orange";       skyBoxeEnums.push_back(val);

    TwType skyBoxType = TwDefineEnum("SkyBoxType", &skyBoxeEnums[0], static_cast<unsigned int>(skyBoxeEnums.size()));
    TwAddVarCB(_tweakbar, "SkyBox", skyBoxType, SetSkyBgndIndexCB, GetSkyBgndIndexCB, this, "help='Available sky boxes' group=Environment");

    TwEnumVal renderTextureEnums[] = { 
        { OSG::HDR2Stage::SCENE_TEXTURE,             "Non Post Processed Scene"}, 
        { OSG::HDR2Stage::LUMINANCE_TEXTURE,         "Luminance Map (No exp)"}, 
        { OSG::HDR2Stage::ADAPTED_LUMINANCE_TEXTURE, "Avaraged Luminance Map (exp)"},
        { OSG::HDR2Stage::THRESHOLD_TEXTURE,         "Threshold Map"},
        { OSG::HDR2Stage::BLURRED_TEXTURE,           "Bloom Blurred Map"},
        { OSG::HDR2Stage::COMPOSITE_TEXTURE,         "Composite"}, 
        { OSG::HDR2Stage::EXPOSURE_TEXTURE,          "Exposure Map"},
        { OSG::HDR2Stage::DEPTH_TEXTURE,             "Depth Map"}, 
        { OSG::HDR2Stage::LINEARIZED_DEPTH_TEXTURE,  "Linearized Depth Map"},
        { OSG::HDR2Stage::DOWN_SCALED_0,             "Down Scale 0 Map"},
        { OSG::HDR2Stage::DOWN_SCALED_1,             "Down Scale 1 Map"},
        { OSG::HDR2Stage::DOWN_SCALED_2,             "Down Scale 2 Map"},
        { OSG::HDR2Stage::BLUR_TEXTURE,              "BLUR Map"},
        { OSG::HDR2Stage::UPSCALED_SCALED_0,         "Up Scale 0 MapDepth Map"},
        { OSG::HDR2Stage::UPSCALED_SCALED_1,         "Up Scale 1 Map"},
    };
    TwType renderTextureType = TwDefineEnum("RenderTextureType", renderTextureEnums, 15);//9);
    TwAddVarCB(_tweakbar, "Render Texture", renderTextureType, SetResultIndexCB, GetResultIndexCB, this, "help='The texture that is finally drawn' group=Environment");

    //
    // Group 'Light'
    //
    TwAddVarCB(_tweakbar, "Emissive",   TW_TYPE_BOOLCPP, SetRenderEmissiveCB, GetRenderEmissiveCB, this, "help='Render emessive contribution.' group=Light");
    TwAddVarCB(_tweakbar, "Ambient",    TW_TYPE_BOOLCPP, SetRenderAmbientCB,  GetRenderAmbientCB,  this, "help='Render ambient contribution.'  group=Light");
    TwAddVarCB(_tweakbar, "Diffuse",    TW_TYPE_BOOLCPP, SetRenderDiffuseCB,  GetRenderDiffuseCB,  this, "help='Render diffuse contribution.'  group=Light");
    TwAddVarCB(_tweakbar, "Specular",   TW_TYPE_BOOLCPP, SetRenderSpecularCB, GetRenderSpecularCB, this, "help='Render specular contribution.' group=Light");

    TwEnumVal lightTypeEnums[] = {
        { OSG::MultiLight::DIRECTIONAL_LIGHT, "Directional Light"},
        { OSG::MultiLight::POINT_LIGHT,       "Point Light"},
        { OSG::MultiLight::SPOT_LIGHT,        "Spot Light"}
    };

    TwType lightType = TwDefineEnum("LightType", lightTypeEnums, 3);

    TwAddVarCB(_tweakbar, "Current Light",      TW_TYPE_INT32,   SetCurrentLightCB,     GetCurrentLightCB,      this, sGenTwDefinition(0, 3, 1, "TAB", "SHIFT+TAB", "Current light parameters.", "Light").c_str());
    TwAddVarCB(_tweakbar, "Position",           TW_TYPE_DIR3F,   SetLightPositionCB,    GetLightPositionCB,     this, "group=Light");
    TwAddVarCB(_tweakbar, "Spot Direction",     TW_TYPE_DIR3F,   SetLightDirectionCB,   GetLightDirectionCB,    this, "group=Light");
    TwAddVarCB(_tweakbar, "Ambient  Intensity", TW_TYPE_COLOR3F, SetLightAmbientCB,     GetLightAmbientCB,      this, "group=Light");
    TwAddVarCB(_tweakbar, "Diffuse  Intensity", TW_TYPE_COLOR3F, SetLightDiffuseCB,     GetLightDiffuseCB,      this, "group=Light");
    TwAddVarCB(_tweakbar, "Specular Intensity", TW_TYPE_COLOR3F, SetLightSpecularCB,    GetLightSpecularCB,     this, "group=Light");
    TwAddVarCB(_tweakbar, "Attenuation",        TW_TYPE_DIR3F,   SetLightAttenuationCB, GetLightAttenuationCB,  this, "group=Light");
    TwAddVarCB(_tweakbar, "Spot Cut Off",       TW_TYPE_FLOAT,   SetLightSpotlightAngCB,GetLightSpotlightAngCB, this, "min=0 max=90 step=0.1 precision=1 group=Light");
    TwAddVarCB(_tweakbar, "Spot Exponent",      TW_TYPE_FLOAT,   SetLightSpotExponentCB,GetLightSpotExponentCB, this, "min=0 max=1000 step=0.1 precision=1 group=Light");
    TwAddVarCB(_tweakbar, "Type",               lightType,       SetLightTypeCB,        GetLightTypeCB,         this, "group=Light");
    TwAddVarCB(_tweakbar, "Enabled",            TW_TYPE_BOOLCPP, SetLightEnabledCB,     GetLightEnabledCB,      this, "group=Light");
    TwAddVarCB(_tweakbar, "Shadow Caster",      TW_TYPE_BOOLCPP, SetLightShadowCB,      GetLightShadowCB,       this, "group=Light");
    //
    // Group 'Shadow'
    //
    TwEnumVal shadowModeEnums[] = {
        { OSG::MultiLightShadowStage::NO_SHADOW_MAP,          "No Shadow"      },
        { OSG::MultiLightShadowStage::SIMPLE_SHADOW_MAP,      "Simple Shadow"  },
        { OSG::MultiLightShadowStage::ADVANCED_SHADOW_MAP,    "Advanced Shadow"},
        { OSG::MultiLightShadowStage::SIMPLE_TEST_SHADOW_MAP, "Simplest Shadow"}
    };

    TwType shadowMode = TwDefineEnum("ShadowMode", shadowModeEnums, 4);

    TwEnumVal filterKernelSizeEnums[] = {
        { 1, "Box  4x4  / Poisson  16"},
        { 2, "Box  6x6  / Poisson  25"},
        { 3, "Box  8x8  / Poisson  32"},
        { 4, "Box 10x10 / Poisson  64"},
        { 5, "Box 12x12 / Poisson 100"},
        { 6, "Box 14x14 / Poisson 128"},
        { 7, "Box 16x16 / Poisson 256"}
    };

    TwEnumVal searchKernelSizeEnums[] = {
        { 0, "Box  2x2  / Poisson   9"},
        { 1, "Box  4x4  / Poisson  16"},
        { 2, "Box  6x6  / Poisson  25"},
        { 3, "Box  8x8  / Poisson  32"},
        { 4, "Box 10x10 / Poisson  64"},
        { 5, "Box 12x12 / Poisson 100"},
        { 6, "Box 14x14 / Poisson 128"},
    };

    TwType filterKernelSize = TwDefineEnum("FilterSize", filterKernelSizeEnums, 7);
    TwType searchKernelSize = TwDefineEnum("SearchSize", searchKernelSizeEnums, 7);

    TwAddVarCB(_tweakbar, "Shadowing",          TW_TYPE_BOOLCPP,  SetShadowOnCB,         GetShadowOnCB,         this, "group=Shadow");
    TwAddVarCB(_tweakbar, "Shadow Mode",        shadowMode,       SetShadowModeCB,       GetShadowModeCB,       this, "group=Shadow");
    TwAddVarCB(_tweakbar, "Filter Kernel Size", filterKernelSize, SetShadowFilterSizeCB, GetShadowFilterSizeCB, this, "group=Shadow");
    TwAddVarCB(_tweakbar, "Search Kernel Size", searchKernelSize, SetShadowSearchSizeCB, GetShadowSearchSizeCB, this, "group=Shadow");
    TwAddVarCB(_tweakbar, "Render Splitting",   TW_TYPE_BOOLCPP,  SetRenderSplittingCB,  GetRenderSplittingCB,  this, "help='Render splitting frustum.' group=Shadow");

    TwAddVarCB(_tweakbar, "Use hardware PCF",   TW_TYPE_BOOLCPP,  SetShadowUseHwPCFCB,  GetShadowUseHwPCFCB, this, "group=Shadow");
    TwAddVarCB(_tweakbar, "Arb Test",           TW_TYPE_BOOLCPP,  SetShadowArbTestCB,   GetShadowArbTestCB,  this, "group=Shadow");

    TwEnumVal shadowFilterModeEnums[] = {
        { OSG::MultiLightShadowStage::PCF_MODE_DISABLED,  "Disabled"},
        { OSG::MultiLightShadowStage::PCF_MODE_SIMPLE,    "Simple"},
        { OSG::MultiLightShadowStage::PCF_MODE_BOX,       "Box"},
        { OSG::MultiLightShadowStage::PCF_MODE_POISSON,   "Poisson"}
    };

    TwType shadowFilterMode = TwDefineEnum("ShadowFilterMode", shadowFilterModeEnums, 4);

    TwAddVarCB(_tweakbar, "Shadow Bias",      TW_TYPE_FLOAT,   SetLightShadowBiasCB,        GetLightShadowBiasCB,       this, "min=0 max=10.0 step=0.01 precision=2 group='Shadow Parameter'");
    TwAddVarCB(_tweakbar, "Shadow Intensity", TW_TYPE_FLOAT,   SetLightShadowIntCB,         GetLightShadowIntCB,        this, "min=0 max=1.0 step=0.01 precision=2 group='Shadow Parameter'");
    TwAddVarCB(_tweakbar, "Offset Bias",      TW_TYPE_FLOAT,   SetShadowBiasCB,             GetShadowBiasCB,            this, "min=0.0 max=100.0 step=0.1 precision=1 group='Shadow Parameter'");
    TwAddVarCB(_tweakbar, "Offset Factor",    TW_TYPE_FLOAT,   SetShadowFactorCB,           GetShadowFactorCB,          this, "min=0.0 max=100.0 step=0.1 precision=1 group='Shadow Parameter'");
    TwAddVarCB(_tweakbar, "Cull Front Face",  TW_TYPE_BOOLCPP, SetShadowCullFaceCB,         GetShadowCullFaceCB,        this, "group='Shadow Parameter'");
    TwAddVarCB(_tweakbar, "Map Size",         TW_TYPE_INT32,   SetShadowMapSizeCB,          GetShadowMapSizeCB,         this, "min=5 max=12 step=1 group='Shadow Parameter'");
    TwAddVarCB(_tweakbar, "Tweak Volume",     TW_TYPE_FLOAT,   SetShadowTweakVolCB,         GetShadowTweakVolCB,        this, "min=0.01 max=10.0 step=0.01 precision=2 group='Shadow Parameter'");
    TwAddVarCB(_tweakbar, "Filter Mode",      shadowFilterMode,SetShadowFilterModeCB,       GetShadowFilterModeCB,      this, "group='Shadow Parameter'");
    TwAddVarCB(_tweakbar, "Filter Radius",    TW_TYPE_FLOAT,   SetShadowFilterRadiusCB,     GetShadowFilterRadiusCB,    this, "min=0.0 max=100.0 step=0.001 precision=4 group='Shadow Parameter'");
    TwAddVarCB(_tweakbar, "Random Rotate",    TW_TYPE_BOOLCPP, SetShadowRandomRotateCB,     GetShadowRandomRotateCB,    this, "group='Shadow Parameter'");
    TwAddVarCB(_tweakbar, "Blocker Search",   TW_TYPE_BOOLCPP, SetShadowUseBlockerSearchCB, GetShadowUseBlockerSearchCB,this, "group='Shadow Parameter'");
    TwAddVarCB(_tweakbar, "Use PCSS",         TW_TYPE_BOOLCPP, SetShadowUsePCSSCB,          GetShadowUsePCSSCB,         this, "group='Shadow Parameter'");

    TwEnumVal lispModeEnums[] = {
        { OSG::LiSPSMTechnique::NOPT,           "NOPT"},
        { OSG::LiSPSMTechnique::REPARAMETRIZED, "REPARAMETRIZED"},
        { OSG::LiSPSMTechnique::ARBITRARY,      "ARBITRARY"},
        { OSG::LiSPSMTechnique::PSEUDO_NEAR,    "PSEUDO_NEAR"}
    };

    TwType lispMode = TwDefineEnum("LiSP Mode", lispModeEnums, 3);

    TwAddVarCB(_tweakbar, "Focusing",         TW_TYPE_BOOLCPP, SetShadowFocusingCB,         GetShadowFocusingCB,        this, "group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "Use LiSP",         TW_TYPE_BOOLCPP, SetShadowUseLiSPCB,          GetShadowUseLiSPCB,         this, "group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "LiSP Mode",        lispMode,        SetShadowLiSPModeCB,         GetShadowLiSPModeCB,        this, "group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "Number of Splits", TW_TYPE_INT32,   SetShadowNbrOfSplitsCB,      GetShadowNbrOfSplitsCB,     this, "min=1 max=10 step=1 group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "Use Geom Shader",  TW_TYPE_BOOLCPP, SetShadowUseGeomShaderCB,    GetShadowUseGeomShaderCB,   this, "group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "Reduce Swimming",  TW_TYPE_BOOLCPP, SetShadowReduceSwimmingCB,   GetShadowReduceSwimmingCB,  this, "group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "Light Space Align",TW_TYPE_BOOLCPP, SetShadowLightSpaceAlignCB,  GetShadowLightSpaceAlignCB, this, "group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "Use Min Depth",    TW_TYPE_BOOLCPP, SetShadowUseMinDepthCB,      GetShadowUseMinDepthCB,     this, "group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "Use Best Resol",   TW_TYPE_BOOLCPP, SetShadowUseBestResolSelCB,  GetShadowUseBestResolSelCB, this, "group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "Warping Parameter",TW_TYPE_FLOAT,   SetShadowWarpParameterCB,    GetShadowWarpParameterCB,   this, "min=0.0 max=6000.0 step=100.0 precision=1 group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "Split Parameter",  TW_TYPE_FLOAT,   SetShadowSplitParameterCB,   GetShadowSplitParameterCB,  this, "min=0.0 max=1.0 step=0.01 precision=2 group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "zNear",            TW_TYPE_FLOAT,   SetShadowZNearCB,            GetShadowZNearCB,           this, "min=0.0 max=1.0 step=0.01 precision=2 group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "Pseudo Near",      TW_TYPE_FLOAT,   SetShadowPseudoNearCB,       GetShadowPseudoNearCB,      this, "min=0.0 max=1.0 step=0.01 precision=2 group='Advanced Parameter'");
    TwAddVarCB(_tweakbar, "Pseudo Far",       TW_TYPE_FLOAT,   SetShadowPseudoFarCB,        GetShadowPseudoFarCB,       this, "min=0.0 max=1.0 step=0.01 precision=2 group='Advanced Parameter'");

    TwDefine("TweakBar/'Luminance Adaption' opened=false");
    TwDefine("TweakBar/'Gamma Correction'   opened=false");
    TwDefine("TweakBar/'Bloom'              opened=false");
    TwDefine("TweakBar/'Tonemapping'        opened=false");
    TwDefine("TweakBar/'Environment'        opened=false");
    TwDefine("TweakBar/'Light'              opened=true");
    TwDefine("TweakBar/'Shadow'             opened=true");

    TwDefine("TweakBar/'Shadow'             group=Light  opened=true");
    TwDefine("TweakBar/'Shadow Parameter'   group=Shadow opened=true");
    TwDefine("TweakBar/'Advanced Parameter' group=Shadow opened=true");

    HandleShadowParamConstraints();
}

#endif

//-----------------------------------------------------------------------------
//
// Material: Setup a repository of some 36 materials. Each of the following
//           functions handles two materials. The functions are basically
//           taken from the descmaterial.cpp example.
//
void Example::setupMaterialFloor()
{
    OSG::MaterialDescRefPtr matDesc = OSG::MaterialDesc::create();
    OSG::TextureDescRefPtr  texDesc = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the texture description
    texDesc->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc->setIsSRGBTexture(true);
    texDesc->setFilename("Data/wood.png");
    texDesc->setUVChannel(0);
    texDesc->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc->setBlendFactor(1.f);
    texDesc->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc->setWrapS(GL_MIRRORED_REPEAT);
    texDesc->setWrapT(GL_MIRRORED_REPEAT);
    texDesc->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc->setImageMap(_imageMap);

    // Setup the material description
    matDesc->setShadingModel   (shadingModel);
    matDesc->setFlatShadingMode(_useFlatShading);
    matDesc->setEmissive       (OSG::Color3f(0,0,0));
    matDesc->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc->setShininess      (0.2f * 128.f);
    matDesc->setOpacity        (1.0f);
    matDesc->setSRGBColorMode  (true);
    matDesc->setRoughness      (0.5f);
    matDesc->setMetalness      (0.8f);
    matDesc->setNumUVChannels  (1);
    matDesc->addTexture        (texDesc);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m = _materialManager->addMaterial(matDesc);

    OSG_ASSERT(m.second);

    _floorMaterial = m.second;
}

void Example::setupMaterialLights()
{
    OSG::MaterialDescRefPtr matDesc = OSG::MaterialDesc::create();
    OSG::UInt32 shadingModel = OSG::MaterialDesc::GOURAUD_SHADING_MODEL;

    matDesc->setEmissive     (OSG::Color3f(0,0,0));
    matDesc->setAlbedo       (OSG::Color3f(0.8f, 0.8f, 0.8f));
    matDesc->setSpecular     (OSG::Color3f(0.0f, 0.0f, 0.0f));
    matDesc->setShininess    (0.0f);
    matDesc->setOpacity      (1.0f);
    matDesc->setSRGBColorMode(true);

    OSG::MaterialManager::ManagedMaterialT m = _materialManager->addMaterial(matDesc);

    OSG_ASSERT(m.second);

    for (OSG::UInt32 i = 0; i < max_num_lights; ++i)
    {
        _vecMaterialsLights.push_back(m.second);
    }
}

void Example::setupMaterial0()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.5f);
    matDesc1->setMetalness      (0.8f);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.5f);
    matDesc2->setMetalness      (0.8f);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial1()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc1 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc2 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the texture description
    texDesc1->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc1->setIsSRGBTexture(true);
    texDesc1->setFilename("Data/wood.png");
    texDesc1->setUVChannel(0);
    texDesc1->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc1->setBlendFactor(1.f);
    texDesc1->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc1->setWrapS(GL_MIRRORED_REPEAT);
    texDesc1->setWrapT(GL_MIRRORED_REPEAT);
    texDesc1->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc1->setImageMap(_imageMap);

    texDesc2->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc2->setIsSRGBTexture(true);
    texDesc2->setFilename("Data/marble.jpg");
    texDesc2->setUVChannel(0);
    texDesc2->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc2->setBlendFactor(100.f);
    texDesc2->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDesc2->setWrapS(GL_MIRRORED_REPEAT);
    texDesc2->setWrapT(GL_MIRRORED_REPEAT);
    texDesc2->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc2->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.5f);
    matDesc1->setMetalness      (0.8f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc1);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.5f);
    matDesc2->setMetalness      (0.8f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc2);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial2()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc1 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc2 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the texture description
    texDesc1->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc1->setIsSRGBTexture(true);
    texDesc1->setFilename("Data/lenna_color.gif");
    texDesc1->setUVChannel(0);
    texDesc1->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc1->setBlendFactor(1.f);
    texDesc1->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc1->setWrapS(GL_REPEAT);
    texDesc1->setWrapT(GL_REPEAT);
    texDesc1->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc1->setImageMap(_imageMap);

    texDesc2->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc2->setIsSRGBTexture(true);
    texDesc2->setFilename("Data/penguin.png");
    texDesc2->setUVChannel(0);
    texDesc2->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc2->setBlendFactor(1.f);
    texDesc2->setOperation(OSG::TextureDesc::DECAL_OPERATION);
    texDesc2->setWrapS(GL_MIRRORED_REPEAT);
    texDesc2->setWrapT(GL_MIRRORED_REPEAT);
    texDesc2->setHasUVTransform(true);
    texDesc2->setRotate(OSG::osgDegree2Rad(10.f));
    texDesc2->setScale(OSG::Vec2f(8.f, 8.f));
    texDesc2->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.5f);
    matDesc1->setMetalness      (0.8f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc1);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.5f);
    matDesc2->setMetalness      (0.8f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc2);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}
     
void Example::setupMaterial3()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the texture description for the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/bricks2.jpg");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(_imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc12->setIsSRGBTexture(true);
    texDesc12->setFilename("Data/penguin.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::DECAL_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::USE_ALPHA_FLAG);
    texDesc12->setHasUVTransform(true);
    texDesc12->setRotate(OSG::osgDegree2Rad(10.f));
    texDesc12->setScale(OSG::Vec2f(8.f, 8.f));
    texDesc12->setImageMap(_imageMap);

    // Setup the texture description for the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/metal.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(100.f);
    texDesc21->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc21->setImageMap(_imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc22->setIsSRGBTexture(true);
    texDesc22->setFilename("Data/worldground.jpg");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG|OSG::TextureDesc::INVERT_FLAG);
    texDesc22->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.5f);
    matDesc1->setMetalness      (0.8f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.5f);
    matDesc2->setMetalness      (0.8f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial4()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::COOK_TORRANCE_SHADING_MODEL;

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/gold/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(_imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/gold/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(_imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/gold/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(_imageMap);


    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/rusted_iron/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setImageMap(_imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/rusted_iron/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(_imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/rusted_iron/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial5()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescSpecular = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/container2.png");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.f);
    texDescDiffuse->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setImageMap(_imageMap);

    texDescSpecular->setTextureType(OSG::TextureDesc::SPECULAR_TEXTURE);
    texDescSpecular->setIsSRGBTexture(true);
    texDescSpecular->setFilename("Data/container2_specular.png");
    texDescSpecular->setUVChannel(0);
    texDescSpecular->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescSpecular->setBlendFactor(1.f);
    texDescSpecular->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescSpecular->setWrapS(GL_MIRRORED_REPEAT);
    texDescSpecular->setWrapT(GL_MIRRORED_REPEAT);
    texDescSpecular->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescSpecular->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc1->setSpecular       (OSG::Color3f(0,0,0));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc2->setSpecular       (OSG::Color3f(0,0,0));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescSpecular);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial6()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse   = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescSpecular  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescShininess = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/container2.png");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.f);
    texDescDiffuse->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setImageMap(_imageMap);

    texDescSpecular->setTextureType(OSG::TextureDesc::SPECULAR_TEXTURE);
    texDescSpecular->setIsSRGBTexture(true);
    texDescSpecular->setFilename("Data/container2_specular.png");
    texDescSpecular->setUVChannel(0);
    texDescSpecular->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescSpecular->setBlendFactor(1.f);
    texDescSpecular->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescSpecular->setWrapS(GL_MIRRORED_REPEAT);
    texDescSpecular->setWrapT(GL_MIRRORED_REPEAT);
    texDescSpecular->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescSpecular->setImageMap(_imageMap);

    texDescShininess->setTextureType(OSG::TextureDesc::SHININESS_TEXTURE);
    texDescShininess->setIsSRGBTexture(true);
    texDescShininess->setFilename("Data/container2_specular.png");
    texDescShininess->setUVChannel(0);
    texDescShininess->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescShininess->setBlendFactor(50.f);
    texDescShininess->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDescShininess->setWrapS(GL_MIRRORED_REPEAT);
    texDescShininess->setWrapT(GL_MIRRORED_REPEAT);
    texDescShininess->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescShininess->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc1->setSpecular       (OSG::Color3f(0,0,0));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);
    matDesc1->addTexture        (texDescSpecular);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc2->setSpecular       (OSG::Color3f(0,0,0));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescSpecular);
    matDesc2->addTexture        (texDescShininess);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial7()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescSpecular = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescEmissive = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/container2.png");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.f);
    texDescDiffuse->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setImageMap(_imageMap);

    texDescSpecular->setTextureType(OSG::TextureDesc::SPECULAR_TEXTURE);
    texDescSpecular->setIsSRGBTexture(true);
    texDescSpecular->setFilename("Data/container2_specular.png");
    texDescSpecular->setUVChannel(0);
    texDescSpecular->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescSpecular->setBlendFactor(1.f);
    texDescSpecular->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescSpecular->setWrapS(GL_MIRRORED_REPEAT);
    texDescSpecular->setWrapT(GL_MIRRORED_REPEAT);
    texDescSpecular->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescSpecular->setImageMap(_imageMap);

    texDescEmissive->setTextureType(OSG::TextureDesc::EMISSIVE_TEXTURE);
    texDescEmissive->setIsSRGBTexture(true);
    texDescEmissive->setFilename("Data/matrix.jpg");
    texDescEmissive->setUVChannel(0);
    texDescEmissive->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescEmissive->setBlendFactor(1.f);
    texDescEmissive->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescEmissive->setWrapS(GL_MIRRORED_REPEAT);
    texDescEmissive->setWrapT(GL_MIRRORED_REPEAT);
    texDescEmissive->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescEmissive->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc1->setSpecular       (OSG::Color3f(0,0,0));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc2->setSpecular       (OSG::Color3f(0,0,0));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescSpecular);
    matDesc2->addTexture        (texDescEmissive);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial8()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescNormals = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/brickwall.jpg");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.f);
    texDescDiffuse->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setImageMap(_imageMap);

    texDescNormals->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDescNormals->setIsSRGBTexture(false);
    texDescNormals->setFilename("Data/brickwall_normal.jpg");
    texDescNormals->setUVChannel(0);
    texDescNormals->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescNormals->setBlendFactor(1.f);
    texDescNormals->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescNormals->setWrapS(GL_MIRRORED_REPEAT);
    texDescNormals->setWrapT(GL_MIRRORED_REPEAT);
    texDescNormals->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescNormals->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc1->setSpecular       (OSG::Color3f(0.2f,0.2f,0.2f));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc2->setSpecular       (OSG::Color3f(0.2f,0.2f,0.2f));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescNormals);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial9()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescSpecular = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescNormals  = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/maps/SpecularMapWave.png");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.0f);
    texDescDiffuse->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setHasUVTransform(true);
    texDescDiffuse->setScale(OSG::Vec2f(4.0, 4.0));
    texDescDiffuse->setImageMap(_imageMap);

    texDescSpecular->setTextureType(OSG::TextureDesc::SPECULAR_TEXTURE);
    texDescSpecular->setIsSRGBTexture(true);
    texDescSpecular->setFilename("Data/maps/SpecularMapWave.png");
    texDescSpecular->setUVChannel(0);
    texDescSpecular->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescSpecular->setBlendFactor(1.f);
    texDescSpecular->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescSpecular->setWrapS(GL_MIRRORED_REPEAT);
    texDescSpecular->setWrapT(GL_MIRRORED_REPEAT);
    texDescSpecular->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescSpecular->setHasUVTransform(true);
    texDescSpecular->setScale(OSG::Vec2f(4.0, 4.0));
    texDescSpecular->setImageMap(_imageMap);

    texDescNormals->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDescNormals->setIsSRGBTexture(false);
    texDescNormals->setFilename("Data/maps/NormalMapWave.png");
    texDescNormals->setUVChannel(0);
    texDescNormals->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescNormals->setBlendFactor(1.f);
    texDescNormals->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescNormals->setWrapS(GL_MIRRORED_REPEAT);
    texDescNormals->setWrapT(GL_MIRRORED_REPEAT);
    texDescNormals->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescNormals->setMirrorFlags(OSG::TextureDesc::MIRROR_VERTICAL_DIRECTION);
    texDescNormals->setHasUVTransform(true);
    texDescNormals->setScale(OSG::Vec2f(4.0, 4.0));
    texDescNormals->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);
    matDesc1->addTexture        (texDescSpecular);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDescNormals);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescSpecular);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial10()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescNormals  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescDisplace = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/bricks2.jpg");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.0f);
    texDescDiffuse->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setImageMap(_imageMap);

    texDescNormals->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDescNormals->setIsSRGBTexture(false);
    texDescNormals->setFilename("Data/bricks2_normal.jpg");
    texDescNormals->setUVChannel(0);
    texDescNormals->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescNormals->setBlendFactor(1.f);
    texDescNormals->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescNormals->setWrapS(GL_MIRRORED_REPEAT);
    texDescNormals->setWrapT(GL_MIRRORED_REPEAT);
    texDescNormals->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescNormals->setImageMap(_imageMap);
    
    texDescDisplace->setTextureType(OSG::TextureDesc::DISPLACEMENT_TEXTURE);
    texDescDisplace->setIsSRGBTexture(false);
    texDescDisplace->setFilename("Data/bricks2_disp.jpg");
    texDescDisplace->setUVChannel(0);
    texDescDisplace->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDisplace->setBlendFactor(1.f);
    texDescDisplace->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDisplace->setWrapS(GL_MIRRORED_REPEAT);
    texDescDisplace->setWrapT(GL_MIRRORED_REPEAT);
    texDescDisplace->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDisplace->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);
    matDesc1->addTexture        (texDescNormals);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->setBumpScaling    (0.1f);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescNormals);
    matDesc2->addTexture        (texDescDisplace);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial11()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;

    // Setup the texture description for the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/bricks2.jpg");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(_imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc12->setIsSRGBTexture(true);
    texDesc12->setFilename("Data/penguin.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::DECAL_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::USE_ALPHA_FLAG);
    texDesc12->setHasUVTransform(true);
    texDesc12->setRotate(OSG::osgDegree2Rad(10.f));
    texDesc12->setScale(OSG::Vec2f(8.f, 8.f));
    texDesc12->setImageMap(_imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::OPACITY_TEXTURE);
    texDesc13->setIsSRGBTexture(true);
    texDesc13->setFilename("Data/ornament.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setImageMap(_imageMap);

    // Setup the texture description for the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/metal.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(100.f);
    texDesc21->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc21->setImageMap(_imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc22->setIsSRGBTexture(true);
    texDesc22->setFilename("Data/worldground.jpg");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG|OSG::TextureDesc::INVERT_FLAG);
    texDesc22->setImageMap(_imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::OPACITY_TEXTURE);
    texDesc23->setIsSRGBTexture(true);
    texDesc23->setFilename("Data/circles.jpg");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setOpacityCutOff  (0.1f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.5f);
    matDesc1->setMetalness      (0.8f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setOpacityCutOff  (0.1f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.5f);
    matDesc2->setMetalness      (0.8f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial12()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc14 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc15 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc24 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc25 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::COOK_TORRANCE_SHADING_MODEL;

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/wall/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(_imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/wall/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(_imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/wall/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(_imageMap);

    texDesc14->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDesc14->setIsSRGBTexture(false);
    texDesc14->setFilename("Data/pbr/wall/normal.png");
    texDesc14->setUVChannel(0);
    texDesc14->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc14->setBlendFactor(1.f);
    texDesc14->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc14->setWrapS(GL_MIRRORED_REPEAT);
    texDesc14->setWrapT(GL_MIRRORED_REPEAT);
    texDesc14->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc14->setImageMap(_imageMap);

    texDesc15->setTextureType(OSG::TextureDesc::AMBIENT_OCCLUSION_TEXTURE);
    texDesc15->setIsSRGBTexture(false);
    texDesc15->setFilename("Data/pbr/wall/ao.png");
    texDesc15->setUVChannel(0);
    texDesc15->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc15->setBlendFactor(1.f);
    texDesc15->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc15->setWrapS(GL_MIRRORED_REPEAT);
    texDesc15->setWrapT(GL_MIRRORED_REPEAT);
    texDesc15->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc15->setInternalFormat(GL_R8);
    texDesc15->setImageMap(_imageMap);


    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/plastic/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc21->setImageMap(_imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/plastic/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(_imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/plastic/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(_imageMap);

    texDesc24->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDesc24->setIsSRGBTexture(false);
    texDesc24->setFilename("Data/pbr/plastic/normal.png");
    texDesc24->setUVChannel(0);
    texDesc24->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc24->setBlendFactor(1.f);
    texDesc24->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc24->setWrapS(GL_MIRRORED_REPEAT);
    texDesc24->setWrapT(GL_MIRRORED_REPEAT);
    texDesc24->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc24->setImageMap(_imageMap);

    texDesc25->setTextureType(OSG::TextureDesc::AMBIENT_OCCLUSION_TEXTURE);
    texDesc25->setIsSRGBTexture(false);
    texDesc25->setFilename("Data/pbr/plastic/ao.png");
    texDesc25->setUVChannel(0);
    texDesc25->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc25->setBlendFactor(1.f);
    texDesc25->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc25->setWrapS(GL_MIRRORED_REPEAT);
    texDesc25->setWrapT(GL_MIRRORED_REPEAT);
    texDesc25->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc25->setInternalFormat(GL_R8);
    texDesc25->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);
    matDesc1->addTexture        (texDesc14);
    matDesc1->addTexture        (texDesc15);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);
    matDesc2->addTexture        (texDesc24);
    matDesc2->addTexture        (texDesc25);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial13()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc14 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc15 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc24 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc25 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::COOK_TORRANCE_SHADING_MODEL;

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/wall/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(_imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/wall/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(_imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/wall/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(_imageMap);

    texDesc14->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDesc14->setIsSRGBTexture(false);
    texDesc14->setFilename("Data/pbr/wall/normal.png");
    texDesc14->setUVChannel(0);
    texDesc14->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc14->setBlendFactor(1.f);
    texDesc14->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc14->setWrapS(GL_MIRRORED_REPEAT);
    texDesc14->setWrapT(GL_MIRRORED_REPEAT);
    texDesc14->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc14->setImageMap(_imageMap);

    texDesc15->setTextureType(OSG::TextureDesc::AMBIENT_OCCLUSION_TEXTURE);
    texDesc15->setIsSRGBTexture(false);
    texDesc15->setFilename("Data/pbr/wall/ao.png");
    texDesc15->setUVChannel(0);
    texDesc15->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc15->setBlendFactor(1.f);
    texDesc15->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc15->setWrapS(GL_MIRRORED_REPEAT);
    texDesc15->setWrapT(GL_MIRRORED_REPEAT);
    texDesc15->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc15->setInternalFormat(GL_R8);
    texDesc15->setImageMap(_imageMap);


    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/grass/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc21->setImageMap(_imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/grass/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(_imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/grass/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(_imageMap);

    texDesc24->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDesc24->setIsSRGBTexture(false);
    texDesc24->setFilename("Data/pbr/grass/normal.png");
    texDesc24->setUVChannel(0);
    texDesc24->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc24->setBlendFactor(1.f);
    texDesc24->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc24->setWrapS(GL_MIRRORED_REPEAT);
    texDesc24->setWrapT(GL_MIRRORED_REPEAT);
    texDesc24->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc24->setImageMap(_imageMap);

    texDesc25->setTextureType(OSG::TextureDesc::AMBIENT_OCCLUSION_TEXTURE);
    texDesc25->setIsSRGBTexture(false);
    texDesc25->setFilename("Data/pbr/grass/ao.png");
    texDesc25->setUVChannel(0);
    texDesc25->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc25->setBlendFactor(1.f);
    texDesc25->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc25->setWrapS(GL_MIRRORED_REPEAT);
    texDesc25->setWrapT(GL_MIRRORED_REPEAT);
    texDesc25->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc25->setInternalFormat(GL_R8);
    texDesc25->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);
    matDesc1->addTexture        (texDesc14);
    matDesc1->addTexture        (texDesc15);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);
    matDesc2->addTexture        (texDesc24);
    matDesc2->addTexture        (texDesc25);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial14()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();


    OSG::TextureDescRefPtr  texDescReflection = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::COOK_TORRANCE_SHADING_MODEL;

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/gold/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(_imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/gold/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(_imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/gold/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(_imageMap);

    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/rusted_iron/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setImageMap(_imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/rusted_iron/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(_imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/rusted_iron/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(_imageMap);

    if (_skyFiles.size() == 6)
    {
        texDescReflection->setTextureType(OSG::TextureDesc::REFLECTION_TEXTURE);
        texDescReflection->setIsSRGBTexture(_backgroundIsSRGB);
        texDescReflection->setFilename(_skyFiles[OSG::TextureDesc::POS_X].c_str(), OSG::TextureDesc::POS_X);
        texDescReflection->setFilename(_skyFiles[OSG::TextureDesc::POS_Y].c_str(), OSG::TextureDesc::POS_Y);
        texDescReflection->setFilename(_skyFiles[OSG::TextureDesc::POS_Z].c_str(), OSG::TextureDesc::POS_Z);
        texDescReflection->setFilename(_skyFiles[OSG::TextureDesc::NEG_X].c_str(), OSG::TextureDesc::NEG_X);
        texDescReflection->setFilename(_skyFiles[OSG::TextureDesc::NEG_Y].c_str(), OSG::TextureDesc::NEG_Y);
        texDescReflection->setFilename(_skyFiles[OSG::TextureDesc::NEG_Z].c_str(), OSG::TextureDesc::NEG_Z);
        texDescReflection->setEnvironmentMapType(OSG::TextureDesc::CUBE_MAP);
        texDescReflection->setBlendFactor(1.f);
        texDescReflection->setWrapS(GL_CLAMP_TO_EDGE);
        texDescReflection->setWrapT(GL_CLAMP_TO_EDGE);
        texDescReflection->setWrapR(GL_CLAMP_TO_EDGE);
        texDescReflection->setImageMap(_imageMap);

        //texDescReflection->setFilename("Data/Cubemaps/axis/+x.png", OSG::TextureDesc::POS_X);
        //texDescReflection->setFilename("Data/Cubemaps/axis/+y.png", OSG::TextureDesc::POS_Y);
        //texDescReflection->setFilename("Data/Cubemaps/axis/+z.png", OSG::TextureDesc::POS_Z);
        //texDescReflection->setFilename("Data/Cubemaps/axis/-x.png", OSG::TextureDesc::NEG_X);
        //texDescReflection->setFilename("Data/Cubemaps/axis/-y.png", OSG::TextureDesc::NEG_Y);
        //texDescReflection->setFilename("Data/Cubemaps/axis/-z.png", OSG::TextureDesc::NEG_Z);
    }

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setReflectivity   (1.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setReflectivity   (1.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);

    if (_skyFiles.size() == 6)
    {
        matDesc1->addTexture        (texDescReflection);
        matDesc2->addTexture        (texDescReflection);
    }

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial15()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();


    OSG::TextureDescRefPtr  texDescRefl1 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescRefl2 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::COOK_TORRANCE_SHADING_MODEL;

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/gold/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(_imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/gold/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(_imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/gold/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(_imageMap);

    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/rusted_iron/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setImageMap(_imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/rusted_iron/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(_imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/rusted_iron/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(_imageMap);

    texDescRefl1->setTextureType(OSG::TextureDesc::REFLECTION_TEXTURE);
    texDescRefl1->setIsSRGBTexture(_backgroundIsSRGB);
    texDescRefl1->setFilename("Data/hdr/newport_loft_hcross.hdr");
    texDescRefl1->setFilename("Data/hdr/newport_loft_vcross.hdr");
    texDescRefl1->setFilename("Data/hdr/newport_loft_hstrip.hdr");
    texDescRefl1->setFilename("Data/hdr/newport_loft_vstrip.hdr");
    texDescRefl1->setEnvironmentMapType(OSG::TextureDesc::CUBE_MAP);
    texDescRefl1->setBlendFactor(1.f);
    texDescRefl1->setWrapS(GL_CLAMP_TO_EDGE);
    texDescRefl1->setWrapT(GL_CLAMP_TO_EDGE);
    texDescRefl1->setWrapR(GL_CLAMP_TO_EDGE);
    texDescRefl1->setImageMap(_imageMap);

    if (_skyFiles.size() == 6)
    {
        texDescRefl2->setTextureType(OSG::TextureDesc::REFLECTION_TEXTURE);
        texDescRefl2->setIsSRGBTexture(_backgroundIsSRGB);
        texDescRefl2->setFilename(_skyFiles[OSG::TextureDesc::POS_X].c_str(), OSG::TextureDesc::POS_X);
        texDescRefl2->setFilename(_skyFiles[OSG::TextureDesc::POS_Y].c_str(), OSG::TextureDesc::POS_Y);
        texDescRefl2->setFilename(_skyFiles[OSG::TextureDesc::POS_Z].c_str(), OSG::TextureDesc::POS_Z);
        texDescRefl2->setFilename(_skyFiles[OSG::TextureDesc::NEG_X].c_str(), OSG::TextureDesc::NEG_X);
        texDescRefl2->setFilename(_skyFiles[OSG::TextureDesc::NEG_Y].c_str(), OSG::TextureDesc::NEG_Y);
        texDescRefl2->setFilename(_skyFiles[OSG::TextureDesc::NEG_Z].c_str(), OSG::TextureDesc::NEG_Z);
        texDescRefl2->setEnvironmentMapType(OSG::TextureDesc::CUBE_MAP);
        texDescRefl2->setBlendFactor(1.f);
        texDescRefl2->setWrapS(GL_CLAMP_TO_EDGE);
        texDescRefl2->setWrapT(GL_CLAMP_TO_EDGE);
        texDescRefl2->setWrapR(GL_CLAMP_TO_EDGE);
        texDescRefl2->setImageMap(_imageMap);
    }

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setReflectivity   (1.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setReflectivity   (1.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);

    if (_skyFiles.size() == 6)
    {
        matDesc1->addTexture        (texDescRefl1);
        matDesc2->addTexture        (texDescRefl2);
    }

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial16()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDescRefl1 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescRefl2 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::COOK_TORRANCE_SHADING_MODEL;

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/gold/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(_imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/gold/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(_imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/gold/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(_imageMap);

    texDescRefl1->setTextureType(OSG::TextureDesc::REFLECTION_TEXTURE);
    texDescRefl1->setIsSRGBTexture(_backgroundIsSRGB);
    texDescRefl1->setFilename("Data/hdr/newport_loft_latlong.hdr");
    texDescRefl1->setEnvironmentMapType(OSG::TextureDesc::EQUIRECTANGULAR_MAP);
    texDescRefl1->setBlendFactor(1.f);
    texDescRefl1->setWrapS(GL_CLAMP_TO_EDGE);
    texDescRefl1->setWrapT(GL_CLAMP_TO_EDGE);
    texDescRefl1->setWrapR(GL_CLAMP_TO_EDGE);
    texDescRefl1->setImageMap(_imageMap);

    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/rusted_iron/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setImageMap(_imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/rusted_iron/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(_imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/rusted_iron/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(_imageMap);

    texDescRefl2->setTextureType(OSG::TextureDesc::REFLECTION_TEXTURE);
    texDescRefl2->setIsSRGBTexture(_backgroundIsSRGB);
    texDescRefl2->setFilename("Data/hdr/newport_loft_latlong.tga");
    texDescRefl2->setEnvironmentMapType(OSG::TextureDesc::EQUIRECTANGULAR_MAP);
    texDescRefl2->setBlendFactor(1.f);
    texDescRefl2->setWrapS(GL_CLAMP_TO_EDGE);
    texDescRefl2->setWrapT(GL_CLAMP_TO_EDGE);
    texDescRefl2->setWrapR(GL_CLAMP_TO_EDGE);
    texDescRefl2->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setReflectivity   (1.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setReflectivity   (1.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);

    if (_skyFiles.size() == 6)
    {
        matDesc1->addTexture        (texDescRefl1);
        matDesc2->addTexture        (texDescRefl2);
    }

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);

    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

void Example::setupMaterial17()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDescIrradiance  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescPreFiltered = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescBrdf        = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = OSG::MaterialDesc::COOK_TORRANCE_SHADING_MODEL;

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/gold/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(_imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/gold/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(_imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/gold/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(_imageMap);

    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/rusted_iron/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setImageMap(_imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/rusted_iron/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(_imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/rusted_iron/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(_imageMap);

    texDescIrradiance->setTextureType(OSG::TextureDesc::IRRADIANCE_TEXTURE);
    texDescIrradiance->setIsSRGBTexture(false);
    texDescIrradiance->setFilename("Data/hdr/newport_irradiance.hdr");
    
    //texDescIrradiance->setFilename("Data/hdr/newport_irradiance_posx.hdr", OSG::TextureDesc::POS_X);
    //texDescIrradiance->setFilename("Data/hdr/newport_irradiance_posy.hdr", OSG::TextureDesc::POS_Y);
    //texDescIrradiance->setFilename("Data/hdr/newport_irradiance_posz.hdr", OSG::TextureDesc::POS_Z);
    //texDescIrradiance->setFilename("Data/hdr/newport_irradiance_negx.hdr", OSG::TextureDesc::NEG_X);
    //texDescIrradiance->setFilename("Data/hdr/newport_irradiance_negy.hdr", OSG::TextureDesc::NEG_Y);
    //texDescIrradiance->setFilename("Data/hdr/newport_irradiance_negz.hdr", OSG::TextureDesc::NEG_Z);

    texDescIrradiance->setEnvironmentMapType(OSG::TextureDesc::CUBE_MAP);

    texDescIrradiance->setBlendFactor(1.f);
    texDescIrradiance->setWrapS(GL_CLAMP_TO_EDGE);
    texDescIrradiance->setWrapT(GL_CLAMP_TO_EDGE);
    texDescIrradiance->setWrapR(GL_CLAMP_TO_EDGE);
    texDescIrradiance->setMinFilter(GL_LINEAR);
    texDescIrradiance->setMagFilter(GL_LINEAR);
    texDescIrradiance->setImageMap(_imageMap);

    texDescPreFiltered->setTextureType(OSG::TextureDesc::PRE_FILTER_TEXTURE);
    texDescPreFiltered->setIsSRGBTexture(false);
    texDescPreFiltered->setFilename("Data/hdr/newport_loft_radiance_hcross.hdr");
    texDescPreFiltered->setEnvironmentMapType(OSG::TextureDesc::CUBE_MAP);
    texDescPreFiltered->setBlendFactor(1.f);
    texDescPreFiltered->setWrapS(GL_CLAMP_TO_EDGE);
    texDescPreFiltered->setWrapT(GL_CLAMP_TO_EDGE);
    texDescPreFiltered->setWrapR(GL_CLAMP_TO_EDGE);
    texDescPreFiltered->setImageMap(_imageMap);

    texDescBrdf->setTextureType(OSG::TextureDesc::PRE_FILTER_TEXTURE);
    texDescBrdf->setIsSRGBTexture(false);
    texDescBrdf->setFilename("Data/pbr/ibl_brdf_lut.png");
    texDescBrdf->setBlendFactor(1.f);
    texDescBrdf->setWrapS(GL_CLAMP_TO_EDGE);
    texDescBrdf->setWrapT(GL_CLAMP_TO_EDGE);
    texDescBrdf->setWrapR(GL_CLAMP_TO_EDGE);
    texDescBrdf->setImageMap(_imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode(_useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode  (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setReflectivity   (1.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);
    matDesc1->addTexture        (texDescIrradiance);
    //matDesc1->addTexture        (texDescPreFiltered);
    //matDesc1->addTexture        (texDescBrdf);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode(_useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode  (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setReflectivity   (1.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);
    matDesc2->addTexture        (texDescIrradiance);
    //matDesc2->addTexture        (texDescPreFiltered);
    //matDesc2->addTexture        (texDescBrdf);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = _materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = _materialManager->addMaterial(matDesc2);
    
    OSG_ASSERT(m1.second && m2.second);

    _vecMaterials.push_back(m1.second);
    _vecMaterials.push_back(m2.second);
}

//-----------------------------------------------------------------------------
//
// Background setup: Just setup 7 different skyboxes.
//
void Example::initBackground()
{
    if (_skyBgnd_index > 0)
    {
        _skyFiles.clear();

        switch (_skyBgnd_index)
        {
        case 1:
            _backgroundIsSRGB = true;
            _skyFiles.push_back("Data/Cubemaps/CoitTower2/posx.jpg");
            _skyFiles.push_back("Data/Cubemaps/CoitTower2/posy.jpg");
            _skyFiles.push_back("Data/Cubemaps/CoitTower2/posz.jpg");
            _skyFiles.push_back("Data/Cubemaps/CoitTower2/negx.jpg");
            _skyFiles.push_back("Data/Cubemaps/CoitTower2/negy.jpg");
            _skyFiles.push_back("Data/Cubemaps/CoitTower2/negz.jpg");
            break;
        case 2:
            _backgroundIsSRGB = true;
            _skyFiles.push_back("Data/Cubemaps/GamlaStan/posx.jpg");
            _skyFiles.push_back("Data/Cubemaps/GamlaStan/posy.jpg");
            _skyFiles.push_back("Data/Cubemaps/GamlaStan/posz.jpg");
            _skyFiles.push_back("Data/Cubemaps/GamlaStan/negx.jpg");
            _skyFiles.push_back("Data/Cubemaps/GamlaStan/negy.jpg");
            _skyFiles.push_back("Data/Cubemaps/GamlaStan/negz.jpg");
            break;
        case 3:
            _backgroundIsSRGB = true;
            _skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/+x.jpg");
            _skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/+y.jpg");
            _skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/+z.jpg");
            _skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/-x.jpg");
            _skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/-y.jpg");
            _skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/-z.jpg");
            break;
        case 4:
            _backgroundIsSRGB = true;
            _skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/posx.jpg");
            _skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/posy.jpg");
            _skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/posz.jpg");
            _skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/negx.jpg");
            _skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/negy.jpg");
            _skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/negz.jpg");
            break;
        case 5:
            _backgroundIsSRGB = true;
            _skyFiles.push_back("Data/Cubemaps/SanFrancisco4/posx.jpg");
            _skyFiles.push_back("Data/Cubemaps/SanFrancisco4/posy.jpg");
            _skyFiles.push_back("Data/Cubemaps/SanFrancisco4/posz.jpg");
            _skyFiles.push_back("Data/Cubemaps/SanFrancisco4/negx.jpg");
            _skyFiles.push_back("Data/Cubemaps/SanFrancisco4/negy.jpg");
            _skyFiles.push_back("Data/Cubemaps/SanFrancisco4/negz.jpg");
            break;
        case 6:
            _backgroundIsSRGB = false;
            _skyFiles.push_back("Data/hdr/newport_loft_posx.hdr");
            _skyFiles.push_back("Data/hdr/newport_loft_posy.hdr");
            _skyFiles.push_back("Data/hdr/newport_loft_posz.hdr");
            _skyFiles.push_back("Data/hdr/newport_loft_negx.hdr");
            _skyFiles.push_back("Data/hdr/newport_loft_negy.hdr");
            _skyFiles.push_back("Data/hdr/newport_loft_negz.hdr");
            break;
        case 7:
            _backgroundIsSRGB = true;
            _skyFiles.push_back("Data/Cubemaps/mountain_orange/+x.jpg");
            _skyFiles.push_back("Data/Cubemaps/mountain_orange/+y.jpg");
            _skyFiles.push_back("Data/Cubemaps/mountain_orange/+z.jpg");
            _skyFiles.push_back("Data/Cubemaps/mountain_orange/-x.jpg");
            _skyFiles.push_back("Data/Cubemaps/mountain_orange/-y.jpg");
            _skyFiles.push_back("Data/Cubemaps/mountain_orange/-z.jpg");
        }

        OSG_ASSERT(_skyFiles.size() == 6);
    }
}

void Example::setupBackground()
{
    if (_skyBgnd_index == 0)
    {
        OSG::SolidBackgroundRefPtr background = OSG::SolidBackground::create();
        background->setColor(_clear_color);
        _mgr->setBackground(background);
    }
    else
    {
        initBackground();

        OSG_ASSERT(_skyFiles.size() == 6);

        OSG::SkyBackgroundRefPtr skyBgnd = OSG::SkyBackground::create();

        OSG::ImageUnrecPtr imgPosX = OSG::ImageFileHandler::the()->read(_skyFiles[0].c_str());
        OSG::ImageUnrecPtr imgPosY = OSG::ImageFileHandler::the()->read(_skyFiles[1].c_str());
        OSG::ImageUnrecPtr imgPosZ = OSG::ImageFileHandler::the()->read(_skyFiles[2].c_str());
        OSG::ImageUnrecPtr imgNegX = OSG::ImageFileHandler::the()->read(_skyFiles[3].c_str());
        OSG::ImageUnrecPtr imgNegY = OSG::ImageFileHandler::the()->read(_skyFiles[4].c_str());
        OSG::ImageUnrecPtr imgNegZ = OSG::ImageFileHandler::the()->read(_skyFiles[5].c_str());

        OSG::TextureObjChunkUnrecPtr texObjPosX = OSG::TextureObjChunk::create();
        OSG::TextureObjChunkUnrecPtr texObjPosY = OSG::TextureObjChunk::create();
        OSG::TextureObjChunkUnrecPtr texObjPosZ = OSG::TextureObjChunk::create();
        OSG::TextureObjChunkUnrecPtr texObjNegX = OSG::TextureObjChunk::create();
        OSG::TextureObjChunkUnrecPtr texObjNegY = OSG::TextureObjChunk::create();
        OSG::TextureObjChunkUnrecPtr texObjNegZ = OSG::TextureObjChunk::create();

        if (_backgroundIsSRGB)
        {
            texObjPosX->setInternalFormat(GL_SRGB);
            texObjPosY->setInternalFormat(GL_SRGB);
            texObjPosZ->setInternalFormat(GL_SRGB);
            texObjNegX->setInternalFormat(GL_SRGB);
            texObjNegY->setInternalFormat(GL_SRGB);
            texObjNegZ->setInternalFormat(GL_SRGB);
        }

        texObjPosX->setImage(imgPosX);
        texObjPosY->setImage(imgPosY);
        texObjPosZ->setImage(imgPosZ);
        texObjNegX->setImage(imgNegX);
        texObjNegY->setImage(imgNegY);
        texObjNegZ->setImage(imgNegZ);

        texObjPosX->setWrapS(GL_CLAMP_TO_EDGE); texObjPosX->setWrapT(GL_CLAMP_TO_EDGE);
        texObjPosY->setWrapS(GL_CLAMP_TO_EDGE); texObjPosY->setWrapT(GL_CLAMP_TO_EDGE);
        texObjPosZ->setWrapS(GL_CLAMP_TO_EDGE); texObjPosZ->setWrapT(GL_CLAMP_TO_EDGE);
        texObjNegX->setWrapS(GL_CLAMP_TO_EDGE); texObjNegX->setWrapT(GL_CLAMP_TO_EDGE);
        texObjNegY->setWrapS(GL_CLAMP_TO_EDGE); texObjNegY->setWrapT(GL_CLAMP_TO_EDGE);
        texObjNegZ->setWrapS(GL_CLAMP_TO_EDGE); texObjNegZ->setWrapT(GL_CLAMP_TO_EDGE);

        skyBgnd->setBackTexture  (texObjNegZ);
        skyBgnd->setFrontTexture (texObjPosZ);
        skyBgnd->setLeftTexture  (texObjNegX);
        skyBgnd->setRightTexture (texObjPosX);
        skyBgnd->setBottomTexture(texObjNegY);
        skyBgnd->setTopTexture   (texObjPosY);

        _mgr->setBackground(skyBgnd);
    }
}
