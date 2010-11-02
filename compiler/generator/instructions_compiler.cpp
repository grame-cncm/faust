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

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
#include <string>
#include <list>
#include <set>
#include <map>
#include <vector>

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

using namespace std;

// globals

extern int gMaxCopyDelay;
extern bool gVectorSwitch;
extern int gVecSize;

std::ostream* Printable::fOut = &cout;

/*****************************************************************************
						getFreshID
*****************************************************************************/

map<string, int> InstructionsCompiler::fIDCounters;

string InstructionsCompiler::getFreshID(const string& prefix)
{
	if (fIDCounters.find(prefix) == fIDCounters.end()) {
		fIDCounters[prefix] = 0;
	}
	int n = fIDCounters[prefix];
	fIDCounters[prefix] = n+1;
	return subst("$0$1", prefix, T(n));
}

/*****************************************************************************
						    prepare
*****************************************************************************/

// Taken form sharing.cpp

int InstructionsCompiler::getSharingCount(Tree sig)
{
	//cerr << "getSharingCount of : " << *sig << " = ";
	Tree c;
	if (getProperty(sig, fSharingKey, c)) {
		//cerr << c->node().getInt() << endl;
		return c->node().getInt();
	} else {
		//cerr << 0 << endl;
		return 0;
	}
}

void InstructionsCompiler::setSharingCount(Tree sig, int count)
{
	//cerr << "setSharingCount of : " << *sig << " <- " << count << endl;
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
	Tree	c, x, y, z;

	//cerr << "START sharing annotation of " << *sig << endl;
	int count = getSharingCount(sig);

	if (count > 0) {
		// it is not our first visit
		setSharingCount(sig, count+1);

	} else {
		// it is our first visit,
		int v = getSigType(sig)->variability();

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
			if (n>0 && ! isSigGen(sig)) {
				for (int i=0; i<n; i++) sharingAnnotation(v, subsig[i]);
			}
		}
	}
	//cerr << "END sharing annotation of " << *sig << endl;
}

Tree InstructionsCompiler::prepare(Tree LS)
{
 startTiming("CodeLlvmScalarCompiler::prepare");
	sharingAnalysis(LS);			// annotate L3 with sharing count
  	fOccMarkup.mark(LS);			// annotate L3 with occurences analysis
 endTiming("CodeLlvmScalarCompiler::prepare");
  	return LS;
}

Tree InstructionsCompiler::prepare2(Tree L0)
{
 startTiming("CodeLlvmScalarCompiler::prepare2");
	recursivnessAnnotation(L0);		// Annotate L0 with recursivness information
	typeAnnotation(L0);				// Annotate L0 with type information
	sharingAnalysis(L0);			// annotate L0 with sharing count
 	fOccMarkup.mark(L0);			// annotate L0 with occurences analysis
 endTiming("CodeLlvmScalarCompiler::prepare2");
  	return L0;
}

void InstructionsCompiler::getTypedNames(::Type t, const string& prefix, Typed::VarType& ctype, string& vname)
{
    if (t->nature() == kInt) {
        ctype = Typed::kInt;
        vname = subst("i$0", getFreshID(prefix));
    } else {
        ctype = itfloat();
        vname = subst("f$0", getFreshID(prefix));
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
 * @param vecname the string representing the vector name.
 * @return true is already compiled
 */
void InstructionsCompiler::setVectorNameProperty(Tree sig, const string& vecname)
{
    assert(vecname.size() > 0);
    fVectorProperty.set(sig, vecname);
}

/**
 * Get the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vecname the string where to store the vector name.
 * @return true if the signal has this property, false otherwise
 */

bool InstructionsCompiler::getVectorNameProperty(Tree sig, string& vecname)
{
    return fVectorProperty.get(sig, vecname);
}

void InstructionsCompiler::setTableNameProperty(Tree sig, const string& name)
{
    assert(name.size() > 0);
    fTableProperty.set(sig, name);
}

bool InstructionsCompiler::getTableNameProperty(Tree sig, string& name)
{
    return fTableProperty.get(sig, name);
}

CodeContainer* InstructionsCompiler::signal2Container(const string& name, Tree sig)
{
	Type t = getSigType(sig); 

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

    // Needed in the global variable table
    //fContainer->pushDeclare(InstBuilder::genDeclareVarInst("count", InstBuilder::genBasicTyped(Typed::kInt), Address::kFunArgs));
    //fContainer->pushDeclare(InstBuilder::genDeclareVarInst("samplingFreq", InstBuilder::genBasicTyped(Typed::kInt), Address::kFunArgs));

    // "input" and "inputs" used as a name convention
    for (int index = 0; index < fContainer->inputs(); index++) {
        string name = subst("input$0", T(index));

        //if (!gVectorSwitch) {
            fContainer->pushComputeBlockMethod(
                InstBuilder::genDeclareVarInst(name, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(Typed::kFloatMacro), 0), Address::kStack,
                    InstBuilder::genLoadVarInst(
                        InstBuilder::genIndexedAddress(
                            InstBuilder::genNamedAddress("inputs", Address::kFunArgs), InstBuilder::genIntNumInst(index)))));
        /*
        } else {
             fContainer->pushComputeBlockMethod(
                InstBuilder::genDeclareVarInst(name, InstBuilder::genArrayTyped(InstBuilder::genVectorTyped(InstBuilder::genBasicTyped(xfloat()), gVecSize), 0), Address::kStack,
                    InstBuilder::genLoadVarInst(
                        InstBuilder::genIndexedAddress(
                            InstBuilder::genNamedAddress("inputs", Address::kFunArgs), InstBuilder::genIntNumInst(index)))));
        }
        */
    }

    // "output" and "outputs" used as a name convention
    for (int index = 0; index < fContainer->outputs(); index++) {
        string name = subst("output$0", T(index));

        //if (!gVectorSwitch) {
            fContainer->pushComputeBlockMethod(
                InstBuilder::genDeclareVarInst(name, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(Typed::kFloatMacro), 0), Address::kStack,
                    InstBuilder::genLoadVarInst(
                        InstBuilder::genIndexedAddress(
                            InstBuilder::genNamedAddress("outputs", Address::kFunArgs), InstBuilder::genIntNumInst(index)))));

        /*
        } else {
             fContainer->pushComputeBlockMethod(
                InstBuilder::genDeclareVarInst(name, InstBuilder::genArrayTyped(InstBuilder::genVectorTyped(InstBuilder::genBasicTyped(xfloat()), gVecSize), 0), Address::kStack,
                    InstBuilder::genLoadVarInst(
                        InstBuilder::genIndexedAddress(
                            InstBuilder::genNamedAddress("outputs", Address::kFunArgs), InstBuilder::genIntNumInst(index)))));
        }
        */
    }

	for (int index = 0; isList(L); L = tl(L), index++) {
		Tree sig = hd(L);
        string name = subst("output$0", T(index));

        // Cast to external float
        ValueInst* res = InstBuilder::genCastNumInst(CS(kSamp, sig), InstBuilder::genBasicTyped(Typed::kFloatMacro));

        fContainer->getCurLoop()->pushComputeDSPMethod(
            InstBuilder::genStoreVarInst(
                InstBuilder::genIndexedAddress(
                    InstBuilder::genNamedAddress(name, Address::kStack),
                        InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("i", Address::kLoop))), res));
    }

	generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
	generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
	if (fDescription) {
		fDescription->ui(prepareUserInterfaceTree(fUIRoot));
	}
}

