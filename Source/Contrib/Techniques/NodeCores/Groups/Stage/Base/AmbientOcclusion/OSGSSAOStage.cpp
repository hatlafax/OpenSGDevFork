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

#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGRenderAction.h"

#include "OSGSSAOStage.h"
#include "OSGSSAOStageData.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"

#include "OSGChunkMaterial.h"
#include "OSGBlendChunk.h"
#include "OSGDepthChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGDrawEnv.h"
#include "OSGImageFunctions.h"
#include "OSGStateOverride.h"
#include "OSGTextureEnvChunk.h"
#include "OSGSimpleSHLFunctions.h"
#include "OSGSimpleSHLVariableChunk.h"
#include "OSGUniformBufferObjStd140Chunk.h"

#include "OSGMatrixUtility.h"
#include "OSGShaderUtility.h"
#include "OSGPoissonDistribution.h"
#include "OSGRandomPoolManager.h"
#include "OSGBaseInterpolators.h"

#include "OSGGLU.h"
#include "OSGGLDebugUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSSAOStageBase.cpp file.
// To modify it, please change the .fcd file (OSGSSAOStage.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 SSAOStage::_uiFramebufferObjectExt = 
    Window::invalidExtensionID;

UInt32 SSAOStage::_uiFuncDrawBuffers      =
    Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SSAOStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            SSAOStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&SSAOStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            SSAOStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&SSAOStage::renderLeave));

        _uiFramebufferObjectExt = 
            Window::registerExtension("GL_ARB_framebuffer_object");

        _uiFuncDrawBuffers  =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDrawBuffersARB", 
                _uiFramebufferObjectExt);
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SSAOStage::SSAOStage(void)
: Inherited             ()
, _mapUpdate            ()
, _mapUpdateOffsetKernel()
, _mapUpdateRotateKernel()
{
}

SSAOStage::SSAOStage(const SSAOStage &source)
: Inherited             (source)
, _mapUpdate            (      )
, _mapUpdateOffsetKernel(      )
, _mapUpdateRotateKernel(      )
{
}

SSAOStage::~SSAOStage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SSAOStage::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if((whichField & (  OffsetKernelSizeFieldMask |
                        RotateKernelSizeFieldMask |
                        RadiusFieldMask |
                        BiasFieldMask |
                        BlurKernelSizeFieldMask |
                        AmbientOcclusionTexUnitFieldMask)) != 0)
    {
        UpdateMapT::iterator iter = _mapUpdate.begin();
        UpdateMapT::iterator end  = _mapUpdate.end  ();

        for (; iter != end; ++iter)
            iter->second = true;
    }

    if((whichField & ( OffsetKernelSizeFieldMask )) != 0)
    {
        UpdateMapT::iterator iter = _mapUpdateOffsetKernel.begin();
        UpdateMapT::iterator end  = _mapUpdateOffsetKernel.end  ();

        for (; iter != end; ++iter)
            iter->second = true;
    }

    if((whichField & ( RotateKernelSizeFieldMask )) != 0)
    {
        UpdateMapT::iterator iter = _mapUpdateRotateKernel.begin();
        UpdateMapT::iterator end  = _mapUpdateRotateKernel.end  ();

        for (; iter != end; ++iter)
            iter->second = true;
    }
    
    
    Inherited::changed(whichField, origin, details);
}

void SSAOStage::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SSAOStage NI" << std::endl;
}

#ifdef OSG_DEBUG_SSAO_STAGE
void SSAOStage::dump_fbo(const char* name, FrameBufferObject* fbo, std::stringstream& ss) const
{
    ss << "FrameBufferObject*    p" << name << "FBO = " << std::hex << fbo << std::endl;

    if (fbo == NULL)
        return;

    TextureBuffer* pColorTexBuffer   = dynamic_cast<TextureBuffer*>(fbo->getColorAttachments(0));
    if (pColorTexBuffer)
    {
        ss << "TextureBuffer*    p" << name << "ColorTB = " << std::hex << pColorTexBuffer << std::endl;

        TextureObjChunk* pTexObjChunk  = pColorTexBuffer->getTexture();
        Image*           pImg          = pTexObjChunk->getImage();

        ss << "TextureObjChunk* p" << name << "ColorTBO = " << std::hex << pTexObjChunk << std::endl;
        ss << "Image*           p" << name << "ColorIMG = " << std::hex << pImg << std::endl;
        ss << "    DataType       = " << convertGLenumToString(pImg->getDataType())               << " = " << std::dec << pImg->getDataType() << std::endl;
        ss << "    PixelFormat    = " << convertGLenumToString(pImg->getPixelFormat())            << " = " << std::dec << pImg->getPixelFormat() << std::endl;
        ss << "    InternalFormat = " << convertGLenumToString(pTexObjChunk->getInternalFormat()) << " = " << std::dec << pTexObjChunk->getInternalFormat() << std::endl;
    }

    TextureBuffer* pDepthTexBuffer   = dynamic_cast<TextureBuffer*>(fbo->getDepthAttachment());
    if (pDepthTexBuffer)
    {
        ss << "TextureBuffer*    p" << name << "DepthTB = " << std::hex << pDepthTexBuffer << std::endl;

        TextureObjChunk* pTexObjChunk  = pDepthTexBuffer->getTexture();
        Image*           pImg          = pTexObjChunk->getImage();

        ss << "TextureObjChunk* p" << name << "DepthTBO = " << std::hex << pTexObjChunk << std::endl;
        ss << "Image*           p" << name << "DepthIMG = " << std::hex << pImg << std::endl;
        ss << "    DataType       = " << convertGLenumToString(pImg->getDataType())               << " = " << std::dec << pImg->getDataType() << std::endl;
        ss << "    PixelFormat    = " << convertGLenumToString(pImg->getPixelFormat())            << " = " << std::dec << pImg->getPixelFormat() << std::endl;
        ss << "    InternalFormat = " << convertGLenumToString(pTexObjChunk->getInternalFormat()) << " = " << std::dec << pTexObjChunk->getInternalFormat() << std::endl;
    }

    TextureBuffer* pStencilTexBuffer = dynamic_cast<TextureBuffer*>(fbo->getStencilAttachment());
    if (pStencilTexBuffer)
    {
        ss << "TextureBuffer*   p" << name << "StencilTB  = " << std::hex << pStencilTexBuffer << std::endl;

        TextureObjChunk* pTexObjChunk  = pStencilTexBuffer->getTexture();
        Image*           pImg          = pTexObjChunk->getImage();

        ss << "TextureObjChunk* p" << name << "StencilTBO = " << std::hex << pTexObjChunk << std::endl;
        ss << "Image*           p" << name << "StencilIMG = " << std::hex << pImg << std::endl;
        ss << "    DataType       = " << convertGLenumToString(pImg->getDataType())               << " = " << std::dec << pImg->getDataType() << std::endl;
        ss << "    PixelFormat    = " << convertGLenumToString(pImg->getPixelFormat())            << " = " << std::dec << pImg->getPixelFormat() << std::endl;
        ss << "    InternalFormat = " << convertGLenumToString(pTexObjChunk->getInternalFormat()) << " = " << std::dec << pTexObjChunk->getInternalFormat() << std::endl;
    }

    RenderBuffer* pColorRenderBuffer   = dynamic_cast<RenderBuffer*>(fbo->getColorAttachments(0));
    if (pColorRenderBuffer)
    {
        ss << "RenderBuffer*    p" << name << "ColorRB = " << std::hex << pColorRenderBuffer << std::endl;
    }

    RenderBuffer* pDepthRenderBuffer   = dynamic_cast<RenderBuffer*>(fbo->getDepthAttachment());
    if (pDepthRenderBuffer)
    {
        ss << "RenderBuffer*    p" << name << "DepthRB = " << std::hex << pDepthRenderBuffer << std::endl;
    }

    RenderBuffer* pStencilRenderBuffer = dynamic_cast<RenderBuffer*>(fbo->getStencilAttachment());
    if (pStencilRenderBuffer)
    {
        ss << "RenderBuffer*    p" << name << "StencilRB = " << std::hex << pStencilRenderBuffer << std::endl;
    }

    ss << std::endl;
}

