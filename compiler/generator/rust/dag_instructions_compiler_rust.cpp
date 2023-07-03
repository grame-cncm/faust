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

    Typed* type = InstBuilder::genBasicTyped(Typed::kFloatMacro_ptr);
    pushComputeBlockMethod(
        InstBuilder::genDeclareBufferIterators("input", "inputs", fContainer->inputs(), type, false, true));
    pushComputeBlockMethod(
        InstBuilder::genDeclareBufferIterators("output", "outputs", fContainer->outputs(), type, true, true));

    for (int index = 0; isList(L); L = tl(L), index++) {
        Tree   sig  = hd(L);
        string name = subst("output$0", T(index));

        fContainer->openLoop("i");

        // Possibly cast to external float
        ValueInst* res = genCastedOutput(getCertifiedSigType(sig)->nature(), CS(sig));

        if (gGlobal->gComputeMix) {
            ValueInst* res1 = InstBuilder::genAdd(res, InstBuilder::genLoadArrayStackVar(name, getCurrentLoopIndex()));
            pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(name, getCurrentLoopIndex(), res1));
        } else {
            pushComputeDSPMethod(InstBuilder::genStoreArrayStackVar(name, getCurrentLoopIndex(), res));
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

StatementInst* DAGInstructionsCompilerRust::generateInitArray(const string& vname, Typed::VarType ctype, int delay)
{
    ValueInst*  init  = InstBuilder::genTypedZero(ctype);
    BasicTyped* typed = InstBuilder::genBasicTyped(ctype);

    // Generates table declaration
    pushDeclare(InstBuilder::genDecStructVar(vname, InstBuilder::genArrayTyped(typed, delay)));

    Values args;
    args.push_back(InstBuilder::genLoadStructVar(vname));
    args.push_back(init);
    return InstBuilder::genVoidFunCallInst("fill", args, true);

    //    ValueInst*  init  = InstBuilder::genTypedZero(ctype);
    //    BasicTyped* typed = InstBuilder::genBasicTyped(ctype);
    //    string      index = gGlobal->getFreshID("l");
    //
    //    // Generates table declaration
    //    pushDeclare(InstBuilder::genDecStructVar(vname, InstBuilder::genArrayTyped(typed, delay)));
    //
    //    ValueInst* upperBound = InstBuilder::genInt32NumInst(delay);
    //    // Generates init table loop
    //    SimpleForLoopInst* loop = InstBuilder::genSimpleForLoopInst(index, upperBound);
    //
    //    LoadVarInst* loadVarInst = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop));
    //    loop->pushFrontInst(InstBuilder::genStoreArrayStructVar(vname, loadVarInst, init));
    //    return loop;
}

StatementInst* DAGInstructionsCompilerRust::generateShiftArray(const string& vname, int delay)
{
    std::cout << "generateShiftArray " << vname << " " << delay << std::endl;

    string index = gGlobal->getFreshID("j");

    ValueInst* upperBound = InstBuilder::genInt32NumInst(delay);
    ValueInst* lowerBound = InstBuilder::genInt32NumInst(1);

    SimpleForLoopInst* loop        = InstBuilder::genSimpleForLoopInst(index, upperBound, lowerBound, true);
    LoadVarInst*       loadVarInst = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop));
    ValueInst*         load_value2 = InstBuilder::genSub(loadVarInst, InstBuilder::genInt32NumInst(1));
    ValueInst*         load_value3 = InstBuilder::genLoadArrayStructVar(vname, load_value2);

    loop->pushFrontInst(InstBuilder::genStoreArrayStructVar(vname, loadVarInst, load_value3));
    return loop;
}

StatementInst* DAGInstructionsCompilerRust::generateCopyArray(const string& vname_to, const string& vname_from,
                                                              int size)
{
    //    std::cout << "generateCopyArray " << vname_to << " " << vname_from << " " << size << std::endl;
    //    Values args;
    //    args.push_back(InstBuilder::genLoadStackVar(vname_to));
    //    args.push_back(
    //        InstBuilder::genLoadVarAddressInst(InstBuilder::genNamedAddress(vname_from,
    //        Address::AccessType::kStruct)));
    //    return InstBuilder::genVoidFunCallInst("copy_from_slice", args, true);

    string index = gGlobal->getFreshID("j");

    ValueInst*         upperBound  = InstBuilder::genInt32NumInst(size);
    SimpleForLoopInst* loop        = InstBuilder::genSimpleForLoopInst(index, upperBound);
    LoadVarInst*       loadVarInst = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop));
    ValueInst*         load_value  = InstBuilder::genLoadArrayStructVar(vname_from, loadVarInst);

    loop->pushFrontInst(InstBuilder::genStoreArrayStackVar(vname_to, loadVarInst, load_value));
    return loop;
}
