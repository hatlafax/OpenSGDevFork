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
 **     class Light
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGLIGHTBASE_H_
#define _OSGLIGHTBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGBaseTypes.h"

#include "OSGNodeCore.h" // Parent

#include "OSGColor4rFields.h" // Ambient type
#include "OSGColor4rFields.h" // Diffuse type
#include "OSGColor4rFields.h" // Specular type
#include "OSGNodeFields.h" // Beacon type
#include "OSGBoolFields.h" // On type
#include "OSGRealFields.h" // ConstantAttenuation type
#include "OSGRealFields.h" // LinearAttenuation type
#include "OSGRealFields.h" // QuadraticAttenuation type
#include "OSGLightEngineFields.h" // LightEngine type

#include "OSGLightFields.h"

OSG_BEGIN_NAMESPACE

class Light;

//! \brief Light Base Class.

class OSG_SYSTEM_DLLMAPPING LightBase : public NodeCore
{
  public:

    typedef NodeCore Inherited;
    typedef NodeCore ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(Light);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        AmbientFieldId = Inherited::NextFieldId,
        DiffuseFieldId = AmbientFieldId + 1,
        SpecularFieldId = DiffuseFieldId + 1,
        BeaconFieldId = SpecularFieldId + 1,
        OnFieldId = BeaconFieldId + 1,
        ConstantAttenuationFieldId = OnFieldId + 1,
        LinearAttenuationFieldId = ConstantAttenuationFieldId + 1,
        QuadraticAttenuationFieldId = LinearAttenuationFieldId + 1,
        LightEngineFieldId = QuadraticAttenuationFieldId + 1,
        NextFieldId = LightEngineFieldId + 1
    };

    static const OSG::BitVector AmbientFieldMask =
        (TypeTraits<BitVector>::One << AmbientFieldId);
    static const OSG::BitVector DiffuseFieldMask =
        (TypeTraits<BitVector>::One << DiffuseFieldId);
    static const OSG::BitVector SpecularFieldMask =
        (TypeTraits<BitVector>::One << SpecularFieldId);
    static const OSG::BitVector BeaconFieldMask =
        (TypeTraits<BitVector>::One << BeaconFieldId);
    static const OSG::BitVector OnFieldMask =
        (TypeTraits<BitVector>::One << OnFieldId);
    static const OSG::BitVector ConstantAttenuationFieldMask =
        (TypeTraits<BitVector>::One << ConstantAttenuationFieldId);
    static const OSG::BitVector LinearAttenuationFieldMask =
        (TypeTraits<BitVector>::One << LinearAttenuationFieldId);
    static const OSG::BitVector QuadraticAttenuationFieldMask =
        (TypeTraits<BitVector>::One << QuadraticAttenuationFieldId);
    static const OSG::BitVector LightEngineFieldMask =
        (TypeTraits<BitVector>::One << LightEngineFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);

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


#ifdef OSG_1_GET_COMPAT
                  SFColor4r           *getSFAmbient         (void);
#endif
                  SFColor4r           *editSFAmbient        (void);
            const SFColor4r           *getSFAmbient         (void) const;

#ifdef OSG_1_GET_COMPAT
                  SFColor4r           *getSFDiffuse         (void);
#endif
                  SFColor4r           *editSFDiffuse        (void);
            const SFColor4r           *getSFDiffuse         (void) const;

#ifdef OSG_1_GET_COMPAT
                  SFColor4r           *getSFSpecular        (void);
#endif
                  SFColor4r           *editSFSpecular       (void);
            const SFColor4r           *getSFSpecular        (void) const;
            const SFUncountedNodePtr           *getSFBeacon          (void) const;

#ifdef OSG_1_GET_COMPAT
                  SFBool              *getSFOn              (void);
#endif
                  SFBool              *editSFOn             (void);
            const SFBool              *getSFOn              (void) const;

#ifdef OSG_1_GET_COMPAT
                  SFReal              *getSFConstantAttenuation (void);
#endif
                  SFReal              *editSFConstantAttenuation(void);
            const SFReal              *getSFConstantAttenuation (void) const;

#ifdef OSG_1_GET_COMPAT
                  SFReal              *getSFLinearAttenuation (void);
#endif
                  SFReal              *editSFLinearAttenuation(void);
            const SFReal              *getSFLinearAttenuation (void) const;

