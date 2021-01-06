include(FetchContent)

FetchContent_Declare(
        googletest
        SOURCE_DIR $ENV{DEV_DIR}/googletest)

FetchContent_MakeAvailable(googletest)

add_executable(qc-core-test
        test-core.cpp
        test-matrix.cpp
        test-quaternion.cpp
        test-span.cpp
        test-vector.cpp)

target_include_directories(qc-core-test PRIVATE ${gtest_SOURCE_DIR}/include)

target_link_libraries(qc-core-test PRIVATE gtest gtest_main qc-core)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(qc-core-test PRIVATE -Wno-unused-value -Wno-unused-variable)
endif ()
