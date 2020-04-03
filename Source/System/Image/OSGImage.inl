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


/*! Check if the pixelFormat, dimension, bpp and data are valid (not null)
    with a single call.    
 */

inline 
bool Image::isValid(void) const
{ 
    return !_mfPixel.empty();
}

/*! Returns a hash value calculated over the image's pixel data. The hash value
    is cached and only (re-)calculated if the cached value has been invalidated
    or \a force is true.
*/

inline
SizeT Image::getHash(bool force) const
{
    if(force || !_hashValid)
        calcHash();

    return _hash;
}

/*! returns the data size in bytes. 
 */
inline 
unsigned long Image::getSize(bool withMipmap,
                             bool withFrames,
                             bool withSides ) const
{ 
    return ( (calcMipmapSumSize((withMipmap ? getMipMapCount() : 1))) *
             (withSides  ? getSideCount () : 1                      ) *
             (withFrames ? getFrameCount() : 1                      ) ); 
}

/*! returns a data pointer for a single frame/mipmap chunk
 */

inline 
const UInt8 *Image::getData(UInt32 mipmapNum, 
                            UInt32 frameNum,
                            UInt32 sideNum ) const
{
    if(_mfPixel.empty())
        return NULL;

    const UInt8 *data = 
        (&(_mfPixel[0])           ) + 
        (sideNum  * getSideSize ()) +
        (frameNum * getFrameSize());
    
    if (mipmapNum)
    {
        data += calcMipmapSumSize(mipmapNum);
    }
  
    return data;
}

inline 
UInt8 *Image::editData(UInt32 mipmapNum, 
                       UInt32 frameNum,
                       UInt32 sideNum) 
{
    if(_mfPixel.empty())
        return NULL;

    editMField(PixelFieldMask, _mfPixel);

    UInt8 *data = 
        (&(_mfPixel[0])           ) + 
        (sideNum  * getSideSize ()) +
        (frameNum * getFrameSize());
    
    if (mipmapNum)
    {
        data += calcMipmapSumSize(mipmapNum);
    }
 
    return data;
}


/*! returns a data pointer for a single frame/mipmap chunk
 */

inline 
const UInt8 *Image::getDataFast(UInt32 mipmapNum, 
                                UInt32 frameNum,
                                UInt32 sideNum ) 
{
    const UInt8 *data = 
        (&(_mfPixel[0])           ) + 
        (sideNum  * getSideSize ()) +
        (frameNum * getFrameSize());
    
    if(_mipmapOffset.size() <= mipmapNum)
        calcMipmapOffsets();

    data += _mipmapOffset[mipmapNum];
   
    return data;
}

inline 
UInt8 *Image::editDataFast(UInt32 mipmapNum, 
                           UInt32 frameNum,
                           UInt32 sideNum) 
{
    editMField(PixelFieldMask, _mfPixel);

    UInt8 *data = 
        (&(_mfPixel[0])           ) + 
        (sideNum  * getSideSize ()) +
        (frameNum * getFrameSize());
    
    if(_mipmapOffset.size() <= mipmapNum)
        calcMipmapOffsets();

    data += _mipmapOffset[mipmapNum];
  
    return data;
}

inline
UInt32 Image::calcMipmapLevelSize(const FormatInfo& info,
                                  UInt32 mipmapNum,
                                  UInt32 w, UInt32 h, UInt32 d) const
{
    Int32 sum = 0;
    if (info.format == 0)
    {
        sum = (w?w:1) * (h?h:1) * (d?d:1) * getBpp();
    }
    else
    {
        sum = ((w?w:1) + info.blockExtent.x()-1) / info.blockExtent.x() * 
              ((h?h:1) + info.blockExtent.y()-1) / info.blockExtent.y() *
              ((d?d:1) + info.blockExtent.z()-1) / info.blockExtent.z() * 
              info.blockSize;
    }

#ifdef OSG_DEBUG
    switch (getPixelFormat())
    {
        case OSG_RGB_DXT1:
        case OSG_RGBA_DXT1:
        case OSG_SRGB_DXT1:
        case OSG_SRGB_ALPHA_DXT1:
            sum = (((w?w:1)+3)/4) * (((h?h:1)+3)/4) * 8;
            break;
        case OSG_RGBA_DXT3:
        case OSG_RGBA_DXT5:
        case OSG_SRGB_ALPHA_DXT3:
        case OSG_SRGB_ALPHA_DXT5:
            sum = (((w?w:1)+3)/4) * (((h?h:1)+3)/4) * 16;
            break;

        default:
            sum = (w?w:1) * (h?h:1) * getBpp();
            break;
    }

    sum *= (d?d:1);
#endif

    return sum;
}

inline
UInt32 Image::calcMipmapLevelSize(const FormatInfo& info,
                                  UInt32 mipmapNum) const
{
    UInt32 w, h, d;
    calcMipmapGeometry(mipmapNum, w, h, d);
    return calcMipmapLevelSize(info, mipmapNum, w, h, d);
}

inline
UInt32 Image::calcMipmapSumSize(const FormatInfo& info,
                                UInt32 mipmapNum,
                                UInt32 w,
                                UInt32 h,
                                UInt32 d) const
{
    Int32 sum = 0;

    if (w && h && d)
    {
        while (mipmapNum--)
        {
            sum += calcMipmapLevelSize(info, mipmapNum,w,h,d);

            w >>= 1;
            h >>= 1;
            d >>= 1;
        }
    }

    return sum;
}

#ifdef CHECK_GV
// Specialization for Image we need this to support VRML PixelTextures.
template <> inline
void SFImagePtr::pushValueByStr(const Char8 *str)
{
    if(getValue() != NullFC)
        getValue()->addValue(str);
}
#endif

OSG_END_NAMESPACE
