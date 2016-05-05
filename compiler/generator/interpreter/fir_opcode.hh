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

#ifndef _FIR_OPCODE_H
#define _FIR_OPCODE_H

#include <string>
#include <map>

// Interpreter

struct FIRInstruction {

    enum Opcode { 
    
        // Numbers
        kRealValue, kIntValue,
        
        // Memory
        kLoadReal, kLoadInt,
        kStoreReal, kStoreInt,
        kStoreRealValue, kStoreIntValue,
        kLoadIndexedReal, kLoadIndexedInt,
        kStoreIndexedReal, kStoreIndexedInt,
        kMoveReal, kMoveInt,
        kLoadInput, kStoreOutput,
        
        // Cast
        kCastReal, kCastInt,
        kCastRealHeap, kCastIntHeap,
        
        // Standard math (stack OP stack)
        kAddReal, kAddInt, kSubReal, kSubInt,  
        kMultReal, kMultInt, kDivReal, kDivInt,
        kRemReal, kRemInt, kLshInt, kRshInt, kGTInt, 
        kLTInt, kGEInt, kLEInt, kEQInt, kNEInt, 
        kGTReal, kLTReal, kGEReal, 
        kLEReal, kEQReal, kNEReal, 
        kANDInt, kORInt, kXORInt,
        
        // Standard math (heap OP heap)
        kAddRealHeap, kAddIntHeap, kSubRealHeap, kSubIntHeap,
        kMultRealHeap, kMultIntHeap, kDivRealHeap, kDivIntHeap,
        kRemRealHeap, kRemIntHeap, kLshIntHeap, kRshIntHeap, kGTIntHeap,
        kLTIntHeap, kGEIntHeap, kLEIntHeap, kEQIntHeap, kNEIntHeap,
        kGTRealHeap, kLTRealHeap, kGERealHeap,
        kLERealHeap, kEQRealHeap, kNERealHeap,
        kANDIntHeap, kORIntHeap, kXORIntHeap,
        
        // Standard math (heap OP stack)
        kAddRealStack, kAddIntStack, kSubRealStack, kSubIntStack,
        kMultRealStack, kMultIntStack, kDivRealStack, kDivIntStack,
        kRemRealStack, kRemIntStack, kLshIntStack, kRshIntStack, kGTIntStack,
        kLTIntStack, kGEIntStack, kLEIntStack, kEQIntStack, kNEIntStack,
        kGTRealStack, kLTRealStack, kGERealStack,
        kLERealStack, kEQRealStack, kNERealStack,
        kANDIntStack, kORIntStack, kXORIntStack,
        
        // Standard math (heap OP stack)
        kAddRealStackValue, kAddIntStackValue, kSubRealStackValue, kSubIntStackValue,
        kMultRealStackValue, kMultIntStackValue, kDivRealStackValue, kDivIntStackValue,
        kRemRealStackValue, kRemIntStackValue, kLshIntStackValue, kRshIntStackValue, kGTIntStackValue,
        kLTIntStackValue, kGEIntStackValue, kLEIntStackValue, kEQIntStackValue, kNEIntStackValue,
        kGTRealStackValue, kLTRealStackValue, kGERealStackValue,
        kLERealStackValue, kEQRealStackValue, kNERealStackValue,
        kANDIntStackValue, kORIntStackValue, kXORIntStackValue,
        
        // Standard math (value OP heap)
        kAddRealValue, kAddIntValue, kSubRealValue, kSubIntValue,
        kMultRealValue, kMultIntValue, kDivRealValue, kDivIntValue,
        kRemRealValue, kRemIntValue, kLshIntValue, kRshIntValue, kGTIntValue,
        kLTIntValue, kGEIntValue, kLEIntValue, kEQIntValue, kNEIntValue,
        kGTRealValue, kLTRealValue, kGERealValue,
        kLERealValue, kEQRealValue, kNERealValue,
        kANDIntValue, kORIntValue, kXORIntValue,
        
        // Standard math (value OP heap) : non commutative operations
        kSubRealValueInvert, kSubIntValueInvert,
        kDivRealValueInvert, kDivIntValueInvert,
        kRemRealValueInvert, kRemIntValueInvert,
        kLshIntValueInvert, kRshIntValueInvert,
        kGTIntValueInvert, kLTIntValueInvert,
        kGEIntValueInvert, kLEIntValueInvert,
        kGTRealValueInvert, kLTRealValueInvert,
        kGERealValueInvert, kLERealValueInvert,
      
        // Extended unary math
        kAbs, kAbsf,
        kAcosf, kAsinf,
        kAtanf,
        kCeilf,
        kCosf, kCoshf,
        kExpf,
        kFloorf,
        kLogf, kLog10f,
        kRoundf,
        kSinf, kSinhf,
        kSqrtf,
        kTanf, kTanhf,
        
