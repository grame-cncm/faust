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

#include <fstream>

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
#include "exception.hh"

DAGInstructionsCompiler::DAGInstructionsCompiler(CodeContainer* container)
:InstructionsCompiler(container)
{}

void DAGInstructionsCompiler::compileMultiSignal(Tree L)
{
	L = prepare(L);		// Optimize, share and annotate expression

    // "input" and "inputs" used as a name convention
    if (!gGlobal->gOpenCLSwitch && !gGlobal->gCUDASwitch) { // HACK

        Typed* type = InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(Typed::kFloatMacro), 0);

        for (int index = 0; index < fContainer->inputs(); index++) {
            string name1 = subst("fInput$0_ptr", T(index));
            string name2 = subst("fInput$0", T(index));
            pushDeclare(InstBuilder::genDecStructVar(name1, type));
            pushComputeBlockMethod(InstBuilder::genStoreStructVar(name1,
                InstBuilder::genLoadArrayFunArgsVar("inputs", InstBuilder::genInt32NumInst(index))));
            pushComputeBlockMethod(InstBuilder::genDecStackVar(name2, type, InstBuilder::genTypedZero(Typed::kObj_ptr)));
        }

        // "output" and "outputs" used as a name convention
        for (int index = 0; index < fContainer->outputs(); index++) {
            string name1 = subst("fOutput$0_ptr", T(index));
            string name2 = subst("fOutput$0", T(index));
            pushDeclare(InstBuilder::genDecStructVar(name1, type));
            pushComputeBlockMethod(InstBuilder::genStoreStructVar(name1,
                InstBuilder::genLoadArrayFunArgsVar("outputs", InstBuilder::genInt32NumInst(index))));
            pushComputeBlockMethod(InstBuilder::genDecStackVar(name2, type, InstBuilder::genTypedZero(Typed::kObj_ptr)));
        }
    }

    if (gGlobal->gOpenCLSwitch || gGlobal->gCUDASwitch) { // HACK

        for (int index = 0; isList(L); L = tl(L), index++) {
            Tree sig = hd(L);
            string name = subst("output$0", T(index));

            // 09/12/11 : HACK
            //int rate = getSigRate(sig);
            int rate = 1;
            fContainer->setOutputRate(index, rate);
            fContainer->openLoop("i");

            // Cast to external float
            ValueInst* res = InstBuilder::genCastFloatMacroInst(CS(sig));
            pushComputeDSPMethod(InstBuilder::genStoreArrayFunArgsVar(name, getCurrentLoopIndex() + InstBuilder::genLoadLoopVar("index"), res));

            fContainer->closeLoop(sig);
        }

    } else {

        for (int index = 0; isList(L); L = tl(L), index++) {
            Tree sig = hd(L);
            string name = subst("fOutput$0", T(index));

            // 09/12/11 : HACK
            //int rate = getSigRate(sig);
            int rate = 1;
            fContainer->setOutputRate(index, rate);
            fContainer->openLoop("i");

            // Cast to external float
            ValueInst* res = InstBuilder::genCastFloatMacroInst(CS(sig));
            pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(name, getCurrentLoopIndex(), res));

            fContainer->closeLoop(sig);
        }
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
}

/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the code translation of sig as ValueInst*
 */
