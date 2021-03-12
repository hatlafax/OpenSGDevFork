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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

inline 
UInt32 MultiLightChunk::getNumLights() const
{
    return static_cast<UInt32>(_mfPosition.size());
}

inline 
bool MultiLightChunk::empty() const
{
    return (getNumLights() == 0);
}

inline
const Pnt3f& MultiLightChunk::getPosition(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfPosition.size());
    return Inherited::getPosition(idx);
}

inline
const Vec3f& MultiLightChunk::getDirection(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfDirection.size());
    return Inherited::getDirection(idx);
}

inline
const Vec3f& MultiLightChunk::getIntensity(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfIntensity.size());
    return Inherited::getIntensity(idx);
}

inline
const Vec3f& MultiLightChunk::getAmbient(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfAmbientIntensity.size());
    return Inherited::getAmbientIntensity(idx);
}

inline
const Vec3f& MultiLightChunk::getDiffuse(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfDiffuseIntensity.size());
    return Inherited::getDiffuseIntensity(idx);
}

inline
const Vec3f& MultiLightChunk::getSpecular(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfSpecularIntensity.size());
    return Inherited::getSpecularIntensity(idx);
}

inline
const Vec3f& MultiLightChunk::getAttenuation(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfAttenuation.size());
    return Inherited::getAttenuation(idx);
}

inline
Real32 MultiLightChunk::getDecayAttenuation(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfDecayAttenuation.size());
    return Inherited::getDecayAttenuation(idx);
}

inline
Real32 MultiLightChunk::getLengthFactor(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfLengthFactor.size());
    return Inherited::getLengthFactor(idx);
}

inline
Real32 MultiLightChunk::getRange(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfRangeCutOff.size());
    return Inherited::getRangeCutOff(idx);
}

inline
Real32 MultiLightChunk::getSpotlightAngle(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfSpotlightAngle.size());
    return Inherited::getSpotlightAngle(idx);
}

inline
Real32 MultiLightChunk::getSpotlightParameter(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfSpotExponent.size());
    return Inherited::getSpotExponent(idx);
}

inline
Real32 MultiLightChunk::getSpotlightExponent(const UInt32 idx) const
{
    OSG_ASSERT(getHasSpotlightExponent());
    return getSpotlightParameter(idx);
}

inline
Real32 MultiLightChunk::getSpotlightPenumbraAngle(const UInt32 idx) const
{
    OSG_ASSERT(getHasSpotlightPenumbraAngle());
    return getSpotlightParameter(idx);
}

inline
Real32 MultiLightChunk::getSpotlightPenumbraFactor(const UInt32 idx) const
{
    OSG_ASSERT(getHasSpotlightPenumbraFactor());
    return getSpotlightParameter(idx);
}

inline
Real32 MultiLightChunk::getInnerSuperEllipsesWidth(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfInnerSuperEllipsesWidth.size());
    return Inherited::getInnerSuperEllipsesWidth(idx);
}

inline
Real32 MultiLightChunk::getInnerSuperEllipsesHeight(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfInnerSuperEllipsesHeight.size());
    return Inherited::getInnerSuperEllipsesHeight(idx);
}

inline
Real32 MultiLightChunk::getOuterSuperEllipsesWidth(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfOuterSuperEllipsesWidth.size());
    return Inherited::getOuterSuperEllipsesWidth(idx);
}

inline
Real32 MultiLightChunk::getOuterSuperEllipsesHeight(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfOuterSuperEllipsesHeight.size());
    return Inherited::getOuterSuperEllipsesHeight(idx);
}

inline
Real32 MultiLightChunk::getSuperEllipsesRoundness(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfSuperEllipsesRoundness.size());
    return Inherited::getSuperEllipsesRoundness(idx);
}

inline
Real32 MultiLightChunk::getSuperEllipsesTwist(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfSuperEllipsesTwist.size());
    return Inherited::getSuperEllipsesTwist(idx);
}

inline
Real32 MultiLightChunk::getRangeCutOn(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfRangeCutOn.size());
    return Inherited::getRangeCutOn(idx);
}

inline
Real32 MultiLightChunk::getRangeCutOff(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfRangeCutOff.size());
    return Inherited::getRangeCutOff(idx);
}

inline
Real32 MultiLightChunk::getRangeNearZone(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfRangeNearZone.size());
    return Inherited::getRangeNearZone(idx);
}

inline
Real32 MultiLightChunk::getRangeFarZone(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfRangeFarZone.size());
    return Inherited::getRangeFarZone(idx);
}

inline
const Matrix& MultiLightChunk::getProjectionMatrix(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfProjectionMatrix.size());
    return Inherited::getProjectionMatrix(idx);
}

inline
MultiLight::TypeOfLight MultiLightChunk::getTypeOfLight(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfTypeOfLight.size());
    return static_cast<MultiLight::TypeOfLight>(Inherited::getTypeOfLight(idx));
}

inline
bool MultiLightChunk::getEnabled(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfEnabled.size());
    return Inherited::getEnabled(idx);
}

inline
bool MultiLightChunk::getShadow(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfShadow.size());
    return Inherited::getShadow(idx);
}

inline
Int32 MultiLightChunk::getShadowDataIndex(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfShadowDataIndex.size());
    return Inherited::getShadowDataIndex(idx);
}

inline
Int32 MultiLightChunk::getShadowParameterIndex(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfShadowParameterIndex.size());
    return Inherited::getShadowParameterIndex(idx);
}

inline
Node* MultiLightChunk::getBeacon(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfBeacon.size());
    return Inherited::getBeacon(idx);
}

inline
void MultiLightChunk::setPosition(const UInt32 idx, const Pnt3f& position)
{
    OSG_ASSERT(idx < _mfPosition.size());
    if (getPosition(idx) != position)
        editPosition(idx) = position;
}

inline
void MultiLightChunk::setDirection(const UInt32 idx, const Vec3f& direction)
{
    OSG_ASSERT(idx < _mfDirection.size());
    if (getDirection(idx) != direction)
        editDirection(idx) = direction;
}

inline
void MultiLightChunk::setIntensity(const UInt32 idx, const Vec3f& intensity)
{
    OSG_ASSERT(idx < _mfIntensity.size());
    if (!getIntensity(idx).equals(intensity, 0.f))
        editIntensity(idx) = intensity;
}

inline
void MultiLightChunk::setIntensity(const UInt32 idx, const Color3f& color)
{
    OSG_ASSERT(idx < _mfIntensity.size());
    if (!getIntensity(idx).equals(color, 0.f))
        editIntensity(idx) = color;
}

inline
void MultiLightChunk::setIntensity(const UInt32 idx, Real32 red, Real32 green, Real32 blue)
{
    setIntensity(idx, Vec3f(red, green, blue));
}

inline
void MultiLightChunk::setAmbient(const UInt32 idx, const Vec3f& intensity)
{
    OSG_ASSERT(idx < _mfAmbientIntensity.size());
    if (!getAmbient(idx).equals(intensity, 0.f))
        editAmbientIntensity(idx) = intensity;
}

