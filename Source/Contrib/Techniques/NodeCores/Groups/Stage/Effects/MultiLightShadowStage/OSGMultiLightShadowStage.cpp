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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGMultiLightShadowStage.h"
#include "OSGMultiLightShadowStageData.h"
#include "OSGMultiLightShadowParameter.h"
#include "OSGMultiLightShadowTechniqueSimple.h"
#include "OSGMultiLightShadowTechniqueAdvanced.h"

#include "OSGMultiLightShadowTechniqueSimplest.h"

#include "OSGRenderAction.h"
#include <boost/bind.hpp>
#include "OSGTextureBuffer.h"

#include "OSGGeometry.h"

#include "OSGMatrixCamera.h"
#include "OSGPerspectiveCamera.h"

#include "OSGChunkOverrideGroup.h"
#include "OSGMaterialChunkOverrideGroup.h"
#include "OSGMaterialGroup.h"
#include "OSGMultiPassMaterial.h"

#include "OSGClusterShadingStage.h"
#include "OSGMultiLightGroup.h"
#include "OSGLineChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMultiLightShadowStageBase.cpp file.
// To modify it, please change the .fcd file (OSGMultiLightShadowStage.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 MultiLightShadowStage::_uiShadingLanguageARB          = Window::invalidExtensionID;
UInt32 MultiLightShadowStage::_uiFramebufferObjectARB        = Window::invalidExtensionID;

UInt32 MultiLightShadowStage::_uiFuncDrawBuffers             = Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiLightShadowStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if (ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            MultiLightShadowStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&MultiLightShadowStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            MultiLightShadowStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&MultiLightShadowStage::renderLeave));

        _uiShadingLanguageARB     =  Window::registerExtension("GL_ARB_shading_language_100");
        _uiFramebufferObjectARB   =  Window::registerExtension("GL_ARB_framebuffer_object");

        _uiFuncDrawBuffers        =  Window::registerFunction (
                                        OSG_DLSYM_UNDERSCORE"glDrawBuffersARB",
                                        _uiFramebufferObjectARB);

        Window::registerConstant(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS);
        Window::registerConstant(GL_MAX_FRAGMENT_UNIFORM_BLOCKS);
    }
}

UInt32 MultiLightShadowStage::getRequiredMultiLightFeatures(UInt32 mode)
{
    switch (mode)
    {
        case NO_SHADOW_MAP:
            return 0;
        case SIMPLE_SHADOW_MAP:
            return MultiLightShadowTechniqueSimple::getRequiredMultiLightFeatures();
        case ADVANCED_SHADOW_MAP:
            return MultiLightShadowTechniqueAdvanced::getRequiredMultiLightFeatures();

        case SIMPLE_TEST_SHADOW_MAP:
            return MultiLightShadowTechniqueSimplest::getRequiredMultiLightFeatures();

    }
    return 0;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MultiLightShadowStage::MultiLightShadowStage(void)
: Inherited              ()
, _bUpdateOffset         (false)
, _bUpdateUniformData    (false)
, _bUpdateShadowParameter(false)
, _bUpdateDistribution   (false)
{
}

MultiLightShadowStage::MultiLightShadowStage(const MultiLightShadowStage &source)
: Inherited              (source)
, _bUpdateOffset         (false)
, _bUpdateUniformData    (false)
, _bUpdateShadowParameter(false)
, _bUpdateDistribution   (false)
{
}

MultiLightShadowStage::~MultiLightShadowStage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MultiLightShadowStage::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{

    if ((whichField & (OffsetBiasFieldMask |
                       OffsetFactorFieldMask |
                       CullFrontFaceFieldMask)) != 0)
        _bUpdateOffset = true;

    if ((whichField & (ShadowOnFieldMask | 
                       UseHWPCFFieldMask |
                       ArbTestFieldMask 
                        )) != 0)
        _bUpdateUniformData = true;

    if ((whichField & (FilterDistributionSizeFieldMask | 
                       SearchDistributionSizeFieldMask)) != 0)
        _bUpdateDistribution = true;

    //ShadowModeFieldMask |

    //ShadowMapWidthFieldMask |
    //ShadowMapHeightFieldMask |
    //OffsetBiasFieldMask |
    //OffsetFactorFieldMask |
    //ExcludeNodesFieldMask |
    //AutoExcludeTransparentNodesFieldMask |
    //MultiLightChunkFieldMask |
    //AutoSearchMultiLightChunkFieldMask |
    //SamplerCubeArrayTextureUnitFieldMask |
    //Sampler2DArrayTextureUnitFieldMask |

    Inherited::changed(whichField, origin, details);
}

void MultiLightShadowStage::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MultiLightShadowStage NI" << std::endl;
}

