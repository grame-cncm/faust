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

#ifndef _MR_DAG_INSTRUCTION_COMPILER_H
#define _MR_DAG_INSTRUCTION_COMPILER_H

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/

#include "dag_instructions_compiler.hh"

class MultiRateDAGInstructionsCompiler : public DAGInstructionsCompiler {

public:
    MultiRateDAGInstructionsCompiler(CodeContainer* container):
        DAGInstructionsCompiler(container)
    {}

private:
    // private helper functions
    bool needSeparateLoop(Tree sig);

   // reimplemented code generation methods
    virtual ValueInst* generateCode(Tree sig);
    virtual ValueInst* generateInput(Tree sig, int idx);
    virtual void compileMultiSignal(Tree L);

    virtual ValueInst* generateVectorize(Tree sig, Tree exp, int n);
    virtual ValueInst* generateSerialize(Tree sig, Tree exp);
    virtual ValueInst* generateVectorAt(Tree sig, Tree exp, Tree index);
    virtual ValueInst* generateConcat(Tree sig, Tree exp1, Tree exp2);
};


#endif
