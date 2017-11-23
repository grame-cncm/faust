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
#include "fir_to_fir.hh"

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
    
        int32_t writeU32LEBPlaceholder()
        {
            int32_t ret = size();
            *this << int32_t(0);
            *this << int8_t(0);
            return ret;
        }
    
        string toString()
        {
            stringstream str;
            for (auto c : *this) str << c;
            return str.str();
        }
   
        template <typename T>
        void writeTo(T& o)
        {
            for (auto c : *this) o << c;
        }
    
};

enum class ExternalKind {
    Function = 0,
    Table = 1,
    Memory = 2,
    Global = 3
};

namespace BinaryConsts {
    
    enum Meta {
        Magic = 0x6d736100,
        Version = 0x01  // First official version
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
        Func = -0x20,    // 0x60
        // block_type
        Empty = -0x40    // 0x40
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
        
        I32ConvertI64 = 0xa7,   // TODO: rename to I32WrapI64
        I32STruncF32 = 0xa8,
        I32UTruncF32 = 0xa9,
        I32STruncF64 = 0xaa,
        I32UTruncF64 = 0xab,
        I64STruncI32 = 0xac,    // TODO: rename to I64SExtendI32
        I64UTruncI32 = 0xad,    // TODO: likewise
        I64STruncF32 = 0xae,
        I64UTruncF32 = 0xaf,
        I64STruncF64 = 0xb0,
        I64UTruncF64 = 0xb1,
        F32SConvertI32 = 0xb2,
        F32UConvertI32 = 0xb3,
        F32SConvertI64 = 0xb4,
        F32UConvertI64 = 0xb5,
        F32ConvertF64 = 0xb6,   // TODO: rename to F32DemoteI64
        F64SConvertI32 = 0xb7,
        F64UConvertI32 = 0xb8,
        F64SConvertI64 = 0xb9,
        F64UConvertI64 = 0xba,
        F64ConvertF32 = 0xbb,   // TODO: rename to F64PromoteF32
        
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

inline int32_t startSectionAux(BufferWithRandomAccess* out, BinaryConsts::Section code)
{
    *out << U32LEB(code);
    return out->writeU32LEBPlaceholder(); // section size to be filled in later
}

inline void finishSectionAux(BufferWithRandomAccess* out, int32_t start)
{
    int32_t size = out->size() - start - 5; // section size does not include the 5 bytes of the size field itself
    out->writeAt(start, U32LEB(size));
}

inline S32LEB type2Binary(Typed::VarType type)
{
    if (isIntOrPtrType(type)) {
        return S32LEB(BinaryConsts::EncodedType::i32);
    } else if (type == Typed::kFloat) {
        return S32LEB(BinaryConsts::EncodedType::f32);
    } else if (type == Typed::kDouble) {
        return S32LEB(BinaryConsts::EncodedType::f64);
    } else {
        faustassert(false);
        return S32LEB(BinaryConsts::EncodedType::Empty);
    }
}

// Local variable counter with their types
struct LocalVarDesc {
    
    LocalVarDesc()
    {}
    
    LocalVarDesc(int index, Typed::VarType type, Address::AccessType access)
        :fIndex(index), fType(type), fAccess(access)
    {}
    
    int fIndex;
    Typed::VarType fType;
    Address::AccessType fAccess;
    
};

// Count local variables (stack/loop) with their types : to be used at the beginning of each block
// Funargs variables are indexed first
struct LocalVariableCounter : public DispatchVisitor {
    
    int fIn32Type;
    int fF32Type;
    int fF64Type;
    
    int fFunArgIndex;
    
    map<string, LocalVarDesc> fLocalVarTable;
    
    LocalVariableCounter():fIn32Type(0), fF32Type(0), fF64Type(0), fFunArgIndex(0)
    {}
    
    virtual void visit(DeclareVarInst* inst)
    {
        string name = inst->fAddress->getName();
        Typed::VarType type = inst->fType->getType();
        
        // stack/loop variables accessed by [var_num, type] pairs
        if (inst->fAddress->getAccess() & Address::kStack || inst->fAddress->getAccess() & Address::kLoop) {
            if (isIntOrPtrType(type)) {
                fLocalVarTable[name] = LocalVarDesc(fIn32Type++, type, inst->fAddress->getAccess());
            } else if (type == Typed::kFloat) {
                fLocalVarTable[name] = LocalVarDesc(fF32Type++, type, inst->fAddress->getAccess());
            } else if (type == Typed::kDouble) {
                fLocalVarTable[name] = LocalVarDesc(fF64Type++, type, inst->fAddress->getAccess());
            } else {
                faustassert(false);
            }
            
            faustassert(inst->fValue == nullptr);
        }
    }
    
