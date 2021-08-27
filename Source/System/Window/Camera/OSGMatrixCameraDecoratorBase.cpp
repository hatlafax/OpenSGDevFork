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
 **     class MatrixCameraDecorator!
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




#include "OSGMatrixCameraDecoratorBase.h"
#include "OSGMatrixCameraDecorator.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MatrixCameraDecorator
    The OSG::MatrixCameraDecorator for modifying the camera matrices by 
    matrices, see \ref
    PageSystemWindowCameraDecoratorsMatrix for a description.

    The matrices to use are defined by the _sf Fields. The size of the full
    image is defined by the _sfFullWidth and
    _sfFullHeight Fields.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Matrix          MatrixCameraDecoratorBase::_sfPreViewing
    The matrix to multiply to the right of the viewing matrix, i.e. 
    applied before the viewing matrix.
*/

/*! \var Matrix          MatrixCameraDecoratorBase::_sfPostViewing
    The matrix to multiply to the left of the viewing matrix, i.e. 
    applied after the viewing matrix.
*/

/*! \var Matrix          MatrixCameraDecoratorBase::_sfPreProjectionTranslation
    The matrix to multiply to the right of the projectionTranslation matrix,
    i.e. applied before the projectionTranslation matrix.
*/

/*! \var Matrix          MatrixCameraDecoratorBase::_sfPostProjectionTranslation
    The matrix to multiply to the left of the projectionTranslation matrix,
    i.e.  applied before the projectionTranslation matrix.
*/

/*! \var Matrix          MatrixCameraDecoratorBase::_sfPreProjection
    The matrix to multiply to the right of the projection matrix, i.e. 
    applied before the projection matrix.
*/

