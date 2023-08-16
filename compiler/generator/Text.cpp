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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "Text.hh"
#include "compatibility.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

static string substitution(const string& model, const vector<string>& args)
{
    char   c;
    int    i = 0, ilast = (int)model.length() - 1;
    string result;
    while (i < ilast) {
        c = model[i++];
        if (c != '$') {
            result += c;
        } else {
            c = model[i++];
            if (c >= '0' && c <= '9') {
                result += args[c - '0'];
            } else {
                result += c;
            }
        }
    }
    if (i == ilast) result += model[i];
    return result;
}

/**
 * Text substitution. Creates a string by replacing all the $n
 * occurences in the model string, with the corresponding arguments.
 * Example : subst("float $0 = $1;", "var", T(10.2))
 */
string subst(const string& model, const vector<string>& args)
{
    return substitution(model, args);
}

string subst(const string& model, const string& a0)
{
    vector<string> args(10);
    args[0] = a0;
    return substitution(model, args);
}

string subst(const string& model, const string& a0, const string& a1)
{
    vector<string> args(10);
    args[0] = a0;
    args[1] = a1;
    return substitution(model, args);
}

string subst(const string& model, const string& a0, const string& a1, const string& a2)
{
    vector<string> args(10);
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    return substitution(model, args);
}

string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3)
{
    vector<string> args(10);
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    return substitution(model, args);
}

string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3,
             const string& a4)
{
    vector<string> args(10);
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    return substitution(model, args);
}

string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3,
             const string& a4, const string& a5)
{
    vector<string> args(10);
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    args[5] = a5;
    return substitution(model, args);
}

string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3,
             const string& a4, const string& a5, const string& a6)
{
    vector<string> args(10);
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    args[5] = a5;
    args[6] = a6;
    return substitution(model, args);
}

string T(char* c)
{
    return string(c);
}

string T(int n)
{
    return std::to_string(n);
}

string T(int64_t n)
{
    return std::to_string(n);
}

/**
 * If needed add a trailing '.0' to the
 * the textual representation of a floating point number
 * to avoid confusions with an int.
 */
static string ensureFloat(const string& c)
{
    bool isInt = true;
    for (size_t i = 0; i < c.size(); i++) {
        if ((c[i] == '.') || (c[i] == 'e')) {
            isInt = false;
            break;
        }
    }
    return (isInt) ? (c + ".0") : c;
}

/**
 * Special encoding for Julia float numbers, see:
 * https://docs.julialang.org/en/v1/manual/integers-and-floating-point-numbers/#Floating-Point-Numbers
 */
static string encodeJuliaFloat(const string& c, bool& need_suffix)
{
    bool   isInt = true;
    string res;
    for (size_t i = 0; i < c.size(); i++) {
        if ((c[i] == '.') || (c[i] == 'e')) {
            isInt = false;
        }
        if (c[i] == 'e') {
            res += 'f';
            need_suffix = false;
        } else {
            res += c[i];
        }
    }
    return (isInt) ? (res + ".0") : res;
}

static string addSuffix(const string& num)
{
    if (gGlobal->gOutputLang == "julia") {
        bool   need_suffix = true;
        string res         = encodeJuliaFloat(num, need_suffix);
        return (need_suffix) ? (res + inumix()) : res;
    } else {
        return ensureFloat(num) + inumix();
    }
}

/**
 * Convert a single precision real into a string.
 * Adjusts the precision p to the needs.
 */
string TAux(float n)
{
    char c[512];
    int  p = 1;

    do {
        snprintf(c, 512, "%.*g", p++, n);
    } while (strtof(c, 0) != n);

    ensureFloat(c);
    return string(c);
}

string T(float n)
{
    return addSuffix(TAux(n));
}

/**
 * Convert a double precision real into a string.
 * Adjusts the precision p to the needs.
 */
string TAux(double n)
{
    char  c[512];
    char* endp;
    int   p = 1;

    if (gGlobal->gFloatSize == 1) {
        float v = (float)n;
        do {
            snprintf(c, 512, "%.*g", p++, v);
            endp = nullptr;
        } while (strtof(c, &endp) != v);
    } else if (gGlobal->gFloatSize == 2) {
        do {
            snprintf(c, 512, "%.*g", p++, n);
            endp = nullptr;
        } while (strtod(c, &endp) != n);
    } else if (gGlobal->gFloatSize == 3) {
        long double q = (long double)n;
        do {
            snprintf(c, 512, "%.*Lg", p++, q);
            endp = nullptr;
        } while (strtold(c, &endp) != q);
    } else if (gGlobal->gFloatSize == 4) {
        do {
            snprintf(c, 512, "%.*g", p++, n);
            endp = nullptr;
        } while (strtod(c, &endp) != n);
    } else {
        cerr << "ASSERT : incorrect float format : " << gGlobal->gFloatSize << endl;
        faustassert(false);
    }

    ensureFloat(c);
    return string(c);
}

