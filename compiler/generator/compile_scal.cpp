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
*****************************************************************************/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include "compile_scal.hh"
#include "timing.hh"
#include "compile.hh"
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
#include "sigToGraph.hh"

using namespace std;

static Klass* signal2klass(Klass* parent, const string& name, Tree sig)
{
	Type t = getCertifiedSigType(sig); //, NULLENV);
	if (t->nature() == kInt) {

        ScalarCompiler C(new SigIntGenKlass(parent, name));
		C.compileSingleSignal(sig);
		return C.getClass();

	} else {

        ScalarCompiler C(new SigFloatGenKlass(parent, name));
		C.compileSingleSignal(sig);
		return C.getClass();

	}
}

/*****************************************************************************
						getFreshID
*****************************************************************************/

map<string, int> ScalarCompiler::fIDCounters;

string ScalarCompiler::getFreshID(const string& prefix)
{
	if (fIDCounters.find(prefix) == fIDCounters.end()) {
		fIDCounters[prefix]=0;
	}
	int n = fIDCounters[prefix];
	fIDCounters[prefix] = n+1;
	return subst("$0$1", prefix, T(n));
}

/*****************************************************************************
						    prepare
*****************************************************************************/

Tree ScalarCompiler::prepare(Tree LS)
{
    startTiming("ScalarCompiler::prepare");
    //  startTiming("first simplification");
    //  LS = simplify(LS);
    //  endTiming("first simplification");
    startTiming("deBruijn2Sym");
    Tree L1 = deBruijn2Sym(LS);   	// convert debruijn recursion into symbolic recursion
    endTiming("deBruijn2Sym");
    startTiming("second simplification");
    Tree L2 = simplify(L1);			// simplify by executing every computable operation
    endTiming("second simplification");
    Tree L3 = privatise(L2);		// Un-share tables with multiple writers

    conditionAnnotation(L3);
    //conditionStatistics(L3);        // count condition occurences

    // dump normal form
    if (gGlobal->gDumpNorm) {
        cout << ppsig(L3) << endl;
        throw faustexception("Dump normal form finished...\n");
    }

	recursivnessAnnotation(L3);		// Annotate L3 with recursivness information

    startTiming("typeAnnotation");
    typeAnnotation(L3);				// Annotate L3 with type information
    endTiming("typeAnnotation");

    sharingAnalysis(L3);			// annotate L3 with sharing count

    if (fOccMarkup != 0) { delete fOccMarkup; }
    fOccMarkup = new old_OccMarkup(fConditionProperty);
    fOccMarkup->mark(L3);			// annotate L3 with occurences analysis

    endTiming("ScalarCompiler::prepare");

    if (gGlobal->gDrawSignals) {
        ofstream dotfile(subst("$0-sig.dot", gGlobal->makeDrawPath()).c_str());
        // SL : 28/09/17 : deactivated for now
        //sigToGraph(L3, dotfile);
    }

  	return L3;
}

Tree ScalarCompiler::prepare2(Tree L0)
{
    startTiming("ScalarCompiler::prepare2");
	recursivnessAnnotation(L0);		// Annotate L0 with recursivness information
	typeAnnotation(L0);				// Annotate L0 with type information
    sharingAnalysis(L0);			// annotate L0 with sharing count

    if (fOccMarkup != 0) { delete fOccMarkup; }
    fOccMarkup = new old_OccMarkup();
    fOccMarkup->mark(L0);			// annotate L0 with occurences analysis

    endTiming("ScalarCompiler::prepare2");

  	return L0;
}

/*****************************************************************************
						    compileMultiSignal
*****************************************************************************/

string ScalarCompiler::dnf2code(Tree cc)
{
    if (cc == gGlobal->nil) return "";
    Tree c1 = hd(cc); cc = tl(cc);
    if (cc == gGlobal->nil) {
        return and2code(c1);
    } else {
        return subst("$0 || $1", and2code(c1), dnf2code(cc));
    }
}

string ScalarCompiler::and2code(Tree cs)
{
    if (cs == gGlobal->nil) return "";
    Tree c1 = hd(cs); cs = tl(cs);
    if (cs == gGlobal->nil) {
        return CS(c1);
    } else {
        return subst("$0 && $1", CS(c1), and2code(cs));
    }
}

string ScalarCompiler::cnf2code(Tree cs)
{
    if (cs == gGlobal->nil) return "";
    Tree c1 = hd(cs); cs = tl(cs);
    if (cs == gGlobal->nil) {
        return or2code(c1);
    } else {
        return subst("($0) && $1", or2code(c1), cnf2code(cs));
    }
}

string ScalarCompiler::or2code(Tree cs)
{
    if (cs == gGlobal->nil) return "";
    Tree c1 = hd(cs); cs = tl(cs);
    if (cs == gGlobal->nil) {
        return CS(c1);
    } else {
        return subst("$0 || $1", CS(c1), or2code(cs));
    }
}

#if _DNF_
#define CND2CODE dnf2code
#else
#define CND2CODE cnf2code
#endif

// temporary implementation for test purposes
string ScalarCompiler::getConditionCode(Tree sig)
{
    Tree cc = fConditionProperty[sig];
    if ((cc != 0) && (cc != gGlobal->nil)) {
        return CND2CODE(cc);
    } else {
        return "";
    }
}

