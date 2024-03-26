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

#ifndef _FBC_INTERPRETER_H
#define _FBC_INTERPRETER_H

#include <string.h>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <functional>

#include "exception.hh"
#include "fbc_executor.hh"
#include "interpreter_bytecode.hh"
#include "dsp_aux.hh"

//#define INTERP_MIR_BUILD 1
//#define INTERP_LLVM_BUILD 1
//#define INTERP_TEMPLATE_BUILD 1

/*
 Interpreter using 'computed goto' technique: https://eli.thegreenplace.net/2012/07/12/computed-goto-for-efficient-dispatch-tables

 Trace mode: only check 'non-optimized' interpreter operations, since the code is not optimized in this case.

 1 : collect FP_SUBNORMAL only
 2 : collect FP_SUBNORMAL, FP_INFINITE and FP_NAN
 3 : collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW and DIV_BY_ZERO
 4 : collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, fails at first FP_INFINITE or FP_NAN
 5 : collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, continue after FP_INFINITE or FP_NAN
*/

#define INTEGER_OVERFLOW    -1
#define DIV_BY_ZERO_REAL    -2
#define DIV_BY_ZERO_INT     -3
#define CAST_INT_OVERFLOW   -4
#define NEGATIVE_BITSHIFT   -5
#define DUMMY_REAL          0.12233344445555
#define DUMMY_INT           1223334444

//#define assertInterp(exp) faustassert(exp)
#define assertInterp(exp)

template <class REAL, int TRACE>
struct interpreter_dsp_factory_aux;

// FBC interpreter
template <class REAL, int TRACE>
class FBCInterpreter : public FBCExecutor<REAL> {
   protected:

    typedef std::function<void(double)> ReflectFunction;
    typedef std::function<double()> ModifyFunction;

    struct ZoneParam {
        
        FAUSTFLOAT fZone;
        ReflectFunction fReflect;
        ModifyFunction fModify;
        
    #if defined(TARGET_OS_IPHONE) || defined(WIN32)
        ZoneParam(ReflectFunction reflect = nullptr, ModifyFunction modify = nullptr)
        :fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { if (fReflect) fReflect(fZone); }
        void modifyZone() { if (fModify) fZone = fModify(); }
    #else
        ZoneParam(ReflectFunction reflect = [](REAL value) {}, ModifyFunction modify = []() { return REAL(-1); })
        :fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { fReflect(fZone); }
        void modifyZone() { fZone = fModify(); }
    #endif
        
        void setReflectZoneFun(ReflectFunction reflect) { fReflect = reflect; }
        void setModifyZoneFun(ModifyFunction modify) { fModify = modify; }
        
    };
    
    typedef std::map<int, ZoneParam*> controlMap;
    
    controlMap fPathInputTable;     // [path, ZoneParam]
    controlMap fPathOutputTable;    // [path, ZoneParam]
    
    interpreter_dsp_factory_aux<REAL, TRACE>* fFactory;

    int*  fIntHeap;
    REAL* fRealHeap;
   
    REAL** fInputs;
    REAL** fOutputs;

    std::map<int, int64_t> fRealStats;
    
    /*
     Keeps the latest TRACE_STACK_SIZE executed instructions, to be displayed when an error occurs.
     */
    struct InterpreterTrace {
#define TRACE_STACK_SIZE 16

        std::vector<std::string> fExecTrace;
        int                      fWriteIndex;
        std::stringstream        fMessage;
   
        InterpreterTrace()
        {
            for (int i = 0; i < TRACE_STACK_SIZE; i++) {
                fExecTrace.push_back("");
            }
            fWriteIndex = 0;
        }

        void push(const std::string& message)
        {
            fExecTrace[fWriteIndex] = message;
            fWriteIndex             = (fWriteIndex + 1) % TRACE_STACK_SIZE;
        }

        void write(std::ostream* out)
        {
            for (int i = fWriteIndex - 1; i >= 0; i--) {
                *out << fExecTrace[i];
            }
            for (int i = int(fExecTrace.size()) - 1; i >= fWriteIndex; i--) {
                *out << fExecTrace[i];
            }
        }

        void traceInstruction(InstructionIT it)
        {
            (*it)->write(&fMessage, false, false, false);  // Last param = false means no recursion in branches
            push(fMessage.str());
            fMessage.str("");
        }
        
        void traceInstruction(InstructionIT it, int int_value, REAL real_value)
        {
            (*it)->write(&fMessage, false, false, false);  // Last param = false means no recursion in branches
            push(fMessage.str());
            push("Stack [Int: " + std::to_string(int_value) + "] [REAL: " + std::to_string(real_value) + "]\n");
            fMessage.str("");
        }
    };

    InterpreterTrace fTraceContext;

    inline void traceInstruction(InstructionIT it)
    {
        fTraceContext.traceInstruction(it);
    }
    
    inline void traceInstruction(InstructionIT it, int int_value, REAL real_value)
    {
        fTraceContext.traceInstruction(it, int_value, real_value);
    }

    void printStats()
    {
        if (TRACE > 0 && TRACE < 6) {
            std::cout << "-------------------------------" << std::endl;
            std::cout << "Interpreter statistics" << std::endl;
            if (TRACE >= 1) {
                std::cout << "FP_SUBNORMAL: " << fRealStats[FP_SUBNORMAL] << std::endl;
            }
            if (TRACE >= 2) {
                std::cout << "FP_INFINITE: " << fRealStats[FP_INFINITE] << std::endl;
                std::cout << "FP_NAN: " << fRealStats[FP_NAN] << std::endl;
            }
            if (TRACE >= 3) {
                std::cout << "INTEGER_OVERFLOW: " << fRealStats[INTEGER_OVERFLOW] << std::endl;
                std::cout << "DIV_BY_ZERO_REAL: " << fRealStats[DIV_BY_ZERO_REAL] << std::endl;
                std::cout << "DIV_BY_ZERO_INT: " << fRealStats[DIV_BY_ZERO_INT] << std::endl;
                std::cout << "CAST_INT_OVERFLOW: " << fRealStats[CAST_INT_OVERFLOW] << std::endl;
                std::cout << "NEGATIVE_BITSHIFT: " << fRealStats[NEGATIVE_BITSHIFT] << std::endl;
            }
            std::cout << "-------------------------------" << std::endl;
        }
    }

    inline void warningOverflow(InstructionIT it, const std::string& op)
    {
        if (TRACE >= 6) return;

        if (TRACE >= 3) {
            fRealStats[INTEGER_OVERFLOW]++;
        }

        if (TRACE >= 5) {
            std::cout << "-------- Interpreter 'Overflow' [" << op << "] warning trace start --------" << std::endl;
            traceInstruction(it);
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter 'Overflow' warning trace end --------\n\n";
        }
    }
    
    inline int warningBitshift(InstructionIT it, int val)
    {
        if (val < 0) {
            
            if (TRACE >= 3) {
                fRealStats[NEGATIVE_BITSHIFT]++;
            }
            
            if (TRACE >= 4) {
                std::cout << "-------- Interpreter 'Bitshift' warning trace start --------" << std::endl;
                traceInstruction(it);
                fTraceContext.write(&std::cout);
                std::cout << "-------- Interpreter 'Bitshift' warning trace end --------\n\n";
            }
        }
        return val;
    }
    
    inline REAL checkCastIntOverflow(InstructionIT it, REAL val)
    {
        if (val > std::numeric_limits<int>::max() || val < std::numeric_limits<int>::min()) {
            
            if (TRACE >= 3) {
                fRealStats[CAST_INT_OVERFLOW]++;
            }
             
            if (TRACE >= 4) {
                std::cout << "-------- Interpreter 'CastIntOverflow' trace start --------" << std::endl;
                std::cout << "val = " << val << std::endl;
                traceInstruction(it);
                fTraceContext.write(&std::cout);
                std::cout << "-------- Interpreter 'CastIntOverflow' trace end --------\n\n";
                // Fails at first error...
                if (TRACE == 4) {
                    throw faustexception("Interpreter exit\n");
                }
            }
        }
    
        return val;
    }
 
    inline void checkDivZero(InstructionIT it, REAL val)
    {
        if (TRACE >= 6) return;

        if ((TRACE >= 3) && (val == REAL(0))) {
            fRealStats[DIV_BY_ZERO_REAL]++;
        }

        if ((TRACE >= 4) && (val == REAL(0))) {
            std::cout << "-------- Interpreter 'REAL div by zero' trace start --------" << std::endl;
            traceInstruction(it);
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter 'REAL div by zero' trace end ----------\n\n";
        }
    }
    
    inline void checkDivZero(InstructionIT it, int val)
    {
        if (TRACE >= 6) return;
        
        if ((TRACE >= 3) && (val == 0)) {
            fRealStats[DIV_BY_ZERO_INT]++;
        }
        
        if ((TRACE >= 4) && (val == 0)) {
            std::cout << "-------- Interpreter 'Int div by zero' trace start --------" << std::endl;
            traceInstruction(it);
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter 'Int div by zero' trace end ----------\n\n";
        }
    }

    inline REAL checkRealAux(InstructionIT it, REAL val)
    {
        if (TRACE >= 6) return val;

        if (TRACE >= 1) {
            if (std::fpclassify(val) == FP_SUBNORMAL) {
                fRealStats[FP_SUBNORMAL]++;
            }
        }

        if (TRACE >= 2) {
            if (std::isnan(val)) {
                fRealStats[FP_NAN]++;
            } else if (std::isinf(val)) {
                fRealStats[FP_INFINITE]++;
            }
        }

        if (TRACE >= 4) {
            if (std::isnan(val)) {
                std::cout << "-------- Interpreter 'NaN' trace start --------" << std::endl;
                traceInstruction(it);
                fTraceContext.write(&std::cout);
                std::cout << "-------- Interpreter 'NaN' trace end --------\n\n";
                // Fails at first error...
                if (TRACE == 4) {
                    throw faustexception("Interpreter exit\n");
                }
            } else if (std::isinf(val)) {
                std::cout << "-------- Interpreter 'Inf' trace start --------" << std::endl;
                traceInstruction(it);
                fTraceContext.write(&std::cout);
                std::cout << "-------- Interpreter 'Inf' trace end --------\n\n";
                // Fails at first error...
                if (TRACE == 4) {
                    throw faustexception("Interpreter exit\n");
                }
            }
        }
        return val;
    }

    inline int assertAudioBuffer(InstructionIT it, int index)
    {
        if (TRACE >= 6) return index;

        if (TRACE >= 4 && ((index < 0) || (index >= fIntHeap[fFactory->fCountOffset]))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            std::cout << "assertAudioBuffer : count = " << fIntHeap[fFactory->fCountOffset];
            std::cout << " index = " << index << std::endl;
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter crash trace end --------\n\n";
            if (TRACE == 4) {
                throw faustexception("Interpreter exit\n");
            }
        }
        return index;
    }

    inline int assertStoreIntHeap(InstructionIT it, int index, int size = -1)
    {
        int index_in_array = index - (*it)->fOffset1;
        if (TRACE >= 4 &&
            ((index < 0)
             || (index >= fFactory->fIntHeapSize)
             || (size > 0 && ((index_in_array < 0) || (index_in_array >= size))))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            if (size > 0) {
                std::cout << "assertStoreIntHeap array: fIntHeapSize = ";
                std::cout << fFactory->fIntHeapSize << " index = " << index_in_array;
                std::cout << " size = " << size;
                std::cout << " name = " << (*it)->fName << std::endl;
            } else {
                std::cout << "assertStoreIntHeap scalar: fIntHeapSize = ";
                std::cout << fFactory->fIntHeapSize << " index = " << index;
                std::cout << " name = " << (*it)->fName << std::endl;
            }
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter crash trace end --------\n\n";
            throw faustexception("Interpreter exit\n");
        }
        return index;
    }

    inline int assertStoreRealHeap(InstructionIT it, int index, int size = -1)
    {
        int index_in_array = index - (*it)->fOffset1;
        if (TRACE >= 4 &&
            ((index < 0)
             || (index >= fFactory->fRealHeapSize)
             || (size > 0 && ((index_in_array < 0) || (index_in_array >= size))))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            if (size > 0) {
                std::cout << "assertStoreRealHeap array: fRealHeapSize = ";
                std::cout << fFactory->fRealHeapSize << " index = " << index_in_array;
                std::cout << " size = " << size;
                std::cout << " name = " << (*it)->fName << std::endl;
            } else {
                std::cout << "assertStoreRealHeap scalar: fRealHeapSize = ";
                std::cout << fFactory->fRealHeapSize << " index = " << index;
                std::cout << " name = " << (*it)->fName << std::endl;
            }
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter crash trace end --------\n\n";
            throw faustexception("Interpreter exit\n");
        }
        return index;
    }

    inline int assertLoadIntHeap(InstructionIT it, int index, int size = -1)
    {
        int index_in_array = index - (*it)->fOffset1;
        if ((TRACE >= 4) &&
            ((index < 0)
             || (index >= fFactory->fIntHeapSize)
             || (size > 0 && ((index_in_array < 0) || (index_in_array >= size)))
             || (fIntHeap[index] == DUMMY_INT))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            if (size > 0) {
                std::cout << "assertLoadIntHeap array: fIntHeapSize = ";
                std::cout << fFactory->fIntHeapSize << " index = " << index_in_array;
                std::cout << " size = " << size;
                if (index >= 0) std::cout << " value = " << fIntHeap[index];
                std::cout << " name = " << (*it)->fName << std::endl;
            } else {
                std::cout << "assertLoadIntHeap scalar: fIntHeapSize = ";
                std::cout << fFactory->fIntHeapSize << " index = " << index;
                std::cout << " name = " << (*it)->fName << std::endl;
            }
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter crash trace end --------\n\n";
            throw faustexception("Interpreter exit\n");
        }
        return index;
    }

    inline int assertLoadRealHeap(InstructionIT it, int index, int size = -1)
    {
        int index_in_array = index - (*it)->fOffset1;
        if ((TRACE >= 4) &&
            ((index < 0)
             || (index >= fFactory->fRealHeapSize)
             || (size > 0 && ((index_in_array < 0) || (index_in_array >= size)))
             || (fRealHeap[index] == REAL(DUMMY_REAL)))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            if (size > 0) {
                std::cout << "assertLoadRealHeap array: fRealHeapSize = ";
                std::cout << fFactory->fRealHeapSize << " index = " << index_in_array;
                std::cout << " size = " << size;
                if (index >= 0) std::cout << " value = " << fRealHeap[index];
                std::cout << " name = " << (*it)->fName << std::endl;
            } else {
                std::cout << "assertLoadRealHeap scalar: fRealHeapSize = ";
                std::cout << fFactory->fRealHeapSize << " index = " << index;
                std::cout << " name = " << (*it)->fName << std::endl;
            }
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter crash trace end --------\n\n";
            throw faustexception("Interpreter exit\n");
        }
        return index;
    }
    