ValueInst* DAGInstructionsCompiler::CS(Tree sig)
{
    ValueInst* code;

    //cerr << "ENTER VectorCompiler::CS : "<< ppsig(sig) << endl;
    if (!getCompiledExpression(sig, code)) {
        code = generateCode(sig);
        //cerr << "CS : " << code << " for " << ppsig(sig) << endl;
        setCompiledExpression(sig, code);
    } else {

        // we require an already compiled expression
        // therefore we must update the dependencies of
        // the current loop
        int i;
        Tree x, d, r;
        CodeLoop* ls;
        CodeLoop* tl = fContainer->getCurLoop();

        if (fContainer->getLoopProperty(sig, ls)) {
            // sig has a loop property
            //cerr << "CASE SH : fBackwardLoopDependencies.insert : " << tl << " --depend(A)son--> " << ls << endl;
            tl->addBackwardDependency(ls);

        } else if (isSigFixDelay(sig, x, d) && fContainer->getLoopProperty(x,ls)) {
            //cerr << "CASE DL : fBackwardLoopDependencies.insert : " << tl << " --depend(B)son--> " << ls << endl;
             tl->addBackwardDependency(ls);

        } else if (isSigFixDelay(sig, x, d) && isProj(x, &i, r) && fContainer->getLoopProperty(r,ls)) {
            //cerr << "CASE DR : fBackwardLoopDependencies.insert : " << tl << " --depend(B)son--> " << ls << endl;
            tl->addBackwardDependency(ls);

        } if (isProj(sig, &i, r) && fContainer->getLoopProperty(r,ls)) {
            //cerr << "CASE R* : fBackwardLoopDependencies.insert : " << tl << " --depend(B)son--> " << ls << endl;
            tl->addBackwardDependency(ls);

		} else {
            if (isProj(sig, &i, r)) {
                //cerr << "SYMBOL RECURSIF EN COURS ??? " << *r << endl;
            } else if (getCertifiedSigType(sig)->variability() < kSamp) {
                //cerr << "SLOW EXPRESSION " << endl;
            } else {
                //cerr << "Expression absorbée" << *sig << endl;
            }

        }
    }
	return code;
}

ValueInst* DAGInstructionsCompiler::generateCode(Tree sig)
{
    generateCodeRecursions(sig);
    return generateCodeNonRec(sig);
}

void DAGInstructionsCompiler::generateCodeRecursions(Tree sig)
{
    Tree id, body;
    ValueInst*  code;
    //cerr << "DAGInstructionsCompiler::generateCodeRecursions( " << ppsig(sig) << " )" << endl;
    if (getCompiledExpression(sig, code)) {
        //cerr << "** ALREADY VISITED : " << code << " ===> " << ppsig(sig) << endl;
        return;
    } else if (isRec(sig, id, body)) {
        //cerr << "we have a recursive expression non compiled yet : " << ppsig(sig) << endl;
        setCompiledExpression(sig, InstBuilder::genNullInst());
        fContainer->openLoop(sig, "i");
        generateRec(sig, id, body);
        fContainer->closeLoop(sig);
    } else {
        // we go down the expression
        vector<Tree>  subsigs;
        int n = getSubSignals(sig, subsigs, false);
        for (int i = 0; i < n; i++) { generateCodeRecursions(subsigs[i]); }
    }
}

ValueInst* DAGInstructionsCompiler::generateCodeNonRec(Tree sig)
{
    ValueInst*  code;
    if (getCompiledExpression(sig, code)) {
        // already visited
        return code;
    } else {
        //cerr << "DAGInstructionsCompiler::generateCodeNonRec( " << ppsig(sig) << " )" << endl;
        code = generateLoopCode(sig);
        setCompiledExpression(sig, code);
        return code;
    }
}

/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the code translation of sig as ValueInst*
 */
ValueInst* DAGInstructionsCompiler::generateLoopCode(Tree sig)
{
    int     i;
    Tree    x;
    CodeLoop*   l;

    l = fContainer->getCurLoop();
    faustassert(l);
    //cerr << "VectorCompiler::OLDgenerateCode " << ppsig(sig) << endl;
    if (needSeparateLoop(sig)) {
        // we need a separate loop unless it's an old recursion
        if (isProj(sig, &i, x)) {
            // projection of a recursive group x
            if (l->hasRecDependencyIn(singleton(x))) {
                // x is already in the loop stack
                return InstructionsCompiler::generateCode(sig);
            } else {
                // x must be defined
                fContainer->openLoop(sig, "i");
                ValueInst* c = InstructionsCompiler::generateCode(sig);
                fContainer->closeLoop(sig);
                return c;
            }
        } else {
            fContainer->openLoop(sig, "i");
            ValueInst* c = InstructionsCompiler::generateCode(sig);
            fContainer->closeLoop(sig);
            return c;
        }
    } else {
        return InstructionsCompiler::generateCode(sig);
    }
}

ValueInst* DAGInstructionsCompiler::generateVariableStore(Tree sig, ValueInst* exp)
{
    ::Type t = getCertifiedSigType(sig);

    if (t->variability() == kSamp) {
        string vname;
        Typed::VarType ctype;
        getTypedNames(t, "Vector", ctype, vname);
        Address::AccessType var_access;
        generateVectorLoop(ctype, vname, exp, var_access);
        return InstBuilder::genLoadArrayVar(vname, var_access, getCurrentLoopIndex());
    } else {
        return InstructionsCompiler::generateVariableStore(sig, exp);
    }
}

