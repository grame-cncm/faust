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
	HISTORY
	22/01/05 : corrected bug on bool signals cached in float variables
	2009-08-16 : First "doc" version (kb)
	2009-11-22 : Some clean up (kb)
*****************************************************************************/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

#include "doc_compile.hh"
#include "sigtype.hh"
#include "floats.hh"
#include "sigprint.hh"
#include "sigtyperules.hh"
#include "recursivness.hh"
#include "simplify.hh"
#include "privatise.hh"
#include "prim2.hh"
#include "xtended.hh"
#include "compatibility.hh"
#include "ppsig.hh"
#include "names.hh"
#include "doc.hh"
#include "tlib.hh"
#include "doc_notice.hh"
#include "exception.hh"
#include "global.hh"

extern bool getSigListNickName(Tree t, Tree& id);


/*****************************************************************************
						getFreshID
*****************************************************************************/

string DocCompiler::getFreshID(const string& prefix)
{
	if (gGlobal->gIDCounters.find(prefix) == gGlobal->gIDCounters.end()) {
		gGlobal->gIDCounters[prefix] = 1;
	}
	int n = gGlobal->gIDCounters[prefix];
	gGlobal->gIDCounters[prefix] = n+1;
	
	return subst("$0_{$1}", prefix, docT(n));
}


/*****************************************************************************
						    prepare
*****************************************************************************/

Tree DocCompiler::annotate(Tree LS)
{
	recursivnessAnnotation(LS);		// Annotate LS with recursivness information
	typeAnnotation(LS);				// Annotate LS with type information
	sharingAnalysis(LS);			// annotate LS with sharing count
    fOccMarkup.mark(LS);			// annotate LS with occurences analysis

  	return LS;
}

/*****************************************************************************
						    compileLateq
*****************************************************************************/

Lateq* DocCompiler::compileLateq (Tree L, Lateq* compiledEqn)
{
	//cerr << "Documentator : compileLateq : L = "; printSignal(L, stdout, 0); cerr << endl;
	
	fLateq = compiledEqn; ///< Dynamic field !
	int priority = 0;
	
	for (int i = 0; isList(L); L = tl(L), i++) {
		Tree sig = hd(L);
		Tree id;
		if(getSigNickname(sig, id)) {
			//cerr << "Documentator : compileLateq : NICKNAMEPROPERTY = " << tree2str(id) << endl;
			fLateq->addOutputSigFormula(subst("$0(t) = $1", tree2str(id), CS(sig, priority), docT(i)));	
		} else {
			//cerr << "Documentator : compileLateq : NO NICKNAMEPROPERTY" << endl;
			if (fLateq->outputs() == 1) {
				fLateq->addOutputSigFormula(subst("y(t) = $0", CS(sig, priority)));	
				gGlobal->gDocNoticeFlagMap["outputsig"] = true;
			} else {
				fLateq->addOutputSigFormula(subst("$0(t) = $1", getFreshID("y"), CS(sig, priority)));	
				gGlobal->gDocNoticeFlagMap["outputsigs"] = true;
			}
		}
	}
	return fLateq;
}



/*****************************************************************************
							 CS : compile a signal
*****************************************************************************/

/**
 * Test if a signal is already compiled
 * @param	sig		the signal expression to compile.
 * @param	name	the string representing the compiled expression.
 * @return	true	is already compiled
 */
bool DocCompiler::getCompiledExpression(Tree sig, string& cexp)
{
    return fCompileProperty.get(sig, cexp);
}


/**
 * Set the string of a compiled expression is already compiled
 * @param	sig		the signal expression to compile.
 * @param	cexp	the string representing the compiled expression.
 * @return	the cexp (for commodity)
 */
string DocCompiler::setCompiledExpression(Tree sig, const string& cexp)
{
    fCompileProperty.set(sig, cexp);
	return cexp;
}


/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */
string DocCompiler::CS (Tree sig, int priority)
{
    string code;

    if (!getCompiledExpression(sig, code)) { // not compiled yet.
        code = generateCode(sig, priority);
        setCompiledExpression(sig, code);
    }
    return code;
}



/*****************************************************************************
					generateCode : dispatch according to signal
*****************************************************************************/


/**
 * @brief Main code generator dispatch.
 *
 * According to the type of the input signal, generateCode calls
 * the appropriate generator with appropriate arguments.
 *
 * @param	sig			The signal expression to compile.
 * @param	priority	The environment priority of the expression.
 * @return	<string>	The LaTeX code translation of the signal.
 */
