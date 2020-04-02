/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGIMAGEFORMAT_H_
#define _OSGIMAGEFORMAT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGImageBase.h"
#include "OSGReal16.h"

OSG_BEGIN_NAMESPACE

/*! \brief ImageFormat class. See \ref PageSystemImage
    for a description.
    \ingroup GrpSystemImageObj
    \ingroup GrpLibOSGSystem
    \includebasedoc
*/

class OSG_SYSTEM_DLLMAPPING ImageFormat
{
public:
    enum Format
    {
        FORMAT_UNDEFINED = 0,

        FORMAT_RG4_UNORM_PACK8,
        FORMAT_RGBA4_UNORM_PACK16,
        FORMAT_BGRA4_UNORM_PACK16,
        FORMAT_R5G6B5_UNORM_PACK16,
        FORMAT_B5G6R5_UNORM_PACK16,
        FORMAT_RGB5A1_UNORM_PACK16,
        FORMAT_BGR5A1_UNORM_PACK16,
        FORMAT_A1RGB5_UNORM_PACK16,

        FORMAT_R8_UNORM_PACK8,
        FORMAT_R8_SNORM_PACK8,
        FORMAT_R8_USCALED_PACK8,
        FORMAT_R8_SSCALED_PACK8,
        FORMAT_R8_UINT_PACK8,
        FORMAT_R8_SINT_PACK8,
        FORMAT_R8_SRGB_PACK8,

        FORMAT_RG8_UNORM_PACK8,
        FORMAT_RG8_SNORM_PACK8,
        FORMAT_RG8_USCALED_PACK8,
        FORMAT_RG8_SSCALED_PACK8,
        FORMAT_RG8_UINT_PACK8,
        FORMAT_RG8_SINT_PACK8,
        FORMAT_RG8_SRGB_PACK8,

        FORMAT_RGB8_UNORM_PACK8,
        FORMAT_RGB8_SNORM_PACK8,
        FORMAT_RGB8_USCALED_PACK8,
        FORMAT_RGB8_SSCALED_PACK8,
        FORMAT_RGB8_UINT_PACK8,
        FORMAT_RGB8_SINT_PACK8,
        FORMAT_RGB8_SRGB_PACK8,

        FORMAT_BGR8_UNORM_PACK8,
        FORMAT_BGR8_SNORM_PACK8,
        FORMAT_BGR8_USCALED_PACK8,
        FORMAT_BGR8_SSCALED_PACK8,
        FORMAT_BGR8_UINT_PACK8,
        FORMAT_BGR8_SINT_PACK8,
        FORMAT_BGR8_SRGB_PACK8,

        FORMAT_RGBA8_UNORM_PACK8,
        FORMAT_RGBA8_SNORM_PACK8,
        FORMAT_RGBA8_USCALED_PACK8,
        FORMAT_RGBA8_SSCALED_PACK8,
        FORMAT_RGBA8_UINT_PACK8,
        FORMAT_RGBA8_SINT_PACK8,
        FORMAT_RGBA8_SRGB_PACK8,

        FORMAT_BGRA8_UNORM_PACK8,
        FORMAT_BGRA8_SNORM_PACK8,
        FORMAT_BGRA8_USCALED_PACK8,
        FORMAT_BGRA8_SSCALED_PACK8,
        FORMAT_BGRA8_UINT_PACK8,
        FORMAT_BGRA8_SINT_PACK8,
        FORMAT_BGRA8_SRGB_PACK8,

        FORMAT_RGBA8_UNORM_PACK32,
        FORMAT_RGBA8_SNORM_PACK32,
        FORMAT_RGBA8_USCALED_PACK32,
        FORMAT_RGBA8_SSCALED_PACK32,
        FORMAT_RGBA8_UINT_PACK32,
        FORMAT_RGBA8_SINT_PACK32,
        FORMAT_RGBA8_SRGB_PACK32,

        FORMAT_RGB10A2_UNORM_PACK32,
        FORMAT_RGB10A2_SNORM_PACK32,
        FORMAT_RGB10A2_USCALED_PACK32,
        FORMAT_RGB10A2_SSCALED_PACK32,
        FORMAT_RGB10A2_UINT_PACK32,
        FORMAT_RGB10A2_SINT_PACK32,

        FORMAT_BGR10A2_UNORM_PACK32,
        FORMAT_BGR10A2_SNORM_PACK32,
        FORMAT_BGR10A2_USCALED_PACK32,
        FORMAT_BGR10A2_SSCALED_PACK32,
        FORMAT_BGR10A2_UINT_PACK32,
        FORMAT_BGR10A2_SINT_PACK32,

        FORMAT_R16_UNORM_PACK16,
        FORMAT_R16_SNORM_PACK16,
        FORMAT_R16_USCALED_PACK16,
        FORMAT_R16_SSCALED_PACK16,
        FORMAT_R16_UINT_PACK16,
        FORMAT_R16_SINT_PACK16,
        FORMAT_R16_SFLOAT_PACK16,

        FORMAT_RG16_UNORM_PACK16,
        FORMAT_RG16_SNORM_PACK16,
        FORMAT_RG16_USCALED_PACK16,
        FORMAT_RG16_SSCALED_PACK16,
        FORMAT_RG16_UINT_PACK16,
        FORMAT_RG16_SINT_PACK16,
        FORMAT_RG16_SFLOAT_PACK16,

