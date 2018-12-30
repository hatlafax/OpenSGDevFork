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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class Background!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#ifdef WIN32 
#pragma warning(disable: 4355) // turn off 'this' : used in base member initializer list warning
#pragma warning(disable: 4290) // disable exception specification warning
#endif

#include "OSGConfig.h"




#include "OSGBackgroundBase.h"
#include "OSGBackground.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Background
    Background is the base class for all background/buffer clearing.  See \ref
    PageSystemWindowBackground for a description.

    \ext

    To create a new Background the method that has be overridden is
    clear(DrawActionBase * action, Viewport * port);. It can directly call OpenGL
    commands, but should restore the state after it's done.

    \endext
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Int32           BackgroundBase::_sfClearStencilBit
    Usually 0 is used to clear all stencil bitplanes 
    (clear is deactivated if smaller zero).
*/

/*! \var Real32          BackgroundBase::_sfDepth
    Depth value for clear, defaults to 1.
*/

/*! \var bool            BackgroundBase::_sfClearDepth
    Whether to clear the depth buffer or not
*/

/*! \var bool            BackgroundBase::_sfClearColor
    Whether to clear the color buffer or not
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<Background *, nsOSG>::_type(
    "BackgroundPtr", 
    "AttachmentContainerPtr", 
    Background::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(Background *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           Background *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           Background *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void BackgroundBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "clearStencilBit",
        "Usually 0 is used to clear all stencil bitplanes \n"
        "(clear is deactivated if smaller zero).\n",
        ClearStencilBitFieldId, ClearStencilBitFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&Background::editHandleClearStencilBit),
        static_cast<FieldGetMethodSig >(&Background::getHandleClearStencilBit));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "depth",
        "Depth value for clear, defaults to 1.\n",
        DepthFieldId, DepthFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&Background::editHandleDepth),
        static_cast<FieldGetMethodSig >(&Background::getHandleDepth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "clearDepth",
        "Whether to clear the depth buffer or not\n",
        ClearDepthFieldId, ClearDepthFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&Background::editHandleClearDepth),
        static_cast<FieldGetMethodSig >(&Background::getHandleClearDepth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "clearColor",
        "Whether to clear the color buffer or not\n",
        ClearColorFieldId, ClearColorFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&Background::editHandleClearColor),
        static_cast<FieldGetMethodSig >(&Background::getHandleClearColor));

    oType.addInitialDesc(pDesc);
}


BackgroundBase::TypeObject BackgroundBase::_type(
    BackgroundBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    NULL,
    reinterpret_cast<InitContainerF>(&Background::initMethod),
    reinterpret_cast<ExitContainerF>(&Background::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&Background::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"Background\"\n"
    "   parent=\"AttachmentContainer\"\n"
    "   library=\"System\"\n"
    "   structure=\"abstract\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   docGroupBase=\"GrpSystemWindow\"\n"
    "   >\n"
    "\n"
    "  Background is the base class for all background/buffer clearing.  See \\ref\n"
    "  PageSystemWindowBackground for a description.\n"
    "\n"
    "  \\ext\n"
    "\n"
    "  To create a new Background the method that has be overridden is\n"
    "  clear(DrawActionBase * action, Viewport * port);. It can directly call OpenGL\n"
    "  commands, but should restore the state after it's done.\n"
    "  \n"
    "  \\endext\n"
    "\n"
    "  <Field\n"
    " \t name=\"clearStencilBit\"\n"
    " \t type=\"Int32\"\n"
    " \t cardinality=\"single\"\n"
    " \t visibility=\"external\"\n"
    " \t defaultValue=\"-1\"\n"
    " \t access=\"public\"\n"
    " \t >\n"
    " \tUsually 0 is used to clear all stencil bitplanes \n"
    "    (clear is deactivated if smaller zero).\n"
    "  </Field>\n"
    "  <Field\n"
    " \t name=\"depth\"\n"
    " \t type=\"Real32\"\n"
    " \t cardinality=\"single\"\n"
    " \t visibility=\"external\"\n"
    " \t defaultValue=\"1.f\"\n"
    " \t access=\"public\"\n"
    " \t >\n"
    " \tDepth value for clear, defaults to 1.\n"
    "  </Field>\n"
    "  <Field\n"
    "     name=\"clearDepth\"\n"
    "     type=\"bool\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     defaultValue=\"true\"\n"
    "     access=\"public\"\n"
    "    >\n"
    "    Whether to clear the depth buffer or not\n"
    "  </Field>\n"
    "  <Field\n"
    "     name=\"clearColor\"\n"
    "     type=\"bool\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     defaultValue=\"true\"\n"
    "     access=\"public\"\n"
    "     >\n"
    "    Whether to clear the color buffer or not\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    "Background is the base class for all background/buffer clearing.  See \\ref\n"
    "PageSystemWindowBackground for a description.\n"
    "\n"
    "\\ext\n"
    "\n"
    "To create a new Background the method that has be overridden is\n"
    "clear(DrawActionBase * action, Viewport * port);. It can directly call OpenGL\n"
    "commands, but should restore the state after it's done.\n"
    "\n"
    "\\endext\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &BackgroundBase::getType(void)
{
    return _type;
}

const FieldContainerType &BackgroundBase::getType(void) const
{
    return _type;
}

UInt32 BackgroundBase::getContainerSize(void) const
{
    return sizeof(Background);
}

/*------------------------- decorator get ------------------------------*/


