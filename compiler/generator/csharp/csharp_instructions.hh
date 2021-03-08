/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    Modified to C# from Java by Mike Oliphant
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

#ifndef _CSHARP_INSTRUCTIONS_H
#define _CSHARP_INSTRUCTIONS_H

using namespace std;

#include "text_instructions.hh"
#include "typing_instructions.hh"

class CSharpInstVisitor : public TextInstVisitor {
   private:
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
     */
    static map<string, bool>   gFunctionSymbolTable;
    static map<string, string> gMathLibTable;

    TypingVisitor fTypingVisitor;

   public:
    using TextInstVisitor::visit;

    CSharpInstVisitor(std::ostream* out, int tab = 0) : TextInstVisitor(out, ".", ifloat(), "[]", tab)
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

        gMathLibTable["abs"]   = "Math.Abs";
        gMathLibTable["max_i"] = "Math.Max";
        gMathLibTable["min_i"] = "Math.Min";

        // Float version
        gMathLibTable["fabsf"]  = "(float)Math.Abs";
        gMathLibTable["acosf"]  = "(float)Math.Acos";
        gMathLibTable["asinf"]  = "(float)Math.Asin";
        gMathLibTable["atanf"]  = "(float)Math.Atan";
        gMathLibTable["atan2f"] = "(float)Math.Atan2";
        gMathLibTable["ceilf"]  = "(float)Math.Ceil";
        gMathLibTable["cosf"]   = "(float)Math.Cos";
        gMathLibTable["coshf"]  = "(float)Math.Cosh";
        gMathLibTable["expf"]   = "(float)Math.Exp";
        gMathLibTable["floorf"] = "(float)Math.Floor";
        gMathLibTable["fmodf"]  = "(float)Math.IEEEremainder";
        gMathLibTable["logf"]   = "(float)Math.Log";
        gMathLibTable["log10f"] = "(float)Math.Log10";
        gMathLibTable["max_f"]  = "(float)Math.Max";
        gMathLibTable["min_f"]  = "(float)Math.Min";
        gMathLibTable["powf"]   = "(float)Math.Pow";
        gMathLibTable["roundf"] = "(float)Math.Round";
        gMathLibTable["sinf"]   = "(float)Math.Sin";
        gMathLibTable["sinhf"]  = "(float)Math.Sinh";
        gMathLibTable["sqrtf"]  = "(float)Math.Sqrt";
        gMathLibTable["tanf"]   = "(float)Math.Tan";
        gMathLibTable["tanhf"]  = "(float)Math.Tanh";