    virtual void visit(DeclareFunInst* inst)
    {
        // funarg variable accessed by [var_num, type] pairs
        for (auto& argType : inst->fType->fArgsTypes) {
            fLocalVarTable[argType->fName] = LocalVarDesc(fFunArgIndex++, argType->fType->getType(), Address::kFunArgs);
        }
        
        if (inst->fCode) {
            inst->fCode->accept(this);
        }
    }
    
    void generateStackMap(BufferWithRandomAccess* out)
    {
        // Update stack variable index depending of 1) number of stack variables of different type 2) funarg variables number
        for (auto& var : fLocalVarTable) {
            if (var.second.fAccess != Address::kFunArgs) {
                if (isIntOrPtrType(var.second.fType)) {
                    var.second.fIndex = var.second.fIndex + fFunArgIndex;
                } else if (var.second.fType == Typed::kFloat) {
                    var.second.fIndex = var.second.fIndex + fFunArgIndex + fIn32Type;
                } else if (var.second.fType == Typed::kDouble) {
                    var.second.fIndex = var.second.fIndex + fFunArgIndex + fIn32Type + fF32Type;
                } else {
                    faustassert(false);
                }
            }
        }
        
        *out << U32LEB((fIn32Type ? 1 : 0) + (fF32Type ? 1 : 0) + (fF64Type ? 1 : 0));
        if (fIn32Type) *out << U32LEB(fIn32Type) << S32LEB(BinaryConsts::EncodedType::i32);
        if (fF32Type) *out << U32LEB(fF32Type) << S32LEB(BinaryConsts::EncodedType::f32);
        if (fF64Type) *out << U32LEB(fF64Type) << S32LEB(BinaryConsts::EncodedType::f64);
    }
    
    void dump()
    {
        std::cout << "===== LocalVariableCounter begin =====" << std::endl;
        for (auto& varDesc : fLocalVarTable) {
            std::cout << "varDesc " << varDesc.first << " index = " << varDesc.second.fIndex << " type = " << Typed::gTypeString[varDesc.second.fType] << std::endl;
        }
        std::cout << "===== LocalVariableCounter end =====" << std::endl;
    }

};

// Counter of functions with their types and global variable offset
struct FunAndTypeCounter : public DispatchVisitor, public WASInst {
    
    std::map<string, FunTyped*> fFunTypes;                  // function name, function type
    std::map<string, pair<string, string> > fFunImports;    // function name, [module, base]
    
    FunAndTypeCounter():WASInst()
    {
        // Additional functions defined in the module
        {
            list<NamedTyped*> args;
            args.push_back(InstBuilder::genNamedTyped("arg1", Typed::kInt32));
            args.push_back(InstBuilder::genNamedTyped("arg2", Typed::kInt32));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kInt32), FunTyped::kDefault);
            fFunTypes["min_i"] = fun_type;
            fFunTypes["max_i"] = fun_type;
        }
        
        // DSP API
        
