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
 **     class DistanceLOD!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"




#include "OSGDistanceLODBase.h"
#include "OSGDistanceLOD.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DistanceLOD
    This Node manages the different levels of detail available for a Geometry
    and decides which one should be rendered, according to the distance from the
    current camera. The details of the selection process are taken from VRML97
    standard. 

    The node chooses which child to render based on the range values in the Range
    multi-field and the current distance of the camera from the object.  
    The children should be ordered from the highest level of detail to the 
    lowest level of detail. The range values specify the distances at which to 
    switch between the different children.

    The center field is a translation offset in the local coordinate system that
    specifies the center of the object for distance calculations.  In order to
    calculate which level to display, first the distance from the 
    viewpoint to the center point of the LOD node (with corresponding 
    transformations) is computed.  If the distance is less than the first range
    value, then the first LOD is drawn. If it is between the first and the second
    values, then the second LOD is drawn, and so on.

    \example Setting up a OSG::DistanceLOD

    Here is an example of setting up an lod core with a center and a range.
    You would also need to add children for the 4 LODs.

    \code
    DistanceLOD lod = DistanceLOD::create();

    // this is supposed to be the center of the LOD model,
    // that is, this is the point the distance is measured from
    lod->setCenter(12,1,5);
    // now we add the distances when models will change
    lod->editMFRange()->push_back(6.0);
    lod->editMFRange()->push_back(12.0);
    lod->editMFRange()->push_back(24.0);
    \endcode
    \endexample
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Pnt3f           DistanceLODBase::_sfCenter
    The center for distance calculation.
*/

