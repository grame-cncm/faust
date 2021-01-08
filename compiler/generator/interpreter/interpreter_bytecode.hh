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

#ifndef _FIR_INTERPRETER_BYTECODE_H
#define _FIR_INTERPRETER_BYTECODE_H

#include <math.h>
#include <iostream>
#include <string>
#include <vector>

#include "exception.hh"
#include "faust/gui/PathBuilder.h"
#include "fbc_opcode.hh"

static inline std::string quote1(std::string str)
{
    return "\"" + str + "\"";
}

static inline std::string unquote1(const std::string& str)
{
    return (str[0] == '"') ? str.substr(1, str.size() - 2) : str;
}

// Bytecode definition

template <class REAL>
struct FBCBlockInstruction;

template <class REAL>
struct FBCBasicInstruction : public FBCInstruction {
    std::string fName;
    Opcode      fOpcode;
    int         fIntValue;
    REAL        fRealValue;
    int         fOffset1;
    int         fOffset2;

    FBCBlockInstruction<REAL>* fBranch1;
    FBCBlockInstruction<REAL>* fBranch2;

    FBCBasicInstruction(Opcode opcode, const std::string& name, int val_int, REAL val_real, int off1, int off2,
                        FBCBlockInstruction<REAL>* branch1, FBCBlockInstruction<REAL>* branch2)
        : fName(""),
          fOpcode(opcode),
          fIntValue(val_int),
          fRealValue(val_real),
          fOffset1(off1),
          fOffset2(off2),
          fBranch1(branch1),
          fBranch2(branch2)
    {
    }

    FBCBasicInstruction(Opcode opcode, int val_int, REAL val_real)
        : fName(""),
          fOpcode(opcode),
          fIntValue(val_int),
          fRealValue(val_real),
          fOffset1(-1),
          fOffset2(-1),
          fBranch1(nullptr),
          fBranch2(nullptr)
    {
    }

    FBCBasicInstruction(Opcode opcode, int val_int, REAL val_real, int off1, int off2)
        : fName(""),
          fOpcode(opcode),
          fIntValue(val_int),
          fRealValue(val_real),
          fOffset1(off1),
          fOffset2(off2),
          fBranch1(nullptr),
          fBranch2(nullptr)
    {
    }

    FBCBasicInstruction(Opcode opcode, const std::string& name, int val_int, REAL val_real, int off1, int off2)
        : fName(name),
          fOpcode(opcode),
          fIntValue(val_int),
          fRealValue(val_real),
          fOffset1(off1),
          fOffset2(off2),
          fBranch1(nullptr),
          fBranch2(nullptr)
    {
    }

    FBCBasicInstruction(Opcode opcode)
        : fName(""),
          fOpcode(opcode),
          fIntValue(0),
          fRealValue(0),
          fOffset1(-1),
          fOffset2(-1),
          fBranch1(nullptr),
          fBranch2(nullptr)
    {
    }

    FBCBasicInstruction()
        : fName(""),
          fOpcode(FBCInstruction::kNop),
          fIntValue(0),
          fRealValue(0),
          fOffset1(-1),
          fOffset2(-1),
          fBranch1(nullptr),
          fBranch2(nullptr)
    {
    }

    FBCBlockInstruction<REAL>* getBranch1() { return (fOpcode == kCondBranch) ? nullptr : fBranch1; }
    FBCBlockInstruction<REAL>* getBranch2() { return fBranch2; }

    virtual ~FBCBasicInstruction()
    {
        delete getBranch1();
        delete getBranch2();
    }

    int size()
    {
        int branches =
            std::max(((getBranch1()) ? getBranch1()->size() : 0), ((getBranch2()) ? getBranch2()->size() : 0));
        return (branches > 0) ? branches : 1;
    }

    virtual void write(std::ostream* out, bool binary = false, bool small = false, bool recurse = true)
    {
        if (small) {
            *out << "o " << fOpcode << " k "
                 << " i " << fIntValue << " r " << fRealValue << " o " << fOffset1 << " o " << fOffset2 << std::endl;
        } else {
            *out << "opcode " << fOpcode << " " << gFBCInstructionTable[fOpcode] << " int " << fIntValue << " real "
                 << fRealValue << " offset1 " << fOffset1 << " offset2 " << fOffset2;
            if (this->fName != "") {
                *out << " name " << this->fName;
            }
            *out << std::endl;
        }
        // If select/if/loop : write branches
        if (recurse && getBranch1()) {
            getBranch1()->write(out, binary, small, recurse);
        }
        if (recurse && getBranch2()) {
            getBranch2()->write(out, binary, small, recurse);
        }
    }

