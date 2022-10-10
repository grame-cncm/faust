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

using namespace std;

string subst(const string& m, const string& a0);
string subst(const string& m, const vector<string>& vargs);
string subst(const string& m, const string& a0, const string& a1);
string subst(const string& m, const string& a0, const string& a1, const string& a2);
string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3);
string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3,
             const string& a4);
string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3,
             const string& a4, const string& a5);
string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3,
             const string& a4, const string& a5, const string& a6);

string T(char* c);
string T(int n);
string T(long n);
string TAux(float n);
string T(float n);
string TAux(double n);
string T(double n);

// Add and remove quotes of a string
string unquote(const string& s);
string quote(const string& s);

void tab(int n, ostream& fout);
void back(int n, ostream& fout);
void printlines(int n, list<string>& lines, ostream& fout, const string& sep = "");
string rmWhiteSpaces(const string& s);

inline string checkFloat(float val)
{
    return (std::isinf(val)) ? "INFINITY" : T(val);
}
inline string checkDouble(double val)
{
    return (std::isinf(val)) ? "INFINITY" : T(val);
}
string checkReal(double val);

string indent(string const& str, int tabs);
string replaceChar(string str, char ch1, char ch2);
string replaceCharList(const string& str, const vector<char>& ch1, char ch2);

inline bool checkMin(const string& str)
{
    return ((str == "min") || (str == "min_i") || (str == "min_f") || (str == "min_") || (str == "min_l"));
}

inline bool checkMax(const string& str)
{
    return ((str == "max") || (str == "max_i") || (str == "max_f") || (str == "max_") || (str == "max_l"));
}

inline bool checkMinMax(const string& str)
{
    return checkMin(str) || checkMax(str);
}

inline bool startWith(const string& str, const string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix);
}

inline bool endWith(const string& str, const string& suffix)
{
    size_t i = str.rfind(suffix);
    return (i != string::npos) && (i == (str.length() - suffix.length()));
}

inline string startWithRes(const string& str, const string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix) ? str.substr(prefix.size()) : "";
}

inline bool startWithRes(const string& str, const string& prefix, string& res)
{
    if (str.substr(0, prefix.size()) == prefix) {
        res = str.substr(prefix.size());
        return true;
    } else {
        return false;
    }
}

inline string removeChar(const string& str, char c)
{
    string res;
    res.reserve(str.size());  // optional, avoids buffer reallocations in the loop
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] != c) res += str[i];
    }
    return res;
}

inline bool replaceExtension(const string& str, const string& term, string& res)
{
    size_t pos = str.rfind('.');
    if (pos != string::npos) {
        res = str.substr(0, pos) + term;
        return true;
    } else {
        res = str;
        return false;
    }
}

inline string pathToContent(const string& path)
{
    ifstream file(path.c_str(), ifstream::binary);

    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);

    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);

    // Terminate the string
    buffer[size]  = 0;
    string result = buffer;
    file.close();
    delete[] buffer;
    return result;
}

// For soundfile : remove spaces between filenames and possibly
// put a unique file in a {...} list
inline string prepareURL(const string& url)
{
    bool in_str = false;
    stringstream dst;
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
    string res = dst.str();

    // If unique file, create a list with it
    return (res[0] != '{') ? "{'" + res + "'}" : res;
}

inline string flatten(const string& src)
{
    string dst;
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

// To be used for WASM or CMaj
inline string flattenJSON(const string& src)
{
    string dst;
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
inline string flattenJSON1(const string& src)
{
    string dst;
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
    vector<const char*> filter_argv = { "-tg", "-sg", "-ps", "-svg", "-mdoc", "-mdlang", "-stripdoc", "-sd", "-xml", "-json" };
    for (size_t i = 0; i < filter_argv.size(); i++) {
        if (strcmp(filter_argv[i], arg) == 0) return true;
    }
    return false;
}

vector<string> tokenizeString(const string& str, char sep);

#endif
