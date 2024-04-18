/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include "vec_code_container.hh"
#include "exception.hh"
#include "fir_code_checker.hh"
#include "fir_to_fir.hh"
#include "global.hh"

using namespace std;

void VectorCodeContainer::moveStack2Struct()
{
    // Transform stack variables in struct variables
    VariableMover::Move(this, "tmp");
    VariableMover::Move(this, "Zec");
    VariableMover::Move(this, "Yec");
    VariableMover::Move(this, "Rec");

    // Remove marked variables from fComputeBlockInstructions
    RemoverCloneVisitor remover;
    fComputeBlockInstructions = static_cast<BlockInst*>(fComputeBlockInstructions->clone(&remover));
}

void VectorCodeContainer::generateLocalInputs(BlockInst* loop_code, const string& index)
{
    // Generates line like: FAUSTFLOAT* input0 = &input0_ptr[index];
    Typed* type = IB::genArrayTyped(IB::genFloatMacroTyped(), 0);

    for (int i = 0; i < inputs(); i++) {
        string name1 = subst("input$0", T(i));
        string name2 = subst("input$0_ptr", T(i));
        loop_code->pushBackInst(IB::genDecStackVar(
            name1, type, IB::genLoadArrayStackVarAddress(name2, IB::genLoadLoopVar(index))));
    }
}

void VectorCodeContainer::generateLocalOutputs(BlockInst* loop_code, const string& index)
{
    // Generates line like: FAUSTFLOAT* ouput0 = &output0_ptr[index];
    Typed* type = IB::genArrayTyped(IB::genFloatMacroTyped(), 0);

    for (int i = 0; i < outputs(); i++) {
        string name1 = subst("output$0", T(i));
        string name2 = subst("output$0_ptr", T(i));
        loop_code->pushBackInst(IB::genDecStackVar(
            name1, type, IB::genLoadArrayStackVarAddress(name2, IB::genLoadLoopVar(index))));
    }
}

BlockInst* VectorCodeContainer::generateDAGLoopVariant0(const string& counter)
{
    string index = "vindex";
    string size  = "vsize";

    // Define result block
    BlockInst* block_res = IB::genBlockInst();

    // Declare the "index" variable outside the loop
    DeclareVarInst* index_dec =
        IB::genDecLoopVar(index, IB::genInt32Typed(), IB::genInt32NumInst(0));
    block_res->pushBackInst(index_dec);
    block_res->pushBackInst(IB::genLabelInst("/* Main loop */"));

    BlockInst* loop_code = IB::genBlockInst();

    // Generate local input/output access
    generateLocalInputs(loop_code, index);
    generateLocalOutputs(loop_code, index);

    // Generate : int count = 32;
    DeclareVarInst* size_dec =
        IB::genDecLoopVar(size, IB::genInt32Typed(), IB::genInt32NumInst(gGlobal->gVecSize));
    loop_code->pushBackInst(size_dec);

    // Debug code
    /*
    loop_code->pushBackInst(IB::genLabelInst("std::cout << vsize << std::endl;"));
    loop_code->pushBackInst(IB::genLabelInst("std::cout << fullcount << std::endl;"));
    loop_code->pushBackInst(IB::genLabelInst("std::cout << vindex << std::endl;"));
    */

    // Generates the loop DAG
    generateDAGLoop(loop_code, size_dec->load());

    // Generates the DAG enclosing loop
    StoreVarInst* loop_init = index_dec->store(IB::genInt32NumInst(0));

    ValueInst* loop_end = IB::genLessEqual(
        index_dec->load(), IB::genSub(IB::genLoadFunArgsVar(counter), gGlobal->gVecSize));
    StoreVarInst* loop_increment =
        index_dec->store(IB::genAdd(index_dec->load(), gGlobal->gVecSize));
    StatementInst* loop = IB::genForLoopInst(loop_init, loop_end, loop_increment, loop_code, true);

    // Put loop in block_res
    block_res->pushBackInst(loop);

    // Remaining frames
    block_res->pushBackInst(IB::genLabelInst("/* Remaining frames */"));

    ValueInst* if_cond = IB::genLessThan(index_dec->load(), IB::genLoadFunArgsVar(counter));

    BlockInst* then_block = IB::genBlockInst();

    // Generate local input/output access
    generateLocalInputs(then_block, index);
    generateLocalOutputs(then_block, index);

    // Generate : int count = fullcount-index;
    DeclareVarInst* size_dec1 = IB::genDecLoopVar(
        size, IB::genInt32Typed(), IB::genSub(IB::genLoadFunArgsVar(counter), index_dec->load()));

    then_block->pushBackInst(size_dec1);

    // Debug code
    /*
    then_block->pushBackInst(IB::genLabelInst("std::cout << vsize << std::endl;"));
    then_block->pushBackInst(IB::genLabelInst("std::cout << fullcount << std::endl;"));
    then_block->pushBackInst(IB::genLabelInst("std::cout << vindex << std::endl;"));
    */

    // Generates the loop DAG
    generateDAGLoop(then_block, size_dec1->load());

    block_res->pushBackInst(IB::genIfInst(if_cond, then_block));
    return block_res;
}

