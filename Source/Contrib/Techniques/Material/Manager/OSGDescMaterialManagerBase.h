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
 **     class DescMaterialManager
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGDESCMATERIALMANAGERBASE_H_
#define _OSGDESCMATERIALMANAGERBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"

//#include "OSGBaseTypes.h"

#include "OSGMaterialManager.h" // Parent

#include "OSGMaterialFactoryFields.h"   // MaterialFactory type
#include "OSGHashKeyToFieldContainerMapFields.h" // MaterialMap type
#include "OSGSysFields.h"               // EvalEnvironmentHash type
#include "OSGBaseFields.h"              // ExcludeHashingMask type

#include "OSGDescMaterialManagerFields.h"

OSG_BEGIN_NAMESPACE


class DescMaterialManager;

//! \brief DescMaterialManager Base Class.

class OSG_CONTRIBTECHNIQUES_DLLMAPPING DescMaterialManagerBase : public MaterialManager
{
  public:

    typedef MaterialManager Inherited;
    typedef MaterialManager ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(DescMaterialManager);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        MaterialFactoryFieldId = Inherited::NextFieldId,
        MaterialMapFieldId = MaterialFactoryFieldId + 1,
        ImageMapFieldId = MaterialMapFieldId + 1,
        EvalEnvironmentHashFieldId = ImageMapFieldId + 1,
        ExcludeHashingMaskFieldId = EvalEnvironmentHashFieldId + 1,
        NextFieldId = ExcludeHashingMaskFieldId + 1
    };

    static const OSG::BitVector MaterialFactoryFieldMask =
        (TypeTraits<BitVector>::One << MaterialFactoryFieldId);
    static const OSG::BitVector MaterialMapFieldMask =
        (TypeTraits<BitVector>::One << MaterialMapFieldId);
    static const OSG::BitVector ImageMapFieldMask =
        (TypeTraits<BitVector>::One << ImageMapFieldId);
    static const OSG::BitVector EvalEnvironmentHashFieldMask =
        (TypeTraits<BitVector>::One << EvalEnvironmentHashFieldId);
    static const OSG::BitVector ExcludeHashingMaskFieldMask =
        (TypeTraits<BitVector>::One << ExcludeHashingMaskFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFUnrecMaterialFactoryPtr SFMaterialFactoryType;
    typedef SFUnrecHashKeyToFieldContainerMapPtr SFMaterialMapType;
    typedef SFUnrecHashKeyToFieldContainerMapPtr SFImageMapType;
    typedef SFBool            SFEvalEnvironmentHashType;
    typedef SFBitVector       SFExcludeHashingMaskType;

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

            const SFUnrecMaterialFactoryPtr *getSFMaterialFactory(void) const;
                  SFUnrecMaterialFactoryPtr *editSFMaterialFactory(void);
            const SFUnrecHashKeyToFieldContainerMapPtr *getSFImageMap       (void) const;
                  SFUnrecHashKeyToFieldContainerMapPtr *editSFImageMap       (void);

                  SFBool              *editSFEvalEnvironmentHash(void);
            const SFBool              *getSFEvalEnvironmentHash (void) const;

                  SFBitVector         *editSFExcludeHashingMask(void);
            const SFBitVector         *getSFExcludeHashingMask (void) const;


                  MaterialFactory * getMaterialFactory(void) const;

                  HashKeyToFieldContainerMap * getImageMap       (void) const;

                  bool                &editEvalEnvironmentHash(void);
                  bool                 getEvalEnvironmentHash (void) const;

                  BitVector           &editExcludeHashingMask(void);
            const BitVector           &getExcludeHashingMask (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setMaterialFactory(MaterialFactory * const value);
            void setImageMap       (HashKeyToFieldContainerMap * const value);
            void setEvalEnvironmentHash(const bool value);
            void setExcludeHashingMask(const BitVector &value);

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

    static  DescMaterialManagerTransitPtr  create          (void);
    static  DescMaterialManager           *createEmpty     (void);

    static  DescMaterialManagerTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  DescMaterialManager            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  DescMaterialManagerTransitPtr  createDependent  (BitVector bFlags);

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

    SFUnrecMaterialFactoryPtr _sfMaterialFactory;
    SFUnrecHashKeyToFieldContainerMapPtr _sfMaterialMap;
    SFUnrecHashKeyToFieldContainerMapPtr _sfImageMap;
    SFBool            _sfEvalEnvironmentHash;
    SFBitVector       _sfExcludeHashingMask;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DescMaterialManagerBase(void);
    DescMaterialManagerBase(const DescMaterialManagerBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DescMaterialManagerBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const DescMaterialManager *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

     GetFieldHandlePtr  getHandleMaterialFactory (void) const;
     EditFieldHandlePtr editHandleMaterialFactory(void);
     GetFieldHandlePtr  getHandleMaterialMap     (void) const;
     EditFieldHandlePtr editHandleMaterialMap    (void);
     GetFieldHandlePtr  getHandleImageMap        (void) const;
     EditFieldHandlePtr editHandleImageMap       (void);
     GetFieldHandlePtr  getHandleEvalEnvironmentHash (void) const;
     EditFieldHandlePtr editHandleEvalEnvironmentHash(void);
     GetFieldHandlePtr  getHandleExcludeHashingMask (void) const;
     EditFieldHandlePtr editHandleExcludeHashingMask(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

            const SFUnrecHashKeyToFieldContainerMapPtr *getSFMaterialMap     (void) const;
                  SFUnrecHashKeyToFieldContainerMapPtr *editSFMaterialMap    (void);


                  HashKeyToFieldContainerMap * getMaterialMap    (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setMaterialMap    (HashKeyToFieldContainerMap * const value);

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

            void execSync (      DescMaterialManagerBase *pFrom,
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
    void operator =(const DescMaterialManagerBase &source);
};

typedef DescMaterialManagerBase *DescMaterialManagerBaseP;

OSG_END_NAMESPACE

#endif /* _OSGDESCMATERIALMANAGERBASE_H_ */
