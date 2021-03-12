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
UInt32 MultiLightGroup::addLight(MultiLight::TypeOfLight eTypeOfLight)
{
    MultiLightChunk* pChunk = getChunk();
    return pChunk->addLight(eTypeOfLight);
}

inline
UInt32 MultiLightGroup::addLight(const MultiLight& light)
{
    MultiLightChunk* pChunk = getChunk();
    return pChunk->addLight(light);
}

inline
void MultiLightGroup::updateLight(const UInt32 idx, const MultiLight& light)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->updateLight(idx, light);
}

inline
MultiLight MultiLightGroup::getLight(const UInt32 idx)
{
    MultiLightChunk* pChunk = getChunk();
    return pChunk->getLight(idx);
}

inline
void MultiLightGroup::removeLight(const UInt32 idx)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->removeLight(idx);
}

inline
void MultiLightGroup::clearLights()
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->clearLights();
}

inline
UInt32 MultiLightGroup::getNumLights() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getNumLights();
}

inline
bool MultiLightGroup::empty() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->empty();
}

inline
void MultiLightGroup::enableLights(bool flag)
{
    MultiLightChunk* pChunk = getChunk();
    return pChunk->enableLights(flag);
}

inline
void MultiLightGroup::setLayoutType(UInt32 layout)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setLayoutType(layout);
}

inline
const Vec3f& MultiLightGroup::getGlobalAmbientIntensity() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getGlobalAmbientIntensity();
}

inline
const std::string& MultiLightGroup::getLightBlockName() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getLightBlockName();
}

inline
const std::string& MultiLightGroup::getLightVariableName() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getLightVariableName();
}

inline
void MultiLightGroup::setGlobalAmbientIntensity(const Vec3f &value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setGlobalAmbientIntensity(value);
}

inline
void MultiLightGroup::setGlobalAmbientIntensity(const Color3f &color)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setGlobalAmbientIntensity(color);
}

inline
void MultiLightGroup::setGlobalAmbientIntensity(Real32 red, Real32 green, Real32 blue)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setGlobalAmbientIntensity(red, green, blue);
}

inline
void MultiLightGroup::setLightBlockName(const std::string &value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setLightBlockName(value);
}

inline
void MultiLightGroup::setLightVariableName(const std::string &value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setLightVariableName(value);
}

inline
const Pnt3f& MultiLightGroup::getPosition(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getPosition(idx);
}

inline
const Vec3f& MultiLightGroup::getDirection(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getDirection(idx);
}

inline
const Vec3f& MultiLightGroup::getIntensity(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getIntensity(idx);
}

inline
const Vec3f& MultiLightGroup::getAmbient(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getAmbient(idx);
}

inline
const Vec3f& MultiLightGroup::getDiffuse(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getDiffuse(idx);
}

inline
const Vec3f& MultiLightGroup::getSpecular(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getSpecular(idx);
}

inline
const Vec3f& MultiLightGroup::getAttenuation(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getAttenuation(idx);
}

inline
Real32 MultiLightGroup::getDecayAttenuation(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getDecayAttenuation(idx);
}

inline
Real32 MultiLightGroup::getLengthFactor(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getLengthFactor(idx);
}

inline
Real32 MultiLightGroup::getRange(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getRange(idx);
}

inline
Real32 MultiLightGroup::getSpotlightAngle(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getSpotlightAngle(idx);
}

inline
Real32 MultiLightGroup::getSpotlightParameter(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getSpotlightParameter(idx);
}

inline
Real32 MultiLightGroup::getSpotlightExponent(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getSpotlightExponent(idx);
}

inline
Real32 MultiLightGroup::getSpotlightPenumbraAngle(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getSpotlightPenumbraAngle(idx);
}

inline
Real32 MultiLightGroup::getSpotlightPenumbraFactor(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getSpotlightPenumbraFactor(idx);
}

inline
Real32 MultiLightGroup::getInnerSuperEllipsesWidth(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getInnerSuperEllipsesWidth(idx);
}

