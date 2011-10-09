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
 **     class Manipulator
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGMANIPULATORBASE_H_
#define _OSGMANIPULATORBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribGUIDef.h"

//#include "OSGBaseTypes.h"

#include "OSGTransform.h" // Parent

#include "OSGNodeFields.h"              // Target type
#include "OSGSysFields.h"               // EnablePivot type
#include "OSGVecFields.h"               // LastMousePos type
#include "OSGViewportFields.h"          // Viewport type
#include "OSGMaterialFields.h"          // MaterialX type

#include "OSGManipulatorFields.h"

OSG_BEGIN_NAMESPACE


class Manipulator;

//! \brief Manipulator Base Class.

class OSG_CONTRIBGUI_DLLMAPPING ManipulatorBase : public Transform
{
  public:

    typedef Transform Inherited;
    typedef Transform ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(Manipulator);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        TargetFieldId = Inherited::NextFieldId,
        EnablePivotFieldId = TargetFieldId + 1,
        ActiveSubHandleFieldId = EnablePivotFieldId + 1,
        LastMousePosFieldId = ActiveSubHandleFieldId + 1,
        ViewportFieldId = LastMousePosFieldId + 1,
        ActiveFieldId = ViewportFieldId + 1,
        LengthFieldId = ActiveFieldId + 1,
        PivotFieldId = LengthFieldId + 1,
        HandleXNodeFieldId = PivotFieldId + 1,
        HandleYNodeFieldId = HandleXNodeFieldId + 1,
        HandleZNodeFieldId = HandleYNodeFieldId + 1,
        HandlePNodeFieldId = HandleZNodeFieldId + 1,
        TransXNodeFieldId = HandlePNodeFieldId + 1,
        TransYNodeFieldId = TransXNodeFieldId + 1,
        TransZNodeFieldId = TransYNodeFieldId + 1,
        PivotNodeFieldId = TransZNodeFieldId + 1,
        MaterialXFieldId = PivotNodeFieldId + 1,
        MaterialYFieldId = MaterialXFieldId + 1,
        MaterialZFieldId = MaterialYFieldId + 1,
        MaterialPivotFieldId = MaterialZFieldId + 1,
        AxisLinesNFieldId = MaterialPivotFieldId + 1,
        NextFieldId = AxisLinesNFieldId + 1
    };

    static const OSG::BitVector TargetFieldMask =
        (TypeTraits<BitVector>::One << TargetFieldId);
    static const OSG::BitVector EnablePivotFieldMask =
        (TypeTraits<BitVector>::One << EnablePivotFieldId);
    static const OSG::BitVector ActiveSubHandleFieldMask =
        (TypeTraits<BitVector>::One << ActiveSubHandleFieldId);
    static const OSG::BitVector LastMousePosFieldMask =
        (TypeTraits<BitVector>::One << LastMousePosFieldId);
    static const OSG::BitVector ViewportFieldMask =
        (TypeTraits<BitVector>::One << ViewportFieldId);
    static const OSG::BitVector ActiveFieldMask =
        (TypeTraits<BitVector>::One << ActiveFieldId);
    static const OSG::BitVector LengthFieldMask =
        (TypeTraits<BitVector>::One << LengthFieldId);
    static const OSG::BitVector PivotFieldMask =
        (TypeTraits<BitVector>::One << PivotFieldId);
    static const OSG::BitVector HandleXNodeFieldMask =
        (TypeTraits<BitVector>::One << HandleXNodeFieldId);
    static const OSG::BitVector HandleYNodeFieldMask =
        (TypeTraits<BitVector>::One << HandleYNodeFieldId);
    static const OSG::BitVector HandleZNodeFieldMask =
        (TypeTraits<BitVector>::One << HandleZNodeFieldId);
    static const OSG::BitVector HandlePNodeFieldMask =
        (TypeTraits<BitVector>::One << HandlePNodeFieldId);
    static const OSG::BitVector TransXNodeFieldMask =
        (TypeTraits<BitVector>::One << TransXNodeFieldId);
    static const OSG::BitVector TransYNodeFieldMask =
        (TypeTraits<BitVector>::One << TransYNodeFieldId);
    static const OSG::BitVector TransZNodeFieldMask =
        (TypeTraits<BitVector>::One << TransZNodeFieldId);
    static const OSG::BitVector PivotNodeFieldMask =
        (TypeTraits<BitVector>::One << PivotNodeFieldId);
    static const OSG::BitVector MaterialXFieldMask =
        (TypeTraits<BitVector>::One << MaterialXFieldId);
    static const OSG::BitVector MaterialYFieldMask =
        (TypeTraits<BitVector>::One << MaterialYFieldId);
    static const OSG::BitVector MaterialZFieldMask =
        (TypeTraits<BitVector>::One << MaterialZFieldId);
    static const OSG::BitVector MaterialPivotFieldMask =
        (TypeTraits<BitVector>::One << MaterialPivotFieldId);
    static const OSG::BitVector AxisLinesNFieldMask =
        (TypeTraits<BitVector>::One << AxisLinesNFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFUnrecNodePtr    SFTargetType;
    typedef SFBool            SFEnablePivotType;
    typedef SFUnrecNodePtr    SFActiveSubHandleType;
    typedef SFPnt2f           SFLastMousePosType;
    typedef SFUnrecViewportPtr SFViewportType;
    typedef SFBool            SFActiveType;
    typedef SFVec3f           SFLengthType;
    typedef SFPnt3f           SFPivotType;
    typedef SFUnrecNodePtr    SFHandleXNodeType;
    typedef SFUnrecNodePtr    SFHandleYNodeType;
    typedef SFUnrecNodePtr    SFHandleZNodeType;
    typedef SFUnrecNodePtr    SFHandlePNodeType;
    typedef SFUnrecNodePtr    SFTransXNodeType;
    typedef SFUnrecNodePtr    SFTransYNodeType;
    typedef SFUnrecNodePtr    SFTransZNodeType;
    typedef SFUnrecNodePtr    SFPivotNodeType;
    typedef SFUnrecMaterialPtr SFMaterialXType;
    typedef SFUnrecMaterialPtr SFMaterialYType;
    typedef SFUnrecMaterialPtr SFMaterialZType;
    typedef SFUnrecMaterialPtr SFMaterialPivotType;
    typedef SFUnrecNodePtr    SFAxisLinesNType;

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

            const SFUnrecNodePtr      *getSFTarget         (void) const;
                  SFUnrecNodePtr      *editSFTarget         (void);

                  SFBool              *editSFEnablePivot    (void);
            const SFBool              *getSFEnablePivot     (void) const;
            const SFUnrecNodePtr      *getSFActiveSubHandle(void) const;
                  SFUnrecNodePtr      *editSFActiveSubHandle(void);
            const SFUnrecViewportPtr  *getSFViewport       (void) const;
                  SFUnrecViewportPtr  *editSFViewport       (void);

                  SFBool              *editSFActive         (void);
            const SFBool              *getSFActive          (void) const;

                  SFVec3f             *editSFLength         (void);
            const SFVec3f             *getSFLength          (void) const;

                  SFPnt3f             *editSFPivot          (void);
            const SFPnt3f             *getSFPivot           (void) const;
            const SFUnrecNodePtr      *getSFHandleXNode    (void) const;
                  SFUnrecNodePtr      *editSFHandleXNode    (void);
            const SFUnrecNodePtr      *getSFHandleYNode    (void) const;
                  SFUnrecNodePtr      *editSFHandleYNode    (void);
            const SFUnrecNodePtr      *getSFHandleZNode    (void) const;
                  SFUnrecNodePtr      *editSFHandleZNode    (void);
            const SFUnrecNodePtr      *getSFHandlePNode    (void) const;
                  SFUnrecNodePtr      *editSFHandlePNode    (void);
            const SFUnrecNodePtr      *getSFTransXNode     (void) const;
                  SFUnrecNodePtr      *editSFTransXNode     (void);
            const SFUnrecNodePtr      *getSFTransYNode     (void) const;
                  SFUnrecNodePtr      *editSFTransYNode     (void);
            const SFUnrecNodePtr      *getSFTransZNode     (void) const;
                  SFUnrecNodePtr      *editSFTransZNode     (void);
            const SFUnrecNodePtr      *getSFPivotNode      (void) const;
                  SFUnrecNodePtr      *editSFPivotNode      (void);
            const SFUnrecMaterialPtr  *getSFMaterialX      (void) const;
                  SFUnrecMaterialPtr  *editSFMaterialX      (void);
            const SFUnrecMaterialPtr  *getSFMaterialY      (void) const;
                  SFUnrecMaterialPtr  *editSFMaterialY      (void);
            const SFUnrecMaterialPtr  *getSFMaterialZ      (void) const;
                  SFUnrecMaterialPtr  *editSFMaterialZ      (void);
            const SFUnrecMaterialPtr  *getSFMaterialPivot  (void) const;
                  SFUnrecMaterialPtr  *editSFMaterialPivot  (void);
            const SFUnrecNodePtr      *getSFAxisLinesN     (void) const;
                  SFUnrecNodePtr      *editSFAxisLinesN     (void);


                  Node * getTarget         (void) const;

                  bool                &editEnablePivot    (void);
                  bool                 getEnablePivot     (void) const;

                  Node * getActiveSubHandle(void) const;

                  Viewport * getViewport       (void) const;

                  bool                &editActive         (void);
                  bool                 getActive          (void) const;

                  Vec3f               &editLength         (void);
            const Vec3f               &getLength          (void) const;

                  Pnt3f               &editPivot          (void);
            const Pnt3f               &getPivot           (void) const;

                  Node * getHandleXNode    (void) const;

                  Node * getHandleYNode    (void) const;

                  Node * getHandleZNode    (void) const;

                  Node * getHandlePNode    (void) const;

                  Node * getTransXNode     (void) const;

                  Node * getTransYNode     (void) const;

                  Node * getTransZNode     (void) const;

                  Node * getPivotNode      (void) const;

                  Material * getMaterialX      (void) const;

                  Material * getMaterialY      (void) const;

                  Material * getMaterialZ      (void) const;

                  Material * getMaterialPivot  (void) const;

                  Node * getAxisLinesN     (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setTarget         (Node * const value);
            void setEnablePivot    (const bool value);
            void setActiveSubHandle(Node * const value);
            void setViewport       (Viewport * const value);
            void setActive         (const bool value);
            void setLength         (const Vec3f &value);
            void setPivot          (const Pnt3f &value);
            void setHandleXNode    (Node * const value);
            void setHandleYNode    (Node * const value);
            void setHandleZNode    (Node * const value);
            void setHandlePNode    (Node * const value);
            void setTransXNode     (Node * const value);
            void setTransYNode     (Node * const value);
            void setTransZNode     (Node * const value);
            void setPivotNode      (Node * const value);
            void setMaterialX      (Material * const value);
            void setMaterialY      (Material * const value);
            void setMaterialZ      (Material * const value);
            void setMaterialPivot  (Material * const value);
            void setAxisLinesN     (Node * const value);

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

    static       void   classDescInserter(TypeObject &oType);
    static const Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFUnrecNodePtr    _sfTarget;
    SFBool            _sfEnablePivot;
    SFUnrecNodePtr    _sfActiveSubHandle;
    SFPnt2f           _sfLastMousePos;
    SFUnrecViewportPtr _sfViewport;
    SFBool            _sfActive;
    SFVec3f           _sfLength;
    SFPnt3f           _sfPivot;
    SFUnrecNodePtr    _sfHandleXNode;
    SFUnrecNodePtr    _sfHandleYNode;
    SFUnrecNodePtr    _sfHandleZNode;
    SFUnrecNodePtr    _sfHandlePNode;
    SFUnrecNodePtr    _sfTransXNode;
    SFUnrecNodePtr    _sfTransYNode;
    SFUnrecNodePtr    _sfTransZNode;
    SFUnrecNodePtr    _sfPivotNode;
    SFUnrecMaterialPtr _sfMaterialX;
    SFUnrecMaterialPtr _sfMaterialY;
    SFUnrecMaterialPtr _sfMaterialZ;
    SFUnrecMaterialPtr _sfMaterialPivot;
    SFUnrecNodePtr    _sfAxisLinesN;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ManipulatorBase(void);
    ManipulatorBase(const ManipulatorBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ManipulatorBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const Manipulator *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleTarget          (void) const;
    EditFieldHandlePtr editHandleTarget         (void);
    GetFieldHandlePtr  getHandleEnablePivot     (void) const;
    EditFieldHandlePtr editHandleEnablePivot    (void);
    GetFieldHandlePtr  getHandleActiveSubHandle (void) const;
    EditFieldHandlePtr editHandleActiveSubHandle(void);
    GetFieldHandlePtr  getHandleLastMousePos    (void) const;
    EditFieldHandlePtr editHandleLastMousePos   (void);
    GetFieldHandlePtr  getHandleViewport        (void) const;
    EditFieldHandlePtr editHandleViewport       (void);
    GetFieldHandlePtr  getHandleActive          (void) const;
    EditFieldHandlePtr editHandleActive         (void);
    GetFieldHandlePtr  getHandleLength          (void) const;
    EditFieldHandlePtr editHandleLength         (void);
    GetFieldHandlePtr  getHandlePivot           (void) const;
    EditFieldHandlePtr editHandlePivot          (void);
    GetFieldHandlePtr  getHandleHandleXNode     (void) const;
    EditFieldHandlePtr editHandleHandleXNode    (void);
    GetFieldHandlePtr  getHandleHandleYNode     (void) const;
    EditFieldHandlePtr editHandleHandleYNode    (void);
    GetFieldHandlePtr  getHandleHandleZNode     (void) const;
    EditFieldHandlePtr editHandleHandleZNode    (void);
    GetFieldHandlePtr  getHandleHandlePNode     (void) const;
    EditFieldHandlePtr editHandleHandlePNode    (void);
    GetFieldHandlePtr  getHandleTransXNode      (void) const;
    EditFieldHandlePtr editHandleTransXNode     (void);
    GetFieldHandlePtr  getHandleTransYNode      (void) const;
    EditFieldHandlePtr editHandleTransYNode     (void);
    GetFieldHandlePtr  getHandleTransZNode      (void) const;
    EditFieldHandlePtr editHandleTransZNode     (void);
    GetFieldHandlePtr  getHandlePivotNode       (void) const;
    EditFieldHandlePtr editHandlePivotNode      (void);
    GetFieldHandlePtr  getHandleMaterialX       (void) const;
    EditFieldHandlePtr editHandleMaterialX      (void);
    GetFieldHandlePtr  getHandleMaterialY       (void) const;
    EditFieldHandlePtr editHandleMaterialY      (void);
    GetFieldHandlePtr  getHandleMaterialZ       (void) const;
    EditFieldHandlePtr editHandleMaterialZ      (void);
    GetFieldHandlePtr  getHandleMaterialPivot   (void) const;
    EditFieldHandlePtr editHandleMaterialPivot  (void);
    GetFieldHandlePtr  getHandleAxisLinesN      (void) const;
    EditFieldHandlePtr editHandleAxisLinesN     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


                  SFPnt2f             *editSFLastMousePos   (void);
            const SFPnt2f             *getSFLastMousePos    (void) const;


                  Pnt2f               &editLastMousePos   (void);
            const Pnt2f               &getLastMousePos    (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setLastMousePos   (const Pnt2f &value);

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

            void execSync (      ManipulatorBase *pFrom,
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
    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ManipulatorBase &source);
};

typedef ManipulatorBase *ManipulatorBaseP;

OSG_END_NAMESPACE

#endif /* _OSGMANIPULATORBASE_H_ */
