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
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdlib.h>

#include "floats.hh"
#include "doc_Text.hh"
#include "compatibility.hh"
#include "exception.hh"

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

const string symbolicNumber (double n);

#if 0
/**
 * Suppress trailing zero in a string representating a floating point number.
 * example : 1.00000  -> 1.0
 * example : 1.00000f -> 1.0f
 */

static void zdel(char* c)
{
    int l = strlen(c) - 1;
    bool f = (c[l] == 'f');

    if (f) c[l--] = 0;      // remove trailing if any f
    while (l>1 && c[l-1] != '.' && c[l] == '0')  c[l--] = 0;
    if (f) c[++l] = 'f';    // restaure trailing f if needed
}
#endif

string docT(char* c){ return string(c); }
string docT(int n) { char c[64]; snprintf(c, 63, "%d", n);  return string(c); }
string docT(long n) { char c[64]; snprintf(c, 63, "%ld", n); return string(c); }
string docT(double n) { return symbolicNumber(n); }

//
//*****************************SYMBOLIC NUMBER REPRESENTATION*******************
//

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
    faustassert(n>0);
    stringstream ss (stringstream::out|stringstream::in);
    int k = (int)floor(log(n)/log(M_PI));
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
    faustassert(n>0);
    stringstream ss (stringstream::out|stringstream::in);
    int k = (int)floor(log(n));
    if ( AlmostEqual(n, exp(float(k))) && (k!=0) && (abs(k)<5.0) ) {
        ss << "e";
        if (k!=1)  ss << "^{"<< k <<"}";
        s = ss.str();
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
    faustassert(n>0);
    if (isPiPower(n,s)) {
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
 * Return symbolic or numerical representation of n>0
 */
const string positiveSymbolicNumber(double n)
{
    string s;
    faustassert(n>0);

    // Try to find a symbolic representation

    for (int i=1; i<10; i++) {
        for(int j=1; j<10; j++) {
            if (isSymbolicPower(i*n/j,s)) {
                return addFraction(j,i,s);
            }
        }
    }

    // No symbolic representation,
    // Then numerical representation x.10^k

    char tmp[64];
    string entree = " * 10^{";
    char sortie = '}';
    string::size_type ps;

    snprintf(tmp, 63, "%.15g", n); // Warning: over 15 decimals, results are wrong !!
    s = tmp;
    ps = s.find('e');

    if (ps != string::npos) {
        s.replace(ps, 1, "");
        s.insert(ps, entree);
        s += sortie;
    }

    return s;
}

/**
 * Return symbolic or numerical representation of n
 */
const string symbolicNumber (double n)
{
    if (n>0.0) {
        return positiveSymbolicNumber(n);
    } else if (n<0.0) {
        return string("-") + positiveSymbolicNumber(-n);
    } else {
        return "0";
    }
}