std::string SSAOStage::dump_stage(SSAOStageData* pData) const
{
    std::stringstream ss;
    ss << std::endl;
    
    FrameBufferObject* pSceneFBO = pData->getScenePassRenderTarget();
    FrameBufferObject* pSSAOFBO  = pData->getSSAOPassRenderTarget();
    FrameBufferObject* pBlurFBO  = pData->getBlurPassRenderTarget();

    dump_fbo("Scene", pSceneFBO, ss);
    dump_fbo("SSAO",  pSSAOFBO,  ss);
    dump_fbo("Blur",  pBlurFBO,  ss);
    return ss.str();
}

void SSAOStage::dump_image(const char* name, FrameBufferAttachment* fba) const
{
    if (fba)
    {
        TextureBuffer* tb = dynamic_cast<TextureBuffer*>(fba);
        if (tb)
        {
            TextureObjChunk* texObj  = tb->getTexture();
            if (texObj)
            {
                Image* img = texObj->getImage();
                if (img)
                {
                    img->write(name);
                }
            }
        }
    }
}

#endif

/*------------------------------- Draw ------------------------------------*/

Action::ResultE SSAOStage::renderEnter(Action* action)
{
    if (getActivate() == false)
        return Group::renderEnter(action);

    RenderAction* a = dynamic_cast<RenderAction*>(action);

    Viewarea*   pArea = a->getViewarea  ();
    Camera*     pCam  = a->getCamera    ();
    Background* pBack = a->getBackground();

    if (pArea == NULL)
        return Action::Continue;

    Int32 iVPWidth  = a->getActivePartition()->getViewportWidth ();
    Int32 iVPHeight = a->getActivePartition()->getViewportHeight();

    SSAOStageDataUnrecPtr pData = a->getData<SSAOStageData *>(_iDataSlotId);
    if (pData == NULL)
    {
        this->initData(a, iVPWidth, iVPHeight);
#ifdef OSG_DEBUG_SSAO_STAGE
        pData = a->getData<SSAOStageData *>(_iDataSlotId);
        std::string dump_str = dump_stage(pData);
        ::OutputDebugString(dump_str.c_str());
        FDEBUG((dump_str.c_str()));
#endif
    }
    else
    {
#if 0
        // only testing: force update
        SSAOStageData* pStageData = pData;
        _mapUpdate            [pStageData] = true;
        _mapUpdateOffsetKernel[pStageData] = true;
        _mapUpdateRotateKernel[pStageData] = true;
#endif

        this->updateData(a, iVPWidth, iVPHeight);
    }

    pData = a->getData<SSAOStageData *>(_iDataSlotId);

    //
    // The duty of the SSAO stage is to render the scene's depth and
    // normals into textures and the perform the SSAO algorithm in a
    // post process render task.
    //
    // In order to achieve this we must setup some partition groups
    // that are responsible for some specific task of the rendering.
    // The following render partitions are setup:
    //      1. Scene RenderPartition:
    //          This partition renders the scene normals into the normal
    //          texture and the depth into a depth texture.
    //      2. SSAO Postprocessing RenderPartition:
    //          This render partition performs all the actual work wrsp. to
    //          SSAO and blurring.
    //

    //a->disableDefaultPartition();

    this->beginPartitionGroup(a);
    {
        //
        // Render scene normals and depth values into textures
        //
        this->pushPartition(a,  RenderPartition::CopyNothing
                            //| RenderPartition::CopyStateOverride
                            //| RenderPartition::CopyViewing
                            //| RenderPartition::CopyProjection
                            //| RenderPartition::CopyVisibility
                            //| RenderPartition::CopyTarget
                            //| RenderPartition::CopyWindow
                            //| RenderPartition::CopyViewportSize
                            //| RenderPartition::CopyFrustum
                            //| RenderPartition::CopyNearFar
                              | RenderPartition::CopyVPCamera
                              | RenderPartition::CopyMatrix
                            //| RenderPartition::CopyAll
                            );
        {
            RenderPartition*   pPart     = a    ->getActivePartition();
            FrameBufferObject* pTarget   = pData->getScenePassRenderTarget();
            ChunkMaterial*     pMaterial = pData->getScenePassMaterial();

            setRenderTarget(pTarget);

            pPart->setRenderTarget(pTarget);
            pPart->setWindow(a->getWindow());

            pPart->calcViewportDimension(
                        pArea->getLeft    (), 
                        pArea->getBottom  (), 
                        pArea->getRight   (), 
                        pArea->getTop     (), 
 
                        pTarget->getWidth (), 
                        pTarget->getHeight());

            if (pCam != NULL)
            {
                Matrix m, t;
                    
                pCam->getProjection           (m, pPart->getViewportWidth(), pPart->getViewportHeight());
                pCam->getProjectionTranslation(t, pPart->getViewportWidth(), pPart->getViewportHeight());
                pPart->setupProjection        (m, t);
                    
                pCam->getViewing   (m, pPart->getViewportWidth(), pPart->getViewportHeight());
                pPart->setupViewing(m);
                    
                pPart->setNear(pCam->getNear());
                pPart->setFar (pCam->getFar ());
                    
                pPart->calcFrustum();
            }
                
            pPart->setBackground(pBack);

            a->overrideMaterial(pMaterial, a->getActNode());
            pPart->deactivateOverride();
            
            this->recurseFromThis(a);
            a->useNodeList(false);

            pPart->activateOverride();
            a->overrideMaterial(NULL, a->getActNode());

        }
        this->popPartition(a);

        //a->getActivePartition()->disable();

        //
        // The SSAO post processing task
        //
        this->pushPartition(a, (RenderPartition::CopyWindow
                              | RenderPartition::CopyViewportSize
                              | RenderPartition::CopyTarget
                              //| RenderPartition::CopyAll
                              ),
                             RenderPartition::SimpleCallback);
        {
            RenderPartition* pPart = a->getActivePartition();

            Matrix m, t;

            m.setIdentity();
            t.setIdentity();
                
            pPart->setupProjection(m, t);

            RenderPartition::SimpleDrawCallback f;

            f = boost::bind(&SSAOStage::postProcess, this, _1);

            pPart->dropFunctor(f);
        }
        this->popPartition(a);
    }
    this->endPartitionGroup(a);

    a->pushState();

    addOverride(pData, a);

    Thread::getCurrentChangeList()->commitChanges();

    this->recurseFromThis(a);
    a->useNodeList(false);

    a->popState();

#ifdef OSG_DEBUG_SSAO_STAGE
    static int cnt = 0;
    cnt++;
    if (cnt == 5)
    {
        //cnt = 0;

        dump_image("d:/dump_normals.tif",   pData->getScenePassRenderTarget()->getColorAttachments(0));

        bool calcPosFromDepth = getCalcPosFromDepth();

        if (!calcPosFromDepth)
        {
            dump_image("d:/dump_positions.tif", pData->getScenePassRenderTarget()->getColorAttachments(1));
        }

        dump_image("d:/dump_depth.pnm",     pData->getScenePassRenderTarget()->getDepthAttachment ( ));
        //dump_image("d:/dump_ssao.tif",      pData->getSSAOPassRenderTarget ()->getColorAttachments(0));
        dump_image("d:/dump_ssao.pnm",      pData->getSSAOPassRenderTarget ()->getColorAttachments(0));
        //dump_image("d:/dump_blur.pnm",    pData->getBlurPassRenderTarget ()->getColorAttachments(0));
    }
#endif

    return Action::Skip;
}

