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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#ifdef OSG_WITH_JPG
extern "C" 
{

#ifdef WIN32
#define __WIN32__
#endif

#include <setjmp.h>
#include <jpeglib.h>
}
#endif

#ifdef   OSG_SGI_LIB
#include <limits>
#endif
#include "OSGJPGImageFileType.h"
#include "OSGLog.h"

#ifndef OSG_DO_DOC
#    ifdef OSG_WITH_JPG
#        define OSG_JPG_ARG(ARG) ARG
#    else
#        define OSG_JPG_ARG(ARG)
#    endif
#else
#    define OSG_JPG_ARG(ARG) ARG
#endif

// Static Class Varible implementations:
static const OSG::Char8 *suffixArray[] = { "jpg", 
                                           "jpeg", 
                                           "jpe", 
                                           "jfif" };

OSG_BEGIN_NAMESPACE

/*! \class JPGImageFileType 

  Image File Type to read/write and store/restore Image objects as
  JPEG data.
  
  To be able to load JPEG images you need the IJG JPEG library, 
  version 6 or later (check the Prerequisites page on www.opensg.org). 
  The lib comes with all Linux distributions.
  
  You have to --enable-jpg in the configure line to enable
  the singleton object.
    
*/

#ifdef OSG_WITH_JPG

static const unsigned long BUFFERSIZE = 4096;

struct SourceManager
{
    struct jpeg_source_mgr pub;
    std::istream *is;
    char *buffer;
    SourceManager(j_decompress_ptr cinfo, std::istream &iStream);
};

static void istream_init_source(j_decompress_ptr cinfo)
{
} // no action necessary

static boolean istream_fill_input_buffer(j_decompress_ptr cinfo)
{
    SourceManager *sourceManager = 
        reinterpret_cast<SourceManager*>(cinfo->src);

    sourceManager->is->read(sourceManager->buffer, BUFFERSIZE);
    
    cinfo->src->next_input_byte = 
        reinterpret_cast<const JOCTET *>(sourceManager->buffer);
    
    if (sourceManager->is->gcount() == 0)
    {
        /* Insert a fake EOI marker */
        sourceManager->buffer[0] = JOCTET(0xFF);
        sourceManager->buffer[1] = JOCTET(JPEG_EOI);
        cinfo->src->bytes_in_buffer = 2;
    }
    else
    {
        cinfo->src->bytes_in_buffer = sourceManager->is->gcount();
    }

    return TRUE;
}

static void istream_skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{
    if (static_cast<unsigned long>(num_bytes) <= cinfo->src->bytes_in_buffer)
    {
        cinfo->src->bytes_in_buffer -= num_bytes;
        cinfo->src->next_input_byte += num_bytes;
    }
    else
    {
        num_bytes -= long(cinfo->src->bytes_in_buffer);
        SourceManager *sourceManager = 
            reinterpret_cast<SourceManager*>(cinfo->src);
        sourceManager->is->ignore(num_bytes);
        cinfo->src->bytes_in_buffer = 0;
        cinfo->src->next_input_byte = 0;
    }
}

static void istream_term_source(j_decompress_ptr cinfo) {} // no action necessary

SourceManager::SourceManager(j_decompress_ptr cinfo, std::istream &iStream):
    pub   (    ),
    is    (NULL),
    buffer(NULL)
{
    pub.init_source = istream_init_source;
    pub.fill_input_buffer = istream_fill_input_buffer;
    pub.skip_input_data = istream_skip_input_data;
    pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
    pub.term_source = istream_term_source;
    pub.bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
    pub.next_input_byte = 0; /* until buffer loaded */
    this->is = &iStream;
    buffer = static_cast<char*>((*cinfo->mem->alloc_small)(j_common_ptr(cinfo), 
                                                           JPOOL_IMAGE, 
                                                           BUFFERSIZE));
}

struct DestinationManager
{
    struct jpeg_destination_mgr pub;
    std::ostream *os;
    char *buffer;
    DestinationManager(j_compress_ptr cinfo, std::ostream &oStream);
};

