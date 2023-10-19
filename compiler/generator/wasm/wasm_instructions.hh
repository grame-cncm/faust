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

#ifndef _WASM_INSTRUCTIONS_H
#define _WASM_INSTRUCTIONS_H

#include <string.h>
#include <cmath>
#include <vector>

#include "fir_to_fir.hh"
#include "was_instructions.hh"
#include "wasm_binary.hh"

//
// We mostly stream into a buffer as we create the binary format, however,
// sometimes we need to backtrack and write to a location behind us - wasm
// is optimized for reading, not writing.
//
class BufferWithRandomAccess : public std::vector<uint8_t> {
   private:
    bool debug;

   public:
    BufferWithRandomAccess(bool dbg = false) : debug(dbg) {}

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
        push_back(x & 0xff);
        x >>= 8;
        push_back(x & 0xff);
        x >>= 8;
        push_back(x & 0xff);
        x >>= 8;
        push_back(x & 0xff);
        return *this;
    }

    BufferWithRandomAccess& operator<<(int64_t x)
    {
        if (debug) std::cerr << "writeInt64: " << x << " (at " << size() << ")" << std::endl;
        push_back(x & 0xff);
        x >>= 8;
        push_back(x & 0xff);
        x >>= 8;
        push_back(x & 0xff);
        x >>= 8;
        push_back(x & 0xff);
        x >>= 8;
        push_back(x & 0xff);
        x >>= 8;
        push_back(x & 0xff);
        x >>= 8;
        push_back(x & 0xff);
        x >>= 8;
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

    BufferWithRandomAccess& operator<<(uint8_t x) { return *this << (int8_t)x; }

    BufferWithRandomAccess& operator<<(uint16_t x) { return *this << (int16_t)x; }

    BufferWithRandomAccess& operator<<(uint32_t x) { return *this << (int32_t)x; }

    BufferWithRandomAccess& operator<<(uint64_t x) { return *this << (int64_t)x; }

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
        int32_t size = int32_t(str.size());
        *this << U32LEB(size);
        for (int32_t i = 0; i < size; i++) {
            *this << int8_t(str[i]);
        }
        return *this;
    }

    void writeAt(size_t i, uint16_t x)
    {
        if (debug) std::cerr << "backpatchInt16: " << x << " (at " << i << ")" << std::endl;
        (*this)[i]     = x & 0xff;
        (*this)[i + 1] = x >> 8;
    }

    void writeAt(size_t i, uint32_t x)
    {
        if (debug) std::cerr << "backpatchInt32: " << x << " (at " << i << ")" << std::endl;
        (*this)[i] = x & 0xff;
        x >>= 8;
        (*this)[i + 1] = x & 0xff;
        x >>= 8;
        (*this)[i + 2] = x & 0xff;
        x >>= 8;
        (*this)[i + 3] = x & 0xff;
    }

    void writeAt(size_t i, U32LEB x)
    {
        if (debug) std::cerr << "backpatchU32LEB: " << x.value << " (at " << i << ")" << std::endl;
        x.writeAt(this, i, 5);  // fill all 5 bytes, we have to do this when backpatching
    }

    int32_t writeU32LEBPlaceholder()
    {
        int32_t ret = int32_t(size());
        *this << int32_t(0);
        *this << int8_t(0);
        return ret;
    }

    std::string toString()
    {
        std::stringstream str;
        for (const auto& c : *this) str << c;
        return str.str();
    }

    template <typename T>
    void writeTo(T& o)
    {
        for (const auto& c : *this) o << c;
    }
};

inline int32_t startSectionAux(BufferWithRandomAccess* out, BinaryConsts::Section code)
{
    *out << U32LEB(code);
    return out->writeU32LEBPlaceholder();  // section size to be filled in later
}

inline void finishSectionAux(BufferWithRandomAccess* out, int32_t start)
{
    // section size does not include the 5 bytes of the size field itself
    int32_t size = int32_t(out->size()) - start - 5;
    out->writeAt(start, U32LEB(size));
}

