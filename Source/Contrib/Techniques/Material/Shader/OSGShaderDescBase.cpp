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
 **     class ShaderDesc!
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


#include "OSGGL.h"                        // ShaderType default header

#include "OSGShaderProgram.h"           // ShaderProgram Class

#include "OSGShaderDescBase.h"
#include "OSGShaderDesc.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ShaderDesc
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var GLenum          ShaderDescBase::_sfShaderType
    
*/

/*! \var std::string     ShaderDescBase::_sfProgram
    
*/

/*! \var UInt64          ShaderDescBase::_sfHash
    
*/

/*! \var ShaderProgram * ShaderDescBase::_sfShaderProgram
    
*/

/*! \var std::string     ShaderDescBase::_mfUniformBlockNames
    
*/

/*! \var Int32           ShaderDescBase::_mfUniformBindingPnts
    
*/

/*! \var std::string     ShaderDescBase::_mfShaderStorageBlockNames
    
*/

/*! \var Int32           ShaderDescBase::_mfShaderStorageBindingPnts
    
*/

/*! \var std::string     ShaderDescBase::_mfOSGVariables
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<ShaderDesc *, nsOSG>::_type(
    "ShaderDescPtr", 
    "FieldContainerPtr", 
    ShaderDesc::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(ShaderDesc *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ShaderDesc *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ShaderDesc *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ShaderDescBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(),
        "shaderType",
        "",
        ShaderTypeFieldId, ShaderTypeFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderDesc::editHandleShaderType),
        static_cast<FieldGetMethodSig >(&ShaderDesc::getHandleShaderType));

    oType.addInitialDesc(pDesc);

    pDesc = new SFString::Description(
        SFString::getClassType(),
        "program",
        "",
        ProgramFieldId, ProgramFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderDesc::editHandleProgram),
        static_cast<FieldGetMethodSig >(&ShaderDesc::getHandleProgram));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt64::Description(
        SFUInt64::getClassType(),
        "hash",
        "",
        HashFieldId, HashFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderDesc::editHandleHash),
        static_cast<FieldGetMethodSig >(&ShaderDesc::getHandleHash));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecShaderProgramPtr::Description(
        SFUnrecShaderProgramPtr::getClassType(),
        "shaderProgram",
        "",
        ShaderProgramFieldId, ShaderProgramFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderDesc::editHandleShaderProgram),
        static_cast<FieldGetMethodSig >(&ShaderDesc::getHandleShaderProgram));

    oType.addInitialDesc(pDesc);

    pDesc = new MFString::Description(
        MFString::getClassType(),
        "uniformBlockNames",
        "",
        UniformBlockNamesFieldId, UniformBlockNamesFieldMask,
        true,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderDesc::editHandleUniformBlockNames),
        static_cast<FieldGetMethodSig >(&ShaderDesc::getHandleUniformBlockNames));

    oType.addInitialDesc(pDesc);

    pDesc = new MFInt32::Description(
        MFInt32::getClassType(),
        "uniformBindingPnts",
        "",
        UniformBindingPntsFieldId, UniformBindingPntsFieldMask,
        true,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderDesc::editHandleUniformBindingPnts),
        static_cast<FieldGetMethodSig >(&ShaderDesc::getHandleUniformBindingPnts));

    oType.addInitialDesc(pDesc);

    pDesc = new MFString::Description(
        MFString::getClassType(),
        "shaderStorageBlockNames",
        "",
        ShaderStorageBlockNamesFieldId, ShaderStorageBlockNamesFieldMask,
        true,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderDesc::editHandleShaderStorageBlockNames),
        static_cast<FieldGetMethodSig >(&ShaderDesc::getHandleShaderStorageBlockNames));

    oType.addInitialDesc(pDesc);

    pDesc = new MFInt32::Description(
        MFInt32::getClassType(),
        "shaderStorageBindingPnts",
        "",
        ShaderStorageBindingPntsFieldId, ShaderStorageBindingPntsFieldMask,
        true,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderDesc::editHandleShaderStorageBindingPnts),
        static_cast<FieldGetMethodSig >(&ShaderDesc::getHandleShaderStorageBindingPnts));

    oType.addInitialDesc(pDesc);

    pDesc = new MFString::Description(
        MFString::getClassType(),
        "OSGVariables",
        "",
        OSGVariablesFieldId, OSGVariablesFieldMask,
        true,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderDesc::editHandleOSGVariables),
        static_cast<FieldGetMethodSig >(&ShaderDesc::getHandleOSGVariables));

    oType.addInitialDesc(pDesc);
}


ShaderDescBase::TypeObject ShaderDescBase::_type(
    ShaderDescBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&ShaderDescBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&ShaderDesc::initMethod),
    reinterpret_cast<ExitContainerF>(&ShaderDesc::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&ShaderDesc::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"ShaderDesc\"\n"
    "    parent=\"FieldContainer\"\n"
    "    library=\"ContribTechniques\"\n"
    "    structure=\"concrete\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    >\n"
    "\n"
    "    <Field\n"
    "        name=\"shaderType\"\n"
    "        type=\"GLenum\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        defaultValue=\"GL_NONE\"\n"
    "        defaultHeader=\"&quot;OSGGL.h&quot;\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"program\"\n"
    "        type=\"std::string\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        defaultValue=\"\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"hash\"\n"
    "        type=\"UInt64\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        defaultValue=\"0\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "\t name=\"shaderProgram\"\n"
    "\t type=\"ShaderProgramPtr\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"internal\"\n"
    "\t access=\"public\"\n"
    "         defaultValue=\"NULL\"\n"
    "\t >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"uniformBlockNames\"\n"
    "        type=\"std::string\"\n"
    "        cardinality=\"multi\"\n"
    "        visibility=\"internal\"\n"
    "        defaultValue=\"\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"uniformBindingPnts\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"multi\"\n"
    "        visibility=\"internal\"\n"
    "        defaultValue=\"0\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"shaderStorageBlockNames\"\n"
    "        type=\"std::string\"\n"
    "        cardinality=\"multi\"\n"
    "        visibility=\"internal\"\n"
    "        defaultValue=\"\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"shaderStorageBindingPnts\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"multi\"\n"
    "        visibility=\"internal\"\n"
    "        defaultValue=\"0\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"OSGVariables\"\n"
    "        type=\"std::string\"\n"
    "        cardinality=\"multi\"\n"
    "        visibility=\"internal\"\n"
    "        defaultValue=\"\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ShaderDescBase::getType(void)
{
    return _type;
}

const FieldContainerType &ShaderDescBase::getType(void) const
{
    return _type;
}

UInt32 ShaderDescBase::getContainerSize(void) const
{
    return sizeof(ShaderDesc);
}

/*------------------------- decorator get ------------------------------*/


