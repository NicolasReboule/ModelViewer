//
// Created by nicol on 29/12/2024.
//

#include "example.hpp"

#include <gtest/gtest.h>

TEST(ExampleTest, PrintHello) {
    testing::internal::CaptureStdout();
    example::ExampleClass::printHello();
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Hello new project!\n");
}

TEST(ExampleTest, PrintHelloFail) {
    testing::internal::CaptureStdout();
    example::ExampleClass::printHello();
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output, "Hello new project\n");
}