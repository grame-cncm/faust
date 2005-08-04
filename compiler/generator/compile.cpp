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
							FAUST SIGNAL COMPILER 
						Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
Compile a list of FAUST signals into a C++ class .

 History :
 ---------
 	2002-02-08 : First version
	
******************************************************************************
*****************************************************************************/



#include "compile.hh"
#include "sigtype.hh"

#include <stdio.h>
//#include <iostream> 

#include "sigprint.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "privatise.hh"
//#include "factorize.hh"

#include "grouper.hh"
//#include "sigvisitor.hh"




/*****************************************************************************
******************************************************************************

							    	API
	
******************************************************************************
*****************************************************************************/

extern int 	gDetailsSwitch;

//map<string, int>	Compiler::fIDCounters;
/*
void compileSignals (const string& name, const string& super, int numInputs, int numOutputs, Tree lsig) 
{ 
	Compiler C(name, super, numInputs, numOutputs);
	//C.getClass()->println(1);
	//C.getClass()->addIncludeFile("math.h");
	C.compileMultiSignal(lsig); 
	C.getClass()->printIncludeFile();
	C.getClass()->println(1);
}
*/




/*****************************************************************************
******************************************************************************

						  GENERAL COMPILER METHODS
	
******************************************************************************
*****************************************************************************/







/*****************************************************************************
							   constructor
*****************************************************************************/

Compiler::Compiler(const string& name, const string& super, int numInputs, int numOutputs, bool vec) 
		: fClass(new Klass(name, super, numInputs, numOutputs, vec)),
		//fNumInputs(numInputs), fNumOutputs(numOutputs), 
		//fSharingKey(nil), 
		//fUIRoot(uiFolder(cons(tree(0), tree("\"\""))))
		fUIRoot(uiFolder(cons(tree(0), tree("\"faust\""))))
{}

Compiler::Compiler(Klass* k)  
		: fClass(k), 
		//fNumInputs(1), fNumOutputs(1), 
		//fSharingKey(nil),
		  fUIRoot(uiFolder(cons(tree(0), tree("\"faust\"")))) 
{}


Compiler::~Compiler()
{}

/*****************************************************************************
						    compileMultiSignal
*****************************************************************************/
/*
void Compiler::compileMultiSignal (Tree L)
{	
	L = prepare(L);		// optimize, share and annotate expression
	for (int i = 0; i < fClass->inputs(); i++) {
		fClass->addSlowCode(subst("float* input$0 = input[$0];", T(i)));
	}
	for (int i = 0; i < fClass->outputs(); i++) {
		fClass->addSlowCode(subst("float* output$0 = output[$0];", T(i)));
	}
	for (int i = 0; isList(L); L = tl(L), i++) {
		Tree sig = hd(L);
		fClass->addExecCode(subst("output$0[i] = $1;", T(i), CS(NULLENV, sig)));
	}
	generateUserInterfaceTree(fUIRoot);
}
*/

/*****************************************************************************
						    compileSingleSignal
*****************************************************************************/
/*
void Compiler::compileSingleSignal (Tree sig)
{	
	sig = prepare2(sig);		// optimize and annotate expression
	fClass->addExecCode(subst("output[i] = $0;", CS(NULLENV, sig)));
	//fClass->addIncludeFile("bidon");
	generateUserInterfaceTree(fUIRoot);
}
*/

/*****************************************************************************
				      Prepare signal for compilation
*****************************************************************************/

