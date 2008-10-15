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
 **     class ComponentTransform!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "OSGComponentTransformBase.h"
#include "OSGComponentTransform.h"

#include "boost/bind.hpp"

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ComponentTransform
    
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var Vec3r           ComponentTransformBase::_sfCenter
    
*/

/*! \var Quaternionr     ComponentTransformBase::_sfRotation
    
*/

/*! \var Vec3r           ComponentTransformBase::_sfScale
    
*/

/*! \var Quaternionr     ComponentTransformBase::_sfScaleOrientation
    
*/

/*! \var Vec3r           ComponentTransformBase::_sfTranslation
    
*/


void ComponentTransformBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFVec3r::Description(
        SFVec3r::getClassType(),
        "center",
        "",
        CenterFieldId, CenterFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ComponentTransform::editHandleCenter),
        static_cast<FieldGetMethodSig >(&ComponentTransform::getHandleCenter));

    oType.addInitialDesc(pDesc);

    pDesc = new SFQuaternionr::Description(
        SFQuaternionr::getClassType(),
        "rotation",
        "",
        RotationFieldId, RotationFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ComponentTransform::editHandleRotation),
        static_cast<FieldGetMethodSig >(&ComponentTransform::getHandleRotation));

    oType.addInitialDesc(pDesc);

    pDesc = new SFVec3r::Description(
        SFVec3r::getClassType(),
        "scale",
        "",
        ScaleFieldId, ScaleFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ComponentTransform::editHandleScale),
        static_cast<FieldGetMethodSig >(&ComponentTransform::getHandleScale));

    oType.addInitialDesc(pDesc);

    pDesc = new SFQuaternionr::Description(
        SFQuaternionr::getClassType(),
        "scaleOrientation",
        "",
        ScaleOrientationFieldId, ScaleOrientationFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ComponentTransform::editHandleScaleOrientation),
        static_cast<FieldGetMethodSig >(&ComponentTransform::getHandleScaleOrientation));

    oType.addInitialDesc(pDesc);

    pDesc = new SFVec3r::Description(
        SFVec3r::getClassType(),
        "translation",
        "",
        TranslationFieldId, TranslationFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ComponentTransform::editHandleTranslation),
        static_cast<FieldGetMethodSig >(&ComponentTransform::getHandleTranslation));

    oType.addInitialDesc(pDesc);
}


ComponentTransformBase::TypeObject ComponentTransformBase::_type(
    ComponentTransformBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&ComponentTransformBase::createEmptyLocal),
    ComponentTransform::initMethod,
    ComponentTransform::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&ComponentTransformBase::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"ComponentTransform\"\n"
    "\tparent=\"Transform\"\n"
    "\tlibrary=\"Group\"\n"
    "\tstructure=\"concrete\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    "    isNodeCore=\"true\"\n"
    ">\n"
    "\t<Field\n"
    "\t\tname=\"center\"\n"
    "\t\ttype=\"Vec3r\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"rotation\"\n"
    "\t\ttype=\"Quaternionr\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"scale\"\n"
    "\t\ttype=\"Vec3r\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"scaleOrientation\"\n"
    "\t\ttype=\"Quaternionr\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"translation\"\n"
    "\t\ttype=\"Vec3r\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t>\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ComponentTransformBase::getType(void)
{
    return _type;
}

const FieldContainerType &ComponentTransformBase::getType(void) const
{
    return _type;
}

UInt32 ComponentTransformBase::getContainerSize(void) const
{
    return sizeof(ComponentTransform);
}

/*------------------------- decorator get ------------------------------*/


SFVec3r *ComponentTransformBase::editSFCenter(void)
{
    editSField(CenterFieldMask);

    return &_sfCenter;
}

const SFVec3r *ComponentTransformBase::getSFCenter(void) const
{
    return &_sfCenter;
}


SFQuaternionr *ComponentTransformBase::editSFRotation(void)
{
    editSField(RotationFieldMask);

    return &_sfRotation;
}

const SFQuaternionr *ComponentTransformBase::getSFRotation(void) const
{
    return &_sfRotation;
}


