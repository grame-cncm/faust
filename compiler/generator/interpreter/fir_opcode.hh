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
    
        // End operation
        kHalt = 0,
        
        // Numbers
        kRealValue, kIntValue,
        
        // Memory
        kLoadReal, kLoadInt, 
        kStoreReal, kStoreInt,
        kLoadIndexedReal, kLoadIndexedInt, 
        kStoreIndexedReal, kStoreIndexedInt,
        kMoveReal, kMoveInt,
        kLoadInput, kStoreOutput,
        
        // Cast
        kCastReal, kCastInt,
        kCastRealHeap, kCastIntHeap,
        
        // Select/if
        kSelectInt, kSelectReal, kIf,
        
        // Standard math
        kAddReal, kAddInt, kSubReal, kSubInt,  
        kMultReal, kMultInt, kDivReal, kDivInt,
        kRemReal, kRemInt, kLshInt, kRshInt, kGTInt, 
        kLTInt, kGEInt, kLEInt, kEQInt, kNEInt, 
        kGTReal, kLTReal, kGEReal, 
        kLEReal, kEQReal, kNEReal, 
        kANDInt, kORInt, kXORInt,
        
        // Standard math (heap version)
        kAddRealHeap, kAddIntHeap, kSubRealHeap, kSubIntHeap,
        kMultRealHeap, kMultIntHeap, kDivRealHeap, kDivIntHeap,
        kRemRealHeap, kRemIntHeap, kLshIntHeap, kRshIntHeap, kGTIntHeap,
        kLTIntHeap, kGEIntHeap, kLEIntHeap, kEQIntHeap, kNEIntHeap,
        kGTRealHeap, kLTRealHeap, kGERealHeap,
        kLERealHeap, kEQRealHeap, kNERealHeap,
        kANDIntHeap, kORIntHeap, kXORIntHeap,
        
        // Standard math (direct version)
        kAddRealDirect, kAddIntDirect, kSubRealDirect, kSubIntDirect,
        kMultRealDirect, kMultIntDirect, kDivRealDirect, kDivIntDirect,
        kRemRealDirect, kRemIntDirect, kLshIntDirect, kRshIntDirect, kGTIntDirect,
        kLTIntDirect, kGEIntDirect, kLEIntDirect, kEQIntDirect, kNEIntDirect,
        kGTRealDirect, kLTRealDirect, kGERealDirect,
        kLERealDirect, kEQRealDirect, kNERealDirect,
        kANDIntDirect, kORIntDirect, kXORIntDirect,
        
        // Standard math (direct version) : non commutative operations
        kSubRealDirectInvert, kSubIntDirectInvert,
        kDivRealDirectInvert, kDivIntDirectInvert,
        kRemRealDirectInvert, kRemIntDirectInvert,
        kLshIntDirectInvert, kRshIntDirectInvert,
        kGTIntDirectInvert, kLTIntDirectInvert,
        kGEIntDirectInvert, kLEIntDirectInvert,
        kGTRealDirectInvert, kLTRealDirectInvert,
        kGERealDirectInvert, kLERealDirectInvert,
      
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
        
        // Extended binary math
        kAtan2f,
        kFmodf,
        kPowf,
        kMax, kMaxf,
        kMin, kMinf,
        
        // Extended unary math (heap version)
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
        
        // Extended binary math (heap version)
        kAtan2fHeap,
        kFmodfHeap,
        kPowfHeap,
        kMaxHeap, kMaxfHeap,
        kMinHeap, kMinfHeap,
        
        // Extended binary math (direct version)
        kAtan2fDirect,
        kFmodfDirect,
        kPowfDirect,
        kMaxDirect, kMaxfDirect,
        kMinDirect, kMinfDirect,
        
        // Extended binary math (direct version) : non commutative operations
        kAtan2fDirectInvert,
        kFmodfDirectInvert,
        kPowfDirectInvert,
        
        // Control
        kLoop,
        
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
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2Direct;
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2DirectInvert;
    
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2Heap;
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2Direct;
    static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2DirectInvert;
    
    static bool isMath(Opcode opt) { return opt >= kAddReal && opt <= kXORInt; }
    static bool isExtendedUnaryMath(Opcode opt) { return opt >= kAbs && opt <= kTanhf; }
    static bool isExtendedBinaryMath(Opcode opt) { return opt >= kAtan2f && opt <= kMinf; }

};


