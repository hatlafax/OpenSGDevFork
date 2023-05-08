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
 **     class MultiLightShadowStage!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &MultiLightShadowStageBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 MultiLightShadowStageBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 MultiLightShadowStageBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the MultiLightShadowStage::_sfShadowMode field.

inline
UInt32 &MultiLightShadowStageBase::editShadowMode(void)
{
    editSField(ShadowModeFieldMask);

    return _sfShadowMode.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfShadowMode field.
inline
      UInt32  MultiLightShadowStageBase::getShadowMode(void) const
{
    return _sfShadowMode.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfShadowMode field.
inline
void MultiLightShadowStageBase::setShadowMode(const UInt32 value)
{
    editSField(ShadowModeFieldMask);

    _sfShadowMode.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfActivate field.

inline
bool &MultiLightShadowStageBase::editActivate(void)
{
    editSField(ActivateFieldMask);

    return _sfActivate.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfActivate field.
inline
      bool  MultiLightShadowStageBase::getActivate(void) const
{
    return _sfActivate.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfActivate field.
inline
void MultiLightShadowStageBase::setActivate(const bool value)
{
    editSField(ActivateFieldMask);

    _sfActivate.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfShadowOn field.

inline
bool &MultiLightShadowStageBase::editShadowOn(void)
{
    editSField(ShadowOnFieldMask);

    return _sfShadowOn.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfShadowOn field.
inline
      bool  MultiLightShadowStageBase::getShadowOn(void) const
{
    return _sfShadowOn.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfShadowOn field.
inline
void MultiLightShadowStageBase::setShadowOn(const bool value)
{
    editSField(ShadowOnFieldMask);

    _sfShadowOn.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfUseHWPCF field.

inline
bool &MultiLightShadowStageBase::editUseHWPCF(void)
{
    editSField(UseHWPCFFieldMask);

    return _sfUseHWPCF.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfUseHWPCF field.
inline
      bool  MultiLightShadowStageBase::getUseHWPCF(void) const
{
    return _sfUseHWPCF.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfUseHWPCF field.
inline
void MultiLightShadowStageBase::setUseHWPCF(const bool value)
{
    editSField(UseHWPCFFieldMask);

    _sfUseHWPCF.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfShadowMapWidth field.

inline
UInt32 &MultiLightShadowStageBase::editShadowMapWidth(void)
{
    editSField(ShadowMapWidthFieldMask);

    return _sfShadowMapWidth.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfShadowMapWidth field.
inline
      UInt32  MultiLightShadowStageBase::getShadowMapWidth(void) const
{
    return _sfShadowMapWidth.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfShadowMapWidth field.
inline
void MultiLightShadowStageBase::setShadowMapWidth(const UInt32 value)
{
    editSField(ShadowMapWidthFieldMask);

    _sfShadowMapWidth.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfShadowMapHeight field.

inline
UInt32 &MultiLightShadowStageBase::editShadowMapHeight(void)
{
    editSField(ShadowMapHeightFieldMask);

    return _sfShadowMapHeight.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfShadowMapHeight field.
inline
      UInt32  MultiLightShadowStageBase::getShadowMapHeight(void) const
{
    return _sfShadowMapHeight.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfShadowMapHeight field.
inline
void MultiLightShadowStageBase::setShadowMapHeight(const UInt32 value)
{
    editSField(ShadowMapHeightFieldMask);

    _sfShadowMapHeight.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfFilterDistributionSize field.

inline
Int32 &MultiLightShadowStageBase::editFilterDistributionSize(void)
{
    editSField(FilterDistributionSizeFieldMask);

    return _sfFilterDistributionSize.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfFilterDistributionSize field.
inline
      Int32  MultiLightShadowStageBase::getFilterDistributionSize(void) const
{
    return _sfFilterDistributionSize.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfFilterDistributionSize field.
inline
void MultiLightShadowStageBase::setFilterDistributionSize(const Int32 value)
{
    editSField(FilterDistributionSizeFieldMask);

    _sfFilterDistributionSize.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfSearchDistributionSize field.

inline
Int32 &MultiLightShadowStageBase::editSearchDistributionSize(void)
{
    editSField(SearchDistributionSizeFieldMask);

    return _sfSearchDistributionSize.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfSearchDistributionSize field.
inline
      Int32  MultiLightShadowStageBase::getSearchDistributionSize(void) const
{
    return _sfSearchDistributionSize.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfSearchDistributionSize field.
inline
void MultiLightShadowStageBase::setSearchDistributionSize(const Int32 value)
{
    editSField(SearchDistributionSizeFieldMask);

    _sfSearchDistributionSize.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfCullFrontFace field.

inline
bool &MultiLightShadowStageBase::editCullFrontFace(void)
{
    editSField(CullFrontFaceFieldMask);

    return _sfCullFrontFace.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfCullFrontFace field.
inline
      bool  MultiLightShadowStageBase::getCullFrontFace(void) const
{
    return _sfCullFrontFace.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfCullFrontFace field.
inline
void MultiLightShadowStageBase::setCullFrontFace(const bool value)
{
    editSField(CullFrontFaceFieldMask);

    _sfCullFrontFace.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfOffsetBias field.

inline
Real32 &MultiLightShadowStageBase::editOffsetBias(void)
{
    editSField(OffsetBiasFieldMask);

    return _sfOffsetBias.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfOffsetBias field.
inline
      Real32  MultiLightShadowStageBase::getOffsetBias(void) const
{
    return _sfOffsetBias.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfOffsetBias field.
inline
void MultiLightShadowStageBase::setOffsetBias(const Real32 value)
{
    editSField(OffsetBiasFieldMask);

    _sfOffsetBias.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfOffsetFactor field.

inline
Real32 &MultiLightShadowStageBase::editOffsetFactor(void)
{
    editSField(OffsetFactorFieldMask);

    return _sfOffsetFactor.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfOffsetFactor field.
inline
      Real32  MultiLightShadowStageBase::getOffsetFactor(void) const
{
    return _sfOffsetFactor.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfOffsetFactor field.
inline
void MultiLightShadowStageBase::setOffsetFactor(const Real32 value)
{
    editSField(OffsetFactorFieldMask);

    _sfOffsetFactor.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfEnlargeShadowVolumeZ field.

inline
Real32 &MultiLightShadowStageBase::editEnlargeShadowVolumeZ(void)
{
    editSField(EnlargeShadowVolumeZFieldMask);

    return _sfEnlargeShadowVolumeZ.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfEnlargeShadowVolumeZ field.
inline
      Real32  MultiLightShadowStageBase::getEnlargeShadowVolumeZ(void) const
{
    return _sfEnlargeShadowVolumeZ.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfEnlargeShadowVolumeZ field.
inline
void MultiLightShadowStageBase::setEnlargeShadowVolumeZ(const Real32 value)
{
    editSField(EnlargeShadowVolumeZFieldMask);

    _sfEnlargeShadowVolumeZ.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfAutoExcludeTransparentNodes field.

inline
bool &MultiLightShadowStageBase::editAutoExcludeTransparentNodes(void)
{
    editSField(AutoExcludeTransparentNodesFieldMask);

    return _sfAutoExcludeTransparentNodes.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfAutoExcludeTransparentNodes field.
inline
      bool  MultiLightShadowStageBase::getAutoExcludeTransparentNodes(void) const
{
    return _sfAutoExcludeTransparentNodes.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfAutoExcludeTransparentNodes field.
inline
void MultiLightShadowStageBase::setAutoExcludeTransparentNodes(const bool value)
{
    editSField(AutoExcludeTransparentNodesFieldMask);

    _sfAutoExcludeTransparentNodes.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfAutoSearchMultiLightChunk field.

inline
bool &MultiLightShadowStageBase::editAutoSearchMultiLightChunk(void)
{
    editSField(AutoSearchMultiLightChunkFieldMask);

    return _sfAutoSearchMultiLightChunk.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfAutoSearchMultiLightChunk field.
inline
      bool  MultiLightShadowStageBase::getAutoSearchMultiLightChunk(void) const
{
    return _sfAutoSearchMultiLightChunk.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfAutoSearchMultiLightChunk field.
inline
void MultiLightShadowStageBase::setAutoSearchMultiLightChunk(const bool value)
{
    editSField(AutoSearchMultiLightChunkFieldMask);

    _sfAutoSearchMultiLightChunk.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfSamplerCubeArrayTextureUnit field.

inline
Int32 &MultiLightShadowStageBase::editSamplerCubeArrayTextureUnit(void)
{
    editSField(SamplerCubeArrayTextureUnitFieldMask);

    return _sfSamplerCubeArrayTextureUnit.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfSamplerCubeArrayTextureUnit field.
inline
      Int32  MultiLightShadowStageBase::getSamplerCubeArrayTextureUnit(void) const
{
    return _sfSamplerCubeArrayTextureUnit.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfSamplerCubeArrayTextureUnit field.
inline
void MultiLightShadowStageBase::setSamplerCubeArrayTextureUnit(const Int32 value)
{
    editSField(SamplerCubeArrayTextureUnitFieldMask);

    _sfSamplerCubeArrayTextureUnit.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfSamplerCubeArrayShadowTextureUnit field.

inline
Int32 &MultiLightShadowStageBase::editSamplerCubeArrayShadowTextureUnit(void)
{
    editSField(SamplerCubeArrayShadowTextureUnitFieldMask);

    return _sfSamplerCubeArrayShadowTextureUnit.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfSamplerCubeArrayShadowTextureUnit field.
inline
      Int32  MultiLightShadowStageBase::getSamplerCubeArrayShadowTextureUnit(void) const
{
    return _sfSamplerCubeArrayShadowTextureUnit.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfSamplerCubeArrayShadowTextureUnit field.
inline
void MultiLightShadowStageBase::setSamplerCubeArrayShadowTextureUnit(const Int32 value)
{
    editSField(SamplerCubeArrayShadowTextureUnitFieldMask);

    _sfSamplerCubeArrayShadowTextureUnit.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfSampler2DArrayTextureUnit field.

inline
Int32 &MultiLightShadowStageBase::editSampler2DArrayTextureUnit(void)
{
    editSField(Sampler2DArrayTextureUnitFieldMask);

    return _sfSampler2DArrayTextureUnit.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfSampler2DArrayTextureUnit field.
inline
      Int32  MultiLightShadowStageBase::getSampler2DArrayTextureUnit(void) const
{
    return _sfSampler2DArrayTextureUnit.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfSampler2DArrayTextureUnit field.
inline
void MultiLightShadowStageBase::setSampler2DArrayTextureUnit(const Int32 value)
{
    editSField(Sampler2DArrayTextureUnitFieldMask);

    _sfSampler2DArrayTextureUnit.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfSampler2DArrayShadowTextureUnit field.

inline
Int32 &MultiLightShadowStageBase::editSampler2DArrayShadowTextureUnit(void)
{
    editSField(Sampler2DArrayShadowTextureUnitFieldMask);

    return _sfSampler2DArrayShadowTextureUnit.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfSampler2DArrayShadowTextureUnit field.
inline
      Int32  MultiLightShadowStageBase::getSampler2DArrayShadowTextureUnit(void) const
{
    return _sfSampler2DArrayShadowTextureUnit.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfSampler2DArrayShadowTextureUnit field.
inline
void MultiLightShadowStageBase::setSampler2DArrayShadowTextureUnit(const Int32 value)
{
    editSField(Sampler2DArrayShadowTextureUnitFieldMask);

    _sfSampler2DArrayShadowTextureUnit.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfShadowDataBindingPnt field.

inline
Int32 &MultiLightShadowStageBase::editShadowDataBindingPnt(void)
{
    editSField(ShadowDataBindingPntFieldMask);

    return _sfShadowDataBindingPnt.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfShadowDataBindingPnt field.
inline
      Int32  MultiLightShadowStageBase::getShadowDataBindingPnt(void) const
{
    return _sfShadowDataBindingPnt.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfShadowDataBindingPnt field.
inline
void MultiLightShadowStageBase::setShadowDataBindingPnt(const Int32 value)
{
    editSField(ShadowDataBindingPntFieldMask);

    _sfShadowDataBindingPnt.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfShadowParameterBindingPnt field.

inline
Int32 &MultiLightShadowStageBase::editShadowParameterBindingPnt(void)
{
    editSField(ShadowParameterBindingPntFieldMask);

    return _sfShadowParameterBindingPnt.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfShadowParameterBindingPnt field.
inline
      Int32  MultiLightShadowStageBase::getShadowParameterBindingPnt(void) const
{
    return _sfShadowParameterBindingPnt.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfShadowParameterBindingPnt field.
inline
void MultiLightShadowStageBase::setShadowParameterBindingPnt(const Int32 value)
{
    editSField(ShadowParameterBindingPntFieldMask);

    _sfShadowParameterBindingPnt.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfDistributionBindingPnt field.

inline
Int32 &MultiLightShadowStageBase::editDistributionBindingPnt(void)
{
    editSField(DistributionBindingPntFieldMask);

    return _sfDistributionBindingPnt.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfDistributionBindingPnt field.
inline
      Int32  MultiLightShadowStageBase::getDistributionBindingPnt(void) const
{
    return _sfDistributionBindingPnt.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfDistributionBindingPnt field.
inline
void MultiLightShadowStageBase::setDistributionBindingPnt(const Int32 value)
{
    editSField(DistributionBindingPntFieldMask);

    _sfDistributionBindingPnt.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfDisableOverride field.

inline
bool &MultiLightShadowStageBase::editDisableOverride(void)
{
    editSField(DisableOverrideFieldMask);

    return _sfDisableOverride.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfDisableOverride field.
inline
      bool  MultiLightShadowStageBase::getDisableOverride(void) const
{
    return _sfDisableOverride.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfDisableOverride field.
inline
void MultiLightShadowStageBase::setDisableOverride(const bool value)
{
    editSField(DisableOverrideFieldMask);

    _sfDisableOverride.setValue(value);
}
//! Get the value of the MultiLightShadowStage::_sfArbTest field.

inline
bool &MultiLightShadowStageBase::editArbTest(void)
{
    editSField(ArbTestFieldMask);

    return _sfArbTest.getValue();
}

//! Get the value of the MultiLightShadowStage::_sfArbTest field.
inline
      bool  MultiLightShadowStageBase::getArbTest(void) const
{
    return _sfArbTest.getValue();
}

//! Set the value of the MultiLightShadowStage::_sfArbTest field.
inline
void MultiLightShadowStageBase::setArbTest(const bool value)
{
    editSField(ArbTestFieldMask);

    _sfArbTest.setValue(value);
}




#ifdef OSG_MT_CPTR_ASPECT
inline
void MultiLightShadowStageBase::execSync (      MultiLightShadowStageBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ShadowModeFieldMask & whichField))
        _sfShadowMode.syncWith(pFrom->_sfShadowMode);

    if(FieldBits::NoField != (ActivateFieldMask & whichField))
        _sfActivate.syncWith(pFrom->_sfActivate);

    if(FieldBits::NoField != (ShadowOnFieldMask & whichField))
        _sfShadowOn.syncWith(pFrom->_sfShadowOn);

    if(FieldBits::NoField != (UseHWPCFFieldMask & whichField))
        _sfUseHWPCF.syncWith(pFrom->_sfUseHWPCF);

    if(FieldBits::NoField != (ShadowParameterFieldMask & whichField))
        _mfShadowParameter.syncWith(pFrom->_mfShadowParameter,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (ShadowMapWidthFieldMask & whichField))
        _sfShadowMapWidth.syncWith(pFrom->_sfShadowMapWidth);

    if(FieldBits::NoField != (ShadowMapHeightFieldMask & whichField))
        _sfShadowMapHeight.syncWith(pFrom->_sfShadowMapHeight);

    if(FieldBits::NoField != (FilterDistributionSizeFieldMask & whichField))
        _sfFilterDistributionSize.syncWith(pFrom->_sfFilterDistributionSize);

    if(FieldBits::NoField != (SearchDistributionSizeFieldMask & whichField))
        _sfSearchDistributionSize.syncWith(pFrom->_sfSearchDistributionSize);

    if(FieldBits::NoField != (CullFrontFaceFieldMask & whichField))
        _sfCullFrontFace.syncWith(pFrom->_sfCullFrontFace);

    if(FieldBits::NoField != (OffsetBiasFieldMask & whichField))
        _sfOffsetBias.syncWith(pFrom->_sfOffsetBias);

    if(FieldBits::NoField != (OffsetFactorFieldMask & whichField))
        _sfOffsetFactor.syncWith(pFrom->_sfOffsetFactor);

    if(FieldBits::NoField != (EnlargeShadowVolumeZFieldMask & whichField))
        _sfEnlargeShadowVolumeZ.syncWith(pFrom->_sfEnlargeShadowVolumeZ);

    if(FieldBits::NoField != (ExcludeNodesFieldMask & whichField))
        _mfExcludeNodes.syncWith(pFrom->_mfExcludeNodes,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (AutoExcludeTransparentNodesFieldMask & whichField))
        _sfAutoExcludeTransparentNodes.syncWith(pFrom->_sfAutoExcludeTransparentNodes);

    if(FieldBits::NoField != (MultiLightChunkFieldMask & whichField))
        _sfMultiLightChunk.syncWith(pFrom->_sfMultiLightChunk);

    if(FieldBits::NoField != (AutoSearchMultiLightChunkFieldMask & whichField))
        _sfAutoSearchMultiLightChunk.syncWith(pFrom->_sfAutoSearchMultiLightChunk);

    if(FieldBits::NoField != (SamplerCubeArrayTextureUnitFieldMask & whichField))
        _sfSamplerCubeArrayTextureUnit.syncWith(pFrom->_sfSamplerCubeArrayTextureUnit);

    if(FieldBits::NoField != (SamplerCubeArrayShadowTextureUnitFieldMask & whichField))
        _sfSamplerCubeArrayShadowTextureUnit.syncWith(pFrom->_sfSamplerCubeArrayShadowTextureUnit);

    if(FieldBits::NoField != (Sampler2DArrayTextureUnitFieldMask & whichField))
        _sfSampler2DArrayTextureUnit.syncWith(pFrom->_sfSampler2DArrayTextureUnit);

    if(FieldBits::NoField != (Sampler2DArrayShadowTextureUnitFieldMask & whichField))
        _sfSampler2DArrayShadowTextureUnit.syncWith(pFrom->_sfSampler2DArrayShadowTextureUnit);

    if(FieldBits::NoField != (ShadowDataBindingPntFieldMask & whichField))
        _sfShadowDataBindingPnt.syncWith(pFrom->_sfShadowDataBindingPnt);

    if(FieldBits::NoField != (ShadowParameterBindingPntFieldMask & whichField))
        _sfShadowParameterBindingPnt.syncWith(pFrom->_sfShadowParameterBindingPnt);

    if(FieldBits::NoField != (DistributionBindingPntFieldMask & whichField))
        _sfDistributionBindingPnt.syncWith(pFrom->_sfDistributionBindingPnt);

    if(FieldBits::NoField != (DisableOverrideFieldMask & whichField))
        _sfDisableOverride.syncWith(pFrom->_sfDisableOverride);

    if(FieldBits::NoField != (ArbTestFieldMask & whichField))
        _sfArbTest.syncWith(pFrom->_sfArbTest);
}
#endif


inline
const Char8 *MultiLightShadowStageBase::getClassname(void)
{
    return "MultiLightShadowStage";
}
OSG_GEN_CONTAINERPTR(MultiLightShadowStage);

OSG_END_NAMESPACE
