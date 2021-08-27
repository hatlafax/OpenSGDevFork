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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>
#include <boost/bind/bind.hpp>

#include "OSGConfig.h"

#include "OSGGLEXT.h"
#include "OSGWindow.h"

#include "OSGGeoProperty.h"
#include "OSGDrawEnv.h"

#include "OSGGLFuncProtos.h"

#include "OSGConceptPropertyChecks.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeoPropertyBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoProperty.fcd) and
// regenerate the base file.

/*! \fn UInt32  GeoProperty::getFormat    (void)
    Returns the OpenGL type constant identifying the data type of the
    properties values.
*/

/*! \fn UInt32  GeoProperty::getFormatSize(void)
    Returns the size (as a multiple of <code>sizeof(char)</code>) of the data
    type of the properties values.
*/

/*! \fn UInt32  GeoProperty::getStride    (void)
    Returns the stride (the distance between successive values) of the
    properties values.
*/

/*! \fn UInt32  GeoProperty::getDimension (void)
    Returns the number of dimensions a single value of the property has.
*/

/*! \fn UInt32  GeoProperty::size         (void)
    Returns the number of values the property holds.

    \return Size of this property.
*/

/*! \fn UInt8* GeoProperty::getData      (void)
    Returns a pointer to the values stored in this property. This mainly exists
    to pass arrays to OpenGL.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass GeoProperty::_class("GeoProperty", 16, 150);

UInt32 GeoProperty::_extVertexBufferObject = Window::invalidExtensionID;
UInt32 GeoProperty::_extMultitexture       = Window::invalidExtensionID;
UInt32 GeoProperty::_arbVertexProgram      = Window::invalidExtensionID;
UInt32 GeoProperty::_extSecondaryColor     = Window::invalidExtensionID;
UInt32 GeoProperty::_arbInstancedArrays    = Window::invalidExtensionID;

UInt32 GeoProperty::_funcBindBuffer                   = 
    Window::invalidFunctionID;
UInt32 GeoProperty::_funcMapBuffer                    = 
    Window::invalidFunctionID;
UInt32 GeoProperty::_funcUnmapBuffer                  = 
    Window::invalidFunctionID;
UInt32 GeoProperty::_funcBufferData                   = 
    Window::invalidFunctionID;
UInt32 GeoProperty::_funcBufferSubData                = 
    Window::invalidFunctionID;
UInt32 GeoProperty::_funcGenBuffers                   = 
    Window::invalidFunctionID;
UInt32 GeoProperty::_funcDeleteBuffers                = 
    Window::invalidFunctionID;
UInt32 GeoProperty::_funcVertexAttribPointerARB       = 
    Window::invalidFunctionID;
UInt32 GeoProperty::_funcEnableVertexAttribArrayARB   = 
    Window::invalidFunctionID;
UInt32 GeoProperty::_funcDisableVertexAttribArrayARB  = 
    Window::invalidFunctionID;

UInt32 GeoProperty::_funcSecondaryColorPointer        = 
    Window::invalidFunctionID;
UInt32 GeoProperty::_funcClientActiveTextureARB       = 
    Window::invalidFunctionID;
UInt32 GeoProperty::_funcVertexAttribDivisorARB       = 
    Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoProperty::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extVertexBufferObject=
            Window::registerExtension("GL_ARB_vertex_buffer_object");
        
        _funcBindBuffer       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBindBufferARB",   
            _extVertexBufferObject);

        _funcMapBuffer       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glMapBufferARB",   
            _extVertexBufferObject);

        _funcUnmapBuffer     = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glUnmapBufferARB",   
            _extVertexBufferObject);

        _funcBufferData       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBufferDataARB",   
            _extVertexBufferObject);

        _funcBufferSubData    = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBufferSubDataARB",   
            _extVertexBufferObject);

        _funcDeleteBuffers       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glDeleteBuffersARB",   
            _extVertexBufferObject);

        _funcGenBuffers         = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGenBuffersARB",   
            _extVertexBufferObject);

        _arbVertexProgram       = 
            Window::registerExtension("GL_ARB_vertex_program");
        
        _funcVertexAttribPointerARB   = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glVertexAttribPointerARB",
            _arbVertexProgram);

        _funcEnableVertexAttribArrayARB   = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glEnableVertexAttribArrayARB",
            _arbVertexProgram);

        _funcDisableVertexAttribArrayARB   = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glDisableVertexAttribArrayARB",
            _arbVertexProgram);

        _extMultitexture        =
            Window::registerExtension("GL_ARB_multitexture");

        _funcClientActiveTextureARB = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glClientActiveTextureARB",
            _extMultitexture);

        _extSecondaryColor      =
            Window::registerExtension("GL_EXT_secondary_color");
        
        _funcSecondaryColorPointer  = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glSecondaryColorPointerEXT",
            _extSecondaryColor);

        _arbInstancedArrays     =
            Window::registerExtension("GL_ARB_instanced_arrays");

        _funcVertexAttribDivisorARB = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glVertexAttribDivisorARB",
            _arbInstancedArrays);
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoProperty::GeoProperty(void) :
    Inherited()
{
}

GeoProperty::GeoProperty(const GeoProperty &source) :
    Inherited(source)
{
}

GeoProperty::~GeoProperty(void)
{
}


/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *GeoProperty::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void GeoProperty::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
    
    if(0x0000 != (whichField & ~UsageFieldMask))
    {
        if(getGLId() > 0)
        {
            Window::refreshGLObject(getGLId());
        }
    }
}

void GeoProperty::dump(      UInt32    , 
                       const BitVector ) const
{
    SLOG << "GeoProperty:"
         << "Format: "      << getFormat() 
         << " FormatSize: " << getFormatSize()
         << " Stride: "     << getStride()
         << " Dim: "        << getDimension() 
         << " Size: "       << size() << std::endl;
}

/*------------------------------ State ------------------------------------*/


