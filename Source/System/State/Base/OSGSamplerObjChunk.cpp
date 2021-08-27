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

#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGWindow.h"

#include "OSGGLFuncProtos.h"

#include "OSGDrawEnv.h"

#include "OSGSamplerObjChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSamplerObjChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGSamplerObjChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass SamplerObjChunk::_class("SamplerObject",
                                        osgMaxTexImages,// number if slots
                                        30);            // priority
                                        
volatile UInt16 SamplerObjChunk::_uiChunkCounter = 1;

typedef OSG::Window Win;

UInt32 SamplerObjChunk::_arbSamplerObjects                  = Win::invalidExtensionID;

UInt32 SamplerObjChunk::_funcGenSamplers             = Win::invalidFunctionID;
UInt32 SamplerObjChunk::_funcDeleteSamplers          = Win::invalidFunctionID;
//UInt32 SamplerObjChunk::_funcIsSampler               = Win::invalidFunctionID;
UInt32 SamplerObjChunk::_funcBindSampler             = Win::invalidFunctionID;
UInt32 SamplerObjChunk::_funcSamplerParameteri       = Win::invalidFunctionID;
UInt32 SamplerObjChunk::_funcSamplerParameterf       = Win::invalidFunctionID;
//UInt32 SamplerObjChunk::_funcSamplerParameteriv      = Win::invalidFunctionID;
UInt32 SamplerObjChunk::_funcSamplerParameterfv      = Win::invalidFunctionID;
//UInt32 SamplerObjChunk::_funcSamplerParameterIiv     = Win::invalidFunctionID;
//UInt32 SamplerObjChunk::_funcSamplerParameterIuiv    = Win::invalidFunctionID;
//UInt32 SamplerObjChunk::_funcGetSamplerParameteriv   = Win::invalidFunctionID;
//UInt32 SamplerObjChunk::_funcGetSamplerParameterfv   = Win::invalidFunctionID;
//UInt32 SamplerObjChunk::_funcGetSamplerParameterIiv  = Win::invalidFunctionID;
//UInt32 SamplerObjChunk::_funcGetSamplerParameterIuiv = Win::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SamplerObjChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _arbSamplerObjects = Window::registerExtension("GL_ARB_sampler_objects");
        
        _funcGenSamplers             = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGenSamplers",
            _arbSamplerObjects);
        _funcDeleteSamplers          = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glDeleteSamplers",
            _arbSamplerObjects);
        //_funcIsSampler               = Window::registerFunction(
        //    OSG_DLSYM_UNDERSCORE"glIsSampler",
        //    _arbSamplerObjects);
        _funcBindSampler             = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBindSampler",
            _arbSamplerObjects);
        _funcSamplerParameteri       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glSamplerParameteri",
            _arbSamplerObjects);
        _funcSamplerParameterf       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glSamplerParameterf",
            _arbSamplerObjects);
        //_funcSamplerParameteriv      = Window::registerFunction(
        //    OSG_DLSYM_UNDERSCORE"glSamplerParameteriv",
        //    _arbSamplerObjects);
        _funcSamplerParameterfv      = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glSamplerParameterfv",
            _arbSamplerObjects);
        //_funcSamplerParameterIiv     = Window::registerFunction(
        //    OSG_DLSYM_UNDERSCORE"glSamplerParameterIiv",
        //    _arbSamplerObjects);
        //_funcSamplerParameterIuiv    = Window::registerFunction(
        //    OSG_DLSYM_UNDERSCORE"glSamplerParameterIuiv",
        //    _arbSamplerObjects);
        //_funcGetSamplerParameteriv   = Window::registerFunction(
        //    OSG_DLSYM_UNDERSCORE"glGetSamplerParameteriv",
        //    _arbSamplerObjects);
        //_funcGetSamplerParameterfv   = Window::registerFunction(
        //    OSG_DLSYM_UNDERSCORE"glGetSamplerParameterfv",
        //    _arbSamplerObjects);
        //_funcGetSamplerParameterIiv  = Window::registerFunction(
        //    OSG_DLSYM_UNDERSCORE"glGetSamplerParameterIiv",
        //    _arbSamplerObjects);
        //_funcGetSamplerParameterIuiv = Window::registerFunction(
        //    OSG_DLSYM_UNDERSCORE"glGetSamplerParameterIuiv",
        //    _arbSamplerObjects);
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SamplerObjChunk::SamplerObjChunk(void) :
    Inherited(),
    _uiChunkId(0)
{
}

