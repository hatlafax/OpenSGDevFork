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
 **     class VisitSubTree!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEVISITSUBTREEINST

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>



#include <OSGNode.h> // SubTreeRoot Class

#include "OSGVisitSubTreeBase.h"
#include "OSGVisitSubTree.h"

#include "boost/bind.hpp"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::VisitSubTree
    VisitSubTree provides a way to point the renderer to another section of the
    scene graph for rendering. This is useful for multi-pass algorithms using
    OSG::Stage because it provides a way to render the same graph multiple times
    without duplicating the nodes.
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var Node *          VisitSubTreeBase::_sfSubTreeRoot
    Reference to the sub-graph to draw in place of this node.
    Whatever node is pointed to will be drawn here as if it was duplicated
    at this location.
*/


void VisitSubTreeBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFWeakNodePtr::Description(
        SFWeakNodePtr::getClassType(),
        "subTreeRoot",
        "Reference to the sub-graph to draw in place of this node.\n"
        "Whatever node is pointed to will be drawn here as if it was duplicated\n"
        "at this location.\n",
        SubTreeRootFieldId, SubTreeRootFieldMask,
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&VisitSubTree::editHandleSubTreeRoot),
        static_cast<FieldGetMethodSig >(&VisitSubTree::getHandleSubTreeRoot));

    oType.addInitialDesc(pDesc);
}


VisitSubTreeBase::TypeObject VisitSubTreeBase::_type(
    VisitSubTreeBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&VisitSubTreeBase::createEmptyLocal),
    VisitSubTree::initMethod,
    VisitSubTree::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&VisitSubTreeBase::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "        name=\"VisitSubTree\"\n"
    "        parent=\"Group\"\n"
    "        library=\"Group\"\n"
    "        pointerfieldtypes=\"none\"\n"
    "        structure=\"concrete\"\n"
    "        systemcomponent=\"true\"\n"
    "        parentsystemcomponent=\"true\"\n"
    "        decoratable=\"false\"\n"
    "        useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"true\"\n"
    ">\n"
    "VisitSubTree provides a way to point the renderer to another section of the\n"
    "scene graph for rendering. This is useful for multi-pass algorithms using\n"
    "OSG::Stage because it provides a way to render the same graph multiple times\n"
    "without duplicating the nodes.\n"
    "        <Field\n"
    "                name=\"subTreeRoot\"\n"
    "                type=\"Node\"\n"
    "                category=\"weakpointer\"\n"
    "                cardinality=\"single\"\n"
    "                visibility=\"external\"\n"
    "                defaultValue=\"NULL\"\n"
    "                access=\"public\"\n"
    "        >\n"
    "        Reference to the sub-graph to draw in place of this node.\n"
    "        Whatever node is pointed to will be drawn here as if it was duplicated\n"
    "        at this location.\n"
    "        </Field>\n"
    "</FieldContainer>\n",
    "VisitSubTree provides a way to point the renderer to another section of the\n"
    "scene graph for rendering. This is useful for multi-pass algorithms using\n"
    "OSG::Stage because it provides a way to render the same graph multiple times\n"
    "without duplicating the nodes.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &VisitSubTreeBase::getType(void)
{
    return _type;
}

const FieldContainerType &VisitSubTreeBase::getType(void) const
{
    return _type;
}

UInt32 VisitSubTreeBase::getContainerSize(void) const
{
    return sizeof(VisitSubTree);
}

/*------------------------- decorator get ------------------------------*/


//! Get the VisitSubTree::_sfSubTreeRoot field.
const SFWeakNodePtr *VisitSubTreeBase::getSFSubTreeRoot(void) const
{
    return &_sfSubTreeRoot;
}

SFWeakNodePtr       *VisitSubTreeBase::editSFSubTreeRoot    (void)
{
    editSField(SubTreeRootFieldMask);

    return &_sfSubTreeRoot;
}





/*------------------------------ access -----------------------------------*/

UInt32 VisitSubTreeBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (SubTreeRootFieldMask & whichField))
    {
        returnValue += _sfSubTreeRoot.getBinSize();
    }

    return returnValue;
}

void VisitSubTreeBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (SubTreeRootFieldMask & whichField))
    {
        _sfSubTreeRoot.copyToBin(pMem);
    }
}

void VisitSubTreeBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (SubTreeRootFieldMask & whichField))
    {
        _sfSubTreeRoot.copyFromBin(pMem);
    }
}

//! create a new instance of the class
VisitSubTreeTransitPtr VisitSubTreeBase::create(void)
{
    VisitSubTreeTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<VisitSubTree>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
VisitSubTreeTransitPtr VisitSubTreeBase::createLocal(BitVector bFlags)
{
    VisitSubTreeTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<VisitSubTree>(tmpPtr);
    }

    return fc;
}

//! create an empty new instance of the class, do not copy the prototype
VisitSubTree *VisitSubTreeBase::createEmpty(void)
{
    VisitSubTree *returnValue;

    newPtr<VisitSubTree>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &= 
        ~Thread::getCurrentLocalFlags(); 

    return returnValue;
}

VisitSubTree *VisitSubTreeBase::createEmptyLocal(BitVector bFlags)
{
    VisitSubTree *returnValue;

    newPtr<VisitSubTree>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr VisitSubTreeBase::shallowCopy(void) const
{
    VisitSubTree *tmpPtr;

    newPtr(tmpPtr, 
           dynamic_cast<const VisitSubTree *>(this), 
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}

FieldContainerTransitPtr VisitSubTreeBase::shallowCopyLocal(
    BitVector bFlags) const
{
    VisitSubTree *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const VisitSubTree *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

VisitSubTreeBase::VisitSubTreeBase(void) :
    Inherited(),
    _sfSubTreeRoot            (NULL)
{
}

VisitSubTreeBase::VisitSubTreeBase(const VisitSubTreeBase &source) :
    Inherited(source),
    _sfSubTreeRoot            (NULL)
{
}


/*-------------------------- destructors ----------------------------------*/

VisitSubTreeBase::~VisitSubTreeBase(void)
{
}

void VisitSubTreeBase::onCreate(const VisitSubTree *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        VisitSubTree *pThis = static_cast<VisitSubTree *>(this);

        pThis->setSubTreeRoot(source->getSubTreeRoot());
    }
}

GetFieldHandlePtr VisitSubTreeBase::getHandleSubTreeRoot     (void) const
{
    SFWeakNodePtr::GetHandlePtr returnValue(
        new  SFWeakNodePtr::GetHandle(
             &_sfSubTreeRoot, 
             this->getType().getFieldDesc(SubTreeRootFieldId)));

    return returnValue;
}

EditFieldHandlePtr VisitSubTreeBase::editHandleSubTreeRoot    (void)
{
    SFWeakNodePtr::EditHandlePtr returnValue(
        new  SFWeakNodePtr::EditHandle(
             &_sfSubTreeRoot, 
             this->getType().getFieldDesc(SubTreeRootFieldId)));

    returnValue->setSetMethod(boost::bind(&VisitSubTree::setSubTreeRoot, 
                                          static_cast<VisitSubTree *>(this), _1));

    editSField(SubTreeRootFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void VisitSubTreeBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<VisitSubTreeBase *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *VisitSubTreeBase::createAspectCopy(void) const
{
    VisitSubTree *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const VisitSubTree *>(this));

    return returnValue;
}
#endif

void VisitSubTreeBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<VisitSubTree *>(this)->setSubTreeRoot(NULL);


}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<VisitSubTree *>::_type("VisitSubTreePtr", "GroupPtr");
#endif


OSG_END_NAMESPACE
