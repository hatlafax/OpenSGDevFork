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
 **     class CoreGLWindow!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "OSGCoreGLWindowBase.h"
#include "OSGCoreGLWindow.h"

#include "boost/bind.hpp"

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CoreGLWindow
    The class for MacOS X CoreGL windows.
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var CGLContextObj   CoreGLWindowBase::_sfContext
    
*/


void CoreGLWindowBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFCGLContextObj::Description(
        SFCGLContextObj::getClassType(),
        "context",
        "",
        ContextFieldId, ContextFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CoreGLWindow::editHandleContext),
        static_cast<FieldGetMethodSig >(&CoreGLWindow::getHandleContext));

    oType.addInitialDesc(pDesc);
}


CoreGLWindowBase::TypeObject CoreGLWindowBase::_type(
    CoreGLWindowBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&CoreGLWindowBase::createEmptyLocal),
    CoreGLWindow::initMethod,
    CoreGLWindow::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&CoreGLWindowBase::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"CoreGLWindow\"\n"
    "\tparent=\"Window\"\n"
    "\tlibrary=\"WindowCoreGL\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    ">\n"
    "The class for MacOS X CoreGL windows.\n"
    "\t<Field\n"
    "\t\tname=\"context\"\n"
    "\t\ttype=\"CGLContextObj\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\tdefaultValue=\"0\"\n"
    "\t\theader=\"OSGCoreGLWindowDataFields.h\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    "The class for MacOS X CoreGL windows.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &CoreGLWindowBase::getType(void)
{
    return _type;
}

const FieldContainerType &CoreGLWindowBase::getType(void) const
{
    return _type;
}

UInt32 CoreGLWindowBase::getContainerSize(void) const
{
    return sizeof(CoreGLWindow);
}

/*------------------------- decorator get ------------------------------*/


SFCGLContextObj *CoreGLWindowBase::editSFContext(void)
{
    editSField(ContextFieldMask);

    return &_sfContext;
}

const SFCGLContextObj *CoreGLWindowBase::getSFContext(void) const
{
    return &_sfContext;
}






/*------------------------------ access -----------------------------------*/

UInt32 CoreGLWindowBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ContextFieldMask & whichField))
    {
        returnValue += _sfContext.getBinSize();
    }

    return returnValue;
}

void CoreGLWindowBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ContextFieldMask & whichField))
    {
        _sfContext.copyToBin(pMem);
    }
}

void CoreGLWindowBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ContextFieldMask & whichField))
    {
        _sfContext.copyFromBin(pMem);
    }
}

//! create a new instance of the class
CoreGLWindowTransitPtr CoreGLWindowBase::createLocal(BitVector bFlags)
{
    CoreGLWindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<CoreGLWindow>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
CoreGLWindowTransitPtr CoreGLWindowBase::createDependent(BitVector bFlags)
{
    CoreGLWindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<CoreGLWindow>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
CoreGLWindowTransitPtr CoreGLWindowBase::create(void)
{
    CoreGLWindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<CoreGLWindow>(tmpPtr);
    }

    return fc;
}

CoreGLWindow *CoreGLWindowBase::createEmptyLocal(BitVector bFlags)
{
    CoreGLWindow *returnValue;

    newPtr<CoreGLWindow>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
CoreGLWindow *CoreGLWindowBase::createEmpty(void)
{
    CoreGLWindow *returnValue;

    newPtr<CoreGLWindow>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr CoreGLWindowBase::shallowCopyLocal(
    BitVector bFlags) const
{
    CoreGLWindow *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CoreGLWindow *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr CoreGLWindowBase::shallowCopyDependent(
    BitVector bFlags) const
{
    CoreGLWindow *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CoreGLWindow *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr CoreGLWindowBase::shallowCopy(void) const
{
    CoreGLWindow *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const CoreGLWindow *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

CoreGLWindowBase::CoreGLWindowBase(void) :
    Inherited(),
    _sfContext                (CGLContextObj(0))
{
}

CoreGLWindowBase::CoreGLWindowBase(const CoreGLWindowBase &source) :
    Inherited(source),
    _sfContext                (source._sfContext                )
{
}


/*-------------------------- destructors ----------------------------------*/

CoreGLWindowBase::~CoreGLWindowBase(void)
{
}


GetFieldHandlePtr CoreGLWindowBase::getHandleContext         (void) const
{
    SFCGLContextObj::GetHandlePtr returnValue(
        new  SFCGLContextObj::GetHandle(
             &_sfContext,
             this->getType().getFieldDesc(ContextFieldId)));

    return returnValue;
}

EditFieldHandlePtr CoreGLWindowBase::editHandleContext        (void)
{
    SFCGLContextObj::EditHandlePtr returnValue(
        new  SFCGLContextObj::EditHandle(
             &_sfContext,
             this->getType().getFieldDesc(ContextFieldId)));


    editSField(ContextFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void CoreGLWindowBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    CoreGLWindow *pThis = static_cast<CoreGLWindow *>(this);

    pThis->execSync(static_cast<CoreGLWindow *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *CoreGLWindowBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    CoreGLWindow *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const CoreGLWindow *>(pRefAspect),
                  dynamic_cast<const CoreGLWindow *>(this));

    return returnValue;
}
#endif

void CoreGLWindowBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<CoreGLWindow *>::_type("CoreGLWindowPtr", "WindowPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(CoreGLWindow *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           CoreGLWindow *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           CoreGLWindow *,
                           0);

OSG_END_NAMESPACE
