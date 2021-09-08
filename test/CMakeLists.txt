### DEPENDENCIES ###############################################################

find_package(GTest CONFIG REQUIRED)

### QC-CORE-TEST ###############################################################

qc_setup_target(
    qc-core-test
    EXECUTABLE
    PRIVATE_LINKS
        qc-core
        GTest::gtest_main
)
