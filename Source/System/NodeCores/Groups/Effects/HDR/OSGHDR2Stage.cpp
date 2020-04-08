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

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGRenderAction.h"
#include "OSGTime.h"

#include "OSGHDR2Stage.h"
#include "OSGHDR2StageData.h"

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
#include "OSGSimpleSHLFunctions.h"
#include "OSGSimpleSHLVariableChunk.h"
#include "OSGUniformBufferObjStd140Chunk.h"

#include "OSGMatrixUtility.h"
#include "OSGShaderUtility.h"

#include "OSGGLU.h"
#include "OSGGLDebugUtils.h"

#ifdef _DEBUG
#define OSG_WRITE_SHADER_CODE_TO_FILE
#endif

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGHDR2StageBase.cpp file.
// To modify it, please change the .fcd file (OSGHDR2Stage.fcd) and
// regenerate the base file.

static Real64 Log2(Real64 number);
static Int32 MipmapLevels(Int32 n);
static std::size_t align_offset(std::size_t base_alignment, std::size_t base_offset);

#ifdef OSG_WRITE_SHADER_CODE_TO_FILE
static std::string getShaderCodeFile(const Char8* file)
{
    std::string dir;
    const Char8* name  =  getenv(OSG_NAMESPACE_PREFIX"_LOG_FILE");
    if (name)
    {
        dir = name;
        const std::size_t pos = dir.find_last_of("/\\");
        if (pos != std::string::npos && dir.size() > pos+1)
        {
            dir = dir.substr(0, pos+1);
        }
    }

    dir += file;

    return dir;
}
#endif

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 HDR2Stage::_uiFramebufferObjectExt = 
    Window::invalidExtensionID;

UInt32 HDR2Stage::_uiFuncDrawBuffers      =
    Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HDR2Stage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            HDR2Stage::getClassType(), 
            reinterpret_cast<Action::Callback>(&HDR2Stage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            HDR2Stage::getClassType(), 
            reinterpret_cast<Action::Callback>(&HDR2Stage::renderLeave));

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

HDR2Stage::HDR2Stage(void)
: Inherited          (     )
, _mapUpdate         (     )
, _mapUpdateUboBuffer(     )
{
    _mfFilmicCurveParameters.push_back(0.15f);
    _mfFilmicCurveParameters.push_back(0.5f);
    _mfFilmicCurveParameters.push_back(0.1f);
    _mfFilmicCurveParameters.push_back(0.2f);
    _mfFilmicCurveParameters.push_back(0.02f);
    _mfFilmicCurveParameters.push_back(0.3f);
    _mfFilmicCurveParameters.push_back(11.2f);
}

HDR2Stage::HDR2Stage(const HDR2Stage &source)
: Inherited          (source)
, _mapUpdate         (     )
, _mapUpdateUboBuffer(     )
{
}

HDR2Stage::~HDR2Stage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void HDR2Stage::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    //
    // The BeaconMatrixFieldMask is deliberately omitted
    // 

    if((whichField & ( ApplyGammaFieldMask |
                       AccurateGammaFieldMask |
                       GammaFieldMask |
                       ShadowLiftColorFieldMask |
                       MidToneGammaColorFieldMask |
                       HighlightGainColorFieldMask |
                       AdjustLuminanceFieldMask |
                       PerformBloomFieldMask |
                       BloomBackgroundFieldMask |
                       ForceBackgroundFieldMask |
                       Use_ITU_R_BT_709FieldMask |
                       TargetFieldMask |
                       CarryDepthFieldMask |
                       PerformDitheringFieldMask |
                       ColorBufferInternalFormatFieldMask |
                       ColorBufferPixelFormatFieldMask |
                       ColorBufferTypeFieldMask |
                       DepthBufferInternalFormatFieldMask |
                       DepthBufferPixelFormatFieldMask |
                       DepthBufferTypeFieldMask |
                       LumBufferInternalFormatFieldMask |
                       LumBufferPixelFormatFieldMask |
                       LumBufferTypeFieldMask |
                       ImageBufferInternalFormatFieldMask |
                       ImageBufferPixelFormatFieldMask |
                       ImageBufferTypeFieldMask |
                       NumSamplesFieldMask |
                       MipmapLevelFieldMask)) != 0)
    {
        UpdateMapT::iterator iter = _mapUpdate.begin();
        UpdateMapT::iterator end  = _mapUpdate.end  ();

        for (; iter != end; ++iter)
            iter->second = true;
    }

    if((whichField & (TauFieldMask |
                      BloomThresholdFieldMask |
                      BloomMagnitudeFieldMask |
                      NumTapsFieldMask |
                      BlurGaussSigmaFieldMask |
                      ToneMappingModeFieldMask |
                      AutoExposureModeFieldMask |
                      ExposureFieldMask |
                      KeyValueFieldMask |
                      ApertureFNumberFieldMask |
                      ShutterSpeedFieldMask |
                      ISOFieldMask |
                      WhiteLevelFieldMask |
                      SaturationFieldMask |
                      FilterColorFieldMask |
                      ContrastFieldMask |
                      UseLinChromCorrectionFieldMask |
                      FilmicCurveParametersFieldMask |
                      DragoBiasFieldMask)) != 0)
    {
        UpdateMapT::iterator iter = _mapUpdateUboBuffer.begin();
        UpdateMapT::iterator end  = _mapUpdateUboBuffer.end  ();

        for (; iter != end; ++iter)
            iter->second = true;
    }

    Inherited::changed(whichField, origin, details);
}

void HDR2Stage::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                     const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump HDR2Stage NI" << std::endl;
}

#if 0
void HDR2Stage::write_read_back_images(HDR2StageData* pData) const
{
    FrameBufferObject*  pBackgroundFBO  = pData->getBackgroundRenderTarget();
    FrameBufferObject*  pSceneFBO       = pData->getSceneRenderTarget();
    FrameBufferObject*  pCompositeFBO   = pData->getCompositeRenderTarget();

    TextureBuffer*      pBackgroundTB   = dynamic_cast<TextureBuffer*>(pBackgroundFBO->getColorAttachments(0));
    TextureBuffer*      pSceneTB        = dynamic_cast<TextureBuffer*>(pSceneFBO     ->getColorAttachments(0));
    TextureBuffer*      pCompositeTB    = dynamic_cast<TextureBuffer*>(pCompositeFBO ->getColorAttachments(0));

    TextureObjChunk*    pBackgroundTBO  = pBackgroundTB->getTexture();
    TextureObjChunk*    pSceneTBO       = pSceneTB     ->getTexture();
    TextureObjChunk*    pCompositeTBO   = pCompositeTB ->getTexture();

    Image*              pBackgroundIMG  = pBackgroundTBO->getImage();
    Image*              pSceneIMG       = pSceneTBO     ->getImage();
    Image*              pCompositeIMG   = pCompositeTBO ->getImage();

    //pBackgroundIMG->write("d:/work/BackgroundIMG.tif");
    //pSceneIMG     ->write("d:/work/SceneIMG.tif");
    //pCompositeIMG ->write("d:/work/CompositeIMG.tif");
}

void HDR2Stage::dump_fbo(const char* name, FrameBufferObject* fbo, std::stringstream& ss) const
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

std::string HDR2Stage::dump_stage(HDR2StageData* pData) const
{
    std::stringstream ss;
    ss << std::endl;

    FrameBufferObject* pBackgroundFBO      = pData->getBackgroundRenderTarget();
    FrameBufferObject* pSceneFBO           = pData->getSceneRenderTarget();
    FrameBufferObject* pInitLuminanceFBO   = pData->getLuminanceRenderTarget();
    FrameBufferObject* pAdaptLuminanceFBO0 = pData->getAdaptLuminanceRenderTarget(0);
    FrameBufferObject* pAdaptLuminanceFBO1 = pData->getAdaptLuminanceRenderTarget(1);
    FrameBufferObject* pThresholdFBO       = pData->getThresholdRenderTarget();
    FrameBufferObject* pScaleFBO0          = NULL;
    FrameBufferObject* pScaleFBO1          = NULL;
    FrameBufferObject* pScaleFBO2          = NULL;
    if (getPerformBloom())
    {
        pScaleFBO0 = pData->getScaleRenderTarget(0);
        pScaleFBO1 = pData->getScaleRenderTarget(1);
        pScaleFBO2 = pData->getScaleRenderTarget(2);
    }
    FrameBufferObject* pBlurHorizFBO       = pData->getBlurHorizRenderTarget();
    FrameBufferObject* pBlurVertFBO        = pData->getBlurVertRenderTarget();
    FrameBufferObject* pCompositeFBO       = pData->getCompositeRenderTarget();

    dump_fbo("Background",      pBackgroundFBO,      ss);
    dump_fbo("Scene",           pSceneFBO,           ss);
    dump_fbo("InitLuminance",   pInitLuminanceFBO,   ss);
    dump_fbo("AdaptLuminance0", pAdaptLuminanceFBO0, ss);
    dump_fbo("AdaptLuminance1", pAdaptLuminanceFBO1, ss);
    dump_fbo("Threshold",       pThresholdFBO,       ss);
    dump_fbo("Scale0",          pScaleFBO0,          ss);
    dump_fbo("Scale1",          pScaleFBO1,          ss);
    dump_fbo("Scale2",          pScaleFBO2,          ss);
    dump_fbo("Composite",       pCompositeFBO,       ss);

    return ss.str();
}
#endif

/*------------------------------- Access ------------------------------------*/

Vec3f HDR2Stage::getAdjustedShadowLift() const
{
    Vec3f  liftColor = 2.0f * getShadowLiftColor();
    return liftColor;
}

Vec3f HDR2Stage::getAdjustedInvMidtoneGamma() const
{
    Vec3f  gammaColor = 2.0f * getMidToneGammaColor();
    Vec3f  invGammaAdjust = Vec3f(1.f/gammaColor[0], 1.f/gammaColor[1], 1.f/gammaColor[2]);
    return invGammaAdjust;
}

Vec3f HDR2Stage::getAdjustedHighlightGain() const
{
    Vec3f  gainColor = 2.0f * getHighlightGainColor();
    return gainColor;
}

/*------------------------------- Draw ------------------------------------*/

Action::ResultE HDR2Stage::renderEnter(Action* action)
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

    HDR2StageDataUnrecPtr pData = a->getData<HDR2StageData *>(_iDataSlotId);
    if (pData == NULL)
    {
        this->initData(a, iVPWidth, iVPHeight);
#if 0
        pData = a->getData<HDR2StageData *>(_iDataSlotId);
        std::string dump_str = dump_stage(pData);
        ::OutputDebugString(dump_str.c_str());
        FDEBUG((dump_str.c_str()));
#endif
    }
    else
    {
#if 0
        // only testing: force update
        HDR2StageData* pStageData = pData;
        _mapUpdate         [pStageData] = true;
        _mapUpdateUboBuffer[pStageData] = true;
#endif

        this->updateData(a, iVPWidth, iVPHeight);
    }

    pData = a->getData<HDR2StageData *>(_iDataSlotId);

    //
    // The duty of the HDR stage is to render the final scene into a
    // texture image and then tonemap that image and add possibly some
    // bloom effect.
    // In order to achieve this we must setup some partition groups
    // that are responsible for some specific task of the rendering.
    // The following render partitions are setup:
    //      1. Background RenderPartition:
    //          This partition renders solely the background into a
    //          separate texture. This texture is needed if the back-
    //          ground should not take part in the tonemapping.
    //          This texture must be ready to use in the HDR post 
    //          processing pass.
    //      2. Scene RenderPartition:
    //          This partition renders the scene content into the scene
    //          texture. This texture is the input for the HDR post
    //          processing pass. It is important that the scene render
    //          partition does not set the background. That is because
    //          the scene recursion can meet stage nodes that might itself
    //          add render partitions to the render action. If this happens
    //          they would be rendered before the scene render partition.
    //          and the scene render partition's background would then override
    //          the current image. Therefore the background must be handled
    //          separately.
    //      3. HDR Postprocessing RenderPartition:
    //          This render partition performs all the actual work wrsp. to
    //          tonemapping and blooming.
    //      4. Scene Background RenderPartition:
    //          This partition renders solely the background into the scene
    //          image. This partition is pushed last and therefore gets 
    //          rendered first solving the background problems mentioned
    //          before.
    //

    a->disableDefaultPartition();

    this->beginPartitionGroup(a);
    {
        //
        // Render Background into separate texture
        //
        if (getForceBackground())
        {
            this->pushPartition(a);
                                //, RenderPartition::CopyAll);    // ??? all correct here
            {
                RenderPartition*   pPart   = a    ->getActivePartition();
                FrameBufferObject* pTarget = pData->getBackgroundRenderTarget();

                setRenderTarget(pTarget);

                pPart->setRenderTarget(pTarget);
                pPart->setWindow(a->getWindow());

                //pPart->calcViewportDimension(0.f, 0.f, 1.f, 1.f, pTarget->getWidth(), pTarget->getHeight());
                pPart->calcViewportDimension(
                            pArea->getLeft  (), 
                            pArea->getBottom(), 
                            pArea->getRight (), 
                            pArea->getTop   (), 
                            
                            pTarget->getWidth(), 
                            pTarget->getHeight());


                if(pCam != NULL)
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
            
                // Nothing to do, we only are interested in the background!
            }
            this->popPartition(a);
        }

        //
        // Render scene without background
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
                            //  | RenderPartition::CopyAll // ??? all correct here
                            );
        {
            RenderPartition*   pPart   = a    ->getActivePartition();
            FrameBufferObject* pTarget = pData->getSceneRenderTarget();
           
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
                
            //
            // No background here. The background is handled separately below.
            //
            pPart->setBackground(NULL);
            
            this->recurseFromThis(a);
            a->useNodeList(false);
        }
        this->popPartition(a);

        a->getActivePartition()->disable();

        //
        // The HDR post processing task
        //
        this->pushPartition(a,
                            (RenderPartition::CopyWindow       |
                             RenderPartition::CopyViewportSize |
                             RenderPartition::CopyTarget 
                            //| RenderPartition::CopyAll // ??? all correct here
                                ),
                             RenderPartition::SimpleCallback    );
        {
            RenderPartition* pPart = a->getActivePartition();

            Matrix m, t;

            m.setIdentity();
            t.setIdentity();
                
            pPart->setupProjection(m, t);

            RenderPartition::SimpleDrawCallback f;

            f = boost::bind(&HDR2Stage::postProcess, this, _1);

            pPart->dropFunctor(f);
        }
        this->popPartition(a);
    }
    this->endPartitionGroup(a);

    //
    // Render scene background only. Actually this happens first
    //
    this->pushPartition(a); //, RenderPartition::CopyAll);    // ??? all correct here
    {
        RenderPartition*   pPart   = a    ->getActivePartition();
        FrameBufferObject* pTarget = pData->getSceneRenderTarget();
            
        setRenderTarget(pTarget);

        pPart->setRenderTarget(pTarget);
        pPart->setWindow(a->getWindow());

        //pPart->calcViewportDimension(0.f, 0.f, 1.f, 1.f, pTarget->getWidth (), pTarget->getHeight());
        pPart->calcViewportDimension(
                    pArea->getLeft  (), 
                    pArea->getBottom(), 
                    pArea->getRight (), 
                    pArea->getTop   (), 
                            
                    pTarget->getWidth(), 
                    pTarget->getHeight());

        if(pCam != NULL)
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
            
        // Nothing to do, we only are interested in the background!
    }
    this->popPartition(a);

    return Action::Skip;
}

