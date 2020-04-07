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
 **     class ShaderCodeGenerator!
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



#include "OSGCapabilitiesDesc.h"        // CapabilitiesDesc Class
#include "OSGHDR2Stage.h"               // HDR2Stage Class
#include "OSGClusterShadingStage.h"     // ClusterShadingStage Class
#include "OSGMultiLightShadowStage.h"   // MultiLightShadowStage Class
#include "OSGSSAOStage.h"               // SSAOStage Class
#include "OSGIBLStage.h"                // IBLStage Class
#include "OSGMultiLightGroup.h"         // MultiLightGroup Class

#include "OSGShaderCodeGeneratorBase.h"
#include "OSGShaderCodeGenerator.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ShaderCodeGenerator
    A concrete shader generator is responsible for generating
    the shader program text from the given ShaderDesc description
    instance. It might uses the provided stages and chunks for
    detailing the program text.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var CapabilitiesDesc * ShaderCodeGeneratorBase::_sfCapabilitiesDesc
    The capabilities that are used for code generation.
*/

/*! \var HDR2Stage *     ShaderCodeGeneratorBase::_sfHDR2Stage
    
*/

/*! \var ClusterShadingStage * ShaderCodeGeneratorBase::_sfClusterShadingStage
    
*/

/*! \var MultiLightShadowStage * ShaderCodeGeneratorBase::_sfMultiLightShadowStage
    
*/

/*! \var SSAOStage *     ShaderCodeGeneratorBase::_sfSSAOStage
    
*/

/*! \var IBLStage *      ShaderCodeGeneratorBase::_sfIBLStage
    
*/

/*! \var MultiLightGroup * ShaderCodeGeneratorBase::_sfMultiLightGroup
    
*/

/*! \var UInt32          ShaderCodeGeneratorBase::_sfLightBindingPnt
    The fragment shader SSBO binding point for the multi light chunk.
*/

