# - Find VMATH
# Find the native VMath includes and library
# This module defines
#  VMATH_INCLUDE_DIR, where to find vmath/VectorMath.h, etc.
#  VMATH_LIBRARIES, the libraries needed to use VMath.
#  VMATH_FOUND, If false, do not try to use VMath.
# also defined, but not for general use are
#  VMATH_LIBRARY, where to find the VMath library.

FIND_PATH(VMATH_INCLUDE_DIR vmath/VectorMath.h)

SET(VMATH_LIBRARY "")
SET(VMATH_LIBRARIES "")

IF(VMATH_INCLUDE_DIR)
    SET(VMATH_FOUND TRUE)
ELSE()
    SET(VMATH_FOUND FALSE)
ENDIF()

MARK_AS_ADVANCED(VMATH_INCLUDE_DIR)
