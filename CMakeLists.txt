cmake_minimum_required(VERSION 3.28)
project(my_project LANGUAGES CXX)

set(TUDAT_BUILD_WITH_SOFA_INTERFACE OFF CACHE BOOL "Disable SOFA interface" FORCE)
# set(TUDAT_BUILD_WITH_NRLMSISE00     OFF CACHE BOOL "" FORCE)


# list(APPEND CMAKE_PREFIX_PATH
#      "${CMAKE_SOURCE_DIR}/extern/cspice-build")
# find_package(CSpice REQUIRED 1.0.0)

add_subdirectory(extern/cspice-cmake
                 ${CMAKE_BINARY_DIR}/extern/cspice-build)
# list(APPEND CMAKE_PREFIX_PATH
#      "${CMAKE_BINARY_DIR}/cspice-build")
# find_package(CSpice   REQUIRED 1.0.0)
add_library(CSpice::CSpice ALIAS cspice)


add_subdirectory(extern/tudat-resources
                 extern/tudat-resources-build)

add_subdirectory(extern/tudat
                 extern/tudat-build)
include_directories(${TUDAT_ROOT_DIR}/include)

find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(TudatResources REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

target_include_directories(my_project PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/extern/tudat/include
)

add_executable(my_project src/main.cpp)
target_link_libraries(my_project PRIVATE CSpice::CSpice tudat_simulation tudat_input_output tudat_astrodynamics Eigen3::Eigen ${Boost_LIBRARIES})




# cmake_minimum_required(VERSION 3.28)
# project(MyTudatApp LANGUAGES CXX)

# set(TUDAT_BUILD_WITH_SOFA_INTERFACE OFF CACHE BOOL "Disable SOFA interface" FORCE)

# # 1) Build the TudatResources bundle
# add_subdirectory(extern/tudat-resources
#                  ${CMAKE_BINARY_DIR}/tudat-resources-build)

# set(CSpice_DIR "${CMAKE_BINARY_DIR}/cspice-build/lib/cmake/CSpice")
# # 2) Build the CSpice‑CMake wrapper *before* Tudat
# add_subdirectory(extern/cspice-cmake
#                  ${CMAKE_BINARY_DIR}/cspice-build)

# # 2b) Point CMake at the CSPICE package config
# #     Adjust this if your CSpiceConfig.cmake lives in a subfolder
# list(APPEND CMAKE_PREFIX_PATH
#      "${CMAKE_BINARY_DIR}/cspice-build"
# )

# find_package(CSpice   REQUIRED 1.0.0)   # <-- This will now succeed

# # 3) Now build Tudat (it can now find both Resources *and* CSpice)
# add_subdirectory(extern/tudat
#                  ${CMAKE_BINARY_DIR}/tudat-build)

# # 4) Find your other deps
# find_package(Boost    REQUIRED COMPONENTS filesystem system)
# find_package(Eigen3   3.3     REQUIRED NO_MODULE)
# find_package(TudatResources REQUIRED)

# # 5) Finally your app
# add_executable(my_project src/main.cpp)

# target_link_libraries(my_project PRIVATE
#     CSpice::CSpice             # brings in the CSPICE include dirs & library
#     tudat_simulation
#     tudat_input_output
#     tudat_astrodynamics
#     Eigen3::Eigen
#     ${Boost_LIBRARIES}
# )

