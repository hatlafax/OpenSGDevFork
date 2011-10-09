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
 **     class AnimTargetAttachment!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"



#include "OSGAnimBlender.h"             // Blenders Class

#include "OSGAnimTargetAttachmentBase.h"
#include "OSGAnimTargetAttachment.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::AnimTargetAttachment
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var std::string     AnimTargetAttachmentBase::_sfTargetId
    
*/

/*! \var AnimBlender *   AnimTargetAttachmentBase::_mfBlenders
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<AnimTargetAttachment *, nsOSG>::_type("AnimTargetAttachmentPtr", "AttachmentPtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(AnimTargetAttachment *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           AnimTargetAttachment *,
                           nsOSG);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           AnimTargetAttachment *,
                           nsOSG);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void AnimTargetAttachmentBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFString::Description(
        SFString::getClassType(),
        "targetId",
        "",
        TargetIdFieldId, TargetIdFieldMask,
        false,
        (Field::FClusterLocal),
        static_cast<FieldEditMethodSig>(&AnimTargetAttachment::editHandleTargetId),
        static_cast<FieldGetMethodSig >(&AnimTargetAttachment::getHandleTargetId));

    oType.addInitialDesc(pDesc);

    pDesc = new MFUnrecAnimBlenderPtr::Description(
        MFUnrecAnimBlenderPtr::getClassType(),
        "blenders",
        "",
        BlendersFieldId, BlendersFieldMask,
        true,
        (Field::FStdAccess | Field::FClusterLocal),
        static_cast<FieldEditMethodSig>(&AnimTargetAttachment::editHandleBlenders),
        static_cast<FieldGetMethodSig >(&AnimTargetAttachment::getHandleBlenders));

    oType.addInitialDesc(pDesc);
}


AnimTargetAttachmentBase::TypeObject AnimTargetAttachmentBase::_type(
    AnimTargetAttachmentBase::getClassname(),
    Inherited::getClassname(),
    "AnimTargetAttachment",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&AnimTargetAttachmentBase::createEmptyLocal),
    AnimTargetAttachment::initMethod,
    AnimTargetAttachment::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&AnimTargetAttachment::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"AnimTargetAttachment\"\n"
    "    parent=\"Attachment\"\n"
    "    library=\"Dynamics\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    ">\n"
    "  <Field\n"
    "     name=\"targetId\"\n"
    "     type=\"std::string\"\n"
    "     category=\"data\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     access=\"public\"\n"
    "     defaultValue=\"\"\n"
    "     fieldFlags=\"FClusterLocal\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "     name=\"blenders\"\n"
    "     type=\"AnimBlender\"\n"
    "     category=\"pointer\"\n"
    "     cardinality=\"multi\"\n"
    "     visibility=\"internal\"\n"
    "     access=\"public\"\n"
    "     fieldFlags=\"FStdAccess, FClusterLocal\"\n"
    "     >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &AnimTargetAttachmentBase::getType(void)
{
    return _type;
}

const FieldContainerType &AnimTargetAttachmentBase::getType(void) const
{
    return _type;
}

UInt32 AnimTargetAttachmentBase::getContainerSize(void) const
{
    return sizeof(AnimTargetAttachment);
}

/*------------------------- decorator get ------------------------------*/


SFString *AnimTargetAttachmentBase::editSFTargetId(void)
{
    editSField(TargetIdFieldMask);

    return &_sfTargetId;
}

const SFString *AnimTargetAttachmentBase::getSFTargetId(void) const
{
    return &_sfTargetId;
}


//! Get the AnimTargetAttachment::_mfBlenders field.
const MFUnrecAnimBlenderPtr *AnimTargetAttachmentBase::getMFBlenders(void) const
{
    return &_mfBlenders;
}

MFUnrecAnimBlenderPtr *AnimTargetAttachmentBase::editMFBlenders       (void)
{
    editMField(BlendersFieldMask, _mfBlenders);

    return &_mfBlenders;
}



void AnimTargetAttachmentBase::pushToBlenders(AnimBlender * const value)
{
    editMField(BlendersFieldMask, _mfBlenders);

    _mfBlenders.push_back(value);
}

void AnimTargetAttachmentBase::assignBlenders (const MFUnrecAnimBlenderPtr &value)
{
    MFUnrecAnimBlenderPtr::const_iterator elemIt  =
        value.begin();
    MFUnrecAnimBlenderPtr::const_iterator elemEnd =
        value.end  ();

    static_cast<AnimTargetAttachment *>(this)->clearBlenders();

    while(elemIt != elemEnd)
    {
        this->pushToBlenders(*elemIt);

        ++elemIt;
    }
}

void AnimTargetAttachmentBase::removeFromBlenders(UInt32 uiIndex)
{
    if(uiIndex < _mfBlenders.size())
    {
        editMField(BlendersFieldMask, _mfBlenders);

        _mfBlenders.erase(uiIndex);
    }
}

void AnimTargetAttachmentBase::removeObjFromBlenders(AnimBlender * const value)
{
    Int32 iElemIdx = _mfBlenders.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(BlendersFieldMask, _mfBlenders);

        _mfBlenders.erase(iElemIdx);
    }
}
void AnimTargetAttachmentBase::clearBlenders(void)
{
    editMField(BlendersFieldMask, _mfBlenders);


    _mfBlenders.clear();
}



/*------------------------------ access -----------------------------------*/

UInt32 AnimTargetAttachmentBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (TargetIdFieldMask & whichField))
    {
        returnValue += _sfTargetId.getBinSize();
    }
    if(FieldBits::NoField != (BlendersFieldMask & whichField))
    {
        returnValue += _mfBlenders.getBinSize();
    }

    return returnValue;
}

void AnimTargetAttachmentBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (TargetIdFieldMask & whichField))
    {
        _sfTargetId.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BlendersFieldMask & whichField))
    {
        _mfBlenders.copyToBin(pMem);
    }
}

void AnimTargetAttachmentBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (TargetIdFieldMask & whichField))
    {
        editSField(TargetIdFieldMask);
        _sfTargetId.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BlendersFieldMask & whichField))
    {
        editMField(BlendersFieldMask, _mfBlenders);
        _mfBlenders.copyFromBin(pMem);
    }
}

//! create a new instance of the class
AnimTargetAttachmentTransitPtr AnimTargetAttachmentBase::createLocal(BitVector bFlags)
{
    AnimTargetAttachmentTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<AnimTargetAttachment>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
AnimTargetAttachmentTransitPtr AnimTargetAttachmentBase::createDependent(BitVector bFlags)
{
    AnimTargetAttachmentTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<AnimTargetAttachment>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
AnimTargetAttachmentTransitPtr AnimTargetAttachmentBase::create(void)
{
    AnimTargetAttachmentTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<AnimTargetAttachment>(tmpPtr);
    }

    return fc;
}

AnimTargetAttachment *AnimTargetAttachmentBase::createEmptyLocal(BitVector bFlags)
{
    AnimTargetAttachment *returnValue;

    newPtr<AnimTargetAttachment>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
AnimTargetAttachment *AnimTargetAttachmentBase::createEmpty(void)
{
    AnimTargetAttachment *returnValue;

    newPtr<AnimTargetAttachment>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr AnimTargetAttachmentBase::shallowCopyLocal(
    BitVector bFlags) const
{
    AnimTargetAttachment *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const AnimTargetAttachment *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr AnimTargetAttachmentBase::shallowCopyDependent(
    BitVector bFlags) const
{
    AnimTargetAttachment *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const AnimTargetAttachment *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr AnimTargetAttachmentBase::shallowCopy(void) const
{
    AnimTargetAttachment *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const AnimTargetAttachment *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

AnimTargetAttachmentBase::AnimTargetAttachmentBase(void) :
    Inherited(),
    _sfTargetId               (),
    _mfBlenders               ()
{
}

AnimTargetAttachmentBase::AnimTargetAttachmentBase(const AnimTargetAttachmentBase &source) :
    Inherited(source),
    _sfTargetId               (source._sfTargetId               ),
    _mfBlenders               ()
{
}


/*-------------------------- destructors ----------------------------------*/

AnimTargetAttachmentBase::~AnimTargetAttachmentBase(void)
{
}

void AnimTargetAttachmentBase::onCreate(const AnimTargetAttachment *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        AnimTargetAttachment *pThis = static_cast<AnimTargetAttachment *>(this);

        MFUnrecAnimBlenderPtr::const_iterator BlendersIt  =
            source->_mfBlenders.begin();
        MFUnrecAnimBlenderPtr::const_iterator BlendersEnd =
            source->_mfBlenders.end  ();

        while(BlendersIt != BlendersEnd)
        {
            pThis->pushToBlenders(*BlendersIt);

            ++BlendersIt;
        }
    }
}

GetFieldHandlePtr AnimTargetAttachmentBase::getHandleTargetId        (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfTargetId,
             this->getType().getFieldDesc(TargetIdFieldId),
             const_cast<AnimTargetAttachmentBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr AnimTargetAttachmentBase::editHandleTargetId       (void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfTargetId,
             this->getType().getFieldDesc(TargetIdFieldId),
             this));


    editSField(TargetIdFieldMask);

    return returnValue;
}

GetFieldHandlePtr AnimTargetAttachmentBase::getHandleBlenders        (void) const
{
    MFUnrecAnimBlenderPtr::GetHandlePtr returnValue(
        new  MFUnrecAnimBlenderPtr::GetHandle(
             &_mfBlenders,
             this->getType().getFieldDesc(BlendersFieldId),
             const_cast<AnimTargetAttachmentBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr AnimTargetAttachmentBase::editHandleBlenders       (void)
{
    MFUnrecAnimBlenderPtr::EditHandlePtr returnValue(
        new  MFUnrecAnimBlenderPtr::EditHandle(
             &_mfBlenders,
             this->getType().getFieldDesc(BlendersFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&AnimTargetAttachment::pushToBlenders,
                    static_cast<AnimTargetAttachment *>(this), _1));
    returnValue->setRemoveMethod(
        boost::bind(&AnimTargetAttachment::removeFromBlenders,
                    static_cast<AnimTargetAttachment *>(this), _1));
    returnValue->setRemoveObjMethod(
        boost::bind(&AnimTargetAttachment::removeObjFromBlenders,
                    static_cast<AnimTargetAttachment *>(this), _1));
    returnValue->setClearMethod(
        boost::bind(&AnimTargetAttachment::clearBlenders,
                    static_cast<AnimTargetAttachment *>(this)));

    editMField(BlendersFieldMask, _mfBlenders);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void AnimTargetAttachmentBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    AnimTargetAttachment *pThis = static_cast<AnimTargetAttachment *>(this);

    pThis->execSync(static_cast<AnimTargetAttachment *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *AnimTargetAttachmentBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    AnimTargetAttachment *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const AnimTargetAttachment *>(pRefAspect),
                  dynamic_cast<const AnimTargetAttachment *>(this));

    return returnValue;
}
#endif

void AnimTargetAttachmentBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<AnimTargetAttachment *>(this)->clearBlenders();


}


OSG_END_NAMESPACE
