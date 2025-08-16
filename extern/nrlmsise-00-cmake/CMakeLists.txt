cmake_minimum_required(VERSION 3.16)

# Project
project(nrlmsise-00
  VERSION 1.0.0
  DESCRIPTION "NRLMSISE-00 empirical atmosphere model (C implementation)"
  LANGUAGES C)

# Sources (repo has these files in the top-level directory)
set(NRLMSISE_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/nrlmsise-00.c
  ${CMAKE_CURRENT_SOURCE_DIR}/nrlmsise-00_data.c
)

# Library
# Honors BUILD_SHARED_LIBS if set by the parent (STATIC by default).
add_library(nrlmsise ${NRLMSISE_SOURCES})
add_library(nrlmsise::nrlmsise ALIAS nrlmsise)

# Public headers live in the repo root
target_include_directories(nrlmsise
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/nrlmsise-00> # if you ever install()
)

# Require C99 and make it PIC so it links cleanly into shared libs
target_compile_features(nrlmsise PUBLIC c_std_99)
set_target_properties(nrlmsise PROPERTIES
  POSITION_INDEPENDENT_CODE ON
  OUTPUT_NAME "nrlmsise-00"
)

# Optionally build the bundled example/test program
option(NRLMSISE_BUILD_EXAMPLE "Build the nrlmsise-00_test example" OFF)
if(NRLMSISE_BUILD_EXAMPLE)
  add_executable(nrlmsise_example ${CMAKE_CURRENT_SOURCE_DIR}/nrlmsise-00_test.c)
  target_link_libraries(nrlmsise_example PRIVATE nrlmsise)
  # libm needed on Linux for math functions used by the test
  if(UNIX AND NOT APPLE)
    target_link_libraries(nrlmsise_example PRIVATE m)
  endif()
endif()

# (Optional) basic install rules if you ever want to 'make install'
# install(TARGETS nrlmsise
#   ARCHIVE DESTINATION lib
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION bin
#   INCLUDES DESTINATION include/nrlmsise-00)
# install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/nrlmsise-00.h
#   DESTINATION include/nrlmsise-00)











# # CMakeLists.txt (place in the root of nrlmsise-00-cmake)
# cmake_minimum_required(VERSION 3.14)

# project(nrlmsise-00 LANGUAGES C)

# # Honor BUILD_SHARED_LIBS if the parent wants a shared lib
# add_library(nrlmsise00
#     nrlmsise-00.c
#     nrlmsise-00_data.c
# )

# # Friendly namespaced alias target
# add_library(nrlmsise-00::nrlmsise-00 ALIAS nrlmsise00)

# # Public headers live in this repo root (header name has a dash, that’s fine)
# target_include_directories(nrlmsise00
#     PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
#         $<INSTALL_INTERFACE:include/nrlmsise-00>
# )

# # Sensible defaults
# set_target_properties(nrlmsise00 PROPERTIES
#     C_STANDARD 99
#     C_STANDARD_REQUIRED YES
#     C_EXTENSIONS NO
#     POSITION_INDEPENDENT_CODE YES
#     OUTPUT_NAME "nrlmsise00"           # artifact name without dash
# )

# option(NRLMSISE_ENABLE_WARNINGS "Enable extra warnings for this target" OFF)
# if(NRLMSISE_ENABLE_WARNINGS)
#     if(MSVC)
#         target_compile_options(nrlmsise00 PRIVATE /W4)
#     else()
#         target_compile_options(nrlmsise00 PRIVATE -Wall -Wextra -Wpedantic)
#     endif()
# endif()

# # Optional: build the tiny upstream test program
# option(NRLMSISE_BUILD_TESTS "Build upstream nrlmsise-00_test" OFF)
# if(NRLMSISE_BUILD_TESTS)
#     add_executable(nrlmsise-00_test nrlmsise-00_test.c)
#     target_link_libraries(nrlmsise-00_test PRIVATE nrlmsise-00::nrlmsise-00)
# endif()

# # Optional: basic install rules, so you can also `make install`
# include(GNUInstallDirs)
# install(TARGETS nrlmsise00
#     EXPORT nrlmsise-00Targets
#     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#     INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nrlmsise-00
# )
# install(FILES nrlmsise-00.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nrlmsise-00)
# install(EXPORT nrlmsise-00Targets
#     NAMESPACE nrlmsise-00::
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nrlmsise-00
# )