        FORMAT_RGB16_UNORM_PACK16,
        FORMAT_RGB16_SNORM_PACK16,
        FORMAT_RGB16_USCALED_PACK16,
        FORMAT_RGB16_SSCALED_PACK16,
        FORMAT_RGB16_UINT_PACK16,
        FORMAT_RGB16_SINT_PACK16,
        FORMAT_RGB16_SFLOAT_PACK16,

        FORMAT_RGBA16_UNORM_PACK16,
        FORMAT_RGBA16_SNORM_PACK16,
        FORMAT_RGBA16_USCALED_PACK16,
        FORMAT_RGBA16_SSCALED_PACK16,
        FORMAT_RGBA16_UINT_PACK16,
        FORMAT_RGBA16_SINT_PACK16,
        FORMAT_RGBA16_SFLOAT_PACK16,

        FORMAT_R32_UINT_PACK32,
        FORMAT_R32_SINT_PACK32,
        FORMAT_R32_SFLOAT_PACK32,

        FORMAT_RG32_UINT_PACK32,
        FORMAT_RG32_SINT_PACK32,
        FORMAT_RG32_SFLOAT_PACK32,

        FORMAT_RGB32_UINT_PACK32,
        FORMAT_RGB32_SINT_PACK32,
        FORMAT_RGB32_SFLOAT_PACK32,

        FORMAT_RGBA32_UINT_PACK32,
        FORMAT_RGBA32_SINT_PACK32,
        FORMAT_RGBA32_SFLOAT_PACK32,

        FORMAT_R64_UINT_PACK64,
        FORMAT_R64_SINT_PACK64,
        FORMAT_R64_SFLOAT_PACK64,

        FORMAT_RG64_UINT_PACK64,
        FORMAT_RG64_SINT_PACK64,
        FORMAT_RG64_SFLOAT_PACK64,

        FORMAT_RGB64_UINT_PACK64,
        FORMAT_RGB64_SINT_PACK64,
        FORMAT_RGB64_SFLOAT_PACK64,

        FORMAT_RGBA64_UINT_PACK64,
        FORMAT_RGBA64_SINT_PACK64,
        FORMAT_RGBA64_SFLOAT_PACK64,

        FORMAT_RG11B10_UFLOAT_PACK32,
        FORMAT_RGB9E5_UFLOAT_PACK32,

        FORMAT_D16_UNORM_PACK16,
        FORMAT_D24_UNORM_PACK32,
        FORMAT_D32_SFLOAT_PACK32,
        FORMAT_S8_UINT_PACK8,
        FORMAT_D16_UNORM_S8_UINT_PACK32,
        FORMAT_D24_UNORM_S8_UINT_PACK32,
        FORMAT_D32_SFLOAT_S8_UINT_PACK64,

        FORMAT_RGB_DXT1_UNORM_BLOCK8,
        FORMAT_RGB_DXT1_SRGB_BLOCK8,
        FORMAT_RGBA_DXT1_UNORM_BLOCK8,
        FORMAT_RGBA_DXT1_SRGB_BLOCK8,
        FORMAT_RGBA_DXT3_UNORM_BLOCK16,
        FORMAT_RGBA_DXT3_SRGB_BLOCK16,
        FORMAT_RGBA_DXT5_UNORM_BLOCK16,
        FORMAT_RGBA_DXT5_SRGB_BLOCK16,
        FORMAT_R_ATI1N_UNORM_BLOCK8,
        FORMAT_R_ATI1N_SNORM_BLOCK8,
        FORMAT_RG_ATI2N_UNORM_BLOCK16,
        FORMAT_RG_ATI2N_SNORM_BLOCK16,
        FORMAT_RGB_BP_UFLOAT_BLOCK16,
        FORMAT_RGB_BP_SFLOAT_BLOCK16,
        FORMAT_RGBA_BP_UNORM_BLOCK16,
        FORMAT_RGBA_BP_SRGB_BLOCK16,

        FORMAT_RGB_ETC2_UNORM_BLOCK8,
        FORMAT_RGB_ETC2_SRGB_BLOCK8,
        FORMAT_RGBA_ETC2_UNORM_BLOCK8,
        FORMAT_RGBA_ETC2_SRGB_BLOCK8,
        FORMAT_RGBA_ETC2_UNORM_BLOCK16,
        FORMAT_RGBA_ETC2_SRGB_BLOCK16,
        FORMAT_R_EAC_UNORM_BLOCK8,
        FORMAT_R_EAC_SNORM_BLOCK8,
        FORMAT_RG_EAC_UNORM_BLOCK16,
        FORMAT_RG_EAC_SNORM_BLOCK16,

        FORMAT_RGBA_ASTC_4X4_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_4X4_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_5X4_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_5X4_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_5X5_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_5X5_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_6X5_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_6X5_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_6X6_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_6X6_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_8X5_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_8X5_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_8X6_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_8X6_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_8X8_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_8X8_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_10X5_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_10X5_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_10X6_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_10X6_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_10X8_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_10X8_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_10X10_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_10X10_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_12X10_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_12X10_SRGB_BLOCK16,
        FORMAT_RGBA_ASTC_12X12_UNORM_BLOCK16,
        FORMAT_RGBA_ASTC_12X12_SRGB_BLOCK16,