ValueInst* DAGInstructionsCompiler::generateInput(Tree sig, int idx)
{
    if (gGlobal->gOpenCLSwitch || gGlobal->gCUDASwitch) { // HACK
        // "input" use as a name convention
        string name = subst("input$0", T(idx));
        ValueInst* res = InstBuilder::genLoadArrayFunArgsVar(name, getCurrentLoopIndex() + InstBuilder::genLoadLoopVar("index"));
        // Cast to internal float
        res = InstBuilder::genCastFloatInst(res);
        return generateCacheCode(sig, res);

     } else {
        // "fInput" use as a name convention
        string name = subst("fInput$0", T(idx));
        ValueInst* res = InstBuilder::genLoadArrayStackVar(name, getCurrentLoopIndex());
        // Cast to internal float
        res = InstBuilder::genCastFloatInst(res);
        return generateCacheCode(sig, res);
     }
}

ValueInst* DAGInstructionsCompiler::generateCacheCode(Tree sig, ValueInst* exp)
{
    string vname;
    Typed::VarType ctype;
    int sharing = getSharingCount(sig);
    ::Type t = getCertifiedSigType(sig);
    Occurences* o = fOccMarkup.retrieve(sig);
    int d = o->getMaxDelay();

    if (t->variability() < kSamp) {
        if (d == 0) {
            // non-sample, not delayed : same as scalar cache
            return InstructionsCompiler::generateCacheCode(sig, exp);

        } else {
            // it is a non-sample expressions but used delayed
            // we need a delay line
			getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
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
            getTypedNames(getCertifiedSigType(sig), "Yec", ctype, vname);
            Address::AccessType var_access;
            generateDelayLine(exp, ctype, vname, d, var_access);
            setVectorNameProperty(sig, vname);

            if (verySimple(sig)) {
                return exp;
            } else {
                if (d < gGlobal->gMaxCopyDelay) {
                    //return subst("$0[i]", vname);
                    return InstBuilder::genLoadArrayVar(vname, var_access, getCurrentLoopIndex());
                } else {
                    // we use a ring buffer
                    string vname_idx = vname + "_idx";
                    int mask = pow2limit(d + gGlobal->gVecSize) - 1;
                    //return subst("$0[($0_idx+i) & $1]", vname, mask);
                    FIRIndex index1 = (getCurrentLoopIndex() + InstBuilder::genLoadStructVar(vname_idx)) & InstBuilder::genInt32NumInst(mask);
                    return InstBuilder::genLoadArrayStructVar(vname, index1);
                }
            }
        } else {
            // not delayed
            if (sharing > 1 && !verySimple(sig)) {
                // shared and not simple : we need a vector
                // cerr << "ZEC : " << ppsig(sig) << endl;
                getTypedNames(getCertifiedSigType(sig), "Zec", ctype, vname);
                Address::AccessType var_access;
                generateDelayLine(exp, ctype, vname, d, var_access);
                setVectorNameProperty(sig, vname);
                // return subst("$0[i]", vname);
                return InstBuilder::genLoadArrayVar(vname, var_access, getCurrentLoopIndex());
           } else {
                // not shared or simple : no cache needed
                return exp;
            }
        }
    }
}

// Code generation

/**
 * Test if a signal need to be compiled in a separate loop.
 * @param sig the signal expression to test.
 * @return true if a separate loop is needed
 */