        // Extended unary math (heap OP)
        kAbsHeap, kAbsfHeap,
        kAcosfHeap, kAsinfHeap,
        kAtanfHeap,
        kCeilfHeap,
        kCosfHeap, kCoshfHeap,
        kExpfHeap,
        kFloorfHeap,
        kLogfHeap, kLog10fHeap,
        kRoundfHeap,
        kSinfHeap, kSinhfHeap,
        kSqrtfHeap,
        kTanfHeap, kTanhfHeap,
        
        // Extended binary math
        kAtan2f,
        kFmodf,
        kPowf,
        kMax, kMaxf,
        kMin, kMinf,
        
        // Extended binary math (heap OP heap)
        kAtan2fHeap,
        kFmodfHeap,
        kPowfHeap,
        kMaxHeap, kMaxfHeap,
        kMinHeap, kMinfHeap,
        
        // Extended binary math (heap OP stack)
        kAtan2fStack,
        kFmodfStack,
        kPowfStack,
        kMaxStack, kMaxfStack,
        kMinStack, kMinfStack,
   
        // Extended binary math (value OP stack)
        kAtan2fStackValue,
        kFmodfStackValue,
        kPowfStackValue,
        kMaxStackValue, kMaxfStackValue,
        kMinStackValue, kMinfStackValue,
        
        // Extended binary math (value OP heap)
        kAtan2fValue,
        kFmodfValue,
        kPowfValue,
        kMaxValue, kMaxfValue,
        kMinValue, kMinfValue,
        
        // Extended binary math (value OP heap) : non commutative operations
        kAtan2fValueInvert,
        kFmodfValueInvert,
        kPowfValueInvert,
        
        //==========
        // Control
        //==========
        kLoop,
        kReturn,
        
        // Select/if
        kIf,
        kCondBranch,
        
        // User Interface 
        kOpenVerticalBox, kOpenHorizontalBox, kOpenTabBox, kCloseBox,
        kAddButton, kAddCheckButton, 
        kAddHorizontalSlider, kAddVerticalSlider, kAddNumEntry, 
        kAddHorizontalBargraph, kAddVerticalBargraph,
        kDeclare,
    };
    
    virtual int size() { return 1; }
    
    virtual void stackMove(int& int_index, int& real_index) {}
    
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2Heap;
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2Stack;
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2StackValue;
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2Value;
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2ValueInvert;
    
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2Heap;
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2Stack;
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2StackValue;
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2Value;
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2ValueInvert;
    
    static bool isMath(Opcode opt) { return opt >= kAddReal && opt <= kXORInt; }
    static bool isExtendedUnaryMath(Opcode opt) { return opt >= kAbs && opt <= kTanhf; }
    static bool isExtendedBinaryMath(Opcode opt) { return opt >= kAtan2f && opt <= kMinf; }

};

