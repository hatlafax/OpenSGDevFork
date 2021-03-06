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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class ShaderManager
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSHADERMANAGERBASE_H_
#define _OSGSHADERMANAGERBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"

//#include "OSGBaseTypes.h"

#include "OSGFieldContainer.h" // Parent

#include "OSGHashKeyToFieldContainerMapFields.h" // ProgramChunkMap type
#include "OSGShaderCodeGeneratorFields.h" // CodeGenerator type
#include "OSGShaderProgramManagerFields.h" // ProgramManager type

#include "OSGShaderManagerFields.h"

OSG_BEGIN_NAMESPACE


class ShaderManager;

//! \brief ShaderManager Base Class.

class OSG_CONTRIBTECHNIQUES_DLLMAPPING ShaderManagerBase : public FieldContainer
{
  public:

    typedef FieldContainer Inherited;
    typedef FieldContainer ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(ShaderManager);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        ProgramChunkMapFieldId = Inherited::NextFieldId,
        CodeGeneratorFieldId = ProgramChunkMapFieldId + 1,
        ProgramManagerFieldId = CodeGeneratorFieldId + 1,
        NextFieldId = ProgramManagerFieldId + 1
    };

    static const OSG::BitVector ProgramChunkMapFieldMask =
        (TypeTraits<BitVector>::One << ProgramChunkMapFieldId);
    static const OSG::BitVector CodeGeneratorFieldMask =
        (TypeTraits<BitVector>::One << CodeGeneratorFieldId);
    static const OSG::BitVector ProgramManagerFieldMask =
        (TypeTraits<BitVector>::One << ProgramManagerFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFUnrecHashKeyToFieldContainerMapPtr SFProgramChunkMapType;
    typedef SFUnrecShaderCodeGeneratorPtr SFCodeGeneratorType;
    typedef SFUnrecShaderProgramManagerPtr SFProgramManagerType;

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

            const SFUnrecShaderCodeGeneratorPtr *getSFCodeGenerator  (void) const;
                  SFUnrecShaderCodeGeneratorPtr *editSFCodeGenerator  (void);
            const SFUnrecShaderProgramManagerPtr *getSFProgramManager (void) const;
                  SFUnrecShaderProgramManagerPtr *editSFProgramManager (void);


                  ShaderCodeGenerator * getCodeGenerator  (void) const;

                  ShaderProgramManager * getProgramManager (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setCodeGenerator  (ShaderCodeGenerator * const value);
            void setProgramManager (ShaderProgramManager * const value);

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

    virtual SizeT  getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  ShaderManagerTransitPtr  create          (void);
    static  ShaderManager           *createEmpty     (void);

    static  ShaderManagerTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  ShaderManager            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  ShaderManagerTransitPtr  createDependent  (BitVector bFlags);

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

    SFUnrecHashKeyToFieldContainerMapPtr _sfProgramChunkMap;
    SFUnrecShaderCodeGeneratorPtr _sfCodeGenerator;
    SFUnrecShaderProgramManagerPtr _sfProgramManager;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ShaderManagerBase(void);
    ShaderManagerBase(const ShaderManagerBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderManagerBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const ShaderManager *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

     GetFieldHandlePtr  getHandleProgramChunkMap (void) const;
     EditFieldHandlePtr editHandleProgramChunkMap(void);
     GetFieldHandlePtr  getHandleCodeGenerator   (void) const;
     EditFieldHandlePtr editHandleCodeGenerator  (void);
     GetFieldHandlePtr  getHandleProgramManager  (void) const;
     EditFieldHandlePtr editHandleProgramManager (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

            const SFUnrecHashKeyToFieldContainerMapPtr *getSFProgramChunkMap (void) const;
                  SFUnrecHashKeyToFieldContainerMapPtr *editSFProgramChunkMap(void);


                  HashKeyToFieldContainerMap * getProgramChunkMap(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setProgramChunkMap(HashKeyToFieldContainerMap * const value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

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

            void execSync (      ShaderManagerBase *pFrom,
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
    void operator =(const ShaderManagerBase &source);
};

typedef ShaderManagerBase *ShaderManagerBaseP;

OSG_END_NAMESPACE

#endif /* _OSGSHADERMANAGERBASE_H_ */
