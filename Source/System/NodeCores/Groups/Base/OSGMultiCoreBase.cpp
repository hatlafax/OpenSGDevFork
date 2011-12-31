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
 **     class MultiCore!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"



#include "OSGNodeCore.h"                // Cores Class

#include "OSGMultiCoreBase.h"
#include "OSGMultiCore.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MultiCore
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var NodeCore *      MultiCoreBase::_mfCores
    
*/

/*! \var bool            MultiCoreBase::_sfExitOnSkip
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<MultiCore *, nsOSG>::_type(
    "MultiCorePtr", 
    "GroupPtr", 
    MultiCore::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(MultiCore *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           MultiCore *,
                           nsOSG);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           MultiCore *,
                           nsOSG);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void MultiCoreBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFUnrecChildNodeCorePtr::Description(
        MFUnrecChildNodeCorePtr::getClassType(),
        "cores",
        "",
        CoresFieldId, CoresFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&MultiCore::editHandleCores),
        static_cast<FieldGetMethodSig >(&MultiCore::getHandleCores));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "exitOnSkip",
        "",
        ExitOnSkipFieldId, ExitOnSkipFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&MultiCore::editHandleExitOnSkip),
        static_cast<FieldGetMethodSig >(&MultiCore::getHandleExitOnSkip));

    oType.addInitialDesc(pDesc);
}


MultiCoreBase::TypeObject MultiCoreBase::_type(
    MultiCoreBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&MultiCoreBase::createEmptyLocal),
    MultiCore::initMethod,
    MultiCore::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&MultiCore::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"MultiCore\"\n"
    "   parent=\"Group\"\n"
    "   library=\"System\"\n"
    "   structure=\"concrete\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   docGroupBase=\"GrpSystemNodeCoreGroups\"\n"
    "   >\n"
    "  <Field\n"
    "     name=\"cores\"\n"
    "     type=\"NodeCore\"\n"
    "     cardinality=\"multi\"\n"
    "     visibility=\"external\"\n"
    "     access=\"protected\"\n"
    "     category=\"childpointer\"\n"
    "     childParentType=\"FieldContainer\"\n"
    "     linkParentField=\"Parents\"\n"
    "     \n"
    "     pushToFieldAs=\"addCore\"\n"
    "     assignMFieldAs=\"assignCoresFrom\"\n"
    "     insertIntoMFieldAs=\"insertCore\"\n"
    "     replaceInMFieldIndexAs=\"replaceCore\"\n"
    "     replaceInMFieldObjectAs=\"replaceCoreByObj\"\n"
    "     removeFromMFieldIndexAs=\"subCore\"\n"
    "     removeFromMFieldObjectAs=\"subCoreByObj\"\n"
    "     clearFieldAs=\"clearCores\"\n"
    "     >\n"
    "  </Field>\n"
    "\n"
    "  <Field\n"
    "      name=\"exitOnSkip\"\n"
    "      type=\"bool\"\n"
    "      cardinality=\"single\"\n"
    "      visibility=\"external\"\n"
    "      defaultValue=\"false\">\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &MultiCoreBase::getType(void)
{
    return _type;
}

const FieldContainerType &MultiCoreBase::getType(void) const
{
    return _type;
}

UInt32 MultiCoreBase::getContainerSize(void) const
{
    return sizeof(MultiCore);
}

/*------------------------- decorator get ------------------------------*/


//! Get the MultiCore::_mfCores field.
const MFUnrecChildNodeCorePtr *MultiCoreBase::getMFCores(void) const
{
    return &_mfCores;
}

MFUnrecChildNodeCorePtr *MultiCoreBase::editMFCores          (void)
{
    editMField(CoresFieldMask, _mfCores);

    return &_mfCores;
}

SFBool *MultiCoreBase::editSFExitOnSkip(void)
{
    editSField(ExitOnSkipFieldMask);

    return &_sfExitOnSkip;
}

const SFBool *MultiCoreBase::getSFExitOnSkip(void) const
{
    return &_sfExitOnSkip;
}




void MultiCoreBase::addCore(NodeCore * const value)
{
    editMField(CoresFieldMask, _mfCores);

    _mfCores.push_back(value);
}

void MultiCoreBase::assignCoresFrom(const MFUnrecChildNodeCorePtr &value)
{
    MFUnrecChildNodeCorePtr::const_iterator elemIt  =
        value.begin();
    MFUnrecChildNodeCorePtr::const_iterator elemEnd =
        value.end  ();

    static_cast<MultiCore *>(this)->clearCores();

    while(elemIt != elemEnd)
    {
        this->addCore(*elemIt);

        ++elemIt;
    }
}

void MultiCoreBase::subCore(UInt32 uiIndex)
{
    if(uiIndex < _mfCores.size())
    {
        editMField(CoresFieldMask, _mfCores);

        _mfCores.erase(uiIndex);
    }
}

void MultiCoreBase::subCoreByObj(NodeCore * const value)
{
    Int32 iElemIdx = _mfCores.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(CoresFieldMask, _mfCores);

        _mfCores.erase(iElemIdx);
    }
}
void MultiCoreBase::clearCores(void)
{
    editMField(CoresFieldMask, _mfCores);


    _mfCores.clear();
}



/*------------------------------ access -----------------------------------*/

SizeT MultiCoreBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (CoresFieldMask & whichField))
    {
        returnValue += _mfCores.getBinSize();
    }
    if(FieldBits::NoField != (ExitOnSkipFieldMask & whichField))
    {
        returnValue += _sfExitOnSkip.getBinSize();
    }

    return returnValue;
}

void MultiCoreBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (CoresFieldMask & whichField))
    {
        _mfCores.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ExitOnSkipFieldMask & whichField))
    {
        _sfExitOnSkip.copyToBin(pMem);
    }
}

void MultiCoreBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (CoresFieldMask & whichField))
    {
        editMField(CoresFieldMask, _mfCores);
        _mfCores.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ExitOnSkipFieldMask & whichField))
    {
        editSField(ExitOnSkipFieldMask);
        _sfExitOnSkip.copyFromBin(pMem);
    }
}

//! create a new instance of the class
MultiCoreTransitPtr MultiCoreBase::createLocal(BitVector bFlags)
{
    MultiCoreTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<MultiCore>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
MultiCoreTransitPtr MultiCoreBase::createDependent(BitVector bFlags)
{
    MultiCoreTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<MultiCore>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
MultiCoreTransitPtr MultiCoreBase::create(void)
{
    MultiCoreTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<MultiCore>(tmpPtr);
    }

    return fc;
}

MultiCore *MultiCoreBase::createEmptyLocal(BitVector bFlags)
{
    MultiCore *returnValue;

    newPtr<MultiCore>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
MultiCore *MultiCoreBase::createEmpty(void)
{
    MultiCore *returnValue;

    newPtr<MultiCore>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr MultiCoreBase::shallowCopyLocal(
    BitVector bFlags) const
{
    MultiCore *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const MultiCore *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr MultiCoreBase::shallowCopyDependent(
    BitVector bFlags) const
{
    MultiCore *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const MultiCore *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr MultiCoreBase::shallowCopy(void) const
{
    MultiCore *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const MultiCore *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

MultiCoreBase::MultiCoreBase(void) :
    Inherited(),
    _mfCores                  (this,
                          CoresFieldId,
                          NodeCore::ParentsFieldId),
    _sfExitOnSkip             (bool(false))
{
}

MultiCoreBase::MultiCoreBase(const MultiCoreBase &source) :
    Inherited(source),
    _mfCores                  (this,
                          CoresFieldId,
                          NodeCore::ParentsFieldId),
    _sfExitOnSkip             (source._sfExitOnSkip             )
{
}


/*-------------------------- destructors ----------------------------------*/

MultiCoreBase::~MultiCoreBase(void)
{
}

/*-------------------------------------------------------------------------*/
/* Child linking                                                           */

bool MultiCoreBase::unlinkChild(
    FieldContainer * const pChild,
    UInt16           const childFieldId)
{
    if(childFieldId == CoresFieldId)
    {
        NodeCore * pTypedChild =
            dynamic_cast<NodeCore *>(pChild);

        if(pTypedChild != NULL)
        {
            Int32 iChildIdx = _mfCores.findIndex(pTypedChild);

            if(iChildIdx != -1)
            {
                editMField(CoresFieldMask, _mfCores);

                _mfCores.erase(iChildIdx);

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

void MultiCoreBase::onCreate(const MultiCore *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        MultiCore *pThis = static_cast<MultiCore *>(this);

        MFUnrecChildNodeCorePtr::const_iterator CoresIt  =
            source->_mfCores.begin();
        MFUnrecChildNodeCorePtr::const_iterator CoresEnd =
            source->_mfCores.end  ();

        while(CoresIt != CoresEnd)
        {
            pThis->addCore(*CoresIt);

            ++CoresIt;
        }
    }
}

GetFieldHandlePtr MultiCoreBase::getHandleCores           (void) const
{
    MFUnrecChildNodeCorePtr::GetHandlePtr returnValue(
        new  MFUnrecChildNodeCorePtr::GetHandle(
             &_mfCores,
             this->getType().getFieldDesc(CoresFieldId),
             const_cast<MultiCoreBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr MultiCoreBase::editHandleCores          (void)
{
    MFUnrecChildNodeCorePtr::EditHandlePtr returnValue(
        new  MFUnrecChildNodeCorePtr::EditHandle(
             &_mfCores,
             this->getType().getFieldDesc(CoresFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&MultiCore::addCore,
                    static_cast<MultiCore *>(this), _1));
    returnValue->setRemoveMethod(
        boost::bind(&MultiCore::subCore,
                    static_cast<MultiCore *>(this), _1));
    returnValue->setRemoveObjMethod(
        boost::bind(&MultiCore::subCoreByObj,
                    static_cast<MultiCore *>(this), _1));
    returnValue->setClearMethod(
        boost::bind(&MultiCore::clearCores,
                    static_cast<MultiCore *>(this)));

    editMField(CoresFieldMask, _mfCores);

    return returnValue;
}

GetFieldHandlePtr MultiCoreBase::getHandleExitOnSkip      (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfExitOnSkip,
             this->getType().getFieldDesc(ExitOnSkipFieldId),
             const_cast<MultiCoreBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr MultiCoreBase::editHandleExitOnSkip     (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfExitOnSkip,
             this->getType().getFieldDesc(ExitOnSkipFieldId),
             this));


    editSField(ExitOnSkipFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void MultiCoreBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    MultiCore *pThis = static_cast<MultiCore *>(this);

    pThis->execSync(static_cast<MultiCore *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *MultiCoreBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    MultiCore *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const MultiCore *>(pRefAspect),
                  dynamic_cast<const MultiCore *>(this));

    return returnValue;
}
#endif

void MultiCoreBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<MultiCore *>(this)->clearCores();


}


OSG_END_NAMESPACE
