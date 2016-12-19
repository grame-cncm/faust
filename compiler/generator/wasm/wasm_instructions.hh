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

#ifndef _WASM_INSTRUCTIONS_H
#define _WASM_INSTRUCTIONS_H

#include <vector>
#include <cmath>
#include <string.h>

#include "was_instructions.hh"

using namespace std;

// Type punning needs to be done through this function to avoid undefined
// behavior: unions and reinterpret_cast aren't valid approaches.
template <class Destination, class Source>
inline Destination bit_cast(const Source& source)
{
    Destination destination;
    memcpy(&destination, &source, sizeof(destination));
    return destination;
}

template<typename T, typename MiniT>
struct LEB {

    T value;
    
    LEB() {}
    LEB(T value) : value(value) {}
    
    bool hasMore(T temp, MiniT byte)
    {
        // for signed, we must ensure the last bit has the right sign, as it will zero extend
        return std::is_signed<T>::value ? (temp != 0 && temp != -1) || (value >= 0 && (byte & 64)) || (value < 0 && !(byte & 64)) : (temp != 0);
    }
    
    void write(std::vector<uint8_t>* out)
    {
        T temp = value;
        bool more;
        do {
            uint8_t byte = temp & 127;
            temp >>= 7;
            more = hasMore(temp, byte);
            if (more) {
                byte = byte | 128;
            }
            out->push_back(byte);
        } while (more);
    }
    
    void writeAt(std::vector<uint8_t>* out, size_t at, size_t minimum = 0)
    {
        T temp = value;
        size_t offset = 0;
        bool more;
        do {
            uint8_t byte = temp & 127;
            temp >>= 7;
            more = hasMore(temp, byte) || offset + 1 < minimum;
            if (more) {
                byte = byte | 128;
            }
            (*out)[at + offset] = byte;
            offset++;
        } while (more);
    }
    
};

typedef LEB<uint32_t, uint8_t> U32LEB;
typedef LEB<uint64_t, uint8_t> U64LEB;
typedef LEB<int32_t, int8_t> S32LEB;
typedef LEB<int64_t, int8_t> S64LEB;

//
// We mostly stream into a buffer as we create the binary format, however,
// sometimes we need to backtrack and write to a location behind us - wasm
// is optimized for reading, not writing.
//
class BufferWithRandomAccess : public std::vector<uint8_t> {
    
    private:
        
        bool debug;
        
    public:
    
        BufferWithRandomAccess(bool debug = false) : debug(debug) {}
        
        BufferWithRandomAccess& operator<<(int8_t x)
        {
            if (debug) std::cerr << "writeInt8: " << (int)(uint8_t)x << " (at " << size() << ")" << std::endl;
            push_back(x);
            return *this;
        }
    
        BufferWithRandomAccess& operator<<(int16_t x)
        {
            if (debug) std::cerr << "writeInt16: " << x << " (at " << size() << ")" << std::endl;
            push_back(x & 0xff);
            push_back(x >> 8);
            return *this;
        }
    
        BufferWithRandomAccess& operator<<(int32_t x)
        {
            if (debug) std::cerr << "writeInt32: " << x << " (at " << size() << ")" << std::endl;
            push_back(x & 0xff); x >>= 8;
            push_back(x & 0xff); x >>= 8;
            push_back(x & 0xff); x >>= 8;
            push_back(x & 0xff);
            return *this;
        }
    
        BufferWithRandomAccess& operator<<(int64_t x)
        {
            if (debug) std::cerr << "writeInt64: " << x << " (at " << size() << ")" << std::endl;
            push_back(x & 0xff); x >>= 8;
            push_back(x & 0xff); x >>= 8;
            push_back(x & 0xff); x >>= 8;
            push_back(x & 0xff); x >>= 8;
            push_back(x & 0xff); x >>= 8;
            push_back(x & 0xff); x >>= 8;
            push_back(x & 0xff); x >>= 8;
            push_back(x & 0xff);
            return *this;
        }
    
