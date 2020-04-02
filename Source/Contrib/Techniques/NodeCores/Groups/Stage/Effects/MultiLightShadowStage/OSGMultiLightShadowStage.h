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

#ifndef _OSGMULTILIGHTSHADOWSTAGE_H_
#define _OSGMULTILIGHTSHADOWSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>
#include <utility>

#include "OSGMultiLightShadowStageBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MultiLightShadowStage class. See \ref
           PageEffectGroupsMultiLightShadowStage for a description.
*/

class MultiLightShadowStageData;

class OSG_CONTRIBTECHNIQUES_DLLMAPPING MultiLightShadowStage : public MultiLightShadowStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MultiLightShadowStageBase Inherited;
    typedef MultiLightShadowStage     Self;
  
    /*---------------------------------------------------------------------*/
    /*! \name                      Mode                                    */
    /*! \{                                                                 */

    enum Mode
    {
        NO_SHADOW_MAP = 0,
        SIMPLE_SHADOW_MAP,
        ADVANCED_SHADOW_MAP,
        SIMPLE_TEST_SHADOW_MAP,
    };

    static UInt32   getRequiredMultiLightFeatures(UInt32 mode);
           UInt32   getRequiredMultiLightFeatures(           ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Mode                                    */
    /*! \{                                                                 */

    enum FilterMode
    {
        PCF_MODE_DISABLED = 0,
        PCF_MODE_SIMPLE   = 1,
        PCF_MODE_BOX      = 2,
        PCF_MODE_POISSON  = 3
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Mode                                    */
    /*! \{                                                                 */

    enum FilterDistribution
    {
        PCF_BOX_2x2_POISSON_9     = 0,
        PCF_BOX_4x4_POISSON_16    = 1,
        PCF_BOX_6x6_POISSON_25    = 2,
        PCF_BOX_8x8_POISSON_32    = 3,
        PCF_BOX_10x10_POISSON_64  = 4,
        PCF_BOX_12x12_POISSON_100 = 5,
        PCF_BOX_14x14_POISSON_128 = 6,
        PCF_BOX_16x16_POISSON_256 = 7
    };

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
    /*! \name                Shadow parameter                              */
    /*! \{                                                                 */

    MultiLightShadowParameter* 
                getShadowParameter      (const UInt32 index) const;

    UInt32      getNumShadowParameters  () const;
    UInt32      addShadowParameter      (MultiLightShadowParameter* param);
    void        removeShadowParameter   (MultiLightShadowParameter* param);
    void        removeShadowParameter   (const UInt32 index);
    void        clearShadowParameters   ();
    
    void        changedShadowParameter  (
                            FieldContainer*     pFC, 
                            ConstFieldMaskArg   whichField, 
                            UInt32              origin);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Convenience                                */
    /*! \{                                                                 */

    void        setMapSize          (UInt32 size);
    Int32       getMapSize          () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            Shader Program Snippets                           */
    /*! \{                                                                 */

    std::string getFragmentProgramSnippet       () const;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/

  protected:

    bool _bUpdateOffset;
    bool _bUpdateUniformData;
    bool _bUpdateShadowParameter;
    bool _bUpdateDistribution;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiLightShadowStage(void);
    MultiLightShadowStage(const MultiLightShadowStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiLightShadowStage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */
    static UInt32 _uiShadingLanguageARB;
    static UInt32 _uiFramebufferObjectARB;
    static UInt32 _uiFuncDrawBuffers;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    void onCreate (const MultiLightShadowStage *source        = NULL);
    void onDestroy(      UInt32                 uiContainerId       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);
    
    Action::ResultE     findTransparent     (MultiLightShadowStageData* pData, Node* const node);
    bool                findMultiLightChunk (Node* node);
    MultiLightChunk*    findMultiLightChunk (NodeCore* core);
    MultiLightChunk*    findMultiLightChunk (Material* material);

    bool                inspectMultiLight   (MultiLightShadowStageData* pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Update                                   */
    /*! \{                                                                 */

    bool        getUpdateOffset         () const;
    bool        getUpdateUniformData    () const;
    bool        getUpdateShadowParameter() const;
    bool        getUpdateDistribution   () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Override                                 */
    /*! \{                                                                 */

    void        initOverrideShaderProgram       (
                    MultiLightShadowStageData* pData);
    void        addOverride                     (
                    MultiLightShadowStageData* pData,
                    RenderAction* a);

    std::string getFragmentProgramImplSnippet   () const;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/

  private:

    void clearUpdate();

    class UpdateAutoClear
    {
    public:
        explicit UpdateAutoClear(MultiLightShadowStage* pStage) : _pStage(pStage) {}
        ~UpdateAutoClear()
        {
            _pStage->clearUpdate();
        }
    private:
        MultiLightShadowStage* _pStage;
    };

    friend class FieldContainer;
    friend class MultiLightShadowStageBase;
    friend class MultiLightShadowTechniqueBase;
    friend class UpdateAutoClear;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MultiLightShadowStage &source);
};

typedef MultiLightShadowStage *MultiLightShadowStageP;

OSG_END_NAMESPACE

#include "OSGMultiLightShadowStageBase.inl"
#include "OSGMultiLightShadowStage.inl"

#endif /* _OSGMULTILIGHTSHADOWSTAGE_H_ */