Action::ResultE SSAOStage::renderLeave(Action *action)
{
    if (getActivate() == false)
        return Group::renderLeave(action);

    return Action::Skip;
}

void SSAOStage::addOverride(
    SSAOStageData* pData,
    RenderAction* a)
{
    Int32 iTexUnit = getAmbientOcclusionTexUnit();

    TextureObjChunk* aoTexObjChunk = pData->getBlurTexObjChunk();
    a->addOverride(aoTexObjChunk->getClassId() + iTexUnit, aoTexObjChunk);
}

/*------------------------------ Data -------------------------------------*/

void SSAOStage::initData(RenderAction* pAction,
                         Int32         iVPWidth,
                         Int32         iVPHeight)
{
    SSAOStageDataUnrecPtr pData = pAction->getData<SSAOStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = setupStageData(pAction, iVPWidth, iVPHeight);

        this->setData(pData, _iDataSlotId, pAction);
    }
}

void SSAOStage::updateData(RenderAction* pAction,
                           Int32         iVPWidth,
                           Int32         iVPHeight)
{
    SSAOStageDataUnrecPtr pData = pAction->getData<SSAOStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        initData(pAction, iVPWidth, iVPHeight);

        pData = pAction->getData<SSAOStageData *>(_iDataSlotId);
    }
    else
    {
        updateStageData(pData, pAction, iVPWidth, iVPHeight);
    }
}

/*---------------------------- StageData ----------------------------------*/

SSAOStageDataTransitPtr SSAOStage::setupStageData(
    RenderAction* pAction,
    Int32         iPixelWidth,
    Int32         iPixelHeight)
{
    SSAOStageDataUnrecPtr stageData = SSAOStageData::createLocal();

    if(stageData == NULL)
        return SSAOStageDataTransitPtr(NULL);

    _mapUpdate            [stageData] = true;
    _mapUpdateOffsetKernel[stageData] = true;
    _mapUpdateRotateKernel[stageData] = true;

    stageData->setWidth (iPixelWidth );
    stageData->setHeight(iPixelHeight);

    Matrix matProjection;
    pAction->getCamera()->getProjection(matProjection, iPixelWidth, iPixelHeight);
    stageData->setProjection(matProjection);

    OSG::Thread::setCurrentLocalFlags();

    setupSharedData     (stageData);
    setupRenderTargets  (stageData, iPixelWidth, iPixelHeight);
    setupMaterials      (stageData);

    Thread::getCurrentChangeList()->commitChanges();

    return SSAOStageDataTransitPtr(stageData);
}

void SSAOStage::updateStageData(
    SSAOStageData* pData,
    RenderAction*  pAction,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    bool resize = false;

    if (iPixelWidth != pData->getWidth() || iPixelHeight != pData->getHeight())
        resize = true;

    if (   !_mapUpdate[pData] 
        && !_mapUpdateOffsetKernel[pData] 
        && !_mapUpdateRotateKernel[pData] 
        && !resize)
        return;

    pData->setWidth (iPixelWidth );
    pData->setHeight(iPixelHeight);

    Matrix matProjection;
    pAction->getCamera()->getProjection(matProjection, iPixelWidth, iPixelHeight);
    pData->setProjection(matProjection);

    OSG::Thread::setCurrentLocalFlags();

    updateSharedData(pData);

    if (resize)
        updateRenderTargets(pData, iPixelWidth, iPixelHeight);

    updateMaterials    (pData);

    _mapUpdate            [pData] = false;
    _mapUpdateOffsetKernel[pData] = false;
    _mapUpdateRotateKernel[pData] = false;

    Thread::getCurrentChangeList()->commitChanges();
}

/*------------------------ StageData Details ------------------------------*/

void SSAOStage::setupSharedData(SSAOStageData* pData)
{
    MaterialChunkUnrecPtr matChunk = MaterialChunk::createLocal();
    matChunk->setLit(false);
    pData->setSharedMaterialChunk(matChunk);
}

void SSAOStage::updateSharedData(SSAOStageData* pData)
{
}

void SSAOStage::setupRenderTargets(
    SSAOStageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    setupScenePassRenderTarget  (pData, iPixelWidth, iPixelHeight);
    setupSSAOPassRenderTarget   (pData, iPixelWidth, iPixelHeight);
    setupBlurPassRenderTarget   (pData, iPixelWidth, iPixelHeight);
}

void SSAOStage::updateRenderTargets(
    SSAOStageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    updateScenePassRenderTarget (pData, iPixelWidth, iPixelHeight);
    updateSSAOPassRenderTarget  (pData, iPixelWidth, iPixelHeight);
    updateBlurPassRenderTarget  (pData, iPixelWidth, iPixelHeight);
}

void SSAOStage::setupMaterials(SSAOStageData* pData)
{
    setupScenePassMaterial      (pData);
    setupSSAOPassMaterial       (pData);
    setupBlurPassMaterial       (pData);
}

void SSAOStage::updateMaterials(SSAOStageData* pData)
{
    updateScenePassMaterial     (pData);
    updateSSAOPassMaterial      (pData);
    updateBlurPassMaterial      (pData);
}

/*--------------------- StageData: RenderTarget ---------------------------*/

void SSAOStage::setupScenePassRenderTarget(
    SSAOStageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    bool calcPosFromDepth = getCalcPosFromDepth();

    FrameBufferObjectUnrecPtr pSceneFBO = FrameBufferObject::createLocal();
    pSceneFBO->setSize(iPixelWidth, iPixelHeight);

#ifdef OSG_DEBUG_SSAO_STAGE
    pSceneFBO->setPostProcessOnDeactivate(true);
#endif

    ImageUnrecPtr pNormalImg = Image ::createLocal();
    pNormalImg->set(Image::OSG_RGB_PF, iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, Image::OSG_FLOAT32_IMAGEDATA, false);

    TextureObjChunkUnrecPtr pNormalTexObjChunk = TextureObjChunk::createLocal();

    pNormalTexObjChunk->setImage         (pNormalImg);
    pNormalTexObjChunk->setMinFilter     (GL_NEAREST);
    pNormalTexObjChunk->setMagFilter     (GL_NEAREST);
    pNormalTexObjChunk->setWrapS         (GL_CLAMP_TO_EDGE);
    pNormalTexObjChunk->setWrapT         (GL_CLAMP_TO_EDGE);
    pNormalTexObjChunk->setInternalFormat(GL_RGB16F);

    TextureBufferUnrecPtr pNormalTexBuffer   = TextureBuffer::createLocal();
    pNormalTexBuffer->setTexture(pNormalTexObjChunk);

    pSceneFBO->setColorAttachment(pNormalTexBuffer,   0);
    pSceneFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

#ifdef OSG_DEBUG_SSAO_STAGE
    pNormalTexBuffer  ->setReadBack(true);
#endif

    if (!calcPosFromDepth)
    {
        ImageUnrecPtr pPositionImg = Image ::createLocal();
        pPositionImg->set(Image::OSG_RGB_PF, iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, Image::OSG_FLOAT32_IMAGEDATA, false);

        TextureObjChunkUnrecPtr pPositionTexObjChunk = TextureObjChunk::createLocal();

        pPositionTexObjChunk->setImage         (pPositionImg);
        pPositionTexObjChunk->setMinFilter     (GL_NEAREST);
        pPositionTexObjChunk->setMagFilter     (GL_NEAREST);
        pPositionTexObjChunk->setWrapS         (GL_CLAMP_TO_EDGE);
        pPositionTexObjChunk->setWrapT         (GL_CLAMP_TO_EDGE);
        pPositionTexObjChunk->setInternalFormat(GL_RGB16F);
        
        TextureBufferUnrecPtr pPositionTexBuffer = TextureBuffer::createLocal();    
        pPositionTexBuffer->setTexture(pPositionTexObjChunk);

        pSceneFBO->setColorAttachment(pPositionTexBuffer, 1);
        pSceneFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT1);

#ifdef OSG_DEBUG_SSAO_STAGE
        pPositionTexBuffer->setReadBack(true);
#endif
    }


    ImageUnrecPtr pDepthImg = Image ::createLocal();
    pDepthImg->set(Image::OSG_DEPTH_PF, iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, Image::OSG_FLOAT32_IMAGEDATA, false);

    TextureObjChunkUnrecPtr pDepthTexObjChunk = TextureObjChunk::createLocal();
    pDepthTexObjChunk->setImage         (pDepthImg);
    pDepthTexObjChunk->setMinFilter     (GL_NEAREST);
    pDepthTexObjChunk->setMagFilter     (GL_NEAREST);
    pDepthTexObjChunk->setWrapS         (GL_CLAMP_TO_EDGE);
    pDepthTexObjChunk->setWrapT         (GL_CLAMP_TO_EDGE);
    pDepthTexObjChunk->setInternalFormat(GL_DEPTH_COMPONENT32);

    TextureBufferUnrecPtr pDepthTexBuffer    = TextureBuffer::createLocal();
    pDepthTexBuffer ->setTexture(pDepthTexObjChunk);

    pSceneFBO->setDepthAttachment(pDepthTexBuffer);

