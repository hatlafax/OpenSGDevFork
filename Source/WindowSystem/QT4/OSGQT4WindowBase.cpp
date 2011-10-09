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
 **     class QT4Window!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"




#include "OSGQT4WindowBase.h"
#include "OSGQT4Window.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::QT4Window
    The class for QT windows.

    Do *NOT* use this fcd to recreate the QTWindow code. The QT window is a hybrid
    beast that derives from XWindow on Unix and WIN32Window on Windows, and as
    such can't be recreated automatically.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var OSGQGLWidgetP   QT4WindowBase::_sfGlWidget
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<QT4Window *, nsOSG>::_type("QT4WindowPtr", "WindowPtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(QT4Window *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           QT4Window *,
                           nsOSG);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           QT4Window *,
                           nsOSG);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void QT4WindowBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFOSGQGLWidgetP::Description(
        SFOSGQGLWidgetP::getClassType(),
        "GlWidget",
        "",
        GlWidgetFieldId, GlWidgetFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&QT4Window::editHandleGlWidget),
        static_cast<FieldGetMethodSig >(&QT4Window::getHandleGlWidget));

    oType.addInitialDesc(pDesc);
}


QT4WindowBase::TypeObject QT4WindowBase::_type(
    QT4WindowBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&QT4WindowBase::createEmptyLocal),
    QT4Window::initMethod,
    QT4Window::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&QT4Window::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"QT4Window\"\n"
    "    parent=\"NativeWindow\"\n"
    "    library=\"WindowQT4\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    realparent=\"Window\"\n"
    "    docGroupBase=\"GrpWindowQt4\"\n"
    "    >\n"
    "  The class for QT windows.\n"
    "  \n"
    "  Do *NOT* use this fcd to recreate the QTWindow code. The QT window is a hybrid\n"
    "  beast that derives from XWindow on Unix and WIN32Window on Windows, and as\n"
    "  such can't be recreated automatically.\n"
    "  <Field\n"
    "      name=\"GlWidget\"\n"
    "      type=\"OSGQGLWidgetP\"\n"
    "      cardinality=\"single\"\n"
    "      visibility=\"internal\"\n"
    "      defaultValue=\"NULL\"\n"
    "      fieldHeader=\"OSGQT4WindowDataFields.h\"\n"
    "      access=\"public\"\n"
    "      >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    "The class for QT windows.\n"
    "\n"
    "Do *NOT* use this fcd to recreate the QTWindow code. The QT window is a hybrid\n"
    "beast that derives from XWindow on Unix and WIN32Window on Windows, and as\n"
    "such can't be recreated automatically.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &QT4WindowBase::getType(void)
{
    return _type;
}

const FieldContainerType &QT4WindowBase::getType(void) const
{
    return _type;
}

UInt32 QT4WindowBase::getContainerSize(void) const
{
    return sizeof(QT4Window);
}

/*------------------------- decorator get ------------------------------*/


SFOSGQGLWidgetP *QT4WindowBase::editSFGlWidget(void)
{
    editSField(GlWidgetFieldMask);

    return &_sfGlWidget;
}

const SFOSGQGLWidgetP *QT4WindowBase::getSFGlWidget(void) const
{
    return &_sfGlWidget;
}






/*------------------------------ access -----------------------------------*/

UInt32 QT4WindowBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (GlWidgetFieldMask & whichField))
    {
        returnValue += _sfGlWidget.getBinSize();
    }

    return returnValue;
}

void QT4WindowBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (GlWidgetFieldMask & whichField))
    {
        _sfGlWidget.copyToBin(pMem);
    }
}

void QT4WindowBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (GlWidgetFieldMask & whichField))
    {
        editSField(GlWidgetFieldMask);
        _sfGlWidget.copyFromBin(pMem);
    }
}

//! create a new instance of the class
QT4WindowTransitPtr QT4WindowBase::createLocal(BitVector bFlags)
{
    QT4WindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<QT4Window>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
QT4WindowTransitPtr QT4WindowBase::createDependent(BitVector bFlags)
{
    QT4WindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<QT4Window>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
QT4WindowTransitPtr QT4WindowBase::create(void)
{
    QT4WindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<QT4Window>(tmpPtr);
    }

    return fc;
}

QT4Window *QT4WindowBase::createEmptyLocal(BitVector bFlags)
{
    QT4Window *returnValue;

    newPtr<QT4Window>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
QT4Window *QT4WindowBase::createEmpty(void)
{
    QT4Window *returnValue;

    newPtr<QT4Window>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr QT4WindowBase::shallowCopyLocal(
    BitVector bFlags) const
{
    QT4Window *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const QT4Window *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr QT4WindowBase::shallowCopyDependent(
    BitVector bFlags) const
{
    QT4Window *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const QT4Window *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr QT4WindowBase::shallowCopy(void) const
{
    QT4Window *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const QT4Window *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

QT4WindowBase::QT4WindowBase(void) :
    Inherited(),
    _sfGlWidget               (OSGQGLWidgetP(NULL))
{
}

QT4WindowBase::QT4WindowBase(const QT4WindowBase &source) :
    Inherited(source),
    _sfGlWidget               (source._sfGlWidget               )
{
}


/*-------------------------- destructors ----------------------------------*/

QT4WindowBase::~QT4WindowBase(void)
{
}


GetFieldHandlePtr QT4WindowBase::getHandleGlWidget        (void) const
{
    SFOSGQGLWidgetP::GetHandlePtr returnValue(
        new  SFOSGQGLWidgetP::GetHandle(
             &_sfGlWidget,
             this->getType().getFieldDesc(GlWidgetFieldId),
             const_cast<QT4WindowBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr QT4WindowBase::editHandleGlWidget       (void)
{
    SFOSGQGLWidgetP::EditHandlePtr returnValue(
        new  SFOSGQGLWidgetP::EditHandle(
             &_sfGlWidget,
             this->getType().getFieldDesc(GlWidgetFieldId),
             this));


    editSField(GlWidgetFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void QT4WindowBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    QT4Window *pThis = static_cast<QT4Window *>(this);

    pThis->execSync(static_cast<QT4Window *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *QT4WindowBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    QT4Window *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const QT4Window *>(pRefAspect),
                  dynamic_cast<const QT4Window *>(this));

    return returnValue;
}
#endif

void QT4WindowBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