        // getNumInputs/getNumOutputs
        {
            list<NamedTyped*> args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kInt32), FunTyped::kDefault);
            fFunTypes["getNumInputs"] = fun_type;
            fFunTypes["getNumOutputs"] = fun_type;
        }
        
        // getSampleRate
        {
            list<NamedTyped*> args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kInt32), FunTyped::kDefault);
            fFunTypes["getSampleRate"] = fun_type;
        }
        
        // init/instanceConstants/instanceInit
        {
            list<NamedTyped*> args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            args.push_back(InstBuilder::genNamedTyped("samplingFreq", Typed::kInt32));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
            fFunTypes["init"] = fun_type;
            fFunTypes["classInit"] = fun_type;
            fFunTypes["instanceConstants"] = fun_type;
            fFunTypes["instanceInit"] = fun_type;
        }
        
        // instanceClear/instanceResetUserInterface
        {
            list<NamedTyped*> args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
            fFunTypes["instanceClear"] = fun_type;
            fFunTypes["instanceResetUserInterface"] = fun_type;
        }
        
        // setParamValue
        {
            list<NamedTyped*> args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            args.push_back(InstBuilder::genNamedTyped("index", Typed::kInt32));
            args.push_back(InstBuilder::genNamedTyped("value", itfloat()));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
            fFunTypes["setParamValue"] = fun_type;
        }
        
        // getParamValue
        {
            list<NamedTyped*> args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            args.push_back(InstBuilder::genNamedTyped("index", Typed::kInt32));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(itfloat()), FunTyped::kDefault);
            fFunTypes["getParamValue"] = fun_type;
        }
        
        // compute
        {
            list<NamedTyped*> args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            args.push_back(InstBuilder::genNamedTyped("count", Typed::kInt32));
            args.push_back(InstBuilder::genNamedTyped("inputs", Typed::kVoid_ptr));     // so that fun type is correcty generated
            args.push_back(InstBuilder::genNamedTyped("outputs", Typed::kVoid_ptr));    // so that fun type is correcty generated
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
            fFunTypes["compute"] = fun_type;
        }
    }
    
    virtual void visit(DeclareVarInst* inst)
    {
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
    
    virtual void visit(DeclareFunInst* inst)
    {
        // Already generated
        if (fFunctionSymbolTable.find(inst->fName) != fFunctionSymbolTable.end()) {
            return;
        } else {
            fFunctionSymbolTable[inst->fName] = 1;
        }
   
        // Math library functions are part of the 'global' module, 'fmod', 'log10' and 'remainder' will be manually generated
        if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
            MathFunDesc desc = fMathLibTable[inst->fName];
            
            if (desc.fMode == MathFunDesc::Gen::kExtMath || desc.fMode == MathFunDesc::Gen::kExtWAS) {
                
                // Build function type (args type same as return type)
                list<NamedTyped*> args;
                if (desc.fArgs == 1) {
                    args.push_back(InstBuilder::genNamedTyped(gGlobal->getFreshID("v1"), desc.fType));
                } else if (desc.fArgs == 2) {
                    args.push_back(InstBuilder::genNamedTyped(gGlobal->getFreshID("v1"), desc.fType));
                    args.push_back(InstBuilder::genNamedTyped(gGlobal->getFreshID("v2"), desc.fType));
                } else {
                    faustassert(false);
                }
                
                // Args type same as return type
                FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(desc.fType), FunTyped::kDefault);
                fFunTypes[inst->fName] = fun_type;
            
                // Build function import
                if (desc.fMode == MathFunDesc::Gen::kExtMath || desc.fMode == MathFunDesc::Gen::kExtWAS) {
                    fFunImports[inst->fName] = std::make_pair("env", desc.fName);
                } else {
                    faustassert(false);
                }
            }
        
        } else {
            // Prototype
            fFunTypes[inst->fName] = inst->fType;
        }
    }
    
    // Get the function index : imported functions are first followed by all module internally defined ones
    int32_t getFunctionIndex(const string& name)
    {
        // If imported function
        if (fFunImports.find(name) != fFunImports.end()) {
            int i = 0;
            for (auto& import : fFunImports) {
                if (import.first == name) {
                    return i;
                }
                i++;
            }
        // Otherwise module defined function
        } else {
            int i = fFunImports.size();
            for (auto& type : fFunTypes) {
                if (fFunImports.find(type.first) == fFunImports.end()) {
                    if (type.first == name) {
                        return i;
                    }
                    i++; // only count module defined functions
                }
            }
        }
        
        std::cerr << "getFunctionIndex " << name << std::endl;
        faustassert(false);
        return -1;
    }
    
    // Get the function type index
    int32_t getFunctionTypeIndex(const string& name)
    {
        int i = 0;
        for (auto& type : fFunTypes) {
            if (type.first == name) {
                return i;
            }
            i++;
        }
        std::cerr << "getFunctionTypeIndex " << name << std::endl;
        faustassert(false);
        return -1;
    }
    
    void generateFunTypes(BufferWithRandomAccess* out)
    {
        int32_t start = startSectionAux(out, BinaryConsts::Section::Type);
        *out << U32LEB(fFunTypes.size());
        
        for (auto& type_int : fFunTypes) {
            FunTyped* type = type_int.second;
            *out << S32LEB(BinaryConsts::EncodedType::Func);
            *out << U32LEB(type->fArgsTypes.size());
            for (auto param : type->fArgsTypes) {
                *out << type2Binary(param->getType());
            }
            if (type->fResult->getType() == Typed::kVoid) {
                *out << U32LEB(0);
            } else {
                *out << U32LEB(1);
                *out << type2Binary(type->fResult->getType());
            }
        }
        
        finishSectionAux(out, start);
    }
    
    // Generate list of imports
    void generateImports(BufferWithRandomAccess* out, int channels, bool internal_memory)
    {
        int32_t start = startSectionAux(out, BinaryConsts::Section::Import);
        *out << U32LEB(fFunImports.size() + ((internal_memory) ? 0 : 1));
        
        if (!internal_memory) {
            // Memory
            *out << "env";
            *out << "memory";
            *out << U32LEB(int32_t(ExternalKind::Memory));  // Memory kind
            *out << U32LEB(0); // Memory flags
            *out << U32LEB(1); // Memory size set by JS code, so use a minimum value that contains the data segment size (shoud be OK for any JSON)
        }
        
        for (auto& import : fFunImports) {
            *out << import.second.first;    // module
            // Possibly map fastmath functions, , emcc compiled functions are prefixed with '_'
            *out << ("_" + gGlobal->getMathFunction(import.first));  // base
            *out << U32LEB(int32_t(ExternalKind::Function));
            *out << U32LEB(getFunctionTypeIndex(import.first));      // function type index
        }
        
        finishSectionAux(out, start);
    }
    
    // Generate internal function export
    void generateExport(BufferWithRandomAccess* out, const string& name)
    {
        *out << name;
        *out << U32LEB(int32_t(ExternalKind::Function));
        *out << U32LEB(getFunctionIndex(name)); // function index
    }
    
    // Generate list of function signatures
    void generateFuncSignatures(BufferWithRandomAccess* out)
    {
        int32_t start = startSectionAux(out, BinaryConsts::Section::Function);
        *out << U32LEB(fFunTypes.size() - fFunImports.size());
        
        // Module internally defined functions (those not in FunImports)
        for (auto& type : fFunTypes) {
            if (fFunImports.find(type.first) == fFunImports.end()) {
                *out << U32LEB(getFunctionTypeIndex(type.first));
            }
        }
        finishSectionAux(out, start);
    }
    
};

