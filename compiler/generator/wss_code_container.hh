/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef _WSS_CODE_CONTAINER_H
#define _WSS_CODE_CONTAINER_H

#include "code_container.hh"

// The name of the struct variable used to share the 'count' parameter between 'compute' and 'computeThread'
#define fFFullCount "fCount"

class WSSCodeContainer : public virtual CodeContainer {
   protected:
    string fObjName;

    void moveCompute2ComputeThread();

    void generateLocalInputs(BlockInst* loop_code, const string& index_string);
    void generateLocalOutputs(BlockInst* loop_code, const string& index_string);

    BlockInst* generateDAGLoopWSS(lclgraph dag);
    void       generateDAGLoopWSSAux1(lclgraph dag, BlockInst* loop_code, int cur_thread = 0);
    void       generateDAGLoopWSSAux2(lclgraph dag, const string& counter);
    void       generateDAGLoopWSSAux3(int loop_count, const vector<int>& ready_loop);

    DeclareFunInst* generateComputeThread(const string& name, const string& obj, bool ismethod, bool isvirtual);
    DeclareFunInst* generateComputeThreadExternal(const string& name, const string& obj);

    void       processFIR(void);
    BlockInst* flattenFIR(void);

   protected:
    BlockInst* fThreadLoopBlock;
    BlockInst* fComputeThreadBlockInstructions;

   public:
    WSSCodeContainer(int numInputs, int numOutputs, string const& objName)
        : fObjName(objName), fComputeThreadBlockInstructions(InstBuilder::genBlockInst())
    {
        initialize(numInputs, numOutputs);
    }
};

#endif