        FORMAT_RGB_PVRTC1_8X8_UNORM_BLOCK32,
        FORMAT_RGB_PVRTC1_8X8_SRGB_BLOCK32,
        FORMAT_RGB_PVRTC1_16X8_UNORM_BLOCK32,
        FORMAT_RGB_PVRTC1_16X8_SRGB_BLOCK32,
        FORMAT_RGBA_PVRTC1_8X8_UNORM_BLOCK32,
        FORMAT_RGBA_PVRTC1_8X8_SRGB_BLOCK32,
        FORMAT_RGBA_PVRTC1_16X8_UNORM_BLOCK32,
        FORMAT_RGBA_PVRTC1_16X8_SRGB_BLOCK32,
        FORMAT_RGBA_PVRTC2_4X4_UNORM_BLOCK8,
        FORMAT_RGBA_PVRTC2_4X4_SRGB_BLOCK8,
        FORMAT_RGBA_PVRTC2_8X4_UNORM_BLOCK8,
        FORMAT_RGBA_PVRTC2_8X4_SRGB_BLOCK8,

        FORMAT_RGB_ETC_UNORM_BLOCK8,
        FORMAT_RGB_ATC_UNORM_BLOCK8,
        FORMAT_RGBA_ATCA_UNORM_BLOCK16,
        FORMAT_RGBA_ATCI_UNORM_BLOCK16,

        FORMAT_L8_UNORM_PACK8,
        FORMAT_A8_UNORM_PACK8,
        FORMAT_LA8_UNORM_PACK8,
        FORMAT_L16_UNORM_PACK16,
        FORMAT_A16_UNORM_PACK16,
        FORMAT_LA16_UNORM_PACK16,

        FORMAT_BGR8_UNORM_PACK32,
        FORMAT_BGR8_SRGB_PACK32,

        FORMAT_RG3B2_UNORM_PACK8, 

        FORMAT_FIRST = FORMAT_RG4_UNORM_PACK8,
        FORMAT_LAST  = FORMAT_RG3B2_UNORM_PACK8
    };

    enum Swizzle
    {
        SWIZZLE_FIRST         = 0,
        SWIZZLE_CHANNEL_FIRST = 0,

        SWIZZLE_RED           = SWIZZLE_FIRST,
        SWIZZLE_GREEN,
        SWIZZLE_BLUE,
        SWIZZLE_ALPHA,
        SWIZZLE_ZERO,
        SWIZZLE_ONE,

        SWIZZLE_CHANNEL_LAST  = SWIZZLE_ALPHA,
        SWIZZLE_LAST          = SWIZZLE_ONE
    };

    struct FormatInfo
    {
        UInt8    blockSize;
        Vec3ub   blockExtent;
        UInt8    component;
        Vec4ub   swizzles;
        UInt16   flags;
    };

public:
    static const FormatInfo&    getFormatInfo(Format format);

    static bool                 IsValid                 (Format format);
    static bool                 IsCompressed            (Format format);
    static bool                 IsS3TcCompressed        (Format format);
    static bool                 IsSRGB                  (Format format);
    static UInt8                getBlockSize            (Format format);
    static const Vec3ub&        getBlockExtent          (Format format);
    static UInt8                getComponentCount       (Format format);
    static bool                 IsUnsigned              (Format format);
    static bool                 IsSigned                (Format format);
    static bool                 IsInteger               (Format format);
    static bool                 IsSignedInteger         (Format format);
    static bool                 IsUnsignedInteger       (Format format);
    static bool                 IsFloat                 (Format format);
    static bool                 IsNormalized            (Format format);
    static bool                 IsUNorm                 (Format format);
    static bool                 IsSNorm                 (Format format);
    static bool                 IsPacked                (Format format);
    static bool                 IsDepth                 (Format format);
    static bool                 IsStencil               (Format format);
    static bool                 IsDepthStencil          (Format format);
    static UInt32               getBitsPerPixel         (Format format);
    static Vec4ub               getSwizzle              (Format format);

    static bool                 IsChannel               (Swizzle swizzle);

public:

    enum
    {
        FORMAT_INVALID = -1,
        FORMAT_COUNT   =  FORMAT_LAST + 1,
        SWIZZLE_COUNT  = SWIZZLE_LAST - SWIZZLE_FIRST + 1
    };

    enum FormatProperty
    {
        FORMAT_PROPERTY_BGRA_FORMAT_BIT = (1 << 0),
	FORMAT_PROPERTY_BGRA_TYPE_BIT   = (1 << 1)
    };

    enum Capabilities
    {
        CAP_COMPRESSED_BIT      = (1 << 0),
        CAP_COLORSPACE_SRGB_BIT = (1 << 1),
        CAP_NORMALIZED_BIT      = (1 << 2),
        CAP_SCALED_BIT          = (1 << 3),
        CAP_UNSIGNED_BIT        = (1 << 4),
        CAP_SIGNED_BIT          = (1 << 5),
        CAP_INTEGER_BIT         = (1 << 6),
        CAP_FLOAT_BIT           = (1 << 7),
        CAP_DEPTH_BIT           = (1 << 8),
        CAP_STENCIL_BIT         = (1 << 9),
        CAP_SWIZZLE_BIT         = (1 << 10),
        CAP_LUMINANCE_ALPHA_BIT = (1 << 11),
        CAP_PACKED8_BIT         = (1 << 12),
        CAP_PACKED16_BIT        = (1 << 13),
        CAP_PACKED32_BIT        = (1 << 14),
        CAP_DDS_GLI_EXT_BIT     = (1 << 15)
    };

