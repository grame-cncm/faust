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

#ifndef _DLANG_INSTRUCTIONS_H
#define _DLANG_INSTRUCTIONS_H

using namespace std;

#include "text_instructions.hh"
#include "type_manager.hh"

class DLangInstVisitor : public TextInstVisitor {
   private:
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated at most once in the module.
     */
    static map<string, bool> gFunctionSymbolTable;

    // Polymorphic math functions
    map<string, string> gPolyMathLibTable;

   public:
    using TextInstVisitor::visit;

    DLangInstVisitor(std::ostream* out, int tab = 0) : TextInstVisitor(out, ".", ifloat(), "[]", tab)
    {
        if (gFunctionSymbolTable.size()) {
            return;
        }

        gFunctionSymbolTable["abs"]   = "std.math.abs";
        gFunctionSymbolTable["max_i"] = "std.algorithm.max";
        gFunctionSymbolTable["min_i"] = "std.algorithm.min";

        // Float version
        gFunctionSymbolTable["fabsf"]  = "std.math.fabs";
        gFunctionSymbolTable["acosf"]  = "std.math.acos";
        gFunctionSymbolTable["asinf"]  = "std.math.asin";
        gFunctionSymbolTable["atanf"]  = "std.math.atan";
        gFunctionSymbolTable["atan2f"] = "std.math.atan2";
        gFunctionSymbolTable["ceilf"]  = "std.math.ceil";
        gFunctionSymbolTable["cosf"]   = "std.math.cos";
        gFunctionSymbolTable["coshf"]  = "std.math.cosh";
        gFunctionSymbolTable["expf"]   = "std.math.exp";
        gFunctionSymbolTable["floorf"] = "std.math.floor";
        gFunctionSymbolTable["fmodf"]  = "std.math.fmod";
        gFunctionSymbolTable["logf"]   = "std.math.log";
        gFunctionSymbolTable["log10f"] = "std.math.log10";
        gFunctionSymbolTable["max_f"]  = "std.math.fmax";
        gFunctionSymbolTable["min_f"]  = "std.math.fmin";
        gFunctionSymbolTable["powf"]   = "std.math.pow";
        gFunctionSymbolTable["roundf"] = "std.math.round";
        gFunctionSymbolTable["sinf"]   = "std.math.sin";
        gFunctionSymbolTable["sinhf"]  = "std.math.sinh";
        gFunctionSymbolTable["sqrtf"]  = "std.math.sqrt";
        gFunctionSymbolTable["tanf"]   = "std.math.tan";
        gFunctionSymbolTable["tanhf"]  = "std.math.tanh";

        // Double version
        gFunctionSymbolTable["fabs"]  = "std.math.fabs";
        gFunctionSymbolTable["acos"]  = "std.math.acos";
        gFunctionSymbolTable["asin"]  = "std.math.asin";
        gFunctionSymbolTable["atan"]  = "std.math.atan";
        gFunctionSymbolTable["atan2"] = "std.math.atan2";
        gFunctionSymbolTable["ceil"]  = "std.math.ceil";
        gFunctionSymbolTable["cos"]   = "std.math.cos";
        gFunctionSymbolTable["cosh"]  = "std.math.cosh";
        gFunctionSymbolTable["exp"]   = "std.math.exp";
        gFunctionSymbolTable["floor"] = "std.math.floor";
        gFunctionSymbolTable["fmod"]  = "std.math.fmod";
        gFunctionSymbolTable["log"]   = "std.math.log";
        gFunctionSymbolTable["log10"] = "std.math.log10";
        gFunctionSymbolTable["max_"]  = "std.math.fmax";
        gFunctionSymbolTable["min_"]  = "std.math.fmin";
        gFunctionSymbolTable["pow"]   = "std.math.pow";
        gFunctionSymbolTable["round"] = "std.math.round";
        gFunctionSymbolTable["sin"]   = "std.math.sin";
        gFunctionSymbolTable["sinh"]  = "std.math.sinh";
        gFunctionSymbolTable["sqrt"]  = "std.math.sqrt";
        gFunctionSymbolTable["tan"]   = "std.math.tan";
        gFunctionSymbolTable["tanh"]  = "std.math.tanh";
    }

    virtual ~DLangInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {
        // Special case
        if (inst->fZone == "0") {
            *fOut << "ui_interface.declare(" << inst->fZone << ", " << quote(inst->fKey) << ", " << quote(inst->fValue)
                  << ")";
        } else {
            *fOut << "ui_interface.declare(&" << inst->fZone << ", " << quote(inst->fKey) << ", "
                  << quote(inst->fValue) << ")";
        }
        EndLine();
    }

