
MESSAGE(STATUS "Applying Compiler Defaults")

SET(OSG_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DOSG_DEBUG")
SET(OSG_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG} -DOSG_DEBUG")

IF(UNIX)
  SET(OSG_CXX_FLAGS_DEBUG "${OSG_CXX_FLAGS_DEBUG} -D_DEBUG")
  SET(OSG_C_FLAGS_DEBUG   "${OSG_C_FLAGS_DEBUG} -D_DEBUG")
ENDIF(UNIX)

IF(APPLE AND IOS)
  SET(OSG_CXX_FLAGS_DEBUG "${OSG_CXX_FLAGS_DEBUG} -g")
  SET(OSG_C_FLAGS_DEBUG   "${OSG_C_FLAGS_DEBUG} -g")
ENDIF(APPLE AND IOS)

SET(OSG_CXX_FLAGS ${CMAKE_CXX_FLAGS})
SET(OSG_C_FLAGS   ${CMAKE_C_FLAGS})

SET(OSG_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
SET(OSG_C_FLAGS_RELEASE   ${CMAKE_C_FLAGS_RELEASE})

IF(APPLE AND IOS)
  SET(OSG_CXX_FLAGS_RELEASE "${OSG_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
  SET(OSG_C_FLAGS_RELEASE   "${OSG_C_FLAGS_RELEASE} -O3 -DNDEBUG")
ENDIF(APPLE AND IOS)

SET(OSG_EXE_LINKER_FLAGS    ${CMAKE_EXE_LINKER_FLAGS})
SET(OSG_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS})

IF(MSVC)

    MESSAGE(STATUS "Setup MSVC")

    # Hide unused cmake targets

    SET(CMAKE_CXX_FLAGS_MINSIZEREL
        "${CMAKE_CXX_FLAGS_MINSIZEREL}" 
        CACHE INTERNAL "")

    SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO
        "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}" 
        CACHE INTERNAL "")


    SET(CMAKE_C_FLAGS_MINSIZEREL
        "${CMAKE_C_FLAGS_MINSIZEREL}" 
        CACHE INTERNAL "")

    SET(CMAKE_C_FLAGS_RELWITHDEBINFO
        "${CMAKE_C_FLAGS_RELWITHDEBINFO}" 
        CACHE INTERNAL "")


    # ReleaseNoOpt

    SET(OSG_CXX_FLAGS_RELEASENOOPT "${OSG_CXX_FLAGS_DEBUG} /MP${OSG_NUM_COMPILE_PROC}")
    SET(OSG_C_FLAGS_RELEASENOOPT   "${OSG_C_FLAGS_DEBUG} /MP${OSG_NUM_COMPILE_PROC}")

    STRING(REPLACE "MDd" "MD" OSG_CXX_FLAGS_RELEASENOOPT ${OSG_CXX_FLAGS_RELEASENOOPT})
    STRING(REPLACE "MDd" "MD" OSG_C_FLAGS_RELEASENOOPT   ${OSG_C_FLAGS_RELEASENOOPT})

    STRING(REPLACE "/RTC1" "" OSG_CXX_FLAGS_RELEASENOOPT ${OSG_CXX_FLAGS_RELEASENOOPT})
    STRING(REPLACE "/RTC1" "" OSG_C_FLAGS_RELEASENOOPT   ${OSG_C_FLAGS_RELEASENOOPT})

    STRING(REPLACE "/D_DEBUG" "" OSG_CXX_FLAGS_RELEASENOOPT ${OSG_CXX_FLAGS_RELEASENOOPT})
    STRING(REPLACE "/D_DEBUG" "" OSG_C_FLAGS_RELEASENOOPT   ${OSG_C_FLAGS_RELEASENOOPT})

    # Debug

    SET(OSG_CXX_FLAGS_DEBUG "${OSG_CXX_FLAGS_DEBUG} -DOSG_DEBUGRT /MP${OSG_NUM_COMPILE_PROC}")
    SET(OSG_C_FLAGS_DEBUG   "${OSG_C_FLAGS_DEBUG} -DOSG_DEBUGRT /MP${OSG_NUM_COMPILE_PROC}")
    
    # Debug Opt

    SET(OSG_CXX_FLAGS_DEBUGOPT "${OSG_CXX_FLAGS_RELEASE} -DOSG_DEBUGRT /Zi /MP${OSG_NUM_COMPILE_PROC}")
    SET(OSG_C_FLAGS_DEBUGOPT   "${OSG_C_FLAGS_RELEASE} -DOSG_DEBUGRT /Zi /MP${OSG_NUM_COMPILE_PROC}")
    
    STRING(REPLACE "MD" "MDd" OSG_CXX_FLAGS_DEBUGOPT ${OSG_CXX_FLAGS_DEBUGOPT})
    STRING(REPLACE "MD" "MDd" OSG_C_FLAGS_DEBUGOPT   ${OSG_C_FLAGS_DEBUGOPT})

#    STRING(REPLACE "/D NDEBUG " "" OSG_CXX_FLAGS_DEBUGOPT ${OSG_CXX_FLAGS_DEBUGOPT})
#    STRING(REPLACE "/D NDEBUG " "" OSG_C_FLAGS_DEBUGOPT   ${OSG_C_FLAGS_DEBUGOPT})

    # Release

    SET(OSG_CXX_FLAGS_RELEASE "${OSG_CXX_FLAGS_RELEASE} /Zi /MP${OSG_NUM_COMPILE_PROC}")
    SET(OSG_C_FLAGS_RELEASE   "${OSG_C_FLAGS_RELEASE} /Zi /MP${OSG_NUM_COMPILE_PROC}")

    # Push to CMAKE

    SET(CMAKE_CXX_FLAGS_DEBUGOPT 
        "${OSG_CXX_FLAGS_DEBUGOPT}" 
        CACHE STRING "Flags used by the C++ compiler during maintainer builds."
        FORCE)

    SET(CMAKE_C_FLAGS_DEBUGOPT 
        "${OSG_C_FLAGS_DEBUGOPT}" 
        CACHE STRING "Flags used by the C compiler during maintainer builds."
        FORCE)

    SET(CMAKE_CXX_FLAGS_RELEASENOOPT 
        "${OSG_CXX_FLAGS_RELEASENOOPT}" 
        CACHE STRING "Flags used by the C++ compiler during maintainer builds."
        FORCE)

    SET(CMAKE_C_FLAGS_RELEASENOOPT 
        "${OSG_C_FLAGS_RELEASENOOPT}" 
        CACHE STRING "Flags used by the C compiler during maintainer builds."
        FORCE)




    # General Flags

#    STRING(REPLACE "W3"  "W1" OSG_CXX_FLAGS       ${OSG_CXX_FLAGS})
#    STRING(REPLACE "W3"  "W1" OSG_C_FLAGS         ${OSG_C_FLAGS})

    # 4290 exception spec
    # 4251 dll export
    # 4275 derived from not exported
    # 4661 template class mem func not defined
    # 4351 member init array handling
    # 4996 deprecated
    # 4231 non standard ext

    # 4244 smaller type assign
    # 4355 this before constructed
    #
    # /wd4244 /wd4355

    STRING(REPLACE "W3"  "W3 /wd4244 /wd4290 /wd4251 /wd4275 /wd4661 /wd4351 /wd4996 /wd4231" OSG_CXX_FLAGS ${OSG_CXX_FLAGS})
    STRING(REPLACE "W3"  "W3 /wd4244 /wd4290 /wd4251 /wd4275 /wd4351 /wd4996" OSG_C_FLAGS ${OSG_C_FLAGS})

    IF(NOT OSG_WIN_VERSION)
      SET(OSG_WIN_VERSION "0x0601" CACHE STRING "" FORCE)
    ENDIF()
    
    SET(OSG_CXX_FLAGS "/bigobj ${OSG_CXX_FLAGS} ${OSG_ADD_CXX_FLAGS} /D_WIN32_WINNT=${OSG_WIN_VERSION} /DWINVER=${OSG_WIN_VERSION}")
    SET(OSG_C_FLAGS   "/bigobj ${OSG_C_FLAGS} ${OSG_ADD_CXX_FLAGS} /D_WIN32_WINNT=${OSG_WIN_VERSION} /DWINVER=${OSG_WIN_VERSION}")


    # Libs
    IF(NOT OSG_WITH_DEFAULTLIBS)
      SET(OSG_EXE_LINKER_FLAGS    "${OSG_EXE_LINKER_FLAGS} /nodefaultlib") 
      SET(OSG_SHARED_LINKER_FLAGS "${OSG_SHARED_LINKER_FLAGS} /nodefaultlib") 

      SET(OSG_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} winmm.lib wsock32.lib oldnames.lib")
      SET(OSG_C_STANDARD_LIBRARIES   "${CMAKE_C_STANDARD_LIBRARIES} winmm.lib wsock32.lib oldnames.lib")

      SET(OSG_CLEAR_STD_LIBS winspool.lib shell32.lib ole32.lib oleaut32.lib
                             uuid.lib comdlg32.lib msvcprt.lib msvcrt.lib ucrt.lib vcruntime.lib)

      FOREACH(STD_LIB ${OSG_CLEAR_STD_LIBS})
        STRING(REPLACE ${STD_LIB} "" OSG_CXX_STANDARD_LIBRARIES ${OSG_CXX_STANDARD_LIBRARIES})
        STRING(REPLACE ${STD_LIB} "" OSG_C_STANDARD_LIBRARIES   ${OSG_C_STANDARD_LIBRARIES})
      ENDFOREACH()

      SET(CMAKE_CXX_STANDARD_LIBRARIES ${OSG_CXX_STANDARD_LIBRARIES} 
                                     CACHE STRING "OpenSG defaults" FORCE )
      SET(CMAKE_C_STANDARD_LIBRARIES   ${OSG_C_STANDARD_LIBRARIES} 
                                     CACHE STRING "OpenSG defaults" FORCE )

#      SET(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo;DebugRT" 
#                                    CACHE STRING "OpenSG Build Types" FORCE )

      SET(CMAKE_CONFIGURATION_TYPES "Debug;Release;DebugOpt;ReleaseNoOpt" 
                                    CACHE STRING "OpenSG Build Types" FORCE )

      # Shared Linker Flags
      IF(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "19")
       SET(OSG_ADD_MSVC_STD_LIBS_DEBUG   "vcruntimed.lib ucrtd.lib")
       SET(OSG_ADD_MSVC_STD_LIBS_RELEASE "vcruntime.lib ucrt.lib")
      ENDIF()

      IF(OSG_WINDOWS_LINK_OPTIMIZE)
          SET(windows_link_optimization "/OPT:REF /OPT:ICF")
      ENDIF()

      # Shared Linker Flags
      SET(CMAKE_SHARED_LINKER_FLAGS_RELEASENOOPT 
          "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} msvcprt.lib msvcrt.lib ucrt.lib vcruntime.lib ${OSG_ADD_MSVC_STD_LIBS_RELEASE}"
          CACHE STRING "OpenSG defaults" FORCE )

      SET(CMAKE_SHARED_LINKER_FLAGS_DEBUGOPT 
          "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /debug ${windows_link_optimization} msvcprtd.lib msvcrtd.lib ucrtd.lib vcruntimed.lib ${OSG_ADD_MSVC_STD_LIBS_DEBUG}"
          CACHE STRING "OpenSG defaults" FORCE )

      SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE 
          "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /debug ${windows_link_optimization} msvcprt.lib msvcrt.lib ucrt.lib vcruntime.lib ${OSG_ADD_MSVC_STD_LIBS_RELEASE}"
          CACHE STRING "OpenSG defaults" FORCE )

      SET(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL 
          "${CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL} msvcprt.lib msvcrt.lib ucrt.lib vcruntime.lib ${OSG_ADD_MSVC_STD_LIBS_RELEASE}"
          CACHE INTERNAL "OpenSG defaults" FORCE )

      SET(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO 
          "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} msvcprt.lib msvcrt.lib ucrt.lib vcruntime.lib ${OSG_ADD_MSVC_STD_LIBS_RELEASE}"
          CACHE INTERNAL "OpenSG defaults" FORCE )
    