        BufferWithRandomAccess& operator<<(U32LEB x)
        {
            size_t before = -1;
            if (debug) {
                before = size();
                std::cerr << "writeU32LEB: " << x.value << " (at " << before << ")" << std::endl;
            }
            x.write(this);
            if (debug) {
                for (size_t i = before; i < size(); i++) {
                    std::cerr << "  " << (int)at(i) << " (at " << i << ")\n";
                }
            }
            return *this;
        }
    
        BufferWithRandomAccess& operator<<(U64LEB x)
        {
            size_t before = -1;
            if (debug) {
                before = size();
                std::cerr << "writeU64LEB: " << x.value << " (at " << before << ")" << std::endl;
            }
            x.write(this);
            if (debug) {
                for (size_t i = before; i < size(); i++) {
                    std::cerr << "  " << (int)at(i) << " (at " << i << ")\n";
                }
            }
            return *this;
        }
    
        BufferWithRandomAccess& operator<<(S32LEB x)
        {
            size_t before = -1;
            if (debug) {
                before = size();
                std::cerr << "writeS32LEB: " << x.value << " (at " << before << ")" << std::endl;
            }
            x.write(this);
            if (debug) {
                for (size_t i = before; i < size(); i++) {
                    std::cerr << "  " << (int)at(i) << " (at " << i << ")\n";
                }
            }
            return *this;
        }
    
        BufferWithRandomAccess& operator<<(S64LEB x)
        {
            size_t before = -1;
            if (debug) {
                before = size();
                std::cerr << "writeS64LEB: " << x.value << " (at " << before << ")" << std::endl;
            }
            x.write(this);
            if (debug) {
                for (size_t i = before; i < size(); i++) {
                    std::cerr << "  " << (int)at(i) << " (at " << i << ")\n";
                }
            }
            return *this;
        }
        
        BufferWithRandomAccess& operator<<(uint8_t x)
        {
            return *this << (int8_t)x;
        }
    
        BufferWithRandomAccess& operator<<(uint16_t x)
        {
            return *this << (int16_t)x;
        }
    
        BufferWithRandomAccess& operator<<(uint32_t x)
        {
            return *this << (int32_t)x;
        }
    
        BufferWithRandomAccess& operator<<(uint64_t x)
        {
            return *this << (int64_t)x;
        }
        
        BufferWithRandomAccess& operator<<(float x)
        {
            if (debug) std::cerr << "writeFloat32: " << x << " (at " << size() << ")" << std::endl;
            return *this << bit_cast<int32_t>(x);
        }
    
        BufferWithRandomAccess& operator<<(double x)
        {
            if (debug) std::cerr << "writeFloat64: " << x << " (at " << size() << ")" << std::endl;
            return *this << bit_cast<int64_t>(x);
        }
    
        BufferWithRandomAccess& operator<<(const std::string& str)
        {
            if (debug) std::cerr << "writeString: " << str << " (at " << size() << ")" << std::endl;
            int32_t size = str.size();
            *this << U32LEB(size);
            for (int32_t i = 0; i < size; i++) {
                *this << int8_t(str[i]);
            }
            return *this;
        }
    
        void writeAt(size_t i, uint16_t x)
        {
            if (debug) std::cerr << "backpatchInt16: " << x << " (at " << i << ")" << std::endl;
            (*this)[i] = x & 0xff;
            (*this)[i+1] = x >> 8;
        }
    
        void writeAt(size_t i, uint32_t x)
        {
            if (debug) std::cerr << "backpatchInt32: " << x << " (at " << i << ")" << std::endl;
            (*this)[i] = x & 0xff; x >>= 8;
            (*this)[i+1] = x & 0xff; x >>= 8;
            (*this)[i+2] = x & 0xff; x >>= 8;
            (*this)[i+3] = x & 0xff;
        }
    
        void writeAt(size_t i, U32LEB x)
        {
            if (debug) std::cerr << "backpatchU32LEB: " << x.value << " (at " << i << ")" << std::endl;
            x.writeAt(this, i, 5); // fill all 5 bytes, we have to do this when backpatching
        }
        
