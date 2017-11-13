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

#include <string>

#include "instructions.hh"
#include "instructions_compiler.hh"
#include "sigprint.hh"
#include "floats.hh"
#include "ppsig.hh"
#include "Text.hh"
#include "sigtyperules.hh"
#include "timing.hh"
#include "recursivness.hh"
#include "privatise.hh"
#include "simplify.hh"
#include "xtended.hh"
#include "prim2.hh"
#include "ensure.hh"
#include "sigToGraph.hh"
#include "exception.hh"
#include "global.hh"

using namespace std;

std::ostream* Printable::fOut = &cout;

static inline BasicTyped* genBasicFIRTyped(int sig_type)
{
    return InstBuilder::genBasicTyped((sig_type == kInt) ? Typed::kInt32 : itfloat());
}

InstructionsCompiler::InstructionsCompiler(CodeContainer* container)
            :fContainer(container), fSharingKey(NULL), fUIRoot(uiFolder(cons(tree(0), tree(subst("$0", ""))), gGlobal->nil)), 
            fDescription(0), fLoadedIota(false)
{}

/*****************************************************************************
						    prepare
*****************************************************************************/

// Taken from sharing.cpp

int InstructionsCompiler::getSharingCount(Tree sig)
{
	Tree c;
	if (getProperty(sig, fSharingKey, c)) {
        return c->node().getInt();
	} else {
        return 0;
	}
}

void InstructionsCompiler::setSharingCount(Tree sig, int count)
{
	setProperty(sig, fSharingKey, tree(count));
}

void InstructionsCompiler::sharingAnalysis(Tree t)
{
  	fSharingKey = shprkey(t);
	if (isList(t)) {
		while (isList(t)) {
			sharingAnnotation(kSamp, hd(t));
			t = tl(t);
		}
	} else {
		sharingAnnotation(kSamp, t);
	}
}

void InstructionsCompiler::sharingAnnotation(int vctxt, Tree sig)
{
	Tree c, x, y, z;

	//cerr << "START sharing annotation of " << *sig << endl;
	int count = getSharingCount(sig);

	if (count > 0) {
		// it is not our first visit
		setSharingCount(sig, count+1);

	} else {
		// it is our first visit,
		int v = getCertifiedSigType(sig)->variability();

		// check "time sharing" cases
		if (v < vctxt) {
			setSharingCount(sig, 2); 	// time sharing occurence : slower expression in faster context
		} else {
			setSharingCount(sig, 1);	// regular occurence
		}

		if (isSigSelect3(sig,c,y,x,z)) {
			// make a special case for select3 implemented with real if
			// because the c expression will be used twice in the C++
			// translation
			sharingAnnotation(v, c);
			sharingAnnotation(v, c);
			sharingAnnotation(v, x);
			sharingAnnotation(v, y);
			sharingAnnotation(v, z);
		} else {
			// Annotate the sub signals
			vector<Tree> subsig;
			int n = getSubSignals(sig, subsig);
			if (n > 0 && !isSigGen(sig)) {
				for (int i = 0; i < n; i++) sharingAnnotation(v, subsig[i]);
			}
		}
	}
	//cerr << "END sharing annotation of " << *sig << endl;
}

Tree InstructionsCompiler::prepare(Tree LS)
{
    startTiming("prepare");
    //startTiming("first simplification");
    //LS = simplify(LS);
    //endTiming("first simplification");
    startTiming("deBruijn2Sym");
	Tree L1 = deBruijn2Sym(LS);   	// convert debruijn recursion into symbolic recursion
    endTiming("deBruijn2Sym");
    startTiming("second simplification");
	Tree L2 = simplify(L1);			// simplify by executing every computable operation
    endTiming("second simplification");
	Tree L3 = privatise(L2);		// Un-share tables with multiple writers

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
  	fOccMarkup.mark(L3);			// annotate L3 with occurences analysis
    //annotationStatistics();
    endTiming("prepare");

    if (gGlobal->gDrawSignals) {
        ofstream dotfile(subst("$0-sig.dot", gGlobal->makeDrawPath()).c_str());
        sigToGraph(L3, dotfile);
    }
  	return L3;
}

Tree InstructionsCompiler::prepare2(Tree L0)
{
    startTiming("prepare2");

	recursivnessAnnotation(L0);		// Annotate L0 with recursivness information
	typeAnnotation(L0);				// Annotate L0 with type information
	sharingAnalysis(L0);			// annotate L0 with sharing count
 	fOccMarkup.mark(L0);			// annotate L0 with occurences analysis

    endTiming("prepare2");
  	return L0;
}

/*****************************************************************************
 CACHE CODE
 *****************************************************************************/

void InstructionsCompiler::getTypedNames(::Type t, const string& prefix, Typed::VarType& ctype, string& vname)
{
    if (t->nature() == kInt) {
        ctype = Typed::kInt32;
        vname = subst("i$0", gGlobal->getFreshID(prefix));
    } else {
        ctype = itfloat();
        vname = subst("f$0", gGlobal->getFreshID(prefix));
    }
}

/**
 * Test if a signal is already compiled
 * @param sig the signal expression to compile.
 * @param name the string representing the compiled expression.
 * @return true is already compiled
 */
bool InstructionsCompiler::getCompiledExpression(Tree sig, InstType& cexp)
{
    return fCompileProperty.get(sig, cexp);
}

/**
 * Set the string of a compiled expression is already compiled
 * @param sig the signal expression to compile.
 * @param cexp the string representing the compiled expression.
 * @return the cexp (for commodity)
 */
InstType InstructionsCompiler::setCompiledExpression(Tree sig, const InstType& cexp)
{
    InstType old;
    if (fCompileProperty.get(sig, old) && (old != cexp)) {
        //stringstream error;
        //error << "ERROR already a compiled expression attached : " << old << " replaced by " << cexp << endl;
        //throw faustexception(error.str());
    }

    fCompileProperty.set(sig, cexp);
	return cexp;
}

/*****************************************************************************
						vector name property
*****************************************************************************/

/**
 * Set the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vname the string representing the vector name.
 * @return true is already compiled
 */
void InstructionsCompiler::setVectorNameProperty(Tree sig, const string& vname)
{
    faustassert(vname.size() > 0);
    fVectorProperty.set(sig, vname);
}

/**
 * Get the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vname the string where to store the vector name.
 * @return true if the signal has this property, false otherwise
 */

bool InstructionsCompiler::getVectorNameProperty(Tree sig, string& vname)
{
    return fVectorProperty.get(sig, vname);
}

void InstructionsCompiler::setTableNameProperty(Tree sig, const string& name)
{
    faustassert(name.size() > 0);
    fTableProperty.set(sig, name);
}

bool InstructionsCompiler::getTableNameProperty(Tree sig, string& name)
{
    return fTableProperty.get(sig, name);
}

CodeContainer* InstructionsCompiler::signal2Container(const string& name, Tree sig)
{
	::Type t = getCertifiedSigType(sig);

	CodeContainer* container = fContainer->createScalarContainer(name, t->nature());
    InstructionsCompiler C(container);
    C.compileSingleSignal(sig);
    return container;
}

/*****************************************************************************
						    compileMultiSignal
*****************************************************************************/

