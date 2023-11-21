cmake_minimum_required(VERSION 3.25)
project(SBUSParser)

include(cmake_scripts/set_default_properties.cmake)
set_default_properties()

set(LIB_INCLUDE_DIR include)

set(LIB_FUNC_FILES parse_sbus print_sbus_decode)

set(LIB_HEADERS ${LIB_FUNC_FILES} sbus_defs)
list(TRANSFORM LIB_HEADERS PREPEND ${LIB_INCLUDE_DIR}/)
list(TRANSFORM LIB_HEADERS APPEND .h)

set(LIB_SOURCES ${LIB_FUNC_FILES})
list(TRANSFORM LIB_SOURCES PREPEND src/)
list(TRANSFORM LIB_SOURCES APPEND .c)
set(LIB_SOURCES ${LIB_HEADERS} ${LIB_SOURCES})

add_library(SBUSParser ${LIB_SOURCES})

target_include_directories(SBUSParser PRIVATE ${LIB_INCLUDE_DIR})

if(NOT CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(SBUSParser_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_INCLUDE_DIR} PARENT_SCOPE)
endif()
