### DEPENDENCIES ###############################################################

find_package(GTest CONFIG REQUIRED)

### QC-CORE-TEST ###############################################################

qc_setup_target(
    test-arena
    EXECUTABLE
    SOURCE_FILES
        test-arena.cpp
    PRIVATE_LINKS
        qc-core-platform
        GTest::gtest_main
)

qc_setup_target(
    test-avl-tree
    EXECUTABLE
    SOURCE_FILES
        test-avl-tree.cpp
    PRIVATE_LINKS
        qc-core-platform
        GTest::gtest_main
)

qc_setup_target(
    test-bank
    EXECUTABLE
    SOURCE_FILES
        test-bank.cpp
    PRIVATE_LINKS
        qc-core-platform
        GTest::gtest_main
)

qc_setup_target(
    test-bubble-tracker
    EXECUTABLE
    SOURCE_FILES
        test-bubble-tracker.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-color
    EXECUTABLE
    SOURCE_FILES
        test-color.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-core
    EXECUTABLE
    SOURCE_FILES
        test-core.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-enum-utils
    EXECUTABLE
    SOURCE_FILES
        test-enum-utils.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-kd-tree
    EXECUTABLE
    SOURCE_FILES
        test-kd-tree.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-lock
    EXECUTABLE
    SOURCE_FILES
        test-lock.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-matrix
    EXECUTABLE
    SOURCE_FILES
        test-matrix.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-paging
    EXECUTABLE
    SOURCE_FILES
        test-paging.cpp
    PRIVATE_LINKS
        qc-core-platform
        GTest::gtest_main
)

qc_setup_target(
    test-pool
    EXECUTABLE
    SOURCE_FILES
        test-pool.cpp
    PRIVATE_LINKS
        qc-core-platform
        GTest::gtest_main
)

qc_setup_target(
    test-quaternion
    EXECUTABLE
    SOURCE_FILES
        test-quaternion.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-random
    EXECUTABLE
    SOURCE_FILES
        test-random.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-ring-deque
    EXECUTABLE
    SOURCE_FILES
        test-ring-deque.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-smart-pointer
    EXECUTABLE
    SOURCE_FILES
        test-smart-pointer.cpp
    PRIVATE_LINKS
        qc-core-platform
        GTest::gtest_main
)

qc_setup_target(
    test-span
    EXECUTABLE
    SOURCE_FILES
        test-span.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-semi-stable-deque
    EXECUTABLE
    SOURCE_FILES
        test-semi-stable-deque.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-unique-ordered-vector
    EXECUTABLE
    SOURCE_FILES
        test-unique-ordered-vector.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)

qc_setup_target(
    test-vector
    EXECUTABLE
    SOURCE_FILES
        test-vector.cpp
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)