string T(double n)
{
    return addSuffix(TAux(n));
}

/**
 * Convert a quad (long double) precision real into a string.
 * Adjusts the precision p to the needs.
 */
string TAux(long double n)
{
    char  c[512];
    char* endp;
    int   p = 1;
    
    if (gGlobal->gFloatSize == 1) {
        float v = (float)n;
        do {
            snprintf(c, 512, "%.*g", p++, v);
            endp = nullptr;
        } while (strtof(c, &endp) != v);
    } else if (gGlobal->gFloatSize == 2) {
        do {
            snprintf(c, 512, "%.*Lg", p++, n);
            endp = nullptr;
        } while (strtod(c, &endp) != n);
    } else if (gGlobal->gFloatSize == 3) {
        long double q = (long double)n;
        do {
            snprintf(c, 512, "%.*Lg", p++, q);
            endp = nullptr;
        } while (strtold(c, &endp) != q);
    } else if (gGlobal->gFloatSize == 4) {
        do {
            snprintf(c, 512, "%.*Lg", p++, n);
            endp = nullptr;
        } while (strtod(c, &endp) != n);
    } else {
        cerr << "ASSERT : incorrect float format : " << gGlobal->gFloatSize << endl;
        faustassert(false);
    }
    
    ensureFloat(c);
    return string(c);
}

string T(long double n)
{
    return addSuffix(TAux(n));
}


/**
 * remove quotes from a string
 */
string unquote(const string& str)
{
    return (str[0] == '"') ? str.substr(1, str.size() - 2) : str;
}

/**
 * add quotes to a string
 */
string quote(const string& s)
{
    return "\"" + s + "\"";
}

/**
 * Print n tabs (for indentation purpose)
 * @param n number of tabs to print
 * @param fout output stream
 */
void tab(int n, ostream& fout)
{
    fout << '\n';
    while (n--) fout << '\t';
}

void back(int n, ostream& fout)
{
    long pos = fout.tellp();
    fout.seekp(pos - n);
}

/**
 * Print a list of lines
 * @param n number of tabs of indentation
 * @param lines list of lines to be printed
 * @param fout output stream
 */
void printlines(int n, list<string>& lines, ostream& fout, const string& sep)
{
    list<string>::const_iterator s;
    for (s = lines.begin(); s != lines.end(); s++) {
        if (s == lines.begin()) {
            tab(n, fout);
            fout << *s;  // No separator before first one
        } else {
            tab(n, fout);
            fout << sep << *s;
        }
    }
}

/**
 * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
 * (but not those in the middle of the string)
 */

string rmWhiteSpaces(const string& s)
{
    size_t i = s.find_first_not_of(" \t");
    size_t j = s.find_last_not_of(" \t");
    if ((i != string::npos) & (j != string::npos)) {
        return s.substr(i, 1 + j - i);
    } else {
        return "";
    }
}

// 'Quad' (= long double) are currectly treated like 'double'

string checkReal(double val)
{
    return (strcmp(ifloat(), "float") == 0) ? checkFloat(float(val)) : checkDouble(val);
}

string indent(const string& str, int tabs)
{
    stringstream instream(str);
    stringstream outstream;
    string       line;
    while (getline(instream, line, '\n')) {
        for (int i = 0; i != tabs; ++i) {
            outstream << '\t';
        }
        outstream << line << endl;
    }
    return outstream.str();
}

string replaceChar(string str, char src, char dst)
{
    replace(str.begin(), str.end(), src, dst);
    return str;
}

string replaceCharList(const string& str, const vector<char>& ch1, char ch2)
{
    auto   beg = ch1.begin();
    auto   end = ch1.end();
    string res = str;
    for (size_t i = 0; i < str.length(); ++i) {
        if (std::find(beg, end, str[i]) != end) res[i] = ch2;
    }
    return res;
}

vector<string> tokenizeString(const string& str, char sep)
{
    vector<string> res;
    istringstream  is(str);
    string         token;
    while (getline(is, token, sep)) res.push_back(token);
    return res;
}

int pow2limit(int x, int def)
{
    if (x > INT_MAX / 2) {
        throw faustexception("ERROR : too big delay value '" + std::to_string(x) +
                             "' which cannot be implemented with a power-of-two delay line\n");
    }

    int n = def;
    while (n < x) {
        n = 2 * n;
    }
    return n;
}