#      STRING(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replacementFlags ${CMAKE_SHARED_LINKER_FLAGS_DEBUG})
#      SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/INCREMENTAL:NO ${replacementFlags}" )
    
      SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG 
          "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} msvcprtd.lib msvcrtd.lib ucrtd.lib vcruntimed.lib ${OSG_ADD_MSVC_STD_LIBS_DEBUG}"
          CACHE STRING "OpenSG defaults" FORCE )



      # Exe Linker Flags
      SET(CMAKE_EXE_LINKER_FLAGS_RELEASENOOPT 
          "${CMAKE_EXE_LINKER_FLAGS_DEBUG} msvcprt.lib msvcrt.lib ucrt.lib vcruntime.lib ${OSG_ADD_MSVC_STD_LIBS_RELEASE}"
          CACHE STRING "OpenSG defaults" FORCE )

      SET(CMAKE_EXE_LINKER_FLAGS_DEBUGOPT 
          "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /debug ${windows_link_optimization} msvcprtd.lib msvcrtd.lib ucrtd.lib vcruntimed.lib ${OSG_ADD_MSVC_STD_LIBS_DEBUG}"
          CACHE STRING "OpenSG defaults" FORCE )

      SET(CMAKE_EXE_LINKER_FLAGS_RELEASE 
          "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /debug ${windows_link_optimization} msvcprt.lib msvcrt.lib ucrt.lib vcruntime.lib ${OSG_ADD_MSVC_STD_LIBS_RELEASE}"
          CACHE STRING "OpenSG defaults" FORCE )

      SET(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL 
          "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} msvcprt.lib msvcrt.lib ucrt.lib vcruntime.lib ${OSG_ADD_MSVC_STD_LIBS_RELEASE}"
          CACHE INTERNAL "OpenSG defaults" FORCE )

      SET(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO 
          "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} msvcprt.lib msvcrt.lib ucrt.lib vcruntime.lib ${OSG_ADD_MSVC_STD_LIBS_RELEASE}"
          CACHE INTERNAL "OpenSG defaults" FORCE )

      SET(CMAKE_EXE_LINKER_FLAGS_DEBUG 
          "${CMAKE_EXE_LINKER_FLAGS_DEBUG} msvcprtd.lib msvcrtd.lib ucrtd.lib vcruntimed.lib ${OSG_ADD_MSVC_STD_LIBS_DEBUG}"
          CACHE STRING "OpenSG defaults" FORCE )
    ELSE()

