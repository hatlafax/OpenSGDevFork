/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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
 **     class CSMTrackball!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &CSMTrackballBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 CSMTrackballBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 CSMTrackballBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the CSMTrackball::_sfModifierMask field.

inline
UInt32 &CSMTrackballBase::editModifierMask(void)
{
    editSField(ModifierMaskFieldMask);

    return _sfModifierMask.getValue();
}

//! Get the value of the CSMTrackball::_sfModifierMask field.
inline
      UInt32  CSMTrackballBase::getModifierMask(void) const
{
    return _sfModifierMask.getValue();
}

//! Set the value of the CSMTrackball::_sfModifierMask field.
inline
void CSMTrackballBase::setModifierMask(const UInt32 value)
{
    editSField(ModifierMaskFieldMask);

    _sfModifierMask.setValue(value);
}
//! Get the value of the CSMTrackball::_sfProcessing field.

inline
UInt32 &CSMTrackballBase::editProcessing(void)
{
    editSField(ProcessingFieldMask);

    return _sfProcessing.getValue();
}

//! Get the value of the CSMTrackball::_sfProcessing field.
inline
      UInt32  CSMTrackballBase::getProcessing(void) const
{
    return _sfProcessing.getValue();
}

//! Set the value of the CSMTrackball::_sfProcessing field.
inline
void CSMTrackballBase::setProcessing(const UInt32 value)
{
    editSField(ProcessingFieldMask);

    _sfProcessing.setValue(value);
}
//! Get the value of the CSMTrackball::_sfTranslationScaleFactor field.

inline
Real32 &CSMTrackballBase::editTranslationScaleFactor(void)
{
    editSField(TranslationScaleFactorFieldMask);

    return _sfTranslationScaleFactor.getValue();
}

//! Get the value of the CSMTrackball::_sfTranslationScaleFactor field.
inline
      Real32  CSMTrackballBase::getTranslationScaleFactor(void) const
{
    return _sfTranslationScaleFactor.getValue();
}

//! Set the value of the CSMTrackball::_sfTranslationScaleFactor field.
inline
void CSMTrackballBase::setTranslationScaleFactor(const Real32 value)
{
    editSField(TranslationScaleFactorFieldMask);

    _sfTranslationScaleFactor.setValue(value);
}
//! Get the value of the CSMTrackball::_sfMatrixResult field.

inline
Matrix &CSMTrackballBase::editMatrixResult(void)
{
    editSField(MatrixResultFieldMask);

    return _sfMatrixResult.getValue();
}

//! Get the value of the CSMTrackball::_sfMatrixResult field.
inline
const Matrix &CSMTrackballBase::getMatrixResult(void) const
{
    return _sfMatrixResult.getValue();
}

//! Set the value of the CSMTrackball::_sfMatrixResult field.
inline
void CSMTrackballBase::setMatrixResult(const Matrix &value)
{
    editSField(MatrixResultFieldMask);

    _sfMatrixResult.setValue(value);
}
//! Get the value of the CSMTrackball::_sfRotationMatrixResult field.

inline
Matrix &CSMTrackballBase::editRotationMatrixResult(void)
{
    editSField(RotationMatrixResultFieldMask);

    return _sfRotationMatrixResult.getValue();
}

//! Get the value of the CSMTrackball::_sfRotationMatrixResult field.
inline
const Matrix &CSMTrackballBase::getRotationMatrixResult(void) const
{
    return _sfRotationMatrixResult.getValue();
}

//! Set the value of the CSMTrackball::_sfRotationMatrixResult field.
inline
void CSMTrackballBase::setRotationMatrixResult(const Matrix &value)
{
    editSField(RotationMatrixResultFieldMask);

    _sfRotationMatrixResult.setValue(value);
}
//! Get the value of the CSMTrackball::_sfReferencePosition field.

inline
Pnt3f &CSMTrackballBase::editReferencePosition(void)
{
    editSField(ReferencePositionFieldMask);

    return _sfReferencePosition.getValue();
}

//! Get the value of the CSMTrackball::_sfReferencePosition field.
inline
const Pnt3f &CSMTrackballBase::getReferencePosition(void) const
{
    return _sfReferencePosition.getValue();
}

//! Set the value of the CSMTrackball::_sfReferencePosition field.
inline
void CSMTrackballBase::setReferencePosition(const Pnt3f &value)
{
    editSField(ReferencePositionFieldMask);

    _sfReferencePosition.setValue(value);
}
//! Get the value of the CSMTrackball::_sfReferenceMatrix field.