void MultiLightShadowStage::onCreate(const MultiLightShadowStage *source)
{
    Inherited::onCreate(source);

    // if we're in startup this is the prototype ...
    if (OSG::GlobalSystemState == OSG::Startup)
        return;
}

void MultiLightShadowStage::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);
}

Action::ResultE MultiLightShadowStage::renderEnter(Action *action)
{
    if (getActivate() == false)
        return Group::renderEnter(action);

    UpdateAutoClear updateClr(this);

    Action::ResultE returnValue = Action::Continue;

    RenderAction* ract = dynamic_cast<RenderAction*>(action);
    if (ract == NULL)
        return returnValue;

    //
    // Precheck of the driver/hardware capabilities; the tree handler do check for
    // themselves later on...
    //
    if (   ract->getWindow()->hasExtOrVersion(_uiShadingLanguageARB,   0x0200, 0x0200) == false
        || ract->getWindow()->hasExtOrVersion(_uiFramebufferObjectARB, 0x0300, 0x0200) == false
        || ract->getWindow()->hasExtOrVersion(_uiFuncDrawBuffers,      0x0300        ) == false
       )
    {
        return returnValue;
    }

    //
    // Search for an appropriate MultiLightChunk. If not found we have nothing to do.
    //
    bool result = findMultiLightChunk(ract->getActNode());
    if (!result)
        return returnValue;

    //
    // Access/create the stage data object
    //
    MultiLightShadowStageData* pData = ract->getData<MultiLightShadowStageData*>(_iDataSlotId);
    if (pData == NULL)
    {
        MultiLightShadowStageDataUnrecPtr pTmp = MultiLightShadowStageData::createLocal();

        pData = pTmp;

        this->setData(pData, _iDataSlotId, ract);
    }

    //
    // Access/create the requested tree handler. These classes implement the
    // details of the shadow techniques.
    //
    MultiLightShadowTechniqueBase* pTechnique = pData->getTechnique();

    if (_bUpdateDistribution)
    {
        //
        // Current override program must be replaced.
        //
        pData->setOverrideProgChunk(NULL);
        pData->setOverrideProgram  (NULL);
    }

    if (pTechnique == NULL || this->getShadowMode() != pTechnique->getMode())
    {
        //
        // Current override program must be replaced.
        //
        if (pTechnique != NULL)
        {
            pData->setOverrideProgChunk(NULL);
            pData->setOverrideProgram  (NULL);
        }

        bool install_default_override = false;;

        pTechnique = NULL;

        switch (getShadowMode())
        {
            case NO_SHADOW_MAP:
            {
                FNOTICE(("No Shadows...\n"));
                //
                // Install a default override that does not produce shadows
                //
                install_default_override = true;
            }
            break;
            
            //
            // A simple shadow map implementation with a fixed shadow map size
            //
            case SIMPLE_SHADOW_MAP:
            {
                FNOTICE(("using simple Shadow Mapping...\n"));
                pTechnique = new MultiLightShadowTechniqueSimple(this,
                                                                 pData,
                                                                 ract->getWindow());

                _bUpdateShadowParameter = true;
                _bUpdateDistribution    = true;
            }
            break;

            //
            // An advanced shadow map implementation with a fixed shadow map size,
            // but with focusing, Lisp, etc.
            //
            case ADVANCED_SHADOW_MAP:
            {
                FNOTICE(("using advanced Shadow Mapping...\n"));
                pTechnique = new MultiLightShadowTechniqueAdvanced(this,
                                                                   pData,
                                                                   ract->getWindow());

                _bUpdateShadowParameter = true;
                _bUpdateDistribution    = true;
            }
            break;
            
            case SIMPLE_TEST_SHADOW_MAP:
            {
                FNOTICE(("using simple test Shadow Mapping...\n"));
                pTechnique = new MultiLightShadowTechniqueSimplest(this,
                                                                     pData,
                                                                     ract->getWindow());

                _bUpdateShadowParameter = true;
                _bUpdateDistribution    = true;
            }
            break;

            default:
            {
                install_default_override = true;
            }
            break;
        }

        //
        // If technique is not realizable on the current platform use fallback
        //
        if (pTechnique && pTechnique->hasExtOrVersion(ract) == false)
        {
            install_default_override = true;

            this->setShadowMode(NO_SHADOW_MAP);

            pTechnique = NULL;
        }

        pData->setTechnique(pTechnique);

        //
        // Fallback, override which does not produce shadows
        //
        if (install_default_override)
        {
            initOverrideShaderProgram(pData);

            //
            // Early out, just render with the fallback override
            //
            ract->pushState();

            addOverride(pData, ract);

            commitChanges();

            this->recurseFromThis(ract);
            ract->useNodeList(false);

            ract->popState();

            return Action::Skip;
        }
    }

    //
    // Fill the stage data it's LightAssocStore and determine if any shadow work is 
    // actually to be done.
    //
    inspectMultiLight(pData);

    //
    // Access the data storage that is associated with each view.
    //
    MultiLightShadowStageData::TravMaskStore& vExclTravMask   = pData->getExcludeNodeTravMask();
    MultiLightShadowStageData::TravMaskStore& vTranspTravMask = pData->getTransparentNodeTravMask();
    MultiLightShadowStageData::NodeStore&     vTransparents   = pData->getTransparents();

    //
    // find transparent nodes
    //
    vTransparents.clear();

    if (getAutoExcludeTransparentNodes())
    {
        traverse(action->getActNode(), 
                    boost::bind(&MultiLightShadowStage::findTransparent,
                                this, 
                                pData,
                                _1) );
    }

    //
    // Memorize the taversal mask of the excluded nodes, so that we can restore this mask
    // at the end of the render cycle. Then zero the mask so that the particular node is
    // not taken into account.
    //

    std::size_t numExcludedNodes = getMFExcludeNodes()->size();
    vExclTravMask.resize(numExcludedNodes, 0);

    for (std::size_t i = 0; i < numExcludedNodes; ++i)
    {
        Node* node = getExcludeNodes(static_cast<UInt32>(i));

        if (node != NULL)
        {
            vExclTravMask[i] = node->getTravMask();
            node->setTravMask(0);
        }
    }

    //
    // Memorize the taversal mask of the transparent nodes, so that we can restore this mask
    // at the end of the render cycle. Then zero the mask so that the particular node is
    // not taken into account.
    //

    std::size_t numTransparentNodes = vTransparents.size();
    vTranspTravMask.resize(numTransparentNodes, 0);

    for (std::size_t i = 0; i < numTransparentNodes; ++i)
    {
        Node* node = vTransparents[i];

        if (node != NULL)
        {
            vTranspTravMask[i] = node->getTravMask();
            node->setTravMask(0);
        }
    }

    DrawEnv& rEnv = ract->getActivePartition()->getDrawEnv();

    this->beginPartitionGroup(ract);
    {
        pTechnique->render(ract, &rEnv);
    }
    this->endPartitionGroup(ract);

    //
    // Restore the traversal mask of the transparent nodes.
    //
    for (std::size_t i = 0; i < numTransparentNodes; ++i)
    {
        Node* node = vTransparents[i];

        if (node != NULL)
        {
            node->setTravMask(vTranspTravMask[i]);
        }
    }

    //
    // Restore the traversal mask of the excluded nodes.
    //
    for (std::size_t i = 0; i < numExcludedNodes; ++i)
    {
        Node* node = getExcludeNodes(static_cast<UInt32>(i));

        if (node != NULL)
        {
            node->setTravMask(vExclTravMask[i]);
        }
    }

    ract->pushState();

    pTechnique->addOverride(ract, &rEnv);

    commitChanges();

    this->recurseFromThis(ract);
    ract->useNodeList(false);

    ract->popState();

    return Action::Skip;

}

