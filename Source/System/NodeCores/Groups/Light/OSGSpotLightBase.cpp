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
 **     class SpotLight!
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




#include "OSGSpotLightBase.h"
#include "OSGSpotLight.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SpotLight
    SpotLight is a located lightsource. The position of the light source
    (in the beacon's coordinate system) is defined by the \c position
    attribute, its direction by the \c direction attribute. The spot has an
    exponential fallof, controlled by the \c spotExponent attribute and a
    maximum opening angle, defined by the \c spotCutOff attribute.
    The influence of the light diminishes with distance, controlled
    by the \c constantAttenuation, \c linearAttenuation and \c
    quadraticAttenuation attributes.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Vec3f           SpotLightBase::_sfDirection
    
*/

/*! \var Real32          SpotLightBase::_sfSpotExponent
    The drop-off exponent of the spotlight.
*/

/*! \var Real32          SpotLightBase::_sfSpotCutOff
    The cut-off angle of the spotlight (in radians, not degrees!).
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<SpotLight *, nsOSG>::_type(
    "SpotLightPtr", 
    "PointLightPtr", 
    SpotLight::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(SpotLight *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void SpotLightBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFVec3f::Description(
        SFVec3f::getClassType(),
        "direction",
        "",
        DirectionFieldId, DirectionFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SpotLight::editHandleDirection),
        static_cast<FieldGetMethodSig >(&SpotLight::getHandleDirection));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "spotExponent",
        "The drop-off exponent of the spotlight.\n",
        SpotExponentFieldId, SpotExponentFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SpotLight::editHandleSpotExponent),
        static_cast<FieldGetMethodSig >(&SpotLight::getHandleSpotExponent));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "spotCutOff",
        "The cut-off angle of the spotlight (in radians, not degrees!).\n",
        SpotCutOffFieldId, SpotCutOffFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SpotLight::editHandleSpotCutOff),
        static_cast<FieldGetMethodSig >(&SpotLight::getHandleSpotCutOff));

    oType.addInitialDesc(pDesc);
}


SpotLightBase::TypeObject SpotLightBase::_type(
    SpotLightBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&SpotLightBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&SpotLight::initMethod),
    reinterpret_cast<ExitContainerF>(&SpotLight::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&SpotLight::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"SpotLight\"\n"
    "   parent=\"PointLight\"\n"
    "   library=\"Group\"\n"
    "   structure=\"concrete\"\n"
    "   pointerfieldtypes=\"none\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   isNodeCore=\"true\"\n"
    "   docGroupBase=\"GrpGroupLight\"\n"
    "   >\n"
    "  SpotLight is a located lightsource. The position of the light source\n"
    "  (in the beacon's coordinate system) is defined by the \\c position\n"
    "  attribute, its direction by the \\c direction attribute. The spot has an\n"
    "  exponential fallof, controlled by the \\c spotExponent attribute and a\n"
    "  maximum opening angle, defined by the \\c spotCutOff attribute.\n"
    "  The influence of the light diminishes with distance, controlled\n"
    "  by the \\c constantAttenuation, \\c linearAttenuation and \\c\n"
    "  quadraticAttenuation attributes.\n"
    "  <Field\n"
    "     name=\"direction\"\n"
    "     type=\"Vec3f\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     defaultValue=\"0.f,0.f,1.f\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "     name=\"spotExponent\"\n"
    "     type=\"Real32\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     defaultValue=\"0.1f\"\n"
    "     >\n"
    "    The drop-off exponent of the spotlight.\n"
    "  </Field>\n"
    "  <Field\n"
    "     name=\"spotCutOff\"\n"
    "     type=\"Real32\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     defaultValue=\"1.0472f\"\n"
    "     >\n"
    "    The cut-off angle of the spotlight (in radians, not degrees!).\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    "SpotLight is a located lightsource. The position of the light source\n"
    "(in the beacon's coordinate system) is defined by the \\c position\n"
    "attribute, its direction by the \\c direction attribute. The spot has an\n"
    "exponential fallof, controlled by the \\c spotExponent attribute and a\n"
    "maximum opening angle, defined by the \\c spotCutOff attribute.\n"
    "The influence of the light diminishes with distance, controlled\n"
    "by the \\c constantAttenuation, \\c linearAttenuation and \\c\n"
    "quadraticAttenuation attributes.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &SpotLightBase::getType(void)
{
    return _type;
}

const FieldContainerType &SpotLightBase::getType(void) const
{
    return _type;
}

UInt32 SpotLightBase::getContainerSize(void) const
{
    return sizeof(SpotLight);
}

/*------------------------- decorator get ------------------------------*/


SFVec3f *SpotLightBase::editSFDirection(void)
{
    editSField(DirectionFieldMask);

    return &_sfDirection;
}

const SFVec3f *SpotLightBase::getSFDirection(void) const
{
    return &_sfDirection;
}


SFReal32 *SpotLightBase::editSFSpotExponent(void)
{
    editSField(SpotExponentFieldMask);

    return &_sfSpotExponent;
}

const SFReal32 *SpotLightBase::getSFSpotExponent(void) const
{
    return &_sfSpotExponent;
}


SFReal32 *SpotLightBase::editSFSpotCutOff(void)
{
    editSField(SpotCutOffFieldMask);

    return &_sfSpotCutOff;
}

const SFReal32 *SpotLightBase::getSFSpotCutOff(void) const
{
    return &_sfSpotCutOff;
}






/*------------------------------ access -----------------------------------*/

SizeT SpotLightBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (DirectionFieldMask & whichField))
    {
        returnValue += _sfDirection.getBinSize();
    }
    if(FieldBits::NoField != (SpotExponentFieldMask & whichField))
    {
        returnValue += _sfSpotExponent.getBinSize();
    }
    if(FieldBits::NoField != (SpotCutOffFieldMask & whichField))
    {
        returnValue += _sfSpotCutOff.getBinSize();
    }

    return returnValue;
}

void SpotLightBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (DirectionFieldMask & whichField))
    {
        _sfDirection.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SpotExponentFieldMask & whichField))
    {
        _sfSpotExponent.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SpotCutOffFieldMask & whichField))
    {
        _sfSpotCutOff.copyToBin(pMem);
    }
}

void SpotLightBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (DirectionFieldMask & whichField))
    {
        editSField(DirectionFieldMask);
        _sfDirection.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SpotExponentFieldMask & whichField))
    {
        editSField(SpotExponentFieldMask);
        _sfSpotExponent.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SpotCutOffFieldMask & whichField))
    {
        editSField(SpotCutOffFieldMask);
        _sfSpotCutOff.copyFromBin(pMem);
    }
}

//! create a new instance of the class
SpotLightTransitPtr SpotLightBase::createLocal(BitVector bFlags)
{
    SpotLightTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<SpotLight>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
SpotLightTransitPtr SpotLightBase::createDependent(BitVector bFlags)
{
    SpotLightTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<SpotLight>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
SpotLightTransitPtr SpotLightBase::create(void)
{
    SpotLightTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<SpotLight>(tmpPtr);
    }

    return fc;
}

SpotLight *SpotLightBase::createEmptyLocal(BitVector bFlags)
{
    SpotLight *returnValue;

    newPtr<SpotLight>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
SpotLight *SpotLightBase::createEmpty(void)
{
    SpotLight *returnValue;

    newPtr<SpotLight>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr SpotLightBase::shallowCopyLocal(
    BitVector bFlags) const
{
    SpotLight *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const SpotLight *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr SpotLightBase::shallowCopyDependent(
    BitVector bFlags) const
{
    SpotLight *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const SpotLight *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr SpotLightBase::shallowCopy(void) const
{
    SpotLight *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const SpotLight *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

SpotLightBase::SpotLightBase(void) :
    Inherited(),
    _sfDirection              (Vec3f(0.f,0.f,1.f)),
    _sfSpotExponent           (Real32(0.1f)),
    _sfSpotCutOff             (Real32(1.0472f))
{
}

SpotLightBase::SpotLightBase(const SpotLightBase &source) :
    Inherited(source),
    _sfDirection              (source._sfDirection              ),
    _sfSpotExponent           (source._sfSpotExponent           ),
    _sfSpotCutOff             (source._sfSpotCutOff             )
{
}


/*-------------------------- destructors ----------------------------------*/

SpotLightBase::~SpotLightBase(void)
{
}


GetFieldHandlePtr SpotLightBase::getHandleDirection       (void) const
{
    SFVec3f::GetHandlePtr returnValue(
        new  SFVec3f::GetHandle(
             &_sfDirection,
             this->getType().getFieldDesc(DirectionFieldId),
             const_cast<SpotLightBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SpotLightBase::editHandleDirection      (void)
{
    SFVec3f::EditHandlePtr returnValue(
        new  SFVec3f::EditHandle(
             &_sfDirection,
             this->getType().getFieldDesc(DirectionFieldId),
             this));


    editSField(DirectionFieldMask);

    return returnValue;
}

GetFieldHandlePtr SpotLightBase::getHandleSpotExponent    (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfSpotExponent,
             this->getType().getFieldDesc(SpotExponentFieldId),
             const_cast<SpotLightBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SpotLightBase::editHandleSpotExponent   (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfSpotExponent,
             this->getType().getFieldDesc(SpotExponentFieldId),
             this));


    editSField(SpotExponentFieldMask);

    return returnValue;
}

GetFieldHandlePtr SpotLightBase::getHandleSpotCutOff      (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfSpotCutOff,
             this->getType().getFieldDesc(SpotCutOffFieldId),
             const_cast<SpotLightBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SpotLightBase::editHandleSpotCutOff     (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfSpotCutOff,
             this->getType().getFieldDesc(SpotCutOffFieldId),
             this));


    editSField(SpotCutOffFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void SpotLightBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    SpotLight *pThis = static_cast<SpotLight *>(this);

    pThis->execSync(static_cast<SpotLight *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *SpotLightBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    SpotLight *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const SpotLight *>(pRefAspect),
                  dynamic_cast<const SpotLight *>(this));

    return returnValue;
}
#endif

void SpotLightBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
