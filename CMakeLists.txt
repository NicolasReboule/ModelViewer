cmake_minimum_required(VERSION 3.29)
project(
        CPPTemplate
        VERSION 0.0.1
        DESCRIPTION "A simple C++ project template"
        HOMEPAGE_URL "https://github.com/NicolasReboule/CPPTemplate"
        LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_PARALLEL_LEVEL 8)

option(BUILD_COVERAGE "Build the coverage" OFF)
option(BUILD_TESTS "Build the tests" OFF)
option(USE_CLANG_TIDY "Use clang-tidy" OFF) # Used by the CI
option(USE_CLANG_TIDY_WITH_ERRORS "Use clang tidy but all warnings are errors" OFF) # Used by the CI
option(USE_CLANG_TIDY_WITH_FIX "Use clang-tidy with fix" OFF) # Used by the CI

# Headers
add_library(${PROJECT_NAME}_Headers INTERFACE)
target_include_directories(${PROJECT_NAME}_Headers INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Coverage
if(BUILD_COVERAGE)
    target_compile_options(${PROJECT_NAME}_Headers INTERFACE --coverage)
    target_link_options(${PROJECT_NAME}_Headers INTERFACE --coverage)
endif()

# Sources
add_library(${PROJECT_NAME}_Sources STATIC
        src/example.cpp
)
target_link_libraries(${PROJECT_NAME}_Sources PUBLIC ${PROJECT_NAME}_Headers)

# Main executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_Sources)

# Compiler Warnings
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Tests
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# CLang-tidy
if (USE_CLANG_TIDY OR USE_CLANG_TIDY_WITH_ERRORS OR USE_CLANG_TIDY_WITH_FIX)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy-19")
    if (NOT CLANG_TIDY_EXE)
        message(WARNING "clang-tidy not found.")
    else ()
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        if (USE_CLANG_TIDY_WITH_FIX)
            set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "--fix" "--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")
        elseif (USE_CLANG_TIDY_WITH_ERRORS)
            set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "--warnings-as-errors=*" "--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")
        else ()
            set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")
        endif ()
        set_target_properties(${BINARY_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
    endif ()
endif ()
