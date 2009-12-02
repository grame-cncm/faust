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
#include <string.h>
#include "doc_Text.hh"
#include "compatibility.hh"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <assert.h>

#include "floats.hh"

extern bool gInternDoubleSwitch;
string scientific2tenpow (double n);

//static string substitution (const string& model, const vector<string>& args)
//{
//	char 	c;
//	int 	i=0, ilast = model.length()-1;
//	string 	result;
//
//	while (i < ilast) {
//		c = model[i++];
//		if (c != '$') {
//			result += c;
//		} else {
//			c = model[i++];
//			if (c >= '0' && c <= '9') {
//				result += args[c - '0'];
//			} else {
//				result += c;
//			}
//		}
//	}
//	if (i == ilast) result += model[i];
//	return result;
//}
//string subst (const string& model, const vector<string>& args)
//{
//	return substitution(model, args);
//}
//
//string subst (const string& model, const string& a0)
//{
//	vector<string> args(10);
//	args[0] = a0;
//	return substitution (model, args);
//}
//
//string subst (const string& model, const string& a0, const string& a1)
//{
//	vector<string> args(10);
//	args[0] = a0;
//	args[1] = a1;
//
//	return substitution (model, args);
//}
//
//string subst (const string& model, const string& a0, const string& a1, const string& a2)
//{
//	vector<string> args(10);
//
//	args[0] = a0;
//	args[1] = a1;
//	args[2] = a2;
//
//	return substitution (model, args);
//}
//
//string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3)
//{
//	vector<string> args(10);
//
//	args[0] = a0;
//	args[1] = a1;
//	args[2] = a2;
//	args[3] = a3;
//
//	return substitution (model, args);
//}
//
//string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4)
//{
//	vector<string> args(10);
//
//	args[0] = a0;
//	args[1] = a1;
//	args[2] = a2;
//	args[3] = a3;
//	args[4] = a4;
//
//	return substitution (model, args);
//}
//
//string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4, const string& a5)
//{
//	vector<string> args(10);
//
//	args[0] = a0;
//	args[1] = a1;
//	args[2] = a2;
//	args[3] = a3;
//	args[4] = a4;
//	args[5] = a5;
//
//	return substitution (model, args);
//}
//
//string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4, const string& a5, const string& a6)
//{
//	vector<string> args(10);
//
//	args[0] = a0;
//	args[1] = a1;
//	args[2] = a2;
//	args[3] = a3;
//	args[4] = a4;
//	args[5] = a5;
//	args[6] = a6;
//
//	return substitution (model, args);
//}

#if 0
/**
 * Suppress trailing zero in a string representating a floating point number.
 * example : 1.00000  -> 1.0
 * example : 1.00000f -> 1.0f
 */

static void zdel(char* c)
{
    int     l = strlen(c) - 1;
    bool    f = (c[l] == 'f');

    if (f) c[l--] = 0;      // remove trailing if any f
    while ( l>1 && c[l-1] != '.' && c[l] == '0')  c[l--] = 0;
    if (f) c[++l] = 'f';    // restaure trailing f if needed
}
#endif

string docT (char* c) 	{ return string(c); }
string docT (int n) 	{ char c[64]; snprintf(c, 63, "%d",n); 	return string(c); }
string docT (long n) 	{ char c[64]; snprintf(c, 63, "%ld",n); return string(c); }

#if 0
string docT (float n)
{
    char c[64];
    if  (n <  0.1 && n > -0.1 && n != 0.0) {
        //snprintf(c, 63, "%e", n);//f", n);
		string s = scientific2tenpow(n);
		snprintf(c, 63, "%s", s.c_str());
    } else {
        snprintf(c, 63, "%f", n);//f", n);
        zdel(c);
    }
    return string(c);
}
#endif

/**
 * Add a trailing f when converting double-precision numbers to text
 * if single-precision is required
 * NO, this is no more true for LaTeX documentator
 */
string docT (double n)
{
//    char c[64];
//    if  (n <  0.1 && n > -0.1 && n != 0.0) {
//        //snprintf(c, 63, "%e", n); //, inumix());
////		string s = scientific2tenpow(n);
////		snprintf(c, 63, "%s", s.c_str());
//        snprintf(c, 63, "%g", n);
//    } else {
//        snprintf(c, 63, "%g", n);
//        //zdel(c);
//    }
//    return string(c);
	return scientific2tenpow(n);
}

string scientific2tenpow (double n)
{
    char tmp[64];
	string entree = " * 10^{";
	char sortie = '}';
	string s;
	string::size_type ps;
	
	snprintf(tmp, 63, "%g", n);
	
	//cout << "doc_Text.cpp : scientific2tenpow : " << n << " -> \"" << tmp << "\"" << endl;
	s = tmp;
	ps = s.find('e');
	
	if (ps != string::npos) {
		s.replace(ps, 1, "");
		s.insert(ps, entree);
		s += sortie;
	}
	else {
		//cout << "doc_Text.cpp : scientific2tenpow : \'e\' non trouvé" << endl;
	}
		
	return s;
}

/*
string docT (double n)
{
    char c[64];
    if  (n <  0.1 && n > -0.1 && n != 0.0) {
        if (gInternDoubleSwitch) {
            snprintf(c, 63, "%e", n);
        } else {
            snprintf(c, 63, "%ef", n);
        }
    } else {
        if (gInternDoubleSwitch) {
            snprintf(c, 63, "%f", n);
        } else {
            snprintf(c, 63, "%ff", n);
        }
        zdel(c);
    }
    return string(c);
}*/

/**
 * remove quotes from a string
 */
//string unquote(const string& s)
//{
//	assert(s.size() >= 2);
//	assert(s[0] == '"');
//	assert(s[s.size()-1] == '"');
//	return s.substr(1, s.size()-2);
//}
//
//
///**
// * add quotes to a string
// */
//string quote(const string& s)
//{
//	string q("\"");
//	q += s;
//	q += "\"";
//	return q;
//}
//
