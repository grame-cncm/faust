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
#include <iostream>

#include "fir_opcode.hh"
#include "exception.hh"

static inline std::string quote1(std::string str)
{
    return "\"" + str + "\"";
}

static inline std::string unquote1(const std::string& str)
{
    return (str[0] == '"') ? str.substr(1, str.size() - 2) : str;
}

// Bytecode definition

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
                        fOffset1(-1), fOffset2(-1),
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
                        fOffset1(-1), fOffset2(-1),
                        fBranch1(0), fBranch2(0)
    {}
    
    FIRBasicInstruction():fOpcode(FIRInstruction::kNop),
                        fIntValue(0), fRealValue(0),
                        fOffset1(-1), fOffset2(-1),
                        fBranch1(0), fBranch2(0)
    {}
    
    FIRBlockInstruction<T>* getBranch1()
    {
        return (fOpcode == kCondBranch) ? 0 : fBranch1;
    }
    
    virtual ~FIRBasicInstruction()
    {
        delete getBranch1();
        delete fBranch2;
    }
    
    int size()
    {
        int branches = std::max(((getBranch1()) ? fBranch1->size() : 0), ((fBranch2) ? fBranch2->size() : 0));
        return (branches > 0) ? branches : 1;
    }
    
    virtual void write(std::ostream* out, bool binary = false, bool small = false)
    {
        if (small) {
            *out << "o " << fOpcode << " k "
            << " i " << fIntValue
            << " r " << fRealValue
            << " o " << fOffset1
            << " o " << fOffset2
            << std::endl;
        } else {
            *out << "opcode " << fOpcode << " "
            << gFIRInstructionTable[fOpcode]
            << " int " << fIntValue
            << " real " << fRealValue
            << " offset1 " << fOffset1
            << " offset2 " << fOffset2
            << std::endl;
        }
        // If select/if/loop : write branches
        if (getBranch1()) { fBranch1->write(out, binary, small); }
        if (fBranch2) { fBranch2->write(out, binary, small); }
    }
    
    virtual FIRBasicInstruction<T>* copy()
    {
        return new FIRBasicInstruction<T>(fOpcode, fIntValue, fRealValue, fOffset1, fOffset2,
                                          ((getBranch1()) ? fBranch1->copy() : 0),
                                          ((fBranch2) ? fBranch2->copy() : 0));
    }
    
};

template <class T>
struct FIRBlockStoreRealInstruction : public FIRBasicInstruction<T> {

    std::vector<T> fNumTable;
    
    FIRBlockStoreRealInstruction(FIRInstruction::Opcode opcode, int offset1, int offset2, const std::vector<T>& numtable)
    {
        this->fOpcode = opcode;
        this->fIntValue = 0;
        this->fRealValue = 0;
        this->fOffset1 = offset1;
        this->fOffset2 = offset2;
        this->fBranch1 = 0;
        this->fBranch2 = 0;
        this->fNumTable = numtable;
    }
    
    virtual FIRBlockStoreRealInstruction<T>* copy()
    {
        return new FIRBlockStoreRealInstruction<T>(this->fOpcode, this->fOffset1 , this->fOffset2, this->fNumTable);
    }
    
    virtual void write(std::ostream* out, bool binary, bool small = false)
    {
        if (small) {
            *out << "o " << this->fOpcode << " k "
            << " o " << this->fOffset1
            << " o " << this->fOffset2
            << " s " << this->fNumTable.size() << std::endl;
        } else {
            *out << "opcode " << this->fOpcode << " "
            << gFIRInstructionTable[this->fOpcode]
            << " offset1 " << this->fOffset1
            << " offset2 " << this->fOffset2
            << " size " << this->fNumTable.size() << std::endl;
        }
        for (unsigned int i = 0; i < fNumTable.size(); i++) {
            *out << this->fNumTable[i] << " ";
        }
        *out << std::endl;
    }
};

template <class T>
struct FIRBlockStoreIntInstruction : public FIRBasicInstruction<T> {
    
    std::vector<int> fNumTable;
    
    FIRBlockStoreIntInstruction(FIRInstruction::Opcode opcode, int offset1, int offset2, const std::vector<int>& numtable)
    {
        this->fOpcode = opcode;
        this->fIntValue = 0;
        this->fRealValue = 0;
        this->fOffset1 = offset1;
        this->fOffset2 = offset2;
        this->fBranch1 = 0;
        this->fBranch2 = 0;
        this->fNumTable = numtable;
    }
    
    virtual FIRBlockStoreIntInstruction<T>* copy()
    {
        return new FIRBlockStoreIntInstruction<T>(this->fOpcode, this->fOffset1 , this->fOffset2, this->fNumTable);
    }
    
    virtual void write(std::ostream* out, bool binary, bool small = false)
    {
        if (small) {
            *out << "o " << this->fOpcode << " k "
            << " o " << this->fOffset1
            << " o " << this->fOffset2
            << " s " << this->fNumTable.size() << std::endl;
        } else {
            *out << "opcode " << this->fOpcode << " "
            << gFIRInstructionTable[this->fOpcode]
            << " offset1 " << this->fOffset1
            << " offset2 " << this->fOffset2
            << " size " << this->fNumTable.size() << std::endl;
        }
        for (unsigned int i = 0; i < fNumTable.size(); i++) {
            *out << this->fNumTable[i] << " ";
        }
        *out << std::endl;
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
    
    FIRUserInterfaceInstruction(Opcode opcode, int offset,
                                const std::string& label,
                                const std::string& key,
                                const std::string& value, T init, T min, T max, T step)
        :fOpcode(opcode), fOffset(offset), fLabel(label), fKey(key),
        fValue(value), fInit(init), fMin(min), fMax(max), fStep(step)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label, T init, T min, T max, T step)
        :fOpcode(opcode), fOffset(offset), fLabel(label), fInit(init), fMin(min), fMax(max), fStep(step)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode)
        :fOpcode(opcode), fOffset(-1), fLabel(""), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode, const std::string& label)
        :fOpcode(opcode), fOffset(-1), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
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
    
    virtual void write(std::ostream* out, bool binary, bool small = false)
    {
        if (small) {
            *out << "o " << fOpcode << " k "
            << " o " << fOffset
            << " l " << quote1(fLabel)
            << " k " << quote1(fKey)
            << " v " << quote1(fValue)
            << " i " << fInit
            << " m " << fMin
            << " m " << fMax
            << " s " << fStep << std::endl;
        } else {
            *out << "opcode " << fOpcode << " " << gFIRInstructionTable[fOpcode]
            << " offset " << fOffset
            << " label " << quote1(fLabel)
            << " key " << quote1(fKey)
            << " value " << quote1(fValue)
            << " init " << fInit
            << " min " << fMin
            << " max " << fMax
            << " step " << fStep << std::endl;
        }
    }
    
};