void ScalarCompiler::compileMultiSignal(Tree L)
{
	//contextor recursivness(0);
	L = prepare(L);		// optimize, share and annotate expression

    for (int i = 0; i < fClass->inputs(); i++) {
        fClass->addZone3(subst("$1* input$0 = input[$0];", T(i), xfloat()));
        if (gGlobal->gInPlace) {
        	CS(sigInput(i));
        }
    }
    for (int i = 0; i < fClass->outputs(); i++) {
        fClass->addZone3(subst("$1* output$0 = output[$0];", T(i), xfloat()));
    }

	for (int i = 0; isList(L); L = tl(L), i++) {
		Tree sig = hd(L);
        fClass->addExecCode(Statement("", subst("output$0[i] = $2$1;", T(i), generateCacheCode(sig, CS(sig)), xcast())));
	}

    generateMetaData();
	generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot), true);
	generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
	if (fDescription) {
		fDescription->ui(prepareUserInterfaceTree(fUIRoot));
	}

    if (gGlobal->gPrintJSONSwitch) {
        ofstream xout(subst("$0.json", gGlobal->makeDrawPath()).c_str());
        xout << fJSON.JSON();
    }
}

/*****************************************************************************
						    compileSingleSignal
*****************************************************************************/

void ScalarCompiler::compileSingleSignal(Tree sig)
{
	//contextor recursivness(0);
	sig = prepare2(sig);		// optimize and annotate expression
    fClass->addExecCode(Statement("", subst("output[i] = $0;", CS(sig))));
	generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot), true);
	generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
	if (fDescription) {
		fDescription->ui(prepareUserInterfaceTree(fUIRoot));
	}
}

/*****************************************************************************
							 CS : compile a signal
*****************************************************************************/

/**
 * Test if a signal is already compiled
 * @param sig the signal expression to compile.
 * @param name the string representing the compiled expression.
 * @return true is already compiled
 */
bool ScalarCompiler::getCompiledExpression(Tree sig, string& cexp)
{
    return fCompileProperty.get(sig, cexp);
}

/**
 * Set the string of a compiled expression is already compiled
 * @param sig the signal expression to compile.
 * @param cexp the string representing the compiled expression.
 * @return the cexp (for commodity)
 */
string ScalarCompiler::setCompiledExpression(Tree sig, const string& cexp)
{
    //cerr << "ScalarCompiler::setCompiledExpression : " << cexp << " ==> " << ppsig(sig) << endl;
    string old;
    if (fCompileProperty.get(sig, old) && (old != cexp)) {
        //cerr << "ERROR already a compiled expression attached : " << old << " replaced by " << cexp << endl;
        //exit(1);
    }
    fCompileProperty.set(sig, cexp);
	return cexp;
}

/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */
string ScalarCompiler::CS(Tree sig)
{
    //contextor contextRecursivness;
    string code;

    if (!getCompiledExpression(sig, code)) {
        // not compiled yet
        /*
        if (getRecursivness(sig) != contextRecursivness.get()) {
            contextRecursivness.set(getRecursivness(sig));
        }
        */
        code = generateCode(sig);
        setCompiledExpression(sig, code);
    }
    return code;
}

/*****************************************************************************
						generateCode : dispatch according to signal
*****************************************************************************/
/**
 * Main code generator dispatch.
 * @param sig the signal expression to compile.
 * @return the C code translation of sig
 */

string ScalarCompiler::generateCode(Tree sig)
{
#if 0
	fprintf(stderr, "CALL generateCode(");
    printSignal(sig, stderr);
	fprintf(stderr, ")\n");
#endif

	int i;
	double r;
    Tree c, sel, x, y, z, label, id, ff, largs, type, name, file, sf;

	//printf("compilation of %p : ", sig); print(sig); printf("\n");

		 if ( getUserData(sig) ) 					{ return generateXtended(sig); }
	else if ( isSigInt(sig, &i) ) 					{ return generateNumber(sig, T(i)); }
	else if ( isSigReal(sig, &r) ) 					{ return generateNumber(sig, T(r)); }
    else if ( isSigWaveform(sig) )                  { return generateWaveform(sig); }
	else if ( isSigInput(sig, &i) ) 				{ return generateInput(sig, T(i)); }
	else if ( isSigOutput(sig, &i, x) ) 			{ return generateOutput(sig, T(i), CS(x));}

	else if ( isSigFixDelay(sig, x, y) ) 			{ return generateFixDelay(sig, x, y); }
	else if ( isSigPrefix(sig, x, y) ) 				{ return generatePrefix(sig, x, y); }
	else if ( isSigIota(sig, x) ) 					{ return generateIota(sig, x); }

	else if ( isSigBinOp(sig, &i, x, y) )			{ return generateBinOp(sig, i, x, y); }
	else if ( isSigFFun(sig, ff, largs) )			{ return generateFFun (sig, ff, largs); }
    else if ( isSigFConst(sig, type, name, file) )  { return generateFConst(sig, tree2str(file), tree2str(name));}
    else if ( isSigFVar(sig, type, name, file) )    { return generateFVar(sig, tree2str(file), tree2str(name)); }

	else if ( isSigTable(sig, id, x, y) ) 			{ return generateTable(sig, x, y); }
	else if ( isSigWRTbl(sig, id, x, y, z) )		{ return generateWRTbl(sig, x, y, z); }
	else if ( isSigRDTbl(sig, x, y) ) 				{ return generateRDTbl(sig, x, y); }

	else if ( isSigSelect2(sig, sel, x, y) ) 		{ return generateSelect2(sig, sel, x, y); }
	else if ( isSigSelect3(sig, sel, x, y, z) ) 	{ return generateSelect3(sig, sel, x, y, z); }

	else if ( isSigGen(sig, x) ) 					{ return generateSigGen(sig, x); }

    else if ( isProj(sig, &i, x) )                  { return generateRecProj(sig, x, i); }

	else if ( isSigIntCast(sig, x) ) 				{ return generateIntCast(sig, x); }
	else if ( isSigFloatCast(sig, x) ) 				{ return generateFloatCast(sig, x); }

	else if ( isSigButton(sig, label) ) 			{ return generateButton(sig, label); }
	else if ( isSigCheckbox(sig, label) ) 			{ return generateCheckbox(sig, label); }
	else if ( isSigVSlider(sig, label,c,x,y,z) )	{ return generateVSlider(sig, label, c,x,y,z); }
	else if ( isSigHSlider(sig, label,c,x,y,z) )	{ return generateHSlider(sig, label, c,x,y,z); }
	else if ( isSigNumEntry(sig, label,c,x,y,z) )	{ return generateNumEntry(sig, label, c,x,y,z); }

	else if ( isSigVBargraph(sig, label,x,y,z) )	{ return generateVBargraph(sig, label, x, y, CS(z)); }
	else if ( isSigHBargraph(sig, label,x,y,z) )	{ return generateHBargraph(sig, label, x, y, CS(z)); }

	else if ( isSigSoundfile(sig, label) )	        { return generateSoundfile(sig, label); }
	else if ( isSigSoundfileLength(sig, sf) )	    { return generateCacheCode(sig, subst("$0cache->fLength", CS(sf))); }
	else if ( isSigSoundfileRate(sig, sf) )	        { return generateCacheCode(sig, subst("$0cache->fSampleRate", CS(sf))); }
    else if ( isSigSoundfileChannels(sig, sf) )     { return generateCacheCode(sig, subst("$0cache->fChannels", CS(sf))); }
    else if ( isSigSoundfileBuffer(sig,sf,x,y))     { return generateCacheCode(sig, subst("$0cache->fBuffers[$1][$2]", CS(sf), CS(x), CS(y))); }

	else if ( isSigAttach(sig, x, y) )				{ CS(y); return generateCacheCode(sig, CS(x)); }
    else if ( isSigEnable(sig, x, y) )				{ return generateEnable(sig, x, y); }
    /* we should not have any control at this stage*/
	else {
        stringstream error;
        error << "ERROR when compiling, unrecognized signal : " << ppsig(sig) << endl;
        throw faustexception(error.str());
	}
	return "error in generate code";
}