void InstructionsCompiler::compileMultiSignal(Tree L)
{
	L = prepare(L);		// Optimize, share and annotate expression
    
    startTiming("compileMultiSignal");

    Typed* type = InstBuilder::genBasicTyped(Typed::kFloatMacro);

    if (!gGlobal->gOpenCLSwitch && !gGlobal->gCUDASwitch) { // HACK
    
        // HACK for Rust backend
        if (gGlobal->gOutputLang != "rust") {
            // "input" and "inputs" used as a name convention
            for (int index = 0; index < fContainer->inputs(); index++) {
                string name = subst("input$0", T(index));
                pushComputeBlockMethod(InstBuilder::genDecStackVar(name, InstBuilder::genArrayTyped(type, 0),
                    InstBuilder::genLoadArrayFunArgsVar("inputs", InstBuilder::genInt32NumInst(index))));
                if (gGlobal->gInPlace) {
                    CS(sigInput(index));
                }
            }
        }

        // HACK for Rust backend
        if (gGlobal->gOutputLang != "rust") {
            // "output" and "outputs" used as a name convention
            for (int index = 0; index < fContainer->outputs(); index++) {
                string name = subst("output$0", T(index));
                pushComputeBlockMethod(InstBuilder::genDecStackVar(name, InstBuilder::genArrayTyped(type, 0),
                    InstBuilder::genLoadArrayFunArgsVar("outputs", InstBuilder::genInt32NumInst(index))));
            }
        }
    }

	for (int index = 0; isList(L); L = tl(L), index++) {
		Tree sig = hd(L);
        string name;
        
        // HACK for Rust backend
        if (gGlobal->gOutputLang == "rust") {
            name = subst("outputs[$0]", T(index));
        } else {
            name = subst("output$0", T(index));
        }

        // Cast to external float
        ValueInst* res = InstBuilder::genCastNumFloatMacroInst(CS(sig));
        pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(name, getCurrentLoopIndex(), res));

        // 09/12/11 : HACK
        //int rate = getSigRate(sig);
        int rate = 1;
        fContainer->setOutputRate(index, rate);
    }

    generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot), true);
    generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
    if (fDescription) {
        fDescription->ui(prepareUserInterfaceTree(fUIRoot));
    }

    // Apply FIR to FIR transformations
    fContainer->processFIR();
    
    // Generate JSON
    if (gGlobal->gPrintJSONSwitch) {
        fContainer->generateJSONFile();
    }
       
    endTiming("compileMultiSignal");
}

/*****************************************************************************
						    compileSingleSignal
*****************************************************************************/

void InstructionsCompiler::compileSingleSignal(Tree sig)
{
  	sig = prepare2(sig);		// Optimize and annotate expression
    string name = "output";

    pushComputeDSPMethod(InstBuilder::genStoreArrayFunArgsVar(name, getCurrentLoopIndex(), CS(sig)));

	generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
	generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
	if (fDescription) {
		fDescription->ui(prepareUserInterfaceTree(fUIRoot));
	}
}

/*****************************************************************************
 generateCode : dispatch according to signal
 *****************************************************************************/
/**
 * Main code generator dispatch.
 * @param sig the signal expression to compile.
 * @return the FIR code translation of sig
 */

ValueInst* InstructionsCompiler::generateCode(Tree sig)
{
#if 0
	fprintf(stderr, "CALL generateCode(");
    printSignal(sig, stderr);
	fprintf(stderr, ")\n");
#endif

    ValueInst* code;
    if (getCompiledExpression(sig, code)) {
        return code;
    }

	int 	i;
	double	r;
	Tree 	c, sel, x, y, z, label, id, ff, largs, type, name, file;

	//printf("compilation of %p : ", sig); print(sig); printf("\n");

		 if ( getUserData(sig) ) 					{ return generateXtended(sig); }
	else if ( isSigInt(sig, &i) ) 					{ return generateIntNumber(sig, i); }
	else if ( isSigReal(sig, &r) ) 					{ return generateRealNumber(sig, r); }
    else if ( isSigWaveform(sig) )                  { return generateWaveform(sig); }
	else if ( isSigInput(sig, &i) ) 				{ return generateInput(sig, i); }

	else if ( isSigFixDelay(sig, x, y) ) 			{ return generateFixDelay(sig, x, y); }
	else if ( isSigPrefix(sig, x, y) ) 				{ return generatePrefix(sig, x, y); }
	else if ( isSigIota(sig, x) ) 					{ return generateIota(sig, x); }

	else if ( isSigBinOp(sig, &i, x, y) )			{ return generateBinOp(sig, i, x, y); }
	else if ( isSigFFun(sig, ff, largs) )			{ return generateFFun(sig, ff, largs); }
    else if ( isSigFConst(sig, type, name, file) )  { return generateFConst(sig, type, tree2str(file), tree2str(name)); }
    else if ( isSigFVar(sig, type, name, file) )    { return generateFVar(sig, type, tree2str(file), tree2str(name)); }

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
	else if ( isSigVSlider(sig, label,c,x,y,z) )	{ return generateVSlider(sig, label, c, x, y, z); }
	else if ( isSigHSlider(sig, label,c,x,y,z) )	{ return generateHSlider(sig, label, c, x, y, z); }
	else if ( isSigNumEntry(sig, label,c,x,y,z) )	{ return generateNumEntry(sig, label, c, x, y, z); }


	else if ( isSigVBargraph(sig, label,x,y,z) )	{ return generateVBargraph(sig, label, x, y, CS(z)); }
	else if ( isSigHBargraph(sig, label,x,y,z) )	{ return generateHBargraph(sig, label, x, y, CS(z)); }
	else if ( isSigAttach(sig, x, y) )				{ CS(y); return generateCacheCode(sig, CS(x)); }
    /*
    HACK : 09/12/11
    else if (isSigVectorize(sig, x, y)) {
        printf("vectorize not implemented\n");
        exit(0);
    }
    else if (isSigSerialize(sig, x)) {
        printf("serialize not implemented\n");
        exit(0);
    }
    else if (isSigConcat(sig, x, y)) {
        printf("concatenation not implemented\n");
        exit(0);
    }
    else if (isSigVectorAt(sig, x, y)) {
        printf("vector at not implemented\n");
        exit(0);
    }
    */
	else {
        stringstream error;
        error << "Error when compiling, unrecognized signal : " << ppsig(sig) << endl;
        throw faustexception(error.str());
	}
	return InstBuilder::genNullInst();
}

ValueInst* InstructionsCompiler::generateCacheCode(Tree sig, ValueInst* exp)
{
    ValueInst* code;

    // Check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }

    string vname;
    Typed::VarType ctype;
    int sharing = getSharingCount(sig);
    Occurences* o = fOccMarkup.retrieve(sig);
    faustassert(o);

    // Check for expression occuring in delays
	if (o->getMaxDelay() > 0) {

        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        if (sharing > 1) {
            return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname, o->getMaxDelay());
        } else {
		    return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
        }

	} else if (sharing == 1) {

        return exp;

	} else if (sharing > 1) {

        return generateVariableStore(sig, exp);

	} else {
        stringstream error;
        error << "Error in sharing count (" << sharing << ") for " << *sig << endl;
        throw faustexception(error.str());
	}
}

// Like generateCacheCode but we force caching like if sharing was always > 1
ValueInst* InstructionsCompiler::forceCacheCode(Tree sig, ValueInst* exp)
{
    ValueInst* code;
    
    // check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }
    
    string vname;
    Typed::VarType ctype;
    Occurences* o = fOccMarkup.retrieve(sig);
    faustassert(o);
    
	// check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname, o->getMaxDelay());
    } else  {
        return generateVariableStore(sig, exp);
 	}
}

ValueInst* InstructionsCompiler::CS(Tree sig)
{
    ValueInst* code;

    if (!getCompiledExpression(sig, code)) {
        code = generateCode(sig);
        setCompiledExpression(sig, code);
    }

    return code;
}

ValueInst* InstructionsCompiler::generateVariableStore(Tree sig, ValueInst* exp)
{
    // If value is already a variable, no need to create a new one, just reuse it...
    if (dynamic_cast<LoadVarInst*>(exp)) { return exp; }

    string vname;
    Typed::VarType ctype;
    ::Type t = getCertifiedSigType(sig);

    switch (t->variability()) {

        case kKonst:
            getTypedNames(t, "Const", ctype, vname);
            pushDeclare(InstBuilder::genDecStructVar(vname, InstBuilder::genBasicTyped(ctype)));
            pushInitMethod(InstBuilder::genStoreStructVar(vname, exp));
            return InstBuilder::genLoadStructVar(vname);

        case kBlock:
            getTypedNames(t, "Slow", ctype, vname);
            pushComputeBlockMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), exp));
            return InstBuilder::genLoadStackVar(vname);

        case kSamp:
            getTypedNames(t, "Temp", ctype, vname);
            // Only generated for the DSP loop
            if (gGlobal->gHasTeeLocal) {
                pushComputeDSPMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype)));
                return InstBuilder::genTeeVar(vname, exp);
            } else {
                pushComputeDSPMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), exp));
                return InstBuilder::genLoadStackVar(vname);
            }

        default:
            return InstBuilder::genNullInst();
    }
}

