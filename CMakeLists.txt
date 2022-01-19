cmake_minimum_required(VERSION 3.20)

project(qc-core)

# Retrieve common CMake stuff
include(FetchContent)
FetchContent_Declare(qc-cmake GIT_REPOSITORY https://github.com/Daskie/qc-cmake.git)
FetchContent_MakeAvailable(qc-cmake)

### QC-CORE ####################################################################

qc_setup_target(qc-core INTERFACE_LIBRARY)

### SUBDIRECTORIES #############################################################

add_subdirectory(test EXCLUDE_FROM_ALL)

### INSTALL ####################################################################

qc_setup_install(TARGETS qc-core)
