cmake_minimum_required(VERSION 3.23)

project(qc-core)

# Retrieve common CMake stuff
include(FetchContent)
FetchContent_Declare(qc-cmake GIT_REPOSITORY https://github.com/Daskie/qc-cmake.git)
FetchContent_MakeAvailable(qc-cmake)

### QC-CORE ####################################################################

qc_setup_target(qc-core INTERFACE_LIBRARY)

### QC-CORE-PAGING #############################################################

qc_setup_target(
    qc-core-platform
    STATIC_LIBRARY
    SOURCE_FILES
        source/paging.cpp
    PUBLIC_LINKS
        qc-core
)

### SUBDIRECTORIES #############################################################

add_subdirectory(test)

### INSTALL ####################################################################

qc_setup_install(TARGETS qc-core qc-core-platform)