#      MESSAGE(STATUS "foo ${CMAKE_SHARED_LINKER_FLAGS_DEBUG} ${CMAKE_SHARED_LINKER_FLAGS_RELEASE} ${CMAKE_SHARED_LINKER_FLAGS_RELEASENOOPT} ${CMAKE_SHARED_LINKER_FLAGS_DEBUGOPT}")

      SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}       ${OSG_ADD_EXE_LIB_REL} /debug"    CACHE INTERNAL "OpenSG defaults" FORCE)
      SET(CMAKE_EXE_LINKER_FLAGS_DEBUG   "${CMAKE_EXE_LINKER_FLAGS_DEBUG}         ${OSG_ADD_EXE_LIB_DEBUG}"         CACHE INTERNAL "OpenSG defaults" FORCE)

      SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} ${OSG_ADD_SHARED_LIB_REL} /debug" CACHE INTERNAL "OpenSG defaults" FORCE)
      SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG   "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}   ${OSG_ADD_SHARED_LIB_DEBUG}"      CACHE INTERNAL "OpenSG defaults" FORCE)

      SET(CMAKE_EXE_LINKER_FLAGS_RELEASENOOPT    "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /debug"    CACHE INTERNAL "OpenSG defaults" FORCE)
      SET(CMAKE_EXE_LINKER_FLAGS_DEBUGOPT        "${CMAKE_EXE_LINKER_FLAGS_DEBUG}"             CACHE INTERNAL "OpenSG defaults" FORCE)

      SET(CMAKE_SHARED_LINKER_FLAGS_RELEASENOOPT "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /debug" CACHE INTERNAL "OpenSG defaults" FORCE)
      SET(CMAKE_SHARED_LINKER_FLAGS_DEBUGOPT     "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}"          CACHE INTERNAL "OpenSG defaults" FORCE)
      
      SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" 
                                    CACHE STRING "OpenSG Build Types" FORCE )
    ENDIF()

    # Hide unused vars

    SET(CMAKE_MODULE_LINKER_FLAGS 
        "${CMAKE_MODULE_LINKER_FLAGS}"
        CACHE INTERNAL "OpenSG defaults" FORCE )

    SET(CMAKE_MODULE_LINKER_FLAGS_DEBUG 
        "${CMAKE_MODULE_LINKER_FLAGS_DEBUG}"
        CACHE INTERNAL "OpenSG defaults" FORCE )

    SET(CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL 
        "${CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL}"
        CACHE INTERNAL "OpenSG defaults" FORCE )

    SET(CMAKE_MODULE_LINKER_FLAGS_RELEASE 
        "${CMAKE_MODULE_LINKER_FLAGS_RELEASE}"
        CACHE INTERNAL "OpenSG defaults" FORCE )

    SET(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO 
        "${CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO}"
        CACHE INTERNAL "OpenSG defaults" FORCE )


