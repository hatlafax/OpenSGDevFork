# - Find zlib
# Find the native ZLIB includes and library
#
#  ZLIB_INCLUDE_DIR - where to find zlib.h, etc.
#  ZLIB_LIBRARIES   - List of libraries when using zlib.
#  ZLIB_FOUND       - True if zlib found.
#  ZLIB_LIBRARY_DEBUG
#  ZLIB_LIBRARY_RELEASE

IF (ZLIB_INCLUDE_DIR)
  # Already in cache, be silent
  SET(ZLIB_FIND_QUIETLY TRUE)
ENDIF (ZLIB_INCLUDE_DIR)

FIND_PATH(ZLIB_INCLUDE_DIR zlib.h)

SET(ZLIB_NAMES_RELEASE z zlib zdll)
FIND_LIBRARY(ZLIB_LIBRARY_RELEASE NAMES ${ZLIB_NAMES_RELEASE} )

SET(ZLIB_NAMES_DEBUG zd zlibd zddll)
FIND_LIBRARY(ZLIB_LIBRARY_DEBUG NAMES ${ZLIB_NAMES_DEBUG} )

SET(ZLIB_LIBRARIES_FOUND )

IF(ZLIB_LIBRARY_DEBUG)
  SET(ZLIB_LIBRARIES_FOUND TRUE)
  MARK_AS_ADVANCED(ZLIB_LIBRARY_DEBUG)
ENDIF(ZLIB_LIBRARY_DEBUG)

IF(ZLIB_LIBRARY_RELEASE)
  SET(ZLIB_LIBRARIES_FOUND TRUE)
  MARK_AS_ADVANCED(ZLIB_LIBRARY_RELEASE)
ENDIF(ZLIB_LIBRARY_RELEASE)

# handle the QUIETLY and REQUIRED arguments and set ZLIB_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ZLIB_OpenSG DEFAULT_MSG 
                                  ZLIB_LIBRARIES_FOUND 
                                  ZLIB_INCLUDE_DIR)
IF(ZLIB_OpenSG_FOUND)
  SET(ZLIB_FOUND TRUE)
ELSE()
  SET(ZLIB_FOUND FALSE)
ENDIF()

MARK_AS_ADVANCED(ZLIB_LIBRARIES_FOUND ZLIB_INCLUDE_DIR)
