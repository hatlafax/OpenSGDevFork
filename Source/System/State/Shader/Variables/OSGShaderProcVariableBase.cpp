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
 **     class ShaderProcVariable!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"




#include "OSGShaderProcVariableBase.h"
#include "OSGShaderProcVariable.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ShaderProcVariable
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var UInt32          ShaderProcVariableBase::_sfDependency
    scope
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ShaderProcVariable *, nsOSG>::_type("ShaderProcVariablePtr", "ShaderVariablePtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(ShaderProcVariable *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ShaderProcVariable *,
                           nsOSG);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ShaderProcVariable *,
                           nsOSG);

DataType &FieldTraits< ShaderProcVariable *, nsOSG + 1 >::getType(void)
{
    return FieldTraits<ShaderProcVariable *, nsOSG>::getType();
}


OSG_EXPORT_PTR_MFIELD(ChildPointerMField,
                      ShaderProcVariable *,
                      UnrecordedRefCountPolicy,
                      nsOSG + 1);


/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ShaderProcVariableBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "dependency",
        "scope\n",
        DependencyFieldId, DependencyFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ShaderProcVariable::editHandleDependency),
        static_cast<FieldGetMethodSig >(&ShaderProcVariable::getHandleDependency));

    oType.addInitialDesc(pDesc);
}


ShaderProcVariableBase::TypeObject ShaderProcVariableBase::_type(
    ShaderProcVariableBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    NULL,
    ShaderProcVariable::initMethod,
    ShaderProcVariable::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&ShaderProcVariable::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"ShaderProcVariable\"\n"
    "   parent=\"ShaderVariable\"\n"
    "   library=\"System\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   structure=\"abstract\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   childFields=\"multi\"\n"
    "   docGroupBase=\"GrpSystemShader\"\n"
    "   >\n"
    "  <Field\n"
    "\t name=\"dependency\"\n"
    "\t type=\"UInt32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t access=\"public\"\n"
    "     defaultValue=\"ShaderProcVariable::SHDObject\"\n"
    "\t >\n"
    "\tscope\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ShaderProcVariableBase::getType(void)
{
    return _type;
}

const FieldContainerType &ShaderProcVariableBase::getType(void) const
{
    return _type;
}

UInt32 ShaderProcVariableBase::getContainerSize(void) const
{
    return sizeof(ShaderProcVariable);
}

/*------------------------- decorator get ------------------------------*/


SFUInt32 *ShaderProcVariableBase::editSFDependency(void)
{
    editSField(DependencyFieldMask);

    return &_sfDependency;
}

const SFUInt32 *ShaderProcVariableBase::getSFDependency(void) const
{
    return &_sfDependency;
}






/*------------------------------ access -----------------------------------*/

UInt32 ShaderProcVariableBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (DependencyFieldMask & whichField))
    {
        returnValue += _sfDependency.getBinSize();
    }

    return returnValue;
}

void ShaderProcVariableBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (DependencyFieldMask & whichField))
    {
        _sfDependency.copyToBin(pMem);
    }
}

void ShaderProcVariableBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (DependencyFieldMask & whichField))
    {
        editSField(DependencyFieldMask);
        _sfDependency.copyFromBin(pMem);
    }
}




/*------------------------- constructors ----------------------------------*/

ShaderProcVariableBase::ShaderProcVariableBase(void) :
    Inherited(),
    _sfDependency             (UInt32(ShaderProcVariable::SHDObject))
{
}

ShaderProcVariableBase::ShaderProcVariableBase(const ShaderProcVariableBase &source) :
    Inherited(source),
    _sfDependency             (source._sfDependency             )
{
}


/*-------------------------- destructors ----------------------------------*/

ShaderProcVariableBase::~ShaderProcVariableBase(void)
{
}


GetFieldHandlePtr ShaderProcVariableBase::getHandleDependency      (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfDependency,
             this->getType().getFieldDesc(DependencyFieldId),
             const_cast<ShaderProcVariableBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ShaderProcVariableBase::editHandleDependency     (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfDependency,
             this->getType().getFieldDesc(DependencyFieldId),
             this));


    editSField(DependencyFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ShaderProcVariableBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ShaderProcVariable *pThis = static_cast<ShaderProcVariable *>(this);

    pThis->execSync(static_cast<ShaderProcVariable *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void ShaderProcVariableBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
