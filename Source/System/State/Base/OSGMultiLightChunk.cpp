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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <boost/bind/bind.hpp>

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGWindow.h"

#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"
#include "OSGQuaternion.h"

#include "OSGGLFuncProtos.h"
#include "OSGBaseFunctions.h"

#include "OSGDrawEnv.h"
#include "OSGNode.h"

#include "OSGMultiLightChunk.h"

//#define OSG_LOG_MULTILIGHT_SHADER_TEST_CODE

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMultiLightChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGMultiLightChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

typedef OSG::Window Win;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiLightChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MultiLightChunk::MultiLightChunk(void) :
    Inherited(),
    _bUpdateBuffer(true)
{
    //
    // Initialize the feature flags, because the flags are declared privately in the 
    // MultiLightChunk class and therefore unknown in the base ctor.
    //
    UInt32 feature = MultiLight::HAS_SEPARATE_INTENSITIES
                   | MultiLight::HAS_ATTENUATION
                   | MultiLight::AUTO_CALC_RANGES
                   | MultiLight::HAS_COS_SPOTLIGHT_ANGLE
                   | MultiLight::HAS_SPOTLIGHT_EXPONENT
                   ;
    _sfFeature.setValue(feature);
}

MultiLightChunk::MultiLightChunk(const MultiLightChunk &source) :
    Inherited(source),
    _bUpdateBuffer(true)
{
}

MultiLightChunk::~MultiLightChunk(void)
{
    clearLights();
}

/*----------------------------- class specific ----------------------------*/

void MultiLightChunk::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    BitVector whichFieldLocal = whichField;

    //
    // The BeaconMatrixFieldMask is deliberately omitted
    // 
    if((whichField & ( FeatureFieldMask |
                       GlobalAmbientIntensityFieldMask |
                       PositionFieldMask |
                       DirectionFieldMask |
                       IntensityFieldMask |
                       AmbientIntensityFieldMask |
                       DiffuseIntensityFieldMask |
                       SpecularIntensityFieldMask |
                       AttenuationFieldMask |
                       DecayAttenuationFieldMask |
                       LengthFactorFieldMask |
                       SpotlightAngleFieldMask |
                       SpotExponentFieldMask |
                       InnerSuperEllipsesWidthFieldMask |
                       InnerSuperEllipsesHeightFieldMask |
                       OuterSuperEllipsesWidthFieldMask |
                       OuterSuperEllipsesHeightFieldMask |
                       SuperEllipsesRoundnessFieldMask |
                       SuperEllipsesTwistFieldMask |
                       RangeCutOnFieldMask |
                       RangeCutOffFieldMask |
                       RangeNearZoneFieldMask |
                       RangeFarZoneFieldMask |
                       ProjectionMatrixFieldMask |
                       TypeOfLightFieldMask |
                       EnabledFieldMask |
                       ShadowFieldMask |
                       ShadowDataIndexFieldMask |
                       ShadowParameterIndexFieldMask |
                       BeaconFieldMask)) != 0)
    {
        _bUpdateBuffer = true;

        //
        // The update procedure is performed in the activate process. The parent's buffer is 
        // then modified in the activation process. In order to trigger the change we artificially
        // modify the change mask for the parent's buffer field.
        whichFieldLocal |= BufferFieldMask;
    }

    Inherited::changed(whichFieldLocal, origin, details);
}

/*----------------------------- onCreate --------------------------------*/

void MultiLightChunk::onCreate(const MultiLightChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;
}

void MultiLightChunk::onCreateAspect(
    const MultiLightChunk *createAspect,
    const MultiLightChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void MultiLightChunk::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);
}

/*------------------------------ Output -------------------------------------*/

void MultiLightChunk::dump(      UInt32    ,
                           const BitVector ) const
{
    SLOG << "Dump MultiLightChunk NI" << std::endl;
}

/*-------------------------- Draw Interface ---------------------------------*/

void MultiLightChunk::calcSpotAngle(
    UInt32 idx, 
    Real32& spotlightAngle,
    Real32& cosSpotlightAngle
    ) const
{
    spotlightAngle    = 0.f;
    cosSpotlightAngle = 1.f;

    switch (getTypeOfLight(idx))
    {
        case MultiLight::POINT_LIGHT:
            break;
        case MultiLight::DIRECTIONAL_LIGHT:
            break;
        case MultiLight::SPOT_LIGHT:
            {
                Real32 angleRad   = osgDegree2Rad(getSpotlightAngle(idx));
                cosSpotlightAngle = osgCos(angleRad);
                spotlightAngle    = angleRad;
            }
            break;
        case MultiLight::CINEMA_LIGHT:
            {
                Real32 s = osgMax(osgMax(getInnerSuperEllipsesWidth(idx), getInnerSuperEllipsesHeight(idx)),
                                  osgMax(getOuterSuperEllipsesWidth(idx), getOuterSuperEllipsesHeight(idx)));

                Real32 angleRad   = osgATan(s/1.f);
                cosSpotlightAngle = osgCos(angleRad);
                spotlightAngle    = angleRad;
            }
            break;
    }
}

void MultiLightChunk::calcFrustumZ(
    DrawEnv* pEnv,
    UInt32   idx,
    Real32&  zNear,
    Real32&  zFar) const
{
    Real32 cutOnRange, cutOffRange;

    //
    // ... we first get the user provided range values without
    // any attenuation based range calculation. ...
    //
    calcRange(pEnv, idx, false, cutOnRange, cutOffRange);

    zNear = cutOnRange;
    zFar  = cutOffRange;

    //
    // ... If the user did not set these values but the multi
    // light is driven in the mode that does provide these fields,
    // we fall back to the imperfect camera parameters due to lack
    // of any better information ...
    //
    if (zNear <= TypeTraits<OSG::Real32>::getDefaultEps())
    {
        Real32 camNear = pEnv->getCameraNear();
        zNear = osgMax(zNear, camNear);
    }
    if (zFar >= (TypeTraits<Real32>::getMax()-TypeTraits<OSG::Real32>::getDefaultEps()))
    {
        Real32 camFar = pEnv->getCameraFar();
        if (camFar > TypeTraits<OSG::Real32>::getDefaultEps())
        {
            zFar = camFar;
        }
    }

    //
    // ... Now, we get the attenuation based range values and try to
    // optimize the current zNear and zFar value.
    //
    calcRange(pEnv, idx, true, cutOnRange, cutOffRange);

    zNear = osgMax(cutOnRange,  zNear);
    zFar  = osgMin(cutOffRange, zFar);
}

void MultiLightChunk::calcRange(
    DrawEnv* pEnv,
    UInt32   idx,
    bool     attenuationAware,
    Real32&  cutOnRange,
    Real32&  cutOffRange) const
{
    switch (getTypeOfLight(idx))
    {
        case MultiLight::DIRECTIONAL_LIGHT:
            cutOnRange  = pEnv->getCameraNear();
            cutOffRange = pEnv->getCameraFar ();
            break;
        case MultiLight::POINT_LIGHT:
        case MultiLight::SPOT_LIGHT:
        case MultiLight::CINEMA_LIGHT:
            cutOnRange  = getHasRangeCutOn () ? getRangeCutOn (idx) : pEnv->getCameraNear();
            cutOffRange = getHasRangeCutOff() ? getRangeCutOff(idx) : pEnv->getCameraFar ();

            if (attenuationAware && getAutoCalcRanges())
            {
                const Real32 threshold = 0.001f;
                if (getHasAttenuation())
                {
                    calcPointLightRange(pEnv, getAttenuation(idx), threshold, cutOnRange, cutOffRange);
                }
                else if (getHasDecayAttenuation())
                {
                    calcPointLightRange(pEnv, getDecayAttenuation(idx), threshold, cutOnRange, cutOffRange);
                }
            }
            break;
    }
}

void MultiLightChunk::calcProjectionMatrix(
    MultiLight::TypeOfLight typeOfLight,
    Real32                  spotlightAngle,
    Real32                  zNear,
    Real32                  zFar,
    const Pnt3f&            lightMin,
    const Pnt3f&            lightMax,
    Matrix&                 matProjection) const
{
    switch (typeOfLight)
    {
        case MultiLight::POINT_LIGHT:
            MatrixPerspective(matProjection, Pi / 4.f, 1.f, zNear, zFar);
            break;
        case MultiLight::DIRECTIONAL_LIGHT:
            MatrixOrthogonal(matProjection, lightMin[0], lightMax[0], lightMin[1], lightMax[1], lightMin[2], lightMax[2]);
            break;
        case MultiLight::SPOT_LIGHT:
        case MultiLight::CINEMA_LIGHT:
            MatrixPerspective(matProjection, spotlightAngle, 1.f, zNear, zFar);
            break;
    }
}

/*------------------------------ buffer -------------------------------------*/

void MultiLightChunk::transformToWorldSpace(
    DrawEnv* pEnv,
    Node* beacon, 
    const Pnt3f& position_bs, 
    const Vec3f& direction_bs, 
    Pnt3f& position_ws, 
    Vec3f& direction_ws) const
{
    Matrix matWsFromBS;
    matWsFromBS.identity();

    if(beacon != NULL)
    {
        beacon->getToWorld(matWsFromBS);
    }
    else
    {
        matWsFromBS.setIdentity();
    }

    matWsFromBS.multFull( position_bs,  position_ws);
    matWsFromBS.multFull(direction_bs, direction_ws);
}

void MultiLightChunk::transformToEyeSpace(
    DrawEnv* pEnv,
    Node* beacon,
    const Pnt3f& position_bs,
    const Vec3f& direction_bs,
    Pnt3f& position_es,
    Vec3f& direction_es) const
{
    Matrix matWsFromBS;

    if(beacon != NULL)
    {
        beacon->getToWorld(matWsFromBS);
    }
    else
    {
        matWsFromBS.setIdentity();
    }

    Matrix mat = pEnv->getCameraViewing();  // matEsFromWs
    mat.mult(matWsFromBS);                  // matEsFromBs

    mat.multFull( position_bs,  position_es);
    mat.multFull(direction_bs, direction_es);
}

void MultiLightChunk::calcDirectionalLightMatrixLSFromWS(
    Node* beacon, 
    const Vec3f& direction_bs,
    Matrix& matLSFromWS) const
{
    if(beacon)
        beacon->getToWorld(matLSFromWS);    // matWsFromBS;

    Matrix     matLightDir;
    Quaternion rotLightDir(Vec3f(0.f, 0.f, 1.f), -direction_bs);
    matLightDir.setRotate(rotLightDir);

    matLSFromWS.mult        (matLightDir);
    matLSFromWS.invert      (           );  // WS -> LS
}

void MultiLightChunk::calcPointLightMatrixLSFromWS(
    Node* beacon, 
    const Pnt3f& position_bs, 
    Matrix& matLSFromWS) const
{
    if(beacon)
        beacon->getToWorld(matLSFromWS);    // matWsFromBS;

    Matrix matLightPos;
    matLightPos.setTranslate(position_bs);

    matLSFromWS.mult        (matLightPos);
    matLSFromWS.invert      (           );  // WS -> LS
}

void MultiLightChunk::calcSpotLightMatrixLSFromWS(
    Node* beacon, 
    const Pnt3f& position_bs, 
    const Vec3f& direction_bs, 
    Matrix& matLSFromWS) const
{
    if(beacon)
        beacon->getToWorld(matLSFromWS);    // matWsFromBS;

    Matrix matLightPos;
    matLightPos.setTranslate(position_bs);

    Matrix     matLightDir;
    Quaternion rotLightDir(Vec3f(0.f, 0.f, 1.f), -direction_bs);
    matLightDir.setRotate(rotLightDir);

    matLSFromWS.mult        (matLightPos);
    matLSFromWS.mult        (matLightDir);
    matLSFromWS.invert      (           );  // WS -> LS // matLSFromWS = [matWsFromBS * matLightPos * matLightDir]^-1;
}

//
// Calculate the light affecting range based on the attenuation and
// the provided cutOnRange and cutOffRange range values. The cutOffRange
// value is an upper limit for the calculation.
//
void MultiLightChunk::calcPointLightRange(
    DrawEnv*    pEnv,
    const Vec3f attenuation,
    Real32      threshold,
    Real32&     cutOnRange,
    Real32&     cutOffRange) const
{
    Real32 oldCutOnRange  = cutOnRange;
    Real32 oldCutOffRange = cutOffRange;

    Real32 q = attenuation[2];
    Real32 l = attenuation[1];
    Real32 c = attenuation[0];

    if (osgAbs(q) > TypeTraits<Real32>::getDefaultEps())
    {
        Real32 D = l*l - 4.f * q * (c - 1.f/threshold);

        if (D >= 0)
        {
            D = osgSqrt(D);

            Real32 r1 = - l + D / (2.f * q);
            Real32 r2 = - l - D / (2.f * q);

            if (r1 > 0.f && r2 > 0.f)
            {
                cutOffRange = osgMin(r1, r2);
            }
            else if (r1 > 0.f)
            {
                cutOffRange = r1;
            }
            else if (r2 > 0.f)
            {
                cutOffRange = r2;
            }
        }
    }
    else if(osgAbs(l) > TypeTraits<Real32>::getDefaultEps())
    {
        Real32 r = (1.f/threshold - c)/l;

        if (r > 0.f)
        {
            cutOffRange = r;
        }
    }

    cutOffRange = osgMin(oldCutOffRange, cutOffRange);

    if (cutOffRange <= cutOnRange)
        cutOffRange = cutOnRange + 1.f;
}

void MultiLightChunk::calcPointLightRange(
    DrawEnv*    pEnv,
    Real32      decayAttenuation,
    Real32      threshold,
    Real32&     cutOnRange,
    Real32&     cutOffRange) const
{
    Real32 oldCutOnRange  = cutOnRange;
    Real32 oldCutOffRange = cutOffRange;

    Real32 r = osgLog(1.f/threshold) / osgMax(0.0001f, decayAttenuation);
    r = osgExp(r);

    cutOffRange = osgMin(oldCutOffRange, r);

    if (cutOffRange <= cutOnRange)
        cutOffRange = cutOnRange + 1.f;
}

