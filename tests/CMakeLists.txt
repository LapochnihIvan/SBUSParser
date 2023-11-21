cmake_minimum_required(VERSION 3.25)
project(Tests)

include(../cmake_scripts/set_default_properties.cmake)
set_default_properties()

add_subdirectory(.. ./build)

include(CTest)

set(TESTS
    parsing_test)

foreach(TEST IN LISTS TESTS)
    add_executable(${TEST} src/${TEST}.c)
    add_test(
        NAME ${TEST}
        COMMAND $<TARGET_FILE:${TEST}>
    )

    target_link_libraries(${TEST} SBUSParser)
    target_include_directories(${TEST} PRIVATE ${SBUSParser_INCLUDE_DIR})
endforeach()
