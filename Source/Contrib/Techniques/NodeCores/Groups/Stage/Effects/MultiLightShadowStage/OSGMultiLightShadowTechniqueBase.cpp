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

#include "OSGMultiLightShadowTechniqueBase.h"
#include "OSGMultiLightShadowStage.h"
#include "OSGMultiLightShadowStageData.h"
#include "OSGMultiLightShadowParameter.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"

#include "OSGRenderAction.h"
#include "OSGMatrixUtility.h"

#include "OSGMatrixCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGTransform.h"

#include "OSGMultiLightChunk.h"
#include "OSGShaderUtility.h"
#include "OSGPoissonDistribution.h"

OSG_BEGIN_NAMESPACE

const Matrix MultiLightShadowTechniqueBase::_matCubeFaceInv[6] =
{
    Matrix( 0,  0, -1,  0,   // + X
            0, -1,  0,  0,
           -1,  0,  0,  0,
            0,  0,  0,  1),
        
    Matrix( 0,  0,  1,  0,   // - X
            0, -1,  0,  0,
            1,  0,  0,  0,
            0,  0,  0,  1),

    Matrix( 1,  0,  0,  0,   // + Y
            0,  0,  1,  0,
            0, -1,  0,  0,
            0,  0,  0,  1),

    Matrix( 1,  0,  0,  0,   // - Y
            0,  0, -1,  0,
            0,  1,  0,  0,
            0,  0,  0,  1),

    Matrix( 1,  0,  0,  0,   // + Z
            0, -1,  0,  0,
            0,  0, -1,  0,
            0,  0,  0,  1),
        
    Matrix(-1,  0,  0,  0,   // - Z
            0, -1,  0,  0,
            0,  0,  1,  0,
            0,  0,  0,  1),
};

MultiLightShadowTechniqueBase::MultiLightShadowTechniqueBase(
    MultiLightShadowStage     *pStage,
    MultiLightShadowStageData *pData,
    Window                    *pWindow)
: Inherited             ()
, _uiMode               (MultiLightShadowStage::NO_SHADOW_MAP)
, _width                (1)
, _height               (1)
, _nTexImages           (0)
, _nShaderStorageBlocks (0)
, _nUniformBlocks       (0)
, _pStage               (pStage)
, _pStageData           (pData)
, _polygonChunk         (NULL)
, _clearBackground      (NULL)
, _shadowDataChunk      (NULL)
, _shadowParamChunk     (NULL)
, _distributionChunk    (NULL)
, _biasFactor           (1.f/1000.f)
{
    OSG_ASSERT(pStage  != NULL);
    OSG_ASSERT(pData   != NULL);
    OSG_ASSERT(pWindow != NULL);

    GLint max_tex_size = pWindow->getConstantValue(GL_MAX_TEXTURE_SIZE);

    _clearBackground = DepthClearBackground::createLocal();
    _polygonChunk    = PolygonChunk::createLocal();

    _polygonChunk->setOffsetBias  (_pStage->getOffsetBias  ());
    _polygonChunk->setOffsetFactor(_pStage->getOffsetFactor());
    _polygonChunk->setCullFace    (_pStage->getCullFrontFace() ?  GL_FRONT : GL_NONE);
    _polygonChunk->setOffsetFill  (true);

    _shadowDataChunk = ShaderStorageBufferObjStdLayoutChunk::createLocal();
    _shadowDataChunk->setUsage(GL_DYNAMIC_DRAW);

    _shadowParamChunk = UniformBufferObjStd140Chunk::createLocal();
    _shadowParamChunk->setUsage(GL_DYNAMIC_DRAW);

    _distributionChunk = UniformBufferObjStd140Chunk::createLocal();
    _distributionChunk->setUsage(GL_STATIC_DRAW);
}

MultiLightShadowTechniqueBase::~MultiLightShadowTechniqueBase()
{
    _pStage            = NULL;
    _pStageData        = NULL;
 
    _polygonChunk      = NULL;
    _clearBackground   = NULL;

    _shadowDataChunk   = NULL;
    _shadowParamChunk  = NULL;

    _distributionChunk = NULL;
}

Action::ResultE MultiLightShadowTechniqueBase::recurseFromThis(Action* action)
{
    return _pStage->recurseFromThis(action);
}

Action::ResultE MultiLightShadowTechniqueBase::recurseFrom(Action* action, NodeCore* pFrom)
{
    return _pStage->recurseFrom(action, pFrom);
}

Action::ResultE MultiLightShadowTechniqueBase::recurse(Action* action, Node* node)
{
    return _pStage->recurse(action, node);
}

void MultiLightShadowTechniqueBase::initializeAssocData(UInt32 idx) const
{
    MultiLightShadowStageData::LightAssocStore& vLightAssocData = _pStageData->getLightAssocData();

    MultiLightShadowStageData::LightAssoc& data = vLightAssocData[idx];

    data.transform = Transform::createLocal();
    data.beacon    = makeNodeFor(data.transform);

    createCamera(data.type, data.camera);

    data.camera->setBeacon(data.beacon);
}

void MultiLightShadowTechniqueBase::createCamera(
    MultiLight::Type type, 
    CameraUnrecPtr&  camera) const
{
    if (type == MultiLight::DIRECTIONAL_LIGHT)
    {
        camera = MatrixCamera::createLocal();
    }
    else
    {
        camera = PerspectiveCamera::createLocal();
    }
}

void MultiLightShadowTechniqueBase::updateLights(RenderAction* a, DrawEnv* pEnv)
{
    MultiLightShadowStageData::LightAssocStore& vLightAssocData    = _pStageData->getLightAssocData();
    MultiLightShadowStageData::LightIndexStore& vPointLightIndices = _pStageData->getPointLightIndices();
    MultiLightShadowStageData::LightIndexStore& vSpotLightIndices  = _pStageData->getSpotLightIndices();
    MultiLightShadowStageData::LightIndexStore& vDirLightIndices   = _pStageData->getDirLightIndices();

    MultiLightChunk* pMLChunk = _pStage->getMultiLightChunk();

    if (!vLightAssocData.empty() && pMLChunk != NULL)
    {
        a->getActNode()->updateVolume();

        MultiLightShadowStageData::LightIndexStore::const_iterator iter;
        MultiLightShadowStageData::LightIndexStore::const_iterator  end;

        iter = vPointLightIndices.begin();
        end  = vPointLightIndices.end();

        for (; iter != end; ++iter)
        {
            UInt32 idx = *iter;
            updatePointLight(a, pEnv, idx, pMLChunk, vLightAssocData[idx].transform, vLightAssocData[idx].camera);
        }

        iter = vSpotLightIndices.begin();
        end  = vSpotLightIndices.end();

        for (; iter != end; ++iter)
        {
            UInt32 idx = *iter;
            updateSpotLight(a, pEnv, idx, pMLChunk, vLightAssocData[idx].transform, vLightAssocData[idx].camera);
        }

        iter = vDirLightIndices.begin();
        end  = vDirLightIndices.end();

        for (; iter != end; ++iter)
        {
            UInt32 idx = *iter;
            updateDirLight(a, pEnv, idx, pMLChunk, vLightAssocData[idx].transform, vLightAssocData[idx].camera);
        }
    }
}

void MultiLightShadowTechniqueBase::updateDirLight(
    RenderAction*    a, 
    DrawEnv*         pEnv, 
    UInt32           idx, 
    MultiLightChunk* pMLChunk, 
    Transform*       transform, 
    Camera*          camera)
{
}

void MultiLightShadowTechniqueBase::updatePointLight(
    RenderAction*    a, 
    DrawEnv*         pEnv, 
    UInt32           idx, 
    MultiLightChunk* pMLChunk, 
    Transform*       transform, 
    Camera*          camera)
{
}

void MultiLightShadowTechniqueBase::updateSpotLight(
    RenderAction*    a, 
    DrawEnv*         pEnv, 
    UInt32           idx, 
    MultiLightChunk* pMLChunk, 
    Transform*       transform, 
    Camera*          camera)
{
}

