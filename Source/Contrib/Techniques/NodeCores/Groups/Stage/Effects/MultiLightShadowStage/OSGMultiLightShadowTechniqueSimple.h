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

#ifndef _OSGMULTILIGHTSHADOWTECHNIQUESIMPLE_H_
#define _OSGMULTILIGHTSHADOWTECHNIQUESIMPLE_H_
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
#include "OSGMultiLightShadowParameter.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class RenderAction;

/*! \ingroup GrpEffectsGroupsMultiLightShadowTechniqueSimple
 */

class OSG_CONTRIBTECHNIQUES_DLLMAPPING MultiLightShadowTechniqueSimple 
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
    MultiLightShadowTechniqueSimple(
        MultiLightShadowStage     *pSource,
        MultiLightShadowStageData *pData,
        Window                    *pWindow);
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiLightShadowTechniqueSimple();

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
        ShadowData() 
            : matLSFromWS()
            , matTSFromWS()
            , frustumSize(1.f, 1.f)
            , zNear      (0.f)
            , zFar       (0.f)
            , shadowIndex(-1)
        {}

        bool operator==(const ShadowData& rhs) const;
        bool operator!=(const ShadowData& rhs) const;

        OSG::Matrix matLSFromWS;
        OSG::Matrix matTSFromWS;
        OSG::Vec2f  frustumSize;
        OSG::Real32 zNear;
        OSG::Real32 zFar;
        OSG::Int32  shadowIndex;
    };

    typedef std::vector<ShadowData> ShadowDataStorage;

            void                adaptShadowDataLayout    (UInt32 num_lights);

    virtual std::size_t         calcShadowDataBufferSize () const;
    virtual std::vector<UInt8>  createShadowDataBuffer   () const;
    virtual void                updateShadowDataState    ();

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
    void        initShadowMaps              ();
    void        updateShadowMaps            ();
    void        renderShadowMaps            (RenderAction* a, DrawEnv* pEnv);

    std::string getPointLightVertProgram    () const;
    std::string getPointLightFragProgram    () const;

    std::string getDirLightVertProgram      () const;
    std::string getDirLightFragProgram      () const;

    std::string getFragmentProgramSnippet   () const;
    std::string getDispatchProgramSnippet   () const;

private:
    ShadowMapStore          _pointLightStore;
    TextureObjChunkUnrecPtr _pointLightTexObj;
    SamplerObjChunkUnrecPtr _pointLightSampleObj;
    ImageUnrecPtr           _pointLightImg;
    SimpleSHLChunkUnrecPtr  _pointLightSHLChunk;
    ChunkMaterialUnrecPtr   _pointLightChunkMaterial;

    ShadowMapStore          _dirLightStore;
    TextureObjChunkUnrecPtr _dirLightTexObj;
    SamplerObjChunkUnrecPtr _dirLightSampleObj;
    ImageUnrecPtr           _dirLightImg;
    SimpleSHLChunkUnrecPtr  _dirLightSHLChunk;
    ChunkMaterialUnrecPtr   _dirLightChunkMaterial;

    ShadowDataStorage       _shadowData;
    ShadowDataStorage       _shadowDataLast;

    MultiLightShadowParameterUnrecPtr   _defaultShadowParameter;

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

#include "OSGMultiLightShadowTechniqueSimple.inl"

#endif /* _OSGMULTILIGHTSHADOWTECHNIQUESIMPLE_H_ */

