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
 **     class GeoProperty!
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


#include "OSGGLEXT.h"                     // VboUsage default header


#include "OSGGeoPropertyBase.h"
#include "OSGGeoProperty.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::GeoProperty
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var bool            GeoPropertyBase::_sfUseVBO
    The id used to register with the Window, 0 if not set up yet.
*/

/*! \var UInt32          GeoPropertyBase::_sfUsage
    Provides information about the semantics of this property. Valid values
    are the GeoProperty::Usage... constants.    
*/

/*! \var UInt32          GeoPropertyBase::_sfGLId
    The id used to register with the Window, 0 if not set up yet.
*/

/*! \var Int32           GeoPropertyBase::_sfVboUsage
    The usage pattern, only valid for VBO use.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<GeoProperty *, nsOSG>::_type(
    "GeoPropertyPtr", 
    "StateChunkPtr", 
    GeoProperty::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(GeoProperty *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           GeoProperty *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           GeoProperty *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void GeoPropertyBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "useVBO",
        "The id used to register with the Window, 0 if not set up yet.\n",
        UseVBOFieldId, UseVBOFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&GeoProperty::editHandleUseVBO),
        static_cast<FieldGetMethodSig >(&GeoProperty::getHandleUseVBO));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "usage",
        "Provides information about the semantics of this property. Valid values\n"
        "are the GeoProperty::Usage... constants.    \n",
        UsageFieldId, UsageFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&GeoProperty::editHandleUsage),
        static_cast<FieldGetMethodSig >(&GeoProperty::getHandleUsage));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "GLId",
        "The id used to register with the Window, 0 if not set up yet.\n",
        GLIdFieldId, GLIdFieldMask,
        true,
        (Field::FClusterLocal),
        static_cast<FieldEditMethodSig>(&GeoProperty::editHandleGLId),
        static_cast<FieldGetMethodSig >(&GeoProperty::getHandleGLId));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "vboUsage",
        "The usage pattern, only valid for VBO use.\n",
        VboUsageFieldId, VboUsageFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&GeoProperty::editHandleVboUsage),
        static_cast<FieldGetMethodSig >(&GeoProperty::getHandleVboUsage));

    oType.addInitialDesc(pDesc);
}


GeoPropertyBase::TypeObject GeoPropertyBase::_type(
    GeoPropertyBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    NULL,
    reinterpret_cast<InitContainerF>(&GeoProperty::initMethod),
    reinterpret_cast<ExitContainerF>(&GeoProperty::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&GeoProperty::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"GeoProperty\"\n"
    "    parent=\"StateChunk\"\n"
    "    library=\"System\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"abstract\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    docGroupBase=\"GrpDrawablesGeometry\"\n"
    "    >\n"
    "    <Field\n"
    "        name=\"useVBO\"\n"
    "        type=\"bool\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"true\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "        The id used to register with the Window, 0 if not set up yet.\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"usage\"\n"
    "        type=\"UInt32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"0\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "        Provides information about the semantics of this property. Valid values\n"
    "        are the GeoProperty::Usage... constants.    \n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"GLId\"\n"
    "        type=\"UInt32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        defaultValue=\"0\"\n"
    "        access=\"protected\"\n"
    "        fieldFlags=\"FClusterLocal\"\n"
    "        >\n"
    "        The id used to register with the Window, 0 if not set up yet.\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"vboUsage\"\n"
    "        type=\"Int32\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        defaultValue=\"GL_STATIC_DRAW_ARB\"\n"
    "        defaultHeader=\"&quot;OSGGLEXT.h&quot;\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "        The usage pattern, only valid for VBO use.\n"
    "    </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &GeoPropertyBase::getType(void)
{
    return _type;
}

const FieldContainerType &GeoPropertyBase::getType(void) const
{
    return _type;
}

UInt32 GeoPropertyBase::getContainerSize(void) const
{
    return sizeof(GeoProperty);
}

/*------------------------- decorator get ------------------------------*/


SFBool *GeoPropertyBase::editSFUseVBO(void)
{
    editSField(UseVBOFieldMask);

    return &_sfUseVBO;
}

const SFBool *GeoPropertyBase::getSFUseVBO(void) const
{
    return &_sfUseVBO;
}


SFUInt32 *GeoPropertyBase::editSFUsage(void)
{
    editSField(UsageFieldMask);

    return &_sfUsage;
}

const SFUInt32 *GeoPropertyBase::getSFUsage(void) const
{
    return &_sfUsage;
}


SFUInt32 *GeoPropertyBase::editSFGLId(void)
{
    editSField(GLIdFieldMask);

    return &_sfGLId;
}