static std::string gFIRInstructionTable[] = {
    
    // End operation
    "kHalt",

    // Numbers
    "kRealValue", "kIntValue",

    // Memory
    "kLoadReal", "kLoadInt", 
    "kStoreReal", "kStoreInt",
    "kLoadIndexedReal", "kLoadIndexedInt", 
    "kStoreIndexedReal", "kStoreIndexedInt",
    "kMoveReal", "kMoveInt",
    "kLoadInput", "kStoreOutput",

    // Cast
    "kCastReal", "kCastInt",
    "kCastRealHeap", "kCastIntHeap",

    // Select/if
    "kSelectInt", "kSelectReal", "kIf",

    // Standard math
    "kAddReal", "kAddInt", "kSubReal", "kSubInt",  
    "kMultReal", "kMultInt", "kDivReal", "kDivInt",
    "kRemReal", "kRemInt", "kLshInt", "kRshInt", "kGTInt", 
    "kLTInt", "kGEInt", "kLEInt", "kEQInt", "kNEInt", 
    "kGTReal", "kLTReal", "kGEReal", 
    "kLEReal", "kEQReal", "kNEReal", 
    "kANDInt", "kORInt", "kXORInt",
    
    // Standard math (heap version)
    "kAddRealHeap", "kAddIntHeap", "kSubRealHeap", "kSubIntHeap",
    "kMultRealHeap", "kMultIntHeap", "kDivRealHeap", "kDivIntHeap",
    "kRemRealHeap", "kRemIntHeap", "kLshIntHeap", "kRshIntHeap", "kGTIntHeap",
    "kLTIntHeap", "kGEIntHeap", "kLEIntHeap", "kEQIntHeap", "kNEIntHeap",
    "kGTRealHeap", "kLTRealHeap", "kGERealHeap",
    "kLERealHeap", "kEQRealHeap", "kNERealHeap",
    "kANDIntHeap", "kORIntHeap", "kXORIntHeap",
    
    // Standard math (direct version) : non commutative operations
    "kAddRealDirect", "kAddIntDirect", "kSubRealDirect", "kSubIntDirect",
    "kMultRealDirect", "kMultIntDirect", "kDivRealDirect", "kDivIntDirect",
    "kRemRealDirect", "kRemIntDirect", "kLshIntDirect", "kRshIntDirect", "kGTIntDirect",
    "kLTIntDirect", "kGEIntDirect", "kLEIntDirect", "kEQIntDirect", "kNEIntDirect",
    "kGTRealDirect", "kLTRealDirect", "kGERealDirect",
    "kLERealDirect", "kEQRealDirect", "kNERealDirect",
    "kANDIntDirect", "kORIntDirect", "kXORIntDirect",
    
    // Non commutatives operations
    "kSubRealDirectInvert", "kSubIntDirectInvert",
    "kDivRealDirectInvert", "kDivIntDirectInvert",
    "kRemRealDirectInvert", "kRemIntDirectInvert",
    "kLshIntDirectInvert", "kRshIntDirectInvert",
    "kGTIntDirectInvert", "kLTIntDirectInvert",
    "kLTIntDirectInvert", "kLEIntDirectInvert",
    "kGTRealDirectInvert", "kLTRealDirectInvert",
    "kGERealDirectInvert", "kLERealDirectInvert",
    
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
    
    // Extended binary math
    "kAtan2f",
    "kFmodf",
    "kPowf",
    "kMax", "kMaxf",
    "kMin", "kMinf",
    
    // Extended unary math (heap version)
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
    
    // Extended binary math (heap version)
    "kAtan2fHeap",
    "kFmodfHeap",
    "kPowfHeap",
    "kMaxHeap", "kMaxfHeap",
    "kMinHeap", "kMinfHeap",
    
    // Extended binary math (direct version)
    "kAtan2fDirect",
    "kFmodfDirect",
    "kPowfDirect",
    "kMaxDirect", "kMaxfDirect",
    "kMinDirect", "kMinfDirect",
    
    // Extended binary math (direct version) : non commutative operations
    "kAtan2fDirectInvert",
    "kFmodfDirectInvert",
    "kPowfDirectInvert",

    // Control
    "kLoop",

    // User Interface
    "kOpenVerticalBox", "kOpenHorizontalBox", "kOpenTabBox", "kCloseBox",
    "kAddButton", "kAddChecButton", 
    "kAddHorizontalSlider", "kAddVerticalSlider", "kAddNumEntry", 
    "kAddHorizontalBargraph", "kAddVerticalBargraph",
    "kDeclare"

};

#endif
