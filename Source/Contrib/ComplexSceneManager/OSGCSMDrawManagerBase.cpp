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
 **     class CSMDrawManager!
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



#include "OSGCSMDrawer.h"               // AppDrawer Class

#include "OSGCSMDrawManagerBase.h"
#include "OSGCSMDrawManager.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CSMDrawManager
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var CSMDrawer *     CSMDrawManagerBase::_sfAppDrawer
    
*/

/*! \var CSMDrawer *     CSMDrawManagerBase::_mfDrawer
    
*/

/*! \var bool            CSMDrawManagerBase::_sfParallel
    
*/

/*! \var std::string     CSMDrawManagerBase::_sfSyncBarrierName
    
*/

/*! \var std::string     CSMDrawManagerBase::_sfSwapBarrierName
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<CSMDrawManager *, nsOSG>::_type(
    "CSMDrawManagerPtr", 
    "AttachmentContainerPtr", 
    CSMDrawManager::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(CSMDrawManager *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           CSMDrawManager *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           CSMDrawManager *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void CSMDrawManagerBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecCSMDrawerPtr::Description(
        SFUnrecCSMDrawerPtr::getClassType(),
        "appDrawer",
        "",
        AppDrawerFieldId, AppDrawerFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMDrawManager::editHandleAppDrawer),
        static_cast<FieldGetMethodSig >(&CSMDrawManager::getHandleAppDrawer));

    oType.addInitialDesc(pDesc);

    pDesc = new MFUnrecCSMDrawerPtr::Description(
        MFUnrecCSMDrawerPtr::getClassType(),
        "drawer",
        "",
        DrawerFieldId, DrawerFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMDrawManager::editHandleDrawer),
        static_cast<FieldGetMethodSig >(&CSMDrawManager::getHandleDrawer));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "parallel",
        "",
        ParallelFieldId, ParallelFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMDrawManager::editHandleParallel),
        static_cast<FieldGetMethodSig >(&CSMDrawManager::getHandleParallel));

    oType.addInitialDesc(pDesc);

    pDesc = new SFString::Description(
        SFString::getClassType(),
        "syncBarrierName",
        "",
        SyncBarrierNameFieldId, SyncBarrierNameFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMDrawManager::editHandleSyncBarrierName),
        static_cast<FieldGetMethodSig >(&CSMDrawManager::getHandleSyncBarrierName));

    oType.addInitialDesc(pDesc);

    pDesc = new SFString::Description(
        SFString::getClassType(),
        "swapBarrierName",
        "",
        SwapBarrierNameFieldId, SwapBarrierNameFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMDrawManager::editHandleSwapBarrierName),
        static_cast<FieldGetMethodSig >(&CSMDrawManager::getHandleSwapBarrierName));

    oType.addInitialDesc(pDesc);
}


CSMDrawManagerBase::TypeObject CSMDrawManagerBase::_type(
    CSMDrawManagerBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&CSMDrawManagerBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&CSMDrawManager::initMethod),
    reinterpret_cast<ExitContainerF>(&CSMDrawManager::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&CSMDrawManager::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"CSMDrawManager\"\n"
    "    parent=\"AttachmentContainer\"\n"
    "    library=\"ContribCSM\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"true\"\n"
    "    >\n"
    "\t<Field\n"
    "\t\tname=\"appDrawer\"\n"
    "\t\ttype=\"CSMDrawer\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "        category=\"pointer\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"drawer\"\n"
    "\t\ttype=\"CSMDrawer\"\n"
    "\t\tcardinality=\"multi\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "        category=\"pointer\"\n"
    "\t>\n"
    "\t</Field>\n"
    "    <Field\n"
    "       name=\"parallel\"\n"
    "       type=\"bool\"\n"
    "       cardinality=\"single\"\n"
    "       visibility=\"external\"\n"
    "       access=\"public\"\n"
    "    >\n"
    "    </Field>\n"
    "\t<Field\n"
    "\t\tname=\"syncBarrierName\"\n"
    "\t\ttype=\"std::string\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"&quot;&quot;\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"swapBarrierName\"\n"
    "\t\ttype=\"std::string\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"&quot;&quot;\"\n"
    "\t>\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &CSMDrawManagerBase::getType(void)
{
    return _type;
}

const FieldContainerType &CSMDrawManagerBase::getType(void) const
{
    return _type;
}

UInt32 CSMDrawManagerBase::getContainerSize(void) const
{
    return sizeof(CSMDrawManager);
}

/*------------------------- decorator get ------------------------------*/