ENDIF(MSVC)

IF(CMAKE_COMPILER_IS_GNUCC)

    EXECUTE_PROCESS(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                    OUTPUT_VARIABLE GCC_VERSION)
#    SET(OSG_GCC_VERSION ${GCC_VERSION} CACHE STRING "" FORCE)
    STRING(REGEX REPLACE "\n$" "" OSG_GCC_VERSION "${GCC_VERSION}")

    MESSAGE("GOT gcc ${OSG_GCC_VERSION}")

    IF(OSG_PLATFORM_64 AND LINUX)
        SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -m64")
        SET(OSG_C_FLAGS   "${OSG_C_FLAGS} -m64")

        SET(OSG_EXE_LINKER_FLAGS    "${OSG_EXE_LINKER_FLAGS} -m64")
        SET(OSG_SHARED_LINKER_FLAGS "${OSG_SHARED_LINKER_FLAGS} -m64")

    ENDIF(OSG_PLATFORM_64 AND LINUX)

    SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -D__STDC_FORMAT_MACROS -fPIC")
    SET(OSG_C_FLAGS   "${OSG_C_FLAGS} -D__STDC_FORMAT_MACROS -fPIC")

#    IF(OSG_ENABLE_C++11)
#      IF(${GCC_VERSION} VERSION_LESS "4.7")
#        SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -std=c++0x")
#      ELSE()
#        SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -std=c++11")
#      ENDIF()
#    ENDIF()
ENDIF(CMAKE_COMPILER_IS_GNUCC)