        template <typename T>
        void writeTo(T& o)
        {
            for (auto c : *this) o << c;
        }
    
};

namespace BinaryConsts {
    
    enum Meta {
        Magic = 0x6d736100,
        Version = 0x0d
    };
    
    enum Section {
        User = 0,
        Type = 1,
        Import = 2,
        Function = 3,
        Table = 4,
        Memory = 5,
        Global = 6,
        Export = 7,
        Start = 8,
        Element = 9,
        Code = 10,
        Data = 11
    };
    
    enum EncodedType {
        // value_type
        i32 = -0x1, // 0x7f
        i64 = -0x2, // 0x7e
        f32 = -0x3, // 0x7d
        f64 = -0x4, // 0x7c
        // elem_type
        AnyFunc = -0x10, // 0x70
        // func_type form
        Func = -0x20, // 0x60
        // block_type
        Empty = -0x40 // 0x40
    };
    
    namespace UserSections {
        extern const char* Name;
    }
    
    enum ASTNodes {
        Unreachable = 0x00,
        Nop = 0x01,
        Block = 0x02,
        Loop = 0x03,
        If = 0x04,
        Else = 0x05,
        
        End = 0x0b,
        Br = 0x0c,
        BrIf = 0x0d,
        TableSwitch = 0x0e, // TODO: Rename to BrTable
        Return = 0x0f,
        
        CallFunction = 0x10,
        CallIndirect = 0x11,
        
        Drop = 0x1a,
        Select = 0x1b,
        
        GetLocal = 0x20,
        SetLocal = 0x21,
        TeeLocal = 0x22,
        GetGlobal = 0x23,
        SetGlobal = 0x24,
        
        I32LoadMem = 0x28,
        I64LoadMem = 0x29,
        F32LoadMem = 0x2a,
        F64LoadMem = 0x2b,
        
        I32LoadMem8S = 0x2c,
        I32LoadMem8U = 0x2d,
        I32LoadMem16S = 0x2e,
        I32LoadMem16U = 0x2f,
        I64LoadMem8S = 0x30,
        I64LoadMem8U = 0x31,
        I64LoadMem16S = 0x32,
        I64LoadMem16U = 0x33,
        I64LoadMem32S = 0x34,
        I64LoadMem32U = 0x35,
        
        I32StoreMem = 0x36,
        I64StoreMem = 0x37,
        F32StoreMem = 0x38,
        F64StoreMem = 0x39,
        
        I32StoreMem8 = 0x3a,
        I32StoreMem16 = 0x3b,
        I64StoreMem8 = 0x3c,
        I64StoreMem16 = 0x3d,
        I64StoreMem32 = 0x3e,
        
        CurrentMemory = 0x3f,
        GrowMemory = 0x40,
        
        I32Const = 0x41,
        I64Const = 0x42,
        F32Const = 0x43,
        F64Const = 0x44,
        
        // Math operation moved in Binop.hh
        
        I32ConvertI64 = 0xa7, // TODO: rename to I32WrapI64
        I32STruncF32 = 0xa8,
        I32UTruncF32 = 0xa9,
        I32STruncF64 = 0xaa,
        I32UTruncF64 = 0xab,
        I64STruncI32 = 0xac, // TODO: rename to I64SExtendI32
        I64UTruncI32 = 0xad, // TODO: likewise
        I64STruncF32 = 0xae,
        I64UTruncF32 = 0xaf,
        I64STruncF64 = 0xb0,
        I64UTruncF64 = 0xb1,
        F32SConvertI32 = 0xb2,
        F32UConvertI32 = 0xb3,
        F32SConvertI64 = 0xb4,
        F32UConvertI64 = 0xb5,
        F32ConvertF64 = 0xb6, // TODO: rename to F32DemoteI64
        F64SConvertI32 = 0xb7,
        F64UConvertI32 = 0xb8,
        F64SConvertI64 = 0xb9,
        F64UConvertI64 = 0xba,
        F64ConvertF32 = 0xbb, // TODO: rename to F64PromoteF32
        
