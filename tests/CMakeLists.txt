include(CTest)
# Get Google tests
include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test Executable
add_executable(${PROJECT_NAME}_Tests
        src/general_tests.cpp
        src/model_manager_tests.cpp
        src/obj_loader_tests.cpp
        src/string_helpers_tests.cpp
)
# Link headers
target_include_directories(${PROJECT_NAME}_Tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
# Link gtest
target_link_libraries(${PROJECT_NAME}_Tests PRIVATE
        ${PROJECT_NAME}_Sources
        GTest::gtest_main
)

# Create tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_Tests)

find_package(Qt6 6.5 REQUIRED COMPONENTS Test)

qt_add_executable(${PROJECT_NAME}_Qt_Tests
        qt/qt_example_test.cpp
)

target_link_libraries(${PROJECT_NAME}_Qt_Tests PRIVATE
        ${PROJECT_NAME}_Sources
        Qt::Test
)
add_test(NAME ${PROJECT_NAME}_Qt_Tests COMMAND ${PROJECT_NAME}_Qt_Tests)


# Add custom cmake test to build
configure_file(
        ${CMAKE_SOURCE_DIR}/CTestCustom.cmake.in
        ${CMAKE_BINARY_DIR}/CTestCustom.cmake
        COPYONLY
)

# Deploy Qt (Add DLLs, ...)
if (WIN32)
    # Find windeployqt
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

    set(WINDEPLOYQT_EXECUTABLE "${_qt_bin_dir}/windeployqt.exe")
    add_custom_command(TARGET ${PROJECT_NAME}_Qt_Tests POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            --no-translations
            --no-opengl-sw
            --qmldir "${CMAKE_SOURCE_DIR}"
            "$<TARGET_FILE:${PROJECT_NAME}_Qt_Tests>"
            COMMENT "Running windeployqt..."
    )
endif()
