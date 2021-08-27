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
 **     class LinuxEventOptions!
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




#include "OSGLinuxEventOptionsBase.h"
#include "OSGLinuxEventOptions.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::LinuxEventOptions
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var std::string     LinuxEventOptionsBase::_sfDevice
    
*/

/*! \var Vec3f           LinuxEventOptionsBase::_sfTRange
    
*/

/*! \var Vec3f           LinuxEventOptionsBase::_sfRRange
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<LinuxEventOptions *, nsOSG>::_type(
    "LinuxEventOptionsPtr", 
    "InterfaceOptionsPtr", 
    LinuxEventOptions::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(LinuxEventOptions *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           LinuxEventOptions *,
                           nsOSG)


DataType &FieldTraits< LinuxEventOptions *, nsOSG + 1 >::getType(void)
{
    return FieldTraits<LinuxEventOptions *, nsOSG>::getType();
}


OSG_EXPORT_PTR_SFIELD(ChildPointerSField,
                      LinuxEventOptions *,
                      UnrecordedRefCountPolicy,
                      nsOSG + 1)


/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void LinuxEventOptionsBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFString::Description(
        SFString::getClassType(),
        "device",
        "",
        DeviceFieldId, DeviceFieldMask,
        true,
        (Field::FStdAccess | Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&LinuxEventOptions::editHandleDevice),
        static_cast<FieldGetMethodSig >(&LinuxEventOptions::getHandleDevice));

    oType.addInitialDesc(pDesc);

    pDesc = new SFVec3f::Description(
        SFVec3f::getClassType(),
        "tRange",
        "",
        TRangeFieldId, TRangeFieldMask,
        true,
        (Field::FStdAccess | Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&LinuxEventOptions::editHandleTRange),
        static_cast<FieldGetMethodSig >(&LinuxEventOptions::getHandleTRange));

    oType.addInitialDesc(pDesc);

    pDesc = new SFVec3f::Description(
        SFVec3f::getClassType(),
        "rRange",
        "",
        RRangeFieldId, RRangeFieldMask,
        true,
        (Field::FStdAccess | Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&LinuxEventOptions::editHandleRRange),
        static_cast<FieldGetMethodSig >(&LinuxEventOptions::getHandleRRange));

    oType.addInitialDesc(pDesc);
}


LinuxEventOptionsBase::TypeObject LinuxEventOptionsBase::_type(
    LinuxEventOptionsBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&LinuxEventOptionsBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&LinuxEventOptions::initMethod),
    reinterpret_cast<ExitContainerF>(&LinuxEventOptions::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&LinuxEventOptions::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"LinuxEventOptions\"\n"
    "    parent=\"InterfaceOptions\"\n"
    "    library=\"ContribCSM\"\n"
    "    pointerfieldtypes=\"single\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"true\"\n"
    "    parentFields=\"none\"\n"
    "    childFields=\"single\"\n"
    "    >\n"
    "    <Field\n"
    "        name=\"device\"\n"
    "        type=\"std::string\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"\"\n"
    "        fieldFlags=\"FStdAccess, FThreadLocal\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"tRange\"\n"
    "        type=\"Vec3f\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"\"\n"
    "        fieldFlags=\"FStdAccess, FThreadLocal\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"rRange\"\n"
    "        type=\"Vec3f\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"\"\n"
    "        fieldFlags=\"FStdAccess, FThreadLocal\"\n"
    "        >\n"
    "    </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &LinuxEventOptionsBase::getType(void)
{
    return _type;
}

const FieldContainerType &LinuxEventOptionsBase::getType(void) const
{
    return _type;
}

UInt32 LinuxEventOptionsBase::getContainerSize(void) const
{
    return sizeof(LinuxEventOptions);
}

/*------------------------- decorator get ------------------------------*/


SFString *LinuxEventOptionsBase::editSFDevice(void)
{
    editSField(DeviceFieldMask);

    return &_sfDevice;
}

const SFString *LinuxEventOptionsBase::getSFDevice(void) const
{
    return &_sfDevice;
}


SFVec3f *LinuxEventOptionsBase::editSFTRange(void)
{
    editSField(TRangeFieldMask);

    return &_sfTRange;
}

const SFVec3f *LinuxEventOptionsBase::getSFTRange(void) const
{
    return &_sfTRange;
}


SFVec3f *LinuxEventOptionsBase::editSFRRange(void)
{
    editSField(RRangeFieldMask);

    return &_sfRRange;
}

const SFVec3f *LinuxEventOptionsBase::getSFRRange(void) const
{
    return &_sfRRange;
}






/*------------------------------ access -----------------------------------*/

SizeT LinuxEventOptionsBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (DeviceFieldMask & whichField))
    {
        returnValue += _sfDevice.getBinSize();
    }
    if(FieldBits::NoField != (TRangeFieldMask & whichField))
    {
        returnValue += _sfTRange.getBinSize();
    }
    if(FieldBits::NoField != (RRangeFieldMask & whichField))
    {
        returnValue += _sfRRange.getBinSize();
    }

    return returnValue;
}

void LinuxEventOptionsBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (DeviceFieldMask & whichField))
    {
        _sfDevice.copyToBin(pMem);
    }
    if(FieldBits::NoField != (TRangeFieldMask & whichField))
    {
        _sfTRange.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RRangeFieldMask & whichField))
    {
        _sfRRange.copyToBin(pMem);
    }
}

void LinuxEventOptionsBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (DeviceFieldMask & whichField))
    {
        editSField(DeviceFieldMask);
        _sfDevice.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (TRangeFieldMask & whichField))
    {
        editSField(TRangeFieldMask);
        _sfTRange.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RRangeFieldMask & whichField))
    {
        editSField(RRangeFieldMask);
        _sfRRange.copyFromBin(pMem);
    }
}

//! create a new instance of the class
LinuxEventOptionsTransitPtr LinuxEventOptionsBase::createLocal(BitVector bFlags)
{
    LinuxEventOptionsTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<LinuxEventOptions>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
LinuxEventOptionsTransitPtr LinuxEventOptionsBase::createDependent(BitVector bFlags)
{
    LinuxEventOptionsTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<LinuxEventOptions>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
LinuxEventOptionsTransitPtr LinuxEventOptionsBase::create(void)
{
    return createLocal();
}

LinuxEventOptions *LinuxEventOptionsBase::createEmptyLocal(BitVector bFlags)
{
    LinuxEventOptions *returnValue;

    newPtr<LinuxEventOptions>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
LinuxEventOptions *LinuxEventOptionsBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr LinuxEventOptionsBase::shallowCopyLocal(
    BitVector bFlags) const
{
    LinuxEventOptions *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const LinuxEventOptions *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr LinuxEventOptionsBase::shallowCopyDependent(
    BitVector bFlags) const
{
    LinuxEventOptions *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const LinuxEventOptions *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr LinuxEventOptionsBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

LinuxEventOptionsBase::LinuxEventOptionsBase(void) :
    Inherited(),
    _sfDevice                 (),
    _sfTRange                 (),
    _sfRRange                 ()
{
}

LinuxEventOptionsBase::LinuxEventOptionsBase(const LinuxEventOptionsBase &source) :
    Inherited(source),
    _sfDevice                 (source._sfDevice                 ),
    _sfTRange                 (source._sfTRange                 ),
    _sfRRange                 (source._sfRRange                 )
{
}


/*-------------------------- destructors ----------------------------------*/

LinuxEventOptionsBase::~LinuxEventOptionsBase(void)
{
}


GetFieldHandlePtr LinuxEventOptionsBase::getHandleDevice          (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfDevice,
             this->getType().getFieldDesc(DeviceFieldId),
             const_cast<LinuxEventOptionsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr LinuxEventOptionsBase::editHandleDevice         (void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfDevice,
             this->getType().getFieldDesc(DeviceFieldId),
             this));


    editSField(DeviceFieldMask);

    return returnValue;
}

GetFieldHandlePtr LinuxEventOptionsBase::getHandleTRange          (void) const
{
    SFVec3f::GetHandlePtr returnValue(
        new  SFVec3f::GetHandle(
             &_sfTRange,
             this->getType().getFieldDesc(TRangeFieldId),
             const_cast<LinuxEventOptionsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr LinuxEventOptionsBase::editHandleTRange         (void)
{
    SFVec3f::EditHandlePtr returnValue(
        new  SFVec3f::EditHandle(
             &_sfTRange,
             this->getType().getFieldDesc(TRangeFieldId),
             this));


    editSField(TRangeFieldMask);

    return returnValue;
}

GetFieldHandlePtr LinuxEventOptionsBase::getHandleRRange          (void) const
{
    SFVec3f::GetHandlePtr returnValue(
        new  SFVec3f::GetHandle(
             &_sfRRange,
             this->getType().getFieldDesc(RRangeFieldId),
             const_cast<LinuxEventOptionsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr LinuxEventOptionsBase::editHandleRRange         (void)
{
    SFVec3f::EditHandlePtr returnValue(
        new  SFVec3f::EditHandle(
             &_sfRRange,
             this->getType().getFieldDesc(RRangeFieldId),
             this));


    editSField(RRangeFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void LinuxEventOptionsBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    LinuxEventOptions *pThis = static_cast<LinuxEventOptions *>(this);

    pThis->execSync(static_cast<LinuxEventOptions *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *LinuxEventOptionsBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    LinuxEventOptions *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const LinuxEventOptions *>(pRefAspect),
                  dynamic_cast<const LinuxEventOptions *>(this));

    return returnValue;
}
#endif

void LinuxEventOptionsBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