/*! \var bool            ShaderCodeGeneratorBase::_sfHasClipPlanes
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<ShaderCodeGenerator *, nsOSG>::_type(
    "ShaderCodeGeneratorPtr", 
    "FieldContainerPtr", 
    ShaderCodeGenerator::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(ShaderCodeGenerator *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ShaderCodeGenerator *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ShaderCodeGenerator *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ShaderCodeGeneratorBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecCapabilitiesDescPtr::Description(
        SFUnrecCapabilitiesDescPtr::getClassType(),
        "CapabilitiesDesc",
        "The capabilities that are used for code generation.\n",
        CapabilitiesDescFieldId, CapabilitiesDescFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderCodeGenerator::editHandleCapabilitiesDesc),
        static_cast<FieldGetMethodSig >(&ShaderCodeGenerator::getHandleCapabilitiesDesc));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecHDR2StagePtr::Description(
        SFUnrecHDR2StagePtr::getClassType(),
        "HDR2Stage",
        "",
        HDR2StageFieldId, HDR2StageFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderCodeGenerator::editHandleHDR2Stage),
        static_cast<FieldGetMethodSig >(&ShaderCodeGenerator::getHandleHDR2Stage));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecClusterShadingStagePtr::Description(
        SFUnrecClusterShadingStagePtr::getClassType(),
        "clusterShadingStage",
        "",
        ClusterShadingStageFieldId, ClusterShadingStageFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderCodeGenerator::editHandleClusterShadingStage),
        static_cast<FieldGetMethodSig >(&ShaderCodeGenerator::getHandleClusterShadingStage));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecMultiLightShadowStagePtr::Description(
        SFUnrecMultiLightShadowStagePtr::getClassType(),
        "multiLightShadowStage",
        "",
        MultiLightShadowStageFieldId, MultiLightShadowStageFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderCodeGenerator::editHandleMultiLightShadowStage),
        static_cast<FieldGetMethodSig >(&ShaderCodeGenerator::getHandleMultiLightShadowStage));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecSSAOStagePtr::Description(
        SFUnrecSSAOStagePtr::getClassType(),
        "SSAOStage",
        "",
        SSAOStageFieldId, SSAOStageFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderCodeGenerator::editHandleSSAOStage),
        static_cast<FieldGetMethodSig >(&ShaderCodeGenerator::getHandleSSAOStage));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecIBLStagePtr::Description(
        SFUnrecIBLStagePtr::getClassType(),
        "IBLStage",
        "",
        IBLStageFieldId, IBLStageFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderCodeGenerator::editHandleIBLStage),
        static_cast<FieldGetMethodSig >(&ShaderCodeGenerator::getHandleIBLStage));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecMultiLightGroupPtr::Description(
        SFUnrecMultiLightGroupPtr::getClassType(),
        "multiLightGroup",
        "",
        MultiLightGroupFieldId, MultiLightGroupFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderCodeGenerator::editHandleMultiLightGroup),
        static_cast<FieldGetMethodSig >(&ShaderCodeGenerator::getHandleMultiLightGroup));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "lightBindingPnt",
        "The fragment shader SSBO binding point for the multi light chunk.\n",
        LightBindingPntFieldId, LightBindingPntFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderCodeGenerator::editHandleLightBindingPnt),
        static_cast<FieldGetMethodSig >(&ShaderCodeGenerator::getHandleLightBindingPnt));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "hasClipPlanes",
        "",
        HasClipPlanesFieldId, HasClipPlanesFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderCodeGenerator::editHandleHasClipPlanes),
        static_cast<FieldGetMethodSig >(&ShaderCodeGenerator::getHandleHasClipPlanes));

    oType.addInitialDesc(pDesc);
}


ShaderCodeGeneratorBase::TypeObject ShaderCodeGeneratorBase::_type(
    ShaderCodeGeneratorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    NULL,
    reinterpret_cast<InitContainerF>(&ShaderCodeGenerator::initMethod),
    reinterpret_cast<ExitContainerF>(&ShaderCodeGenerator::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&ShaderCodeGenerator::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"ShaderCodeGenerator\"\n"
    "    parent=\"FieldContainer\"\n"
    "    library=\"ContribTechniques\"\n"
    "    structure=\"abstract\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    >\n"
    "    A concrete shader generator is responsible for generating\n"
    "    the shader program text from the given ShaderDesc description\n"
    "    instance. It might uses the provided stages and chunks for\n"
    "    detailing the program text.\n"
    "\n"
    "    <Field\n"
    "        name=\"CapabilitiesDesc\"\n"
    "        type=\"CapabilitiesDescPtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "        The capabilities that are used for code generation.\n"
    "    </Field>\n"
    "     <Field\n"
    "        name=\"HDR2Stage\"\n"
    "        type=\"HDR2StagePtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"clusterShadingStage\"\n"
    "        type=\"ClusterShadingStagePtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"multiLightShadowStage\"\n"
    "        type=\"MultiLightShadowStagePtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"SSAOStage\"\n"
    "        type=\"SSAOStagePtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"IBLStage\"\n"
    "        type=\"IBLStagePtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"multiLightGroup\"\n"
    "        type=\"MultiLightGroupPtr\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"NULL\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"lightBindingPnt\"\n"
    "        type=\"UInt32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"1\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "        The fragment shader SSBO binding point for the multi light chunk.\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"hasClipPlanes\"\n"
    "        type=\"bool\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"false\"\n"
    "        >\n"
    "    </Field>\n"
    "</FieldContainer>\n",
    "A concrete shader generator is responsible for generating\n"
    "the shader program text from the given ShaderDesc description\n"
    "instance. It might uses the provided stages and chunks for\n"
    "detailing the program text.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ShaderCodeGeneratorBase::getType(void)
{
    return _type;
}

const FieldContainerType &ShaderCodeGeneratorBase::getType(void) const
{
    return _type;
}

UInt32 ShaderCodeGeneratorBase::getContainerSize(void) const
{
    return sizeof(ShaderCodeGenerator);
}

/*------------------------- decorator get ------------------------------*/


//! Get the ShaderCodeGenerator::_sfCapabilitiesDesc field.
const SFUnrecCapabilitiesDescPtr *ShaderCodeGeneratorBase::getSFCapabilitiesDesc(void) const
{
    return &_sfCapabilitiesDesc;
}

SFUnrecCapabilitiesDescPtr *ShaderCodeGeneratorBase::editSFCapabilitiesDesc(void)
{
    editSField(CapabilitiesDescFieldMask);

    return &_sfCapabilitiesDesc;
}

