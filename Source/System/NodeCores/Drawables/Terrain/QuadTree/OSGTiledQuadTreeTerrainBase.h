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
 **     class TiledQuadTreeTerrain
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGTILEDQUADTREETERRAINBASE_H_
#define _OSGTILEDQUADTREETERRAINBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGDrawableDef.h"

#include "OSGBaseTypes.h"

#include "OSGMaterialGroup.h" // Parent

#include "OSGImageFields.h" // HeightTiles type
#include "OSGMaterialFields.h" // HeightTextures type
#include "OSGUInt32Fields.h" // SizeX type
#include "OSGUInt32Fields.h" // SizeY type
#include "OSGReal32Fields.h" // HeightScale type
#include "OSGReal32Fields.h" // VertexSpacing type
#include "OSGBoolFields.h" // GeoMorphing type
#include "OSGReal32Fields.h" // Detail type
#include "OSGInt32Fields.h" // CurrentX type
#include "OSGInt32Fields.h" // CurrentY type
#include "OSGInt32Fields.h" // SizeROI type
#include "OSGBoolFields.h" // Update type
#include "OSGBoolFields.h" // UpdateTerrain type
#include "OSGBoolFields.h" // PerPixelLighting type

#include "OSGTiledQuadTreeTerrainFields.h"

OSG_BEGIN_NAMESPACE

class TiledQuadTreeTerrain;

//! \brief TiledQuadTreeTerrain Base Class.

class OSG_DRAWABLE_DLLMAPPING TiledQuadTreeTerrainBase : public MaterialGroup
{
  public:

