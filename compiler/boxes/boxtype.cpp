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
 
/*****************************************************************************
******************************************************************************
	
							  Box Type System
	
******************************************************************************
*****************************************************************************/

/**\file boxtype.cpp
 * \author Yann Orlarey
 * \version 1.0
 * \date 2003
 * \brief A simple type system for block diagram expressions.
 *  The type of a block diagram is defined by a number of inputs and outputs.
 */

#include <stdio.h>
#include <string.h>
#include "boxes.hh"
#include "ppbox.hh"
#include "prim2.hh"
#include "xtended.hh"
#include "exception.hh"
#include "global.hh"

static bool infereBoxType (Tree box, int* inum, int* onum);

/**
 * Return the type (number of inputs and outputs) of a box or false if undefined
 * \param box the box we want to know the type
 * \param inum the place to return the number of inputs
 * \param onum the place to return the number of outputs
 * \return true if type is defined, false if undefined
 */

bool getBoxType (Tree box, int* inum, int* onum)
{
	Tree t;
	if (getProperty(box, gGlobal->BOXTYPEPROP, t)) {
		
		if (isNil(t)) {
			return false;
		} else {
			*inum = hd(t)->node().getInt();
			*onum = tl(t)->node().getInt();
			return true;
		}
		
	} else {
	
		if (infereBoxType(box, inum, onum)) {
			setProperty(box, gGlobal->BOXTYPEPROP, cons(tree(*inum), tree(*onum)));
			return true;
		} else {
			setProperty(box, gGlobal->BOXTYPEPROP, gGlobal->nil);
			return false;
		}
	}
}

/**
 * Infere the type (number of inputs and outputs) of a box.
 * The box expression is assumed to be in 'propagation normal form'
 * that is to have been evaluated and residual abstractions to have been
 * converted to symbolic boxes (using a2sb()).
 * \param box the box we want to know the type
 * \param inum the place to return the number of inputs
 * \param onum the place to return the number of outputs
 * \return true if the box expression has a type
 */

