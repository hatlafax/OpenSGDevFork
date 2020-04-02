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

#ifndef _OSGMATERIALDESC_H_
#define _OSGMATERIALDESC_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBinaryDataHandler.h"
#include "OSGMaterialDescBase.h"

OSG_BEGIN_NAMESPACE

class Hash64;
class TextureDesc;
class Image;

/*! \brief MaterialDesc class. See \ref
           PageSystemMaterialDesc for a description.
*/

class OSG_SYSTEM_DLLMAPPING MaterialDesc : public MaterialDescBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MaterialDescBase Inherited;
    typedef MaterialDesc     Self;

    typedef UInt64           HashKeyType;

    /*---------------------------------------------------------------------*/
    /*! \name                  Shading Model                               */
    /*! \{                                                                 */

    enum ShadingModel
    {
        NO_SHADING_MODEL =  0,
        GOURAUD_SHADING_MODEL,
        PHONG_SHADING_MODEL,
        BLINN_PHONG_SHADING_MODEL,
        COOK_TORRANCE_SHADING_MODEL,
        OREN_NAYAR_SHADING_MODEL,
        TOON_SHADING_MODEL,
        GOOCH_SHADING_MODEL,
    };

    enum BlendMode
    {
        DEFAULT_BLEND_MODE = 0,
        ADDITIVE_BLEND_MODE,
        MULTIPLICATIVE_BLEND_MODE,
        INTERPOLATION_BLEND_MODE
    };

    enum OpacityMode
    {
        NO_OPACITY_MODE = 0,
        OPAQUE_OPACITY_MODE,
        MASK_OPACITY_MODE,
        BLEND_OPACITY_MODE
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  State Flags                                 */
    /*! \{                                                                 */

    enum StateFlags
    {
        SRGB_COLOR_MODE                  = 0x00000001,  // All color information is expected to be in SRGB space (usually fine)
        SHADOW_ONLY_MODE                 = 0x00000002,  // The material is invisible expect from shadowed regions
        PBR_SPECULAR_MODE                = 0x00000004,  // The Cook-Torrance shading model uses the specular/gloss workflow instead of the metalness/roughness workflow
        UNLIT_MODE                       = 0x00000008,  // The material does not participate in any lighting calculations
        PBR_CLEAR_COAT_MODE              = 0x00000010,  // The PBR material should evaluate clear coat information.
        PBR_SHEEN_COLOR_MODE             = 0x00000020,  // The PBR material should evaluate sheen color information.
        PBR_ANISOTROPY_MODE              = 0x00000040,  // The PBR material should evaluate anisotropy information.
        HAS_NORMALS_MODE                 = 0x00001000,
        HAS_TANGENTS_AND_BITANGENTS_MODE = 0x00002000,
        FLAT_SHADING_MODE                = 0x00004000,  // Normals are not interpolated
        OFFSET_POINT_MODE                = 0x00008000,
        OFFSET_LINE_MODE                 = 0x00010000,
        OFFSET_FILL_MODE                 = 0x00020000,
        XOR_MODE                         = 0x00040000,
        NO_DEPTH_TEST_MODE               = 0x00080000,
    };

    bool        getSRGBColorMode                () const;
    bool        getShadowOnlyMode               () const;
    bool        getPbrSpecularMode              () const;
    bool        getPbrClearCoatMode             () const;
    bool        getPbrSheenColorMode            () const;
    bool        getPbrAnisotropyMode            () const;
    bool        getUnlitMode                    () const;
    bool        getHasNormalsMode               () const;
    bool        getHasTangentsAndBitangentsMode () const;
    bool        getFlatShadingMode              () const;
    bool        getOffsetPointMode              () const;
    bool        getOffsetLineMode               () const;
    bool        getOffsetFillMode               () const;
    bool        getXORMode                      () const;
    bool        getNoDepthTestMode              () const;

    void        setSRGBColorMode                (bool flag);
    void        setShadowOnlyMode               (bool flag);
    void        setPbrSpecularMode              (bool flag);
    void        setPbrClearCoatMode             (bool  flag);
    void        setPbrSheenColorMode            (bool  flag);
    void        setPbrAnisotropyMode            (bool  flag);
    void        setUnlitMode                    (bool flag);
    void        setHasNormalsMode               (bool flag);
    void        setHasTangentsAndBitangentsMode (bool flag);
    void        setFlatShadingMode              (bool flag);
    void        setOffsetPointMode              (bool flag);
    void        setOffsetLineMode               (bool flag);
    void        setOffsetFillMode               (bool flag);
    void        setXORMode                      (bool flag);
    void        setNoDepthTestMode              (bool flag);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Convenience                                 */
    /*! \{                                                                 */

    void        addTexture          (TextureDesc* texDesc);

    Real32      getRefractiveIndex  () const;
    void        setRefractiveIndex  (Real32 value);

    Real32      getShininess        () const;
    void        setShininess        (Real32 value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Hash                                    */
    /*! \{                                                                 */

    HashKeyType             getHashValue();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MaterialDescBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    class BinaryWriteHandler : public BinaryDataHandler
    {
      public:
        BinaryWriteHandler(Hash64& hasher);

        virtual ~BinaryWriteHandler(void);

      protected:
        virtual void write(MemoryHandle mem, UInt32 size);

      private:
        std::vector<UInt8>  _writeMemory;
        Hash64&             _hasher;

        BinaryWriteHandler(const BinaryWriteHandler &source);
        void operator =   (const BinaryWriteHandler &source);
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MaterialDesc(void);
    MaterialDesc(const MaterialDesc &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MaterialDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    void calcHash(Image*          fc, BinaryWriteHandler& wh) const;
    void calcHash(FieldContainer* fc, BinaryWriteHandler& wh, BitVector excludeMask) const;

    friend class FieldContainer;
    friend class MaterialDescBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MaterialDesc &source);
};

typedef MaterialDesc *MaterialDescP;

OSG_END_NAMESPACE

#include "OSGMaterialDescBase.inl"
#include "OSGMaterialDesc.inl"

#endif /* _OSGMATERIALDESC_H_ */