void MultiLightShadowTechniqueBase::calcOrthoShadowViewVolume(
    const Matrix&        matWSFromMS,
    const Matrix&        matLSFromWS,
    const FrustumVolume& camFrust,
    const BoxVolume&     sceneBB,
    Pnt3f&               lightMin,
    Pnt3f&               lightMax) const
{
    Pnt3f camVerts  [10];
    Pnt3f sceneVerts[10];

    camFrust.getCorners(camVerts  [0], camVerts  [1],
                        camVerts  [2], camVerts  [3],
                        camVerts  [4], camVerts  [5],
                        camVerts  [6], camVerts  [7]);

    sceneBB .getCorners(sceneVerts[0], sceneVerts[1],
                        sceneVerts[2], sceneVerts[3],
                        sceneVerts[4], sceneVerts[5],
                        sceneVerts[6], sceneVerts[7]);


    Real32 min_value = TypeTraits<Real32>::getMin();
    Real32 max_value = TypeTraits<Real32>::getMax();

    camVerts[8].setValues(max_value, max_value, max_value);
    camVerts[9].setValues(min_value, min_value, min_value);

    sceneVerts[8].setValues(max_value, max_value, max_value);
    sceneVerts[9].setValues(min_value, min_value, min_value );


    for(UInt32 i = 0; i < 8; ++i)
    {
        matLSFromWS.mult(camVerts[i], camVerts[i]);

        matWSFromMS.mult(sceneVerts[i], sceneVerts[i]);
        matLSFromWS.mult(sceneVerts[i], sceneVerts[i]);

        camVerts  [8][0] = osgMin(camVerts  [8][0], camVerts  [i][0]);
        camVerts  [9][0] = osgMax(camVerts  [9][0], camVerts  [i][0]);
        camVerts  [8][1] = osgMin(camVerts  [8][1], camVerts  [i][1]);
        camVerts  [9][1] = osgMax(camVerts  [9][1], camVerts  [i][1]);

        sceneVerts[8][0] = osgMin(sceneVerts[8][0], sceneVerts[i][0]);
        sceneVerts[9][0] = osgMax(sceneVerts[9][0], sceneVerts[i][0]);
        sceneVerts[8][1] = osgMin(sceneVerts[8][1], sceneVerts[i][1]);
        sceneVerts[9][1] = osgMax(sceneVerts[9][1], sceneVerts[i][1]);
        sceneVerts[8][2] = osgMin(sceneVerts[8][2], sceneVerts[i][2]);
        sceneVerts[9][2] = osgMax(sceneVerts[9][2], sceneVerts[i][2]);
    }

    //
    // these points are the corners of the ortho shadow view volume
    //
    lightMin.setValues(osgMax(camVerts[8][0], sceneVerts[8][0]),
                       osgMax(camVerts[8][1], sceneVerts[8][1]),
                       -sceneVerts[9][2]);

    lightMax.setValues(osgMin(camVerts[9][0], sceneVerts[9][0]),
                       osgMin(camVerts[9][1], sceneVerts[9][1]),
                       -sceneVerts[8][2]);


    //
    // enlarge by 2% in x, y, z direction
    //
    lightMin[0] -= (lightMax[0] - lightMin[0]) * 0.01f;
    lightMin[1] -= (lightMax[1] - lightMin[1]) * 0.01f; 
    lightMin[2] -= (lightMax[2] - lightMin[2]) * 0.01f;

    lightMax[0] += (lightMax[0] - lightMin[0]) * 0.01f;
    lightMax[1] += (lightMax[1] - lightMin[1]) * 0.01f;
    lightMax[2] += (lightMax[2] - lightMin[2]) * _pStage->getEnlargeShadowVolumeZ();
}

Vec2f MultiLightShadowTechniqueBase::calcFrustumSize(const Matrix& matTSFromWS) const
{
    Matrix matWSfromTS;
    matTSFromWS.inverse(matWSfromTS);

    Vec4f lh4(0.f, 1.f, 0.f, 1.f);
    Vec4f ll4(0.f, 0.f, 0.f, 1.f);
    Vec4f hl4(1.f, 0.f, 0.f, 1.f);

    matWSfromTS.mult(lh4, lh4);
    matWSfromTS.mult(ll4, ll4);
    matWSfromTS.mult(hl4, hl4);

    Vec3f lh3(lh4[0]/lh4[3], lh4[1]/lh4[3], lh4[2]/lh4[3]);
    Vec3f ll3(ll4[0]/ll4[3], ll4[1]/ll4[3], ll4[2]/ll4[3]);
    Vec3f hl3(hl4[0]/hl4[3], hl4[1]/hl4[3], hl4[2]/hl4[3]);

    Vec2f frustumSize((ll3-hl3).length(), (ll3-lh3).length());

    return frustumSize;
}

bool MultiLightShadowTechniqueBase::getUpdateOffset() const
{
    return _pStage->getUpdateOffset();
}

bool MultiLightShadowTechniqueBase::getUpdateUniformData() const
{
    return _pStage->getUpdateUniformData();
}

bool MultiLightShadowTechniqueBase::getUpdateShadowParameter() const
{
    return _pStage->getUpdateShadowParameter();
}

bool MultiLightShadowTechniqueBase::changedShadowParameter(
    FieldContainer*     pFC, 
    ConstFieldMaskArg   whichField, 
    UInt32              origin)
{
    bool changed = false;

    MultiLightShadowParameter* pMLShadowParameter = dynamic_cast<MultiLightShadowParameter*>(pFC);
    if (pMLShadowParameter)
    {
        if ((whichField & (
                MultiLightShadowParameter::BiasFieldMask |
                MultiLightShadowParameter::IntensityFieldMask |
                MultiLightShadowParameter::FilterModeFieldMask |
                MultiLightShadowParameter::FilterRadiusFieldMask |
                MultiLightShadowParameter::RandomRotateFilterFieldMask |
                MultiLightShadowParameter::UseBlockerSearchFieldMask |
                MultiLightShadowParameter::UsePCSSFieldMask
           )) != 0) changed = true;
    }

    return changed;
}

Int32 MultiLightShadowTechniqueBase::getAdaptedFilterDiskSize() const
{
    Int32 filterSize = 0;

    Int32 distrSize = _pStage->getFilterDistributionSize();

    if      (distrSize <= 1) filterSize =  16;
    else if (distrSize <= 2) filterSize =  25;
    else if (distrSize <= 3) filterSize =  32;
    else if (distrSize <= 4) filterSize =  64;
    else if (distrSize <= 5) filterSize = 100;
    else if (distrSize <= 6) filterSize = 128;
    else if (distrSize <= 7) filterSize = 256;
    else                     filterSize = 256;
    return filterSize;
}

Int32 MultiLightShadowTechniqueBase::getAdaptedSearchDiskSize() const
{
    Int32 searchSize = 0;

    Int32 distrSize = _pStage->getSearchDistributionSize();

    if      (distrSize <= 0) searchSize =   9;
    else if (distrSize <= 1) searchSize =  16;
    else if (distrSize <= 2) searchSize =  25;
    else if (distrSize <= 3) searchSize =  32;
    else if (distrSize <= 4) searchSize =  64;
    else if (distrSize <= 5) searchSize = 100;
    else if (distrSize <= 6) searchSize = 128;
    else                     searchSize = 128;

    Int32 filterSize = getAdaptedFilterDiskSize();

    if (searchSize >= filterSize)
    {
        searchSize = filterSize;

        if      (searchSize <=  16) searchSize =   9;
        else if (searchSize <=  25) searchSize =  16;
        else if (searchSize <=  32) searchSize =  25;
        else if (searchSize <=  64) searchSize =  32;
        else if (searchSize <= 100) searchSize =  64;
        else if (searchSize <= 128) searchSize = 100;
        else if (searchSize <= 256) searchSize = 128;
        else                        searchSize = 128;
    }

    return searchSize;
}

Int32 MultiLightShadowTechniqueBase::getAdaptedFilterBoxSize() const
{
    Int32 filterSize = 0;

    Int32 distrSize = _pStage->getFilterDistributionSize();

    if      (distrSize <= 1) filterSize =  4;
    else if (distrSize <= 2) filterSize =  6;
    else if (distrSize <= 3) filterSize =  8;
    else if (distrSize <= 4) filterSize = 10;
    else if (distrSize <= 5) filterSize = 12;
    else if (distrSize <= 6) filterSize = 14;
    else if (distrSize <= 7) filterSize = 16;
    else                     filterSize = 16;
    return filterSize;
}

Int32 MultiLightShadowTechniqueBase::getAdaptedSearchBoxSize() const
{
    Int32 searchSize = 0;

    Int32 distrSize = _pStage->getSearchDistributionSize();

    if      (distrSize <= 0) searchSize =  2;
    else if (distrSize <= 1) searchSize =  4;
    else if (distrSize <= 2) searchSize =  6;
    else if (distrSize <= 3) searchSize =  8;
    else if (distrSize <= 4) searchSize = 10;
    else if (distrSize <= 5) searchSize = 12;
    else if (distrSize <= 6) searchSize = 14;
    else                     searchSize = 14;

    Int32 filterSize = getAdaptedFilterDiskSize();

    if (searchSize >= filterSize)
    {
        searchSize = filterSize;

        if      (searchSize <=  4) searchSize =  2;
        else if (searchSize <=  6) searchSize =  4;
        else if (searchSize <=  8) searchSize =  6;
        else if (searchSize <= 10) searchSize =  8;
        else if (searchSize <= 12) searchSize = 10;
        else if (searchSize <= 14) searchSize = 12;
        else if (searchSize <= 16) searchSize = 14;
        else                       searchSize = 14;
    }

    return searchSize;
}

bool MultiLightShadowTechniqueBase::getUpdateDistribution() const
{
    return _pStage->getUpdateDistribution();
}

