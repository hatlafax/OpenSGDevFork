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
 **     class Viewport!
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



#include "OSGFieldContainer.h"          // Parent Class
#include "OSGCamera.h"                  // Camera Class
#include "OSGNode.h"                    // Root Class
#include "OSGBackground.h"              // Background Class
#include "OSGForeground.h"              // Foregrounds Class

#include "OSGViewportBase.h"
#include "OSGViewport.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Viewport
    A Viewport is a part of the Window it is attached to used for rendering. See
    \ref PageSystemWindowViewports for a description.

    The size of the viewport is defined by the _sfLeft, _sfRight, _sfBottom and
    _sfTop Fields. The Window this Viewport is attached is stored in _sfWindow.
    _sfBackground defines the background clearing method, the
    _sfRoot and _sfCamera Fields the scene being rendered and the camera used to
    view it. The optional _mfForegrounds define which information are added or
    actions are executed after the Viewport has been rendered.

    \ext

    To create a new Viewport the draw and render methods should be overridden. 

    \endext

    \dev

    When adding fields to the Viewport, make sure to add the code to copy them to
    all the different ClusterWindows!

    \enddev
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var FieldContainer * ViewportBase::_sfParent
    The Window this viewport is contained in.
*/

/*! \var Camera *        ViewportBase::_sfCamera
    The Camera used to render the viewport.
*/

/*! \var Node *          ViewportBase::_sfRoot
    The root of the tree that is displayed in this viewport.
*/

/*! \var Background *    ViewportBase::_sfBackground
    The background used to clear this viewport.
*/

