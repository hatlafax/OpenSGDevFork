/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class FrameBufferAttachment!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"




#include "OSGFrameBufferAttachmentBase.h"
#include "OSGFrameBufferAttachment.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FrameBufferAttachment
    FramebufferAttachment base class.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var UInt16          FrameBufferAttachmentBase::_sfWidth
    
*/

/*! \var UInt16          FrameBufferAttachmentBase::_sfHeight
    
*/

/*! \var bool            FrameBufferAttachmentBase::_sfReadBack
    read back the render result into the texture image obj on 
    framebuffer object deactivate
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<FrameBufferAttachment *, nsOSG>::_type("FrameBufferAttachmentPtr", "AttachmentContainerPtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(FrameBufferAttachment *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           FrameBufferAttachment *,
                           nsOSG);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           FrameBufferAttachment *,
                           nsOSG);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void FrameBufferAttachmentBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUInt16::Description(
        SFUInt16::getClassType(),
        "width",
        "",
        WidthFieldId, WidthFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&FrameBufferAttachment::editHandleWidth),
        static_cast<FieldGetMethodSig >(&FrameBufferAttachment::getHandleWidth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt16::Description(
        SFUInt16::getClassType(),
        "height",
        "",
        HeightFieldId, HeightFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&FrameBufferAttachment::editHandleHeight),
        static_cast<FieldGetMethodSig >(&FrameBufferAttachment::getHandleHeight));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "readBack",
        "read back the render result into the texture image obj on \n"
        "framebuffer object deactivate\n",
        ReadBackFieldId, ReadBackFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&FrameBufferAttachment::editHandleReadBack),
        static_cast<FieldGetMethodSig >(&FrameBufferAttachment::getHandleReadBack));

    oType.addInitialDesc(pDesc);
}


FrameBufferAttachmentBase::TypeObject FrameBufferAttachmentBase::_type(
    FrameBufferAttachmentBase::getClassname(),
    Inherited::getClassname(),
    "FrameBufferAttachment",
    nsOSG, //Namespace
    NULL,
    FrameBufferAttachment::initMethod,
    FrameBufferAttachment::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&FrameBufferAttachment::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"FrameBufferAttachment\"\n"
    "   parent=\"AttachmentContainer\"\n"
    "   library=\"System\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   structure=\"abstract\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   docGroupBase=\"GrpSystemWindowFBO\"\n"
    ">\n"
    "FramebufferAttachment base class.\n"
    "\t<Field\n"
    "\t\tname=\"width\"\n"
    "\t\ttype=\"UInt16\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"protected\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"height\"\n"
    "\t\ttype=\"UInt16\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"protected\"\n"
    "\t>\n"
    "\t</Field>\n"
    "    <Field\n"
    "       name=\"readBack\"\n"
    "       type=\"bool\"\n"
    "       cardinality=\"single\"\n"
    "       visibility=\"external\"\n"
    "       access=\"public\"\n"
    "       defaultValue=\"false\"\n"
    "       >\n"
    "      read back the render result into the texture image obj on \n"
    "      framebuffer object deactivate\n"
    "    </Field>\n"
    "</FieldContainer>\n",
    "FramebufferAttachment base class.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &FrameBufferAttachmentBase::getType(void)
{
    return _type;
}

const FieldContainerType &FrameBufferAttachmentBase::getType(void) const
{
    return _type;
}

UInt32 FrameBufferAttachmentBase::getContainerSize(void) const
{
    return sizeof(FrameBufferAttachment);
}

/*------------------------- decorator get ------------------------------*/


SFUInt16 *FrameBufferAttachmentBase::editSFWidth(void)
{
    editSField(WidthFieldMask);

    return &_sfWidth;
}

const SFUInt16 *FrameBufferAttachmentBase::getSFWidth(void) const
{
    return &_sfWidth;
}


SFUInt16 *FrameBufferAttachmentBase::editSFHeight(void)
{
    editSField(HeightFieldMask);

    return &_sfHeight;
}