std::size_t MultiLightShadowTechniqueBase::calcDistributionBufferSize(
    UInt32 filterSize, 
    UInt32 searchSize) const
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    //
    // Box kernel sizes
    //
    ao = alignOffset( 4, bo); bo = ao + sizeof( Int32); // Int32   boxFilterSize
    ao = alignOffset( 4, bo); bo = ao + sizeof( Int32); // Int32   boxSearchSize

    //
    // Filter Distribution
    //
    for (UInt32 idx = 0; idx < filterSize; ++idx)
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec2f);  // Vec2f  entry
    }
    ao = alignOffset(16, bo); bo = ao;                      // array padding

    //
    // Search Distribution
    //
    for (UInt32 idx = 0; idx < searchSize; ++idx)
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec2f);  // Vec2f  entry
    }
    ao = alignOffset(16, bo); bo = ao;                      // array padding

    return ao;
}

std::vector<UInt8> MultiLightShadowTechniqueBase::createDistributionBuffer() const
{
    Int32 filterSize = getAdaptedFilterDiskSize();
    Int32 searchSize = getAdaptedSearchDiskSize();

    std::size_t size = calcDistributionBufferSize(filterSize, searchSize);
    std::vector<UInt8> buffer(size);
    
    std::vector<Vec2f> filterDistribution = Distribution::getPoissonDisk(filterSize);
    std::vector<Vec2f> searchDistribution = Distribution::getPoissonDisk(searchSize);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = getAdaptedFilterBoxSize(); bo = ao + sizeof( Int32);
    ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = getAdaptedSearchBoxSize(); bo = ao + sizeof( Int32);

    for (Int32 idx = 0; idx < filterSize; ++idx)
    {
        const Vec2f& value = filterDistribution[idx];
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &value[0], sizeof(Vec2f)); bo = ao + sizeof(Vec2f);
    }
    ao = alignOffset(16, bo); bo = ao;                  // padding

    for (Int32 idx = 0; idx < searchSize; ++idx)
    {
        const Vec2f& value = searchDistribution[idx];
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &value[0], sizeof(Vec2f)); bo = ao + sizeof(Vec2f);
    }
    ao = alignOffset(16, bo); bo = ao;                  // padding

    return buffer;
}

void MultiLightShadowTechniqueBase::updateDistributionState()
{
    if (getUpdateDistribution())
    {
        std::vector<UInt8> buffer = createDistributionBuffer();
        _distributionChunk->editMFBuffer()->setValues(buffer);
    }
}

void MultiLightShadowTechniqueBase::initLimits(Window* win)
{
    if (_nTexImages == 0 || _nShaderStorageBlocks == 0 || _nUniformBlocks == 0)
    {
        Int32 maxTexImageUnits = static_cast<Int32>(win->getConstantValue(GL_MAX_TEXTURE_IMAGE_UNITS_ARB));
        _nTexImages = osgMin(maxTexImageUnits, osgMaxTexImages);

        Int32 maxFragmentShaderStorageBlocks = static_cast<Int32>(win->getConstantValue(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS));
        _nShaderStorageBlocks = osgMin(maxFragmentShaderStorageBlocks, osgMaxShaderStorageBufferBindings);

        Int32 maxFragmentUniformBlocks = static_cast<Int32>(win->getConstantValue(GL_MAX_FRAGMENT_UNIFORM_BLOCKS));
        _nUniformBlocks = osgMin(maxFragmentUniformBlocks, osgMaxUniformBufferBindings);
    }
}

Int32 MultiLightShadowTechniqueBase::getSamplerCubeArrayTextureUnit() const
{
    Int32 texUnit = _pStage->getSamplerCubeArrayTextureUnit();
    if (texUnit == -1)
        texUnit = _nTexImages - 1;
    return texUnit;
}

Int32 MultiLightShadowTechniqueBase::getSampler2DArrayTextureUnit() const
{
    Int32 texUnit = _pStage->getSampler2DArrayTextureUnit();
    if (texUnit == -1)
        texUnit = _nTexImages - 2;
    return texUnit;
}

Int32 MultiLightShadowTechniqueBase::getSamplerCubeArrayShadowTextureUnit() const
{
    Int32 texUnit = _pStage->getSamplerCubeArrayShadowTextureUnit();
    if (texUnit == -1)
        texUnit = _nTexImages - 3;
    return texUnit;
}

Int32 MultiLightShadowTechniqueBase::getSampler2DArrayShadowTextureUnit() const
{
    Int32 texUnit = _pStage->getSampler2DArrayShadowTextureUnit();
    if (texUnit == -1)
        texUnit = _nTexImages - 4;
    return texUnit;
}

Int32 MultiLightShadowTechniqueBase::getShadowDataBindingPnt() const
{
    Int32 bndPnt = _pStage->getShadowDataBindingPnt();
    if (bndPnt == -1)
        bndPnt = _nShaderStorageBlocks - 1;
    return bndPnt;
}

Int32 MultiLightShadowTechniqueBase::getShadowParameterBindingPnt() const
{
    Int32 bndPnt = _pStage->getShadowParameterBindingPnt();
    if (bndPnt == -1)
        bndPnt = _nUniformBlocks - 1;
    return bndPnt;
}

Int32 MultiLightShadowTechniqueBase::getDistributionBindingPnt() const
{
    Int32 bndPnt = _pStage->getDistributionBindingPnt();
    if (bndPnt == -1)
        bndPnt = _nUniformBlocks - 2;
    return bndPnt;
}

Real32 MultiLightShadowTechniqueBase::getBiasFactor() const
{
    return _biasFactor;
}

std::string MultiLightShadowTechniqueBase::getShadowBaseProgramSnippet() const
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
    << endl << "// generates pseudorandom number in [0, 1]"
    << endl << "// seed - world space position of a fragemnt"
    << endl << "// freq - modifier for seed. The bigger, the faster"
    << endl << "// the pseudorandom numbers will change with change of world space position"
    << endl << "// http://www.sunandblackcat.com/tipFullView.php?l=eng&topicid=35"
    << endl << "//"
    << endl << "float random(in vec3 seed, in float freq)"
    << endl << "{"
    << endl << "    //"
    << endl << "    // project seed on random constant vector"
    << endl << "    //"
    << endl << "    float dt = dot(floor(seed * freq), vec3(53.1215, 21.1352, 9.1322));"
    << endl << ""
    << endl << "    //"
    << endl << "    // return number between 0 and 1"
    << endl << "    //"
    << endl << "    return fract(sin(dt) * 2105.2354);"
    << endl << "}"
    << endl << ""
    << endl << "float randomAngle(in vec3 seed, in float freq)"
    << endl << "{"
    << endl << "    return random(seed, freq) * 6.283285;"
    << endl << "}"
    << endl << ""
    << endl << Shader::getCubemapSnippet()
