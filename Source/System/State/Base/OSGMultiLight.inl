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
const Pnt3f& MultiLight::getPosition() const
{
    return _position;
}

inline
const Vec3f& MultiLight::getDirection() const
{
    return _direction;
}

inline
const Vec3f& MultiLight::getIntensity() const
{
    return _intensity;
}

inline
const Vec3f& MultiLight::getAmbient() const
{
    return _ambientIntensity;
}

inline
const Vec3f& MultiLight::getDiffuse() const
{
    return _diffuseIntensity;
}

inline
const Vec3f& MultiLight::getSpecular() const
{
    return _specularIntensity;
}

inline
const Vec3f& MultiLight::getAttenuation() const
{
    return _attenuation;
}

inline
Real32 MultiLight::getDecayAttenuation() const
{
    return _decayAttenuation;
}

inline
Real32 MultiLight::getLengthFactor() const
{
    return _lengthFactor;
}

inline
Real32 MultiLight::getRange() const
{
    return _rangeCutOff;
}

inline
Real32 MultiLight::getSpotlightAngle() const
{
    return _spotlightAngle;
}

inline
Real32 MultiLight::getSpotlightParameter() const
{
    return _spotlightParameter;
}

inline
Real32 MultiLight::getSpotlightExponent() const
{
    return _spotlightParameter;
}

inline
Real32 MultiLight::getSpotlightPenumbraAngle() const
{
    return _spotlightParameter;
}

inline
Real32 MultiLight::getSpotlightPenumbraFactor() const
{
    return _spotlightParameter;
}

inline
Real32 MultiLight::getInnerSuperEllipsesWidth() const
{
    return _innerSuperEllipsesWidth;
}

inline
Real32 MultiLight::getInnerSuperEllipsesHeight() const
{
    return _innerSuperEllipsesHeight;
}

inline
Real32 MultiLight::getOuterSuperEllipsesWidth() const
{
    return _outerSuperEllipsesWidth;
}

inline
Real32 MultiLight::getOuterSuperEllipsesHeight() const
{
    return _outerSuperEllipsesHeight;
}

inline
Real32 MultiLight::getSuperEllipsesRoundness() const
{
    return _superEllipsesRoundness;
}

inline
Real32 MultiLight::getSuperEllipsesTwist() const
{
    return _superEllipsesTwist;
}

inline
Real32 MultiLight::getRangeCutOn() const
{
    return _rangeCutOn;
}

inline
Real32 MultiLight::getRangeCutOff() const
{
    return _rangeCutOff;
}

inline
Real32 MultiLight::getRangeNearZone() const
{
    return _rangeNearZone;
}

inline
Real32 MultiLight::getRangeFarZone() const
{
    return _rangeFarZone;
}

inline
const Matrix& MultiLight::getProjectionMatrix() const
{
    return _projectionMatrix;
}

inline
MultiLight::Type MultiLight::getType() const
{
    return _type;
}

inline
bool MultiLight::getEnabled() const
{
    return _enabled;
}

inline
bool MultiLight::getShadow() const
{
    return _shadow;
}

inline
Int32 MultiLight::getShadowDataIndex() const
{
    return _shadowDataIndex;
}

inline
Int32 MultiLight::getShadowParameterIndex() const
{
    return _shadowParameterIndex;
}

inline
Node* MultiLight::getBeacon() const
{
    return _beacon;
}

inline
void MultiLight::setPosition(const Pnt3f& position)
{
    _position = position;
}

inline
void MultiLight::setDirection(const Vec3f& direction)
{
    _direction = direction;
}

inline
void MultiLight::setIntensity(const Vec3f& intensity)
{
    _intensity = intensity;
}

inline
void MultiLight::setIntensity(const Color3f& color)
{
    _intensity = color;
}

inline
void MultiLight::setIntensity(Real32 red, Real32 green, Real32 blue)
{
    setIntensity(Vec3f(red, green, blue));
}

inline
void MultiLight::setAmbient(const Vec3f& intensity)
{
    _ambientIntensity = intensity;
}

inline
void MultiLight::setAmbient(const Color3f& color)
{
    _ambientIntensity = color;
}

