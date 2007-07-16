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
 **     class SwitchMaterial!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESWITCHMATERIALINST

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>



#include <OSGMaterial.h> // Materials Class

#include "OSGSwitchMaterialBase.h"
#include "OSGSwitchMaterial.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SwitchMaterial
    Material that allows selection of one of the materials in the _mfMaterials
    field based on the value of the _sfChoice field.
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var MaterialPtr     SwitchMaterialBase::_mfMaterials
    Materials to choose from.
*/

/*! \var UInt32          SwitchMaterialBase::_sfChoice
    The material to actually use for drawing.
*/


void SwitchMaterialBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFMaterialPtr::Description(
        MFMaterialPtr::getClassType(),
        "materials",
        "Materials to choose from.\n",
        MaterialsFieldId, MaterialsFieldMask,
        false,
        Field::MFDefaultFlags,
        static_cast     <FieldEditMethodSig>(&SwitchMaterialBase::invalidEditField),
        reinterpret_cast<FieldGetMethodSig >(&SwitchMaterialBase::getMFMaterials));

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_GET_COMPAT
    typedef const SFUInt32 *(SwitchMaterialBase::*GetSFChoiceF)(void) const;

    GetSFChoiceF GetSFChoice = &SwitchMaterialBase::getSFChoice;
#endif

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "choice",
        "The material to actually use for drawing.\n",
        ChoiceFieldId, ChoiceFieldMask,
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&SwitchMaterialBase::editSFChoice),
#ifdef OSG_1_GET_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetSFChoice));
#else
        reinterpret_cast<FieldGetMethodSig >(&SwitchMaterialBase::getSFChoice));
#endif

    oType.addInitialDesc(pDesc);
}