SamplerObjChunk::SamplerObjChunk(const SamplerObjChunk &source) :
    Inherited(source),
    _uiChunkId(0)
{
}

SamplerObjChunk::~SamplerObjChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

const StateChunkClass *SamplerObjChunk::getClass(void) const
{
    return &_class;
}

void SamplerObjChunk::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    GLenum id = _sfGLId.getValue();

    if((whichField & (BorderColorFieldMask |
                      MinFilterFieldMask |
                      MagFilterFieldMask |
                      WrapSFieldMask |
                      WrapTFieldMask |
                      WrapRFieldMask |
                      MinLODFieldMask |
                      MaxLODFieldMask |
                      LODBiasFieldMask |
                      CompareModeFieldMask |
                      CompareFuncFieldMask |
                      MaxAnisotropyFieldMask)) != 0)
    {
        Window::reinitializeGLObject(id);
    }
    
    Inherited::changed(whichField, origin, details);
}

/*----------------------------- onCreate --------------------------------*/

void SamplerObjChunk::onCreate(const SamplerObjChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    _uiChunkId = _uiChunkCounter++;
    
    setGLId(Window::registerGLObject(
                boost::bind(&SamplerObjChunk::handleGL, 
                            SamplerObjChunkMTUncountedPtr(this), 
                            ::boost::placeholders::_1, 
                            ::boost::placeholders::_2, 
                            ::boost::placeholders::_3, 
                            ::boost::placeholders::_4),
                &SamplerObjChunk::handleDestroyGL));
}

void SamplerObjChunk::onCreateAspect(const SamplerObjChunk *createAspect,
                                     const SamplerObjChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

void SamplerObjChunk::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}

/*------------------------------ Output ----------------------------------*/

