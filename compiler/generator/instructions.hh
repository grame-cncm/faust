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

#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef WIN32
#pragma warning(disable : 4800)
#endif

#include "Text.hh"
#include "binop.hh"
#include "exception.hh"
#include "garbageable.hh"
#include "instructions_type.hh"
#include "property.hh"

struct Printable;

// ===============
// User Interface
// ===============
struct AddMetaDeclareInst;
struct OpenboxInst;
struct CloseboxInst;
struct AddButtonInst;
struct AddSliderInst;
struct AddBargraphInst;
struct AddSoundfileInst;
struct LabelInst;

// =======
// Values
// =======
struct ValueInst;

// Memory load
struct LoadVarInst;
struct LoadVarAddressInst;
struct TeeVarInst;

// Base class for array of numbers
template <class TYPE>
struct ArrayNumInst;

// Numbers and array of numbers
struct FloatNumInst;
struct FloatArrayNumInst;
struct Int32NumInst;
struct Int64NumInst;
struct Int32ArrayNumInst;
struct BoolNumInst;
struct DoubleNumInst;
struct DoubleArrayNumInst;
struct FixedPointNumInst;
struct FixedPointArrayNumInst;

// Math Binop
struct BinopInst;

// Cast
struct CastInst;
struct BitcastInst;

// Selector
struct Select2Inst;

// Null value
struct NullValueInst;

// Function call
struct FunCallInst;

// ===========
// Statements
// ===========
struct StatementInst;

// Declarations
struct DeclareVarInst;
struct DeclareBufferIterators;
struct DeclareFunInst;
struct DeclareStructTypeInst;

// Memory store
struct StoreVarInst;
// Array move
struct ShiftArrayVarInst;

// Used in function
struct RetInst;

// Used for enable/control
struct ControlInst;

// Control flow
struct IfInst;
struct SwitchInst;

// Loops
struct ForLoopInst;
struct SimpleForLoopInst;
struct IteratorForLoopInst;
struct WhileLoopInst;

// Block of statements
struct BlockInst;

// A no-op statement
struct DropInst;

// Null statement
struct NullStatementInst;

// ======
// Types
// ======
struct Typed;

struct BasicTyped;
struct NamedTyped;
struct FixedTyped;
struct FunTyped;
struct ArrayTyped;
struct StructTyped;
struct VectorTyped;

// =========
// Adresses
// =========
struct Address;
struct NamedAddress;
struct IndexedAddress;

// =============
// Naming tools
// =============
typedef ValueInst* ValueType;
typedef std::list<ValueInst*> Values;
typedef std::list<ValueInst*>::const_iterator ValuesIt;
typedef std::list<NamedTyped*> Names;
typedef std::list<NamedTyped*>::const_iterator NamesIt;

// ==============
// Type checking
// ==============

inline bool isRealType(Typed::VarType type)
{
    return (type == Typed::kFloat || type == Typed::kFloatMacro || type == Typed::kDouble || type == Typed::kFixedPoint);
}

inline bool isIntType(Typed::VarType type)
{
    return (type == Typed::kInt32 || type == Typed::kInt64);
}

inline bool isInt32Type(Typed::VarType type)
{
    return (type == Typed::kInt32);
}

inline bool isInt64Type(Typed::VarType type)
{
    return (type == Typed::kInt64);
}

inline bool isFloatType(Typed::VarType type)
{
    return (type == Typed::kFloat);
}

inline bool isDoubleType(Typed::VarType type)
{
    return (type == Typed::kDouble);
}

inline bool isFixedPoint(Typed::VarType type)
{
    return (type == Typed::kFixedPoint);
}

inline bool isFloatMacroType(Typed::VarType type)
{
    return (type == Typed::kFloatMacro);
}

inline bool isBoolType(Typed::VarType type)
{
    return (type == Typed::kBool);
}

inline bool isIntPtrType(Typed::VarType type)
{
    return (type == Typed::kInt32_ptr || type == Typed::kInt64_ptr);
}

inline bool isRealPtrType(Typed::VarType type)
{
    return (type == Typed::kFloat_ptr
            || type == Typed::kFloat_ptr_ptr
            || type == Typed::kFloatMacro_ptr
            || type == Typed::kFloatMacro_ptr_ptr
            || type == Typed::kDouble_ptr
            || type == Typed::kDouble_ptr_ptr);
}

inline bool isPtrType(Typed::VarType type)
{
    return (isRealPtrType(type)
            || isIntPtrType(type)
            || type == Typed::kVoid_ptr
            || type == Typed::kObj_ptr
            || type == Typed::kSound_ptr);
}

inline bool isIntOrPtrType(Typed::VarType type)
{
    return isIntType(type) || isPtrType(type);
}

DeclareStructTypeInst* isStructType(const std::string& name);

// =========
// Visitors
// =========

struct InstVisitor : public virtual Garbageable {
    InstVisitor() {}
    virtual ~InstVisitor() {}

    // User interface
    virtual void visit(AddMetaDeclareInst* inst) {}
    virtual void visit(OpenboxInst* inst) {}
    virtual void visit(CloseboxInst* inst) {}
    virtual void visit(AddButtonInst* inst) {}
    virtual void visit(AddSliderInst* inst) {}
    virtual void visit(AddBargraphInst* inst) {}
    virtual void visit(AddSoundfileInst* inst) {}

    virtual void visit(LabelInst* inst) {}

    virtual void visit(Printable* inst) {}
    virtual void visit(NullValueInst* inst) {}
    virtual void visit(NullStatementInst* inst) {}

    // Declarations
    virtual void visit(DeclareVarInst* inst) {}
    virtual void visit(DeclareFunInst* inst) {}
    virtual void visit(DeclareStructTypeInst* inst) {}
    virtual void visit(DeclareBufferIterators* inst) {}

    // Memory
    virtual void visit(LoadVarInst* inst) {}
    virtual void visit(LoadVarAddressInst* inst) {}
    virtual void visit(TeeVarInst* inst) {}
    virtual void visit(StoreVarInst* inst) {}
    virtual void visit(ShiftArrayVarInst* inst) {}

    // Numbers
    virtual void visit(FloatNumInst* inst) {}
    virtual void visit(FloatArrayNumInst* inst) {}
    virtual void visit(Int32NumInst* inst) {}
    virtual void visit(Int64NumInst* inst) {}
    virtual void visit(Int32ArrayNumInst* inst) {}
    virtual void visit(BoolNumInst* inst) {}
    virtual void visit(DoubleNumInst* inst) {}
    virtual void visit(DoubleArrayNumInst* inst) {}
    virtual void visit(FixedPointNumInst* inst) {}
    virtual void visit(FixedPointArrayNumInst* inst) {}

    // Numerical computation
    virtual void visit(BinopInst* inst) {}

    // Cast
    virtual void visit(CastInst* inst) {}
    virtual void visit(BitcastInst* inst) {}

    // Function call
    virtual void visit(FunCallInst* inst) {}
    virtual void visit(RetInst* inst) {}
    virtual void visit(DropInst* inst) {}

    // Conditional
    virtual void visit(Select2Inst* inst) {}
    virtual void visit(ControlInst* inst) {}
    virtual void visit(IfInst* inst) {}
    virtual void visit(SwitchInst* inst) {}

    // Loops
    virtual void visit(ForLoopInst* inst) {}
    virtual void visit(SimpleForLoopInst* inst) {}
    virtual void visit(IteratorForLoopInst* inst) {}
    virtual void visit(WhileLoopInst* inst) {}

    // Block
    virtual void visit(BlockInst* inst) {}
 
    // Addresses
    virtual void visit(NamedAddress* address) {}
    virtual void visit(IndexedAddress* address) {}

    // Types
    virtual void visit(BasicTyped* typed) {}
    virtual void visit(NamedTyped* typed) {}
    virtual void visit(FixedTyped* typed) {}
    virtual void visit(FunTyped* typed) {}
    virtual void visit(ArrayTyped* typed) {}
    virtual void visit(StructTyped* typed) {}
    virtual void visit(VectorTyped* typed) {}
};

// =======================
// Clone a FIR expression
// =======================

struct CloneVisitor : public virtual Garbageable {
    CloneVisitor() {}
    virtual ~CloneVisitor() {}

    virtual ValueInst*     visit(NullValueInst* inst)     = 0;
    virtual StatementInst* visit(NullStatementInst* inst) = 0;

    // Declarations
    virtual StatementInst* visit(DeclareVarInst* inst)        = 0;
    virtual StatementInst* visit(DeclareFunInst* inst)        = 0;
    virtual StatementInst* visit(DeclareStructTypeInst* inst) = 0;
    virtual StatementInst* visit(DeclareBufferIterators* inst) = 0;

    // Memory
    virtual ValueInst*     visit(LoadVarInst* inst)        = 0;
    virtual ValueInst*     visit(LoadVarAddressInst* inst) = 0;
    virtual ValueInst*     visit(TeeVarInst* inst)         = 0;
    virtual StatementInst* visit(StoreVarInst* inst)       = 0;
    virtual StatementInst* visit(ShiftArrayVarInst* inst)  = 0;

    // Numbers
    virtual ValueInst* visit(Int32NumInst* inst)       = 0;
    virtual ValueInst* visit(Int32ArrayNumInst* inst)  = 0;
    virtual ValueInst* visit(Int64NumInst* inst)       = 0;
    virtual ValueInst* visit(FloatNumInst* inst)       = 0;
    virtual ValueInst* visit(FloatArrayNumInst* inst)  = 0;
    virtual ValueInst* visit(BoolNumInst* inst)        = 0;
    virtual ValueInst* visit(DoubleNumInst* inst)      = 0;
    virtual ValueInst* visit(DoubleArrayNumInst* inst) = 0;
    virtual ValueInst* visit(FixedPointNumInst* inst)      = 0;
    virtual ValueInst* visit(FixedPointArrayNumInst* inst) = 0;

    // Math Binop
    virtual ValueInst* visit(BinopInst* inst) = 0;

    // Cast
    virtual ValueInst* visit(CastInst* inst)    = 0;
    virtual ValueInst* visit(BitcastInst* inst) = 0;

    // Function call
    virtual ValueInst*     visit(FunCallInst* inst) = 0;
    virtual StatementInst* visit(RetInst* inst)     = 0;
    virtual StatementInst* visit(DropInst* inst)    = 0;

    // Conditional
    virtual ValueInst*     visit(Select2Inst* inst) = 0;
    virtual StatementInst* visit(ControlInst* inst) = 0;
    virtual StatementInst* visit(IfInst* inst)      = 0;
    virtual StatementInst* visit(SwitchInst* inst)  = 0;

    // Loops
    virtual StatementInst* visit(ForLoopInst* inst)       = 0;
    virtual StatementInst* visit(SimpleForLoopInst* inst) = 0;
    virtual StatementInst* visit(IteratorForLoopInst* inst) = 0;
    virtual StatementInst* visit(WhileLoopInst* inst)     = 0;

    // Block
    virtual StatementInst* visit(BlockInst* inst) = 0;

    // User interface
    virtual StatementInst* visit(AddMetaDeclareInst* inst) = 0;
    virtual StatementInst* visit(OpenboxInst* inst)        = 0;
    virtual StatementInst* visit(CloseboxInst* inst)       = 0;
    virtual StatementInst* visit(AddButtonInst* inst)      = 0;
    virtual StatementInst* visit(AddSliderInst* inst)      = 0;
    virtual StatementInst* visit(AddBargraphInst* inst)    = 0;
    virtual StatementInst* visit(AddSoundfileInst* inst)   = 0;
    virtual StatementInst* visit(LabelInst* inst)          = 0;
 
