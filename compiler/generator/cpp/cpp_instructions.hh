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

#ifndef _CPP_INSTRUCTIONS_H
#define _CPP_INSTRUCTIONS_H

using namespace std;

#include "struct_manager.hh"
#include "text_instructions.hh"
#include "type_manager.hh"

/**
 * Implement C++ FIR visitor.
 */

class CPPInstVisitor : public TextInstVisitor {
   private:
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated at most once in the module.
     */
    static map<string, bool> gFunctionSymbolTable;

    // Polymorphic math functions
    map<string, string> gPolyMathLibTable;

    string cast2FAUSTFLOAT(const string& str) { return "FAUSTFLOAT(" + str + ")"; }

   public:
    using TextInstVisitor::visit;

    CPPInstVisitor(std::ostream* out, int tab = 0)
        : TextInstVisitor(out, "->", new CStringTypeManager(xfloat(), "*"), tab)
    {
        // Mark all math.h functions as generated...
        gFunctionSymbolTable["abs"] = true;

        gFunctionSymbolTable["max_i"] = true;
        gFunctionSymbolTable["min_i"] = true;

        // Float version
        gFunctionSymbolTable["fabsf"]      = true;
        gFunctionSymbolTable["acosf"]      = true;
        gFunctionSymbolTable["asinf"]      = true;
        gFunctionSymbolTable["atanf"]      = true;
        gFunctionSymbolTable["atan2f"]     = true;
        gFunctionSymbolTable["ceilf"]      = true;
        gFunctionSymbolTable["cosf"]       = true;
        gFunctionSymbolTable["expf"]       = true;
        gFunctionSymbolTable["exp10f"]     = true;
        gFunctionSymbolTable["floorf"]     = true;
        gFunctionSymbolTable["fmodf"]      = true;
        gFunctionSymbolTable["logf"]       = true;
        gFunctionSymbolTable["log10f"]     = true;
        gFunctionSymbolTable["powf"]       = true;
        gFunctionSymbolTable["remainderf"] = true;
        gFunctionSymbolTable["rintf"]      = true;
        gFunctionSymbolTable["roundf"]     = true;
        gFunctionSymbolTable["sinf"]       = true;
        gFunctionSymbolTable["sqrtf"]      = true;
        gFunctionSymbolTable["tanf"]       = true;

        // Double version
        gFunctionSymbolTable["fabs"]      = true;
        gFunctionSymbolTable["acos"]      = true;
        gFunctionSymbolTable["asin"]      = true;
        gFunctionSymbolTable["atan"]      = true;
        gFunctionSymbolTable["atan2"]     = true;
        gFunctionSymbolTable["ceil"]      = true;
        gFunctionSymbolTable["cos"]       = true;
        gFunctionSymbolTable["exp"]       = true;
        gFunctionSymbolTable["exp10"]     = true;
        gFunctionSymbolTable["floor"]     = true;
        gFunctionSymbolTable["fmod"]      = true;
        gFunctionSymbolTable["log"]       = true;
        gFunctionSymbolTable["log10"]     = true;
        gFunctionSymbolTable["pow"]       = true;
        gFunctionSymbolTable["remainder"] = true;
        gFunctionSymbolTable["rint"]      = true;
        gFunctionSymbolTable["round"]     = true;
        gFunctionSymbolTable["sin"]       = true;
        gFunctionSymbolTable["sqrt"]      = true;
        gFunctionSymbolTable["tan"]       = true;

        // Quad version
        gFunctionSymbolTable["fabsl"]      = true;
        gFunctionSymbolTable["acosl"]      = true;
        gFunctionSymbolTable["asinl"]      = true;
        gFunctionSymbolTable["atanl"]      = true;
        gFunctionSymbolTable["atan2l"]     = true;
        gFunctionSymbolTable["ceill"]      = true;
        gFunctionSymbolTable["cosl"]       = true;
        gFunctionSymbolTable["expl"]       = true;
        gFunctionSymbolTable["exp10l"]     = true;
        gFunctionSymbolTable["floorl"]     = true;
        gFunctionSymbolTable["fmodl"]      = true;
        gFunctionSymbolTable["logl"]       = true;
        gFunctionSymbolTable["log10l"]     = true;
        gFunctionSymbolTable["powl"]       = true;
        gFunctionSymbolTable["remainderl"] = true;
        gFunctionSymbolTable["rintl"]      = true;
        gFunctionSymbolTable["roundl"]     = true;
        gFunctionSymbolTable["sinl"]       = true;
        gFunctionSymbolTable["sqrtl"]      = true;
        gFunctionSymbolTable["tanl"]       = true;

        // Polymath mapping int version
        gPolyMathLibTable["abs"]   = "std::abs";
        gPolyMathLibTable["max_i"] = "std::max<int>";
        gPolyMathLibTable["min_i"] = "std::min<int>";

        // Polymath mapping float version
        gPolyMathLibTable["max_f"] = "std::max<float>";
        gPolyMathLibTable["min_f"] = "std::min<float>";

        gPolyMathLibTable["fabsf"]      = "std::fabs";
        gPolyMathLibTable["acosf"]      = "std::acos";
        gPolyMathLibTable["asinf"]      = "std::asin";
        gPolyMathLibTable["atanf"]      = "std::atan";
        gPolyMathLibTable["atan2f"]     = "std::atan2";
        gPolyMathLibTable["ceilf"]      = "std::ceil";
        gPolyMathLibTable["cosf"]       = "std::cos";
        gPolyMathLibTable["expf"]       = "std::exp";
        gPolyMathLibTable["exp2f"]      = "std::exp2";
        gPolyMathLibTable["exp10f"]     = "exp10f";
        gPolyMathLibTable["floorf"]     = "std::floor";
        gPolyMathLibTable["fmodf"]      = "std::fmod";
        gPolyMathLibTable["logf"]       = "std::log";
        gPolyMathLibTable["log2f"]      = "std::log2";
        gPolyMathLibTable["log10f"]     = "std::log10";
        gPolyMathLibTable["powf"]       = "std::pow";
        gPolyMathLibTable["remainderf"] = "std::remainder";
        gPolyMathLibTable["rintf"]      = "std::rint";
        gPolyMathLibTable["roundf"]     = "std::round";
        gPolyMathLibTable["sinf"]       = "std::sin";
        gPolyMathLibTable["sqrtf"]      = "std::sqrt";
        gPolyMathLibTable["tanf"]       = "std::tan";

        // Polymath mapping double version
        gPolyMathLibTable["max_"] = "std::max<double>";
        gPolyMathLibTable["min_"] = "std::min<double>";

        gPolyMathLibTable["fabs"]      = "std::fabs";
        gPolyMathLibTable["acos"]      = "std::acos";
        gPolyMathLibTable["asin"]      = "std::asin";
        gPolyMathLibTable["atan"]      = "std::atan";
        gPolyMathLibTable["atan2"]     = "std::atan2";
        gPolyMathLibTable["ceil"]      = "std::ceil";
        gPolyMathLibTable["cos"]       = "std::cos";
        gPolyMathLibTable["exp"]       = "std::exp";
        gPolyMathLibTable["exp2"]      = "std::exp2";
        gPolyMathLibTable["exp10"]     = "exp10";
        gPolyMathLibTable["floor"]     = "std::floor";
        gPolyMathLibTable["fmod"]      = "std::fmod";
        gPolyMathLibTable["log"]       = "std::log";
        gPolyMathLibTable["log2"]      = "std::log2";
        gPolyMathLibTable["log10"]     = "std::log10";
        gPolyMathLibTable["pow"]       = "std::pow";
        gPolyMathLibTable["remainder"] = "std::remainder";
        gPolyMathLibTable["rint"]      = "std::rint";
        gPolyMathLibTable["round"]     = "std::round";
        gPolyMathLibTable["sin"]       = "std::sin";
        gPolyMathLibTable["sqrt"]      = "std::sqrt";
        gPolyMathLibTable["tan"]       = "std::tan";

        // Polymath mapping quad version
        gPolyMathLibTable["max_l"] = "std::max<quad>";
        gPolyMathLibTable["min_l"] = "std::min<quad>";

        gPolyMathLibTable["fabsl"]      = "std::fabs";
        gPolyMathLibTable["acosl"]      = "std::acos";
        gPolyMathLibTable["asinl"]      = "std::asin";
        gPolyMathLibTable["atanl"]      = "std::atan";
        gPolyMathLibTable["atan2l"]     = "std::atan2";
        gPolyMathLibTable["ceill"]      = "std::ceil";
        gPolyMathLibTable["cosl"]       = "std::cos";
        gPolyMathLibTable["expl"]       = "std::exp";
        gPolyMathLibTable["exp2l"]      = "std::exp2";
        gPolyMathLibTable["exp10l"]     = "exp10";
        gPolyMathLibTable["floorl"]     = "std::floor";
        gPolyMathLibTable["fmodl"]      = "std::fmod";
        gPolyMathLibTable["logl"]       = "std::log";
        gPolyMathLibTable["log2l"]      = "std::log2";
        gPolyMathLibTable["log10l"]     = "std::log10";
        gPolyMathLibTable["powl"]       = "std::pow";
        gPolyMathLibTable["remainderl"] = "std::remainder";
        gPolyMathLibTable["rintl"]      = "std::rint";
        gPolyMathLibTable["roundl"]     = "std::round";
        gPolyMathLibTable["sinl"]       = "std::sin";
        gPolyMathLibTable["sqrtl"]      = "std::sqrt";
        gPolyMathLibTable["tanl"]       = "std::tan";
    }