Action::ResultE MultiLightShadowStage::renderLeave(Action *action)
{
    if (getActivate() == false)
        return Group::renderLeave(action);

    return Action::Skip;
}

/*------------------------------ details ----------------------------------*/

Action::ResultE MultiLightShadowStage::findTransparent(
    MultiLightShadowStageData* pData,
    Node* const                node)
{
    if (node->getCore() != NULL)
    {
        MultiLightShadowStageData::NodeStore &vTransparents = pData->getTransparents();

        if (node->getCore()->getType() ==      Geometry::getClassType() ||
            node->getCore()->getType() == MaterialGroup::getClassType())
        {
            Material*          mat      = NULL;
            MultiPassMaterial* multiMat = NULL;

            Geometry*          geo      = dynamic_cast<Geometry*     >(node->getCore());
            MaterialGroup*     matGroup = dynamic_cast<MaterialGroup*>(node->getCore());

            if (geo != NULL)
                mat = geo->getMaterial();
            if (matGroup != NULL)
                mat = matGroup->getMaterial();

            if (mat != NULL)
            {
                // isTransparent in MultiPassMaterial returns false,
                // if one Material is not transparent. Here we need
                // to know if one Material is transparent so we can't
                // use isTransparent for MultiPassMaterials.

                multiMat = dynamic_cast<MultiPassMaterial*>(mat);

                if (multiMat != NULL)
                {
                    MultiPassMaterial::MFMaterialsType::const_iterator it = 
                        multiMat->getMFMaterials()->begin();

                    MultiPassMaterial::MFMaterialsType::const_iterator matsEnd =
                        multiMat->getMFMaterials()->end();

                    for (;it != matsEnd; ++it)
                    {
                        if ((*it) == NULL)
                            continue;

                        if ((*it)->isTransparent() && node->getTravMask() != 0)
                        {
                            vTransparents.push_back(node);
                            break;
                        }
                    }
                }
                else
                {
                    if (mat->isTransparent() && node->getTravMask() != 0)
                        vTransparents.push_back(node);
                    else
                    {
                        // HF: Bug 9111112: Exclude Materials with LineChunk (Silhouettes / Edges)
                        LineChunk* pLineChunk = NULL;
                        if (mat->getType().isDerivedFrom(ChunkMaterial::getClassType()))
                        {
                            ChunkMaterial* chunkMat = dynamic_cast<ChunkMaterial*>(mat);
                            UInt32 numChunks = static_cast<UInt32>(chunkMat->getMFChunks()->size());
                            for (UInt32 i = 0; i < numChunks; ++i)
                            {
                                pLineChunk = dynamic_cast<LineChunk*>(chunkMat->getChunk(i));
                                if (pLineChunk)
                                    break;
                            }
                        }
                        if (pLineChunk)
                            vTransparents.push_back(node);
                    }
                }
            }
        }
    }
    return Action::Continue;
}