const SFUInt16 *FrameBufferAttachmentBase::getSFHeight(void) const
{
    return &_sfHeight;
}


SFBool *FrameBufferAttachmentBase::editSFReadBack(void)
{
    editSField(ReadBackFieldMask);

    return &_sfReadBack;
}

const SFBool *FrameBufferAttachmentBase::getSFReadBack(void) const
{
    return &_sfReadBack;
}






/*------------------------------ access -----------------------------------*/

UInt32 FrameBufferAttachmentBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        returnValue += _sfWidth.getBinSize();
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        returnValue += _sfHeight.getBinSize();
    }
    if(FieldBits::NoField != (ReadBackFieldMask & whichField))
    {
        returnValue += _sfReadBack.getBinSize();
    }

    return returnValue;
}

void FrameBufferAttachmentBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        _sfWidth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        _sfHeight.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ReadBackFieldMask & whichField))
    {
        _sfReadBack.copyToBin(pMem);
    }
}

void FrameBufferAttachmentBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        editSField(WidthFieldMask);
        _sfWidth.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        editSField(HeightFieldMask);
        _sfHeight.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ReadBackFieldMask & whichField))
    {
        editSField(ReadBackFieldMask);
        _sfReadBack.copyFromBin(pMem);
    }
}




/*------------------------- constructors ----------------------------------*/

FrameBufferAttachmentBase::FrameBufferAttachmentBase(void) :
    Inherited(),
    _sfWidth                  (),
    _sfHeight                 (),
    _sfReadBack               (bool(false))
{
}

FrameBufferAttachmentBase::FrameBufferAttachmentBase(const FrameBufferAttachmentBase &source) :
    Inherited(source),
    _sfWidth                  (source._sfWidth                  ),
    _sfHeight                 (source._sfHeight                 ),
    _sfReadBack               (source._sfReadBack               )
{
}


/*-------------------------- destructors ----------------------------------*/

FrameBufferAttachmentBase::~FrameBufferAttachmentBase(void)
{
}


GetFieldHandlePtr FrameBufferAttachmentBase::getHandleWidth           (void) const
{
    SFUInt16::GetHandlePtr returnValue(
        new  SFUInt16::GetHandle(
             &_sfWidth,
             this->getType().getFieldDesc(WidthFieldId),
             const_cast<FrameBufferAttachmentBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr FrameBufferAttachmentBase::editHandleWidth          (void)
{
    SFUInt16::EditHandlePtr returnValue(
        new  SFUInt16::EditHandle(
             &_sfWidth,
             this->getType().getFieldDesc(WidthFieldId),
             this));


    editSField(WidthFieldMask);

    return returnValue;
}

GetFieldHandlePtr FrameBufferAttachmentBase::getHandleHeight          (void) const
{
    SFUInt16::GetHandlePtr returnValue(
        new  SFUInt16::GetHandle(
             &_sfHeight,
             this->getType().getFieldDesc(HeightFieldId),
             const_cast<FrameBufferAttachmentBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr FrameBufferAttachmentBase::editHandleHeight         (void)
{
    SFUInt16::EditHandlePtr returnValue(
        new  SFUInt16::EditHandle(
             &_sfHeight,
             this->getType().getFieldDesc(HeightFieldId),
             this));


    editSField(HeightFieldMask);

    return returnValue;
}

GetFieldHandlePtr FrameBufferAttachmentBase::getHandleReadBack        (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfReadBack,
             this->getType().getFieldDesc(ReadBackFieldId),
             const_cast<FrameBufferAttachmentBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr FrameBufferAttachmentBase::editHandleReadBack       (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfReadBack,
             this->getType().getFieldDesc(ReadBackFieldId),
             this));


    editSField(ReadBackFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void FrameBufferAttachmentBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    FrameBufferAttachment *pThis = static_cast<FrameBufferAttachment *>(this);

    pThis->execSync(static_cast<FrameBufferAttachment *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void FrameBufferAttachmentBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