static std::string gFIRInstructionTable[] = {
    
    // Numbers
    "kRealValue", "kIntValue",

    // Memory
    "kLoadReal", "kLoadInt", 
    "kStoreReal", "kStoreInt",
    "kStoreRealValue", "kStoreIntValue",
    "kLoadIndexedReal", "kLoadIndexedInt", 
    "kStoreIndexedReal", "kStoreIndexedInt",
    "kMoveReal", "kMoveInt",
    "kLoadInput", "kStoreOutput",

    // Cast
    "kCastReal", "kCastInt",
    "kCastRealHeap", "kCastIntHeap",

    // Standard math (stack OP stack)
    "kAddReal", "kAddInt", "kSubReal", "kSubInt",  
    "kMultReal", "kMultInt", "kDivReal", "kDivInt",
    "kRemReal", "kRemInt", "kLshInt", "kRshInt", "kGTInt", 
    "kLTInt", "kGEInt", "kLEInt", "kEQInt", "kNEInt", 
    "kGTReal", "kLTReal", "kGEReal", 
    "kLEReal", "kEQReal", "kNEReal", 
    "kANDInt", "kORInt", "kXORInt",
    
    // Standard math (heap OP heap)
    "kAddRealHeap", "kAddIntHeap", "kSubRealHeap", "kSubIntHeap",
    "kMultRealHeap", "kMultIntHeap", "kDivRealHeap", "kDivIntHeap",
    "kRemRealHeap", "kRemIntHeap", "kLshIntHeap", "kRshIntHeap", "kGTIntHeap",
    "kLTIntHeap", "kGEIntHeap", "kLEIntHeap", "kEQIntHeap", "kNEIntHeap",
    "kGTRealHeap", "kLTRealHeap", "kGERealHeap",
    "kLERealHeap", "kEQRealHeap", "kNERealHeap",
    "kANDIntHeap", "kORIntHeap", "kXORIntHeap",
    
    // Standard math (heap OP stack)
    "kAddRealStack", "kAddIntStack", "kSubRealStack", "kSubIntStack",
    "kMultRealStack", "kMultIntStack", "kDivRealStack", "kDivIntStack",
    "kRemRealStack", "kRemIntStack", "kLshIntStack", "kRshIntStack", "kGTIntStack",
    "kLTIntStack", "kGEIntStack", "kLEIntStack", "kEQIntStack", "kNEIntStack",
    "kGTRealStack", "kLTRealStack", "kGERealStack",
    "kLERealStack", "kEQRealStack", "kNERealStack",
    "kANDIntStack", "kORIntStack", "kXORIntStack",
    
    // Standard math (value OP stack)
    "kAddRealStackValue", "kAddIntStackValue", "kSubRealStackValue", "kSubIntStackValue",
    "kMultRealStackValue", "kMultIntStackValue", "kDivRealStackValue", "kDivIntStackValue",
    "kRemRealStackValue", "kRemIntStackValue", "kLshIntStackValue", "kRshIntStackValue", "kGTIntStackValue",
    "kLTIntStackValue", "kGEIntStackValue", "kLEIntStackValue", "kEQIntStackValue", "kNEIntStackValue",
    "kGTRealStackValue", "kLTRealStackValue", "kGERealStackValue",
    "kLERealStackValue", "kEQRealStackValue", "kNERealStackValue",
    "kANDIntStackValue", "kORIntStackValue", "kXORIntStackValue",
    
    // Standard math (value OP heap)
    "kAddRealValue", "kAddIntValue", "kSubRealValue", "kSubIntValue",
    "kMultRealValue", "kMultIntValue", "kDivRealValue", "kDivIntValue",
    "kRemRealValue", "kRemIntValue", "kLshIntValue", "kRshIntValue", "kGTIntValue",
    "kLTIntValue", "kGEIntValue", "kLEIntValue", "kEQIntValue", "kNEIntValue",
    "kGTRealValue", "kLTRealValue", "kGERealValue",
    "kLERealValue", "kEQRealValue", "kNERealValue",
    "kANDIntValue", "kORIntValue", "kXORIntValue",
    
    // Standard math (value OP heap) : non commutative operations
    "kSubRealValueInvert", "kSubIntValueInvert",
    "kDivRealValueInvert", "kDivIntValueInvert",
    "kRemRealValueInvert", "kRemIntValueInvert",
    "kLshIntValueInvert", "kRshIntValueInvert",
    "kGTIntValueInvert", "kLTIntValueInvert",
    "kLTIntValueInvert", "kLEIntValueInvert",
    "kGTRealValueInvert", "kLTRealValueInvert",
    "kGERealValueInvert", "kLERealValueInvert",
    
    // Extended unary math
    "kAbs", "kAbsf",
    "kAcosf", "kAsinf",
    "kAtanf",
    "kCeilf",
    "kCosf", "kCoshf",
    "kExpf",
    "kFloorf",
    "kLogf", "kLog10f",
    "kRoundf",
    "kSinf", "kSinhf",
    "kSqrtf",
    "kTanf", "kTanhf",
    
    // Extended unary math (heap OP heap)
    "kAbsHeap", "kAbsfHeap",
    "kAcosfHeap", "kAsinfHeap",
    "kAtanfHeap",
    "kCeilfHeap",
    "kCosfHeap", "kCoshfHeap",
    "kExpfHeap",
    "kFloorfHeap",
    "kLogfHeap", "kLog10fHeap",
    "kRoundfHeap",
    "kSinfHeap", "kSinhfHeap",
    "kSqrtfHeap",
    "kTanfHeap", "kTanhfHeap",
    
    // Extended binary math
    "kAtan2f",
    "kFmodf",
    "kPowf",
    "kMax", "kMaxf",
    "kMin", "kMinf",
    
    // Extended binary math (heap version)
    "kAtan2fHeap",
    "kFmodfHeap",
    "kPowfHeap",
    "kMaxHeap", "kMaxfHeap",
    "kMinHeap", "kMinfHeap",
    
    // Extended binary math (stack version)
    "kAtan2fStack",
    "kFmodfStack",
    "kPowfStack",
    "kMaxStack", "kMaxfStack",
    "kMinStack", "kMinfStack",
    
    // Extended binary math (Stack/Value version)
    "kAtan2fStackValue",
    "kFmodfStackValue",
    "kPowfStackValue",
    "kMaxStackValue", "kMaxStackfValue",
    "kMinStackValue", "kMinfStackValue",
    
    // Extended binary math (Value version)
    "kAtan2fValue",
    "kFmodfValue",
    "kPowfValue",
    "kMaxValue", "kMaxfValue",
    "kMinValue", "kMinfValue",
    
    // Extended binary math (Value version) : non commutative operations
    "kAtan2fValueInvert",
    "kFmodfValueInvert",
    "kPowfValueInvert",

    //==========
    // Control
    //==========
    
    "kLoop",
    "kReturn",
    
    // Select/if
    "kIf",
    "kCondBranch",
 
    // User Interface
    "kOpenVerticalBox", "kOpenHorizontalBox", "kOpenTabBox", "kCloseBox",
    "kAddButton", "kAddChecButton", 
    "kAddHorizontalSlider", "kAddVerticalSlider", "kAddNumEntry", 
    "kAddHorizontalBargraph", "kAddVerticalBargraph",
    "kDeclare"

};

#define INTERP_FILE_VERSION 0.50

#endif
