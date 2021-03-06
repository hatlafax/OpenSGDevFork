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
 **     class DescMaterialManager!
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



#include "OSGMaterialFactory.h"         // MaterialFactory Class
#include "OSGHashKeyToFieldContainerMap.h" // MaterialMap Class

#include "OSGDescMaterialManagerBase.h"
#include "OSGDescMaterialManager.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DescMaterialManager
    This is a concrete implementation of the abstract material manager.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var MaterialFactory * DescMaterialManagerBase::_sfMaterialFactory
    The material factory is responsible for providing a concrete
    ChunkMaterial from a given MaterialDesc object. The ChunkMaterial
    might be shared with other parts of the scene.
*/

/*! \var HashKeyToFieldContainerMap * DescMaterialManagerBase::_sfMaterialMap
    
*/

/*! \var HashKeyToFieldContainerMap * DescMaterialManagerBase::_sfImageMap
    
*/

/*! \var bool            DescMaterialManagerBase::_sfEvalEnvironmentHash
    If true, a hash value describing the environment is stored into the MaterialDesc
    instance on adding a material.
*/

/*! \var BitVector       DescMaterialManagerBase::_sfExcludeHashingMask
    All field mask that are contained in this value do not participate in the
    hash calculation procedure.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<DescMaterialManager *, nsOSG>::_type(
    "DescMaterialManagerPtr", 
    "MaterialManagerPtr", 
    DescMaterialManager::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(DescMaterialManager *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           DescMaterialManager *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           DescMaterialManager *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void DescMaterialManagerBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecMaterialFactoryPtr::Description(
        SFUnrecMaterialFactoryPtr::getClassType(),
        "materialFactory",
        "The material factory is responsible for providing a concrete\n"
        "ChunkMaterial from a given MaterialDesc object. The ChunkMaterial\n"
        "might be shared with other parts of the scene.\n",
        MaterialFactoryFieldId, MaterialFactoryFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DescMaterialManager::editHandleMaterialFactory),
        static_cast<FieldGetMethodSig >(&DescMaterialManager::getHandleMaterialFactory));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecHashKeyToFieldContainerMapPtr::Description(
        SFUnrecHashKeyToFieldContainerMapPtr::getClassType(),
        "materialMap",
        "",
        MaterialMapFieldId, MaterialMapFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DescMaterialManager::editHandleMaterialMap),
        static_cast<FieldGetMethodSig >(&DescMaterialManager::getHandleMaterialMap));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecHashKeyToFieldContainerMapPtr::Description(
        SFUnrecHashKeyToFieldContainerMapPtr::getClassType(),
        "imageMap",
        "",
        ImageMapFieldId, ImageMapFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DescMaterialManager::editHandleImageMap),
        static_cast<FieldGetMethodSig >(&DescMaterialManager::getHandleImageMap));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "evalEnvironmentHash",
        "If true, a hash value describing the environment is stored into the MaterialDesc\n"
        "instance on adding a material.\n",
        EvalEnvironmentHashFieldId, EvalEnvironmentHashFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DescMaterialManager::editHandleEvalEnvironmentHash),
        static_cast<FieldGetMethodSig >(&DescMaterialManager::getHandleEvalEnvironmentHash));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBitVector::Description(
        SFBitVector::getClassType(),
        "excludeHashingMask",
        "All field mask that are contained in this value do not participate in the\n"
        "hash calculation procedure.\n",
        ExcludeHashingMaskFieldId, ExcludeHashingMaskFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DescMaterialManager::editHandleExcludeHashingMask),
        static_cast<FieldGetMethodSig >(&DescMaterialManager::getHandleExcludeHashingMask));

    oType.addInitialDesc(pDesc);
}


DescMaterialManagerBase::TypeObject DescMaterialManagerBase::_type(
    DescMaterialManagerBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&DescMaterialManagerBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&DescMaterialManager::initMethod),
    reinterpret_cast<ExitContainerF>(&DescMaterialManager::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&DescMaterialManager::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"DescMaterialManager\"\n"
    "    parent=\"MaterialManager\"\n"
    "    library=\"ContribTechniques\"\n"
    "    structure=\"concrete\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    >\n"
    "    This is a concrete implementation of the abstract material manager.\n"
    "\n"
    "    <Field\n"
    "        name=\"materialFactory\"\n"
    "        type=\"MaterialFactory\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        category=\"pointer\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "        The material factory is responsible for providing a concrete\n"
    "        ChunkMaterial from a given MaterialDesc object. The ChunkMaterial\n"
    "        might be shared with other parts of the scene.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"materialMap\"\n"
    "        type=\"HashKeyToFieldContainerMap\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"protected\"\n"
    "        category=\"pointer\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"imageMap\"\n"
    "        type=\"HashKeyToFieldContainerMap\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        category=\"pointer\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"evalEnvironmentHash\"\n"
    "        type=\"bool\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"false\"\n"
    "        >\n"
    "        If true, a hash value describing the environment is stored into the MaterialDesc\n"
    "        instance on adding a material.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"excludeHashingMask\"\n"
    "        type=\"BitVector\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"0\"\n"
    "        >\n"
    "        All field mask that are contained in this value do not participate in the\n"
    "        hash calculation procedure.\n"
    "    </Field>\n"
    "\n"
    "</FieldContainer>\n",
    "This is a concrete implementation of the abstract material manager.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &DescMaterialManagerBase::getType(void)
{
    return _type;
}

const FieldContainerType &DescMaterialManagerBase::getType(void) const
{
    return _type;
}

UInt32 DescMaterialManagerBase::getContainerSize(void) const
{
    return sizeof(DescMaterialManager);
}

/*------------------------- decorator get ------------------------------*/


