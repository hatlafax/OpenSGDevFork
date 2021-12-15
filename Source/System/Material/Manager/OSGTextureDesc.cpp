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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <boost/filesystem.hpp>

#include "OSGConfig.h"

#include "OSGTextureDesc.h"
#include "OSGImage.h"
#include "OSGQuaternion.h"

#include "OSGHashKeyToFieldContainerMap.h"
#include "OSGBaseHash.h"

//#define OSG_TEXTUREDESC_CUBEMAP_WRITE_TEST_IMAGES

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTextureDescBase.cpp file.
// To modify it, please change the .fcd file (OSGTextureDesc.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::string TextureDesc::_emptyFileName = "";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextureDesc::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextureDesc::TextureDesc(void) :
    Inherited()
{
}

TextureDesc::TextureDesc(const TextureDesc &source) :
    Inherited(source)
{
}

TextureDesc::~TextureDesc(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextureDesc::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TextureDesc::dump(      UInt32    ,
                       const BitVector ) const
{
    SLOG << "Dump TextureDesc NI" << std::endl;

    std::string spc = "    ";

    if (isCubeMap())
    {
        SLOG << spc << "Filename[POS_X]      = " << getFilename(POS_X) << std::endl;
        SLOG << spc << "Filename[POS_Y]      = " << getFilename(POS_Y) << std::endl;
        SLOG << spc << "Filename[POS_Z]      = " << getFilename(POS_Z) << std::endl;
        SLOG << spc << "Filename[NEG_X]      = " << getFilename(NEG_X) << std::endl;
        SLOG << spc << "Filename[NEG_Y]      = " << getFilename(NEG_Y) << std::endl;
        SLOG << spc << "Filename[NEG_Z]      = " << getFilename(NEG_Z) << std::endl;
        SLOG << spc << "hasTexImage          = " << hasTexImage() << std::endl;
    }
    else
    {
        SLOG << spc << "Filename             = " << getFilename() << std::endl;
        SLOG << spc << "hasTexImage          = " << hasTexImage() << std::endl;
    }

    SLOG << spc << "isEnvironmentMap     = " << isEnvironmentMap() << std::endl;
    SLOG << spc << "isEquirectangularMap = " << isEquirectangularMap() << std::endl;
    SLOG << spc << "isCubeMap            = " << isCubeMap() << std::endl;

    SLOG << spc << "Matrix               = " << getMatrix() << std::endl;

    SLOG << spc << "TextureTypeName      = " << getTextureTypeName() << std::endl;
    SLOG << spc << "hasSwizzle           = " << hasSwizzle() << std::endl;
    SLOG << spc << "isInverted           = " << isInverted() << std::endl;
    SLOG << spc << "ignoreAlpha          = " << ((getTextureFlags() & INVERT_FLAG) != 0) << std::endl;
    SLOG << spc << "isNormalDirectX      = " << ((getTextureFlags() & NORMAL_DIRECTX_FLAG) != 0) << std::endl;

    std::string texture_type = "NONE_TEXTURE";
    switch (getTextureType())
    {
        case NONE_TEXTURE:              texture_type = "NONE_TEXTURE";              break;
        case UNKNOWN_TEXTURE:           texture_type = "UNKNOWN_TEXTURE";           break;
        case ALBEDO_TEXTURE:            texture_type = "ALBEDO_TEXTURE";            break;
        case SPECULAR_TEXTURE:          texture_type = "SPECULAR_TEXTURE";          break;
        case EMISSIVE_TEXTURE:          texture_type = "EMISSIVE_TEXTURE";          break;
        case SHININESS_TEXTURE:         texture_type = "SHININESS_TEXTURE";         break;
        case OPACITY_TEXTURE:           texture_type = "OPACITY_TEXTURE";           break;
        case NORMALS_TEXTURE:           texture_type = "NORMALS_TEXTURE";           break;
        case HEIGHT_TEXTURE:            texture_type = "HEIGHT_TEXTURE";            break;
        case DISPLACEMENT_TEXTURE:      texture_type = "DISPLACEMENT_TEXTURE";      break;
        case REFLECTION_TEXTURE:        texture_type = "REFLECTION_TEXTURE";        break;
        case REFRACTION_TEXTURE:        texture_type = "REFRACTION_TEXTURE";        break;
        case ANISOTROPY_U_TEXTURE:      texture_type = "ANISOTROPY_U_TEXTURE";      break;
        case ANISOTROPY_V_TEXTURE:      texture_type = "ANISOTROPY_V_TEXTURE";      break;
        case ANISOTROPY_UV_TEXTURE:     texture_type = "ANISOTROPY_UV_TEXTURE";     break;
        case AMBIENT_OCCLUSION_TEXTURE: texture_type = "AMBIENT_OCCLUSION_TEXTURE"; break;
        case ROUGH_TEXTURE:             texture_type = "ROUGH_TEXTURE";             break;
        case METAL_TEXTURE:             texture_type = "METAL_TEXTURE";             break;
        case ROUGH_METAL_TEXTURE:       texture_type = "ROUGH_METAL_TEXTURE";       break;
        case OCCL_ROUGH_METAL_TEXTURE:  texture_type = "OCCL_ROUGH_METAL_TEXTURE";  break;
        case IRRADIANCE_TEXTURE:        texture_type = "IRRADIANCE_TEXTURE";        break;
        case PRE_FILTER_TEXTURE:        texture_type = "PRE_FILTER_TEXTURE";        break;
        case BRDF_LUT_TEXTURE:          texture_type = "BRDF_LUT_TEXTURE";          break;
        case STANDARD_MATERIAL_TEXTURE: texture_type = "STANDARD_MATERIAL_TEXTURE"; break;
    }
    SLOG << spc << "TextureType          = " << texture_type << std::endl;

    SLOG << spc << "Swizzle              = " << getSwizzle() << std::endl;
    SLOG << spc << "IsSRGBTexture        = " << getIsSRGBTexture() << std::endl;
    SLOG << spc << "TexUnit              = " << getTexUnit() << std::endl;
    SLOG << spc << "UVChannel            = " << getUVChannel() << std::endl;

    std::string mapping_mode = "UV_MAPPING";
    switch (getMappingMode())
    {
        case UV_MAPPING:        mapping_mode = "UV_MAPPING";        break;
        case SPHERE_MAPPING:    mapping_mode = "SPHERE_MAPPING";    break;
        case CYLINDER_MAPPING:  mapping_mode = "CYLINDER_MAPPING";  break;
        case BOX_MAPPING:       mapping_mode = "BOX_MAPPING";       break;
        case PLANE_MAPPING:     mapping_mode = "PLANE_MAPPING";     break;
        case OTHER_MAPPING:     mapping_mode = "OTHER_MAPPING";     break;
    }
    SLOG << spc << "MappingMode          = " << mapping_mode << std::endl;

    SLOG << spc << "MapAxis              = " << getMapAxis() << std::endl;

    std::string environment_map_type = "OTHER_MAP";
    switch (getEnvironmentMapType())
    {
        case OTHER_MAP:                 environment_map_type = "OTHER_MAP";                 break;
        case EQUIRECTANGULAR_MAP:       environment_map_type = "EQUIRECTANGULAR_MAP";       break;
        case CUBE_MAP:                  environment_map_type = "CUBE_MAP";                  break;
        case VERTICAL_CROSS_CUBE_MAP:   environment_map_type = "VERTICAL_CROSS_CUBE_MAP";   break;
        case HORIZONTAL_CROSS_CUBE_MAP: environment_map_type = "HORIZONTAL_CROSS_CUBE_MAP"; break;
        case VERTICAL_STRIP_CUBE_MAP:   environment_map_type = "VERTICAL_STRIP_CUBE_MAP";   break;
        case HORIZONTAL_STRIP_CUBE_MAP: environment_map_type = "HORIZONTAL_STRIP_CUBE_MAP"; break;
    }
    SLOG << spc << "EnvironmentMapType   = " << environment_map_type << std::endl;

    SLOG << spc << "BlendFactor          = " << getBlendFactor() << std::endl;

    std::string operation = "MULTIPLY_OPERATION";
    switch (getOperation())
    {
        case MULTIPLY_OPERATION:    operation = "MULTIPLY_OPERATION";   break;
        case ADD_OPERATION:         operation = "ADD_OPERATION";        break;
        case SUBTRACT_OPERATION:    operation = "SUBTRACT_OPERATION";   break;
        case DIVIDE_OPERATION:      operation = "DIVIDE_OPERATION";     break;
        case SMOOTHADD_OPERATION:   operation = "SMOOTHADD_OPERATION";  break;
        case SIGNEDADD_OPERATION:   operation = "SIGNEDADD_OPERATION";  break;
        case REPLACE_OPERATION:     operation = "REPLACE_OPERATION";    break;
        case DECAL_OPERATION:       operation = "DECAL_OPERATION";      break;
        case BLEND_OPERATION:       operation = "BLEND_OPERATION";      break;
    }
    SLOG << spc << "Operation            = " << operation << std::endl;

    std::string wrap_s = "GL_REPEAT";
    switch (getWrapS())
    {
        case GL_REPEAT:          wrap_s = "GL_REPEAT";          break;
        case GL_CLAMP_TO_EDGE:   wrap_s = "GL_CLAMP_TO_EDGE";   break;
        case GL_CLAMP_TO_BORDER: wrap_s = "GL_CLAMP_TO_BORDER"; break;
        case GL_MIRRORED_REPEAT: wrap_s = "GL_MIRRORED_REPEAT"; break;
    }
    SLOG << spc << "WrapS                = " << wrap_s << std::endl;

    std::string wrap_t = "GL_REPEAT";
    switch (getWrapT())
    {
        case GL_REPEAT:          wrap_t = "GL_REPEAT";          break;
        case GL_CLAMP_TO_EDGE:   wrap_t = "GL_CLAMP_TO_EDGE";   break;
        case GL_CLAMP_TO_BORDER: wrap_t = "GL_CLAMP_TO_BORDER"; break;
        case GL_MIRRORED_REPEAT: wrap_t = "GL_MIRRORED_REPEAT"; break;
    }
    SLOG << spc << "WrapT                = " << wrap_t << std::endl;

    std::string wrap_r = "GL_REPEAT";
    switch (getWrapR())
    {
        case GL_REPEAT:          wrap_r = "GL_REPEAT";          break;
        case GL_CLAMP_TO_EDGE:   wrap_r = "GL_CLAMP_TO_EDGE";   break;
        case GL_CLAMP_TO_BORDER: wrap_r = "GL_CLAMP_TO_BORDER"; break;
        case GL_MIRRORED_REPEAT: wrap_r = "GL_MIRRORED_REPEAT"; break;
    }
    SLOG << spc << "WrapR                = " << wrap_r << std::endl;

    std::string min_filter = "GL_NEAREST";
    switch (getMinFilter())
    {
        case GL_NEAREST:                min_filter = "GL_NEAREST";                break;
        case GL_LINEAR:                 min_filter = "GL_LINEAR";                 break;
        case GL_NEAREST_MIPMAP_NEAREST: min_filter = "GL_NEAREST_MIPMAP_NEAREST"; break;
        case GL_LINEAR_MIPMAP_NEAREST:  min_filter = "GL_LINEAR_MIPMAP_NEAREST";  break;
        case GL_NEAREST_MIPMAP_LINEAR:  min_filter = "GL_NEAREST_MIPMAP_LINEAR";  break;
        case GL_LINEAR_MIPMAP_LINEAR:   min_filter = "GL_LINEAR_MIPMAP_LINEAR";   break;
    }
    SLOG << spc << "MinFilter            = " << min_filter << std::endl;

    std::string mag_filter = "GL_NEAREST";
    switch (getMinFilter())
    {
        case GL_NEAREST: mag_filter = "GL_NEAREST"; break;
        case GL_LINEAR:  mag_filter = "GL_LINEAR";  break;
    }
    SLOG << spc << "MagFilter            = " << mag_filter << std::endl;

    std::string internal_format = "GL_NONE";
    switch (getInternalFormat())
    {
        case GL_DEPTH_COMPONENT:                    internal_format = "GL_DEPTH_COMPONENT"; break;
        case GL_DEPTH_STENCIL:                      internal_format = "GL_DEPTH_STENCIL"; break;
        case GL_RED:                                internal_format = "GL_RED"; break;
        case GL_RG:                                 internal_format = "GL_RG"; break;
        case GL_RGB:                                internal_format = "GL_RGB"; break;
        case GL_RGBA:                               internal_format = "GL_RGBA"; break;
        case GL_R8:                                 internal_format = "GL_R8"; break;
        case GL_R8_SNORM:                           internal_format = "GL_R8_SNORM"; break;
        case GL_R16:                                internal_format = "GL_R16"; break;
        case GL_R16_SNORM:                          internal_format = "GL_R16_SNORM"; break;
        case GL_RG8:                                internal_format = "GL_RG8"; break;
        case GL_RG8_SNORM:                          internal_format = "GL_RG8_SNORM"; break;
        case GL_RG16:                               internal_format = "GL_RG16"; break;
        case GL_RG16_SNORM:                         internal_format = "GL_RG16_SNORM"; break;
        case GL_R3_G3_B2:                           internal_format = "GL_R3_G3_B2"; break;
        case GL_RGB4:                               internal_format = "GL_RGB4"; break;
        case GL_RGB5:                               internal_format = "GL_RGB5"; break;
        case GL_RGB8:                               internal_format = "GL_RGB8"; break;
        case GL_RGB8_SNORM:                         internal_format = "GL_RGB8_SNORM"; break;
        case GL_RGB10:                              internal_format = "GL_RGB10"; break;
        case GL_RGB12:                              internal_format = "GL_RGB12"; break;
        case GL_RGB16_SNORM:                        internal_format = "GL_RGB16_SNORM"; break;
        case GL_RGBA2:                              internal_format = "GL_RGBA2"; break;
        case GL_RGBA4:                              internal_format = "GL_RGBA4"; break;
        case GL_RGB5_A1:                            internal_format = "GL_RGB5_A1"; break;
        case GL_RGBA8:                              internal_format = "GL_RGBA8"; break;
        case GL_RGBA8_SNORM:                        internal_format = "GL_RGBA8_SNORM"; break;
        case GL_RGB10_A2:                           internal_format = "GL_RGB10_A2"; break;
        case GL_RGB10_A2UI:                         internal_format = "GL_RGB10_A2UI"; break;
        case GL_RGBA12:                             internal_format = "GL_RGBA12"; break;
        case GL_RGBA16:                             internal_format = "GL_RGBA16"; break;
        case GL_SRGB8:                              internal_format = "GL_SRGB8"; break;
        case GL_SRGB8_ALPHA8:                       internal_format = "GL_SRGB8_ALPHA8"; break;
        case GL_R16F:                               internal_format = "GL_R16F"; break;
        case GL_RG16F:                              internal_format = "GL_RG16F"; break;
        case GL_RGB16F:                             internal_format = "GL_RGB16F"; break;
        case GL_RGBA16F:                            internal_format = "GL_RGBA16F"; break;
        case GL_R32F:                               internal_format = "GL_R32F"; break;
        case GL_RG32F:                              internal_format = "GL_RG32F"; break;
        case GL_RGB32F:                             internal_format = "GL_RGB32F"; break;
        case GL_RGBA32F:                            internal_format = "GL_RGBA32F"; break;
        case GL_R11F_G11F_B10F:                     internal_format = "GL_R11F_G11F_B10F"; break;
        case GL_RGB9_E5:                            internal_format = "GL_RGB9_E5"; break;
        case GL_R8I:                                internal_format = "GL_R8I"; break;
        case GL_R8UI:                               internal_format = "GL_R8UI"; break;
        case GL_R16I:                               internal_format = "GL_R16I"; break;
        case GL_R16UI:                              internal_format = "GL_R16UI"; break;
        case GL_R32I:                               internal_format = "GL_R32I"; break;
        case GL_R32UI:                              internal_format = "GL_R32UI"; break;
        case GL_RG8I:                               internal_format = "GL_RG8I"; break;
        case GL_RG8UI:                              internal_format = "GL_RG8UI"; break;
        case GL_RG16I:                              internal_format = "GL_RG16I"; break;
        case GL_RG16UI:                             internal_format = "GL_RG16UI"; break;
        case GL_RG32I:                              internal_format = "GL_RG32I"; break;
        case GL_RG32UI:                             internal_format = "GL_RG32UI"; break;
        case GL_RGB8I:                              internal_format = "GL_RGB8I"; break;
        case GL_RGB8UI:                             internal_format = "GL_RGB8UI"; break;
        case GL_RGB16I:                             internal_format = "GL_RGB16I"; break;
        case GL_RGB16UI:                            internal_format = "GL_RGB16UI"; break;
        case GL_RGB32I:                             internal_format = "GL_RGB32I"; break;
        case GL_RGB32UI:                            internal_format = "GL_RGB32UI"; break;
        case GL_RGBA8I:                             internal_format = "GL_RGBA8I"; break;
        case GL_RGBA8UI:                            internal_format = "GL_RGBA8UI"; break;
        case GL_RGBA16I:                            internal_format = "GL_RGBA16I"; break;
        case GL_RGBA16UI:                           internal_format = "GL_RGBA16UI"; break;
        case GL_RGBA32I:                            internal_format = "GL_RGBA32I"; break;
        case GL_RGBA32UI:                           internal_format = "GL_RGBA32UI"; break;
        case GL_COMPRESSED_RED:                     internal_format = "GL_COMPRESSED_RED"; break;
        case GL_COMPRESSED_RG:                      internal_format = "GL_COMPRESSED_RG"; break;
        case GL_COMPRESSED_RGB:                     internal_format = "GL_COMPRESSED_RGB"; break;
        case GL_COMPRESSED_RGBA:                    internal_format = "GL_COMPRESSED_RGBA"; break;
        case GL_COMPRESSED_SRGB:                    internal_format = "GL_COMPRESSED_SRGB"; break;
        case GL_COMPRESSED_SRGB_ALPHA:              internal_format = "GL_COMPRESSED_SRGB_ALPHA"; break;
        case GL_COMPRESSED_RED_RGTC1:               internal_format = "GL_COMPRESSED_RED_RGTC1"; break;
        case GL_COMPRESSED_SIGNED_RED_RGTC1:        internal_format = "GL_COMPRESSED_SIGNED_RED_RGTC1"; break;
        case GL_COMPRESSED_RG_RGTC2:                internal_format = "GL_COMPRESSED_RG_RGTC2"; break;
        case GL_COMPRESSED_SIGNED_RG_RGTC2:         internal_format = "GL_COMPRESSED_SIGNED_RG_RGTC2"; break;
        case GL_COMPRESSED_RGBA_BPTC_UNORM:         internal_format = "GL_COMPRESSED_RGBA_BPTC_UNORM"; break;
        case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:   internal_format = "GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM"; break;
        case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT:   internal_format = "GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT"; break;
        case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT: internal_format = "GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT"; break;
    }
    SLOG << spc << "InternalFormat       = " << internal_format << std::endl;

    std::string external_format = "GL_NONE";
    switch (getExternalFormat())
    {
        case GL_RED:             external_format = "GL_RED"; break;
        case GL_RG:              external_format = "GL_RG"; break;
        case GL_RGB:             external_format = "GL_RGB"; break;
        case GL_BGR:             external_format = "GL_BGR"; break;
        case GL_RGBA:            external_format = "GL_RGBA"; break;
        case GL_BGRA:            external_format = "GL_BGRA"; break;
        case GL_RED_INTEGER:     external_format = "GL_RED_INTEGER"; break;
        case GL_RG_INTEGER:      external_format = "GL_RG_INTEGER"; break;
        case GL_RGB_INTEGER:     external_format = "GL_RGB_INTEGER"; break;
        case GL_BGR_INTEGER:     external_format = "GL_BGR_INTEGER"; break;
        case GL_RGBA_INTEGER:    external_format = "GL_RGBA_INTEGER"; break;
        case GL_BGRA_INTEGER:    external_format = "GL_BGRA_INTEGER"; break;
        case GL_STENCIL_INDEX:   external_format = "GL_STENCIL_INDEX"; break;
        case GL_DEPTH_COMPONENT: external_format = "GL_DEPTH_COMPONENT"; break;
        case GL_DEPTH_STENCIL:   external_format = "GL_DEPTH_STENCIL"; break;
    }
    SLOG << spc << "ExternalFormat       = " << external_format << std::endl;

    SLOG << spc << "Anisotropy           = " << getAnisotropy() << std::endl;

    std::string mirror_flags = "UNKNOWN";
    switch (getMirrorFlags())
    {
        case 0:                                 mirror_flags = "0"; break;
        case MIRROR_HORIZONTAL_DIRECTION:       mirror_flags = "MIRROR_HORIZONTAL_DIRECTION"; break;
        case MIRROR_VERTICAL_DIRECTION:         mirror_flags = "MIRROR_VERTICAL_DIRECTION"; break;
        case MIRROR_DEPTH_DIRECTION:            mirror_flags = "MIRROR_DEPTH_DIRECTION"; break;
        case MIRROR_HORIZONTAL_DIRECTION_POS_X: mirror_flags = "MIRROR_HORIZONTAL_DIRECTION_POS_X"; break;
        case MIRROR_HORIZONTAL_DIRECTION_POS_Y: mirror_flags = "MIRROR_HORIZONTAL_DIRECTION_POS_Y"; break;
        case MIRROR_HORIZONTAL_DIRECTION_POS_Z: mirror_flags = "MIRROR_HORIZONTAL_DIRECTION_POS_Z"; break;
        case MIRROR_HORIZONTAL_DIRECTION_NEG_X: mirror_flags = "MIRROR_HORIZONTAL_DIRECTION_NEG_X"; break;
        case MIRROR_HORIZONTAL_DIRECTION_NEG_Y: mirror_flags = "MIRROR_HORIZONTAL_DIRECTION_NEG_Y"; break;
        case MIRROR_HORIZONTAL_DIRECTION_NEG_Z: mirror_flags = "MIRROR_HORIZONTAL_DIRECTION_NEG_Z"; break;
        case MIRROR_VERTICAL_DIRECTION_POS_X:   mirror_flags = "MIRROR_VERTICAL_DIRECTION_POS_X"; break;
        case MIRROR_VERTICAL_DIRECTION_POS_Y:   mirror_flags = "MIRROR_VERTICAL_DIRECTION_POS_Y"; break;
        case MIRROR_VERTICAL_DIRECTION_POS_Z:   mirror_flags = "MIRROR_VERTICAL_DIRECTION_POS_Z"; break;
        case MIRROR_VERTICAL_DIRECTION_NEG_X:   mirror_flags = "MIRROR_VERTICAL_DIRECTION_NEG_X"; break;
        case MIRROR_VERTICAL_DIRECTION_NEG_Y:   mirror_flags = "MIRROR_VERTICAL_DIRECTION_NEG_Y"; break;
        case MIRROR_VERTICAL_DIRECTION_NEG_Z:   mirror_flags = "MIRROR_VERTICAL_DIRECTION_NEG_Z"; break;
        case CUBEMAP_DEFAULT_MIRROR_FLAGS:      mirror_flags = "CUBEMAP_DEFAULT_MIRROR_FLAGS"; break;

    }
    SLOG << spc << "MirrorFlags          = " << mirror_flags << std::endl;

    SLOG << spc << "Scale                = " << getScale() << std::endl;

    SLOG << spc << "Translate            = " << getTranslate() << std::endl;

    SLOG << spc << "Rotate               = " << getRotate() << std::endl;

    SLOG << spc << "HasUVTransform       = " << getHasUVTransform() << std::endl;

    SLOG << spc << "BorderColor          = " << getBorderColor() << std::endl;

    if (isCubeMap())
    {
        if (hasTexImage())
        {
            for (int side = POS_X; side <= NEG_Z; ++side)
            {
                Image* image = getTexImage(static_cast<CubeMapSide>(side));
                if (image)
                {
                    image->dump();
                }
            }
            
        }
    }
    else
    {
        if (hasTexImage())
        {
            Image* image = getTexImage();
            if (image)
            {
                image->dump();
            }
        }
    }
}

/*---------------------------- Interface ----------------------------------*/

const GLenum TextureDesc::getAdaptedInternalFormat(
    GLenum pixelFormat, GLenum dataType) const
{
    GLenum internalFormat = getInternalFormat();
    GLenum externalFormat = getExternalFormat();

    if (externalFormat == GL_NONE)
        externalFormat = pixelFormat;

    if (internalFormat == GL_NONE && getIsSRGBTexture())
    {
        switch(externalFormat)
        {
            case GL_BGR:
            case GL_RGB:
            {
                switch(dataType)
                {
                    case GL_FLOAT:
                    case GL_HALF_FLOAT_NV:
                        break;
                    default:
                        internalFormat = GL_SRGB;
                }
            }
            break;

            case GL_BGRA:
            case GL_RGBA:
            {
                switch(dataType)
                {
                    case GL_FLOAT:
                    case GL_HALF_FLOAT_NV:
                        break;
                    default:
                        internalFormat = GL_SRGB_ALPHA;
                }
            }
            break;
        }
    }
    return internalFormat;
}

void TextureDesc::setFilename(const std::string& filename)
{
    MFString& filenames = *editMFFilename();

    filenames.resize(1);
    filenames[0] = filename;
}

const std::string& TextureDesc::getFilename() const
{
    const MFString& filenames = *getMFFilename();
    return filenames.empty() ? _emptyFileName : filenames[0];
}

void TextureDesc::setFilename(const std::string& filename, CubeMapSide side)
{
    MFString& filenames = *editMFFilename();

    if (filenames.size32() <= UInt32(side))
        filenames.resize(6);

    filenames[UInt32(side)] = filename;
}

const std::string& TextureDesc::getFilename(CubeMapSide side) const
{
    const MFString& filenames = *getMFFilename();
    if (filenames.size32() <= UInt32(side))
    {
        return _emptyFileName;
    }
    else
    {
        return filenames[UInt32(side)];
    }
}

void TextureDesc::setTexImage(Image* const image)
{
    editMField(TexImageFieldMask, _mfTexImage);
    _mfTexImage.resize(1);
    _mfTexImage[0] = image;
}

Image* TextureDesc::getTexImage() const
{
    return _mfTexImage.empty() ? NULL : _mfTexImage[0];
}

void TextureDesc::setTexImage(Image* const image, CubeMapSide side)
{
    editMField(TexImageFieldMask, _mfTexImage);

    if (_mfTexImage.size32() <= UInt32(side))
        _mfTexImage.resize(6);

    _mfTexImage[UInt32(side)] = image;
}

Image* TextureDesc::getTexImage(CubeMapSide side) const
{
    return _mfTexImage.size32() <= UInt32(side) ? NULL : _mfTexImage[UInt32(side)];
}

void TextureDesc::loadImage()
{
    if (isCubeMap())
    {
        ImageStore images;

        readImage(images);

        OSG_ASSERT(images.size() == 6);

        for (UInt32 i = 0; i < 6; ++i)
        {
            setTexImage(images[i], static_cast<CubeMapSide>(i));
        }
    }
    else
    {
        ImageUnrecPtr image = readImage();
        setTexImage(image);
    }
}

bool TextureDesc::hasTexImage() const
{
    if (isCubeMap())
    {
        return getTexImage(POS_X) != NULL
            && getTexImage(POS_Y) != NULL
            && getTexImage(POS_Z) != NULL
            && getTexImage(NEG_X) != NULL
            && getTexImage(NEG_Y) != NULL
            && getTexImage(NEG_Z) != NULL
            ;
    }
    else
    {
        return getTexImage() != NULL;
    }
}

/*------------------------------ image loader -----------------------------*/

ImageTransitPtr TextureDesc::readImage(const std::string& f) const
{
    bool result = false;

    ImageUnrecPtr image = OSG::Image::createLocal();

    namespace fs = ::boost::filesystem;

    fs::path filename = f;
    if (!filename.empty())
    {
        if (fs::exists(filename) && fs::is_regular_file(filename))
        {
            result = image->read(filename.string().c_str());
        }
    }

    if (!result)
        image = NULL;

    return ImageTransitPtr(image);
}

ImageTransitPtr TextureDesc::readImage()
{
    typedef HashKeyToFieldContainerMap::HashKeyType HashKeyType;

    ImageUnrecPtr image = NULL;
    HashKeyType   key   = 0;

    const std::string& file = getFilename();
    UInt32 mirrorFlags      = getMirrorFlags();

    HashKeyToFieldContainerMap* imageMap = getImageMap();
    if (imageMap)
    {
        key   = Hash64::hash(&file[0], file.size(), mirrorFlags);
        image = dynamic_cast<Image*>(getImageMap()->find(key));
    }

    if (image == NULL)
    {
        image = readImage(file);

        if (image != NULL)
        {
            bool mirror_horiz, mirror_verti, mirror_depth;

            mirror_horiz = ((mirrorFlags & MIRROR_HORIZONTAL_DIRECTION) != 0);
            mirror_verti = ((mirrorFlags & MIRROR_VERTICAL_DIRECTION  ) != 0);
            mirror_depth = ((mirrorFlags & MIRROR_DEPTH_DIRECTION     ) != 0);

            if (mirror_horiz || mirror_verti || mirror_depth)
                image->mirror(mirror_horiz, mirror_verti, mirror_depth);

            // not working in Release code, and generally, not advisable
            if (false && !image->hasCompressedData())
            {
                switch (image->getDataType())
                {
                    case Image::OSG_UINT8_IMAGEDATA:
                        switch (image->getPixelFormat())
                        {
                            case Image::OSG_RGB_PF:
                                image->reformat(OSG::Image::OSG_RGB_DXT1, nullptr, 0);
                                break;
                            case Image::OSG_RGBA_PF:
                                image->reformat(OSG::Image::OSG_RGBA_DXT5, nullptr, 0);
                                break;
                        }
                        break;
                }
            }

            if (imageMap)
            {
                imageMap->insert(key, image);
            }
        }
    }

    return ImageTransitPtr(image);
}

ImageTransitPtr TextureDesc::readImage(
    CubeMapSide side, 
    UInt32      mirrorFlags, 
    bool        mirror_horiz, 
    bool        mirror_verti)
{
    typedef HashKeyToFieldContainerMap::HashKeyType HashKeyType;

    ImageUnrecPtr image = NULL;
    HashKeyType   key   = 0;

    const std::string& file = getFilename(side);

    HashKeyToFieldContainerMap* imageMap = getImageMap();
    if (imageMap)
    {
        UInt32 side_seed = (1 << (0x1F + side));
        Hash64 hasher;

        hasher.update(getMirrorFlags());
        hasher.update(side_seed);
        hasher.update(mirror_horiz);
        hasher.update(mirror_verti);
        hasher.update_from_string(file);
       
        key = hasher.finish();

        image = dynamic_cast<Image*>(getImageMap()->find(key));
    }

    if (image == NULL)
    {
        image = readImage(file);

        mirrorCubemapImages(side, image, mirrorFlags, mirror_horiz, mirror_verti);

        if (imageMap)
        {
            imageMap->insert(key, image);
        }
    }

    return ImageTransitPtr(image);
}

bool TextureDesc::readImage(ImageStore& images)
{
    if (images.size() != 6)
        images.resize(6, NULL);

    UInt32 mirrorFlags = getMirrorFlags();

    //
    // First six independent image files
    //
    if (getMFFilename()->size() == 6 && getEnvironmentMapType() == CUBE_MAP)
    {
        images[POS_X] = readImage(POS_X, mirrorFlags, true,  true);
        images[POS_Y] = readImage(POS_Y, mirrorFlags, false, false);
        images[POS_Z] = readImage(POS_Z, mirrorFlags, true,  true);
        images[NEG_X] = readImage(NEG_X, mirrorFlags, true,  true);
        images[NEG_Y] = readImage(NEG_Y, mirrorFlags, false, false);
        images[NEG_Z] = readImage(NEG_Z, mirrorFlags, true,  true);
    }
    //
    // Secondly a H-Cross, V-Cross, H-Strip or V-Strip image
    //
    else if (getMFFilename()->size() == 1 && getEnvironmentMapType() >= CUBE_MAP)
    {
        typedef HashKeyToFieldContainerMap::HashKeyType HashKeyType;

        bool mirror_horiz[6];
        bool mirror_verti[6];

        HashKeyType   key[6];

        for (UInt32 i = POS_X; i <= NEG_Z; ++i)
        {
                  key[i] = 0;
               images[i] = NULL;
        }

        HashKeyToFieldContainerMap* imageMap = getImageMap();

        const std::string& file = getFilename();

        bool found = false;

        if (imageMap)
        {
            found = true;

            for (UInt32 i = POS_X; i <= NEG_Z; ++i)
            {
                   key[i] = Hash64::hash(&file[0], file.size(), (1 << (0x1F + i)));
                images[i] = dynamic_cast<Image*>(imageMap->find(key[i]));

                if (images[i] == NULL)
                {
                    found = false;
                }
            }
        }

        if (!found)
        {
            ImageUnrecPtr image = readImage(file);

            if (image != NULL)
            {
                Real32 width  = image->getWidth ();
                Real32 height = image->getHeight();
                Real32 depth  = image->getDepth ();

                Real32 ratio  = width / height;

                Int32  offX,  offY,  offZ;
                Int32 destW, destH, destD;

                for (UInt32 i = POS_X; i <= NEG_Z; ++i)
                {
                    images[i] = Image::create();
                }

                if (osgAbs(ratio - 4.f/3.f) < 1.E-3)
                {
                    // Found Horizontal cross image by ratio. Environment type should nevertheless by consistent
                    if ( getEnvironmentMapType() == CUBE_MAP 
                      || getEnvironmentMapType() == HORIZONTAL_CROSS_CUBE_MAP )
                    {
                        destW = Int32( width / 4.f + 0.5f);
                        destH = Int32(height / 3.f + 0.5f);
                        destD = Int32(depth);

                        // POS_Y and NEG_Y are exchanged, because we load the images with origin at top/left position.

                        offX = 2 * destW;  offY = 1 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_X]);
                        offX = 1 * destW;  offY = 2 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_Y]);
                        offX = 1 * destW;  offY = 1 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_Z]);
                        offX = 0 * destW;  offY = 1 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_X]);
                        offX = 1 * destW;  offY = 0 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_Y]);
                        offX = 3 * destW;  offY = 1 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_Z]);

                        mirror_horiz[POS_X] = true;  mirror_verti[POS_X] = true;
                        mirror_horiz[POS_Y] = false; mirror_verti[POS_Y] = false;
                        mirror_horiz[POS_Z] = true;  mirror_verti[POS_Z] = true;
                        mirror_horiz[NEG_X] = true;  mirror_verti[NEG_X] = true;
                        mirror_horiz[NEG_Y] = false; mirror_verti[NEG_Y] = false;
                        mirror_horiz[NEG_Z] = true;  mirror_verti[NEG_Z] = true;
                    }
                }
                else
                if (osgAbs(ratio - 3.f/4.f) < 1.E-3)
                {
                    // Found Vertical cross image by ratio. Environment type should nevertheless by consistent
                    if ( getEnvironmentMapType() == CUBE_MAP 
                      || getEnvironmentMapType() == VERTICAL_CROSS_CUBE_MAP )
                    {
                        destW = Int32( width / 3.f + 0.5f);
                        destH = Int32(height / 4.f + 0.5f);
                        destD = Int32(depth);

                        offX = 2 * destW;  offY = 2 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_X]);
                        offX = 1 * destW;  offY = 3 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_Y]);
                        offX = 1 * destW;  offY = 2 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_Z]);
                        offX = 0 * destW;  offY = 2 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_X]);
                        offX = 1 * destW;  offY = 1 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_Y]);
                        offX = 1 * destW;  offY = 0 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_Z]);

                        mirror_horiz[POS_X] = true;  mirror_verti[POS_X] = true;
                        mirror_horiz[POS_Y] = false; mirror_verti[POS_Y] = false;
                        mirror_horiz[POS_Z] = true;  mirror_verti[POS_Z] = true;
                        mirror_horiz[NEG_X] = true;  mirror_verti[NEG_X] = true;
                        mirror_horiz[NEG_Y] = false; mirror_verti[NEG_Y] = false;
                        mirror_horiz[NEG_Z] = false; mirror_verti[NEG_Z] = false;
                    }
                }
                else
                if (osgAbs(ratio - 6.f/1.f) < 1.E-3)
                {
                    // Found Horizontal strip image. Environment type should nevertheless by consistent
                    if ( getEnvironmentMapType() == CUBE_MAP 
                      || getEnvironmentMapType() == HORIZONTAL_STRIP_CUBE_MAP )
                    {
                        destW = Int32( width / 6.f + 0.5f);
                        destH = Int32(height);
                        destD = Int32(depth);

                        offX = 0 * destW;  offY = 0 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_X]);
                        offX = 2 * destW;  offY = 0 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_Y]);
                        offX = 4 * destW;  offY = 0 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_Z]);
                        offX = 1 * destW;  offY = 0 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_X]);
                        offX = 3 * destW;  offY = 0 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_Y]);
                        offX = 5 * destW;  offY = 0 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_Z]);

                        mirror_horiz[POS_X] = true;  mirror_verti[POS_X] = true;
                        mirror_horiz[POS_Y] = false; mirror_verti[POS_Y] = false;
                        mirror_horiz[POS_Z] = true;  mirror_verti[POS_Z] = true;
                        mirror_horiz[NEG_X] = true;  mirror_verti[NEG_X] = true;
                        mirror_horiz[NEG_Y] = false; mirror_verti[NEG_Y] = false;
                        mirror_horiz[NEG_Z] = true;  mirror_verti[NEG_Z] = true;
                    }
                }
                else
                if (osgAbs(ratio - 1.f/6.f) < 1.E-3)
                {
                    // Found Vertical strip image. Environment type should nevertheless by consistent
                    if ( getEnvironmentMapType() == CUBE_MAP 
                      || getEnvironmentMapType() == VERTICAL_STRIP_CUBE_MAP)
                    {
                        destW = Int32( width);
                        destH = Int32(height / 6.f + 0.5f);
                        destD = Int32(depth);

                        offX = 0 * destW;  offY = 5 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_X]);
                        offX = 0 * destW;  offY = 3 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_Y]);
                        offX = 0 * destW;  offY = 1 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[POS_Z]);
                        offX = 0 * destW;  offY = 4 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_X]);
                        offX = 0 * destW;  offY = 2 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_Y]);
                        offX = 0 * destW;  offY = 0 * destH;  offZ = 0;  image->subImage(offX, offY, offZ, destW, destH, destD, images[NEG_Z]);

                        mirror_horiz[POS_X] = true;  mirror_verti[POS_X] = true;
                        mirror_horiz[POS_Y] = false; mirror_verti[POS_Y] = false;
                        mirror_horiz[POS_Z] = true;  mirror_verti[POS_Z] = true;
                        mirror_horiz[NEG_X] = true;  mirror_verti[NEG_X] = true;
                        mirror_horiz[NEG_Y] = false; mirror_verti[NEG_Y] = false;
                        mirror_horiz[NEG_Z] = true;  mirror_verti[NEG_Z] = true;
                    }
                }
            }

            for (UInt32 i = POS_X; i <= NEG_Z; ++i)
            {
                mirrorCubemapImages(static_cast<CubeMapSide>(i), images[i], mirrorFlags, mirror_horiz[i], mirror_verti[i]);

                if (imageMap)
                {
                    imageMap->insert(key[i], images[i]);
                }
            }
        }
    }

    // POS_Z and NEG_Z are exchanged, because we look into the negative z-direction in OpenGL
    ImageUnrecPtr imgTmp = images[POS_Z];
    images[POS_Z] = images[NEG_Z];
    images[NEG_Z] = imgTmp;

    return ( images[POS_X] != NULL && images[POS_Y] != NULL && images[POS_Z] != NULL
          && images[NEG_X] != NULL && images[NEG_Y] != NULL && images[NEG_Z] != NULL );
}

