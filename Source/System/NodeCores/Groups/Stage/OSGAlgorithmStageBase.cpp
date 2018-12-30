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
 **     class AlgorithmStage!
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



#include "OSGAlgorithm.h"               // Algorithm Class

#include "OSGAlgorithmStageBase.h"
#include "OSGAlgorithmStage.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::AlgorithmStage
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Algorithm *     AlgorithmStageBase::_sfAlgorithm
    
*/

/*! \var UInt32          AlgorithmStageBase::_sfProjectionMode
    
*/

/*! \var bool            AlgorithmStageBase::_sfCopyViewing
    
*/

/*! \var Matrix          AlgorithmStageBase::_sfProjectionMatrix
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<AlgorithmStage *, nsOSG>::_type(
    "AlgorithmStagePtr", 
    "StagePtr", 
    AlgorithmStage::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(AlgorithmStage *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void AlgorithmStageBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecAlgorithmPtr::Description(
        SFUnrecAlgorithmPtr::getClassType(),
        "algorithm",
        "",
        AlgorithmFieldId, AlgorithmFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&AlgorithmStage::editHandleAlgorithm),
        static_cast<FieldGetMethodSig >(&AlgorithmStage::getHandleAlgorithm));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "projectionMode",
        "",
        ProjectionModeFieldId, ProjectionModeFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&AlgorithmStage::editHandleProjectionMode),
        static_cast<FieldGetMethodSig >(&AlgorithmStage::getHandleProjectionMode));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "copyViewing",
        "",
        CopyViewingFieldId, CopyViewingFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&AlgorithmStage::editHandleCopyViewing),
        static_cast<FieldGetMethodSig >(&AlgorithmStage::getHandleCopyViewing));

    oType.addInitialDesc(pDesc);

    pDesc = new SFMatrix::Description(
        SFMatrix::getClassType(),
        "projectionMatrix",
        "",
        ProjectionMatrixFieldId, ProjectionMatrixFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&AlgorithmStage::editHandleProjectionMatrix),
        static_cast<FieldGetMethodSig >(&AlgorithmStage::getHandleProjectionMatrix));

    oType.addInitialDesc(pDesc);
}


AlgorithmStageBase::TypeObject AlgorithmStageBase::_type(
    AlgorithmStageBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&AlgorithmStageBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&AlgorithmStage::initMethod),
    reinterpret_cast<ExitContainerF>(&AlgorithmStage::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&AlgorithmStage::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"AlgorithmStage\"\n"
    "   parent=\"Stage\"\n"
    "   library=\"Group\"\n"
    "   pointerfieldtypes=\"none\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   isNodeCore=\"true\"\n"
    "   docGroupBase=\"GrpGroupStage\"\n"
    "   >\n"
    "  <Field\n"
    "\t name=\"algorithm\"\n"
    "\t type=\"AlgorithmPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"NULL\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"projectionMode\"\n"
    "\t type=\"UInt32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"0x0001\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"copyViewing\"\n"
    "\t type=\"bool\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"false\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"projectionMatrix\"\n"
    "\t type=\"Matrix\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &AlgorithmStageBase::getType(void)
{
    return _type;
}

const FieldContainerType &AlgorithmStageBase::getType(void) const
{
    return _type;
}

UInt32 AlgorithmStageBase::getContainerSize(void) const
{
    return sizeof(AlgorithmStage);
}

/*------------------------- decorator get ------------------------------*/


//! Get the AlgorithmStage::_sfAlgorithm field.
const SFUnrecAlgorithmPtr *AlgorithmStageBase::getSFAlgorithm(void) const
{
    return &_sfAlgorithm;
}

SFUnrecAlgorithmPtr *AlgorithmStageBase::editSFAlgorithm      (void)
{
    editSField(AlgorithmFieldMask);

    return &_sfAlgorithm;
}

//! Get the value of the AlgorithmStage::_sfAlgorithm field.
Algorithm * AlgorithmStageBase::getAlgorithm(void) const
{
    return _sfAlgorithm.getValue();
}