Action::ResultE HDR2Stage::renderLeave(Action *action)
{
    if (getActivate() == false)
        return Group::renderLeave(action);

    return Action::Skip;
}

/*------------------------------ Data -------------------------------------*/

void HDR2Stage::initData(RenderAction* pAction,
                         Int32         iVPWidth,
                         Int32         iVPHeight)
{
    HDR2StageDataUnrecPtr pData = pAction->getData<HDR2StageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = setupStageData(iVPWidth, iVPHeight);

        this->setData(pData, _iDataSlotId, pAction);
    }
}

void HDR2Stage::updateData(RenderAction* pAction,
                           Int32         iVPWidth,
                           Int32         iVPHeight)
{
    HDR2StageDataUnrecPtr pData = pAction->getData<HDR2StageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        initData(pAction, iVPWidth, iVPHeight);

        pData = pAction->getData<HDR2StageData *>(_iDataSlotId);

        Camera* pCam = pAction->getCamera();
        if (pCam)
        {
            pData->setZNear(pCam->getNear());
            pData->setZFar (pCam->getFar());
        }
    }
    else
    {
        Camera* pCam = pAction->getCamera();
        if (pCam)
        {
            pData->setZNear(pCam->getNear());
            pData->setZFar (pCam->getFar());
        }

        updateStageData(pData, iVPWidth, iVPHeight);
    }
}

/*---------------------------- StageData ----------------------------------*/

HDR2StageDataTransitPtr HDR2Stage::setupStageData(Int32 iPixelWidth,
                                                  Int32 iPixelHeight)
{
    HDR2StageDataUnrecPtr hdrStageData = HDR2StageData::createLocal();

    if(hdrStageData == NULL)
        return HDR2StageDataTransitPtr(NULL);

    _mapUpdate         [hdrStageData] = true;
    _mapUpdateUboBuffer[hdrStageData] = true;

    hdrStageData->setWidth (iPixelWidth );
    hdrStageData->setHeight(iPixelHeight);

    OSG::Thread::setCurrentLocalFlags();

    setupUBOData        (hdrStageData);
    setupSharedData     (hdrStageData);
    setupRenderTargets  (hdrStageData, iPixelWidth, iPixelHeight);
    setupMaterials      (hdrStageData);

    Thread::getCurrentChangeList()->commitChanges();

    return HDR2StageDataTransitPtr(hdrStageData);
}

void HDR2Stage::updateStageData(HDR2StageData* pData,
                                Int32          iPixelWidth,
                                Int32          iPixelHeight)
{
    bool resize = false;

    if (iPixelWidth != pData->getWidth() || iPixelHeight != pData->getHeight())
        resize = true;

    if (!_mapUpdate[pData] && !_mapUpdateUboBuffer[pData] && !resize)
        return;

    pData->setWidth (iPixelWidth );
    pData->setHeight(iPixelHeight);

    updateUBOData      (pData);
    updateSharedData   (pData);

    if (resize)
        updateRenderTargets(pData, iPixelWidth, iPixelHeight);

    updateMaterials    (pData);

    _mapUpdate         [pData] = false;
    _mapUpdateUboBuffer[pData] = false;

    Thread::getCurrentChangeList()->commitChanges();
}

/*------------------------ StageData Details ------------------------------*/

std::size_t HDR2Stage::calcUBOBufferSize()
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float BloomThreshold
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float BloomMagnitude
    ao = align_offset( 4, bo); bo = ao + sizeof(UInt32);   // int   ToneMapTechnique
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float Exposure
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float KeyValue
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float ApertureFNumber
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float ShutterSpeed
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float ISO
    ao = align_offset( 4, bo); bo = ao + sizeof(UInt32);   // int   AutoExposure
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float WhiteLevel
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float ShoulderStrength
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float LinearStrength
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float LinearAngle
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float ToeStrength
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float ToeNumerator
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float ToeDenominator
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float LinearWhite
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float LumSaturation
    ao = align_offset(16, bo); bo = ao + sizeof(Color3f);  // float filterColor
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float Contrast
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float Bias
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float Tau
    ao = align_offset( 4, bo); bo = ao + sizeof(Int32);    // int   nTaps
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float Sigma
    ao = align_offset( 4, bo); bo = ao + sizeof(Int32);    // bool  UseLinChromInterp
    ao = align_offset( 4, bo); bo = ao;                    // padding
    return ao;
}

void HDR2Stage::fillUBOBuffer(std::vector<OSG::UInt8>& buffer)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getBloomThreshold();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getBloomMagnitude();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::UInt32*>(&buffer[0] + ao)) = getToneMappingMode();
    bo = ao + sizeof(OSG::UInt32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getExposure();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getKeyValue();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getApertureFNumber();
    bo = ao + sizeof(Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getShutterSpeed();
    bo = ao + sizeof(Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getISO();
    bo = ao + sizeof(Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::UInt32*>(&buffer[0] + ao)) = getAutoExposureMode();
    bo = ao + sizeof(OSG::UInt32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = osgMax(getWhiteLevel(), 0.01f);
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicShoulderStrenght();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicLinearStrength();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicLinearAngle();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicToeStrength();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicToeNumerator();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicToeDenominator();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicLinearWhite();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getSaturation();
    bo = ao + sizeof(OSG::Real32);

    Color3f filterColor = sRGBToLinear(getFilterColor());

    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &filterColor[0], sizeof(Color3f));  bo = ao + sizeof(Color3f);
    bo = ao + sizeof(Color3f);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getContrast();
    bo = ao + sizeof(Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getDragoBias();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getTau();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = getNumTaps();
    bo = ao + sizeof(OSG::Int32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getBlurGaussSigma();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = getUseLinChromCorrection();
    bo = ao + sizeof(OSG::Int32);
}

void HDR2Stage::setupUBOData(HDR2StageData* pData)
{
    UniformBufferObjStd140ChunkUnrecPtr uboChunk = UniformBufferObjStd140Chunk::createLocal();
    std::vector<OSG::UInt8> buffer(calcUBOBufferSize());
    fillUBOBuffer(buffer);

    uboChunk->editMFBuffer()->setValues(buffer);
    uboChunk->setUsage(GL_DYNAMIC_DRAW);

    pData->setHdrShaderData(uboChunk);
}

void HDR2Stage::updateUBOData(HDR2StageData* pData)
{
    if (_mapUpdateUboBuffer[pData])
    {
        UniformBufferObjStd140Chunk* uboChunk = pData->getHdrShaderData();
        std::vector<OSG::UInt8> buffer(calcUBOBufferSize());
        fillUBOBuffer(buffer);

        uboChunk->editMFBuffer()->setValues(buffer);
    }
}

void HDR2Stage::setupSharedData(HDR2StageData* pData)
{
    MaterialChunkUnrecPtr matChunk = MaterialChunk::createLocal();
    matChunk->setLit(false);
    pData->setSharedMaterialChunk(matChunk);
}

void HDR2Stage::updateSharedData(HDR2StageData* pData)
{
}

void HDR2Stage::setupRenderTargets(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    setupBackgroundRenderTarget     (pData, iPixelWidth, iPixelHeight);
    setupSceneRenderTarget          (pData, iPixelWidth, iPixelHeight);
    setupLuminanceRenderTarget      (pData, iPixelWidth, iPixelHeight);
    setupAdaptLuminanceRenderTarget (pData, iPixelWidth, iPixelHeight);

    if (getPerformBloom())
    {
        setupThresholdRenderTarget      (pData, iPixelWidth, iPixelHeight);
        setupScaleRenderTarget          (pData, iPixelWidth, iPixelHeight);
        setupBlurRenderTarget           (pData, iPixelWidth, iPixelHeight);
    }

    setupCompositeRenderTarget      (pData, iPixelWidth, iPixelHeight);
}

void HDR2Stage::updateRenderTargets(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    updateBackgroundRenderTarget    (pData, iPixelWidth, iPixelHeight);
    updateSceneRenderTarget         (pData, iPixelWidth, iPixelHeight);
    updateLuminanceRenderTarget     (pData, iPixelWidth, iPixelHeight);
    updateAdaptLuminanceRenderTarget(pData, iPixelWidth, iPixelHeight);

    if (getPerformBloom())
    {
        updateThresholdRenderTarget     (pData, iPixelWidth, iPixelHeight);
        updateScaleRenderTarget         (pData, iPixelWidth, iPixelHeight);
        updateBlurRenderTarget          (pData, iPixelWidth, iPixelHeight);
    }

    updateCompositeRenderTarget     (pData, iPixelWidth, iPixelHeight);
}

void HDR2Stage::setupMaterials(HDR2StageData* pData)
{
    setupLuminanceMapMaterial  (pData);
    setupAdaptLuminanceMaterial(pData);

    if (getPerformBloom())
    {
        setupThresholdMaterial     (pData);
        setupScaleMaterial         (pData);
        setupBlurHorizMaterial     (pData);
        setupBlurVertMaterial      (pData);
    }

    setupCompositeMaterial     (pData);
    setupFinalScreenMaterial   (pData);
}

void HDR2Stage::updateMaterials(HDR2StageData* pData)
{
    updateLuminanceMapMaterial  (pData);
    updateAdaptLuminanceMaterial(pData);

    if (getPerformBloom())
    {
        updateThresholdMaterial     (pData);
        updateScaleMaterial         (pData);
        updateBlurHorizMaterial     (pData);
        updateBlurVertMaterial      (pData);
    }

    updateCompositeMaterial     (pData);
    updateFinalScreenMaterial   (pData);
}

void HDR2Stage::setupBackgroundRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObjectUnrecPtr pBackgroundFBO = FrameBufferObject::createLocal();

    pBackgroundFBO->setSize(iPixelWidth, iPixelHeight);

    if (getNumSamples() > 0)
    {
        pBackgroundFBO->setEnableMultiSample(true);
        pBackgroundFBO->setColorSamples(getNumSamples());
    }

    ImageUnrecPtr pBackgroundImg = Image ::createLocal();
    pBackgroundImg->set(getColorBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getColorBufferType(), false);

    TextureObjChunkUnrecPtr pBackgroundTexObjChunk = TextureObjChunk::createLocal();
    pBackgroundTexObjChunk->setImage         (pBackgroundImg); 
    pBackgroundTexObjChunk->setMinFilter     (GL_LINEAR);
    pBackgroundTexObjChunk->setMagFilter     (GL_LINEAR);
    pBackgroundTexObjChunk->setWrapS         (GL_REPEAT);
    pBackgroundTexObjChunk->setWrapT         (GL_REPEAT);
    pBackgroundTexObjChunk->setInternalFormat(getColorBufferInternalFormat());

    ImageUnrecPtr pDepthImg = Image ::createLocal();
    pDepthImg->set(getDepthBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getDepthBufferType(), false);

    TextureObjChunkUnrecPtr pDepthTexObjChunk = TextureObjChunk::createLocal();
    pDepthTexObjChunk->setImage         (pDepthImg); 
    pDepthTexObjChunk->setMinFilter     (GL_LINEAR);
    pDepthTexObjChunk->setMagFilter     (GL_LINEAR);
    pDepthTexObjChunk->setWrapS         (GL_REPEAT);
    pDepthTexObjChunk->setWrapT         (GL_REPEAT);
    pDepthTexObjChunk->setInternalFormat(getDepthBufferInternalFormat());

    TextureBufferUnrecPtr pBackgroundTexBuffer = TextureBuffer::createLocal();
    TextureBufferUnrecPtr pDepthTexBuffer      = TextureBuffer::createLocal();

#if 0
    pBackgroundFBO->setPostProcessOnDeactivate(true);
    pBackgroundTexBuffer->setReadBack(true);
#endif

    pBackgroundTexBuffer->setTexture(pBackgroundTexObjChunk);
    pDepthTexBuffer     ->setTexture(pDepthTexObjChunk);

    pBackgroundFBO->setColorAttachment(pBackgroundTexBuffer, 0);
    pBackgroundFBO->setDepthAttachment(pDepthTexBuffer);

    pBackgroundFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setBackgroundRenderTarget(pBackgroundFBO);
}

void HDR2Stage::setupSceneRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObjectUnrecPtr pSceneFBO = FrameBufferObject::createLocal();
    pSceneFBO->setSize(iPixelWidth, iPixelHeight);

    if (getNumSamples() > 0)
    {
        pSceneFBO->setEnableMultiSample(true);
        pSceneFBO->setColorSamples(getNumSamples());
    }

    ImageUnrecPtr pSceneImg = Image ::createLocal();
    pSceneImg->set(getColorBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getColorBufferType(), false);

    TextureObjChunkUnrecPtr pSceneTexObjChunk = TextureObjChunk::createLocal();
    pSceneTexObjChunk->setImage         (pSceneImg); 
    pSceneTexObjChunk->setMinFilter     (GL_LINEAR);
    pSceneTexObjChunk->setMagFilter     (GL_LINEAR);
    pSceneTexObjChunk->setWrapS         (GL_REPEAT);
    pSceneTexObjChunk->setWrapT         (GL_REPEAT);
    pSceneTexObjChunk->setInternalFormat(getColorBufferInternalFormat());

    ImageUnrecPtr pDepthImg = Image ::createLocal();
    pDepthImg->set(getDepthBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getDepthBufferType(), false);

    TextureObjChunkUnrecPtr pDepthTexObjChunk = TextureObjChunk::createLocal();
    pDepthTexObjChunk->setImage         (pDepthImg); 
    pDepthTexObjChunk->setMinFilter     (GL_LINEAR);
    pDepthTexObjChunk->setMagFilter     (GL_LINEAR);
    pDepthTexObjChunk->setWrapS         (GL_REPEAT);
    pDepthTexObjChunk->setWrapT         (GL_REPEAT);
    pDepthTexObjChunk->setInternalFormat(getDepthBufferInternalFormat());

    TextureBufferUnrecPtr pSceneTexBuffer   = TextureBuffer::createLocal();
    TextureBufferUnrecPtr pDepthTexBuffer   = TextureBuffer::createLocal();

    pSceneTexBuffer  ->setTexture(pSceneTexObjChunk);
    pDepthTexBuffer  ->setTexture(pDepthTexObjChunk);

#if 0
    pSceneFBO->setPostProcessOnDeactivate(true);
    pSceneTexBuffer->setReadBack(true);
#endif

    pSceneFBO->setColorAttachment  (pSceneTexBuffer, 0);
    pSceneFBO->setDepthAttachment  (pDepthTexBuffer);

    if ( (getDepthBufferInternalFormat() == GL_DEPTH24_STENCIL8 || getDepthBufferInternalFormat() == GL_DEPTH32F_STENCIL8)
       && getDepthBufferPixelFormat   () == GL_DEPTH_STENCIL )
    {
        pSceneFBO->setStencilAttachment(pDepthTexBuffer);
    }

    pSceneFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setSceneRenderTarget(pSceneFBO);
}

void HDR2Stage::setupLuminanceRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObjectUnrecPtr pInitLuminanceFBO = FrameBufferObject::createLocal();
    pInitLuminanceFBO->setSize(iPixelWidth, iPixelHeight);

    ImageUnrecPtr pInitLuminanceImg = Image ::createLocal();
    pInitLuminanceImg->set(getLumBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getLumBufferType(), false);

    TextureObjChunkUnrecPtr pInitLuminanceTexObjChunk = TextureObjChunk::createLocal();
    pInitLuminanceTexObjChunk->setImage         (pInitLuminanceImg); 
    pInitLuminanceTexObjChunk->setMinFilter     (GL_LINEAR);
    pInitLuminanceTexObjChunk->setMagFilter     (GL_LINEAR);
    pInitLuminanceTexObjChunk->setWrapS         (GL_REPEAT);
    pInitLuminanceTexObjChunk->setWrapT         (GL_REPEAT);
    pInitLuminanceTexObjChunk->setInternalFormat(getLumBufferInternalFormat());

    TextureBufferUnrecPtr pInitLuminanceTexBuffer = TextureBuffer::createLocal();
    pInitLuminanceTexBuffer->setTexture(pInitLuminanceTexObjChunk);

    pInitLuminanceFBO->setColorAttachment(pInitLuminanceTexBuffer, 0);
    pInitLuminanceFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setLuminanceRenderTarget(pInitLuminanceFBO);
}

void HDR2Stage::setupAdaptLuminanceRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth, iPixelHeight));

    for (UInt32 i = 0; i < 2; ++i)
    {
        FrameBufferObjectUnrecPtr pAdaptLuminanceFBO = FrameBufferObject::createLocal();
        pAdaptLuminanceFBO->setSize(iPixelWidth, iPixelHeight);
        pAdaptLuminanceFBO->setPostProcessOnDeactivate(true);   // ??? ToDo: check if necessary

        ImageUnrecPtr pAdaptLuminanceImg = Image ::createLocal();
        pAdaptLuminanceImg->set(getLumBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, levels, 1, 0.0, 0, getLumBufferType(), false);

        TextureObjChunkUnrecPtr pAdaptLuminanceTexObjChunk = TextureObjChunk::createLocal();
        pAdaptLuminanceTexObjChunk->setImage         (pAdaptLuminanceImg); 
        pAdaptLuminanceTexObjChunk->setMinFilter     (GL_LINEAR_MIPMAP_LINEAR);
        pAdaptLuminanceTexObjChunk->setMagFilter     (GL_LINEAR);
        pAdaptLuminanceTexObjChunk->setWrapS         (GL_REPEAT);
        pAdaptLuminanceTexObjChunk->setWrapT         (GL_REPEAT);
        pAdaptLuminanceTexObjChunk->setInternalFormat(getLumBufferInternalFormat());

        TextureBufferUnrecPtr pAdaptLuminanceTexBuffer = TextureBuffer::createLocal();
        pAdaptLuminanceTexBuffer->setTexture(pAdaptLuminanceTexObjChunk);

        pAdaptLuminanceFBO->setColorAttachment(pAdaptLuminanceTexBuffer, 0);
        pAdaptLuminanceFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

        pData->pushToAdaptLuminanceRenderTarget(pAdaptLuminanceFBO);
    }
}

