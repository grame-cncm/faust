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
 
/************************************************************************
 ************************************************************************
    Signals Order Rules
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    A small typing system that computes the "order" of a signal :
		0 = numerical constant
		1 = non-numerical constants (FConst)
		2 = User Interface
		3 = Audio
	This order will be used to put expressions in normal form.
	
	Contrary to the full type system, it doesn't require environments
	or special treatments for recursions
 ************************************************************************
 ************************************************************************/
 
#include <stdio.h>
#include "sigtype.hh"
#include "sigprint.hh"
#include "prim2.hh"
#include "tlib.hh"
#include "sigorderrules.hh"
#include "xtended.hh"
#include "exception.hh"
#include "global.hh"

static int infereSigOrder(Tree sig);

/**
 * retrieve the order annotation (between 0 and 3) of a signal.
 * (compute the order the first time). Orders have the following meanings
 *	0 : numbers
 *	1 : constants
 *	2 : user interface values
 *	3 : audio values
 * @param sig the signal we want to know the order
 * @return the order number
 */
int getSigOrder(Tree sig)
{
	Tree tt;
	if (getProperty(sig, gGlobal->ORDERPROP, tt)) { 
		return tree2int(tt); 
	} else {
		int order = infereSigOrder(sig);
		setProperty(sig, gGlobal->ORDERPROP, tree(order));
		return order;
	}
}	

// shortcut for order inference algorithm
#define O getSigOrder

/**
 * Infere the order of a term according to its components
 * @param sig the signal to analyze
 * @return the order of sig 
 */
static int infereSigOrder(Tree sig)
{
	int 		i;
	double 		r;
    Tree		sel, s1, s2, s3, s4, ff, id, ls, l, x, y, var, body, type, name, file, sf;

	xtended* xt = (xtended*) getUserData(sig);
	// primitive elements
	if (xt) 								
	{
		//return 3;
		vector<int> args;
		for (int i=0; i<sig->arity(); i++) { args.push_back( O(sig->branch(i)) ); }
		return xt->infereSigOrder(args);
	}
	
	else if (isSigInt(sig, &i))					return 0;
		
    else if (isSigReal(sig, &r)) 				return 0;

    else if (isSigWaveform(sig))                return 3;

	else if (isSigInput(sig, &i))				return 3;
		
	else if (isSigOutput(sig, &i, s1)) 			return 3;
		
	else if (isSigDelay1(sig, s1)) 				return 3;
	
	else if (isSigPrefix(sig, s1, s2)) 			return 3;
	
	else if (isSigFixDelay(sig, s1, s2)) 		return 3;
	
	else if (isSigBinOp(sig, &i, s1, s2)) 		return max(O(s1),O(s2));
	
	else if (isSigIntCast(sig, s1))				return O(s1);
        
    else if (isSigFloatCast(sig, s1))           return O(s1);

    else if (isSigFFun(sig,ff,ls) && isNil(ls)) return 1;

    else if (isSigFFun(sig, ff, ls))            return max(1,O(ls));

    else if (isSigFConst(sig,type,name,file))   return 1;

    else if (isSigFVar(sig,type,name,file))     return 2;
		
	else if (isSigButton(sig)) 					return 2;
	
	else if (isSigCheckbox(sig))				return 2;
	
	else if (isSigVSlider(sig))					return 2;
	 
	else if (isSigHSlider(sig))					return 2;
	
	else if (isSigNumEntry(sig))				return 2;
		
	else if (isSigHBargraph(sig, l, x, y, s1)) 	return max(2,O(s1)); 	// at least a user interface
		
	else if (isSigVBargraph(sig, l, x, y, s1)) 	return max(2,O(s1)); 	// at least a user interface
	
    else if (isSigEnable(sig, s1, s2)) 			return O(s1);

    else if (isSigControl(sig, s1, s2)) 		return O(s1);

    else if (isSigSoundfile(sig, l))			throw faustexception("ERROR infering signal order : isSigSoundfile\n");	// not supposed to happen.;
    
	else if (isSigSoundfileLength(sig, sf) )	return 2;
    
	else if (isSigSoundfileRate(sig, sf) )	    return 2;
    
	else if (isSigSoundfileChannel(sig,sf,x,y)) return 3;

	else if (isSigAttach(sig, s1, s2)) 			return max(1,O(s1));	// at least a constant
				
	else if (isRec(sig, var, body))				throw faustexception("ERROR infering signal order : isRec\n"); //return 3;  // not supposed to happen.
				
	else if (isRef(sig, var))					throw faustexception("ERROR infering signal order : isRef\n"); //return 3;  // not supposed to happen. 

	else if (isProj(sig, &i, s1))				return 3;
	                                                	
	else if (isSigTable(sig, id, s1, s2)) 		return 3;
		
	else if (isSigWRTbl(sig, id, s1, s2, s3)) 	return 3; 
			
    else if (isSigRDTbl(sig, s1, s2)) 			return 3;

    else if (isSigDocConstantTbl(sig, s1, s2)) 	return 3;

    else if (isSigDocWriteTbl(sig,s1,s2,s3,s4)) return 3;

    else if (isSigDocAccessTbl(sig,s1,s2))      return 3;

    else if (isSigGen(sig, s1)) 				return 3;
		
	else if (isSigSelect2(sig,sel,s1,s2)) 		return 3;
		
	else if (isSigSelect3(sig,sel,s1,s2,s3)) 	return 3;	
	
	else if (isList(sig)) 
	{
		int r = 0;
		while (isList(sig)) { int x = O(hd(sig)); if (x > r) r = x; sig = tl(sig); }
		return r;
	}
	
	// unrecognized signal here
    throw faustexception("ERROR inferring signal order : unrecognized signal\n");
}

