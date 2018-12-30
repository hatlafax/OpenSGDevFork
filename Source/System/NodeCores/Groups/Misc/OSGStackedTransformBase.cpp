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
 **     class StackedTransform!
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



#include "OSGTransformationElement.h"   // TransformElements Class

#include "OSGStackedTransformBase.h"
#include "OSGStackedTransform.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StackedTransform
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var TransformationElement * StackedTransformBase::_mfTransformElements
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<StackedTransform *, nsOSG>::_type(
    "StackedTransformPtr", 
    "GroupPtr", 
    StackedTransform::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(StackedTransform *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           StackedTransform *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           StackedTransform *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void StackedTransformBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFUnrecChildTransformationElementPtr::Description(
        MFUnrecChildTransformationElementPtr::getClassType(),
        "TransformElements",
        "",
        TransformElementsFieldId, TransformElementsFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FNullCheckAccess),
        static_cast<FieldEditMethodSig>(&StackedTransform::editHandleTransformElements),
        static_cast<FieldGetMethodSig >(&StackedTransform::getHandleTransformElements));

    oType.addInitialDesc(pDesc);
}


StackedTransformBase::TypeObject StackedTransformBase::_type(
    StackedTransformBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&StackedTransformBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&StackedTransform::initMethod),
    reinterpret_cast<ExitContainerF>(&StackedTransform::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&StackedTransform::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"StackedTransform\"\n"
    "    parent=\"Group\"\n"
    "    library=\"Group\"\n"
    "    structure=\"concrete\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    isNodeCore=\"true\"\n"
    "    >\n"
    "  <Field\n"
    "      name=\"TransformElements\"\n"
    "      type=\"TransformationElement\"\n"
    "      category=\"childpointer\"\n"
    "      cardinality=\"multi\"\n"
    "      childParentType=\"FieldContainer\"\n"
    "      visibility=\"external\"\n"
    "      access=\"public\"\n"
    "      ptrFieldAccess = \"nullCheck\"\n"
    "      linkParentField=\"ParentStack\"\n"
    "      >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &StackedTransformBase::getType(void)
{
    return _type;
}

const FieldContainerType &StackedTransformBase::getType(void) const
{
    return _type;
}

UInt32 StackedTransformBase::getContainerSize(void) const
{
    return sizeof(StackedTransform);
}

/*------------------------- decorator get ------------------------------*/


//! Get the StackedTransform::_mfTransformElements field.
const MFUnrecChildTransformationElementPtr *StackedTransformBase::getMFTransformElements(void) const
{
    return &_mfTransformElements;
}
TransformationElement * StackedTransformBase::getTransformElements(const UInt32 index) const
{
    return _mfTransformElements[index];
}



void StackedTransformBase::pushToTransformElements(TransformationElement * const value)
{
    if(value == NULL)
        return;

    editMField(TransformElementsFieldMask, _mfTransformElements);

    _mfTransformElements.push_back(value);
}

void StackedTransformBase::assignTransformElements(const MFUnrecChildTransformationElementPtr &value)
{
    MFUnrecChildTransformationElementPtr::const_iterator elemIt  =
        value.begin();
    MFUnrecChildTransformationElementPtr::const_iterator elemEnd =
        value.end  ();

    static_cast<StackedTransform *>(this)->clearTransformElements();

    while(elemIt != elemEnd)
    {
        this->pushToTransformElements(*elemIt);

        ++elemIt;
    }
}

void StackedTransformBase::insertIntoTransformElements(UInt32               uiIndex,
                                                   TransformationElement * const value   )
{
    if(value == NULL)
        return;

    editMField(TransformElementsFieldMask, _mfTransformElements);

    MFUnrecChildTransformationElementPtr::iterator fieldIt = _mfTransformElements.begin_nc();

    fieldIt += uiIndex;

    _mfTransformElements.insert(fieldIt, value);
}

void StackedTransformBase::replaceInTransformElements(UInt32               uiIndex,
                                                       TransformationElement * const value   )
{
    if(value == NULL)
        return;

    if(uiIndex >= _mfTransformElements.size())
        return;

    editMField(TransformElementsFieldMask, _mfTransformElements);

    _mfTransformElements.replace(uiIndex, value);
}

void StackedTransformBase::replaceObjInTransformElements(TransformationElement * const pOldElem,
                                                        TransformationElement * const pNewElem)
{
    if(pNewElem == NULL)
        return;

    Int32  elemIdx = _mfTransformElements.findIndex(pOldElem);

    if(elemIdx != -1)
    {
        editMField(TransformElementsFieldMask, _mfTransformElements);

        _mfTransformElements.replace(elemIdx, pNewElem);
    }
}

void StackedTransformBase::removeFromTransformElements(UInt32 uiIndex)
{
    if(uiIndex < _mfTransformElements.size())
    {
        editMField(TransformElementsFieldMask, _mfTransformElements);

        _mfTransformElements.erase(uiIndex);
    }
}

void StackedTransformBase::removeObjFromTransformElements(TransformationElement * const value)
{
    Int32 iElemIdx = _mfTransformElements.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(TransformElementsFieldMask, _mfTransformElements);

        _mfTransformElements.erase(iElemIdx);
    }
}
void StackedTransformBase::clearTransformElements(void)
{
    editMField(TransformElementsFieldMask, _mfTransformElements);


    _mfTransformElements.clear();
}