/*! \var Real32          DistanceLODBase::_mfRange
    The range intervals.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<DistanceLOD *, nsOSG>::_type("DistanceLODPtr", "GroupPtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(DistanceLOD *, nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void DistanceLODBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFPnt3f::Description(
        SFPnt3f::getClassType(),
        "center",
        "The center for distance calculation.\n",
        CenterFieldId, CenterFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DistanceLOD::editHandleCenter),
        static_cast<FieldGetMethodSig >(&DistanceLOD::getHandleCenter));

    oType.addInitialDesc(pDesc);

    pDesc = new MFReal32::Description(
        MFReal32::getClassType(),
        "range",
        "The range intervals.\n",
        RangeFieldId, RangeFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DistanceLOD::editHandleRange),
        static_cast<FieldGetMethodSig >(&DistanceLOD::getHandleRange));

    oType.addInitialDesc(pDesc);
}


DistanceLODBase::TypeObject DistanceLODBase::_type(
    DistanceLODBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&DistanceLODBase::createEmptyLocal),
    DistanceLOD::initMethod,
    DistanceLOD::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&DistanceLOD::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"DistanceLOD\"\n"
    "   parent=\"Group\"\n"
    "   library=\"Group\"\n"
    "   pointerfieldtypes=\"none\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   isNodeCore=\"true\"\n"
    "   docGroupBase=\"GrpGroupMisc\"\n"
    "   ><![CDATA[\n"
    "This Node manages the different levels of detail available for a Geometry\n"
    "and decides which one should be rendered, according to the distance from the\n"
    "current camera. The details of the selection process are taken from VRML97\n"
    "standard. \n"
    "\n"
    "The node chooses which child to render based on the range values in the Range\n"
    "multi-field and the current distance of the camera from the object.  \n"
    "The children should be ordered from the highest level of detail to the \n"
    "lowest level of detail. The range values specify the distances at which to \n"
    "switch between the different children.\n"
    "\n"
    "The center field is a translation offset in the local coordinate system that\n"
    "specifies the center of the object for distance calculations.  In order to\n"
    "calculate which level to display, first the distance from the \n"
    "viewpoint to the center point of the LOD node (with corresponding \n"
    "transformations) is computed.  If the distance is less than the first range\n"
    "value, then the first LOD is drawn. If it is between the first and the second\n"
    "values, then the second LOD is drawn, and so on.\n"
    "\n"
    "\\example Setting up a OSG::DistanceLOD\n"
    "\n"
    "Here is an example of setting up an lod core with a center and a range.\n"
    "You would also need to add children for the 4 LODs.\n"
    "\n"
    "\\code\n"
    "DistanceLOD lod = DistanceLOD::create();\n"
    "\n"
    "// this is supposed to be the center of the LOD model,\n"
    "// that is, this is the point the distance is measured from\n"
    "lod->setCenter(12,1,5);\n"
    "// now we add the distances when models will change\n"
    "lod->editMFRange()->push_back(6.0);\n"
    "lod->editMFRange()->push_back(12.0);\n"
    "lod->editMFRange()->push_back(24.0);\n"
    "\\endcode\n"
    "\\endexample]]>\n"
    "  <Field\n"
    "\t name=\"center\"\n"
    "\t type=\"Pnt3f\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tThe center for distance calculation.\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"range\"\n"
    "\t type=\"Real32\"\n"
    "\t cardinality=\"multi\"\n"
    "\t visibility=\"external\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tThe range intervals.\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    "This Node manages the different levels of detail available for a Geometry\n"
    "and decides which one should be rendered, according to the distance from the\n"
    "current camera. The details of the selection process are taken from VRML97\n"
    "standard. \n"
    "\n"
    "The node chooses which child to render based on the range values in the Range\n"
    "multi-field and the current distance of the camera from the object.  \n"
    "The children should be ordered from the highest level of detail to the \n"
    "lowest level of detail. The range values specify the distances at which to \n"
    "switch between the different children.\n"
    "\n"
    "The center field is a translation offset in the local coordinate system that\n"
    "specifies the center of the object for distance calculations.  In order to\n"
    "calculate which level to display, first the distance from the \n"
    "viewpoint to the center point of the LOD node (with corresponding \n"
    "transformations) is computed.  If the distance is less than the first range\n"
    "value, then the first LOD is drawn. If it is between the first and the second\n"
    "values, then the second LOD is drawn, and so on.\n"
    "\n"
    "\\example Setting up a OSG::DistanceLOD\n"
    "\n"
    "Here is an example of setting up an lod core with a center and a range.\n"
    "You would also need to add children for the 4 LODs.\n"
    "\n"
    "\\code\n"
    "DistanceLOD lod = DistanceLOD::create();\n"
    "\n"
    "// this is supposed to be the center of the LOD model,\n"
    "// that is, this is the point the distance is measured from\n"
    "lod->setCenter(12,1,5);\n"
    "// now we add the distances when models will change\n"
    "lod->editMFRange()->push_back(6.0);\n"
    "lod->editMFRange()->push_back(12.0);\n"
    "lod->editMFRange()->push_back(24.0);\n"
    "\\endcode\n"
    "\\endexample\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &DistanceLODBase::getType(void)
{
    return _type;
}

const FieldContainerType &DistanceLODBase::getType(void) const
{
    return _type;
}

UInt32 DistanceLODBase::getContainerSize(void) const
{
    return sizeof(DistanceLOD);
}

/*------------------------- decorator get ------------------------------*/


SFPnt3f *DistanceLODBase::editSFCenter(void)
{
    editSField(CenterFieldMask);

    return &_sfCenter;
}

const SFPnt3f *DistanceLODBase::getSFCenter(void) const
{
    return &_sfCenter;
}


MFReal32 *DistanceLODBase::editMFRange(void)
{
    editMField(RangeFieldMask, _mfRange);

    return &_mfRange;
}

const MFReal32 *DistanceLODBase::getMFRange(void) const
{
    return &_mfRange;
}






/*------------------------------ access -----------------------------------*/

UInt32 DistanceLODBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        returnValue += _sfCenter.getBinSize();
    }
    if(FieldBits::NoField != (RangeFieldMask & whichField))
    {
        returnValue += _mfRange.getBinSize();
    }

    return returnValue;
}

void DistanceLODBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        _sfCenter.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RangeFieldMask & whichField))
    {
        _mfRange.copyToBin(pMem);
    }
}

void DistanceLODBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (CenterFieldMask & whichField))
    {
        editSField(CenterFieldMask);
        _sfCenter.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RangeFieldMask & whichField))
    {
        editMField(RangeFieldMask, _mfRange);
        _mfRange.copyFromBin(pMem);
    }
}

//! create a new instance of the class
DistanceLODTransitPtr DistanceLODBase::createLocal(BitVector bFlags)
{
    DistanceLODTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<DistanceLOD>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
DistanceLODTransitPtr DistanceLODBase::createDependent(BitVector bFlags)
{
    DistanceLODTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<DistanceLOD>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
DistanceLODTransitPtr DistanceLODBase::create(void)
{
    DistanceLODTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<DistanceLOD>(tmpPtr);
    }

    return fc;
}

DistanceLOD *DistanceLODBase::createEmptyLocal(BitVector bFlags)
{
    DistanceLOD *returnValue;

    newPtr<DistanceLOD>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
DistanceLOD *DistanceLODBase::createEmpty(void)
{
    DistanceLOD *returnValue;

    newPtr<DistanceLOD>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr DistanceLODBase::shallowCopyLocal(
    BitVector bFlags) const
{
    DistanceLOD *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DistanceLOD *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr DistanceLODBase::shallowCopyDependent(
    BitVector bFlags) const
{
    DistanceLOD *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DistanceLOD *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr DistanceLODBase::shallowCopy(void) const
{
    DistanceLOD *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const DistanceLOD *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

DistanceLODBase::DistanceLODBase(void) :
    Inherited(),
    _sfCenter                 (),
    _mfRange                  ()
{
}

DistanceLODBase::DistanceLODBase(const DistanceLODBase &source) :
    Inherited(source),
    _sfCenter                 (source._sfCenter                 ),
    _mfRange                  (source._mfRange                  )
{
}


/*-------------------------- destructors ----------------------------------*/

DistanceLODBase::~DistanceLODBase(void)
{
}


GetFieldHandlePtr DistanceLODBase::getHandleCenter          (void) const
{
    SFPnt3f::GetHandlePtr returnValue(
        new  SFPnt3f::GetHandle(
             &_sfCenter,
             this->getType().getFieldDesc(CenterFieldId),
             const_cast<DistanceLODBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DistanceLODBase::editHandleCenter         (void)
{
    SFPnt3f::EditHandlePtr returnValue(
        new  SFPnt3f::EditHandle(
             &_sfCenter,
             this->getType().getFieldDesc(CenterFieldId),
             this));


    editSField(CenterFieldMask);

    return returnValue;
}

GetFieldHandlePtr DistanceLODBase::getHandleRange           (void) const
{
    MFReal32::GetHandlePtr returnValue(
        new  MFReal32::GetHandle(
             &_mfRange,
             this->getType().getFieldDesc(RangeFieldId),
             const_cast<DistanceLODBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DistanceLODBase::editHandleRange          (void)
{
    MFReal32::EditHandlePtr returnValue(
        new  MFReal32::EditHandle(
             &_mfRange,
             this->getType().getFieldDesc(RangeFieldId),
             this));


    editMField(RangeFieldMask, _mfRange);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void DistanceLODBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    DistanceLOD *pThis = static_cast<DistanceLOD *>(this);

    pThis->execSync(static_cast<DistanceLOD *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *DistanceLODBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    DistanceLOD *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const DistanceLOD *>(pRefAspect),
                  dynamic_cast<const DistanceLOD *>(this));

    return returnValue;
}
#endif

void DistanceLODBase::resolveLinks(void)
{
    Inherited::resolveLinks();

#ifdef OSG_MT_CPTR_ASPECT
    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);
#endif

#ifdef OSG_MT_CPTR_ASPECT
    _mfRange.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
}


OSG_END_NAMESPACE
