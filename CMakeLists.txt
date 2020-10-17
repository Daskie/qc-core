cmake_minimum_required(VERSION 3.17)
project(qc-core)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(extern)
add_subdirectory(test)

add_library(qc-core INTERFACE)

target_include_directories(qc-core INTERFACE include)