    enum GlTypeFormat
    {
        OGL_TYPE_NONE                = 0,       //GL_NONE
        OGL_TYPE_I8                  = 0x1400,  //GL_BYTE
        OGL_TYPE_U8                  = 0x1401,  //GL_UNSIGNED_BYTE
        OGL_TYPE_I16                 = 0x1402,  //GL_SHORT
        OGL_TYPE_U16                 = 0x1403,  //GL_UNSIGNED_SHORT
        OGL_TYPE_I32                 = 0x1404,  //GL_INT
        OGL_TYPE_U32                 = 0x1405,  //GL_UNSIGNED_INT
        OGL_TYPE_I64                 = 0x140E,  //GL_INT64_ARB
        OGL_TYPE_U64                 = 0x140F,  //GL_UNSIGNED_INT64_ARB
        OGL_TYPE_F16                 = 0x140B,  //GL_HALF_FLOAT
        OGL_TYPE_F16_OES             = 0x8D61,  //GL_HALF_FLOAT_OES
        OGL_TYPE_F32                 = 0x1406,  //GL_FLOAT
        OGL_TYPE_F64                 = 0x140A,  //GL_DOUBLE
        OGL_TYPE_UINT32_RGB9_E5_REV  = 0x8C3E,  //GL_UNSIGNED_INT_5_9_9_9_REV
        OGL_TYPE_UINT32_RG11B10F_REV = 0x8C3B,  //GL_UNSIGNED_INT_10F_11F_11F_REV
        OGL_TYPE_UINT8_RG3B2         = 0x8032,  //GL_UNSIGNED_BYTE_3_3_2
        OGL_TYPE_UINT8_RG3B2_REV     = 0x8362,  //GL_UNSIGNED_BYTE_2_3_3_REV
        OGL_TYPE_UINT16_RGB5A1       = 0x8034,  //GL_UNSIGNED_SHORT_5_5_5_1
        OGL_TYPE_UINT16_RGB5A1_REV   = 0x8366,  //GL_UNSIGNED_SHORT_1_5_5_5_REV
        OGL_TYPE_UINT16_R5G6B5       = 0x8363,  //GL_UNSIGNED_SHORT_5_6_5
        OGL_TYPE_UINT16_R5G6B5_REV   = 0x8364,  //GL_UNSIGNED_SHORT_5_6_5_REV
        OGL_TYPE_UINT16_RGBA4        = 0x8033,  //GL_UNSIGNED_SHORT_4_4_4_4
        OGL_TYPE_UINT16_RGBA4_REV    = 0x8365,  //GL_UNSIGNED_SHORT_4_4_4_4_REV
        OGL_TYPE_UINT32_RGBA8        = 0x8035,  //GL_UNSIGNED_SHORT_8_8_8_8
        OGL_TYPE_UINT32_RGBA8_REV    = 0x8367,  //GL_UNSIGNED_SHORT_8_8_8_8_REV
        OGL_TYPE_UINT32_RGB10A2      = 0x8036,  //GL_UNSIGNED_INT_10_10_10_2
        OGL_TYPE_UINT32_RGB10A2_REV  = 0x8368,  //GL_UNSIGNED_INT_2_10_10_10_REV

        OGL_TYPE_UINT8_RG4_REV_GTC   = 0xFFFD,
        OGL_TYPE_UINT16_A1RGB5_GTC   = 0xFFFC
    };

    enum GlInternalFormat
    {
        OGL_INTERNAL_NONE                            = 0,       //GL_NONE

        OGL_INTERNAL_RGB_UNORM                       = 0x1907,  //GL_RGB
        OGL_INTERNAL_BGR_UNORM                       = 0x80E0,  //GL_BGR
        OGL_INTERNAL_RGBA_UNORM                      = 0x1908,  //GL_RGBA
        OGL_INTERNAL_BGRA_UNORM                      = 0x80E1,  //GL_BGRA
        OGL_INTERNAL_BGRA8_UNORM                     = 0x93A1,  //GL_BGRA8_EXT

        // unorm formats
        OGL_INTERNAL_R8_UNORM                        = 0x8229,  //GL_R8
        OGL_INTERNAL_RG8_UNORM                       = 0x822B,  //GL_RG8
        OGL_INTERNAL_RGB8_UNORM                      = 0x8051,  //GL_RGB8
        OGL_INTERNAL_RGBA8_UNORM                     = 0x8058,  //GL_RGBA8

        OGL_INTERNAL_R16_UNORM                       = 0x822A,  //GL_R16
        OGL_INTERNAL_RG16_UNORM                      = 0x822C,  //GL_RG16
        OGL_INTERNAL_RGB16_UNORM                     = 0x8054,  //GL_RGB16
        OGL_INTERNAL_RGBA16_UNORM                    = 0x805B,  //GL_RGBA16

        OGL_INTERNAL_RGB10A2_UNORM                   = 0x8059,  //GL_RGB10_A2
        OGL_INTERNAL_RGB10A2_SNORM_EXT               = 0xFFFC,

        // snorm formats
        OGL_INTERNAL_R8_SNORM                        = 0x8F94,  //GL_R8_SNORM
        OGL_INTERNAL_RG8_SNORM                       = 0x8F95,  //GL_RG8_SNORM
        OGL_INTERNAL_RGB8_SNORM                      = 0x8F96,  //GL_RGB8_SNORM
        OGL_INTERNAL_RGBA8_SNORM                     = 0x8F97,  //GL_RGBA8_SNORM

