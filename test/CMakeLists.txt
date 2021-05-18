### DEPENDENCIES ###

# GTest
find_package(GTest CONFIG REQUIRED)

### QC-CORE-TEST ###

file(GLOB qc-core-test_SRC *.cpp)

add_executable(qc-core-test ${qc-core-test_SRC})

# Link executable statically
set_property(TARGET qc-core-test PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

if(MSVC)
    target_compile_options(qc-core-test PRIVATE /W4 /WX)
else()
    add_compile_options(qc-core-test PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(
    qc-core-test
    PRIVATE
        GTest::gtest_main
        qc-core
)
