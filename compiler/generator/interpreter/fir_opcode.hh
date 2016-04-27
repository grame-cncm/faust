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

// Interpreter

struct FIRInstruction {

    enum Opcode { 
    
        // Halt
        kHalt = 0,
        
        // Numbers
        kRealValue, kIntValue,  // 2
        
        // Memory
        kLoadReal, kLoadInt, 
        kStoreReal, kStoreInt,
        kLoadIndexedReal, kLoadIndexedInt, 
        kStoreIndexedReal, kStoreIndexedInt,
        kLoadInput, kStoreOutput,  // 12
        
        // Cast
        kCastReal, kCastInt, // 14
        
        // Select/if
        kSelectInt, kSelectReal, kIf, // 17
        
        // Standard math
        kAddReal, kAddInt, kSubReal, kSubInt,  
        kMultReal, kMultInt, kDivReal, kDivInt,
        kRemReal, kRemInt, kLshInt, kRshInt, kGTInt, 
        kLTInt, kGEInt, kLEInt, kEQInt, kNEInt, 
        kGTReal, kLTReal, kGEReal, 
        kLEReal, kEQReal, kNEReal, 
        kANDInt, kORInt, kXORInt,  // 44
        
        // Math
        kSqrt,  // 45
        kSin, kCos, // 47
        
        // Control
        kLoop, // 48
        
        // User Interface 
        kOpenVerticalBox, kOpenHorizontalBox, kOpenTabBox, kCloseBox,
        kAddButton, kAddCheckButton, 
        kAddHorizontalSlider, kAddVerticalSlider, kAddNumEntry, 
        kAddHorizontalBargraph, kAddVerticalBargraph,
        kDeclare, // 60
        
    };
     
};

static std::string gFIRInstructionTable[] = {
                                            "kHalt",
    
                                            "kRealValue", "kIntValue",
    
                                            "kLoadReal", "kLoadInt", 
                                            "kStoreReal", "kStoreInt",
                                            "kLoadIndexedReal", "kLoadIndexedInt", 
                                            "kStoreIndexedReal", "kStoreIndexedInt",
                                            "kLoadInput", "kStoreOutput",  // 12
    
                                            "kCastReal", "kCastInt",
    
                                            "kSelectInt", "kSelectReal", "kIf", // 17
    
                                            "kAddReal", "kAddInt", "kSubReal", "kSubInt",  
                                            "kMultReal", "kMultInt", "kDivReal", "kDivInt",
                                            "kRemReal", "kRemInt", "kLshInt", "kRshInt", "kGTInt", 
                                            "kLTInt", "kGEInt", "kLEInt", "kEQInt", "kNEInt", 
                                            "kGTReal", "kLTReal", "kGEReal", 
                                            "kLEReal", "kEQReal", "kNEReal", 
                                            "kANDInt", "kORInt", "kXORInt", // 44
    
                                            "kSqrt",
                                            "kSin", "kCos", // 47
    
                                            "kLoop", // 48
    
                                            "kOpenVerticalBox", "kOpenHorizontalBox", "kOpenTabBox", "kCloseBox",
                                            "kAddButton", "kAddChecButton", 
                                            "kAddHorizontalSlider", "kAddVerticalSlider", "kAddNumEntry", 
                                            "kAddHorizontalBargraph", "kAddVerticalBargraph",
                                            "kDeclare"
    
                                        };

#endif
