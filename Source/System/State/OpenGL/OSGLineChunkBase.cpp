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
 **     class LineChunk!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"


#include "OSGGL.h"                        // Smooth default header


#include "OSGLineChunkBase.h"
#include "OSGLineChunk.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::LineChunk
    See \ref PageSystemLineChunk for a description.

    The line chunk contains the parameters that are specific to lines.

    The parameters of the following functions are wrapped here: glLineWidth
    (OSG::LineChunk::_sfWidth), glLineStipple (OSG::LineChunk::_sfStippleRepeat,
    OSG::LineChunk::_sfStipplePattern), glEnable(GL_LINE_SMOOTH)
    (OSG::LineChunk::_sfSmooth).
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Real32          LineChunkBase::_sfWidth
    The line's width, in pixels.
*/

/*! \var Int32           LineChunkBase::_sfStippleRepeat
    Repetition factor for stippling.
*/

/*! \var UInt16          LineChunkBase::_sfStipplePattern
    Defines the stipple pattern. 1 bits are drawn, 0 bits are ignored, 
    starting with the most significant bit.
*/

/*! \var bool            LineChunkBase::_sfSmooth
    Defines if line antialiasing is used.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<LineChunk *, nsOSG>::_type("LineChunkPtr", "StateChunkPtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(LineChunk *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           LineChunk *,
                           nsOSG);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           LineChunk *,
                           nsOSG);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void LineChunkBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "width",
        "The line's width, in pixels.\n",
        WidthFieldId, WidthFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&LineChunk::editHandleWidth),
        static_cast<FieldGetMethodSig >(&LineChunk::getHandleWidth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "stippleRepeat",
        "Repetition factor for stippling.\n",
        StippleRepeatFieldId, StippleRepeatFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&LineChunk::editHandleStippleRepeat),
        static_cast<FieldGetMethodSig >(&LineChunk::getHandleStippleRepeat));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt16::Description(
        SFUInt16::getClassType(),
        "stipplePattern",
        "Defines the stipple pattern. 1 bits are drawn, 0 bits are ignored, \n"
        "starting with the most significant bit.\n",
        StipplePatternFieldId, StipplePatternFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&LineChunk::editHandleStipplePattern),
        static_cast<FieldGetMethodSig >(&LineChunk::getHandleStipplePattern));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "smooth",
        "Defines if line antialiasing is used.\n",
        SmoothFieldId, SmoothFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&LineChunk::editHandleSmooth),
        static_cast<FieldGetMethodSig >(&LineChunk::getHandleSmooth));

    oType.addInitialDesc(pDesc);
}


LineChunkBase::TypeObject LineChunkBase::_type(
    LineChunkBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&LineChunkBase::createEmptyLocal),
    LineChunk::initMethod,
    LineChunk::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&LineChunk::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"LineChunk\"\n"
    "   parent=\"StateChunk\"\n"
    "   library=\"State\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   docGroupBase=\"GrpStateOpenGL\"\n"
    "   >\n"
    "  See \\ref PageSystemLineChunk for a description.\n"
    "\n"
    "  The line chunk contains the parameters that are specific to lines.\n"
    "\n"
    "  The parameters of the following functions are wrapped here: glLineWidth\n"
    "  (OSG::LineChunk::_sfWidth), glLineStipple (OSG::LineChunk::_sfStippleRepeat,\n"
    "  OSG::LineChunk::_sfStipplePattern), glEnable(GL_LINE_SMOOTH)\n"
    "  (OSG::LineChunk::_sfSmooth).\n"
    "  <Field\n"
    "\t name=\"width\"\n"
    "\t type=\"Real32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"1\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "    The line's width, in pixels.\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"stippleRepeat\"\n"
    "\t type=\"Int32\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"1\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "    Repetition factor for stippling.\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"stipplePattern\"\n"
    "\t type=\"UInt16\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"0xffff\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tDefines the stipple pattern. 1 bits are drawn, 0 bits are ignored, \n"
    "    starting with the most significant bit.\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"smooth\"\n"
    "\t type=\"bool\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"GL_FALSE\"\n"
    "\t defaultHeader=\"&quot;OSGGL.h&quot;\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tDefines if line antialiasing is used.\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    "See \\ref PageSystemLineChunk for a description.\n"
    "\n"
    "The line chunk contains the parameters that are specific to lines.\n"
    "\n"
    "The parameters of the following functions are wrapped here: glLineWidth\n"
    "(OSG::LineChunk::_sfWidth), glLineStipple (OSG::LineChunk::_sfStippleRepeat,\n"
    "OSG::LineChunk::_sfStipplePattern), glEnable(GL_LINE_SMOOTH)\n"
    "(OSG::LineChunk::_sfSmooth).\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &LineChunkBase::getType(void)
{
    return _type;
}

const FieldContainerType &LineChunkBase::getType(void) const
{
    return _type;
}

UInt32 LineChunkBase::getContainerSize(void) const
{
    return sizeof(LineChunk);
}

/*------------------------- decorator get ------------------------------*/


