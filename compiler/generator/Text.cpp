/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>

#include "Text.hh"
#include "compatibility.hh"
#include "floats.hh"
#include "global.hh"

static string substitution (const string& model, const vector<string>& args);

/**
 * Text substitution. Creates a string by replacing all the $n
 * occurences in the model string, with the corresponding arguments.
 * Example :
 * 		subst("float $0 = $1;", "var", T(10.2))
 */
string subst (const string& model, const vector<string>& args)
{
	return substitution(model, args);
}

string subst (const string& model, const string& a0)
{
	vector<string> args(10);
	args[0] = a0;
	return substitution (model, args);
}

string subst (const string& model, const string& a0, const string& a1)
{
	vector<string> args(10);
	args[0] = a0;
	args[1] = a1;

	return substitution (model, args);
}

string subst (const string& model, const string& a0, const string& a1, const string& a2)
{
	vector<string> args(10);

	args[0] = a0;
	args[1] = a1;
	args[2] = a2;

	return substitution (model, args);
}

string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3)
{
	vector<string> args(10);

	args[0] = a0;
	args[1] = a1;
	args[2] = a2;
	args[3] = a3;

	return substitution (model, args);
}

string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4)
{
	vector<string> args(10);

	args[0] = a0;
	args[1] = a1;
	args[2] = a2;
	args[3] = a3;
	args[4] = a4;

	return substitution (model, args);
}

string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4, const string& a5)
{
	vector<string> args(10);

	args[0] = a0;
	args[1] = a1;
	args[2] = a2;
	args[3] = a3;
	args[4] = a4;
	args[5] = a5;

	return substitution (model, args);
}

string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4, const string& a5, const string& a6)
{
	vector<string> args(10);

	args[0] = a0;
	args[1] = a1;
	args[2] = a2;
	args[3] = a3;
	args[4] = a4;
	args[5] = a5;
	args[6] = a6;

	return substitution (model, args);
}

static string substitution (const string& model, const vector<string>& args)
{
    char c;
    int i = 0, ilast = (int)model.length() - 1;
    string 	result;

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

string T(char* c) 	{ return string(c); }
string T(int n) 	{ char c[64]; snprintf(c, 63, "%d", n); 	return string(c); }
string T(long n) 	{ char c[64]; snprintf(c, 63, "%ld", n); return string(c); }

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
 * Convert a simple-precision float into a string.
 * Adjusts the precision p to the needs.
 */
string T(float n)
{
    std::stringstream num;
    num << std::setprecision(std::numeric_limits<float>::max_digits10) << n;
    return ensureFloat(num.str()) + inumix();
}

/**
 * Convert a double-precision float into a string.
 * Adjusts the precision p to the needs.
 */
string T(double n)
{
    std::stringstream num;
    num << std::setprecision(std::numeric_limits<double>::max_digits10) << n;
    return ensureFloat(num.str()) + inumix();
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

/**
 * Print a list of lines
 * @param n number of tabs of indentation
 * @param lines list of lines to be printed
 * @param fout output stream
 */
void printlines(int n, list<string>& lines, ostream& fout, string sep)
{
    list<string>::iterator s;
    for (s = lines.begin(); s != lines.end(); s++) {
        if (s == lines.begin()) {
            tab(n, fout); fout << *s;  // No separator before first one
        } else {
            tab(n, fout); fout << sep << *s;
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

    if ( (i != string::npos) & (j != string::npos) ) {
        return s.substr(i, 1+j-i);
    } else {
        return "";
    }
}

// 'Quad' (= long double) are currectly treated like 'double'

string checkReal(double val)
{
    return (strcmp(ifloat(), "float") == 0) ? checkFloat(val) : checkDouble(val);
}

string indent(const string& str, int tabs)
{
    stringstream instream(str);
    stringstream outstream;
    string line;
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
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == src) {
            str[i] = dst;
        }
    }
    return str;
}

string replaceCharList(string str, const vector<char>& ch1, char ch2)
{
    vector<char>::const_iterator beg = ch1.begin();
    vector<char>::const_iterator end = ch1.end();
    for (size_t i = 0; i < str.length(); ++i) {
        if (std::find(beg, end, str[i]) != end) {
            str[i] = ch2;
        }
    }
    return str;
}