/*****************************************************************************
						    compileSingleSignal
*****************************************************************************/

void InstructionsCompiler::compileSingleSignal(Tree sig)
{
  	sig = prepare2(sig);		// Optimize and annotate expression
    string name = "output";

    fContainer->getCurLoop()->pushComputeDSPMethod(
            InstBuilder::genStoreVarInst(
                InstBuilder::genIndexedAddress(
                    InstBuilder::genNamedAddress(name, Address::kFunArgs),
                        InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("i", Address::kLoop))), CS(kSamp, sig)));

	generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
	generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
	if (fDescription) {
		fDescription->ui(prepareUserInterfaceTree(fUIRoot));
	}
}

ValueInst* InstructionsCompiler::generateCode(int variability, Tree sig)
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

		 if ( getUserData(sig) ) 					{ return generateXtended(variability, sig); }
	else if ( isSigInt(sig, &i) ) 					{ return generateIntNumber(variability, sig, i); }
	else if ( isSigReal(sig, &r) ) 					{ return generateRealNumber(variability, sig, r); }
	else if ( isSigInput(sig, &i) ) 				{ return generateInput(variability, sig, i); }

	else if ( isSigFixDelay(sig, x, y) ) 			{ return generateFixDelay(variability, sig, x, y); }
	else if ( isSigPrefix(sig, x, y) ) 				{ return generatePrefix(variability, sig, x, y); }
	else if ( isSigIota(sig, x) ) 					{ return generateIota(variability, sig, x); }

	else if ( isSigBinOp(sig, &i, x, y) )			{ return generateBinOp(variability, sig, i, x, y); }
	else if ( isSigFFun(sig, ff, largs) )			{ return generateFFun(variability, sig, ff, largs); }
    else if ( isSigFConst(sig, type, name, file) )  { return generateFConst(variability, sig, type, tree2str(file), tree2str(name)); }
    else if ( isSigFVar(sig, type, name, file) )    { return generateFVar(variability, sig, type, tree2str(file), tree2str(name)); }

	else if ( isSigTable(sig, id, x, y) ) 			{ return generateTable(variability, sig, x, y); }
	else if ( isSigWRTbl(sig, id, x, y, z) )		{ return generateWRTbl(variability, sig, x, y, z); }
	else if ( isSigRDTbl(sig, x, y) ) 				{ return generateRDTbl(variability, sig, x, y); }

	else if ( isSigSelect2(sig, sel, x, y) ) 		{ return generateSelect2(variability, sig, sel, x, y); }
	else if ( isSigSelect3(sig, sel, x, y, z) ) 	{ return generateSelect3(variability, sig, sel, x, y, z); }

	else if ( isSigGen(sig, x) ) 					{ return generateSigGen(variability, sig, x); }

    else if ( isProj(sig, &i, x) )                  { return generateRecProj(variability, sig, x, i); }

	else if ( isSigIntCast(sig, x) ) 				{ return generateIntCast(variability, sig, x); }
	else if ( isSigFloatCast(sig, x) ) 				{ return generateFloatCast(variability, sig, x); }

	else if ( isSigButton(sig, label) ) 			{ return generateButton(variability, sig, label); }
	else if ( isSigCheckbox(sig, label) ) 			{ return generateCheckbox(variability, sig, label); }
	else if ( isSigVSlider(sig, label,c,x,y,z) )	{ return generateVSlider(variability, sig, label, c, x, y, z); }
	else if ( isSigHSlider(sig, label,c,x,y,z) )	{ return generateHSlider(variability, sig, label, c, x, y, z); }
	else if ( isSigNumEntry(sig, label,c,x,y,z) )	{ return generateNumEntry(variability, sig, label, c, x, y, z); }


	else if ( isSigVBargraph(sig, label,x,y,z) )	{ return generateVBargraph(variability, sig, label, x, y, CS(variability, z)); }
	else if ( isSigHBargraph(sig, label,x,y,z) )	{ return generateHBargraph(variability, sig, label, x, y, CS(variability, z)); }
	else if ( isSigAttach(sig, x, y) )				{ CS(variability, y); return generateCacheCode(sig, CS(variability, x)); }
    else if (isSigVectorize(sig, x, y)) {
        printf("vectorize not implemented\n");
        exit (0);
    }
    else if (isSigSerialize(sig, x)) {
        printf("serialize not implemented\n");
        exit (0);
    }
    else if (isSigConcat(sig, x, y)) {
        printf("concatenation not implemented\n");
        exit (0);
    }
    else if (isSigVectorAt(sig, x, y)) {
        printf("vector at not implemented\n");
        exit (0);
    }
	else {
		printf("Error in compiling signal, unrecognized signal : ");
		print(sig);
		printf("\n");
		exit(1);
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

    // Check for expression occuring in delays
	if (o->getMaxDelay() > 0) {

        getTypedNames(getSigType(sig), "Vec", ctype, vname);
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
        cerr << "Error in sharing count (" << sharing << ") for " << *sig << endl;
		exit(1);
	}
}

