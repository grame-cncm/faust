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

#include "mr_dag_instructions_compiler.hh"

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

// Code generation

void MultiRateDAGInstructionsCompiler::compileMultiSignal(Tree L)
{
	L = prepare(L);		// Optimize, share and annotate expression

    // "input" and "inputs" used as a name convention
    Typed* type = InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(Typed::kFloatMacro), 0);

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

    for (int index = 0; isList(L); L = tl(L), index++) {
        Tree sig = hd(L);
        string name = subst("fOutput$0", T(index));

        int sigRate = getSigRate(sig);
        fContainer->setOutputRate(index, sigRate);

        fContainer->openLoop(new MultiRateCodeLoop("i", sigRate));
        ValueInst * loopIndex = curLoopIndex();

        // Cast to external float
        /*
        ValueInst* res = InstBuilder::genCastNumInst(CS(sig), InstBuilder::genBasicTyped(Typed::kFloatMacro));
        pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(name, curLoopIndex(), res));
        */

        ValueInst * compiledSignal = CS(sig);

        if (sigRate > 1) {
            string address;
            getVectorNameProperty(sig, address);
            StatementInst* store = InstBuilder::genStoreArrayStructVar(name, loopIndex,
                InstBuilder::genCastNumInst(InstBuilder::genLoadArrayStructVar(address,
                                                                               loopIndex),
                                            InstBuilder::genBasicTyped(Typed::kFloatMacro)));

            pushComputeDSPMethod(store);
        } else {
            pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(name, loopIndex,
                InstBuilder::genCastNumInst(compiledSignal, InstBuilder::genBasicTyped(Typed::kFloatMacro))));
        }

        fContainer->closeLoop();
    }

	generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
	generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
	if (fDescription) {
		fDescription->ui(prepareUserInterfaceTree(fUIRoot));
	}

	fContainer->processFIR();
}