/*****************************************************************************
							   NUMBERS
*****************************************************************************/

string ScalarCompiler::generateNumber(Tree sig, const string& exp)
{
	string ctype, vname;
    old_Occurences* o = fOccMarkup->retrieve(sig);

	// check for number occuring in delays
	if (o->getMaxDelay()>0) {
		getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
		generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
	}
	return exp;
}

/*****************************************************************************
                               FOREIGN CONSTANTS
*****************************************************************************/

string ScalarCompiler::generateFConst(Tree sig, const string& file, const string& exp)
{
    string ctype, vname;
    old_Occurences* o = fOccMarkup->retrieve(sig);

    addIncludeFile(file);

    if (o->getMaxDelay()>0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
    }
    return exp;
}

/*****************************************************************************
                               FOREIGN VARIABLES
*****************************************************************************/

string ScalarCompiler::generateFVar(Tree sig, const string& file, const string& exp)
{
    string ctype, vname;

    addIncludeFile(file);
    return generateCacheCode(sig, exp);
}

/*****************************************************************************
							   INPUTS - OUTPUTS
*****************************************************************************/

string ScalarCompiler::generateInput(Tree sig, const string& idx)
{
    if (gGlobal->gInPlace) {
        // inputs must be cached for in-place transformations
        return forceCacheCode(sig, subst("$1input$0[i]", idx, icast()));
    } else {
        return generateCacheCode(sig, subst("$1input$0[i]", idx, icast()));
    }
}

string ScalarCompiler::generateOutput(Tree sig, const string& idx, const string& arg)
{
	string dst = subst("output$0[i]", idx);
    fClass->addExecCode(Statement("", subst("$0 = $2$1;", dst, arg, xcast())));
	return dst;
}

/*****************************************************************************
							   BINARY OPERATION
*****************************************************************************/

string ScalarCompiler::generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2)
{
    if (opcode == kDiv) {
        // special handling for division, we always want a float division
        Type t1 = getCertifiedSigType(arg1);
        Type t2 = getCertifiedSigType(arg2);

        interval j = t2->getInterval();

        if (j.haszero()) {
            // potential division by zero
            // interval    i = t1->getInterval();
            //std::cerr << "WARNING : potential division by zero (" << i << "/" << j << ") in " << ppsig(sig) << std::endl;
        }

        if (t1->nature()==kInt && t2->nature()==kInt ) {
            return generateCacheCode(sig, subst("($3($0) $1 $3($2))", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2), ifloat()));
        } else if (t1->nature()==kInt && t2->nature()==kReal ) {
            return generateCacheCode(sig, subst("($3($0) $1 $2)", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2), ifloat()));
        } else if (t1->nature()==kReal && t2->nature()==kInt ) {
            return generateCacheCode(sig, subst("($0 $1 $3($2))", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2), ifloat()));
        } else  {
            return generateCacheCode(sig, subst("($0 $1 $2)", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2), ifloat()));
        }
    } else {
        return generateCacheCode(sig, subst("($0 $1 $2)", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2)));
    }
}

/*****************************************************************************
							   Primitive Operations
*****************************************************************************/

string ScalarCompiler::generateFFun(Tree sig, Tree ff, Tree largs)
{
	addIncludeFile(ffincfile(ff)); 	//printf("inc file %s\n", ffincfile(ff));
	addLibrary(fflibfile(ff));		//printf("lib file %s\n", fflibfile(ff));

    string code = ffname(ff);
    code += '(';
    string sep = "";
    for (int i = 0; i< ffarity(ff); i++) {
        code += sep;
        code += CS(nth(largs, i));
        sep = ", ";
    }
    code += ')';
    return generateCacheCode(sig, code);
}