        // Double version
        gMathLibTable["fabs"]  = "Math.Abs";
        gMathLibTable["acos"]  = "Math.Acos";
        gMathLibTable["asin"]  = "Math.Asin";
        gMathLibTable["atan"]  = "Math.Atan";
        gMathLibTable["atan2"] = "Math.Atan2";
        gMathLibTable["ceil"]  = "Math.Ceil";
        gMathLibTable["cos"]   = "Math.Cos";
        gMathLibTable["cosh"]  = "Math.Cosh";
        gMathLibTable["exp"]   = "Math.Exp";
        gMathLibTable["floor"] = "Math.Floor";
        gMathLibTable["fmod"]  = "Math.IEEEremainder";
        gMathLibTable["log"]   = "Math.Log";
        gMathLibTable["log10"] = "Math.Log10";
        gMathLibTable["max_"]  = "Math.Max";
        gMathLibTable["min_"]  = "Math.Min";
        gMathLibTable["pow"]   = "Math.Pow";
        gMathLibTable["round"] = "Math.Round";
        gMathLibTable["sin"]   = "Math.Sin";
        gMathLibTable["sinh"]  = "Math.Sinh";
        gMathLibTable["sqrt"]  = "Math.Sqrt";
        gMathLibTable["tan"]   = "Math.Tan";
        gMathLibTable["tanh"]  = "Math.Tanh";
    }

    virtual ~CSharpInstVisitor() {}

    string createVarAccess(string varname)
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
                   "\t\t\t\tpublic float get() { return (double)" +
                   varname +
                   "; }\n"
                   "\t\t\t}\n"
                   "\t\t\t";
        }
    }

    virtual void visit(AddMetaDeclareInst* inst)
    {
        *fOut << "ui_interface.declare(\"" << inst->fZone << "\", \"" << inst->fKey << "\", \"" << inst->fValue
              << "\")";
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
        string name;
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
        string name;
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
        *fOut << name << quote(inst->fLabel) << ", " << createVarAccess(inst->fZone) << ", " << checkReal(inst->fInit)
              << ", " << checkReal(inst->fMin) << ", " << checkReal(inst->fMax) << ", " << checkReal(inst->fStep)
              << ")";
        EndLine();
    }

    virtual void visit(AddBargraphInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                name = "ui_interface.addHorizontalBargraph(";
                break;
            case AddBargraphInst::kVertical:
                name = "ui_interface.addVerticalBargraph(";
                break;
        }
        *fOut << name << quote(inst->fLabel) << ", " << createVarAccess(inst->fZone) << ", " << checkReal(inst->fMin)
              << ", " << checkReal(inst->fMax) << ")";
        EndLine();
    }

    virtual void visit(LabelInst* inst) {}

    virtual void visit(DeclareVarInst* inst)
    {
        if (inst->fAddress->getAccess() & Address::kStaticStruct) {
            *fOut << "static ";
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

        // Do not declare Math library functions, they are defined in java.lang.Math and used in a polymorphic way.
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
        if (isBoolOpcode(inst->fOpcode)) {
            *fOut << "(";
            inst->fInst1->accept(this);
            *fOut << " ";
            *fOut << gBinOpTable[inst->fOpcode]->fName;
            *fOut << " ";
            inst->fInst2->accept(this);
            *fOut << ")";
        } else {
            inst->fInst1->accept(&fTypingVisitor);
            Typed::VarType type1 = fTypingVisitor.fCurType;

            inst->fInst2->accept(&fTypingVisitor);
            Typed::VarType type2 = fTypingVisitor.fCurType;

            *fOut << "(";

            if (type1 == Typed::kInt32 && type2 == Typed::kInt32) {
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
            } else if (type1 == Typed::kInt32 && type2 == Typed::kFloat) {
                *fOut << "(float)";
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
            } else if (type1 == Typed::kFloat && type2 == Typed::kInt32) {
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                *fOut << "(float)";
                inst->fInst2->accept(this);
            } else if (type1 == Typed::kFloat && type2 == Typed::kFloat) {
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
            } else if (type1 == Typed::kInt32 && type2 == Typed::kBool) {
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                *fOut << "((";
                inst->fInst2->accept(this);
                *fOut << ")?1:0)";
            } else if (type1 == Typed::kBool && type2 == Typed::kInt32) {
                *fOut << "((";
                inst->fInst1->accept(this);
                *fOut << ")?1:0)";
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
            } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                *fOut << "((";
                inst->fInst1->accept(this);
                *fOut << ")?1:0)";
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                *fOut << "((";
                inst->fInst2->accept(this);
                *fOut << ")?1:0)";
            } else if (type1 == Typed::kFloat && type2 == Typed::kBool) {
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                *fOut << "((";
                inst->fInst2->accept(this);
                *fOut << ")?1.f:0.f)";
            } else if (type1 == Typed::kBool && type2 == Typed::kFloat) {
                *fOut << "((";
                inst->fInst1->accept(this);
                *fOut << ")?1.f:0.f)";
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
            } else {  // Default
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
            }

            *fOut << ")";
        }

        fTypingVisitor.visit(inst);
    }

    virtual void visit(::CastInst* inst)
    {
        inst->fInst->accept(&fTypingVisitor);

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
                    printf("visitor.fCurType %d\n", fTypingVisitor.fCurType);
                    faustassert(false);
                    break;
            }
        } else {
            switch (fTypingVisitor.fCurType) {
                case Typed::kDouble:
                case Typed::kInt32:
                    *fOut << "(float)";
                    inst->fInst->accept(this);
                    break;
                case Typed::kFloat:
                case Typed::kFloatMacro:
                    inst->fInst->accept(this);
                    break;
                case Typed::kBool:
                    *fOut << "((";
                    inst->fInst->accept(this);
                    *fOut << ")?1.f:0.f)";
                    break;
                default:
                    printf("visitor.fCurType %d\n", fTypingVisitor.fCurType);
                    faustassert(false);
                    break;
            }
        }
        fTypingVisitor.visit(inst);
    }

    virtual void visit(BitcastInst* inst) { faustassert(false); }

    virtual void visit(FunCallInst* inst)
    {
        string fun_name =
            (gMathLibTable.find(inst->fName) != gMathLibTable.end()) ? gMathLibTable[inst->fName] : inst->fName;
        generateFunCall(inst, fun_name);
    }

    virtual void visit(Select2Inst* inst)
    {
        inst->fCond->accept(&fTypingVisitor);

        switch (fTypingVisitor.fCurType) {
            case Typed::kDouble:
            case Typed::kInt32:
                *fOut << "(((";
                inst->fCond->accept(this);
                *fOut << "==0)?true:false)";
                break;
            case Typed::kFloat:
            case Typed::kFloatMacro:
                *fOut << "(((";
                inst->fCond->accept(this);
                *fOut << "==0.f)?true:false)";
                break;
            case Typed::kBool:
                *fOut << "((";
                inst->fCond->accept(this);
                *fOut << ")";
                break;
            default:
                faustassert(false);
                break;
        }

        *fOut << "?";
        inst->fThen->accept(this);
        *fOut << ":";
        inst->fElse->accept(this);
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
