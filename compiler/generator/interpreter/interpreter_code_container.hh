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

#ifndef _INTERPRETER_CODE_CONTAINER_H
#define _INTERPRETER_CODE_CONTAINER_H

#include "code_container.hh"
#include "fir_to_fir.hh"
#include "instructions_compiler.hh"
#include "interpreter_dsp.hh"
#include "interpreter_instructions.hh"
#include "vec_code_container.hh"

using namespace std;

template <class REAL>
class InterpreterCodeContainer : public virtual CodeContainer {
   protected:
    static InterpreterInstVisitor<REAL>* gInterpreterVisitor;

    FIRMetaBlockInstruction* produceMetadata(string& name);

    virtual void generateSR()
    {
        if (!fGeneratedSR) {
            pushDeclare(InstBuilder::genDecStructVar("fSampleRate", InstBuilder::genInt32Typed()));
        }
    }

    // To be implemented in each InterpreterScalarCodeContainer and InterpreterVectorCodeContainer classes
    virtual FBCBlockInstruction<REAL>* generateCompute() = 0;

   public:
    InterpreterCodeContainer(const string& name, int numInputs, int numOutputs);

    virtual ~InterpreterCodeContainer() {}

    void                      produceInternal() {}
    virtual dsp_factory_base* produceFactory();

    CodeContainer* createScalarContainer(const string& name, int sub_container_type);

    static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs);
};

template <class REAL>
class InterpreterScalarCodeContainer : public InterpreterCodeContainer<REAL> {
   protected:
    virtual FBCBlockInstruction<REAL>* generateCompute();

   public:
    InterpreterScalarCodeContainer(const string& name, int numInputs, int numOutputs, int sub_container_type);
    virtual ~InterpreterScalarCodeContainer();
};

template <class REAL>
class InterpreterVectorCodeContainer : public VectorCodeContainer, public InterpreterCodeContainer<REAL> {
   protected:
    virtual FBCBlockInstruction<REAL>* generateCompute();

   public:
    InterpreterVectorCodeContainer(const string& name, int numInputs, int numOutputs)
        : VectorCodeContainer(numInputs, numOutputs), InterpreterCodeContainer<REAL>(name, numInputs, numOutputs)
    {
    }
    virtual ~InterpreterVectorCodeContainer() {}
};

class InterpreterInstructionsCompiler : public virtual InstructionsCompiler {
   public:
    InterpreterInstructionsCompiler(CodeContainer* container) : InstructionsCompiler(container) {}

    StatementInst* generateShiftArray(const string& vname, int delay)
    {
        return InstBuilder::genShiftArrayVarInst(InstBuilder::genNamedAddress(vname, Address::kStruct), delay);
    }
};

#endif