std::size_t MultiLightChunk::calcLightBufferSize() const
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    OSG_ASSERT(check_invariant());

    //struct GlobalLightState
    //{
    //    vec3  ambientIntensity;
    //};
    //
    //struct Light
    //{
    //    mat4  matLSFromWS;
    //    mat4  matWSFromLS;
    //    mat4  matLSFromES;
    //    mat4  matESFromLS;
    //    mat4  matProjection;
    //    mat4  matInvProjection;
    //    mat4  matProjLSFromWS;
    //    mat4  matInvProjLSFromWS;
    //    mat4  matProjLSFromES;
    //    mat4  matInvProjLSFromES;
    //    vec3  position;
    //    vec3  direction;
    //    vec3  color;
    //    vec3  ambientIntensity;
    //    vec3  diffuseIntensity;
    //    vec3  specularIntensity;
    //    float intensity;
    //    float constantAttenuation;
    //    float linearAttenuation;
    //    float quadraticAttenuation;
    //    float decayAttenuation;
    //    float lengthFactor;
    //    float rangeCutOn;
    //    float rangeCutOff;
    //    float rangeNearZone;
    //    float rangeFarZone;
    //    float cosSpotlightAngle;
    //    float spotlightAngle;
    //    float spotlightExponent;
    //    float cosSpotlightPenumbraAngle;
    //    float spotlightScale;
    //    float spotlightOffset;
    //    float innerSuperEllipsesWidth;
    //    float innerSuperEllipsesHeight;
    //    float outerSuperEllipsesWidth;
    //    float outerSuperEllipsesHeight;
    //    float superEllipsesRoundness;
    //    float superEllipsesTwist;
    //    int   type;
    //    bool  enabled;
    //    bool  shadow;
    //    int   shadowDataIndex;
    //    int   shadowParameterIndex;
    //};

    if (getHasGlobalAmbientIntensity())
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);          // Vec3f ambientIntensity
    }

    ao = alignOffset(16, bo); bo = ao;                              // padding    

    OSG::UInt32 numLights = osgMax(getNumLights(), 1U);             // We must create a disabled dummy light if no light is available

    for (UInt32 idx = 0; idx < numLights; ++idx)
    {
        if (getHasLightSpaceFromWorldSpaceMatrix())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);      // Matrix  matLSFromWS
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasWorldSpaceFromLightSpaceMatrix())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);      // Matrix  matWSFromLS
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasLightSpaceFromEyeSpaceMatrix())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);      // Matrix  matLSFromES
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasEyeSpaceFromLightSpaceMatrix())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);      // Matrix  matESFromLS
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasProjectionMatrix())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);      // Matrix  matProjection
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasInvProjectionMatrix())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);      // Matrix  matInvProjection
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasProjectionLightSpaceFromWorldSpaceMatrix())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);      // Matrix  matProjLSFromWS
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasInvProjectionLightSpaceFromWorldSpaceMatrix())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);      // Matrix  matInvProjLSFromWS
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasProjectionLightSpaceFromEyeSpaceMatrix())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);      // Matrix  matProjLSFromES
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasInvProjectionLightSpaceFromEyeSpaceMatrix())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);      // Matrix  matInvProjLSFromES
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        ao = alignOffset(16, bo); bo = ao + sizeof(Pnt3f);          // Pnt3f   position
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);          // Vec3f   direction

        if (getHasSeparateIntensities())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);      // Vec3f   ambientIntensity
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);      // Vec3f   diffuseIntensity
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);      // Vec3f   specularIntensity
        }

        if (getHasIntensity())
        {
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);      // Vec3f   intensity
        }

        if (getHasAttenuation())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  constantAttenuation
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  linearAttenuation
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  quadraticAttenuation
        }

        if (getHasDecayAttenuation())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  decayAttenuation
        }

        if (getHasLengthFactor())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  lengthFactor
        }

        if (getHasRangeCutOn())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  rangeCutOn
        }

        if (getHasRangeCutOff())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  rangeCutOff
        }

        if (getHasRangeNearZone())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  rangeNearZone
        }

        if (getHasRangeFarZone())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  rangeFarZone
        }

        if (getHasCosSpotlightAngle() || (!getHasCosSpotlightAngle() && !getHasSpotlightAngle()))
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  cosSpotlightAngle
        }

        if (getHasTanSpotlightAngle())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  tanSpotlightAngle
        }

        if (getHasSpotlightAngle())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  spotlightAngle
        }

        if (getHasSpotlightExponent())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  spotlightExponent
        }
        else
        if (getHasSpotlightPenumbraFrostbite())
        {
            if (getHasSpotlightPenumbraAngle() || getHasSpotlightPenumbraFactor())
            {
                ao = alignOffset( 4, bo); bo = ao + sizeof(Real32); // Real32  spotlightScale
                ao = alignOffset( 4, bo); bo = ao + sizeof(Real32); // Real32  spotlightOffset
            }
        }
        else
        if (getHasSpotlightPenumbraAngle())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  cosSpotlightPenumbraAngle
        }
        else
        if (getHasSpotlightPenumbraAngle())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  cosSpotlightPenumbraAngle
        }

        if (getHasCinemaLight())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  innerSuperEllipsesWidth
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  innerSuperEllipsesHeight
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  outerSuperEllipsesWidth
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  outerSuperEllipsesHeight
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  superEllipsesRoundness
            ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  superEllipsesTwist
        }

        ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);          // UInt8   typeOfLight
        ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);          // bool    enabled

        if (getHasShadow())
        {
            ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);      // bool    shadow
            ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);      // Int32   shadowDataIndex
            ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);      // Int32   shadowParameterIndex
        }

        ao = alignOffset(16, bo); bo = ao;                          // padding
    }

    ao = alignOffset(16, bo); bo = ao;                          // padding

    return ao;
}

