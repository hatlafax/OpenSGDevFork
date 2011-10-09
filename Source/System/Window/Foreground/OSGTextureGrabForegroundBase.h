/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class TextureGrabForeground
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGTEXTUREGRABFOREGROUNDBASE_H_
#define _OSGTEXTUREGRABFOREGROUNDBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGWindowDef.h"

//#include "OSGBaseTypes.h"

#include "OSGForeground.h" // Parent

#include "OSGTextureObjChunkFields.h"   // Texture type
#include "OSGSysFields.h"               // AutoResize type
#include "OSGBaseFields.h"              // BindTarget type

#include "OSGTextureGrabForegroundFields.h"

OSG_BEGIN_NAMESPACE


class TextureGrabForeground;

//! \brief TextureGrabForeground Base Class.

class OSG_WINDOW_DLLMAPPING TextureGrabForegroundBase : public Foreground
{
  public:

    typedef Foreground Inherited;
    typedef Foreground ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(TextureGrabForeground);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        TextureFieldId = Inherited::NextFieldId,
        AutoResizeFieldId = TextureFieldId + 1,
        BindTargetFieldId = AutoResizeFieldId + 1,
        CopyTargetFieldId = BindTargetFieldId + 1,
        NextFieldId = CopyTargetFieldId + 1
    };

    static const OSG::BitVector TextureFieldMask =
        (TypeTraits<BitVector>::One << TextureFieldId);
    static const OSG::BitVector AutoResizeFieldMask =
        (TypeTraits<BitVector>::One << AutoResizeFieldId);
    static const OSG::BitVector BindTargetFieldMask =
        (TypeTraits<BitVector>::One << BindTargetFieldId);
    static const OSG::BitVector CopyTargetFieldMask =
        (TypeTraits<BitVector>::One << CopyTargetFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFUnrecTextureObjChunkPtr SFTextureType;
    typedef SFBool            SFAutoResizeType;
    typedef SFGLenum          SFBindTargetType;
    typedef SFGLenum          SFCopyTargetType;

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static FieldContainerType &getClassType   (void);
    static UInt32              getClassTypeId (void);
    static UInt16              getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                FieldContainer Get                            */
    /*! \{                                                                 */

    virtual       FieldContainerType &getType         (void);
    virtual const FieldContainerType &getType         (void) const;

    virtual       UInt32              getContainerSize(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

            const SFUnrecTextureObjChunkPtr *getSFTexture        (void) const;
                  SFUnrecTextureObjChunkPtr *editSFTexture        (void);

                  SFBool              *editSFAutoResize     (void);
            const SFBool              *getSFAutoResize      (void) const;

                  SFGLenum            *editSFBindTarget     (void);
            const SFGLenum            *getSFBindTarget      (void) const;

                  SFGLenum            *editSFCopyTarget     (void);
            const SFGLenum            *getSFCopyTarget      (void) const;


                  TextureObjChunk * getTexture        (void) const;

                  bool                &editAutoResize     (void);
                  bool                 getAutoResize      (void) const;

                  GLenum              &editBindTarget     (void);
            const GLenum              &getBindTarget      (void) const;

                  GLenum              &editCopyTarget     (void);
            const GLenum              &getCopyTarget      (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setTexture        (TextureObjChunk * const value);
            void setAutoResize     (const bool value);
            void setBindTarget     (const GLenum &value);
            void setCopyTarget     (const GLenum &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  TextureGrabForegroundTransitPtr  create          (void);
    static  TextureGrabForeground           *createEmpty     (void);

    static  TextureGrabForegroundTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  TextureGrabForeground            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  TextureGrabForegroundTransitPtr  createDependent  (BitVector bFlags);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerTransitPtr shallowCopy     (void) const;
    virtual FieldContainerTransitPtr shallowCopyLocal(
                                       BitVector bFlags = FCLocal::All) const;
    virtual FieldContainerTransitPtr shallowCopyDependent(
                                                      BitVector bFlags) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    static       void   classDescInserter(TypeObject &oType);
    static const Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFUnrecTextureObjChunkPtr _sfTexture;
    SFBool            _sfAutoResize;
    SFGLenum          _sfBindTarget;
    SFGLenum          _sfCopyTarget;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TextureGrabForegroundBase(void);
    TextureGrabForegroundBase(const TextureGrabForegroundBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureGrabForegroundBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const TextureGrabForeground *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleTexture         (void) const;
    EditFieldHandlePtr editHandleTexture        (void);
    GetFieldHandlePtr  getHandleAutoResize      (void) const;
    EditFieldHandlePtr editHandleAutoResize     (void);
    GetFieldHandlePtr  getHandleBindTarget      (void) const;
    EditFieldHandlePtr editHandleBindTarget     (void);
    GetFieldHandlePtr  getHandleCopyTarget      (void) const;
    EditFieldHandlePtr editHandleCopyTarget     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

            void execSync (      TextureGrabForegroundBase *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Aspect Create                            */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual FieldContainer *createAspectCopy(
                                    const FieldContainer *pRefAspect) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextureGrabForegroundBase &source);
};

typedef TextureGrabForegroundBase *TextureGrabForegroundBaseP;

OSG_END_NAMESPACE

#endif /* _OSGTEXTUREGRABFOREGROUNDBASE_H_ */
