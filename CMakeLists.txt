cmake_minimum_required(VERSION 3.17)

project(qc-core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DEBUG_POSTFIX -d)

# Retrieve common CMake stuff
include(FetchContent)
FetchContent_Declare(qc-cmake GIT_REPOSITORY https://github.com/Daskie/qc-cmake.git)
FetchContent_MakeAvailable(qc-cmake)

### QC-CORE ####################################################################

add_library(qc-core INTERFACE)

target_include_directories(
    qc-core
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

### SUBDIRECTORIES #############################################################

add_subdirectory(test EXCLUDE_FROM_ALL)

### INSTALL ####################################################################

qc_install()
