### DEPENDENCIES ###############################################################

find_package(GTest CONFIG REQUIRED)

### QC-CORE-TEST ###############################################################

qc_setup_target(
    qc-core-test-bubble-tracker
    EXECUTABLE
    SOURCE_FILES
        test-bubble-tracker.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-color
    EXECUTABLE
    SOURCE_FILES
        test-color.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-core
    EXECUTABLE
    SOURCE_FILES
        test-core.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-enum-utils
    EXECUTABLE
    SOURCE_FILES
        test-enum-utils.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-fixed-pool
    EXECUTABLE
    SOURCE_FILES
        test-fixed-pool.cpp
    PRIVATE_LINKS
        qc-core-platform
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-kd-tree
    EXECUTABLE
    SOURCE_FILES
        test-kd-tree.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-matrix
    EXECUTABLE
    SOURCE_FILES
        test-matrix.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-paging
    EXECUTABLE
    SOURCE_FILES
        test-paging.cpp
    PRIVATE_LINKS
        qc-core-platform
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-pool
    EXECUTABLE
    SOURCE_FILES
        test-pool.cpp
    PRIVATE_LINKS
        qc-core-platform
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-quaternion
    EXECUTABLE
    SOURCE_FILES
        test-quaternion.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-span
    EXECUTABLE
    SOURCE_FILES
        test-span.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-semi-stable-deque
    EXECUTABLE
    SOURCE_FILES
        test-semi-stable-deque.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-unique-ordered-vector
    EXECUTABLE
    SOURCE_FILES
        test-unique-ordered-vector.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    qc-core-test-vector
    EXECUTABLE
    SOURCE_FILES
        test-vector.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)