ValueInst* InstructionsCompiler::CS(int variability, Tree sig)
{
    ValueInst* code;

    if (!getCompiledExpression(sig, code)) {
        code = generateCode(variability, sig);
        setCompiledExpression(sig, code);
    }
    return code;
}

ValueInst* InstructionsCompiler::generateVariableStore(Tree sig, ValueInst* exp)
{
    string vname;
    Typed::VarType ctype;
    ::Type t = getSigType(sig);

    switch (t->variability()) {

        case kKonst:

            getTypedNames(t, "Const", ctype, vname);
            //if (!gVectorSwitch) {
                fContainer->pushDeclare(InstBuilder::genDeclareVarInst(vname, InstBuilder::genBasicTyped(ctype), Address::kStruct));
            //} else {
            //    fContainer->pushDeclare(InstBuilder::genDeclareVarInst(vname, InstBuilder::genVectorTyped(InstBuilder::genBasicTyped(ctype), gVecSize), Address::kStruct));
            //}
            fContainer->pushInitMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(vname, Address::kStruct), exp));
            return InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(vname, Address::kStruct));

        case kBlock:

            getTypedNames(t, "Slow", ctype, vname);
            //if (!gVectorSwitch) {
                fContainer->pushComputeBlockMethod(InstBuilder::genDeclareVarInst(vname, InstBuilder::genBasicTyped(ctype), Address::kStack, exp));
            //} else {
            //    fContainer->pushComputeBlockMethod(InstBuilder::genDeclareVarInst(vname,
            //        InstBuilder::genVectorTyped(InstBuilder::genBasicTyped(ctype), gVecSize), Address::kStack, exp));
            //}
            return InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(vname, Address::kStack));

        case kSamp:

            getTypedNames(t, "Temp", ctype, vname);
            //if (!gVectorSwitch) {
                fContainer->getCurLoop()->pushComputeDSPMethod(InstBuilder::genDeclareVarInst(vname, InstBuilder::genBasicTyped(ctype), Address::kStack, exp));
            //} else {
            //    fContainer->getCurLoop()->pushComputeDSPMethod(InstBuilder::genDeclareVarInst(vname,
            //        InstBuilder::genVectorTyped(InstBuilder::genBasicTyped(ctype), gVecSize), Address::kStack, exp));
            //}
            return InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(vname, Address::kStack));

        default:
            return InstBuilder::genNullInst();
    }
}

ValueInst* InstructionsCompiler::generateXtended(int variability, Tree sig)
{
    xtended* p = (xtended*)getUserData(sig);
	list<ValueInst*> args;
    vector< ::Type> arg_types;
    ::Type result_type = getSigType(sig);

	for (int i = 0; i < sig->arity(); i++) {
		args.push_back(CS(variability, sig->branch(i)));
		arg_types.push_back(getSigType(sig->branch(i)));
	}

	if (p->needCache()) {
		return generateCacheCode(sig, p->generateCode(variability, fContainer, args, result_type, arg_types));
	} else {
		return p->generateCode(variability, fContainer, args, result_type, arg_types);
	}
}

ValueInst* InstructionsCompiler::generateFixDelay(int variability, Tree sig, Tree exp, Tree delay)
{
    int mxd;
	string vecname;

    ValueInst* value = CS(variability, exp); // ensure exp is compiled to have a vector name
    mxd = fOccMarkup.retrieve(exp)->getMaxDelay();

	if (!getVectorNameProperty(exp, vecname)) {
        cerr << "No vector name for : " << ppsig(exp) << endl;
        assert(0);
    }

    if (mxd == 0) {
        return value; // TO CHECK
	} else if (mxd < gMaxCopyDelay) {
		return InstBuilder::genLoadVarInst(InstBuilder::genIndexedAddress(InstBuilder::genNamedAddress(vecname, Address::kStruct), CS(variability, delay)));
	} else {
		// Long delay : we use a ring buffer of size 2^x
		int N = pow2limit(mxd + 1);

        ValueInst* value1 = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("IOTA", Address::kStruct));
        ValueInst* value2 = InstBuilder::genBinopInst(kSub, value1, CS(variability, delay));
        ValueInst* value3 = InstBuilder::genBinopInst(kAND, value2, InstBuilder::genIntNumInst(N - 1));
        return InstBuilder::genLoadVarInst(InstBuilder::genIndexedAddress(InstBuilder::genNamedAddress(vecname, Address::kStruct), value3));
    }
}

ValueInst* InstructionsCompiler::generatePrefix(int variability, Tree sig, Tree x, Tree e)
{
    ::Type te = getSigType(sig);

	string vperm = getFreshID("M");
	string vtemp = getFreshID("T");

   Typed::VarType type = ctType(te);

    // Table declaration
    fContainer->pushDeclare(InstBuilder::genDeclareVarInst(vperm, InstBuilder::genBasicTyped(type), Address::kStruct));

    // Init
    fContainer->pushInitMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(vperm, Address::kStruct), CS(variability, x)));

    // Exec
    fContainer->getCurLoop()->pushComputeDSPMethod(
        InstBuilder::genDeclareVarInst(vtemp, InstBuilder::genBasicTyped(type), Address::kStack,
            InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(vperm, Address::kStruct))));
    fContainer->getCurLoop()->pushComputeDSPMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(vperm, Address::kStruct), CS(variability, e)));

    return InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(vtemp, Address::kStack));
}

ValueInst* InstructionsCompiler::generateIota(int variability, Tree sig, Tree arg) { return InstBuilder::genNullInst(); }  // Not used

ValueInst* InstructionsCompiler::generateBinOp(int variability, Tree sig, int opcode, Tree arg1, Tree arg2)
{
    int t1 = getSigType(arg1)->nature();
    int t2 = getSigType(arg2)->nature();
    int t3 = getSigType(sig)->nature();

    ValueInst* res = NULL;
    ValueInst* val1 = CS(variability, arg1);
    ValueInst* val2 = CS(variability, arg2);

    // Arguments and expected result type analysis, add the required "cast" when needed
    if (t1 == kReal) {
        if (t2 == kReal) {
            res = InstBuilder::genBinopInst(opcode, val1, val2);
            if (t3 == kReal) {
                // Nothing
            } else {
                res = InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(Typed::kInt));
            }
        } else {
            res = InstBuilder::genBinopInst(opcode, val1, InstBuilder::genCastNumInst(val2, InstBuilder::genBasicTyped(itfloat())));
            if (t3 == kReal) {
                // Nothing
            } else {
                res = InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(Typed::kInt));
            }
        }
    } else if (t2 == kReal) {
        res = InstBuilder::genBinopInst(opcode, InstBuilder::genCastNumInst(val1, InstBuilder::genBasicTyped(itfloat())), val2);
        if (t3 == kReal) {
            // Nothing
        } else {
            res = InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(Typed::kInt));
        }
    } else {
        res = InstBuilder::genBinopInst(opcode, val1, val2);
        if (t3 == kReal) {
            res = InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(itfloat()));
        } else {
            // Nothing
        }
    }

    assert(res);
    return generateCacheCode(sig, res);
}