/*****************************************************************************
							   CACHE CODE
*****************************************************************************/

void ScalarCompiler::getTypedNames(Type t, const string& prefix, string& ctype, string& vname)
{
    if (t->nature() == kInt) {
        ctype = "int"; vname = subst("i$0", getFreshID(prefix));
    } else {
        ctype = ifloat(); vname = subst("f$0", getFreshID(prefix));
    }
}

string ScalarCompiler::generateCacheCode(Tree sig, const string& exp)
{
	string vname, ctype, code;
	int sharing = getSharingCount(sig);
    old_Occurences* o = fOccMarkup->retrieve(sig);

	// check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }

	// check for expression occuring in delays
	if (o->getMaxDelay()>0) {

        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        if (sharing>1) {
            return generateDelayVec(sig, generateVariableStore(sig,exp), ctype, vname, o->getMaxDelay());
        } else {
		    return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
        }

    } else if ((sharing > 1) || (o->hasMultiOccurences())) {

        return generateVariableStore(sig, exp);

    } else if (sharing == 1) {

        return exp;

	} else {
        stringstream error;
        error << "ERROR in sharing count (" << sharing << ") for " << *sig << endl;
        throw faustexception(error.str());
	}

	return "Error in generateCacheCode";
}

// like generateCacheCode but we force caching like if sharing was always > 1
string ScalarCompiler::forceCacheCode(Tree sig, const string& exp)
{
	string vname, ctype, code;
	old_Occurences* o = fOccMarkup->retrieve(sig);

	// check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }

	// check for expression occuring in delays
    faustassert(o);
    if (o->getMaxDelay()>0) {

        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        return generateDelayVec(sig, generateVariableStore(sig,exp), ctype, vname, o->getMaxDelay());

	} else  {

        return generateVariableStore(sig, exp);

	}
}

string ScalarCompiler::generateVariableStore(Tree sig, const string& exp)
{
    string vname, ctype;
    Type t = getCertifiedSigType(sig);

    switch (t->variability()) {

        case kKonst:
            getTypedNames(t, "Const", ctype, vname);
            fClass->addDeclCode(subst("$0 \t$1;", ctype, vname));
            fClass->addInitCode(subst("$0 = $1;", vname, exp));
            break;

        case kBlock:
            getTypedNames(t, "Slow", ctype, vname);
            fClass->addFirstPrivateDecl(vname);
            fClass->addZone2(subst("$0 \t$1 = $2;", ctype, vname, exp));
            break;

        case kSamp:
            getTypedNames(t, "TempPerm", ctype, vname);
            // need to be preserved because of new enable and control primitives
            fClass->addDeclCode(subst("$0 \t$1;", ctype, vname));
            fClass->addInitCode(subst("$0 = 0;", vname));
            fClass->addExecCode(Statement(getConditionCode(sig), subst("$0 = $1;", vname, exp)));
            break;
    }
    return vname;
}

/*****************************************************************************
							   	    CASTING
*****************************************************************************/

string ScalarCompiler::generateIntCast(Tree sig, Tree x)
{
	return generateCacheCode(sig, subst("int($0)", CS(x)));
}

string ScalarCompiler::generateFloatCast (Tree sig, Tree x)
{
	return generateCacheCode(sig, subst("$1($0)", CS(x), ifloat()));
}

/*****************************************************************************
							user interface elements
*****************************************************************************/

