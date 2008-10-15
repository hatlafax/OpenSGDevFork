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
 **     class ComplexSceneManager
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGCOMPLEXSCENEMANAGERBASE_H_
#define _OSGCOMPLEXSCENEMANAGERBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribCSMDef.h"

#include "OSGBaseTypes.h"

#include "OSGFieldContainer.h" // Parent

#include "OSGFieldContainerFields.h" // Globals type
#include "OSGDrawManagerFields.h" // DrawManager type
#include "OSGSensorTaskFields.h" // SensorTask type
#include "OSGUInt64Fields.h" // FrameCount type
#include "OSGTimeFields.h" // StartTime type
#include "OSGTimeFields.h" // LastTime type
#include "OSGTimeFields.h" // CurrTime type
#include "OSGTimeFields.h" // TimeStamp type
#include "OSGTimeFields.h" // TimeScale type
#include "OSGTimeFields.h" // ConstantTimeStep type
#include "OSGBoolFields.h" // ConstantTime type
#include "OSGBoolFields.h" // Paused type

#include "OSGComplexSceneManagerFields.h"

OSG_BEGIN_NAMESPACE

class ComplexSceneManager;

//! \brief ComplexSceneManager Base Class.

class OSG_CONTRIBCSM_DLLMAPPING ComplexSceneManagerBase : public FieldContainer
{
  public:

    typedef FieldContainer Inherited;
    typedef FieldContainer ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(ComplexSceneManager);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        GlobalsFieldId = Inherited::NextFieldId,
        DrawManagerFieldId = GlobalsFieldId + 1,
        SensorTaskFieldId = DrawManagerFieldId + 1,
        FrameCountFieldId = SensorTaskFieldId + 1,
        StartTimeFieldId = FrameCountFieldId + 1,
        LastTimeFieldId = StartTimeFieldId + 1,
        CurrTimeFieldId = LastTimeFieldId + 1,
        TimeStampFieldId = CurrTimeFieldId + 1,
        TimeScaleFieldId = TimeStampFieldId + 1,
        ConstantTimeStepFieldId = TimeScaleFieldId + 1,
        ConstantTimeFieldId = ConstantTimeStepFieldId + 1,
        PausedFieldId = ConstantTimeFieldId + 1,
        NextFieldId = PausedFieldId + 1
    };

    static const OSG::BitVector GlobalsFieldMask =
        (TypeTraits<BitVector>::One << GlobalsFieldId);
    static const OSG::BitVector DrawManagerFieldMask =
        (TypeTraits<BitVector>::One << DrawManagerFieldId);
    static const OSG::BitVector SensorTaskFieldMask =
        (TypeTraits<BitVector>::One << SensorTaskFieldId);
    static const OSG::BitVector FrameCountFieldMask =
        (TypeTraits<BitVector>::One << FrameCountFieldId);
    static const OSG::BitVector StartTimeFieldMask =
        (TypeTraits<BitVector>::One << StartTimeFieldId);
    static const OSG::BitVector LastTimeFieldMask =
        (TypeTraits<BitVector>::One << LastTimeFieldId);
    static const OSG::BitVector CurrTimeFieldMask =
        (TypeTraits<BitVector>::One << CurrTimeFieldId);
    static const OSG::BitVector TimeStampFieldMask =
        (TypeTraits<BitVector>::One << TimeStampFieldId);
    static const OSG::BitVector TimeScaleFieldMask =
        (TypeTraits<BitVector>::One << TimeScaleFieldId);
    static const OSG::BitVector ConstantTimeStepFieldMask =
        (TypeTraits<BitVector>::One << ConstantTimeStepFieldId);
    static const OSG::BitVector ConstantTimeFieldMask =
        (TypeTraits<BitVector>::One << ConstantTimeFieldId);
    static const OSG::BitVector PausedFieldMask =
        (TypeTraits<BitVector>::One << PausedFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef MFUnrecFieldContainerPtr MFGlobalsType;
    typedef SFUnrecDrawManagerPtr SFDrawManagerType;
    typedef SFUnrecSensorTaskPtr SFSensorTaskType;
    typedef SFUInt64          SFFrameCountType;
    typedef SFTime            SFStartTimeType;
    typedef SFTime            SFLastTimeType;
    typedef SFTime            SFCurrTimeType;
    typedef SFTime            SFTimeStampType;
    typedef SFTime            SFTimeScaleType;
    typedef SFTime            SFConstantTimeStepType;
    typedef SFBool            SFConstantTimeType;
    typedef SFBool            SFPausedType;

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

            const MFUnrecFieldContainerPtr *getMFGlobals        (void) const;
                  MFUnrecFieldContainerPtr *editMFGlobals        (void);
            const SFUnrecDrawManagerPtr *getSFDrawManager    (void) const;
                  SFUnrecDrawManagerPtr *editSFDrawManager    (void);
            const SFUnrecSensorTaskPtr *getSFSensorTask     (void) const;
                  SFUnrecSensorTaskPtr *editSFSensorTask     (void);

                  SFUInt64            *editSFFrameCount     (void);
            const SFUInt64            *getSFFrameCount      (void) const;

                  SFTime              *editSFStartTime      (void);
            const SFTime              *getSFStartTime       (void) const;

                  SFTime              *editSFLastTime       (void);
            const SFTime              *getSFLastTime        (void) const;

                  SFTime              *editSFCurrTime       (void);
            const SFTime              *getSFCurrTime        (void) const;

                  SFTime              *editSFTimeStamp      (void);
            const SFTime              *getSFTimeStamp       (void) const;

                  SFTime              *editSFTimeScale      (void);
            const SFTime              *getSFTimeScale       (void) const;

                  SFTime              *editSFConstantTimeStep(void);
            const SFTime              *getSFConstantTimeStep (void) const;

                  SFBool              *editSFConstantTime   (void);
            const SFBool              *getSFConstantTime    (void) const;

                  SFBool              *editSFPaused         (void);
            const SFBool              *getSFPaused          (void) const;


                  FieldContainer * getGlobals        (const UInt32 index) const;

                  DrawManager * getDrawManager    (void) const;

                  SensorTask * getSensorTask     (void) const;

                  UInt64              &editFrameCount     (void);
                  UInt64               getFrameCount      (void) const;

                  Time                &editStartTime      (void);
            const Time                &getStartTime       (void) const;

                  Time                &editLastTime       (void);
            const Time                &getLastTime        (void) const;

                  Time                &editCurrTime       (void);
            const Time                &getCurrTime        (void) const;

                  Time                &editTimeStamp      (void);
            const Time                &getTimeStamp       (void) const;

                  Time                &editTimeScale      (void);
            const Time                &getTimeScale       (void) const;

                  Time                &editConstantTimeStep(void);
            const Time                &getConstantTimeStep (void) const;

                  bool                &editConstantTime   (void);
                  bool                 getConstantTime    (void) const;

                  bool                &editPaused         (void);
                  bool                 getPaused          (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setDrawManager    (DrawManager * const value);
            void setSensorTask     (SensorTask * const value);
            void setFrameCount     (const UInt64 value);
            void setStartTime      (const Time &value);
            void setLastTime       (const Time &value);
            void setCurrTime       (const Time &value);
            void setTimeStamp      (const Time &value);
            void setTimeScale      (const Time &value);
            void setConstantTimeStep(const Time &value);
            void setConstantTime   (const bool value);
            void setPaused         (const bool value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    void pushToGlobals             (FieldContainer * const value   );
    void assignGlobals            (const MFUnrecFieldContainerPtr &value);
    void removeFromGlobals (UInt32               uiIndex );
    void removeObjFromGlobals(FieldContainer * const value   );
    void clearGlobals               (void                         );

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

    static  ComplexSceneManagerTransitPtr  create          (void);
    static  ComplexSceneManager           *createEmpty     (void);

    static  ComplexSceneManagerTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  ComplexSceneManager            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  ComplexSceneManagerTransitPtr  createDependent  (BitVector bFlags);

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

    MFUnrecFieldContainerPtr _mfGlobals;
    SFUnrecDrawManagerPtr _sfDrawManager;
    SFUnrecSensorTaskPtr _sfSensorTask;
    SFUInt64          _sfFrameCount;
    SFTime            _sfStartTime;
    SFTime            _sfLastTime;
    SFTime            _sfCurrTime;
    SFTime            _sfTimeStamp;
    SFTime            _sfTimeScale;
    SFTime            _sfConstantTimeStep;
    SFBool            _sfConstantTime;
    SFBool            _sfPaused;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ComplexSceneManagerBase(void);
    ComplexSceneManagerBase(const ComplexSceneManagerBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComplexSceneManagerBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const ComplexSceneManager *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleGlobals         (void) const;
    EditFieldHandlePtr editHandleGlobals        (void);
    GetFieldHandlePtr  getHandleDrawManager     (void) const;
    EditFieldHandlePtr editHandleDrawManager    (void);
    GetFieldHandlePtr  getHandleSensorTask      (void) const;
    EditFieldHandlePtr editHandleSensorTask     (void);
    GetFieldHandlePtr  getHandleFrameCount      (void) const;
    EditFieldHandlePtr editHandleFrameCount     (void);
    GetFieldHandlePtr  getHandleStartTime       (void) const;
    EditFieldHandlePtr editHandleStartTime      (void);
    GetFieldHandlePtr  getHandleLastTime        (void) const;
    EditFieldHandlePtr editHandleLastTime       (void);
    GetFieldHandlePtr  getHandleCurrTime        (void) const;
    EditFieldHandlePtr editHandleCurrTime       (void);
    GetFieldHandlePtr  getHandleTimeStamp       (void) const;
    EditFieldHandlePtr editHandleTimeStamp      (void);
    GetFieldHandlePtr  getHandleTimeScale       (void) const;
    EditFieldHandlePtr editHandleTimeScale      (void);
    GetFieldHandlePtr  getHandleConstantTimeStep (void) const;
    EditFieldHandlePtr editHandleConstantTimeStep(void);
    GetFieldHandlePtr  getHandleConstantTime    (void) const;
    EditFieldHandlePtr editHandleConstantTime   (void);
    GetFieldHandlePtr  getHandlePaused          (void) const;
    EditFieldHandlePtr editHandlePaused         (void);

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

            void execSync (      ComplexSceneManagerBase *pFrom,
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
    void operator =(const ComplexSceneManagerBase &source);
};

typedef ComplexSceneManagerBase *ComplexSceneManagerBaseP;

OSG_END_NAMESPACE

#endif /* _OSGCOMPLEXSCENEMANAGERBASE_H_ */