static void ostream_init_destination(j_compress_ptr cinfo)
{
    DestinationManager* dest= 
        reinterpret_cast<DestinationManager*>(cinfo->dest);

    // Allocate the output buffer --- it will be released when done with image
    dest->buffer = static_cast<char *>(
        (*cinfo->mem->alloc_small)(j_common_ptr(cinfo), JPOOL_IMAGE, 
                                   BUFFERSIZE * sizeof(char)));

    dest->pub.next_output_byte = reinterpret_cast<JOCTET *>(dest->buffer);
    dest->pub.free_in_buffer = BUFFERSIZE;
}

static boolean ostream_empty_output_buffer(j_compress_ptr cinfo)
{
    DestinationManager *destinationManager = 
        reinterpret_cast<DestinationManager*>(cinfo->dest);

    destinationManager->os->write(
        static_cast<char *>(destinationManager->buffer),
        BUFFERSIZE);

    destinationManager->pub.next_output_byte = 
        reinterpret_cast<JOCTET *>(destinationManager->buffer);
    destinationManager->pub.free_in_buffer = BUFFERSIZE;

    return destinationManager->os->good() != false ? TRUE : FALSE;
}

static void ostream_term_destination(j_compress_ptr cinfo)
{
    DestinationManager* dest = 
        reinterpret_cast<DestinationManager*>(cinfo->dest);
    
    size_t datacount = BUFFERSIZE - dest->pub.free_in_buffer;
    // Write any data remaining in the buffer
    if (datacount > 0)
    {
        dest->os->write(static_cast<char *>(dest->buffer), datacount);
    }
}

DestinationManager::DestinationManager(j_compress_ptr cinfo, 
                                       std::ostream &oStream):
    pub   (    ),
    os    (NULL),
    buffer(NULL)
{
    pub.init_destination = ostream_init_destination;
    pub.empty_output_buffer = ostream_empty_output_buffer;
    pub.term_destination = ostream_term_destination;
    this->os = &oStream;
    buffer = static_cast<char *>(
        (*cinfo->mem->alloc_small)(j_common_ptr(cinfo), 
                                   JPOOL_IMAGE, 
                                   BUFFERSIZE));
    pub.free_in_buffer = BUFFERSIZE;
    pub.next_output_byte = reinterpret_cast<JOCTET *>(buffer);
}

struct osg_jpeg_error_mgr
{
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};

static void osg_jpeg_error_exit(j_common_ptr cinfo)
{
    /* Always display the message */
    (*cinfo->err->output_message) (cinfo);

    /* Let the memory manager delete any temp files before we die */
    jpeg_destroy(cinfo);

    /* Return control to the setjmp point */
    struct osg_jpeg_error_mgr *osgerr = 
        reinterpret_cast<struct osg_jpeg_error_mgr *>(cinfo->err);
    longjmp(osgerr->setjmp_buffer, 1);
}

static void osg_jpeg_output_message(j_common_ptr cinfo)
{
    char buffer[JMSG_LENGTH_MAX];

    /* Create the message */
    (*cinfo->err->format_message) (cinfo, buffer);

    /* Send it to the OSG logger, adding a newline */
    FFATAL (("JPG: %s\n", buffer));
}

struct jpeg_mem
{
    struct jpeg_destination_mgr dest;
    struct jpeg_source_mgr      src;
    UChar8                      *buffer;
    UInt32                      memSize;
    UInt32                      dataSize;
} jpeg_mem;

/* */
static void jpeg_mem_init_source(j_decompress_ptr OSG_CHECK_ARG(cinfo))
{
    jpeg_mem.src.next_input_byte = static_cast<JOCTET *>(jpeg_mem.buffer);
    jpeg_mem.src.bytes_in_buffer = size_t(jpeg_mem.dataSize);
}

/* */

static boolean jpeg_mem_fill_input_buffer(
    j_decompress_ptr OSG_CHECK_ARG(cinfo))
{
    SFATAL << "Missing data. Given data block to small." << std::endl;
    return false;
}

/* */
static void jpeg_mem_skip_input_data(j_decompress_ptr OSG_CHECK_ARG(cinfo    ),
                                     long                           num_bytes)
{
    jpeg_mem.src.next_input_byte += num_bytes;
    jpeg_mem.src.bytes_in_buffer -= num_bytes;
}

