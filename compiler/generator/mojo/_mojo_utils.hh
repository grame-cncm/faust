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

inline namespace mojo {

////////////////////////////////////////////////////////////////
// Namespaced type aliases for syntactic sugar

using String = std::string;
using VString = std::string_view;
using OString = std::ostringstream;
using OStream = std::ostream;
template<typename T> using Vector = std::vector<T>;

////////////////////////////////////////////////////////////////
// Writing helpers for `MojoVisitor`s and `MojoCodeContainer`s 

inline constexpr isize TAB_SIZE = 4;

inline String wbanner()                 {   return "# ==============================================================================";   }
inline String wblank (isize n=1)        {   return String(n, '\n');                                                                      }
inline String windent(isize n=TAB_SIZE) {   return String(n, ' ');                                                                       }
inline String wlit   (String s)         {   return "\"" + s + "\"";                                                                      }
inline String wnextl (isize n=1)        {   return '\n' + windent(TAB_SIZE*n);                                                           }
inline String wptr   (String s)         {   return "Ptr["+s+"]";                                                                         }
inline String wtab   (isize n=1)        {   return String(TAB_SIZE*n, ' ');                                                              }

inline String wrewind(std::ostream* out, isize n = 1)
{
    out->seekp(isize(out->tellp()) - n * TAB_SIZE);
    return "";
}

inline String wmultilit(String&& s)
{
    OString out;
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

////////////////////////////////////////////////////////////////
// String manip helpers for `Visitor`s and `CodeContainer`s
 
inline String toStringTrim(f64 x)
{
    String res = std::to_string(x);
    res.erase(res.find_last_not_of('0') + 1, String::npos);
    res.erase(res.find_last_not_of('.') + 1, String::npos);
    return res;
}

inline b32 isWhole(double n) { return n == trunc(n); }

/**
    @req
    - `x` is finite and has null fractional part.
**/
inline String toStringTruncNullFraction(f64 x)
{
    faustassert(isWhole(x));
    auto res = std::to_string(x);
    res.erase(res.find_first_of('.'), String::npos);
    return res;
}

inline String ensureReal(String&& str)
{
    b32 is_int = true;
    OString res;
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

inline String ensureReal(f64 x)
{
    return ensureReal(toStringTrim(x));
}

inline Vector<VString> split(VString src, char sep)
{
    isize i = 0;
    isize size = src.size();
    Vector<VString> res;

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

inline String snakeCase(String const& src)
{
    isize const len = src.size();
    if (len == 0) {
        return {};
    }

    String res;
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

inline String appendSnake(String const& prefx, String const& className)
{
    OString res("");
    res << prefx;
    if (!className.empty()) {
        res << "_" << snakeCase(className);
    }
    return res.str();

}

inline String formatCompilerOptions(isize indent, String const& begln = "")
{
    constexpr isize MAX_WIDTH = 81;
    OString build;
    String options = gGlobal->printCompilationOptions1();
    Vector<VString> opts = split(options, ' ');
    Vector<String> units;
    units.reserve(opts.size());

    for (usize i = 0; i < opts.size(); i++) {
        VString op = opts[i];
        if (op.empty()) {
            continue;
        }

        if (op[0] == '-'
            && i + 1 < opts.size()
            && !opts[i + 1].empty()
            && opts[i + 1][0] != '-'
        ) {
            units.emplace_back(String(op) + " " + String(opts[i + 1]));
            i++;
        } else {
            units.emplace_back(op);
        }
    }

    String prefx = begln + windent(indent);
    isize count = prefx.size();

    build << prefx;
    for (auto ut = units.begin(); ut != units.end(); ut++) {
        String const& uni = *ut;
        isize needed = 1 + uni.size();

        if (count + needed > MAX_WIDTH) {
            build << "\n" << prefx;
            count = prefx.size();
        }

        build << uni << " ";
        count += needed;
    }
    String res = build.str();
    if (!res.empty() && res.back() == ' ') {
        res.pop_back();
    }
    return res;
}

}       // namespace mojo
#endif  // _MOJO_UTILS_HH
