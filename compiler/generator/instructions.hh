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
#include "sigtype.hh"

// ============================
// Generic instruction visitor
// ============================

struct Printable;
struct NullValueInst;
struct NullStatementInst;
struct DeclareVarInst;
struct DeclareBufferIteratorsRust;
struct DeclareFunInst;
struct DeclareStructTypeInst;
struct LoadVarInst;
struct LoadVarAddressInst;
struct TeeVarInst;
struct StoreVarInst;
struct ShiftArrayVarInst;
template <class TYPE>
struct ArrayNumInst;
struct FloatNumInst;
struct FloatArrayNumInst;
struct Int32NumInst;
struct Int64NumInst;
struct Int32ArrayNumInst;
struct BoolNumInst;
struct DoubleNumInst;
struct DoubleArrayNumInst;
struct BinopInst;
struct CastInst;
struct BitcastInst;
struct RetInst;
struct DropInst;

struct FunCallInst;
struct Select2Inst;
struct ControlInst;
struct IfInst;
struct ForLoopInst;
struct SimpleForLoopInst;
struct WhileLoopInst;
struct BlockInst;
struct SwitchInst;

// User interface
struct AddMetaDeclareInst;
struct OpenboxInst;
struct CloseboxInst;
struct AddButtonInst;
struct AddSliderInst;
struct AddBargraphInst;
struct AddSoundfileInst;
struct LabelInst;

struct Typed;
struct Address;
struct ValueInst;
struct StatementInst;

struct BasicTyped;
struct NamedTyped;
struct FunTyped;
struct ArrayTyped;
struct StructTyped;
struct VectorTyped;

struct NamedAddress;
struct IndexedAddress;

// Type checking

inline bool isRealType(Typed::VarType type)
{
    return (type == Typed::kFloat || type == Typed::kFloatMacro || type == Typed::kDouble);
}

inline bool isRealPtrType(Typed::VarType type)
{
    return (type == Typed::kFloat_ptr || type == Typed::kFloatMacro_ptr || type == Typed::kDouble_ptr);
}

inline bool isIntType(Typed::VarType type)
{
    return (type == Typed::kInt32 || type == Typed::kInt64);
}

inline bool isIntType32(Typed::VarType type)
{
    return (type == Typed::kInt32);
}

inline bool isIntType64(Typed::VarType type)
{
    return (type == Typed::kInt64);
}

inline bool isIntPtrType(Typed::VarType type)
{
    return (type == Typed::kInt32_ptr || type == Typed::kInt64_ptr);
}

inline bool isPtrType(Typed::VarType type)
{
    return isRealPtrType(type) || isIntPtrType(type);
}

inline bool isBoolType(Typed::VarType type)
{
    return (type == Typed::kBool);
}

inline bool isIntOrPtrType(Typed::VarType type)
{
    return (type == Typed::kInt32 || type == Typed::kInt64 || type == Typed::kInt32_ptr || type == Typed::kInt64_ptr ||
            type == Typed::kFloat_ptr || type == Typed::kFloat_ptr_ptr || type == Typed::kFloatMacro_ptr ||
            type == Typed::kFloatMacro_ptr_ptr || type == Typed::kDouble_ptr || type == Typed::kObj_ptr ||
            type == Typed::kVoid_ptr || type == Typed::kSound_ptr);
}

DeclareStructTypeInst* isStructType(const string& name);

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
    virtual void visit(DeclareBufferIteratorsRust* inst) {}

    // Memory
    virtual void visit(LoadVarInst* inst) {}
    virtual void visit(LoadVarAddressInst* inst) {}
    virtual void visit(TeeVarInst* inst) {}
    virtual void visit(StoreVarInst* inst) {}
    virtual void visit(ShiftArrayVarInst* inst) {}

    // Addresses
    virtual void visit(NamedAddress* address) {}
    virtual void visit(IndexedAddress* address) {}

    // Numbers
    virtual void visit(FloatNumInst* inst) {}
    virtual void visit(FloatArrayNumInst* inst) {}
    virtual void visit(Int32NumInst* inst) {}
    virtual void visit(Int64NumInst* inst) {}
    virtual void visit(Int32ArrayNumInst* inst) {}
    virtual void visit(BoolNumInst* inst) {}
    virtual void visit(DoubleNumInst* inst) {}
    virtual void visit(DoubleArrayNumInst* inst) {}

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
    virtual void visit(WhileLoopInst* inst) {}

    // Block
    virtual void visit(BlockInst* inst) {}

    // Typed
    virtual void visit(BasicTyped* typed) {}
    virtual void visit(NamedTyped* typed) {}
    virtual void visit(FunTyped* typed) {}
    virtual void visit(ArrayTyped* typed) {}
    virtual void visit(StructTyped* typed) {}
    virtual void visit(VectorTyped* typed) {}
};

// Clone a FIR expression

struct CloneVisitor : public virtual Garbageable {
    CloneVisitor() {}
    virtual ~CloneVisitor() {}

    virtual ValueInst*     visit(NullValueInst* inst)     = 0;
    virtual StatementInst* visit(NullStatementInst* inst) = 0;

    // Declarations
    virtual StatementInst* visit(DeclareVarInst* inst)        = 0;
    virtual StatementInst* visit(DeclareFunInst* inst)        = 0;
    virtual StatementInst* visit(DeclareStructTypeInst* inst) = 0;
    virtual StatementInst* visit(DeclareBufferIteratorsRust* inst) = 0;

    // Memory
    virtual ValueInst*     visit(LoadVarInst* inst)        = 0;
    virtual ValueInst*     visit(LoadVarAddressInst* inst) = 0;
    virtual ValueInst*     visit(TeeVarInst* inst)         = 0;
    virtual StatementInst* visit(StoreVarInst* inst)       = 0;
    virtual StatementInst* visit(ShiftArrayVarInst* inst)  = 0;

    // Addresses
    virtual Address* visit(NamedAddress* address)   = 0;
    virtual Address* visit(IndexedAddress* address) = 0;

    // Numbers
    virtual ValueInst* visit(FloatNumInst* inst)       = 0;
    virtual ValueInst* visit(FloatArrayNumInst* inst)  = 0;
    virtual ValueInst* visit(Int32NumInst* inst)       = 0;
    virtual ValueInst* visit(Int64NumInst* inst)       = 0;
    virtual ValueInst* visit(Int32ArrayNumInst* inst)  = 0;
    virtual ValueInst* visit(BoolNumInst* inst)        = 0;
    virtual ValueInst* visit(DoubleNumInst* inst)      = 0;
    virtual ValueInst* visit(DoubleArrayNumInst* inst) = 0;

    // Numerical computation
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

    // Types
    virtual Typed* visit(BasicTyped* type)  = 0;
    virtual Typed* visit(NamedTyped* type)  = 0;
    virtual Typed* visit(FunTyped* type)    = 0;
    virtual Typed* visit(ArrayTyped* type)  = 0;
    virtual Typed* visit(StructTyped* type) = 0;
    virtual Typed* visit(VectorTyped* type) = 0;
};

