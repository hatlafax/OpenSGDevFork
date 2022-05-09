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

#ifndef _OSGIMAGE_H_
#define _OSGIMAGE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGImageBase.h"
#include "OSGGLEXT.h"
#include "OSGReal16.h"

#define OSG_GL_BGR                                          0x80E0
#define OSG_GL_BGRA                                         0x80E1
#define OSG_GL_COMPRESSED_RGB_S3TC_DXT1_EXT                 0x83F0
#define OSG_GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                0x83F1
#define OSG_GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                0x83F2
#define OSG_GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                0x83F3
#define OSG_GL_COMPRESSED_SRGB_S3TC_DXT1_EXT                0x8C4C
#define OSG_GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT          0x8C4D
#define OSG_GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT          0x8C4E
#define OSG_GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT          0x8C4F
#define OSG_GL_COMPRESSED_RED_RGTC1                         0x8DBB
#define OSG_GL_COMPRESSED_SIGNED_RED_RGTC1                  0x8DBC
#define OSG_GL_COMPRESSED_RG_RGTC2                          0x8DBD
#define OSG_GL_COMPRESSED_SIGNED_RG_RGTC2                   0x8DBE
#define OSG_GL_COMPRESSED_RGBA_BPTC_UNORM_ARB               0x8E8C
#define OSG_GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB         0x8E8D
#define OSG_GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB         0x8E8E
#define OSG_GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB       0x8E8F
#define OSG_GL_COMPRESSED_RGBA_ASTC_4x4_KHR                 0x93B0
#define OSG_GL_COMPRESSED_RGBA_ASTC_5x4_KHR                 0x93B1
#define OSG_GL_COMPRESSED_RGBA_ASTC_5x5_KHR                 0x93B2
#define OSG_GL_COMPRESSED_RGBA_ASTC_6x5_KHR                 0x93B3
#define OSG_GL_COMPRESSED_RGBA_ASTC_6x6_KHR                 0x93B4
#define OSG_GL_COMPRESSED_RGBA_ASTC_8x5_KHR                 0x93B5
#define OSG_GL_COMPRESSED_RGBA_ASTC_8x6_KHR                 0x93B6
#define OSG_GL_COMPRESSED_RGBA_ASTC_8x8_KHR                 0x93B7
#define OSG_GL_COMPRESSED_RGBA_ASTC_10x5_KHR                0x93B8
#define OSG_GL_COMPRESSED_RGBA_ASTC_10x6_KHR                0x93B9
#define OSG_GL_COMPRESSED_RGBA_ASTC_10x8_KHR                0x93BA
#define OSG_GL_COMPRESSED_RGBA_ASTC_10x10_KHR               0x93BB
#define OSG_GL_COMPRESSED_RGBA_ASTC_12x10_KHR               0x93BC
#define OSG_GL_COMPRESSED_RGBA_ASTC_12x12_KHR               0x93BD
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR         0x93D0
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR         0x93D1
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR         0x93D2
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR         0x93D3
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR         0x93D4
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR         0x93D5
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR         0x93D6
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR         0x93D7
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR        0x93D8
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR        0x93D9
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR        0x93DA
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR       0x93DB
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR       0x93DC
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR       0x93DD
#define OSG_GL_COMPRESSED_RGB8_ETC2                         0x9274
#define OSG_GL_COMPRESSED_SRGB8_ETC2                        0x9275
#define OSG_GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2     0x9276
#define OSG_GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2    0x9277
#define OSG_GL_COMPRESSED_RGBA8_ETC2_EAC                    0x9278
#define OSG_GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC             0x9279
#define OSG_GL_COMPRESSED_R11_EAC                           0x9270
#define OSG_GL_COMPRESSED_SIGNED_R11_EAC                    0x9271
#define OSG_GL_COMPRESSED_RG11_EAC                          0x9272
#define OSG_GL_COMPRESSED_SIGNED_RG11_EAC                   0x9273
#define OSG_GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG              0x8C00
#define OSG_GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG              0x8C01
#define OSG_GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG             0x8C02
#define OSG_GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG             0x8C03
#define OSG_GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG             0x9137
#define OSG_GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG             0x9138
#define OSG_GL_COMPRESSED_RGB8_ETC1                         0x8D64
#define OSG_GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT             0x8A54
#define OSG_GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT             0x8A55
#define OSG_GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT       0x8A56
#define OSG_GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT       0x8A57
#define OSG_GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG       0x93F0
#define OSG_GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG       0x93F1
#define OSG_GL_DEPTH_STENCIL                                0x84F9
#define OSG_GL_UNSIGNED_INT_24_8                            0x84FA

