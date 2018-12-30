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
 **     class HDRStage!
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


#include "OSGGLEXT.h"                     // BufferFormat default header


#include "OSGHDRStageBase.h"
#include "OSGHDRStage.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::HDRStage
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Real32          HDRStageBase::_sfExposure
    
*/

/*! \var Real32          HDRStageBase::_sfBlurWidth
    
*/

/*! \var Real32          HDRStageBase::_sfBlurAmount
    
*/

/*! \var Real32          HDRStageBase::_sfEffectAmount
    
*/

/*! \var Real32          HDRStageBase::_sfGamma
    
*/

/*! \var GLenum          HDRStageBase::_sfBufferFormat
    
*/

/*! \var bool            HDRStageBase::_sfCombineBlend
    Use blending when writing the combined scene and "effect"images
    to the target framebuffer.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<HDRStage *, nsOSG>::_type(
    "HDRStagePtr", 
    "StagePtr", 
    HDRStage::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(HDRStage *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void HDRStageBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "exposure",
        "",
        ExposureFieldId, ExposureFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&HDRStage::editHandleExposure),
        static_cast<FieldGetMethodSig >(&HDRStage::getHandleExposure));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "blurWidth",
        "",
        BlurWidthFieldId, BlurWidthFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&HDRStage::editHandleBlurWidth),
        static_cast<FieldGetMethodSig >(&HDRStage::getHandleBlurWidth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "blurAmount",
        "",
        BlurAmountFieldId, BlurAmountFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&HDRStage::editHandleBlurAmount),
        static_cast<FieldGetMethodSig >(&HDRStage::getHandleBlurAmount));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "effectAmount",
        "",
        EffectAmountFieldId, EffectAmountFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&HDRStage::editHandleEffectAmount),
        static_cast<FieldGetMethodSig >(&HDRStage::getHandleEffectAmount));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "gamma",
        "",
        GammaFieldId, GammaFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&HDRStage::editHandleGamma),
        static_cast<FieldGetMethodSig >(&HDRStage::getHandleGamma));

    oType.addInitialDesc(pDesc);

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(),
        "bufferFormat",
        "",
        BufferFormatFieldId, BufferFormatFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&HDRStage::editHandleBufferFormat),
        static_cast<FieldGetMethodSig >(&HDRStage::getHandleBufferFormat));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "combineBlend",
        "Use blending when writing the combined scene and \"effect\"images\n"
        "to the target framebuffer.\n",
        CombineBlendFieldId, CombineBlendFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&HDRStage::editHandleCombineBlend),
        static_cast<FieldGetMethodSig >(&HDRStage::getHandleCombineBlend));

    oType.addInitialDesc(pDesc);
}


HDRStageBase::TypeObject HDRStageBase::_type(
    HDRStageBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&HDRStageBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&HDRStage::initMethod),
    reinterpret_cast<ExitContainerF>(&HDRStage::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&HDRStage::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"HDRStage\"\n"
    "   parent=\"Stage\"\n"
    "   library=\"EffectGroups\"\n"
    "   pointerfieldtypes=\"none\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   isNodeCore=\"true\"\n"
    "   isBundle=\"false\"\n"
    "   docGroupBase=\"GrpEffectsGroupsHDR\"\n"
    "   >\n"
    "  <Field\n"
    "\t name=\"exposure\"\n"
    "\t type=\"Real32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"8.f\"\n"
    "\t access=\"public\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"blurWidth\"\n"
    "\t type=\"Real32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"3.0f\"\n"
    "\t access=\"public\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"blurAmount\"\n"
    "\t type=\"Real32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"0.5f\"\n"
    "\t access=\"public\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"effectAmount\"\n"
    "\t type=\"Real32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"0.2f\"\n"
    "\t access=\"public\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"gamma\"\n"
    "\t type=\"Real32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"1.f / 2.2f\"\n"
    "\t access=\"public\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"bufferFormat\"\n"
    "\t type=\"GLenum\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"GL_RGBA16F_ARB\"\n"
    "\t defaultHeader=\"&quot;OSGGLEXT.h&quot;\"\n"
    "\t access=\"public\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "     name=\"combineBlend\"\n"
    "     type=\"bool\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     defaultValue=\"false\"\n"
    "     access=\"public\"\n"
    "     >\n"
    "     Use blending when writing the combined scene and &quot;effect&quot; images\n"
    "     to the target framebuffer.\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &HDRStageBase::getType(void)
{
    return _type;
}

const FieldContainerType &HDRStageBase::getType(void) const
{
    return _type;
}

UInt32 HDRStageBase::getContainerSize(void) const
{
    return sizeof(HDRStage);
}

/*------------------------- decorator get ------------------------------*/


SFReal32 *HDRStageBase::editSFExposure(void)
{
    editSField(ExposureFieldMask);

    return &_sfExposure;
}

const SFReal32 *HDRStageBase::getSFExposure(void) const
{
    return &_sfExposure;
}