/*! \var Matrix          MatrixCameraDecoratorBase::_sfPostProjection
    The matrix to multiply to the left of the projection matrix, i.e. 
    applied before the projection matrix.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<MatrixCameraDecorator *, nsOSG>::_type(
    "MatrixCameraDecoratorPtr", 
    "CameraDecoratorPtr", 
    MatrixCameraDecorator::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(MatrixCameraDecorator *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           MatrixCameraDecorator *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           MatrixCameraDecorator *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void MatrixCameraDecoratorBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFMatrix::Description(
        SFMatrix::getClassType(),
        "preViewing",
        "The matrix to multiply to the right of the viewing matrix, i.e. \n"
        "applied before the viewing matrix.\n",
        PreViewingFieldId, PreViewingFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&MatrixCameraDecorator::editHandlePreViewing),
        static_cast<FieldGetMethodSig >(&MatrixCameraDecorator::getHandlePreViewing));

    oType.addInitialDesc(pDesc);

    pDesc = new SFMatrix::Description(
        SFMatrix::getClassType(),
        "postViewing",
        "The matrix to multiply to the left of the viewing matrix, i.e. \n"
        "applied after the viewing matrix.\n",
        PostViewingFieldId, PostViewingFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&MatrixCameraDecorator::editHandlePostViewing),
        static_cast<FieldGetMethodSig >(&MatrixCameraDecorator::getHandlePostViewing));

    oType.addInitialDesc(pDesc);

    pDesc = new SFMatrix::Description(
        SFMatrix::getClassType(),
        "preProjectionTranslation",
        "The matrix to multiply to the right of the projectionTranslation matrix,\n"
        "i.e. applied before the projectionTranslation matrix.\n",
        PreProjectionTranslationFieldId, PreProjectionTranslationFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&MatrixCameraDecorator::editHandlePreProjectionTranslation),
        static_cast<FieldGetMethodSig >(&MatrixCameraDecorator::getHandlePreProjectionTranslation));

    oType.addInitialDesc(pDesc);

    pDesc = new SFMatrix::Description(
        SFMatrix::getClassType(),
        "postProjectionTranslation",
        "The matrix to multiply to the left of the projectionTranslation matrix,\n"
        "i.e.  applied before the projectionTranslation matrix.\n",
        PostProjectionTranslationFieldId, PostProjectionTranslationFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&MatrixCameraDecorator::editHandlePostProjectionTranslation),
        static_cast<FieldGetMethodSig >(&MatrixCameraDecorator::getHandlePostProjectionTranslation));

    oType.addInitialDesc(pDesc);

    pDesc = new SFMatrix::Description(
        SFMatrix::getClassType(),
        "preProjection",
        "The matrix to multiply to the right of the projection matrix, i.e. \n"
        "applied before the projection matrix.\n",
        PreProjectionFieldId, PreProjectionFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&MatrixCameraDecorator::editHandlePreProjection),
        static_cast<FieldGetMethodSig >(&MatrixCameraDecorator::getHandlePreProjection));

    oType.addInitialDesc(pDesc);

    pDesc = new SFMatrix::Description(
        SFMatrix::getClassType(),
        "postProjection",
        "The matrix to multiply to the left of the projection matrix, i.e. \n"
        "applied before the projection matrix.\n",
        PostProjectionFieldId, PostProjectionFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&MatrixCameraDecorator::editHandlePostProjection),
        static_cast<FieldGetMethodSig >(&MatrixCameraDecorator::getHandlePostProjection));

    oType.addInitialDesc(pDesc);
}


MatrixCameraDecoratorBase::TypeObject MatrixCameraDecoratorBase::_type(
    MatrixCameraDecoratorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&MatrixCameraDecoratorBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&MatrixCameraDecorator::initMethod),
    reinterpret_cast<ExitContainerF>(&MatrixCameraDecorator::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&MatrixCameraDecorator::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"MatrixCameraDecorator\"\n"
    "   parent=\"CameraDecorator\"\n"
    "   library=\"Window\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   structure=\"concrete\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   docGroupBase=\"GrpWindowCamera\"\n"
    "   >\n"
    "  The OSG::MatrixCameraDecorator for modifying the camera matrices by \n"
    "  matrices, see \\ref\n"
    "  PageSystemWindowCameraDecoratorsMatrix for a description.\n"
    "\n"
    "  The matrices to use are defined by the _sf Fields. The size of the full\n"
    "  image is defined by the _sfFullWidth and\n"
    "  _sfFullHeight Fields.\n"
    "  <Field\n"
    "\t name=\"preViewing\"\n"
    "\t type=\"Matrix\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tThe matrix to multiply to the right of the viewing matrix, i.e. \n"
    "    applied before the viewing matrix.\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"postViewing\"\n"
    "\t type=\"Matrix\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tThe matrix to multiply to the left of the viewing matrix, i.e. \n"
    "    applied after the viewing matrix.\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"preProjectionTranslation\"\n"
    "\t type=\"Matrix\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tThe matrix to multiply to the right of the projectionTranslation matrix,\n"
    "\ti.e. applied before the projectionTranslation matrix.\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"postProjectionTranslation\"\n"
    "\t type=\"Matrix\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tThe matrix to multiply to the left of the projectionTranslation matrix,\n"
    "\ti.e.  applied before the projectionTranslation matrix.\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"preProjection\"\n"
    "\t type=\"Matrix\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tThe matrix to multiply to the right of the projection matrix, i.e. \n"
    "    applied before the projection matrix.\n"
    "  </Field>\n"
    "  <Field\n"
    "\t name=\"postProjection\"\n"
    "\t type=\"Matrix\"\n"
    "\t cardinality=\"single\"\n"
    "\t visibility=\"external\"\n"
    "\t defaultValue=\"1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1\"\n"
    "\t access=\"public\"\n"
    "\t >\n"
    "\tThe matrix to multiply to the left of the projection matrix, i.e. \n"
    "    applied before the projection matrix.\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    "The OSG::MatrixCameraDecorator for modifying the camera matrices by \n"
    "matrices, see \\ref\n"
    "PageSystemWindowCameraDecoratorsMatrix for a description.\n"
    "\n"
    "The matrices to use are defined by the _sf Fields. The size of the full\n"
    "image is defined by the _sfFullWidth and\n"
    "_sfFullHeight Fields.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &MatrixCameraDecoratorBase::getType(void)
{
    return _type;
}

const FieldContainerType &MatrixCameraDecoratorBase::getType(void) const
{
    return _type;
}

UInt32 MatrixCameraDecoratorBase::getContainerSize(void) const
{
    return sizeof(MatrixCameraDecorator);
}

/*------------------------- decorator get ------------------------------*/


