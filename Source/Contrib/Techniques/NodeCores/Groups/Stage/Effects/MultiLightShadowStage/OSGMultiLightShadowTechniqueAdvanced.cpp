/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGMultiLightShadowTechniqueAdvanced.h"
#include "OSGRenderAction.h"
#include "OSGMultiLightChunk.h"
#include "OSGMultiLightShadowStage.h"
#include "OSGMultiLightShadowStageData.h"
#include "OSGMultiLightShadowParameter.h"
#include "OSGMultiLightShadowParameterAdvanced.h"

#include "OSGMaterialChunk.h"
#include "OSGColorMaskChunk.h"
#include "OSGPolygonChunk.h"

#include "OSGMatrixUtility.h"
#include "OSGShaderUtility.h"

#include "OSGPolygon.h"
#include "OSGPolygonBody.h"
#include "OSGPerspectiveProjection.h"
#include "OSGOrthographicProjection.h"

#include "OSGPerspectiveCamera.h"
#include "OSGOrthographicCamera.h"

OSG_BEGIN_NAMESPACE

bool MultiLightShadowTechniqueAdvanced::_initExtenstions = false;

UInt32 MultiLightShadowTechniqueAdvanced::_uiTextureCubeMapArrayARB      = Window::invalidExtensionID;
UInt32 MultiLightShadowTechniqueAdvanced::_uiTextureArrayEXT             = Window::invalidExtensionID;
UInt32 MultiLightShadowTechniqueAdvanced::_uiGeometryShader4ARB          = Window::invalidExtensionID;

UInt32 MultiLightShadowTechniqueAdvanced::_uiFuncFramebufferTextureLayer = Window::invalidFunctionID;

void MultiLightShadowTechniqueAdvanced::initializeExtensions()
{
    if (_initExtenstions) return;

    // GL_TEXTURE_CUBE_MAP_ARRAY OpenGL 4.0/4.6 ARB_texture_cube_map_array
    // GL_TEXTURE_2D_ARRAY       OpenGL 3.0/4.6 EXT_texture_array

    _uiTextureCubeMapArrayARB =  Window::registerExtension("GL_ARB_texture_cube_map_array");
    _uiTextureArrayEXT        =  Window::registerExtension("GL_EXT_texture_array");
    _uiGeometryShader4ARB     =  Window::registerExtension("GL_ARB_geometry_shader4");

    _uiFuncFramebufferTextureLayer =  Window::registerFunction (OSG_DLSYM_UNDERSCORE"glFramebufferTextureLayerARB", _uiGeometryShader4ARB);

    _initExtenstions = true;
}

UInt32 MultiLightShadowTechniqueAdvanced::getRequiredMultiLightFeatures()
{
    UInt32 required = 
          MultiLight::HAS_SHADOW
        | MultiLight::HAS_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX
        ;

    return required;
}

MultiLightShadowTechniqueAdvanced::MultiLightShadowTechniqueAdvanced(
    MultiLightShadowStage     *pStage,
    MultiLightShadowStageData *pData,
    Window                    *pWindow)
: Inherited                 (pStage, pData, pWindow)
, _pointLightStore          ()
, _pointLightTexObj         (NULL)
, _pointLightSampleObj      (NULL)
, _pointLightImg            (NULL)
, _pointLightSHLChunk       (NULL)
, _pointLightChunkMaterial  (NULL)
, _pointLightNbrMaps        (0)
, _dirLightStore            ()
, _dirLightTexObj           (NULL)
, _dirLightSampleObj        (NULL)
, _dirLightImg              (NULL)
, _dirLightSHLChunk         (NULL)
, _dirLightChunkMaterial    (NULL)
, _dirLightNbrMaps          (0)
, _shadowData               ()
, _shadowDataLast           ()
, _algorithmData            ()
, _algorithmDataLast        ()
// The following members will be set/calculated for each light 
// separately.
, _nbrOfSplits              (1)
, _useLiSP                  (false)
, _useGS                    (false)
, _liSPMode                 (LiSPSMTechnique::REPARAMETRIZED)
, _focusing                 (false)
, _reduceSwimming           (false)
, _updateLightUp            (false) // lightSpaceAlignment
, _useMinDepth              (false)
, _useBestResSelection      (false)
, _warpingParameter         (1.f)
, _lambda                   (0.5f)
, _zNear                    (0.f)
, _pseudoNear               (0.f)
, _pseudoFar                (1.f)
, _type                     (MultiLight::POINT_LIGHT)
// Runtime data
, _maxNbrOfSplits           (0)
, _maxNbrOfSplitsLast       (0)
, _gamma                    (0.f)
, _depthRange               (0.f, 0.f)
, _liSP                     (0)
, _camView                  ()
, _lightView                ()
, _defaultShadowParameter   (NULL)
{
    _uiMode = MultiLightShadowStage::ADVANCED_SHADOW_MAP;

    //
    // Reset to allow mode switching
    //
    pData->setOverrideProgChunk(NULL);
    pData->setOverrideProgram(NULL);

    _defaultShadowParameter = MultiLightShadowParameterAdvanced::createLocal();
}

MultiLightShadowTechniqueAdvanced::~MultiLightShadowTechniqueAdvanced()
{
}

void MultiLightShadowTechniqueAdvanced::initialize(RenderAction* a, DrawEnv* pEnv)
{
    MultiLightChunk* pMLChunk = _pStage->getMultiLightChunk();

    bool check = pMLChunk->checkFeatures(getRequiredMultiLightFeatures());
    OSG_ASSERT(check);

    initLimits(a->getWindow());

    calcMaxNbrOfSplits();
}

bool MultiLightShadowTechniqueAdvanced::hasExtOrVersion(RenderAction* a)
{
    if (!a) return false;

    initializeExtensions();

    Window* win = a->getWindow();

    if (   win->hasExtOrVersion(_uiTextureCubeMapArrayARB,      0x0400        ) == false
        || win->hasExtOrVersion(_uiTextureArrayEXT,             0x0300        ) == false
        || win->hasExtOrVersion(_uiGeometryShader4ARB,          0x0302        ) == false
        || win->hasExtOrVersion(_uiFuncFramebufferTextureLayer, 0x0302        ) == false
       )
    {
        return false;
    }

    return true;
}

std::size_t MultiLightShadowTechniqueAdvanced::calcShadowDataBufferSize() const
{
    UInt32 numShadowData = static_cast<UInt32>(_shadowData.size());

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    //
    // _maxNbrOfSplits is the upper bound of splits over all lights. But
    // each light has its own split number that is stored in nbrOfSplits.
    //

    //struct ShadowData
    //{
    //    int   nbrOfSplits;
    //    bool  focused;
    //    vec3  lightPosDir;
    //    mat4  matLSFromWS    [_maxNbrOfSplits];
    //    mat4  matTSFromWS    [_maxNbrOfSplits];
    //    vec2  frustumSize    [_maxNbrOfSplits];
    //    float zNear          [_maxNbrOfSplits];
    //    float zFar           [_maxNbrOfSplits];
    //    int   shadowIndex    [_maxNbrOfSplits];
    //    float splitPositions [_maxNbrOfSplits];
    //};

    ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);      // Int32   nbrOfSplits
    ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);      // bool    focused

    ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);      // Vec3f   lightPosDir

    for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);  // Matrix  matLSFromWS
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
    }
    
    ao = alignOffset(16, bo); bo = ao;

    for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);  // Matrix  matTSFromWS
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
    }
    
    ao = alignOffset(16, bo); bo = ao;
    
    for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
    {
        ao = alignOffset( 8, bo); bo = ao + sizeof(Vec2f);  // Vec2f   frustumSize
    }
    
    ao = alignOffset(8, bo); bo = ao;

    for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32); // Real32  zNear
    }
    
    for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32); // Real32  zFar
    }

    for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);  // Int32   shadowIndex
    }

    for (Int32 i = 1; i <= _maxNbrOfSplits; ++i)
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32); // Real32  splitPositions
    }

    ao = alignOffset(16, bo); bo = ao;                  // padding

    ao *= numShadowData;      bo = ao;                  // array
    ao = alignOffset(16, bo); bo = ao;                  // padding

    return ao;
}

std::vector<UInt8> MultiLightShadowTechniqueAdvanced::createShadowDataBuffer() const
{
    std::size_t size = calcShadowDataBufferSize();

    std::vector<UInt8> buffer(size);

    UInt32 numShadowData = static_cast<UInt32>(_shadowData.size());

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    //
    // _maxNbrOfSplits is the upper bound of splits over all lights. But
    // each light has its own split number that is stored in nbrOfSplits.
    //

    for (UInt32 idx = 0; idx < numShadowData; ++idx)
    {
        const Int32                           nbrOfSplits     = _shadowData[idx].nbrOfSplits;
        const bool                            focused         = _shadowData[idx].focused;
        const Vec3f&                          lightPosDir     = _shadowData[idx].lightPosDir;
        const ShadowData::MatrixStore&        matLSFromWS     = _shadowData[idx].matLSFromWS;
        const ShadowData::MatrixStore&        matTSFromWS     = _shadowData[idx].matTSFromWS;
        const ShadowData::VectorStore&        frustumSize     = _shadowData[idx].frustumSize;
        const ShadowData::ValueStore&         zNear           = _shadowData[idx].zNear;
        const ShadowData::ValueStore&         zFar            = _shadowData[idx].zFar;
        const ShadowData::IndexStore&         shadowIndex     = _shadowData[idx].shadowIndex;
        const ShadowData::SplitPositionStore& splitPositions  = _shadowData[idx].splitPositions;

        ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = nbrOfSplits; bo = ao + sizeof(Int32);
        ao = alignOffset( 4, bo); *(reinterpret_cast<  bool*>(&buffer[0] + ao)) = focused;     bo = ao + sizeof(Int32);

        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &lightPosDir[0], sizeof(Vec3f));     bo = ao + sizeof(Vec3f);

        for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
        {
            if (i < nbrOfSplits)
            {
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[i][0][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[i][1][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[i][2][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[i][3][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
            }
            else
            {
                ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            }
        }

        ao = alignOffset(16, bo); bo = ao;

        for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
        {
            if (i < nbrOfSplits)
            {
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matTSFromWS[i][0][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matTSFromWS[i][1][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matTSFromWS[i][2][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matTSFromWS[i][3][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
            }
            else
            {
                ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            }
        }

        ao = alignOffset(16, bo); bo = ao;
        
        for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
        {
            if (i < nbrOfSplits)
            {
                ao = alignOffset( 8, bo); memcpy(&buffer[0] + ao, &frustumSize[i][0],    sizeof(Vec2f));  bo = ao + sizeof(Vec2f);
            }
            else
            {
                ao = alignOffset( 8, bo); bo = ao + sizeof(Vec2f);
            }
        }

        ao = alignOffset(8, bo); bo = ao;

        for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
        {
            if (i < nbrOfSplits)
            {
                ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = zNear[i];          bo = ao + sizeof(Real32);
            }
            else
            {
                ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);
            }
        }

        for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
        {
            if (i < nbrOfSplits)
            {
                ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = zFar[i];           bo = ao + sizeof(Real32);
            }
            else
            {
                ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);
            }
        }

        for (Int32 i = 0; i < _maxNbrOfSplits; ++i)
        {
            if (i < nbrOfSplits)
            {
                ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = shadowIndex[i];     bo = ao + sizeof( Int32);
            }
            else
            {
                ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);
            }
        }

        for (Int32 i = 1; i <= _maxNbrOfSplits; ++i)
        {
            if (i <= nbrOfSplits)
            {
                ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = splitPositions[i];  bo = ao + sizeof(Real32);
            }
            else
            {
                ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);
            }
        }

        ao = alignOffset(16, bo); bo = ao;    // padding
    }

    return buffer;
}

void MultiLightShadowTechniqueAdvanced::updateShadowDataState()
{
    if (_shadowData != _shadowDataLast)
    {
        std::vector<UInt8> buffer = createShadowDataBuffer();
        _shadowDataChunk->editMFBuffer()->setValues(buffer);

        _shadowDataLast = _shadowData;
    }
}

std::size_t MultiLightShadowTechniqueAdvanced::calcShadowParamBufferSize() const
{
    UInt32 numShadowParam = _pStage->getNumShadowParameters();

    //
    // If no shadow parameter are given we set a default parameter
    //
    numShadowParam = osgMax(1U, numShadowParam);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    //struct ShadowParameter
    //{
    //    float intensity;
    //    float bias;
    //    int   filterMode;
    //    float filterRadius;
    //    bool  randomRotateFilter;
    //    bool  useBlockerSearch;
    //    bool  usePCSS;
    //};
    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32); // Real32  intensity
    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32); // Real32  bias
    ao = alignOffset( 4, bo); bo = ao + sizeof( Int32); // Int32   filterMode
    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32); // Real32  filterRadius
    ao = alignOffset( 4, bo); bo = ao + sizeof( Int32); // bool    randomRotateFilter
    ao = alignOffset( 4, bo); bo = ao + sizeof( Int32); // bool    useBlockerSearch
    ao = alignOffset( 4, bo); bo = ao + sizeof( Int32); // bool    usePCSS

    ao = alignOffset(16, bo); bo = ao;                  // padding

    ao *= numShadowParam;     bo = ao;                  // array
    ao = alignOffset(16, bo); bo = ao;                  // padding

    return ao;
}

