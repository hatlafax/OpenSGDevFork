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
 **     class ShaderParameterMVec4f!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESHADERPARAMETERMVEC4FINST

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "OSGShaderParameterMVec4fBase.h"
#include "OSGShaderParameterMVec4f.h"

#include "boost/bind.hpp"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ShaderParameterMVec4f
    
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var Vec4f           ShaderParameterMVec4fBase::_mfValue
    parameter value
*/


void ShaderParameterMVec4fBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFVec4f::Description(
        MFVec4f::getClassType(),
        "value",
        "parameter value\n",
        ValueFieldId, ValueFieldMask,
        false,
        Field::MFDefaultFlags,
        static_cast<FieldEditMethodSig>(&ShaderParameterMVec4f::editHandleValue),
        static_cast<FieldGetMethodSig >(&ShaderParameterMVec4f::getHandleValue));

    oType.addInitialDesc(pDesc);
}


ShaderParameterMVec4fBase::TypeObject ShaderParameterMVec4fBase::_type(
    ShaderParameterMVec4fBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&ShaderParameterMVec4fBase::createEmptyLocal),
    ShaderParameterMVec4f::initMethod,
    ShaderParameterMVec4f::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&ShaderParameterMVec4fBase::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"ShaderParameterMVec4f\"\n"
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
    "\t\ttype=\"Vec4f\"\n"
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

FieldContainerType &ShaderParameterMVec4fBase::getType(void)
{
    return _type;
}

const FieldContainerType &ShaderParameterMVec4fBase::getType(void) const
{
    return _type;
}

UInt32 ShaderParameterMVec4fBase::getContainerSize(void) const
{
    return sizeof(ShaderParameterMVec4f);
}

/*------------------------- decorator get ------------------------------*/


MFVec4f *ShaderParameterMVec4fBase::editMFValue(void)
{
    editMField(ValueFieldMask, _mfValue);

    return &_mfValue;
}

const MFVec4f *ShaderParameterMVec4fBase::getMFValue(void) const
{
    return &_mfValue;
}

#ifdef OSG_1_GET_COMPAT
MFVec4f             *ShaderParameterMVec4fBase::getMFValue          (void)
{
    return this->editMFValue          ();
}
#endif





/*------------------------------ access -----------------------------------*/

UInt32 ShaderParameterMVec4fBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        returnValue += _mfValue.getBinSize();
    }

    return returnValue;
}

void ShaderParameterMVec4fBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _mfValue.copyToBin(pMem);
    }
}

void ShaderParameterMVec4fBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _mfValue.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ShaderParameterMVec4fTransitPtr ShaderParameterMVec4fBase::create(void)
{
    ShaderParameterMVec4fTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ShaderParameterMVec4f>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ShaderParameterMVec4fTransitPtr ShaderParameterMVec4fBase::createLocal(BitVector bFlags)
{
    ShaderParameterMVec4fTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ShaderParameterMVec4f>(tmpPtr);
    }

    return fc;
}

//! create an empty new instance of the class, do not copy the prototype
ShaderParameterMVec4f *ShaderParameterMVec4fBase::createEmpty(void)
{
    ShaderParameterMVec4f *returnValue;

    newPtr<ShaderParameterMVec4f>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &= 
        ~Thread::getCurrentLocalFlags(); 

    return returnValue;
}

ShaderParameterMVec4f *ShaderParameterMVec4fBase::createEmptyLocal(BitVector bFlags)
{
    ShaderParameterMVec4f *returnValue;

    newPtr<ShaderParameterMVec4f>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShaderParameterMVec4fBase::shallowCopy(void) const
{
    ShaderParameterMVec4f *tmpPtr;

    newPtr(tmpPtr, 
           dynamic_cast<const ShaderParameterMVec4f *>(this), 
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}

FieldContainerTransitPtr ShaderParameterMVec4fBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ShaderParameterMVec4f *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShaderParameterMVec4f *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

ShaderParameterMVec4fBase::ShaderParameterMVec4fBase(void) :
    Inherited(),
    _mfValue                  ()
{
}

ShaderParameterMVec4fBase::ShaderParameterMVec4fBase(const ShaderParameterMVec4fBase &source) :
    Inherited(source),
    _mfValue                  (source._mfValue                  )
{
}


/*-------------------------- destructors ----------------------------------*/

ShaderParameterMVec4fBase::~ShaderParameterMVec4fBase(void)
{
}


GetFieldHandlePtr ShaderParameterMVec4fBase::getHandleValue           (void) const
{
    MFVec4f::GetHandlePtr returnValue(
        new  MFVec4f::GetHandle(
             &_mfValue, 
             this->getType().getFieldDesc(ValueFieldId)));

    return returnValue;
}

EditFieldHandlePtr ShaderParameterMVec4fBase::editHandleValue          (void)
{
    MFVec4f::EditHandlePtr returnValue(
        new  MFVec4f::EditHandle(
             &_mfValue, 
             this->getType().getFieldDesc(ValueFieldId)));

    editMField(ValueFieldMask, _mfValue);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ShaderParameterMVec4fBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<ShaderParameterMVec4fBase *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ShaderParameterMVec4fBase::createAspectCopy(void) const
{
    ShaderParameterMVec4f *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ShaderParameterMVec4f *>(this));

    return returnValue;
}
#endif

void ShaderParameterMVec4fBase::resolveLinks(void)
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
DataType FieldTraits<ShaderParameterMVec4f *>::_type("ShaderParameterMVec4fPtr", "ShaderParameterPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ShaderParameterMVec4f *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           ShaderParameterMVec4f *, 
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           ShaderParameterMVec4f *, 
                           0);

OSG_END_NAMESPACE
