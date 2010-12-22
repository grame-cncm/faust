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

        //fContainer->openLoop(getFreshID("i"));
        fContainer->openLoop(new MultiRateCodeLoop("i"));

        // Cast to external float
        /*
        ValueInst* res = InstBuilder::genCastNumInst(CS(sig), InstBuilder::genBasicTyped(Typed::kFloatMacro));
        pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(name, fContainer->getCurLoop()->getLoopIndex(), res));
        */

        pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(name, CS(sig)));

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
            fContainer->openLoop(new MultiRateCodeLoop(x, "i", sigRate));
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
    // "fInput" use as a name convention
    string name = subst("fInput$0", T(idx));
    ValueInst* res = InstBuilder::genLoadArrayStructVar(name);
    // Cast to internal float
    //res = InstBuilder::genCastNumInst(res, InstBuilder::genBasicTyped(itfloat()));
    return generateCacheCode(sig, res);

}

ValueInst* MultiRateDAGInstructionsCompiler::generateVectorize(Tree sig, Tree exp, int n)
{
    Type expType = getSigType(exp);
    int expRate = getSigRate(exp);
    int sigRate = getSigRate(sig);
    DeclareTypeInst * typeInst = InstBuilder::genType(expType);
    assert(sigRate * n == expRate);

    pushGlobalDeclare(typeInst);
    DeclareVarInst * vecBuffer = InstBuilder::genDecStackVar("toto", typeInst->fType);
    pushDeclare(vecBuffer);

    VectorizeCodeLoop * vLoop = new VectorizeCodeLoop(fContainer->getCurLoop(), "j", sigRate);
    fContainer->openLoop(vLoop);

    fContainer->openLoop(new MultiRateCodeLoop("i", n));
    ValueInst * body = generateCode(exp);
    fContainer->closeLoop();

    vLoop->setExpression(body);

    fContainer->closeLoop(); // close vectorize

    return vecBuffer->load(); // return handle
}

ValueInst* MultiRateDAGInstructionsCompiler::generateSerialize(Tree sig, Tree exp)
{
    Type expType = getSigType(exp);
    int expRate = getSigRate(exp);
    int sigRate = getSigRate(sig);
    int n = sigRate / expRate;
    Typed * firType = NULL; //genVectorType(expType, n, expRate);
    DeclareTypeInst * typeInst = InstBuilder::genDeclareTypeInst(firType);

    pushGlobalDeclare(typeInst);
    DeclareVarInst * vecBuffer = InstBuilder::genDecStackVar("toto", firType);
    pushDeclare(vecBuffer);

    SerializeCodeLoop * vLoop = new SerializeCodeLoop(fContainer->getCurLoop(), "j", sigRate);
    fContainer->openLoop(vLoop);

    fContainer->openLoop("i", n);
    ValueInst * body = generateCode(exp);
    fContainer->closeLoop();

    vLoop->setExpression(body);

    fContainer->closeLoop(); // close vectorize

    return vecBuffer->load(); // return handle
}