//! Get the CSMDrawManager::_sfAppDrawer field.
const SFUnrecCSMDrawerPtr *CSMDrawManagerBase::getSFAppDrawer(void) const
{
    return &_sfAppDrawer;
}

SFUnrecCSMDrawerPtr *CSMDrawManagerBase::editSFAppDrawer      (void)
{
    editSField(AppDrawerFieldMask);

    return &_sfAppDrawer;
}

//! Get the value of the CSMDrawManager::_sfAppDrawer field.
CSMDrawer * CSMDrawManagerBase::getAppDrawer(void) const
{
    return _sfAppDrawer.getValue();
}

//! Set the value of the CSMDrawManager::_sfAppDrawer field.
void CSMDrawManagerBase::setAppDrawer(CSMDrawer * const value)
{
    editSField(AppDrawerFieldMask);

    _sfAppDrawer.setValue(value);
}


//! Get the CSMDrawManager::_mfDrawer field.
const MFUnrecCSMDrawerPtr *CSMDrawManagerBase::getMFDrawer(void) const
{
    return &_mfDrawer;
}

MFUnrecCSMDrawerPtr *CSMDrawManagerBase::editMFDrawer         (void)
{
    editMField(DrawerFieldMask, _mfDrawer);

    return &_mfDrawer;
}
CSMDrawer * CSMDrawManagerBase::getDrawer(const UInt32 index) const
{
    return _mfDrawer[index];
}

SFBool *CSMDrawManagerBase::editSFParallel(void)
{
    editSField(ParallelFieldMask);

    return &_sfParallel;
}

const SFBool *CSMDrawManagerBase::getSFParallel(void) const
{
    return &_sfParallel;
}


SFString *CSMDrawManagerBase::editSFSyncBarrierName(void)
{
    editSField(SyncBarrierNameFieldMask);

    return &_sfSyncBarrierName;
}

const SFString *CSMDrawManagerBase::getSFSyncBarrierName(void) const
{
    return &_sfSyncBarrierName;
}


SFString *CSMDrawManagerBase::editSFSwapBarrierName(void)
{
    editSField(SwapBarrierNameFieldMask);

    return &_sfSwapBarrierName;
}

const SFString *CSMDrawManagerBase::getSFSwapBarrierName(void) const
{
    return &_sfSwapBarrierName;
}




void CSMDrawManagerBase::pushToDrawer(CSMDrawer * const value)
{
    editMField(DrawerFieldMask, _mfDrawer);

    _mfDrawer.push_back(value);
}

void CSMDrawManagerBase::assignDrawer   (const MFUnrecCSMDrawerPtr &value)
{
    MFUnrecCSMDrawerPtr::const_iterator elemIt  =
        value.begin();
    MFUnrecCSMDrawerPtr::const_iterator elemEnd =
        value.end  ();

    static_cast<CSMDrawManager *>(this)->clearDrawer();

    while(elemIt != elemEnd)
    {
        this->pushToDrawer(*elemIt);

        ++elemIt;
    }
}

void CSMDrawManagerBase::removeFromDrawer(UInt32 uiIndex)
{
    if(uiIndex < _mfDrawer.size())
    {
        editMField(DrawerFieldMask, _mfDrawer);

        _mfDrawer.erase(uiIndex);
    }
}

void CSMDrawManagerBase::removeObjFromDrawer(CSMDrawer * const value)
{
    Int32 iElemIdx = _mfDrawer.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(DrawerFieldMask, _mfDrawer);

        _mfDrawer.erase(iElemIdx);
    }
}
void CSMDrawManagerBase::clearDrawer(void)
{
    editMField(DrawerFieldMask, _mfDrawer);


    _mfDrawer.clear();
}



/*------------------------------ access -----------------------------------*/