inline
void MultiLight::setAmbient(Real32 red, Real32 green, Real32 blue)
{
    setAmbient(Vec3f(red, green, blue));
}

inline
void MultiLight::setDiffuse(const Vec3f& intensity)
{
    _diffuseIntensity = intensity;
}

inline
void MultiLight::setDiffuse(const Color3f& color)
{
    _diffuseIntensity = color;
}

inline
void MultiLight::setDiffuse(Real32 red, Real32 green, Real32 blue)
{
    setDiffuse(Vec3f(red, green, blue));
}

inline
void MultiLight::setSpecular(const Vec3f& intensity)
{
    _specularIntensity = intensity;
}

inline
void MultiLight::setSpecular(const Color3f& color)
{
    _specularIntensity = color;
}

inline
void MultiLight::setSpecular(Real32 red, Real32 green, Real32 blue)
{
    setSpecular(Vec3f(red, green, blue));
}

inline
void MultiLight::setAttenuation(const Vec3f& attenuation)
{
    _attenuation = attenuation;
}

inline
void MultiLight::setDecayAttenuation(Real32 decayAttenuation)
{
    _decayAttenuation = decayAttenuation;
}

inline
void MultiLight::setLengthFactor(Real32 lengthFactor)
{
    _lengthFactor = lengthFactor;
}

inline
void MultiLight::setRange(Real32 range)
{
    _rangeCutOff = range;
}

inline
void MultiLight::setSpotlightAngle(Real32 angle)
{
    _spotlightAngle = angle;
}

inline
void MultiLight::setSpotlightParameter(Real32 value)
{
    _spotlightParameter = value;
}

inline
void MultiLight::setSpotlightExponent(Real32 exponent)
{
    _spotlightParameter = exponent;
}

inline
void MultiLight::setSpotlightPenumbraAngle(Real32 angle)
{
    _spotlightParameter = angle;
}

inline
void MultiLight::setSpotlightPenumbraFactor(Real32 factor)
{
    _spotlightParameter = factor;
}

inline
void MultiLight::setInnerSuperEllipsesWidth(Real32 width)
{
    _innerSuperEllipsesWidth = width;
}

inline
void MultiLight::setInnerSuperEllipsesHeight(Real32 height)
{
    _innerSuperEllipsesHeight = height;
}

inline
void MultiLight::setOuterSuperEllipsesWidth(Real32 width)
{
    _outerSuperEllipsesWidth = width;
}

inline
void MultiLight::setOuterSuperEllipsesHeight(Real32 height)
{
    _outerSuperEllipsesHeight = height;
}

inline
void MultiLight::setSuperEllipsesRoundness(Real32 roundness)
{
    _superEllipsesRoundness = roundness;
}

inline
void MultiLight::setSuperEllipsesTwist(Real32 twist)
{
    _superEllipsesTwist = twist;
}

inline
void MultiLight::setRangeCutOn(Real32 cutOn)
{
    _rangeCutOn = cutOn;
}

inline
void MultiLight::setRangeCutOff(Real32 cutOff)
{
    _rangeCutOff = cutOff;
}

inline
void MultiLight::setRangeNearZone(Real32 nearZone)
{
    _rangeNearZone = nearZone;
}

inline
void MultiLight::setRangeFarZone(Real32 farZone)
{
    _rangeFarZone = farZone;
}

inline
void MultiLight::setProjectionMatrix(const Matrix& projectionMatrix)
{
    _projectionMatrix = projectionMatrix;
}

inline
void MultiLight::setType(MultiLight::Type eType)
{
    _type = eType;
}

inline
void MultiLight::setEnabled(bool flag)
{
    _enabled = flag;
}

inline
void MultiLight::setShadow(bool flag)
{
    _shadow = flag;
}

inline
void MultiLight::setShadowDataIndex(Int32 shadowDataIndex)
{
    _shadowDataIndex = shadowDataIndex;
}

inline
void MultiLight::setShadowParameterIndex(Int32 shadowParameterIndex)
{
    _shadowParameterIndex = shadowParameterIndex;
}

inline
void MultiLight::setBeacon(Node* const beacon)
{
    _beacon = beacon;
}

OSG_END_NAMESPACE