//
// Search for a valid MultiLightChunk in the parent tree. We assume that the
// MultiLightChunk is either part of a ChunkMaterial or that it is part of
// a MultiLightGroup or a ClusterShadingStage in the parent tree. We do not 
// search downward!
//
bool MultiLightShadowStage::findMultiLightChunk(Node* node)
{
    if (getAutoSearchMultiLightChunk() == true)
    {
        MultiLightChunk* pChunk = NULL;

        while (node != NULL && pChunk == NULL)
        {
            NodeCore* core = node->getCore();
            if (core)
            {
                pChunk = findMultiLightChunk(core);
                if (pChunk)
                {
                    setMultiLightChunk(pChunk);
                    return true;
                }
            }
            node = node->getParent();
        }
    }
    else
    {
        if (getMultiLightChunk() != NULL)
            return true;
    }
    return false;
}

MultiLightChunk* MultiLightShadowStage::findMultiLightChunk(NodeCore* core)
{
    MultiLightChunk* pChunk = NULL;

    if (core->getType().isDerivedFrom(MultiCore::getClassType()))
    {
        MultiCore* pCore = dynamic_cast<MultiCore*>(core);

        MultiCore::MFCoresType::const_iterator cIt  = pCore->getMFCores()->begin();
        MultiCore::MFCoresType::const_iterator cEnd = pCore->getMFCores()->end();

        for (; cIt != cEnd; ++cIt)
        {
            pChunk = findMultiLightChunk(*cIt);
            if (pChunk)
                break;
        }
    }
    else
    {
        if (core->getType().isDerivedFrom(MultiLightGroup::getClassType()))
        {
            MultiLightGroup* group = dynamic_cast<MultiLightGroup*>(core);
            pChunk = group->getMultiLightChunk();
        }
        else
        if (core->getType().isDerivedFrom(ClusterShadingStage::getClassType()))
        {
            ClusterShadingStage* group = dynamic_cast<ClusterShadingStage*>(core);
            pChunk = group->getMultiLightChunk();
        }
        else
        if (core->getType().isDerivedFrom(MaterialGroup::getClassType()))
        {
            MaterialGroup* group = dynamic_cast<MaterialGroup*>(core);
            pChunk = findMultiLightChunk(group->getMaterial());
        }
        else
        if (core->getType().isDerivedFrom(MaterialChunkOverrideGroup::getClassType()))
        {
            MaterialChunkOverrideGroup* group = dynamic_cast<MaterialChunkOverrideGroup*>(core);
            pChunk = findMultiLightChunk(group->getMaterial());
        }
        else
        if (core->getType().isDerivedFrom(ChunkOverrideGroup::getClassType()))
        {
            ChunkOverrideGroup* group = dynamic_cast<ChunkOverrideGroup*>(core);

            if (group->getSubOverride() == false)
            {
                ChunkBlock* pBlock = group->finalize(0x0000);
                if (pBlock != NULL)
                {
                    MFUnrecStateChunkPtr::const_iterator chIt   = pBlock->beginChunks();
                    MFUnrecStateChunkPtr::const_iterator chEnd  = pBlock->endChunks  ();

                    while (chIt != chEnd)
                    {
                        if (*chIt != NULL && (*chIt)->getIgnore() == false)
                        {
                            if (group->getSubOverride() == false)
                            {
                                pChunk = dynamic_cast<MultiLightChunk*>(*chIt);
                                if (pChunk)
                                    break;
                            }
                        }

                        ++chIt;
                    }
                }
            }
        }
    }
    return pChunk;
}