ValueInst* MultiRateDAGInstructionsCompiler::generateCode(Tree sig)
{
    int         i;
    Tree        x;
    CodeLoop*   l = fContainer->getCurLoop();
    assert(l);

    Tree exp, exp2, n;
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
                int sigRate = getSigRate(sig);
                fContainer->openLoop(new MultiRateCodeLoop(x, "i", sigRate));
                ValueInst* code = InstructionsCompiler::generateCode(sig);
                fContainer->closeLoop(sig);
                return code;
            }

        } else if (isSigVectorize(sig, exp, n)) {
             return generateVectorize(sig, exp, tree2int(n));
        } else if (isSigSerialize(sig, exp)) {
            return generateSerialize(sig, exp);
        } else {
            int sigRate = getSigRate(sig);
            fContainer->openLoop(new MultiRateCodeLoop("i", sigRate));
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
bool MultiRateDAGInstructionsCompiler::needSeparateLoop(Tree sig)
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
    } else if (isSigVectorize(sig, x, y)) {
        b = true;
    } else if (isSigSerialize(sig, x)) {
        b = true;
    } else if (isSigConcat(sig, x, y)) {
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

// TO CHECK
ValueInst* MultiRateDAGInstructionsCompiler::generateCacheCode(Tree sig, ValueInst* exp)
{
    string      vname;
    Typed::VarType    ctype;
    Type        t = getSigType(sig);
    Occurences* o = fOccMarkup.retrieve(sig);
    int         d = o->getMaxDelay();

    if (t->variability() < kSamp) {
    } else {
        // sample-rate signal
        if (d > 0) {
        } else {
            // not delayed
            if (isVectorType(t) || getSigRate(sig) > 1) {
                getTypedNames(getSigType(sig), "Zec", ctype, vname);
                Address::AccessType var_access;
                generateDelayLine(sig, exp, ctype, vname, d, var_access);
                setVectorNameProperty(sig, vname);
                // return subst("$0[i]", vname);
                return InstBuilder::genLoadArrayVar(vname, var_access, curLoopIndex());
            }
        }
    }

    return DAGInstructionsCompiler::generateCacheCode(sig, exp);
}

ValueInst* MultiRateDAGInstructionsCompiler::generateFixDelay(Tree sig, Tree exp, Tree delay)
{
    return generateCacheCode(sig, DAGInstructionsCompiler::generateFixDelay(sig, exp, delay));
}

void MultiRateDAGInstructionsCompiler::generateDlineLoop(Tree sig, Typed::VarType ctype, const string& vname, int delay, ValueInst* exp, Address::AccessType& var_access)
{
    if (getSigRate(sig) > 1) {
        LoadVarInst * loadExp = dynamic_cast<LoadVarInst*>(exp);
        if (loadExp)
            exp = InstBuilder::genLoadArrayStackVar(loadExp->fAddress->getName(), curLoopIndex());
    }

    return DAGInstructionsCompiler::generateDlineLoop(sig, ctype, vname, delay, exp, var_access);
}


void MultiRateDAGInstructionsCompiler::generateVectorLoop(Tree sig, Typed::VarType ctype, const string& vname, ValueInst* exp, Address::AccessType& var_access)
{
    DeclareTypeInst* typeInst = InstBuilder::genType(getSigType(sig));
    pushGlobalDeclare(typeInst);
    DeclareVarInst* vecBuffer = InstBuilder::genDecStackVar(vname, InstBuilder::genArrayTyped(typeInst->fType, getSigRate(sig) * gVecSize));
    pushDeclare(vecBuffer);

    // -- compute the new samples
    if (isVectorType(getSigType(sig)) || getSigRate(sig) > 1) {
        LoadVarInst * loadExp = dynamic_cast<LoadVarInst*>(exp);
        if (loadExp) {
            IndexedAddress * idxAddress = dynamic_cast<IndexedAddress*>(loadExp->fAddress);
            if (idxAddress) {
                ValueInst * index = InstBuilder::genAdd(idxAddress->fIndex, curLoopIndex());
                exp = InstBuilder::genLoadArrayStackVar(loadExp->fAddress->getName(), index);
            } else
                exp = InstBuilder::genLoadArrayStackVar(loadExp->fAddress->getName(), curLoopIndex());
        }
    }

    pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(vname, curLoopIndex(), exp));

    // Set desired variable access
    var_access = Address::kStack;
}



ValueInst* MultiRateDAGInstructionsCompiler::generateInput(Tree sig, int idx)
{
    int rate = getSigRate(sig);
    fContainer->setInputRate(idx, rate);

    // "fInput" use as a name convention
    string name = subst("fInput$0", T(idx));
    ValueInst* res = InstBuilder::genLoadArrayStructVar(name);  // return "handle" on vector
    // Cast to internal float
    //res = InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(itfloat()));
    return generateCacheCode(sig, res);
}

ValueInst* MultiRateDAGInstructionsCompiler::generateVectorize(Tree sig, Tree exp, int n)
{
    Type sigType = getSigType(sig);

    int sigRate = getSigRate(sig); // m x [n]T
    int expRate = getSigRate(exp); // m.n x T

    DeclareTypeInst* typeInst = InstBuilder::genType(sigType);

    assert(sigRate * n == expRate);

    string vecname = getFreshID("fVectorize");

    printf("generateVectorize expRate=%d, sigRate=%d, n=%d\n", expRate, sigRate, n);

    fContainer->openLoop("i", sigRate);

    pushGlobalDeclare(typeInst);
    DeclareVarInst* vecBuffer = InstBuilder::genDecStackVar(vecname, InstBuilder::genArrayTyped(typeInst->fType, sigRate * gVecSize));
    pushDeclare(vecBuffer);

    // open vectorize loop
    VectorizeCodeLoop* vLoop = new VectorizeCodeLoop(fContainer->getCurLoop(), "j", sigRate, expRate);
    fContainer->openLoop(vLoop);

    LoadVarInst* in_buffer = dynamic_cast<LoadVarInst*>(generateCode(exp));

    // Assume the result is a buffer for now (and not a more complex ValueInst*)
    assert(in_buffer);

    // input index
    LoadVarInst * loadI = InstBuilder::genLoadLoopVar("i");
    LoadVarInst * loadJ = InstBuilder::genLoadLoopVar("j");
    ValueInst* in_index = InstBuilder::genAdd(InstBuilder::genMul(loadI, InstBuilder::genIntNumInst(n)), loadJ);

    pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(vecname, loadI, loadJ,
        InstBuilder::genLoadArrayStructVar(in_buffer->fAddress->getName(), in_index)));

    fContainer->closeLoop(); // close vectorize

    ValueInst * ret = generateCacheCode(sig, vecBuffer->load());
    fContainer->closeLoop();


    return ret; // return "handle" on vector
}

