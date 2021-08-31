### DEPENDENCIES ###############################################################

find_package(GTest CONFIG REQUIRED)

### QC-CORE-TEST ###############################################################

file(GLOB SRC_FILES *.cpp)

add_executable(qc-core-test ${SRC_FILES})

target_compile_options(qc-core-test PRIVATE ${QC_WARNINGS_ERROR})

target_link_libraries(
    qc-core-test
    PRIVATE
        qc-core
        GTest::gtest_main
)
