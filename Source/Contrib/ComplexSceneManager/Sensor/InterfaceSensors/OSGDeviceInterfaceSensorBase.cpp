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
 **     class DeviceInterfaceSensor!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"



#include "OSGInterfaceOptions.h"        // Options Class

#include "OSGDeviceInterfaceSensorBase.h"
#include "OSGDeviceInterfaceSensor.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DeviceInterfaceSensor
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var std::string     DeviceInterfaceSensorBase::_sfInterfaceName
    
*/

/*! \var InterfaceOptions * DeviceInterfaceSensorBase::_sfOptions
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<DeviceInterfaceSensor *, nsOSG>::_type("DeviceInterfaceSensorPtr", "NodeCorePtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(DeviceInterfaceSensor *, nsOSG)

DataType &FieldTraits<DeviceInterfaceSensor *, nsOSG + 1 >::getType(void)
{
    return FieldTraits<DeviceInterfaceSensor *, nsOSG>::getType();
}


OSG_SFIELDTYPE_INST(ParentPointerSField,
                    DeviceInterfaceSensor *,
                    NoRefCountPolicy,
                    nsOSG + 1);

OSG_FIELD_DLLEXPORT_DEF3(ParentPointerSField,
                         DeviceInterfaceSensor *,
                         NoRefCountPolicy,
                         nsOSG + 1);


/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void DeviceInterfaceSensorBase::classDescInserter(TypeObject &oType)
{
    Inherited::classDescInserter(oType);

    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFString::Description(
        SFString::getClassType(),
        "interfaceName",
        "",
        InterfaceNameFieldId, InterfaceNameFieldMask,
        true,
        (Field::FStdAccess | Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&DeviceInterfaceSensor::editHandleInterfaceName),
        static_cast<FieldGetMethodSig >(&DeviceInterfaceSensor::getHandleInterfaceName));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecChildInterfaceOptionsPtr::Description(
        SFUnrecChildInterfaceOptionsPtr::getClassType(),
        "options",
        "",
        OptionsFieldId, OptionsFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DeviceInterfaceSensor::editHandleOptions),
        static_cast<FieldGetMethodSig >(&DeviceInterfaceSensor::getHandleOptions));

    oType.addInitialDesc(pDesc);
}


DeviceInterfaceSensorBase::TypeObject DeviceInterfaceSensorBase::_type(
    DeviceInterfaceSensorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    NULL,
    DeviceInterfaceSensor::initMethod,
    DeviceInterfaceSensor::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&DeviceInterfaceSensor::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"DeviceInterfaceSensor\"\n"
    "    parent=\"NodeCore\"\n"
    "    mixinparent=\"NodeCoreSensorParent\"\n"
    "    library=\"ContribCSM\"\n"
    "    pointerfieldtypes=\"none\"\n"
    "    structure=\"abstract\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"false\"\n"
    "    parentFields=\"single\"\n"
    "    >\n"
    "    <Field\n"
    "        name=\"interfaceName\"\n"
    "        type=\"std::string\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"\"\n"
    "        fieldFlags=\"FStdAccess, FThreadLocal\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"options\"\n"
    "        type=\"InterfaceOptions\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        category=\"childpointer\"\n"
    "        childParentType=\"DeviceInterfaceSensor\"\n"
    "        linkParentField=\"Parent\"\n"
    "        >\n"
    "    </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &DeviceInterfaceSensorBase::getType(void)
{
    return _type;
}

const FieldContainerType &DeviceInterfaceSensorBase::getType(void) const
{
    return _type;
}

UInt32 DeviceInterfaceSensorBase::getContainerSize(void) const
{
    return sizeof(DeviceInterfaceSensor);
}

/*------------------------- decorator get ------------------------------*/


SFString *DeviceInterfaceSensorBase::editSFInterfaceName(void)
{
    editSField(InterfaceNameFieldMask);

    return &_sfInterfaceName;
}

const SFString *DeviceInterfaceSensorBase::getSFInterfaceName(void) const
{
    return &_sfInterfaceName;
}


//! Get the DeviceInterfaceSensor::_sfOptions field.
const SFUnrecChildInterfaceOptionsPtr *DeviceInterfaceSensorBase::getSFOptions(void) const
{
    return &_sfOptions;
}

SFUnrecChildInterfaceOptionsPtr *DeviceInterfaceSensorBase::editSFOptions        (void)
{
    editSField(OptionsFieldMask);

    return &_sfOptions;
}





/*------------------------------ access -----------------------------------*/

UInt32 DeviceInterfaceSensorBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (InterfaceNameFieldMask & whichField))
    {
        returnValue += _sfInterfaceName.getBinSize();
    }
    if(FieldBits::NoField != (OptionsFieldMask & whichField))
    {
        returnValue += _sfOptions.getBinSize();
    }

    return returnValue;
}

void DeviceInterfaceSensorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (InterfaceNameFieldMask & whichField))
    {
        _sfInterfaceName.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OptionsFieldMask & whichField))
    {
        _sfOptions.copyToBin(pMem);
    }
}

void DeviceInterfaceSensorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (InterfaceNameFieldMask & whichField))
    {
        editSField(InterfaceNameFieldMask);
        _sfInterfaceName.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OptionsFieldMask & whichField))
    {
        editSField(OptionsFieldMask);
        _sfOptions.copyFromBin(pMem);
    }
}




/*------------------------- constructors ----------------------------------*/

DeviceInterfaceSensorBase::DeviceInterfaceSensorBase(void) :
    Inherited(),
    _sfInterfaceName          (),
    _sfOptions                (this,
                          OptionsFieldId,
                          InterfaceOptions::ParentFieldId)
{
}

DeviceInterfaceSensorBase::DeviceInterfaceSensorBase(const DeviceInterfaceSensorBase &source) :
    Inherited(source),
    _sfInterfaceName          (source._sfInterfaceName          ),
    _sfOptions                (this,
                          OptionsFieldId,
                          InterfaceOptions::ParentFieldId)
{
}


/*-------------------------- destructors ----------------------------------*/

DeviceInterfaceSensorBase::~DeviceInterfaceSensorBase(void)
{
}

/*-------------------------------------------------------------------------*/
/* Child linking                                                           */

bool DeviceInterfaceSensorBase::unlinkChild(
    FieldContainer * const pChild,
    UInt16           const childFieldId)
{
    if(childFieldId == OptionsFieldId)
    {
        InterfaceOptions * pTypedChild =
            dynamic_cast<InterfaceOptions *>(pChild);

        if(pTypedChild != NULL)
        {
            if(_sfOptions.getValue() == pTypedChild)
            {
                editSField(OptionsFieldMask);

                _sfOptions.setValue(NULL);

                return true;
            }

            SWARNING << "Parent (["        << this
                     << "] id ["           << this->getId()
                     << "] type ["         << this->getType().getCName()
                     << "] childFieldId [" << childFieldId
                     << "]) - Child (["    << pChild
                     << "] id ["           << pChild->getId()
                     << "] type ["         << pChild->getType().getCName()
                     << "]): link inconsistent!"
                     << std::endl;

            return false;
        }

        return false;
    }


    return Inherited::unlinkChild(pChild, childFieldId);
}

void DeviceInterfaceSensorBase::onCreate(const DeviceInterfaceSensor *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        DeviceInterfaceSensor *pThis = static_cast<DeviceInterfaceSensor *>(this);

        pThis->setOptions(source->getOptions());
    }
}

GetFieldHandlePtr DeviceInterfaceSensorBase::getHandleInterfaceName   (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfInterfaceName,
             this->getType().getFieldDesc(InterfaceNameFieldId),
             const_cast<DeviceInterfaceSensorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DeviceInterfaceSensorBase::editHandleInterfaceName  (void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfInterfaceName,
             this->getType().getFieldDesc(InterfaceNameFieldId),
             this));


    editSField(InterfaceNameFieldMask);

    return returnValue;
}

GetFieldHandlePtr DeviceInterfaceSensorBase::getHandleOptions         (void) const
{
    SFUnrecChildInterfaceOptionsPtr::GetHandlePtr returnValue(
        new  SFUnrecChildInterfaceOptionsPtr::GetHandle(
             &_sfOptions,
             this->getType().getFieldDesc(OptionsFieldId),
             const_cast<DeviceInterfaceSensorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DeviceInterfaceSensorBase::editHandleOptions        (void)
{
    SFUnrecChildInterfaceOptionsPtr::EditHandlePtr returnValue(
        new  SFUnrecChildInterfaceOptionsPtr::EditHandle(
             &_sfOptions,
             this->getType().getFieldDesc(OptionsFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DeviceInterfaceSensor::setOptions,
                    static_cast<DeviceInterfaceSensor *>(this), _1));

    editSField(OptionsFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void DeviceInterfaceSensorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    DeviceInterfaceSensor *pThis = static_cast<DeviceInterfaceSensor *>(this);

    pThis->execSync(static_cast<DeviceInterfaceSensor *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void DeviceInterfaceSensorBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<DeviceInterfaceSensor *>(this)->setOptions(NULL);


}


OSG_END_NAMESPACE