SFVec3r *ComponentTransformBase::editSFScale(void)
{
    editSField(ScaleFieldMask);

    return &_sfScale;
}

const SFVec3r *ComponentTransformBase::getSFScale(void) const
{
    return &_sfScale;
}


SFQuaternionr *ComponentTransformBase::editSFScaleOrientation(void)
{
    editSField(ScaleOrientationFieldMask);

    return &_sfScaleOrientation;
}

const SFQuaternionr *ComponentTransformBase::getSFScaleOrientation(void) const
{
    return &_sfScaleOrientation;
}


SFVec3r *ComponentTransformBase::editSFTranslation(void)
{
    editSField(TranslationFieldMask);

    return &_sfTranslation;
}

const SFVec3r *ComponentTransformBase::getSFTranslation(void) const
{
    return &_sfTranslation;
}






/*------------------------------ access -----------------------------------*/

UInt32 ComponentTransformBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        returnValue += _sfCenter.getBinSize();
    }
    if(FieldBits::NoField != (RotationFieldMask & whichField))
    {
        returnValue += _sfRotation.getBinSize();
    }
    if(FieldBits::NoField != (ScaleFieldMask & whichField))
    {
        returnValue += _sfScale.getBinSize();
    }
    if(FieldBits::NoField != (ScaleOrientationFieldMask & whichField))
    {
        returnValue += _sfScaleOrientation.getBinSize();
    }
    if(FieldBits::NoField != (TranslationFieldMask & whichField))
    {
        returnValue += _sfTranslation.getBinSize();
    }

    return returnValue;
}

void ComponentTransformBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        _sfCenter.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RotationFieldMask & whichField))
    {
        _sfRotation.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ScaleFieldMask & whichField))
    {
        _sfScale.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ScaleOrientationFieldMask & whichField))
    {
        _sfScaleOrientation.copyToBin(pMem);
    }
    if(FieldBits::NoField != (TranslationFieldMask & whichField))
    {
        _sfTranslation.copyToBin(pMem);
    }
}

void ComponentTransformBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        _sfCenter.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RotationFieldMask & whichField))
    {
        _sfRotation.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ScaleFieldMask & whichField))
    {
        _sfScale.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ScaleOrientationFieldMask & whichField))
    {
        _sfScaleOrientation.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (TranslationFieldMask & whichField))
    {
        _sfTranslation.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ComponentTransformTransitPtr ComponentTransformBase::createLocal(BitVector bFlags)
{
    ComponentTransformTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ComponentTransform>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ComponentTransformTransitPtr ComponentTransformBase::createDependent(BitVector bFlags)
{
    ComponentTransformTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ComponentTransform>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ComponentTransformTransitPtr ComponentTransformBase::create(void)
{
    ComponentTransformTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ComponentTransform>(tmpPtr);
    }

    return fc;
}

ComponentTransform *ComponentTransformBase::createEmptyLocal(BitVector bFlags)
{
    ComponentTransform *returnValue;

    newPtr<ComponentTransform>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ComponentTransform *ComponentTransformBase::createEmpty(void)
{
    ComponentTransform *returnValue;

    newPtr<ComponentTransform>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr ComponentTransformBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ComponentTransform *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ComponentTransform *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ComponentTransformBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ComponentTransform *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ComponentTransform *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ComponentTransformBase::shallowCopy(void) const
{
    ComponentTransform *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const ComponentTransform *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

ComponentTransformBase::ComponentTransformBase(void) :
    Inherited(),
    _sfCenter                 (),
    _sfRotation               (),
    _sfScale                  (),
    _sfScaleOrientation       (),
    _sfTranslation            ()
{
}

ComponentTransformBase::ComponentTransformBase(const ComponentTransformBase &source) :
    Inherited(source),
    _sfCenter                 (source._sfCenter                 ),
    _sfRotation               (source._sfRotation               ),
    _sfScale                  (source._sfScale                  ),
    _sfScaleOrientation       (source._sfScaleOrientation       ),
    _sfTranslation            (source._sfTranslation            )
{
}


/*-------------------------- destructors ----------------------------------*/

ComponentTransformBase::~ComponentTransformBase(void)
{
}


GetFieldHandlePtr ComponentTransformBase::getHandleCenter          (void) const
{
    SFVec3r::GetHandlePtr returnValue(
        new  SFVec3r::GetHandle(
             &_sfCenter,
             this->getType().getFieldDesc(CenterFieldId)));

    return returnValue;
}

EditFieldHandlePtr ComponentTransformBase::editHandleCenter         (void)
{
    SFVec3r::EditHandlePtr returnValue(
        new  SFVec3r::EditHandle(
             &_sfCenter,
             this->getType().getFieldDesc(CenterFieldId)));


    editSField(CenterFieldMask);

    return returnValue;
}

GetFieldHandlePtr ComponentTransformBase::getHandleRotation        (void) const
{
    SFQuaternionr::GetHandlePtr returnValue(
        new  SFQuaternionr::GetHandle(
             &_sfRotation,
             this->getType().getFieldDesc(RotationFieldId)));

    return returnValue;
}

EditFieldHandlePtr ComponentTransformBase::editHandleRotation       (void)
{
    SFQuaternionr::EditHandlePtr returnValue(
        new  SFQuaternionr::EditHandle(
             &_sfRotation,
             this->getType().getFieldDesc(RotationFieldId)));


    editSField(RotationFieldMask);

    return returnValue;
}

GetFieldHandlePtr ComponentTransformBase::getHandleScale           (void) const
{
    SFVec3r::GetHandlePtr returnValue(
        new  SFVec3r::GetHandle(
             &_sfScale,
             this->getType().getFieldDesc(ScaleFieldId)));

    return returnValue;
}

EditFieldHandlePtr ComponentTransformBase::editHandleScale          (void)
{
    SFVec3r::EditHandlePtr returnValue(
        new  SFVec3r::EditHandle(
             &_sfScale,
             this->getType().getFieldDesc(ScaleFieldId)));


    editSField(ScaleFieldMask);

    return returnValue;
}

GetFieldHandlePtr ComponentTransformBase::getHandleScaleOrientation (void) const
{
    SFQuaternionr::GetHandlePtr returnValue(
        new  SFQuaternionr::GetHandle(
             &_sfScaleOrientation,
             this->getType().getFieldDesc(ScaleOrientationFieldId)));

    return returnValue;
}

EditFieldHandlePtr ComponentTransformBase::editHandleScaleOrientation(void)
{
    SFQuaternionr::EditHandlePtr returnValue(
        new  SFQuaternionr::EditHandle(
             &_sfScaleOrientation,
             this->getType().getFieldDesc(ScaleOrientationFieldId)));


    editSField(ScaleOrientationFieldMask);

    return returnValue;
}

GetFieldHandlePtr ComponentTransformBase::getHandleTranslation     (void) const
{
    SFVec3r::GetHandlePtr returnValue(
        new  SFVec3r::GetHandle(
             &_sfTranslation,
             this->getType().getFieldDesc(TranslationFieldId)));

    return returnValue;
}

EditFieldHandlePtr ComponentTransformBase::editHandleTranslation    (void)
{
    SFVec3r::EditHandlePtr returnValue(
        new  SFVec3r::EditHandle(
             &_sfTranslation,
             this->getType().getFieldDesc(TranslationFieldId)));


    editSField(TranslationFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ComponentTransformBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ComponentTransform *pThis = static_cast<ComponentTransform *>(this);

    pThis->execSync(static_cast<ComponentTransform *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ComponentTransformBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ComponentTransform *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ComponentTransform *>(pRefAspect),
                  dynamic_cast<const ComponentTransform *>(this));

    return returnValue;
}
#endif

void ComponentTransformBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ComponentTransform *>::_type("ComponentTransformPtr", "TransformPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ComponentTransform *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ComponentTransform *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ComponentTransform *,
                           0);

OSG_END_NAMESPACE
