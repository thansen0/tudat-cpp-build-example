# Try to reuse your already-built target
if (TARGET nrlmsise::nrlmsise)
  # Provide an imported shim with the name Tudat expects
  add_library(nrlmsise00::nrlmsise00 INTERFACE IMPORTED)
  target_link_libraries(nrlmsise00::nrlmsise00 INTERFACE nrlmsise::nrlmsise)

  # Conventional Find-module variables (helps some consumers)
  get_target_property(_incs nrlmsise::nrlmsise INTERFACE_INCLUDE_DIRECTORIES)
  set(nrlmsise00_INCLUDE_DIRS "${_incs}")
  set(nrlmsise00_VERSION "1.0.0") # Version not enforced in Module mode, but harmless
  set(nrlmsise00_FOUND TRUE)
  return()
endif()

# Fallback: locate system install
find_path(nrlmsise00_INCLUDE_DIR NAMES nrlmsise-00.h)
find_library(nrlmsise00_LIBRARY  NAMES nrlmsise-00 nrlmsise)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(nrlmsise00
  REQUIRED_VARS nrlmsise00_LIBRARY nrlmsise00_INCLUDE_DIR)
if (nrlmsise00_FOUND AND NOT TARGET nrlmsise00::nrlmsise00)
  add_library(nrlmsise00::nrlmsise00 UNKNOWN IMPORTED)
  set_target_properties(nrlmsise00::nrlmsise00 PROPERTIES
    IMPORTED_LOCATION "${nrlmsise00_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${nrlmsise00_INCLUDE_DIR}")
endif()

