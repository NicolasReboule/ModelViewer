cmake_minimum_required(VERSION 3.29)
project(
        ModelViewer
        VERSION 0.0.1
        DESCRIPTION "A simple C++ project template"
        HOMEPAGE_URL "https://github.com/NicolasReboule/ModelViewer"
        LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_PARALLEL_LEVEL 8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

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

# QT
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Qml Quick Quick3D)
qt_standard_project_setup(REQUIRES 6.5)

# Sources
add_library(${PROJECT_NAME}_Sources STATIC
        src/example.cpp
        src/ObjLoader.cpp
        include/ObjLoader.hpp # So moc file is generated using AUTOMOC
        src/ObjGeometry.cpp
        include/ObjGeometry.hpp
        src/ModelManager.cpp
        include/ModelManager.hpp
        src/Material.cpp
        include/Material.hpp
)
target_link_libraries(${PROJECT_NAME}_Sources PUBLIC
        ${PROJECT_NAME}_Headers
        Qt6::Core
        Qt6::Qml
        Qt6::Quick
        Qt6::Quick3D
)

# Main executable with QT
qt_add_executable(${PROJECT_NAME}
        main.cpp
        application.qrc
)

#qt_add_qml_module(${PROJECT_NAME}
#        URI main
#        VERSION 1.0
#        QML_FILES main.qml
#)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${PROJECT_NAME}_Sources
)

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

file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

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

# Deploy Qt (Add DLLs, ...)
if (WIN32)
    # Find windeployqt
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

    set(WINDEPLOYQT_EXECUTABLE "${_qt_bin_dir}/windeployqt.exe")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            --no-translations
            --no-opengl-sw
            --qmldir "${CMAKE_SOURCE_DIR}"
            "$<TARGET_FILE:${PROJECT_NAME}>"
            COMMENT "Running windeployqt..."
    )
endif()