bool DAGInstructionsCompiler::needSeparateLoop(Tree sig)
{
    Occurences* o = fOccMarkup.retrieve(sig);
    ::Type t = getCertifiedSigType(sig);
    int c = getSharingCount(sig);
    bool b;

    int i;
    Tree x,y;

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
    string vname;
    ValueInst* code = CS(exp); // ensure exp is compiled to have a vector name
    int d, mxd = fOccMarkup.retrieve(exp)->getMaxDelay();

    if (!getVectorNameProperty(exp, vname)) {
        if (mxd == 0) {
            //cerr << "it is a pure zero delay : " << code << endl;
            return code;
        } else {
            stringstream error;
            error << "ERROR : no vector name for : " << ppsig(exp) << endl;
            throw faustexception(error.str());
        }
    }

    if (mxd == 0) {
        // not a real vector name but a scalar name
        //return subst("$0[i]", vname);
        return InstBuilder::genLoadArrayStackVar(vname, getCurrentLoopIndex());

    } else if (mxd < gGlobal->gMaxCopyDelay) {
        if (isSigInt(delay, &d)) {
            if (d == 0) {
                // return subst("$0[i]", vname);
                return InstBuilder::genLoadArrayStackVar(vname, getCurrentLoopIndex());
            } else {
                // return subst("$0[i-$1]", vname, T(d));
                FIRIndex index = getCurrentLoopIndex() - InstBuilder::genInt32NumInst(d);
                return InstBuilder::genLoadArrayStackVar(vname, index);
            }
        } else {
            // return subst("$0[i-$1]", vname, CS(delay));
            FIRIndex index = getCurrentLoopIndex() - CS(delay);
            return InstBuilder::genLoadArrayStackVar(vname, index);
        }
    } else {

        // long delay : we use a ring buffer of size 2^x
        int N = pow2limit(mxd + gGlobal->gVecSize);
        string vname_idx = vname + "_idx";

        if (isSigInt(delay, &d)) {
            if (d == 0) {
                //return subst("$0[($0_idx+i)&$1]", vname, T(N-1));
                FIRIndex index1 = (getCurrentLoopIndex() + InstBuilder::genLoadStructVar(vname_idx)) & InstBuilder::genInt32NumInst(N-1);
                return InstBuilder::genLoadArrayStructVar(vname, index1);
            } else {
                //return subst("$0[($0_idx+i-$2)&$1]", vname, T(N-1), T(d));
                FIRIndex index1 = getCurrentLoopIndex() + InstBuilder::genLoadStructVar(vname_idx);
                FIRIndex index2 = index1 - InstBuilder::genInt32NumInst(d);
                FIRIndex index3 = index2 & InstBuilder::genInt32NumInst(N-1);
                return InstBuilder::genLoadArrayStructVar(vname, index3);
            }
        } else {
            //return subst("$0[($0_idx+i-$2)&$1]", vname, T(N-1), CS(delay));
            FIRIndex index1 = getCurrentLoopIndex() + InstBuilder::genLoadStructVar(vname_idx);
            FIRIndex index2 = index1 - CS(delay);
            FIRIndex index3 = index2 & InstBuilder::genInt32NumInst(N-1);
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
        return InstBuilder::genLoadArrayVar(vname, var_access, getCurrentLoopIndex());
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
    DeclareVarInst* table_inst = InstBuilder::genDecStackVar(vname, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(ctype), gGlobal->gVecSize));
    pushComputeBlockMethod(table_inst);

    // -- compute the new samples
    // $0[i] = $1;"
    pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(vname, getCurrentLoopIndex(), exp));

    // Set desired variable access
    var_access = Address::kStack;
}