OSG_BEGIN_NAMESPACE

/*! \brief Image class. See \ref PageSystemImage
    for a description.
    \ingroup GrpSystemImageObj
    \ingroup GrpLibOSGSystem
    \includebasedoc
*/

class OSG_SYSTEM_DLLMAPPING Image : public ImageBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ImageBase                           Inherited;

    enum PixelFormat 
    {   
        OSG_INVALID_PF                      = 0,
        OSG_A_PF                            =     GL_ALPHA,
        OSG_I_PF                            =     GL_INTENSITY,
        OSG_L_PF                            =     GL_LUMINANCE,
        OSG_LA_PF                           =     GL_LUMINANCE_ALPHA,

        OSG_R_PF                            =     GL_RED,
        OSG_RG_PF                           =     GL_RG,

        OSG_RGB_PF                          =     GL_RGB,
        OSG_RGBA_PF                         =     GL_RGBA,

        OSG_BGR_PF                          = OSG_GL_BGR,
        OSG_BGRA_PF                         = OSG_GL_BGRA,

        OSG_RGB_DXT1                        = OSG_GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
        OSG_RGBA_DXT1                       = OSG_GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
        OSG_RGBA_DXT3                       = OSG_GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
        OSG_RGBA_DXT5                       = OSG_GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
        OSG_SRGB_DXT1                       = OSG_GL_COMPRESSED_SRGB_S3TC_DXT1_EXT,
        OSG_SRGB_ALPHA_DXT1                 = OSG_GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT,
        OSG_SRGB_ALPHA_DXT3                 = OSG_GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT,
        OSG_SRGB_ALPHA_DXT5                 = OSG_GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT,
        OSG_RED_RGTC1                       = OSG_GL_COMPRESSED_RED_RGTC1,
        OSG_SIGNED_RED_RGTC1                = OSG_GL_COMPRESSED_SIGNED_RED_RGTC1,
        OSG_RG_RGTC2                        = OSG_GL_COMPRESSED_RG_RGTC2,
        OSG_SIGNED_RG_RGTC2                 = OSG_GL_COMPRESSED_SIGNED_RG_RGTC2,
        OSG_RGBA_BPTC_UNORM                 = OSG_GL_COMPRESSED_RGBA_BPTC_UNORM_ARB,
        OSG_SRGB_ALPHA_BPTC_UNORM           = OSG_GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB,
        OSG_RGB_BPTC_SIGNED_FLOAT           = OSG_GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB,
        OSG_RGB_BPTC_UNSIGNED_FLOAT         = OSG_GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB,
        OSG_RGBA_ASTC_4x4                   = OSG_GL_COMPRESSED_RGBA_ASTC_4x4_KHR,
        OSG_RGBA_ASTC_5x4                   = OSG_GL_COMPRESSED_RGBA_ASTC_5x4_KHR,
        OSG_RGBA_ASTC_5x5                   = OSG_GL_COMPRESSED_RGBA_ASTC_5x5_KHR,
        OSG_RGBA_ASTC_6x5                   = OSG_GL_COMPRESSED_RGBA_ASTC_6x5_KHR,
        OSG_RGBA_ASTC_6x6                   = OSG_GL_COMPRESSED_RGBA_ASTC_6x6_KHR,
        OSG_RGBA_ASTC_8x5                   = OSG_GL_COMPRESSED_RGBA_ASTC_8x5_KHR,
        OSG_RGBA_ASTC_8x6                   = OSG_GL_COMPRESSED_RGBA_ASTC_8x6_KHR,
        OSG_RGBA_ASTC_8x8                   = OSG_GL_COMPRESSED_RGBA_ASTC_8x8_KHR,
        OSG_RGBA_ASTC_10x5                  = OSG_GL_COMPRESSED_RGBA_ASTC_10x5_KHR,
        OSG_RGBA_ASTC_10x6                  = OSG_GL_COMPRESSED_RGBA_ASTC_10x6_KHR,
        OSG_RGBA_ASTC_10x8                  = OSG_GL_COMPRESSED_RGBA_ASTC_10x8_KHR,
        OSG_RGBA_ASTC_10x10                 = OSG_GL_COMPRESSED_RGBA_ASTC_10x10_KHR,
        OSG_RGBA_ASTC_12x10                 = OSG_GL_COMPRESSED_RGBA_ASTC_12x10_KHR,
        OSG_RGBA_ASTC_12x12                 = OSG_GL_COMPRESSED_RGBA_ASTC_12x12_KHR,
        OSG_SRGB8_ALPHA8_ASTC_4x4           = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR,
        OSG_SRGB8_ALPHA8_ASTC_5x4           = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR,
        OSG_SRGB8_ALPHA8_ASTC_5x5           = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR,
        OSG_SRGB8_ALPHA8_ASTC_6x5           = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR,
        OSG_SRGB8_ALPHA8_ASTC_6x6           = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR,
        OSG_SRGB8_ALPHA8_ASTC_8x5           = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR,
        OSG_SRGB8_ALPHA8_ASTC_8x6           = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR,
        OSG_SRGB8_ALPHA8_ASTC_8x8           = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR,
        OSG_SRGB8_ALPHA8_ASTC_10x5          = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR,
        OSG_SRGB8_ALPHA8_ASTC_10x6          = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR,
        OSG_SRGB8_ALPHA8_ASTC_10x8          = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR,
        OSG_SRGB8_ALPHA8_ASTC_10x10         = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR,
        OSG_SRGB8_ALPHA8_ASTC_12x10         = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR,
        OSG_SRGB8_ALPHA8_ASTC_12x12         = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR,
        OSG_RGB8_ETC2                       = OSG_GL_COMPRESSED_RGB8_ETC2,
        OSG_SRGB8_ETC2                      = OSG_GL_COMPRESSED_SRGB8_ETC2,
        OSG_RGB8_PUNCHTHROUGH_ALPHA1_ETC2   = OSG_GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,
        OSG_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2  = OSG_GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2,
        OSG_RGBA8_ETC2_EAC                  = OSG_GL_COMPRESSED_RGBA8_ETC2_EAC,
        OSG_SRGB8_ALPHA8_ETC2_EAC           = OSG_GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,
        OSG_R11_EAC                         = OSG_GL_COMPRESSED_R11_EAC,
        OSG_SIGNED_R11_EAC                  = OSG_GL_COMPRESSED_SIGNED_R11_EAC,
        OSG_RG11_EAC                        = OSG_GL_COMPRESSED_RG11_EAC,
        OSG_SIGNED_RG11_EAC                 = OSG_GL_COMPRESSED_SIGNED_RG11_EAC,
        OSG_RGB_PVRTC_4BPPV1                = OSG_GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG,
        OSG_RGB_PVRTC_2BPPV1                = OSG_GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG,
        OSG_RGBA_PVRTC_4BPPV1               = OSG_GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG,
        OSG_RGBA_PVRTC_2BPPV1               = OSG_GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG,
        OSG_RGBA_PVRTC_4BPPV2               = OSG_GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG,
        OSG_RGBA_PVRTC_2BPPV2               = OSG_GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG,
        OSG_RGB8_ETC1                       = OSG_GL_COMPRESSED_RGB8_ETC1,
        OSG_SRGB_PVRTC_2BPPV1               = OSG_GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT,
        OSG_SRGB_PVRTC_4BPPV1               = OSG_GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT,
        OSG_SRGB_ALPHA_PVRTC_2BPPV1         = OSG_GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT,
        OSG_SRGB_ALPHA_PVRTC_4BPPV1         = OSG_GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT,
        OSG_SRGB_ALPHA_PVRTC_2BPPV2         = OSG_GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG,
        OSG_SRGB_ALPHA_PVRTC_4BPPV2         = OSG_GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG,

        OSG_DEPTH_PF                        =     GL_DEPTH_COMPONENT,
        OSG_DEPTH_STENCIL_PF                = OSG_GL_DEPTH_STENCIL,

        OSG_ALPHA_INTEGER_PF                =     GL_ALPHA_INTEGER,
        OSG_RGB_INTEGER_PF                  =     GL_RGB_INTEGER,
        OSG_RGBA_INTEGER_PF                 =     GL_RGBA_INTEGER,
        OSG_BGR_INTEGER_PF                  =     GL_BGR_INTEGER,
        OSG_BGRA_INTEGER_PF                 =     GL_BGRA_INTEGER,
        OSG_LUMINANCE_INTEGER_PF            =     GL_LUMINANCE_INTEGER_EXT,
        OSG_LUMINANCE_ALPHA_INTEGER_PF      =     GL_LUMINANCE_ALPHA_INTEGER_EXT
    };

    enum Type 
    {
        OSG_INVALID_IMAGEDATATYPE           = GL_NONE,
        OSG_UINT8_IMAGEDATA                 = GL_UNSIGNED_BYTE,
        OSG_UINT16_IMAGEDATA                = GL_UNSIGNED_SHORT,
        OSG_UINT32_IMAGEDATA                = GL_UNSIGNED_INT,
        OSG_FLOAT16_IMAGEDATA               = GL_HALF_FLOAT_NV,
        OSG_FLOAT32_IMAGEDATA               = GL_FLOAT,
        OSG_INT16_IMAGEDATA                 = GL_SHORT,
        OSG_INT32_IMAGEDATA                 = GL_INT,
        OSG_UINT24_8_IMAGEDATA              = OSG_GL_UNSIGNED_INT_24_8,
    };

    enum ResUnit 
    {
        OSG_RESUNIT_INVALID       = 0,
        OSG_RESUNIT_NONE          = 1,
        OSG_RESUNIT_INCH          = 2
    };

    enum ImageConversion 
    {
        OSG_CONVERT_NO_OP           = 0,
        OSG_CONVERT_TO_SRGB_SPACE   = 1,
        OSG_CONVERT_TO_LINEAR_SPACE = 2,
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Set Object Data                            */
    /*! \{                                                                 */

    bool set               (      UInt32    pixelFormat,
                                  Int32     width,
                                  Int32     height      = 1,
                                  Int32     depth       = 1,
                                  Int32     mipmapCount = 1,
                                  Int32     frameCount  = 1,
                                  Time      frameDelay  = 0.0,
                            const UInt8    *data        = 0,
                                  Int32     type        = OSG_UINT8_IMAGEDATA,
                                  bool      allocMem    = true,
                                  Int32     sidecount   = 1                  );
    bool set               (      Image    *image                            );
    bool setData           (const UInt8    *data = 0                         );
    void clearData         (      void                                       );
    bool setSubData        (      Int32     offX, 
                                  Int32     offY, 
                                  Int32     offZ,
                                  Int32     srcW, 
                                  Int32     srcH, 
                                  Int32     srcD,
                            const UInt8    *data                             );
    bool flipDepthFrameData(      void                                       );


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Add Value                                */
    /*! \{                                                                 */

    bool addValue(const Char8 *value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Reformate                                */
    /*! \{                                                                 */

    bool reformat(const PixelFormat  pixelFormat,
                        Image       *destination       = NULL,
                        Int32        iCompressionFlags = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Convert dataType                          */
    /*! \{                                                                 */

    void swapDataEndian   (void                                    );
    bool convertDataTypeTo(Int32 destDataType = OSG_UINT8_IMAGEDATA);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Scale                                  */
    /*! \{                                                                 */

    bool scale          (Int32  width, 
                         Int32  height      = 1,
                         Int32  depth       = 1,
                         Image *destination = NULL);
    bool scaleNextPower2(Image *destination = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Mirror                                  */
    /*! \{                                                                 */

    bool mirror         (bool   horizontal,
                         bool   vertical,
                         bool   flipDepth   = false,
                         Image *destination = NULL  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      SubImage                                */
    /*! \{                                                                 */

    bool subImage(Int32  offX, 
                  Int32  offY, 
                  Int32  offZ,
                  Int32  destW, 
                  Int32  destH, 
                  Int32  destD,
                  Image *destination = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      SubImage                                */
    /*! \{                                                                 */

    ImageTransitPtr placeSubImage(Int32   srcOffX,
                                  Int32   srcOffY,
                                  Int32   srcOffZ,
                                  Int32   srcRectW,
                                  Int32   srcRectH,
                                  Int32   srcRectD,
                                  Int32   dstOffX,
                                  Int32   dstOffY,
                                  Int32   dstOffZ,
                                  Int32   destW,
                                  Int32   destH,
                                  Int32   destD,
                                  Image*  destination = NULL);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Slice                                   */
    /*! \{                                                                 */

    bool slice(Int32  offX = -1, 
               Int32  offY = -1, 
               Int32  offZ = -1,
               Image *destination = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      copyComponent                           */
    /*! \{                                                                 */

    bool copyComponent  (Image* srcImage, 
                         UInt8  srcComponent, 
                         UInt8  dstComponent,
                         UInt32 format = OSG_INVALID_PF);

    bool copyComponents (Image* srcImage, 
                         std::vector<UInt8> vecSrcComponents, 
                         std::vector<UInt8> vecDstComponents, 
                         UInt32 format = OSG_INVALID_PF);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      flipComponent                           */
    /*! \{                                                                 */

    bool flipComponent(UInt8 component, bool sRGB);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      convertColorSpace                       */
    /*! \{                                                                 */

    bool convertImage(UInt8 component, ImageConversion task);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      setComponent                            */
    /*! \{                                                                 */

    bool setComponent(UInt8 component, Real64 value, bool sRGB);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Mipmap                                  */
    /*! \{                                                                 */

    bool createMipmap(Int32  level       = -1, 
                      Image *destination = NULL);

    bool removeMipmap(void                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    bool write(const Char8 *fileName);
    bool read (const Char8 *fileName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Storage/Restore                              */
    /*! \{                                                                 */

    UInt64 store  (const Char8 *mimeType, 
                         UInt8 *mem, 
                         Int32  memSize = -1);
    UInt64 restore(const UInt8 *mem, 
                         Int32  memSize = -1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Comparison/Assign                              */
    /*! \{                                                                 */

    Image &operator =  (const Image &image);
    bool   operator <  (const Image &image);
    bool   operator == (const Image &image);
    bool   operator != (const Image &image);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get  Methods                              */
    /*! \{                                                                 */

    bool   isValid          (void) const;
    bool   hasAlphaChannel  (void);
    bool   isAlphaBinary    (void);
    bool   hasColorChannel  (void);
    bool   hasCompressedData(void);
    UInt8  getComponents    (void) const;
    
    bool   calcIsAlphaBinary(void);

    SizeT  getHash          (bool force = false) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Size                                    */
    /*! \{                                                                 */

    unsigned long getSize(bool withMipmap = true,
                          bool withFrames = true,
                          bool withSides  = true) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get Methods                                */
    /*! \{                                                                 */

    const UInt8 *getData       (UInt32 mipmapNum = 0,
                                UInt32 frameNum  = 0,
                                UInt32 sidecount = 0) const;
          UInt8 *editData      (UInt32 mipmapNum = 0,
                                UInt32 frameNum  = 0,
                                UInt32 sidecount = 0);

    const UInt8 *getDataFast   (UInt32 mipmapNum = 0,
                                UInt32 frameNum  = 0,
                                UInt32 sidecount = 0);
          UInt8 *editDataFast  (UInt32 mipmapNum = 0,
                                UInt32 frameNum  = 0,
                                UInt32 sidecount = 0);

    const UInt8 *getDataByTime (Time   time, 
                                UInt32 mipmapNum = 1) const;
          UInt8 *editDataByTime(Time   time, 
                                UInt32 mipmapNum = 1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Calculate                               */
    /*! \{                                                                 */

    void   calcMipmapGeometry  (UInt32 mipmapNum,
                                UInt32 &width,
                                UInt32 &height,
                                UInt32 &depth     ) const;
    UInt32 calcMipmapLevelCount(void              ) const;
    UInt32 calcFrameNum        (Time    time, 
                                bool    loop = true) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Clear Image                                */
    /*! \{                                                                 */

    virtual void clear     (UChar8 pixelValue = 0            );
    virtual void clearFloat(Real32 pixelValue = 0.0          );
    virtual void clearHalf (Real16 pixelValue = Real16( 0.0 ));

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               attachment handling                            */
    /*! \{                                                                 */

    bool               hasAttachment      (      void             ) const;
    UInt32             attachmentCount    (      void             ) const;
    void               setAttachmentField (const std::string &key,
                                           const std::string &data);
    const std::string *findAttachmentField(const std::string &key ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Calculate Mipmap Size                          */
    /*! \{                                                                 */

    UInt32 calcMipmapLevelSize(UInt32 mipmapNum,
                               UInt32 w, 
                               UInt32 h, 
                               UInt32 d        ) const;
    UInt32 calcMipmapLevelSize(UInt32 mipmapNum) const;

    UInt32 calcMipmapSumSize  (UInt32 mipmapNum,
                               UInt32 w, 
                               UInt32 h, 
                               UInt32 d        ) const;
    UInt32 calcMipmapSumSize  (UInt32 mipmapNum) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Don't know yet                        */
    /*! \{                                                                 */

#if 0
    void imageContentChanged(Int32 minX = -1, Int32 maxX = -1,
                             Int32 minY = -1, Int32 maxY = -1,
                             Int32 minZ = -1, Int32 maxZ = -1 );
#endif    

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    std::vector<Int32> _mipmapOffset;
    mutable SizeT      _hash;
    mutable bool       _hashValid;

    /*---------------------------------------------------------------------*/
    /*! \name                  static element                              */
    /*! \{                                                                 */

    struct FormatInfo
    {
        UInt32 format;
        UInt8  blockSize;
        Vec3ub blockExtent;
        UInt8  component;
    };

    static const FormatInfo& getFormatInfo(UInt32 format);

    static UInt32       _formatDic[][2];
    static Int32        _typeDic  [][2];
    static FormatInfo   _formatInfoDic[];

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Image(void);
    Image(const Image &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Image(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                   Image Data                                 */
    /*! \{                                                                 */

    bool createData       (const UInt8 *data, 
                                 bool   allocMem = true  );
    bool scaleData        (const UInt8 *srcData,
                                 Int32  srcW, 
                                 Int32  srcH, 
                                 Int32  srcD,
                                 UInt8 *destData,
                                 Int32  destW, 
                                 Int32  destH, 
                                 Int32  destD            );

    void calcMipmapOffsets(      void                    );
    void calcHash         (      void                    ) const;

    bool mirrorData       (const UInt8 *srcData,
                                 UInt8 *destData,
                                 Int32  width,
                                 Int32  height,
                                 Int32  depth,
                                 bool   horizontal,
                                 bool   vertical,
                                 bool   flipDepth = false);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Helper                                 */
    /*! \{                                                                 */

    UInt32 calcMipmapLevelSize(const FormatInfo& info,
                               UInt32 mipmapNum,
                               UInt32 w, 
                               UInt32 h, 
                               UInt32 d        ) const;
    UInt32 calcMipmapLevelSize(const FormatInfo& info,
                               UInt32 mipmapNum) const;

    UInt32 calcMipmapSumSize  (const FormatInfo& info,
                               UInt32 mipmapNum,
                               UInt32 w, 
                               UInt32 h, 
                               UInt32 d        ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    friend class FieldContainer;
    friend class ImageBase;
};

typedef Image *ImageP;

OSG_END_NAMESPACE

#include "OSGImageBase.inl"
#include "OSGImage.inl"

#endif /* _OSGIMAGE_H_ */
