include(FetchContent)

### DEPENDENCIES ###

# googletest
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git)
FetchContent_MakeAvailable(googletest)

### QC-CORE-TEST ###

file(GLOB qc-core-test_SRC *.cpp)

add_executable(qc-core-test ${qc-core-test_SRC})

target_link_libraries(
    qc-core-test
    PRIVATE
        gtest_main
        qc-core
)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(qc-core-test PRIVATE -Wno-unused-value -Wno-unused-variable)
endif ()