void HDR2Stage::setupThresholdRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObjectUnrecPtr pThresholdFBO = FrameBufferObject::createLocal();
    pThresholdFBO->setSize(iPixelWidth, iPixelHeight);

    ImageUnrecPtr pThresholdImg = Image ::createLocal();
    pThresholdImg->set(getImageBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getImageBufferType(), false);

    TextureObjChunkUnrecPtr pThresholdTexObjChunk = TextureObjChunk::createLocal();
    pThresholdTexObjChunk->setImage         (pThresholdImg); 
    pThresholdTexObjChunk->setMinFilter     (GL_LINEAR);
    pThresholdTexObjChunk->setMagFilter     (GL_LINEAR);
    pThresholdTexObjChunk->setWrapS         (GL_CLAMP_TO_EDGE);
    pThresholdTexObjChunk->setWrapT         (GL_CLAMP_TO_EDGE);
    pThresholdTexObjChunk->setInternalFormat(getImageBufferInternalFormat());

    TextureBufferUnrecPtr pThresholdTexBuffer = TextureBuffer::createLocal();
    pThresholdTexBuffer->setTexture(pThresholdTexObjChunk);

    pThresholdFBO->setColorAttachment(pThresholdTexBuffer, 0);
    pThresholdFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setThresholdRenderTarget(pThresholdFBO);
}

void HDR2Stage::setupScaleRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    for (UInt32 i = 0; i < 3; ++i)
    {
        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        FrameBufferObjectUnrecPtr pScaleFBO = FrameBufferObject::createLocal();
        pScaleFBO->setSize(w, h);

        ImageUnrecPtr pScaleImg = Image ::createLocal();
        pScaleImg->set(getImageBufferPixelFormat(), w, h, 1, 1, 1, 0.0, 0, getImageBufferType(), false);

        TextureObjChunkUnrecPtr pScaleTexObjChunk = TextureObjChunk::createLocal();
        pScaleTexObjChunk->setImage         (pScaleImg); 
        pScaleTexObjChunk->setMinFilter     (GL_LINEAR);
        pScaleTexObjChunk->setMagFilter     (GL_LINEAR);
        pScaleTexObjChunk->setWrapS         (GL_CLAMP_TO_EDGE);
        pScaleTexObjChunk->setWrapT         (GL_CLAMP_TO_EDGE);
        pScaleTexObjChunk->setInternalFormat(getImageBufferInternalFormat());

        TextureBufferUnrecPtr pScaleTexBuffer = TextureBuffer::createLocal();
        pScaleTexBuffer->setTexture(pScaleTexObjChunk);

        pScaleFBO->setColorAttachment(pScaleTexBuffer, 0);
        pScaleFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

        pData->pushToScaleRenderTarget(pScaleFBO);
    }
}

void HDR2Stage::setupBlurRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    UInt32 w = std::max( iPixelWidth / (1 << 3), 1);
    UInt32 h = std::max(iPixelHeight / (1 << 3), 1);

    FrameBufferObjectUnrecPtr pBlurHorizFBO = FrameBufferObject::createLocal();
    pBlurHorizFBO->setSize(w, h);

    ImageUnrecPtr pBlurHorizImg = Image ::createLocal();
    pBlurHorizImg->set(getImageBufferPixelFormat(), w, h, 1, 1, 1, 0.0, 0, getImageBufferType(), false);

    TextureObjChunkUnrecPtr pBlurHorizTexObjChunk = TextureObjChunk::createLocal();
    pBlurHorizTexObjChunk->setImage         (pBlurHorizImg); 
    pBlurHorizTexObjChunk->setMinFilter     (GL_LINEAR);
    pBlurHorizTexObjChunk->setMagFilter     (GL_LINEAR);
    pBlurHorizTexObjChunk->setWrapS         (GL_CLAMP_TO_EDGE);
    pBlurHorizTexObjChunk->setWrapT         (GL_CLAMP_TO_EDGE);
    pBlurHorizTexObjChunk->setInternalFormat(getImageBufferInternalFormat());

    TextureBufferUnrecPtr pBlurHorizTexBuffer = TextureBuffer::createLocal();
    pBlurHorizTexBuffer->setTexture(pBlurHorizTexObjChunk);

    pBlurHorizFBO->setColorAttachment(pBlurHorizTexBuffer, 0);
    pBlurHorizFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setBlurHorizRenderTarget(pBlurHorizFBO);


    FrameBufferObjectUnrecPtr pBlurVertFBO = FrameBufferObject::createLocal();
    pBlurVertFBO->setSize(w, h);

    TextureBufferUnrecPtr pBlurVertTexBuffer = TextureBuffer::createLocal();
    pBlurVertTexBuffer->setTexture(pData->getScaleTexObjChunk(2));

    pBlurVertFBO->setColorAttachment(pBlurVertTexBuffer, 0);
    pBlurVertFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setBlurVertRenderTarget(pBlurVertFBO);
}

void HDR2Stage::setupCompositeRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObjectUnrecPtr pCompositeFBO = FrameBufferObject::createLocal();
    pCompositeFBO->setSize(iPixelWidth, iPixelHeight);


    ImageUnrecPtr pCompositeImg = Image ::createLocal();
    pCompositeImg->set(getImageBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getImageBufferType(), false);

    TextureObjChunkUnrecPtr pCompositeTexObjChunk = TextureObjChunk::createLocal();
    pCompositeTexObjChunk->setImage         (pCompositeImg); 
    pCompositeTexObjChunk->setMinFilter     (GL_LINEAR);
    pCompositeTexObjChunk->setMagFilter     (GL_LINEAR);
    pCompositeTexObjChunk->setWrapS         (GL_REPEAT);
    pCompositeTexObjChunk->setWrapT         (GL_REPEAT);
    pCompositeTexObjChunk->setInternalFormat(getImageBufferInternalFormat());

    ImageUnrecPtr pExposureImg = Image ::createLocal();
    pExposureImg->set(getImageBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getImageBufferType(), false);

    TextureObjChunkUnrecPtr pExposureTexObjChunk = TextureObjChunk::createLocal();
    pExposureTexObjChunk->setImage         (pExposureImg); 
    pExposureTexObjChunk->setMinFilter     (GL_LINEAR);
    pExposureTexObjChunk->setMagFilter     (GL_LINEAR);
    pExposureTexObjChunk->setWrapS         (GL_REPEAT);
    pExposureTexObjChunk->setWrapT         (GL_REPEAT);
    pExposureTexObjChunk->setInternalFormat(getImageBufferInternalFormat());

    TextureBufferUnrecPtr pCompositeTexBuffer = TextureBuffer::createLocal();
    TextureBufferUnrecPtr pExposureTexBuffer  = TextureBuffer::createLocal();

    pCompositeTexBuffer->setTexture(pCompositeTexObjChunk);
    pExposureTexBuffer ->setTexture(pExposureTexObjChunk);

#if 0
    pCompositeFBO->setPostProcessOnDeactivate(true);
    pCompositeTexBuffer->setReadBack(true);
#endif

    pCompositeFBO->setColorAttachment(pCompositeTexBuffer, 0);
    pCompositeFBO->setColorAttachment(pExposureTexBuffer,  1);
    pCompositeFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);
    pCompositeFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT1);

    pData->setCompositeRenderTarget(pCompositeFBO);
}

void HDR2Stage::updateBackgroundRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getBackgroundRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

void HDR2Stage::updateSceneRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getSceneRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

void HDR2Stage::updateLuminanceRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getLuminanceRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

void HDR2Stage::updateAdaptLuminanceRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth, iPixelHeight));

    for (UInt32 i = 0; i < 2; ++i)
    {
        FrameBufferObject* pFBO = pData->getAdaptLuminanceRenderTarget(i);

        TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getColorAttachments(0));
        assert(pTexBuffer);

        TextureObjChunk* pTexObjChunk = pTexBuffer->getTexture();
        assert(pTexObjChunk);

        Image* pImg = pTexObjChunk->getImage();
        assert(pImg);

        pImg->set(getLumBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, levels, 1, 0.0, 0, getLumBufferType(), false);

        pFBO->resizeAll(iPixelWidth, iPixelHeight);
    }
}

void HDR2Stage::updateThresholdRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getThresholdRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

void HDR2Stage::updateScaleRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    for (UInt32 i = 0; i < 3; ++i)
    {
        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        FrameBufferObject* pFBO = pData->getScaleRenderTarget(i);
        pFBO->resizeAll(w, h);
    }
}

void HDR2Stage::updateBlurRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    UInt32 w = std::max( iPixelWidth / (1 << 3), 1);
    UInt32 h = std::max(iPixelHeight / (1 << 3), 1);

    FrameBufferObject* pFBOHoriz = pData->getBlurHorizRenderTarget();
    pFBOHoriz->resizeAll(w, h);

    FrameBufferObject* pFBOVert = pData->getBlurVertRenderTarget();
    pFBOVert->resizeAll(w, h);
}

void HDR2Stage::updateCompositeRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getCompositeRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

