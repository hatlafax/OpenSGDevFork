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
 **     class AnimKeyFrameDataSource!
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




#include "OSGAnimKeyFrameDataSourceBase.h"
#include "OSGAnimKeyFrameDataSource.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::AnimKeyFrameDataSource
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Real32          AnimKeyFrameDataSourceBase::_mfInValues
    
*/

/*! \var UInt32          AnimKeyFrameDataSourceBase::_mfInterpolationModes
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<AnimKeyFrameDataSource *, nsOSG>::_type(
    "AnimKeyFrameDataSourcePtr", 
    "AnimDataSourcePtr", 
    AnimKeyFrameDataSource::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(AnimKeyFrameDataSource *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           AnimKeyFrameDataSource *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           AnimKeyFrameDataSource *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void AnimKeyFrameDataSourceBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFReal32::Description(
        MFReal32::getClassType(),
        "inValues",
        "",
        InValuesFieldId, InValuesFieldMask,
        false,
        (Field::FClusterLocal),
        static_cast<FieldEditMethodSig>(&AnimKeyFrameDataSource::editHandleInValues),
        static_cast<FieldGetMethodSig >(&AnimKeyFrameDataSource::getHandleInValues));

    oType.addInitialDesc(pDesc);

    pDesc = new MFUInt32::Description(
        MFUInt32::getClassType(),
        "interpolationModes",
        "",
        InterpolationModesFieldId, InterpolationModesFieldMask,
        false,
        (Field::FClusterLocal),
        static_cast<FieldEditMethodSig>(&AnimKeyFrameDataSource::editHandleInterpolationModes),
        static_cast<FieldGetMethodSig >(&AnimKeyFrameDataSource::getHandleInterpolationModes));

    oType.addInitialDesc(pDesc);
}


AnimKeyFrameDataSourceBase::TypeObject AnimKeyFrameDataSourceBase::_type(
    AnimKeyFrameDataSourceBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    NULL,
    reinterpret_cast<InitContainerF>(&AnimKeyFrameDataSource::initMethod),
    reinterpret_cast<ExitContainerF>(&AnimKeyFrameDataSource::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&AnimKeyFrameDataSource::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"AnimKeyFrameDataSource\"\n"
    "    parent=\"AnimDataSource\"\n"
    "    library=\"Dynamics\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"abstract\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"false\"\n"
    "    parentFields=\"none\"\n"
    ">\n"
    "  <Field\n"
    "     name=\"inValues\"\n"
    "     category=\"data\"\n"
    "     type=\"Real32\"\n"
    "     cardinality=\"multi\"\n"
    "     visibility=\"external\"\n"
    "     access=\"public\"\n"
    "     fieldFlags=\"FClusterLocal\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "     name=\"interpolationModes\"\n"
    "     category=\"data\"\n"
    "     type=\"UInt32\"\n"
    "     cardinality=\"multi\"\n"
    "     visibility=\"external\"\n"
    "     access=\"public\"\n"
    "     fieldFlags=\"FClusterLocal\"\n"
    "     >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &AnimKeyFrameDataSourceBase::getType(void)
{
    return _type;
}

const FieldContainerType &AnimKeyFrameDataSourceBase::getType(void) const
{
    return _type;
}

UInt32 AnimKeyFrameDataSourceBase::getContainerSize(void) const
{
    return sizeof(AnimKeyFrameDataSource);
}

/*------------------------- decorator get ------------------------------*/


MFReal32 *AnimKeyFrameDataSourceBase::editMFInValues(void)
{
    editMField(InValuesFieldMask, _mfInValues);

    return &_mfInValues;
}

const MFReal32 *AnimKeyFrameDataSourceBase::getMFInValues(void) const
{
    return &_mfInValues;
}


MFUInt32 *AnimKeyFrameDataSourceBase::editMFInterpolationModes(void)
{
    editMField(InterpolationModesFieldMask, _mfInterpolationModes);

    return &_mfInterpolationModes;
}

