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

#include "OSGMultiLightShadowTechniqueSimplest.h"
#include "OSGRenderAction.h"
#include "OSGMultiLightChunk.h"
#include "OSGMultiLightShadowStage.h"
#include "OSGMultiLightShadowStageData.h"
#include "OSGMultiLightShadowParameter.h"

#include "OSGMaterialChunk.h"
#include "OSGColorMaskChunk.h"
#include "OSGPolygonChunk.h"

#include "OSGShaderUtility.h"

OSG_BEGIN_NAMESPACE

bool MultiLightShadowTechniqueSimplest::_initExtenstions = false;

UInt32 MultiLightShadowTechniqueSimplest::_uiTextureCubeMapArrayARB      = Window::invalidExtensionID;
UInt32 MultiLightShadowTechniqueSimplest::_uiTextureArrayEXT             = Window::invalidExtensionID;
UInt32 MultiLightShadowTechniqueSimplest::_uiGeometryShader4ARB          = Window::invalidExtensionID;

UInt32 MultiLightShadowTechniqueSimplest::_uiFuncFramebufferTextureLayer = Window::invalidFunctionID;

void MultiLightShadowTechniqueSimplest::initializeExtensions()
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

UInt32 MultiLightShadowTechniqueSimplest::getRequiredMultiLightFeatures()
{
    UInt32 required = 
          MultiLight::HAS_SHADOW
        ;

    return required;
}

MultiLightShadowTechniqueSimplest::MultiLightShadowTechniqueSimplest(
    MultiLightShadowStage     *pStage,
    MultiLightShadowStageData *pData,
    Window                    *pWindow)
: Inherited                 (pStage, pData, pWindow)
, _pointLightStore          ()
, _pointLightTexObj         (NULL)
//, _pointLightSampleObj      (NULL)
, _pointLightImgPX          (NULL)
, _pointLightImgMX          (NULL)
, _pointLightImgPY          (NULL)
, _pointLightImgMY          (NULL)
, _pointLightImgPZ          (NULL)
, _pointLightImgMZ          (NULL)
, _pointLightSHLChunk       (NULL)
, _pointLightChunkMaterial  (NULL)
, _dirLightStore            ()
, _dirLightTexObj           (NULL)
//, _dirLightSampleObj        (NULL)
, _dirLightImg              (NULL)
, _dirLightSHLChunk         (NULL)
, _dirLightChunkMaterial    (NULL)
, _shadowData               ()
, _shadowDataLast           ()
, _defaultShadowParameter   (NULL)
{
    _uiMode = MultiLightShadowStage::SIMPLE_TEST_SHADOW_MAP;

    //
    // Reset to allow mode switching
    //
    pData->setOverrideProgChunk(NULL);
    pData->setOverrideProgram  (NULL);

    _defaultShadowParameter = MultiLightShadowParameter::createLocal();
}

MultiLightShadowTechniqueSimplest::~MultiLightShadowTechniqueSimplest()
{
}

void MultiLightShadowTechniqueSimplest::initialize(RenderAction* a, DrawEnv* pEnv)
{
    MultiLightChunk* pMLChunk = _pStage->getMultiLightChunk();

    bool check = pMLChunk->checkFeatures(getRequiredMultiLightFeatures());
    OSG_ASSERT(check);

    initLimits(a->getWindow());
}

bool MultiLightShadowTechniqueSimplest::hasExtOrVersion(RenderAction* a)
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

void MultiLightShadowTechniqueSimplest::adaptShadowDataLayout(UInt32 num_lights)
{
    //
    // Force the number of shadow data entries to be the same as the number of lights.
    // In principal we could go with only so many shadow data entries as their are active
    // shadow casting lights. However, that did not work so well and resulted in flickering
    // of the rendered scene when disabeling or enabeling a light, because then all shadow
    // maps would be regenerated. The brute force approach seems to be superior.
    //
    if (num_lights != _shadowData.size())
    {
        _shadowData.resize(num_lights);
    }
}

std::size_t MultiLightShadowTechniqueSimplest::calcShadowDataBufferSize() const
{
    UInt32 numShadowData = static_cast<UInt32>(_shadowData.size());

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    //struct ShadowData
    //{
    //    mat4  matLSFromWS;
    //    mat4  matTSFromWS;
    //    vec2  frustumSize;
    //    float zNear;
    //    float zFar;
    //    int   shadowIndex;
    //};

    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);  // Matrix  matLSFromWS
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
    ao = alignOffset(16, bo); bo = ao;

    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);  // Matrix  matTSFromWS
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
    ao = alignOffset(16, bo); bo = ao;
    
    ao = alignOffset( 8, bo); bo = ao + sizeof(Vec2f);  // Vec2f   frustumSize

    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32); // Real32  zNear
    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32); // Real32  zFar
    ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);  // Int32   shadowIndex

    ao = alignOffset(16, bo); bo = ao;                  // padding

    ao *= numShadowData;      bo = ao;                  // array
    ao = alignOffset(16, bo); bo = ao;                  // padding

    return ao;
}

