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

#ifndef __ATERM__
#define __ATERM__

#include <stdio.h>
#include <map>
#include <list>

#include "tlib.hh"
#include "signals.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "normalize.hh"
#include "sigorderrules.hh"
#include "mterm.hh"
#include "garbageable.hh"
#include "exception.hh"

using namespace std;

/**
 * Implements a additive term, a set of mterms added together
 * m1 + m2 + m3 + ...
 */

class aterm : public virtual Garbageable
{

    map<Tree,mterm> fSig2MTerms;     			///< mapping between signatures and corresponding mterms

 public:
 
    aterm ();									///< create an empty aterm (equivalent to 0)
    aterm (Tree t);								///< create a aterm from an additive exp
    //aterm (const aterm& a);						///< create a copy of an aterm

    const aterm& operator += (Tree t);			///< add in place an additive expression tree
    const aterm& operator -= (Tree t);			///< add in place an additive expression tree
	
    const aterm& operator += (const mterm& m);	///< add in place an mterm
    const aterm& operator -= (const mterm& m);	///< add in place an mterm
	Tree normalizedTree() const;				///< return the corresponding normalized expression tree
	
	ostream& print(ostream& dst) const;			///< print a aterm m1 + m2 + m3 +...
	mterm greatestDivisor() const;				///< return the greatest divisor of any two mterms
	aterm factorize(const mterm& d);			///< reorganize the aterm by factorizing d
};

inline ostream& operator << (ostream& s, const aterm& a) { return a.print(s); }

#endif
