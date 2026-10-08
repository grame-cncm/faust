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

#ifndef _JAVA_INSTRUCTIONS_H
#define _JAVA_INSTRUCTIONS_H

#include <iostream>

#include "text_instructions.hh"
#include "typing_instructions.hh"

class JAVAInstVisitor : public TextInstVisitor {
   private:
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
     */
    static std::map<std::string, bool>        gFunctionSymbolTable;
    static std::map<std::string, std::string> gMathLibTable;

    TypingVisitor fTypingVisitor;

   public:
    using TextInstVisitor::visit;

    JAVAInstVisitor(std::ostream* out, int tab = 0) : TextInstVisitor(out, ".", ifloat(), "[]", tab)
    {
        initMathTable();

        // Pointer to JAVA object is actually the object itself...
        fTypeManager->fTypeDirectTable[Typed::kObj_ptr] = "";
    }

    void initMathTable()
    {
        if (gMathLibTable.size()) {
            return;
        }

        gMathLibTable["abs"]   = "java.lang.Math.abs";
        gMathLibTable["max_i"] = "java.lang.Math.max";
        gMathLibTable["min_i"] = "java.lang.Math.min";

        // Float version
        gMathLibTable["fabsf"]  = "(float)java.lang.Math.abs";
        gMathLibTable["acosf"]  = "(float)java.lang.Math.acos";
        gMathLibTable["asinf"]  = "(float)java.lang.Math.asin";
        gMathLibTable["atanf"]  = "(float)java.lang.Math.atan";
        gMathLibTable["atan2f"] = "(float)java.lang.Math.atan2";
        gMathLibTable["ceilf"]  = "(float)java.lang.Math.ceil";
        gMathLibTable["cosf"]   = "(float)java.lang.Math.cos";
        gMathLibTable["coshf"]  = "(float)java.lang.Math.cosh";
        gMathLibTable["expf"]   = "(float)java.lang.Math.exp";
        gMathLibTable["floorf"] = "(float)java.lang.Math.floor";
        gMathLibTable["fmodf"]  = "fmodf";  // Emitted as the Java % operator.
        gMathLibTable["logf"]   = "(float)java.lang.Math.log";
        gMathLibTable["log10f"] = "(float)java.lang.Math.log10";
        gMathLibTable["max_f"]  = "(float)java.lang.Math.max";
        gMathLibTable["min_f"]  = "(float)java.lang.Math.min";
        gMathLibTable["powf"]   = "(float)java.lang.Math.pow";
        gMathLibTable["roundf"] = "(float)faust_round";
        gMathLibTable["sinf"]   = "(float)java.lang.Math.sin";
        gMathLibTable["sinhf"]  = "(float)java.lang.Math.sinh";
        gMathLibTable["sqrtf"]  = "(float)java.lang.Math.sqrt";
        gMathLibTable["tanf"]   = "(float)java.lang.Math.tan";
        gMathLibTable["tanhf"]  = "(float)java.lang.Math.tanh";

        gMathLibTable["remainderf"] = "(float)java.lang.Math.IEEEremainder";
        gMathLibTable["rintf"]      = "(float)java.lang.Math.rint";

        gMathLibTable["copysignf"] = "java.lang.Math.copySign";
        gMathLibTable["isnanf"]    = "isnanf";
        gMathLibTable["isinff"]    = "isinff";
        gMathLibTable["acoshf"]    = "(float)faust_acosh";
        gMathLibTable["asinhf"]    = "(float)faust_asinh";
        gMathLibTable["atanhf"]    = "(float)faust_atanh";

        // Double version
        gMathLibTable["fabs"]  = "java.lang.Math.abs";
        gMathLibTable["acos"]  = "java.lang.Math.acos";
        gMathLibTable["asin"]  = "java.lang.Math.asin";
        gMathLibTable["atan"]  = "java.lang.Math.atan";
        gMathLibTable["atan2"] = "java.lang.Math.atan2";
        gMathLibTable["ceil"]  = "java.lang.Math.ceil";
        gMathLibTable["cos"]   = "java.lang.Math.cos";
        gMathLibTable["cosh"]  = "java.lang.Math.cosh";
        gMathLibTable["exp"]   = "java.lang.Math.exp";
        gMathLibTable["floor"] = "java.lang.Math.floor";
        gMathLibTable["fmod"]  = "fmod";  // Emitted as the Java % operator.
        gMathLibTable["log"]   = "java.lang.Math.log";
        gMathLibTable["log10"] = "java.lang.Math.log10";
        gMathLibTable["max_"]  = "java.lang.Math.max";
        gMathLibTable["min_"]  = "java.lang.Math.min";
        gMathLibTable["pow"]   = "java.lang.Math.pow";
        gMathLibTable["round"] = "faust_round";
        gMathLibTable["sin"]   = "java.lang.Math.sin";
        gMathLibTable["sinh"]  = "java.lang.Math.sinh";
        gMathLibTable["sqrt"]  = "java.lang.Math.sqrt";
        gMathLibTable["tan"]   = "java.lang.Math.tan";
        gMathLibTable["tanh"]  = "java.lang.Math.tanh";

        gMathLibTable["remainder"] = "java.lang.Math.IEEEremainder";
        gMathLibTable["rint"]      = "java.lang.Math.rint";
        gMathLibTable["copysign"]  = "java.lang.Math.copySign";
        gMathLibTable["isnan"]     = "isnan";
        gMathLibTable["isinf"]     = "isinf";
        gMathLibTable["acosh"]     = "faust_acosh";
        gMathLibTable["asinh"]     = "faust_asinh";
        gMathLibTable["atanh"]     = "faust_atanh";
    }

