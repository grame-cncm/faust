/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef _Text_H
#define _Text_H

#include <string.h>

#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

std::string subst(const std::string& m, const std::string& a0);
std::string subst(const std::string& m, const std::vector<std::string>& vargs);
std::string subst(const std::string& m, const std::string& a0, const std::string& a1);
std::string subst(const std::string& m, const std::string& a0, const std::string& a1, const std::string& a2);
std::string subst(const std::string& model, const std::string& a0, const std::string& a1, const std::string& a2, const std::string& a3);
std::string subst(const std::string& model, const std::string& a0, const std::string& a1, const std::string& a2, const std::string& a3,
             const std::string& a4);
std::string subst(const std::string& model, const std::string& a0, const std::string& a1, const std::string& a2, const std::string& a3,
             const std::string& a4, const std::string& a5);
std::string subst(const std::string& model, const std::string& a0, const std::string& a1, const std::string& a2, const std::string& a3,
             const std::string& a4, const std::string& a5, const std::string& a6);

std::string T(char* c);
std::string T(int n);
std::string T(long n);
std::string TAux(float n);
std::string T(float n);
std::string TAux(double n);
std::string T(double n);
std::string T(int64_t n);

// Add and remove quotes of a std::string
std::string unquote(const std::string& s);
std::string quote(const std::string& s);

void tab(int n, std::ostream& fout);
void back(int n, std::ostream& fout);
void printlines(int n, std::list<std::string>& lines, std::ostream& fout, const std::string& sep = "");
std::string rmWhiteSpaces(const std::string& s);

inline std::string checkFloat(float val)
{
    return (std::isinf(val)) ? "INFINITY" : T(val);
}
inline std::string checkDouble(double val)
{
    return (std::isinf(val)) ? "INFINITY" : T(val);
}
std::string checkReal(double val);

std::string indent(const std::string& str, int tabs);
std::string replaceChar(std::string str, char ch1, char ch2);
std::string replaceCharList(const std::string& str, const std::vector<char>& ch1, char ch2);

inline bool checkMin(const std::string& str)
{
    return ((str == "min") || (str == "min_i") || (str == "min_f") || (str == "min_") || (str == "min_l") || (str == "min_fx"));
}

inline bool checkMax(const std::string& str)
{
    return ((str == "max") || (str == "max_i") || (str == "max_f") || (str == "max_") || (str == "max_l") || (str == "max_fx"));
}

inline bool checkMinMax(const std::string& str)
{
    return checkMin(str) || checkMax(str);
}

inline bool startWith(const std::string& str, const std::string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix);
}

inline bool endWith(const std::string& str, const std::string& suffix)
{
    size_t i = str.rfind(suffix);
    return (i != std::string::npos) && (i == (str.length() - suffix.length()));
}

inline std::string startWithRes(const std::string& str, const std::string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix) ? str.substr(prefix.size()) : "";
}

inline bool startWithRes(const std::string& str, const std::string& prefix, std::string& res)
{
    if (str.substr(0, prefix.size()) == prefix) {
        res = str.substr(prefix.size());
        return true;
    } else {
        return false;
    }
}

inline std::string removeChar(const std::string& str, char c)
{
    std::string res;
    res.reserve(str.size());  // optional, avoids buffer reallocations in the loop
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] != c) res += str[i];
    }
    return res;
}

inline bool replaceExtension(const std::string& str, const std::string& term, std::string& res)
{
    size_t pos = str.rfind('.');
    if (pos != std::string::npos) {
        res = str.substr(0, pos) + term;
        return true;
    } else {
        res = str;
        return false;
    }
}

inline std::string pathToContent(const std::string& path)
{
    std::ifstream file(path.c_str(), std::ifstream::binary);

    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);

    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);

    // Terminate the string
    buffer[size]  = 0;
    std::string result = buffer;
    file.close();
    delete[] buffer;
    return result;
}

// For soundfile : remove spaces between filenames and possibly
// put a unique file in a {...} list
inline std::string prepareURL(const std::string& url)
{
    bool in_str = false;
    std::stringstream dst;
    for (size_t i = 0; i < url.size(); i++) {
        switch (url[i]) {
            case '\n':
            case '\t':
            case '\r':
                break;
            case '\'':
                in_str = !in_str;
                dst << url[i];
                break;
            case ' ':
                // Do not remove spaces in path ('....')
                if (in_str) dst << url[i];
                break;
            default:
                dst << url[i];
                break;
        }
    }
    std::string res = dst.str();

    // If unique file, create a list with it
    return (res[0] != '{') ? "{'" + res + "'}" : res;
}

inline std::string flatten(const std::string& src)
{
    std::string dst;
    for (size_t i = 0; i < src.size(); i++) {
        switch (src[i]) {
            case '\n':
            case '\t':
            case '\r':
                break;
            case ' ':
                if (!(i + 1 < src.size() && src[i + 1] == ' ')) {
                    dst += src[i];
                }
                break;
            default:
                dst += src[i];
                break;
        }
    }
    return dst;
}

// To be used for WASM or CMajor
inline std::string flattenJSON(const std::string& src)
{
    std::string dst;
    for (size_t i = 0; i < src.size(); i++) {
        switch (src[i]) {
            case '"':
                dst += "\\\"";
                break;
            case '\\':
                dst += "\\";
                break;
            case '\'':
                dst += "\\'";
                break;
            default:
                dst += src[i];
                break;
        }
    }
    return dst;
}

// To be used for JavaScript
inline std::string flattenJSON1(const std::string& src)
{
    std::string dst;
    for (size_t i = 0; i < src.size(); i++) {
        switch (src[i]) {
            case '\\':
                dst += "\\";
                break;
            case '\'':
                dst += "\\'";
                break;
            default:
                dst += src[i];
                break;
        }
    }
    return dst;
}

// To filter compilation arguments in 'createDSPFactoryFromString' and 'createInterpreterDSPFactoryFromString'
inline bool testArg(const char* arg)
{
    std::vector<const char*> filter_argv = { "-tg", "-sg", "-ps", "-svg", "-mdoc", "-mdlang", "-stripdoc", "-sd", "-xml", "-json" };
    for (size_t i = 0; i < filter_argv.size(); i++) {
        if (strcmp(filter_argv[i], arg) == 0) return true;
    }
    return false;
}

std::vector<std::string> tokenizeString(const std::string& str, char sep);

/**
 * Compute the minimal power of 2 greater than x
 */
int pow2limit(int x, int def = 2);

inline bool ispowerof2(int x)
{
    /* First x in the below expression is for the case when x is 0 */
    return x && (!(x&(x-1)));
}

// To check all control fields in the DSP structure
inline bool isControl(const std::string& name)
{
    return startWith(name, "fButton") || startWith(name, "fCheckbox")
        || startWith(name, "fVslider") || startWith(name, "fHslider") || startWith(name, "fEntry")
        || startWith(name, "fVbargraph") || startWith(name, "fHbargraph")
        || name == "iControl" || name == "fControl"
        || name == "iZone" || name == "fZone"
        || name == "fSampleRate";
}

inline bool isConst(const std::string& name)
{
    return startWith(name, "fConst") || startWith(name, "iConst");
}

inline bool isTable(const std::string& name)
{
    return startWith(name, "itbl") || startWith(name, "ftbl");
}

#endif