string DocCompiler::generateCode (Tree sig, int priority)
{
	int 	i;
	double	r;
    Tree 	c, sel, x, y, z, u, label, ff, largs, type, name, file;
	
	if ( getUserData(sig) )							{ printGCCall(sig,"generateXtended");	return generateXtended	(sig, priority);		}
	else if ( isSigInt(sig, &i) ) 					{ printGCCall(sig,"generateNumber");	return generateNumber	(sig, docT(i));			}
	else if ( isSigReal(sig, &r) ) 					{ printGCCall(sig,"generateNumber");	return generateNumber	(sig, docT(r));			}
	else if ( isSigInput(sig, &i) ) 				{ printGCCall(sig,"generateInput");		return generateInput	(sig, docT(i+1)); 		}
	else if ( isSigOutput(sig, &i, x) ) 			{ printGCCall(sig,"generateOutput");	return generateOutput	(sig, docT(i+1), CS(x, priority));	}
	
	else if ( isSigFixDelay(sig, x, y) ) 			{ printGCCall(sig,"generateFixDelay");	return generateFixDelay	(sig, x, y, priority); 	}
	else if ( isSigPrefix(sig, x, y) ) 				{ printGCCall(sig,"generatePrefix");	return generatePrefix	(sig, x, y, priority); 	}
	else if ( isSigIota(sig, x) ) 					{ printGCCall(sig,"generateIota");		return generateIota 	(sig, x); 				}
	
	else if ( isSigBinOp(sig, &i, x, y) )			{ printGCCall(sig,"generateBinOp");		return generateBinOp	(sig, i, x, y, priority); 		}
	else if ( isSigFFun(sig, ff, largs) )			{ printGCCall(sig,"generateFFun");		return generateFFun 	(sig, ff, largs, priority); 	}
    else if ( isSigFConst(sig, type, name, file) )  { printGCCall(sig,"generateFConst");	return generateFConst	(sig, tree2str(file), tree2str(name)); }
    else if ( isSigFVar(sig, type, name, file) )    { printGCCall(sig,"generateFVar");		return generateFVar		(sig, tree2str(file), tree2str(name)); }
	
    // new special tables for documentation purposes

    else if ( isSigDocConstantTbl(sig, x, y) )      { printGCCall(sig,"generateDocConstantTbl");    return generateDocConstantTbl (sig, x, y);	}
    else if ( isSigDocWriteTbl(sig,x,y,z,u) )       { printGCCall(sig,"generateDocWriteTbl");       return generateDocWriteTbl (sig, x, y, z, u); }
    else if ( isSigDocAccessTbl(sig, x, y) )        { printGCCall(sig, "generateDocAccessTbl");     return generateDocAccessTbl(sig, x, y); }


	else if ( isSigSelect2(sig, sel, x, y) ) 		{ printGCCall(sig,"generateSelect2");	return generateSelect2 	(sig, sel, x, y, priority); 	}
	else if ( isSigSelect3(sig, sel, x, y, z) ) 	{ printGCCall(sig,"generateSelect3");	return generateSelect3 	(sig, sel, x, y, z, priority); 	}
	
    else if ( isProj(sig, &i, x) )                  { printGCCall(sig,"generateRecProj");	return generateRecProj	(sig, x, i, priority);	}
	
	else if ( isSigIntCast(sig, x) ) 				{ printGCCall(sig,"generateIntCast");	return generateIntCast	(sig, x, priority); 	}
	else if ( isSigFloatCast(sig, x) ) 				{ printGCCall(sig,"generateFloatCast");	return generateFloatCast(sig, x, priority); 	}
	
	else if ( isSigButton(sig, label) ) 			{ printGCCall(sig,"generateButton");	return generateButton   (sig, label); 			}
	else if ( isSigCheckbox(sig, label) ) 			{ printGCCall(sig,"generateCheckbox");	return generateCheckbox (sig, label); 			}
	else if ( isSigVSlider(sig, label,c,x,y,z) )	{ printGCCall(sig,"generateVSlider");	return generateVSlider 	(sig, label, c,x,y,z);	}
	else if ( isSigHSlider(sig, label,c,x,y,z) )	{ printGCCall(sig,"generateHSlider");	return generateHSlider 	(sig, label, c,x,y,z);	}
	else if ( isSigNumEntry(sig, label,c,x,y,z) )	{ printGCCall(sig,"generateNumEntry");	return generateNumEntry (sig, label, c,x,y,z);	}
	
	else if ( isSigVBargraph(sig, label,x,y,z) )	{ printGCCall(sig,"generateVBargraph");	return CS(z, priority);}//generateVBargraph 	(sig, label, x, y, CS(z, priority)); }
	else if ( isSigHBargraph(sig, label,x,y,z) )	{ printGCCall(sig,"generateHBargraph");	return CS(z, priority);}//generateHBargraph 	(sig, label, x, y, CS(z, priority)); }
    else if ( isSigAttach(sig, x, y) )				{ printGCCall(sig,"generateAttach");	return generateAttach	(sig, x, y, priority); }
    else if ( isSigEnable(sig, x, y) )				{ printGCCall(sig,"generateEnable");      return generateEnable	(sig, x, y, priority); }

	else {
        stringstream error;
        error << "Error in d signal, unrecognized signal : " << *sig << endl;
        throw faustexception(error.str());
	}
    faustassert(0);
	return "error in generate code";
}


/**
 * Print calling information of generateCode, for debug purposes.
 *
 * @remark
 * To turn printing on, turn the 'printCalls' boolean to true.
 */
void DocCompiler::printGCCall(Tree sig, const string& calledFunction)
{
	bool printCalls	= false;
	bool maskSigs	= false;
	
	if(printCalls) {
		cerr << "  -> generateCode calls " << calledFunction;
		if(maskSigs) {
			cerr << endl;
		} else {
			cerr << " on " << ppsig(sig) << endl;
		}
	}
}


/*****************************************************************************
							   NUMBERS
*****************************************************************************/


string DocCompiler::generateNumber (Tree sig, const string& exp)
{
	string		ctype, vname;
    Occurences* o = fOccMarkup.retrieve(sig);

	// check for number occuring in delays
	if (o->getMaxDelay()>0) {
		getTypedNames(getCertifiedSigType(sig), "r", ctype, vname);
		gGlobal->gDocNoticeFlagMap["recursigs"] = true;
		//cerr << "- r : generateNumber : \"" << vname << "\"" << endl;            
		generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
	}
	return exp;
}

/*****************************************************************************
                               FOREIGN CONSTANTS
*****************************************************************************/


string DocCompiler::generateFConst (Tree sig, const string& file, const string& exp)
{
    string      ctype, vname;
    Occurences* o = fOccMarkup.retrieve(sig);

    if (o->getMaxDelay()>0) {
        getTypedNames(getCertifiedSigType(sig), "r", ctype, vname);
		gGlobal->gDocNoticeFlagMap["recursigs"] = true;
		//cerr << "- r : generateFConst : \"" << vname << "\"" << endl;            
        generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
    }
	
	if (exp == "fSamplingFreq") {
		//gGlobal->gDocNoticeFlagMap["fsamp"] = true;
		return "f_S";
	}
	
    return "\\mathrm{"+exp+"}";
}