std::vector<UInt8> MultiLightChunk::createLightBuffer(DrawEnv* pEnv) const
{
    std::size_t size = calcLightBufferSize();

    std::vector<UInt8> buffer(size, 0U);    // zero initialization ensures disabling of the dummy light
                                            // in case that no light is defined.

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    //struct GlobalLightState
    //{
    //    vec3  ambientIntensity;
    //};
    //

    if (getHasGlobalAmbientIntensity())
    {
        const Vec3f& intensity = getGlobalAmbientIntensity();
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &intensity[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);
    }

    ao = alignOffset(16, bo); bo = ao;                              // padding

    UInt32 num_lights = getNumLights();

    //struct Light
    //{
    //    mat4  matLSFromWS;
    //    mat4  matWSFromLS;
    //    mat4  matLSFromES;
    //    mat4  matESFromLS;
    //    mat4  matProjection;
    //    mat4  matInvProjection;
    //    mat4  matProjLSFromWS;
    //    mat4  matInvProjLSFromWS;
    //    mat4  matProjLSFromES;
    //    mat4  matInvProjLSFromES;
    //    vec3  position;
    //    vec3  direction;
    //    vec3  color;
    //    vec3  ambientIntensity;
    //    vec3  diffuseIntensity;
    //    vec3  specularIntensity;
    //    float intensity;
    //    float constantAttenuation;
    //    float linearAttenuation;
    //    float quadraticAttenuation;
    //    float decayAttenuation;
    //    float lengthFactor;
    //    float rangeCutOn;
    //    float rangeCutOff;
    //    float rangeNearZone;
    //    float rangeFarZone;
    //    float cosSpotlightAngle;
    //    float spotlightAngle;
    //    float spotlightExponent;
    //    float cosSpotlightPenumbraAngle;
    //    float spotlightScale;
    //    float spotlightOffset;
    //    float innerSuperEllipsesWidth;
    //    float innerSuperEllipsesHeight;
    //    float outerSuperEllipsesWidth;
    //    float outerSuperEllipsesHeight;
    //    float superEllipsesRoundness;
    //    float superEllipsesTwist;
    //    int   type;
    //    bool  enabled;
    //    bool  shadow;
    //    int   shadowDataIndex;
    //    int   shadowParameterIndex;
    //};

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
    std::stringstream ss;
    ss << std::endl;
    std::string start_token = "    << endl << \"    ";
    std::string   end_token = "\"";

    ss << start_token << "bool flag = true;" << end_token << std::endl;
    ss << start_token << end_token << std::endl;
    ss << start_token << "mat4  mVal;" << end_token << std::endl;
    ss << start_token << "vec3  vVal;" << end_token << std::endl;
    ss << start_token << "float fVal;" << end_token << std::endl;
    ss << start_token << "int   iVal;" << end_token << std::endl;
    ss << start_token << "bool  bVal;" << end_token << std::endl;
    ss << start_token << end_token << std::endl;
#endif

    for (UInt32 idx = 0; idx < num_lights; ++idx)
    {
        Real32 cosSpotlightAngle, spotlightAngle;
        calcSpotAngle(idx, spotlightAngle, cosSpotlightAngle);

        Real32 cutOnRange, cutOffRange;
        calcRange(pEnv, idx, true, cutOnRange, cutOffRange);

        Pnt3f position; Vec3f direction;
        calcPositionAndDirection(pEnv, idx, position, direction, getEyeSpace());

        if (getNormalizeDirection())
        {
            direction.normalize();
        }

        //
        // Test code to check matrices in the shader
        //
        // Matrix matTest(1,2,3,4,  5,6,7,8,  9,10,11,12,  13,14,15,16);

        Matrix matLSFromWS, matLSFromES;
        Matrix matWSFromLS, matESFromLS;

        if ( (
                getHasLightSpaceFromWorldSpaceMatrix()
             || getHasWorldSpaceFromLightSpaceMatrix()
             || getHasProjectionLightSpaceFromWorldSpaceMatrix()
             || getHasInvProjectionLightSpaceFromWorldSpaceMatrix() )
         && !(
                getHasLightSpaceFromEyeSpaceMatrix()
             || getHasEyeSpaceFromLightSpaceMatrix()
             || getHasProjectionLightSpaceFromEyeSpaceMatrix()
             || getHasInvProjectionLightSpaceFromEyeSpaceMatrix()) )
        {
            calcLightSpaceMatrixLSFromWS(idx, matLSFromWS);
            //matLSFromWS = matTest;
        }
        else 
        if (getHasLightSpaceFromWorldSpaceMatrix()
         || getHasWorldSpaceFromLightSpaceMatrix()
         || getHasLightSpaceFromEyeSpaceMatrix()
         || getHasEyeSpaceFromLightSpaceMatrix()
         || getHasProjectionLightSpaceFromWorldSpaceMatrix()
         || getHasInvProjectionLightSpaceFromWorldSpaceMatrix()
         || getHasProjectionLightSpaceFromEyeSpaceMatrix()
         || getHasInvProjectionLightSpaceFromEyeSpaceMatrix())
        {
            calcLightSpaceMatricesLSFrom(pEnv, idx, matLSFromWS, matLSFromES);
            //matLSFromES = matTest;
        }

        if (getHasWorldSpaceFromLightSpaceMatrix())
        {
            matLSFromWS.inverse(matWSFromLS);
            //matWSFromLS = matTest;
        }

        if (getHasEyeSpaceFromLightSpaceMatrix())
        {
            matLSFromES.inverse(matESFromLS);
            //matESFromLS = matTest;
        }

        Matrix matProjection, matInvProjection;

        if (getHasProjectionMatrix()
         || getHasInvProjectionMatrix()
         || getHasProjectionLightSpaceFromWorldSpaceMatrix()
         || getHasInvProjectionLightSpaceFromWorldSpaceMatrix()
         || getHasProjectionLightSpaceFromEyeSpaceMatrix()
         || getHasInvProjectionLightSpaceFromEyeSpaceMatrix())
        {
            matProjection = getProjectionMatrix(idx);
            //matProjection = matTest;
        }

        if (getHasInvProjectionMatrix())
        {
            matProjection.inverse(matInvProjection);
            //matInvProjection = matTest;
        }

        Matrix matProjLSFromWS, matInvProjLSFromWS;
        Matrix matProjLSFromES, matInvProjLSFromES;

        if (getHasProjectionLightSpaceFromWorldSpaceMatrix())
        {
            matProjLSFromWS = matProjection;
            matProjLSFromWS.mult(matLSFromWS);
            //matProjLSFromWS = matTest;
        }

        if (getHasInvProjectionLightSpaceFromWorldSpaceMatrix())
        {
            matProjLSFromWS.inverse(matInvProjLSFromWS);
            //matInvProjLSFromWS = matTest;
        }

        if (getHasProjectionLightSpaceFromEyeSpaceMatrix())
        {
            matProjLSFromES = matProjection;
            matProjLSFromES.mult(matLSFromES);
            //matProjLSFromES = matTest;
        }

        if (getHasInvProjectionLightSpaceFromEyeSpaceMatrix())
        {
            matProjLSFromES.inverse(matInvProjLSFromES);
            //matProjLSFromES = matTest;
        }


        if (getHasLightSpaceFromWorldSpaceMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "mVal = lights.light[" << idx << "].matLSFromWS;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(mVal, " 
           << "mat4(vec4(" << matLSFromWS[0][0] << " ," << matLSFromWS[0][1] << " ," << matLSFromWS[0][2] << " ," << matLSFromWS[0][3]
             << "), vec4(" << matLSFromWS[1][0] << " ," << matLSFromWS[1][1] << " ," << matLSFromWS[1][2] << " ," << matLSFromWS[1][3]
             << "), vec4(" << matLSFromWS[2][0] << " ," << matLSFromWS[2][1] << " ," << matLSFromWS[2][2] << " ," << matLSFromWS[2][3]
             << "), vec4(" << matLSFromWS[3][0] << " ," << matLSFromWS[3][1] << " ," << matLSFromWS[3][2] << " ," << matLSFromWS[3][3] 
             << ")), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasWorldSpaceFromLightSpaceMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matWSFromLS[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matWSFromLS[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matWSFromLS[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matWSFromLS[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "mVal = lights.light[" << idx << "].matWSFromLS;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(mVal, " 
           << "mat4(vec4(" << matWSFromLS[0][0] << " ," << matWSFromLS[0][1] << " ," << matWSFromLS[0][2] << " ," << matWSFromLS[0][3]
             << "), vec4(" << matWSFromLS[1][0] << " ," << matWSFromLS[1][1] << " ," << matWSFromLS[1][2] << " ," << matWSFromLS[1][3]
             << "), vec4(" << matWSFromLS[2][0] << " ," << matWSFromLS[2][1] << " ," << matWSFromLS[2][2] << " ," << matWSFromLS[2][3]
             << "), vec4(" << matWSFromLS[3][0] << " ," << matWSFromLS[3][1] << " ," << matWSFromLS[3][2] << " ," << matWSFromLS[3][3]
             << ")), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasLightSpaceFromEyeSpaceMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromES[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromES[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromES[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromES[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "mVal = lights.light[" << idx << "].matLSFromES;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(mVal, " 
           << "mat4(vec4(" << matLSFromES[0][0] << " ," << matLSFromES[0][1] << " ," << matLSFromES[0][2] << " ," << matLSFromES[0][3]
             << "), vec4(" << matLSFromES[1][0] << " ," << matLSFromES[1][1] << " ," << matLSFromES[1][2] << " ," << matLSFromES[1][3]
             << "), vec4(" << matLSFromES[2][0] << " ," << matLSFromES[2][1] << " ," << matLSFromES[2][2] << " ," << matLSFromES[2][3]
             << "), vec4(" << matLSFromES[3][0] << " ," << matLSFromES[3][1] << " ," << matLSFromES[3][2] << " ," << matLSFromES[3][3]
             << ")), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasEyeSpaceFromLightSpaceMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matESFromLS[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matESFromLS[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matESFromLS[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matESFromLS[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "mVal = lights.light[" << idx << "].matESFromLS;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(mVal, " 
           << "mat4(vec4(" << matESFromLS[0][0] << " ," << matESFromLS[0][1] << " ," << matESFromLS[0][2] << " ," << matESFromLS[0][3]
             << "), vec4(" << matESFromLS[1][0] << " ," << matESFromLS[1][1] << " ," << matESFromLS[1][2] << " ," << matESFromLS[1][3]
             << "), vec4(" << matESFromLS[2][0] << " ," << matESFromLS[2][1] << " ," << matESFromLS[2][2] << " ," << matESFromLS[2][3]
             << "), vec4(" << matESFromLS[3][0] << " ," << matESFromLS[3][1] << " ," << matESFromLS[3][2] << " ," << matESFromLS[3][3]
             << ")), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasProjectionMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjection[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjection[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjection[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjection[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "mVal = lights.light[" << idx << "].matProjection;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(mVal, " 
           << "mat4(vec4(" << matProjection[0][0] << " ," << matProjection[0][1] << " ," << matProjection[0][2] << " ," << matProjection[0][3]
             << "), vec4(" << matProjection[1][0] << " ," << matProjection[1][1] << " ," << matProjection[1][2] << " ," << matProjection[1][3]
             << "), vec4(" << matProjection[2][0] << " ," << matProjection[2][1] << " ," << matProjection[2][2] << " ," << matProjection[2][3]
             << "), vec4(" << matProjection[3][0] << " ," << matProjection[3][1] << " ," << matProjection[3][2] << " ," << matProjection[3][3]
             << ")), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasInvProjectionMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjection[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjection[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjection[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjection[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "mVal = lights.light[" << idx << "].matInvProjection;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(mVal, " 
           << "mat4(vec4(" << matInvProjection[0][0] << " ," << matInvProjection[0][1] << " ," << matInvProjection[0][2] << " ," << matInvProjection[0][3]
             << "), vec4(" << matInvProjection[1][0] << " ," << matInvProjection[1][1] << " ," << matInvProjection[1][2] << " ," << matInvProjection[1][3]
             << "), vec4(" << matInvProjection[2][0] << " ," << matInvProjection[2][1] << " ," << matInvProjection[2][2] << " ," << matInvProjection[2][3]
             << "), vec4(" << matInvProjection[3][0] << " ," << matInvProjection[3][1] << " ," << matInvProjection[3][2] << " ," << matInvProjection[3][3]
             << ")), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasProjectionLightSpaceFromWorldSpaceMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjLSFromWS[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjLSFromWS[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjLSFromWS[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjLSFromWS[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "mVal = lights.light[" << idx << "].matProjLSFromWS;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(mVal, " 
           << "mat4(vec4(" << matProjLSFromWS[0][0] << " ," << matProjLSFromWS[0][1] << " ," << matProjLSFromWS[0][2] << " ," << matProjLSFromWS[0][3]
             << "), vec4(" << matProjLSFromWS[1][0] << " ," << matProjLSFromWS[1][1] << " ," << matProjLSFromWS[1][2] << " ," << matProjLSFromWS[1][3]
             << "), vec4(" << matProjLSFromWS[2][0] << " ," << matProjLSFromWS[2][1] << " ," << matProjLSFromWS[2][2] << " ," << matProjLSFromWS[2][3]
             << "), vec4(" << matProjLSFromWS[3][0] << " ," << matProjLSFromWS[3][1] << " ," << matProjLSFromWS[3][2] << " ," << matProjLSFromWS[3][3]
             << ")), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasInvProjectionLightSpaceFromWorldSpaceMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjLSFromWS[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjLSFromWS[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjLSFromWS[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjLSFromWS[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "mVal = lights.light[" << idx << "].matInvProjLSFromWS;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(mVal, " 
           << "mat4(vec4(" << matInvProjLSFromWS[0][0] << " ," << matInvProjLSFromWS[0][1] << " ," << matInvProjLSFromWS[0][2] << " ," << matInvProjLSFromWS[0][3]
             << "), vec4(" << matInvProjLSFromWS[1][0] << " ," << matInvProjLSFromWS[1][1] << " ," << matInvProjLSFromWS[1][2] << " ," << matInvProjLSFromWS[1][3]
             << "), vec4(" << matInvProjLSFromWS[2][0] << " ," << matInvProjLSFromWS[2][1] << " ," << matInvProjLSFromWS[2][2] << " ," << matInvProjLSFromWS[2][3]
             << "), vec4(" << matInvProjLSFromWS[3][0] << " ," << matInvProjLSFromWS[3][1] << " ," << matInvProjLSFromWS[3][2] << " ," << matInvProjLSFromWS[3][3]
             << ")), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasProjectionLightSpaceFromEyeSpaceMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjLSFromES[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjLSFromES[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjLSFromES[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matProjLSFromES[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "mVal = lights.light[" << idx << "].matProjLSFromES;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(mVal, " 
           << "mat4(vec4(" << matProjLSFromES[0][0] << " ," << matProjLSFromES[0][1] << " ," << matProjLSFromES[0][2] << " ," << matProjLSFromES[0][3]
             << "), vec4(" << matProjLSFromES[1][0] << " ," << matProjLSFromES[1][1] << " ," << matProjLSFromES[1][2] << " ," << matProjLSFromES[1][3]
             << "), vec4(" << matProjLSFromES[2][0] << " ," << matProjLSFromES[2][1] << " ," << matProjLSFromES[2][2] << " ," << matProjLSFromES[2][3]
             << "), vec4(" << matProjLSFromES[3][0] << " ," << matProjLSFromES[3][1] << " ," << matProjLSFromES[3][2] << " ," << matProjLSFromES[3][3]
             << ")), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasInvProjectionLightSpaceFromEyeSpaceMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjLSFromES[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjLSFromES[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjLSFromES[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvProjLSFromES[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "mVal = lights.light[" << idx << "].matInvProjLSFromES;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(mVal, " 
           << "mat4(vec4(" << matInvProjLSFromES[0][0] << " ," << matInvProjLSFromES[0][1] << " ," << matInvProjLSFromES[0][2] << " ," << matInvProjLSFromES[0][3]
             << "), vec4(" << matInvProjLSFromES[1][0] << " ," << matInvProjLSFromES[1][1] << " ," << matInvProjLSFromES[1][2] << " ," << matInvProjLSFromES[1][3]
             << "), vec4(" << matInvProjLSFromES[2][0] << " ," << matInvProjLSFromES[2][1] << " ," << matInvProjLSFromES[2][2] << " ," << matInvProjLSFromES[2][3]
             << "), vec4(" << matInvProjLSFromES[3][0] << " ," << matInvProjLSFromES[3][1] << " ," << matInvProjLSFromES[3][2] << " ," << matInvProjLSFromES[3][3]
             << ")), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &position [0], sizeof(Pnt3f)); bo = ao + sizeof(Pnt3f);
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &direction[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "vVal = lights.light[" << idx << "].position;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(vVal,  vec3(" <<  position[0] << " ," <<  position[1] << " ," <<  position[2] << "), 1.E-5) == false) flag = false;" << end_token << std::endl;

        ss << start_token << "vVal = lights.light[" << idx << "].direction;" << end_token << std::endl;
        ss << start_token << "if (OSGEqualEps(vVal, vec3(" << direction[0] << " ," << direction[1] << " ," << direction[2] << "), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif

        if (getHasSeparateIntensities())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getAmbient (idx)[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getDiffuse (idx)[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getSpecular(idx)[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "vVal = lights.light[" << idx << "].ambientIntensity;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(vVal, vec3("  << getAmbient (idx)[0] << " ," << getAmbient (idx)[1] << " ," << getAmbient (idx)[2] << "), 1.E-5) == false) flag = false;" << end_token << std::endl;

            ss << start_token << "vVal = lights.light[" << idx << "].diffuseIntensity;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(vVal, vec3("  << getDiffuse (idx)[0] << " ," << getDiffuse (idx)[1] << " ," << getDiffuse (idx)[2] << "), 1.E-5) == false) flag = false;" << end_token << std::endl;

            ss << start_token << "vVal = lights.light[" << idx << "].specularIntensity;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(vVal, vec3(" << getSpecular(idx)[0] << " ," << getSpecular(idx)[1] << " ," << getSpecular(idx)[2] << "), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasIntensity())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getIntensity(idx)[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "vVal = lights.light[" << idx << "].intensity;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(vVal, vec3("  << getIntensity (idx)[0] << " ," << getIntensity(idx)[1] << " ," << getIntensity(idx)[2] << "), 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasAttenuation())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getAttenuation(idx)[0]; bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getAttenuation(idx)[1]; bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getAttenuation(idx)[2]; bo = ao + sizeof(Real32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].constantAttenuation;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, "  << getAttenuation(idx)[0] << ", 1.E-5) == false) flag = false;" << end_token << std::endl;

            ss << start_token << "fVal = lights.light[" << idx << "].linearAttenuation;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, "    << getAttenuation(idx)[1] << ", 1.E-5) == false) flag = false;" << end_token << std::endl;

            ss << start_token << "fVal = lights.light[" << idx << "].quadraticAttenuation;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << getAttenuation(idx)[2] << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasDecayAttenuation())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getDecayAttenuation(idx); bo = ao + sizeof(Real32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].decayAttenuation;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, "  << getDecayAttenuation(idx)[0] << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasLengthFactor())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getLengthFactor(idx); bo = ao + sizeof(Real32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].lengthFactor;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, "  << getLengthFactor(idx)[0] << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasRangeCutOn())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = cutOnRange; bo = ao + sizeof(Real32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].rangeCutOn;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << cutOnRange << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasRangeCutOff())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = cutOffRange; bo = ao + sizeof(Real32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].rangeCutOff;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << cutOffRange << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasRangeNearZone())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getRangeNearZone(idx); bo = ao + sizeof(Real32);
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].rangeNearZone;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << getRangeNearZone(idx) << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasRangeFarZone())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getRangeFarZone (idx); bo = ao + sizeof(Real32);
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].rangeFarZone;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << getRangeFarZone(idx) << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasCosSpotlightAngle() || (!getHasCosSpotlightAngle() && !getHasSpotlightAngle()))
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = cosSpotlightAngle; bo = ao + sizeof(Real32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].cosSpotlightAngle;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << cosSpotlightAngle << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasTanSpotlightAngle())
        {
            Real32 angleRad = osgDegree2Rad(getSpotlightAngle(idx));
            Real32 tanSpotlightAngle = osgTan(angleRad);

            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = tanSpotlightAngle; bo = ao + sizeof(Real32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].tanSpotlightAngle;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << tanSpotlightAngle << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasSpotlightAngle())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = spotlightAngle; bo = ao + sizeof(Real32);
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].spotlightAngle;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << spotlightAngle << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasSpotlightExponent())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getSpotlightExponent(idx); bo = ao + sizeof(Real32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].spotlightExponent;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << getSpotlightExponent(idx) << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }
        else
        if (getHasSpotlightPenumbraFrostbite())
        {
            if (getHasSpotlightPenumbraAngle() || getHasSpotlightPenumbraFactor())
            {
                Real32 cosSpotlightPenumbraAngle = cosSpotlightAngle;

                if (getHasSpotlightPenumbraAngle())
                {
                    Real32 angleRad = osgDegree2Rad(getSpotlightPenumbraAngle(idx));
                    cosSpotlightPenumbraAngle = osgCos(angleRad);
                }
                else
                if (getHasSpotlightPenumbraFactor())
                {
                    cosSpotlightPenumbraAngle = osgCos(spotlightAngle * getSpotlightPenumbraFactor(idx));
                }

                Real32 scale  = 1.f / osgMax(0.001f, cosSpotlightPenumbraAngle - cosSpotlightAngle);
                Real32 offset = -cosSpotlightAngle * scale;

                ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = scale;  bo = ao + sizeof(Real32);
                ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = offset; bo = ao + sizeof(Real32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
                ss << start_token << "fVal = lights.light[" << idx << "].spotlightScale;" << end_token << std::endl;
                ss << start_token << "if (OSGEqualEps(fVal, " << scale << ", 1.E-5) == false) flag = false;" << end_token << std::endl;

                ss << start_token << "fVal = lights.light[" << idx << "].spotlightOffset;" << end_token << std::endl;
                ss << start_token << "if (OSGEqualEps(fVal, " << offset << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
            }
        }
        else
        if (getHasSpotlightPenumbraAngle())
        {
            Real32 angleRad = osgDegree2Rad(getSpotlightPenumbraAngle(idx));
            Real32 cosSpotlightPenumbraAngle = osgCos(angleRad);

            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = cosSpotlightPenumbraAngle; bo = ao + sizeof(Real32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].cosSpotlightPenumbraAngle;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << cosSpotlightPenumbraAngle << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }
        else
        if (getHasSpotlightPenumbraFactor())
        {
            Real32 cosSpotlightPenumbraAngle = osgCos(spotlightAngle * getSpotlightPenumbraFactor(idx));

            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = cosSpotlightPenumbraAngle; bo = ao + sizeof(Real32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].cosSpotlightPenumbraAngle;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << cosSpotlightPenumbraAngle << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        if (getHasCinemaLight())
        {
            Real32 twistAngle = osgDegree2Rad(getSuperEllipsesTwist(idx));

            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getInnerSuperEllipsesWidth (idx); bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getInnerSuperEllipsesHeight(idx); bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getOuterSuperEllipsesWidth (idx); bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getOuterSuperEllipsesHeight(idx); bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getSuperEllipsesRoundness  (idx); bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = twistAngle;                       bo = ao + sizeof(Real32);
            
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "fVal = lights.light[" << idx << "].innerSuperEllipsesWidth;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << getInnerSuperEllipsesWidth (idx) << ", 1.E-5) == false) flag = false;" << end_token << std::endl;

            ss << start_token << "fVal = lights.light[" << idx << "].innerSuperEllipsesHeight;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << getInnerSuperEllipsesHeight(idx) << ", 1.E-5) == false) flag = false;" << end_token << std::endl;

            ss << start_token << "fVal = lights.light[" << idx << "].outerSuperEllipsesWidth;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << getOuterSuperEllipsesWidth (idx) << ", 1.E-5) == false) flag = false;" << end_token << std::endl;

            ss << start_token << "fVal = lights.light[" << idx << "].outerSuperEllipsesHeight;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << getOuterSuperEllipsesHeight(idx) << ", 1.E-5) == false) flag = false;" << end_token << std::endl;

            ss << start_token << "fVal = lights.light[" << idx << "].superEllipsesRoundness;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << getSuperEllipsesRoundness  (idx) << ", 1.E-5) == false) flag = false;" << end_token << std::endl;

            ss << start_token << "fVal = lights.light[" << idx << "].superEllipsesTwist;" << end_token << std::endl;
            ss << start_token << "if (OSGEqualEps(fVal, " << twistAngle                       << ", 1.E-5) == false) flag = false;" << end_token << std::endl;
