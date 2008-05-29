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
 **     class StereoBufferViewport!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESTEREOBUFFERVIEWPORTINST

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "OSGStereoBufferViewportBase.h"
#include "OSGStereoBufferViewport.h"

#include "boost/bind.hpp"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StereoBufferViewport
    \ingroup GrpSystemWindowViewports

    Viewport for quad-buffered stereo rendering, see \ref
    PageSystemWindowViewports for a description.

    The active buffers are selected using the _sfLeftBuffer and _sfRightBuffer
    Fields.
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var bool            StereoBufferViewportBase::_sfLeftBuffer
    Defines whether the left buffer is written to.
*/

/*! \var bool            StereoBufferViewportBase::_sfRightBuffer
    Defines whether the right buffer is written to.
*/


void StereoBufferViewportBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "leftBuffer",
        "Defines whether the left buffer is written to.\n",
        LeftBufferFieldId, LeftBufferFieldMask,
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&StereoBufferViewport::editHandleLeftBuffer),
        static_cast<FieldGetMethodSig >(&StereoBufferViewport::getHandleLeftBuffer));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "rightBuffer",
        "Defines whether the right buffer is written to.\n",
        RightBufferFieldId, RightBufferFieldMask,
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&StereoBufferViewport::editHandleRightBuffer),
        static_cast<FieldGetMethodSig >(&StereoBufferViewport::getHandleRightBuffer));

    oType.addInitialDesc(pDesc);
}


StereoBufferViewportBase::TypeObject StereoBufferViewportBase::_type(
    StereoBufferViewportBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&StereoBufferViewportBase::createEmptyLocal),
    StereoBufferViewport::initMethod,
    StereoBufferViewport::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&StereoBufferViewportBase::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"StereoBufferViewport\"\n"
    "\tparent=\"Viewport\"\n"
    "\tlibrary=\"Window\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    "\tdecoratable=\"false\"\n"
    ">\n"
    "\\ingroup GrpSystemWindowViewports\n"
    "\n"
    "Viewport for quad-buffered stereo rendering, see \\ref\n"
    "PageSystemWindowViewports for a description.\n"
    "\n"
    "The active buffers are selected using the _sfLeftBuffer and _sfRightBuffer\n"
    "Fields.\n"
    "\t<Field\n"
    "\t\tname=\"leftBuffer\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"true\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "        Defines whether the left buffer is written to.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"rightBuffer\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"true\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "        Defines whether the right buffer is written to.\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    "\\ingroup GrpSystemWindowViewports\n"
    "\n"
    "Viewport for quad-buffered stereo rendering, see \\ref\n"
    "PageSystemWindowViewports for a description.\n"
    "\n"
    "The active buffers are selected using the _sfLeftBuffer and _sfRightBuffer\n"
    "Fields.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &StereoBufferViewportBase::getType(void)
{
    return _type;
}

const FieldContainerType &StereoBufferViewportBase::getType(void) const
{
    return _type;
}

UInt32 StereoBufferViewportBase::getContainerSize(void) const
{
    return sizeof(StereoBufferViewport);
}

/*------------------------- decorator get ------------------------------*/


SFBool *StereoBufferViewportBase::editSFLeftBuffer(void)
{
    editSField(LeftBufferFieldMask);

    return &_sfLeftBuffer;
}

const SFBool *StereoBufferViewportBase::getSFLeftBuffer(void) const
{
    return &_sfLeftBuffer;
}

#ifdef OSG_1_GET_COMPAT
SFBool              *StereoBufferViewportBase::getSFLeftBuffer     (void)
{
    return this->editSFLeftBuffer     ();
}
#endif

SFBool *StereoBufferViewportBase::editSFRightBuffer(void)
{
    editSField(RightBufferFieldMask);

    return &_sfRightBuffer;
}

const SFBool *StereoBufferViewportBase::getSFRightBuffer(void) const
{
    return &_sfRightBuffer;
}

#ifdef OSG_1_GET_COMPAT
SFBool              *StereoBufferViewportBase::getSFRightBuffer    (void)
{
    return this->editSFRightBuffer    ();
}
#endif





/*------------------------------ access -----------------------------------*/

