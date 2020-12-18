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

#ifndef _STRUCT_MANAGER_H
#define _STRUCT_MANAGER_H

#include <string>
#include <utility>
#include <vector>

#include "instructions.hh"

// Describe a field memory location in the DSP structure
struct MemoryDesc {
    int fIndex;         // Field index
    int fOffset;        // Field offset in bytes in a mixed int/real zone
    int fIntOffset;     // Field offset in bytes in a separated int zone
    int fRealOffset;    // Field offset in bytes in a separated real zone
    int fSize;          // Field size in bytes

    Typed::VarType fType;

    MemoryDesc() : fIndex(-1), fOffset(-1), fIntOffset(-1), fRealOffset(-1), fSize(-1), fType(Typed::kNoType) {}

    MemoryDesc(int index, int offset, int size, Typed::VarType type)
    : fIndex(index), fOffset(offset), fIntOffset(-1), fRealOffset(-1), fSize(size), fType(type) {}
 
    MemoryDesc(int index, int offset, int int_offset, int read_offset, int size, Typed::VarType type)
    : fIndex(index), fOffset(offset), fIntOffset(int_offset), fRealOffset(read_offset), fSize(size), fType(type) {}
    
    Typed* getTyped()
    {
        if (fSize > 1) {
            return InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(fType), fSize);
        } else {
            return InstBuilder::genBasicTyped(fType);
        }
    }
};

/*
 Compute all field info, the DSP size, and separate 'int' and 'real' types
 */
struct StructInstVisitor : public DispatchVisitor {
    int        fStructIntOffset;    // Keep the int offset in bytes
    int        fStructRealOffset;   // Keep the real offset in bytes
    int        fFieldIndex;         // Keep the field index
    MemoryDesc fDefault;
    
    // Vector is used so that field names are ordered in 'getStructType'
    typedef vector<pair<string, MemoryDesc> > field_table_type;
    
    field_table_type fFieldTable;  // Table: field_name, { index, offset, size, type }
    
    StructInstVisitor() : fStructIntOffset(0), fStructRealOffset(0), fFieldIndex(0) {}
    
    // Check if the field name exists
    bool hasField(const string& name, Typed::VarType& type)
    {
        for (auto& field : fFieldTable) {
            if (field.first == name) {
                type = field.second.fType;
                return true;
            }
        }
        return false;
    }
    
    // Return the offset of a given field in bytes
    int getFieldOffset(const string& name)
    {
        for (auto& field : fFieldTable) {
            if (field.first == name) return field.second.fOffset;
        }
        std::cerr << "ERROR in getFieldOffset : " << name << std::endl;
        faustassert(false);
        return -1;
    }
    
    // Return the int offset of a given field in bytes
    int getFieldIntOffset(const string& name)
    {
        for (auto& field : fFieldTable) {
            if (field.first == name) return field.second.fIntOffset;
        }
        std::cerr << "ERROR in getFieldIntOffset : " << name << std::endl;
        faustassert(false);
        return -1;
    }
    
    // Return the real offset of a given field in bytes
    int getFieldRealOffset(const string& name)
    {
        for (auto& field : fFieldTable) {
            if (field.first == name) return field.second.fRealOffset;
        }
        std::cerr << "ERROR in getFieldRealOffset : " << name << std::endl;
        faustassert(false);
        return -1;
    }
    
    // Return the index of a given field
    int getFieldIndex(const string& name)
    {
        for (auto& field : fFieldTable) {
            if (field.first == name) return field.second.fIndex;
        }
        std::cerr << "ERROR in getFieldIndex : " << name << std::endl;
        faustassert(false);
        return -1;
    }
    
    // Return the memory description of a given field
    MemoryDesc& getMemoryDesc(const string& name)
    {
        for (auto& field : fFieldTable) {
            if (field.first == name) return field.second;
        }
        std::cerr << "ERROR in getMemoryDesc : " << name << std::endl;
        faustassert(false);
        return fDefault;
    }
    
    // Return the struct 'int' size in bytes
    int getStructIntSize() { return fStructIntOffset; }
    
    // Return the struct 'real' size in bytes
    int getStructRealSize() { return fStructRealOffset; }
    
    // Return the struct size in bytes
    int getStructSize() { return fStructIntOffset + fStructRealOffset; }
    
    field_table_type& getFieldTable() { return fFieldTable; }
    
    // Return the struct type
    DeclareStructTypeInst* getStructType(const string& name)
    {
        vector<NamedTyped*> dsp_type_fields;
        for (auto& field : fFieldTable) {
            // std::cout << "getStructType " << field.first << std::endl;
            dsp_type_fields.push_back(InstBuilder::genNamedTyped(field.first, field.second.getTyped()));
        }
        return InstBuilder::genDeclareStructTypeInst(InstBuilder::genStructTyped(name, dsp_type_fields));
    }
    
    // Declarations
    virtual void visit(DeclareVarInst* inst)
    {
        //dump2FIR(inst);
        string              name   = inst->fAddress->getName();
        Address::AccessType access = inst->fAddress->getAccess();
        
        bool        is_struct   = (access & Address::kStruct) || (access & Address::kStaticStruct);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        
        if (array_typed && array_typed->fSize > 1) {
            if (is_struct) {
                if (array_typed->fType->getType() == Typed::kInt32) {
                    fFieldTable.push_back(make_pair(name, MemoryDesc(fFieldIndex++,
                                                                     getStructSize(),
                                                                     getStructIntSize(),
                                                                     getStructRealSize(),
                                                                     array_typed->fSize,
                                                                     array_typed->fType->getType())));
                    fStructIntOffset += array_typed->getSize();
                } else {
                    fFieldTable.push_back(make_pair(name, MemoryDesc(fFieldIndex++,
                                                                     getStructSize(),
                                                                     getStructIntSize(),
                                                                     getStructRealSize(),
                                                                     array_typed->fSize,
                                                                     array_typed->fType->getType())));
                    fStructRealOffset += array_typed->getSize();
                }
            } else {
                // Should never happen...
                faustassert(false);
            }
        } else {
            if (is_struct) {
                if (inst->fType->getType() == Typed::kInt32) {
                    fFieldTable.push_back(make_pair(name, MemoryDesc(fFieldIndex++,
                                                                     getStructSize(),
                                                                     getStructIntSize(),
                                                                     getStructRealSize(),
                                                                     1, inst->fType->getType())));
                    fStructIntOffset += inst->fType->getSize();
                } else {
                    fFieldTable.push_back(make_pair(name, MemoryDesc(fFieldIndex++,
                                                                     getStructSize(),
                                                                     getStructIntSize(),
                                                                     getStructRealSize(),
                                                                     1, inst->fType->getType())));
                    fStructRealOffset += inst->fType->getSize();
                }
            } else {
                // Local variables declared by [var_num, type] pairs
                faustassert(inst->fValue == nullptr);
            }
        }
    }
    
};

#endif
