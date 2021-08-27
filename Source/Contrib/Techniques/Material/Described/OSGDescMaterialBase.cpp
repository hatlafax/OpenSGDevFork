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
 **     class DescMaterial!
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



#include "OSGEnvironmentDesc.h"         // EnvironmentDesc Class
#include "OSGMaterialDesc.h"            // MaterialDesc Class
#include "OSGCapabilitiesDesc.h"        // CapabilitiesDesc Class

#include "OSGDescMaterialBase.h"
#include "OSGDescMaterial.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DescMaterial
    The described material is a ChunkMaterial that wraps a MaterialDesc instance which
    is used for setting up various chunks for material and texture properties and that
    is able to optionally provide matching shader code.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var EnvironmentDesc * DescMaterialBase::_sfEnvironmentDesc
    The capabilities that are used for code generation.
*/

/*! \var MaterialDesc *  DescMaterialBase::_sfMaterialDesc
    The plain material parameters.
*/

/*! \var CapabilitiesDesc * DescMaterialBase::_sfCapabilitiesDesc
    The capabilities that are used for code generation.
*/

/*! \var Int32           DescMaterialBase::_sfVertMaterialBindingPnt
    The vertex shader material binding point for the uniform buffer object.
*/

/*! \var Int32           DescMaterialBase::_sfFragMaterialBindingPnt
    The fragment shader material binding point for the uniform buffer object.
*/

/*! \var Int32           DescMaterialBase::_sfFragEnvironmentBindingPnt
    The fragment shader environment binding point for the uniform buffer object.
*/

/*! \var Int32           DescMaterialBase::_sfTexUnitOffset
    Each texture of the material does reserve one texture binding point. 
    The texUnitOffset parameter determines the first one to use.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<DescMaterial *, nsOSG>::_type(
    "DescMaterialPtr", 
    "ChunkMaterialPtr", 
    DescMaterial::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(DescMaterial *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void DescMaterialBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecEnvironmentDescPtr::Description(
        SFUnrecEnvironmentDescPtr::getClassType(),
        "environmentDesc",
        "The capabilities that are used for code generation.\n",
        EnvironmentDescFieldId, EnvironmentDescFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FCustomAccess),
        static_cast<FieldEditMethodSig>(&DescMaterial::editHandleEnvironmentDesc),
        static_cast<FieldGetMethodSig >(&DescMaterial::getHandleEnvironmentDesc));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecMaterialDescPtr::Description(
        SFUnrecMaterialDescPtr::getClassType(),
        "materialDesc",
        "The plain material parameters.\n",
        MaterialDescFieldId, MaterialDescFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FCustomAccess),
        static_cast<FieldEditMethodSig>(&DescMaterial::editHandleMaterialDesc),
        static_cast<FieldGetMethodSig >(&DescMaterial::getHandleMaterialDesc));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecCapabilitiesDescPtr::Description(
        SFUnrecCapabilitiesDescPtr::getClassType(),
        "capabilitiesDesc",
        "The capabilities that are used for code generation.\n",
        CapabilitiesDescFieldId, CapabilitiesDescFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DescMaterial::editHandleCapabilitiesDesc),
        static_cast<FieldGetMethodSig >(&DescMaterial::getHandleCapabilitiesDesc));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "vertMaterialBindingPnt",
        "The vertex shader material binding point for the uniform buffer object.\n",
        VertMaterialBindingPntFieldId, VertMaterialBindingPntFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DescMaterial::editHandleVertMaterialBindingPnt),
        static_cast<FieldGetMethodSig >(&DescMaterial::getHandleVertMaterialBindingPnt));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "fragMaterialBindingPnt",
        "The fragment shader material binding point for the uniform buffer object.\n",
        FragMaterialBindingPntFieldId, FragMaterialBindingPntFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DescMaterial::editHandleFragMaterialBindingPnt),
        static_cast<FieldGetMethodSig >(&DescMaterial::getHandleFragMaterialBindingPnt));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "fragEnvironmentBindingPnt",
        "The fragment shader environment binding point for the uniform buffer object.\n",
        FragEnvironmentBindingPntFieldId, FragEnvironmentBindingPntFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DescMaterial::editHandleFragEnvironmentBindingPnt),
        static_cast<FieldGetMethodSig >(&DescMaterial::getHandleFragEnvironmentBindingPnt));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "texUnitOffset",
        "Each texture of the material does reserve one texture binding point. \n"
        "The texUnitOffset parameter determines the first one to use.\n",
        TexUnitOffsetFieldId, TexUnitOffsetFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DescMaterial::editHandleTexUnitOffset),
        static_cast<FieldGetMethodSig >(&DescMaterial::getHandleTexUnitOffset));

    oType.addInitialDesc(pDesc);
}


DescMaterialBase::TypeObject DescMaterialBase::_type(
    DescMaterialBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&DescMaterialBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&DescMaterial::initMethod),
    reinterpret_cast<ExitContainerF>(&DescMaterial::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&DescMaterial::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"DescMaterial\"\n"
    "    parent=\"ChunkMaterial\"\n"
    "    library=\"ContribTechniques\"\n"
    "    structure=\"concrete\"\n"
    "    pointerfieldtypes=\"none\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    >\n"
    "    The described material is a ChunkMaterial that wraps a MaterialDesc instance which\n"
    "    is used for setting up various chunks for material and texture properties and that\n"
    "    is able to optionally provide matching shader code.\n"
    "\n"
    "    <Field\n"
    "        name=\"environmentDesc\"\n"
    "        type=\"EnvironmentDescPtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        ptrFieldAccess = \"custom\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "        The capabilities that are used for code generation.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"materialDesc\"\n"
    "        type=\"MaterialDescPtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "\taccess=\"public\"\n"
    "        ptrFieldAccess = \"custom\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "        The plain material parameters.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"capabilitiesDesc\"\n"
    "        type=\"CapabilitiesDescPtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "        The capabilities that are used for code generation.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"vertMaterialBindingPnt\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "\taccess=\"public\"\n"
    "        defaultValue=\"-1\"\n"
    "        >\n"
    "        The vertex shader material binding point for the uniform buffer object.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"fragMaterialBindingPnt\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "\taccess=\"public\"\n"
    "        defaultValue=\"-1\"\n"
    "        >\n"
    "        The fragment shader material binding point for the uniform buffer object.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"fragEnvironmentBindingPnt\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "\taccess=\"public\"\n"
    "        defaultValue=\"-1\"\n"
    "        >\n"
    "        The fragment shader environment binding point for the uniform buffer object.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"texUnitOffset\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"8\"\n"
    "        >\n"
    "        Each texture of the material does reserve one texture binding point. \n"
    "        The texUnitOffset parameter determines the first one to use.\n"
    "    </Field>\n"
    "\n"
    "</FieldContainer>\n"
    "\n",
    "The described material is a ChunkMaterial that wraps a MaterialDesc instance which\n"
    "is used for setting up various chunks for material and texture properties and that\n"
    "is able to optionally provide matching shader code.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &DescMaterialBase::getType(void)
{
    return _type;
}

const FieldContainerType &DescMaterialBase::getType(void) const
{
    return _type;
}

UInt32 DescMaterialBase::getContainerSize(void) const
{
    return sizeof(DescMaterial);
}

/*------------------------- decorator get ------------------------------*/