#ifdef OSG_DEBUG_SSAO_STAGE
    pDepthTexBuffer   ->setReadBack(true);
#endif

    pData->setScenePassRenderTarget(pSceneFBO);
}

void SSAOStage::setupSSAOPassRenderTarget(
    SSAOStageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObjectUnrecPtr pSSAOFBO = FrameBufferObject::createLocal();
    pSSAOFBO->setSize(iPixelWidth, iPixelHeight);

    ImageUnrecPtr pSSAOImg = Image ::createLocal();
    pSSAOImg->set(Image::OSG_R_PF, iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, Image::OSG_FLOAT32_IMAGEDATA, false);

    TextureObjChunkUnrecPtr pSSAOTexObjChunk = TextureObjChunk::createLocal();
    pSSAOTexObjChunk->setImage         (pSSAOImg);
    pSSAOTexObjChunk->setMinFilter     (GL_LINEAR);
    pSSAOTexObjChunk->setMagFilter     (GL_LINEAR);
    pSSAOTexObjChunk->setWrapS         (GL_CLAMP_TO_EDGE);
    pSSAOTexObjChunk->setWrapT         (GL_CLAMP_TO_EDGE);
    pSSAOTexObjChunk->setInternalFormat(GL_R32F);

    TextureBufferUnrecPtr pSSAOTexBuffer = TextureBuffer::createLocal();
    pSSAOTexBuffer->setTexture(pSSAOTexObjChunk);

    pSSAOFBO->setColorAttachment(pSSAOTexBuffer, 0);
    pSSAOFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

#ifdef OSG_DEBUG_SSAO_STAGE
    pSSAOFBO->setPostProcessOnDeactivate(true);
    pSSAOTexBuffer->setReadBack(true);
#endif

    pData->setSSAOPassRenderTarget(pSSAOFBO);
}

void SSAOStage::setupBlurPassRenderTarget(
    SSAOStageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObjectUnrecPtr pBlurFBO = FrameBufferObject::createLocal();
    pBlurFBO->setSize(iPixelWidth, iPixelHeight);

    ImageUnrecPtr pBlurImg = Image ::createLocal();
    pBlurImg->set(Image::OSG_R_PF, iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, Image::OSG_FLOAT32_IMAGEDATA, false);

    TextureObjChunkUnrecPtr pBlurTexObjChunk = TextureObjChunk::createLocal();
    pBlurTexObjChunk->setImage         (pBlurImg); 
    pBlurTexObjChunk->setMinFilter     (GL_LINEAR);
    pBlurTexObjChunk->setMagFilter     (GL_LINEAR);
    pBlurTexObjChunk->setWrapS         (GL_CLAMP_TO_EDGE);
    pBlurTexObjChunk->setWrapT         (GL_CLAMP_TO_EDGE);
    pBlurTexObjChunk->setInternalFormat(GL_R32F);

    pBlurTexObjChunk->setTarget        (GL_TEXTURE_RECTANGLE);
    pBlurTexObjChunk->setScale         (false);

    TextureBufferUnrecPtr pBlurTexBuffer = TextureBuffer::createLocal();
    pBlurTexBuffer->setTexture(pBlurTexObjChunk);

#ifdef OSG_DEBUG_SSAO_STAGE
    pBlurFBO->setPostProcessOnDeactivate(true);
    
    pBlurTexBuffer->setReadBack(true);
#endif

    pBlurFBO->setColorAttachment(pBlurTexBuffer, 0);
    pBlurFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setBlurPassRenderTarget(pBlurFBO);
}

void SSAOStage::updateScenePassRenderTarget(
    SSAOStageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getScenePassRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

void SSAOStage::updateSSAOPassRenderTarget(
    SSAOStageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getSSAOPassRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

void SSAOStage::updateBlurPassRenderTarget(
    SSAOStageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getBlurPassRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

/*----------------------- StageData: Materials ----------------------------*/

void SSAOStage::setupScenePassMaterial(SSAOStageData* pData)
{
    bool calcPosFromDepth = getCalcPosFromDepth();

    SimpleSHLChunkUnrecPtr shaderChunk = genScenePassShader(calcPosFromDepth);

    DepthChunkUnrecPtr     depthChunk = DepthChunk::createLocal();
    depthChunk->setEnable(true);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());
    chunkMat->addChunk(shaderChunk);
    chunkMat->addChunk(depthChunk);

    pData->setScenePassShader(shaderChunk);
    pData->setScenePassMaterial(chunkMat);
}

void SSAOStage::setupSSAOPassMaterial(SSAOStageData* pData)
{
    updateOffsetKernelState(pData);
    updateRotateKernelState(pData);

    bool calcPosFromDepth = getCalcPosFromDepth();

    SimpleSHLChunkUnrecPtr shaderChunk = genSSAOPassShader(calcPosFromDepth);

    const Matrix& matProjection = pData->getProjection();
    shaderChunk->addUniformVariable("uProjectionMatrix", matProjection);

    if (calcPosFromDepth)
    {
        bool isPerspective = false;

        // Attention: OpenSG stores internally the transposed of the matrix as 4 row vectors
        //            => to get m32 we have to check matProjection[2][3]
        if (matProjection[2][3] == -1.f)
            isPerspective = true;

        shaderChunk->addUniformVariable("uIsPerspective",    isPerspective);
    }

    Real32 kernelSize(getRotateKernelSize());
    Vec2f rotateScale(pData->getWidth() / kernelSize, pData->getHeight() / kernelSize);

    shaderChunk->addUniformVariable("uRotateScale", rotateScale);
    shaderChunk->addUniformVariable("uRadius",      getRadius());
    shaderChunk->addUniformVariable("uBias",        getBias());

    shaderChunk->addUniformVariable("NormalTex",   0);

    if (!calcPosFromDepth)
    {
        shaderChunk->addUniformVariable("PositionTex", 1);
    }

    shaderChunk->addUniformVariable("DepthTex",    2);
    shaderChunk->addUniformVariable("RotateTex",   3);
    shaderChunk->addUniformVariable("OffsetKernelBlock", 0);


    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());
    chunkMat->addChunk(pData->getNormalTexObjChunk  (), 0);
    chunkMat->addChunk(       getOffsetKernelChunk  (), 0);

    if (!calcPosFromDepth)
    {
        chunkMat->addChunk(pData->getPositionTexObjChunk(), 1);
    }

    chunkMat->addChunk(pData->getDepthTexObjChunk   (), 2);
    chunkMat->addChunk(       getRotateKernelChunk  (), 3);

    chunkMat->addChunk(shaderChunk);

    pData->setSSAOPassShader(shaderChunk);
    pData->setSSAOPassMaterial(chunkMat);
}

void SSAOStage::setupBlurPassMaterial(SSAOStageData* pData)
{
    SimpleSHLChunkUnrecPtr shaderChunk = genBlurPassShader();
    shaderChunk->addUniformVariable("SSAOTex", 0);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());
    chunkMat->addChunk(pData->getSSAOTexObjChunk(), 0);
    chunkMat->addChunk(shaderChunk);

    pData->setBlurPassShader(shaderChunk);
    pData->setBlurPassMaterial(chunkMat);
}