/* */
static boolean jpeg_mem_resync_to_restart(
    j_decompress_ptr OSG_CHECK_ARG(cinfo  ),
    int              OSG_CHECK_ARG(desired))
{
    return false;
}

/* */
static void jpeg_mem_term_source(j_decompress_ptr OSG_CHECK_ARG(cinfo))
{
}

/* */
static void jpeg_mem_init_destination(j_compress_ptr OSG_CHECK_ARG(cinfo))
{
    jpeg_mem.dest.next_output_byte = static_cast<JOCTET *>(jpeg_mem.buffer);
    jpeg_mem.dest.free_in_buffer = size_t(jpeg_mem.memSize);
}

/* */
static boolean jpeg_mem_empty_output_buffer(
    j_compress_ptr OSG_CHECK_ARG(cinfo))
{
    SFATAL << "Not enough space left in buffer." << std::endl;
    return false;
}

/* */
static void jpeg_mem_term_destination(j_compress_ptr OSG_CHECK_ARG(cinfo))
{
    jpeg_mem.dataSize = 
        (static_cast<UChar8 *>(jpeg_mem.dest.next_output_byte)) - 
        (static_cast<UChar8 *>(jpeg_mem.buffer));
}

/* */
static void jpeg_memory_dest(struct jpeg_compress_struct *cinfo, 
                                    UChar8               *buffer,
                                    UInt32                memSize)
{
    jpeg_mem.buffer=buffer;
    jpeg_mem.memSize=memSize;
    jpeg_mem.dest.init_destination    = jpeg_mem_init_destination;
    jpeg_mem.dest.empty_output_buffer = jpeg_mem_empty_output_buffer;
    jpeg_mem.dest.term_destination    = jpeg_mem_term_destination;

    cinfo->dest=&jpeg_mem.dest;
}

/* */
static void jpeg_memory_src(      struct jpeg_decompress_struct *cinfo, 
                            const        UChar8                 *buffer,
                                         UInt32                  dataSize)
{
    jpeg_mem.buffer = const_cast < UChar8 * > (buffer);
    jpeg_mem.dataSize = dataSize;

    jpeg_mem.src.init_source       = jpeg_mem_init_source;
    jpeg_mem.src.fill_input_buffer = jpeg_mem_fill_input_buffer;
    jpeg_mem.src.skip_input_data   = jpeg_mem_skip_input_data;
    jpeg_mem.src.resync_to_restart = jpeg_mem_resync_to_restart;
    jpeg_mem.src.term_source       = jpeg_mem_term_source;
    cinfo->src = &jpeg_mem.src;
}
#endif

JPGImageFileType JPGImageFileType:: _the("image/jpeg",
                                         suffixArray, sizeof(suffixArray),
                                         (OSG_READ_SUPPORTED | 
                                          OSG_WRITE_SUPPORTED));

void JPGImageFileType::setQuality(UInt32 cl)
{
    if(cl > 100)
        cl = 100;
    
    _quality = cl;
}

UInt32 JPGImageFileType::getQuality(void)
{
    return _quality;
}

#ifdef OSG_DEBUG_OLD_C_CASTS
#ifdef jpeg_create_compress
#undef jpeg_create_compress
#endif
#ifdef jpeg_create_decompress
#undef jpeg_create_decompress
#endif

#define jpeg_create_compress(cinfo) \
    jpeg_CreateCompress((cinfo), JPEG_LIB_VERSION, \
                        size_t(sizeof(struct jpeg_compress_struct)))
#define jpeg_create_decompress(cinfo) \
    jpeg_CreateDecompress((cinfo), JPEG_LIB_VERSION, \
                          size_t(sizeof(struct jpeg_decompress_struct)))
#endif

