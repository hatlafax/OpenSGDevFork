/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

//-------------------------------
//      Includes                                    
//-------------------------------

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <memory.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGLog.h"
#include "OSGImageFileHandler.h"
#include "OSGPathHandler.h"
#include "OSGFileSystem.h"

#include "OSGHDRImageFileType.h"

// Static Class Varible implementations: 
static const OSG::Char8 *suffixArray[] = 
{
    "hdr"
};

OSG_BEGIN_NAMESPACE

#define MINELEN 8           // minimum scanline length for encoding
#define MAXELEN 0x7fff      // maximum scanline length for encoding
#define MINRUN  4           // minimum run length
#define RED 0
#define GRN 1
#define BLU 2
#define EXP 3
#define COLXS 128

// copy source -> dest
#define copy_rgbe(c1, c2) (c2[RED]=c1[RED],c2[GRN]=c1[GRN],c2[BLU]=c1[BLU],c2[EXP]=c1[EXP])

/*! \class HDRImageFileType 

  Image File Type to read/write and store/restore Image objects as
  HDR data.

  All the type specific code is included in the class. Does
  not depend on external libs.
    
 */

/*****************************
 *   Types
 *****************************/

HDRImageFileType HDRImageFileType::_the("image/x-hdr",
                                        suffixArray, sizeof(suffixArray),
                                        OSG_READ_SUPPORTED | 
                                        OSG_WRITE_SUPPORTED );


/*****************************
 *    Classvariables
 *****************************/


/********************************
 *    Class methodes
 *******************************/


/*******************************
*public
*******************************/

//-------------------------------------------------------------------------
/*!
  Tries to fill the image object with the data read from
  the given input stream. Returns true on success.
*/

bool HDRImageFileType::read(      Image        *image, 
                                  std::istream &is, 
                            const std::string  &mimetype)
{
    int width, height;
    
    if (!checkHDR(is, width, height))
    {
        FWARNING(("No valid RADIANCE picture format\n"));
        return false;
    }

    bool use16BitFloat = false;

    if(this->hasOption("use16BitFloat") == true)
    {
        this->getOptionAs("use16BitFloat", use16BitFloat);
    }

    image->set(Image::OSG_RGB_PF, 
               width, 
               height, 
               1, 1, 1, 0.0, 0, 
               (use16BitFloat == true) ? 
                   Image::OSG_FLOAT16_IMAGEDATA : Image::OSG_FLOAT32_IMAGEDATA);

    if(!image->isValid())
        return false;

    image->clear();

    if(use16BitFloat)
    {
        Real16 *data = reinterpret_cast<Real16 *>(image->editData());

        return radiance2fp(is, data, width, height);
    }
    else
    {
        Real32 *data = reinterpret_cast<Real32 *>(image->editData());
        
        return radiance2fp(is, data, width, height);
    }
}

//-------------------------------------------------------------------------
/*!
  Tries to write the image object to the given output stream.
  Returns true on success.
*/

bool HDRImageFileType::write(const Image        *image, 
                                   std::ostream &os, 
                             const std::string  &mimetype)
{
    if( (image->getDataType() != Image::OSG_FLOAT32_IMAGEDATA) &&
        (image->getDataType() != Image::OSG_FLOAT16_IMAGEDATA)  )
    {
        FWARNING(("HDRImageFileType::write: Image has non float data "
                  "type!\n"));
        return false;
    }
    
    if(!os.good())
        return false;

    int width  = image->getWidth();
    int height = image->getHeight();

    os << "#?RADIANCE" << std::endl;
    os << "# Written with OpenSG" << std::endl;
    os << "FORMAT=32-bit_rle_rgbe" << std::endl;
    os << "EXPOSURE=" << 1.0f << std::endl << std::endl;
    os << "-Y " << height << " +X " << width << std::endl;

    ScanlineT rgbe_scan(width);
    ScratchT  scratch(4 * width);

    if( image->getDataType() == Image::OSG_FLOAT32_IMAGEDATA)
    {
        const Real32 *data = reinterpret_cast<const Real32 *>(image->getData());

        //upside down !!!
        for(int y=height-1;y>=0;y--)
        {
            if (fwritecolrs(os, 
                            &data[y * width * 3], 
                            rgbe_scan, 
                            scratch,
                            width, 
                            height) < 0)
            {
                return false;
            }
        }
    }
    else // OSG_FLOAT16_IMAGEDATA
    {
        const Real16 *data = reinterpret_cast<const Real16 *>(image->getData());

        //upside down !!!
        for(int y=height-1;y>=0;y--)
        {
            if(fwritecolrs(os, 
                           &data[y * width * 3], 
                           rgbe_scan, 
                           scratch,
                           width, 
                           height) < 0)
            {
                return false;
            }
        }
    }

    return true;
}

