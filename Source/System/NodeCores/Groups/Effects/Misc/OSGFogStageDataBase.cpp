/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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
 **     class FogStageData!
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



#include "OSGChunkMaterial.h"           // FogMaterial Class
#include "OSGFrameBufferObject.h"       // RenderTarget Class
#include "OSGCamera.h"                  // Camera Class

#include "OSGFogStageDataBase.h"
#include "OSGFogStageData.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FogStageData
    Data used for rendering by the Fog effect stage
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var ChunkMaterial * FogStageDataBase::_sfFogMaterial
    
*/

/*! \var Int32           FogStageDataBase::_sfWidth
    
*/

/*! \var Int32           FogStageDataBase::_sfHeight
    
*/

/*! \var FrameBufferObject * FogStageDataBase::_sfRenderTarget
    
*/

/*! \var Camera *        FogStageDataBase::_sfCamera
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<FogStageData *, nsOSG>::_type(
    "FogStageDataPtr", 
    "StageDataPtr", 
    FogStageData::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(FogStageData *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void FogStageDataBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecChunkMaterialPtr::Description(
        SFUnrecChunkMaterialPtr::getClassType(),
        "FogMaterial",
        "",
        FogMaterialFieldId, FogMaterialFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&FogStageData::editHandleFogMaterial),
        static_cast<FieldGetMethodSig >(&FogStageData::getHandleFogMaterial));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "Width",
        "",
        WidthFieldId, WidthFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&FogStageData::editHandleWidth),
        static_cast<FieldGetMethodSig >(&FogStageData::getHandleWidth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "Height",
        "",
        HeightFieldId, HeightFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&FogStageData::editHandleHeight),
        static_cast<FieldGetMethodSig >(&FogStageData::getHandleHeight));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecFrameBufferObjectPtr::Description(
        SFUnrecFrameBufferObjectPtr::getClassType(),
        "RenderTarget",
        "",
        RenderTargetFieldId, RenderTargetFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&FogStageData::editHandleRenderTarget),
        static_cast<FieldGetMethodSig >(&FogStageData::getHandleRenderTarget));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecCameraPtr::Description(
        SFUnrecCameraPtr::getClassType(),
        "Camera",
        "",
        CameraFieldId, CameraFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&FogStageData::editHandleCamera),
        static_cast<FieldGetMethodSig >(&FogStageData::getHandleCamera));

    oType.addInitialDesc(pDesc);
}


FogStageDataBase::TypeObject FogStageDataBase::_type(
    FogStageDataBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&FogStageDataBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&FogStageData::initMethod),
    reinterpret_cast<ExitContainerF>(&FogStageData::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&FogStageData::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"FogStageData\"\n"
    "    parent=\"StageData\"\n"
    "    library=\"EffectGroups\"\n"
    "    pointerfieldtypes=\"none\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    docGroupBase=\"GrpEffectsGroupsFog\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)\"\n"
    "    >\n"
    "    Data used for rendering by the Fog effect stage\n"
    "    <Field\n"
    "        name=\"FogMaterial\"\n"
    "        type=\"ChunkMaterial\"\n"
    "        category=\"pointer\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"NULL\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"Width\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"0\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"Height\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"0\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"RenderTarget\"\n"
    "        type=\"FrameBufferObject\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"NULL\"\n"
    "        access=\"public\"\n"
    "        category=\"pointer\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"Camera\"\n"
    "        type=\"Camera\"\n"
    "        category=\"pointer\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"NULL\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "</FieldContainer>\n",
    "Data used for rendering by the Fog effect stage\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &FogStageDataBase::getType(void)
{
    return _type;
}

const FieldContainerType &FogStageDataBase::getType(void) const
{
    return _type;
}

UInt32 FogStageDataBase::getContainerSize(void) const
{
    return sizeof(FogStageData);
}

/*------------------------- decorator get ------------------------------*/


//! Get the FogStageData::_sfFogMaterial field.
const SFUnrecChunkMaterialPtr *FogStageDataBase::getSFFogMaterial(void) const
{
    return &_sfFogMaterial;
}

SFUnrecChunkMaterialPtr *FogStageDataBase::editSFFogMaterial    (void)
{
    editSField(FogMaterialFieldMask);

    return &_sfFogMaterial;
}

//! Get the value of the FogStageData::_sfFogMaterial field.
ChunkMaterial * FogStageDataBase::getFogMaterial(void) const
{
    return _sfFogMaterial.getValue();
}

//! Set the value of the FogStageData::_sfFogMaterial field.
void FogStageDataBase::setFogMaterial(ChunkMaterial * const value)
{
    editSField(FogMaterialFieldMask);

    _sfFogMaterial.setValue(value);
}