struct FIRMetaInstruction : public FIRInstruction {
    
    std::string fKey;
    std::string fValue;
 
    FIRMetaInstruction(const std::string& key, const std::string& value)
        :fKey(key), fValue(value)
    {}
    
    virtual ~FIRMetaInstruction()
    {}
    
    virtual void write(std::ostream* out, bool binary, bool small = false)
    {
        if (small) {
            *out << "m"
            << " k " << quote1(fKey)
            << " v " << quote1(fValue) << std::endl;
        } else {
            *out << "meta"
            << " key " << quote1(fKey)
            << " value " << quote1(fValue) << std::endl;

        }
    }
};

#define InstructionIT typename std::vector<FIRBasicInstruction<T>* >::iterator
#define UIInstructionIT typename std::vector<FIRUserInterfaceInstruction<T>* >::iterator
#define MetaInstructionIT std::vector<FIRMetaInstruction* >::iterator

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
    
    virtual void write(std::ostream* out, bool binary, bool small = false)
    {
        *out << "block_size " << fInstructions.size() << std::endl;
        UIInstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            (*it)->write(out, binary, small);
        }
    }
    
    void freezeDefaultValues(std::map<int, T>& real_map)
    {
        UIInstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            if ((*it)->fOpcode == FIRInstruction::kAddButton
                || (*it)->fOpcode == FIRInstruction::kAddCheckButton
                || (*it)->fOpcode == FIRInstruction::kAddHorizontalSlider
                || (*it)->fOpcode == FIRInstruction::kAddVerticalSlider
                || (*it)->fOpcode == FIRInstruction::kAddNumEntry) {
                real_map[(*it)->fOffset] = (*it)->fInit;
                std::cout << "getDefaultValues offset " << (*it)->fOffset << " value " << (*it)->fInit << std::endl;
            }
        }
    }
    
    void unFreezeDefaultValues(std::map<int, T>& real_map, FIRInstruction::Opcode opcode)
    {
        UIInstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            if (((*it)->fOpcode == opcode) && real_map.find((*it)->fOffset) != real_map.end()) {
                real_map.erase(real_map.find((*it)->fOffset));
            }
        }
    }
    
    void unFreezeDefaultValues(std::map<int, T>& real_map)
    {
        UIInstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            if (real_map.find((*it)->fOffset) != real_map.end()) {
                real_map.erase(real_map.find((*it)->fOffset));
            }
        }
    }
    
};

struct FIRMetaBlockInstruction : public FIRInstruction {
    
    std::vector<FIRMetaInstruction*> fInstructions;
    
    virtual ~FIRMetaBlockInstruction()
    {
        MetaInstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            delete(*it);
        }
    }
    
    void push(FIRMetaInstruction* inst) { fInstructions.push_back(inst); }
    
    virtual void write(std::ostream* out, bool binary, bool small = false)
    {
        *out << "block_size " << fInstructions.size() << std::endl;
        MetaInstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            (*it)->write(out, binary, small);
        }
    }
    
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
    
    void merge(FIRBlockInstruction<T>* block)
    {
        InstructionIT it;
        for (it = block->fInstructions.begin(); it != block->fInstructions.end(); it++) {
            if ((*it)->fOpcode != FIRInstruction::kReturn) { // kReturn must be removed...
                fInstructions.push_back(*it);
            }
        }
    }
    
    virtual void write(std::ostream* out, bool binary, bool small = false)
    {
        *out << "block_size " << fInstructions.size() << std::endl;
        InstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            (*it)->write(out, binary, small);
        }
    }
    
    void stackMove(int& int_index, int& real_index)
    {
        std::cout << "FIRBlockInstruction::stackMove" << std::endl;
        InstructionIT it;
        int tmp_int_index = 0;
        int tmp_real_index = 0;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            (*it)->stackMove(tmp_int_index, tmp_real_index);
            (*it)->write(&std::cout);
            std::cout << "int_stack_index " << tmp_int_index << " real_stack_index " << tmp_real_index << std::endl;
            faustassert(tmp_int_index >= 0 && tmp_real_index >= 0);
            int_index = std::max(int_index, tmp_int_index);
            real_index = std::max(real_index, tmp_real_index);
        }
    }
    
    virtual FIRBlockInstruction<T>* copy()
    {
        FIRBlockInstruction<T>* block = new FIRBlockInstruction<T>();
        InstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            FIRBasicInstruction<T>* inst_copy = (*it)->copy();
            if ((*it)->fOpcode == kCondBranch) {   // Special case for loops
                inst_copy->fBranch1 = block;
            }
            block->push(inst_copy);
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
    
    bool isRealInst() { return isRealType(fInstructions.back()->fOpcode); }
};

#endif