void SSAOStage::updateScenePassMaterial(SSAOStageData* pData)
{
    SimpleSHLChunk* shaderChunk = pData->getScenePassShader();
}

void SSAOStage::updateSSAOPassMaterial(SSAOStageData* pData)
{
    updateOffsetKernelState(pData);
    updateRotateKernelState(pData);

    bool calcPosFromDepth = getCalcPosFromDepth();

    SimpleSHLChunk* shaderChunk = pData->getSSAOPassShader();

    const Matrix& matProjection = pData->getProjection();
    shaderChunk->updateUniformVariable("uProjectionMatrix", matProjection);

    if (calcPosFromDepth)
    {
        bool isPerspective = false;

        // Attention: OpenSG stores internally the transposed of the matrix as 4 row vectors
        //            => to get m32 we have to check matProjection[2][3]
        if (matProjection[2][3] == -1.f)
            isPerspective = true;

        shaderChunk->updateUniformVariable("uIsPerspective",    isPerspective);
    }

    Real32 kernelSize(getRotateKernelSize());
    Vec2f rotateScale(pData->getWidth() / kernelSize, pData->getHeight() / kernelSize);

    shaderChunk->updateUniformVariable("uRotateScale", rotateScale);
    shaderChunk->updateUniformVariable("uRadius",      getRadius());
    shaderChunk->updateUniformVariable("uBias",        getBias());
}

void SSAOStage::updateBlurPassMaterial(SSAOStageData* pData)
{
    SimpleSHLChunk* shaderChunk = pData->getBlurPassShader();
}

std::size_t SSAOStage::calcOffsetKernelBufferSize(Int32 kernelSize) const
{
    // layout (std140) uniform OffsetKernelBlock
    // {
    //     int   size;
    //     vec3  kernel[ << getOffsetKernelSize() << ];
    // } offset;

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    //
    // Box kernel sizes
    //
    ao = alignOffset( 4, bo); bo = ao + sizeof( Int32); // Int32   offsetKernelSize

    //
    // Filter Distribution
    //
    for (Int32 idx = 0; idx < kernelSize; ++idx)
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);  // vec3 kernel[]
    }
    ao = alignOffset(16, bo); bo = ao;                      // padding

    return ao;
}

std::vector<UInt8> SSAOStage::createOffsetKernelBuffer() const
{
    Int32 kernelSize = getOffsetKernelSize();

         if (kernelSize >= 256) kernelSize = 256;
    else if (kernelSize >= 128) kernelSize = 128;
    else if (kernelSize >= 100) kernelSize = 100;
    else if (kernelSize >=  64) kernelSize =  64;
    else if (kernelSize >=  32) kernelSize =  32;
    else if (kernelSize >=  16) kernelSize =  16;
    else if (kernelSize >=   9) kernelSize =   9;
    else                        kernelSize =   9;

    std::size_t size = calcOffsetKernelBufferSize(kernelSize);

    std::vector<UInt8> buffer(size);

    //
    // Generate the sample kernel. Requirements:
    //
    //  - sample positions fall within the unit hemisphere
    //  - sample positions are more densely clustered towards the origin.
    //
    // See http://john-chapman-graphics.blogspot.de/2013/01/ssao-tutorial.html
    //

    std::vector<Vec3f> offsetKernel;

    //
    // Alternative 1: Use a random number kernel in accordance to the Chapman's article
    //
    for (Int32 i = 0; i < kernelSize; ++i)
    {
        //
        // Construt a point in the upper hemisphere [-1,1]^2 x [0,1]
        //
        OSG::Real32 x = OSG::RandomPoolManager::the()->getRandomReal32(-1.f, 1.f);
        OSG::Real32 y = OSG::RandomPoolManager::the()->getRandomReal32(-1.f, 1.f);
        OSG::Real32 z = OSG::RandomPoolManager::the()->getRandomReal32( 0.f, 1.f);

        Vec3f sample(x, y, z);

        //
        // Project the point onto the unit hemisphere surface
        //
        sample.normalize();

        //
        // Evenly distribute the points in the hemisphere
        //
        sample *= OSG::RandomPoolManager::the()->getRandomReal32( 0.f, 1.f);

        //
        // and distribute them in such a way that the density of points fall off
        // by the squared distance from the hemisphere center.
        //
        Real32 scale = static_cast<Real32>(i) / static_cast<Real32>(kernelSize);

        scale = lerp(0.1f, 1.f, scale * scale);

        sample *= scale;

        offsetKernel.push_back(sample);
    }
/*
    //
    // Alternative 2: Use Poisson distributions
    //  
    std::vector<Vec3f>  hemisphere_surface = Distribution::getPoissonHemisphereSurface(kernelSize);

    for (Int32 i = 0; i < kernelSize; ++i)
    {
        Vec3f sample = hemisphere_surface[i];

        //
        // Evenly distribute the points in the hemisphere
        //
        sample *= OSG::RandomPoolManager::the()->getRandomReal32( 0.f, 1.f);

        //
        // and distribute them in such a way that the density of points fall off
        // by the squared distance from the hemisphere center.
        //
        Real32 scale = static_cast<Real32>(i) / static_cast<Real32>(kernelSize);

        scale = lerp(0.1f, 1.f, scale * scale);

        sample *= scale;

        offsetKernel.push_back(sample);
    }
*/
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = kernelSize; bo = ao + sizeof( Int32);

    for (Int32 idx = 0; idx < kernelSize; ++idx)
    {
        const Vec3f& value = offsetKernel[idx];
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &value[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);
    }
    ao = alignOffset(16, bo); bo = ao;                  // padding

    return buffer;
}

void SSAOStage::updateOffsetKernelState(SSAOStageData* pData)
{
    if (_mapUpdateOffsetKernel[pData])
    {
        std::vector<UInt8> buffer = createOffsetKernelBuffer();

        UniformBufferObjStd140Chunk* offsetKernelChunk = getOffsetKernelChunk();
        if (offsetKernelChunk == NULL)
        {
            UniformBufferObjStd140ChunkUnrecPtr chunk = UniformBufferObjStd140Chunk::createLocal();
            setOffsetKernelChunk(chunk);

            offsetKernelChunk = getOffsetKernelChunk();
        }

        offsetKernelChunk->editMFBuffer()->setValues(buffer);
    }
}