//! Get the DescMaterialManager::_sfMaterialFactory field.
const SFUnrecMaterialFactoryPtr *DescMaterialManagerBase::getSFMaterialFactory(void) const
{
    return &_sfMaterialFactory;
}

SFUnrecMaterialFactoryPtr *DescMaterialManagerBase::editSFMaterialFactory(void)
{
    editSField(MaterialFactoryFieldMask);

    return &_sfMaterialFactory;
}

//! Get the value of the DescMaterialManager::_sfMaterialFactory field.
MaterialFactory * DescMaterialManagerBase::getMaterialFactory(void) const
{
    return _sfMaterialFactory.getValue();
}

//! Set the value of the DescMaterialManager::_sfMaterialFactory field.
void DescMaterialManagerBase::setMaterialFactory(MaterialFactory * const value)
{
    editSField(MaterialFactoryFieldMask);

    _sfMaterialFactory.setValue(value);
}


//! Get the DescMaterialManager::_sfMaterialMap field.
const SFUnrecHashKeyToFieldContainerMapPtr *DescMaterialManagerBase::getSFMaterialMap(void) const
{
    return &_sfMaterialMap;
}

SFUnrecHashKeyToFieldContainerMapPtr *DescMaterialManagerBase::editSFMaterialMap    (void)
{
    editSField(MaterialMapFieldMask);

    return &_sfMaterialMap;
}

//! Get the value of the DescMaterialManager::_sfMaterialMap field.
HashKeyToFieldContainerMap * DescMaterialManagerBase::getMaterialMap(void) const
{
    return _sfMaterialMap.getValue();
}

//! Set the value of the DescMaterialManager::_sfMaterialMap field.
void DescMaterialManagerBase::setMaterialMap(HashKeyToFieldContainerMap * const value)
{
    editSField(MaterialMapFieldMask);

    _sfMaterialMap.setValue(value);
}


//! Get the DescMaterialManager::_sfImageMap field.
const SFUnrecHashKeyToFieldContainerMapPtr *DescMaterialManagerBase::getSFImageMap(void) const
{
    return &_sfImageMap;
}

SFUnrecHashKeyToFieldContainerMapPtr *DescMaterialManagerBase::editSFImageMap       (void)
{
    editSField(ImageMapFieldMask);

    return &_sfImageMap;
}

//! Get the value of the DescMaterialManager::_sfImageMap field.
HashKeyToFieldContainerMap * DescMaterialManagerBase::getImageMap(void) const
{
    return _sfImageMap.getValue();
}

//! Set the value of the DescMaterialManager::_sfImageMap field.
void DescMaterialManagerBase::setImageMap(HashKeyToFieldContainerMap * const value)
{
    editSField(ImageMapFieldMask);

    _sfImageMap.setValue(value);
}


SFBool *DescMaterialManagerBase::editSFEvalEnvironmentHash(void)
{
    editSField(EvalEnvironmentHashFieldMask);

    return &_sfEvalEnvironmentHash;
}

const SFBool *DescMaterialManagerBase::getSFEvalEnvironmentHash(void) const
{
    return &_sfEvalEnvironmentHash;
}


SFBitVector *DescMaterialManagerBase::editSFExcludeHashingMask(void)
{
    editSField(ExcludeHashingMaskFieldMask);

    return &_sfExcludeHashingMask;
}

const SFBitVector *DescMaterialManagerBase::getSFExcludeHashingMask(void) const
{
    return &_sfExcludeHashingMask;
}






/*------------------------------ access -----------------------------------*/

