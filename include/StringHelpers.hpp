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

// Trim from the start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
}

// Trim from the end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
}

// Trim from both ends (in place)
inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

// Trim from the start (copying)
inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// Trim from the end (copying)
inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// Trim from both ends (copying)
inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

inline std::string normalizePath(std::string p)
{
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

#endif  // MODELVIEWER_STRINGHELPERS_HPP