        I32ReinterpretF32 = 0xbc,
        I64ReinterpretF64 = 0xbd,
        F32ReinterpretI32 = 0xbe,
        F64ReinterpretI64 = 0xbf
    };
    
    enum MemoryAccess {
        Offset = 0x10,     // bit 4
        Alignment = 0x80,  // bit 7
        NaturalAlignment = 0
    };
    
} // namespace BinaryConsts


// Local variable counter with their types

struct LocalVarDesc {
    
    LocalVarDesc()
    {}
    
    LocalVarDesc(int index, Typed::VarType type)
    :fIndex(index), fType(type)
    {}
    
    int fIndex;
    Typed::VarType fType;
    
};

// TO REMOVE ?
inline S32LEB type2Binary(Typed::VarType type)
{
    if (type == Typed::kInt
        || type == Typed::kFloat_ptr
        || type == Typed::kDouble_ptr) {
        return S32LEB(BinaryConsts::EncodedType::i32);
    } else if (type == Typed::kFloat) {
        return S32LEB(BinaryConsts::EncodedType::f32);
    } else if (type == Typed::kDouble) {
        return S32LEB(BinaryConsts::EncodedType::f64);
    } else {
        assert(false);
        return S32LEB(BinaryConsts::EncodedType::Empty);
    }
}

// Count local variables with their types

struct LocalVariableCounter : public InstVisitor {
    
    int fIn32Type;
    int fF32Type;
    int fF64Type;
    map<string, LocalVarDesc> fLocalVarTable;
    int fLocalVarIndex;
    
    LocalVariableCounter():fIn32Type(0), fF32Type(0), fF64Type(0), fLocalVarIndex(0)
    {}
    
    virtual void visit(DeclareVarInst* inst)
    {
        // Local variables declared by [var_num, type] pairs
        if (inst->fAddress->getAccess() & Address::kStack) {
            Typed::VarType type = inst->fType->getType();
            if (type == Typed::kInt
                || type == Typed::kFloat_ptr
                || type == Typed::kDouble_ptr) {
                fIn32Type++;
            } else if (type == Typed::kFloat) {
                fF32Type++;
            } else if (type == Typed::kDouble) {
                fF64Type++;
            } else {
                assert(false);
            }
            assert(inst->fValue == nullptr);
            fLocalVarTable[inst->fAddress->getName()] = LocalVarDesc(fLocalVarIndex++, type);
        }
    }
    
    void generateLocals(BufferWithRandomAccess* out)
    {
        *out << U32LEB((fIn32Type ? 1 : 0) + (fF32Type ? 1 : 0) + (fF64Type ? 1 : 0));
        if (fIn32Type) *out << U32LEB(fIn32Type) << S32LEB(BinaryConsts::EncodedType::i32);
        if (fF32Type) *out << U32LEB(fF32Type) << S32LEB(BinaryConsts::EncodedType::f32);
        if (fF64Type) *out << U32LEB(fF64Type) << S32LEB(BinaryConsts::EncodedType::f64);
    }

};

// Counter of functions with their types

struct FunAndTypeCounter : public InstVisitor , public WASInst {
    
    FunAndTypeCounter():WASInst()
    {}
    
