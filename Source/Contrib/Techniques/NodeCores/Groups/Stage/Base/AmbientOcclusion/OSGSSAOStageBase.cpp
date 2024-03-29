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
 **     class SSAOStage!
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



#include "OSGUniformBufferObjStd140Chunk.h" // OffsetKernelChunk Class
#include "OSGTextureObjChunk.h"         // RotateKernelChunk Class

#include "OSGSSAOStageBase.h"
#include "OSGSSAOStage.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SSAOStage
    This stage generates an ambient occlusion texture object from its child tree.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var bool            SSAOStageBase::_sfActivate
    If the stage is deactivated it does not perform any action on its own but act as a simple Group core.
*/

/*! \var bool            SSAOStageBase::_sfCalcPosFromDepth
    If true the view space position is calculated from the depth texture value in the SSAO shader.
    Otherwise a separate position texture is used to get the position information into the SSAO shader.
*/

/*! \var Int32           SSAOStageBase::_sfOffsetKernelSize
    The number of hemisphere samples used in the SSAO technique.
*/

/*! \var Int32           SSAOStageBase::_sfRotateKernelSize
    The square root of the rotation vector kernel size. A texture with
    these vectors is tiled over the scene.
*/

/*! \var Real32          SSAOStageBase::_sfRadius
    The radius of the sample hemisphere.
*/

/*! \var Real32          SSAOStageBase::_sfBias
    The bias value used for depth testing.
*/

/*! \var Int32           SSAOStageBase::_sfBlurKernelSize
    Number of tap iterations (x,y) used in the Blur shader. Reasonable values are in the interval [2, 10].
*/

/*! \var Int32           SSAOStageBase::_sfAmbientOcclusionTexUnit
    Texture unit for the final ambientOcclusion texture map. This texture is activated
    for the subsequent scene rendering pass. Shaders are expected to provide a sampler
    for this texture.
*/

/*! \var UniformBufferObjStd140Chunk * SSAOStageBase::_sfOffsetKernelChunk
    
*/