IF(APPLE AND NOT IOS)
  IF(OSG_ENABLE_C++11)
#    SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -std=c++11 -stdlib=libstdc++")
    SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -std=c++11 -stdlib=libc++ -Wno-deprecated-register")
#    SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -std=c++11")
  ENDIF()
ENDIF()




SET(CMAKE_CXX_FLAGS         ${OSG_CXX_FLAGS} 
                            CACHE STRING "OpenSG defaults" FORCE )
SET(CMAKE_C_FLAGS           ${OSG_C_FLAGS} 
                            CACHE STRING "OpenSG defaults" FORCE )

SET(CMAKE_CXX_FLAGS_DEBUG   ${OSG_CXX_FLAGS_DEBUG} 
                            CACHE STRING "OpenSG defaults" FORCE )
SET(CMAKE_C_FLAGS_DEBUG     ${OSG_C_FLAGS_DEBUG} 
                            CACHE STRING "OpenSG defaults" FORCE )

SET(CMAKE_CXX_FLAGS_RELEASE ${OSG_CXX_FLAGS_RELEASE} 
                            CACHE STRING "OpenSG defaults" FORCE )
SET(CMAKE_C_FLAGS_RELEASE   ${OSG_C_FLAGS_RELEASE} 
                            CACHE STRING "OpenSG defaults" FORCE )


SET(CMAKE_EXE_LINKER_FLAGS    ${OSG_EXE_LINKER_FLAGS} 
                              CACHE STRING "OpenSG defaults" FORCE )
SET(CMAKE_SHARED_LINKER_FLAGS ${OSG_SHARED_LINKER_FLAGS} 
                              CACHE STRING "OpenSG defaults" FORCE )

   

###########
# GV stuff
###########