//! Get the DescMaterial::_sfEnvironmentDesc field.
const SFUnrecEnvironmentDescPtr *DescMaterialBase::getSFEnvironmentDesc(void) const
{
    return &_sfEnvironmentDesc;
}

//! Get the value of the DescMaterial::_sfEnvironmentDesc field.
EnvironmentDesc * DescMaterialBase::getEnvironmentDesc(void) const
{
    return _sfEnvironmentDesc.getValue();
}



//! Get the DescMaterial::_sfMaterialDesc field.
const SFUnrecMaterialDescPtr *DescMaterialBase::getSFMaterialDesc(void) const
{
    return &_sfMaterialDesc;
}

//! Get the value of the DescMaterial::_sfMaterialDesc field.
MaterialDesc * DescMaterialBase::getMaterialDesc(void) const
{
    return _sfMaterialDesc.getValue();
}



//! Get the DescMaterial::_sfCapabilitiesDesc field.
const SFUnrecCapabilitiesDescPtr *DescMaterialBase::getSFCapabilitiesDesc(void) const
{
    return &_sfCapabilitiesDesc;
}

SFUnrecCapabilitiesDescPtr *DescMaterialBase::editSFCapabilitiesDesc(void)
{
    editSField(CapabilitiesDescFieldMask);

    return &_sfCapabilitiesDesc;
}

//! Get the value of the DescMaterial::_sfCapabilitiesDesc field.
CapabilitiesDesc * DescMaterialBase::getCapabilitiesDesc(void) const
{
    return _sfCapabilitiesDesc.getValue();
}