    typedef MaterialGroup Inherited;
    typedef MaterialGroup ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(TiledQuadTreeTerrain);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        HeightTilesFieldId = Inherited::NextFieldId,
        HeightTexturesFieldId = HeightTilesFieldId + 1,
        SizeXFieldId = HeightTexturesFieldId + 1,
        SizeYFieldId = SizeXFieldId + 1,
        HeightScaleFieldId = SizeYFieldId + 1,
        VertexSpacingFieldId = HeightScaleFieldId + 1,
        GeoMorphingFieldId = VertexSpacingFieldId + 1,
        DetailFieldId = GeoMorphingFieldId + 1,
        CurrentXFieldId = DetailFieldId + 1,
        CurrentYFieldId = CurrentXFieldId + 1,
        SizeROIFieldId = CurrentYFieldId + 1,
        UpdateFieldId = SizeROIFieldId + 1,
        UpdateTerrainFieldId = UpdateFieldId + 1,
        PerPixelLightingFieldId = UpdateTerrainFieldId + 1,
        NextFieldId = PerPixelLightingFieldId + 1
    };

    static const OSG::BitVector HeightTilesFieldMask =
        (TypeTraits<BitVector>::One << HeightTilesFieldId);
    static const OSG::BitVector HeightTexturesFieldMask =
        (TypeTraits<BitVector>::One << HeightTexturesFieldId);
    static const OSG::BitVector SizeXFieldMask =
        (TypeTraits<BitVector>::One << SizeXFieldId);
    static const OSG::BitVector SizeYFieldMask =
        (TypeTraits<BitVector>::One << SizeYFieldId);
    static const OSG::BitVector HeightScaleFieldMask =
        (TypeTraits<BitVector>::One << HeightScaleFieldId);
    static const OSG::BitVector VertexSpacingFieldMask =
        (TypeTraits<BitVector>::One << VertexSpacingFieldId);
    static const OSG::BitVector GeoMorphingFieldMask =
        (TypeTraits<BitVector>::One << GeoMorphingFieldId);
    static const OSG::BitVector DetailFieldMask =
        (TypeTraits<BitVector>::One << DetailFieldId);
    static const OSG::BitVector CurrentXFieldMask =
        (TypeTraits<BitVector>::One << CurrentXFieldId);
    static const OSG::BitVector CurrentYFieldMask =
        (TypeTraits<BitVector>::One << CurrentYFieldId);
    static const OSG::BitVector SizeROIFieldMask =
        (TypeTraits<BitVector>::One << SizeROIFieldId);
    static const OSG::BitVector UpdateFieldMask =
        (TypeTraits<BitVector>::One << UpdateFieldId);
    static const OSG::BitVector UpdateTerrainFieldMask =
        (TypeTraits<BitVector>::One << UpdateTerrainFieldId);
    static const OSG::BitVector PerPixelLightingFieldMask =
        (TypeTraits<BitVector>::One << PerPixelLightingFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef MFUnrecImagePtr   MFHeightTilesType;
    typedef MFUnrecMaterialPtr MFHeightTexturesType;
    typedef SFUInt32          SFSizeXType;
    typedef SFUInt32          SFSizeYType;
    typedef SFReal32          SFHeightScaleType;
    typedef SFReal32          SFVertexSpacingType;
    typedef SFBool            SFGeoMorphingType;
    typedef SFReal32          SFDetailType;
    typedef SFInt32           SFCurrentXType;
    typedef SFInt32           SFCurrentYType;
    typedef SFInt32           SFSizeROIType;
    typedef SFBool            SFUpdateType;
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

            const MFUnrecImagePtr     *getMFHeightTiles    (void) const;
                  MFUnrecImagePtr     *editMFHeightTiles    (void);
            const MFUnrecMaterialPtr  *getMFHeightTextures (void) const;
                  MFUnrecMaterialPtr  *editMFHeightTextures (void);

                  SFUInt32            *editSFSizeX          (void);
            const SFUInt32            *getSFSizeX           (void) const;

                  SFUInt32            *editSFSizeY          (void);
            const SFUInt32            *getSFSizeY           (void) const;

                  SFReal32            *editSFHeightScale    (void);
            const SFReal32            *getSFHeightScale     (void) const;

                  SFReal32            *editSFVertexSpacing  (void);
            const SFReal32            *getSFVertexSpacing   (void) const;

                  SFBool              *editSFGeoMorphing    (void);
            const SFBool              *getSFGeoMorphing     (void) const;

                  SFReal32            *editSFDetail         (void);
            const SFReal32            *getSFDetail          (void) const;

                  SFInt32             *editSFCurrentX       (void);
            const SFInt32             *getSFCurrentX        (void) const;

                  SFInt32             *editSFCurrentY       (void);
            const SFInt32             *getSFCurrentY        (void) const;

                  SFInt32             *editSFSizeROI        (void);
            const SFInt32             *getSFSizeROI         (void) const;

                  SFBool              *editSFUpdate         (void);
            const SFBool              *getSFUpdate          (void) const;

                  SFBool              *editSFUpdateTerrain  (void);
            const SFBool              *getSFUpdateTerrain   (void) const;

                  SFBool              *editSFPerPixelLighting(void);
            const SFBool              *getSFPerPixelLighting (void) const;


                  Image * getHeightTiles    (const UInt32 index) const;

                  Material * getHeightTextures (const UInt32 index) const;

                  UInt32              &editSizeX          (void);
                  UInt32               getSizeX           (void) const;

                  UInt32              &editSizeY          (void);
                  UInt32               getSizeY           (void) const;

                  Real32              &editHeightScale    (void);
                  Real32               getHeightScale     (void) const;

                  Real32              &editVertexSpacing  (void);
                  Real32               getVertexSpacing   (void) const;

                  bool                &editGeoMorphing    (void);
                  bool                 getGeoMorphing     (void) const;

                  Real32              &editDetail         (void);
                  Real32               getDetail          (void) const;

                  Int32               &editCurrentX       (void);
                  Int32                getCurrentX        (void) const;

                  Int32               &editCurrentY       (void);
                  Int32                getCurrentY        (void) const;

                  Int32               &editSizeROI        (void);
                  Int32                getSizeROI         (void) const;

                  bool                &editUpdate         (void);
                  bool                 getUpdate          (void) const;

                  bool                &editUpdateTerrain  (void);
                  bool                 getUpdateTerrain   (void) const;

                  bool                &editPerPixelLighting(void);
                  bool                 getPerPixelLighting (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setSizeX          (const UInt32 value);
            void setSizeY          (const UInt32 value);
            void setHeightScale    (const Real32 value);
            void setVertexSpacing  (const Real32 value);
            void setGeoMorphing    (const bool value);
            void setDetail         (const Real32 value);
            void setCurrentX       (const Int32 value);
            void setCurrentY       (const Int32 value);
            void setSizeROI        (const Int32 value);
            void setUpdate         (const bool value);
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

    void pushToHeightTiles           (Image * const value   );
    void assignHeightTiles          (const MFUnrecImagePtr   &value);
    void removeFromHeightTiles (UInt32               uiIndex );
    void removeObjFromHeightTiles(Image * const value   );
    void clearHeightTiles            (void                         );

    void pushToHeightTextures           (Material * const value   );
    void assignHeightTextures          (const MFUnrecMaterialPtr &value);
    void removeFromHeightTextures (UInt32               uiIndex );
    void removeObjFromHeightTextures(Material * const value   );
    void clearHeightTextures            (void                         );

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

    static  TiledQuadTreeTerrainTransitPtr  create          (void);
    static  TiledQuadTreeTerrain           *createEmpty     (void);

    static  TiledQuadTreeTerrainTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  TiledQuadTreeTerrain            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  TiledQuadTreeTerrainTransitPtr  createDependent  (BitVector bFlags);

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

    MFUnrecImagePtr   _mfHeightTiles;
    MFUnrecMaterialPtr _mfHeightTextures;
    SFUInt32          _sfSizeX;
    SFUInt32          _sfSizeY;
    SFReal32          _sfHeightScale;
    SFReal32          _sfVertexSpacing;
    SFBool            _sfGeoMorphing;
    SFReal32          _sfDetail;
    SFInt32           _sfCurrentX;
    SFInt32           _sfCurrentY;
    SFInt32           _sfSizeROI;
    SFBool            _sfUpdate;
    SFBool            _sfUpdateTerrain;
    SFBool            _sfPerPixelLighting;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TiledQuadTreeTerrainBase(void);
    TiledQuadTreeTerrainBase(const TiledQuadTreeTerrainBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TiledQuadTreeTerrainBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const TiledQuadTreeTerrain *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleHeightTiles     (void) const;
    EditFieldHandlePtr editHandleHeightTiles    (void);
    GetFieldHandlePtr  getHandleHeightTextures  (void) const;
    EditFieldHandlePtr editHandleHeightTextures (void);
    GetFieldHandlePtr  getHandleSizeX           (void) const;
    EditFieldHandlePtr editHandleSizeX          (void);
    GetFieldHandlePtr  getHandleSizeY           (void) const;
    EditFieldHandlePtr editHandleSizeY          (void);
    GetFieldHandlePtr  getHandleHeightScale     (void) const;
    EditFieldHandlePtr editHandleHeightScale    (void);
    GetFieldHandlePtr  getHandleVertexSpacing   (void) const;
    EditFieldHandlePtr editHandleVertexSpacing  (void);
    GetFieldHandlePtr  getHandleGeoMorphing     (void) const;
    EditFieldHandlePtr editHandleGeoMorphing    (void);
    GetFieldHandlePtr  getHandleDetail          (void) const;
    EditFieldHandlePtr editHandleDetail         (void);
    GetFieldHandlePtr  getHandleCurrentX        (void) const;
    EditFieldHandlePtr editHandleCurrentX       (void);
    GetFieldHandlePtr  getHandleCurrentY        (void) const;
    EditFieldHandlePtr editHandleCurrentY       (void);
    GetFieldHandlePtr  getHandleSizeROI         (void) const;
    EditFieldHandlePtr editHandleSizeROI        (void);
    GetFieldHandlePtr  getHandleUpdate          (void) const;
    EditFieldHandlePtr editHandleUpdate         (void);
    GetFieldHandlePtr  getHandleUpdateTerrain   (void) const;
    EditFieldHandlePtr editHandleUpdateTerrain  (void);
    GetFieldHandlePtr  getHandlePerPixelLighting (void) const;
    EditFieldHandlePtr editHandlePerPixelLighting(void);

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

            void execSync (      TiledQuadTreeTerrainBase *pFrom,
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
    void operator =(const TiledQuadTreeTerrainBase &source);
};

typedef TiledQuadTreeTerrainBase *TiledQuadTreeTerrainBaseP;

OSG_END_NAMESPACE

#endif /* _OSGTILEDQUADTREETERRAINBASE_H_ */