void TextureDesc::mirrorCubemapImages(
    CubeMapSide side, 
    Image* image, 
    UInt32 mirrorFlags,
    bool mirror_horiz, 
    bool mirror_verti) const
{
#ifdef OSG_TEXTUREDESC_CUBEMAP_WRITE_TEST_IMAGES
    switch (side)
    {
        case POS_X: if (image) image->write("d:/work/posx.hdr"); break;
        case POS_Y: if (image) image->write("d:/work/posy.hdr"); break;
        case POS_Z: if (image) image->write("d:/work/posz.hdr"); break;
        case NEG_X: if (image) image->write("d:/work/negx.hdr"); break;
        case NEG_Y: if (image) image->write("d:/work/negy.hdr"); break;
        case NEG_Z: if (image) image->write("d:/work/negz.hdr"); break;
    }
#endif

    switch (side)
    {
        case POS_X:
            mirror_horiz ^= ((mirrorFlags & MIRROR_HORIZONTAL_DIRECTION_POS_X) != 0);
            mirror_verti ^= ((mirrorFlags & MIRROR_VERTICAL_DIRECTION_POS_X  ) != 0);
            break;
        case POS_Y:
            mirror_horiz ^= ((mirrorFlags & MIRROR_HORIZONTAL_DIRECTION_POS_Y) != 0);
            mirror_verti ^= ((mirrorFlags & MIRROR_VERTICAL_DIRECTION_POS_Y  ) != 0);
            break;
        case POS_Z:
            mirror_horiz ^= ((mirrorFlags & MIRROR_HORIZONTAL_DIRECTION_POS_Z) != 0);
            mirror_verti ^= ((mirrorFlags & MIRROR_VERTICAL_DIRECTION_POS_Z  ) != 0);
            break;
        case NEG_X:
            mirror_horiz ^= ((mirrorFlags & MIRROR_HORIZONTAL_DIRECTION_NEG_X) != 0);
            mirror_verti ^= ((mirrorFlags & MIRROR_VERTICAL_DIRECTION_NEG_X  ) != 0);
            break;
        case NEG_Y:
            mirror_horiz ^= ((mirrorFlags & MIRROR_HORIZONTAL_DIRECTION_NEG_Y) != 0);
            mirror_verti ^= ((mirrorFlags & MIRROR_VERTICAL_DIRECTION_NEG_Y  ) != 0);
            break;
        case NEG_Z:
            mirror_horiz ^= ((mirrorFlags & MIRROR_HORIZONTAL_DIRECTION_NEG_Z) != 0);
            mirror_verti ^= ((mirrorFlags & MIRROR_VERTICAL_DIRECTION_NEG_Z  ) != 0);
            break;
    }

    if (image != NULL && (mirror_horiz || mirror_verti))
        image->mirror(mirror_horiz, mirror_verti);

#ifdef OSG_TEXTUREDESC_CUBEMAP_WRITE_TEST_IMAGES
    switch (side)
    {
        case POS_X: if (image) image->write("d:/work/posx_mirrored.hdr"); break;
        case POS_Y: if (image) image->write("d:/work/posy_mirrored.hdr"); break;
        case POS_Z: if (image) image->write("d:/work/posz_mirrored.hdr"); break;
        case NEG_X: if (image) image->write("d:/work/negx_mirrored.hdr"); break;
        case NEG_Y: if (image) image->write("d:/work/negy_mirrored.hdr"); break;
        case NEG_Z: if (image) image->write("d:/work/negz_mirrored.hdr"); break;
    }
#endif
}


