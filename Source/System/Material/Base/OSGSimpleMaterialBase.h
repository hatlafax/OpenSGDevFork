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
 **     class SimpleMaterial
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSIMPLEMATERIALBASE_H_
#define _OSGSIMPLEMATERIALBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGBaseTypes.h"

#include "OSGChunkMaterial.h" // Parent

#include "OSGColor3rFields.h" // Ambient type
#include "OSGColor3rFields.h" // Diffuse type
#include "OSGColor3rFields.h" // Specular type
#include "OSGRealFields.h" // Shininess type
#include "OSGColor3rFields.h" // Emission type
#include "OSGRealFields.h" // Transparency type
#include "OSGBoolFields.h" // Lit type
#include "OSGGLenumFields.h" // ColorMaterial type

#include "OSGSimpleMaterialFields.h"

OSG_BEGIN_NAMESPACE

class SimpleMaterial;

//! \brief SimpleMaterial Base Class.

class OSG_SYSTEM_DLLMAPPING SimpleMaterialBase : public ChunkMaterial
{
  public:

    typedef ChunkMaterial Inherited;
    typedef ChunkMaterial ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(SimpleMaterial);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        AmbientFieldId = Inherited::NextFieldId,
        DiffuseFieldId = AmbientFieldId + 1,
        SpecularFieldId = DiffuseFieldId + 1,
        ShininessFieldId = SpecularFieldId + 1,
        EmissionFieldId = ShininessFieldId + 1,
        TransparencyFieldId = EmissionFieldId + 1,
        LitFieldId = TransparencyFieldId + 1,
        ColorMaterialFieldId = LitFieldId + 1,
        NextFieldId = ColorMaterialFieldId + 1
    };

    static const OSG::BitVector AmbientFieldMask =
        (TypeTraits<BitVector>::One << AmbientFieldId);
    static const OSG::BitVector DiffuseFieldMask =
        (TypeTraits<BitVector>::One << DiffuseFieldId);
    static const OSG::BitVector SpecularFieldMask =
        (TypeTraits<BitVector>::One << SpecularFieldId);
    static const OSG::BitVector ShininessFieldMask =
        (TypeTraits<BitVector>::One << ShininessFieldId);
    static const OSG::BitVector EmissionFieldMask =
        (TypeTraits<BitVector>::One << EmissionFieldId);
    static const OSG::BitVector TransparencyFieldMask =
        (TypeTraits<BitVector>::One << TransparencyFieldId);
    static const OSG::BitVector LitFieldMask =
        (TypeTraits<BitVector>::One << LitFieldId);
    static const OSG::BitVector ColorMaterialFieldMask =
        (TypeTraits<BitVector>::One << ColorMaterialFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFColor3r         SFAmbientType;
    typedef SFColor3r         SFDiffuseType;
    typedef SFColor3r         SFSpecularType;
    typedef SFReal            SFShininessType;
    typedef SFColor3r         SFEmissionType;
    typedef SFReal            SFTransparencyType;
    typedef SFBool            SFLitType;
    typedef SFGLenum          SFColorMaterialType;

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


                  SFColor3r           *editSFAmbient        (void);
            const SFColor3r           *getSFAmbient         (void) const;

                  SFColor3r           *editSFDiffuse        (void);
            const SFColor3r           *getSFDiffuse         (void) const;

                  SFColor3r           *editSFSpecular       (void);
            const SFColor3r           *getSFSpecular        (void) const;

                  SFReal              *editSFShininess      (void);
            const SFReal              *getSFShininess       (void) const;

                  SFColor3r           *editSFEmission       (void);
            const SFColor3r           *getSFEmission        (void) const;

                  SFReal              *editSFTransparency   (void);
            const SFReal              *getSFTransparency    (void) const;

                  SFBool              *editSFLit            (void);
            const SFBool              *getSFLit             (void) const;

                  SFGLenum            *editSFColorMaterial  (void);
            const SFGLenum            *getSFColorMaterial   (void) const;


                  Color3r             &editAmbient        (void);
            const Color3r             &getAmbient         (void) const;

                  Color3r             &editDiffuse        (void);
            const Color3r             &getDiffuse         (void) const;

                  Color3r             &editSpecular       (void);
            const Color3r             &getSpecular        (void) const;

                  Real                &editShininess      (void);
            const Real                &getShininess       (void) const;

                  Color3r             &editEmission       (void);
            const Color3r             &getEmission        (void) const;

                  Real                &editTransparency   (void);
            const Real                &getTransparency    (void) const;

                  bool                &editLit            (void);
                  bool                 getLit             (void) const;

                  GLenum              &editColorMaterial  (void);
            const GLenum              &getColorMaterial   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setAmbient        (const Color3r &value);
            void setDiffuse        (const Color3r &value);
            void setSpecular       (const Color3r &value);
            void setShininess      (const Real &value);
            void setEmission       (const Color3r &value);
            void setTransparency   (const Real &value);
            void setLit            (const bool value);
            void setColorMaterial  (const GLenum &value);

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

    static  SimpleMaterialTransitPtr  create          (void);
    static  SimpleMaterial           *createEmpty     (void);

    static  SimpleMaterialTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  SimpleMaterial            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  SimpleMaterialTransitPtr  createDependent  (BitVector bFlags);

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

    SFColor3r         _sfAmbient;
    SFColor3r         _sfDiffuse;
    SFColor3r         _sfSpecular;
    SFReal            _sfShininess;
    SFColor3r         _sfEmission;
    SFReal            _sfTransparency;
    SFBool            _sfLit;
    SFGLenum          _sfColorMaterial;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SimpleMaterialBase(void);
    SimpleMaterialBase(const SimpleMaterialBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleMaterialBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleAmbient         (void) const;
    EditFieldHandlePtr editHandleAmbient        (void);
    GetFieldHandlePtr  getHandleDiffuse         (void) const;
    EditFieldHandlePtr editHandleDiffuse        (void);
    GetFieldHandlePtr  getHandleSpecular        (void) const;
    EditFieldHandlePtr editHandleSpecular       (void);
    GetFieldHandlePtr  getHandleShininess       (void) const;
    EditFieldHandlePtr editHandleShininess      (void);
    GetFieldHandlePtr  getHandleEmission        (void) const;
    EditFieldHandlePtr editHandleEmission       (void);
    GetFieldHandlePtr  getHandleTransparency    (void) const;
    EditFieldHandlePtr editHandleTransparency   (void);
    GetFieldHandlePtr  getHandleLit             (void) const;
    EditFieldHandlePtr editHandleLit            (void);
    GetFieldHandlePtr  getHandleColorMaterial   (void) const;
    EditFieldHandlePtr editHandleColorMaterial  (void);

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

            void execSync (      SimpleMaterialBase *pFrom,
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
    void operator =(const SimpleMaterialBase &source);
};

typedef SimpleMaterialBase *SimpleMaterialBaseP;

OSG_END_NAMESPACE

#endif /* _OSGSIMPLEMATERIALBASE_H_ */