/*! GL object handler
    create the VBO and destroy it
*/

UInt32 GeoProperty::handleGL(DrawEnv                 *pEnv, 
                             UInt32                   id, 
                             Window::GLObjectStatusE  mode,
                             UInt64                   uiOptions)
{
    GLuint  glid;

    Window *pWin = pEnv->getWindow();

    osgSinkUnusedWarning(pWin);

    if(mode == Window::initialize || mode == Window::reinitialize ||
       mode == Window::needrefresh )
    {
        if(mode == Window::initialize)
        {
            OSGGETGLFUNCBYID_GL3_ES( glGenBuffers, 
                                     osgGlGenBuffers,
                                    _funcGenBuffers, 
                                     pWin);

            osgGlGenBuffers(1, &glid);

            pWin->setGLObjectId(id, glid);
        }
        else
        {
            glid = pWin->getGLObjectId(id);
        }

        OSGGETGLFUNCBYID_GL3_ES( glBindBuffer,
                                 osgGlBindBuffer,
                                _funcBindBuffer, 
                                 pWin);

        OSGGETGLFUNCBYID_GL3_ES( glBufferData, 
                                 osgGlBufferData,
                                _funcBufferData, 
                                 pWin);

        OSGGETGLFUNCBYID_GL3_ES( glBufferSubData, 
                                 osgGlBufferSubData,
                                _funcBufferSubData, 
                                 pWin);
        
        osgGlBindBuffer(getBufferType(), glid);

        UInt32 uiBufferSize = getFormatSize() * getDimension() * size32();

        bool   bSizeChanged = (uiBufferSize != pWin->getGLObjectInfo(id));
                             

        if(mode         == Window::initialize   || 
           mode         == Window::reinitialize ||
           bSizeChanged == true                  )
        {
            osgGlBufferData(getBufferType(), 
                            uiBufferSize, 
                            NULL, //getData      (), 
                            getVboUsage  ());

            pWin->setGLObjectInfo(id, uiBufferSize);
        }

        if(getData() != NULL)
        {
            osgGlBufferSubData(getBufferType(),
                               0,
                               uiBufferSize, 
                               getData());
        }

        osgGlBindBuffer(getBufferType(), 0);
    }
    else
    {
        SWARNING << "GeoProperty(" << this << "::handleGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }

    return 0;
}

void GeoProperty::handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode)
{
    GLuint glid;

    Window *pWin = pEnv->getWindow();

    osgSinkUnusedWarning(pWin);

    if(mode == Window::destroy)
    {   
        OSGGETGLFUNCBYID_GL3_ES( glDeleteBuffers, 
                                 osgGlDeleteBuffers,
                                _funcDeleteBuffers, 
                                 pWin);

        glid = pWin->getGLObjectId(id);

        osgGlDeleteBuffers(1, &glid);

        pWin->setGLObjectId(id, 0);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last texture user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "GeoProperty::handleDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
}

/*-------------------------- Comparison -----------------------------------*/

bool GeoProperty::isTransparent(void) const
{
    return false;
}

Real32 GeoProperty::switchCost(StateChunk *)
{
    return 0;
}

bool GeoProperty::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool GeoProperty::operator == (const StateChunk &other) const
{
    GeoProperty const *tother = dynamic_cast<GeoProperty const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return false;
}

bool GeoProperty::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