inline
Real32 MultiLightGroup::getInnerSuperEllipsesHeight(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getInnerSuperEllipsesHeight(idx);
}

inline
Real32 MultiLightGroup::getOuterSuperEllipsesWidth(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getOuterSuperEllipsesWidth(idx);
}

inline
Real32 MultiLightGroup::getOuterSuperEllipsesHeight(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getOuterSuperEllipsesHeight(idx);
}

inline
Real32 MultiLightGroup::getSuperEllipsesRoundness(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getSuperEllipsesRoundness(idx);
}

inline
Real32 MultiLightGroup::getSuperEllipsesTwist(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getSuperEllipsesTwist(idx);
}

inline
Real32 MultiLightGroup::getRangeCutOn(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getRangeCutOn(idx);
}

inline
Real32 MultiLightGroup::getRangeCutOff(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getRangeCutOff(idx);
}

inline
Real32 MultiLightGroup::getRangeNearZone(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getRangeNearZone(idx);
}

inline
Real32 MultiLightGroup::getRangeFarZone(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getRangeFarZone(idx);
}

inline
MultiLight::TypeOfLight MultiLightGroup::getTypeOfLight(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getTypeOfLight(idx);
}

inline
bool MultiLightGroup::getEnabled(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getEnabled(idx);
}

inline
bool MultiLightGroup::getShadow(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getShadow(idx);
}

inline
Int32 MultiLightGroup::getShadowDataIndex(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getShadowDataIndex(idx);
}

inline
Int32 MultiLightGroup::getShadowParameterIndex(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getShadowParameterIndex(idx);
}

inline
Node* MultiLightGroup::getBeacon(const UInt32 idx) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getBeacon(idx);
}

inline
void MultiLightGroup::setPosition(const UInt32 idx, const Pnt3f& position)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setPosition(idx, position);
}

inline
void MultiLightGroup::setDirection(const UInt32 idx, const Vec3f& direction)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setDirection(idx, direction);
}

inline
void MultiLightGroup::setIntensity(const UInt32 idx, const Vec3f& intensity)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setIntensity(idx, intensity);
}

inline
void MultiLightGroup::setIntensity(const UInt32 idx, const Color3f& color)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setIntensity(idx, color);
}

inline
void MultiLightGroup::setIntensity(const UInt32 idx, Real32 red, Real32 green, Real32 blue)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setIntensity(idx, red, green, blue);
}

inline
void MultiLightGroup::setAmbient(const UInt32 idx, const Vec3f& intensity)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setAmbient(idx, intensity);
}

inline
void MultiLightGroup::setAmbient(const UInt32 idx, const Color3f& color)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setAmbient(idx, color);
}

inline
void MultiLightGroup::setAmbient(const UInt32 idx, Real32 red, Real32 green, Real32 blue)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setAmbient(idx, red, green, blue);
}

inline
void MultiLightGroup::setDiffuse(const UInt32 idx, const Vec3f& intensity)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setDiffuse(idx, intensity);
}

inline
void MultiLightGroup::setDiffuse(const UInt32 idx, const Color3f& color)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setDiffuse(idx, color);
}

inline
void MultiLightGroup::setDiffuse(const UInt32 idx, Real32 red, Real32 green, Real32 blue)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setDiffuse(idx, red, green, blue);
}

inline
void MultiLightGroup::setSpecular(const UInt32 idx, const Vec3f& intensity)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setSpecular(idx, intensity);
}

inline
void MultiLightGroup::setSpecular(const UInt32 idx, const Color3f& color)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setSpecular(idx, color);
}

inline
void MultiLightGroup::setSpecular(const UInt32 idx, Real32 red, Real32 green, Real32 blue)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setSpecular(idx, red, green, blue);
}

inline
void MultiLightGroup::setAttenuation(const UInt32 idx, const Vec3f& attenuation)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setAttenuation(idx, attenuation);
}