SizeT DescMaterialManagerBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (MaterialFactoryFieldMask & whichField))
    {
        returnValue += _sfMaterialFactory.getBinSize();
    }
    if(FieldBits::NoField != (MaterialMapFieldMask & whichField))
    {
        returnValue += _sfMaterialMap.getBinSize();
    }
    if(FieldBits::NoField != (ImageMapFieldMask & whichField))
    {
        returnValue += _sfImageMap.getBinSize();
    }
    if(FieldBits::NoField != (EvalEnvironmentHashFieldMask & whichField))
    {
        returnValue += _sfEvalEnvironmentHash.getBinSize();
    }
    if(FieldBits::NoField != (ExcludeHashingMaskFieldMask & whichField))
    {
        returnValue += _sfExcludeHashingMask.getBinSize();
    }

    return returnValue;
}

void DescMaterialManagerBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (MaterialFactoryFieldMask & whichField))
    {
        _sfMaterialFactory.copyToBin(pMem);
    }
    if(FieldBits::NoField != (MaterialMapFieldMask & whichField))
    {
        _sfMaterialMap.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ImageMapFieldMask & whichField))
    {
        _sfImageMap.copyToBin(pMem);
    }
    if(FieldBits::NoField != (EvalEnvironmentHashFieldMask & whichField))
    {
        _sfEvalEnvironmentHash.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ExcludeHashingMaskFieldMask & whichField))
    {
        _sfExcludeHashingMask.copyToBin(pMem);
    }
}

void DescMaterialManagerBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (MaterialFactoryFieldMask & whichField))
    {
        editSField(MaterialFactoryFieldMask);
        _sfMaterialFactory.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (MaterialMapFieldMask & whichField))
    {
        editSField(MaterialMapFieldMask);
        _sfMaterialMap.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ImageMapFieldMask & whichField))
    {
        editSField(ImageMapFieldMask);
        _sfImageMap.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (EvalEnvironmentHashFieldMask & whichField))
    {
        editSField(EvalEnvironmentHashFieldMask);
        _sfEvalEnvironmentHash.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ExcludeHashingMaskFieldMask & whichField))
    {
        editSField(ExcludeHashingMaskFieldMask);
        _sfExcludeHashingMask.copyFromBin(pMem);
    }
}

