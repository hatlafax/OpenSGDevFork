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
 **     class GroupingStage!
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




#include "OSGGroupingStageBase.h"
#include "OSGGroupingStage.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::GroupingStage
    Extension to the Stage core that groups its subtree. It inherits all
    parameters from it parent.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<GroupingStage *, nsOSG>::_type(
    "GroupingStagePtr", 
    "RenderCallbackStagePtr", 
    GroupingStage::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(GroupingStage *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void GroupingStageBase::classDescInserter(TypeObject &oType)
{
}


GroupingStageBase::TypeObject GroupingStageBase::_type(
    GroupingStageBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&GroupingStageBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&GroupingStage::initMethod),
    reinterpret_cast<ExitContainerF>(&GroupingStage::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&GroupingStage::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"GroupingStage\"\n"
    "   parent=\"RenderCallbackStage\"\n"
    "   library=\"Group\"\n"
    "   pointerfieldtypes=\"none\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   isNodeCore=\"true\"\n"
    "   docGroupBase=\"GrpGroupStage\"\n"
    "   >\n"
    "  Extension to the Stage core that groups its subtree. It inherits all\n"
    "  parameters from it parent.\n"
    "</FieldContainer>\n",
    "Extension to the Stage core that groups its subtree. It inherits all\n"
    "parameters from it parent.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &GroupingStageBase::getType(void)
{
    return _type;
}

const FieldContainerType &GroupingStageBase::getType(void) const
{
    return _type;
}

UInt32 GroupingStageBase::getContainerSize(void) const
{
    return sizeof(GroupingStage);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

SizeT GroupingStageBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void GroupingStageBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void GroupingStageBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
GroupingStageTransitPtr GroupingStageBase::createLocal(BitVector bFlags)
{
    GroupingStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<GroupingStage>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
GroupingStageTransitPtr GroupingStageBase::createDependent(BitVector bFlags)
{
    GroupingStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<GroupingStage>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
GroupingStageTransitPtr GroupingStageBase::create(void)
{
    GroupingStageTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<GroupingStage>(tmpPtr);
    }

    return fc;
}

GroupingStage *GroupingStageBase::createEmptyLocal(BitVector bFlags)
{
    GroupingStage *returnValue;

    newPtr<GroupingStage>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
GroupingStage *GroupingStageBase::createEmpty(void)
{
    GroupingStage *returnValue;

    newPtr<GroupingStage>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr GroupingStageBase::shallowCopyLocal(
    BitVector bFlags) const
{
    GroupingStage *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const GroupingStage *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr GroupingStageBase::shallowCopyDependent(
    BitVector bFlags) const
{
    GroupingStage *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const GroupingStage *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr GroupingStageBase::shallowCopy(void) const
{
    GroupingStage *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const GroupingStage *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

GroupingStageBase::GroupingStageBase(void) :
    Inherited()
{
}

GroupingStageBase::GroupingStageBase(const GroupingStageBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

GroupingStageBase::~GroupingStageBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void GroupingStageBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    GroupingStage *pThis = static_cast<GroupingStage *>(this);

    pThis->execSync(static_cast<GroupingStage *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *GroupingStageBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    GroupingStage *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const GroupingStage *>(pRefAspect),
                  dynamic_cast<const GroupingStage *>(this));

    return returnValue;
}
#endif

void GroupingStageBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