inline
void MultiLightChunk::setAmbient(const UInt32 idx, const Color3f& color)
{
    OSG_ASSERT(idx < _mfAmbientIntensity.size());
    if (!getAmbient(idx).equals(color, 0.f))
        editAmbientIntensity(idx) = color;
}

inline
void MultiLightChunk::setAmbient(const UInt32 idx, Real32 red, Real32 green, Real32 blue)
{
    setAmbient(idx, Vec3f(red, green, blue));
}

inline
void MultiLightChunk::setDiffuse(const UInt32 idx, const Vec3f& intensity)
{
    OSG_ASSERT(idx < _mfDiffuseIntensity.size());
    if (!getDiffuse(idx).equals(intensity, 0.f))
        editDiffuseIntensity(idx) = intensity;
}

inline
void MultiLightChunk::setDiffuse(const UInt32 idx, const Color3f& color)
{
    OSG_ASSERT(idx < _mfDiffuseIntensity.size());
    if (!getDiffuse(idx).equals(color, 0.f))
        editDiffuseIntensity(idx) = color;
}

inline
void MultiLightChunk::setDiffuse(const UInt32 idx, Real32 red, Real32 green, Real32 blue)
{
    setDiffuse(idx, Vec3f(red, green, blue));
}

inline
void MultiLightChunk::setSpecular(const UInt32 idx, const Vec3f& intensity)
{
    OSG_ASSERT(idx < _mfSpecularIntensity.size());
    if (!getSpecular(idx).equals(intensity, 0.f))
        editSpecularIntensity(idx) = intensity;
}

inline
void MultiLightChunk::setSpecular(const UInt32 idx, const Color3f& color)
{
    OSG_ASSERT(idx < _mfSpecularIntensity.size());
    if (!getSpecular(idx).equals(color, 0.f))
        editSpecularIntensity(idx) = color;
}

inline
void MultiLightChunk::setSpecular(const UInt32 idx, Real32 red, Real32 green, Real32 blue)
{
    setSpecular(idx, Vec3f(red, green, blue));
}

inline
void MultiLightChunk::setAttenuation(const UInt32 idx, const Vec3f& attenuation)
{
    OSG_ASSERT(idx < _mfAttenuation.size());
    if (!getAttenuation(idx).equals(attenuation, 0.f))
        editAttenuation(idx) = attenuation;
}

inline
void MultiLightChunk::setDecayAttenuation(const UInt32 idx, Real32 decayAttenuation)
{
    OSG_ASSERT(idx < _mfDecayAttenuation.size());
    if (getDecayAttenuation(idx) != decayAttenuation)
        editDecayAttenuation(idx) = decayAttenuation;
}

inline
void MultiLightChunk::setLengthFactor(const UInt32 idx, Real32 lengthFactor)
{
    OSG_ASSERT(idx < _mfLengthFactor.size());
    if (getLengthFactor(idx) != lengthFactor)
        editLengthFactor(idx) = lengthFactor;
}

inline
void MultiLightChunk::setRange(const UInt32 idx, Real32 range)
{
    OSG_ASSERT(idx < _mfRangeCutOff.size());
    if (getRange(idx) != range)
        editRangeCutOff(idx) = range;
}

inline
void MultiLightChunk::setSpotlightAngle(const UInt32 idx, Real32 angle)
{
    OSG_ASSERT(idx < _mfSpotlightAngle.size());
    if (getSpotlightAngle(idx) != angle)
        editSpotlightAngle(idx) = angle;
}

inline
void MultiLightChunk::setSpotlightParameter(const UInt32 idx, Real32 value)
{
    OSG_ASSERT(idx < _mfSpotExponent.size());
    if (getSpotExponent(idx) != value)
        editSpotExponent(idx) = value;
}

inline
void MultiLightChunk::setSpotlightExponent(const UInt32 idx, Real32 exponent)
{
    OSG_ASSERT(getHasSpotlightExponent());
    setSpotlightParameter(idx, exponent);
}

inline
void MultiLightChunk::setSpotlightPenumbraAngle(const UInt32 idx, Real32 angle)
{
    OSG_ASSERT(getHasSpotlightPenumbraAngle());
    setSpotlightParameter(idx, angle);
}

inline
void MultiLightChunk::setSpotlightPenumbraFactor(const UInt32 idx, Real32 factor)
{
    OSG_ASSERT(getHasSpotlightPenumbraFactor());
    setSpotlightParameter(idx, factor);
}

inline
void MultiLightChunk::setInnerSuperEllipsesWidth(const UInt32 idx, Real32 width)
{
    OSG_ASSERT(idx < _mfInnerSuperEllipsesWidth.size());
    if (getInnerSuperEllipsesWidth(idx) != width)
        editInnerSuperEllipsesWidth(idx) = width;
}

inline
void MultiLightChunk::setInnerSuperEllipsesHeight(const UInt32 idx, Real32 height)
{
    OSG_ASSERT(idx < _mfInnerSuperEllipsesHeight.size());
    if (getInnerSuperEllipsesHeight(idx) != height)
        editInnerSuperEllipsesHeight(idx) = height;
}

inline
void MultiLightChunk::setOuterSuperEllipsesWidth(const UInt32 idx, Real32 width)
{
    OSG_ASSERT(idx < _mfOuterSuperEllipsesWidth.size());
    if (getOuterSuperEllipsesWidth(idx) != width)
        editOuterSuperEllipsesWidth(idx) = width;
}

inline
void MultiLightChunk::setOuterSuperEllipsesHeight(const UInt32 idx, Real32 height)
{
    OSG_ASSERT(idx < _mfOuterSuperEllipsesHeight.size());
    if (getOuterSuperEllipsesHeight(idx) != height)
        editOuterSuperEllipsesHeight(idx) = height;
}

inline
void MultiLightChunk::setSuperEllipsesRoundness(const UInt32 idx, Real32 roundness)
{
    OSG_ASSERT(idx < _mfSuperEllipsesRoundness.size());
    if (getSuperEllipsesRoundness(idx) != roundness)
        editSuperEllipsesRoundness(idx) = roundness;
}

inline
void MultiLightChunk::setSuperEllipsesTwist(const UInt32 idx, Real32 twist)
{
    OSG_ASSERT(idx < _mfSuperEllipsesTwist.size());
    if (getSuperEllipsesTwist(idx) != twist)
        editSuperEllipsesTwist(idx) = twist;
}

inline
void MultiLightChunk::setRangeCutOn(const UInt32 idx, Real32 cutOn)
{
    OSG_ASSERT(idx < _mfRangeCutOn.size());
    if (getRangeCutOn(idx) != cutOn)
        editRangeCutOn(idx) = cutOn;
}

inline
void MultiLightChunk::setRangeCutOff(const UInt32 idx, Real32 cutOff)
{
    OSG_ASSERT(idx < _mfRangeCutOff.size());
    if (getRangeCutOff(idx) != cutOff)
        editRangeCutOff(idx) = cutOff;
}

inline
void MultiLightChunk::setRangeNearZone(const UInt32 idx, Real32 nearZone)
{
    OSG_ASSERT(idx < _mfRangeNearZone.size());
    if (getRangeNearZone(idx) != nearZone)
        editRangeNearZone(idx) = nearZone;
}