SFReal32 *LineChunkBase::editSFWidth(void)
{
    editSField(WidthFieldMask);

    return &_sfWidth;
}

const SFReal32 *LineChunkBase::getSFWidth(void) const
{
    return &_sfWidth;
}


SFInt32 *LineChunkBase::editSFStippleRepeat(void)
{
    editSField(StippleRepeatFieldMask);

    return &_sfStippleRepeat;
}

const SFInt32 *LineChunkBase::getSFStippleRepeat(void) const
{
    return &_sfStippleRepeat;
}


SFUInt16 *LineChunkBase::editSFStipplePattern(void)
{
    editSField(StipplePatternFieldMask);

    return &_sfStipplePattern;
}

const SFUInt16 *LineChunkBase::getSFStipplePattern(void) const
{
    return &_sfStipplePattern;
}


SFBool *LineChunkBase::editSFSmooth(void)
{
    editSField(SmoothFieldMask);

    return &_sfSmooth;
}

const SFBool *LineChunkBase::getSFSmooth(void) const
{
    return &_sfSmooth;
}






/*------------------------------ access -----------------------------------*/

UInt32 LineChunkBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        returnValue += _sfWidth.getBinSize();
    }
    if(FieldBits::NoField != (StippleRepeatFieldMask & whichField))
    {
        returnValue += _sfStippleRepeat.getBinSize();
    }
    if(FieldBits::NoField != (StipplePatternFieldMask & whichField))
    {
        returnValue += _sfStipplePattern.getBinSize();
    }
    if(FieldBits::NoField != (SmoothFieldMask & whichField))
    {
        returnValue += _sfSmooth.getBinSize();
    }

    return returnValue;
}

void LineChunkBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        _sfWidth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (StippleRepeatFieldMask & whichField))
    {
        _sfStippleRepeat.copyToBin(pMem);
    }
    if(FieldBits::NoField != (StipplePatternFieldMask & whichField))
    {
        _sfStipplePattern.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SmoothFieldMask & whichField))
    {
        _sfSmooth.copyToBin(pMem);
    }
}

void LineChunkBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (WidthFieldMask & whichField))
    {
        editSField(WidthFieldMask);
        _sfWidth.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (StippleRepeatFieldMask & whichField))
    {
        editSField(StippleRepeatFieldMask);
        _sfStippleRepeat.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (StipplePatternFieldMask & whichField))
    {
        editSField(StipplePatternFieldMask);
        _sfStipplePattern.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SmoothFieldMask & whichField))
    {
        editSField(SmoothFieldMask);
        _sfSmooth.copyFromBin(pMem);
    }
}

