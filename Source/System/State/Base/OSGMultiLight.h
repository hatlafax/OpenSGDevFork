/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#ifndef _OSGMULTILIGHT_H_
#define _OSGMULTILIGHT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGBaseTypes.h"
#include "OSGColor.h"
#include "OSGNode.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEM_DLLMAPPING  MultiLight
{
public:
    enum Type
    {
        POINT_LIGHT = 1,
        DIRECTIONAL_LIGHT = 2,
        SPOT_LIGHT = 3,
        CINEMA_LIGHT = 4
    };

    enum Layout {
         SIMPLE_LAYOUT = 0x01,  // Intensity,RangeCutOff
          RANGE_LAYOUT = 0x02,  // RangeCutOn, RangeCutOff
           ZONE_LAYOUT = 0x04,  // RangeNearZone, RangeFarZone
         OPENGL_LAYOUT = 0x08,  // Ambient-, Diffuse-, Specular Intensity, Attenuation, Spotlight-Exponent
         CINEMA_LAYOUT = 0x10,  // SuperEllipses
         SHADOW_LAYOUT = 0x20,  // Shadow
         GLOBAL_LAYOUT = 0x40,  // Global ambient color
       PHYSICAL_LAYOUT = 0x80   // Global ambient color, Intensity, RangeCutOn, RangeCutOff, Attenuation, Spotlight-Exponent, Shadow
    };

    enum Feature
    {
        HAS_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX                 = 0x00000001,
        HAS_WORLD_SPACE_FROM_LIGHT_SPACE_MATRIX                 = 0x00000002,
        HAS_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX                   = 0x00000004,
        HAS_EYE_SPACE_FROM_LIGHT_SPACE_MATRIX                   = 0x00000008,
        HAS_PROJECTION_MATRIX                                   = 0x00000010,
        HAS_INV_PROJECTION_MATRIX                               = 0x00000020,
        HAS_PROJECTION_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX      = 0x00000040,
        HAS_INV_PROJECTION_LIGHT_SPACE_FROM_WORLD_SPACE_MATRIX  = 0x00000080,
        HAS_PROJECTION_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX        = 0x00000100,
        HAS_INV_PROJECTION_LIGHT_SPACE_FROM_EYE_SPACE_MATRIX    = 0x00000200,
        HAS_INTENSITY                                           = 0x00000400,
        HAS_SEPARATE_INTENSITIES                                = 0x00000800,
        HAS_ATTENUATION                                         = 0x00001000,
        HAS_RANGE_CUT_ON                                        = 0x00002000,
        HAS_RANGE_CUT_OFF                                       = 0x00004000,
        HAS_RANGE_NEAR_ZONE                                     = 0x00008000,
        HAS_RANGE_FAR_ZONE                                      = 0x00010000,
        HAS_COS_SPOTLIGHT_ANGLE                                 = 0x00020000,
        HAS_TAN_SPOTLIGHT_ANGLE                                 = 0x00040000,
        HAS_SPOTLIGHT_ANGLE                                     = 0x00080000,
        HAS_SPOTLIGHT_EXPONENT                                  = 0x00100000,
        HAS_SPOTLIGHT_PENUMBRA_ANGLE                            = 0x00200000,
        HAS_SPOTLIGHT_PENUMBRA_FACTOR                           = 0x00400000,
        HAS_SPOTLIGHT_PENUMBRA_FROSTBITE                        = 0x00800000,
        HAS_CINEMA_LIGHT                                        = 0x01000000,
        HAS_SHADOW                                              = 0x02000000,
        HAS_PROJECTION                                          = 0x04000000,
        HAS_GLOBAL_AMBIENT_INTENSITY                            = 0x08000000,
        AUTO_CALC_RANGES                                        = 0x10000000,
        HAS_DECAY_ATTENUATION                                   = 0x20000000,
        HAS_LENGTH_FACTOR                                       = 0x40000000,
        EYE_SPACE                                               = 0x80000000,
    };

    enum CodeFeature {
        CODE_DISTANCE_ATTENUATION_CLASSIC                       = 0x00000001,
        CODE_DISTANCE_ATTENUATION_PHYSICAL                      = 0x00000002,
        CODE_DISTANCE_ATTENUATION_DECAY                         = 0x00000004,
        CODE_DISTANCE_ATTENUATION_SMOOTH_HERMITE                = 0x00000008,
        CODE_DISTANCE_ATTENUATION_MIX_PHYSICAL                  = 0x00000010,
        CODE_DISTANCE_ATTENUATION_MIX_DECAY                     = 0x00000020,
        CODE_SPOT_ATTENUATION_CLASSIC                           = 0x00000100,
        CODE_SPOT_ATTENUATION_SMOOTH_HERMITE                    = 0x00000200,
        CODE_SPOT_ATTENUATION_SMOOTH_HERMITE_2                  = 0x00000400,
        CODE_SPOT_ATTENUATION_FROSTBITE                         = 0x00000800,
    };

public:
    const Pnt3f&               getPosition                      () const;
    const Vec3f&               getDirection                     () const;
    const Vec3f&               getIntensity                     () const;
    const Vec3f&               getAmbient                       () const;
    const Vec3f&               getDiffuse                       () const;
    const Vec3f&               getSpecular                      () const;
    const Vec3f&               getAttenuation                   () const;
          Real32               getDecayAttenuation              () const;
          Real32               getLengthFactor                  () const;
          Real32               getRange                         () const;
          Real32               getSpotlightAngle                () const;
          Real32               getSpotlightParameter            () const;
          Real32               getSpotlightExponent             () const;
          Real32               getSpotlightPenumbraAngle        () const;
          Real32               getSpotlightPenumbraFactor       () const;
          Real32               getInnerSuperEllipsesWidth       () const;
          Real32               getInnerSuperEllipsesHeight      () const;
          Real32               getOuterSuperEllipsesWidth       () const;
          Real32               getOuterSuperEllipsesHeight      () const;
          Real32               getSuperEllipsesRoundness        () const;
          Real32               getSuperEllipsesTwist            () const;
          Real32               getRangeCutOn                    () const;
          Real32               getRangeCutOff                   () const;
          Real32               getRangeNearZone                 () const;
          Real32               getRangeFarZone                  () const;
    const Matrix&              getProjectionMatrix              () const;
          Type                 getType                          () const;
          bool                 getEnabled                       () const;
          bool                 getShadow                        () const;
          Int32                getShadowDataIndex               () const;
          Int32                getShadowParameterIndex          () const;
          Node*                getBeacon                        () const;

          void                 setPosition                      (const Pnt3f& position);
          void                 setDirection                     (const Vec3f& direction);
          void                 setIntensity                     (const Vec3f& intensity);
          void                 setIntensity                     (const Color3f& color);
          void                 setIntensity                     (Real32 red, Real32 green, Real32 blue);
          void                 setAmbient                       (const Vec3f& intensity);
          void                 setAmbient                       (Real32 red, Real32 green, Real32 blue);
          void                 setAmbient                       (const Color3f& color);
          void                 setDiffuse                       (const Vec3f& intensity);
          void                 setDiffuse                       (Real32 red, Real32 green, Real32 blue);
          void                 setDiffuse                       (const Color3f& color);
          void                 setSpecular                      (const Vec3f& intensity);
          void                 setSpecular                      (Real32 red, Real32 green, Real32 blue);
          void                 setSpecular                      (const Color3f& color);
          void                 setAttenuation                   (const Vec3f& attenuation);
          void                 setDecayAttenuation              (Real32 decayAttenuation);
          void                 setLengthFactor                  (Real32 lengthFactor);
          void                 setRange                         (Real32 range);
          void                 setSpotlightAngle                (Real32 angle);
          void                 setSpotlightParameter            (Real32 value);
          void                 setSpotlightExponent             (Real32 exponent);
          void                 setSpotlightPenumbraAngle        (Real32 angle);
          void                 setSpotlightPenumbraFactor       (Real32 factor);
          void                 setInnerSuperEllipsesWidth       (Real32 width);
          void                 setInnerSuperEllipsesHeight      (Real32 height);
          void                 setOuterSuperEllipsesWidth       (Real32 width);
          void                 setOuterSuperEllipsesHeight      (Real32 height);
          void                 setSuperEllipsesRoundness        (Real32 roundness);
          void                 setSuperEllipsesTwist            (Real32 twist);
          void                 setRangeCutOn                    (Real32 cutOn);
          void                 setRangeCutOff                   (Real32 cutOff);
          void                 setRangeNearZone                 (Real32 nearZone);
          void                 setRangeFarZone                  (Real32 farZone);
          void                 setProjectionMatrix              (const Matrix& projectionMatrix);
          void                 setType                          (Type eType);
          void                 setEnabled                       (bool flag);
          void                 setShadow                        (bool flag);
          void                 setShadowDataIndex               (Int32 shadowDataIndex);
          void                 setShadowParameterIndex          (Int32 shadowParameterIndex);
          void                 setBeacon                        (Node* const beacon);

    explicit MultiLight(Type e);

private:
    Pnt3f       _position;
    Vec3f       _direction;
    Vec3f       _intensity;
    Vec3f       _ambientIntensity;
    Vec3f       _diffuseIntensity;
    Vec3f       _specularIntensity;
    Vec3f       _attenuation;
    Real32      _decayAttenuation;
    Real32      _lengthFactor;
    Real32      _spotlightAngle;
    Real32      _spotlightParameter;
    Real32      _innerSuperEllipsesWidth;
    Real32      _innerSuperEllipsesHeight;
    Real32      _outerSuperEllipsesWidth;
    Real32      _outerSuperEllipsesHeight;
    Real32      _superEllipsesRoundness;
    Real32      _superEllipsesTwist;
    Real32      _rangeCutOn;
    Real32      _rangeCutOff;
    Real32      _rangeNearZone;
    Real32      _rangeFarZone;
    Matrix      _projectionMatrix;
    Type        _type;
    bool        _enabled;
    bool        _shadow;
    Int32       _shadowDataIndex;
    Int32       _shadowParameterIndex;
    NodeRefPtr  _beacon;
};

OSG_END_NAMESPACE

#include "OSGMultiLight.inl"

#endif /* _OSGMULTILIGHT_H_ */