ValueInst* InstructionsCompiler::generateXtended(Tree sig)
{
    xtended* p = (xtended*)getUserData(sig);
	list<ValueInst*> args;
    vector< ::Type> arg_types;

	for (int i = 0; i < sig->arity(); i++) {
		args.push_back(CS(sig->branch(i)));
		arg_types.push_back(getCertifiedSigType(sig->branch(i)));
	}

	if (p->needCache()) {
		return generateCacheCode(sig, p->generateCode(fContainer, args, getCertifiedSigType(sig), arg_types));
	} else {
		return p->generateCode(fContainer, args, getCertifiedSigType(sig), arg_types);
	}
}

ValueInst* InstructionsCompiler::generateFixDelay(Tree sig, Tree exp, Tree delay)
{
    ValueInst* code = CS(exp); // Ensure exp is compiled to have a vector name
    int mxd = fOccMarkup.retrieve(exp)->getMaxDelay();
    string vname;

	if (!getVectorNameProperty(exp, vname)) {
    
        if (mxd == 0) {
            //cerr << "it is a pure zero delay : " << code << endl;
            return code;
        } else {
            stringstream error;
            error << "No vector name for : " << ppsig(exp) << endl;
            throw faustexception(error.str());
        }
    }

    if (mxd == 0) {
        return InstBuilder::genLoadStackVar(vname);
	} else if (mxd < gGlobal->gMaxCopyDelay) {
		return InstBuilder::genLoadArrayStructVar(vname, CS(delay));
	} else {
		// Long delay : we use a ring buffer of size 2^x
		int N = pow2limit(mxd + 1);
        FIRIndex value2 = (FIRIndex(InstBuilder::genLoadStructVar("IOTA")) - CS(delay)) & InstBuilder::genInt32NumInst(N - 1);
        return InstBuilder::genLoadArrayStructVar(vname, value2);
    }
}

/*****************************************************************************
 PREFIX, DELAY A PREFIX VALUE
 *****************************************************************************/

ValueInst* InstructionsCompiler::generatePrefix(Tree sig, Tree x, Tree e)
{
 	string vperm = gGlobal->getFreshID("M");
	string vtemp = gGlobal->getFreshID("T");
    Typed::VarType type = ctType(getCertifiedSigType(sig));

    // Table declaration
    pushDeclare(InstBuilder::genDecStructVar(vperm, InstBuilder::genBasicTyped(type)));

    // Init
    pushInitMethod(InstBuilder::genStoreStructVar(vperm, CS(x)));

    // Exec
    pushComputeDSPMethod(InstBuilder::genDecStructVar(vtemp, InstBuilder::genBasicTyped(type), InstBuilder::genLoadStructVar(vperm)));
    pushComputeDSPMethod(InstBuilder::genStoreStructVar(vperm, CS(e)));

    return InstBuilder::genLoadStackVar(vtemp);
}

ValueInst* InstructionsCompiler::generateIota(Tree sig, Tree arg) { return InstBuilder::genNullInst(); }  // Result not used

/*****************************************************************************
 BINARY OPERATION
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateBinOp(Tree sig, int opcode, Tree a1, Tree a2)
{
    int t1 = getCertifiedSigType(a1)->nature();
    int t2 = getCertifiedSigType(a2)->nature();
    int t3 = getCertifiedSigType(sig)->nature();
  
    ValueInst* res;
    ValueInst* v1 = CS(a1);
    ValueInst* v2 = CS(a2);
    
    interval i = getCertifiedSigType(a1)->getInterval();
    interval j = getCertifiedSigType(a2)->getInterval();

    if (j.haszero()) {
        // potential division by zero
        //std::cerr << "WARNING : potential division by zero (" << i << "/" << j << ") in " << ppsig(sig) << std::endl;
    }
  
    // Logical operations work on kInt32, so cast both operands here
    if (isLogicalOpcode(opcode)) {
        res = InstBuilder::genBinopInst(opcode, promote2int(t1, v1), promote2int(t2, v2));
        res = cast2real(t3, res);
    // Boolean operations work on kInt32 or kReal, result is kInt32
    } else if (isBoolOpcode(opcode)) {
        if ((t1 == kReal) || (t2 == kReal)) {
            res = InstBuilder::genBinopInst(opcode, promote2real(t1, v1), promote2real(t2, v2));
        } else {
            res = InstBuilder::genBinopInst(opcode, v1, v2);
        }
        // HACK for Rust backend
        if (gGlobal->gOutputLang == "rust") {
            res = InstBuilder::genCastNumIntInst(res);
        }
    // One of a1 or a2 is kReal, operation is done on kReal
    } else if ((t1 == kReal) || (t2 == kReal)) {
        res = cast2int(t3, InstBuilder::genBinopInst(opcode, promote2real(t1, v1), promote2real(t2, v2)));
    // Otherwise kInt32 operation
    } else if (opcode == kDiv) {
        // special handling for division, we always want a float division
        res = cast2int(t3, InstBuilder::genBinopInst(opcode, promote2real(t1, v1), promote2real(t2, v2)));
    } else {
        res = cast2real(t3, InstBuilder::genBinopInst(opcode, v1, v2));
    }
    
    return generateCacheCode(sig, res);
}

/*****************************************************************************
 Primitive Operations
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateFFun(Tree sig, Tree ff, Tree largs)
{
    fContainer->addIncludeFile(ffincfile(ff));
	fContainer->addLibrary(fflibfile(ff));
    string funname = ffname(ff);
    
    if (!gGlobal->gAllowForeignFunction) {
        stringstream error;
        error << "ERROR : calling foreign function '"<< funname  << "'" << " is not allowed in this compilation mode!" << endl;
        throw faustexception(error.str());
    }
   
    list<ValueInst*> args_value;
    list<NamedTyped*> args_types;
 
    for (int i = 0; i< ffarity(ff); i++) {
        stringstream num; num << i;
        Tree parameter = nth(largs, i);
        // Reversed...
        int sig_argtype = ffargtype(ff, (ffarity(ff) - 1) - i);
        BasicTyped* argtype = genBasicFIRTyped(sig_argtype);
        args_types.push_back(InstBuilder::genNamedTyped("dummy" + num.str(), argtype));
        args_value.push_back(InstBuilder::genCastInst(CS(parameter), argtype));
    }
   
    // Add function declaration
    FunTyped* fun_type = InstBuilder::genFunTyped(args_types, genBasicFIRTyped(ffrestype(ff)));
    pushExtGlobalDeclare(InstBuilder::genDeclareFunInst(funname, fun_type));
 
    return generateCacheCode(sig, InstBuilder::genCastInst(InstBuilder::genFunCallInst(funname, args_value), genBasicFIRTyped(ffrestype(ff))));
}

/*****************************************************************************
 INPUTS - OUTPUTS
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateInput(Tree sig, int idx)
{
    // 09/12/11 : HACK
    //int rate = getSigRate(sig);
    int rate = 1;
    fContainer->setInputRate(idx, rate);
    
    // Cast to internal float
    ValueInst* res;
    // HACK for Rust backend
    if (gGlobal->gOutputLang == "rust") {
        res = InstBuilder::genCastNumFloatInst(InstBuilder::genLoadArrayStackVar(subst("inputs[$0]", T(idx)), getCurrentLoopIndex()));
    } else {
        res = InstBuilder::genCastNumFloatInst(InstBuilder::genLoadArrayStackVar(subst("input$0", T(idx)), getCurrentLoopIndex()));
    }

    if (gGlobal->gInPlace) {
        // inputs must be cached for in-place transformations
        return forceCacheCode(sig, res);
    } else {
        return generateCacheCode(sig, res);
    }
}

/*****************************************************************************
 TABLES
 *****************************************************************************/

/*----------------------------------------------------------------------------
 sigTable : table declaration
 ----------------------------------------------------------------------------*/