MultiLightChunk* MultiLightShadowStage::findMultiLightChunk(Material* material)
{
    MultiLightChunk* pChunk = NULL;

    if (material->getType().isDerivedFrom(ChunkMaterial::getClassType()))
    {
        ChunkMaterial* chunkMat = dynamic_cast<ChunkMaterial*>(material);
        UInt32 numChunks = static_cast<UInt32>(chunkMat->getMFChunks()->size());
        for (UInt32 i = 0; i < numChunks; ++i)
        {
            pChunk = dynamic_cast<MultiLightChunk*>(chunkMat->getChunk(i));
            if (pChunk)
                break;
        }
    }

    return pChunk;
}

//
// Duty of this function is to fill the stage data it's LightAssocStore
// and to determine if any shadow work is to do. This function dispatches
// part of its work to the current technique instance in order to allow
// various implementation techniques with respect to transform, beacon and
// camera.
//
bool MultiLightShadowStage::inspectMultiLight(MultiLightShadowStageData* pData)
{
    OSG_ASSERT(pData != NULL);

    MultiLightShadowStageData::LightAssocStore& vLightAssocData = pData->getLightAssocData();

    MultiLightChunk* pChunk = getMultiLightChunk();

    OSG_ASSERT(pChunk != NULL);

    if (!pChunk->getHasShadow())
        return false;

    UInt32 num_lights = pChunk->getNumLights();

    if (num_lights == 0)
    {
        vLightAssocData.resize(0);
        return false;
    }

    bool rebuild_store    = false;
    bool has_active_light = false;

    if (vLightAssocData.size() != num_lights)
    {
        rebuild_store = true;
    }
    else
    {
        for (UInt32 idx = 0; idx < num_lights; ++idx)
        {
            if (vLightAssocData[idx].enabled && vLightAssocData[idx].shadow)
                has_active_light = true;

            if (   pChunk->getTypeOfLight         (idx) != vLightAssocData[idx].typeOfLight
                || pChunk->getEnabled             (idx) != vLightAssocData[idx].enabled
                || pChunk->getShadow              (idx) != vLightAssocData[idx].shadow
                || pChunk->getShadowParameterIndex(idx) != vLightAssocData[idx].shadowParamIdx)
            {
                rebuild_store = true;
                break;
            }
        }
    }

    if (rebuild_store)
    {
        MultiLightShadowStageData::LightIndexStore& vPointLightIndices = pData->getPointLightIndices();
        MultiLightShadowStageData::LightIndexStore& vSpotLightIndices  = pData->getSpotLightIndices();
        MultiLightShadowStageData::LightIndexStore& vDirLightIndices   = pData->getDirLightIndices();

        MultiLightShadowTechniqueBase* pTechnique = pData->getTechnique();

        vLightAssocData.resize(num_lights);

        vPointLightIndices.clear();
        vSpotLightIndices.clear();
        vDirLightIndices.clear();

        has_active_light = false;

        for (UInt32 idx = 0; idx < num_lights; ++idx)
        {
            vLightAssocData[idx].typeOfLight    = pChunk->getTypeOfLight         (idx);
            vLightAssocData[idx].enabled        = pChunk->getEnabled             (idx);
            vLightAssocData[idx].shadow         = pChunk->getShadow              (idx);
            vLightAssocData[idx].shadowParamIdx = pChunk->getShadowParameterIndex(idx);

            if (vLightAssocData[idx].enabled && vLightAssocData[idx].shadow)
            {
                has_active_light = true;

                //
                // Technique variation point: a technique might work with a
                // camera, beacon, tansform setup to define the lights in 
                // space with its projection type. Other might calculate the
                // necessary information by other mean. For instance the
                // simple shadow technique does not use a camera and therefor
                // implements the following function empty.
                //
                pTechnique->initializeAssocData(idx);
                
                switch (vLightAssocData[idx].typeOfLight) {
                    case MultiLight::DIRECTIONAL_LIGHT:
                        vDirLightIndices.push_back(idx);
                        break;
                    case MultiLight::POINT_LIGHT:
                        vPointLightIndices.push_back(idx);
                        break;
                    case MultiLight::SPOT_LIGHT:
                    case MultiLight::CINEMA_LIGHT:
                        vSpotLightIndices.push_back(idx);
                        break;
                }
            }
        }
    }

    return has_active_light;
}

