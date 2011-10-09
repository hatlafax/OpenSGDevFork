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
 **     class Particles
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGPARTICLESBASE_H_
#define _OSGPARTICLESBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGDrawableDef.h"

//#include "OSGBaseTypes.h"

#include "OSGMaterialDrawable.h" // Parent

#include "OSGSysFields.h"               // Mode type
#include "OSGGeoVectorPropertyFields.h" // Positions type
#include "OSGVecFields.h"               // Sizes type
#include "OSGParticleBSP.h"             // Bsp type

#include "OSGParticlesFields.h"

OSG_BEGIN_NAMESPACE


class Particles;

//! \brief Particles Base Class.

class OSG_DRAWABLE_DLLMAPPING ParticlesBase : public MaterialDrawable
{
  public:

    typedef MaterialDrawable Inherited;
    typedef MaterialDrawable ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(Particles);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        ModeFieldId = Inherited::NextFieldId,
        PositionsFieldId = ModeFieldId + 1,
        SizesFieldId = PositionsFieldId + 1,
        SecPositionsFieldId = SizesFieldId + 1,
        ColorsFieldId = SecPositionsFieldId + 1,
        NormalsFieldId = ColorsFieldId + 1,
        IndicesFieldId = NormalsFieldId + 1,
        TextureZsFieldId = IndicesFieldId + 1,
        DrawOrderFieldId = TextureZsFieldId + 1,
        DynamicFieldId = DrawOrderFieldId + 1,
        PumpFieldId = DynamicFieldId + 1,
        BspFieldId = PumpFieldId + 1,
        NumParticlesFieldId = BspFieldId + 1,
        NextFieldId = NumParticlesFieldId + 1
    };

    static const OSG::BitVector ModeFieldMask =
        (TypeTraits<BitVector>::One << ModeFieldId);
    static const OSG::BitVector PositionsFieldMask =
        (TypeTraits<BitVector>::One << PositionsFieldId);
    static const OSG::BitVector SizesFieldMask =
        (TypeTraits<BitVector>::One << SizesFieldId);
    static const OSG::BitVector SecPositionsFieldMask =
        (TypeTraits<BitVector>::One << SecPositionsFieldId);
    static const OSG::BitVector ColorsFieldMask =
        (TypeTraits<BitVector>::One << ColorsFieldId);
    static const OSG::BitVector NormalsFieldMask =
        (TypeTraits<BitVector>::One << NormalsFieldId);
    static const OSG::BitVector IndicesFieldMask =
        (TypeTraits<BitVector>::One << IndicesFieldId);
    static const OSG::BitVector TextureZsFieldMask =
        (TypeTraits<BitVector>::One << TextureZsFieldId);
    static const OSG::BitVector DrawOrderFieldMask =
        (TypeTraits<BitVector>::One << DrawOrderFieldId);
    static const OSG::BitVector DynamicFieldMask =
        (TypeTraits<BitVector>::One << DynamicFieldId);
    static const OSG::BitVector PumpFieldMask =
        (TypeTraits<BitVector>::One << PumpFieldId);
    static const OSG::BitVector BspFieldMask =
        (TypeTraits<BitVector>::One << BspFieldId);
    static const OSG::BitVector NumParticlesFieldMask =
        (TypeTraits<BitVector>::One << NumParticlesFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFUInt32          SFModeType;
    typedef SFUnrecChildGeoVectorPropertyPtr SFPositionsType;
    typedef MFVec3f           MFSizesType;
    typedef SFUnrecChildGeoVectorPropertyPtr SFSecPositionsType;
    typedef SFUnrecChildGeoVectorPropertyPtr SFColorsType;
    typedef SFUnrecChildGeoVectorPropertyPtr SFNormalsType;
    typedef MFInt32           MFIndicesType;
    typedef MFReal32          MFTextureZsType;
    typedef SFUInt32          SFDrawOrderType;
    typedef SFBool            SFDynamicType;
    typedef SFUInt32          SFPumpType;
    typedef SFParticleBSPTree SFBspType;
    typedef SFInt32           SFNumParticlesType;

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


                  SFUInt32            *editSFMode           (void);
            const SFUInt32            *getSFMode            (void) const;
            const SFUnrecChildGeoVectorPropertyPtr *getSFPositions      (void) const;
                  SFUnrecChildGeoVectorPropertyPtr *editSFPositions      (void);

                  MFVec3f             *editMFSizes          (void);
            const MFVec3f             *getMFSizes           (void) const;
            const SFUnrecChildGeoVectorPropertyPtr *getSFSecPositions   (void) const;
                  SFUnrecChildGeoVectorPropertyPtr *editSFSecPositions   (void);
            const SFUnrecChildGeoVectorPropertyPtr *getSFColors         (void) const;
                  SFUnrecChildGeoVectorPropertyPtr *editSFColors         (void);
            const SFUnrecChildGeoVectorPropertyPtr *getSFNormals        (void) const;
                  SFUnrecChildGeoVectorPropertyPtr *editSFNormals        (void);

                  MFInt32             *editMFIndices        (void);
            const MFInt32             *getMFIndices         (void) const;

                  MFReal32            *editMFTextureZs      (void);
            const MFReal32            *getMFTextureZs       (void) const;

                  SFUInt32            *editSFDrawOrder      (void);
            const SFUInt32            *getSFDrawOrder       (void) const;

                  SFBool              *editSFDynamic        (void);
            const SFBool              *getSFDynamic         (void) const;

                  SFParticleBSPTree   *editSFBsp            (void);
            const SFParticleBSPTree   *getSFBsp             (void) const;

                  SFInt32             *editSFNumParticles   (void);
            const SFInt32             *getSFNumParticles    (void) const;


                  UInt32              &editMode           (void);
                  UInt32               getMode            (void) const;

                  GeoVectorProperty * getPositions      (void) const;

                  Vec3f               &editSizes          (const UInt32 index);
            const Vec3f               &getSizes           (const UInt32 index) const;

                  GeoVectorProperty * getSecPositions   (void) const;

                  GeoVectorProperty * getColors         (void) const;

                  GeoVectorProperty * getNormals        (void) const;

                  Int32               &editIndices        (const UInt32 index);
                  Int32                getIndices         (const UInt32 index) const;

                  Real32              &editTextureZs      (const UInt32 index);
                  Real32               getTextureZs       (const UInt32 index) const;

                  UInt32              &editDrawOrder      (void);
                  UInt32               getDrawOrder       (void) const;

                  bool                &editDynamic        (void);
                  bool                 getDynamic         (void) const;

                  ParticleBSPTree     &editBsp            (void);
            const ParticleBSPTree     &getBsp             (void) const;

                  Int32               &editNumParticles   (void);
                  Int32                getNumParticles    (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setMode           (const UInt32 value);
            void setPositions      (GeoVectorProperty * const value);
            void setSecPositions   (GeoVectorProperty * const value);
            void setColors         (GeoVectorProperty * const value);
            void setNormals        (GeoVectorProperty * const value);
            void setDrawOrder      (const UInt32 value);
            void setDynamic        (const bool value);
            void setBsp            (const ParticleBSPTree &value);
            void setNumParticles   (const Int32 value);

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

    static  ParticlesTransitPtr  create          (void);
    static  Particles           *createEmpty     (void);

    static  ParticlesTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  Particles            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  ParticlesTransitPtr  createDependent  (BitVector bFlags);

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

    SFUInt32          _sfMode;
    SFUnrecChildGeoVectorPropertyPtr _sfPositions;
    MFVec3f           _mfSizes;
    SFUnrecChildGeoVectorPropertyPtr _sfSecPositions;
    SFUnrecChildGeoVectorPropertyPtr _sfColors;
    SFUnrecChildGeoVectorPropertyPtr _sfNormals;
    MFInt32           _mfIndices;
    MFReal32          _mfTextureZs;
    SFUInt32          _sfDrawOrder;
    SFBool            _sfDynamic;
    SFUInt32          _sfPump;
    SFParticleBSPTree _sfBsp;
    SFInt32           _sfNumParticles;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ParticlesBase(void);
    ParticlesBase(const ParticlesBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticlesBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const Particles *source = NULL);

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

    GetFieldHandlePtr  getHandleMode            (void) const;
    EditFieldHandlePtr editHandleMode           (void);
    GetFieldHandlePtr  getHandlePositions       (void) const;
    EditFieldHandlePtr editHandlePositions      (void);
    GetFieldHandlePtr  getHandleSizes           (void) const;
    EditFieldHandlePtr editHandleSizes          (void);
    GetFieldHandlePtr  getHandleSecPositions    (void) const;
    EditFieldHandlePtr editHandleSecPositions   (void);
    GetFieldHandlePtr  getHandleColors          (void) const;
    EditFieldHandlePtr editHandleColors         (void);
    GetFieldHandlePtr  getHandleNormals         (void) const;
    EditFieldHandlePtr editHandleNormals        (void);
    GetFieldHandlePtr  getHandleIndices         (void) const;
    EditFieldHandlePtr editHandleIndices        (void);
    GetFieldHandlePtr  getHandleTextureZs       (void) const;
    EditFieldHandlePtr editHandleTextureZs      (void);
    GetFieldHandlePtr  getHandleDrawOrder       (void) const;
    EditFieldHandlePtr editHandleDrawOrder      (void);
    GetFieldHandlePtr  getHandleDynamic         (void) const;
    EditFieldHandlePtr editHandleDynamic        (void);
    GetFieldHandlePtr  getHandlePump            (void) const;
    EditFieldHandlePtr editHandlePump           (void);
    GetFieldHandlePtr  getHandleBsp             (void) const;
    EditFieldHandlePtr editHandleBsp            (void);
    GetFieldHandlePtr  getHandleNumParticles    (void) const;
    EditFieldHandlePtr editHandleNumParticles   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


                  SFUInt32            *editSFPump           (void);
            const SFUInt32            *getSFPump            (void) const;


                  UInt32              &editPump           (void);
                  UInt32               getPump            (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setPump           (const UInt32 value);

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

            void execSync (      ParticlesBase *pFrom,
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
    void operator =(const ParticlesBase &source);
};

typedef ParticlesBase *ParticlesBaseP;

OSG_END_NAMESPACE

#endif /* _OSGPARTICLESBASE_H_ */
