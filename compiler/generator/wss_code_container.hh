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
#ifndef _WSS_CODE_CONTAINER_H
#define _WSS_CODE_CONTAINER_H

#include "code_container.hh"

struct WSSCodeContainer : public virtual CodeContainer {

    BlockInst* fComputeThreadBlockInstructions;

    WSSCodeContainer(int numInputs, int numOutputs)
        :CodeContainer(numInputs, numOutputs), fComputeThreadBlockInstructions(InstBuilder::genBlockInst())
    {}

    void MoveStackArray2Struct();
    void MoveStack2Struct();

    void generateDAGLoopWSSAux1(lclgraph dag, BlockInst* loop_code, bool master_thread);
    void generateDAGLoopWSSAux2(bool obj);
    void generateDAGLoopWSSAux3();
    StatementInst* generateDAGLoopWSS(lclgraph dag);
};


#endif
