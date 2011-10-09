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
 **     class BlendChunk!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &BlendChunkBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 BlendChunkBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 BlendChunkBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the BlendChunk::_sfSrcFactor field.

inline
GLenum &BlendChunkBase::editSrcFactor(void)
{
    editSField(SrcFactorFieldMask);

    return _sfSrcFactor.getValue();
}

//! Get the value of the BlendChunk::_sfSrcFactor field.
inline
const GLenum &BlendChunkBase::getSrcFactor(void) const
{
    return _sfSrcFactor.getValue();
}

//! Set the value of the BlendChunk::_sfSrcFactor field.
inline
void BlendChunkBase::setSrcFactor(const GLenum &value)
{
    editSField(SrcFactorFieldMask);

    _sfSrcFactor.setValue(value);
}
//! Get the value of the BlendChunk::_sfDestFactor field.

inline
GLenum &BlendChunkBase::editDestFactor(void)
{
    editSField(DestFactorFieldMask);

    return _sfDestFactor.getValue();
}

//! Get the value of the BlendChunk::_sfDestFactor field.
inline
const GLenum &BlendChunkBase::getDestFactor(void) const
{
    return _sfDestFactor.getValue();
}

//! Set the value of the BlendChunk::_sfDestFactor field.
inline
void BlendChunkBase::setDestFactor(const GLenum &value)
{
    editSField(DestFactorFieldMask);

    _sfDestFactor.setValue(value);
}
//! Get the value of the BlendChunk::_sfEquation field.

inline
GLenum &BlendChunkBase::editEquation(void)
{
    editSField(EquationFieldMask);

    return _sfEquation.getValue();
}

//! Get the value of the BlendChunk::_sfEquation field.
inline
const GLenum &BlendChunkBase::getEquation(void) const
{
    return _sfEquation.getValue();
}

//! Set the value of the BlendChunk::_sfEquation field.
inline
void BlendChunkBase::setEquation(const GLenum &value)
{
    editSField(EquationFieldMask);

    _sfEquation.setValue(value);
}
//! Get the value of the BlendChunk::_sfColor field.

inline
Color4f &BlendChunkBase::editColor(void)
{
    editSField(ColorFieldMask);

    return _sfColor.getValue();
}

//! Get the value of the BlendChunk::_sfColor field.
inline
const Color4f &BlendChunkBase::getColor(void) const
{
    return _sfColor.getValue();
}

//! Set the value of the BlendChunk::_sfColor field.
inline
void BlendChunkBase::setColor(const Color4f &value)
{
    editSField(ColorFieldMask);

    _sfColor.setValue(value);
}
//! Get the value of the BlendChunk::_sfAlphaFunc field.

inline
GLenum &BlendChunkBase::editAlphaFunc(void)
{
    editSField(AlphaFuncFieldMask);

    return _sfAlphaFunc.getValue();
}

//! Get the value of the BlendChunk::_sfAlphaFunc field.
inline
const GLenum &BlendChunkBase::getAlphaFunc(void) const
{
    return _sfAlphaFunc.getValue();
}

//! Set the value of the BlendChunk::_sfAlphaFunc field.
inline
void BlendChunkBase::setAlphaFunc(const GLenum &value)
{
    editSField(AlphaFuncFieldMask);

    _sfAlphaFunc.setValue(value);
}
//! Get the value of the BlendChunk::_sfAlphaValue field.

inline
Real32 &BlendChunkBase::editAlphaValue(void)
{
    editSField(AlphaValueFieldMask);

    return _sfAlphaValue.getValue();
}

//! Get the value of the BlendChunk::_sfAlphaValue field.
inline
      Real32  BlendChunkBase::getAlphaValue(void) const
{
    return _sfAlphaValue.getValue();
}

//! Set the value of the BlendChunk::_sfAlphaValue field.
inline
void BlendChunkBase::setAlphaValue(const Real32 value)
{
    editSField(AlphaValueFieldMask);

    _sfAlphaValue.setValue(value);
}
//! Get the value of the BlendChunk::_sfAlphaSrcFactor field.

inline
GLenum &BlendChunkBase::editAlphaSrcFactor(void)
{
    editSField(AlphaSrcFactorFieldMask);

    return _sfAlphaSrcFactor.getValue();
}

//! Get the value of the BlendChunk::_sfAlphaSrcFactor field.
inline
const GLenum &BlendChunkBase::getAlphaSrcFactor(void) const
{
    return _sfAlphaSrcFactor.getValue();
}

//! Set the value of the BlendChunk::_sfAlphaSrcFactor field.
inline
void BlendChunkBase::setAlphaSrcFactor(const GLenum &value)
{
    editSField(AlphaSrcFactorFieldMask);

    _sfAlphaSrcFactor.setValue(value);
}
//! Get the value of the BlendChunk::_sfAlphaDestFactor field.

inline
GLenum &BlendChunkBase::editAlphaDestFactor(void)
{
    editSField(AlphaDestFactorFieldMask);

    return _sfAlphaDestFactor.getValue();
}

//! Get the value of the BlendChunk::_sfAlphaDestFactor field.
inline
const GLenum &BlendChunkBase::getAlphaDestFactor(void) const
{
    return _sfAlphaDestFactor.getValue();
}

//! Set the value of the BlendChunk::_sfAlphaDestFactor field.
inline
void BlendChunkBase::setAlphaDestFactor(const GLenum &value)
{
    editSField(AlphaDestFactorFieldMask);

    _sfAlphaDestFactor.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void BlendChunkBase::execSync (      BlendChunkBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (SrcFactorFieldMask & whichField))
        _sfSrcFactor.syncWith(pFrom->_sfSrcFactor);

    if(FieldBits::NoField != (DestFactorFieldMask & whichField))
        _sfDestFactor.syncWith(pFrom->_sfDestFactor);

    if(FieldBits::NoField != (EquationFieldMask & whichField))
        _sfEquation.syncWith(pFrom->_sfEquation);

    if(FieldBits::NoField != (ColorFieldMask & whichField))
        _sfColor.syncWith(pFrom->_sfColor);

    if(FieldBits::NoField != (AlphaFuncFieldMask & whichField))
        _sfAlphaFunc.syncWith(pFrom->_sfAlphaFunc);

    if(FieldBits::NoField != (AlphaValueFieldMask & whichField))
        _sfAlphaValue.syncWith(pFrom->_sfAlphaValue);

    if(FieldBits::NoField != (AlphaSrcFactorFieldMask & whichField))
        _sfAlphaSrcFactor.syncWith(pFrom->_sfAlphaSrcFactor);

    if(FieldBits::NoField != (AlphaDestFactorFieldMask & whichField))
        _sfAlphaDestFactor.syncWith(pFrom->_sfAlphaDestFactor);
}
#endif


inline
const Char8 *BlendChunkBase::getClassname(void)
{
    return "BlendChunk";
}
OSG_GEN_CONTAINERPTR(BlendChunk);

OSG_END_NAMESPACE

