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

#ifndef __MTERM__
#define __MTERM__

#include <stdio.h>
#include <list>
#include <map>

#include "exception.hh"
#include "garbageable.hh"
#include "normalize.hh"
#include "signals.hh"
#include "sigorderrules.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "tlib.hh"

using namespace std;

/**
 * Implements a multiplicative term, a term of type
 * k*x^n*y^m*... and its arithmetic.
 */

struct CompareTree {
    bool operator()(Tree t1, Tree t2) const { return t1->serial() < t2->serial(); }
};

class mterm : public virtual Garbageable {
    Tree                        fCoef;     ///< constant part of the term (usually 1 or -1)
    map<Tree, int, CompareTree> fFactors;  ///< non constant terms and their power

   public:
    mterm();                ///< create a 0 mterm
    mterm(int k);           ///< create a simple integer mterm
    mterm(double k);        ///< create a simple float mterm
    mterm(Tree t);          ///< create a mterm from a multiplicative exp
    mterm(const mterm& m);  ///< create a copy of a mterm

    void cleanup();           ///< remove used factors
    bool isNotZero() const;   ///< true if mterm doesn't represent number 0
    bool isNegative() const;  ///< true if mterm has a negative coefficient

    const mterm& operator=(const mterm& m);  ///< replace the content with a copy of m

    const mterm& operator*=(Tree m);  ///< multiply in place by a multiplicative exp
    const mterm& operator/=(Tree m);  ///< divide in place by a multiplicative exp

    const mterm& operator+=(const mterm& m);  ///< add in place an mterm of same signature
    const mterm& operator-=(const mterm& m);  ///< add in place an mterm of same signature

    const mterm& operator*=(const mterm& m);  ///< multiply in place by a mterm
    const mterm& operator/=(const mterm& m);  ///< divide in place by a mterm

    mterm    operator*(const mterm& m) const;  ///< mterms multiplication
    mterm    operator/(const mterm& m) const;  ///< mterms division
    ostream& print(ostream& dst) const;        ///< print a mterm k*x1**n1*x2**n2...

    int  complexity() const;  ///< return an evaluation of the complexity
    Tree normalizedTree(bool sign = false,
                        bool neg  = false) const;  ///< return the normalized tree of the mterm
    Tree signatureTree() const;                    ///< return a signature (a normalized tree)

    bool         hasDivisor(const mterm& n) const;       ///< return true if this can be divided by n
    friend mterm gcd(const mterm& m1, const mterm& m2);  /// greatest common divisor of two mterms
};

inline ostream& operator<<(ostream& s, const mterm& m)
{
    return m.print(s);
}

#endif
