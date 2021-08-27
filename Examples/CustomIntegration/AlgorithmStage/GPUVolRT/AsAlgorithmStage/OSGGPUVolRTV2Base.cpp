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
 **     class GPUVolRTV2!
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




#include "OSGGPUVolRTV2Base.h"
#include "OSGGPUVolRTV2.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::GPUVolRTV2
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Real32          GPUVolRTV2Base::_sfStepsize
    
*/

/*! \var bool            GPUVolRTV2Base::_sfToggleVisuals
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<GPUVolRTV2 *, nsOSG>::_type(
    "GPUVolRTV2Ptr", 
    "AlgorithmPtr", 
    GPUVolRTV2::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(GPUVolRTV2 *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           GPUVolRTV2 *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           GPUVolRTV2 *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void GPUVolRTV2Base::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "stepsize",
        "",
        StepsizeFieldId, StepsizeFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&GPUVolRTV2::editHandleStepsize),
        static_cast<FieldGetMethodSig >(&GPUVolRTV2::getHandleStepsize));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "toggleVisuals",
        "",
        ToggleVisualsFieldId, ToggleVisualsFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&GPUVolRTV2::editHandleToggleVisuals),
        static_cast<FieldGetMethodSig >(&GPUVolRTV2::getHandleToggleVisuals));

    oType.addInitialDesc(pDesc);
}


GPUVolRTV2Base::TypeObject GPUVolRTV2Base::_type(
    GPUVolRTV2Base::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&GPUVolRTV2Base::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&GPUVolRTV2::initMethod),
    reinterpret_cast<ExitContainerF>(&GPUVolRTV2::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&GPUVolRTV2::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"GPUVolRTV2\"\n"
    "   parent=\"Algorithm\"\n"
    "   library=\"ExGPUVolRT\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   isNodeCore=\"false\"\n"
    "   >\n"
    "  <Field\n"
    "     name=\"stepsize\"\n"
    "     type=\"Real32\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     defaultValue=\"1.f/50.f\"\n"
    "     >\n"
    "  </Field>\n"
    "  <Field\n"
    "     name=\"toggleVisuals\"\n"
    "     type=\"bool\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     defaultValue=\"true\"\n"
    "     >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &GPUVolRTV2Base::getType(void)
{
    return _type;
}

const FieldContainerType &GPUVolRTV2Base::getType(void) const
{
    return _type;
}

UInt32 GPUVolRTV2Base::getContainerSize(void) const
{
    return sizeof(GPUVolRTV2);
}

/*------------------------- decorator get ------------------------------*/


SFReal32 *GPUVolRTV2Base::editSFStepsize(void)
{
    editSField(StepsizeFieldMask);

    return &_sfStepsize;
}

const SFReal32 *GPUVolRTV2Base::getSFStepsize(void) const
{
    return &_sfStepsize;
}


SFBool *GPUVolRTV2Base::editSFToggleVisuals(void)
{
    editSField(ToggleVisualsFieldMask);

    return &_sfToggleVisuals;
}

const SFBool *GPUVolRTV2Base::getSFToggleVisuals(void) const
{
    return &_sfToggleVisuals;
}






/*------------------------------ access -----------------------------------*/

SizeT GPUVolRTV2Base::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (StepsizeFieldMask & whichField))
    {
        returnValue += _sfStepsize.getBinSize();
    }
    if(FieldBits::NoField != (ToggleVisualsFieldMask & whichField))
    {
        returnValue += _sfToggleVisuals.getBinSize();
    }

    return returnValue;
}

void GPUVolRTV2Base::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (StepsizeFieldMask & whichField))
    {
        _sfStepsize.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ToggleVisualsFieldMask & whichField))
    {
        _sfToggleVisuals.copyToBin(pMem);
    }
}

void GPUVolRTV2Base::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (StepsizeFieldMask & whichField))
    {
        editSField(StepsizeFieldMask);
        _sfStepsize.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ToggleVisualsFieldMask & whichField))
    {
        editSField(ToggleVisualsFieldMask);
        _sfToggleVisuals.copyFromBin(pMem);
    }
}

//! create a new instance of the class
GPUVolRTV2TransitPtr GPUVolRTV2Base::createLocal(BitVector bFlags)
{
    GPUVolRTV2TransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<GPUVolRTV2>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
GPUVolRTV2TransitPtr GPUVolRTV2Base::createDependent(BitVector bFlags)
{
    GPUVolRTV2TransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<GPUVolRTV2>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
GPUVolRTV2TransitPtr GPUVolRTV2Base::create(void)
{
    GPUVolRTV2TransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<GPUVolRTV2>(tmpPtr);
    }

    return fc;
}

GPUVolRTV2 *GPUVolRTV2Base::createEmptyLocal(BitVector bFlags)
{
    GPUVolRTV2 *returnValue;

    newPtr<GPUVolRTV2>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
GPUVolRTV2 *GPUVolRTV2Base::createEmpty(void)
{
    GPUVolRTV2 *returnValue;

    newPtr<GPUVolRTV2>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr GPUVolRTV2Base::shallowCopyLocal(
    BitVector bFlags) const
{
    GPUVolRTV2 *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const GPUVolRTV2 *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr GPUVolRTV2Base::shallowCopyDependent(
    BitVector bFlags) const
{
    GPUVolRTV2 *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const GPUVolRTV2 *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr GPUVolRTV2Base::shallowCopy(void) const
{
    GPUVolRTV2 *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const GPUVolRTV2 *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

GPUVolRTV2Base::GPUVolRTV2Base(void) :
    Inherited(),
    _sfStepsize               (Real32(1.f/50.f)),
    _sfToggleVisuals          (bool(true))
{
}

GPUVolRTV2Base::GPUVolRTV2Base(const GPUVolRTV2Base &source) :
    Inherited(source),
    _sfStepsize               (source._sfStepsize               ),
    _sfToggleVisuals          (source._sfToggleVisuals          )
{
}


/*-------------------------- destructors ----------------------------------*/

GPUVolRTV2Base::~GPUVolRTV2Base(void)
{
}


GetFieldHandlePtr GPUVolRTV2Base::getHandleStepsize        (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfStepsize,
             this->getType().getFieldDesc(StepsizeFieldId),
             const_cast<GPUVolRTV2Base *>(this)));

    return returnValue;
}

EditFieldHandlePtr GPUVolRTV2Base::editHandleStepsize       (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfStepsize,
             this->getType().getFieldDesc(StepsizeFieldId),
             this));


    editSField(StepsizeFieldMask);

    return returnValue;
}

GetFieldHandlePtr GPUVolRTV2Base::getHandleToggleVisuals   (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfToggleVisuals,
             this->getType().getFieldDesc(ToggleVisualsFieldId),
             const_cast<GPUVolRTV2Base *>(this)));

    return returnValue;
}

EditFieldHandlePtr GPUVolRTV2Base::editHandleToggleVisuals  (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfToggleVisuals,
             this->getType().getFieldDesc(ToggleVisualsFieldId),
             this));


    editSField(ToggleVisualsFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void GPUVolRTV2Base::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    GPUVolRTV2 *pThis = static_cast<GPUVolRTV2 *>(this);

    pThis->execSync(static_cast<GPUVolRTV2 *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *GPUVolRTV2Base::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    GPUVolRTV2 *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const GPUVolRTV2 *>(pRefAspect),
                  dynamic_cast<const GPUVolRTV2 *>(this));

    return returnValue;
}
#endif

void GPUVolRTV2Base::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
