if(NOT PKG_CONFIG_FOUND)
    INCLUDE(FindPkgConfig)
endif()
PKG_CHECK_MODULES(PC_INTEGRATOR integrator)

FIND_PATH(
    INTEGRATOR_INCLUDE_DIRS
    NAMES integrator/api.h
    HINTS $ENV{INTEGRATOR_DIR}/include
        ${PC_INTEGRATOR_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    INTEGRATOR_LIBRARIES
    NAMES gnuradio-integrator
    HINTS $ENV{INTEGRATOR_DIR}/lib
        ${PC_INTEGRATOR_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/integratorTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(INTEGRATOR DEFAULT_MSG INTEGRATOR_LIBRARIES INTEGRATOR_INCLUDE_DIRS)
MARK_AS_ADVANCED(INTEGRATOR_LIBRARIES INTEGRATOR_INCLUDE_DIRS)
