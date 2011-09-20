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
#include <math.h>

#include "floats.hh"

extern bool gInternDoubleSwitch;
string scientific2tenpow (double n);



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


/**
 * Check if two floating point numbers are (almost) equal
 */
static bool AlmostEqual(double A, double B)
{
    double maxRelativeError = 0.00001;
    double maxAbsoluteError = 0.00001;


    if (fabs(A - B) < maxAbsoluteError)
        return true;
    float relativeError;
    if (fabs(B) > fabs(A))
        relativeError = fabs((A - B) / B);
    else
        relativeError = fabs((A - B) / A);
    if (relativeError <= maxRelativeError)
        return true;
    return false;
}

string scientific2tenpow (double n)
{
    // First try symbolic representation of n
    if (AlmostEqual(n, M_PI)) return "\\pi ";
    if (AlmostEqual(n, M_PI_2)) return "\\frac{\\pi}{2}";
    if (AlmostEqual(n, M_PI_4)) return "\\frac{\\pi}{4}";
    if (AlmostEqual(n, M_E)) return "e";
    if ((n>0) && AlmostEqual(n, exp(int(log(n))) )) {
        char tmp[64];
        snprintf(tmp, 63, "e^{%d}", int(log(n)));
        return string(tmp);
    }
    // <---- add more symbolic constants here


    // Then numerical representation
    char tmp[64];
	string entree = " * 10^{";
	char sortie = '}';
	string s;
	string::size_type ps;
	
	snprintf(tmp, 63, "%.15g", n); // Warning: over 15 decimals, results are wrong !!
//	snprintf(tmp, 63, "%f", n);
	
//	cerr << "doc_Text.cpp : scientific2tenpow : " << n << " -> \"" << tmp << "\"" << endl;
	s = tmp;
	ps = s.find('e');
	
	if (ps != string::npos) {
		s.replace(ps, 1, "");
		s.insert(ps, entree);
		s += sortie;
	}
	else {
		//cerr << "doc_Text.cpp : scientific2tenpow : \'e\' non trouvé" << endl;
	}
		
	return s;
}
