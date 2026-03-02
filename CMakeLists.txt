cmake_minimum_required(VERSION 3.28)
set(CMAKE_SUPPRESS_REGENERATION ON)
project(my_project LANGUAGES C CXX)
set_property(GLOBAL PROPERTY CMAKE_SUPPRESS_REGENERATION ON)

set(TUDAT_BUILD_WITH_SOFA_INTERFACE OFF CACHE BOOL "Disable SOFA interface")
set(TUDAT_BUILD_WITH_ESTIMATION_TOOLS OFF CACHE BOOL "Disable Tudat estimation stack")
set(TUDAT_BUILD_TESTS OFF CACHE BOOL "Disable Tudat tests")
set(TUDAT_BUILD_TUDAT_TUTORIALS OFF CACHE BOOL "Disable Tudat tutorials")
# set(CSPICE_BUILD_STATIC_LIBRARY OFF CACHE BOOL "Enable or disable static library" FORCE)

# add find module, to resolve require in tudat
# really should move this locally
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extern/nrlmsise-00-cmake/cmake/Modules")
# fakes the tudat install, so the find_package in tudat doesn't break the build
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")
include_directories(BEFORE "${CMAKE_SOURCE_DIR}/cmake/sofa_stub")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CMAKE_SOURCE_DIR}/cmake/sofa_stub")
add_compile_options("-I${CMAKE_SOURCE_DIR}/cmake/sofa_stub")


add_subdirectory(extern/cspice-cmake)
add_subdirectory(extern/nrlmsise-00-cmake)
add_subdirectory(extern/tudat-resources)

# Ensure Tudat sees local build-tree packages/includes when added as subdirectory.
set(TudatResources_DIR
    "${CMAKE_BINARY_DIR}/extern/tudat-resources/lib/cmake/tudatresources"
    CACHE PATH "Path to local TudatResources config")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/cspice-cmake/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/nrlmsise-00-cmake/include)

add_subdirectory(extern/tudat)
# Tudat currently always includes tleEphemeris.cpp, which depends on SOFA headers
# even when TUDAT_BUILD_WITH_SOFA_INTERFACE is disabled.
set_source_files_properties(
    "tleEphemeris.cpp"
    TARGET_DIRECTORY tudat_ephemerides
    PROPERTIES HEADER_FILE_ONLY ON
)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(my_project src/main.cpp)
target_compile_definitions(my_project PRIVATE
    PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)
target_include_directories(my_project PRIVATE
    # tudat-resources generates config.hpp in its build tree.
    ${CMAKE_BINARY_DIR}/extern/tudat-resources/include
)

target_link_libraries(my_project PRIVATE
    ${Tudat_PROPAGATION_LIBRARIES}
    Eigen3::Eigen
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)
