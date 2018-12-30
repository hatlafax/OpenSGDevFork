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
 **     class VRMLOrientationInterpolator!
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




#include "OSGVRMLOrientationInterpolatorBase.h"
#include "OSGVRMLOrientationInterpolator.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::VRMLOrientationInterpolator
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Quaternion      VRMLOrientationInterpolatorBase::_mfKeyValue
    
*/

/*! \var Quaternion      VRMLOrientationInterpolatorBase::_sfOutValue
    This is VRML's value field.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<VRMLOrientationInterpolator *, nsOSG>::_type(
    "VRMLOrientationInterpolatorPtr", 
    "VRMLInterpolatorPtr", 
    VRMLOrientationInterpolator::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(VRMLOrientationInterpolator *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void VRMLOrientationInterpolatorBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFQuaternion::Description(
        MFQuaternion::getClassType(),
        "keyValue",
        "",
        KeyValueFieldId, KeyValueFieldMask,
        false,
        (Field::FStdAccess | Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&VRMLOrientationInterpolator::editHandleKeyValue),
        static_cast<FieldGetMethodSig >(&VRMLOrientationInterpolator::getHandleKeyValue));

    oType.addInitialDesc(pDesc);

    pDesc = new SFQuaternion::Description(
        SFQuaternion::getClassType(),
        "outValue",
        "This is VRML's value field.\n",
        OutValueFieldId, OutValueFieldMask,
        true,
        (Field::FStdAccess | Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&VRMLOrientationInterpolator::editHandleOutValue),
        static_cast<FieldGetMethodSig >(&VRMLOrientationInterpolator::getHandleOutValue));

    oType.addInitialDesc(pDesc);
}


VRMLOrientationInterpolatorBase::TypeObject VRMLOrientationInterpolatorBase::_type(
    VRMLOrientationInterpolatorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&VRMLOrientationInterpolatorBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&VRMLOrientationInterpolator::initMethod),
    reinterpret_cast<ExitContainerF>(&VRMLOrientationInterpolator::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&VRMLOrientationInterpolator::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"VRMLOrientationInterpolator\"\n"
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
    "        type=\"Quaternion\"\n"
    "        cardinality=\"multi\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"\"\n"
    "        fieldFlags=\"FStdAccess, FThreadLocal\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"outValue\"\n"
    "        type=\"Quaternion\"\n"
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

FieldContainerType &VRMLOrientationInterpolatorBase::getType(void)
{
    return _type;
}

const FieldContainerType &VRMLOrientationInterpolatorBase::getType(void) const
{
    return _type;
}

UInt32 VRMLOrientationInterpolatorBase::getContainerSize(void) const
{
    return sizeof(VRMLOrientationInterpolator);
}

/*------------------------- decorator get ------------------------------*/


MFQuaternion *VRMLOrientationInterpolatorBase::editMFKeyValue(void)
{
    editMField(KeyValueFieldMask, _mfKeyValue);

    return &_mfKeyValue;
}

const MFQuaternion *VRMLOrientationInterpolatorBase::getMFKeyValue(void) const
{
    return &_mfKeyValue;
}


SFQuaternion *VRMLOrientationInterpolatorBase::editSFOutValue(void)
{
    editSField(OutValueFieldMask);

    return &_sfOutValue;
}

const SFQuaternion *VRMLOrientationInterpolatorBase::getSFOutValue(void) const
{
    return &_sfOutValue;
}






/*------------------------------ access -----------------------------------*/

SizeT VRMLOrientationInterpolatorBase::getBinSize(ConstFieldMaskArg whichField)
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

