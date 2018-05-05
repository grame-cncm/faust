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

#ifndef _Text_H
#define _Text_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string subst(const string& m, const string& a0);
string subst(const string& m, const vector<string>& vargs);
string subst(const string& m, const string& a0, const string& a1);
string subst(const string& m, const string& a0, const string& a1, const string& a2);
string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3);
string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4);
string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4, const string& a5);
string subst(const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4, const string& a5, const string& a6);

string T(char* c);
string T(int n);
string T(long n);
string T(float n);
string T(double n);

// add and remove quotes of a string
string unquote(const string& s);
string quote(const string& s);

void tab(int n, ostream& fout);
void printlines(int n, list<string>& lines, ostream& fout, string sep = "");
string rmWhiteSpaces(const string& s);

inline string checkFloat(float val) { return T(val); }
inline string checkDouble(double val)  { return T(val); }
string checkReal(double val);

string indent(string const& str, int tabs);
string replaceChar(string str, char ch1, char ch2);
string replaceCharList(string str, const vector<char>& ch1, char ch2);

inline bool checkMin(const string& str)
{
    return ((str == "min") || (str == "min_i") || (str == "min_f") || (str == "min_"));
}

inline bool checkMax(const string& str)
{
    return ((str == "max") || (str == "max_i") || (str == "max_f") || (str == "max_"));
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
    if (str.substr(0, prefix.size()) == prefix)  {
        res = str.substr(prefix.size());
        return true;
    } else {
        return false;
    }   
}

inline string removeChar(const string& str, char c)
{
    string res;
    res.reserve(str.size()); // optional, avoids buffer reallocations in the loop
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

inline string flatten(const string& src)
{
    stringstream dst;
    size_t size = src.size();
    for (size_t i = 0; i < src.size(); i++) {
        switch (src[i]) {
            case '\n':
            case '\t':
            case '\r':
                break;
            case ' ':
                if (!(i + 1 < size && src[i + 1] == ' ')) {
                    dst << src[i];
                }
                break;
            default:
                dst << src[i];
                break;
        }
    }
    return dst.str();
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
    buffer[size] = 0;
    string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}

#endif