/*    << endl << "void getCubeMapLocalFrame(in vec3 s, out vec3 e1, out vec3 e2)"
    << endl << "{"
    << endl << "    float absX = abs(s.x);"
    << endl << "    float absY = abs(s.y);"
    << endl << "    float absZ = abs(s.z);"
    << endl << ""
    << endl << "    bool isXPositive = s.x > 0 ? true : false;"
    << endl << "    bool isYPositive = s.y > 0 ? true : false;"
    << endl << "    bool isZPositive = s.z > 0 ? true : false;"
    << endl << ""
    << endl << "    if ( isXPositive && absX >= absY && absX >= absZ) // POSITIVE_X"
    << endl << "    {"
    << endl << "        e1 = vec3( 0, 0,-1); e2 = vec3( 0, 1, 0);"
    << endl << "    }"
    << endl << "    if (!isXPositive && absX >= absY && absX >= absZ) // NEGATIVE_X"
    << endl << "    {"
    << endl << "        e1 = vec3( 0, 0, 1); e2 = vec3( 0, 1, 0);"
    << endl << "    }"
    << endl << "    if ( isYPositive && absY >= absX && absY >= absZ) // POSITIVE_Y"
    << endl << "    {"
    << endl << "        e1 = vec3( 1, 0, 0); e2 = vec3( 0, 0,-1);"
    << endl << "    }"
    << endl << "    if (!isYPositive && absY >= absX && absY >= absZ) // NEGATIVE_Y"
    << endl << "    {"
    << endl << "        e1 = vec3( 1, 0, 0); e2 = vec3( 0, 0, 1);"
    << endl << "    }"
    << endl << "    if ( isZPositive && absZ >= absX && absZ >= absY) // POSITIVE_Z"
    << endl << "    {"
    << endl << "        e1 = vec3( 1, 0, 0); e2 = vec3( 0, 1, 0);"
    << endl << "    }"
    << endl << "    if (!isZPositive && absZ >= absX && absZ >= absY) // NEGATIVE_Z"
    << endl << "    {"
    << endl << "        e1 = vec3(-1, 0, 0); e2 = vec3( 0, 1, 0);"
    << endl << "    }"
    << endl << "}"
*/
    << endl << ""
    << endl << "float biasedZ(in float z, in float bias, in vec2 dz_duv, in vec2 offset)"
    << endl << "{"
    << endl << "    return z + dot(dz_duv, offset) - bias;"
    << endl << "}"
    << endl << ""
    << endl << "float biasedZ(in float z, in float bias)"
    << endl << "{"
    << endl << "    return z - bias;"
    << endl << "}"
    << endl << ""
    << endl << "vec2 searchRadius(in vec2 radius, in float fragDepthLS, in float zNearLight)"
    << endl << "{"
    << endl << "    return radius * (fragDepthLS - zNearLight) / fragDepthLS;"
    << endl << "}"
    << endl << ""
    << endl << "vec2 penumbraRadius(in vec2 radius, in float zReceiver, in float zBlocker)"
    << endl << "{"
    << endl << "    return radius * (zReceiver - zBlocker) / zBlocker;"
    << endl << "}"
    << endl << ""
    //
    // Projection:
    //              Zc = Ze * P33 + We * P34
    //              Wc = We * P43
    //
    // 1. Perspective Projection:
    //    i) OpenGL: P33 = -(f+n)/(f-n), P34 = -2f*n/(f-n), P43 = -1, We = 1
    //          => Wc = -Ze
    //          => Zc'= Zc/Wc = -Zc/Ze = -1/Ze * (Ze * P33 + We * P34)
    //         <=> Zc'= -P33 - P34/Ze
    //         <=> Ze = 2*f*n / (Zc'(f-n)-(f+n))
    //   ii) DirectX: P33 = f/(f-n), P34 = -f*n/(f-n), P43 = +1
    //          => Wc = Ze
    //          => Zc'= Zc/Wc = Zc/Ze = 1/Ze * (Ze * P33 + We * P34)
    //         <=> Zc'= P33 + P34/Ze
    //         <=> Ze = f*n/(f - Zc'*(f-n))
    // 2. Orthographic Projection
    //    i) OpenGL: P33 = -2/(f-n), P34 = -(f+n)/(f-n), P43 = 0, P44 = 0, We = 1
    //          => Wc = We
    //         <=> Wc = 1
    //          => Zc'= Zc/Wc = (Ze * P33 + We * P34)/Wc
    //         <=> Zc'= Ze * P33 + P34
    //         <=> Ze = -1/2 * (Zc'(f-n) + (f+n))
    //         <=> Ze = -1/2 * (f*(Zc'+1) + n*(1-Zc'))
    //   ii) DirectX: P33 = 1/(f-n), P34 = -n/(f-n), P43 = +1
    //          => Wc = We
    //         <=> Wc = 1
    //          => Zc'= Zc/Wc = (Ze * P33 + We * P34)/Wc
    //         <=> Zc'= Ze * P33 + P34
    //         <=> Ze = (Zc'- P34)/P33
    //         <=> Ze = (Zc'+n/(f-n))/(1/(f-n))
    //         <=> Ze = Zc'*(f-n) + n
    //
    << endl << "float zLSFromTSPersp(in float z, in float zNearLight, in float zFarLight)"
    << endl << "{"
    << endl << "    return zFarLight * zNearLight / (zFarLight - z * (zFarLight - zNearLight));"
    << endl << "}"
    << endl << ""
    << endl << "float zLSFromTSOrtho(in float z, in float zNearLight, in float zFarLight)"
    << endl << "{"
    << endl << "    return -0.5 * ( zFarLight*(z+1.0) + zNearLight*(1.0-z) );"
    << endl << "}"
    << endl << ""
    << endl << "float zLSFromTS(in bool isPersp, in float z, in float zNearLight, in float zFarLight)"
    << endl << "{"
    << endl << "    if (isPersp)"
    << endl << "        return zLSFromTSPersp(z, zNearLight, zFarLight);"
    << endl << "    else"
    << endl << "        return zLSFromTSOrtho(z, zNearLight, zFarLight);"
    << endl << "}"
    << endl << ""
    << endl << "vec2 projectToLight(in bool isPerspective, in vec2 size, in float fragDepthLS, in float zNearLight)"
    << endl << "{"
    << endl << "    return isPerspective ? size * zNearLight / fragDepthLS : size;"
    << endl << "}"
    << endl << ""
    << endl << "vec2 depthGradient(in vec2 uv, in float z)"
    << endl << "{"
    << endl << "    vec2 dz_duv = vec2(0.0, 0.0);"
    << endl << ""
    << endl << "    vec3 duvdist_dx = dFdx(vec3(uv, z));"
    << endl << "    vec3 duvdist_dy = dFdy(vec3(uv, z));"
    << endl << ""
    << endl << "    dz_duv.x  = duvdist_dy.y * duvdist_dx.z;"
    << endl << "    dz_duv.x -= duvdist_dx.y * duvdist_dy.z;"
    << endl << ""
    << endl << "    dz_duv.y  = duvdist_dx.x * duvdist_dy.z;"
    << endl << "    dz_duv.y -= duvdist_dy.x * duvdist_dx.z;"
    << endl << ""
    << endl << "    float det = (duvdist_dx.x * duvdist_dy.y) - (duvdist_dx.y * duvdist_dy.x);"
    << endl << "    dz_duv /= det;"
    << endl << ""
    << endl << "    return dz_duv;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Shadow map lookup for blocker search resulting in depth value."
    << endl << "//"
    << endl << "float lookUpShadowMapDir("
    << endl << "    in float          layer,"
    << endl << "    in vec2           uv,"
    << endl << "    in vec2           offset)"
    << endl << "{"
    << endl << "    uv += offset;"
    << endl << "    vec3 samplePos = vec3(uv, layer);"
    << endl << "    return texture(uShadowMapDir, samplePos).x;"
    << endl << "}"
    << endl << ""
    << endl << "float lookUpShadowMapPnt("
    << endl << "    in float            layer,"
    << endl << "    in vec3             dir,"
    << endl << "    in vec3             e1,"
    << endl << "    in vec3             e2,"
    << endl << "    in vec2             offset)"
    << endl << "{"
    << endl << "    dir += offset.x * e1 + offset.y * e2;"
    << endl << "    vec4 samplePos = vec4(dir, layer);"
    << endl << "    return texture(uShadowMapPnt, samplePos).x;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Shadow map lookup for common case resulting comparsion value"
    << endl << "//"
    << endl << "float lookUpShadowMapDir("
    << endl << "    in float          layer,"
    << endl << "    in vec2           uv,"
    << endl << "    in vec2           offset,"
    << endl << "    in float          ref)"
    << endl << "{"
    << endl << "    uv += offset;"
    << endl << "    vec3 samplePos = vec3(uv, layer);"
    << endl << "    if (uUseShadowSampler)"
    << endl << "        return texture(uShadowMapDirComp, vec4(samplePos, ref));"
    << endl << "    else"
    << endl << "        return step(ref, texture(uShadowMapDir, samplePos).x);"
    << endl << "}"
    << endl << ""
    << endl << "float lookUpShadowMapPnt("
    << endl << "    in float            layer,"
    << endl << "    in vec3             dir,"
    << endl << "    in vec3             offset,"
    << endl << "    in float            ref)"
    << endl << "{"
    << endl << "    dir += offset;"
    << endl << "    vec4 samplePos = vec4(dir, layer);"
    << endl << "    if (uUseShadowSampler)"
    << endl << "        return texture(uShadowMapPntComp, samplePos, ref);"
    << endl << "    else"
    << endl << "        return step(ref, texture(uShadowMapPnt, samplePos).x);"
    << endl << "}"
    << endl << ""
    << endl << "float lookUpShadowMapPnt("
    << endl << "    in float            layer,"
    << endl << "    in vec3             dir,"
    << endl << "    in vec3             e1,"
    << endl << "    in vec3             e2,"
    << endl << "    in vec2             offset,"
    << endl << "    in float            ref)"
    << endl << "{"
    << endl << "    dir += offset.x * e1 + offset.y * e2;"
    << endl << "    vec4 samplePos = vec4(dir, layer);"
    << endl << "    if (uUseShadowSampler)"
    << endl << "        return texture(uShadowMapPntComp, samplePos, ref);"
    << endl << "    else"
    << endl << "        return step(ref, texture(uShadowMapPnt, samplePos).x);"
    << endl << "}"
    << endl << ""
    << endl << "struct FilterParameter"
    << endl << "{"
    << endl << "    float zReceiver;"
    << endl << "    float bias;"
    << endl << "    float fragDepthLS;"
    << endl << "    float zNear;"
    << endl << "    float zFar;"
    << endl << "    vec2  filterRadius;"
    << endl << "    vec2  frustumSize;"
    << endl << "    bool  useBlocker;"
    << endl << "    bool  usePCSS;"
    << endl << "    bool  isPerspective;"
    << endl << "    float sin_a;"
    << endl << "    float cos_a;"
    << endl << "};"
    << endl << ""
    ;

    ost << endl << getFilterModeDisabledSnippet ();
    ost << endl << getFilterModeSimpleSnippet   ();

    ost << endl << getFindBlockersBoxSnippet    ();
    ost << endl << getFilterModeBoxSnippet      ();

    ost << endl << getFindBlockersPoissonSnippet();
    ost << endl << getFilterModePoissonSnippet  ();

    ost     << "const int PCF_MODE_DISABLED = 0;"
    << endl << "const int PCF_MODE_SIMPLE   = 1;"
    << endl << "const int PCF_MODE_BOX      = 2;"
    << endl << "const int PCF_MODE_POISSON  = 3;"
    << endl << ""
    << endl << "float calcPCFShadowDir("
    << endl << "        in int             mode,"
    << endl << "        in float           layer,"
    << endl << "        in vec2            uv,"
    << endl << "        in FilterParameter fp)"
    << endl << "{"
    << endl << "    float shadow = 0.0;"
    << endl << "    vec2 dz_duv  = depthGradient(uv, fp.zReceiver);"
    << endl << ""
    << endl << "    switch (mode)"
    << endl << "    {"
    << endl << "    case PCF_MODE_DISABLED:"
    << endl << "        shadow = calcPCFShadowDirSimple1(layer, uv, dz_duv, fp);"
    << endl << "        break;"
    << endl << "    case PCF_MODE_SIMPLE:"
    << endl << "        shadow = calcPCFShadowDirSimple9(layer, uv, dz_duv, fp);"
    << endl << "        break;"
    << endl << "    case PCF_MODE_BOX:"
    << endl << "        shadow = calcPCFShadowDirBox(layer, uv, dz_duv, fp);"
    << endl << "        break;"
    << endl << "    case PCF_MODE_POISSON:"
    << endl << "        shadow = calcPCFShadowDirPoisson(layer, uv, dz_duv, fp);"
    << endl << "        break;"
    << endl << "    }"
    << endl << ""
    << endl << "    return shadow;"
    << endl << "}"
    << endl << ""
    << endl << "float calcPCFShadowPnt("
    << endl << "        in int              mode,"
    << endl << "        in float            layer,"
    << endl << "        in vec3             projDir,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    float shadow = 0.0;"
    << endl << ""
    << endl << "    switch (mode)"
    << endl << "    {"
    << endl << "    case PCF_MODE_DISABLED:"
    << endl << "        shadow = calcPCFShadowPntSimple1(layer, projDir, fp);"
    << endl << "        break;"
    << endl << "    case PCF_MODE_SIMPLE:"
    << endl << "        shadow = calcPCFShadowPntCage20(layer, projDir, fp);"
    << endl << "        break;"
    << endl << "    case PCF_MODE_BOX:"
    << endl << "        shadow = calcPCFShadowPntBox(layer, projDir, fp);"
    << endl << "        break;"
    << endl << "    case PCF_MODE_POISSON:"
    << endl << "        shadow = calcPCFShadowPntPoisson(layer, projDir, fp);"
    << endl << "        break;"
    << endl << "    }"
    << endl << ""
    << endl << "    return shadow;"
    << endl << "}"
    ;

    return ost.str();
}