void VRMLOrientationInterpolatorBase::copyToBin(BinaryDataHandler &pMem,
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

void VRMLOrientationInterpolatorBase::copyFromBin(BinaryDataHandler &pMem,
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
VRMLOrientationInterpolatorTransitPtr VRMLOrientationInterpolatorBase::createLocal(BitVector bFlags)
{
    VRMLOrientationInterpolatorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<VRMLOrientationInterpolator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
VRMLOrientationInterpolatorTransitPtr VRMLOrientationInterpolatorBase::createDependent(BitVector bFlags)
{
    VRMLOrientationInterpolatorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<VRMLOrientationInterpolator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
VRMLOrientationInterpolatorTransitPtr VRMLOrientationInterpolatorBase::create(void)
{
    VRMLOrientationInterpolatorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<VRMLOrientationInterpolator>(tmpPtr);
    }

    return fc;
}

VRMLOrientationInterpolator *VRMLOrientationInterpolatorBase::createEmptyLocal(BitVector bFlags)
{
    VRMLOrientationInterpolator *returnValue;

    newPtr<VRMLOrientationInterpolator>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
VRMLOrientationInterpolator *VRMLOrientationInterpolatorBase::createEmpty(void)
{
    VRMLOrientationInterpolator *returnValue;

    newPtr<VRMLOrientationInterpolator>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr VRMLOrientationInterpolatorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    VRMLOrientationInterpolator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const VRMLOrientationInterpolator *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr VRMLOrientationInterpolatorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    VRMLOrientationInterpolator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const VRMLOrientationInterpolator *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr VRMLOrientationInterpolatorBase::shallowCopy(void) const
{
    VRMLOrientationInterpolator *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const VRMLOrientationInterpolator *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

VRMLOrientationInterpolatorBase::VRMLOrientationInterpolatorBase(void) :
    Inherited(),
    _mfKeyValue               (),
    _sfOutValue               ()
{
}

VRMLOrientationInterpolatorBase::VRMLOrientationInterpolatorBase(const VRMLOrientationInterpolatorBase &source) :
    Inherited(source),
    _mfKeyValue               (source._mfKeyValue               ),
    _sfOutValue               (source._sfOutValue               )
{
}


/*-------------------------- destructors ----------------------------------*/

VRMLOrientationInterpolatorBase::~VRMLOrientationInterpolatorBase(void)
{
}


GetFieldHandlePtr VRMLOrientationInterpolatorBase::getHandleKeyValue        (void) const
{
    MFQuaternion::GetHandlePtr returnValue(
        new  MFQuaternion::GetHandle(
             &_mfKeyValue,
             this->getType().getFieldDesc(KeyValueFieldId),
             const_cast<VRMLOrientationInterpolatorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr VRMLOrientationInterpolatorBase::editHandleKeyValue       (void)
{
    MFQuaternion::EditHandlePtr returnValue(
        new  MFQuaternion::EditHandle(
             &_mfKeyValue,
             this->getType().getFieldDesc(KeyValueFieldId),
             this));


    editMField(KeyValueFieldMask, _mfKeyValue);

    return returnValue;
}

GetFieldHandlePtr VRMLOrientationInterpolatorBase::getHandleOutValue        (void) const
{
    SFQuaternion::GetHandlePtr returnValue(
        new  SFQuaternion::GetHandle(
             &_sfOutValue,
             this->getType().getFieldDesc(OutValueFieldId),
             const_cast<VRMLOrientationInterpolatorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr VRMLOrientationInterpolatorBase::editHandleOutValue       (void)
{
    SFQuaternion::EditHandlePtr returnValue(
        new  SFQuaternion::EditHandle(
             &_sfOutValue,
             this->getType().getFieldDesc(OutValueFieldId),
             this));


    editSField(OutValueFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void VRMLOrientationInterpolatorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    VRMLOrientationInterpolator *pThis = static_cast<VRMLOrientationInterpolator *>(this);

    pThis->execSync(static_cast<VRMLOrientationInterpolator *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *VRMLOrientationInterpolatorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    VRMLOrientationInterpolator *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const VRMLOrientationInterpolator *>(pRefAspect),
                  dynamic_cast<const VRMLOrientationInterpolator *>(this));

    return returnValue;
}
#endif

void VRMLOrientationInterpolatorBase::resolveLinks(void)
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
