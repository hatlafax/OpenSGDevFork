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
 **     class FBOBackground!
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



#include "OSGFrameBufferObject.h"       // FrameBufferObject Class

#include "OSGFBOBackgroundBase.h"
#include "OSGFBOBackground.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FBOBackground
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var FrameBufferObject * FBOBackgroundBase::_sfFrameBufferObject
    The FramebufferObject to clear from.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<FBOBackground *, nsOSG>::_type(
    "FBOBackgroundPtr", 
    "BackgroundPtr", 
    FBOBackground::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(FBOBackground *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           FBOBackground *,
                           nsOSG)


/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void FBOBackgroundBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecFrameBufferObjectPtr::Description(
        SFUnrecFrameBufferObjectPtr::getClassType(),
        "frameBufferObject",
        "The FramebufferObject to clear from.\n",
        FrameBufferObjectFieldId, FrameBufferObjectFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&FBOBackground::editHandleFrameBufferObject),
        static_cast<FieldGetMethodSig >(&FBOBackground::getHandleFrameBufferObject));

    oType.addInitialDesc(pDesc);
}


FBOBackgroundBase::TypeObject FBOBackgroundBase::_type(
    FBOBackgroundBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&FBOBackgroundBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&FBOBackground::initMethod),
    reinterpret_cast<ExitContainerF>(&FBOBackground::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&FBOBackground::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"FBOBackground\"\n"
    "   parent=\"Background\"\n"
    "   library=\"Window\"\n"
    "   structure=\"concrete\"\n"
    "   pointerfieldtypes=\"single\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   docGroupBase=\"GrpWindowPassive\"\n"
    "   >\n"
    "  <Field\n"
    "\t  name=\"frameBufferObject\"\n"
    "\t  type=\"FrameBufferObjectPtr\"\n"
    "\t  cardinality=\"single\"\n"
    "\t  visibility=\"external\"\n"
    "\t  access=\"public\"\n"
    "\t  >\n"
    "    The FramebufferObject to clear from.\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &FBOBackgroundBase::getType(void)
{
    return _type;
}

const FieldContainerType &FBOBackgroundBase::getType(void) const
{
    return _type;
}

UInt32 FBOBackgroundBase::getContainerSize(void) const
{
    return sizeof(FBOBackground);
}

/*------------------------- decorator get ------------------------------*/


//! Get the FBOBackground::_sfFrameBufferObject field.
const SFUnrecFrameBufferObjectPtr *FBOBackgroundBase::getSFFrameBufferObject(void) const
{
    return &_sfFrameBufferObject;
}

SFUnrecFrameBufferObjectPtr *FBOBackgroundBase::editSFFrameBufferObject(void)
{
    editSField(FrameBufferObjectFieldMask);

    return &_sfFrameBufferObject;
}

//! Get the value of the FBOBackground::_sfFrameBufferObject field.
FrameBufferObject * FBOBackgroundBase::getFrameBufferObject(void) const
{
    return _sfFrameBufferObject.getValue();
}

//! Set the value of the FBOBackground::_sfFrameBufferObject field.
void FBOBackgroundBase::setFrameBufferObject(FrameBufferObject * const value)
{
    editSField(FrameBufferObjectFieldMask);

    _sfFrameBufferObject.setValue(value);
}






/*------------------------------ access -----------------------------------*/

SizeT FBOBackgroundBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (FrameBufferObjectFieldMask & whichField))
    {
        returnValue += _sfFrameBufferObject.getBinSize();
    }

    return returnValue;
}

void FBOBackgroundBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (FrameBufferObjectFieldMask & whichField))
    {
        _sfFrameBufferObject.copyToBin(pMem);
    }
}

void FBOBackgroundBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (FrameBufferObjectFieldMask & whichField))
    {
        editSField(FrameBufferObjectFieldMask);
        _sfFrameBufferObject.copyFromBin(pMem);
    }
}

//! create a new instance of the class
FBOBackgroundTransitPtr FBOBackgroundBase::createLocal(BitVector bFlags)
{
    FBOBackgroundTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<FBOBackground>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
FBOBackgroundTransitPtr FBOBackgroundBase::createDependent(BitVector bFlags)
{
    FBOBackgroundTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<FBOBackground>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
FBOBackgroundTransitPtr FBOBackgroundBase::create(void)
{
    FBOBackgroundTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<FBOBackground>(tmpPtr);
    }

    return fc;
}

FBOBackground *FBOBackgroundBase::createEmptyLocal(BitVector bFlags)
{
    FBOBackground *returnValue;

    newPtr<FBOBackground>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
FBOBackground *FBOBackgroundBase::createEmpty(void)
{
    FBOBackground *returnValue;

    newPtr<FBOBackground>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr FBOBackgroundBase::shallowCopyLocal(
    BitVector bFlags) const
{
    FBOBackground *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const FBOBackground *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr FBOBackgroundBase::shallowCopyDependent(
    BitVector bFlags) const
{
    FBOBackground *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const FBOBackground *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr FBOBackgroundBase::shallowCopy(void) const
{
    FBOBackground *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const FBOBackground *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

FBOBackgroundBase::FBOBackgroundBase(void) :
    Inherited(),
    _sfFrameBufferObject      (NULL)
{
}

FBOBackgroundBase::FBOBackgroundBase(const FBOBackgroundBase &source) :
    Inherited(source),
    _sfFrameBufferObject      (NULL)
{
}


/*-------------------------- destructors ----------------------------------*/

FBOBackgroundBase::~FBOBackgroundBase(void)
{
}

void FBOBackgroundBase::onCreate(const FBOBackground *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        FBOBackground *pThis = static_cast<FBOBackground *>(this);

        pThis->setFrameBufferObject(source->getFrameBufferObject());
    }
}

GetFieldHandlePtr FBOBackgroundBase::getHandleFrameBufferObject (void) const
{
    SFUnrecFrameBufferObjectPtr::GetHandlePtr returnValue(
        new  SFUnrecFrameBufferObjectPtr::GetHandle(
             &_sfFrameBufferObject,
             this->getType().getFieldDesc(FrameBufferObjectFieldId),
             const_cast<FBOBackgroundBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr FBOBackgroundBase::editHandleFrameBufferObject(void)
{
    SFUnrecFrameBufferObjectPtr::EditHandlePtr returnValue(
        new  SFUnrecFrameBufferObjectPtr::EditHandle(
             &_sfFrameBufferObject,
             this->getType().getFieldDesc(FrameBufferObjectFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&FBOBackground::setFrameBufferObject,
                    static_cast<FBOBackground *>(this), _1));

    editSField(FrameBufferObjectFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void FBOBackgroundBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    FBOBackground *pThis = static_cast<FBOBackground *>(this);

    pThis->execSync(static_cast<FBOBackground *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *FBOBackgroundBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    FBOBackground *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const FBOBackground *>(pRefAspect),
                  dynamic_cast<const FBOBackground *>(this));

    return returnValue;
}
#endif

void FBOBackgroundBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<FBOBackground *>(this)->setFrameBufferObject(NULL);


}


OSG_END_NAMESPACE