std::vector<Vec3f> SSAOStage::createRotateKernelBuffer(Int32 kernelSize) const
{
    Int32 size = kernelSize * kernelSize;
    
    std::vector<Vec3f> buffer;

    //std::vector<Vec2f> rect = Distribution::getPoissonQuad(size);

    for (Int32 i = 0; i < size; ++i)
    {
        OSG::Real32 x = OSG::RandomPoolManager::the()->getRandomReal32(-1.f, 1.f);
        OSG::Real32 y = OSG::RandomPoolManager::the()->getRandomReal32(-1.f, 1.f);

        //OSG::Real32 x = rect[i].x();
        //OSG::Real32 y = rect[i].y();

        Vec3f noise(x, y, 0.f); // rotate around z-axis (in tangent space)
        buffer.push_back(noise);
    }

    return buffer;
}

void SSAOStage::updateRotateKernelState(SSAOStageData* pData)
{
    if (_mapUpdateRotateKernel[pData])
    {
        Int32 kernelSize = getRotateKernelSize();

        std::vector<Vec3f> buffer = createRotateKernelBuffer(kernelSize);

        TextureObjChunk* rotTexChunk = getRotateKernelChunk();
        if (rotTexChunk == NULL)
        {
            TextureObjChunkUnrecPtr chunk = TextureObjChunk::createLocal();

            setRotateKernelChunk(chunk);

            rotTexChunk = getRotateKernelChunk();

            rotTexChunk->setMinFilter     (GL_NEAREST);
            rotTexChunk->setMagFilter     (GL_NEAREST);
            rotTexChunk->setWrapS         (GL_REPEAT);
            rotTexChunk->setWrapT         (GL_REPEAT);
            rotTexChunk->setInternalFormat(GL_RGB32F);
        }
        
        Image* image = rotTexChunk->getImage();
        if (image == NULL)
        {
            ImageUnrecPtr img = Image::createLocal();
            rotTexChunk->setImage(img);
            
            image = rotTexChunk->getImage();

            image->set(Image::OSG_RGB_PF, kernelSize, kernelSize, 1, 1, 1, 0.0, 0, Image::OSG_FLOAT32_IMAGEDATA, true);

            rotTexChunk->setImage(image);
        }

        const UInt8* data = reinterpret_cast<const UInt8*>(&buffer[0][0]);

        image->setData(data);
    }
}

/*---------------------------- postProcess --------------------------------*/

void SSAOStage::postProcess(DrawEnv *pEnv)
{
    UInt32  uiActiveFBO = pEnv->getActiveFBO();
    Window* win         = pEnv->getWindow();

    SSAOStageData* pData = pEnv->getData<SSAOStageData*>(_iDataSlotId);
    if(pData == NULL)
    {
        return;
    }

    if(win->hasExtOrVersion(_uiFramebufferObjectExt, 0x0300, 0x0200) == false)
    {
        FNOTICE(("Framebuffer objects not supported on Window %p!\n", 
                 static_cast<void *>(win)));
        return;        
    }

    OSGGETGLFUNCBYID_GL3( glDrawBuffers,
                          osgGlDrawBuffers,
                         _uiFuncDrawBuffers,
                          win);

    glColor3f(1.f, 1.f, 1.f);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();


    Real32 proj_matrix[16], model_matrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, proj_matrix);
    glGetFloatv(GL_MODELVIEW_MATRIX, model_matrix);

    ssaoPass(pEnv, pData);
    blurPass(pEnv, pData);

    pEnv->deactivateState();

    glPopMatrix();
}

void SSAOStage::ssaoPass(DrawEnv* pEnv, SSAOStageData* pData)
{
    FrameBufferObject* pSSAOFBO = pData->getSSAOPassRenderTarget();
    ChunkMaterial*     pSSAOMat = pData->getSSAOPassMaterial();

    pSSAOFBO->activate(pEnv);

    State* pSSAOState = pSSAOMat->getState();

    pEnv->activateState(pSSAOState, NULL);
    
    this->renderQuad();

    pSSAOFBO->deactivate(pEnv);
}

void SSAOStage::blurPass(DrawEnv* pEnv, SSAOStageData* pData)
{
    FrameBufferObject* pBlurFBO = pData->getBlurPassRenderTarget();
    ChunkMaterial*     pBlurMat = pData->getBlurPassMaterial();

    pBlurFBO->activate(pEnv);

    State* pBlurState = pBlurMat->getState();

    pEnv->activateState(pBlurState, NULL);
    
    this->renderQuad();

    pBlurFBO->deactivate(pEnv);
}

/*------------------------------- Shader ----------------------------------*/

