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
 **     class MultiLightChunk!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &MultiLightChunkBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 MultiLightChunkBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 MultiLightChunkBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the MultiLightChunk::_sfFeature field.

inline
UInt32 &MultiLightChunkBase::editFeature(void)
{
    editSField(FeatureFieldMask);

    return _sfFeature.getValue();
}

//! Get the value of the MultiLightChunk::_sfFeature field.
inline
      UInt32  MultiLightChunkBase::getFeature(void) const
{
    return _sfFeature.getValue();
}

//! Set the value of the MultiLightChunk::_sfFeature field.
inline
void MultiLightChunkBase::setFeature(const UInt32 value)
{
    editSField(FeatureFieldMask);

    _sfFeature.setValue(value);
}
//! Get the value of the MultiLightChunk::_sfCodeFeature field.

inline
UInt32 &MultiLightChunkBase::editCodeFeature(void)
{
    editSField(CodeFeatureFieldMask);

    return _sfCodeFeature.getValue();
}

//! Get the value of the MultiLightChunk::_sfCodeFeature field.
inline
      UInt32  MultiLightChunkBase::getCodeFeature(void) const
{
    return _sfCodeFeature.getValue();
}

//! Set the value of the MultiLightChunk::_sfCodeFeature field.
inline
void MultiLightChunkBase::setCodeFeature(const UInt32 value)
{
    editSField(CodeFeatureFieldMask);

    _sfCodeFeature.setValue(value);
}
//! Get the value of the MultiLightChunk::_sfGlobalAmbientIntensity field.

inline
Vec3f &MultiLightChunkBase::editGlobalAmbientIntensity(void)
{
    editSField(GlobalAmbientIntensityFieldMask);

    return _sfGlobalAmbientIntensity.getValue();
}

//! Get the value of the MultiLightChunk::_sfGlobalAmbientIntensity field.
inline
const Vec3f &MultiLightChunkBase::getGlobalAmbientIntensity(void) const
{
    return _sfGlobalAmbientIntensity.getValue();
}

//! Set the value of the MultiLightChunk::_sfGlobalAmbientIntensity field.
inline
void MultiLightChunkBase::setGlobalAmbientIntensity(const Vec3f &value)
{
    editSField(GlobalAmbientIntensityFieldMask);

    _sfGlobalAmbientIntensity.setValue(value);
}
//! Get the value of the MultiLightChunk::_sfNormalizeDirection field.

inline
bool &MultiLightChunkBase::editNormalizeDirection(void)
{
    editSField(NormalizeDirectionFieldMask);

    return _sfNormalizeDirection.getValue();
}

//! Get the value of the MultiLightChunk::_sfNormalizeDirection field.
inline
      bool  MultiLightChunkBase::getNormalizeDirection(void) const
{
    return _sfNormalizeDirection.getValue();
}

//! Set the value of the MultiLightChunk::_sfNormalizeDirection field.
inline
void MultiLightChunkBase::setNormalizeDirection(const bool value)
{
    editSField(NormalizeDirectionFieldMask);

    _sfNormalizeDirection.setValue(value);
}
//! Get the value of the MultiLightChunk::_sfLastCamNear field.

inline
Real32 &MultiLightChunkBase::editLastCamNear(void)
{
    editSField(LastCamNearFieldMask);

    return _sfLastCamNear.getValue();
}

//! Get the value of the MultiLightChunk::_sfLastCamNear field.
inline
      Real32  MultiLightChunkBase::getLastCamNear(void) const
{
    return _sfLastCamNear.getValue();
}

//! Set the value of the MultiLightChunk::_sfLastCamNear field.
inline
void MultiLightChunkBase::setLastCamNear(const Real32 value)
{
    editSField(LastCamNearFieldMask);

    _sfLastCamNear.setValue(value);
}
//! Get the value of the MultiLightChunk::_sfLastCamFar field.