UInt32 StereoBufferViewportBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (LeftBufferFieldMask & whichField))
    {
        returnValue += _sfLeftBuffer.getBinSize();
    }
    if(FieldBits::NoField != (RightBufferFieldMask & whichField))
    {
        returnValue += _sfRightBuffer.getBinSize();
    }

    return returnValue;
}

void StereoBufferViewportBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (LeftBufferFieldMask & whichField))
    {
        _sfLeftBuffer.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RightBufferFieldMask & whichField))
    {
        _sfRightBuffer.copyToBin(pMem);
    }
}

void StereoBufferViewportBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (LeftBufferFieldMask & whichField))
    {
        _sfLeftBuffer.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RightBufferFieldMask & whichField))
    {
        _sfRightBuffer.copyFromBin(pMem);
    }
}

//! create a new instance of the class
StereoBufferViewportTransitPtr StereoBufferViewportBase::create(void)
{
    StereoBufferViewportTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<StereoBufferViewport>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
StereoBufferViewportTransitPtr StereoBufferViewportBase::createLocal(BitVector bFlags)
{
    StereoBufferViewportTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<StereoBufferViewport>(tmpPtr);
    }

    return fc;
}

//! create an empty new instance of the class, do not copy the prototype
StereoBufferViewport *StereoBufferViewportBase::createEmpty(void)
{
    StereoBufferViewport *returnValue;

    newPtr<StereoBufferViewport>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &= 
        ~Thread::getCurrentLocalFlags(); 

    return returnValue;
}

StereoBufferViewport *StereoBufferViewportBase::createEmptyLocal(BitVector bFlags)
{
    StereoBufferViewport *returnValue;

    newPtr<StereoBufferViewport>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr StereoBufferViewportBase::shallowCopy(void) const
{
    StereoBufferViewport *tmpPtr;

    newPtr(tmpPtr, 
           dynamic_cast<const StereoBufferViewport *>(this), 
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}

FieldContainerTransitPtr StereoBufferViewportBase::shallowCopyLocal(
    BitVector bFlags) const
{
    StereoBufferViewport *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const StereoBufferViewport *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

StereoBufferViewportBase::StereoBufferViewportBase(void) :
    Inherited(),
    _sfLeftBuffer             (bool(true)),
    _sfRightBuffer            (bool(true))
{
}

StereoBufferViewportBase::StereoBufferViewportBase(const StereoBufferViewportBase &source) :
    Inherited(source),
    _sfLeftBuffer             (source._sfLeftBuffer             ),
    _sfRightBuffer            (source._sfRightBuffer            )
{
}


/*-------------------------- destructors ----------------------------------*/

StereoBufferViewportBase::~StereoBufferViewportBase(void)
{
}


GetFieldHandlePtr StereoBufferViewportBase::getHandleLeftBuffer      (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfLeftBuffer, 
             this->getType().getFieldDesc(LeftBufferFieldId)));

    return returnValue;
}

EditFieldHandlePtr StereoBufferViewportBase::editHandleLeftBuffer     (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfLeftBuffer, 
             this->getType().getFieldDesc(LeftBufferFieldId)));

    editSField(LeftBufferFieldMask);

    return returnValue;
}

GetFieldHandlePtr StereoBufferViewportBase::getHandleRightBuffer     (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfRightBuffer, 
             this->getType().getFieldDesc(RightBufferFieldId)));

    return returnValue;
}

EditFieldHandlePtr StereoBufferViewportBase::editHandleRightBuffer    (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfRightBuffer, 
             this->getType().getFieldDesc(RightBufferFieldId)));

    editSField(RightBufferFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void StereoBufferViewportBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<StereoBufferViewportBase *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *StereoBufferViewportBase::createAspectCopy(void) const
{
    StereoBufferViewport *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const StereoBufferViewport *>(this));

    return returnValue;
}
#endif

void StereoBufferViewportBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<StereoBufferViewport *>::_type("StereoBufferViewportPtr", "ViewportPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(StereoBufferViewport *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           StereoBufferViewport *, 
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           StereoBufferViewport *, 
                           0);

OSG_END_NAMESPACE
