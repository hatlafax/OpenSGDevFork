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
 **     class SSAOStage!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &SSAOStageBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 SSAOStageBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 SSAOStageBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the SSAOStage::_sfActivate field.

inline
bool &SSAOStageBase::editActivate(void)
{
    editSField(ActivateFieldMask);

    return _sfActivate.getValue();
}

//! Get the value of the SSAOStage::_sfActivate field.
inline
      bool  SSAOStageBase::getActivate(void) const
{
    return _sfActivate.getValue();
}

//! Set the value of the SSAOStage::_sfActivate field.
inline
void SSAOStageBase::setActivate(const bool value)
{
    editSField(ActivateFieldMask);

    _sfActivate.setValue(value);
}
//! Get the value of the SSAOStage::_sfCalcPosFromDepth field.

inline
bool &SSAOStageBase::editCalcPosFromDepth(void)
{
    editSField(CalcPosFromDepthFieldMask);

    return _sfCalcPosFromDepth.getValue();
}

//! Get the value of the SSAOStage::_sfCalcPosFromDepth field.
inline
      bool  SSAOStageBase::getCalcPosFromDepth(void) const
{
    return _sfCalcPosFromDepth.getValue();
}

//! Set the value of the SSAOStage::_sfCalcPosFromDepth field.
inline
void SSAOStageBase::setCalcPosFromDepth(const bool value)
{
    editSField(CalcPosFromDepthFieldMask);

    _sfCalcPosFromDepth.setValue(value);
}
//! Get the value of the SSAOStage::_sfOffsetKernelSize field.

inline
Int32 &SSAOStageBase::editOffsetKernelSize(void)
{
    editSField(OffsetKernelSizeFieldMask);

    return _sfOffsetKernelSize.getValue();
}

//! Get the value of the SSAOStage::_sfOffsetKernelSize field.
inline
      Int32  SSAOStageBase::getOffsetKernelSize(void) const
{
    return _sfOffsetKernelSize.getValue();
}

//! Set the value of the SSAOStage::_sfOffsetKernelSize field.
inline
void SSAOStageBase::setOffsetKernelSize(const Int32 value)
{
    editSField(OffsetKernelSizeFieldMask);

    _sfOffsetKernelSize.setValue(value);
}
//! Get the value of the SSAOStage::_sfRotateKernelSize field.

inline
Int32 &SSAOStageBase::editRotateKernelSize(void)
{
    editSField(RotateKernelSizeFieldMask);

    return _sfRotateKernelSize.getValue();
}

//! Get the value of the SSAOStage::_sfRotateKernelSize field.
inline
      Int32  SSAOStageBase::getRotateKernelSize(void) const
{
    return _sfRotateKernelSize.getValue();
}

//! Set the value of the SSAOStage::_sfRotateKernelSize field.
inline
void SSAOStageBase::setRotateKernelSize(const Int32 value)
{
    editSField(RotateKernelSizeFieldMask);

    _sfRotateKernelSize.setValue(value);
}
//! Get the value of the SSAOStage::_sfRadius field.

inline
Real32 &SSAOStageBase::editRadius(void)
{
    editSField(RadiusFieldMask);

    return _sfRadius.getValue();
}

//! Get the value of the SSAOStage::_sfRadius field.
inline
      Real32  SSAOStageBase::getRadius(void) const
{
    return _sfRadius.getValue();
}

//! Set the value of the SSAOStage::_sfRadius field.
inline
void SSAOStageBase::setRadius(const Real32 value)
{
    editSField(RadiusFieldMask);

    _sfRadius.setValue(value);
}
//! Get the value of the SSAOStage::_sfBias field.

inline
Real32 &SSAOStageBase::editBias(void)
{
    editSField(BiasFieldMask);

    return _sfBias.getValue();
}

//! Get the value of the SSAOStage::_sfBias field.
inline
      Real32  SSAOStageBase::getBias(void) const
{
    return _sfBias.getValue();
}

//! Set the value of the SSAOStage::_sfBias field.
inline
void SSAOStageBase::setBias(const Real32 value)
{
    editSField(BiasFieldMask);

    _sfBias.setValue(value);
}
//! Get the value of the SSAOStage::_sfBlurKernelSize field.

inline
Int32 &SSAOStageBase::editBlurKernelSize(void)
{
    editSField(BlurKernelSizeFieldMask);

    return _sfBlurKernelSize.getValue();
}

//! Get the value of the SSAOStage::_sfBlurKernelSize field.
inline
      Int32  SSAOStageBase::getBlurKernelSize(void) const
{
    return _sfBlurKernelSize.getValue();
}

//! Set the value of the SSAOStage::_sfBlurKernelSize field.
inline
void SSAOStageBase::setBlurKernelSize(const Int32 value)
{
    editSField(BlurKernelSizeFieldMask);

    _sfBlurKernelSize.setValue(value);
}
//! Get the value of the SSAOStage::_sfAmbientOcclusionTexUnit field.

inline
Int32 &SSAOStageBase::editAmbientOcclusionTexUnit(void)
{
    editSField(AmbientOcclusionTexUnitFieldMask);

    return _sfAmbientOcclusionTexUnit.getValue();
}

//! Get the value of the SSAOStage::_sfAmbientOcclusionTexUnit field.
inline
      Int32  SSAOStageBase::getAmbientOcclusionTexUnit(void) const
{
    return _sfAmbientOcclusionTexUnit.getValue();
}

//! Set the value of the SSAOStage::_sfAmbientOcclusionTexUnit field.
inline
void SSAOStageBase::setAmbientOcclusionTexUnit(const Int32 value)
{
    editSField(AmbientOcclusionTexUnitFieldMask);

    _sfAmbientOcclusionTexUnit.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void SSAOStageBase::execSync (      SSAOStageBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ActivateFieldMask & whichField))
        _sfActivate.syncWith(pFrom->_sfActivate);

    if(FieldBits::NoField != (CalcPosFromDepthFieldMask & whichField))
        _sfCalcPosFromDepth.syncWith(pFrom->_sfCalcPosFromDepth);

    if(FieldBits::NoField != (OffsetKernelSizeFieldMask & whichField))
        _sfOffsetKernelSize.syncWith(pFrom->_sfOffsetKernelSize);

    if(FieldBits::NoField != (RotateKernelSizeFieldMask & whichField))
        _sfRotateKernelSize.syncWith(pFrom->_sfRotateKernelSize);

    if(FieldBits::NoField != (RadiusFieldMask & whichField))
        _sfRadius.syncWith(pFrom->_sfRadius);

    if(FieldBits::NoField != (BiasFieldMask & whichField))
        _sfBias.syncWith(pFrom->_sfBias);

    if(FieldBits::NoField != (BlurKernelSizeFieldMask & whichField))
        _sfBlurKernelSize.syncWith(pFrom->_sfBlurKernelSize);

    if(FieldBits::NoField != (AmbientOcclusionTexUnitFieldMask & whichField))
        _sfAmbientOcclusionTexUnit.syncWith(pFrom->_sfAmbientOcclusionTexUnit);

    if(FieldBits::NoField != (OffsetKernelChunkFieldMask & whichField))
        _sfOffsetKernelChunk.syncWith(pFrom->_sfOffsetKernelChunk);

    if(FieldBits::NoField != (RotateKernelChunkFieldMask & whichField))
        _sfRotateKernelChunk.syncWith(pFrom->_sfRotateKernelChunk);
}
#endif


inline
const Char8 *SSAOStageBase::getClassname(void)
{
    return "SSAOStage";
}
OSG_GEN_CONTAINERPTR(SSAOStage);

OSG_END_NAMESPACE