    virtual ~CPPInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {
        // Special case
        if (inst->fZone == "0") {
            *fOut << "ui_interface->declare(" << inst->fZone << ", " << quote(inst->fKey) << ", " << quote(inst->fValue)
                  << ")";
        } else {
            *fOut << "ui_interface->declare(&" << inst->fZone << ", " << quote(inst->fKey) << ", "
                  << quote(inst->fValue) << ")";
        }
        EndLine();
    }

    virtual void visit(OpenboxInst* inst)
    {
        string name;
        switch (inst->fOrient) {
            case OpenboxInst::kVerticalBox:
                name = "ui_interface->openVerticalBox(";
                break;
            case OpenboxInst::kHorizontalBox:
                name = "ui_interface->openHorizontalBox(";
                break;
            case OpenboxInst::kTabBox:
                name = "ui_interface->openTabBox(";
                break;
        }
        *fOut << name << quote(inst->fName) << ")";
        EndLine();
    }

    virtual void visit(CloseboxInst* inst)
    {
        *fOut << "ui_interface->closeBox();";
        tab(fTab, *fOut);
    }

    virtual void visit(AddButtonInst* inst)
    {
        if (inst->fType == AddButtonInst::kDefaultButton) {
            *fOut << "ui_interface->addButton(" << quote(inst->fLabel) << ", &" << inst->fZone << ")";
        } else {
            *fOut << "ui_interface->addCheckButton(" << quote(inst->fLabel) << ", &" << inst->fZone << ")";
        }
        EndLine();
    }

