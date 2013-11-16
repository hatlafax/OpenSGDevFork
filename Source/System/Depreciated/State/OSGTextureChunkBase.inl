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
 **     class TextureChunk!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &TextureChunkBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 TextureChunkBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 TextureChunkBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the TextureChunk::_sfEnvMode field.

inline
GLenum &TextureChunkBase::editEnvMode(void)
{
    editSField(EnvModeFieldMask);

    return _sfEnvMode.getValue();
}

//! Get the value of the TextureChunk::_sfEnvMode field.
inline
const GLenum &TextureChunkBase::getEnvMode(void) const
{
    return _sfEnvMode.getValue();
}

//! Set the value of the TextureChunk::_sfEnvMode field.
inline
void TextureChunkBase::setEnvMode(const GLenum &value)
{
    editSField(EnvModeFieldMask);

    _sfEnvMode.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvColor field.

inline
Color4f &TextureChunkBase::editEnvColor(void)
{
    editSField(EnvColorFieldMask);

    return _sfEnvColor.getValue();
}

//! Get the value of the TextureChunk::_sfEnvColor field.
inline
const Color4f &TextureChunkBase::getEnvColor(void) const
{
    return _sfEnvColor.getValue();
}

//! Set the value of the TextureChunk::_sfEnvColor field.
inline
void TextureChunkBase::setEnvColor(const Color4f &value)
{
    editSField(EnvColorFieldMask);

    _sfEnvColor.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvCombineRGB field.

inline
GLenum &TextureChunkBase::editEnvCombineRGB(void)
{
    editSField(EnvCombineRGBFieldMask);

    return _sfEnvCombineRGB.getValue();
}

//! Get the value of the TextureChunk::_sfEnvCombineRGB field.
inline
const GLenum &TextureChunkBase::getEnvCombineRGB(void) const
{
    return _sfEnvCombineRGB.getValue();
}

//! Set the value of the TextureChunk::_sfEnvCombineRGB field.
inline
void TextureChunkBase::setEnvCombineRGB(const GLenum &value)
{
    editSField(EnvCombineRGBFieldMask);

    _sfEnvCombineRGB.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvCombineAlpha field.

inline
GLenum &TextureChunkBase::editEnvCombineAlpha(void)
{
    editSField(EnvCombineAlphaFieldMask);

    return _sfEnvCombineAlpha.getValue();
}

//! Get the value of the TextureChunk::_sfEnvCombineAlpha field.
inline
const GLenum &TextureChunkBase::getEnvCombineAlpha(void) const
{
    return _sfEnvCombineAlpha.getValue();
}

//! Set the value of the TextureChunk::_sfEnvCombineAlpha field.
inline
void TextureChunkBase::setEnvCombineAlpha(const GLenum &value)
{
    editSField(EnvCombineAlphaFieldMask);

    _sfEnvCombineAlpha.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvScaleRGB field.

inline
Real32 &TextureChunkBase::editEnvScaleRGB(void)
{
    editSField(EnvScaleRGBFieldMask);

    return _sfEnvScaleRGB.getValue();
}

//! Get the value of the TextureChunk::_sfEnvScaleRGB field.
inline
      Real32  TextureChunkBase::getEnvScaleRGB(void) const
{
    return _sfEnvScaleRGB.getValue();
}

//! Set the value of the TextureChunk::_sfEnvScaleRGB field.
inline
void TextureChunkBase::setEnvScaleRGB(const Real32 value)
{
    editSField(EnvScaleRGBFieldMask);

    _sfEnvScaleRGB.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvScaleAlpha field.

inline
Real32 &TextureChunkBase::editEnvScaleAlpha(void)
{
    editSField(EnvScaleAlphaFieldMask);

    return _sfEnvScaleAlpha.getValue();
}

//! Get the value of the TextureChunk::_sfEnvScaleAlpha field.
inline
      Real32  TextureChunkBase::getEnvScaleAlpha(void) const
{
    return _sfEnvScaleAlpha.getValue();
}

//! Set the value of the TextureChunk::_sfEnvScaleAlpha field.
inline
void TextureChunkBase::setEnvScaleAlpha(const Real32 value)
{
    editSField(EnvScaleAlphaFieldMask);

    _sfEnvScaleAlpha.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvSource0RGB field.

inline
GLenum &TextureChunkBase::editEnvSource0RGB(void)
{
    editSField(EnvSource0RGBFieldMask);

    return _sfEnvSource0RGB.getValue();
}

//! Get the value of the TextureChunk::_sfEnvSource0RGB field.
inline
const GLenum &TextureChunkBase::getEnvSource0RGB(void) const
{
    return _sfEnvSource0RGB.getValue();
}

//! Set the value of the TextureChunk::_sfEnvSource0RGB field.
inline
void TextureChunkBase::setEnvSource0RGB(const GLenum &value)
{
    editSField(EnvSource0RGBFieldMask);

    _sfEnvSource0RGB.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvSource1RGB field.

inline
GLenum &TextureChunkBase::editEnvSource1RGB(void)
{
    editSField(EnvSource1RGBFieldMask);

    return _sfEnvSource1RGB.getValue();
}

//! Get the value of the TextureChunk::_sfEnvSource1RGB field.
inline
const GLenum &TextureChunkBase::getEnvSource1RGB(void) const
{
    return _sfEnvSource1RGB.getValue();
}

//! Set the value of the TextureChunk::_sfEnvSource1RGB field.
inline
void TextureChunkBase::setEnvSource1RGB(const GLenum &value)
{
    editSField(EnvSource1RGBFieldMask);

    _sfEnvSource1RGB.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvSource2RGB field.

inline
GLenum &TextureChunkBase::editEnvSource2RGB(void)
{
    editSField(EnvSource2RGBFieldMask);

    return _sfEnvSource2RGB.getValue();
}

//! Get the value of the TextureChunk::_sfEnvSource2RGB field.
inline
const GLenum &TextureChunkBase::getEnvSource2RGB(void) const
{
    return _sfEnvSource2RGB.getValue();
}

//! Set the value of the TextureChunk::_sfEnvSource2RGB field.
inline
void TextureChunkBase::setEnvSource2RGB(const GLenum &value)
{
    editSField(EnvSource2RGBFieldMask);

    _sfEnvSource2RGB.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvSource0Alpha field.

inline
GLenum &TextureChunkBase::editEnvSource0Alpha(void)
{
    editSField(EnvSource0AlphaFieldMask);

    return _sfEnvSource0Alpha.getValue();
}

//! Get the value of the TextureChunk::_sfEnvSource0Alpha field.
inline
const GLenum &TextureChunkBase::getEnvSource0Alpha(void) const
{
    return _sfEnvSource0Alpha.getValue();
}

//! Set the value of the TextureChunk::_sfEnvSource0Alpha field.
inline
void TextureChunkBase::setEnvSource0Alpha(const GLenum &value)
{
    editSField(EnvSource0AlphaFieldMask);

    _sfEnvSource0Alpha.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvSource1Alpha field.

inline
GLenum &TextureChunkBase::editEnvSource1Alpha(void)
{
    editSField(EnvSource1AlphaFieldMask);

    return _sfEnvSource1Alpha.getValue();
}

//! Get the value of the TextureChunk::_sfEnvSource1Alpha field.
inline
const GLenum &TextureChunkBase::getEnvSource1Alpha(void) const
{
    return _sfEnvSource1Alpha.getValue();
}

//! Set the value of the TextureChunk::_sfEnvSource1Alpha field.
inline
void TextureChunkBase::setEnvSource1Alpha(const GLenum &value)
{
    editSField(EnvSource1AlphaFieldMask);

    _sfEnvSource1Alpha.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvSource2Alpha field.

inline
GLenum &TextureChunkBase::editEnvSource2Alpha(void)
{
    editSField(EnvSource2AlphaFieldMask);

    return _sfEnvSource2Alpha.getValue();
}

//! Get the value of the TextureChunk::_sfEnvSource2Alpha field.
inline
const GLenum &TextureChunkBase::getEnvSource2Alpha(void) const
{
    return _sfEnvSource2Alpha.getValue();
}

//! Set the value of the TextureChunk::_sfEnvSource2Alpha field.
inline
void TextureChunkBase::setEnvSource2Alpha(const GLenum &value)
{
    editSField(EnvSource2AlphaFieldMask);

    _sfEnvSource2Alpha.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvOperand0RGB field.

inline
GLenum &TextureChunkBase::editEnvOperand0RGB(void)
{
    editSField(EnvOperand0RGBFieldMask);

    return _sfEnvOperand0RGB.getValue();
}

//! Get the value of the TextureChunk::_sfEnvOperand0RGB field.
inline
const GLenum &TextureChunkBase::getEnvOperand0RGB(void) const
{
    return _sfEnvOperand0RGB.getValue();
}

//! Set the value of the TextureChunk::_sfEnvOperand0RGB field.
inline
void TextureChunkBase::setEnvOperand0RGB(const GLenum &value)
{
    editSField(EnvOperand0RGBFieldMask);

    _sfEnvOperand0RGB.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvOperand1RGB field.

inline
GLenum &TextureChunkBase::editEnvOperand1RGB(void)
{
    editSField(EnvOperand1RGBFieldMask);

    return _sfEnvOperand1RGB.getValue();
}

//! Get the value of the TextureChunk::_sfEnvOperand1RGB field.
inline
const GLenum &TextureChunkBase::getEnvOperand1RGB(void) const
{
    return _sfEnvOperand1RGB.getValue();
}

//! Set the value of the TextureChunk::_sfEnvOperand1RGB field.
inline
void TextureChunkBase::setEnvOperand1RGB(const GLenum &value)
{
    editSField(EnvOperand1RGBFieldMask);

    _sfEnvOperand1RGB.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvOperand2RGB field.

inline
GLenum &TextureChunkBase::editEnvOperand2RGB(void)
{
    editSField(EnvOperand2RGBFieldMask);

    return _sfEnvOperand2RGB.getValue();
}

//! Get the value of the TextureChunk::_sfEnvOperand2RGB field.
inline
const GLenum &TextureChunkBase::getEnvOperand2RGB(void) const
{
    return _sfEnvOperand2RGB.getValue();
}

//! Set the value of the TextureChunk::_sfEnvOperand2RGB field.
inline
void TextureChunkBase::setEnvOperand2RGB(const GLenum &value)
{
    editSField(EnvOperand2RGBFieldMask);

    _sfEnvOperand2RGB.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvOperand0Alpha field.

inline
GLenum &TextureChunkBase::editEnvOperand0Alpha(void)
{
    editSField(EnvOperand0AlphaFieldMask);

    return _sfEnvOperand0Alpha.getValue();
}

//! Get the value of the TextureChunk::_sfEnvOperand0Alpha field.
inline
const GLenum &TextureChunkBase::getEnvOperand0Alpha(void) const
{
    return _sfEnvOperand0Alpha.getValue();
}

//! Set the value of the TextureChunk::_sfEnvOperand0Alpha field.
inline
void TextureChunkBase::setEnvOperand0Alpha(const GLenum &value)
{
    editSField(EnvOperand0AlphaFieldMask);

    _sfEnvOperand0Alpha.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvOperand1Alpha field.

inline
GLenum &TextureChunkBase::editEnvOperand1Alpha(void)
{
    editSField(EnvOperand1AlphaFieldMask);

    return _sfEnvOperand1Alpha.getValue();
}

//! Get the value of the TextureChunk::_sfEnvOperand1Alpha field.
inline
const GLenum &TextureChunkBase::getEnvOperand1Alpha(void) const
{
    return _sfEnvOperand1Alpha.getValue();
}

//! Set the value of the TextureChunk::_sfEnvOperand1Alpha field.
inline
void TextureChunkBase::setEnvOperand1Alpha(const GLenum &value)
{
    editSField(EnvOperand1AlphaFieldMask);

    _sfEnvOperand1Alpha.setValue(value);
}
//! Get the value of the TextureChunk::_sfEnvOperand2Alpha field.

inline
GLenum &TextureChunkBase::editEnvOperand2Alpha(void)
{
    editSField(EnvOperand2AlphaFieldMask);

    return _sfEnvOperand2Alpha.getValue();
}

//! Get the value of the TextureChunk::_sfEnvOperand2Alpha field.
inline
const GLenum &TextureChunkBase::getEnvOperand2Alpha(void) const
{
    return _sfEnvOperand2Alpha.getValue();
}

//! Set the value of the TextureChunk::_sfEnvOperand2Alpha field.
inline
void TextureChunkBase::setEnvOperand2Alpha(const GLenum &value)
{
    editSField(EnvOperand2AlphaFieldMask);

    _sfEnvOperand2Alpha.setValue(value);
}
//! Get the value of the TextureChunk::_sfPointSprite field.

inline
bool &TextureChunkBase::editPointSprite(void)
{
    editSField(PointSpriteFieldMask);

    return _sfPointSprite.getValue();
}

//! Get the value of the TextureChunk::_sfPointSprite field.
inline
      bool  TextureChunkBase::getPointSprite(void) const
{
    return _sfPointSprite.getValue();
}

//! Set the value of the TextureChunk::_sfPointSprite field.
inline
void TextureChunkBase::setPointSprite(const bool value)
{
    editSField(PointSpriteFieldMask);

    _sfPointSprite.setValue(value);
}
//! Get the value of the TextureChunk::_sfShaderOperation field.

inline
GLenum &TextureChunkBase::editShaderOperation(void)
{
    editSField(ShaderOperationFieldMask);

    return _sfShaderOperation.getValue();
}

//! Get the value of the TextureChunk::_sfShaderOperation field.
inline
const GLenum &TextureChunkBase::getShaderOperation(void) const
{
    return _sfShaderOperation.getValue();
}

//! Set the value of the TextureChunk::_sfShaderOperation field.
inline
void TextureChunkBase::setShaderOperation(const GLenum &value)
{
    editSField(ShaderOperationFieldMask);

    _sfShaderOperation.setValue(value);
}
//! Get the value of the TextureChunk::_sfShaderInput field.

inline
GLenum &TextureChunkBase::editShaderInput(void)
{
    editSField(ShaderInputFieldMask);

    return _sfShaderInput.getValue();
}

//! Get the value of the TextureChunk::_sfShaderInput field.
inline
const GLenum &TextureChunkBase::getShaderInput(void) const
{
    return _sfShaderInput.getValue();
}

//! Set the value of the TextureChunk::_sfShaderInput field.
inline
void TextureChunkBase::setShaderInput(const GLenum &value)
{
    editSField(ShaderInputFieldMask);

    _sfShaderInput.setValue(value);
}
//! Get the value of the TextureChunk::_sfShaderOffsetScale field.

inline
Real32 &TextureChunkBase::editShaderOffsetScale(void)
{
    editSField(ShaderOffsetScaleFieldMask);

    return _sfShaderOffsetScale.getValue();
}

//! Get the value of the TextureChunk::_sfShaderOffsetScale field.
inline
      Real32  TextureChunkBase::getShaderOffsetScale(void) const
{
    return _sfShaderOffsetScale.getValue();
}

//! Set the value of the TextureChunk::_sfShaderOffsetScale field.
inline
void TextureChunkBase::setShaderOffsetScale(const Real32 value)
{
    editSField(ShaderOffsetScaleFieldMask);

    _sfShaderOffsetScale.setValue(value);
}
//! Get the value of the TextureChunk::_sfShaderOffsetBias field.

inline
Real32 &TextureChunkBase::editShaderOffsetBias(void)
{
    editSField(ShaderOffsetBiasFieldMask);

    return _sfShaderOffsetBias.getValue();
}

//! Get the value of the TextureChunk::_sfShaderOffsetBias field.
inline
      Real32  TextureChunkBase::getShaderOffsetBias(void) const
{
    return _sfShaderOffsetBias.getValue();
}

//! Set the value of the TextureChunk::_sfShaderOffsetBias field.
inline
void TextureChunkBase::setShaderOffsetBias(const Real32 value)
{
    editSField(ShaderOffsetBiasFieldMask);

    _sfShaderOffsetBias.setValue(value);
}
//! Get the value of the TextureChunk::_sfShaderRGBADotProduct field.

inline
GLenum &TextureChunkBase::editShaderRGBADotProduct(void)
{
    editSField(ShaderRGBADotProductFieldMask);

    return _sfShaderRGBADotProduct.getValue();
}

//! Get the value of the TextureChunk::_sfShaderRGBADotProduct field.
inline
const GLenum &TextureChunkBase::getShaderRGBADotProduct(void) const
{
    return _sfShaderRGBADotProduct.getValue();
}

//! Set the value of the TextureChunk::_sfShaderRGBADotProduct field.
inline
void TextureChunkBase::setShaderRGBADotProduct(const GLenum &value)
{
    editSField(ShaderRGBADotProductFieldMask);

    _sfShaderRGBADotProduct.setValue(value);
}
//! Get the value of the TextureChunk::_sfShaderCullModes field.

inline
UInt8 &TextureChunkBase::editShaderCullModes(void)
{
    editSField(ShaderCullModesFieldMask);

    return _sfShaderCullModes.getValue();
}

//! Get the value of the TextureChunk::_sfShaderCullModes field.
inline
      UInt8  TextureChunkBase::getShaderCullModes(void) const
{
    return _sfShaderCullModes.getValue();
}

//! Set the value of the TextureChunk::_sfShaderCullModes field.
inline
void TextureChunkBase::setShaderCullModes(const UInt8 value)
{
    editSField(ShaderCullModesFieldMask);

    _sfShaderCullModes.setValue(value);
}
//! Get the value of the TextureChunk::_sfShaderConstEye field.

inline
Vec3f &TextureChunkBase::editShaderConstEye(void)
{
    editSField(ShaderConstEyeFieldMask);

    return _sfShaderConstEye.getValue();
}

//! Get the value of the TextureChunk::_sfShaderConstEye field.
inline
const Vec3f &TextureChunkBase::getShaderConstEye(void) const
{
    return _sfShaderConstEye.getValue();
}

//! Set the value of the TextureChunk::_sfShaderConstEye field.
inline
void TextureChunkBase::setShaderConstEye(const Vec3f &value)
{
    editSField(ShaderConstEyeFieldMask);

    _sfShaderConstEye.setValue(value);
}
//! Get the value of the TextureChunk::_sfLodBias field.

inline
Real32 &TextureChunkBase::editLodBias(void)
{
    editSField(LodBiasFieldMask);

    return _sfLodBias.getValue();
}

//! Get the value of the TextureChunk::_sfLodBias field.
inline
      Real32  TextureChunkBase::getLodBias(void) const
{
    return _sfLodBias.getValue();
}

//! Set the value of the TextureChunk::_sfLodBias field.
inline
void TextureChunkBase::setLodBias(const Real32 value)
{
    editSField(LodBiasFieldMask);

    _sfLodBias.setValue(value);
}
//! Get the value of the TextureChunk::_sfNPOTMatrixScale field.

inline
UInt32 &TextureChunkBase::editNPOTMatrixScale(void)
{
    editSField(NPOTMatrixScaleFieldMask);

    return _sfNPOTMatrixScale.getValue();
}

//! Get the value of the TextureChunk::_sfNPOTMatrixScale field.
inline
      UInt32  TextureChunkBase::getNPOTMatrixScale(void) const
{
    return _sfNPOTMatrixScale.getValue();
}

//! Set the value of the TextureChunk::_sfNPOTMatrixScale field.
inline
void TextureChunkBase::setNPOTMatrixScale(const UInt32 value)
{
    editSField(NPOTMatrixScaleFieldMask);

    _sfNPOTMatrixScale.setValue(value);
}

//! Get the value of the \a index element the TextureChunk::_mfShaderOffsetMatrix field.
inline
      Real32  TextureChunkBase::getShaderOffsetMatrix(const UInt32 index) const
{
    return _mfShaderOffsetMatrix[index];
}

inline
Real32 &TextureChunkBase::editShaderOffsetMatrix(const UInt32 index)
{
    editMField(ShaderOffsetMatrixFieldMask, _mfShaderOffsetMatrix);

    return _mfShaderOffsetMatrix[index];
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void TextureChunkBase::execSync (      TextureChunkBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (EnvModeFieldMask & whichField))
        _sfEnvMode.syncWith(pFrom->_sfEnvMode);

    if(FieldBits::NoField != (EnvColorFieldMask & whichField))
        _sfEnvColor.syncWith(pFrom->_sfEnvColor);

    if(FieldBits::NoField != (EnvCombineRGBFieldMask & whichField))
        _sfEnvCombineRGB.syncWith(pFrom->_sfEnvCombineRGB);

    if(FieldBits::NoField != (EnvCombineAlphaFieldMask & whichField))
        _sfEnvCombineAlpha.syncWith(pFrom->_sfEnvCombineAlpha);

    if(FieldBits::NoField != (EnvScaleRGBFieldMask & whichField))
        _sfEnvScaleRGB.syncWith(pFrom->_sfEnvScaleRGB);

    if(FieldBits::NoField != (EnvScaleAlphaFieldMask & whichField))
        _sfEnvScaleAlpha.syncWith(pFrom->_sfEnvScaleAlpha);

    if(FieldBits::NoField != (EnvSource0RGBFieldMask & whichField))
        _sfEnvSource0RGB.syncWith(pFrom->_sfEnvSource0RGB);

    if(FieldBits::NoField != (EnvSource1RGBFieldMask & whichField))
        _sfEnvSource1RGB.syncWith(pFrom->_sfEnvSource1RGB);

    if(FieldBits::NoField != (EnvSource2RGBFieldMask & whichField))
        _sfEnvSource2RGB.syncWith(pFrom->_sfEnvSource2RGB);

    if(FieldBits::NoField != (EnvSource0AlphaFieldMask & whichField))
        _sfEnvSource0Alpha.syncWith(pFrom->_sfEnvSource0Alpha);

    if(FieldBits::NoField != (EnvSource1AlphaFieldMask & whichField))
        _sfEnvSource1Alpha.syncWith(pFrom->_sfEnvSource1Alpha);

    if(FieldBits::NoField != (EnvSource2AlphaFieldMask & whichField))
        _sfEnvSource2Alpha.syncWith(pFrom->_sfEnvSource2Alpha);

    if(FieldBits::NoField != (EnvOperand0RGBFieldMask & whichField))
        _sfEnvOperand0RGB.syncWith(pFrom->_sfEnvOperand0RGB);

    if(FieldBits::NoField != (EnvOperand1RGBFieldMask & whichField))
        _sfEnvOperand1RGB.syncWith(pFrom->_sfEnvOperand1RGB);

    if(FieldBits::NoField != (EnvOperand2RGBFieldMask & whichField))
        _sfEnvOperand2RGB.syncWith(pFrom->_sfEnvOperand2RGB);

    if(FieldBits::NoField != (EnvOperand0AlphaFieldMask & whichField))
        _sfEnvOperand0Alpha.syncWith(pFrom->_sfEnvOperand0Alpha);

    if(FieldBits::NoField != (EnvOperand1AlphaFieldMask & whichField))
        _sfEnvOperand1Alpha.syncWith(pFrom->_sfEnvOperand1Alpha);

    if(FieldBits::NoField != (EnvOperand2AlphaFieldMask & whichField))
        _sfEnvOperand2Alpha.syncWith(pFrom->_sfEnvOperand2Alpha);

    if(FieldBits::NoField != (PointSpriteFieldMask & whichField))
        _sfPointSprite.syncWith(pFrom->_sfPointSprite);

    if(FieldBits::NoField != (ShaderOperationFieldMask & whichField))
        _sfShaderOperation.syncWith(pFrom->_sfShaderOperation);

    if(FieldBits::NoField != (ShaderInputFieldMask & whichField))
        _sfShaderInput.syncWith(pFrom->_sfShaderInput);

    if(FieldBits::NoField != (ShaderOffsetMatrixFieldMask & whichField))
        _mfShaderOffsetMatrix.syncWith(pFrom->_mfShaderOffsetMatrix,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (ShaderOffsetScaleFieldMask & whichField))
        _sfShaderOffsetScale.syncWith(pFrom->_sfShaderOffsetScale);

    if(FieldBits::NoField != (ShaderOffsetBiasFieldMask & whichField))
        _sfShaderOffsetBias.syncWith(pFrom->_sfShaderOffsetBias);

    if(FieldBits::NoField != (ShaderRGBADotProductFieldMask & whichField))
        _sfShaderRGBADotProduct.syncWith(pFrom->_sfShaderRGBADotProduct);

    if(FieldBits::NoField != (ShaderCullModesFieldMask & whichField))
        _sfShaderCullModes.syncWith(pFrom->_sfShaderCullModes);

    if(FieldBits::NoField != (ShaderConstEyeFieldMask & whichField))
        _sfShaderConstEye.syncWith(pFrom->_sfShaderConstEye);

    if(FieldBits::NoField != (LodBiasFieldMask & whichField))
        _sfLodBias.syncWith(pFrom->_sfLodBias);

    if(FieldBits::NoField != (NPOTMatrixScaleFieldMask & whichField))
        _sfNPOTMatrixScale.syncWith(pFrom->_sfNPOTMatrixScale);
}
#endif


inline
const Char8 *TextureChunkBase::getClassname(void)
{
    return "TextureChunk";
}
OSG_GEN_CONTAINERPTR(TextureChunk);

OSG_END_NAMESPACE

