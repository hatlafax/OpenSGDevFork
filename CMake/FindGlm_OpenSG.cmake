# - Find GLM
# Find the native Glm includes and library
# This module defines
#  GLM_INCLUDE_DIR, where to find glm/glm/glm.hpp.
#  GLM_LIBRARIES, the libraries needed to use Glm.
#  GLM_FOUND, If false, do not try to use Glm.
# also defined, but not for general use are
#  GLM_LIBRARY, where to find the Glm library.

FIND_PATH(GLM_INCLUDE_DIR glm/glm.hpp)

SET(GLM_LIBRARY "")
SET(GLM_LIBRARIES "")

IF(GLM_INCLUDE_DIR)
    SET(GLM_FOUND TRUE)
ELSE()
    SET(GLM_FOUND FALSE)
ENDIF()

MARK_AS_ADVANCED(GLM_INCLUDE_DIR)
