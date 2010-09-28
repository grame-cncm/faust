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

#ifndef _DAG_INSTRUCTION_COMPILER_H
#define _DAG_INSTRUCTION_COMPILER_H

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/

#include "instructions_compiler.hh"

class DAGInstructionsCompiler : public InstructionsCompiler {

    protected:
    
        bool needSeparateLoop(Tree sig);
       
    public:
    
        DAGInstructionsCompiler(CodeContainer* container):InstructionsCompiler(container)        
        {}
        virtual ~DAGInstructionsCompiler()
        {}
        
        virtual ValueInst* CS(int variability, Tree sig);
        
        virtual void compileMultiSignal(Tree sig);
        
        virtual ValueInst* generateVariableStore(Tree sig, ValueInst* inst);
        virtual ValueInst* generateCacheCode(Tree sig, ValueInst* inst);
        
        virtual ValueInst* generateInput(int variability, Tree sig, int idx);
        
        // Code generation
        
        virtual ValueInst* generateCode(int variability, Tree sig);
        virtual ValueInst* generateFixDelay(int variability, Tree sig, Tree arg, Tree size);
           
        virtual ValueInst* generateDelayVec(Tree sig, ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd);
        virtual ValueInst* generateDelayLine(ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd, Address::AccessType& var_access);
        
        virtual void generateVectorLoop(Typed::VarType ctype, const string& vecname, ValueInst* exp, Address::AccessType& var_access);
        virtual void generateDlineLoop(Typed::VarType ctype, const string& vecname, int delay, ValueInst* exp, Address::AccessType& var_access);
        
};


#endif