ValueInst* MultiRateDAGInstructionsCompiler::generateSerialize(Tree sig, Tree exp)
{
    Type sigType = getSigType(sig);

    int sigRate = getSigRate(sig); // m.n x T
    int expRate = getSigRate(exp); // m x [n]T     (expRate = m)
    int n = sigRate / expRate;

    string vecname = getFreshID("fSerialize");

    fContainer->openLoop("i", sigRate);

    DeclareTypeInst* typeInst = InstBuilder::genType(sigType);

    printf("generateSerialize expRate=%d, sigRate=%d, n=%d \n", expRate, sigRate, n);

    pushGlobalDeclare(typeInst);
    DeclareVarInst* vecBuffer = InstBuilder::genDecStackVar(vecname, InstBuilder::genArrayTyped(typeInst->fType, sigRate * gVecSize));
    pushDeclare(vecBuffer);

    // open serialize loop
    SerializeCodeLoop* vLoop = new SerializeCodeLoop(fContainer->getCurLoop(), "j", sigRate, expRate);
    fContainer->openLoop(vLoop);

    // Output index
    LoadVarInst * loadI = InstBuilder::genLoadLoopVar("i");
    LoadVarInst * loadJ = InstBuilder::genLoadLoopVar("j");
    ValueInst* out_index = InstBuilder::genAdd(InstBuilder::genMul(loadI, InstBuilder::genIntNumInst(n)), loadJ);

    LoadVarInst* in_buffer = dynamic_cast<LoadVarInst*>(generateCode(exp));

    // Assume the result is a buffer for now (and not a more complex ValueInst*)
    assert(in_buffer);
    pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(vecname, out_index,
        InstBuilder::genLoadArrayStructVar(in_buffer->fAddress->getName(), loadI, loadJ)));

    fContainer->closeLoop(); // close serialize

    ValueInst * ret = generateCacheCode(sig, vecBuffer->load());
    fContainer->closeLoop();

    return ret; // return "handle" on vector
}

ValueInst* MultiRateDAGInstructionsCompiler::generateVectorAt(Tree sig, Tree exp, Tree index)
{
    int sigRate = getSigRate(sig);

    ValueInst * compiledExpression = CS(exp);
    LoadVarInst * loadExpression = dynamic_cast<LoadVarInst*>(compiledExpression);

    // FIXME: only supports compile-time indices
    ValueInst * indexInst = InstBuilder::genIntNumInst(tree2int(index));
    ValueInst * loadedCode = InstBuilder::genLoadArrayStructVar(loadExpression->fAddress->getName(), curLoopIndex(), indexInst);

    Type sigType = getSigType(sig);

    DeclareTypeInst* typeInst = InstBuilder::genType(sigType);
    pushGlobalDeclare(typeInst);

    pushGlobalDeclare(InstBuilder::genType(getSigType(exp)));

    string vecname = getFreshID("fAt");
    DeclareVarInst* vecBuffer = InstBuilder::genDecStackVar(vecname, InstBuilder::genArrayTyped(typeInst->fType, sigRate * gVecSize));
    pushDeclare(vecBuffer);

    StatementInst * storeInst = InstBuilder::genStoreArrayStructVar(vecname,
                                                                    InstBuilder::genLoadLoopVar("i"), // rate*count
                                                                    loadedCode);
    pushComputeDSPMethod(storeInst);

    return generateCacheCode(sig, vecBuffer->load()); // return "handle" on vector
}

