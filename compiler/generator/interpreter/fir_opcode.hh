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

// Interpreter

struct FIRInstruction {

    enum Opcode { 
    
        // Numbers
        kRealValue1, kRealValue2, kIntValue1, kIntValue2,  
        
        // Memory
        // 4
        kLoadReal1, kLoadReal2, kLoadInt1, kLoadInt2, 
        kStoreReal1, kStoreReal2, kStoreInt1, kStoreInt2,
        kLoadIndexedReal1, kLoadIndexedReal2, kLoadIndexedInt1, kLoadIndexedInt2, 
        kStoreIndexedReal1, kStoreIndexedReal2, kStoreIndexedInt1, kStoreIndexedInt2,
        // 20
        kLoadInput1, kLoadInput2, kStoreOutput1, kStoreOutput2,  
        
        // Cast
        kCastReal1, kCastReal2, kCastInt1, kCastInt2, 
        
        // Select/if
        kIfInt1, kIfInt2, kIfReal1, kIfReal2,
        
        // Standard math
        kAddReal1, kAddReal2, kAddInt1, kAddInt2, kSubReal1, kSubReal2, kSubInt1, kSubInt2, 
        kMultReal1, kMultReal2, kMultInt1, kMultInt2, kDivReal1, kDivReal2, kDivInt1, kDivInt2,
        kRemReal1, kRemReal2, kRemInt1, kRemInt2, kLshInt1, kLshInt2, kRshInt1, kRshInt2, kGTInt1, kGTInt2,
        kLTInt1, kLTInt2, kGEInt1, kGEInt2, kLEInt1, kLEInt2, kEQInt1, kEQInt2, kNEInt1, kNEInt2, 
        kGTReal1, kGTReal2, kLTReal1, kLTReal2, kGEReal1, kGEReal2, 
        kLEReal1, kLEReal2, kEQReal1, kEQReal2, kNEReal1, kNEReal2,
        kANDInt1, kANDInt2, kORInt1, kORInt2, kXORInt1, kXORInt2, 
        
        // Trigonometric
        kSin1, kSin2, kCos1, kCos2,
        
        // User Interface 
        kOpenVerticalBox, kOpenHorizontalBox, kOpenTabBox, kCloseBox,
        kAddButton, kAddCheckButton, 
        kAddHorizontalSlider, kAddVerticalSlider, kAddNumEntry, 
        kAddHorizontalBargraph, kAddVerticalBargraph,
        kDeclare,
        
        // Control
        kLoop
    };
     
};

#endif
