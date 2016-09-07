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
 
#ifndef _PPBOX_H
#define _PPBOX_H

/**********************************************************************
			- ppbox.h : pretty print box expressions (projet FAUST) -
					

		Historique :
		-----------
		12-07-2002  first implementation  (yo)
		
***********************************************************************/

#include <iostream>
#include <sstream>
#include "boxes.hh"
#include "garbageable.hh"

using namespace std;

//void 		fppbox (FILE* fout, Tree box, int priority=0);
//inline void	ppbox  (Tree box, int priority=0) 					{ fppbox(stdout, box, priority); }

const char * prim0name(CTree *(*ptr) ());
const char * prim1name(CTree *(*ptr) (CTree *));
const char * prim2name(CTree *(*ptr) (CTree *, CTree *));
const char * prim3name(CTree *(*ptr) (CTree *, CTree *, CTree *));
const char * prim4name(CTree *(*ptr) (CTree *, CTree *, CTree *, CTree *));
const char * prim5name(CTree *(*ptr) (CTree *, CTree *, CTree *, CTree *, CTree *));

// box pretty printer.
// usage : out << boxpp(aBoxExp);

class boxpp : public virtual Garbageable
{
    protected:
        Tree box;
        int priority;
    public:
        boxpp(Tree b, int p=0) : box(b), priority(p) {}
        virtual ~boxpp() {}
        virtual ostream& print (ostream& fout) const;
};

inline ostream& operator << (ostream& file, const boxpp& bpp) { return bpp.print(file); }


// box pretty printer.
// usage : out << boxpp(aBoxExp);

// Used on the stack so not Garbageable 

class envpp : public virtual Garbageable
{
	Tree 	fEnv;
public:
	envpp(Tree e) : fEnv(e) {}
	ostream& print (ostream& fout) const;
};

inline ostream& operator << (ostream& file, const envpp& epp) { return epp.print(file); }

#endif
