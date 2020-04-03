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
 **     class DescMaterialShaderCodeGenerator!
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




#include "OSGDescMaterialShaderCodeGeneratorBase.h"
#include "OSGDescMaterialShaderCodeGenerator.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DescMaterialShaderCodeGenerator
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<DescMaterialShaderCodeGenerator *, nsOSG>::_type(
    "DescMaterialShaderCodeGeneratorPtr", 
    "ShaderCodeGeneratorPtr", 
    DescMaterialShaderCodeGenerator::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(DescMaterialShaderCodeGenerator *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           DescMaterialShaderCodeGenerator *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           DescMaterialShaderCodeGenerator *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void DescMaterialShaderCodeGeneratorBase::classDescInserter(TypeObject &oType)
{
}


DescMaterialShaderCodeGeneratorBase::TypeObject DescMaterialShaderCodeGeneratorBase::_type(
    DescMaterialShaderCodeGeneratorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&DescMaterialShaderCodeGeneratorBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&DescMaterialShaderCodeGenerator::initMethod),
    reinterpret_cast<ExitContainerF>(&DescMaterialShaderCodeGenerator::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&DescMaterialShaderCodeGenerator::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"DescMaterialShaderCodeGenerator\"\n"
    "    parent=\"ShaderCodeGenerator\"\n"
    "    library=\"ContribTechniques\"\n"
    "    structure=\"concrete\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    >\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &DescMaterialShaderCodeGeneratorBase::getType(void)
{
    return _type;
}

const FieldContainerType &DescMaterialShaderCodeGeneratorBase::getType(void) const
{
    return _type;
}

UInt32 DescMaterialShaderCodeGeneratorBase::getContainerSize(void) const
{
    return sizeof(DescMaterialShaderCodeGenerator);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

SizeT DescMaterialShaderCodeGeneratorBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void DescMaterialShaderCodeGeneratorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void DescMaterialShaderCodeGeneratorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
DescMaterialShaderCodeGeneratorTransitPtr DescMaterialShaderCodeGeneratorBase::createLocal(BitVector bFlags)
{
    DescMaterialShaderCodeGeneratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<DescMaterialShaderCodeGenerator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
DescMaterialShaderCodeGeneratorTransitPtr DescMaterialShaderCodeGeneratorBase::createDependent(BitVector bFlags)
{
    DescMaterialShaderCodeGeneratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<DescMaterialShaderCodeGenerator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
DescMaterialShaderCodeGeneratorTransitPtr DescMaterialShaderCodeGeneratorBase::create(void)
{
    DescMaterialShaderCodeGeneratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<DescMaterialShaderCodeGenerator>(tmpPtr);
    }

    return fc;
}

DescMaterialShaderCodeGenerator *DescMaterialShaderCodeGeneratorBase::createEmptyLocal(BitVector bFlags)
{
    DescMaterialShaderCodeGenerator *returnValue;

    newPtr<DescMaterialShaderCodeGenerator>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
DescMaterialShaderCodeGenerator *DescMaterialShaderCodeGeneratorBase::createEmpty(void)
{
    DescMaterialShaderCodeGenerator *returnValue;

    newPtr<DescMaterialShaderCodeGenerator>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr DescMaterialShaderCodeGeneratorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    DescMaterialShaderCodeGenerator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DescMaterialShaderCodeGenerator *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr DescMaterialShaderCodeGeneratorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    DescMaterialShaderCodeGenerator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DescMaterialShaderCodeGenerator *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr DescMaterialShaderCodeGeneratorBase::shallowCopy(void) const
{
    DescMaterialShaderCodeGenerator *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const DescMaterialShaderCodeGenerator *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

DescMaterialShaderCodeGeneratorBase::DescMaterialShaderCodeGeneratorBase(void) :
    Inherited()
{
}

DescMaterialShaderCodeGeneratorBase::DescMaterialShaderCodeGeneratorBase(const DescMaterialShaderCodeGeneratorBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

DescMaterialShaderCodeGeneratorBase::~DescMaterialShaderCodeGeneratorBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void DescMaterialShaderCodeGeneratorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    DescMaterialShaderCodeGenerator *pThis = static_cast<DescMaterialShaderCodeGenerator *>(this);

    pThis->execSync(static_cast<DescMaterialShaderCodeGenerator *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *DescMaterialShaderCodeGeneratorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    DescMaterialShaderCodeGenerator *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const DescMaterialShaderCodeGenerator *>(pRefAspect),
                  dynamic_cast<const DescMaterialShaderCodeGenerator *>(this));

    return returnValue;
}
#endif

void DescMaterialShaderCodeGeneratorBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