/*****************************************************************************
                               FOREIGN VARIABLES
*****************************************************************************/


string DocCompiler::generateFVar (Tree sig, const string& file, const string& exp)
{
    string      ctype, vname;
    Occurences* o = fOccMarkup.retrieve(sig);

    if (o->getMaxDelay()>0) {
        getTypedNames(getCertifiedSigType(sig), "r", ctype, vname);
		gGlobal->gDocNoticeFlagMap["recursigs"] = true;
		//cerr << "- r : generateFVar : \"" << vname << "\"" << endl;            
		setVectorNameProperty(sig, vname);
        generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
    }
    return generateCacheCode(sig, exp);
}


/*****************************************************************************
							   INPUTS - OUTPUTS
*****************************************************************************/


string DocCompiler::generateInput (Tree sig, const string& idx)
{
	if (fLateq->inputs() == 1) {
		setVectorNameProperty(sig, "x");
		fLateq->addInputSigFormula("x(t)");	
		gGlobal->gDocNoticeFlagMap["inputsig"] = true;
		return generateCacheCode(sig, "x(t)");
	} else {
		setVectorNameProperty(sig, subst("x_{$0}", idx));
		fLateq->addInputSigFormula(subst("x_{$0}(t)", idx));
		gGlobal->gDocNoticeFlagMap["inputsigs"] = true;
		return generateCacheCode(sig, subst("x_{$0}(t)", idx));
	}
}


/** Unused for the moment ! */
string DocCompiler::generateOutput (Tree sig, const string& idx, const string& arg)
{
	string dst;
	
	if (fLateq->outputs() == 1) {
		dst = subst("y(t)", idx);
		gGlobal->gDocNoticeFlagMap["outputsig"] = true;
	} else {
		dst = subst("y_{$0}(t)", idx);
		gGlobal->gDocNoticeFlagMap["outputsigs"] = true;
	}
	
	fLateq->addOutputSigFormula(subst("$0 = $1", dst, arg));
	return dst;
}


/*****************************************************************************
							   BINARY OPERATION
*****************************************************************************/

/**
 * Generate binary operations, managing priority parenthesis.
 * ((a*b)+c) can be written (a*b+c) if priority(*) > priority(+)
 * ((a*b)*c) can be writteb (a*b*c) if * is associative
 * Associative operation should have a distinc priority from other operations.
 * Non associative operations can share the same priority.
 *
 * @param	sig			The signal expression to treat.
 * @param	opcode		The operation code, as described in gBinOpLateqTable.
 * @param	arg1		The first operand.
 * @param	arg2		The second operand.
 * @param	priority	The priority of the environment of the expression.
 *
 * @return	<string>	The LaTeX code translation of the signal, cached.
 *
 * @remark	The case of LaTeX frac{}{} is special.
 *
 * @todo	Handle integer arithmetics, by testing arguments type,
 * and printing dedicated operators (\oplus, \odot, \ominus, \oslash).
 */

/// associative operations are + * | & xor
static bool associative (int opcode) {
    return (opcode == kAdd) || (opcode == kMul) || (opcode == kAND) || (opcode == kOR) || (opcode == kXOR);
}

string DocCompiler::generateEnable(Tree sig, Tree arg1, Tree arg2, int priority)
{
    return generateBinOp(sig, kMul, arg1, arg2, priority);
}

string DocCompiler::generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2, int priority)
{
	string s;
	int thisPriority = gBinOpLateqTable[opcode]->fPriority;
	
	/* Priority parenthesis handling. */
	string lpar = "";
	string rpar = "";
    if ( (thisPriority < priority) || ((thisPriority == priority) && !associative(opcode)) ) {
        // (a+b)*c or (a/b)/c need parenthesis
        lpar = " \\left(";
        rpar = "\\right) ";
    }
	
	Type t1 = getCertifiedSigType(arg1);
	Type t2 = getCertifiedSigType(arg2);
	bool intOpDetected = false;
	if ( (t1->nature() == kInt) && (t2->nature() == kInt) ) {
		intOpDetected = true;
	}
	
	string op;
	if(!intOpDetected) {
		op = gBinOpLateqTable[opcode]->fName;
	} else {
		switch (opcode) {
			case kAdd:
				op = "\\oplus";
				gGlobal->gDocNoticeFlagMap["intplus"] = true;
				break;
			case kSub:
				op = "\\ominus";
				gGlobal->gDocNoticeFlagMap["intminus"] = true;
				break;
			case kMul:
				op = "\\odot";
				gGlobal->gDocNoticeFlagMap["intmult"] = true;
				break;
			case kDiv:
				op = "\\oslash";
				gGlobal->gDocNoticeFlagMap["intdiv"] = true;
				gGlobal->gDocNoticeFlagMap["intcast"] = true; // "$normalize(int(i/j))$" in the notice.
				break;
			default:
				op = gBinOpLateqTable[opcode]->fName;
				break;
		}
	}
	
	/* LaTeX frac{}{} handling VS general case. */
	if ( (opcode == kDiv) && (!intOpDetected) ) { 
		s = subst("$0\\frac{$1}{$2}$3", lpar, CS(arg1, 0), CS(arg2, 0), rpar);
	} else {
		s = subst("$0$1 $2 $3$4", lpar, CS(arg1, thisPriority), op, CS(arg2, thisPriority), rpar);
	}
	
//	if (opcode == kMul) {
//		gGlobal->gDocNoticeFlagMap["cdot"] = true;
//	}
	
	return generateCacheCode(sig, s);
}


/*****************************************************************************
							   Primitive Operations
*****************************************************************************/

