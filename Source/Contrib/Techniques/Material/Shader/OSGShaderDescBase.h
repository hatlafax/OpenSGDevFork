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
 **     class ShaderDesc
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSHADERDESCBASE_H_
#define _OSGSHADERDESCBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"

//#include "OSGBaseTypes.h"

#include "OSGFieldContainer.h" // Parent

#include "OSGBaseFields.h"              // ShaderType type
#include "OSGSysFields.h"               // Hash type
#include "OSGShaderProgramFields.h"     // ShaderProgram type

#include "OSGShaderDescFields.h"

OSG_BEGIN_NAMESPACE


class ShaderDesc;

//! \brief ShaderDesc Base Class.

class OSG_CONTRIBTECHNIQUES_DLLMAPPING ShaderDescBase : public FieldContainer
{
  public:

    typedef FieldContainer Inherited;
    typedef FieldContainer ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(ShaderDesc);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        ShaderTypeFieldId = Inherited::NextFieldId,
        ProgramFieldId = ShaderTypeFieldId + 1,
        HashFieldId = ProgramFieldId + 1,
        ShaderProgramFieldId = HashFieldId + 1,
        UniformBlockNamesFieldId = ShaderProgramFieldId + 1,
        UniformBindingPntsFieldId = UniformBlockNamesFieldId + 1,
        ShaderStorageBlockNamesFieldId = UniformBindingPntsFieldId + 1,
        ShaderStorageBindingPntsFieldId = ShaderStorageBlockNamesFieldId + 1,
        OSGVariablesFieldId = ShaderStorageBindingPntsFieldId + 1,
        NextFieldId = OSGVariablesFieldId + 1
    };

    static const OSG::BitVector ShaderTypeFieldMask =
        (TypeTraits<BitVector>::One << ShaderTypeFieldId);
    static const OSG::BitVector ProgramFieldMask =
        (TypeTraits<BitVector>::One << ProgramFieldId);
    static const OSG::BitVector HashFieldMask =
        (TypeTraits<BitVector>::One << HashFieldId);
    static const OSG::BitVector ShaderProgramFieldMask =
        (TypeTraits<BitVector>::One << ShaderProgramFieldId);
    static const OSG::BitVector UniformBlockNamesFieldMask =
        (TypeTraits<BitVector>::One << UniformBlockNamesFieldId);
    static const OSG::BitVector UniformBindingPntsFieldMask =
        (TypeTraits<BitVector>::One << UniformBindingPntsFieldId);
    static const OSG::BitVector ShaderStorageBlockNamesFieldMask =
        (TypeTraits<BitVector>::One << ShaderStorageBlockNamesFieldId);
    static const OSG::BitVector ShaderStorageBindingPntsFieldMask =
        (TypeTraits<BitVector>::One << ShaderStorageBindingPntsFieldId);
    static const OSG::BitVector OSGVariablesFieldMask =
        (TypeTraits<BitVector>::One << OSGVariablesFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFGLenum          SFShaderTypeType;
    typedef SFString          SFProgramType;
    typedef SFUInt64          SFHashType;
    typedef SFUnrecShaderProgramPtr SFShaderProgramType;
    typedef MFString          MFUniformBlockNamesType;
    typedef MFInt32           MFUniformBindingPntsType;
    typedef MFString          MFShaderStorageBlockNamesType;
    typedef MFInt32           MFShaderStorageBindingPntsType;
    typedef MFString          MFOSGVariablesType;

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


                  SFGLenum            *editSFShaderType     (void);
            const SFGLenum            *getSFShaderType      (void) const;

                  SFString            *editSFProgram        (void);
            const SFString            *getSFProgram         (void) const;

                  SFUInt64            *editSFHash           (void);
            const SFUInt64            *getSFHash            (void) const;
            const SFUnrecShaderProgramPtr *getSFShaderProgram  (void) const;
                  SFUnrecShaderProgramPtr *editSFShaderProgram  (void);

                  MFString            *editMFUniformBlockNames(void);
            const MFString            *getMFUniformBlockNames (void) const;

                  MFInt32             *editMFUniformBindingPnts(void);
            const MFInt32             *getMFUniformBindingPnts (void) const;

                  MFString            *editMFShaderStorageBlockNames(void);
            const MFString            *getMFShaderStorageBlockNames (void) const;

                  MFInt32             *editMFShaderStorageBindingPnts(void);
            const MFInt32             *getMFShaderStorageBindingPnts (void) const;

                  MFString            *editMFOSGVariables   (void);
            const MFString            *getMFOSGVariables    (void) const;


                  GLenum              &editShaderType     (void);
            const GLenum              &getShaderType      (void) const;

                  std::string         &editProgram        (void);
            const std::string         &getProgram         (void) const;

                  UInt64              &editHash           (void);
                  UInt64               getHash            (void) const;

                  ShaderProgram * getShaderProgram  (void) const;

            MFString           ::reference       editUniformBlockNames(const UInt32 index);
            const std::string         &getUniformBlockNames (const UInt32 index) const;

            MFInt32            ::reference       editUniformBindingPnts(const UInt32 index);
                  Int32                getUniformBindingPnts (const UInt32 index) const;

            MFString           ::reference       editShaderStorageBlockNames(const UInt32 index);
            const std::string         &getShaderStorageBlockNames (const UInt32 index) const;

            MFInt32            ::reference       editShaderStorageBindingPnts(const UInt32 index);
                  Int32                getShaderStorageBindingPnts (const UInt32 index) const;

            MFString           ::reference       editOSGVariables   (const UInt32 index);
            const std::string         &getOSGVariables    (const UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setShaderType     (const GLenum &value);
            void setProgram        (const std::string &value);
            void setHash           (const UInt64 value);
            void setShaderProgram  (ShaderProgram * const value);

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

    static  ShaderDescTransitPtr  create          (void);
    static  ShaderDesc           *createEmpty     (void);

    static  ShaderDescTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  ShaderDesc            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  ShaderDescTransitPtr  createDependent  (BitVector bFlags);

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

    SFGLenum          _sfShaderType;
    SFString          _sfProgram;
    SFUInt64          _sfHash;
    SFUnrecShaderProgramPtr _sfShaderProgram;
    MFString          _mfUniformBlockNames;
    MFInt32           _mfUniformBindingPnts;
    MFString          _mfShaderStorageBlockNames;
    MFInt32           _mfShaderStorageBindingPnts;
    MFString          _mfOSGVariables;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ShaderDescBase(void);
    ShaderDescBase(const ShaderDescBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderDescBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const ShaderDesc *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

     GetFieldHandlePtr  getHandleShaderType      (void) const;
     EditFieldHandlePtr editHandleShaderType     (void);
     GetFieldHandlePtr  getHandleProgram         (void) const;
     EditFieldHandlePtr editHandleProgram        (void);
     GetFieldHandlePtr  getHandleHash            (void) const;
     EditFieldHandlePtr editHandleHash           (void);
     GetFieldHandlePtr  getHandleShaderProgram   (void) const;
     EditFieldHandlePtr editHandleShaderProgram  (void);
     GetFieldHandlePtr  getHandleUniformBlockNames (void) const;
     EditFieldHandlePtr editHandleUniformBlockNames(void);
     GetFieldHandlePtr  getHandleUniformBindingPnts (void) const;
     EditFieldHandlePtr editHandleUniformBindingPnts(void);
     GetFieldHandlePtr  getHandleShaderStorageBlockNames (void) const;
     EditFieldHandlePtr editHandleShaderStorageBlockNames(void);
     GetFieldHandlePtr  getHandleShaderStorageBindingPnts (void) const;
     EditFieldHandlePtr editHandleShaderStorageBindingPnts(void);
     GetFieldHandlePtr  getHandleOSGVariables    (void) const;
     EditFieldHandlePtr editHandleOSGVariables   (void);

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

            void execSync (      ShaderDescBase *pFrom,
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
    void operator =(const ShaderDescBase &source);
};

typedef ShaderDescBase *ShaderDescBaseP;

OSG_END_NAMESPACE

#endif /* _OSGSHADERDESCBASE_H_ */