string ScalarCompiler::generateButton(Tree sig, Tree path)
{
	string varname = getFreshID("fbutton");
	fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
	fClass->addInitUICode(subst("$0 = 0.0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    //return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateCheckbox(Tree sig, Tree path)
{
	string varname = getFreshID("fcheckbox");
	fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
	fClass->addInitUICode(subst("$0 = 0.0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    //return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateVSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fslider");
	fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
	fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    //return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateHSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fslider");
	fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
	fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    //return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateNumEntry(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fentry");
	fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
	fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    //return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateVBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
	string varname = getFreshID("fbargraph");
	fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

	Type t = getCertifiedSigType(sig);
	switch (t->variability()) {

		case kKonst :
			fClass->addInitUICode(subst("$0 = $1;", varname, exp));
			break;

		case kBlock :
			fClass->addZone2(subst("$0 = $1;", varname, exp));
			break;

		case kSamp :
            fClass->addExecCode(Statement(getConditionCode(sig), subst("$0 = $1;", varname, exp)));
			break;
	}

	//return varname;
    return generateCacheCode(sig, varname);
}

string ScalarCompiler::generateHBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
	string varname = getFreshID("fbargraph");
	fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

	Type t = getCertifiedSigType(sig);
	switch (t->variability()) {

		case kKonst :
			fClass->addInitUICode(subst("$0 = $1;", varname, exp));
			break;

		case kBlock :
			fClass->addZone2(subst("$0 = $1;", varname, exp));
			break;

		case kSamp :
            fClass->addExecCode(Statement(getConditionCode(sig), subst("$0 = $1;", varname, exp)));
			break;
	}

    //return varname;
    return generateCacheCode(sig, varname);
}

string ScalarCompiler::generateSoundfile(Tree sig, Tree path)
{
    string varname = getFreshID("fSoundfile");

    // SL
    //fClass->addIncludeFile("<atomic>");
    //fClass->addIncludeFile("\"faust/gui/soundfile.h\"");

    // SL
    //fClass->addDeclCode(subst("std::atomic<Soundfile*> \t$0;", varname));
    fClass->addDeclCode(subst("Soundfile* \t$0;", varname));

    //fClass->addDeclCode(subst("Soundfile* \t$0cache;", varname));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // SL
    fClass->addInitUICode(subst("if (!$0) $0 = defaultsound;", varname));
    fClass->addFirstPrivateDecl(subst("$0cache", varname));

    // SL
    //fClass->addZone2(subst("Soundfile* $0cache = $0.exchange(nullptr);", varname));
    fClass->addZone2(subst("Soundfile* $0cache = $0;", varname));
    fClass->addZone4(subst("$0 = $0cache;", varname));
    return varname;
}

/*****************************************************************************
							   	    TABLES
*****************************************************************************/

/*----------------------------------------------------------------------------
						sigGen : initial table content
----------------------------------------------------------------------------*/

string ScalarCompiler::generateSigGen(Tree sig, Tree content)
{
	string klassname = getFreshID("SIG");
	string signame = getFreshID("sig");

    fClass->addSubKlass(signal2klass(fClass, klassname, content));
	fClass->addInitCode(subst("$0 $1;", klassname, signame));
    fInstanceInitProperty.set(content, pair<string,string>(klassname,signame));

	return signame;
}

string ScalarCompiler::generateStaticSigGen(Tree sig, Tree content)
{
	string klassname = getFreshID("SIG");
	string signame = getFreshID("sig");

    fClass->addSubKlass(signal2klass(fClass, klassname, content));
	fClass->addStaticInitCode(subst("$0 $1;", klassname, signame));
    fStaticInitProperty.set(content, pair<string,string>(klassname,signame));

	return signame;
}

/*----------------------------------------------------------------------------
						sigTable : table declaration
----------------------------------------------------------------------------*/

string ScalarCompiler::generateTable(Tree sig, Tree tsize, Tree content)
{
	string generator(CS(content));
    Tree g;
    string cexp;
    string ctype, vname;
	int size;

    // already compiled but check if we need to add declarations

    faustassert(isSigGen(content, g));
    pair<string,string> kvnames;
    if ( ! fInstanceInitProperty.get(g, kvnames)) {
        // not declared here, we add a declaration
        bool b = fStaticInitProperty.get(g, kvnames);
        faustassert(b);
        fClass->addInitCode(subst("$0 $1;", kvnames.first, kvnames.second));
    }

	if (!isSigInt(tsize, &size)) {
        stringstream error;
        error << "ERROR in generateTable : "
            << *tsize
            << " is not an integer expression "
            << endl;
        throw faustexception(error.str());
	}
	// definition du nom et du type de la table
	// A REVOIR !!!!!!!!!
	Type t = getCertifiedSigType(content);//, tEnv);
	if (t->nature() == kInt) {
		vname = getFreshID("itbl");
		ctype = "int";
	} else {
		vname = getFreshID("ftbl");
		ctype = ifloat();
	}

	// declaration de la table
	fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(size)));

	// initialisation du generateur de contenu
	fClass->addInitCode(subst("$0.init(samplingFreq);", generator));
	// remplissage de la table
	fClass->addInitCode(subst("$0.fill($1,$2);", generator, T(size), vname));

	// on retourne le nom de la table
	return vname;
}

string ScalarCompiler::generateStaticTable(Tree sig, Tree tsize, Tree content)
{
	//string generator(CS(content));
	Tree g;
	string cexp;
	string ctype, vname;
	int size;

	faustassert(isSigGen(content, g));

	if (!getCompiledExpression(content, cexp)) {
		cexp = setCompiledExpression(content, generateStaticSigGen(content, g));
    } else {
        // already compiled but check if we need to add declarations
        pair<string,string> kvnames;
        if ( ! fStaticInitProperty.get(g, kvnames)) {
            // not declared here, we add a declaration
            bool b = fInstanceInitProperty.get(g, kvnames);
            faustassert(b);
            fClass->addStaticInitCode(subst("$0 $1;", kvnames.first, kvnames.second));
        }
    }

    if (!isSigInt(tsize, &size)) {
        stringstream error;
        error << "ERROR in generateStaticTable : "
            << *tsize
            << " is not an integer expression "
            << endl;
        throw faustexception(error.str());
	}

	// definition du nom et du type de la table
	// A REVOIR !!!!!!!!!
	Type t = getCertifiedSigType(content);//, tEnv);
	if (t->nature() == kInt) {
		vname = getFreshID("itbl");
		ctype = "int";
	} else {
		vname = getFreshID("ftbl");
		ctype = ifloat();
	}

	// declaration de la table
    if (gGlobal->gMemoryManager) {
        fClass->addDeclCode(subst("static $0* \t$1;", ctype, vname));
        fClass->addStaticFields(subst("$0* \t$1::$2 = 0;", ctype, fClass->getClassName(), vname));
        fClass->addStaticInitCode(subst("$0 = static_cast<$1*>(fManager->allocate(sizeof($1) * $2));", vname, ctype, T(size)));
        fClass->addStaticDestroyCode(subst("fManager->destroy($0);", vname));
     } else {
        fClass->addDeclCode(subst("static $0 \t$1[$2];", ctype, vname, T(size)));
        fClass->addStaticFields(subst("$0 \t$1::$2[$3];", ctype, fClass->getClassName(), vname, T(size)));
    }

    // initialisation du generateur de contenu
    fClass->addStaticInitCode(subst("$0.init(samplingFreq);", cexp));
    // remplissage de la table
    fClass->addStaticInitCode(subst("$0.fill($1,$2);", cexp, T(size), vname));

	// on retourne le nom de la table
	return vname;
}

/*----------------------------------------------------------------------------
						sigWRTable : table assignement
----------------------------------------------------------------------------*/

string ScalarCompiler::generateWRTbl(Tree sig, Tree tbl, Tree idx, Tree data)
{
	string tblName(CS(tbl));
    fClass->addExecCode(Statement(getConditionCode(sig), subst("$0[$1] = $2;", tblName, CS(idx), CS(data))));
	return tblName;
}

/*----------------------------------------------------------------------------
						sigRDTable : table access
----------------------------------------------------------------------------*/

string ScalarCompiler::generateRDTbl(Tree sig, Tree tbl, Tree idx)
{
	// YO le 21/04/05 : La lecture des tables n'était pas mise dans le cache
	// et donc le code était dupliqué(dans tester.dsp par exemple)
	//return subst("$0[$1]", CS(tEnv, tbl), CS(tEnv, idx));

	//cerr << "generateRDTable " << *sig << endl;
	// test the special case of a read only table that can be compiled as a static member
	Tree id, size, content;
	if(	isSigTable(tbl, id, size, content) ) {
		string tblname;
		if (!getCompiledExpression(tbl, tblname)) {
			tblname = setCompiledExpression(tbl, generateStaticTable(tbl, size, content));
		}
		return generateCacheCode(sig, subst("$0[$1]", tblname, CS(idx)));
	} else {
		return generateCacheCode(sig, subst("$0[$1]", CS(tbl), CS(idx)));
	}
}

/*****************************************************************************
							   RECURSIONS
*****************************************************************************/

/**
 * Generate code for a projection of a group of mutually recursive definitions
 */
string ScalarCompiler::generateRecProj(Tree sig, Tree r, int i)
{
    string vname;
    Tree var, le;

    if (!getVectorNameProperty(sig, vname)) {
        faustassert(isRec(r, var, le));
        generateRec(r, var, le);
        faustassert(getVectorNameProperty(sig, vname));
    }
    return "[[UNUSED EXP]]";    // make sure the resulting expression is never used in the generated code
}

/**
 * Generate code for a group of mutually recursive definitions
 */
void ScalarCompiler::generateRec(Tree sig, Tree var, Tree le)
{
    int N = len(le);

    vector<bool> used(N);
    vector<int> delay(N);
    vector<string> vname(N);
    vector<string> ctype(N);

    // prepare each element of a recursive definition
    for (int i = 0; i < N; i++) {
        Tree e = sigProj(i,sig);     // recreate each recursive definition
        if (fOccMarkup->retrieve(e)) {
            // this projection is used
            used[i] = true;
            getTypedNames(getCertifiedSigType(e), "Rec", ctype[i],  vname[i]);
            setVectorNameProperty(e, vname[i]);
            delay[i] = fOccMarkup->retrieve(e)->getMaxDelay();
        } else {
            // this projection is not used therefore
            // we should not generate code for it
            used[i] = false;
        }
    }

    // generate delayline for each element of a recursive definition
    for (int i = 0; i < N; i++) {
        if (used[i]) {
            generateDelayLine(ctype[i], vname[i], delay[i], CS(nth(le,i)), getConditionCode(nth(le,i)));
        }
    }
}

/*****************************************************************************
                               PREFIX, DELAY A PREFIX VALUE
*****************************************************************************/

string ScalarCompiler::generateEnable(Tree sig, Tree x, Tree y)
{
    CS(y);
    return generateCacheCode(x, CS(x));
// return CS(x);
}

/*****************************************************************************
                               PREFIX, DELAY A PREFIX VALUE
*****************************************************************************/

string ScalarCompiler::generatePrefix(Tree sig, Tree x, Tree e)
{
    Type te = getCertifiedSigType(sig);//, tEnv);

    string vperm = getFreshID("M");
    string vtemp = getFreshID("T");

    string type = old_cType(te);

    fClass->addDeclCode(subst("$0 \t$1;", type, vperm));
    fClass->addInitCode(subst("$0 = $1;", vperm, CS(x)));
    fClass->addInitCode(subst("$0 \t$1;", type, vtemp));

    fClass->addExecCode(Statement(getConditionCode(sig), subst("$0 = $1;", vtemp, vperm)));
    fClass->addExecCode(Statement(getConditionCode(sig), subst("$0 = $1;", vperm, CS(e))));
    return vtemp;
}

/*****************************************************************************
							   IOTA(n)
*****************************************************************************/
static bool isPowerOf2(int n)
{
	return !(n & (n - 1));
}

string ScalarCompiler::generateIota(Tree sig, Tree n)
{
	int size;
	if (!isSigInt(n, &size)) { throw faustexception("ERROR in generateIota\n"); }

	string vperm = getFreshID("iota");

	fClass->addDeclCode(subst("int \t$0;",  vperm));
	fClass->addClearCode(subst("$0 = 0;", vperm));

	if (isPowerOf2(size)) {
        fClass->addExecCode(Statement("", subst("$0 = ($0+1)&$1;", vperm, T(size-1))));
	} else {
        fClass->addExecCode(Statement("", subst("if (++$0 == $1) $0=0;", vperm, T(size))));
	}
	return vperm;
}

// a revoir en utilisant la lecture de table et en partageant la construction de la paire de valeurs

/**
 * Generate a select2 code
 */

string ScalarCompiler::generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2)
{
    return generateCacheCode(sig, subst("(($0)?$1:$2)", CS(sel), CS(s2), CS(s1)));
}