/*! \var TextureObjChunk * SSAOStageBase::_sfRotateKernelChunk
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<SSAOStage *, nsOSG>::_type(
    "SSAOStagePtr", 
    "StagePtr", 
    SSAOStage::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(SSAOStage *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           SSAOStage *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           SSAOStage *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void SSAOStageBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "activate",
        "If the stage is deactivated it does not perform any action on its own but act as a simple Group core.\n",
        ActivateFieldId, ActivateFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SSAOStage::editHandleActivate),
        static_cast<FieldGetMethodSig >(&SSAOStage::getHandleActivate));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "calcPosFromDepth",
        "If true the view space position is calculated from the depth texture value in the SSAO shader.\n"
        "Otherwise a separate position texture is used to get the position information into the SSAO shader.\n",
        CalcPosFromDepthFieldId, CalcPosFromDepthFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SSAOStage::editHandleCalcPosFromDepth),
        static_cast<FieldGetMethodSig >(&SSAOStage::getHandleCalcPosFromDepth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "offsetKernelSize",
        "The number of hemisphere samples used in the SSAO technique.\n",
        OffsetKernelSizeFieldId, OffsetKernelSizeFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SSAOStage::editHandleOffsetKernelSize),
        static_cast<FieldGetMethodSig >(&SSAOStage::getHandleOffsetKernelSize));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "rotateKernelSize",
        "The square root of the rotation vector kernel size. A texture with\n"
        "these vectors is tiled over the scene.\n",
        RotateKernelSizeFieldId, RotateKernelSizeFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SSAOStage::editHandleRotateKernelSize),
        static_cast<FieldGetMethodSig >(&SSAOStage::getHandleRotateKernelSize));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "radius",
        "The radius of the sample hemisphere.\n",
        RadiusFieldId, RadiusFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SSAOStage::editHandleRadius),
        static_cast<FieldGetMethodSig >(&SSAOStage::getHandleRadius));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "bias",
        "The bias value used for depth testing.\n",
        BiasFieldId, BiasFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SSAOStage::editHandleBias),
        static_cast<FieldGetMethodSig >(&SSAOStage::getHandleBias));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "blurKernelSize",
        "Number of tap iterations (x,y) used in the Blur shader. Reasonable values are in the interval [2, 10].\n",
        BlurKernelSizeFieldId, BlurKernelSizeFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SSAOStage::editHandleBlurKernelSize),
        static_cast<FieldGetMethodSig >(&SSAOStage::getHandleBlurKernelSize));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "ambientOcclusionTexUnit",
        "Texture unit for the final ambientOcclusion texture map. This texture is activated\n"
        "for the subsequent scene rendering pass. Shaders are expected to provide a sampler\n"
        "for this texture.\n",
        AmbientOcclusionTexUnitFieldId, AmbientOcclusionTexUnitFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SSAOStage::editHandleAmbientOcclusionTexUnit),
        static_cast<FieldGetMethodSig >(&SSAOStage::getHandleAmbientOcclusionTexUnit));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecUniformBufferObjStd140ChunkPtr::Description(
        SFUnrecUniformBufferObjStd140ChunkPtr::getClassType(),
        "offsetKernelChunk",
        "",
        OffsetKernelChunkFieldId, OffsetKernelChunkFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SSAOStage::editHandleOffsetKernelChunk),
        static_cast<FieldGetMethodSig >(&SSAOStage::getHandleOffsetKernelChunk));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecTextureObjChunkPtr::Description(
        SFUnrecTextureObjChunkPtr::getClassType(),
        "rotateKernelChunk",
        "",
        RotateKernelChunkFieldId, RotateKernelChunkFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&SSAOStage::editHandleRotateKernelChunk),
        static_cast<FieldGetMethodSig >(&SSAOStage::getHandleRotateKernelChunk));

    oType.addInitialDesc(pDesc);
}


SSAOStageBase::TypeObject SSAOStageBase::_type(
    SSAOStageBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&SSAOStageBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&SSAOStage::initMethod),
    reinterpret_cast<ExitContainerF>(&SSAOStage::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&SSAOStage::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"SSAOStage\"\n"
    "    parent=\"Stage\"\n"
    "    library=\"ContribTechniques\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"true\"\n"
    "    isBundle=\"false\"\n"
    "    >\n"
    "    This stage generates an ambient occlusion texture object from its child tree.\n"
    "\n"
    "    <Field\n"
    "        name=\"activate\"\n"
    "        type=\"bool\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"true\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "        If the stage is deactivated it does not perform any action on its own but act as a simple Group core.\n"
    "    </Field>\n"
    "    \n"
    "    <Field\n"
    "        name=\"calcPosFromDepth\"\n"
    "        type=\"bool\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"true\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "        If true the view space position is calculated from the depth texture value in the SSAO shader.\n"
    "        Otherwise a separate position texture is used to get the position information into the SSAO shader.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"offsetKernelSize\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"64\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "        The number of hemisphere samples used in the SSAO technique.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"rotateKernelSize\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"4\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "        The square root of the rotation vector kernel size. A texture with\n"
    "        these vectors is tiled over the scene.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"radius\"\n"
    "        type=\"Real32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"0.5\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "        The radius of the sample hemisphere.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"bias\"\n"
    "        type=\"Real32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"0.025\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "        The bias value used for depth testing.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"blurKernelSize\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"4\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "        Number of tap iterations (x,y) used in the Blur shader. Reasonable values are in the interval [2, 10].\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"ambientOcclusionTexUnit\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "\taccess=\"public\"\n"
    "        defaultValue=\"16\"\n"
    "        >\n"
    "        Texture unit for the final ambientOcclusion texture map. This texture is activated\n"
    "        for the subsequent scene rendering pass. Shaders are expected to provide a sampler\n"
    "        for this texture.\n"
    "    </Field>\n"
    "\n"
    "    <Field\n"
    "        name=\"offsetKernelChunk\"\n"
    "        type=\"UniformBufferObjStd140ChunkPtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "\taccess=\"protected\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "    </Field>\n"
    "    \n"
    "    <Field\n"
    "        name=\"rotateKernelChunk\"\n"
    "        type=\"TextureObjChunkPtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "\taccess=\"protected\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "    </Field>\n"
    "\n"
    "</FieldContainer>\n",
    "This stage generates an ambient occlusion texture object from its child tree.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &SSAOStageBase::getType(void)
{
    return _type;
}

const FieldContainerType &SSAOStageBase::getType(void) const
{
    return _type;
}

UInt32 SSAOStageBase::getContainerSize(void) const
{
    return sizeof(SSAOStage);
}

/*------------------------- decorator get ------------------------------*/


SFBool *SSAOStageBase::editSFActivate(void)
{
    editSField(ActivateFieldMask);

    return &_sfActivate;
}

