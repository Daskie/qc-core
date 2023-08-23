find_package(GTest REQUIRED)

qc_setup_target(
    test
    EXECUTABLE
    PRIVATE_LINKS
        qc-core-cpu
        gtest_main
    DISABLE_LTO
)
