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
//  Includes
//-------------------------------

#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "OSGConfig.h"

#include <string>
#include <vector>

#include <iostream>
#include <fstream>

#include "OSGLog.h"

#include "OSGImage.h"

#include "OSGContribDDSImageFileType.h"

#include "OSGGLDebugUtils.h"

#ifdef OSG_SGI_STL

//#include <limits>
#ifndef INT_MAX
#define INT_MAX numeric_limits<Int32>::max()
#endif
#else
#include <climits>
#endif

#ifdef OSG_WITH_GLI
#include "gli/gli.hpp"
#endif


static const OSG::Char8 *cmimeType = "image/vnd-ms.dds";

// Static Class Varible implementations:
static const OSG::Char8 *suffixArray[] =
{
    "dds"
};

OSG_BEGIN_NAMESPACE

/*! \class ContribDDSImageFileType 

  Image File Type to read/write and store/restore Image objects as
  DDS data. Should work with binary and ascii dds/pbm/pgm/ppm data.
  
  All the type specific code is included in the class. Does
  not depend on external libs.
  
*/
/*
ContribDDSImageFileType ContribDDSImageFileType::_the(cmimeType,
                                                      suffixArray, 
                                                      sizeof(suffixArray),
                                                      (OSG_READ_SUPPORTED | 
                                                       OSG_WRITE_SUPPORTED));
*/

//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
    the given stream. Returns true on success.
 */

