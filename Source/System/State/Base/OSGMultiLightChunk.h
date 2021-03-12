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

#ifndef _OSGMULTILIGHTCHUNK_H_
#define _OSGMULTILIGHTCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMultiLight.h"
#include "OSGMultiLightChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MultiLightChunk class. See \ref
           PageSystemMultiLightChunk for a description.
*/

class OSG_SYSTEM_DLLMAPPING MultiLightChunk : public MultiLightChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MultiLightChunkBase Inherited;
    typedef MultiLightChunk     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                 Main Interface                               */
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

          void                 setGlobalAmbientIntensity        (const Color3f& color);
          void                 setGlobalAmbientIntensity        (Real32 red, Real32 green, Real32 blue);

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
    const Matrix&                  getProjectionMatrix              (const UInt32 idx) const;
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
          void                 setProjectionMatrix              (const UInt32 idx, const Matrix& projectionMatrix);
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

          std::string          getFragmentProgramSnippet        (bool add_attenuation_code, bool add_ubo_code) const;
          std::string          getLightUBOProgSnippet           () const;
          std::string          getAttenuationProgSnippet        () const;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                   Draw Interface                             */
    /*! \{                                                                 */

    //
    // The following convenience functions (calc...) do not modify the 
    // multi light state.
    //

    void    calcSpotAngle                               (
                UInt32           idx,
                Real32&          spotlightAngle,
                Real32&          cosSpotlightAngle) const;
 
    void    calcRange                                   (
                DrawEnv*         pEnv,
                UInt32           idx,
                bool             attenuationAware,
                Real32&          cutOnRange,
                Real32&          cutOffRange)const;

    void    calcCutOnRange                              (
                DrawEnv*         pEnv,
                UInt32           idx,
                bool             attenuationAware,
                Real32&          cutOnRange) const;

    void    calcCutOffRange                             (
                DrawEnv*         pEnv,
                UInt32           idx,
                bool             attenuationAware,
                Real32&          cutOffRange) const;

    void    calcFrustumZ(
                DrawEnv*         pEnv,
                UInt32           idx,
                Real32&          zNear,
                Real32&          zFar)const;

    void    calcPosition                                (
                DrawEnv*         pEnv,
                UInt32           idx,
                Pnt3f&           position, 
                bool             eyeSpace = false) const;

    void    calcDirection                               (
                DrawEnv*         pEnv,
                UInt32           idx,
                Vec3f&           direction,
                bool             eyeSpace = false) const;

    void    calcPositionAndDirection                    (
                DrawEnv*         pEnv,
                UInt32           idx,
                Pnt3f&           position, 
                Vec3f&           direction,
                bool             eyeSpace = false) const;

    void    calcLightSpaceMatrixLSFromWS                (
                UInt32           idx,
                Matrix&          matLSFromWS) const;

    void    calcLightSpaceMatrixLSFromES                (
                DrawEnv*         pEnv,
                UInt32           idx,
                Matrix&          matLSFromES) const;

    void    calcLightSpaceMatricesLSFrom                (
                DrawEnv*         pEnv,
                UInt32           idx,
                Matrix&          matLSFromWS, 
                Matrix&          matLSFromES) const;

    void    calcInvLightSpaceMatrixWSFromLS             (
                UInt32           idx,
                Matrix&          matWSFromLS) const;

    void    calcInvLightSpaceMatricesWSFrom             (
                DrawEnv*         pEnv,
                UInt32           idx,
                Matrix&          matWSFromLS, 
                Matrix&          matESFromLS) const;

    void    calcProjectionMatrix                        (
                DrawEnv*         pEnv,
                UInt32           idx,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matProjection) const;

    void    calcInvProjectionMatrix                     (
                DrawEnv*         pEnv,
                UInt32           idx,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matInvProjection) const;

    void    calcLightSpaceProjectionMatrixLSFromWS      (
                DrawEnv*         pEnv,
                UInt32           idx,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matLightSpaceProjectionLSFromWS) const;

    void    calcLightSpaceProjectionMatrixLSFromES      (
                DrawEnv*         pEnv,
                UInt32           idx,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matLightSpaceProjectionLSFromES) const;

    void    calcInvLightSpaceProjectionMatrixLSFromWS   (
                DrawEnv*         pEnv,
                UInt32           idx,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matInvLightSpaceProjectionLSFromWS) const;

    void    calcInvLightSpaceProjectionMatrixLSFromES   (
                DrawEnv*         pEnv,
                UInt32           idx,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matInvLightSpaceProjectionLSFromES) const;
    
    void    calcProjectionMatrix                        (
                UInt32           idx,
                Real32           zNear,
                Real32           zFar,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matProjection) const;

    void    calcInvProjectionMatrix                     (
                UInt32           idx,
                Real32           zNear,
                Real32           zFar,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matInvProjection) const;

    void    calcLightSpaceProjectionMatrixLSFromWS      (
                UInt32           idx,
                Real32           zNear,
                Real32           zFar,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matLightSpaceProjectionLSFromWS) const;

    void    calcLightSpaceProjectionMatrixLSFromES      (
                DrawEnv*         pEnv,
                UInt32           idx,
                Real32           zNear,
                Real32           zFar,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matLightSpaceProjectionLSFromES) const;

    void    calcInvLightSpaceProjectionMatrixLSFromWS   (
                UInt32           idx,
                Real32           zNear,
                Real32           zFar,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matInvLightSpaceProjectionLSFromWS) const;

    void    calcInvLightSpaceProjectionMatrixLSFromES   (
                DrawEnv*         pEnv,
                UInt32           idx,
                Real32           zNear,
                Real32           zFar,
                const Pnt3f&     lightMin,      // Corners of the light view volume
                const Pnt3f&     lightMax,      // used for directional lights only.
                Matrix&          matInvLightSpaceProjectionLSFromES) const;

    void    calcProjectionMatrix                        (
                MultiLight::TypeOfLight typeOfLight,
                Real32                  cosSpotlightAngle,
                Real32                  zNear,
                Real32                  zFar,
                const Pnt3f&            lightMin,      // Corners of the light view volume
                const Pnt3f&            lightMax,      // used for directional lights only.
                Matrix&                 matProjection) const;

    void    calcInvProjectionMatrix                     (
                MultiLight::TypeOfLight typeOfLight,
                Real32                  cosSpotlightAngle,
                Real32                  zNear,
                Real32                  zFar,
                const Pnt3f&            lightMin,      // Corners of the light view volume
                const Pnt3f&            lightMax,      // used for directional lights only.
                Matrix&                 matInvProjection) const;

    //
    // The following convenience function do take credit of the currently stored
    // projection matrix.
    //

    Matrix  getInvProjectionMatrix                      (
                UInt32           idx) const;

    Matrix  getLightSpaceProjectionMatrixLSFromWS       (
                UInt32           idx) const;

    Matrix  getLightSpaceProjectionMatrixLSFromES       (
                DrawEnv*         pEnv,
                UInt32           idx) const;

    Matrix  getLightSpaceProjectionMatrixLSFrom         (
                UInt32           idx,
                const Matrix&    matLSFrom) const;

    Matrix  getInvLightSpaceProjectionMatrixLSFromWS    (
                UInt32           idx) const;

    Matrix  getInvLightSpaceProjectionMatrixLSFromES    (
                DrawEnv*         pEnv,
                UInt32           idx) const;

    Matrix  getInvLightSpaceProjectionMatrixLSFrom      (
                UInt32           idx,
                const Matrix&    matLSFrom) const;
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
    /*---------------------------------------------------------------------*/
    /*! \name                       State                                  */
    /*! \{                                                                 */

    virtual void activate   (DrawEnv    *pEnv,
                             UInt32      index = 0);

    virtual void changeFrom (DrawEnv    *pEnv,
                             StateChunk *pOld,
                             UInt32      index = 0);

    virtual void deactivate (DrawEnv    *pEnv,
                             UInt32      index = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             OpenGL handling                                  */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    bool   _bUpdateBuffer;

    ChangedFunctor  _cameraCB;

    // Variables should all be in MultiLightChunkBase.

    void onCreate      (const MultiLightChunk *source      = NULL);
    void onCreateAspect(const MultiLightChunk *createAspect,
                        const MultiLightChunk *source      = NULL);
    void onDestroy     (      UInt32           uiContainerId     );

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiLightChunk(void);
    MultiLightChunk(const MultiLightChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiLightChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MultiLightChunkBase;

    /*---------------------------------------------------------------------*/
    /*! \name                         buffer                               */
    /*! \{                                                                 */
    void    transformToWorldSpace               (DrawEnv* pEnv,
                                                 Node* beacon, 
                                                 const Pnt3f& position_bs, 
                                                 const Vec3f& direction_bs, 
                                                 Pnt3f& position_ws, 
                                                 Vec3f& direction_ws) const;

    void    transformToEyeSpace                  (DrawEnv* pEnv,
                                                  Node* beacon, 
                                                  const Pnt3f& position_bs, 
                                                  const Vec3f& direction_bs, 
                                                  Pnt3f& position_es, 
                                                  Vec3f& direction_es) const;

    void    calcDirectionalLightMatrixLSFromWS  (Node* beacon, 
                                                 const Vec3f& direction_bs, 
                                                 Matrix& matLSFromWS) const;

    void    calcDirectionalLightMatrixLSFromES  (DrawEnv* pEnv,
                                                 Node* beacon, 
                                                 const Vec3f& direction_bs, 
                                                 Matrix& matLSFromES) const;

    void    calcDirectionalLightMatricesLSFrom  (DrawEnv* pEnv,
                                                 Node* beacon, 
                                                 const Vec3f& direction_bs, 
                                                 Matrix& matLSFromWS,
                                                 Matrix& matLSFromES) const;

    void    calcPointLightMatrixLSFromWS        (Node* beacon, 
                                                 const Pnt3f& position_bs, 
                                                 Matrix& matLSFromWS) const;

    void    calcPointLightMatrixLSFromES        (DrawEnv* pEnv,
                                                 Node* beacon, 
                                                 const Pnt3f& position_bs, 
                                                 Matrix& matLSFromES) const;

    void    calcPointLightMatricesLSFrom        (DrawEnv* pEnv,
                                                 Node* beacon, 
                                                 const Pnt3f& position_bs, 
                                                 Matrix& matLSFromWS,
                                                 Matrix& matLSFromES) const;

    void    calcSpotLightMatrixLSFromWS         (Node* beacon, 
                                                 const Pnt3f& position_bs, 
                                                 const Vec3f& direction_bs, 
                                                 Matrix& matLSFromWS) const;

    void    calcSpotLightMatrixLSFromES         (DrawEnv* pEnv,
                                                 Node* beacon, 
                                                 const Pnt3f& position_bs, 
                                                 const Vec3f& direction_bs, 
                                                 Matrix& matLSFromES) const;

    void    calcSpotLightMatricesLSFrom         (DrawEnv* pEnv,
                                                 Node* beacon, 
                                                 const Pnt3f& position_bs, 
                                                 const Vec3f& direction_bs, 
                                                 Matrix& matLSFromWS,
                                                 Matrix& matLSFromES) const;

    void    calcPointLightRange                 (DrawEnv* pEnv,
                                                 const Vec3f attenuation,
                                                 Real32 threshold,
                                                 Real32& cutOnRange,
                                                 Real32& cutOffRange) const;

    void    calcPointLightRange                 (DrawEnv* pEnv,
                                                 Real32 decayAttenuation,
                                                 Real32 threshold,
                                                 Real32& cutOnRange,
                                                 Real32& cutOffRange) const;

    std::size_t         calcLightBufferSize     () const;
    std::vector<UInt8>  createLightBuffer       (DrawEnv* pEnv) const;
    void                createLightState        (DrawEnv* pEnv);
    void                updateLightState        (DrawEnv* pEnv);

    /*! \}                                                                 */

    bool        check_invariant() const;
    void        force_invariant();

    void        setFeatureImpl          (UInt32 features);
    void        setCodeFeatureImpl      (UInt32 features);

    /*---------------------------------------------------------------------*/
    /*! \name                  code generation                             */
    /*! \{                                                                 */

    std::string getDistanceAttenuationClassicProgSnippet        () const;
    std::string getDistanceAttenuationPhysicallyProgSnippet     () const;
    std::string getDistanceAttenuationDecayProgSnippet          () const;
    std::string getDistanceAttenuationMixPhysicallyProgSnippet  () const;
    std::string getDistanceAttenuationMixDecayProgSnippet       () const;
    std::string getDistanceAttenuationSmoothHermiteProgSnippet  () const;
    std::string getSpotAttenuationClassicProgSnippet            () const;
    std::string getSpotAttenuationSmoothHermiteProgSnippet      () const;
    std::string getSpotAttenuationSmoothHermite2ProgSnippet     () const;
    std::string getSpotAttenuationFrostbiteProgSnippet          () const;
    std::string getCinemaAttenuationProgSnippet                 () const;

    /*! \}                                                                 */


    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MultiLightChunk &source);
};

typedef MultiLightChunk *MultiLightChunkP;

OSG_END_NAMESPACE

#include "OSGMultiLightChunkBase.inl"
#include "OSGMultiLightChunk.inl"

#endif /* _OSGMULTILIGHTCHUNK_H_ */
