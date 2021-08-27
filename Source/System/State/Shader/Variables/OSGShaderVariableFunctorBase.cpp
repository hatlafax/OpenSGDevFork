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
 **     class ShaderVariableFunctor!
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




#include "OSGShaderVariableFunctorBase.h"
#include "OSGShaderVariableFunctor.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ShaderVariableFunctor
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<ShaderVariableFunctor *, nsOSG>::_type(
    "ShaderVariableFunctorPtr", 
    "ShaderProcVariablePtr", 
    ShaderVariableFunctor::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(ShaderVariableFunctor *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ShaderVariableFunctor *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ShaderVariableFunctor *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ShaderVariableFunctorBase::classDescInserter(TypeObject &oType)
{
}


ShaderVariableFunctorBase::TypeObject ShaderVariableFunctorBase::_type(
    ShaderVariableFunctorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&ShaderVariableFunctorBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&ShaderVariableFunctor::initMethod),
    reinterpret_cast<ExitContainerF>(&ShaderVariableFunctor::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&ShaderVariableFunctor::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"ShaderVariableFunctor\"\n"
    "   parent=\"ShaderProcVariable\"\n"
    "   library=\"System\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   docGroupBase=\"GrpSystemShader\"\n"
    "   >\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ShaderVariableFunctorBase::getType(void)
{
    return _type;
}

const FieldContainerType &ShaderVariableFunctorBase::getType(void) const
{
    return _type;
}

UInt32 ShaderVariableFunctorBase::getContainerSize(void) const
{
    return sizeof(ShaderVariableFunctor);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

SizeT ShaderVariableFunctorBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void ShaderVariableFunctorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void ShaderVariableFunctorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
ShaderVariableFunctorTransitPtr ShaderVariableFunctorBase::createLocal(BitVector bFlags)
{
    ShaderVariableFunctorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ShaderVariableFunctor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ShaderVariableFunctorTransitPtr ShaderVariableFunctorBase::createDependent(BitVector bFlags)
{
    ShaderVariableFunctorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ShaderVariableFunctor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ShaderVariableFunctorTransitPtr ShaderVariableFunctorBase::create(void)
{
    ShaderVariableFunctorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ShaderVariableFunctor>(tmpPtr);
    }

    return fc;
}

ShaderVariableFunctor *ShaderVariableFunctorBase::createEmptyLocal(BitVector bFlags)
{
    ShaderVariableFunctor *returnValue;

    newPtr<ShaderVariableFunctor>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ShaderVariableFunctor *ShaderVariableFunctorBase::createEmpty(void)
{
    ShaderVariableFunctor *returnValue;

    newPtr<ShaderVariableFunctor>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr ShaderVariableFunctorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ShaderVariableFunctor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShaderVariableFunctor *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShaderVariableFunctorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ShaderVariableFunctor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ShaderVariableFunctor *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ShaderVariableFunctorBase::shallowCopy(void) const
{
    ShaderVariableFunctor *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const ShaderVariableFunctor *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

ShaderVariableFunctorBase::ShaderVariableFunctorBase(void) :
    Inherited()
{
}

ShaderVariableFunctorBase::ShaderVariableFunctorBase(const ShaderVariableFunctorBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

ShaderVariableFunctorBase::~ShaderVariableFunctorBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void ShaderVariableFunctorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ShaderVariableFunctor *pThis = static_cast<ShaderVariableFunctor *>(this);

    pThis->execSync(static_cast<ShaderVariableFunctor *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ShaderVariableFunctorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ShaderVariableFunctor *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ShaderVariableFunctor *>(pRefAspect),
                  dynamic_cast<const ShaderVariableFunctor *>(this));

    return returnValue;
}
#endif

void ShaderVariableFunctorBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
