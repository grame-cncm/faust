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

#ifndef _FIR_INTERPRETER_BYTECODE_H
#define _FIR_INTERPRETER_BYTECODE_H

#include <vector>
#include <string>
#include <math.h>
#include <assert.h>
#include <iostream>

#include "fir_opcode.hh"

// Bytecode definition

typedef long double quad;

template <class T>
struct FIRBlockInstruction;

template <class T>
struct FIRBasicInstruction : public FIRInstruction {

    Opcode fOpcode;
    int fIntValue;
    T fRealValue;
    int fOffset1;
    int fOffset2;
    
    FIRBlockInstruction<T>* fBranch1;
    FIRBlockInstruction<T>* fBranch2;
    
    FIRBasicInstruction(Opcode opcode, 
                        int val_int, T val_real, 
                        int off1, int off2,
                        FIRBlockInstruction<T>* branch1, 
                        FIRBlockInstruction<T>* branch2) 
                        :fOpcode(opcode), fIntValue(val_int), fRealValue(val_real),
                        fOffset1(off1), fOffset2(off2),
                        fBranch1(branch1), fBranch2(branch2)
    {}
    
    FIRBasicInstruction(Opcode opcode, 
                        int val_int, T val_real) 
                        :fOpcode(opcode), fIntValue(val_int), fRealValue(val_real),
                        fOffset1(0), fOffset2(0),
                        fBranch1(0), fBranch2(0)
    {}
    
    FIRBasicInstruction(Opcode opcode, 
                        int val_int, T val_real, int off1, int off2)
                        :fOpcode(opcode), fIntValue(val_int), fRealValue(val_real),
                        fOffset1(off1), fOffset2(off2),
                        fBranch1(0), fBranch2(0)
    {}
    
    FIRBasicInstruction(Opcode opcode) 
                        :fOpcode(opcode), fIntValue(0), fRealValue(0),
                        fOffset1(0), fOffset2(0),
                        fBranch1(0), fBranch2(0)
    {}
    
     
    virtual ~FIRBasicInstruction()
    {
        delete fBranch1;
        delete fBranch2;
    }
    
    int size()
    {
        int branches = std::max(((fBranch1) ? fBranch1->size() : 0), ((fBranch2) ? fBranch2->size() : 0));
        return (branches > 0) ? branches : 1;
    }
    
    void dump()
    {
        std::cout << "opcode = " << fOpcode << " " << gFIRInstructionTable[fOpcode]
        << " int = " << fIntValue
        << " real = " << fRealValue
        << " offset1 = " << fOffset1
        << " offset2 = " << fOffset2
        << std::endl;
        if (fBranch1) fBranch1->dump();
        if (fBranch2) fBranch2->dump();
    }
    
    FIRBasicInstruction<T>* copy()
    {
        return new FIRBasicInstruction<T>(fOpcode, fIntValue, fRealValue, fOffset1, fOffset2, ((fBranch1) ? fBranch1->copy() : 0), ((fBranch2) ? fBranch2->copy() : 0));
    }
    
};

template <class T>
struct FIRUserInterfaceInstruction : public FIRInstruction {

    Opcode fOpcode;
    int fOffset;
    std::string fLabel;
    std::string fKey;
    std::string fValue;
    T fInit;
    T fMin;
    T fMax;
    T fStep;
    
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label, T init, T min, T max, T step)
        :fOpcode(opcode), fOffset(offset), fLabel(label), fInit(init), fMin(min), fMax(max), fStep(step)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode)
        :fOpcode(opcode), fOffset(0), fLabel(""), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode, const std::string& label)
        :fOpcode(opcode), fOffset(0), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label)
        :fOpcode(opcode), fOffset(offset), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
     
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label, T min, T max)
        :fOpcode(opcode), fOffset(offset), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(min), fMax(max), fStep(0)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& key, const std::string& value)
        :fOpcode(opcode), fOffset(offset), fLabel(""), fKey(key), fValue(value), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
    
    virtual ~FIRUserInterfaceInstruction()
    {}
    
    void dump()
    {
        
    }
    
};

#define InstructionIT typename std::vector<FIRBasicInstruction<T>* >::iterator
#define UIInstructionIT typename std::vector<FIRUserInterfaceInstruction<T>* >::iterator

template <class T>
struct FIRUserInterfaceBlockInstruction : public FIRInstruction {

    std::vector<FIRUserInterfaceInstruction<T>*> fInstructions;
     
    virtual ~FIRUserInterfaceBlockInstruction()
    {
        UIInstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            delete(*it);
        }
    }
     
    void push(FIRUserInterfaceInstruction<T>* inst) { fInstructions.push_back(inst); }
    
    void dump()
    {}
    
};

template <class T>
struct FIRBlockInstruction : public FIRInstruction {
    
    std::vector<FIRBasicInstruction<T>*> fInstructions;
    
    virtual ~FIRBlockInstruction()
    {
        InstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            delete (*it);
        }
    }
    
    void push(FIRBasicInstruction<T>* inst) { fInstructions.push_back(inst); }
    
    void dump()
    {
        std::cout << "Block size = " << fInstructions.size() << std::endl;
        InstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            (*it)->dump();
        }
    }
    
    FIRBlockInstruction<T>* copy()
    {
        FIRBlockInstruction<T>* block = new FIRBlockInstruction<T>();
        InstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            block->push((*it)->copy());
        }
        return block;
    }
  
    int size()
    {
        int size = 0;
        InstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            size += (*it)->size();
        }
        return size;
    }
};

#endif
