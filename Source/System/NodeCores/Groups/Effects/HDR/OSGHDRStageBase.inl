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
 **     class HDRStage!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &HDRStageBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 HDRStageBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 HDRStageBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the HDRStage::_sfExposure field.

inline
Real32 &HDRStageBase::editExposure(void)
{
    editSField(ExposureFieldMask);

    return _sfExposure.getValue();
}

//! Get the value of the HDRStage::_sfExposure field.
inline
      Real32  HDRStageBase::getExposure(void) const
{
    return _sfExposure.getValue();
}

//! Set the value of the HDRStage::_sfExposure field.
inline
void HDRStageBase::setExposure(const Real32 value)
{
    editSField(ExposureFieldMask);

    _sfExposure.setValue(value);
}
//! Get the value of the HDRStage::_sfBlurWidth field.

inline
Real32 &HDRStageBase::editBlurWidth(void)
{
    editSField(BlurWidthFieldMask);

    return _sfBlurWidth.getValue();
}

//! Get the value of the HDRStage::_sfBlurWidth field.
inline
      Real32  HDRStageBase::getBlurWidth(void) const
{
    return _sfBlurWidth.getValue();
}

//! Set the value of the HDRStage::_sfBlurWidth field.
inline
void HDRStageBase::setBlurWidth(const Real32 value)
{
    editSField(BlurWidthFieldMask);

    _sfBlurWidth.setValue(value);
}
//! Get the value of the HDRStage::_sfBlurAmount field.

inline
Real32 &HDRStageBase::editBlurAmount(void)
{
    editSField(BlurAmountFieldMask);

    return _sfBlurAmount.getValue();
}

//! Get the value of the HDRStage::_sfBlurAmount field.
inline
      Real32  HDRStageBase::getBlurAmount(void) const
{
    return _sfBlurAmount.getValue();
}

//! Set the value of the HDRStage::_sfBlurAmount field.
inline
void HDRStageBase::setBlurAmount(const Real32 value)
{
    editSField(BlurAmountFieldMask);

    _sfBlurAmount.setValue(value);
}
//! Get the value of the HDRStage::_sfEffectAmount field.

inline
Real32 &HDRStageBase::editEffectAmount(void)
{
    editSField(EffectAmountFieldMask);

    return _sfEffectAmount.getValue();
}

//! Get the value of the HDRStage::_sfEffectAmount field.
inline
      Real32  HDRStageBase::getEffectAmount(void) const
{
    return _sfEffectAmount.getValue();
}

//! Set the value of the HDRStage::_sfEffectAmount field.
inline
void HDRStageBase::setEffectAmount(const Real32 value)
{
    editSField(EffectAmountFieldMask);

    _sfEffectAmount.setValue(value);
}
//! Get the value of the HDRStage::_sfGamma field.

inline
Real32 &HDRStageBase::editGamma(void)
{
    editSField(GammaFieldMask);

    return _sfGamma.getValue();
}

//! Get the value of the HDRStage::_sfGamma field.
inline
      Real32  HDRStageBase::getGamma(void) const
{
    return _sfGamma.getValue();
}

//! Set the value of the HDRStage::_sfGamma field.
inline
void HDRStageBase::setGamma(const Real32 value)
{
    editSField(GammaFieldMask);

    _sfGamma.setValue(value);
}
//! Get the value of the HDRStage::_sfBufferFormat field.

inline
GLenum &HDRStageBase::editBufferFormat(void)
{
    editSField(BufferFormatFieldMask);

    return _sfBufferFormat.getValue();
}

//! Get the value of the HDRStage::_sfBufferFormat field.
inline
const GLenum &HDRStageBase::getBufferFormat(void) const
{
    return _sfBufferFormat.getValue();
}

//! Set the value of the HDRStage::_sfBufferFormat field.
inline
void HDRStageBase::setBufferFormat(const GLenum &value)
{
    editSField(BufferFormatFieldMask);

    _sfBufferFormat.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void HDRStageBase::execSync (      HDRStageBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ExposureFieldMask & whichField))
        _sfExposure.syncWith(pFrom->_sfExposure);

    if(FieldBits::NoField != (BlurWidthFieldMask & whichField))
        _sfBlurWidth.syncWith(pFrom->_sfBlurWidth);

    if(FieldBits::NoField != (BlurAmountFieldMask & whichField))
        _sfBlurAmount.syncWith(pFrom->_sfBlurAmount);

    if(FieldBits::NoField != (EffectAmountFieldMask & whichField))
        _sfEffectAmount.syncWith(pFrom->_sfEffectAmount);

    if(FieldBits::NoField != (GammaFieldMask & whichField))
        _sfGamma.syncWith(pFrom->_sfGamma);

    if(FieldBits::NoField != (BufferFormatFieldMask & whichField))
        _sfBufferFormat.syncWith(pFrom->_sfBufferFormat);
}
#endif


inline
const Char8 *HDRStageBase::getClassname(void)
{
    return "HDRStage";
}
OSG_GEN_CONTAINERPTR(HDRStage);

OSG_END_NAMESPACE

