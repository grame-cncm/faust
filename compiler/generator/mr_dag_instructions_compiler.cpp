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
        fContainer->setOutputRate(index , sigRate);

        fContainer->openLoop(new MultiRateCodeLoop("i", sigRate));
        ValueInst * loopIndex = fContainer->getCurLoop()->getLoopIndex();

        // Cast to external float
        /*
        ValueInst* res = InstBuilder::genCastNumInst(CS(sig), InstBuilder::genBasicTyped(Typed::kFloatMacro));
        pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(name, fContainer->getCurLoop()->getLoopIndex(), res));
        */

        ValueInst * compiledSignal = CS(sig);
        LoadVarInst* compiledSignalBuffer = dynamic_cast<LoadVarInst*>(compiledSignal);


        if (compiledSignalBuffer) {
            StatementInst* store = InstBuilder::genStoreArrayStructVar(name, loopIndex,
                InstBuilder::genCastNumInst(InstBuilder::genLoadArrayStructVar(compiledSignalBuffer->fAddress->getName(),
                                                                               loopIndex),
                                            InstBuilder::genBasicTyped(Typed::kFloatMacro)));

            pushComputeDSPMethod(store);
        } else
            pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(name, loopIndex, compiledSignal));

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

    Tree exp, n;
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
    } else if (c > 1) {
        b = true;
    } else {
        // sample expressions that are not recursive, not delayed
        // and not shared, doesn't require a separate loop.
        b = false;
    }
    return b;
}

ValueInst* MultiRateDAGInstructionsCompiler::generateInput(Tree sig, int idx)
{
    int rate = getSigRate(sig);
    fContainer->setInputRate(idx, rate);

    // "fInput" use as a name convention
    string name = subst("fInput$0", T(idx));
    ValueInst* res = InstBuilder::genLoadArrayStructVar(name);
    // Cast to internal float
    //res = InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(itfloat()));
    return generateCacheCode(sig, res);
}