#define EXPORTED_FUNCTION_NUM 11

class WASMInstVisitor : public DispatchVisitor, public WASInst {
    
     private:
    
        map<string, LocalVarDesc> fLocalVarTable;
        BufferWithRandomAccess* fOut;
        FunAndTypeCounter fFunAndTypeCounter;
    
        void generateMemoryAccess(int offset = 0)
        {
            //*fOut << U32LEB(offStrNum);   // Makes V8 return : 'invalid alignment; expected maximum alignment is 2, actual alignment is 3'
            *fOut << U32LEB(2);
            *fOut << U32LEB(offset);
        }
   
    public:
		using DispatchVisitor::visit;
    
        WASMInstVisitor(BufferWithRandomAccess* out, bool fast_memory):WASInst(fast_memory), fOut(out)
        {}

        virtual ~WASMInstVisitor()
        {}
    
        void setLocalVarTable(const map<string, LocalVarDesc>& table) { fLocalVarTable = table; }
    
        FunAndTypeCounter* getFunAndTypeCounter() { return &fFunAndTypeCounter; }
    
        void updateStructOffsetAndFieldTable()
        {
            fStructOffset = fFunAndTypeCounter.fStructOffset;
            fFieldTable = fFunAndTypeCounter.fFieldTable;
        }
    
        int32_t startSection(BinaryConsts::Section code)
        {
            return startSectionAux(fOut, code);
        }
    
        void finishSection(int32_t start)
        {
            return finishSectionAux(fOut, start);
        }
    
        void generateFunTypes()
        {
            fFunAndTypeCounter.generateFunTypes(fOut);
        }
    
        void generateImports(int channels, bool internal_memory)
        {
            fFunAndTypeCounter.generateImports(fOut, channels, internal_memory);
        }
    
        void generateExports(bool internal_memory)
        {
            int32_t start = startSection(BinaryConsts::Section::Export);
            *fOut << U32LEB(EXPORTED_FUNCTION_NUM + ((internal_memory) ? 1 : 0)); // num export = EXPORTED_FUNCTION_NUM functions (+ memory)
            
            fFunAndTypeCounter.generateExport(fOut, "compute");
            fFunAndTypeCounter.generateExport(fOut, "getNumInputs");
            fFunAndTypeCounter.generateExport(fOut, "getNumOutputs");
            fFunAndTypeCounter.generateExport(fOut, "getParamValue");
            fFunAndTypeCounter.generateExport(fOut, "getSampleRate");
            fFunAndTypeCounter.generateExport(fOut, "init");
            fFunAndTypeCounter.generateExport(fOut, "instanceClear");
            fFunAndTypeCounter.generateExport(fOut, "instanceConstants");
            fFunAndTypeCounter.generateExport(fOut, "instanceInit");
            fFunAndTypeCounter.generateExport(fOut, "instanceResetUserInterface");
            fFunAndTypeCounter.generateExport(fOut, "setParamValue");
            
            if (internal_memory) {
                // Memory
                *fOut << "memory";
                *fOut << U32LEB(int32_t(ExternalKind::Memory));  // Memory kind
                *fOut << U32LEB(0);  // Memory index
            }
            
            finishSection(start);
        }
    