std::vector<UInt8> MultiLightShadowTechniqueAdvanced::createShadowParamBuffer() const
{
    std::size_t size = calcShadowParamBufferSize();

    std::vector<UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    UInt32 numShadowParam = _pStage->getNumShadowParameters();
    if (numShadowParam > 0)
    {
        for (UInt32 idx = 0; idx < numShadowParam; ++idx)
        {
            Real32 intensity        = _pStage->getShadowParameter(idx)->getIntensity();
            Real32 bias             = _pStage->getShadowParameter(idx)->getBias() * getBiasFactor();
             Int32 filterMode       = _pStage->getShadowParameter(idx)->getFilterMode();
            Real32 filterRadius     = _pStage->getShadowParameter(idx)->getFilterRadius();
            bool   randomRotate     = _pStage->getShadowParameter(idx)->getRandomRotateFilter();
            bool   useBlockerSearch = _pStage->getShadowParameter(idx)->getUseBlockerSearch();
            bool   usePCSS          = _pStage->getShadowParameter(idx)->getUsePCSS();

            intensity = osgClamp(0.f, 1.f-intensity, 1.f);

            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = intensity;        bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = bias;             bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = filterMode;       bo = ao + sizeof( Int32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = filterRadius;     bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<  bool*>(&buffer[0] + ao)) = randomRotate;     bo = ao + sizeof( Int32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<  bool*>(&buffer[0] + ao)) = useBlockerSearch; bo = ao + sizeof( Int32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<  bool*>(&buffer[0] + ao)) = usePCSS;          bo = ao + sizeof( Int32);

            MultiLightShadowParameterAdvanced* shadowParam = 
                dynamic_cast<MultiLightShadowParameterAdvanced*>(_pStage->getShadowParameter(idx));

            if (shadowParam)
            {
                // ToDo: Set specific advanced parameter from associated light parameter
            }
            else
            {
                // ToDo: Use default parameter for advanced settings instead
            }
        
            ao = alignOffset(16, bo); bo = ao;    // padding
        }
    }
    else
    {
        Real32 intensity        = _defaultShadowParameter->getIntensity();
        Real32 bias             = _defaultShadowParameter->getBias() * getBiasFactor();
         Int32 filterMode       = _defaultShadowParameter->getFilterMode();
        Real32 filterRadius     = _defaultShadowParameter->getFilterRadius();
        bool   randomRotate     = _defaultShadowParameter->getRandomRotateFilter();
        bool   useBlockerSearch = _defaultShadowParameter->getUseBlockerSearch();
        bool   usePCSS          = _defaultShadowParameter->getUsePCSS();

        intensity = osgClamp(0.f, 1.f-intensity, 1.f);

        ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = intensity;        bo = ao + sizeof(Real32);
        ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = bias;             bo = ao + sizeof(Real32);
        ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = filterMode;       bo = ao + sizeof( Int32);
        ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = filterRadius;     bo = ao + sizeof(Real32);
        ao = alignOffset( 4, bo); *(reinterpret_cast<  bool*>(&buffer[0] + ao)) = randomRotate;     bo = ao + sizeof( Int32);
        ao = alignOffset( 4, bo); *(reinterpret_cast<  bool*>(&buffer[0] + ao)) = useBlockerSearch; bo = ao + sizeof( Int32);
        ao = alignOffset( 4, bo); *(reinterpret_cast<  bool*>(&buffer[0] + ao)) = usePCSS;          bo = ao + sizeof( Int32);

        // ToDo: Use default parameter for advanced settings instead

        ao = alignOffset(16, bo); bo = ao;    // padding
    }

    return buffer;
}

void MultiLightShadowTechniqueAdvanced::updateShadowParamState()
{
    if (getUpdateShadowParameter())
    {
        std::vector<UInt8> buffer = createShadowParamBuffer();
        _shadowParamChunk->editMFBuffer()->setValues(buffer);
    }
}

void MultiLightShadowTechniqueAdvanced::initializeAssocData(UInt32 idx) const
{
    // empty implementation: variation detail not used for technique
}

void MultiLightShadowTechniqueAdvanced::createCamera(
    MultiLight::Type type, 
    CameraUnrecPtr&  camera) const
{
    // empty implementation: variation detail not used for technique
}

bool MultiLightShadowTechniqueAdvanced::changedShadowParameter(
    FieldContainer*     pFC, 
    ConstFieldMaskArg   whichField, 
    UInt32              origin)
{
    bool changed = Inherited::changedShadowParameter(pFC, whichField, origin);
    if (!changed)
    {
        MultiLightShadowParameterAdvanced* pMLShadowParameter = dynamic_cast<MultiLightShadowParameterAdvanced*>(pFC);
        if (pMLShadowParameter)
        {
            if ((whichField & (
                    MultiLightShadowParameterAdvanced::NumberOfSplitsFieldMask |
                    MultiLightShadowParameterAdvanced::UseLiSPFieldMask |
                    MultiLightShadowParameterAdvanced::LiSPModeFieldMask |
                    MultiLightShadowParameterAdvanced::FocusingFieldMask |
                    MultiLightShadowParameterAdvanced::ReduceSwimmingFieldMask |
                    MultiLightShadowParameterAdvanced::LightSpaceAlignmentFieldMask |
                    MultiLightShadowParameterAdvanced::UseMinDepthFieldMask |
                    MultiLightShadowParameterAdvanced::UseBestResSelectionFieldMask |
                    MultiLightShadowParameterAdvanced::WarpingParameterFieldMask |
                    MultiLightShadowParameterAdvanced::SplitParamterLambdaFieldMask |
                    MultiLightShadowParameterAdvanced::ZNearFieldMask |
                    MultiLightShadowParameterAdvanced::PseudoNearFieldMask |
                    MultiLightShadowParameterAdvanced::PseudoFarFieldMask
               )) != 0) changed = true;
        }
    }

    return changed;
}


void MultiLightShadowTechniqueAdvanced::render(RenderAction* a, DrawEnv* pEnv)
{
    initialize(a, pEnv);

    initOverrideShaderProgram(a, pEnv);
    updateOverrideShaderProgram();

    commitChanges();

    if (_pStage->getShadowOn() == true)
    {
        calcShadowAlgorithmData(a, pEnv);
    }

    initShadowMaps();
    updateShadowMaps();

    commitChanges();

    if (_pStage->getShadowOn() == true)
    {
        renderShadowMaps(a, pEnv);

        updateShadowDataState();
        updateShadowParamState();
        updateDistributionState();
    }
}