#ifdef OSG_1_GET_COMPAT
                  SFReal              *getSFQuadraticAttenuation (void);
#endif
                  SFReal              *editSFQuadraticAttenuation(void);
            const SFReal              *getSFQuadraticAttenuation (void) const;
            const SFLightEnginePtr    *getSFLightEngine     (void) const;


#ifdef OSG_1_GET_COMPAT
                  Color4r             &getAmbient         (void);
#endif
                  Color4r             &editAmbient        (void);
            const Color4r             &getAmbient         (void) const;

#ifdef OSG_1_GET_COMPAT
                  Color4r             &getDiffuse         (void);
#endif
                  Color4r             &editDiffuse        (void);
            const Color4r             &getDiffuse         (void) const;

#ifdef OSG_1_GET_COMPAT
                  Color4r             &getSpecular        (void);
#endif
                  Color4r             &editSpecular       (void);
            const Color4r             &getSpecular        (void) const;

                  NodePtrConst getBeacon         (void) const;

#ifdef OSG_1_GET_COMPAT
                  bool                &getOn              (void);
#endif
                  bool                &editOn             (void);
            const bool                &getOn              (void) const;

#ifdef OSG_1_GET_COMPAT
                  Real                &getConstantAttenuation (void);
#endif
                  Real                &editConstantAttenuation(void);
            const Real                &getConstantAttenuation (void) const;

#ifdef OSG_1_GET_COMPAT
                  Real                &getLinearAttenuation (void);
#endif
                  Real                &editLinearAttenuation(void);
            const Real                &getLinearAttenuation (void) const;

#ifdef OSG_1_GET_COMPAT
                  Real                &getQuadraticAttenuation (void);
#endif
                  Real                &editQuadraticAttenuation(void);
            const Real                &getQuadraticAttenuation (void) const;

                  LightEnginePtrConst getLightEngine    (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setAmbient        (const Color4r &value);
            void setDiffuse        (const Color4r &value);
            void setSpecular       (const Color4r &value);
            void setBeacon         (NodePtrConstArg value);
            void setOn             (const bool &value);
            void setConstantAttenuation(const Real &value);
            void setLinearAttenuation(const Real &value);
            void setQuadraticAttenuation(const Real &value);
            void setLightEngine    (LightEnginePtrConstArg value);

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    static void   classDescInserter(TypeObject &oType);
    static Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFColor4r         _sfAmbient;
    SFColor4r         _sfDiffuse;
    SFColor4r         _sfSpecular;
    SFUncountedNodePtr _sfBeacon;
    SFBool            _sfOn;
    SFReal            _sfConstantAttenuation;
    SFReal            _sfLinearAttenuation;
    SFReal            _sfQuadraticAttenuation;
    SFLightEnginePtr  _sfLightEngine;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LightBase(void);
    LightBase(const LightBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LightBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const Light *source = NULL);

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
    GetFieldHandlePtr  getHandleBeacon          (void) const;
    EditFieldHandlePtr editHandleBeacon         (void);
    GetFieldHandlePtr  getHandleOn              (void) const;
    EditFieldHandlePtr editHandleOn             (void);
    GetFieldHandlePtr  getHandleConstantAttenuation (void) const;
    EditFieldHandlePtr editHandleConstantAttenuation(void);
    GetFieldHandlePtr  getHandleLinearAttenuation (void) const;
    EditFieldHandlePtr editHandleLinearAttenuation(void);
    GetFieldHandlePtr  getHandleQuadraticAttenuation (void) const;
    EditFieldHandlePtr editHandleQuadraticAttenuation(void);
    GetFieldHandlePtr  getHandleLightEngine     (void) const;
    EditFieldHandlePtr editHandleLightEngine    (void);

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

            void execSync (      LightBase *pFrom,
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

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LightBase &source);
};

typedef LightBase *LightBaseP;

/** Type specific RefPtr type for Light. */
typedef RefPtr<LightPtr> LightRefPtr;

typedef boost::mpl::if_<
    boost::mpl::bool_<LightBase::isNodeCore>,
    CoredNodePtr<Light>,
    FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC>::type

        LightNodePtr;

OSG_END_NAMESPACE

#endif /* _OSGLIGHTBASE_H_ */