inline
void MultiLightGroup::setDecayAttenuation(const UInt32 idx, Real32 decayAttenuation)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setDecayAttenuation(idx, decayAttenuation);
}

inline
void MultiLightGroup::setLengthFactor(const UInt32 idx, Real32 lengthFactor)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setLengthFactor(idx, lengthFactor);
}

inline
void MultiLightGroup::setRange(const UInt32 idx, Real32 range)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setRange(idx, range);
}

inline
void MultiLightGroup::setSpotlightAngle(const UInt32 idx, Real32 angle)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setSpotlightAngle(idx, angle);
}

inline
void MultiLightGroup::setSpotlightParameter(const UInt32 idx, Real32 value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setSpotlightParameter(idx, value);
}

inline
void MultiLightGroup::setSpotlightExponent(const UInt32 idx, Real32 exponent)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setSpotlightExponent(idx, exponent);
}

inline
void MultiLightGroup::setSpotlightPenumbraAngle(const UInt32 idx, Real32 angle)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setSpotlightPenumbraAngle(idx, angle);
}

inline
void MultiLightGroup::setSpotlightPenumbraFactor(const UInt32 idx, Real32 factor)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setSpotlightPenumbraFactor(idx, factor);
}

inline
void MultiLightGroup::setInnerSuperEllipsesWidth(const UInt32 idx, Real32 width)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setInnerSuperEllipsesWidth(idx, width);
}

inline
void MultiLightGroup::setInnerSuperEllipsesHeight(const UInt32 idx, Real32 height)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setInnerSuperEllipsesHeight(idx, height);
}

inline
void MultiLightGroup::setOuterSuperEllipsesWidth(const UInt32 idx, Real32 width)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setOuterSuperEllipsesWidth(idx, width);
}

inline
void MultiLightGroup::setOuterSuperEllipsesHeight(const UInt32 idx, Real32 height)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setOuterSuperEllipsesHeight(idx, height);
}

inline
void MultiLightGroup::setSuperEllipsesRoundness(const UInt32 idx, Real32 roundness)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setSuperEllipsesRoundness(idx, roundness);
}

inline
void MultiLightGroup::setSuperEllipsesTwist(const UInt32 idx, Real32 twist)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setSuperEllipsesTwist(idx, twist);
}

inline
void MultiLightGroup::setRangeCutOn(const UInt32 idx, Real32 cutOn)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setRangeCutOn(idx, cutOn);
}

inline
void MultiLightGroup::setRangeCutOff(const UInt32 idx, Real32 cutOff)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setRangeCutOff(idx, cutOff);
}

inline
void MultiLightGroup::setRangeNearZone(const UInt32 idx, Real32 nearZone)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setRangeNearZone(idx, nearZone);
}

inline
void MultiLightGroup::setRangeFarZone(const UInt32 idx, Real32 farZone)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setRangeFarZone(idx, farZone);
}

inline
void MultiLightGroup::setTypeOfLight(const UInt32 idx, MultiLight::TypeOfLight eTypeOfLight)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setTypeOfLight(idx, eTypeOfLight);
}

inline
void MultiLightGroup::setEnabled(const UInt32 idx, bool flag)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setEnabled(idx, flag);
}

inline
void MultiLightGroup::setShadow(const UInt32 idx, bool flag)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setShadow(idx, flag);
}

inline
void MultiLightGroup::setShadowDataIndex(const UInt32 idx, Int32 shadowDataIndex)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setShadowDataIndex(idx, shadowDataIndex);
}

inline
void MultiLightGroup::setShadowParameterIndex(const UInt32 idx, Int32 shadowParameterIndex)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setShadowParameterIndex(idx, shadowParameterIndex);
}

inline
void MultiLightGroup::setBeacon(const UInt32 idx, Node* const beacon)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setBeacon(idx, beacon);
}

inline
void MultiLightGroup::changedBeacon()
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->changedBeacon();
}