    virtual void visit(OpenboxInst* inst)
    {
        string name;
        switch (inst->fOrient) {
            case OpenboxInst::kVerticalBox:
                name = "ui_interface.openVerticalBox(";
                break;
            case OpenboxInst::kHorizontalBox:
                name = "ui_interface.openHorizontalBox(";
                break;
            case OpenboxInst::kTabBox:
                name = "ui_interface.openTabBox(";
                break;
        }
        *fOut << name << quote(inst->fName) << ")";
        EndLine();
    }

    virtual void visit(CloseboxInst* inst)
    {
        *fOut << "ui_interface.closeBox();";
        tab(fTab, *fOut);
    }

    virtual void visit(AddButtonInst* inst)
    {
        if (inst->fType == AddButtonInst::kDefaultButton) {
            *fOut << "ui_interface.addButton(" << quote(inst->fLabel) << ", &" << inst->fZone << ")";
        } else {
            *fOut << "ui_interface.addCheckButton(" << quote(inst->fLabel) << ", &" << inst->fZone << ")";
        }
        EndLine();
    }

    virtual void visit(AddSliderInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                name = "ui_interface.addHorizontalSlider";
                break;
            case AddSliderInst::kVertical:
                name = "ui_interface.addVerticalSlider";
                break;
            case AddSliderInst::kNumEntry:
                name = "ui_interface.addNumEntry";
                break;
        }
        *fOut << name << "(" << quote(inst->fLabel) << ", "
              << "&" << inst->fZone << ", " << checkReal(inst->fInit) << ", " << checkReal(inst->fMin) << ", "
              << checkReal(inst->fMax) << ", " << checkReal(inst->fStep) << ")";
        EndLine();
    }

    virtual void visit(AddBargraphInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                name = "ui_interface.addHorizontalBargraph";
                break;
            case AddBargraphInst::kVertical:
                name = "ui_interface.addVerticalBargraph";
                break;
        }
        *fOut << name << "(" << quote(inst->fLabel) << ", &" << inst->fZone << ", " << checkReal(inst->fMin) << ", "
              << checkReal(inst->fMax) << ")";
        EndLine();
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        *fOut << "ui_interface.addSoundfile(" << quote(inst->fLabel) << ", " << quote(inst->fURL) << ", &"
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
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        if (array_typed && array_typed->fSize > 1) {
            string type = fTypeManager->fTypeDirectTable[array_typed->fType->getType()];
            if (inst->fValue) {
                *fOut << type << "[] " << inst->fAddress->getName() << " = ";
                inst->fValue->accept(this);
            } else {
                *fOut << type << "[] " << inst->fAddress->getName() << " = new " << type << "[" << array_typed->fSize
                      << "]";
            }
        } else {
            *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
            if (inst->fValue) {
                *fOut << " = ";
                inst->fValue->accept(this);
            }
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

        if (inst->fType->fAttribute & FunTyped::kLocal || inst->fType->fAttribute & FunTyped::kStatic) {
            *fOut << "static ";
        }

        // Prototype
        *fOut << fTypeManager->generateType(inst->fType->fResult, generateFunName(inst->fName));
        generateFunDefArgs(inst);
        generateFunDefBody(inst);
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        *fOut << "&";
        inst->fAddress->accept(this);
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

    /*
     Indexed adresses can actually be values in an array or fields in a struct type
     */
    virtual void visit(IndexedAddress* indexed)
    {
        indexed->fAddress->accept(this);
        DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
        if (struct_type) {
            Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->fIndex);
            *fOut << "." << struct_type->fType->getName(field_index->fNum);
        } else {
            if (dynamic_cast<Int32NumInst*>(indexed->fIndex)) {
                *fOut << "[";
                indexed->fIndex->accept(this);
                *fOut << "]";
            } else {
                // wrap code is automatically added by the SOUL compiler (and the same if [idex] syntax is used)
                *fOut << ".at (";
                indexed->fIndex->accept(this);
                *fOut << ")";
            }
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
                *fOut << "*reinterpret_cast<long long*>(&";
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
        name = (gPolyMathLibTable.find(name) != gPolyMathLibTable.end()) ? gPolyMathLibTable[name] : name;
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

class DLangVecInstVisitor : public DLangInstVisitor {
   public:
    DLangVecInstVisitor(std::ostream* out, int tab = 0) : DLangInstVisitor(out, tab) {}
};

#endif
