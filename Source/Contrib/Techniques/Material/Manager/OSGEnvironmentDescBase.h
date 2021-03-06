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
 **     class EnvironmentDesc
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGENVIRONMENTDESCBASE_H_
#define _OSGENVIRONMENTDESCBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"

//#include "OSGBaseTypes.h"

#include "OSGFieldContainer.h" // Parent

#include "OSGSysFields.h"               // Feature type
#include "OSGVecFields.h"               // ClipPlanes type
#include "OSGBaseFields.h"              // FilterColor type

#include "OSGEnvironmentDescFields.h"

OSG_BEGIN_NAMESPACE


class EnvironmentDesc;

//! \brief EnvironmentDesc Base Class.

class OSG_CONTRIBTECHNIQUES_DLLMAPPING EnvironmentDescBase : public FieldContainer
{
  public:

    typedef FieldContainer Inherited;
    typedef FieldContainer ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(EnvironmentDesc);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        FeatureFieldId = Inherited::NextFieldId,
        ClipPlanesFieldId = FeatureFieldId + 1,
        ApplyGammaFieldId = ClipPlanesFieldId + 1,
        AccurateGammaFieldId = ApplyGammaFieldId + 1,
        ToneMappingModeFieldId = AccurateGammaFieldId + 1,
        AutoExposureModeFieldId = ToneMappingModeFieldId + 1,
        Use_ITU_R_BT_709FieldId = AutoExposureModeFieldId + 1,
        UseLinChromCorrectionFieldId = Use_ITU_R_BT_709FieldId + 1,
        ExposureFieldId = UseLinChromCorrectionFieldId + 1,
        KeyValueFieldId = ExposureFieldId + 1,
        ApertureFNumberFieldId = KeyValueFieldId + 1,
        ShutterSpeedFieldId = ApertureFNumberFieldId + 1,
        ISOFieldId = ShutterSpeedFieldId + 1,
        WhiteLevelFieldId = ISOFieldId + 1,
        DragoBiasFieldId = WhiteLevelFieldId + 1,
        SaturationFieldId = DragoBiasFieldId + 1,
        ContrastFieldId = SaturationFieldId + 1,
        GammaFieldId = ContrastFieldId + 1,
        FilterColorFieldId = GammaFieldId + 1,
        GlobalAmbientIntensityFieldId = FilterColorFieldId + 1,
        NextFieldId = GlobalAmbientIntensityFieldId + 1
    };

    static const OSG::BitVector FeatureFieldMask =
        (TypeTraits<BitVector>::One << FeatureFieldId);
    static const OSG::BitVector ClipPlanesFieldMask =
        (TypeTraits<BitVector>::One << ClipPlanesFieldId);
    static const OSG::BitVector ApplyGammaFieldMask =
        (TypeTraits<BitVector>::One << ApplyGammaFieldId);
    static const OSG::BitVector AccurateGammaFieldMask =
        (TypeTraits<BitVector>::One << AccurateGammaFieldId);
    static const OSG::BitVector ToneMappingModeFieldMask =
        (TypeTraits<BitVector>::One << ToneMappingModeFieldId);
    static const OSG::BitVector AutoExposureModeFieldMask =
        (TypeTraits<BitVector>::One << AutoExposureModeFieldId);
    static const OSG::BitVector Use_ITU_R_BT_709FieldMask =
        (TypeTraits<BitVector>::One << Use_ITU_R_BT_709FieldId);
    static const OSG::BitVector UseLinChromCorrectionFieldMask =
        (TypeTraits<BitVector>::One << UseLinChromCorrectionFieldId);
    static const OSG::BitVector ExposureFieldMask =
        (TypeTraits<BitVector>::One << ExposureFieldId);
    static const OSG::BitVector KeyValueFieldMask =
        (TypeTraits<BitVector>::One << KeyValueFieldId);
    static const OSG::BitVector ApertureFNumberFieldMask =
        (TypeTraits<BitVector>::One << ApertureFNumberFieldId);
    static const OSG::BitVector ShutterSpeedFieldMask =
        (TypeTraits<BitVector>::One << ShutterSpeedFieldId);
    static const OSG::BitVector ISOFieldMask =
        (TypeTraits<BitVector>::One << ISOFieldId);
    static const OSG::BitVector WhiteLevelFieldMask =
        (TypeTraits<BitVector>::One << WhiteLevelFieldId);
    static const OSG::BitVector DragoBiasFieldMask =
        (TypeTraits<BitVector>::One << DragoBiasFieldId);
    static const OSG::BitVector SaturationFieldMask =
        (TypeTraits<BitVector>::One << SaturationFieldId);
    static const OSG::BitVector ContrastFieldMask =
        (TypeTraits<BitVector>::One << ContrastFieldId);
    static const OSG::BitVector GammaFieldMask =
        (TypeTraits<BitVector>::One << GammaFieldId);
    static const OSG::BitVector FilterColorFieldMask =
        (TypeTraits<BitVector>::One << FilterColorFieldId);
    static const OSG::BitVector GlobalAmbientIntensityFieldMask =
        (TypeTraits<BitVector>::One << GlobalAmbientIntensityFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFUInt32          SFFeatureType;
    typedef MFVec4f           MFClipPlanesType;
    typedef SFBool            SFApplyGammaType;
    typedef SFBool            SFAccurateGammaType;
    typedef SFUInt32          SFToneMappingModeType;
    typedef SFUInt32          SFAutoExposureModeType;
    typedef SFBool            SFUse_ITU_R_BT_709Type;
    typedef SFBool            SFUseLinChromCorrectionType;
    typedef SFReal32          SFExposureType;
    typedef SFReal32          SFKeyValueType;
    typedef SFReal32          SFApertureFNumberType;
    typedef SFReal32          SFShutterSpeedType;
    typedef SFReal32          SFISOType;
    typedef SFReal32          SFWhiteLevelType;
    typedef SFReal32          SFDragoBiasType;
    typedef SFReal32          SFSaturationType;
    typedef SFReal32          SFContrastType;
    typedef SFReal32          SFGammaType;
    typedef SFColor3f         SFFilterColorType;
    typedef SFVec3f           SFGlobalAmbientIntensityType;

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


                  SFUInt32            *editSFFeature        (void);
            const SFUInt32            *getSFFeature         (void) const;

                  MFVec4f             *editMFClipPlanes     (void);
            const MFVec4f             *getMFClipPlanes      (void) const;

                  SFBool              *editSFApplyGamma     (void);
            const SFBool              *getSFApplyGamma      (void) const;

                  SFBool              *editSFAccurateGamma  (void);
            const SFBool              *getSFAccurateGamma   (void) const;

                  SFUInt32            *editSFToneMappingMode(void);
            const SFUInt32            *getSFToneMappingMode (void) const;

                  SFUInt32            *editSFAutoExposureMode(void);
            const SFUInt32            *getSFAutoExposureMode (void) const;

                  SFBool              *editSFUse_ITU_R_BT_709(void);
            const SFBool              *getSFUse_ITU_R_BT_709 (void) const;

                  SFBool              *editSFUseLinChromCorrection(void);
            const SFBool              *getSFUseLinChromCorrection (void) const;

                  SFReal32            *editSFExposure       (void);
            const SFReal32            *getSFExposure        (void) const;

                  SFReal32            *editSFKeyValue       (void);
            const SFReal32            *getSFKeyValue        (void) const;

                  SFReal32            *editSFApertureFNumber(void);
            const SFReal32            *getSFApertureFNumber (void) const;

                  SFReal32            *editSFShutterSpeed   (void);
            const SFReal32            *getSFShutterSpeed    (void) const;

                  SFReal32            *editSFISO            (void);
            const SFReal32            *getSFISO             (void) const;

                  SFReal32            *editSFWhiteLevel     (void);
            const SFReal32            *getSFWhiteLevel      (void) const;

                  SFReal32            *editSFDragoBias      (void);
            const SFReal32            *getSFDragoBias       (void) const;

                  SFReal32            *editSFSaturation     (void);
            const SFReal32            *getSFSaturation      (void) const;

                  SFReal32            *editSFContrast       (void);
            const SFReal32            *getSFContrast        (void) const;

                  SFReal32            *editSFGamma          (void);
            const SFReal32            *getSFGamma           (void) const;

                  SFColor3f           *editSFFilterColor    (void);
            const SFColor3f           *getSFFilterColor     (void) const;

                  SFVec3f             *editSFGlobalAmbientIntensity(void);
            const SFVec3f             *getSFGlobalAmbientIntensity (void) const;


                  UInt32              &editFeature        (void);
                  UInt32               getFeature         (void) const;

            MFVec4f            ::reference       editClipPlanes     (const UInt32 index);
            const Vec4f               &getClipPlanes      (const UInt32 index) const;

                  bool                &editApplyGamma     (void);
                  bool                 getApplyGamma      (void) const;

                  bool                &editAccurateGamma  (void);
                  bool                 getAccurateGamma   (void) const;

                  UInt32              &editToneMappingMode(void);
                  UInt32               getToneMappingMode (void) const;

                  UInt32              &editAutoExposureMode(void);
                  UInt32               getAutoExposureMode (void) const;

                  bool                &editUse_ITU_R_BT_709(void);
                  bool                 getUse_ITU_R_BT_709 (void) const;

                  bool                &editUseLinChromCorrection(void);
                  bool                 getUseLinChromCorrection (void) const;

                  Real32              &editExposure       (void);
                  Real32               getExposure        (void) const;

                  Real32              &editKeyValue       (void);
                  Real32               getKeyValue        (void) const;

                  Real32              &editApertureFNumber(void);
                  Real32               getApertureFNumber (void) const;

                  Real32              &editShutterSpeed   (void);
                  Real32               getShutterSpeed    (void) const;

                  Real32              &editISO            (void);
                  Real32               getISO             (void) const;

                  Real32              &editWhiteLevel     (void);
                  Real32               getWhiteLevel      (void) const;

                  Real32              &editDragoBias      (void);
                  Real32               getDragoBias       (void) const;

                  Real32              &editSaturation     (void);
                  Real32               getSaturation      (void) const;

                  Real32              &editContrast       (void);
                  Real32               getContrast        (void) const;

                  Real32              &editGamma          (void);
                  Real32               getGamma           (void) const;

                  Color3f             &editFilterColor    (void);
            const Color3f             &getFilterColor     (void) const;

                  Vec3f               &editGlobalAmbientIntensity(void);
            const Vec3f               &getGlobalAmbientIntensity (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setFeature        (const UInt32 value);
            void setApplyGamma     (const bool value);
            void setAccurateGamma  (const bool value);
            void setToneMappingMode(const UInt32 value);
            void setAutoExposureMode(const UInt32 value);
            void setUse_ITU_R_BT_709(const bool value);
            void setUseLinChromCorrection(const bool value);
            void setExposure       (const Real32 value);
            void setKeyValue       (const Real32 value);
            void setApertureFNumber(const Real32 value);
            void setShutterSpeed   (const Real32 value);
            void setISO            (const Real32 value);
            void setWhiteLevel     (const Real32 value);
            void setDragoBias      (const Real32 value);
            void setSaturation     (const Real32 value);
            void setContrast       (const Real32 value);
            void setGamma          (const Real32 value);
            void setFilterColor    (const Color3f &value);
            void setGlobalAmbientIntensity(const Vec3f &value);

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

    static  EnvironmentDescTransitPtr  create          (void);
    static  EnvironmentDesc           *createEmpty     (void);

    static  EnvironmentDescTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  EnvironmentDesc            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  EnvironmentDescTransitPtr  createDependent  (BitVector bFlags);

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

    SFUInt32          _sfFeature;
    MFVec4f           _mfClipPlanes;
    SFBool            _sfApplyGamma;
    SFBool            _sfAccurateGamma;
    SFUInt32          _sfToneMappingMode;
    SFUInt32          _sfAutoExposureMode;
    SFBool            _sfUse_ITU_R_BT_709;
    SFBool            _sfUseLinChromCorrection;
    SFReal32          _sfExposure;
    SFReal32          _sfKeyValue;
    SFReal32          _sfApertureFNumber;
    SFReal32          _sfShutterSpeed;
    SFReal32          _sfISO;
    SFReal32          _sfWhiteLevel;
    SFReal32          _sfDragoBias;
    SFReal32          _sfSaturation;
    SFReal32          _sfContrast;
    SFReal32          _sfGamma;
    SFColor3f         _sfFilterColor;
    SFVec3f           _sfGlobalAmbientIntensity;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    EnvironmentDescBase(void);
    EnvironmentDescBase(const EnvironmentDescBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~EnvironmentDescBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

     GetFieldHandlePtr  getHandleFeature         (void) const;
     EditFieldHandlePtr editHandleFeature        (void);
     GetFieldHandlePtr  getHandleClipPlanes      (void) const;
     EditFieldHandlePtr editHandleClipPlanes     (void);
     GetFieldHandlePtr  getHandleApplyGamma      (void) const;
     EditFieldHandlePtr editHandleApplyGamma     (void);
     GetFieldHandlePtr  getHandleAccurateGamma   (void) const;
     EditFieldHandlePtr editHandleAccurateGamma  (void);
     GetFieldHandlePtr  getHandleToneMappingMode (void) const;
     EditFieldHandlePtr editHandleToneMappingMode(void);
     GetFieldHandlePtr  getHandleAutoExposureMode (void) const;
     EditFieldHandlePtr editHandleAutoExposureMode(void);
     GetFieldHandlePtr  getHandleUse_ITU_R_BT_709 (void) const;
     EditFieldHandlePtr editHandleUse_ITU_R_BT_709(void);
     GetFieldHandlePtr  getHandleUseLinChromCorrection (void) const;
     EditFieldHandlePtr editHandleUseLinChromCorrection(void);
     GetFieldHandlePtr  getHandleExposure        (void) const;
     EditFieldHandlePtr editHandleExposure       (void);
     GetFieldHandlePtr  getHandleKeyValue        (void) const;
     EditFieldHandlePtr editHandleKeyValue       (void);
     GetFieldHandlePtr  getHandleApertureFNumber (void) const;
     EditFieldHandlePtr editHandleApertureFNumber(void);
     GetFieldHandlePtr  getHandleShutterSpeed    (void) const;
     EditFieldHandlePtr editHandleShutterSpeed   (void);
     GetFieldHandlePtr  getHandleISO             (void) const;
     EditFieldHandlePtr editHandleISO            (void);
     GetFieldHandlePtr  getHandleWhiteLevel      (void) const;
     EditFieldHandlePtr editHandleWhiteLevel     (void);
     GetFieldHandlePtr  getHandleDragoBias       (void) const;
     EditFieldHandlePtr editHandleDragoBias      (void);
     GetFieldHandlePtr  getHandleSaturation      (void) const;
     EditFieldHandlePtr editHandleSaturation     (void);
     GetFieldHandlePtr  getHandleContrast        (void) const;
     EditFieldHandlePtr editHandleContrast       (void);
     GetFieldHandlePtr  getHandleGamma           (void) const;
     EditFieldHandlePtr editHandleGamma          (void);
     GetFieldHandlePtr  getHandleFilterColor     (void) const;
     EditFieldHandlePtr editHandleFilterColor    (void);
     GetFieldHandlePtr  getHandleGlobalAmbientIntensity (void) const;
     EditFieldHandlePtr editHandleGlobalAmbientIntensity(void);

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

            void execSync (      EnvironmentDescBase *pFrom,
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
    void operator =(const EnvironmentDescBase &source);
};

typedef EnvironmentDescBase *EnvironmentDescBaseP;

OSG_END_NAMESPACE

#endif /* _OSGENVIRONMENTDESCBASE_H_ */
