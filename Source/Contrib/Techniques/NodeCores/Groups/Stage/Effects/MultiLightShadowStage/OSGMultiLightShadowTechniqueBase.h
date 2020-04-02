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

#ifndef _OSGMULTILIGHTSHADOWTECHNIQUEBASE_H_
#define _OSGMULTILIGHTSHADOWTECHNIQUEBASE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGContribTechniquesDef.h"
#include "OSGMemoryObject.h"

#include "OSGAction.h"
#include "OSGShaderStorageBufferObjStdLayoutChunk.h"
#include "OSGUniformBufferObjStd140Chunk.h"
#include "OSGDepthClearBackground.h"
#include "OSGPolygonChunk.h"
#include "OSGCamera.h"
#include "OSGMultiLight.h"

OSG_BEGIN_NAMESPACE

#ifdef __APPLE__
#define NO_CONST_GLSL_VAR
#endif

class MultiLightChunk;
class MultiLightShadowStage;
class MultiLightShadowStageData;
class DrawEnv;
class RenderAction;
class Transform;
class Window;

/*! \ingroup GrpEffectsGroupsMultiLightShadowTechniqueBase
 */

class OSG_CONTRIBTECHNIQUES_DLLMAPPING MultiLightShadowTechniqueBase : public MemoryObject
{

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Requirements                               */
    /*! \{                                                                 */

    virtual bool hasExtOrVersion(RenderAction *a) = 0;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiLightShadowTechniqueBase(
        MultiLightShadowStage     *pSource,
        MultiLightShadowStageData *pData,
        Window                    *pWindow);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiLightShadowTechniqueBase();
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    virtual void initialize (RenderAction* a, DrawEnv* pEnv) = 0;

    virtual void render     (RenderAction* a, DrawEnv* pEnv) = 0;
    virtual void addOverride(RenderAction* a, DrawEnv* pEnv) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Misc                                       */
    /*! \{                                                                 */

    UInt32      getMode         ();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        Variation Point: Light Assoc Data                     */
    /*! \{                                                                 */

    virtual void    initializeAssocData (UInt32 idx) const;

    virtual void    createCamera        (MultiLight::Type type, 
                                         CameraUnrecPtr&  camera) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    Action::ResultE recurseFromThis(Action   *action );
    Action::ResultE recurseFrom    (Action   *action, NodeCore *pFrom  );
    Action::ResultE recurse        (Action   *action, Node     *node   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    void            updateLights        (RenderAction* a, DrawEnv* pEnv);

    virtual void    updateDirLight      (RenderAction* a,         DrawEnv*         pEnv, 
                                         UInt32        idx,       MultiLightChunk* pMLChunk, 
                                         Transform*    transform, Camera*          camera);

    virtual void    updatePointLight    (RenderAction* a,         DrawEnv*         pEnv, 
                                         UInt32        idx,       MultiLightChunk* pMLChunk, 
                                         Transform*    transform, Camera*          camera);

    virtual void    updateSpotLight     (RenderAction* a,         DrawEnv*         pEnv, 
                                         UInt32        idx,       MultiLightChunk* pMLChunk, 
                                         Transform*    transform, Camera*          camera);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Shader                                   */
    /*! \{                                                                 */

    virtual std::string     getShadowBaseProgramSnippet     () const;

    virtual std::string     getFilterModeDisabledSnippet    () const;
    virtual std::string     getFilterModeSimpleSnippet      () const;

    virtual std::string     getFilterModeBoxSnippet         () const;
    virtual std::string     getFindBlockersBoxSnippet       () const;

    virtual std::string     getFilterModePoissonSnippet     () const;
    virtual std::string     getFindBlockersPoissonSnippet   () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Utility                                      */
    /*! \{                                                                 */

    void    calcOrthoShadowViewVolume   (const Matrix&          matWSFromMS,
                                         const Matrix&          matLSFromWS,
                                         const FrustumVolume&   camFrust,
                                         const BoxVolume&       sceneBB,
                                         Pnt3f&                 lightMin,
                                         Pnt3f&                 lightMax   ) const;
                                         
    Vec2f   calcFrustumSize             (const Matrix&          matWSfromTS) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Update State                                 */
    /*! \{                                                                 */

    bool    getUpdateOffset            () const;
    bool    getUpdateUniformData       () const;
    bool    getUpdateShadowParameter   () const;
    bool    getUpdateDistribution      () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  shadow data                                 */
    /*! \{                                                                 */

    virtual std::size_t         calcShadowDataBufferSize () const = 0;
    virtual std::vector<UInt8>  createShadowDataBuffer   () const = 0;
    virtual void                updateShadowDataState    () = 0;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                shadow parameter                              */
    /*! \{                                                                 */

    virtual std::size_t         calcShadowParamBufferSize() const = 0;
    virtual std::vector<UInt8>  createShadowParamBuffer  () const = 0;
    virtual void                updateShadowParamState   () = 0;

    static  bool                changedShadowParameter  (
                                        FieldContainer*     pFC, 
                                        ConstFieldMaskArg   whichField, 
                                        UInt32              origin);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                filter and search distributions               */
    /*! \{                                                                 */

    virtual std::size_t         calcDistributionBufferSize
                                                    (
                                                        UInt32 filterSize,
                                                        UInt32  searchSize
                                                    ) const;

    virtual std::vector<UInt8>  createDistributionBuffer    () const;
    virtual void                updateDistributionState     ();

    Int32                       getAdaptedFilterDiskSize    () const;
    Int32                       getAdaptedSearchDiskSize    () const;

    Int32                       getAdaptedFilterBoxSize     () const;
    Int32                       getAdaptedSearchBoxSize     () const;

    Real32                      getBiasFactor               () const;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name           texture units and binding points                   */
    /*! \{                                                                 */

    void        initLimits  (Window* win);

    Int32       getSamplerCubeArrayTextureUnit          () const;
    Int32       getSamplerCubeArrayShadowTextureUnit    () const;
    Int32       getSampler2DArrayTextureUnit            () const;
    Int32       getSampler2DArrayShadowTextureUnit      () const;
    Int32       getShadowDataBindingPnt                 () const;
    Int32       getShadowParameterBindingPnt            () const;
    Int32       getDistributionBindingPnt               () const;

    /*! \}                                                                 */

  protected:
    UInt32                                       _uiMode;
  
    Int32                                        _width;
    Int32                                        _height;

    Int32                                        _nTexImages;
    Int32                                        _nShaderStorageBlocks;
    Int32                                        _nUniformBlocks;

    MultiLightShadowStage*                       _pStage;
    MultiLightShadowStageData*                   _pStageData;

    PolygonChunkUnrecPtr                         _polygonChunk;
    DepthClearBackgroundUnrecPtr                 _clearBackground;
    static const Matrix                          _matCubeFaceInv[6];

    ShaderStorageBufferObjStdLayoutChunkUnrecPtr _shadowDataChunk;
    UniformBufferObjStd140ChunkUnrecPtr          _shadowParamChunk;
    UniformBufferObjStd140ChunkUnrecPtr          _distributionChunk;

    Real32                                       _biasFactor;

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    MultiLightShadowTechniqueBase(const MultiLightShadowTechniqueBase &source);
    void operator =(const MultiLightShadowTechniqueBase &source);
};

typedef RefCountPtr<MultiLightShadowTechniqueBase, 
                    MemObjRefCountPolicy> MultiLightShadowTechniqueBaseRefPtr;

OSG_END_NAMESPACE

#include "OSGMultiLightShadowTechniqueBase.inl"

#endif /* _OSGMULTILIGHTSHADOWTECHNIQUEBASE_H_ */