const SFBool *SSAOStageBase::getSFActivate(void) const
{
    return &_sfActivate;
}


SFBool *SSAOStageBase::editSFCalcPosFromDepth(void)
{
    editSField(CalcPosFromDepthFieldMask);

    return &_sfCalcPosFromDepth;
}

const SFBool *SSAOStageBase::getSFCalcPosFromDepth(void) const
{
    return &_sfCalcPosFromDepth;
}


SFInt32 *SSAOStageBase::editSFOffsetKernelSize(void)
{
    editSField(OffsetKernelSizeFieldMask);

    return &_sfOffsetKernelSize;
}

const SFInt32 *SSAOStageBase::getSFOffsetKernelSize(void) const
{
    return &_sfOffsetKernelSize;
}


SFInt32 *SSAOStageBase::editSFRotateKernelSize(void)
{
    editSField(RotateKernelSizeFieldMask);

    return &_sfRotateKernelSize;
}

const SFInt32 *SSAOStageBase::getSFRotateKernelSize(void) const
{
    return &_sfRotateKernelSize;
}


SFReal32 *SSAOStageBase::editSFRadius(void)
{
    editSField(RadiusFieldMask);

    return &_sfRadius;
}

const SFReal32 *SSAOStageBase::getSFRadius(void) const
{
    return &_sfRadius;
}


SFReal32 *SSAOStageBase::editSFBias(void)
{
    editSField(BiasFieldMask);

    return &_sfBias;
}

const SFReal32 *SSAOStageBase::getSFBias(void) const
{
    return &_sfBias;
}


SFInt32 *SSAOStageBase::editSFBlurKernelSize(void)
{
    editSField(BlurKernelSizeFieldMask);

    return &_sfBlurKernelSize;
}

const SFInt32 *SSAOStageBase::getSFBlurKernelSize(void) const
{
    return &_sfBlurKernelSize;
}


SFInt32 *SSAOStageBase::editSFAmbientOcclusionTexUnit(void)
{
    editSField(AmbientOcclusionTexUnitFieldMask);

    return &_sfAmbientOcclusionTexUnit;
}

const SFInt32 *SSAOStageBase::getSFAmbientOcclusionTexUnit(void) const
{
    return &_sfAmbientOcclusionTexUnit;
}


//! Get the SSAOStage::_sfOffsetKernelChunk field.
const SFUnrecUniformBufferObjStd140ChunkPtr *SSAOStageBase::getSFOffsetKernelChunk(void) const
{
    return &_sfOffsetKernelChunk;
}

SFUnrecUniformBufferObjStd140ChunkPtr *SSAOStageBase::editSFOffsetKernelChunk(void)
{
    editSField(OffsetKernelChunkFieldMask);

    return &_sfOffsetKernelChunk;
}

//! Get the value of the SSAOStage::_sfOffsetKernelChunk field.
UniformBufferObjStd140Chunk * SSAOStageBase::getOffsetKernelChunk(void) const
{
    return _sfOffsetKernelChunk.getValue();
}

//! Set the value of the SSAOStage::_sfOffsetKernelChunk field.
void SSAOStageBase::setOffsetKernelChunk(UniformBufferObjStd140Chunk * const value)
{
    editSField(OffsetKernelChunkFieldMask);

    _sfOffsetKernelChunk.setValue(value);
}


//! Get the SSAOStage::_sfRotateKernelChunk field.
const SFUnrecTextureObjChunkPtr *SSAOStageBase::getSFRotateKernelChunk(void) const
{
    return &_sfRotateKernelChunk;
}

SFUnrecTextureObjChunkPtr *SSAOStageBase::editSFRotateKernelChunk(void)
{
    editSField(RotateKernelChunkFieldMask);

    return &_sfRotateKernelChunk;
}

//! Get the value of the SSAOStage::_sfRotateKernelChunk field.
TextureObjChunk * SSAOStageBase::getRotateKernelChunk(void) const
{
    return _sfRotateKernelChunk.getValue();
}

//! Set the value of the SSAOStage::_sfRotateKernelChunk field.
void SSAOStageBase::setRotateKernelChunk(TextureObjChunk * const value)
{
    editSField(RotateKernelChunkFieldMask);

    _sfRotateKernelChunk.setValue(value);
}






/*------------------------------ access -----------------------------------*/

