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
 **     class OffCenterPerspectiveCamera!
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




#include "OSGOffCenterPerspectiveCameraBase.h"
#include "OSGOffCenterPerspectiveCamera.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::OffCenterPerspectiveCamera
    A generalized perspective camera for an asymmetric frustum.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Vec2f           OffCenterPerspectiveCameraBase::_sfPrincipalPoint
    The relative position of the principal point.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<OffCenterPerspectiveCamera *, nsOSG>::_type(
    "OffCenterPerspectiveCameraPtr", 
    "PerspectiveCameraPtr", 
    OffCenterPerspectiveCamera::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(OffCenterPerspectiveCamera *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           OffCenterPerspectiveCamera *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           OffCenterPerspectiveCamera *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void OffCenterPerspectiveCameraBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFVec2f::Description(
        SFVec2f::getClassType(),
        "principalPoint",
        "The relative position of the principal point.\n",
        PrincipalPointFieldId, PrincipalPointFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&OffCenterPerspectiveCamera::editHandlePrincipalPoint),
        static_cast<FieldGetMethodSig >(&OffCenterPerspectiveCamera::getHandlePrincipalPoint));

    oType.addInitialDesc(pDesc);
}


OffCenterPerspectiveCameraBase::TypeObject OffCenterPerspectiveCameraBase::_type(
    OffCenterPerspectiveCameraBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&OffCenterPerspectiveCameraBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&OffCenterPerspectiveCamera::initMethod),
    reinterpret_cast<ExitContainerF>(&OffCenterPerspectiveCamera::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&OffCenterPerspectiveCamera::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"OffCenterPerspectiveCamera\"\n"
    "   parent=\"PerspectiveCamera\"\n"
    "   library=\"Window\"\n"
    "   structure=\"concrete\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   docGroupBase=\"GrpWindowCamera\"\n"
    "   >\n"
    "  A generalized perspective camera for an asymmetric frustum.\n"
    "  <Field\n"
    "\t name=\"principalPoint\"\n"
    "\t type=\"Vec2f\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "     defaultValue=\"0,0\"\n"
    "\t >\n"
    "\tThe relative position of the principal point.\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    "A generalized perspective camera for an asymmetric frustum.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &OffCenterPerspectiveCameraBase::getType(void)
{
    return _type;
}

const FieldContainerType &OffCenterPerspectiveCameraBase::getType(void) const
{
    return _type;
}

UInt32 OffCenterPerspectiveCameraBase::getContainerSize(void) const
{
    return sizeof(OffCenterPerspectiveCamera);
}

/*------------------------- decorator get ------------------------------*/


SFVec2f *OffCenterPerspectiveCameraBase::editSFPrincipalPoint(void)
{
    editSField(PrincipalPointFieldMask);

    return &_sfPrincipalPoint;
}

const SFVec2f *OffCenterPerspectiveCameraBase::getSFPrincipalPoint(void) const
{
    return &_sfPrincipalPoint;
}






/*------------------------------ access -----------------------------------*/

SizeT OffCenterPerspectiveCameraBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (PrincipalPointFieldMask & whichField))
    {
        returnValue += _sfPrincipalPoint.getBinSize();
    }

    return returnValue;
}

void OffCenterPerspectiveCameraBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (PrincipalPointFieldMask & whichField))
    {
        _sfPrincipalPoint.copyToBin(pMem);
    }
}

void OffCenterPerspectiveCameraBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (PrincipalPointFieldMask & whichField))
    {
        editSField(PrincipalPointFieldMask);
        _sfPrincipalPoint.copyFromBin(pMem);
    }
}

//! create a new instance of the class
OffCenterPerspectiveCameraTransitPtr OffCenterPerspectiveCameraBase::createLocal(BitVector bFlags)
{
    OffCenterPerspectiveCameraTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<OffCenterPerspectiveCamera>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
OffCenterPerspectiveCameraTransitPtr OffCenterPerspectiveCameraBase::createDependent(BitVector bFlags)
{
    OffCenterPerspectiveCameraTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<OffCenterPerspectiveCamera>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
OffCenterPerspectiveCameraTransitPtr OffCenterPerspectiveCameraBase::create(void)
{
    OffCenterPerspectiveCameraTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<OffCenterPerspectiveCamera>(tmpPtr);
    }

    return fc;
}

OffCenterPerspectiveCamera *OffCenterPerspectiveCameraBase::createEmptyLocal(BitVector bFlags)
{
    OffCenterPerspectiveCamera *returnValue;

    newPtr<OffCenterPerspectiveCamera>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
OffCenterPerspectiveCamera *OffCenterPerspectiveCameraBase::createEmpty(void)
{
    OffCenterPerspectiveCamera *returnValue;

    newPtr<OffCenterPerspectiveCamera>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr OffCenterPerspectiveCameraBase::shallowCopyLocal(
    BitVector bFlags) const
{
    OffCenterPerspectiveCamera *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const OffCenterPerspectiveCamera *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr OffCenterPerspectiveCameraBase::shallowCopyDependent(
    BitVector bFlags) const
{
    OffCenterPerspectiveCamera *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const OffCenterPerspectiveCamera *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr OffCenterPerspectiveCameraBase::shallowCopy(void) const
{
    OffCenterPerspectiveCamera *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const OffCenterPerspectiveCamera *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

OffCenterPerspectiveCameraBase::OffCenterPerspectiveCameraBase(void) :
    Inherited(),
    _sfPrincipalPoint         (Vec2f(0,0))
{
}

OffCenterPerspectiveCameraBase::OffCenterPerspectiveCameraBase(const OffCenterPerspectiveCameraBase &source) :
    Inherited(source),
    _sfPrincipalPoint         (source._sfPrincipalPoint         )
{
}


/*-------------------------- destructors ----------------------------------*/

OffCenterPerspectiveCameraBase::~OffCenterPerspectiveCameraBase(void)
{
}


GetFieldHandlePtr OffCenterPerspectiveCameraBase::getHandlePrincipalPoint  (void) const
{
    SFVec2f::GetHandlePtr returnValue(
        new  SFVec2f::GetHandle(
             &_sfPrincipalPoint,
             this->getType().getFieldDesc(PrincipalPointFieldId),
             const_cast<OffCenterPerspectiveCameraBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr OffCenterPerspectiveCameraBase::editHandlePrincipalPoint (void)
{
    SFVec2f::EditHandlePtr returnValue(
        new  SFVec2f::EditHandle(
             &_sfPrincipalPoint,
             this->getType().getFieldDesc(PrincipalPointFieldId),
             this));


    editSField(PrincipalPointFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void OffCenterPerspectiveCameraBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    OffCenterPerspectiveCamera *pThis = static_cast<OffCenterPerspectiveCamera *>(this);

    pThis->execSync(static_cast<OffCenterPerspectiveCamera *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *OffCenterPerspectiveCameraBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    OffCenterPerspectiveCamera *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const OffCenterPerspectiveCamera *>(pRefAspect),
                  dynamic_cast<const OffCenterPerspectiveCamera *>(this));

    return returnValue;
}
#endif

void OffCenterPerspectiveCameraBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