        // Return the stream position where the memory size value will have to be written
        size_t generateInternalMemory()
        {
            int32_t start = startSection(BinaryConsts::Section::Memory);
            *fOut << U32LEB(1); // num memories
            *fOut << U32LEB(0); // memory flags
            size_t size_pos = fOut->writeU32LEBPlaceholder();
            finishSection(start);
            return size_pos;
        }
    
        void generateFuncSignatures()
        {
            fFunAndTypeCounter.generateFuncSignatures(fOut);
        }
    
        void generateModuleHeader()
        {
            *fOut << int32_t(BinaryConsts::Magic) << int32_t(BinaryConsts::Version);
        }
    
        // (adhoc generation for now since currently FIR cannot be generated to handle this case)
        void generateSetParamValue()
        {
            size_t size_pos = fOut->writeU32LEBPlaceholder();
            size_t start = fOut->size();
            
            // Local variables
            LocalVariableCounter local_counter;
            local_counter.generateStackMap(fOut);
            
            // Index in the dsp
            *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(0);  // 0 = dsp
            *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(1);  // 1 = index
            *fOut << int8_t(gBinOpTable[kAdd]->fWasmInt32);
            
            // Value
            *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(2);  // 2 = value
            
            // Store value at index
            *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32StoreMem) : int8_t(BinaryConsts::F64StoreMem));
            generateMemoryAccess();
            
            // Generate end
            *fOut << int8_t(BinaryConsts::End);
            size_t size = fOut->size() - start;
            fOut->writeAt(size_pos, U32LEB(size));
        }
    
        // (adhoc generation for now since currently FIR cannot be generated to handle this case)
        void generateGetParamValue()
        {
            size_t size_pos = fOut->writeU32LEBPlaceholder();
            size_t start = fOut->size();
            
            // Local variables
            LocalVariableCounter local_counter;
            local_counter.generateStackMap(fOut);
            
            // Index in the dsp
            *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(0);  // 0 = dsp
            *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(1);  // 1 = index
            *fOut << int8_t(gBinOpTable[kAdd]->fWasmInt32);
            
            // Load value from index
            *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32LoadMem) : int8_t(BinaryConsts::F64LoadMem));
            generateMemoryAccess();
            
            // Return value
            *fOut << int8_t(BinaryConsts::Return);
            
            // Generate end
            *fOut << int8_t(BinaryConsts::End);
            size_t size = fOut->size() - start;
            fOut->writeAt(size_pos, U32LEB(size));
        }
    
        void generateJSON(const string& json)
        {
            // One data segment only
            int data_segment_num = 1;
            int32_t start = startSection(BinaryConsts::Section::Data);
            *fOut << U32LEB(data_segment_num);
            // For each segment (= 1 here)
            // Linear memory 0 in the MVP
            *fOut << U32LEB(0);
            // Offset defined as an 'initializer expression' is 0
            *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(0);
            *fOut << int8_t(BinaryConsts::End);
            // Write the JSON string
            size_t size = json.size();
            *fOut << U32LEB(size + 1); // Including null character
            for (size_t i = 0; i < size; i++) {
                *fOut << int8_t(json[i]);
            }
            // Finish the string
            *fOut << int8_t('0');
            finishSection(start);
        }
    
        virtual void visit(DeclareVarInst* inst)
        {
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
    
        virtual void visit(RetInst* inst)
        {
            if (inst->fResult) {
                inst->fResult->accept(this);
                *fOut << int8_t(BinaryConsts::Return);
            }
        }
    
        // Function type definition is done first with FunAndTypeCounter, then the function body is generated here
        virtual void visit(DeclareFunInst* inst)
        {
            // Already generated
            if (fFunctionSymbolTable.find(inst->fName) != fFunctionSymbolTable.end()) {
                return;
            } else {
                fFunctionSymbolTable[inst->fName] = 1;
            }
       
            // Generate function body
            size_t size_pos = fOut->writeU32LEBPlaceholder();
            size_t start = fOut->size();
        
            // Generate locals
            LocalVariableCounter local_counter;
            inst->accept(&local_counter);
            local_counter.generateStackMap(fOut);
            //local_counter.dump();
            setLocalVarTable(local_counter.fLocalVarTable);
        
            inst->fCode->accept(this);
            
            // Generate end
            *fOut << int8_t(BinaryConsts::End);
            size_t size = fOut->size() - start;
            fOut->writeAt(size_pos, U32LEB(size));
        }
    
        virtual void visit(LoadVarInst* inst)
        {
            fTypingVisitor.visit(inst);
            Typed::VarType type = fTypingVisitor.fCurType;
            
            if (inst->fAddress->getAccess() & Address::kStruct
                || inst->fAddress->getAccess() & Address::kStaticStruct
                || dynamic_cast<IndexedAddress*>(inst->fAddress)) {
               
                int offset;
                if ((offset = getConstantOffset(inst->fAddress)) > 0) {
                    // Generate 0
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(0);
                } else {
                    // Otherwise generate address expression
                    inst->fAddress->accept(this);
                }
                if (isRealType(type) || isRealPtrType(type)) {
                    *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32LoadMem) : int8_t(BinaryConsts::F64LoadMem));
                } else {
                    *fOut << int8_t(BinaryConsts::I32LoadMem);
                }
                // Possibly used offset (if > 0)
                generateMemoryAccess(offset);
              
            } else {
                faustassert(fLocalVarTable.find(inst->fAddress->getName()) != fLocalVarTable.end());
                LocalVarDesc local = fLocalVarTable[inst->fAddress->getName()];
                *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(local.fIndex);
            }
        }
    
        virtual void visit(TeeVarInst* inst)
        {
            faustassert(fLocalVarTable.find(inst->fAddress->getName()) != fLocalVarTable.end());
            LocalVarDesc local = fLocalVarTable[inst->fAddress->getName()];
            
            // 'tee_local' is generated the first time the variable is used
            // All future access simply use a get_local
            if (fTeeMap.find(inst->fAddress->getName()) == fTeeMap.end()) {
                inst->fValue->accept(this);
                *fOut << int8_t(BinaryConsts::TeeLocal) << U32LEB(local.fIndex);
                fTeeMap[inst->fAddress->getName()] = true;
            } else {
                *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(local.fIndex);
            }
        }
    
        virtual void visit(StoreVarInst* inst)
        {
            inst->fValue->accept(&fTypingVisitor);
            Typed::VarType type = fTypingVisitor.fCurType;

            if (inst->fAddress->getAccess() & Address::kStruct
                || inst->fAddress->getAccess() & Address::kStaticStruct
                || dynamic_cast<IndexedAddress*>(inst->fAddress)) {
            
                int offset;
                if ((offset = getConstantOffset(inst->fAddress)) > 0) {
                    // Generate 0
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(0);
                } else {
                    // Otherwise generate address expression
                    inst->fAddress->accept(this);
                }
                inst->fValue->accept(this);
                if (isRealType(type) || isRealPtrType(type)) {
                    *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32StoreMem) : int8_t(BinaryConsts::F64StoreMem));
                } else {
                    *fOut << int8_t(BinaryConsts::I32StoreMem);
                }
                // Possibly used offset (if > 0)
                generateMemoryAccess(offset);
                
          } else {
                faustassert(fLocalVarTable.find(inst->fAddress->getName()) != fLocalVarTable.end());
                LocalVarDesc local = fLocalVarTable[inst->fAddress->getName()];
                inst->fValue->accept(this);
                *fOut << int8_t(BinaryConsts::SetLocal) << U32LEB(local.fIndex);
            }
        }
    
        virtual void visit(NamedAddress* named)
        {
            if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
                faustassert(fFieldTable.find(named->getName()) != fFieldTable.end());
                MemoryDesc tmp = fFieldTable[named->getName()];
                if (fFastMemory) {
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(tmp.fOffset);
                } else {
                    *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(0); // Assuming $dsp is at 0 local variable index
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(tmp.fOffset);
                    *fOut << int8_t(WasmOp::I32Add);
                }
            } else {
                faustassert(fLocalVarTable.find(named->getName()) != fLocalVarTable.end());
                LocalVarDesc local = fLocalVarTable[named->getName()];
                *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(local.fIndex);
            }
        }
    
        virtual void visit(IndexedAddress* indexed)
        {
            // TO CHECK : size of memory ptr ?
            
            // HACK : completely adhoc code for inputs/outputs...
            if ((startWith(indexed->getName(), "inputs") || startWith(indexed->getName(), "outputs"))) {
                // Since indexed->fIndex is always a known constant value, offset can be directly generated
                Int32NumInst* num = dynamic_cast<Int32NumInst*>(indexed->fIndex); faustassert(num);
                // "inputs" is 'compute' method third parameter, so with index 2
                // "outputs" is 'compute' method fourth parameter, so with index 3
                *fOut << int8_t(BinaryConsts::GetLocal) << ((startWith(indexed->getName(), "inputs")) ? U32LEB(2) : U32LEB(3));
                *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(num->fNum << 2);
                *fOut << int8_t(WasmOp::I32Add);
            // HACK : completely adhoc code for input/output...
            } else if ((startWith(indexed->getName(), "input") || startWith(indexed->getName(), "output"))) {
                faustassert(fLocalVarTable.find(indexed->getName()) != fLocalVarTable.end());
                LocalVarDesc local = fLocalVarTable[indexed->getName()];
                *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(local.fIndex);
                indexed->fIndex->accept(this);
                // If 'i' loop variable moves in bytes, save index code generation of input/output
                if (gGlobal->gLoopVarInBytes) {
                    *fOut << int8_t(WasmOp::I32Add);
                } else {
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB((fSubContainerType == kInt) ? 2 : offStrNum);
                    *fOut << int8_t(WasmOp::I32Shl);
                    *fOut << int8_t(WasmOp::I32Add);
                }
            } else {
                // Fields in struct are accessed using 'dsp' and an offset
                faustassert(fFieldTable.find(indexed->getName()) != fFieldTable.end());
                MemoryDesc tmp = fFieldTable[indexed->getName()];
                Int32NumInst* num;
                if ((num = dynamic_cast<Int32NumInst*>(indexed->fIndex))) {
                    // Index can be computed at compile time
                    if (fFastMemory) {
                        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB((tmp.fOffset + (num->fNum << offStrNum)));
                    } else {
                        *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(0); // Assuming $dsp is at 0 local variable index
                        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB((tmp.fOffset + (num->fNum << offStrNum)));
                        *fOut << int8_t(WasmOp::I32Add);
                    }
                } else {
                    // Otherwise generate index computation code
                    if (fFastMemory) {
                        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(tmp.fOffset);
                        indexed->fIndex->accept(this);
                        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(offStrNum);
                        *fOut << int8_t(WasmOp::I32Shl);
                        *fOut << int8_t(WasmOp::I32Add);
                    } else {
                        *fOut << int8_t(BinaryConsts::GetLocal) << U32LEB(0); // Assuming $dsp is at 0 local variable index
                        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(tmp.fOffset);
                        indexed->fIndex->accept(this);
                        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(offStrNum);
                        *fOut << int8_t(WasmOp::I32Shl);
                        *fOut << int8_t(WasmOp::I32Add);
                        *fOut << int8_t(WasmOp::I32Add);
                    }
                }
            }
        }
    
        virtual void visit(LoadVarAddressInst* inst)
        {
           // Not implemented in WASM
            faustassert(false);
        }
         
        virtual void visit(FloatNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << int8_t(BinaryConsts::F32Const) << inst->fNum;
        }
        
        virtual void visit(DoubleNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << int8_t(BinaryConsts::F64Const) << inst->fNum;
        }
    
        virtual void visit(Int32NumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(inst->fNum);
        }
    
        virtual void visit(Int64NumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << int8_t(BinaryConsts::I64Const) << S32LEB(inst->fNum);
        }
    
        // Numerical computation
        void visitAuxInt(BinopInst* inst, Typed::VarType type)
        {
            inst->fInst1->accept(this);
            inst->fInst2->accept(this);
            if (type == Typed::kInt32 || type == Typed::kBool) {
                *fOut << int8_t(gBinOpTable[inst->fOpcode]->fWasmInt32);
            } else if (type == Typed::kInt64) {
                *fOut << int8_t(gBinOpTable[inst->fOpcode]->fWasmInt64);
            } else {
                faustassert(false);
            }
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
                faustassert(false);
            }
        }
    
        virtual void visit(BinopInst* inst)
        {
            inst->fInst1->accept(&fTypingVisitor);
            Typed::VarType type1 = fTypingVisitor.fCurType;
            
            if (isRealType(type1)) {
                visitAuxReal(inst, type1);
            } else {
                // type1 is kInt
                inst->fInst2->accept(&fTypingVisitor);
                Typed::VarType type2 = fTypingVisitor.fCurType;
                if (isRealType(type2)) {
                    visitAuxReal(inst, type2);
                } else if (isIntType(type1) || isIntType(type2)) {
                    visitAuxInt(inst, type2);
                } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                    visitAuxInt(inst, type1);
                } else {
                    // Should never happen...
                    faustassert(false);
                }
            }
            
            fTypingVisitor.visit(inst);
        }

        virtual void visit(::CastInst* inst)
        {
            inst->fInst->accept(&fTypingVisitor);
            Typed::VarType type = fTypingVisitor.fCurType;
            
            if (inst->fType->getType() == Typed::kInt32) {
                if (type == Typed::kInt32) {
                    //std::cout << "CastInst : cast to int, but arg already int !" << std::endl;
                    inst->fInst->accept(this);
                } else {
                    inst->fInst->accept(this);
                    *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::I32STruncF32) : int8_t(BinaryConsts::I32STruncF64));
                }
            } else {
                if (isRealType(type)) {
                    //std::cout << "CastInst : cast to real, but arg already real !" << std::endl;
                    inst->fInst->accept(this);
                } else {
                    inst->fInst->accept(this);
                    *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32SConvertI32) : int8_t(BinaryConsts::F64SConvertI32));
                }
            }
            
            fTypingVisitor.visit(inst);
        }
    
        virtual void visit(BitcastInst* inst)
        {
            inst->fInst->accept(this);
            
            switch (inst->fType->getType()) {
                case Typed::kInt32:
                    *fOut << int8_t(BinaryConsts::I32ReinterpretF32);
                    break;
                case Typed::kInt64:
                    *fOut << int8_t(BinaryConsts::I64ReinterpretF64);
                    break;
                case Typed::kFloat:
                    *fOut << int8_t(BinaryConsts::F32ReinterpretI32);
                    break;
                case Typed::kDouble:
                    *fOut << int8_t(BinaryConsts::F64ReinterpretI64);
                    break;
                default:
                    faustassert(false);
                    break;
            }
            
            fTypingVisitor.visit(inst);
        }
    
        // Special case for min/max
        void generateMinMax(const list<ValueInst*>& args, const string& name)
        {
            list<ValueInst*>::iterator it;
            ValueInst* arg1 = *(args.begin());
            arg1->accept(&fTypingVisitor);
            if (isIntType(fTypingVisitor.fCurType)) {
                // Using manually generated min/max
                *fOut << int8_t(BinaryConsts::CallFunction) << U32LEB(fFunAndTypeCounter.getFunctionIndex(name));
                
            } else {
                faustassert(fMathLibTable.find(name) != fMathLibTable.end());
                MathFunDesc desc = fMathLibTable[name];
                *fOut << int8_t(desc.fWasmOp);
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
                        generateMinMax(inst->fArgs, inst->fName);
                    } else {
                        *fOut << int8_t(desc.fWasmOp);
                    }
                } else {
                    *fOut << int8_t(BinaryConsts::CallFunction) << U32LEB(fFunAndTypeCounter.getFunctionIndex(inst->fName));
                }
            } else {
                *fOut << int8_t(BinaryConsts::CallFunction) << U32LEB(fFunAndTypeCounter.getFunctionIndex(inst->fName));
            }
        }
    
        // Conditional : select
        virtual void visit(Select2Inst* inst)
        {
            inst->fThen->accept(this);
            inst->fElse->accept(this);
            // Condition is last item
            inst->fCond->accept(this);
            // Possibly convert i64 to i32
            inst->fCond->accept(&fTypingVisitor);
            if (isIntType64(fTypingVisitor.fCurType)) {
                // Compare to 0
                *fOut << int8_t(BinaryConsts::I64Const) << S32LEB(0);
                *fOut << int8_t(WasmOp::I64Ne);
            }
            *fOut << int8_t(BinaryConsts::Select);
            
            fTypingVisitor.visit(inst);
        }
    
        // Conditional : if (TO CHECK : utilise drop ?)
        virtual void visit(IfInst* inst)
        {
            inst->fCond->accept(this);
            // Possibly convert i64 to i32
            inst->fCond->accept(&fTypingVisitor);
            if (isIntType64(fTypingVisitor.fCurType)) {
                // Compare to 0
                *fOut << int8_t(BinaryConsts::I64Const) << S32LEB(0);
                *fOut << int8_t(WasmOp::I64Ne);
            }
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
            *fOut << int8_t(BinaryConsts::Loop) << S32LEB(BinaryConsts::Empty);
            
                // Loop body block
                *fOut << int8_t(BinaryConsts::Block) << S32LEB(BinaryConsts::Empty);
            
                    // Loop code code
                    inst->fCode->accept(this);
            
                    // Loop counter increment
                    inst->fIncrement->accept(this);
            
                    // Loop counter test and possibly branch out
                    inst->fEnd->accept(this);
                    *fOut << int8_t(BinaryConsts::If) << S32LEB(BinaryConsts::Empty);
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
