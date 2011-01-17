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

#include "dag_instructions_compiler.hh"

#include "ppsig.hh"
#include "Text.hh"
#include "sigtyperules.hh"
#include "timing.hh"
#include "recursivness.hh"
#include "privatise.hh"
#include "simplify.hh"
#include "xtended.hh"
#include "prim2.hh"
#include "sigrateinference.hh"

extern int gMaxCopyDelay;
extern bool gOpenCLSwitch;
extern bool gCUDASwitch;

DAGInstructionsCompiler::DAGInstructionsCompiler(CodeContainer* container):
    InstructionsCompiler(container)
{}

void DAGInstructionsCompiler::compileMultiSignal(Tree L)
{
	L = prepare(L);		// Optimize, share and annotate expression

    // "input" and "inputs" used as a name convention
    if (!gOpenCLSwitch && !gCUDASwitch) { // HACK

        Typed* type;
        /*
        if (gVectorSwitch) {
            type =  InstBuilder::genArrayTyped(InstBuilder::genVectorTyped(InstBuilder::genBasicTyped(Typed::kFloatMacro)), 0);
        } else {
            type = InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(Typed::kFloatMacro), 0);
        }
        */
        type = InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(Typed::kFloatMacro), 0);

        for (int index = 0; index < fContainer->inputs(); index++) {
            string name1 = subst("fInput$0_ptr", T(index));
            string name2 = subst("fInput$0", T(index));
            pushDeclare(InstBuilder::genDecStructVar(name1, type));
            pushComputeBlockMethod(InstBuilder::genStoreStructVar(name1,
                InstBuilder::genLoadArrayFunArgsVar("inputs", InstBuilder::genIntNumInst(index))));
            pushDeclare(InstBuilder::genDecStructVar(name2, type));
        }

        // "output" and "outputs" used as a name convention
        for (int index = 0; index < fContainer->outputs(); index++) {
            string name1 = subst("fOutput$0_ptr", T(index));
            string name2 = subst("fOutput$0", T(index));
            pushDeclare(InstBuilder::genDecStructVar(name1, type));
            pushComputeBlockMethod(InstBuilder::genStoreStructVar(name1,
                InstBuilder::genLoadArrayFunArgsVar("outputs", InstBuilder::genIntNumInst(index))));
            pushDeclare(InstBuilder::genDecStructVar(name2, type));
        }
    }

    if (gOpenCLSwitch || gCUDASwitch) { // HACK

        for (int index = 0; isList(L); L = tl(L), index++) {
            Tree sig = hd(L);
            string name = subst("output$0", T(index));

            int sigRate = getSigRate(sig);
            fContainer->setOutputRate(index, sigRate);

            //fContainer->openLoop(getFreshID("i"));
            fContainer->openLoop("i");

            // Cast to external float
            ValueInst* res = InstBuilder::genCastNumInst(CS(sig), InstBuilder::genBasicTyped(Typed::kFloatMacro));
            pushComputeDSPMethod(InstBuilder::genStoreArrayFunArgsVar(name,
                                InstBuilder::genAdd(InstBuilder::genLoadLoopVar("index"), curLoopIndex()), res));

            fContainer->closeLoop();
        }

    } else {

        for (int index = 0; isList(L); L = tl(L), index++) {
            Tree sig = hd(L);
            string name = subst("fOutput$0", T(index));
            int sigRate = getSigRate(sig);
            fContainer->setOutputRate(index, sigRate);

            //fContainer->openLoop(getFreshID("i"));
            fContainer->openLoop("i");

            // Cast to external float
            ValueInst* res = InstBuilder::genCastNumInst(CS(sig), InstBuilder::genBasicTyped(Typed::kFloatMacro));
            pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(name, curLoopIndex(), res));

            fContainer->closeLoop();
        }
    }

	generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
	generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
	if (fDescription) {
		fDescription->ui(prepareUserInterfaceTree(fUIRoot));
	}

	fContainer->processFIR();
}

ValueInst* DAGInstructionsCompiler::CS(Tree sig)
{
    int i;
    Tree x;
    ValueInst* code;
    if (!getCompiledExpression(sig, code)) {
        code = generateCode(sig);
        setCompiledExpression(sig, code);
    } else {
        // check for recursive dependencies
        CodeLoop* ls;
        CodeLoop* tl = fContainer->getCurLoop();
        if (isProj(sig, &i, x) && tl->findRecDefinition(x)) {
            tl->addRecDependency(x);
		} else if (fContainer->getLoopProperty(sig, ls)) {
			tl->addBackwardDependency(ls);
		} else {
			Tree x, d;
			if (isSigFixDelay(sig, x, d)) {
				if (fContainer->getLoopProperty(x, ls)) {
					tl->addBackwardDependency(ls);
				}
			}
        }
    }
	return code;
}