    virtual FBCBasicInstruction<REAL>* copy()
    {
        return new FBCBasicInstruction<REAL>(fOpcode, fName, fIntValue, fRealValue, fOffset1, fOffset2,
                                            ((getBranch1()) ? getBranch1()->copy() : nullptr),
                                            ((getBranch2()) ? getBranch2()->copy() : nullptr));
    }
};

template <class REAL>
struct FIRBlockStoreRealInstruction : public FBCBasicInstruction<REAL> {
    std::vector<REAL> fNumTable;

    FIRBlockStoreRealInstruction(FBCInstruction::Opcode opcode, int offset1, int offset2,
                                 const std::vector<REAL>& numtable)
    {
        this->fOpcode    = opcode;
        this->fIntValue  = 0;
        this->fRealValue = 0;
        this->fOffset1   = offset1;
        this->fOffset2   = offset2;
        this->fBranch1   = nullptr;
        this->fBranch2   = nullptr;
        this->fNumTable  = numtable;
    }

    virtual FIRBlockStoreRealInstruction<REAL>* copy()
    {
        return new FIRBlockStoreRealInstruction<REAL>(this->fOpcode, this->fOffset1, this->fOffset2, this->fNumTable);
    }

    virtual void write(std::ostream* out, bool binary = false, bool small = false, bool recurse = true)
    {
        if (small) {
            *out << "o " << this->fOpcode << " k "
                 << " o " << this->fOffset1 << " o " << this->fOffset2 << " s " << this->fNumTable.size() << std::endl;
        } else {
            *out << "opcode " << this->fOpcode << " " << gFBCInstructionTable[this->fOpcode] << " offset1 "
                 << this->fOffset1 << " offset2 " << this->fOffset2 << " size " << this->fNumTable.size();
            if (this->fName != "") {
                *out << " name " << this->fName;
            }
            *out << std::endl;
        }
        for (size_t i = 0; i < fNumTable.size(); i++) {
            *out << this->fNumTable[i] << " ";
        }
        *out << std::endl;
    }
};

template <class REAL>
struct FIRBlockStoreIntInstruction : public FBCBasicInstruction<REAL> {
    std::vector<int> fNumTable;

    FIRBlockStoreIntInstruction(FBCInstruction::Opcode opcode, int offset1, int offset2,
                                const std::vector<int>& numtable)
    {
        this->fOpcode    = opcode;
        this->fIntValue  = 0;
        this->fRealValue = 0;
        this->fOffset1   = offset1;
        this->fOffset2   = offset2;
        this->fBranch1   = nullptr;
        this->fBranch2   = nullptr;
        this->fNumTable  = numtable;
    }

    virtual FIRBlockStoreIntInstruction<REAL>* copy()
    {
        return new FIRBlockStoreIntInstruction<REAL>(this->fOpcode, this->fOffset1, this->fOffset2, this->fNumTable);
    }

    virtual void write(std::ostream* out, bool binary = false, bool small = false, bool recurse = true)
    {
        if (small) {
            *out << "o " << this->fOpcode << " k "
                 << " o " << this->fOffset1 << " o " << this->fOffset2 << " s " << this->fNumTable.size() << std::endl;
        } else {
            *out << "opcode " << this->fOpcode << " " << gFBCInstructionTable[this->fOpcode] << " offset1 "
                 << this->fOffset1 << " offset2 " << this->fOffset2 << " size " << this->fNumTable.size();
            if (this->fName != "") {
                *out << " name " << this->fName;
            }
            *out << std::endl;
        }
        for (size_t i = 0; i < fNumTable.size(); i++) {
            *out << this->fNumTable[i] << " ";
        }
        *out << std::endl;
    }
};