SFGLenum *ShaderDescBase::editSFShaderType(void)
{
    editSField(ShaderTypeFieldMask);

    return &_sfShaderType;
}

const SFGLenum *ShaderDescBase::getSFShaderType(void) const
{
    return &_sfShaderType;
}


SFString *ShaderDescBase::editSFProgram(void)
{
    editSField(ProgramFieldMask);

    return &_sfProgram;
}

const SFString *ShaderDescBase::getSFProgram(void) const
{
    return &_sfProgram;
}


SFUInt64 *ShaderDescBase::editSFHash(void)
{
    editSField(HashFieldMask);

    return &_sfHash;
}

const SFUInt64 *ShaderDescBase::getSFHash(void) const
{
    return &_sfHash;
}


//! Get the ShaderDesc::_sfShaderProgram field.
const SFUnrecShaderProgramPtr *ShaderDescBase::getSFShaderProgram(void) const
{
    return &_sfShaderProgram;
}

SFUnrecShaderProgramPtr *ShaderDescBase::editSFShaderProgram  (void)
{
    editSField(ShaderProgramFieldMask);

    return &_sfShaderProgram;
}

//! Get the value of the ShaderDesc::_sfShaderProgram field.
ShaderProgram * ShaderDescBase::getShaderProgram(void) const
{
    return _sfShaderProgram.getValue();
}