inline
Real32 &MultiLightChunkBase::editLastCamFar(void)
{
    editSField(LastCamFarFieldMask);

    return _sfLastCamFar.getValue();
}

//! Get the value of the MultiLightChunk::_sfLastCamFar field.
inline
      Real32  MultiLightChunkBase::getLastCamFar(void) const
{
    return _sfLastCamFar.getValue();
}

//! Set the value of the MultiLightChunk::_sfLastCamFar field.
inline
void MultiLightChunkBase::setLastCamFar(const Real32 value)
{
    editSField(LastCamFarFieldMask);

    _sfLastCamFar.setValue(value);
}
//! Get the value of the MultiLightChunk::_sfLastCamToWorld field.

inline
Matrix &MultiLightChunkBase::editLastCamToWorld(void)
{
    editSField(LastCamToWorldFieldMask);

    return _sfLastCamToWorld.getValue();
}

//! Get the value of the MultiLightChunk::_sfLastCamToWorld field.
inline
const Matrix &MultiLightChunkBase::getLastCamToWorld(void) const
{
    return _sfLastCamToWorld.getValue();
}

//! Set the value of the MultiLightChunk::_sfLastCamToWorld field.
inline
void MultiLightChunkBase::setLastCamToWorld(const Matrix &value)
{
    editSField(LastCamToWorldFieldMask);

    _sfLastCamToWorld.setValue(value);
}
//! Get the value of the MultiLightChunk::_sfLightBlockName field.

inline
std::string &MultiLightChunkBase::editLightBlockName(void)
{
    editSField(LightBlockNameFieldMask);

    return _sfLightBlockName.getValue();
}

//! Get the value of the MultiLightChunk::_sfLightBlockName field.
inline
const std::string &MultiLightChunkBase::getLightBlockName(void) const
{
    return _sfLightBlockName.getValue();
}

//! Set the value of the MultiLightChunk::_sfLightBlockName field.
inline
void MultiLightChunkBase::setLightBlockName(const std::string &value)
{
    editSField(LightBlockNameFieldMask);

    _sfLightBlockName.setValue(value);
}
//! Get the value of the MultiLightChunk::_sfLightVariableName field.

inline
std::string &MultiLightChunkBase::editLightVariableName(void)
{
    editSField(LightVariableNameFieldMask);

    return _sfLightVariableName.getValue();
}

//! Get the value of the MultiLightChunk::_sfLightVariableName field.
inline
const std::string &MultiLightChunkBase::getLightVariableName(void) const
{
    return _sfLightVariableName.getValue();
}

//! Set the value of the MultiLightChunk::_sfLightVariableName field.
inline
void MultiLightChunkBase::setLightVariableName(const std::string &value)
{
    editSField(LightVariableNameFieldMask);

    _sfLightVariableName.setValue(value);
}

//! Get the value of the \a index element the MultiLightChunk::_mfPosition field.
inline
const Pnt3f &MultiLightChunkBase::getPosition(const UInt32 index) const
{
    return _mfPosition[index];
}