void HDR2Stage::setupLuminanceMapMaterial(HDR2StageData* pData)
{
    SimpleSHLChunkUnrecPtr shaderChunk = genLuminanceMapShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("InputTex1", 1);
    shaderChunk->addUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());
    shaderChunk->addUniformVariable("ForceBackground",  getForceBackground());

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());
    chunkMat->addChunk(pData->getSceneTexObjChunk(), 0);
    chunkMat->addChunk(pData->getBackgroundTexObjChunk(), 1);
    chunkMat->addChunk(shaderChunk);

    pData->setLuminanceMapShader(shaderChunk);
    pData->setLuminanceMapMaterial(chunkMat);
}

void HDR2Stage::setupAdaptLuminanceMaterial(HDR2StageData* pData)
{
    pData->setCurrentTime(getTimeStampMsecs(getTimeStamp()));
    pData->setLastTime   (pData->getCurrentTime());

    SimpleSHLChunkUnrecPtr shaderChunk = genAdaptLuminanceShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("InputTex1", 1);
    shaderChunk->addUniformVariable("TimeDelta", 0.01f);
    shaderChunk->addUniformVariable("AdjustLuminance", getAdjustLuminance());
    shaderChunk->addUniformBlock("HDRShaderDataBlock", 0);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());

    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(
        !pData->getCurrentAdaptLuminanceIdx()), 0);

    chunkMat->addChunk(pData->getLuminanceTexObjChunk(), 1);

    chunkMat->addChunk(pData->getHdrShaderData(), 0);
    chunkMat->addChunk(shaderChunk);

    pData->setAdaptLuminanceShader(shaderChunk);
    pData->setAdaptLuminanceMaterial(chunkMat);
}

void HDR2Stage::setupThresholdMaterial(HDR2StageData* pData)
{
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth,iPixelHeight));

    if (getMipmapLevel() >= 0)
        levels = getMipmapLevel();

    SimpleSHLChunkUnrecPtr shaderChunk = genThresholdShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("InputTex1", 1);
    shaderChunk->addUniformVariable("InputTex2", 2);
    shaderChunk->addUniformVariable("Level", static_cast<float>(levels));
    shaderChunk->addUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());
    shaderChunk->addUniformVariable("FilterBackground", !getBloomBackground());
    shaderChunk->addUniformBlock("HDRShaderDataBlock", 0);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());

    chunkMat->addChunk(pData->getSceneTexObjChunk(), 0);
    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 1);
    chunkMat->addChunk(pData->getDepthTexObjChunk(), 2);

    chunkMat->addChunk(pData->getHdrShaderData(), 0);

    chunkMat->addChunk(shaderChunk);

    pData->setThresholdShader(shaderChunk);
    pData->setThresholdMaterial(chunkMat);
}

void HDR2Stage::setupScaleMaterial(HDR2StageData* pData)
{
    SimpleSHLChunkUnrecPtr shaderChunk = genScaleShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    pData->setScaleShader(shaderChunk);

    // 0 : down scale /2
    {
        ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
        chunkMat->addChunk(pData->getSharedMaterialChunk());
        chunkMat->addChunk(pData->getThresholdTexObjChunk(), 0);
        chunkMat->addChunk(shaderChunk);
        
        pData->pushToScaleMaterial(chunkMat);
    }

    // 1 : down scale /4
    {
        ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
        chunkMat->addChunk(pData->getSharedMaterialChunk());
        chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
        chunkMat->addChunk(shaderChunk);
        
        pData->pushToScaleMaterial(chunkMat);
    }

    // 2 : down scale /8
    {
        ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
        chunkMat->addChunk(pData->getSharedMaterialChunk());
        chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
        chunkMat->addChunk(shaderChunk);
        
        pData->pushToScaleMaterial(chunkMat);
    }

    // 3 : up scale / 4
    {
        ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
        chunkMat->addChunk(pData->getSharedMaterialChunk());
        chunkMat->addChunk(pData->getBlurVertTexObjChunk(), 0);
        chunkMat->addChunk(shaderChunk);
        
        pData->pushToScaleMaterial(chunkMat);
    }

    // 4 : up scale / 2
    {
        ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
        chunkMat->addChunk(pData->getSharedMaterialChunk());
        chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
        chunkMat->addChunk(shaderChunk);
        
        pData->pushToScaleMaterial(chunkMat);
    }
}

void HDR2Stage::setupBlurHorizMaterial(HDR2StageData* pData)
{
    SimpleSHLChunkUnrecPtr shaderChunk = genBloomBlurShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("Direction", Vec2f(1.f,0.f));
    shaderChunk->addUniformBlock("HDRShaderDataBlock", 0);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());
    chunkMat->addChunk(pData->getBlurVertTexObjChunk(), 0);
    chunkMat->addChunk(pData->getHdrShaderData(), 0);
    chunkMat->addChunk(shaderChunk);

    pData->setBlurHorizShader(shaderChunk);
    pData->setBlurHorizMaterial(chunkMat);
}

void HDR2Stage::setupBlurVertMaterial(HDR2StageData* pData)
{
    SimpleSHLChunkUnrecPtr shaderChunk = genBloomBlurShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("Direction", Vec2f(0.f, 1.f));
    shaderChunk->addUniformBlock("HDRShaderDataBlock", 0);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());
    chunkMat->addChunk(pData->getBlurHorizTexObjChunk(), 0);
    chunkMat->addChunk(pData->getHdrShaderData(), 0);
    chunkMat->addChunk(shaderChunk);

    pData->setBlurVertShader(shaderChunk);
    pData->setBlurVertMaterial(chunkMat);
}

void HDR2Stage::setupCompositeMaterial(HDR2StageData* pData)
{
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth,iPixelHeight));

    if (getMipmapLevel() >= 0)
        levels = getMipmapLevel();

    SimpleSHLChunkUnrecPtr shaderChunk = genCompositeShader();
    shaderChunk->addUniformVariable("InputTex0", 0);        // scene
    shaderChunk->addUniformVariable("InputTex1", 1);        // adapted luminance

    if (getPerformBloom())
        shaderChunk->addUniformVariable("InputTex2", 2);    // bloom

    shaderChunk->addUniformVariable("InputTex3", 3);        // background
    shaderChunk->addUniformVariable("InputTex4", 4);        // depth
    shaderChunk->addUniformVariable("ForceBackground", getForceBackground());

    shaderChunk->addUniformVariable("Level", static_cast<float>(levels));
    shaderChunk->addUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());
    shaderChunk->addUniformBlock("HDRShaderDataBlock", 0);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());
    chunkMat->addChunk(pData->getSceneTexObjChunk     (), 0);
    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 1);

    if (getPerformBloom())
    {
        chunkMat->addChunk(pData->getScaleTexObjChunk     (0), 2);
    }

    chunkMat->addChunk(pData->getBackgroundTexObjChunk(), 3);
    chunkMat->addChunk(pData->getDepthTexObjChunk     (), 4);
    chunkMat->addChunk(shaderChunk);
    chunkMat->addChunk(pData->getHdrShaderData(), 0);

    pData->setCompositeShader(shaderChunk);
    pData->setCompositeMaterial(chunkMat);
}

void HDR2Stage::setupFinalScreenMaterial(HDR2StageData* pData)
{
    SimpleSHLChunkUnrecPtr shaderChunk = genFinalScreenShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("InputTex1", 1);
    shaderChunk->addUniformVariable("CarryDepth", getCarryDepth());
    shaderChunk->addUniformVariable("PerformDithering", getPerformDithering());
    shaderChunk->addUniformVariable("LinearizeDepth", getTarget() == LINEARIZED_DEPTH_TEXTURE);
    shaderChunk->addUniformVariable("zNear", pData->getZNear());
    shaderChunk->addUniformVariable("zFar",  pData->getZFar());
    
    shaderChunk->addUniformVariable("Gamma",         getGamma());
    shaderChunk->addUniformVariable("ApplyGamma",    getApplyGamma());
    shaderChunk->addUniformVariable("AccurateGamma", getAccurateGamma());

    shaderChunk->addUniformVariable("ShadowLift",      getAdjustedShadowLift());
    shaderChunk->addUniformVariable("InvMidtoneGamma", getAdjustedInvMidtoneGamma());
    shaderChunk->addUniformVariable("HighlightGain",   getAdjustedHighlightGain());

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();

    chunkMat->addChunk(shaderChunk);
    chunkMat->addChunk(pData->getSharedMaterialChunk());

    DepthChunkUnrecPtr depthChunk = DepthChunk::createLocal();

    pData->setFinalScreenMaterialDepthChunk(depthChunk);

    depthChunk->setFunc    (GL_ALWAYS);
    depthChunk->setEnable  (true);
    depthChunk->setReadOnly(false);

    chunkMat->addChunk(depthChunk);

    switch (getTarget())
    {
        case BACKGROUND_TEXTURE:
            chunkMat->addChunk(pData->getBackgroundTexObjChunk(), 0);
            break;
        case SCENE_TEXTURE:
            chunkMat->addChunk(pData->getSceneTexObjChunk(), 0);
            break;
        case LUMINANCE_TEXTURE:
            chunkMat->addChunk(pData->getLuminanceTexObjChunk(), 0);
            break;
        case ADAPTED_LUMINANCE_TEXTURE:
            chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 0);
            break;
        case THRESHOLD_TEXTURE:
            if (getPerformBloom())
                chunkMat->addChunk(pData->getThresholdTexObjChunk(), 0);
            else
                chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case BLURRED_TEXTURE:
            if (getPerformBloom())
                chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            else
                chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case COMPOSITE_TEXTURE:
            chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case EXPOSURE_TEXTURE:
            chunkMat->addChunk(pData->getExposureTexObjChunk(), 0);
            break;
        case DEPTH_TEXTURE:
            chunkMat->addChunk(pData->getDepthTexObjChunk(), 0);
            break;
        case LINEARIZED_DEPTH_TEXTURE:
            chunkMat->addChunk(pData->getDepthTexObjChunk(), 0);
            break;

        case DOWN_SCALED_0:
            chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            break;
        case DOWN_SCALED_1:
            chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
            break;
        case DOWN_SCALED_2:
            chunkMat->addChunk(pData->getScaleTexObjChunk(2), 0);
            break;
        case BLUR_TEXTURE:
            chunkMat->addChunk(pData->getScaleTexObjChunk(2), 0);
            break;
        case UPSCALED_SCALED_0:
            chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
            break;
        case UPSCALED_SCALED_1:
            chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            break;
    }

    chunkMat->addChunk(pData->getDepthTexObjChunk(), 1);

    pData->setFinalScreenShader(shaderChunk);
    pData->setFinalScreenMaterial(chunkMat);
}

void HDR2Stage::updateLuminanceMapMaterial(HDR2StageData* pData)
{
    SimpleSHLChunk* shaderChunk = pData->getLuminanceMapShader();
    shaderChunk->updateUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());
    shaderChunk->updateUniformVariable("ForceBackground",  getForceBackground());
}

void HDR2Stage::updateAdaptLuminanceMaterial(HDR2StageData* pData)
{
    pData->setCurrentTime(getTimeStampMsecs(getTimeStamp()));
    Real32 dt = pData->getTimeDeltaInSeconds();
    pData->setLastTime(pData->getCurrentTime());

    SimpleSHLChunk* shaderChunk = pData->getAdaptLuminanceShader();
    shaderChunk->updateUniformVariable("TimeDelta", dt);
    shaderChunk->updateUniformVariable("AdjustLuminance", getAdjustLuminance());

    ChunkMaterial* chunkMat = pData->getAdaptLuminanceMaterial();

    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(!pData->getCurrentAdaptLuminanceIdx()), 0);
}

void HDR2Stage::updateThresholdMaterial(HDR2StageData* pData)
{
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth,iPixelHeight));

    if (getMipmapLevel() >= 0)
        levels = getMipmapLevel();

    SimpleSHLChunk* shaderChunk = pData->getThresholdShader();
    shaderChunk->updateUniformVariable("Level", static_cast<float>(levels));
    shaderChunk->updateUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());
    shaderChunk->updateUniformVariable("FilterBackground", !getBloomBackground());

    ChunkMaterial* chunkMat = pData->getThresholdMaterial();

    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 1);
}

void HDR2Stage::updateScaleMaterial(HDR2StageData* pData)
{
}

void HDR2Stage::updateBlurHorizMaterial(HDR2StageData* pData)
{
}

void HDR2Stage::updateBlurVertMaterial(HDR2StageData* pData)
{
}

void HDR2Stage::updateCompositeMaterial(HDR2StageData* pData)
{
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth,iPixelHeight));

    if (getMipmapLevel() >= 0)
        levels = getMipmapLevel();

    SimpleSHLChunk* shaderChunk = pData->getCompositeShader();

    shaderChunk->updateUniformVariable("ForceBackground",  getForceBackground());
    shaderChunk->updateUniformVariable("Level", static_cast<float>(levels));
    shaderChunk->updateUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());

    ChunkMaterial* chunkMat = pData->getCompositeMaterial();

    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 1);
}