void MultiLightShadowTechniqueAdvanced::initOverrideShaderProgram(RenderAction* a, DrawEnv* pEnv)
{
    //
    // Initialize some GL constants
    //
    if (_nTexImages == 0 || _nShaderStorageBlocks == 0 || _nUniformBlocks == 0)
    {
        Window* win = a->getWindow();

        Int32 maxTexImageUnits = static_cast<Int32>(win->getConstantValue(GL_MAX_TEXTURE_IMAGE_UNITS_ARB));
        _nTexImages = osgMin(maxTexImageUnits, osgMaxTexImages);

        Int32 maxFragmentShaderStorageBlocks = static_cast<Int32>(win->getConstantValue(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS));
        _nShaderStorageBlocks = osgMin(maxFragmentShaderStorageBlocks, osgMaxShaderStorageBufferBindings);

        Int32 maxFragmentUniformBlocks = static_cast<Int32>(win->getConstantValue(GL_MAX_FRAGMENT_UNIFORM_BLOCKS));
        _nUniformBlocks = osgMin(maxFragmentUniformBlocks, osgMaxUniformBufferBindings);
    }

    //
    // If the number of max. splits changes the shader needs to be regenerated, because it contains 
    // arrays of _maxNbrOfSplits elements.
    // Probably it is sufficient to get along with a less than test.
    //
    if (_maxNbrOfSplitsLast != _maxNbrOfSplits)
    {
        _pStageData->setOverrideProgChunk(NULL);
        _pStageData->setOverrideProgram(NULL);

        _maxNbrOfSplitsLast = _maxNbrOfSplits;
    }

    if (_pStage->getDisableOverride() == false)
    {
        ShaderProgramChunk* progChunk = _pStageData->getOverrideProgChunk();
        if (progChunk == NULL)
        {
            ShaderProgramChunkUnrecPtr chunk = ShaderProgramChunk::createLocal();
            _pStageData->setOverrideProgChunk(chunk);

            progChunk = chunk;
        }

        ShaderProgram* shaderProg = _pStageData->getOverrideProgram();
        if (shaderProg == NULL)
        {
            ShaderProgramUnrecPtr shader = ShaderProgram::createLocal();
            _pStageData->setOverrideProgram(shader);

            shader->setShaderType(GL_FRAGMENT_SHADER);
            shader->setProgram(getFragmentProgramSnippet());

            Int32 iPLTextureUnit       = getSamplerCubeArrayTextureUnit();
            Int32 iDLTextureUnit       = getSampler2DArrayTextureUnit();
            Int32 iPLShadowTextureUnit = getSamplerCubeArrayShadowTextureUnit();
            Int32 iDLShadowTextureUnit = getSampler2DArrayShadowTextureUnit();
            Int32 iShadowDataDBndPnt   = getShadowDataBindingPnt();
            Int32 iShadowParamBndPnt   = getShadowParameterBindingPnt();
            Int32 iDistributionBndPnt  = getDistributionBindingPnt();

            shader->addUniformVariable   ("uShadowEnabled",       _pStage->getShadowOn());
            shader->addUniformVariable   ("uShadowMapPnt",        iPLTextureUnit);
            shader->addUniformVariable   ("uShadowMapDir",        iDLTextureUnit);
            shader->addUniformVariable   ("uShadowMapPntComp",    iPLShadowTextureUnit);
            shader->addUniformVariable   ("uShadowMapDirComp",    iDLShadowTextureUnit);
            shader->addShaderStorageBlock("ShadowDataBlock",      UInt32(iShadowDataDBndPnt));
            shader->addUniformBlock      ("ShadowParameterBlock", UInt32(iShadowParamBndPnt));
            shader->addUniformBlock      ("DistributionBlock",    UInt32(iDistributionBndPnt));

            shader->addUniformVariable   ("uUseShadowSampler",    _pStage->getUseHWPCF());

            progChunk->addShader(shader);
        }
    }
}

void MultiLightShadowTechniqueAdvanced::updateOverrideShaderProgram()
{
    if (getUpdateUniformData() && _pStage->getDisableOverride() == false)
    {
        ShaderProgram* shaderProg = _pStageData->getOverrideProgram();
        if (shaderProg)
        {
            shaderProg->updateUniformVariable("uShadowEnabled",     _pStage->getShadowOn());
            shaderProg->updateUniformVariable("uUseShadowSampler",  _pStage->getUseHWPCF());
        }
    }
}

void MultiLightShadowTechniqueAdvanced::addOverride(RenderAction* a, DrawEnv* pEnv)
{
    Int32 iPLTextureUnit       = getSamplerCubeArrayTextureUnit();
    Int32 iDLTextureUnit       = getSampler2DArrayTextureUnit();
    Int32 iPLShadowTextureUnit = getSamplerCubeArrayShadowTextureUnit();
    Int32 iDLShadowTextureUnit = getSampler2DArrayShadowTextureUnit();
    Int32 iShadowDataDBndPnt   = getShadowDataBindingPnt();
    Int32 iShadowParamBndPnt   = getShadowParameterBindingPnt();
    Int32 iDistributionBndPnt  = getDistributionBindingPnt();

    a->addOverride(    _pointLightTexObj->getClassId() + iPLTextureUnit,       _pointLightTexObj);
    a->addOverride(      _dirLightTexObj->getClassId() + iDLTextureUnit,         _dirLightTexObj);

    a->addOverride(    _pointLightTexObj->getClassId() + iPLShadowTextureUnit, _pointLightTexObj);
    a->addOverride(      _dirLightTexObj->getClassId() + iDLShadowTextureUnit,   _dirLightTexObj);

    a->addOverride( _pointLightSampleObj->getClassId() + iPLShadowTextureUnit, _pointLightSampleObj);
    a->addOverride(   _dirLightSampleObj->getClassId() + iDLShadowTextureUnit,   _dirLightSampleObj);

    a->addOverride(     _shadowDataChunk->getClassId() + iShadowDataDBndPnt,     _shadowDataChunk);
    a->addOverride(    _shadowParamChunk->getClassId() + iShadowParamBndPnt,    _shadowParamChunk);
    a->addOverride(   _distributionChunk->getClassId() + iDistributionBndPnt,  _distributionChunk);

    if (_pStage->getDisableOverride() == false)
    {
        a->addOverride(ShaderProgramChunk::getStaticClassId(), _pStageData->getOverrideProgChunk());
    }
}