inline
MFPnt3f            ::reference MultiLightChunkBase::editPosition(const UInt32 index)
{
    editMField(PositionFieldMask, _mfPosition);

    return _mfPosition[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfDirection field.
inline
const Vec3f &MultiLightChunkBase::getDirection(const UInt32 index) const
{
    return _mfDirection[index];
}

inline
MFVec3f            ::reference MultiLightChunkBase::editDirection(const UInt32 index)
{
    editMField(DirectionFieldMask, _mfDirection);

    return _mfDirection[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfIntensity field.
inline
const Vec3f &MultiLightChunkBase::getIntensity(const UInt32 index) const
{
    return _mfIntensity[index];
}

inline
MFVec3f            ::reference MultiLightChunkBase::editIntensity(const UInt32 index)
{
    editMField(IntensityFieldMask, _mfIntensity);

    return _mfIntensity[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfAmbientIntensity field.
inline
const Vec3f &MultiLightChunkBase::getAmbientIntensity(const UInt32 index) const
{
    return _mfAmbientIntensity[index];
}

inline
MFVec3f            ::reference MultiLightChunkBase::editAmbientIntensity(const UInt32 index)
{
    editMField(AmbientIntensityFieldMask, _mfAmbientIntensity);

    return _mfAmbientIntensity[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfDiffuseIntensity field.
inline
const Vec3f &MultiLightChunkBase::getDiffuseIntensity(const UInt32 index) const
{
    return _mfDiffuseIntensity[index];
}

inline
MFVec3f            ::reference MultiLightChunkBase::editDiffuseIntensity(const UInt32 index)
{
    editMField(DiffuseIntensityFieldMask, _mfDiffuseIntensity);

    return _mfDiffuseIntensity[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfSpecularIntensity field.
inline
const Vec3f &MultiLightChunkBase::getSpecularIntensity(const UInt32 index) const
{
    return _mfSpecularIntensity[index];
}

inline
MFVec3f            ::reference MultiLightChunkBase::editSpecularIntensity(const UInt32 index)
{
    editMField(SpecularIntensityFieldMask, _mfSpecularIntensity);

    return _mfSpecularIntensity[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfAttenuation field.
inline
const Vec3f &MultiLightChunkBase::getAttenuation(const UInt32 index) const
{
    return _mfAttenuation[index];
}

inline
MFVec3f            ::reference MultiLightChunkBase::editAttenuation(const UInt32 index)
{
    editMField(AttenuationFieldMask, _mfAttenuation);

    return _mfAttenuation[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfDecayAttenuation field.
inline
      Real32  MultiLightChunkBase::getDecayAttenuation(const UInt32 index) const
{
    return _mfDecayAttenuation[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editDecayAttenuation(const UInt32 index)
{
    editMField(DecayAttenuationFieldMask, _mfDecayAttenuation);

    return _mfDecayAttenuation[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfLengthFactor field.
inline
      Real32  MultiLightChunkBase::getLengthFactor(const UInt32 index) const
{
    return _mfLengthFactor[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editLengthFactor(const UInt32 index)
{
    editMField(LengthFactorFieldMask, _mfLengthFactor);

    return _mfLengthFactor[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfSpotlightAngle field.
inline
      Real32  MultiLightChunkBase::getSpotlightAngle(const UInt32 index) const
{
    return _mfSpotlightAngle[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editSpotlightAngle(const UInt32 index)
{
    editMField(SpotlightAngleFieldMask, _mfSpotlightAngle);

    return _mfSpotlightAngle[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfSpotExponent field.
inline
      Real32  MultiLightChunkBase::getSpotExponent(const UInt32 index) const
{
    return _mfSpotExponent[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editSpotExponent(const UInt32 index)
{
    editMField(SpotExponentFieldMask, _mfSpotExponent);

    return _mfSpotExponent[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfInnerSuperEllipsesWidth field.
inline
      Real32  MultiLightChunkBase::getInnerSuperEllipsesWidth(const UInt32 index) const
{
    return _mfInnerSuperEllipsesWidth[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editInnerSuperEllipsesWidth(const UInt32 index)
{
    editMField(InnerSuperEllipsesWidthFieldMask, _mfInnerSuperEllipsesWidth);

    return _mfInnerSuperEllipsesWidth[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfInnerSuperEllipsesHeight field.
inline
      Real32  MultiLightChunkBase::getInnerSuperEllipsesHeight(const UInt32 index) const
{
    return _mfInnerSuperEllipsesHeight[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editInnerSuperEllipsesHeight(const UInt32 index)
{
    editMField(InnerSuperEllipsesHeightFieldMask, _mfInnerSuperEllipsesHeight);

    return _mfInnerSuperEllipsesHeight[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfOuterSuperEllipsesWidth field.
inline
      Real32  MultiLightChunkBase::getOuterSuperEllipsesWidth(const UInt32 index) const
{
    return _mfOuterSuperEllipsesWidth[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editOuterSuperEllipsesWidth(const UInt32 index)
{
    editMField(OuterSuperEllipsesWidthFieldMask, _mfOuterSuperEllipsesWidth);

    return _mfOuterSuperEllipsesWidth[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfOuterSuperEllipsesHeight field.
inline
      Real32  MultiLightChunkBase::getOuterSuperEllipsesHeight(const UInt32 index) const
{
    return _mfOuterSuperEllipsesHeight[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editOuterSuperEllipsesHeight(const UInt32 index)
{
    editMField(OuterSuperEllipsesHeightFieldMask, _mfOuterSuperEllipsesHeight);

    return _mfOuterSuperEllipsesHeight[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfSuperEllipsesRoundness field.
inline
      Real32  MultiLightChunkBase::getSuperEllipsesRoundness(const UInt32 index) const
{
    return _mfSuperEllipsesRoundness[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editSuperEllipsesRoundness(const UInt32 index)
{
    editMField(SuperEllipsesRoundnessFieldMask, _mfSuperEllipsesRoundness);

    return _mfSuperEllipsesRoundness[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfSuperEllipsesTwist field.
inline
      Real32  MultiLightChunkBase::getSuperEllipsesTwist(const UInt32 index) const
{
    return _mfSuperEllipsesTwist[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editSuperEllipsesTwist(const UInt32 index)
{
    editMField(SuperEllipsesTwistFieldMask, _mfSuperEllipsesTwist);

    return _mfSuperEllipsesTwist[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfRangeCutOn field.
inline
      Real32  MultiLightChunkBase::getRangeCutOn(const UInt32 index) const
{
    return _mfRangeCutOn[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editRangeCutOn(const UInt32 index)
{
    editMField(RangeCutOnFieldMask, _mfRangeCutOn);

    return _mfRangeCutOn[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfRangeCutOff field.
inline
      Real32  MultiLightChunkBase::getRangeCutOff(const UInt32 index) const
{
    return _mfRangeCutOff[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editRangeCutOff(const UInt32 index)
{
    editMField(RangeCutOffFieldMask, _mfRangeCutOff);

    return _mfRangeCutOff[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfRangeNearZone field.
inline
      Real32  MultiLightChunkBase::getRangeNearZone(const UInt32 index) const
{
    return _mfRangeNearZone[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editRangeNearZone(const UInt32 index)
{
    editMField(RangeNearZoneFieldMask, _mfRangeNearZone);

    return _mfRangeNearZone[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfRangeFarZone field.
inline
      Real32  MultiLightChunkBase::getRangeFarZone(const UInt32 index) const
{
    return _mfRangeFarZone[index];
}

inline
MFReal32           ::reference MultiLightChunkBase::editRangeFarZone(const UInt32 index)
{
    editMField(RangeFarZoneFieldMask, _mfRangeFarZone);

    return _mfRangeFarZone[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfProjectionMatrix field.
inline
const Matrix &MultiLightChunkBase::getProjectionMatrix(const UInt32 index) const
{
    return _mfProjectionMatrix[index];
}

inline
MFMatrix           ::reference MultiLightChunkBase::editProjectionMatrix(const UInt32 index)
{
    editMField(ProjectionMatrixFieldMask, _mfProjectionMatrix);

    return _mfProjectionMatrix[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfTypeOfLight field.
inline
      UInt8  MultiLightChunkBase::getTypeOfLight(const UInt32 index) const
{
    return _mfTypeOfLight[index];
}

inline
MFUInt8            ::reference MultiLightChunkBase::editTypeOfLight(const UInt32 index)
{
    editMField(TypeOfLightFieldMask, _mfTypeOfLight);

    return _mfTypeOfLight[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfEnabled field.
inline
      bool  MultiLightChunkBase::getEnabled(const UInt32 index) const
{
    return _mfEnabled[index];
}

inline
MFBool             ::reference MultiLightChunkBase::editEnabled(const UInt32 index)
{
    editMField(EnabledFieldMask, _mfEnabled);

    return _mfEnabled[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfShadow field.
inline
      bool  MultiLightChunkBase::getShadow(const UInt32 index) const
{
    return _mfShadow[index];
}

inline
MFBool             ::reference MultiLightChunkBase::editShadow(const UInt32 index)
{
    editMField(ShadowFieldMask, _mfShadow);

    return _mfShadow[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfShadowDataIndex field.
inline
      Int32  MultiLightChunkBase::getShadowDataIndex(const UInt32 index) const
{
    return _mfShadowDataIndex[index];
}

inline
MFInt32            ::reference MultiLightChunkBase::editShadowDataIndex(const UInt32 index)
{
    editMField(ShadowDataIndexFieldMask, _mfShadowDataIndex);

    return _mfShadowDataIndex[index];
}

//! Get the value of the \a index element the MultiLightChunk::_mfShadowParameterIndex field.
inline
      Int32  MultiLightChunkBase::getShadowParameterIndex(const UInt32 index) const
{
    return _mfShadowParameterIndex[index];
}

inline
MFInt32            ::reference MultiLightChunkBase::editShadowParameterIndex(const UInt32 index)
{
    editMField(ShadowParameterIndexFieldMask, _mfShadowParameterIndex);

    return _mfShadowParameterIndex[index];
}


//! Get the value of the \a index element the MultiLightChunk::_mfBeaconMatrix field.
inline
const Matrix &MultiLightChunkBase::getBeaconMatrix(const UInt32 index) const
{
    return _mfBeaconMatrix[index];
}

inline
MFMatrix           ::reference MultiLightChunkBase::editBeaconMatrix(const UInt32 index)
{
    editMField(BeaconMatrixFieldMask, _mfBeaconMatrix);

    return _mfBeaconMatrix[index];
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void MultiLightChunkBase::execSync (      MultiLightChunkBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (FeatureFieldMask & whichField))
        _sfFeature.syncWith(pFrom->_sfFeature);

    if(FieldBits::NoField != (CodeFeatureFieldMask & whichField))
        _sfCodeFeature.syncWith(pFrom->_sfCodeFeature);

    if(FieldBits::NoField != (GlobalAmbientIntensityFieldMask & whichField))
        _sfGlobalAmbientIntensity.syncWith(pFrom->_sfGlobalAmbientIntensity);

    if(FieldBits::NoField != (PositionFieldMask & whichField))
        _mfPosition.syncWith(pFrom->_mfPosition,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (DirectionFieldMask & whichField))
        _mfDirection.syncWith(pFrom->_mfDirection,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (IntensityFieldMask & whichField))
        _mfIntensity.syncWith(pFrom->_mfIntensity,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (AmbientIntensityFieldMask & whichField))
        _mfAmbientIntensity.syncWith(pFrom->_mfAmbientIntensity,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (DiffuseIntensityFieldMask & whichField))
        _mfDiffuseIntensity.syncWith(pFrom->_mfDiffuseIntensity,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (SpecularIntensityFieldMask & whichField))
        _mfSpecularIntensity.syncWith(pFrom->_mfSpecularIntensity,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (AttenuationFieldMask & whichField))
        _mfAttenuation.syncWith(pFrom->_mfAttenuation,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (DecayAttenuationFieldMask & whichField))
        _mfDecayAttenuation.syncWith(pFrom->_mfDecayAttenuation,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (LengthFactorFieldMask & whichField))
        _mfLengthFactor.syncWith(pFrom->_mfLengthFactor,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (SpotlightAngleFieldMask & whichField))
        _mfSpotlightAngle.syncWith(pFrom->_mfSpotlightAngle,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (SpotExponentFieldMask & whichField))
        _mfSpotExponent.syncWith(pFrom->_mfSpotExponent,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (InnerSuperEllipsesWidthFieldMask & whichField))
        _mfInnerSuperEllipsesWidth.syncWith(pFrom->_mfInnerSuperEllipsesWidth,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (InnerSuperEllipsesHeightFieldMask & whichField))
        _mfInnerSuperEllipsesHeight.syncWith(pFrom->_mfInnerSuperEllipsesHeight,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (OuterSuperEllipsesWidthFieldMask & whichField))
        _mfOuterSuperEllipsesWidth.syncWith(pFrom->_mfOuterSuperEllipsesWidth,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (OuterSuperEllipsesHeightFieldMask & whichField))
        _mfOuterSuperEllipsesHeight.syncWith(pFrom->_mfOuterSuperEllipsesHeight,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (SuperEllipsesRoundnessFieldMask & whichField))
        _mfSuperEllipsesRoundness.syncWith(pFrom->_mfSuperEllipsesRoundness,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (SuperEllipsesTwistFieldMask & whichField))
        _mfSuperEllipsesTwist.syncWith(pFrom->_mfSuperEllipsesTwist,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (RangeCutOnFieldMask & whichField))
        _mfRangeCutOn.syncWith(pFrom->_mfRangeCutOn,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (RangeCutOffFieldMask & whichField))
        _mfRangeCutOff.syncWith(pFrom->_mfRangeCutOff,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (RangeNearZoneFieldMask & whichField))
        _mfRangeNearZone.syncWith(pFrom->_mfRangeNearZone,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (RangeFarZoneFieldMask & whichField))
        _mfRangeFarZone.syncWith(pFrom->_mfRangeFarZone,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (ProjectionMatrixFieldMask & whichField))
        _mfProjectionMatrix.syncWith(pFrom->_mfProjectionMatrix,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (TypeOfLightFieldMask & whichField))
        _mfTypeOfLight.syncWith(pFrom->_mfTypeOfLight,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (EnabledFieldMask & whichField))
        _mfEnabled.syncWith(pFrom->_mfEnabled,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (ShadowFieldMask & whichField))
        _mfShadow.syncWith(pFrom->_mfShadow,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (ShadowDataIndexFieldMask & whichField))
        _mfShadowDataIndex.syncWith(pFrom->_mfShadowDataIndex,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (ShadowParameterIndexFieldMask & whichField))
        _mfShadowParameterIndex.syncWith(pFrom->_mfShadowParameterIndex,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (BeaconFieldMask & whichField))
        _mfBeacon.syncWith(pFrom->_mfBeacon,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (NormalizeDirectionFieldMask & whichField))
        _sfNormalizeDirection.syncWith(pFrom->_sfNormalizeDirection);

    if(FieldBits::NoField != (BeaconMatrixFieldMask & whichField))
        _mfBeaconMatrix.syncWith(pFrom->_mfBeaconMatrix,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (LastCamNearFieldMask & whichField))
        _sfLastCamNear.syncWith(pFrom->_sfLastCamNear);

    if(FieldBits::NoField != (LastCamFarFieldMask & whichField))
        _sfLastCamFar.syncWith(pFrom->_sfLastCamFar);

    if(FieldBits::NoField != (LastCamToWorldFieldMask & whichField))
        _sfLastCamToWorld.syncWith(pFrom->_sfLastCamToWorld);

    if(FieldBits::NoField != (LightBlockNameFieldMask & whichField))
        _sfLightBlockName.syncWith(pFrom->_sfLightBlockName);

    if(FieldBits::NoField != (LightVariableNameFieldMask & whichField))
        _sfLightVariableName.syncWith(pFrom->_sfLightVariableName);
}
#endif


inline
const Char8 *MultiLightChunkBase::getClassname(void)
{
    return "MultiLightChunk";
}
OSG_GEN_CONTAINERPTR(MultiLightChunk);

OSG_END_NAMESPACE