SFReal32 *HDRStageBase::editSFBlurWidth(void)
{
    editSField(BlurWidthFieldMask);

    return &_sfBlurWidth;
}

const SFReal32 *HDRStageBase::getSFBlurWidth(void) const
{
    return &_sfBlurWidth;
}


SFReal32 *HDRStageBase::editSFBlurAmount(void)
{
    editSField(BlurAmountFieldMask);

    return &_sfBlurAmount;
}

const SFReal32 *HDRStageBase::getSFBlurAmount(void) const
{
    return &_sfBlurAmount;
}


SFReal32 *HDRStageBase::editSFEffectAmount(void)
{
    editSField(EffectAmountFieldMask);

    return &_sfEffectAmount;
}

const SFReal32 *HDRStageBase::getSFEffectAmount(void) const
{
    return &_sfEffectAmount;
}


SFReal32 *HDRStageBase::editSFGamma(void)
{
    editSField(GammaFieldMask);

    return &_sfGamma;
}

const SFReal32 *HDRStageBase::getSFGamma(void) const
{
    return &_sfGamma;
}


SFGLenum *HDRStageBase::editSFBufferFormat(void)
{
    editSField(BufferFormatFieldMask);

    return &_sfBufferFormat;
}

const SFGLenum *HDRStageBase::getSFBufferFormat(void) const
{
    return &_sfBufferFormat;
}


SFBool *HDRStageBase::editSFCombineBlend(void)
{
    editSField(CombineBlendFieldMask);

    return &_sfCombineBlend;
}

const SFBool *HDRStageBase::getSFCombineBlend(void) const
{
    return &_sfCombineBlend;
}






/*------------------------------ access -----------------------------------*/

SizeT HDRStageBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ExposureFieldMask & whichField))
    {
        returnValue += _sfExposure.getBinSize();
    }
    if(FieldBits::NoField != (BlurWidthFieldMask & whichField))
    {
        returnValue += _sfBlurWidth.getBinSize();
    }
    if(FieldBits::NoField != (BlurAmountFieldMask & whichField))
    {
        returnValue += _sfBlurAmount.getBinSize();
    }
    if(FieldBits::NoField != (EffectAmountFieldMask & whichField))
    {
        returnValue += _sfEffectAmount.getBinSize();
    }
    if(FieldBits::NoField != (GammaFieldMask & whichField))
    {
        returnValue += _sfGamma.getBinSize();
    }
    if(FieldBits::NoField != (BufferFormatFieldMask & whichField))
    {
        returnValue += _sfBufferFormat.getBinSize();
    }
    if(FieldBits::NoField != (CombineBlendFieldMask & whichField))
    {
        returnValue += _sfCombineBlend.getBinSize();
    }

    return returnValue;
}

void HDRStageBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ExposureFieldMask & whichField))
    {
        _sfExposure.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BlurWidthFieldMask & whichField))
    {
        _sfBlurWidth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BlurAmountFieldMask & whichField))
    {
        _sfBlurAmount.copyToBin(pMem);
    }
    if(FieldBits::NoField != (EffectAmountFieldMask & whichField))
    {
        _sfEffectAmount.copyToBin(pMem);
    }
    if(FieldBits::NoField != (GammaFieldMask & whichField))
    {
        _sfGamma.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BufferFormatFieldMask & whichField))
    {
        _sfBufferFormat.copyToBin(pMem);
    }
    if(FieldBits::NoField != (CombineBlendFieldMask & whichField))
    {
        _sfCombineBlend.copyToBin(pMem);
    }
}

void HDRStageBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ExposureFieldMask & whichField))
    {
        editSField(ExposureFieldMask);
        _sfExposure.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BlurWidthFieldMask & whichField))
    {
        editSField(BlurWidthFieldMask);
        _sfBlurWidth.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BlurAmountFieldMask & whichField))
    {
        editSField(BlurAmountFieldMask);
        _sfBlurAmount.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (EffectAmountFieldMask & whichField))
    {
        editSField(EffectAmountFieldMask);
        _sfEffectAmount.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (GammaFieldMask & whichField))
    {
        editSField(GammaFieldMask);
        _sfGamma.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BufferFormatFieldMask & whichField))
    {
        editSField(BufferFormatFieldMask);
        _sfBufferFormat.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (CombineBlendFieldMask & whichField))
    {
        editSField(CombineBlendFieldMask);
        _sfCombineBlend.copyFromBin(pMem);
    }
}