//-------------------------------------------------------------------------
/*!
  Tries to restore the image data from the given memblock.
  Returns the amount of data read.
*/

UInt64 HDRImageFileType::restoreData(      Image  *image, 
                                     const UChar8 *buffer,
                                           Int32         ) const
{
    image->setData(buffer);

    return image->getSize();
}

//-------------------------------------------------------------------------
/*!
  Tries to store the image data to the given memblock.
  Returns the amount of data written.
*/

UInt64 HDRImageFileType::storeData(const Image  *image, 
                                         UChar8 *buffer,
                                         Int32   OSG_CHECK_ARG(memSize)) const
{
    UInt32 dataSize = image->getSize();

    const UChar8 *src = image->getData();

    if(dataSize && src && buffer)
        memcpy(buffer, src, dataSize);
  
    return dataSize;
} 


//-------------------------------------------------------------------------
/*!
  Constructor used for the singleton object
*/

HDRImageFileType::HDRImageFileType(const Char8 *mimeType,
                                   const Char8 *suffixArray[], 
                                         UInt16 suffixByteCount,
                                         UInt32 flags          ) :
    Inherited(mimeType, 
              suffixArray, 
              suffixByteCount, 
              flags )
{
}

//-------------------------------------------------------------------------
/*!
  Destructor
*/

HDRImageFileType::~HDRImageFileType(void)
{
}

// check header and get resolution (streaming type)
bool HDRImageFileType::checkHDR(std::istream &is, int &width, int &height)
{
    char cs[256], st1[80], st2[80];
    bool resok = false;
    bool HDRok = false;
    int i = 0;

    while (!is.eof() && !resok)
    {
        is.getline(cs, 255);

        if (strstr(cs, "32-bit_rle_rgbe"))
            HDRok = true;

        if (HDRok && (cs[0] == '\r' || cs[0] == '\n' || cs[0] == '\0'))
        {
            // empty line found, next is resolution info, format: -Y N +X N
            // directly followed by data
            is.getline(cs, 255);
        
            i = sscanf(cs, "%79s %d %79s %d", st1, &height, st2, &width);
            if (i == 4) 
                resok = true;
        }
    }
    
    return HDRok;
}

bool HDRImageFileType::handleNonRunLengthEncodedData(
    std::istream  &is, 
    Real16        *data, 
    int            width, 
    int            height,
    ScanlineT     &sline,
    unsigned char  rgbe[4])
{
    int x,y,yx;

    for(int i=0;i<4;i++)
        sline[0][i] = rgbe[i];

    for(y = height-1; y >= 0; y--)
    {
        yx = y*width;

        for (int j=1; j < width; ++j)
        {
            rgbe[0] = static_cast<unsigned char>(is.get());
            rgbe[1] = static_cast<unsigned char>(is.get());
            rgbe[2] = static_cast<unsigned char>(is.get());
            rgbe[3] = static_cast<unsigned char>(is.get());

            for(int i=0;i<4;i++)
                sline[j][i] = rgbe[i];
        }

        Real16* fcol = &data[yx * 3];
        for (x=0;x<width;x++)
        {
            RGBE2Half(sline[x], fcol);
            fcol += 3;
        }
    }

    return true;
}