/*------------------------------ access -----------------------------------*/

SizeT StackedTransformBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (TransformElementsFieldMask & whichField))
    {
        returnValue += _mfTransformElements.getBinSize();
    }

    return returnValue;
}

void StackedTransformBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (TransformElementsFieldMask & whichField))
    {
        _mfTransformElements.copyToBin(pMem);
    }
}

void StackedTransformBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (TransformElementsFieldMask & whichField))
    {
        editMField(TransformElementsFieldMask, _mfTransformElements);
        _mfTransformElements.copyFromBin(pMem);
    }
}

//! create a new instance of the class
StackedTransformTransitPtr StackedTransformBase::createLocal(BitVector bFlags)
{
    StackedTransformTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<StackedTransform>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
StackedTransformTransitPtr StackedTransformBase::createDependent(BitVector bFlags)
{
    StackedTransformTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<StackedTransform>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
StackedTransformTransitPtr StackedTransformBase::create(void)
{
    StackedTransformTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<StackedTransform>(tmpPtr);
    }

    return fc;
}

StackedTransform *StackedTransformBase::createEmptyLocal(BitVector bFlags)
{
    StackedTransform *returnValue;

    newPtr<StackedTransform>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
StackedTransform *StackedTransformBase::createEmpty(void)
{
    StackedTransform *returnValue;

    newPtr<StackedTransform>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr StackedTransformBase::shallowCopyLocal(
    BitVector bFlags) const
{
    StackedTransform *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const StackedTransform *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr StackedTransformBase::shallowCopyDependent(
    BitVector bFlags) const
{
    StackedTransform *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const StackedTransform *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr StackedTransformBase::shallowCopy(void) const
{
    StackedTransform *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const StackedTransform *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

StackedTransformBase::StackedTransformBase(void) :
    Inherited(),
    _mfTransformElements      (this,
                          TransformElementsFieldId,
                          TransformationElement::ParentStackFieldId)
{
}

StackedTransformBase::StackedTransformBase(const StackedTransformBase &source) :
    Inherited(source),
    _mfTransformElements      (this,
                          TransformElementsFieldId,
                          TransformationElement::ParentStackFieldId)
{
}


/*-------------------------- destructors ----------------------------------*/

StackedTransformBase::~StackedTransformBase(void)
{
}

/*-------------------------------------------------------------------------*/
/* Child linking                                                           */

bool StackedTransformBase::unlinkChild(
    FieldContainer * const pChild,
    UInt16           const childFieldId)
{
    if(childFieldId == TransformElementsFieldId)
    {
        TransformationElement * pTypedChild =
            dynamic_cast<TransformationElement *>(pChild);

        if(pTypedChild != NULL)
        {
            Int32 iChildIdx = _mfTransformElements.findIndex(pTypedChild);

            if(iChildIdx != -1)
            {
                editMField(TransformElementsFieldMask, _mfTransformElements);

                _mfTransformElements.erase(iChildIdx);

                return true;
            }

            SWARNING << "Parent (["        << this
                     << "] id ["           << this->getId()
                     << "] type ["         << this->getType().getCName()
                     << "] childFieldId [" << childFieldId
                     << "]) - Child (["    << pChild
                     << "] id ["           << pChild->getId()
                     << "] type ["         << pChild->getType().getCName()
                     << "]): link inconsistent!"
                     << std::endl;

            return false;
        }

        return false;
    }


    return Inherited::unlinkChild(pChild, childFieldId);
}

void StackedTransformBase::onCreate(const StackedTransform *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        StackedTransform *pThis = static_cast<StackedTransform *>(this);

        MFUnrecChildTransformationElementPtr::const_iterator TransformElementsIt  =
            source->_mfTransformElements.begin();
        MFUnrecChildTransformationElementPtr::const_iterator TransformElementsEnd =
            source->_mfTransformElements.end  ();

        while(TransformElementsIt != TransformElementsEnd)
        {
            pThis->pushToTransformElements(*TransformElementsIt);

            ++TransformElementsIt;
        }
    }
}

GetFieldHandlePtr StackedTransformBase::getHandleTransformElements (void) const
{
    MFUnrecChildTransformationElementPtr::GetHandlePtr returnValue(
        new  MFUnrecChildTransformationElementPtr::GetHandle(
             &_mfTransformElements,
             this->getType().getFieldDesc(TransformElementsFieldId),
             const_cast<StackedTransformBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr StackedTransformBase::editHandleTransformElements(void)
{
    MFUnrecChildTransformationElementPtr::EditHandlePtr returnValue(
        new  MFUnrecChildTransformationElementPtr::EditHandle(
             &_mfTransformElements,
             this->getType().getFieldDesc(TransformElementsFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&StackedTransform::pushToTransformElements,
                    static_cast<StackedTransform *>(this), _1));
    returnValue->setInsertMethod(
        boost::bind(&StackedTransform::insertIntoTransformElements,
                    static_cast<StackedTransform *>(this), _1, _2));
    returnValue->setReplaceMethod(
        boost::bind(&StackedTransform::replaceInTransformElements,
                    static_cast<StackedTransform *>(this), _1, _2));
    returnValue->setReplaceObjMethod(
        boost::bind(&StackedTransform::replaceObjInTransformElements,
                    static_cast<StackedTransform *>(this), _1, _2));
    returnValue->setRemoveMethod(
        boost::bind(&StackedTransform::removeFromTransformElements,
                    static_cast<StackedTransform *>(this), _1));
    returnValue->setRemoveObjMethod(
        boost::bind(&StackedTransform::removeObjFromTransformElements,
                    static_cast<StackedTransform *>(this), _1));
    returnValue->setClearMethod(
        boost::bind(&StackedTransform::clearTransformElements,
                    static_cast<StackedTransform *>(this)));

    editMField(TransformElementsFieldMask, _mfTransformElements);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void StackedTransformBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    StackedTransform *pThis = static_cast<StackedTransform *>(this);

    pThis->execSync(static_cast<StackedTransform *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *StackedTransformBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    StackedTransform *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const StackedTransform *>(pRefAspect),
                  dynamic_cast<const StackedTransform *>(this));

    return returnValue;
}
#endif

void StackedTransformBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<StackedTransform *>(this)->clearTransformElements();


}


OSG_END_NAMESPACE