    // Addresses
    virtual Address* visit(NamedAddress* address)   = 0;
    virtual Address* visit(IndexedAddress* address) = 0;

    // Types
    virtual Typed* visit(BasicTyped* type)  = 0;
    virtual Typed* visit(NamedTyped* type)  = 0;
    virtual Typed* visit(FixedTyped* type)  = 0;
    virtual Typed* visit(FunTyped* type)    = 0;
    virtual Typed* visit(ArrayTyped* type)  = 0;
    virtual Typed* visit(StructTyped* type) = 0;
    virtual Typed* visit(VectorTyped* type) = 0;
};

// ============================
// Base class for instructions
// ============================

// Printable is defined in instructions_type.h

// Statement added in the compilation block
struct StatementInst : public Printable {
    virtual void accept(InstVisitor* visitor) = 0;

    virtual StatementInst* clone(CloneVisitor* cloner) = 0;

    virtual std::string getName() const { return ""; }
};

// Results from the compilation
struct ValueInst : public Printable {
    virtual void accept(InstVisitor* visitor) = 0;

    virtual ValueInst* clone(CloneVisitor* cloner) = 0;

    ValueInst() {}

    virtual int size() const { return 1; }

    virtual bool isSimpleValue() const { return false; }
};

// =======================
// Null value instruction
// =======================

struct NullValueInst : public ValueInst {
    NullValueInst() {}

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

// ===========================
// Null statement instruction
// ===========================

struct NullStatementInst : public StatementInst {
    NullStatementInst() {}

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

// =======
//  Types
// =======

// Base type is defined in instructions_type.h

struct BasicTyped : public Typed {
    const VarType fType;

    static void cleanup();

    BasicTyped(VarType type) : fType(type) {}

    VarType getType() const { return fType; }

    int getSizeBytes() const;  // moved in "instructions.cpp"

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
    
    virtual std::string toString() { return gTypeString[fType]; }
};

struct NamedTyped : public Typed {
    
    enum Attribute { kDefault, kNoalias };
    static std::vector<std::string> AttributeMap;
    
    const std::string fName;
    Typed* fType;

    NamedTyped(const std::string& name, Typed* type) : fName(name), fType(type) {}

    virtual ~NamedTyped() {}

    VarType getType() const { return fType->getType(); }
    
    std::string getName() const { return fName; }
    
    int getSizeBytes() const { return fType->getSizeBytes(); }

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
    
    virtual std::string toString() { return "[" + fName + "_" + fType->toString() + "]"; }
};

struct FixedTyped : public BasicTyped {
    
    int fMSB;
    int fLSB;
    bool fIsSigned;
    
    FixedTyped(int msb, int lsb, bool is_signed):BasicTyped(Typed::kFixedPoint), fMSB(msb), fLSB(lsb), fIsSigned(is_signed) {}
    
    virtual ~FixedTyped() {}
    
    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }
    
    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
    
    std::string toString() { return "[" + BasicTyped::toString() + "(" + std::to_string(fMSB) + "," + std::to_string(fLSB) + ")]"; }
};

struct FunTyped : public Typed {
    enum FunAttribute { kDefault = 0x1, kLocal = 0x2, kVirtual = 0x4, kStatic = 0x8, kStaticConstExpr = 0x10, kInline = 0x20 };

    Names         fArgsTypes;
    BasicTyped*   fResult;
    FunAttribute  fAttribute;

    FunTyped(const Names& args, BasicTyped* result, FunAttribute attribute = kDefault)
        : fArgsTypes(args), fResult(result), fAttribute(attribute)
    {
    }

    VarType getType() const { return fResult->getType(); }

    Typed* getTyped() { return fResult; }

    // Arguments type encoded as a string
    std::string toString()
    {
        std::string res, sep = "[";
        if (fArgsTypes.size() > 0) {
            for (const auto& it : fArgsTypes) {
                res += sep + gTypeString[it->getType()];
                sep =  ":";
            }
            res += "]";
        } else {
            res = "[void]";
        }
        return res;
    }
    
    // Check if 'name' is paired with another argument, like "fRec0" and "fRec0_tmp" when generating functions in -fun mode
    bool isPairedFunArg(const std::string& name)
    {
        for (const auto& it : fArgsTypes) {
            if (isPtrType(it->getType()) && (name != it->fName) && (startWith(it->fName, name) || startWith(name, it->fName))) return true;
        }
        return false;
    }

    int getSizeBytes() const;  // moved in "instructions.cpp"

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct ArrayTyped : public Typed {
    Typed*     fType;
    const int  fSize;   // Size of 0 is interpreted as a pointer on fType
   
    ArrayTyped(Typed* type, int size) : fType(type), fSize(size) {}

    virtual ~ArrayTyped() {}

    VarType getType() const { return getPtrFromType(fType->getType()); }

    int getSizeBytes() const;  // moved in "instructions.cpp"

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
    
    std::string toString() { return "[" + fType->toString() + "," + std::to_string(fSize) + "]"; }
};

struct StructTyped : public Typed {
    const std::string fName;
    std::vector<NamedTyped*> fFields;

    StructTyped(const std::string& name, const std::vector<NamedTyped*>& fields) : fName(name), fFields(fields) {}

    virtual ~StructTyped() {}

    VarType getType() const { return kObj_ptr; }
    VarType getType(int index) { return fFields[index]->getType(); }

    int getSizeBytes() const
    {
        int size = 0;
        for (const auto& it : fFields) {
            size += it->getSizeBytes();
        }
        return size;
    }

    int getOffset(int field) const
    {
        int offset = 0;
        for (int i = 0; i < field; i++) {
            offset += fFields[i]->getSizeBytes();
        }
        return offset;
    }

    std::string getName(int index) { return fFields[index]->fName; }

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
    
    std::string toString()
    {
        std::string res = "[";
        for (const auto& it : fFields) {
            res = res + it->toString() + ",";
        }
        res += "]";
        return res;
    }
};

struct VectorTyped : public Typed {
    BasicTyped* fType;
    const int  fSize;

    VectorTyped(BasicTyped* type, int size) : fType(type), fSize(size) {}

    virtual ~VectorTyped() {}

    VarType getType() const { return getVecFromType(fType->getType()); }

    int getSizeBytes() const { return fType->getSizeBytes() * fSize; }

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
    
    std::string toString() { return "[" + fType->toString() + std::to_string(fSize) + "]"; }
};

// Base class for number values
struct NumValueInst {};

// ===========
//  Addresses
// ===========

struct Address : public Printable {
    enum AccessType {
        kStruct       = 0x1,
        kStaticStruct = 0x2,  // Static shared variable between all DSPs
        kFunArgs      = 0x4,
        kStack        = 0x8,
        kGlobal       = 0x10,
        kLink         = 0x20,
        kLoop         = 0x40,
        kVolatile     = 0x80,
        kReference    = 0x100,  // Access by reference (for Rust backend)
        kMutable      = 0x200,  // Mutable access (for Rust backend)
        kConst        = 0x400   // Const access
    };

    Address() {}

    virtual void                setAccess(Address::AccessType access) = 0;
    virtual Address::AccessType getAccess() const                     = 0;
    
    bool isStack() { return getAccess() & kStack; }
    bool isLoop() { return getAccess() & kLoop; }
    bool isStruct() { return getAccess() & kStruct; }
    bool isFunArgs() { return getAccess() & kFunArgs; }
    bool isVolatile() { return getAccess() & kVolatile; }

    virtual void   setName(const std::string& name) = 0;
    virtual std::string getName() const             = 0;

    static void dump(AccessType access) { *fOut << dumpString(access); }

#define hasAccess(arg) res += (res != "") ? (std::string("|") + std::string(arg)) : std::string(arg);

    static std::string dumpString(AccessType access)
    {
        std::string res;
        if (access & kStruct) hasAccess("kStruct");
        if (access & kStaticStruct) hasAccess("kStaticStruct");
        if (access & kFunArgs) hasAccess("kFunArgs");
        if (access & kStack) hasAccess("kStack");
        if (access & kGlobal) hasAccess("kGlobal");
        if (access & kLink) hasAccess("kLink");
        if (access & kLoop) hasAccess("kLoop");
        if (access & kVolatile) hasAccess("kVolatile");
        if (access & kReference) hasAccess("kReference");
        if (access & kMutable) hasAccess("kMutable");
        if (access & kConst) hasAccess("kConst");
        return res;
    }

    virtual Address* clone(CloneVisitor* cloner) = 0;

    virtual void accept(InstVisitor* visitor) = 0;
};

struct NamedAddress : public Address {
    std::string fName;
    AccessType  fAccess;

    NamedAddress(const std::string& name, AccessType access) : fName(name), fAccess(access) {}

    void                setAccess(Address::AccessType access) { fAccess = access; }
    Address::AccessType getAccess() const { return fAccess; }

    void   setName(const std::string& name) { fName = name; }
    std::string getName() const { return fName; }

    Address* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }
};

struct IndexedAddress : public Address {
    Address*   fAddress;
    std::vector<ValueInst*> fIndices;

    IndexedAddress(Address* address, ValueInst* index) : fAddress(address)
    {
        fIndices.push_back(index);
    }
    
    IndexedAddress(Address* address, const std::vector<ValueInst*>& indices) : fAddress(address), fIndices(indices)
    {}

    virtual ~IndexedAddress() {}

    void                setAccess(Address::AccessType access) { fAddress->setAccess(access); }
    Address::AccessType getAccess() const { return fAddress->getAccess(); }

    void   setName(const std::string& name) { fAddress->setName(name); }
    std::string getName() const { return fAddress->getName(); }

    ValueInst* getIndex(int index = 0) const { return fIndices[index]; }
    std::vector<ValueInst*> getIndices() const { return fIndices; }
 
    Address* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }
};


// ===============
// User interface
// ===============

struct AddMetaDeclareInst : public StatementInst {
    const std::string fZone;
    const std::string fKey;
    const std::string fValue;

