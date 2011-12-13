/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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
 **     class MatrixTransformationElement!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &MatrixTransformationElementBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 MatrixTransformationElementBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 MatrixTransformationElementBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the MatrixTransformationElement::_sfMatrix field.

inline
Matrix &MatrixTransformationElementBase::editMatrix(void)
{
    editSField(MatrixFieldMask);

    return _sfMatrix.getValue();
}

//! Get the value of the MatrixTransformationElement::_sfMatrix field.
inline
const Matrix &MatrixTransformationElementBase::getMatrix(void) const
{
    return _sfMatrix.getValue();
}

//! Set the value of the MatrixTransformationElement::_sfMatrix field.
inline
void MatrixTransformationElementBase::setMatrix(const Matrix &value)
{
    editSField(MatrixFieldMask);

    _sfMatrix.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void MatrixTransformationElementBase::execSync (      MatrixTransformationElementBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (MatrixFieldMask & whichField))
        _sfMatrix.syncWith(pFrom->_sfMatrix);
}
#endif


inline
const Char8 *MatrixTransformationElementBase::getClassname(void)
{
    return "MatrixTransformationElement";
}
OSG_GEN_CONTAINERPTR(MatrixTransformationElement);

OSG_END_NAMESPACE