    virtual void visit(AddSliderInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                name = "ui_interface->addHorizontalSlider";
                break;
            case AddSliderInst::kVertical:
                name = "ui_interface->addVerticalSlider";
                break;
            case AddSliderInst::kNumEntry:
                name = "ui_interface->addNumEntry";
                break;
        }
        *fOut << name << "(" << quote(inst->fLabel) << ", "
              << "&" << inst->fZone << ", " << cast2FAUSTFLOAT(checkReal(inst->fInit)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMin)) << ", " << cast2FAUSTFLOAT(checkReal(inst->fMax)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fStep)) << ")";
        EndLine();
    }

    virtual void visit(AddBargraphInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                name = "ui_interface->addHorizontalBargraph";
                break;
            case AddBargraphInst::kVertical:
                name = "ui_interface->addVerticalBargraph";
                break;
        }
        *fOut << name << "(" << quote(inst->fLabel) << ", &" << inst->fZone << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMin)) << ", " << cast2FAUSTFLOAT(checkReal(inst->fMax)) << ")";
        EndLine();
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        *fOut << "ui_interface->addSoundfile(" << quote(inst->fLabel) << ", " << quote(inst->fURL) << ", &"
              << inst->fSFZone << ")";
        EndLine();
    }

    virtual void visit(DeclareVarInst* inst)
    {
        if (inst->fAddress->getAccess() & Address::kConst) {
            *fOut << "const ";
        }

        if (inst->fAddress->getAccess() & Address::kStaticStruct) {
            *fOut << "static ";
        }

        if (inst->fAddress->getAccess() & Address::kVolatile) {
            *fOut << "volatile ";
        }

        *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
        if (inst->fValue) {
            *fOut << " = ";
            inst->fValue->accept(this);
        }
        EndLine();
    }

    virtual void visit(DeclareFunInst* inst)
    {
        // Already generated
        if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
            return;
        } else {
            gFunctionSymbolTable[inst->fName] = true;
        }

        // Defined as macro in the architecture file...
        if (checkMinMax(inst->fName)) {
            return;
        }

        // Prototype arguments
        if (inst->fType->fAttribute & FunTyped::kInline) {
            *fOut << "inline ";
        }

        if (inst->fType->fAttribute & FunTyped::kVirtual) {
            *fOut << "virtual ";
        }

        if (inst->fType->fAttribute & FunTyped::kLocal || inst->fType->fAttribute & FunTyped::kStatic) {
            *fOut << "static ";
        }
    
        if (inst->fType->fAttribute & FunTyped::kStaticConstExpr) {
            *fOut << "static constexpr ";
        }

        // Prototype
        *fOut << fTypeManager->generateType(inst->fType->fResult, generateFunName(inst->fName));
        generateFunDefArgs(inst);
        generateFunDefBody(inst);
    }

    virtual void generateFunDefArgs(DeclareFunInst* inst)
    {
        *fOut << "(";

        size_t size = inst->fType->fArgsTypes.size(), i = 0;
        for (const auto& it : inst->fType->fArgsTypes) {
            // Pointers are set with 'noalias' for non paired arguments, which are garantied to be unique
            if (isPtrType(it->getType()) && !inst->fType->isPairedFunArg(it->fName)) {
                *fOut << fTypeManager->generateType(it, NamedTyped::kNoalias);
            } else {
                *fOut << fTypeManager->generateType(it);
            }
            if (i++ < size - 1) *fOut << ", ";
        }
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        *fOut << "&";
        inst->fAddress->accept(this);
    }

    virtual void visit(BinopInst* inst)
    {
        // Special case for 'logical right-shift'
        if (strcmp(gBinOpTable[inst->fOpcode]->fName, ">>>") == 0) {
            Typed::VarType type = TypingVisitor::getType(inst->fInst1);
            if (isInt64Type(type)) {
                *fOut << "(int64_t(uint64_t(";
            } else if (isInt32Type(type)) {
                *fOut << "(int32_t(uint32_t(";
            } else {
                faustassert(false);
            }
            inst->fInst1->accept(this);
            *fOut << ") >> ";
            inst->fInst2->accept(this);
            *fOut << "))";
        } else {
            TextInstVisitor::visit(inst);
        }
    }

    virtual void visit(FixedPointNumInst* inst) { *fOut << "fixpoint_t(" << checkFloat(inst->fNum) << ")"; }

    virtual void visit(FixedPointArrayNumInst* inst)
    {
        char sep = '{';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << "fixpoint_t(" << checkFloat(inst->fNumTable[i]) << ")";
            sep = ',';
        }
        *fOut << '}';
    }

    virtual void visit(::CastInst* inst)
    {
        string type = fTypeManager->generateType(inst->fType);
        if (endWith(type, "*")) {
            *fOut << "static_cast<" << type << ">(";
            inst->fInst->accept(this);
            *fOut << ")";
        } else {
            *fOut << type << "(";
            inst->fInst->accept(this);
            *fOut << ")";
        }
    }

    virtual void visit(BitcastInst* inst)
    {
        switch (inst->fType->getType()) {
            case Typed::kInt32:
                *fOut << "*reinterpret_cast<int*>(&";
                inst->fInst->accept(this);
                *fOut << ")";
                break;
            case Typed::kInt64:
                *fOut << "*reinterpret_cast<int64_t*>(&";
                inst->fInst->accept(this);
                *fOut << ")";
                break;
            case Typed::kFloat:
                *fOut << "*reinterpret_cast<float*>(&";
                inst->fInst->accept(this);
                *fOut << ")";
                break;
            case Typed::kDouble:
                *fOut << "*reinterpret_cast<double*>(&";
                inst->fInst->accept(this);
                *fOut << ")";
                break;
            default:
                faustassert(false);
                break;
        }
    }

    virtual void visit(FunCallInst* inst)
    {
        string name = gGlobal->getMathFunction(inst->fName);
        name        = (gPolyMathLibTable.find(name) != gPolyMathLibTable.end()) ? gPolyMathLibTable[name] : name;
        generateFunCall(inst, name);
    }

    virtual void visit(ForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) return;

        if (gGlobal->gClang && !inst->fIsRecursive) {
            *fOut << "#pragma clang loop vectorize(enable) interleave(enable)";
            tab(fTab, *fOut);
        }
        TextInstVisitor::visit(inst);
    }

    static void cleanup() { gFunctionSymbolTable.clear(); }
};