ValueInst* DAGInstructionsCompiler::generateVariableStore(Tree sig, ValueInst* exp)
{
    ::Type t = getSigType(sig);

    if (getSigType(sig)->variability() == kSamp) {
        string vname;
        Typed::VarType ctype;
        getTypedNames(t, "Vector", ctype, vname);
        Address::AccessType var_access;
        generateVectorLoop(ctype, vname, exp, var_access);
        return InstBuilder::genLoadArrayVar(vname, var_access, curLoopIndex());
    } else {
        return InstructionsCompiler::generateVariableStore(sig, exp);
    }
}

ValueInst* DAGInstructionsCompiler::generateInput(Tree sig, int idx)
{
    int rate = getSigRate(sig);
    fContainer->setInputRate(idx, rate);

    if (gOpenCLSwitch || gCUDASwitch) { // HACK
        // "input" use as a name convention
        string name = subst("input$0", T(idx));
        ValueInst* res = InstBuilder::genLoadArrayFunArgsVar(name,
            InstBuilder::genAdd(InstBuilder::genLoadLoopVar("index"), curLoopIndex()));
        // Cast to internal float
        res = InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(itfloat()));
        return generateCacheCode(sig, res);

     } else {
        // "fInput" use as a name convention
        string name = subst("fInput$0", T(idx));
        ValueInst* res = InstBuilder::genLoadArrayStructVar(name, curLoopIndex());
        // Cast to internal float
        res = InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(itfloat()));
        return generateCacheCode(sig, res);
     }
}

ValueInst* DAGInstructionsCompiler::generateCacheCode(Tree sig, ValueInst* exp)
{
    string      vname;
    Typed::VarType    ctype;
    int         sharing = getSharingCount(sig);
    Type        t = getSigType(sig);
    Occurences* o = fOccMarkup.retrieve(sig);
    int         d = o->getMaxDelay();

    if (t->variability() < kSamp) {
        if (d == 0) {
            // non-sample, not delayed : same as scalar cache
            return InstructionsCompiler::generateCacheCode(sig, exp);

        } else {
            // it is a non-sample expressions but used delayed
            // we need a delay line
			getTypedNames(getSigType(sig), "Vec", ctype, vname);
            Address::AccessType var_access;

            if ((sharing > 1) && !verySimple(sig)) {
                // first cache this expression because it
                // it is shared and complex
                ValueInst* cachedexp = generateVariableStore(sig, exp);
                generateDelayLine(cachedexp, ctype, vname, d, var_access);
                setVectorNameProperty(sig, vname);
                return cachedexp;
            } else {
                // no need to cache this expression because
                // it is either not shared or very simple
                generateDelayLine(exp, ctype, vname, d, var_access);
                setVectorNameProperty(sig, vname);
                return exp;
            }
        }
    } else {
        // sample-rate signal
        if (d > 0) {
            // used delayed : we need a delay line
            getTypedNames(getSigType(sig), "Yec", ctype, vname);
            Address::AccessType var_access;
            generateDelayLine(exp, ctype, vname, d, var_access);
            setVectorNameProperty(sig, vname);

            if (verySimple(sig)) {
                return exp;
            } else {
                // return subst("$0[i]", vname);
                return InstBuilder::genLoadArrayVar(vname, var_access, curLoopIndex());
            }
        } else {
            // not delayed
            if (sharing > 1 && !verySimple(sig)) {
                // shared and not simple : we need a vector
                // cerr << "ZEC : " << ppsig(sig) << endl;
                getTypedNames(getSigType(sig), "Zec", ctype, vname);
                Address::AccessType var_access;
                generateDelayLine(exp, ctype, vname, d, var_access);
                setVectorNameProperty(sig, vname);
                // return subst("$0[i]", vname);
                return InstBuilder::genLoadArrayVar(vname, var_access, curLoopIndex());
           } else {
                // not shared or simple : no cache needed
                return exp;
            }
        }
    }
}

// Code generation

ValueInst* DAGInstructionsCompiler::generateCode(Tree sig)
{
    int         i;
    Tree        x;
    CodeLoop*   l = fContainer->getCurLoop();
    assert(l);

    if (needSeparateLoop(sig)) {
        // we need a separate loop unless it's an old recursion
        if (isProj(sig, &i, x)) {
            // projection of a recursive group x
            if (l->findRecDefinition(x)) {
                // x is already in the loop stack
                l->addRecDependency(x);
                return InstructionsCompiler::generateCode(sig);
            } else {
                // x must be defined
                int sigRate = getSigRate(x);
                fContainer->openLoop(x, "i", sigRate);
                ValueInst* code = InstructionsCompiler::generateCode(sig);
                fContainer->closeLoop(sig);
                return code;
            }
        } else {
            int sigRate = getSigRate(sig);
            fContainer->openLoop("i", sigRate);
            ValueInst* code = InstructionsCompiler::generateCode(sig);
            fContainer->closeLoop(sig);
            return code;
        }
    } else {
        return InstructionsCompiler::generateCode(sig);
    }
}