//! Set the value of the AlgorithmStage::_sfAlgorithm field.
void AlgorithmStageBase::setAlgorithm(Algorithm * const value)
{
    editSField(AlgorithmFieldMask);

    _sfAlgorithm.setValue(value);
}


SFUInt32 *AlgorithmStageBase::editSFProjectionMode(void)
{
    editSField(ProjectionModeFieldMask);

    return &_sfProjectionMode;
}

const SFUInt32 *AlgorithmStageBase::getSFProjectionMode(void) const
{
    return &_sfProjectionMode;
}


SFBool *AlgorithmStageBase::editSFCopyViewing(void)
{
    editSField(CopyViewingFieldMask);

    return &_sfCopyViewing;
}

const SFBool *AlgorithmStageBase::getSFCopyViewing(void) const
{
    return &_sfCopyViewing;
}


SFMatrix *AlgorithmStageBase::editSFProjectionMatrix(void)
{
    editSField(ProjectionMatrixFieldMask);

    return &_sfProjectionMatrix;
}

const SFMatrix *AlgorithmStageBase::getSFProjectionMatrix(void) const
{
    return &_sfProjectionMatrix;
}






/*------------------------------ access -----------------------------------*/

SizeT AlgorithmStageBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (AlgorithmFieldMask & whichField))
    {
        returnValue += _sfAlgorithm.getBinSize();
    }
    if(FieldBits::NoField != (ProjectionModeFieldMask & whichField))
    {
        returnValue += _sfProjectionMode.getBinSize();
    }
    if(FieldBits::NoField != (CopyViewingFieldMask & whichField))
    {
        returnValue += _sfCopyViewing.getBinSize();
    }
    if(FieldBits::NoField != (ProjectionMatrixFieldMask & whichField))
    {
        returnValue += _sfProjectionMatrix.getBinSize();
    }

    return returnValue;
}

void AlgorithmStageBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (AlgorithmFieldMask & whichField))
    {
        _sfAlgorithm.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ProjectionModeFieldMask & whichField))
    {
        _sfProjectionMode.copyToBin(pMem);
    }
    if(FieldBits::NoField != (CopyViewingFieldMask & whichField))
    {
        _sfCopyViewing.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ProjectionMatrixFieldMask & whichField))
    {
        _sfProjectionMatrix.copyToBin(pMem);
    }
}

void AlgorithmStageBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (AlgorithmFieldMask & whichField))
    {
        editSField(AlgorithmFieldMask);
        _sfAlgorithm.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ProjectionModeFieldMask & whichField))
    {
        editSField(ProjectionModeFieldMask);
        _sfProjectionMode.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (CopyViewingFieldMask & whichField))
    {
        editSField(CopyViewingFieldMask);
        _sfCopyViewing.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ProjectionMatrixFieldMask & whichField))
    {
        editSField(ProjectionMatrixFieldMask);
        _sfProjectionMatrix.copyFromBin(pMem);
    }
}

