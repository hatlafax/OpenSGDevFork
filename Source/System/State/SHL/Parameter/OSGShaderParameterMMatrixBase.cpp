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
 **     class ShaderParameterMMatrix!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESHADERPARAMETERMMATRIXINST

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "OSGShaderParameterMMatrixBase.h"
#include "OSGShaderParameterMMatrix.h"

#include "boost/bind.hpp"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ShaderParameterMMatrix
    
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var Matrix          ShaderParameterMMatrixBase::_mfValue
    parameter value
*/


void ShaderParameterMMatrixBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFMatrix::Description(
        MFMatrix::getClassType(),
        "value",
        "parameter value\n",
        ValueFieldId, ValueFieldMask,
        false,
        Field::MFDefaultFlags,
        static_cast<FieldEditMethodSig>(&ShaderParameterMMatrix::editHandleValue),
        static_cast<FieldGetMethodSig >(&ShaderParameterMMatrix::getHandleValue));

    oType.addInitialDesc(pDesc);
}


ShaderParameterMMatrixBase::TypeObject ShaderParameterMMatrixBase::_type(
    ShaderParameterMMatrixBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&ShaderParameterMMatrixBase::createEmptyLocal),
    ShaderParameterMMatrix::initMethod,
    ShaderParameterMMatrix::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&ShaderParameterMMatrixBase::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"ShaderParameterMMatrix\"\n"
    "\tparent=\"ShaderParameter\"\n"
    "\tlibrary=\"State\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    "\tdecoratable=\"false\"\n"
    "\tuseLocalIncludes=\"false\"\n"
    ">\n"
    "\t<Field\n"
    "\t\tname=\"value\"\n"
    "\t\ttype=\"Matrix\"\n"
    "\t\tcardinality=\"multi\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\tparameter value\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ShaderParameterMMatrixBase::getType(void)
{
    return _type;
}

const FieldContainerType &ShaderParameterMMatrixBase::getType(void) const
{
    return _type;
}

UInt32 ShaderParameterMMatrixBase::getContainerSize(void) const
{
    return sizeof(ShaderParameterMMatrix);
}

/*------------------------- decorator get ------------------------------*/


MFMatrix *ShaderParameterMMatrixBase::editMFValue(void)
{
    editMField(ValueFieldMask, _mfValue);

    return &_mfValue;
}

const MFMatrix *ShaderParameterMMatrixBase::getMFValue(void) const
{
    return &_mfValue;
}

#ifdef OSG_1_GET_COMPAT
MFMatrix            *ShaderParameterMMatrixBase::getMFValue          (void)
{
    return this->editMFValue          ();
}
#endif





/*------------------------------ access -----------------------------------*/

UInt32 ShaderParameterMMatrixBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        returnValue += _mfValue.getBinSize();
    }

    return returnValue;
}

void ShaderParameterMMatrixBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _mfValue.copyToBin(pMem);
    }
}

void ShaderParameterMMatrixBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _mfValue.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ShaderParameterMMatrixTransitPtr ShaderParameterMMatrixBase::create(void)
{
    ShaderParameterMMatrixTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ShaderParameterMMatrix>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ShaderParameterMMatrixTransitPtr ShaderParameterMMatrixBase::createLocal(BitVector bFlags)
{
    ShaderParameterMMatrixTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ShaderParameterMMatrix>(tmpPtr);
    }

    return fc;
}

//! create an empty new instance of the class, do not copy the prototype
ShaderParameterMMatrix *ShaderParameterMMatrixBase::createEmpty(void)
{
    ShaderParameterMMatrix *returnValue;

    newPtr<ShaderParameterMMatrix>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &= 
        ~Thread::getCurrentLocalFlags(); 

    return returnValue;
}

ShaderParameterMMatrix *ShaderParameterMMatrixBase::createEmptyLocal(BitVector bFlags)
{
    ShaderParameterMMatrix *returnValue;

    newPtr<ShaderParameterMMatrix>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShaderParameterMMatrixBase::shallowCopy(void) const
{
    ShaderParameterMMatrix *tmpPtr;

    newPtr(tmpPtr, 
           dynamic_cast<const ShaderParameterMMatrix *>(this), 
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}

FieldContainerTransitPtr ShaderParameterMMatrixBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ShaderParameterMMatrix *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShaderParameterMMatrix *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

ShaderParameterMMatrixBase::ShaderParameterMMatrixBase(void) :
    Inherited(),
    _mfValue                  ()
{
}

ShaderParameterMMatrixBase::ShaderParameterMMatrixBase(const ShaderParameterMMatrixBase &source) :
    Inherited(source),
    _mfValue                  (source._mfValue                  )
{
}


/*-------------------------- destructors ----------------------------------*/

ShaderParameterMMatrixBase::~ShaderParameterMMatrixBase(void)
{
}


GetFieldHandlePtr ShaderParameterMMatrixBase::getHandleValue           (void) const
{
    MFMatrix::GetHandlePtr returnValue(
        new  MFMatrix::GetHandle(
             &_mfValue, 
             this->getType().getFieldDesc(ValueFieldId)));

    return returnValue;
}

EditFieldHandlePtr ShaderParameterMMatrixBase::editHandleValue          (void)
{
    MFMatrix::EditHandlePtr returnValue(
        new  MFMatrix::EditHandle(
             &_mfValue, 
             this->getType().getFieldDesc(ValueFieldId)));

    editMField(ValueFieldMask, _mfValue);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ShaderParameterMMatrixBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<ShaderParameterMMatrixBase *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ShaderParameterMMatrixBase::createAspectCopy(void) const
{
    ShaderParameterMMatrix *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ShaderParameterMMatrix *>(this));

    return returnValue;
}
#endif

void ShaderParameterMMatrixBase::resolveLinks(void)
{
    Inherited::resolveLinks();

#ifdef OSG_MT_CPTR_ASPECT
    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);
#endif

#ifdef OSG_MT_CPTR_ASPECT
    _mfValue.terminateShare(Thread::getCurrentAspect(), 
                                      oOffsets);
#endif
}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ShaderParameterMMatrix *>::_type("ShaderParameterMMatrixPtr", "ShaderParameterPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ShaderParameterMMatrix *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           ShaderParameterMMatrix *, 
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           ShaderParameterMMatrix *, 
                           0);

OSG_END_NAMESPACE
