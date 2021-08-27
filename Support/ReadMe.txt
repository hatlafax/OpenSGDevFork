
How to build and work with the support packages:

1) Download:

 1a) Boost

  If you don't have the need to modify the visual studio security c****
  or need a 64bit version you might download the prebuild packages from
  boost consulting instead. 

  Otherwise download:

http://sourceforge.net/projects/boost/files/boost/1.44.0/boost_1_44_0.zip/download
#http://nchc.dl.sourceforge.net/sourceforge/boost/boost_1_37_0.tar.gz

http://sourceforge.net/projects/boost/files/boost-jam/3.1.18/boost-jam-3.1.18-1-ntx86.zip/download
#http://nchc.dl.sourceforge.net/sourceforge/boost/boost-jam-3.1.17-1-ntx86.zip

build 

  a) dll + static lib + dll runtime + opt + dbg + 32 bit + vc9

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-9.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=32 stage


  a-s) dll + static lib + static runtime + opt + dbg + 32 bit + vc9

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-9.0 variant=debug,release threading=multi link=static runtime-link=static address-model=32 stage



  b) dll + static lib + dll runtime + opt + dbg + 32 bit + vc9 + no ms secure c****

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-9.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=32 define=_CRT_SECURE_NO_DEPRECATE define=_CRT_SECURE_NO_WARNINGS define=_CRT_NONSTDC_NO_DEPRECATE define=_ITERATOR_DEBUG_LEVEL=0 define=_SCL_SECURE_NO_WARNINGS define=_SCL_SECURE_NO_DEPRECATE define=_HAS_ITERATOR_DEBUGGING=0 stage


  b-s) dll + static lib + static runtime + opt + dbg + 32 bit + vc9 + no ms secure c****

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-9.0 variant=debug,release threading=multi link=static runtime-link=static address-model=32 define=_CRT_SECURE_NO_DEPRECATE define=_CRT_SECURE_NO_WARNINGS define=_CRT_NONSTDC_NO_DEPRECATE define=_ITERATOR_DEBUG_LEVEL=0 define=_SCL_SECURE_NO_WARNINGS define=_SCL_SECURE_NO_DEPRECATE define=_HAS_ITERATOR_DEBUGGING=0 stage



  c) dll + static lib + dll runtime + opt + dbg + 32 bit + vc10

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-10.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=32 stage


  c-s) dll + static lib + static runtime + opt + dbg + 32 bit + vc10

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-10.0 variant=debug,release threading=multi link=static runtime-link=static address-model=32 stage




  d) dll + static lib + dll runtime + opt + dbg + 32 bit + vc10 + no ms secure c****

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-10.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=32 define=_CRT_SECURE_NO_DEPRECATE define=_CRT_SECURE_NO_WARNINGS define=_CRT_NONSTDC_NO_DEPRECATE define=_ITERATOR_DEBUG_LEVEL=0 define=_SCL_SECURE_NO_WARNINGS define=_SCL_SECURE_NO_DEPRECATE define=_HAS_ITERATOR_DEBUGGING=0 stage


  d-s) dll + static lib + static runtime + opt + dbg + 32 bit + vc10 + no ms secure c****

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-10.0 variant=debug,release threading=multi link=static runtime-link=static address-model=32 define=_CRT_SECURE_NO_DEPRECATE define=_CRT_SECURE_NO_WARNINGS define=_CRT_NONSTDC_NO_DEPRECATE define=_ITERATOR_DEBUG_LEVEL=0 define=_SCL_SECURE_NO_WARNINGS define=_SCL_SECURE_NO_DEPRECATE define=_HAS_ITERATOR_DEBUGGING=0 stage



  e) dll + static lib + dll runtime + opt + dbg + 64 bit + vc9

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-9.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=64 stage


  e-s) dll + static lib + static runtime + opt + dbg + 64 bit + vc9

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-9.0 variant=debug,release threading=multi link=static runtime-link=static address-model=64 stage




  f) dll + static lib + dll runtime + opt + dbg + 64 bit + vc9 + no ms secure c****

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-9.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=64 define=_CRT_SECURE_NO_DEPRECATE define=_CRT_SECURE_NO_WARNINGS define=_CRT_NONSTDC_NO_DEPRECATE define=_ITERATOR_DEBUG_LEVEL=0 define=_SCL_SECURE_NO_WARNINGS define=_SCL_SECURE_NO_DEPRECATE define=_HAS_ITERATOR_DEBUGGING=0 stage


  f-s) dll + static lib + static runtime + opt + dbg + 64 bit + vc9 + no ms secure c****

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-9.0 variant=debug,release threading=multi link=static runtime-link=static address-model=64 define=_CRT_SECURE_NO_DEPRECATE define=_CRT_SECURE_NO_WARNINGS define=_CRT_NONSTDC_NO_DEPRECATE define=_ITERATOR_DEBUG_LEVEL=0 define=_SCL_SECURE_NO_WARNINGS define=_SCL_SECURE_NO_DEPRECATE define=_HAS_ITERATOR_DEBUGGING=0 stage



  g) dll + static lib + dll runtime + opt + dbg + 64 bit + vc10

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-10.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=64 stage


  g-s) dll + static lib + static runtime + opt + dbg + 64 bit + vc10

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-10.0 variant=debug,release threading=multi link=static runtime-link=static address-model=64 stage



  h) dll + static lib + dll runtime + opt + dbg + 64 bit + vc10 + no ms secure c****

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-10.0 variant=debug,release threading=multi link=shared,static runtime-link=shared address-model=64 define=_CRT_SECURE_NO_DEPRECATE define=_CRT_SECURE_NO_WARNINGS define=_CRT_NONSTDC_NO_DEPRECATE define=_ITERATOR_DEBUG_LEVEL=0 define=_SCL_SECURE_NO_WARNINGS define=_SCL_SECURE_NO_DEPRECATE define=_HAS_ITERATOR_DEBUGGING=0 stage


  h-s) dll + static lib + static runtime + opt + dbg + 64 bit + vc10 + no ms secure c****