inline
void MultiLightChunk::setRangeFarZone(const UInt32 idx, Real32 farZone)
{
    OSG_ASSERT(idx < _mfRangeFarZone.size());
    if (getRangeFarZone(idx) != farZone)
        editRangeFarZone(idx) = farZone;
}

inline
void MultiLightChunk::setProjectionMatrix(const UInt32 idx, const Matrix& projectionMatrix)
{
    OSG_ASSERT(idx < _mfProjectionMatrix.size());
    //if (getProjectionMatrix(idx) != projectionMatrix)
    if (!getProjectionMatrix(idx).equals(projectionMatrix, 0.f))
        editProjectionMatrix(idx) = projectionMatrix;
}

inline
void MultiLightChunk::setTypeOfLight(const UInt32 idx, MultiLight::TypeOfLight eTypeOfLight)
{
    OSG_ASSERT(idx < _mfTypeOfLight.size());
    if (getTypeOfLight(idx) != eTypeOfLight)
        editTypeOfLight(idx) = eTypeOfLight;
}

inline
void MultiLightChunk::setEnabled(const UInt32 idx, bool flag)
{
    OSG_ASSERT(idx < _mfEnabled.size());
    if (getEnabled(idx) != flag)
        editEnabled(idx) = flag;
}

inline
void MultiLightChunk::setShadow(const UInt32 idx, bool flag)
{
    OSG_ASSERT(idx < _mfShadow.size());
    if (getShadow(idx) != flag)
        editShadow(idx) = flag;
}

inline
void MultiLightChunk::setShadowDataIndex(const UInt32 idx, Int32 shadowDataIndex)
{
    OSG_ASSERT(idx < _mfShadowDataIndex.size());
    if (getShadowDataIndex(idx) != shadowDataIndex)
        editShadowDataIndex(idx) = shadowDataIndex;
}

inline
void MultiLightChunk::setShadowParameterIndex(const UInt32 idx, Int32 shadowParameterIndex)
{
    OSG_ASSERT(idx < _mfShadowParameterIndex.size());
    if (getShadowParameterIndex(idx) != shadowParameterIndex)
        editShadowParameterIndex(idx) = shadowParameterIndex;
}

inline
void MultiLightChunk::setBeacon(const UInt32 idx, Node* const beacon)
{
    OSG_ASSERT(idx < _mfBeacon.size());

    if (getBeacon(idx) != beacon)
    {
        editMField(BeaconFieldMask, _mfBeacon);
        _mfBeacon.replace(idx, beacon);
    }
}

inline
void MultiLightChunk::changedBeacon()
{
    editMField(BeaconFieldMask, _mfBeacon);
}

inline
bool MultiLightChunk::check_invariant() const
{
    std::size_t sz = _mfPosition.size();

    if (getHasSeparateIntensities()
      && (
        sz != _mfAmbientIntensity.size() ||
        sz != _mfDiffuseIntensity.size() ||
        sz != _mfSpecularIntensity.size()))
        return false;

    if (getHasIntensity() && sz != _mfIntensity.size())
        return false;

    if (getHasAttenuation() && sz != _mfAttenuation.size())
        return false;

    if (getHasDecayAttenuation() && sz != _mfDecayAttenuation.size())
        return false;

    if (getHasRangeCutOn() && sz != _mfRangeCutOn.size())
        return false;

    if (getHasRangeCutOff() && sz != _mfRangeCutOff.size())
        return false;

    if (getHasRangeNearZone() && sz != _mfRangeNearZone.size())
        return false;

    if (getHasRangeFarZone() && sz != _mfRangeFarZone.size())
        return false;

    if (getHasProjection() && sz != _mfProjectionMatrix.size())
        return false;

    if (getHasSpotlightExponent() && sz != _mfSpotExponent.size())
        return false;

    if (getHasSpotlightPenumbraAngle() && sz != _mfSpotExponent.size())
        return false;

    if (getHasSpotlightPenumbraFactor() && sz != _mfSpotExponent.size())
        return false;

    if (getHasSpotlightPenumbraFrostbite() && sz != _mfSpotExponent.size())
        return false;

    if (getHasCinemaLight()
      && (
        sz != _mfInnerSuperEllipsesWidth.size() ||
        sz != _mfInnerSuperEllipsesHeight.size() ||
        sz != _mfOuterSuperEllipsesWidth.size() ||
        sz != _mfOuterSuperEllipsesHeight.size() ||
        sz != _mfSuperEllipsesRoundness.size() ||
        sz != _mfSuperEllipsesTwist.size()))
        return false;

    if (getHasShadow() && (
        sz != _mfShadowDataIndex.size() ||
        sz != _mfShadowParameterIndex.size() ||
        sz != _mfShadow.size()))
        return false;
    
    return sz == _mfDirection.size() 
        && sz == _mfSpotlightAngle.size() 
        && sz == _mfTypeOfLight.size() 
        && sz == _mfEnabled.size() 
        && sz == _mfBeacon.size()
        && sz == _mfBeaconMatrix.size();
}

inline
void MultiLightChunk::setGlobalAmbientIntensity(const Color3f& color)
{
    setGlobalAmbientIntensity(color[0], color[1], color[2]);
}

inline
void MultiLightChunk::setGlobalAmbientIntensity(Real32 red, Real32 green, Real32 blue)
{
    Inherited::setGlobalAmbientIntensity(Vec3f(red, green, blue));
}

inline
bool MultiLightChunk::getHasLightSpaceFromWorldSpaceMatrix() const
{
    return (getFeature() & MultiLight::HAS_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX) != 0;
}

inline
bool MultiLightChunk::getHasWorldSpaceFromLightSpaceMatrix() const
{
    return (getFeature() & MultiLight::HAS_WORLD_SPACE_FROM_LIGHT_SPACE_MATRIX) != 0;
}

inline
bool MultiLightChunk::getHasLightSpaceFromEyeSpaceMatrix() const
{
    return (getFeature() & MultiLight::HAS_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX) != 0;
}

inline
bool MultiLightChunk::getHasEyeSpaceFromLightSpaceMatrix() const
{
    return (getFeature() & MultiLight::HAS_EYE_SPACE_FROM_LIGHT_SPACE_MATRIX) != 0;
}

inline
bool MultiLightChunk::getHasProjectionMatrix() const
{
    return (getFeature() & MultiLight::HAS_PROJECTION_MATRIX) != 0;
}

inline
bool MultiLightChunk::getHasInvProjectionMatrix() const
{
    return (getFeature() & MultiLight::HAS_INV_PROJECTION_MATRIX) != 0;
}

inline
bool MultiLightChunk::getHasProjectionLightSpaceFromWorldSpaceMatrix() const
{
    return (getFeature() & MultiLight::HAS_PROJECTION_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX) != 0;
}

inline
bool MultiLightChunk::getHasInvProjectionLightSpaceFromWorldSpaceMatrix() const
{
    return (getFeature() & MultiLight::HAS_INV_PROJECTION_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX) != 0;
}

inline
bool MultiLightChunk::getHasProjectionLightSpaceFromEyeSpaceMatrix() const
{
    return (getFeature() & MultiLight::HAS_PROJECTION_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX) != 0;
}

