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
 **     class CSMSortFirstWinOptions!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"




#include "OSGCSMSortFirstWinOptionsBase.h"
#include "OSGCSMSortFirstWinOptions.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CSMSortFirstWinOptions
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var std::string     CSMSortFirstWinOptionsBase::_sfCompression
    
*/

/*! \var UInt32          CSMSortFirstWinOptionsBase::_sfSubtileSize
    
*/

/*! \var bool            CSMSortFirstWinOptionsBase::_sfCompose
    
*/

/*! \var bool            CSMSortFirstWinOptionsBase::_sfUseFaceDistribution
    Enabe, disable analysation of face distribution
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<CSMSortFirstWinOptions *, nsOSG>::_type("CSMSortFirstWinOptionsPtr", "CSMClusterWinOptionsPtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(CSMSortFirstWinOptions *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void CSMSortFirstWinOptionsBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFString::Description(
        SFString::getClassType(),
        "compression",
        "",
        CompressionFieldId, CompressionFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMSortFirstWinOptions::editHandleCompression),
        static_cast<FieldGetMethodSig >(&CSMSortFirstWinOptions::getHandleCompression));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "subtileSize",
        "",
        SubtileSizeFieldId, SubtileSizeFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMSortFirstWinOptions::editHandleSubtileSize),
        static_cast<FieldGetMethodSig >(&CSMSortFirstWinOptions::getHandleSubtileSize));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "compose",
        "",
        ComposeFieldId, ComposeFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMSortFirstWinOptions::editHandleCompose),
        static_cast<FieldGetMethodSig >(&CSMSortFirstWinOptions::getHandleCompose));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "useFaceDistribution",
        "Enabe, disable analysation of face distribution\n",
        UseFaceDistributionFieldId, UseFaceDistributionFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMSortFirstWinOptions::editHandleUseFaceDistribution),
        static_cast<FieldGetMethodSig >(&CSMSortFirstWinOptions::getHandleUseFaceDistribution));

    oType.addInitialDesc(pDesc);
}


CSMSortFirstWinOptionsBase::TypeObject CSMSortFirstWinOptionsBase::_type(
    CSMSortFirstWinOptionsBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&CSMSortFirstWinOptionsBase::createEmptyLocal),
    CSMSortFirstWinOptions::initMethod,
    CSMSortFirstWinOptions::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&CSMSortFirstWinOptions::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"CSMSortFirstWinOptions\"\n"
    "    parent=\"CSMClusterWinOptions\"\n"
    "    library=\"ContribCSM\"\n"
    "    pointerfieldtypes=\"none\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"true\"\n"
    "    parentFields=\"none\"\n"
    ">\n"
    "\t<Field\n"
    "\t\tname=\"compression\"\n"
    "\t\ttype=\"std::string\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"subtileSize\"\n"
    "\t\ttype=\"UInt32\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"32\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"compose\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"true\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"useFaceDistribution\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"false\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\tEnabe, disable analysation of face distribution\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &CSMSortFirstWinOptionsBase::getType(void)
{
    return _type;
}

const FieldContainerType &CSMSortFirstWinOptionsBase::getType(void) const
{
    return _type;
}

UInt32 CSMSortFirstWinOptionsBase::getContainerSize(void) const
{
    return sizeof(CSMSortFirstWinOptions);
}

/*------------------------- decorator get ------------------------------*/


SFString *CSMSortFirstWinOptionsBase::editSFCompression(void)
{
    editSField(CompressionFieldMask);

    return &_sfCompression;
}

const SFString *CSMSortFirstWinOptionsBase::getSFCompression(void) const
{
    return &_sfCompression;
}


SFUInt32 *CSMSortFirstWinOptionsBase::editSFSubtileSize(void)
{
    editSField(SubtileSizeFieldMask);

    return &_sfSubtileSize;
}

const SFUInt32 *CSMSortFirstWinOptionsBase::getSFSubtileSize(void) const
{
    return &_sfSubtileSize;
}


SFBool *CSMSortFirstWinOptionsBase::editSFCompose(void)
{
    editSField(ComposeFieldMask);

    return &_sfCompose;
}

const SFBool *CSMSortFirstWinOptionsBase::getSFCompose(void) const
{
    return &_sfCompose;
}


SFBool *CSMSortFirstWinOptionsBase::editSFUseFaceDistribution(void)
{
    editSField(UseFaceDistributionFieldMask);

    return &_sfUseFaceDistribution;
}

const SFBool *CSMSortFirstWinOptionsBase::getSFUseFaceDistribution(void) const
{
    return &_sfUseFaceDistribution;
}






/*------------------------------ access -----------------------------------*/

UInt32 CSMSortFirstWinOptionsBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (CompressionFieldMask & whichField))
    {
        returnValue += _sfCompression.getBinSize();
    }
    if(FieldBits::NoField != (SubtileSizeFieldMask & whichField))
    {
        returnValue += _sfSubtileSize.getBinSize();
    }
    if(FieldBits::NoField != (ComposeFieldMask & whichField))
    {
        returnValue += _sfCompose.getBinSize();
    }
    if(FieldBits::NoField != (UseFaceDistributionFieldMask & whichField))
    {
        returnValue += _sfUseFaceDistribution.getBinSize();
    }

    return returnValue;
}

void CSMSortFirstWinOptionsBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (CompressionFieldMask & whichField))
    {
        _sfCompression.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SubtileSizeFieldMask & whichField))
    {
        _sfSubtileSize.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ComposeFieldMask & whichField))
    {
        _sfCompose.copyToBin(pMem);
    }
    if(FieldBits::NoField != (UseFaceDistributionFieldMask & whichField))
    {
        _sfUseFaceDistribution.copyToBin(pMem);
    }
}

void CSMSortFirstWinOptionsBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (CompressionFieldMask & whichField))
    {
        editSField(CompressionFieldMask);
        _sfCompression.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SubtileSizeFieldMask & whichField))
    {
        editSField(SubtileSizeFieldMask);
        _sfSubtileSize.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ComposeFieldMask & whichField))
    {
        editSField(ComposeFieldMask);
        _sfCompose.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (UseFaceDistributionFieldMask & whichField))
    {
        editSField(UseFaceDistributionFieldMask);
        _sfUseFaceDistribution.copyFromBin(pMem);
    }
}

//! create a new instance of the class
CSMSortFirstWinOptionsTransitPtr CSMSortFirstWinOptionsBase::createLocal(BitVector bFlags)
{
    CSMSortFirstWinOptionsTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<CSMSortFirstWinOptions>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
CSMSortFirstWinOptionsTransitPtr CSMSortFirstWinOptionsBase::createDependent(BitVector bFlags)
{
    CSMSortFirstWinOptionsTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<CSMSortFirstWinOptions>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
CSMSortFirstWinOptionsTransitPtr CSMSortFirstWinOptionsBase::create(void)
{
    return createLocal();
}

CSMSortFirstWinOptions *CSMSortFirstWinOptionsBase::createEmptyLocal(BitVector bFlags)
{
    CSMSortFirstWinOptions *returnValue;

    newPtr<CSMSortFirstWinOptions>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
CSMSortFirstWinOptions *CSMSortFirstWinOptionsBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr CSMSortFirstWinOptionsBase::shallowCopyLocal(
    BitVector bFlags) const
{
    CSMSortFirstWinOptions *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CSMSortFirstWinOptions *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr CSMSortFirstWinOptionsBase::shallowCopyDependent(
    BitVector bFlags) const
{
    CSMSortFirstWinOptions *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CSMSortFirstWinOptions *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr CSMSortFirstWinOptionsBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

CSMSortFirstWinOptionsBase::CSMSortFirstWinOptionsBase(void) :
    Inherited(),
    _sfCompression            (),
    _sfSubtileSize            (UInt32(32)),
    _sfCompose                (bool(true)),
    _sfUseFaceDistribution    (bool(false))
{
}

CSMSortFirstWinOptionsBase::CSMSortFirstWinOptionsBase(const CSMSortFirstWinOptionsBase &source) :
    Inherited(source),
    _sfCompression            (source._sfCompression            ),
    _sfSubtileSize            (source._sfSubtileSize            ),
    _sfCompose                (source._sfCompose                ),
    _sfUseFaceDistribution    (source._sfUseFaceDistribution    )
{
}


/*-------------------------- destructors ----------------------------------*/

CSMSortFirstWinOptionsBase::~CSMSortFirstWinOptionsBase(void)
{
}


GetFieldHandlePtr CSMSortFirstWinOptionsBase::getHandleCompression     (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfCompression,
             this->getType().getFieldDesc(CompressionFieldId),
             const_cast<CSMSortFirstWinOptionsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMSortFirstWinOptionsBase::editHandleCompression    (void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfCompression,
             this->getType().getFieldDesc(CompressionFieldId),
             this));


    editSField(CompressionFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMSortFirstWinOptionsBase::getHandleSubtileSize     (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfSubtileSize,
             this->getType().getFieldDesc(SubtileSizeFieldId),
             const_cast<CSMSortFirstWinOptionsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMSortFirstWinOptionsBase::editHandleSubtileSize    (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfSubtileSize,
             this->getType().getFieldDesc(SubtileSizeFieldId),
             this));


    editSField(SubtileSizeFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMSortFirstWinOptionsBase::getHandleCompose         (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfCompose,
             this->getType().getFieldDesc(ComposeFieldId),
             const_cast<CSMSortFirstWinOptionsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMSortFirstWinOptionsBase::editHandleCompose        (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfCompose,
             this->getType().getFieldDesc(ComposeFieldId),
             this));


    editSField(ComposeFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMSortFirstWinOptionsBase::getHandleUseFaceDistribution (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfUseFaceDistribution,
             this->getType().getFieldDesc(UseFaceDistributionFieldId),
             const_cast<CSMSortFirstWinOptionsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMSortFirstWinOptionsBase::editHandleUseFaceDistribution(void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfUseFaceDistribution,
             this->getType().getFieldDesc(UseFaceDistributionFieldId),
             this));


    editSField(UseFaceDistributionFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void CSMSortFirstWinOptionsBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    CSMSortFirstWinOptions *pThis = static_cast<CSMSortFirstWinOptions *>(this);

    pThis->execSync(static_cast<CSMSortFirstWinOptions *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *CSMSortFirstWinOptionsBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    CSMSortFirstWinOptions *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const CSMSortFirstWinOptions *>(pRefAspect),
                  dynamic_cast<const CSMSortFirstWinOptions *>(this));

    return returnValue;
}
#endif

void CSMSortFirstWinOptionsBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