/**
 Implement C++ FIR visitor: used for -os1 mode (TODO : does not work with 'soundfile').
*/

class CPPInstVisitor1 : public CPPInstVisitor {
   private:
    // Fields are moved in iZone/fZone model
    StructInstVisitor fStructVisitor;

   public:
    CPPInstVisitor1(std::ostream* out, int tab = 0) : CPPInstVisitor(out, tab) {}

    virtual void visit(AddSoundfileInst* inst)
    {
        // Not supported for now
        throw faustexception("ERROR : AddSoundfileInst not supported for -osX mode\n");
    }

    virtual void visit(DeclareVarInst* inst)
    {
        Address::AccessType access = inst->fAddress->getAccess();
        string              name   = inst->fAddress->getName();
        if (((access & Address::kStruct) || (access & Address::kStaticStruct)) && !isControl(name)) {
            fStructVisitor.visit(inst);
        } else {
            CPPInstVisitor::visit(inst);
        }
    }

    virtual void visit(NamedAddress* named)
    {
        Typed::VarType type;
        string         name = named->getName();

        if (fStructVisitor.hasField(name, type)) {
            if (type == Typed::kInt32) {
                FIRIndex value = FIRIndex(fStructVisitor.getFieldIntOffset(name) / sizeof(int));
                InstBuilder::genLoadArrayFunArgsVar("iZone", value)->accept(this);
            } else {
                FIRIndex value = FIRIndex(fStructVisitor.getFieldRealOffset(name) / ifloatsize());
                InstBuilder::genLoadArrayFunArgsVar("fZone", value)->accept(this);
            }
        } else {
            TextInstVisitor::visit(named);
        }
    }