//! create a new instance of the class
DescMaterialManagerTransitPtr DescMaterialManagerBase::createLocal(BitVector bFlags)
{
    DescMaterialManagerTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<DescMaterialManager>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
DescMaterialManagerTransitPtr DescMaterialManagerBase::createDependent(BitVector bFlags)
{
    DescMaterialManagerTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<DescMaterialManager>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
DescMaterialManagerTransitPtr DescMaterialManagerBase::create(void)
{
    DescMaterialManagerTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<DescMaterialManager>(tmpPtr);
    }

    return fc;
}

DescMaterialManager *DescMaterialManagerBase::createEmptyLocal(BitVector bFlags)
{
    DescMaterialManager *returnValue;

    newPtr<DescMaterialManager>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
DescMaterialManager *DescMaterialManagerBase::createEmpty(void)
{
    DescMaterialManager *returnValue;

    newPtr<DescMaterialManager>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr DescMaterialManagerBase::shallowCopyLocal(
    BitVector bFlags) const
{
    DescMaterialManager *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DescMaterialManager *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr DescMaterialManagerBase::shallowCopyDependent(
    BitVector bFlags) const
{
    DescMaterialManager *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DescMaterialManager *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr DescMaterialManagerBase::shallowCopy(void) const
{
    DescMaterialManager *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const DescMaterialManager *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

DescMaterialManagerBase::DescMaterialManagerBase(void) :
    Inherited(),
    _sfMaterialFactory        (NULL),
    _sfMaterialMap            (NULL),
    _sfImageMap               (NULL),
    _sfEvalEnvironmentHash    (bool(false)),
    _sfExcludeHashingMask     (BitVector(0))
{
}

DescMaterialManagerBase::DescMaterialManagerBase(const DescMaterialManagerBase &source) :
    Inherited(source),
    _sfMaterialFactory        (NULL),
    _sfMaterialMap            (NULL),
    _sfImageMap               (NULL),
    _sfEvalEnvironmentHash    (source._sfEvalEnvironmentHash    ),
    _sfExcludeHashingMask     (source._sfExcludeHashingMask     )
{
}


/*-------------------------- destructors ----------------------------------*/

DescMaterialManagerBase::~DescMaterialManagerBase(void)
{
}

void DescMaterialManagerBase::onCreate(const DescMaterialManager *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        DescMaterialManager *pThis = static_cast<DescMaterialManager *>(this);

        pThis->setMaterialFactory(source->getMaterialFactory());

        pThis->setMaterialMap(source->getMaterialMap());

        pThis->setImageMap(source->getImageMap());
    }
}

GetFieldHandlePtr DescMaterialManagerBase::getHandleMaterialFactory (void) const
{
    SFUnrecMaterialFactoryPtr::GetHandlePtr returnValue(
        new  SFUnrecMaterialFactoryPtr::GetHandle(
             &_sfMaterialFactory,
             this->getType().getFieldDesc(MaterialFactoryFieldId),
             const_cast<DescMaterialManagerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialManagerBase::editHandleMaterialFactory(void)
{
    SFUnrecMaterialFactoryPtr::EditHandlePtr returnValue(
        new  SFUnrecMaterialFactoryPtr::EditHandle(
             &_sfMaterialFactory,
             this->getType().getFieldDesc(MaterialFactoryFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DescMaterialManager::setMaterialFactory,
                    static_cast<DescMaterialManager *>(this), _1));

    editSField(MaterialFactoryFieldMask);

    return returnValue;
}

GetFieldHandlePtr DescMaterialManagerBase::getHandleMaterialMap     (void) const
{
    SFUnrecHashKeyToFieldContainerMapPtr::GetHandlePtr returnValue(
        new  SFUnrecHashKeyToFieldContainerMapPtr::GetHandle(
             &_sfMaterialMap,
             this->getType().getFieldDesc(MaterialMapFieldId),
             const_cast<DescMaterialManagerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialManagerBase::editHandleMaterialMap    (void)
{
    SFUnrecHashKeyToFieldContainerMapPtr::EditHandlePtr returnValue(
        new  SFUnrecHashKeyToFieldContainerMapPtr::EditHandle(
             &_sfMaterialMap,
             this->getType().getFieldDesc(MaterialMapFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DescMaterialManager::setMaterialMap,
                    static_cast<DescMaterialManager *>(this), _1));

    editSField(MaterialMapFieldMask);

    return returnValue;
}

GetFieldHandlePtr DescMaterialManagerBase::getHandleImageMap        (void) const
{
    SFUnrecHashKeyToFieldContainerMapPtr::GetHandlePtr returnValue(
        new  SFUnrecHashKeyToFieldContainerMapPtr::GetHandle(
             &_sfImageMap,
             this->getType().getFieldDesc(ImageMapFieldId),
             const_cast<DescMaterialManagerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialManagerBase::editHandleImageMap       (void)
{
    SFUnrecHashKeyToFieldContainerMapPtr::EditHandlePtr returnValue(
        new  SFUnrecHashKeyToFieldContainerMapPtr::EditHandle(
             &_sfImageMap,
             this->getType().getFieldDesc(ImageMapFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DescMaterialManager::setImageMap,
                    static_cast<DescMaterialManager *>(this), _1));

    editSField(ImageMapFieldMask);

    return returnValue;
}

GetFieldHandlePtr DescMaterialManagerBase::getHandleEvalEnvironmentHash (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfEvalEnvironmentHash,
             this->getType().getFieldDesc(EvalEnvironmentHashFieldId),
             const_cast<DescMaterialManagerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialManagerBase::editHandleEvalEnvironmentHash(void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfEvalEnvironmentHash,
             this->getType().getFieldDesc(EvalEnvironmentHashFieldId),
             this));


    editSField(EvalEnvironmentHashFieldMask);

    return returnValue;
}

GetFieldHandlePtr DescMaterialManagerBase::getHandleExcludeHashingMask (void) const
{
    SFBitVector::GetHandlePtr returnValue(
        new  SFBitVector::GetHandle(
             &_sfExcludeHashingMask,
             this->getType().getFieldDesc(ExcludeHashingMaskFieldId),
             const_cast<DescMaterialManagerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DescMaterialManagerBase::editHandleExcludeHashingMask(void)
{
    SFBitVector::EditHandlePtr returnValue(
        new  SFBitVector::EditHandle(
             &_sfExcludeHashingMask,
             this->getType().getFieldDesc(ExcludeHashingMaskFieldId),
             this));


    editSField(ExcludeHashingMaskFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void DescMaterialManagerBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    DescMaterialManager *pThis = static_cast<DescMaterialManager *>(this);

    pThis->execSync(static_cast<DescMaterialManager *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *DescMaterialManagerBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    DescMaterialManager *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const DescMaterialManager *>(pRefAspect),
                  dynamic_cast<const DescMaterialManager *>(this));

    return returnValue;
}
#endif

void DescMaterialManagerBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<DescMaterialManager *>(this)->setMaterialFactory(NULL);

    static_cast<DescMaterialManager *>(this)->setMaterialMap(NULL);

    static_cast<DescMaterialManager *>(this)->setImageMap(NULL);


}


OSG_END_NAMESPACE
