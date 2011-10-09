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
 **     class SkeletonJoint!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &SkeletonJointBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 SkeletonJointBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 SkeletonJointBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the SkeletonJoint::_sfInvBindMatrix field.

inline
Matrix &SkeletonJointBase::editInvBindMatrix(void)
{
    editSField(InvBindMatrixFieldMask);

    return _sfInvBindMatrix.getValue();
}

//! Get the value of the SkeletonJoint::_sfInvBindMatrix field.
inline
const Matrix &SkeletonJointBase::getInvBindMatrix(void) const
{
    return _sfInvBindMatrix.getValue();
}

//! Set the value of the SkeletonJoint::_sfInvBindMatrix field.
inline
void SkeletonJointBase::setInvBindMatrix(const Matrix &value)
{
    editSField(InvBindMatrixFieldMask);

    _sfInvBindMatrix.setValue(value);
}
//! Get the value of the SkeletonJoint::_sfMatrix field.

inline
Matrix &SkeletonJointBase::editMatrix(void)
{
    editSField(MatrixFieldMask);

    return _sfMatrix.getValue();
}

//! Get the value of the SkeletonJoint::_sfMatrix field.
inline
const Matrix &SkeletonJointBase::getMatrix(void) const
{
    return _sfMatrix.getValue();
}

//! Set the value of the SkeletonJoint::_sfMatrix field.
inline
void SkeletonJointBase::setMatrix(const Matrix &value)
{
    editSField(MatrixFieldMask);

    _sfMatrix.setValue(value);
}
//! Get the value of the SkeletonJoint::_sfOffsetMatrix field.

inline
Matrix &SkeletonJointBase::editOffsetMatrix(void)
{
    editSField(OffsetMatrixFieldMask);

    return _sfOffsetMatrix.getValue();
}

//! Get the value of the SkeletonJoint::_sfOffsetMatrix field.
inline
const Matrix &SkeletonJointBase::getOffsetMatrix(void) const
{
    return _sfOffsetMatrix.getValue();
}

//! Set the value of the SkeletonJoint::_sfOffsetMatrix field.
inline
void SkeletonJointBase::setOffsetMatrix(const Matrix &value)
{
    editSField(OffsetMatrixFieldMask);

    _sfOffsetMatrix.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void SkeletonJointBase::execSync (      SkeletonJointBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (InvBindMatrixFieldMask & whichField))
        _sfInvBindMatrix.syncWith(pFrom->_sfInvBindMatrix);

    if(FieldBits::NoField != (MatrixFieldMask & whichField))
        _sfMatrix.syncWith(pFrom->_sfMatrix);

    if(FieldBits::NoField != (OffsetMatrixFieldMask & whichField))
        _sfOffsetMatrix.syncWith(pFrom->_sfOffsetMatrix);
}
#endif


inline
const Char8 *SkeletonJointBase::getClassname(void)
{
    return "SkeletonJoint";
}
OSG_GEN_CONTAINERPTR(SkeletonJoint);

OSG_END_NAMESPACE