ValueInst* InstructionsCompiler::generateTable(Tree sig, Tree tsize, Tree content)
{
    ValueInst* generator = CS(content);
    Typed::VarType ctype;
    Tree g;
    string vname;
    int size;

    // already compiled but check if we need to add declarations
    faustassert(isSigGen(content, g));
    pair<string, string> kvnames;
    if (!fInstanceInitProperty.get(g, kvnames)) {
        // not declared here, we add a declaration
        bool b = fStaticInitProperty.get(g, kvnames);
        faustassert(b);
        list<ValueInst*> args;
        if (gGlobal->gMemoryManager) {
            args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
        }
        ValueInst* obj = InstBuilder::genFunCallInst("new" + kvnames.first, args);
        pushInitMethod(InstBuilder::genDecStackVar(kvnames.second, InstBuilder::genNamedTyped(kvnames.first, InstBuilder::genBasicTyped(Typed::kObj_ptr)), obj));

        // HACK for Rust backend
        if (gGlobal->gOutputLang != "rust") {
            // Delete object
            list<ValueInst*> args3;
            if (gGlobal->gMemoryManager) {
                args3.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
            }
            args3.push_back(generator);
            pushPostInitMethod(InstBuilder::genVoidFunCallInst("delete" + kvnames.first, args3));
        }
    }

	if (!isSigInt(tsize, &size)) {
	    stringstream error;
        error << "error in InstructionsCompiler::generateTable() : "
			 << *tsize
			 << " is not an integer expression "
			 << endl;
        throw faustexception(error.str());
	}

	// Define table name and type
    getTypedNames(getCertifiedSigType(content), "tbl", ctype, vname);

    // Table declaration
    pushDeclare(InstBuilder::genDecStructVar(vname, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), size)));

    string tablename;
    getTableNameProperty(content, tablename);

    // Init content generator
    list<ValueInst*> args1;
    args1.push_back(generator);
    args1.push_back(InstBuilder::genLoadFunArgsVar("samplingFreq"));
    pushInitMethod(InstBuilder::genVoidFunCallInst("instanceInit" + tablename, args1, true));

    // Fill the table
    list<ValueInst*> args2;
    args2.push_back(generator);
    args2.push_back(InstBuilder::genInt32NumInst(size));
    // HACK for Rust backend
    args2.push_back(InstBuilder::genLoadMutRefStructVar(vname));
    pushInitMethod(InstBuilder::genVoidFunCallInst("fill" + tablename, args2, true));

    // Return table access
    return InstBuilder::genLoadStructVar(vname);
}

ValueInst* InstructionsCompiler::generateStaticTable(Tree sig, Tree tsize, Tree content)
{
    Tree g;
    ValueInst* 	cexp;
    Typed::VarType ctype;
    string vname;
    int size;

	ensure(isSigGen(content, g));

	if (!getCompiledExpression(content, cexp)) {
		cexp = setCompiledExpression(content, generateStaticSigGen(content, g));
	} else {
        // already compiled but check if we need to add declarations
        pair<string, string> kvnames;
        if (!fStaticInitProperty.get(g, kvnames)) {
            // not declared here, we add a declaration
            bool b = fInstanceInitProperty.get(g, kvnames);
            faustassert(b);
            list<ValueInst*> args;
            if (gGlobal->gMemoryManager) {
                args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
            }
            ValueInst* obj = InstBuilder::genFunCallInst("new" + kvnames.first, args);
            pushInitMethod(InstBuilder::genDecStackVar(kvnames.second, InstBuilder::genNamedTyped(kvnames.first, InstBuilder::genBasicTyped(Typed::kObj_ptr)), obj));

            // HACK for Rust backend
            if (gGlobal->gOutputLang != "rust") {
                // Delete object
                list<ValueInst*> args3;
                if (gGlobal->gMemoryManager) {
                    args3.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
                }
                args3.push_back(cexp);
                pushPostInitMethod(InstBuilder::genVoidFunCallInst("delete" + kvnames.first, args3));
            }
        }
    }

    if (!isSigInt(tsize, &size)) {
	    stringstream error;
        error << "error in InstructionsCompiler::generateStaticTable() : "
			  << *tsize
			  << " is not an integer expression "
			  << endl;
        throw faustexception(error.str());
  	}
    
	// Define table name and type
    getTypedNames(getCertifiedSigType(content), "tbl", ctype, vname);

    string tablename;
    getTableNameProperty(content, tablename);
    vname += tablename;
    
    // Table declaration
    if (gGlobal->gMemoryManager) {
        pushGlobalDeclare(InstBuilder::genDecStaticStructVar(vname, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), 0), InstBuilder::genInt32NumInst(0)));
    } else {
        pushGlobalDeclare(InstBuilder::genDecStaticStructVar(vname, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), size)));
    }
 
    // Init content generator
    list<ValueInst*> args1;
    args1.push_back(cexp);
    args1.push_back(InstBuilder::genLoadFunArgsVar("samplingFreq"));
    pushStaticInitMethod(InstBuilder::genVoidFunCallInst("instanceInit" + tablename, args1, true));
    
    if (gGlobal->gMemoryManager) {
        list<ValueInst*> alloc_args;
        alloc_args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
        alloc_args.push_back(InstBuilder::genInt32NumInst(size * Typed::getSizeOf(ctype)));
        pushStaticInitMethod(InstBuilder::genStoreStaticStructVar(vname,
                                                                  InstBuilder::genCastInst(InstBuilder::genFunCallInst("allocate", alloc_args, true),
                                                                                              InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), 0))));
        
        list<ValueInst*> destroy_args;
        destroy_args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
        destroy_args.push_back(InstBuilder::genLoadStaticStructVar(vname));
        pushStaticDestroyMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("destroy", destroy_args, true)));
    }

    // Fill the table
    list<ValueInst*> args2;
    args2.push_back(cexp);
    args2.push_back(InstBuilder::genInt32NumInst(size));
    // HACK for Rust backend
    args2.push_back(InstBuilder::genLoadStaticMutRefStructVar(vname));
    pushStaticInitMethod(InstBuilder::genVoidFunCallInst("fill" + tablename, args2, true));

    // Return table access
    return InstBuilder::genLoadStaticStructVar(vname);
}

/*----------------------------------------------------------------------------
 sigWRTable : table assignement
 ----------------------------------------------------------------------------*/

ValueInst* InstructionsCompiler::generateWRTbl(Tree sig, Tree tbl, Tree idx, Tree data)
{
    ValueInst* tblname = CS(tbl);
    LoadVarInst* load_value = dynamic_cast<LoadVarInst*>(tblname);
    faustassert(load_value);
    
    // Check types and possibly cast written value
    int table_type = getCertifiedSigType(tbl)->nature();
    int data_type = getCertifiedSigType(data)->nature();
     
    pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(load_value->fAddress->getName(), 
                                                             CS(idx), 
                                                             (table_type != data_type) ? InstBuilder::genCastInst(CS(data), genBasicFIRTyped(table_type)) : CS(data)));

    // Return table access
    return InstBuilder::genLoadStructVar(load_value->fAddress->getName());
}

/*----------------------------------------------------------------------------
 sigRDTable : table access
 ----------------------------------------------------------------------------*/

ValueInst* InstructionsCompiler::generateRDTbl(Tree sig, Tree tbl, Tree idx)
{
    // Test the special case of a read only table that can be compiled as a static member
	Tree id, size, content;
    ValueInst* tblname;
    Address::AccessType access;

    if (isSigTable(tbl, id, size, content)) {
        access = Address::kStaticStruct;
        if (!getCompiledExpression(tbl, tblname)) {
            tblname = setCompiledExpression(tbl, generateStaticTable(tbl, size, content));
        }
    } else {
        access = Address::kStruct;
        tblname = CS(tbl);
    }

    LoadVarInst* load_value1 = dynamic_cast<LoadVarInst*>(tblname);
    faustassert(load_value1);

    LoadVarInst* load_value2 = InstBuilder::genLoadArrayVar(load_value1->fAddress->getName(), access, CS(idx));
    return generateCacheCode(sig, load_value2);
}