    AddMetaDeclareInst(const std::string& zone, const std::string& key, const std::string& value)
        : fZone(zone), fKey(key), fValue(value)
    {
    }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct OpenboxInst : public StatementInst {
    enum BoxType { kVerticalBox, kHorizontalBox, kTabBox };

    const std::string  fName;
    const BoxType fOrient;

    OpenboxInst(const std::string& name, BoxType orient) : fName(name), fOrient(orient) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct CloseboxInst : public StatementInst {
    CloseboxInst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct AddButtonInst : public StatementInst {
    enum ButtonType { kDefaultButton, kCheckButton };

    const std::string fLabel;
    const std::string fZone;
    const ButtonType fType;

    AddButtonInst(const std::string& label, const std::string& zone, ButtonType type) : fLabel(label), fZone(zone), fType(type) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct AddSliderInst : public StatementInst {
    enum SliderType { kHorizontal, kVertical, kNumEntry };

    const std::string fLabel;
    const std::string fZone;
    const double     fInit;
    const double     fMin;
    const double     fMax;
    const double     fStep;
    const SliderType fType;

    AddSliderInst(const std::string& label, const std::string& zone, double init, double min, double max, double step,
                  SliderType type)
        : fLabel(label), fZone(zone), fInit(init), fMin(min), fMax(max), fStep(step), fType(type)
    {
    }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct AddBargraphInst : public StatementInst {
    enum BargraphType { kHorizontal, kVertical };

    const std::string  fLabel;
    const std::string  fZone;
    const double       fMin;
    const double       fMax;
    const BargraphType fType;

    AddBargraphInst(const std::string& label, const std::string& zone, double min, double max, BargraphType type)
        : fLabel(label), fZone(zone), fMin(min), fMax(max), fType(type)
    {
    }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct AddSoundfileInst : public StatementInst {
    const std::string fLabel;
    const std::string fURL;
    const std::string fSFZone;

    AddSoundfileInst(const std::string& label, const std::string& url, const std::string& sf_zone)
        : fLabel(label), fURL(url), fSFZone(sf_zone)
    {
    }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct LabelInst : public StatementInst {
    const std::string fLabel;

    LabelInst(const std::string& label) : fLabel(label) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

// ====================
// Block of statements
// ====================

struct BlockInst : public StatementInst {
    std::list<StatementInst*> fCode;
    bool                      fIndent;
    
    BlockInst(std::list<StatementInst*> code) : fCode(code), fIndent(false) {}
    
    BlockInst() : fIndent(false) {}
    
    virtual ~BlockInst() {}
    
    void setIndent(bool indent) { fIndent = indent; }
    bool getIndent() { return fIndent; }
    
    void accept(InstVisitor* visitor) { visitor->visit(this); }
    
    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
    
    void pushFrontInst(StatementInst* inst) { faustassert(inst); fCode.push_front(inst); }
    
    void pushBackInst(StatementInst* inst) { faustassert(inst); fCode.push_back(inst); }
    
    void merge(BlockInst* inst)
    {
        for (const auto& it : inst->fCode) {
            fCode.push_back(it);
        }
    }
    
    int size() const { return int(fCode.size()); }
    
    bool hasReturn() const;
    ValueInst* getReturnValue();
};

// =============
// Declarations
// =============

struct DeclareVarInst : public StatementInst {
    Address*   fAddress;
    Typed*     fType;
    ValueInst* fValue;

    static void cleanup();

    DeclareVarInst(Address* address, Typed* typed, ValueInst* value);

    virtual ~DeclareVarInst() {}

    void                setAccess(Address::AccessType access) { fAddress->setAccess(access); }
    Address::AccessType getAccess() const  { return fAddress->getAccess(); }

    void   setName(const std::string& name) { fAddress->setName(name); }
    std::string getName() const { return fAddress->getName(); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    struct StoreVarInst* store(ValueInst* val);
    struct LoadVarInst*  load();
};

struct DeclareBufferIterators : public StatementInst {
    std::string fBufferName1;
    std::string fBufferName2;
    int         fChannels;
    Typed*      fType;
    bool        fMutable;

    DeclareBufferIterators(const std::string& name1, const std::string& name2, int channels, Typed* type, bool mut);
    
    virtual ~DeclareBufferIterators() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct DeclareFunInst : public StatementInst {
    const std::string fName;
    FunTyped*    fType;  // Describes type of all arguments and function result
    BlockInst*   fCode;  // Code is a list of StatementInst*
    
    DeclareFunInst(const std::string& name, FunTyped* type, BlockInst* code = new BlockInst());
    
    virtual ~DeclareFunInst() {}
    
    Typed::VarType getResType() { return fType->fResult->getType(); }
    
    void accept(InstVisitor* visitor) { visitor->visit(this); }
    
    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct DeclareStructTypeInst : public StatementInst {
    StructTyped* fType;
    
    DeclareStructTypeInst(StructTyped* type) : fType(type) {}
    
    virtual ~DeclareStructTypeInst() {}
    
    void accept(InstVisitor* visitor) { visitor->visit(this); }
    
    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

// ==============
// Memory access
// ==============

struct LoadVarInst : public ValueInst {
    Address* fAddress;

    LoadVarInst(Address* address) : ValueInst(), fAddress(address) {}

    virtual ~LoadVarInst() {}

    void   setName(const std::string& name) { fAddress->setName(name); }
    std::string getName() const { return fAddress->getName(); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual bool isSimpleValue() const;
};

struct LoadVarAddressInst : public ValueInst {
    Address* fAddress;

    LoadVarAddressInst(Address* address) : ValueInst(), fAddress(address) {}

    virtual ~LoadVarAddressInst() {}

    void   setName(const std::string& name) { fAddress->setName(name); }
    std::string getName() const { return fAddress->getName(); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual bool isSimpleValue() const { return dynamic_cast<NamedAddress*>(fAddress); }
};

// Special for wast/wasm backend : combine a store and a load
struct TeeVarInst : public ValueInst {
    Address*   fAddress;
    ValueInst* fValue;

    TeeVarInst(Address* address, ValueInst* value) : ValueInst(), fAddress(address), fValue(value) {}

    virtual ~TeeVarInst() {}

    void   setName(const std::string& name) { fAddress->setName(name); }
    std::string getName() const { return fAddress->getName(); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct StoreVarInst : public StatementInst {
    Address*   fAddress;
    ValueInst* fValue;

    StoreVarInst(Address* address, ValueInst* value) : fAddress(address), fValue(value) {}

    virtual ~StoreVarInst() {}

    void   setName(const std::string& name) { fAddress->setName(name); }
    std::string getName() const { return fAddress->getName(); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct ShiftArrayVarInst : public StatementInst {
    Address*  fAddress;
    const int fDelay;

    ShiftArrayVarInst(Address* address, int delay) : fAddress(address), fDelay(delay) {}

    virtual ~ShiftArrayVarInst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct DropInst : public StatementInst {
    ValueInst* fResult;
    
    DropInst(ValueInst* result = nullptr) : fResult(result) {}
    
    virtual ~DropInst() {}
    
    void accept(InstVisitor* visitor) { visitor->visit(this); }
    
    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

// ========
// Numbers
// ========

template <class TYPE>
struct ArrayNumInst : public ValueInst {
    std::vector<TYPE> fNumTable;
    
    ArrayNumInst(const std::vector<TYPE>& nums) : ValueInst(), fNumTable(nums) {}
    
    ArrayNumInst(int size) : ValueInst() { fNumTable.resize(size); }
    
    void setValue(int index, TYPE num) { fNumTable[index] = num; }
    TYPE getValue(int index) { return fNumTable[index]; }
    void addValue(TYPE num) { fNumTable.push_back(num); }
    
    void accept(InstVisitor* visitor) { visitor->visit(this); }
    
    virtual bool isSimpleValue() const { return true; }
};

struct FloatNumInst : public ValueInst, public NumValueInst {
    const float fNum;

    FloatNumInst(float num) : ValueInst(), fNum(num) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual bool isSimpleValue() const { return true; }
};

struct FloatArrayNumInst : public ArrayNumInst<float> {
    FloatArrayNumInst(const std::vector<float>& nums) : ArrayNumInst<float>(nums) {}
    FloatArrayNumInst(int size) : ArrayNumInst<float>(size) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct DoubleNumInst : public ValueInst, public NumValueInst {
    const double fNum;

    DoubleNumInst(double num) : ValueInst(), fNum(num) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual bool isSimpleValue() const { return true; }
};

struct DoubleArrayNumInst : public ArrayNumInst<double> {
    DoubleArrayNumInst(const std::vector<double>& nums) : ArrayNumInst<double>(nums) {}
    DoubleArrayNumInst(int size) : ArrayNumInst<double>(size) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct FixedPointNumInst : public ValueInst, public NumValueInst {
    const double fNum;
    
    FixedPointNumInst(double num) : ValueInst(), fNum(num) {}
    
    void accept(InstVisitor* visitor) { visitor->visit(this); }
    
    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
    
    virtual bool isSimpleValue() const { return true; }
};

struct FixedPointArrayNumInst : public ArrayNumInst<double> {
    FixedTyped* fType;
    FixedPointArrayNumInst(const std::vector<double>& nums, FixedTyped* type) : ArrayNumInst<double>(nums), fType(type) {}
    FixedPointArrayNumInst(int size, FixedTyped* type) : ArrayNumInst<double>(size), fType(type) {}
    
    void accept(InstVisitor* visitor) { visitor->visit(this); }
    
    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct Int32NumInst : public ValueInst, public NumValueInst {
    const int fNum;

    Int32NumInst(int num) : ValueInst(), fNum(num) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual bool isSimpleValue() const { return true; }
};

struct Int32ArrayNumInst : public ArrayNumInst<int> {
    Int32ArrayNumInst(const std::vector<int>& nums) : ArrayNumInst<int>(nums) {}
    Int32ArrayNumInst(int size) : ArrayNumInst<int>(size) {}
    
    void accept(InstVisitor* visitor) { visitor->visit(this); }
    
    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct Int64NumInst : public ValueInst, public NumValueInst {
    const int64_t fNum;

    Int64NumInst(int64_t num) : ValueInst(), fNum(num) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual bool isSimpleValue() const { return true; }
};

struct BoolNumInst : public ValueInst, public NumValueInst {
    const bool fNum;

    BoolNumInst(bool num) : ValueInst(), fNum(num) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual bool isSimpleValue() const { return true; }
};

// ===========
// Math Binop
// ===========

struct BinopInst : public ValueInst {
    const int  fOpcode;
    ValueInst* fInst1;
    ValueInst* fInst2;

    BinopInst(int opcode, ValueInst* inst1, ValueInst* inst2)
        : ValueInst(), fOpcode(opcode), fInst1(inst1), fInst2(inst2)
    {
    }

    virtual ~BinopInst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual int size() const { return fInst1->size() + fInst2->size(); }
};

// =====
// Cast
// =====

struct CastInst : public ValueInst {
    Typed*     fType;
    ValueInst* fInst;

    CastInst(ValueInst* inst, Typed* typed) : ValueInst(), fType(typed), fInst(inst) {}

    virtual ~CastInst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual int size() const { return fInst->size(); }
};

struct BitcastInst : public ValueInst {
    Typed*     fType;
    ValueInst* fInst;

    BitcastInst(ValueInst* inst, Typed* typed) : ValueInst(), fType(typed), fInst(inst) {}

    virtual ~BitcastInst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual int size() const { return fInst->size(); }
};

// =============
// Control flow
// =============

struct Select2Inst : public ValueInst {
    ValueInst* fCond;
    ValueInst* fThen;
    ValueInst* fElse;

    Select2Inst(ValueInst* cond_inst, ValueInst* then_inst, ValueInst* else_inst)
        : ValueInst(), fCond(cond_inst), fThen(then_inst), fElse(else_inst)
    {
    }

    virtual ~Select2Inst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual int size() const { return std::max(fThen->size(), fElse->size()); }
};

// Contains a condition (derived from 'enable/contol') and a statement to be computed if the cond is true
struct ControlInst : public StatementInst {
    ValueInst* fCond;
    StatementInst* fStatement;

    ControlInst(ValueInst* cond_inst, StatementInst* exp_inst)
    : fCond(cond_inst), fStatement(exp_inst)
    {
    }

    virtual ~ControlInst() {}

    // Test if (cond == fCond)
    bool hasCondition(ValueInst* cond);

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct IfInst : public StatementInst {
    ValueInst* fCond;
    BlockInst* fThen;
    BlockInst* fElse;

    IfInst(ValueInst* cond_inst, BlockInst* then_inst, BlockInst* else_inst)
        : fCond(cond_inst), fThen(then_inst), fElse(else_inst)
    {
    }

    IfInst(ValueInst* cond_inst, BlockInst* then_inst) : fCond(cond_inst), fThen(then_inst), fElse(new BlockInst()) {}

    virtual ~IfInst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct SwitchInst : public StatementInst {
    ValueInst*                   fCond;
    std::list<std::pair<int, BlockInst*> > fCode;

    SwitchInst(ValueInst* cond, const std::list<std::pair<int, BlockInst*> >& code) : fCond(cond), fCode(code) {}

    SwitchInst(ValueInst* cond) : fCond(cond) {}

    virtual ~SwitchInst() {}

    void addCase(int value, BlockInst* block) { fCode.push_back(std::make_pair(value, block)); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct FunCallInst : public ValueInst {
    const std::string fName;
    Values fArgs;  // List of arguments
    const bool       fMethod;

    FunCallInst(const std::string& name, const Values& args, bool method)
        : ValueInst(), fName(name), fArgs(args), fMethod(method)
    {
    }

    virtual ~FunCallInst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct RetInst : public StatementInst {
    ValueInst* fResult;
    
    RetInst(ValueInst* result = nullptr) : fResult(result) {}
    
    virtual ~RetInst() {}
    
    void accept(InstVisitor* visitor) { visitor->visit(this); }
    
    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

// ======
// Loops
// ======

struct ForLoopInst : public StatementInst {
    StatementInst* fInit;
    StatementInst* fIncrement;
    ValueInst*     fEnd;
    BlockInst*     fCode;
    const bool     fIsRecursive;

    ForLoopInst(StatementInst* init, ValueInst* end, StatementInst* increment, BlockInst* code, bool is_recursive)
        : fInit(init), fIncrement(increment), fEnd(end), fCode(code), fIsRecursive(is_recursive)
    {
    }

    virtual ~ForLoopInst() {}

    void pushFrontInst(StatementInst* inst) { faustassert(inst); fCode->pushFrontInst(inst); }

    void pushBackInst(StatementInst* inst) { faustassert(inst); fCode->pushBackInst(inst); }

    std::string getName() const { return fInit->getName(); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

// To be used for the Rust backend
struct SimpleForLoopInst : public StatementInst {
    StatementInst* fInit;
    ValueInst*   fUpperBound;
    ValueInst*   fLowerBound;
    const std::string fName;
    const bool   fReverse;
    BlockInst* fCode;

    SimpleForLoopInst(const std::string& name, ValueInst* upperBound, ValueInst* lowerBound, bool reverse, BlockInst* code);
   
    std::string getName() const { return fName; }

    virtual ~SimpleForLoopInst() {}

    void pushFrontInst(StatementInst* inst) { faustassert(inst); fCode->pushFrontInst(inst); }

    void pushBackInst(StatementInst* inst) { faustassert(inst); fCode->pushBackInst(inst); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct IteratorForLoopInst : public StatementInst {
    std::vector<NamedAddress*> fIterators;
    const bool                 fReverse;
    BlockInst*                 fCode;

    IteratorForLoopInst(const std::vector<NamedAddress*>& iterators, bool reverse, BlockInst* code)
        : fIterators(iterators), fReverse(reverse), fCode(code)
    {
    }

    virtual ~IteratorForLoopInst() {}

    void pushFrontInst(StatementInst* inst) { faustassert(inst); fCode->pushFrontInst(inst); }

    void pushBackInst(StatementInst* inst) { faustassert(inst); fCode->pushBackInst(inst); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct WhileLoopInst : public StatementInst {
    ValueInst* fCond;
    BlockInst* fCode;

    WhileLoopInst(ValueInst* cond, BlockInst* code) : fCond(cond), fCode(code) {}

    virtual ~WhileLoopInst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

// ====================
// Basic clone visitor
// ====================

class BasicCloneVisitor : public CloneVisitor {
   protected:
    // Used when inlining functions
    static std::stack<BlockInst*> fBlockStack;

   public:
    BasicCloneVisitor() {}

    virtual NullValueInst*     visit(NullValueInst* inst) { return new NullValueInst(); }
    virtual NullStatementInst* visit(NullStatementInst* inst) { return new NullStatementInst(); }

    // Declarations
    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        // To be sure args are evaluated in order
        Address* cloned_address = inst->fAddress->clone(this);
        Typed* cloned_type = inst->fType->clone(this);
        return new DeclareVarInst(cloned_address, cloned_type, ((inst->fValue) ? inst->fValue->clone(this) : nullptr));
    }
    virtual StatementInst* visit(DeclareFunInst* inst)
    {
        // To be sure args are evaluated in order
        FunTyped* cloned_fun = static_cast<FunTyped*>(inst->fType->clone(this));
        return new DeclareFunInst(inst->fName, cloned_fun, static_cast<BlockInst*>(inst->fCode->clone(this)));
    }
    virtual StatementInst* visit(DeclareStructTypeInst* inst)
    {
        return new DeclareStructTypeInst(static_cast<StructTyped*>(inst->fType->clone(this)));
    }
    virtual StatementInst* visit(DeclareBufferIterators* inst)
    {
        return new DeclareBufferIterators(inst->fBufferName1, inst->fBufferName2, inst->fChannels, inst->fType, inst->fMutable);
    }

    // Memory
    virtual ValueInst* visit(LoadVarInst* inst) { return new LoadVarInst(inst->fAddress->clone(this)); }
    virtual ValueInst* visit(LoadVarAddressInst* inst) { return new LoadVarAddressInst(inst->fAddress->clone(this)); }
    virtual ValueInst* visit(TeeVarInst* inst)
    {
        // To be sure args are evaluated in order
        Address* cloned_address = inst->fAddress->clone(this);
        ValueInst* cloned_value = inst->fValue->clone(this);
        return new TeeVarInst(cloned_address, cloned_value);
    }
    virtual StatementInst* visit(StoreVarInst* inst)
    {
        // To be sure args are evaluated in order
        Address* cloned_address = inst->fAddress->clone(this);
        ValueInst* cloned_value = inst->fValue->clone(this);
        return new StoreVarInst(cloned_address, cloned_value);
    }
    virtual StatementInst* visit(ShiftArrayVarInst* inst)
    {
        return new ShiftArrayVarInst(inst->fAddress->clone(this), inst->fDelay);
    }

    // Addresses
    virtual Address* visit(NamedAddress* address) { return new NamedAddress(address->fName, address->fAccess); }
    virtual Address* visit(IndexedAddress* address)
    {
        std::vector<ValueInst*> indices;
        for (const auto& it : address->fIndices) {
            indices.push_back(static_cast<ValueInst*>(it->clone(this)));
        }
        return new IndexedAddress(address->fAddress->clone(this), indices);
    }

    // Numbers
    virtual ValueInst* visit(FloatNumInst* inst) { return new FloatNumInst(inst->fNum); }
    virtual ValueInst* visit(FloatArrayNumInst* inst) { return new FloatArrayNumInst(inst->fNumTable); }
    virtual ValueInst* visit(Int32NumInst* inst) { return new Int32NumInst(inst->fNum); }
    virtual ValueInst* visit(Int64NumInst* inst) { return new Int64NumInst(inst->fNum); }
    virtual ValueInst* visit(Int32ArrayNumInst* inst) { return new Int32ArrayNumInst(inst->fNumTable); }
    virtual ValueInst* visit(BoolNumInst* inst) { return new BoolNumInst(inst->fNum); }
    virtual ValueInst* visit(DoubleNumInst* inst) { return new DoubleNumInst(inst->fNum); }
    virtual ValueInst* visit(DoubleArrayNumInst* inst) { return new DoubleArrayNumInst(inst->fNumTable); }
    virtual ValueInst* visit(FixedPointNumInst* inst) { return new FixedPointNumInst(inst->fNum); }
    virtual ValueInst* visit(FixedPointArrayNumInst* inst) { return new FixedPointArrayNumInst(inst->fNumTable, inst->fType); }

    // Numerical computation
    virtual ValueInst* visit(BinopInst* inst)
    {
        // To be sure args are evaluated in order
        ValueInst* cloned_arg1 = inst->fInst1->clone(this);
        ValueInst* cloned_arg2 = inst->fInst2->clone(this);
        return new BinopInst(inst->fOpcode, cloned_arg1, cloned_arg2);
    }

    // Cast
    virtual ValueInst* visit(CastInst* inst)
    {
        // To be sure args are evaluated in order
        ValueInst* cloned_value = inst->fInst->clone(this);
        Typed* cloned_type = inst->fType->clone(this);
        return new CastInst(cloned_value, cloned_type);
    }

    virtual ValueInst* visit(BitcastInst* inst)
    {
        // To be sure args are evaluated in order
        ValueInst* cloned_value = inst->fInst->clone(this);
        Typed* cloned_type = inst->fType->clone(this);
        return new BitcastInst(cloned_value, cloned_type);
    }

    // Function call
    virtual ValueInst* visit(FunCallInst* inst)
    {
        Values cloned_args;
        for (const auto& it : inst->fArgs) {
            cloned_args.push_back(it->clone(this));
        }
        return new FunCallInst(inst->fName, cloned_args, inst->fMethod);
    }
    
    virtual StatementInst* visit(RetInst* inst)
    {
        return new RetInst((inst->fResult) ? inst->fResult->clone(this) : nullptr);
    }
    
    virtual StatementInst* visit(DropInst* inst)
    {
        return new DropInst((inst->fResult) ? inst->fResult->clone(this) : nullptr);
    }

    // Conditional
    virtual ValueInst* visit(Select2Inst* inst)
    {
        ValueInst* cloned_then = inst->fThen->clone(this);
        ValueInst* cloned_else = inst->fElse->clone(this);
        ValueInst* cloned_cond = inst->fCond->clone(this);
        // cond_exp has to be evaluated last for FunctionInliner to correctly work in gHasTeeLocal mode
        return new Select2Inst(cloned_cond, cloned_then, cloned_else);
    }

    virtual StatementInst* visit(ControlInst* inst)
    {
        // To be sure args are evaluated in order
        ValueInst* cloned_cond = inst->fCond->clone(this);
        StatementInst* cloned_statement = inst->fStatement->clone(this);
        return new ControlInst(cloned_cond, cloned_statement);
    }

    virtual StatementInst* visit(IfInst* inst)
    {
        // To be sure args are evaluated in order
        ValueInst* cond_exp = inst->fCond->clone(this);
        BlockInst* then_exp = static_cast<BlockInst*>(inst->fThen->clone(this));
        BlockInst* else_exp = static_cast<BlockInst*>(inst->fElse->clone(this));
        return new IfInst(cond_exp, then_exp, else_exp);
    }
    virtual StatementInst* visit(SwitchInst* inst)
    {
        SwitchInst* cloned = new SwitchInst(inst->fCond->clone(this));
        for (const auto& it : inst->fCode) {
            cloned->addCase(it.first, static_cast<BlockInst*>((it.second)->clone(this)));
        }
        return cloned;
    }

    // Loop
    virtual StatementInst* visit(ForLoopInst* inst)
    {
        // To be sure args are evaluated in order
        StatementInst* cloned_init = inst->fInit->clone(this);
        ValueInst* cloned_end = inst->fEnd->clone(this);
        StatementInst* cloned_increment = inst->fIncrement->clone(this);
        return new ForLoopInst(cloned_init, cloned_end, cloned_increment,
                               static_cast<BlockInst*>(inst->fCode->clone(this)), inst->fIsRecursive);
    }

    virtual StatementInst* visit(SimpleForLoopInst* inst)
    {
        // To be sure args are evaluated in order
        ValueInst* cloned_upper = inst->fUpperBound->clone(this);
        ValueInst* cloned_lower = inst->fLowerBound->clone(this);
        return new SimpleForLoopInst(inst->fName, cloned_upper, cloned_lower,
                                     inst->fReverse, static_cast<BlockInst*>(inst->fCode->clone(this)));
    }

    virtual StatementInst* visit(IteratorForLoopInst* inst)
    {
        std::vector<NamedAddress*> iterators;
        for (const auto& it : inst->fIterators) {
            iterators.push_back(static_cast<NamedAddress*>(it->clone(this)));
        }
        return new IteratorForLoopInst(iterators, inst->fReverse, static_cast<BlockInst*>(inst->fCode->clone(this)));
    }

    virtual StatementInst* visit(WhileLoopInst* inst)
    {
        // To be sure args are evaluated in order
        ValueInst* cloned_cond = inst->fCond->clone(this);
        BlockInst* cloned_code = static_cast<BlockInst*>(inst->fCode->clone(this));
        return new WhileLoopInst(cloned_cond, cloned_code);
    }

    // Block
    virtual StatementInst* visit(BlockInst* inst)
    {
        // fBlockStack is used when inlining functions
        BlockInst* cloned = new BlockInst();
        fBlockStack.push(cloned);
        for (const auto& it : inst->fCode) {
            cloned->pushBackInst(it->clone(this));
        }
        fBlockStack.pop();
        return cloned;
    }

    // User interface
    virtual StatementInst* visit(AddMetaDeclareInst* inst)
    {
        return new AddMetaDeclareInst(inst->fZone, inst->fKey, inst->fValue);
    }
    virtual StatementInst* visit(OpenboxInst* inst) { return new OpenboxInst(inst->fName, inst->fOrient); }
    virtual StatementInst* visit(CloseboxInst* inst) { return new CloseboxInst(); }
    virtual StatementInst* visit(AddButtonInst* inst)
    {
        return new AddButtonInst(inst->fLabel, inst->fZone, inst->fType);
    }
    virtual StatementInst* visit(AddSliderInst* inst)
    {
        return new AddSliderInst(inst->fLabel, inst->fZone, inst->fInit, inst->fMin, inst->fMax, inst->fStep,
                                 inst->fType);
    }
    virtual StatementInst* visit(AddBargraphInst* inst)
    {
        return new AddBargraphInst(inst->fLabel, inst->fZone, inst->fMin, inst->fMax, inst->fType);
    }
    virtual StatementInst* visit(AddSoundfileInst* inst)
    {
        return new AddSoundfileInst(inst->fLabel, inst->fURL, inst->fSFZone);
    }
    virtual StatementInst* visit(LabelInst* inst) { return new LabelInst(inst->fLabel); }

    // Typed
    virtual Typed* visit(BasicTyped* typed);  // Moved in instructions.cpp
    virtual Typed* visit(NamedTyped* typed) { return new NamedTyped(typed->fName, typed->fType); }
    virtual Typed* visit(FixedTyped* typed) { return new FixedTyped(typed->fMSB, typed->fLSB, typed->fIsSigned); }
    virtual Typed* visit(FunTyped* typed)
    {
        Names cloned;
        for (const auto& it : typed->fArgsTypes) {
            cloned.push_back(static_cast<NamedTyped*>(it->clone(this)));
        }
        return new FunTyped(cloned, static_cast<BasicTyped*>(typed->fResult->clone(this)), typed->fAttribute);
    }
    virtual Typed* visit(ArrayTyped* typed)
    {
        return new ArrayTyped(typed->fType->clone(this), typed->fSize);
    }
    virtual Typed* visit(StructTyped* typed)
    {
        std::vector<NamedTyped*> cloned;
        for (const auto& it : typed->fFields) {
            cloned.push_back(static_cast<NamedTyped*>(it->clone(this)));
        }
        return new StructTyped(typed->fName, cloned);
    }

    virtual Typed* visit(VectorTyped* typed)
    {
        return new VectorTyped(static_cast<BasicTyped*>(typed->fType->clone(this)), typed->fSize);
    }
    
    // Return the cloned block, possibly refined in subclasses.
    virtual BlockInst* getCode(BlockInst* src) { return static_cast<BlockInst*>(src->clone(this)); }
    
};

// =======================
// Basic dispatch visitor
// =======================

struct DispatchVisitor : public InstVisitor {
    using InstVisitor::visit;

    virtual void visit(DeclareVarInst* inst)
    {
        inst->fAddress->accept(this);
        inst->fType->accept(this);
        if (inst->fValue) {
            inst->fValue->accept(this);
        }
    }

    virtual void visit(DeclareFunInst* inst)
    {
        if (inst->fCode) {
            inst->fCode->accept(this);
        }
    }

    virtual void visit(LoadVarInst* inst) { inst->fAddress->accept(this); }
    virtual void visit(LoadVarAddressInst* inst) { inst->fAddress->accept(this); }
    virtual void visit(TeeVarInst* inst)
    {
        inst->fAddress->accept(this);
        inst->fValue->accept(this);
    }
    virtual void visit(StoreVarInst* inst)
    {
        inst->fAddress->accept(this);
        inst->fValue->accept(this);
    }

    virtual void visit(ShiftArrayVarInst* inst) { inst->fAddress->accept(this); }

    virtual void visit(IndexedAddress* address)
    {
        address->fAddress->accept(this);
        for (const auto& it : address->fIndices) {
            it->accept(this);
        }
    }

    virtual void visit(BinopInst* inst)
    {
        inst->fInst1->accept(this);
        inst->fInst2->accept(this);
    }

    virtual void visit(CastInst* inst) { inst->fInst->accept(this); }

    virtual void visit(BitcastInst* inst) { inst->fInst->accept(this); }

    virtual void visit(FunCallInst* inst)
    {
        for (const auto& it : inst->fArgs) {
            it->accept(this);
        }
    }

    virtual void visit(RetInst* inst)
    {
        if (inst->fResult) {
            inst->fResult->accept(this);
        }
    }

    virtual void visit(DropInst* inst)
    {
        if (inst->fResult) {
            inst->fResult->accept(this);
        }
    }

    virtual void visit(Select2Inst* inst)
    {
        inst->fCond->accept(this);
        inst->fThen->accept(this);
        inst->fElse->accept(this);
    }

    virtual void visit(ControlInst* inst)
    {
        inst->fCond->accept(this);
        inst->fStatement->accept(this);
    }

    virtual void visit(IfInst* inst)
    {
        inst->fCond->accept(this);
        inst->fThen->accept(this);
        inst->fElse->accept(this);
    }

    virtual void visit(ForLoopInst* inst)
    {
        inst->fInit->accept(this);
        inst->fEnd->accept(this);
        inst->fIncrement->accept(this);
        inst->fCode->accept(this);
    }

    virtual void visit(SimpleForLoopInst* inst)
    {
        inst->fInit->accept(this);
        inst->fUpperBound->accept(this);
        inst->fLowerBound->accept(this);
        inst->fCode->accept(this);
    }

    virtual void visit(IteratorForLoopInst* inst)
    {
        for (const auto& it : inst->fIterators) {
            it->accept(this);
        }
        inst->fCode->accept(this);
    }

    virtual void visit(WhileLoopInst* inst)
    {
        inst->fCond->accept(this);
        inst->fCode->accept(this);
    }

    virtual void visit(SwitchInst* inst)
    {
        inst->fCond->accept(this);
        for (const auto& it : inst->fCode) {
            (it.second)->accept(this);
        }
    }

    virtual void visit(BlockInst* inst)
    {
        for (const auto& it : inst->fCode) {
            it->accept(this);
        }
    }

    // Typed
    virtual void visit(FunTyped* typed)
    {
        typed->fResult->accept(this);
        for (const auto& it : typed->fArgsTypes) {
            it->accept(this);
        }
    }
    virtual void visit(ArrayTyped* typed) { typed->fType->accept(this); }
    virtual void visit(StructTyped* typed)
    {
        for (const auto& it : typed->fFields) {
            it->accept(this);
        }
    }

    virtual void visit(VectorTyped* typed) { typed->fType->accept(this); }
};

struct VariableScopeVisitor : public DispatchVisitor {
    std::stack<std::list<DeclareVarInst*> > fBlockVarTable;

    VariableScopeVisitor() {}

    virtual void visit(DeclareVarInst* inst)
    {
        fBlockVarTable.top().push_back(inst);
        DispatchVisitor::visit(inst);
    }

    virtual void visit(BlockInst* inst)
    {
        std::list<DeclareVarInst*> variable_block;
        fBlockVarTable.push(variable_block);
        DispatchVisitor::visit(inst);
        fBlockVarTable.pop();
    }
};

class ScalVecDispatcherVisitor : public DispatchVisitor {
   protected:
    InstVisitor* fScalarVisitor;
    InstVisitor* fVectorVisitor;

    void Dispatch2Visitor(ValueInst* inst);

   public:
    using DispatchVisitor::visit;

    ScalVecDispatcherVisitor(InstVisitor* scal, InstVisitor* vec) : fScalarVisitor(scal), fVectorVisitor(vec) {}

    ~ScalVecDispatcherVisitor()
    {
        delete fScalarVisitor;
        delete fVectorVisitor;
    }

    virtual void visit(LoadVarInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(LoadVarAddressInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(TeeVarInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(StoreVarInst* inst)
    {
        /*
        if (inst->fValue->fSize == 1) {
            fScalarVisitor->visit(inst);
        } else {
            fVectorVisitor->visit(inst);
        }
        */

        fScalarVisitor->visit(inst);
    }

    virtual void visit(ShiftArrayVarInst* inst) { fScalarVisitor->visit(inst); }

    virtual void visit(FloatNumInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(FloatArrayNumInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(Int32NumInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(Int64NumInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(BoolNumInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(DoubleNumInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(DoubleArrayNumInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(FixedPointNumInst* inst) { Dispatch2Visitor(inst); }
    
    virtual void visit(FixedPointArrayNumInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(BinopInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(CastInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(BitcastInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(FunCallInst* inst) { Dispatch2Visitor(inst); }

    virtual void visit(Select2Inst* inst) { Dispatch2Visitor(inst); }

};

// ===================
// Combining visitors
// ===================

class CombinerVisitor : public DispatchVisitor {
   protected:
    InstVisitor* fVisitor1;
    InstVisitor* fVisitor2;
    InstVisitor* fCurVisitor;

   public:
    CombinerVisitor(InstVisitor* v1, InstVisitor* v2) : fVisitor1(v1), fVisitor2(v2) { fCurVisitor = v1; }

    virtual ~CombinerVisitor() {}
};

// ======================
// Instruction generator
// ======================

#define castInt32(e) dynamic_cast<Int32NumInst*>(e)
#define castInt64(e) dynamic_cast<Int64NumInst*>(e)
#define castFloat(e) dynamic_cast<FloatNumInst*>(e)
#define castDouble(e) dynamic_cast<DoubleNumInst*>(e)
#define castFixed(e) dynamic_cast<FixedPointNumInst*>(e)

struct InstBuilder {
    // User interface
    static AddMetaDeclareInst* genAddMetaDeclareInst(const std::string& zone, const std::string& key, const std::string& value)
    {
        return new AddMetaDeclareInst(zone, key, value);
    }

    static OpenboxInst* genOpenboxInst(const std::string& name, OpenboxInst::BoxType orient)
    {
        faustassert(orient >= OpenboxInst::kVerticalBox && orient <= OpenboxInst::kTabBox);
        return new OpenboxInst(name, orient);
    }

    static CloseboxInst* genCloseboxInst() { return new CloseboxInst(); }

    static AddButtonInst* genAddButtonInst(const std::string& label, const std::string& zone)
    {
        return new AddButtonInst(label, zone, AddButtonInst::kDefaultButton);
    }

    static AddButtonInst* genAddCheckbuttonInst(const std::string& label, const std::string& zone)
    {
        return new AddButtonInst(label, zone, AddButtonInst::kCheckButton);
    }

    static AddSliderInst* genAddHorizontalSliderInst(const std::string& label, const std::string& zone, double init, double min, double max, double step)
    {
        return new AddSliderInst(label, zone, init, min, max, step, AddSliderInst::kHorizontal);
    }

    static AddSliderInst* genAddVerticalSliderInst(const std::string& label, const std::string& zone, double init, double min, double max, double step)
    {
        return new AddSliderInst(label, zone, init, min, max, step, AddSliderInst::kVertical);
    }

    static AddSliderInst* genAddNumEntryInst(const std::string& label, const std::string& zone, double init, double min, double max, double step)
    {
        return new AddSliderInst(label, zone, init, min, max, step, AddSliderInst::kNumEntry);
    }

    static AddBargraphInst* genAddHorizontalBargraphInst(const std::string& label, const std::string& zone, double min, double max)
    {
        return new AddBargraphInst(label, zone, min, max, AddBargraphInst::kHorizontal);
    }

    static AddBargraphInst* genAddVerticalBargraphInst(const std::string& label, const std::string& zone, double min, double max)
    {
        return new AddBargraphInst(label, zone, min, max, AddBargraphInst::kVertical);
    }

    static AddSoundfileInst* genAddSoundfileInst(const std::string& label, const std::string& url, const std::string& sf_zone)
    {
        return new AddSoundfileInst(label, url, sf_zone);
    }

    static LabelInst* genLabelInst(const std::string& label) { return new LabelInst(label); }

    // Null instruction
    static NullValueInst*     genNullValueInst() { return new NullValueInst(); }
    static NullStatementInst* genNullStatementInst() { return new NullStatementInst(); }

    // Declarations
    static DeclareVarInst* genDeclareVarInst(Address* address, Typed* typed, ValueInst* value = nullptr)
    {
        return new DeclareVarInst(address, typed, value);
    }

    static DeclareFunInst* genDeclareFunInst(const std::string& name, FunTyped* typed, BlockInst* code)
    {
        return new DeclareFunInst(name, typed, code);
    }
    static DeclareFunInst* genDeclareFunInst(const std::string& name, FunTyped* typed)
    {
        return new DeclareFunInst(name, typed);
    }

    static DeclareStructTypeInst* genDeclareStructTypeInst(StructTyped* type)
    {
        return new DeclareStructTypeInst(type);
    }

    static DeclareBufferIterators* genDeclareBufferIterators(const std::string& name1, const std::string& name2, int channels, Typed* type, bool mut)
    {
        return new DeclareBufferIterators(name1, name2, channels, type, mut);
    }

    // Memory
    static LoadVarInst*        genLoadVarInst(Address* address) { return new LoadVarInst(address); }
    static LoadVarAddressInst* genLoadVarAddressInst(Address* address) { return new LoadVarAddressInst(address); }
    static TeeVarInst*         genTeeVar(const std::string& vname, ValueInst* value)
    {
        return new TeeVarInst(InstBuilder::genNamedAddress(vname, Address::kStack), value);
    }
    static StoreVarInst* genStoreVarInst(Address* address, ValueInst* value)
    {
        return new StoreVarInst(address, value);
    }
    static ShiftArrayVarInst* genShiftArrayVarInst(Address* address, int delay)
    {
        return new ShiftArrayVarInst(address, delay);
    }

    // Numbers
    static Int32NumInst*       genInt32NumInst(int num) { return new Int32NumInst(num); }
    static Int32ArrayNumInst*  genInt32ArrayNumInst(int num) { return new Int32ArrayNumInst(num); }
    static FloatNumInst*       genFloatNumInst(float num) { return new FloatNumInst(num); }
    static FloatArrayNumInst*  genFloatArrayNumInst(int size) { return new FloatArrayNumInst(size); }
    static DoubleNumInst*      genDoubleNumInst(double num) { return new DoubleNumInst(num); }
    static DoubleArrayNumInst* genDoubleArrayNumInst(int size) { return new DoubleArrayNumInst(size); }
    static FixedPointNumInst*       genFixedPointNumInst(double num) { return new FixedPointNumInst(num); }
    static FixedPointArrayNumInst*  genFixedPointArrayNumInst(int size, FixedTyped* type) { return new FixedPointArrayNumInst(size, type); }
    static DoubleNumInst*      genQuadNumInst(double num) { return new DoubleNumInst(num); }  // Use DoubleNumInst

    static ValueInst* genTypedNum(Typed::VarType type, double num);
    static ValueInst* genTypedZero(Typed::VarType type);
    static ValueInst* genTypedZero(BasicTyped* type) { return genTypedZero(type->getType()); }
    static ValueInst* genRealNumInst(Typed::VarType ctype, double num);
   
    static ValueInst* genArrayNumInst(Typed::VarType ctype, int size, FixedTyped* type = nullptr)
    {
        if (ctype == Typed::kInt32) {
            return new Int32ArrayNumInst(size);
        } else if (ctype == Typed::kFloat) {
            return new FloatArrayNumInst(size);
        } else if (ctype == Typed::kDouble) {
            return new DoubleArrayNumInst(size);
        } else if (ctype == Typed::kFixedPoint) {
            return new FixedPointArrayNumInst(size, type);
        } else {
            faustassert(false);
        }
        return nullptr;
    }

    static Int64NumInst* genInt64NumInst(int64_t num) { return new Int64NumInst(num); }
    static BoolNumInst*  genBoolNumInst(bool num) { return new BoolNumInst(num); }

    // Numerical computation
    static BinopInst* genBinopInst(int opcode, ValueInst* inst1, ValueInst* inst2)
    {
        return new BinopInst(opcode, inst1, inst2);
    }

    static ValueInst* genCastInst(ValueInst* inst, Typed* typed_ext)
    {
        return new CastInst(inst, typed_ext);
    }

    static ValueInst* genBitcastInst(ValueInst* inst, Typed* typed) { return new BitcastInst(inst, typed); }
    // Cast float/double/quad
    static ValueInst* genCastRealInst(ValueInst* inst);
    static ValueInst* genCastFloatMacroInst(ValueInst* inst);
    static ValueInst* genCastInt32Inst(ValueInst* inst);
    
    // Control flow
    static RetInst*  genRetInst(ValueInst* result = nullptr) { return new RetInst(result); }
    static DropInst* genDropInst(ValueInst* result = nullptr) { return new DropInst(result); }

    // Conditional
    static Select2Inst* genSelect2Inst(ValueInst* cond_inst, ValueInst* then_inst, ValueInst* else_inst)
    {
        return new Select2Inst(cond_inst, then_inst, else_inst);
    }

    static StatementInst* genControlInst(ValueInst* cond_inst, StatementInst* exp_inst)
    {
        // If called with a NullValueInst, then the exp_inst is going to be always computed
        return (dynamic_cast<NullValueInst*>(cond_inst)) ? exp_inst : new ControlInst(cond_inst, exp_inst);
    }

    static IfInst* genIfInst(ValueInst* cond_inst, BlockInst* then_inst, BlockInst* else_inst)
    {
        return new IfInst(cond_inst, then_inst, else_inst);
    }
    static IfInst* genIfInst(ValueInst* cond_inst, BlockInst* then_inst) { return new IfInst(cond_inst, then_inst); }
    static SwitchInst* genSwitchInst(ValueInst* cond) { return new SwitchInst(cond); }

    // Function management
    static FunCallInst* genFunCallInst(const std::string& name, const Values& args)
    {
        return new FunCallInst(name, args, false);
    }
    static FunCallInst* genFunCallInst(const std::string& name, const Values& args, bool method)
    {
        return new FunCallInst(name, args, method);
    }
    static DropInst* genVoidFunCallInst(const std::string& name, const Values& args)
    {
        return new DropInst(new FunCallInst(name, args, false));
    }
    static DropInst* genVoidFunCallInst(const std::string& name, const Values& args, bool method)
    {
        return new DropInst(new FunCallInst(name, args, method));
    }

    // Loop
    static ForLoopInst* genForLoopInst(StatementInst* init, ValueInst* end, StatementInst* increment,
                                       BlockInst* code = new BlockInst(), bool is_recursive = false)
    {
        faustassert(dynamic_cast<DeclareVarInst*>(init) || dynamic_cast<StoreVarInst*>(init));
        return new ForLoopInst(init, end, increment, code, is_recursive);
    }

    // TODO: add access to the loop variable, generate ascending/descending loops...
    static ForLoopInst* genForLoopInst(const std::string& index, int init, int size, int step = 1)
    {
        DeclareVarInst* dec = genDecLoopVar(index, genInt32Typed(), genInt32NumInst(init));
        ValueInst*      end = genLessThan(dec->load(), genInt32NumInst(size));
        StoreVarInst*   inc = dec->store(genAdd(dec->load(), step));
        return genForLoopInst(dec, end, inc);
    }

    // Used for Rust backend
    static SimpleForLoopInst* genSimpleForLoopInst(const std::string& name, ValueInst* upperBound,
                                                   ValueInst* lowerBound = new Int32NumInst(0), bool reverse = false,
                                                   BlockInst* code = new BlockInst())
    {
        faustassert(castInt32(upperBound) || dynamic_cast<LoadVarInst*>(upperBound));
        faustassert(castInt32(lowerBound) || dynamic_cast<LoadVarInst*>(lowerBound));
        return new SimpleForLoopInst(name, upperBound, lowerBound, reverse, code);
    }
    static IteratorForLoopInst* genIteratorForLoopInst(const std::vector<NamedAddress*>& iterators, bool reverse = false,
                                                       BlockInst* code = new BlockInst())
    {
        return new IteratorForLoopInst(iterators, reverse, code);
    }

    static WhileLoopInst* genWhileLoopInst(ValueInst* cond, BlockInst* code) { return new WhileLoopInst(cond, code); }

    static BlockInst* genBlockInst(const std::list<StatementInst*>& code) { return new BlockInst(code); }
    static BlockInst* genBlockInst() { return new BlockInst(); }

    // Types
    static BasicTyped* genBasicTyped(Typed::VarType type);  // moved in instructions.cpp

    static BasicTyped* genInt32Typed() { return genBasicTyped(Typed::kInt32); }
    static BasicTyped* genInt64Typed() { return genBasicTyped(Typed::kInt64); }
    static BasicTyped* genVoidTyped() { return genBasicTyped(Typed::kVoid); }
    static BasicTyped* genFloatTyped() { return genBasicTyped(Typed::kFloat); }
    static BasicTyped* genDoubleTyped() { return genBasicTyped(Typed::kDouble); }
    
    static BasicTyped* genFloatMacroTyped() { return genBasicTyped(Typed::kFloatMacro); }
    static BasicTyped* genItFloatTyped();

    static NamedTyped* genNamedTyped(const std::string& name, Typed* type);
    static NamedTyped* genNamedTyped(const std::string& name, Typed::VarType type);
    
    static FixedTyped* genFixedTyped(int msb, int lsb, bool is_signed = true) { return new FixedTyped(msb, lsb, is_signed); }

    static FunTyped* genFunTyped(const Names& args, BasicTyped* result,
                                 FunTyped::FunAttribute attribute = FunTyped::kDefault)
    {
        return new FunTyped(args, result, attribute);
    }
    static VectorTyped* genVectorTyped(BasicTyped* type, int size) { return new VectorTyped(type, size); }
    static ArrayTyped* genArrayTyped(Typed* type, int size)
    {
        return new ArrayTyped(type, size);
    }
    static StructTyped* genStructTyped(const std::string& name, const std::vector<NamedTyped*>& fields)
    {
        return new StructTyped(name, fields);
    }

    // Addresses
    static NamedAddress* genNamedAddress(const std::string& name, Address::AccessType access)
    {
        return new NamedAddress(name, access);
    }
    static IndexedAddress* genIndexedAddress(Address* address, ValueInst* index)
    {
        return new IndexedAddress(address, index);
    }
    
    static IndexedAddress* genIndexedAddress(Address* address, const std::vector<ValueInst*>& indices)
    {
        return new IndexedAddress(address, indices);
    }

    // Helper build methods
    static DeclareVarInst* genDecArrayVar(const std::string& vname, Address::AccessType access, Typed* type, int size)
    {
        return genDeclareVarInst(genNamedAddress(vname, access), genArrayTyped(type, size));
    }

    static LoadVarInst* genLoadArrayVar(const std::string& vname, Address::AccessType access, ValueInst* index)
    {
        return genLoadVarInst(genIndexedAddress(genNamedAddress(vname, access), index));
    }
    
    // Actually same as genLoadArrayVar
    static LoadVarInst* genLoadStructPtrVar(const std::string& vname, Address::AccessType access, ValueInst* index)
    {
        return genLoadArrayVar(vname, access, index);
    }

    static StoreVarInst* genStoreArrayVar(const std::string& vname, Address::AccessType access, ValueInst* index,
                                          ValueInst* exp)
    {
        return genStoreVarInst(genIndexedAddress(genNamedAddress(vname, access), index), exp);
    }

    // Struct variable
    static DeclareVarInst* genDecStructVar(const std::string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, Address::kStruct), type, exp);
    }

    static DeclareVarInst* genDecVolatileStructVar(const std::string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, (Address::AccessType)(Address::kStruct | Address::kVolatile)),
                                 type, exp);
    }

    static DeclareVarInst* genDecArrayStructVar(const std::string& vname, Typed* type, int size)
    {
        return genDecArrayVar(vname, Address::kStruct, type, size);
    }

    static LoadVarInst* genLoadStructVar(const std::string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kStruct));
    }

    static LoadVarInst* genLoadMutRefStructVar(const std::string& vname)
    {
        return genLoadVarInst(
            genNamedAddress(vname, (Address::AccessType)(Address::kStruct | Address::kReference | Address::kMutable)));
    }

    static LoadVarInst* genVolatileLoadStructVar(const std::string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, (Address::AccessType)(Address::kStruct | Address::kVolatile)));
    }
    
    template <typename Iterator>
    static LoadVarInst* genLoadArrayVar(const std::string& vname, Address::AccessType access, Iterator begin, Iterator end)
    {
        Address* address = genNamedAddress(vname, access);
        std::vector<ValueInst*> indices;
        for (Iterator it = begin; it != end; ++it) {
            indices.push_back(*it);
        }
        address = genIndexedAddress(address, indices);
    
        return genLoadVarInst(address);
    }

    template <typename Iterator>
    static LoadVarInst* genLoadArrayStructVar(const std::string& vname, Iterator indexBegin, Iterator indexEnd)
    {
        return genLoadArrayVar(vname, Address::kStruct, indexBegin, indexEnd);
    }

    static LoadVarInst* genLoadArrayStructVar(const std::string& vname, ValueInst* index)
    {
        std::vector<ValueInst*> indices = { index };
        return genLoadArrayStructVar(vname, indices.begin(), indices.end());
    }
    
    static LoadVarInst* genLoadArrayStructVar(const std::string& vname, const std::vector<ValueInst*>& indices)
    {
        return genLoadArrayStructVar(vname, indices.begin(), indices.end());
    }

    static LoadVarInst* genLoadArrayStructVar(const std::string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kStruct));
    }

    static LoadVarAddressInst* genLoadArrayStructVarAddress(const std::string& vname, ValueInst* index)
    {
        return genLoadVarAddressInst(genIndexedAddress(genNamedAddress(vname, Address::kStruct), index));
    }

    static StoreVarInst* genStoreStructVar(const std::string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kStruct), exp);
    }

    static StoreVarInst* genVolatileStoreStructVar(const std::string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, (Address::AccessType)(Address::kStruct | Address::kVolatile)),
                               exp);
    }

    
    template <typename Iterator>
    static StoreVarInst* genStoreArrayVar(const std::string& vname,
                                          ValueInst* exp,
                                          Address::AccessType access,
                                          Iterator begin,
                                          Iterator end)
    {
        Address* address = genNamedAddress(vname, access);
        std::vector<ValueInst*> indices;
        for (Iterator it = begin; it != end; ++it) {
            indices.push_back(*it);
        }
        address = genIndexedAddress(address, indices);
                
        return genStoreVarInst(address, exp);
    }

    template <typename Iterator>
    static StoreVarInst* genStoreArrayStructVar(const std::string& vname,
                                                ValueInst* exp,
                                                Iterator indexBegin,
                                                Iterator indexEnd)
    {
        return genStoreArrayVar(vname, exp, Address::kStruct, indexBegin, indexEnd);
    }

    static StoreVarInst* genStoreArrayStructVar(const std::string& vname, ValueInst* index, ValueInst* exp)
    {
        std::vector<ValueInst*> indices = {index};
        return genStoreArrayStructVar(vname, exp, indices.begin(), indices.end());
    }

    static StoreVarInst* genStoreArrayStructVar(const std::string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kStruct), exp);
    }

    // Static struct variable
    static DeclareVarInst* genDecStaticStructVar(const std::string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, Address::kStaticStruct), type, exp);
    }

    static DeclareVarInst* genDecConstStaticStructVar(const std::string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(
            genNamedAddress(vname, (Address::AccessType)(Address::kStaticStruct | Address::kConst)), type, exp);
    }

    static LoadVarInst* genLoadStaticStructVar(const std::string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kStaticStruct));
    }

    static LoadVarInst* genLoadStaticMutRefStructVar(const std::string& vname)
    {
        return genLoadVarInst(genNamedAddress(
            vname, (Address::AccessType)(Address::kStaticStruct | Address::kReference | Address::kMutable)));
    }

    static StoreVarInst* genStoreStaticStructVar(const std::string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kStaticStruct), exp);
    }

    template <typename Iterator>
    static LoadVarInst* genLoadArrayStaticStructVar(const std::string& vname, Iterator indexBegin, Iterator indexEnd)
    {
        return genLoadArrayVar(vname, Address::kStaticStruct, indexBegin, indexEnd);
    }

    static LoadVarInst* genLoadArrayStaticStructVar(const std::string& vname, ValueInst* index)
    {
        std::vector<ValueInst*> indices = {index};
        return genLoadArrayStaticStructVar(vname, indices.begin(), indices.end());
    }

    template <typename Iterator>
    static StoreVarInst* genStoreArrayStaticStructVar(const std::string& vname, ValueInst* exp, Iterator indexBegin,
                                                      Iterator indexEnd)
    {
        return genStoreArrayVar(vname, exp, Address::kStaticStruct, indexBegin, indexEnd);
    }

    static StoreVarInst* genStoreArrayStaticStructVar(const std::string& vname, ValueInst* index, ValueInst* exp)
    {
        std::vector<ValueInst*> indices = {index};
        return genStoreArrayStructVar(vname, exp, indices.begin(), indices.end());
    }

    // Stack variable
    static DeclareVarInst* genDecStackVar(const std::string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, Address::kStack), type, exp);
    }

    static DeclareVarInst* genDecArrayStackVar(const std::string& vname, Typed* type, int size)
    {
        return genDecArrayVar(vname, Address::kStack, type, size);
    }

    static LoadVarInst* genLoadStackVar(const std::string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kStack));
    }

    static LoadVarAddressInst* genLoadStackVarAddress(const std::string& vname)
    {
        return genLoadVarAddressInst(genNamedAddress(vname, Address::kStack));
    }

    static LoadVarInst* genLoadArrayStackVar(const std::string& vname, ValueInst* index)
    {
        return genLoadVarInst(genIndexedAddress(genNamedAddress(vname, Address::kStack), index));
    }

    static LoadVarAddressInst* genLoadArrayStackVarAddress(const std::string& vname, ValueInst* index)
    {
        return genLoadVarAddressInst(genIndexedAddress(genNamedAddress(vname, Address::kStack), index));
    }

    static StoreVarInst* genStoreStackVar(const std::string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kStack), exp);
    }

    static StoreVarInst* genStoreArrayStackVar(const std::string& vname, ValueInst* index, ValueInst* exp)
    {
        return genStoreVarInst(genIndexedAddress(genNamedAddress(vname, Address::kStack), index), exp);
    }

    // Loop variable
    static DeclareVarInst* genDecLoopVar(const std::string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, Address::kLoop), type, exp);
    }

    static LoadVarInst* genLoadLoopVar(const std::string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kLoop));
    }

    static StoreVarInst* genStoreLoopVar(const std::string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kLoop), exp);
    }

    // FunArgs variable
    static LoadVarInst* genLoadFunArgsVar(const std::string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kFunArgs));
    }

    static LoadVarInst* genLoadArrayFunArgsVar(const std::string& vname, ValueInst* index)
    {
        return genLoadVarInst(genIndexedAddress(genNamedAddress(vname, Address::kFunArgs), index));
    }

    static StoreVarInst* genStoreArrayFunArgsVar(const std::string& vname, ValueInst* index, ValueInst* exp)
    {
        return genStoreVarInst(genIndexedAddress(genNamedAddress(vname, Address::kFunArgs), index), exp);
    }

    // Global variable
    static DeclareVarInst* genDecGlobalVar(const std::string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, Address::kGlobal), type, exp);
    }

    static DeclareVarInst* genDecConstGlobalVar(const std::string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, (Address::AccessType)(Address::kGlobal | Address::kConst)),
                                 type, exp);
    }

    static LoadVarInst* genLoadGlobalVar(const std::string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kGlobal));
    }

    static StoreVarInst* genStoreGlobalVar(const std::string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kGlobal), exp);
    }
    
    static bool isZero(ValueInst* val)
    {
        return (castInt32(val) && castInt32(val)->fNum == 0)
            || (castInt64(val) && castInt64(val)->fNum == 0)
            || (castFloat(val) && castFloat(val)->fNum == 0.f)
            || (castDouble(val) && castDouble(val)->fNum == 0.)
            || (castFixed(val) && castFixed(val)->fNum == 0.);
    }
    
    static bool isOne(ValueInst* val)
    {
        return (castInt32(val) && castInt32(val)->fNum == 1)
            || (castInt64(val) && castInt64(val)->fNum == 1)
            || (castFloat(val) && castFloat(val)->fNum == 1.f)
            || (castDouble(val) && castDouble(val)->fNum == 1.)
            || (castFixed(val) && castFixed(val)->fNum == 1.);
    }

    // Binop operations
    static ValueInst* genAdd(ValueInst* a1, ValueInst* a2)
    {
        if (isZero(a1)) {
            return a2;
        } else if (isZero(a2)) {
            return a1;
        } else if (castInt32(a1) && castInt32(a2)) {
            return genInt32NumInst(castInt32(a1)->fNum + castInt32(a2)->fNum);
        } else if (castInt64(a1) && castInt64(a2)) {
            return genInt64NumInst(castInt64(a1)->fNum + castInt64(a2)->fNum);
        } else if (castFloat(a1) && castFloat(a2)) {
            return genFloatNumInst(castFloat(a1)->fNum + castFloat(a2)->fNum);
        } else if (castDouble(a1) && castDouble(a2)) {
            return genDoubleNumInst(castDouble(a1)->fNum + castDouble(a2)->fNum);
        } else if (castFixed(a1) && castFixed(a2)) {
            return genFixedPointNumInst(castFixed(a1)->fNum + castFixed(a2)->fNum);
        }  else {
            return genBinopInst(kAdd, a1, a2);
        }
    }
                
    static ValueInst* genAdd(ValueInst* a1, int a2) { return genAdd(a1, genInt32NumInst(a2)); }

    static ValueInst* genSub(ValueInst* a1, ValueInst* a2)
    {
        return isZero(a2) ? a1 : genBinopInst(kSub, a1, a2);
    }

    static ValueInst* genSub(ValueInst* a1, int a2) { return genSub(a1, genInt32NumInst(a2)); }

    static ValueInst* genMul(ValueInst* a1, ValueInst* a2)
    {
        return isOne(a1) ? a2 : (isOne(a2) ? a1 : genBinopInst(kMul, a1, a2));
    }

    static ValueInst* genDiv(ValueInst* a1, ValueInst* a2)
    {
        return isOne(a2) ? a1 : genBinopInst(kDiv, a1, a2);
    }

    static BinopInst* genRem(ValueInst* a1, ValueInst* a2) { return genBinopInst(kRem, a1, a2); }

    static BinopInst* genGreaterThan(ValueInst* a1, ValueInst* a2) { return genBinopInst(kGT, a1, a2); }

    static BinopInst* genLessThan(ValueInst* a1, ValueInst* a2) { return genBinopInst(kLT, a1, a2); }

    static BinopInst* genGreaterEqual(ValueInst* a1, ValueInst* a2) { return genBinopInst(kGE, a1, a2); }

    static BinopInst* genLessEqual(ValueInst* a1, ValueInst* a2) { return genBinopInst(kLE, a1, a2); }

    static BinopInst* genEqual(ValueInst* a1, ValueInst* a2) { return genBinopInst(kEQ, a1, a2); }

    static BinopInst* genNotEqual(ValueInst* a1, ValueInst* a2) { return genBinopInst(kNE, a1, a2); }

    static BinopInst* genAnd(ValueInst* a1, ValueInst* a2) { return genBinopInst(kAND, a1, a2); }

    static BinopInst* genOr(ValueInst* a1, ValueInst* a2) { return genBinopInst(kOR, a1, a2); }

    static BinopInst* genXOr(ValueInst* a1, ValueInst* a2) { return genBinopInst(kXOR, a1, a2); }

    // Functions
    static DeclareFunInst* genVoidFunction(const std::string& name, BlockInst* code = new BlockInst());
    static DeclareFunInst* genVoidFunction(const std::string& name, Names& args, BlockInst* code,
                                           bool isvirtual = false);
    static DeclareFunInst* genFunction0(const std::string& name, Typed::VarType res, BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction1(const std::string& name, Typed::VarType res, const std::string& arg1,
                                        Typed::VarType arg1_ty, BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction2(const std::string& name, Typed::VarType res, const std::string& arg1,
                                        Typed::VarType arg1_ty, const std::string& arg2, Typed::VarType arg2_ty,
                                        BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction3(const std::string& name, Typed::VarType res, const std::string& arg1,
                                        Typed::VarType arg1_ty, const std::string& arg2, Typed::VarType arg2_ty,
                                        const std::string& arg3, Typed::VarType arg3_ty, BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction4(const std::string& name, Typed::VarType res, const std::string& arg1,
                                        Typed::VarType arg1_ty, const std::string& arg2, Typed::VarType arg2_ty,
                                        const std::string& arg3, Typed::VarType arg3_ty, const std::string& arg4,
                                        Typed::VarType arg4_ty, BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction5(const std::string& name, Typed::VarType res, const std::string& arg1,
                                        Typed::VarType arg1_ty, const std::string& arg2, Typed::VarType arg2_ty,
                                        const std::string& arg3, Typed::VarType arg3_ty, const std::string& arg4,
                                        Typed::VarType arg4_ty, const std::string& arg5, Typed::VarType arg5_ty,
                                        BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction6(const std::string& name, Typed::VarType res, const std::string& arg1,
                                        Typed::VarType arg1_ty, const std::string& arg2, Typed::VarType arg2_ty,
                                        const std::string& arg3, Typed::VarType arg3_ty, const std::string& arg4,
                                        Typed::VarType arg4_ty, const std::string& arg5, Typed::VarType arg5_ty,
                                        const std::string& arg6, Typed::VarType arg6_ty, BlockInst* code = new BlockInst());
};

/*
 * Syntactic sugar for index computations.
 *
 * wrapper for ValueInst* with support for basic arithmetics
 *
 */
class FIRIndex {
    
  public:
    
    /* explicit constructors in order to avoid the generation of implicit conversions */
    explicit FIRIndex(ValueInst* inst) : fValue(inst) {}

    explicit FIRIndex(int num) : fValue(InstBuilder::genInt32NumInst(num)) {}

    FIRIndex(FIRIndex const& rhs) : fValue(rhs.fValue) {}

    /* implicitly convert to ValueInst* in order to simplify the usage */
    operator ValueInst*(void)const { return fValue; }

    // Add
    friend FIRIndex operator+(FIRIndex const& lhs, ValueInst* rhs)
    {
        return FIRIndex(InstBuilder::genAdd(lhs.fValue, rhs));
    }

    friend FIRIndex operator+(FIRIndex const& lhs, FIRIndex const& rhs) { return operator+(lhs, rhs.fValue); }

    friend FIRIndex operator+(FIRIndex const& lhs, int rhs)
    {
        return operator+(lhs, InstBuilder::genInt32NumInst(rhs));
    }

    // Sub
    friend FIRIndex operator-(FIRIndex const& lhs, ValueInst* rhs)
    {
        return FIRIndex(InstBuilder::genSub(lhs.fValue, rhs));
    }

    friend FIRIndex operator-(FIRIndex const& lhs, FIRIndex const& rhs) { return operator-(lhs, rhs.fValue); }

    friend FIRIndex operator-(FIRIndex const& lhs, int rhs)
    {
        return operator-(lhs, InstBuilder::genInt32NumInst(rhs));
    }

    // Mul
    friend FIRIndex operator*(FIRIndex const& lhs, ValueInst* rhs)
    {
        return FIRIndex(InstBuilder::genMul(lhs.fValue, rhs));
    }

    friend FIRIndex operator*(FIRIndex const& lhs, FIRIndex const& rhs) { return operator*(lhs, rhs.fValue); }

    friend FIRIndex operator*(FIRIndex const& lhs, int rhs)
    {
        return operator*(lhs, InstBuilder::genInt32NumInst(rhs));
    }

    // Div
    friend FIRIndex operator/(FIRIndex const& lhs, ValueInst* rhs)
    {
        return FIRIndex(InstBuilder::genDiv(lhs.fValue, rhs));
    }

    friend FIRIndex operator/(FIRIndex const& lhs, FIRIndex const& rhs) { return operator/(lhs, rhs.fValue); }

    friend FIRIndex operator/(FIRIndex const& lhs, int rhs)
    {
        return operator/(lhs, InstBuilder::genInt32NumInst(rhs));
    }

    // And
    friend FIRIndex operator&(FIRIndex const& lhs, ValueInst* rhs)
    {
        return FIRIndex(InstBuilder::genAnd(lhs.fValue, rhs));
    }

    friend FIRIndex operator&(FIRIndex const& lhs, FIRIndex const& rhs) { return operator&(lhs, rhs.fValue); }

    friend FIRIndex operator&(FIRIndex const& lhs, int rhs)
    {
        return operator&(lhs, InstBuilder::genInt32NumInst(rhs));
    }

    // Modulo
    friend FIRIndex operator%(FIRIndex const& lhs, ValueInst* rhs)
    {
        return FIRIndex(InstBuilder::genRem(lhs.fValue, rhs));
    }

    friend FIRIndex operator%(FIRIndex const& lhs, FIRIndex const& rhs) { return operator%(lhs, rhs.fValue); }

    friend FIRIndex operator%(FIRIndex const& lhs, int rhs)
    {
        return operator%(lhs, InstBuilder::genInt32NumInst(rhs));
    }

    // Equal
    friend FIRIndex operator==(FIRIndex const& lhs, ValueInst* rhs)
    {
        return FIRIndex(InstBuilder::genEqual(lhs.fValue, rhs));
    }

    friend FIRIndex operator==(FIRIndex const& lhs, FIRIndex const& rhs) { return operator==(lhs, rhs.fValue); }

    friend FIRIndex operator==(FIRIndex const& lhs, int rhs)
    {
        return operator==(lhs, InstBuilder::genInt32NumInst(rhs));
    }

    // Inf
    friend FIRIndex operator<(FIRIndex const& lhs, ValueInst* rhs)
    {
        return FIRIndex(InstBuilder::genLessThan(lhs.fValue, rhs));
    }

    friend FIRIndex operator<(FIRIndex const& lhs, FIRIndex const& rhs) { return operator<(lhs, rhs.fValue); }

    friend FIRIndex operator<(FIRIndex const& lhs, int rhs)
    {
        return operator<(lhs, InstBuilder::genInt32NumInst(rhs));
    }

   private:
    ValueInst* fValue;
};

Typed::VarType convert2FIRType(int type);

#endif

/*

Name := sequence of char

Size := digits

Opcode := + | - | * | / |...etc...

Access := kGlobal | kStruct | kStaticStruct | kFunArgs | kStack | kLoop

Type := kFloat | kInt32 | kDouble | kVoid | Type* --> Type | Vector (Type) | Array (Type) if size = 0, then
equivalent to a pointer on the considered type

Address := Access name | Address index

Statement   := DeclareVar (Address, Type, Value)
            | DeclareFun (Name, Type, Block)
            | ForLoop (Statement, Value, Statement, Block)
            | SimpleForLoop (string, Value, Block)
            | WhileLoop (Value, Block)
            | StoreVar (Address, Value)
            | Drop (Value)
            | Return (Value)
            | BlockInst (Statement*)
            | If (Value, BlockInst, BlockInst)
            | Switch (Value, <int>, BlockInst>*)

Value       := LoadVar (Address)
            | Float | Int | Double | Bool
            | Select (Cond, Value1, Value2)
            | Binop (Opcode, Value1, Value2)
            | Cast (Type, Value)
            | Null ()

Code rewritting:

For WSS:

1) change access of variable of type kStack in kStruct

Loop to function rewritting (faster compilation ?):

Two methods:

I)

1) change kStack variables in kStruct
2) transform Loop (Name, Value, Statement*) in DeclareFun (Name, Type, Statement*) : function type kVoid --> kVoid
3) in Compute, replace each loop with a call to the created function

II)

1) in each loop, transform in put vector access from kStack in kFunArgs
2) transform Loop (Name, Value, Statement*) in DeclareFun (Name, Type, Statement*) : all input variables become function
parameters 3) in Compute, replace each loop with a call to the created function giving it the good parameters

Scalarisation (some ideas, possibly not correct or not complete...):

1) transform all vectors *without delay* on the stack (used in loops) in scalar
2) in each loop, transform input vector accessing scalar access (Load/Store)
3) regroup all "postcode" of all loop at the end
4) rename loop variable into the Compute variable name
5) extract code and put it in Compute, suppress Loop statements

 Vision of the loops (count, list of input vectors, list of output vectors) different from the external prototype
 compute(count, float**, float**) or want to homogenize.
 
 Hence:
 
 DAG of loops in the format (count, list of input vectors, list of output vectors)
 compute(count, float**, float**)
 
 1) generate the header that prepares the separate input and output arrays
 2) compile the loops
 
 How to differentiate vectors without delay (which can be transformed into a scalar) from vectors with delay? With a specific
 specific naming?
 
 TODO: management of loop indices
 
 - in IndexedAddress, put a ValueInst instead of fIndex, update visitors
 - in InstructionsCompiler, generate accesses with "LoadVar" (loop-index)
 - in ForLoopInst, fName becomes a "DeclareVarInst" (allows to name and initialize the index), add a test expression,
addition of ValueInst fNext, calculation using fName.
 - new kLoop access type for loop variables
 - when transforming loops, Loop2FunctionBuider, SeqLoopBuilderVisitor, "disable" statements that
 manipulate the indices of the loop ? (no need, they don't appear in the loop body, but
 the loop index is used in the loop body, it must be matched with the new loop index,
 renaming necessary?)
 - use the *same* index name in ForLoopInst and in the internal code of the loop
 
*/
