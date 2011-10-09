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
 **     class ShadowStageData!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"



#include "OSGChunkMaterial.h"           // ToneMappingMaterial Class
#include "OSGFrameBufferObject.h"       // BlurRenderTarget Class
#include "OSGSimpleSHLChunk.h"          // HBlurShader Class

#include "OSGShadowStageDataBase.h"
#include "OSGShadowStageData.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ShadowStageData
    Data use for rendering by the HDR stage
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var ChunkMaterial * ShadowStageDataBase::_sfToneMappingMaterial
    
*/

/*! \var FrameBufferObject * ShadowStageDataBase::_sfBlurRenderTarget
    
*/

/*! \var ChunkMaterial * ShadowStageDataBase::_sfBlurMaterial
    
*/

/*! \var SimpleSHLChunk * ShadowStageDataBase::_sfHBlurShader
    
*/

/*! \var SimpleSHLChunk * ShadowStageDataBase::_sfVBlurShader
    
*/

/*! \var UInt32          ShadowStageDataBase::_sfWidth
    
*/

/*! \var UInt32          ShadowStageDataBase::_sfHeight
    
*/

/*! \var FrameBufferObject * ShadowStageDataBase::_sfShrinkRenderTarget
    
*/

/*! \var ChunkMaterial * ShadowStageDataBase::_sfShrinkMaterial
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ShadowStageData *, nsOSG>::_type("ShadowStageDataPtr", "StageDataPtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(ShadowStageData *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ShadowStageDataBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecChunkMaterialPtr::Description(
        SFUnrecChunkMaterialPtr::getClassType(),
        "toneMappingMaterial",
        "",
        ToneMappingMaterialFieldId, ToneMappingMaterialFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShadowStageData::editHandleToneMappingMaterial),
        static_cast<FieldGetMethodSig >(&ShadowStageData::getHandleToneMappingMaterial));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecFrameBufferObjectPtr::Description(
        SFUnrecFrameBufferObjectPtr::getClassType(),
        "blurRenderTarget",
        "",
        BlurRenderTargetFieldId, BlurRenderTargetFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShadowStageData::editHandleBlurRenderTarget),
        static_cast<FieldGetMethodSig >(&ShadowStageData::getHandleBlurRenderTarget));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecChunkMaterialPtr::Description(
        SFUnrecChunkMaterialPtr::getClassType(),
        "blurMaterial",
        "",
        BlurMaterialFieldId, BlurMaterialFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShadowStageData::editHandleBlurMaterial),
        static_cast<FieldGetMethodSig >(&ShadowStageData::getHandleBlurMaterial));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecSimpleSHLChunkPtr::Description(
        SFUnrecSimpleSHLChunkPtr::getClassType(),
        "hBlurShader",
        "",
        HBlurShaderFieldId, HBlurShaderFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShadowStageData::editHandleHBlurShader),
        static_cast<FieldGetMethodSig >(&ShadowStageData::getHandleHBlurShader));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecSimpleSHLChunkPtr::Description(
        SFUnrecSimpleSHLChunkPtr::getClassType(),
        "vBlurShader",
        "",
        VBlurShaderFieldId, VBlurShaderFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShadowStageData::editHandleVBlurShader),
        static_cast<FieldGetMethodSig >(&ShadowStageData::getHandleVBlurShader));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "width",
        "",
        WidthFieldId, WidthFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShadowStageData::editHandleWidth),
        static_cast<FieldGetMethodSig >(&ShadowStageData::getHandleWidth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "height",
        "",
        HeightFieldId, HeightFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShadowStageData::editHandleHeight),
        static_cast<FieldGetMethodSig >(&ShadowStageData::getHandleHeight));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecFrameBufferObjectPtr::Description(
        SFUnrecFrameBufferObjectPtr::getClassType(),
        "shrinkRenderTarget",
        "",
        ShrinkRenderTargetFieldId, ShrinkRenderTargetFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShadowStageData::editHandleShrinkRenderTarget),
        static_cast<FieldGetMethodSig >(&ShadowStageData::getHandleShrinkRenderTarget));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecChunkMaterialPtr::Description(
        SFUnrecChunkMaterialPtr::getClassType(),
        "shrinkMaterial",
        "",
        ShrinkMaterialFieldId, ShrinkMaterialFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShadowStageData::editHandleShrinkMaterial),
        static_cast<FieldGetMethodSig >(&ShadowStageData::getHandleShrinkMaterial));

    oType.addInitialDesc(pDesc);
}


ShadowStageDataBase::TypeObject ShadowStageDataBase::_type(
    ShadowStageDataBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&ShadowStageDataBase::createEmptyLocal),
    ShadowStageData::initMethod,
    ShadowStageData::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&ShadowStageData::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"ShadowStageData\"\n"
    "   parent=\"StageData\"\n"
    "   library=\"EffectGroups\"\n"
    "   pointerfieldtypes=\"none\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   isNodeCore=\"false\"\n"
    "   isBundle=\"true\"\n"
    "   docGroupBase=\"GrpEffectsGroupsDeferredShading\"\n"
    "   >\n"
    "  Data use for rendering by the HDR stage\n"
    "  <Field\n"
    "\t name=\"toneMappingMaterial\"\n"
    "\t type=\"ChunkMaterialPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"NULL\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"blurRenderTarget\"\n"
    "\t type=\"FrameBufferObjectPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"NULL\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"blurMaterial\"\n"
    "\t type=\"ChunkMaterialPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"NULL\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"hBlurShader\"\n"
    "\t type=\"SimpleSHLChunkPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"NULL\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"vBlurShader\"\n"
    "\t type=\"SimpleSHLChunkPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"NULL\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"width\"\n"
    "\t type=\"UInt32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"0\"\n"
    "\t access=\"public\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"height\"\n"
    "\t type=\"UInt32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"0\"\n"
    "\t access=\"public\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"shrinkRenderTarget\"\n"
    "\t type=\"FrameBufferObjectPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"NULL\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"shrinkMaterial\"\n"
    "\t type=\"ChunkMaterialPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"NULL\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    "Data use for rendering by the HDR stage\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ShadowStageDataBase::getType(void)
{
    return _type;
}

const FieldContainerType &ShadowStageDataBase::getType(void) const
{
    return _type;
}

UInt32 ShadowStageDataBase::getContainerSize(void) const
{
    return sizeof(ShadowStageData);
}

/*------------------------- decorator get ------------------------------*/


