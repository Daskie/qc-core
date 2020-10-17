add_executable(qc-core-test
        test-core.cpp
        test-matrix.cpp
        test-quaternion.cpp
        test-span.cpp
        test-vector.cpp)

target_include_directories(qc-core-test PRIVATE ${gtest_SOURCE_DIR}/include)
target_link_libraries(qc-core-test PRIVATE gtest gtest_main qc-core)
