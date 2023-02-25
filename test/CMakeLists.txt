### DEPENDENCIES ###############################################################

find_package(GTest CONFIG REQUIRED)

### QC-CORE-TEST ###############################################################

qc_setup_target(
    test
    EXECUTABLE
    PRIVATE_LINKS
        qc-core-platform
        GTest::gtest_main
)