//
// Shadow Lookup No PCF
//
std::string MultiLightShadowTechniqueBase::getFilterModeDisabledSnippet() const
{
    using namespace std;

    stringstream ost;

    ost     << "//"
    << endl << "// no PCF"
    << endl << "//"
    << endl << "float calcPCFShadowDirSimple1("
    << endl << "        in float           layer,"
    << endl << "        in vec2            uv,"
    << endl << "        in vec2            dz_duv,"
    << endl << "        in FilterParameter fp)"
    << endl << "{"
    << endl << "    float z = biasedZ(fp.zReceiver, fp.bias);"
    << endl << "    return lookUpShadowMapDir(layer, uv, vec2(0), z);"
    << endl << "}"
    << endl << ""
    << endl << "float calcPCFShadowPntSimple1("
    << endl << "        in float            layer,"
    << endl << "        in vec3             projDir,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    float z = biasedZ(fp.zReceiver, fp.bias);"
    << endl << "    return lookUpShadowMapPnt(layer, projDir, vec3(0), z);"
    << endl << "}"
    << endl << ""
    ;

    return ost.str();
}

//
// Filter Shadow Simple
//
std::string MultiLightShadowTechniqueBase::getFilterModeSimpleSnippet() const
{
    using namespace std;

    stringstream ost;

    ost     << "//"
    << endl << "// simple kernel with 9 samples"
    << endl << "//"
    << endl << "const vec2 sampleOffsetDirections2[9]   = vec2[]"
    << endl << "("
    << endl << "    vec2(-1,-1), vec2(-1, 0), vec2(-1, 1), "
    << endl << "    vec2( 0,-1), vec2( 0, 0), vec2( 0, 1)," 
    << endl << "    vec2( 1,-1), vec2( 1, 0), vec2( 1, 1)"
    << endl << ");"
    << endl << ""
    << endl << "float calcPCFShadowDirSimple9("
    << endl << "        in float           layer,"
    << endl << "        in vec2            uv,"
    << endl << "        in vec2            dz_duv,"
    << endl << "        in FilterParameter fp)"
    << endl << "{"
    << endl << "    float shadow = 0.0;"
    << endl << "    vec2  radius = projectToLight(fp.isPerspective, fp.filterRadius / fp.frustumSize, fp.fragDepthLS, fp.zNear);"
    << endl << ""
    << endl << "    for (int i = 0; i < 9; ++i)"
    << endl << "    {"
    << endl << "        vec2 offset = sampleOffsetDirections2[i] * radius;"
    << endl << ""
    << endl << "        offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                      offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "        float z = biasedZ(fp.zReceiver, fp.bias, dz_duv, offset);"
    << endl << "        shadow += lookUpShadowMapDir(layer, uv, offset, z);"
    << endl << "    }"
    << endl << ""
    << endl << "    return shadow / 9.0;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Use cage, 20 samples"
    << endl << "//"
    << endl << "const vec3 sampleOffsetDirections3[20] = vec3[]"
    << endl << "("
    << endl << "    vec3( 1, 1, 1), vec3( 1,-1, 1), vec3(-1,-1, 1), vec3(-1, 1, 1),"
    << endl << "    vec3( 1, 1,-1), vec3( 1,-1,-1), vec3(-1,-1,-1), vec3(-1, 1,-1),"
    << endl << "    vec3( 1, 1, 0), vec3( 1,-1, 0), vec3(-1,-1, 0), vec3(-1, 1, 0),"
    << endl << "    vec3( 1, 0, 1), vec3(-1, 0, 1), vec3( 1, 0,-1), vec3(-1, 0,-1),"
    << endl << "    vec3( 0, 1, 1), vec3( 0,-1, 1), vec3( 0,-1,-1), vec3( 0, 1,-1)"
    << endl << ");"
    << endl << ""
    << endl << "float calcPCFShadowPntCage20("
    << endl << "        in float            layer,"
    << endl << "        in vec3             projDir,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    float shadow = 0.0;"
    << endl << "    float radius = fp.filterRadius.x / fp.fragDepthLS;"
    << endl << ""
    << endl << "    for (int i = 0; i < 20; i++)"
    << endl << "    {"
    << endl << "        vec3  offset = sampleOffsetDirections3[i] * radius;"
    << endl << "        float      z = biasedZ(fp.zReceiver, fp.bias);"
    << endl << "        shadow      += lookUpShadowMapPnt(layer, projDir, offset, z);"
    << endl << "    }"
    << endl << ""
    << endl << "    return shadow / 20.0;"
    << endl << "}"
    << endl << ""
    ;

    return ost.str();
}