/**
 * Test if a signal need to be compiled in a separate loop.
 * @param sig the signal expression to test.
 * @return true if a separate loop is needed
 */
bool DAGInstructionsCompiler::needSeparateLoop(Tree sig)
{
    Occurences* o = fOccMarkup.retrieve(sig);
    Type        t = getSigType(sig);
    int         c = getSharingCount(sig);
    bool        b;

    int         i;
    Tree        x,y;

    if (o->getMaxDelay() > 0) {
        b = true;
    } else if (verySimple(sig) || t->variability() < kSamp) {
        b = false;      // non sample computation never require a loop
    } else if (isSigFixDelay(sig, x, y)) {
        b = false;
    } else if (isProj(sig, &i, x)) {
        b = true;
    } else if (c > 1) {
        b = true;
    } else {
        // sample expressions that are not recursive, not delayed
        // and not shared, doesn't require a separate loop.
        b = false;
    }
    return b;
}

ValueInst* DAGInstructionsCompiler::generateFixDelay(Tree sig, Tree exp, Tree delay)
{
    int mxd, d;
    string vname;

    CS(exp); // ensure exp is compiled to have a vector name

    mxd = fOccMarkup.retrieve(exp)->getMaxDelay();

    if (!getVectorNameProperty(exp, vname)) {
        cerr << "no vector name for " << ppsig(exp) << endl;
        exit(1);
    }

    if (mxd == 0) {
        // not a real vector name but a scalar name
        //return subst("$0[i]", vname);
        return InstBuilder::genLoadArrayStackVar(vname, curLoopIndex());

    } else if (mxd < gMaxCopyDelay) {
        if (isSigInt(delay, &d)) {
            if (d == 0) {
                // return subst("$0[i]", vname);
                return InstBuilder::genLoadArrayStackVar(vname, curLoopIndex());
            } else {
                // return subst("$0[i-$1]", vname, T(d));
                ValueInst* index = InstBuilder::genSub(curLoopIndex(), InstBuilder::genIntNumInst(d));
                return InstBuilder::genLoadArrayStackVar(vname, index);
            }
        } else {
            // return subst("$0[i-$1]", vname, CS(delay));
            ValueInst* index = InstBuilder::genSub(curLoopIndex(), CS(delay));
            return InstBuilder::genLoadArrayStackVar(vname, index);
        }
    } else {

        // long delay : we use a ring buffer of size 2^x
        int N = pow2limit(mxd + gVecSize);
        string vname_idx = vname + "_idx";

        if (isSigInt(delay, &d)) {
            if (d == 0) {
                //return subst("$0[($0_idx+i)&$1]", vname, T(N-1));
                ValueInst* index1 = InstBuilder::genAdd(curLoopIndex(), InstBuilder::genLoadStructVar(vname_idx));
                ValueInst* index2 = InstBuilder::genAnd(index1, InstBuilder::genIntNumInst(N-1));
                return InstBuilder::genLoadArrayStructVar(vname, index2);
            } else {
                //return subst("$0[($0_idx+i-$2)&$1]", vname, T(N-1), T(d));
                ValueInst* index1 = InstBuilder::genAdd(curLoopIndex(), InstBuilder::genLoadStructVar(vname_idx));
                ValueInst* index2 = InstBuilder::genSub(index1, InstBuilder::genIntNumInst(d));
                ValueInst* index3 = InstBuilder::genAnd(index2, InstBuilder::genIntNumInst(N-1));
                return InstBuilder::genLoadArrayStructVar(vname, index3);
            }
        } else {
            //return subst("$0[($0_idx+i-$2)&$1]", vname, T(N-1), CS(delay));
            ValueInst* index1 = InstBuilder::genAdd(curLoopIndex(), InstBuilder::genLoadStructVar(vname_idx));
            ValueInst* index2 = InstBuilder::genSub(index1, CS(delay));
            ValueInst* index3 = InstBuilder::genAnd(index2, InstBuilder::genIntNumInst(N-1));
            return InstBuilder::genLoadArrayStructVar(vname, index3);
        }
    }
}