//! Set the value of the ShaderDesc::_sfShaderProgram field.
void ShaderDescBase::setShaderProgram(ShaderProgram * const value)
{
    editSField(ShaderProgramFieldMask);

    _sfShaderProgram.setValue(value);
}


MFString *ShaderDescBase::editMFUniformBlockNames(void)
{
    editMField(UniformBlockNamesFieldMask, _mfUniformBlockNames);

    return &_mfUniformBlockNames;
}

const MFString *ShaderDescBase::getMFUniformBlockNames(void) const
{
    return &_mfUniformBlockNames;
}


MFInt32 *ShaderDescBase::editMFUniformBindingPnts(void)
{
    editMField(UniformBindingPntsFieldMask, _mfUniformBindingPnts);

    return &_mfUniformBindingPnts;
}

const MFInt32 *ShaderDescBase::getMFUniformBindingPnts(void) const
{
    return &_mfUniformBindingPnts;
}


MFString *ShaderDescBase::editMFShaderStorageBlockNames(void)
{
    editMField(ShaderStorageBlockNamesFieldMask, _mfShaderStorageBlockNames);

    return &_mfShaderStorageBlockNames;
}

const MFString *ShaderDescBase::getMFShaderStorageBlockNames(void) const
{
    return &_mfShaderStorageBlockNames;
}


MFInt32 *ShaderDescBase::editMFShaderStorageBindingPnts(void)
{
    editMField(ShaderStorageBindingPntsFieldMask, _mfShaderStorageBindingPnts);

    return &_mfShaderStorageBindingPnts;
}

const MFInt32 *ShaderDescBase::getMFShaderStorageBindingPnts(void) const
{
    return &_mfShaderStorageBindingPnts;
}


MFString *ShaderDescBase::editMFOSGVariables(void)
{
    editMField(OSGVariablesFieldMask, _mfOSGVariables);

    return &_mfOSGVariables;
}

const MFString *ShaderDescBase::getMFOSGVariables(void) const
{
    return &_mfOSGVariables;
}






/*------------------------------ access -----------------------------------*/

SizeT ShaderDescBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ShaderTypeFieldMask & whichField))
    {
        returnValue += _sfShaderType.getBinSize();
    }
    if(FieldBits::NoField != (ProgramFieldMask & whichField))
    {
        returnValue += _sfProgram.getBinSize();
    }
    if(FieldBits::NoField != (HashFieldMask & whichField))
    {
        returnValue += _sfHash.getBinSize();
    }
    if(FieldBits::NoField != (ShaderProgramFieldMask & whichField))
    {
        returnValue += _sfShaderProgram.getBinSize();
    }
    if(FieldBits::NoField != (UniformBlockNamesFieldMask & whichField))
    {
        returnValue += _mfUniformBlockNames.getBinSize();
    }
    if(FieldBits::NoField != (UniformBindingPntsFieldMask & whichField))
    {
        returnValue += _mfUniformBindingPnts.getBinSize();
    }
    if(FieldBits::NoField != (ShaderStorageBlockNamesFieldMask & whichField))
    {
        returnValue += _mfShaderStorageBlockNames.getBinSize();
    }
    if(FieldBits::NoField != (ShaderStorageBindingPntsFieldMask & whichField))
    {
        returnValue += _mfShaderStorageBindingPnts.getBinSize();
    }
    if(FieldBits::NoField != (OSGVariablesFieldMask & whichField))
    {
        returnValue += _mfOSGVariables.getBinSize();
    }

    return returnValue;
}

void ShaderDescBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ShaderTypeFieldMask & whichField))
    {
        _sfShaderType.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ProgramFieldMask & whichField))
    {
        _sfProgram.copyToBin(pMem);
    }
    if(FieldBits::NoField != (HashFieldMask & whichField))
    {
        _sfHash.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ShaderProgramFieldMask & whichField))
    {
        _sfShaderProgram.copyToBin(pMem);
    }
    if(FieldBits::NoField != (UniformBlockNamesFieldMask & whichField))
    {
        _mfUniformBlockNames.copyToBin(pMem);
    }
    if(FieldBits::NoField != (UniformBindingPntsFieldMask & whichField))
    {
        _mfUniformBindingPnts.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ShaderStorageBlockNamesFieldMask & whichField))
    {
        _mfShaderStorageBlockNames.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ShaderStorageBindingPntsFieldMask & whichField))
    {
        _mfShaderStorageBindingPnts.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OSGVariablesFieldMask & whichField))
    {
        _mfOSGVariables.copyToBin(pMem);
    }
}

void ShaderDescBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ShaderTypeFieldMask & whichField))
    {
        editSField(ShaderTypeFieldMask);
        _sfShaderType.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ProgramFieldMask & whichField))
    {
        editSField(ProgramFieldMask);
        _sfProgram.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (HashFieldMask & whichField))
    {
        editSField(HashFieldMask);
        _sfHash.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ShaderProgramFieldMask & whichField))
    {
        editSField(ShaderProgramFieldMask);
        _sfShaderProgram.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (UniformBlockNamesFieldMask & whichField))
    {
        editMField(UniformBlockNamesFieldMask, _mfUniformBlockNames);
        _mfUniformBlockNames.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (UniformBindingPntsFieldMask & whichField))
    {
        editMField(UniformBindingPntsFieldMask, _mfUniformBindingPnts);
        _mfUniformBindingPnts.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ShaderStorageBlockNamesFieldMask & whichField))
    {
        editMField(ShaderStorageBlockNamesFieldMask, _mfShaderStorageBlockNames);
        _mfShaderStorageBlockNames.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ShaderStorageBindingPntsFieldMask & whichField))
    {
        editMField(ShaderStorageBindingPntsFieldMask, _mfShaderStorageBindingPnts);
        _mfShaderStorageBindingPnts.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OSGVariablesFieldMask & whichField))
    {
        editMField(OSGVariablesFieldMask, _mfOSGVariables);
        _mfOSGVariables.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ShaderDescTransitPtr ShaderDescBase::createLocal(BitVector bFlags)
{
    ShaderDescTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ShaderDesc>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ShaderDescTransitPtr ShaderDescBase::createDependent(BitVector bFlags)
{
    ShaderDescTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ShaderDesc>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ShaderDescTransitPtr ShaderDescBase::create(void)
{
    ShaderDescTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ShaderDesc>(tmpPtr);
    }

    return fc;
}

ShaderDesc *ShaderDescBase::createEmptyLocal(BitVector bFlags)
{
    ShaderDesc *returnValue;

    newPtr<ShaderDesc>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ShaderDesc *ShaderDescBase::createEmpty(void)
{
    ShaderDesc *returnValue;

    newPtr<ShaderDesc>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr ShaderDescBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ShaderDesc *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShaderDesc *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShaderDescBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ShaderDesc *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShaderDesc *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShaderDescBase::shallowCopy(void) const
{
    ShaderDesc *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const ShaderDesc *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

ShaderDescBase::ShaderDescBase(void) :
    Inherited(),
    _sfShaderType             (GLenum(GL_NONE)),
    _sfProgram                (),
    _sfHash                   (UInt64(0)),
    _sfShaderProgram          (NULL),
    _mfUniformBlockNames      (),
    _mfUniformBindingPnts     (Int32(0)),
    _mfShaderStorageBlockNames(),
    _mfShaderStorageBindingPnts(Int32(0)),
    _mfOSGVariables           ()
{
}

ShaderDescBase::ShaderDescBase(const ShaderDescBase &source) :
    Inherited(source),
    _sfShaderType             (source._sfShaderType             ),
    _sfProgram                (source._sfProgram                ),
    _sfHash                   (source._sfHash                   ),
    _sfShaderProgram          (NULL),
    _mfUniformBlockNames      (source._mfUniformBlockNames      ),
    _mfUniformBindingPnts     (source._mfUniformBindingPnts     ),
    _mfShaderStorageBlockNames(source._mfShaderStorageBlockNames),
    _mfShaderStorageBindingPnts(source._mfShaderStorageBindingPnts),
    _mfOSGVariables           (source._mfOSGVariables           )
{
}


/*-------------------------- destructors ----------------------------------*/

ShaderDescBase::~ShaderDescBase(void)
{
}

void ShaderDescBase::onCreate(const ShaderDesc *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        ShaderDesc *pThis = static_cast<ShaderDesc *>(this);

        pThis->setShaderProgram(source->getShaderProgram());
    }
}

GetFieldHandlePtr ShaderDescBase::getHandleShaderType      (void) const
{
    SFGLenum::GetHandlePtr returnValue(
        new  SFGLenum::GetHandle(
             &_sfShaderType,
             this->getType().getFieldDesc(ShaderTypeFieldId),
             const_cast<ShaderDescBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderDescBase::editHandleShaderType     (void)
{
    SFGLenum::EditHandlePtr returnValue(
        new  SFGLenum::EditHandle(
             &_sfShaderType,
             this->getType().getFieldDesc(ShaderTypeFieldId),
             this));


    editSField(ShaderTypeFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderDescBase::getHandleProgram         (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfProgram,
             this->getType().getFieldDesc(ProgramFieldId),
             const_cast<ShaderDescBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderDescBase::editHandleProgram        (void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfProgram,
             this->getType().getFieldDesc(ProgramFieldId),
             this));


    editSField(ProgramFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderDescBase::getHandleHash            (void) const
{
    SFUInt64::GetHandlePtr returnValue(
        new  SFUInt64::GetHandle(
             &_sfHash,
             this->getType().getFieldDesc(HashFieldId),
             const_cast<ShaderDescBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderDescBase::editHandleHash           (void)
{
    SFUInt64::EditHandlePtr returnValue(
        new  SFUInt64::EditHandle(
             &_sfHash,
             this->getType().getFieldDesc(HashFieldId),
             this));


    editSField(HashFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderDescBase::getHandleShaderProgram   (void) const
{
    SFUnrecShaderProgramPtr::GetHandlePtr returnValue(
        new  SFUnrecShaderProgramPtr::GetHandle(
             &_sfShaderProgram,
             this->getType().getFieldDesc(ShaderProgramFieldId),
             const_cast<ShaderDescBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderDescBase::editHandleShaderProgram  (void)
{
    SFUnrecShaderProgramPtr::EditHandlePtr returnValue(
        new  SFUnrecShaderProgramPtr::EditHandle(
             &_sfShaderProgram,
             this->getType().getFieldDesc(ShaderProgramFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&ShaderDesc::setShaderProgram,
                    static_cast<ShaderDesc *>(this), _1));

    editSField(ShaderProgramFieldMask);

    return returnValue;
}

GetFieldHandlePtr ShaderDescBase::getHandleUniformBlockNames (void) const
{
    MFString::GetHandlePtr returnValue(
        new  MFString::GetHandle(
             &_mfUniformBlockNames,
             this->getType().getFieldDesc(UniformBlockNamesFieldId),
             const_cast<ShaderDescBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderDescBase::editHandleUniformBlockNames(void)
{
    MFString::EditHandlePtr returnValue(
        new  MFString::EditHandle(
             &_mfUniformBlockNames,
             this->getType().getFieldDesc(UniformBlockNamesFieldId),
             this));


    editMField(UniformBlockNamesFieldMask, _mfUniformBlockNames);

    return returnValue;
}

GetFieldHandlePtr ShaderDescBase::getHandleUniformBindingPnts (void) const
{
    MFInt32::GetHandlePtr returnValue(
        new  MFInt32::GetHandle(
             &_mfUniformBindingPnts,
             this->getType().getFieldDesc(UniformBindingPntsFieldId),
             const_cast<ShaderDescBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderDescBase::editHandleUniformBindingPnts(void)
{
    MFInt32::EditHandlePtr returnValue(
        new  MFInt32::EditHandle(
             &_mfUniformBindingPnts,
             this->getType().getFieldDesc(UniformBindingPntsFieldId),
             this));


    editMField(UniformBindingPntsFieldMask, _mfUniformBindingPnts);

    return returnValue;
}

GetFieldHandlePtr ShaderDescBase::getHandleShaderStorageBlockNames (void) const
{
    MFString::GetHandlePtr returnValue(
        new  MFString::GetHandle(
             &_mfShaderStorageBlockNames,
             this->getType().getFieldDesc(ShaderStorageBlockNamesFieldId),
             const_cast<ShaderDescBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderDescBase::editHandleShaderStorageBlockNames(void)
{
    MFString::EditHandlePtr returnValue(
        new  MFString::EditHandle(
             &_mfShaderStorageBlockNames,
             this->getType().getFieldDesc(ShaderStorageBlockNamesFieldId),
             this));


    editMField(ShaderStorageBlockNamesFieldMask, _mfShaderStorageBlockNames);

    return returnValue;
}

GetFieldHandlePtr ShaderDescBase::getHandleShaderStorageBindingPnts (void) const
{
    MFInt32::GetHandlePtr returnValue(
        new  MFInt32::GetHandle(
             &_mfShaderStorageBindingPnts,
             this->getType().getFieldDesc(ShaderStorageBindingPntsFieldId),
             const_cast<ShaderDescBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderDescBase::editHandleShaderStorageBindingPnts(void)
{
    MFInt32::EditHandlePtr returnValue(
        new  MFInt32::EditHandle(
             &_mfShaderStorageBindingPnts,
             this->getType().getFieldDesc(ShaderStorageBindingPntsFieldId),
             this));


    editMField(ShaderStorageBindingPntsFieldMask, _mfShaderStorageBindingPnts);

    return returnValue;
}

GetFieldHandlePtr ShaderDescBase::getHandleOSGVariables    (void) const
{
    MFString::GetHandlePtr returnValue(
        new  MFString::GetHandle(
             &_mfOSGVariables,
             this->getType().getFieldDesc(OSGVariablesFieldId),
             const_cast<ShaderDescBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderDescBase::editHandleOSGVariables   (void)
{
    MFString::EditHandlePtr returnValue(
        new  MFString::EditHandle(
             &_mfOSGVariables,
             this->getType().getFieldDesc(OSGVariablesFieldId),
             this));


    editMField(OSGVariablesFieldMask, _mfOSGVariables);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ShaderDescBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ShaderDesc *pThis = static_cast<ShaderDesc *>(this);

    pThis->execSync(static_cast<ShaderDesc *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ShaderDescBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ShaderDesc *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ShaderDesc *>(pRefAspect),
                  dynamic_cast<const ShaderDesc *>(this));

    return returnValue;
}
#endif

void ShaderDescBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<ShaderDesc *>(this)->setShaderProgram(NULL);

#ifdef OSG_MT_CPTR_ASPECT
    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);
#endif

#ifdef OSG_MT_CPTR_ASPECT
    _mfUniformBlockNames.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    _mfUniformBindingPnts.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    _mfShaderStorageBlockNames.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    _mfShaderStorageBindingPnts.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    _mfOSGVariables.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
}


OSG_END_NAMESPACE