template <class REAL>
struct FIRUserInterfaceInstruction : public FBCInstruction {
    Opcode      fOpcode;
    int         fOffset;
    std::string fLabel;
    std::string fKey;
    std::string fValue;
    REAL        fInit;
    REAL        fMin;
    REAL        fMax;
    REAL        fStep;

    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label, const std::string& key,
                                const std::string& value, REAL init, REAL min, REAL max, REAL step)
        : fOpcode(opcode),
          fOffset(offset),
          fLabel(label),
          fKey(key),
          fValue(value),
          fInit(init),
          fMin(min),
          fMax(max),
          fStep(step)
    {
    }

    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label, REAL init, REAL min, REAL max, REAL step)
        : fOpcode(opcode), fOffset(offset), fLabel(label), fInit(init), fMin(min), fMax(max), fStep(step)
    {
    }

    FIRUserInterfaceInstruction(Opcode opcode)
        : fOpcode(opcode), fOffset(-1), fLabel(""), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {
    }

    FIRUserInterfaceInstruction(Opcode opcode, const std::string& label)
        : fOpcode(opcode), fOffset(-1), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {
    }

    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label)
        : fOpcode(opcode), fOffset(offset), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {
    }

    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label, REAL min, REAL max)
        : fOpcode(opcode),
          fOffset(offset),
          fLabel(label),
          fKey(""),
          fValue(""),
          fInit(0),
          fMin(min),
          fMax(max),
          fStep(0)
    {
    }

    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& key, const std::string& value)
        : fOpcode(opcode), fOffset(offset), fLabel(""), fKey(key), fValue(value), fInit(0), fMin(0), fMax(0), fStep(0)
    {
    }

    virtual ~FIRUserInterfaceInstruction() {}

    virtual void write(std::ostream* out, bool binary = false, bool small = false, bool recurse = true)
    {
        if (small) {
            *out << "o " << fOpcode << " k "
                 << " o " << fOffset << " l " << quote1(fLabel) << " k " << quote1(fKey) << " v " << quote1(fValue)
                 << " i " << fInit << " m " << fMin << " m " << fMax << " s " << fStep << std::endl;
        } else {
            *out << "opcode " << fOpcode << " " << gFBCInstructionTable[fOpcode] << " offset " << fOffset << " label "
                 << quote1(fLabel) << " key " << quote1(fKey) << " value " << quote1(fValue) << " init " << fInit
                 << " min " << fMin << " max " << fMax << " step " << fStep << std::endl;
        }
    }
};

struct FIRMetaInstruction : public FBCInstruction {
    std::string fKey;
    std::string fValue;

    FIRMetaInstruction(const std::string& key, const std::string& value) : fKey(key), fValue(value) {}

    virtual ~FIRMetaInstruction() {}

    virtual void write(std::ostream* out, bool binary = false, bool small = false, bool recurse = true)
    {
        if (small) {
            *out << "m"
                 << " k " << quote1(fKey) << " v " << quote1(fValue) << std::endl;
        } else {
            *out << "meta"
                 << " key " << quote1(fKey) << " value " << quote1(fValue) << std::endl;
        }
    }
};

#define InstructionIT typename std::vector<FBCBasicInstruction<REAL>*>::iterator
#define UIInstructionIT typename std::vector<FIRUserInterfaceInstruction<REAL>*>::iterator
#define MetaInstructionIT std::vector<FIRMetaInstruction*>::iterator

template <class REAL>
struct FIRUserInterfaceBlockInstruction : public FBCInstruction {
    std::vector<FIRUserInterfaceInstruction<REAL>*> fInstructions;
    std::map<std::string, int>                      fPathMap;

    FIRUserInterfaceBlockInstruction() {}

    virtual ~FIRUserInterfaceBlockInstruction()
    {
        for (auto& it : fInstructions) {
            delete it;
        }
    }

    void push(FIRUserInterfaceInstruction<REAL>* inst)
    {
        if (inst) fInstructions.push_back(inst);
    }

    virtual void write(std::ostream* out, bool binary = false, bool small = false, bool recurse = true)
    {
        *out << "block_size " << fInstructions.size() << std::endl;
        for (auto& it : fInstructions) {
            it->write(out, binary, small, recurse);
        }
    }

    std::map<std::string, int>& getPathMap()
    {
        // Build the [path, offset] map
        PathBuilder path_builder;

        for (auto& it : fInstructions) {
            switch (it->fOpcode) {
                case FBCInstruction::kOpenVerticalBox:
                    path_builder.pushLabel(it->fLabel);
                    break;

                case FBCInstruction::kOpenHorizontalBox:
                    path_builder.pushLabel(it->fLabel);
                    break;

                case FBCInstruction::kOpenTabBox:
                    path_builder.pushLabel(it->fLabel);
                    break;

                case FBCInstruction::kCloseBox:
                    path_builder.popLabel();
                    break;

                case FBCInstruction::kAddButton:
                case FBCInstruction::kAddCheckButton:
                case FBCInstruction::kAddHorizontalSlider:
                case FBCInstruction::kAddVerticalSlider:
                case FBCInstruction::kAddNumEntry:
                    fPathMap[path_builder.buildPath(it->fLabel)] = it->fOffset;
                    break;

                default:
                    break;
            }
        }

        return fPathMap;
    }