..\bjam.exe -d+2 --stagedir=./stage --without-mpi toolset=msvc-10.0 variant=debug,release threading=multi link=static runtime-link=static address-model=64 define=_CRT_SECURE_NO_DEPRECATE define=_CRT_SECURE_NO_WARNINGS define=_CRT_NONSTDC_NO_DEPRECATE define=_ITERATOR_DEBUG_LEVEL=0 define=_SCL_SECURE_NO_WARNINGS define=_SCL_SECURE_NO_DEPRECATE define=_HAS_ITERATOR_DEBUGGING=0 stage
  

Please note that you need different source/build directories for the 32 bit, 64 bit,
scecurity and non security versions, as the standards cmake find boost module
only seems to work with the single 'stage' dir.

 1b) Qt

Download

http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.6.4.tar.gz

Build

 a) dll + opt + debug + vc9

configure -opensource -platform win32-msvc2008 -nomake examples -nomake demos -nomake docs -debug-and-release -mmx -sse -sse2 -plugin-sql-sqlite -no-dbus -no-phonon -no-phonon-backend -no-webkit -no-scripttools

 b) dll + opt + debug + vc9 + no ms secure c****

configure -opensource -platform win32-msvc2008 -nomake examples -nomake demos -nomake docs -debug-and-release -mmx -sse -sse2 -plugin-sql-sqlite -no-dbus -no-phonon -no-phonon-backend -no-webkit -no-scripttools -D _CRT_SECURE_NO_DEPRECATE -D _CRT_SECURE_NO_WARNINGS -D _CRT_NONSTDC_NO_DEPRECATE -D _ITERATOR_DEBUG_LEVEL=0 -D _SCL_SECURE_NO_WARNINGS -D _SCL_SECURE_NO_DEPRECATE -D _HAS_ITERATOR_DEBUGGING=0

 c)  dll + opt + debug + vc10

configure -opensource -platform win32-msvc2010 -nomake examples -nomake demos -nomake docs -debug-and-release -mmx -sse -sse2 -plugin-sql-sqlite -no-dbus -no-phonon -no-phonon-backend -no-webkit -no-scripttools

 d) dll + opt + debug + vc10 + no ms secure c****

configure -opensource -platform win32-msvc2010 -nomake examples -nomake demos -nomake docs -debug-and-release -mmx -sse -sse2 -plugin-sql-sqlite -no-dbus -no-phonon -no-phonon-backend -no-webkit -no-scripttools -D _CRT_SECURE_NO_DEPRECATE -D _CRT_SECURE_NO_WARNINGS -D _CRT_NONSTDC_NO_DEPRECATE -D _ITERATOR_DEBUG_LEVEL=0 -D _SCL_SECURE_NO_WARNINGS -D _SCL_SECURE_NO_DEPRECATE -D _HAS_ITERATOR_DEBUGGING=0

 1c) VTK

 1b) Rest

http://sourceforge.net/projects/libpng/files/zlib/1.2.5/zlib125.zip/download
#http://sourceforge.net/projects/libpng/files/zlib/1.2.5/zlib-1.2.5.tar.gz/download

http://sourceforge.net/projects/libpng/files/libpng15/1.5.4/lpng154.zip/download
#http://sourceforge.net/projects/libpng/files/libpng15/1.5.4/libpng-1.5.4.tar.gz/download

http://sourceforge.net/projects/libjpeg/files/libjpeg/6b/jpegsr6.zip/download
#http://sourceforge.net/projects/libjpeg/files/libjpeg/6b/jpegsrc.v6b.tar.gz/download
http://download.osgeo.org/libtiff/tiff-3.8.2.zip
#ftp://ftp.remotesensing.org/pub/libtiff/tiff-3.8.2.zip

 http://prdownloads.sourceforge.net/freeglut/freeglut-2.8.0.tar.gz?download

 or

 http://www.xmission.com/~nate/glut/glut-3.7.6-src.zip