SizeT SSAOStageBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ActivateFieldMask & whichField))
    {
        returnValue += _sfActivate.getBinSize();
    }
    if(FieldBits::NoField != (CalcPosFromDepthFieldMask & whichField))
    {
        returnValue += _sfCalcPosFromDepth.getBinSize();
    }
    if(FieldBits::NoField != (OffsetKernelSizeFieldMask & whichField))
    {
        returnValue += _sfOffsetKernelSize.getBinSize();
    }
    if(FieldBits::NoField != (RotateKernelSizeFieldMask & whichField))
    {
        returnValue += _sfRotateKernelSize.getBinSize();
    }
    if(FieldBits::NoField != (RadiusFieldMask & whichField))
    {
        returnValue += _sfRadius.getBinSize();
    }
    if(FieldBits::NoField != (BiasFieldMask & whichField))
    {
        returnValue += _sfBias.getBinSize();
    }
    if(FieldBits::NoField != (BlurKernelSizeFieldMask & whichField))
    {
        returnValue += _sfBlurKernelSize.getBinSize();
    }
    if(FieldBits::NoField != (AmbientOcclusionTexUnitFieldMask & whichField))
    {
        returnValue += _sfAmbientOcclusionTexUnit.getBinSize();
    }
    if(FieldBits::NoField != (OffsetKernelChunkFieldMask & whichField))
    {
        returnValue += _sfOffsetKernelChunk.getBinSize();
    }
    if(FieldBits::NoField != (RotateKernelChunkFieldMask & whichField))
    {
        returnValue += _sfRotateKernelChunk.getBinSize();
    }

    return returnValue;
}

void SSAOStageBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ActivateFieldMask & whichField))
    {
        _sfActivate.copyToBin(pMem);
    }
    if(FieldBits::NoField != (CalcPosFromDepthFieldMask & whichField))
    {
        _sfCalcPosFromDepth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OffsetKernelSizeFieldMask & whichField))
    {
        _sfOffsetKernelSize.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RotateKernelSizeFieldMask & whichField))
    {
        _sfRotateKernelSize.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RadiusFieldMask & whichField))
    {
        _sfRadius.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BiasFieldMask & whichField))
    {
        _sfBias.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BlurKernelSizeFieldMask & whichField))
    {
        _sfBlurKernelSize.copyToBin(pMem);
    }
    if(FieldBits::NoField != (AmbientOcclusionTexUnitFieldMask & whichField))
    {
        _sfAmbientOcclusionTexUnit.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OffsetKernelChunkFieldMask & whichField))
    {
        _sfOffsetKernelChunk.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RotateKernelChunkFieldMask & whichField))
    {
        _sfRotateKernelChunk.copyToBin(pMem);
    }
}

void SSAOStageBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ActivateFieldMask & whichField))
    {
        editSField(ActivateFieldMask);
        _sfActivate.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (CalcPosFromDepthFieldMask & whichField))
    {
        editSField(CalcPosFromDepthFieldMask);
        _sfCalcPosFromDepth.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OffsetKernelSizeFieldMask & whichField))
    {
        editSField(OffsetKernelSizeFieldMask);
        _sfOffsetKernelSize.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RotateKernelSizeFieldMask & whichField))
    {
        editSField(RotateKernelSizeFieldMask);
        _sfRotateKernelSize.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RadiusFieldMask & whichField))
    {
        editSField(RadiusFieldMask);
        _sfRadius.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BiasFieldMask & whichField))
    {
        editSField(BiasFieldMask);
        _sfBias.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BlurKernelSizeFieldMask & whichField))
    {
        editSField(BlurKernelSizeFieldMask);
        _sfBlurKernelSize.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (AmbientOcclusionTexUnitFieldMask & whichField))
    {
        editSField(AmbientOcclusionTexUnitFieldMask);
        _sfAmbientOcclusionTexUnit.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OffsetKernelChunkFieldMask & whichField))
    {
        editSField(OffsetKernelChunkFieldMask);
        _sfOffsetKernelChunk.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RotateKernelChunkFieldMask & whichField))
    {
        editSField(RotateKernelChunkFieldMask);
        _sfRotateKernelChunk.copyFromBin(pMem);
    }
}