ValueInst* InstructionsCompiler::generateSigGen(Tree sig, Tree content)
{
    string cname = gGlobal->getFreshID(fContainer->getClassName() + "SIG");
    string signame = gGlobal->getFreshID("sig");

    CodeContainer* subcontainer = signal2Container(cname, content);
	fContainer->addSubContainer(subcontainer);

    // We must allocate an object of type "cname"
    list<ValueInst*> args;
    if (gGlobal->gMemoryManager) {
        args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
    }
    ValueInst* obj = InstBuilder::genFunCallInst("new" + cname, args);
    pushInitMethod(InstBuilder::genDecStackVar(signame, InstBuilder::genNamedTyped(cname, InstBuilder::genBasicTyped(Typed::kObj_ptr)), obj));

    // HACK for Rust backend
    if (gGlobal->gOutputLang != "rust") {
        // Delete object
        list<ValueInst*> args3;
        args3.push_back(InstBuilder::genLoadStackVar(signame));
        if (gGlobal->gMemoryManager) {
            args3.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
        }
        pushPostInitMethod(InstBuilder::genVoidFunCallInst("delete" + cname, args3));
    }

    setTableNameProperty(sig, cname);
    fInstanceInitProperty.set(content, pair<string, string>(cname, signame));

    return InstBuilder::genLoadStackVar(signame);
}

ValueInst* InstructionsCompiler::generateStaticSigGen(Tree sig, Tree content)
{
    string cname = gGlobal->getFreshID(fContainer->getClassName() + "SIG");
    string signame = gGlobal->getFreshID("sig");

	CodeContainer* subcontainer = signal2Container(cname, content);
	fContainer->addSubContainer(subcontainer);

   // We must allocate an object of type "cname"
    list<ValueInst*> args;
    if (gGlobal->gMemoryManager) {
        args.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
    }
    ValueInst* obj = InstBuilder::genFunCallInst("new" + cname, args);
    pushStaticInitMethod(InstBuilder::genDecStackVar(signame, InstBuilder::genNamedTyped(cname, InstBuilder::genBasicTyped(Typed::kObj_ptr)), obj));

    // HACK for Rust backend
    if (gGlobal->gOutputLang != "rust") {
        // Delete object
        list<ValueInst*> args3;
        args3.push_back(InstBuilder::genLoadStackVar(signame));
        if (gGlobal->gMemoryManager) {
            args3.push_back(InstBuilder::genLoadStaticStructVar("fManager"));
        }
        pushPostStaticInitMethod(InstBuilder::genVoidFunCallInst("delete" + cname, args3));
    }

    setTableNameProperty(sig, cname);
    fStaticInitProperty.set(content, pair<string,string>(cname, signame));

    return InstBuilder::genLoadStackVar(signame);
}

ValueInst* InstructionsCompiler::generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2)
{
    ValueInst* cond = CS(sel);
    ValueInst* v1 = CS(s1);
    ValueInst* v2 = CS(s2);
    
    int t1 = getCertifiedSigType(s1)->nature();
    int t2 = getCertifiedSigType(s2)->nature();
     
    ::Type type = getCertifiedSigType(s1);
    
    // Type promotion
    if ((t1 == kReal) || (t2 == kReal)) {
        v1 = promote2real(t1, v1);
        v2 = promote2real(t2, v2);
    }
    
    if (gGlobal->gGenerateSelectWithIf && (type->variability() == kSamp) && (!dynamic_cast<SimpleValueInst*>(v1) || !dynamic_cast<SimpleValueInst*>(v2))) {
        return generateSelect2WithIf(sig, (((t1 == kReal) || (t2 == kReal)) ? itfloat() : Typed::kInt32), cond, v1, v2);
    } else {
        return generateSelect2WithSelect(sig, cond, v1, v2);
    }
}

ValueInst* InstructionsCompiler::generateSelect2WithSelect(Tree sig, ValueInst* sel, ValueInst* v1, ValueInst* v2)
{
    return generateCacheCode(sig, InstBuilder::genSelect2Inst(sel, v2, v1));
}

ValueInst* InstructionsCompiler::generateSelect2WithIf(Tree sig, Typed::VarType type, ValueInst* sel, ValueInst* v1, ValueInst* v2)
{
    ValueInst* cond = InstBuilder::genNotEqual(sel, InstBuilder::genInt32NumInst(0));
    string vname = gGlobal->getFreshID(((type == Typed::kInt32) ? "iSel" :"fSel"));
    BlockInst* block1 = InstBuilder::genBlockInst();
    BlockInst* block2 = InstBuilder::genBlockInst();
    
    block1->pushBackInst(InstBuilder::genStoreStackVar(vname, v1));
    block2->pushBackInst(InstBuilder::genStoreStackVar(vname, v2));
    DeclareVarInst* var = InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(type), InstBuilder::genTypedZero(type));
      
    /* 
    generateSelect2WithIf only called for kSamp code for now 
    (otherwise generated "sel" variables are not correctly handled in -sch mode when they are moved from "compute" to "computeThread").
    */
    pushComputeDSPMethod(var);
    pushComputeDSPMethod(InstBuilder::genIfInst(cond, block2, block1));
    
    /*
    switch (type->variability()) {
        
        case kBlock:
            pushComputeBlockMethod(var);
            pushComputeBlockMethod(InstBuilder::genIfInst(cond, block2, block1));
            break;
        
        case kSamp:
        case kKonst:
            pushComputeDSPMethod(var);
            pushComputeDSPMethod(InstBuilder::genIfInst(cond, block2, block1));
            break;
    }
    */
    
    return generateCacheCode(sig, InstBuilder::genLoadStackVar(vname));
}

ValueInst* InstructionsCompiler::generateSelect3(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3)
{
    // Done at signal level
    faustassert(false);
    return InstBuilder::genNullInst();
}

/*****************************************************************************
 RECURSIONS
 *****************************************************************************/

/**
 * Generate code for a projection of a group of mutually recursive definitions
 */
ValueInst* InstructionsCompiler::generateRecProj(Tree sig, Tree r, int i)
{
    string vname;
    Tree var, le;
    ValueInst* res;

    if (!getVectorNameProperty(sig, vname)) {
        ensure(isRec(r, var, le));
        res = generateRec(r, var, le, i);
        ensure(getVectorNameProperty(sig, vname));
    } else {
        res = InstBuilder::genNullInst(); // Result not used
    }
    return res;
}

/**
 * Generate code for a group of mutually recursive definitions
 */
ValueInst* InstructionsCompiler::generateRec(Tree sig, Tree var, Tree le, int index)
{
    int N = len(le);

    ValueInst* res = NULL;
    vector<bool> used(N);
    vector<int> delay(N);
    vector<string> vname(N);
    vector<Typed::VarType> ctype(N);

    // Prepare each element of a recursive definition
    for (int i = 0; i < N; i++) {
        Tree e = sigProj(i, sig);     // recreate each recursive definition
        if (fOccMarkup.retrieve(e)) {
            // This projection is used
            used[i] = true;
            getTypedNames(getCertifiedSigType(e), "Rec", ctype[i], vname[i]);
            setVectorNameProperty(e, vname[i]);
            delay[i] = fOccMarkup.retrieve(e)->getMaxDelay();
        } else {
            // This projection is not used therefore
            // we should not generate code for it
            used[i] = false;
        }
    }

    // Generate delayline for each element of a recursive definition
    for (int i = 0; i < N; i++) {
        if (used[i]) {
            Address::AccessType var_access;
            if (index == i) {
                res = generateDelayLine(CS(nth(le,i)), ctype[i], vname[i], delay[i], var_access);
            } else {
                generateDelayLine(CS(nth(le,i)), ctype[i], vname[i], delay[i], var_access);
            }
        }
    }

    return res;
}

/*****************************************************************************
 CASTING
 *****************************************************************************/

// Generate cast only when really necessary...
ValueInst* InstructionsCompiler::generateIntCast(Tree sig, Tree x)
{
    return generateCacheCode(sig, (getCertifiedSigType(x)->nature() != kInt) ? InstBuilder::genCastNumIntInst(CS(x)) : CS(x)); 
}

// Generate cast only when really necessary...
ValueInst* InstructionsCompiler::generateFloatCast(Tree sig, Tree x)
{
    return generateCacheCode(sig, (getCertifiedSigType(x)->nature() != kReal) ? InstBuilder::genCastNumFloatInst(CS(x)) : CS(x)); 
}

