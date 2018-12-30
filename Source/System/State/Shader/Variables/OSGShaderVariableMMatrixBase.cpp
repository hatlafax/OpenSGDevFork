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
 **     class ShaderVariableMMatrix!
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




#include "OSGShaderVariableMMatrixBase.h"
#include "OSGShaderVariableMMatrix.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ShaderVariableMMatrix
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Matrix          ShaderVariableMMatrixBase::_mfValue
    variable value
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<ShaderVariableMMatrix *, nsOSG>::_type(
    "ShaderVariableMMatrixPtr", 
    "ShaderValueVariablePtr", 
    ShaderVariableMMatrix::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(ShaderVariableMMatrix *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ShaderVariableMMatrix *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ShaderVariableMMatrix *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ShaderVariableMMatrixBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFMatrix::Description(
        MFMatrix::getClassType(),
        "value",
        "variable value\n",
        ValueFieldId, ValueFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderVariableMMatrix::editHandleValue),
        static_cast<FieldGetMethodSig >(&ShaderVariableMMatrix::getHandleValue));

    oType.addInitialDesc(pDesc);
}


ShaderVariableMMatrixBase::TypeObject ShaderVariableMMatrixBase::_type(
    ShaderVariableMMatrixBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&ShaderVariableMMatrixBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&ShaderVariableMMatrix::initMethod),
    reinterpret_cast<ExitContainerF>(&ShaderVariableMMatrix::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&ShaderVariableMMatrix::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"ShaderVariableMMatrix\"\n"
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
    "\t type=\"Matrix\"\n"
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

FieldContainerType &ShaderVariableMMatrixBase::getType(void)
{
    return _type;
}

const FieldContainerType &ShaderVariableMMatrixBase::getType(void) const
{
    return _type;
}

UInt32 ShaderVariableMMatrixBase::getContainerSize(void) const
{
    return sizeof(ShaderVariableMMatrix);
}

/*------------------------- decorator get ------------------------------*/


MFMatrix *ShaderVariableMMatrixBase::editMFValue(void)
{
    editMField(ValueFieldMask, _mfValue);

    return &_mfValue;
}

const MFMatrix *ShaderVariableMMatrixBase::getMFValue(void) const
{
    return &_mfValue;
}






/*------------------------------ access -----------------------------------*/

SizeT ShaderVariableMMatrixBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        returnValue += _mfValue.getBinSize();
    }

    return returnValue;
}

void ShaderVariableMMatrixBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _mfValue.copyToBin(pMem);
    }
}

void ShaderVariableMMatrixBase::copyFromBin(BinaryDataHandler &pMem,
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
ShaderVariableMMatrixTransitPtr ShaderVariableMMatrixBase::createLocal(BitVector bFlags)
{
    ShaderVariableMMatrixTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ShaderVariableMMatrix>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ShaderVariableMMatrixTransitPtr ShaderVariableMMatrixBase::createDependent(BitVector bFlags)
{
    ShaderVariableMMatrixTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ShaderVariableMMatrix>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ShaderVariableMMatrixTransitPtr ShaderVariableMMatrixBase::create(void)
{
    ShaderVariableMMatrixTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ShaderVariableMMatrix>(tmpPtr);
    }

    return fc;
}

ShaderVariableMMatrix *ShaderVariableMMatrixBase::createEmptyLocal(BitVector bFlags)
{
    ShaderVariableMMatrix *returnValue;

    newPtr<ShaderVariableMMatrix>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ShaderVariableMMatrix *ShaderVariableMMatrixBase::createEmpty(void)
{
    ShaderVariableMMatrix *returnValue;

    newPtr<ShaderVariableMMatrix>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr ShaderVariableMMatrixBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ShaderVariableMMatrix *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShaderVariableMMatrix *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShaderVariableMMatrixBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ShaderVariableMMatrix *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShaderVariableMMatrix *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShaderVariableMMatrixBase::shallowCopy(void) const
{
    ShaderVariableMMatrix *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const ShaderVariableMMatrix *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

ShaderVariableMMatrixBase::ShaderVariableMMatrixBase(void) :
    Inherited(),
    _mfValue                  ()
{
}

ShaderVariableMMatrixBase::ShaderVariableMMatrixBase(const ShaderVariableMMatrixBase &source) :
    Inherited(source),
    _mfValue                  (source._mfValue                  )
{
}


/*-------------------------- destructors ----------------------------------*/

ShaderVariableMMatrixBase::~ShaderVariableMMatrixBase(void)
{
}


GetFieldHandlePtr ShaderVariableMMatrixBase::getHandleValue           (void) const
{
    MFMatrix::GetHandlePtr returnValue(
        new  MFMatrix::GetHandle(
             &_mfValue,
             this->getType().getFieldDesc(ValueFieldId),
             const_cast<ShaderVariableMMatrixBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderVariableMMatrixBase::editHandleValue          (void)
{
    MFMatrix::EditHandlePtr returnValue(
        new  MFMatrix::EditHandle(
             &_mfValue,
             this->getType().getFieldDesc(ValueFieldId),
             this));


    editMField(ValueFieldMask, _mfValue);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ShaderVariableMMatrixBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ShaderVariableMMatrix *pThis = static_cast<ShaderVariableMMatrix *>(this);

    pThis->execSync(static_cast<ShaderVariableMMatrix *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ShaderVariableMMatrixBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ShaderVariableMMatrix *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ShaderVariableMMatrix *>(pRefAspect),
                  dynamic_cast<const ShaderVariableMMatrix *>(this));

    return returnValue;
}
#endif

void ShaderVariableMMatrixBase::resolveLinks(void)
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