void DAGInstructionsCompiler::generateDlineLoop(Typed::VarType ctype, const string& vname, int delay, ValueInst* exp, Address::AccessType& var_access)
{
    BasicTyped* typed = InstBuilder::genBasicTyped(ctype);

    if (delay < gGlobal->gMaxCopyDelay) {

        // Implementation of a copy based delayline
        // create names for temporary and permanent storage
	    string buf = subst("$0_tmp", vname);
        string pmem = subst("$0_perm", vname);

        // constraints delay size to be multiple of 4
        delay = (delay+3) & -4;

        // allocate permanent storage for delayed samples
        pushClearMethod(generateInitArray(pmem, ctype, delay));

        // compute method

        // -- declare a buffer and a "shifted" vector
        DeclareVarInst* table_inst1 = InstBuilder::genDecStackVar(buf, InstBuilder::genArrayTyped(typed, gGlobal->gVecSize + delay));
        pushComputeBlockMethod(table_inst1);

        ValueInst* address_value = InstBuilder::genLoadArrayStackVarAddress(buf, InstBuilder::genInt32NumInst(delay));
        DeclareVarInst* table_inst2 = InstBuilder::genDecStackVar(vname, InstBuilder::genArrayTyped(typed, 0), address_value);
        pushComputeBlockMethod(table_inst2);

        // -- copy the stored samples to the delay line
        pushComputePreDSPMethod(generateCopyArray(buf, pmem, delay));

        // -- compute the new samples
        pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(vname, getCurrentLoopIndex(), exp));

        // -- copy back to stored samples
        pushComputePostDSPMethod(generateCopyBackArray(pmem, buf, delay));

        // Set desired variable access
        var_access = Address::kStack;

    } else {

        // Implementation of a ring-buffer delayline, the size should be large enough and aligned on a power of two
        delay = pow2limit(delay + gGlobal->gVecSize);

        // create names for temporary and permanent storage
        string idx = subst("$0_idx", vname);
        string idx_save = subst("$0_idx_save", vname);

        // allocate permanent storage for delayed samples
        pushClearMethod(generateInitArray(vname, ctype, delay));
        pushDeclare(InstBuilder::genDecStructVar(idx, InstBuilder::genBasicTyped(Typed::kInt32)));
        pushDeclare(InstBuilder::genDecStructVar(idx_save, InstBuilder::genBasicTyped(Typed::kInt32)));

        // init permanent memory
        pushClearMethod(InstBuilder::genStoreStructVar(idx, InstBuilder::genInt32NumInst(0)));
        pushClearMethod(InstBuilder::genStoreStructVar(idx_save, InstBuilder::genInt32NumInst(0)));

        // -- update index
        FIRIndex index1 = FIRIndex(InstBuilder::genLoadStructVar(idx)) + InstBuilder::genLoadStructVar(idx_save);
        FIRIndex index2 = index1 & InstBuilder::genInt32NumInst(delay-1);

        pushComputePreDSPMethod(InstBuilder::genStoreStructVar(idx, index2));

        // -- compute the new samples
        FIRIndex index3 = getCurrentLoopIndex() + InstBuilder::genLoadStructVar(idx);
        FIRIndex index4 = index3 & InstBuilder::genInt32NumInst(delay-1);

        pushComputeDSPMethod(InstBuilder::genStoreArrayStructVar(vname, index4, exp));

        // -- save index
        pushComputePostDSPMethod(InstBuilder::genStoreStructVar(idx_save, InstBuilder::genLoadStackVar("count")));

        // Set desired variable access
        var_access = Address::kStruct;
    }
}

StatementInst* DAGInstructionsCompiler::generateCopyBackArray(const string& vname_to, const string& vname_from, int size)
{
    string index = "j";

    // Generates init table loop
    DeclareVarInst* loop_decl = InstBuilder::genDecLoopVar(index, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(0));
    ValueInst* loop_end = InstBuilder::genLessThan(loop_decl->load(), InstBuilder::genInt32NumInst(size));
    StoreVarInst* loop_increment = loop_decl->store(InstBuilder::genAdd(loop_decl->load(), 1));

    ForLoopInst* loop = InstBuilder::genForLoopInst(loop_decl, loop_end, loop_increment);

    FIRIndex load_index = FIRIndex(InstBuilder::genLoadStackVar("count")) + loop_decl->load();
    ValueInst* load_value = InstBuilder::genLoadArrayStackVar(vname_from, load_index);

    loop->pushFrontInst(InstBuilder::genStoreArrayStructVar(vname_to, loop_decl->load(), load_value));
    return loop;
}

ValueInst* DAGInstructionsCompiler::generateWaveform(Tree sig)
{
    string vname;
    int size;

    declareWaveform(sig, vname, size);
    
    string idx = subst("$0_idx", vname);
    FIRIndex index1 = (FIRIndex(InstBuilder::genLoadStructVar(idx)) + InstBuilder::genLoadStackVar("count")) % InstBuilder::genInt32NumInst(size);
    pushComputePostDSPMethod(InstBuilder::genStoreStructVar(idx, index1));
    FIRIndex index2 = (FIRIndex(InstBuilder::genLoadStructVar(idx)) + getCurrentLoopIndex()) % InstBuilder::genInt32NumInst(size);
    return generateCacheCode(sig, InstBuilder::genLoadArrayStaticStructVar(vname, index2));
}
