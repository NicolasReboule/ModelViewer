/*
** EPITECH PROJECT, 2026
** string_helpers_tests.cpp
** File description:
** string_helpers_tests.cpp
*/

#include <gtest/gtest.h>

#include "Helpers/StringHelpers.hpp"

// Tests for the copy-returning variants
TEST(StringHelpers, TrimInPlaceVariants) {
    std::string lsrc = "   hello   ";
    // Left trim
    model_viewer::string_helpers::ltrim(lsrc);
    ASSERT_EQ(lsrc, "hello   ");

    std::string rsrc = "   hello   ";
    // Right trim
    model_viewer::string_helpers::rtrim(rsrc);
    ASSERT_EQ(rsrc, "   hello");

    std::string src = "   hello   ";
    // Full trim
    model_viewer::string_helpers::trim(src);
    ASSERT_EQ(src, "hello");
}

TEST(StringHelpers, TrimNoLeadingWhitespace) {
    std::string s = "hello   ";
    model_viewer::string_helpers::ltrim(s);
    ASSERT_EQ(s, "hello   ");
}

TEST(StringHelpers, TrimNoEndingWhitespace) {
    std::string s = "   hello";
    model_viewer::string_helpers::rtrim(s);
    ASSERT_EQ(s, "   hello");
}

// Tests for the copy-returning variants
TEST(StringHelpers, TrimCopyVariants) {
    std::string original = "   hello   ";

    // ltrim_copy should not modify the original
    std::string lcopy = model_viewer::string_helpers::ltrim_copy(original);
    ASSERT_EQ(lcopy, "hello   ");
    ASSERT_EQ(original, "   hello   ");

    // rtrim_copy
    std::string rcopy = model_viewer::string_helpers::rtrim_copy(original);
    ASSERT_EQ(rcopy, "   hello");
    ASSERT_EQ(original, "   hello   ");

    // trim_copy
    std::string tcopy = model_viewer::string_helpers::trim_copy(original);
    ASSERT_EQ(tcopy, "hello");
    ASSERT_EQ(original, "   hello   ");
}

TEST(StringHelpers, TrimEdgeCases) {
    // Empty string
    std::string empty = "";
    model_viewer::string_helpers::trim(empty);
    ASSERT_EQ(empty, "") << "Empty string should remain empty";

    // String with only whitespace
    std::string onlyWs = " \t\n  \r\n";
    model_viewer::string_helpers::trim(onlyWs);
    ASSERT_EQ(onlyWs, "") << "Whitespace-only string should become empty";
}

TEST(StringHelpers, NormalizePath) {
    // file:// scheme removed, unix absolute path remains absolute
    std::string p1 = "file:///home/user/file.txt";
    ASSERT_EQ(model_viewer::string_helpers::normalizePath(p1),
              "/home/user/file.txt");

    // file:// with Windows drive: remove leading slash
    std::string p2 = "file:///C:/path/to/file.txt";
    ASSERT_EQ(model_viewer::string_helpers::normalizePath(p2),
              "C:/path/to/file.txt");

    // Leading slash before Windows drive without file://
    std::string p3 = "/D:/another/path";
    ASSERT_EQ(model_viewer::string_helpers::normalizePath(p3),
              "D:/another/path");

    // Already-normal windows path
    std::string p4 = "E:/ok/path";
    ASSERT_EQ(model_viewer::string_helpers::normalizePath(p4), "E:/ok/path");

    // Relative path with file:// should have scheme removed
    std::string p5 = "file://relative/path";
    ASSERT_EQ(model_viewer::string_helpers::normalizePath(p5), "relative/path");

    // Empty path stays empty
    std::string p6 = "";
    ASSERT_EQ(model_viewer::string_helpers::normalizePath(p6), "");
}
