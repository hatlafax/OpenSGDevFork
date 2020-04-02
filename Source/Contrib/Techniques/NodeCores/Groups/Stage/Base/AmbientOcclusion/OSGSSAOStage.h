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

#ifndef _OSGSSAOSTAGE_H_
#define _OSGSSAOSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/container/flat_map.hpp>

#include "OSGSSAOStageBase.h"
#include "OSGAction.h"
#include "OSGSSAOStageDataFields.h"
#include "OSGSimpleSHLChunk.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class RenderAction;
class TextureObjChunk;
class FrameBufferAttachment;

//#define OSG_DEBUG_SSAO_STAGE

/*! \brief SSAOStage class. See \ref
           PageContribTechniquesSSAOStage for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING SSAOStage : public SSAOStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SSAOStageBase Inherited;
    typedef SSAOStage     Self;

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

    // Variables should all be in SSAOStageBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SSAOStage(void);
    SSAOStage(const SSAOStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SSAOStage(void);

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

    Action::ResultE renderEnter (Action *action);
    Action::ResultE renderLeave (Action *action);

    void            renderQuad  ();

    void            addOverride (SSAOStageData* pData, RenderAction* a);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   StageData                                  */
    /*! \{                                                                 */

    SSAOStageDataTransitPtr setupStageData (RenderAction*  pAction,
                                            Int32          iPixelWidth,
                                            Int32          iPixelHeight);

    void                    updateStageData(SSAOStageData* pData,
                                            RenderAction*  pAction,
                                            Int32          iPixelWidth,
                                            Int32          iPixelHeight);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                StageData Details                             */
    /*! \{                                                                 */

    void setupSharedData                 (SSAOStageData* pData);
    void setupRenderTargets              (SSAOStageData* pData, Int32 iWidth, Int32 iHeight);
    void setupMaterials                  (SSAOStageData* pData);

    void updateSharedData                (SSAOStageData* pData);
    void updateRenderTargets             (SSAOStageData* pData, Int32 iWidth, Int32 iHeight);
    void updateMaterials                 (SSAOStageData* pData);

    void setupScenePassRenderTarget      (SSAOStageData* pData, Int32 iWidth, Int32 iHeight);
    void setupSSAOPassRenderTarget       (SSAOStageData* pData, Int32 iWidth, Int32 iHeight);
    void setupBlurPassRenderTarget       (SSAOStageData* pData, Int32 iWidth, Int32 iHeight);
    
    void updateScenePassRenderTarget     (SSAOStageData* pData, Int32 iWidth, Int32 iHeight);
    void updateSSAOPassRenderTarget      (SSAOStageData* pData, Int32 iWidth, Int32 iHeight);
    void updateBlurPassRenderTarget      (SSAOStageData* pData, Int32 iWidth, Int32 iHeight);

    void setupScenePassMaterial          (SSAOStageData* pData);
    void setupSSAOPassMaterial           (SSAOStageData* pData);
    void setupBlurPassMaterial           (SSAOStageData* pData);

    void updateScenePassMaterial         (SSAOStageData* pData);
    void updateSSAOPassMaterial          (SSAOStageData* pData);
    void updateBlurPassMaterial          (SSAOStageData* pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Offset Kernel                              */
    /*! \{                                                                 */

    std::size_t         calcOffsetKernelBufferSize  (Int32 kernelSize) const;
    std::vector<UInt8>  createOffsetKernelBuffer    () const;
    void                updateOffsetKernelState     (SSAOStageData* pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Rotate Kernel                              */
    /*! \{                                                                 */

    std::vector<Vec3f>  createRotateKernelBuffer    (Int32 kernelSize) const;
    void                updateRotateKernelState     (SSAOStageData* pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Postprocess Toolbox                           */
    /*! \{                                                                 */

    void ssaoPass                       (DrawEnv* pEnv, SSAOStageData* pData);
    void blurPass                       (DrawEnv* pEnv, SSAOStageData* pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Shader                                 */
    /*! \{                                                                 */

    SimpleSHLChunkTransitPtr        genScenePassShader  (bool calcPosFromDepth);
    SimpleSHLChunkTransitPtr        genSSAOPassShader   (bool calcPosFromDepth);
    SimpleSHLChunkTransitPtr        genBlurPassShader   ();

    void genScenePassVertexShader       (std::stringstream& ost, bool calcPosFromDepth);
    void genScenePassFragmentShader     (std::stringstream& ost, bool calcPosFromDepth);
    
    void genSSAOPassVertexShader        (std::stringstream& ost, bool calcPosFromDepth);
    void genSSAOPassFragmentShader      (std::stringstream& ost, bool calcPosFromDepth);

    void genBlurPassVertexShader        (std::stringstream& ost);
    void genBlurPassFragmentShader      (std::stringstream& ost);

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
    typedef boost::container::flat_map<SSAOStageData*, bool> UpdateMapT;

    UpdateMapT  _mapUpdate;
    UpdateMapT  _mapUpdateOffsetKernel;
    UpdateMapT  _mapUpdateRotateKernel;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
#ifdef OSG_DEBUG_SSAO_STAGE
    void            dump_fbo    (const char* name, FrameBufferObject* fbo, std::stringstream& ss) const;
    std::string     dump_stage  (SSAOStageData* pData) const;
    void            dump_image (const char* name, FrameBufferAttachment* fba) const;
#endif

    friend class FieldContainer;
    friend class SSAOStageBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SSAOStage &source);
};

typedef SSAOStage *SSAOStageP;

OSG_END_NAMESPACE

#include "OSGSSAOStageBase.inl"
#include "OSGSSAOStage.inl"

#endif /* _OSGSSAOSTAGE_H_ */