static Int32 calcQuality(jpeg_decompress_struct* cinfo)
{
    Int32 quality = -1;

    if (!cinfo)
        return quality;

    std::size_t qvalue;
    std::size_t sum = 0;

    for (std::size_t i = 0; i < NUM_QUANT_TBLS; ++i)
    {
        if (cinfo->quant_tbl_ptrs[i] != NULL)
        {
            for (std::size_t j = 0; j < DCTSIZE2; ++j)
            {
                sum += cinfo->quant_tbl_ptrs[i]->quantval[j];
            }
        }
    }

    quality = 0;

    const std::size_t cnEntries = 101;

    if ((cinfo->quant_tbl_ptrs[0] != NULL) && (cinfo->quant_tbl_ptrs[1] != NULL))
    {
        std::size_t hash[cnEntries] = {
            1020, 1015,  932,  848,  780,  735,  702,  679,  660,  645,
             632,  623,  613,  607,  600,  594,  589,  585,  581,  571,
             555,  542,  529,  514,  494,  474,  457,  439,  424,  410,
             397,  386,  373,  364,  351,  341,  334,  324,  317,  309,
             299,  294,  287,  279,  274,  267,  262,  257,  251,  247,
             243,  237,  232,  227,  222,  217,  213,  207,  202,  198,
             192,  188,  183,  177,  173,  168,  163,  157,  153,  148,
             143,  139,  132,  128,  125,  119,  115,  108,  104,   99,
              94,   90,   84,   79,   74,   70,   64,   59,   55,   49,
              45,   40,   34,   30,   25,   20,   15,   11,    6,    4,
               0 };

        std::size_t sums[cnEntries] = {
            32640, 32635, 32266, 31495, 30665, 29804, 29146, 28599, 28104, 27670,
            27225, 26725, 26210, 25716, 25240, 24789, 24373, 23946, 23572, 22846,
            21801, 20842, 19949, 19121, 18386, 17651, 16998, 16349, 15800, 15247,
            14783, 14321, 13859, 13535, 13081, 12702, 12423, 12056, 11779, 11513,
            11135, 10955, 10676, 10392, 10208,  9928,  9747,  9564,  9369,  9193,
             9017,  8822,  8639,  8458,  8270,  8084,  7896,  7710,  7527,  7347,
             7156,  6977,  6788,  6607,  6422,  6236,  6054,  5867,  5684,  5495,
             5305,  5128,  4945,  4751,  4638,  4442,  4248,  4065,  3888,  3698,
             3509,  3326,  3139,  2957,  2775,  2586,  2405,  2216,  2037,  1846,
             1666,  1483,  1297,  1109,   927,   735,   554,   375,   201,   128,
                0 };

        qvalue = static_cast<std::size_t>(
                        cinfo->quant_tbl_ptrs[0]->quantval[ 2]
                      + cinfo->quant_tbl_ptrs[0]->quantval[53]
                      + cinfo->quant_tbl_ptrs[1]->quantval[ 0]
                      + cinfo->quant_tbl_ptrs[1]->quantval[DCTSIZE2-1]);

        for (std::size_t i = 0; i < cnEntries-1; i++)
        {
            if (qvalue < hash[i] && sum < sums[i])
                continue;
          
            if ((qvalue <= hash[i] && sum <= sums[i]) || i >= 50)
                quality = static_cast<Int32>(i + 1);

            break;
        }
    }
    else
    {
        if (cinfo->quant_tbl_ptrs[0] != NULL)
        {
            std::size_t hash[cnEntries] = {
                510,  505,  422,  380,  355,  338,  326,  318,  311,  305,
                300,  297,  293,  291,  288,  286,  284,  283,  281,  280,
                279,  278,  277,  273,  262,  251,  243,  233,  225,  218,
                211,  205,  198,  193,  186,  181,  177,  172,  168,  164,
                158,  156,  152,  148,  145,  142,  139,  136,  133,  131,
                129,  126,  123,  120,  118,  115,  113,  110,  107,  105,
                102,  100,   97,   94,   92,   89,   87,   83,   81,   79,
                 76,   74,   70,   68,   66,   63,   61,   57,   55,   52,
                 50,   48,   44,   42,   39,   37,   34,   31,   29,   26,
                 24,   21,   18,   16,   13,   11,    8,    6,    3,    2,
                  0 };

            std::size_t  sums[cnEntries] = {
                16320, 16315, 15946, 15277, 14655, 14073, 13623, 13230, 12859, 12560,
                12240, 11861, 11456, 11081, 10714, 10360, 10027,  9679,  9368,  9056,
                 8680,  8331,  7995,  7668,  7376,  7084,  6823,  6562,  6345,  6125,
                 5939,  5756,  5571,  5421,  5240,  5086,  4976,  4829,  4719,  4616,
                 4463,  4393,  4280,  4166,  4092,  3980,  3909,  3835,  3755,  3688,
                 3621,  3541,  3467,  3396,  3323,  3247,  3170,  3096,  3021,  2952,
                 2874,  2804,  2727,  2657,  2583,  2509,  2437,  2362,  2290,  2211,
                 2136,  2068,  1996,  1915,  1858,  1773,  1692,  1620,  1552,  1477,
                 1398,  1326,  1251,  1179,  1109,  1031,   961,   884,   814,   736,
                  667,   592,   518,   441,   369,   292,   221,   151,    86,    64,
                    0 };

            qvalue = static_cast<std::size_t>(
                        cinfo->quant_tbl_ptrs[0]->quantval[2]
                      + cinfo->quant_tbl_ptrs[0]->quantval[53]);

            for (std::size_t i = 0; i < cnEntries-1; ++i)
            {
                if (qvalue < hash[i] && sum < sums[i])
                    continue;

                if ((qvalue <= hash[i] && sum <= sums[i]) || i >= 50)
                    quality = static_cast<Int32>(i + 1);

                break;
            }
        }
    }

    return quality;
}