void MultiLightShadowTechniqueAdvanced::calcShadowAlgorithmData(RenderAction* a, DrawEnv* pEnv)
{
    _pointLightNbrMaps = 0;
      _dirLightNbrMaps = 0;

    MultiLightShadowStageData::LightAssocStore& vLightAssocData = _pStageData->getLightAssocData();

    MultiLightChunk* pMLChunk = _pStage->getMultiLightChunk();

    UInt32 num_lights = static_cast<UInt32>(vLightAssocData.size());

    adaptShadowDataLayout   (num_lights);
    adaptAlgorithmDataLayout(num_lights);

    RenderPartition* pParentPart = a->getActivePartition();

    //
    // Commit has been called; adapt to shadow casting scene
    //
    a->getActNode()->updateVolume();

    const FrustumVolume& camFrust    = pParentPart->getFrustum();
    const BoxVolume&     sceneBB     = a->getActNode()->getVolume();
    const Matrix&        matWSFromMS = a->topMatrix();
    const Matrix&        matESFromWS = pEnv->getCameraViewing();

    initCameraView(matESFromWS);

    bool isOrthoCamera = isOrthographicCamera(a->getCamera());

    for (UInt32 idx = 0; idx < num_lights; ++idx)
    {
        if (vLightAssocData[idx].enabled && vLightAssocData[idx].shadow)
        {
            //
            // The shadow data are tracked in a separate shader storage block.
            // This block does have the same number of array elements as
            // the multi light. The ShadowIndex memeber of the light just carry
            // the corresponding light index for lookup in the shadow data array.
            //
            pMLChunk->setShadowDataIndex(idx, idx);

            //
            // These light matrices needs to be calculated
            //
            Matrix matLSFromWS, matProjection, matProjLSFromWS;

            pMLChunk->calcLightSpaceMatrixLSFromWS(idx, matLSFromWS);

            Real32 zNearLight, zFarLight;
            pMLChunk->calcFrustumZ(pEnv, idx, zNearLight, zFarLight);

            Pnt3f lightPos;
            pMLChunk->calcPosition(pEnv, idx, lightPos, false);

            _algorithmData[idx].lightPositionWS = lightPos;

            Vec3f lightPosDir;
            if (vLightAssocData[idx].type == MultiLight::DIRECTIONAL_LIGHT
             || vLightAssocData[idx].type == MultiLight::SPOT_LIGHT 
             || vLightAssocData[idx].type == MultiLight::CINEMA_LIGHT)
            {
                pMLChunk->calcDirection(pEnv, idx, lightPosDir, false);
                lightPosDir.normalize();
            }
            else
            {
                lightPosDir = lightPos.subZero();
            }

            Pnt3f  lightMin, lightMax;
            if (vLightAssocData[idx].type == MultiLight::DIRECTIONAL_LIGHT)
            {
                calcOrthoShadowViewVolume(matWSFromMS, matLSFromWS, camFrust, sceneBB, lightMin, lightMax);
                zFarLight = osgMin(zFarLight, lightMax.z());
            }

            initLightView(matLSFromWS);

            pMLChunk->calcProjectionMatrix(idx, zNearLight, zFarLight, lightMin, lightMax, matProjection);

            //
            // If the user has requested a projection matrix for the multi lights then
            // set the projection.
            //
            if (pMLChunk->getHasProjection())
                pMLChunk->setProjectionMatrix(idx, matProjection);

            initShadowAlgorithmState(pMLChunk, idx, isOrthoCamera);


            bool focusingFeasible = false;

            //
            // If focusing is requested we have to check if it is possible to
            // to treat a point light like a spot light.
            // If focusing is not requested we don't need to spent time here
            //
            if (_focusing)
            {
                focusingFeasible = true;    // Assumption

                if (vLightAssocData[idx].type == MultiLight::POINT_LIGHT)
                {
                    PolygonBody body;
                    body.add(camFrust);
                    body.clip(sceneBB);

                    body.createUniqueVertices();

                    const PolygonBody::VecVerticesT& vertices = body.getVertices();

                    PolygonBody::VecVerticesT::const_iterator iter = vertices.begin();
                    PolygonBody::VecVerticesT::const_iterator end  = vertices.end();

                    BoxVolume boxCamFrust;
                    for (; iter != end; ++iter)
                    {
                        boxCamFrust.extendBy(*iter);
                    }

                    const Pnt3f& maximum = boxCamFrust.getMax();
                    const Pnt3f& minimum = boxCamFrust.getMin();

                    Vec3f lightDir = (minimum + (maximum - minimum) / 2.f) - lightPos;
                    Real32 dist    = lightDir.length();

                    lightDir.normalize();

                    Real32 maxDist = 0.f;
                    Real32 shadow_spotlight_cutoff = 0.f;

                    for (iter = vertices.begin(); iter != end; ++iter)
                    {
                        Vec3f diff = *iter - lightPos;
                        Real32 length = diff.length();

                        if (length > maxDist)
                            maxDist = length;

                        diff.normalize();

                        Real32 angle = osgRad2Degree(osgACos(diff.dot(lightDir)));
                        if (angle > shadow_spotlight_cutoff)
                            shadow_spotlight_cutoff = angle;
                    }

                    const Real32 max_shadow_spotlight_cutoff = 45.f;

                    if (shadow_spotlight_cutoff <= max_shadow_spotlight_cutoff)
                    {
                        //
                        // We need to adapt the light view and projection matrix
                        //
                        _lightView.setEye(lightPos);
                        _lightView.setCenter(lightPos + dist * lightDir);

                        Vec3f up      = _lightView.getUp();
                        Vec3f leftVec = up.cross(lightDir);
                        if (leftVec.length() < 1e-3f)
                        {
                            Int32 idx_max = 0;
                            Int32 idx_min = 0;
                            if (up[0] > up[1])
                            {
                                idx_max = 0;
                                idx_min = 1;
                            }
                            else
                            {
                                idx_max = 1;
                                idx_min = 0;
                            }

                            if (up[idx_max] <= up[2])
                                idx_max = 2;
                            if (up[idx_min] >= up[2])
                                idx_min = 2;

                            Real32 tmp = up[idx_max];
                            up[idx_max] = up[idx_min];
                            up[idx_min] = tmp;

                            _lightView.setUp(up);
                        }

                        MatrixLookAtGL(matLSFromWS, _lightView);
                        MatrixPerspective(matProjection, osgDegree2Rad(shadow_spotlight_cutoff), 1.f, zNearLight, zFarLight);

                        lightPosDir = _lightView.getDirection();
                    }
                    else
                    {
                        focusingFeasible = false;

                        _focusing    = false;
                        _useLiSP     = false;
                        _nbrOfSplits = 1;
                    }
                }
            }
    
            _shadowData[idx].nbrOfSplits = _nbrOfSplits;
            _shadowData[idx].focused     = _focusing;
            _shadowData[idx].lightPosDir = lightPosDir;

            adaptAlgorithmDataSplits(idx, _nbrOfSplits);

            updateLDirVDirAngle();

            Real32 zNearCam = pEnv->getCameraNear();
            Real32 zFarCam  = pEnv->getCameraFar ();

            if (_focusing || _useLiSP || _nbrOfSplits > 1)
            {
                adjustCameraPlanes(sceneBB, camFrust, zNearCam, zFarCam);
            }

            zNearCam += _zNear * (zFarCam - zNearCam);

            if (_useMinDepth)
                zNearCam = osgMax(zNearCam, getMinDepth());

            _depthRange[0] = zNearCam;
            _depthRange[1] = zFarCam;

            //
            // Split the view frustum into a number if cascading frustums. 
            //
            calcSplitPositions(idx, zNearCam, zFarCam);

            //
            // Calculate a modified matLSFromWS and in case of perspective projection
            // calculate the light frustum.
            //
            FrustumVolume lightFrust;

            if (focusingFeasible)
            {
                if (vLightAssocData[idx].type == MultiLight::DIRECTIONAL_LIGHT)
                {
                    if (_useLiSP || _updateLightUp)
                    {
                        Vec3f camLeftVec = _camView.getUp().cross(_camView.getDirection());
                        Vec3f lightDir   = _lightView.getDirection();

                        Vec3f up = lightDir.cross(camLeftVec);
                        up.normalize();

                        if (_useGS || !_focusing)
                        {
                            View lightView(_lightView.getEye(), _lightView.getCenter(), up);
                            MatrixLookAtGL(matLSFromWS, lightView);
                        }
                        else
                        {
                            const Pnt3f& eye = _camView.getEye();
                            View lightView(eye, eye + (_lightView.getCenter() - _lightView.getEye()), up);
                            MatrixLookAtGL(matLSFromWS, lightView);
                        }
                    }
                }
                else
                {
                    if (_useLiSP || _updateLightUp)
                    {
                        Vec3f camLeftVec = _camView.getUp().cross(_camView.getDirection());
                        Vec3f lightDir   = _lightView.getDirection();

                        Vec3f up = lightDir.cross(camLeftVec);
                        up.normalize();

                        View lightView(_lightView.getEye(), _lightView.getCenter(), up);

                        MatrixLookAtGL(matLSFromWS, lightView);
                    }

                    matProjLSFromWS = matProjection;
                    matProjLSFromWS.mult(matLSFromWS);

                    lightFrust.setPlanesOutwards(matProjLSFromWS);
                }
            }

            //
            // The iteration over the splits. If no focusing is possible the number of splits is forced to one.
            //
            for (Int32 split = 0; split < _nbrOfSplits; ++split)
            {
                zNearCam = _shadowData[idx].splitPositions[split];
                zFarCam  = _shadowData[idx].splitPositions[split+1];

                Matrix matNewProjection   = matProjection;
                Matrix matNewProjLSFromWS = matNewProjection;
                matNewProjLSFromWS.mult(matLSFromWS);

                if (_focusing)
                {
                    CameraUnrecPtr splitCamera = dynamic_pointer_cast<Camera>(a->getCamera()->shallowCopy());
                    splitCamera->setNear(zNearCam);
                    splitCamera->setFar (zFarCam );

                    Matrix matCamProjection;
                    splitCamera->getProjection(matCamProjection, pParentPart->getViewportWidth(), pParentPart->getViewportHeight());

                    Matrix matProjESFromWS = matCamProjection;
                    matProjESFromWS.mult(matESFromWS);

                    FrustumVolume cameraFrustum;
                    cameraFrustum.setPlanesOutwards(matProjESFromWS);

                    Projection::Type projectionType = (vLightAssocData[idx].type == MultiLight::DIRECTIONAL_LIGHT) 
                                                            ? Projection::ORTHOGRAPHIC 
                                                            : Projection::PERSPECTIVE;

                    PolygonBody body;
                    calcPolygonBody(body, projectionType, sceneBB, cameraFrustum, lightFrust);

                    if (body.getNumVertices())
                    {
                        if (_useLiSP)
                        {
                            if (split == 0)
                            {
                                PerspectiveProjection eyeProj(matCamProjection);

                                _liSP.setLightProjMat  (matProjection, projectionType);
                                _liSP.setLightView     (matLSFromWS,  _lightView);
                                _liSP.setCamView       (matESFromWS,  _camView);
                                _liSP.setCamProjMat    (matCamProjection);
                                _liSP.setFieldOfView   (osgRad2Degree(eyeProj.getFov()));
                                _liSP.setGamma         (_gamma);
                                _liSP.setSplitParam    (_lambda);
                                _liSP.setPseudoNear    (_pseudoNear);
                                _liSP.setPseudoFar     (1.f - _pseudoFar);
                            }

                            const FrustumVolume* pLightFrust = NULL;
                            if (vLightAssocData[idx].type != MultiLight::DIRECTIONAL_LIGHT)
                                pLightFrust = &lightFrust;
                        
                            Matrix matliSP = _liSP.getLiSPMtx(split, body, cameraFrustum, pLightFrust, sceneBB, _depthRange);

                            matliSP.mult(matProjection);
                            calcLightViewProjMat(matNewProjection, matNewProjLSFromWS, split, body, matliSP, matLSFromWS);
                        }
                        else
                        {
                            calcLightViewProjMat(matNewProjection, matNewProjLSFromWS, split, body, matProjection, matLSFromWS);
                        }

                        if (projectionType == Projection::PERSPECTIVE)
                        {
                            PerspectiveProjection lightProj(matNewProjection);
                            zNearLight = lightProj.getZNear();
                            zFarLight  = lightProj.getZFar ();
                        }
                        else
                        {
                            OrthographicProjection lightProj(matNewProjection);
                            zNearLight = lightProj.getZNear();
                            zFarLight  = lightProj.getZFar ();
                        }
                    }
                }

                Matrix matTSFromCS;
                matTSFromCS.setScale(0.5f, 0.5f, 0.5f);
                matTSFromCS.setTranslate(0.5f, 0.5f, 0.5f);

                Matrix matTSFromWS = matTSFromCS;
                matTSFromWS.mult(matNewProjLSFromWS);

                //
                // Finally, collect the render data
                //
                _shadowData[idx].matLSFromWS     [split] = matLSFromWS;
                _shadowData[idx].matTSFromWS     [split] = matTSFromWS;
                _shadowData[idx].frustumSize     [split] = calcFrustumSize(matTSFromWS);
                _shadowData[idx].zNear           [split] = zNearLight;
                _shadowData[idx].zFar            [split] = zFarLight;

                _algorithmData[idx].matProjection[split] = matNewProjection;

                if ( vLightAssocData[idx].type == MultiLight::POINT_LIGHT
                  && !_focusing)
                {
                    _pointLightNbrMaps += 1;
                }
                else
                {
                    _dirLightNbrMaps += 1;
                }
            }
        }
    }
}

