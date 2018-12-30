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
 **     class VRMLScalarInterpolator!
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




#include "OSGVRMLScalarInterpolatorBase.h"
#include "OSGVRMLScalarInterpolator.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::VRMLScalarInterpolator
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Real32          VRMLScalarInterpolatorBase::_mfKeyValue
    
*/

/*! \var Real32          VRMLScalarInterpolatorBase::_sfOutValue
    This is VRML's value field.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<VRMLScalarInterpolator *, nsOSG>::_type(
    "VRMLScalarInterpolatorPtr", 
    "VRMLInterpolatorPtr", 
    VRMLScalarInterpolator::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(VRMLScalarInterpolator *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void VRMLScalarInterpolatorBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFReal32::Description(
        MFReal32::getClassType(),
        "keyValue",
        "",
        KeyValueFieldId, KeyValueFieldMask,
        false,
        (Field::FStdAccess | Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&VRMLScalarInterpolator::editHandleKeyValue),
        static_cast<FieldGetMethodSig >(&VRMLScalarInterpolator::getHandleKeyValue));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "outValue",
        "This is VRML's value field.\n",
        OutValueFieldId, OutValueFieldMask,
        true,
        (Field::FStdAccess | Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&VRMLScalarInterpolator::editHandleOutValue),
        static_cast<FieldGetMethodSig >(&VRMLScalarInterpolator::getHandleOutValue));

    oType.addInitialDesc(pDesc);
}


VRMLScalarInterpolatorBase::TypeObject VRMLScalarInterpolatorBase::_type(
    VRMLScalarInterpolatorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&VRMLScalarInterpolatorBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&VRMLScalarInterpolator::initMethod),
    reinterpret_cast<ExitContainerF>(&VRMLScalarInterpolator::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&VRMLScalarInterpolator::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"VRMLScalarInterpolator\"\n"
    "    parent=\"VRMLInterpolator\"\n"
    "    library=\"Dynamics\"\n"
    "    pointerfieldtypes=\"none\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"true\"\n"
    "    isBundle=\"false\"\n"
    "    parentFields=\"none\"\n"
    "    docGroupBase=\"GrpDynamicsVRMLAnimation\"\n"
    "    >\n"
    "    <Field\n"
    "        name=\"keyValue\"\n"
    "        type=\"Real32\"\n"
    "        cardinality=\"multi\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"\"\n"
    "        fieldFlags=\"FStdAccess, FThreadLocal\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"outValue\"\n"
    "        type=\"Real32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"\"\n"
    "        fieldFlags=\"FStdAccess, FThreadLocal\"\n"
    "        >\n"
    "        This is VRML's value field.\n"
    "    </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &VRMLScalarInterpolatorBase::getType(void)
{
    return _type;
}

const FieldContainerType &VRMLScalarInterpolatorBase::getType(void) const
{
    return _type;
}

UInt32 VRMLScalarInterpolatorBase::getContainerSize(void) const
{
    return sizeof(VRMLScalarInterpolator);
}

/*------------------------- decorator get ------------------------------*/


MFReal32 *VRMLScalarInterpolatorBase::editMFKeyValue(void)
{
    editMField(KeyValueFieldMask, _mfKeyValue);

    return &_mfKeyValue;
}

const MFReal32 *VRMLScalarInterpolatorBase::getMFKeyValue(void) const
{
    return &_mfKeyValue;
}


SFReal32 *VRMLScalarInterpolatorBase::editSFOutValue(void)
{
    editSField(OutValueFieldMask);

    return &_sfOutValue;
}

const SFReal32 *VRMLScalarInterpolatorBase::getSFOutValue(void) const
{
    return &_sfOutValue;
}






/*------------------------------ access -----------------------------------*/

SizeT VRMLScalarInterpolatorBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (KeyValueFieldMask & whichField))
    {
        returnValue += _mfKeyValue.getBinSize();
    }
    if(FieldBits::NoField != (OutValueFieldMask & whichField))
    {
        returnValue += _sfOutValue.getBinSize();
    }

    return returnValue;
}

void VRMLScalarInterpolatorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (KeyValueFieldMask & whichField))
    {
        _mfKeyValue.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OutValueFieldMask & whichField))
    {
        _sfOutValue.copyToBin(pMem);
    }
}

void VRMLScalarInterpolatorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (KeyValueFieldMask & whichField))
    {
        editMField(KeyValueFieldMask, _mfKeyValue);
        _mfKeyValue.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OutValueFieldMask & whichField))
    {
        editSField(OutValueFieldMask);
        _sfOutValue.copyFromBin(pMem);
    }
}

//! create a new instance of the class
VRMLScalarInterpolatorTransitPtr VRMLScalarInterpolatorBase::createLocal(BitVector bFlags)
{
    VRMLScalarInterpolatorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<VRMLScalarInterpolator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
VRMLScalarInterpolatorTransitPtr VRMLScalarInterpolatorBase::createDependent(BitVector bFlags)
{
    VRMLScalarInterpolatorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<VRMLScalarInterpolator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
VRMLScalarInterpolatorTransitPtr VRMLScalarInterpolatorBase::create(void)
{
    VRMLScalarInterpolatorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<VRMLScalarInterpolator>(tmpPtr);
    }

    return fc;
}

VRMLScalarInterpolator *VRMLScalarInterpolatorBase::createEmptyLocal(BitVector bFlags)
{
    VRMLScalarInterpolator *returnValue;

    newPtr<VRMLScalarInterpolator>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
VRMLScalarInterpolator *VRMLScalarInterpolatorBase::createEmpty(void)
{
    VRMLScalarInterpolator *returnValue;

    newPtr<VRMLScalarInterpolator>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr VRMLScalarInterpolatorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    VRMLScalarInterpolator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const VRMLScalarInterpolator *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr VRMLScalarInterpolatorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    VRMLScalarInterpolator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const VRMLScalarInterpolator *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr VRMLScalarInterpolatorBase::shallowCopy(void) const
{
    VRMLScalarInterpolator *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const VRMLScalarInterpolator *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

VRMLScalarInterpolatorBase::VRMLScalarInterpolatorBase(void) :
    Inherited(),
    _mfKeyValue               (),
    _sfOutValue               ()
{
}

VRMLScalarInterpolatorBase::VRMLScalarInterpolatorBase(const VRMLScalarInterpolatorBase &source) :
    Inherited(source),
    _mfKeyValue               (source._mfKeyValue               ),
    _sfOutValue               (source._sfOutValue               )
{
}


/*-------------------------- destructors ----------------------------------*/

VRMLScalarInterpolatorBase::~VRMLScalarInterpolatorBase(void)
{
}


GetFieldHandlePtr VRMLScalarInterpolatorBase::getHandleKeyValue        (void) const
{
    MFReal32::GetHandlePtr returnValue(
        new  MFReal32::GetHandle(
             &_mfKeyValue,
             this->getType().getFieldDesc(KeyValueFieldId),
             const_cast<VRMLScalarInterpolatorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr VRMLScalarInterpolatorBase::editHandleKeyValue       (void)
{
    MFReal32::EditHandlePtr returnValue(
        new  MFReal32::EditHandle(
             &_mfKeyValue,
             this->getType().getFieldDesc(KeyValueFieldId),
             this));


    editMField(KeyValueFieldMask, _mfKeyValue);

    return returnValue;
}

GetFieldHandlePtr VRMLScalarInterpolatorBase::getHandleOutValue        (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfOutValue,
             this->getType().getFieldDesc(OutValueFieldId),
             const_cast<VRMLScalarInterpolatorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr VRMLScalarInterpolatorBase::editHandleOutValue       (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfOutValue,
             this->getType().getFieldDesc(OutValueFieldId),
             this));


    editSField(OutValueFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void VRMLScalarInterpolatorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    VRMLScalarInterpolator *pThis = static_cast<VRMLScalarInterpolator *>(this);

    pThis->execSync(static_cast<VRMLScalarInterpolator *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *VRMLScalarInterpolatorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    VRMLScalarInterpolator *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const VRMLScalarInterpolator *>(pRefAspect),
                  dynamic_cast<const VRMLScalarInterpolator *>(this));

    return returnValue;
}
#endif

void VRMLScalarInterpolatorBase::resolveLinks(void)
{
    Inherited::resolveLinks();

#ifdef OSG_MT_CPTR_ASPECT
    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);
#endif

#ifdef OSG_MT_CPTR_ASPECT
    _mfKeyValue.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
}


OSG_END_NAMESPACE