bool ContribDDSImageFileType::read(      Image        *pImage, 
                                         std::istream &is, 
                                   const std::string  &mimetype)
{
    bool error = false;

    std::ofstream os("d:/work/readDDSAndKtx.log", std::ofstream::out | std::ofstream::app);

    if (is.fail())
    {
        os << "is fail" << std::endl;
        return error;
    }

    os << "is ok" << std::endl;

    is.unsetf(std::ios::skipws);

    is.seekg(0, std::ios::end);
    std::streampos fileSize = is.tellg();

    is.seekg(0, std::ios::beg);

    std::vector<char> data;
    data.reserve(fileSize);

    os << "data file size = " << fileSize << std::endl;

    data.insert(data.begin(), std::istream_iterator<char>(is), std::istream_iterator<char>());

    gli::texture Texture = gli::load(&data[0], data.size());

    if(Texture.empty())
    {
        os << "gli::load texture empty" << std::endl;
        return error;
    }

    os << "gli::load ok" << std::endl;

    gli::gl GL(gli::gl::PROFILE_GL33);
    gli::gl::format const Format = GL.translate(Texture.format(), Texture.swizzles());

    GLenum Target = GL.translate(Texture.target());

    UInt32 swizzles_r = Format.Swizzles[0];
    UInt32 swizzles_g = Format.Swizzles[1];
    UInt32 swizzles_b = Format.Swizzles[2];
    UInt32 swizzles_a = Format.Swizzles[3];

    GLenum internalFormat = Format.Internal;
    GLenum externalFormat = Format.External;
    GLenum type           = Format.Type;

    Int32 levels = static_cast<Int32>(Texture.levels());
    Int32 layers = static_cast<Int32>(Texture.layers());
    Int32 faces  = static_cast<Int32>(Texture.faces ());
    Int32 total  = layers * faces;

    Int32 width  = Texture.extent().x;
    Int32 height = Texture.extent().y;
    Int32 depth  = Texture.extent().z;

    bool compressed = gli::is_compressed (Texture.format());
    bool cubemap    = gli::is_target_cube(Texture.target());

    os << "target         = " << (Target == 0 ? "0" : convertGLenumToString(Target)) << std::endl;
    os << "swizzles_r     = " << (swizzles_r == 0 ? "0" : swizzles_r == 1 ? "1" : convertGLenumToString(swizzles_r)) << std::endl;
    os << "swizzles_g     = " << (swizzles_g == 0 ? "0" : swizzles_g == 1 ? "1" : convertGLenumToString(swizzles_g)) << std::endl;
    os << "swizzles_b     = " << (swizzles_b == 0 ? "0" : swizzles_b == 1 ? "1" : convertGLenumToString(swizzles_b)) << std::endl;
    os << "swizzles_a     = " << (swizzles_a == 0 ? "0" : swizzles_a == 1 ? "1" : convertGLenumToString(swizzles_a)) << std::endl;

    os << "internalFormat = " << convertGLenumToString(internalFormat) << std::endl;
    os << "externalFormat = " << (externalFormat == 0 ? "0" : convertGLenumToString(externalFormat)) << std::endl;
    os << "type           = " << (type == 0 ? "0" : convertGLenumToString(type)) << std::endl;

    os << "width          = " << width  << std::endl;
    os << "height         = " << height << std::endl;
    os << "depth          = " << depth  << std::endl;

    os << "levels         = " << levels << std::endl;
    os << "layers         = " << layers << std::endl;
    os << "faces          = " << faces  << std::endl;
    os << "faces total    = " << total  << std::endl;

    os << "compressed     = " << compressed << std::endl;
    os << "cubemap        = " << cubemap    << std::endl;

    pImage->set(OSG::Image::PixelFormat(internalFormat),
                width, height, depth,
                levels,                             // mipmapCount
                layers,                             // frameCount
                0.0,                                // frameDelay
                NULL,                               // data
                OSG::Image::OSG_UINT8_IMAGEDATA,    // type
                true,                               // allocMem
                faces                               // sidecount
            );

    std::size_t tex_sz = Texture.size();
    UInt32 img_sz = pImage->getSize();

    os << "Texture size   = " << tex_sz  << std::endl;
    os << "Image size     = " << img_sz  << std::endl;
    os << std::endl;

//    if (Texture.size() == pImage->getSize())
    {
        UInt8* data = pImage->editData();

        char* p0 = static_cast<char*>(Texture.data());

        Int32 sum = 0;

        for(std::size_t Layer = 0; Layer < Texture.layers(); ++Layer)
        {
            os << "  layer        = " << Layer << std::endl;

            for(std::size_t Face  = 0; Face  < Texture.faces (); ++Face )
            {
                os << "  face         = " << Face  << std::endl;

                for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
                {
                    Int32 level_width  = Texture.extent(Level).x;
                    Int32 level_height = Texture.extent(Level).y;
                    Int32 level_depth  = Texture.extent(Level).z;

                    Target = cubemap ? static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + Face) : Target;
                    
                    char* p = static_cast<char*>(Texture.data(Layer, Face, Level));

                    Int32 szLevel = static_cast<Int32>(Texture.size(Level));
                    sum += szLevel;

                    os << "  level        = " << Level << std::endl;
                    os << "  size level   = " << szLevel << std::endl;
                    os << "  target       = " << (Target == 0 ? "0" : convertGLenumToString(Target)) << std::endl;

                    os << "  level width  = " << level_width  << std::endl;
                    os << "  level height = " << level_height << std::endl;
                    os << "  level depth  = " << level_depth  << std::endl;

                    os << "  offset       = " << std::ptrdiff_t(p - p0) << std::endl;

                    os << std::endl;
                }
            }
        }

        os << "Size sum       = " << sum << std::endl;
    }

    os << "------------------------------------------------------------------------" << std::endl;
    os << std::endl;

    Texture.clear();

    return true;
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given fileName.
  Returns true on success.
 */

bool ContribDDSImageFileType::write(const Image        *, 
                                          std::ostream &, 
                                    const std::string  &)
{
    
    return false;
}


//-------------------------------------------------------------------------
/*!
  Tries to determine the mime type of the data provided by an input stream
  by searching for magic bytes. Returns the mime type or an empty string
  when the function could not determine the mime type.
 */

std::string ContribDDSImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[4];

    is.read(filecode, 4);
    is.seekg(-4, std::ios::cur);
    
    return strncmp(filecode, "DDS ", 4) == 0 ?
        std::string(getMimeType()) : std::string();
}

/**constructors & destructors**/

ContribDDSImageFileType::ContribDDSImageFileType() :
     Inherited  (cmimeType, suffixArray, sizeof(suffixArray), (OSG_READ_SUPPORTED | OSG_WRITE_SUPPORTED))
{
}

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

ContribDDSImageFileType::ContribDDSImageFileType(const Char8  *mimeType,
                                                 const Char8  *suffixArray[],
                                                       UInt16  suffixByteCount,
                                                       UInt32  flags          ) :
     Inherited  (mimeType,suffixArray, suffixByteCount, flags)
{
}

//-------------------------------------------------------------------------
/*! Destructor
 */

ContribDDSImageFileType::~ContribDDSImageFileType(void)
{
}

OSG_END_NAMESPACE
