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
 **     class AnimQuaternionBlender!
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



#include "OSGAnimQuaternionChannel.h"   // Channels Class

#include "OSGAnimQuaternionBlenderBase.h"
#include "OSGAnimQuaternionBlender.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::AnimQuaternionBlender
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var AnimQuaternionChannel * AnimQuaternionBlenderBase::_mfChannels
    
*/

/*! \var Quaternion      AnimQuaternionBlenderBase::_sfOutValue
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<AnimQuaternionBlender *, nsOSG>::_type(
    "AnimQuaternionBlenderPtr", 
    "AnimBlenderPtr", 
    AnimQuaternionBlender::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(AnimQuaternionBlender *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           AnimQuaternionBlender *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           AnimQuaternionBlender *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void AnimQuaternionBlenderBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFUnrecAnimQuaternionChannelPtr::Description(
        MFUnrecAnimQuaternionChannelPtr::getClassType(),
        "channels",
        "",
        ChannelsFieldId, ChannelsFieldMask,
        false,
        (Field::FStdAccess | Field::FClusterLocal),
        static_cast<FieldEditMethodSig>(&AnimQuaternionBlender::editHandleChannels),
        static_cast<FieldGetMethodSig >(&AnimQuaternionBlender::getHandleChannels));

    oType.addInitialDesc(pDesc);

    pDesc = new SFQuaternion::Description(
        SFQuaternion::getClassType(),
        "outValue",
        "",
        OutValueFieldId, OutValueFieldMask,
        false,
        (Field::FClusterLocal),
        static_cast<FieldEditMethodSig>(&AnimQuaternionBlender::editHandleOutValue),
        static_cast<FieldGetMethodSig >(&AnimQuaternionBlender::getHandleOutValue));

    oType.addInitialDesc(pDesc);
}


AnimQuaternionBlenderBase::TypeObject AnimQuaternionBlenderBase::_type(
    AnimQuaternionBlenderBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&AnimQuaternionBlenderBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&AnimQuaternionBlender::initMethod),
    reinterpret_cast<ExitContainerF>(&AnimQuaternionBlender::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&AnimQuaternionBlender::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"AnimQuaternionBlender\"\n"
    "   parent=\"AnimBlender\"\n"
    "   library=\"Dynamics\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   isNodeCore=\"true\"\n"
    "   isBundle=\"false\"\n"
    "   parentFields=\"none\"\n"
    "   >\n"
    "  <Field\n"
    "     name=\"channels\"\n"
    "     category=\"pointer\"\n"
    "     type=\"AnimQuaternionChannel\"\n"
    "     cardinality=\"multi\"\n"
    "     visibility=\"external\"\n"
    "     access=\"public\"\n"
    "     fieldFlags=\"FStdAccess, FClusterLocal\"\n"
    "     >\n"
    "    </Field>\n"
    "  <Field\n"
    "     name=\"outValue\"\n"
    "     category=\"data\"\n"
    "     type=\"Quaternion\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     access=\"public\"\n"
    "     fieldFlags=\"FClusterLocal\"\n"
    "     >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &AnimQuaternionBlenderBase::getType(void)
{
    return _type;
}

const FieldContainerType &AnimQuaternionBlenderBase::getType(void) const
{
    return _type;
}

UInt32 AnimQuaternionBlenderBase::getContainerSize(void) const
{
    return sizeof(AnimQuaternionBlender);
}

/*------------------------- decorator get ------------------------------*/


//! Get the AnimQuaternionBlender::_mfChannels field.
const MFUnrecAnimQuaternionChannelPtr *AnimQuaternionBlenderBase::getMFChannels(void) const
{
    return &_mfChannels;
}

MFUnrecAnimQuaternionChannelPtr *AnimQuaternionBlenderBase::editMFChannels       (void)
{
    editMField(ChannelsFieldMask, _mfChannels);

    return &_mfChannels;
}
AnimQuaternionChannel * AnimQuaternionBlenderBase::getChannels(const UInt32 index) const
{
    return _mfChannels[index];
}