inline
std::string MultiLightGroup::getFragmentProgramSnippet(bool add_attenuation_code, bool add_ubo_code) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getFragmentProgramSnippet(add_attenuation_code, add_ubo_code);
}

inline
std::string MultiLightGroup::getLightUBOProgSnippet() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getLightUBOProgSnippet();
}

inline
std::string MultiLightGroup::getAttenuationProgSnippet() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getAttenuationProgSnippet();
}

inline
bool MultiLightGroup::getHasLightSpaceFromWorldSpaceMatrix() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasLightSpaceFromWorldSpaceMatrix();
}

inline
bool MultiLightGroup::getHasWorldSpaceFromLightSpaceMatrix() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasWorldSpaceFromLightSpaceMatrix();
}

inline
bool MultiLightGroup::getHasLightSpaceFromEyeSpaceMatrix() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasLightSpaceFromEyeSpaceMatrix();
}

inline
bool MultiLightGroup::getHasEyeSpaceFromLightSpaceMatrix() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasEyeSpaceFromLightSpaceMatrix();
}

inline
bool MultiLightGroup::getHasProjectionMatrix() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasProjectionMatrix();
}

inline
bool MultiLightGroup::getHasInvProjectionMatrix() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasInvProjectionMatrix();
}

inline
bool MultiLightGroup::getHasProjectionLightSpaceFromWorldSpaceMatrix() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasProjectionLightSpaceFromWorldSpaceMatrix();
}

inline
bool MultiLightGroup::getHasInvProjectionLightSpaceFromWorldSpaceMatrix() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasInvProjectionLightSpaceFromWorldSpaceMatrix();
}

inline
bool MultiLightGroup::getHasProjectionLightSpaceFromEyeSpaceMatrix() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasProjectionLightSpaceFromEyeSpaceMatrix();
}

inline
bool MultiLightGroup::getHasInvProjectionLightSpaceFromEyeSpaceMatrix() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasInvProjectionLightSpaceFromEyeSpaceMatrix();
}

inline
bool MultiLightGroup::getHasIntensity() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasIntensity();
}

inline
bool MultiLightGroup::getHasSeparateIntensities() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasSeparateIntensities();
}

inline
bool MultiLightGroup::getHasAttenuation() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasAttenuation();
}

inline
bool MultiLightGroup::getHasDecayAttenuation() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasDecayAttenuation();
}

inline
bool MultiLightGroup::getHasLengthFactor() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasLengthFactor();
}

inline
bool MultiLightGroup::getHasRangeCutOn() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasRangeCutOn();
}

inline
bool MultiLightGroup::getHasRangeCutOff() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasRangeCutOff();
}

inline
bool MultiLightGroup::getHasRangeNearZone() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasRangeNearZone();
}

inline
bool MultiLightGroup::getHasRangeFarZone() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasRangeFarZone();
}

inline
bool MultiLightGroup::getHasSpotlightAngle() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasSpotlightAngle();
}

inline
bool MultiLightGroup::getHasCosSpotlightAngle() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasCosSpotlightAngle();
}

inline
bool MultiLightGroup::getHasTanSpotlightAngle() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasTanSpotlightAngle();
}

inline
bool MultiLightGroup::getHasSpotlightExponent() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasSpotlightExponent();
}

inline
bool MultiLightGroup::getHasSpotlightPenumbraAngle() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasSpotlightPenumbraAngle();
}

inline
bool MultiLightGroup::getHasSpotlightPenumbraFactor() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasSpotlightPenumbraFactor();
}

inline
bool MultiLightGroup::getHasSpotlightPenumbraFrostbite() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasSpotlightPenumbraFrostbite();
}

inline
bool MultiLightGroup::getHasCinemaLight() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasCinemaLight();
}

inline
bool MultiLightGroup::getHasShadow() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasShadow();
}

inline
bool MultiLightGroup::getHasProjection() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasProjection();
}

inline
bool MultiLightGroup::getHasGlobalAmbientIntensity() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasGlobalAmbientIntensity();
}

