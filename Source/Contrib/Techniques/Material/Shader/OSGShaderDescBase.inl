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
 **     class ShaderDesc!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &ShaderDescBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 ShaderDescBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 ShaderDescBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the ShaderDesc::_sfShaderType field.

inline
GLenum &ShaderDescBase::editShaderType(void)
{
    editSField(ShaderTypeFieldMask);

    return _sfShaderType.getValue();
}

//! Get the value of the ShaderDesc::_sfShaderType field.
inline
const GLenum &ShaderDescBase::getShaderType(void) const
{
    return _sfShaderType.getValue();
}

//! Set the value of the ShaderDesc::_sfShaderType field.
inline
void ShaderDescBase::setShaderType(const GLenum &value)
{
    editSField(ShaderTypeFieldMask);

    _sfShaderType.setValue(value);
}
//! Get the value of the ShaderDesc::_sfProgram field.

inline
std::string &ShaderDescBase::editProgram(void)
{
    editSField(ProgramFieldMask);

    return _sfProgram.getValue();
}

//! Get the value of the ShaderDesc::_sfProgram field.
inline
const std::string &ShaderDescBase::getProgram(void) const
{
    return _sfProgram.getValue();
}

//! Set the value of the ShaderDesc::_sfProgram field.
inline
void ShaderDescBase::setProgram(const std::string &value)
{
    editSField(ProgramFieldMask);

    _sfProgram.setValue(value);
}
//! Get the value of the ShaderDesc::_sfHash field.

inline
UInt64 &ShaderDescBase::editHash(void)
{
    editSField(HashFieldMask);

    return _sfHash.getValue();
}

//! Get the value of the ShaderDesc::_sfHash field.
inline
      UInt64  ShaderDescBase::getHash(void) const
{
    return _sfHash.getValue();
}

//! Set the value of the ShaderDesc::_sfHash field.
inline
void ShaderDescBase::setHash(const UInt64 value)
{
    editSField(HashFieldMask);

    _sfHash.setValue(value);
}

//! Get the value of the \a index element the ShaderDesc::_mfUniformBlockNames field.
inline
const std::string &ShaderDescBase::getUniformBlockNames(const UInt32 index) const
{
    return _mfUniformBlockNames[index];
}

inline
MFString           ::reference ShaderDescBase::editUniformBlockNames(const UInt32 index)
{
    editMField(UniformBlockNamesFieldMask, _mfUniformBlockNames);

    return _mfUniformBlockNames[index];
}

//! Get the value of the \a index element the ShaderDesc::_mfUniformBindingPnts field.
inline
      Int32  ShaderDescBase::getUniformBindingPnts(const UInt32 index) const
{
    return _mfUniformBindingPnts[index];
}

inline
MFInt32            ::reference ShaderDescBase::editUniformBindingPnts(const UInt32 index)
{
    editMField(UniformBindingPntsFieldMask, _mfUniformBindingPnts);

    return _mfUniformBindingPnts[index];
}

//! Get the value of the \a index element the ShaderDesc::_mfShaderStorageBlockNames field.
inline
const std::string &ShaderDescBase::getShaderStorageBlockNames(const UInt32 index) const
{
    return _mfShaderStorageBlockNames[index];
}

inline
MFString           ::reference ShaderDescBase::editShaderStorageBlockNames(const UInt32 index)
{
    editMField(ShaderStorageBlockNamesFieldMask, _mfShaderStorageBlockNames);

    return _mfShaderStorageBlockNames[index];
}

//! Get the value of the \a index element the ShaderDesc::_mfShaderStorageBindingPnts field.
inline
      Int32  ShaderDescBase::getShaderStorageBindingPnts(const UInt32 index) const
{
    return _mfShaderStorageBindingPnts[index];
}

inline
MFInt32            ::reference ShaderDescBase::editShaderStorageBindingPnts(const UInt32 index)
{
    editMField(ShaderStorageBindingPntsFieldMask, _mfShaderStorageBindingPnts);

    return _mfShaderStorageBindingPnts[index];
}

//! Get the value of the \a index element the ShaderDesc::_mfOSGVariables field.
inline
const std::string &ShaderDescBase::getOSGVariables(const UInt32 index) const
{
    return _mfOSGVariables[index];
}

inline
MFString           ::reference ShaderDescBase::editOSGVariables(const UInt32 index)
{
    editMField(OSGVariablesFieldMask, _mfOSGVariables);

    return _mfOSGVariables[index];
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void ShaderDescBase::execSync (      ShaderDescBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ShaderTypeFieldMask & whichField))
        _sfShaderType.syncWith(pFrom->_sfShaderType);

    if(FieldBits::NoField != (ProgramFieldMask & whichField))
        _sfProgram.syncWith(pFrom->_sfProgram);

    if(FieldBits::NoField != (HashFieldMask & whichField))
        _sfHash.syncWith(pFrom->_sfHash);

    if(FieldBits::NoField != (ShaderProgramFieldMask & whichField))
        _sfShaderProgram.syncWith(pFrom->_sfShaderProgram);

    if(FieldBits::NoField != (UniformBlockNamesFieldMask & whichField))
        _mfUniformBlockNames.syncWith(pFrom->_mfUniformBlockNames,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (UniformBindingPntsFieldMask & whichField))
        _mfUniformBindingPnts.syncWith(pFrom->_mfUniformBindingPnts,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (ShaderStorageBlockNamesFieldMask & whichField))
        _mfShaderStorageBlockNames.syncWith(pFrom->_mfShaderStorageBlockNames,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (ShaderStorageBindingPntsFieldMask & whichField))
        _mfShaderStorageBindingPnts.syncWith(pFrom->_mfShaderStorageBindingPnts,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (OSGVariablesFieldMask & whichField))
        _mfOSGVariables.syncWith(pFrom->_mfOSGVariables,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);
}
#endif


inline
const Char8 *ShaderDescBase::getClassname(void)
{
    return "ShaderDesc";
}
OSG_GEN_CONTAINERPTR(ShaderDesc);

OSG_END_NAMESPACE