std::vector<UInt8> MultiLightShadowTechniqueSimplest::createShadowDataBuffer() const
{
    std::size_t size = calcShadowDataBufferSize();

    std::vector<UInt8> buffer(size);

    UInt32 numShadowData = static_cast<UInt32>(_shadowData.size());

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (UInt32 idx = 0; idx < numShadowData; ++idx)
    {
        const Matrix& matLSFromWS = _shadowData[idx].matLSFromWS;
        const Matrix& matTSFromWS = _shadowData[idx].matTSFromWS;
        const Vec2f&  frustumSize = _shadowData[idx].frustumSize;
        Real32        zNear       = _shadowData[idx].zNear;
        Real32        zFar        = _shadowData[idx].zFar;
        Int32         shadowIndex = _shadowData[idx].shadowIndex;

        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[0][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[1][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[2][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[3][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); bo = ao;

        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matTSFromWS[0][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matTSFromWS[1][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matTSFromWS[2][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matTSFromWS[3][0], sizeof(Vec4f));  bo = ao + sizeof(Vec4f);
        ao = alignOffset(16, bo); bo = ao;
        
        ao = alignOffset( 8, bo); memcpy(&buffer[0] + ao, &frustumSize[0],    sizeof(Vec2f));  bo = ao + sizeof(Vec2f);

        ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = zNear;       bo = ao + sizeof(Real32);
        ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = zFar;        bo = ao + sizeof(Real32);
        ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = shadowIndex; bo = ao + sizeof( Int32);

        ao = alignOffset(16, bo); bo = ao;    // padding
    }

    return buffer;
}

void MultiLightShadowTechniqueSimplest::updateShadowDataState()
{
    if (_shadowData != _shadowDataLast)
    {
        std::vector<UInt8> buffer = createShadowDataBuffer();
        _shadowDataChunk->editMFBuffer()->setValues(buffer);

        _shadowDataLast = _shadowData;
    }
}

std::size_t MultiLightShadowTechniqueSimplest::calcShadowParamBufferSize() const
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

std::vector<UInt8> MultiLightShadowTechniqueSimplest::createShadowParamBuffer() const
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
        
        ao = alignOffset(16, bo); bo = ao;    // padding
    }

    return buffer;
}

void MultiLightShadowTechniqueSimplest::updateShadowParamState()
{
    if (getUpdateShadowParameter())
    {
        std::vector<UInt8> buffer = createShadowParamBuffer();
        _shadowParamChunk->editMFBuffer()->setValues(buffer);
    }
}

void MultiLightShadowTechniqueSimplest::initializeAssocData(UInt32 idx) const
{
    // empty implementation: variation detail not used for technique
}

void MultiLightShadowTechniqueSimplest::createCamera(
    MultiLight::Type type, 
    CameraUnrecPtr&  camera) const
{
    // empty implementation: variation detail not used for technique
}

bool MultiLightShadowTechniqueSimplest::changedShadowParameter(
    FieldContainer*     pFC, 
    ConstFieldMaskArg   whichField, 
    UInt32              origin)
{
    bool changed = Inherited::changedShadowParameter(pFC, whichField, origin);
    return changed;
}

void MultiLightShadowTechniqueSimplest::render(RenderAction* a, DrawEnv* pEnv)
{
    initialize(a, pEnv);

    initOverrideShaderProgram(a, pEnv);
    updateOverrideShaderProgram();

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

void MultiLightShadowTechniqueSimplest::initOverrideShaderProgram(RenderAction* a, DrawEnv* pEnv)
{
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

void MultiLightShadowTechniqueSimplest::updateOverrideShaderProgram()
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

void MultiLightShadowTechniqueSimplest::addOverride(RenderAction* a, DrawEnv* pEnv)
{
    Int32 iPLTextureUnit       = getSamplerCubeArrayTextureUnit();
    Int32 iDLTextureUnit       = getSampler2DArrayTextureUnit();
    Int32 iPLShadowTextureUnit = getSamplerCubeArrayShadowTextureUnit();
    Int32 iDLShadowTextureUnit = getSampler2DArrayShadowTextureUnit();
    Int32 iShadowDataDBndPnt   = getShadowDataBindingPnt();
    Int32 iShadowParamBndPnt   = getShadowParameterBindingPnt();
    Int32 iDistributionBndPnt  = getDistributionBindingPnt();

    if (   _pointLightTexObj) a->addOverride(    _pointLightTexObj->getClassId() + iPLTextureUnit,       _pointLightTexObj);
    if (     _dirLightTexObj) a->addOverride(      _dirLightTexObj->getClassId() + iDLTextureUnit,         _dirLightTexObj);

    if (   _pointLightTexObj) a->addOverride(    _pointLightTexObj->getClassId() + iPLShadowTextureUnit, _pointLightTexObj);
    if (     _dirLightTexObj) a->addOverride(      _dirLightTexObj->getClassId() + iDLShadowTextureUnit,   _dirLightTexObj);

    //if (_pointLightSampleObj) a->addOverride( _pointLightSampleObj->getClassId() + iPLShadowTextureUnit, _pointLightSampleObj);
    //if (  _dirLightSampleObj) a->addOverride(   _dirLightSampleObj->getClassId() + iDLShadowTextureUnit,   _dirLightSampleObj);

    if (    _shadowDataChunk) a->addOverride(     _shadowDataChunk->getClassId() + iShadowDataDBndPnt,     _shadowDataChunk);
    if (   _shadowParamChunk) a->addOverride(    _shadowParamChunk->getClassId() + iShadowParamBndPnt,    _shadowParamChunk);
    if (  _distributionChunk) a->addOverride(   _distributionChunk->getClassId() + iDistributionBndPnt,  _distributionChunk);

    if (_pStage->getDisableOverride() == false)
    {
        a->addOverride(ShaderProgramChunk::getStaticClassId(), _pStageData->getOverrideProgChunk());
    }
}

void MultiLightShadowTechniqueSimplest::initShadowMaps()
{
    MultiLightShadowStageData::LightAssocStore& vLightAssocData    = _pStageData->getLightAssocData();
    MultiLightShadowStageData::LightIndexStore& vPointLightIndices = _pStageData->getPointLightIndices();
    MultiLightShadowStageData::LightIndexStore& vSpotLightIndices  = _pStageData->getSpotLightIndices();
    MultiLightShadowStageData::LightIndexStore& vDirLightIndices   = _pStageData->getDirLightIndices();

    MultiLightChunk* pMLChunk = _pStage->getMultiLightChunk();

    if (!vLightAssocData.empty() && pMLChunk != NULL)
    {
        Int32 szPL = static_cast<Int32>(vPointLightIndices.size());
        Int32 szDL = static_cast<Int32>(vDirLightIndices.size() + vSpotLightIndices.size());

        Int32 width  = _pStage->getShadowMapWidth();
        Int32 height = _pStage->getShadowMapHeight();
        Int32 depth  = 0;

        //
        // 1. create/initialize texture object and environment
        //
        if (_pointLightTexObj == NULL)
        {
            depth = osgMax(6, 6*szPL);

            _pointLightImgPX = Image::createLocal();
            _pointLightImgMX = Image::createLocal();
            _pointLightImgPY = Image::createLocal();
            _pointLightImgMY = Image::createLocal();
            _pointLightImgPZ = Image::createLocal();
            _pointLightImgMZ = Image::createLocal();

            _pointLightImgPX->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA, false, 1);
            _pointLightImgMX->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA, false, 1);
            _pointLightImgPY->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA, false, 1);
            _pointLightImgMY->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA, false, 1);
            _pointLightImgPZ->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA, false, 1);
            _pointLightImgMZ->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA, false, 1);

            _pointLightTexObj = CubeTextureObjChunk::createLocal();
            _pointLightTexObj->setPosXImage(_pointLightImgPX);
            _pointLightTexObj->setNegXImage(_pointLightImgMX);
            _pointLightTexObj->setPosYImage(_pointLightImgPY);
            _pointLightTexObj->setNegYImage(_pointLightImgMY);            
            _pointLightTexObj->setPosZImage(_pointLightImgPZ);
            _pointLightTexObj->setImage    (_pointLightImgMZ);

            _pointLightTexObj->setInternalFormat(GL_DEPTH_COMPONENT32);
            _pointLightTexObj->setExternalFormat(GL_DEPTH_COMPONENT);
            //
            // GL_TEXTURE_CUBE_MAP_ARRAY OpenGL 4.0/4.6 ARB_texture_cube_map_array
            // https://www.khronos.org/opengl/wiki/Cubemap_Texture
            // https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_texture_cube_map_array.txt
            //
            _pointLightTexObj->setTarget        (GL_TEXTURE_CUBE_MAP);

            _pointLightTexObj->setMinFilter     (GL_NEAREST);
            _pointLightTexObj->setMagFilter     (GL_NEAREST);
            _pointLightTexObj->setWrapS         (GL_CLAMP_TO_EDGE);
            _pointLightTexObj->setWrapT         (GL_CLAMP_TO_EDGE);
            _pointLightTexObj->setWrapR         (GL_CLAMP_TO_EDGE);

            //_pointLightSampleObj = SamplerObjChunk::createLocal();
            //_pointLightSampleObj->setMinFilter      (GL_LINEAR);
            //_pointLightSampleObj->setMagFilter      (GL_LINEAR);
            //_pointLightSampleObj->setWrapS          (GL_CLAMP_TO_EDGE);
            //_pointLightSampleObj->setWrapT          (GL_CLAMP_TO_EDGE);
            //_pointLightSampleObj->setWrapR          (GL_CLAMP_TO_EDGE);
            //_pointLightSampleObj->setCompareMode    (GL_COMPARE_REF_TO_TEXTURE);
            //_pointLightSampleObj->setCompareFunc    (GL_LEQUAL);
            //_pointLightSampleObj->addTextureUnit    (getSamplerCubeArrayShadowTextureUnit());

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
            depth = osgMax(1, szDL);

            _dirLightImg = Image::createLocal();
            _dirLightImg->set(Image::OSG_DEPTH_PF, 
                              width, height, depth, 
                              1, 1, 0.f, 
                              NULL,
                              Image::OSG_FLOAT32_IMAGEDATA, 
                              false);

            _dirLightTexObj = TextureObjChunk::createLocal();
            _dirLightTexObj->setImage         (_dirLightImg);
            _dirLightTexObj->setInternalFormat(GL_DEPTH_COMPONENT32);
            _dirLightTexObj->setExternalFormat(GL_DEPTH_COMPONENT);
            //
            // GL_TEXTURE_2D_ARRAY OpenGL 3.0/4.6 EXT_texture_array
            // https://www.khronos.org/opengl/wiki/Array_Texture
            //
            _dirLightTexObj->setTarget        (GL_TEXTURE_2D);

            _dirLightTexObj->setMinFilter     (GL_NEAREST);
            _dirLightTexObj->setMagFilter     (GL_NEAREST);
            _dirLightTexObj->setWrapS         (GL_CLAMP_TO_EDGE);
            _dirLightTexObj->setWrapT         (GL_CLAMP_TO_EDGE);
            _dirLightTexObj->setWrapR         (GL_CLAMP_TO_EDGE);

            //_dirLightSampleObj = SamplerObjChunk::createLocal();
            //_dirLightSampleObj->setMinFilter      (GL_LINEAR);
            //_dirLightSampleObj->setMagFilter      (GL_LINEAR);
            //_dirLightSampleObj->setWrapS          (GL_CLAMP_TO_EDGE);
            //_dirLightSampleObj->setWrapT          (GL_CLAMP_TO_EDGE);
            //_dirLightSampleObj->setWrapR          (GL_CLAMP_TO_EDGE);
            //_dirLightSampleObj->setCompareMode    (GL_COMPARE_REF_TO_TEXTURE);
            //_dirLightSampleObj->setCompareFunc    (GL_LEQUAL);
            //_dirLightSampleObj->addTextureUnit    (getSampler2DArrayShadowTextureUnit());

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
        if (_pointLightStore.size() != 6 * vPointLightIndices.size())
        {
            _pointLightStore.clear();

            UInt32 sz = static_cast<UInt32>(vPointLightIndices.size());

            for (UInt32 i = 0; i < sz; ++i)
            {
                for (UInt32 j = 0; j < 6; ++j)
                {
                    ShadowMapData data;

                    data.pFBO = FrameBufferObject::createLocal();
                    data.pTBO = TextureBuffer    ::createLocal();

                    data.pTBO->setLevel          (0);
                    //data.pTBO->setLayer          (i*6 + j);
                    data.pTBO->setTexture        (_pointLightTexObj);
                    data.pTBO->setTexTarget      (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB+j);
                    data.pFBO->setDepthAttachment(data.pTBO);
                    data.pFBO->setWidth          (width);
                    data.pFBO->setHeight         (height);

                    data.pFBO->setPostProcessOnDeactivate(true);
                    data.pTBO->setReadBack(true);

                    _pointLightStore.push_back(data);
                }
            }
        }

        if (_dirLightStore.size() != (vDirLightIndices.size() + vSpotLightIndices.size()))
        {
            _dirLightStore.clear();

            UInt32 sz = static_cast<UInt32>(vDirLightIndices.size() + vSpotLightIndices.size());

            for (UInt32 i = 0; i < sz; ++i)
            {
                ShadowMapData data;

                data.pFBO = FrameBufferObject::createLocal();
                data.pTBO = TextureBuffer    ::createLocal();

                data.pTBO->setLevel          (0);
                //data.pTBO->setLayer          (i);
                data.pTBO->setTexture        (_dirLightTexObj);
                data.pTBO->setTexTarget      (GL_TEXTURE_2D);

                data.pFBO->setDepthAttachment(data.pTBO);
                data.pFBO->setWidth          (width);
                data.pFBO->setHeight         (height);

                data.pFBO->setPostProcessOnDeactivate(true);
                data.pTBO->setReadBack(true);

                _dirLightStore.push_back(data);
            }
        }
    }
    else
    {
        _pointLightStore.clear();
        _dirLightStore  .clear();
    }

    //{
    //    static int iCntTest = 0;
    //    iCntTest++;
    //    if (iCntTest == 10)
    //    {
    //        for (int i = 0; i < _pointLightStore.size(); ++i)
    //        {
    //            const ShadowMapData& data = _pointLightStore[i];
    //            TextureBuffer* tb = data.pTBO;
    //            CubeTextureObjChunk* toc = dynamic_cast<CubeTextureObjChunk*>(tb->getTexture());

    //            Image* imgPX = toc->getPosXImage();
    //            Image* imgMX = toc->getNegXImage();
    //            Image* imgPY = toc->getPosYImage();
    //            Image* imgMY = toc->getNegYImage();
    //            Image* imgPZ = toc->getPosZImage();
    //            Image* imgMZ = toc->getImage();

    //            {
    //                std::stringstream ss;
    //                ss << "d:/work/imgPX_" << ".pnm" << std::flush;
    //                imgPX->write(ss.str().c_str());
    //            }
    //            {
    //                std::stringstream ss;
    //                ss << "d:/work/imgMX_" << ".pnm" << std::flush;
    //                imgMX->write(ss.str().c_str());
    //            }
    //            {
    //                std::stringstream ss;
    //                ss << "d:/work/imgPY_" << ".pnm" << std::flush;
    //                imgPY->write(ss.str().c_str());
    //            }
    //            {
    //                std::stringstream ss;
    //                ss << "d:/work/imgMY_" << ".pnm" << std::flush;
    //                imgMY->write(ss.str().c_str());
    //            }
    //            {
    //                std::stringstream ss;
    //                ss << "d:/work/imgPZ_" << ".pnm" << std::flush;
    //                imgPZ->write(ss.str().c_str());
    //            }
    //            {
    //                std::stringstream ss;
    //                ss << "d:/work/imgMZ_" << ".pnm" << std::flush;
    //                imgMZ->write(ss.str().c_str());
    //            }

    //            break;
    //        }

    //        for (int i = 0; i < _dirLightStore.size(); ++i)
    //        {
    //            std::stringstream ss;
    //            ss << "d:/work/imgDir_" << ".pnm" << std::flush;

    //            const ShadowMapData& data = _dirLightStore[i];
    //            TextureBuffer* tb = data.pTBO;
    //            TextureObjChunk* toc = tb->getTexture();
    //            Image* img = toc->getImage();
    //            img->write(ss.str().c_str());
    //        }

    //    }
    //}
}

