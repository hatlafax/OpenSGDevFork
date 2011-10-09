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
 **     class HardwareContext!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"




#include "OSGHardwareContextBase.h"
#include "OSGHardwareContext.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::HardwareContext
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<HardwareContext *, nsOSG>::_type("HardwareContextPtr", "AttachmentContainerPtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(HardwareContext *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           HardwareContext *,
                           nsOSG);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           HardwareContext *,
                           nsOSG);

DataType &FieldTraits< HardwareContext *, nsOSG + 1 >::getType(void)
{
    return FieldTraits<HardwareContext *, nsOSG>::getType();
}


OSG_EXPORT_PTR_SFIELD(ChildPointerSField,
                      HardwareContext *,
                      UnrecordedRefCountPolicy,
                      nsOSG + 1);


OSG_EXPORT_PTR_MFIELD(ChildPointerMField,
                      HardwareContext *,
                      UnrecordedRefCountPolicy,
                      nsOSG + 1);


DataType &FieldTraits<HardwareContext *, nsOSG + 2 >::getType(void)
{
    return FieldTraits<HardwareContext *, nsOSG>::getType();
}


OSG_SFIELDTYPE_INST(ParentPointerSField,
                    HardwareContext *,
                    NoRefCountPolicy,
                    nsOSG + 2);

OSG_FIELD_DLLEXPORT_DEF3(ParentPointerSField,
                         HardwareContext *,
                         NoRefCountPolicy,
                         nsOSG + 2);


OSG_MFIELDTYPE_INST(ParentPointerMField,
                    HardwareContext *,
                    NoRefCountPolicy,
                    2);

OSG_FIELD_DLLEXPORT_DEF3(ParentPointerMField,
                         HardwareContext *,
                         NoRefCountPolicy,
                         2);


/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void HardwareContextBase::classDescInserter(TypeObject &oType)
{
    Inherited::classDescInserter(oType);

}


HardwareContextBase::TypeObject HardwareContextBase::_type(
    HardwareContextBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    NULL,
    HardwareContext::initMethod,
    HardwareContext::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&HardwareContext::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"HardwareContext\"\n"
    "   parent=\"AttachmentContainer\"\n"
    "   mixinparent=\"HardwareContextParent\"\n"
    "   library=\"Base\"\n"
    "   structure=\"abstract\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   parentFields=\"both\"\n"
    "   childFields=\"both\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   isNodeCore=\"false\"\n"
    "   docGroupBase=\"GrpBaseHardwareContext\"\n"
    "   >\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &HardwareContextBase::getType(void)
{
    return _type;
}

const FieldContainerType &HardwareContextBase::getType(void) const
{
    return _type;
}

UInt32 HardwareContextBase::getContainerSize(void) const
{
    return sizeof(HardwareContext);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 HardwareContextBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void HardwareContextBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void HardwareContextBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}




/*------------------------- constructors ----------------------------------*/

HardwareContextBase::HardwareContextBase(void) :
    Inherited()
{
}

HardwareContextBase::HardwareContextBase(const HardwareContextBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

HardwareContextBase::~HardwareContextBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void HardwareContextBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    HardwareContext *pThis = static_cast<HardwareContext *>(this);

    pThis->execSync(static_cast<HardwareContext *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void HardwareContextBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