void HDR2Stage::updateFinalScreenMaterial(HDR2StageData* pData)
{
    SimpleSHLChunk* shaderChunk = pData->getFinalScreenShader();

    shaderChunk->updateUniformVariable("CarryDepth", getCarryDepth());
    shaderChunk->updateUniformVariable("PerformDithering", getPerformDithering());
    shaderChunk->updateUniformVariable("LinearizeDepth", getTarget() == LINEARIZED_DEPTH_TEXTURE);
    shaderChunk->updateUniformVariable("zNear", pData->getZNear());
    shaderChunk->updateUniformVariable("zFar",  pData->getZFar());

    shaderChunk->updateUniformVariable("Gamma",         getGamma());
    shaderChunk->updateUniformVariable("ApplyGamma",    getApplyGamma());
    shaderChunk->updateUniformVariable("AccurateGamma", getAccurateGamma());

    shaderChunk->updateUniformVariable("ShadowLift",      getAdjustedShadowLift());
    shaderChunk->updateUniformVariable("InvMidtoneGamma", getAdjustedInvMidtoneGamma());
    shaderChunk->updateUniformVariable("HighlightGain",   getAdjustedHighlightGain());

    ChunkMaterial* chunkMat = pData->getFinalScreenMaterial();

    DepthChunk* depthChunk = pData->getFinalScreenMaterialDepthChunk();
    if (depthChunk)
    {
        depthChunk->setFunc   (GL_ALWAYS);
        depthChunk->setEnable (true);
        depthChunk->setReadOnly(false);
    }

    switch (getTarget())
    {
        case BACKGROUND_TEXTURE:
            chunkMat->addChunk(pData->getBackgroundTexObjChunk(), 0);
            break;
        case SCENE_TEXTURE:
            chunkMat->addChunk(pData->getSceneTexObjChunk(), 0);
            break;
        case LUMINANCE_TEXTURE:
            chunkMat->addChunk(pData->getLuminanceTexObjChunk(), 0);
            break;
        case ADAPTED_LUMINANCE_TEXTURE:
            chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 0);
            break;
        case THRESHOLD_TEXTURE:
            if (getPerformBloom())
                chunkMat->addChunk(pData->getThresholdTexObjChunk(), 0);
            else
                chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case BLURRED_TEXTURE:
            if (getPerformBloom())
                chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            else
                chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case COMPOSITE_TEXTURE:
            chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case EXPOSURE_TEXTURE:
            chunkMat->addChunk(pData->getExposureTexObjChunk(), 0);
            break;
        case DEPTH_TEXTURE:
            chunkMat->addChunk(pData->getDepthTexObjChunk(), 0);
            break;
        case LINEARIZED_DEPTH_TEXTURE:
            chunkMat->addChunk(pData->getDepthTexObjChunk(), 0);
            break;

        case DOWN_SCALED_0:
            chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            break;
        case DOWN_SCALED_1:
            chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
            break;
        case DOWN_SCALED_2:
            chunkMat->addChunk(pData->getScaleTexObjChunk(2), 0);
            break;
        case BLUR_TEXTURE:
            chunkMat->addChunk(pData->getScaleTexObjChunk(2), 0);
            break;
        case UPSCALED_SCALED_0:
            chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
            break;
        case UPSCALED_SCALED_1:
            chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            break;
    }
}

/*---------------------------- postProcess --------------------------------*/

void HDR2Stage::postProcess(DrawEnv *pEnv)
{
    UInt32  uiActiveFBO = pEnv->getActiveFBO();
    Window* win         = pEnv->getWindow();

    HDR2StageData* pData = pEnv->getData<HDR2StageData*>(_iDataSlotId);
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

    calcAvgLuminance(pEnv, pData);

    if (getPerformBloom())
        bloomBlur(pEnv, pData);

    composite(pEnv, pData);

    if(uiActiveFBO != 0)
    {
        FrameBufferObject::activateFBOById(pEnv, uiActiveFBO);
    }

    drawToFinalTarget(pEnv, pData);

    pEnv->deactivateState();

    glPopMatrix();

    UInt32 currIdx = pData->getCurrentAdaptLuminanceIdx();
    pData->setCurrentAdaptLuminanceIdx(!currIdx);

#if 0
    write_read_back_images(pData);
#endif
}

