cmake_minimum_required(VERSION 3.28)
project(my_project LANGUAGES C CXX)

set(TUDAT_BUILD_WITH_SOFA_INTERFACE OFF CACHE BOOL "Disable SOFA interface" FORCE)
# set(CSPICE_BUILD_STATIC_LIBRARY OFF CACHE BOOL "Enable or disable static library" FORCE)

# add find module, to resolve require in tudat
# really should move this locally
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extern/nrlmsise-00-cmake/cmake/Modules")
# fakes the tudat install, so the find_package in tudat doesn't break the build
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")


add_subdirectory(extern/cspice-cmake)
add_subdirectory(extern/nrlmsise-00-cmake)
add_subdirectory(extern/tudat-resources)
add_subdirectory(extern/tudat)
include_directories(${TUDAT_ROOT_DIR}/include)

find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(TudatResources REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(my_project src/main.cpp)
target_include_directories(my_project PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/extern/tudat/include
)

target_link_libraries(my_project PRIVATE
    CSpice::CSpice
    nrlmsise::nrlmsise
    tudat_simulation
    tudat_input_output
    tudat_astrodynamics
    Eigen3::Eigen
    ${Boost_LIBRARIES}
)

