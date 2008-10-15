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
 **     class PassiveWindow!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "OSGPassiveWindowBase.h"
#include "OSGPassiveWindow.h"

#include "boost/bind.hpp"

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PassiveWindow
    \ingroup GrpSystemWindowPassive
 */


PassiveWindowBase::TypeObject PassiveWindowBase::_type(
    PassiveWindowBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&PassiveWindowBase::createEmptyLocal),
    PassiveWindow::initMethod,
    PassiveWindow::exitMethod,
    NULL,
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"PassiveWindow\"\n"
    "\tparent=\"Window\"\n"
    "\tlibrary=\"System\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    ">\n"
    "\\ingroup GrpSystemWindowPassive\n"
    "\n"
    "A PassiveWindow is a Window class for integration into other OpenGL\n"
    "programs. See \\ref PageSystemWindowWindowPassive for a description.\n"
    "</FieldContainer>\n",
    "\\ingroup GrpSystemWindowPassive\n"
    "\n"
    "A PassiveWindow is a Window class for integration into other OpenGL\n"
    "programs. See \\ref PageSystemWindowWindowPassive for a description.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &PassiveWindowBase::getType(void)
{
    return _type;
}

const FieldContainerType &PassiveWindowBase::getType(void) const
{
    return _type;
}

UInt32 PassiveWindowBase::getContainerSize(void) const
{
    return sizeof(PassiveWindow);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 PassiveWindowBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void PassiveWindowBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void PassiveWindowBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
PassiveWindowTransitPtr PassiveWindowBase::createLocal(BitVector bFlags)
{
    PassiveWindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<PassiveWindow>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
PassiveWindowTransitPtr PassiveWindowBase::createDependent(BitVector bFlags)
{
    PassiveWindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<PassiveWindow>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
PassiveWindowTransitPtr PassiveWindowBase::create(void)
{
    PassiveWindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<PassiveWindow>(tmpPtr);
    }

    return fc;
}

PassiveWindow *PassiveWindowBase::createEmptyLocal(BitVector bFlags)
{
    PassiveWindow *returnValue;

    newPtr<PassiveWindow>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
PassiveWindow *PassiveWindowBase::createEmpty(void)
{
    PassiveWindow *returnValue;

    newPtr<PassiveWindow>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr PassiveWindowBase::shallowCopyLocal(
    BitVector bFlags) const
{
    PassiveWindow *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const PassiveWindow *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr PassiveWindowBase::shallowCopyDependent(
    BitVector bFlags) const
{
    PassiveWindow *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const PassiveWindow *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr PassiveWindowBase::shallowCopy(void) const
{
    PassiveWindow *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const PassiveWindow *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

PassiveWindowBase::PassiveWindowBase(void) :
    Inherited()
{
}

PassiveWindowBase::PassiveWindowBase(const PassiveWindowBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

PassiveWindowBase::~PassiveWindowBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void PassiveWindowBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    PassiveWindow *pThis = static_cast<PassiveWindow *>(this);

    pThis->execSync(static_cast<PassiveWindow *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *PassiveWindowBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    PassiveWindow *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const PassiveWindow *>(pRefAspect),
                  dynamic_cast<const PassiveWindow *>(this));

    return returnValue;
}
#endif

void PassiveWindowBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<PassiveWindow *>::_type("PassiveWindowPtr", "WindowPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(PassiveWindow *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           PassiveWindow *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           PassiveWindow *,
                           0);

OSG_END_NAMESPACE
