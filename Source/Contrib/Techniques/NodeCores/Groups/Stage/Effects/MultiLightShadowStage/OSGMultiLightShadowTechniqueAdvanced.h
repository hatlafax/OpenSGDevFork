/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGMULTILIGHTSHADOWTECHNIQUEADVANCED_H_
#define _OSGMULTILIGHTSHADOWTECHNIQUEADVANCED_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>

#include "OSGMultiLightShadowTechniqueBase.h"
#include "OSGTileCameraDecorator.h"
#include "OSGMatrixCameraDecorator.h"
#include "OSGPolygonChunk.h"

#include "OSGImage.h"
#include "OSGFrameBufferObject.h"
#include "OSGTextureBuffer.h"
#include "OSGTextureObjChunk.h"
#include "OSGSamplerObjChunk.h"
#include "OSGSimpleSHLChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMultiLightShadowParameterAdvanced.h"
#include "OSGPolygonBody.h"
#include "OSGView.h"
#include "OSGLiSPSMTechnique.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class RenderAction;

/*! \ingroup GrpEffectsGroupsMultiLightShadowTechniqueAdvanced
 */

class OSG_CONTRIBTECHNIQUES_DLLMAPPING MultiLightShadowTechniqueAdvanced 
    : public MultiLightShadowTechniqueBase
{
public:
    static UInt32   getRequiredMultiLightFeatures();

public:
    
    typedef MultiLightShadowTechniqueBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Requirements                               */
    /*! \{                                                                 */

    virtual bool hasExtOrVersion(RenderAction* a);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */
    MultiLightShadowTechniqueAdvanced(
        MultiLightShadowStage     *pSource,
        MultiLightShadowStageData *pData,
        Window                    *pWindow);
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiLightShadowTechniqueAdvanced();

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    virtual void initialize (RenderAction* a, DrawEnv* pEnv);

    virtual void render     (RenderAction* a, DrawEnv* pEnv);
    virtual void addOverride(RenderAction* a, DrawEnv* pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        Variation Point: Light Assoc Data                     */
    /*! \{                                                                 */

    virtual void    initializeAssocData (UInt32 idx) const;

    virtual void    createCamera        (MultiLight::TypeOfLight typeOfLight, 
                                         CameraUnrecPtr&         camera) const;
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Shadow parameter                              */
    /*! \{                                                                 */

    static bool     changedShadowParameter  (
                                        FieldContainer*     pFC, 
                                        ConstFieldMaskArg   whichField, 
                                        UInt32              origin);

    /*! \}                                                                 */

private:
    /*---------------------------------------------------------------------*/
    /*! \name                  shadow data                                 */
    /*! \{                                                                 */

    struct ShadowData
    {
        ShadowData();
        ShadowData(const ShadowData& rhs);

        ShadowData&     operator=   (const ShadowData& rhs);
        bool            operator==  (const ShadowData& rhs) const;
        bool            equals      (const ShadowData& rhs, Real32 tol) const;

        void            resize      (std::size_t size);

        typedef std::vector<Matrix> MatrixStore;
        typedef std::vector< Vec2f> VectorStore;
        typedef std::vector<Real32> ValueStore;
        typedef std::vector< Int32> IndexStore;
        typedef std::vector<Real32> SplitPositionStore;

        Int32               nbrOfSplits;
        bool                focused;
        Vec3f               lightPosDir;
        MatrixStore         matLSFromWS;
        MatrixStore         matTSFromWS;
        VectorStore         frustumSize;
        ValueStore          zNear;
        ValueStore          zFar;
        IndexStore          shadowIndex;
        SplitPositionStore  splitPositions;
    };

    typedef std::vector<ShadowData> ShadowDataStorage;

    void                        adaptShadowDataLayout    (UInt32 num_lights);

    virtual std::size_t         calcShadowDataBufferSize () const;
    virtual std::vector<UInt8>  createShadowDataBuffer   () const;
    virtual void                updateShadowDataState    ();

    struct AlgorithmData
    {
        AlgorithmData();
        AlgorithmData(const AlgorithmData& rhs);

        AlgorithmData&  operator=   (const AlgorithmData& rhs);
        bool            operator==  (const AlgorithmData& rhs) const;
        bool            equals      (const AlgorithmData& rhs, Real32 tol) const;

        void            resize      (std::size_t size);

        typedef std::vector<Matrix>      MatrixStore;

        Pnt3f                   lightPositionWS;
        MatrixStore             matProjection;
    };

    typedef std::vector<AlgorithmData> AlgorithmDataStorage;

    void                        adaptAlgorithmDataLayout  (UInt32 num_lights);
    void                        adaptAlgorithmDataSplits  (UInt32 lightIdx, Int32 num_splits);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                shadow parameter                              */
    /*! \{                                                                 */

    virtual std::size_t         calcShadowParamBufferSize() const;
    virtual std::vector<UInt8>  createShadowParamBuffer  () const;
    virtual void                updateShadowParamState   ();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                shadow map data                               */
    /*! \{                                                                 */

    struct ShadowMapData
    {
        ShadowMapData(void) 
            : pFBO(NULL)
            , pTBO(NULL)
        {
        }

        ShadowMapData(const ShadowMapData& rhs) 
            : pFBO(rhs.pFBO  )
            , pTBO(rhs.pTBO  )
        {
        }

        ~ShadowMapData(void)
        {
            pFBO = NULL;
            pTBO = NULL;
        }

        const ShadowMapData& operator=(const ShadowMapData& rhs)
        {
            if(this != &rhs)
                return *this;

            pFBO = rhs.pFBO;
            pTBO = rhs.pTBO;

            return *this;
        }

        bool operator==(const ShadowMapData& rhs) const
        {
            return pFBO == rhs.pFBO 
                && pTBO == rhs.pTBO;
        }

        bool operator!=(const ShadowMapData& rhs) const
        {
            return ! (*this == rhs);
        }

        FrameBufferObjectUnrecPtr   pFBO;
        TextureBufferUnrecPtr       pTBO;
    };

    typedef std::vector<ShadowMapData>      ShadowMapStore;
    /*! \}                                                                 */

private:
    void        initOverrideShaderProgram   (RenderAction* a, DrawEnv* pEnv);
    void        updateOverrideShaderProgram ();
    void        calcShadowAlgorithmData     (RenderAction* a, DrawEnv* pEnv);
    void        initShadowMaps              ();
    void        updateShadowMaps            ();
    void        renderShadowMaps            (RenderAction* a, DrawEnv* pEnv);

    Int32       getNbrOfSplits              (Int32 shadowParamIdx);
    void        calcMaxNbrOfSplits          ();

    void        initShadowAlgorithmState    (MultiLightChunk* pMLChunk, UInt32 lightIdx, bool isOrthoCamera);
    void        adjustShadowAlgorithmState  (bool isOrthoCamera);
    bool        isFocusingFeasable          () const;
    void        initCameraView              (const Matrix& matESFromWS);
    void        initLightView               (const Matrix& matLSFromWS);
    void        updateLDirVDirAngle         ();
    void        adjustCameraPlanes          (
                                                const BoxVolume&        sceneBB, 
                                                const FrustumVolume&    camFrust, 
                                                Real32&                 nearDist, 
                                                Real32&                 farDist) const;
    Real32      getMinDepth                 ();

    void        calcSplitPositions          (
                                                UInt32                  idx, 
                                                Real32                  zNear, 
                                                Real32                  zFar
                                            );
    void        calcPolygonBody             (
                                                PolygonBody&            body, 
                                                Projection::Type        projectionType,
                                                const BoxVolume&        sceneBB,
                                                const FrustumVolume&    camFrust,
                                                const FrustumVolume&    lightFrust
                                            ) const;
    void        calcLightViewProjMat        (
                                                Matrix&                 matWrappedProjection, 
                                                Matrix&                 matWrappedProjLSFromWS, 
                                                Int32                   split, 
                                                const PolygonBody&      body, 
                                                const Matrix&           matProjection, 
                                                const Matrix&           matLSFromWS
                                            );


    bool        isOrthographicCamera        (Camera* camera) const;

    std::string getPointLightVertProgram    () const;
    std::string getPointLightFragProgram    () const;

    std::string getDirLightVertProgram      () const;
    std::string getDirLightFragProgram      () const;

    std::string getFragmentProgramSnippet   () const;
    std::string getDispatchProgramSnippet   () const;

private:
    //
    // Cube and plain shadow map arrays for point and directional
    // lights respectively. 
    //
    ShadowMapStore          _pointLightStore;
    TextureObjChunkUnrecPtr _pointLightTexObj;
    SamplerObjChunkUnrecPtr _pointLightSampleObj;
    ImageUnrecPtr           _pointLightImg;
    SimpleSHLChunkUnrecPtr  _pointLightSHLChunk;
    ChunkMaterialUnrecPtr   _pointLightChunkMaterial;
    Int32                   _pointLightNbrMaps;

    ShadowMapStore          _dirLightStore;
    TextureObjChunkUnrecPtr _dirLightTexObj;
    SamplerObjChunkUnrecPtr _dirLightSampleObj;
    ImageUnrecPtr           _dirLightImg;
    SimpleSHLChunkUnrecPtr  _dirLightSHLChunk;
    ChunkMaterialUnrecPtr   _dirLightChunkMaterial;
    Int32                   _dirLightNbrMaps;

    //
    // Runtime data for each enabled shadowing light that is needed
    // at different placed in the rendering loop and that must be
    // available in the light fragment shader.
    //
    ShadowDataStorage       _shadowData;
    ShadowDataStorage       _shadowDataLast;

    //
    // Runtime data for each enabled shadowing light that is needed
    // at different places in rendering loop.
    //
    AlgorithmDataStorage    _algorithmData;
    AlgorithmDataStorage    _algorithmDataLast;

    //
    // The fragment shader contains array data for each split. The
    // number of splits might be different for each light. But the
    // shader array size is fixed. Therefore the max number if splits
    // over all lights must be determined. This is done by the function
    // calcMaxNbrOfSplits().
    //
    Int32                   _maxNbrOfSplits;
    Int32                   _maxNbrOfSplitsLast;


    //
    // Shadow parameter data, that will be updated for each
    // enabled shadowing light.
    //
    Int32                   _nbrOfSplits;
    bool                    _useLiSP;
    bool                    _useGS;
    Int32                   _liSPMode;
    bool                    _focusing;
    bool                    _reduceSwimming;
    bool                    _updateLightUp;     // lightSpaceAlignment
    bool                    _useMinDepth;
    bool                    _useBestResSelection;
    Real32                  _warpingParameter;
    Real32                  _lambda;
    Real32                  _zNear;
    Real32                  _pseudoNear;
    Real32                  _pseudoFar;
    MultiLight::TypeOfLight _typeOfLight;
    Vec3f                   _direction;

    //
    // Calculated algorithm data updated for each enabled shadowing light
    //
    Real32                  _gamma;
    Vec2f                   _depthRange;
    LiSPSMTechnique         _liSP;
    View                    _camView;
    View                    _lightView;

    //
    // If no parameter is available at all, use a default parameter.
    //
    MultiLightShadowParameterAdvancedUnrecPtr   _defaultShadowParameter;

private:
    static void     initializeExtensions();

private:
    static bool     _initExtenstions;

    static UInt32   _uiTextureCubeMapArrayARB;
    static UInt32   _uiTextureArrayEXT;
    static UInt32   _uiGeometryShader4ARB;
    static UInt32   _uiFuncFramebufferTextureLayer;
};

OSG_END_NAMESPACE

#include "OSGMultiLightShadowTechniqueAdvanced.inl"

#endif /* _OSGMULTILIGHTSHADOWTECHNIQUEADVANCED_H_ */

