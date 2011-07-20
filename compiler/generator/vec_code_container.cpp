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
#include "vec_code_container.hh"

using namespace std;

StatementInst* VectorCodeContainer::generateDAGLoopVariant0(const string& counter)
{
    string index = "index";

    // Define result block
    BlockInst* block_res = InstBuilder::genBlockInst();

    // Declare the "index" variable outside the loop
    DeclareVarInst* index_dec = InstBuilder::genDecStackVar(index, InstBuilder::genBasicTyped(Typed::kInt));
    block_res->pushBackInst(index_dec);
    block_res->pushBackInst(InstBuilder::genLabelInst("// Main loop"));

    BlockInst* loop_code = InstBuilder::genBlockInst();

    // Generate local input/output access
    generateLocalInputs(loop_code);
    generateLocalOutputs(loop_code);

    // Generate : int count = 32;
    DeclareVarInst* count_dec1 = InstBuilder::genDecStackVar("count", InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(gVecSize));
    loop_code->pushBackInst(count_dec1);

    // Generates the loop DAG
    generateDAGLoop(loop_code, count_dec1);

    // Generates the DAG enclosing loop
    StoreVarInst* loop_init = index_dec->store(InstBuilder::genIntNumInst(0));

    ValueInst* loop_end = InstBuilder::genBinopInst(kLE, index_dec->load(),
        InstBuilder::genSub(InstBuilder::genLoadFunArgsVar(counter), InstBuilder::genIntNumInst(gVecSize)));

    StoreVarInst* loop_increment = index_dec->store(InstBuilder::genAdd(index_dec->load(), gVecSize));

    StatementInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment, loop_code);

    // Put loop in block_res
    block_res->pushBackInst(loop);

    // Remaining frames
    block_res->pushBackInst(InstBuilder::genLabelInst("// Remaining frames"));

    ValueInst* if_cond = InstBuilder::genLessThan(InstBuilder::genLoadStackVar(index), InstBuilder::genLoadFunArgsVar(counter));

    BlockInst* then_block = InstBuilder::genBlockInst();

    // Generate local input/output access
    generateLocalInputs(then_block);
    generateLocalOutputs(then_block);

    // Generate : int count = fullcount-index;
    DeclareVarInst* count_dec2 = InstBuilder::genDecStackVar("count", InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genBinopInst(kSub,
                                    InstBuilder::genLoadFunArgsVar(counter), InstBuilder::genLoadStackVar(index)));

    then_block->pushBackInst(count_dec2);

    // Generates the loop DAG
    generateDAGLoop(then_block, count_dec2);

    block_res->pushBackInst(InstBuilder::genIfInst(if_cond, then_block));
    return block_res;
}

StatementInst* VectorCodeContainer::generateDAGLoopVariant1(const string& counter)
{
    string index = "index";

    BlockInst* loop_code = InstBuilder::genBlockInst();

    // Generate local input/output access
    generateLocalInputs(loop_code);
    generateLocalOutputs(loop_code);

    // Generate : int count = min(32, (fullcount - index))
    ValueInst* init1 = InstBuilder::genLoadFunArgsVar(counter);
    ValueInst* init2 = InstBuilder::genSub(init1, InstBuilder::genLoadLoopVar(index));
    list<ValueInst*> min_fun_args;
    min_fun_args.push_back(InstBuilder::genIntNumInst(gVecSize));
    min_fun_args.push_back(init2);
    ValueInst* init3 = InstBuilder::genFunCallInst("min", min_fun_args);
    DeclareVarInst* count_dec = InstBuilder::genDecStackVar("count", InstBuilder::genBasicTyped(Typed::kInt), init3);
    loop_code->pushBackInst(count_dec);

    // Generates the loop DAG
    generateDAGLoop(loop_code, count_dec);

    // Generates the DAG enclosing loop
    DeclareVarInst* loop_dec = InstBuilder::genDecLoopVar(index, InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
    ValueInst* loop_end = InstBuilder::genLessThan(loop_dec->load(), InstBuilder::genLoadFunArgsVar(counter));
    StoreVarInst* loop_increment = loop_dec->store(InstBuilder::genAdd(loop_dec->load(), gVecSize));

    StatementInst* loop = InstBuilder::genForLoopInst(loop_dec, loop_end, loop_increment, loop_code);
    return loop;
}

extern int gVectorLoopVariant;

void VectorCodeContainer::processFIR(void)
{
    // Sort arrays to be at the begining
    fComputeBlockInstructions->fCode.sort(sortArrayDeclarations);

    if (gVectorLoopVariant == 0) {
        fDAGBlock = generateDAGLoopVariant0(fFullCount);
    } else if (gVectorLoopVariant == 1) {
        fDAGBlock = generateDAGLoopVariant1(fFullCount);
    } else {
        fDAGBlock = NULL;
    }
}
