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
    
    string cast2FAUSTFLOAT(const string& str) { return "cast(FAUSTFLOAT)" + str; }

   public:
    using TextInstVisitor::visit;

    DLangInstVisitor(std::ostream* out, int tab = 0) : TextInstVisitor(out, ".", xfloat(), "*", tab)
    {
        // Set 64 bits types
        fTypeManager->fTypeDirectTable[Typed::kInt64]     = "long";
        fTypeManager->fTypeDirectTable[Typed::kInt64_ptr] = "long*";
        fTypeManager->fTypeDirectTable[Typed::kInt64_vec] = "vector<long>";
     
        // Int version
        gPolyMathLibTable["abs"]   = "std.math.abs";
        gPolyMathLibTable["max_i"] = "max";
        gPolyMathLibTable["min_i"] = "min";
        gPolyMathLibTable["rint"] = "round";

        // Float version
        gPolyMathLibTable["fabsf"]  = "fabs";
        gPolyMathLibTable["acosf"]  = "acos";
        gPolyMathLibTable["asinf"]  = "asin";
        gPolyMathLibTable["atanf"]  = "atan";
        gPolyMathLibTable["atan2f"] = "atan2";
        gPolyMathLibTable["ceilf"]  = "ceil";
        gPolyMathLibTable["cosf"]   = "cos";
        gPolyMathLibTable["coshf"]  = "cosh";
        gPolyMathLibTable["expf"]   = "exp";
        gPolyMathLibTable["floorf"] = "floor";
        gPolyMathLibTable["fmodf"]  = "fmod";
        gPolyMathLibTable["logf"]   = "log";
        gPolyMathLibTable["log10f"] = "log10";
        gPolyMathLibTable["max_f"]  = "fmax";
        gPolyMathLibTable["min_f"]  = "fmin";
        gPolyMathLibTable["powf"]   = "pow";
        gPolyMathLibTable["remainderf"] = "remainder";
        gPolyMathLibTable["roundf"] = "round";
        gPolyMathLibTable["sinf"]   = "sin";
        gPolyMathLibTable["sinhf"]  = "sinh";
        gPolyMathLibTable["sqrtf"]  = "sqrt";
        gPolyMathLibTable["tanf"]   = "tan";
        gPolyMathLibTable["tanhf"]  = "tanh";
    
        // Hyperbolic
        gPolyMathLibTable["acoshf"]     = "acosh";
        gPolyMathLibTable["asinhf"]     = "asinh";
        gPolyMathLibTable["atanhf"]     = "atanh";
        gPolyMathLibTable["coshf"]      = "cosh";
        gPolyMathLibTable["sinhf"]      = "sinh";
        gPolyMathLibTable["tanhf"]      = "tanh";
        
        gPolyMathLibTable["isnanf"]     = "isNaN";
        gPolyMathLibTable["isinff"]     = "isInfinity";
        gPolyMathLibTable["copysignf"]  = "copysign";
   
        // Double version
        gPolyMathLibTable["fabs"]  = "fabs";
        gPolyMathLibTable["acos"]  = "acos";
        gPolyMathLibTable["asin"]  = "asin";
        gPolyMathLibTable["atan"]  = "atan";
        gPolyMathLibTable["atan2"] = "atan2";
        gPolyMathLibTable["ceil"]  = "ceil";
        gPolyMathLibTable["cos"]   = "cos";
        gPolyMathLibTable["cosh"]  = "cosh";
        gPolyMathLibTable["exp"]   = "exp";
        gPolyMathLibTable["floor"] = "floor";
        gPolyMathLibTable["fmod"]  = "fmod";
        gPolyMathLibTable["log"]   = "log";
        gPolyMathLibTable["log10"] = "log10";
        gPolyMathLibTable["max_"]  = "fmax";
        gPolyMathLibTable["min_"]  = "fmin";
        gPolyMathLibTable["pow"]   = "pow";
        gPolyMathLibTable["remainder"] = "remainder";
        gPolyMathLibTable["round"] = "round";
        gPolyMathLibTable["sin"]   = "sin";
        gPolyMathLibTable["sinh"]  = "sinh";
        gPolyMathLibTable["sqrt"]  = "sqrt";
        gPolyMathLibTable["tan"]   = "tan";
        gPolyMathLibTable["tanh"]  = "tanh";
    
        // Hyperbolic
        gPolyMathLibTable["acosh"]     = "acosh";
        gPolyMathLibTable["asinh"]     = "asinh";
        gPolyMathLibTable["atanh"]     = "atanh";
        gPolyMathLibTable["cosh"]      = "cosh";
        gPolyMathLibTable["sinh"]      = "sinh";
        gPolyMathLibTable["tanh"]      = "tanh";
        
        gPolyMathLibTable["isnan"]     = "isNaN";
        gPolyMathLibTable["isinf"]     = "isInfinity";
        gPolyMathLibTable["copysign"]  = "copysign";
    }

    virtual ~DLangInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {
        // Special case
        if (inst->fZone == "0") {
            *fOut << "uiInterface.declare(" << inst->fZone << ", " << quote(inst->fKey) << ", " << quote(inst->fValue)
                  << ")";
        } else {
            *fOut << "uiInterface.declare(&" << inst->fZone << ", " << quote(inst->fKey) << ", "
                  << quote(inst->fValue) << ")";
        }
        EndLine();
    }

    virtual void visit(OpenboxInst* inst)
    {
        string name;
        switch (inst->fOrient) {
            case OpenboxInst::kVerticalBox:
                name = "uiInterface.openVerticalBox(";
                break;
            case OpenboxInst::kHorizontalBox:
                name = "uiInterface.openHorizontalBox(";
                break;
            case OpenboxInst::kTabBox:
                name = "uiInterface.openTabBox(";
                break;
        }
        *fOut << name << quote(inst->fName) << ")";
        EndLine();
    }

    virtual void visit(CloseboxInst* inst)
    {
        *fOut << "uiInterface.closeBox();";
        tab(fTab, *fOut);
    }

    virtual void visit(AddButtonInst* inst)
    {
        if (inst->fType == AddButtonInst::kDefaultButton) {
            *fOut << "uiInterface.addButton(" << quote(inst->fLabel) << ", &" << inst->fZone << ")";
        } else {
            *fOut << "uiInterface.addCheckButton(" << quote(inst->fLabel) << ", &" << inst->fZone << ")";
        }
        EndLine();
    }

    virtual void visit(AddSliderInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                name = "uiInterface.addHorizontalSlider";
                break;
            case AddSliderInst::kVertical:
                name = "uiInterface.addVerticalSlider";
                break;
            case AddSliderInst::kNumEntry:
                name = "uiInterface.addNumEntry";
                break;
        }
        *fOut << name << "(" << quote(inst->fLabel) << ", " << "&" << inst->fZone << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fInit)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMin)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMax)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fStep)) << ")";
        EndLine();
    }

    virtual void visit(AddBargraphInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                name = "uiInterface.addHorizontalBargraph";
                break;
            case AddBargraphInst::kVertical:
                name = "uiInterface.addVerticalBargraph";
                break;
        }
        *fOut << name << "(" << quote(inst->fLabel) << ", &" << inst->fZone << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMin)) << ", "
              << cast2FAUSTFLOAT(checkReal(inst->fMax)) << ")";
        EndLine();
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        *fOut << "uiInterface.addSoundfile(" << quote(inst->fLabel) << ", " << quote(inst->fURL) << ", &"
              << inst->fSFZone << ")";
        EndLine();
    }

    virtual void visit(DeclareVarInst* inst)
    {
        if (inst->fAddress->getAccess() & Address::kConst) {
            *fOut << "const ";
        }

        if (inst->fAddress->getAccess() & Address::kStaticStruct) {
            *fOut << "__gshared ";
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
                *fOut << type << "[" << array_typed->fSize << "] " << inst->fAddress->getName();
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

        // Dont declare Math library functions, they are already defined in std.math
        if (gPolyMathLibTable.find(inst->fName) != gPolyMathLibTable.end()) {
            return;
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
        // Special case: member function `init` renamed to `initialize` so it doesnt conflict with D `.init` property.
        *fOut << fTypeManager->generateType(inst->fType->fResult, generateFunName(inst->fName == "init" ? "initialize" : inst->fName));
        generateFunDefArgs(inst);
        generateFunDefBody(inst);
    }

    virtual void generateFunDefBody(DeclareFunInst* inst)
    {
        if (inst->fCode->fCode.size() == 0) {
            *fOut << ") nothrow @nogc;" << endl;  // Pure prototype
        } else {
            // Function body
            *fOut << ") nothrow @nogc {";
            fTab++;
            tab(fTab, *fOut);
            inst->fCode->accept(this);
            fTab--;
            back(1, *fOut);
            *fOut << "}";
            tab(fTab, *fOut);
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
                *fOut << "(cast(long)(cast(ulong)";
            } else if (isInt32Type(type)) {
                *fOut << "(cast(int)(cast(uint)";
            } else {
                faustassert(false);
            }
            inst->fInst1->accept(this);
            *fOut << " >> ";
            inst->fInst2->accept(this);
            *fOut << "))";
        } else {
            TextInstVisitor::visit(inst);
        }
    }

    virtual void visit(::CastInst* inst)
    {
        *fOut << "cast(" << fTypeManager->generateType(inst->fType) << ")(";
        inst->fInst->accept(this);
        *fOut << ")";
    }

    /*
     Indexed adresses can actually be values in an array or fields in a struct type
     */
    virtual void visit(IndexedAddress* indexed)
    {
        indexed->fAddress->accept(this);
        DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
        if (struct_type) {
            Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->getIndex());
            *fOut << "." << struct_type->fType->getName(field_index->fNum);
        } else {
            *fOut << "[";
            indexed->getIndex()->accept(this);
            *fOut << "]";
        }
    }

    virtual void visit(BitcastInst* inst) { faustassert(false); }

    virtual void visit(FunCallInst* inst)
    {
        string name = gGlobal->getMathFunction(inst->fName);
        name = (gPolyMathLibTable.find(name) != gPolyMathLibTable.end()) ? gPolyMathLibTable[name] : name;
        generateFunCall(inst, name);
    }
    
    virtual void visit(FloatArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << ']';
    }

    virtual void visit(Int32ArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << inst->fNumTable[i];
            sep = ',';
        }
        *fOut << ']';
    }

    virtual void visit(DoubleArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkDouble(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << ']';
    }

    static void cleanup() { gFunctionSymbolTable.clear(); }
};

#endif