SFInt32 *FogStageDataBase::editSFWidth(void)
{
    editSField(WidthFieldMask);

    return &_sfWidth;
}

const SFInt32 *FogStageDataBase::getSFWidth(void) const
{
    return &_sfWidth;
}


SFInt32 *FogStageDataBase::editSFHeight(void)
{
    editSField(HeightFieldMask);

    return &_sfHeight;
}

const SFInt32 *FogStageDataBase::getSFHeight(void) const
{
    return &_sfHeight;
}


//! Get the FogStageData::_sfRenderTarget field.
const SFUnrecFrameBufferObjectPtr *FogStageDataBase::getSFRenderTarget(void) const
{
    return &_sfRenderTarget;
}

SFUnrecFrameBufferObjectPtr *FogStageDataBase::editSFRenderTarget   (void)
{
    editSField(RenderTargetFieldMask);

    return &_sfRenderTarget;
}

//! Get the value of the FogStageData::_sfRenderTarget field.
FrameBufferObject * FogStageDataBase::getRenderTarget(void) const
{
    return _sfRenderTarget.getValue();
}

//! Set the value of the FogStageData::_sfRenderTarget field.
void FogStageDataBase::setRenderTarget(FrameBufferObject * const value)
{
    editSField(RenderTargetFieldMask);

    _sfRenderTarget.setValue(value);
}


//! Get the FogStageData::_sfCamera field.
const SFUnrecCameraPtr *FogStageDataBase::getSFCamera(void) const
{
    return &_sfCamera;
}

SFUnrecCameraPtr    *FogStageDataBase::editSFCamera         (void)
{
    editSField(CameraFieldMask);

    return &_sfCamera;
}

//! Get the value of the FogStageData::_sfCamera field.
Camera * FogStageDataBase::getCamera(void) const
{
    return _sfCamera.getValue();
}

//! Set the value of the FogStageData::_sfCamera field.
void FogStageDataBase::setCamera(Camera * const value)
{
    editSField(CameraFieldMask);

    _sfCamera.setValue(value);
}






/*------------------------------ access -----------------------------------*/

SizeT FogStageDataBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (FogMaterialFieldMask & whichField))
    {
        returnValue += _sfFogMaterial.getBinSize();
    }
    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        returnValue += _sfWidth.getBinSize();
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        returnValue += _sfHeight.getBinSize();
    }
    if(FieldBits::NoField != (RenderTargetFieldMask & whichField))
    {
        returnValue += _sfRenderTarget.getBinSize();
    }
    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        returnValue += _sfCamera.getBinSize();
    }

    return returnValue;
}

void FogStageDataBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (FogMaterialFieldMask & whichField))
    {
        _sfFogMaterial.copyToBin(pMem);
    }
    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        _sfWidth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        _sfHeight.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RenderTargetFieldMask & whichField))
    {
        _sfRenderTarget.copyToBin(pMem);
    }
    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        _sfCamera.copyToBin(pMem);
    }
}

void FogStageDataBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (FogMaterialFieldMask & whichField))
    {
        editSField(FogMaterialFieldMask);
        _sfFogMaterial.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        editSField(WidthFieldMask);
        _sfWidth.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        editSField(HeightFieldMask);
        _sfHeight.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RenderTargetFieldMask & whichField))
    {
        editSField(RenderTargetFieldMask);
        _sfRenderTarget.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        editSField(CameraFieldMask);
        _sfCamera.copyFromBin(pMem);
    }
}

