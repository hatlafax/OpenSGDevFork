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
 **     class MultiLightShadowParameter
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGMULTILIGHTSHADOWPARAMETERBASE_H_
#define _OSGMULTILIGHTSHADOWPARAMETERBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"

//#include "OSGBaseTypes.h"

#include "OSGFieldContainer.h" // Parent

#include "OSGSysFields.h"               // Intensity type

#include "OSGMultiLightShadowParameterFields.h"

OSG_BEGIN_NAMESPACE


class MultiLightShadowParameter;

//! \brief MultiLightShadowParameter Base Class.

class OSG_CONTRIBTECHNIQUES_DLLMAPPING MultiLightShadowParameterBase : public FieldContainer
{
  public:

    typedef FieldContainer Inherited;
    typedef FieldContainer ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(MultiLightShadowParameter);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        IntensityFieldId = Inherited::NextFieldId,
        BiasFieldId = IntensityFieldId + 1,
        FilterModeFieldId = BiasFieldId + 1,
        FilterRadiusFieldId = FilterModeFieldId + 1,
        RandomRotateFilterFieldId = FilterRadiusFieldId + 1,
        UseBlockerSearchFieldId = RandomRotateFilterFieldId + 1,
        UsePCSSFieldId = UseBlockerSearchFieldId + 1,
        NextFieldId = UsePCSSFieldId + 1
    };

    static const OSG::BitVector IntensityFieldMask =
        (TypeTraits<BitVector>::One << IntensityFieldId);
    static const OSG::BitVector BiasFieldMask =
        (TypeTraits<BitVector>::One << BiasFieldId);
    static const OSG::BitVector FilterModeFieldMask =
        (TypeTraits<BitVector>::One << FilterModeFieldId);
    static const OSG::BitVector FilterRadiusFieldMask =
        (TypeTraits<BitVector>::One << FilterRadiusFieldId);
    static const OSG::BitVector RandomRotateFilterFieldMask =
        (TypeTraits<BitVector>::One << RandomRotateFilterFieldId);
    static const OSG::BitVector UseBlockerSearchFieldMask =
        (TypeTraits<BitVector>::One << UseBlockerSearchFieldId);
    static const OSG::BitVector UsePCSSFieldMask =
        (TypeTraits<BitVector>::One << UsePCSSFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFReal32          SFIntensityType;
    typedef SFReal32          SFBiasType;
    typedef SFInt32           SFFilterModeType;
    typedef SFReal32          SFFilterRadiusType;
    typedef SFBool            SFRandomRotateFilterType;
    typedef SFBool            SFUseBlockerSearchType;
    typedef SFBool            SFUsePCSSType;

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


                  SFReal32            *editSFIntensity      (void);
            const SFReal32            *getSFIntensity       (void) const;

                  SFReal32            *editSFBias           (void);
            const SFReal32            *getSFBias            (void) const;

                  SFInt32             *editSFFilterMode     (void);
            const SFInt32             *getSFFilterMode      (void) const;

                  SFReal32            *editSFFilterRadius   (void);
            const SFReal32            *getSFFilterRadius    (void) const;

                  SFBool              *editSFRandomRotateFilter(void);
            const SFBool              *getSFRandomRotateFilter (void) const;

                  SFBool              *editSFUseBlockerSearch(void);
            const SFBool              *getSFUseBlockerSearch (void) const;

                  SFBool              *editSFUsePCSS        (void);
            const SFBool              *getSFUsePCSS         (void) const;


                  Real32              &editIntensity      (void);
                  Real32               getIntensity       (void) const;

                  Real32              &editBias           (void);
                  Real32               getBias            (void) const;

                  Int32               &editFilterMode     (void);
                  Int32                getFilterMode      (void) const;

                  Real32              &editFilterRadius   (void);
                  Real32               getFilterRadius    (void) const;

                  bool                &editRandomRotateFilter(void);
                  bool                 getRandomRotateFilter (void) const;

                  bool                &editUseBlockerSearch(void);
                  bool                 getUseBlockerSearch (void) const;

                  bool                &editUsePCSS        (void);
                  bool                 getUsePCSS         (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setIntensity      (const Real32 value);
            void setBias           (const Real32 value);
            void setFilterMode     (const Int32 value);
            void setFilterRadius   (const Real32 value);
            void setRandomRotateFilter(const bool value);
            void setUseBlockerSearch(const bool value);
            void setUsePCSS        (const bool value);

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

    static  MultiLightShadowParameterTransitPtr  create          (void);
    static  MultiLightShadowParameter           *createEmpty     (void);

    static  MultiLightShadowParameterTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  MultiLightShadowParameter            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  MultiLightShadowParameterTransitPtr  createDependent  (BitVector bFlags);

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

    SFReal32          _sfIntensity;
    SFReal32          _sfBias;
    SFInt32           _sfFilterMode;
    SFReal32          _sfFilterRadius;
    SFBool            _sfRandomRotateFilter;
    SFBool            _sfUseBlockerSearch;
    SFBool            _sfUsePCSS;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    MultiLightShadowParameterBase(void);
    MultiLightShadowParameterBase(const MultiLightShadowParameterBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiLightShadowParameterBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

     GetFieldHandlePtr  getHandleIntensity       (void) const;
     EditFieldHandlePtr editHandleIntensity      (void);
     GetFieldHandlePtr  getHandleBias            (void) const;
     EditFieldHandlePtr editHandleBias           (void);
     GetFieldHandlePtr  getHandleFilterMode      (void) const;
     EditFieldHandlePtr editHandleFilterMode     (void);
     GetFieldHandlePtr  getHandleFilterRadius    (void) const;
     EditFieldHandlePtr editHandleFilterRadius   (void);
     GetFieldHandlePtr  getHandleRandomRotateFilter (void) const;
     EditFieldHandlePtr editHandleRandomRotateFilter(void);
     GetFieldHandlePtr  getHandleUseBlockerSearch (void) const;
     EditFieldHandlePtr editHandleUseBlockerSearch(void);
     GetFieldHandlePtr  getHandleUsePCSS         (void) const;
     EditFieldHandlePtr editHandleUsePCSS        (void);

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

            void execSync (      MultiLightShadowParameterBase *pFrom,
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
    void operator =(const MultiLightShadowParameterBase &source);
};

typedef MultiLightShadowParameterBase *MultiLightShadowParameterBaseP;

OSG_END_NAMESPACE

#endif /* _OSGMULTILIGHTSHADOWPARAMETERBASE_H_ */