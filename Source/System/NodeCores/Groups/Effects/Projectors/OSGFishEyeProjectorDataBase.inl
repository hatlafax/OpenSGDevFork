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
 **     class FishEyeProjectorData!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &FishEyeProjectorDataBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 FishEyeProjectorDataBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 FishEyeProjectorDataBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/


//! Get the value of the FishEyeProjectorData::_sfRenderTarget field.
inline
FrameBufferObject * FishEyeProjectorDataBase::getRenderTarget(void) const
{
    return _sfRenderTarget.getValue();
}

//! Set the value of the FishEyeProjectorData::_sfRenderTarget field.
inline
void FishEyeProjectorDataBase::setRenderTarget(FrameBufferObject * const value)
{
    editSField(RenderTargetFieldMask);

    _sfRenderTarget.setValue(value);
}
//! Get the value of the FishEyeProjectorData::_sfTextureRes field.

inline
UInt32 &FishEyeProjectorDataBase::editTextureRes(void)
{
    editSField(TextureResFieldMask);

    return _sfTextureRes.getValue();
}

//! Get the value of the FishEyeProjectorData::_sfTextureRes field.
inline
      UInt32  FishEyeProjectorDataBase::getTextureRes(void) const
{
    return _sfTextureRes.getValue();
}

//! Set the value of the FishEyeProjectorData::_sfTextureRes field.
inline
void FishEyeProjectorDataBase::setTextureRes(const UInt32 value)
{
    editSField(TextureResFieldMask);

    _sfTextureRes.setValue(value);
}
//! Get the value of the FishEyeProjectorData::_sfTextureFormat field.

inline
GLenum &FishEyeProjectorDataBase::editTextureFormat(void)
{
    editSField(TextureFormatFieldMask);

    return _sfTextureFormat.getValue();
}

//! Get the value of the FishEyeProjectorData::_sfTextureFormat field.
inline
const GLenum &FishEyeProjectorDataBase::getTextureFormat(void) const
{
    return _sfTextureFormat.getValue();
}

//! Set the value of the FishEyeProjectorData::_sfTextureFormat field.
inline
void FishEyeProjectorDataBase::setTextureFormat(const GLenum &value)
{
    editSField(TextureFormatFieldMask);

    _sfTextureFormat.setValue(value);
}

//! Get the value of the FishEyeProjectorData::_sfCamera field.
inline
Camera * FishEyeProjectorDataBase::getCamera(void) const
{
    return _sfCamera.getValue();
}

//! Set the value of the FishEyeProjectorData::_sfCamera field.
inline
void FishEyeProjectorDataBase::setCamera(Camera * const value)
{
    editSField(CameraFieldMask);

    _sfCamera.setValue(value);
}

//! Get the value of the \a index element the FishEyeProjectorData::_mfTextures field.
inline
TextureObjChunk * FishEyeProjectorDataBase::getTextures(const UInt32 index) const
{
    return _mfTextures[index];
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void FishEyeProjectorDataBase::execSync (      FishEyeProjectorDataBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (RenderTargetFieldMask & whichField))
        _sfRenderTarget.syncWith(pFrom->_sfRenderTarget);

    if(FieldBits::NoField != (TexturesFieldMask & whichField))
        _mfTextures.syncWith(pFrom->_mfTextures,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (TextureResFieldMask & whichField))
        _sfTextureRes.syncWith(pFrom->_sfTextureRes);

    if(FieldBits::NoField != (TextureFormatFieldMask & whichField))
        _sfTextureFormat.syncWith(pFrom->_sfTextureFormat);

    if(FieldBits::NoField != (CameraFieldMask & whichField))
        _sfCamera.syncWith(pFrom->_sfCamera);
}
#endif


inline
const Char8 *FishEyeProjectorDataBase::getClassname(void)
{
    return "FishEyeProjectorData";
}
OSG_GEN_CONTAINERPTR(FishEyeProjectorData);

OSG_END_NAMESPACE