SwitchMaterialBase::TypeObject SwitchMaterialBase::_type(
    SwitchMaterialBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &SwitchMaterialBase::createEmpty,
    SwitchMaterial::initMethod,
    (InitalInsertDescFunc) &SwitchMaterialBase::classDescInserter,
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"SwitchMaterial\"\n"
    "\tparent=\"Material\"\n"
    "\tlibrary=\"System\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    "\tdecoratable=\"false\"\n"
    "\tuseLocalIncludes=\"false\"\n"
    ">\n"
    "Material that allows selection of one of the materials in the _mfMaterials\n"
    "field based on the value of the _sfChoice field.\n"
    "\t<Field\n"
    "\t\tname=\"materials\"\n"
    "\t\ttype=\"MaterialPtr\"\n"
    "\t\tcardinality=\"multi\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\tMaterials to choose from.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"choice\"\n"
    "\t\ttype=\"UInt32\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\tThe material to actually use for drawing.\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    "Material that allows selection of one of the materials in the _mfMaterials\n"
    "field based on the value of the _sfChoice field.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &SwitchMaterialBase::getType(void)
{
    return _type;
}

const FieldContainerType &SwitchMaterialBase::getType(void) const
{
    return _type;
}

UInt32 SwitchMaterialBase::getContainerSize(void) const
{
    return sizeof(SwitchMaterial);
}

/*------------------------- decorator get ------------------------------*/


//! Get the SwitchMaterial::_mfMaterials field.
const MFMaterialPtr *SwitchMaterialBase::getMFMaterials(void) const
{
    return &_mfMaterials;
}

SFUInt32 *SwitchMaterialBase::editSFChoice(void)
{
    editSField(ChoiceFieldMask);

    return &_sfChoice;
}

const SFUInt32 *SwitchMaterialBase::getSFChoice(void) const
{
    return &_sfChoice;
}

#ifdef OSG_1_GET_COMPAT
SFUInt32            *SwitchMaterialBase::getSFChoice         (void)
{
    return this->editSFChoice         ();
}
#endif


void SwitchMaterialBase::pushToField(      FieldContainerPtrConstArg pNewElement,
                                    const UInt32                    uiFieldId  )
{
    Inherited::pushToField(pNewElement, uiFieldId);

    if(uiFieldId == MaterialsFieldId)
    {
        static_cast<SwitchMaterial *>(this)->pushToMaterials(
            dynamic_cast<MaterialPtr>(pNewElement));
    }
}

void SwitchMaterialBase::insertIntoMField(const UInt32                    uiIndex,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId  )
{
    Inherited::insertIntoMField(uiIndex, pNewElement, uiFieldId);

    if(uiFieldId == MaterialsFieldId)
    {
        static_cast<SwitchMaterial *>(this)->insertIntoMaterials(
            uiIndex,
            dynamic_cast<MaterialPtr>(pNewElement));
    }
}

void SwitchMaterialBase::replaceInMField (const UInt32                    uiIndex,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId)
{
    Inherited::replaceInMField(uiIndex, pNewElement, uiFieldId);

    if(uiFieldId == MaterialsFieldId)
    {
        static_cast<SwitchMaterial *>(this)->replaceInMaterials(
            uiIndex,
            dynamic_cast<MaterialPtr>(pNewElement));
    }
}

void SwitchMaterialBase::replaceInMField (      FieldContainerPtrConstArg pOldElement,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId  )
{
    Inherited::replaceInMField(pOldElement, pNewElement, uiFieldId);

    if(uiFieldId == MaterialsFieldId)
    {
        static_cast<SwitchMaterial *>(this)->replaceInMaterials(
            dynamic_cast<MaterialPtr>(pOldElement),
            dynamic_cast<MaterialPtr>(pNewElement));
    }
}

void SwitchMaterialBase::removeFromMField(const UInt32 uiIndex,
                                         const UInt32 uiFieldId)
{
    Inherited::removeFromMField(uiIndex, uiFieldId);

    if(uiFieldId == MaterialsFieldId)
    {
        static_cast<SwitchMaterial *>(this)->removeFromMaterials(
            uiIndex);
    }
}

void SwitchMaterialBase::removeFromMField(      FieldContainerPtrConstArg pElement,
                                         const UInt32                    uiFieldId)
{
    Inherited::removeFromMField(pElement, uiFieldId);

    if(uiFieldId == MaterialsFieldId)
    {
        static_cast<SwitchMaterial *>(this)->removeFromMaterials(
            dynamic_cast<MaterialPtr>(pElement));
    }
}

void SwitchMaterialBase::clearField(const UInt32 uiFieldId)
{
    Inherited::clearField(uiFieldId);

    if(uiFieldId == MaterialsFieldId)
    {
        static_cast<SwitchMaterial *>(this)->clearMaterials();
    }
}

void SwitchMaterialBase::pushToMaterials(MaterialPtrConstArg value)
{
    if(value == NullFC)
        return;

    editMField(MaterialsFieldMask, _mfMaterials);

    addRef(value);

    _mfMaterials.push_back(value);
}

void SwitchMaterialBase::assignMaterials(const MFMaterialPtr     &value)
{
    MFMaterialPtr    ::const_iterator elemIt  =
        value.begin();
    MFMaterialPtr    ::const_iterator elemEnd =
        value.end  ();

    static_cast<SwitchMaterial *>(this)->clearMaterials();

    while(elemIt != elemEnd)
    {
        this->pushToMaterials(*elemIt);

        ++elemIt;
    }
}

void SwitchMaterialBase::insertIntoMaterials(UInt32                uiIndex,
                                                   MaterialPtrConstArg value   )
{
    if(value == NullFC)
        return;

    editMField(MaterialsFieldMask, _mfMaterials);

    MFMaterialPtr::iterator fieldIt = _mfMaterials.begin();

    addRef(value);

    fieldIt += uiIndex;

    _mfMaterials.insert(fieldIt, value);
}

void SwitchMaterialBase::replaceInMaterials(UInt32                uiIndex,
                                                       MaterialPtrConstArg value   )
{
    if(value == NullFC)
        return;

    if(uiIndex >= _mfMaterials.size())
        return;

    editMField(MaterialsFieldMask, _mfMaterials);

    addRef(value);

    subRef(_mfMaterials[uiIndex]);

    _mfMaterials[uiIndex] = value;
}

void SwitchMaterialBase::replaceInMaterials(MaterialPtrConstArg pOldElem,
                                                        MaterialPtrConstArg pNewElem)
{
    if(pNewElem == NullFC)
        return;

    Int32  elemIdx = _mfMaterials.findIndex(pOldElem);

    if(elemIdx != -1)
    {
        editMField(MaterialsFieldMask, _mfMaterials);

        MFMaterialPtr::iterator fieldIt = _mfMaterials.begin();

        fieldIt += elemIdx;

        addRef(pNewElem);
        subRef(pOldElem);

        (*fieldIt) = pNewElem;
    }
}

void SwitchMaterialBase::removeFromMaterials(UInt32 uiIndex)
{
    if(uiIndex < _mfMaterials.size())
    {
        editMField(MaterialsFieldMask, _mfMaterials);

        MFMaterialPtr::iterator fieldIt = _mfMaterials.begin();

        fieldIt += uiIndex;

        subRef(*fieldIt);

        _mfMaterials.erase(fieldIt);
    }
}

void SwitchMaterialBase::removeFromMaterials(MaterialPtrConstArg value)
{
    Int32 iElemIdx = _mfMaterials.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(MaterialsFieldMask, _mfMaterials);

        MFMaterialPtr::iterator fieldIt = _mfMaterials.begin();

        fieldIt += iElemIdx;

        subRef(*fieldIt);

        _mfMaterials.erase(fieldIt);
    }
}
void SwitchMaterialBase::clearMaterials(void)
{
    editMField(MaterialsFieldMask, _mfMaterials);

    MFMaterialPtr::iterator       fieldIt  = _mfMaterials.begin();
    MFMaterialPtr::const_iterator fieldEnd = _mfMaterials.end  ();

    while(fieldIt != fieldEnd)
    {
        subRef(*fieldIt);

        ++fieldIt;
    }

    _mfMaterials.clear();
}



