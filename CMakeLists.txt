cmake_minimum_required(VERSION 3.23)

project(qc-core)

# Retrieve common CMake stuff
include(FetchContent)
FetchContent_Declare(qc-cmake GIT_REPOSITORY https://github.com/Daskie/qc-cmake.git)
FetchContent_MakeAvailable(qc-cmake)

add_subdirectory(qc-core)

add_subdirectory(qc-core-platform)

add_subdirectory(test)

qc_setup_install(TARGETS qc-core qc-core-platform)