/*--------------------------- Fallback override -----------------------------*/

void MultiLightShadowStage::initOverrideShaderProgram(
    MultiLightShadowStageData* pData)
{
    ShaderProgramChunk* progChunk = pData->getOverrideProgChunk();
    if (progChunk == NULL)
    {
        ShaderProgramChunkUnrecPtr chunk = ShaderProgramChunk::createLocal();
        pData->setOverrideProgChunk(chunk);

        progChunk = chunk;
    }

    ShaderProgram* shaderProg = pData->getOverrideProgram();
    if (shaderProg == NULL)
    {
        ShaderProgramUnrecPtr shader = ShaderProgram::createLocal();
        pData->setOverrideProgram(shader);

        shader->setShaderType(GL_FRAGMENT_SHADER);
        shader->setProgram(getFragmentProgramImplSnippet());

        progChunk->addShader(shader);
    }
}

void MultiLightShadowStage::addOverride(
    MultiLightShadowStageData* pData,
    RenderAction* a)
{
    a->addOverride(ShaderProgramChunk::getStaticClassId(), pData->getOverrideProgChunk());
}

/*--------------------------- Shadow parameter ------------------------------*/

UInt32 MultiLightShadowStage::addShadowParameter(MultiLightShadowParameter* param)
{
    Inherited::pushToShadowParameter(param);
    
    param->addChangedFunctor(
            boost::bind(&MultiLightShadowStage::changedShadowParameter, this, _1, _2, _3),
            "");
    
    return static_cast<UInt32>(_mfShadowParameter.size() - 1);
}

void MultiLightShadowStage::removeShadowParameter(MultiLightShadowParameter* param)
{
    param->subChangedFunctor(
            boost::bind(&MultiLightShadowStage::changedShadowParameter, this, _1, _2, _3));
    
    Inherited::removeObjFromShadowParameter(param);
}

void MultiLightShadowStage::removeShadowParameter(const UInt32 index)
{
    MultiLightShadowParameter* param = _mfShadowParameter[index];

    param->subChangedFunctor(
            boost::bind(&MultiLightShadowStage::changedShadowParameter, this, _1, _2, _3));

    this->removeFromShadowParameter(index);
}

