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

#ifndef _WSS_CODE_CONTAINER_H
#define _WSS_CODE_CONTAINER_H

#include "code_container.hh"

// The name of the struct variable used to share the 'count' parameter between 'compute' and 'computeThread'
#define fFFullCount "fCount"

/*
 Base class for -sch code generation (Work Stealing Scheduler).
 */
class WSSCodeContainer : public virtual CodeContainer {
   protected:
    std::string fObjName;

    void moveCompute2ComputeThread();

    void generateLocalInputs(BlockInst* loop_code, const std::string& index) override;
    void generateLocalOutputs(BlockInst* loop_code, const std::string& index) override;

    BlockInst* generateDAGLoopWSS(lclgraph dag);
    void       generateDAGLoopWSSAux1(lclgraph dag, BlockInst* loop_code, int cur_thread = 0);
    void       generateDAGLoopWSSAux2(lclgraph dag, const std::string& counter);
    void       generateDAGLoopWSSAux3(int loop_count, const std::vector<int>& ready_loop);

    DeclareFunInst* generateComputeThread(const std::string& name, const std::string& obj, bool ismethod, bool isvirtual);
    DeclareFunInst* generateComputeThreadExternal(const std::string& name, const std::string& obj);

    void       processFIR(void) override;
    BlockInst* flattenFIR(void) override;

   protected:
    BlockInst* fThreadLoopBlock;
    BlockInst* fComputeThreadBlockInstructions;
    
    StatementInst* pushComputeThread(StatementInst* inst)
    {
        fComputeThreadBlockInstructions->pushBackInst(inst);
        return inst;
    }

   public:
    WSSCodeContainer(int numInputs, int numOutputs, const std::string& objName)
        : fObjName(objName), fComputeThreadBlockInstructions(InstBuilder::genBlockInst())
    {
        initialize(numInputs, numOutputs);
    }
};

#endif