SFQuaternion *AnimQuaternionBlenderBase::editSFOutValue(void)
{
    editSField(OutValueFieldMask);

    return &_sfOutValue;
}

const SFQuaternion *AnimQuaternionBlenderBase::getSFOutValue(void) const
{
    return &_sfOutValue;
}




void AnimQuaternionBlenderBase::pushToChannels(AnimQuaternionChannel * const value)
{
    editMField(ChannelsFieldMask, _mfChannels);

    _mfChannels.push_back(value);
}

void AnimQuaternionBlenderBase::assignChannels (const MFUnrecAnimQuaternionChannelPtr &value)
{
    MFUnrecAnimQuaternionChannelPtr::const_iterator elemIt  =
        value.begin();
    MFUnrecAnimQuaternionChannelPtr::const_iterator elemEnd =
        value.end  ();

    static_cast<AnimQuaternionBlender *>(this)->clearChannels();

    while(elemIt != elemEnd)
    {
        this->pushToChannels(*elemIt);

        ++elemIt;
    }
}

void AnimQuaternionBlenderBase::removeFromChannels(UInt32 uiIndex)
{
    if(uiIndex < _mfChannels.size())
    {
        editMField(ChannelsFieldMask, _mfChannels);

        _mfChannels.erase(uiIndex);
    }
}

void AnimQuaternionBlenderBase::removeObjFromChannels(AnimQuaternionChannel * const value)
{
    Int32 iElemIdx = _mfChannels.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(ChannelsFieldMask, _mfChannels);

        _mfChannels.erase(iElemIdx);
    }
}
void AnimQuaternionBlenderBase::clearChannels(void)
{
    editMField(ChannelsFieldMask, _mfChannels);


    _mfChannels.clear();
}



/*------------------------------ access -----------------------------------*/

SizeT AnimQuaternionBlenderBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ChannelsFieldMask & whichField))
    {
        returnValue += _mfChannels.getBinSize();
    }
    if(FieldBits::NoField != (OutValueFieldMask & whichField))
    {
        returnValue += _sfOutValue.getBinSize();
    }

    return returnValue;
}

void AnimQuaternionBlenderBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ChannelsFieldMask & whichField))
    {
        _mfChannels.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OutValueFieldMask & whichField))
    {
        _sfOutValue.copyToBin(pMem);
    }
}

void AnimQuaternionBlenderBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ChannelsFieldMask & whichField))
    {
        editMField(ChannelsFieldMask, _mfChannels);
        _mfChannels.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OutValueFieldMask & whichField))
    {
        editSField(OutValueFieldMask);
        _sfOutValue.copyFromBin(pMem);
    }
}

