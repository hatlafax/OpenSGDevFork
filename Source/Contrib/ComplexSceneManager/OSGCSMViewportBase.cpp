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
 **     class CSMViewport!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>



#include <OSGNode.h> // Root Class
#include <OSGCamera.h> // Camera Class
#include <OSGBackground.h> // Background Class
#include <OSGForeground.h> // Foregrounds Class

#include "OSGCSMViewportBase.h"
#include "OSGCSMViewport.h"

#include "boost/bind.hpp"

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CSMViewport
    
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var Node *          CSMViewportBase::_sfRoot
    
*/

/*! \var Camera *        CSMViewportBase::_sfCamera
    
*/

/*! \var Background *    CSMViewportBase::_sfBackground
    
*/

/*! \var Foreground *    CSMViewportBase::_mfForegrounds
    
*/

/*! \var Vec2f           CSMViewportBase::_sfLeftBottom
    
*/

/*! \var Vec2f           CSMViewportBase::_sfRightTop
    
*/


void CSMViewportBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecNodePtr::Description(
        SFUnrecNodePtr::getClassType(),
        "root",
        "",
        RootFieldId, RootFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMViewport::editHandleRoot),
        static_cast<FieldGetMethodSig >(&CSMViewport::getHandleRoot));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecCameraPtr::Description(
        SFUnrecCameraPtr::getClassType(),
        "camera",
        "",
        CameraFieldId, CameraFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMViewport::editHandleCamera),
        static_cast<FieldGetMethodSig >(&CSMViewport::getHandleCamera));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecBackgroundPtr::Description(
        SFUnrecBackgroundPtr::getClassType(),
        "background",
        "",
        BackgroundFieldId, BackgroundFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMViewport::editHandleBackground),
        static_cast<FieldGetMethodSig >(&CSMViewport::getHandleBackground));

    oType.addInitialDesc(pDesc);

    pDesc = new MFUnrecForegroundPtr::Description(
        MFUnrecForegroundPtr::getClassType(),
        "foregrounds",
        "",
        ForegroundsFieldId, ForegroundsFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMViewport::editHandleForegrounds),
        static_cast<FieldGetMethodSig >(&CSMViewport::getHandleForegrounds));

    oType.addInitialDesc(pDesc);

    pDesc = new SFVec2f::Description(
        SFVec2f::getClassType(),
        "leftBottom",
        "",
        LeftBottomFieldId, LeftBottomFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMViewport::editHandleLeftBottom),
        static_cast<FieldGetMethodSig >(&CSMViewport::getHandleLeftBottom));

    oType.addInitialDesc(pDesc);

    pDesc = new SFVec2f::Description(
        SFVec2f::getClassType(),
        "rightTop",
        "",
        RightTopFieldId, RightTopFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMViewport::editHandleRightTop),
        static_cast<FieldGetMethodSig >(&CSMViewport::getHandleRightTop));

    oType.addInitialDesc(pDesc);
}


CSMViewportBase::TypeObject CSMViewportBase::_type(
    CSMViewportBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&CSMViewportBase::createEmptyLocal),
    CSMViewport::initMethod,
    CSMViewport::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&CSMViewportBase::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"CSMViewport\"\n"
    "    parent=\"FieldContainer\"\n"
    "    library=\"ContribCSM\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"true\"\n"
    ">\n"
    "\t<Field\n"
    "\t\tname=\"root\"\n"
    "\t\ttype=\"Node\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "        defaultValue=\"NULL\"\n"
    "\t\taccess=\"public\"\n"
    "        category=\"pointer\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"camera\"\n"
    "\t\ttype=\"Camera\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "        defaultValue=\"NULL\"\n"
    "\t\taccess=\"public\"\n"
    "        category=\"pointer\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"background\"\n"
    "\t\ttype=\"Background\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "        category=\"pointer\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"foregrounds\"\n"
    "\t\ttype=\"Foreground\"\n"
    "\t\tcardinality=\"multi\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "        category=\"pointer\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"leftBottom\"\n"
    "\t\ttype=\"Vec2f\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"0.f, 0.f\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"rightTop\"\n"
    "\t\ttype=\"Vec2f\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"1.f, 1.f\"\n"
    "\t>\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &CSMViewportBase::getType(void)
{
    return _type;
}

const FieldContainerType &CSMViewportBase::getType(void) const
{
    return _type;
}

UInt32 CSMViewportBase::getContainerSize(void) const
{
    return sizeof(CSMViewport);
}

