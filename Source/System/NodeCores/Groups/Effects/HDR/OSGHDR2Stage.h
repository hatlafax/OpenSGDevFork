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

#ifndef _OSGHDR2STAGE_H_
#define _OSGHDR2STAGE_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/container/flat_map.hpp>

#include "OSGHDR2StageBase.h"
#include "OSGAction.h"
#include "OSGHDR2StageDataFields.h"
#include "OSGSimpleSHLChunk.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class RenderAction;
class TextureObjChunk;

/*! \brief HDR2Stage class. See \ref
           PageEffectGroupsHDR2Stage for a description.
*/

class OSG_EFFECTGROUPS_DLLMAPPING HDR2Stage : public HDR2StageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef HDR2StageBase Inherited;
    typedef HDR2Stage     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                       Tone Mapping Modes                     */
    /*! \{                                                                 */

    enum ToneMappingModes
    {
        NO_TONE_MAPPING = 0,
        LOGARITHMIC_TONE_MAPPING,
        EXPONENTIAL_TONE_MAPPING,
        DRAGO_LOGARITHMIC_TONE_MAPPING, 
        REINHARD_TONE_MAPPING,
        REINHARD_MODIFIED_TONE_MAPPING,
        FILMIC_HABLE_TONE_MAPPING,
        FILMIC_UNCHARTED2_TONE_MAPPING,
        FILMIC_ACES_TONE_MAPPING,
        FILMIC_HEJ2015_TONE_MAPPING,
        FILMIC_ACES_2_TONE_MAPPING,
    };

    enum FinalScreenTarget
    {
        BACKGROUND_TEXTURE = 0,
        SCENE_TEXTURE,
        LUMINANCE_TEXTURE,
        ADAPTED_LUMINANCE_TEXTURE,
        THRESHOLD_TEXTURE,
        BLURRED_TEXTURE,
        COMPOSITE_TEXTURE,
        EXPOSURE_TEXTURE,
        DEPTH_TEXTURE,
        LINEARIZED_DEPTH_TEXTURE,

        DOWN_SCALED_0,
        DOWN_SCALED_1,
        DOWN_SCALED_2,
        BLUR_TEXTURE,
        UPSCALED_SCALED_0,
        UPSCALED_SCALED_1
    };

    enum AutoExposureMode
    {
        MANUAL = 0,
        KEY_VALUE, 
        AUTOMATIC,
        SATURATION_BASED,
        STANDARD_OUTPUT_BASED
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Filmic Curve Parameters                         */
    /*! \{                                                                 */

    Real32 getFilmicShoulderStrenght    () const;
    Real32 getFilmicLinearStrength      () const;
    Real32 getFilmicLinearAngle         () const;
    Real32 getFilmicToeStrength         () const;
    Real32 getFilmicToeNumerator        () const;
    Real32 getFilmicToeDenominator      () const;
    Real32 getFilmicLinearWhite         () const;

    void   setFilmicShoulderStrenght    (Real32 value);
    void   setFilmicLinearStrength      (Real32 value);
    void   setFilmicLinearAngle         (Real32 value);
    void   setFilmicToeStrength         (Real32 value);
    void   setFilmicToeNumerator        (Real32 value);
    void   setFilmicToeDenominator      (Real32 value);
    void   setFilmicLinearWhite         (Real32 value);

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
    /*! \name                    postProcess                               */
    /*! \{                                                                 */

    void postProcess            (DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Data                                  */
    /*! \{                                                                 */

    void initData  (RenderAction *pAction,
                    Int32         iVPWidth,
                    Int32         iVPHeight);

    void updateData(RenderAction *pAction,
                    Int32         iVPWidth,
                    Int32         iVPHeight);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    enum FilmicCurveParameterAccessIds
    {
        FilmicShoulderStrenghtId = 0,
        FilmicLinearStrengthId,
        FilmicLinearAngleId,
        FilmicToeStrengthId,
        FilmicToeNumeratorId,
        FilmicToeDenominatorId,
        FilmicLinearWhiteId,
        FilmicCurveParameterAccessNumEntries
    };

    // Variables should all be in HDR2StageBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    HDR2Stage(void);
    HDR2Stage(const HDR2Stage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~HDR2Stage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    static UInt32 _uiFramebufferObjectExt;
    static UInt32 _uiFuncDrawBuffers;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    void renderQuad();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   StageData                                  */
    /*! \{                                                                 */

    HDR2StageDataTransitPtr setupStageData (Int32          iPixelWidth,
                                            Int32          iPixelHeight);

    void                    updateStageData(HDR2StageData* pData,
                                            Int32          iPixelWidth,
                                            Int32          iPixelHeight);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Access                                   */
    /*! \{                                                                 */

    Vec3f                   getAdjustedShadowLift       () const;
    Vec3f                   getAdjustedInvMidtoneGamma  () const;
    Vec3f                   getAdjustedHighlightGain    () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                StageData Details                             */
    /*! \{                                                                 */
    std::size_t calcUBOBufferSize        ();
    void        fillUBOBuffer            (std::vector<OSG::UInt8>& buffer);
    
    void setupUBOData                    (HDR2StageData* pData);
    void updateUBOData                   (HDR2StageData* pData);

    void setupSharedData                 (HDR2StageData* pData);
    void setupRenderTargets              (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void setupMaterials                  (HDR2StageData* pData);

    void updateSharedData                (HDR2StageData* pData);
    void updateRenderTargets             (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void updateMaterials                 (HDR2StageData* pData);

    void setupBackgroundRenderTarget     (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void setupSceneRenderTarget          (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void setupLuminanceRenderTarget      (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void setupAdaptLuminanceRenderTarget (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void setupThresholdRenderTarget      (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void setupScaleRenderTarget          (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void setupBlurRenderTarget           (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void setupCompositeRenderTarget      (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);

    void setupLuminanceMapMaterial       (HDR2StageData* pData);
    void setupAdaptLuminanceMaterial     (HDR2StageData* pData);
    void setupThresholdMaterial          (HDR2StageData* pData);
    void setupScaleMaterial              (HDR2StageData* pData);
    void setupBlurHorizMaterial          (HDR2StageData* pData);
    void setupBlurVertMaterial           (HDR2StageData* pData);
    void setupCompositeMaterial          (HDR2StageData* pData);
    void setupFinalScreenMaterial        (HDR2StageData* pData);

    void updateBackgroundRenderTarget    (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void updateSceneRenderTarget         (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void updateLuminanceRenderTarget     (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void updateAdaptLuminanceRenderTarget(HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void updateThresholdRenderTarget     (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void updateScaleRenderTarget         (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void updateBlurRenderTarget          (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);
    void updateCompositeRenderTarget     (HDR2StageData* pData, Int32 iWidth, Int32 iHeight);

    void updateLuminanceMapMaterial      (HDR2StageData* pData);
    void updateAdaptLuminanceMaterial    (HDR2StageData* pData);
    void updateThresholdMaterial         (HDR2StageData* pData);
    void updateScaleMaterial             (HDR2StageData* pData);
    void updateBlurHorizMaterial         (HDR2StageData* pData);
    void updateBlurVertMaterial          (HDR2StageData* pData);
    void updateCompositeMaterial         (HDR2StageData* pData);
    void updateFinalScreenMaterial       (HDR2StageData* pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Shader Toolbox                              */
    /*! \{                                                                 */
    void genBlockHDRShaderData           (std::stringstream& ost);
    void genFuncGetPrimaryInputColor     (std::stringstream& ost);
    void genFuncCalcLuminance            (std::stringstream& ost);
    void genFuncGetLastLumValue          (std::stringstream& ost);
    void genFuncGetCurrLumValue          (std::stringstream& ost);
    void genFuncLog10                    (std::stringstream& ost);
    void genFuncPow                      (std::stringstream& ost);
    void genFuncGetAvgLuminance          (std::stringstream& ost);
    void genFuncGetDepthValue            (std::stringstream& ost);
    void genFuncSaturationBasedExp       (std::stringstream& ost);
    void genFuncStandardOutputBasedExp   (std::stringstream& ost);
    void genFuncCalcExposedColor         (std::stringstream& ost);
    void genFuncColorCorrection          (std::stringstream& ost);
    void genFuncContrastCorrection       (std::stringstream& ost);
    void genFuncLog2Exposure             (std::stringstream& ost);
    void genFuncU2Func                   (std::stringstream& ost);
    void genFuncToneMapLogarithmic       (std::stringstream& ost);
    void genFuncToneMapExponential       (std::stringstream& ost);
    void genFuncToneMapDragoLogarithmic  (std::stringstream& ost);
    void genFuncToneMapReinhard          (std::stringstream& ost);
    void genFuncToneMapReinhardModified  (std::stringstream& ost);
    void genFuncToneMapFilmicALU         (std::stringstream& ost);
    void genFuncToneMapFilmicU2          (std::stringstream& ost);
    void genFuncToneMapFilmicACES        (std::stringstream& ost);
    void genFuncToneMapFilmicHejl2015    (std::stringstream& ost);
    void genFuncToneMapFilmicACES2       (std::stringstream& ost);
    void genFuncToneMap                  (std::stringstream& ost);
    void genFuncCalcGaussianWeight       (std::stringstream& ost);
    void genFuncGetBloomColor            (std::stringstream& ost);
    void genFuncGammaCorrection          (std::stringstream& ost);
    void genFuncLiftGammaGainCorrection  (std::stringstream& ost);
    void genFuncDithering                (std::stringstream& ost);
    void genFuncLinearizeZ               (std::stringstream& ost);

    void genSharedCode                   (std::stringstream& ost);

    void genCommonVertexShader           (std::stringstream& ost);

    void genLuminanceMapFragmentShader   (std::stringstream& ost);
    void genAdaptLuminanceFragmentShader (std::stringstream& ost);
    void genThresholdFragmentShader      (std::stringstream& ost);
    void genScaleFragmentShader          (std::stringstream& ost);
    void genBloomBlurFragmentShader      (std::stringstream& ost);
    void genCompositeFragmentShader      (std::stringstream& ost);
    void genFinalScreenFragmentShader    (std::stringstream& ost);

    SimpleSHLChunkTransitPtr    genLuminanceMapShader   ();
    SimpleSHLChunkTransitPtr    genAdaptLuminanceShader ();
    SimpleSHLChunkTransitPtr    genThresholdShader      ();
    SimpleSHLChunkTransitPtr    genScaleShader          ();
    SimpleSHLChunkTransitPtr    genBloomBlurShader      ();
    SimpleSHLChunkTransitPtr    genCompositeShader      ();
    SimpleSHLChunkTransitPtr    genFinalScreenShader    ();
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Postprocess Toolbox                           */
    /*! \{                                                                 */

    void calcAvgLuminance       (DrawEnv* pEnv, HDR2StageData* pData);
    void bloomBlur              (DrawEnv* pEnv, HDR2StageData* pData);
    void composite              (DrawEnv* pEnv, HDR2StageData* pData);
    void drawToFinalTarget      (DrawEnv* pEnv, HDR2StageData* pData);

    void bloomBlur_DOWN_SCALED_0(DrawEnv* pEnv, HDR2StageData* pData);
    void bloomBlur_DOWN_SCALED_1(DrawEnv* pEnv, HDR2StageData* pData);
    void bloomBlur_DOWN_SCALED_2(DrawEnv* pEnv, HDR2StageData* pData);
    void bloomBlur_BLUR_TEXTURE (DrawEnv* pEnv, HDR2StageData* pData);
    void bloomBlur_UP_SCALED_0  (DrawEnv* pEnv, HDR2StageData* pData);
    void bloomBlur_UP_SCALED_1  (DrawEnv* pEnv, HDR2StageData* pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      sRGB                                    */
    /*! \{                                                                 */

    Color3f sRGBToLinear        (const Color3f& c) const;
    Real32  sRGBToLinear        (      Real32   x) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Update                                  */
    /*! \{                                                                 */

    //
    // Update need to be done for each stage data separately. Since we
    // do not have (as far as I know) a proper way to push the update
    // request into the stage data objects, we settle for the map solution.
    // On Change, all entries in the maps are set to true and on rendering
    // of the different windows/views we reset the specific entries separately.
    // StageData objects, that are passed away, are still accounted in the maps.
    // But since that are not so many, we don't bother. 
    //
    typedef boost::container::flat_map<HDR2StageData*, bool> UpdateMapT;

    UpdateMapT  _mapUpdate;
    UpdateMapT  _mapUpdateUboBuffer;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
#if 0
    void            write_read_back_images(HDR2StageData* pData) const;
    void            dump_fbo    (const char* name, FrameBufferObject* fbo, std::stringstream& ss) const;
    std::string     dump_stage  (HDR2StageData* pData) const;
#endif

    friend class FieldContainer;
    friend class HDR2StageBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const HDR2Stage &source);
};

typedef HDR2Stage *HDR2StageP;

OSG_END_NAMESPACE

#include "OSGHDR2StageBase.inl"
#include "OSGHDR2Stage.inl"

#endif /* _OSGHDR2STAGE_H_ */