/**
 * Generate a select3 code (using if-then-else)
 * ((int n = sel==0)? s0 : ((sel==1)? s1 : s2))
 * int nn; ((nn=sel) ? ((nn==1)? s1 : s2) : s0);
 */
string ScalarCompiler::generateSelect3(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3)
{
    return generateCacheCode(sig, subst("(($0==0)? $1 : (($0==1)?$2:$3) )", CS(sel), CS(s1), CS(s2), CS(s3)));
}

#if 0
string ScalarCompiler::generateSelect3(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3)
{
    Type t = getCertifiedSigType(sig);
    Type t1 = getCertifiedSigType(s1);
    Type t2 = getCertifiedSigType(s2);
    Type t3 = getCertifiedSigType(s3);
    Type w = min(t1,min(t2,t3));

    string type = old_cType(t);
    string var = getFreshID("S");

    switch (w->variability())
    {
        case kKonst:
            fClass->addDeclCode(subst("$0 \t$1[3];", type, var));
            break;
        case kBlock:
            //fClass->addLocalDecl(type, subst("$0[3]", var));
            //fClass->addLocalVecDecl(type, var, 3);
            fClass->addSharedDecl(var);
            fClass->addZone1(subst("$0 \t$1[3];", type, var));
            break;
        case kSamp:
            fClass->addExecCode(subst("$0 \t$1[3];", type, var));
            break;
    }

    switch (t1->variability())
    {
        case kKonst:
            fClass->addClearCode(subst("$0[0] = $1;", var, CS(s1)));
            break;
        case kBlock:
            fClass->addZone2b(subst("$0[0] = $1;", var, CS(s1)));
            break;
        case kSamp:
            fClass->addExecCode(subst("$0[0] = $1;", var, CS(s1)));
            break;
    }

    switch (t2->variability())
    {
        case kKonst:
            fClass->addClearCode(subst("$0[1] = $1;", var, CS(s2)));
            break;
        case kBlock:
            fClass->addZone2b(subst("$0[1] = $1;", var, CS(s2)));
            break;
        case kSamp:
            fClass->addExecCode(subst("$0[1] = $1;", var, CS(s2)));
            break;
    }

    switch (t3->variability())
    {
        case kKonst:
            fClass->addClearCode(subst("$0[2] = $1;", var, CS(s3)));
            break;
        case kBlock:
            fClass->addZone2b(subst("$0[2] = $1;", var, CS(s3)));
            break;
        case kSamp:
            fClass->addExecCode(subst("$0[2] = $1;", var, CS(s3)));
            break;
    }

    return generateCacheCode(sig, subst("$0[$1]", var, CS(sel)));
}
#endif