static bool infereBoxType (Tree t, int* inum, int* onum)
{
	Tree a, b, ff, l, s, c;
	//Tree abstr, genv, vis, lenv;
	
	xtended* p = (xtended*) getUserData(t);

	if (p) 						{ *inum = p->arity(); *onum = 1; }
	else if (isBoxInt(t)) 		{ *inum = 0; *onum = 1; } 
	else if (isBoxReal(t)) 		{ *inum = 0; *onum = 1; } 
	
	else if (isBoxWaveform(t)) 	{ *inum = 0; *onum = 2; } 

	else if (isBoxWire(t)) 		{ *inum = 1; *onum = 1; }
	else if (isBoxCut(t)) 		{ *inum = 1; *onum = 0; } 

    else if (isBoxSlot(t))          { *inum = 0; *onum = 1; }
	else if (isBoxSymbolic(t,s,b)) 	{ if (!getBoxType(b, inum, onum)) return false; *inum += 1; } 
	
    else if (isBoxPatternVar(t,a))  { return false; }

    else if (isBoxPrim0(t)) 	{ *inum = 0; *onum = 1; }
	else if (isBoxPrim1(t)) 	{ *inum = 1; *onum = 1; } 
	else if (isBoxPrim2(t)) 	{ *inum = 2; *onum = 1; } 
	else if (isBoxPrim3(t)) 	{ *inum = 3; *onum = 1; } 
	else if (isBoxPrim4(t)) 	{ *inum = 4; *onum = 1; } 
	else if (isBoxPrim5(t)) 	{ *inum = 5; *onum = 1; } 
		
	else if (isBoxFFun(t,ff)) 	{ *inum = ffarity(ff); *onum = 1; } 
    else if (isBoxFConst(t))    { *inum = 0; *onum = 1; } 
    else if (isBoxFVar(t))      { *inum = 0; *onum = 1; } 
	
	else if (isBoxButton(t)) 	{ *inum = 0; *onum = 1; } 
	else if (isBoxCheckbox(t)) 	{ *inum = 0; *onum = 1; } 
	else if (isBoxVSlider(t)) 	{ *inum = 0; *onum = 1; } 
	else if (isBoxHSlider(t)) 	{ *inum = 0; *onum = 1; } 
	else if (isBoxNumEntry(t)) 	{ *inum = 0; *onum = 1; } 
    else if (isBoxVGroup(t,l,a)){ return getBoxType(a, inum, onum); }
    else if (isBoxHGroup(t,l,a)){ return getBoxType(a, inum, onum); }
    else if (isBoxTGroup(t,l,a)){ return getBoxType(a, inum, onum); }
	
	else if (isBoxVBargraph(t)) 	{ *inum = 1; *onum = 1; } 
	else if (isBoxHBargraph(t)) 	{ *inum = 1; *onum = 1; }
    else if (isBoxSoundfile(t, l, c)) {
        *inum = 1;
        *onum = 3+tree2int(c);
    }
	else if (isBoxSeq(t, a, b)) {
		int u,v,x,y;
		if (!getBoxType(a, &u, &v)) return false;
		if (!getBoxType(b, &x, &y)) return false;

		if (v != x) {
            stringstream error;
            error   << "ERROR in sequential composition (A:B)" << endl
                    << "The number of outputs (" << v << ") of A = " << boxpp(a) << endl
                    << "must be equal to the number of inputs (" << x << ") of B : " << boxpp(b) << endl;
            throw faustexception(error.str());
		} else {
            *inum = u;
            *onum = y;
		}

	} else if (isBoxPar(t, a, b)) {
		
		int u,v,x,y;
		if (!getBoxType(a, &u, &v)) return false;
		if (!getBoxType(b, &x, &y)) return false;

		*inum = u+x; *onum = v+y;

	} else if (isBoxSplit(t, a, b)) {
		
		int u,v,x,y;
		if (!getBoxType(a, &u, &v)) return false;
		if (!getBoxType(b, &x, &y)) return false;

        if (v == 0) {
            stringstream error;
            error   << "Connection error in : " << boxpp(t) << endl
                    << "The first expression : " << boxpp(a) << " has no outputs" << endl;
            throw faustexception(error.str());
        }
        
        if (x == 0) {
            stringstream error;
            error   << "Connection error in : " << boxpp(t) << endl
                    << "The second expression : " << boxpp(b) << " has no inputs" << endl;
            throw faustexception(error.str());
        }
		 
		if (x % v != 0) {
            stringstream error;
            error   << "Connection error in : " << boxpp(t) << endl
					<< "The number of outputs " << v
					<< " of the first expression should be a divisor of the number of inputs " << x
					<< " of the second expression" << endl;
			throw faustexception(error.str());
		}
		
		*inum = u; *onum = y;

	} else if (isBoxMerge(t, a, b)) {
		
		int u,v,x,y;
		if (!getBoxType(a, &u, &v)) return false;
		if (!getBoxType(b, &x, &y)) return false;

        if (v == 0) {
            stringstream error;
            error   << "Connection error in : " << boxpp(t) << endl
                    << "The first expression : " << boxpp(a) << " has no outputs" << endl;
            throw faustexception(error.str());
        }
        
        if (x == 0) {
            stringstream error;
            error   << "Connection error in : " << boxpp(t) << endl
                    << "The second expression : " << boxpp(b) << " has no inputs" << endl;
            throw faustexception(error.str());
        }
        
		if (v % x != 0) { 
			stringstream error;
            error   << "Connection error in : " << boxpp(t) << endl
					<< "The number of outputs " << v
					<< " of the first expression should be a multiple of the number of inputs " << x
					<< " of the second expression" << endl;
            throw faustexception(error.str());
		}

		*inum = u; *onum = y;

	} else if (isBoxRec(t, a, b)) {
		
		int u,v,x,y;
		if (!getBoxType(a, &u, &v)) return false;
		if (!getBoxType(b, &x, &y)) return false;
		if ( (x > v) | (y > u) ) { 
			stringstream error;
            error << "Connection error in : " << boxpp(t) << endl;
			if (x > v) error << "The number of outputs " << v 
                            << " of the first expression should be greater or equal \n  to the number of inputs " << x 
							<< " of the second expression" << endl;
			if (y > u) error << "The number of inputs " << u
							<< " of the first expression should be greater or equal \n  to the number of outputs " << y
							<< " of the second expression" << endl;
			throw faustexception(error.str());
		}
		*inum = max(0,u-y); *onum = v;
		
    } else if (isBoxEnvironment(t)) {
		*inum = 0;
		*onum = 0;

    } else {
        stringstream error;
        error << "boxType() internal error : unrecognized box expression " << boxpp(t) << endl;
        throw faustexception(error.str());
	}
	return true;
}	
		
		
	