    virtual void generateFunDefArgs(DeclareFunInst* inst)
    {
        list<NamedTyped*>::const_iterator it;
        int size = inst->fType->fArgsTypes.size(), i = 0;
        for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
            //*fOut << "(param $" << (*it)->fName << " " << type2String((*it)->getType()) << ")";
            //if (i < size - 1) *fOut << " ";
        }
        //*fOut << " (result " << type2String(inst->fType->getType()) << ")";
    }
    
    virtual void generateFunDefBody(DeclareFunInst* inst)
    {
        if (inst->fCode->fCode.size() == 0) {
            // Pure prototype
        } else {
            // Function body
            //fTab++;
            //tab(fTab, *fOut);
            inst->fCode->accept(this);
            //fTab--;
            //tab(fTab, *fOut);
        }
    }
    
    virtual void generateFunCallArgs(list<ValueInst*>::const_iterator beg, list<ValueInst*>::const_iterator end, int size)
    {
        list<ValueInst*>::const_iterator it = beg;
        int i = 0;
        for (it = beg; it != end; it++, i++) {
            // Compile argument
            (*it)->accept(this);
            //if (i < size - 1) *fOut << " ";
        }
    }
    
    virtual void visit(DeclareFunInst* inst)
    {
        // Already generated
        if (fFunctionSymbolTable.find(inst->fName) != fFunctionSymbolTable.end()) {
            return;
        } else {
            fFunctionSymbolTable[inst->fName] = 1;
        }
        
        // Math library functions are part of the 'global' module, 'fmodf' and 'log10f' will be manually generated
        if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
            MathFunDesc desc = fMathLibTable[inst->fName];
            if (desc.fMode == MathFunDesc::Gen::kExtMath || desc.fMode == MathFunDesc::Gen::kExtWAS) {
                //tab(fTab, *fOut);
                if (desc.fMode == MathFunDesc::Gen::kExtMath) {
                    //*fOut << "(import $" << inst->fName << " \"global.Math\" " "\"" << desc.fName << "\" (param ";
                } else if (desc.fMode == MathFunDesc::Gen::kExtWAS) {
                    //*fOut << "(import $" << inst->fName << " \"asm2wasm\" " "\"" << desc.fName << "\" (param ";
                } else {
                    assert(false);
                }
            }
        } else {
            // Prototype
            generateFunDefArgs(inst);
            generateFunDefBody(inst);
        }
    }
    
};

class WASMInstVisitor : public InstVisitor, public WASInst {
    
     private:
    
        map<string, LocalVarDesc> fLocalVarTable;
        map<string, int> fFunctionsOffset;
        BufferWithRandomAccess* fOut;
    
        int32_t writeU32LEBPlaceholder()
        {
            int32_t ret = fOut->size();
            *fOut << int32_t(0);
            *fOut << int8_t(0);
            return ret;
        }
    
        void emitMemoryAccess()
        {
            *fOut << U32LEB(offStrNum);
            *fOut << U32LEB(0); // TO CHECK : assuming offset is always 0
        }
   
    public:

        WASMInstVisitor(BufferWithRandomAccess* out, int tab = 0)
            :WASInst(), fOut(out)
        {}

        virtual ~WASMInstVisitor()
        {}
    
        void setLocalVarTable(const map<string, LocalVarDesc>& table) { fLocalVarTable = table; }
    
        int32_t startSection(BinaryConsts::Section code)
        {
            *fOut << U32LEB(code);
            return writeU32LEBPlaceholder(); // section size to be filled in later
        }
    
        void finishSection(int32_t start)
        {
            int32_t size = fOut->size() - start - 5; // section size does not include the 5 bytes of the size field itself
            fOut->writeAt(start, U32LEB(size));
        }
 
        virtual void visit(DeclareVarInst* inst)
        {
            bool is_struct = (inst->fAddress->getAccess() & Address::kStruct) || (inst->fAddress->getAccess() & Address::kStaticStruct);
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
            
            if (array_typed && array_typed->fSize > 1) {
                if (is_struct) {
                    fFieldTable[inst->fAddress->getName()] = MemoryDesc(fStructOffset, array_typed->fSize, array_typed->fType->getType());
                    fStructOffset += (array_typed->fSize * fsize()); // Always use biggest size so that int/real access are correctly aligned
                } else {
                    // Should never happen...
                    assert(false);
                }
            } else {
                if (is_struct) {
                    fFieldTable[inst->fAddress->getName()] = MemoryDesc(fStructOffset, 1, inst->fType->getType());
                    fStructOffset += fsize(); // Always use biggest size so that int/real access are correctly aligned
                } else {
                    // Local variables declared by [var_num, type] pairs
                    assert(inst->fValue == nullptr);
                }
            }
        }
    