//! Get the value of the ShaderCodeGenerator::_sfCapabilitiesDesc field.
CapabilitiesDesc * ShaderCodeGeneratorBase::getCapabilitiesDesc(void) const
{
    return _sfCapabilitiesDesc.getValue();
}

//! Set the value of the ShaderCodeGenerator::_sfCapabilitiesDesc field.
void ShaderCodeGeneratorBase::setCapabilitiesDesc(CapabilitiesDesc * const value)
{
    editSField(CapabilitiesDescFieldMask);

    _sfCapabilitiesDesc.setValue(value);
}


//! Get the ShaderCodeGenerator::_sfHDR2Stage field.
const SFUnrecHDR2StagePtr *ShaderCodeGeneratorBase::getSFHDR2Stage(void) const
{
    return &_sfHDR2Stage;
}

SFUnrecHDR2StagePtr *ShaderCodeGeneratorBase::editSFHDR2Stage      (void)
{
    editSField(HDR2StageFieldMask);

    return &_sfHDR2Stage;
}

//! Get the value of the ShaderCodeGenerator::_sfHDR2Stage field.
HDR2Stage * ShaderCodeGeneratorBase::getHDR2Stage(void) const
{
    return _sfHDR2Stage.getValue();
}

//! Set the value of the ShaderCodeGenerator::_sfHDR2Stage field.
void ShaderCodeGeneratorBase::setHDR2Stage(HDR2Stage * const value)
{
    editSField(HDR2StageFieldMask);

    _sfHDR2Stage.setValue(value);
}


//! Get the ShaderCodeGenerator::_sfClusterShadingStage field.
const SFUnrecClusterShadingStagePtr *ShaderCodeGeneratorBase::getSFClusterShadingStage(void) const
{
    return &_sfClusterShadingStage;
}

SFUnrecClusterShadingStagePtr *ShaderCodeGeneratorBase::editSFClusterShadingStage(void)
{
    editSField(ClusterShadingStageFieldMask);

    return &_sfClusterShadingStage;
}

//! Get the value of the ShaderCodeGenerator::_sfClusterShadingStage field.
ClusterShadingStage * ShaderCodeGeneratorBase::getClusterShadingStage(void) const
{
    return _sfClusterShadingStage.getValue();
}

//! Set the value of the ShaderCodeGenerator::_sfClusterShadingStage field.
void ShaderCodeGeneratorBase::setClusterShadingStage(ClusterShadingStage * const value)
{
    editSField(ClusterShadingStageFieldMask);

    _sfClusterShadingStage.setValue(value);
}


//! Get the ShaderCodeGenerator::_sfMultiLightShadowStage field.
const SFUnrecMultiLightShadowStagePtr *ShaderCodeGeneratorBase::getSFMultiLightShadowStage(void) const
{
    return &_sfMultiLightShadowStage;
}

SFUnrecMultiLightShadowStagePtr *ShaderCodeGeneratorBase::editSFMultiLightShadowStage(void)
{
    editSField(MultiLightShadowStageFieldMask);

    return &_sfMultiLightShadowStage;
}

//! Get the value of the ShaderCodeGenerator::_sfMultiLightShadowStage field.
MultiLightShadowStage * ShaderCodeGeneratorBase::getMultiLightShadowStage(void) const
{
    return _sfMultiLightShadowStage.getValue();
}

//! Set the value of the ShaderCodeGenerator::_sfMultiLightShadowStage field.
void ShaderCodeGeneratorBase::setMultiLightShadowStage(MultiLightShadowStage * const value)
{
    editSField(MultiLightShadowStageFieldMask);

    _sfMultiLightShadowStage.setValue(value);
}


//! Get the ShaderCodeGenerator::_sfSSAOStage field.
const SFUnrecSSAOStagePtr *ShaderCodeGeneratorBase::getSFSSAOStage(void) const
{
    return &_sfSSAOStage;
}

SFUnrecSSAOStagePtr *ShaderCodeGeneratorBase::editSFSSAOStage      (void)
{
    editSField(SSAOStageFieldMask);

    return &_sfSSAOStage;
}

//! Get the value of the ShaderCodeGenerator::_sfSSAOStage field.
SSAOStage * ShaderCodeGeneratorBase::getSSAOStage(void) const
{
    return _sfSSAOStage.getValue();
}

