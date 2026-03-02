# Run a first pass for finding the headers only and establishing the Boost version.
set(_TUDAT_BOOST_MINIMUM_VERSION 1.72.0)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost ${_TUDAT_BOOST_MINIMUM_VERSION} QUIET REQUIRED)

if(_TUDAT_FIND_BOOST_PYTHON)
    # Since Boost 1.67, Boost.Python includes the major/minor Python version.
    if(${Boost_MAJOR_VERSION} GREATER 1 OR (${Boost_MAJOR_VERSION} EQUAL 1 AND ${Boost_MINOR_VERSION} GREATER 66))
        list(APPEND _TUDAT_REQUIRED_BOOST_LIBS "python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}")
    else()
        list(APPEND _TUDAT_REQUIRED_BOOST_LIBS python3)
    endif()
endif()

message(STATUS "Required Boost libraries: ${_TUDAT_REQUIRED_BOOST_LIBS}")
find_package(Boost ${_TUDAT_BOOST_MINIMUM_VERSION} REQUIRED COMPONENTS ${_TUDAT_REQUIRED_BOOST_LIBS})
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Not all requested Boost components were found, exiting.")
endif()

# Tudat appends `-isystem "${Boost_INCLUDE_DIRS}"` to CMAKE_CXX_FLAGS on UNIX.
# If this resolves to `/usr/include`, GCC can no longer resolve headers reached
# via `#include_next` from libstdc++ headers.
if(UNIX AND Boost_INCLUDE_DIRS STREQUAL "/usr/include")
    set(_TUDAT_BOOST_INCLUDE_SHIM "${CMAKE_BINARY_DIR}/boost_include_shim")
    if(NOT EXISTS "${_TUDAT_BOOST_INCLUDE_SHIM}/boost")
        file(MAKE_DIRECTORY "${_TUDAT_BOOST_INCLUDE_SHIM}")
        file(CREATE_LINK "/usr/include/boost" "${_TUDAT_BOOST_INCLUDE_SHIM}/boost" SYMBOLIC)
    endif()

    set(Boost_INCLUDE_DIR "${_TUDAT_BOOST_INCLUDE_SHIM}")
    set(Boost_INCLUDE_DIRS "${_TUDAT_BOOST_INCLUDE_SHIM}")
endif()

message(STATUS "Detected Boost version: ${Boost_VERSION}")
message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")

# Might need to recreate targets if they are missing (e.g., older CMake versions).
if(NOT TARGET Boost::boost)
    message(STATUS "The 'Boost::boost' target is missing, creating it.")
    add_library(Boost::boost INTERFACE IMPORTED)
    set_target_properties(Boost::boost PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIRS}")
endif()
if(NOT TARGET Boost::disable_autolinking)
    message(STATUS "The 'Boost::disable_autolinking' target is missing, creating it.")
    add_library(Boost::disable_autolinking INTERFACE IMPORTED)
    if(WIN32)
        set_target_properties(Boost::disable_autolinking PROPERTIES INTERFACE_COMPILE_DEFINITIONS "BOOST_ALL_NO_LIB")
    endif()
endif()
foreach(_TUDAT_BOOST_COMPONENT ${_TUDAT_REQUIRED_BOOST_LIBS})
    if(NOT TARGET Boost::${_TUDAT_BOOST_COMPONENT})
        message(STATUS "The 'Boost::${_TUDAT_BOOST_COMPONENT}' imported target is missing, creating it.")
        string(TOUPPER ${_TUDAT_BOOST_COMPONENT} _TUDAT_BOOST_UPPER_COMPONENT)
        if(Boost_USE_STATIC_LIBS)
            add_library(Boost::${_TUDAT_BOOST_COMPONENT} STATIC IMPORTED)
        else()
            add_library(Boost::${_TUDAT_BOOST_COMPONENT} UNKNOWN IMPORTED)
        endif()
        set_target_properties(Boost::${_TUDAT_BOOST_COMPONENT} PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIRS}")
        set_target_properties(Boost::${_TUDAT_BOOST_COMPONENT} PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
                IMPORTED_LOCATION "${Boost_${_TUDAT_BOOST_UPPER_COMPONENT}_LIBRARY}")
    endif()
endforeach()

unset(_TUDAT_BOOST_MINIMUM_VERSION)
unset(_TUDAT_REQUIRED_BOOST_LIBS)
unset(_TUDAT_BOOST_INCLUDE_SHIM)
