### DEPENDENCIES ###############################################################

find_package(GTest CONFIG REQUIRED)

### QC-CORE-TEST ###############################################################

set(NAME ${PROJECT_NAME}-test)

file(GLOB ${NAME}_SRC *.cpp)

add_executable(${NAME} ${${NAME}_SRC})

if(MSVC)
    target_compile_options(${NAME} PRIVATE /W4 /WX)
else()
    message(FATAL_ERROR "TODO")
endif()

target_link_libraries(
    ${NAME}
    PRIVATE
        ${PROJECT_NAME}
        GTest::gtest_main
)