void MultiLightShadowStage::clearShadowParameters()
{
    MFUnrecMultiLightShadowParameterPtr::iterator iter = _mfShadowParameter.begin();
    MFUnrecMultiLightShadowParameterPtr::iterator end  = _mfShadowParameter.end();
    
    for (; iter != end; ++iter)
    {
        MultiLightShadowParameter* param = *iter;
        param->subChangedFunctor(
            boost::bind(&MultiLightShadowStage::changedShadowParameter, this, _1, _2, _3));
    }
    
    Inherited::clearShadowParameter();
}

void MultiLightShadowStage::changedShadowParameter(
    FieldContainer*     pFC, 
    ConstFieldMaskArg   whichField, 
    UInt32              origin)
{
    switch (getShadowMode())
    {
        case SIMPLE_SHADOW_MAP:
            _bUpdateShadowParameter = MultiLightShadowTechniqueSimple::changedShadowParameter(pFC, whichField, origin);
            break;

        case ADVANCED_SHADOW_MAP:
            _bUpdateShadowParameter = MultiLightShadowTechniqueAdvanced::changedShadowParameter(pFC, whichField, origin);
            break;

        case SIMPLE_TEST_SHADOW_MAP:
            _bUpdateShadowParameter = MultiLightShadowTechniqueSimplest::changedShadowParameter(pFC, whichField, origin);
            break;

        default:
            _bUpdateShadowParameter = false;
    }
}

/*----------------------- Shader Program Snippets -------------------------*/

std::string MultiLightShadowStage::getFragmentProgramSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "//-- MultiLightShadwoStage::getFragmentProgramSnippet() --"
    << endl << "//"
    << endl << "//      Shadow functions forward declarations"
    << endl << "//"
    << endl << "float shadowAttenuationDirectionalLight(in float fragDepthES, in vec3 fragPos, in vec3 normalWS, in Light light);"
    << endl << "float shadowAttenuationPointLight      (in float fragDepthES, in vec3 fragPos, in vec3 normalWS, in Light light);"
    << endl << "float shadowAttenuationSpotLight       (in float fragDepthES, in vec3 fragPos, in vec3 normalWS, in Light light);"
    << endl << "float shadowAttenuationCinemaLight     (in float fragDepthES, in vec3 fragPos, in vec3 normalWS, in Light light);"
    << endl << "vec4  shadowSplitIndexTest             (in float fragDepthES, in Light light);"
    << endl << "bool  shadowTestShader                 (in int idx, in Light light);"
    ;

    return ost.str();
}

std::string MultiLightShadowStage::getFragmentProgramImplSnippet() const
{
    using namespace std;

    stringstream ost;

    MultiLightChunk* pMLChunk = getMultiLightChunk();
    
    ost     << "#version 330 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects:   enable"
    << endl << ""
    << pMLChunk->getFragmentProgramSnippet(false, false)  // Light struct declaration only
    << endl << ""
    << endl << "float shadowAttenuationDirectionalLight(in float fragDepthES, in vec3 fragPosWS, in vec3 normalWS, in Light light)"
    << endl << "{"
    << endl << "    return 1.0;"
    << endl << "}"
    << endl << ""
    << endl << "float shadowAttenuationPointLight(in float fragDepthES, in vec3 fragPosWS, in vec3 normalWS, in Light light)"
    << endl << "{"
    << endl << "    return 1.0;"
    << endl << "}"
    << endl << ""
    << endl << "float shadowAttenuationSpotLight(in float fragDepthES, in vec3 fragPosWS, in vec3 normalWS, in Light light)"
    << endl << "{"
    << endl << "    return 1.0;"
    << endl << "}"
    << endl << ""
    << endl << "float shadowAttenuationCinemaLight(in float fragDepthES, in vec3 fragPosWS, in vec3 normalWS, in Light light)"
    << endl << "{"
    << endl << "    return 1.0;"
    << endl << "}"
    << endl << ""
    << endl << "vec4 shadowSplitIndexTest(in float fragDepthES, in Light light)"
    << endl << "{"
    << endl << "    return vec4(0);"
    << endl << "}"
    ;
    return ost.str();
}

OSG_END_NAMESPACE