// ============================
// Base class for instructions
// ============================

// Printable is defined in instructions_type.h

// Added in compilation environment
struct StatementInst : public Printable {
    virtual void accept(InstVisitor* visitor) = 0;

    virtual StatementInst* clone(CloneVisitor* cloner) = 0;

    virtual string getName() const { return ""; }
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

// ==========================
//  Instruction with a type
// ==========================

// Base type is defined in instructions_type.h

Typed::VarType ctType(Type t);

struct BasicTyped : public Typed {
    const VarType fType;

    static void cleanup();

    BasicTyped(VarType type) : fType(type) {}

    VarType getType() const { return fType; }

    int getSize() const;  // moved in "instructions.cpp"

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct NamedTyped : public Typed {
    const string fName;
    Typed* fType;

    NamedTyped(const string& name, Typed* type) : fName(name), fType(type) {}

    virtual ~NamedTyped() {}

    VarType getType() const { return fType->getType(); }

    int getSize() const { return fType->getSize(); }

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct FunTyped : public Typed {
    enum FunAttribute { kDefault = 0x1, kLocal = 0x2, kVirtual = 0x4, kStatic = 0x8, kInline = 0x10 };

    list<NamedTyped*> fArgsTypes;
    BasicTyped*       fResult;
    FunAttribute      fAttribute;

    FunTyped(const list<NamedTyped*>& args, BasicTyped* result, FunAttribute attribute = kDefault)
        : fArgsTypes(args), fResult(result), fAttribute(attribute)
    {
    }

    VarType getType() const { return fResult->getType(); }

    Typed* getTyped() { return fResult; }

    // Arguments type encoded as a string
    string getPrototype()
    {
        string res;
        if (fArgsTypes.size() > 0) {
            for (auto& it : fArgsTypes) {
                res += gTypeString[it->getType()];
            }
        } else {
            res = "void";
        }
        return res;
    }

    int getSize() const;  // moved in "instructions.cpp"

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct ArrayTyped : public Typed {
    Typed*     fType;
    const int  fSize;
    const bool fIsPtr;

    ArrayTyped(Typed* type, int size, bool is_ptr = false) : fType(type), fSize(size), fIsPtr(is_ptr) {}

    virtual ~ArrayTyped() {}

    VarType getType() const { return getPtrFromType(fType->getType()); }

    int getSize() const;  // moved in "instructions.cpp"

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct StructTyped : public Typed {
    const string        fName;
    vector<NamedTyped*> fFields;

    StructTyped(const string& name, const vector<NamedTyped*>& fields) : fName(name), fFields(fields) {}

    virtual ~StructTyped() {}

    VarType getType() const { return kObj_ptr; }
    VarType getType(int index) { return fFields[index]->getType(); }

    int getSize() const
    {
        int size = 0;
        for (auto& it : fFields) {
            size += it->getSize();
        }
        return size;
    }

    int getOffset(int field) const
    {
        int offset = 0;
        for (int i = 0; i < field; i++) {
            offset += fFields[i]->getSize();
        }
        return offset;
    }

    string getName(int index) { return fFields[index]->fName; }

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct VectorTyped : public Typed {
    BasicTyped* fType;
    const int  fSize;

    VectorTyped(BasicTyped* type, int size) : fType(type), fSize(size) {}

    virtual ~VectorTyped() {}

    VarType getType() const { return getVecFromType(fType->getType()); }

    int getSize() const { return fType->getSize() * fSize; }

    virtual void accept(InstVisitor* visitor) { visitor->visit(this); }

    Typed* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct NumValueInst {
};

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

    virtual void                setAccess(Address::AccessType type) = 0;
    virtual Address::AccessType getAccess() const                   = 0;

    virtual void   setName(const string& name) = 0;
    virtual string getName() const             = 0;

    static void dump(AccessType access) { *fOut << dumpString(access); }

#define hasAccess(arg) res += (res != "") ? (string("|") + string(arg)) : string(arg);

    static string dumpString(AccessType access)
    {
        string res;
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
    string fName;
    AccessType   fAccess;

    NamedAddress(const string& name, AccessType access) : fName(name), fAccess(access) {}

    void                setAccess(Address::AccessType type) { fAccess = type; }
    Address::AccessType getAccess() const { return fAccess; }

    void   setName(const string& name) { fName = name; }
    string getName() const { return fName; }

    Address* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }
};

struct IndexedAddress : public Address {
    Address*   fAddress;
    ValueInst* fIndex;

    IndexedAddress(Address* address, ValueInst* index) : fAddress(address), fIndex(index) {}

    virtual ~IndexedAddress() {}

    void                setAccess(Address::AccessType type) { fAddress->setAccess(type); }
    Address::AccessType getAccess() const { return fAddress->getAccess(); }

    void   setName(const string& name) { fAddress->setName(name); }
    string getName() const { return fAddress->getName(); }

    ValueInst* getIndex() const { return fIndex; }

    Address* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }
};

// ===============
// User interface
// ===============

struct AddMetaDeclareInst : public StatementInst {
    const string fZone;
    const string fKey;
    const string fValue;

    AddMetaDeclareInst(const string& zone, const string& key, const string& value)
        : fZone(zone), fKey(key), fValue(value)
    {
    }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct OpenboxInst : public StatementInst {
    enum BoxType { kVerticalBox, kHorizontalBox, kTabBox };

    const string  fName;
    const BoxType fOrient;

    OpenboxInst(const string& name, BoxType orient) : fName(name), fOrient(orient) {}

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

    const string     fLabel;
    const string     fZone;
    const ButtonType fType;

    AddButtonInst(const string& label, const string& zone, ButtonType type) : fLabel(label), fZone(zone), fType(type) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct AddSliderInst : public StatementInst {
    enum SliderType { kHorizontal, kVertical, kNumEntry };

    const string     fLabel;
    const string     fZone;
    const double     fInit;
    const double     fMin;
    const double     fMax;
    const double     fStep;
    const SliderType fType;

    AddSliderInst(const string& label, const string& zone, double init, double min, double max, double step,
                  SliderType type)
        : fLabel(label), fZone(zone), fInit(init), fMin(min), fMax(max), fStep(step), fType(type)
    {
    }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct AddBargraphInst : public StatementInst {
    enum BargraphType { kHorizontal, kVertical };

    const string       fLabel;
    const string       fZone;
    const double       fMin;
    const double       fMax;
    const BargraphType fType;

    AddBargraphInst(const string& label, const string& zone, double min, double max, BargraphType type)
        : fLabel(label), fZone(zone), fMin(min), fMax(max), fType(type)
    {
    }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct AddSoundfileInst : public StatementInst {
    const string fLabel;
    const string fURL;
    const string fSFZone;

    AddSoundfileInst(const string& label, const string& url, const string& sf_zone)
        : fLabel(label), fURL(url), fSFZone(sf_zone)
    {
    }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct LabelInst : public StatementInst {
    const string fLabel;

    LabelInst(const string& label) : fLabel(label) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
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

    void                setAccess(Address::AccessType type) { fAddress->setAccess(type); }
    Address::AccessType getAccess() const  { return fAddress->getAccess(); }

    void   setName(const string& name) { fAddress->setName(name); }
    string getName() const { return fAddress->getName(); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    struct StoreVarInst* store(ValueInst* val);
    struct LoadVarInst*  load();
};

struct DeclareBufferIteratorsRust : public StatementInst {
    std::string fBufferName;
    int         fNumChannels;
    bool        fMutable;

    DeclareBufferIteratorsRust(const std::string& buffer_name, int num_channels, bool mut) :
        fBufferName(buffer_name), fNumChannels(num_channels), fMutable(mut)
        {};

    virtual ~DeclareBufferIteratorsRust() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

// ==============
// Memory access
// ==============

struct DropInst : public StatementInst {
    ValueInst* fResult;

    DropInst(ValueInst* result = nullptr) : fResult(result) {}

    virtual ~DropInst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct LoadVarInst : public ValueInst {
    Address* fAddress;

    LoadVarInst(Address* address) : ValueInst(), fAddress(address) {}

    virtual ~LoadVarInst() {}

    void   setName(const string& name) { fAddress->setName(name); }
    string getName() const { return fAddress->getName(); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual bool isSimpleValue() const { return dynamic_cast<NamedAddress*>(fAddress); }
};

struct LoadVarAddressInst : public ValueInst {
    Address* fAddress;

    LoadVarAddressInst(Address* address) : ValueInst(), fAddress(address) {}

    virtual ~LoadVarAddressInst() {}

    void   setName(const string& name) { fAddress->setName(name); }
    string getName() const { return fAddress->getName(); }

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

    void   setName(const string& name) { fAddress->setName(name); }
    string getName() const { return fAddress->getName(); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct StoreVarInst : public StatementInst {
    Address*   fAddress;
    ValueInst* fValue;

    StoreVarInst(Address* address, ValueInst* value) : fAddress(address), fValue(value) {}

    virtual ~StoreVarInst() {}

    void   setName(const string& name) { fAddress->setName(name); }
    string getName() const { return fAddress->getName(); }

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

// ========
// Numbers
// ========

struct FloatNumInst : public ValueInst, public NumValueInst {
    const float fNum;

    FloatNumInst(float num) : ValueInst(), fNum(num) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual bool isSimpleValue() const { return true; }
};

template <class TYPE>
struct ArrayNumInst : public ValueInst {
    vector<TYPE> fNumTable;

    ArrayNumInst(const vector<TYPE>& nums) : ValueInst(), fNumTable(nums) {}

    ArrayNumInst(int size) : ValueInst() { fNumTable.resize(size); }

    void setValue(int index, TYPE num) { fNumTable[index] = num; }
    void addValue(TYPE num) { fNumTable.push_back(num); }
    TYPE getValue(int index) { return fNumTable[index]; }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    virtual bool isSimpleValue() const { return true; }
};

struct FloatArrayNumInst : public ArrayNumInst<float> {
    FloatArrayNumInst(const vector<float>& nums) : ArrayNumInst<float>(nums) {}
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
    DoubleArrayNumInst(const vector<double>& nums) : ArrayNumInst<double>(nums) {}
    DoubleArrayNumInst(int size) : ArrayNumInst<double>(size) {}

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

struct Int64NumInst : public ValueInst, public NumValueInst {
    const long long fNum;

    Int64NumInst(long long num) : ValueInst(), fNum(num) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual bool isSimpleValue() const { return true; }
};

struct Int32ArrayNumInst : public ArrayNumInst<int> {
    Int32ArrayNumInst(const vector<int>& nums) : ArrayNumInst<int>(nums) {}
    Int32ArrayNumInst(int size) : ArrayNumInst<int>(size) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct BoolNumInst : public ValueInst, public NumValueInst {
    const bool fNum;

    BoolNumInst(bool num) : ValueInst(), fNum(num) {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    virtual bool isSimpleValue() const { return true; }
};

// ======================
// Numerical computation
// ======================

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

struct BlockInst : public StatementInst {
    list<StatementInst*> fCode;
    bool                 fIndent;

    BlockInst(list<StatementInst*> code) : fCode(code), fIndent(false) {}

    BlockInst() : fIndent(false) {}

    virtual ~BlockInst() {}

    void setIndent(bool indent) { fIndent = indent; }
    bool getIndent() { return fIndent; }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }

    void pushFrontInst(StatementInst* inst) { fCode.push_front(inst); }

    void pushBackInst(StatementInst* inst) { fCode.push_back(inst); }

    void merge(BlockInst* inst)
    {
        for (auto& it : inst->fCode) {
            fCode.push_back(it);
        }
    }

    int size() const { return int(fCode.size()); }

    bool hasReturn() const;
    ValueInst* getReturnValue();
};

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
    list<pair<int, BlockInst*> > fCode;

    SwitchInst(ValueInst* cond, const list<pair<int, BlockInst*> >& code) : fCond(cond), fCode(code) {}

    SwitchInst(ValueInst* cond) : fCond(cond) {}

    virtual ~SwitchInst() {}

    void addCase(int value, BlockInst* block) { fCode.push_back(make_pair(value, block)); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct RetInst : public StatementInst {
    ValueInst* fResult;

    RetInst(ValueInst* result = nullptr) : fResult(result) {}

    virtual ~RetInst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct FunCallInst : public ValueInst {
    const string     fName;
    list<ValueInst*> fArgs;  // List of arguments
    const bool       fMethod;

    FunCallInst(const string& name, const list<ValueInst*>& args, bool method)
        : ValueInst(), fName(name), fArgs(args), fMethod(method)
    {
    }

    virtual ~FunCallInst() {}

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    ValueInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

struct DeclareFunInst : public StatementInst {
    const string fName;
    FunTyped*    fType;  // Describes type of all arguments and function result
    BlockInst*   fCode;  // Code is a list of StatementInst*

    DeclareFunInst(const string& name, FunTyped* type, BlockInst* code = new BlockInst());

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

    void pushFrontInst(StatementInst* inst) { fCode->pushFrontInst(inst); }

    void pushBackInst(StatementInst* inst) { fCode->pushBackInst(inst); }

    string getName() const { return fInit->getName(); }

    void accept(InstVisitor* visitor) { visitor->visit(this); }

    StatementInst* clone(CloneVisitor* cloner) { return cloner->visit(this); }
};

// To be used for the 'rust' backend
struct SimpleForLoopInst : public StatementInst {
    ValueInst*   fUpperBound;
    ValueInst*   fLowerBound;
    const string fName;
    const bool   fReverse;
    BlockInst* fCode;

    SimpleForLoopInst(const string& index, ValueInst* upperBound, ValueInst* lowerBound, bool reverse, BlockInst* code)
        : fUpperBound(upperBound), fLowerBound(lowerBound), fName(index), fReverse(reverse), fCode(code)
    {
    }

    string getName() const { return fName; }

    virtual ~SimpleForLoopInst() {}

    void pushFrontInst(StatementInst* inst) { fCode->pushFrontInst(inst); }

    void pushBackInst(StatementInst* inst) { fCode->pushBackInst(inst); }

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
        return new DeclareVarInst(inst->fAddress->clone(this), inst->fType->clone(this),
                                  ((inst->fValue) ? inst->fValue->clone(this) : nullptr));
    }
    virtual StatementInst* visit(DeclareFunInst* inst)
    {
        return new DeclareFunInst(inst->fName, static_cast<FunTyped*>(inst->fType->clone(this)),
                                  static_cast<BlockInst*>(inst->fCode->clone(this)));
    }
    virtual StatementInst* visit(DeclareStructTypeInst* inst)
    {
        return new DeclareStructTypeInst(static_cast<StructTyped*>(inst->fType->clone(this)));
    }
    virtual StatementInst* visit(DeclareBufferIteratorsRust* inst)
    {
        return new DeclareBufferIteratorsRust(inst->fBufferName, inst->fNumChannels, inst->fMutable);
    }

    // Memory
    virtual ValueInst* visit(LoadVarInst* inst) { return new LoadVarInst(inst->fAddress->clone(this)); }
    virtual ValueInst* visit(LoadVarAddressInst* inst) { return new LoadVarAddressInst(inst->fAddress->clone(this)); }
    virtual ValueInst* visit(TeeVarInst* inst)
    {
        return new TeeVarInst(inst->fAddress->clone(this), inst->fValue->clone(this));
    }
    virtual StatementInst* visit(StoreVarInst* inst)
    {
        return new StoreVarInst(inst->fAddress->clone(this), inst->fValue->clone(this));
    }
    virtual StatementInst* visit(ShiftArrayVarInst* inst)
    {
        return new ShiftArrayVarInst(inst->fAddress->clone(this), inst->fDelay);
    }

    // Addresses
    virtual Address* visit(NamedAddress* address) { return new NamedAddress(address->fName, address->fAccess); }
    virtual Address* visit(IndexedAddress* address)
    {
        return new IndexedAddress(address->fAddress->clone(this), address->fIndex->clone(this));
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

    // Numerical computation
    virtual ValueInst* visit(BinopInst* inst)
    {
        return new BinopInst(inst->fOpcode, inst->fInst1->clone(this), inst->fInst2->clone(this));
    }

    // Cast
    virtual ValueInst* visit(CastInst* inst)
    {
        return new CastInst(inst->fInst->clone(this), inst->fType->clone(this));
    }

    virtual ValueInst* visit(BitcastInst* inst)
    {
        return new BitcastInst(inst->fInst->clone(this), inst->fType->clone(this));
    }

    // Function call
    virtual ValueInst* visit(FunCallInst* inst)
    {
        list<ValueInst*> cloned_args;
        for (auto& it : inst->fArgs) {
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
        ValueInst* then_exp = inst->fThen->clone(this);
        ValueInst* else_exp = inst->fElse->clone(this);
        ValueInst* cond_exp = inst->fCond->clone(this);
        // cond_exp has to be evaluated last for FunctionInliner to correctly work in gHasTeeLocal mode
        return new Select2Inst(cond_exp, then_exp, else_exp);
    }

    virtual StatementInst* visit(ControlInst* inst)
    {
        return new ControlInst(inst->fCond->clone(this), inst->fStatement->clone(this));
    }

    virtual StatementInst* visit(IfInst* inst)
    {
        return new IfInst(inst->fCond->clone(this), static_cast<BlockInst*>(inst->fThen->clone(this)),
                          static_cast<BlockInst*>(inst->fElse->clone(this)));
    }
    virtual StatementInst* visit(SwitchInst* inst)
    {
        SwitchInst* cloned = new SwitchInst(inst->fCond->clone(this));
        for (auto& it : inst->fCode) {
            cloned->addCase(it.first, static_cast<BlockInst*>((it.second)->clone(this)));
        }
        return cloned;
    }

    // Loop
    virtual StatementInst* visit(ForLoopInst* inst)
    {
        return new ForLoopInst(inst->fInit->clone(this), inst->fEnd->clone(this), inst->fIncrement->clone(this),
                               static_cast<BlockInst*>(inst->fCode->clone(this)), inst->fIsRecursive);
    }

    virtual StatementInst* visit(SimpleForLoopInst* inst)
    {
        return new SimpleForLoopInst(inst->fName, inst->fUpperBound->clone(this), inst->fLowerBound->clone(this),
                                     inst->fReverse, static_cast<BlockInst*>(inst->fCode->clone(this)));
    }

    virtual StatementInst* visit(WhileLoopInst* inst)
    {
        return new WhileLoopInst(inst->fCond->clone(this), static_cast<BlockInst*>(inst->fCode->clone(this)));
    }

    // Block
    virtual StatementInst* visit(BlockInst* inst)
    {
        // fBlockStack is used when inlining functions
        BlockInst* cloned = new BlockInst();
        fBlockStack.push(cloned);
        for (auto& it : inst->fCode) {
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
    virtual Typed* visit(FunTyped* typed)
    {
        list<NamedTyped*> cloned;
        for (auto& it : typed->fArgsTypes) {
            cloned.push_back(static_cast<NamedTyped*>(it->clone(this)));
        }
        return new FunTyped(cloned, static_cast<BasicTyped*>(typed->fResult->clone(this)), typed->fAttribute);
    }
    virtual Typed* visit(ArrayTyped* typed)
    {
        return new ArrayTyped(typed->fType->clone(this), typed->fSize, typed->fIsPtr);
    }
    virtual Typed* visit(StructTyped* typed)
    {
        vector<NamedTyped*> cloned;
        for (auto& it : typed->fFields) {
            cloned.push_back(static_cast<NamedTyped*>(it->clone(this)));
        }
        return new StructTyped(typed->fName, cloned);
    }

    virtual Typed* visit(VectorTyped* typed)
    {
        return new VectorTyped(static_cast<BasicTyped*>(typed->fType->clone(this)), typed->fSize);
    }
};

// =======================
// Basic dispatch visitor
// =======================

struct DispatchVisitor : public InstVisitor {
    using InstVisitor::visit;

    virtual void visit(DeclareVarInst* inst)
    {
        inst->fAddress->accept(this);
        // No visitor on types
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
        address->fIndex->accept(this);
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
        for (auto& it : inst->fArgs) {
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
        inst->fUpperBound->accept(this);
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
        for (auto& it : inst->fCode) {
            (it.second)->accept(this);
        }
    }

    virtual void visit(BlockInst* inst)
    {
        for (auto& it : inst->fCode) {
            it->accept(this);
        }
    }

    // Typed
    virtual void visit(FunTyped* typed)
    {
        typed->fResult->accept(this);
        for (auto& it : typed->fArgsTypes) {
            it->accept(this);
        }
    }
    virtual void visit(ArrayTyped* typed) { typed->fType->accept(this); }
    virtual void visit(StructTyped* typed)
    {
        for (auto& it : typed->fFields) {
            it->accept(this);
        }
    }

    virtual void visit(VectorTyped* typed) { typed->fType->accept(this); }
};

struct VariableScopeVisitor : public DispatchVisitor {
    stack<list<DeclareVarInst*> > fBlockVarTable;

    VariableScopeVisitor() {}

    virtual void visit(DeclareVarInst* inst)
    {
        fBlockVarTable.top().push_back(inst);
        DispatchVisitor::visit(inst);
    }

    virtual void visit(BlockInst* inst)
    {
        list<DeclareVarInst*> variable_block;
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

struct InstBuilder {
    // User interface
    static AddMetaDeclareInst* genAddMetaDeclareInst(const string& zone, const string& key, const string& value)
    {
        return new AddMetaDeclareInst(zone, key, value);
    }

    static OpenboxInst* genOpenboxInst(const string& name, OpenboxInst::BoxType orient)
    {
        faustassert(orient >= OpenboxInst::kVerticalBox && orient <= OpenboxInst::kTabBox);
        return new OpenboxInst(name, orient);
    }

    static CloseboxInst* genCloseboxInst() { return new CloseboxInst(); }

    static AddButtonInst* genAddButtonInst(const string& label, const string& zone)
    {
        return new AddButtonInst(label, zone, AddButtonInst::kDefaultButton);
    }

    static AddButtonInst* genAddCheckbuttonInst(const string& label, const string& zone)
    {
        return new AddButtonInst(label, zone, AddButtonInst::kCheckButton);
    }

    static AddSliderInst* genAddHorizontalSliderInst(const string& label, const string& zone, double init, double min,
                                                     double max, double step)
    {
        stringstream error;
        if (min > max) {
            error << "ERROR : horizontal slider \'"<< label << "\' min = " << min << " should be less than max = " << max << "\n";
            throw faustexception(error.str());
        } else if (init < min || init > max) {
            error << "ERROR : horizontal slider \'"<< label << "\' init = " << init << " outside of [" << min << " " << max << "] range\n";
            throw faustexception(error.str());
        }
        return new AddSliderInst(label, zone, init, min, max, step, AddSliderInst::kHorizontal);
    }

    static AddSliderInst* genAddVerticalSliderInst(const string& label, const string& zone, double init, double min,
                                                   double max, double step)
    {
        stringstream error;
        if (min > max) {
            error << "ERROR : vertical slider \'"<< label << "\' min = " << min << " should be less than max = " << max << "\n";
            throw faustexception(error.str());
        } else if (init < min || init > max) {
            error << "ERROR : vertical slider \'" << label << "\' init = " << init << " outside of [" << min << " " << max << "] range\n";
            throw faustexception(error.str());
        }
        return new AddSliderInst(label, zone, init, min, max, step, AddSliderInst::kVertical);
    }

    static AddSliderInst* genAddNumEntryInst(const string& label, const string& zone, double init, double min,
                                             double max, double step)
    {
        stringstream error;
        if (min > max) {
            error << "ERROR : num entry \'"<< label << "\' min = " << min << " should be less than max = " << max << "\n";
            throw faustexception(error.str());
        } else if (init < min || init > max) {
            error << "ERROR : num entry \'" << label << "\' init = " << init << " outside of [" << min << " " << max << "] range\n";
            throw faustexception(error.str());
        }
        return new AddSliderInst(label, zone, init, min, max, step, AddSliderInst::kNumEntry);
    }

    static AddBargraphInst* genAddHorizontalBargraphInst(const string& label, const string& zone, double min,
                                                         double max)
    {
        return new AddBargraphInst(label, zone, min, max, AddBargraphInst::kHorizontal);
    }

    static AddBargraphInst* genAddVerticalBargraphInst(const string& label, const string& zone, double min, double max)
    {
        return new AddBargraphInst(label, zone, min, max, AddBargraphInst::kVertical);
    }

    static AddSoundfileInst* genAddSoundfileInst(const string& label, const string& url, const string& sf_zone)
    {
        return new AddSoundfileInst(label, url, sf_zone);
    }

    static LabelInst* genLabelInst(const string& label) { return new LabelInst(label); }

    // Null instruction
    static NullValueInst*     genNullValueInst() { return new NullValueInst(); }
    static NullStatementInst* genNullStatementInst() { return new NullStatementInst(); }

    // Declarations
    static DeclareVarInst* genDeclareVarInst(Address* address, Typed* typed, ValueInst* value = nullptr)
    {
        return new DeclareVarInst(address, typed, value);
    }

    static DeclareFunInst* genDeclareFunInst(const string& name, FunTyped* typed, BlockInst* code)
    {
        return new DeclareFunInst(name, typed, code);
    }
    static DeclareFunInst* genDeclareFunInst(const string& name, FunTyped* typed)
    {
        return new DeclareFunInst(name, typed);
    }

    static DeclareStructTypeInst* genDeclareStructTypeInst(StructTyped* type)
    {
        return new DeclareStructTypeInst(type);
    }

    static DeclareBufferIteratorsRust* genDeclareBufferIteratorsRust(std::string buffer_name, int num_channels, bool mut)
    {
        return new DeclareBufferIteratorsRust(buffer_name, num_channels, mut);
    }

    // Memory
    static LoadVarInst*        genLoadVarInst(Address* address) { return new LoadVarInst(address); }
    static LoadVarAddressInst* genLoadVarAddressInst(Address* address) { return new LoadVarAddressInst(address); }
    static TeeVarInst*         genTeeVar(const string& vname, ValueInst* value)
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
    static FloatNumInst*       genFloatNumInst(float num) { return new FloatNumInst(num); }
    static FloatArrayNumInst*  genFloatArrayNumInst(int size) { return new FloatArrayNumInst(size); }
    static DoubleNumInst*      genDoubleNumInst(double num) { return new DoubleNumInst(num); }
    static DoubleArrayNumInst* genDoubleArrayNumInst(int size) { return new DoubleArrayNumInst(size); }
    static DoubleNumInst*      genQuadNumInst(double num) { return new DoubleNumInst(num); }  // Use DoubleNumInst

    static ValueInst* genTypedZero(Typed::VarType type);

    static ValueInst* genRealNumInst(Typed::VarType ctype, double num)
    {
        if (ctype == Typed::kFloat) {
            return new FloatNumInst(float(num));
        } else if (ctype == Typed::kFloatMacro) {
            return genCastInst(new DoubleNumInst(num), genBasicTyped(Typed::kFloatMacro));
        } else if (ctype == Typed::kDouble) {
            return new DoubleNumInst(num);
        } else if (ctype == Typed::kQuad) {
            return new DoubleNumInst(num);
        } else {
            faustassert(false);
        }
        return nullptr;
    }

    static ValueInst* genArrayNumInst(Typed::VarType ctype, int size)
    {
        if (ctype == Typed::kInt32) {
            return new Int32ArrayNumInst(size);
        } else if (ctype == Typed::kFloat) {
            return new FloatArrayNumInst(size);
        } else if (ctype == Typed::kDouble) {
            return new DoubleArrayNumInst(size);
        } else {
            faustassert(false);
        }
        return nullptr;
    }

    static Int32NumInst* genInt32NumInst(int num) { return new Int32NumInst(num); }
    static Int64NumInst* genInt64NumInst(long long num) { return new Int64NumInst(num); }
    static BoolNumInst*  genBoolNumInst(bool num) { return new BoolNumInst(num); }

    // Numerical computation
    static BinopInst* genBinopInst(int opcode, ValueInst* inst1, ValueInst* inst2)
    {
        return new BinopInst(opcode, inst1, inst2);
    }

    static ValueInst* genCastInst(ValueInst* inst, Typed* typed_ext)
    {
        Int32NumInst*  int_num    = dynamic_cast<Int32NumInst*>(inst);
        FloatNumInst*  float_num  = dynamic_cast<FloatNumInst*>(inst);
        DoubleNumInst* double_num = dynamic_cast<DoubleNumInst*>(inst);
        BasicTyped*    typed      = dynamic_cast<BasicTyped*>(typed_ext);
        CastInst*      cast       = dynamic_cast<CastInst*>(inst);

        if (!typed) {
            // Default case
            return new CastInst(inst, typed_ext);
        } else if (cast && (cast->fType == typed_ext)) {
            // Casting an already casted value with the same type
            return inst;
        } else if (typed->getType() == Typed::kFloat) {
            if (int_num) {
                // Simple float cast of integer
                return genFloatNumInst(float(int_num->fNum));
            } else if (float_num) {
                // No cast needed
                return inst;
            } else if (double_num) {
                return genFloatNumInst(float(double_num->fNum));
            } else {
                // Default case
                return new CastInst(inst, typed);
            }
        } else if (typed->getType() == Typed::kDouble || typed->getType() == Typed::kQuad) {
            if (int_num) {
                // Simple double cast of integer
                return genDoubleNumInst(double(int_num->fNum));
            } else if (float_num) {
                return genDoubleNumInst(double(float_num->fNum));
            } else if (double_num) {
                // No cast needed
                return inst;
            } else {
                // Default case
                return new CastInst(inst, typed);
            }
        } else if (typed->getType() == Typed::kInt32) {
            if (int_num) {
                // No cast needed
                return inst;
            } else if (float_num) {
                // Simple int cast of float
                return genInt32NumInst(int(float_num->fNum));
            } else if (double_num) {
                // Simple int cast of double
                return genInt32NumInst(int(double_num->fNum));
            } else {
                // Default case
                return new CastInst(inst, typed);
            }
        } else {
            // Default case
            return new CastInst(inst, typed);
        }
    }

    static ValueInst* genBitcastInst(ValueInst* inst, Typed* typed) { return new BitcastInst(inst, typed); }
    static ValueInst* genCastFloatInst(ValueInst* inst);
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
    static FunCallInst* genFunCallInst(const string& name, const list<ValueInst*>& args)
    {
        return new FunCallInst(name, args, false);
    }
    static FunCallInst* genFunCallInst(const string& name, const list<ValueInst*>& args, bool method)
    {
        return new FunCallInst(name, args, method);
    }
    static DropInst* genVoidFunCallInst(const string& name, const list<ValueInst*>& args)
    {
        return new DropInst(new FunCallInst(name, args, false));
    }
    static DropInst* genVoidFunCallInst(const string& name, const list<ValueInst*>& args, bool method)
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
    static ForLoopInst* genForLoopInst(const string& index, int init, int size, int step = 1)
    {
        DeclareVarInst* dec = genDecLoopVar(index, genInt32Typed(), genInt32NumInst(init));
        ValueInst*      end = genLessThan(dec->load(), genInt32NumInst(size));
        StoreVarInst*   inc = dec->store(genAdd(dec->load(), step));
        return genForLoopInst(dec, end, inc);
    }

    // Used for Rust backend
    static SimpleForLoopInst* genSimpleForLoopInst(const string& index, ValueInst* upperBound,
                                                   ValueInst* lowerBound = new Int32NumInst(0), bool reverse = false,
                                                   BlockInst* code = new BlockInst())
    {
        faustassert(dynamic_cast<Int32NumInst*>(upperBound) || dynamic_cast<LoadVarInst*>(upperBound));
        faustassert(dynamic_cast<Int32NumInst*>(lowerBound) || dynamic_cast<LoadVarInst*>(lowerBound));
        return new SimpleForLoopInst(index, upperBound, lowerBound, reverse, code);
    }

    static WhileLoopInst* genWhileLoopInst(ValueInst* cond, BlockInst* code) { return new WhileLoopInst(cond, code); }

    static BlockInst* genBlockInst(const list<StatementInst*>& code) { return new BlockInst(code); }
    static BlockInst* genBlockInst() { return new BlockInst(); }

    // Types
    static BasicTyped* genBasicTyped(Typed::VarType type);  // moved in instructions.cpp

    static BasicTyped* genInt32Typed() { return genBasicTyped(Typed::kInt32); }
    static BasicTyped* genVoidTyped() { return genBasicTyped(Typed::kVoid); }
    static BasicTyped* genFloatTyped() { return genBasicTyped(Typed::kFloat); }
    static BasicTyped* genFloatMacroTyped() { return genBasicTyped(Typed::kFloatMacro); }

    static NamedTyped* genNamedTyped(const string& name, Typed* type);
    static NamedTyped* genNamedTyped(const string& name, Typed::VarType type);

    static FunTyped* genFunTyped(const list<NamedTyped*>& args, BasicTyped* result,
                                 FunTyped::FunAttribute attribute = FunTyped::kDefault)
    {
        return new FunTyped(args, result, attribute);
    }
    static VectorTyped* genVectorTyped(BasicTyped* type, int size) { return new VectorTyped(type, size); }
    static ArrayTyped*  genArrayTyped(Typed* type, int size, bool is_ptr = false)
    {
        return new ArrayTyped(type, size, is_ptr);
    }
    static StructTyped* genStructTyped(const string& name, const vector<NamedTyped*>& fields)
    {
        return new StructTyped(name, fields);
    }

    // Addresses
    static NamedAddress* genNamedAddress(const string& name, Address::AccessType access)
    {
        return new NamedAddress(name, access);
    }
    static IndexedAddress* genIndexedAddress(Address* address, ValueInst* index)
    {
        return new IndexedAddress(address, index);
    }

    // Helper build methods
    static DeclareVarInst* genDecArrayVar(const string& vname, Address::AccessType var_access, Typed* type, int size)
    {
        return genDeclareVarInst(genNamedAddress(vname, var_access), genArrayTyped(type, size));
    }

    static LoadVarInst* genLoadArrayVar(const string& vname, Address::AccessType var_access, ValueInst* index)
    {
        return genLoadVarInst(genIndexedAddress(genNamedAddress(vname, var_access), index));
    }
    // Actually same as genLoadArrayVar
    static LoadVarInst* genLoadStructPtrVar(const string& vname, Address::AccessType var_access, ValueInst* index)
    {
        return genLoadArrayVar(vname, var_access, index);
    }

    static StoreVarInst* genStoreArrayVar(const string& vname, Address::AccessType var_access, ValueInst* index,
                                          ValueInst* exp)
    {
        return genStoreVarInst(genIndexedAddress(genNamedAddress(vname, var_access), index), exp);
    }

    // Struct variable
    static DeclareVarInst* genDecStructVar(const string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, Address::kStruct), type, exp);
    }

    static DeclareVarInst* genDecVolatileStructVar(const string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, (Address::AccessType)(Address::kStruct | Address::kVolatile)),
                                 type, exp);
    }

    static DeclareVarInst* genDecArrayStructVar(const string& vname, Typed* type, int size)
    {
        return genDecArrayVar(vname, Address::kStruct, type, size);
    }

    static LoadVarInst* genLoadStructVar(const string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kStruct));
    }

    static LoadVarInst* genLoadMutRefStructVar(const string& vname)
    {
        return genLoadVarInst(
            genNamedAddress(vname, (Address::AccessType)(Address::kStruct | Address::kReference | Address::kMutable)));
    }

    static LoadVarInst* genVolatileLoadStructVar(const string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, (Address::AccessType)(Address::kStruct | Address::kVolatile)));
    }

    template <typename Iterator>
    static LoadVarInst* genLoadArrayStructVar(const string& vname, Iterator indexBegin, Iterator indexEnd)
    {
        typedef reverse_iterator<Iterator> Rit;
        Rit                                rbegin(indexEnd);
        Rit                                rend(indexBegin);

        Address* address = genNamedAddress(vname, Address::kStruct);
        for (Rit it = rbegin; it != rend; ++it) {
            address = genIndexedAddress(address, *it);
        }

        return genLoadVarInst(address);
    }

    static LoadVarInst* genLoadArrayStructVar(const string& vname, ValueInst* index)
    {
        vector<ValueInst*> indices;
        indices.push_back(index);
        return genLoadArrayStructVar(vname, indices.begin(), indices.end());
    }

    static LoadVarInst* genLoadArrayStructVar(const string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kStruct));
    }

    static LoadVarAddressInst* genLoadArrayStructVarAddress(const string& vname, ValueInst* index)
    {
        return genLoadVarAddressInst(genIndexedAddress(genNamedAddress(vname, Address::kStruct), index));
    }

    static StoreVarInst* genStoreStructVar(const string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kStruct), exp);
    }

    static StoreVarInst* genVolatileStoreStructVar(const string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, (Address::AccessType)(Address::kStruct | Address::kVolatile)),
                               exp);
    }

    template <typename Iterator>
    static StoreVarInst* genStoreArrayStructVar(const string& vname, ValueInst* exp, Iterator indexBegin,
                                                Iterator indexEnd)
    {
        typedef reverse_iterator<Iterator> Rit;
        Rit                                rbegin(indexEnd);
        Rit                                rend(indexBegin);

        Address* address = genNamedAddress(vname, Address::kStruct);
        for (Rit it = rbegin; it != rend; ++it) {
            address = genIndexedAddress(address, *it);
        }

        return genStoreVarInst(address, exp);
    }

    static StoreVarInst* genStoreArrayStructVar(const string& vname, ValueInst* index, ValueInst* exp)
    {
        vector<ValueInst*> indices;
        indices.push_back(index);
        return genStoreArrayStructVar(vname, exp, indices.begin(), indices.end());
    }

    static StoreVarInst* genStoreArrayStructVar(const string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kStruct), exp);
    }

    // Static struct variable
    static DeclareVarInst* genDecStaticStructVar(const string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, Address::kStaticStruct), type, exp);
    }

    static DeclareVarInst* genDecConstStaticStructVar(const string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(
            genNamedAddress(vname, (Address::AccessType)(Address::kStaticStruct | Address::kConst)), type, exp);
    }

    static LoadVarInst* genLoadStaticStructVar(const string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kStaticStruct));
    }

    static LoadVarInst* genLoadStaticMutRefStructVar(const string& vname)
    {
        return genLoadVarInst(genNamedAddress(
            vname, (Address::AccessType)(Address::kStaticStruct | Address::kReference | Address::kMutable)));
    }

    static StoreVarInst* genStoreStaticStructVar(const string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kStaticStruct), exp);
    }

    template <typename Iterator>
    static LoadVarInst* genLoadArrayStaticStructVar(const string& vname, Iterator indexBegin, Iterator indexEnd)
    {
        typedef reverse_iterator<Iterator> Rit;
        Rit                                rbegin(indexEnd);
        Rit                                rend(indexBegin);

        Address* address = genNamedAddress(vname, Address::kStaticStruct);
        for (Rit it = rbegin; it != rend; ++it) {
            address = genIndexedAddress(address, *it);
        }

        return genLoadVarInst(address);
    }

    static LoadVarInst* genLoadArrayStaticStructVar(const string& vname, ValueInst* index)
    {
        vector<ValueInst*> indices;
        indices.push_back(index);
        return genLoadArrayStaticStructVar(vname, indices.begin(), indices.end());
    }

    template <typename Iterator>
    static StoreVarInst* genStoreArrayStaticStructVar(const string& vname, ValueInst* exp, Iterator indexBegin,
                                                      Iterator indexEnd)
    {
        typedef reverse_iterator<Iterator> Rit;
        Rit                                rbegin(indexEnd);
        Rit                                rend(indexBegin);

        Address* address = genNamedAddress(vname, Address::kStaticStruct);
        for (Rit it = rbegin; it != rend; ++it) {
            address = genIndexedAddress(address, *it);
        }

        return genStoreVarInst(address, exp);
    }

    static StoreVarInst* genStoreArrayStaticStructVar(const string& vname, ValueInst* index, ValueInst* exp)
    {
        vector<ValueInst*> indices;
        indices.push_back(index);
        return genStoreArrayStructVar(vname, exp, indices.begin(), indices.end());
    }

    // Stack variable
    static DeclareVarInst* genDecStackVar(const string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, Address::kStack), type, exp);
    }

    static DeclareVarInst* genDecArrayStackVar(const string& vname, Typed* type, int size)
    {
        return genDecArrayVar(vname, Address::kStack, type, size);
    }

    static LoadVarInst* genLoadStackVar(const string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kStack));
    }

    static LoadVarAddressInst* genLoadStackVarAddress(const string& vname)
    {
        return genLoadVarAddressInst(genNamedAddress(vname, Address::kStack));
    }

    static LoadVarInst* genLoadArrayStackVar(const string& vname, ValueInst* index)
    {
        return genLoadVarInst(genIndexedAddress(genNamedAddress(vname, Address::kStack), index));
    }

    static LoadVarAddressInst* genLoadArrayStackVarAddress(const string& vname, ValueInst* index)
    {
        return genLoadVarAddressInst(genIndexedAddress(genNamedAddress(vname, Address::kStack), index));
    }

    static StoreVarInst* genStoreStackVar(const string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kStack), exp);
    }

