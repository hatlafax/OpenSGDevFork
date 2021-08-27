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
 **     class ChunkListHelper!
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



#include "OSGStateChunk.h"              // Chunk Class

#include "OSGChunkListHelperBase.h"
#include "OSGChunkListHelper.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ChunkListHelper
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Int32           ChunkListHelperBase::_sfSlot
    
*/

/*! \var StateChunk *    ChunkListHelperBase::_sfChunk
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<ChunkListHelper *, nsOSG>::_type(
    "ChunkListHelperPtr", 
    "FieldContainerPtr", 
    ChunkListHelper::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(ChunkListHelper *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ChunkListHelper *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ChunkListHelper *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ChunkListHelperBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "slot",
        "",
        SlotFieldId, SlotFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ChunkListHelper::editHandleSlot),
        static_cast<FieldGetMethodSig >(&ChunkListHelper::getHandleSlot));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecStateChunkPtr::Description(
        SFUnrecStateChunkPtr::getClassType(),
        "chunk",
        "",
        ChunkFieldId, ChunkFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ChunkListHelper::editHandleChunk),
        static_cast<FieldGetMethodSig >(&ChunkListHelper::getHandleChunk));

    oType.addInitialDesc(pDesc);
}


ChunkListHelperBase::TypeObject ChunkListHelperBase::_type(
    ChunkListHelperBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&ChunkListHelperBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&ChunkListHelper::initMethod),
    reinterpret_cast<ExitContainerF>(&ChunkListHelper::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&ChunkListHelper::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"ChunkListHelper\"\n"
    "   parent=\"FieldContainer\"\n"
    "   library=\"System\"\n"
    "   structure=\"concrete\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   docGroupBase=\"GrpSystemFieldContainer\"\n"
    ">\n"
    "  <Field\n"
    "\t name=\"slot\"\n"
    "\t type=\"Int32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"chunk\"\n"
    "\t type=\"StateChunkPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "     access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ChunkListHelperBase::getType(void)
{
    return _type;
}

const FieldContainerType &ChunkListHelperBase::getType(void) const
{
    return _type;
}

UInt32 ChunkListHelperBase::getContainerSize(void) const
{
    return sizeof(ChunkListHelper);
}

/*------------------------- decorator get ------------------------------*/


SFInt32 *ChunkListHelperBase::editSFSlot(void)
{
    editSField(SlotFieldMask);

    return &_sfSlot;
}

const SFInt32 *ChunkListHelperBase::getSFSlot(void) const
{
    return &_sfSlot;
}


//! Get the ChunkListHelper::_sfChunk field.
const SFUnrecStateChunkPtr *ChunkListHelperBase::getSFChunk(void) const
{
    return &_sfChunk;
}

SFUnrecStateChunkPtr *ChunkListHelperBase::editSFChunk          (void)
{
    editSField(ChunkFieldMask);

    return &_sfChunk;
}

//! Get the value of the ChunkListHelper::_sfChunk field.
StateChunk * ChunkListHelperBase::getChunk(void) const
{
    return _sfChunk.getValue();
}

//! Set the value of the ChunkListHelper::_sfChunk field.
void ChunkListHelperBase::setChunk(StateChunk * const value)
{
    editSField(ChunkFieldMask);

    _sfChunk.setValue(value);
}






/*------------------------------ access -----------------------------------*/

SizeT ChunkListHelperBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (SlotFieldMask & whichField))
    {
        returnValue += _sfSlot.getBinSize();
    }
    if(FieldBits::NoField != (ChunkFieldMask & whichField))
    {
        returnValue += _sfChunk.getBinSize();
    }

    return returnValue;
}

void ChunkListHelperBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (SlotFieldMask & whichField))
    {
        _sfSlot.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ChunkFieldMask & whichField))
    {
        _sfChunk.copyToBin(pMem);
    }
}

void ChunkListHelperBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (SlotFieldMask & whichField))
    {
        editSField(SlotFieldMask);
        _sfSlot.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ChunkFieldMask & whichField))
    {
        editSField(ChunkFieldMask);
        _sfChunk.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ChunkListHelperTransitPtr ChunkListHelperBase::createLocal(BitVector bFlags)
{
    ChunkListHelperTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ChunkListHelper>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ChunkListHelperTransitPtr ChunkListHelperBase::createDependent(BitVector bFlags)
{
    ChunkListHelperTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ChunkListHelper>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ChunkListHelperTransitPtr ChunkListHelperBase::create(void)
{
    ChunkListHelperTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ChunkListHelper>(tmpPtr);
    }

    return fc;
}

ChunkListHelper *ChunkListHelperBase::createEmptyLocal(BitVector bFlags)
{
    ChunkListHelper *returnValue;

    newPtr<ChunkListHelper>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ChunkListHelper *ChunkListHelperBase::createEmpty(void)
{
    ChunkListHelper *returnValue;

    newPtr<ChunkListHelper>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr ChunkListHelperBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ChunkListHelper *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ChunkListHelper *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ChunkListHelperBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ChunkListHelper *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ChunkListHelper *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ChunkListHelperBase::shallowCopy(void) const
{
    ChunkListHelper *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const ChunkListHelper *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

ChunkListHelperBase::ChunkListHelperBase(void) :
    Inherited(),
    _sfSlot                   (),
    _sfChunk                  (NULL)
{
}

ChunkListHelperBase::ChunkListHelperBase(const ChunkListHelperBase &source) :
    Inherited(source),
    _sfSlot                   (source._sfSlot                   ),
    _sfChunk                  (NULL)
{
}


/*-------------------------- destructors ----------------------------------*/

ChunkListHelperBase::~ChunkListHelperBase(void)
{
}

void ChunkListHelperBase::onCreate(const ChunkListHelper *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        ChunkListHelper *pThis = static_cast<ChunkListHelper *>(this);

        pThis->setChunk(source->getChunk());
    }
}

GetFieldHandlePtr ChunkListHelperBase::getHandleSlot            (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfSlot,
             this->getType().getFieldDesc(SlotFieldId),
             const_cast<ChunkListHelperBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ChunkListHelperBase::editHandleSlot           (void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfSlot,
             this->getType().getFieldDesc(SlotFieldId),
             this));


    editSField(SlotFieldMask);

    return returnValue;
}

GetFieldHandlePtr ChunkListHelperBase::getHandleChunk           (void) const
{
    SFUnrecStateChunkPtr::GetHandlePtr returnValue(
        new  SFUnrecStateChunkPtr::GetHandle(
             &_sfChunk,
             this->getType().getFieldDesc(ChunkFieldId),
             const_cast<ChunkListHelperBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ChunkListHelperBase::editHandleChunk          (void)
{
    SFUnrecStateChunkPtr::EditHandlePtr returnValue(
        new  SFUnrecStateChunkPtr::EditHandle(
             &_sfChunk,
             this->getType().getFieldDesc(ChunkFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ChunkListHelper::setChunk,
                    static_cast<ChunkListHelper *>(this), ::boost::placeholders::_1));

    editSField(ChunkFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ChunkListHelperBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ChunkListHelper *pThis = static_cast<ChunkListHelper *>(this);

    pThis->execSync(static_cast<ChunkListHelper *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ChunkListHelperBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ChunkListHelper *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ChunkListHelper *>(pRefAspect),
                  dynamic_cast<const ChunkListHelper *>(this));

    return returnValue;
}
#endif

void ChunkListHelperBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<ChunkListHelper *>(this)->setChunk(NULL);


}


OSG_END_NAMESPACE
