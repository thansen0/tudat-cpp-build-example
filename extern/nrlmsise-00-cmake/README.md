# nrlmsise-00

This repository has been copied directly from https://www.brodo.de/space/nrlmsise/ for use in the TU Delft Astrodynamics Toolbox (Tudat) ecosystem. The copyright of the code belongs to Dominik Brodowski.

* This repo was cloned from [tudat's fork](https://github.com/tudat-team/nrlmsise-00-cmake) and committed it directly to the project, insteading of forking through github.
* It can be added to projects as `nrlmsise::nrlmsise` in your `target_link_libraries(proj_name PRIVATE ...)`
* I have updated the build system to include a `CMakeLists.txt` which can be added to the main CMakeLists.txt file using the following script:

```
add_subdirectory(extern/nrlmsise-00-cmake)
```


