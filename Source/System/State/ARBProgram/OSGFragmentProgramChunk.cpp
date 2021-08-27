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

#include "OSGGL.h"
#include "OSGGLEXT.h"

#include "OSGWindow.h"

#include "OSGFragmentProgramChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGFragmentProgramChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGFragmentProgramChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass FragmentProgramChunk::_class("FragmentProgram", 1, 200);

UInt32 FragmentProgramChunk::_arbFragmentProgram = Window::invalidExtensionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FragmentProgramChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _arbFragmentProgram = 
            Window::registerExtension("GL_ARB_fragment_program");
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FragmentProgramChunk::FragmentProgramChunk(void) :
    Inherited()
{
}

FragmentProgramChunk::FragmentProgramChunk(
    const FragmentProgramChunk &source) :

    Inherited(source)
{
}

FragmentProgramChunk::~FragmentProgramChunk(void)
{
}

/*----------------------------- onCreate --------------------------------*/

void FragmentProgramChunk::onCreate(const FragmentProgramChunk *chunk)
{
    Inherited::onCreate(chunk); 

    if(GlobalSystemState == Startup)
        return;

    setGLId(Window::registerGLObject(
                    boost::bind(&FragmentProgramChunk::handleGL, 
                                FragmentProgramChunkMTUncountedPtr(this), 
                                ::boost::placeholders::_1,
                                ::boost::placeholders::_2,
                                ::boost::placeholders::_3,
                                ::boost::placeholders::_4),
                    &FragmentProgramChunk::handleDestroyGL));
}

void FragmentProgramChunk::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *FragmentProgramChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void FragmentProgramChunk::changed(ConstFieldMaskArg whichField, 
                                   UInt32            origin,
                                   BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FragmentProgramChunk::dump(      UInt32    , 
                                const BitVector ) const
{
    SLOG << "Dump FragmentProgramChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

UInt32 FragmentProgramChunk::getExtension(void) const
{
    return _arbFragmentProgram;
}

GLenum FragmentProgramChunk::getTarget(void) const
{
    return GL_FRAGMENT_PROGRAM_ARB;
}

const char *FragmentProgramChunk::getTargetName(void) const
{
    return "Fragment Program";
}

UInt32 FragmentProgramChunk::handleGL(DrawEnv                 *pEnv, 
                                      UInt32                   osgid, 
                                      Window::GLObjectStatusE  mode,
                                      UInt64                   uiOptions)
{
    Inherited::handleGL(pEnv, 
                        osgid,
                        mode, 
                        GL_FRAGMENT_PROGRAM_ARB, 
                        _arbFragmentProgram);

    return 0;
}

void FragmentProgramChunk::handleDestroyGL(DrawEnv                 *pEnv, 
                                           UInt32                   osgid, 
                                           Window::GLObjectStatusE  mode)
{
    Inherited::handleDestroyGL(pEnv, 
                        osgid,
                        mode, 
                        GL_FRAGMENT_PROGRAM_ARB, 
                        _arbFragmentProgram);
}

