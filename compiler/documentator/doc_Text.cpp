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
#include <cmath>

#include "floats.hh"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

#ifndef M_PI_4
#define M_PI_4 0.785398163397448309616
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

extern bool gInternDoubleSwitch;
const string scientific2tenpow (double n);



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
 * Compute the smallest float representable
 * difference epsilon such that 1 != 1+epsilon
 */
float fltEpsilon()
{
   float machEps = 1.0f;
   do {
      machEps /= 2.0f;
   } while ((float)(1.0 + (machEps/2.0)) != 1.0);
   return machEps;
}

/**
 * Compute the smallest double representable
 * difference epsilon such that 1 != 1+epsilon
 */
double dblEpsilon()
{
   double machEps = 1.0f;
   do {
      machEps /= 2.0f;
   } while ((1.0 + (machEps/2.0)) != 1.0);
   return machEps;
}

/**
 * Check if two floating point numbers are (almost) equal
 * Abs(x-y) < epsilon
 */
static bool AlmostEqual(double A, double B)
{
    double maxRelativeError = 2*dblEpsilon();
    double maxAbsoluteError = maxRelativeError;


    if (fabs(A - B) < maxAbsoluteError)
        return true;
    double relativeError;
    if (fabs(B) > fabs(A))
        relativeError = fabs((A - B) / B);
    else
        relativeError = fabs((A - B) / A);
    if (relativeError <= maxRelativeError)
        return true;
    return false;
}

/**
 * Return true if n>0 is equal to PI^k for some small integer k.
 * k = log(n)/log(pi) is integer => n = exp(int(k)*log(pi))
 * The latex representation \pi^{k} is returned in string s
 */
bool isPiPower (double n, string& s)
{
    assert(n>0);
    stringstream ss (stringstream::out|stringstream::in);
    int k = floor(log(n)/log(M_PI));
    if ( AlmostEqual(n, exp(k * log(M_PI))) && (k!=0) && (abs(k)<5.0) ) {
        ss << "\\pi";
        if (k!=1)  ss << "^{"<< k <<"}";
        s = ss.str();
        return true;
    } else {
        return false;
    }
}

/**
 * Return true if n>0 is equal to e^k for some small integer k.
 * The latex representation e^{k} is returned in string s
 */
bool isExpPower (double n, string& s)
{
    assert(n>0);
    stringstream ss (stringstream::out|stringstream::in);
    int k = floor(log(n));
    if ( AlmostEqual(n, exp(k)) && (k!=0) && (abs(k)<5.0) ) {
        ss << "e";
        if (k!=1)  ss << "^{"<< k <<"}";
        s = ss.str();
        return true;
    } else {
        return false;
    }
}

/**
 * Return true if n>0 is equal to 10^k for some integer k.
 * The symbolic latex representation is returned in string s
 */
const char* tenpow[] = {"0.001", "0.01", "0.1", "1", "10", "100", "1000" };

bool isTenPower (double n, string& s)
{
    assert(n>0);
    int k = floor(log10(n));
    if ( AlmostEqual(n, pow(10.0,k)) ) {
        if (abs(k)<4) {
            s = tenpow[3+k];
        } else {
            char tmp[64];
            snprintf(tmp, 63, "10^{%d}", k);
            s = tmp;
        }
        return true;
    } else {
        return false;
    }
}

/**
 * Return true if n>0 is equal to e^k or PI^k for some integer k
 * The symbolic latex representation is returned in string s
 */
bool isSymbolicPower (double n, string& s)
{
    assert(n>0);
    /*if (isTenPower(n,s)) {
        return true;
    } else*/ if (isPiPower(n,s)) {
        return true;
    } else if (isExpPower(n,s)) {
        return true;
    } else {
        return false;
    }
}


/**
 * Return exp or num.exp, or exp/denom, or num/denom.exp
 */
const string addFraction (int num, int denom, const string& exp)
{
    stringstream ss (stringstream::out|stringstream::in);

    if ((num==1) & (denom==1)) {
        ss << exp;
    } else if ((num==1) & (denom!=1)) {
        ss << "\\frac{"<< exp <<  "}{" << denom << "}";
    } else if ((num!=1) & (denom==1)) {
        ss << num << "*" << exp;
    } else {
        ss << "\\frac{"<< num <<  "}{" << denom << "}*" << exp;
    }
    return ss.str();
}


/**
 * Return symbolic or numerical representation of n
 */
const string positive_scientific2tenpow (double n)
{
    string s;
    assert(n>0);

    // Try to find a symbolic representation

    for (int i=1;i<10;i++) {
        for(int j=1;j<10;j++) {
            if (isSymbolicPower(i*n/j,s)) {
                return addFraction(j,i,s);
            }
        }
    }

    // No symbolic representation,
    // Then numerical representation

    char tmp[64];
    string entree = " * 10^{";
    char sortie = '}';
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

string old_positive_scientific2tenpow (double n)
{
    if (! AlmostEqual(n,0.0)) {
        // First try symbolic representation of n
        if (AlmostEqual(n, int(n))) return docT(int(n));
        if (AlmostEqual(n, M_PI)) return "\\pi ";
        if (AlmostEqual(n, M_PI_2)) return "\\frac{\\pi}{2}";
        if (AlmostEqual(n, M_PI_4)) return "\\frac{\\pi}{4}";
        if (AlmostEqual(n, M_PI/3.0)) return "\\frac{\\pi}{3}";
        if (AlmostEqual(n, 3*M_PI_4)) return "\\frac{3}{4}\\pi";
        if (AlmostEqual(n, M_E)) return "e";
        if ((n>0) && AlmostEqual(n, exp(floor(log(n))) )) {
            char tmp[64];
            snprintf(tmp, 63, "e^{%d}", int(log(n)));
            return string(tmp);
        }
        if ((n>0) && AlmostEqual(n, exp(floor(log(n)/log(M_PI)) * log(M_PI)) )) {
            char tmp[64];
            snprintf(tmp, 63, "\\pi^{%d}", int(log(n)/log(M_PI)));
            return string(tmp);
        }
        // <---- add more symbolic constants here
    }

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

const string scientific2tenpow (double n)
{
    if (n>0.0) {
        return positive_scientific2tenpow(n);
    } else if (n<0.0) {
        return string("-") + positive_scientific2tenpow(-n);
    } else {
        return "0";
    }
}