bool HDRImageFileType::handleNonRunLengthEncodedData(
    std::istream  &is, 
    Real32        *data, 
    int            width, 
    int            height,
    ScanlineT     &sline,
    unsigned char  rgbe[4])
{
    int x,y,yx;

    for(int i=0;i<4;i++)
        sline[0][i] = rgbe[i];

    int j=1;

    for(y = height-1; y >= 0; y--, j=0)
    {
        yx = y*width;

        for (; j < width; ++j)
        {
            rgbe[0] = static_cast<unsigned char>(is.get());
            rgbe[1] = static_cast<unsigned char>(is.get());
            rgbe[2] = static_cast<unsigned char>(is.get());
            rgbe[3] = static_cast<unsigned char>(is.get());

            for(int i=0;i<4;i++)
                sline[j][i] = rgbe[i];
        }

        Real32* fcol = &data[yx * 3];
        for (x=0;x<width;x++)
        {
            RGBE2Float(sline[x], fcol);
            fcol += 3;
        }
    }

    return true;
}

// convert radiance hdr to float image (streaming type)
bool HDRImageFileType::radiance2fp(std::istream &is, 
                                   Real16       *data, 
                                   int           width, 
                                   int           height)
{
    int x,y,yx;
    ScanlineT sline(width);

    int code,val;
    unsigned char c1, c2, len;

    if ((width < MINELEN) | (width > MAXELEN))
    {
        // Read flat data
        unsigned char rgbe[4];

        rgbe[0] = static_cast<unsigned char>(is.get()); if (is.eof()) return false;
        rgbe[1] = static_cast<unsigned char>(is.get());
        rgbe[2] = static_cast<unsigned char>(is.get());
        rgbe[3] = static_cast<unsigned char>(is.get());

        return handleNonRunLengthEncodedData(is, data, width, height, sline, rgbe);
    }

    for(y=height-1;y>=0;y--)
    {
        yx = y*width;

                        c1  = static_cast<unsigned char>(is.get());     if (is.eof()) return false;
        sline[0][GRN] = c2  = static_cast<unsigned char>(is.get());
        sline[0][BLU] = len = static_cast<unsigned char>(is.get());

        if ( c1 != 2 || c2 != 2 || (len & 0x80) )
        {
            // not run-length encoded, so we have to actually use THIS data as a decoded
            // pixel (note this can't be a valid pixel--one of RGB must be >= 128)

            unsigned char rgbe[4];
            rgbe[0] = c1;
            rgbe[1] = c2;
            rgbe[2] = len;
            rgbe[3] = static_cast<unsigned char>(is.get());

            return handleNonRunLengthEncodedData(is, data, width, height, sline, rgbe);
        }

        len <<= 8;
        len |= is.get();

        for(int i=0;i<4;i++)
        {
            for (int j=0;j<width;)
            {
                if (is.eof())
                    return false;

                code = is.get();
                    
                if (code > 128)
                {
                    code &= 127;
                    val = is.get();
                    
                    while (code--)
                        sline[j++][i] = static_cast<unsigned char>(val);
                }
                else
                {
                    while (code--) 
                      sline[j++][i] = is.get();
                }
            }
        }

        Real16* fcol = &data[yx * 3];
        for (x=0;x<width;x++)
        {
            RGBE2Half(sline[x], fcol);
            fcol += 3;
        }
    }
    
    return true;
}

