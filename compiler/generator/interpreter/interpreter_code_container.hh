/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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

#ifndef _INTERPRETER_CODE_CONTAINER_H
#define _INTERPRETER_CODE_CONTAINER_H

#include "code_container.hh"
#include "interpreter_dsp_aux.hh"
#include "interpreter_instructions.hh"
#include "instructions_compiler.hh"
#include "fir_to_fir.hh"

using namespace std;           

template <class T>
class InterpreterCodeContainer : public virtual CodeContainer {

    protected:

        static InterpreterInstVisitor<T>* gInterpreterVisitor;
    
        FIRMetaBlockInstruction* produceMetadata(string& name);
    
        virtual void generateSR()
        {
            if (!fGeneratedSR) {
                pushDeclare(InstBuilder::genDecStructVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt32)));
            }
        }

    public:

        InterpreterCodeContainer(const string& name, int numInputs, int numOutputs);
    
        virtual ~InterpreterCodeContainer()
        {}

        void produceInternal();
        virtual dsp_factory_base* produceFactory();
    
        CodeContainer* createScalarContainer(const string& name, int sub_container_type);

        static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs);
    
};

template <class T>
class InterpreterScalarCodeContainer : public InterpreterCodeContainer<T> {

    protected:

    public:

        InterpreterScalarCodeContainer(const string& name, int numInputs, int numOutputs, int sub_container_type);
        virtual ~InterpreterScalarCodeContainer();

        void generateCompute(int tab);

};

class InterpreterInstructionsCompiler : public virtual InstructionsCompiler {

    public:
    
        InterpreterInstructionsCompiler(CodeContainer* container):InstructionsCompiler(container)
        {}
    
        StatementInst* generateShiftArray(const string& vname, int delay)
        {
            return InstBuilder::genShiftArrayVarInst(InstBuilder::genNamedAddress(vname, Address::kStruct), delay);
        }
};

#endif
