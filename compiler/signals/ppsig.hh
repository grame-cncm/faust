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

#ifndef _PPSIG_H
#define _PPSIG_H

/**********************************************************************
			- ppsig.h : pretty print signals expressions (projet FAUST) -


		Historique :
		-----------
		05-07-2006  first implementation  (yo)

***********************************************************************/

#include <iostream>
#include <sstream>
#include "signals.hh"
#include "garbageable.hh"

using namespace std;

//void 		fppbox (FILE* fout, Tree box, int priority=0);

// box pretty printer.
// usage : out << boxpp(aBoxExp);

class ppsig  : public virtual Garbageable
{
	Tree 	sig;
	Tree 	fEnv;		///< recursive environment stack
	int		fPriority;	///< priority context
	bool	fHideRecursion; 	///<
public:
	ppsig(Tree s);
	ostream& print (ostream& fout) const;

private:
	ppsig(Tree s, Tree env, int priority=0) : sig(s), fEnv(env), fPriority(priority), fHideRecursion(false) {}
	ostream& printinfix (ostream& fout, const string& opname, int priority, Tree x, Tree y) const;
	ostream& printfun (ostream& fout, const string& funame, Tree x) const;
	ostream& printfun (ostream& fout, const string& funame, Tree x, Tree y) const;
	ostream& printfun (ostream& fout, const string& funame, Tree x, Tree y, Tree z) const;
    ostream& printfun (ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree zz) const;
    ostream& printfun (ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree z2, Tree z3) const;
    ostream& printout (ostream& fout, int i, Tree x) const;
	ostream& printlist (ostream& fout, Tree largs) const;
	ostream& printff (ostream& fout, Tree ff, Tree largs) const;
	ostream& printrec (ostream& fout, Tree var, Tree lexp, bool hide) const;
	ostream& printrec (ostream& fout, Tree lexp, bool hide) const;
	ostream& printextended (ostream& fout, Tree sig) const;
	ostream& printui (ostream& fout, const string& funame, Tree label) const;
	ostream& printui (ostream& fout, const string& funame, Tree label, Tree lo, Tree hi, Tree step) const;
	ostream& printui (ostream& fout, const string& funame, Tree label, Tree cur, Tree lo, Tree hi, Tree step) const;
	ostream& printlabel (ostream& fout, Tree pathname) const;
	ostream& printFixDelay (ostream& fout, Tree exp, Tree delay) const;

};

inline ostream& operator << (ostream& file, const ppsig& pp) { return pp.print(file); }

#endif
