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
 **     class TextureChunk
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGTEXTURECHUNKBASE_H_
#define _OSGTEXTURECHUNKBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGSystemDef.h"

//#include "OSGBaseTypes.h"

#include "OSGTextureObjChunk.h" // Parent

#include "OSGBaseFields.h"              // EnvMode type
#include "OSGSysFields.h"               // EnvScaleRGB type
#include "OSGVecFields.h"               // ShaderConstEye type

#include "OSGTextureChunkFields.h"

OSG_BEGIN_NAMESPACE


class TextureChunk;

//! \brief TextureChunk Base Class.

class OSG_SYSTEM_DLLMAPPING TextureChunkBase : public TextureObjChunk
{
  public:

    typedef TextureObjChunk Inherited;
    typedef TextureObjChunk ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(TextureChunk);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        EnvModeFieldId = Inherited::NextFieldId,
        EnvColorFieldId = EnvModeFieldId + 1,
        EnvCombineRGBFieldId = EnvColorFieldId + 1,
        EnvCombineAlphaFieldId = EnvCombineRGBFieldId + 1,
        EnvScaleRGBFieldId = EnvCombineAlphaFieldId + 1,
        EnvScaleAlphaFieldId = EnvScaleRGBFieldId + 1,
        EnvSource0RGBFieldId = EnvScaleAlphaFieldId + 1,
        EnvSource1RGBFieldId = EnvSource0RGBFieldId + 1,
        EnvSource2RGBFieldId = EnvSource1RGBFieldId + 1,
        EnvSource0AlphaFieldId = EnvSource2RGBFieldId + 1,
        EnvSource1AlphaFieldId = EnvSource0AlphaFieldId + 1,
        EnvSource2AlphaFieldId = EnvSource1AlphaFieldId + 1,
        EnvOperand0RGBFieldId = EnvSource2AlphaFieldId + 1,
        EnvOperand1RGBFieldId = EnvOperand0RGBFieldId + 1,
        EnvOperand2RGBFieldId = EnvOperand1RGBFieldId + 1,
        EnvOperand0AlphaFieldId = EnvOperand2RGBFieldId + 1,
        EnvOperand1AlphaFieldId = EnvOperand0AlphaFieldId + 1,
        EnvOperand2AlphaFieldId = EnvOperand1AlphaFieldId + 1,
        PointSpriteFieldId = EnvOperand2AlphaFieldId + 1,
        ShaderOperationFieldId = PointSpriteFieldId + 1,
        ShaderInputFieldId = ShaderOperationFieldId + 1,
        ShaderOffsetMatrixFieldId = ShaderInputFieldId + 1,
        ShaderOffsetScaleFieldId = ShaderOffsetMatrixFieldId + 1,
        ShaderOffsetBiasFieldId = ShaderOffsetScaleFieldId + 1,
        ShaderRGBADotProductFieldId = ShaderOffsetBiasFieldId + 1,
        ShaderCullModesFieldId = ShaderRGBADotProductFieldId + 1,
        ShaderConstEyeFieldId = ShaderCullModesFieldId + 1,
        LodBiasFieldId = ShaderConstEyeFieldId + 1,
        NPOTMatrixScaleFieldId = LodBiasFieldId + 1,
        NextFieldId = NPOTMatrixScaleFieldId + 1
    };

    static const OSG::BitVector EnvModeFieldMask =
        (TypeTraits<BitVector>::One << EnvModeFieldId);
    static const OSG::BitVector EnvColorFieldMask =
        (TypeTraits<BitVector>::One << EnvColorFieldId);
    static const OSG::BitVector EnvCombineRGBFieldMask =
        (TypeTraits<BitVector>::One << EnvCombineRGBFieldId);
    static const OSG::BitVector EnvCombineAlphaFieldMask =
        (TypeTraits<BitVector>::One << EnvCombineAlphaFieldId);
    static const OSG::BitVector EnvScaleRGBFieldMask =
        (TypeTraits<BitVector>::One << EnvScaleRGBFieldId);
    static const OSG::BitVector EnvScaleAlphaFieldMask =
        (TypeTraits<BitVector>::One << EnvScaleAlphaFieldId);
    static const OSG::BitVector EnvSource0RGBFieldMask =
        (TypeTraits<BitVector>::One << EnvSource0RGBFieldId);
    static const OSG::BitVector EnvSource1RGBFieldMask =
        (TypeTraits<BitVector>::One << EnvSource1RGBFieldId);
    static const OSG::BitVector EnvSource2RGBFieldMask =
        (TypeTraits<BitVector>::One << EnvSource2RGBFieldId);
    static const OSG::BitVector EnvSource0AlphaFieldMask =
        (TypeTraits<BitVector>::One << EnvSource0AlphaFieldId);
    static const OSG::BitVector EnvSource1AlphaFieldMask =
        (TypeTraits<BitVector>::One << EnvSource1AlphaFieldId);
    static const OSG::BitVector EnvSource2AlphaFieldMask =
        (TypeTraits<BitVector>::One << EnvSource2AlphaFieldId);
    static const OSG::BitVector EnvOperand0RGBFieldMask =
        (TypeTraits<BitVector>::One << EnvOperand0RGBFieldId);
    static const OSG::BitVector EnvOperand1RGBFieldMask =
        (TypeTraits<BitVector>::One << EnvOperand1RGBFieldId);
    static const OSG::BitVector EnvOperand2RGBFieldMask =
        (TypeTraits<BitVector>::One << EnvOperand2RGBFieldId);
    static const OSG::BitVector EnvOperand0AlphaFieldMask =
        (TypeTraits<BitVector>::One << EnvOperand0AlphaFieldId);
    static const OSG::BitVector EnvOperand1AlphaFieldMask =
        (TypeTraits<BitVector>::One << EnvOperand1AlphaFieldId);
    static const OSG::BitVector EnvOperand2AlphaFieldMask =
        (TypeTraits<BitVector>::One << EnvOperand2AlphaFieldId);
    static const OSG::BitVector PointSpriteFieldMask =
        (TypeTraits<BitVector>::One << PointSpriteFieldId);
    static const OSG::BitVector ShaderOperationFieldMask =
        (TypeTraits<BitVector>::One << ShaderOperationFieldId);
    static const OSG::BitVector ShaderInputFieldMask =
        (TypeTraits<BitVector>::One << ShaderInputFieldId);
    static const OSG::BitVector ShaderOffsetMatrixFieldMask =
        (TypeTraits<BitVector>::One << ShaderOffsetMatrixFieldId);
    static const OSG::BitVector ShaderOffsetScaleFieldMask =
        (TypeTraits<BitVector>::One << ShaderOffsetScaleFieldId);
    static const OSG::BitVector ShaderOffsetBiasFieldMask =
        (TypeTraits<BitVector>::One << ShaderOffsetBiasFieldId);
    static const OSG::BitVector ShaderRGBADotProductFieldMask =
        (TypeTraits<BitVector>::One << ShaderRGBADotProductFieldId);
    static const OSG::BitVector ShaderCullModesFieldMask =
        (TypeTraits<BitVector>::One << ShaderCullModesFieldId);
    static const OSG::BitVector ShaderConstEyeFieldMask =
        (TypeTraits<BitVector>::One << ShaderConstEyeFieldId);
    static const OSG::BitVector LodBiasFieldMask =
        (TypeTraits<BitVector>::One << LodBiasFieldId);
    static const OSG::BitVector NPOTMatrixScaleFieldMask =
        (TypeTraits<BitVector>::One << NPOTMatrixScaleFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFGLenum          SFEnvModeType;
    typedef SFColor4f         SFEnvColorType;
    typedef SFGLenum          SFEnvCombineRGBType;
    typedef SFGLenum          SFEnvCombineAlphaType;
    typedef SFReal32          SFEnvScaleRGBType;
    typedef SFReal32          SFEnvScaleAlphaType;
    typedef SFGLenum          SFEnvSource0RGBType;
    typedef SFGLenum          SFEnvSource1RGBType;
    typedef SFGLenum          SFEnvSource2RGBType;
    typedef SFGLenum          SFEnvSource0AlphaType;
    typedef SFGLenum          SFEnvSource1AlphaType;
    typedef SFGLenum          SFEnvSource2AlphaType;
    typedef SFGLenum          SFEnvOperand0RGBType;
    typedef SFGLenum          SFEnvOperand1RGBType;
    typedef SFGLenum          SFEnvOperand2RGBType;
    typedef SFGLenum          SFEnvOperand0AlphaType;
    typedef SFGLenum          SFEnvOperand1AlphaType;
    typedef SFGLenum          SFEnvOperand2AlphaType;
    typedef SFBool            SFPointSpriteType;
    typedef SFGLenum          SFShaderOperationType;
    typedef SFGLenum          SFShaderInputType;
    typedef MFReal32          MFShaderOffsetMatrixType;
    typedef SFReal32          SFShaderOffsetScaleType;
    typedef SFReal32          SFShaderOffsetBiasType;
    typedef SFGLenum          SFShaderRGBADotProductType;
    typedef SFUInt8           SFShaderCullModesType;
    typedef SFVec3f           SFShaderConstEyeType;
    typedef SFReal32          SFLodBiasType;
    typedef SFUInt32          SFNPOTMatrixScaleType;

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


                  SFGLenum            *editSFEnvMode        (void);
            const SFGLenum            *getSFEnvMode         (void) const;

                  SFColor4f           *editSFEnvColor       (void);
            const SFColor4f           *getSFEnvColor        (void) const;

                  SFGLenum            *editSFEnvCombineRGB  (void);
            const SFGLenum            *getSFEnvCombineRGB   (void) const;

                  SFGLenum            *editSFEnvCombineAlpha(void);
            const SFGLenum            *getSFEnvCombineAlpha (void) const;

                  SFReal32            *editSFEnvScaleRGB    (void);
            const SFReal32            *getSFEnvScaleRGB     (void) const;

                  SFReal32            *editSFEnvScaleAlpha  (void);
            const SFReal32            *getSFEnvScaleAlpha   (void) const;

                  SFGLenum            *editSFEnvSource0RGB  (void);
            const SFGLenum            *getSFEnvSource0RGB   (void) const;

                  SFGLenum            *editSFEnvSource1RGB  (void);
            const SFGLenum            *getSFEnvSource1RGB   (void) const;

                  SFGLenum            *editSFEnvSource2RGB  (void);
            const SFGLenum            *getSFEnvSource2RGB   (void) const;

                  SFGLenum            *editSFEnvSource0Alpha(void);
            const SFGLenum            *getSFEnvSource0Alpha (void) const;

                  SFGLenum            *editSFEnvSource1Alpha(void);
            const SFGLenum            *getSFEnvSource1Alpha (void) const;

                  SFGLenum            *editSFEnvSource2Alpha(void);
            const SFGLenum            *getSFEnvSource2Alpha (void) const;

                  SFGLenum            *editSFEnvOperand0RGB (void);
            const SFGLenum            *getSFEnvOperand0RGB  (void) const;

                  SFGLenum            *editSFEnvOperand1RGB (void);
            const SFGLenum            *getSFEnvOperand1RGB  (void) const;

                  SFGLenum            *editSFEnvOperand2RGB (void);
            const SFGLenum            *getSFEnvOperand2RGB  (void) const;

                  SFGLenum            *editSFEnvOperand0Alpha(void);
            const SFGLenum            *getSFEnvOperand0Alpha (void) const;

                  SFGLenum            *editSFEnvOperand1Alpha(void);
            const SFGLenum            *getSFEnvOperand1Alpha (void) const;

                  SFGLenum            *editSFEnvOperand2Alpha(void);
            const SFGLenum            *getSFEnvOperand2Alpha (void) const;

                  SFBool              *editSFPointSprite    (void);
            const SFBool              *getSFPointSprite     (void) const;

                  SFGLenum            *editSFShaderOperation(void);
            const SFGLenum            *getSFShaderOperation (void) const;

                  SFGLenum            *editSFShaderInput    (void);
            const SFGLenum            *getSFShaderInput     (void) const;

                  MFReal32            *editMFShaderOffsetMatrix(void);
            const MFReal32            *getMFShaderOffsetMatrix (void) const;

                  SFReal32            *editSFShaderOffsetScale(void);
            const SFReal32            *getSFShaderOffsetScale (void) const;

                  SFReal32            *editSFShaderOffsetBias(void);
            const SFReal32            *getSFShaderOffsetBias (void) const;

                  SFGLenum            *editSFShaderRGBADotProduct(void);
            const SFGLenum            *getSFShaderRGBADotProduct (void) const;

                  SFUInt8             *editSFShaderCullModes(void);
            const SFUInt8             *getSFShaderCullModes (void) const;

                  SFVec3f             *editSFShaderConstEye (void);
            const SFVec3f             *getSFShaderConstEye  (void) const;

                  SFReal32            *editSFLodBias        (void);
            const SFReal32            *getSFLodBias         (void) const;

                  SFUInt32            *editSFNPOTMatrixScale(void);
            const SFUInt32            *getSFNPOTMatrixScale (void) const;


                  GLenum              &editEnvMode        (void);
            const GLenum              &getEnvMode         (void) const;

                  Color4f             &editEnvColor       (void);
            const Color4f             &getEnvColor        (void) const;

                  GLenum              &editEnvCombineRGB  (void);
            const GLenum              &getEnvCombineRGB   (void) const;

                  GLenum              &editEnvCombineAlpha(void);
            const GLenum              &getEnvCombineAlpha (void) const;

                  Real32              &editEnvScaleRGB    (void);
                  Real32               getEnvScaleRGB     (void) const;

                  Real32              &editEnvScaleAlpha  (void);
                  Real32               getEnvScaleAlpha   (void) const;

                  GLenum              &editEnvSource0RGB  (void);
            const GLenum              &getEnvSource0RGB   (void) const;

                  GLenum              &editEnvSource1RGB  (void);
            const GLenum              &getEnvSource1RGB   (void) const;

                  GLenum              &editEnvSource2RGB  (void);
            const GLenum              &getEnvSource2RGB   (void) const;

                  GLenum              &editEnvSource0Alpha(void);
            const GLenum              &getEnvSource0Alpha (void) const;

                  GLenum              &editEnvSource1Alpha(void);
            const GLenum              &getEnvSource1Alpha (void) const;

                  GLenum              &editEnvSource2Alpha(void);
            const GLenum              &getEnvSource2Alpha (void) const;

                  GLenum              &editEnvOperand0RGB (void);
            const GLenum              &getEnvOperand0RGB  (void) const;

                  GLenum              &editEnvOperand1RGB (void);
            const GLenum              &getEnvOperand1RGB  (void) const;

                  GLenum              &editEnvOperand2RGB (void);
            const GLenum              &getEnvOperand2RGB  (void) const;

                  GLenum              &editEnvOperand0Alpha(void);
            const GLenum              &getEnvOperand0Alpha (void) const;

                  GLenum              &editEnvOperand1Alpha(void);
            const GLenum              &getEnvOperand1Alpha (void) const;

                  GLenum              &editEnvOperand2Alpha(void);
            const GLenum              &getEnvOperand2Alpha (void) const;

                  bool                &editPointSprite    (void);
                  bool                 getPointSprite     (void) const;

                  GLenum              &editShaderOperation(void);
            const GLenum              &getShaderOperation (void) const;

                  GLenum              &editShaderInput    (void);
            const GLenum              &getShaderInput     (void) const;

                  Real32              &editShaderOffsetMatrix(const UInt32 index);
                  Real32               getShaderOffsetMatrix (const UInt32 index) const;

                  Real32              &editShaderOffsetScale(void);
                  Real32               getShaderOffsetScale (void) const;

                  Real32              &editShaderOffsetBias(void);
                  Real32               getShaderOffsetBias (void) const;

                  GLenum              &editShaderRGBADotProduct(void);
            const GLenum              &getShaderRGBADotProduct (void) const;

                  UInt8               &editShaderCullModes(void);
                  UInt8                getShaderCullModes (void) const;

                  Vec3f               &editShaderConstEye (void);
            const Vec3f               &getShaderConstEye  (void) const;

                  Real32              &editLodBias        (void);
                  Real32               getLodBias         (void) const;

                  UInt32              &editNPOTMatrixScale(void);
                  UInt32               getNPOTMatrixScale (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setEnvMode        (const GLenum &value);
            void setEnvColor       (const Color4f &value);
            void setEnvCombineRGB  (const GLenum &value);
            void setEnvCombineAlpha(const GLenum &value);
            void setEnvScaleRGB    (const Real32 value);
            void setEnvScaleAlpha  (const Real32 value);
            void setEnvSource0RGB  (const GLenum &value);
            void setEnvSource1RGB  (const GLenum &value);
            void setEnvSource2RGB  (const GLenum &value);
            void setEnvSource0Alpha(const GLenum &value);
            void setEnvSource1Alpha(const GLenum &value);
            void setEnvSource2Alpha(const GLenum &value);
            void setEnvOperand0RGB (const GLenum &value);
            void setEnvOperand1RGB (const GLenum &value);
            void setEnvOperand2RGB (const GLenum &value);
            void setEnvOperand0Alpha(const GLenum &value);
            void setEnvOperand1Alpha(const GLenum &value);
            void setEnvOperand2Alpha(const GLenum &value);
            void setPointSprite    (const bool value);
            void setShaderOperation(const GLenum &value);
            void setShaderInput    (const GLenum &value);
            void setShaderOffsetScale(const Real32 value);
            void setShaderOffsetBias(const Real32 value);
            void setShaderRGBADotProduct(const GLenum &value);
            void setShaderCullModes(const UInt8 value);
            void setShaderConstEye (const Vec3f &value);
            void setLodBias        (const Real32 value);
            void setNPOTMatrixScale(const UInt32 value);

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

    static  TextureChunkTransitPtr  create          (void);
    static  TextureChunk           *createEmpty     (void);

    static  TextureChunkTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  TextureChunk            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  TextureChunkTransitPtr  createDependent  (BitVector bFlags);

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

    SFGLenum          _sfEnvMode;
    SFColor4f         _sfEnvColor;
    SFGLenum          _sfEnvCombineRGB;
    SFGLenum          _sfEnvCombineAlpha;
    SFReal32          _sfEnvScaleRGB;
    SFReal32          _sfEnvScaleAlpha;
    SFGLenum          _sfEnvSource0RGB;
    SFGLenum          _sfEnvSource1RGB;
    SFGLenum          _sfEnvSource2RGB;
    SFGLenum          _sfEnvSource0Alpha;
    SFGLenum          _sfEnvSource1Alpha;
    SFGLenum          _sfEnvSource2Alpha;
    SFGLenum          _sfEnvOperand0RGB;
    SFGLenum          _sfEnvOperand1RGB;
    SFGLenum          _sfEnvOperand2RGB;
    SFGLenum          _sfEnvOperand0Alpha;
    SFGLenum          _sfEnvOperand1Alpha;
    SFGLenum          _sfEnvOperand2Alpha;
    SFBool            _sfPointSprite;
    SFGLenum          _sfShaderOperation;
    SFGLenum          _sfShaderInput;
    MFReal32          _mfShaderOffsetMatrix;
    SFReal32          _sfShaderOffsetScale;
    SFReal32          _sfShaderOffsetBias;
    SFGLenum          _sfShaderRGBADotProduct;
    SFUInt8           _sfShaderCullModes;
    SFVec3f           _sfShaderConstEye;
    SFReal32          _sfLodBias;
    SFUInt32          _sfNPOTMatrixScale;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TextureChunkBase(void);
    TextureChunkBase(const TextureChunkBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureChunkBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleEnvMode         (void) const;
    EditFieldHandlePtr editHandleEnvMode        (void);
    GetFieldHandlePtr  getHandleEnvColor        (void) const;
    EditFieldHandlePtr editHandleEnvColor       (void);
    GetFieldHandlePtr  getHandleEnvCombineRGB   (void) const;
    EditFieldHandlePtr editHandleEnvCombineRGB  (void);
    GetFieldHandlePtr  getHandleEnvCombineAlpha (void) const;
    EditFieldHandlePtr editHandleEnvCombineAlpha(void);
    GetFieldHandlePtr  getHandleEnvScaleRGB     (void) const;
    EditFieldHandlePtr editHandleEnvScaleRGB    (void);
    GetFieldHandlePtr  getHandleEnvScaleAlpha   (void) const;
    EditFieldHandlePtr editHandleEnvScaleAlpha  (void);
    GetFieldHandlePtr  getHandleEnvSource0RGB   (void) const;
    EditFieldHandlePtr editHandleEnvSource0RGB  (void);
    GetFieldHandlePtr  getHandleEnvSource1RGB   (void) const;
    EditFieldHandlePtr editHandleEnvSource1RGB  (void);
    GetFieldHandlePtr  getHandleEnvSource2RGB   (void) const;
    EditFieldHandlePtr editHandleEnvSource2RGB  (void);
    GetFieldHandlePtr  getHandleEnvSource0Alpha (void) const;
    EditFieldHandlePtr editHandleEnvSource0Alpha(void);
    GetFieldHandlePtr  getHandleEnvSource1Alpha (void) const;
    EditFieldHandlePtr editHandleEnvSource1Alpha(void);
    GetFieldHandlePtr  getHandleEnvSource2Alpha (void) const;
    EditFieldHandlePtr editHandleEnvSource2Alpha(void);
    GetFieldHandlePtr  getHandleEnvOperand0RGB  (void) const;
    EditFieldHandlePtr editHandleEnvOperand0RGB (void);
    GetFieldHandlePtr  getHandleEnvOperand1RGB  (void) const;
    EditFieldHandlePtr editHandleEnvOperand1RGB (void);
    GetFieldHandlePtr  getHandleEnvOperand2RGB  (void) const;
    EditFieldHandlePtr editHandleEnvOperand2RGB (void);
    GetFieldHandlePtr  getHandleEnvOperand0Alpha (void) const;
    EditFieldHandlePtr editHandleEnvOperand0Alpha(void);
    GetFieldHandlePtr  getHandleEnvOperand1Alpha (void) const;
    EditFieldHandlePtr editHandleEnvOperand1Alpha(void);
    GetFieldHandlePtr  getHandleEnvOperand2Alpha (void) const;
    EditFieldHandlePtr editHandleEnvOperand2Alpha(void);
    GetFieldHandlePtr  getHandlePointSprite     (void) const;
    EditFieldHandlePtr editHandlePointSprite    (void);
    GetFieldHandlePtr  getHandleShaderOperation (void) const;
    EditFieldHandlePtr editHandleShaderOperation(void);
    GetFieldHandlePtr  getHandleShaderInput     (void) const;
    EditFieldHandlePtr editHandleShaderInput    (void);
    GetFieldHandlePtr  getHandleShaderOffsetMatrix (void) const;
    EditFieldHandlePtr editHandleShaderOffsetMatrix(void);
    GetFieldHandlePtr  getHandleShaderOffsetScale (void) const;
    EditFieldHandlePtr editHandleShaderOffsetScale(void);
    GetFieldHandlePtr  getHandleShaderOffsetBias (void) const;
    EditFieldHandlePtr editHandleShaderOffsetBias(void);
    GetFieldHandlePtr  getHandleShaderRGBADotProduct (void) const;
    EditFieldHandlePtr editHandleShaderRGBADotProduct(void);
    GetFieldHandlePtr  getHandleShaderCullModes (void) const;
    EditFieldHandlePtr editHandleShaderCullModes(void);
    GetFieldHandlePtr  getHandleShaderConstEye  (void) const;
    EditFieldHandlePtr editHandleShaderConstEye (void);
    GetFieldHandlePtr  getHandleLodBias         (void) const;
    EditFieldHandlePtr editHandleLodBias        (void);
    GetFieldHandlePtr  getHandleNPOTMatrixScale (void) const;
    EditFieldHandlePtr editHandleNPOTMatrixScale(void);

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

            void execSync (      TextureChunkBase *pFrom,
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
    void operator =(const TextureChunkBase &source);
};

typedef TextureChunkBase *TextureChunkBaseP;

OSG_END_NAMESPACE

#endif /* _OSGTEXTURECHUNKBASE_H_ */