        OGL_INTERNAL_R16_SNORM                       = 0x8F98,  //GL_R16_SNORM
        OGL_INTERNAL_RG16_SNORM                      = 0x8F99,  //GL_RG16_SNORM
        OGL_INTERNAL_RGB16_SNORM                     = 0x8F9A,  //GL_RGB16_SNORM
        OGL_INTERNAL_RGBA16_SNORM                    = 0x8F9B,  //GL_RGBA16_SNORM

        // unsigned integer formats
        OGL_INTERNAL_R8U                             = 0x8232,  //GL_R8UI
        OGL_INTERNAL_RG8U                            = 0x8238,  //GL_RG8UI
        OGL_INTERNAL_RGB8U                           = 0x8D7D,  //GL_RGB8UI
        OGL_INTERNAL_RGBA8U                          = 0x8D7C,  //GL_RGBA8UI

        OGL_INTERNAL_R16U                            = 0x8234,  //GL_R16UI
        OGL_INTERNAL_RG16U                           = 0x823A,  //GL_RG16UI
        OGL_INTERNAL_RGB16U                          = 0x8D77,  //GL_RGB16UI
        OGL_INTERNAL_RGBA16U                         = 0x8D76,  //GL_RGBA16UI

        OGL_INTERNAL_R32U                            = 0x8236,  //GL_R32UI
        OGL_INTERNAL_RG32U                           = 0x823C,  //GL_RG32UI
        OGL_INTERNAL_RGB32U                          = 0x8D71,  //GL_RGB32UI
        OGL_INTERNAL_RGBA32U                         = 0x8D70,  //GL_RGBA32UI

        OGL_INTERNAL_RGB10A2U                        = 0x906F,  //GL_RGB10_A2UI
        OGL_INTERNAL_RGB10A2I_EXT                    = 0xFFFB,

        // signed integer formats
        OGL_INTERNAL_R8I                             = 0x8231,  //GL_R8I
        OGL_INTERNAL_RG8I                            = 0x8237,  //GL_RG8I
        OGL_INTERNAL_RGB8I                           = 0x8D8F,  //GL_RGB8I
        OGL_INTERNAL_RGBA8I                          = 0x8D8E,  //GL_RGBA8I

        OGL_INTERNAL_R16I                            = 0x8233,  //GL_R16I
        OGL_INTERNAL_RG16I                           = 0x8239,  //GL_RG16I
        OGL_INTERNAL_RGB16I                          = 0x8D89,  //GL_RGB16I
        OGL_INTERNAL_RGBA16I                         = 0x8D88,  //GL_RGBA16I

        OGL_INTERNAL_R32I                            = 0x8235,  //GL_R32I
        OGL_INTERNAL_RG32I                           = 0x823B,  //GL_RG32I
        OGL_INTERNAL_RGB32I                          = 0x8D83,  //GL_RGB32I
        OGL_INTERNAL_RGBA32I                         = 0x8D82,  //GL_RGBA32I

        // Floating formats
        OGL_INTERNAL_R16F                            = 0x822D,  //GL_R16F
        OGL_INTERNAL_RG16F                           = 0x822F,  //GL_RG16F
        OGL_INTERNAL_RGB16F                          = 0x881B,  //GL_RGB16F
        OGL_INTERNAL_RGBA16F                         = 0x881A,  //GL_RGBA16F

        OGL_INTERNAL_R32F                            = 0x822E,  //GL_R32F
        OGL_INTERNAL_RG32F                           = 0x8230,  //GL_RG32F
        OGL_INTERNAL_RGB32F                          = 0x8815,  //GL_RGB32F
        OGL_INTERNAL_RGBA32F                         = 0x8814,  //GL_RGBA32F

        OGL_INTERNAL_R64F_EXT                        = 0xFFFA,  //GL_R64F
        OGL_INTERNAL_RG64F_EXT                       = 0xFFF9,  //GL_RG64F
        OGL_INTERNAL_RGB64F_EXT                      = 0xFFF8,  //GL_RGB64F
        OGL_INTERNAL_RGBA64F_EXT                     = 0xFFF7,  //GL_RGBA64F

        // sRGB formats
        OGL_INTERNAL_SR8                             = 0x8FBD,  //GL_SR8_EXT
        OGL_INTERNAL_SRG8                            = 0x8FBE,  //GL_SRG8_EXT
        OGL_INTERNAL_SRGB8                           = 0x8C41,  //GL_SRGB8
        OGL_INTERNAL_SRGB8_ALPHA8                    = 0x8C43,  //GL_SRGB8_ALPHA8

        // Packed formats
        OGL_INTERNAL_RGB9E5                          = 0x8C3D,  //GL_RGB9_E5
        OGL_INTERNAL_RG11B10F                        = 0x8C3A,  //GL_R11F_G11F_B10F
        OGL_INTERNAL_RG3B2                           = 0x2A10,  //GL_R3_G3_B2
        OGL_INTERNAL_R5G6B5                          = 0x8D62,  //GL_RGB565
        OGL_INTERNAL_RGB5A1                          = 0x8057,  //GL_RGB5_A1
        OGL_INTERNAL_RGBA4                           = 0x8056,  //GL_RGBA4

        OGL_INTERNAL_RG4_EXT                         = 0xFFFE,