IF(CMAKE_COMPILER_IS_GNUCC)

    IF(${GCC_VERSION} VERSION_LESS "4.8")
      SET(OSG_GCC_PEDANTIC_OPTION ""          )
      SET(OSG_GCC_EFFCPP_OPTION   ""          )
    ELSE()
      SET(OSG_GCC_PEDANTIC_OPTION "-Wpedantic")
      SET(OSG_GCC_EFFCPP_OPTION   "-Weffc++"  )
    ENDIF()


    SET(OSG_CXX_FLAGS_GV " -Wall -Wextra -Wshadow ${OSG_GCC_PEDANTIC_OPTION} -Werror ${OSG_GCC_EFFCPP_OPTION}")

    SET(OSG_CXX_FLAGS_GV "${OSG_CXX_FLAGS_GV} -Wreturn-type -Wold-style-cast -Wno-unused-parameter -Wwrite-strings")
    SET(OSG_CXX_FLAGS_GV "${OSG_CXX_FLAGS_GV} -DOSG_DEBUG_OLD_C_CASTS -DOSG_CLEAN_FCFIELDS -DOSG_CHECK_CONST_CORRECT_FIELD_USAGE")

    SET(OSG_C_FLAGS_GV " -Wall -Wextra -Wshadow ${OSG_GCC_PEDANTIC_OPTION} -Werror ${OSG_GCC_EFFCPP_OPTION}")
    SET(OSG_C_FLAGS_GV "${OSG_C_FLAGS_GV} -Wreturn-type -Wold-style-cast -Wno-unused-parameter -Wwrite-strings ")
    SET(OSG_C_FLAGS_GV "${OSG_C_FLAGS_GV} -DOSG_DEBUG_OLD_C_CASTS -DOSG_CLEAN_FCFIELDS -DOSG_CHECK_CONST_CORRECT_FIELD_USAGE")


    SET(OSG_ADD_CXX_FLAGS_GV "")
    SET(OSG_ADD_C_FLAGS_GV "")

    SET(OSG_SHARED_LINKER_FLAGS_GV " -Wl,--no-undefined")


##########
# Debug
##########

    SET(CMAKE_CXX_FLAGS_DEBUGGV 
        "${CMAKE_CXX_FLAGS_DEBUG}${OSG_CXX_FLAGS_GV}" 
        CACHE STRING "Flags used by the C++ compiler during maintainer builds."
        FORCE)

    SET(CMAKE_C_FLAGS_DEBUGGV 
        "${CMAKE_C_FLAGS_DEBUG}${OSG_C_FLAGS_GV}" 
        CACHE STRING "Flags used by the C compiler during maintainer builds."
        FORCE)

    SET(CMAKE_EXE_LINKER_FLAGS_DEBUGGV
        "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" 
        CACHE STRING "Flags used for linking binaries during maintainer builds."
        FORCE)

    SET(CMAKE_MODULE_LINKER_FLAGS_DEBUGGV
        "${CMAKE_MODULE_LINKER_FLAGS_DEBUG}" 
        CACHE STRING "Flags used for linking binaries during maintainer builds."
        FORCE)

    SET(CMAKE_SHARED_LINKER_FLAGS_DEBUGGV
        "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}${OSG_SHARED_LINKER_FLAGS_GV}" 
        CACHE STRING
        "Flags used by the shared libraries linker during maintainer builds."
        FORCE)

    ##########
    # Release
    ##########

    SET(CMAKE_CXX_FLAGS_RELEASEGV 
        "${CMAKE_CXX_FLAGS_RELEASE}${OSG_CXX_FLAGS_GV}" 
        CACHE STRING "Flags used by the C++ compiler during gv builds."
        FORCE)

    SET(CMAKE_C_FLAGS_RELEASEGV 
        "${CMAKE_C_FLAGS_RELEASE}${OSG_C_FLAGS_GV}"
        CACHE STRING "Flags used by the C compiler during gv builds."
        FORCE)

    SET(CMAKE_EXE_LINKER_FLAGS_RELEASEGV
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" 
        CACHE STRING "Flags used for linking binaries during gv builds."
        FORCE)

    SET(CMAKE_MODULE_LINKER_FLAGS_RELEASEGV
         "${CMAKE_MODULE_LINKER_FLAGS_RELEASE}" 
        CACHE STRING "Flags used for linking binaries during gv builds."
        FORCE)

    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASEGV
        "${CMAKE_SHARED_LINKER_FLAGS_RELEASE}${OSG_SHARED_LINKER_FLAGS_GV}" 
        CACHE STRING
        "Flags used by the shared libraries linker during gv builds."
        FORCE)

ENDIF(CMAKE_COMPILER_IS_GNUCC)
