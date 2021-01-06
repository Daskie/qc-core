cmake_minimum_required(VERSION 3.17)
project(qc-core)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(test)

# qc-core

add_library(qc-core INTERFACE)

target_include_directories(qc-core INTERFACE include)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(qc-core INTERFACE -Wall -Werror -Wextra -Wpedantic)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options(qc-core INTERFACE /W4 /WX)
endif()