Tree Compiler::prepare (Tree L0)
{	
//	fprintf(stderr, "L0 = "); printSignal(L0, stderr); fputs("\n", stderr);
	Tree L1 = simplify(L0);			// simplify by executing every computable operation 
	//fprintf(stderr, "L1 = "); printSignal(L1, stderr); fputs("\n", stderr);	
	Tree L2a = deBruijn2Sym(L1);
	Tree L2 = simplify(L2a);			// simplify by executing every computable operation 
	//Tree L2	= 
	//factorizeAddTerms(L2);
	
	//fprintf(stderr, "L2 = "); printSignal(L2, stderr); fputs("\n", stderr);	
	Tree L3 = privatise(L2);		// Un-share tables with multiple writers
	updateAperture(L3);
	typeAnnotation(L3);
	
	// calcul du parallelisme
	//fullvisitor fv;
	//fv.visit(L3);
	
	//grouper mygrouper;
	//mygrouper.visit(L3);
	//for (Tree zz= L3; !isNil(zz); zz = tl(zz)) 	mygrouper.dispatchInGroups(hd(zz));
	//cerr << mygrouper << endl;
	
	//sharingAnalysis(L3);			// annotate L3 with sharing count
//	fprintf(stderr, "L3 = "); printSignal(L3, stderr); fputs("\n", stderr);	
	
	
//	Type tp = getSigType(L3, NULLENV );
//	if (gDetailsSwitch) { cout << "signal type details: " << tp << endl;}
	
//	fCompileKey = makeCompileKey(L2); etrange !!!!!
	//fCompileKey = makeCompileKey(L3);
	return L3;
}

Tree Compiler::prepare2 (Tree L0)
{	
// 	fprintf(stderr, "L0 = "); printSignal(L0, stderr); fputs("\n", stderr);
// 	Tree L1 = simplify(L0);			// simplify by executing every computable operation 
// 	Tree L2 = deBruijn2Sym(L1);
//	Tree L3 = privatise(L2);		// Un-share tables with multiple writers
//	updateAperture(L3);
	Tree L3 = L0;
	typeAnnotation(L3);
	//sharingAnalysis(L3);			// annotate L3 with sharing count
//	fprintf(stderr, "L3 = "); printSignal(L3, stderr); fputs("\n", stderr);	
	
	
	Type tp = getSigType(L3, NULLENV );
//	if (gDetailsSwitch) { cout << "signal type details: " << tp << endl;}
	
	//fCompileKey = makeCompileKey(L3);
	return L3;
}



/*****************************************************************************
							 CS : compile a signal
*****************************************************************************/
/**
 * Compile a signal
 * @param env the type environment (enclosing recursions).
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */
/*
string	Compiler::CS (Tree env, Tree sig)
{
	Tree t; 
#if 0	
	fprintf(stderr, "CALL CS("); 
		print(env, stderr);  
		fprintf(stderr, ", ");
		printSignal(sig, stderr); 
	fprintf(stderr, ")\n");
#endif
	
	if (getProperty(sig, fCompileKey, t)) {
		// terme deja visité

#if 0			
		fprintf(stderr, "RETURN of CS("); 
			print(env, stderr);  
			fprintf(stderr, ", ");
			printSignal(sig, stderr); 
		fprintf(stderr, ") -found-> "); print(t, stderr); fputc('\n', stderr);
#endif
		return name(t->node().getSym());
		
	} else {
		
		string s = generateCode(env, sig);
		const char * r = s.c_str();
		setProperty(sig, fCompileKey, tree(r));
		
#if 0
		fprintf(stderr, "RETURN of CS("); 
			print(env, stderr);  
			fprintf(stderr, ", ");
			printSignal(sig, stderr); 
		fprintf(stderr, ") -computed-> %s \n", r);
#endif
		return s;
	}
}
*/


/*****************************************************************************
						generateCode : dispatch according to signal
*****************************************************************************/
/**
 * Main code generator dispatch.
 * @param env the type environment.
 * @param sig the signal expression to compile.
 * @return the C code translation of sig
 */