//! create a new instance of the class
FogStageDataTransitPtr FogStageDataBase::createLocal(BitVector bFlags)
{
    FogStageDataTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<FogStageData>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
FogStageDataTransitPtr FogStageDataBase::createDependent(BitVector bFlags)
{
    FogStageDataTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<FogStageData>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
FogStageDataTransitPtr FogStageDataBase::create(void)
{
    FogStageDataTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<FogStageData>(tmpPtr);
    }

    return fc;
}

FogStageData *FogStageDataBase::createEmptyLocal(BitVector bFlags)
{
    FogStageData *returnValue;

    newPtr<FogStageData>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
FogStageData *FogStageDataBase::createEmpty(void)
{
    FogStageData *returnValue;

    newPtr<FogStageData>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr FogStageDataBase::shallowCopyLocal(
    BitVector bFlags) const
{
    FogStageData *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const FogStageData *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr FogStageDataBase::shallowCopyDependent(
    BitVector bFlags) const
{
    FogStageData *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const FogStageData *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr FogStageDataBase::shallowCopy(void) const
{
    FogStageData *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const FogStageData *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

FogStageDataBase::FogStageDataBase(void) :
    Inherited(),
    _sfFogMaterial            (NULL),
    _sfWidth                  (Int32(0)),
    _sfHeight                 (Int32(0)),
    _sfRenderTarget           (NULL),
    _sfCamera                 (NULL)
{
}

FogStageDataBase::FogStageDataBase(const FogStageDataBase &source) :
    Inherited(source),
    _sfFogMaterial            (NULL),
    _sfWidth                  (source._sfWidth                  ),
    _sfHeight                 (source._sfHeight                 ),
    _sfRenderTarget           (NULL),
    _sfCamera                 (NULL)
{
}


/*-------------------------- destructors ----------------------------------*/

FogStageDataBase::~FogStageDataBase(void)
{
}

void FogStageDataBase::onCreate(const FogStageData *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        FogStageData *pThis = static_cast<FogStageData *>(this);

        pThis->setFogMaterial(source->getFogMaterial());

        pThis->setRenderTarget(source->getRenderTarget());

        pThis->setCamera(source->getCamera());
    }
}

GetFieldHandlePtr FogStageDataBase::getHandleFogMaterial     (void) const
{
    SFUnrecChunkMaterialPtr::GetHandlePtr returnValue(
        new  SFUnrecChunkMaterialPtr::GetHandle(
             &_sfFogMaterial,
             this->getType().getFieldDesc(FogMaterialFieldId),
             const_cast<FogStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr FogStageDataBase::editHandleFogMaterial    (void)
{
    SFUnrecChunkMaterialPtr::EditHandlePtr returnValue(
        new  SFUnrecChunkMaterialPtr::EditHandle(
             &_sfFogMaterial,
             this->getType().getFieldDesc(FogMaterialFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&FogStageData::setFogMaterial,
                    static_cast<FogStageData *>(this), ::boost::placeholders::_1));

    editSField(FogMaterialFieldMask);

    return returnValue;
}

GetFieldHandlePtr FogStageDataBase::getHandleWidth           (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfWidth,
             this->getType().getFieldDesc(WidthFieldId),
             const_cast<FogStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr FogStageDataBase::editHandleWidth          (void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfWidth,
             this->getType().getFieldDesc(WidthFieldId),
             this));


    editSField(WidthFieldMask);

    return returnValue;
}

GetFieldHandlePtr FogStageDataBase::getHandleHeight          (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfHeight,
             this->getType().getFieldDesc(HeightFieldId),
             const_cast<FogStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr FogStageDataBase::editHandleHeight         (void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfHeight,
             this->getType().getFieldDesc(HeightFieldId),
             this));


    editSField(HeightFieldMask);

    return returnValue;
}

GetFieldHandlePtr FogStageDataBase::getHandleRenderTarget    (void) const
{
    SFUnrecFrameBufferObjectPtr::GetHandlePtr returnValue(
        new  SFUnrecFrameBufferObjectPtr::GetHandle(
             &_sfRenderTarget,
             this->getType().getFieldDesc(RenderTargetFieldId),
             const_cast<FogStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr FogStageDataBase::editHandleRenderTarget   (void)
{
    SFUnrecFrameBufferObjectPtr::EditHandlePtr returnValue(
        new  SFUnrecFrameBufferObjectPtr::EditHandle(
             &_sfRenderTarget,
             this->getType().getFieldDesc(RenderTargetFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&FogStageData::setRenderTarget,
                    static_cast<FogStageData *>(this), ::boost::placeholders::_1));

    editSField(RenderTargetFieldMask);

    return returnValue;
}

GetFieldHandlePtr FogStageDataBase::getHandleCamera          (void) const
{
    SFUnrecCameraPtr::GetHandlePtr returnValue(
        new  SFUnrecCameraPtr::GetHandle(
             &_sfCamera,
             this->getType().getFieldDesc(CameraFieldId),
             const_cast<FogStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr FogStageDataBase::editHandleCamera         (void)
{
    SFUnrecCameraPtr::EditHandlePtr returnValue(
        new  SFUnrecCameraPtr::EditHandle(
             &_sfCamera,
             this->getType().getFieldDesc(CameraFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&FogStageData::setCamera,
                    static_cast<FogStageData *>(this), ::boost::placeholders::_1));

    editSField(CameraFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void FogStageDataBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    FogStageData *pThis = static_cast<FogStageData *>(this);

    pThis->execSync(static_cast<FogStageData *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *FogStageDataBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    FogStageData *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const FogStageData *>(pRefAspect),
                  dynamic_cast<const FogStageData *>(this));

    return returnValue;
}
#endif

void FogStageDataBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<FogStageData *>(this)->setFogMaterial(NULL);

    static_cast<FogStageData *>(this)->setRenderTarget(NULL);

    static_cast<FogStageData *>(this)->setCamera(NULL);


}


OSG_END_NAMESPACE