void MultiLightShadowTechniqueSimplest::updateShadowMaps()
{
    MultiLightShadowStageData::LightIndexStore& vPointLightIndices = _pStageData->getPointLightIndices();
    MultiLightShadowStageData::LightIndexStore& vSpotLightIndices  = _pStageData->getSpotLightIndices();
    MultiLightShadowStageData::LightIndexStore& vDirLightIndices   = _pStageData->getDirLightIndices();

    Int32 szPL = static_cast<Int32>(vPointLightIndices.size());
    Int32 szDL = static_cast<Int32>(vDirLightIndices.size() + vSpotLightIndices.size());

    Int32 width, height, depth;

    width  = _pStage->getShadowMapWidth();
    height = _pStage->getShadowMapHeight();
    depth  = osgMax(6, 6*szPL);

    if (_pointLightImgPX && 
        (   _pointLightImgPX->getWidth()  != width 
         || _pointLightImgPX->getHeight() != height )
       )
    {
        _pointLightImgPX->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA,  false, 1);
        _pointLightImgMX->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA,  false, 1);
        _pointLightImgPY->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA,  false, 1);
        _pointLightImgMY->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA,  false, 1);
        _pointLightImgPZ->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA,  false, 1);
        _pointLightImgMZ->set(Image::OSG_DEPTH_PF, width, height, 1, 1, 1, 0.f, NULL, Image::OSG_FLOAT32_IMAGEDATA,  false, 1);

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
    depth  = osgMax(1, szDL);

    if (_dirLightImg &&
        (   _dirLightImg->getWidth()  != width 
         || _dirLightImg->getHeight() != height
         || _dirLightImg->getDepth()  != depth )
       )
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
        if (_dirLightChunkMaterial && _pointLightChunkMaterial)
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
}

