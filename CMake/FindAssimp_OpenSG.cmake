# - Find Assimp
# Find the native Assimp includes and library
# This module defines
#  ASSIMP_INCLUDE_DIR, where to find assimp/ai_assert.h.
#  ASSIMP_LIBRARIES, the libraries needed to use Assimp.
#  ASSIMP_FOUND, If false, do not try to use Assimp.
# also defined, but not for general use are
#  ASSIMP_LIBRARY, where to find the Assimp library.

FIND_PATH(ASSIMP_INCLUDE_DIR assimp/ai_assert.h)

set(_assimp_lib_name_decoration "")

if(WIN32)
    set(_assimp_msvc_version "")
    if(MSVC12)
        set(_assimp_msvc_version "vc120")
    elseif(MSVC14)
        set(_assimp_msvc_version "vc140")
    elseif(MSVC15)
        set(_assimp_msvc_version "vc141")
    endif(MSVC12)
    set(_assimp_lib_name_decoration "-${_assimp_msvc_version}-mt")
endif(WIN32)

SET(ASSIMP_NAME Assimp${_assimp_lib_name_decoration})

SET(ASSIMP_NAMES_RELEASE ${ASSIMP_NAMES_RELEASE} ${ASSIMP_NAME})
FIND_LIBRARY(ASSIMP_LIBRARY_RELEASE NAMES ${ASSIMP_NAMES_RELEASE} )

SET(ASSIMP_NAMES_DEBUG ${ASSIMP_NAMES_DEBUG} ${ASSIMP_NAME})
FIND_LIBRARY(ASSIMP_LIBRARY_DEBUG NAMES ${ASSIMP_NAMES_DEBUG} )

IF(ASSIMP_LIBRARY_DEBUG)
  SET(ASSIMP_LIBRARIES_FOUND TRUE)
  MARK_AS_ADVANCED(ASSIMP_LIBRARY_DEBUG)
ENDIF(ASSIMP_LIBRARY_DEBUG)

IF(ASSIMP_LIBRARY_RELEASE)
  SET(ASSIMP_LIBRARIES_FOUND TRUE)
  MARK_AS_ADVANCED(ASSIMP_LIBRARY_RELEASE)
ENDIF(ASSIMP_LIBRARY_RELEASE)

# handle the QUIETLY and REQUIRED arguments and set ASSIMP_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Assimp_OpenSG DEFAULT_MSG 
                                  ASSIMP_LIBRARIES_FOUND
                                  ASSIMP_INCLUDE_DIR)
IF(Assimp_OpenSG_FOUND)
  SET(ASSIMP_FOUND TRUE)
ELSE()
  SET(ASSIMP_FOUND FALSE)
ENDIF()

#IF(ASSIMP_FOUND)
#  SET(ASSIMP_LIBRARIES ${ASSIMP_LIBRARY})
#ENDIF(ASSIMP_FOUND)

# Deprecated declarations.
#SET (NATIVE_ASSIMP_INCLUDE_PATH ${ASSIMP_INCLUDE_DIR} )
#IF(ASSIMP_LIBRARY)
#  GET_FILENAME_COMPONENT (NATIVE_ASSIMP_LIB_PATH ${ASSIMP_LIBRARY} PATH)
#ENDIF(ASSIMP_LIBRARY)

MARK_AS_ADVANCED(ASSIMP_LIBRARIES_FOUND ASSIMP_INCLUDE_DIR )
