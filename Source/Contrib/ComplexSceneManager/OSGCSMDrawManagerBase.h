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
 **     class CSMDrawManager
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGCSMDRAWMANAGERBASE_H_
#define _OSGCSMDRAWMANAGERBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribCSMDef.h"

//#include "OSGBaseTypes.h"

#include "OSGAttachmentContainer.h" // Parent

#include "OSGCSMDrawerFields.h"         // Drawer type
#include "OSGSysFields.h"               // Parallel type
#include "OSGBaseFields.h"              // SyncBarrierName type

#include "OSGCSMDrawManagerFields.h"

OSG_BEGIN_NAMESPACE


class CSMDrawManager;

//! \brief CSMDrawManager Base Class.

class OSG_CONTRIBCSM_DLLMAPPING CSMDrawManagerBase : public AttachmentContainer
{
  public:

    typedef AttachmentContainer Inherited;
    typedef AttachmentContainer ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(CSMDrawManager);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        DrawerFieldId = Inherited::NextFieldId,
        ParallelFieldId = DrawerFieldId + 1,
        SyncBarrierNameFieldId = ParallelFieldId + 1,
        SwapBarrierNameFieldId = SyncBarrierNameFieldId + 1,
        NextFieldId = SwapBarrierNameFieldId + 1
    };

    static const OSG::BitVector DrawerFieldMask =
        (TypeTraits<BitVector>::One << DrawerFieldId);
    static const OSG::BitVector ParallelFieldMask =
        (TypeTraits<BitVector>::One << ParallelFieldId);
    static const OSG::BitVector SyncBarrierNameFieldMask =
        (TypeTraits<BitVector>::One << SyncBarrierNameFieldId);
    static const OSG::BitVector SwapBarrierNameFieldMask =
        (TypeTraits<BitVector>::One << SwapBarrierNameFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef MFUnrecCSMDrawerPtr MFDrawerType;
    typedef SFBool            SFParallelType;
    typedef SFString          SFSyncBarrierNameType;
    typedef SFString          SFSwapBarrierNameType;

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

            const MFUnrecCSMDrawerPtr *getMFDrawer         (void) const;
                  MFUnrecCSMDrawerPtr *editMFDrawer         (void);

                  SFBool              *editSFParallel       (void);
            const SFBool              *getSFParallel        (void) const;

                  SFString            *editSFSyncBarrierName(void);
            const SFString            *getSFSyncBarrierName (void) const;

                  SFString            *editSFSwapBarrierName(void);
            const SFString            *getSFSwapBarrierName (void) const;


                  CSMDrawer * getDrawer         (const UInt32 index) const;

                  bool                &editParallel       (void);
                  bool                 getParallel        (void) const;

                  std::string         &editSyncBarrierName(void);
            const std::string         &getSyncBarrierName (void) const;

                  std::string         &editSwapBarrierName(void);
            const std::string         &getSwapBarrierName (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setParallel       (const bool value);
            void setSyncBarrierName(const std::string &value);
            void setSwapBarrierName(const std::string &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    void pushToDrawer              (CSMDrawer * const value   );
    void assignDrawer             (const MFUnrecCSMDrawerPtr &value);
    void removeFromDrawer (UInt32               uiIndex );
    void removeObjFromDrawer(CSMDrawer * const value   );
    void clearDrawer                (void                         );

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

    static  CSMDrawManagerTransitPtr  create          (void);
    static  CSMDrawManager           *createEmpty     (void);

    static  CSMDrawManagerTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  CSMDrawManager            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  CSMDrawManagerTransitPtr  createDependent  (BitVector bFlags);

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

    MFUnrecCSMDrawerPtr _mfDrawer;
    SFBool            _sfParallel;
    SFString          _sfSyncBarrierName;
    SFString          _sfSwapBarrierName;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CSMDrawManagerBase(void);
    CSMDrawManagerBase(const CSMDrawManagerBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CSMDrawManagerBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const CSMDrawManager *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleDrawer          (void) const;
    EditFieldHandlePtr editHandleDrawer         (void);
    GetFieldHandlePtr  getHandleParallel        (void) const;
    EditFieldHandlePtr editHandleParallel       (void);
    GetFieldHandlePtr  getHandleSyncBarrierName (void) const;
    EditFieldHandlePtr editHandleSyncBarrierName(void);
    GetFieldHandlePtr  getHandleSwapBarrierName (void) const;
    EditFieldHandlePtr editHandleSwapBarrierName(void);

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

            void execSync (      CSMDrawManagerBase *pFrom,
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
    void operator =(const CSMDrawManagerBase &source);
};

typedef CSMDrawManagerBase *CSMDrawManagerBaseP;

OSG_END_NAMESPACE

#endif /* _OSGCSMDRAWMANAGERBASE_H_ */