SizeT CSMDrawManagerBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (AppDrawerFieldMask & whichField))
    {
        returnValue += _sfAppDrawer.getBinSize();
    }
    if(FieldBits::NoField != (DrawerFieldMask & whichField))
    {
        returnValue += _mfDrawer.getBinSize();
    }
    if(FieldBits::NoField != (ParallelFieldMask & whichField))
    {
        returnValue += _sfParallel.getBinSize();
    }
    if(FieldBits::NoField != (SyncBarrierNameFieldMask & whichField))
    {
        returnValue += _sfSyncBarrierName.getBinSize();
    }
    if(FieldBits::NoField != (SwapBarrierNameFieldMask & whichField))
    {
        returnValue += _sfSwapBarrierName.getBinSize();
    }

    return returnValue;
}

void CSMDrawManagerBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (AppDrawerFieldMask & whichField))
    {
        _sfAppDrawer.copyToBin(pMem);
    }
    if(FieldBits::NoField != (DrawerFieldMask & whichField))
    {
        _mfDrawer.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ParallelFieldMask & whichField))
    {
        _sfParallel.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SyncBarrierNameFieldMask & whichField))
    {
        _sfSyncBarrierName.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SwapBarrierNameFieldMask & whichField))
    {
        _sfSwapBarrierName.copyToBin(pMem);
    }
}

void CSMDrawManagerBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (AppDrawerFieldMask & whichField))
    {
        editSField(AppDrawerFieldMask);
        _sfAppDrawer.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (DrawerFieldMask & whichField))
    {
        editMField(DrawerFieldMask, _mfDrawer);
        _mfDrawer.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ParallelFieldMask & whichField))
    {
        editSField(ParallelFieldMask);
        _sfParallel.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SyncBarrierNameFieldMask & whichField))
    {
        editSField(SyncBarrierNameFieldMask);
        _sfSyncBarrierName.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SwapBarrierNameFieldMask & whichField))
    {
        editSField(SwapBarrierNameFieldMask);
        _sfSwapBarrierName.copyFromBin(pMem);
    }
}