//! create a new instance of the class
AnimQuaternionBlenderTransitPtr AnimQuaternionBlenderBase::createLocal(BitVector bFlags)
{
    AnimQuaternionBlenderTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<AnimQuaternionBlender>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
AnimQuaternionBlenderTransitPtr AnimQuaternionBlenderBase::createDependent(BitVector bFlags)
{
    AnimQuaternionBlenderTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<AnimQuaternionBlender>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
AnimQuaternionBlenderTransitPtr AnimQuaternionBlenderBase::create(void)
{
    AnimQuaternionBlenderTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<AnimQuaternionBlender>(tmpPtr);
    }

    return fc;
}

AnimQuaternionBlender *AnimQuaternionBlenderBase::createEmptyLocal(BitVector bFlags)
{
    AnimQuaternionBlender *returnValue;

    newPtr<AnimQuaternionBlender>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
AnimQuaternionBlender *AnimQuaternionBlenderBase::createEmpty(void)
{
    AnimQuaternionBlender *returnValue;

    newPtr<AnimQuaternionBlender>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr AnimQuaternionBlenderBase::shallowCopyLocal(
    BitVector bFlags) const
{
    AnimQuaternionBlender *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const AnimQuaternionBlender *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr AnimQuaternionBlenderBase::shallowCopyDependent(
    BitVector bFlags) const
{
    AnimQuaternionBlender *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const AnimQuaternionBlender *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr AnimQuaternionBlenderBase::shallowCopy(void) const
{
    AnimQuaternionBlender *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const AnimQuaternionBlender *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

AnimQuaternionBlenderBase::AnimQuaternionBlenderBase(void) :
    Inherited(),
    _mfChannels               (),
    _sfOutValue               ()
{
}

AnimQuaternionBlenderBase::AnimQuaternionBlenderBase(const AnimQuaternionBlenderBase &source) :
    Inherited(source),
    _mfChannels               (),
    _sfOutValue               (source._sfOutValue               )
{
}


/*-------------------------- destructors ----------------------------------*/

AnimQuaternionBlenderBase::~AnimQuaternionBlenderBase(void)
{
}

void AnimQuaternionBlenderBase::onCreate(const AnimQuaternionBlender *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        AnimQuaternionBlender *pThis = static_cast<AnimQuaternionBlender *>(this);

        MFUnrecAnimQuaternionChannelPtr::const_iterator ChannelsIt  =
            source->_mfChannels.begin();
        MFUnrecAnimQuaternionChannelPtr::const_iterator ChannelsEnd =
            source->_mfChannels.end  ();

        while(ChannelsIt != ChannelsEnd)
        {
            pThis->pushToChannels(*ChannelsIt);

            ++ChannelsIt;
        }
    }
}

GetFieldHandlePtr AnimQuaternionBlenderBase::getHandleChannels        (void) const
{
    MFUnrecAnimQuaternionChannelPtr::GetHandlePtr returnValue(
        new  MFUnrecAnimQuaternionChannelPtr::GetHandle(
             &_mfChannels,
             this->getType().getFieldDesc(ChannelsFieldId),
             const_cast<AnimQuaternionBlenderBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr AnimQuaternionBlenderBase::editHandleChannels       (void)
{
    MFUnrecAnimQuaternionChannelPtr::EditHandlePtr returnValue(
        new  MFUnrecAnimQuaternionChannelPtr::EditHandle(
             &_mfChannels,
             this->getType().getFieldDesc(ChannelsFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&AnimQuaternionBlender::pushToChannels,
                    static_cast<AnimQuaternionBlender *>(this), ::boost::placeholders::_1));
    returnValue->setRemoveMethod(
        boost::bind(&AnimQuaternionBlender::removeFromChannels,
                    static_cast<AnimQuaternionBlender *>(this), ::boost::placeholders::_1));
    returnValue->setRemoveObjMethod(
        boost::bind(&AnimQuaternionBlender::removeObjFromChannels,
                    static_cast<AnimQuaternionBlender *>(this), ::boost::placeholders::_1));
    returnValue->setClearMethod(
        boost::bind(&AnimQuaternionBlender::clearChannels,
                    static_cast<AnimQuaternionBlender *>(this)));

    editMField(ChannelsFieldMask, _mfChannels);

    return returnValue;
}

GetFieldHandlePtr AnimQuaternionBlenderBase::getHandleOutValue        (void) const
{
    SFQuaternion::GetHandlePtr returnValue(
        new  SFQuaternion::GetHandle(
             &_sfOutValue,
             this->getType().getFieldDesc(OutValueFieldId),
             const_cast<AnimQuaternionBlenderBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr AnimQuaternionBlenderBase::editHandleOutValue       (void)
{
    SFQuaternion::EditHandlePtr returnValue(
        new  SFQuaternion::EditHandle(
             &_sfOutValue,
             this->getType().getFieldDesc(OutValueFieldId),
             this));


    editSField(OutValueFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void AnimQuaternionBlenderBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    AnimQuaternionBlender *pThis = static_cast<AnimQuaternionBlender *>(this);

    pThis->execSync(static_cast<AnimQuaternionBlender *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *AnimQuaternionBlenderBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    AnimQuaternionBlender *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const AnimQuaternionBlender *>(pRefAspect),
                  dynamic_cast<const AnimQuaternionBlender *>(this));

    return returnValue;
}
#endif

void AnimQuaternionBlenderBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<AnimQuaternionBlender *>(this)->clearChannels();


}


OSG_END_NAMESPACE