SFMatrix *MatrixCameraDecoratorBase::editSFPreViewing(void)
{
    editSField(PreViewingFieldMask);

    return &_sfPreViewing;
}

const SFMatrix *MatrixCameraDecoratorBase::getSFPreViewing(void) const
{
    return &_sfPreViewing;
}


SFMatrix *MatrixCameraDecoratorBase::editSFPostViewing(void)
{
    editSField(PostViewingFieldMask);

    return &_sfPostViewing;
}

const SFMatrix *MatrixCameraDecoratorBase::getSFPostViewing(void) const
{
    return &_sfPostViewing;
}


SFMatrix *MatrixCameraDecoratorBase::editSFPreProjectionTranslation(void)
{
    editSField(PreProjectionTranslationFieldMask);

    return &_sfPreProjectionTranslation;
}

const SFMatrix *MatrixCameraDecoratorBase::getSFPreProjectionTranslation(void) const
{
    return &_sfPreProjectionTranslation;
}


SFMatrix *MatrixCameraDecoratorBase::editSFPostProjectionTranslation(void)
{
    editSField(PostProjectionTranslationFieldMask);

    return &_sfPostProjectionTranslation;
}

const SFMatrix *MatrixCameraDecoratorBase::getSFPostProjectionTranslation(void) const
{
    return &_sfPostProjectionTranslation;
}


SFMatrix *MatrixCameraDecoratorBase::editSFPreProjection(void)
{
    editSField(PreProjectionFieldMask);

    return &_sfPreProjection;
}

const SFMatrix *MatrixCameraDecoratorBase::getSFPreProjection(void) const
{
    return &_sfPreProjection;
}


SFMatrix *MatrixCameraDecoratorBase::editSFPostProjection(void)
{
    editSField(PostProjectionFieldMask);

    return &_sfPostProjection;
}

const SFMatrix *MatrixCameraDecoratorBase::getSFPostProjection(void) const
{
    return &_sfPostProjection;
}






/*------------------------------ access -----------------------------------*/

SizeT MatrixCameraDecoratorBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (PreViewingFieldMask & whichField))
    {
        returnValue += _sfPreViewing.getBinSize();
    }
    if(FieldBits::NoField != (PostViewingFieldMask & whichField))
    {
        returnValue += _sfPostViewing.getBinSize();
    }
    if(FieldBits::NoField != (PreProjectionTranslationFieldMask & whichField))
    {
        returnValue += _sfPreProjectionTranslation.getBinSize();
    }
    if(FieldBits::NoField != (PostProjectionTranslationFieldMask & whichField))
    {
        returnValue += _sfPostProjectionTranslation.getBinSize();
    }
    if(FieldBits::NoField != (PreProjectionFieldMask & whichField))
    {
        returnValue += _sfPreProjection.getBinSize();
    }
    if(FieldBits::NoField != (PostProjectionFieldMask & whichField))
    {
        returnValue += _sfPostProjection.getBinSize();
    }

    return returnValue;
}

void MatrixCameraDecoratorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (PreViewingFieldMask & whichField))
    {
        _sfPreViewing.copyToBin(pMem);
    }
    if(FieldBits::NoField != (PostViewingFieldMask & whichField))
    {
        _sfPostViewing.copyToBin(pMem);
    }
    if(FieldBits::NoField != (PreProjectionTranslationFieldMask & whichField))
    {
        _sfPreProjectionTranslation.copyToBin(pMem);
    }
    if(FieldBits::NoField != (PostProjectionTranslationFieldMask & whichField))
    {
        _sfPostProjectionTranslation.copyToBin(pMem);
    }
    if(FieldBits::NoField != (PreProjectionFieldMask & whichField))
    {
        _sfPreProjection.copyToBin(pMem);
    }
    if(FieldBits::NoField != (PostProjectionFieldMask & whichField))
    {
        _sfPostProjection.copyToBin(pMem);
    }
}

void MatrixCameraDecoratorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (PreViewingFieldMask & whichField))
    {
        editSField(PreViewingFieldMask);
        _sfPreViewing.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (PostViewingFieldMask & whichField))
    {
        editSField(PostViewingFieldMask);
        _sfPostViewing.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (PreProjectionTranslationFieldMask & whichField))
    {
        editSField(PreProjectionTranslationFieldMask);
        _sfPreProjectionTranslation.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (PostProjectionTranslationFieldMask & whichField))
    {
        editSField(PostProjectionTranslationFieldMask);
        _sfPostProjectionTranslation.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (PreProjectionFieldMask & whichField))
    {
        editSField(PreProjectionFieldMask);
        _sfPreProjection.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (PostProjectionFieldMask & whichField))
    {
        editSField(PostProjectionFieldMask);
        _sfPostProjection.copyFromBin(pMem);
    }
}

//! create a new instance of the class
MatrixCameraDecoratorTransitPtr MatrixCameraDecoratorBase::createLocal(BitVector bFlags)
{
    MatrixCameraDecoratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<MatrixCameraDecorator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
MatrixCameraDecoratorTransitPtr MatrixCameraDecoratorBase::createDependent(BitVector bFlags)
{
    MatrixCameraDecoratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<MatrixCameraDecorator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
MatrixCameraDecoratorTransitPtr MatrixCameraDecoratorBase::create(void)
{
    MatrixCameraDecoratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<MatrixCameraDecorator>(tmpPtr);
    }

    return fc;
}

MatrixCameraDecorator *MatrixCameraDecoratorBase::createEmptyLocal(BitVector bFlags)
{
    MatrixCameraDecorator *returnValue;

    newPtr<MatrixCameraDecorator>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
MatrixCameraDecorator *MatrixCameraDecoratorBase::createEmpty(void)
{
    MatrixCameraDecorator *returnValue;

    newPtr<MatrixCameraDecorator>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr MatrixCameraDecoratorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    MatrixCameraDecorator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const MatrixCameraDecorator *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr MatrixCameraDecoratorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    MatrixCameraDecorator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const MatrixCameraDecorator *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr MatrixCameraDecoratorBase::shallowCopy(void) const
{
    MatrixCameraDecorator *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const MatrixCameraDecorator *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

MatrixCameraDecoratorBase::MatrixCameraDecoratorBase(void) :
    Inherited(),
    _sfPreViewing             (Matrix(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1)),
    _sfPostViewing            (Matrix(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1)),
    _sfPreProjectionTranslation(Matrix(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1)),
    _sfPostProjectionTranslation(Matrix(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1)),
    _sfPreProjection          (Matrix(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1)),
    _sfPostProjection         (Matrix(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1))
{
}

MatrixCameraDecoratorBase::MatrixCameraDecoratorBase(const MatrixCameraDecoratorBase &source) :
    Inherited(source),
    _sfPreViewing             (source._sfPreViewing             ),
    _sfPostViewing            (source._sfPostViewing            ),
    _sfPreProjectionTranslation(source._sfPreProjectionTranslation),
    _sfPostProjectionTranslation(source._sfPostProjectionTranslation),
    _sfPreProjection          (source._sfPreProjection          ),
    _sfPostProjection         (source._sfPostProjection         )
{
}


/*-------------------------- destructors ----------------------------------*/

MatrixCameraDecoratorBase::~MatrixCameraDecoratorBase(void)
{
}


GetFieldHandlePtr MatrixCameraDecoratorBase::getHandlePreViewing      (void) const
{
    SFMatrix::GetHandlePtr returnValue(
        new  SFMatrix::GetHandle(
             &_sfPreViewing,
             this->getType().getFieldDesc(PreViewingFieldId),
             const_cast<MatrixCameraDecoratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr MatrixCameraDecoratorBase::editHandlePreViewing     (void)
{
    SFMatrix::EditHandlePtr returnValue(
        new  SFMatrix::EditHandle(
             &_sfPreViewing,
             this->getType().getFieldDesc(PreViewingFieldId),
             this));


    editSField(PreViewingFieldMask);

    return returnValue;
}

GetFieldHandlePtr MatrixCameraDecoratorBase::getHandlePostViewing     (void) const
{
    SFMatrix::GetHandlePtr returnValue(
        new  SFMatrix::GetHandle(
             &_sfPostViewing,
             this->getType().getFieldDesc(PostViewingFieldId),
             const_cast<MatrixCameraDecoratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr MatrixCameraDecoratorBase::editHandlePostViewing    (void)
{
    SFMatrix::EditHandlePtr returnValue(
        new  SFMatrix::EditHandle(
             &_sfPostViewing,
             this->getType().getFieldDesc(PostViewingFieldId),
             this));


    editSField(PostViewingFieldMask);

    return returnValue;
}

GetFieldHandlePtr MatrixCameraDecoratorBase::getHandlePreProjectionTranslation (void) const
{
    SFMatrix::GetHandlePtr returnValue(
        new  SFMatrix::GetHandle(
             &_sfPreProjectionTranslation,
             this->getType().getFieldDesc(PreProjectionTranslationFieldId),
             const_cast<MatrixCameraDecoratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr MatrixCameraDecoratorBase::editHandlePreProjectionTranslation(void)
{
    SFMatrix::EditHandlePtr returnValue(
        new  SFMatrix::EditHandle(
             &_sfPreProjectionTranslation,
             this->getType().getFieldDesc(PreProjectionTranslationFieldId),
             this));


    editSField(PreProjectionTranslationFieldMask);

    return returnValue;
}

GetFieldHandlePtr MatrixCameraDecoratorBase::getHandlePostProjectionTranslation (void) const
{
    SFMatrix::GetHandlePtr returnValue(
        new  SFMatrix::GetHandle(
             &_sfPostProjectionTranslation,
             this->getType().getFieldDesc(PostProjectionTranslationFieldId),
             const_cast<MatrixCameraDecoratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr MatrixCameraDecoratorBase::editHandlePostProjectionTranslation(void)
{
    SFMatrix::EditHandlePtr returnValue(
        new  SFMatrix::EditHandle(
             &_sfPostProjectionTranslation,
             this->getType().getFieldDesc(PostProjectionTranslationFieldId),
             this));


    editSField(PostProjectionTranslationFieldMask);

    return returnValue;
}

GetFieldHandlePtr MatrixCameraDecoratorBase::getHandlePreProjection   (void) const
{
    SFMatrix::GetHandlePtr returnValue(
        new  SFMatrix::GetHandle(
             &_sfPreProjection,
             this->getType().getFieldDesc(PreProjectionFieldId),
             const_cast<MatrixCameraDecoratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr MatrixCameraDecoratorBase::editHandlePreProjection  (void)
{
    SFMatrix::EditHandlePtr returnValue(
        new  SFMatrix::EditHandle(
             &_sfPreProjection,
             this->getType().getFieldDesc(PreProjectionFieldId),
             this));


    editSField(PreProjectionFieldMask);

    return returnValue;
}

GetFieldHandlePtr MatrixCameraDecoratorBase::getHandlePostProjection  (void) const
{
    SFMatrix::GetHandlePtr returnValue(
        new  SFMatrix::GetHandle(
             &_sfPostProjection,
             this->getType().getFieldDesc(PostProjectionFieldId),
             const_cast<MatrixCameraDecoratorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr MatrixCameraDecoratorBase::editHandlePostProjection (void)
{
    SFMatrix::EditHandlePtr returnValue(
        new  SFMatrix::EditHandle(
             &_sfPostProjection,
             this->getType().getFieldDesc(PostProjectionFieldId),
             this));


    editSField(PostProjectionFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void MatrixCameraDecoratorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    MatrixCameraDecorator *pThis = static_cast<MatrixCameraDecorator *>(this);

    pThis->execSync(static_cast<MatrixCameraDecorator *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *MatrixCameraDecoratorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    MatrixCameraDecorator *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const MatrixCameraDecorator *>(pRefAspect),
                  dynamic_cast<const MatrixCameraDecorator *>(this));

    return returnValue;
}
#endif

void MatrixCameraDecoratorBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