// TODO
ValueInst* InstructionsCompiler::generateFFun(int variability, Tree sig, Tree ff, Tree largs)
{
    fContainer->addIncludeFile(ffincfile(ff));
	fContainer->addLibrary(fflibfile(ff));

    string funname = ffname(ff);
    list<ValueInst*> args_value;
    list<NamedTyped*> args_types;
    FunTyped* fun_type;

    for (int i = 0; i< ffarity(ff); i++) {
        stringstream num; num << i;
        Tree parameter = nth(largs, i);
        ::Type t1 = getSigType(parameter);
        args_types.push_back(InstBuilder::genNamedTyped("dummy" + num.str(), InstBuilder::genBasicTyped((t1->nature() == kInt) ? Typed::kInt : itfloat())));
        args_value.push_back(CS(variability, parameter));
    }

    // Add function declaration
    fun_type = InstBuilder::genFunTyped(args_types, InstBuilder::genBasicTyped((ffrestype(ff) == kInt) ? Typed::kInt : itfloat()));
    fContainer->pushGlobalDeclare(InstBuilder::genDeclareFunInst(funname, fun_type));

    return generateCacheCode(sig, InstBuilder::genFunCallInst(funname, args_value));
}

ValueInst* InstructionsCompiler::generateInput(int variability, Tree sig, int idx)
{
    // "input" use as a name convention
    string name = subst("input$0", T(idx));
    ValueInst* res = InstBuilder::genLoadVarInst(
                        InstBuilder::genIndexedAddress(
                            InstBuilder::genNamedAddress(name, Address::kStack),
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("i", Address::kLoop))));
    // Cast to internal float
    res = InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(itfloat()));
    return generateCacheCode(sig, res);
}

ValueInst* InstructionsCompiler::generateTable(int variability, Tree sig, Tree tsize, Tree content)
{
    ValueInst* 	generator = CS(variability, content);
    Typed::VarType ctype;
	string		vname;
	int 		size;

	if (!isSigInt(tsize, &size)) {
		cerr << "error in ScalarCompiler::generateTable() : "
			 << *tsize
			 << " is not an integer expression "
			 << endl;
        exit(1);
	}

	// definition du nom et du type de la table
	// A REVOIR !!!!!!!!!
	Type t = getSigType(content);//, tEnv);
	if (t->nature() == kInt) {
		vname = getFreshID("itbl");
		ctype = Typed::kInt;
	} else {
		vname = getFreshID("ftbl");
		ctype = itfloat();
	}

    // Table declaration
    fContainer->pushDeclare(InstBuilder::genDeclareVarInst(vname, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), size), Address::kStruct));

    string tablename;
    getTableNameProperty(content, tablename);

    // Init content generator
    list<ValueInst*> args1;
    args1.push_back(generator);
    args1.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("samplingFreq", Address::kFunArgs)));
    fContainer->pushInitMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("instanceInit" + tablename, args1, true)));

    // Fill the table
    list<ValueInst*> args2;
    args2.push_back(generator);
    args2.push_back(InstBuilder::genIntNumInst(size));
    args2.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(vname, Address::kStruct)));
    fContainer->pushInitMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("fill" + tablename, args2, true)));

    // Delete object
    list<ValueInst*> args3;
    args3.push_back(generator);
    fContainer->pushInitMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("delete" + tablename, args3)));

    // Return table access
    return InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(vname, Address::kStruct));
}

ValueInst* InstructionsCompiler::generateStaticTable(int variability, Tree sig, Tree tsize, Tree content)
{
    Tree        g;
	ValueInst* 	cexp;
    Typed::VarType ctype;
	string      vname;
	int         size;

	assert(isSigGen(content, g));

	if (!getCompiledExpression(content, cexp)) {
		cexp = setCompiledExpression(content, generateStaticSigGen(variability, content, g));
	}

    if (!isSigInt(tsize, &size)) {
		//fprintf(stderr, "error in ScalarCompiler::generateTable()\n"); exit(1);
		cerr << "error in ScalarCompiler::generateTable() : "
			 << *tsize
			 << " is not an integer expression "
			 << endl;
        exit(1);
	}
	// definition du nom et du type de la table
	// A REVOIR !!!!!!!!!
	Type t = getSigType(content);//, tEnv);
	if (t->nature() == kInt) {
		vname = getFreshID("itbl");
		ctype = Typed::kInt;
	} else {
		vname = getFreshID("ftbl");
		ctype = itfloat();
	}

    string tablename;
    getTableNameProperty(content, tablename);

    vname += tablename;

    // Table declaration
    fContainer->pushGlobalDeclare(InstBuilder::genDeclareVarInst(vname, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), size), Address::kStaticStruct));

    // Init content generator
    list<ValueInst*> args1;
    args1.push_back(cexp);
    args1.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("samplingFreq", Address::kFunArgs)));
    fContainer->pushStaticInitMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("instanceInit" + tablename, args1, true)));

    // Fill the table
    list<ValueInst*> args2;
    args2.push_back(cexp);
    args2.push_back(InstBuilder::genIntNumInst(size));
    args2.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(vname, Address::kStaticStruct)));
    fContainer->pushStaticInitMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("fill" + tablename, args2, true)));

    // Delete object
    list<ValueInst*> args3;
    args3.push_back(cexp);
    fContainer->pushStaticInitMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("delete" + tablename, args3)));

    // Return table access
    return InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(vname, Address::kStaticStruct));
}