    virtual ~JAVAInstVisitor() {}

    std::string createVarAccess(const std::string& varname)
    {
        if (strcmp(ifloat(), "float") == 0) {
            return "new FaustVarAccess() {\n"
                   "\t\t\t\tpublic String getId() { return \"" +
                   varname +
                   "\"; }\n"
                   "\t\t\t\tpublic void set(float val) { " +
                   varname +
                   " = val; }\n"
                   "\t\t\t\tpublic float get() { return (float)" +
                   varname +
                   "; }\n"
                   "\t\t\t}\n"
                   "\t\t\t";
        } else {
            return "new FaustVarAccess() {\n"
                   "\t\t\t\tpublic String getId() { return \"" +
                   varname +
                   "\"; }\n"
                   "\t\t\t\tpublic void set(double val) { " +
                   varname +
                   " = val; }\n"
                   "\t\t\t\tpublic double get() { return (double)" +
                   varname +
                   "; }\n"
                   "\t\t\t}\n"
                   "\t\t\t";
        }
    }

    virtual void visit(AddMetaDeclareInst* inst)
    {
        *fOut << "ui_interface.declare(\"" << inst->fZone << "\", \"" << inst->fKey << "\", \""
              << inst->fValue << "\")";
        EndLine();
    }

    virtual void visit(OpenboxInst* inst)
    {
        std::string name;
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
        std::string name;
        if (inst->fType == AddButtonInst::kDefaultButton) {
            name = "ui_interface.addButton(";
        } else {
            name = "ui_interface.addCheckButton(";
        }
        *fOut << name << quote(inst->fLabel) << ", " << createVarAccess(inst->fZone) << ")";
        EndLine();
    }

