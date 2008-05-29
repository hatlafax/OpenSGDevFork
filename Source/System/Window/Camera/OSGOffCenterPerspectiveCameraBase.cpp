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
 **     class OffCenterPerspectiveCamera!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEOFFCENTERPERSPECTIVECAMERAINST

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "OSGOffCenterPerspectiveCameraBase.h"
#include "OSGOffCenterPerspectiveCamera.h"

#include "boost/bind.hpp"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::OffCenterPerspectiveCamera
    A generalized perspective camera for an asymmetric frustum.
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var Vec2f           OffCenterPerspectiveCameraBase::_sfPrincipalPoint
    The relative position of the principal point.
*/


void OffCenterPerspectiveCameraBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFVec2f::Description(
        SFVec2f::getClassType(),
        "principalPoint",
        "The relative position of the principal point.\n",
        PrincipalPointFieldId, PrincipalPointFieldMask,
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&OffCenterPerspectiveCamera::editHandlePrincipalPoint),
        static_cast<FieldGetMethodSig >(&OffCenterPerspectiveCamera::getHandlePrincipalPoint));

    oType.addInitialDesc(pDesc);
}


OffCenterPerspectiveCameraBase::TypeObject OffCenterPerspectiveCameraBase::_type(
    OffCenterPerspectiveCameraBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&OffCenterPerspectiveCameraBase::createEmptyLocal),
    OffCenterPerspectiveCamera::initMethod,
    OffCenterPerspectiveCamera::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&OffCenterPerspectiveCameraBase::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"OffCenterPerspectiveCamera\"\n"
    "\tparent=\"PerspectiveCamera\"\n"
    "\tlibrary=\"Window\"\n"
    "\tstructure=\"concrete\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    ">\n"
    "A generalized perspective camera for an asymmetric frustum.\n"
    "\t<Field\n"
    "\t\tname=\"principalPoint\"\n"
    "\t\ttype=\"Vec2f\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "                defaultValue=\"0,0\"\n"
    "\t>\n"
    "\tThe relative position of the principal point.\n"
    "\t</Field>\n"
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

#ifdef OSG_1_GET_COMPAT
SFVec2f             *OffCenterPerspectiveCameraBase::getSFPrincipalPoint (void)
{
    return this->editSFPrincipalPoint ();
}
#endif





/*------------------------------ access -----------------------------------*/

UInt32 OffCenterPerspectiveCameraBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

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
        _sfPrincipalPoint.copyFromBin(pMem);
    }
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

//! create an empty new instance of the class, do not copy the prototype
OffCenterPerspectiveCamera *OffCenterPerspectiveCameraBase::createEmpty(void)
{
    OffCenterPerspectiveCamera *returnValue;

    newPtr<OffCenterPerspectiveCamera>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &= 
        ~Thread::getCurrentLocalFlags(); 

    return returnValue;
}

OffCenterPerspectiveCamera *OffCenterPerspectiveCameraBase::createEmptyLocal(BitVector bFlags)
{
    OffCenterPerspectiveCamera *returnValue;

    newPtr<OffCenterPerspectiveCamera>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

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

FieldContainerTransitPtr OffCenterPerspectiveCameraBase::shallowCopyLocal(
    BitVector bFlags) const
{
    OffCenterPerspectiveCamera *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const OffCenterPerspectiveCamera *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

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
             this->getType().getFieldDesc(PrincipalPointFieldId)));

    return returnValue;
}

EditFieldHandlePtr OffCenterPerspectiveCameraBase::editHandlePrincipalPoint (void)
{
    SFVec2f::EditHandlePtr returnValue(
        new  SFVec2f::EditHandle(
             &_sfPrincipalPoint, 
             this->getType().getFieldDesc(PrincipalPointFieldId)));

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
    this->execSync(static_cast<OffCenterPerspectiveCameraBase *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *OffCenterPerspectiveCameraBase::createAspectCopy(void) const
{
    OffCenterPerspectiveCamera *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const OffCenterPerspectiveCamera *>(this));

    return returnValue;
}
#endif

void OffCenterPerspectiveCameraBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<OffCenterPerspectiveCamera *>::_type("OffCenterPerspectiveCameraPtr", "PerspectiveCameraPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(OffCenterPerspectiveCamera *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           OffCenterPerspectiveCamera *, 
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           OffCenterPerspectiveCamera *, 
                           0);

OSG_END_NAMESPACE