inline S32LEB type2Binary(Typed::VarType type)
{
    if (isIntOrPtrType(type) || isBoolType(type)) {
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
    LocalVarDesc() {}

    LocalVarDesc(int index, Typed::VarType type, Address::AccessType access)
        : fIndex(index), fType(type), fAccess(access)
    {
    }

    int                 fIndex;
    Typed::VarType      fType;
    Address::AccessType fAccess;
};

// Count local variables (stack/loop) with their types : to be used at the beginning of each block
// Funargs variables are indexed first
struct LocalVariableCounter : public DispatchVisitor {
    int fIn32Type;
    int fF32Type;
    int fF64Type;

    int fFunArgIndex;

    std::map<std::string, LocalVarDesc> fLocalVarTable;

    LocalVariableCounter() : fIn32Type(0), fF32Type(0), fF64Type(0), fFunArgIndex(0) {}

    virtual void visit(DeclareVarInst* inst)
    {
        std::string    name = inst->fAddress->getName();
        Typed::VarType type = inst->fType->getType();
        Address::AccessType access = inst->fAddress->getAccess();

        faustassert(fLocalVarTable.find(name) == fLocalVarTable.end());

        // stack/loop variables accessed by [var_num, type] pairs
        if (access & Address::kStack || access & Address::kLoop) {
            if (isIntOrPtrType(type)) {
                fLocalVarTable[name] = LocalVarDesc(fIn32Type++, type, access);
            } else if (type == Typed::kFloat) {
                fLocalVarTable[name] = LocalVarDesc(fF32Type++, type, access);
            } else if (type == Typed::kDouble) {
                fLocalVarTable[name] = LocalVarDesc(fF64Type++, type, access);
            } else {
                faustassert(false);
            }

            faustassert(inst->fValue == nullptr);
        }
    }

    virtual void visit(DeclareFunInst* inst)
    {
        // funarg variable accessed by [var_num, type] pairs
        for (const auto& argType : inst->fType->fArgsTypes) {
            fLocalVarTable[argType->fName] = LocalVarDesc(fFunArgIndex++, argType->fType->getType(), Address::kFunArgs);
        }

        if (inst->fCode) {
            inst->fCode->accept(this);
        }
    }

    void generateStackMap(BufferWithRandomAccess* out)
    {
        // Update stack variable index depending of:
        // - number of stack variables of different type
        // - funarg variables number
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
        for (const auto& varDesc : fLocalVarTable) {
            std::cout << "varDesc " << varDesc.first << " index = " << varDesc.second.fIndex
                      << " type = " << Typed::gTypeString[varDesc.second.fType] << std::endl;
        }
        std::cout << "===== LocalVariableCounter end =====" << std::endl;
    }
};

// Counter of functions with their types and global variable offset
struct FunAndTypeCounter : public DispatchVisitor, public WASInst {
    std::map<std::string, FunTyped*>             fFunTypes;    // function name, function type
    std::map<std::string, std::pair<std::string, std::string>> fFunImports;  // function name, [module, base]

    using DispatchVisitor::visit;

    FunAndTypeCounter() : DispatchVisitor(), WASInst()
    {
        // Additional functions defined in the module
        {
            Names args;
            args.push_back(InstBuilder::genNamedTyped("arg1", Typed::kInt32));
            args.push_back(InstBuilder::genNamedTyped("arg2", Typed::kInt32));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genInt32Typed(), FunTyped::kDefault);
            fFunTypes["min_i"] = fun_type;
            fFunTypes["max_i"] = fun_type;
        }

        // DSP API

        // getNumInputs/getNumOutputs
        {
            Names args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genInt32Typed(), FunTyped::kDefault);
            fFunTypes["getNumInputs"]  = fun_type;
            fFunTypes["getNumOutputs"] = fun_type;
        }

        // getSampleRate
        {
            Names args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genInt32Typed(), FunTyped::kDefault);
            fFunTypes["getSampleRate"] = fun_type;
        }

        // init/instanceConstants/instanceInit
        {
            Names args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            args.push_back(InstBuilder::genNamedTyped("sample_rate", Typed::kInt32));
            FunTyped* fun_type     = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped(), FunTyped::kDefault);
            fFunTypes["init"]      = fun_type;
            fFunTypes["classInit"] = fun_type;
            fFunTypes["instanceConstants"] = fun_type;
            fFunTypes["instanceInit"]      = fun_type;
        }

        // instanceClear/instanceResetUserInterface
        {
            Names args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped(), FunTyped::kDefault);
            fFunTypes["instanceClear"]              = fun_type;
            fFunTypes["instanceResetUserInterface"] = fun_type;
        }

        // setParamValue
        {
            Names args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            args.push_back(InstBuilder::genNamedTyped("index", Typed::kInt32));
            args.push_back(InstBuilder::genNamedTyped("value", itfloat()));
            FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped(), FunTyped::kDefault);
            fFunTypes["setParamValue"] = fun_type;
        }

        // getParamValue
        {
            Names args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            args.push_back(InstBuilder::genNamedTyped("index", Typed::kInt32));
            FunTyped* fun_type =
                InstBuilder::genFunTyped(args, InstBuilder::genItFloatTyped(), FunTyped::kDefault);
            fFunTypes["getParamValue"] = fun_type;
        }

        // compute
        {
            Names args;
            args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
            args.push_back(InstBuilder::genNamedTyped("count", Typed::kInt32));
            args.push_back(
                InstBuilder::genNamedTyped("inputs", Typed::kVoid_ptr));  // so that fun type is correcty generated
            args.push_back(
                InstBuilder::genNamedTyped("outputs", Typed::kVoid_ptr));  // so that fun type is correcty generated
            FunTyped* fun_type   = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped(), FunTyped::kDefault);
            fFunTypes["compute"] = fun_type;
        }
    }

    virtual void visit(DeclareVarInst* inst)
    {
        bool is_struct = (inst->fAddress->getAccess() & Address::kStruct)
                        || (inst->fAddress->getAccess() & Address::kStaticStruct);
        
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        std::string name = inst->fAddress->getName();

        if (array_typed && array_typed->fSize > 1) {
            if (is_struct) {
                fFieldTable[name] = MemoryDesc(-1, fStructOffset, array_typed->fSize, array_typed->getSizeBytes(), array_typed->fType->getType());
                // Always use biggest size so that int/real access are correctly aligned
                fStructOffset += (array_typed->fSize * gGlobal->audioSampleSize());
            } else {
                // Local variables declared by [var_num, type] pairs, separated as (local, set_local instruction)
            }
        } else {
            if (is_struct) {
                fFieldTable[name] = MemoryDesc(-1, fStructOffset, 1, inst->fType->getSizeBytes(), inst->fType->getType());
                // Always use biggest size so that int/real access are correctly aligned
                fStructOffset += gGlobal->audioSampleSize();
            } else {
                // Local variables declared by [var_num, type] pairs, separated as (local, set_local instruction)
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
            fFunctionSymbolTable[inst->fName] = true;
        }

        // Math library functions are part of the 'global' module, 'fmod', 'log10' and 'remainder'
        // will be manually generated
        if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
            MathFunDesc desc = fMathLibTable[inst->fName];

            if (desc.fMode == MathFunDesc::Gen::kExtMath || desc.fMode == MathFunDesc::Gen::kExtWAS) {
                
                // Build function type (args type same as return type)
                Names args;
                if (desc.fArgs == 1) {
                    args.push_back(InstBuilder::genNamedTyped(gGlobal->getFreshID("v1"), desc.fTypeIn));
                } else if (desc.fArgs == 2) {
                    args.push_back(InstBuilder::genNamedTyped(gGlobal->getFreshID("v1"), desc.fTypeIn));
                    args.push_back(InstBuilder::genNamedTyped(gGlobal->getFreshID("v2"), desc.fTypeIn));
                } else {
                    faustassert(false);
                }

                FunTyped* fun_type =
                    InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(desc.fTypeOut), FunTyped::kDefault);
                fFunTypes[inst->fName] = fun_type;

                // Build function import
                fFunImports[inst->fName] = std::make_pair("env", desc.fName);
            }

        } else {
            // Prototype
            fFunTypes[inst->fName] = inst->fType;
        }
    }

    // Get the function index : imported functions are first followed by all module internally defined ones
    int32_t getFunctionIndex(const std::string& name)
    {
        // If imported function
        if (fFunImports.find(name) != fFunImports.end()) {
            int i = 0;
            for (const auto& import : fFunImports) {
                if (import.first == name) {
                    return i;
                }
                i++;
            }
            // Otherwise module defined function
        } else {
            int i = int(fFunImports.size());
            for (const auto& type : fFunTypes) {
                if (fFunImports.find(type.first) == fFunImports.end()) {
                    if (type.first == name) {
                        return i;
                    }
                    i++;  // only count module defined functions
                }
            }
        }

        std::cerr << "ASSERT : getFunctionIndex " << name << std::endl;
        faustassert(false);
        return -1;
    }

    // Get the function type index
    int32_t getFunctionTypeIndex(const std::string& name)
    {
        int i = 0;
        for (const auto& type : fFunTypes) {
            if (type.first == name) {
                return i;
            }
            i++;
        }
        std::cerr << "ASSERT : getFunctionTypeIndex " << name << std::endl;
        faustassert(false);
        return -1;
    }

    void generateFunTypes(BufferWithRandomAccess* out)
    {
        int32_t start = startSectionAux(out, BinaryConsts::Section::Type);
        *out << U32LEB(uint32_t(fFunTypes.size()));

        for (const auto& type_int : fFunTypes) {
            FunTyped* type = type_int.second;
            *out << S32LEB(BinaryConsts::EncodedType::Func);
            *out << U32LEB(uint32_t(type->fArgsTypes.size()));
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
        *out << U32LEB(uint32_t(fFunImports.size()) + ((internal_memory) ? 0 : 1));

        if (!internal_memory) {
            // Memory
            *out << "env";
            *out << "memory";
            *out << U32LEB(int32_t(ExternalKind::Memory));  // Memory kind
            *out << U32LEB(0);                            // Memory flags
            *out << U32LEB(1);  // Memory size set by JS code, so use a minimum value that contains the data segment
                                // size (shoud be OK for any JSON)
        }

        for (const auto& import : fFunImports) {
            *out << import.second.first;  // module
            // Possibly map fastmath functions, emcc compiled functions are prefixed with '_'
            *out << ("_" + gGlobal->getMathFunction(import.first));  // base
            *out << U32LEB(int32_t(ExternalKind::Function));
            *out << U32LEB(getFunctionTypeIndex(import.first));  // function type index
        }

        finishSectionAux(out, start);
    }

    // Generate internal function export
    void generateExport(BufferWithRandomAccess* out, const std::string& name)
    {
        *out << name;
        *out << U32LEB(int32_t(ExternalKind::Function));
        *out << U32LEB(getFunctionIndex(name));  // function index
    }

    // Generate list of function signatures
    void generateFuncSignatures(BufferWithRandomAccess* out)
    {
        int32_t start = startSectionAux(out, BinaryConsts::Section::Function);
        *out << U32LEB(uint32_t(fFunTypes.size() - fFunImports.size()));

        // Module internally defined functions (those not in FunImports)
        for (const auto& type : fFunTypes) {
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
    std::map<std::string, LocalVarDesc> fLocalVarTable;
    BufferWithRandomAccess*   fOut;
    FunAndTypeCounter         fFunAndTypeCounter;

    void generateMemoryAccess(int offset = 0)
    {
        //*fOut << U32LEB(offStrNum); // Makes V8 return: 'invalid alignment; expected maximum alignment is 2, actual
        // alignment is 3'
        *fOut << U32LEB(2);
        *fOut << U32LEB(offset);
    }

   public:
    using DispatchVisitor::visit;

    WASMInstVisitor(BufferWithRandomAccess* out, bool fast_memory) : WASInst(fast_memory), fOut(out) {}

    virtual ~WASMInstVisitor() {}

    void setLocalVarTable(const std::map<std::string, LocalVarDesc>& table) { fLocalVarTable = table; }

    FunAndTypeCounter* getFunAndTypeCounter() { return &fFunAndTypeCounter; }

    void updateStructOffsetAndFieldTable()
    {
        fStructOffset = fFunAndTypeCounter.fStructOffset;
        fFieldTable   = fFunAndTypeCounter.fFieldTable;
    }

    int32_t startSection(BinaryConsts::Section code) { return startSectionAux(fOut, code); }

    void finishSection(int32_t start) { return finishSectionAux(fOut, start); }

    void generateFunTypes() { fFunAndTypeCounter.generateFunTypes(fOut); }

    void generateImports(int channels, bool internal_memory)
    {
        fFunAndTypeCounter.generateImports(fOut, channels, internal_memory);
    }

    void generateExports(bool internal_memory)
    {
        int32_t start = startSection(BinaryConsts::Section::Export);
        *fOut << U32LEB(EXPORTED_FUNCTION_NUM +
                        ((internal_memory) ? 1 : 0));  // num export = EXPORTED_FUNCTION_NUM functions (+ memory)

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
            *fOut << U32LEB(0);                              // Memory index
        }

        finishSection(start);
    }

    // Return the stream position where the memory size value will have to be written
    size_t generateInternalMemory()
    {
        int32_t start = startSection(BinaryConsts::Section::Memory);
        *fOut << U32LEB(1);  // num memories
        *fOut << U32LEB(1);  // memory flags, 1 means [min, max]
        // minimum memory pages number
        size_t size_pos = fOut->writeU32LEBPlaceholder();
        // maximum memory pages number, to be extended on JS side for soundfiles
        fOut->writeU32LEBPlaceholder();
        finishSection(start);
        return size_pos;
    }

    void generateFuncSignatures() { fFunAndTypeCounter.generateFuncSignatures(fOut); }

    void generateModuleHeader() { *fOut << int32_t(BinaryConsts::Magic) << int32_t(BinaryConsts::Version); }

    // (adhoc generation for now since currently FIR cannot be generated to handle this case)
    void generateSetParamValue()
    {
        size_t size_pos = fOut->writeU32LEBPlaceholder();
        size_t start    = fOut->size();

        // Local variables
        LocalVariableCounter local_counter;
        local_counter.generateStackMap(fOut);

        // Index in the dsp
        *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(0);  // 0 = dsp
        *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(1);  // 1 = index
        *fOut << int8_t(gBinOpTable[kAdd]->fWasmInt32);

        // Value
        *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(2);  // 2 = value

        // Store value at index
        *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32StoreMem) : int8_t(BinaryConsts::F64StoreMem));
        generateMemoryAccess();

        // Generate end
        *fOut << int8_t(BinaryConsts::End);
        size_t size = fOut->size() - start;
        fOut->writeAt(size_pos, U32LEB(uint32_t(size)));
    }

    // (adhoc generation for now since currently FIR cannot be generated to handle this case)
    void generateGetParamValue()
    {
        size_t size_pos = fOut->writeU32LEBPlaceholder();
        size_t start    = fOut->size();

        // Local variables
        LocalVariableCounter local_counter;
        local_counter.generateStackMap(fOut);

        // Index in the dsp
        *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(0);  // 0 = dsp
        *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(1);  // 1 = index
        *fOut << int8_t(gBinOpTable[kAdd]->fWasmInt32);

        // Load value from index
        *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32LoadMem) : int8_t(BinaryConsts::F64LoadMem));
        generateMemoryAccess();

        // Return value
        *fOut << int8_t(BinaryConsts::Return);

        // Generate end
        *fOut << int8_t(BinaryConsts::End);
        size_t size = fOut->size() - start;
        fOut->writeAt(size_pos, U32LEB(uint32_t(size)));
    }

    void generateJSON(const std::string& json)
    {
        // One data segment only
        int     data_segment_num = 1;
        int32_t start            = startSection(BinaryConsts::Section::Data);
        *fOut << U32LEB(data_segment_num);
        // For each segment (= 1 here)
        // Linear memory 0 in the MVP
        *fOut << U32LEB(0);
        // Offset defined as an 'initializer expression' is 0
        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(0);
        *fOut << int8_t(BinaryConsts::End);
        // Write the JSON string
        size_t size = json.size();
        *fOut << U32LEB(uint32_t(json.size()));
        for (size_t i = 0; i < size; i++) {
            *fOut << int8_t(json[i]);
        }
        finishSection(start);
    }
    
    virtual void visit(AddSoundfileInst* inst)
    {
        // Not supported for now
        throw faustexception("ERROR : 'soundfile' primitive not yet supported for wasm\n");
    }

    virtual void visit(DeclareVarInst* inst)
    {
        Address::AccessType access      = inst->fAddress->getAccess();
        bool                is_struct  = (access & Address::kStruct) || (access & Address::kStaticStruct);
        ArrayTyped*         array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        std::string        name        = inst->fAddress->getName();
    
        // fSampleRate may appear several time (in subcontainers and in main DSP)
        if (name != "fSampleRate") {
            if (fFieldTable.find(name) != fFieldTable.end() && (access & Address::kStaticStruct)) {
                // When inlined in classInit and instanceConstants, kStaticStruct may appear several times
                return;
            }
            faustassert(fFieldTable.find(name) == fFieldTable.end());
        }
    
        if (array_typed && array_typed->fSize > 1) {
            if (is_struct) {
                fFieldTable[name] = MemoryDesc(-1, fStructOffset, array_typed->fSize, array_typed->getSizeBytes(), array_typed->fType->getType());
                // Always use biggest size so that int/real access are correctly aligned
                fStructOffset += (array_typed->fSize * gGlobal->audioSampleSize());
            } else {
                // Local variables declared by [var_num, type] pairs, separated as (local, set_local instruction)
            }
        } else {
            if (is_struct) {
                fFieldTable[name] = MemoryDesc(-1, fStructOffset, 1, inst->fType->getSizeBytes(), inst->fType->getType());
                // Always use biggest size so that int/real access are correctly aligned
                fStructOffset += gGlobal->audioSampleSize();
            } else {
                // Local variables declared by [var_num, type] pairs, separated as (local, set_local instruction)
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
            fFunctionSymbolTable[inst->fName] = true;
        }

        // Generate function body
        size_t size_pos = fOut->writeU32LEBPlaceholder();
        size_t start    = fOut->size();

        // Generate locals
        LocalVariableCounter local_counter;
        inst->accept(&local_counter);
        local_counter.generateStackMap(fOut);
        // local_counter.dump();
        setLocalVarTable(local_counter.fLocalVarTable);

        inst->fCode->accept(this);

        // Generate end
        *fOut << int8_t(BinaryConsts::End);
        size_t size = fOut->size() - start;
        fOut->writeAt(size_pos, U32LEB(uint32_t(size)));
    }

    virtual void visit(LoadVarInst* inst)
    {
        Typed::VarType type        = TypingVisitor::getType(inst);
        Address::AccessType access = inst->fAddress->getAccess();
        std::string          name = inst->fAddress->getName();
        IndexedAddress*    indexed = dynamic_cast<IndexedAddress*>(inst->fAddress);
    
        if (access & Address::kStruct || access & Address::kStaticStruct || indexed) {
            int offset;
            if ((offset = getConstantOffset(inst->fAddress)) > 0) {
                // Generate 0
                *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(0);
            } else {
                // Otherwise generate address expression
                inst->fAddress->accept(this);
            }
            if (isRealType(type)) {
                *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32LoadMem)
                                                     : int8_t(BinaryConsts::F64LoadMem));
            } else if (isInt64Type(type)) {
                *fOut << int8_t(BinaryConsts::I64LoadMem);
            } else if (isInt32Type(type) || isPtrType(type)) {
                *fOut << int8_t(BinaryConsts::I32LoadMem);
            } else {
                faustassert(false);
            }
            // Possibly used offset (if > 0)
            generateMemoryAccess(offset);
    
        } else {
            faustassert(fLocalVarTable.find(name) != fLocalVarTable.end());
            LocalVarDesc local = fLocalVarTable[name];
            *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(local.fIndex);
        }
    }

    virtual void visit(TeeVarInst* inst)
    {
        std::string name = inst->fAddress->getName();

        faustassert(fLocalVarTable.find(name) != fLocalVarTable.end());
        LocalVarDesc local = fLocalVarTable[name];

        // 'tee_local' is generated the first time the variable is used
        // All future access simply use a local.get
        if (fTeeMap.find(name) == fTeeMap.end()) {
            inst->fValue->accept(this);
            *fOut << int8_t(BinaryConsts::LocalTee) << U32LEB(local.fIndex);
            fTeeMap[name] = true;
        } else {
            *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(local.fIndex);
        }
    }

    virtual void visit(StoreVarInst* inst)
    {
        Typed::VarType type        = TypingVisitor::getType(inst->fValue);
        Address::AccessType access = inst->fAddress->getAccess();
        std::string name           = inst->fAddress->getName();
        IndexedAddress* indexed    = dynamic_cast<IndexedAddress*>(inst->fAddress);

        if (access & Address::kStruct || access & Address::kStaticStruct || indexed) {
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
                *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32StoreMem)
                                                     : int8_t(BinaryConsts::F64StoreMem));
            } else if (isInt64Type(type)) {
                *fOut << int8_t(BinaryConsts::I64StoreMem);
            } else if (isInt32Type(type) || isPtrType(type) || isBoolType(type)) {
                *fOut << int8_t(BinaryConsts::I32StoreMem);
            } else {
                faustassert(false);
            }
            // Possibly used offset (if > 0)
            generateMemoryAccess(offset);

        } else {
            faustassert(fLocalVarTable.find(name) != fLocalVarTable.end());
            LocalVarDesc local = fLocalVarTable[name];
            inst->fValue->accept(this);
            *fOut << int8_t(BinaryConsts::LocalSet) << U32LEB(local.fIndex);
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
                *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(0);  // Assuming $dsp is at 0 local variable index
                *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(tmp.fOffset);
                *fOut << int8_t(WasmOp::I32Add);
            }
        } else {
            faustassert(fLocalVarTable.find(named->getName()) != fLocalVarTable.end());
            LocalVarDesc local = fLocalVarTable[named->getName()];
            *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(local.fIndex);
        }
    }

    virtual void visit(IndexedAddress* indexed)
    {
        // TO CHECK : size of memory ptr ?

        // HACK : completely adhoc code for inputs/outputs...
        if ((startWith(indexed->getName(), "inputs") || startWith(indexed->getName(), "outputs"))) {
            // Since indexed->getIndex() is always a known constant value, offset can be directly generated
            Int32NumInst* num = dynamic_cast<Int32NumInst*>(indexed->getIndex());
            faustassert(num);
            // "inputs" is 'compute' method third parameter, so with index 2
            // "outputs" is 'compute' method fourth parameter, so with index 3
            *fOut << int8_t(BinaryConsts::LocalGet)
                  << ((startWith(indexed->getName(), "inputs")) ? U32LEB(2) : U32LEB(3));
            *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(num->fNum << 2);
            *fOut << int8_t(WasmOp::I32Add);
            // HACK : completely adhoc code for input/output...
        } else if ((startWith(indexed->getName(), "input") || startWith(indexed->getName(), "output"))) {
            faustassert(fLocalVarTable.find(indexed->getName()) != fLocalVarTable.end());
            LocalVarDesc local = fLocalVarTable[indexed->getName()];
            *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(local.fIndex);
            indexed->getIndex()->accept(this);
            // If 'i' loop variable moves in bytes, save index code generation of input/output
            if (gGlobal->gLoopVarInBytes) {
                *fOut << int8_t(WasmOp::I32Add);
            } else {
                *fOut << int8_t(BinaryConsts::I32Const) << S32LEB((fSubContainerType == kInt) ? 2 : offStrNum);
                *fOut << int8_t(WasmOp::I32Shl);
                *fOut << int8_t(WasmOp::I32Add);
            }
        } else {
            /*
             Fields in DSP struct are accessed using 'dsp' and an offset
             IndexedAddress is also used for soundfiles (pointer + field index)
            */
            if (fFieldTable.find(indexed->getName()) != fFieldTable.end()) {
                MemoryDesc    tmp = fFieldTable[indexed->getName()];
                Int32NumInst* num;
                if ((num = dynamic_cast<Int32NumInst*>(indexed->getIndex()))) {
                    // Index can be computed at compile time
                    if (fFastMemory) {
                        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB((tmp.fOffset + (num->fNum << offStrNum)));
                    } else {
                        *fOut << int8_t(BinaryConsts::LocalGet)
                              << U32LEB(0);  // Assuming $dsp is at 0 local variable index
                        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB((tmp.fOffset + (num->fNum << offStrNum)));
                        *fOut << int8_t(WasmOp::I32Add);
                    }
                } else {
                    // Otherwise generate index computation code
                    if (fFastMemory) {
                        // Micro optimization if the field is actually the first one in the structure
                        if (tmp.fOffset == 0) {
                            indexed->getIndex()->accept(this);
                            *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(offStrNum);
                            *fOut << int8_t(WasmOp::I32Shl);
                        } else {
                            *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(tmp.fOffset);
                            indexed->getIndex()->accept(this);
                            *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(offStrNum);
                            *fOut << int8_t(WasmOp::I32Shl);
                            *fOut << int8_t(WasmOp::I32Add);
                        }
                    } else {
                        // Micro optimization if the field is actually the first one in the structure
                        if (tmp.fOffset == 0) {
                            *fOut << int8_t(BinaryConsts::LocalGet)
                                  << U32LEB(0);  // Assuming $dsp is at 0 local variable index
                            indexed->getIndex()->accept(this);
                            *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(offStrNum);
                            *fOut << int8_t(WasmOp::I32Shl);
                            *fOut << int8_t(WasmOp::I32Add);
                        } else {
                            *fOut << int8_t(BinaryConsts::LocalGet)
                                  << U32LEB(0);  // Assuming $dsp is at 0 local variable index
                            *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(tmp.fOffset);
                            indexed->getIndex()->accept(this);
                            *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(offStrNum);
                            *fOut << int8_t(WasmOp::I32Shl);
                            *fOut << int8_t(WasmOp::I32Add);
                            *fOut << int8_t(WasmOp::I32Add);
                        }
                    }
                }
            } else {
                // Local variable
                LocalVarDesc  local = fLocalVarTable[indexed->getName()];
                Int32NumInst* num;
                if ((num = dynamic_cast<Int32NumInst*>(indexed->getIndex()))) {
                    // Hack for 'soundfile'
                    DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
                    *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(local.fIndex);
                    if (struct_type) {
                        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(struct_type->fType->getOffset(num->fNum));
                    } else {
                        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(num->fNum << offStrNum);
                    }
                    *fOut << int8_t(WasmOp::I32Add);
                } else {
                    *fOut << int8_t(BinaryConsts::LocalGet) << U32LEB(local.fIndex);
                    indexed->getIndex()->accept(this);
                    *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(offStrNum);
                    *fOut << int8_t(WasmOp::I32Shl);
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
        *fOut << int8_t(BinaryConsts::F32Const) << inst->fNum;
    }

    virtual void visit(DoubleNumInst* inst)
    {
        *fOut << int8_t(BinaryConsts::F64Const) << inst->fNum;
    }

    virtual void visit(BoolNumInst* inst) { faustassert(false); }

    virtual void visit(Int32NumInst* inst)
    {
        *fOut << int8_t(BinaryConsts::I32Const) << S32LEB(inst->fNum);
    }

    virtual void visit(Int64NumInst* inst)
    {
        *fOut << int8_t(BinaryConsts::I64Const) << S64LEB(inst->fNum);
    }

    // Numerical computation
    virtual void visit(MinusInst* inst)
    {
        Typed::VarType type = TypingVisitor::getType(inst->fInst);
        InstBuilder::genMul(InstBuilder::genTypedNum(type, -1.), inst->fInst)->accept(this);
    }
    
    void visitAuxInt(BinopInst* inst, Typed::VarType type)
    {
        inst->fInst1->accept(this);
        inst->fInst2->accept(this);
        if (isInt32Type(type) || isBoolType(type)) {
            *fOut << int8_t(gBinOpTable[inst->fOpcode]->fWasmInt32);
        } else if (isInt64Type(type)) {
            *fOut << int8_t(gBinOpTable[inst->fOpcode]->fWasmInt64);
        } else {
            faustassert(false);
        }
    }

    void visitAuxReal(BinopInst* inst, Typed::VarType type)
    {
        inst->fInst1->accept(this);
        inst->fInst2->accept(this);
        if (isFloatType(type)) {
            *fOut << int8_t(gBinOpTable[inst->fOpcode]->fWasmFloat);
        } else if (isDoubleType(type)) {
            *fOut << int8_t(gBinOpTable[inst->fOpcode]->fWasmDouble);
        } else {
            faustassert(false);
        }
    }

    virtual void visit(BinopInst* inst)
    {
        Typed::VarType type1 = TypingVisitor::getType(inst->fInst1);
    
        if (isRealType(type1)) {
            visitAuxReal(inst, type1);
        } else {
            // type1 is kInt
            Typed::VarType type2 = TypingVisitor::getType(inst->fInst2);
            if (isRealType(type2)) {
                visitAuxReal(inst, type2);
            } else if (isIntType(type1) || isIntType(type2)) {
                visitAuxInt(inst, type2);
            } else if (isBoolType(type1) && isBoolType(type2)) {
                visitAuxInt(inst, type1);
            } else {
                // Should never happen...
                faustassert(false);
            }
        }
   }

    virtual void visit(::CastInst* inst)
    {
        Typed::VarType type = TypingVisitor::getType(inst->fInst);
    
        switch (inst->fType->getType()) {
            case Typed::kInt32:
                if (isInt32Type(type)) {
                    // Should not happen with properly casted FIR
                    dump2FIR(inst);
                    faustassert(false);
                } else if (isInt64Type(type)) {
                    inst->fInst->accept(this);
                    *fOut << int8_t(BinaryConsts::I32WrapI64);
                } else {
                    inst->fInst->accept(this);
                    *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::I32STruncF32)
                                                         : int8_t(BinaryConsts::I32STruncF64));
                }
                break;
                
            case Typed::kInt64:
                faustassert(false);
                break;
                
            case Typed::kFloat:
            case Typed::kDouble:
                if (isRealType(type)) {
                    // Should not happen with properly casted FIR
                    dump2FIR(inst);
                    faustassert(false);
                } else if (isInt64Type(type)) {
                    inst->fInst->accept(this);
                    *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32SConvertI64)
                                                         : int8_t(BinaryConsts::F64SConvertI64));
                } else if (isInt32Type(type) || isBoolType(type)) {
                    inst->fInst->accept(this);
                    *fOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32SConvertI32)
                                                         : int8_t(BinaryConsts::F64SConvertI32));
                } else {
                    faustassert(false);
                }
                break;
                
            default:
                faustassert(false);
                break;
        }
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
    }

    // Special case for min/max
    void generateMinMax(const Values& args, const std::string& name)
    {
        Values::iterator it;
        ValueInst* arg1 = *(args.begin());
        Typed::VarType type = TypingVisitor::getType(arg1);
        if (isIntType(type)) {
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
        for (const auto& it : inst->fArgs) {
            it->accept(this);
        }

        // Then compile funcall
        if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
            MathFunDesc desc = fMathLibTable[inst->fName];
            if (desc.fMode == MathFunDesc::Gen::kWAS) {
                // Special case for min/max
                if (checkMinMax(desc.fName)) {
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

    // Select that computes both branches
    /*
    virtual void visit(Select2Inst* inst)
    {
        inst->fThen->accept(this);
        inst->fElse->accept(this);
        // Condition is last item
        inst->fCond->accept(this);
        // Possibly convert i64 to i32
        Typed::VarType type = TypingVisitor::getType(inst->fCond);
        if (isInt64Type(type)) {
            // Compare to 0
            *fOut << int8_t(BinaryConsts::I64Const) << S32LEB(0);
            *fOut << int8_t(WasmOp::I64Ne);
        }
        *fOut << int8_t(BinaryConsts::Select);
     }
    */
    
    // Select that only computes one branch
    virtual void visit(Select2Inst* inst)
    {
        // Condition is first item
        inst->fCond->accept(this);
        // Possibly convert i64 to i32
        Typed::VarType cond = TypingVisitor::getType(inst->fCond);
        if (isInt64Type(cond)) {
            // Compare to 0
            *fOut << int8_t(BinaryConsts::I64Const) << S32LEB(0);
            *fOut << int8_t(WasmOp::I64Ne);
        }
        // Result type
        Typed::VarType then = TypingVisitor::getType(inst->fThen);
        *fOut << int8_t(BinaryConsts::If) << S32LEB(type2Binary(then));
        // Compile 'then'
        inst->fThen->accept(this);
        // Compile 'else'
        *fOut << int8_t(BinaryConsts::Else);
        inst->fElse->accept(this);
        // End of if
        *fOut << int8_t(BinaryConsts::End);
    }
  
    // Conditional : if (TO CHECK : use drop ?)
    virtual void visit(IfInst* inst)
    {
        inst->fCond->accept(this);
        // Possibly convert i64 to i32
        Typed::VarType type = TypingVisitor::getType(inst->fCond);
        if (isInt64Type(type)) {
            // Compare to 0
            *fOut << int8_t(BinaryConsts::I64Const) << S32LEB(0);
            *fOut << int8_t(WasmOp::I64Ne);
        }
        *fOut << int8_t(BinaryConsts::If) << S32LEB(BinaryConsts::Empty);
        inst->fThen->accept(this);
        if (inst->fElse->fCode.size() > 0) {
            *fOut << int8_t(BinaryConsts::Else);
            inst->fElse->accept(this);
        }
        // End of if
        *fOut << int8_t(BinaryConsts::End);
    }

    // Loop : beware, compiled loop does not work with an index of 0
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