void HDR2Stage::calcAvgLuminance(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // render luminance map
    //
    FrameBufferObject* pLuminanceRenderTarget = pData->getLuminanceRenderTarget();
    ChunkMaterial*     pLuminanceMapMaterial  = pData->getLuminanceMapMaterial();

    pLuminanceRenderTarget->activate(pEnv);

    State* pLuminanceState = pLuminanceMapMaterial->getState();

    pEnv->activateState(pLuminanceState, NULL);
    
    this->renderQuad();

    pLuminanceRenderTarget->deactivate(pEnv);

    //
    // calculate average log luminance map with mipmap generation
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    Int32 w = iPixelWidth; //Int32 w = osgNextPower2(iPixelWidth);
    Int32 h = iPixelHeight;//Int32 h = osgNextPower2(iPixelHeight);

    glViewport(0, 0, w, h);

    UInt32 idx = pData->getCurrentAdaptLuminanceIdx();

    FrameBufferObject* pAdaptLuminanceRenderTarget = pData->getAdaptLuminanceRenderTarget(idx);
    ChunkMaterial*     pAdaptLuminanceMapMaterial  = pData->getAdaptLuminanceMaterial();

    pAdaptLuminanceRenderTarget->activate(pEnv);

    State* pAdaptLuminanceState = pAdaptLuminanceMapMaterial->getState();

    pEnv->activateState(pAdaptLuminanceState, NULL);
    
    this->renderQuad();

    pAdaptLuminanceRenderTarget->deactivate(pEnv);

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Run threshold shader on scene render result
    //
    FrameBufferObject* pThresholdRenderTarget = pData->getThresholdRenderTarget();
    ChunkMaterial*     pThresholdMaterial     = pData->getThresholdMaterial();

    pThresholdRenderTarget->activate(pEnv);

    State* pThresholdState = pThresholdMaterial->getState();

    pEnv->activateState(pThresholdState, NULL);

    this->renderQuad();

    pThresholdRenderTarget->deactivate(pEnv);

    switch (getTarget())
    {
        case DOWN_SCALED_0:
            bloomBlur_DOWN_SCALED_0(pEnv, pData);
            return;
        case DOWN_SCALED_1:
            bloomBlur_DOWN_SCALED_1(pEnv, pData);
            return;
        case DOWN_SCALED_2:
            bloomBlur_DOWN_SCALED_2(pEnv, pData);
            return;
        case BLUR_TEXTURE:
            bloomBlur_BLUR_TEXTURE(pEnv, pData);
            return;
        case UPSCALED_SCALED_0:
            bloomBlur_UP_SCALED_0(pEnv, pData);
            return;
        case UPSCALED_SCALED_1:
            bloomBlur_UP_SCALED_1(pEnv, pData);
            return;
    }

    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 3; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    //
    // Blur downscaled result
    //
    FrameBufferObject* pBlurHorizRenderTarget  = pData->getBlurHorizRenderTarget();
    FrameBufferObject* pBlurVertRenderTarget   = pData->getBlurVertRenderTarget();

    ChunkMaterial*     pBlurHorizMaterial = pData->getBlurHorizMaterial();
    ChunkMaterial*     pBlurVertMaterial  = pData->getBlurVertMaterial();

    for (Int32 i = 0; i < 4; ++i)
    {
        //
        // Horizontal pass: pData->getBlurVertTexObjChunk() is equal to pData->getScaleTexObjChunk(2) by design!
        //
        pBlurHorizRenderTarget->activate(pEnv);

        State* pBlurHorizState = pBlurHorizMaterial->getState();

        pEnv->activateState(pBlurHorizState, NULL);
    
        this->renderQuad();

        pBlurHorizRenderTarget->deactivate(pEnv);

        //
        // Vertical pass
        //
        pBlurVertRenderTarget->activate(pEnv);

        State* pBlurVertState = pBlurVertMaterial->getState();

        pEnv->activateState(pBlurVertState, NULL);
    
        this->renderQuad();

        pBlurVertRenderTarget->deactivate(pEnv);
    }

    //
    // Upscale blurred result
    //
    for (Int32 i = 1; i >= 0; --i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i+2);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

//########################################################################################################################
void HDR2Stage::bloomBlur_DOWN_SCALED_0(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 1; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur_DOWN_SCALED_1(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 2; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur_DOWN_SCALED_2(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 3; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur_BLUR_TEXTURE(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 3; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    //
    // Blur downscaled result
    //
    FrameBufferObject* pBlurHorizRenderTarget  = pData->getBlurHorizRenderTarget();
    FrameBufferObject* pBlurVertRenderTarget   = pData->getBlurVertRenderTarget();

    ChunkMaterial*     pBlurHorizMaterial = pData->getBlurHorizMaterial();
    ChunkMaterial*     pBlurVertMaterial  = pData->getBlurVertMaterial();

    for (Int32 i = 0; i < 4; ++i)
    {
        //
        // Horizontal pass: pData->getBlurVertTexObjChunk() is equal to pData->getScaleTexObjChunk(2) by design!
        //
        pBlurHorizRenderTarget->activate(pEnv);

        State* pBlurHorizState = pBlurHorizMaterial->getState();

        pEnv->activateState(pBlurHorizState, NULL);
    
        this->renderQuad();

        pBlurHorizRenderTarget->deactivate(pEnv);

        //
        // Vertical pass
        //
        pBlurVertRenderTarget->activate(pEnv);

        State* pBlurVertState = pBlurVertMaterial->getState();

        pEnv->activateState(pBlurVertState, NULL);
    
        this->renderQuad();

        pBlurVertRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur_UP_SCALED_0(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 3; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    //
    // Blur downscaled result
    //
    FrameBufferObject* pBlurHorizRenderTarget  = pData->getBlurHorizRenderTarget();
    FrameBufferObject* pBlurVertRenderTarget   = pData->getBlurVertRenderTarget();

    ChunkMaterial*     pBlurHorizMaterial = pData->getBlurHorizMaterial();
    ChunkMaterial*     pBlurVertMaterial  = pData->getBlurVertMaterial();

    for (Int32 i = 0; i < 4; ++i)
    {
        //
        // Horizontal pass: pData->getBlurVertTexObjChunk() is equal to pData->getScaleTexObjChunk(2) by design!
        //
        pBlurHorizRenderTarget->activate(pEnv);

        State* pBlurHorizState = pBlurHorizMaterial->getState();

        pEnv->activateState(pBlurHorizState, NULL);
    
        this->renderQuad();

        pBlurHorizRenderTarget->deactivate(pEnv);

        //
        // Vertical pass
        //
        pBlurVertRenderTarget->activate(pEnv);

        State* pBlurVertState = pBlurVertMaterial->getState();

        pEnv->activateState(pBlurVertState, NULL);
    
        this->renderQuad();

        pBlurVertRenderTarget->deactivate(pEnv);
    }

    //
    // Upscale blurred result
    //
    for (Int32 i = 1; i >= 1; --i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i+2);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur_UP_SCALED_1(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 3; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(
            iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    //
    // Blur downscaled result
    //
    FrameBufferObject* pBlurHorizRenderTarget  = pData->getBlurHorizRenderTarget();
    FrameBufferObject* pBlurVertRenderTarget   = pData->getBlurVertRenderTarget();

    ChunkMaterial*     pBlurHorizMaterial = pData->getBlurHorizMaterial();
    ChunkMaterial*     pBlurVertMaterial  = pData->getBlurVertMaterial();

    for (Int32 i = 0; i < 4; ++i)
    {
        //
        // Horizontal pass: pData->getBlurVertTexObjChunk() is equal to pData->getScaleTexObjChunk(2) by design!
        //
        pBlurHorizRenderTarget->activate(pEnv);

        State* pBlurHorizState = pBlurHorizMaterial->getState();

        pEnv->activateState(pBlurHorizState, NULL);
    
        this->renderQuad();

        pBlurHorizRenderTarget->deactivate(pEnv);

        //
        // Vertical pass
        //
        pBlurVertRenderTarget->activate(pEnv);

        State* pBlurVertState = pBlurVertMaterial->getState();

        pEnv->activateState(pBlurVertState, NULL);
    
        this->renderQuad();

        pBlurVertRenderTarget->deactivate(pEnv);
    }

    //
    // Upscale blurred result
    //
    for (Int32 i = 1; i >= 0; --i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i+2);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

/*-------------------------------- sRGB -----------------------------------*/

Color3f HDR2Stage::sRGBToLinear(const Color3f& c) const
{
    Real32 r = c.red();
    Real32 g = c.green();
    Real32 b = c.blue();

    r = sRGBToLinear(r);
    g = sRGBToLinear(g);
    b = sRGBToLinear(b);

    return Color3f(r,g,b);
}

Real32 HDR2Stage::sRGBToLinear(Real32 x) const
{
    return (x <= 0.04045) ? x / 12.92 : osgPow((x + 0.055) / 1.055, 2.4);
}

//########################################################################################################################

void HDR2Stage::composite(DrawEnv* pEnv, HDR2StageData* pData)
{
    FrameBufferObject* pCompositeRenderTarget = pData->getCompositeRenderTarget();
    ChunkMaterial*     pCompositeMaterial     = pData->getCompositeMaterial();

    pCompositeRenderTarget->activate(pEnv);

    State* pCompositeState = pCompositeMaterial->getState();

    pEnv->activateState(pCompositeState, NULL);

    this->renderQuad();

    pCompositeRenderTarget->deactivate(pEnv);
}

void HDR2Stage::drawToFinalTarget(DrawEnv* pEnv, HDR2StageData* pData)
{
    ChunkMaterial* pFinalScreenMaterial = pData->getFinalScreenMaterial();

    State* pFinalScreenState = pFinalScreenMaterial->getState();

    pEnv->activateState(pFinalScreenState, NULL);

    glViewport(pEnv->getPixelLeft  (), 
               pEnv->getPixelBottom(),
               pEnv->getPixelWidth (),
               pEnv->getPixelHeight());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    this->renderQuad();
}

/*-------------------------- Shader Toolbox -------------------------------*/

void HDR2Stage::genBlockHDRShaderData(std::stringstream& ost)
{
    ost << "layout (std140) uniform HDRShaderDataBlock"                                 << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float BloomThreshold;"                                                  << std::endl;
    ost << "    float BloomMagnitude;"                                                  << std::endl;
    ost << "    int   ToneMapTechnique;"                                                << std::endl;
    ost << "    float Exposure;"                                                        << std::endl;
    ost << "    float KeyValue;"                                                        << std::endl;
    ost << "    float ApertureFNumber;"                                                 << std::endl;
    ost << "    float ShutterSpeedValue;"                                               << std::endl;
    ost << "    float ISO;"                                                             << std::endl;
    ost << "    int   AutoExposure;"                                                    << std::endl;
    ost << "    float WhiteLevel;"                                                      << std::endl;
    ost << "    float ShoulderStrength;"                                                << std::endl;
    ost << "    float LinearStrength;"                                                  << std::endl;
    ost << "    float LinearAngle;"                                                     << std::endl;
    ost << "    float ToeStrength;"                                                     << std::endl;
    ost << "    float ToeNumerator;"                                                    << std::endl;
    ost << "    float ToeDenominator;"                                                  << std::endl;
    ost << "    float LinearWhite;"                                                     << std::endl;
    ost << "    float LumSaturation;"                                                   << std::endl;
    ost << "    vec3  FilterColor;"                                                     << std::endl;
    ost << "    float Contrast;"                                                        << std::endl;
    ost << "    float Bias;"                                                            << std::endl;
    ost << "    float Tau;"                                                             << std::endl;
    ost << "    int   nTaps;"                                                           << std::endl;
    ost << "    float Sigma;"                                                           << std::endl;
    ost << "    bool  UseLinChromInterp;"                                               << std::endl;
    ost << "} hdrShaderData;"                                                           << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetPrimaryInputColor(std::stringstream& ost)
{
    ost << "vec3 GetPrimaryInputColor(sampler2D sampler)"                               << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return texture(sampler, TexCoord).rgb;"                                 << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncCalcLuminance(std::stringstream& ost)
{
    // https://en.wikipedia.org/wiki/Talk:Relative_luminance
    // https://en.wikipedia.org/wiki/Relative_luminance
    ost << "float CalcLuminance(vec3 color)"                                            << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    if (Use_ITU_R_BT_709)"                                                  << std::endl;
    ost << "        return max(dot(color, vec3(0.2126, 0.7152, 0.0722)), 0.0001);"      << std::endl;
    ost << "    else"                                                                   << std::endl;
    ost << "        return max(dot(color, vec3(0.299, 0.587, 0.114)), 0.0001);"         << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetLastLumValue(std::stringstream& ost)
{
    ost << "float GetLastLumValue(sampler2D sampler)"                                   << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return texture(sampler, TexCoord).x;"                                   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetCurrLumValue(std::stringstream& ost)
{
    ost << "float GetCurrLumValue(sampler2D sampler)"                                   << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return texture(sampler, TexCoord).x;"                                   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncLog10(std::stringstream& ost)
{
    ost << "const float inv_log_10 = 1.0 / log(10.0);"                                  << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "float Log10(float x)"                                                       << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return inv_log_10 * log(x);"                                            << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncPow(std::stringstream& ost)
{
    ost << "vec3 Pow(vec3 x, float v)"                                                  << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return pow(x, vec3(v));"                                                << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetAvgLuminance(std::stringstream& ost)
{
    ost << "float GetAvgLuminance(sampler2D sampler)"                                   << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec2 texCoord = gl_FragCoord.xy / "                                     << std::endl;
    ost << "                       vec2(textureSize(sampler, int(Level)));"             << std::endl;
    ost << "    float avgLum  = textureLod(sampler, texCoord, Level).x;"                << std::endl;
    ost << "    return exp(avgLum);"                                                    << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetDepthValue(std::stringstream& ost)
{
    ost << "float GetDepthValue(sampler2D sampler)"                                     << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float depth = texture2D(sampler, TexCoord).x;"                          << std::endl;
    ost << "    return depth;"                                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncSaturationBasedExp(std::stringstream& ost)
{
    // https://placeholderart.wordpress.com/2014/11/16/implementing-a-physically-based-camera-understanding-exposure/
    // https://placeholderart.wordpress.com/2014/11/21/implementing-a-physically-based-camera-manual-exposure/
    ost << "float SaturationBasedExposure()"                                            << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float maxLuminance = (7800.0 / 65.0)"                                   << std::endl;
    ost << "        * (hdrShaderData.ApertureFNumber * hdrShaderData.ApertureFNumber)"  << std::endl;
    ost << "        / (hdrShaderData.ISO * hdrShaderData.ShutterSpeedValue);"           << std::endl;
    ost << "    return log2(1.0 / maxLuminance);"                                       << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncStandardOutputBasedExp(std::stringstream& ost)
{
    // https://placeholderart.wordpress.com/2014/11/16/implementing-a-physically-based-camera-understanding-exposure/
    // https://placeholderart.wordpress.com/2014/11/21/implementing-a-physically-based-camera-manual-exposure/
    ost << "float StandardOutputBasedExposure()"                                        << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float middleGrey = 0.18;"                                               << std::endl;
    ost << "    float lAvg = (1000.0 / 65.0)"                                           << std::endl;
    ost << "        * (hdrShaderData.ApertureFNumber * hdrShaderData.ApertureFNumber)"  << std::endl;
    ost << "        / (hdrShaderData.ISO * hdrShaderData.ShutterSpeedValue);"           << std::endl;
    ost << "    return log2(middleGrey / lAvg);"                                        << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncLog2Exposure(std::stringstream& ost)
{
    ost << "const int ciExposureModeManualExposure            = " << MANUAL                << ";" << std::endl;
    ost << "const int ciExposureModeManualKeyValue            = " << KEY_VALUE             << ";" << std::endl;
    ost << "const int ciExposureModeAutomatic                 = " << AUTOMATIC             << ";" << std::endl;
    ost << "const int ciExposureModeManualSaturationBased     = " << SATURATION_BASED      << ";" << std::endl;
    ost << "const int ciExposureModeManualStandardOutputBased = " << STANDARD_OUTPUT_BASED << ";" << std::endl;

    ost << ""                                                                           << std::endl;
    ost << "float Log2Exposure(in float avgLuminance)"                                  << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float exposure = 0.0f;"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    switch (hdrShaderData.AutoExposure)"                                    << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        case ciExposureModeManualExposure:"                                 << std::endl;
    ost << "        {"                                                                  << std::endl;
    ost << "            exposure = -hdrShaderData.Exposure - 0.263034406;"              << std::endl;
    ost << "        }"                                                                  << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "        case ciExposureModeManualKeyValue:"                                 << std::endl;
    ost << "        {"                                                                  << std::endl;
    ost << "            avgLuminance = max(avgLuminance, 0.00001);"                     << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "            float linearExposure = (hdrShaderData.KeyValue / avgLuminance);"<< std::endl;
    ost << "            exposure = log2(max(linearExposure, 0.0001));"                  << std::endl;
    ost << "        }"                                                                  << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "        case ciExposureModeAutomatic:"                                      << std::endl;
    ost << "        {"                                                                  << std::endl;
    ost << "            avgLuminance = max(avgLuminance, 0.00001);"                     << std::endl;
    ost << "            float keyValue = 1.03 - (2.0/(2.0 + Log10(avgLuminance+1.0)));" << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "            float linearExposure = (keyValue / avgLuminance);"              << std::endl;
    ost << "            exposure = log2(max(linearExposure, 0.0001));"                  << std::endl;
    ost << "        }"                                                                  << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "        case ciExposureModeManualSaturationBased:"                          << std::endl;
    ost << "        {"                                                                  << std::endl;
    ost << "            exposure = SaturationBasedExposure();"                          << std::endl;
    ost << "        }"                                                                  << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "        case ciExposureModeManualStandardOutputBased:"                      << std::endl;
    ost << "        {"                                                                  << std::endl;
    ost << "            exposure = StandardOutputBasedExposure();"                      << std::endl;
    ost << "        }"                                                                  << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return exposure;"                                                       << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncCalcExposedColor(std::stringstream& ost)
{
    ost << ""                                                                           << std::endl;
    ost << "vec3 CalcExposedColor("                                                     << std::endl;
    ost << "    vec3 color, float avgLuminance, float threshold)"                       << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float exposure = Log2Exposure(avgLuminance);"                           << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    exposure -= threshold;"                                                 << std::endl;
    ost << "    return max(exp2(exposure) * color, 0.0);"                               << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncColorCorrection(std::stringstream& ost)
{
    ost << "vec3 ColorCorrection(vec3 color, float pixelLuminance)"                     << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    if (hdrShaderData.UseLinChromInterp)"                                   << std::endl;
    ost << "        return ( (color / pixelLuminance - 1 ) * "                          << std::endl;
    ost << "                hdrShaderData.LumSaturation + 1 );"                         << std::endl;
    ost << "    else"                                                                   << std::endl;
    ost << "        return Pow(color/pixelLuminance, hdrShaderData.LumSaturation);"     << std::endl;
    ost << "}"                                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "vec3 SaturationCorrection(vec3 color, float pixelLuminance)"                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float a = 1.0 - hdrShaderData.LumSaturation;"                           << std::endl;
    ost << "    return mix(color, vec3(pixelLuminance), a);"                            << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncContrastCorrection(std::stringstream& ost)
{
    ost << "const vec3 logMidpoint = log2(vec3(0.18,0.18,0.18));"                       << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "vec3 ContrastCorrection(vec3 color)"                                        << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 logColor = log2(color + vec3(0.00001));"                           << std::endl;
    ost << "    vec3 adjColor = logMidpoint + (logColor - logMidpoint)"                 << std::endl;
    ost << "                        * hdrShaderData.Contrast;"                          << std::endl;
    ost << "    return max(vec3(0.0),exp2(adjColor) - vec3(0.00001));"                  << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncU2Func(std::stringstream& ost)
{
    ost << "vec3 U2Func(vec3 x)"                                                        << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float A = hdrShaderData.ShoulderStrength;"                              << std::endl;
    ost << "    float B = hdrShaderData.LinearStrength;"                                << std::endl;
    ost << "    float C = hdrShaderData.LinearAngle;"                                   << std::endl;
    ost << "    float D = hdrShaderData.ToeStrength;"                                   << std::endl;
    ost << "    float E = hdrShaderData.ToeNumerator;"                                  << std::endl;
    ost << "    float F = hdrShaderData.ToeDenominator;"                                << std::endl;
    ost << "    return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F)) - E/F;"                      << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapLogarithmic(std::stringstream& ost)
{
    ost << "vec3 ToneMapLogarithmic(vec3 color)"                                        << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float pixelLuminance      = CalcLuminance(color);"                      << std::endl;
    ost << "    float toneMappedLuminance = Log10(1 + pixelLuminance) / "               << std::endl;
    ost << "                                Log10(1 + hdrShaderData.WhiteLevel);"       << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapExponential(std::stringstream& ost)
{
    ost << "vec3 ToneMapExponential(vec3 color)"                                        << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float pixelLuminance      = CalcLuminance(color);"                      << std::endl;
    ost << "    float toneMappedLuminance = 1 - exp(-pixelLuminance / "                 << std::endl;
    ost << "                                hdrShaderData.WhiteLevel);"                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapDragoLogarithmic(std::stringstream& ost)
{
    ost << "vec3 ToneMapDragoLogarithmic(vec3 color)"                                   << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float pixelLuminance      = CalcLuminance(color);"                      << std::endl;
    ost << "    float toneMappedLuminance = Log10(1 + pixelLuminance);"                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    toneMappedLuminance /= Log10(1 + hdrShaderData.WhiteLevel);"            << std::endl;
    ost << "    toneMappedLuminance /= Log10(2 + 8 * ("                                 << std::endl;
    ost << "        pow( (pixelLuminance / hdrShaderData.WhiteLevel),"                  << std::endl;
    ost << "             Log10(hdrShaderData.Bias) / Log10(0.5))));"                    << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapReinhard(std::stringstream& ost)
{
    ost << "vec3 ToneMapReinhard(vec3 color)"                                           << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float pixelLuminance      = CalcLuminance(color);"                      << std::endl;
    ost << "    float toneMappedLuminance = pixelLuminance / (pixelLuminance + 1);"     << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapReinhardModified(std::stringstream& ost)
{
    ost << "vec3 ToneMapReinhardModified(vec3 color)"                                   << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float pixelLuminance      = CalcLuminance(color);"                      << std::endl;
    ost << "    float toneMappedLuminance = pixelLuminance * (1.0 + pixelLuminance / "  << std::endl;
    ost << "        (hdrShaderData.WhiteLevel * hdrShaderData.WhiteLevel)) / "          << std::endl;
    ost << "        (1.0 + pixelLuminance);"                                            << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapFilmicALU(std::stringstream& ost)
{
    ost << "vec3 ToneMapFilmicALU(vec3 color)"                                          << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    color = max(vec3(0), color - 0.004);"                                   << std::endl;
    ost << "    color = (color * (6.2 * color + 0.5)) / "                               << std::endl;
    ost << "            (color * (6.2 * color + 1.7)+ 0.06);"                           << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    // result color is sRGB, i.e. has 1/2.2 baked in"                       << std::endl;
    ost << "    color = AccurateSRGBToLinear(color);"                                   << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    float pixelLuminance = CalcLuminance(color);"                           << std::endl;
    ost << "    color = SaturationCorrection(color, pixelLuminance);"                   << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return color;"                                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapFilmicU2(std::stringstream& ost)
{
    ost << "vec3 ToneMapFilmicU2(vec3 color)"                                           << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 numerator   = U2Func(color);"                                      << std::endl;
    ost << "    vec3 denominator = U2Func(vec3(hdrShaderData.LinearWhite));"            << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    color = numerator / denominator;"                                       << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    float pixelLuminance = CalcLuminance(color);"                           << std::endl;
    ost << "    color = SaturationCorrection(color, pixelLuminance);"                   << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return color;"                                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapFilmicACES(std::stringstream& ost)
{
    // sRGB => XYZ => D65_2_D60 => AP1 => RRT_SAT
    ost << "const mat3 matACESIn = mat3("                                               << std::endl;
    ost << "    0.59719, 0.07600, 0.02840,"                                             << std::endl;
    ost << "    0.35458, 0.90834, 0.13383,"                                             << std::endl;
    ost << "    0.04823, 0.01566, 0.83777);"                                            << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "const mat3 matACESOut = mat3("                                              << std::endl;
    ost << "     1.60475, -0.10208, -0.00327,"                                          << std::endl;
    ost << "    -0.53108,  1.10813, -0.07276,"                                          << std::endl;
    ost << "    -0.07367, -0.00605,  1.07602);"                                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "vec3 ToneMapFilmicACES(vec3 color)"                                         << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    color = 1.8 * matACESIn * color;"                                       << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    vec3 a = color * (color + 0.0245786) - 0.000090537;"                    << std::endl;
    ost << "    vec3 b = color * (0.983729 * color + 0.4329510) + 0.238081;"            << std::endl;
    ost << "    color = a / b;"                                                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    color = matACESOut * color;"                                            << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    float pixelLuminance = CalcLuminance(color);"                           << std::endl;
    ost << "    color = SaturationCorrection(color, pixelLuminance);"                   << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return color;"                                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapFilmicHejl2015(std::stringstream& ost)
{
    ost << "vec3 ToneMapFilmicHejl2015(vec3 color)"                                     << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec4 vh = vec4(color, hdrShaderData.WhiteLevel);"                       << std::endl;
    ost << "    vec4 va = (1.435 * vh) + 0.05;"                                         << std::endl;
    ost << "    vec4 vf = ((vh * va + 0.004) / ((vh * (va + 0.55) + 0.0491))) - 0.0821;"<< std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    color = vf.xyz / vf.www;"                                               << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    float pixelLuminance = CalcLuminance(color);"                           << std::endl;
    ost << "    color = SaturationCorrection(color, pixelLuminance);"                   << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return color;"                                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapFilmicACES2(std::stringstream& ost)
{
    ost << "vec3 ToneMapFilmicACES2(vec3 color)"                                        << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 a = color * ( 2.51 * color + 0.03 );"                              << std::endl;
    ost << "    vec3 b = color * ( 2.43 * color + 0.59 ) + 0.14;"                       << std::endl;
    ost << "    color = a / b;"                                                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    float pixelLuminance = CalcLuminance(color);"                           << std::endl;
    ost << "    color = SaturationCorrection(color, pixelLuminance);"                   << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return color;"                                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMap(std::stringstream& ost)
{
    ost << "const int ciNoToneMapping               = " << NO_TONE_MAPPING                << ";" << std::endl;
    ost << "const int ciLogarithmicToneMapping      = " << LOGARITHMIC_TONE_MAPPING       << ";" << std::endl;
    ost << "const int ciExponentialToneMapping      = " << EXPONENTIAL_TONE_MAPPING       << ";" << std::endl;
    ost << "const int ciDragoLogarithmicToneMapping = " << DRAGO_LOGARITHMIC_TONE_MAPPING << ";" << std::endl;
    ost << "const int ciReinhardToneMapping         = " << REINHARD_TONE_MAPPING          << ";" << std::endl;
    ost << "const int ciReinhardModifiedToneMapping = " << REINHARD_MODIFIED_TONE_MAPPING << ";" << std::endl;
    ost << "const int ciFilmicHableToneMapping      = " << FILMIC_HABLE_TONE_MAPPING      << ";" << std::endl;
    ost << "const int ciFilmicUncharted2ToneMapping = " << FILMIC_UNCHARTED2_TONE_MAPPING << ";" << std::endl;
    ost << "const int ciFilmicAcesToneMapping       = " << FILMIC_ACES_TONE_MAPPING       << ";" << std::endl;
    ost << "const int ciFilmicHej2015ToneMapping    = " << FILMIC_HEJ2015_TONE_MAPPING    << ";" << std::endl;
    ost << "const int ciFilmicAces2ToneMapping      = " << FILMIC_ACES_2_TONE_MAPPING     << ";" << std::endl;

    ost << ""                                                                           << std::endl;
    ost << "vec3 ToneMap("                                                              << std::endl;
    ost << "    vec3 color, float avgLuminance, float threshold)"                       << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    color = CalcExposedColor(color, avgLuminance, threshold);"              << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    switch (hdrShaderData.ToneMapTechnique)"                                << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "    case ciNoToneMapping:"                                                  << std::endl;
    ost << "        // Do nothing!"                                                     << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    case ciLogarithmicToneMapping:"                                         << std::endl;
    ost << "        color = ToneMapLogarithmic(color);"                                 << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    case ciExponentialToneMapping:"                                         << std::endl;
    ost << "        color = ToneMapExponential(color);"                                 << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    case ciDragoLogarithmicToneMapping:"                                    << std::endl;
    ost << "        color = ToneMapDragoLogarithmic(color);"                            << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    case ciReinhardToneMapping:"                                            << std::endl;
    ost << "        color = ToneMapReinhard(color);"                                    << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    case ciReinhardModifiedToneMapping:"                                    << std::endl;
    ost << "        color = ToneMapReinhardModified(color);"                            << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    case ciFilmicHableToneMapping:"                                         << std::endl;
    ost << "        color = ToneMapFilmicALU(color);"                                   << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    case ciFilmicUncharted2ToneMapping:"                                    << std::endl;
    ost << "        color = ToneMapFilmicU2(color);"                                    << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    case ciFilmicAcesToneMapping:"                                          << std::endl;
    ost << "        color = ToneMapFilmicACES(color);"                                  << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    case ciFilmicHej2015ToneMapping:"                                       << std::endl;
    ost << "        color = ToneMapFilmicHejl2015(color);"                              << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    case ciFilmicAces2ToneMapping:"                                         << std::endl;
    ost << "        color = ToneMapFilmicACES2(color);"                                 << std::endl;
    ost << "        break;"                                                             << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    color *= hdrShaderData.FilterColor;"                                    << std::endl;
    ost << "    color = ContrastCorrection(color);"                                     << std::endl;
    ost << "    return color;"                                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncCalcGaussianWeight(std::stringstream& ost)
{
    ost << "float CalcGaussianWeight(int sampleDist, float sigma)"                      << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float twoSigma2 = 2.0 * sigma * sigma;"                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    float g = 1.0 / sqrt(3.1415926 * twoSigma2);"                           << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return (g * exp(-(sampleDist * sampleDist) / twoSigma2));"              << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetBloomColor(std::stringstream& ost)
{
    ost << "vec3 GetBloomColor(sampler2D sampler)"                                      << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return texture(sampler, TexCoord).rgb;"                                 << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGammaCorrection(std::stringstream& ost)
{
    //
    // Gamma correction functions
    //
    ost << "vec3 ApproximationSRGBToLinear(vec3 sRGBCol, float gamma)"                  << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return Pow(sRGBCol, gamma);"                                            << std::endl;
    ost << "}"                                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "vec3 ApproximationLinearToSRGB(vec3 linearCol, float gamma)"                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return Pow(linearCol, 1.0 / gamma);"                                    << std::endl;
    ost << "}"                                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "vec3 AccurateSRGBToLinear(vec3 v)"                                          << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 t = step(vec3(0.04045), v.rgb);"                                   << std::endl;
    ost << "    return mix(v.rgb/12.92, Pow((v.rgb+vec3(0.055))/1.055, 2.4), t);"       << std::endl;
    ost << "}"                                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "vec3 AccurateLinearToSRGB(vec3 v)"                                          << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 t = step(vec3(0.00313067),v.rgb);"                                 << std::endl;
    ost << "    return mix(v.rgb*12.92, 1.055*Pow(v.rgb, 1.0/2.4)-0.055, t);"           << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}



void HDR2Stage::genFuncLiftGammaGainCorrection(std::stringstream& ost)
{
    ost << "vec3 LiftGammaGainCorrection(vec3 sRGB)"                                    << std::endl;
    ost << "{"                                                                          << std::endl;
    //ost << "    sRGB = clamp(pow(sRGB, InvMidtoneGamma), 0.0, 1.0);"                    << std::endl;
    //ost << "    return HighlightGain * sRGB + ShadowLift * (vec3(1.0) - sRGB);"         << std::endl;
    ost << "    sRGB = sRGB*(1.5 - 0.5*ShadowLift) + 0.5*ShadowLift - 0.5;"             << std::endl;
    ost << "    sRGB = pow(HighlightGain * sRGB, InvMidtoneGamma);"                     << std::endl;
    ost << "    return clamp(sRGB, 0.0, 1.0);"                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncDithering(std::stringstream& ost)
{
    ost << "#define PI 3.14159265359"                                                   << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "float rand(const in vec2 uv)"                                               << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    const float a = 12.9898, b = 78.233, c = 43758.5453;"                   << std::endl;
    ost << "    float dt = dot( uv.xy, vec2( a,b ) ), sn = mod( dt, PI );"              << std::endl;
    ost << "    return fract(sin(sn) * c);"                                             << std::endl;
    ost << "}"                                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "vec3 DitherColor(vec3 color)"                                               << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    const float dither_bit = 8.0;"                                          << std::endl;
    ost << "    float shift = 0.25 * (1.0/(pow(2.0, dither_bit) - 1.0));"               << std::endl;
    ost << "    vec3  dither_shift  = vec3(shift, -shift, shift);"                      << std::endl;
    ost << "    float grid_position = rand(gl_FragCoord.xy);"                           << std::endl;
    ost << "    dither_shift = mix(2.0*dither_shift,-2.0*dither_shift, grid_position );"<< std::endl;
    ost << "    return color + dither_shift;"                                           << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncLinearizeZ(std::stringstream& ost)
{
    ost << "float LinearizeZ(float depth)"                                              << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float zLinear = 2.0 * zNear  "                                          << std::endl;
    ost << "                    / (zFar + zNear - depth * (zFar - zNear));"             << std::endl;
    ost << "    return zLinear;"                                                        << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genSharedCode(std::stringstream& ost)
{
    //
    // Logarithm to base 10 currently missing form GLSL
    //
    genFuncLog10(ost);

    //
    // Mixed type power function
    //
    genFuncPow(ost);

    //
    // Color conversion functions
    //
    genFuncGammaCorrection(ost);

    //
    // Sample the primary input color
    //
    genFuncGetPrimaryInputColor(ost);
    genFuncGetDepthValue(ost);

    //
    // Samples average luminance value from given texture at given mip map level
    //
    genFuncGetAvgLuminance(ost);

    //
    // Approximates luminance from an RGB value
    //
    genFuncCalcLuminance(ost);

    //
    // Determines the color based on exposure settings
    //
    // See: https://placeholderart.wordpress.com/2014/11/21/implementing-a-physically-based-camera-manual-exposure/
    //
    genFuncSaturationBasedExp(ost);
    genFuncStandardOutputBasedExp(ost);
    genFuncLog2Exposure(ost);
    genFuncCalcExposedColor(ost);

    //
    // Apply a contrast operation
    //
    // See: http://filmicworlds.com/blog/minimal-color-grading-tools/
    //
    genFuncContrastCorrection(ost);

    //
    // Perform color correction in tone mapping
    //
    // R. Mantiuk et al
    // Color correction for tone mapping
    // https://www.cs.ubc.ca/~heidrich/Papers/EG.09_1.pdf
    //
    genFuncColorCorrection(ost);

    //
    // Logarithmic mapping
    //
    // Adaptive Logarithmic Mapping for Displaying High Contrast Scenes
    // F. Drago, K. Myszkowski, T. Annen, and N. Chiba
    // In Eurographics 2003 
    // http://resources.mpi-inf.mpg.de/tmo/logmap/logmap.pdf
    //
    genFuncToneMapLogarithmic(ost);

    //
    // Exponential mapping
    //
    genFuncToneMapExponential(ost);

    //
    // Drago's Logarithmic mapping
    //
    // Adaptive Logarithmic Mapping for Displaying High Contrast Scenes
    // F. Drago, K. Myszkowski, T. Annen, and N. Chiba
    // In Eurographics 2003 
    // http://resources.mpi-inf.mpg.de/tmo/logmap/logmap.pdf
    //
    genFuncToneMapDragoLogarithmic(ost);

    //
    // Applies Reinhard's basic tone mapping operator
    //
    // Photographic Tone Reproduction for Digital Images
    // Erik Reinhard, Michael Stark, Peter Shirley, James Ferwerda
    // http://www.cmap.polytechnique.fr/~peyre/cours/x2005signal/hdr_photographic.pdf
    //
    genFuncToneMapReinhard(ost);

    //
    // Applies Reinhard's modified tone mapping operator
    //
    // Photographic Tone Reproduction for Digital Images
    // Erik Reinhard, Michael Stark, Peter Shirley, James Ferwerda
    // http://www.cmap.polytechnique.fr/~peyre/cours/x2005signal/hdr_photographic.pdf
    //
    genFuncToneMapReinhardModified(ost);

    //
    // Applies the filmic curve from John Hable's presentation
    // Optimized filmic operator by Jim Hejl and Richard Burgess-Dawson.
    //
    // http://filmicgames.com/archives/75
    // http://de.slideshare.net/ozlael/hable-john-uncharted2-hdr-lighting slide 53ff
    //
    genFuncToneMapFilmicALU(ost);

    //
    // Function used by the Uncharted2 tone mapping curve
    //
    genFuncU2Func(ost);

    //
    // Applies the Uncharted 2 filmic tone mapping curve
    //
    // http://filmicgames.com/archives/75
    // http://de.slideshare.net/ozlael/hable-john-uncharted2-hdr-lighting slide 53ff
    //
    genFuncToneMapFilmicU2(ost);

    //
    // http://filmicworlds.com/blog/filmic-tonemapping-with-piecewise-power-curves/
    //
    genFuncToneMapFilmicACES(ost);

    //
    // https://twitter.com/jimhejl/status/633777619998130176
    //
    genFuncToneMapFilmicHejl2015(ost);

    //
    // https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
    //
    genFuncToneMapFilmicACES2(ost);

    //
    // Applies exposure and tone mapping to the specific color, and applies
    // the threshold to the exposure value. 
    //
    genFuncToneMap(ost);
}

void HDR2Stage::genCommonVertexShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout(location = 0) in vec2 vPosition;"                                    << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "out vec2 TexCoord;"                                                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "const vec2 madd = vec2(0.5, 0.5);"                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec4 vPos = vec4(vPosition.x, vPosition.y, 0, 1);"                      << std::endl;
    ost << "    gl_Position = vPos;"                                                    << std::endl;
    ost << "    TexCoord    = vPos.xy * madd + madd;"                                   << std::endl;
    ost << "}"                                                                          << std::endl;
}

void HDR2Stage::genLuminanceMapFragmentShader(std::stringstream& ost)
{
    //
    // This shader takes the input fragment color and writes
    // the calculated luminance. 
    //
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;"                                               << std::endl;
    ost << "uniform sampler2D InputTex1;"                                               << std::endl;
    ost << "uniform bool      Use_ITU_R_BT_709;"                                        << std::endl;
    ost << "uniform bool      ForceBackground;"                                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout(location = 0) out float FragColor;   // only red channel"            << std::endl;
    ost << ""                                                                           << std::endl;
    ost << Shader::getEqualEpsSnippet()                                                 << std::endl;
    //
    // Sample the primary input color
    //
    genFuncGetPrimaryInputColor(ost);

    //
    // Approximates luminance from an RGB value
    //      http://www.poynton.com/PDFs/ColorFAQ.pdf
    //      http://www.poynton.com/PDFs/coloureq.pdf
    //
    genFuncCalcLuminance(ost);

    //
    // Creates the luminance map for the scene
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 color  = GetPrimaryInputColor(InputTex0);"                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (ForceBackground)"                                                   << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        vec3 background = GetPrimaryInputColor(InputTex1);"                 << std::endl;
    ost << "        if (OSGEqualEps(color, background, 1.E-6))"                         << std::endl;
    ost << "            color = vec3(0.5,0.5,0.5);"                                     << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    float lum   = CalcLuminance(color);"                                    << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    FragColor   = lum;"                                                     << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genAdaptLuminanceFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;    // Last luminance map"                      << std::endl;
    ost << "uniform sampler2D InputTex1;    // Current luminance map"                   << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform float TimeDelta;        // timer.DeltaSecondsF()"                   << std::endl;
    ost << "uniform bool  AdjustLuminance;"                                             << std::endl;
    ost << ""                                                                           << std::endl;

    genBlockHDRShaderData(ost);

    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout(location = 0) out float FragColor;"                                  << std::endl;
    ost << ""                                                                           << std::endl;

    //
    // Sample the last luminance value
    //
    genFuncGetLastLumValue(ost);

    //
    // Sample the current luminance value
    //
    genFuncGetCurrLumValue(ost);

    //
    // Slowly adjusts the scene luminance based on the previous scene luminance
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float currLum = GetCurrLumValue(InputTex1);"                            << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    float adaptedLum;"                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (AdjustLuminance)"                                                   << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        float lastLum = exp(GetLastLumValue(InputTex0));"                   << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "        // Adapt the luminance using Pattanaik's technique"                 << std::endl;
    ost << "        adaptedLum = lastLum + (currLum - lastLum)"                         << std::endl;
    ost << "                         * (1.0 - exp(-TimeDelta * hdrShaderData.Tau));"    << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "    else"                                                                   << std::endl;
    ost << "        adaptedLum = currLum;"                                              << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    FragColor = log(adaptedLum);"                                           << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genThresholdFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;    // Primary color input"                     << std::endl;
    ost << "uniform sampler2D InputTex1;    // Average luminance map"                   << std::endl;
    ost << "uniform sampler2D InputTex2;    // Depth map"                               << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform float     Level;  // Mipmap level"                                  << std::endl;
    ost << "uniform bool      Use_ITU_R_BT_709;"                                        << std::endl;
    ost << "uniform bool      FilterBackground;"                                        << std::endl;

    genBlockHDRShaderData(ost);

    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout (location = 0) out vec4 FragColor;"                                  << std::endl;
    ost << ""                                                                           << std::endl;

    genSharedCode(ost);

    //
    // Uses a lower exposure to produce a value suitable for a bloom pass
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float avgLuminance = GetAvgLuminance(InputTex1);"                       << std::endl;
    ost << "    vec3 color         = GetPrimaryInputColor(InputTex0);"                  << std::endl;
    ost << "    float depth        = GetDepthValue(InputTex2);"                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    color = ToneMap(color, avgLuminance, hdrShaderData.BloomThreshold);"    << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (FilterBackground && depth == 1.0)"                                  << std::endl;
    ost << "        FragColor = vec4(0.0);"                                             << std::endl;
    ost << "    else"                                                                   << std::endl;
    ost << "        FragColor = vec4(color, 1.0);"                                      << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genScaleFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                << std::endl;
    ost << ""                                                                          << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                         << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                         << std::endl;
    ost << ""                                                                          << std::endl;
    ost << "uniform sampler2D InputTex0;    // Primary color input"                    << std::endl;
    ost << ""                                                                          << std::endl;
    ost << "in vec2 TexCoord;"                                                         << std::endl;
    ost << ""                                                                          << std::endl;
    ost << "layout (location = 0) out vec4 FragColor;"                                 << std::endl;
    ost << ""                                                                          << std::endl;
    //
    // Sample the primary input color
    //
    genFuncGetPrimaryInputColor(ost);

    //
    // Uses hw bilinear filtering for upscaling or downscaling
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 color = GetPrimaryInputColor(InputTex0);"                          << std::endl;
    ost << "    FragColor = vec4(color, 1.0);"                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genBloomBlurFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;"                                               << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform vec2      Direction;    // {(1.0, 0.0), (0.0, 1.0)}"                << std::endl;
    ost << ""                                                                           << std::endl;

    genBlockHDRShaderData(ost);

    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout(location = 0) out vec4 FragColor;"                                   << std::endl;
    ost << ""                                                                           << std::endl;

    //
    // Calculates the gaussian blur weight for a given distance and sigmas
    //
    genFuncCalcGaussianWeight(ost);

    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec2 rcpSize = 1.0 / vec2(textureSize(InputTex0, 0).xy);"               << std::endl;
    ost << "    vec2 offset  = Direction * rcpSize;"                                    << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    vec3 color = vec3(0);"                                                  << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    for(int i = -hdrShaderData.nTaps; i <= hdrShaderData.nTaps; ++i)"       << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        float weight = CalcGaussianWeight(i, hdrShaderData.Sigma);"         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "        vec2 texCoord = TexCoord + i*offset;"                               << std::endl;
    ost << "        color += weight * texture(InputTex0, texCoord).rgb;"                << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    FragColor = vec4(color, 1);"                                            << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genCompositeFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;    // Primary color input"                     << std::endl;
    ost << "uniform sampler2D InputTex1;    // Average luminance map"                   << std::endl;
    if (getPerformBloom())
    {
    ost << "uniform sampler2D InputTex2;    // Bloom map"                               << std::endl;
    }
    ost << "uniform sampler2D InputTex3;    // Background color map"                    << std::endl;
    ost << "uniform sampler2D InputTex4;    // Depth value input"                       << std::endl;
    ost << "uniform bool      ForceBackground;"                                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform float     Level;        // Luminance Mip Map Level"                 << std::endl;
    ost << "uniform bool      Use_ITU_R_BT_709;"                                        << std::endl;
    ost << ""                                                                           << std::endl;

    genBlockHDRShaderData(ost);

    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout (location = 0) out vec4 FragColor;      // final color"              << std::endl;
    ost << "layout (location = 1) out vec3 AvgLuminance;   // exposure map"             << std::endl;
    ost << ""                                                                           << std::endl;
    ost << Shader::getEqualEpsSnippet()                                                 << std::endl;

    //
    // Sample the bloom map
    //
    if (getPerformBloom())
        genFuncGetBloomColor(ost);

    genSharedCode(ost);

    //
    // Applies exposure and tone mapping to the input combined with bloom pass result
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float avgLuminance = GetAvgLuminance(InputTex1);"                       << std::endl;
    ost << "    vec3 color         = GetPrimaryInputColor(InputTex0);"                  << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (ForceBackground)"                                                   << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        vec3 background = GetPrimaryInputColor(InputTex3);"                 << std::endl;
    ost << "        float depth     = GetDepthValue(InputTex4);"                        << std::endl;
    ost << "        if (OSGEqualEps(color, background, 1.E-6) && depth == 1.0)"         << std::endl;
    ost << "        {"                                                                  << std::endl;
    ost << "            FragColor = vec4(background, 1.0);"                             << std::endl;
    ost << "            AvgLuminance = vec3(avgLuminance, avgLuminance, avgLuminance);" << std::endl;
    ost << "            return;"                                                        << std::endl;
    ost << "        }"                                                                  << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    if (getPerformBloom())
    {
    ost << "    vec3 bloom         = GetBloomColor(InputTex2);"                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    bloom *= hdrShaderData.BloomMagnitude;"                                 << std::endl;
    }
    ost << ""                                                                           << std::endl;
    ost << "    float threshold = 0.0;"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    if (getPerformBloom())
    {
    ost << "    color = color + bloom;"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    }

    ost << "    color = ToneMap(color, avgLuminance, threshold);"                       << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    FragColor    = vec4(color, 1.0);"                                       << std::endl;
    ost << "    AvgLuminance = vec3(avgLuminance, avgLuminance, avgLuminance);"         << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFinalScreenFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;    // Primary color input"                     << std::endl;
    ost << "uniform sampler2D InputTex1;    // Depth value input"                       << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform bool  CarryDepth;"                                                  << std::endl;
    ost << "uniform bool  PerformDithering;"                                            << std::endl;
    ost << "uniform bool  LinearizeDepth;"                                              << std::endl;
    ost << "uniform float zNear;"                                                       << std::endl;
    ost << "uniform float zFar;"                                                        << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform float Gamma;"                                                       << std::endl;
    ost << "uniform bool  ApplyGamma;"                                                  << std::endl;
    ost << "uniform bool  AccurateGamma;"                                               << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform vec3  ShadowLift;"                                                  << std::endl;
    ost << "uniform vec3  InvMidtoneGamma;"                                             << std::endl;
    ost << "uniform vec3  HighlightGain;"                                               << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout (location = 0) out vec4 FragColor;"                                  << std::endl;
    ost << ""                                                                           << std::endl;

    //
    // Sample the primary input color
    //
    genFuncGetPrimaryInputColor(ost);

    //
    // Sample the depth value
    //
    genFuncGetDepthValue(ost);
    genFuncLinearizeZ(ost);

    //
    // Mixed type power function
    //
    genFuncPow(ost);

    //
    // Bunch of gamma correction functions
    //
    genFuncGammaCorrection(ost);


    //
    // Lift/Gamma/Gain color correction function
    //
    genFuncLiftGammaGainCorrection(ost);

    //
    // Dithering function
    //
    genFuncDithering(ost);

    //
    // Write color and depth to screen buffer
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3  color = GetPrimaryInputColor(InputTex0);"                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (LinearizeDepth)"                                                    << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        float zLinear = LinearizeZ(color.x);"                               << std::endl;
    ost << "        color = vec3(zLinear);"                                             << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (ApplyGamma)"                                                        << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        if (AccurateGamma)"                                                 << std::endl;
    ost << "            color = AccurateLinearToSRGB(color);"                           << std::endl;
    ost << "        else"                                                               << std::endl;
    ost << "            color = ApproximationLinearToSRGB(color, Gamma);"               << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    color = LiftGammaGainCorrection(color);"                                << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (PerformDithering)"                                                  << std::endl;
    ost << "        color = DitherColor(color);"                                        << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    FragColor = vec4(color, 1.0);"                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (CarryDepth)"                                                        << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        float depth  = GetDepthValue(InputTex1);"                           << std::endl;
    ost << "        gl_FragDepth = depth;"                                              << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

SimpleSHLChunkTransitPtr HDR2Stage::genLuminanceMapShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genLuminanceMapFragmentShader(frag);

#ifdef OSG_WRITE_SHADER_CODE_TO_FILE
    {
        std::ofstream outVert(getShaderCodeFile("HDR2LuminanceMapShader.vert"));
        std::ofstream outFrag(getShaderCodeFile("HDR2LuminanceMapShader.frag"));
    
        outVert << vert.str() << std::endl << std::flush;
        outFrag << frag.str() << std::endl << std::flush;
    }
#endif    

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genAdaptLuminanceShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genAdaptLuminanceFragmentShader(frag);

#ifdef OSG_WRITE_SHADER_CODE_TO_FILE
    {
        std::ofstream outVert(getShaderCodeFile("HDR2AdaptLuminanceShader.vert"));
        std::ofstream outFrag(getShaderCodeFile("HDR2AdaptLuminanceShader.frag"));
    
        outVert << vert.str() << std::endl << std::flush;
        outFrag << frag.str() << std::endl << std::flush;
    }
#endif    

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genThresholdShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genThresholdFragmentShader(frag);

#ifdef OSG_WRITE_SHADER_CODE_TO_FILE
    {
        std::ofstream outVert(getShaderCodeFile("HDR2ThresholdShader.vert"));
        std::ofstream outFrag(getShaderCodeFile("HDR2ThresholdShader.frag"));
    
        outVert << vert.str() << std::endl << std::flush;
        outFrag << frag.str() << std::endl << std::flush;
    }
#endif    

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genScaleShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genScaleFragmentShader(frag);

#ifdef OSG_WRITE_SHADER_CODE_TO_FILE
    {
        std::ofstream outVert(getShaderCodeFile("HDR2ScaleShader.vert"));
        std::ofstream outFrag(getShaderCodeFile("HDR2ScaleShader.frag"));
    
        outVert << vert.str() << std::endl << std::flush;
        outFrag << frag.str() << std::endl << std::flush;
    }
#endif    

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genBloomBlurShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genBloomBlurFragmentShader(frag);

#ifdef OSG_WRITE_SHADER_CODE_TO_FILE
    {
        std::ofstream outVert(getShaderCodeFile("HDR2BloomBlurShader.vert"));
        std::ofstream outFrag(getShaderCodeFile("HDR2BloomBlurShader.frag"));
    
        outVert << vert.str() << std::endl << std::flush;
        outFrag << frag.str() << std::endl << std::flush;
    }
#endif    

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genCompositeShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genCompositeFragmentShader(frag);

#ifdef OSG_WRITE_SHADER_CODE_TO_FILE
    {
        std::ofstream outVert(getShaderCodeFile("HDR2CompositeShader.vert"));
        std::ofstream outFrag(getShaderCodeFile("HDR2CompositeShader.frag"));
    
        outVert << vert.str() << std::endl << std::flush;
        outFrag << frag.str() << std::endl << std::flush;
    }
#endif    

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genFinalScreenShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genFinalScreenFragmentShader(frag);

#ifdef OSG_WRITE_SHADER_CODE_TO_FILE
    {
        std::ofstream outVert(getShaderCodeFile("HDR2FinalScreenShader.vert"));
        std::ofstream outFrag(getShaderCodeFile("HDR2FinalScreenShader.frag"));
    
        outVert << vert.str() << std::endl << std::flush;
        outFrag << frag.str() << std::endl << std::flush;
    }
#endif    

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

static Real64 Log2(Real64 number)
{
    return log(number)/log(2.0);
}

static Int32 MipmapLevels(Int32 n)
{
    return static_cast<Int32>(1.0 + floor(Log2(n)));
}

static std::size_t align_offset(std::size_t base_alignment, std::size_t base_offset)
{
    return base_alignment * ((base_alignment + base_offset - 1) / base_alignment);
}

OSG_END_NAMESPACE