/**
 * retrieve the type annotation of sig
 * @param sig the signal we want to know the type
 */
string ScalarCompiler::generateXtended(Tree sig)
{
	xtended* p = (xtended*)getUserData(sig);
	vector<string> args;
	vector<Type> types;

	for (int i = 0; i < sig->arity(); i++) {
		args.push_back(CS(sig->branch(i)));
		types.push_back(getCertifiedSigType(sig->branch(i)));
	}

	if (p->needCache()) {
		return generateCacheCode(sig, p->old_generateCode(fClass, args, types));
	} else {
		return p->old_generateCode(fClass, args, types);
	}
}

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
void ScalarCompiler::setVectorNameProperty(Tree sig, const string& vecname)
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

bool ScalarCompiler::getVectorNameProperty(Tree sig, string& vecname)
{
    return fVectorProperty.get(sig, vecname);
}

/**
 * Compute the minimal power of 2 greater than x
 */

int ScalarCompiler::pow2limit(int x)
{
	int n = 2;
	while (n < x) { n = 2*n; }
	return n;
}

/*****************************************************************************
							   N-SAMPLE FIXED DELAY : sig = exp@delay

	case 1-sample max delay :
		Y(t-0)	Y(t-1)
		Temp	Var						gLessTempSwitch = false
		V[0]	V[1]					gLessTempSwitch = true

	case max delay < gMaxCopyDelay :
		Y(t-0)	Y(t-1)	Y(t-2)  ...
		Temp	V[0]	V[1]	...		gLessTempSwitch = false
		V[0]	V[1]	V[2]	...		gLessTempSwitch = true

	case max delay >= gMaxCopyDelay :
		Y(t-0)	Y(t-1)	Y(t-2)  ...
		Temp	V[0]	V[1]	...
		V[0]	V[1]	V[2]	...


*****************************************************************************/

/**
 * Generate code for accessing a delayed signal. The generated code depend of
 * the maximum delay attached to exp and the gLessTempSwitch.
 */

string ScalarCompiler::generateFixDelay(Tree sig, Tree exp, Tree delay)
{
	int mxd, d;
	string vecname;

    //cerr << "ScalarCompiler::generateFixDelay sig = " << *sig << endl;
    //cerr << "ScalarCompiler::generateFixDelay exp = " << *exp << endl;
    //cerr << "ScalarCompiler::generateFixDelay del = " << *delay << endl;

    string code = CS(exp); // ensure exp is compiled to have a vector name

    mxd = fOccMarkup->retrieve(exp)->getMaxDelay();

	if (! getVectorNameProperty(exp, vecname)) {
        if (mxd == 0) {
            //cerr << "it is a pure zero delay : " << code << endl;
            return code;
        } else {
            cerr << "No vector name for : " << ppsig(exp) << endl;
            faustassert(0);
        }
    }

    if (mxd == 0) {
        // not a real vector name but a scalar name
        return vecname;

	} else if (mxd < gGlobal->gMaxCopyDelay) {
		if (isSigInt(delay, &d)) {
			return subst("$0[$1]", vecname, CS(delay));
		} else {
			return generateCacheCode(sig, subst("$0[$1]", vecname, CS(delay)));
		}

	} else {

		// long delay : we use a ring buffer of size 2^x
		int 	N 	= pow2limit( mxd+1 );
		return generateCacheCode(sig, subst("$0[(IOTA-$1)&$2]", vecname, CS(delay), T(N-1)));
	}
}

