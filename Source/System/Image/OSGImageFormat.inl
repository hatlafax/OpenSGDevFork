/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

inline
const ImageFormat::FormatInfo& ImageFormat::getFormatInfo(Format format)
{
    OSG_ASSERT(format >= FORMAT_FIRST && format <= FORMAT_LAST);
    return _formatInfo[format];
}

inline 
bool ImageFormat::IsValid(Format format)
{
    return format >= FORMAT_FIRST && format <= FORMAT_LAST;
}

inline 
bool ImageFormat::IsCompressed(Format format)
{
    return getFormatInfo(format).flags & CAP_COMPRESSED_BIT ? true : false;
}

inline 
bool ImageFormat::IsS3TcCompressed(Format format)
{
    return format >= FORMAT_RGB_DXT1_UNORM_BLOCK8 && format <= FORMAT_RGBA_DXT5_SRGB_BLOCK16;
}

inline 
bool ImageFormat::IsSRGB(Format format)
{
    return getFormatInfo(format).flags & CAP_COLORSPACE_SRGB_BIT ? true : false;
}

// Return the size in bytes of a block for a format.
inline 
UInt8 ImageFormat::getBlockSize(Format format)
{
    return getFormatInfo(format).blockSize;
}

// Return the dimensions in texels of the block for a format
inline 
const Vec3ub& ImageFormat::getBlockExtent(Format format)
{
    return getFormatInfo(format).blockExtent;
}

// Return the number of components of a format
inline 
UInt8 ImageFormat::getComponentCount(Format format)
{
    return getFormatInfo(format).component;
}

inline 
bool ImageFormat::IsUnsigned(Format format)
{
    return getFormatInfo(format).flags & CAP_UNSIGNED_BIT ? true : false;
}

inline 
bool ImageFormat::IsSigned(Format format)
{
    return getFormatInfo(format).flags & CAP_SIGNED_BIT ? true : false;
}

inline 
bool ImageFormat::IsInteger(Format format)
{
    return getFormatInfo(format).flags & CAP_INTEGER_BIT ? true : false;
}

inline 
bool ImageFormat::IsSignedInteger(Format format)
{
    return IsInteger(format) && IsSigned(format);
}

inline 
bool ImageFormat::IsUnsignedInteger(Format format)
{
    return IsInteger(format) && IsUnsigned(format);
}

inline 
bool ImageFormat::IsFloat(Format format)
{
    return getFormatInfo(format).flags & CAP_FLOAT_BIT ? true : false;
}

inline 
bool ImageFormat::IsNormalized(Format format)
{
    return getFormatInfo(format).flags & CAP_NORMALIZED_BIT ? true : false;
}

inline 
bool ImageFormat::IsUNorm(Format format)
{
    return IsNormalized(format) && IsUnsigned(format);
}

inline 
bool ImageFormat::IsSNorm(Format format)
{
    return IsNormalized(format) && IsSigned(format);
}

inline 
bool ImageFormat::IsPacked(Format format)
{
    UInt16 flags = getFormatInfo(format).flags;
		
    return (flags & CAP_PACKED8_BIT) != 0 || (flags & CAP_PACKED16_BIT) != 0 || (flags & CAP_PACKED32_BIT) != 0;
}

inline 
bool ImageFormat::IsDepth(Format format)
{
    return getFormatInfo(format).flags & CAP_DEPTH_BIT ? true : false;
}

inline 
bool ImageFormat::IsStencil(Format format)
{
    return getFormatInfo(format).flags & CAP_STENCIL_BIT ? true : false;
}

inline 
bool ImageFormat::IsDepthStencil(Format format)
{
    return IsDepth(format) && IsStencil(format);
}

inline
UInt32 ImageFormat::getBitsPerPixel(Format format)
{
    const FormatInfo& info = getFormatInfo(format);

    return info.blockSize * 8 / (info.blockExtent.x() * info.blockExtent.y() * info.blockExtent.z());
}

inline
Vec4ub ImageFormat::getSwizzle(Format format)
{
    const FormatInfo& info = getFormatInfo(format);

    return info.swizzles;
}

inline
bool ImageFormat::IsChannel(Swizzle swizzle)
{
    return swizzle >= SWIZZLE_CHANNEL_FIRST && swizzle <= SWIZZLE_CHANNEL_LAST;
}

inline
Vec4u ImageFormat::getGlSwizzle(const Vec4ub& swizzles)
{
    return Vec4u(_swizzleInfo[swizzles[0]],
                 _swizzleInfo[swizzles[1]],
                 _swizzleInfo[swizzles[2]], 
                 _swizzleInfo[swizzles[3]]);
}

inline
Vec4ub ImageFormat::computeSwizzle(const FormatDesc& formatDesc, const Vec4ub& swizzles)
{
    if (!hasSwizzle())
        return Vec4ub(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA);

    bool isExternalBGRA = ( (formatDesc.properties & FORMAT_PROPERTY_BGRA_FORMAT_BIT) &&  !hasSwizzle() ) || (formatDesc.properties & FORMAT_PROPERTY_BGRA_TYPE_BIT);

    return isExternalBGRA ? Vec4ub(swizzles[2], swizzles[1], swizzles[0], swizzles[3]) : swizzles;
}

inline
const ImageFormat::FormatDesc& ImageFormat::getFormatDesc(Format format)
{
    OSG_ASSERT(IsValid(format));

    initializeFormatDesc();

    return _formatDesc[format];
}

inline
ImageFormat::GlFormatDesc ImageFormat::getGlFormatDesc(Format format)
{
    const Vec4ub swizzles = getSwizzle(format);
    return getGlFormatDesc(format, swizzles);
}

inline
ImageFormat::GlFormatDesc ImageFormat::getGlFormatDesc(Format format, const Vec4ub& swizzles)
{
    const FormatDesc& desc = getFormatDesc(format);
    
    GlFormatDesc result;

    result.internalFormat = desc.internalFormat;
    result.externalFormat = desc.externalFormat;
    result.type           = desc.type;
    result.swizzles       = getGlSwizzle(computeSwizzle(desc, swizzles));

    return result;
}

OSG_END_NAMESPACE