void SamplerObjChunk::dump(      UInt32  uiIndent,
                         const BitVector bvFlags) const
{
    SLOG << "Dump SamplerObjChunk NI" << std::endl;

    if ((bvFlags & GLIdFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "gl Id " << _sfGLId.getValue() << "\n";
    }
    if ((bvFlags & TextureUnitsFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);

        MFTextureUnitsType::const_iterator sIt  = getMFTextureUnits()->begin();
        MFTextureUnitsType::const_iterator sEnd = getMFTextureUnits()->end();

        for(; sIt != sEnd; ++sIt)
        {
            UInt32 texUnit = *sIt;
            PLOG << "texture unit " << texUnit << "\n";
        }
    }
    if ((bvFlags & BorderColorFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "border color " << _sfBorderColor.getValue() << "\n";
    }
    if ((bvFlags & MinFilterFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "minification filter " << _sfMinFilter.getValue() << "\n";
    }
    if ((bvFlags & MagFilterFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "magnification filter " << _sfMagFilter.getValue() << "\n";
    }
    if ((bvFlags & WrapSFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "warp S " << _sfWrapS.getValue() << "\n";
    }
    if ((bvFlags & WrapTFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "warp T " << _sfWrapT.getValue() << "\n";
    }
    if ((bvFlags & WrapRFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "warp R " << _sfWrapR.getValue() << "\n";
    }
    if ((bvFlags & MinLODFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "minimal LOD " << _sfMinLOD.getValue() << "\n";
    }
    if ((bvFlags & MaxLODFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "maximal LOD " << _sfMaxLOD.getValue() << "\n";
    }
    if ((bvFlags & LODBiasFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "bial LOD " << _sfLODBias.getValue() << "\n";
    }
    if ((bvFlags & CompareModeFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "compare mode " << _sfCompareMode.getValue() << "\n";
    }
    if ((bvFlags & CompareFuncFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "compare function " << _sfCompareFunc.getValue() << "\n";
    }
    if ((bvFlags & MaxAnisotropyFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "maximal anisotropy " << _sfMaxAnisotropy.getValue() << "\n";
    }
}

/*------------------------------ GL -----------------------------------------*/

/*! GL object handler                                                        */
UInt32 SamplerObjChunk::handleGL(DrawEnv                 *pEnv, 
                                 UInt32                   osgid, 
                                 Window::GLObjectStatusE  mode,
                                 UInt64                   uiOptions)
{
    Window *pWin = pEnv->getWindow();
    GLuint  id   = pWin->getGLObjectId(osgid);

    bool hasSamplerObj = pWin->hasExtOrVersion(_arbSamplerObjects, 0x0302, 0x0300);
    if(!hasSamplerObj)
    {
        FWARNING(
            ("SamplerObjChunk::handleGL: sampler objects not "
             "supported for this window!\n"));
        return 0;
    }

    switch (mode)
    {
        case Window::initialize:
            {
                OSGGETGLFUNCBYID_GL3_ES( glGenSamplers,
                                      osgGlGenSamplers,
                                      _funcGenSamplers,
                                      pWin);

                osgGlGenSamplers(1, &id);
                pWin->setGLObjectId(osgid, id);
            }
            break;
        default:
            {
                SWARNING << "SamplerObjChunk(" << this << "::handleGL: Illegal mode: "
                         << mode << " for id " << id << std::endl;
            }
    }

    switch (mode)
    {
        case Window::initialize:
        case Window::reinitialize:
        case Window::needrefresh:
            {
                OSGGETGLFUNCBYID_GL3_ES( glSamplerParameteri,
                                        osgGlSamplerParameteri,
                                        _funcSamplerParameteri,
                                        pWin);
                OSGGETGLFUNCBYID_GL3_ES( glSamplerParameterf,
                                        osgGlSamplerParameterf,
                                        _funcSamplerParameterf,
                                        pWin);
                //OSGGETGLFUNCBYID_GL3_ES( glSamplerParameteriv,
                //                        osgGlSamplerParameteriv,
                //                        _funcSamplerParameteriv,
                //                        pWin);
                OSGGETGLFUNCBYID_GL3_ES( glSamplerParameterfv,
                                        osgGlSamplerParameterfv,
                                        _funcSamplerParameterfv,
                                        pWin);
                //OSGGETGLFUNCBYID_GL3_ES( glSamplerParameterIiv,
                //                        osgGlSamplerParameterIiv,
                //                        _funcSamplerParameterIiv,
                //                        pWin);
                //OSGGETGLFUNCBYID_GL3_ES( glSamplerParameterIuiv,
                //                        osgGlSamplerParameterIuiv,
                //                        _funcSamplerParameterIuiv,
                //                        pWin);

                GLuint id = pWin->getGLObjectId(osgid);

                osgGlSamplerParameterfv(id, GL_TEXTURE_BORDER_COLOR,        const_cast<GLfloat *>(getBorderColor().getValuesRGBA()));
                osgGlSamplerParameteri (id, GL_TEXTURE_MIN_FILTER,          getMinFilter());
                osgGlSamplerParameteri (id, GL_TEXTURE_MAG_FILTER,          getMagFilter());
                osgGlSamplerParameteri (id, GL_TEXTURE_WRAP_S,              getWrapS());
                osgGlSamplerParameteri (id, GL_TEXTURE_WRAP_T,              getWrapT());
                osgGlSamplerParameteri (id, GL_TEXTURE_WRAP_R,              getWrapR());
                osgGlSamplerParameterf (id, GL_TEXTURE_MIN_LOD,             getMinLOD());
                osgGlSamplerParameterf (id, GL_TEXTURE_MAX_LOD,             getMaxLOD());
                osgGlSamplerParameterf (id, GL_TEXTURE_LOD_BIAS,            getLODBias());
                osgGlSamplerParameteri (id, GL_TEXTURE_COMPARE_MODE,        getCompareMode());
                osgGlSamplerParameteri (id, GL_TEXTURE_COMPARE_FUNC,        getCompareFunc());
                osgGlSamplerParameterf (id, GL_TEXTURE_MAX_ANISOTROPY_EXT,  getMaxAnisotropy());

                glErr("SamplerObjChunk::handleGL initialize");
            }
            break;
    }

    return 0;
}

/*! GL object handler
    destroy it
*/
void SamplerObjChunk::handleDestroyGL(DrawEnv                 *pEnv, 
                                      UInt32                   osgid, 
                                      Window::GLObjectStatusE  mode)
{
    Window *pWin = pEnv->getWindow();
    GLuint  id   = pWin->getGLObjectId(osgid);

    if(mode == Window::destroy)
    {
        OSGGETGLFUNCBYID_GL3_ES( glDeleteSamplers,
                                 osgGlDeleteSamplers,
                                _funcDeleteSamplers, 
                                 pWin);

        osgGlDeleteSamplers(1, &id);
        pWin->setGLObjectId(osgid, 0);

        glErr("SamplerObjChunk::handleDestroyGL");
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last buffer user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "SamplerObjChunk::handleDestroyGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

}

/*------------------------------ tools --------------------------------------*/

void SamplerObjChunk::validate(DrawEnv *pEnv)
{
    pEnv->getWindow()->validateGLObject(this->getGLId(),
                                        pEnv           );
}

Int32 SamplerObjChunk::getOpenGLId(DrawEnv *pEnv)
{
    return pEnv->getWindow()->getGLObjectId(this->getGLId());
}

/*------------------------------ activate -----------------------------------*/

void SamplerObjChunk::activate(DrawEnv *pEnv, UInt32 idx)
{
    Window *pWin = pEnv->getWindow();

    pWin->validateGLObject(getGLId(), pEnv);

    GLuint id = pWin->getGLObjectId(getGLId());

    OSGGETGLFUNCBYID_GL3_ES( glBindSampler,
                             osgGlBindSampler,
                            _funcBindSampler, 
                             pWin);

    MFTextureUnitsType::const_iterator sIt  = getMFTextureUnits()->begin();
    MFTextureUnitsType::const_iterator sEnd = getMFTextureUnits()->end();

    for(; sIt != sEnd; ++sIt)
    {
        UInt32 texUnit = *sIt;

        osgGlBindSampler(texUnit, id);
    }

    glErr("SamplerObjChunk::activate");
}

/*------------------------------ deactivate ---------------------------------*/

void SamplerObjChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
{
    Window *pWin = pEnv->getWindow();

    OSGGETGLFUNCBYID_GL3_ES( glBindSampler,
                             osgGlBindSampler,
                            _funcBindSampler, 
                             pWin);

    MFTextureUnitsType::const_iterator sIt  = getMFTextureUnits()->begin();
    MFTextureUnitsType::const_iterator sEnd = getMFTextureUnits()->end();

    for(; sIt != sEnd; ++sIt)
    {
        UInt32 texUnit = *sIt;

        osgGlBindSampler(texUnit, 0);
    }

    glErr("SamplerObjChunk::deactivate");
}

/*------------------------------ changeFrom ---------------------------------*/

void SamplerObjChunk::changeFrom(DrawEnv    *pEnv,
                                 StateChunk *old,
                                 UInt32      idx )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime.
    // is that a valid assumption?
    if (old == this)
        return;

    old->deactivate(pEnv, idx);
    this->activate(pEnv, idx);
}

OSG_END_NAMESPACE
