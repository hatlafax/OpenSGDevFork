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
 **     class ShaderShadowMapEngine
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSHADERSHADOWMAPENGINEBASE_H_
#define _OSGSHADERSHADOWMAPENGINEBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGGroupDef.h"

//#include "OSGBaseTypes.h"

#include "OSGShadowMapEngine.h" // Parent

#include "OSGShaderProgramFields.h"     // ShadowVertexProgram type
#include "OSGSysFields.h"               // ForceTextureUnit type

#include "OSGShaderShadowMapEngineFields.h"

OSG_BEGIN_NAMESPACE


class ShaderShadowMapEngine;

//! \brief ShaderShadowMapEngine Base Class.

class OSG_GROUP_DLLMAPPING ShaderShadowMapEngineBase : public ShadowMapEngine
{
  public:

    typedef ShadowMapEngine Inherited;
    typedef ShadowMapEngine ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(ShaderShadowMapEngine);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        ShadowVertexProgramFieldId = Inherited::NextFieldId,
        ShadowFragmentProgramFieldId = ShadowVertexProgramFieldId + 1,
        ForceTextureUnitFieldId = ShadowFragmentProgramFieldId + 1,
        ShadowNearFieldId = ForceTextureUnitFieldId + 1,
        ShadowFarFieldId = ShadowNearFieldId + 1,
        NextFieldId = ShadowFarFieldId + 1
    };

    static const OSG::BitVector ShadowVertexProgramFieldMask =
        (TypeTraits<BitVector>::One << ShadowVertexProgramFieldId);
    static const OSG::BitVector ShadowFragmentProgramFieldMask =
        (TypeTraits<BitVector>::One << ShadowFragmentProgramFieldId);
    static const OSG::BitVector ForceTextureUnitFieldMask =
        (TypeTraits<BitVector>::One << ForceTextureUnitFieldId);
    static const OSG::BitVector ShadowNearFieldMask =
        (TypeTraits<BitVector>::One << ShadowNearFieldId);
    static const OSG::BitVector ShadowFarFieldMask =
        (TypeTraits<BitVector>::One << ShadowFarFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFUnrecShaderProgramPtr SFShadowVertexProgramType;
    typedef SFUnrecShaderProgramPtr SFShadowFragmentProgramType;
    typedef SFInt32           SFForceTextureUnitType;
    typedef SFReal32          SFShadowNearType;
    typedef SFReal32          SFShadowFarType;

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

            const SFUnrecShaderProgramPtr *getSFShadowVertexProgram(void) const;
                  SFUnrecShaderProgramPtr *editSFShadowVertexProgram(void);
            const SFUnrecShaderProgramPtr *getSFShadowFragmentProgram(void) const;
                  SFUnrecShaderProgramPtr *editSFShadowFragmentProgram(void);

                  SFInt32             *editSFForceTextureUnit(void);
            const SFInt32             *getSFForceTextureUnit (void) const;

                  SFReal32            *editSFShadowNear     (void);
            const SFReal32            *getSFShadowNear      (void) const;

                  SFReal32            *editSFShadowFar      (void);
            const SFReal32            *getSFShadowFar       (void) const;


                  ShaderProgram * getShadowVertexProgram(void) const;

                  ShaderProgram * getShadowFragmentProgram(void) const;

                  Int32               &editForceTextureUnit(void);
                  Int32                getForceTextureUnit (void) const;

                  Real32              &editShadowNear     (void);
                  Real32               getShadowNear      (void) const;

                  Real32              &editShadowFar      (void);
                  Real32               getShadowFar       (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setShadowVertexProgram(ShaderProgram * const value);
            void setShadowFragmentProgram(ShaderProgram * const value);
            void setForceTextureUnit(const Int32 value);
            void setShadowNear     (const Real32 value);
            void setShadowFar      (const Real32 value);

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

    static  ShaderShadowMapEngineTransitPtr  create          (void);
    static  ShaderShadowMapEngine           *createEmpty     (void);

    static  ShaderShadowMapEngineTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  ShaderShadowMapEngine            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  ShaderShadowMapEngineTransitPtr  createDependent  (BitVector bFlags);

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

    SFUnrecShaderProgramPtr _sfShadowVertexProgram;
    SFUnrecShaderProgramPtr _sfShadowFragmentProgram;
    SFInt32           _sfForceTextureUnit;
    SFReal32          _sfShadowNear;
    SFReal32          _sfShadowFar;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ShaderShadowMapEngineBase(void);
    ShaderShadowMapEngineBase(const ShaderShadowMapEngineBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderShadowMapEngineBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const ShaderShadowMapEngine *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleShadowVertexProgram (void) const;
    EditFieldHandlePtr editHandleShadowVertexProgram(void);
    GetFieldHandlePtr  getHandleShadowFragmentProgram (void) const;
    EditFieldHandlePtr editHandleShadowFragmentProgram(void);
    GetFieldHandlePtr  getHandleForceTextureUnit (void) const;
    EditFieldHandlePtr editHandleForceTextureUnit(void);
    GetFieldHandlePtr  getHandleShadowNear      (void) const;
    EditFieldHandlePtr editHandleShadowNear     (void);
    GetFieldHandlePtr  getHandleShadowFar       (void) const;
    EditFieldHandlePtr editHandleShadowFar      (void);

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

            void execSync (      ShaderShadowMapEngineBase *pFrom,
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
    void operator =(const ShaderShadowMapEngineBase &source);
};

typedef ShaderShadowMapEngineBase *ShaderShadowMapEngineBaseP;

OSG_END_NAMESPACE

#endif /* _OSGSHADERSHADOWMAPENGINEBASE_H_ */