string DocCompiler::generateFFun(Tree sig, Tree ff, Tree largs, int priority)
{
    string code = ffname(ff);
    code += '(';
    string sep = "";
    for (int i = 0; i< ffarity(ff); i++) {
        code += sep;
        code += CS(nth(largs, i), priority);
        sep = ", ";
    }
    code += ')';
	
	gGlobal->gDocNoticeFlagMap["foreignfun"] = true;

    return "\\mathrm{ff"+code+"}";
}


/*****************************************************************************
							   CACHE CODE
*****************************************************************************/

void DocCompiler::getTypedNames(Type t, const string& prefix, string& ctype, string& vname)
{
    if (t->nature() == kInt) {
        ctype = "int"; vname = subst("$0", getFreshID(prefix));
    } else {
        ctype = ifloat(); vname = subst("$0", getFreshID(prefix));
    }
}


/**
 * Test if exp is very simple that is it
 * can't be considered a real component
 * @param exp the signal we want to test
 * @return true if it a very simple signal
 */
static bool isVerySimpleFormula(Tree sig)
{
	int		i;
	double	r;
	Tree 	type, name, file, label, c, x, y, z;
	
	return 	isSigInt(sig, &i) 
	|| 	isSigReal(sig, &r)
	||	isSigInput(sig, &i)
	||	isSigFConst(sig, type, name, file)
	||	isSigButton(sig, label)
	||	isSigCheckbox(sig, label)
	||	isSigVSlider(sig, label,c,x,y,z)
	||	isSigHSlider(sig, label,c,x,y,z)
	||	isSigNumEntry(sig, label,c,x,y,z)
	;
}


string DocCompiler::generateCacheCode(Tree sig, const string& exp)
{
	//cerr << "!! entering generateCacheCode with sig=\"" << ppsig(sig) << "\"" << endl;	
	
	string vname, ctype, code, vectorname;
	
	int sharing = getSharingCount(sig);
    Occurences* o = fOccMarkup.retrieve(sig);
	
	// check reentrance
    if (getCompiledExpression(sig, code)) {
		//cerr << "!! generateCacheCode called a true getCompiledExpression" << endl;
        return code;
    }
	
	// check for expression occuring in delays
	if (o->getMaxDelay()>0) {
        if (getVectorNameProperty(sig, vectorname)) {
			return exp;
		}
        getTypedNames(getCertifiedSigType(sig), "r", ctype, vname);
		gGlobal->gDocNoticeFlagMap["recursigs"] = true;
		//cerr << "- r : generateCacheCode : vame=\"" << vname << "\", for sig=\"" << ppsig(sig) << "\"" << endl;
        if (sharing>1) {
			//cerr << "      generateCacheCode calls generateDelayVec(generateVariableStore) on vame=\"" << vname << "\"" << endl;            
            return generateDelayVec(sig, generateVariableStore(sig,exp), ctype, vname, o->getMaxDelay());
        } else {
			//cerr << "      generateCacheCode calls generateDelayVec(exp) on vame=\"" << vname << "\"" << endl;            
		    return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
        }
	} 
	else if (sharing == 1 || getVectorNameProperty(sig, vectorname) || isVerySimpleFormula(sig)) {
		//cerr << "! generateCacheCode : sharing == 1 : return \"" << exp << "\"" << endl;
        return exp;
	} 
	else if (sharing > 1) {
		//cerr << "! generateCacheCode : sharing > 1 : return \"" << exp << "\"" << endl;
        return generateVariableStore(sig, exp);
	} 
	else {
        stringstream error;
        error << "Error in sharing count (" << sharing << ") for " << *sig << endl;
        throw faustexception(error.str());
	}
	
	return "Error in generateCacheCode";
}


string DocCompiler::generateVariableStore(Tree sig, const string& exp)
{
    string vname, ctype;
    Type t = getCertifiedSigType(sig);
	
    switch (t->variability()) {
			
        case kKonst :
            getTypedNames(t, "k", ctype, vname); ///< "k" for constants.
            fLateq->addConstSigFormula(subst("$0 = $1", vname, exp));
			gGlobal->gDocNoticeFlagMap["constsigs"] = true;
			return vname;
			
        case kBlock :
            getTypedNames(t, "p", ctype, vname); ///< "p" for "parameter".
            fLateq->addParamSigFormula(subst("$0(t) = $1", vname, exp));
			gGlobal->gDocNoticeFlagMap["paramsigs"] = true;
			setVectorNameProperty(sig, vname);
			return subst("$0(t)", vname);
			
        case kSamp :
			if(getVectorNameProperty(sig, vname)) {
				return subst("$0(t)", vname);
			} else {
				getTypedNames(t, "s", ctype, vname);
				//cerr << "- generateVariableStore : \"" << subst("$0(t) = $1", vname, exp) << "\"" << endl;
				fLateq->addStoreSigFormula(subst("$0(t) = $1", vname, exp));
				gGlobal->gDocNoticeFlagMap["storedsigs"] = true;
				setVectorNameProperty(sig, vname);
				return subst("$0(t)", vname);
			}
			
		default:
			faustassert(0);
			return "";
    }
}


/*****************************************************************************
							   	    CASTING
*****************************************************************************/


string DocCompiler::generateIntCast(Tree sig, Tree x, int priority)
{
	gGlobal->gDocNoticeFlagMap["intcast"] = true;
			 
	return generateCacheCode(sig, subst("\\mathrm{int}\\left($0\\right)", CS(x, 0)));
}


/**
 * @brief Don't generate float cast !
 *
 * It is just a kind of redirection.
 * Calling generateCacheCode ensures to create a new 
 * variable name if the input signal expression is shared.
 */
string DocCompiler::generateFloatCast (Tree sig, Tree x, int priority)
{
	return generateCacheCode(sig, subst("$0", CS(x, priority)));
}


/*****************************************************************************
							user interface elements
*****************************************************************************/