inline
bool MultiLightChunk::getHasInvProjectionLightSpaceFromEyeSpaceMatrix() const
{
    return (getFeature() & MultiLight::HAS_INV_PROJECTION_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX) != 0;
}

inline
bool MultiLightChunk::getHasIntensity() const
{
    return (getFeature() & MultiLight::HAS_INTENSITY) != 0;
}

inline
bool MultiLightChunk::getHasSeparateIntensities() const
{
    return (getFeature() & MultiLight::HAS_SEPARATE_INTENSITIES) != 0;
}

inline
bool MultiLightChunk::getHasAttenuation() const
{
    return (getFeature() & MultiLight::HAS_ATTENUATION) != 0;
}

inline
bool MultiLightChunk::getHasDecayAttenuation() const
{
    return (getFeature() & MultiLight::HAS_DECAY_ATTENUATION) != 0;
}

inline
bool MultiLightChunk::getHasLengthFactor() const
{
    return (getFeature() & MultiLight::HAS_LENGTH_FACTOR) != 0;
}

inline
bool MultiLightChunk::getHasRangeCutOn() const
{
    return (getFeature() & MultiLight::HAS_RANGE_CUT_ON) != 0;
}

inline
bool MultiLightChunk::getHasRangeCutOff() const
{
    return (getFeature() & MultiLight::HAS_RANGE_CUT_OFF) != 0;
}

inline
bool MultiLightChunk::getHasRangeNearZone() const
{
    return (getFeature() & MultiLight::HAS_RANGE_NEAR_ZONE) != 0;
}

inline
bool MultiLightChunk::getHasRangeFarZone() const
{
    return (getFeature() & MultiLight::HAS_RANGE_FAR_ZONE) != 0;
}

inline
bool MultiLightChunk::getHasSpotlightAngle() const
{
    return (getFeature() & MultiLight::HAS_SPOTLIGHT_ANGLE) != 0;
}

inline
bool MultiLightChunk::getHasCosSpotlightAngle() const
{
    return (getFeature() & MultiLight::HAS_COS_SPOTLIGHT_ANGLE) != 0;
}

inline
bool MultiLightChunk::getHasTanSpotlightAngle() const
{
    return (getFeature() & MultiLight::HAS_TAN_SPOTLIGHT_ANGLE) != 0;
}

inline
bool MultiLightChunk::getHasSpotlightExponent() const
{
    return (getFeature() & MultiLight::HAS_SPOTLIGHT_EXPONENT) != 0;
}

inline
bool MultiLightChunk::getHasSpotlightPenumbraAngle() const
{
    return (getFeature() & MultiLight::HAS_SPOTLIGHT_PENUMBRA_ANGLE) != 0;
}

inline
bool MultiLightChunk::getHasSpotlightPenumbraFactor() const
{
    return (getFeature() & MultiLight::HAS_SPOTLIGHT_PENUMBRA_FACTOR) != 0;
}

inline
bool MultiLightChunk::getHasSpotlightPenumbraFrostbite() const
{
    return (getFeature() & MultiLight::HAS_SPOTLIGHT_PENUMBRA_FROSTBITE) != 0;
}

inline
bool MultiLightChunk::getHasCinemaLight() const
{
    return (getFeature() & MultiLight::HAS_CINEMA_LIGHT) != 0;
}

inline
bool MultiLightChunk::getHasShadow() const
{
    return (getFeature() & MultiLight::HAS_SHADOW) != 0;
}

inline
bool MultiLightChunk::getHasProjection() const
{
    return (getFeature() & MultiLight::HAS_PROJECTION) != 0;
}

inline
bool MultiLightChunk::getHasGlobalAmbientIntensity() const
{
    return (getFeature() & MultiLight::HAS_GLOBAL_AMBIENT_INTENSITY) != 0;
}

inline
bool MultiLightChunk::getAutoCalcRanges() const
{
    return (getFeature() & MultiLight::AUTO_CALC_RANGES) != 0;
}

inline
bool MultiLightChunk::getEyeSpace() const
{
    return (getFeature() & MultiLight::EYE_SPACE) != 0;
}

inline
bool MultiLightChunk::getHasGlobalState() const
{
    return getHasGlobalAmbientIntensity();
}

inline
void MultiLightChunk::setFeatureImpl(UInt32 feature)
{
    if (feature != getFeature())
    {
        setFeature(feature);

        force_invariant();
    }
}

inline
bool MultiLightChunk::checkFeatures(UInt32 features) const
{
    UInt32 check = getFeature();
    return (check & features) == features;
}