Matrix TextureDesc::getMatrix() const
{
    UInt32 channel        = getUVChannel();
    bool   hasUVTransform = getHasUVTransform();
    Matrix uvTransform;

    if (hasUVTransform)
    {
        Vec2f  t = getTranslate();
        Vec2f  s = getScale();
        Real32 r = getRotate();

        Real32 tx = t.x();
        Real32 ty = t.y();
        Real32 tz = 0.f;

        Real32 sx = s.x();
        Real32 sy = s.y();
        Real32 sz = 1.f;

        Vec3f axis(0.f, 0.f, 1.f);

        Int32 intFraction = static_cast<Int32>(r / OSG::TwoPi);
        if (intFraction)
        {
            r -= intFraction * OSG::TwoPi;
        }
                
        if (r < 0.f)
            r += OSG::TwoPi;

        Quaternion rotation(axis, r);

        Matrix S, R, T;

        S.setScale(sx, sy, sz);
        R.setRotate(rotation);
        T.setTranslate(tx, ty, tz);

        uvTransform = S;
        uvTransform.mult(R);
        uvTransform.mult(T);
    }

    return uvTransform;
}

const Char8* TextureDesc::getTextureTypeName() const
{
    TextureType type = static_cast<TextureType>(getTextureType());

    switch (type)
    {
        case NONE_TEXTURE:                      return "NONE_TEXTURE";
        case UNKNOWN_TEXTURE:                   return "UNKNOWN_TEXTURE";
        case ALBEDO_TEXTURE:                    return "ALBEDO_TEXTURE";
        case SPECULAR_TEXTURE:                  return "SPECULAR_TEXTURE";
        case EMISSIVE_TEXTURE:                  return "EMISSIVE_TEXTURE";
        case SHININESS_TEXTURE:                 return "SHININESS_TEXTURE";
        case OPACITY_TEXTURE:                   return "OPACITY_TEXTURE";
        case NORMALS_TEXTURE:                   return "NORMALS_TEXTURE";
        case HEIGHT_TEXTURE:                    return "HEIGHT_TEXTURE";
        case DISPLACEMENT_TEXTURE:              return "DISPLACEMENT_TEXTURE";
        case REFLECTION_TEXTURE:                return "REFLECTION_TEXTURE";
        case REFRACTION_TEXTURE:                return "REFRACTION_TEXTURE";
        case ANISOTROPY_U_TEXTURE:              return "ANISOTROPY_U_TEXTURE";
        case ANISOTROPY_V_TEXTURE:              return "ANISOTROPY_V_TEXTURE";
        case ANISOTROPY_UV_TEXTURE:             return "ANISOTROPY_UV_TEXTURE";
        case AMBIENT_OCCLUSION_TEXTURE:         return "AMBIENT_OCCLUSION_TEXTURE";
        case ROUGH_TEXTURE:                     return "ROUGH_TEXTURE";
        case METAL_TEXTURE:                     return "METAL_TEXTURE";
        case ROUGH_METAL_TEXTURE:               return "ROUGH_METAL_TEXTURE";
        case OCCL_ROUGH_METAL_TEXTURE:          return "OCCL_ROUGH_METAL_TEXTURE";
        case IRRADIANCE_TEXTURE:                return "IRRADIANCE_TEXTURE";
        case PRE_FILTER_TEXTURE:                return "PRE_FILTER_TEXTURE";
        case BRDF_LUT_TEXTURE:                  return "BRDF_LUT_TEXTURE";
        case STANDARD_MATERIAL_TEXTURE:         return "STANDARD_MATERIAL_TEXTURE";
        default:                                return "foreign texture type";
    }
}

