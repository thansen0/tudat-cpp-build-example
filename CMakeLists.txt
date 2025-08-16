cmake_minimum_required(VERSION 3.28)
project(tudat_cpp LANGUAGES C CXX)

# I'm not sure what SOFA is but it causes all sorts of issues
set(TUDAT_BUILD_WITH_SOFA_INTERFACE OFF CACHE BOOL "Disable SOFA interface" FORCE)

# add find module, to resolve require in tudat
# really should move this locally
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extern/nrlmsise-00-cmake/cmake/Modules")

# custom-compiled external code
add_subdirectory(extern/nrlmsise-00-cmake)
add_subdirectory(extern/tudat-resources)
add_subdirectory(extern/tudat)

# required packages, tudat resources bundles things like cspice
find_package(Eigen3 3.3 REQUIRED CONFIG)
find_package(Boost 1.72 REQUIRED COMPONENTS filesystem system)
find_package(TudatResources REQUIRED)

add_executable(tudat_cpp src/main.cpp)

# link custom libraries to target
target_link_libraries(tudat_cpp PRIVATE
    nrlmsise::nrlmsise
    tudat_simulation
    tudat_input_output
    tudat_astrodynamics
    Eigen3::Eigen
    Boost::filesystem
    Boost::system
)








# # OLD cmakelists file, which also didn't really work
# cmake_minimum_required(VERSION 3.28)
# if(POLICY CMP0024)
#   cmake_policy(SET CMP0024 OLD)
# endif()

# project(my_project LANGUAGES CXX)

# set(TUDAT_BUILD_WITH_SOFA_INTERFACE OFF CACHE BOOL "Disable SOFA interface" FORCE)

# # list(APPEND CMAKE_PREFIX_PATH
# #      "${CMAKE_SOURCE_DIR}/extern/cspice-build")
# # find_package(CSpice REQUIRED 1.0.0)

# add_subdirectory(extern/cspice-cmake
#                  ${CMAKE_BINARY_DIR}/extern/cspice-build)
# # list(APPEND CMAKE_PREFIX_PATH
# #      "${CMAKE_BINARY_DIR}/cspice-build")
# # find_package(CSpice   REQUIRED 1.0.0)
# add_library(CSpice::CSpice ALIAS cspice)

# add_subdirectory(extern/nrlmsise-00-cmake)

# add_subdirectory(extern/tudat-resources
#                  extern/tudat-resources-build)

# add_subdirectory(extern/tudat
#                  extern/tudat-build)
# include_directories(${TUDAT_ROOT_DIR}/include)

# find_package(Boost REQUIRED COMPONENTS filesystem system)
# find_package(Eigen3 3.3 REQUIRED NO_MODULE)
# find_package(TudatResources REQUIRED)

# include_directories(${Boost_INCLUDE_DIRS})

# add_executable(my_project src/main.cpp)
# target_include_directories(my_project PRIVATE
#     ${Boost_INCLUDE_DIRS}
#     ${CMAKE_SOURCE_DIR}/extern/tudat/include
# )

# target_link_libraries(my_project PRIVATE
#     CSpice::CSpice
#     nrlmsise::nrlmsise
#     tudat_simulation
#     tudat_input_output
#     tudat_astrodynamics
#     Eigen3::Eigen
#     ${Boost_LIBRARIES}
# )