//
// Filter Shadow Box PCF
//
std::string MultiLightShadowTechniqueBase::getFilterModeBoxSnippet() const
{
    using namespace std;

    stringstream ost;

    ost     << "//"
    << endl << "// Simple box kernel"
    << endl << "//"
    << endl << "float algoPCFShadowDirBox("
    << endl << "        in float           layer,"
    << endl << "        in vec2            uv,"
    << endl << "        in vec2            dz_duv,"
    << endl << "        in FilterParameter fp)"
    << endl << "{"
    << endl << "    float shadow = 0.0;"
    << endl << ""
    << endl << "    int N  = distribution.boxFilterSize / 2;"
    << endl << "    int N2 = 2 * N;"
    << endl << "    float anchor = float(N) - 0.5;"
    << endl << "    vec2  stepUV = fp.filterRadius / anchor;"
    << endl << ""
    << endl << "    for (int i = 0; i < N2; ++i)"
    << endl << "    {"
    << endl << "        for (int j = 0; j < N2; ++j)"
    << endl << "        {"
    << endl << "            vec2 offset = vec2( -anchor + float(i), -anchor + float(j) ) * stepUV;"
    << endl << ""
    << endl << "            offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                          offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "            float z = biasedZ(fp.zReceiver, fp.bias, dz_duv, offset);"
    << endl << "            shadow += lookUpShadowMapDir(layer, uv, offset, z);"
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    return shadow / float(N2 * N2);"
    << endl << "}"
    << endl << ""
    << endl << "float calcImplPCFShadowDirBox("
    << endl << "        in float           layer,"
    << endl << "        in vec2            uv,"
    << endl << "        in vec2            dz_duv,"
    << endl << "        in FilterParameter fp)"
    << endl << "{"
    << endl << "    fp.filterRadius = projectToLight(fp.isPerspective, fp.filterRadius / fp.frustumSize, fp.fragDepthLS, fp.zNear);"
    << endl << ""
    << endl << "    float numBlockers = 1.0;"
    << endl << "    if (fp.useBlocker)"
    << endl << "        numBlockers = findBlockersDirBoxPCF(layer, uv, dz_duv, fp);"
    << endl << "    if (numBlockers == 0.0)"
    << endl << "        return 1.0;"
    << endl << ""
    << endl << "    return algoPCFShadowDirBox(layer, uv, dz_duv, fp);"
    << endl << "}"
    << endl << ""
    << endl << "float calcImplPCSShadowDirBox("
    << endl << "        in float           layer,"
    << endl << "        in vec2            uv,"
    << endl << "        in vec2            dz_duv,"
    << endl << "        in FilterParameter fp)"
    << endl << "{"
    << endl << "    float avgBlockerDepthTS = 0.0;"
    << endl << "    float numBlockers = findBlockersDirBox(avgBlockerDepthTS, layer, uv, dz_duv, fp);"
    << endl << ""
    << endl << "    if (numBlockers == 0.0) return 1.0;"
    << endl << ""
    << endl << "    float avgBlockerDepthLS  = zLSFromTS(fp.isPerspective, avgBlockerDepthTS, fp.zNear, fp.zFar);"
    << endl << "    vec2  penumbraRadius     = penumbraRadius(fp.filterRadius, fp.fragDepthLS, avgBlockerDepthLS);"
    << endl << "    fp.filterRadius = projectToLight(fp.isPerspective, penumbraRadius / fp.frustumSize, fp.fragDepthLS, fp.zNear);"
    << endl << ""
    << endl << "    return algoPCFShadowDirBox(layer, uv, dz_duv, fp);"
    << endl << "}"
    << endl << ""
    << endl << "float calcPCFShadowDirBox("
    << endl << "        in float           layer,"
    << endl << "        in vec2            uv,"
    << endl << "        in vec2            dz_duv,"
    << endl << "        in FilterParameter fp)"
    << endl << "{"
    << endl << "    if (fp.usePCSS)"
    << endl << "        return calcImplPCSShadowDirBox(layer, uv, dz_duv, fp);"
    << endl << "    else"
    << endl << "        return calcImplPCFShadowDirBox(layer, uv, dz_duv, fp);"
    << endl << "}"
    << endl << ""
    << endl << "float algoPCFShadowPntBox("
    << endl << "        in float            layer,"
    << endl << "        in vec3             projDir,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    float shadow = 0.0;"
    << endl << ""
    << endl << "    int N  = distribution.boxFilterSize / 2;"
    << endl << "    int N2 = 2 * N;"
    << endl << "    float anchor = float(N) - 0.5;"
    << endl << "    vec2  stepUV = fp.filterRadius / anchor;"
    << endl << ""
    << endl << "    vec3 e1 = cross(projDir, vec3(0.0, 0.0, 1.0));"
    << endl << "    if (length(e1) == 0.0)"
    << endl << "        e1 = cross(projDir, vec3(0.0, 1.0, 0.0));"
    << endl << "    e1 = normalize(e1);"
    << endl << "    vec3 e2 = cross(e1, projDir);"
    << endl << ""
    << endl << "    for (int i = 0; i < N2; ++i)"
    << endl << "    {"
    << endl << "        for (int j = 0; j < N2; ++j)"
    << endl << "        {"
    << endl << "            vec2 offset = vec2( -anchor + float(i), -anchor + float(j) ) * stepUV;"
    << endl << ""
    << endl << "            offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                          offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "            float z = biasedZ(fp.zReceiver, fp.bias);"
    << endl << "            shadow += lookUpShadowMapPnt(layer, projDir, e1, e2, offset, z);"
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    return shadow / float(N2 * N2);"
    << endl << "}"
    << endl << ""
    << endl << "float calcImplPCFShadowPntBox("
    << endl << "        in float            layer,"
    << endl << "        in vec3             projDir,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    fp.filterRadius = fp.filterRadius / fp.fragDepthLS;"
    << endl << ""
    << endl << "    float numBlockers = 1.0;"
    << endl << "    if (fp.useBlocker)"
    << endl << "        numBlockers = findBlockersPntBoxPCF(layer, projDir, fp);"
    << endl << "    if (numBlockers == 0.0)"
    << endl << "        return 1.0;"
    << endl << ""
    << endl << "    return algoPCFShadowPntBox(layer, projDir, fp);"
    << endl << "}"
    << endl << ""
    << endl << "float calcImplPCSShadowPntBox("
    << endl << "        in float            layer,"
    << endl << "        in vec3             projDir,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    float avgBlockerDepthTS = 0.0;"
    << endl << "    float numBlockers = findBlockersPntBox(avgBlockerDepthTS, layer, projDir, fp);"
    << endl << ""
    << endl << "    if (numBlockers == 0.0) return 1.0;"
    << endl << ""
    << endl << "    float avgBlockerDepthLS  = avgBlockerDepthTS * fp.zFar;"
    << endl << "    vec2  penumbraRadius     = penumbraRadius(fp.filterRadius, fp.fragDepthLS, avgBlockerDepthLS);"
    << endl << "    fp.filterRadius = penumbraRadius/fp.fragDepthLS;"
    << endl << ""
    << endl << "    return algoPCFShadowPntBox(layer, projDir, fp);"
    << endl << "}"
    << endl << ""
    << endl << "float calcPCFShadowPntBox("
    << endl << "        in float            layer,"
    << endl << "        in vec3             projDir,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    if (fp.usePCSS)"
    << endl << "        return calcImplPCSShadowPntBox(layer, projDir, fp);"
    << endl << "    else"
    << endl << "        return calcImplPCFShadowPntBox(layer, projDir, fp);"
    << endl << "}"
    << endl << ""
    ;

    return ost.str();
}

//
// Find Blockers Box PCF
//
std::string MultiLightShadowTechniqueBase::getFindBlockersBoxSnippet() const
{
    using namespace std;

    stringstream ost;

    ost     << "//"
    << endl << "// Simple box kernel"
    << endl << "//"
    << endl << "float findBlockersDirBox("
    << endl << "        out float           avgBlockerDepthTS,"
    << endl << "        in  float           layer,"
    << endl << "        in  vec2            uv,"
    << endl << "        in  vec2            dz_duv,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    float blockerDepth = 0.0;"
    << endl << "    float numBlockers  = 0.0;"
    << endl << ""
    << endl << "    vec2 radius = fp.isPerspective"
    << endl << "                        ? searchRadius(fp.filterRadius, fp.fragDepthLS, fp.zNear)"
    << endl << "                        : fp.filterRadius;"
    << endl << ""
    << endl << "    int N  = distribution.boxSearchSize / 2;"
    << endl << "    int N2 = 2 * N;"
    << endl << "    float anchor = float(N) - 0.5;"
    << endl << "    vec2  stepUV = radius / anchor;"
    << endl << ""
    << endl << "    for (int i = 0; i < N2; ++i)"
    << endl << "    {"
    << endl << "        for (int j = 0; j < N2; ++j)"
    << endl << "        {"
    << endl << "            vec2 offset = vec2( -anchor + float(i), -anchor + float(j) ) * stepUV;"
    << endl << ""
    << endl << "            offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                          offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "            float     z = biasedZ(fp.zReceiver, fp.bias, dz_duv, offset);"
    << endl << "            float depth = lookUpShadowMapDir(layer, uv, offset);"
    << endl << ""
    << endl << "            float test = 1.0 - step(z, depth);"
    << endl << "            blockerDepth += test * depth;"  // if (depth < z) blockerDepth += depth;
    << endl << "            numBlockers  += test;"          // if (depth < z) numBlockers++;
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    avgBlockerDepthTS = blockerDepth / numBlockers;"
    << endl << "    return numBlockers;"
    << endl << "}"
    << endl << ""
    << endl << "float findBlockersDirBoxPCF("
    << endl << "        in  float           layer,"
    << endl << "        in  vec2            uv,"
    << endl << "        in  vec2            dz_duv,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    float numBlockers = 0.0;"
    << endl << ""
    << endl << "    vec2 radius = fp.filterRadius;"
    << endl << ""
    << endl << "    int N  = distribution.boxSearchSize / 2;"
    << endl << "    int N2 = 2 * N;"
    << endl << "    float anchor = float(N) - 0.5;"
    << endl << "    vec2  stepUV = radius / anchor;"
    << endl << ""
    << endl << "    for (int i = 0; i < N2; ++i)"
    << endl << "    {"
    << endl << "        for (int j = 0; j < N2; ++j)"
    << endl << "        {"
    << endl << "            vec2 offset = vec2( -anchor + float(i), -anchor + float(j) ) * stepUV;"
    << endl << ""
    << endl << "            offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                          offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "            float     z = biasedZ(fp.zReceiver, fp.bias, dz_duv, offset);"
    << endl << "            float depth = lookUpShadowMapDir(layer, uv, offset);"
    << endl << ""
    << endl << "            float test = 1.0 - step(z, depth);"
    << endl << "            numBlockers  += test;"          // if (depth < z) numBlockers++;
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    return numBlockers;"
    << endl << "}"
    << endl << ""
    << endl << "float findBlockersPntBox("
    << endl << "        out float            avgBlockerDepthTS,"
    << endl << "        in  float            layer,"
    << endl << "        in  vec3             projDir,"
    << endl << "        in  FilterParameter  fp)"
    << endl << "{"
    << endl << "    float blockerDepth = 0.0;"
    << endl << "    float numBlockers  = 0.0;"
    << endl << ""
    << endl << "    vec2  radius = searchRadius(fp.filterRadius, fp.fragDepthLS, fp.zNear);"
    << endl << ""
    << endl << "    int N  = distribution.boxSearchSize / 2;"
    << endl << "    int N2 = 2 * N;"
    << endl << "    float anchor = float(N) - 0.5;"
    << endl << "    vec2  stepUV = radius / anchor;"
    << endl << ""
    << endl << "    vec3 e1 = cross(projDir, vec3(0.0, 0.0, 1.0));"
    << endl << "    if (length(e1) == 0.0)"
    << endl << "        e1 = cross(projDir, vec3(0.0, 1.0, 0.0));"
    << endl << "    e1 = normalize(e1);"
    << endl << "    vec3 e2 = cross(e1, projDir);"
    << endl << ""
    << endl << "    for (int i = 0; i < N2; ++i)"
    << endl << "    {"
    << endl << "        for (int j = 0; j < N2; ++j)"
    << endl << "        {"
    << endl << "            vec2 offset = vec2( -anchor + float(i), -anchor + float(j) ) * stepUV;"
    << endl << ""
    << endl << "            offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                          offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "            float     z = biasedZ(fp.zReceiver, fp.bias);"
    << endl << "            float depth = lookUpShadowMapPnt(layer, projDir, e1, e2, offset);"
    << endl << ""
    << endl << "            float test = 1.0 - step(z, depth);"
    << endl << "            blockerDepth += test * depth;"  // if (depth < z) blockerDepth += depth;
    << endl << "            numBlockers  += test;"          // if (depth < z) numBlockers++;
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    avgBlockerDepthTS = blockerDepth / numBlockers;"
    << endl << "    return numBlockers;"
    << endl << "}"
    << endl << ""    
    << endl << "float findBlockersPntBoxPCF("
    << endl << "        in  float            layer,"
    << endl << "        in  vec3             projDir,"
    << endl << "        in  FilterParameter  fp)"
    << endl << "{"
    << endl << "    float numBlockers  = 0.0;"
    << endl << ""
    << endl << "    vec2  radius = fp.filterRadius;"
    << endl << ""
    << endl << "    int N  = distribution.boxSearchSize / 2;"
    << endl << "    int N2 = 2 * N;"
    << endl << "    float anchor = float(N) - 0.5;"
    << endl << "    vec2  stepUV = radius / anchor;"
    << endl << ""
    << endl << "    vec3 e1 = cross(projDir, vec3(0.0, 0.0, 1.0));"
    << endl << "    if (length(e1) == 0.0)"
    << endl << "        e1 = cross(projDir, vec3(0.0, 1.0, 0.0));"
    << endl << "    e1 = normalize(e1);"
    << endl << "    vec3 e2 = cross(e1, projDir);"
    << endl << ""
    << endl << "    for (int i = 0; i < N2; ++i)"
    << endl << "    {"
    << endl << "        for (int j = 0; j < N2; ++j)"
    << endl << "        {"
    << endl << "            vec2 offset = vec2( -anchor + float(i), -anchor + float(j) ) * stepUV;"
    << endl << ""
    << endl << "            offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                          offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "            float     z = biasedZ(fp.zReceiver, fp.bias);"
    << endl << "            float depth = lookUpShadowMapPnt(layer, projDir, e1, e2, offset);"
    << endl << ""
    << endl << "            float test = 1.0 - step(z, depth);"
    << endl << "            numBlockers  += test;"          // if (depth < z) numBlockers++;
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    return numBlockers;"
    << endl << "}"
    << endl << ""
    ;

    return ost.str();
}