void MultiLightShadowTechniqueSimplest::renderShadowMaps(RenderAction* a, DrawEnv* pEnv)
{
    MultiLightChunk* pMLChunk = _pStage->getMultiLightChunk();

    MultiLightShadowStageData::LightAssocStore& vLightAssocData = _pStageData->getLightAssocData();

    UInt32 num_lights = static_cast<UInt32>(vLightAssocData.size());

    adaptShadowDataLayout(num_lights);

    RenderPartition* pParentPart = a->getActivePartition();

    //
    // Commit has been called; adapt to shadow casting scene
    //
    a->getActNode()->updateVolume();

    const FrustumVolume& camFrust    = pParentPart->getFrustum();
    const BoxVolume&     sceneBB     = a->getActNode()->getVolume();
    const Matrix&        matWSFromMS = a->topMatrix();

    //
    // Task: For each shadowing enabled light create a render partition that
    //       renders into the associated frame buffer object, i.e the texture.
    //
    //       Render from the view point of the light either into the direction
    //       of the light or for point lights into all six cube face directions.
    //
    //       On rendereing of the scene only adapt the z-depth of the fragments.
    //
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
            // The shadow data are tracked in a separate shader storage block.
            // This block does have the same number of array elements as
            // the multi light. The ShadowIndex memeber of the light just carry
            // the corresponding light index for lookup in the shadow data array.
            //
            pMLChunk->setShadowDataIndex(idx, idx);

            Matrix matLSFromWS;
            pMLChunk->calcLightSpaceMatrixLSFromWS(idx, matLSFromWS);

            Real32 zNear, zFar;
            pMLChunk->calcFrustumZ(pEnv, idx, zNear, zFar);

            Pnt3f  lightMin, lightMax;
            if ( vLightAssocData[idx].type == MultiLight::DIRECTIONAL_LIGHT)
            {
                calcOrthoShadowViewVolume(matWSFromMS, matLSFromWS, camFrust, sceneBB, lightMin, lightMax);

                zFar = osgMin(zFar, lightMax.z());
            }

            Matrix matProjection;
            pMLChunk->calcProjectionMatrix(idx, zNear, zFar, lightMin, lightMax, matProjection);

            //
            // If the user has requested a projection matrix for the multi lights then
            // set the projection.
            //
            if (pMLChunk->getHasProjection())
                pMLChunk->setProjectionMatrix(idx, matProjection);

            Matrix matProjLSFromWS = matProjection;
            matProjLSFromWS.mult(matLSFromWS);

            Matrix matTSFromCS;
            matTSFromCS.setScale(0.5f, 0.5f, 0.5f);
            matTSFromCS.setTranslate(0.5f, 0.5f, 0.5f);

            Matrix matTSFromWS = matTSFromCS;
            matTSFromWS.mult(matProjLSFromWS);

            _shadowData[idx].matLSFromWS = matLSFromWS;
            _shadowData[idx].matTSFromWS = matTSFromWS;
            _shadowData[idx].frustumSize = calcFrustumSize(matTSFromWS);
            _shadowData[idx].zNear       = zNear;
            _shadowData[idx].zFar        = zFar;
            
            Pnt3f  position;
            pMLChunk->calcPosition(pEnv, idx, position, false);

            if ( vLightAssocData[idx].type == MultiLight::DIRECTIONAL_LIGHT 
              || vLightAssocData[idx].type == MultiLight::SPOT_LIGHT 
              || vLightAssocData[idx].type == MultiLight::CINEMA_LIGHT)
            {
                OSG_ASSERT(dir_light_iter != dir_light_end);
                const ShadowMapData& data = *dir_light_iter;

                _shadowData[idx].shadowIndex = dirShadowIndex;
                dirShadowIndex++;

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

                dir_light_iter++;
            }
            else
            if (vLightAssocData[idx].type == MultiLight::POINT_LIGHT)
            {
                _shadowData[idx].shadowIndex = pointShadowIndex;
                pointShadowIndex++;

                for (int i = 0; i < 6; ++i)
                {
                    Matrix matLSFromWSFace(matLSFromWS);
                    matLSFromWSFace.multLeft(_matCubeFaceInv[i]);

                    OSG_ASSERT(point_light_iter != point_light_end);
                    const ShadowMapData& data = *point_light_iter;

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

                        // vertex shader

                        // fragment shader
                        _pointLightSHLChunk->updateUniformVariable("uLightPosWS", position);
                        _pointLightSHLChunk->updateUniformVariable("uFarPlaneWS", zFar);

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

                    point_light_iter++;
                }
            }
        }
    }
}