const SFUInt32 *GeoPropertyBase::getSFGLId(void) const
{
    return &_sfGLId;
}


SFInt32 *GeoPropertyBase::editSFVboUsage(void)
{
    editSField(VboUsageFieldMask);

    return &_sfVboUsage;
}

const SFInt32 *GeoPropertyBase::getSFVboUsage(void) const
{
    return &_sfVboUsage;
}






/*------------------------------ access -----------------------------------*/

SizeT GeoPropertyBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (UseVBOFieldMask & whichField))
    {
        returnValue += _sfUseVBO.getBinSize();
    }
    if(FieldBits::NoField != (UsageFieldMask & whichField))
    {
        returnValue += _sfUsage.getBinSize();
    }
    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        returnValue += _sfGLId.getBinSize();
    }
    if(FieldBits::NoField != (VboUsageFieldMask & whichField))
    {
        returnValue += _sfVboUsage.getBinSize();
    }

    return returnValue;
}

void GeoPropertyBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (UseVBOFieldMask & whichField))
    {
        _sfUseVBO.copyToBin(pMem);
    }
    if(FieldBits::NoField != (UsageFieldMask & whichField))
    {
        _sfUsage.copyToBin(pMem);
    }
    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        _sfGLId.copyToBin(pMem);
    }
    if(FieldBits::NoField != (VboUsageFieldMask & whichField))
    {
        _sfVboUsage.copyToBin(pMem);
    }
}

void GeoPropertyBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (UseVBOFieldMask & whichField))
    {
        editSField(UseVBOFieldMask);
        _sfUseVBO.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (UsageFieldMask & whichField))
    {
        editSField(UsageFieldMask);
        _sfUsage.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        editSField(GLIdFieldMask);
        _sfGLId.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (VboUsageFieldMask & whichField))
    {
        editSField(VboUsageFieldMask);
        _sfVboUsage.copyFromBin(pMem);
    }
}




/*------------------------- constructors ----------------------------------*/

GeoPropertyBase::GeoPropertyBase(void) :
    Inherited(),
    _sfUseVBO                 (bool(true)),
    _sfUsage                  (UInt32(0)),
    _sfGLId                   (UInt32(0)),
    _sfVboUsage               (Int32(GL_STATIC_DRAW_ARB))
{
}

GeoPropertyBase::GeoPropertyBase(const GeoPropertyBase &source) :
    Inherited(source),
    _sfUseVBO                 (source._sfUseVBO                 ),
    _sfUsage                  (source._sfUsage                  ),
    _sfGLId                   (source._sfGLId                   ),
    _sfVboUsage               (source._sfVboUsage               )
{
}


/*-------------------------- destructors ----------------------------------*/

GeoPropertyBase::~GeoPropertyBase(void)
{
}


GetFieldHandlePtr GeoPropertyBase::getHandleUseVBO          (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfUseVBO,
             this->getType().getFieldDesc(UseVBOFieldId),
             const_cast<GeoPropertyBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr GeoPropertyBase::editHandleUseVBO         (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfUseVBO,
             this->getType().getFieldDesc(UseVBOFieldId),
             this));


    editSField(UseVBOFieldMask);

    return returnValue;
}

GetFieldHandlePtr GeoPropertyBase::getHandleUsage           (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfUsage,
             this->getType().getFieldDesc(UsageFieldId),
             const_cast<GeoPropertyBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr GeoPropertyBase::editHandleUsage          (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfUsage,
             this->getType().getFieldDesc(UsageFieldId),
             this));


    editSField(UsageFieldMask);

    return returnValue;
}

GetFieldHandlePtr GeoPropertyBase::getHandleGLId            (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfGLId,
             this->getType().getFieldDesc(GLIdFieldId),
             const_cast<GeoPropertyBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr GeoPropertyBase::editHandleGLId           (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfGLId,
             this->getType().getFieldDesc(GLIdFieldId),
             this));


    editSField(GLIdFieldMask);

    return returnValue;
}

GetFieldHandlePtr GeoPropertyBase::getHandleVboUsage        (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfVboUsage,
             this->getType().getFieldDesc(VboUsageFieldId),
             const_cast<GeoPropertyBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr GeoPropertyBase::editHandleVboUsage       (void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfVboUsage,
             this->getType().getFieldDesc(VboUsageFieldId),
             this));


    editSField(VboUsageFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void GeoPropertyBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    GeoProperty *pThis = static_cast<GeoProperty *>(this);

    pThis->execSync(static_cast<GeoProperty *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void GeoPropertyBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