//
// Filter Shadow Poisson PCF
//
std::string MultiLightShadowTechniqueBase::getFilterModePoissonSnippet() const
{
    using namespace std;

    stringstream ost;

    ost     << "//"
    << endl << "// Poisson kernel"
    << endl << "//"
    << endl << "float algoPCFShadowDirPoisson("
    << endl << "        in float           layer,"
    << endl << "        in vec2            uv,"
    << endl << "        in vec2            dz_duv,"
    << endl << "        in FilterParameter fp)"
    << endl << "{"
    << endl << "    float shadow = 0.0;"
    << endl << ""
    << endl << "    int kernelSize   = distribution.filterDisk.length();"
    << endl << "    int kernelOffset = 0;"
    << endl << ""
    << endl << "    for (int i = 0; i < distribution.filterDisk.length(); ++i)"
    << endl << "    {"
    << endl << "        vec2 offset = fp.filterRadius * distribution.filterDisk[kernelOffset+i];"
    << endl << ""
    << endl << "        offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                      offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "        float z = biasedZ(fp.zReceiver, fp.bias, dz_duv, offset);"
    << endl << "        shadow += lookUpShadowMapDir(layer, uv, offset, z);"
    << endl << "    }"
    << endl << ""
    << endl << "    return shadow / kernelSize;"
    << endl << "}"
    << endl << ""
    << endl << "float calcImplPCFShadowDirPoisson("
    << endl << "        in float           layer,"
    << endl << "        in vec2            uv,"
    << endl << "        in vec2            dz_duv,"
    << endl << "        in FilterParameter fp)"
    << endl << "{"
    << endl << "    fp.filterRadius = projectToLight(fp.isPerspective, fp.filterRadius / fp.frustumSize, fp.fragDepthLS, fp.zNear);"
    << endl << ""
    << endl << "    float numBlockers = 1.0;"
    << endl << "    if (fp.useBlocker)"
    << endl << "        numBlockers = findBlockersDirPoissonPCF(layer, uv, dz_duv, fp);"
    << endl << "    if (numBlockers == 0)"
    << endl << "        return 1.0;"
    << endl << ""
    << endl << "    return algoPCFShadowDirPoisson(layer, uv, dz_duv, fp);"
    << endl << "}"
    << endl << ""
    << endl << "float calcImplPCSShadowDirPoisson("
    << endl << "        in float           layer,"
    << endl << "        in vec2            uv,"
    << endl << "        in vec2            dz_duv,"
    << endl << "        in FilterParameter fp)"
    << endl << "{"
    << endl << "    float avgBlockerDepthTS = 0.0;"
    << endl << "    float numBlockers = findBlockersDirPoisson(avgBlockerDepthTS, layer, uv, dz_duv, fp);"
    << endl << ""
    << endl << "    if (numBlockers == 0.0) return 1.0;"
    << endl << ""
    << endl << "    float avgBlockerDepthLS  = zLSFromTS(fp.isPerspective, avgBlockerDepthTS, fp.zNear, fp.zFar);"
    << endl << "    vec2  penumbraRadius     = penumbraRadius(fp.filterRadius, fp.fragDepthLS, avgBlockerDepthLS);"
    << endl << "    fp.filterRadius = projectToLight(fp.isPerspective, penumbraRadius / fp.frustumSize, fp.fragDepthLS, fp.zNear);"
    << endl << ""
    << endl << "    return algoPCFShadowDirPoisson(layer, uv, dz_duv, fp);"
    << endl << "}"
    << endl << ""
    << endl << "float calcPCFShadowDirPoisson("
    << endl << "        in float           layer,"
    << endl << "        in vec2            uv,"
    << endl << "        in vec2            dz_duv,"
    << endl << "        in FilterParameter fp)"
    << endl << "{"
    << endl << "    if (fp.usePCSS)"
    << endl << "        return calcImplPCSShadowDirPoisson(layer, uv, dz_duv, fp);"
    << endl << "    else"
    << endl << "        return calcImplPCFShadowDirPoisson(layer, uv, dz_duv, fp);"
    << endl << "}"
    << endl << ""
    << endl << "float algoPCFShadowPntPoisson("
    << endl << "        in float            layer,"
    << endl << "        in vec3             projDir,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    float shadow = 0.0;"
    << endl << ""
    << endl << "    vec3 e1 = cross(projDir, vec3(0.0, 0.0, 1.0));"
    << endl << "    if (length(e1) == 0.0)"
    << endl << "        e1 = cross(projDir, vec3(0.0, 1.0, 0.0));"
    << endl << "    e1 = normalize(e1);"
    << endl << "    vec3 e2 = cross(e1, projDir);"
    << endl << ""
    << endl << "    int kernelSize   = distribution.filterDisk.length();"
    << endl << "    int kernelOffset = 0;"
    << endl << ""
    << endl << "    for (int i = 0; i < kernelSize; ++i)"
    << endl << "    {"
    << endl << "        vec2 offset = fp.filterRadius * distribution.filterDisk[kernelOffset + i];"
    << endl << ""
    << endl << "        offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                      offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "        float z = biasedZ(fp.zReceiver, fp.bias);"
    << endl << "        shadow += lookUpShadowMapPnt(layer, projDir, e1, e2, offset, z);"
    << endl << "    }"
    << endl << ""
    << endl << "    return shadow /= kernelSize;"
    << endl << "}"
    << endl << ""
    << endl << "float calcImplPCFShadowPntPoisson("
    << endl << "        in float            layer,"
    << endl << "        in vec3             projDir,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    fp.filterRadius = fp.filterRadius / fp.fragDepthLS;"
    << endl << ""
    << endl << "    float numBlockers = 1.0;"
    << endl << "    if (fp.useBlocker)"
    << endl << "        numBlockers = findBlockersPntPoissonPCF(layer, projDir, fp);"
    << endl << "    if (numBlockers == 0.0)"
    << endl << "        return 1.0;"
    << endl << ""
    << endl << "    return algoPCFShadowPntPoisson(layer, projDir, fp);"
    << endl << "}"
    << endl << ""
    << endl << "float calcImplPCSShadowPntPoisson("
    << endl << "        in float            layer,"
    << endl << "        in vec3             projDir,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    float avgBlockerDepthTS = 0.0;"
    << endl << "    float numBlockers = findBlockersPntPoisson(avgBlockerDepthTS, layer, projDir, fp);"
    << endl << ""
    << endl << "    if (numBlockers == 0.0) return 1.0;"
    << endl << ""
    << endl << "    float avgBlockerDepthLS  = avgBlockerDepthTS * fp.zFar;"
    << endl << "    vec2  penumbraRadius     = penumbraRadius(fp.filterRadius, fp.fragDepthLS, avgBlockerDepthLS);"
    << endl << "    fp.filterRadius = penumbraRadius/fp.fragDepthLS;"
    << endl << ""
    << endl << "    return algoPCFShadowPntPoisson(layer, projDir, fp);"
    << endl << "}"
    << endl << ""
    << endl << "float calcPCFShadowPntPoisson("
    << endl << "        in float            layer,"
    << endl << "        in vec3             projDir,"
    << endl << "        in FilterParameter  fp)"
    << endl << "{"
    << endl << "    if (fp.usePCSS)"
    << endl << "        return calcImplPCSShadowPntPoisson(layer, projDir, fp);"
    << endl << "    else"
    << endl << "        return calcImplPCFShadowPntPoisson(layer, projDir, fp);"
    << endl << "}"
    << endl << ""
    ;

    return ost.str();
}

