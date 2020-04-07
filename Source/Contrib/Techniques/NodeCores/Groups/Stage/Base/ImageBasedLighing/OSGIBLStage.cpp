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

#include "OSGIBLStage.h"
#include "OSGIBLStageData.h"

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
// OSGIBLStageBase.cpp file.
// To modify it, please change the .fcd file (OSGIBLStage.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 IBLStage::_uiFramebufferObjectExt = Window::invalidExtensionID;
UInt32 IBLStage::_uiFuncDrawBuffers      = Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void IBLStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            IBLStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&IBLStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            IBLStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&IBLStage::renderLeave));

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

IBLStage::IBLStage(void)
: Inherited ()
, _mapUpdate()
{
}

IBLStage::IBLStage(const IBLStage &source)
: Inherited (source)
, _mapUpdate(      )
{
}

IBLStage::~IBLStage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void IBLStage::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if((whichField & (  IrradianceTexUnitFieldMask |
                        PreFilterTexUnitFieldMask |
                        BrdfLutTexUnitFieldMask |
                        IrradianceTexDescFieldMask |
                        PreFilterTexDescFieldMask |
                        BrdfLutTexDescFieldMask
                     )) != 0)
    {
        UpdateMapT::iterator iter = _mapUpdate.begin();
        UpdateMapT::iterator end  = _mapUpdate.end  ();

        for (; iter != end; ++iter)
            iter->second = true;
    }

    Inherited::changed(whichField, origin, details);
}

void IBLStage::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump IBLStage NI" << std::endl;
}

#ifdef OSG_DEBUG_IBL_STAGE
void IBLStage::dump_fbo(const char* name, FrameBufferObject* fbo, std::stringstream& ss) const
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

std::string IBLStage::dump_stage(IBLStageData* pData) const
{
    std::stringstream ss;
    ss << std::endl;
    
    return ss.str();
}

void IBLStage::dump_image(const char* name, FrameBufferAttachment* fba) const
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

Action::ResultE IBLStage::renderEnter(Action* action)
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

    IBLStageDataUnrecPtr pData = a->getData<IBLStageData *>(_iDataSlotId);
    if (pData == NULL)
    {
        this->initData(a, iVPWidth, iVPHeight);
#ifdef OSG_DEBUG_IBL_STAGE
        pData = a->getData<IBLStageData *>(_iDataSlotId);
        std::string dump_str = dump_stage(pData);
        ::OutputDebugString(dump_str.c_str());
        FDEBUG((dump_str.c_str()));
#endif
    }
    else
    {
#if 0
        // only testing: force update
        IBLStageData* pStageData = pData;
        _mapUpdate            [pStageData] = true;
        _mapUpdateOffsetKernel[pStageData] = true;
        _mapUpdateRotateKernel[pStageData] = true;
#endif

        this->updateData(a, iVPWidth, iVPHeight);
    }

    pData = a->getData<IBLStageData *>(_iDataSlotId);

    //
    // Future: Preprocessing goes here. See SSAO stage as an example!
    //


    //
    // We override the current state in such a way that we add the three IBL texture object chunks.
    //
    a->pushState();

    addOverride(pData, a);

    Thread::getCurrentChangeList()->commitChanges();

    this->recurseFromThis(a);
    a->useNodeList(false);

    a->popState();

    return Action::Skip;
}

Action::ResultE IBLStage::renderLeave(Action *action)
{
    if (getActivate() == false)
        return Group::renderLeave(action);

    return Action::Skip;
}

void IBLStage::addOverride(IBLStageData* pData, RenderAction* a)
{
    Int32 iIrradianceTexUnit = getIrradianceTexUnit();
    Int32 iPreFilterTexUnit  = getPreFilterTexUnit();
    Int32 iBrdfLutTexUnit    = getBrdfLutTexUnit();

    TextureObjChunk* irradianceTexObjChunk = getIrradianceTexObjChunk();
    TextureObjChunk*  preFilterTexObjChunk = getPreFilterTexObjChunk();
    TextureObjChunk*    brdfLutTexObjChunk = getBrdfLutTexObjChunk();

    if (irradianceTexObjChunk && preFilterTexObjChunk && brdfLutTexObjChunk)
    {
        a->addOverride(irradianceTexObjChunk->getClassId() + iIrradianceTexUnit, irradianceTexObjChunk);
        a->addOverride( preFilterTexObjChunk->getClassId() + iPreFilterTexUnit,   preFilterTexObjChunk);
        a->addOverride(   brdfLutTexObjChunk->getClassId() + iBrdfLutTexUnit,       brdfLutTexObjChunk);
    }
}

/*------------------------------ Data -------------------------------------*/

void IBLStage::initData(RenderAction* pAction,
                        Int32         iVPWidth,
                        Int32         iVPHeight)
{
    IBLStageDataUnrecPtr pData = pAction->getData<IBLStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = setupStageData(pAction, iVPWidth, iVPHeight);

        this->setData(pData, _iDataSlotId, pAction);
    }
}

void IBLStage::updateData(RenderAction* pAction,
                          Int32         iVPWidth,
                          Int32         iVPHeight)
{
    IBLStageDataUnrecPtr pData = pAction->getData<IBLStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        initData(pAction, iVPWidth, iVPHeight);

        pData = pAction->getData<IBLStageData *>(_iDataSlotId);
    }
    else
    {
        updateStageData(pData, pAction, iVPWidth, iVPHeight);
    }
}

/*---------------------------- StageData ----------------------------------*/

IBLStageDataTransitPtr IBLStage::setupStageData(
    RenderAction* pAction,
    Int32         iPixelWidth,
    Int32         iPixelHeight)
{
    IBLStageDataUnrecPtr stageData = IBLStageData::createLocal();

    if(stageData == NULL)
        return IBLStageDataTransitPtr(NULL);

    _mapUpdate[stageData] = true;

    stageData->setWidth (iPixelWidth );
    stageData->setHeight(iPixelHeight);

    OSG::Thread::setCurrentLocalFlags();

    Thread::getCurrentChangeList()->commitChanges();

    return IBLStageDataTransitPtr(stageData);
}

void IBLStage::updateStageData(
    IBLStageData* pData,
    RenderAction* pAction,
    Int32         iPixelWidth,
    Int32         iPixelHeight)
{
    bool resize = false;

    if (iPixelWidth != pData->getWidth() || iPixelHeight != pData->getHeight())
        resize = true;

    if (   !_mapUpdate[pData] 
        && !resize)
        return;

    pData->setWidth (iPixelWidth );
    pData->setHeight(iPixelHeight);

    OSG::Thread::setCurrentLocalFlags();

    _mapUpdate[pData] = false;

    Thread::getCurrentChangeList()->commitChanges();
}

/*---------------------------- postProcess --------------------------------*/

void IBLStage::postProcess(DrawEnv *pEnv)
{
    UInt32  uiActiveFBO = pEnv->getActiveFBO();
    Window* win         = pEnv->getWindow();

    IBLStageData* pData = pEnv->getData<IBLStageData*>(_iDataSlotId);
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


    pEnv->deactivateState();

    glPopMatrix();
}

OSG_END_NAMESPACE