/*****************************************************************************
 user interface elements
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateButtonAux(Tree sig, Tree path, const string& name)
{
    string varname = gGlobal->getFreshID(name);
    Typed* type = InstBuilder::genBasicTyped(Typed::kFloatMacro);

    pushDeclare(InstBuilder::genDecStructVar(varname, type));
    pushResetUIInstructions(InstBuilder::genStoreStructVar(varname, InstBuilder::genRealNumInst(Typed::kFloatMacro, 0)));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // Cast to internal float
    return generateCacheCode(sig, InstBuilder::genCastNumFloatInst(InstBuilder::genLoadStructVar(varname)));
}

ValueInst* InstructionsCompiler::generateButton(Tree sig, Tree path)
{
    return generateButtonAux(sig, path, "fButton");
}

ValueInst* InstructionsCompiler::generateCheckbox(Tree sig, Tree path)
{
    return generateButtonAux(sig, path, "fCheckbox");
}

ValueInst* InstructionsCompiler::generateSliderAux(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step, const string& name)
{
    string varname = gGlobal->getFreshID(name);
    Typed* type = InstBuilder::genBasicTyped(Typed::kFloatMacro);

    pushDeclare(InstBuilder::genDecStructVar(varname, type));
    pushResetUIInstructions(InstBuilder::genStoreStructVar(varname, InstBuilder::genRealNumInst(Typed::kFloatMacro, tree2float(cur))));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // Cast to internal float
    return generateCacheCode(sig, InstBuilder::genCastNumFloatInst(InstBuilder::genLoadStructVar(varname)));
}

ValueInst* InstructionsCompiler::generateVSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    return generateSliderAux(sig, path, cur, min, max, step, "fVslider");
}
ValueInst* InstructionsCompiler::generateHSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    return generateSliderAux(sig, path, cur, min, max, step, "fHslider");
}

ValueInst* InstructionsCompiler::generateNumEntry(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    return generateSliderAux(sig, path, cur, min, max, step, "fEntry");
}

ValueInst* InstructionsCompiler::generateBargraphAux(Tree sig, Tree path, Tree min, Tree max, ValueInst* exp, const string& name)
{
    string varname = gGlobal->getFreshID(name);
    pushDeclare(InstBuilder::genDecStructVar(varname, InstBuilder::genBasicTyped(Typed::kFloatMacro)));
 	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

	::Type t = getCertifiedSigType(sig);
    
    // Cast to external float
    StoreVarInst* res = InstBuilder::genStoreStructVar(varname, InstBuilder::genCastNumFloatMacroInst(exp));
    
	switch (t->variability()) {

        case kKonst:
            pushResetUIInstructions(res);
            break;

        case kBlock:
            pushComputeBlockMethod(res);
            break;

        case kSamp:
            pushComputeDSPMethod(res);
            break;
	}

    return generateCacheCode(sig, (t->nature() == kInt)
        ? InstBuilder::genCastNumIntInst(InstBuilder::genLoadStructVar(varname))
        : InstBuilder::genLoadStructVar(varname));
}

ValueInst* InstructionsCompiler::generateVBargraph(Tree sig, Tree path, Tree min, Tree max, ValueInst* exp)
{
    return generateBargraphAux(sig, path, min, max, exp, "fVbargraph");
}

ValueInst* InstructionsCompiler::generateHBargraph(Tree sig, Tree path, Tree min, Tree max, ValueInst* exp)
{
    return generateBargraphAux(sig, path, min, max, exp, "fHbargraph");
}

ValueInst* InstructionsCompiler::generateIntNumber(Tree sig, int num)
{
    Occurences* o = fOccMarkup.retrieve(sig);

	// Check for number occuring in delays
	if (o->getMaxDelay() > 0) {
        Typed::VarType ctype;
        string vname;
		getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
		generateDelayVec(sig, InstBuilder::genInt32NumInst(num), ctype, vname, o->getMaxDelay());
	}

    // No cache for numbers
    return InstBuilder::genInt32NumInst(num);
}

ValueInst* InstructionsCompiler::generateRealNumber(Tree sig, double num)
{
    Typed::VarType ctype = itfloat();
 	Occurences* o = fOccMarkup.retrieve(sig);

	// Check for number occuring in delays
	if (o->getMaxDelay() > 0) {
        string vname;
		getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
		generateDelayVec(sig, InstBuilder::genRealNumInst(ctype, num), ctype, vname, o->getMaxDelay());
	}

    // No cache for numbers
    return InstBuilder::genRealNumInst(ctype, num);
}

ValueInst* InstructionsCompiler::generateFConst(Tree sig, Tree type, const string& file, const string& name)
{
    Typed::VarType ctype;
    string vname;
	Occurences* o = fOccMarkup.retrieve(sig);

    fContainer->addIncludeFile(file);

    // Keep SR generation state
    if (name == "fSamplingFreq") {
        fContainer->setGeneratedSR();
    }

	// Check for number occuring in delays
	if (o->getMaxDelay() > 0) {
		getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
		generateDelayVec(sig, (name == "fSamplingFreq") ? InstBuilder::genLoadStructVar(name) : InstBuilder::genLoadGlobalVar(name), ctype, vname, o->getMaxDelay());
	}

    int sig_type = getCertifiedSigType(sig)->nature();
    if (name == "fSamplingFreq") {
        pushDeclare(InstBuilder::genDecStructVar(name, genBasicFIRTyped(sig_type)));
        return InstBuilder::genLoadStructVar(name);
    } else {
        pushExtGlobalDeclare(InstBuilder::genDecGlobalVar(name, genBasicFIRTyped(sig_type)));
        return InstBuilder::genLoadGlobalVar(name);
    }
}

/*****************************************************************************
 FOREIGN VARIABLES
 *****************************************************************************/

ValueInst* InstructionsCompiler::generateFVar(Tree sig, Tree type, const string& file, const string& name)
{
    fContainer->addIncludeFile(file);

    int sig_type = getCertifiedSigType(sig)->nature();
    pushExtGlobalDeclare(InstBuilder::genDecGlobalVar(name, genBasicFIRTyped(sig_type)));
    return generateCacheCode(sig, InstBuilder::genLoadGlobalVar(name));
}

ValueInst* InstructionsCompiler::generateDelayVec(Tree sig, ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd)
{
    setVectorNameProperty(sig, vname);
    Address::AccessType var_access;
    return generateDelayLine(exp, ctype, vname, mxd, var_access);
}

StatementInst* InstructionsCompiler::generateInitArray(const string& vname, Typed::VarType ctype, int delay)
{
    ValueInst* init = InstBuilder::genTypedZero(ctype);
    BasicTyped* typed = InstBuilder::genBasicTyped(ctype);
    string index = gGlobal->getFreshID("l");

    // Generates table declaration
    pushDeclare(InstBuilder::genDecStructVar(vname, InstBuilder::genArrayTyped(typed, delay)));

    // Generates init table loop
    DeclareVarInst* loop_decl = InstBuilder::genDecLoopVar(index, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(0));
    ValueInst* loop_end = InstBuilder::genLessThan(loop_decl->load(), InstBuilder::genInt32NumInst(delay));
    StoreVarInst* loop_inc = loop_decl->store(InstBuilder::genAdd(loop_decl->load(), 1));

    ForLoopInst* loop = InstBuilder::genForLoopInst(loop_decl, loop_end, loop_inc);

    loop->pushFrontInst(InstBuilder::genStoreArrayStructVar(vname, loop_decl->load(), init));
    return loop;
}

StatementInst* InstructionsCompiler::generateShiftArray(const string& vname, int delay)
{
    string index = gGlobal->getFreshID("j");

    // Generates init table loop
    DeclareVarInst* loop_decl = InstBuilder::genDecLoopVar(index, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(delay));
    ValueInst* loop_end = InstBuilder::genGreaterThan(loop_decl->load(), InstBuilder::genInt32NumInst(0));
    StoreVarInst* loop_inc = loop_decl->store(InstBuilder::genSub(loop_decl->load(), InstBuilder::genInt32NumInst(1)));

    ForLoopInst* loop = InstBuilder::genForLoopInst(loop_decl, loop_end, loop_inc);
    ValueInst* load_value2 = InstBuilder::genSub(loop_decl->load(), InstBuilder::genInt32NumInst(1));
    ValueInst* load_value3 = InstBuilder::genLoadArrayStructVar(vname, load_value2);

    loop->pushFrontInst(InstBuilder::genStoreArrayStructVar(vname, loop_decl->load(), load_value3));
    return loop;
}