ValueInst* MultiRateDAGInstructionsCompiler::generateVectorize(Tree sig, Tree exp, int n)
{
    //Type expType = getSigType(exp);
    Type sigType = getSigType(sig);

    //sigType->print(cout);

    int expRate = getSigRate(exp);
    int sigRate = getSigRate(sig);

    //DeclareTypeInst * typeInst = InstBuilder::genType(expType);
    DeclareTypeInst* typeInst = InstBuilder::genType(sigType);

    assert(sigRate * n == expRate);

    string vecname = getFreshID("fVectorize");

    printf("generateVectorize expRate %d sigRate %d n %d\n", expRate, sigRate, n);

    pushGlobalDeclare(typeInst);
    DeclareVarInst* vecBuffer = InstBuilder::genDecStackVar(vecname, InstBuilder::genArrayTyped(typeInst->fType, sigRate * gVecSize));
    pushDeclare(vecBuffer);

    // open vectorize loop
    VectorizeCodeLoop* vLoop = new VectorizeCodeLoop(fContainer->getCurLoop(), "j", sigRate);
    fContainer->openLoop(vLoop);

    // Enclosing loops
    string i_decl = "i";
    string j_decl = "j";

    // Loop "i"
    DeclareVarInst* loop_i_decl = InstBuilder::genDecLoopVar(i_decl, InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
    ValueInst* loop_i_end = InstBuilder::genLessThan(loop_i_decl->load(), InstBuilder::genMul(InstBuilder::genLoadStackVar("count"), InstBuilder::genIntNumInst(sigRate)));
    StoreVarInst* loop_i_increment = loop_i_decl->store(InstBuilder::genAdd(loop_i_decl->load(), 1));

    BlockInst* block_i = InstBuilder::genBlockInst();

    // Loop "j"
    DeclareVarInst* loop_j_decl = InstBuilder::genDecLoopVar(j_decl, InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
    ValueInst* loop_j_end = InstBuilder::genLessThan(loop_j_decl->load(), InstBuilder::genIntNumInst(expRate));
    StoreVarInst* loop_j_increment = loop_j_decl->store(InstBuilder::genAdd(loop_j_decl->load(), 1));

    BlockInst* block_j = InstBuilder::genBlockInst();

    // Output index
    ValueInst* out_index = InstBuilder::genAdd(loop_j_decl->load(), InstBuilder::genMul(loop_i_decl->load(), InstBuilder::genIntNumInst(expRate)));

    MultiRateCodeLoop* cLoop = new MultiRateCodeLoop(fContainer->getCurLoop(), "i", expRate);
    fContainer->openLoop(cLoop);
    LoadVarInst* in_buffer = dynamic_cast<LoadVarInst*>(generateCode(exp));
    fContainer->closeLoop();

    // Assume the result is a buffer for now (and not a more complex ValueInst*)
    assert(in_buffer);

    block_j->pushFrontInst(InstBuilder::genStoreArrayStructVar(vecname, loop_i_decl->load(), loop_j_decl->load(),
        InstBuilder::genLoadArrayStructVar(in_buffer->fAddress->getName(), out_index)));

    ForLoopInst* loop_j = InstBuilder::genForLoopInst(loop_j_decl, loop_j_end, loop_j_increment, block_j);

    block_i->pushFrontInst(loop_j);

    ForLoopInst* loop_i = InstBuilder::genForLoopInst(loop_i_decl, loop_i_end, loop_i_increment, block_i);

    //pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(vecname, generateCode(exp)));
    pushComputeDSPMethod(InstBuilder::genLabelInst("// vectorize"));
    pushComputeDSPMethod(loop_i);
    fContainer->closeLoop(); // close vectorize

    return generateCacheCode(sig, vecBuffer->load()); // return "handle" on vector

/*
Tim...
    VectorizeCodeLoop* vLoop = new VectorizeCodeLoop(fContainer->getCurLoop(), "j", expRate);
    fContainer->openLoop(vLoop);

    DeclareVarInst* index = InstBuilder::genDecLoopVar("j", InstBuilder::genBasicTyped(Typed::kInt),
                                                       InstBuilder::genIntNumInst(n));

    ValueInst * code = generateCode(exp);
    ValueInst * loadedCode = code;

    LoadVarInst * loadCode = dynamic_cast<LoadVarInst*>(code);
    if (loadCode) {
        Address * loadAddress = InstBuilder::genIndexedAddress(loadCode->fAddress, index->load());
        loadedCode = InstBuilder::genLoadVarInst(loadAddress);
    }

    pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(vecname, index->load(), loadedCode));

*/

}

ValueInst* MultiRateDAGInstructionsCompiler::generateSerialize(Tree sig, Tree exp)
{
    //Type expType = getSigType(exp);
    Type sigType = getSigType(sig);

    //sigType->print(cout);

    int expRate = getSigRate(exp);
    int sigRate = getSigRate(sig);

    string vecname = getFreshID("fSerialize");

    //DeclareTypeInst * typeInst = InstBuilder::genType(expType);
    DeclareTypeInst* typeInst = InstBuilder::genType(sigType);

    printf("generateSerialize expRate %d sigRate %d\n", expRate, sigRate);

    pushGlobalDeclare(typeInst);
    DeclareVarInst* vecBuffer = InstBuilder::genDecStackVar(vecname, InstBuilder::genArrayTyped(typeInst->fType, sigRate * gVecSize));
    pushDeclare(vecBuffer);

    // open serialize loop
    SerializeCodeLoop* vLoop = new SerializeCodeLoop(fContainer->getCurLoop(), "j", sigRate);
    fContainer->openLoop(vLoop);

    // Enclosing loops
    string i_decl = "i";
    string j_decl = "j";

    // Loop "i"
    DeclareVarInst* loop_i_decl = InstBuilder::genDecLoopVar(i_decl, InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
    ValueInst* loop_i_end = InstBuilder::genLessThan(loop_i_decl->load(), InstBuilder::genMul(InstBuilder::genLoadStackVar("count"), InstBuilder::genIntNumInst(sigRate)));
    StoreVarInst* loop_i_increment = loop_i_decl->store(InstBuilder::genAdd(loop_i_decl->load(), 1));

    BlockInst* block_i = InstBuilder::genBlockInst();

    // Loop "j"
    DeclareVarInst* loop_j_decl = InstBuilder::genDecLoopVar(j_decl, InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
    ValueInst* loop_j_end = InstBuilder::genLessThan(loop_j_decl->load(), InstBuilder::genIntNumInst(expRate));
    StoreVarInst* loop_j_increment = loop_j_decl->store(InstBuilder::genAdd(loop_j_decl->load(), 1));

    BlockInst* block_j = InstBuilder::genBlockInst();

    // Output index
    ValueInst* out_index = InstBuilder::genAdd(loop_j_decl->load(), InstBuilder::genMul(loop_i_decl->load(), InstBuilder::genIntNumInst(expRate)));

    MultiRateCodeLoop* cLoop = new MultiRateCodeLoop(fContainer->getCurLoop(), "i", sigRate);
    fContainer->openLoop(cLoop);
    LoadVarInst* in_buffer = dynamic_cast<LoadVarInst*>(generateCode(exp));
    fContainer->closeLoop();

    // Assume the result is a buffer for now (and not a more complex ValueInst*)
    assert(in_buffer);

    block_j->pushFrontInst(InstBuilder::genStoreArrayStructVar(vecname, out_index,
        InstBuilder::genLoadArrayStructVar(in_buffer->fAddress->getName(), loop_i_decl->load(), loop_j_decl->load())));

    ForLoopInst* loop_j = InstBuilder::genForLoopInst(loop_j_decl, loop_j_end, loop_j_increment, block_j);

    block_i->pushFrontInst(loop_j);

    ForLoopInst* loop_i = InstBuilder::genForLoopInst(loop_i_decl, loop_i_end, loop_i_increment, block_i);


    //pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(vecname, generateCode(exp)));
    pushComputeDSPMethod(InstBuilder::genLabelInst("// serialize"));
    pushComputeDSPMethod(loop_i);
    fContainer->closeLoop(); // close serialize

    return generateCacheCode(sig, vecBuffer->load()); // return "handle" on vector

/*
Tim...
    DeclareVarInst* index = InstBuilder::genDecLoopVar("j", InstBuilder::genBasicTyped(Typed::kInt),
                                                       InstBuilder::genIntNumInst(n));

    ValueInst * code = generateCode(exp);
    LoadVarInst * loadCode = dynamic_cast<LoadVarInst*>(code);
    Address * loadAddress = InstBuilder::genIndexedAddress(loadCode->fAddress, index->load());

    ValueInst * loadedCode = InstBuilder::genLoadVarInst(loadAddress);

    pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(vecname, index->load(), loadedCode));

*/

}

ValueInst* MultiRateDAGInstructionsCompiler::generateVectorAt(Tree sig, Tree exp, Tree index)
{
    int sigRate = getSigRate(sig);

    ValueInst * compiledExpression = CS(exp);
    LoadVarInst * loadExpression = dynamic_cast<LoadVarInst*>(compiledExpression);

    // FIXME: only supports compile-time indices
    ValueInst * indexInst = InstBuilder::genIntNumInst(tree2int(index));
    Address * loadAddress = InstBuilder::genIndexedAddress(loadExpression->fAddress,
                                                           indexInst);
    ValueInst * loadedCode = InstBuilder::genLoadVarInst(loadAddress);

    Type sigType = getSigType(sig);

    DeclareTypeInst* typeInst = InstBuilder::genType(sigType);
    pushGlobalDeclare(typeInst);

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

    // first loop
    {
        DeclareVarInst* loopDeclare = InstBuilder::genDecLoopVar("k", InstBuilder::genBasicTyped(Typed::kInt),
                                                            InstBuilder::genIntNumInst(0));
        ValueInst* loopEnd = InstBuilder::genLessThan(loopDeclare->load(), InstBuilder::genIntNumInst(exp1Size));
        StoreVarInst* loopIncrement = loopDeclare->store(InstBuilder::genAdd(loopDeclare->load(), 1));
        BlockInst* block = InstBuilder::genBlockInst();

        ForLoopInst * loop = InstBuilder::genForLoopInst(loopDeclare, loopEnd, loopIncrement, block);

        Address * loadAddress = InstBuilder::genIndexedAddress(loadExpression1->fAddress,
                                                                loopDeclare->load());
        ValueInst * loadedCode = InstBuilder::genLoadVarInst(loadAddress);

        StatementInst * storeInst = InstBuilder::genStoreArrayStructVar(vecname, loopDeclare->load(), loadedCode);

        block->pushBackInst(storeInst);

        pushComputeDSPMethod(loop);
    }

    {
        DeclareVarInst* loopDeclare = InstBuilder::genDecLoopVar("k", InstBuilder::genBasicTyped(Typed::kInt),
                                                            InstBuilder::genIntNumInst(0));
        ValueInst* loopEnd = InstBuilder::genLessThan(loopDeclare->load(), InstBuilder::genIntNumInst(exp2Size));
        StoreVarInst* loopIncrement = loopDeclare->store(InstBuilder::genAdd(loopDeclare->load(), 1));
        BlockInst* block = InstBuilder::genBlockInst();

        ForLoopInst * loop = InstBuilder::genForLoopInst(loopDeclare, loopEnd, loopIncrement, block);

        Address * loadAddress = InstBuilder::genIndexedAddress(loadExpression2->fAddress,
                                                                loopDeclare->load());
        ValueInst * loadedCode = InstBuilder::genLoadVarInst(loadAddress);

        ValueInst * index = InstBuilder::genAdd(loopDeclare->load(), InstBuilder::genIntNumInst(exp2Size));

        StatementInst * storeInst = InstBuilder::genStoreArrayStructVar(vecname, index, loadedCode);

        block->pushBackInst(storeInst);

        pushComputeDSPMethod(loop);
    }

    return generateCacheCode(sig, vecBuffer->load()); // return "handle" on vector
}