//! create a new instance of the class
SSAOStageTransitPtr SSAOStageBase::createLocal(BitVector bFlags)
{
    SSAOStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<SSAOStage>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
SSAOStageTransitPtr SSAOStageBase::createDependent(BitVector bFlags)
{
    SSAOStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<SSAOStage>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
SSAOStageTransitPtr SSAOStageBase::create(void)
{
    SSAOStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<SSAOStage>(tmpPtr);
    }

    return fc;
}

SSAOStage *SSAOStageBase::createEmptyLocal(BitVector bFlags)
{
    SSAOStage *returnValue;

    newPtr<SSAOStage>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
SSAOStage *SSAOStageBase::createEmpty(void)
{
    SSAOStage *returnValue;

    newPtr<SSAOStage>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr SSAOStageBase::shallowCopyLocal(
    BitVector bFlags) const
{
    SSAOStage *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const SSAOStage *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr SSAOStageBase::shallowCopyDependent(
    BitVector bFlags) const
{
    SSAOStage *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const SSAOStage *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr SSAOStageBase::shallowCopy(void) const
{
    SSAOStage *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const SSAOStage *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

SSAOStageBase::SSAOStageBase(void) :
    Inherited(),
    _sfActivate               (bool(true)),
    _sfCalcPosFromDepth       (bool(true)),
    _sfOffsetKernelSize       (Int32(64)),
    _sfRotateKernelSize       (Int32(4)),
    _sfRadius                 (Real32(0.5)),
    _sfBias                   (Real32(0.025)),
    _sfBlurKernelSize         (Int32(4)),
    _sfAmbientOcclusionTexUnit(Int32(16)),
    _sfOffsetKernelChunk      (NULL),
    _sfRotateKernelChunk      (NULL)
{
}

SSAOStageBase::SSAOStageBase(const SSAOStageBase &source) :
    Inherited(source),
    _sfActivate               (source._sfActivate               ),
    _sfCalcPosFromDepth       (source._sfCalcPosFromDepth       ),
    _sfOffsetKernelSize       (source._sfOffsetKernelSize       ),
    _sfRotateKernelSize       (source._sfRotateKernelSize       ),
    _sfRadius                 (source._sfRadius                 ),
    _sfBias                   (source._sfBias                   ),
    _sfBlurKernelSize         (source._sfBlurKernelSize         ),
    _sfAmbientOcclusionTexUnit(source._sfAmbientOcclusionTexUnit),
    _sfOffsetKernelChunk      (NULL),
    _sfRotateKernelChunk      (NULL)
{
}


/*-------------------------- destructors ----------------------------------*/

SSAOStageBase::~SSAOStageBase(void)
{
}

void SSAOStageBase::onCreate(const SSAOStage *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        SSAOStage *pThis = static_cast<SSAOStage *>(this);

        pThis->setOffsetKernelChunk(source->getOffsetKernelChunk());

        pThis->setRotateKernelChunk(source->getRotateKernelChunk());
    }
}

GetFieldHandlePtr SSAOStageBase::getHandleActivate        (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfActivate,
             this->getType().getFieldDesc(ActivateFieldId),
             const_cast<SSAOStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SSAOStageBase::editHandleActivate       (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfActivate,
             this->getType().getFieldDesc(ActivateFieldId),
             this));


    editSField(ActivateFieldMask);

    return returnValue;
}

GetFieldHandlePtr SSAOStageBase::getHandleCalcPosFromDepth (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfCalcPosFromDepth,
             this->getType().getFieldDesc(CalcPosFromDepthFieldId),
             const_cast<SSAOStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SSAOStageBase::editHandleCalcPosFromDepth(void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfCalcPosFromDepth,
             this->getType().getFieldDesc(CalcPosFromDepthFieldId),
             this));


    editSField(CalcPosFromDepthFieldMask);

    return returnValue;
}

GetFieldHandlePtr SSAOStageBase::getHandleOffsetKernelSize (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfOffsetKernelSize,
             this->getType().getFieldDesc(OffsetKernelSizeFieldId),
             const_cast<SSAOStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SSAOStageBase::editHandleOffsetKernelSize(void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfOffsetKernelSize,
             this->getType().getFieldDesc(OffsetKernelSizeFieldId),
             this));


    editSField(OffsetKernelSizeFieldMask);

    return returnValue;
}

GetFieldHandlePtr SSAOStageBase::getHandleRotateKernelSize (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfRotateKernelSize,
             this->getType().getFieldDesc(RotateKernelSizeFieldId),
             const_cast<SSAOStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SSAOStageBase::editHandleRotateKernelSize(void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfRotateKernelSize,
             this->getType().getFieldDesc(RotateKernelSizeFieldId),
             this));


    editSField(RotateKernelSizeFieldMask);

    return returnValue;
}

GetFieldHandlePtr SSAOStageBase::getHandleRadius          (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfRadius,
             this->getType().getFieldDesc(RadiusFieldId),
             const_cast<SSAOStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SSAOStageBase::editHandleRadius         (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfRadius,
             this->getType().getFieldDesc(RadiusFieldId),
             this));


    editSField(RadiusFieldMask);

    return returnValue;
}