StatementInst* InstructionsCompiler::generateCopyArray(const string& vname, int index_from, int index_to)
{
    ValueInst* inst1 = InstBuilder::genLoadArrayStructVar(vname, InstBuilder::genInt32NumInst(index_from));
    return InstBuilder::genStoreArrayStructVar(vname, InstBuilder::genInt32NumInst(index_to), inst1);
}

StatementInst* InstructionsCompiler::generateCopyArray(const string& vname_to, const string& vname_from, int size)
{
    string index = gGlobal->getFreshID("j");

    // Generates init table loop
    DeclareVarInst* loop_decl = InstBuilder::genDecLoopVar(index, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(0));
    ValueInst* loop_end = InstBuilder::genLessThan(loop_decl->load(), InstBuilder::genInt32NumInst(size));
    StoreVarInst* loop_inc = loop_decl->store(InstBuilder::genAdd(loop_decl->load(), 1));

    ForLoopInst* loop = InstBuilder::genForLoopInst(loop_decl, loop_end, loop_inc);
    ValueInst* load_value = InstBuilder::genLoadArrayStructVar(vname_from, loop_decl->load());

    loop->pushFrontInst(InstBuilder::genStoreArrayStackVar(vname_to, loop_decl->load(), load_value));
    return loop;
}

ValueInst* InstructionsCompiler::generateDelayLine(ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd, Address::AccessType& var_access)
{
    if (mxd == 0) {

        // Generate scalar use
        pushComputeDSPMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), exp));

   } else if (mxd < gGlobal->gMaxCopyDelay) {

        // Generates table init
        pushClearMethod(generateInitArray(vname, ctype, mxd + 1));

        // Generate table use
        pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(vname, InstBuilder::genInt32NumInst(0), exp));

        // Generates post processing copy code to update delay values
        if (mxd == 1) {
            pushComputePostDSPMethod(generateCopyArray(vname, 0, 1));
        } else if (mxd == 2) {
            pushComputePostDSPMethod(generateCopyArray(vname, 1, 2));
            pushComputePostDSPMethod(generateCopyArray(vname, 0, 1));
        } else {
            pushComputePostDSPMethod(generateShiftArray(vname, mxd));
        }

    } else {
        
        // Generate code for a long delay : we use a ring buffer of size N = 2**x > mxd
        int N = pow2limit(mxd + 1);

        // We need an iota index
        ensureIotaCode();

        // Generates table init
        pushClearMethod(generateInitArray(vname, ctype, N));

        // Generate table use
        if (gGlobal->gComputeIOTA) {  // Ensure IOTA base fixed delays are computed once
            if (fIOTATable.find(N) == fIOTATable.end()) {
                string iota_name = subst("i$0", gGlobal->getFreshID("IOTA_temp"));
                FIRIndex value2 = FIRIndex(InstBuilder::genLoadStructVar("IOTA")) & InstBuilder::genInt32NumInst(N - 1);
                pushComputeDSPMethod(InstBuilder::genDecStackVar(iota_name, InstBuilder::genBasicTyped(Typed::kInt32), value2));
                fIOTATable[N] = iota_name;
            }
            pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(vname, InstBuilder::genLoadStackVar(fIOTATable[N]), exp));
        } else {
            FIRIndex value2 = FIRIndex(InstBuilder::genLoadStructVar("IOTA")) & InstBuilder::genInt32NumInst(N - 1);
            pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(vname, value2, exp));
        }
    }

    return exp;
}

/*****************************************************************************
 IOTA(n)
 *****************************************************************************/

/**
 * Generate code for a unique IOTA variable increased at each sample
 * and used to index ring buffers.
 */
void InstructionsCompiler::ensureIotaCode()
{
    if (!fLoadedIota) {
        fLoadedIota = true;

        pushDeclare(InstBuilder::genDecStructVar("IOTA", InstBuilder::genBasicTyped(Typed::kInt32)));
        pushClearMethod(InstBuilder::genStoreStructVar("IOTA", InstBuilder::genInt32NumInst(0)));

        FIRIndex value = FIRIndex(InstBuilder::genLoadStructVar("IOTA")) + 1;
        pushComputePostDSPMethod(InstBuilder::genStoreStructVar("IOTA", value));
    }
}

/**
 * Add a widget with a certain path to the user interface tree
 */
void InstructionsCompiler::addUIWidget(Tree path, Tree widget)
{
	fUIRoot = putSubFolder(fUIRoot, path, widget);
}

/**
 * Remove fake root folder if not needed (that is if the UI
 * is completely enclosed in one folder)
 */
Tree InstructionsCompiler::prepareUserInterfaceTree(Tree t)
{
	Tree root, elems;
	if (isUiFolder(t, root, elems) && isList(elems) && isNil(tl(elems)) ) {
		Tree folder = right(hd(elems));
		return (isUiFolder(folder)) ? folder : t;
	}
	return t;
}

//================================= BUILD USER INTERFACE METHOD =================================

/**
 * Generate buildUserInterface C++ lines of code corresponding
 * to user interface element t
 */
void InstructionsCompiler::generateUserInterfaceTree(Tree t, bool root)
{
	Tree label, elements, varname, sig;

	if (isUiFolder(t, label, elements)) {
		const int orient = tree2int(left(label));
        // Empty labels will be renamed with a 0xABCD (address) that is ignored and not displayed by UI architectures
		string str = tree2str(right(label));
      
        // extract metadata from group label str resulting in a simplifiedLabel
		// and metadata declarations for fictive zone at address 0
        string simplifiedLabel;
        map<string, set<string> > metadata;
        extractMetadata(str, simplifiedLabel, metadata);

        // add metadata if any
        for (map<string, set<string> >::iterator i = metadata.begin(); i != metadata.end(); i++) {
            const string& key = i->first;
            const set<string>& values = i->second;
            for (set<string>::const_iterator j = values.begin(); j != values.end(); j++) {
                pushUserInterfaceMethod(InstBuilder::genAddMetaDeclareInst("0", rmWhiteSpaces(key), rmWhiteSpaces(*j)));
            }
        }
        // At rool level and if label is empty, use the name kept in "metadata" (either the one coded in 'declare name "XXX";' line, or the filename)
        string group = (root && (simplifiedLabel == "")) ? unquote(tree2str(*(gGlobal->gMetaDataSet[tree("name")].begin()))) : checkNullLabel(t, simplifiedLabel);
        
        pushUserInterfaceMethod(InstBuilder::genOpenboxInst(orient, group));
        generateUserInterfaceElements(elements);
        pushUserInterfaceMethod(InstBuilder::genCloseboxInst());

	} else if (isUiWidget(t, label, varname, sig)) {

		generateWidgetCode(label, varname, sig);

	} else {
        throw faustexception("ERROR in user interface generation\n");
	}
}

/**
 * Iterate generateUserInterfaceTree on a list of user interface elements
 */
void InstructionsCompiler::generateUserInterfaceElements(Tree elements)
{
  	while (!isNil(elements)) {
       	generateUserInterfaceTree(right(hd(elements)));
		elements = tl(elements);
	}
}

/**
 * Generate buildUserInterface C++ lines of code corresponding
 * to user interface widget t
 */