inline
bool MultiLightGroup::getAutoCalcRanges() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getAutoCalcRanges();
}

inline
bool MultiLightGroup::getEyeSpace() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getEyeSpace();
}

inline
bool MultiLightGroup::getHasGlobalState() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getHasGlobalState();
}

inline
void MultiLightGroup::setHasLightSpaceFromWorldSpaceMatrix(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasLightSpaceFromWorldSpaceMatrix(value);
}

inline
void MultiLightGroup::setHasWorldSpaceFromLightSpaceMatrix(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasWorldSpaceFromLightSpaceMatrix(value);
}

inline
void MultiLightGroup::setHasLightSpaceFromEyeSpaceMatrix(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasLightSpaceFromEyeSpaceMatrix(value);
}

inline
void MultiLightGroup::setHasEyeSpaceFromLightSpaceMatrix(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasEyeSpaceFromLightSpaceMatrix(value);
}

inline
void MultiLightGroup::setHasProjectionMatrix(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasProjectionMatrix(value);
}

inline
void MultiLightGroup::setHasInvProjectionMatrix(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasInvProjectionMatrix(value);
}

inline
void MultiLightGroup::setHasProjectionLightSpaceFromWorldSpaceMatrix(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasProjectionLightSpaceFromWorldSpaceMatrix(value);
}

inline
void MultiLightGroup::setHasInvProjectionLightSpaceFromWorldSpaceMatrix(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasInvProjectionLightSpaceFromWorldSpaceMatrix(value);
}

inline
void MultiLightGroup::setHasProjectionLightSpaceFromEyeSpaceMatrix(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasProjectionLightSpaceFromEyeSpaceMatrix(value);
}

inline
void MultiLightGroup::setHasInvProjectionLightSpaceFromEyeSpaceMatrix(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasInvProjectionLightSpaceFromEyeSpaceMatrix(value);
}

inline
void MultiLightGroup::setHasIntensity(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasIntensity(value);
}

inline
void MultiLightGroup::setHasSeparateIntensities(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasSeparateIntensities(value);
}

inline
void MultiLightGroup::setHasAttenuation(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasAttenuation(value);
}

inline
void MultiLightGroup::setHasDecayAttenuation(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasDecayAttenuation(value);
}

inline
void MultiLightGroup::setHasLengthFactor(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasLengthFactor(value);
}

inline
void MultiLightGroup::setHasRangeCutOn(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasRangeCutOn(value);
}

inline
void MultiLightGroup::setHasRangeCutOff(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasRangeCutOff(value);
}

inline
void MultiLightGroup::setHasRangeNearZone(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasRangeNearZone(value);
}

inline
void MultiLightGroup::setHasRangeFarZone(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasRangeFarZone(value);
}

inline
void MultiLightGroup::setHasSpotlightAngle(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasSpotlightAngle(value);
}

inline
void MultiLightGroup::setHasCosSpotlightAngle(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasCosSpotlightAngle(value);
}

inline
void MultiLightGroup::setHasTanSpotlightAngle(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasTanSpotlightAngle(value);
}

inline
void MultiLightGroup::setHasSpotlightExponent(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasSpotlightExponent(value);
}

inline
void MultiLightGroup::setHasSpotlightPenumbraAngle(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasSpotlightPenumbraAngle(value);
}

inline
void MultiLightGroup::setHasSpotlightPenumbraFactor(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasSpotlightPenumbraFactor(value);
}

inline
void MultiLightGroup::setHasSpotlightPenumbraFrostbite(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasSpotlightPenumbraFrostbite(value);
}

inline
void MultiLightGroup::setHasCinemaLight(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasCinemaLight(value);
}

inline
void MultiLightGroup::setHasShadow(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasShadow(value);
}

inline
void MultiLightGroup::setHasProjection(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasProjection(value);
}

inline
void MultiLightGroup::setHasGlobalAmbientIntensity(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setHasGlobalAmbientIntensity(value);
}

inline
void MultiLightGroup::setAutoCalcRanges(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setAutoCalcRanges(value);
}

