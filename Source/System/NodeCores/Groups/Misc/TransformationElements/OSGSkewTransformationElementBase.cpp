/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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
 **     class SkewTransformationElement!
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




#include "OSGSkewTransformationElementBase.h"
#include "OSGSkewTransformationElement.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SkewTransformationElement
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Vec3f           SkewTransformationElementBase::_sfRotationAxis
    
*/

/*! \var Vec3f           SkewTransformationElementBase::_sfTranslationAxis
    
*/

/*! \var Real32          SkewTransformationElementBase::_sfAngle
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<SkewTransformationElement *, nsOSG>::_type(
    "SkewTransformationElementPtr", 
    "TransformationElementPtr", 
    SkewTransformationElement::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(SkewTransformationElement *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           SkewTransformationElement *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           SkewTransformationElement *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void SkewTransformationElementBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFVec3f::Description(
        SFVec3f::getClassType(),
        "RotationAxis",
        "",
        RotationAxisFieldId, RotationAxisFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SkewTransformationElement::editHandleRotationAxis),
        static_cast<FieldGetMethodSig >(&SkewTransformationElement::getHandleRotationAxis));

    oType.addInitialDesc(pDesc);

    pDesc = new SFVec3f::Description(
        SFVec3f::getClassType(),
        "TranslationAxis",
        "",
        TranslationAxisFieldId, TranslationAxisFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SkewTransformationElement::editHandleTranslationAxis),
        static_cast<FieldGetMethodSig >(&SkewTransformationElement::getHandleTranslationAxis));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "Angle",
        "",
        AngleFieldId, AngleFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SkewTransformationElement::editHandleAngle),
        static_cast<FieldGetMethodSig >(&SkewTransformationElement::getHandleAngle));

    oType.addInitialDesc(pDesc);
}


SkewTransformationElementBase::TypeObject SkewTransformationElementBase::_type(
    SkewTransformationElementBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&SkewTransformationElementBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&SkewTransformationElement::initMethod),
    reinterpret_cast<ExitContainerF>(&SkewTransformationElement::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&SkewTransformationElement::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"SkewTransformationElement\"\n"
    "    parent=\"TransformationElement\"\n"
    "    library=\"Group\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    "    >\n"
    "  <Field\n"
    "      name=\"RotationAxis\"\n"
    "      type=\"Vec3f\"\n"
    "      category=\"data\"\n"
    "      cardinality=\"single\"\n"
    "      visibility=\"external\"\n"
    "      access=\"public\"\n"
    "      defaultValue=\"0.0f,1.0f,0.0f\"\n"
    "      >\n"
    "  </Field>\n"
    "  <Field\n"
    "      name=\"TranslationAxis\"\n"
    "      type=\"Vec3f\"\n"
    "      category=\"data\"\n"
    "      cardinality=\"single\"\n"
    "      visibility=\"external\"\n"
    "      access=\"public\"\n"
    "      defaultValue=\"1.0f,0.0f,0.0f\"\n"
    "      >\n"
    "  </Field>\n"
    "  <Field\n"
    "      name=\"Angle\"\n"
    "      type=\"Real32\"\n"
    "      category=\"data\"\n"
    "      cardinality=\"single\"\n"
    "      visibility=\"external\"\n"
    "      access=\"public\"\n"
    "      defaultValue=\"0.0f\"\n"
    "      >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &SkewTransformationElementBase::getType(void)
{
    return _type;
}

const FieldContainerType &SkewTransformationElementBase::getType(void) const
{
    return _type;
}

UInt32 SkewTransformationElementBase::getContainerSize(void) const
{
    return sizeof(SkewTransformationElement);
}

/*------------------------- decorator get ------------------------------*/


SFVec3f *SkewTransformationElementBase::editSFRotationAxis(void)
{
    editSField(RotationAxisFieldMask);

    return &_sfRotationAxis;
}

const SFVec3f *SkewTransformationElementBase::getSFRotationAxis(void) const
{
    return &_sfRotationAxis;
}


SFVec3f *SkewTransformationElementBase::editSFTranslationAxis(void)
{
    editSField(TranslationAxisFieldMask);

    return &_sfTranslationAxis;
}

const SFVec3f *SkewTransformationElementBase::getSFTranslationAxis(void) const
{
    return &_sfTranslationAxis;
}


SFReal32 *SkewTransformationElementBase::editSFAngle(void)
{
    editSField(AngleFieldMask);

    return &_sfAngle;
}

const SFReal32 *SkewTransformationElementBase::getSFAngle(void) const
{
    return &_sfAngle;
}






/*------------------------------ access -----------------------------------*/

SizeT SkewTransformationElementBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (RotationAxisFieldMask & whichField))
    {
        returnValue += _sfRotationAxis.getBinSize();
    }
    if(FieldBits::NoField != (TranslationAxisFieldMask & whichField))
    {
        returnValue += _sfTranslationAxis.getBinSize();
    }
    if(FieldBits::NoField != (AngleFieldMask & whichField))
    {
        returnValue += _sfAngle.getBinSize();
    }

    return returnValue;
}

void SkewTransformationElementBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (RotationAxisFieldMask & whichField))
    {
        _sfRotationAxis.copyToBin(pMem);
    }
    if(FieldBits::NoField != (TranslationAxisFieldMask & whichField))
    {
        _sfTranslationAxis.copyToBin(pMem);
    }
    if(FieldBits::NoField != (AngleFieldMask & whichField))
    {
        _sfAngle.copyToBin(pMem);
    }
}

void SkewTransformationElementBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (RotationAxisFieldMask & whichField))
    {
        editSField(RotationAxisFieldMask);
        _sfRotationAxis.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (TranslationAxisFieldMask & whichField))
    {
        editSField(TranslationAxisFieldMask);
        _sfTranslationAxis.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (AngleFieldMask & whichField))
    {
        editSField(AngleFieldMask);
        _sfAngle.copyFromBin(pMem);
    }
}

//! create a new instance of the class
SkewTransformationElementTransitPtr SkewTransformationElementBase::createLocal(BitVector bFlags)
{
    SkewTransformationElementTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<SkewTransformationElement>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
SkewTransformationElementTransitPtr SkewTransformationElementBase::createDependent(BitVector bFlags)
{
    SkewTransformationElementTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<SkewTransformationElement>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
SkewTransformationElementTransitPtr SkewTransformationElementBase::create(void)
{
    SkewTransformationElementTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<SkewTransformationElement>(tmpPtr);
    }

    return fc;
}

SkewTransformationElement *SkewTransformationElementBase::createEmptyLocal(BitVector bFlags)
{
    SkewTransformationElement *returnValue;

    newPtr<SkewTransformationElement>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
SkewTransformationElement *SkewTransformationElementBase::createEmpty(void)
{
    SkewTransformationElement *returnValue;

    newPtr<SkewTransformationElement>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr SkewTransformationElementBase::shallowCopyLocal(
    BitVector bFlags) const
{
    SkewTransformationElement *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const SkewTransformationElement *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr SkewTransformationElementBase::shallowCopyDependent(
    BitVector bFlags) const
{
    SkewTransformationElement *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const SkewTransformationElement *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr SkewTransformationElementBase::shallowCopy(void) const
{
    SkewTransformationElement *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const SkewTransformationElement *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

SkewTransformationElementBase::SkewTransformationElementBase(void) :
    Inherited(),
    _sfRotationAxis           (Vec3f(0.0f,1.0f,0.0f)),
    _sfTranslationAxis        (Vec3f(1.0f,0.0f,0.0f)),
    _sfAngle                  (Real32(0.0f))
{
}

SkewTransformationElementBase::SkewTransformationElementBase(const SkewTransformationElementBase &source) :
    Inherited(source),
    _sfRotationAxis           (source._sfRotationAxis           ),
    _sfTranslationAxis        (source._sfTranslationAxis        ),
    _sfAngle                  (source._sfAngle                  )
{
}


/*-------------------------- destructors ----------------------------------*/

SkewTransformationElementBase::~SkewTransformationElementBase(void)
{
}


GetFieldHandlePtr SkewTransformationElementBase::getHandleRotationAxis    (void) const
{
    SFVec3f::GetHandlePtr returnValue(
        new  SFVec3f::GetHandle(
             &_sfRotationAxis,
             this->getType().getFieldDesc(RotationAxisFieldId),
             const_cast<SkewTransformationElementBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SkewTransformationElementBase::editHandleRotationAxis   (void)
{
    SFVec3f::EditHandlePtr returnValue(
        new  SFVec3f::EditHandle(
             &_sfRotationAxis,
             this->getType().getFieldDesc(RotationAxisFieldId),
             this));


    editSField(RotationAxisFieldMask);

    return returnValue;
}

GetFieldHandlePtr SkewTransformationElementBase::getHandleTranslationAxis (void) const
{
    SFVec3f::GetHandlePtr returnValue(
        new  SFVec3f::GetHandle(
             &_sfTranslationAxis,
             this->getType().getFieldDesc(TranslationAxisFieldId),
             const_cast<SkewTransformationElementBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SkewTransformationElementBase::editHandleTranslationAxis(void)
{
    SFVec3f::EditHandlePtr returnValue(
        new  SFVec3f::EditHandle(
             &_sfTranslationAxis,
             this->getType().getFieldDesc(TranslationAxisFieldId),
             this));


    editSField(TranslationAxisFieldMask);

    return returnValue;
}

GetFieldHandlePtr SkewTransformationElementBase::getHandleAngle           (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfAngle,
             this->getType().getFieldDesc(AngleFieldId),
             const_cast<SkewTransformationElementBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SkewTransformationElementBase::editHandleAngle          (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfAngle,
             this->getType().getFieldDesc(AngleFieldId),
             this));


    editSField(AngleFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void SkewTransformationElementBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    SkewTransformationElement *pThis = static_cast<SkewTransformationElement *>(this);

    pThis->execSync(static_cast<SkewTransformationElement *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *SkewTransformationElementBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    SkewTransformationElement *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const SkewTransformationElement *>(pRefAspect),
                  dynamic_cast<const SkewTransformationElement *>(this));

    return returnValue;
}
#endif

void SkewTransformationElementBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