void InstructionsCompiler::generateWidgetCode(Tree fulllabel, Tree varname, Tree sig)
{
	Tree path, c, x, y, z;
    string label;
    map<string, set<string> > metadata;

    extractMetadata(tree2str(fulllabel), label, metadata);

    // Add metadata if any
    for (map<string, set<string> >::iterator i = metadata.begin(); i != metadata.end(); i++) {
        const string& key = i->first;
        const set<string>& values = i->second;
        for (set<string>::const_iterator j = values.begin(); j != values.end(); j++) {
            pushUserInterfaceMethod(InstBuilder::genAddMetaDeclareInst(tree2str(varname), rmWhiteSpaces(key), rmWhiteSpaces(*j)));
        }
    }

	if (isSigButton(sig, path)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(InstBuilder::genAddButtonInst(checkNullLabel(varname, label), tree2str(varname)));

	} else if (isSigCheckbox(sig, path)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(InstBuilder::genAddCheckbuttonInst(checkNullLabel(varname, label), tree2str(varname)));

	} else if (isSigVSlider(sig, path,c,x,y,z)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(
            InstBuilder::genAddVerticalSliderInst(checkNullLabel(varname, label), tree2str(varname), tree2float(c), tree2float(x), tree2float(y), tree2float(z)));

	} else if (isSigHSlider(sig, path,c,x,y,z))	{
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(
            InstBuilder::genAddHorizontalSliderInst(checkNullLabel(varname, label), tree2str(varname), tree2float(c), tree2float(x), tree2float(y), tree2float(z)));

	} else if (isSigNumEntry(sig, path,c,x,y,z)) {
        fContainer->incUIActiveCount();
        pushUserInterfaceMethod(
            InstBuilder::genAddNumEntryInst(checkNullLabel(varname, label), tree2str(varname), tree2float(c), tree2float(x), tree2float(y), tree2float(z)));

	} else if (isSigVBargraph(sig, path,x,y,z))	{
        fContainer->incUIPassiveCount();
        pushUserInterfaceMethod(
            InstBuilder::genAddVerticalBargraphInst(checkNullLabel(varname, label, true), tree2str(varname),  tree2float(x), tree2float(y)));

	} else if (isSigHBargraph(sig, path,x,y,z))	{
        fContainer->incUIPassiveCount();
 	    pushUserInterfaceMethod(
            InstBuilder::genAddHorizontalBargraphInst(checkNullLabel(varname, label, true), tree2str(varname), tree2float(x), tree2float(y)));

	} else {
		throw faustexception("ERROR in generating widget code\n");
	}
}

//==================================== USER INTERFACE MACROS ==================================

/**
 * Generate user interface macros corresponding
 * to user interface element t
 */
void InstructionsCompiler::generateMacroInterfaceTree(const string& pathname, Tree t)
{
	Tree label, elements, varname, sig;

	if (isUiFolder(t, label, elements)) {
		string pathname2 = pathname;
		//string str = unquote(tree2str(right(label)));
		string str = tree2str(right(label));
		if (str.length() > 0) pathname2 += str + "/";
		generateMacroInterfaceElements(pathname2, elements);
    } else if (isUiWidget(t, label, varname, sig)) {
		generateWidgetMacro(pathname, label, varname, sig);
	} else {
        throw faustexception("ERROR in user interface macro generation\n");
	}
}

/**
 * Iterate generateMacroInterfaceTree on a list of user interface elements
 */
void InstructionsCompiler::generateMacroInterfaceElements(const string& pathname, Tree elements)
{
	while (!isNil(elements)) {
		generateMacroInterfaceTree(pathname, right(hd(elements)));
		elements = tl(elements);
	}
}

/**
 * Generate user interface macros corresponding
 * to a user interface widget
 */
void InstructionsCompiler::generateWidgetMacro(const string& pathname, Tree fulllabel, Tree varname, Tree sig)
{
	Tree path, c, x, y, z;
    string label;
    map<string, set<string> > metadata;

    extractMetadata(tree2str(fulllabel), label, metadata);

    //string pathlabel = pathname+unquote(label);
	string pathlabel = pathname+label;

	if (isSigButton(sig, path)) 					{
		fContainer->addUIMacro(subst("FAUST_ADDBUTTON(\"$0\", $1);", pathlabel, tree2str(varname)));

	} else if (isSigCheckbox(sig, path)) 			{
		fContainer->addUIMacro(subst("FAUST_ADDCHECKBOX(\"$0\", $1);", pathlabel, tree2str(varname)));

	} else if (isSigVSlider(sig, path,c,x,y,z))	{
		fContainer->addUIMacro(subst("FAUST_ADDVERTICALSLIDER(\"$0\", $1, $2, $3, $4, $5);",
                                pathlabel,
                                tree2str(varname),
                                T(tree2float(c)),
                                T(tree2float(x)),
                                T(tree2float(y)),
                                T(tree2float(z))));

	} else if (isSigHSlider(sig, path,c,x,y,z))	{
		fContainer->addUIMacro(subst("FAUST_ADDHORIZONTALSLIDER(\"$0\", $1, $2, $3, $4, $5);",
                                pathlabel,
                                tree2str(varname),
                                T(tree2float(c)),
                                T(tree2float(x)),
                                T(tree2float(y)),
                                T(tree2float(z))));

	} else if (isSigNumEntry(sig, path,c,x,y,z))	{
		fContainer->addUIMacro(subst("FAUST_ADDNUMENTRY(\"$0\", $1, $2, $3, $4, $5);",
                                pathlabel,
                                tree2str(varname),
                                T(tree2float(c)),
                                T(tree2float(x)),
                                T(tree2float(y)),
                                T(tree2float(z))));

	} else if (isSigVBargraph(sig, path,x,y,z))	{
		fContainer->addUIMacro(subst("FAUST_ADDVERTICALBARGRAPH(\"$0\", $1, $2, $3);",
                                pathlabel,
                                tree2str(varname),
                                T(tree2float(x)),
                                T(tree2float(y))));

	} else if (isSigHBargraph(sig, path,x,y,z))	{
		fContainer->addUIMacro(subst("FAUST_ADDHORIZONTALBARGRAPH(\"$0\", $1, $2, $3);",
                                pathlabel,
                                tree2str(varname),
                                T(tree2float(x)),
                                T(tree2float(y))));

	} else {
	     throw faustexception("ERROR in generating widget code\n");
	}
}

/**
 * Generate code for a waveform. The waveform will be declared as a static field.
 * The name of the waveform is returned in vname and its size in size.
 */
void InstructionsCompiler::declareWaveform(Tree sig, string& vname, int& size)
{
   // computes C type and unique name for the waveform

    Typed::VarType ctype;
    getTypedNames(getCertifiedSigType(sig), fContainer->getClassName() + "Wave", ctype, vname);
    size = sig->arity();
    
    // Declares the Waveform
    Typed* type = InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), size);
    ValueInst* num_array = InstBuilder::genArrayNumInst(ctype, size);
    
    double r;
    int i;
        
    if (ctype == Typed::kInt32) {
        Int32ArrayNumInst* int_array = dynamic_cast<Int32ArrayNumInst*>(num_array);
        for (int k = 0; k < size; k++) {
            if (isSigInt(sig->branch(k), &i)) {   
                int_array->setValue(k, i);
            } else if (isSigReal(sig->branch(k), &r)) {
                int_array->setValue(k, int(r));
            }
        }
    } else if (ctype == Typed::kFloat) {
        FloatArrayNumInst* float_array = dynamic_cast<FloatArrayNumInst*>(num_array);
        for (int k = 0; k < size; k++) {
            if (isSigInt(sig->branch(k), &i)) {   
                float_array->setValue(k, float(i));
            } else if (isSigReal(sig->branch(k), &r)) {
                float_array->setValue(k, float(r));
            }
        }
    } else if (ctype == Typed::kDouble) {
        DoubleArrayNumInst* double_array = dynamic_cast<DoubleArrayNumInst*>(num_array);
        for (int k = 0; k < size; k++) {
            if (isSigInt(sig->branch(k), &i)) {   
                double_array->setValue(k, double(i));
            } else if (isSigReal(sig->branch(k), &r)) {
                double_array->setValue(k, r);
            }
        }
    } else {
        faustassert(false);
    }
    
    if (gGlobal->gWaveformInDSP) {
        // waveform are allocated in the DSP and not as global data
        pushStaticInitMethod(InstBuilder::genDecStaticStructVar(vname, type, num_array));
    } else {
        pushGlobalDeclare(InstBuilder::genDecStaticStructVar(vname, type, num_array));
    }
    
    string idx = subst("$0_idx", vname);
    pushDeclare(InstBuilder::genDecStructVar(idx, InstBuilder::genBasicTyped(Typed::kInt32)));
    pushInitMethod(InstBuilder::genStoreStructVar(idx, InstBuilder::genInt32NumInst(0)));
}

ValueInst* InstructionsCompiler::generateWaveform(Tree sig)
{
    string vname;
    int size;

    declareWaveform(sig, vname, size);
    
    string idx = subst("$0_idx", vname);
    FIRIndex index = (FIRIndex(1) + InstBuilder::genLoadStructVar(idx)) % InstBuilder::genInt32NumInst(size);
    pushComputePostDSPMethod(InstBuilder::genStoreStructVar(idx, index));
    return generateCacheCode(sig, InstBuilder::genLoadArrayStaticStructVar(vname, InstBuilder::genLoadStructVar(idx)));
}
