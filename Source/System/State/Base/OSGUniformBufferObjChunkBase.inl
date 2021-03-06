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
 **     class UniformBufferObjChunk!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &UniformBufferObjChunkBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 UniformBufferObjChunkBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 UniformBufferObjChunkBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the UniformBufferObjChunk::_sfGLId field.

inline
GLenum &UniformBufferObjChunkBase::editGLId(void)
{
    editSField(GLIdFieldMask);

    return _sfGLId.getValue();
}

//! Get the value of the UniformBufferObjChunk::_sfGLId field.
inline
const GLenum &UniformBufferObjChunkBase::getGLId(void) const
{
    return _sfGLId.getValue();
}

//! Set the value of the UniformBufferObjChunk::_sfGLId field.
inline
void UniformBufferObjChunkBase::setGLId(const GLenum &value)
{
    editSField(GLIdFieldMask);

    _sfGLId.setValue(value);
}
//! Get the value of the UniformBufferObjChunk::_sfUsage field.

inline
GLenum &UniformBufferObjChunkBase::editUsage(void)
{
    editSField(UsageFieldMask);

    return _sfUsage.getValue();
}

//! Get the value of the UniformBufferObjChunk::_sfUsage field.
inline
const GLenum &UniformBufferObjChunkBase::getUsage(void) const
{
    return _sfUsage.getValue();
}

//! Set the value of the UniformBufferObjChunk::_sfUsage field.
inline
void UniformBufferObjChunkBase::setUsage(const GLenum &value)
{
    editSField(UsageFieldMask);

    _sfUsage.setValue(value);
}
//! Get the value of the UniformBufferObjChunk::_sfBlockName field.

inline
std::string &UniformBufferObjChunkBase::editBlockName(void)
{
    editSField(BlockNameFieldMask);

    return _sfBlockName.getValue();
}

//! Get the value of the UniformBufferObjChunk::_sfBlockName field.
inline
const std::string &UniformBufferObjChunkBase::getBlockName(void) const
{
    return _sfBlockName.getValue();
}

//! Set the value of the UniformBufferObjChunk::_sfBlockName field.
inline
void UniformBufferObjChunkBase::setBlockName(const std::string &value)
{
    editSField(BlockNameFieldMask);

    _sfBlockName.setValue(value);
}
//! Get the value of the UniformBufferObjChunk::_sfNameToIndex field.

inline
StringToUInt32Map &UniformBufferObjChunkBase::editNameToIndex(void)
{
    editSField(NameToIndexFieldMask);

    return _sfNameToIndex.getValue();
}

//! Get the value of the UniformBufferObjChunk::_sfNameToIndex field.
inline
const StringToUInt32Map &UniformBufferObjChunkBase::getNameToIndex(void) const
{
    return _sfNameToIndex.getValue();
}

//! Set the value of the UniformBufferObjChunk::_sfNameToIndex field.
inline
void UniformBufferObjChunkBase::setNameToIndex(const StringToUInt32Map &value)
{
    editSField(NameToIndexFieldMask);

    _sfNameToIndex.setValue(value);
}

//! Get the value of the \a index element the UniformBufferObjChunk::_mfFundamentalTypes field.
inline
      UInt8  UniformBufferObjChunkBase::getFundamentalTypes(const UInt32 index) const
{
    return _mfFundamentalTypes[index];
}

inline
MFUInt8            ::reference UniformBufferObjChunkBase::editFundamentalTypes(const UInt32 index)
{
    editMField(FundamentalTypesFieldMask, _mfFundamentalTypes);

    return _mfFundamentalTypes[index];
}

//! Get the value of the \a index element the UniformBufferObjChunk::_mfMainTypes field.
inline
      UInt8  UniformBufferObjChunkBase::getMainTypes(const UInt32 index) const
{
    return _mfMainTypes[index];
}

inline
MFUInt8            ::reference UniformBufferObjChunkBase::editMainTypes(const UInt32 index)
{
    editMField(MainTypesFieldMask, _mfMainTypes);

    return _mfMainTypes[index];
}

//! Get the value of the \a index element the UniformBufferObjChunk::_mfCardinality field.
inline
      UInt32  UniformBufferObjChunkBase::getCardinality(const UInt32 index) const
{
    return _mfCardinality[index];
}

inline
MFUInt32           ::reference UniformBufferObjChunkBase::editCardinality(const UInt32 index)
{
    editMField(CardinalityFieldMask, _mfCardinality);

    return _mfCardinality[index];
}

//! Get the value of the \a index element the UniformBufferObjChunk::_mfIndex field.
inline
      UInt32  UniformBufferObjChunkBase::getIndex(const UInt32 index) const
{
    return _mfIndex[index];
}

inline
MFUInt32           ::reference UniformBufferObjChunkBase::editIndex(const UInt32 index)
{
    editMField(IndexFieldMask, _mfIndex);

    return _mfIndex[index];
}

