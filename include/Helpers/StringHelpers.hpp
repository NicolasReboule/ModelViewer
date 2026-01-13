/*
** EPITECH PROJECT, 2026
** StringHelpers.hpp
** File description:
** StringHelpers.hpp
*/

#ifndef MODELVIEWER_STRINGHELPERS_HPP
#define MODELVIEWER_STRINGHELPERS_HPP

// Source - https://stackoverflow.com/a
// Posted by Evan Teran, modified by community. See post 'Timeline' for change
// history Retrieved 2026-01-02, License - CC BY-SA 4.0

#include <algorithm>
#include <cctype>
#include <locale>

namespace model_viewer::string_helpers {

inline bool isNotSpace(const unsigned char ch) noexcept {
    return std::isspace(ch) == 0;
}

/**
 * @brief Trim from the start (in place)
 * @param s String to trim
 */
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::ranges::find_if(s, isNotSpace));
}

/**
 * @brief Trim from the end (in place)
 * @param s String to trim
 */
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
}

/**
 * @brief Trim from both ends (in place)
 * @param s String to trim
 */
inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

/**
 * @brief Trim from the start (copying)
 * @param s String to trim
 * @return Trimmed string
 */
inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

/**
 * @brief Trim from the end (copying)
 * @param s String to trim
 * @return Trimmed string
 */
inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

/**
 * @brief Trim from both ends (copying)
 * @param s String to trim
 * @return Trimmed string
 */
inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

/**
 * @brief Normalize a file path by removing "file://" scheme and leading slash
 *        on Windows paths
 * @param p Path to normalize
 * @return Normalized path
 */
inline std::string normalizePath(std::string p) {
    const std::string fileScheme = "file://";
    if (p.rfind(fileScheme, 0) == 0) {
        p.erase(0, fileScheme.size());
    }
    if (p.size() >= 3 && p[0] == '/' &&
        std::isalpha(static_cast<unsigned char>(p[1])) && p[2] == ':') {
        p.erase(0, 1);
    }
    return p;
}

}  // namespace model_viewer::string_helpers

#endif  // MODELVIEWER_STRINGHELPERS_HPP