//! create a new instance of the class
CSMDrawManagerTransitPtr CSMDrawManagerBase::createLocal(BitVector bFlags)
{
    CSMDrawManagerTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<CSMDrawManager>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
CSMDrawManagerTransitPtr CSMDrawManagerBase::createDependent(BitVector bFlags)
{
    CSMDrawManagerTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<CSMDrawManager>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
CSMDrawManagerTransitPtr CSMDrawManagerBase::create(void)
{
    return createLocal();
}

CSMDrawManager *CSMDrawManagerBase::createEmptyLocal(BitVector bFlags)
{
    CSMDrawManager *returnValue;

    newPtr<CSMDrawManager>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
CSMDrawManager *CSMDrawManagerBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr CSMDrawManagerBase::shallowCopyLocal(
    BitVector bFlags) const
{
    CSMDrawManager *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CSMDrawManager *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr CSMDrawManagerBase::shallowCopyDependent(
    BitVector bFlags) const
{
    CSMDrawManager *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CSMDrawManager *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr CSMDrawManagerBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

CSMDrawManagerBase::CSMDrawManagerBase(void) :
    Inherited(),
    _sfAppDrawer              (NULL),
    _mfDrawer                 (),
    _sfParallel               (),
    _sfSyncBarrierName        (std::string("")),
    _sfSwapBarrierName        (std::string(""))
{
}

CSMDrawManagerBase::CSMDrawManagerBase(const CSMDrawManagerBase &source) :
    Inherited(source),
    _sfAppDrawer              (NULL),
    _mfDrawer                 (),
    _sfParallel               (source._sfParallel               ),
    _sfSyncBarrierName        (source._sfSyncBarrierName        ),
    _sfSwapBarrierName        (source._sfSwapBarrierName        )
{
}


/*-------------------------- destructors ----------------------------------*/

CSMDrawManagerBase::~CSMDrawManagerBase(void)
{
}

void CSMDrawManagerBase::onCreate(const CSMDrawManager *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        CSMDrawManager *pThis = static_cast<CSMDrawManager *>(this);

        pThis->setAppDrawer(source->getAppDrawer());

        MFUnrecCSMDrawerPtr::const_iterator DrawerIt  =
            source->_mfDrawer.begin();
        MFUnrecCSMDrawerPtr::const_iterator DrawerEnd =
            source->_mfDrawer.end  ();

        while(DrawerIt != DrawerEnd)
        {
            pThis->pushToDrawer(*DrawerIt);

            ++DrawerIt;
        }
    }
}

GetFieldHandlePtr CSMDrawManagerBase::getHandleAppDrawer       (void) const
{
    SFUnrecCSMDrawerPtr::GetHandlePtr returnValue(
        new  SFUnrecCSMDrawerPtr::GetHandle(
             &_sfAppDrawer,
             this->getType().getFieldDesc(AppDrawerFieldId),
             const_cast<CSMDrawManagerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMDrawManagerBase::editHandleAppDrawer      (void)
{
    SFUnrecCSMDrawerPtr::EditHandlePtr returnValue(
        new  SFUnrecCSMDrawerPtr::EditHandle(
             &_sfAppDrawer,
             this->getType().getFieldDesc(AppDrawerFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&CSMDrawManager::setAppDrawer,
                    static_cast<CSMDrawManager *>(this), _1));

    editSField(AppDrawerFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMDrawManagerBase::getHandleDrawer          (void) const
{
    MFUnrecCSMDrawerPtr::GetHandlePtr returnValue(
        new  MFUnrecCSMDrawerPtr::GetHandle(
             &_mfDrawer,
             this->getType().getFieldDesc(DrawerFieldId),
             const_cast<CSMDrawManagerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMDrawManagerBase::editHandleDrawer         (void)
{
    MFUnrecCSMDrawerPtr::EditHandlePtr returnValue(
        new  MFUnrecCSMDrawerPtr::EditHandle(
             &_mfDrawer,
             this->getType().getFieldDesc(DrawerFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&CSMDrawManager::pushToDrawer,
                    static_cast<CSMDrawManager *>(this), _1));
    returnValue->setRemoveMethod(
        boost::bind(&CSMDrawManager::removeFromDrawer,
                    static_cast<CSMDrawManager *>(this), _1));
    returnValue->setRemoveObjMethod(
        boost::bind(&CSMDrawManager::removeObjFromDrawer,
                    static_cast<CSMDrawManager *>(this), _1));
    returnValue->setClearMethod(
        boost::bind(&CSMDrawManager::clearDrawer,
                    static_cast<CSMDrawManager *>(this)));

    editMField(DrawerFieldMask, _mfDrawer);

    return returnValue;
}

GetFieldHandlePtr CSMDrawManagerBase::getHandleParallel        (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfParallel,
             this->getType().getFieldDesc(ParallelFieldId),
             const_cast<CSMDrawManagerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMDrawManagerBase::editHandleParallel       (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfParallel,
             this->getType().getFieldDesc(ParallelFieldId),
             this));


    editSField(ParallelFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMDrawManagerBase::getHandleSyncBarrierName (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfSyncBarrierName,
             this->getType().getFieldDesc(SyncBarrierNameFieldId),
             const_cast<CSMDrawManagerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMDrawManagerBase::editHandleSyncBarrierName(void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfSyncBarrierName,
             this->getType().getFieldDesc(SyncBarrierNameFieldId),
             this));


    editSField(SyncBarrierNameFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMDrawManagerBase::getHandleSwapBarrierName (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfSwapBarrierName,
             this->getType().getFieldDesc(SwapBarrierNameFieldId),
             const_cast<CSMDrawManagerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMDrawManagerBase::editHandleSwapBarrierName(void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfSwapBarrierName,
             this->getType().getFieldDesc(SwapBarrierNameFieldId),
             this));


    editSField(SwapBarrierNameFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void CSMDrawManagerBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    CSMDrawManager *pThis = static_cast<CSMDrawManager *>(this);

    pThis->execSync(static_cast<CSMDrawManager *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *CSMDrawManagerBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    CSMDrawManager *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const CSMDrawManager *>(pRefAspect),
                  dynamic_cast<const CSMDrawManager *>(this));

    return returnValue;
}
#endif

void CSMDrawManagerBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<CSMDrawManager *>(this)->setAppDrawer(NULL);

    static_cast<CSMDrawManager *>(this)->clearDrawer();


}


OSG_END_NAMESPACE
