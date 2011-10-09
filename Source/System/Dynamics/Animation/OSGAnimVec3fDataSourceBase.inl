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
 **     class AnimVec3fDataSource!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &AnimVec3fDataSourceBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 AnimVec3fDataSourceBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 AnimVec3fDataSourceBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/


//! Get the value of the \a index element the AnimVec3fDataSource::_mfValues field.
inline
const Vec3f &AnimVec3fDataSourceBase::getValues(const UInt32 index) const
{
    return _mfValues[index];
}

inline
Vec3f &AnimVec3fDataSourceBase::editValues(const UInt32 index)
{
    editMField(ValuesFieldMask, _mfValues);

    return _mfValues[index];
}


//! Get the value of the \a index element the AnimVec3fDataSource::_mfInTangentsX field.
inline
const Vec2f &AnimVec3fDataSourceBase::getInTangentsX(const UInt32 index) const
{
    return _mfInTangentsX[index];
}

inline
Vec2f &AnimVec3fDataSourceBase::editInTangentsX(const UInt32 index)
{
    editMField(InTangentsXFieldMask, _mfInTangentsX);

    return _mfInTangentsX[index];
}


//! Get the value of the \a index element the AnimVec3fDataSource::_mfInTangentsY field.
inline
const Vec2f &AnimVec3fDataSourceBase::getInTangentsY(const UInt32 index) const
{
    return _mfInTangentsY[index];
}

inline
Vec2f &AnimVec3fDataSourceBase::editInTangentsY(const UInt32 index)
{
    editMField(InTangentsYFieldMask, _mfInTangentsY);

    return _mfInTangentsY[index];
}


//! Get the value of the \a index element the AnimVec3fDataSource::_mfInTangentsZ field.
inline
const Vec2f &AnimVec3fDataSourceBase::getInTangentsZ(const UInt32 index) const
{
    return _mfInTangentsZ[index];
}

inline
Vec2f &AnimVec3fDataSourceBase::editInTangentsZ(const UInt32 index)
{
    editMField(InTangentsZFieldMask, _mfInTangentsZ);

    return _mfInTangentsZ[index];
}


//! Get the value of the \a index element the AnimVec3fDataSource::_mfOutTangentsX field.
inline
const Vec2f &AnimVec3fDataSourceBase::getOutTangentsX(const UInt32 index) const
{
    return _mfOutTangentsX[index];
}

inline
Vec2f &AnimVec3fDataSourceBase::editOutTangentsX(const UInt32 index)
{
    editMField(OutTangentsXFieldMask, _mfOutTangentsX);

    return _mfOutTangentsX[index];
}


//! Get the value of the \a index element the AnimVec3fDataSource::_mfOutTangentsY field.
inline
const Vec2f &AnimVec3fDataSourceBase::getOutTangentsY(const UInt32 index) const
{
    return _mfOutTangentsY[index];
}

inline
Vec2f &AnimVec3fDataSourceBase::editOutTangentsY(const UInt32 index)
{
    editMField(OutTangentsYFieldMask, _mfOutTangentsY);

    return _mfOutTangentsY[index];
}


//! Get the value of the \a index element the AnimVec3fDataSource::_mfOutTangentsZ field.
inline
const Vec2f &AnimVec3fDataSourceBase::getOutTangentsZ(const UInt32 index) const
{
    return _mfOutTangentsZ[index];
}

inline
Vec2f &AnimVec3fDataSourceBase::editOutTangentsZ(const UInt32 index)
{
    editMField(OutTangentsZFieldMask, _mfOutTangentsZ);

    return _mfOutTangentsZ[index];
}



#ifdef OSG_MT_CPTR_ASPECT
inline
void AnimVec3fDataSourceBase::execSync (      AnimVec3fDataSourceBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ValuesFieldMask & whichField))
        _mfValues.syncWith(pFrom->_mfValues,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (InTangentsXFieldMask & whichField))
        _mfInTangentsX.syncWith(pFrom->_mfInTangentsX,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (InTangentsYFieldMask & whichField))
        _mfInTangentsY.syncWith(pFrom->_mfInTangentsY,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (InTangentsZFieldMask & whichField))
        _mfInTangentsZ.syncWith(pFrom->_mfInTangentsZ,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (OutTangentsXFieldMask & whichField))
        _mfOutTangentsX.syncWith(pFrom->_mfOutTangentsX,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (OutTangentsYFieldMask & whichField))
        _mfOutTangentsY.syncWith(pFrom->_mfOutTangentsY,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (OutTangentsZFieldMask & whichField))
        _mfOutTangentsZ.syncWith(pFrom->_mfOutTangentsZ,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);
}
#endif


inline
const Char8 *AnimVec3fDataSourceBase::getClassname(void)
{
    return "AnimVec3fDataSource";
}
OSG_GEN_CONTAINERPTR(AnimVec3fDataSource);

OSG_END_NAMESPACE