ValueInst* DAGInstructionsCompiler::generateDelayVec(Tree sig, ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd)
{
    // it is a non-sample but used delayed
    // we need a delay line

    setVectorNameProperty(sig, vname);
    Address::AccessType var_access;
    generateDelayLine(exp, ctype, vname, mxd, var_access);

    if (verySimple(sig)) {
        return exp;
    } else {
        return InstBuilder::genLoadArrayVar(vname, var_access, curLoopIndex());
    }
}

ValueInst* DAGInstructionsCompiler::generateDelayLine(ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd, Address::AccessType& var_access)
{
    if (mxd == 0) {
        generateVectorLoop(ctype, vname, exp, var_access);
    } else {
        generateDlineLoop(ctype, vname, mxd, exp, var_access);
    }

    return exp;
}

void DAGInstructionsCompiler::generateVectorLoop(Typed::VarType ctype, const string& vname, ValueInst* exp, Address::AccessType& var_access)
{
    // "$0 $1[$2];"
    DeclareVarInst* table_inst = InstBuilder::genDecStackVar(vname, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), gVecSize));
    pushComputeBlockMethod(table_inst);

    // -- compute the new samples
    // $0[i] = $1;"
    pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(vname, curLoopIndex(), exp));

    // Set desired variable access
    var_access = Address::kStack;
}

void DAGInstructionsCompiler::generateDlineLoop(Typed::VarType ctype, const string& vname, int delay, ValueInst* exp, Address::AccessType& var_access)
{
    BasicTyped* typed = InstBuilder::genBasicTyped(ctype);

    if (delay < gMaxCopyDelay) {

        // Implementation of a copy based delayline
        // create names for temporary and permanent storage
	    string buf = subst("$0_tmp", vname);
        string pmem = subst("$0_perm", vname);

        // constraints delay size to be multiple of 4
        delay = (delay+3) & -4;

        // allocate permanent storage for delayed samples
        pushInitMethod(generateInitArray(pmem, ctype, delay));

        // compute method

        // -- declare a buffer and a "shifted" vector
        DeclareVarInst* table_inst1 = InstBuilder::genDecStackVar(buf, InstBuilder::genArrayTyped(typed, gVecSize + delay));
        pushComputeBlockMethod(table_inst1);

        ValueInst* address_value = InstBuilder::genLoadArrayStackAddressVar(buf, InstBuilder::genIntNumInst(delay));
        DeclareVarInst* table_inst2 = InstBuilder::genDecStackVar(vname, InstBuilder::genArrayTyped(typed, 0), address_value);
        pushComputeBlockMethod(table_inst2);

        // -- copy the stored samples to the delay line
        pushComputePreDSPMethod(generateCopyArray(buf, pmem, delay));

        // -- compute the new samples
        pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(vname, curLoopIndex(), exp));

        // -- copy back to stored samples
        pushComputePostDSPMethod(generateCopyBackArray(pmem, buf, delay));

        // Set desired variable access
        var_access = Address::kStack;

    } else {

        // Implementation of a ring-buffer delayline, the size should be large enough and aligned on a power of two
        delay = pow2limit(delay + gVecSize);

        // create names for temporary and permanent storage
        string idx = subst("$0_idx", vname);
        string idx_save = subst("$0_idx_save", vname);

        // allocate permanent storage for delayed samples
        pushInitMethod(generateInitArray(vname, ctype, delay));
        pushDeclare(InstBuilder::genDecStructVar(idx, InstBuilder::genBasicTyped(Typed::kInt)));
        pushDeclare(InstBuilder::genDecStructVar(idx_save, InstBuilder::genBasicTyped(Typed::kInt)));

        // init permanent memory
        pushInitMethod(InstBuilder::genStoreStructVar(idx, InstBuilder::genIntNumInst(0)));
        pushInitMethod(InstBuilder::genStoreStructVar(idx_save, InstBuilder::genIntNumInst(0)));

        // -- update index
        ValueInst* index1 = InstBuilder::genAdd(InstBuilder::genLoadStructVar(idx), InstBuilder::genLoadStructVar(idx_save));
        ValueInst* index2 = InstBuilder::genAnd(index1, InstBuilder::genIntNumInst(delay-1));

        pushComputePreDSPMethod(InstBuilder::genStoreStructVar(idx, index2));

        // -- compute the new samples
        ValueInst* index3 = InstBuilder::genAdd(curLoopIndex(), InstBuilder::genLoadStructVar(idx));
        ValueInst* index4 = InstBuilder::genAnd(index3, InstBuilder::genIntNumInst(delay-1));

        pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(vname, index4, exp));

        // -- save index
        pushComputePostDSPMethod(InstBuilder::genStoreStructVar(idx_save, InstBuilder::genLoadStackVar("count")));

        // Set desired variable access
        var_access = Address::kStruct;
    }
}