inline
void MultiLightGroup::setEyeSpace(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setEyeSpace(value);
}

inline
bool MultiLightGroup::checkFeatures(UInt32 features) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->checkFeatures(features);
}

inline
void MultiLightGroup::setFeatures(UInt32 features, bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setFeatures(features, value);
}

inline
bool MultiLightGroup::getCodeDistanceAttenuationClassic() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getCodeDistanceAttenuationClassic();
}

inline
bool MultiLightGroup::getCodeDistanceAttenuationPhysical() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getCodeDistanceAttenuationPhysical();
}

inline
bool MultiLightGroup::getCodeDistanceAttenuationDecay() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getCodeDistanceAttenuationDecay();
}

inline
bool MultiLightGroup::getCodeDistanceAttenuationMixPhysical() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getCodeDistanceAttenuationMixPhysical();
}

inline
bool MultiLightGroup::getCodeDistanceAttenuationMixDecay() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getCodeDistanceAttenuationMixDecay();
}

inline
bool MultiLightGroup::getCodeDistanceAttenuationSmoothHermite() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getCodeDistanceAttenuationSmoothHermite();
}

inline
bool MultiLightGroup::getCodeSpotAttenuationClassic() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getCodeSpotAttenuationClassic();
}

inline
bool MultiLightGroup::getCodeSpotAttenuationSmoothHermite() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getCodeSpotAttenuationSmoothHermite();
}

inline
bool MultiLightGroup::getCodeSpotAttenuationSmoothHermite2() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getCodeSpotAttenuationSmoothHermite2();
}

inline
bool MultiLightGroup::getCodeSpotAttenuationFrostbite() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getCodeSpotAttenuationFrostbite();
}

inline
void MultiLightGroup::setCodeDistanceAttenuationClassic(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setCodeDistanceAttenuationClassic(value);
}

inline
void MultiLightGroup::setCodeDistanceAttenuationPhysical(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setCodeDistanceAttenuationPhysical(value);
}

inline
void MultiLightGroup::setCodeDistanceAttenuationDecay(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setCodeDistanceAttenuationDecay(value);
}

inline
void MultiLightGroup::setCodeDistanceAttenuationMixPhysical(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setCodeDistanceAttenuationMixPhysical(value);
}

inline
void MultiLightGroup::setCodeDistanceAttenuationMixDecay(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setCodeDistanceAttenuationMixDecay(value);
}

inline
void MultiLightGroup::setCodeDistanceAttenuationSmoothHermite(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setCodeDistanceAttenuationSmoothHermite(value);
}

inline
void MultiLightGroup::setCodeSpotAttenuationClassic(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setCodeSpotAttenuationClassic(value);
}

inline
void MultiLightGroup::setCodeSpotAttenuationSmoothHermite(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setCodeSpotAttenuationSmoothHermite(value);
}

inline
void MultiLightGroup::setCodeSpotAttenuationSmoothHermite2(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setCodeSpotAttenuationSmoothHermite2(value);
}

inline
void MultiLightGroup::setCodeSpotAttenuationFrostbite(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setCodeSpotAttenuationFrostbite(value);
}

inline
bool MultiLightGroup::checkCodeFeatures(UInt32 features) const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->checkCodeFeatures(features);
}

inline
void MultiLightGroup::setCodeFeatures(UInt32 features, bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setCodeFeatures(features, value);
}

inline
bool MultiLightGroup::getNormalizeDirection() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getNormalizeDirection();
}

inline
GLenum MultiLightGroup::getUsage() const
{
    const MultiLightChunk* pChunk = getChunk();
    return pChunk->getUsage();
}

inline
void MultiLightGroup::setNormalizeDirection(bool value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setNormalizeDirection(value);
}

inline
void MultiLightGroup::setUsage(const GLenum &value)
{
    MultiLightChunk* pChunk = getChunk();
    pChunk->setUsage(value);
}

OSG_END_NAMESPACE