#endif
        }

        ao = alignOffset( 4, bo); *(reinterpret_cast<Int32*>(&buffer[0] + ao)) = Int32(getTypeOfLight(idx)); bo = ao + sizeof(Int32);
        ao = alignOffset( 4, bo); *(reinterpret_cast<bool* >(&buffer[0] + ao)) = getEnabled(idx);            bo = ao + sizeof(Int32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << "iVal = lights.light[" << idx << "].type;" << end_token << std::endl;
        ss << start_token << "if (iVal != " << Int32(getTypeOfLight(idx)) << ") flag = false;" << end_token << std::endl;

        ss << start_token << "bVal = lights.light[" << idx << "].enabled;" << end_token << std::endl;
        ss << start_token << "if (bVal != " << (getEnabled(idx) ? "true" : "false") << ") flag = false;" << end_token << std::endl;
#endif

        if (getHasShadow())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<bool*  >(&buffer[0] + ao)) = getShadow              (idx); bo = ao + sizeof( Int32);
            ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = getShadowDataIndex     (idx); bo = ao + sizeof( Int32);
            ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = getShadowParameterIndex(idx); bo = ao + sizeof( Int32);

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
            ss << start_token << "bVal = lights.light[" << idx << "].shadow;" << end_token << std::endl;
            ss << start_token << "if (bVal != " << (getShadow(idx) ? "true" : "false") << ") flag = false;" << end_token << std::endl;

            ss << start_token << "iVal = lights.light[" << idx << "].shadowDataIndex;" << end_token << std::endl;
            ss << start_token << "if (iVal != " << getShadowDataIndex     (idx) << ") flag = false;" << end_token << std::endl;

            ss << start_token << "iVal = lights.light[" << idx << "].shadowParameterIndex;" << end_token << std::endl;
            ss << start_token << "if (iVal != " << getShadowParameterIndex(idx) << ") flag = false;" << end_token << std::endl;
#endif
        }

        ao = alignOffset(16, bo); bo = ao;    // padding
        
#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
        ss << start_token << end_token << std::endl;
#endif
    }

#ifdef OSG_LOG_MULTILIGHT_SHADER_TEST_CODE
    ::OutputDebugString(ss.str().c_str());
    FDEBUG((ss.str().c_str()));
#endif

    return buffer;
}

void MultiLightChunk::createLightState(DrawEnv* pEnv)
{
    std::vector<UInt8> buffer = createLightBuffer(pEnv);
    editMFBuffer()->setValues(buffer);
}

void MultiLightChunk::updateLightState(DrawEnv* pEnv)
{
    if (_mfBeacon.size() != _mfBeaconMatrix.size()) 
    {
        editMField(BeaconFieldMask, _mfBeaconMatrix);
        _mfBeaconMatrix.resize(_mfBeacon.size(), Matrix());
    }

    std::vector<UInt8> buffer = createLightBuffer(pEnv);
    editMFBuffer()->setValues(buffer);

    setLastCamNear   (pEnv->getCameraNear());
    setLastCamFar    (pEnv->getCameraFar());
    setLastCamToWorld(pEnv->getCameraToWorld());

    for (std::size_t idx = 0; idx < _mfBeacon.size(); ++idx)
    {
        Matrix matWsFromBS;
        Node* beacon = getBeacon(UInt32(idx));
        if (beacon)
        {
            beacon->getToWorld(matWsFromBS);

            editMField(BeaconMatrixFieldMask, _mfBeaconMatrix);
            _mfBeaconMatrix[idx] = matWsFromBS;
        }
    }

    _bUpdateBuffer = false;
}

/*------------------------------ activate -----------------------------------*/

void MultiLightChunk::activate(DrawEnv *pEnv, UInt32 idx)
{
    if (getLastCamNear   () != pEnv->getCameraNear   () ||
        getLastCamFar    () != pEnv->getCameraFar    () ||
        getLastCamToWorld() != pEnv->getCameraToWorld() ||
        _mfBeacon.size   () != _mfBeaconMatrix.size  () 
        )
    {
        _bUpdateBuffer = true;
    } 
    else
    {
        for (std::size_t idx = 0; idx < _mfBeacon.size(); ++idx)
        {
            Matrix matWsFromBS;
            Node* beacon = getBeacon(UInt32(idx));
            if (beacon)
            {
                beacon->getToWorld(matWsFromBS);

                if (matWsFromBS != _mfBeaconMatrix[idx])
                {
                    _bUpdateBuffer = true;
                    break;
                }
            }
        }
    }

    //_bUpdateBuffer = true;
    if (_bUpdateBuffer)
        updateLightState(pEnv);

    Inherited::activate(pEnv, idx);
}

/*------------------------------ deactivate ---------------------------------*/

void MultiLightChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
{
    Inherited::deactivate(pEnv, idx);
}

/*------------------------------ changeFrom ---------------------------------*/

void MultiLightChunk::changeFrom(DrawEnv    *pEnv,
                                 StateChunk *old,
                                 UInt32      idx )
{
    Inherited::changeFrom(pEnv, old, idx);
}

/*------------------------------ interface ----------------------------------*/

UInt32 MultiLightChunk::addLight(MultiLight::TypeOfLight eTypeOfLight)
{
    if (!check_invariant())
        clearLights();

    editMField(PositionFieldMask,           _mfPosition);
    editMField(DirectionFieldMask,          _mfDirection);
    editMField(SpotlightAngleFieldMask,     _mfSpotlightAngle);
    editMField(TypeOfLightFieldMask,        _mfTypeOfLight);
    editMField(EnabledFieldMask,            _mfEnabled);
    editMField(BeaconFieldMask,             _mfBeacon);
    editMField(BeaconMatrixFieldMask,       _mfBeaconMatrix);

    _mfPosition.        push_back(Pnt3f(0.f,0.f,0.f));
    _mfDirection.       push_back(Vec3f(0.f,0.f,1.f));
    _mfSpotlightAngle.  push_back(45.f);
    _mfTypeOfLight.     push_back(eTypeOfLight);
    _mfEnabled.         push_back(false);
                        pushToBeacon(NULL);
    _mfBeaconMatrix.    push_back(Matrix());

    if (getHasSeparateIntensities())
    {
        editMField(AmbientIntensityFieldMask,   _mfAmbientIntensity);
        editMField(DiffuseIntensityFieldMask,   _mfDiffuseIntensity);
        editMField(SpecularIntensityFieldMask,  _mfSpecularIntensity);

        _mfAmbientIntensity. push_back(Vec3f(1.f,1.f,1.f));
        _mfDiffuseIntensity. push_back(Vec3f(1.f,1.f,1.f));
        _mfSpecularIntensity.push_back(Vec3f(1.f,1.f,1.f));
    }

    if (getHasIntensity())
    {
        editMField(IntensityFieldMask,        _mfIntensity);
        _mfIntensity.push_back(Vec3f(1.f,1.f,1.f));
    }

    if (getHasAttenuation())
    {
        editMField(AttenuationFieldMask,      _mfAttenuation);
        _mfAttenuation.push_back(Vec3f(1.f,0.f,0.f));
    }

    if (getHasDecayAttenuation())
    {
        editMField(DecayAttenuationFieldMask, _mfDecayAttenuation);
        _mfDecayAttenuation.push_back(2.f);
    }

    if (getHasLengthFactor())
    {
        editMField(LengthFactorFieldMask,     _mfLengthFactor);
        _mfLengthFactor.push_back(1.f);
    }

    if (getHasRangeCutOn())
    {
        editMField(RangeCutOnFieldMask,       _mfRangeCutOn);
        _mfRangeCutOn.push_back(0.f);
    }

    if (getHasRangeCutOff())
    {
        editMField(RangeCutOffFieldMask,      _mfRangeCutOff);
        _mfRangeCutOff.push_back(0.f);
    }

    if (getHasRangeNearZone())
    {
        editMField(RangeNearZoneFieldMask,    _mfRangeNearZone);
        _mfRangeNearZone.push_back(0.f);
    }

    if (getHasRangeFarZone())
    {
        editMField(RangeFarZoneFieldMask,     _mfRangeFarZone);
        _mfRangeFarZone.push_back(0.f);
    }

    if (getHasSpotlightExponent())
    {
        editMField(SpotExponentFieldMask,     _mfSpotExponent);
        _mfSpotExponent.push_back(1.f);
    }
    else
    if (getHasSpotlightPenumbraAngle())
    {
        editMField(SpotExponentFieldMask,     _mfSpotExponent);
        _mfSpotExponent.push_back(40.f);
    }
    else
    if (getHasSpotlightPenumbraFactor())
    {
        editMField(SpotExponentFieldMask,     _mfSpotExponent);
        _mfSpotExponent.push_back(0.9f);
    }

    if (getHasCinemaLight())
    {
        editMField(InnerSuperEllipsesWidthFieldMask,    _mfInnerSuperEllipsesWidth);
        editMField(InnerSuperEllipsesHeightFieldMask,   _mfInnerSuperEllipsesHeight);
        editMField(OuterSuperEllipsesWidthFieldMask,    _mfOuterSuperEllipsesWidth);
        editMField(OuterSuperEllipsesHeightFieldMask,   _mfOuterSuperEllipsesHeight);
        editMField(SuperEllipsesRoundnessFieldMask,     _mfSuperEllipsesRoundness);
        editMField(SuperEllipsesTwistFieldMask,         _mfSuperEllipsesTwist);

        _mfInnerSuperEllipsesWidth. push_back(1.f);
        _mfInnerSuperEllipsesHeight.push_back(1.f);
        _mfOuterSuperEllipsesWidth. push_back(1.f);
        _mfOuterSuperEllipsesHeight.push_back(1.f);
        _mfSuperEllipsesRoundness.  push_back(0.f);
        _mfSuperEllipsesTwist.      push_back(0.f);
    }

    if (getHasProjection())
    {
        editMField(ProjectionMatrixFieldMask, _mfProjectionMatrix);
        _mfProjectionMatrix.push_back(Matrix());
    }

    if (getHasShadow())
    {
        editMField(ShadowFieldMask,               _mfShadow);
        editMField(ShadowDataIndexFieldMask,      _mfShadowDataIndex);
        editMField(ShadowParameterIndexFieldMask, _mfShadowParameterIndex);

        _mfShadow              .push_back(false);
        _mfShadowDataIndex     .push_back(-1);
        _mfShadowParameterIndex.push_back(-1);
    }

    OSG_ASSERT(check_invariant());

    return UInt32(_mfPosition.size() - 1);
}