bool HDRImageFileType::radiance2fp(std::istream &is, 
                                   Real32       *data, 
                                   int           width, 
                                   int           height)
{
    int x,y,yx;
    ScanlineT sline(width);

    int code,val;
    unsigned char c1, c2, len;

    if ((width < MINELEN) | (width > MAXELEN))
    {
        // Read flat data
        unsigned char rgbe[4];

        rgbe[0] = static_cast<unsigned char>(is.get()); if (is.eof()) return false;
        rgbe[1] = static_cast<unsigned char>(is.get());
        rgbe[2] = static_cast<unsigned char>(is.get());
        rgbe[3] = static_cast<unsigned char>(is.get());

        return handleNonRunLengthEncodedData(is, data, width, height, sline, rgbe);
    }

    for(y=height-1;y>=0;y--)
    {
        yx = y*width;

                        c1  = static_cast<unsigned char>(is.get());     if (is.eof()) return false;
        sline[0][GRN] = c2  = static_cast<unsigned char>(is.get());
        sline[0][BLU] = len = static_cast<unsigned char>(is.get());

        if ( c1 != 2 || c2 != 2 || (len & 0x80) )
        {
            // not run-length encoded, so we have to actually use THIS data as a decoded
            // pixel (note this can't be a valid pixel--one of RGB must be >= 128)

            unsigned char rgbe[4];
            rgbe[0] = c1;
            rgbe[1] = c2;
            rgbe[2] = len;
            rgbe[3] = static_cast<unsigned char>(is.get());

            return handleNonRunLengthEncodedData(is, data, width, height, sline, rgbe);
        }

        len <<= 8;
        len |= is.get();

        for(int i=0;i<4;i++)
        {
            for (int j=0;j<width;)
            {
                if (is.eof())
                    return false;

                code = is.get();
                    
                if (code > 128)
                {
                    code &= 127;
                    val = is.get();
                    
                    while (code--)
                        sline[j++][i] = static_cast<unsigned char>(val);
                }
                else
                {
                    while (code--) 
                      sline[j++][i] = is.get();
                }
            }
        }

        Real32* fcol = &data[yx * 3];
        for (x=0;x<width;x++)
        {
            RGBE2Float(sline[x], fcol);
            fcol += 3;
        }
    }
    
    return true;
}

//rgbe -> float color
void HDRImageFileType::RGBE2Float(const RGBE& rgbe, Real32 *fcol)
{
    if (rgbe[EXP] == 0)
    {
        *(fcol + RED) = *(fcol + GRN) = *(fcol + BLU) = 0;
    }
    else
    {
        Real32 f = ldexp(1., rgbe[EXP]-(COLXS+8));
        *(fcol + RED) = (rgbe[RED]+.5)*f;
        *(fcol + GRN) = (rgbe[GRN]+.5)*f;
        *(fcol + BLU) = (rgbe[BLU]+.5)*f;
    }
}

void HDRImageFileType::RGBE2Half(const RGBE& rgbe, Real16 *fcol)
{
    if(rgbe[EXP] == 0)
    {
        *(fcol + RED) = *(fcol + GRN) = *(fcol + BLU) = 0;
    }
    else
    {
        Real32 f = ldexp(1., rgbe[EXP]-(COLXS+8));

        *(fcol + RED) = Real16( ( rgbe[RED]+.5) * f);
        *(fcol + GRN) = Real16( ( rgbe[GRN]+.5) * f);
        *(fcol + BLU) = Real16( ( rgbe[BLU]+.5) * f);
    }
}

int HDRImageFileType::fwritecolrs(std:: ostream   &os, 
                                  const Real32    *scan, 
                                        ScanlineT &rgbe_scan, 
                                        ScratchT  &scratch,
                                        int        width, 
                                        int        height   )
{
    // convert scanline
    for (int i=0;i<width;i++)
    {
        float2RGBE(scan, rgbe_scan[i]);
        scan += 3;
    }

    return fwriteRGBE(os, rgbe_scan, scratch, width, height);
}

int HDRImageFileType::fwritecolrs(std:: ostream   &os, 
                                  const Real16    *scan, 
                                        ScanlineT &rgbe_scan, 
                                        ScratchT  &scratch,
                                        int        width, 
                                        int        height)
{
    // convert scanline
    for(int i=0;i<width;i++)
    {
        half2RGBE(scan, rgbe_scan[i]);
        scan += 3;
    }

    return fwriteRGBE(os, rgbe_scan, scratch, width, height);
}

