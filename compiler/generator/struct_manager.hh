/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#ifndef _STRUCT_MANAGER_H
#define _STRUCT_MANAGER_H

#include <string>
#include <map>

#include "instructions.hh"

// Describe a field memory location the the DSP structure
struct MemoryDesc {
    
    MemoryDesc(): fOffset(-1),
                fSize(-1),
                fType(Typed::kNoType)
    {}
    
    MemoryDesc(int offset, int size, Typed::VarType type):
        fOffset(offset),
        fSize(size),
        fType(type)
    {}
    
    int fOffset;
    int fSize;
    Typed::VarType fType;
};

/*
 Compute all fields addresses and DSP structure size
 */

struct StructMemoryInstVisitor : public DispatchVisitor {
    
    int fStructOffset;                      // Keep the offset in bytes of the structure
    map <string, MemoryDesc> fFieldTable;   // Table : field_name, { offset, size, type }
    
    StructMemoryInstVisitor():fStructOffset(0)
    {}
    
    // Return the index of a given field
    int getFieldOffset(const string& name)
    {
        return (fFieldTable.find(name) != fFieldTable.end()) ? fFieldTable[name].fOffset : -1;
    }
    
    // Return the DSP size in bytes
    int getStructSize() { return fStructOffset; }
    
    map <string, MemoryDesc>& getFieldTable() { return fFieldTable; }
    
    // Declarations
    virtual void visit(DeclareVarInst* inst)
    {
        //dump2FIR(inst);
        bool is_struct = (inst->fAddress->getAccess() & Address::kStruct) || (inst->fAddress->getAccess() & Address::kStaticStruct);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        
        if (array_typed && array_typed->fSize > 1) {
            if (is_struct) {
                fFieldTable[inst->fAddress->getName()] = MemoryDesc(fStructOffset, array_typed->fSize, array_typed->fType->getType());
                fStructOffset += (array_typed->fSize * audioSampleSize()); // Always use biggest size so that int/real access are correctly aligned
            } else {
                // Should never happen...
                faustassert(false);
            }
        } else {
            if (is_struct) {
                fFieldTable[inst->fAddress->getName()] = MemoryDesc(fStructOffset, 1, inst->fType->getType());
                fStructOffset += audioSampleSize(); // Always use biggest size so that int/real access are correctly aligned
            } else {
                // Local variables declared by [var_num, type] pairs
                faustassert(inst->fValue == nullptr);
            }
        }
    }
    
};

#endif