UInt32 MultiLightChunk::addLight(const MultiLight& light)
{
    if (!check_invariant())
        clearLights();

    editMField(PositionFieldMask,           _mfPosition);
    editMField(DirectionFieldMask,          _mfDirection);
    editMField(SpotlightAngleFieldMask,     _mfSpotlightAngle);
    editMField(TypeOfLightFieldMask,        _mfTypeOfLight);
    editMField(EnabledFieldMask,            _mfEnabled);
    editMField(BeaconFieldMask,             _mfBeacon);
    editMField(BeaconMatrixFieldMask,       _mfBeaconMatrix);

    _mfPosition.        push_back(light.getPosition());
    _mfDirection.       push_back(light.getDirection());
    _mfSpotlightAngle.  push_back(light.getSpotlightAngle());
    _mfTypeOfLight.     push_back(light.getTypeOfLight());
    _mfEnabled.         push_back(light.getEnabled());
                        pushToBeacon(light.getBeacon());
    _mfBeaconMatrix.    push_back(Matrix());

    if (getHasSeparateIntensities())
    {
        editMField(AmbientIntensityFieldMask,   _mfAmbientIntensity);
        editMField(DiffuseIntensityFieldMask,   _mfDiffuseIntensity);
        editMField(SpecularIntensityFieldMask,  _mfSpecularIntensity);

        _mfAmbientIntensity. push_back(light.getAmbient());
        _mfDiffuseIntensity. push_back(light.getDiffuse());
        _mfSpecularIntensity.push_back(light.getSpecular());
    }

    if (getHasIntensity())
    {
        editMField(IntensityFieldMask,          _mfIntensity);

        _mfIntensity.push_back(light.getIntensity());
    }

    if (getHasAttenuation())
    {
        editMField(AttenuationFieldMask,        _mfAttenuation);
        _mfAttenuation.push_back(light.getAttenuation());
    }

    if (getHasDecayAttenuation())
    {
        editMField(DecayAttenuationFieldMask,   _mfDecayAttenuation);
        _mfDecayAttenuation.push_back(light.getDecayAttenuation());
    }

    if (getHasLengthFactor())
    {
        editMField(LengthFactorFieldMask,   _mfLengthFactor);
        _mfLengthFactor.push_back(light.getLengthFactor());
    }

    if (getHasRangeCutOn())
    {
        editMField(RangeCutOnFieldMask,         _mfRangeCutOn);
        _mfRangeCutOn.push_back(light.getRangeCutOn());
    }

    if (getHasRangeCutOff())
    {
        editMField(RangeCutOffFieldMask,        _mfRangeCutOff);
        _mfRangeCutOff.push_back(light.getRangeCutOff());
    }

    if (getHasRangeNearZone())
    {
        editMField(RangeNearZoneFieldMask,      _mfRangeNearZone);
        _mfRangeNearZone.push_back(light.getRangeNearZone());
    }

    if (getHasRangeFarZone())
    {
        editMField(RangeFarZoneFieldMask,       _mfRangeFarZone);
        _mfRangeFarZone.push_back(light.getRangeFarZone());
    }

    if (getHasSpotlightExponent())
    {
        editMField(SpotExponentFieldMask,       _mfSpotExponent);
        _mfSpotExponent.push_back(light.getSpotlightExponent());
    }
    else
    if (getHasSpotlightPenumbraAngle())
    {
        editMField(SpotExponentFieldMask,       _mfSpotExponent);
        _mfSpotExponent.push_back(light.getSpotlightPenumbraAngle());
    }
    else
    if (getHasSpotlightPenumbraFactor())
    {
        editMField(SpotExponentFieldMask,       _mfSpotExponent);
        _mfSpotExponent.push_back(light.getSpotlightPenumbraFactor());
    }

    if (getHasCinemaLight())
    {
        editMField(InnerSuperEllipsesWidthFieldMask,    _mfInnerSuperEllipsesWidth);
        editMField(InnerSuperEllipsesHeightFieldMask,   _mfInnerSuperEllipsesHeight);
        editMField(OuterSuperEllipsesWidthFieldMask,    _mfOuterSuperEllipsesWidth);
        editMField(OuterSuperEllipsesHeightFieldMask,   _mfOuterSuperEllipsesHeight);
        editMField(SuperEllipsesRoundnessFieldMask,     _mfSuperEllipsesRoundness);
        editMField(SuperEllipsesTwistFieldMask,         _mfSuperEllipsesTwist);

        _mfInnerSuperEllipsesWidth. push_back(light.getInnerSuperEllipsesWidth());
        _mfInnerSuperEllipsesHeight.push_back(light.getInnerSuperEllipsesHeight());
        _mfOuterSuperEllipsesWidth. push_back(light.getOuterSuperEllipsesWidth());
        _mfOuterSuperEllipsesHeight.push_back(light.getOuterSuperEllipsesHeight());
        _mfSuperEllipsesRoundness.  push_back(light.getSuperEllipsesRoundness());
        _mfSuperEllipsesTwist.      push_back(light.getSuperEllipsesTwist());
    }

    if (getHasProjection())
    {
        editMField(ProjectionMatrixFieldMask, _mfProjectionMatrix);
        _mfProjectionMatrix.push_back(light.getProjectionMatrix());
    }

    if (getHasShadow())
    {
        editMField(ShadowFieldMask,               _mfShadow);
        editMField(ShadowDataIndexFieldMask,      _mfShadowDataIndex);
        editMField(ShadowParameterIndexFieldMask, _mfShadowParameterIndex);

        _mfShadow              .push_back(light.getShadow());
        _mfShadowDataIndex     .push_back(light.getShadowDataIndex());
        _mfShadowParameterIndex.push_back(light.getShadowParameterIndex());
    }
    
    OSG_ASSERT(check_invariant());

    return UInt32(_mfPosition.size() - 1);
}

void MultiLightChunk::updateLight(const UInt32 idx, const MultiLight& light)
{
    setPosition         (idx, light.getPosition());
    setDirection        (idx, light.getDirection());
    setSpotlightAngle   (idx, light.getSpotlightAngle());
    setTypeOfLight      (idx, light.getTypeOfLight());
    setEnabled          (idx, light.getEnabled());
    setBeacon           (idx, light.getBeacon());

    if (getHasSeparateIntensities())
    {
        setAmbient (idx, light.getAmbient());
        setDiffuse (idx, light.getDiffuse());
        setSpecular(idx, light.getSpecular());
    }

    if (getHasIntensity())
    {
        setIntensity(idx, light.getIntensity());
    }

    if (getHasAttenuation())
    {
        setAttenuation(idx, light.getAttenuation());
    }

    if (getHasDecayAttenuation())
    {
        setDecayAttenuation(idx, light.getDecayAttenuation());
    }

    if (getHasLengthFactor())
    {
        setLengthFactor(idx, light.getLengthFactor());
    }

    if (getHasRangeCutOn())
    {
        setRangeCutOn(idx, light.getRangeCutOn());
    }

    if (getHasRangeCutOff())
    {
        setRangeCutOff(idx, light.getRangeCutOff());
    }

    if (getHasRangeNearZone())
    {
        setRangeNearZone(idx, light.getRangeNearZone());
    }

    if (getHasRangeFarZone())
    {
        setRangeFarZone(idx, light.getRangeFarZone());
    }

    if (getHasSpotlightExponent())
    {
        setSpotlightExponent(idx, light.getSpotlightExponent());
    }
    else
    if (getHasSpotlightPenumbraAngle())
    {
        setSpotlightPenumbraAngle(idx, light.getSpotlightPenumbraAngle());
    }
    else
    if (getHasSpotlightPenumbraFactor())
    {
        setSpotlightPenumbraFactor(idx, light.getSpotlightPenumbraFactor());
    }

    if (getHasCinemaLight())
    {
        setInnerSuperEllipsesWidth  (idx, light.getInnerSuperEllipsesWidth());
        setInnerSuperEllipsesHeight (idx, light.getInnerSuperEllipsesHeight());
        setOuterSuperEllipsesWidth  (idx, light.getOuterSuperEllipsesWidth());
        setOuterSuperEllipsesHeight (idx, light.getOuterSuperEllipsesHeight());
        setSuperEllipsesRoundness   (idx, light.getSuperEllipsesRoundness());
        setSuperEllipsesTwist       (idx, light.getSuperEllipsesTwist());
    }

    if (getHasProjection())
    {
        setProjectionMatrix(idx, light.getProjectionMatrix());
    }

    if (getHasShadow())
    {
        setShadow              (idx, light.getShadow());
        setShadowDataIndex     (idx, light.getShadowDataIndex());
        setShadowParameterIndex(idx, light.getShadowParameterIndex());
    }
   
}

MultiLight MultiLightChunk::getLight(const UInt32 idx)
{
    OSG_ASSERT(check_invariant());

    MultiLight light(getTypeOfLight(idx));

    light.setPosition         (getPosition         (idx));
    light.setDirection        (getDirection        (idx));
    light.setSpotlightAngle   (getSpotlightAngle   (idx));
    light.setEnabled          (getEnabled          (idx));
    light.setBeacon           (getBeacon           (idx));

    if (getHasSeparateIntensities())
    {
        light.setAmbient (getAmbient (idx));
        light.setDiffuse (getDiffuse (idx));
        light.setSpecular(getSpecular(idx));
    }

    if (getHasIntensity())
    {
        light.setIntensity(getIntensity(idx));
    }

    if (getHasAttenuation())
    {
        light.setAttenuation(getAttenuation(idx));
    }

    if (getHasDecayAttenuation())
    {
        light.setDecayAttenuation(getDecayAttenuation(idx));
    }

    if (getHasLengthFactor())
    {
        light.setLengthFactor(getLengthFactor(idx));
    }

    if (getHasRangeCutOn())
    {
        light.setRangeCutOn(getRangeCutOn(idx));
    }

    if (getHasRangeCutOff())
    {
        light.setRangeCutOff(getRangeCutOff(idx));
    }

    if (getHasRangeNearZone())
    {
        light.setRangeNearZone(getRangeNearZone(idx));
    }

    if (getHasRangeFarZone())
    {
        light.setRangeFarZone(getRangeFarZone(idx));
    }

    if (getHasSpotlightExponent())
    {
        light.setSpotlightExponent(getSpotlightExponent(idx));
    }
    else
    if (getHasSpotlightPenumbraAngle())
    {
        light.setSpotlightPenumbraAngle(getSpotlightPenumbraAngle(idx));
    }
    else
    if (getHasSpotlightPenumbraFactor())
    {
        light.setSpotlightPenumbraFactor(getSpotlightPenumbraFactor(idx));
    }

    if (getHasCinemaLight())
    {
        light.setInnerSuperEllipsesWidth  (getInnerSuperEllipsesWidth  (idx));
        light.setInnerSuperEllipsesHeight (getInnerSuperEllipsesHeight (idx));
        light.setOuterSuperEllipsesWidth  (getOuterSuperEllipsesWidth  (idx));
        light.setOuterSuperEllipsesHeight (getOuterSuperEllipsesHeight (idx));
        light.setSuperEllipsesRoundness   (getSuperEllipsesRoundness   (idx));
        light.setSuperEllipsesTwist       (getSuperEllipsesTwist       (idx));
    }

    if (getHasProjection())
    {
        light.setProjectionMatrix(getProjectionMatrix(idx));
    }

    if (getHasShadow())
    {
        light.setShadow              (getShadow              (idx));
        light.setShadowDataIndex     (getShadowDataIndex     (idx));
        light.setShadowParameterIndex(getShadowParameterIndex(idx));
    }

    return light;
}

void MultiLightChunk::removeLight(const UInt32 idx)
{
    OSG_ASSERT(check_invariant());

    if (idx >= _mfPosition.size())
        return;

    editMField(PositionFieldMask,           _mfPosition);
    editMField(DirectionFieldMask,          _mfDirection);
    editMField(SpotlightAngleFieldMask,     _mfSpotlightAngle);
    editMField(TypeOfLightFieldMask,        _mfTypeOfLight);
    editMField(EnabledFieldMask,            _mfEnabled);
    editMField(BeaconFieldMask,             _mfBeacon);
    editMField(BeaconMatrixFieldMask,       _mfBeaconMatrix);

    _mfPosition.        erase(idx);
    _mfDirection.       erase(idx);
    _mfSpotlightAngle.  erase(idx);
    _mfTypeOfLight.     erase(idx);
    _mfEnabled.         erase(idx);
    _mfBeacon.          erase(idx);
    _mfBeaconMatrix.    erase(idx);

    if (getHasSeparateIntensities())
    {
        editMField(AmbientIntensityFieldMask,   _mfAmbientIntensity);
        editMField(DiffuseIntensityFieldMask,   _mfDiffuseIntensity);
        editMField(SpecularIntensityFieldMask,  _mfSpecularIntensity);

        _mfAmbientIntensity. erase(idx);
        _mfDiffuseIntensity. erase(idx);
        _mfSpecularIntensity.erase(idx);
    }

    if (getHasIntensity())
    {
        editMField(IntensityFieldMask,          _mfIntensity);
        _mfIntensity.erase(idx);
    }

    if (getHasAttenuation())
    {
        editMField(AttenuationFieldMask,        _mfAttenuation);
        _mfAttenuation.erase(idx);
    }

    if (getHasDecayAttenuation())
    {
        editMField(DecayAttenuationFieldMask,   _mfDecayAttenuation);
        _mfDecayAttenuation.erase(idx);
    }

    if (getHasLengthFactor())
    {
        editMField(LengthFactorFieldMask,   _mfLengthFactor);
        _mfLengthFactor.erase(idx);
    }

    if (getHasRangeCutOn())
    {
        editMField(RangeCutOnFieldMask,         _mfRangeCutOn);
        _mfRangeCutOn.erase(idx);
    }

    if (getHasRangeCutOff())
    {
        editMField(RangeCutOffFieldMask,        _mfRangeCutOff);
        _mfRangeCutOff.erase(idx);
    }

    if (getHasRangeNearZone())
    {
        editMField(RangeNearZoneFieldMask,      _mfRangeNearZone);
        _mfRangeNearZone.erase(idx);
    }

    if (getHasRangeFarZone())
    {
        editMField(RangeFarZoneFieldMask,       _mfRangeFarZone);
        _mfRangeFarZone.erase(idx);
    }

    if (getHasSpotlightExponent() || getHasSpotlightPenumbraAngle() || getHasSpotlightPenumbraFactor())
    {
        editMField(SpotExponentFieldMask,       _mfSpotExponent);
        _mfSpotExponent.erase(idx);
    }

    if (getHasCinemaLight())
    {
        editMField(InnerSuperEllipsesWidthFieldMask,    _mfInnerSuperEllipsesWidth);
        editMField(InnerSuperEllipsesHeightFieldMask,   _mfInnerSuperEllipsesHeight);
        editMField(OuterSuperEllipsesWidthFieldMask,    _mfOuterSuperEllipsesWidth);
        editMField(OuterSuperEllipsesHeightFieldMask,   _mfOuterSuperEllipsesHeight);
        editMField(SuperEllipsesRoundnessFieldMask,     _mfSuperEllipsesRoundness);
        editMField(SuperEllipsesTwistFieldMask,         _mfSuperEllipsesTwist);

        _mfInnerSuperEllipsesWidth. erase(idx);
        _mfInnerSuperEllipsesHeight.erase(idx);
        _mfOuterSuperEllipsesWidth. erase(idx);
        _mfOuterSuperEllipsesHeight.erase(idx);
        _mfSuperEllipsesRoundness.  erase(idx);
        _mfSuperEllipsesTwist.      erase(idx);
    }

    if (getHasProjection())
    {
        editMField(ProjectionMatrixFieldMask, _mfProjectionMatrix);
        _mfProjectionMatrix.erase(idx);
    }

    if (getHasShadow())
    {
        editMField(ShadowFieldMask,               _mfShadow);
        editMField(ShadowDataIndexFieldMask,      _mfShadowDataIndex);
        editMField(ShadowParameterIndexFieldMask, _mfShadowParameterIndex);

        _mfShadow              .erase(idx);
        _mfShadowDataIndex     .erase(idx);
        _mfShadowParameterIndex.erase(idx);
    }
   
    OSG_ASSERT(check_invariant());
}

