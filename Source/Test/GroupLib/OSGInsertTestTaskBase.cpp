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
 **     class InsertTestTask!
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



#include "OSGCSMWindow.h"               // Window Class

#include "OSGInsertTestTaskBase.h"
#include "OSGInsertTestTask.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::InsertTestTask
    just dumps a message on traversal and render for testing
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var std::string     InsertTestTaskBase::_sfMessage
    
*/

/*! \var CSMWindow *     InsertTestTaskBase::_sfWindow
    
*/

/*! \var OSGAny          InsertTestTaskBase::_sfTrigger
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<InsertTestTask *, nsOSG>::_type(
    "InsertTestTaskPtr", 
    "AttachmentContainerPtr", 
    InsertTestTask::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(InsertTestTask *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void InsertTestTaskBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFString::Description(
        SFString::getClassType(),
        "message",
        "",
        MessageFieldId, MessageFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&InsertTestTask::editHandleMessage),
        static_cast<FieldGetMethodSig >(&InsertTestTask::getHandleMessage));

    oType.addInitialDesc(pDesc);

    pDesc = new SFWeakCSMWindowPtr::Description(
        SFWeakCSMWindowPtr::getClassType(),
        "window",
        "",
        WindowFieldId, WindowFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&InsertTestTask::editHandleWindow),
        static_cast<FieldGetMethodSig >(&InsertTestTask::getHandleWindow));

    oType.addInitialDesc(pDesc);

    pDesc = new SFOSGAny::Description(
        SFOSGAny::getClassType(),
        "trigger",
        "",
        TriggerFieldId, TriggerFieldMask,
        true,
        (Field::FStdAccess | Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&InsertTestTask::editHandleTrigger),
        static_cast<FieldGetMethodSig >(&InsertTestTask::getHandleTrigger));

    oType.addInitialDesc(pDesc);
}


InsertTestTaskBase::TypeObject InsertTestTaskBase::_type(
    InsertTestTaskBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&InsertTestTaskBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&InsertTestTask::initMethod),
    reinterpret_cast<ExitContainerF>(&InsertTestTask::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&InsertTestTask::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"InsertTestTask\"\n"
    "    parent=\"AttachmentContainer\"\n"
    "    library=\"Group\"\n"
    "    pointerfieldtypes=\"none\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    >\n"
    "    just dumps a message on traversal and render for testing\n"
    "    <Field\n"
    "        name=\"message\"\n"
    "        type=\"std::string\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"window\"\n"
    "        type=\"CSMWindow\"\n"
    "        cardinality=\"single\"\n"
    "        category=\"weakpointer\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"trigger\"\n"
    "        type=\"OSGAny\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        access=\"protected\"\n"
    "        defaultValue=\"\"\n"
    "        fieldFlags=\"FStdAccess, FThreadLocal\"\n"
    "        >\n"
    "    </Field>\n"
    "</FieldContainer>\n",
    "just dumps a message on traversal and render for testing\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &InsertTestTaskBase::getType(void)
{
    return _type;
}

const FieldContainerType &InsertTestTaskBase::getType(void) const
{
    return _type;
}

UInt32 InsertTestTaskBase::getContainerSize(void) const
{
    return sizeof(InsertTestTask);
}

/*------------------------- decorator get ------------------------------*/


SFString *InsertTestTaskBase::editSFMessage(void)
{
    editSField(MessageFieldMask);

    return &_sfMessage;
}

const SFString *InsertTestTaskBase::getSFMessage(void) const
{
    return &_sfMessage;
}


//! Get the InsertTestTask::_sfWindow field.
const SFWeakCSMWindowPtr *InsertTestTaskBase::getSFWindow(void) const
{
    return &_sfWindow;
}

SFWeakCSMWindowPtr  *InsertTestTaskBase::editSFWindow         (void)
{
    editSField(WindowFieldMask);

    return &_sfWindow;
}

//! Get the value of the InsertTestTask::_sfWindow field.
CSMWindow * InsertTestTaskBase::getWindow(void) const
{
    return _sfWindow.getValue();
}

//! Set the value of the InsertTestTask::_sfWindow field.
void InsertTestTaskBase::setWindow(CSMWindow * const value)
{
    editSField(WindowFieldMask);

    _sfWindow.setValue(value);
}


SFOSGAny *InsertTestTaskBase::editSFTrigger(void)
{
    editSField(TriggerFieldMask);

    return &_sfTrigger;
}

const SFOSGAny *InsertTestTaskBase::getSFTrigger(void) const
{
    return &_sfTrigger;
}






/*------------------------------ access -----------------------------------*/

SizeT InsertTestTaskBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (MessageFieldMask & whichField))
    {
        returnValue += _sfMessage.getBinSize();
    }
    if(FieldBits::NoField != (WindowFieldMask & whichField))
    {
        returnValue += _sfWindow.getBinSize();
    }
    if(FieldBits::NoField != (TriggerFieldMask & whichField))
    {
        returnValue += _sfTrigger.getBinSize();
    }

    return returnValue;
}

void InsertTestTaskBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (MessageFieldMask & whichField))
    {
        _sfMessage.copyToBin(pMem);
    }
    if(FieldBits::NoField != (WindowFieldMask & whichField))
    {
        _sfWindow.copyToBin(pMem);
    }
    if(FieldBits::NoField != (TriggerFieldMask & whichField))
    {
        _sfTrigger.copyToBin(pMem);
    }
}

void InsertTestTaskBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (MessageFieldMask & whichField))
    {
        editSField(MessageFieldMask);
        _sfMessage.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (WindowFieldMask & whichField))
    {
        editSField(WindowFieldMask);
        _sfWindow.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (TriggerFieldMask & whichField))
    {
        editSField(TriggerFieldMask);
        _sfTrigger.copyFromBin(pMem);
    }
}

//! create a new instance of the class
InsertTestTaskTransitPtr InsertTestTaskBase::createLocal(BitVector bFlags)
{
    InsertTestTaskTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<InsertTestTask>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
InsertTestTaskTransitPtr InsertTestTaskBase::createDependent(BitVector bFlags)
{
    InsertTestTaskTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<InsertTestTask>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
InsertTestTaskTransitPtr InsertTestTaskBase::create(void)
{
    InsertTestTaskTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<InsertTestTask>(tmpPtr);
    }

    return fc;
}

InsertTestTask *InsertTestTaskBase::createEmptyLocal(BitVector bFlags)
{
    InsertTestTask *returnValue;

    newPtr<InsertTestTask>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
InsertTestTask *InsertTestTaskBase::createEmpty(void)
{
    InsertTestTask *returnValue;

    newPtr<InsertTestTask>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr InsertTestTaskBase::shallowCopyLocal(
    BitVector bFlags) const
{
    InsertTestTask *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const InsertTestTask *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr InsertTestTaskBase::shallowCopyDependent(
    BitVector bFlags) const
{
    InsertTestTask *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const InsertTestTask *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr InsertTestTaskBase::shallowCopy(void) const
{
    InsertTestTask *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const InsertTestTask *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

InsertTestTaskBase::InsertTestTaskBase(void) :
    Inherited(),
    _sfMessage                (),
    _sfWindow                 (NULL),
    _sfTrigger                ()
{
}

InsertTestTaskBase::InsertTestTaskBase(const InsertTestTaskBase &source) :
    Inherited(source),
    _sfMessage                (source._sfMessage                ),
    _sfWindow                 (NULL),
    _sfTrigger                (source._sfTrigger                )
{
}


/*-------------------------- destructors ----------------------------------*/

InsertTestTaskBase::~InsertTestTaskBase(void)
{
}

void InsertTestTaskBase::onCreate(const InsertTestTask *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        InsertTestTask *pThis = static_cast<InsertTestTask *>(this);

        pThis->setWindow(source->getWindow());
    }
}

GetFieldHandlePtr InsertTestTaskBase::getHandleMessage         (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfMessage,
             this->getType().getFieldDesc(MessageFieldId),
             const_cast<InsertTestTaskBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr InsertTestTaskBase::editHandleMessage        (void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfMessage,
             this->getType().getFieldDesc(MessageFieldId),
             this));


    editSField(MessageFieldMask);

    return returnValue;
}

GetFieldHandlePtr InsertTestTaskBase::getHandleWindow          (void) const
{
    SFWeakCSMWindowPtr::GetHandlePtr returnValue(
        new  SFWeakCSMWindowPtr::GetHandle(
             &_sfWindow,
             this->getType().getFieldDesc(WindowFieldId),
             const_cast<InsertTestTaskBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr InsertTestTaskBase::editHandleWindow         (void)
{
    SFWeakCSMWindowPtr::EditHandlePtr returnValue(
        new  SFWeakCSMWindowPtr::EditHandle(
             &_sfWindow,
             this->getType().getFieldDesc(WindowFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&InsertTestTask::setWindow,
                    static_cast<InsertTestTask *>(this), _1));

    editSField(WindowFieldMask);

    return returnValue;
}

GetFieldHandlePtr InsertTestTaskBase::getHandleTrigger         (void) const
{
    SFOSGAny::GetHandlePtr returnValue(
        new  SFOSGAny::GetHandle(
             &_sfTrigger,
             this->getType().getFieldDesc(TriggerFieldId),
             const_cast<InsertTestTaskBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr InsertTestTaskBase::editHandleTrigger        (void)
{
    SFOSGAny::EditHandlePtr returnValue(
        new  SFOSGAny::EditHandle(
             &_sfTrigger,
             this->getType().getFieldDesc(TriggerFieldId),
             this));


    editSField(TriggerFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void InsertTestTaskBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    InsertTestTask *pThis = static_cast<InsertTestTask *>(this);

    pThis->execSync(static_cast<InsertTestTask *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *InsertTestTaskBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    InsertTestTask *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const InsertTestTask *>(pRefAspect),
                  dynamic_cast<const InsertTestTask *>(this));

    return returnValue;
}
#endif

void InsertTestTaskBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<InsertTestTask *>(this)->setWindow(NULL);


}


OSG_END_NAMESPACE