/*! \var Foreground *    ViewportBase::_mfForegrounds
    The foreground additions to the rendered image.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<Viewport *, nsOSG>::_type(
    "ViewportPtr", 
    "ViewareaPtr", 
    Viewport::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(Viewport *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           Viewport *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           Viewport *,
                           nsOSG)

DataType &FieldTraits< Viewport *, nsOSG + 1 >::getType(void)
{
    return FieldTraits<Viewport *, nsOSG>::getType();
}


OSG_EXPORT_PTR_MFIELD(ChildPointerMField,
                      Viewport *,
                      UnrecordedRefCountPolicy,
                      nsOSG + 1)


/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ViewportBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFParentFieldContainerPtr::Description(
        SFParentFieldContainerPtr::getClassType(),
        "parent",
        "The Window this viewport is contained in.\n",
        ParentFieldId, ParentFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast     <FieldEditMethodSig>(&Viewport::invalidEditField),
        static_cast     <FieldGetMethodSig >(&Viewport::invalidGetField));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecCameraPtr::Description(
        SFUnrecCameraPtr::getClassType(),
        "camera",
        "The Camera used to render the viewport.\n",
        CameraFieldId, CameraFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&Viewport::editHandleCamera),
        static_cast<FieldGetMethodSig >(&Viewport::getHandleCamera));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecNodePtr::Description(
        SFUnrecNodePtr::getClassType(),
        "root",
        "The root of the tree that is displayed in this viewport.\n",
        RootFieldId, RootFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&Viewport::editHandleRoot),
        static_cast<FieldGetMethodSig >(&Viewport::getHandleRoot));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecBackgroundPtr::Description(
        SFUnrecBackgroundPtr::getClassType(),
        "background",
        "The background used to clear this viewport.\n",
        BackgroundFieldId, BackgroundFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&Viewport::editHandleBackground),
        static_cast<FieldGetMethodSig >(&Viewport::getHandleBackground));

    oType.addInitialDesc(pDesc);

    pDesc = new MFUnrecForegroundPtr::Description(
        MFUnrecForegroundPtr::getClassType(),
        "foregrounds",
        "The foreground additions to the rendered image.\n",
        ForegroundsFieldId, ForegroundsFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&Viewport::editHandleForegrounds),
        static_cast<FieldGetMethodSig >(&Viewport::getHandleForegrounds));

    oType.addInitialDesc(pDesc);
}


ViewportBase::TypeObject ViewportBase::_type(
    ViewportBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&ViewportBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&Viewport::initMethod),
    reinterpret_cast<ExitContainerF>(&Viewport::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&Viewport::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"Viewport\"\n"
    "   parent=\"Viewarea\"\n"
    "   library=\"System\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   childFields=\"multi\"\n"
    "   docGroupBase=\"GrpSystemWindow\"\n"
    "   >\n"
    "\n"
    "  A Viewport is a part of the Window it is attached to used for rendering. See\n"
    "  \\ref PageSystemWindowViewports for a description.\n"
    "\n"
    "  The size of the viewport is defined by the _sfLeft, _sfRight, _sfBottom and\n"
    "  _sfTop Fields. The Window this Viewport is attached is stored in _sfWindow.\n"
    "  _sfBackground defines the background clearing method, the\n"
    "  _sfRoot and _sfCamera Fields the scene being rendered and the camera used to\n"
    "  view it. The optional _mfForegrounds define which information are added or\n"
    "  actions are executed after the Viewport has been rendered.\n"
    "  \n"
    "  \\ext\n"
    "\n"
    "  To create a new Viewport the draw and render methods should be overridden. \n"
    "  \n"
    "  \\endext\n"
    "  \n"
    "  \\dev\n"
    "\n"
    "  When adding fields to the Viewport, make sure to add the code to copy them to\n"
    "  all the different ClusterWindows!\n"
    "  \n"
    "  \\enddev\n"
    "\n"
    "  <Field\n"
    "      name=\"parent\"\n"
    "      type=\"FieldContainer\"\n"
    "      cardinality=\"single\"\n"
    "      visibility=\"external\"\n"
    "      access=\"none\"\n"
    "      category=\"parentpointer\"\n"
    "       >\n"
    "    The Window this viewport is contained in.\n"
    "  </Field>\n"
    "  <Field\n"
    "      name=\"camera\"\n"
    "      type=\"CameraPtr\"\n"
    "      cardinality=\"single\"\n"
    "      visibility=\"external\"\n"
    "      access=\"public\"\n"
    "      >\n"
    "    The Camera used to render the viewport.\n"
    "  </Field>\n"
    "  <Field\n"
    "      name=\"root\"\n"
    "      type=\"NodePtr\"\n"
    "      cardinality=\"single\"\n"
    "      visibility=\"external\"\n"
    "      access=\"public\"\n"
    "      >\n"
    "    The root of the tree that is displayed in this viewport.\n"
    "  </Field>\n"
    "  <Field\n"
    "      name=\"background\"\n"
    "      type=\"BackgroundPtr\"\n"
    "      cardinality=\"single\"\n"
    "      visibility=\"external\"\n"
    "      access=\"public\"\n"
    "      >\n"
    "    The background used to clear this viewport.\n"
    "  </Field>\n"
    "  <Field\n"
    "      name=\"foregrounds\"\n"
    "      type=\"ForegroundPtr\"\n"
    "      cardinality=\"multi\"\n"
    "      visibility=\"external\"\n"
    "      access=\"public\"\n"
    "      pushToFieldAs=\"addForeground\"\n"
    "      >\n"
    "    The foreground additions to the rendered image.\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    "A Viewport is a part of the Window it is attached to used for rendering. See\n"
    "\\ref PageSystemWindowViewports for a description.\n"
    "\n"
    "The size of the viewport is defined by the _sfLeft, _sfRight, _sfBottom and\n"
    "_sfTop Fields. The Window this Viewport is attached is stored in _sfWindow.\n"
    "_sfBackground defines the background clearing method, the\n"
    "_sfRoot and _sfCamera Fields the scene being rendered and the camera used to\n"
    "view it. The optional _mfForegrounds define which information are added or\n"
    "actions are executed after the Viewport has been rendered.\n"
    "\n"
    "\\ext\n"
    "\n"
    "To create a new Viewport the draw and render methods should be overridden. \n"
    "\n"
    "\\endext\n"
    "\n"
    "\\dev\n"
    "\n"
    "When adding fields to the Viewport, make sure to add the code to copy them to\n"
    "all the different ClusterWindows!\n"
    "\n"
    "\\enddev\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ViewportBase::getType(void)
{
    return _type;
}

const FieldContainerType &ViewportBase::getType(void) const
{
    return _type;
}

UInt32 ViewportBase::getContainerSize(void) const
{
    return sizeof(Viewport);
}

/*------------------------- decorator get ------------------------------*/



//! Get the Viewport::_sfCamera field.
const SFUnrecCameraPtr *ViewportBase::getSFCamera(void) const
{
    return &_sfCamera;
}

SFUnrecCameraPtr    *ViewportBase::editSFCamera         (void)
{
    editSField(CameraFieldMask);

    return &_sfCamera;
}

//! Get the value of the Viewport::_sfCamera field.
Camera * ViewportBase::getCamera(void) const
{
    return _sfCamera.getValue();
}