TextureDesc::SwizzleIndicesT TextureDesc::getSwizzleIndices() const
{
    SwizzleIndicesT indices;

    const std::string& swizzle = getSwizzle();

    const std::size_t channels = 4;

    OSG_ASSERT(swizzle.size() == channels);

    for (std::size_t i = 0; i < channels; ++i)
    {
        switch (swizzle[i])
        {
            case 'r': indices[i] = 0; break;
            case 'g': indices[i] = 1; break;
            case 'b': indices[i] = 2; break;
            case 'a': indices[i] = 3; break;
        }
    }

    return indices;
}

bool TextureDesc::equals(const TextureDesc& rhs) const
{
    if (isCubeMap() != rhs.isCubeMap())
        return false;

    if (isCubeMap())
    {
        for (int idx = POS_X; idx <= NEG_Z; ++idx)
        {
            CubeMapSide side = static_cast<CubeMapSide>(idx);
            if (   getFilename(side) != rhs.getFilename(side)
                || getTexImage(side) != rhs.getTexImage(side) ) return false;
        }
    }
    else
    {
        if (   getFilename() != rhs.getFilename()
            || getTexImage() != rhs.getTexImage() ) return false;
    }

    if (   getTextureType       () != rhs.getTextureType       ()
        || getSwizzle           () != rhs.getSwizzle           ()
        || getIsSRGBTexture     () != rhs.getIsSRGBTexture     ()
        || getTexUnit           () != rhs.getTexUnit           ()
        || getUVChannel         () != rhs.getUVChannel         ()
        || getMappingMode       () != rhs.getMappingMode       ()
        || getMapAxis           () != rhs.getMapAxis           ()
        || getEnvironmentMapType() != rhs.getEnvironmentMapType()
        || getBlendFactor       () != rhs.getBlendFactor       ()
        || getOperation         () != rhs.getOperation         ()
        || getWrapS             () != rhs.getWrapS             ()
        || getWrapT             () != rhs.getWrapT             ()
        || getWrapR             () != rhs.getWrapR             ()
        || getTextureFlags      () != rhs.getTextureFlags      ()
        || getMinFilter         () != rhs.getMinFilter         ()
        || getMagFilter         () != rhs.getMagFilter         ()
        || getInternalFormat    () != rhs.getInternalFormat    ()
        || getExternalFormat    () != rhs.getExternalFormat    ()
        || getAnisotropy        () != rhs.getAnisotropy        ()
        || getMirrorFlags       () != rhs.getMirrorFlags       ()
        || getHasUVTransform    () != rhs.getHasUVTransform    ()
        || getBorderColor       () != rhs.getBorderColor       () ) return false;

    if (getHasUVTransform())
    {
        if (   getScale    () != rhs.getScale    ()
            || getTranslate() != rhs.getTranslate()
            || getRotate   () != rhs.getRotate   () ) return false;
    }

    return true;
}

OSG_END_NAMESPACE
