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
 **     class QuadTreeTerrain
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGQUADTREETERRAINBASE_H_
#define _OSGQUADTREETERRAINBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGDrawableDef.h"

//#include "OSGBaseTypes.h"

#include "OSGGeometry.h" // Parent

#include "OSGImageFields.h"             // HeightData type
#include "OSGSysFields.h"               // HeightScale type
#include "OSGGeoVectorPropertyFields.h" // HeightVertices type
#include "OSGVecFields.h"               // BoundMin type

#include "OSGQuadTreeTerrainFields.h"

OSG_BEGIN_NAMESPACE


class QuadTreeTerrain;

//! \brief QuadTreeTerrain Base Class.

class OSG_DRAWABLE_DLLMAPPING QuadTreeTerrainBase : public Geometry
{
  public:

    typedef Geometry Inherited;
    typedef Geometry ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(QuadTreeTerrain);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        HeightDataFieldId = Inherited::NextFieldId,
        HeightScaleFieldId = HeightDataFieldId + 1,
        HeightErrorFieldId = HeightScaleFieldId + 1,
        HeightQuadFieldId = HeightErrorFieldId + 1,
        WidthFieldId = HeightQuadFieldId + 1,
        LevelFieldId = WidthFieldId + 1,
        DetailFieldId = LevelFieldId + 1,
        BorderDetailFieldId = DetailFieldId + 1,
        VertexSpacingFieldId = BorderDetailFieldId + 1,
        HeightVerticesFieldId = VertexSpacingFieldId + 1,
        GeoMorphingFieldId = HeightVerticesFieldId + 1,
        BoundMinFieldId = GeoMorphingFieldId + 1,
        BoundMaxFieldId = BoundMinFieldId + 1,
        EyePointFieldId = BoundMaxFieldId + 1,
        EyeHeightFieldId = EyePointFieldId + 1,
        EyePointValidFieldId = EyeHeightFieldId + 1,
        OriginXFieldId = EyePointValidFieldId + 1,
        OriginYFieldId = OriginXFieldId + 1,
        OriginTexXFieldId = OriginYFieldId + 1,
        OriginTexYFieldId = OriginTexXFieldId + 1,
        TexSpacingFieldId = OriginTexYFieldId + 1,
        TexYSpacingFieldId = TexSpacingFieldId + 1,
        UpdateTerrainFieldId = TexYSpacingFieldId + 1,
        PerPixelLightingFieldId = UpdateTerrainFieldId + 1,
        NextFieldId = PerPixelLightingFieldId + 1
    };

    static const OSG::BitVector HeightDataFieldMask =
        (TypeTraits<BitVector>::One << HeightDataFieldId);
    static const OSG::BitVector HeightScaleFieldMask =
        (TypeTraits<BitVector>::One << HeightScaleFieldId);
    static const OSG::BitVector HeightErrorFieldMask =
        (TypeTraits<BitVector>::One << HeightErrorFieldId);
    static const OSG::BitVector HeightQuadFieldMask =
        (TypeTraits<BitVector>::One << HeightQuadFieldId);
    static const OSG::BitVector WidthFieldMask =
        (TypeTraits<BitVector>::One << WidthFieldId);
    static const OSG::BitVector LevelFieldMask =
        (TypeTraits<BitVector>::One << LevelFieldId);
    static const OSG::BitVector DetailFieldMask =
        (TypeTraits<BitVector>::One << DetailFieldId);
    static const OSG::BitVector BorderDetailFieldMask =
        (TypeTraits<BitVector>::One << BorderDetailFieldId);
    static const OSG::BitVector VertexSpacingFieldMask =
        (TypeTraits<BitVector>::One << VertexSpacingFieldId);
    static const OSG::BitVector HeightVerticesFieldMask =
        (TypeTraits<BitVector>::One << HeightVerticesFieldId);
    static const OSG::BitVector GeoMorphingFieldMask =
        (TypeTraits<BitVector>::One << GeoMorphingFieldId);
    static const OSG::BitVector BoundMinFieldMask =
        (TypeTraits<BitVector>::One << BoundMinFieldId);
    static const OSG::BitVector BoundMaxFieldMask =
        (TypeTraits<BitVector>::One << BoundMaxFieldId);
    static const OSG::BitVector EyePointFieldMask =
        (TypeTraits<BitVector>::One << EyePointFieldId);
    static const OSG::BitVector EyeHeightFieldMask =
        (TypeTraits<BitVector>::One << EyeHeightFieldId);
    static const OSG::BitVector EyePointValidFieldMask =
        (TypeTraits<BitVector>::One << EyePointValidFieldId);
    static const OSG::BitVector OriginXFieldMask =
        (TypeTraits<BitVector>::One << OriginXFieldId);
    static const OSG::BitVector OriginYFieldMask =
        (TypeTraits<BitVector>::One << OriginYFieldId);
    static const OSG::BitVector OriginTexXFieldMask =
        (TypeTraits<BitVector>::One << OriginTexXFieldId);
    static const OSG::BitVector OriginTexYFieldMask =
        (TypeTraits<BitVector>::One << OriginTexYFieldId);
    static const OSG::BitVector TexSpacingFieldMask =
        (TypeTraits<BitVector>::One << TexSpacingFieldId);
    static const OSG::BitVector TexYSpacingFieldMask =
        (TypeTraits<BitVector>::One << TexYSpacingFieldId);
    static const OSG::BitVector UpdateTerrainFieldMask =
        (TypeTraits<BitVector>::One << UpdateTerrainFieldId);
    static const OSG::BitVector PerPixelLightingFieldMask =
        (TypeTraits<BitVector>::One << PerPixelLightingFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFUnrecImagePtr   SFHeightDataType;
    typedef SFReal32          SFHeightScaleType;
    typedef MFReal32          MFHeightErrorType;
    typedef MFReal32          MFHeightQuadType;
    typedef SFInt32           SFWidthType;
    typedef SFInt32           SFLevelType;
    typedef SFReal32          SFDetailType;
    typedef SFInt32           SFBorderDetailType;
    typedef SFReal32          SFVertexSpacingType;
    typedef SFUnrecGeoVectorPropertyPtr SFHeightVerticesType;
    typedef SFBool            SFGeoMorphingType;
    typedef SFPnt3f           SFBoundMinType;
    typedef SFPnt3f           SFBoundMaxType;
    typedef SFPnt3f           SFEyePointType;
    typedef SFReal32          SFEyeHeightType;
    typedef SFBool            SFEyePointValidType;
    typedef SFReal32          SFOriginXType;
    typedef SFReal32          SFOriginYType;
    typedef SFReal32          SFOriginTexXType;
    typedef SFReal32          SFOriginTexYType;
    typedef SFReal32          SFTexSpacingType;
    typedef SFReal32          SFTexYSpacingType;
    typedef SFBool            SFUpdateTerrainType;
    typedef SFBool            SFPerPixelLightingType;

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

            const SFUnrecImagePtr     *getSFHeightData     (void) const;
                  SFUnrecImagePtr     *editSFHeightData     (void);

                  SFReal32            *editSFHeightScale    (void);
            const SFReal32            *getSFHeightScale     (void) const;

                  MFReal32            *editMFHeightError    (void);
            const MFReal32            *getMFHeightError     (void) const;

                  MFReal32            *editMFHeightQuad     (void);
            const MFReal32            *getMFHeightQuad      (void) const;

                  SFReal32            *editSFDetail         (void);
            const SFReal32            *getSFDetail          (void) const;

                  SFInt32             *editSFBorderDetail   (void);
            const SFInt32             *getSFBorderDetail    (void) const;

                  SFReal32            *editSFVertexSpacing  (void);
            const SFReal32            *getSFVertexSpacing   (void) const;

                  SFBool              *editSFGeoMorphing    (void);
            const SFBool              *getSFGeoMorphing     (void) const;

                  SFPnt3f             *editSFEyePoint       (void);
            const SFPnt3f             *getSFEyePoint        (void) const;

                  SFBool              *editSFEyePointValid  (void);
            const SFBool              *getSFEyePointValid   (void) const;

                  SFReal32            *editSFOriginX        (void);
            const SFReal32            *getSFOriginX         (void) const;

                  SFReal32            *editSFOriginY        (void);
            const SFReal32            *getSFOriginY         (void) const;

                  SFReal32            *editSFOriginTexX     (void);
            const SFReal32            *getSFOriginTexX      (void) const;

                  SFReal32            *editSFOriginTexY     (void);
            const SFReal32            *getSFOriginTexY      (void) const;

                  SFReal32            *editSFTexSpacing     (void);
            const SFReal32            *getSFTexSpacing      (void) const;

                  SFReal32            *editSFTexYSpacing    (void);
            const SFReal32            *getSFTexYSpacing     (void) const;

                  SFBool              *editSFUpdateTerrain  (void);
            const SFBool              *getSFUpdateTerrain   (void) const;

                  SFBool              *editSFPerPixelLighting(void);
            const SFBool              *getSFPerPixelLighting (void) const;


                  Image * getHeightData     (void) const;

                  Real32              &editHeightScale    (void);
                  Real32               getHeightScale     (void) const;

                  Real32              &editHeightError    (const UInt32 index);
                  Real32               getHeightError     (const UInt32 index) const;

                  Real32              &editHeightQuad     (const UInt32 index);
                  Real32               getHeightQuad      (const UInt32 index) const;

                  Real32              &editDetail         (void);
                  Real32               getDetail          (void) const;

                  Int32               &editBorderDetail   (void);
                  Int32                getBorderDetail    (void) const;

                  Real32              &editVertexSpacing  (void);
                  Real32               getVertexSpacing   (void) const;

                  bool                &editGeoMorphing    (void);
                  bool                 getGeoMorphing     (void) const;

                  Pnt3f               &editEyePoint       (void);
            const Pnt3f               &getEyePoint        (void) const;

                  bool                &editEyePointValid  (void);
                  bool                 getEyePointValid   (void) const;

                  Real32              &editOriginX        (void);
                  Real32               getOriginX         (void) const;

                  Real32              &editOriginY        (void);
                  Real32               getOriginY         (void) const;

                  Real32              &editOriginTexX     (void);
                  Real32               getOriginTexX      (void) const;

                  Real32              &editOriginTexY     (void);
                  Real32               getOriginTexY      (void) const;

                  Real32              &editTexSpacing     (void);
                  Real32               getTexSpacing      (void) const;

                  Real32              &editTexYSpacing    (void);
                  Real32               getTexYSpacing     (void) const;

                  bool                &editUpdateTerrain  (void);
                  bool                 getUpdateTerrain   (void) const;

                  bool                &editPerPixelLighting(void);
                  bool                 getPerPixelLighting (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setHeightData     (Image * const value);
            void setHeightScale    (const Real32 value);
            void setDetail         (const Real32 value);
            void setBorderDetail   (const Int32 value);
            void setVertexSpacing  (const Real32 value);
            void setGeoMorphing    (const bool value);
            void setEyePoint       (const Pnt3f &value);
            void setEyePointValid  (const bool value);
            void setOriginX        (const Real32 value);
            void setOriginY        (const Real32 value);
            void setOriginTexX     (const Real32 value);
            void setOriginTexY     (const Real32 value);
            void setTexSpacing     (const Real32 value);
            void setTexYSpacing    (const Real32 value);
            void setUpdateTerrain  (const bool value);
            void setPerPixelLighting(const bool value);

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

    static  QuadTreeTerrainTransitPtr  create          (void);
    static  QuadTreeTerrain           *createEmpty     (void);

    static  QuadTreeTerrainTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  QuadTreeTerrain            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  QuadTreeTerrainTransitPtr  createDependent  (BitVector bFlags);

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

    SFUnrecImagePtr   _sfHeightData;
    SFReal32          _sfHeightScale;
    MFReal32          _mfHeightError;
    MFReal32          _mfHeightQuad;
    SFInt32           _sfWidth;
    SFInt32           _sfLevel;
    SFReal32          _sfDetail;
    SFInt32           _sfBorderDetail;
    SFReal32          _sfVertexSpacing;
    SFUnrecGeoVectorPropertyPtr _sfHeightVertices;
    SFBool            _sfGeoMorphing;
    SFPnt3f           _sfBoundMin;
    SFPnt3f           _sfBoundMax;
    SFPnt3f           _sfEyePoint;
    SFReal32          _sfEyeHeight;
    SFBool            _sfEyePointValid;
    SFReal32          _sfOriginX;
    SFReal32          _sfOriginY;
    SFReal32          _sfOriginTexX;
    SFReal32          _sfOriginTexY;
    SFReal32          _sfTexSpacing;
    SFReal32          _sfTexYSpacing;
    SFBool            _sfUpdateTerrain;
    SFBool            _sfPerPixelLighting;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    QuadTreeTerrainBase(void);
    QuadTreeTerrainBase(const QuadTreeTerrainBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~QuadTreeTerrainBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const QuadTreeTerrain *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleHeightData      (void) const;
    EditFieldHandlePtr editHandleHeightData     (void);
    GetFieldHandlePtr  getHandleHeightScale     (void) const;
    EditFieldHandlePtr editHandleHeightScale    (void);
    GetFieldHandlePtr  getHandleHeightError     (void) const;
    EditFieldHandlePtr editHandleHeightError    (void);
    GetFieldHandlePtr  getHandleHeightQuad      (void) const;
    EditFieldHandlePtr editHandleHeightQuad     (void);
    GetFieldHandlePtr  getHandleWidth           (void) const;
    EditFieldHandlePtr editHandleWidth          (void);
    GetFieldHandlePtr  getHandleLevel           (void) const;
    EditFieldHandlePtr editHandleLevel          (void);
    GetFieldHandlePtr  getHandleDetail          (void) const;
    EditFieldHandlePtr editHandleDetail         (void);
    GetFieldHandlePtr  getHandleBorderDetail    (void) const;
    EditFieldHandlePtr editHandleBorderDetail   (void);
    GetFieldHandlePtr  getHandleVertexSpacing   (void) const;
    EditFieldHandlePtr editHandleVertexSpacing  (void);
    GetFieldHandlePtr  getHandleHeightVertices  (void) const;
    EditFieldHandlePtr editHandleHeightVertices (void);
    GetFieldHandlePtr  getHandleGeoMorphing     (void) const;
    EditFieldHandlePtr editHandleGeoMorphing    (void);
    GetFieldHandlePtr  getHandleBoundMin        (void) const;
    EditFieldHandlePtr editHandleBoundMin       (void);
    GetFieldHandlePtr  getHandleBoundMax        (void) const;
    EditFieldHandlePtr editHandleBoundMax       (void);
    GetFieldHandlePtr  getHandleEyePoint        (void) const;
    EditFieldHandlePtr editHandleEyePoint       (void);
    GetFieldHandlePtr  getHandleEyeHeight       (void) const;
    EditFieldHandlePtr editHandleEyeHeight      (void);
    GetFieldHandlePtr  getHandleEyePointValid   (void) const;
    EditFieldHandlePtr editHandleEyePointValid  (void);
    GetFieldHandlePtr  getHandleOriginX         (void) const;
    EditFieldHandlePtr editHandleOriginX        (void);
    GetFieldHandlePtr  getHandleOriginY         (void) const;
    EditFieldHandlePtr editHandleOriginY        (void);
    GetFieldHandlePtr  getHandleOriginTexX      (void) const;
    EditFieldHandlePtr editHandleOriginTexX     (void);
    GetFieldHandlePtr  getHandleOriginTexY      (void) const;
    EditFieldHandlePtr editHandleOriginTexY     (void);
    GetFieldHandlePtr  getHandleTexSpacing      (void) const;
    EditFieldHandlePtr editHandleTexSpacing     (void);
    GetFieldHandlePtr  getHandleTexYSpacing     (void) const;
    EditFieldHandlePtr editHandleTexYSpacing    (void);
    GetFieldHandlePtr  getHandleUpdateTerrain   (void) const;
    EditFieldHandlePtr editHandleUpdateTerrain  (void);
    GetFieldHandlePtr  getHandlePerPixelLighting (void) const;
    EditFieldHandlePtr editHandlePerPixelLighting(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


                  SFInt32             *editSFWidth          (void);
            const SFInt32             *getSFWidth           (void) const;

                  SFInt32             *editSFLevel          (void);
            const SFInt32             *getSFLevel           (void) const;
            const SFUnrecGeoVectorPropertyPtr *getSFHeightVertices  (void) const;
                  SFUnrecGeoVectorPropertyPtr *editSFHeightVertices (void);

                  SFPnt3f             *editSFBoundMin       (void);
            const SFPnt3f             *getSFBoundMin        (void) const;

                  SFPnt3f             *editSFBoundMax       (void);
            const SFPnt3f             *getSFBoundMax        (void) const;

                  SFReal32            *editSFEyeHeight      (void);
            const SFReal32            *getSFEyeHeight       (void) const;


                  Int32               &editWidth          (void);
                  Int32                getWidth           (void) const;

                  Int32               &editLevel          (void);
                  Int32                getLevel           (void) const;

                  GeoVectorProperty * getHeightVertices (void) const;

                  Pnt3f               &editBoundMin       (void);
            const Pnt3f               &getBoundMin        (void) const;

                  Pnt3f               &editBoundMax       (void);
            const Pnt3f               &getBoundMax        (void) const;

                  Real32              &editEyeHeight      (void);
                  Real32               getEyeHeight       (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setWidth          (const Int32 value);
            void setLevel          (const Int32 value);
            void setHeightVertices (GeoVectorProperty * const value);
            void setBoundMin       (const Pnt3f &value);
            void setBoundMax       (const Pnt3f &value);
            void setEyeHeight      (const Real32 value);

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

            void execSync (      QuadTreeTerrainBase *pFrom,
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
    void operator =(const QuadTreeTerrainBase &source);
};

typedef QuadTreeTerrainBase *QuadTreeTerrainBaseP;

OSG_END_NAMESPACE

#endif /* _OSGQUADTREETERRAINBASE_H_ */