BlockInst* VectorCodeContainer::generateDAGLoopVariant1(const string& counter)
{
    string index = "vindex";
    string size  = "vsize";

    BlockInst* loop_code = IB::genBlockInst();

    // Generates the DAG enclosing loop
    DeclareVarInst* loop_dec =
        IB::genDecLoopVar(index, IB::genInt32Typed(), IB::genInt32NumInst(0));

    // Generate local input/output access
    generateLocalInputs(loop_code, index);
    generateLocalOutputs(loop_code, index);

    // Generate : int count = min(32, (fullcount - index))
    ValueInst* init1 = IB::genLoadFunArgsVar(counter);
    ValueInst* init2 = IB::genSub(init1, loop_dec->load());
    Values     min_fun_args;
    min_fun_args.push_back(IB::genInt32NumInst(gGlobal->gVecSize));
    min_fun_args.push_back(init2);
    ValueInst*      init3    = IB::genFunCallInst("min_i", min_fun_args);
    DeclareVarInst* size_dec = IB::genDecLoopVar(size, IB::genInt32Typed(), init3);
    loop_code->pushBackInst(size_dec);

    // Debug code
    /*
    loop_code->pushBackInst(IB::genLabelInst("std::cout << vsize << std::endl;"));
    loop_code->pushBackInst(IB::genLabelInst("std::cout << fullcount << std::endl;"));
    loop_code->pushBackInst(IB::genLabelInst("std::cout << vindex << std::endl;"));
    */

    // Generates the loop DAG
    generateDAGLoop(loop_code, size_dec->load());

    ValueInst*    loop_end = IB::genLessThan(loop_dec->load(), IB::genLoadFunArgsVar(counter));
    StoreVarInst* loop_increment = loop_dec->store(IB::genAdd(loop_dec->load(), gGlobal->gVecSize));
    StatementInst* loop = IB::genForLoopInst(loop_dec, loop_end, loop_increment, loop_code, true);

    BlockInst* res_block = IB::genBlockInst();
    res_block->pushBackInst(loop);
    return res_block;
}

BlockInst* VectorCodeContainer::generateDAGLoopVariant2(const string& counter)
{
    BlockInst* res_block = IB::genBlockInst();
    string     index     = "vindex";
    res_block->pushBackInst(
        IB::genDecStackVar("vindex", IB::genInt32Typed(), IB::genInt32NumInst(0)));

    // Generate local input/output access
    generateLocalInputs(res_block, index);
    generateLocalOutputs(res_block, index);

    // Generates the loop DAG
    generateDAGLoop(res_block, IB::genInt32NumInst(gGlobal->gVecSize));
    return res_block;
}

void VectorCodeContainer::processFIR(void)
{
    // Default FIR to FIR transformations
    CodeContainer::processFIR();

    // If stack variables take too much room, move them in struct
    // dump2FIR(fComputeBlockInstructions);
    VariableSizeCounter counter(Address::kStack);
    generateComputeBlock(&counter);

    /*
     Possibly remove LoadVarAddress. The remover has to be shared between
     fComputeBlockInstructions and fDAGBlock, so a *unique* one is defined here.
    */
    VarAddressRemover remover;
    if (gGlobal->gRemoveVarAddress) {
        fComputeBlockInstructions = remover.getCode(fComputeBlockInstructions);
    }

    if (counter.fSizeBytes > gGlobal->gMachineMaxStackSize) {
        // Transform stack array variables in struct variables
        moveStack2Struct();
    } else {
        // Sort arrays to be at the beginning
        // fComputeBlockInstructions->fCode.sort(sortArrayDeclarations);
    }

    if (gGlobal->gVectorLoopVariant == 0) {
        fDAGBlock = generateDAGLoopVariant0(fFullCount);
    } else if (gGlobal->gVectorLoopVariant == 1) {
        fDAGBlock = generateDAGLoopVariant1(fFullCount);
    } else if (gGlobal->gVectorLoopVariant == 2) {
        fDAGBlock = generateDAGLoopVariant2(fFullCount);
    } else {
        faustassert(false);
    }

    // Possibly remove LoadVarAddress
    if (gGlobal->gRemoveVarAddress) {
        fDAGBlock = remover.getCode(fDAGBlock);
    }

    // Rewrite "Rec/Vec" indexes in iZone/fZone access
    if (gGlobal->gMemoryManager >= 1) {
        fDAGBlock = gGlobal->gIntZone->getCode(fDAGBlock);
        fDAGBlock = gGlobal->gRealZone->getCode(fDAGBlock);
    }

    // Verify code
    /*
    Still not working for Array variables access

    FIRCodeChecker verifier;
    BlockInst* global_block = flattenFIR();
    global_block->accept(&verifier);

    if (verifier.fError) {
        throw faustexception("Incorrect FIR code\n");
    }
    */
}

BlockInst* VectorCodeContainer::flattenFIR(void)
{
    BlockInst* global_block = CodeContainer::flattenFIR();
    global_block->pushBackInst(fDAGBlock);
    return global_block;
}
