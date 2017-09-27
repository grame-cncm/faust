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

#include <iostream>

#include "exception.hh"
#include "sigvisitor.hh"

using namespace std;

/**
 * Infere the type of a term according to its surrounding type environment
 * @param sig the signal to aanlyze
 * @param env the type environment
 * @return the type of sig according to environment env
 */
 
void sigvisitor::visit(Tree sig)
{
	int 		i;
	double 		r;
    Tree		sel, s1, s2, s3, s4, ff, id, ls, l, var, body, type, name, file, cur, min, max, step;
	
	faustassert(sig);
	
		 if (isSigInt(sig, &i))					visitInt (sig, i);
		
	else if (isSigReal(sig, &r)) 				visitReal (sig, r);
	
	else if (isSigInput(sig, &i))				visitInput (sig, i);
		
	else if (isSigOutput(sig, &i, s1)) 			visitOutput (sig, i, s1);
	
	else if (isSigDelay1(sig, s1)) 				visitDelay1 (sig, s1);
	
	else if (isSigPrefix(sig, s1, s2)) 			visitPrefix (sig, s1, s2);
	
	else if (isSigFixDelay(sig, s1, s2)) 		visitFixDelay (sig, s1, s2);
	
	else if (isSigBinOp(sig, &i, s1, s2)) 		visitBinOp(sig, i, s1, s2);
		
	else if (isSigIntCast(sig, s1))				visitIntCast(sig, s1);
	
	else if (isSigFloatCast(sig, s1)) 			visitFloatCast(sig, s1);

	else if (isSigFFun(sig, ff, ls)) 			visitFFun(sig,ff,ls);

    else if (isSigFConst(sig,type,name,file))   visitFConst(sig,type,name,file);

    else if (isSigFVar(sig,type,name,file))     visitFVar(sig,type,name,file);
			
	//---------------
	
	else if (isSigButton(sig, l)) 							visitButton(sig, l);
	
	else if (isSigCheckbox(sig, l))							visitCheckbox(sig, l);
	
	else if (isSigVSlider(sig, l, cur, min, max, step))		visitVSlider(sig, l, cur, min, max, step);
	 
	else if (isSigHSlider(sig, l, cur, min, max, step))		visitHSlider(sig, l, cur, min, max, step);
	
	else if (isSigNumEntry(sig, l, cur, min, max, step))	visitNumEntry(sig, l, cur, min, max, step);
		
	else if (isSigHBargraph(sig, l, min, max, s1)) 			visitHBargraph(sig, l, min, max, s1);
		
	else if (isSigVBargraph(sig, l, min, max, s1)) 			visitVBargraph(sig, l, min, max, s1);
		
    else if (isSigAttach(sig, s1, s2)) 						visitAttach(sig, s1, s2);

    else if (isSigEnable(sig, s1, s2)) 						visitEnable(sig, s1, s2);

    else if (isSigControl(sig, s1, s2)) 					visitControl(sig, s1, s2);

	//------------------------
	
	else if (isRec(sig, var, body))				visitRec(sig, var, body);
				
	else if (isRef(sig, var))					visitRef(sig, var); 

	else if (isProj(sig, &i, s1))				visitProj(sig, i, s1);
			
	//----------------------------                                               
				
	else if (isSigTable(sig, id, s1, s2)) 		visitTable(sig, id, s1, s2);
		
	else if (isSigWRTbl(sig, id, s1, s2, s3)) 	visitWRTbl(sig, id, s1, s2, s3); 
			
	else if (isSigRDTbl(sig, s1, s2)) 			visitRDTbl(sig, s1, s2);  
		
	else if (isSigGen(sig, s1)) 				visitGen(sig, s1);

    else if (isSigDocConstantTbl(sig, s1, s2)) 	visitDocConstantTbl(sig, s1, s2);

    else if (isSigDocWriteTbl(sig,s1,s2,s3,s4)) visitDocWriteTbl(sig,s1,s2,s3,s4);

    else if (isSigDocAccessTbl(sig,s1,s2)) 		visitDocAccessTbl(sig,s1,s2);
	
	//----------------------------                                               
				
	else if (isSigSelect2(sig,sel,s1,s2)) 		visitSelect2(sig,sel,s1,s2); 
		
	else if (isSigSelect3(sig,sel,s1,s2,s3)) 	visitSelect3(sig,sel,s1,s2,s3); 		
	
	else if (isList(sig)) 						visitList(sig);	
	
	//----------------------------                                               
				
	else if (isSigTuple(sig,&i,ls)) 			visitTuple(sig,i,ls); 
		
	else if (isSigTupleAccess(sig,s1,s2)) 		visitTupleAccess(sig,s1,s2); 		
			
	//----------------------------                                               
				
	else 										visitError(sig);
}

void sigvisitor::visitError(Tree sig)
{
	cerr << "ERROR visiting signal" << endl;
}