    inline REAL checkReal(InstructionIT it, REAL val) { return (TRACE > 0) ? checkRealAux(it, val) : val; }

    void updateInputControls()
    {
        for (const auto& i : fPathInputTable) {
            i.second->reflectZone();
        }
        
    }
    void updateOutputControls()
    {
        for (const auto& i : fPathOutputTable) {
            i.second->modifyZone();
        }
    }

#define pushInt(val) (int_stack[int_stack_index++] = val)
#define popInt() (int_stack[--int_stack_index])

#define pushReal(it, val) (real_stack[real_stack_index++] = checkReal(it, val))
#define popReal(it) checkReal(it, real_stack[--real_stack_index])

#define pushAddr_(addr) (address_stack[addr_stack_index++] = addr)
#define popAddr_() (address_stack[--addr_stack_index])
    
    ZoneParam* getZoneParam(controlMap& map, ZoneParam* cur_param, int offset)
    {
        if (cur_param) {
            map[offset] = cur_param;
            return cur_param;
        } else if (map.find(offset) == map.end()) {
            ZoneParam* param = new ZoneParam();
            map[offset] = param;
            return param;
        } else {
             return map[offset];
        }
    }
    
    ZoneParam* getZoneParam(int offset)
    {
        if (fPathInputTable.find(offset) != fPathInputTable.end()) {
            return fPathInputTable[offset];
        } else if (fPathOutputTable.find(offset) != fPathOutputTable.end()) {
            return fPathOutputTable[offset];
        } else {
            return new ZoneParam();
        }
    }

    void executeBuildUserInterface(FIRUserInterfaceBlockInstruction<REAL>* block, UIInterface* glue)
    {
        // UI may have to be adapted if REAL and FAUSTFLOAT size do not match
        bool need_proxy = sizeof(REAL) != glue->sizeOfFAUSTFLOAT();
        ZoneParam* cur_param = nullptr;
        
        for (const auto& it : block->fInstructions) {
            // it->write(&std::cout);

            switch (it->fOpcode) {
                case FBCInstruction::kOpenVerticalBox:
                    glue->openVerticalBox(it->fLabel.c_str());
                    break;

                case FBCInstruction::kOpenHorizontalBox:
                    glue->openHorizontalBox(it->fLabel.c_str());
                    break;

                case FBCInstruction::kOpenTabBox:
                    glue->openTabBox(it->fLabel.c_str());
                    break;

                case FBCInstruction::kCloseBox:
                    glue->closeBox();
                    break;

                case FBCInstruction::kAddButton:
                    if (need_proxy) {
                        ZoneParam* param = getZoneParam(fPathInputTable, cur_param, it->fOffset);
                        param->setReflectZoneFun([=](REAL value) { fRealHeap[it->fOffset] = value; });
                        glue->addButton(it->fLabel.c_str(), &param->fZone);
                        cur_param = nullptr;
                    } else {
                        glue->addButton(it->fLabel.c_str(), &fRealHeap[it->fOffset]);
                    }
                    break;

                case FBCInstruction::kAddCheckButton:
                    if (need_proxy) {
                        ZoneParam* param = getZoneParam(fPathInputTable, cur_param, it->fOffset);
                        param->setReflectZoneFun([=](REAL value) { fRealHeap[it->fOffset] = value; });
                        glue->addCheckButton(it->fLabel.c_str(), &param->fZone);
                        cur_param = nullptr;
                    } else {
                        glue->addCheckButton(it->fLabel.c_str(), &fRealHeap[it->fOffset]);
                    }
                    break;

                case FBCInstruction::kAddHorizontalSlider:
                    if (need_proxy) {
                        ZoneParam* param = getZoneParam(fPathInputTable, cur_param, it->fOffset);
                        param->setReflectZoneFun([=](REAL value) { fRealHeap[it->fOffset] = value; });
                        glue->addHorizontalSlider(it->fLabel.c_str(), &param->fZone,
                                                  it->fInit, it->fMin,it->fMax, it->fStep);
                        cur_param = nullptr;
                    } else {
                        glue->addHorizontalSlider(it->fLabel.c_str(), &fRealHeap[it->fOffset],
                                                  it->fInit, it->fMin,it->fMax, it->fStep);
                    }
                    break;

                case FBCInstruction::kAddVerticalSlider:
                    if (need_proxy) {
                        ZoneParam* param = getZoneParam(fPathInputTable, cur_param, it->fOffset);
                        param->setReflectZoneFun([=](REAL value) { fRealHeap[it->fOffset] = value; });
                        glue->addVerticalSlider(it->fLabel.c_str(), &param->fZone,
                                                  it->fInit, it->fMin,it->fMax, it->fStep);
                        cur_param = nullptr;
                    } else {
                        glue->addVerticalSlider(it->fLabel.c_str(), &fRealHeap[it->fOffset],
                                                it->fInit, it->fMin, it->fMax, it->fStep);
                    }
                    break;

                case FBCInstruction::kAddNumEntry:
                    if (need_proxy) {
                        ZoneParam* param = getZoneParam(fPathInputTable, cur_param, it->fOffset);
                        param->setReflectZoneFun([=](REAL value) { fRealHeap[it->fOffset] = value; });
                        glue->addNumEntry(it->fLabel.c_str(), &param->fZone,
                                          it->fInit, it->fMin,it->fMax, it->fStep);
                        cur_param = nullptr;
                    } else {
                        glue->addNumEntry(it->fLabel.c_str(), &fRealHeap[it->fOffset],
                                          it->fInit, it->fMin, it->fMax, it->fStep);
                    }
                    break;

                case FBCInstruction::kAddSoundfile:
                    // fKey use for label, fValue used for URL, fLabel for SF field name
                    // The fSoundTable entry is created with it->fLabel
                    glue->addSoundfile(it->fKey.c_str(), it->fValue.c_str(), &this->fSoundTable[it->fLabel]);
                    break;

                case FBCInstruction::kAddHorizontalBargraph:
                    if (need_proxy) {
                        ZoneParam* param = getZoneParam(fPathOutputTable, cur_param, it->fOffset);
                        param->setModifyZoneFun([=]() { return fRealHeap[it->fOffset]; });
                        glue->addHorizontalBargraph(it->fLabel.c_str(), &param->fZone, it->fMin, it->fMax);
                        cur_param = nullptr;
                    } else {
                        glue->addHorizontalBargraph(it->fLabel.c_str(), &fRealHeap[it->fOffset], it->fMin, it->fMax);
                    }
                    break;

                case FBCInstruction::kAddVerticalBargraph:
                    if (need_proxy) {
                        ZoneParam* param = getZoneParam(fPathOutputTable, cur_param, it->fOffset);
                        param->setModifyZoneFun([=]() { return fRealHeap[it->fOffset]; });
                        glue->addVerticalBargraph(it->fLabel.c_str(), &param->fZone, it->fMin, it->fMax);
                        cur_param = nullptr;
                    } else {
                        glue->addVerticalBargraph(it->fLabel.c_str(), &fRealHeap[it->fOffset], it->fMin, it->fMax);
                    }
                    break;

                case FBCInstruction::kDeclare:
                    // Special case for "0" zone
                    if (it->fOffset == -1) {
                        glue->declare(static_cast<REAL*>(nullptr), it->fKey.c_str(), it->fValue.c_str());
                    } else {
                        if (need_proxy) {
                            if (!cur_param) cur_param = getZoneParam(it->fOffset);
                            glue->declare(&cur_param->fZone, it->fKey.c_str(), it->fValue.c_str());
                        } else {
                            glue->declare(&fRealHeap[it->fOffset], it->fKey.c_str(), it->fValue.c_str());
                        }
                    }
                    break;

                default:
                    break;
            }
        }
    }
   
#if defined(_WIN32)
    
    // Fake versions for now
    bool __builtin_sadd_overflow(int v1, int v2, int* res) { return false; }
    bool __builtin_ssub_overflow(int v1, int v2, int* res) { return false; }
    bool __builtin_smul_overflow(int v1, int v2, int* res) { return false; }
    
