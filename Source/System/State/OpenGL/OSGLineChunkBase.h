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
 **     class LineChunk
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGLINECHUNKBASE_H_
#define _OSGLINECHUNKBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGStateDef.h"

#include "OSGBaseTypes.h"

#include "OSGStateChunk.h" // Parent

#include "OSGReal32Fields.h" // Width type
#include "OSGInt32Fields.h" // StippleRepeat type
#include "OSGUInt16Fields.h" // StipplePattern type
#include "OSGBoolFields.h" // Smooth type

#include "OSGLineChunkFields.h"

OSG_BEGIN_NAMESPACE

class LineChunk;

//! \brief LineChunk Base Class.

class OSG_STATE_DLLMAPPING LineChunkBase : public StateChunk
{
  public:

    typedef StateChunk Inherited;
    typedef StateChunk ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(LineChunk);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        WidthFieldId = Inherited::NextFieldId,
        StippleRepeatFieldId = WidthFieldId + 1,
        StipplePatternFieldId = StippleRepeatFieldId + 1,
        SmoothFieldId = StipplePatternFieldId + 1,
        NextFieldId = SmoothFieldId + 1
    };

    static const OSG::BitVector WidthFieldMask =
        (TypeTraits<BitVector>::One << WidthFieldId);
    static const OSG::BitVector StippleRepeatFieldMask =
        (TypeTraits<BitVector>::One << StippleRepeatFieldId);
    static const OSG::BitVector StipplePatternFieldMask =
        (TypeTraits<BitVector>::One << StipplePatternFieldId);
    static const OSG::BitVector SmoothFieldMask =
        (TypeTraits<BitVector>::One << SmoothFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFReal32          SFWidthType;
    typedef SFInt32           SFStippleRepeatType;
    typedef SFUInt16          SFStipplePatternType;
    typedef SFBool            SFSmoothType;

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


                  SFReal32            *editSFWidth          (void);
            const SFReal32            *getSFWidth           (void) const;

                  SFInt32             *editSFStippleRepeat  (void);
            const SFInt32             *getSFStippleRepeat   (void) const;

                  SFUInt16            *editSFStipplePattern (void);
            const SFUInt16            *getSFStipplePattern  (void) const;

                  SFBool              *editSFSmooth         (void);
            const SFBool              *getSFSmooth          (void) const;


                  Real32              &editWidth          (void);
                  Real32               getWidth           (void) const;

                  Int32               &editStippleRepeat  (void);
                  Int32                getStippleRepeat   (void) const;

                  UInt16              &editStipplePattern (void);
                  UInt16               getStipplePattern  (void) const;

                  bool                &editSmooth         (void);
                  bool                 getSmooth          (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setWidth          (const Real32 value);
            void setStippleRepeat  (const Int32 value);
            void setStipplePattern (const UInt16 value);
            void setSmooth         (const bool value);

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

    static  LineChunkTransitPtr  create          (void);
    static  LineChunk           *createEmpty     (void);

    static  LineChunkTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  LineChunk            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  LineChunkTransitPtr  createDependent  (BitVector bFlags);

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

    SFReal32          _sfWidth;
    SFInt32           _sfStippleRepeat;
    SFUInt16          _sfStipplePattern;
    SFBool            _sfSmooth;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LineChunkBase(void);
    LineChunkBase(const LineChunkBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LineChunkBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleWidth           (void) const;
    EditFieldHandlePtr editHandleWidth          (void);
    GetFieldHandlePtr  getHandleStippleRepeat   (void) const;
    EditFieldHandlePtr editHandleStippleRepeat  (void);
    GetFieldHandlePtr  getHandleStipplePattern  (void) const;
    EditFieldHandlePtr editHandleStipplePattern (void);
    GetFieldHandlePtr  getHandleSmooth          (void) const;
    EditFieldHandlePtr editHandleSmooth         (void);

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

            void execSync (      LineChunkBase *pFrom,
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
    void operator =(const LineChunkBase &source);
};

typedef LineChunkBase *LineChunkBaseP;

OSG_END_NAMESPACE

#endif /* _OSGLINECHUNKBASE_H_ */