/*------------------------- decorator get ------------------------------*/


//! Get the CSMViewport::_sfRoot field.
const SFUnrecNodePtr *CSMViewportBase::getSFRoot(void) const
{
    return &_sfRoot;
}

SFUnrecNodePtr      *CSMViewportBase::editSFRoot           (void)
{
    editSField(RootFieldMask);

    return &_sfRoot;
}

//! Get the CSMViewport::_sfCamera field.
const SFUnrecCameraPtr *CSMViewportBase::getSFCamera(void) const
{
    return &_sfCamera;
}

SFUnrecCameraPtr    *CSMViewportBase::editSFCamera         (void)
{
    editSField(CameraFieldMask);

    return &_sfCamera;
}

//! Get the CSMViewport::_sfBackground field.
const SFUnrecBackgroundPtr *CSMViewportBase::getSFBackground(void) const
{
    return &_sfBackground;
}

SFUnrecBackgroundPtr *CSMViewportBase::editSFBackground     (void)
{
    editSField(BackgroundFieldMask);

    return &_sfBackground;
}

//! Get the CSMViewport::_mfForegrounds field.
const MFUnrecForegroundPtr *CSMViewportBase::getMFForegrounds(void) const
{
    return &_mfForegrounds;
}

MFUnrecForegroundPtr *CSMViewportBase::editMFForegrounds    (void)
{
    editMField(ForegroundsFieldMask, _mfForegrounds);

    return &_mfForegrounds;
}

SFVec2f *CSMViewportBase::editSFLeftBottom(void)
{
    editSField(LeftBottomFieldMask);

    return &_sfLeftBottom;
}

const SFVec2f *CSMViewportBase::getSFLeftBottom(void) const
{
    return &_sfLeftBottom;
}


SFVec2f *CSMViewportBase::editSFRightTop(void)
{
    editSField(RightTopFieldMask);

    return &_sfRightTop;
}

const SFVec2f *CSMViewportBase::getSFRightTop(void) const
{
    return &_sfRightTop;
}




void CSMViewportBase::pushToForegrounds(Foreground * const value)
{
    editMField(ForegroundsFieldMask, _mfForegrounds);

    _mfForegrounds.push_back(value);
}

void CSMViewportBase::assignForegrounds(const MFUnrecForegroundPtr &value)
{
    MFUnrecForegroundPtr::const_iterator elemIt  =
        value.begin();
    MFUnrecForegroundPtr::const_iterator elemEnd =
        value.end  ();

    static_cast<CSMViewport *>(this)->clearForegrounds();

    while(elemIt != elemEnd)
    {
        this->pushToForegrounds(*elemIt);

        ++elemIt;
    }
}

void CSMViewportBase::removeFromForegrounds(UInt32 uiIndex)
{
    if(uiIndex < _mfForegrounds.size())
    {
        editMField(ForegroundsFieldMask, _mfForegrounds);

        _mfForegrounds.erase(uiIndex);
    }
}

void CSMViewportBase::removeObjFromForegrounds(Foreground * const value)
{
    Int32 iElemIdx = _mfForegrounds.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(ForegroundsFieldMask, _mfForegrounds);

        _mfForegrounds.erase(iElemIdx);
    }
}
void CSMViewportBase::clearForegrounds(void)
{
    editMField(ForegroundsFieldMask, _mfForegrounds);


    _mfForegrounds.clear();
}



/*------------------------------ access -----------------------------------*/

UInt32 CSMViewportBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (RootFieldMask & whichField))
    {
        returnValue += _sfRoot.getBinSize();
    }
    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        returnValue += _sfCamera.getBinSize();
    }
    if(FieldBits::NoField != (BackgroundFieldMask & whichField))
    {
        returnValue += _sfBackground.getBinSize();
    }
    if(FieldBits::NoField != (ForegroundsFieldMask & whichField))
    {
        returnValue += _mfForegrounds.getBinSize();
    }
    if(FieldBits::NoField != (LeftBottomFieldMask & whichField))
    {
        returnValue += _sfLeftBottom.getBinSize();
    }
    if(FieldBits::NoField != (RightTopFieldMask & whichField))
    {
        returnValue += _sfRightTop.getBinSize();
    }

    return returnValue;
}

void CSMViewportBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (RootFieldMask & whichField))
    {
        _sfRoot.copyToBin(pMem);
    }
    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        _sfCamera.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BackgroundFieldMask & whichField))
    {
        _sfBackground.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ForegroundsFieldMask & whichField))
    {
        _mfForegrounds.copyToBin(pMem);
    }
    if(FieldBits::NoField != (LeftBottomFieldMask & whichField))
    {
        _sfLeftBottom.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RightTopFieldMask & whichField))
    {
        _sfRightTop.copyToBin(pMem);
    }
}

void CSMViewportBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (RootFieldMask & whichField))
    {
        _sfRoot.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        _sfCamera.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BackgroundFieldMask & whichField))
    {
        _sfBackground.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ForegroundsFieldMask & whichField))
    {
        _mfForegrounds.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (LeftBottomFieldMask & whichField))
    {
        _sfLeftBottom.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RightTopFieldMask & whichField))
    {
        _sfRightTop.copyFromBin(pMem);
    }
}

//! create a new instance of the class
CSMViewportTransitPtr CSMViewportBase::createLocal(BitVector bFlags)
{
    CSMViewportTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<CSMViewport>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
CSMViewportTransitPtr CSMViewportBase::createDependent(BitVector bFlags)
{
    CSMViewportTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<CSMViewport>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
CSMViewportTransitPtr CSMViewportBase::create(void)
{
    return createLocal();
}

CSMViewport *CSMViewportBase::createEmptyLocal(BitVector bFlags)
{
    CSMViewport *returnValue;

    newPtr<CSMViewport>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
CSMViewport *CSMViewportBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr CSMViewportBase::shallowCopyLocal(
    BitVector bFlags) const
{
    CSMViewport *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CSMViewport *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr CSMViewportBase::shallowCopyDependent(
    BitVector bFlags) const
{
    CSMViewport *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CSMViewport *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr CSMViewportBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

CSMViewportBase::CSMViewportBase(void) :
    Inherited(),
    _sfRoot                   (NULL),
    _sfCamera                 (NULL),
    _sfBackground             (NULL),
    _mfForegrounds            (),
    _sfLeftBottom             (Vec2f(0.f, 0.f)),
    _sfRightTop               (Vec2f(1.f, 1.f))
{
}

CSMViewportBase::CSMViewportBase(const CSMViewportBase &source) :
    Inherited(source),
    _sfRoot                   (NULL),
    _sfCamera                 (NULL),
    _sfBackground             (NULL),
    _mfForegrounds            (),
    _sfLeftBottom             (source._sfLeftBottom             ),
    _sfRightTop               (source._sfRightTop               )
{
}


/*-------------------------- destructors ----------------------------------*/

CSMViewportBase::~CSMViewportBase(void)
{
}

void CSMViewportBase::onCreate(const CSMViewport *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        CSMViewport *pThis = static_cast<CSMViewport *>(this);

        pThis->setRoot(source->getRoot());

        pThis->setCamera(source->getCamera());

        pThis->setBackground(source->getBackground());

        MFUnrecForegroundPtr::const_iterator ForegroundsIt  =
            source->_mfForegrounds.begin();
        MFUnrecForegroundPtr::const_iterator ForegroundsEnd =
            source->_mfForegrounds.end  ();

        while(ForegroundsIt != ForegroundsEnd)
        {
            pThis->pushToForegrounds(*ForegroundsIt);

            ++ForegroundsIt;
        }
    }
}

GetFieldHandlePtr CSMViewportBase::getHandleRoot            (void) const
{
    SFUnrecNodePtr::GetHandlePtr returnValue(
        new  SFUnrecNodePtr::GetHandle(
             &_sfRoot,
             this->getType().getFieldDesc(RootFieldId)));

    return returnValue;
}

EditFieldHandlePtr CSMViewportBase::editHandleRoot           (void)
{
    SFUnrecNodePtr::EditHandlePtr returnValue(
        new  SFUnrecNodePtr::EditHandle(
             &_sfRoot,
             this->getType().getFieldDesc(RootFieldId)));

    returnValue->setSetMethod(
        boost::bind(&CSMViewport::setRoot,
                    static_cast<CSMViewport *>(this), _1));

    editSField(RootFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMViewportBase::getHandleCamera          (void) const
{
    SFUnrecCameraPtr::GetHandlePtr returnValue(
        new  SFUnrecCameraPtr::GetHandle(
             &_sfCamera,
             this->getType().getFieldDesc(CameraFieldId)));

    return returnValue;
}

EditFieldHandlePtr CSMViewportBase::editHandleCamera         (void)
{
    SFUnrecCameraPtr::EditHandlePtr returnValue(
        new  SFUnrecCameraPtr::EditHandle(
             &_sfCamera,
             this->getType().getFieldDesc(CameraFieldId)));

    returnValue->setSetMethod(
        boost::bind(&CSMViewport::setCamera,
                    static_cast<CSMViewport *>(this), _1));

    editSField(CameraFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMViewportBase::getHandleBackground      (void) const
{
    SFUnrecBackgroundPtr::GetHandlePtr returnValue(
        new  SFUnrecBackgroundPtr::GetHandle(
             &_sfBackground,
             this->getType().getFieldDesc(BackgroundFieldId)));

    return returnValue;
}

EditFieldHandlePtr CSMViewportBase::editHandleBackground     (void)
{
    SFUnrecBackgroundPtr::EditHandlePtr returnValue(
        new  SFUnrecBackgroundPtr::EditHandle(
             &_sfBackground,
             this->getType().getFieldDesc(BackgroundFieldId)));

    returnValue->setSetMethod(
        boost::bind(&CSMViewport::setBackground,
                    static_cast<CSMViewport *>(this), _1));

    editSField(BackgroundFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMViewportBase::getHandleForegrounds     (void) const
{
    MFUnrecForegroundPtr::GetHandlePtr returnValue(
        new  MFUnrecForegroundPtr::GetHandle(
             &_mfForegrounds,
             this->getType().getFieldDesc(ForegroundsFieldId)));

    return returnValue;
}

EditFieldHandlePtr CSMViewportBase::editHandleForegrounds    (void)
{
    MFUnrecForegroundPtr::EditHandlePtr returnValue(
        new  MFUnrecForegroundPtr::EditHandle(
             &_mfForegrounds,
             this->getType().getFieldDesc(ForegroundsFieldId)));

    returnValue->setAddMethod(
        boost::bind(&CSMViewport::pushToForegrounds,
                    static_cast<CSMViewport *>(this), _1));
    returnValue->setRemoveMethod(
        boost::bind(&CSMViewport::removeFromForegrounds,
                    static_cast<CSMViewport *>(this), _1));
    returnValue->setRemoveObjMethod(
        boost::bind(&CSMViewport::removeObjFromForegrounds,
                    static_cast<CSMViewport *>(this), _1));
    returnValue->setClearMethod(
        boost::bind(&CSMViewport::clearForegrounds,
                    static_cast<CSMViewport *>(this)));

    editMField(ForegroundsFieldMask, _mfForegrounds);

    return returnValue;
}

GetFieldHandlePtr CSMViewportBase::getHandleLeftBottom      (void) const
{
    SFVec2f::GetHandlePtr returnValue(
        new  SFVec2f::GetHandle(
             &_sfLeftBottom,
             this->getType().getFieldDesc(LeftBottomFieldId)));

    return returnValue;
}

EditFieldHandlePtr CSMViewportBase::editHandleLeftBottom     (void)
{
    SFVec2f::EditHandlePtr returnValue(
        new  SFVec2f::EditHandle(
             &_sfLeftBottom,
             this->getType().getFieldDesc(LeftBottomFieldId)));


    editSField(LeftBottomFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMViewportBase::getHandleRightTop        (void) const
{
    SFVec2f::GetHandlePtr returnValue(
        new  SFVec2f::GetHandle(
             &_sfRightTop,
             this->getType().getFieldDesc(RightTopFieldId)));

    return returnValue;
}

EditFieldHandlePtr CSMViewportBase::editHandleRightTop       (void)
{
    SFVec2f::EditHandlePtr returnValue(
        new  SFVec2f::EditHandle(
             &_sfRightTop,
             this->getType().getFieldDesc(RightTopFieldId)));


    editSField(RightTopFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void CSMViewportBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    CSMViewport *pThis = static_cast<CSMViewport *>(this);

    pThis->execSync(static_cast<CSMViewport *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *CSMViewportBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    CSMViewport *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const CSMViewport *>(pRefAspect),
                  dynamic_cast<const CSMViewport *>(this));

    return returnValue;
}
#endif

void CSMViewportBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<CSMViewport *>(this)->setRoot(NULL);

    static_cast<CSMViewport *>(this)->setCamera(NULL);

    static_cast<CSMViewport *>(this)->setBackground(NULL);

    static_cast<CSMViewport *>(this)->clearForegrounds();


}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<CSMViewport *>::_type("CSMViewportPtr", "FieldContainerPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(CSMViewport *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           CSMViewport *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           CSMViewport *,
                           0);

OSG_END_NAMESPACE
