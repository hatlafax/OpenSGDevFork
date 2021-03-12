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

#ifndef _OSGMULTILIGHTGROUP_H_
#define _OSGMULTILIGHTGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMultiLightGroupBase.h"
#include "OSGMultiLightChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief MultiLightGroup class. See \ref
           PageSystemMultiLightGroup for a description.
*/

class OSG_SYSTEM_DLLMAPPING MultiLightGroup : public MultiLightGroupBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MultiLightGroupBase Inherited;
    typedef MultiLightGroup     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Interface                               */
    /*! \{                                                                 */
          void                 setLayoutType                    (UInt32 layout);

          UInt32               getNumLights                     () const;
          UInt32               addLight                         (MultiLight::TypeOfLight eTypeOfLight);
          UInt32               addLight                         (const MultiLight& light);
          void                 updateLight                      (const UInt32 idx, const MultiLight& light);
          MultiLight           getLight                         (const UInt32 idx);
          void                 removeLight                      (const UInt32 idx);
          void                 clearLights                      ();
          bool                 empty                            () const;
          void                 enableLights                     (bool flag);

    const Pnt3f&                   getPosition                      (const UInt32 idx) const;
    const Vec3f&                   getDirection                     (const UInt32 idx) const;
    const Vec3f&                   getIntensity                     (const UInt32 idx) const;
    const Vec3f&                   getAmbient                       (const UInt32 idx) const;
    const Vec3f&                   getDiffuse                       (const UInt32 idx) const;
    const Vec3f&                   getSpecular                      (const UInt32 idx) const;
    const Vec3f&                   getAttenuation                   (const UInt32 idx) const;
          Real32                   getDecayAttenuation              (const UInt32 idx) const;
          Real32                   getLengthFactor                  (const UInt32 idx) const;
          Real32                   getRange                         (const UInt32 idx) const;
          Real32                   getSpotlightAngle                (const UInt32 idx) const;
          Real32                   getSpotlightParameter            (const UInt32 idx) const;
          Real32                   getSpotlightExponent             (const UInt32 idx) const;
          Real32                   getSpotlightPenumbraAngle        (const UInt32 idx) const;
          Real32                   getSpotlightPenumbraFactor       (const UInt32 idx) const;
          Real32                   getInnerSuperEllipsesWidth       (const UInt32 idx) const;
          Real32                   getInnerSuperEllipsesHeight      (const UInt32 idx) const;
          Real32                   getOuterSuperEllipsesWidth       (const UInt32 idx) const;
          Real32                   getOuterSuperEllipsesHeight      (const UInt32 idx) const;
          Real32                   getSuperEllipsesRoundness        (const UInt32 idx) const;
          Real32                   getSuperEllipsesTwist            (const UInt32 idx) const;
          Real32                   getRangeCutOn                    (const UInt32 idx) const;
          Real32                   getRangeCutOff                   (const UInt32 idx) const;
          Real32                   getRangeNearZone                 (const UInt32 idx) const;
          Real32                   getRangeFarZone                  (const UInt32 idx) const;
          MultiLight::TypeOfLight  getTypeOfLight                   (const UInt32 idx) const;
          bool                     getEnabled                       (const UInt32 idx) const;
          bool                     getShadow                        (const UInt32 idx) const;
          Int32                    getShadowDataIndex               (const UInt32 idx) const;
          Int32                    getShadowParameterIndex          (const UInt32 idx) const;
          Node*                    getBeacon                        (const UInt32 idx) const;

          void                 setPosition                      (const UInt32 idx, const Pnt3f& position);
          void                 setDirection                     (const UInt32 idx, const Vec3f& direction);
          void                 setIntensity                     (const UInt32 idx, const Vec3f& intensity);
          void                 setIntensity                     (const UInt32 idx, const Color3f& color);
          void                 setIntensity                     (const UInt32 idx, Real32 red, Real32 green, Real32 blue);
          void                 setAmbient                       (const UInt32 idx, const Vec3f& intensity);
          void                 setAmbient                       (const UInt32 idx, const Color3f& color);
          void                 setAmbient                       (const UInt32 idx, Real32 red, Real32 green, Real32 blue);
          void                 setDiffuse                       (const UInt32 idx, const Vec3f& intensity);
          void                 setDiffuse                       (const UInt32 idx, const Color3f& color);
          void                 setDiffuse                       (const UInt32 idx, Real32 red, Real32 green, Real32 blue);
          void                 setSpecular                      (const UInt32 idx, const Vec3f& intensity);
          void                 setSpecular                      (const UInt32 idx, const Color3f& color);
          void                 setSpecular                      (const UInt32 idx, Real32 red, Real32 green, Real32 blue);
          void                 setAttenuation                   (const UInt32 idx, const Vec3f& attenuation);
          void                 setDecayAttenuation              (const UInt32 idx, Real32 decayAttenuation);
          void                 setLengthFactor                  (const UInt32 idx, Real32 lengthFactor);
          void                 setRange                         (const UInt32 idx, Real32 range);
          void                 setSpotlightAngle                (const UInt32 idx, Real32 angle);
          void                 setSpotlightParameter            (const UInt32 idx, Real32 value);
          void                 setSpotlightExponent             (const UInt32 idx, Real32 exponent);
          void                 setSpotlightPenumbraAngle        (const UInt32 idx, Real32 angle);
          void                 setSpotlightPenumbraFactor       (const UInt32 idx, Real32 factor);
          void                 setInnerSuperEllipsesWidth       (const UInt32 idx, Real32 width);
          void                 setInnerSuperEllipsesHeight      (const UInt32 idx, Real32 height);
          void                 setOuterSuperEllipsesWidth       (const UInt32 idx, Real32 width);
          void                 setOuterSuperEllipsesHeight      (const UInt32 idx, Real32 height);
          void                 setSuperEllipsesRoundness        (const UInt32 idx, Real32 roundness);
          void                 setSuperEllipsesTwist            (const UInt32 idx, Real32 twist);
          void                 setRangeCutOn                    (const UInt32 idx, Real32 cutOn);
          void                 setRangeCutOff                   (const UInt32 idx, Real32 cutOff);
          void                 setRangeNearZone                 (const UInt32 idx, Real32 nearZone);
          void                 setRangeFarZone                  (const UInt32 idx, Real32 farZone);
          void                 setTypeOfLight                   (const UInt32 idx, MultiLight::TypeOfLight eTypeOfLight);
          void                 setEnabled                       (const UInt32 idx, bool flag);
          void                 setShadow                        (const UInt32 idx, bool flag);
          void                 setShadowDataIndex               (const UInt32 idx, Int32 shadowDataIndex);
          void                 setShadowParameterIndex          (const UInt32 idx, Int32 shadowParameterIndex);
          void                 setBeacon                        (const UInt32 idx, Node* const beacon);

          void                 changedBeacon                    ();

          bool                 getHasLightSpaceFromWorldSpaceMatrix             () const;
          bool                 getHasWorldSpaceFromLightSpaceMatrix             () const;
          bool                 getHasLightSpaceFromEyeSpaceMatrix               () const;
          bool                 getHasEyeSpaceFromLightSpaceMatrix               () const;
          bool                 getHasProjectionMatrix                           () const;
          bool                 getHasInvProjectionMatrix                        () const;
          bool                 getHasProjectionLightSpaceFromWorldSpaceMatrix   () const;
          bool                 getHasInvProjectionLightSpaceFromWorldSpaceMatrix() const;
          bool                 getHasProjectionLightSpaceFromEyeSpaceMatrix     () const;
          bool                 getHasInvProjectionLightSpaceFromEyeSpaceMatrix  () const;
          bool                 getHasIntensity                                  () const;
          bool                 getHasSeparateIntensities                        () const;
          bool                 getHasAttenuation                                () const;
          bool                 getHasDecayAttenuation                           () const;
          bool                 getHasLengthFactor                               () const;
          bool                 getHasRangeCutOn                                 () const;
          bool                 getHasRangeCutOff                                () const;
          bool                 getHasRangeNearZone                              () const;
          bool                 getHasRangeFarZone                               () const;
          bool                 getHasSpotlightAngle                             () const;
          bool                 getHasCosSpotlightAngle                          () const;
          bool                 getHasTanSpotlightAngle                          () const;
          bool                 getHasSpotlightExponent                          () const;
          bool                 getHasSpotlightPenumbraAngle                     () const;
          bool                 getHasSpotlightPenumbraFactor                    () const;
          bool                 getHasSpotlightPenumbraFrostbite                 () const;
          bool                 getHasCinemaLight                                () const;
          bool                 getHasShadow                                     () const;
          bool                 getHasProjection                                 () const;
          bool                 getHasGlobalAmbientIntensity                     () const;
          bool                 getAutoCalcRanges                                () const;
          bool                 getEyeSpace                                      () const;
          bool                 getHasGlobalState                                () const;

          void                 setHasLightSpaceFromWorldSpaceMatrix             (bool value);
          void                 setHasWorldSpaceFromLightSpaceMatrix             (bool value);
          void                 setHasLightSpaceFromEyeSpaceMatrix               (bool value);
          void                 setHasEyeSpaceFromLightSpaceMatrix               (bool value);
          void                 setHasProjectionMatrix                           (bool value);
          void                 setHasInvProjectionMatrix                        (bool value);
          void                 setHasProjectionLightSpaceFromWorldSpaceMatrix   (bool value);
          void                 setHasInvProjectionLightSpaceFromWorldSpaceMatrix(bool value);
          void                 setHasProjectionLightSpaceFromEyeSpaceMatrix     (bool value);
          void                 setHasInvProjectionLightSpaceFromEyeSpaceMatrix  (bool value);
          void                 setHasIntensity                                  (bool value);
          void                 setHasSeparateIntensities                        (bool value);
          void                 setHasAttenuation                                (bool value);
          void                 setHasDecayAttenuation                           (bool value);
          void                 setHasLengthFactor                               (bool value);
          void                 setHasRangeCutOn                                 (bool value);
          void                 setHasRangeCutOff                                (bool value);
          void                 setHasRangeNearZone                              (bool value);
          void                 setHasRangeFarZone                               (bool value);
          void                 setHasSpotlightAngle                             (bool value);
          void                 setHasCosSpotlightAngle                          (bool value);
          void                 setHasTanSpotlightAngle                          (bool value);
          void                 setHasSpotlightExponent                          (bool value);
          void                 setHasSpotlightPenumbraAngle                     (bool value);
          void                 setHasSpotlightPenumbraFactor                    (bool value);
          void                 setHasSpotlightPenumbraFrostbite                 (bool value);
          void                 setHasCinemaLight                                (bool value);
          void                 setHasShadow                                     (bool value);
          void                 setHasProjection                                 (bool value);
          void                 setHasGlobalAmbientIntensity                     (bool value);
          void                 setAutoCalcRanges                                (bool value);
          void                 setEyeSpace                                      (bool value);

          bool                 checkFeatures                                    (UInt32 features) const;
          void                 setFeatures                                      (UInt32 features, bool value);

          bool                 getCodeDistanceAttenuationClassic                () const;
          bool                 getCodeDistanceAttenuationPhysical               () const;
          bool                 getCodeDistanceAttenuationDecay                  () const;
          bool                 getCodeDistanceAttenuationMixPhysical            () const;
          bool                 getCodeDistanceAttenuationMixDecay               () const;
          bool                 getCodeDistanceAttenuationSmoothHermite          () const;
          bool                 getCodeSpotAttenuationClassic                    () const;
          bool                 getCodeSpotAttenuationSmoothHermite              () const;
          bool                 getCodeSpotAttenuationSmoothHermite2             () const;
          bool                 getCodeSpotAttenuationFrostbite                  () const;

          void                 setCodeDistanceAttenuationClassic                (bool value);
          void                 setCodeDistanceAttenuationPhysical               (bool value);
          void                 setCodeDistanceAttenuationDecay                  (bool value);
          void                 setCodeDistanceAttenuationMixPhysical            (bool value);
          void                 setCodeDistanceAttenuationMixDecay               (bool value);
          void                 setCodeDistanceAttenuationSmoothHermite          (bool value);
          void                 setCodeSpotAttenuationClassic                    (bool value);
          void                 setCodeSpotAttenuationSmoothHermite              (bool value);
          void                 setCodeSpotAttenuationSmoothHermite2             (bool value);
          void                 setCodeSpotAttenuationFrostbite                  (bool value);

          bool                 checkCodeFeatures                                (UInt32 features) const;
          void                 setCodeFeatures                                  (UInt32 features, bool value);

          const Vec3f&         getGlobalAmbientIntensity        () const;

          const std::string&   getLightBlockName                () const;
          const std::string&   getLightVariableName             () const;
          bool                 getNormalizeDirection            () const;
          GLenum               getUsage                         () const;

          void                 setGlobalAmbientIntensity        (const Vec3f &value);
          void                 setGlobalAmbientIntensity        (const Color3f &color);
          void                 setGlobalAmbientIntensity        (Real32 red, Real32 green, Real32 blue);

          void                 setLightBlockName                (const std::string &value);
          void                 setLightVariableName             (const std::string &value);
          void                 setNormalizeDirection            (bool value);
          void                 setUsage                         (const GLenum &value);

          std::string          getFragmentProgramSnippet        (bool add_attenuation_code, bool add_ubo_code) const;
          std::string          getLightUBOProgSnippet           () const;
          std::string          getAttenuationProgSnippet        () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MultiLightGroupBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiLightGroup(void);
    MultiLightGroup(const MultiLightGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiLightGroup(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Render                                  */
    /*! \{                                                                 */

    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    MultiLightChunk*            getChunk();
    const MultiLightChunk*      getChunk() const;

    friend class FieldContainer;
    friend class MultiLightGroupBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MultiLightGroup &source);
};

typedef MultiLightGroup *MultiLightGroupP;

OSG_END_NAMESPACE

#include "OSGMultiLightGroupBase.inl"
#include "OSGMultiLightGroup.inl"

#endif /* _OSGMULTILIGHTGROUP_H_ */
