/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGImage.h"

#include "OSGDrawEnv.h"

#include "OSGTextureBaseChunk.h"

//#define OSG_DUMP_TEX

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGTextureBaseChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGTextureBaseChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass TextureBaseChunk::_class("Texture", osgMaxTexImages, 20);

volatile UInt16 TextureBaseChunk::_uiChunkCounter = 1;

UInt32 TextureBaseChunk::_arbMultiTex           = Window::invalidExtensionID;
UInt32 TextureBaseChunk::_funcActiveTexture     = Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void TextureBaseChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _arbMultiTex       =
            Window::registerExtension("GL_ARB_multitexture");

        _funcActiveTexture =
            Window::registerFunction (OSG_DLSYM_UNDERSCORE"glActiveTextureARB",
                                      _arbMultiTex);
    }

}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

TextureBaseChunk::TextureBaseChunk(void) :
     Inherited( ),
    _uiChunkId(0)
{
}

TextureBaseChunk::TextureBaseChunk(const TextureBaseChunk &source) :
     Inherited(source),
    _uiChunkId(     0)
{
}

TextureBaseChunk::~TextureBaseChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *TextureBaseChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

/*! React to field changes.
    Note: this function also handles CubeTexture changes, make sure to keep
    it consistent with the cubeTexture specifics
*/

void TextureBaseChunk::changed(ConstFieldMaskArg whichField, 
                               UInt32            origin,
                               BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}


/*----------------------------- onCreate --------------------------------*/

void TextureBaseChunk::onCreate(const TextureBaseChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    _uiChunkId = _uiChunkCounter++;
}

void TextureBaseChunk::onCreateAspect(const TextureBaseChunk *createAspect,
                                      const TextureBaseChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

/*------------------------------ Output ----------------------------------*/

void TextureBaseChunk::dump(      UInt32    uiIndent,
                            const BitVector bvFlags  ) const
{
    Inherited::dump(uiIndent, bvFlags);

    if((bvFlags & TargetFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "target "
             << GLDefineMapper::the()->toString(_sfTarget.getValue())
             << "\n";
    }
}

bool TextureBaseChunk::isCubeTexture(void)
{
    return false;
}

/*------------------------------ State ------------------------------------*/


/*-------------------------- Comparison -----------------------------------*/

