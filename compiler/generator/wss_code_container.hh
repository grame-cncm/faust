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

#ifndef _WSS_CODE_CONTAINER_H
#define _WSS_CODE_CONTAINER_H

/**********************************************************************

		Historique :
		-----------

***********************************************************************/

#include "code_container.hh"

class WSSCodeContainer : public virtual CodeContainer {

private:

    string fObjName;
    BlockInst* fComputeThreadBlockInstructions;

    void MoveStackArray2Struct();
    void MoveStackSlow2Struct();
    void MoveStack2Struct();

    void generateLocalInputs(BlockInst* loop_code);
    void generateLocalOutputs(BlockInst* loop_code);

    StatementInst* generateDAGLoopWSS(lclgraph dag);
    void generateDAGLoopWSSAux1(lclgraph dag, BlockInst* loop_code, bool master_thread);
    void generateDAGLoopWSSAux2(const string& counter);
    void generateDAGLoopWSSAux3();

    void processFIR(void);

public:
    WSSCodeContainer(int numInputs, int numOutputs, string const & objName)
        : fObjName(objName),
        fComputeThreadBlockInstructions(InstBuilder::genBlockInst())
    {
        initializeCodeContainer(numInputs, numOutputs);
        fFullCount = "fullcount";
    }

protected:
    StatementInst* fThreadLoopBlock;
};

#endif
