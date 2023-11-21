macro(set_default_properties)
    include(ProcessorCount)
    ProcessorCount(THREADS_COUNT)
    if(NOT THREADS_COUNT)
        set(N THREADS_COUNT)
    endif()
    set(CMAKE_BUILD_PARALLEL_LEVEL ${THREADS_COUNT})

    set(CMAKE_C_STANDARD 17)
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_C_FLAGS
            "${CMAKE_C_FLAGS}     \
            -Werror               \
            -pedantic-errors      \
            -Wall                 \
            -Wextra               \
            -Wpedantic            \
            -Wcast-align          \
            -Wcast-qual           \
            -Wconversion          \
            -Wduplicated-branches \
            -Wduplicated-cond     \
            -Wfloat-equal         \
            -Wlogical-op          \
            -Wredundant-decls     \
            -Wsign-conversion")
    endif()
endmacro()