inline
Matrix &CSMTrackballBase::editReferenceMatrix(void)
{
    editSField(ReferenceMatrixFieldMask);

    return _sfReferenceMatrix.getValue();
}

//! Get the value of the CSMTrackball::_sfReferenceMatrix field.
inline
const Matrix &CSMTrackballBase::getReferenceMatrix(void) const
{
    return _sfReferenceMatrix.getValue();
}

//! Set the value of the CSMTrackball::_sfReferenceMatrix field.
inline
void CSMTrackballBase::setReferenceMatrix(const Matrix &value)
{
    editSField(ReferenceMatrixFieldMask);

    _sfReferenceMatrix.setValue(value);
}
//! Get the value of the CSMTrackball::_sfTransformCenter field.

inline
Pnt3f &CSMTrackballBase::editTransformCenter(void)
{
    editSField(TransformCenterFieldMask);

    return _sfTransformCenter.getValue();
}

//! Get the value of the CSMTrackball::_sfTransformCenter field.
inline
const Pnt3f &CSMTrackballBase::getTransformCenter(void) const
{
    return _sfTransformCenter.getValue();
}

//! Set the value of the CSMTrackball::_sfTransformCenter field.
inline
void CSMTrackballBase::setTransformCenter(const Pnt3f &value)
{
    editSField(TransformCenterFieldMask);

    _sfTransformCenter.setValue(value);
}
//! Get the value of the CSMTrackball::_sfWorldDiag field.

inline
Vec3f &CSMTrackballBase::editWorldDiag(void)
{
    editSField(WorldDiagFieldMask);

    return _sfWorldDiag.getValue();
}

//! Get the value of the CSMTrackball::_sfWorldDiag field.
inline
const Vec3f &CSMTrackballBase::getWorldDiag(void) const
{
    return _sfWorldDiag.getValue();
}

//! Set the value of the CSMTrackball::_sfWorldDiag field.
inline
void CSMTrackballBase::setWorldDiag(const Vec3f &value)
{
    editSField(WorldDiagFieldMask);

    _sfWorldDiag.setValue(value);
}
//! Get the value of the CSMTrackball::_sfMouseData field.

inline
MouseData &CSMTrackballBase::editMouseData(void)
{
    editSField(MouseDataFieldMask);

    return _sfMouseData.getValue();
}

//! Get the value of the CSMTrackball::_sfMouseData field.
inline
const MouseData &CSMTrackballBase::getMouseData(void) const
{
    return _sfMouseData.getValue();
}

//! Set the value of the CSMTrackball::_sfMouseData field.
inline
void CSMTrackballBase::setMouseData(const MouseData &value)
{
    editSField(MouseDataFieldMask);

    _sfMouseData.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void CSMTrackballBase::execSync (      CSMTrackballBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ModifierMaskFieldMask & whichField))
        _sfModifierMask.syncWith(pFrom->_sfModifierMask);

    if(FieldBits::NoField != (ProcessingFieldMask & whichField))
        _sfProcessing.syncWith(pFrom->_sfProcessing);

    if(FieldBits::NoField != (TranslationScaleFactorFieldMask & whichField))
        _sfTranslationScaleFactor.syncWith(pFrom->_sfTranslationScaleFactor);

    if(FieldBits::NoField != (MatrixResultFieldMask & whichField))
        _sfMatrixResult.syncWith(pFrom->_sfMatrixResult);

    if(FieldBits::NoField != (RotationMatrixResultFieldMask & whichField))
        _sfRotationMatrixResult.syncWith(pFrom->_sfRotationMatrixResult);

    if(FieldBits::NoField != (ReferencePositionFieldMask & whichField))
        _sfReferencePosition.syncWith(pFrom->_sfReferencePosition);

    if(FieldBits::NoField != (ReferenceMatrixFieldMask & whichField))
        _sfReferenceMatrix.syncWith(pFrom->_sfReferenceMatrix);

    if(FieldBits::NoField != (TransformCenterFieldMask & whichField))
        _sfTransformCenter.syncWith(pFrom->_sfTransformCenter);

    if(FieldBits::NoField != (WorldDiagFieldMask & whichField))
        _sfWorldDiag.syncWith(pFrom->_sfWorldDiag);

    if(FieldBits::NoField != (MouseDataFieldMask & whichField))
        _sfMouseData.syncWith(pFrom->_sfMouseData);
}
#endif


inline
const Char8 *CSMTrackballBase::getClassname(void)
{
    return "CSMTrackball";
}
OSG_GEN_CONTAINERPTR(CSMTrackball);

OSG_END_NAMESPACE

