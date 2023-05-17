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

#ifndef _INTERPRETER_CODE_CONTAINER_H
#define _INTERPRETER_CODE_CONTAINER_H

#include "code_container.hh"
#include "fir_to_fir.hh"
#include "instructions_compiler.hh"
#include "interpreter_dsp.hh"
#include "interpreter_instructions.hh"
#include "vec_code_container.hh"

template <class REAL>
class InterpreterCodeContainer : public virtual CodeContainer {
   protected:
    static InterpreterInstVisitor<REAL>* gInterpreterVisitor;

    FIRMetaBlockInstruction* produceMetadata(std::string& name);

    virtual void generateSR()
    {
        if (!fGeneratedSR) {
            pushDeclare(InstBuilder::genDecStructVar("fSampleRate", InstBuilder::genInt32Typed()));
        }
    }

    // To be implemented in each InterpreterScalarCodeContainer and InterpreterVectorCodeContainer classes
    virtual FBCBlockInstruction<REAL>* generateCompute() = 0;

   public:
    InterpreterCodeContainer(const std::string& name, int numInputs, int numOutputs);

    virtual ~InterpreterCodeContainer() {}

    void                      produceInternal() {}
    virtual dsp_factory_base* produceFactory();

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type);

    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs);
};

template <class REAL>
class InterpreterScalarCodeContainer : public InterpreterCodeContainer<REAL> {
   protected:
    virtual FBCBlockInstruction<REAL>* generateCompute();

   public:
    InterpreterScalarCodeContainer(const std::string& name, int numInputs, int numOutputs, int sub_container_type);
    virtual ~InterpreterScalarCodeContainer();
};

template <class REAL>
class InterpreterVectorCodeContainer : public VectorCodeContainer, public InterpreterCodeContainer<REAL> {
   protected:
    virtual FBCBlockInstruction<REAL>* generateCompute();

   public:
    InterpreterVectorCodeContainer(const std::string& name, int numInputs, int numOutputs)
        : VectorCodeContainer(numInputs, numOutputs), InterpreterCodeContainer<REAL>(name, numInputs, numOutputs)
    {
    }
    virtual ~InterpreterVectorCodeContainer() {}
};

class InterpreterInstructionsCompiler : public virtual InstructionsCompiler {
   public:
    InterpreterInstructionsCompiler(CodeContainer* container) : InstructionsCompiler(container) {}

   protected:
    
    StatementInst* generateShiftArray(const std::string& vname, int delay) override
    {
        return InstBuilder::genShiftArrayVarInst(InstBuilder::genNamedAddress(vname, Address::kStruct), delay);
    }
    
    ValueInst* generateSoundfile(Tree sig, Tree path) override
    {
        std::string varname = gGlobal->getFreshID("fSoundfile");
        std::string SFcache = varname + "ca";

        fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));
        pushDeclare(InstBuilder::genDecStructVar(varname, InstBuilder::genBasicTyped(Typed::kSound_ptr)));
        return InstBuilder::genLoadStructVar(varname);
    }
    
    // Soundfile struct access are fully generated, instead of using intermediate local stack variables as in InstructionsCompiler
    
    // x = part
    ValueInst* generateSoundfileLength(Tree sig, ValueInst* sf, ValueInst* x) override
    {
        LoadVarInst* load = dynamic_cast<LoadVarInst*>(sf);
        faustassert(load);
    
        // In reverse order for the Interp stack
        std::vector<ValueInst*> indices = { x, InstBuilder::genInt32NumInst(Soundfile::kLength) };
        return InstBuilder::genLoadArrayStructVar(load->fAddress->getName(), indices);
    }
    
    // x = part
    ValueInst* generateSoundfileRate(Tree sig, ValueInst* sf, ValueInst* x) override
    {
        LoadVarInst* load = dynamic_cast<LoadVarInst*>(sf);
        faustassert(load);
        
        // In reverse order for the Interp stack
        std::vector<ValueInst*> indices = { x, InstBuilder::genInt32NumInst(Soundfile::kSR) };
        return InstBuilder::genLoadArrayStructVar(load->fAddress->getName(), indices);
    }
    
    // x = chan, y = part, z = ridx
    ValueInst* generateSoundfileBuffer(Tree sig, ValueInst* sf, ValueInst* x, ValueInst* y, ValueInst* z) override
    {
        LoadVarInst* load = dynamic_cast<LoadVarInst*>(sf);
        faustassert(load);
     
        // In reverse order for the Interp stack
        std::vector<ValueInst*> indices1 = { y, InstBuilder::genInt32NumInst(Soundfile::kOffset) };
        ValueInst* offset = InstBuilder::genLoadArrayStructVar(load->fAddress->getName(), indices1);
        // In reverse order for the Interp stack
        std::vector<ValueInst*> indices2 = { InstBuilder::genAdd(offset, z), x, InstBuilder::genInt32NumInst(Soundfile::kBuffers) };
    
        return InstBuilder::genLoadArrayStructVar(load->fAddress->getName(), indices2);
     }

};

#endif