    void freezeDefaultValues(std::map<int, REAL>& real_map)
    {
        for (auto& it : fInstructions) {
            if (it->fOpcode == FBCInstruction::kAddButton
                || it->fOpcode == FBCInstruction::kAddCheckButton
                || it->fOpcode == FBCInstruction::kAddHorizontalSlider
                || it->fOpcode == FBCInstruction::kAddVerticalSlider
                || it->fOpcode == FBCInstruction::kAddNumEntry) {
                real_map[it->fOffset] = it->fInit;
            }
        }
    }

    void unFreezeValue(std::map<int, REAL>& real_map, FBCInstruction::Opcode opcode)
    {
        for (auto& it : fInstructions) {
            if ((it->fOpcode == opcode) && real_map.find(it->fOffset) != real_map.end()) {
                real_map.erase(real_map.find(it->fOffset));
            }
        }
    }

    void unFreezeValue(std::map<int, REAL>& real_map, const std::string& path)
    {
        if (fPathMap.find(path) != fPathMap.end()) {
            real_map.erase(real_map.find(fPathMap[path]));
        }
    }

    void unFreezeValue(std::map<int, REAL>& real_map)
    {
        for (auto& it : fInstructions) {
            if (real_map.find(it->fOffset) != real_map.end()) {
                real_map.erase(real_map.find(it->fOffset));
            }
        }
    }
};

struct FIRMetaBlockInstruction : public FBCInstruction {
    std::vector<FIRMetaInstruction*> fInstructions;

    virtual ~FIRMetaBlockInstruction()
    {
        for (auto& it : fInstructions) {
            delete it;
        }
    }

    void push(FIRMetaInstruction* inst)
    {
        if (inst) fInstructions.push_back(inst);
    }

    virtual void write(std::ostream* out, bool binary = false, bool small = false, bool recurse = true)
    {
        *out << "block_size " << fInstructions.size() << std::endl;
        for (auto& it : fInstructions) {
            it->write(out, binary, small, recurse);
        }
    }
};

template <class REAL>
struct FBCBlockInstruction : public FBCInstruction {
    std::vector<FBCBasicInstruction<REAL>*> fInstructions;

    virtual ~FBCBlockInstruction()
    {
        for (auto& it : fInstructions) {
            delete it;
        }
    }

    // Check block coherency
    void check()
    {
        InstructionIT it = fInstructions.end();
        it--;
        faustassert((*it)->fOpcode == FBCInstruction::kReturn);
    }

    void push(FBCBasicInstruction<REAL>* inst)
    {
        if (inst) fInstructions.push_back(inst);
    }

    void merge(FBCBlockInstruction<REAL>* block)
    {
        for (auto& it : block->fInstructions) {
            if (it->fOpcode != FBCInstruction::kReturn) {  // kReturn must be removed...
                fInstructions.push_back(it);
            }
        }
    }

    virtual void write(std::ostream* out, bool binary = false, bool small = false, bool recurse = true)
    {
        *out << "block_size " << fInstructions.size() << std::endl;
        for (auto& it : fInstructions) {
            it->write(out, binary, small, recurse);
        }
    }

    void stackMove(int& int_index, int& real_index)
    {
        std::cout << "FBCBlockInstruction::stackMove" << std::endl;
        int tmp_int_index  = 0;
        int tmp_real_index = 0;
        for (auto& it : fInstructions) {
            it->stackMove(tmp_int_index, tmp_real_index);
            it->write(&std::cout);
            std::cout << "int_stack_index " << tmp_int_index << " real_stack_index " << tmp_real_index << std::endl;
            faustassert(tmp_int_index >= 0 && tmp_real_index >= 0);
            int_index  = std::max(int_index, tmp_int_index);
            real_index = std::max(real_index, tmp_real_index);
        }
    }

    virtual FBCBlockInstruction<REAL>* copy()
    {
        FBCBlockInstruction<REAL>* block = new FBCBlockInstruction<REAL>();
        for (auto& it : fInstructions) {
            FBCBasicInstruction<REAL>* inst_copy = it->copy();
            if (it->fOpcode == kCondBranch) {  // Special case for loops
                inst_copy->fBranch1 = block;
            }
            block->push(inst_copy);
        }
        return block;
    }

    int size()
    {
        int size = 0;
        for (auto& it : fInstructions) {
            size += it->size();
        }
        return size;
    }

    bool isRealInst() { return isRealType(fInstructions.back()->fOpcode); }
};

#endif
