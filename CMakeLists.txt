cmake_minimum_required(VERSION 3.10)
project(PushdOut)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Move executables to 'bin' folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin)
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

## Compiler Flags
if (MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

## Project Setup

add_subdirectory(engine)
add_subdirectory(game)

## External tools/libs

include_directories(${CMAKE_SOURCE_DIR}/external)

## Tests
add_subdirectory(tests)

enable_testing()
add_test(
    NAME UnitTests COMMAND tests
)

## Clang Tidy
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_BIN clang-tidy-6.0)
    find_program(RUN_CLANG_TIDY_BIN run-clang-tidy-6.0)

    if(CLANG_TIDY_BIN STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate clang-tidy-6.0")
    endif()

    if(RUN_CLANG_TIDY_BIN STREQUAL "RUN_CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate run-clang-tidy-6.0.py")
    endif()

    list(APPEND RUN_CLANG_TIDY_BIN_ARGS
        -clang-tidy-binary ${CLANG_TIDY_BIN}
        -checks=*,-android*,-fuchsia*,-google-readability*,-llvm*,-hicpp-signed-bitwise,-hicpp-braces-around-statements,-google-build-using-namespace,-google-runtime-references,-cert-err58-cpp,-hicpp-noexcept-move,-performance-noexcept-move-constructor,-cppcoreguidelines-special-member-functions,-google-runtime-int
    )

    add_custom_target(
        tidy
        COMMAND ${RUN_CLANG_TIDY_BIN} ${RUN_CLANG_TIDY_BIN_ARGS}
    )
endif()