ValueInst* InstructionsCompiler::generateWRTbl(int variability, Tree sig, Tree tbl, Tree idx, Tree data)
{
    ValueInst* tblname = CS(variability, tbl);
    LoadVarInst* load_value = dynamic_cast<LoadVarInst*>(tblname);
    assert(load_value);

    StoreVarInst* store_inst = InstBuilder::genStoreVarInst(InstBuilder::genIndexedAddress(
                                                                InstBuilder::genNamedAddress(load_value->fAddress->getName(), Address::kStruct),
                                                                CS(variability, idx)),
                                                                CS(variability, data));
    fContainer->getCurLoop()->pushComputeDSPMethod(store_inst);

    // Return table access
    return InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(load_value->fAddress->getName(), Address::kStruct));
}

ValueInst* InstructionsCompiler::generateRDTbl(int variability, Tree sig, Tree tbl, Tree idx)
{
    // Test the special case of a read only table that can be compiled as a static member
	Tree id, size, content;
    ValueInst* tblname;
    Address::AccessType access;

	if (isSigTable(tbl, id, size, content)) {
        access = Address::kStaticStruct;
		if (!getCompiledExpression(tbl, tblname)) {
			tblname = setCompiledExpression(tbl, generateStaticTable(variability, tbl, size, content));
        }
	} else {
		tblname = CS(variability, tbl);
        access = Address::kStruct;
	}

    LoadVarInst* load_value1 = dynamic_cast<LoadVarInst*>(tblname);
    assert(load_value1);

    LoadVarInst* load_value2 = InstBuilder::genLoadVarInst(InstBuilder::genIndexedAddress(
        InstBuilder::genNamedAddress(load_value1->fAddress->getName(), access), CS(variability, idx)));

    return generateCacheCode(sig, load_value2);
}

ValueInst* InstructionsCompiler::generateSigGen(int variability, Tree sig, Tree content)
{
    string cname = getFreshID("SIG");
	string signame = getFreshID("sig");

    CodeContainer* subcontainer = signal2Container(cname, content);
	fContainer->addSubContainer(subcontainer);

    // We must allocate an object of type "cname"
    const list<ValueInst*> args;
    ValueInst* obj = InstBuilder::genFunCallInst("new" + cname, args);
    StatementInst* obj_decl =
        InstBuilder::genDeclareVarInst(signame, InstBuilder::genNamedTyped(cname, InstBuilder::genBasicTyped(Typed::kObj_ptr)), Address::kStack, obj);
    fContainer->pushInitMethod(obj_decl);

    setTableNameProperty(sig, cname);
    return InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(signame, Address::kStack));
}

ValueInst* InstructionsCompiler::generateStaticSigGen(int variability, Tree sig, Tree content)
{
    string cname = getFreshID("SIG");
	string signame = getFreshID("sig");

	CodeContainer* subcontainer = signal2Container(cname, content);
	fContainer->addSubContainer(subcontainer);

   // We must allocate an object of type "cname"
    const list<ValueInst*> args;
    ValueInst* obj = InstBuilder::genFunCallInst("new" + cname, args);
    StatementInst* obj_decl =
        InstBuilder::genDeclareVarInst(signame, InstBuilder::genNamedTyped(cname, InstBuilder::genBasicTyped(Typed::kObj_ptr)), Address::kStack, obj);
    fContainer->pushStaticInitMethod(obj_decl);

    setTableNameProperty(sig, cname);
    return InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(signame, Address::kStack));
}

ValueInst* InstructionsCompiler::generateSelect2(int variability, Tree sig, Tree sel, Tree s1, Tree s2)
{
    int t1 = getSigType(s1)->nature();
    int t2 = getSigType(s2)->nature();

    ValueInst* cond = CS(variability, sel);
    ValueInst* val1 = CS(variability, s1);
    ValueInst* val2 = CS(variability, s2);

    if (t1 == kReal) {
        if (t2 == kReal) {
            return generateCacheCode(sig, InstBuilder::genSelect2Inst(cond, val2, val1));
        } else {
            return generateCacheCode(sig, InstBuilder::genSelect2Inst(cond, InstBuilder::genCastNumInst(val2, InstBuilder::genBasicTyped(itfloat())), val1));
        }
    } else if (t2 == kReal) {
        return generateCacheCode(sig, InstBuilder::genSelect2Inst(cond, val2, InstBuilder::genCastNumInst(val1, InstBuilder::genBasicTyped(itfloat()))));
    } else {
        return generateCacheCode(sig, InstBuilder::genSelect2Inst(cond, val2, val1));
    }
}

ValueInst* InstructionsCompiler::generateSelect3(int variability, Tree sig, Tree sel, Tree s1, Tree s2, Tree s3)
{
    // TODO
    return InstBuilder::genNullInst();
}

ValueInst* InstructionsCompiler::generateRecProj(int variability, Tree sig, Tree r, int i)
{
    string vname;
    Tree var, le;
    ValueInst* res;

    if (!getVectorNameProperty(sig, vname)) {
        assert(isRec(r, var, le));
        res = generateRec(variability, r, var, le, i);
        assert(getVectorNameProperty(sig, vname));
    } else {
        res = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(vname, Address::kStack));
    }
    return res;
}

ValueInst* InstructionsCompiler::generateRec(int variability, Tree sig, Tree var, Tree le, int index)
{
    int N = len(le);

    ValueInst* res = NULL;
    vector<bool>    used(N);
    vector<int>     delay(N);
    vector<string>  vname(N);
    vector<Typed::VarType>  ctype(N);

    // Prepare each element of a recursive definition
    for (int i = 0; i < N; i++) {
        Tree e = sigProj(i, sig, unknown_box);     // recreate each recursive definition
        if (fOccMarkup.retrieve(e)) {
            // This projection is used
            used[i] = true;
            getTypedNames(getSigType(e), "Rec", ctype[i], vname[i]);
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
                res = generateDelayLine(CS(variability, nth(le,i)), ctype[i], vname[i], delay[i], var_access);
            } else {
                generateDelayLine(CS(variability, nth(le,i)), ctype[i], vname[i], delay[i], var_access);
            }
        }
    }

    return res;
}

ValueInst* InstructionsCompiler::generateIntCast(int variability, Tree sig, Tree x)
{
    return generateCacheCode(sig, InstBuilder::genCastNumInst(CS(variability, x), InstBuilder::genBasicTyped(Typed::kInt)));
}