void MultiLightShadowTechniqueAdvanced::initShadowMaps()
{
    MultiLightShadowStageData::LightAssocStore& vLightAssocData = _pStageData->getLightAssocData();

    MultiLightChunk* pMLChunk = _pStage->getMultiLightChunk();

    if (!vLightAssocData.empty() && pMLChunk != NULL)
    {
        Int32 width  = _pStage->getShadowMapWidth();
        Int32 height = _pStage->getShadowMapHeight();
        Int32 depth  = 0;

        //
        // 1. create/initialize texture object and environment
        //
        if (_pointLightTexObj == NULL)
        {
            depth = osgMax(6, _pointLightNbrMaps * 6);

            _pointLightImg    = Image          ::createLocal();
            _pointLightImg->set(Image::OSG_DEPTH_PF, 
                                width, height, depth, 
                                1, 1, 0.f, 
                                NULL,
                                Image::OSG_FLOAT32_IMAGEDATA, 
                                false);

            _pointLightTexObj = TextureObjChunk::createLocal();
            _pointLightTexObj->setImage(_pointLightImg);
            _pointLightTexObj->setInternalFormat(GL_DEPTH_COMPONENT);
            _pointLightTexObj->setExternalFormat(GL_DEPTH_COMPONENT);
            //
            // GL_TEXTURE_CUBE_MAP_ARRAY OpenGL 4.0/4.6 ARB_texture_cube_map_array
            // https://www.khronos.org/opengl/wiki/Cubemap_Texture
            // https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_texture_cube_map_array.txt
            //
            _pointLightTexObj->setTarget        (GL_TEXTURE_CUBE_MAP_ARRAY);

            _pointLightTexObj->setMinFilter     (GL_NEAREST);
            _pointLightTexObj->setMagFilter     (GL_NEAREST);
            _pointLightTexObj->setWrapS         (GL_CLAMP_TO_EDGE);
            _pointLightTexObj->setWrapT         (GL_CLAMP_TO_EDGE);
            _pointLightTexObj->setWrapR         (GL_CLAMP_TO_EDGE);

            _pointLightSampleObj = SamplerObjChunk::createLocal();
            _pointLightSampleObj->setMinFilter      (GL_LINEAR);
            _pointLightSampleObj->setMagFilter      (GL_LINEAR);
            _pointLightSampleObj->setWrapS          (GL_CLAMP_TO_EDGE);
            _pointLightSampleObj->setWrapT          (GL_CLAMP_TO_EDGE);
            _pointLightSampleObj->setWrapR          (GL_CLAMP_TO_EDGE);
            _pointLightSampleObj->setCompareMode    (GL_COMPARE_REF_TO_TEXTURE);
            _pointLightSampleObj->setCompareFunc    (GL_LEQUAL);
            _pointLightSampleObj->addTextureUnit    (getSamplerCubeArrayShadowTextureUnit());

            _pointLightSHLChunk = SimpleSHLChunk::createLocal();
            _pointLightSHLChunk->setVertexProgram  (getPointLightVertProgram());
            _pointLightSHLChunk->setFragmentProgram(getPointLightFragProgram());

            // Vertex shader
            _pointLightSHLChunk->addOSGVariable    ("OSGWorldMatrix");

            // fragment shader
            _pointLightSHLChunk->addUniformVariable("uLightPosWS", Pnt3f());
            _pointLightSHLChunk->addUniformVariable("uFarPlaneWS", 0.f);

            _pointLightChunkMaterial = ChunkMaterial::createLocal();
            _pointLightChunkMaterial->addChunk(_pointLightSHLChunk);

            if (_pStage->getOffsetBias() != 0.f || _pStage->getOffsetFactor() != 0.f || _pStage->getCullFrontFace())
            {
                _pointLightChunkMaterial->addChunk(_polygonChunk);
            }
        }

        if (_dirLightTexObj == NULL)
        {
            depth = osgMax(1, _dirLightNbrMaps);

            _dirLightImg    = Image          ::createLocal();
            _dirLightImg->set(Image::OSG_DEPTH_PF, 
                                width, height, depth, 
                                1, 1, 0.f, 
                                NULL,
                                Image::OSG_FLOAT32_IMAGEDATA, 
                                false);

            _dirLightTexObj = TextureObjChunk::createLocal();
            _dirLightTexObj->setImage         (_dirLightImg);
            _dirLightTexObj->setInternalFormat(GL_DEPTH_COMPONENT);
            _dirLightTexObj->setExternalFormat(GL_DEPTH_COMPONENT);
            //
            // GL_TEXTURE_2D_ARRAY OpenGL 3.0/4.6 EXT_texture_array
            // https://www.khronos.org/opengl/wiki/Array_Texture
            //
            _dirLightTexObj->setTarget        (GL_TEXTURE_2D_ARRAY);

            _dirLightTexObj->setMinFilter     (GL_NEAREST);
            _dirLightTexObj->setMagFilter     (GL_NEAREST);
            _dirLightTexObj->setWrapS         (GL_CLAMP_TO_EDGE);
            _dirLightTexObj->setWrapT         (GL_CLAMP_TO_EDGE);
            _dirLightTexObj->setWrapR         (GL_CLAMP_TO_EDGE);

            _dirLightSampleObj = SamplerObjChunk::createLocal();
            _dirLightSampleObj->setMinFilter      (GL_LINEAR);
            _dirLightSampleObj->setMagFilter      (GL_LINEAR);
            _dirLightSampleObj->setWrapS          (GL_CLAMP_TO_EDGE);
            _dirLightSampleObj->setWrapT          (GL_CLAMP_TO_EDGE);
            _dirLightSampleObj->setWrapR          (GL_CLAMP_TO_EDGE);
            _dirLightSampleObj->setCompareMode    (GL_COMPARE_REF_TO_TEXTURE);
            _dirLightSampleObj->setCompareFunc    (GL_LEQUAL);
            _dirLightSampleObj->addTextureUnit    (getSampler2DArrayShadowTextureUnit());

            _dirLightSHLChunk = SimpleSHLChunk::createLocal();
            _dirLightSHLChunk->setVertexProgram  (getDirLightVertProgram());
            _dirLightSHLChunk->setFragmentProgram(getDirLightFragProgram());

            // Vertex shader
            // None

            // fragment shader
            // None

            _dirLightChunkMaterial = ChunkMaterial::createLocal();
            _dirLightChunkMaterial->addChunk(_dirLightSHLChunk);

            if (_pStage->getOffsetBias() != 0.f || _pStage->getOffsetFactor() != 0.f || _pStage->getCullFrontFace())
            {
                _dirLightChunkMaterial->addChunk(_polygonChunk);
            }
        }

        //
        // 2. create/initialize the FBO for the lights
        //
        if (_pointLightStore.size() != 6 * _pointLightNbrMaps)
        {
            _pointLightStore.clear();

            for (Int32 i = 0; i < _pointLightNbrMaps; ++i)
            {
                for (UInt32 j = 0; j < 6; ++j)
                {
                    ShadowMapData data;

                    data.pFBO = FrameBufferObject::createLocal();
                    data.pTBO = TextureBuffer    ::createLocal();

                    data.pTBO->setLevel          (0);
                    data.pTBO->setLayer          (i*6 + j);
                    data.pTBO->setTexture        (_pointLightTexObj);
                    data.pTBO->setTexTarget      (GL_TEXTURE_CUBE_MAP_ARRAY);

                    data.pFBO->setDepthAttachment(data.pTBO);
                    data.pFBO->setWidth          (width);
                    data.pFBO->setHeight         (height);

                    _pointLightStore.push_back(data);
                }
            }
        }

        if (_dirLightStore.size() != _dirLightNbrMaps)
        {
            _dirLightStore.clear();

            for (Int32 i = 0; i < _dirLightNbrMaps; ++i)
            {
                ShadowMapData data;

                data.pFBO = FrameBufferObject::createLocal();
                data.pTBO = TextureBuffer    ::createLocal();

                data.pTBO->setLevel          (0);
                data.pTBO->setLayer          (i);
                data.pTBO->setTexture        (_dirLightTexObj);
                data.pTBO->setTexTarget      (GL_TEXTURE_2D_ARRAY);

                data.pFBO->setDepthAttachment(data.pTBO);
                data.pFBO->setWidth          (width);
                data.pFBO->setHeight         (height);

                _dirLightStore.push_back(data);
            }
        }
    }
    else
    {
        _pointLightStore.clear();
        _dirLightStore  .clear();
    }
}

void MultiLightShadowTechniqueAdvanced::updateShadowMaps()
{
    Int32 width, height, depth;

    width  = _pStage->getShadowMapWidth();
    height = _pStage->getShadowMapHeight();
    depth  = osgMax(6, _pointLightNbrMaps * 6);

    if (_pointLightImg->getWidth()  != width 
     || _pointLightImg->getHeight() != height
     || _pointLightImg->getDepth()  != depth)
    {
        _pointLightImg->set(Image::OSG_DEPTH_PF, 
                            width, height, depth, 
                            1, 1, 0.f, 
                            NULL,
                            Image::OSG_FLOAT32_IMAGEDATA, 
                            false);

        ShadowMapStore::const_iterator iter = _pointLightStore.begin();
        ShadowMapStore::const_iterator end  = _pointLightStore.end();

        for (; iter != end; ++iter)
        {
            iter->pFBO->setWidth (width);
            iter->pFBO->setHeight(height);
        }
    }

    width  = _pStage->getShadowMapWidth();
    height = _pStage->getShadowMapHeight();
    depth  = osgMax(1, _dirLightNbrMaps);

    if (_dirLightImg->getWidth()  != width 
     || _dirLightImg->getHeight() != height
     || _dirLightImg->getDepth()  != depth)
    {
        _dirLightImg->set(Image::OSG_DEPTH_PF, 
                          width, height, depth, 
                          1, 1, 0.f, 
                          NULL,
                          Image::OSG_FLOAT32_IMAGEDATA, 
                          false);

        ShadowMapStore::const_iterator iter = _dirLightStore.begin();
        ShadowMapStore::const_iterator end  = _dirLightStore.end();

        for (; iter != end; ++iter)
        {
            iter->pFBO->setWidth (width);
            iter->pFBO->setHeight(height);
        }
    }

    if (getUpdateOffset())
    {
        Int32 idx = _dirLightChunkMaterial->find(_polygonChunk); // w.l.o.g.
        
        if (_pStage->getOffsetBias() != 0.f || _pStage->getOffsetFactor() != 0.f || _pStage->getCullFrontFace())
        {
            _polygonChunk->setOffsetBias  (_pStage->getOffsetBias  ());
            _polygonChunk->setOffsetFactor(_pStage->getOffsetFactor());
            _polygonChunk->setCullFace    (_pStage->getCullFrontFace() ?  GL_FRONT : GL_NONE);

            if (idx == -1)
            {
                  _dirLightChunkMaterial->addChunk(_polygonChunk);
                _pointLightChunkMaterial->addChunk(_polygonChunk);
            }
        }
        else
        {
            if (idx != -1)
            {
                  _dirLightChunkMaterial->subChunk(_polygonChunk);
                _pointLightChunkMaterial->subChunk(_polygonChunk);
            }
        }
    }
}