string DocCompiler::generateButton(Tree sig, Tree path)
{
	string vname = getFreshID("{u_b}");
	string varname = vname + "(t)";
	fLateq->addUISigFormula(getUIDir(path), prepareBinaryUI(varname, path));
	gGlobal->gDocNoticeFlagMap["buttonsigs"] = true;
	return generateCacheCode(sig, varname);
}

string DocCompiler::generateCheckbox(Tree sig, Tree path)
{
	string vname = getFreshID("{u_c}");
	string varname = vname + "(t)";
	fLateq->addUISigFormula(getUIDir(path), prepareBinaryUI(varname, path));
	gGlobal->gDocNoticeFlagMap["checkboxsigs"] = true;
	return generateCacheCode(sig, varname);
}

string DocCompiler::generateVSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("{u_s}") + "(t)";
	fLateq->addUISigFormula(getUIDir(path), prepareIntervallicUI(varname, path, cur, min, max));
	gGlobal->gDocNoticeFlagMap["slidersigs"] = true;
	return generateCacheCode(sig, varname);
}

string DocCompiler::generateHSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("{u_s}") + "(t)";
	fLateq->addUISigFormula(getUIDir(path), prepareIntervallicUI(varname, path, cur, min, max));
	gGlobal->gDocNoticeFlagMap["slidersigs"] = true;
	return generateCacheCode(sig, varname);
}

string DocCompiler::generateNumEntry(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("{u_n}") + "(t)";		
	fLateq->addUISigFormula(getUIDir(path), prepareIntervallicUI(varname, path, cur, min, max));
	gGlobal->gDocNoticeFlagMap["nentrysigs"] = true;
	return generateCacheCode(sig, varname);
}

string DocCompiler::generateVBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
	string varname = getFreshID("{u_g}");

	Type t = getCertifiedSigType(sig);
	switch (t->variability()) {

		case kKonst :
			break;

		case kBlock :
			break;

		case kSamp :
			break;
	}
    return generateCacheCode(sig, varname);
}

string DocCompiler::generateHBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
	string varname = getFreshID("{u_g}");

	Type t = getCertifiedSigType(sig);
	switch (t->variability()) {

		case kKonst :
			break;

		case kBlock :
			break;

		case kSamp :
			break;
	}
    return generateCacheCode(sig, varname);
}

string DocCompiler::generateAttach (Tree sig, Tree x, Tree y, int priority)
{
    string vname;
    string exp;

    CS(y, priority);
    exp = CS(x, priority);

    if(getVectorNameProperty(x, vname)) {
        setVectorNameProperty(sig, vname);
    }

    return generateCacheCode(sig, exp);
}

/*****************************************************************************
							   	    TABLES
 (note : tables here are siplified versions different from the ones used to 
  generate c++ code)
*****************************************************************************/

/**
 * Generate the equation of a constant table (its content is time constant).
 * Returns the name of the table
 */
string DocCompiler::generateDocConstantTbl (Tree /*tbl*/, Tree size, Tree isig)
{	
	string 	vname, ctype;
    string 	init = CS(isig,0);

    int     n;
    if (!isSigInt(size, &n)) {
        cerr << "error in DocCompiler::generateDocConstantTbl() : "
             << *size
             << " is not an integer expression and can't be used as a table size' "
             << endl;
    }

    // allocate a name v_i for the table
    getTypedNames(getCertifiedSigType(isig), "v", ctype, vname);
	
    // add a comment on tables in the notice
    gGlobal->gDocNoticeFlagMap["tablesigs"] = true;
	
    // add equation v[t] = isig(t)
    fLateq->addRDTblSigFormula(subst("$0[t] = $1 \\condition{when $$t \\in [0,$2]$$} ", vname, init, T(n-1)));
	
    // note that the name of the table can never be used outside an sigDocTableAccess
    return vname;
}

/**
 * tests if a charactere is a word separator
 */
static bool isSeparator(char c)
{
    bool w = (  ((c >= 'a') && (c <='z'))
            ||  ((c >= 'A') && (c <='Z'))
            ||  ((c >= '0') && (c <='9'))
            );

    return ! w;
}

/**
 * Replaces the occurences of 't' in a formula with another character
 */
static string replaceTimeBy(const string& src, char r)
{
    string  dst;
    char    pre = 0;
    for (size_t i=0; i < src.size(); i++)
    {
        char x = src[i];
        if ((x=='t') && isSeparator(pre) && ((i == src.size()-1) || isSeparator(src[i+1]))) {
            dst.push_back(r);
        } else {
            dst.push_back(x);
        }
        pre = x;
    }
    return dst;
}

/**
 * Generate the equation of a write table, which content is time dependent.
 * It is basically a signal of vectors.
 */
string DocCompiler::generateDocWriteTbl (Tree /*tbl*/, Tree size, Tree isig, Tree widx, Tree wsig)
{
	string vname, ctype;
    string init = CS(isig,0);
    int n;
    if (!isSigInt(size, &n)) {
        cerr << "error in DocCompiler::generateDocWriteTbl() : "
             << *size
             << " is not an integer expression and can't be used as a table size' "
             << endl;
    }


    // allocate a name w_i for the table
    getTypedNames(getCertifiedSigType(isig), "w", ctype, vname);

    // add a comment on tables in the notice
    gGlobal->gDocNoticeFlagMap["tablesigs"] = true;

    // describe the table equation
    string ltqRWTableDef;
    ltqRWTableDef += subst("$0(t)[i] = \n", vname);
    ltqRWTableDef += "\\left\\{\\begin{array}{ll}\n";
    ltqRWTableDef += subst("$0 & \\mbox{if \\,} t < 0 \\mbox{\\, and \\,}  i \\in [0,$1] \\\\\n", 	replaceTimeBy(init,'i'), T(n-1));
    ltqRWTableDef += subst("$0 & \\mbox{if \\,} i = $1 \\\\\n", CS(wsig,0), CS(widx,0));
    ltqRWTableDef += subst("$0(t\\!-\\!1)[i] & \\mbox{otherwise} \\\\\n", vname);
    ltqRWTableDef += "\\end{array}\\right.";
		
    // add the table equation
		fLateq->addRWTblSigFormula(ltqRWTableDef); //w(t) = initsig(t)
	
    // note that the name of the table can never be used outside an sigDocTableAccess
    return vname;
}


