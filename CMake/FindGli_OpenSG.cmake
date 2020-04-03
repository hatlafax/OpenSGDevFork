# - Find GLI
# Find the native Gli includes and library
# This module defines
#  GLI_INCLUDE_DIR, where to find gli/gli/gli.hpp.
#  GLI_LIBRARIES, the libraries needed to use Gli.
#  GLI_FOUND, If false, do not try to use Gli.
# also defined, but not for general use are
#  GLI_LIBRARY, where to find the Gli library.

FIND_PATH(GLI_INCLUDE_DIR gli/gli.hpp)

SET(GLI_LIBRARY "")
SET(GLI_LIBRARIES "")

IF(GLI_INCLUDE_DIR)
    SET(GLI_FOUND TRUE)
ELSE()
    SET(GLI_FOUND FALSE)
ENDIF()

MARK_AS_ADVANCED(GLI_INCLUDE_DIR)
