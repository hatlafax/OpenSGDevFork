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
 **     class CubeMapGeneratorStageData!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"



#include "OSGCamera.h"                  // Camera Class
#include "OSGTextureTransformChunk.h"   // TexTransform Class

#include "OSGCubeMapGeneratorStageDataBase.h"
#include "OSGCubeMapGeneratorStageData.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CubeMapGeneratorStageData
    Data use for rendering by the generator stage
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Camera *        CubeMapGeneratorStageDataBase::_sfCamera
    
*/

/*! \var TextureTransformChunk * CubeMapGeneratorStageDataBase::_sfTexTransform
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<CubeMapGeneratorStageData *, nsOSG>::_type("CubeMapGeneratorStageDataPtr", "DynamicStateGeneratorStageDataPtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(CubeMapGeneratorStageData *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void CubeMapGeneratorStageDataBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecCameraPtr::Description(
        SFUnrecCameraPtr::getClassType(),
        "camera",
        "",
        CameraFieldId, CameraFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CubeMapGeneratorStageData::editHandleCamera),
        static_cast<FieldGetMethodSig >(&CubeMapGeneratorStageData::getHandleCamera));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecTextureTransformChunkPtr::Description(
        SFUnrecTextureTransformChunkPtr::getClassType(),
        "texTransform",
        "",
        TexTransformFieldId, TexTransformFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CubeMapGeneratorStageData::editHandleTexTransform),
        static_cast<FieldGetMethodSig >(&CubeMapGeneratorStageData::getHandleTexTransform));

    oType.addInitialDesc(pDesc);
}


CubeMapGeneratorStageDataBase::TypeObject CubeMapGeneratorStageDataBase::_type(
    CubeMapGeneratorStageDataBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&CubeMapGeneratorStageDataBase::createEmptyLocal),
    CubeMapGeneratorStageData::initMethod,
    CubeMapGeneratorStageData::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&CubeMapGeneratorStageData::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"CubeMapGeneratorStageData\"\n"
    "   parent=\"DynamicStateGeneratorStageData\"\n"
    "   library=\"Group\"\n"
    "   pointerfieldtypes=\"none\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   isNodeCore=\"false\"\n"
    "   isBundle=\"true\"\n"
    "   docGroupBase=\"GrpGroupDynamicStateGenerators\"\n"
    "   >\n"
    "  Data use for rendering by the generator stage\n"
    "  <Field\n"
    "\t name=\"camera\"\n"
    "\t type=\"CameraPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"NULL\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"texTransform\"\n"
    "\t type=\"TextureTransformChunkPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"NULL\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    "Data use for rendering by the generator stage\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &CubeMapGeneratorStageDataBase::getType(void)
{
    return _type;
}

const FieldContainerType &CubeMapGeneratorStageDataBase::getType(void) const
{
    return _type;
}

UInt32 CubeMapGeneratorStageDataBase::getContainerSize(void) const
{
    return sizeof(CubeMapGeneratorStageData);
}

/*------------------------- decorator get ------------------------------*/


//! Get the CubeMapGeneratorStageData::_sfCamera field.
const SFUnrecCameraPtr *CubeMapGeneratorStageDataBase::getSFCamera(void) const
{
    return &_sfCamera;
}

SFUnrecCameraPtr    *CubeMapGeneratorStageDataBase::editSFCamera         (void)
{
    editSField(CameraFieldMask);

    return &_sfCamera;
}

//! Get the CubeMapGeneratorStageData::_sfTexTransform field.
const SFUnrecTextureTransformChunkPtr *CubeMapGeneratorStageDataBase::getSFTexTransform(void) const
{
    return &_sfTexTransform;
}

SFUnrecTextureTransformChunkPtr *CubeMapGeneratorStageDataBase::editSFTexTransform   (void)
{
    editSField(TexTransformFieldMask);

    return &_sfTexTransform;
}





/*------------------------------ access -----------------------------------*/

UInt32 CubeMapGeneratorStageDataBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        returnValue += _sfCamera.getBinSize();
    }
    if(FieldBits::NoField != (TexTransformFieldMask & whichField))
    {
        returnValue += _sfTexTransform.getBinSize();
    }

    return returnValue;
}

void CubeMapGeneratorStageDataBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        _sfCamera.copyToBin(pMem);
    }
    if(FieldBits::NoField != (TexTransformFieldMask & whichField))
    {
        _sfTexTransform.copyToBin(pMem);
    }
}

void CubeMapGeneratorStageDataBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        editSField(CameraFieldMask);
        _sfCamera.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (TexTransformFieldMask & whichField))
    {
        editSField(TexTransformFieldMask);
        _sfTexTransform.copyFromBin(pMem);
    }
}

