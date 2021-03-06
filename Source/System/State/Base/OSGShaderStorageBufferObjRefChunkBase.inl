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
 **     class ShaderStorageBufferObjRefChunk!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &ShaderStorageBufferObjRefChunkBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 ShaderStorageBufferObjRefChunkBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 ShaderStorageBufferObjRefChunkBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the ShaderStorageBufferObjRefChunk::_sfOglGLId field.

inline
GLenum &ShaderStorageBufferObjRefChunkBase::editOglGLId(void)
{
    editSField(OglGLIdFieldMask);

    return _sfOglGLId.getValue();
}

//! Get the value of the ShaderStorageBufferObjRefChunk::_sfOglGLId field.
inline
const GLenum &ShaderStorageBufferObjRefChunkBase::getOglGLId(void) const
{
    return _sfOglGLId.getValue();
}

//! Set the value of the ShaderStorageBufferObjRefChunk::_sfOglGLId field.
inline
void ShaderStorageBufferObjRefChunkBase::setOglGLId(const GLenum &value)
{
    editSField(OglGLIdFieldMask);

    _sfOglGLId.setValue(value);
}
//! Get the value of the ShaderStorageBufferObjRefChunk::_sfOsgGLId field.

inline
GLenum &ShaderStorageBufferObjRefChunkBase::editOsgGLId(void)
{
    editSField(OsgGLIdFieldMask);

    return _sfOsgGLId.getValue();
}

//! Get the value of the ShaderStorageBufferObjRefChunk::_sfOsgGLId field.
inline
const GLenum &ShaderStorageBufferObjRefChunkBase::getOsgGLId(void) const
{
    return _sfOsgGLId.getValue();
}

//! Set the value of the ShaderStorageBufferObjRefChunk::_sfOsgGLId field.
inline
void ShaderStorageBufferObjRefChunkBase::setOsgGLId(const GLenum &value)
{
    editSField(OsgGLIdFieldMask);

    _sfOsgGLId.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void ShaderStorageBufferObjRefChunkBase::execSync (      ShaderStorageBufferObjRefChunkBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (OglGLIdFieldMask & whichField))
        _sfOglGLId.syncWith(pFrom->_sfOglGLId);

    if(FieldBits::NoField != (OsgGLIdFieldMask & whichField))
        _sfOsgGLId.syncWith(pFrom->_sfOsgGLId);
}
#endif


inline
const Char8 *ShaderStorageBufferObjRefChunkBase::getClassname(void)
{
    return "ShaderStorageBufferObjRefChunk";
}
OSG_GEN_CONTAINERPTR(ShaderStorageBufferObjRefChunk);

OSG_END_NAMESPACE