    virtual void visit(IndexedAddress* indexed)
    {
        Typed::VarType type;
        string         name = indexed->getName();

        if (fStructVisitor.hasField(name, type)) {
            if (type == Typed::kInt32) {
                FIRIndex value = FIRIndex(indexed->getIndex()) + fStructVisitor.getFieldIntOffset(name) / sizeof(int);
                InstBuilder::genLoadArrayFunArgsVar("iZone", value)->accept(this);
            } else {
                FIRIndex value = FIRIndex(indexed->getIndex()) + fStructVisitor.getFieldRealOffset(name) / ifloatsize();
                InstBuilder::genLoadArrayFunArgsVar("fZone", value)->accept(this);
            }
        } else {
            TextInstVisitor::visit(indexed);
        }
    }

    // Size is expressed in unit of the actual type (so 'int' or 'float/double')
    int getIntZoneSize() { return fStructVisitor.getStructIntSize() / sizeof(int); }
    int getRealZoneSize() { return fStructVisitor.getStructRealSize() / ifloatsize(); }
};

/**
 Implement C++ FIR visitor: Used for -os2 mode, accessing iZone/fZone as function args (TODO : does not work with
 'soundfile').
 */

class CPPInstVisitor2 : public CPPInstVisitor {
   protected:
    // Fields are distributed between the DSP struct and iZone/fZone model
    StructInstVisitor1 fStructVisitor;