void MultiLightChunk::clearLights()
{
    editMField(PositionFieldMask,                   _mfPosition);
    editMField(DirectionFieldMask,                  _mfDirection);
    editMField(IntensityFieldMask,                  _mfIntensity);
    editMField(AmbientIntensityFieldMask,           _mfAmbientIntensity);
    editMField(DiffuseIntensityFieldMask,           _mfDiffuseIntensity);
    editMField(SpecularIntensityFieldMask,          _mfSpecularIntensity);
    editMField(AttenuationFieldMask,                _mfAttenuation);
    editMField(DecayAttenuationFieldMask,           _mfDecayAttenuation);
    editMField(LengthFactorFieldMask,               _mfLengthFactor);
    editMField(RangeCutOnFieldMask,                 _mfRangeCutOn);
    editMField(RangeCutOffFieldMask,                _mfRangeCutOff);
    editMField(RangeNearZoneFieldMask,              _mfRangeNearZone);
    editMField(RangeFarZoneFieldMask,               _mfRangeFarZone);
    editMField(SpotlightAngleFieldMask,             _mfSpotlightAngle);
    editMField(SpotExponentFieldMask,               _mfSpotExponent);
    editMField(InnerSuperEllipsesWidthFieldMask,    _mfInnerSuperEllipsesWidth);
    editMField(InnerSuperEllipsesHeightFieldMask,   _mfInnerSuperEllipsesHeight);
    editMField(OuterSuperEllipsesWidthFieldMask,    _mfOuterSuperEllipsesWidth);
    editMField(OuterSuperEllipsesHeightFieldMask,   _mfOuterSuperEllipsesHeight);
    editMField(SuperEllipsesRoundnessFieldMask,     _mfSuperEllipsesRoundness);
    editMField(SuperEllipsesTwistFieldMask,         _mfSuperEllipsesTwist);
    editMField(ProjectionMatrixFieldMask,           _mfProjectionMatrix);
    editMField(TypeOfLightFieldMask,                _mfTypeOfLight);
    editMField(EnabledFieldMask,                    _mfEnabled);
    editMField(ShadowFieldMask,                     _mfShadow);
    editMField(ShadowDataIndexFieldMask,            _mfShadowDataIndex);
    editMField(ShadowParameterIndexFieldMask,       _mfShadowParameterIndex);
    editMField(BeaconFieldMask,                     _mfBeacon);
    editMField(BeaconMatrixFieldMask,               _mfBeaconMatrix);

    _mfPosition.                clear();
    _mfDirection.               clear();
    _mfIntensity.               clear();
    _mfAmbientIntensity.        clear();
    _mfDiffuseIntensity.        clear();
    _mfSpecularIntensity.       clear();
    _mfAttenuation.             clear();
    _mfDecayAttenuation.        clear();
    _mfLengthFactor.            clear();
    _mfRangeCutOn.              clear();
    _mfRangeCutOff.             clear();
    _mfRangeNearZone.           clear();
    _mfRangeFarZone.            clear();
    _mfSpotlightAngle.          clear();
    _mfSpotExponent.            clear();
    _mfInnerSuperEllipsesWidth. clear();
    _mfInnerSuperEllipsesHeight.clear();
    _mfOuterSuperEllipsesWidth. clear();
    _mfOuterSuperEllipsesHeight.clear();
    _mfSuperEllipsesRoundness.  clear();
    _mfSuperEllipsesTwist.      clear();
    _mfProjectionMatrix.        clear();
    _mfTypeOfLight.             clear();
    _mfEnabled.                 clear();
    _mfShadow.                  clear();
    _mfShadowDataIndex.         clear();
    _mfShadowParameterIndex.    clear();
    _mfBeacon.                  clear();
    _mfBeaconMatrix.            clear();
}

void MultiLightChunk::enableLights(bool flag)
{
    UInt32 num_lights = getNumLights();
    for (UInt32 idx = 0; idx < num_lights; ++idx)
    {
        setEnabled(idx, flag);
    }
}

void MultiLightChunk::setLayoutType(UInt32 layout)
{
    setAutoCalcRanges               (false);

    setHasIntensity                 (false);
    setHasSeparateIntensities       (false);
    setHasAttenuation               (false);
    setHasDecayAttenuation          (false);
    setHasLengthFactor              (false);
    setHasRangeCutOn                (false);
    setHasRangeCutOff               (false);
    setHasRangeNearZone             (false);
    setHasRangeFarZone              (false);

    setHasCosSpotlightAngle         (true);
    setHasSpotlightAngle            (false);
    setHasSpotlightExponent         (false);
    setHasSpotlightPenumbraAngle    (false);
    setHasSpotlightPenumbraFactor   (false);
    setHasSpotlightPenumbraFrostbite(false);

    setHasCinemaLight               (false);
    setHasShadow                    (false);
    setHasGlobalAmbientIntensity    (false);

    if (layout & MultiLight::SIMPLE_LAYOUT)
    {
        setHasIntensity             (true);
        setHasRangeCutOff           (true);
    }

    if (layout & MultiLight::RANGE_LAYOUT)
    {
        setHasRangeCutOn            (true);
        setHasRangeCutOff           (true);
    }

    if (layout & MultiLight::ZONE_LAYOUT)
    {
        setHasRangeNearZone         (true);
        setHasRangeFarZone          (true);
    }

    if (layout & MultiLight::OPENGL_LAYOUT)
    {
        setHasSeparateIntensities   (true);
        setHasAttenuation           (true);
        setHasSpotlightExponent     (true);
    }

    if (layout & MultiLight::CINEMA_LAYOUT)
    {
        setHasCinemaLight           (true);
    }

    if (layout & MultiLight::SHADOW_LAYOUT)
    {
        setHasShadow                (true);
    }

    if (layout & MultiLight::GLOBAL_LAYOUT)
    {
        setHasGlobalAmbientIntensity(true);
    }

    if (layout & MultiLight::PHYSICAL_LAYOUT)
    {
        setHasIntensity              (true);
        setHasRangeCutOn             (true);
        setHasRangeCutOff            (true);
        setHasAttenuation            (true);
        setHasDecayAttenuation       (true);
        setHasLengthFactor           (true);
        setHasSpotlightExponent      (true);
        setHasShadow                 (true);
        setHasGlobalAmbientIntensity (true);
    }

    clearLights();
}

void MultiLightChunk::force_invariant()
{
    std::size_t sz = _mfPosition.size();

    MultiLight init_light(MultiLight::POINT_LIGHT);

    if (getHasSeparateIntensities())
    {
        if (sz != _mfAmbientIntensity.size())
        {
            std::size_t sz_old = _mfAmbientIntensity.size();

            editMField(AmbientIntensityFieldMask, _mfAmbientIntensity);
            _mfAmbientIntensity.resize(sz, init_light.getAmbient());
            
        }
        if (sz != _mfDiffuseIntensity.size())
        {
            std::size_t sz_old = _mfDiffuseIntensity.size();

            editMField(DiffuseIntensityFieldMask, _mfDiffuseIntensity);
            _mfDiffuseIntensity.resize(sz, init_light.getDiffuse());
        }
        if (sz != _mfSpecularIntensity.size())
        {
            std::size_t sz_old = _mfSpecularIntensity.size();

            editMField(SpecularIntensityFieldMask, _mfSpecularIntensity);
            _mfSpecularIntensity.resize(sz, init_light.getSpecular());
        }
    }

    if (getHasIntensity() && sz != _mfIntensity.size())
    {
        std::size_t sz_old = _mfIntensity.size();

        editMField(IntensityFieldMask, _mfIntensity);
        _mfIntensity.resize(sz, init_light.getIntensity());
    }

    if (getHasAttenuation() && sz != _mfAttenuation.size())
    {
        std::size_t sz_old = _mfAttenuation.size();

        editMField(AttenuationFieldMask, _mfAttenuation);
        _mfAttenuation.resize(sz, init_light.getAttenuation());
    }

    if (getHasDecayAttenuation() && sz != _mfDecayAttenuation.size())
    {
        std::size_t sz_old = _mfDecayAttenuation.size();

        editMField(DecayAttenuationFieldMask, _mfDecayAttenuation);
        _mfDecayAttenuation.resize(sz, init_light.getDecayAttenuation());
    }

    if (getHasLengthFactor() && sz != _mfLengthFactor.size())
    {
        std::size_t sz_old = _mfLengthFactor.size();

        editMField(LengthFactorFieldMask, _mfLengthFactor);
        _mfLengthFactor.resize(sz, init_light.getLengthFactor());
    }

    if (getHasRangeCutOn() && sz != _mfRangeCutOn.size())
    {
        std::size_t sz_old = _mfRangeCutOn.size();

        editMField(RangeCutOnFieldMask, _mfRangeCutOn);
        _mfRangeCutOn.resize(sz, init_light.getRangeCutOn());
    }

    if (getHasRangeCutOff() && sz != _mfRangeCutOff.size())
    {
        std::size_t sz_old = _mfRangeCutOff.size();

        editMField(RangeCutOffFieldMask, _mfRangeCutOff);
        _mfRangeCutOff.resize(sz, init_light.getRangeCutOff());
    }

    if (getHasRangeNearZone() && sz != _mfRangeNearZone.size())
    {
        std::size_t sz_old = _mfRangeNearZone.size();

        editMField(RangeNearZoneFieldMask, _mfRangeNearZone);
        _mfRangeNearZone.resize(sz, init_light.getRangeNearZone());
    }

    if (getHasRangeFarZone() && sz != _mfRangeFarZone.size())
    {
        std::size_t sz_old = _mfRangeFarZone.size();

        editMField(RangeFarZoneFieldMask, _mfRangeFarZone);
        _mfRangeFarZone.resize(sz, init_light.getRangeFarZone());
    }

    if (getHasProjection() && sz != _mfProjectionMatrix.size())
    {
        std::size_t sz_old = _mfProjectionMatrix.size();

        editMField(ProjectionMatrixFieldMask, _mfProjectionMatrix);
        _mfProjectionMatrix.resize(sz, init_light.getProjectionMatrix());
    }

    if (getHasSpotlightExponent() && sz != _mfSpotExponent.size())
    {
        std::size_t sz_old = _mfSpotExponent.size();

        editMField(SpotExponentFieldMask, _mfSpotExponent);
        _mfSpotExponent.resize(sz, init_light.getSpotlightExponent());
    }
    else
    if (getHasSpotlightPenumbraAngle() && sz != _mfSpotExponent.size())
    {
        std::size_t sz_old = _mfSpotExponent.size();

        editMField(SpotExponentFieldMask, _mfSpotExponent);
        _mfSpotExponent.resize(sz, init_light.getSpotlightPenumbraAngle());
    }
    else
    if (getHasSpotlightPenumbraFactor() && sz != _mfSpotExponent.size())
    {
        std::size_t sz_old = _mfSpotExponent.size();

        editMField(SpotExponentFieldMask, _mfSpotExponent);
        _mfSpotExponent.resize(sz, init_light.getSpotlightPenumbraFactor());
    }

    if (getHasCinemaLight())
    {
        if (sz != _mfInnerSuperEllipsesWidth.size())
        {
            std::size_t sz_old = _mfInnerSuperEllipsesWidth.size();

            editMField(InnerSuperEllipsesWidthFieldMask, _mfInnerSuperEllipsesWidth);
            _mfInnerSuperEllipsesWidth.resize(sz, init_light.getInnerSuperEllipsesWidth());
        }
        if (sz != _mfInnerSuperEllipsesHeight.size())
        {
            std::size_t sz_old = _mfInnerSuperEllipsesHeight.size();

            editMField(InnerSuperEllipsesHeightFieldMask, _mfInnerSuperEllipsesHeight);
            _mfInnerSuperEllipsesHeight.resize(sz, init_light.getInnerSuperEllipsesHeight());
        }
        if (sz != _mfOuterSuperEllipsesWidth.size())
        {
            std::size_t sz_old = _mfOuterSuperEllipsesWidth.size();

            editMField(OuterSuperEllipsesWidthFieldMask, _mfOuterSuperEllipsesWidth);
            _mfOuterSuperEllipsesWidth.resize(sz, init_light.getOuterSuperEllipsesWidth());
        }
        if (sz != _mfOuterSuperEllipsesHeight.size())
        {
            std::size_t sz_old = _mfOuterSuperEllipsesHeight.size();

            editMField(OuterSuperEllipsesHeightFieldMask, _mfOuterSuperEllipsesHeight);
            _mfOuterSuperEllipsesHeight.resize(sz, init_light.getOuterSuperEllipsesHeight());
        }
        if (sz != _mfSuperEllipsesRoundness.size())
        {
            std::size_t sz_old = _mfSuperEllipsesRoundness.size();

            editMField(SuperEllipsesRoundnessFieldMask, _mfSuperEllipsesRoundness);
            _mfSuperEllipsesRoundness.resize(sz, init_light.getSuperEllipsesRoundness());
        }
        if (sz != _mfSuperEllipsesTwist.size())
        {
            std::size_t sz_old = _mfSuperEllipsesTwist.size();

            editMField(SuperEllipsesTwistFieldMask, _mfSuperEllipsesTwist);
            _mfSuperEllipsesTwist.resize(sz, init_light.getSuperEllipsesTwist());
        }
    }

    if (getHasShadow())
    {
        if (sz != _mfShadowDataIndex.size())
        {
            std::size_t sz_old = _mfShadowDataIndex.size();

            editMField(ShadowDataIndexFieldMask, _mfShadowDataIndex);
            _mfShadowDataIndex.resize(sz, init_light.getShadowDataIndex());
        }
        if (sz != _mfShadowParameterIndex.size())
        {
            std::size_t sz_old = _mfShadowParameterIndex.size();

            editMField(ShadowParameterIndexFieldMask, _mfShadowParameterIndex);
            _mfShadowParameterIndex.resize(sz, init_light.getShadowParameterIndex());
        }
        if (sz != _mfShadow.size())
        {
            std::size_t sz_old = _mfShadow.size();

            editMField(ShadowFieldMask, _mfShadow);
            _mfShadow.resize(sz, init_light.getShadow());
        }
    }

    if (sz != _mfDirection.size())
    {
        std::size_t sz_old = _mfDirection.size();

        editMField(DirectionFieldMask, _mfDirection);
        _mfDirection.resize(sz, init_light.getDirection());
    }
    if (sz != _mfSpotlightAngle.size())
    {
        std::size_t sz_old = _mfSpotlightAngle.size();

        editMField(SpotlightAngleFieldMask, _mfSpotlightAngle);
        _mfSpotlightAngle.resize(sz, init_light.getSpotlightAngle());
    }
    if (sz != _mfTypeOfLight.size())
    {
        std::size_t sz_old = _mfTypeOfLight.size();

        editMField(TypeOfLightFieldMask, _mfTypeOfLight);
        _mfTypeOfLight.resize(sz, init_light.getTypeOfLight());
    }
    if (sz != _mfEnabled.size())
    {
        std::size_t sz_old = _mfEnabled.size();

        editMField(EnabledFieldMask, _mfEnabled);
        _mfEnabled.resize(sz, init_light.getEnabled());
    }
    if (sz != _mfBeacon.size())
    {
        std::size_t sz_old = _mfBeacon.size();

        editMField(BeaconFieldMask, _mfBeacon);
        _mfBeacon.resize(sz, init_light.getBeacon());
    }
    if (sz != _mfBeaconMatrix.size())
    {
        std::size_t sz_old = _mfBeaconMatrix.size();

        editMField(BeaconFieldMask, _mfBeaconMatrix);
        _mfBeaconMatrix.resize(sz, Matrix());
    }
}