/**
 * Generate the equation of a write table, which content is time dependent.
 * It is basically a signal of vectors.
 */
string DocCompiler::generateDocAccessTbl (Tree sig, Tree tbl, Tree ridx)
{
    // the compilation of a table always returns its name
    string	vname = CS(tbl, 0);
    string result = subst("$0[$1]", vname, CS(ridx,0) );

    return generateCacheCode(sig, result);
}

bool DocCompiler::isShortEnough(string& s, unsigned int max)
{	
	return (s.length() <= max);
}

/*****************************************************************************
							   RECURSIONS
*****************************************************************************/

/**
 * Generate code for a projection of a group of mutually recursive definitions
 */
string DocCompiler::generateRecProj(Tree sig, Tree r, int i, int priority)
{
    string vname;
    Tree var, le;
	
	//cerr << "*** generateRecProj sig : \"" << ppsig(sig) << "\"" << endl;            

    if ( ! getVectorNameProperty(sig, vname)) {
        faustassert(isRec(r, var, le));
		//cerr << "    generateRecProj has NOT YET a vname : " << endl;            
		//cerr << "--> generateRecProj calls generateRec on \"" << ppsig(sig) << "\"" << endl;            
        generateRec(r, var, le, priority);
        faustassert(getVectorNameProperty(sig, vname));
		//cerr << "<-- generateRecProj vname : \"" << subst("$0(t)", vname) << "\"" << endl;            
    } else {
		//cerr << "(generateRecProj has already a vname : \"" << subst("$0(t)", vname) << "\")" << endl;            
	}
    return subst("$0(t)", vname);
}

/**
 * Generate code for a group of mutually recursive definitions
 */
void DocCompiler::generateRec(Tree sig, Tree var, Tree le, int priority)
{
    int N = len(le);

    vector<bool> used(N);
    vector<int> delay(N);
    vector<string> vname(N);
    vector<string> ctype(N);

    // prepare each element of a recursive definition
    for (int i = 0; i < N; i++) {
        Tree e = sigProj(i,sig);     // recreate each recursive definition
        if (fOccMarkup.retrieve(e)) {
            // this projection is used
            used[i] = true;
			//cerr << "generateRec : used[" << i << "] = true" << endl;            
            getTypedNames(getCertifiedSigType(e), "r", ctype[i],  vname[i]);
			gGlobal->gDocNoticeFlagMap["recursigs"] = true;
			//cerr << "- r : generateRec setVectorNameProperty : \"" << vname[i] << "\"" << endl;
			setVectorNameProperty(e, vname[i]);
            delay[i] = fOccMarkup.retrieve(e)->getMaxDelay();
        } else {
            // this projection is not used therefore
            // we should not generate code for it
            used[i] = false;
			//cerr << "generateRec : used[" << i << "] = false" << endl;
        }
    }

    // generate delayline for each element of a recursive definition
    for (int i=0; i<N; i++) {
        if (used[i]) {
            generateDelayLine(ctype[i], vname[i], delay[i], CS(nth(le,i), priority));
        }
    }
}


/*****************************************************************************
							   PREFIX, DELAY A PREFIX VALUE
*****************************************************************************/

/**
 * Generate LaTeX code for "prefix", a 1­sample-delay explicitely initialized.
 *
 * @param	sig			The signal expression to treat.
 * @param	x			The initial value for the delay line.
 * @param	e			The value for the delay line, after initialization.
 * @param	priority	The priority of the environment of the expression.
 *
 * @return	<string>	The LaTeX code translation of the signal, cached.
 */
string DocCompiler::generatePrefix (Tree sig, Tree x, Tree e, int priority)
{
	string var  = getFreshID("m");
	string exp0 = CS(x, priority);
	string exp1 = CS(e, priority); // ensure exp1 is compiled to have a vector name
	string vecname;

	if (! getVectorNameProperty(e, vecname)) {
		cerr << "No vector name for : " << ppsig(e) << endl;
		faustassert(0);
	}
	
	string ltqPrefixDef;
	ltqPrefixDef += subst("$0(t) = \n", var);
	ltqPrefixDef += "\\left\\{\\begin{array}{ll}\n";
	ltqPrefixDef += subst("$0 & \\mbox{, when \\,} t = 0\\\\\n", exp0);
	ltqPrefixDef += subst("$0 & \\mbox{, when \\,} t > 0\n", subst("$0(t\\!-\\!1)", vecname));
	ltqPrefixDef += "\\end{array}\\right.";
	
	fLateq->addPrefixSigFormula(ltqPrefixDef);
	gGlobal->gDocNoticeFlagMap["prefixsigs"] = true;
	
	return generateCacheCode(sig, subst("$0(t)", var));
}


/*****************************************************************************
							   IOTA(n)
*****************************************************************************/

/**
 * Generate a "iota" time function, n-cyclical.
 */
string DocCompiler::generateIota (Tree sig, Tree n)
{
	int size;
	if (!isSigInt(n, &size)) { 
        throw faustexception("Error in generateIota\n");
    }
	//cout << "iota !" << endl;
	return subst(" t \\bmod{$0} ", docT(size));
}

// a revoir en utilisant la lecture de table et en partageant la construction de la paire de valeurs

/**
 * Generate a select2 code
 */