//-------------------------------------------------------------------------
/*!
  Tries to fill the image object with the data read from
  the given stream. Returns true on success.
*/

bool JPGImageFileType::read(      Image        *OSG_JPG_ARG(pImage  ), 
                                  std::istream &OSG_JPG_ARG(is      ),
                            const std::string  &OSG_JPG_ARG(mimetype))
{
#ifdef OSG_WITH_JPG

    struct osg_jpeg_error_mgr jerr;
    struct jpeg_decompress_struct cinfo;

    cinfo.err = jpeg_std_error(&jerr.pub);
    if (setjmp(jerr.setjmp_buffer))
        return false;
    cinfo.err->error_exit = osg_jpeg_error_exit;
    cinfo.err->output_message = osg_jpeg_output_message;

    jpeg_create_decompress(&cinfo);

    SourceManager *sourceManager =
        new ((*cinfo.mem->alloc_small)(j_common_ptr(&cinfo), 
                                       JPOOL_IMAGE, 
                                       sizeof(SourceManager)))
        SourceManager(&cinfo, is);

    cinfo.src = reinterpret_cast<jpeg_source_mgr *>(sourceManager);

    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    _quality = calcQuality(&cinfo);

    Image::PixelFormat pixelFormat;

    switch (cinfo.output_components)
    {
        case 1:
            pixelFormat = Image::OSG_L_PF;
            break;
        case 3:
            pixelFormat = Image::OSG_RGB_PF;
            break;
        default:
            pixelFormat = Image::OSG_INVALID_PF;
            break;
    };
    
    bool retCode;
    
    if(pImage->set(pixelFormat, 
                   cinfo.output_width, 
                   cinfo.output_height) == true)
    {
        Real32 res_x = Real32(cinfo.X_density);
        Real32 res_y = Real32(cinfo.Y_density);
        UInt16 res_unit = UInt16(cinfo.density_unit);
        if(res_unit == 2) // centimeter
        {
            // convert dpcm to dpi.
            res_x *= 2.54f;
            res_y *= 2.54f;
            res_unit = Image::OSG_RESUNIT_INCH;
        }
        pImage->setResX(res_x);
        pImage->setResY(res_y);
        pImage->setResUnit(res_unit);

        unsigned char *destData = pImage->editData() + pImage->getSize();

        int row_stride = cinfo.output_width * cinfo.output_components;

        while (cinfo.output_scanline < cinfo.output_height)
        {
            destData -= row_stride;
            jpeg_read_scanlines(&cinfo, &destData, 1);
        }
        retCode = true;
    }
	else
    {
		retCode = false;
    }

    jpeg_finish_decompress (&cinfo);
    jpeg_destroy_decompress(&cinfo);

	return retCode;

#else

    SWARNING << getMimeType()
             << " read is not compiled into the current binary " 
             << std::endl;

    return false;

#endif
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given stream.
    Returns true on success.
*/

bool JPGImageFileType::write(const Image        *OSG_JPG_ARG(pImage  ), 
                                   std::ostream &OSG_JPG_ARG(os      ),
                             const std::string  &OSG_JPG_ARG(mimetype))
{
#ifdef OSG_WITH_JPG

    if((pImage->getBpp() != 1 && 
        pImage->getBpp() != 3) || pImage->getDepth() != 1)
    {
        SWARNING << getMimeType() 
                 << " JPEG write only works for 2D 1 or 3 bpp images " 
                 << std::endl;

        return false;
    }

    struct osg_jpeg_error_mgr jerr;
    struct jpeg_compress_struct cinfo;

    cinfo.err = jpeg_std_error(&jerr.pub);

    if (setjmp(jerr.setjmp_buffer))
        return false;
    cinfo.err->error_exit     = osg_jpeg_error_exit;
    cinfo.err->output_message = osg_jpeg_output_message;

    jpeg_create_compress(&cinfo);

    DestinationManager *destinationManager =
        new ((*cinfo.mem->alloc_small)(j_common_ptr(&cinfo), 
                                       JPOOL_IMAGE, 
                                       sizeof(DestinationManager)))
        DestinationManager(&cinfo, os);

    cinfo.dest             =
        reinterpret_cast<jpeg_destination_mgr*>(destinationManager);
    cinfo.image_width      = pImage->getWidth();
    cinfo.image_height     = pImage->getHeight();
    cinfo.input_components = pImage->getBpp();
    cinfo.in_color_space   = (pImage->getBpp() == 1) ? JCS_GRAYSCALE : JCS_RGB;

    jpeg_set_defaults(&cinfo);

    cinfo.density_unit = 1;  // dpi
    cinfo.X_density    = UInt16(pImage->getResX() < 0.0f ?
                                pImage->getResX() - 0.5f :
                                pImage->getResX() + 0.5f);
    cinfo.Y_density    = UInt16(pImage->getResY() < 0.0f ?
                                pImage->getResY() - 0.5f :
                                pImage->getResY() + 0.5f);

    jpeg_set_quality   (&cinfo, _quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    unsigned char *srcData = 
        const_cast<UInt8 *>(pImage->getData()) + pImage->getSize();
    int row_stride = cinfo.image_width * cinfo.input_components;

    while (cinfo.next_scanline < cinfo.image_height)
    {
        srcData -= row_stride;
        jpeg_write_scanlines(&cinfo, &srcData, 1);
    }

    jpeg_finish_compress (&cinfo);
    jpeg_destroy_compress(&cinfo);

    return true;
#else

    SWARNING << getMimeType() 
             << " write is not compiled into the current binary " 
             << std::endl;

	return false;

#endif
}

//-------------------------------------------------------------------------
/*!
  Tries to determine the mime type of the data provided by an input stream
  by searching for magic bytes. Returns the mime type or an empty string
  when the function could not determine the mime type.
 */

std::string JPGImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[2];

    is.read(filecode, 2);
    is.seekg(-2, std::ios::cur);

    return strncmp(filecode, "\xff\xd8", 2) == 0 ?
        std::string(getMimeType()) : std::string();
}


bool JPGImageFileType::validateHeader(const Char8 *fileName, 
                                            bool  &implemented)
{
    implemented = true;

    if(fileName == NULL)
        return false;

    FILE *file = fopen(fileName, "rb");

    if(file == NULL)
        return false;

    UInt16 magic = 0;

    fread(static_cast<void *>(&magic), sizeof(magic), 1, file);

    fclose(file);

#if BYTE_ORDER == LITTLE_ENDIAN
    if(magic == 0xd8ff) // the magic header is big endian need to swap it.
#else
    if(magic == 0xffd8)
#endif
    {
        return true;
    }

    return false;
}


UInt64 JPGImageFileType::restoreData(      Image  *OSG_JPG_ARG(pImage ), 
                                     const UChar8 *OSG_JPG_ARG(buffer ),
                                           Int32   OSG_JPG_ARG(memSize)) const
{
#ifdef OSG_WITH_JPG
    UInt64 retCode = 0;

    struct local_error_mgr
    {
        struct jpeg_error_mgr   pub;
        jmp_buf                 setjmp_buffer;
    };

    unsigned char                  *destData;
    Image::PixelFormat              pixelFormat = Image::OSG_INVALID_PF;

    unsigned long                    imageSize;
    struct local_error_mgr          jerr;
    struct jpeg_decompress_struct   cinfo;
    JSAMPARRAY                      imagebuffer;

    int                             row_stride;

    cinfo.err = jpeg_std_error(&jerr.pub);

    if(setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_decompress(&cinfo);

        return 0;
    }

    jpeg_create_decompress(&cinfo);
    jpeg_memory_src(&cinfo, buffer, memSize);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    switch(cinfo.output_components)
    {
        case 1:
            pixelFormat = Image::OSG_L_PF;
            break;
        case 2:
            pixelFormat = Image::OSG_LA_PF;
            break;
        case 3:
            pixelFormat = Image::OSG_RGB_PF;
            break;
        case 4:
            pixelFormat = Image::OSG_RGBA_PF;
            break;
    };

    if(pImage->set(pixelFormat, cinfo.output_width, cinfo.output_height))
    {
        imageSize = pImage->getSize();
        destData = pImage->editData() + imageSize;
        row_stride = cinfo.output_width * cinfo.output_components;

        imagebuffer = (*cinfo.mem->alloc_sarray) (j_common_ptr(&cinfo), 
                                                  JPOOL_IMAGE, 
                                                  row_stride, 
                                                  1);

        while(cinfo.output_scanline < cinfo.output_height)
        {
            destData -= row_stride;
            jpeg_read_scanlines(&cinfo, imagebuffer, 1);
            memcpy(destData, *imagebuffer, row_stride);
        }
        
        retCode = imageSize;
    }
    else
    {
        retCode = 0;
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return retCode;
#else
    SWARNING << getMimeType() 
             << " read is not compiled into the current binary " 
             << std::endl;

    return 0;
#endif
}

//-------------------------------------------------------------------------
/*!
Tries to restore the image data from the given memblock.
Returns the amount of data read.
*/
UInt64 JPGImageFileType::storeData(const Image  *OSG_JPG_ARG(pImage ), 
                                         UChar8 *OSG_JPG_ARG(buffer ),
                                         Int32   OSG_JPG_ARG(memSize)) const
{
#ifdef OSG_WITH_JPG
    if((pImage->getBpp  () != 1 && pImage->getBpp() != 3) ||
       (pImage->getDepth() != 1)                          )
    {
        SWARNING << getMimeType() 
                 << " JPEG storeData only works for 2D 1 or 3 bpp images " 
                 << std::endl;

        return 0;
    }

    struct local_error_mgr
    {
        struct jpeg_error_mgr   pub;
        jmp_buf                 setjmp_buffer;
    };

    struct local_error_mgr          jerr;
    struct jpeg_compress_struct     cinfo;
    JSAMPARRAY                      imagebuffer;
    UChar8                          *data;

    cinfo.err = jpeg_std_error(&jerr.pub);

    if(setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_compress(&cinfo);

        return 0;
    }

    jpeg_create_compress(&cinfo);
    jpeg_memory_dest    (&cinfo, buffer, memSize);

    cinfo.image_width = pImage->getWidth();
    cinfo.image_height = pImage->getHeight();
    cinfo.input_components = pImage->getBpp();
    cinfo.in_color_space = (pImage->getBpp() == 1) ? JCS_GRAYSCALE : JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, _quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    imagebuffer = &data;

    while(cinfo.next_scanline < cinfo.image_height)
    {
        data = 
            const_cast<UInt8 *>(pImage->getData()) +
            (pImage->getHeight() - 1 - cinfo.next_scanline) *
            pImage->getWidth() *
            pImage->getBpp();

        jpeg_write_scanlines(&cinfo, imagebuffer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    return jpeg_mem.dataSize;
#else
    SWARNING << getMimeType() 
             << " write is not compiled into the current binary " 
             << std::endl;

    return 0;
#endif
}

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

JPGImageFileType::JPGImageFileType(const Char8  *mimeType,
                                   const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         UInt32  flags) :

     Inherited(mimeType, 
               suffixArray, 
               suffixByteCount, 
               flags),
    _quality(90)
{
}

//-------------------------------------------------------------------------
/*! Dummy Copy Constructor
 */

//-------------------------------------------------------------------------
/*!
 */

JPGImageFileType::~JPGImageFileType(void)
{
}

OSG_END_NAMESPACE
