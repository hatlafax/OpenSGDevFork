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

OSG_END_NAMESPACE