    static StoreVarInst* genStoreArrayStackVar(const string& vname, ValueInst* index, ValueInst* exp)
    {
        return genStoreVarInst(genIndexedAddress(genNamedAddress(vname, Address::kStack), index), exp);
    }

    // Loop variable
    static DeclareVarInst* genDecLoopVar(const string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, Address::kLoop), type, exp);
    }

    static LoadVarInst* genLoadLoopVar(const string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kLoop));
    }

    static StoreVarInst* genStoreLoopVar(const string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kLoop), exp);
    }

    // FunArgs variable
    static LoadVarInst* genLoadFunArgsVar(const string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kFunArgs));
    }

    static LoadVarInst* genLoadArrayFunArgsVar(const string& vname, ValueInst* index)
    {
        return genLoadVarInst(genIndexedAddress(genNamedAddress(vname, Address::kFunArgs), index));
    }

    static StoreVarInst* genStoreArrayFunArgsVar(const string& vname, ValueInst* index, ValueInst* exp)
    {
        return genStoreVarInst(genIndexedAddress(genNamedAddress(vname, Address::kFunArgs), index), exp);
    }

    // Global variable
    static DeclareVarInst* genDecGlobalVar(const string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, Address::kGlobal), type, exp);
    }

    static DeclareVarInst* genDecConstGlobalVar(const string& vname, Typed* type, ValueInst* exp = nullptr)
    {
        return genDeclareVarInst(genNamedAddress(vname, (Address::AccessType)(Address::kGlobal | Address::kConst)),
                                 type, exp);
    }

    static LoadVarInst* genLoadGlobalVar(const string& vname)
    {
        return genLoadVarInst(genNamedAddress(vname, Address::kGlobal));
    }

    static StoreVarInst* genStoreGlobalVar(const string& vname, ValueInst* exp)
    {
        return genStoreVarInst(genNamedAddress(vname, Address::kGlobal), exp);
    }

    // Binop operations
    static BinopInst* genAdd(ValueInst* a1, ValueInst* a2) { return genBinopInst(kAdd, a1, a2); }

    static BinopInst* genAdd(ValueInst* a1, int a2) { return genBinopInst(kAdd, a1, genInt32NumInst(a2)); }

    static BinopInst* genSub(ValueInst* a1, ValueInst* a2) { return genBinopInst(kSub, a1, a2); }

    static BinopInst* genSub(ValueInst* a1, int a2) { return genBinopInst(kSub, a1, genInt32NumInst(a2)); }

    static BinopInst* genMul(ValueInst* a1, ValueInst* a2) { return genBinopInst(kMul, a1, a2); }

    static BinopInst* genDiv(ValueInst* a1, ValueInst* a2) { return genBinopInst(kDiv, a1, a2); }

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
    static DeclareFunInst* genVoidFunction(const string& name, BlockInst* code = new BlockInst());
    static DeclareFunInst* genVoidFunction(const string& name, list<NamedTyped*>& args, BlockInst* code,
                                           bool isvirtual = false);
    static DeclareFunInst* genFunction0(const string& name, Typed::VarType res, BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction1(const string& name, Typed::VarType res, const string& arg1,
                                        Typed::VarType arg1_ty, BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction2(const string& name, Typed::VarType res, const string& arg1,
                                        Typed::VarType arg1_ty, const string& arg2, Typed::VarType arg2_ty,
                                        BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction3(const string& name, Typed::VarType res, const string& arg1,
                                        Typed::VarType arg1_ty, const string& arg2, Typed::VarType arg2_ty,
                                        const string& arg3, Typed::VarType arg3_ty, BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction4(const string& name, Typed::VarType res, const string& arg1,
                                        Typed::VarType arg1_ty, const string& arg2, Typed::VarType arg2_ty,
                                        const string& arg3, Typed::VarType arg3_ty, const string& arg4,
                                        Typed::VarType arg4_ty, BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction5(const string& name, Typed::VarType res, const string& arg1,
                                        Typed::VarType arg1_ty, const string& arg2, Typed::VarType arg2_ty,
                                        const string& arg3, Typed::VarType arg3_ty, const string& arg4,
                                        Typed::VarType arg4_ty, const string& arg5, Typed::VarType arg5_ty,
                                        BlockInst* code = new BlockInst());
    static DeclareFunInst* genFunction6(const string& name, Typed::VarType res, const string& arg1,
                                        Typed::VarType arg1_ty, const string& arg2, Typed::VarType arg2_ty,
                                        const string& arg3, Typed::VarType arg3_ty, const string& arg4,
                                        Typed::VarType arg4_ty, const string& arg5, Typed::VarType arg5_ty,
                                        const string& arg6, Typed::VarType arg6_ty, BlockInst* code = new BlockInst());

    // Convert a signal type in a Fir type by using an intermediate Tree based implementation to assure type creation
    // unicity. HACK : 09/12/11
    // static DeclareTypeInst* genType(AudioType* type);

    // HACK : 09/12/11
    // static Typed* mapFIRType(AudioType* type);
};

/* syntactic sugar for index computations
 *
 * wrapper for ValueInst* with support for basic arithmetics
 *
 */
struct FIRIndex {
    /* explicit constructors in order to avoid the generation of implicit conversions */
    explicit FIRIndex(ValueInst* inst) : fValue(inst) {}

    explicit FIRIndex(int i) : fValue(InstBuilder::genInt32NumInst(i)) {}

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

    // Mult
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
            | Select (Value1, Value2, Value3)
            | Binop (Opcode, Value1, Value2)
            | Cast (Type, Value)
            | Null ()

Code rewritting :

For WSS:

1) change access of variable of type kStack in kStruct

Loop to function rewritting (faster compilation ?):

2 methods

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

Vision des boucles (count, liste de vecteurs d'entrée, liste de vecteurs de sorties) différente du prototype externe
compute(count, float**, float**) ou veut homogenéiser

D'ou:

DAG de boucles au format (count, liste de vecteurs d'entrée, liste de vecteurs de sorties)
compute(count, float**, float**)

1) générer le header qui prépare les tableaux d'entrée et de sortie séparés
2) compiler les boucles

Comment différencier les vecteurs sans retard (qu'on peut transformer en scalaire) des vecteurs avec retard ? Avec un
nommage spécifique ?

TODO : gestion des indices de boucles:

 - dans IndexedAddress, mettre un ValueInst à la place de fIndex, mettre à jour les visiteurs

 - dans InstructionsCompiler, generer des accès avec "LoadVar" (loop-index)

 - dans ForLoopInst, fName devient un "DeclareVarInst" (permet de nommer et d'initialiser l'indice), ajout d'une
expression test, ajout de ValueInst fNext, calcul qui utilise fName.

 - nouveau type d'accès kLoop pour les variables de loop

 - lors des transformations sur les loops, Loop2FunctionBuider, SeqLoopBuilderVisitor, "désactiver" les statements qui
manipulent les indices de la boucle ?? (pas besoin, ils n'apparaissent pas dans le corps de le boucle, par contre
l'indice de la boucle est utilisé dans le corps de la boucle, il faut le faire correspondre au nouvel indice de boucle,
renommage nécessaire ?)

 - utiliser le *même* nom d'index dans ForLoopInst et dans le code interne de la loop

*/