//
// Find Blockers Poisson
//
std::string MultiLightShadowTechniqueBase::getFindBlockersPoissonSnippet() const
{
    using namespace std;

    stringstream ost;

    ost     << "//"
    << endl << "// Poisson kernel"
    << endl << "//"
    << endl << "float findBlockersDirPoisson("
    << endl << "        out float           avgBlockerDepthTS,"
    << endl << "        in  float           layer,"
    << endl << "        in  vec2            uv,"
    << endl << "        in  vec2            dz_duv,"
    << endl << "        in  FilterParameter fp)"
    << endl << "{"
    << endl << "    float blockerDepth = 0.0;"
    << endl << "    float numBlockers  = 0.0;"
    << endl << ""
    << endl << "    vec2 radius = fp.isPerspective"
    << endl << "                        ? searchRadius(fp.filterRadius, fp.fragDepthLS, fp.zNear)"
    << endl << "                        : fp.filterRadius;"
    << endl << ""
    << endl << "    int kernelSize   = distribution.searchDisk.length();"
    << endl << "    int kernelOffset = 0;"
    << endl << ""
    << endl << "    for (int i = 0; i < kernelSize; ++i)"
    << endl << "    {"
    << endl << "        vec2 offset = radius * distribution.searchDisk[kernelOffset + i];"
    << endl << ""
    << endl << "        offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                      offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "        float     z = biasedZ(fp.zReceiver, fp.bias, dz_duv, offset);"
    << endl << "        float depth = lookUpShadowMapDir(layer, uv, offset);"
    << endl << ""
    << endl << "        float test = 1.0 - step(z, depth);"
    << endl << "        blockerDepth += test * depth;"  // if (depth < z) blockerDepth += depth;
    << endl << "        numBlockers  += test;"          // if (depth < z) numBlockers++;
    << endl << "    }"
    << endl << ""
    << endl << "    avgBlockerDepthTS = blockerDepth / numBlockers;"
    << endl << "    return numBlockers;"
    << endl << "}"
    << endl << ""    
    << endl << "float findBlockersDirPoissonPCF("
    << endl << "        in  float           layer,"
    << endl << "        in  vec2            uv,"
    << endl << "        in  vec2            dz_duv,"
    << endl << "        in  FilterParameter fp)"
    << endl << "{"
    << endl << "    float numBlockers  = 0.0;"
    << endl << ""
    << endl << "    vec2 radius = fp.filterRadius;"
    << endl << ""
    << endl << "    int kernelSize   = distribution.searchDisk.length();"
    << endl << "    int kernelOffset = 0;"
    << endl << ""
    << endl << "    for (int i = 0; i < kernelSize; ++i)"
    << endl << "    {"
    << endl << "        vec2 offset = radius * distribution.searchDisk[kernelOffset + i];"
    << endl << ""
    << endl << "        offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                      offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "        float     z = biasedZ(fp.zReceiver, fp.bias, dz_duv, offset);"
    << endl << "        float depth = lookUpShadowMapDir(layer, uv, offset);"
    << endl << ""
    << endl << "        float test = 1.0 - step(z, depth);"
    << endl << "        numBlockers  += test;"          // if (depth < z) numBlockers++;
    << endl << "    }"
    << endl << ""
    << endl << "    return numBlockers;"
    << endl << "}"
    << endl << ""
    << endl << "float findBlockersPntPoisson("
    << endl << "        out float            avgBlockerDepthTS,"
    << endl << "        in  float            layer,"
    << endl << "        in  vec3             projDir,"
    << endl << "        in  FilterParameter  fp)"
    << endl << "{"
    << endl << "    float blockerDepth = 0.0;"
    << endl << "    float numBlockers  = 0.0;"
    << endl << ""
    << endl << "    vec3 e1 = cross(projDir, vec3(0.0, 0.0, 1.0));"
    << endl << "    if (length(e1) == 0.0)"
    << endl << "        e1 = cross(projDir, vec3(0.0, 1.0, 0.0));"
    << endl << "    e1 = normalize(e1);"
    << endl << "    vec3 e2 = cross(e1, projDir);"
    << endl << ""
    << endl << "    vec2 radius = searchRadius(fp.filterRadius, fp.fragDepthLS, fp.zNear);"
    << endl << ""
    << endl << "    int kernelSize   = distribution.searchDisk.length();"
    << endl << "    int kernelOffset = 0;"
    << endl << ""
    << endl << "    for (int i = 0; i < kernelSize; ++i)"
    << endl << "    {"
    << endl << "        vec2 offset = radius * distribution.searchDisk[kernelOffset + i];"
    << endl << ""
    << endl << "        offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                      offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "        float     z = biasedZ(fp.zReceiver, fp.bias);"
    << endl << "        float depth = lookUpShadowMapPnt(layer, projDir, e1, e2, offset);"
    << endl << ""
    << endl << "        float test = 1.0 - step(z, depth);"
    << endl << "        blockerDepth += test * depth;"  // if (depth < z) blockerDepth += depth;
    << endl << "        numBlockers  += test;"          // if (depth < z) numBlockers++;
    << endl << "    }"
    << endl << ""
    << endl << "    avgBlockerDepthTS = blockerDepth / numBlockers;"
    << endl << "    return numBlockers;"
    << endl << "}"
    << endl << ""
    << endl << "float findBlockersPntPoissonPCF("
    << endl << "        in  float            layer,"
    << endl << "        in  vec3             projDir,"
    << endl << "        in  FilterParameter  fp)"
    << endl << "{"
    << endl << "    float numBlockers  = 0.0;"
    << endl << ""
    << endl << "    vec3 e1 = cross(projDir, vec3(0.0, 0.0, 1.0));"
    << endl << "    if (length(e1) == 0.0)"
    << endl << "        e1 = cross(projDir, vec3(0.0, 1.0, 0.0));"
    << endl << "    e1 = normalize(e1);"
    << endl << "    vec3 e2 = cross(e1, projDir);"
    << endl << ""
    << endl << "    vec2 radius = fp.filterRadius;"
    << endl << ""
    << endl << "    int kernelSize   = distribution.searchDisk.length();"
    << endl << "    int kernelOffset = 0;"
    << endl << ""
    << endl << "    for (int i = 0; i < kernelSize; ++i)"
    << endl << "    {"
    << endl << "        vec2 offset = radius * distribution.searchDisk[kernelOffset + i];"
    << endl << ""
    << endl << "        offset = vec2(offset.x *  fp.cos_a + offset.y * fp.sin_a,"
    << endl << "                      offset.x * -fp.sin_a + offset.y * fp.cos_a);"
    << endl << ""
    << endl << "        float     z = biasedZ(fp.zReceiver, fp.bias);"
    << endl << "        float depth = lookUpShadowMapPnt(layer, projDir, e1, e2, offset);"
    << endl << ""
    << endl << "        float test = 1.0 - step(z, depth);"
    << endl << "        numBlockers  += test;"          // if (depth < z) numBlockers++;
    << endl << "    }"
    << endl << ""
    << endl << "    return numBlockers;"
    << endl << "}"
    << endl << ""
    ;

    return ost.str();
}

OSG_END_NAMESPACE