//! Set the value of the Viewport::_sfCamera field.
void ViewportBase::setCamera(Camera * const value)
{
    editSField(CameraFieldMask);

    _sfCamera.setValue(value);
}


//! Get the Viewport::_sfRoot field.
const SFUnrecNodePtr *ViewportBase::getSFRoot(void) const
{
    return &_sfRoot;
}

SFUnrecNodePtr      *ViewportBase::editSFRoot           (void)
{
    editSField(RootFieldMask);

    return &_sfRoot;
}

//! Get the value of the Viewport::_sfRoot field.
Node * ViewportBase::getRoot(void) const
{
    return _sfRoot.getValue();
}

//! Set the value of the Viewport::_sfRoot field.
void ViewportBase::setRoot(Node * const value)
{
    editSField(RootFieldMask);

    _sfRoot.setValue(value);
}


//! Get the Viewport::_sfBackground field.
const SFUnrecBackgroundPtr *ViewportBase::getSFBackground(void) const
{
    return &_sfBackground;
}

SFUnrecBackgroundPtr *ViewportBase::editSFBackground     (void)
{
    editSField(BackgroundFieldMask);

    return &_sfBackground;
}

//! Get the value of the Viewport::_sfBackground field.
Background * ViewportBase::getBackground(void) const
{
    return _sfBackground.getValue();
}

//! Set the value of the Viewport::_sfBackground field.
void ViewportBase::setBackground(Background * const value)
{
    editSField(BackgroundFieldMask);

    _sfBackground.setValue(value);
}


//! Get the Viewport::_mfForegrounds field.
const MFUnrecForegroundPtr *ViewportBase::getMFForegrounds(void) const
{
    return &_mfForegrounds;
}

MFUnrecForegroundPtr *ViewportBase::editMFForegrounds    (void)
{
    editMField(ForegroundsFieldMask, _mfForegrounds);

    return &_mfForegrounds;
}
Foreground * ViewportBase::getForegrounds(const UInt32 index) const
{
    return _mfForegrounds[index];
}



void ViewportBase::addForeground(Foreground * const value)
{
    editMField(ForegroundsFieldMask, _mfForegrounds);

    _mfForegrounds.push_back(value);
}

void ViewportBase::assignForegrounds(const MFUnrecForegroundPtr &value)
{
    MFUnrecForegroundPtr::const_iterator elemIt  =
        value.begin();
    MFUnrecForegroundPtr::const_iterator elemEnd =
        value.end  ();

    static_cast<Viewport *>(this)->clearForegrounds();

    while(elemIt != elemEnd)
    {
        this->addForeground(*elemIt);

        ++elemIt;
    }
}

void ViewportBase::removeFromForegrounds(UInt32 uiIndex)
{
    if(uiIndex < _mfForegrounds.size())
    {
        editMField(ForegroundsFieldMask, _mfForegrounds);

        _mfForegrounds.erase(uiIndex);
    }
}

void ViewportBase::removeObjFromForegrounds(Foreground * const value)
{
    Int32 iElemIdx = _mfForegrounds.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(ForegroundsFieldMask, _mfForegrounds);

        _mfForegrounds.erase(iElemIdx);
    }
}
void ViewportBase::clearForegrounds(void)
{
    editMField(ForegroundsFieldMask, _mfForegrounds);


    _mfForegrounds.clear();
}



/*------------------------------ access -----------------------------------*/

SizeT ViewportBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        returnValue += _sfParent.getBinSize();
    }
    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        returnValue += _sfCamera.getBinSize();
    }
    if(FieldBits::NoField != (RootFieldMask & whichField))
    {
        returnValue += _sfRoot.getBinSize();
    }
    if(FieldBits::NoField != (BackgroundFieldMask & whichField))
    {
        returnValue += _sfBackground.getBinSize();
    }
    if(FieldBits::NoField != (ForegroundsFieldMask & whichField))
    {
        returnValue += _mfForegrounds.getBinSize();
    }

    return returnValue;
}

void ViewportBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _sfParent.copyToBin(pMem);
    }
    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        _sfCamera.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RootFieldMask & whichField))
    {
        _sfRoot.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BackgroundFieldMask & whichField))
    {
        _sfBackground.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ForegroundsFieldMask & whichField))
    {
        _mfForegrounds.copyToBin(pMem);
    }
}

void ViewportBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        editSField(ParentFieldMask);
        _sfParent.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (CameraFieldMask & whichField))
    {
        editSField(CameraFieldMask);
        _sfCamera.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RootFieldMask & whichField))
    {
        editSField(RootFieldMask);
        _sfRoot.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BackgroundFieldMask & whichField))
    {
        editSField(BackgroundFieldMask);
        _sfBackground.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ForegroundsFieldMask & whichField))
    {
        editMField(ForegroundsFieldMask, _mfForegrounds);
        _mfForegrounds.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ViewportTransitPtr ViewportBase::createLocal(BitVector bFlags)
{
    ViewportTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<Viewport>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ViewportTransitPtr ViewportBase::createDependent(BitVector bFlags)
{
    ViewportTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<Viewport>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ViewportTransitPtr ViewportBase::create(void)
{
    ViewportTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<Viewport>(tmpPtr);
    }

    return fc;
}

Viewport *ViewportBase::createEmptyLocal(BitVector bFlags)
{
    Viewport *returnValue;

    newPtr<Viewport>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
Viewport *ViewportBase::createEmpty(void)
{
    Viewport *returnValue;

    newPtr<Viewport>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr ViewportBase::shallowCopyLocal(
    BitVector bFlags) const
{
    Viewport *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const Viewport *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ViewportBase::shallowCopyDependent(
    BitVector bFlags) const
{
    Viewport *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const Viewport *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ViewportBase::shallowCopy(void) const
{
    Viewport *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const Viewport *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

ViewportBase::ViewportBase(void) :
    Inherited(),
    _sfParent                 (NULL),
    _sfCamera                 (NULL),
    _sfRoot                   (NULL),
    _sfBackground             (NULL),
    _mfForegrounds            ()
{
}

ViewportBase::ViewportBase(const ViewportBase &source) :
    Inherited(source),
    _sfParent                 (NULL),
    _sfCamera                 (NULL),
    _sfRoot                   (NULL),
    _sfBackground             (NULL),
    _mfForegrounds            ()
{
}


/*-------------------------- destructors ----------------------------------*/

ViewportBase::~ViewportBase(void)
{
}
/*-------------------------------------------------------------------------*/
/* Parent linking                                                          */

bool ViewportBase::linkParent(
    FieldContainer * const pParent,
    UInt16           const childFieldId,
    UInt16           const parentFieldId )
{
    if(parentFieldId == ParentFieldId)
    {
        FieldContainer * pTypedParent =
            dynamic_cast< FieldContainer * >(pParent);

        if(pTypedParent != NULL)
        {
            FieldContainer *pOldParent =
                _sfParent.getValue         ();

            UInt16 oldChildFieldId =
                _sfParent.getParentFieldPos();

            if(pOldParent != NULL)
            {
                pOldParent->unlinkChild(this, oldChildFieldId);
            }

            editSField(ParentFieldMask);

            _sfParent.setValue(static_cast<FieldContainer *>(pParent), childFieldId);

            return true;
        }

        return false;
    }

    return Inherited::linkParent(pParent, childFieldId, parentFieldId);
}

bool ViewportBase::unlinkParent(
    FieldContainer * const pParent,
    UInt16           const parentFieldId)
{
    if(parentFieldId == ParentFieldId)
    {
        FieldContainer * pTypedParent =
            dynamic_cast< FieldContainer * >(pParent);

        if(pTypedParent != NULL)
        {
            if(_sfParent.getValue() == pTypedParent)
            {
                editSField(ParentFieldMask);

                _sfParent.setValue(NULL, 0xFFFF);

                return true;
            }

            SWARNING << "Child (["          << this
                     << "] id ["            << this->getId()
                     << "] type ["          << this->getType().getCName()
                     << "] parentFieldId [" << parentFieldId
                     << "]) - Parent (["    << pParent
                     << "] id ["            << pParent->getId()
                     << "] type ["          << pParent->getType().getCName()
                     << "]): link inconsistent!"
                     << std::endl;

            return false;
        }

        return false;
    }

    return Inherited::unlinkParent(pParent, parentFieldId);
}


void ViewportBase::onCreate(const Viewport *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        Viewport *pThis = static_cast<Viewport *>(this);

        pThis->setCamera(source->getCamera());

        pThis->setRoot(source->getRoot());

        pThis->setBackground(source->getBackground());

        MFUnrecForegroundPtr::const_iterator ForegroundsIt  =
            source->_mfForegrounds.begin();
        MFUnrecForegroundPtr::const_iterator ForegroundsEnd =
            source->_mfForegrounds.end  ();

        while(ForegroundsIt != ForegroundsEnd)
        {
            pThis->addForeground(*ForegroundsIt);

            ++ForegroundsIt;
        }
    }
}

GetFieldHandlePtr ViewportBase::getHandleParent          (void) const
{
    SFParentFieldContainerPtr::GetHandlePtr returnValue;

    return returnValue;
}

EditFieldHandlePtr ViewportBase::editHandleParent         (void)
{
    EditFieldHandlePtr returnValue;

    return returnValue;
}

GetFieldHandlePtr ViewportBase::getHandleCamera          (void) const
{
    SFUnrecCameraPtr::GetHandlePtr returnValue(
        new  SFUnrecCameraPtr::GetHandle(
             &_sfCamera,
             this->getType().getFieldDesc(CameraFieldId),
             const_cast<ViewportBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ViewportBase::editHandleCamera         (void)
{
    SFUnrecCameraPtr::EditHandlePtr returnValue(
        new  SFUnrecCameraPtr::EditHandle(
             &_sfCamera,
             this->getType().getFieldDesc(CameraFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&Viewport::setCamera,
                    static_cast<Viewport *>(this), ::boost::placeholders::_1));

    editSField(CameraFieldMask);

    return returnValue;
}

GetFieldHandlePtr ViewportBase::getHandleRoot            (void) const
{
    SFUnrecNodePtr::GetHandlePtr returnValue(
        new  SFUnrecNodePtr::GetHandle(
             &_sfRoot,
             this->getType().getFieldDesc(RootFieldId),
             const_cast<ViewportBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ViewportBase::editHandleRoot           (void)
{
    SFUnrecNodePtr::EditHandlePtr returnValue(
        new  SFUnrecNodePtr::EditHandle(
             &_sfRoot,
             this->getType().getFieldDesc(RootFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&Viewport::setRoot,
                    static_cast<Viewport *>(this), ::boost::placeholders::_1));

    editSField(RootFieldMask);

    return returnValue;
}

GetFieldHandlePtr ViewportBase::getHandleBackground      (void) const
{
    SFUnrecBackgroundPtr::GetHandlePtr returnValue(
        new  SFUnrecBackgroundPtr::GetHandle(
             &_sfBackground,
             this->getType().getFieldDesc(BackgroundFieldId),
             const_cast<ViewportBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ViewportBase::editHandleBackground     (void)
{
    SFUnrecBackgroundPtr::EditHandlePtr returnValue(
        new  SFUnrecBackgroundPtr::EditHandle(
             &_sfBackground,
             this->getType().getFieldDesc(BackgroundFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&Viewport::setBackground,
                    static_cast<Viewport *>(this), ::boost::placeholders::_1));

    editSField(BackgroundFieldMask);

    return returnValue;
}

GetFieldHandlePtr ViewportBase::getHandleForegrounds     (void) const
{
    MFUnrecForegroundPtr::GetHandlePtr returnValue(
        new  MFUnrecForegroundPtr::GetHandle(
             &_mfForegrounds,
             this->getType().getFieldDesc(ForegroundsFieldId),
             const_cast<ViewportBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ViewportBase::editHandleForegrounds    (void)
{
    MFUnrecForegroundPtr::EditHandlePtr returnValue(
        new  MFUnrecForegroundPtr::EditHandle(
             &_mfForegrounds,
             this->getType().getFieldDesc(ForegroundsFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&Viewport::addForeground,
                    static_cast<Viewport *>(this), ::boost::placeholders::_1));
    returnValue->setRemoveMethod(
        boost::bind(&Viewport::removeFromForegrounds,
                    static_cast<Viewport *>(this), ::boost::placeholders::_1));
    returnValue->setRemoveObjMethod(
        boost::bind(&Viewport::removeObjFromForegrounds,
                    static_cast<Viewport *>(this), ::boost::placeholders::_1));
    returnValue->setClearMethod(
        boost::bind(&Viewport::clearForegrounds,
                    static_cast<Viewport *>(this)));

    editMField(ForegroundsFieldMask, _mfForegrounds);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void ViewportBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Viewport *pThis = static_cast<Viewport *>(this);

    pThis->execSync(static_cast<Viewport *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ViewportBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    Viewport *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const Viewport *>(pRefAspect),
                  dynamic_cast<const Viewport *>(this));

    return returnValue;
}
#endif

void ViewportBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<Viewport *>(this)->setCamera(NULL);

    static_cast<Viewport *>(this)->setRoot(NULL);

    static_cast<Viewport *>(this)->setBackground(NULL);

    static_cast<Viewport *>(this)->clearForegrounds();


}


OSG_END_NAMESPACE