    virtual void visit(AddSliderInst* inst)
    {
        std::string name;
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                name = "ui_interface.addHorizontalSlider(";
                break;
            case AddSliderInst::kVertical:
                name = "ui_interface.addVerticalSlider(";
                break;
            case AddSliderInst::kNumEntry:
                name = "ui_interface.addNumEntry(";
                break;
        }
        *fOut << name << quote(inst->fLabel) << ", " << createVarAccess(inst->fZone) << ", "
              << checkReal(inst->fInit) << ", " << checkReal(inst->fMin) << ", "
              << checkReal(inst->fMax) << ", " << checkReal(inst->fStep) << ")";
        EndLine();
    }

    virtual void visit(AddBargraphInst* inst)
    {
        std::string name;
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                name = "ui_interface.addHorizontalBargraph(";
                break;
            case AddBargraphInst::kVertical:
                name = "ui_interface.addVerticalBargraph(";
                break;
        }
        *fOut << name << quote(inst->fLabel) << ", " << createVarAccess(inst->fZone) << ", "
              << checkReal(inst->fMin) << ", " << checkReal(inst->fMax) << ")";
        EndLine();
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        // Not supported for now
        throw faustexception("ERROR : 'soundfile' primitive not yet supported for JAVA\n");
    }

    virtual void visit(LabelInst* inst) {}

    static Typed::VarType javaValueType(ValueInst* value)
    {
        if (Select2Inst* select = dynamic_cast<Select2Inst*>(value)) {
            Typed::VarType then_type = javaValueType(select->fThen);
            Typed::VarType else_type = javaValueType(select->fElse);
            // Mixed selects become numeric after converting their boolean arm to 0/1.
            if (then_type == Typed::kBool && else_type != Typed::kBool) {
                return else_type;
            }
            if (else_type == Typed::kBool && then_type != Typed::kBool) {
                return then_type;
            }
        }
        return TypingVisitor::getType(value);
    }

    virtual void visitCond(ValueInst* cond)
    {
        *fOut << "(";
        cond->accept(this);
        if (javaValueType(cond) != Typed::kBool) {
            *fOut << " != 0";
        }
        *fOut << ")";
    }

    // FIR comparisons can initialize numeric values, but Java booleans cannot.
    void generateNumericValue(ValueInst* value, Typed::VarType target)
    {
        if ((isIntType(target) || isRealType(target)) && javaValueType(value) == Typed::kBool) {
            *fOut << "((";
            value->accept(this);
            *fOut << ")?1:0)";
        } else {
            value->accept(this);
        }
    }

    virtual void visit(StoreVarInst* inst)
    {
        // Table-fill parameters are numeric and may not be in the global type table.
        LoadVarInst          load(inst->fAddress);
        const Typed::VarType target = gGlobal->hasVarType(inst->fAddress->getName())
                                          ? TypingVisitor::getType(&load)
                                          : Typed::kInt32;
        inst->fAddress->accept(this);
        *fOut << " = ";
        generateNumericValue(inst->fValue, target);
        EndLine();
    }

    virtual void visit(DeclareVarInst* inst)
    {
        if (inst->fAddress->isStaticStruct()) {
            *fOut << "static ";
        }

        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        if (array_typed && array_typed->fSize > 1) {
            std::string type = fTypeManager->fTypeDirectTable[array_typed->fType->getType()];
            if (inst->fValue) {
                *fOut << type << " " << inst->getName() << "[] = ";
                generateNumericValue(inst->fValue, inst->fType->getType());
            } else {
                *fOut << type << " " << inst->getName() << "[] = new " << type << "["
                      << array_typed->fSize << "]";
            }
        } else {
            *fOut << fTypeManager->generateType(inst->fType, inst->getName());
            if (inst->fValue) {
                *fOut << " = ";
                generateNumericValue(inst->fValue, inst->fType->getType());
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

        if (inst->fName == "round" || inst->fName == "roundf") {
            if (!gFunctionSymbolTable["faust_round"]) {
                gFunctionSymbolTable["faust_round"] = true;
                // Math.round uses ties toward +infinity; Faust uses ties away from zero.
                *fOut << "private static double faust_round(double value) {";
                tab(fTab + 1, *fOut);
                *fOut << "double magnitude = java.lang.Math.abs(value);";
                tab(fTab + 1, *fOut);
                *fOut << "double integral = java.lang.Math.floor(magnitude);";
                tab(fTab + 1, *fOut);
                *fOut << "return java.lang.Math.copySign(integral + "
                         "((magnitude - integral >= 0.5) ? 1.0 : 0.0), value);";
                tab(fTab, *fOut);
                *fOut << "}";
                tab(fTab, *fOut);
            }
            return;
        }

        std::string inverse;
        if (inst->fName == "asinh" || inst->fName == "asinhf") {
            inverse = "asinh";
        }
        if (inst->fName == "acosh" || inst->fName == "acoshf") {
            inverse = "acosh";
        }
        if (inst->fName == "atanh" || inst->fName == "atanhf") {
            inverse = "atanh";
        }
        if (!inverse.empty()) {
            const std::string helper = "faust_" + inverse;
            if (!gFunctionSymbolTable[helper]) {
                gFunctionSymbolTable[helper] = true;
                *fOut << "private static double " << helper << "(double value) {";
                tab(fTab + 1, *fOut);
                // log1p preserves tiny values; logarithmic limits avoid squaring overflow.
                if (inverse == "asinh") {
                    *fOut << "double magnitude = java.lang.Math.abs(value);";
                    tab(fTab + 1, *fOut);
                    *fOut << "double result = (magnitude > 1e154) ? "
                             "java.lang.Math.log(magnitude) + java.lang.Math.log(2.0) : "
                             "java.lang.Math.log1p(magnitude + magnitude * magnitude / "
                             "(1.0 + java.lang.Math.hypot(1.0, magnitude)));";
                    tab(fTab + 1, *fOut);
                    *fOut << "return java.lang.Math.copySign(result, value);";
                } else if (inverse == "acosh") {
                    *fOut
                        << "return (value > 1e154) ? "
                           "java.lang.Math.log(value) + java.lang.Math.log(2.0) : "
                           "java.lang.Math.log1p((value - 1.0) + "
                           "java.lang.Math.sqrt(value - 1.0) * java.lang.Math.sqrt(value + 1.0));";
                } else {
                    *fOut << "return 0.5 * (java.lang.Math.log1p(value) - "
                             "java.lang.Math.log1p(-value));";
                }
                tab(fTab, *fOut);
                *fOut << "}";
                tab(fTab, *fOut);
            }
            return;
        }

        // Do not declare Math library functions, they are defined in java.lang.Math and used in a
        // polymorphic way.
        if (gMathLibTable.find(inst->fName) != gMathLibTable.end()) {
            return;
        }

        // Prototype
        *fOut << fTypeManager->generateType(inst->fType->fResult, generateFunName(inst->fName));
        generateFunDefArgs(inst);
        generateFunDefBody(inst);
    }

    virtual void visit(LoadVarInst* inst)
    {
        fTypingVisitor.visit(inst);
        TextInstVisitor::visit(inst);
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        // Not implemented in JAVA
        faustassert(false);
    }

    virtual void visit(FloatNumInst* inst)
    {
        fTypingVisitor.visit(inst);
        TextInstVisitor::visit(inst);
    }

    virtual void visit(Int32NumInst* inst)
    {
        fTypingVisitor.visit(inst);
        TextInstVisitor::visit(inst);
    }

    virtual void visit(BoolNumInst* inst)
    {
        fTypingVisitor.visit(inst);
        TextInstVisitor::visit(inst);
    }

    virtual void visit(DoubleNumInst* inst)
    {
        fTypingVisitor.visit(inst);
        TextInstVisitor::visit(inst);
    }

    virtual void visit(BinopInst* inst)
    {
        *fOut << "(";
        // Java promotes numeric operands itself; Faust comparison values need 0/1.
        generateNumericValue(inst->fInst1, Typed::kInt32);
        *fOut << " " << gBinOpTable[inst->fOpcode]->fName << " ";
        generateNumericValue(inst->fInst2, Typed::kInt32);
        *fOut << ")";
        fTypingVisitor.visit(inst);
    }

    virtual void visit(::CastInst* inst)
    {
        fTypingVisitor.fCurType = javaValueType(inst->fInst);

        if (fTypeManager->generateType(inst->fType) == "int") {
            switch (fTypingVisitor.fCurType) {
                case Typed::kDouble:
                case Typed::kFloat:
                case Typed::kFloatMacro:
                    *fOut << "(int)";
                    inst->fInst->accept(this);
                    break;
                case Typed::kInt32:
                    inst->fInst->accept(this);
                    break;
                case Typed::kBool:
                    *fOut << "((";
                    inst->fInst->accept(this);
                    *fOut << ")?1:0)";
                    break;
                default:
                    std::cerr << "visitor.fCurType " << fTypingVisitor.fCurType << std::endl;
                    faustassert(false);
                    break;
            }
        } else {
            const std::string type = fTypeManager->generateType(inst->fType);
            if (fTypingVisitor.fCurType == Typed::kBool) {
                *fOut << "((";
                inst->fInst->accept(this);
                *fOut << ")?(" << type << ")1:(" << type << ")0)";
            } else {
                *fOut << "(" << type << ")(";
                inst->fInst->accept(this);
                *fOut << ")";
            }
        }
        fTypingVisitor.visit(inst);
    }

    virtual void visit(BitcastInst* inst) { faustassert(false); }

    virtual void visit(FunCallInst* inst)
    {
        if (inst->fName == "isnan" || inst->fName == "isnanf" || inst->fName == "isinf" ||
            inst->fName == "isinff") {
            *fOut << "(java.lang.Double."
                  << ((inst->fName == "isnan" || inst->fName == "isnanf") ? "isNaN" : "isInfinite")
                  << "(";
            inst->fArgs.front()->accept(this);
            *fOut << ") ? 1 : 0)";
            return;
        }
        if (inst->fName == "fmod" || inst->fName == "fmodf") {
            *fOut << "(";
            inst->fArgs.front()->accept(this);
            *fOut << " % ";
            inst->fArgs.back()->accept(this);
            *fOut << ")";
            return;
        }
        std::string fun_name = (gMathLibTable.find(inst->fName) != gMathLibTable.end())
                                   ? gMathLibTable[inst->fName]
                                   : inst->fName;
        generateFunCall(inst, fun_name);
    }

    virtual void visit(Select2Inst* inst)
    {
        const Typed::VarType target = javaValueType(inst);
        *fOut << "(";
        visitCond(inst->fCond);
        *fOut << " ? ";
        generateNumericValue(inst->fThen, target);
        *fOut << " : ";
        generateNumericValue(inst->fElse, target);
        *fOut << ")";
        fTypingVisitor.visit(inst);
    }

    static void cleanup()
    {
        gFunctionSymbolTable.clear();
        gMathLibTable.clear();
    }
};

#endif
