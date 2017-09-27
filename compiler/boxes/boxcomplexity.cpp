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
/**
 * @file boxcomplexity.cpp
 * Implement complexity computation for box diagrams.
 */
 
// construction des representations graphiques

#include <ostream>
#include "xtended.hh"
#include "boxcomplexity.hh"
#include "exception.hh"
#include "global.hh"

using namespace std;

/**
 * property Key used to store box complexity
 */

static int computeBoxComplexity (Tree box);

/**
 * Return the complexity propety of a box expression tree.
 * Return the complexity propety of a box expression tree. If no 
 * complexity property exist, it is created an computeBoxComplexity
 * is called do to the job.
 *
 * @param box an evaluated box expression tree
 * @return the complexity of box
 *
 * @see computeBoxComplexity
 */
int boxComplexity (Tree box)
{
	Tree prop = box->getProperty(gGlobal->BCOMPLEXITY);
	
	if (prop) {
		return tree2int(prop);
		
	} else {
		int v = computeBoxComplexity(box);
		box->setProperty(gGlobal->BCOMPLEXITY,tree(v));
		return v;
	}
}

/**
 * internal shortcut to simplify computeBoxComplexity code
 */
#define BC boxComplexity


/**
 * Compute the complexity of a box expression.
 *
 * Compute the complexity of a box expression tree according to the 
 * complexity of its subexpressions. Basically it counts the number 
 * of boxes to be drawn. The box-diagram expression is supposed
 * to be evaluated. It will exit with an error if it is not the case.
 *
 * @param box an evaluated box expression tree
 * @return the complexity of box
 */
int computeBoxComplexity (Tree box)
{
	int		i;
	double	r;
	prim0	p0;
	prim1	p1;
	prim2	p2;
	prim3	p3;
	prim4	p4;
	prim5	p5;

	Tree	t1, t2, ff, label, cur, min, max, step, type, name, file, chan;
	
	xtended* xt = (xtended*) getUserData(box);

	
	// simple elements 
		 if (xt) 						return 1;
	else if (isBoxInt(box, &i))			return 1; 
    else if (isBoxReal(box, &r))		return 1;

    else if (isBoxWaveform(box))        return 1;

	else if (isBoxCut(box))				return 0; 
	else if (isBoxWire(box))			return 0; 
	 
	else if (isBoxPrim0(box, &p0))		return 1;  
	else if (isBoxPrim1(box, &p1))		return 1;  
	else if (isBoxPrim2(box, &p2))		return 1;  
	else if (isBoxPrim3(box, &p3))		return 1;  
	else if (isBoxPrim4(box, &p4))		return 1;  
	else if (isBoxPrim5(box, &p5))		return 1; 
	
	// foreign elements 
	else if (isBoxFFun(box, ff))		return 1; 
    else if (isBoxFConst(box, type, name, file))        
                                        return 1; 
    else if (isBoxFVar(box, type, name, file))        
                                        return 1; 
	// slots and symbolic boxes
	else if (isBoxSlot(box, &i))		return 1;
	else if (isBoxSymbolic(box,t1,t2))	return 1 + BC(t2);
	
	// block diagram binary operator 
	else if (isBoxSeq(box, t1, t2))		return BC(t1) + BC(t2);
	else if (isBoxSplit(box, t1, t2))	return BC(t1) + BC(t2);
	else if (isBoxMerge(box, t1, t2)) 	return BC(t1) + BC(t2);
	else if (isBoxPar(box, t1, t2)) 	return BC(t1) + BC(t2);
	else if (isBoxRec(box, t1, t2)) 	return BC(t1) + BC(t2);
	
	// user interface widgets
	else if (isBoxButton(box, label))						return 1;  
	else if (isBoxCheckbox(box, label))						return 1;  
	else if (isBoxVSlider(box, label, cur, min, max, step))	return 1;
	else if (isBoxHSlider(box, label, cur, min, max, step))	return 1;
	else if (isBoxHBargraph(box, label, min, max))			return 1;
	else if (isBoxVBargraph(box, label, min, max))			return 1;
	else if (isBoxSoundfile(box, label, chan))				return 1;
	else if (isBoxNumEntry(box, label, cur, min, max, step))return 1;
	
	// user interface groups
	else if (isBoxVGroup(box, label, t1))	return BC(t1);
	else if (isBoxHGroup(box, label, t1))	return BC(t1);
	else if (isBoxTGroup(box, label, t1))	return BC(t1);

	//a completer
	else {
		//fout << tree2str(box);
        stringstream error;
        error << "ERROR in boxComplexity : not an evaluated box [[  " << *box << " ]]\n";
        throw faustexception(error.str());
	}

	return -1;
}
