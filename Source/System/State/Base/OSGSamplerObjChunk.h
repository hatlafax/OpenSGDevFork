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

#ifndef _OSGSAMPLEROBJCHUNK_H_
#define _OSGSAMPLEROBJCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSamplerObjChunkBase.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

/*! \brief SamplerObjChunk class. See \ref
           PageSystemSamplerObjChunk for a description.
*/

class OSG_SYSTEM_DLLMAPPING SamplerObjChunk : public SamplerObjChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SamplerObjChunkBase Inherited;
    typedef SamplerObjChunk     Self;
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Texture Units                              */
    /*! \{                                                                 */
  
    void        addTextureUnit  (UInt32 textureUnit);
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    virtual const StateChunkClass *getClass(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    static       UInt32           getStaticClassId(void);
    static const StateChunkClass *getStaticClass  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Chunk Id                                  */
    /*! \{                                                                 */

    virtual UInt16 getChunkId(void);

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

    virtual void   validate               (DrawEnv *pEnv);
    virtual Int32  getOpenGLId            (DrawEnv *pEnv);

    /*! \}                                                                 */
    
    /*=========================  PROTECTED  ===============================*/

  protected:
    UInt16 _uiChunkId;
  
    // Variables should all be in SamplerObjChunkBase.

    void onCreate      (const SamplerObjChunk *source      = NULL);
    void onCreateAspect(const SamplerObjChunk *createAspect,
                        const SamplerObjChunk *source      = NULL);
    void onDestroy     (      UInt32           uiContainerId     );
  
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SamplerObjChunk(void);
    SamplerObjChunk(const SamplerObjChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SamplerObjChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    static StateChunkClass _class;
    static volatile UInt16 _uiChunkCounter;
    
    /*! \}                                                                 */
    
    static UInt32 _arbSamplerObjects;
    
    static UInt32 _funcGenSamplers;
    static UInt32 _funcDeleteSamplers;
    //static UInt32 _funcIsSampler;
    static UInt32 _funcBindSampler;
    static UInt32 _funcSamplerParameteri;
    static UInt32 _funcSamplerParameterf;
    //static UInt32 _funcSamplerParameteriv;
    static UInt32 _funcSamplerParameterfv;
    //static UInt32 _funcSamplerParameterIiv;
    //static UInt32 _funcSamplerParameterIuiv;
    //static UInt32 _funcGetSamplerParameteriv;
    //static UInt32 _funcGetSamplerParameterfv;
    //static UInt32 _funcGetSamplerParameterIiv;
    //static UInt32 _funcGetSamplerParameterIuiv;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SamplerObjChunkBase;

    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

           UInt32 handleGL       (DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode,
                                  UInt64                   uiOptions);

    static void   handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode     );

    /*! \}                                                                 */  
  
    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SamplerObjChunk &source);
};

typedef SamplerObjChunk *SamplerObjChunkP;

OSG_END_NAMESPACE

#include "OSGSamplerObjChunkBase.inl"
#include "OSGSamplerObjChunk.inl"

#endif /* _OSGSAMPLEROBJCHUNK_H_ */