//! create a new instance of the class
LineChunkTransitPtr LineChunkBase::createLocal(BitVector bFlags)
{
    LineChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<LineChunk>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
LineChunkTransitPtr LineChunkBase::createDependent(BitVector bFlags)
{
    LineChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<LineChunk>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
LineChunkTransitPtr LineChunkBase::create(void)
{
    LineChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<LineChunk>(tmpPtr);
    }

    return fc;
}

LineChunk *LineChunkBase::createEmptyLocal(BitVector bFlags)
{
    LineChunk *returnValue;

    newPtr<LineChunk>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
LineChunk *LineChunkBase::createEmpty(void)
{
    LineChunk *returnValue;

    newPtr<LineChunk>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr LineChunkBase::shallowCopyLocal(
    BitVector bFlags) const
{
    LineChunk *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const LineChunk *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr LineChunkBase::shallowCopyDependent(
    BitVector bFlags) const
{
    LineChunk *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const LineChunk *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr LineChunkBase::shallowCopy(void) const
{
    LineChunk *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const LineChunk *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

LineChunkBase::LineChunkBase(void) :
    Inherited(),
    _sfWidth                  (Real32(1)),
    _sfStippleRepeat          (Int32(1)),
    _sfStipplePattern         (UInt16(0xffff)),
    _sfSmooth                 (bool(GL_FALSE))
{
}

LineChunkBase::LineChunkBase(const LineChunkBase &source) :
    Inherited(source),
    _sfWidth                  (source._sfWidth                  ),
    _sfStippleRepeat          (source._sfStippleRepeat          ),
    _sfStipplePattern         (source._sfStipplePattern         ),
    _sfSmooth                 (source._sfSmooth                 )
{
}


/*-------------------------- destructors ----------------------------------*/

LineChunkBase::~LineChunkBase(void)
{
}


GetFieldHandlePtr LineChunkBase::getHandleWidth           (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfWidth,
             this->getType().getFieldDesc(WidthFieldId),
             const_cast<LineChunkBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr LineChunkBase::editHandleWidth          (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfWidth,
             this->getType().getFieldDesc(WidthFieldId),
             this));


    editSField(WidthFieldMask);

    return returnValue;
}

GetFieldHandlePtr LineChunkBase::getHandleStippleRepeat   (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfStippleRepeat,
             this->getType().getFieldDesc(StippleRepeatFieldId),
             const_cast<LineChunkBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr LineChunkBase::editHandleStippleRepeat  (void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfStippleRepeat,
             this->getType().getFieldDesc(StippleRepeatFieldId),
             this));


    editSField(StippleRepeatFieldMask);

    return returnValue;
}

GetFieldHandlePtr LineChunkBase::getHandleStipplePattern  (void) const
{
    SFUInt16::GetHandlePtr returnValue(
        new  SFUInt16::GetHandle(
             &_sfStipplePattern,
             this->getType().getFieldDesc(StipplePatternFieldId),
             const_cast<LineChunkBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr LineChunkBase::editHandleStipplePattern (void)
{
    SFUInt16::EditHandlePtr returnValue(
        new  SFUInt16::EditHandle(
             &_sfStipplePattern,
             this->getType().getFieldDesc(StipplePatternFieldId),
             this));


    editSField(StipplePatternFieldMask);

    return returnValue;
}

GetFieldHandlePtr LineChunkBase::getHandleSmooth          (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfSmooth,
             this->getType().getFieldDesc(SmoothFieldId),
             const_cast<LineChunkBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr LineChunkBase::editHandleSmooth         (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfSmooth,
             this->getType().getFieldDesc(SmoothFieldId),
             this));


    editSField(SmoothFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void LineChunkBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    LineChunk *pThis = static_cast<LineChunk *>(this);

    pThis->execSync(static_cast<LineChunk *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *LineChunkBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    LineChunk *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const LineChunk *>(pRefAspect),
                  dynamic_cast<const LineChunk *>(this));

    return returnValue;
}
#endif

void LineChunkBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