/*
string	Compiler::generateCode (Tree env, Tree sig)
{
#if 0
	fprintf(stderr, "CALL generateCode("); 
		print(env, stderr);  
		fprintf(stderr, ", ");
		printSignal(sig, stderr); 
	fprintf(stderr, ")\n");
#endif
		
	int 	i;
	float	r;
	//const char	*ct, *vn;
	Tree 	c, sel, x, y, z, var, le, label, id, ff, largs;
		
	//printf("compilation of %p : ", sig); print(sig); printf("\n");  
	    
	 if ( isSigInt(sig, &i) ) 					{ return T(i); }
	else if ( isSigReal(sig, &r) ) 					{ return T(r); }
	else if ( isSigInput(sig, &i) ) 				{ return generateInput 		(env, sig, T(i)); 			}
	else if ( isSigOutput(sig, &i, x) ) 			{ return generateOutput 	(env, sig, T(i), CS(env,x));}
	
	else if ( isSigDelay1(sig, x) ) 				{ return generateDelay1 	(env, sig, x); 		}

	else if ( isSigBinOp(sig, &i, x, y) )			{ return generateBinOp 		(env, sig, i, x, y); 		}
	else if ( isSigFFun(sig, ff, largs) )			{ return generateFFun 		(env, sig, ff, largs); 		}
	
	else if ( isSigTable(sig, id, x, y) ) 			{ return generateTable 		(env, sig, x, y); 			}
	else if ( isSigWRTbl(sig, id, x, y, z) )		{ return generateWRTbl 		(env, sig, x, y, z); 		}
	else if ( isSigRDTbl(sig, x, y) ) 				{ return generateRDTbl 		(env, sig, x, y); 			}
	
	else if ( isSigSelect2(sig, sel, x, y) ) 		{ return generateSelect2 	(env, sig, sel, x, y); 		}
	else if ( isSigSelect3(sig, sel, x, y, z) ) 	{ return generateSelect3 	(env, sig, sel, x, y, z); 	}
	
	else if ( isSigGen(sig, x) ) 					{ return generateSigGen 	(env, sig, x); 				}

	else if ( isProj(sig, &i, x) ) 					{ return generateRecProj 	(env, sig, CS(env,x), i); 	}
	else if ( isRec(sig, var, le))					{ return generateRecGroup 	(env, sig, var, le); 		}
	//else if ( isRef(sig, var) ) 					{ return CS(env,var); } //compiled in enclosing rec
 
	else if ( isSigIntCast(sig, x) ) 				{ return generateIntCast   	(env, sig, x); 				}
	else if ( isSigFloatCast(sig, x) ) 				{ return generateFloatCast 	(env, sig, x); 				}
 
	else if ( isSigButton(sig, label) ) 			{ return generateButton   	(env, sig, label); 			}
	else if ( isSigCheckbox(sig, label) ) 			{ return generateCheckbox 	(env, sig, label); 			}	
	else if ( isSigVSlider(sig, label,c,x,y,z) )	{ return generateVSlider 	(env, sig, label, c,x,y,z); }
	else if ( isSigHSlider(sig, label,c,x,y,z) )	{ return generateHSlider 	(env, sig, label, c,x,y,z); }
	else if ( isSigNumEntry(sig, label,c,x,y,z) )	{ return generateNumEntry 	(env, sig, label, c,x,y,z); }
	
	else {
		printf("Error in compiling signal :");
		print(sig);
		printf("\n");
		exit(1);
	}
	return "error in generate code";
}
*/



/*****************************************************************************
						getFreshID
*****************************************************************************/
/*
string Compiler::getFreshID(const char* prefix)
{
	char c[64]; 
	
	if (fIDCounters.find(prefix) == fIDCounters.end()) {
		fIDCounters[prefix]=0;;
	}
	int n = fIDCounters[prefix];
	fIDCounters[prefix] = n+1;
	
	snprintf(c, 63, "%s%d", prefix, n); 	
	return string(c); 
}
*/


/*****************************************************************************
						makeCompileKey
*****************************************************************************/
/*
Tree Compiler::makeCompileKey(Tree t) 
{
	char 	name[256];
	snprintf(name, 256, "COMPILED IN %p : ", (CTree*)t);
	return tree(unique(name));
}	

*/



/*****************************************************************************
							user interface elements
*****************************************************************************/

void Compiler::addUIWidget(Tree path, Tree widget)
{
	fUIRoot = putSubFolder(fUIRoot, path, widget);
}