std::string MultiLightChunk::getFragmentProgramSnippet(bool add_attenuation_code, bool add_ubo_code) const
{
    using namespace std;

    stringstream ost;

    ost
    << endl <<     "//"
    << endl <<     "// The supported light types"
    << endl <<     "//"
    << endl <<     "const int POINT_LIGHT       = " << MultiLight::POINT_LIGHT       << ";"
    << endl <<     "const int DIRECTIONAL_LIGHT = " << MultiLight::DIRECTIONAL_LIGHT << ";"
    << endl <<     "const int SPOT_LIGHT        = " << MultiLight::SPOT_LIGHT        << ";"
    << endl <<     "const int CINEMA_LIGHT      = " << MultiLight::CINEMA_LIGHT      << ";"
    << endl <<     ""
    ;

    if (getHasGlobalAmbientIntensity())
    {
        ost
        << endl << "//"
        << endl << "// The multi light type declaration"
        << endl << "//"
        << endl << "struct GlobalLightState"
        << endl << "{"
        ;

        if (getHasGlobalAmbientIntensity())
        {
            ost
            << endl << "    vec3  ambientIntensity;"
            ;
        }

        ost
        << endl << "};"
        << endl << ""
        ;
    }


    ost
    << endl <<     "//"
    << endl <<     "// The multi light type declaration"
    << endl <<     "//"
    << endl <<     "struct Light"
    << endl <<     "{"
    ;

    if (getHasLightSpaceFromWorldSpaceMatrix())
    {
        ost
        << endl << "    mat4  matLSFromWS;"
        ;
    }
    if (getHasWorldSpaceFromLightSpaceMatrix())
    {
        ost
        << endl << "    mat4  matWSFromLS;"
        ;
    }
    if (getHasLightSpaceFromEyeSpaceMatrix())
    {
        ost
        << endl << "    mat4  matLSFromES;"
        ;
    }
    if (getHasEyeSpaceFromLightSpaceMatrix())
    {
        ost
        << endl << "    mat4  matESFromLS;"
        ;
    }
    if (getHasProjectionMatrix())
    {
        ost
        << endl << "    mat4  matProjection;"
        ;
    }
    if (getHasInvProjectionMatrix())
    {
        ost
        << endl << "    mat4  matInvProjection;"
        ;
    }
    if (getHasProjectionLightSpaceFromWorldSpaceMatrix())
    {
        ost
        << endl << "    mat4  matProjLSFromWS;"
        ;
    }
    if (getHasInvProjectionLightSpaceFromWorldSpaceMatrix())
    {
        ost
        << endl << "    mat4  matInvProjLSFromWS;"
        ;
    }
    if (getHasProjectionLightSpaceFromEyeSpaceMatrix())
    {
        ost
        << endl << "    mat4  matProjLSFromES;"
        ;
    }
    if (getHasInvProjectionLightSpaceFromEyeSpaceMatrix())
    {
        ost
        << endl << "    mat4  matInvProjLSFromES;"
        ;
    }

    ost 
    << endl <<     "    vec3  position;                 // in " << (getEyeSpace() ? "eye" : "world") << " space"
    << endl <<     "    vec3  direction;                // in " << (getEyeSpace() ? "eye" : "world") << " space"
    ;

    if (getHasSeparateIntensities())
    {
        ost
        << endl << "    vec3  ambientIntensity;"
        << endl << "    vec3  diffuseIntensity;"
        << endl << "    vec3  specularIntensity;"
        ;
    }

    if (getHasIntensity())
    {
        ost
        << endl << "    vec3  intensity;"
        ;
    }

    if (getHasAttenuation())
    {
        ost
        << endl << "    float constantAttenuation;"
        << endl << "    float linearAttenuation;"
        << endl << "    float quadraticAttenuation;"
        ;
    }

    if (getHasDecayAttenuation())
    {
        ost
        << endl << "    float decayAttenuation;"
        ;
    }

    if (getHasLengthFactor())
    {
        ost
        << endl << "    float lengthFactor;"
        ;
    }

    if (getHasRangeCutOn())
    {
        ost
        << endl << "    float rangeCutOn;"
        ;
    }

    if (getHasRangeCutOff())
    {
        ost
        << endl << "    float rangeCutOff;"
        ;
    }

    if (getHasRangeNearZone())
    {
        ost
        << endl << "    float rangeNearZone;"
        ;
    }

    if (getHasRangeFarZone())
    {
        ost
        << endl << "    float rangeFarZone;"
        ;
    }

    if (getHasCosSpotlightAngle() || (!getHasCosSpotlightAngle() && !getHasSpotlightAngle()))
    {
        ost
        << endl << "    float cosSpotlightAngle;"
        ;
    }

    if (getHasTanSpotlightAngle())
    {
        ost
        << endl << "    float tanSpotlightAngle;"
        ;
    }

    if (getHasSpotlightAngle())
    {
        ost
        << endl << "    float spotlightAngle;           // in radians"
        ;
    }

    if (getHasSpotlightExponent())
    {
        ost
        << endl << "    float spotlightExponent;"
        ;
    }
    else
    if (getHasSpotlightPenumbraFrostbite())
    {
        ost
        << endl << "    float spotlightScale;"
        << endl << "    float spotlightOffset;"
        ;
    }
    else
    if (getHasSpotlightPenumbraAngle() || getHasSpotlightPenumbraFactor())
    {
        ost
        << endl << "    float cosSpotlightPenumbraAngle;"
        ;
    }

    if (getHasCinemaLight())
    {
        ost
        << endl << "    float innerSuperEllipsesWidth;  // a" 
        << endl << "    float innerSuperEllipsesHeight; // b"
        << endl << "    float outerSuperEllipsesWidth;  // A"
        << endl << "    float outerSuperEllipsesHeight; // B"
        << endl << "    float superEllipsesRoundness;   // r"
        << endl << "    float superEllipsesTwist;       // twist angle theta in radians"
        ;
    }

    ost
    << endl <<     "    int   type;                     // specific type of light: POINT_LIGHT, DIRECTIONAL_LIGHT, SPOT_LIGHT or CINEMA_LIGHT"
    << endl <<     "    bool  enabled;                  // on/off state of light"
    ;

    if (getHasShadow())
    {
        ost
        << endl << "    bool  shadow;                   // shadow on/off state of light"
        << endl << "    int   shadowDataIndex;          // index into shadow data technique array"
        << endl << "    int   shadowParameterIndex;     // index into shadow parameter array"
        ;
    }

    ost
    << endl <<     "};"
    ;

    if (add_ubo_code)
    {
        ost
        << endl << ""
        << getLightUBOProgSnippet()
        ;
    }

    if (add_attenuation_code)
    {
        ost
        << endl << ""
        << getAttenuationProgSnippet()
        ;
    }

    return ost.str();
}

std::string MultiLightChunk::getLightUBOProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl <<     "layout (std430) buffer " << getLightBlockName()
    << endl <<     "{"
    ;
    if (getHasGlobalAmbientIntensity())
    {
        ost
        << endl << "    GlobalLightState global;"
        << endl << "    Light            light[];"
        ;
    }
    else
    {
        ost
        << endl << "    Light light[];"
        ;
    }
    ost
    << endl <<     "} " << getLightVariableName() << ";"
    << endl <<     ""
    ;
    if (getHasGlobalAmbientIntensity())
    {
        if (getHasGlobalAmbientIntensity())
        {
            ost
            << endl << "vec3 globalAmbientIntensity()"
            << endl << "{"
            << endl << "    return " << getLightVariableName() << ".global.ambientIntensity;"
            << endl << "}"
            << endl << ""
            ;
        }
    }
    ost
    << endl <<     "Light getLight(in int idx)"
    << endl <<     "{"
                        // Remark: Older AMD/ATI driver struggle if the light is directly returned from the
                        //         light buffer/array.
    << endl <<     "    Light light = " << getLightVariableName() << ".light[idx];"
    << endl <<     "    return light;"
    << endl <<     "}"
    << endl <<     ""
    << endl <<     "struct OutgoingLight"
    << endl <<     "{"
    << endl <<     "    vec3 directDiffuse;"
    << endl <<     "    vec3 directSpecular;"
    << endl <<     "    vec3 indirectDiffuse;"
    << endl <<     "    vec3 indirectSpecular;"
    << endl <<     "    vec3 emissiveRadiance;"
    << endl <<     "};"
    << endl <<     ""
    << endl <<     "OutgoingLight outLight;"
    ;

    return ost.str();
}

std::string MultiLightChunk::getDistanceAttenuationClassicProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// Calculate the attenuation of the light based on its"
    << endl << "// constant, linear and quadratic attenuation factors"
    << endl << "// and the distance d of the light to the current point."
    << endl << "//"
    << endl << "float calcAttenuation("
    << endl << "    in float c,"
    << endl << "    in float l,"
    << endl << "    in float q,"
    << endl << "    in float d)"
    << endl << "{"
    << endl << "    return 1.0 / (q*d*d + l*d + c);"
    << endl << "}"
    ;

    return ost.str();
}

std::string MultiLightChunk::getDistanceAttenuationPhysicallyProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// Calculate the attenuation of the light based upon Frostbite 3 'Moving to Physically-based Rendering'"
    << endl << "// page 32, equation 26: https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf"
    << endl << "// with light range r (max d) and light fragment distance d."
    << endl << "//"
    << endl << "float calcAttenuation("
    << endl << "    in float r,"
    << endl << "    in float d)"
    << endl << "{"
    << endl << "    float sqrSize      = 0.0001;"
    << endl << "    float sqrDistMax   = r * r;"
    << endl << "    float sqrDist      = d * d;"
    << endl << "    float factor       = sqrDist / max(sqrDistMax, sqrSize);"
    << endl << "    float smoothFactor = clamp(1.0f - factor * factor, 0.0, 1.0);"
    << endl << "    float attenuation  = 1.0 / max(sqrDist, sqrSize);"
    << endl << "    return attenuation * smoothFactor * smoothFactor;"
    << endl << "}"
    ;

    return ost.str();
}

std::string MultiLightChunk::getDistanceAttenuationDecayProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// Calculate the attenuation of the light based upon Frostbite 3 'Moving to Physically-based Rendering'"
    << endl << "// page 32, equation 26: https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf"
    << endl << "// with light range r (max d), decay exponent a and light fragment distance d."
    << endl << "//"
    << endl << "float calcAttenuation("
    << endl << "    in float a,"
    << endl << "    in float r,"
    << endl << "    in float d)"
    << endl << "{"
    << endl << "    float sqrSize      = 0.0001;"
    << endl << "    float sqrDistMax   = r * r;"
    << endl << "    float sqrDist      = d * d;"
    << endl << "    float factor       = sqrDist / max(sqrDistMax, sqrSize);"
    << endl << "    float smoothFactor = clamp(1.0f - factor * factor, 0.0, 1.0);"
    << endl << "    float attenuation  = 1.0 / max(pow(d, a), pow(0.01, a));"
    << endl << "    return attenuation * smoothFactor * smoothFactor;"
    << endl << "}"
    ;

    return ost.str();
}

