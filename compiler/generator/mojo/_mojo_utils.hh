/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _MOJO_UTILS_HH
#define _MOJO_UTILS_HH

// faust
#include "global.hh"

// mojo
#include "_mojo_hal.hh"
#include "_mojo_macro.hh"

namespace mojo {

//==============================================================
// Writing helpers for `MojoVisitor`s and `MojoCodeContainer`s 
// =============================================================

inline std::string wbanner()                   { return "# ------------------------------------------------------------------------------"; }
inline std::string wblank (isize n = 1)        { return std::string(n, '\n'); }
inline std::string windent(isize n = 4)        { return std::string(n, ' '); }
inline std::string wlit   (std::string s)      { return "\"" + s + "\""; }
inline std::string wendl  (b32 b, isize n = 1) { return b ? '\n' + windent(4*n) : ""; }
inline std::string wptr   (std::string s)      { return "Ptr["+s+"]"; }
inline std::string wtab   (isize n = 1)        { return std::string(4*n, ' '); }

inline std::string wrewind(std::ostream* out, isize n = 1)
{
    isize pos = out->tellp();
    out->seekp(pos - n * 4);
    return "";
}

inline std::string wmultilit(std::string&& s)
{
    std::ostringstream out;
    out << "\"";
    b32 prev_endl = false;
    for (auto i = s.begin(); i != s.end(); i++) {
        if (prev_endl) {
            prev_endl = false;
            while (i != s.end() && *i == ' ') {
               out << *i;
               i++;
            }
            out << "\"" << *i;
        } else if (*i == '\n') {
            prev_endl = true;
            out << "\"\n";
        } else {
            out << *i;
        }
    }
    out << "\"";
    return out.str();
}

// =============================================================
// String manip helpers for `Visitor`s and `CodeContainer`s
// =============================================================
 
inline std::string toStringTrim(f64 x)
{
    auto res = std::to_string(x);
    res.erase(res.find_last_not_of('0') + 1, std::string::npos);
    res.erase(res.find_last_not_of('.') + 1, std::string::npos);
    return res;
}

inline std::string ensureReal(std::string&& str)
{
    b32 is_int = true;
    std::ostringstream res;
    for (char const& c : str) {
        res << c;
        if (c == '.') {
            is_int = false;
        }
    }
    if (is_int) {
        res << ".0";
    }
    return res.str();
}

inline std::string ensureReal(f64 x)
{
    return ensureReal(toStringTrim(x));
}

inline std::vector<std::string_view> split(std::string_view src, char sep)
{
    isize i = 0;
    isize size = src.size();
    std::vector<std::string_view> res;

    while (i < size) {
        while (i < size && src[i] == sep) {
            i++;
        }

        isize j = i;
        while (i < size && src[i] != sep) {
            i++;
        }

        if (j < i) {
            res.emplace_back(src.substr(j, i - j));
        }
    }

    return res;
}

inline std::string snakeCase(std::string const& src)
{
    isize const len = src.size();
    if (len == 0) {
        return {};
    }

    std::string res;
    res.reserve(len * 2 > 16 ? len * 2 : 16);

    for (isize i = 0; i < len; i++) {
        char const c = src[i];

        b32 const is_upper = ('A' <= c && c <= 'Z');
        b32 const is_digit = ('0' <= c && c <= '9');
        b32 const prev_is_digit = (i > 0) &&
                                   ('0' <= src[i - 1] && src[i - 1] <= '9');
        b32 const prev_is_lower = (i > 0) &&
                                   ('a' <= src[i - 1] && src[i - 1] <= 'z');
        b32 const prev_is_upper = (i > 0) &&
                                   ('A' <= src[i - 1] && src[i - 1] <= 'Z');
        b32 const next_is_lower = (i + 1 < len) &&
                                   ('a' <= src[i + 1] && src[i + 1] <= 'z');

        if (prev_is_digit) {
            if (is_digit) {
                res.push_back(c);
                continue;
            }
            if (i + 1 < len && src[i] != '_') {
                res.push_back('_');
            }
        }

        if (is_upper) {
            if (i > 0 && (prev_is_lower || (prev_is_upper && next_is_lower))) {
                res.push_back('_');
            }
            res.push_back(c - 'A' + 'a');
        } else {
            res.push_back(c);
        }
    }

    if (res[0] == 'f' && res[1] == '_') {
        res = res.substr(2);
    }

    return res;
}

inline std::string appendSnake(std::string const& prefx, std::string const& className)
{
    std::ostringstream res("");
    res << prefx;
    if (!className.empty()) {
        res << "_" << snakeCase(className);
    }
    return res.str();

}

inline std::string formatCompilerOptions(usize indent, std::string const& begln = "")
{
    constexpr usize MAX_WIDTH = 81;
    std::ostringstream build;
    std::string options = gGlobal->printCompilationOptions1();
    std::vector<std::string_view> opts = split(options, ' ');
    std::vector<std::string> units;
    units.reserve(opts.size());

    for (usize i = 0; i < opts.size(); i++) {
        std::string_view op = opts[i];
        if (op.empty()) {
            continue;
        }

        if (op[0] == '-'
            && i + 1 < opts.size()
            && !opts[i + 1].empty()
            && opts[i + 1][0] != '-'
        ) {
            units.emplace_back(std::string(op) + " " + std::string(opts[i + 1]));
            i++;
        } else {
            units.emplace_back(op);
        }
    }

    std::string prefx = begln + windent(indent);
    usize count = prefx.size();

    build << prefx;
    for (auto ut = units.begin(); ut != units.end(); ut++) {
        std::string const& uni = *ut;
        usize needed = 1 + uni.size();

        if (count + needed > MAX_WIDTH) {
            build << "\n" << prefx;
            count = prefx.size();
        }

        build << uni << " ";
        count += needed;
    }
    std::string res = build.str();
    if (!res.empty() && res.back() == ' ') {
        res.pop_back();
    }
    return res;
}

// inline std::string formatCopts(isize indent, std::string const& begln = "")
// {
//     constexpr isize MAX_WIDTH = 79;
//     std::ostringstream build;
//     std::string options = gGlobal->printCompilationOptions1();
//     std::vector<std::string_view> opts = split(options, ' ');
//     isize count = 0;
//     b32 newl = 0;
//     for (auto it = opts.begin(); it != opts.end(); it++) {
//         newl = 0;
//         std::string_view opt = *it;
//         auto jt = it + 1;
//
//         if (!opt.empty() && opt[0] == '-') {
//             count += opt.size();
//
//             if (jt != opts.end() && (*jt)[0] != '-') {
//                 count += (it + 1)->size();
//             }
//         }
//
//         if (indent + count + sz > 79) {
//             count = 0;
//             newl = 1;
//         }
//
//         if (jt != opts.end()) {
//             build << " ";
//             count++;
//         }
//
//         if (newl) {
//             build << "\n" << begln << windent(indent);
//         }
//
//         build << *it;
//     }
//     return build.str();
// }

}       // namespace mojo
#endif  // _MOJO_UTILS_HH