const MFUInt32 *AnimKeyFrameDataSourceBase::getMFInterpolationModes(void) const
{
    return &_mfInterpolationModes;
}






/*------------------------------ access -----------------------------------*/

SizeT AnimKeyFrameDataSourceBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (InValuesFieldMask & whichField))
    {
        returnValue += _mfInValues.getBinSize();
    }
    if(FieldBits::NoField != (InterpolationModesFieldMask & whichField))
    {
        returnValue += _mfInterpolationModes.getBinSize();
    }

    return returnValue;
}

void AnimKeyFrameDataSourceBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (InValuesFieldMask & whichField))
    {
        _mfInValues.copyToBin(pMem);
    }
    if(FieldBits::NoField != (InterpolationModesFieldMask & whichField))
    {
        _mfInterpolationModes.copyToBin(pMem);
    }
}

void AnimKeyFrameDataSourceBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (InValuesFieldMask & whichField))
    {
        editMField(InValuesFieldMask, _mfInValues);
        _mfInValues.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (InterpolationModesFieldMask & whichField))
    {
        editMField(InterpolationModesFieldMask, _mfInterpolationModes);
        _mfInterpolationModes.copyFromBin(pMem);
    }
}




/*------------------------- constructors ----------------------------------*/

AnimKeyFrameDataSourceBase::AnimKeyFrameDataSourceBase(void) :
    Inherited(),
    _mfInValues               (),
    _mfInterpolationModes     ()
{
}

AnimKeyFrameDataSourceBase::AnimKeyFrameDataSourceBase(const AnimKeyFrameDataSourceBase &source) :
    Inherited(source),
    _mfInValues               (source._mfInValues               ),
    _mfInterpolationModes     (source._mfInterpolationModes     )
{
}


/*-------------------------- destructors ----------------------------------*/

AnimKeyFrameDataSourceBase::~AnimKeyFrameDataSourceBase(void)
{
}


GetFieldHandlePtr AnimKeyFrameDataSourceBase::getHandleInValues        (void) const
{
    MFReal32::GetHandlePtr returnValue(
        new  MFReal32::GetHandle(
             &_mfInValues,
             this->getType().getFieldDesc(InValuesFieldId),
             const_cast<AnimKeyFrameDataSourceBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr AnimKeyFrameDataSourceBase::editHandleInValues       (void)
{
    MFReal32::EditHandlePtr returnValue(
        new  MFReal32::EditHandle(
             &_mfInValues,
             this->getType().getFieldDesc(InValuesFieldId),
             this));


    editMField(InValuesFieldMask, _mfInValues);

    return returnValue;
}

GetFieldHandlePtr AnimKeyFrameDataSourceBase::getHandleInterpolationModes (void) const
{
    MFUInt32::GetHandlePtr returnValue(
        new  MFUInt32::GetHandle(
             &_mfInterpolationModes,
             this->getType().getFieldDesc(InterpolationModesFieldId),
             const_cast<AnimKeyFrameDataSourceBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr AnimKeyFrameDataSourceBase::editHandleInterpolationModes(void)
{
    MFUInt32::EditHandlePtr returnValue(
        new  MFUInt32::EditHandle(
             &_mfInterpolationModes,
             this->getType().getFieldDesc(InterpolationModesFieldId),
             this));


    editMField(InterpolationModesFieldMask, _mfInterpolationModes);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void AnimKeyFrameDataSourceBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    AnimKeyFrameDataSource *pThis = static_cast<AnimKeyFrameDataSource *>(this);

    pThis->execSync(static_cast<AnimKeyFrameDataSource *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void AnimKeyFrameDataSourceBase::resolveLinks(void)
{
    Inherited::resolveLinks();

#ifdef OSG_MT_CPTR_ASPECT
    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);
#endif

#ifdef OSG_MT_CPTR_ASPECT
    _mfInValues.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    _mfInterpolationModes.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
}


OSG_END_NAMESPACE