//! Set the value of the ShaderCodeGenerator::_sfSSAOStage field.
void ShaderCodeGeneratorBase::setSSAOStage(SSAOStage * const value)
{
    editSField(SSAOStageFieldMask);

    _sfSSAOStage.setValue(value);
}


//! Get the ShaderCodeGenerator::_sfIBLStage field.
const SFUnrecIBLStagePtr *ShaderCodeGeneratorBase::getSFIBLStage(void) const
{
    return &_sfIBLStage;
}

SFUnrecIBLStagePtr  *ShaderCodeGeneratorBase::editSFIBLStage       (void)
{
    editSField(IBLStageFieldMask);

    return &_sfIBLStage;
}

//! Get the value of the ShaderCodeGenerator::_sfIBLStage field.
IBLStage * ShaderCodeGeneratorBase::getIBLStage(void) const
{
    return _sfIBLStage.getValue();
}

//! Set the value of the ShaderCodeGenerator::_sfIBLStage field.
void ShaderCodeGeneratorBase::setIBLStage(IBLStage * const value)
{
    editSField(IBLStageFieldMask);

    _sfIBLStage.setValue(value);
}


//! Get the ShaderCodeGenerator::_sfMultiLightGroup field.
const SFUnrecMultiLightGroupPtr *ShaderCodeGeneratorBase::getSFMultiLightGroup(void) const
{
    return &_sfMultiLightGroup;
}

SFUnrecMultiLightGroupPtr *ShaderCodeGeneratorBase::editSFMultiLightGroup(void)
{
    editSField(MultiLightGroupFieldMask);

    return &_sfMultiLightGroup;
}

//! Get the value of the ShaderCodeGenerator::_sfMultiLightGroup field.
MultiLightGroup * ShaderCodeGeneratorBase::getMultiLightGroup(void) const
{
    return _sfMultiLightGroup.getValue();
}

//! Set the value of the ShaderCodeGenerator::_sfMultiLightGroup field.
void ShaderCodeGeneratorBase::setMultiLightGroup(MultiLightGroup * const value)
{
    editSField(MultiLightGroupFieldMask);

    _sfMultiLightGroup.setValue(value);
}


SFUInt32 *ShaderCodeGeneratorBase::editSFLightBindingPnt(void)
{
    editSField(LightBindingPntFieldMask);

    return &_sfLightBindingPnt;
}

const SFUInt32 *ShaderCodeGeneratorBase::getSFLightBindingPnt(void) const
{
    return &_sfLightBindingPnt;
}


SFBool *ShaderCodeGeneratorBase::editSFHasClipPlanes(void)
{
    editSField(HasClipPlanesFieldMask);

    return &_sfHasClipPlanes;
}

const SFBool *ShaderCodeGeneratorBase::getSFHasClipPlanes(void) const
{
    return &_sfHasClipPlanes;
}






/*------------------------------ access -----------------------------------*/

SizeT ShaderCodeGeneratorBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (CapabilitiesDescFieldMask & whichField))
    {
        returnValue += _sfCapabilitiesDesc.getBinSize();
    }
    if(FieldBits::NoField != (HDR2StageFieldMask & whichField))
    {
        returnValue += _sfHDR2Stage.getBinSize();
    }
    if(FieldBits::NoField != (ClusterShadingStageFieldMask & whichField))
    {
        returnValue += _sfClusterShadingStage.getBinSize();
    }
    if(FieldBits::NoField != (MultiLightShadowStageFieldMask & whichField))
    {
        returnValue += _sfMultiLightShadowStage.getBinSize();
    }
    if(FieldBits::NoField != (SSAOStageFieldMask & whichField))
    {
        returnValue += _sfSSAOStage.getBinSize();
    }
    if(FieldBits::NoField != (IBLStageFieldMask & whichField))
    {
        returnValue += _sfIBLStage.getBinSize();
    }
    if(FieldBits::NoField != (MultiLightGroupFieldMask & whichField))
    {
        returnValue += _sfMultiLightGroup.getBinSize();
    }
    if(FieldBits::NoField != (LightBindingPntFieldMask & whichField))
    {
        returnValue += _sfLightBindingPnt.getBinSize();
    }
    if(FieldBits::NoField != (HasClipPlanesFieldMask & whichField))
    {
        returnValue += _sfHasClipPlanes.getBinSize();
    }

    return returnValue;
}

void ShaderCodeGeneratorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (CapabilitiesDescFieldMask & whichField))
    {
        _sfCapabilitiesDesc.copyToBin(pMem);
    }
    if(FieldBits::NoField != (HDR2StageFieldMask & whichField))
    {
        _sfHDR2Stage.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ClusterShadingStageFieldMask & whichField))
    {
        _sfClusterShadingStage.copyToBin(pMem);
    }
    if(FieldBits::NoField != (MultiLightShadowStageFieldMask & whichField))
    {
        _sfMultiLightShadowStage.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SSAOStageFieldMask & whichField))
    {
        _sfSSAOStage.copyToBin(pMem);
    }
    if(FieldBits::NoField != (IBLStageFieldMask & whichField))
    {
        _sfIBLStage.copyToBin(pMem);
    }
    if(FieldBits::NoField != (MultiLightGroupFieldMask & whichField))
    {
        _sfMultiLightGroup.copyToBin(pMem);
    }
    if(FieldBits::NoField != (LightBindingPntFieldMask & whichField))
    {
        _sfLightBindingPnt.copyToBin(pMem);
    }
    if(FieldBits::NoField != (HasClipPlanesFieldMask & whichField))
    {
        _sfHasClipPlanes.copyToBin(pMem);
    }
}

void ShaderCodeGeneratorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (CapabilitiesDescFieldMask & whichField))
    {
        editSField(CapabilitiesDescFieldMask);
        _sfCapabilitiesDesc.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (HDR2StageFieldMask & whichField))
    {
        editSField(HDR2StageFieldMask);
        _sfHDR2Stage.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ClusterShadingStageFieldMask & whichField))
    {
        editSField(ClusterShadingStageFieldMask);
        _sfClusterShadingStage.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (MultiLightShadowStageFieldMask & whichField))
    {
        editSField(MultiLightShadowStageFieldMask);
        _sfMultiLightShadowStage.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SSAOStageFieldMask & whichField))
    {
        editSField(SSAOStageFieldMask);
        _sfSSAOStage.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (IBLStageFieldMask & whichField))
    {
        editSField(IBLStageFieldMask);
        _sfIBLStage.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (MultiLightGroupFieldMask & whichField))
    {
        editSField(MultiLightGroupFieldMask);
        _sfMultiLightGroup.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (LightBindingPntFieldMask & whichField))
    {
        editSField(LightBindingPntFieldMask);
        _sfLightBindingPnt.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (HasClipPlanesFieldMask & whichField))
    {
        editSField(HasClipPlanesFieldMask);
        _sfHasClipPlanes.copyFromBin(pMem);
    }
}




/*------------------------- constructors ----------------------------------*/

ShaderCodeGeneratorBase::ShaderCodeGeneratorBase(void) :
    Inherited(),
    _sfCapabilitiesDesc       (NULL),
    _sfHDR2Stage              (NULL),
    _sfClusterShadingStage    (NULL),
    _sfMultiLightShadowStage  (NULL),
    _sfSSAOStage              (NULL),
    _sfIBLStage               (NULL),
    _sfMultiLightGroup        (NULL),
    _sfLightBindingPnt        (UInt32(1)),
    _sfHasClipPlanes          (bool(false))
{
}

ShaderCodeGeneratorBase::ShaderCodeGeneratorBase(const ShaderCodeGeneratorBase &source) :
    Inherited(source),
    _sfCapabilitiesDesc       (NULL),
    _sfHDR2Stage              (NULL),
    _sfClusterShadingStage    (NULL),
    _sfMultiLightShadowStage  (NULL),
    _sfSSAOStage              (NULL),
    _sfIBLStage               (NULL),
    _sfMultiLightGroup        (NULL),
    _sfLightBindingPnt        (source._sfLightBindingPnt        ),
    _sfHasClipPlanes          (source._sfHasClipPlanes          )
{
}


/*-------------------------- destructors ----------------------------------*/

ShaderCodeGeneratorBase::~ShaderCodeGeneratorBase(void)
{
}

