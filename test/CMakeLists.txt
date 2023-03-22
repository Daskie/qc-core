find_package(GTest CONFIG REQUIRED)

qc_setup_target(
    test
    EXECUTABLE
    PRIVATE_LINKS
        qc-core-cpu
        GTest::gtest_main
    DISABLE_LTO
)
