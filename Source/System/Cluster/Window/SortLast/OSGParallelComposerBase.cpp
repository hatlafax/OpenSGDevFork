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
 **     class ParallelComposer!
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




#include "OSGParallelComposerBase.h"
#include "OSGParallelComposer.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ParallelComposer
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var bool            ParallelComposerBase::_sfShort
    
*/

/*! \var bool            ParallelComposerBase::_sfAlpha
    
*/

/*! \var std::string     ParallelComposerBase::_sfPcLibPath
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<ParallelComposer *, nsOSG>::_type(
    "ParallelComposerPtr", 
    "ImageComposerPtr", 
    ParallelComposer::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(ParallelComposer *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ParallelComposerBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "short",
        "",
        ShortFieldId, ShortFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ParallelComposer::editHandleShort),
        static_cast<FieldGetMethodSig >(&ParallelComposer::getHandleShort));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "alpha",
        "",
        AlphaFieldId, AlphaFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ParallelComposer::editHandleAlpha),
        static_cast<FieldGetMethodSig >(&ParallelComposer::getHandleAlpha));

    oType.addInitialDesc(pDesc);

    pDesc = new SFString::Description(
        SFString::getClassType(),
        "pcLibPath",
        "",
        PcLibPathFieldId, PcLibPathFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ParallelComposer::editHandlePcLibPath),
        static_cast<FieldGetMethodSig >(&ParallelComposer::getHandlePcLibPath));

    oType.addInitialDesc(pDesc);
}


ParallelComposerBase::TypeObject ParallelComposerBase::_type(
    ParallelComposerBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&ParallelComposerBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&ParallelComposer::initMethod),
    reinterpret_cast<ExitContainerF>(&ParallelComposer::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&ParallelComposer::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"ParallelComposer\"\n"
    "   parent=\"ImageComposer\"\n"
    "   library=\"Cluster\"\n"
    "   pointerfieldtypes=\"none\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   docGroupBase=\"GrpClusterWindow\"\n"
    "   >\n"
    "  <Field\n"
    "     name=\"short\"\n"
    "     type=\"bool\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     defaultValue=\"true\"\n"
    "     access=\"public\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "     name=\"alpha\"\n"
    "     type=\"bool\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     defaultValue=\"false\"\n"
    "     access=\"public\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "     name=\"pcLibPath\"\n"
    "     type=\"std::string\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     access=\"public\"\n"
    "     defaultValue=\"\"\n"
    "     >\n"
    "  </Field>        \n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ParallelComposerBase::getType(void)
{
    return _type;
}

const FieldContainerType &ParallelComposerBase::getType(void) const
{
    return _type;
}

UInt32 ParallelComposerBase::getContainerSize(void) const
{
    return sizeof(ParallelComposer);
}

/*------------------------- decorator get ------------------------------*/


SFBool *ParallelComposerBase::editSFShort(void)
{
    editSField(ShortFieldMask);

    return &_sfShort;
}

const SFBool *ParallelComposerBase::getSFShort(void) const
{
    return &_sfShort;
}


SFBool *ParallelComposerBase::editSFAlpha(void)
{
    editSField(AlphaFieldMask);

    return &_sfAlpha;
}

const SFBool *ParallelComposerBase::getSFAlpha(void) const
{
    return &_sfAlpha;
}


SFString *ParallelComposerBase::editSFPcLibPath(void)
{
    editSField(PcLibPathFieldMask);

    return &_sfPcLibPath;
}

const SFString *ParallelComposerBase::getSFPcLibPath(void) const
{
    return &_sfPcLibPath;
}






/*------------------------------ access -----------------------------------*/

SizeT ParallelComposerBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ShortFieldMask & whichField))
    {
        returnValue += _sfShort.getBinSize();
    }
    if(FieldBits::NoField != (AlphaFieldMask & whichField))
    {
        returnValue += _sfAlpha.getBinSize();
    }
    if(FieldBits::NoField != (PcLibPathFieldMask & whichField))
    {
        returnValue += _sfPcLibPath.getBinSize();
    }

    return returnValue;
}

void ParallelComposerBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ShortFieldMask & whichField))
    {
        _sfShort.copyToBin(pMem);
    }
    if(FieldBits::NoField != (AlphaFieldMask & whichField))
    {
        _sfAlpha.copyToBin(pMem);
    }
    if(FieldBits::NoField != (PcLibPathFieldMask & whichField))
    {
        _sfPcLibPath.copyToBin(pMem);
    }
}

void ParallelComposerBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ShortFieldMask & whichField))
    {
        editSField(ShortFieldMask);
        _sfShort.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (AlphaFieldMask & whichField))
    {
        editSField(AlphaFieldMask);
        _sfAlpha.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (PcLibPathFieldMask & whichField))
    {
        editSField(PcLibPathFieldMask);
        _sfPcLibPath.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ParallelComposerTransitPtr ParallelComposerBase::createLocal(BitVector bFlags)
{
    ParallelComposerTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ParallelComposer>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ParallelComposerTransitPtr ParallelComposerBase::createDependent(BitVector bFlags)
{
    ParallelComposerTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ParallelComposer>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ParallelComposerTransitPtr ParallelComposerBase::create(void)
{
    ParallelComposerTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ParallelComposer>(tmpPtr);
    }

    return fc;
}

ParallelComposer *ParallelComposerBase::createEmptyLocal(BitVector bFlags)
{
    ParallelComposer *returnValue;

    newPtr<ParallelComposer>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ParallelComposer *ParallelComposerBase::createEmpty(void)
{
    ParallelComposer *returnValue;

    newPtr<ParallelComposer>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr ParallelComposerBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ParallelComposer *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ParallelComposer *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ParallelComposerBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ParallelComposer *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ParallelComposer *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ParallelComposerBase::shallowCopy(void) const
{
    ParallelComposer *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const ParallelComposer *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

ParallelComposerBase::ParallelComposerBase(void) :
    Inherited(),
    _sfShort                  (bool(true)),
    _sfAlpha                  (bool(false)),
    _sfPcLibPath              ()
{
}

ParallelComposerBase::ParallelComposerBase(const ParallelComposerBase &source) :
    Inherited(source),
    _sfShort                  (source._sfShort                  ),
    _sfAlpha                  (source._sfAlpha                  ),
    _sfPcLibPath              (source._sfPcLibPath              )
{
}


/*-------------------------- destructors ----------------------------------*/

ParallelComposerBase::~ParallelComposerBase(void)
{
}


GetFieldHandlePtr ParallelComposerBase::getHandleShort           (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfShort,
             this->getType().getFieldDesc(ShortFieldId),
             const_cast<ParallelComposerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ParallelComposerBase::editHandleShort          (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfShort,
             this->getType().getFieldDesc(ShortFieldId),
             this));


    editSField(ShortFieldMask);

    return returnValue;
}

GetFieldHandlePtr ParallelComposerBase::getHandleAlpha           (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfAlpha,
             this->getType().getFieldDesc(AlphaFieldId),
             const_cast<ParallelComposerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ParallelComposerBase::editHandleAlpha          (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfAlpha,
             this->getType().getFieldDesc(AlphaFieldId),
             this));


    editSField(AlphaFieldMask);

    return returnValue;
}

GetFieldHandlePtr ParallelComposerBase::getHandlePcLibPath       (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfPcLibPath,
             this->getType().getFieldDesc(PcLibPathFieldId),
             const_cast<ParallelComposerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ParallelComposerBase::editHandlePcLibPath      (void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfPcLibPath,
             this->getType().getFieldDesc(PcLibPathFieldId),
             this));


    editSField(PcLibPathFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ParallelComposerBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ParallelComposer *pThis = static_cast<ParallelComposer *>(this);

    pThis->execSync(static_cast<ParallelComposer *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ParallelComposerBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ParallelComposer *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ParallelComposer *>(pRefAspect),
                  dynamic_cast<const ParallelComposer *>(this));

    return returnValue;
}
#endif

void ParallelComposerBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