string DocCompiler::generateSelect2  (Tree sig, Tree sel, Tree s1, Tree s2, int priority)
{
    string var = getFreshID("q");
	string expsel = CS(sel, 0);
	string exps1 = CS(s1, 0);
	string exps2 = CS(s2, 0);
	
	string ltqSelDef;
	ltqSelDef += subst("$0(t) = \n", var);
	ltqSelDef += "\\left\\{\\begin{array}{ll}\n";
	ltqSelDef += subst("$0 & \\mbox{if \\,} $1 = 0\\\\\n", exps1, expsel);
	ltqSelDef += subst("$0 & \\mbox{if \\,} $1 = 1\n", exps2, expsel);
	ltqSelDef += "\\end{array}\\right.";
	
	fLateq->addSelectSigFormula(ltqSelDef);
	gGlobal->gDocNoticeFlagMap["selectionsigs"] = true;
	
    //return generateCacheCode(sig, subst("$0(t)", var));
    setVectorNameProperty(sig, var);
    return subst("$0(t)", var);
}

/**
 * Generate a select3 code
 */
string DocCompiler::generateSelect3  (Tree sig, Tree sel, Tree s1, Tree s2, Tree s3, int priority)
{
	string var  = getFreshID("q");
	string expsel = CS(sel, 0);
	string exps1 = CS(s1, 0);
	string exps2 = CS(s2, 0);
	string exps3 = CS(s3, 0);
	
	string ltqSelDef;
	ltqSelDef += subst("$0(t) = \n", var);
	ltqSelDef += "\\left\\{\\begin{array}{ll}\n";
	ltqSelDef += subst("$0 & \\mbox{if \\,} $1 = 0\\\\\n", generateVariableStore(s1, exps1), expsel);
	ltqSelDef += subst("$0 & \\mbox{if \\,} $1 = 1\\\\\n", generateVariableStore(s2, exps2), expsel);
	ltqSelDef += subst("$0 & \\mbox{if \\,} $1 = 2\n", generateVariableStore(s3, exps3), expsel);
	ltqSelDef += "\\end{array}\\right.";
	
	fLateq->addSelectSigFormula(ltqSelDef);
	gGlobal->gDocNoticeFlagMap["selectionsigs"] = true;
	
    //return generateCacheCode(sig, subst("$0(t)", var));
    setVectorNameProperty(sig, var);
    return subst("$0(t)", var);
}

/**
 * retrieve the type annotation of sig
 * @param sig the signal we want to know the type
 */
string DocCompiler::generateXtended 	(Tree sig, int priority)
{
	xtended* p = (xtended*) getUserData(sig);
	vector<string> args;
	vector<Type> types;

	for (int i=0; i<sig->arity(); i++) {
		args.push_back(CS(sig->branch(i), 0));
		types.push_back(getCertifiedSigType(sig->branch(i)));
	}

	if (p->needCache()) {
		//cerr << "!! generateXtended : <needCache> : calls generateCacheCode(sig, p->generateLateq(fLateq, args, types))" << endl;
		return generateCacheCode(sig, p->generateLateq(fLateq, args, types));
	} else {
		//cerr << "!! generateXtended : <do not needCache> : calls p->generateLateq(fLateq, args, types)" << endl;
		return p->generateLateq(fLateq, args, types);
	}
}

//------------------------------------------------------------------------------------------------

/*****************************************************************************
						vector name property
*****************************************************************************/

/**
 * Set the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vecname the string representing the vector name.
 * @return true is already compiled
 */
void DocCompiler::setVectorNameProperty(Tree sig, const string& vecname)
{
	fVectorProperty.set(sig, vecname);
}

/**
 * Get the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vecname the string where to store the vector name.
 * @return true if the signal has this property, false otherwise
 */

bool DocCompiler::getVectorNameProperty(Tree sig, string& vecname)
{
    return fVectorProperty.get(sig, vecname);
}

/*****************************************************************************
							   N-SAMPLE FIXED DELAY : sig = exp@delay

	case 1-sample max delay :
		Y(t-0)	Y(t-1)
		Temp	Var						gGlobal->gLessTempSwitch = false
		V[0]	V[1]					gGlobal->gLessTempSwitch = true

	case max delay < gGlobal->gMaxCopyDelay :
		Y(t-0)	Y(t-1)	Y(t-2)  ...
		Temp	V[0]	V[1]	...		gGlobal->gLessTempSwitch = false
		V[0]	V[1]	V[2]	...		gGlobal->gLessTempSwitch = true

	case max delay >= gGlobal->gMaxCopyDelay :
		Y(t-0)	Y(t-1)	Y(t-2)  ...
		Temp	V[0]	V[1]	...
		V[0]	V[1]	V[2]	...

*****************************************************************************/

/**
 * Generate code for accessing a delayed signal. The generated code depend of
 * the maximum delay attached to exp and the gGlobal->gLessTempSwitch.
 *
 * @todo Priorités à revoir pour le parenthésage (associativité de - et /),
 * avec gBinOpLateqTable dans binop.cpp.
 */
string DocCompiler::generateFixDelay (Tree sig, Tree exp, Tree delay, int priority)
{
	int d;
	string vecname;
	
	CS(exp, 0); // ensure exp is compiled to have a vector name
	
	if (! getVectorNameProperty(exp, vecname)) {
		cerr << "No vector name for : " << ppsig(exp) << endl;
		faustassert(0);
	}
	
	if (isSigInt(delay, &d) && (d == 0)) {
		//cerr << "@ generateFixDelay : d = " << d << endl;
		return subst("$0(t)", vecname);
	} else {
		//cerr << "@ generateFixDelay : d = " << d << endl;
		return subst("$0(t\\!-\\!$1)", vecname, CS(delay, 7));
	}
}

/**
 * Generate code for the delay mecchanism. The generated code depend of the
 * maximum delay attached to exp and the "less temporaries" switch
 */
string DocCompiler::generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd)
{
	string s = generateDelayVecNoTemp(sig, exp, ctype, vname, mxd);
	if (getCertifiedSigType(sig)->variability() < kSamp) {
        return exp;
	} else {
		return s;
	}
}