    void executeBlock(FBCBlockInstruction<REAL>* block)
    {
        int real_stack_index  = 0;
        int int_stack_index   = 0;
        int addr_stack_index  = 0;
        
        REAL          real_stack[512];
        int           int_stack[512];
        InstructionIT address_stack[64];
        
        memset(real_stack, 0, sizeof(REAL)*512);
        memset(int_stack, 0, sizeof(int)*512);
        memset(address_stack, 0, sizeof(InstructionIT)*64);
        
        if (TRACE > 0) {
            // Check block coherency
            block->check();
        }
        
#define dispatchFirstScal() \
    {                       \
        goto loop;          \
    }
#define dispatchNextScal()    \
    {                         \
        if (TRACE >= 4) {     \
            traceInstruction(it, int_stack[int_stack_index], real_stack[real_stack_index]); \
        }                     \
        it++;                 \
        dispatchFirstScal()   \
    }
        
#define dispatchBranch1Scal()                        \
    {                                                \
        it = (*it)->fBranch1->fInstructions.begin(); \
        dispatchFirstScal();                         \
    }
#define dispatchBranch2Scal()                        \
    {                                                \
        it = (*it)->fBranch2->fInstructions.begin(); \
        dispatchFirstScal();                         \
    }
        
#define pushBranch1Scal()                                  \
    {                                                      \
        pushAddr_((*it)->fBranch1->fInstructions.begin()); \
    }
#define pushBranch2Scal()                                  \
    {                                                      \
        pushAddr_((*it)->fBranch2->fInstructions.begin()); \
    }
        
#define dispatchReturnScal() \
    {                        \
        it = popAddr_();     \
        dispatchFirstScal(); \
    }
#define saveReturnScal()   \
    {                      \
        pushAddr_(it + 1); \
    }
#define emptyReturnScal() (addr_stack_index == 0)
        
        InstructionIT it = block->fInstructions.begin();
    
        loop:
            // (*it)->write(&std::cout);
            switch ((*it)->fOpcode) {
                    
                // Number operations
                case FBCInstruction::kRealValue: {
                    pushReal(it, (*it)->fRealValue);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kInt32Value: {
                    pushInt((*it)->fIntValue);
                    dispatchNextScal();
                }
                    
                // Memory operations
                case FBCInstruction::kLoadSoundFieldInt: {
                    faustassert(this->fSoundTable.find((*it)->fName) != this->fSoundTable.end());
                    Soundfile* sf = this->fSoundTable[(*it)->fName];
                    int field_index = popInt();
                    int part = popInt();
                    int* field = nullptr;
                    switch (field_index) {
                        case Soundfile::kLength: {
                            field = sf->fLength;
                            break;
                        }
                        case Soundfile::kSR: {
                            field = sf->fSR;
                            break;
                        }
                        case Soundfile::kOffset: {
                            field = sf->fOffset;
                            break;
                        }
                        default:
                            faustassert(false);
                            break;
                    }
                    pushInt(field[part]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLoadSoundFieldReal: {
                    faustassert(this->fSoundTable.find((*it)->fName) != this->fSoundTable.end());
                    Soundfile* sf = this->fSoundTable[(*it)->fName];
                    // field_index (unused)
                    popInt();
                    int chan = popInt();
                    int offset = popInt();
                    REAL* buffer = reinterpret_cast<REAL**>(sf->fBuffers)[chan];
                    pushReal(it, buffer[offset]);
                    dispatchNextScal();
                }
        
                case FBCInstruction::kLoadReal: {
                    if (TRACE > 0) {
                        pushReal(it, fRealHeap[assertLoadRealHeap(it, (*it)->fOffset1)]);
                    } else {
                        pushReal(it, fRealHeap[(*it)->fOffset1]);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLoadInt: {
                    if (TRACE > 0) {
                        pushInt(fIntHeap[assertLoadIntHeap(it, (*it)->fOffset1)]);
                    } else {
                        pushInt(fIntHeap[(*it)->fOffset1]);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kStoreReal: {
                    if (TRACE > 0) {
                        fRealHeap[assertStoreRealHeap(it, (*it)->fOffset1)] = popReal(it);
                    } else {
                        fRealHeap[(*it)->fOffset1] = popReal(it);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kStoreInt: {
                    if (TRACE > 0) {
                        fIntHeap[assertStoreIntHeap(it, (*it)->fOffset1)] = popInt();
                    } else {
                        fIntHeap[(*it)->fOffset1] = popInt();
                    }
                    dispatchNextScal();
                }
                    
                // Directly store a value
                case FBCInstruction::kStoreRealValue: {
                    if (TRACE > 0) {
                        fRealHeap[assertStoreRealHeap(it, (*it)->fOffset1)] = (*it)->fRealValue;
                    } else {
                        fRealHeap[(*it)->fOffset1] = (*it)->fRealValue;
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kStoreIntValue: {
                    if (TRACE > 0) {
                        fIntHeap[assertStoreIntHeap(it, (*it)->fOffset1)] = (*it)->fIntValue;
                    } else {
                        fIntHeap[(*it)->fOffset1] = (*it)->fIntValue;
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLoadIndexedReal: {
                    int offset = popInt();
                    if (TRACE > 0) {
                        pushReal(it, fRealHeap[assertLoadRealHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)]);
                    } else {
                        pushReal(it, fRealHeap[(*it)->fOffset1 + offset]);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLoadIndexedInt: {
                    int offset = popInt();
                    if (TRACE > 0) {
                        pushInt(fIntHeap[assertLoadIntHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)]);
                    } else {
                        pushInt(fIntHeap[(*it)->fOffset1 + offset]);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kStoreIndexedReal: {
                    int offset = popInt();
                    if (TRACE > 0) {
                        fRealHeap[assertStoreRealHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)] = popReal(it);
                    } else {
                        fRealHeap[(*it)->fOffset1 + offset] = popReal(it);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kStoreIndexedInt: {
                    int offset = popInt();
                    if (TRACE > 0) {
                        fIntHeap[assertStoreIntHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)] = popInt();
                    } else {
                        fIntHeap[(*it)->fOffset1 + offset] = popInt();
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kBlockStoreReal: {
                    FIRBlockStoreRealInstruction<REAL>* inst = static_cast<FIRBlockStoreRealInstruction<REAL>*>(*it);
                    assertInterp(inst);
                    for (int i = 0; i < inst->fOffset2; i++) {
                        fRealHeap[inst->fOffset1 + i] = inst->fNumTable[i];
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kBlockStoreInt: {
                    FIRBlockStoreIntInstruction<REAL>* inst = static_cast<FIRBlockStoreIntInstruction<REAL>*>(*it);
                    assertInterp(inst);
                    for (int i = 0; i < inst->fOffset2; i++) {
                        fIntHeap[inst->fOffset1 + i] = inst->fNumTable[i];
                    }
                    dispatchNextScal();
                }
                   
                case FBCInstruction::kMoveReal: {
                    fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset2];
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMoveInt: {
                    fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset2];
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kPairMoveReal: {
                    fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset1 - 1];
                    fRealHeap[(*it)->fOffset2] = fRealHeap[(*it)->fOffset2 - 1];
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kPairMoveInt: {
                    fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset1 - 1];
                    fIntHeap[(*it)->fOffset2] = fIntHeap[(*it)->fOffset2 - 1];
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kBlockPairMoveReal: {
                    for (int i = (*it)->fOffset1; i < (*it)->fOffset2; i += 2) {
                        fRealHeap[i + 1] = fRealHeap[i];
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kBlockPairMoveInt: {
                    for (int i = (*it)->fOffset1; i < (*it)->fOffset2; i += 2) {
                        fIntHeap[i + 1] = fIntHeap[i];
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kBlockShiftReal: {
                    for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                        fRealHeap[i] = fRealHeap[i - 1];
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kBlockShiftInt: {
                    for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                        fIntHeap[i] = fIntHeap[i - 1];
                    }
                    dispatchNextScal();
                }
                    
                // Input/output access
                case FBCInstruction::kLoadInput: {
                    if (TRACE > 0) {
                        pushReal(it, fInputs[(*it)->fOffset1][assertAudioBuffer(it, popInt())]);
                    } else {
                        pushReal(it, fInputs[(*it)->fOffset1][popInt()]);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kStoreOutput: {
                    if (TRACE > 0) {
                        fOutputs[(*it)->fOffset1][assertAudioBuffer(it, popInt())] = popReal(it);
                    } else {
                        fOutputs[(*it)->fOffset1][popInt()] = popReal(it);
                    }
                    dispatchNextScal();
                }
                    
                // Cast operations
                case FBCInstruction::kCastReal: {
                    pushReal(it, REAL(popInt()));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kCastRealHeap: {
                    pushReal(it, REAL(fIntHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kCastInt: {
                    if (TRACE >= 3) {
                        pushInt(int(checkCastIntOverflow(it, popReal(it))));
                    } else {
                        pushInt(int(popReal(it)));
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kCastIntHeap: {
                    if (TRACE >= 3) {
                        pushInt(int(checkCastIntOverflow(it, fRealHeap[(*it)->fOffset1])));
                    } else {
                        pushInt(int(fRealHeap[(*it)->fOffset1]));
                    }
                    dispatchNextScal();
                }
                    
                // Bitcast operations
                case FBCInstruction::kBitcastInt: {
                    REAL v1 = popReal(it);
                    int  v2 = *reinterpret_cast<int*>(&v1);
                    pushInt(v2);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kBitcastReal: {
                    int  v1 = popInt();
                    REAL v2 = *reinterpret_cast<REAL*>(&v1);
                    pushReal(it, v2);
                    dispatchNextScal();
                }
                    
                //-------------------------------------------------------
                // Standard math operations : 'stack' OP 'stack' version
                //-------------------------------------------------------
                    
                case FBCInstruction::kAddReal: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushReal(it, v1 + v2);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAddInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    if (TRACE > 0) {
                        int res;
                        if (__builtin_sadd_overflow(v1, v2, &res)) {
                            warningOverflow(it, "kAddInt");
                        }
                        pushInt(res);
                    } else {
                        pushInt(v1 + v2);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSubReal: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushReal(it, v1 - v2);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSubInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    if (TRACE > 0) {
                        int res;
                        if (__builtin_ssub_overflow(v1, v2, &res)) {
                            warningOverflow(it, "kSubInt");
                        }
                        pushInt(res);
                    } else {
                        pushInt(v1 - v2);
                    }
                    dispatchNextScal();
                }
                
                case FBCInstruction::kMultReal: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushReal(it, v1 * v2);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMultInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    if (TRACE > 0) {
                        int res;
                        if (__builtin_smul_overflow(v1, v2, &res)) {
                            warningOverflow(it, "kMultInt");
                        }
                        pushInt(res);
                    } else {
                        pushInt(v1 * v2);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kDivReal: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    if (TRACE > 0) {
                        checkDivZero(it, v2);
                    }
                    pushReal(it, v1 / v2);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kDivInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    if (TRACE > 0) {
                        checkDivZero(it, v2);
                    }
                    pushInt(v1 / v2);
                    dispatchNextScal();
                    dispatchNextScal();
                }
                    
                //-------------------------------------------------------
                // Standard math operations : 'stack' OP 'stack' version
                //-------------------------------------------------------
            
                case FBCInstruction::kRemReal: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    if (TRACE > 0) {
                        checkDivZero(it, v2);
                    }
                    pushReal(it, std::remainder(v1, v2));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRemInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    if (TRACE > 0) {
                        checkDivZero(it, v2);
                    }
                    pushInt(v1 % v2);
                    dispatchNextScal();
                }
                    
                // Shift operation
                case FBCInstruction::kLshInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    if (TRACE > 0) {
                        pushInt(v1 << warningBitshift(it, v2));
                    } else {
                        pushInt(v1 << v2);
                    }
                    dispatchNextScal();
                }
                
                case FBCInstruction::kARshInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    if (TRACE > 0) {
                        pushInt(v1 >> warningBitshift(it, v2));
                    } else {
                        pushInt(v1 >> v2);
                    }
                    dispatchNextScal();
                }
                
               case FBCInstruction::kLRshInt: {
                    // TODO
                    int v1 = popInt();
                    int v2 = popInt();
                    if (TRACE > 0) {
                        pushInt(v1 >> warningBitshift(it, v2));
                    } else {
                        pushInt(v1 >> v2);
                    }
                    dispatchNextScal();
                }
                    
                // Comparaison Int
                case FBCInstruction::kGTInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    pushInt(v1 > v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kLTInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    pushInt(v1 < v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kGEInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    pushInt(v1 >= v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kLEInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    pushInt(v1 <= v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kEQInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    pushInt(v1 == v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kNEInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    pushInt(v1 != v2);
                    dispatchNextScal();
                }
                    
                // Comparaison Real
                case FBCInstruction::kGTReal: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushInt(v1 > v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kLTReal: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushInt(v1 < v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kGEReal: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushInt(v1 >= v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kLEReal: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushInt(v1 <= v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kEQReal: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushInt(v1 == v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kNEReal: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushInt(v1 != v2);
                    dispatchNextScal();
                }
                
                // Logical operations
                case FBCInstruction::kANDInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    pushInt(v1 & v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kORInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    pushInt(v1 | v2);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kXORInt: {
                    int v1 = popInt();
                    int v2 = popInt();
                    pushInt(v1 ^ v2);
                    dispatchNextScal();
                }
                    
                //-----------------------------------------------------
                // Standard math operations : 'heap' OP 'heap' version
                //-----------------------------------------------------
                    
                case FBCInstruction::kAddRealHeap: {
                    pushReal(it, fRealHeap[(*it)->fOffset1] + fRealHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kAddIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] + fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kSubRealHeap: {
                    pushReal(it, fRealHeap[(*it)->fOffset1] - fRealHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kSubIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] - fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kMultRealHeap: {
                    pushReal(it, fRealHeap[(*it)->fOffset1] * fRealHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kMultIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] * fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kDivRealHeap: {
                    pushReal(it, fRealHeap[(*it)->fOffset1] / fRealHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kDivIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] / fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                
                case FBCInstruction::kRemRealHeap: {
                    pushReal(it, std::remainder(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatchNextScal();
                }
                
                case FBCInstruction::kRemIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] % fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                // Shift operation
                case FBCInstruction::kLshIntHeap: {
                    if (TRACE > 0) {
                        pushInt(fIntHeap[(*it)->fOffset1] << warningBitshift(it, fIntHeap[(*it)->fOffset2]));
                    } else {
                        pushInt(fIntHeap[(*it)->fOffset1] << fIntHeap[(*it)->fOffset2]);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kARshIntHeap: {
                    if (TRACE > 0) {
                        pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, fIntHeap[(*it)->fOffset2]));
                    } else {
                        pushInt(fIntHeap[(*it)->fOffset1] >> fIntHeap[(*it)->fOffset2]);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLRshIntHeap: {
                    if (TRACE > 0) {
                        pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, fIntHeap[(*it)->fOffset2]));
                    } else {
                        pushInt(fIntHeap[(*it)->fOffset1] >> fIntHeap[(*it)->fOffset2]);
                    }
                    dispatchNextScal();
                }
                    
                // Comparaison Int
                case FBCInstruction::kGTIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] > fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLTIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] < fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kGEIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] >= fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLEIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] <= fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kEQIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] == fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kNEIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] != fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                // Comparaison Real
                case FBCInstruction::kGTRealHeap: {
                    pushInt(fRealHeap[(*it)->fOffset1] > fRealHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLTRealHeap: {
                    pushInt(fRealHeap[(*it)->fOffset1] < fRealHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kGERealHeap: {
                    pushInt(fRealHeap[(*it)->fOffset1] >= fRealHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLERealHeap: {
                    pushInt(fRealHeap[(*it)->fOffset1] <= fRealHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kEQRealHeap: {
                    pushInt(fRealHeap[(*it)->fOffset1] == fRealHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kNERealHeap: {
                    pushInt(fRealHeap[(*it)->fOffset1] != fRealHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                // Logical operations
                case FBCInstruction::kANDIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] & fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kORIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] | fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kXORIntHeap: {
                    pushInt(fIntHeap[(*it)->fOffset1] ^ fIntHeap[(*it)->fOffset2]);
                    dispatchNextScal();
                }
                    
                //------------------------------------------------------
                // Standard math operations : 'stack' OP 'heap' version
                //------------------------------------------------------
                    
                case FBCInstruction::kAddRealStack: {
                    REAL v1 = popReal(it);
                    pushReal(it, fRealHeap[(*it)->fOffset1] + v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAddIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] + v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSubRealStack: {
                    REAL v1 = popReal(it);
                    pushReal(it, fRealHeap[(*it)->fOffset1] - v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSubIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] - v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMultRealStack: {
                    REAL v1 = popReal(it);
                    pushReal(it, fRealHeap[(*it)->fOffset1] * v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMultIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] * v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kDivRealStack: {
                    REAL v1 = popReal(it);
                    pushReal(it, fRealHeap[(*it)->fOffset1] / v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kDivIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] / v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRemRealStack: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::remainder(fRealHeap[(*it)->fOffset1], v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRemIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] % v1);
                    dispatchNextScal();
                }
                    
                // Shift operation
                case FBCInstruction::kLshIntStack: {
                    int v1 = popInt();
                    if (TRACE > 0) {
                        pushInt(fIntHeap[(*it)->fOffset1] << warningBitshift(it, v1));
                    } else {
                        pushInt(fIntHeap[(*it)->fOffset1] << v1);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kARshIntStack: {
                    int v1 = popInt();
                    if (TRACE > 0) {
                        pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, v1));
                    } else {
                        pushInt(fIntHeap[(*it)->fOffset1] >> v1);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLRshIntStack: {
                    int v1 = popInt();
                    if (TRACE > 0) {
                        pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, v1));
                    } else {
                        pushInt(fIntHeap[(*it)->fOffset1] >> v1);
                    }
                    dispatchNextScal();
                }
                    
                // Comparaison Int
                case FBCInstruction::kGTIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] > v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLTIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] < v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kGEIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] >= v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLEIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] <= v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kEQIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] == v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kNEIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] != v1);
                    dispatchNextScal();
                }
                    
                // Comparaison Real
                case FBCInstruction::kGTRealStack: {
                    REAL v1 = popReal(it);
                    pushInt(fRealHeap[(*it)->fOffset1] > v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLTRealStack: {
                    REAL v1 = popReal(it);
                    pushInt(fRealHeap[(*it)->fOffset1] < v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kGERealStack: {
                    REAL v1 = popReal(it);
                    pushInt(fRealHeap[(*it)->fOffset1] >= v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLERealStack: {
                    REAL v1 = popReal(it);
                    pushInt(fRealHeap[(*it)->fOffset1] <= v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kEQRealStack: {
                    REAL v1 = popReal(it);
                    pushInt(fRealHeap[(*it)->fOffset1] == v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kNERealStack: {
                    REAL v1 = popReal(it);
                    pushInt(fRealHeap[(*it)->fOffset1] != v1);
                    dispatchNextScal();
                }
                    
                // Logical operations
                case FBCInstruction::kANDIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] & v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kORIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] | v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kXORIntStack: {
                    int v1 = popInt();
                    pushInt(fIntHeap[(*it)->fOffset1] ^ v1);
                    dispatchNextScal();
                }
                    
                //-------------------------------------------------------
                // Standard math operations : 'stack' OP 'value' version
                //-------------------------------------------------------
                    
                case FBCInstruction::kAddRealStackValue: {
                    REAL v1 = popReal(it);
                    pushReal(it, (*it)->fRealValue + v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAddIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue + v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSubRealStackValue: {
                    REAL v1 = popReal(it);
                    pushReal(it, (*it)->fRealValue - v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSubIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue - v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMultRealStackValue: {
                    REAL v1 = popReal(it);
                    pushReal(it, (*it)->fRealValue * v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMultIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue * v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kDivRealStackValue: {
                    REAL v1 = popReal(it);
                    pushReal(it, (*it)->fRealValue / v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kDivIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue / v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRemRealStackValue: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::remainder((*it)->fRealValue, v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRemIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue % v1);
                    dispatchNextScal();
                }
                    
                // Shift operation
                case FBCInstruction::kLshIntStackValue: {
                    int v1 = popInt();
                    if (TRACE > 0) {
                        pushInt((*it)->fIntValue << warningBitshift(it, v1));
                    } else {
                        pushInt((*it)->fIntValue << v1);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kARshIntStackValue: {
                    int v1 = popInt();
                    if (TRACE > 0) {
                        pushInt((*it)->fIntValue >> warningBitshift(it, v1));
                    } else {
                        pushInt((*it)->fIntValue >> v1);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLRshIntStackValue: {
                    int v1 = popInt();
                    if (TRACE > 0) {
                        pushInt((*it)->fIntValue >> warningBitshift(it, v1));
                    } else {
                        pushInt((*it)->fIntValue >> v1);
                    }
                    dispatchNextScal();
                }
                    
                // Comparaison Int
                case FBCInstruction::kGTIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue > v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLTIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue < v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kGEIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue >= v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLEIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue <= v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kEQIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue == v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kNEIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue != v1);
                    dispatchNextScal();
                }
                    
                // Comparaison Real
                case FBCInstruction::kGTRealStackValue: {
                    REAL v1 = popReal(it);
                    pushInt((*it)->fRealValue > v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLTRealStackValue: {
                    REAL v1 = popReal(it);
                    pushInt((*it)->fRealValue < v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kGERealStackValue: {
                    REAL v1 = popReal(it);
                    pushInt((*it)->fRealValue >= v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLERealStackValue: {
                    REAL v1 = popReal(it);
                    pushInt((*it)->fRealValue <= v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kEQRealStackValue: {
                    REAL v1 = popReal(it);
                    pushInt((*it)->fRealValue == v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kNERealStackValue: {
                    REAL v1 = popReal(it);
                    pushInt((*it)->fRealValue != v1);
                    dispatchNextScal();
                }
                    
                // Logical operations
                case FBCInstruction::kANDIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue & v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kORIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue | v1);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kXORIntStackValue: {
                    int v1 = popInt();
                    pushInt((*it)->fIntValue ^ v1);
                    dispatchNextScal();
                }
                    
                //------------------------------------------------------
                // Standard math operations : 'value' OP 'heap' version
                //------------------------------------------------------
                    
                case FBCInstruction::kAddRealValue: {
                    pushReal(it, (*it)->fRealValue + fRealHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAddIntValue: {
                    pushInt((*it)->fIntValue + fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSubRealValue: {
                    pushReal(it, (*it)->fRealValue - fRealHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSubIntValue: {
                    pushInt((*it)->fIntValue - fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMultRealValue: {
                    pushReal(it, (*it)->fRealValue * fRealHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMultIntValue: {
                    pushInt((*it)->fIntValue * fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kDivRealValue: {
                    pushReal(it, (*it)->fRealValue / fRealHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kDivIntValue: {
                    pushInt((*it)->fIntValue / fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRemRealValue: {
                    pushReal(it, std::remainder((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRemIntValue: {
                    pushInt((*it)->fIntValue % fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                // Shift operation
                case FBCInstruction::kLshIntValue: {
                    if (TRACE > 0) {
                        pushInt((*it)->fIntValue << warningBitshift(it, fIntHeap[(*it)->fOffset1]));
                    } else {
                        pushInt((*it)->fIntValue << fIntHeap[(*it)->fOffset1]);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kARshIntValue: {
                    if (TRACE > 0) {
                        pushInt((*it)->fIntValue >> warningBitshift(it, fIntHeap[(*it)->fOffset1]));
                    } else {
                        pushInt((*it)->fIntValue >> fIntHeap[(*it)->fOffset1]);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLRshIntValue: {
                    if (TRACE > 0) {
                        pushInt((*it)->fIntValue >> warningBitshift(it, fIntHeap[(*it)->fOffset1]));
                    } else {
                        pushInt((*it)->fIntValue >> fIntHeap[(*it)->fOffset1]);
                    }
                    dispatchNextScal();
                }
                    
                // Comparaison Int
                case FBCInstruction::kGTIntValue: {
                    pushInt((*it)->fIntValue > fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLTIntValue: {
                    pushInt((*it)->fIntValue < fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kGEIntValue: {
                    pushInt((*it)->fIntValue >= fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLEIntValue: {
                    pushInt((*it)->fIntValue <= fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kEQIntValue: {
                    pushInt((*it)->fIntValue == fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kNEIntValue: {
                    pushInt((*it)->fIntValue != fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                // Comparaison Real
                case FBCInstruction::kGTRealValue: {
                    pushInt((*it)->fRealValue > fRealHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLTRealValue: {
                    pushInt((*it)->fRealValue < fRealHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kGERealValue: {
                    pushInt((*it)->fRealValue >= fRealHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLERealValue: {
                    pushInt((*it)->fRealValue <= fRealHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kEQRealValue: {
                    pushInt((*it)->fRealValue == fRealHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kNERealValue: {
                    pushInt((*it)->fRealValue != fRealHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                // Logical operations
                case FBCInstruction::kANDIntValue: {
                    pushInt((*it)->fIntValue & fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kORIntValue: {
                    pushInt((*it)->fIntValue | fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kXORIntValue: {
                    pushInt((*it)->fIntValue ^ fIntHeap[(*it)->fOffset1]);
                    dispatchNextScal();
                }
                    
                //----------------------------------------------------
                // Standard math operations : Value inverted version
                // (non commutative operations)
                //----------------------------------------------------
                    
                case FBCInstruction::kSubRealValueInvert: {
                    pushReal(it, fRealHeap[(*it)->fOffset1] - (*it)->fRealValue);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSubIntValueInvert: {
                    pushInt(fIntHeap[(*it)->fOffset1] - (*it)->fIntValue);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kDivRealValueInvert: {
                    pushReal(it, fRealHeap[(*it)->fOffset1] / (*it)->fRealValue);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kDivIntValueInvert: {
                    pushInt(fIntHeap[(*it)->fOffset1] / (*it)->fIntValue);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRemRealValueInvert: {
                    pushReal(it, std::remainder(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRemIntValueInvert: {
                    pushInt(fIntHeap[(*it)->fOffset1] % (*it)->fIntValue);
                    dispatchNextScal();
                }
                    
                // Shift operation
                case FBCInstruction::kLshIntValueInvert: {
                    if (TRACE > 0) {
                        pushInt(fIntHeap[(*it)->fOffset1] << warningBitshift(it, (*it)->fIntValue));
                    } else {
                        pushInt(fIntHeap[(*it)->fOffset1] << (*it)->fIntValue);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kARshIntValueInvert: {
                    if (TRACE > 0) {
                        pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, (*it)->fIntValue));
                    } else {
                        pushInt(fIntHeap[(*it)->fOffset1] >> (*it)->fIntValue);
                    }
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLRshIntValueInvert: {
                    if (TRACE > 0) {
                        pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, (*it)->fIntValue));
                    } else {
                        pushInt(fIntHeap[(*it)->fOffset1] >> (*it)->fIntValue);
                    }
                    dispatchNextScal();
                }
                    
                // Comparaison Int
                case FBCInstruction::kGTIntValueInvert: {
                    pushInt(fIntHeap[(*it)->fOffset1] > (*it)->fIntValue);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLTIntValueInvert: {
                    pushInt(fIntHeap[(*it)->fOffset1] < (*it)->fIntValue);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kGEIntValueInvert: {
                    pushInt(fIntHeap[(*it)->fOffset1] >= (*it)->fIntValue);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLEIntValueInvert: {
                    pushInt(fIntHeap[(*it)->fOffset1] <= (*it)->fIntValue);
                    dispatchNextScal();
                }
                    
                // Comparaison Real
                case FBCInstruction::kGTRealValueInvert: {
                    pushInt(fRealHeap[(*it)->fOffset1] > (*it)->fRealValue);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLTRealValueInvert: {
                    pushInt(fRealHeap[(*it)->fOffset1] < (*it)->fRealValue);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kGERealValueInvert: {
                    pushInt(fRealHeap[(*it)->fOffset1] >= (*it)->fRealValue);
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLERealValueInvert: {
                    pushInt(fRealHeap[(*it)->fOffset1] <= (*it)->fRealValue);
                    dispatchNextScal();
                }
                    
                //---------------------
                // Extended unary math
                //---------------------
                    
                case FBCInstruction::kAbs: {
                    int v = popInt();
                    pushInt(std::abs(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAbsf: {
                    REAL v = popReal(it);
                    pushReal(it, std::fabs(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAcosf: {
                    REAL v = popReal(it);
                    pushReal(it, std::acos(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAcoshf: {
                    REAL v = popReal(it);
                    pushReal(it, std::acosh(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAsinf: {
                    REAL v = popReal(it);
                    pushReal(it, std::asin(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAsinhf: {
                    REAL v = popReal(it);
                    pushReal(it, std::asinh(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAtanf: {
                    REAL v = popReal(it);
                    pushReal(it, std::atan(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAtanhf: {
                    REAL v = popReal(it);
                    pushReal(it, std::atanh(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kCeilf: {
                    REAL v = popReal(it);
                    pushReal(it, std::ceil(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kCosf: {
                    REAL v = popReal(it);
                    pushReal(it, std::cos(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kCoshf: {
                    REAL v = popReal(it);
                    pushReal(it, std::cosh(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kExpf: {
                    REAL v = popReal(it);
                    pushReal(it, std::exp(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kFloorf: {
                    REAL v = popReal(it);
                    pushReal(it, std::floor(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLogf: {
                    REAL v = popReal(it);
                    pushReal(it, std::log(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLog10f: {
                    REAL v = popReal(it);
                    pushReal(it, std::log10(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRintf: {
                    REAL v = popReal(it);
                    pushReal(it, std::rint(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRoundf: {
                    REAL v = popReal(it);
                    pushReal(it, std::round(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSinf: {
                    REAL v = popReal(it);
                    pushReal(it, std::sin(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSinhf: {
                    REAL v = popReal(it);
                    pushReal(it, std::sinh(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSqrtf: {
                    REAL v = popReal(it);
                    pushReal(it, std::sqrt(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kTanf: {
                    REAL v = popReal(it);
                    pushReal(it, std::tan(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kTanhf: {
                    REAL v = popReal(it);
                    pushReal(it, std::tanh(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kIsnanf: {
                    REAL v = popReal(it);
                    pushInt(std::isnan(v));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kIsinff: {
                    REAL v = popReal(it);
                    pushInt(std::isinf(v));
                    dispatchNextScal();
                }
                 
                //------------------------------------
                // Extended unary math (heap version)
                //------------------------------------
                    
                case FBCInstruction::kAbsHeap: {
                    pushInt(std::abs(fIntHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAbsfHeap: {
                    pushReal(it, std::fabs(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAcosfHeap: {
                    pushReal(it, std::acos(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAcoshfHeap: {
                    pushReal(it, std::acosh(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAsinfHeap: {
                    pushReal(it, std::asin(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAsinhfHeap: {
                    pushReal(it, std::asinh(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAtanfHeap: {
                    pushReal(it, std::atan(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kAtanhfHeap: {
                    pushReal(it, std::atanh(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kCeilfHeap: {
                    pushReal(it, std::ceil(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kCosfHeap: {
                    pushReal(it, std::cos(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kCoshfHeap: {
                    pushReal(it, std::cosh(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kExpfHeap: {
                    pushReal(it, std::exp(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kFloorfHeap: {
                    pushReal(it, std::floor(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLogfHeap: {
                    pushReal(it, std::log(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kLog10fHeap: {
                    pushReal(it, std::log10(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRintfHeap: {
                    pushReal(it, std::rint(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kRoundfHeap: {
                    pushReal(it, std::round(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSinfHeap: {
                    pushReal(it, std::sin(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSinhfHeap: {
                    pushReal(it, std::sinh(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kSqrtfHeap: {
                    pushReal(it, std::sqrt(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kTanfHeap: {
                    pushReal(it, std::tan(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kTanhfHeap: {
                    pushReal(it, std::tanh(fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                //----------------------
                // Extended binary math
                //----------------------
                    
                case FBCInstruction::kAtan2f: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushReal(it, std::atan2(v1, v2));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kFmodf: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushReal(it, std::fmod(v1, v2));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kPowf: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushReal(it, std::pow(v1, v2));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMax: {
                    int v1 = popInt();
                    int v2 = popInt();
                    pushInt(std::max(v1, v2));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMaxf: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushReal(it, std::max(v1, v2));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMin: {
                    int v1 = popInt();
                    int v2 = popInt();
                    pushInt(std::min(v1, v2));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMinf: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushReal(it, std::min(v1, v2));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kCopysignf: {
                    REAL v1 = popReal(it);
                    REAL v2 = popReal(it);
                    pushReal(it, std::copysign(v1, v2));
                    dispatchNextScal();
                }
                    
                //-------------------------------------
                // Extended binary math (heap version)
                //-------------------------------------
                    
                case FBCInstruction::kAtan2fHeap: {
                    pushReal(it, std::atan2(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kFmodfHeap: {
                    pushReal(it, std::fmod(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kPowfHeap: {
                    pushReal(it, std::pow(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMaxHeap: {
                    pushInt(std::max(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMaxfHeap: {
                    pushReal(it, std::max(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMinHeap: {
                    pushInt(std::min(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMinfHeap: {
                    pushReal(it, std::min(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatchNextScal();
                }
                    
                //--------------------------------------
                // Extended binary math (stack version)
                //--------------------------------------
                    
                case FBCInstruction::kAtan2fStack: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::atan2(fRealHeap[(*it)->fOffset1], v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kFmodfStack: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::fmod(fRealHeap[(*it)->fOffset1], v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kPowfStack: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::pow(fRealHeap[(*it)->fOffset1], v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMaxStack: {
                    int v1 = popInt();
                    pushInt(std::max(fIntHeap[(*it)->fOffset1], v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMaxfStack: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::max(fRealHeap[(*it)->fOffset1], v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMinStack: {
                    int v1 = popInt();
                    pushInt(std::min(fIntHeap[(*it)->fOffset1], v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMinfStack: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::min(fRealHeap[(*it)->fOffset1], v1));
                    dispatchNextScal();
                }
                    
                //--------------------------------------------
                // Extended binary math (stack/value version)
                //--------------------------------------------
                    
                case FBCInstruction::kAtan2fStackValue: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::atan2((*it)->fRealValue, v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kFmodfStackValue: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::fmod((*it)->fRealValue, v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kPowfStackValue: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::pow((*it)->fRealValue, v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMaxStackValue: {
                    int v1 = popInt();
                    pushInt(std::max((*it)->fIntValue, v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMaxfStackValue: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::max((*it)->fRealValue, v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMinStackValue: {
                    int v1 = popInt();
                    pushInt(std::min((*it)->fIntValue, v1));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMinfStackValue: {
                    REAL v1 = popReal(it);
                    pushReal(it, std::min((*it)->fRealValue, v1));
                    dispatchNextScal();
                }
                    
                //-------------------------------------
                // Extended binary math (Value version)
                //-------------------------------------
                    
                case FBCInstruction::kAtan2fValue: {
                    pushReal(it, std::atan2((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kFmodfValue: {
                    pushReal(it, std::fmod((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kPowfValue: {
                    pushReal(it, std::pow((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMaxValue: {
                    pushInt(std::max((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMaxfValue: {
                    pushReal(it, std::max((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMinValue: {
                    pushInt(std::min((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kMinfValue: {
                    pushReal(it, std::min((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatchNextScal();
                }
                    
                //-------------------------------------------------------------------
                // Extended binary math (Value version) : non commutative operations
                //-------------------------------------------------------------------
                    
                case FBCInstruction::kAtan2fValueInvert: {
                    pushReal(it, std::atan2(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kFmodfValueInvert: {
                    pushReal(it, std::fmod(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    dispatchNextScal();
                }
                    
                case FBCInstruction::kPowfValueInvert: {
                    pushReal(it, std::pow(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    dispatchNextScal();
                }
                    
                //---------
                // Control
                //---------
                    
                case FBCInstruction::kReturn: {
                    // Empty addr stack = end of computation
                    if (emptyReturnScal()) {
                        goto end;
                    } else {
                        dispatchReturnScal();
                    }
                }
                    
                case FBCInstruction::kIf: {
                    // Keep next instruction
                    saveReturnScal();
                    
                    if (popInt()) {
                        // Execute new block
                        assertInterp((*it)->fBranch1);
                        dispatchBranch1Scal();
                        // No value (If)
                    } else {
                        // Execute new block
                        assertInterp((*it)->fBranch2);
                        dispatchBranch2Scal();
                        // No value (If)
                    }
                }
                    
                case FBCInstruction::kSelectReal: {
                    // Keep next instruction
                    saveReturnScal();
                    
                    if (popInt()) {
                        // Execute new block
                        assertInterp((*it)->fBranch1);
                        dispatchBranch1Scal();
                        // Real value
                    } else {
                        // Execute new block
                        assertInterp((*it)->fBranch2);
                        dispatchBranch2Scal();
                        // Real value
                    }
                }
                    
                case FBCInstruction::kSelectInt: {
                    // Keep next instruction
                    saveReturnScal();
                    
                    if (popInt()) {
                        // Execute new block
                        assertInterp((*it)->fBranch1);
                        dispatchBranch1Scal();
                        // Int value
                    } else {
                        // Execute new block
                        assertInterp((*it)->fBranch2);
                        dispatchBranch2Scal();
                        // Int value
                    }
                }
                    
                case FBCInstruction::kCondBranch: {
                    // If condition is true, just branch back on the block beginning
                    if (popInt()) {
                        assertInterp((*it)->fBranch1);
                        dispatchBranch1Scal();
                    } else {
                        // Just continue after 'loop block' (do the final 'return')
                        dispatchNextScal();
                    }
                }
                    
                case FBCInstruction::kLoop: {
                    // Keep next instruction
                    saveReturnScal();
                    
                    // Push branch2 (loop content)
                    assertInterp((*it)->fBranch2);
                    pushBranch2Scal();
                    
                    // And start branch1 loop variable declaration block
                    assertInterp((*it)->fBranch1);
                    dispatchBranch1Scal();
                }
                    
                default:
                    faustassert(false);
                    break;
            }
        
    end:
        // Check stack coherency
        assertInterp(real_stack_index == 0 && int_stack_index == 0);
    }
   #else
    void executeBlock(FBCBlockInstruction<REAL>* block)
    {
        static void* fDispatchTable[] = {

            // Numbers
            &&do_kRealValue, &&do_kInt32Value,

            // Memory
            &&do_kLoadReal, &&do_kLoadInt, &&do_kLoadSoundFieldInt, &&do_kLoadSoundFieldReal, &&do_kStoreReal, &&do_kStoreInt,
            &&do_kStoreRealValue, &&do_kStoreIntValue, &&do_kLoadIndexedReal, &&do_kLoadIndexedInt,
            &&do_kStoreIndexedReal, &&do_kStoreIndexedInt, &&do_kBlockStoreReal, &&do_kBlockStoreInt, &&do_kMoveReal,
            &&do_kMoveInt, &&do_kPairMoveReal, &&do_kPairMoveInt, &&do_kBlockPairMoveReal, &&do_kBlockPairMoveInt,
            &&do_kBlockShiftReal, &&do_kBlockShiftInt, &&do_kLoadInput, &&do_kStoreOutput,

            // Cast/bitcast
            &&do_kCastReal, &&do_kCastInt, &&do_kCastRealHeap, &&do_kCastIntHeap, &&do_kBitcastInt, &&do_kBitcastReal,

            // Standard math (stack OP stack)
            &&do_kAddReal, &&do_kAddInt, &&do_kSubReal, &&do_kSubInt, &&do_kMultReal, &&do_kMultInt, &&do_kDivReal,
            &&do_kDivInt, &&do_kRemReal, &&do_kRemInt, &&do_kLshInt, &&do_kARshInt, &&do_kLRshInt, &&do_kGTInt, &&do_kLTInt,
            &&do_kGEInt, &&do_kLEInt, &&do_kEQInt, &&do_kNEInt, &&do_kGTReal, &&do_kLTReal, &&do_kGEReal, &&do_kLEReal,
            &&do_kEQReal, &&do_kNEReal, &&do_kANDInt, &&do_kORInt, &&do_kXORInt,

            // Standard math (heap OP heap)
            &&do_kAddRealHeap, &&do_kAddIntHeap, &&do_kSubRealHeap, &&do_kSubIntHeap, &&do_kMultRealHeap,
            &&do_kMultIntHeap, &&do_kDivRealHeap, &&do_kDivIntHeap, &&do_kRemRealHeap, &&do_kRemIntHeap,
            &&do_kLshIntHeap, &&do_kARshIntHeap, &&do_kLRshIntHeap, &&do_kGTIntHeap, &&do_kLTIntHeap, &&do_kGEIntHeap, &&do_kLEIntHeap,
            &&do_kEQIntHeap, &&do_kNEIntHeap, &&do_kGTRealHeap, &&do_kLTRealHeap, &&do_kGERealHeap, &&do_kLERealHeap,
            &&do_kEQRealHeap, &&do_kNERealHeap, &&do_kANDIntHeap, &&do_kORIntHeap, &&do_kXORIntHeap,

            // Standard math (heap OP stack)
            &&do_kAddRealStack, &&do_kAddIntStack, &&do_kSubRealStack, &&do_kSubIntStack, &&do_kMultRealStack,
            &&do_kMultIntStack, &&do_kDivRealStack, &&do_kDivIntStack, &&do_kRemRealStack, &&do_kRemIntStack,
            &&do_kLshIntStack, &&do_kARshIntStack, &&do_kLRshIntStack, &&do_kGTIntStack, &&do_kLTIntStack, &&do_kGEIntStack,
            &&do_kLEIntStack, &&do_kEQIntStack, &&do_kNEIntStack, &&do_kGTRealStack, &&do_kLTRealStack,
            &&do_kGERealStack, &&do_kLERealStack, &&do_kEQRealStack, &&do_kNERealStack, &&do_kANDIntStack,
            &&do_kORIntStack, &&do_kXORIntStack,

            // Standard math (value OP stack)
            &&do_kAddRealStackValue, &&do_kAddIntStackValue, &&do_kSubRealStackValue, &&do_kSubIntStackValue,
            &&do_kMultRealStackValue, &&do_kMultIntStackValue, &&do_kDivRealStackValue, &&do_kDivIntStackValue,
            &&do_kRemRealStackValue, &&do_kRemIntStackValue, &&do_kLshIntStackValue, &&do_kARshIntStackValue, &&do_kLRshIntStackValue,
            &&do_kGTIntStackValue, &&do_kLTIntStackValue, &&do_kGEIntStackValue, &&do_kLEIntStackValue,
            &&do_kEQIntStackValue, &&do_kNEIntStackValue, &&do_kGTRealStackValue, &&do_kLTRealStackValue,
            &&do_kGERealStackValue, &&do_kLERealStackValue, &&do_kEQRealStackValue, &&do_kNERealStackValue,
            &&do_kANDIntStackValue, &&do_kORIntStackValue, &&do_kXORIntStackValue,

            // Standard math (value OP heap)
            &&do_kAddRealValue, &&do_kAddIntValue, &&do_kSubRealValue, &&do_kSubIntValue, &&do_kMultRealValue,
            &&do_kMultIntValue, &&do_kDivRealValue, &&do_kDivIntValue, &&do_kRemRealValue, &&do_kRemIntValue,
            &&do_kLshIntValue, &&do_kARshIntValue, &&do_kLRshIntValue, &&do_kGTIntValue, &&do_kLTIntValue, &&do_kGEIntValue,
            &&do_kLEIntValue, &&do_kEQIntValue, &&do_kNEIntValue, &&do_kGTRealValue, &&do_kLTRealValue,
            &&do_kGERealValue, &&do_kLERealValue, &&do_kEQRealValue, &&do_kNERealValue, &&do_kANDIntValue,
            &&do_kORIntValue, &&do_kXORIntValue,

            // Standard math (value OP heap) : non commutative operations
            &&do_kSubRealValueInvert, &&do_kSubIntValueInvert, &&do_kDivRealValueInvert, &&do_kDivIntValueInvert,
            &&do_kRemRealValueInvert, &&do_kRemIntValueInvert, &&do_kLshIntValueInvert, &&do_kARshIntValueInvert, &&do_kLRshIntValueInvert,
            &&do_kGTIntValueInvert, &&do_kLTIntValueInvert, &&do_kGEIntValueInvert, &&do_kLEIntValueInvert,
            &&do_kGTRealValueInvert, &&do_kLTRealValueInvert, &&do_kGERealValueInvert, &&do_kLERealValueInvert,

            // Extended unary math
            &&do_kAbs, &&do_kAbsf, &&do_kAcosf, &&do_kAcoshf, &&do_kAsinf, &&do_kAsinhf, &&do_kAtanf, &&do_kAtanhf, &&do_kCeilf,
            &&do_kCosf, &&do_kCoshf,
            &&do_kExpf, &&do_kFloorf, &&do_kLogf, &&do_kLog10f, &&do_kRintf, &&do_kRoundf, &&do_kSinf, &&do_kSinhf, &&do_kSqrtf,
            &&do_kTanf, &&do_kTanhf, &&do_kIsnanf, &&do_kIsinff,

            // Extended unary math (heap OP heap)
            &&do_kAbsHeap, &&do_kAbsfHeap, &&do_kAcosfHeap, &&do_kAcoshfHeap, &&do_kAsinfHeap, &&do_kAsinhfHeap, &&do_kAtanfHeap, &&do_kAtanhfHeap,
            &&do_kCeilfHeap,
            &&do_kCosfHeap, &&do_kCoshfHeap, &&do_kExpfHeap, &&do_kFloorfHeap, &&do_kLogfHeap, &&do_kLog10fHeap,
            &&do_kRintfHeap, &&do_kRoundfHeap, &&do_kSinfHeap, &&do_kSinhfHeap, &&do_kSqrtfHeap, &&do_kTanfHeap, &&do_kTanhfHeap,

            // Extended binary math
            &&do_kAtan2f, &&do_kFmodf, &&do_kPowf, &&do_kMax, &&do_kMaxf, &&do_kMin, &&do_kMinf, &&do_kCopysignf,

            // Extended binary math (heap version)
            &&do_kAtan2fHeap, &&do_kFmodfHeap, &&do_kPowfHeap, &&do_kMaxHeap, &&do_kMaxfHeap, &&do_kMinHeap,
            &&do_kMinfHeap,

            // Extended binary math (stack version)
            &&do_kAtan2fStack, &&do_kFmodfStack, &&do_kPowfStack, &&do_kMaxStack, &&do_kMaxfStack, &&do_kMinStack,
            &&do_kMinfStack,

            // Extended binary math (Stack/Value version)
            &&do_kAtan2fStackValue, &&do_kFmodfStackValue, &&do_kPowfStackValue, &&do_kMaxStackValue,
            &&do_kMaxfStackValue, &&do_kMinStackValue, &&do_kMinfStackValue,

            // Extended binary math (Value version)
            &&do_kAtan2fValue, &&do_kFmodfValue, &&do_kPowfValue, &&do_kMaxValue, &&do_kMaxfValue, &&do_kMinValue,
            &&do_kMinfValue,

            // Extended binary math (Value version) : non commutative operations
            &&do_kAtan2fValueInvert, &&do_kFmodfValueInvert, &&do_kPowfValueInvert,

            // Control
            &&do_kLoop, &&do_kReturn,

            // Select/if
            &&do_kIf, &&do_kSelectReal, &&do_kSelectInt, &&do_kCondBranch

        };

        int real_stack_index  = 0;
        int int_stack_index   = 0;
        int addr_stack_index  = 0;

        REAL          real_stack[512];
        int           int_stack[512];
        InstructionIT address_stack[64];
        
        memset(real_stack, 0, sizeof(REAL)*512);
        memset(int_stack, 0, sizeof(int)*512);
        memset(address_stack, 0, sizeof(InstructionIT)*64);

#define dispatchFirstScal()                   \
    {                                         \
        goto *fDispatchTable[(*it)->fOpcode]; \
    }
#define dispatchNextScal()                    \
    {                                         \
        if (TRACE >= 4) {     \
            traceInstruction(it, int_stack[int_stack_index], real_stack[real_stack_index]); \
        }                                     \
        it++;                                 \
        dispatchFirstScal();                  \
    }

#define dispatchBranch1Scal()                        \
    {                                                \
        it = (*it)->fBranch1->fInstructions.begin(); \
        dispatchFirstScal();                         \
    }
#define dispatchBranch2Scal()                        \
    {                                                \
        it = (*it)->fBranch2->fInstructions.begin(); \
        dispatchFirstScal();                         \
    }

#define pushBranch1Scal()                                  \
    {                                                      \
        pushAddr_((*it)->fBranch1->fInstructions.begin()); \
    }
#define pushBranch2Scal()                                  \
    {                                                      \
        pushAddr_((*it)->fBranch2->fInstructions.begin()); \
    }

#define dispatchReturnScal() \
    {                        \
        it = popAddr_();     \
        dispatchFirstScal(); \
    }
#define saveReturnScal()   \
    {                      \
        pushAddr_(it + 1); \
    }
#define emptyReturnScal() (addr_stack_index == 0)

        if (TRACE > 0) {
            // Check block coherency
            block->check();
        }

        InstructionIT it = block->fInstructions.begin();
        dispatchFirstScal();

    // Number operations
    do_kRealValue: {
        pushReal(it, (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kInt32Value: {
        pushInt((*it)->fIntValue);
        dispatchNextScal();
    }

    // Memory operations
    do_kLoadSoundFieldInt: {
        faustassert(this->fSoundTable.find((*it)->fName) != this->fSoundTable.end());
        Soundfile* sf = this->fSoundTable[(*it)->fName];
        int field_index = popInt();
        int part = popInt();
        int* field = nullptr;
        switch (field_index) {
            case Soundfile::kLength: {
                field = sf->fLength;
                break;
            }
            case Soundfile::kSR: {
                field = sf->fSR;
                break;
            }
            case Soundfile::kOffset: {
                field = sf->fOffset;
                break;
            }
            default:
                faustassert(false);
                break;
        }
        pushInt(field[part]);
        dispatchNextScal();
    }
    
    do_kLoadSoundFieldReal: {
        faustassert(this->fSoundTable.find((*it)->fName) != this->fSoundTable.end());
        Soundfile* sf = this->fSoundTable[(*it)->fName];
        // field_index (unused)
        popInt();
        int chan = popInt();
        int offset = popInt();
        REAL* buffer = reinterpret_cast<REAL**>(sf->fBuffers)[chan];
        pushReal(it, buffer[offset]);
        dispatchNextScal();
    }
    
    do_kLoadReal: {
        if (TRACE > 0) {
            pushReal(it, fRealHeap[assertLoadRealHeap(it, (*it)->fOffset1)]);
        } else {
            pushReal(it, fRealHeap[(*it)->fOffset1]);
        }
        dispatchNextScal();
    }
    
    do_kLoadInt: {
        if (TRACE > 0) {
            pushInt(fIntHeap[assertLoadIntHeap(it, (*it)->fOffset1)]);
        } else {
            pushInt(fIntHeap[(*it)->fOffset1]);
        }
        dispatchNextScal();
    }

    do_kStoreReal: {
        if (TRACE > 0) {
            fRealHeap[assertStoreRealHeap(it, (*it)->fOffset1)] = popReal(it);
        } else {
            fRealHeap[(*it)->fOffset1] = popReal(it);
        }
        dispatchNextScal();
    }

    do_kStoreInt: {
        if (TRACE > 0) {
            fIntHeap[assertStoreIntHeap(it, (*it)->fOffset1)] = popInt();
        } else {
            fIntHeap[(*it)->fOffset1] = popInt();
        }
        dispatchNextScal();
    }

    // Directly store a value
    do_kStoreRealValue: {
        if (TRACE > 0) {
            fRealHeap[assertStoreRealHeap(it, (*it)->fOffset1)] = (*it)->fRealValue;
        } else {
            fRealHeap[(*it)->fOffset1] = (*it)->fRealValue;
        }
        dispatchNextScal();
    }

    do_kStoreIntValue: {
        if (TRACE > 0) {
            fIntHeap[assertStoreIntHeap(it, (*it)->fOffset1)] = (*it)->fIntValue;
        } else {
            fIntHeap[(*it)->fOffset1] = (*it)->fIntValue;
        }
        dispatchNextScal();
    }

    do_kLoadIndexedReal: {
        int offset = popInt();
        if (TRACE > 0) {
            pushReal(it, fRealHeap[assertLoadRealHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)]);
        } else {
            pushReal(it, fRealHeap[(*it)->fOffset1 + offset]);
        }
        dispatchNextScal();
    }

    do_kLoadIndexedInt: {
        int offset = popInt();
        if (TRACE > 0) {
            pushInt(fIntHeap[assertLoadIntHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)]);
        } else {
            pushInt(fIntHeap[(*it)->fOffset1 + offset]);
        }
        dispatchNextScal();
    }

    do_kStoreIndexedReal: {
        int offset = popInt();
        if (TRACE > 0) {
            fRealHeap[assertStoreRealHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)] = popReal(it);
        } else {
            fRealHeap[(*it)->fOffset1 + offset] = popReal(it);
        }
        dispatchNextScal();
    }

    do_kStoreIndexedInt: {
        int offset = popInt();
        if (TRACE > 0) {
            fIntHeap[assertStoreIntHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)] = popInt();
        } else {
            fIntHeap[(*it)->fOffset1 + offset] = popInt();
        }
        dispatchNextScal();
    }

    do_kBlockStoreReal: {
        FIRBlockStoreRealInstruction<REAL>* inst = static_cast<FIRBlockStoreRealInstruction<REAL>*>(*it);
        assertInterp(inst);
        for (int i = 0; i < inst->fOffset2; i++) {
            fRealHeap[inst->fOffset1 + i] = inst->fNumTable[i];
        }
        dispatchNextScal();
    }

    do_kBlockStoreInt: {
        FIRBlockStoreIntInstruction<REAL>* inst = static_cast<FIRBlockStoreIntInstruction<REAL>*>(*it);
        assertInterp(inst);
        for (int i = 0; i < inst->fOffset2; i++) {
            fIntHeap[inst->fOffset1 + i] = inst->fNumTable[i];
        }
        dispatchNextScal();
    }

    do_kMoveReal: {
        fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset2];
        dispatchNextScal();
    }

    do_kMoveInt: {
        fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset2];
        dispatchNextScal();
    }

    do_kPairMoveReal: {
        fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset1 - 1];
        fRealHeap[(*it)->fOffset2] = fRealHeap[(*it)->fOffset2 - 1];
        dispatchNextScal();
    }

    do_kPairMoveInt: {
        fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset1 - 1];
        fIntHeap[(*it)->fOffset2] = fIntHeap[(*it)->fOffset2 - 1];
        dispatchNextScal();
    }

    do_kBlockPairMoveReal: {
        for (int i = (*it)->fOffset1; i < (*it)->fOffset2; i += 2) {
            fRealHeap[i + 1] = fRealHeap[i];
        }
        dispatchNextScal();
    }

    do_kBlockPairMoveInt: {
        for (int i = (*it)->fOffset1; i < (*it)->fOffset2; i += 2) {
            fIntHeap[i + 1] = fIntHeap[i];
        }
        dispatchNextScal();
    }

    do_kBlockShiftReal: {
        for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
            fRealHeap[i] = fRealHeap[i - 1];
        }
        dispatchNextScal();
    }

    do_kBlockShiftInt: {
        for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
            fIntHeap[i] = fIntHeap[i - 1];
        }
        dispatchNextScal();
    }

    // Input/output access
    do_kLoadInput: {
        if (TRACE > 0) {
            pushReal(it, fInputs[(*it)->fOffset1][assertAudioBuffer(it, popInt())]);
        } else {
            pushReal(it, fInputs[(*it)->fOffset1][popInt()]);
        }
        dispatchNextScal();
    }

    do_kStoreOutput: {
        if (TRACE > 0) {
            fOutputs[(*it)->fOffset1][assertAudioBuffer(it, popInt())] = popReal(it);
        } else {
            fOutputs[(*it)->fOffset1][popInt()] = popReal(it);
        }
        dispatchNextScal();
    }

    // Cast operations
    do_kCastReal: {
        pushReal(it, REAL(popInt()));
        dispatchNextScal();
    }

    do_kCastRealHeap: {
        pushReal(it, REAL(fIntHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kCastInt: {
        if (TRACE >= 3) {
            pushInt(int(checkCastIntOverflow(it, popReal(it))));
        } else {
            pushInt(int(popReal(it)));
        }
        dispatchNextScal();
    }

    do_kCastIntHeap: {
        if (TRACE >= 3) {
            pushInt(int(checkCastIntOverflow(it, fRealHeap[(*it)->fOffset1])));
        } else {
            pushInt(int(fRealHeap[(*it)->fOffset1]));
        }
        dispatchNextScal();
    }

    // Bitcast operations
    do_kBitcastInt: {
        REAL v1 = popReal(it);
        int  v2 = *reinterpret_cast<int*>(&v1);
        pushInt(v2);
        dispatchNextScal();
    }

    do_kBitcastReal: {
        int  v1 = popInt();
        REAL v2 = *reinterpret_cast<REAL*>(&v1);
        pushReal(it, v2);
        dispatchNextScal();
    }

        //-------------------------------------------------------
        // Standard math operations : 'stack' OP 'stack' version
        //-------------------------------------------------------

    do_kAddReal: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushReal(it, v1 + v2);
        dispatchNextScal();
    }

    do_kAddInt: {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            int res;
            if (__builtin_sadd_overflow(v1, v2, &res)) {
                warningOverflow(it, "kAddInt");
            }
            pushInt(res);
        } else {
            pushInt(v1 + v2);
        }
        dispatchNextScal();
    }

    do_kSubReal: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushReal(it, v1 - v2);
        dispatchNextScal();
    }

    do_kSubInt: {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            int res;
            if (__builtin_ssub_overflow(v1, v2, &res)) {
                warningOverflow(it, "kSubInt");
            }
            pushInt(res);
        } else {
            pushInt(v1 - v2);
        }
        dispatchNextScal();
    }

    do_kMultReal: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushReal(it, v1 * v2);
        dispatchNextScal();
    }

    do_kMultInt: {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            int res;
            if (__builtin_smul_overflow(v1, v2, &res)) {
                warningOverflow(it, "kMultInt");
            }
            pushInt(res);
        } else {
            pushInt(v1 * v2);
        }
        dispatchNextScal();
    }

    do_kDivReal: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        if (TRACE > 0) {
            checkDivZero(it, v2);
        }
        pushReal(it, v1 / v2);
        dispatchNextScal();
    }

    do_kDivInt: {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            checkDivZero(it, v2);
        }
        pushInt(v1 / v2);
        dispatchNextScal();
    }

    do_kRemReal: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        if (TRACE > 0) {
            checkDivZero(it, v2);
        }
        pushReal(it, std::remainder(v1, v2));
        dispatchNextScal();
    }

    do_kRemInt: {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            checkDivZero(it, v2);
        }
        pushInt(v1 % v2);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshInt: {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            pushInt(v1 << warningBitshift(it, v2));
        } else {
            pushInt(v1 << v2);
        }
        dispatchNextScal();
    }

    do_kARshInt: {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            pushInt(v1 >> warningBitshift(it, v2));
        } else {
            pushInt(v1 >> v2);
        }
        dispatchNextScal();
    }
    
    do_kLRshInt: {
        // TODO
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            pushInt(v1 >> warningBitshift(it, v2));
        } else {
            pushInt(v1 >> v2);
        }
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTInt: {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 > v2);
        dispatchNextScal();
    }

    do_kLTInt: {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 < v2);
        dispatchNextScal();
    }

    do_kGEInt: {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 >= v2);
        dispatchNextScal();
    }

    do_kLEInt: {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 <= v2);
        dispatchNextScal();
    }

    do_kEQInt: {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 == v2);
        dispatchNextScal();
    }

    do_kNEInt: {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 != v2);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTReal: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushInt(v1 > v2);
        dispatchNextScal();
    }

    do_kLTReal: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushInt(v1 < v2);
        dispatchNextScal();
    }

    do_kGEReal: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushInt(v1 >= v2);
        dispatchNextScal();
    }

    do_kLEReal: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushInt(v1 <= v2);
        dispatchNextScal();
    }

    do_kEQReal: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushInt(v1 == v2);
        dispatchNextScal();
    }

    do_kNEReal: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushInt(v1 != v2);
        dispatchNextScal();
    }

    // Logical operations
    do_kANDInt: {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 & v2);
        dispatchNextScal();
    }

    do_kORInt: {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 | v2);
        dispatchNextScal();
    }

    do_kXORInt: {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 ^ v2);
        dispatchNextScal();
    }

        //-----------------------------------------------------
        // Standard math operations : 'heap' OP 'heap' version
        //-----------------------------------------------------

    do_kAddRealHeap: {
        pushReal(it, fRealHeap[(*it)->fOffset1] + fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kAddIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] + fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kSubRealHeap: {
        pushReal(it, fRealHeap[(*it)->fOffset1] - fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kSubIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] - fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kMultRealHeap: {
        pushReal(it, fRealHeap[(*it)->fOffset1] * fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kMultIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] * fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kDivRealHeap: {
        pushReal(it, fRealHeap[(*it)->fOffset1] / fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kDivIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] / fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kRemRealHeap: {
        pushReal(it, std::remainder(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kRemIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] % fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshIntHeap: {
        if (TRACE > 0) {
            pushInt(fIntHeap[(*it)->fOffset1] << warningBitshift(it, fIntHeap[(*it)->fOffset2]));
        } else {
            pushInt(fIntHeap[(*it)->fOffset1] << fIntHeap[(*it)->fOffset2]);
        }
        dispatchNextScal();
    }

    do_kARshIntHeap: {
        if (TRACE > 0) {
            pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, fIntHeap[(*it)->fOffset2]));
        } else {
            pushInt(fIntHeap[(*it)->fOffset1] >> fIntHeap[(*it)->fOffset2]);
        }
        dispatchNextScal();
    }
        
    do_kLRshIntHeap: {
        if (TRACE > 0) {
            pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, fIntHeap[(*it)->fOffset2]));
        } else {
            pushInt(fIntHeap[(*it)->fOffset1] >> fIntHeap[(*it)->fOffset2]);
        }
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] > fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kLTIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] < fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kGEIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] >= fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kLEIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] <= fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kEQIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] == fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kNEIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] != fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTRealHeap: {
        pushInt(fRealHeap[(*it)->fOffset1] > fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kLTRealHeap: {
        pushInt(fRealHeap[(*it)->fOffset1] < fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kGERealHeap: {
        pushInt(fRealHeap[(*it)->fOffset1] >= fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kLERealHeap: {
        pushInt(fRealHeap[(*it)->fOffset1] <= fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kEQRealHeap: {
        pushInt(fRealHeap[(*it)->fOffset1] == fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kNERealHeap: {
        pushInt(fRealHeap[(*it)->fOffset1] != fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    // Logical operations
    do_kANDIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] & fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kORIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] | fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kXORIntHeap: {
        pushInt(fIntHeap[(*it)->fOffset1] ^ fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

        //------------------------------------------------------
        // Standard math operations : 'stack' OP 'heap' version
        //------------------------------------------------------

    do_kAddRealStack: {
        REAL v1 = popReal(it);
        pushReal(it, fRealHeap[(*it)->fOffset1] + v1);
        dispatchNextScal();
    }

    do_kAddIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] + v1);
        dispatchNextScal();
    }

    do_kSubRealStack: {
        REAL v1 = popReal(it);
        pushReal(it, fRealHeap[(*it)->fOffset1] - v1);
        dispatchNextScal();
    }

    do_kSubIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] - v1);
        dispatchNextScal();
    }

    do_kMultRealStack: {
        REAL v1 = popReal(it);
        pushReal(it, fRealHeap[(*it)->fOffset1] * v1);
        dispatchNextScal();
    }

    do_kMultIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] * v1);
        dispatchNextScal();
    }

    do_kDivRealStack: {
        REAL v1 = popReal(it);
        pushReal(it, fRealHeap[(*it)->fOffset1] / v1);
        dispatchNextScal();
    }

    do_kDivIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] / v1);
        dispatchNextScal();
    }

    do_kRemRealStack: {
        REAL v1 = popReal(it);
        pushReal(it, std::remainder(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kRemIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] % v1);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshIntStack: {
        int v1 = popInt();
        if (TRACE > 0) {
            pushInt(fIntHeap[(*it)->fOffset1] << warningBitshift(it, v1));
        } else {
            pushInt(fIntHeap[(*it)->fOffset1] << v1);
        }
        dispatchNextScal();
    }

    do_kARshIntStack: {
        int v1 = popInt();
        if (TRACE > 0) {
            pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, v1));
        } else {
            pushInt(fIntHeap[(*it)->fOffset1] >> v1);
        }
        dispatchNextScal();
    }
        
    do_kLRshIntStack: {
        // TODO
        int v1 = popInt();
        if (TRACE > 0) {
            pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, v1));
        } else {
            pushInt(fIntHeap[(*it)->fOffset1] >> v1);
        }
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] > v1);
        dispatchNextScal();
    }

    do_kLTIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] < v1);
        dispatchNextScal();
    }

    do_kGEIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] >= v1);
        dispatchNextScal();
    }

    do_kLEIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] <= v1);
        dispatchNextScal();
    }

    do_kEQIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] == v1);
        dispatchNextScal();
    }

    do_kNEIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] != v1);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTRealStack: {
        REAL v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] > v1);
        dispatchNextScal();
    }

    do_kLTRealStack: {
        REAL v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] < v1);
        dispatchNextScal();
    }

    do_kGERealStack: {
        REAL v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] >= v1);
        dispatchNextScal();
    }

    do_kLERealStack: {
        REAL v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] <= v1);
        dispatchNextScal();
    }

    do_kEQRealStack: {
        REAL v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] == v1);
        dispatchNextScal();
    }

    do_kNERealStack: {
        REAL v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] != v1);
        dispatchNextScal();
    }

    // Logical operations
    do_kANDIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] & v1);
        dispatchNextScal();
    }

    do_kORIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] | v1);
        dispatchNextScal();
    }

    do_kXORIntStack: {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] ^ v1);
        dispatchNextScal();
    }

        //-------------------------------------------------------
        // Standard math operations : 'stack' OP 'value' version
        //-------------------------------------------------------

    do_kAddRealStackValue: {
        REAL v1 = popReal(it);
        pushReal(it, (*it)->fRealValue + v1);
        dispatchNextScal();
    }

    do_kAddIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue + v1);
        dispatchNextScal();
    }

    do_kSubRealStackValue: {
        REAL v1 = popReal(it);
        pushReal(it, (*it)->fRealValue - v1);
        dispatchNextScal();
    }

    do_kSubIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue - v1);
        dispatchNextScal();
    }

    do_kMultRealStackValue: {
        REAL v1 = popReal(it);
        pushReal(it, (*it)->fRealValue * v1);
        dispatchNextScal();
    }

    do_kMultIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue * v1);
        dispatchNextScal();
    }

    do_kDivRealStackValue: {
        REAL v1 = popReal(it);
        pushReal(it, (*it)->fRealValue / v1);
        dispatchNextScal();
    }

    do_kDivIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue / v1);
        dispatchNextScal();
    }

    do_kRemRealStackValue: {
        REAL v1 = popReal(it);
        pushReal(it, std::remainder((*it)->fRealValue, v1));
        dispatchNextScal();
    }

    do_kRemIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue % v1);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshIntStackValue: {
        int v1 = popInt();
        if (TRACE > 0) {
            pushInt((*it)->fIntValue << warningBitshift(it, v1));
        } else {
            pushInt((*it)->fIntValue << v1);
        }
        dispatchNextScal();
    }

    do_kARshIntStackValue: {
        int v1 = popInt();
        if (TRACE > 0) {
            pushInt((*it)->fIntValue >> warningBitshift(it, v1));
        } else {
            pushInt((*it)->fIntValue >> v1);
        }
        dispatchNextScal();
    }
        
    do_kLRshIntStackValue: {
        int v1 = popInt();
        if (TRACE > 0) {
            pushInt((*it)->fIntValue >> warningBitshift(it, v1));
        } else {
            pushInt((*it)->fIntValue >> v1);
        }
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue > v1);
        dispatchNextScal();
    }

    do_kLTIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue < v1);
        dispatchNextScal();
    }

    do_kGEIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue >= v1);
        dispatchNextScal();
    }

    do_kLEIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue <= v1);
        dispatchNextScal();
    }

    do_kEQIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue == v1);
        dispatchNextScal();
    }

    do_kNEIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue != v1);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTRealStackValue: {
        REAL v1 = popReal(it);
        pushInt((*it)->fRealValue > v1);
        dispatchNextScal();
    }

    do_kLTRealStackValue: {
        REAL v1 = popReal(it);
        pushInt((*it)->fRealValue < v1);
        dispatchNextScal();
    }

    do_kGERealStackValue: {
        REAL v1 = popReal(it);
        pushInt((*it)->fRealValue >= v1);
        dispatchNextScal();
    }

    do_kLERealStackValue: {
        REAL v1 = popReal(it);
        pushInt((*it)->fRealValue <= v1);
        dispatchNextScal();
    }

    do_kEQRealStackValue: {
        REAL v1 = popReal(it);
        pushInt((*it)->fRealValue == v1);
        dispatchNextScal();
    }

    do_kNERealStackValue: {
        REAL v1 = popReal(it);
        pushInt((*it)->fRealValue != v1);
        dispatchNextScal();
    }

    // Logical operations
    do_kANDIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue & v1);
        dispatchNextScal();
    }

    do_kORIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue | v1);
        dispatchNextScal();
    }

    do_kXORIntStackValue: {
        int v1 = popInt();
        pushInt((*it)->fIntValue ^ v1);
        dispatchNextScal();
    }

        //------------------------------------------------------
        // Standard math operations : 'value' OP 'heap' version
        //------------------------------------------------------

    do_kAddRealValue: {
        pushReal(it, (*it)->fRealValue + fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kAddIntValue: {
        pushInt((*it)->fIntValue + fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kSubRealValue: {
        pushReal(it, (*it)->fRealValue - fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kSubIntValue: {
        pushInt((*it)->fIntValue - fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kMultRealValue: {
        pushReal(it, (*it)->fRealValue * fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kMultIntValue: {
        pushInt((*it)->fIntValue * fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kDivRealValue: {
        pushReal(it, (*it)->fRealValue / fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kDivIntValue: {
        pushInt((*it)->fIntValue / fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kRemRealValue: {
        pushReal(it, std::remainder((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kRemIntValue: {
        pushInt((*it)->fIntValue % fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshIntValue: {
        if (TRACE > 0) {
            pushInt((*it)->fIntValue << warningBitshift(it, fIntHeap[(*it)->fOffset1]));
        } else {
            pushInt((*it)->fIntValue << fIntHeap[(*it)->fOffset1]);
        }
        dispatchNextScal();
    }

    do_kARshIntValue: {
        if (TRACE > 0) {
            pushInt((*it)->fIntValue >> warningBitshift(it, fIntHeap[(*it)->fOffset1]));
        } else {
            pushInt((*it)->fIntValue >> fIntHeap[(*it)->fOffset1]);
        }
        dispatchNextScal();
    }
        
    do_kLRshIntValue: {
        if (TRACE > 0) {
            pushInt((*it)->fIntValue >> warningBitshift(it, fIntHeap[(*it)->fOffset1]));
        } else {
            pushInt((*it)->fIntValue >> fIntHeap[(*it)->fOffset1]);
        }
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTIntValue: {
        pushInt((*it)->fIntValue > fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kLTIntValue: {
        pushInt((*it)->fIntValue < fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kGEIntValue: {
        pushInt((*it)->fIntValue >= fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kLEIntValue: {
        pushInt((*it)->fIntValue <= fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kEQIntValue: {
        pushInt((*it)->fIntValue == fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kNEIntValue: {
        pushInt((*it)->fIntValue != fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTRealValue: {
        pushInt((*it)->fRealValue > fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kLTRealValue: {
        pushInt((*it)->fRealValue < fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kGERealValue: {
        pushInt((*it)->fRealValue >= fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kLERealValue: {
        pushInt((*it)->fRealValue <= fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kEQRealValue: {
        pushInt((*it)->fRealValue == fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kNERealValue: {
        pushInt((*it)->fRealValue != fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    // Logical operations
    do_kANDIntValue: {
        pushInt((*it)->fIntValue & fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kORIntValue: {
        pushInt((*it)->fIntValue | fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kXORIntValue: {
        pushInt((*it)->fIntValue ^ fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

        //----------------------------------------------------
        // Standard math operations : Value inverted version
        // (non commutative operations)
        //----------------------------------------------------

    do_kSubRealValueInvert: {
        pushReal(it, fRealHeap[(*it)->fOffset1] - (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kSubIntValueInvert: {
        pushInt(fIntHeap[(*it)->fOffset1] - (*it)->fIntValue);
        dispatchNextScal();
    }

    do_kDivRealValueInvert: {
        pushReal(it, fRealHeap[(*it)->fOffset1] / (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kDivIntValueInvert: {
        pushInt(fIntHeap[(*it)->fOffset1] / (*it)->fIntValue);
        dispatchNextScal();
    }

    do_kRemRealValueInvert: {
        pushReal(it, std::remainder(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
        dispatchNextScal();
    }

    do_kRemIntValueInvert: {
        pushInt(fIntHeap[(*it)->fOffset1] % (*it)->fIntValue);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshIntValueInvert: {
        if (TRACE > 0) {
            pushInt(fIntHeap[(*it)->fOffset1] << warningBitshift(it, (*it)->fIntValue));
        } else {
            pushInt(fIntHeap[(*it)->fOffset1] << (*it)->fIntValue);
        }
        dispatchNextScal();
    }

    do_kARshIntValueInvert: {
        if (TRACE > 0) {
            pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, (*it)->fIntValue));
        } else {
            pushInt(fIntHeap[(*it)->fOffset1] >> (*it)->fIntValue);
        }
        dispatchNextScal();
    }
        
    do_kLRshIntValueInvert: {
        if (TRACE > 0) {
            pushInt(fIntHeap[(*it)->fOffset1] >> warningBitshift(it, (*it)->fIntValue));
        } else {
            pushInt(fIntHeap[(*it)->fOffset1] >> (*it)->fIntValue);
        }
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTIntValueInvert: {
        pushInt(fIntHeap[(*it)->fOffset1] > (*it)->fIntValue);
        dispatchNextScal();
    }

    do_kLTIntValueInvert: {
        pushInt(fIntHeap[(*it)->fOffset1] < (*it)->fIntValue);
        dispatchNextScal();
    }

    do_kGEIntValueInvert: {
        pushInt(fIntHeap[(*it)->fOffset1] >= (*it)->fIntValue);
        dispatchNextScal();
    }

    do_kLEIntValueInvert: {
        pushInt(fIntHeap[(*it)->fOffset1] <= (*it)->fIntValue);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTRealValueInvert: {
        pushInt(fRealHeap[(*it)->fOffset1] > (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kLTRealValueInvert: {
        pushInt(fRealHeap[(*it)->fOffset1] < (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kGERealValueInvert: {
        pushInt(fRealHeap[(*it)->fOffset1] >= (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kLERealValueInvert: {
        pushInt(fRealHeap[(*it)->fOffset1] <= (*it)->fRealValue);
        dispatchNextScal();
    }

        //---------------------
        // Extended unary math
        //---------------------

    do_kAbs: {
        int v = popInt();
        pushInt(std::abs(v));
        dispatchNextScal();
    }

    do_kAbsf: {
        REAL v = popReal(it);
        pushReal(it, std::fabs(v));
        dispatchNextScal();
    }

    do_kAcosf: {
        REAL v = popReal(it);
        pushReal(it, std::acos(v));
        dispatchNextScal();
    }
        
    do_kAcoshf: {
        REAL v = popReal(it);
        pushReal(it, std::acosh(v));
        dispatchNextScal();
    }

    do_kAsinf: {
        REAL v = popReal(it);
        pushReal(it, std::asin(v));
        dispatchNextScal();
    }
        
    do_kAsinhf: {
        REAL v = popReal(it);
        pushReal(it, std::asinh(v));
        dispatchNextScal();
    }

    do_kAtanf: {
        REAL v = popReal(it);
        pushReal(it, std::atan(v));
        dispatchNextScal();
    }
        
    do_kAtanhf: {
        REAL v = popReal(it);
        pushReal(it, std::atanh(v));
        dispatchNextScal();
    }

    do_kCeilf: {
        REAL v = popReal(it);
        pushReal(it, std::ceil(v));
        dispatchNextScal();
    }

    do_kCosf: {
        REAL v = popReal(it);
        pushReal(it, std::cos(v));
        dispatchNextScal();
    }

    do_kCoshf: {
        REAL v = popReal(it);
        pushReal(it, std::cosh(v));
        dispatchNextScal();
    }

    do_kExpf: {
        REAL v = popReal(it);
        pushReal(it, std::exp(v));
        dispatchNextScal();
    }

    do_kFloorf: {
        REAL v = popReal(it);
        pushReal(it, std::floor(v));
        dispatchNextScal();
    }

    do_kLogf: {
        REAL v = popReal(it);
        pushReal(it, std::log(v));
        dispatchNextScal();
    }

    do_kLog10f: {
        REAL v = popReal(it);
        pushReal(it, std::log10(v));
        dispatchNextScal();
    }
        
    do_kRintf: {
        REAL v = popReal(it);
        pushReal(it, std::rint(v));
        dispatchNextScal();
    }

    do_kRoundf: {
        REAL v = popReal(it);
        pushReal(it, std::round(v));
        dispatchNextScal();
    }

    do_kSinf: {
        REAL v = popReal(it);
        pushReal(it, std::sin(v));
        dispatchNextScal();
    }

    do_kSinhf: {
        REAL v = popReal(it);
        pushReal(it, std::sinh(v));
        dispatchNextScal();
    }

    do_kSqrtf: {
        REAL v = popReal(it);
        pushReal(it, std::sqrt(v));
        dispatchNextScal();
    }

    do_kTanf: {
        REAL v = popReal(it);
        pushReal(it, std::tan(v));
        dispatchNextScal();
    }

    do_kTanhf: {
        REAL v = popReal(it);
        pushReal(it, std::tanh(v));
        dispatchNextScal();
    }
        
    do_kIsnanf: {
        REAL v = popReal(it);
        pushInt(std::isnan(v));
        dispatchNextScal();
    }
    
    do_kIsinff: {
        REAL v = popReal(it);
        pushInt(std::isinf(v));
        dispatchNextScal();
    }
  
        //------------------------------------
        // Extended unary math (heap version)
        ///-----------------------------------

    do_kAbsHeap: {
        pushInt(std::abs(fIntHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kAbsfHeap: {
        pushReal(it, std::fabs(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kAcosfHeap: {
        pushReal(it, std::acos(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }
        
    do_kAcoshfHeap: {
        pushReal(it, std::acosh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kAsinfHeap: {
        pushReal(it, std::asin(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }
        
    do_kAsinhfHeap: {
        pushReal(it, std::asinh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kAtanfHeap: {
        pushReal(it, std::atan(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }
        
    do_kAtanhfHeap: {
        pushReal(it, std::atanh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kCeilfHeap: {
        pushReal(it, std::ceil(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kCosfHeap: {
        pushReal(it, std::cos(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kCoshfHeap: {
        pushReal(it, std::cosh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kExpfHeap: {
        pushReal(it, std::exp(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kFloorfHeap: {
        pushReal(it, std::floor(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kLogfHeap: {
        pushReal(it, std::log(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kLog10fHeap: {
        pushReal(it, std::log10(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }
        
    do_kRintfHeap: {
        pushReal(it, std::rint(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }
   
    do_kRoundfHeap: {
        pushReal(it, std::round(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kSinfHeap: {
        pushReal(it, std::sin(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kSinhfHeap: {
        pushReal(it, std::sinh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kSqrtfHeap: {
        pushReal(it, std::sqrt(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kTanfHeap: {
        pushReal(it, std::tan(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kTanhfHeap: {
        pushReal(it, std::tanh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

        //----------------------
        // Extended binary math
        //----------------------

    do_kAtan2f: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushReal(it, std::atan2(v1, v2));
        dispatchNextScal();
    }

    do_kFmodf: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushReal(it, std::fmod(v1, v2));
        dispatchNextScal();
    }

    do_kPowf: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushReal(it, std::pow(v1, v2));
        dispatchNextScal();
    }

    do_kMax: {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(std::max(v1, v2));
        dispatchNextScal();
    }

    do_kMaxf: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushReal(it, std::max(v1, v2));
        dispatchNextScal();
    }

    do_kMin: {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(std::min(v1, v2));
        dispatchNextScal();
    }

    do_kMinf: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushReal(it, std::min(v1, v2));
        dispatchNextScal();
    }
        
    do_kCopysignf: {
        REAL v1 = popReal(it);
        REAL v2 = popReal(it);
        pushReal(it, std::copysign(v1, v2));
        dispatchNextScal();
    }
        
        //-------------------------------------
        // Extended binary math (heap version)
        //-------------------------------------

    do_kAtan2fHeap: {
        pushReal(it, std::atan2(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kFmodfHeap: {
        pushReal(it, std::fmod(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kPowfHeap: {
        pushReal(it, std::pow(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kMaxHeap: {
        pushInt(std::max(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kMaxfHeap: {
        pushReal(it, std::max(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kMinHeap: {
        pushInt(std::min(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kMinfHeap: {
        pushReal(it, std::min(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

        //--------------------------------------
        // Extended binary math (stack version)
        //--------------------------------------

    do_kAtan2fStack: {
        REAL v1 = popReal(it);
        pushReal(it, std::atan2(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kFmodfStack: {
        REAL v1 = popReal(it);
        pushReal(it, std::fmod(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kPowfStack: {
        REAL v1 = popReal(it);
        pushReal(it, std::pow(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kMaxStack: {
        int v1 = popInt();
        pushInt(std::max(fIntHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kMaxfStack: {
        REAL v1 = popReal(it);
        pushReal(it, std::max(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kMinStack: {
        int v1 = popInt();
        pushInt(std::min(fIntHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kMinfStack: {
        REAL v1 = popReal(it);
        pushReal(it, std::min(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

        //--------------------------------------------
        // Extended binary math (stack/value version)
        //--------------------------------------------

    do_kAtan2fStackValue: {
        REAL v1 = popReal(it);
        pushReal(it, std::atan2((*it)->fRealValue, v1));
        dispatchNextScal();
    }

    do_kFmodfStackValue: {
        REAL v1 = popReal(it);
        pushReal(it, std::fmod((*it)->fRealValue, v1));
        dispatchNextScal();
    }

    do_kPowfStackValue: {
        REAL v1 = popReal(it);
        pushReal(it, std::pow((*it)->fRealValue, v1));
        dispatchNextScal();
    }

    do_kMaxStackValue: {
        int v1 = popInt();
        pushInt(std::max((*it)->fIntValue, v1));
        dispatchNextScal();
    }

    do_kMaxfStackValue: {
        REAL v1 = popReal(it);
        pushReal(it, std::max((*it)->fRealValue, v1));
        dispatchNextScal();
    }

    do_kMinStackValue: {
        int v1 = popInt();
        pushInt(std::min((*it)->fIntValue, v1));
        dispatchNextScal();
    }

    do_kMinfStackValue: {
        REAL v1 = popReal(it);
        pushReal(it, std::min((*it)->fRealValue, v1));
        dispatchNextScal();
    }

        //-------------------------------------
        // Extended binary math (Value version)
        //-------------------------------------

    do_kAtan2fValue: {
        pushReal(it, std::atan2((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kFmodfValue: {
        pushReal(it, std::fmod((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kPowfValue: {
        pushReal(it, std::pow((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kMaxValue: {
        pushInt(std::max((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kMaxfValue: {
        pushReal(it, std::max((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kMinValue: {
        pushInt(std::min((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kMinfValue: {
        pushReal(it, std::min((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

        //-------------------------------------------------------------------
        // Extended binary math (Value version) : non commutative operations
        //-------------------------------------------------------------------

    do_kAtan2fValueInvert: {
        pushReal(it, std::atan2(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
        dispatchNextScal();
    }

    do_kFmodfValueInvert: {
        pushReal(it, std::fmod(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
        dispatchNextScal();
    }

    do_kPowfValueInvert: {
        pushReal(it, std::pow(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
        dispatchNextScal();
    }

        //---------
        // Control
        //---------

    do_kReturn: {
        // Empty addr stack = end of computation
        if (emptyReturnScal()) {
            goto end;
        } else {
            dispatchReturnScal();
        }
    }

    do_kIf: {
        // Keep next instruction
        saveReturnScal();

        if (popInt()) {
            // Execute new block
            assertInterp((*it)->fBranch1);
            dispatchBranch1Scal();
            // No value (If)
        } else {
            // Execute new block
            assertInterp((*it)->fBranch2);
            dispatchBranch2Scal();
            // No value (If)
        }
    }

    do_kSelectReal: {
        // Keep next instruction
        saveReturnScal();

        if (popInt()) {
            // Execute new block
            assertInterp((*it)->fBranch1);
            dispatchBranch1Scal();
            // Real value
        } else {
            // Execute new block
            assertInterp((*it)->fBranch2);
            dispatchBranch2Scal();
            // Real value
        }
    }

    do_kSelectInt: {
        // Keep next instruction
        saveReturnScal();

        if (popInt()) {
            // Execute new block
            assertInterp((*it)->fBranch1);
            dispatchBranch1Scal();
            // Int value
        } else {
            // Execute new block
            assertInterp((*it)->fBranch2);
            dispatchBranch2Scal();
            // Int value
        }
    }

    do_kCondBranch: {
        // If condition is true, just branch back on the block beginning
        if (popInt()) {
            assertInterp((*it)->fBranch1);
            dispatchBranch1Scal();
        } else {
            // Just continue after 'loop block' (do the final 'return')
            dispatchNextScal();
        }
    }

    do_kLoop: {
        // Keep next instruction
        saveReturnScal();

        // Push branch2 (loop content)
        assertInterp((*it)->fBranch2);
        pushBranch2Scal();

        // And start branch1 loop variable declaration block
        assertInterp((*it)->fBranch1);
        dispatchBranch1Scal();
    }

    end:
        // Check stack coherency
        assertInterp(real_stack_index == 0 && int_stack_index == 0);
    }
#endif
    
    
    inline bool startWith(const std::string& str, const std::string& prefix)
    {
        return (str.substr(0, prefix.size()) == prefix);
    }
    
    void buildMemoryMap(FBCBlockInstruction<REAL>* block,
                        std::map<int, std::pair<int, std::string>>& memory_map,
                        std::vector<std::string> mem_opcodes)
    {
        if (!block) return;
        for (const auto& it : block->fInstructions) {
            for (const auto& mem_opcode : mem_opcodes) {
                if (startWith(gFBCInstructionTable[it->fOpcode], mem_opcode)) {
                    memory_map[it->fOffset1] = std::make_pair(it->fOffset2, it->fName);
                    break;
                }
            }
            buildMemoryMap(it->getBranch1(), memory_map, mem_opcodes);
            buildMemoryMap(it->getBranch2(), memory_map, mem_opcodes);
        }
    }

   public:
    FBCInterpreter(interpreter_dsp_factory_aux<REAL, TRACE>* factory)
    {
        /*
        std::cout << "FBCInterpreter :"
                << " int_heap_size " << int_heap_size
                << " real_heap_size " << real_heap_size
                << " sr_offset " << sr_offset
                << " count_offset " << count_offset << std::endl;
        */

        fFactory = factory;
   
        if (fFactory->getMemoryManager()) {
            fRealHeap  = static_cast<REAL*>(fFactory->allocate(sizeof(REAL) * fFactory->fRealHeapSize));
            fIntHeap   = static_cast<int*>(fFactory->allocate(sizeof(REAL) * fFactory->fIntHeapSize));
            fInputs    = static_cast<REAL**>(fFactory->allocate(sizeof(REAL*) * fFactory->fNumInputs));
            fOutputs   = static_cast<REAL**>(fFactory->allocate(sizeof(REAL*) * fFactory->fNumOutputs));
        } else {
            fRealHeap  = new REAL[fFactory->fRealHeapSize];
            fIntHeap   = new int[fFactory->fIntHeapSize];
            fInputs    = new REAL*[fFactory->fNumInputs];
            fOutputs   = new REAL*[fFactory->fNumOutputs];
        }

        // std::cout << "==== FBCInterpreter ==== " << std::endl;
        // std::cout << "fRealHeapSize = " << fFactory->fRealHeapSize << std::endl;
        // std::cout << "fIntHeapSize = " << fFactory->fIntHeapSize << std::endl;

        // Initialise HEAP with special values to detect incorrect Load access
        for (int i = 0; i < fFactory->fRealHeapSize; i++) {
            fRealHeap[i] = REAL(DUMMY_REAL);
        }
        for (int i = 0; i < fFactory->fIntHeapSize; i++) {
            fIntHeap[i] = DUMMY_INT;
        }

        fRealStats[INTEGER_OVERFLOW]  = 0;
        fRealStats[DIV_BY_ZERO_REAL]  = 0;
        fRealStats[DIV_BY_ZERO_INT]   = 0;
        fRealStats[FP_INFINITE]       = 0;
        fRealStats[FP_NAN]            = 0;
        fRealStats[FP_SUBNORMAL]      = 0;
        fRealStats[CAST_INT_OVERFLOW] = 0;
        fRealStats[NEGATIVE_BITSHIFT] = 0;
    }

    virtual ~FBCInterpreter()
    {
        for (const auto& it : fPathInputTable) {
            delete it.second;
        }
        for (const auto& it : fPathOutputTable) {
            delete it.second;
        }
        if (fFactory->getMemoryManager()) {
            fFactory->destroy(fRealHeap);
            fFactory->destroy(fIntHeap);
            fFactory->destroy(fInputs);
            fFactory->destroy(fOutputs);
        } else {
            delete[] fRealHeap;
            delete[] fIntHeap;
            delete[] fInputs;
            delete[] fOutputs;
        }
        if (TRACE > 0) {
            printStats();
        }
    }

    void dumpMemory(std::vector<FBCBlockInstruction<REAL>*> blocks,
                    const std::string& name,
                    const std::string& filename)
    {
        std::ofstream out(filename);
        out << "DSP name: " << name << std::endl;
    
        // Built <index, field> real map
        std::map<int, std::pair<int, std::string>> memory_map_real;
        for (const auto& it : blocks) {
            buildMemoryMap(it, memory_map_real, {"kLoadReal", "kStoreReal", "kLoadIndexedReal", "kStoreIndexedReal"});
        }
        out << "=================================" << std::endl;
        out << "REAL memory: " << fFactory->fRealHeapSize << std::endl;
        for (int i = 0; i < fFactory->fRealHeapSize;) {
            // out << "mem: " << i << " " << fRealHeap[i] << " " << memory_map[i] << std::endl;
            if (memory_map_real[i].first > 0) {
                // Array
                int j = 0;
                for (j = 0; j < memory_map_real[i].first; j++) {
                    out << i+j << " " << memory_map_real[i].second << "[" << j << "] " << fRealHeap[i+j] << std::endl;
                }
                i += j;
            } else {
                // Scalar
                out << i << " " << memory_map_real[i].second << " " << fRealHeap[i] << std::endl;
                i++;
            }
        }
    
        // Built <index, field> int map
        std::map<int, std::pair<int, std::string>> memory_map_int;
        for (const auto& it : blocks) {
            buildMemoryMap(it, memory_map_int, {"kLoadInt", "kStoreInt", "kLoadIndexedInt", "kStoreIndexedInt"});
        }
        out << "=================================" << std::endl;
        out << "INT memory: " << fFactory->fIntHeapSize << std::endl;
        for (int i = 0; i < fFactory->fIntHeapSize;) {
            if (memory_map_int[i].first > 0) {
                // Array
                int j = 0;
                for (j = 0; j < memory_map_int[i].first; j++) {
                    out << i+j << " " << memory_map_int[i].second << "[" << j << "] " << fIntHeap[i+j] << std::endl;
                }
                i += j;
            } else {
                // Scalar
                out << i << " " << memory_map_int[i].second << " " << fIntHeap[i] << std::endl;
                i++;
            }
        }
    }

    void setIntValue(int offset, int value) { fIntHeap[offset] = value; }
    int  getIntValue(int offset) { return fIntHeap[offset]; }

    virtual void setInput(int input, REAL* buffer) { fInputs[input] = buffer; }
    virtual void setOutput(int output, REAL* buffer) { fOutputs[output] = buffer; }
};

#endif