SFInt32 *BackgroundBase::editSFClearStencilBit(void)
{
    editSField(ClearStencilBitFieldMask);

    return &_sfClearStencilBit;
}

const SFInt32 *BackgroundBase::getSFClearStencilBit(void) const
{
    return &_sfClearStencilBit;
}


SFReal32 *BackgroundBase::editSFDepth(void)
{
    editSField(DepthFieldMask);

    return &_sfDepth;
}

const SFReal32 *BackgroundBase::getSFDepth(void) const
{
    return &_sfDepth;
}


SFBool *BackgroundBase::editSFClearDepth(void)
{
    editSField(ClearDepthFieldMask);

    return &_sfClearDepth;
}

const SFBool *BackgroundBase::getSFClearDepth(void) const
{
    return &_sfClearDepth;
}


SFBool *BackgroundBase::editSFClearColor(void)
{
    editSField(ClearColorFieldMask);

    return &_sfClearColor;
}

const SFBool *BackgroundBase::getSFClearColor(void) const
{
    return &_sfClearColor;
}






/*------------------------------ access -----------------------------------*/

SizeT BackgroundBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ClearStencilBitFieldMask & whichField))
    {
        returnValue += _sfClearStencilBit.getBinSize();
    }
    if(FieldBits::NoField != (DepthFieldMask & whichField))
    {
        returnValue += _sfDepth.getBinSize();
    }
    if(FieldBits::NoField != (ClearDepthFieldMask & whichField))
    {
        returnValue += _sfClearDepth.getBinSize();
    }
    if(FieldBits::NoField != (ClearColorFieldMask & whichField))
    {
        returnValue += _sfClearColor.getBinSize();
    }

    return returnValue;
}

void BackgroundBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ClearStencilBitFieldMask & whichField))
    {
        _sfClearStencilBit.copyToBin(pMem);
    }
    if(FieldBits::NoField != (DepthFieldMask & whichField))
    {
        _sfDepth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ClearDepthFieldMask & whichField))
    {
        _sfClearDepth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ClearColorFieldMask & whichField))
    {
        _sfClearColor.copyToBin(pMem);
    }
}

void BackgroundBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ClearStencilBitFieldMask & whichField))
    {
        editSField(ClearStencilBitFieldMask);
        _sfClearStencilBit.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (DepthFieldMask & whichField))
    {
        editSField(DepthFieldMask);
        _sfDepth.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ClearDepthFieldMask & whichField))
    {
        editSField(ClearDepthFieldMask);
        _sfClearDepth.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ClearColorFieldMask & whichField))
    {
        editSField(ClearColorFieldMask);
        _sfClearColor.copyFromBin(pMem);
    }
}




/*------------------------- constructors ----------------------------------*/

BackgroundBase::BackgroundBase(void) :
    Inherited(),
    _sfClearStencilBit        (Int32(-1)),
    _sfDepth                  (Real32(1.f)),
    _sfClearDepth             (bool(true)),
    _sfClearColor             (bool(true))
{
}

BackgroundBase::BackgroundBase(const BackgroundBase &source) :
    Inherited(source),
    _sfClearStencilBit        (source._sfClearStencilBit        ),
    _sfDepth                  (source._sfDepth                  ),
    _sfClearDepth             (source._sfClearDepth             ),
    _sfClearColor             (source._sfClearColor             )
{
}


/*-------------------------- destructors ----------------------------------*/

BackgroundBase::~BackgroundBase(void)
{
}


GetFieldHandlePtr BackgroundBase::getHandleClearStencilBit (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfClearStencilBit,
             this->getType().getFieldDesc(ClearStencilBitFieldId),
             const_cast<BackgroundBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr BackgroundBase::editHandleClearStencilBit(void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfClearStencilBit,
             this->getType().getFieldDesc(ClearStencilBitFieldId),
             this));


    editSField(ClearStencilBitFieldMask);

    return returnValue;
}

GetFieldHandlePtr BackgroundBase::getHandleDepth           (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfDepth,
             this->getType().getFieldDesc(DepthFieldId),
             const_cast<BackgroundBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr BackgroundBase::editHandleDepth          (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfDepth,
             this->getType().getFieldDesc(DepthFieldId),
             this));


    editSField(DepthFieldMask);

    return returnValue;
}

GetFieldHandlePtr BackgroundBase::getHandleClearDepth      (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfClearDepth,
             this->getType().getFieldDesc(ClearDepthFieldId),
             const_cast<BackgroundBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr BackgroundBase::editHandleClearDepth     (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfClearDepth,
             this->getType().getFieldDesc(ClearDepthFieldId),
             this));


    editSField(ClearDepthFieldMask);

    return returnValue;
}

GetFieldHandlePtr BackgroundBase::getHandleClearColor      (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfClearColor,
             this->getType().getFieldDesc(ClearColorFieldId),
             const_cast<BackgroundBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr BackgroundBase::editHandleClearColor     (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfClearColor,
             this->getType().getFieldDesc(ClearColorFieldId),
             this));


    editSField(ClearColorFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void BackgroundBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Background *pThis = static_cast<Background *>(this);

    pThis->execSync(static_cast<Background *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void BackgroundBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