ValueInst* InstructionsCompiler::generateFloatCast(int variability, Tree sig, Tree x)
{
    return generateCacheCode(sig, InstBuilder::genCastNumInst(CS(variability, x), InstBuilder::genBasicTyped(itfloat())));
}

ValueInst* InstructionsCompiler::generateButtonAux(int variability, Tree sig, Tree path, const string& name)
{
    string varname = getFreshID(name);
    //if (!gVectorSwitch) {
        fContainer->pushDeclare(InstBuilder::genDeclareVarInst(varname, InstBuilder::genBasicTyped(Typed::kFloatMacro), Address::kStruct));
    //} else {
    //    fContainer->pushDeclare(InstBuilder::genDeclareVarInst(varname,
    //        InstBuilder::genVectorTyped(InstBuilder::genBasicTyped(xfloat()), gVecSize), Address::kStruct));
    //}
    fContainer->pushInitMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(varname, Address::kStruct), InstBuilder::genRealNumInst(Typed::kFloatMacro, 0)));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    ValueInst* res = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(varname, Address::kStruct));
    return generateCacheCode(sig, InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(itfloat())));
}

ValueInst* InstructionsCompiler::generateButton(int variability, Tree sig, Tree path)
{
    return generateButtonAux(variability, sig, path, "fbutton");
}

ValueInst* InstructionsCompiler::generateCheckbox(int variability, Tree sig, Tree path)
{
    return generateButtonAux(variability, sig, path, "fcheckbox");
}

ValueInst* InstructionsCompiler::generateSliderAux(int variability, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step, const string& name)
{
    string varname = getFreshID(name);
    //if (!gVectorSwitch) {
        fContainer->pushDeclare(InstBuilder::genDeclareVarInst(varname, InstBuilder::genBasicTyped(Typed::kFloatMacro), Address::kStruct));
    //} else {
    //    fContainer->pushDeclare(InstBuilder::genDeclareVarInst(varname,
    //        InstBuilder::genVectorTyped(InstBuilder::genBasicTyped(xfloat()), gVecSize), Address::kStruct));
    //}
    fContainer->pushInitMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(varname, Address::kStruct), InstBuilder::genRealNumInst(Typed::kFloatMacro, tree2float(cur))));
    addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    ValueInst* res = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(varname, Address::kStruct));
    return generateCacheCode(sig, InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(itfloat())));
}

ValueInst* InstructionsCompiler::generateVSlider(int variability, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    return generateSliderAux(variability, sig, path, cur, min, max, step, "fvslider");
}
ValueInst* InstructionsCompiler::generateHSlider(int variability, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    return generateSliderAux(variability, sig, path, cur, min, max, step, "fhslider");
}

ValueInst* InstructionsCompiler::generateNumEntry(int variability, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    return generateSliderAux(variability, sig, path, cur, min, max, step, "fentry");
}

ValueInst* InstructionsCompiler::generateBargraphAux(int variability, Tree sig, Tree path, Tree min, Tree max, ValueInst* exp, const string& name)
{
    string varname = getFreshID(name);
    fContainer->pushDeclare(InstBuilder::genDeclareVarInst(varname, InstBuilder::genBasicTyped(Typed::kFloatMacro), Address::kStruct));
 	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

	::Type t = getSigType(sig);
	switch (t->variability()) {

		case kKonst :
            fContainer->pushInitMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(varname, Address::kStruct), exp));
			break;

		case kBlock :
            fContainer->pushComputeBlockMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(varname, Address::kStruct), exp));
			break;

		case kSamp :
	        fContainer->getCurLoop()->pushComputeDSPMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(varname, Address::kStruct), exp));
			break;
	}

    ValueInst* res = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(varname, Address::kStruct));
    return generateCacheCode(sig, InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(itfloat())));
}

ValueInst* InstructionsCompiler::generateVBargraph(int variability, Tree sig, Tree path, Tree min, Tree max, ValueInst* exp)
{
    return generateBargraphAux(variability, sig, path, min, max, exp, "fvbargraph");
}

ValueInst* InstructionsCompiler::generateHBargraph(int variability, Tree sig, Tree path, Tree min, Tree max, ValueInst* exp)
{
    return generateBargraphAux(variability, sig, path, min, max, exp, "fhbargraph");
}

ValueInst* InstructionsCompiler::generateIntNumber(int variability, Tree sig, int num)
{
    Typed::VarType ctype;
    string vname;
	Occurences* o = fOccMarkup.retrieve(sig);

	// Check for number occuring in delays
	if (o->getMaxDelay() > 0) {
		getTypedNames(getSigType(sig), "Vec", ctype, vname);
		generateDelayVec(sig, InstBuilder::genIntNumInst(num), ctype, vname, o->getMaxDelay());
	}

    // No cache for numbers
    return InstBuilder::genIntNumInst(num);
}

ValueInst* InstructionsCompiler::generateRealNumber(int variability, Tree sig, double num)
{
    Typed::VarType ctype = itfloat();
    string vname;
	Occurences* o = fOccMarkup.retrieve(sig);

	// Check for number occuring in delays
	if (o->getMaxDelay() > 0) {
		getTypedNames(getSigType(sig), "Vec", ctype, vname);
		generateDelayVec(sig, InstBuilder::genRealNumInst(ctype, num), ctype, vname, o->getMaxDelay());
	}

    // No cache for numbers
    return InstBuilder::genRealNumInst(ctype, num);
}

ValueInst* InstructionsCompiler::generateFConst(int variability, Tree sig, Tree type, const string& file, const string& name)
{
    Typed::VarType ctype;
    string vname;
	Occurences* o = fOccMarkup.retrieve(sig);
    int sig_type = getSigType(sig)->nature();

    fContainer->addIncludeFile(file);

	// Check for number occuring in delays
	if (o->getMaxDelay() > 0) {
		getTypedNames(getSigType(sig), "Vec", ctype, vname);
		generateDelayVec(sig, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(name, Address::kGlobal)), ctype, vname, o->getMaxDelay());
	}

    fContainer->pushGlobalDeclare(InstBuilder::genDeclareVarInst(name,
        InstBuilder::genBasicTyped((sig_type == kInt) ? Typed::kInt : itfloat()), Address::kGlobal));
    return InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(name, Address::kGlobal));
}

