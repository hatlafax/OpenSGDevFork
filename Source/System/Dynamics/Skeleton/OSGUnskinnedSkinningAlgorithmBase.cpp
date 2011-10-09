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
 **     class UnskinnedSkinningAlgorithm!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"




#include "OSGUnskinnedSkinningAlgorithmBase.h"
#include "OSGUnskinnedSkinningAlgorithm.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::UnskinnedSkinningAlgorithm
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<UnskinnedSkinningAlgorithm *, nsOSG>::_type("UnskinnedSkinningAlgorithmPtr", "SkinningAlgorithmPtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(UnskinnedSkinningAlgorithm *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           UnskinnedSkinningAlgorithm *,
                           nsOSG);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           UnskinnedSkinningAlgorithm *,
                           nsOSG);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void UnskinnedSkinningAlgorithmBase::classDescInserter(TypeObject &oType)
{
}


UnskinnedSkinningAlgorithmBase::TypeObject UnskinnedSkinningAlgorithmBase::_type(
    UnskinnedSkinningAlgorithmBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&UnskinnedSkinningAlgorithmBase::createEmptyLocal),
    UnskinnedSkinningAlgorithm::initMethod,
    UnskinnedSkinningAlgorithm::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&UnskinnedSkinningAlgorithm::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"UnskinnedSkinningAlgorithm\"\n"
    "   parent=\"SkinningAlgorithm\"\n"
    "   library=\"Dynamics\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   childFields=\"none\"\n"
    "   parentFields=\"none\"\n"
    "   >\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &UnskinnedSkinningAlgorithmBase::getType(void)
{
    return _type;
}

const FieldContainerType &UnskinnedSkinningAlgorithmBase::getType(void) const
{
    return _type;
}

UInt32 UnskinnedSkinningAlgorithmBase::getContainerSize(void) const
{
    return sizeof(UnskinnedSkinningAlgorithm);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 UnskinnedSkinningAlgorithmBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void UnskinnedSkinningAlgorithmBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void UnskinnedSkinningAlgorithmBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
UnskinnedSkinningAlgorithmTransitPtr UnskinnedSkinningAlgorithmBase::createLocal(BitVector bFlags)
{
    UnskinnedSkinningAlgorithmTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<UnskinnedSkinningAlgorithm>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
UnskinnedSkinningAlgorithmTransitPtr UnskinnedSkinningAlgorithmBase::createDependent(BitVector bFlags)
{
    UnskinnedSkinningAlgorithmTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<UnskinnedSkinningAlgorithm>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
UnskinnedSkinningAlgorithmTransitPtr UnskinnedSkinningAlgorithmBase::create(void)
{
    UnskinnedSkinningAlgorithmTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<UnskinnedSkinningAlgorithm>(tmpPtr);
    }

    return fc;
}

UnskinnedSkinningAlgorithm *UnskinnedSkinningAlgorithmBase::createEmptyLocal(BitVector bFlags)
{
    UnskinnedSkinningAlgorithm *returnValue;

    newPtr<UnskinnedSkinningAlgorithm>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
UnskinnedSkinningAlgorithm *UnskinnedSkinningAlgorithmBase::createEmpty(void)
{
    UnskinnedSkinningAlgorithm *returnValue;

    newPtr<UnskinnedSkinningAlgorithm>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr UnskinnedSkinningAlgorithmBase::shallowCopyLocal(
    BitVector bFlags) const
{
    UnskinnedSkinningAlgorithm *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const UnskinnedSkinningAlgorithm *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr UnskinnedSkinningAlgorithmBase::shallowCopyDependent(
    BitVector bFlags) const
{
    UnskinnedSkinningAlgorithm *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const UnskinnedSkinningAlgorithm *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr UnskinnedSkinningAlgorithmBase::shallowCopy(void) const
{
    UnskinnedSkinningAlgorithm *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const UnskinnedSkinningAlgorithm *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

UnskinnedSkinningAlgorithmBase::UnskinnedSkinningAlgorithmBase(void) :
    Inherited()
{
}

UnskinnedSkinningAlgorithmBase::UnskinnedSkinningAlgorithmBase(const UnskinnedSkinningAlgorithmBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

UnskinnedSkinningAlgorithmBase::~UnskinnedSkinningAlgorithmBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void UnskinnedSkinningAlgorithmBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    UnskinnedSkinningAlgorithm *pThis = static_cast<UnskinnedSkinningAlgorithm *>(this);

    pThis->execSync(static_cast<UnskinnedSkinningAlgorithm *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *UnskinnedSkinningAlgorithmBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    UnskinnedSkinningAlgorithm *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const UnskinnedSkinningAlgorithm *>(pRefAspect),
                  dynamic_cast<const UnskinnedSkinningAlgorithm *>(this));

    return returnValue;
}
#endif

void UnskinnedSkinningAlgorithmBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
