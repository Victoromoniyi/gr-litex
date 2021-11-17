if(NOT PKG_CONFIG_FOUND)
    INCLUDE(FindPkgConfig)
endif()
PKG_CHECK_MODULES(PC_LITEXGNU litexgnu)

FIND_PATH(
    LITEXGNU_INCLUDE_DIRS
    NAMES litexgnu/api.h
    HINTS $ENV{LITEXGNU_DIR}/include
        ${PC_LITEXGNU_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    LITEXGNU_LIBRARIES
    NAMES gnuradio-litexgnu
    HINTS $ENV{LITEXGNU_DIR}/lib
        ${PC_LITEXGNU_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/litexgnuTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LITEXGNU DEFAULT_MSG LITEXGNU_LIBRARIES LITEXGNU_INCLUDE_DIRS)
MARK_AS_ADVANCED(LITEXGNU_LIBRARIES LITEXGNU_INCLUDE_DIRS)