inline
void MultiLightChunk::setFeatures(UInt32 features, bool value)
{
    UInt32 feature = value ? getFeature() |  features
                           : getFeature() & ~features;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setCodeFeatureImpl(UInt32 feature)
{
    if (feature != getCodeFeature())
    {
        setCodeFeature(feature);
    }
}

inline
bool MultiLightChunk::checkCodeFeatures(UInt32 features) const
{
    UInt32 check = getCodeFeature();
    return (check & features) == features;
}

inline
void MultiLightChunk::setCodeFeatures(UInt32 features, bool value)
{
    UInt32 feature = value ? getCodeFeature() |  features
                           : getCodeFeature() & ~features;

    setCodeFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasLightSpaceFromWorldSpaceMatrix(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX
                           : getFeature() & ~MultiLight::HAS_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasWorldSpaceFromLightSpaceMatrix(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_WORLD_SPACE_FROM_LIGHT_SPACE_MATRIX
                           : getFeature() & ~MultiLight::HAS_WORLD_SPACE_FROM_LIGHT_SPACE_MATRIX;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasLightSpaceFromEyeSpaceMatrix(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX
                           : getFeature() & ~MultiLight::HAS_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasEyeSpaceFromLightSpaceMatrix(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_EYE_SPACE_FROM_LIGHT_SPACE_MATRIX
                           : getFeature() & ~MultiLight::HAS_EYE_SPACE_FROM_LIGHT_SPACE_MATRIX;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasProjectionMatrix(bool value)
{
    if (value)
        setHasProjection(value);

    UInt32 feature = value ? getFeature() |  MultiLight::HAS_PROJECTION_MATRIX
                           : getFeature() & ~MultiLight::HAS_PROJECTION_MATRIX;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasInvProjectionMatrix(bool value)
{
    if (value)
        setHasProjection(value);

    UInt32 feature = value ? getFeature() |  MultiLight::HAS_INV_PROJECTION_MATRIX
                           : getFeature() & ~MultiLight::HAS_INV_PROJECTION_MATRIX;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasProjectionLightSpaceFromWorldSpaceMatrix(bool value)
{
    if (value)
        setHasProjection(value);

    UInt32 feature = value ? getFeature() |  MultiLight::HAS_PROJECTION_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX
                           : getFeature() & ~MultiLight::HAS_PROJECTION_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasInvProjectionLightSpaceFromWorldSpaceMatrix(bool value)
{
    if (value)
        setHasProjection(value);

    UInt32 feature = value ? getFeature() |  MultiLight::HAS_INV_PROJECTION_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX
                           : getFeature() & ~MultiLight::HAS_INV_PROJECTION_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasProjectionLightSpaceFromEyeSpaceMatrix(bool value)
{
    if (value)
        setHasProjection(value);

    UInt32 feature = value ? getFeature() |  MultiLight::HAS_PROJECTION_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX
                           : getFeature() & ~MultiLight::HAS_PROJECTION_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasInvProjectionLightSpaceFromEyeSpaceMatrix(bool value)
{
    if (value)
        setHasProjection(value);

    UInt32 feature = value ? getFeature() |  MultiLight::HAS_INV_PROJECTION_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX
                           : getFeature() & ~MultiLight::HAS_INV_PROJECTION_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasIntensity(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_INTENSITY
                           : getFeature() & ~MultiLight::HAS_INTENSITY;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasSeparateIntensities(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_SEPARATE_INTENSITIES
                           : getFeature() & ~MultiLight::HAS_SEPARATE_INTENSITIES;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasAttenuation(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_ATTENUATION
                           : getFeature() & ~MultiLight::HAS_ATTENUATION;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasDecayAttenuation(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_DECAY_ATTENUATION
                           : getFeature() & ~MultiLight::HAS_DECAY_ATTENUATION;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasLengthFactor(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_LENGTH_FACTOR
                           : getFeature() & ~MultiLight::HAS_LENGTH_FACTOR;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasRangeCutOn(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_RANGE_CUT_ON
                           : getFeature() & ~MultiLight::HAS_RANGE_CUT_ON;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasRangeCutOff(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_RANGE_CUT_OFF
                           : getFeature() & ~MultiLight::HAS_RANGE_CUT_OFF;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasRangeNearZone(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_RANGE_NEAR_ZONE
                           : getFeature() & ~MultiLight::HAS_RANGE_NEAR_ZONE;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasRangeFarZone(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_RANGE_FAR_ZONE
                           : getFeature() & ~MultiLight::HAS_RANGE_FAR_ZONE;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasSpotlightAngle(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_SPOTLIGHT_ANGLE
                           : getFeature() & ~MultiLight::HAS_SPOTLIGHT_ANGLE;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasCosSpotlightAngle(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_COS_SPOTLIGHT_ANGLE
                           : getFeature() & ~MultiLight::HAS_COS_SPOTLIGHT_ANGLE;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasTanSpotlightAngle(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_TAN_SPOTLIGHT_ANGLE
                           : getFeature() & ~MultiLight::HAS_TAN_SPOTLIGHT_ANGLE;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasSpotlightExponent(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_SPOTLIGHT_EXPONENT
                           : getFeature() & ~MultiLight::HAS_SPOTLIGHT_EXPONENT;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasSpotlightPenumbraAngle(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_SPOTLIGHT_PENUMBRA_ANGLE
                           : getFeature() & ~MultiLight::HAS_SPOTLIGHT_PENUMBRA_ANGLE;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasSpotlightPenumbraFactor(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_SPOTLIGHT_PENUMBRA_FACTOR
                           : getFeature() & ~MultiLight::HAS_SPOTLIGHT_PENUMBRA_FACTOR;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasSpotlightPenumbraFrostbite(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_SPOTLIGHT_PENUMBRA_FROSTBITE
                           : getFeature() & ~MultiLight::HAS_SPOTLIGHT_PENUMBRA_FROSTBITE;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasCinemaLight(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_CINEMA_LIGHT
                           : getFeature() & ~MultiLight::HAS_CINEMA_LIGHT;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasShadow(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_SHADOW
                           : getFeature() & ~MultiLight::HAS_SHADOW;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasProjection(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_PROJECTION
                           : getFeature() & ~MultiLight::HAS_PROJECTION;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setHasGlobalAmbientIntensity(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::HAS_GLOBAL_AMBIENT_INTENSITY
                           : getFeature() & ~MultiLight::HAS_GLOBAL_AMBIENT_INTENSITY;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setAutoCalcRanges(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::AUTO_CALC_RANGES
                           : getFeature() & ~MultiLight::AUTO_CALC_RANGES;

    setFeatureImpl(feature);
}

inline
void MultiLightChunk::setEyeSpace(bool value)
{
    UInt32 feature = value ? getFeature() |  MultiLight::EYE_SPACE
                           : getFeature() & ~MultiLight::EYE_SPACE;

    setFeatureImpl(feature);
}

inline
bool MultiLightChunk::getCodeDistanceAttenuationClassic() const
{
    return (getCodeFeature() & MultiLight::CODE_DISTANCE_ATTENUATION_CLASSIC) != 0;
}

inline
bool MultiLightChunk::getCodeDistanceAttenuationPhysical() const
{
    return (getCodeFeature() & MultiLight::CODE_DISTANCE_ATTENUATION_PHYSICAL) != 0;
}

inline
bool MultiLightChunk::getCodeDistanceAttenuationDecay() const
{
    return (getCodeFeature() & MultiLight::CODE_DISTANCE_ATTENUATION_DECAY) != 0;
}

inline
bool MultiLightChunk::getCodeDistanceAttenuationMixPhysical() const
{
    return (getCodeFeature() & MultiLight::CODE_DISTANCE_ATTENUATION_MIX_PHYSICAL) != 0;
}

inline
bool MultiLightChunk::getCodeDistanceAttenuationMixDecay() const
{
    return (getCodeFeature() & MultiLight::CODE_DISTANCE_ATTENUATION_MIX_DECAY) != 0;
}

inline
bool MultiLightChunk::getCodeDistanceAttenuationSmoothHermite() const
{
    return (getCodeFeature() & MultiLight::CODE_DISTANCE_ATTENUATION_SMOOTH_HERMITE) != 0;
}

inline
bool MultiLightChunk::getCodeSpotAttenuationClassic() const
{
    return (getCodeFeature() & MultiLight::CODE_SPOT_ATTENUATION_CLASSIC) != 0;
}

inline
bool MultiLightChunk::getCodeSpotAttenuationSmoothHermite() const
{
    return (getCodeFeature() & MultiLight::CODE_SPOT_ATTENUATION_SMOOTH_HERMITE) != 0;
}

inline
bool MultiLightChunk::getCodeSpotAttenuationSmoothHermite2() const
{
    return (getCodeFeature() & MultiLight::CODE_SPOT_ATTENUATION_SMOOTH_HERMITE_2) != 0;
}

inline
bool MultiLightChunk::getCodeSpotAttenuationFrostbite() const
{
    return (getCodeFeature() & MultiLight::CODE_SPOT_ATTENUATION_FROSTBITE) != 0;
}

inline
void MultiLightChunk::setCodeDistanceAttenuationClassic(bool value)
{
    UInt32 feature = value ? getCodeFeature() |  MultiLight::CODE_DISTANCE_ATTENUATION_CLASSIC
                           : getCodeFeature() & ~MultiLight::CODE_DISTANCE_ATTENUATION_CLASSIC;

    setCodeFeatureImpl(feature);
}

inline
void MultiLightChunk::setCodeDistanceAttenuationPhysical(bool value)
{
    UInt32 feature = value ? getCodeFeature() |  MultiLight::CODE_DISTANCE_ATTENUATION_PHYSICAL
                           : getCodeFeature() & ~MultiLight::CODE_DISTANCE_ATTENUATION_PHYSICAL;

    setCodeFeatureImpl(feature);
}

inline
void MultiLightChunk::setCodeDistanceAttenuationDecay(bool value)
{
    UInt32 feature = value ? getCodeFeature() |  MultiLight::CODE_DISTANCE_ATTENUATION_DECAY
                           : getCodeFeature() & ~MultiLight::CODE_DISTANCE_ATTENUATION_DECAY;

    setCodeFeatureImpl(feature);
}

inline
void MultiLightChunk::setCodeDistanceAttenuationMixPhysical(bool value)
{
    UInt32 feature = value ? getCodeFeature() |  MultiLight::CODE_DISTANCE_ATTENUATION_MIX_PHYSICAL
                           : getCodeFeature() & ~MultiLight::CODE_DISTANCE_ATTENUATION_MIX_PHYSICAL;

    setCodeFeatureImpl(feature);
}

inline
void MultiLightChunk::setCodeDistanceAttenuationMixDecay(bool value)
{
    UInt32 feature = value ? getCodeFeature() |  MultiLight::CODE_DISTANCE_ATTENUATION_MIX_DECAY
                           : getCodeFeature() & ~MultiLight::CODE_DISTANCE_ATTENUATION_MIX_DECAY;

    setCodeFeatureImpl(feature);
}

inline
void MultiLightChunk::setCodeDistanceAttenuationSmoothHermite(bool value)
{
    UInt32 feature = value ? getCodeFeature() |  MultiLight::CODE_DISTANCE_ATTENUATION_SMOOTH_HERMITE
                           : getCodeFeature() & ~MultiLight::CODE_DISTANCE_ATTENUATION_SMOOTH_HERMITE;

    setCodeFeatureImpl(feature);
}

inline
void MultiLightChunk::setCodeSpotAttenuationClassic(bool value)
{
    UInt32 feature = value ? getCodeFeature() |  MultiLight::CODE_SPOT_ATTENUATION_CLASSIC
                           : getCodeFeature() & ~MultiLight::CODE_SPOT_ATTENUATION_CLASSIC;

    setCodeFeatureImpl(feature);
}

inline
void MultiLightChunk::setCodeSpotAttenuationSmoothHermite(bool value)
{
    UInt32 feature = value ? getCodeFeature() |  MultiLight::CODE_SPOT_ATTENUATION_SMOOTH_HERMITE
                           : getCodeFeature() & ~MultiLight::CODE_SPOT_ATTENUATION_SMOOTH_HERMITE;

    setCodeFeatureImpl(feature);
}

inline
void MultiLightChunk::setCodeSpotAttenuationSmoothHermite2(bool value)
{
    UInt32 feature = value ? getCodeFeature() |  MultiLight::CODE_SPOT_ATTENUATION_SMOOTH_HERMITE_2
                           : getCodeFeature() & ~MultiLight::CODE_SPOT_ATTENUATION_SMOOTH_HERMITE_2;

    setCodeFeatureImpl(feature);
}

inline
void MultiLightChunk::setCodeSpotAttenuationFrostbite(bool value)
{
    UInt32 feature = value ? getCodeFeature() |  MultiLight::CODE_SPOT_ATTENUATION_FROSTBITE
                           : getCodeFeature() & ~MultiLight::CODE_SPOT_ATTENUATION_FROSTBITE;

    setCodeFeatureImpl(feature);
}

inline
void MultiLightChunk::calcCutOnRange(
    DrawEnv* pEnv,
    UInt32   idx,
    bool     attenuationAware,
    Real32&  cutOnRange) const
{
    Real32 cutOffRange;
    calcRange(pEnv, idx, attenuationAware, cutOnRange, cutOffRange);
}

inline
void MultiLightChunk::calcCutOffRange(
    DrawEnv* pEnv,
    UInt32   idx,
    bool     attenuationAware,
    Real32&  cutOffRange) const
{
    Real32 cutOnRange;
    calcRange(pEnv, idx, attenuationAware, cutOnRange, cutOffRange);
}

inline
void MultiLightChunk::calcPosition(
    DrawEnv* pEnv,
    UInt32   idx,
    Pnt3f&   position, 
    bool     eyeSpace) const
{
    Vec3f direction;
    calcPositionAndDirection(pEnv, idx, position, direction, eyeSpace);
}

inline
void MultiLightChunk::calcDirection(
    DrawEnv* pEnv,
    UInt32   idx,
    Vec3f&   direction,
    bool     eyeSpace) const
{
    Pnt3f position;
    calcPositionAndDirection(pEnv, idx, position, direction, eyeSpace);
}

inline
void MultiLightChunk::calcPositionAndDirection(
    DrawEnv* pEnv,
    UInt32   idx,
    Pnt3f&   position, 
    Vec3f&   direction,
    bool     eyeSpace) const
{
    if (eyeSpace)
    {
        transformToEyeSpace(
                pEnv, getBeacon(idx), 
                getPosition(idx), getDirection(idx), 
                position, direction);
    }
    else
    {
        transformToWorldSpace(
                pEnv, getBeacon(idx), 
                getPosition(idx), getDirection(idx), 
                position, direction);
    }
}

inline
void MultiLightChunk::calcLightSpaceMatrixLSFromWS(
    UInt32   idx,
    Matrix&  matLSFromWS) const
{
    switch (getTypeOfLight(idx))
    {
        case MultiLight::POINT_LIGHT:
            calcPointLightMatrixLSFromWS(getBeacon(idx), getPosition(idx), matLSFromWS);
            break;
        case MultiLight::DIRECTIONAL_LIGHT:
            calcDirectionalLightMatrixLSFromWS(getBeacon(idx), getDirection(idx), matLSFromWS);
            break;
        case MultiLight::SPOT_LIGHT:
        case MultiLight::CINEMA_LIGHT:
            calcSpotLightMatrixLSFromWS(getBeacon(idx), getPosition(idx), getDirection(idx), matLSFromWS);
            break;
    }
}

inline
void MultiLightChunk::calcLightSpaceMatrixLSFromES(
    DrawEnv* pEnv,
    UInt32   idx,
    Matrix&  matLSFromES) const
{
    switch (getTypeOfLight(idx))
    {
        case MultiLight::POINT_LIGHT:
            calcPointLightMatrixLSFromES(pEnv, getBeacon(idx), getPosition(idx), matLSFromES);
            break;
        case MultiLight::DIRECTIONAL_LIGHT:
            calcDirectionalLightMatrixLSFromES(pEnv, getBeacon(idx), getDirection(idx), matLSFromES);
            break;
        case MultiLight::SPOT_LIGHT:
        case MultiLight::CINEMA_LIGHT:
            calcSpotLightMatrixLSFromES(pEnv, getBeacon(idx), getPosition(idx), getDirection(idx), matLSFromES);
            break;
    }
}

inline
void MultiLightChunk::calcLightSpaceMatricesLSFrom(
    DrawEnv* pEnv,
    UInt32   idx,
    Matrix&  matLSFromWS, 
    Matrix&  matLSFromES) const
{
    switch (getTypeOfLight(idx))
    {
        case MultiLight::POINT_LIGHT:
            calcPointLightMatricesLSFrom(pEnv, getBeacon(idx), getPosition(idx), matLSFromWS, matLSFromES);
            break;
        case MultiLight::DIRECTIONAL_LIGHT:
            calcDirectionalLightMatricesLSFrom(pEnv, getBeacon(idx), getDirection(idx), matLSFromWS, matLSFromES);
            break;
        case MultiLight::SPOT_LIGHT:
        case MultiLight::CINEMA_LIGHT:
            calcSpotLightMatricesLSFrom(pEnv, getBeacon(idx), getPosition(idx), getDirection(idx), matLSFromWS, matLSFromES);
            break;
    }
}

inline
void MultiLightChunk::calcInvLightSpaceMatrixWSFromLS(
    UInt32   idx,
    Matrix&  matWSFromLS) const
{
    Matrix matLSFromWS;
    calcLightSpaceMatrixLSFromWS(idx, matLSFromWS);

    matLSFromWS.inverse(matWSFromLS);
}

inline
void MultiLightChunk::calcInvLightSpaceMatricesWSFrom(
    DrawEnv* pEnv,
    UInt32   idx,
    Matrix&  matWSFromLS, 
    Matrix&  matESFromLS) const
{
    Matrix matLSFromWS, matLSFromES;
    calcLightSpaceMatricesLSFrom(pEnv, idx, matLSFromWS, matLSFromES);

    matLSFromWS.inverse(matWSFromLS);
    matLSFromES.inverse(matESFromLS);
}

inline
void MultiLightChunk::calcProjectionMatrix(
    DrawEnv*     pEnv,
    UInt32       idx,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matProjection) const
{
    Real32 spotlightAngle, cosSpotlightAngle;
    calcSpotAngle(idx, spotlightAngle, cosSpotlightAngle);

    Real32 zNear, zFar;
    calcFrustumZ(pEnv, idx, zNear, zFar);

    calcProjectionMatrix(getTypeOfLight(idx), spotlightAngle, zNear, zFar, lightMin, lightMax, matProjection);
}

inline
void MultiLightChunk::calcInvProjectionMatrix(
    DrawEnv*     pEnv,
    UInt32       idx,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matInvProjection) const
{
    Matrix  matProjection;
    calcProjectionMatrix(pEnv, idx, lightMin, lightMax, matProjection);

    matProjection.inverse(matInvProjection);
}

inline
void MultiLightChunk::calcLightSpaceProjectionMatrixLSFromWS(
    DrawEnv*     pEnv,
    UInt32       idx,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matLightSpaceProjectionLSFromWS) const
{
    calcProjectionMatrix(pEnv, idx, lightMin, lightMax, matLightSpaceProjectionLSFromWS);

    Matrix  matLSFromWS;
    calcLightSpaceMatrixLSFromWS(idx, matLSFromWS);

    matLightSpaceProjectionLSFromWS.mult(matLSFromWS);
}

inline
void MultiLightChunk::calcLightSpaceProjectionMatrixLSFromES(
    DrawEnv*     pEnv,
    UInt32       idx,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matLightSpaceProjectionLSFromES) const
{
    calcProjectionMatrix(pEnv, idx, lightMin, lightMax, matLightSpaceProjectionLSFromES);

    Matrix  matLSFromES;
    calcLightSpaceMatrixLSFromES(pEnv, idx, matLSFromES);

    matLightSpaceProjectionLSFromES.mult(matLSFromES);
}

inline
void MultiLightChunk::calcInvLightSpaceProjectionMatrixLSFromWS(
    DrawEnv*     pEnv,
    UInt32       idx,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matInvLightSpaceProjectionLSFromWS) const
{
    Matrix  matLightSpaceProjectionLSFromWS;
    calcLightSpaceProjectionMatrixLSFromWS(pEnv, idx, lightMin, lightMax, matLightSpaceProjectionLSFromWS);

    matLightSpaceProjectionLSFromWS.inverse(matInvLightSpaceProjectionLSFromWS);
}

inline
void MultiLightChunk::calcInvLightSpaceProjectionMatrixLSFromES(
    DrawEnv*     pEnv,
    UInt32       idx,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matInvLightSpaceProjectionLSFromES) const
{
    Matrix  matLightSpaceProjectionLSFromES;
    calcLightSpaceProjectionMatrixLSFromES(pEnv, idx, lightMin, lightMax, matLightSpaceProjectionLSFromES);

    matLightSpaceProjectionLSFromES.inverse(matInvLightSpaceProjectionLSFromES);
}

inline
void MultiLightChunk::calcProjectionMatrix(
    UInt32       idx,
    Real32       zNear,
    Real32       zFar,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matProjection) const
{
    Real32 spotlightAngle, cosSpotlightAngle;
    calcSpotAngle(idx, spotlightAngle, cosSpotlightAngle);

    calcProjectionMatrix(getTypeOfLight(idx), spotlightAngle, zNear, zFar, lightMin, lightMax, matProjection);
}

inline
void MultiLightChunk::calcInvProjectionMatrix(
    UInt32       idx,
    Real32       zNear,
    Real32       zFar,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matInvProjection) const
{
    Matrix  matProjection;
    calcProjectionMatrix(idx, zNear, zFar, lightMin, lightMax, matProjection);

    matProjection.inverse(matInvProjection);
}

inline
void MultiLightChunk::calcLightSpaceProjectionMatrixLSFromWS(
    UInt32       idx,
    Real32       zNear,
    Real32       zFar,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matLightSpaceProjectionLSFromWS) const
{
    calcProjectionMatrix(idx, zNear, zFar, lightMin, lightMax, matLightSpaceProjectionLSFromWS);

    Matrix  matLSFromWS;
    calcLightSpaceMatrixLSFromWS(idx, matLSFromWS);

    matLightSpaceProjectionLSFromWS.mult(matLSFromWS);
}

inline
void MultiLightChunk::calcLightSpaceProjectionMatrixLSFromES(
    DrawEnv*     pEnv,
    UInt32       idx,
    Real32       zNear,
    Real32       zFar,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matLightSpaceProjectionLSFromES) const
{
    calcProjectionMatrix(idx, zNear, zFar, lightMin, lightMax, matLightSpaceProjectionLSFromES);

    Matrix  matLSFromES;
    calcLightSpaceMatrixLSFromES(pEnv, idx, matLSFromES);

    matLightSpaceProjectionLSFromES.mult(matLSFromES);
}

inline
void MultiLightChunk::calcInvLightSpaceProjectionMatrixLSFromWS(
    UInt32       idx,
    Real32       zNear,
    Real32       zFar,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matInvLightSpaceProjectionLSFromWS) const
{
    Matrix  matLightSpaceProjectionLSFromWS;
    calcLightSpaceProjectionMatrixLSFromWS(idx, zNear, zFar, lightMin, lightMax, matLightSpaceProjectionLSFromWS);

    matLightSpaceProjectionLSFromWS.inverse(matInvLightSpaceProjectionLSFromWS);
}

inline
void MultiLightChunk::calcInvLightSpaceProjectionMatrixLSFromES(
    DrawEnv*     pEnv,
    UInt32       idx,
    Real32       zNear,
    Real32       zFar,
    const Pnt3f& lightMin,
    const Pnt3f& lightMax,
    Matrix&      matInvLightSpaceProjectionLSFromES) const
{
    Matrix  matLightSpaceProjectionLSFromES;
    calcLightSpaceProjectionMatrixLSFromES(pEnv, idx, lightMin, lightMax, matLightSpaceProjectionLSFromES);

    matLightSpaceProjectionLSFromES.inverse(matInvLightSpaceProjectionLSFromES);
}

inline
void MultiLightChunk::calcInvProjectionMatrix(
    MultiLight::TypeOfLight typeOfLight,
    Real32                  spotlightAngle,
    Real32                  zNear,
    Real32                  zFar,
    const Pnt3f&            lightMin,
    const Pnt3f&            lightMax,
    Matrix&                 matInvProjection) const
{
    Matrix  matProjection;
    calcProjectionMatrix(typeOfLight, spotlightAngle, zNear, zFar, lightMin, lightMax, matProjection);

    matProjection.inverse(matInvProjection);
}

inline
Matrix MultiLightChunk::getInvProjectionMatrix(
    UInt32 idx) const
{
    Matrix matInvProjection;

    const Matrix& matProjection = getProjectionMatrix(idx);
    matProjection.inverse(matInvProjection);

    return matInvProjection;
}

inline
Matrix MultiLightChunk::getLightSpaceProjectionMatrixLSFromWS(
    UInt32 idx) const
{
    Matrix matLightSpaceProjectionLSFromWS = getProjectionMatrix(idx);

    Matrix  matLSFromWS;
    calcLightSpaceMatrixLSFromWS(idx, matLSFromWS);

    matLightSpaceProjectionLSFromWS.mult(matLSFromWS);

    return matLightSpaceProjectionLSFromWS;
}

inline
Matrix MultiLightChunk::getLightSpaceProjectionMatrixLSFromES(
    DrawEnv* pEnv, 
    UInt32   idx) const
{
    Matrix matLightSpaceProjectionLSFromES = getProjectionMatrix(idx);

    Matrix  matLSFromES;
    calcLightSpaceMatrixLSFromES(pEnv, idx, matLSFromES);

    matLightSpaceProjectionLSFromES.mult(matLSFromES);

    return matLightSpaceProjectionLSFromES;
}

inline
Matrix MultiLightChunk::getLightSpaceProjectionMatrixLSFrom(
    UInt32        idx,
    const Matrix& matLSFrom) const
{
    Matrix matLightSpaceProjectionLSFrom = getProjectionMatrix(idx);
    matLightSpaceProjectionLSFrom.mult(matLSFrom);

    return matLightSpaceProjectionLSFrom;
}

inline
Matrix MultiLightChunk::getInvLightSpaceProjectionMatrixLSFromWS(UInt32 idx) const
{
    Matrix matLightSpaceProjectionLSFromWS = getLightSpaceProjectionMatrixLSFromWS(idx);

    Matrix matInvLightSpaceProjectionLSFromWS;
    matLightSpaceProjectionLSFromWS.inverse(matInvLightSpaceProjectionLSFromWS);

    return matInvLightSpaceProjectionLSFromWS;
}

inline
Matrix MultiLightChunk::getInvLightSpaceProjectionMatrixLSFromES(
    DrawEnv* pEnv,
    UInt32   idx) const
{
    Matrix matLightSpaceProjectionLSFromES = getLightSpaceProjectionMatrixLSFromES(pEnv, idx);

    Matrix matInvLightSpaceProjectionLSFromES;
    matLightSpaceProjectionLSFromES.inverse(matInvLightSpaceProjectionLSFromES);

    return matInvLightSpaceProjectionLSFromES;
}

inline
Matrix MultiLightChunk::getInvLightSpaceProjectionMatrixLSFrom(
    UInt32        idx,
    const Matrix& matLSFrom) const
{
    Matrix matLightSpaceProjectionLSFrom = getLightSpaceProjectionMatrixLSFrom(idx, matLSFrom);

    Matrix matInvLightSpaceProjectionLSFrom;
    matLightSpaceProjectionLSFrom.inverse(matInvLightSpaceProjectionLSFrom);

    return matInvLightSpaceProjectionLSFrom;
}

inline
void MultiLightChunk::calcDirectionalLightMatricesLSFrom(
    DrawEnv* pEnv,
    Node* beacon, 
    const Vec3f& direction_bs,
    Matrix& matLSFromWS,
    Matrix& matLSFromES) const
{
    calcDirectionalLightMatrixLSFromWS(beacon, direction_bs,matLSFromWS);

    Matrix matWsFromEs = pEnv->getCameraToWorld();
    matLSFromES = matLSFromWS;
    matLSFromES.mult(matWsFromEs);
}

inline
void MultiLightChunk::calcDirectionalLightMatrixLSFromES(
    DrawEnv* pEnv,
    Node* beacon, 
    const Vec3f& direction_bs,
    Matrix& matLSFromES) const
{
    Matrix matLSFromWS;
    calcDirectionalLightMatricesLSFrom(pEnv, beacon, direction_bs, matLSFromWS, matLSFromES);
}

inline
void MultiLightChunk::calcPointLightMatricesLSFrom(
    DrawEnv* pEnv,
    Node* beacon, 
    const Pnt3f& position_bs, 
    Matrix& matLSFromWS,
    Matrix& matLSFromES) const
{
    calcPointLightMatrixLSFromWS(beacon, position_bs, matLSFromWS);

    Matrix matWsFromEs = pEnv->getCameraToWorld();
    matLSFromES = matLSFromWS;
    matLSFromES.mult(matWsFromEs);
}

inline
void MultiLightChunk::calcPointLightMatrixLSFromES(
    DrawEnv* pEnv,
    Node* beacon, 
    const Pnt3f& position_bs, 
    Matrix& matLSFromES) const
{
    Matrix matLSFromWS;
    calcPointLightMatricesLSFrom(pEnv, beacon, position_bs, matLSFromWS, matLSFromES);
}

inline
void MultiLightChunk::calcSpotLightMatricesLSFrom(
    DrawEnv* pEnv,
    Node* beacon, 
    const Pnt3f& position_bs, 
    const Vec3f& direction_bs, 
    Matrix& matLSFromWS,
    Matrix& matLSFromES) const
{
    calcSpotLightMatrixLSFromWS(beacon, position_bs, direction_bs, matLSFromWS);

    Matrix matWsFromEs = pEnv->getCameraToWorld();
    matLSFromES = matLSFromWS;
    matLSFromES.mult(matWsFromEs);
}

inline
void MultiLightChunk::calcSpotLightMatrixLSFromES(
    DrawEnv* pEnv,
    Node* beacon, 
    const Pnt3f& position_bs, 
    const Vec3f& direction_bs, 
    Matrix& matLSFromES) const
{
    Matrix matLSFromWS;
    calcSpotLightMatricesLSFrom(pEnv, beacon, position_bs, direction_bs, matLSFromWS, matLSFromES);
}



OSG_END_NAMESPACE
