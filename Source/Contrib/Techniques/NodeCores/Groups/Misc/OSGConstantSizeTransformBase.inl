/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
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
 **     class ConstantSizeTransform!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &ConstantSizeTransformBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 ConstantSizeTransformBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 ConstantSizeTransformBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the ConstantSizeTransform::_sfDistance field.

inline
Real32 &ConstantSizeTransformBase::editDistance(void)
{
    editSField(DistanceFieldMask);

    return _sfDistance.getValue();
}

//! Get the value of the ConstantSizeTransform::_sfDistance field.
inline
      Real32  ConstantSizeTransformBase::getDistance(void) const
{
    return _sfDistance.getValue();
}

//! Set the value of the ConstantSizeTransform::_sfDistance field.
inline
void ConstantSizeTransformBase::setDistance(const Real32 value)
{
    editSField(DistanceFieldMask);

    _sfDistance.setValue(value);
}
//! Get the value of the ConstantSizeTransform::_sfTransform field.

inline
Matrix &ConstantSizeTransformBase::editTransform(void)
{
    editSField(TransformFieldMask);

    return _sfTransform.getValue();
}

//! Get the value of the ConstantSizeTransform::_sfTransform field.
inline
const Matrix &ConstantSizeTransformBase::getTransform(void) const
{
    return _sfTransform.getValue();
}

//! Set the value of the ConstantSizeTransform::_sfTransform field.
inline
void ConstantSizeTransformBase::setTransform(const Matrix &value)
{
    editSField(TransformFieldMask);

    _sfTransform.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void ConstantSizeTransformBase::execSync (      ConstantSizeTransformBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (DistanceFieldMask & whichField))
        _sfDistance.syncWith(pFrom->_sfDistance);

    if(FieldBits::NoField != (TransformFieldMask & whichField))
        _sfTransform.syncWith(pFrom->_sfTransform);
}
#endif


inline
const Char8 *ConstantSizeTransformBase::getClassname(void)
{
    return "ConstantSizeTransform";
}
OSG_GEN_CONTAINERPTR(ConstantSizeTransform);

OSG_END_NAMESPACE

