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
 **     class ShaderVariableMVec4f!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"




#include "OSGShaderVariableMVec4fBase.h"
#include "OSGShaderVariableMVec4f.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ShaderVariableMVec4f
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Vec4f           ShaderVariableMVec4fBase::_mfValue
    variable value
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ShaderVariableMVec4f *, nsOSG>::_type("ShaderVariableMVec4fPtr", "ShaderValueVariablePtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(ShaderVariableMVec4f *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ShaderVariableMVec4f *,
                           nsOSG);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ShaderVariableMVec4f *,
                           nsOSG);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ShaderVariableMVec4fBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFVec4f::Description(
        MFVec4f::getClassType(),
        "value",
        "variable value\n",
        ValueFieldId, ValueFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderVariableMVec4f::editHandleValue),
        static_cast<FieldGetMethodSig >(&ShaderVariableMVec4f::getHandleValue));

    oType.addInitialDesc(pDesc);
}


ShaderVariableMVec4fBase::TypeObject ShaderVariableMVec4fBase::_type(
    ShaderVariableMVec4fBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&ShaderVariableMVec4fBase::createEmptyLocal),
    ShaderVariableMVec4f::initMethod,
    ShaderVariableMVec4f::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&ShaderVariableMVec4f::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"ShaderVariableMVec4f\"\n"
    "   parent=\"ShaderValueVariable\"\n"
    "   library=\"System\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   docGroupBase=\"GrpSystemShader\"\n"
    "   >\n"
    "  <Field\n"
    "\t name=\"value\"\n"
    "\t type=\"Vec4f\"\n"
    "\t cardinality=\"multi\"\n"
    "\t visibility=\"external\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tvariable value\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ShaderVariableMVec4fBase::getType(void)
{
    return _type;
}

const FieldContainerType &ShaderVariableMVec4fBase::getType(void) const
{
    return _type;
}

UInt32 ShaderVariableMVec4fBase::getContainerSize(void) const
{
    return sizeof(ShaderVariableMVec4f);
}

/*------------------------- decorator get ------------------------------*/


MFVec4f *ShaderVariableMVec4fBase::editMFValue(void)
{
    editMField(ValueFieldMask, _mfValue);

    return &_mfValue;
}

const MFVec4f *ShaderVariableMVec4fBase::getMFValue(void) const
{
    return &_mfValue;
}






/*------------------------------ access -----------------------------------*/

UInt32 ShaderVariableMVec4fBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        returnValue += _mfValue.getBinSize();
    }

    return returnValue;
}

void ShaderVariableMVec4fBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _mfValue.copyToBin(pMem);
    }
}

void ShaderVariableMVec4fBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        editMField(ValueFieldMask, _mfValue);
        _mfValue.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ShaderVariableMVec4fTransitPtr ShaderVariableMVec4fBase::createLocal(BitVector bFlags)
{
    ShaderVariableMVec4fTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ShaderVariableMVec4f>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ShaderVariableMVec4fTransitPtr ShaderVariableMVec4fBase::createDependent(BitVector bFlags)
{
    ShaderVariableMVec4fTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ShaderVariableMVec4f>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ShaderVariableMVec4fTransitPtr ShaderVariableMVec4fBase::create(void)
{
    ShaderVariableMVec4fTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ShaderVariableMVec4f>(tmpPtr);
    }

    return fc;
}

ShaderVariableMVec4f *ShaderVariableMVec4fBase::createEmptyLocal(BitVector bFlags)
{
    ShaderVariableMVec4f *returnValue;

    newPtr<ShaderVariableMVec4f>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ShaderVariableMVec4f *ShaderVariableMVec4fBase::createEmpty(void)
{
    ShaderVariableMVec4f *returnValue;

    newPtr<ShaderVariableMVec4f>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr ShaderVariableMVec4fBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ShaderVariableMVec4f *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShaderVariableMVec4f *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShaderVariableMVec4fBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ShaderVariableMVec4f *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShaderVariableMVec4f *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShaderVariableMVec4fBase::shallowCopy(void) const
{
    ShaderVariableMVec4f *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const ShaderVariableMVec4f *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

ShaderVariableMVec4fBase::ShaderVariableMVec4fBase(void) :
    Inherited(),
    _mfValue                  ()
{
}

ShaderVariableMVec4fBase::ShaderVariableMVec4fBase(const ShaderVariableMVec4fBase &source) :
    Inherited(source),
    _mfValue                  (source._mfValue                  )
{
}


/*-------------------------- destructors ----------------------------------*/

ShaderVariableMVec4fBase::~ShaderVariableMVec4fBase(void)
{
}


GetFieldHandlePtr ShaderVariableMVec4fBase::getHandleValue           (void) const
{
    MFVec4f::GetHandlePtr returnValue(
        new  MFVec4f::GetHandle(
             &_mfValue,
             this->getType().getFieldDesc(ValueFieldId),
             const_cast<ShaderVariableMVec4fBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderVariableMVec4fBase::editHandleValue          (void)
{
    MFVec4f::EditHandlePtr returnValue(
        new  MFVec4f::EditHandle(
             &_mfValue,
             this->getType().getFieldDesc(ValueFieldId),
             this));


    editMField(ValueFieldMask, _mfValue);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ShaderVariableMVec4fBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ShaderVariableMVec4f *pThis = static_cast<ShaderVariableMVec4f *>(this);

    pThis->execSync(static_cast<ShaderVariableMVec4f *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ShaderVariableMVec4fBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ShaderVariableMVec4f *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ShaderVariableMVec4f *>(pRefAspect),
                  dynamic_cast<const ShaderVariableMVec4f *>(this));

    return returnValue;
}
#endif

void ShaderVariableMVec4fBase::resolveLinks(void)
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


OSG_END_NAMESPACE