std::string MultiLightChunk::getDistanceAttenuationMixPhysicallyProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// Calculate the attenuation of the light based upon Frostbite 3 'Moving to Physically-based Rendering'"
    << endl << "// page 32, equation 26: https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf"
    << endl << "// with light range r (max d) and light fragment distance d. Additionally, a constant and linear factor is added for"
    << endl << "// compatibility to the classic attenuation formula."
    << endl << "//"
    << endl << "float calcAttenuation("
    << endl << "    in float c,"
    << endl << "    in float l,"
    << endl << "    in float q,"
    << endl << "    in float r,"
    << endl << "    in float d)"
    << endl << "{"
    << endl << "    float sqrSize      = 0.0001;"
    << endl << "    float sqrDistMax   = r * r;"
    << endl << "    float sqrDist      = d * d;"
    << endl << "    float factor       = sqrDist / max(sqrDistMax, sqrSize);"
    << endl << "    float smoothFactor = clamp(1.0f - factor * factor, 0.0, 1.0);"
    << endl << "    float attenuation  = 1.0 / (q * max(sqrDist, sqrSize) + l * d + c);"
    << endl << "    return attenuation * smoothFactor * smoothFactor;"
    << endl << "}"
    ;

    return ost.str();
}

std::string MultiLightChunk::getDistanceAttenuationMixDecayProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// Calculate the attenuation of the light based upon Frostbite 3 'Moving to Physically-based Rendering'"
    << endl << "// page 32, equation 26: https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf"
    << endl << "// with light range r (max d), decay exponent a and light fragment distance d. Additionally, a constant and linear"
    << endl << "// factor is added for compatibility to the classic attenuation formula."
    << endl << "//"
    << endl << "float calcAttenuation("
    << endl << "    in float c,"
    << endl << "    in float l,"
    << endl << "    in float q,"
    << endl << "    in float a,"
    << endl << "    in float r,"
    << endl << "    in float d)"
    << endl << "{"
    << endl << "    float sqrSize      = 0.0001;"
    << endl << "    float sqrDistMax   = r * r;"
    << endl << "    float sqrDist      = d * d;"
    << endl << "    float factor       = sqrDist / max(sqrDistMax, sqrSize);"
    << endl << "    float smoothFactor = clamp(1.0f - factor * factor, 0.0, 1.0);"
    << endl << "    float attenuation  = 1.0 / (q * max(pow(d, a), pow(0.01, a)) + l * d + c);"
    << endl << "    return attenuation * smoothFactor * smoothFactor;"
    << endl << "}"
    ;

    return ost.str();
}

std::string MultiLightChunk::getDistanceAttenuationSmoothHermiteProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// Calculate the attenuation of the light based on the light "
    << endl << "// range r and the distance d of the light to the current point."
    << endl << "//"
    << endl << "float calcAttenuation("
    << endl << "    in float r,"
    << endl << "    in float d)"
    << endl << "{"
    << endl << "    //"
    << endl << "    // Perform smooth Hermite interpolation between 0 and 1, when e0<x<e1"
    << endl << "    // float t = clamp((x-e0)/(e1-e0),0.0,1.0);"
    << endl << "    // smoothstep(e0,e1,x) = t*t*(3-2*t);"
    << endl << "    //"
    << endl << "    return 1.0 - smoothstep(0.75 * r, r, d);"
    << endl << "}"
    ;

    return ost.str();
}

std::string MultiLightChunk::getSpotAttenuationClassicProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// Calculate the attenuation with respect to the spot light cone."
    << endl << "// Parameters:"
    << endl << "//      coneCos  :  cosine of the spot cutoff angle"
    << endl << "//      exponent :  the spot exponent"
    << endl << "//      l        :  normalized direction between fragment and light position"
    << endl << "//      s        :  normalized light direction"
    << endl << "//"
    << endl << "float spotAttenuation("
    << endl << "    in float coneCos,"
    << endl << "    in float exponent,"
    << endl << "    in vec3  l,"
    << endl << "    in vec3  s)"
    << endl << "{"
    << endl << "    float attenuation = 0.0;"
    << endl << "    float l_dot_s = dot(-l, s);"
    << endl << "    if (l_dot_s >= coneCos)"
    << endl << "        attenuation = pow(l_dot_s, exponent);"
    << endl << "    return attenuation;"
    << endl << "}"
    ;

    return ost.str();
}

std::string MultiLightChunk::getSpotAttenuationSmoothHermiteProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// Calculate the attenuation with respect to the spot light cone."
    << endl << "// Parameters:"
    << endl << "//      coneCos: the cosine of the spot light angle"
    << endl << "//      l      :  normalized direction between fragment and light position"
    << endl << "//      s      :  normalized light direction"
    << endl << "//"
    << endl << "float spotAttenuation("
    << endl << "    in float coneCos,"
    << endl << "    in vec3  l,"
    << endl << "    in vec3  s)"
    << endl << "{"
    << endl << "    //"
    << endl << "    // Linear interpolate between x and y using weight a"
    << endl << "    // mix(x,y,a) = x*(1-a)+y*a"
    << endl << "    //"
    << endl << "    float penumbraCos = mix(coneCos, 1.0, 0.5);"
    << endl << "    float l_dot_s = dot(-l, s);"
    << endl << "    //"
    << endl << "    // Perform smooth Hermite interpolation between 0 and 1, when e0<x<e1"
    << endl << "    // float t = clamp((x-e0)/(e1-e0),0.0,1.0);"
    << endl << "    // smoothstep(e0,e1,x) = t*t*(3-2*t);"
    << endl << "    //"
    << endl << "    return smoothstep(coneCos, penumbraCos, l_dot_s);"
    << endl << "}"
    ;

    return ost.str();
}

std::string MultiLightChunk::getSpotAttenuationSmoothHermite2ProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// Calculate the attenuation with respect to the spot light cone."
    << endl << "// Parameters:"
    << endl << "//      coneCos    :  the cosine of the spot light angle"
    << endl << "//      penumbraCos:  the cosine of the penumbra spot light angle"
    << endl << "//      l          :  normalized direction between fragment and light position"
    << endl << "//      s          :  normalized light direction"
    << endl << "//"
    << endl << "float spotAttenuation("
    << endl << "    in float coneCos,"
    << endl << "    in float penumbraCos,"
    << endl << "    in vec3  l,"
    << endl << "    in vec3  s)"
    << endl << "{"
    << endl << "    float l_dot_s = dot(-l, s);"
    << endl << "    return smoothstep(coneCos, penumbraCos, l_dot_s);"
    << endl << "}"
    ;

    return ost.str();
}

std::string MultiLightChunk::getSpotAttenuationFrostbiteProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// Calculate the attenuation with respect to the spot light cone."
    << endl << "// Parameters:"
    << endl << "//      scale :  = 1.0f / max (0.001f, (penumbraCos  - coneCos)); // Calc on CPU"
    << endl << "//      offset:  = -coneCos * scale;                              // Calc on CPU"
    << endl << "//      l     :  normalized direction between fragment and light position"
    << endl << "//      s     :  normalized light direction"
    << endl << "//"
    << endl << "float spotAttenuation("
    << endl << "    in float scale,"
    << endl << "    in float offset,"
    << endl << "    in vec3  l,"
    << endl << "    in vec3  s)"
    << endl << "{"
    << endl << "    float l_dot_s = dot(-l, s);"
    << endl << "    return clamp(l_dot_s * scale + offset, 0.0, 1.0);"
    << endl << "}"
    ;

    return ost.str();
}

std::string MultiLightChunk::getCinemaAttenuationProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// cinema (uber) light super ellipses clipping"
    << endl << "// Parameters:"
    << endl << "//      a     :  inner super ellipses width"
    << endl << "//      b     :  inner super ellipses height"
    << endl << "//      A     :  outer super ellipses width"
    << endl << "//      B     :  outer super ellipses height"
    << endl << "//      r     :  roundness parameter"
    << endl << "//      theta :  twist parameter"
    << endl << "//      pos   :  fragment position in light space"
    << endl << "//"
    << endl << "//      |x/a|^r + |y/b|^r = 1 <=> a*b*(|b*x|^r + |a*y|^r)^(-1/r) = 1"
    << endl << "//"
    << endl << "// smoothstep(e0,e1,x)"
    << endl << "//      Perform smooth Hermite interpolation between 0 and 1, when e0<x<e1"
    << endl << "//      float t = clamp((x-e0)/(e1-e0),0.0,1.0);"
    << endl << "//      smoothstep(e0,e1,x) = t*t*(3-2*t);"
    << endl << "//"
    << endl << "float clipSuperEllipses("
    << endl << "    in float a,"
    << endl << "    in float b,"
    << endl << "    in float A,"
    << endl << "    in float B,"
    << endl << "    in float r,"
    << endl << "    in float theta,"
    << endl << "    in vec3 pos)"
    << endl << "{"
    << endl << "    if (pos.z > 0.0)"
    << endl << "        return 0.0;"
    << endl << ""
    << endl << "    vec2 P = pos.xy / pos.z;"
    << endl << "    if (all(equal(P, vec2(0.0, 0.0))))"
    << endl << "        return 1.0;"
    << endl << ""
    << endl << "    float cos_theta = cos(-theta);"
    << endl << "    float sin_theta = sin(-theta);"
    << endl << ""
    << endl << "    float x =  abs(cos_theta * P.x - sin_theta * P.y);"
    << endl << "    float y =  abs(sin_theta * P.x + cos_theta * P.y);"
    << endl << ""
    << endl << "    float result = 1.0;"
    << endl << ""
    << endl << "    if (r > 50) // basically a square"
    << endl << "    {"
    << endl << "        // Simpler case of a square"
    << endl << "        result = (1.0 - smoothstep(a, A, x)) * (1.0 - smoothstep(b, B, y));"
    << endl << "    }"
    << endl << "    else"
    << endl << "    {"
    << endl << "        float q = pow(x/a, r) + pow(y/b, r);"
    << endl << "        float Q = pow(x/A, r) + pow(y/B, r);"
    << endl << ""
    << endl << "        if (q <  1) return 1.0;"
    << endl << "        if (Q >= 1) return 0.0;"
    << endl << ""
    << endl << "        result = 1.0 - smoothstep(q, Q, 1.0);"
    << endl << "    }"
    << endl << ""
    << endl << "    return clamp(result, 0.0, 1.0);"
    << endl << "}"
    ;

    return ost.str();
}

std::string MultiLightChunk::getAttenuationProgSnippet() const
{
    using namespace std;

    stringstream ost;

    //
    // Distance attenuation
    //
    if (getCodeDistanceAttenuationClassic() && getHasAttenuation())
    {
        ost
        << endl << getDistanceAttenuationClassicProgSnippet()
        << endl << ""
        ;
    }
    else if (getCodeDistanceAttenuationPhysical() && getHasRangeCutOff())
    {
        ost
        << endl << getDistanceAttenuationPhysicallyProgSnippet()
        << endl << ""
        ;
    }
    else if (getCodeDistanceAttenuationDecay() && getHasRangeCutOff() && getHasDecayAttenuation())
    {
        ost
        << endl << getDistanceAttenuationDecayProgSnippet()
        << endl << ""
        ;
    }
    else if (getCodeDistanceAttenuationMixPhysical() && getHasRangeCutOff() && getHasAttenuation())
    {
        ost
        << endl << getDistanceAttenuationMixPhysicallyProgSnippet()
        << endl << ""
        ;
    }
    else if (getCodeDistanceAttenuationMixDecay() && getHasRangeCutOff() && getHasAttenuation() && getHasDecayAttenuation())
    {
        ost
        << endl << getDistanceAttenuationMixDecayProgSnippet()
        << endl << ""
        ;
    }
    else if (getCodeDistanceAttenuationSmoothHermite() && getHasRangeCutOff())
    {
        ost
        << endl << getDistanceAttenuationSmoothHermiteProgSnippet()
        << endl << ""
        ;
    }
    else if (getHasAttenuation())
    {
        ost
        << endl << getDistanceAttenuationClassicProgSnippet()
        << endl << ""
        ;
    }
    else if (getHasRangeCutOff())
    {
        ost
        << endl << getDistanceAttenuationSmoothHermiteProgSnippet()
        << endl << ""
        ;
    }

    //
    // Spot attenuation
    //
    if (getCodeSpotAttenuationClassic())
    {
        ost
        << endl << getSpotAttenuationClassicProgSnippet()
        << endl << ""
        ;
    }
    else if (getCodeSpotAttenuationSmoothHermite())
    {
        ost
        << endl << getSpotAttenuationSmoothHermiteProgSnippet()
        << endl << ""
        ;
    }
    else if (getCodeSpotAttenuationSmoothHermite2())
    {
        ost
        << endl << getSpotAttenuationSmoothHermite2ProgSnippet()
        << endl << ""
        ;
    }
    else if (getCodeSpotAttenuationFrostbite())
    {
        ost
        << endl << getSpotAttenuationFrostbiteProgSnippet()
        << endl << ""
        ;
    }
    else if (getHasAttenuation())
    {
        ost
        << endl << getSpotAttenuationClassicProgSnippet()
        << endl << ""
        ;
    }
    else
    {
        ost
        << endl << getSpotAttenuationSmoothHermiteProgSnippet()
        << endl << ""
        ;
    }

    //
    // Cinema attenuation
    //
    if (getHasCinemaLight())
    {
        ost
        << endl << getCinemaAttenuationProgSnippet()
        << endl << ""
        ;
    }

    return ost.str();
}

OSG_END_NAMESPACE