        // Luminance Alpha formats
        OGL_INTERNAL_LA4                             = 0x8043,  //GL_LUMINANCE4_ALPHA4
        OGL_INTERNAL_L8                              = 0x8040,  //GL_LUMINANCE8
        OGL_INTERNAL_A8                              = 0x803C,  //GL_ALPHA8
        OGL_INTERNAL_LA8                             = 0x8045,  //GL_LUMINANCE8_ALPHA8
        OGL_INTERNAL_L16                             = 0x8042,  //GL_LUMINANCE16
        OGL_INTERNAL_A16                             = 0x803E,  //GL_ALPHA16
        OGL_INTERNAL_LA16                            = 0x8048,  //GL_LUMINANCE16_ALPHA16

        // Depth formats
        OGL_INTERNAL_D16                             = 0x81A5,  //GL_DEPTH_COMPONENT16
        OGL_INTERNAL_D24                             = 0x81A6,  //GL_DEPTH_COMPONENT24
        OGL_INTERNAL_D16S8_EXT                       = 0xFFF6,
        OGL_INTERNAL_D24S8                           = 0x88F0,  //GL_DEPTH24_STENCIL8
        OGL_INTERNAL_D32                             = 0x81A7,  //GL_DEPTH_COMPONENT32
        OGL_INTERNAL_D32F                            = 0x8CAC,  //GL_DEPTH_COMPONENT32F
        OGL_INTERNAL_D32FS8X24                       = 0x8CAD,  //GL_DEPTH32F_STENCIL8
        OGL_INTERNAL_S8_EXT                          = 0x8D48,  //GL_STENCIL_INDEX8

        // Compressed formats
        OGL_INTERNAL_RGB_DXT1                        = 0x83F0,  //GL_COMPRESSED_RGB_S3TC_DXT1_EXT
        OGL_INTERNAL_RGBA_DXT1                       = 0x83F1,  //GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
        OGL_INTERNAL_RGBA_DXT3                       = 0x83F2,  //GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
        OGL_INTERNAL_RGBA_DXT5                       = 0x83F3,  //GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
        OGL_INTERNAL_R_ATI1N_UNORM                   = 0x8DBB,  //GL_COMPRESSED_RED_RGTC1
        OGL_INTERNAL_R_ATI1N_SNORM                   = 0x8DBC,  //GL_COMPRESSED_SIGNED_RED_RGTC1
        OGL_INTERNAL_RG_ATI2N_UNORM                  = 0x8DBD,  //GL_COMPRESSED_RG_RGTC2
        OGL_INTERNAL_RG_ATI2N_SNORM                  = 0x8DBE,  //GL_COMPRESSED_SIGNED_RG_RGTC2
        OGL_INTERNAL_RGB_BP_UNSIGNED_FLOAT           = 0x8E8F,  //GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT
        OGL_INTERNAL_RGB_BP_SIGNED_FLOAT             = 0x8E8E,  //GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT
        OGL_INTERNAL_RGB_BP_UNORM                    = 0x8E8C,  //GL_COMPRESSED_RGBA_BPTC_UNORM
        OGL_INTERNAL_RGB_PVRTC_4BPPV1                = 0x8C00,  //GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG
        OGL_INTERNAL_RGB_PVRTC_2BPPV1                = 0x8C01,  //GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
        OGL_INTERNAL_RGBA_PVRTC_4BPPV1               = 0x8C02,  //GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG
        OGL_INTERNAL_RGBA_PVRTC_2BPPV1               = 0x8C03,  //GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG
        OGL_INTERNAL_RGBA_PVRTC_4BPPV2               = 0x9137,  //GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG
        OGL_INTERNAL_RGBA_PVRTC_2BPPV2               = 0x9138,  //GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG
        OGL_INTERNAL_ATC_RGB                         = 0x8C92,  //GL_ATC_RGB_AMD
        OGL_INTERNAL_ATC_RGBA_EXPLICIT_ALPHA         = 0x8C93,  //GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
        OGL_INTERNAL_ATC_RGBA_INTERPOLATED_ALPHA     = 0x87EE,  //GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD

        OGL_INTERNAL_RGB_ETC                         = 0x8D64,  //GL_COMPRESSED_RGB8_ETC1
        OGL_INTERNAL_RGB_ETC2                        = 0x9274,  //GL_COMPRESSED_RGB8_ETC2
        OGL_INTERNAL_RGBA_PUNCHTHROUGH_ETC2          = 0x9276,  //GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2
        OGL_INTERNAL_RGBA_ETC2                       = 0x9278,  //GL_COMPRESSED_RGBA8_ETC2_EAC
        OGL_INTERNAL_R11_EAC                         = 0x9270,  //GL_COMPRESSED_R11_EAC
        OGL_INTERNAL_SIGNED_R11_EAC                  = 0x9271,  //GL_COMPRESSED_SIGNED_R11_EAC
        OGL_INTERNAL_RG11_EAC                        = 0x9272,  //GL_COMPRESSED_RG11_EAC
        OGL_INTERNAL_SIGNED_RG11_EAC                 = 0x9273,  //GL_COMPRESSED_SIGNED_RG11_EAC

