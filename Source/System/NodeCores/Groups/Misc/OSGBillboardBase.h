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
 **     class Billboard
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGBILLBOARDBASE_H_
#define _OSGBILLBOARDBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGGroupDef.h"

#include "OSGBaseTypes.h"

#include "OSGGroup.h" // Parent

#include "OSGVec3fFields.h" // AxisOfRotation type
#include "OSGBoolFields.h" // FocusOnCamera type
#include "OSGBoolFields.h" // AlignToScreen type
#include "OSGReal32Fields.h" // MinAngle type
#include "OSGReal32Fields.h" // MaxAngle type

#include "OSGBillboardFields.h"

OSG_BEGIN_NAMESPACE

class Billboard;

//! \brief Billboard Base Class.

class OSG_GROUP_DLLMAPPING BillboardBase : public Group
{
  public:

    typedef Group Inherited;
    typedef Group ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(Billboard);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        AxisOfRotationFieldId = Inherited::NextFieldId,
        FocusOnCameraFieldId = AxisOfRotationFieldId + 1,
        AlignToScreenFieldId = FocusOnCameraFieldId + 1,
        MinAngleFieldId = AlignToScreenFieldId + 1,
        MaxAngleFieldId = MinAngleFieldId + 1,
        NextFieldId = MaxAngleFieldId + 1
    };

    static const OSG::BitVector AxisOfRotationFieldMask =
        (TypeTraits<BitVector>::One << AxisOfRotationFieldId);
    static const OSG::BitVector FocusOnCameraFieldMask =
        (TypeTraits<BitVector>::One << FocusOnCameraFieldId);
    static const OSG::BitVector AlignToScreenFieldMask =
        (TypeTraits<BitVector>::One << AlignToScreenFieldId);
    static const OSG::BitVector MinAngleFieldMask =
        (TypeTraits<BitVector>::One << MinAngleFieldId);
    static const OSG::BitVector MaxAngleFieldMask =
        (TypeTraits<BitVector>::One << MaxAngleFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFVec3f           SFAxisOfRotationType;
    typedef SFBool            SFFocusOnCameraType;
    typedef SFBool            SFAlignToScreenType;
    typedef SFReal32          SFMinAngleType;
    typedef SFReal32          SFMaxAngleType;

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


                  SFVec3f             *editSFAxisOfRotation (void);
            const SFVec3f             *getSFAxisOfRotation  (void) const;

                  SFBool              *editSFFocusOnCamera  (void);
            const SFBool              *getSFFocusOnCamera   (void) const;

                  SFBool              *editSFAlignToScreen  (void);
            const SFBool              *getSFAlignToScreen   (void) const;

                  SFReal32            *editSFMinAngle       (void);
            const SFReal32            *getSFMinAngle        (void) const;

                  SFReal32            *editSFMaxAngle       (void);
            const SFReal32            *getSFMaxAngle        (void) const;


                  Vec3f               &editAxisOfRotation (void);
            const Vec3f               &getAxisOfRotation  (void) const;

                  bool                &editFocusOnCamera  (void);
                  bool                 getFocusOnCamera   (void) const;

                  bool                &editAlignToScreen  (void);
                  bool                 getAlignToScreen   (void) const;

                  Real32              &editMinAngle       (void);
                  Real32               getMinAngle        (void) const;

                  Real32              &editMaxAngle       (void);
                  Real32               getMaxAngle        (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setAxisOfRotation (const Vec3f &value);
            void setFocusOnCamera  (const bool value);
            void setAlignToScreen  (const bool value);
            void setMinAngle       (const Real32 value);
            void setMaxAngle       (const Real32 value);

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

    static  BillboardTransitPtr  create          (void);
    static  Billboard           *createEmpty     (void);

    static  BillboardTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  Billboard            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  BillboardTransitPtr  createDependent  (BitVector bFlags);

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

    SFVec3f           _sfAxisOfRotation;
    SFBool            _sfFocusOnCamera;
    SFBool            _sfAlignToScreen;
    SFReal32          _sfMinAngle;
    SFReal32          _sfMaxAngle;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BillboardBase(void);
    BillboardBase(const BillboardBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BillboardBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleAxisOfRotation  (void) const;
    EditFieldHandlePtr editHandleAxisOfRotation (void);
    GetFieldHandlePtr  getHandleFocusOnCamera   (void) const;
    EditFieldHandlePtr editHandleFocusOnCamera  (void);
    GetFieldHandlePtr  getHandleAlignToScreen   (void) const;
    EditFieldHandlePtr editHandleAlignToScreen  (void);
    GetFieldHandlePtr  getHandleMinAngle        (void) const;
    EditFieldHandlePtr editHandleMinAngle       (void);
    GetFieldHandlePtr  getHandleMaxAngle        (void) const;
    EditFieldHandlePtr editHandleMaxAngle       (void);

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

            void execSync (      BillboardBase *pFrom,
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
    void operator =(const BillboardBase &source);
};

typedef BillboardBase *BillboardBaseP;

typedef CoredNodeRefPtr  <Billboard> BillboardNodeRefPtr;
typedef CoredNodeMTRefPtr<Billboard> BillboardNodeMTRefPtr;

OSG_END_NAMESPACE

#endif /* _OSGBILLBOARDBASE_H_ */