void MultiLightShadowTechniqueAdvanced::renderShadowMaps(RenderAction* a, DrawEnv* pEnv)
{
    MultiLightShadowStageData::LightAssocStore& vLightAssocData = _pStageData->getLightAssocData();

    UInt32 num_lights = static_cast<UInt32>(vLightAssocData.size());


    RenderPartition* pParentPart = a->getActivePartition();

    ShadowMapStore::const_iterator dir_light_iter   = _dirLightStore.begin();
    ShadowMapStore::const_iterator dir_light_end    = _dirLightStore.end();

    ShadowMapStore::const_iterator point_light_iter = _pointLightStore.begin();
    ShadowMapStore::const_iterator point_light_end  = _pointLightStore.end();

    Int32 pointShadowIndex = 0;
    Int32   dirShadowIndex = 0;

    for (UInt32 idx = 0; idx < num_lights; ++idx)
    {
        if (vLightAssocData[idx].enabled && vLightAssocData[idx].shadow)
        {
            //
            // Performance optimization: if the data for the enabled shadowing light did not
            // change, we don't need to render the particular shadow map, because it is already
            // fine from the last pass.
            //
            bool isEqualShadowData    =    _shadowData[idx].equals(   _shadowDataLast[idx], 1.E-6f);
            bool isEqualAlgorithmData = _algorithmData[idx].equals(_algorithmDataLast[idx], 1.E-6f);

            const Pnt3f& lightPosWS = _algorithmData[idx].lightPositionWS;
            bool  focused           =    _shadowData[idx].focused;
            Int32 nbrOfSplits       =    _shadowData[idx].nbrOfSplits;

            for (Int32 split = 0; split < nbrOfSplits; ++split)
            {
                const Matrix& matLSFromWS   =    _shadowData[idx].matLSFromWS  [split];
                const Matrix& matProjection = _algorithmData[idx].matProjection[split];

                const Real32  zNear         = _shadowData   [idx].zNear        [split];
                const Real32  zFar          = _shadowData   [idx].zFar         [split];

                if ( (vLightAssocData[idx].type == MultiLight::DIRECTIONAL_LIGHT     )
                  || (vLightAssocData[idx].type == MultiLight::SPOT_LIGHT            )
                  || (vLightAssocData[idx].type == MultiLight::CINEMA_LIGHT          )
                  || (vLightAssocData[idx].type == MultiLight::POINT_LIGHT && focused) 
                   )
                {
                    OSG_ASSERT(dir_light_iter != dir_light_end);
                    const ShadowMapData& data = *dir_light_iter;

                    _shadowData[idx].shadowIndex[split] = dirShadowIndex;
                    dirShadowIndex++;

                    if ( !isEqualShadowData || !isEqualAlgorithmData)
                    {
                        _pStage->pushPartition(a);
                        {
                            RenderPartition* pPart = a->getActivePartition();

                            pPart->setRenderTarget(data.pFBO);
                            pPart->setWindow(a->getWindow());
                            pPart->calcViewportDimension(0.f, 0.f, 1.f, 1.f, data.pFBO->getWidth(), data.pFBO->getHeight());

                            pPart->setupProjection(matProjection, Matrix::identity());
                            pPart->setupViewing(matLSFromWS);

                            pPart->setNear(zNear);
                            pPart->setFar (zFar);

                            pPart->calcFrustum();

                            pPart->setBackground(_clearBackground);

                            pPart->pushMatrix(a->getActNode()->getToWorld());

                            // Vertex shader
                            // None

                            // fragment shader
                            // None

                            pPart->overrideMaterial(_dirLightChunkMaterial, a->getActNode());
                            pPart->deactivateOverride();

                            recurseFromThis(a);
                            a->useNodeList(false);

                            pPart->activateOverride();
                            pPart->overrideMaterial(NULL, a->getActNode());

                            pPart->popMatrix();
                        }
                        _pStage->popPartition(a);
                    }
                    dir_light_iter++;
                }
                else
                if (vLightAssocData[idx].type == MultiLight::POINT_LIGHT)
                {
                    _shadowData[idx].shadowIndex[split] = pointShadowIndex;
                    pointShadowIndex++;

                    for (int i = 0; i < 6; ++i)
                    {
                        Matrix matLSFromWSFace(matLSFromWS);
                        matLSFromWSFace.multLeft(_matCubeFaceInv[i]);

                        OSG_ASSERT(point_light_iter != point_light_end);
                        const ShadowMapData& data = *point_light_iter;

                        if ( !isEqualShadowData || !isEqualAlgorithmData)
                        {
                            _pStage->pushPartition(a);
                            {
                                RenderPartition* pPart = a->getActivePartition();

                                pPart->setRenderTarget(data.pFBO);
                                pPart->setWindow(a->getWindow());
                                pPart->calcViewportDimension(0.f, 0.f, 1.f, 1.f, data.pFBO->getWidth (), data.pFBO->getHeight());

                                pPart->setupProjection(matProjection, Matrix::identity());
                                pPart->setupViewing(matLSFromWSFace);
                        
                                pPart->setNear(zNear);
                                pPart->setFar (zFar);

                                pPart->calcFrustum();

                                pPart->setBackground(_clearBackground);

                                // fragment shader
                                _pointLightSHLChunk->updateUniformVariable("uLightPosWS", lightPosWS);
                                _pointLightSHLChunk->updateUniformVariable("uFarPlaneWS", zFar);

                                pPart->pushMatrix(a->getActNode()->getToWorld());

                                pPart->pushMatrix(a->getActNode()->getToWorld());

                                pPart->overrideMaterial(_pointLightChunkMaterial, a->getActNode());
                                pPart->deactivateOverride();

                                recurseFromThis(a);
                                a->useNodeList(false);

                                pPart->activateOverride();
                                pPart->overrideMaterial(NULL, a->getActNode());

                                pPart->popMatrix();
                            }
                            _pStage->popPartition(a);
                        }
                        point_light_iter++;
                    }
                }
            }
        }
    }

    _algorithmDataLast = _algorithmData;
}

Int32 MultiLightShadowTechniqueAdvanced::getNbrOfSplits(Int32 shadowParamIdx)
{
    Int32 nbrOfSplits = 1;
    bool useDefault = true;

    if (shadowParamIdx >= 0 && shadowParamIdx < Int32(_pStage->getNumShadowParameters()))
    {
        MultiLightShadowParameterAdvanced* shadowParam = 
            dynamic_cast<MultiLightShadowParameterAdvanced*>(
                    _pStage->getShadowParameter(shadowParamIdx));

        if (shadowParam)
        {
            useDefault = false;
            nbrOfSplits = shadowParam->getNumberOfSplits();
        }
    }

    if (useDefault)
    {
        nbrOfSplits = _defaultShadowParameter->getNumberOfSplits();
    }

    return nbrOfSplits;
}

void MultiLightShadowTechniqueAdvanced::calcMaxNbrOfSplits()
{
    _maxNbrOfSplits = 1;

    MultiLightShadowStageData::LightAssocStore& vLightAssocData = _pStageData->getLightAssocData();
    std::size_t szAssocData = vLightAssocData.size();

    for (UInt32 idx = 0; idx < szAssocData; ++idx)
    {
        if (vLightAssocData[idx].enabled && vLightAssocData[idx].shadow)
        {
            Int32 shadowParamIdx = vLightAssocData[idx].shadowParamIdx;

            Int32 nbrOfSplits = getNbrOfSplits(shadowParamIdx);

            _maxNbrOfSplits = osgMax(_maxNbrOfSplits, nbrOfSplits);
        }
    }
}

//
// The algorithm control variables are defined by the parameter index of a particular light.
// That is, each light does might define an index into the array of shadow parameter instances
// stored in the multi light shadow stage.
//
void MultiLightShadowTechniqueAdvanced::initShadowAlgorithmState(
    MultiLightChunk* pMLChunk, 
    UInt32           lightIdx,
    bool             isOrthoCamera)
{
    _type      = pMLChunk->getType(lightIdx);
    _direction = pMLChunk->getDirection(lightIdx);

    bool useDefault = true;
    Int32 shadowParamIdx = pMLChunk->getShadowParameterIndex(lightIdx);
    if (shadowParamIdx >= 0 && shadowParamIdx < Int32(_pStage->getNumShadowParameters()))
    {
        MultiLightShadowParameterAdvanced* shadowParam = 
            dynamic_cast<MultiLightShadowParameterAdvanced*>(
                    _pStage->getShadowParameter(shadowParamIdx));

        if (shadowParam)
        {
            useDefault = false;

            _nbrOfSplits         = shadowParam->getNumberOfSplits();
            _useLiSP             = shadowParam->getUseLiSP();
            _useGS               = shadowParam->getUseGeometryShader();
            _liSPMode            = shadowParam->getLiSPMode();
            _focusing            = shadowParam->getFocusing();
            _reduceSwimming      = shadowParam->getReduceSwimming();
            _updateLightUp       = shadowParam->getLightSpaceAlignment();
            _useMinDepth         = shadowParam->getUseMinDepth();
            _useBestResSelection = shadowParam->getUseBestResSelection();
            _warpingParameter    = shadowParam->getWarpingParameter();
            _lambda              = shadowParam->getSplitParamterLambda();
            _zNear               = shadowParam->getZNear();
            _pseudoNear          = shadowParam->getPseudoNear();
            _pseudoFar           = shadowParam->getPseudoFar();
        }
    }

    if (useDefault)
    {
        // No shadow parameter defined but shadow parameter => use default
        _nbrOfSplits         = _defaultShadowParameter->getNumberOfSplits();
        _useLiSP             = _defaultShadowParameter->getUseLiSP();
        _useGS               = _defaultShadowParameter->getUseGeometryShader();
        _liSPMode            = _defaultShadowParameter->getLiSPMode();
        _focusing            = _defaultShadowParameter->getFocusing();
        _reduceSwimming      = _defaultShadowParameter->getReduceSwimming();
        _updateLightUp       = _defaultShadowParameter->getLightSpaceAlignment();
        _useMinDepth         = _defaultShadowParameter->getUseMinDepth();
        _useBestResSelection = _defaultShadowParameter->getUseBestResSelection();
        _warpingParameter    = _defaultShadowParameter->getWarpingParameter();
        _lambda              = _defaultShadowParameter->getSplitParamterLambda();
        _zNear               = _defaultShadowParameter->getZNear();
        _pseudoNear          = _defaultShadowParameter->getPseudoNear();
        _pseudoFar           = _defaultShadowParameter->getPseudoFar();
    }

    adjustShadowAlgorithmState(isOrthoCamera);

    if (_useLiSP)
        _liSP = LiSPSMTechnique(_nbrOfSplits);
}

//
// This function checks the light requested algorithm state and
//
void MultiLightShadowTechniqueAdvanced::adjustShadowAlgorithmState(bool isOrthoCamera)
{
    if (_focusing || _useLiSP || _nbrOfSplits > 1)
    {
        _focusing = true;
    }

    if (!_focusing)
    {
        _useLiSP     = false;
        _nbrOfSplits = 1;
    }

    if (isOrthoCamera)
    {
        _useLiSP = false;
    }
}

bool MultiLightShadowTechniqueAdvanced::isFocusingFeasable() const
{
    bool feasable = false;

    switch (_type)
    {
        case MultiLight::DIRECTIONAL_LIGHT:
            feasable = true;
            break;
        case MultiLight::POINT_LIGHT:
            break;
        case MultiLight::SPOT_LIGHT:
        case MultiLight::CINEMA_LIGHT:
            break;
    }

    return feasable;
}

void MultiLightShadowTechniqueAdvanced::updateLDirVDirAngle()
{
    Vec3f eViewDir =   _camView.getDirection();
    Vec3f lViewDir = _lightView.getDirection();

    _gamma = osgRad2Degree(osgACos(osgAbs(eViewDir.dot(lViewDir))));
}

Real32 MultiLightShadowTechniqueAdvanced::getMinDepth()
{
    // Implementation still missing
    Real32 minDepth = 0.f;
    return minDepth;
}

void MultiLightShadowTechniqueAdvanced::adjustCameraPlanes(
    const BoxVolume&     sceneBB, 
    const FrustumVolume& camFrust, 
    Real32&              nearDist, 
    Real32&              farDist) const
{
    PolygonBody body;

    body.add(camFrust);
    body.clip(sceneBB);

    body.createUniqueVertices();

    const PolygonBody::VecVerticesT& vertices = body.getVertices();

    std::size_t size = body.getNumVertices();

    Real32 maxZ = 0.f;
    Real32 minZ = TypeTraits<Real32>::getMax();

    const Pnt3f& eye     = _camView.getEye();
    const Vec3f  viewDir = _camView.getDirection();

    //
    // for each point in body
    //
    for (std::size_t i = 0; i < size; ++i)
    {
        const Vec3f  toCam = vertices[i] - eye;
        const Real32 dist  = toCam.dot(viewDir);
        //
        // find boundary values
        //
        maxZ = osgMax(dist, maxZ);
        minZ = osgMin(dist, minZ);
    }

    //
    // use smallest distance as new near plane
    // and make sure it is not too small
    //
    nearDist = osgMax(minZ, nearDist + _zNear);

    //
    // use largest distance as new far plane
    // and make sure it is larger than zNear
    //
    farDist = osgMax(maxZ, nearDist + 1.f);
}