        OGL_INTERNAL_RGBA_ASTC_4x4                   = 0x93B0,  //GL_COMPRESSED_RGBA_ASTC_4x4_KHR
        OGL_INTERNAL_RGBA_ASTC_5x4                   = 0x93B1,  //GL_COMPRESSED_RGBA_ASTC_5x4_KHR
        OGL_INTERNAL_RGBA_ASTC_5x5                   = 0x93B2,  //GL_COMPRESSED_RGBA_ASTC_5x5_KHR
        OGL_INTERNAL_RGBA_ASTC_6x5                   = 0x93B3,  //GL_COMPRESSED_RGBA_ASTC_6x5_KHR
        OGL_INTERNAL_RGBA_ASTC_6x6                   = 0x93B4,  //GL_COMPRESSED_RGBA_ASTC_6x6_KHR
        OGL_INTERNAL_RGBA_ASTC_8x5                   = 0x93B5,  //GL_COMPRESSED_RGBA_ASTC_8x5_KHR
        OGL_INTERNAL_RGBA_ASTC_8x6                   = 0x93B6,  //GL_COMPRESSED_RGBA_ASTC_8x6_KHR
        OGL_INTERNAL_RGBA_ASTC_8x8                   = 0x93B7,  //GL_COMPRESSED_RGBA_ASTC_8x8_KHR
        OGL_INTERNAL_RGBA_ASTC_10x5                  = 0x93B8,  //GL_COMPRESSED_RGBA_ASTC_10x5_KHR
        OGL_INTERNAL_RGBA_ASTC_10x6                  = 0x93B9,  //GL_COMPRESSED_RGBA_ASTC_10x6_KHR
        OGL_INTERNAL_RGBA_ASTC_10x8                  = 0x93BA,  //GL_COMPRESSED_RGBA_ASTC_10x8_KHR
        OGL_INTERNAL_RGBA_ASTC_10x10                 = 0x93BB,  //GL_COMPRESSED_RGBA_ASTC_10x10_KHR
        OGL_INTERNAL_RGBA_ASTC_12x10                 = 0x93BC,  //GL_COMPRESSED_RGBA_ASTC_12x10_KHR
        OGL_INTERNAL_RGBA_ASTC_12x12                 = 0x93BD,  //GL_COMPRESSED_RGBA_ASTC_12x12_KHR

        // sRGB formats
        OGL_INTERNAL_SRGB_DXT1                       = 0x8C4C,  //GL_COMPRESSED_SRGB_S3TC_DXT1_EXT
        OGL_INTERNAL_SRGB_ALPHA_DXT1                 = 0x8C4D,  //GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT
        OGL_INTERNAL_SRGB_ALPHA_DXT3                 = 0x8C4E,  //GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT
        OGL_INTERNAL_SRGB_ALPHA_DXT5                 = 0x8C4F,  //GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT
        OGL_INTERNAL_SRGB_BP_UNORM                   = 0x8E8D,  //GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM
        OGL_INTERNAL_SRGB_PVRTC_2BPPV1               = 0x8A54,  //GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT
        OGL_INTERNAL_SRGB_PVRTC_4BPPV1               = 0x8A55,  //GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT
        OGL_INTERNAL_SRGB_ALPHA_PVRTC_2BPPV1         = 0x8A56,  //GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT
        OGL_INTERNAL_SRGB_ALPHA_PVRTC_4BPPV1         = 0x8A57,  //GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT
        OGL_INTERNAL_SRGB_ALPHA_PVRTC_2BPPV2         = 0x93F0,  //GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG
        OGL_INTERNAL_SRGB_ALPHA_PVRTC_4BPPV2         = 0x93F1,  //GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG
        OGL_INTERNAL_SRGB8_ETC2                      = 0x9275,  //GL_COMPRESSED_SRGB8_ETC2
        OGL_INTERNAL_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2  = 0x9277,  //GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2
        OGL_INTERNAL_SRGB8_ALPHA8_ETC2_EAC           = 0x9279,  //GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_4x4           = 0x93D0,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_5x4           = 0x93D1,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_5x5           = 0x93D2,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_6x5           = 0x93D3,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_6x6           = 0x93D4,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_8x5           = 0x93D5,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_8x6           = 0x93D6,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_8x8           = 0x93D7,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_10x5          = 0x93D8,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_10x6          = 0x93D9,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_10x8          = 0x93DA,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_10x10         = 0x93DB,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_12x10         = 0x93DC,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR
        OGL_INTERNAL_SRGB8_ALPHA8_ASTC_12x12         = 0x93DD,  //GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR

        OGL_INTERNAL_ALPHA8                          = 0x803C,
        OGL_INTERNAL_ALPHA16                         = 0x803E,
        OGL_INTERNAL_LUMINANCE8                      = 0x8040,
        OGL_INTERNAL_LUMINANCE16                     = 0x8042,
        OGL_INTERNAL_LUMINANCE8_ALPHA8               = 0x8045,
        OGL_INTERNAL_LUMINANCE16_ALPHA16             = 0x8048,

        OGL_INTERNAL_R8_USCALED_GTC                  = 0xF000,
        OGL_INTERNAL_R8_SSCALED_GTC,
        OGL_INTERNAL_RG8_USCALED_GTC,
        OGL_INTERNAL_RG8_SSCALED_GTC,
        OGL_INTERNAL_RGB8_USCALED_GTC,
        OGL_INTERNAL_RGB8_SSCALED_GTC,
        OGL_INTERNAL_RGBA8_USCALED_GTC,
        OGL_INTERNAL_RGBA8_SSCALED_GTC,
        OGL_INTERNAL_RGB10A2_USCALED_GTC,
        OGL_INTERNAL_RGB10A2_SSCALED_GTC,
        OGL_INTERNAL_R16_USCALED_GTC,
        OGL_INTERNAL_R16_SSCALED_GTC,
        OGL_INTERNAL_RG16_USCALED_GTC,
        OGL_INTERNAL_RG16_SSCALED_GTC,
        OGL_INTERNAL_RGB16_USCALED_GTC,
        OGL_INTERNAL_RGB16_SSCALED_GTC,
        OGL_INTERNAL_RGBA16_USCALED_GTC,
        OGL_INTERNAL_RGBA16_SSCALED_GTC,
    };

