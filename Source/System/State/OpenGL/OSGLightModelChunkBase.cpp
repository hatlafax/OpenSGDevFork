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
 **     class LightModelChunk!
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


#include "OSGGLEXT.h"                     // ColorControl default header


#include "OSGLightModelChunkBase.h"
#include "OSGLightModelChunk.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::LightModelChunk
    The LightModelChunk wraps most of glLightModel. It does not wrap
    GL_LIGHT_MODEL_TWO_SIDE, which is wrapped by TwoSidedLightingChunk. 
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Color4f         LightModelChunkBase::_sfAmbient
    GL_LIGHT_MODEL_AMBIENT is set to this color.
*/

/*! \var GLenum          LightModelChunkBase::_sfColorControl
    GL_LIGHT_MODEL_COLOR_CONTROL is set to this value.  Legal values are
    directly taken from the glLightModel() manpage. 
*/

/*! \var bool            LightModelChunkBase::_sfLocalViewer
    GL_LIGHT_MODEL_LOCAL_VIEWER is activated by this bool.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<LightModelChunk *, nsOSG>::_type(
    "LightModelChunkPtr", 
    "StateChunkPtr", 
    LightModelChunk::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(LightModelChunk *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           LightModelChunk *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           LightModelChunk *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void LightModelChunkBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFColor4f::Description(
        SFColor4f::getClassType(),
        "ambient",
        "GL_LIGHT_MODEL_AMBIENT is set to this color.\n",
        AmbientFieldId, AmbientFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&LightModelChunk::editHandleAmbient),
        static_cast<FieldGetMethodSig >(&LightModelChunk::getHandleAmbient));

    oType.addInitialDesc(pDesc);

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(),
        "colorControl",
        "GL_LIGHT_MODEL_COLOR_CONTROL is set to this value.  Legal values are\n"
        "directly taken from the glLightModel() manpage. \n",
        ColorControlFieldId, ColorControlFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&LightModelChunk::editHandleColorControl),
        static_cast<FieldGetMethodSig >(&LightModelChunk::getHandleColorControl));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "localViewer",
        "GL_LIGHT_MODEL_LOCAL_VIEWER is activated by this bool.\n",
        LocalViewerFieldId, LocalViewerFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&LightModelChunk::editHandleLocalViewer),
        static_cast<FieldGetMethodSig >(&LightModelChunk::getHandleLocalViewer));

    oType.addInitialDesc(pDesc);
}


LightModelChunkBase::TypeObject LightModelChunkBase::_type(
    LightModelChunkBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&LightModelChunkBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&LightModelChunk::initMethod),
    reinterpret_cast<ExitContainerF>(&LightModelChunk::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&LightModelChunk::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"LightModelChunk\"\n"
    "   parent=\"StateChunk\"\n"
    "   library=\"State\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   decoratable=\"false\"\n"
    "   useLocalIncludes=\"false\"\n"
    "   docGroupBase=\"GrpStateOpenGL\"\n"
    "   >\n"
    "  The LightModelChunk wraps most of glLightModel. It does not wrap\n"
    "  GL_LIGHT_MODEL_TWO_SIDE, which is wrapped by TwoSidedLightingChunk. \n"
    "  <Field\n"
    "\t name=\"ambient\"\n"
    "\t type=\"Color4f\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"0.2f, 0.2f, 0.2f, 1.0f\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tGL_LIGHT_MODEL_AMBIENT is set to this color.\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"colorControl\"\n"
    "\t type=\"GLenum\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"GL_SINGLE_COLOR\"\n"
    "\t defaultHeader=\"&quot;OSGGLEXT.h&quot;\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tGL_LIGHT_MODEL_COLOR_CONTROL is set to this value.  Legal values are\n"
    "\tdirectly taken from the glLightModel() manpage. \n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"localViewer\"\n"
    "\t type=\"bool\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"false\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tGL_LIGHT_MODEL_LOCAL_VIEWER is activated by this bool.\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    "The LightModelChunk wraps most of glLightModel. It does not wrap\n"
    "GL_LIGHT_MODEL_TWO_SIDE, which is wrapped by TwoSidedLightingChunk. \n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &LightModelChunkBase::getType(void)
{
    return _type;
}

const FieldContainerType &LightModelChunkBase::getType(void) const
{
    return _type;
}

UInt32 LightModelChunkBase::getContainerSize(void) const
{
    return sizeof(LightModelChunk);
}

/*------------------------- decorator get ------------------------------*/


SFColor4f *LightModelChunkBase::editSFAmbient(void)
{
    editSField(AmbientFieldMask);

    return &_sfAmbient;
}

const SFColor4f *LightModelChunkBase::getSFAmbient(void) const
{
    return &_sfAmbient;
}


SFGLenum *LightModelChunkBase::editSFColorControl(void)
{
    editSField(ColorControlFieldMask);

    return &_sfColorControl;
}

const SFGLenum *LightModelChunkBase::getSFColorControl(void) const
{
    return &_sfColorControl;
}


SFBool *LightModelChunkBase::editSFLocalViewer(void)
{
    editSField(LocalViewerFieldMask);

    return &_sfLocalViewer;
}

const SFBool *LightModelChunkBase::getSFLocalViewer(void) const
{
    return &_sfLocalViewer;
}






