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
 **     class KeyValue!
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



#include "OSGFieldContainer.h"          // Value Class

#include "OSGKeyValueBase.h"
#include "OSGKeyValue.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::KeyValue
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var std::string     KeyValueBase::_sfKey
    
*/

/*! \var FieldContainer * KeyValueBase::_sfValue
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<KeyValue *, nsOSG>::_type(
    "KeyValuePtr", 
    "FieldContainerPtr", 
    KeyValue::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(KeyValue *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           KeyValue *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           KeyValue *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void KeyValueBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFString::Description(
        SFString::getClassType(),
        "key",
        "",
        KeyFieldId, KeyFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&KeyValue::editHandleKey),
        static_cast<FieldGetMethodSig >(&KeyValue::getHandleKey));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecFieldContainerPtr::Description(
        SFUnrecFieldContainerPtr::getClassType(),
        "value",
        "",
        ValueFieldId, ValueFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&KeyValue::editHandleValue),
        static_cast<FieldGetMethodSig >(&KeyValue::getHandleValue));

    oType.addInitialDesc(pDesc);
}


KeyValueBase::TypeObject KeyValueBase::_type(
    KeyValueBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&KeyValueBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&KeyValue::initMethod),
    reinterpret_cast<ExitContainerF>(&KeyValue::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&KeyValue::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"KeyValue\"\n"
    "   parent=\"FieldContainer\"\n"
    "   library=\"Base\"\n"
    "   structure=\"concrete\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   docGroupBase=\"GrpBaseFieldContainer\"\n"
    ">\n"
    "  <Field\n"
    "\t name=\"key\"\n"
    "\t type=\"std::string\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t access=\"public\"\n"
    "         defaultValue=\"\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"value\"\n"
    "\t type=\"FieldContainerPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t access=\"public\"\n"
    "         defaultValue=\"NULL\"\n"
    "\t >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &KeyValueBase::getType(void)
{
    return _type;
}

const FieldContainerType &KeyValueBase::getType(void) const
{
    return _type;
}

UInt32 KeyValueBase::getContainerSize(void) const
{
    return sizeof(KeyValue);
}

/*------------------------- decorator get ------------------------------*/


SFString *KeyValueBase::editSFKey(void)
{
    editSField(KeyFieldMask);

    return &_sfKey;
}

const SFString *KeyValueBase::getSFKey(void) const
{
    return &_sfKey;
}


//! Get the KeyValue::_sfValue field.
const SFUnrecFieldContainerPtr *KeyValueBase::getSFValue(void) const
{
    return &_sfValue;
}

SFUnrecFieldContainerPtr *KeyValueBase::editSFValue          (void)
{
    editSField(ValueFieldMask);

    return &_sfValue;
}

//! Get the value of the KeyValue::_sfValue field.
FieldContainer * KeyValueBase::getValue(void) const
{
    return _sfValue.getValue();
}

//! Set the value of the KeyValue::_sfValue field.
void KeyValueBase::setValue(FieldContainer * const value)
{
    editSField(ValueFieldMask);

    _sfValue.setValue(value);
}






/*------------------------------ access -----------------------------------*/

SizeT KeyValueBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (KeyFieldMask & whichField))
    {
        returnValue += _sfKey.getBinSize();
    }
    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        returnValue += _sfValue.getBinSize();
    }

    return returnValue;
}

void KeyValueBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (KeyFieldMask & whichField))
    {
        _sfKey.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyToBin(pMem);
    }
}

void KeyValueBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (KeyFieldMask & whichField))
    {
        editSField(KeyFieldMask);
        _sfKey.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        editSField(ValueFieldMask);
        _sfValue.copyFromBin(pMem);
    }
}

//! create a new instance of the class
KeyValueTransitPtr KeyValueBase::createLocal(BitVector bFlags)
{
    KeyValueTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<KeyValue>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
KeyValueTransitPtr KeyValueBase::createDependent(BitVector bFlags)
{
    KeyValueTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<KeyValue>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
KeyValueTransitPtr KeyValueBase::create(void)
{
    KeyValueTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<KeyValue>(tmpPtr);
    }

    return fc;
}

KeyValue *KeyValueBase::createEmptyLocal(BitVector bFlags)
{
    KeyValue *returnValue;

    newPtr<KeyValue>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
KeyValue *KeyValueBase::createEmpty(void)
{
    KeyValue *returnValue;

    newPtr<KeyValue>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr KeyValueBase::shallowCopyLocal(
    BitVector bFlags) const
{
    KeyValue *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const KeyValue *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr KeyValueBase::shallowCopyDependent(
    BitVector bFlags) const
{
    KeyValue *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const KeyValue *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr KeyValueBase::shallowCopy(void) const
{
    KeyValue *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const KeyValue *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

KeyValueBase::KeyValueBase(void) :
    Inherited(),
    _sfKey                    (),
    _sfValue                  (NULL)
{
}

KeyValueBase::KeyValueBase(const KeyValueBase &source) :
    Inherited(source),
    _sfKey                    (source._sfKey                    ),
    _sfValue                  (NULL)
{
}


/*-------------------------- destructors ----------------------------------*/

KeyValueBase::~KeyValueBase(void)
{
}

void KeyValueBase::onCreate(const KeyValue *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        KeyValue *pThis = static_cast<KeyValue *>(this);

        pThis->setValue(source->getValue());
    }
}

GetFieldHandlePtr KeyValueBase::getHandleKey             (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfKey,
             this->getType().getFieldDesc(KeyFieldId),
             const_cast<KeyValueBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr KeyValueBase::editHandleKey            (void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfKey,
             this->getType().getFieldDesc(KeyFieldId),
             this));


    editSField(KeyFieldMask);

    return returnValue;
}

GetFieldHandlePtr KeyValueBase::getHandleValue           (void) const
{
    SFUnrecFieldContainerPtr::GetHandlePtr returnValue(
        new  SFUnrecFieldContainerPtr::GetHandle(
             &_sfValue,
             this->getType().getFieldDesc(ValueFieldId),
             const_cast<KeyValueBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr KeyValueBase::editHandleValue          (void)
{
    SFUnrecFieldContainerPtr::EditHandlePtr returnValue(
        new  SFUnrecFieldContainerPtr::EditHandle(
             &_sfValue,
             this->getType().getFieldDesc(ValueFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&KeyValue::setValue,
                    static_cast<KeyValue *>(this), _1));

    editSField(ValueFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void KeyValueBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    KeyValue *pThis = static_cast<KeyValue *>(this);

    pThis->execSync(static_cast<KeyValue *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *KeyValueBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    KeyValue *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const KeyValue *>(pRefAspect),
                  dynamic_cast<const KeyValue *>(this));

    return returnValue;
}
#endif

void KeyValueBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<KeyValue *>(this)->setValue(NULL);


}


OSG_END_NAMESPACE