//! create a new instance of the class
HDRStageTransitPtr HDRStageBase::createLocal(BitVector bFlags)
{
    HDRStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<HDRStage>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
HDRStageTransitPtr HDRStageBase::createDependent(BitVector bFlags)
{
    HDRStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<HDRStage>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
HDRStageTransitPtr HDRStageBase::create(void)
{
    HDRStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<HDRStage>(tmpPtr);
    }

    return fc;
}

HDRStage *HDRStageBase::createEmptyLocal(BitVector bFlags)
{
    HDRStage *returnValue;

    newPtr<HDRStage>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
HDRStage *HDRStageBase::createEmpty(void)
{
    HDRStage *returnValue;

    newPtr<HDRStage>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr HDRStageBase::shallowCopyLocal(
    BitVector bFlags) const
{
    HDRStage *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const HDRStage *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr HDRStageBase::shallowCopyDependent(
    BitVector bFlags) const
{
    HDRStage *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const HDRStage *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr HDRStageBase::shallowCopy(void) const
{
    HDRStage *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const HDRStage *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

HDRStageBase::HDRStageBase(void) :
    Inherited(),
    _sfExposure               (Real32(8.f)),
    _sfBlurWidth              (Real32(3.0f)),
    _sfBlurAmount             (Real32(0.5f)),
    _sfEffectAmount           (Real32(0.2f)),
    _sfGamma                  (Real32(1.f / 2.2f)),
    _sfBufferFormat           (GLenum(GL_RGBA16F_ARB)),
    _sfCombineBlend           (bool(false))
{
}

HDRStageBase::HDRStageBase(const HDRStageBase &source) :
    Inherited(source),
    _sfExposure               (source._sfExposure               ),
    _sfBlurWidth              (source._sfBlurWidth              ),
    _sfBlurAmount             (source._sfBlurAmount             ),
    _sfEffectAmount           (source._sfEffectAmount           ),
    _sfGamma                  (source._sfGamma                  ),
    _sfBufferFormat           (source._sfBufferFormat           ),
    _sfCombineBlend           (source._sfCombineBlend           )
{
}


/*-------------------------- destructors ----------------------------------*/

HDRStageBase::~HDRStageBase(void)
{
}


GetFieldHandlePtr HDRStageBase::getHandleExposure        (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfExposure,
             this->getType().getFieldDesc(ExposureFieldId),
             const_cast<HDRStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr HDRStageBase::editHandleExposure       (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfExposure,
             this->getType().getFieldDesc(ExposureFieldId),
             this));


    editSField(ExposureFieldMask);

    return returnValue;
}

GetFieldHandlePtr HDRStageBase::getHandleBlurWidth       (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfBlurWidth,
             this->getType().getFieldDesc(BlurWidthFieldId),
             const_cast<HDRStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr HDRStageBase::editHandleBlurWidth      (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfBlurWidth,
             this->getType().getFieldDesc(BlurWidthFieldId),
             this));


    editSField(BlurWidthFieldMask);

    return returnValue;
}

GetFieldHandlePtr HDRStageBase::getHandleBlurAmount      (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfBlurAmount,
             this->getType().getFieldDesc(BlurAmountFieldId),
             const_cast<HDRStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr HDRStageBase::editHandleBlurAmount     (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfBlurAmount,
             this->getType().getFieldDesc(BlurAmountFieldId),
             this));


    editSField(BlurAmountFieldMask);

    return returnValue;
}

GetFieldHandlePtr HDRStageBase::getHandleEffectAmount    (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfEffectAmount,
             this->getType().getFieldDesc(EffectAmountFieldId),
             const_cast<HDRStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr HDRStageBase::editHandleEffectAmount   (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfEffectAmount,
             this->getType().getFieldDesc(EffectAmountFieldId),
             this));


    editSField(EffectAmountFieldMask);

    return returnValue;
}

GetFieldHandlePtr HDRStageBase::getHandleGamma           (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfGamma,
             this->getType().getFieldDesc(GammaFieldId),
             const_cast<HDRStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr HDRStageBase::editHandleGamma          (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfGamma,
             this->getType().getFieldDesc(GammaFieldId),
             this));


    editSField(GammaFieldMask);

    return returnValue;
}

GetFieldHandlePtr HDRStageBase::getHandleBufferFormat    (void) const
{
    SFGLenum::GetHandlePtr returnValue(
        new  SFGLenum::GetHandle(
             &_sfBufferFormat,
             this->getType().getFieldDesc(BufferFormatFieldId),
             const_cast<HDRStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr HDRStageBase::editHandleBufferFormat   (void)
{
    SFGLenum::EditHandlePtr returnValue(
        new  SFGLenum::EditHandle(
             &_sfBufferFormat,
             this->getType().getFieldDesc(BufferFormatFieldId),
             this));


    editSField(BufferFormatFieldMask);

    return returnValue;
}

GetFieldHandlePtr HDRStageBase::getHandleCombineBlend    (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfCombineBlend,
             this->getType().getFieldDesc(CombineBlendFieldId),
             const_cast<HDRStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr HDRStageBase::editHandleCombineBlend   (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfCombineBlend,
             this->getType().getFieldDesc(CombineBlendFieldId),
             this));


    editSField(CombineBlendFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void HDRStageBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    HDRStage *pThis = static_cast<HDRStage *>(this);

    pThis->execSync(static_cast<HDRStage *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *HDRStageBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    HDRStage *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const HDRStage *>(pRefAspect),
                  dynamic_cast<const HDRStage *>(this));

    return returnValue;
}
#endif

void HDRStageBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