//! Set the value of the DescMaterial::_sfCapabilitiesDesc field.
void DescMaterialBase::setCapabilitiesDesc(CapabilitiesDesc * const value)
{
    editSField(CapabilitiesDescFieldMask);

    _sfCapabilitiesDesc.setValue(value);
}


SFInt32 *DescMaterialBase::editSFVertMaterialBindingPnt(void)
{
    editSField(VertMaterialBindingPntFieldMask);

    return &_sfVertMaterialBindingPnt;
}

const SFInt32 *DescMaterialBase::getSFVertMaterialBindingPnt(void) const
{
    return &_sfVertMaterialBindingPnt;
}


SFInt32 *DescMaterialBase::editSFFragMaterialBindingPnt(void)
{
    editSField(FragMaterialBindingPntFieldMask);

    return &_sfFragMaterialBindingPnt;
}

const SFInt32 *DescMaterialBase::getSFFragMaterialBindingPnt(void) const
{
    return &_sfFragMaterialBindingPnt;
}


SFInt32 *DescMaterialBase::editSFFragEnvironmentBindingPnt(void)
{
    editSField(FragEnvironmentBindingPntFieldMask);

    return &_sfFragEnvironmentBindingPnt;
}

const SFInt32 *DescMaterialBase::getSFFragEnvironmentBindingPnt(void) const
{
    return &_sfFragEnvironmentBindingPnt;
}


SFInt32 *DescMaterialBase::editSFTexUnitOffset(void)
{
    editSField(TexUnitOffsetFieldMask);

    return &_sfTexUnitOffset;
}

const SFInt32 *DescMaterialBase::getSFTexUnitOffset(void) const
{
    return &_sfTexUnitOffset;
}






/*------------------------------ access -----------------------------------*/

SizeT DescMaterialBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (EnvironmentDescFieldMask & whichField))
    {
        returnValue += _sfEnvironmentDesc.getBinSize();
    }
    if(FieldBits::NoField != (MaterialDescFieldMask & whichField))
    {
        returnValue += _sfMaterialDesc.getBinSize();
    }
    if(FieldBits::NoField != (CapabilitiesDescFieldMask & whichField))
    {
        returnValue += _sfCapabilitiesDesc.getBinSize();
    }
    if(FieldBits::NoField != (VertMaterialBindingPntFieldMask & whichField))
    {
        returnValue += _sfVertMaterialBindingPnt.getBinSize();
    }
    if(FieldBits::NoField != (FragMaterialBindingPntFieldMask & whichField))
    {
        returnValue += _sfFragMaterialBindingPnt.getBinSize();
    }
    if(FieldBits::NoField != (FragEnvironmentBindingPntFieldMask & whichField))
    {
        returnValue += _sfFragEnvironmentBindingPnt.getBinSize();
    }
    if(FieldBits::NoField != (TexUnitOffsetFieldMask & whichField))
    {
        returnValue += _sfTexUnitOffset.getBinSize();
    }

    return returnValue;
}

void DescMaterialBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (EnvironmentDescFieldMask & whichField))
    {
        _sfEnvironmentDesc.copyToBin(pMem);
    }
    if(FieldBits::NoField != (MaterialDescFieldMask & whichField))
    {
        _sfMaterialDesc.copyToBin(pMem);
    }
    if(FieldBits::NoField != (CapabilitiesDescFieldMask & whichField))
    {
        _sfCapabilitiesDesc.copyToBin(pMem);
    }
    if(FieldBits::NoField != (VertMaterialBindingPntFieldMask & whichField))
    {
        _sfVertMaterialBindingPnt.copyToBin(pMem);
    }
    if(FieldBits::NoField != (FragMaterialBindingPntFieldMask & whichField))
    {
        _sfFragMaterialBindingPnt.copyToBin(pMem);
    }
    if(FieldBits::NoField != (FragEnvironmentBindingPntFieldMask & whichField))
    {
        _sfFragEnvironmentBindingPnt.copyToBin(pMem);
    }
    if(FieldBits::NoField != (TexUnitOffsetFieldMask & whichField))
    {
        _sfTexUnitOffset.copyToBin(pMem);
    }
}

void DescMaterialBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (EnvironmentDescFieldMask & whichField))
    {
        editSField(EnvironmentDescFieldMask);
        _sfEnvironmentDesc.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (MaterialDescFieldMask & whichField))
    {
        editSField(MaterialDescFieldMask);
        _sfMaterialDesc.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (CapabilitiesDescFieldMask & whichField))
    {
        editSField(CapabilitiesDescFieldMask);
        _sfCapabilitiesDesc.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (VertMaterialBindingPntFieldMask & whichField))
    {
        editSField(VertMaterialBindingPntFieldMask);
        _sfVertMaterialBindingPnt.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (FragMaterialBindingPntFieldMask & whichField))
    {
        editSField(FragMaterialBindingPntFieldMask);
        _sfFragMaterialBindingPnt.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (FragEnvironmentBindingPntFieldMask & whichField))
    {
        editSField(FragEnvironmentBindingPntFieldMask);
        _sfFragEnvironmentBindingPnt.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (TexUnitOffsetFieldMask & whichField))
    {
        editSField(TexUnitOffsetFieldMask);
        _sfTexUnitOffset.copyFromBin(pMem);
    }
}

//! create a new instance of the class
DescMaterialTransitPtr DescMaterialBase::createLocal(BitVector bFlags)
{
    DescMaterialTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<DescMaterial>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
DescMaterialTransitPtr DescMaterialBase::createDependent(BitVector bFlags)
{
    DescMaterialTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<DescMaterial>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
DescMaterialTransitPtr DescMaterialBase::create(void)
{
    DescMaterialTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<DescMaterial>(tmpPtr);
    }

    return fc;
}

DescMaterial *DescMaterialBase::createEmptyLocal(BitVector bFlags)
{
    DescMaterial *returnValue;

    newPtr<DescMaterial>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
DescMaterial *DescMaterialBase::createEmpty(void)
{
    DescMaterial *returnValue;

    newPtr<DescMaterial>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr DescMaterialBase::shallowCopyLocal(
    BitVector bFlags) const
{
    DescMaterial *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DescMaterial *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr DescMaterialBase::shallowCopyDependent(
    BitVector bFlags) const
{
    DescMaterial *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DescMaterial *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr DescMaterialBase::shallowCopy(void) const
{
    DescMaterial *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const DescMaterial *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

DescMaterialBase::DescMaterialBase(void) :
    Inherited(),
    _sfEnvironmentDesc        (NULL),
    _sfMaterialDesc           (NULL),
    _sfCapabilitiesDesc       (NULL),
    _sfVertMaterialBindingPnt (Int32(-1)),
    _sfFragMaterialBindingPnt (Int32(-1)),
    _sfFragEnvironmentBindingPnt(Int32(-1)),
    _sfTexUnitOffset          (Int32(8))
{
}

DescMaterialBase::DescMaterialBase(const DescMaterialBase &source) :
    Inherited(source),
    _sfEnvironmentDesc        (NULL),
    _sfMaterialDesc           (NULL),
    _sfCapabilitiesDesc       (NULL),
    _sfVertMaterialBindingPnt (source._sfVertMaterialBindingPnt ),
    _sfFragMaterialBindingPnt (source._sfFragMaterialBindingPnt ),
    _sfFragEnvironmentBindingPnt(source._sfFragEnvironmentBindingPnt),
    _sfTexUnitOffset          (source._sfTexUnitOffset          )
{
}


/*-------------------------- destructors ----------------------------------*/

DescMaterialBase::~DescMaterialBase(void)
{
}

void DescMaterialBase::onCreate(const DescMaterial *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        DescMaterial *pThis = static_cast<DescMaterial *>(this);

        pThis->setEnvironmentDesc(source->getEnvironmentDesc());

        pThis->setMaterialDesc(source->getMaterialDesc());

        pThis->setCapabilitiesDesc(source->getCapabilitiesDesc());
    }
}

GetFieldHandlePtr DescMaterialBase::getHandleEnvironmentDesc (void) const
{
    SFUnrecEnvironmentDescPtr::GetHandlePtr returnValue(
        new  SFUnrecEnvironmentDescPtr::GetHandle(
             &_sfEnvironmentDesc,
             this->getType().getFieldDesc(EnvironmentDescFieldId),
             const_cast<DescMaterialBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialBase::editHandleEnvironmentDesc(void)
{
    SFUnrecEnvironmentDescPtr::EditHandlePtr returnValue(
        new  SFUnrecEnvironmentDescPtr::EditHandle(
             &_sfEnvironmentDesc,
             this->getType().getFieldDesc(EnvironmentDescFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DescMaterial::setEnvironmentDesc,
                    static_cast<DescMaterial *>(this), ::boost::placeholders::_1));

    editSField(EnvironmentDescFieldMask);

    return returnValue;
}

GetFieldHandlePtr DescMaterialBase::getHandleMaterialDesc    (void) const
{
    SFUnrecMaterialDescPtr::GetHandlePtr returnValue(
        new  SFUnrecMaterialDescPtr::GetHandle(
             &_sfMaterialDesc,
             this->getType().getFieldDesc(MaterialDescFieldId),
             const_cast<DescMaterialBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialBase::editHandleMaterialDesc   (void)
{
    SFUnrecMaterialDescPtr::EditHandlePtr returnValue(
        new  SFUnrecMaterialDescPtr::EditHandle(
             &_sfMaterialDesc,
             this->getType().getFieldDesc(MaterialDescFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DescMaterial::setMaterialDesc,
                    static_cast<DescMaterial *>(this), ::boost::placeholders::_1));

    editSField(MaterialDescFieldMask);

    return returnValue;
}

GetFieldHandlePtr DescMaterialBase::getHandleCapabilitiesDesc (void) const
{
    SFUnrecCapabilitiesDescPtr::GetHandlePtr returnValue(
        new  SFUnrecCapabilitiesDescPtr::GetHandle(
             &_sfCapabilitiesDesc,
             this->getType().getFieldDesc(CapabilitiesDescFieldId),
             const_cast<DescMaterialBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialBase::editHandleCapabilitiesDesc(void)
{
    SFUnrecCapabilitiesDescPtr::EditHandlePtr returnValue(
        new  SFUnrecCapabilitiesDescPtr::EditHandle(
             &_sfCapabilitiesDesc,
             this->getType().getFieldDesc(CapabilitiesDescFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DescMaterial::setCapabilitiesDesc,
                    static_cast<DescMaterial *>(this), ::boost::placeholders::_1));

    editSField(CapabilitiesDescFieldMask);

    return returnValue;
}

GetFieldHandlePtr DescMaterialBase::getHandleVertMaterialBindingPnt (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfVertMaterialBindingPnt,
             this->getType().getFieldDesc(VertMaterialBindingPntFieldId),
             const_cast<DescMaterialBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialBase::editHandleVertMaterialBindingPnt(void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfVertMaterialBindingPnt,
             this->getType().getFieldDesc(VertMaterialBindingPntFieldId),
             this));


    editSField(VertMaterialBindingPntFieldMask);

    return returnValue;
}

GetFieldHandlePtr DescMaterialBase::getHandleFragMaterialBindingPnt (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfFragMaterialBindingPnt,
             this->getType().getFieldDesc(FragMaterialBindingPntFieldId),
             const_cast<DescMaterialBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialBase::editHandleFragMaterialBindingPnt(void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfFragMaterialBindingPnt,
             this->getType().getFieldDesc(FragMaterialBindingPntFieldId),
             this));


    editSField(FragMaterialBindingPntFieldMask);

    return returnValue;
}

GetFieldHandlePtr DescMaterialBase::getHandleFragEnvironmentBindingPnt (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfFragEnvironmentBindingPnt,
             this->getType().getFieldDesc(FragEnvironmentBindingPntFieldId),
             const_cast<DescMaterialBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialBase::editHandleFragEnvironmentBindingPnt(void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfFragEnvironmentBindingPnt,
             this->getType().getFieldDesc(FragEnvironmentBindingPntFieldId),
             this));


    editSField(FragEnvironmentBindingPntFieldMask);

    return returnValue;
}

GetFieldHandlePtr DescMaterialBase::getHandleTexUnitOffset   (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfTexUnitOffset,
             this->getType().getFieldDesc(TexUnitOffsetFieldId),
             const_cast<DescMaterialBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialBase::editHandleTexUnitOffset  (void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfTexUnitOffset,
             this->getType().getFieldDesc(TexUnitOffsetFieldId),
             this));


    editSField(TexUnitOffsetFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void DescMaterialBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    DescMaterial *pThis = static_cast<DescMaterial *>(this);

    pThis->execSync(static_cast<DescMaterial *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *DescMaterialBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    DescMaterial *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const DescMaterial *>(pRefAspect),
                  dynamic_cast<const DescMaterial *>(this));

    return returnValue;
}
#endif

void DescMaterialBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<DescMaterial *>(this)->setEnvironmentDesc(NULL);

    static_cast<DescMaterial *>(this)->setMaterialDesc(NULL);

    static_cast<DescMaterial *>(this)->setCapabilitiesDesc(NULL);


}


OSG_END_NAMESPACE