//! Get the ShadowStageData::_sfToneMappingMaterial field.
const SFUnrecChunkMaterialPtr *ShadowStageDataBase::getSFToneMappingMaterial(void) const
{
    return &_sfToneMappingMaterial;
}

SFUnrecChunkMaterialPtr *ShadowStageDataBase::editSFToneMappingMaterial(void)
{
    editSField(ToneMappingMaterialFieldMask);

    return &_sfToneMappingMaterial;
}

//! Get the ShadowStageData::_sfBlurRenderTarget field.
const SFUnrecFrameBufferObjectPtr *ShadowStageDataBase::getSFBlurRenderTarget(void) const
{
    return &_sfBlurRenderTarget;
}

SFUnrecFrameBufferObjectPtr *ShadowStageDataBase::editSFBlurRenderTarget(void)
{
    editSField(BlurRenderTargetFieldMask);

    return &_sfBlurRenderTarget;
}

//! Get the ShadowStageData::_sfBlurMaterial field.
const SFUnrecChunkMaterialPtr *ShadowStageDataBase::getSFBlurMaterial(void) const
{
    return &_sfBlurMaterial;
}

SFUnrecChunkMaterialPtr *ShadowStageDataBase::editSFBlurMaterial   (void)
{
    editSField(BlurMaterialFieldMask);

    return &_sfBlurMaterial;
}