ValueInst* InstructionsCompiler::generateFVar(int variability, Tree sig, Tree type, const string& file, const string& name)
{
    fContainer->addIncludeFile(file);

    int sig_type = getSigType(sig)->nature();
    fContainer->pushGlobalDeclare(InstBuilder::genDeclareVarInst(name,
        InstBuilder::genBasicTyped((sig_type == kInt) ? Typed::kInt : itfloat()), Address::kGlobal));
    return InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(name, Address::kGlobal));
}

ValueInst* InstructionsCompiler::generateDelayVec(Tree sig, ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd)
{
    setVectorNameProperty(sig, vname);
    Address::AccessType var_access;
    return generateDelayLine(exp, ctype, vname, mxd, var_access);
}

StatementInst* InstructionsCompiler::generateInitArray(const string& vname, Typed::VarType ctype, int delay)
{
    ValueInst* init;
    BasicTyped* typed;
    string index = "i";

    if (ctype == Typed::kInt) {
        init = InstBuilder::genIntNumInst(0);
        typed = InstBuilder::genBasicTyped(Typed::kInt);
    } else {  // Real type
        init = InstBuilder::genRealNumInst(ctype, 0);
        typed = InstBuilder::genBasicTyped(ctype);
    }

    // Generates table declaration
    DeclareVarInst* table_inst = InstBuilder::genDeclareVarInst(vname, InstBuilder::genArrayTyped(typed, delay), Address::kStruct);
    fContainer->pushDeclare(table_inst);

    // Generates init table loop
    DeclareVarInst* loop_init = InstBuilder::genDeclareVarInst(index, InstBuilder::genBasicTyped(Typed::kInt), Address::kLoop, InstBuilder::genIntNumInst(0));

    ValueInst* loop_end = InstBuilder::genBinopInst(kLT,
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                InstBuilder::genIntNumInst(delay));
    StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                        InstBuilder::genBinopInst(kAdd,
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                    InstBuilder::genIntNumInst(1)));

    ForLoopInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment);

    loop->pushFrontInst(InstBuilder::genStoreVarInst(
                            InstBuilder::genIndexedAddress(
                                InstBuilder::genNamedAddress(vname, Address::kStruct),
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop))), init));
    return loop;
}

StatementInst* InstructionsCompiler::generateShiftArray(const string& vname, int delay)
{
    string index = "j";

    // Generates init table loop
    DeclareVarInst* loop_init = InstBuilder::genDeclareVarInst(index, InstBuilder::genBasicTyped(Typed::kInt), Address::kLoop, InstBuilder::genIntNumInst(delay));

    ValueInst* loop_end = InstBuilder::genBinopInst(kGT,
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                InstBuilder::genIntNumInst(0));
    StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                                            InstBuilder::genBinopInst(kSub,
                                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                                    InstBuilder::genIntNumInst(1)));

    ForLoopInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment);

    ValueInst* load_value1 = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop));
    ValueInst* load_value2 = InstBuilder::genBinopInst(kSub, load_value1, InstBuilder::genIntNumInst(1));
    ValueInst* load_value3 = InstBuilder::genLoadVarInst(
                                InstBuilder::genIndexedAddress(
                                    InstBuilder::genNamedAddress(vname, Address::kStruct), load_value2));

    loop->pushFrontInst(InstBuilder::genStoreVarInst(
                            InstBuilder::genIndexedAddress(
                                InstBuilder::genNamedAddress(vname, Address::kStruct),
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop))), load_value3));
    return loop;
}

StatementInst* InstructionsCompiler::generateCopyArray(const string& vname, int index_from, int index_to)
{
    ValueInst* inst1 = InstBuilder::genLoadVarInst(
                                    InstBuilder::genIndexedAddress(
                                        InstBuilder::genNamedAddress(vname, Address::kStruct), InstBuilder::genIntNumInst(index_from)));
    StatementInst* inst2 = InstBuilder::genStoreVarInst(
                                InstBuilder::genIndexedAddress(
                                    InstBuilder::genNamedAddress(vname, Address::kStruct), InstBuilder::genIntNumInst(index_to)), inst1);
    return inst2;
}

StatementInst* InstructionsCompiler::generateCopyArray(const string& vname_to, const string& vname_from, int size)
{
    string index = "j";

    // Generates init table loop
    DeclareVarInst* loop_init = InstBuilder::genDeclareVarInst(index, InstBuilder::genBasicTyped(Typed::kInt), Address::kLoop, InstBuilder::genIntNumInst(0));

    ValueInst* loop_end = InstBuilder::genBinopInst(kLT,
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                InstBuilder::genIntNumInst(size));
    StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                        InstBuilder::genBinopInst(kAdd,
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                    InstBuilder::genIntNumInst(1)));

    ForLoopInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment);

    ValueInst* load_value = InstBuilder::genLoadVarInst(InstBuilder::genIndexedAddress(
                                InstBuilder::genNamedAddress(vname_from, Address::kStruct),
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop))));

    loop->pushFrontInst(InstBuilder::genStoreVarInst(
                            InstBuilder::genIndexedAddress(
                                InstBuilder::genNamedAddress(vname_to, Address::kStack),
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop))), load_value));
    return loop;
}

StatementInst* InstructionsCompiler::generateCopyBackArray(const string& vname_to, const string& vname_from, int size)
{
    string index = "j";

    // Generates init table loop
    DeclareVarInst* loop_init = InstBuilder::genDeclareVarInst(index, InstBuilder::genBasicTyped(Typed::kInt), Address::kLoop, InstBuilder::genIntNumInst(0));

    ValueInst* loop_end = InstBuilder::genBinopInst(kLT,
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                InstBuilder::genIntNumInst(size));

    StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                        InstBuilder::genBinopInst(kAdd,
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                    InstBuilder::genIntNumInst(1)));

    ForLoopInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment);

    ValueInst* load_index = InstBuilder::genBinopInst(kAdd,
            InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("count", Address::kStack)),
            InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)));

    ValueInst* load_value = InstBuilder::genLoadVarInst(InstBuilder::genIndexedAddress(InstBuilder::genNamedAddress(vname_from, Address::kStack), load_index));

    loop->pushFrontInst(InstBuilder::genStoreVarInst(
                            InstBuilder::genIndexedAddress(
                                InstBuilder::genNamedAddress(vname_to, Address::kStruct),
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop))), load_value));
    return loop;
}