http://sourceforge.net/projects/collada-dom/files/Collada%20DOM/Collada%20DOM%202.4/collada-dom-2.4.0-libsrc.tgz/download
ftp://xmlsoft.org/libxml2/libxml2-2.7.8.tar.gz
http://sourceforge.net/projects/pcre/files/pcre/8.12/pcre-8.12.zip/download
#http://sourceforge.net/projects/pcre/files/pcre/8.12/pcre-8.12.tar.gz/download

http://download.savannah.nongnu.org/releases/openexr/openexr-1.7.0.tar.gz
http://download.savannah.nongnu.org/releases/openexr/ilmbase-1.0.2.tar.gz

http://sourceforge.net/projects/expat/files/expat/2.0.1/expat-2.0.1.tar.gz/download
http://download.osgeo.org/gdal/gdal180.zip
http://sourceforge.net/projects/glew/files/glew/1.7.0/glew-1.7.0.zip/download
#http://sourceforge.net/projects/glew/files/glew/1.6.0/glew-1.6.0.tgz/download
http://cudpp.googlecode.com/files/cudpp_src_1.1.zip
http://stereofx.org/download/mini/MINI-9.8.zip
http://files.na.mcneel.com/opennurbs/5.0/2011-11-22/opennurbs_20111122.zip

2) Unpack to disk

3) Point OSGFreeGlutSrcDir, OSGJpegLibSrcDir, OSGLibPNGSrcDir, 
   OSGTiffLibSrcDir, OSGZLibSrcDir, OSGColladaSrcDir, OSGPcreSrcDir,
   OSGLibXml2SrcDir, ....., and OSGLibIconvSrcDir to the appropriate directories, e.g.

   OSGFreeGlutSrcDir:PATH=X:/..../OpenSG-Support/Unpack/freeglut-2.6.0
   OSGJpegLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/jpeg-6b
   OSGLibPNGSrcDir:PATH=X:/....//OpenSG-Support/Unpack/libpng-1.2.37
   OSGTiffLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/tiff-3.8.2
   OSGZLibSrcDir:PATH=X:/..../OpenSG-Support/Unpack/zlib-1.2.3-source
   OSGColladaSrcDir:PATH=X:/..../OpenSG-Support/Unpack/collada-dom
   OSGPcreSrcDir:PATH=X:/..../OpenSG-Support/Unpack/pcre-7.9
   OSGLibXml2SrcDir:PATH=X:/..../OpenSG-Unpack/libxml2-2.7.3
   OSGLibIconvSrcDir:PATH=X:/..../OpenSG-Support/Unpack/libiconv-1.12-source
   .
   .
   .

4) Build + Install

5) Configure OpenSG.

  5a) activate OSG_USE_OSGSUPPORT_LIBS

    set OSG_SUPPORT_ROOT the where you installed the support libs, e.g.

    OSG_SUPPORT_ROOT:PATH=X:/..../OpenSG-Support/install

    choose to use dlls / static libs according to what you build or prefer

    OSG_USE_STATIC_SUPPORT_LIBS:BOOL=OFF

    Please make sure to use the same boost libs and _SECURE settings as for
    the support libs. This is currently neither checked/enforced nor
    automatically transferred.

  5b) set by hand

  5a is strongly recommended !

6) Doxygen

  As we use some custom doxygen extensions building the documentation works
  best with the customized doxygen version. For linux check out revision 752
  to the disk and setup the OSGDoxygenSrcDir to point to it.

  svn checkout -r 752 https://doxygen.svn.sourceforge.net/svnroot/doxygen/trunk doxygen

  After the build and install steps the custom binary should be picked up by the 
  main OpenSG cmake script.


Finally a small word of caution. The packages are build to work with OpenSG,
there might not be as general as possible. For example some of the internal package
headers are not installed (libxml2, iconv, pcre) as the are not directly
included by OpenSG. If you need them let us know.


Support Package <-> OpenSG Feature dependencies:
================================================

1) must haves, without them OpenSG itself won't build:

 -) boost
 -) zlib

2) File formats:

 -) Collada SceneFileType
      collada-dom, libiconv, libxml2, pcre 

 -) Tiff ImageFileType
      tiff
  
 -) PNG ImageFileType
      libpng

 -) JPG ImageFileType
      libjpeg

 -) GDAL ImageFileType
      gdal, expat
 
 -) OpenEXR ImageFileType
      OpenEXR

3) Window types

 -) GLUTWindow
      freeglut
 
 -) QTWindow
      qt

4) Rest

 -) Source/Contrib/VTK
      vtk

 -) Source/Contrib/Compute
      cudpp

 -) Easy testing
      glew

have fun
  gerrit