//! create a new instance of the class
AlgorithmStageTransitPtr AlgorithmStageBase::createLocal(BitVector bFlags)
{
    AlgorithmStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<AlgorithmStage>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
AlgorithmStageTransitPtr AlgorithmStageBase::createDependent(BitVector bFlags)
{
    AlgorithmStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<AlgorithmStage>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
AlgorithmStageTransitPtr AlgorithmStageBase::create(void)
{
    AlgorithmStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<AlgorithmStage>(tmpPtr);
    }

    return fc;
}

AlgorithmStage *AlgorithmStageBase::createEmptyLocal(BitVector bFlags)
{
    AlgorithmStage *returnValue;

    newPtr<AlgorithmStage>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
AlgorithmStage *AlgorithmStageBase::createEmpty(void)
{
    AlgorithmStage *returnValue;

    newPtr<AlgorithmStage>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr AlgorithmStageBase::shallowCopyLocal(
    BitVector bFlags) const
{
    AlgorithmStage *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const AlgorithmStage *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr AlgorithmStageBase::shallowCopyDependent(
    BitVector bFlags) const
{
    AlgorithmStage *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const AlgorithmStage *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr AlgorithmStageBase::shallowCopy(void) const
{
    AlgorithmStage *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const AlgorithmStage *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

AlgorithmStageBase::AlgorithmStageBase(void) :
    Inherited(),
    _sfAlgorithm              (NULL),
    _sfProjectionMode         (UInt32(0x0001)),
    _sfCopyViewing            (bool(false)),
    _sfProjectionMatrix       ()
{
}

AlgorithmStageBase::AlgorithmStageBase(const AlgorithmStageBase &source) :
    Inherited(source),
    _sfAlgorithm              (NULL),
    _sfProjectionMode         (source._sfProjectionMode         ),
    _sfCopyViewing            (source._sfCopyViewing            ),
    _sfProjectionMatrix       (source._sfProjectionMatrix       )
{
}


/*-------------------------- destructors ----------------------------------*/

AlgorithmStageBase::~AlgorithmStageBase(void)
{
}

void AlgorithmStageBase::onCreate(const AlgorithmStage *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        AlgorithmStage *pThis = static_cast<AlgorithmStage *>(this);

        pThis->setAlgorithm(source->getAlgorithm());
    }
}

GetFieldHandlePtr AlgorithmStageBase::getHandleAlgorithm       (void) const
{
    SFUnrecAlgorithmPtr::GetHandlePtr returnValue(
        new  SFUnrecAlgorithmPtr::GetHandle(
             &_sfAlgorithm,
             this->getType().getFieldDesc(AlgorithmFieldId),
             const_cast<AlgorithmStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr AlgorithmStageBase::editHandleAlgorithm      (void)
{
    SFUnrecAlgorithmPtr::EditHandlePtr returnValue(
        new  SFUnrecAlgorithmPtr::EditHandle(
             &_sfAlgorithm,
             this->getType().getFieldDesc(AlgorithmFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&AlgorithmStage::setAlgorithm,
                    static_cast<AlgorithmStage *>(this), _1));

    editSField(AlgorithmFieldMask);

    return returnValue;
}

GetFieldHandlePtr AlgorithmStageBase::getHandleProjectionMode  (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfProjectionMode,
             this->getType().getFieldDesc(ProjectionModeFieldId),
             const_cast<AlgorithmStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr AlgorithmStageBase::editHandleProjectionMode (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfProjectionMode,
             this->getType().getFieldDesc(ProjectionModeFieldId),
             this));


    editSField(ProjectionModeFieldMask);

    return returnValue;
}

GetFieldHandlePtr AlgorithmStageBase::getHandleCopyViewing     (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfCopyViewing,
             this->getType().getFieldDesc(CopyViewingFieldId),
             const_cast<AlgorithmStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr AlgorithmStageBase::editHandleCopyViewing    (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfCopyViewing,
             this->getType().getFieldDesc(CopyViewingFieldId),
             this));


    editSField(CopyViewingFieldMask);

    return returnValue;
}

GetFieldHandlePtr AlgorithmStageBase::getHandleProjectionMatrix (void) const
{
    SFMatrix::GetHandlePtr returnValue(
        new  SFMatrix::GetHandle(
             &_sfProjectionMatrix,
             this->getType().getFieldDesc(ProjectionMatrixFieldId),
             const_cast<AlgorithmStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr AlgorithmStageBase::editHandleProjectionMatrix(void)
{
    SFMatrix::EditHandlePtr returnValue(
        new  SFMatrix::EditHandle(
             &_sfProjectionMatrix,
             this->getType().getFieldDesc(ProjectionMatrixFieldId),
             this));


    editSField(ProjectionMatrixFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void AlgorithmStageBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    AlgorithmStage *pThis = static_cast<AlgorithmStage *>(this);

    pThis->execSync(static_cast<AlgorithmStage *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *AlgorithmStageBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    AlgorithmStage *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const AlgorithmStage *>(pRefAspect),
                  dynamic_cast<const AlgorithmStage *>(this));

    return returnValue;
}
#endif

void AlgorithmStageBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<AlgorithmStage *>(this)->setAlgorithm(NULL);


}


OSG_END_NAMESPACE