SimpleSHLChunkTransitPtr SSAOStage::genScenePassShader(bool calcPosFromDepth)
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genScenePassVertexShader  (vert, calcPosFromDepth);
    genScenePassFragmentShader(frag, calcPosFromDepth);

    simpleSHLChunk->setVertexProgram  (vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

#ifdef OSG_OGL_COREONLY
    simpleSHLChunk->addOSGVariable("OSGNormalMatrix");

    if (!calcPosFromDepth)
    {
        simpleSHLChunk->addOSGVariable("OSGModelViewMatrix");
    }

    simpleSHLChunk->addOSGVariable("OSGModelViewProjectionMatrix");
#else
    simpleSHLChunk->addOSGVariable("OSGProjectionMatrix");
    simpleSHLChunk->addOSGVariable("OSGModelViewMatrix");
#endif

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr SSAOStage::genSSAOPassShader(bool calcPosFromDepth)
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genSSAOPassVertexShader  (vert, calcPosFromDepth);
    genSSAOPassFragmentShader(frag, calcPosFromDepth);

    simpleSHLChunk->setVertexProgram  (vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr SSAOStage::genBlurPassShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genBlurPassVertexShader  (vert);
    genBlurPassFragmentShader(frag);

    simpleSHLChunk->setVertexProgram  (vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

void SSAOStage::genScenePassVertexShader(std::stringstream& ost, bool calcPosFromDepth)
{
    using namespace std;

    if (calcPosFromDepth)
    {
        ost
        << endl << "#version 330 core"
        << endl << ""
        << endl << "layout (location = 0) in vec4 aVertex;"
        << endl << "layout (location = 2) in vec3 aNormal;"
        << endl << ""
        << endl << "out vec3 vNormalES;"
        << endl << ""
#ifdef OSG_OGL_COREONLY
        << endl << "uniform mat4  OSGNormalMatrix;"
        << endl << "uniform mat4  OSGModelViewProjectionMatrix;"
#else
        << endl << "uniform mat4  OSGModelViewMatrix;"
        << endl << "uniform mat4  OSGProjectionMatrix;"
#endif
        << endl << ""
        << endl << "void main()"
        << endl << "{"
#ifdef OSG_OGL_COREONLY
        << endl << "    vNormalES   = mat3x3(OSGNormalMatrix) * aNormal;"
        << endl << "    gl_Position = OSGModelViewProjectionMatrix * aVertex;"
#else
        << endl << "    vNormalES   = transpose(inverse(mat3x3(OSGModelViewMatrix))) * aNormal;"
        << endl << "    gl_Position = OSGProjectionMatrix * OSGModelViewMatrix * aVertex;"
#endif
        << endl << "}"
        ;
    }
    else
    {
        ost
        << endl << "#version 330 core"
        << endl << ""
        << endl << "layout (location = 0) in vec4 aVertex;"
        << endl << "layout (location = 2) in vec3 aNormal;"
        << endl << ""
        << endl << "out vec3 vNormalES;"
        << endl << "out vec3 vPositionES;"
        << endl << ""
#ifdef OSG_OGL_COREONLY
        << endl << "uniform mat4  OSGNormalMatrix;"
        << endl << "uniform mat4  OSGModelViewMatrix;"
        << endl << "uniform mat4  OSGModelViewProjectionMatrix;"
#else
        << endl << "uniform mat4  OSGModelViewMatrix;"
        << endl << "uniform mat4  OSGProjectionMatrix;"
#endif
        << endl << ""
        << endl << "void main()"
        << endl << "{"
#ifdef OSG_OGL_COREONLY
        << endl << "    vNormalES   = mat3x3(OSGNormalMatrix) * aNormal;"
        << endl << "    vec4 fragPosES = OSGModelViewMatrix * aVertex;"
        << endl << "    vPositionES = fragPosES.xyz;"
        << endl << "    gl_Position = OSGModelViewProjectionMatrix * aVertex;"
#else
        << endl << "    vNormalES   = transpose(inverse(mat3x3(OSGModelViewMatrix))) * aNormal;"
        << endl << "    vec4 fragPosES = OSGModelViewMatrix * aVertex;"
        << endl << "    vPositionES = fragPosES.xyz;"
        << endl << "    gl_Position = OSGProjectionMatrix * fragPosES;"
#endif
        << endl << "}"
        ;
    }
}

void SSAOStage::genScenePassFragmentShader(std::stringstream& ost, bool calcPosFromDepth)
{
    using namespace std;

    if (calcPosFromDepth)
    {
        ost
        << endl << "#version 330 core"
        << endl << ""
        << endl << "in vec3 vNormalES;"
        << endl << ""
        << endl << "out vec3 outNormal;"
        << endl << ""
        << endl << "void main()"
        << endl << "{"
        << endl << "    vec3 normal = normalize(vNormalES);"
        << endl << "    outNormal   = gl_FrontFacing ? normal : -normal;"
        //<< endl << ""
        //<< endl << "    gl_FragDepth = gl_FragCoord.z;"
        << endl << "}"
        << endl << ""
        ;
    }
    else
    {
        ost
        << endl << "#version 330 core"
        << endl << ""
        << endl << "in vec3 vNormalES;"
        << endl << "in vec3 vPositionES;"
        << endl << ""
        << endl << "out vec3 outNormal;"
        << endl << "out vec3 outPosition;"
        << endl << ""
        << endl << "void main()"
        << endl << "{"
        << endl << "    vec3 normal = normalize(vNormalES);"
        << endl << "    outNormal   = gl_FrontFacing ? normal : -normal;"
        << endl << "    outPosition = vPositionES;"
        << endl << "}"
        << endl << ""
        ;
    }
}

void SSAOStage::genSSAOPassVertexShader(std::stringstream& ost, bool calcPosFromDepth)
{
    using namespace std;

    if (calcPosFromDepth)
    {
        ost
        << endl << "#version 330 compatibility"
        << endl << ""
        << endl << "layout(location = 0) in vec2 aVertex;"
        << endl << ""
        << endl << "uniform mat4 uProjectionMatrix;"
        << endl << "uniform bool uIsPerspective;"
        << endl << ""
        << endl << "out vec2 vTexCoord;"
        << endl << "out vec2 vPositionNDC;"
        << endl << ""
        << endl << "vec2 CalcPerspPosNDC()"
        << endl << "{"
        << endl << "    float P00 = uProjectionMatrix[0][0];"
        << endl << "    float P02 = uProjectionMatrix[2][0];"
        << endl << ""
        << endl << "    float P11 = uProjectionMatrix[1][1];"
        << endl << "    float P12 = uProjectionMatrix[2][1];"
        << endl << ""
        << endl << "    return vec2((aVertex.x + P02) / P00, (aVertex.y + P12) / P11);"
        << endl << "}"
        << endl << ""
        << endl << "vec2 CalcOrthoPosNDC()"
        << endl << "{"
        << endl << "    float P00 = uProjectionMatrix[0][0];"
        << endl << "    float P03 = uProjectionMatrix[3][0];"
        << endl << ""
        << endl << "    float P11 = uProjectionMatrix[1][1];"
        << endl << "    float P13 = uProjectionMatrix[3][1];"
        << endl << ""
        << endl << "    return vec2((aVertex.x - P03) / P00, (aVertex.y - P13) / P11);"
        << endl << "}"
        << endl << ""
        << endl << "void main()"
        << endl << "{"
        << endl << "    vec4 vPos   = vec4(aVertex.x, aVertex.y, 0, 1);"
        << endl << "    vTexCoord   = 0.5 * vPos.xy + 0.5;"
        << endl << "    vPositionNDC = uIsPerspective ? CalcPerspPosNDC() : CalcOrthoPosNDC();"
        << endl << ""
        << endl << "    gl_Position = vPos;"
        << endl << "}"
        << endl << ""
        ;
    }
    else
    {
        ost
        << endl << "#version 330 compatibility"
        << endl << ""
        << endl << "layout(location = 0) in vec2 aVertex;"
        << endl << ""
        << endl << "out vec2 vTexCoord;"
        << endl << ""
        << endl << "void main()"
        << endl << "{"
        << endl << "    vec4 vPos = vec4(aVertex.x, aVertex.y, 0, 1);"
        << endl << "    vTexCoord = 0.5 * vPos.xy + 0.5;"
        << endl << ""
        << endl << "    gl_Position = vPos;"
        << endl << "}"
        << endl << ""
        ;
    }
}

void SSAOStage::genSSAOPassFragmentShader(std::stringstream& ost, bool calcPosFromDepth)
{
    using namespace std;

    if (calcPosFromDepth)
    {
        ost
        << endl << "#version 330 compatibility"
        << endl << ""
        << endl << "uniform sampler2D NormalTex;"
        << endl << "uniform sampler2D DepthTex;"
        << endl << "uniform sampler2D RotateTex;"
        << endl << ""
        << endl << "uniform mat4  uProjectionMatrix;"
        << endl << "uniform bool  uIsPerspective;"
        << endl << "uniform vec2  uRotateScale;"
        << endl << "uniform float uRadius;"
        << endl << "uniform float uBias;"
        << endl << ""
        << endl << "layout (std140) uniform OffsetKernelBlock"
        << endl << "{"
        << endl << "    int   size;"
        << endl << "    vec3  kernel[" << getOffsetKernelSize() << "];"
        << endl << "} offset;"
        << endl << ""
        << endl << "in vec2 vTexCoord;"
        << endl << "in vec2 vViewRay;"
        << endl << ""
        << endl << "in vec2 vPositionNDC;"
        << endl << ""
        << endl << "layout(location = 0) out float FragColor;"
        << endl << ""
        << endl << "float CalcPerspZe(in vec2 uv)"
        << endl << "{"
        << endl << "    float Zd  = texture(DepthTex, uv).x;"
        << endl << "    float Zn  = 2.0 * Zd - 1.0;"
        << endl << ""
        << endl << "    float P22 = uProjectionMatrix[2][2];"
        << endl << "    float P23 = uProjectionMatrix[3][2];"
        << endl << ""
        << endl << "    return -P23 / (Zn + P22);"
        << endl << "}"
        << endl << ""
        << endl << "float CalcOrthoZe(in vec2 uv)"
        << endl << "{"
        << endl << "    float Zd  = texture(DepthTex, uv).x;"
        << endl << "    float Zn  = 2.0 * Zd - 1.0;"
        << endl << ""
        << endl << "    float P22 = uProjectionMatrix[2][2];"
        << endl << "    float P23 = uProjectionMatrix[3][2];"
        << endl << ""
        << endl << "    return (Zn - P23) / P22;"
        << endl << "}"
        << endl << ""
        << endl << "float CalcZe(in vec2 uv)"
        << endl << "{"
        << endl << "    return (uIsPerspective ? CalcPerspZe(uv) : CalcOrthoZe(uv));"
        << endl << "}"
        << endl << ""
        << endl << "vec3 CalcFragPosES(in vec2 uv)"
        << endl << "{"
        << endl << "    float Xe,Ye,Ze;"
        << endl << "    if (uIsPerspective)"
        << endl << "    {"
        << endl << "        Ze = CalcPerspZe(uv);"
        << endl << "        Xe = -vPositionNDC.x * Ze;"
        << endl << "        Ye = -vPositionNDC.y * Ze;"
        << endl << "    }"
        << endl << "    else"
        << endl << "    {"
        << endl << "        Ze = CalcOrthoZe(uv);"
        << endl << "        Xe = -vPositionNDC.x;"
        << endl << "        Ye = -vPositionNDC.y;"
        << endl << "    }"
        << endl << "    return vec3(Xe,Ye,Ze);"
        << endl << "}"
        << endl << ""
        << endl << "void main()"
        << endl << "{"
        << endl << "    vec3 position = CalcFragPosES(vTexCoord);"
        << endl << "    vec3 normal   = texture(NormalTex, vTexCoord).xyz;"
        << endl << "    vec3 rotate   = texture(RotateTex, vTexCoord * uRotateScale).xyz;"
        << endl << ""
        << endl << "    rotate = normalize(rotate);"
        << endl << ""
        << endl << "    vec3 tangent   = normalize(rotate - normal * dot(rotate, normal));"
        << endl << "    vec3 bitangent = cross(normal, tangent);"
        << endl << "    mat3 TBN = mat3(tangent, bitangent, normal);"
        << endl << ""
        << endl << "    int   kernelSize = offset.size;"
        << endl << "    float occlusion  = 0.0;"
        << endl << ""
        << endl << "    for (int i = 0; i < kernelSize; ++i)"
        << endl << "    {"
        << endl << "        vec3 sample = TBN * offset.kernel[i];"
        << endl << "        sample = position + sample * uRadius;"
        << endl << ""
        << endl << "        vec4 p = vec4(sample, 1.0);"
        << endl << "        p = uProjectionMatrix * p;"
        << endl << "        p.xyz /= p.w;"
        << endl << "        p.xyz  = p.xyz * 0.5 + 0.5;"
        << endl << ""
        << endl << "        float depth = CalcZe(p.xy);"
        << endl << ""
        << endl << "        float check = smoothstep(0.0, 1.0, uRadius / abs(position.z - depth));"
        << endl << "        occlusion += (depth >= sample.z + uBias ? 1.0 : 0.0) * check;"
        << endl << "    }"
        << endl << ""
        << endl << "    occlusion = 1.0 - occlusion / kernelSize;"
        << endl << ""
        << endl << "    FragColor = occlusion;"
        << endl << "}"
        ;
    }
    else
    {
        ost
        << endl << "#version 330 compatibility"
        << endl << ""
        << endl << "uniform sampler2D NormalTex;"
        << endl << "uniform sampler2D PositionTex;"
        << endl << "uniform sampler2D DepthTex;"
        << endl << "uniform sampler2D RotateTex;"
        << endl << ""
        << endl << "uniform mat4  uProjectionMatrix;"
        << endl << "uniform vec2  uRotateScale;"
        << endl << "uniform float uRadius;"
        << endl << "uniform float uBias;"
        << endl << ""
        << endl << "layout (std140) uniform OffsetKernelBlock"
        << endl << "{"
        << endl << "    int   size;"
        << endl << "    vec3  kernel[" << getOffsetKernelSize() << "];"
        << endl << "} offset;"
        << endl << ""
        << endl << "in vec2 vTexCoord;"
        << endl << ""
        << endl << "layout(location = 0) out float FragColor;"
        << endl << ""
        << endl << "void main()"
        << endl << "{"
        << endl << "    vec3 position = texture(PositionTex, vTexCoord).xyz;"
        << endl << "    vec3 normal   = texture(NormalTex,   vTexCoord).xyz;"
        << endl << "    vec3 rotate   = texture(RotateTex,   vTexCoord * uRotateScale).xyz;"
        << endl << ""
        << endl << "    rotate = normalize(rotate);"
        << endl << ""
        << endl << "    vec3 tangent   = normalize(rotate - normal * dot(rotate, normal));"
        << endl << "    vec3 bitangent = cross(normal, tangent);"
        << endl << "    mat3 TBN = mat3(tangent, bitangent, normal);"
        << endl << ""
        << endl << "    int   kernelSize = offset.size;"
        << endl << "    float occlusion  = 0.0;"
        << endl << ""
        << endl << "    for (int i = 0; i < kernelSize; ++i)"
        << endl << "    {"
        << endl << "        vec3 sample = TBN * offset.kernel[i];"
        << endl << "        sample = position + sample * uRadius;"
        << endl << ""
        << endl << "        vec4 p = vec4(sample, 1.0);"
        << endl << "        p = uProjectionMatrix * p;"
        << endl << "        p.xyz /= p.w;"
        << endl << "        p.xyz  = p.xyz * 0.5 + 0.5;"
        << endl << ""
        << endl << "        float depth = texture(PositionTex, p.xy).z;"
        << endl << ""
        << endl << "        float check = smoothstep(0.0, 1.0, uRadius / abs(position.z - depth));"
        << endl << "        occlusion += (depth >= sample.z + uBias ? 1.0 : 0.0) * check;"
        << endl << "    }"
        << endl << ""
        << endl << "    occlusion = 1.0 - occlusion / kernelSize;"
        << endl << ""
        << endl << "    FragColor = occlusion;"
        << endl << "}"
        ;
    }
}

void SSAOStage::genBlurPassVertexShader(std::stringstream& ost)
{
    using namespace std;

    ost
        << endl << "#version 330 compatibility"
        << endl << ""
        << endl << "layout(location = 0) in vec2 aVertex;"
        << endl << ""
        << endl << "out vec2 vTexCoord;"
        << endl << ""
        << endl << "void main()"
        << endl << "{"
        << endl << "    vec4 vPos = vec4(aVertex.x, aVertex.y, 0, 1);"
        << endl << "    vTexCoord = 0.5 * vPos.xy + 0.5;"
        << endl << ""
        << endl << "    gl_Position = vPos;"
        << endl << "}"
        << endl << ""
    ;
}

void SSAOStage::genBlurPassFragmentShader(std::stringstream& ost)
{
    using namespace std;

    ost
        << endl << "#version 330 compatibility"
        << endl << ""
        << endl << "in vec2 vTexCoord;"
        << endl << ""
        << endl << "uniform sampler2D SSAOTex;"
        << endl << ""
        << endl << "layout(location = 0) out float FragColor;"
        << endl << ""
        << endl << "void main()"
        << endl << "{"
        << endl << "    vec2 texelSize = 1.0 / vec2(textureSize(SSAOTex, 0));"
        << endl << "    float result = 0.0;"
        << endl << "    for (int x = -2; x < 2; ++x)"
        << endl << "    {"
        << endl << "        for (int y = -2; y < 2; ++y)"
        << endl << "        {"
        << endl << "            vec2 offset = vec2(float(x), float(y)) * texelSize;"
        << endl << "            result += texture(SSAOTex, vTexCoord + offset).r;"
        << endl << "        }"
        << endl << "    }"
        << endl << ""
        << endl << "    FragColor = result / 16.0;"
        << endl << "}"
        << endl << ""
        ;
}

OSG_END_NAMESPACE
