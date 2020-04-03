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

#ifndef _OSGTEXTUREDESC_H_
#define _OSGTEXTUREDESC_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/array.hpp>

#include "OSGTextureDescBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextureDesc class. See \ref
           PageSystemTextureDesc for a description.
*/

class OSG_SYSTEM_DLLMAPPING TextureDesc : public TextureDescBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TextureDescBase Inherited;
    typedef TextureDesc     Self;

    typedef boost::array<UInt8, 4>    SwizzleIndicesT;

    /*---------------------------------------------------------------------*/
    /*! \name                   Enumerations                               */
    /*! \{                                                                 */

    enum TextureType
    {
        NONE_TEXTURE = 0,
        UNKNOWN_TEXTURE,
        ALBEDO_TEXTURE,
        SPECULAR_TEXTURE,
        EMISSIVE_TEXTURE,
        SHININESS_TEXTURE,
        OPACITY_TEXTURE,
        NORMALS_TEXTURE,
        HEIGHT_TEXTURE,
        DISPLACEMENT_TEXTURE,
        REFLECTION_TEXTURE,
        REFRACTION_TEXTURE,
        ANISOTROPY_U_TEXTURE,
        ANISOTROPY_V_TEXTURE,
        ANISOTROPY_UV_TEXTURE,
        AMBIENT_OCCLUSION_TEXTURE,
        ROUGH_TEXTURE,
        METAL_TEXTURE,
        ROUGH_METAL_TEXTURE,
        OCCL_ROUGH_METAL_TEXTURE,
        IRRADIANCE_TEXTURE,
        PRE_FILTER_TEXTURE,
        BRDF_LUT_TEXTURE,
        STANDARD_MATERIAL_TEXTURE,
        MAX_NUM_TEXTURE_TYPES
    };

    enum MappingMode
    {
        UV_MAPPING = 0,
        SPHERE_MAPPING,
        CYLINDER_MAPPING,
        BOX_MAPPING,
        PLANE_MAPPING,
        OTHER_MAPPING,
    };

    enum EnvironmentMapType
    {
        OTHER_MAP = 0,
        EQUIRECTANGULAR_MAP,
        CUBE_MAP,
        VERTICAL_CROSS_CUBE_MAP, 
        HORIZONTAL_CROSS_CUBE_MAP,
        VERTICAL_STRIP_CUBE_MAP,
        HORIZONTAL_STRIP_CUBE_MAP
    };

    enum TextureOperation
    {
        MULTIPLY_OPERATION = 0,
        ADD_OPERATION,
        SUBTRACT_OPERATION,
        DIVIDE_OPERATION,
        SMOOTHADD_OPERATION,
        SIGNEDADD_OPERATION,
        REPLACE_OPERATION,
        DECAL_OPERATION,
        BLEND_OPERATION
    };

    enum TextureFlags
    {
        EMPTY_FLAG          = 0x00,
        INVERT_FLAG         = 0x01,

        USE_ALPHA_FLAG      = 0x20,
        IGNORE_ALPHA_FLAG   = 0x40,
        NORMAL_DIRECTX_FLAG = 0x80
    };

    enum MirrorFlags
    {
        MIRROR_HORIZONTAL_DIRECTION       = 1 << 1,
        MIRROR_VERTICAL_DIRECTION         = 1 << 2,
        MIRROR_DEPTH_DIRECTION            = 1 << 3,

        MIRROR_HORIZONTAL_DIRECTION_POS_X = 1 << 4,
        MIRROR_HORIZONTAL_DIRECTION_POS_Y = 1 << 5,
        MIRROR_HORIZONTAL_DIRECTION_POS_Z = 1 << 6,

        MIRROR_HORIZONTAL_DIRECTION_NEG_X = 1 << 7,
        MIRROR_HORIZONTAL_DIRECTION_NEG_Y = 1 << 8,
        MIRROR_HORIZONTAL_DIRECTION_NEG_Z = 1 << 9,

        MIRROR_VERTICAL_DIRECTION_POS_X   = 1 << 10,
        MIRROR_VERTICAL_DIRECTION_POS_Y   = 1 << 11,
        MIRROR_VERTICAL_DIRECTION_POS_Z   = 1 << 12,

        MIRROR_VERTICAL_DIRECTION_NEG_X   = 1 << 13,
        MIRROR_VERTICAL_DIRECTION_NEG_Y   = 1 << 14,
        MIRROR_VERTICAL_DIRECTION_NEG_Z   = 1 << 15,

        CUBEMAP_DEFAULT_MIRROR_FLAGS      =
                    MIRROR_HORIZONTAL_DIRECTION_POS_X
                  | MIRROR_HORIZONTAL_DIRECTION_NEG_X
                  | MIRROR_HORIZONTAL_DIRECTION_POS_Z
                  | MIRROR_HORIZONTAL_DIRECTION_NEG_Z
                  | MIRROR_VERTICAL_DIRECTION_POS_X
                  | MIRROR_VERTICAL_DIRECTION_NEG_X
                  | MIRROR_VERTICAL_DIRECTION_POS_Z
                  | MIRROR_VERTICAL_DIRECTION_NEG_Z,
    };

    enum CubeMapSide
    {
        POS_X  = 0,
        POS_Y  = 1,
        POS_Z  = 2,
        NEG_X  = 3,
        NEG_Y  = 4,
        NEG_Z  = 5,

        RIGHT  = POS_X,
        TOP    = POS_Y,
        BACK   = POS_Z,
        LEFT   = NEG_X,
        BOTTOM = NEG_Y,
        FRONT  = NEG_Z,

        EAST  = POS_X,
        UP    = POS_Y,
        SOUTH = POS_Z,
        WEST  = NEG_X,
        DOWN  = NEG_Y,
        NORTH = NEG_Z,
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Interface                                 */
    /*! \{                                                                 */

    const GLenum getAdaptedInternalFormat   (
                                                GLenum pixelFormat, 
                                                GLenum dataType
                                            ) const;

    void                setFilename         (const std::string& filename);
    const std::string&  getFilename         () const;

    void                setFilename         (const std::string& filename, CubeMapSide side);
    const std::string&  getFilename         (CubeMapSide side) const;

    void                setTexImage         (Image* const image);
    Image*              getTexImage         () const;

    void                setTexImage         (Image* const image, CubeMapSide side);
    Image*              getTexImage         (CubeMapSide side) const;

    bool                hasTexImage         () const;

    bool                isEnvironmentMap    () const;
    bool                isEquirectangularMap() const;
    bool                isCubeMap           () const;

    void                loadImage           ();

    Matrix              getMatrix           () const;

    const Char8*        getTextureTypeName  () const;

    bool                hasSwizzle          () const;
    SwizzleIndicesT     getSwizzleIndices   () const;

    bool                isInverted          () const;

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

    // Variables should all be in TextureDescBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextureDesc(void);
    TextureDesc(const TextureDesc &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                  Image loader                                */
    /*! \{                                                                 */

    typedef std::vector<ImageUnrecPtr>  ImageStore;

    ImageTransitPtr     readImage       (const std::string& f) const;
    ImageTransitPtr     readImage       (                    );
    ImageTransitPtr     readImage       (CubeMapSide side, UInt32 mirrorFlags, bool mirror_horiz, bool mirror_verti);
    bool                readImage       (ImageStore& images  );

    void                mirrorCubemapImages
                                        (
                                            CubeMapSide side, 
                                            Image*      image, 
                                            UInt32      mirrorFlags, 
                                            bool        mirror_horiz, 
                                            bool        mirror_verti
                                        ) const;

    /*! \}                                                                 */




    /*==========================  PRIVATE  ================================*/

  private:

    static std::string _emptyFileName;

    friend class FieldContainer;
    friend class TextureDescBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextureDesc &source);
};

typedef TextureDesc *TextureDescP;

OSG_END_NAMESPACE

#include "OSGTextureDescBase.inl"
#include "OSGTextureDesc.inl"

#endif /* _OSGTEXTUREDESC_H_ */