void MultiLightShadowTechniqueAdvanced::calcSplitPositions(
    UInt32 idx,
    Real32 zNear, 
    Real32 zFar)
{
    _shadowData[idx].splitPositions[0]            = zNear;
    _shadowData[idx].splitPositions[_nbrOfSplits] = zFar;
    
    Real32 n = zNear;
    Real32 f = zFar;

    if (_nbrOfSplits > 1)
    {
        n +=        _pseudoNear  * (zFar - zNear);
        f -= (1.f - _pseudoFar)  * (zFar - zNear);
    }

    for (Int32 i = 1; i < _nbrOfSplits; ++i)
    {
        Real32 s    =  i / static_cast<Real32>(_nbrOfSplits);
        Real32 cLog = n * osgPow(f / n, s);
        Real32 cUni = n + (f - n) * s;

        _shadowData[idx].splitPositions[i] = (1.f - _lambda) * cUni + _lambda * cLog;
    }
}

void MultiLightShadowTechniqueAdvanced::calcPolygonBody(
    PolygonBody&         body, 
    Projection::Type     projectionType,
    const BoxVolume&     sceneBB,
    const FrustumVolume& camFrust,
    const FrustumVolume& lightFrust) const
{
    body.add(camFrust);

    if (projectionType == Projection::PERSPECTIVE)
    {
        if (_focusing)
        {
            body.clip(sceneBB);
            body.createConvexHull(_lightView.getEye());
            body.clip(lightFrust);
            body.clip(sceneBB);
        }
        else
        {
            body.createConvexHull(_lightView.getEye());
        }

        body.createUniqueVertices();
    }
    else
    {
        if (_focusing)
        {
            body.clip(sceneBB);
        }

        body.extrude(-_lightView.getDirection(), sceneBB);
    }
}

void MultiLightShadowTechniqueAdvanced::calcLightViewProjMat(
    Matrix&            matNewProjection, 
    Matrix&            matNewProjLSFromWS, 
    Int32              split, 
    const PolygonBody& body, 
    const Matrix&      matProjection, 
    const Matrix&      matLSFromWS)
{
    Matrix matTSFromWS = matProjection;
    matTSFromWS.mult(matLSFromWS);

    BoxVolume bodyBB;

    const PolygonBody::VecVerticesT& vertices = body.getVertices();

    PolygonBody::VecVerticesT::const_iterator iter = vertices.begin();
    PolygonBody::VecVerticesT::const_iterator end  = vertices.end();

    for (; iter != end; ++iter)
    {
        Pnt3f pnt = *iter;
        matTSFromWS.multFull(*iter, pnt);
        bodyBB.extendBy(pnt);
    }

    Pnt3f maximum = bodyBB.getMax();
    Pnt3f minimum = bodyBB.getMin();

    //
    // maximize z for more robust shadows to avoid unwanted far plane clipping
    //
    maximum[2] = 1.f;

    Real32 diffX = maximum.x() - minimum.x();
    Real32 diffY = maximum.y() - minimum.y();
    Real32 diffZ = maximum.z() - minimum.z();

    Real32 sumX = maximum.x() + minimum.x();
    Real32 sumY = maximum.y() + minimum.y();

    Vec3f scale (  2.f / diffX,   2.f / diffY,          1.f / diffZ);
    Vec3f offset(-sumX / diffX, -sumY / diffY, -minimum.z() / diffZ);

    if ( _reduceSwimming && !(_useLiSP || _updateLightUp) )
    {
        Real32 scaleQuantizer = 64.f;

        scale[0] = 1.f / osgCeil(1.f / scale.x() * scaleQuantizer) * scaleQuantizer;
        scale[1] = 1.f / osgCeil(1.f / scale.y() * scaleQuantizer) * scaleQuantizer;

        offset[0] = -0.5f * (sumX) * scale.x();
        offset[1] = -0.5f * (sumY) * scale.y();

        Real32 halfTexSzX = 0.5f * _pStage->getShadowMapWidth();
        Real32 halfTexSzY = 0.5f * _pStage->getShadowMapHeight();

        offset[0] = osgCeil(offset.x() * halfTexSzX) / halfTexSzX;
        offset[1] = osgCeil(offset.y() * halfTexSzY) / halfTexSzY;
    }

    Matrix scaleTranslate(
                            scale.x(),   0.f,     0.f,   offset.x(),
                              0.f,   scale.y(),   0.f,   offset.y(),
                              0.f,     0.f,   scale.z(), offset.z(),
                              0.f,     0.f,     0.f,     1.f
                         );

    matNewProjection = matProjection;

    if (_useLiSP || _nbrOfSplits > 1 || _focusing)
        matNewProjection.multLeft(scaleTranslate);

    matNewProjLSFromWS = matNewProjection;
    matNewProjLSFromWS.mult(matLSFromWS);
}

bool MultiLightShadowTechniqueAdvanced::isOrthographicCamera(Camera* camera) const
{
    const OrthographicCamera* pOrthoCamera = dynamic_cast<const OrthographicCamera*>(camera);
    if (pOrthoCamera)
    {
        return true;
    }
    else
    {
        const PerspectiveCamera* pPerspCamera = dynamic_cast<const PerspectiveCamera*>(camera);
        if (pPerspCamera)
        {
            return false;
        }
        else
        {
            Matrix matCamProjection;
            camera->getProjection(matCamProjection, 10,10);
            Real32 m32 = matCamProjection[2][3];
            if (osgAbs(m32) <= 1.E-6)
            {
                return true;
            }
        }
    }
    return false;
}