/*------------------------------ access -----------------------------------*/

UInt32 SwitchMaterialBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (MaterialsFieldMask & whichField))
    {
        returnValue += _mfMaterials.getBinSize();
    }
    if(FieldBits::NoField != (ChoiceFieldMask & whichField))
    {
        returnValue += _sfChoice.getBinSize();
    }

    return returnValue;
}

void SwitchMaterialBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (MaterialsFieldMask & whichField))
    {
        _mfMaterials.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ChoiceFieldMask & whichField))
    {
        _sfChoice.copyToBin(pMem);
    }
}

void SwitchMaterialBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (MaterialsFieldMask & whichField))
    {
        _mfMaterials.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ChoiceFieldMask & whichField))
    {
        _sfChoice.copyFromBin(pMem);
    }
}

//! create a new instance of the class
SwitchMaterialPtr SwitchMaterialBase::create(void)
{
    SwitchMaterialPtr fc;

    if(getClassType().getPrototype() != NullFC)
    {
        fc = dynamic_cast<SwitchMaterial::ObjPtr>(
            getClassType().getPrototype()-> shallowCopy());
    }

    return fc;
}

//! create an empty new instance of the class, do not copy the prototype
SwitchMaterialPtr SwitchMaterialBase::createEmpty(void)
{
    SwitchMaterialPtr returnValue;

    newPtr<SwitchMaterial>(returnValue);

    return returnValue;
}

FieldContainerPtr SwitchMaterialBase::shallowCopy(void) const
{
    SwitchMaterialPtr returnValue;

    newPtr(returnValue, dynamic_cast<const SwitchMaterial *>(this));

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

SwitchMaterialBase::SwitchMaterialBase(void) :
    Inherited(),
    _mfMaterials              (),
    _sfChoice                 ()
{
}

SwitchMaterialBase::SwitchMaterialBase(const SwitchMaterialBase &source) :
    Inherited(source),
    _mfMaterials              (),
    _sfChoice                 (source._sfChoice                 )
{
}


/*-------------------------- destructors ----------------------------------*/

SwitchMaterialBase::~SwitchMaterialBase(void)
{
}

void SwitchMaterialBase::onCreate(const SwitchMaterial *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {

        MFMaterialPtr::const_iterator MaterialsIt  =
            source->_mfMaterials.begin();
        MFMaterialPtr::const_iterator MaterialsEnd =
            source->_mfMaterials.end  ();

        while(MaterialsIt != MaterialsEnd)
        {
            this->pushToMaterials(*MaterialsIt);

            ++MaterialsIt;
        }
    }
}

#ifdef OSG_MT_CPTR_ASPECT
void SwitchMaterialBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<SwitchMaterialBase *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr SwitchMaterialBase::createAspectCopy(void) const
{
    SwitchMaterialPtr returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const SwitchMaterial *>(this));

    return returnValue;
}
#endif

void SwitchMaterialBase::resolveLinks(void)
{
    Inherited::resolveLinks();


    static_cast<SwitchMaterial *>(this)->clearMaterials();
}


OSG_END_NAMESPACE

#include "OSGSFieldAdaptor.ins"
#include "OSGMFieldAdaptor.ins"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<SwitchMaterialPtr>::_type("SwitchMaterialPtr", "MaterialPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(SwitchMaterialPtr)

OSG_FIELD_DLLEXPORT_DEF2(SFieldAdaptor, SwitchMaterialPtr, SFFieldContainerPtr);
OSG_FIELD_DLLEXPORT_DEF2(MFieldAdaptor, SwitchMaterialPtr, MFFieldContainerPtr);

OSG_END_NAMESPACE
