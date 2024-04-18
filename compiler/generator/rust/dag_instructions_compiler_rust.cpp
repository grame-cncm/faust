/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2017-2021 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "dag_instructions_compiler_rust.hh"
#include "fir_to_fir.hh"
#include "sigtyperules.hh"
#include "timing.hh"

using std::string;

void DAGInstructionsCompilerRust::compileMultiSignal(Tree L)
{
    startTiming("compileMultiSignal");

    // Has to be done *after* gMachinePtrSize is set by the actual backend
    gGlobal->initTypeSizeMap();

    L = prepare(L);  // Optimize, share and annotate expression

    Typed* type = IB::genBasicTyped(Typed::kFloatMacro_ptr);
    pushComputeBlockMethod(
        IB::genDeclareBufferIterators("input", "inputs", fContainer->inputs(), type, false, true));
    pushComputeBlockMethod(IB::genDeclareBufferIterators("output", "outputs", fContainer->outputs(),
                                                         type, true, true));

    for (int index = 0; isList(L); L = tl(L), index++) {
        Tree   sig  = hd(L);
        string name = subst("output$0", T(index));

        fContainer->openLoop("i");

        // Possibly cast to external float
        ValueInst* res = genCastedOutput(getCertifiedSigType(sig)->nature(), CS(sig));

        if (gGlobal->gComputeMix) {
            ValueInst* res1 =
                IB::genAdd(res, IB::genLoadArrayStackVar(name, getCurrentLoopIndex()));
            pushComputeDSPMethod(IB::genStoreArrayStackVar(name, getCurrentLoopIndex(), res1));
        } else {
            pushComputeDSPMethod(IB::genStoreArrayStackVar(name, getCurrentLoopIndex(), res));
        }

        fContainer->closeLoop(sig);
    }

    generateUserInterfaceTree(fUITree.prepareUserInterfaceTree(), true);
    generateMacroInterfaceTree("", fUITree.prepareUserInterfaceTree());
    if (fDescription) {
        fDescription->ui(fUITree.prepareUserInterfaceTree());
    }

    // Apply FIR to FIR transformations
    fContainer->processFIR();

    endTiming("compileMultiSignal");
}

StatementInst* DAGInstructionsCompilerRust::generateInitArray(const string& vname,
                                                              BasicTyped* ctype, int delay)
{
    ValueInst*  init  = IB::genTypedZero(ctype);
    BasicTyped* typed = ctype;

    // Generates table declaration
    pushDeclare(IB::genDecStructVar(vname, IB::genArrayTyped(typed, delay)));

    Values args;
    args.push_back(IB::genLoadStructVar(vname));
    args.push_back(init);
    return IB::genVoidFunCallInst("fill", args, true);
}

StatementInst* DAGInstructionsCompilerRust::generateShiftArray(const string& vname, int delay)
{
    string index = gGlobal->getFreshID("j");

    ValueInst* upperBound = IB::genInt32NumInst(delay);
    ValueInst* lowerBound = IB::genInt32NumInst(1);

    SimpleForLoopInst* loop        = IB::genSimpleForLoopInst(index, upperBound, lowerBound, true);
    LoadVarInst*       loadVarInst = IB::genLoadVarInst(IB::genNamedAddress(index, Address::kLoop));
    ValueInst*         load_value2 = IB::genSub(loadVarInst, IB::genInt32NumInst(1));
    ValueInst*         load_value3 = IB::genLoadArrayStructVar(vname, load_value2);

    loop->pushFrontInst(IB::genStoreArrayStructVar(vname, loadVarInst, load_value3));
    return loop;
}

StatementInst* DAGInstructionsCompilerRust::generateCopyArray(const string& vname_to,
                                                              const string& vname_from, int size)
{
    string index = gGlobal->getFreshID("j");

    ValueInst*         upperBound  = IB::genInt32NumInst(size);
    SimpleForLoopInst* loop        = IB::genSimpleForLoopInst(index, upperBound);
    LoadVarInst*       loadVarInst = IB::genLoadVarInst(IB::genNamedAddress(index, Address::kLoop));
    ValueInst*         load_value  = IB::genLoadArrayStructVar(vname_from, loadVarInst);

    loop->pushFrontInst(IB::genStoreArrayStackVar(vname_to, loadVarInst, load_value));
    return loop;
}
