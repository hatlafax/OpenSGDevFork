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

#ifndef _OSGIBLSTAGE_H_
#define _OSGIBLSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/container/flat_map.hpp>

#include "OSGIBLStageBase.h"
#include "OSGAction.h"
#include "OSGIBLStageDataFields.h"
#include "OSGSimpleSHLChunk.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class RenderAction;
class TextureObjChunk;
class FrameBufferAttachment;

//#define OSG_DEBUG_IBL_STAGE

/*! \brief IBLStage class. See \ref
           PageContribTechniquesIBLStage for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING IBLStage : public IBLStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef IBLStageBase Inherited;
    typedef IBLStage     Self;

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

    // Variables should all be in IBLStageBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    IBLStage(void);
    IBLStage(const IBLStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~IBLStage(void);

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

    void            addOverride (IBLStageData* pData, RenderAction* a);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   StageData                                  */
    /*! \{                                                                 */

    IBLStageDataTransitPtr  setupStageData (RenderAction*  pAction,
                                            Int32          iPixelWidth,
                                            Int32          iPixelHeight);

    void                    updateStageData(IBLStageData*  pData,
                                            RenderAction*  pAction,
                                            Int32          iPixelWidth,
                                            Int32          iPixelHeight);

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
    typedef boost::container::flat_map<IBLStageData*, bool> UpdateMapT;

    UpdateMapT  _mapUpdate;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
#ifdef OSG_DEBUG_IBL_STAGE
    void            dump_fbo    (const char* name, FrameBufferObject* fbo, std::stringstream& ss) const;
    std::string     dump_stage  (SSAOStageData* pData) const;
    void            dump_image (const char* name, FrameBufferAttachment* fba) const;
#endif

    friend class FieldContainer;
    friend class IBLStageBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const IBLStage &source);
};

typedef IBLStage *IBLStageP;

OSG_END_NAMESPACE

#include "OSGIBLStageBase.inl"
#include "OSGIBLStage.inl"

#endif /* _OSGIBLSTAGE_H_ */