/**
 * Generate code for the delay mecchanism. The generated code depend of the
 * maximum delay attached to exp and the "less temporaries" switch
 */

string ScalarCompiler::generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd)
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

string ScalarCompiler::generateDelayVecNoTemp(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd)
{
    faustassert(mxd > 0);

    //bool odocc = fOccMarkup->retrieve(sig)->hasOutDelayOccurences();
    string ccs = getConditionCode(sig);

    if (mxd < gGlobal->gMaxCopyDelay) {

        // short delay : we copy
        fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(mxd+1)));
        fClass->addClearCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(mxd+1)));
        fClass->addExecCode(Statement(ccs, subst("$0[0] = $1;", vname, exp)));

        // generate post processing copy code to update delay values
        if (mxd == 1) {
            fClass->addPostCode(Statement(ccs, subst("$0[1] = $0[0];", vname)));
        } else if (mxd == 2) {
            //fClass->addPostCode(subst("$0[2] = $0[1];", vname));
            fClass->addPostCode(Statement(ccs, subst("$0[2] = $0[1]; $0[1] = $0[0];", vname)));
        } else {
            fClass->addPostCode(Statement(ccs, subst("for (int i=$0; i>0; i--) $1[i] = $1[i-1];", T(mxd), vname)));
        }
        setVectorNameProperty(sig, vname);
        return subst("$0[0]", vname);

    } else {

        // generate code for a long delay : we use a ring buffer of size N = 2**x > mxd
        int N = pow2limit(mxd+1);

        // we need a iota index
        ensureIotaCode();

        // declare and init
        fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(N)));
        fClass->addClearCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(N)));

        // execute
        fClass->addExecCode(Statement(ccs, subst("$0[IOTA&$1] = $2;", vname, T(N-1), exp)));
        setVectorNameProperty(sig, vname);
        return subst("$0[IOTA&$1]", vname, T(N-1));
    }
}

/**
 * Generate code for the delay mecchanism without using temporary variables
 */

void ScalarCompiler::generateDelayLine(const string& ctype, const string& vname, int mxd, const string& exp, const string& ccs)
{
    //faustassert(mxd > 0);
    if (mxd == 0) {
        // cerr << "MXD==0 :  " << vname << " := " << exp << endl;
        // no need for a real vector
        fClass->addExecCode(Statement(ccs, subst("$0 \t$1 = $2;", ctype, vname, exp)));


    } else if (mxd < gGlobal->gMaxCopyDelay) {
        // cerr << "small delay : " << vname << "[" << mxd << "]" << endl;

        // short delay : we copy
        fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(mxd+1)));
        fClass->addClearCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(mxd+1)));
        fClass->addExecCode(Statement(ccs, subst("$0[0] = $1;", vname, exp)));

        // generate post processing copy code to update delay values
        if (mxd == 1) {
            fClass->addPostCode(Statement(ccs, subst("$0[1] = $0[0];", vname)));
        } else if (mxd == 2) {
            fClass->addPostCode(Statement(ccs, subst("$0[2] = $0[1]; $0[1] = $0[0];", vname)));
        } else {
            fClass->addPostCode(Statement(ccs, subst("for (int i=$0; i>0; i--) $1[i] = $1[i-1];", T(mxd), vname)));
        }

    } else {

        // generate code for a long delay : we use a ring buffer of size N = 2**x > mxd
        int N = pow2limit(mxd+1);

        // we need a iota index
        ensureIotaCode();

        // declare and init
        fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(N)));
        fClass->addClearCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(N)));

        // execute
        fClass->addExecCode(Statement(ccs, subst("$0[IOTA&$1] = $2;", vname, T(N-1), exp)));
    }
}

/**
 * Generate code for a unique IOTA variable increased at each sample
 * and used to index ring buffers.
 */
void ScalarCompiler::ensureIotaCode()
{
    if (!fHasIota) {
        fHasIota = true;
        fClass->addDeclCode("int \tIOTA;");
        fClass->addClearCode("IOTA = 0;");
        fClass->addPostCode(Statement("", "IOTA = IOTA+1;"));
    }
}

/**
 * Generate code for a waveform. The waveform will be declared as a static field.
 * The name of the waveform is returned in vname and its size in size.
 */
void ScalarCompiler::declareWaveform(Tree sig, string& vname, int& size)
{
    // computes C type and unique name for the waveform
    string ctype;
    getTypedNames(getCertifiedSigType(sig), "Wave", ctype, vname);

    size = sig->arity();

    // Converts waveform into a string : "{a,b,c,...}"
    stringstream content;

    char sep = '{';
    for (int i = 0; i < size; i++) {
        content << sep << ppsig(sig->branch(i));
        sep = ',';
    }
    content << '}';

    // Declares the Waveform
    fClass->addDeclCode(subst("static $0 \t$1[$2];", ctype, vname, T(size)));
    fClass->addDeclCode(subst("int \tidx$0;", vname));
    fClass->addInitCode(subst("idx$0 = 0;", vname));
    fClass->getTopParentKlass()->addStaticFields(
                subst("$0 \t$1::$2[$3] = ", ctype, fClass->getFullClassName(), vname, T(size) )
                + content.str() + ";");
}

string ScalarCompiler::generateWaveform(Tree sig)
{
    string vname;
    int size;

    declareWaveform(sig, vname, size);
    fClass->addPostCode(Statement(getConditionCode(sig), subst("idx$0 = (idx$0 + 1) % $1;", vname, T(size))));
    return generateCacheCode(sig, subst("$0[idx$0]", vname));
}
