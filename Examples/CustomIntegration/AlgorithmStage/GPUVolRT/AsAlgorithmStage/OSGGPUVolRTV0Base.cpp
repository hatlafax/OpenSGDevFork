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
 **     class GPUVolRTV0!
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




#include "OSGGPUVolRTV0Base.h"
#include "OSGGPUVolRTV0.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::GPUVolRTV0
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<GPUVolRTV0 *, nsOSG>::_type(
    "GPUVolRTV0Ptr", 
    "AlgorithmPtr", 
    GPUVolRTV0::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(GPUVolRTV0 *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           GPUVolRTV0 *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           GPUVolRTV0 *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void GPUVolRTV0Base::classDescInserter(TypeObject &oType)
{
}


GPUVolRTV0Base::TypeObject GPUVolRTV0Base::_type(
    GPUVolRTV0Base::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&GPUVolRTV0Base::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&GPUVolRTV0::initMethod),
    reinterpret_cast<ExitContainerF>(&GPUVolRTV0::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&GPUVolRTV0::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"GPUVolRTV0\"\n"
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
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &GPUVolRTV0Base::getType(void)
{
    return _type;
}

const FieldContainerType &GPUVolRTV0Base::getType(void) const
{
    return _type;
}

UInt32 GPUVolRTV0Base::getContainerSize(void) const
{
    return sizeof(GPUVolRTV0);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

SizeT GPUVolRTV0Base::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void GPUVolRTV0Base::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void GPUVolRTV0Base::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
GPUVolRTV0TransitPtr GPUVolRTV0Base::createLocal(BitVector bFlags)
{
    GPUVolRTV0TransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<GPUVolRTV0>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
GPUVolRTV0TransitPtr GPUVolRTV0Base::createDependent(BitVector bFlags)
{
    GPUVolRTV0TransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<GPUVolRTV0>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
GPUVolRTV0TransitPtr GPUVolRTV0Base::create(void)
{
    GPUVolRTV0TransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<GPUVolRTV0>(tmpPtr);
    }

    return fc;
}

GPUVolRTV0 *GPUVolRTV0Base::createEmptyLocal(BitVector bFlags)
{
    GPUVolRTV0 *returnValue;

    newPtr<GPUVolRTV0>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
GPUVolRTV0 *GPUVolRTV0Base::createEmpty(void)
{
    GPUVolRTV0 *returnValue;

    newPtr<GPUVolRTV0>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr GPUVolRTV0Base::shallowCopyLocal(
    BitVector bFlags) const
{
    GPUVolRTV0 *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const GPUVolRTV0 *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr GPUVolRTV0Base::shallowCopyDependent(
    BitVector bFlags) const
{
    GPUVolRTV0 *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const GPUVolRTV0 *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr GPUVolRTV0Base::shallowCopy(void) const
{
    GPUVolRTV0 *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const GPUVolRTV0 *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

GPUVolRTV0Base::GPUVolRTV0Base(void) :
    Inherited()
{
}

GPUVolRTV0Base::GPUVolRTV0Base(const GPUVolRTV0Base &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

GPUVolRTV0Base::~GPUVolRTV0Base(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void GPUVolRTV0Base::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    GPUVolRTV0 *pThis = static_cast<GPUVolRTV0 *>(this);

    pThis->execSync(static_cast<GPUVolRTV0 *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *GPUVolRTV0Base::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    GPUVolRTV0 *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const GPUVolRTV0 *>(pRefAspect),
                  dynamic_cast<const GPUVolRTV0 *>(this));

    return returnValue;
}
#endif

void GPUVolRTV0Base::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