//! Get the ShadowStageData::_sfHBlurShader field.
const SFUnrecSimpleSHLChunkPtr *ShadowStageDataBase::getSFHBlurShader(void) const
{
    return &_sfHBlurShader;
}

SFUnrecSimpleSHLChunkPtr *ShadowStageDataBase::editSFHBlurShader    (void)
{
    editSField(HBlurShaderFieldMask);

    return &_sfHBlurShader;
}

//! Get the ShadowStageData::_sfVBlurShader field.
const SFUnrecSimpleSHLChunkPtr *ShadowStageDataBase::getSFVBlurShader(void) const
{
    return &_sfVBlurShader;
}

SFUnrecSimpleSHLChunkPtr *ShadowStageDataBase::editSFVBlurShader    (void)
{
    editSField(VBlurShaderFieldMask);

    return &_sfVBlurShader;
}

SFUInt32 *ShadowStageDataBase::editSFWidth(void)
{
    editSField(WidthFieldMask);

    return &_sfWidth;
}

const SFUInt32 *ShadowStageDataBase::getSFWidth(void) const
{
    return &_sfWidth;
}


SFUInt32 *ShadowStageDataBase::editSFHeight(void)
{
    editSField(HeightFieldMask);

    return &_sfHeight;
}

const SFUInt32 *ShadowStageDataBase::getSFHeight(void) const
{
    return &_sfHeight;
}


//! Get the ShadowStageData::_sfShrinkRenderTarget field.
const SFUnrecFrameBufferObjectPtr *ShadowStageDataBase::getSFShrinkRenderTarget(void) const
{
    return &_sfShrinkRenderTarget;
}

SFUnrecFrameBufferObjectPtr *ShadowStageDataBase::editSFShrinkRenderTarget(void)
{
    editSField(ShrinkRenderTargetFieldMask);

    return &_sfShrinkRenderTarget;
}

//! Get the ShadowStageData::_sfShrinkMaterial field.
const SFUnrecChunkMaterialPtr *ShadowStageDataBase::getSFShrinkMaterial(void) const
{
    return &_sfShrinkMaterial;
}

SFUnrecChunkMaterialPtr *ShadowStageDataBase::editSFShrinkMaterial (void)
{
    editSField(ShrinkMaterialFieldMask);

    return &_sfShrinkMaterial;
}





/*------------------------------ access -----------------------------------*/

UInt32 ShadowStageDataBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ToneMappingMaterialFieldMask & whichField))
    {
        returnValue += _sfToneMappingMaterial.getBinSize();
    }
    if(FieldBits::NoField != (BlurRenderTargetFieldMask & whichField))
    {
        returnValue += _sfBlurRenderTarget.getBinSize();
    }
    if(FieldBits::NoField != (BlurMaterialFieldMask & whichField))
    {
        returnValue += _sfBlurMaterial.getBinSize();
    }
    if(FieldBits::NoField != (HBlurShaderFieldMask & whichField))
    {
        returnValue += _sfHBlurShader.getBinSize();
    }
    if(FieldBits::NoField != (VBlurShaderFieldMask & whichField))
    {
        returnValue += _sfVBlurShader.getBinSize();
    }
    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        returnValue += _sfWidth.getBinSize();
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        returnValue += _sfHeight.getBinSize();
    }
    if(FieldBits::NoField != (ShrinkRenderTargetFieldMask & whichField))
    {
        returnValue += _sfShrinkRenderTarget.getBinSize();
    }
    if(FieldBits::NoField != (ShrinkMaterialFieldMask & whichField))
    {
        returnValue += _sfShrinkMaterial.getBinSize();
    }

    return returnValue;
}

void ShadowStageDataBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ToneMappingMaterialFieldMask & whichField))
    {
        _sfToneMappingMaterial.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BlurRenderTargetFieldMask & whichField))
    {
        _sfBlurRenderTarget.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BlurMaterialFieldMask & whichField))
    {
        _sfBlurMaterial.copyToBin(pMem);
    }
    if(FieldBits::NoField != (HBlurShaderFieldMask & whichField))
    {
        _sfHBlurShader.copyToBin(pMem);
    }
    if(FieldBits::NoField != (VBlurShaderFieldMask & whichField))
    {
        _sfVBlurShader.copyToBin(pMem);
    }
    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        _sfWidth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (HeightFieldMask & whichField))
    {
        _sfHeight.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ShrinkRenderTargetFieldMask & whichField))
    {
        _sfShrinkRenderTarget.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ShrinkMaterialFieldMask & whichField))
    {
        _sfShrinkMaterial.copyToBin(pMem);
    }
}

void ShadowStageDataBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ToneMappingMaterialFieldMask & whichField))
    {
        editSField(ToneMappingMaterialFieldMask);
        _sfToneMappingMaterial.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BlurRenderTargetFieldMask & whichField))
    {
        editSField(BlurRenderTargetFieldMask);
        _sfBlurRenderTarget.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BlurMaterialFieldMask & whichField))
    {
        editSField(BlurMaterialFieldMask);
        _sfBlurMaterial.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (HBlurShaderFieldMask & whichField))
    {
        editSField(HBlurShaderFieldMask);
        _sfHBlurShader.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (VBlurShaderFieldMask & whichField))
    {
        editSField(VBlurShaderFieldMask);
        _sfVBlurShader.copyFromBin(pMem);
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
    if(FieldBits::NoField != (ShrinkRenderTargetFieldMask & whichField))
    {
        editSField(ShrinkRenderTargetFieldMask);
        _sfShrinkRenderTarget.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ShrinkMaterialFieldMask & whichField))
    {
        editSField(ShrinkMaterialFieldMask);
        _sfShrinkMaterial.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ShadowStageDataTransitPtr ShadowStageDataBase::createLocal(BitVector bFlags)
{
    ShadowStageDataTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ShadowStageData>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ShadowStageDataTransitPtr ShadowStageDataBase::createDependent(BitVector bFlags)
{
    ShadowStageDataTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ShadowStageData>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ShadowStageDataTransitPtr ShadowStageDataBase::create(void)
{
    return createLocal();
}

ShadowStageData *ShadowStageDataBase::createEmptyLocal(BitVector bFlags)
{
    ShadowStageData *returnValue;

    newPtr<ShadowStageData>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ShadowStageData *ShadowStageDataBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr ShadowStageDataBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ShadowStageData *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShadowStageData *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShadowStageDataBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ShadowStageData *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShadowStageData *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShadowStageDataBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

ShadowStageDataBase::ShadowStageDataBase(void) :
    Inherited(),
    _sfToneMappingMaterial    (NULL),
    _sfBlurRenderTarget       (NULL),
    _sfBlurMaterial           (NULL),
    _sfHBlurShader            (NULL),
    _sfVBlurShader            (NULL),
    _sfWidth                  (UInt32(0)),
    _sfHeight                 (UInt32(0)),
    _sfShrinkRenderTarget     (NULL),
    _sfShrinkMaterial         (NULL)
{
}

ShadowStageDataBase::ShadowStageDataBase(const ShadowStageDataBase &source) :
    Inherited(source),
    _sfToneMappingMaterial    (NULL),
    _sfBlurRenderTarget       (NULL),
    _sfBlurMaterial           (NULL),
    _sfHBlurShader            (NULL),
    _sfVBlurShader            (NULL),
    _sfWidth                  (source._sfWidth                  ),
    _sfHeight                 (source._sfHeight                 ),
    _sfShrinkRenderTarget     (NULL),
    _sfShrinkMaterial         (NULL)
{
}


/*-------------------------- destructors ----------------------------------*/

ShadowStageDataBase::~ShadowStageDataBase(void)
{
}

void ShadowStageDataBase::onCreate(const ShadowStageData *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        ShadowStageData *pThis = static_cast<ShadowStageData *>(this);

        pThis->setToneMappingMaterial(source->getToneMappingMaterial());

        pThis->setBlurRenderTarget(source->getBlurRenderTarget());

        pThis->setBlurMaterial(source->getBlurMaterial());

        pThis->setHBlurShader(source->getHBlurShader());

        pThis->setVBlurShader(source->getVBlurShader());

        pThis->setShrinkRenderTarget(source->getShrinkRenderTarget());

        pThis->setShrinkMaterial(source->getShrinkMaterial());
    }
}

GetFieldHandlePtr ShadowStageDataBase::getHandleToneMappingMaterial (void) const
{
    SFUnrecChunkMaterialPtr::GetHandlePtr returnValue(
        new  SFUnrecChunkMaterialPtr::GetHandle(
             &_sfToneMappingMaterial,
             this->getType().getFieldDesc(ToneMappingMaterialFieldId),
             const_cast<ShadowStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShadowStageDataBase::editHandleToneMappingMaterial(void)
{
    SFUnrecChunkMaterialPtr::EditHandlePtr returnValue(
        new  SFUnrecChunkMaterialPtr::EditHandle(
             &_sfToneMappingMaterial,
             this->getType().getFieldDesc(ToneMappingMaterialFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShadowStageData::setToneMappingMaterial,
                    static_cast<ShadowStageData *>(this), _1));

    editSField(ToneMappingMaterialFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShadowStageDataBase::getHandleBlurRenderTarget (void) const
{
    SFUnrecFrameBufferObjectPtr::GetHandlePtr returnValue(
        new  SFUnrecFrameBufferObjectPtr::GetHandle(
             &_sfBlurRenderTarget,
             this->getType().getFieldDesc(BlurRenderTargetFieldId),
             const_cast<ShadowStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShadowStageDataBase::editHandleBlurRenderTarget(void)
{
    SFUnrecFrameBufferObjectPtr::EditHandlePtr returnValue(
        new  SFUnrecFrameBufferObjectPtr::EditHandle(
             &_sfBlurRenderTarget,
             this->getType().getFieldDesc(BlurRenderTargetFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShadowStageData::setBlurRenderTarget,
                    static_cast<ShadowStageData *>(this), _1));

    editSField(BlurRenderTargetFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShadowStageDataBase::getHandleBlurMaterial    (void) const
{
    SFUnrecChunkMaterialPtr::GetHandlePtr returnValue(
        new  SFUnrecChunkMaterialPtr::GetHandle(
             &_sfBlurMaterial,
             this->getType().getFieldDesc(BlurMaterialFieldId),
             const_cast<ShadowStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShadowStageDataBase::editHandleBlurMaterial   (void)
{
    SFUnrecChunkMaterialPtr::EditHandlePtr returnValue(
        new  SFUnrecChunkMaterialPtr::EditHandle(
             &_sfBlurMaterial,
             this->getType().getFieldDesc(BlurMaterialFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShadowStageData::setBlurMaterial,
                    static_cast<ShadowStageData *>(this), _1));

    editSField(BlurMaterialFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShadowStageDataBase::getHandleHBlurShader     (void) const
{
    SFUnrecSimpleSHLChunkPtr::GetHandlePtr returnValue(
        new  SFUnrecSimpleSHLChunkPtr::GetHandle(
             &_sfHBlurShader,
             this->getType().getFieldDesc(HBlurShaderFieldId),
             const_cast<ShadowStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShadowStageDataBase::editHandleHBlurShader    (void)
{
    SFUnrecSimpleSHLChunkPtr::EditHandlePtr returnValue(
        new  SFUnrecSimpleSHLChunkPtr::EditHandle(
             &_sfHBlurShader,
             this->getType().getFieldDesc(HBlurShaderFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShadowStageData::setHBlurShader,
                    static_cast<ShadowStageData *>(this), _1));

    editSField(HBlurShaderFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShadowStageDataBase::getHandleVBlurShader     (void) const
{
    SFUnrecSimpleSHLChunkPtr::GetHandlePtr returnValue(
        new  SFUnrecSimpleSHLChunkPtr::GetHandle(
             &_sfVBlurShader,
             this->getType().getFieldDesc(VBlurShaderFieldId),
             const_cast<ShadowStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShadowStageDataBase::editHandleVBlurShader    (void)
{
    SFUnrecSimpleSHLChunkPtr::EditHandlePtr returnValue(
        new  SFUnrecSimpleSHLChunkPtr::EditHandle(
             &_sfVBlurShader,
             this->getType().getFieldDesc(VBlurShaderFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShadowStageData::setVBlurShader,
                    static_cast<ShadowStageData *>(this), _1));

    editSField(VBlurShaderFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShadowStageDataBase::getHandleWidth           (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfWidth,
             this->getType().getFieldDesc(WidthFieldId),
             const_cast<ShadowStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShadowStageDataBase::editHandleWidth          (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfWidth,
             this->getType().getFieldDesc(WidthFieldId),
             this));


    editSField(WidthFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShadowStageDataBase::getHandleHeight          (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfHeight,
             this->getType().getFieldDesc(HeightFieldId),
             const_cast<ShadowStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShadowStageDataBase::editHandleHeight         (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfHeight,
             this->getType().getFieldDesc(HeightFieldId),
             this));


    editSField(HeightFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShadowStageDataBase::getHandleShrinkRenderTarget (void) const
{
    SFUnrecFrameBufferObjectPtr::GetHandlePtr returnValue(
        new  SFUnrecFrameBufferObjectPtr::GetHandle(
             &_sfShrinkRenderTarget,
             this->getType().getFieldDesc(ShrinkRenderTargetFieldId),
             const_cast<ShadowStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShadowStageDataBase::editHandleShrinkRenderTarget(void)
{
    SFUnrecFrameBufferObjectPtr::EditHandlePtr returnValue(
        new  SFUnrecFrameBufferObjectPtr::EditHandle(
             &_sfShrinkRenderTarget,
             this->getType().getFieldDesc(ShrinkRenderTargetFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShadowStageData::setShrinkRenderTarget,
                    static_cast<ShadowStageData *>(this), _1));

    editSField(ShrinkRenderTargetFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShadowStageDataBase::getHandleShrinkMaterial  (void) const
{
    SFUnrecChunkMaterialPtr::GetHandlePtr returnValue(
        new  SFUnrecChunkMaterialPtr::GetHandle(
             &_sfShrinkMaterial,
             this->getType().getFieldDesc(ShrinkMaterialFieldId),
             const_cast<ShadowStageDataBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShadowStageDataBase::editHandleShrinkMaterial (void)
{
    SFUnrecChunkMaterialPtr::EditHandlePtr returnValue(
        new  SFUnrecChunkMaterialPtr::EditHandle(
             &_sfShrinkMaterial,
             this->getType().getFieldDesc(ShrinkMaterialFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShadowStageData::setShrinkMaterial,
                    static_cast<ShadowStageData *>(this), _1));

    editSField(ShrinkMaterialFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ShadowStageDataBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ShadowStageData *pThis = static_cast<ShadowStageData *>(this);

    pThis->execSync(static_cast<ShadowStageData *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ShadowStageDataBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ShadowStageData *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ShadowStageData *>(pRefAspect),
                  dynamic_cast<const ShadowStageData *>(this));

    return returnValue;
}
#endif

void ShadowStageDataBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<ShadowStageData *>(this)->setToneMappingMaterial(NULL);

    static_cast<ShadowStageData *>(this)->setBlurRenderTarget(NULL);

    static_cast<ShadowStageData *>(this)->setBlurMaterial(NULL);

    static_cast<ShadowStageData *>(this)->setHBlurShader(NULL);

    static_cast<ShadowStageData *>(this)->setVBlurShader(NULL);

    static_cast<ShadowStageData *>(this)->setShrinkRenderTarget(NULL);

    static_cast<ShadowStageData *>(this)->setShrinkMaterial(NULL);


}


OSG_END_NAMESPACE