void Compiler::generateWidgetCode(Tree label, Tree varname, Tree sig)
{
	Tree path, c, x, y, z;
	
	if ( isSigButton(sig, path) ) 					{ 
		fClass->addUICode(subst("interface->addButton($0, &$1);", tree2str(label), tree2str(varname))); 
			
	} else if ( isSigCheckbox(sig, path) ) 			{ 
		fClass->addUICode(subst("interface->addCheckButton($0, &$1);", tree2str(label), tree2str(varname))); 
			
	} else if ( isSigVSlider(sig, path,c,x,y,z) )	{ 
		fClass->addUICode(subst("interface->addVerticalSlider($0, &$1, $2, $3, $4, $5);", 
				tree2str(label), 
				tree2str(varname), 
				T(tree2float(c)), 
				T(tree2float(x)),
				T(tree2float(y)), 
				T(tree2float(z)))); 
		
	} else if ( isSigHSlider(sig, path,c,x,y,z) )	{ 
		fClass->addUICode(subst("interface->addHorizontalSlider($0, &$1, $2, $3, $4, $5);", 
				tree2str(label), 
				tree2str(varname), 
				T(tree2float(c)), 
				T(tree2float(x)),
				T(tree2float(y)), 
				T(tree2float(z)))); 
		
	} else if ( isSigNumEntry(sig, path,c,x,y,z) )	{ 
		fClass->addUICode(subst("interface->addNumEntry($0, &$1, $2, $3, $4, $5);", 
				tree2str(label), 
				tree2str(varname), 
				T(tree2float(c)), 
				T(tree2float(x)),
				T(tree2float(y)), 
				T(tree2float(z)))); 
			
	} else if ( isSigVBargraph(sig, path,x,y,z) )	{ 
		fClass->addUICode(subst("interface->addVerticalBargraph($0, &$1, $2, $3);", 
				tree2str(label), 
				tree2str(varname), 
				T(tree2float(x)), 
				T(tree2float(y)))); 
		
	} else if ( isSigHBargraph(sig, path,x,y,z) )	{ 
		fClass->addUICode(subst("interface->addHorizontalBargraph($0, &$1, $2, $3);", 
				tree2str(label), 
				tree2str(varname), 
				T(tree2float(x)), 
				T(tree2float(y)))); 
		
	} else {
		fprintf(stderr, "Error in generating widget code\n");
		exit(1);
	}
}


// Remove fake root folder if not needed (that is if the UI
// is completely enclosed in one folder
Tree Compiler::prepareUserInterfaceTree(Tree t)
{
	Tree root, elems;
	if (isUiFolder(t, root, elems) && isList(elems) && isNil(tl(elems)) ) {
		Tree folder = right(hd(elems));
		return (isUiFolder(folder)) ? folder : t;
	}
	return t;
}
 
void Compiler::generateUserInterfaceTree(Tree t)
{
	Tree 	label, elements, varname, sig;
	
	if (isUiFolder(t, label, elements)) {
		const int		orient = tree2int(left(label));
		const char * 	str = tree2str(right(label));
		const char * 	model;
		
		switch (orient) {
			case 0 : model = "interface->openVerticalBox($0);"; break;
			case 1 : model = "interface->openHorizontalBox($0);"; break;
			case 2 : model = "interface->openTabBox($0);"; break;
			default : 
					fprintf(stderr, "error in user interface generation 1\n");
				exit(1);
		}
		fClass->addUICode(subst(model, str));
		generateUserInterfaceElements(elements);
		fClass->addUICode("interface->closeBox();");
		
	} else if (isUiWidget(t, label, varname, sig)) {
			
		generateWidgetCode(label, varname, sig);
		
	} else {
		
		fprintf(stderr, "error in user interface generation 2\n");
		exit(1);
		
	}
}
 
void Compiler::generateUserInterfaceElements(Tree elements)
{
	while (!isNil(elements)) {
		generateUserInterfaceTree(right(hd(elements)));
		elements = tl(elements);
	}		
}