int HDRImageFileType::fwriteRGBE(std::ostream   &os,  
                                      ScanlineT &rgbe_scan, 
                                      ScratchT  &scratch,
                                      int        width, 
                                      int        height)
{
    if ((width < MINELEN) | (width > MAXELEN))
    {
        // OOBs, write out flat
        os.write(reinterpret_cast<char *>(&rgbe_scan[0]), width);
        return 0;
    }

    for(int j=0;j<width;j++)
    {
        scratch[j + width*0] = rgbe_scan[j][0];
        scratch[j + width*1] = rgbe_scan[j][1];
        scratch[j + width*2] = rgbe_scan[j][2];
        scratch[j + width*3] = rgbe_scan[j][3];
    }

    // put magic header
    os << static_cast<unsigned char>(2);
    os << static_cast<unsigned char>(2);
    os << static_cast<unsigned char>((width&0xff00) >>8);
    os << static_cast<unsigned char>( width&0x00ff     );

    /* RLE each component separately */
    int x;
    int c,r;

    for (c=0; c < 4; c++)
    {
        unsigned char *comp = &scratch[width*c];

        x = 0;
        while (x < width)
        {
            // find first run
            r = x;
            while (r+2 < width)
            {
                if (comp[r] == comp[r+1] && comp[r] == comp[r+2])
                    break;
                ++r;
            }
    
            if (r+2 >= width)
                r = width;
    
            // dump up to first run
            while (x < r)
            {
                int len = r-x;
                if (len > 128)
                    len = 128;
    
                os << static_cast<unsigned char>(len);
                os.write(reinterpret_cast<const char*>(&comp[x]), len);
                
                x += len;
            }
    
            // if there's a run, output it
            if (r+2 < width)    // same test as what we break out of in search loop, so only true if we break'd
            {
                // find next byte after run
                while (r < width && comp[r] == comp[x])
                    ++r;
    
                // output run up to r
                while (x < r)
                {
                    int len = r-x;
                    if (len > 127)
                        len = 127;
    
                    unsigned char lengthbyte = static_cast<unsigned char>(len+128);

                    os << lengthbyte;
                    os << comp[x];

                    x += len;
                }
            }
        }
    }

    return (os.fail() ? -1 : 0);
}

//float color -> rgbe
void HDRImageFileType::float2RGBE(const Real32 *fcol, RGBE& rgbe)
{
    Real32 d = (*(fcol + RED) > *(fcol + GRN)) ? *(fcol + RED) : *(fcol + GRN);
    
    if(*(fcol + BLU) > d)
    {
        d = *(fcol + BLU);
    }
    if(d <= 1e-32f)
    {
        rgbe[RED] = rgbe[GRN] = rgbe[BLU] = rgbe[EXP] = 0;
    }
    else
    {
        int e;
        d = frexp(d, &e) * 256.f / d;
        rgbe[RED] = static_cast<unsigned char>(*(fcol + RED) * d);
        rgbe[GRN] = static_cast<unsigned char>(*(fcol + GRN) * d);
        rgbe[BLU] = static_cast<unsigned char>(*(fcol + BLU) * d);
        rgbe[EXP] = static_cast<unsigned char>(e + COLXS);
    }
}

//half color -> rgbe
void HDRImageFileType::half2RGBE(const Real16 *fcol, RGBE& rgbe)
{
    Real32 d = (*(fcol + RED) > *(fcol + GRN)) ? *(fcol + RED) : *(fcol + GRN);
    
    if(*(fcol + BLU) > d)
    {
        d = *(fcol + BLU);
    }
    if(d <= 1e-32f)
    {
        rgbe[RED] = rgbe[GRN] = rgbe[BLU] = rgbe[EXP] = 0;
    }
    else
    {
        int e;
        d = frexp(d, &e) * 256.f / d;
        rgbe[RED] = static_cast<unsigned char>(*(fcol + RED) * d);
        rgbe[GRN] = static_cast<unsigned char>(*(fcol + GRN) * d);
        rgbe[BLU] = static_cast<unsigned char>(*(fcol + BLU) * d);
        rgbe[EXP] = static_cast<unsigned char>(e + COLXS);
    }
}

OSG_END_NAMESPACE