        virtual void visit(RetInst* inst)
        {
            if (inst->fResult) {
                inst->fResult->accept(this);
                *fOut << int8_t(BinaryConsts::Return);
            }
        }
    
        // Already handled using FunAndTypeCounter
        virtual void visit(DeclareFunInst* inst)
        {
            // Already generated
            if (fFunctionSymbolTable.find(inst->fName) != fFunctionSymbolTable.end()) {
                return;
            } else {
                fFunctionSymbolTable[inst->fName] = 1;
            }
            
            // If not math function, generate it
            if (fMathLibTable.find(inst->fName) == fMathLibTable.end()) {
                
                // Generate locals
                LocalVariableCounter local_counter;
                inst->fCode->accept(&local_counter);
                local_counter.generateLocals(fOut);
                
                // Generate body
                setLocalVarTable(local_counter.fLocalVarTable);
                inst->fCode->accept(this);
            }
        }
    
        virtual void visit(LoadVarInst* inst)
        {
            fTypingVisitor.visit(inst);
            if (inst->fAddress->getAccess() & Address::kStruct
                || inst->fAddress->getAccess() & Address::kStaticStruct
                || dynamic_cast<IndexedAddress*>(inst->fAddress)) {

                inst->fAddress->accept(this);
                if (isRealType(fTypingVisitor.fCurType) || isRealPtrType(fTypingVisitor.fCurType)) {
                    *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32LoadMem) : int8_t(BinaryConsts::F64LoadMem));
                } else {
                    *fOut << int8_t(BinaryConsts::I32LoadMem);
                }
                emitMemoryAccess();
                
            } else {
                LocalVarDesc local = fLocalVarTable[inst->fAddress->getName()];
                *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(local.fIndex);
            }
        }
    
        virtual void visit(StoreVarInst* inst)
        {
            inst->fValue->accept(&fTypingVisitor);

            if (inst->fAddress->getAccess() & Address::kStruct
                || inst->fAddress->getAccess() & Address::kStaticStruct
                || dynamic_cast<IndexedAddress*>(inst->fAddress)) {

                inst->fValue->accept(this);
                inst->fAddress->accept(this);
                if (isRealType(fTypingVisitor.fCurType) || isRealPtrType(fTypingVisitor.fCurType)) {
                    *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32StoreMem) : int8_t(BinaryConsts::F64StoreMem));
                } else {
                    *fOut << int8_t(BinaryConsts::I32StoreMem);
                }
                emitMemoryAccess();
     
            } else {
                LocalVarDesc local = fLocalVarTable[inst->fAddress->getName()];
                inst->fValue->accept(this);
                *fOut << int8_t(BinaryConsts::SetLocal) << U32LEB(local.fIndex);
            }
        }
    
        virtual void visit(NamedAddress* named)
        {
            if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
                MemoryDesc tmp = fFieldTable[named->getName()];
                if (fFastMemory) {
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(tmp.fOffset);
                } else {
                    *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(0);  // TO CHECK: assuming $dsp is at 0 local index
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(tmp.fOffset);
                    *fOut << int8_t(WasmOp::I32Add);
                }
            } else {
                LocalVarDesc local = fLocalVarTable[named->fName];
                *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(local.fIndex);
            }
        }
    
        virtual void visit(IndexedAddress* indexed)
        {
            // HACK : completely adhoc code for inputs/outputs...
            if ((startWith(indexed->getName(), "inputs") || startWith(indexed->getName(), "outputs"))) {
                LocalVarDesc local = fLocalVarTable[indexed->getName()];
                *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(2);
                indexed->fIndex->accept(this);
                *fOut << int8_t(WasmOp::I32Shl);
                *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(local.fIndex);
                *fOut << int8_t(WasmOp::I32Add);
                 // HACK : completely adhoc code for input/output...
            } else if ((startWith(indexed->getName(), "input") || startWith(indexed->getName(), "output"))) {
                LocalVarDesc local = fLocalVarTable[indexed->getName()];
                // Force "output" access to be coherent with fSubContainerType (integer or real)
                if (fSubContainerType == kInt) {
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(2);
                } else {
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(offStrNum);
                }
                indexed->fIndex->accept(this);
                *fOut << int8_t(WasmOp::I32Shl);
                *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(local.fIndex);
                *fOut << int8_t(WasmOp::I32Add);
            } else {
                // Fields in struct are accessed using 'dsp' and an offset
                MemoryDesc tmp = fFieldTable[indexed->getName()];
                IntNumInst* num;
                if ((num = dynamic_cast<IntNumInst*>(indexed->fIndex))) {
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB((tmp.fOffset + (num->fNum << offStrNum)));
                    // Index can be computed at compile time
                    if (!fFastMemory) {
                        *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(0);  // TO CHECK: assuming $dsp is at 0 local index
                        *fOut << int8_t(WasmOp::I32Add);
                    }
                } else {
                    // Otherwise generate index computation code
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(offStrNum);
                    indexed->fIndex->accept(this);
                    *fOut << int8_t(WasmOp::I32Shl);
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(tmp.fOffset);
                    *fOut << int8_t(WasmOp::I32Add);
                    if (!fFastMemory) {
                        *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(0);  // TO CHECK: assuming $dsp is at 0 local index
                        *fOut << int8_t(WasmOp::I32Add);
                    }
                }
            }
        }
    
        virtual void visit(LoadVarAddressInst* inst)
        {
           // Not implemented in WASM
            assert(false);
        }
         
        virtual void visit(FloatNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << int8_t(BinaryConsts::F32Const) << inst->fNum;
        }
        
        virtual void visit(DoubleNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << int8_t(BinaryConsts::I64Const) << inst->fNum;
        }
    
        virtual void visit(IntNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(inst->fNum);
        }
    
        // Numerical computation
        void visitAuxInt(BinopInst* inst)
        {
            inst->fInst1->accept(this);
            inst->fInst2->accept(this);
            *fOut << int8_t(gBinOpTable[inst->fOpcode]->fWasmInt);
        }
    
        void visitAuxReal(BinopInst* inst, Typed::VarType type)
        {
            inst->fInst1->accept(this);
            inst->fInst2->accept(this);
            if (type == Typed::kFloat) {
                *fOut << int8_t(gBinOpTable[inst->fOpcode]->fWasmFloat);
            } else if (type == Typed::kDouble) {
                *fOut << int8_t(gBinOpTable[inst->fOpcode]->fWasmDouble);
            } else {
                assert(false);
            }
        }
    
        virtual void visit(BinopInst* inst)
        {
            inst->fInst1->accept(&fTypingVisitor);
            Typed::VarType type1 = fTypingVisitor.fCurType;
            
            if (isRealType(type1)) {
                visitAuxReal(inst, type1);
            } else {
                inst->fInst2->accept(&fTypingVisitor);
                Typed::VarType type2 = fTypingVisitor.fCurType;
                if (isRealType(type2)) {
                    visitAuxReal(inst, type1);
                } else if (isIntType(type1) || isIntType(type2)) {
                    visitAuxInt(inst);
                } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                    visitAuxInt(inst);
                } else {
                    // Should never happen...
                    assert(false);
                }
            }
            
            fTypingVisitor.visit(inst);
        }

        virtual void visit(CastNumInst* inst)
        {
            inst->fInst->accept(&fTypingVisitor);
            Typed::VarType type = fTypingVisitor.fCurType;
            
            if (inst->fType->getType() == Typed::kInt) {
                if (type == Typed::kInt) {
                    //std::cout << "CastNumInst : cast to int, but arg already int !" << std::endl;
                    inst->fInst->accept(this);
                } else {
                    inst->fInst->accept(this);
                    *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::I32STruncF32) : int8_t(BinaryConsts::I32STruncF64));
                }
            } else {
                if (isRealType(type)) {
                    //std::cout << "CastNumInst : cast to real, but arg already real !" << std::endl;
                    inst->fInst->accept(this);
                } else {
                    inst->fInst->accept(this);
                    *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32SConvertI32) : int8_t(BinaryConsts::F64SConvertI32));
                }
            }
            
            fTypingVisitor.visit(inst);
        }
    
        // Special case for min/max
        void generateMinMax(const list<ValueInst*>& args, const string& fun)
        {
            list<ValueInst*>::iterator it;
            ValueInst* arg1 = *(args.begin());
            arg1->accept(&fTypingVisitor);
            if (isIntType(fTypingVisitor.fCurType)) {
                // Using manually generated min/max
                *fOut << BinaryConsts::CallFunction << fFunctionsOffset[fun];
            } else {
                MathFunDesc desc = fMathLibTable[fun];
                *fOut << desc.fWasmOp;
            }
        }

        // Generate standard funcall (not 'method' like funcall...)
        virtual void visit(FunCallInst* inst)
        {
            // Compile args first
            list<ValueInst*>::const_iterator it;
            for (it = inst->fArgs.begin(); it != inst->fArgs.end(); it++) {
                (*it)->accept(this);
            }
            
            // Then compile funcall
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
                MathFunDesc desc = fMathLibTable[inst->fName];
                if (desc.fMode == MathFunDesc::Gen::kWAS) {
                    // Special case for min/max
                    if (startWith(desc.fName, "min") || startWith(desc.fName, "max")) {
                        generateMinMax(inst->fArgs, desc.fName);
                    } else {
                        *fOut << desc.fWasmOp;
                    }
                } else {
                    *fOut << BinaryConsts::CallFunction << fFunctionsOffset[inst->fName];
                }
            } else {
                *fOut << BinaryConsts::CallFunction << fFunctionsOffset[inst->fName];
            }
        }
    
        // Conditional : select
        virtual void visit(Select2Inst* inst)
        {
            inst->fThen->accept(this);
            inst->fElse->accept(this);
            // Condition is last item
            inst->fCond->accept(this);
            *fOut << int8_t(BinaryConsts::Select);
            
            fTypingVisitor.visit(inst);
        }
    
        // Conditional : if : TO CHECK : utilise drop ?
        virtual void visit(IfInst* inst)
        {
            inst->fCond->accept(this);
            *fOut << int8_t(BinaryConsts::If) << int8_t(BinaryConsts::Empty);
            inst->fThen->accept(this);
            *fOut << int8_t(BinaryConsts::Else);
            inst->fElse->accept(this);
            // End of if
            *fOut << int8_t(BinaryConsts::End);
            
            fTypingVisitor.visit(inst);
        }
    
        virtual void visit(ForLoopInst* inst)
        {
            // Don't generate empty loops...
            if (inst->fCode->size() == 0) return;
            
            // Init loop counter
            inst->fInit->accept(this);
            
            // Loop block
            *fOut << int8_t(BinaryConsts::Loop) << int8_t(BinaryConsts::Empty);
            
                // Loop body block
                *fOut << int8_t(BinaryConsts::Block) << int8_t(BinaryConsts::Empty);
            
                    // Loop code code
                    inst->fCode->accept(this);
            
                    // Loop counter increment
                    inst->fIncrement->accept(this);
            
                    // Loop counter test and possibly branch out
                    inst->fEnd->accept(this);
                    *fOut << int8_t(BinaryConsts::If) << int8_t(BinaryConsts::Empty);
                    // Branch to loop
                    *fOut << int8_t(BinaryConsts::Br) << U32LEB(2);
                    // Branch out
                    *fOut << int8_t(BinaryConsts::Br) << U32LEB(1);
                    // End of if
                    *fOut << int8_t(BinaryConsts::End);
            
                // End of body block
                *fOut << int8_t(BinaryConsts::End);
            
            // End of loop block
            *fOut << int8_t(BinaryConsts::End);
        }
    
};

#endif
