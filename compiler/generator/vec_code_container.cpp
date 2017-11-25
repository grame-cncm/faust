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

#include "vec_code_container.hh"
#include "global.hh"
#include "fir_to_fir.hh"
#include "fir_code_checker.hh"
#include "exception.hh"

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

BlockInst* VectorCodeContainer::generateDAGLoopVariant0(const string& counter)
{
    string index = "index";
    string count = "count";

    // Define result block
    BlockInst* block_res = InstBuilder::genBlockInst();

    // Declare the "index" variable outside the loop
    DeclareVarInst* index_dec = InstBuilder::genDecStackVar(index, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(0));
    block_res->pushBackInst(index_dec);
    block_res->pushBackInst(InstBuilder::genLabelInst("/* Main loop */"));

    BlockInst* loop_code = InstBuilder::genBlockInst();

    // Generate local input/output access
    generateLocalInputs(loop_code, index);
    generateLocalOutputs(loop_code, index);

    // Generate : int count = 32;
    DeclareVarInst* count_dec1 = InstBuilder::genDecStackVar(count, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(gGlobal->gVecSize));
    loop_code->pushBackInst(count_dec1);

    // Generates the loop DAG
    generateDAGLoop(loop_code, count_dec1);

    // Generates the DAG enclosing loop
    StoreVarInst* loop_init = index_dec->store(InstBuilder::genInt32NumInst(0));

    ValueInst* loop_end = InstBuilder::genLessEqual(index_dec->load(),
        InstBuilder::genSub(InstBuilder::genLoadStackVar(counter), InstBuilder::genInt32NumInst(gGlobal->gVecSize)));

    StoreVarInst* loop_increment = index_dec->store(InstBuilder::genAdd(index_dec->load(), gGlobal->gVecSize));

    StatementInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment, loop_code);

    // Put loop in block_res
    block_res->pushBackInst(loop);

    // Remaining frames
    block_res->pushBackInst(InstBuilder::genLabelInst("/* Remaining frames */"));

    ValueInst* if_cond = InstBuilder::genLessThan(InstBuilder::genLoadStackVar(index), InstBuilder::genLoadStackVar(counter));

    BlockInst* then_block = InstBuilder::genBlockInst();

    // Generate local input/output access
    generateLocalInputs(then_block, index);
    generateLocalOutputs(then_block, index);

    // Generate : int count = fullcount-index;
    DeclareVarInst* count_dec2 = 
        InstBuilder::genDecStackVar(count, InstBuilder::genBasicTyped(Typed::kInt32), 
            InstBuilder::genSub(InstBuilder::genLoadStackVar(counter), InstBuilder::genLoadStackVar(index)));

    then_block->pushBackInst(count_dec2);

    // Generates the loop DAG
    generateDAGLoop(then_block, count_dec2);

    block_res->pushBackInst(InstBuilder::genIfInst(if_cond, then_block));
    return block_res;
}

BlockInst* VectorCodeContainer::generateDAGLoopVariant1(const string& counter)
{
    string index = "index";
    string count = "count";
    
    BlockInst* loop_code = InstBuilder::genBlockInst();

    // Generate local input/output access
    generateLocalInputs(loop_code, index);
    generateLocalOutputs(loop_code, index);

    // Generate : int count = min(32, (fullcount - index))
    ValueInst* init1 = InstBuilder::genLoadStackVar(counter);
    ValueInst* init2 = InstBuilder::genSub(init1, InstBuilder::genLoadLoopVar(index));
    list<ValueInst*> min_fun_args;
    min_fun_args.push_back(InstBuilder::genInt32NumInst(gGlobal->gVecSize));
    min_fun_args.push_back(init2);
    ValueInst* init3 = InstBuilder::genFunCallInst("min", min_fun_args);
    DeclareVarInst* count_dec = InstBuilder::genDecStackVar(count, InstBuilder::genBasicTyped(Typed::kInt32), init3);
    loop_code->pushBackInst(count_dec);

    // Generates the loop DAG
    generateDAGLoop(loop_code, count_dec);

    // Generates the DAG enclosing loop
    DeclareVarInst* loop_dec = InstBuilder::genDecLoopVar(index, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(0));
    ValueInst* loop_end = InstBuilder::genLessThan(loop_dec->load(), InstBuilder::genLoadStackVar(counter));
    StoreVarInst* loop_increment = loop_dec->store(InstBuilder::genAdd(loop_dec->load(), gGlobal->gVecSize));

    StatementInst* loop = InstBuilder::genForLoopInst(loop_dec, loop_end, loop_increment, loop_code);
    
    BlockInst* res_block = InstBuilder::genBlockInst();
    res_block->pushBackInst(loop);
    return res_block;
}

void VectorCodeContainer::processFIR(void)
{
    // Default FIR to FIR transformations
    CodeContainer::processFIR();
    
    // If stack variables take to much room, move them in struct
    VariableSizeCounter counter(Address::kStack);
    generateComputeBlock(&counter);
    
    if (counter.fSizeBytes > gGlobal->gMachineMaxStackSize) {
        // Transform stack array variables in struct variables
        moveStack2Struct();
    } else {
        // Sort arrays to be at the begining
        //fComputeBlockInstructions->fCode.sort(sortArrayDeclarations);
    }
    
    string fullcount = "fullcount";
    DeclareVarInst* fullcount_dec = InstBuilder::genDecStackVar(fullcount, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genLoadFunArgsVar(fFullCount));
    pushComputeBlockMethod(fullcount_dec);
    
    if (gGlobal->gVectorLoopVariant == 0) {
        fDAGBlock = generateDAGLoopVariant0(fullcount);
    } else if (gGlobal->gVectorLoopVariant == 1) {
        fDAGBlock = generateDAGLoopVariant1(fullcount);
    } else {
        fDAGBlock = NULL;
    }
    
    faustassert(fDAGBlock);
    
    // Verify code
    /*
    Still not working for Array variables access
    
    FIRCodeChecker verifier;
    BlockInst* global_block = flattenFIR();
    global_block->accept(&verifier);
    
    if (verifier.fError) {
        //throw faustexception("Incorrect FIR code\n");
    }
    */
}

BlockInst* VectorCodeContainer::flattenFIR(void)
{
    BlockInst* global_block = CodeContainer::flattenFIR();
    global_block->pushBackInst(fDAGBlock);
    return global_block;
}