void ShaderCodeGeneratorBase::onCreate(const ShaderCodeGenerator *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        ShaderCodeGenerator *pThis = static_cast<ShaderCodeGenerator *>(this);

        pThis->setCapabilitiesDesc(source->getCapabilitiesDesc());

        pThis->setHDR2Stage(source->getHDR2Stage());

        pThis->setClusterShadingStage(source->getClusterShadingStage());

        pThis->setMultiLightShadowStage(source->getMultiLightShadowStage());

        pThis->setSSAOStage(source->getSSAOStage());

        pThis->setIBLStage(source->getIBLStage());

        pThis->setMultiLightGroup(source->getMultiLightGroup());
    }
}

GetFieldHandlePtr ShaderCodeGeneratorBase::getHandleCapabilitiesDesc (void) const
{
    SFUnrecCapabilitiesDescPtr::GetHandlePtr returnValue(
        new  SFUnrecCapabilitiesDescPtr::GetHandle(
             &_sfCapabilitiesDesc,
             this->getType().getFieldDesc(CapabilitiesDescFieldId),
             const_cast<ShaderCodeGeneratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderCodeGeneratorBase::editHandleCapabilitiesDesc(void)
{
    SFUnrecCapabilitiesDescPtr::EditHandlePtr returnValue(
        new  SFUnrecCapabilitiesDescPtr::EditHandle(
             &_sfCapabilitiesDesc,
             this->getType().getFieldDesc(CapabilitiesDescFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShaderCodeGenerator::setCapabilitiesDesc,
                    static_cast<ShaderCodeGenerator *>(this), _1));

    editSField(CapabilitiesDescFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderCodeGeneratorBase::getHandleHDR2Stage       (void) const
{
    SFUnrecHDR2StagePtr::GetHandlePtr returnValue(
        new  SFUnrecHDR2StagePtr::GetHandle(
             &_sfHDR2Stage,
             this->getType().getFieldDesc(HDR2StageFieldId),
             const_cast<ShaderCodeGeneratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderCodeGeneratorBase::editHandleHDR2Stage      (void)
{
    SFUnrecHDR2StagePtr::EditHandlePtr returnValue(
        new  SFUnrecHDR2StagePtr::EditHandle(
             &_sfHDR2Stage,
             this->getType().getFieldDesc(HDR2StageFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShaderCodeGenerator::setHDR2Stage,
                    static_cast<ShaderCodeGenerator *>(this), _1));

    editSField(HDR2StageFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderCodeGeneratorBase::getHandleClusterShadingStage (void) const
{
    SFUnrecClusterShadingStagePtr::GetHandlePtr returnValue(
        new  SFUnrecClusterShadingStagePtr::GetHandle(
             &_sfClusterShadingStage,
             this->getType().getFieldDesc(ClusterShadingStageFieldId),
             const_cast<ShaderCodeGeneratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderCodeGeneratorBase::editHandleClusterShadingStage(void)
{
    SFUnrecClusterShadingStagePtr::EditHandlePtr returnValue(
        new  SFUnrecClusterShadingStagePtr::EditHandle(
             &_sfClusterShadingStage,
             this->getType().getFieldDesc(ClusterShadingStageFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShaderCodeGenerator::setClusterShadingStage,
                    static_cast<ShaderCodeGenerator *>(this), _1));

    editSField(ClusterShadingStageFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderCodeGeneratorBase::getHandleMultiLightShadowStage (void) const
{
    SFUnrecMultiLightShadowStagePtr::GetHandlePtr returnValue(
        new  SFUnrecMultiLightShadowStagePtr::GetHandle(
             &_sfMultiLightShadowStage,
             this->getType().getFieldDesc(MultiLightShadowStageFieldId),
             const_cast<ShaderCodeGeneratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderCodeGeneratorBase::editHandleMultiLightShadowStage(void)
{
    SFUnrecMultiLightShadowStagePtr::EditHandlePtr returnValue(
        new  SFUnrecMultiLightShadowStagePtr::EditHandle(
             &_sfMultiLightShadowStage,
             this->getType().getFieldDesc(MultiLightShadowStageFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShaderCodeGenerator::setMultiLightShadowStage,
                    static_cast<ShaderCodeGenerator *>(this), _1));

    editSField(MultiLightShadowStageFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderCodeGeneratorBase::getHandleSSAOStage       (void) const
{
    SFUnrecSSAOStagePtr::GetHandlePtr returnValue(
        new  SFUnrecSSAOStagePtr::GetHandle(
             &_sfSSAOStage,
             this->getType().getFieldDesc(SSAOStageFieldId),
             const_cast<ShaderCodeGeneratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderCodeGeneratorBase::editHandleSSAOStage      (void)
{
    SFUnrecSSAOStagePtr::EditHandlePtr returnValue(
        new  SFUnrecSSAOStagePtr::EditHandle(
             &_sfSSAOStage,
             this->getType().getFieldDesc(SSAOStageFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShaderCodeGenerator::setSSAOStage,
                    static_cast<ShaderCodeGenerator *>(this), _1));

    editSField(SSAOStageFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderCodeGeneratorBase::getHandleIBLStage        (void) const
{
    SFUnrecIBLStagePtr::GetHandlePtr returnValue(
        new  SFUnrecIBLStagePtr::GetHandle(
             &_sfIBLStage,
             this->getType().getFieldDesc(IBLStageFieldId),
             const_cast<ShaderCodeGeneratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderCodeGeneratorBase::editHandleIBLStage       (void)
{
    SFUnrecIBLStagePtr::EditHandlePtr returnValue(
        new  SFUnrecIBLStagePtr::EditHandle(
             &_sfIBLStage,
             this->getType().getFieldDesc(IBLStageFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShaderCodeGenerator::setIBLStage,
                    static_cast<ShaderCodeGenerator *>(this), _1));

    editSField(IBLStageFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderCodeGeneratorBase::getHandleMultiLightGroup (void) const
{
    SFUnrecMultiLightGroupPtr::GetHandlePtr returnValue(
        new  SFUnrecMultiLightGroupPtr::GetHandle(
             &_sfMultiLightGroup,
             this->getType().getFieldDesc(MultiLightGroupFieldId),
             const_cast<ShaderCodeGeneratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderCodeGeneratorBase::editHandleMultiLightGroup(void)
{
    SFUnrecMultiLightGroupPtr::EditHandlePtr returnValue(
        new  SFUnrecMultiLightGroupPtr::EditHandle(
             &_sfMultiLightGroup,
             this->getType().getFieldDesc(MultiLightGroupFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShaderCodeGenerator::setMultiLightGroup,
                    static_cast<ShaderCodeGenerator *>(this), _1));

    editSField(MultiLightGroupFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderCodeGeneratorBase::getHandleLightBindingPnt (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfLightBindingPnt,
             this->getType().getFieldDesc(LightBindingPntFieldId),
             const_cast<ShaderCodeGeneratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderCodeGeneratorBase::editHandleLightBindingPnt(void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfLightBindingPnt,
             this->getType().getFieldDesc(LightBindingPntFieldId),
             this));


    editSField(LightBindingPntFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderCodeGeneratorBase::getHandleHasClipPlanes   (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfHasClipPlanes,
             this->getType().getFieldDesc(HasClipPlanesFieldId),
             const_cast<ShaderCodeGeneratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderCodeGeneratorBase::editHandleHasClipPlanes  (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfHasClipPlanes,
             this->getType().getFieldDesc(HasClipPlanesFieldId),
             this));


    editSField(HasClipPlanesFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ShaderCodeGeneratorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ShaderCodeGenerator *pThis = static_cast<ShaderCodeGenerator *>(this);

    pThis->execSync(static_cast<ShaderCodeGenerator *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void ShaderCodeGeneratorBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<ShaderCodeGenerator *>(this)->setCapabilitiesDesc(NULL);

    static_cast<ShaderCodeGenerator *>(this)->setHDR2Stage(NULL);

    static_cast<ShaderCodeGenerator *>(this)->setClusterShadingStage(NULL);

    static_cast<ShaderCodeGenerator *>(this)->setMultiLightShadowStage(NULL);

    static_cast<ShaderCodeGenerator *>(this)->setSSAOStage(NULL);

    static_cast<ShaderCodeGenerator *>(this)->setIBLStage(NULL);

    static_cast<ShaderCodeGenerator *>(this)->setMultiLightGroup(NULL);


}


OSG_END_NAMESPACE