//! create a new instance of the class
CubeMapGeneratorStageDataTransitPtr CubeMapGeneratorStageDataBase::createLocal(BitVector bFlags)
{
    CubeMapGeneratorStageDataTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<CubeMapGeneratorStageData>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
CubeMapGeneratorStageDataTransitPtr CubeMapGeneratorStageDataBase::createDependent(BitVector bFlags)
{
    CubeMapGeneratorStageDataTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<CubeMapGeneratorStageData>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
CubeMapGeneratorStageDataTransitPtr CubeMapGeneratorStageDataBase::create(void)
{
    return createLocal();
}

CubeMapGeneratorStageData *CubeMapGeneratorStageDataBase::createEmptyLocal(BitVector bFlags)
{
    CubeMapGeneratorStageData *returnValue;

    newPtr<CubeMapGeneratorStageData>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
CubeMapGeneratorStageData *CubeMapGeneratorStageDataBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr CubeMapGeneratorStageDataBase::shallowCopyLocal(
    BitVector bFlags) const
{
    CubeMapGeneratorStageData *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CubeMapGeneratorStageData *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr CubeMapGeneratorStageDataBase::shallowCopyDependent(
    BitVector bFlags) const
{
    CubeMapGeneratorStageData *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CubeMapGeneratorStageData *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr CubeMapGeneratorStageDataBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

CubeMapGeneratorStageDataBase::CubeMapGeneratorStageDataBase(void) :
    Inherited(),
    _sfCamera                 (NULL),
    _sfTexTransform           (NULL)
{
}

CubeMapGeneratorStageDataBase::CubeMapGeneratorStageDataBase(const CubeMapGeneratorStageDataBase &source) :
    Inherited(source),
    _sfCamera                 (NULL),
    _sfTexTransform           (NULL)
{
}


/*-------------------------- destructors ----------------------------------*/

CubeMapGeneratorStageDataBase::~CubeMapGeneratorStageDataBase(void)
{
}

void CubeMapGeneratorStageDataBase::onCreate(const CubeMapGeneratorStageData *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        CubeMapGeneratorStageData *pThis = static_cast<CubeMapGeneratorStageData *>(this);

        pThis->setCamera(source->getCamera());

        pThis->setTexTransform(source->getTexTransform());
    }
}

GetFieldHandlePtr CubeMapGeneratorStageDataBase::getHandleCamera          (void) const
{
    SFUnrecCameraPtr::GetHandlePtr returnValue(
        new  SFUnrecCameraPtr::GetHandle(
             &_sfCamera,
             this->getType().getFieldDesc(CameraFieldId),
             const_cast<CubeMapGeneratorStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CubeMapGeneratorStageDataBase::editHandleCamera         (void)
{
    SFUnrecCameraPtr::EditHandlePtr returnValue(
        new  SFUnrecCameraPtr::EditHandle(
             &_sfCamera,
             this->getType().getFieldDesc(CameraFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&CubeMapGeneratorStageData::setCamera,
                    static_cast<CubeMapGeneratorStageData *>(this), _1));

    editSField(CameraFieldMask);

    return returnValue;
}

GetFieldHandlePtr CubeMapGeneratorStageDataBase::getHandleTexTransform    (void) const
{
    SFUnrecTextureTransformChunkPtr::GetHandlePtr returnValue(
        new  SFUnrecTextureTransformChunkPtr::GetHandle(
             &_sfTexTransform,
             this->getType().getFieldDesc(TexTransformFieldId),
             const_cast<CubeMapGeneratorStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CubeMapGeneratorStageDataBase::editHandleTexTransform   (void)
{
    SFUnrecTextureTransformChunkPtr::EditHandlePtr returnValue(
        new  SFUnrecTextureTransformChunkPtr::EditHandle(
             &_sfTexTransform,
             this->getType().getFieldDesc(TexTransformFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&CubeMapGeneratorStageData::setTexTransform,
                    static_cast<CubeMapGeneratorStageData *>(this), _1));

    editSField(TexTransformFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void CubeMapGeneratorStageDataBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    CubeMapGeneratorStageData *pThis = static_cast<CubeMapGeneratorStageData *>(this);

    pThis->execSync(static_cast<CubeMapGeneratorStageData *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *CubeMapGeneratorStageDataBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    CubeMapGeneratorStageData *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const CubeMapGeneratorStageData *>(pRefAspect),
                  dynamic_cast<const CubeMapGeneratorStageData *>(this));

    return returnValue;
}
#endif

void CubeMapGeneratorStageDataBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<CubeMapGeneratorStageData *>(this)->setCamera(NULL);

    static_cast<CubeMapGeneratorStageData *>(this)->setTexTransform(NULL);


}


OSG_END_NAMESPACE
