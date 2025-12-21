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
add_executable(src_example_tests
        src/example_test.cpp
)
# Link headers
target_include_directories(src_example_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
# Link gtest
target_link_libraries(src_example_tests PRIVATE GTest::gtest_main ${PROJECT_NAME}_Sources)

# Create tests
include(GoogleTest)
gtest_discover_tests(src_example_tests)

find_package(Qt6 6.5 REQUIRED COMPONENTS Test)

qt_add_executable(qt_example_tests
        qt/qt_example_test.cpp
)

target_link_libraries(qt_example_tests PRIVATE
        Qt::Test
)
add_test(NAME qt_example_tests COMMAND qt_example_tests)


# Add custom cmake test to build
configure_file(
        ${CMAKE_SOURCE_DIR}/CTestCustom.cmake.in
        ${CMAKE_BINARY_DIR}/CTestCustom.cmake
        COPYONLY
)