/*------------------------------ access -----------------------------------*/

SizeT LightModelChunkBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (AmbientFieldMask & whichField))
    {
        returnValue += _sfAmbient.getBinSize();
    }
    if(FieldBits::NoField != (ColorControlFieldMask & whichField))
    {
        returnValue += _sfColorControl.getBinSize();
    }
    if(FieldBits::NoField != (LocalViewerFieldMask & whichField))
    {
        returnValue += _sfLocalViewer.getBinSize();
    }

    return returnValue;
}

void LightModelChunkBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (AmbientFieldMask & whichField))
    {
        _sfAmbient.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ColorControlFieldMask & whichField))
    {
        _sfColorControl.copyToBin(pMem);
    }
    if(FieldBits::NoField != (LocalViewerFieldMask & whichField))
    {
        _sfLocalViewer.copyToBin(pMem);
    }
}

void LightModelChunkBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (AmbientFieldMask & whichField))
    {
        editSField(AmbientFieldMask);
        _sfAmbient.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ColorControlFieldMask & whichField))
    {
        editSField(ColorControlFieldMask);
        _sfColorControl.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (LocalViewerFieldMask & whichField))
    {
        editSField(LocalViewerFieldMask);
        _sfLocalViewer.copyFromBin(pMem);
    }
}

//! create a new instance of the class
LightModelChunkTransitPtr LightModelChunkBase::createLocal(BitVector bFlags)
{
    LightModelChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<LightModelChunk>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
LightModelChunkTransitPtr LightModelChunkBase::createDependent(BitVector bFlags)
{
    LightModelChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<LightModelChunk>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
LightModelChunkTransitPtr LightModelChunkBase::create(void)
{
    LightModelChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<LightModelChunk>(tmpPtr);
    }

    return fc;
}

LightModelChunk *LightModelChunkBase::createEmptyLocal(BitVector bFlags)
{
    LightModelChunk *returnValue;

    newPtr<LightModelChunk>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
LightModelChunk *LightModelChunkBase::createEmpty(void)
{
    LightModelChunk *returnValue;

    newPtr<LightModelChunk>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr LightModelChunkBase::shallowCopyLocal(
    BitVector bFlags) const
{
    LightModelChunk *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const LightModelChunk *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr LightModelChunkBase::shallowCopyDependent(
    BitVector bFlags) const
{
    LightModelChunk *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const LightModelChunk *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr LightModelChunkBase::shallowCopy(void) const
{
    LightModelChunk *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const LightModelChunk *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

LightModelChunkBase::LightModelChunkBase(void) :
    Inherited(),
    _sfAmbient                (Color4f(0.2f, 0.2f, 0.2f, 1.0f)),
    _sfColorControl           (GLenum(GL_SINGLE_COLOR)),
    _sfLocalViewer            (bool(false))
{
}

LightModelChunkBase::LightModelChunkBase(const LightModelChunkBase &source) :
    Inherited(source),
    _sfAmbient                (source._sfAmbient                ),
    _sfColorControl           (source._sfColorControl           ),
    _sfLocalViewer            (source._sfLocalViewer            )
{
}


/*-------------------------- destructors ----------------------------------*/

LightModelChunkBase::~LightModelChunkBase(void)
{
}


GetFieldHandlePtr LightModelChunkBase::getHandleAmbient         (void) const
{
    SFColor4f::GetHandlePtr returnValue(
        new  SFColor4f::GetHandle(
             &_sfAmbient,
             this->getType().getFieldDesc(AmbientFieldId),
             const_cast<LightModelChunkBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr LightModelChunkBase::editHandleAmbient        (void)
{
    SFColor4f::EditHandlePtr returnValue(
        new  SFColor4f::EditHandle(
             &_sfAmbient,
             this->getType().getFieldDesc(AmbientFieldId),
             this));


    editSField(AmbientFieldMask);

    return returnValue;
}

GetFieldHandlePtr LightModelChunkBase::getHandleColorControl    (void) const
{
    SFGLenum::GetHandlePtr returnValue(
        new  SFGLenum::GetHandle(
             &_sfColorControl,
             this->getType().getFieldDesc(ColorControlFieldId),
             const_cast<LightModelChunkBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr LightModelChunkBase::editHandleColorControl   (void)
{
    SFGLenum::EditHandlePtr returnValue(
        new  SFGLenum::EditHandle(
             &_sfColorControl,
             this->getType().getFieldDesc(ColorControlFieldId),
             this));


    editSField(ColorControlFieldMask);

    return returnValue;
}

GetFieldHandlePtr LightModelChunkBase::getHandleLocalViewer     (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfLocalViewer,
             this->getType().getFieldDesc(LocalViewerFieldId),
             const_cast<LightModelChunkBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr LightModelChunkBase::editHandleLocalViewer    (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfLocalViewer,
             this->getType().getFieldDesc(LocalViewerFieldId),
             this));


    editSField(LocalViewerFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void LightModelChunkBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    LightModelChunk *pThis = static_cast<LightModelChunk *>(this);

    pThis->execSync(static_cast<LightModelChunk *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *LightModelChunkBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    LightModelChunk *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const LightModelChunk *>(pRefAspect),
                  dynamic_cast<const LightModelChunk *>(this));

    return returnValue;
}
#endif

void LightModelChunkBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