ValueInst* InstructionsCompiler::generateDelayLine(ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd, Address::AccessType& var_access)
{
    if (mxd == 0) {
    
        // Generate scalar use
        fContainer->getCurLoop()->pushComputeDSPMethod(
            InstBuilder::genDeclareVarInst(vname, InstBuilder::genBasicTyped(ctype), Address::kStack, exp));
        
    } else if (mxd < gMaxCopyDelay) {

        // Generates table init
        fContainer->pushInitMethod(generateInitArray(vname, ctype, mxd + 1));

        // Generate table use
        fContainer->getCurLoop()->pushComputeDSPMethod(InstBuilder::genStoreVarInst(
                                                            InstBuilder::genIndexedAddress(
                                                                InstBuilder::genNamedAddress(vname, Address::kStruct),
                                                                    InstBuilder::genIntNumInst(0)), exp));

        // Generates post processing copy code to update delay values
        if (mxd == 1) {
             fContainer->getCurLoop()->pushComputePostDSPMethod(generateCopyArray(vname, 0, 1));
        } else if (mxd == 2) {
            fContainer->getCurLoop()->pushComputePostDSPMethod(generateCopyArray(vname, 1, 2));
            fContainer->getCurLoop()->pushComputePostDSPMethod(generateCopyArray(vname, 0, 1));
        } else {
            fContainer->getCurLoop()->pushComputePostDSPMethod(generateShiftArray(vname, mxd));
        }

    } else {
        int N = pow2limit(mxd + 1);

        ensureIotaCode();

        // Generates table init
        fContainer->pushInitMethod(generateInitArray(vname, ctype, N));

        // Generate table use
        ValueInst* value1 = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("IOTA", Address::kStruct));
        ValueInst* value2 = InstBuilder::genBinopInst(kAND, value1, InstBuilder::genIntNumInst(N - 1));
        fContainer->getCurLoop()->pushComputeDSPMethod(InstBuilder::genStoreVarInst(
                                                            InstBuilder::genIndexedAddress(
                                                                InstBuilder::genNamedAddress(vname, Address::kStruct),
                                                                   value2), exp));
    }

    return exp;
}

void InstructionsCompiler::ensureIotaCode()
{
    if (!fLoadedIota) {
        fLoadedIota = true;

        fContainer->pushDeclare(InstBuilder::genDeclareVarInst("IOTA", InstBuilder::genBasicTyped(Typed::kInt), Address::kStruct));
        fContainer->pushInitMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("IOTA", Address::kStruct), InstBuilder::genIntNumInst(0)));

        ValueInst* value1 = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("IOTA", Address::kStruct));
        ValueInst* value2 = InstBuilder::genBinopInst(kAdd, value1, InstBuilder::genIntNumInst(1));
        fContainer->getCurLoop()->pushComputePostDSPMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("IOTA", Address::kStruct), value2));
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
 * is completely enclosed in one folder
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

//================================= some string processing utilities =================================

/**
 * Removes enclosing whitespaces : '  toto  ' -> 'toto'
 */
static string wdel(const string& s)
{
    size_t i = 0;
    size_t j = s.size();
    while (i<j && s[i]==' ') i++;
    while (j>i && s[j-1] == ' ') j--;
    return s.substr(i,j-i);
}

//================================= BUILD USER INTERFACE METHOD =================================

/**
 * Generate buildUserInterface C++ lines of code corresponding
 * to user interface element t
 */
void InstructionsCompiler::generateUserInterfaceTree(Tree t)
{
	Tree label, elements, varname, sig;

	if (isUiFolder(t, label, elements)) {
		const int orient = tree2int(left(label));
		const char* str = tree2str(right(label));

        fContainer->pushUserInterfaceMethod(InstBuilder::genOpenboxInst(orient, str));
        generateUserInterfaceElements(elements);
        fContainer->pushUserInterfaceMethod(InstBuilder::genCloseboxInst());

	} else if (isUiWidget(t, label, varname, sig)) {

		generateWidgetCode(label, varname, sig);

	} else {

		fprintf(stderr, "error in user interface generation 2\n");
		exit(1);

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
            fContainer->pushUserInterfaceMethod(InstBuilder::genAddMetaDeclareInst(tree2str(varname), wdel(key), wdel(*j)));
        }
    }

	if (isSigButton(sig, path)) 					{
        fContainer->pushUserInterfaceMethod(InstBuilder::genAddButtonInst(label, tree2str(varname)));

	} else if (isSigCheckbox(sig, path)) 			{
        fContainer->pushUserInterfaceMethod(InstBuilder::genAddCheckbuttonInst(label, tree2str(varname)));

	} else if (isSigVSlider(sig, path,c,x,y,z))	{
        fContainer->pushUserInterfaceMethod(
            InstBuilder::genAddVerticalSliderInst(label, tree2str(varname), tree2float(c), tree2float(x), tree2float(y), tree2float(z)));

	} else if (isSigHSlider(sig, path,c,x,y,z))	{
        fContainer->pushUserInterfaceMethod(
            InstBuilder::genAddHorizontalSliderInst(label, tree2str(varname), tree2float(c), tree2float(x), tree2float(y), tree2float(z)));

	} else if (isSigNumEntry(sig, path,c,x,y,z))	{
        fContainer->pushUserInterfaceMethod(
            InstBuilder::genAddNumEntryInst(label, tree2str(varname), tree2float(c), tree2float(x), tree2float(y), tree2float(z)));

	} else if (isSigVBargraph(sig, path,x,y,z))	{
        fContainer->pushUserInterfaceMethod(
            InstBuilder::genAddVerticalBargraphInst(label, tree2str(varname),  tree2float(x), tree2float(y)));

	} else if (isSigHBargraph(sig, path,x,y,z))	{
 	    fContainer->pushUserInterfaceMethod(
            InstBuilder::genAddHorizontalBargraphInst(label, tree2str(varname), tree2float(x), tree2float(y)));

	} else {
		fprintf(stderr, "Error in generating widget code\n");
		exit(1);
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
		fprintf(stderr, "error in user interface macro generation 2\n");
		exit(1);
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
    map<string, set<string> >   metadata;

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
		fprintf(stderr, "Error in generating widget code\n");
		exit(1);
	}
}