/**
 * Generate code for the delay mecchanism without using temporary variables
 */
string DocCompiler::generateDelayVecNoTemp(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd)
{
    faustassert(mxd > 0);
	//cerr << "  entering generateDelayVecNoTemp" << endl;
	string vectorname;

	// if generateVariableStore has already tagged sig, no definition is needed.
	if(getVectorNameProperty(sig, vectorname)) { 
		return subst("$0(t)", vectorname);
	} else {
        fLateq->addRecurSigFormula(subst("$0(t) = $1", vname, exp));
        setVectorNameProperty(sig, vname);
        return subst("$0(t)", vname);
	}
}

/**
 * Generate code for the delay mecchanism without using temporary variables
 */
void DocCompiler::generateDelayLine(const string& ctype, const string& vname, int mxd, const string& exp)
{
    //faustassert(mxd > 0);
    if (mxd == 0) {
        fLateq->addRecurSigFormula(subst("$0(t) = $1", vname, exp));
    } else {
        fLateq->addRecurSigFormula(subst("$0(t) = $1", vname, exp));
	}
}

/****************************************************************
			User interface element utilities.
 *****************************************************************/

/**
 * @brief Get the directory of a user interface element.
 *
 * Convert the input reversed path tree into a string.
 * The name of the UI is stripped (the head of the path tree), 
 * the rest of the tree is a list of pointed pairs, where the names 
 * are contained by the tail of these pointed pairs.
 * Metadatas (begining by '[') are stripped.
 * 
 * @param[in]	pathname	The path tree to convert.
 * @return		<string>	A directory-like string. 
 */
string DocCompiler::getUIDir(Tree pathname)
{	
	//cerr << "Documentator : getUIDir : print(pathname, stdout) = "; print(pathname, stdout); cerr << endl;
	string s;
	Tree dir = reverse(tl(pathname));
	while (!isNil(dir)) { 
		string tmp = tree2str(tl(hd(dir)));
		if ( (tmp[0] != '[') && (!tmp.empty()) ) {
			s += tmp + '/';
		}
		dir = tl(dir);
	}
	return s;
}

/**
 * @brief Prepare binary user interface elements (button, checkbox).
 *
 * - Format a LaTeX output string as a supertabular row with 3 columns :
 * "\begin{supertabular}{lll}". @see Lateq::printHierarchy
 * - The UI range is only a set of two values : {0, 1}.
 * - The UI current value is automatically 0.
 * 
 * @param[in]	name		The LaTeX name of the UI signal (eg. "{u_b}_{i}(t)").
 * @param[in]	path		The path tree to parse.
 * @return		<string>	The LaTeX output string. 
 */
string DocCompiler::prepareBinaryUI(const string& name, Tree path)
{	
	string label, unit;
	getUIDocInfos(path, label, unit);
	string s = "";
	label = (label.size()>0) ? ("\\textsf{\""+label+"\"} ") : "";
	unit = (unit.size()>0) ? ("\\ ("+unit+")") : "";
	s += label + unit;
	s += " & $" + name + "$";
	s += " $\\in$ $\\left\\{\\,0, 1\\,\\right\\}$";
	s += " & $(\\mbox{" + gGlobal->gDocMathStringMap["defaultvalue"] + "} = 0)$\\\\";
	return s;
}

/**
 * @brief Prepare "intervallic" user interface elements (sliders, nentry).
 *
 * - Format a LaTeX output string as a supertabular row with 3 columns :
 * "\begin{supertabular}{lll}". @see Lateq::printHierarchy
 * - The UI range is an bounded interval : [tmin, tmax].
 * - The UI current value is tcur.
 * 
 * @param[in]	name		The LaTeX name of the UI signal (eg. "{u_s}_{i}(t)").
 * @param[in]	path		The path tree to parse.
 * @param[in]	tcur		The current UI value tree to convert.
 * @param[in]	tmin		The minimum UI value tree to convert.
 * @param[in]	tmax		The maximum UI value tree to convert.
 * @return		<string>	The LaTeX output string. 
 */
string DocCompiler::prepareIntervallicUI(const string& name, Tree path, Tree tcur, Tree tmin, Tree tmax)
{	
	string label, unit, cur, min, max;
	getUIDocInfos(path, label, unit);
	cur = docT(tree2float(tcur));
	min = docT(tree2float(tmin));
	max = docT(tree2float(tmax));
	
	string s = "";
	label = (label.size()>0) ? ("\\textsf{\""+label+"\"} ") : "";
	unit = (unit.size()>0) ? ("\\ ("+unit+")") : "";
	s += label + unit;
	s += " & $" + name + "$";
	s += " $\\in$ $\\left[\\," + min + ", " + max + "\\,\\right]$";
	s += " & $(\\mbox{" + gGlobal->gDocMathStringMap["defaultvalue"] + "} = " + cur + ")$\\\\";
	return s;
}

/** 
 * Get information on a user interface element for documentation.
 *
 * @param[in]	path	The UI full pathname to parse.
 * @param[out]	label	The place to store the UI name. 
 * @param[out]	unit	The place to store the UI unit.
 */
void DocCompiler::getUIDocInfos(Tree path, string& label, string& unit)
{
	label = "";
	unit = "";
	
    map<string, set<string> >   metadata;
    extractMetadata(tree2str(hd(path)), label, metadata);
	
	set<string> myunits = metadata["unit"];
//	for (set<string>::iterator i = myunits.begin(); i != myunits.end(); i++) {
//		cerr << "Documentator : getUIDocInfos : metadata[\"unit\"] = " << *i << endl;
//	}
	for (map<string, set<string> >::iterator i = metadata.begin(); i != metadata.end(); i++) {
		const string& key = i->first;
		const set<string>& values = i->second;
		for (set<string>::const_iterator j = values.begin(); j != values.end(); j++) {
			if (key == "unit") unit += *j;
		}
	}
}