std::string MultiLightShadowTechniqueSimplest::getPointLightVertProgram() const
{
    using namespace std;

    stringstream ost;

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects: enable"
    << endl << "#extension GL_ARB_uniform_buffer_object:   enable"
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

std::string MultiLightShadowTechniqueSimplest::getPointLightFragProgram() const
{
    using namespace std;

    stringstream ost;

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects: enable"
    << endl << "#extension GL_ARB_uniform_buffer_object:   enable"
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

std::string MultiLightShadowTechniqueSimplest::getDirLightVertProgram() const
{
    using namespace std;

    stringstream ost;

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects: enable"
    << endl << "#extension GL_ARB_uniform_buffer_object:   enable"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    gl_Position = ftransform();"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

std::string MultiLightShadowTechniqueSimplest::getDirLightFragProgram() const
{
    using namespace std;

    stringstream ost;

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects: enable"
    << endl << "#extension GL_ARB_uniform_buffer_object:   enable"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    gl_FragDepth = gl_FragCoord.z;"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

std::string MultiLightShadowTechniqueSimplest::getFragmentProgramSnippet() const
{
    using namespace std;

    stringstream ost;

    MultiLightChunk* pMLChunk = _pStage->getMultiLightChunk();

    // GL_TEXTURE_CUBE_MAP_ARRAY OpenGL 4.0/4.6 ARB_texture_cube_map_array
    // GL_TEXTURE_2D_ARRAY       OpenGL 3.0/4.6 EXT_texture_array
     
    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects:   enable"
    << endl << ""
    << pMLChunk->getFragmentProgramSnippet(false, false)  // Light struct declaration only
    << endl << ""
    << endl << "uniform samplerCube uShadowMapPnt;"
    << endl << "uniform sampler2D   uShadowMapDir;"
    << endl << ""
    //<< endl << "uniform samplerCubeShadow uShadowMapPntComp;"
    //<< endl << "uniform sampler2DShadow   uShadowMapDirComp;"
    << endl << ""
    << endl << "uniform bool  uShadowEnabled;"
    << endl << "uniform bool  uUseShadowSampler;"
    << endl << ""
    << endl << "struct ShadowData"
    << endl << "{"
    << endl << "    mat4  matLSFromWS;"
    << endl << "    mat4  matTSFromWS;"
    << endl << "    vec2  frustumSize;"
    << endl << "    float zNear;"
    << endl << "    float zFar;"
    << endl << "    int   shadowIndex;"
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
    << endl << Shader::getEqualEpsDeclSnippet()
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
    << endl << "    float layer = float(data.shadowIndex);"
    << endl << ""
    << endl << "    vec3  projDir  = normalize(lightDirWS);"
    << endl << "    float cosTheta = clamp(dot(normalWS, -projDir), 0.0, 1.0);"
    << endl << "    float factor   = tan(acos(cosTheta));"
    << endl << "    float bias     = param.bias * clamp(factor, 1.0, 100.0);"
    << endl << ""
    << endl << "    float fragDepthLS = length(lightDirWS);"
    << endl << "    float zReceiver   = fragDepthLS / data.zFar;"
    << endl << ""
    << endl << "    float z = zReceiver - bias;"
    << endl << "    return lookUpShadowMapPnt(projDir, z);"
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
    << endl << "    float layer = float(data.shadowIndex);"
    << endl << ""
    << endl << "    float cosTheta = clamp(dot(normalWS, -normalize(lightDirWS)), 0.0, 1.0);"
    << endl << "    float factor   = tan(acos(cosTheta));"
    << endl << "    float bias     = param.bias * clamp(factor, 1.0, 100.0);"
    << endl << ""
    << endl << "    vec3  fragPosTS   = getShadowCoords(data.matTSFromWS, fragPosWS);"
    << endl << "    vec2  uv          = fragPosTS.xy;"
    << endl << "    float zReceiver   = fragPosTS.z;"
    << endl << ""
    << endl << "    float z = zReceiver - bias;"
    << endl << "    return lookUpShadowMapDir(uv, z);"
    << endl << "}"
    << endl << ""
    << getDispatchProgramSnippet()
    << endl << ""
    << endl;

    return ost.str();
}

std::string MultiLightShadowTechniqueSimplest::getDispatchProgramSnippet() const
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
    << endl << "        return 0.0;"
    << endl << ""
    << endl << "    int  dataIdx     = light.shadowDataIndex;"
    << endl << "    int  paramIdx    = light.shadowParameterIndex;"
    << endl << "    vec3 lightDirWS  = light.direction;"
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
    << endl << "    int  dataIdx    = light.shadowDataIndex;"
    << endl << "    int  paramIdx   = light.shadowParameterIndex;"
    << endl << "    vec3 lightDirWS = fragPosWS - light.position;"
    << endl << ""
    << endl << "    return _shadowCalculationPoint(fragDepthES, fragPosWS, normalWS, lightDirWS, dataIdx, paramIdx);"
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
    << endl << "    int  dataIdx    = light.shadowDataIndex;"
    << endl << "    int  paramIdx   = light.shadowParameterIndex;"
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
    << endl << "    int  dataIdx    = light.shadowDataIndex;"
    << endl << "    int  paramIdx   = light.shadowParameterIndex;"
    << endl << "    vec3 lightDirWS = fragPosWS - light.position;"
    << endl << ""
    << endl << "    return _shadowCalculationSpot(fragDepthES, fragPosWS, normalWS, lightDirWS, dataIdx, paramIdx, true);"
    << endl << "}"
    << endl << ""
    << endl << "vec4 shadowSplitIndexTest(in float fragDepthES, in Light light)"
    << endl << "{"
    << endl << "    return vec4(0);"
    << endl << "}"
    << endl << ""
    << endl << "bool shadowTestShader(in int idx, in Light light)"
    << endl << "{"
    << endl << "    bool flag = true;"
    << endl << ""
    << endl << "    mat4  mVal;"
    << endl << "    vec3  vVal;"
    << endl << "    float fVal;"
    << endl << "    int   iVal;"
    << endl << "    bool  bVal;"
    << endl << ""
    << endl << "    switch(idx)"
    << endl << "    {"
    << endl << "        case 0:"
    << endl << "            {"
    << endl << "                vVal = light.position;"
    << endl << "                if (OSGEqualEps(vVal,  vec3(0 ,4 ,3), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.direction;"
    << endl << "                if (OSGEqualEps(vVal, vec3(0 ,0 ,1), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.ambientIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.diffuseIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.specularIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.constantAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 1, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.linearAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 0.0001, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.quadraticAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 1e-006, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.rangeCutOn;"
    << endl << "                if (OSGEqualEps(fVal, 0.1, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.rangeCutOff;"
    << endl << "                if (OSGEqualEps(fVal, 9.99e+006, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.cosSpotlightAngle;"
    << endl << "                if (OSGEqualEps(fVal, 1, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.spotlightExponent;"
    << endl << "                if (OSGEqualEps(fVal, 1, 1.E-5) == false) flag = false;"
    << endl << "                iVal = light.type;"
    << endl << "                if (iVal != 1) flag = false;"
    << endl << "                bVal = light.enabled;"
    << endl << "                if (bVal != true) flag = false;"
    << endl << "                bVal = light.shadow;"
    << endl << "                if (bVal != true) flag = false;"
    << endl << "                iVal = light.shadowDataIndex;"
    << endl << "                if (iVal != 0) flag = false;"
    << endl << "                iVal = light.shadowParameterIndex;"
    << endl << "                if (iVal != 0) flag = false;"
    << endl << "            }"
    << endl << "            break;"
    << endl << "        case 1:"
    << endl << "            {"
    << endl << "                vVal = light.position;"
    << endl << "                if (OSGEqualEps(vVal,  vec3(0 ,7 ,3), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.direction;"
    << endl << "                if (OSGEqualEps(vVal, vec3(0 ,-0.919145 ,-0.393919), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.ambientIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.diffuseIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.specularIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.constantAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 1, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.linearAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 0.0001, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.quadraticAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 1e-006, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.rangeCutOn;"
    << endl << "                if (OSGEqualEps(fVal, 0.1, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.rangeCutOff;"
    << endl << "                if (OSGEqualEps(fVal, 9.99e+006, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.cosSpotlightAngle;"
    << endl << "                if (OSGEqualEps(fVal, 0.819152, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.spotlightExponent;"
    << endl << "                if (OSGEqualEps(fVal, 1, 1.E-5) == false) flag = false;"
    << endl << "                iVal = light.type;"
    << endl << "                if (iVal != 3) flag = false;"
    << endl << "                bVal = light.enabled;"
    << endl << "                if (bVal != false) flag = false;"
    << endl << "                bVal = light.shadow;"
    << endl << "                if (bVal != false) flag = false;"
    << endl << "                iVal = light.shadowDataIndex;"
    << endl << "                if (iVal != -1) flag = false;"
    << endl << "                iVal = light.shadowParameterIndex;"
    << endl << "                if (iVal != 1) flag = false;"
    << endl << "            }"
    << endl << "            break;"
    << endl << "        case 2:"
    << endl << "            {"
    << endl << "                vVal = light.position;"
    << endl << "                if (OSGEqualEps(vVal,  vec3(-0.654 ,0.589 ,0.476), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.direction;"
    << endl << "                if (OSGEqualEps(vVal, vec3(0.653604 ,-0.588643 ,-0.475712), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.ambientIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.diffuseIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.specularIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.constantAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 1, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.linearAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 0.0001, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.quadraticAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 1e-006, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.rangeCutOn;"
    << endl << "                if (OSGEqualEps(fVal, 0.1, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.rangeCutOff;"
    << endl << "                if (OSGEqualEps(fVal, 1000, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.cosSpotlightAngle;"
    << endl << "                if (OSGEqualEps(fVal, 1, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.spotlightExponent;"
    << endl << "                if (OSGEqualEps(fVal, 1, 1.E-5) == false) flag = false;"
    << endl << "                iVal = light.type;"
    << endl << "                if (iVal != 2) flag = false;"
    << endl << "                bVal = light.enabled;"
    << endl << "                if (bVal != true) flag = false;"
    << endl << "                bVal = light.shadow;"
    << endl << "                if (bVal != true) flag = false;"
    << endl << "                iVal = light.shadowDataIndex;"
    << endl << "                if (iVal != 2) flag = false;"
    << endl << "                iVal = light.shadowParameterIndex;"
    << endl << "                if (iVal != 2) flag = false;"
    << endl << "            }"
    << endl << "            break;"
    << endl << "        case 3:"
    << endl << "            {"
    << endl << "                vVal = light.position;"
    << endl << "                if (OSGEqualEps(vVal,  vec3(-0.654 ,0.589 ,-0.476), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.direction;"
    << endl << "                if (OSGEqualEps(vVal, vec3(0.653604 ,-0.588643 ,0.475712), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.ambientIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.diffuseIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                vVal = light.specularIntensity;"
    << endl << "                if (OSGEqualEps(vVal, vec3(1 ,1 ,1), 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.constantAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 1, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.linearAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 0.0001, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.quadraticAttenuation;"
    << endl << "                if (OSGEqualEps(fVal, 1e-006, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.rangeCutOn;"
    << endl << "                if (OSGEqualEps(fVal, 0.1, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.rangeCutOff;"
    << endl << "                if (OSGEqualEps(fVal, 1000, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.cosSpotlightAngle;"
    << endl << "                if (OSGEqualEps(fVal, 1, 1.E-5) == false) flag = false;"
    << endl << "                fVal = light.spotlightExponent;"
    << endl << "                if (OSGEqualEps(fVal, 1, 1.E-5) == false) flag = false;"
    << endl << "                iVal = light.type;"
    << endl << "                if (iVal != 2) flag = false;"
    << endl << "                bVal = light.enabled;"
    << endl << "                if (bVal != false) flag = false;"
    << endl << "                bVal = light.shadow;"
    << endl << "                if (bVal != false) flag = false;"
    << endl << "                iVal = light.shadowDataIndex;"
    << endl << "                if (iVal != -1) flag = false;"
    << endl << "                iVal = light.shadowParameterIndex;"
    << endl << "                if (iVal != 3) flag = false;"
    << endl << "            }"
    << endl << "            break;"
    << endl << "    }"
    << endl << "    return flag;"
    << endl << "}"
    ;
    return ost.str();
}

std::string MultiLightShadowTechniqueSimplest::getShadowBaseProgramSnippet() const
{
    using namespace std;

    stringstream ost;

    ost     << "vec3 getShadowCoords(in mat4 matTSFromWS, in vec3 fragPosWS)"
    << endl << "{"
    << endl << "    vec4 fragPosTS = matTSFromWS * vec4(fragPosWS, 1.0);"
    << endl << "    fragPosTS = fragPosTS / fragPosTS.w;"
    << endl << "    return fragPosTS.xyz;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Shadow map lookup for common case resulting comparsion value"
    << endl << "//"
    << endl << "float lookUpShadowMapDir("
    << endl << "    in vec2           uv,"
    << endl << "    in float          ref)"
    << endl << "{"
    //<< endl << "    if (uUseShadowSampler)"
    //<< endl << "        return texture(uShadowMapDirComp, vec3(uv, ref)).x;"
    //<< endl << "    else"
    << endl << "        return step(ref, texture(uShadowMapDir, uv).x);"
    << endl << "}"
    << endl << ""
    << endl << "float lookUpShadowMapPnt("
    << endl << "    in vec3             dir,"
    << endl << "    in float            ref)"
    << endl << "{"
    //<< endl << "    if (uUseShadowSampler)"
    //<< endl << "        return texture(uShadowMapPntComp, vec4(dir, ref)).x;"
    //<< endl << "    else"
    << endl << "        return step(ref, texture(uShadowMapPnt, dir).x);"
    << endl << "}"
    << endl << ""
    ;

    return ost.str();
}

OSG_END_NAMESPACE