    enum GlExternalFormat
    {
        OGL_EXTERNAL_NONE            = 0,       //GL_NONE
        OGL_EXTERNAL_RED             = 0x1903,  //GL_RED
        OGL_EXTERNAL_RG              = 0x8227,  //GL_RG
        OGL_EXTERNAL_RGB             = 0x1907,  //GL_RGB
        OGL_EXTERNAL_BGR             = 0x80E0,  //GL_BGR
        OGL_EXTERNAL_RGBA            = 0x1908,  //GL_RGBA
        OGL_EXTERNAL_BGRA            = 0x80E1,  //GL_BGRA
        OGL_EXTERNAL_RED_INTEGER     = 0x8D94,  //GL_RED_INTEGER
        OGL_EXTERNAL_RG_INTEGER      = 0x8228,  //GL_RG_INTEGER
        OGL_EXTERNAL_RGB_INTEGER     = 0x8D98,  //GL_RGB_INTEGER
        OGL_EXTERNAL_BGR_INTEGER     = 0x8D9A,  //GL_BGR_INTEGER
        OGL_EXTERNAL_RGBA_INTEGER    = 0x8D99,  //GL_RGBA_INTEGER
        OGL_EXTERNAL_BGRA_INTEGER    = 0x8D9B,  //GL_BGRA_INTEGER
        OGL_EXTERNAL_DEPTH           = 0x1902,  //GL_DEPTH_COMPONENT
        OGL_EXTERNAL_DEPTH_STENCIL   = 0x84F9,  //GL_DEPTH_STENCIL
        OGL_EXTERNAL_STENCIL         = 0x1901,  //GL_STENCIL_INDEX
        OGL_EXTERNAL_LUMINANCE       = 0x1909,  //GL_LUMINANCE
        OGL_EXTERNAL_ALPHA           = 0x1906,  //GL_ALPHA
        OGL_EXTERNAL_LUMINANCE_ALPHA = 0x190A,  //GL_LUMINANCE_ALPHA
        OGL_EXTERNAL_SRGB_EXT        = 0x8C40,  //SRGB_EXT
        OGL_EXTERNAL_SRGB_ALPHA_EXT  = 0x8C42   //SRGB_ALPHA_EXT
    };

    enum GlTextureTarget
    {
        OGL_TARGET_1D                = 0x0DE0,
        OGL_TARGET_1D_ARRAY          = 0x8C18,
        OGL_TARGET_2D                = 0x0DE1,
        OGL_TARGET_2D_ARRAY          = 0x8C1A,
        OGL_TARGET_3D                = 0x806F,
        OGL_TARGET_RECT              = 0x84F5,
        OGL_TARGET_RECT_ARRAY        = 0x84F5, // Not supported by OpenGL
        OGL_TARGET_CUBE              = 0x8513,
        OGL_TARGET_CUBE_ARRAY        = 0x9009
    };

    enum GlSwizzle
    {
        OGL_SWIZZLE_RED              = 0x1903, //GL_RED
        OGL_SWIZZLE_GREEN            = 0x1904, //GL_GREEN
        OGL_SWIZZLE_BLUE             = 0x1905, //GL_BLUE
        OGL_SWIZZLE_ALPHA            = 0x1906, //GL_ALPHA
        OGL_SWIZZLE_ZERO             = 0x0000, //GL_ZERO
        OGL_SWIZZLE_ONE              = 0x0001  //GL_ONE
    };

    struct GlFormatDesc
    {
        GlInternalFormat internalFormat;
        GlExternalFormat externalFormat;
        GlTypeFormat     type;
        Vec4u            swizzles;
    };

public:
    static Vec4u            getGlSwizzle    (const Vec4ub& swizzles);
    static bool             hasSwizzle      ();
    static GlFormatDesc     getGlFormatDesc (Format format);
    static GlFormatDesc     getGlFormatDesc (Format format, const Vec4ub& swizzles);
    static Format           find            (GlInternalFormat internalFormat, GlExternalFormat externalFormat, GlTypeFormat type);

public:
    static FormatInfo                _formatInfo    [FORMAT_COUNT ];
    static GlSwizzle                 _swizzleInfo   [SWIZZLE_COUNT];

private:
    struct FormatDesc
    {
        GlInternalFormat internalFormat;
        GlExternalFormat externalFormat;
        GlTypeFormat     type;
        UInt32           properties;
    };

    static void              initializeFormatDesc   ();
    static const FormatDesc& getFormatDesc          (Format format);
    static Vec4ub            computeSwizzle         (const FormatDesc& formatDesc, const Vec4ub& swizzles);

private:
    static std::vector<FormatDesc> _formatDesc;
};

OSG_END_NAMESPACE

#include "OSGImageFormat.inl"

#endif /* _OSGIMAGEFORMAT_H_ */