   public:
    CPPInstVisitor2(std::ostream* out, int external_memory, int tab = 0)
        : CPPInstVisitor(out, tab), fStructVisitor(external_memory, 4)
    {
    }

    virtual void visit(DeclareVarInst* inst)
    {
        Address::AccessType access = inst->fAddress->getAccess();
        string              name   = inst->fAddress->getName();
        if (((access & Address::kStruct) || (access & Address::kStaticStruct)) && !isControl(name)) {
            fStructVisitor.visit(inst);
            // Local fields have to be generated
            if (fStructVisitor.getFieldMemoryType(name) == MemoryDesc::kLocal) {
                CPPInstVisitor::visit(inst);
            }
        } else {
            CPPInstVisitor::visit(inst);
        }
    }

    virtual void visit(IndexedAddress* indexed)
    {
        Typed::VarType type;
        string         name = indexed->getName();

        if (fStructVisitor.hasField(name, type) && fStructVisitor.getFieldMemoryType(name) == MemoryDesc::kExternal) {
            if (type == Typed::kInt32) {
                FIRIndex value = FIRIndex(indexed->getIndex()) + fStructVisitor.getFieldIntOffset(name) / sizeof(int);
                InstBuilder::genLoadArrayFunArgsVar("iZone", value)->accept(this);
            } else {
                FIRIndex value = FIRIndex(indexed->getIndex()) + fStructVisitor.getFieldRealOffset(name) / ifloatsize();
                InstBuilder::genLoadArrayFunArgsVar("fZone", value)->accept(this);
            }
        } else {
            TextInstVisitor::visit(indexed);
        }
    }

    // Size is expressed in unit of the actual type (so 'int' or 'float/double')
    int getIntZoneSize() { return fStructVisitor.getStructIntSize() / sizeof(int); }
    int getRealZoneSize() { return fStructVisitor.getStructRealSize() / ifloatsize(); }
};

/**
 Implement C++ FIR visitor: used for -os3 mode, accessing iZone/fZone in DSP struct (TODO : does not work with
 'soundfile').
 */

class CPPInstVisitor3 : public CPPInstVisitor2 {
   public:
    CPPInstVisitor3(std::ostream* out, int external_memory, int tab = 0) : CPPInstVisitor2(out, external_memory, tab) {}

    virtual void visit(IndexedAddress* indexed)
    {
        Typed::VarType type;
        string         name = indexed->getName();

        if (fStructVisitor.hasField(name, type) && fStructVisitor.getFieldMemoryType(name) == MemoryDesc::kExternal) {
            if (type == Typed::kInt32) {
                FIRIndex value = FIRIndex(indexed->getIndex()) + fStructVisitor.getFieldIntOffset(name) / sizeof(int);
                InstBuilder::genLoadArrayStructVar("iZone", value)->accept(this);
            } else {
                FIRIndex value = FIRIndex(indexed->getIndex()) + fStructVisitor.getFieldRealOffset(name) / ifloatsize();
                InstBuilder::genLoadArrayStructVar("fZone", value)->accept(this);
            }
        } else {
            TextInstVisitor::visit(indexed);
        }
    }
};

class CPPVecInstVisitor : public CPPInstVisitor {
   public:
    CPPVecInstVisitor(std::ostream* out, int tab = 0) : CPPInstVisitor(out, tab) {}
};

#endif