ValueInst* MultiRateDAGInstructionsCompiler::generateConcat(Tree sig, Tree exp1, Tree exp2)
{
    int sigRate = getSigRate(sig);
    Type sigType = getSigType(sig);

    DeclareTypeInst* typeInst = InstBuilder::genType(sigType);

    pushGlobalDeclare(typeInst);
    string vecname = getFreshID("fConcat");
    DeclareVarInst* vecBuffer = InstBuilder::genDecStackVar(vecname, InstBuilder::genArrayTyped(typeInst->fType, sigRate * gVecSize));
    pushDeclare(vecBuffer);

    Type exp1Type = getSigType(exp1);
    int exp1Size = isVectorType(exp1Type)->size();

    Type exp2Type = getSigType(exp2);
    int exp2Size = isVectorType(exp2Type)->size();

    ValueInst * compiledExpression1 = CS(exp1);
    LoadVarInst * loadExpression1 = dynamic_cast<LoadVarInst*>(compiledExpression1);

    ValueInst * compiledExpression2 = CS(exp2);
    LoadVarInst * loadExpression2 = dynamic_cast<LoadVarInst*>(compiledExpression2);
    ValueInst* currentIndex = curLoopIndex();

    // first loop
    {
        DeclareVarInst* loopDeclare = InstBuilder::genDecLoopVar("k", InstBuilder::genBasicTyped(Typed::kInt),
                                                            InstBuilder::genIntNumInst(0));
        ValueInst* loopEnd = InstBuilder::genLessThan(loopDeclare->load(), InstBuilder::genIntNumInst(exp1Size));
        StoreVarInst* loopIncrement = loopDeclare->store(InstBuilder::genAdd(loopDeclare->load(), 1));
        BlockInst* block = InstBuilder::genBlockInst();

        ForLoopInst * loop = InstBuilder::genForLoopInst(loopDeclare, loopEnd, loopIncrement, block);

        ValueInst * loadedCode = InstBuilder::genLoadArrayStructVar(loadExpression1->fAddress->getName(), currentIndex, loopDeclare->load());
        StatementInst * storeInst = InstBuilder::genStoreArrayStructVar(vecname, currentIndex, loopDeclare->load(), loadedCode);

        block->pushBackInst(storeInst);
        pushComputeDSPMethod(loop);
    }

    // second loop
    {
        DeclareVarInst* loopDeclare = InstBuilder::genDecLoopVar("k", InstBuilder::genBasicTyped(Typed::kInt),
                                                            InstBuilder::genIntNumInst(0));
        ValueInst* loopEnd = InstBuilder::genLessThan(loopDeclare->load(), InstBuilder::genIntNumInst(exp2Size));
        StoreVarInst* loopIncrement = loopDeclare->store(InstBuilder::genAdd(loopDeclare->load(), 1));
        BlockInst* block = InstBuilder::genBlockInst();

        ForLoopInst * loop = InstBuilder::genForLoopInst(loopDeclare, loopEnd, loopIncrement, block);

        ValueInst * index = InstBuilder::genAdd(loopDeclare->load(), InstBuilder::genIntNumInst(exp1Size));
        ValueInst * loadedCode = InstBuilder::genLoadArrayStructVar(loadExpression2->fAddress->getName(), currentIndex, loopDeclare->load());
        StatementInst * storeInst = InstBuilder::genStoreArrayStructVar(vecname, currentIndex, index, loadedCode);

        block->pushBackInst(storeInst);
        pushComputeDSPMethod(loop);
    }

    return generateCacheCode(sig, vecBuffer->load()); // return "handle" on vector
}