GetFieldHandlePtr SSAOStageBase::getHandleBias            (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfBias,
             this->getType().getFieldDesc(BiasFieldId),
             const_cast<SSAOStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SSAOStageBase::editHandleBias           (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfBias,
             this->getType().getFieldDesc(BiasFieldId),
             this));


    editSField(BiasFieldMask);

    return returnValue;
}

GetFieldHandlePtr SSAOStageBase::getHandleBlurKernelSize  (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfBlurKernelSize,
             this->getType().getFieldDesc(BlurKernelSizeFieldId),
             const_cast<SSAOStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SSAOStageBase::editHandleBlurKernelSize (void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfBlurKernelSize,
             this->getType().getFieldDesc(BlurKernelSizeFieldId),
             this));


    editSField(BlurKernelSizeFieldMask);

    return returnValue;
}

GetFieldHandlePtr SSAOStageBase::getHandleAmbientOcclusionTexUnit (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfAmbientOcclusionTexUnit,
             this->getType().getFieldDesc(AmbientOcclusionTexUnitFieldId),
             const_cast<SSAOStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SSAOStageBase::editHandleAmbientOcclusionTexUnit(void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfAmbientOcclusionTexUnit,
             this->getType().getFieldDesc(AmbientOcclusionTexUnitFieldId),
             this));


    editSField(AmbientOcclusionTexUnitFieldMask);

    return returnValue;
}

GetFieldHandlePtr SSAOStageBase::getHandleOffsetKernelChunk (void) const
{
    SFUnrecUniformBufferObjStd140ChunkPtr::GetHandlePtr returnValue(
        new  SFUnrecUniformBufferObjStd140ChunkPtr::GetHandle(
             &_sfOffsetKernelChunk,
             this->getType().getFieldDesc(OffsetKernelChunkFieldId),
             const_cast<SSAOStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SSAOStageBase::editHandleOffsetKernelChunk(void)
{
    SFUnrecUniformBufferObjStd140ChunkPtr::EditHandlePtr returnValue(
        new  SFUnrecUniformBufferObjStd140ChunkPtr::EditHandle(
             &_sfOffsetKernelChunk,
             this->getType().getFieldDesc(OffsetKernelChunkFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&SSAOStage::setOffsetKernelChunk,
                    static_cast<SSAOStage *>(this), ::boost::placeholders::_1));

    editSField(OffsetKernelChunkFieldMask);

    return returnValue;
}

GetFieldHandlePtr SSAOStageBase::getHandleRotateKernelChunk (void) const
{
    SFUnrecTextureObjChunkPtr::GetHandlePtr returnValue(
        new  SFUnrecTextureObjChunkPtr::GetHandle(
             &_sfRotateKernelChunk,
             this->getType().getFieldDesc(RotateKernelChunkFieldId),
             const_cast<SSAOStageBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr SSAOStageBase::editHandleRotateKernelChunk(void)
{
    SFUnrecTextureObjChunkPtr::EditHandlePtr returnValue(
        new  SFUnrecTextureObjChunkPtr::EditHandle(
             &_sfRotateKernelChunk,
             this->getType().getFieldDesc(RotateKernelChunkFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&SSAOStage::setRotateKernelChunk,
                    static_cast<SSAOStage *>(this), ::boost::placeholders::_1));

    editSField(RotateKernelChunkFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void SSAOStageBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    SSAOStage *pThis = static_cast<SSAOStage *>(this);

    pThis->execSync(static_cast<SSAOStage *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *SSAOStageBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    SSAOStage *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const SSAOStage *>(pRefAspect),
                  dynamic_cast<const SSAOStage *>(this));

    return returnValue;
}
#endif

void SSAOStageBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<SSAOStage *>(this)->setOffsetKernelChunk(NULL);

    static_cast<SSAOStage *>(this)->setRotateKernelChunk(NULL);


}


OSG_END_NAMESPACE
