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
 **     class Skeleton
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSKELETONBASE_H_
#define _OSGSKELETONBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGDynamicsDef.h"

//#include "OSGBaseTypes.h"

#include "OSGAttachmentContainer.h" // Parent

#include "OSGNodeFields.h"              // Roots type
#include "OSGBaseSkeletonJointFields.h" // Joints type
#include "OSGMathFields.h"              // JointMatrices type
#include "OSGSysFields.h"               // UseInvBindMatrix type
#include "OSGOSGAnyFields.h"            // JointsChanged type

#include "OSGSkeletonFields.h"

#include "OSGSkeletonParent.h"

OSG_BEGIN_NAMESPACE


class Skeleton;

//! \brief Skeleton Base Class.

class OSG_DYNAMICS_DLLMAPPING SkeletonBase : public SkeletonParent
{
  public:

    typedef SkeletonParent Inherited;
    typedef AttachmentContainer ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(Skeleton);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        RootsFieldId = Inherited::NextFieldId,
        JointsFieldId = RootsFieldId + 1,
        ParentJointsFieldId = JointsFieldId + 1,
        JointMatricesFieldId = ParentJointsFieldId + 1,
        JointNormalMatricesFieldId = JointMatricesFieldId + 1,
        UseInvBindMatrixFieldId = JointNormalMatricesFieldId + 1,
        CalcNormalMatricesFieldId = UseInvBindMatrixFieldId + 1,
        JointsChangedFieldId = CalcNormalMatricesFieldId + 1,
        NextFieldId = JointsChangedFieldId + 1
    };

    static const OSG::BitVector RootsFieldMask =
        (TypeTraits<BitVector>::One << RootsFieldId);
    static const OSG::BitVector JointsFieldMask =
        (TypeTraits<BitVector>::One << JointsFieldId);
    static const OSG::BitVector ParentJointsFieldMask =
        (TypeTraits<BitVector>::One << ParentJointsFieldId);
    static const OSG::BitVector JointMatricesFieldMask =
        (TypeTraits<BitVector>::One << JointMatricesFieldId);
    static const OSG::BitVector JointNormalMatricesFieldMask =
        (TypeTraits<BitVector>::One << JointNormalMatricesFieldId);
    static const OSG::BitVector UseInvBindMatrixFieldMask =
        (TypeTraits<BitVector>::One << UseInvBindMatrixFieldId);
    static const OSG::BitVector CalcNormalMatricesFieldMask =
        (TypeTraits<BitVector>::One << CalcNormalMatricesFieldId);
    static const OSG::BitVector JointsChangedFieldMask =
        (TypeTraits<BitVector>::One << JointsChangedFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef MFUnrecNodePtr    MFRootsType;
    typedef MFUnrecChildBaseSkeletonJointPtr MFJointsType;
    typedef MFUnrecBaseSkeletonJointPtr MFParentJointsType;
    typedef MFMatrix          MFJointMatricesType;
    typedef MFMatrix          MFJointNormalMatricesType;
    typedef SFBool            SFUseInvBindMatrixType;
    typedef SFBool            SFCalcNormalMatricesType;
    typedef SFOSGAny          SFJointsChangedType;

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

            const MFUnrecNodePtr      *getMFRoots          (void) const;
                  MFUnrecNodePtr      *editMFRoots          (void);
            const MFUnrecChildBaseSkeletonJointPtr *getMFJoints         (void) const;
                  MFUnrecChildBaseSkeletonJointPtr *editMFJoints         (void);
            const MFUnrecBaseSkeletonJointPtr *getMFParentJoints   (void) const;
                  MFUnrecBaseSkeletonJointPtr *editMFParentJoints   (void);

                  MFMatrix            *editMFJointMatrices  (void);
            const MFMatrix            *getMFJointMatrices   (void) const;

                  MFMatrix            *editMFJointNormalMatrices(void);
            const MFMatrix            *getMFJointNormalMatrices (void) const;

                  SFBool              *editSFUseInvBindMatrix(void);
            const SFBool              *getSFUseInvBindMatrix (void) const;

                  SFBool              *editSFCalcNormalMatrices(void);
            const SFBool              *getSFCalcNormalMatrices (void) const;

                  SFOSGAny            *editSFJointsChanged  (void);
            const SFOSGAny            *getSFJointsChanged   (void) const;


                  Node * getRoots          (const UInt32 index) const;

                  BaseSkeletonJoint * getJoints         (const UInt32 index) const;

                  BaseSkeletonJoint * getParentJoints   (const UInt32 index) const;

            MFMatrix           ::reference       editJointMatrices  (const UInt32 index);
            const Matrix              &getJointMatrices   (const UInt32 index) const;

            MFMatrix           ::reference       editJointNormalMatrices(const UInt32 index);
            const Matrix              &getJointNormalMatrices (const UInt32 index) const;

                  bool                &editUseInvBindMatrix(void);
                  bool                 getUseInvBindMatrix (void) const;

                  bool                &editCalcNormalMatrices(void);
                  bool                 getCalcNormalMatrices (void) const;

                  OSGAny              &editJointsChanged  (void);
            const OSGAny              &getJointsChanged   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setUseInvBindMatrix(const bool value);
            void setCalcNormalMatrices(const bool value);
            void setJointsChanged  (const OSGAny &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    void pushToRoots               (Node * const value   );
    void assignRoots              (const MFUnrecNodePtr    &value);
    void removeFromRoots (UInt32               uiIndex );
    void removeObjFromRoots(Node * const value   );
    void clearRoots                 (void                         );

    void pushToJoints              (BaseSkeletonJoint * const value   );
    void assignJoints             (const MFUnrecChildBaseSkeletonJointPtr &value);
    void removeFromJoints (UInt32               uiIndex );
    void removeObjFromJoints(BaseSkeletonJoint * const value   );
    void clearJoints                (void                         );

    void pushToParentJoints           (BaseSkeletonJoint * const value   );
    void assignParentJoints          (const MFUnrecBaseSkeletonJointPtr &value);
    void removeFromParentJoints (UInt32               uiIndex );
    void removeObjFromParentJoints(BaseSkeletonJoint * const value   );
    void clearParentJoints            (void                         );

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

    static  SkeletonTransitPtr  create          (void);
    static  Skeleton           *createEmpty     (void);

    static  SkeletonTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  Skeleton            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  SkeletonTransitPtr  createDependent  (BitVector bFlags);

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

    MFUnrecNodePtr    _mfRoots;
    MFUnrecChildBaseSkeletonJointPtr _mfJoints;
    MFUnrecBaseSkeletonJointPtr _mfParentJoints;
    MFMatrix          _mfJointMatrices;
    MFMatrix          _mfJointNormalMatrices;
    SFBool            _sfUseInvBindMatrix;
    SFBool            _sfCalcNormalMatrices;
    SFOSGAny          _sfJointsChanged;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SkeletonBase(void);
    SkeletonBase(const SkeletonBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkeletonBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const Skeleton *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Child linking                                                */
    /*! \{                                                                 */

    virtual bool unlinkChild(FieldContainer * const pChild,
                             UInt16           const childFieldId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

     GetFieldHandlePtr  getHandleRoots           (void) const;
     EditFieldHandlePtr editHandleRoots          (void);
     GetFieldHandlePtr  getHandleJoints          (void) const;
     EditFieldHandlePtr editHandleJoints         (void);
     GetFieldHandlePtr  getHandleParentJoints    (void) const;
     EditFieldHandlePtr editHandleParentJoints   (void);
     GetFieldHandlePtr  getHandleJointMatrices   (void) const;
     EditFieldHandlePtr editHandleJointMatrices  (void);
     GetFieldHandlePtr  getHandleJointNormalMatrices (void) const;
     EditFieldHandlePtr editHandleJointNormalMatrices(void);
     GetFieldHandlePtr  getHandleUseInvBindMatrix (void) const;
     EditFieldHandlePtr editHandleUseInvBindMatrix(void);
     GetFieldHandlePtr  getHandleCalcNormalMatrices (void) const;
     EditFieldHandlePtr editHandleCalcNormalMatrices(void);
     GetFieldHandlePtr  getHandleJointsChanged   (void) const;
     EditFieldHandlePtr editHandleJointsChanged  (void);

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

            void execSync (      SkeletonBase *pFrom,
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
    void operator =(const SkeletonBase &source);
};

typedef SkeletonBase *SkeletonBaseP;

OSG_END_NAMESPACE

#endif /* _OSGSKELETONBASE_H_ */