//! Get the value of the \a index element the UniformBufferObjChunk::_mfNames field.
inline
const std::string &UniformBufferObjChunkBase::getNames(const UInt32 index) const
{
    return _mfNames[index];
}

inline
MFString           ::reference UniformBufferObjChunkBase::editNames(const UInt32 index)
{
    editMField(NamesFieldMask, _mfNames);

    return _mfNames[index];
}

//! Get the value of the \a index element the UniformBufferObjChunk::_mfFloatValues field.
inline
      Real32  UniformBufferObjChunkBase::getFloatValues(const UInt32 index) const
{
    return _mfFloatValues[index];
}

inline
MFReal32           ::reference UniformBufferObjChunkBase::editFloatValues(const UInt32 index)
{
    editMField(FloatValuesFieldMask, _mfFloatValues);

    return _mfFloatValues[index];
}

//! Get the value of the \a index element the UniformBufferObjChunk::_mfDoubleValues field.
inline
      Real64  UniformBufferObjChunkBase::getDoubleValues(const UInt32 index) const
{
    return _mfDoubleValues[index];
}

inline
MFReal64           ::reference UniformBufferObjChunkBase::editDoubleValues(const UInt32 index)
{
    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    return _mfDoubleValues[index];
}

//! Get the value of the \a index element the UniformBufferObjChunk::_mfIntValues field.
inline
      Int32  UniformBufferObjChunkBase::getIntValues(const UInt32 index) const
{
    return _mfIntValues[index];
}

inline
MFInt32            ::reference UniformBufferObjChunkBase::editIntValues(const UInt32 index)
{
    editMField(IntValuesFieldMask, _mfIntValues);

    return _mfIntValues[index];
}

//! Get the value of the \a index element the UniformBufferObjChunk::_mfUIntValues field.
inline
      UInt32  UniformBufferObjChunkBase::getUIntValues(const UInt32 index) const
{
    return _mfUIntValues[index];
}

inline
MFUInt32           ::reference UniformBufferObjChunkBase::editUIntValues(const UInt32 index)
{
    editMField(UIntValuesFieldMask, _mfUIntValues);

    return _mfUIntValues[index];
}

//! Get the value of the \a index element the UniformBufferObjChunk::_mfBoolValues field.
inline
      UInt8  UniformBufferObjChunkBase::getBoolValues(const UInt32 index) const
{
    return _mfBoolValues[index];
}

inline
MFUInt8            ::reference UniformBufferObjChunkBase::editBoolValues(const UInt32 index)
{
    editMField(BoolValuesFieldMask, _mfBoolValues);

    return _mfBoolValues[index];
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void UniformBufferObjChunkBase::execSync (      UniformBufferObjChunkBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (GLIdFieldMask & whichField))
        _sfGLId.syncWith(pFrom->_sfGLId);

    if(FieldBits::NoField != (UsageFieldMask & whichField))
        _sfUsage.syncWith(pFrom->_sfUsage);

    if(FieldBits::NoField != (BlockNameFieldMask & whichField))
        _sfBlockName.syncWith(pFrom->_sfBlockName);

    if(FieldBits::NoField != (FundamentalTypesFieldMask & whichField))
        _mfFundamentalTypes.syncWith(pFrom->_mfFundamentalTypes,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (MainTypesFieldMask & whichField))
        _mfMainTypes.syncWith(pFrom->_mfMainTypes,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (CardinalityFieldMask & whichField))
        _mfCardinality.syncWith(pFrom->_mfCardinality,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (IndexFieldMask & whichField))
        _mfIndex.syncWith(pFrom->_mfIndex,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (NamesFieldMask & whichField))
        _mfNames.syncWith(pFrom->_mfNames,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (NameToIndexFieldMask & whichField))
        _sfNameToIndex.syncWith(pFrom->_sfNameToIndex);

    if(FieldBits::NoField != (FloatValuesFieldMask & whichField))
        _mfFloatValues.syncWith(pFrom->_mfFloatValues,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (DoubleValuesFieldMask & whichField))
        _mfDoubleValues.syncWith(pFrom->_mfDoubleValues,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (IntValuesFieldMask & whichField))
        _mfIntValues.syncWith(pFrom->_mfIntValues,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (UIntValuesFieldMask & whichField))
        _mfUIntValues.syncWith(pFrom->_mfUIntValues,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (BoolValuesFieldMask & whichField))
        _mfBoolValues.syncWith(pFrom->_mfBoolValues,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);
}
#endif


inline
const Char8 *UniformBufferObjChunkBase::getClassname(void)
{
    return "UniformBufferObjChunk";
}
OSG_GEN_CONTAINERPTR(UniformBufferObjChunk);

OSG_END_NAMESPACE