std::string MultiLightShadowTechniqueAdvanced::getPointLightVertProgram() const
{
    using namespace std;

    stringstream ost;

    ost     << "#version 330 compatibility"
    << endl << ""
    << endl << "uniform mat4 OSGWorldMatrix;"
    << endl << ""
    << endl << "smooth out vec4 fragPosWS;"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    fragPosWS   =  OSGWorldMatrix * gl_Vertex;"
    << endl << "    gl_Position = ftransform();"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

std::string MultiLightShadowTechniqueAdvanced::getPointLightFragProgram() const
{
    using namespace std;

    stringstream ost;

    ost     << "#version 330 compatibility"
    << endl << ""
    << endl << "smooth in vec4 fragPosWS;"
    << endl << ""
    << endl << "uniform vec3  uLightPosWS;"
    << endl << "uniform float uFarPlaneWS;"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    float lightDistanceWS = length(fragPosWS.xyz - uLightPosWS);"
    << endl << ""
    << endl << "    // map to [0;1] range"
    << endl << "    lightDistanceWS = lightDistanceWS / uFarPlaneWS;"
    << endl << ""
    << endl << "    gl_FragDepth = lightDistanceWS;"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

std::string MultiLightShadowTechniqueAdvanced::getDirLightVertProgram() const
{
    using namespace std;

    stringstream ost;

    ost     << "#version 330 compatibility"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    gl_Position = ftransform();"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

std::string MultiLightShadowTechniqueAdvanced::getDirLightFragProgram() const
{
    using namespace std;

    stringstream ost;

    ost     << "#version 330 compatibility"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    gl_FragDepth = gl_FragCoord.z;"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

std::string MultiLightShadowTechniqueAdvanced::getFragmentProgramSnippet() const
{
    using namespace std;

    stringstream ost;

    MultiLightChunk* pMLChunk = _pStage->getMultiLightChunk();

    // GL_TEXTURE_CUBE_MAP_ARRAY OpenGL 4.0/4.6 ARB_texture_cube_map_array
    // GL_TEXTURE_2D_ARRAY       OpenGL 3.0/4.6 EXT_texture_array
     
    ost     << "#version 330 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_shader_storage_buffer_object: enable"
    << endl << "#extension GL_ARB_texture_cube_map_array:       enable"
    << endl << "#extension GL_EXT_texture_array:                enable"
    << endl << ""
    << pMLChunk->getFragmentProgramSnippet(false, false)  // Light struct declaration only
    << endl << ""
    << endl << "uniform samplerCubeArray uShadowMapPnt;"
    << endl << "uniform sampler2DArray   uShadowMapDir;"
    << endl << ""
    << endl << "uniform samplerCubeArrayShadow uShadowMapPntComp;"
    << endl << "uniform sampler2DArrayShadow   uShadowMapDirComp;"
    << endl << ""
    << endl << "uniform bool  uShadowEnabled;"
    << endl << "uniform bool  uUseShadowSampler;"
    << endl << ""
    << endl << "struct ShadowData"
    << endl << "{"
    << endl << "    int   nbrOfSplits;"
    << endl << "    bool  focused;"
    << endl << "    vec3  lightPosDir;"
    << endl << "    mat4  matLSFromWS["     << _maxNbrOfSplits << "];"
    << endl << "    mat4  matTSFromWS["     << _maxNbrOfSplits << "];"
    << endl << "    vec2  frustumSize["     << _maxNbrOfSplits << "];"
    << endl << "    float zNear["           << _maxNbrOfSplits << "];"
    << endl << "    float zFar["            << _maxNbrOfSplits << "];"
    << endl << "    int   shadowIndex["     << _maxNbrOfSplits << "];"
    << endl << "    float splitPositions["  << _maxNbrOfSplits << "];"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430) buffer ShadowDataBlock"
    << endl << "{"
    << endl << "    ShadowData data[];"
    << endl << "} shadowDataBlock;"
    << endl << ""
    << endl << "struct ShadowParameter"
    << endl << "{"
    << endl << "    float intensity;"
    << endl << "    float bias;"
    << endl << "    int   filterMode;"
    << endl << "    float filterRadius;"
    << endl << "    bool  randomRotateFilter;"
    << endl << "    bool  useBlockerSearch;"
    << endl << "    bool  usePCSS;"
    << endl << "};"
    << endl << ""
    << endl << "layout (std140) uniform ShadowParameterBlock"
    << endl << "{"
    << endl << "    ShadowParameter param[" << osgMax(1U, _pStage->getNumShadowParameters()) << "];"
    << endl << "} shadowParamBlock;"
    << endl << ""
    << endl << "layout (std140) uniform DistributionBlock"
    << endl << "{"
    << endl << "    int  boxFilterSize;"
    << endl << "    int  boxSearchSize;"
    << endl << "    vec2 filterDisk[" << getAdaptedFilterDiskSize() << "];"
    << endl << "    vec2 searchDisk[" << getAdaptedSearchDiskSize() << "];"
    << endl << "} distribution;"
    << endl << ""
    << endl << "int getSplitIndex(in int dataIdx, in float z_LS)"
    << endl << "{"
    << endl << "    int max_split = shadowDataBlock.data[dataIdx].nbrOfSplits - 1;"
    << endl << "    int     split = 0;"
    << endl << ""
    << endl << "    while (split < max_split && z_LS > shadowDataBlock.data[dataIdx].splitPositions[split])"
    << endl << "    {"
    << endl << "        split++;"
    << endl << "    }"
    << endl << "    return split;"
    << endl << "}"
    << endl << ""
    //<< endl << Shader::getEqualEpsDeclSnippet()
    //<< endl << Shader::getEqualDefaultTestMatrixSnippet()
    << endl << ""
    << endl << getShadowBaseProgramSnippet()
    << endl << ""
    << endl << "float _shadowCalculationPoint("
    << endl << "    in float fragDepthES,"
    << endl << "    in vec3  fragPosWS,"
    << endl << "    in vec3  normalWS,"
    << endl << "    in vec3  lightDirWS,"
    << endl << "    in int   dataIdx,"
    << endl << "    in int   paramIdx)"
    << endl << "{"
    << endl << "    ShadowData      data  = shadowDataBlock .data [dataIdx ];"
    << endl << "    ShadowParameter param = shadowParamBlock.param[paramIdx];"
    << endl << ""
    << endl << "    int   split       = 0;"  //  Point lights are not splitted.
    << endl << "    int   layerIdx    = data.shadowIndex[split];"
    << endl << "    float zNear       = data.zNear[split];"
    << endl << "    float zFar        = data.zFar[split];"
    << endl << "    vec2  frustumSize = data.frustumSize[split];"
    << endl << "    float layer       = float(layerIdx);"
    << endl << ""
    << endl << "    vec3  projDir  = normalize(lightDirWS);"
    << endl << "    float cosTheta = clamp(dot(normalWS, -projDir), 0.0, 1.0);"
    << endl << "    float factor   = tan(acos(cosTheta));"
    << endl << "    float bias     = param.bias * clamp(factor, 1.0, 100.0);"
    << endl << ""
    << endl << "    float fragDepthLS = length(lightDirWS);"
    << endl << "    float zReceiver   = fragDepthLS / zFar;"
    << endl << ""
    << endl << "    vec2 filterRadius = vec2(param.filterRadius, param.filterRadius);"
    << endl << ""
    << endl << "    float sin_a  = 0.0;"
    << endl << "    float cos_a  = 1.0;"
    << endl << ""
    << endl << "    if (param.randomRotateFilter)"
    << endl << "    {"
    << endl << "        float angle = randomAngle(fragPosWS.xyz, 5000);"
    << endl << ""
    << endl << "        sin_a = sin(angle);"
    << endl << "        cos_a = cos(angle);"
    << endl << "    }"
    << endl << "    else"
    << endl << "    {"
    << endl << "        sin_a = 0.0;"
    << endl << "        cos_a = 1.0;"
    << endl << "    }"
    << endl << ""
    << endl << "    FilterParameter filterParam = FilterParameter("
    << endl << "                                        zReceiver, bias, fragDepthLS,"
    << endl << "                                        zNear, zFar,"
    << endl << "                                        filterRadius, frustumSize,"
    << endl << "                                        param.useBlockerSearch,"
    << endl << "                                        param.usePCSS,"
    << endl << "                                        true,"
    << endl << "                                        sin_a, cos_a);"
    << endl << ""
    << endl << "    float shadow = calcPCFShadowPnt("
    << endl << "                        param.filterMode,"
    << endl << "                        layer,"
    << endl << "                        projDir,"
    << endl << "                        filterParam);"
    << endl << "    return clamp(shadow, param.intensity, 1.0);"
    << endl << "}"
    << endl << ""
    << endl << "float _shadowCalculationSpot("
    << endl << "    in float fragDepthES,"
    << endl << "    in vec3  fragPosWS,"
    << endl << "    in vec3  normalWS,"
    << endl << "    in vec3  lightDirWS,"
    << endl << "    in int   dataIdx,"
    << endl << "    in int   paramIdx,"
    << endl << "    in bool  isPerspective)"
    << endl << "{"
    << endl << "    ShadowData      data  = shadowDataBlock .data [dataIdx ];"
    << endl << "    ShadowParameter param = shadowParamBlock.param[paramIdx];"
    << endl << ""
    << endl << "    int   split       = getSplitIndex(dataIdx, -fragDepthES);"
    << endl << "    int   layerIdx    = data.shadowIndex[split];"
    << endl << "    float zNear       = data.zNear[split];"
    << endl << "    float zFar        = data.zFar[split];"
    << endl << "    vec2  frustumSize = data.frustumSize[split];"
    << endl << "    mat4  matTSFromWS = data.matTSFromWS[split];"
    << endl << "    float layer       = float(layerIdx);"
    << endl << ""
    << endl << "    float cosTheta  = clamp(dot(normalWS, -normalize(lightDirWS)), 0.0, 1.0);"
    << endl << "    float factor    = tan(acos(cosTheta));"
    << endl << "    float bias      = param.bias * clamp(factor, 1.0, 100.0);"
    << endl << ""
    << endl << "    vec3  fragPosTS   = getShadowCoords(matTSFromWS, fragPosWS);"
    << endl << "    vec2  uv          = fragPosTS.xy;"
    << endl << "    float zReceiver   = fragPosTS.z;"
    << endl << "    float fragDepthLS = -(data.matLSFromWS[split] * vec4(fragPosWS, 1.0)).z;"
    << endl << ""
    << endl << "    vec2 filterRadius = vec2(param.filterRadius, param.filterRadius);"
    << endl << ""
    << endl << "    float sin_a  = 0.0;"
    << endl << "    float cos_a  = 1.0;"
    << endl << ""
    << endl << "    if (param.randomRotateFilter)"
    << endl << "    {"
    << endl << "        float angle = randomAngle(fragPosWS.xyz, 5000);"
    << endl << ""
    << endl << "        sin_a = sin(angle);"
    << endl << "        cos_a = cos(angle);"
    << endl << "    }"
    << endl << "    else"
    << endl << "    {"
    << endl << "        sin_a = 0.0;"
    << endl << "        cos_a = 1.0;"
    << endl << "    }"
    << endl << ""
    << endl << "    FilterParameter filterParam = FilterParameter("
    << endl << "                                        zReceiver, bias, fragDepthLS,"
    << endl << "                                        zNear, zFar,"
    << endl << "                                        filterRadius, frustumSize,"
    << endl << "                                        param.useBlockerSearch,"
    << endl << "                                        param.usePCSS,"
    << endl << "                                        isPerspective,"
    << endl << "                                        sin_a, cos_a);"
    << endl << ""
    << endl << "    float shadow = calcPCFShadowDir("
    << endl << "                        param.filterMode,"
    << endl << "                        layer,"
    << endl << "                        uv,"
    << endl << "                        filterParam);"
    << endl << "    return clamp(shadow, param.intensity, 1.0);"
    << endl << "}"
    << endl << ""
    << getDispatchProgramSnippet()
    << endl << ""
    << endl;

    return ost.str();
}

std::string MultiLightShadowTechniqueAdvanced::getDispatchProgramSnippet() const
{
    using namespace std;

    stringstream ost;

    ost     << "float shadowAttenuationDirectionalLight("
    << endl << "    in float fragDepthES,"
    << endl << "    in vec3  fragPosWS,"
    << endl << "    in vec3  normalWS,"
    << endl << "    in Light light)"
    << endl << "{"
    << endl << "    if (!light.shadow || !uShadowEnabled)"
    << endl << "        return 1.0;"
    << endl << ""
    << endl << "    int dataIdx     = light.shadowDataIndex;"
    << endl << "    int paramIdx    = light.shadowParameterIndex;"
    << endl << "    vec3 lightDirWS = light.direction;"
    << endl << ""
    << endl << "    return _shadowCalculationSpot(fragDepthES, fragPosWS, normalWS, lightDirWS, dataIdx, paramIdx, false);"
    << endl << "}"
    << endl << ""
    << endl << "float shadowAttenuationPointLight("
    << endl << "    in float fragDepthES,"
    << endl << "    in vec3  fragPosWS,"
    << endl << "    in vec3  normalWS,"
    << endl << "    in Light light)"
    << endl << "{"
    << endl << "    if (!light.shadow || !uShadowEnabled)"
    << endl << "        return 1.0;"
    << endl << ""
    << endl << "    int dataIdx     = light.shadowDataIndex;"
    << endl << "    int paramIdx    = light.shadowParameterIndex;"
    << endl << "    vec3 lightDirWS = fragPosWS - light.position;"
    << endl << "    bool focused    = shadowDataBlock.data[dataIdx].focused;"
    << endl << ""
    << endl << "    float shadow = focused"
    << endl << "            ? _shadowCalculationSpot (fragDepthES, fragPosWS, normalWS, lightDirWS, dataIdx, paramIdx, true)"
    << endl << "            : _shadowCalculationPoint(fragDepthES, fragPosWS, normalWS, lightDirWS, dataIdx, paramIdx)"
    << endl << "            ;"
    << endl << "    return shadow;"
    << endl << "}"
    << endl << ""
    << endl << "float shadowAttenuationSpotLight("
    << endl << "    in float fragDepthES,"
    << endl << "    in vec3  fragPosWS,"
    << endl << "    in vec3  normalWS,"
    << endl << "    in Light light)"
    << endl << "{"
    << endl << "    if (!light.shadow || !uShadowEnabled)"
    << endl << "        return 1.0;"
    << endl << ""
    << endl << "    int dataIdx     = light.shadowDataIndex;"
    << endl << "    int paramIdx    = light.shadowParameterIndex;"
    << endl << "    vec3 lightDirWS = fragPosWS - light.position;"
    << endl << ""
    << endl << "    return _shadowCalculationSpot(fragDepthES, fragPosWS, normalWS, lightDirWS, dataIdx, paramIdx, true);"
    << endl << "}"
    << endl << ""
    << endl << "float shadowAttenuationCinemaLight("
    << endl << "    in float fragDepthES,"
    << endl << "    in vec3  fragPosWS,"
    << endl << "    in vec3  normalWS,"
    << endl << "    in Light light)"
    << endl << "{"
    << endl << "    if (!light.shadow || !uShadowEnabled)"
    << endl << "        return 1.0;"
    << endl << ""
    << endl << "    int dataIdx     = light.shadowDataIndex;"
    << endl << "    int paramIdx    = light.shadowParameterIndex;"
    << endl << "    vec3 lightDirWS = fragPosWS - light.position;"
    << endl << ""
    << endl << "    return _shadowCalculationSpot(fragDepthES, fragPosWS, normalWS, lightDirWS, dataIdx, paramIdx, true);"
    << endl << "}"
    << endl << ""
    << endl << Shader::getColorsSnippet()
    << endl << ""
    << endl << "vec4 shadowSplitIndexTest(in float fragDepthES, in Light light)"
    << endl << "{"
    << endl << "    if (!light.shadow || !uShadowEnabled || !light.enabled)"
    << endl << "        return vec4(0);"
    << endl << ""
    << endl << "    int split = getSplitIndex(light.shadowDataIndex, -fragDepthES);"
    << endl << "    return OSGGetHeatColor(split, 4, 6, 28);"
    << endl << "}"
    << endl << ""
    << endl << "bool shadowTestShader(in int idx, in Light light)"
    << endl << "{"
    << endl << "    return true;"
    << endl << "}"
    ;
    return ost.str();
}

OSG_END_NAMESPACE
