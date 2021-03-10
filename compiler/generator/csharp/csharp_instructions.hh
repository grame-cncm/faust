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

        // Pointer to C# object is actually the object itself...
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
        gMathLibTable["ceilf"]  = "(float)Math.Ceiling";
        gMathLibTable["cosf"]   = "(float)Math.Cos";
        gMathLibTable["coshf"]  = "(float)Math.Cosh";
        gMathLibTable["expf"]   = "(float)Math.Exp";
        gMathLibTable["floorf"] = "(float)Math.Floor";
        gMathLibTable["fmodf"]  = "(float)Math.IEEERemainder";   // **** This isn't quite right - should be %
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

        gMathLibTable["remainderf"] = "(float)Math.IEEERemainder";
        gMathLibTable["rintf"]  = "(float)Math.Truncate";

        gMathLibTable["acoshf"] = "(float)Math.Acosh";
        gMathLibTable["asinhf"] = "(float)Math.Asinh";
        gMathLibTable["atanhf"] = "(float)Math.Atanh";
        gMathLibTable["coshf"]  = "(float)Math.Cosh";
        gMathLibTable["sinhf"]  = "(float)Math.Sinh";
        gMathLibTable["tanhf"]  = "(float)Math.Tanh";

        // Double version
        gMathLibTable["fabs"]  = "Math.Abs";
        gMathLibTable["acos"]  = "Math.Acos";
        gMathLibTable["asin"]  = "Math.Asin";
        gMathLibTable["atan"]  = "Math.Atan";
        gMathLibTable["atan2"] = "Math.Atan2";
        gMathLibTable["ceil"]  = "Math.Ceiling";
        gMathLibTable["cos"]   = "Math.Cos";
        gMathLibTable["cosh"]  = "Math.Cosh";
        gMathLibTable["exp"]   = "Math.Exp";
        gMathLibTable["floor"] = "Math.Floor";
        gMathLibTable["fmod"]  = "Math.IEEERemainder";  // **** This isn't quite right - should be %
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

        gMathLibTable["remainder"] = "Math.IEEERemainder";
        gMathLibTable["rint"]  = "Math.Truncate";

        gMathLibTable["acosh"] = "Math.Acosh";
        gMathLibTable["asinh"] = "Math.Asinh";
        gMathLibTable["atanh"] = "Math.Atanh";
        gMathLibTable["cosh"]  = "Math.Cosh";
        gMathLibTable["sinh"]  = "Math.Sinh";
        gMathLibTable["tanh"]  = "Math.Tanh";
    }

    virtual ~CSharpInstVisitor() {}

    string createVarAccess(string varname)
    {
        if (strcmp(ifloat(), "float") == 0) {
            return "new FaustVariableAccessor {\n"
                   "\t\t\t\tID = \"" + varname + "\",\n"
                   "\t\t\t\tSetValue = delegate(double val) { " + varname + " = (float)val; },\n" +
                   "\t\t\t\tGetValue = delegate { return " + varname + "; }\n" +
                   "\t\t\t}\n"
                   "\t\t\t";
        } else {
            return "new FaustVariableAccessor {\n"
                   "\t\t\t\tID = \"" + varname + "\",\n"
                   "\t\t\t\tSetValue = delegate(double val) { " + varname + " = val; },\n" +
                   "\t\t\t\tGetValue = delegate { return " + varname + "; }\n" +
                   "\t\t\t}\n"
                   "\t\t\t";
        }
    }

    virtual void visit(AddMetaDeclareInst* inst)
    {
        *fOut << "UIDefinition.DeclareElementMetaData(\"" << inst->fZone << "\", \"" << inst->fKey << "\", \"" << inst->fValue << "\")";
        EndLine();
    }

    virtual void visit(OpenboxInst* inst)
    {
        switch (inst->fOrient) {
            case OpenboxInst::kVerticalBox:
                *fOut << "UIDefinition.StartBox(new FaustBoxElement(EFaustUIElementType.VerticalBox, " << quote(inst->fName) << "))";
                break;
            case OpenboxInst::kHorizontalBox:
                *fOut << "UIDefinition.StartBox(new FaustBoxElement(EFaustUIElementType.HorizontalBox, " << quote(inst->fName) << "))";
                break;
            case OpenboxInst::kTabBox:
                *fOut << "UIDefinition.StartBox(new FaustBoxElement(EFaustUIElementType.TabBox, " << quote(inst->fName) << "))";
                break;
        }
        EndLine();
    }

    virtual void visit(CloseboxInst* inst)
    {
        *fOut << "UIDefinition.EndBox();";
        tab(fTab, *fOut);
    }

    virtual void visit(AddButtonInst* inst)
    {
        if (inst->fType == AddButtonInst::kDefaultButton) {
            *fOut << "UIDefinition.AddElement(new FaustUIVariableElement(EFaustUIElementType.Button, " << quote(inst->fLabel) << ", " << createVarAccess(inst->fZone) << "))";
        } else {
            *fOut << "UIDefinition.AddElement(new FaustUIVariableElement(EFaustUIElementType.CheckBox, " << quote(inst->fLabel) << ", " << createVarAccess(inst->fZone) << "))";
        }
        EndLine();
    }

    virtual void visit(AddSliderInst* inst)
    {
        string name;

        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                name = "UIDefinition.AddElement(new FaustUIWriteableFloatElement(EFaustUIElementType.HorizontalSlider, ";
                break;
            case AddSliderInst::kVertical:
                name = "UIDefinition.AddElement(new FaustUIWriteableFloatElement(EFaustUIElementType.VerticalSlider, ";
                break;
            case AddSliderInst::kNumEntry:
                name = "UIDefinition.AddElement(new FaustUIWriteableFloatElement(EFaustUIElementType.NumEntry, ";
                break;
        }
        *fOut << name << quote(inst->fLabel) << ", " << createVarAccess(inst->fZone) << ", " << checkReal(inst->fInit)
              << ", " << checkReal(inst->fMin) << ", " << checkReal(inst->fMax) << ", " << checkReal(inst->fStep)
              << "))";
        EndLine();
    }

    virtual void visit(AddBargraphInst* inst)
    {
        string name;

        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                name = "UIDefinition.AddElement(new FaustUIFloatElement(EFaustUIElementType.HorizontalBargraph, ";
                break;
            case AddBargraphInst::kVertical:
                name = "UIDefinition.AddElement(new FaustUIFloatElement(EFaustUIElementType.VerticalBargraph, ";
                break;
        }
        *fOut << name << quote(inst->fLabel) << ", " << createVarAccess(inst->fZone) << ", " << checkReal(inst->fMin)
              << ", " << checkReal(inst->fMax) << "))";
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

        // Do not declare Math library functions
        if (gMathLibTable.find(inst->fName) != gMathLibTable.end()) {
            return;
        }

        // Prototype arguments
        if (inst->fType->fAttribute & FunTyped::kInline) {
            *fOut << "[MethodImpl(MethodImplOptions.AggressiveInlining)]" << endl;
        }

        if (!(inst->fType->fAttribute & FunTyped::kLocal)) {
            *fOut << "public ";
        }

        if (inst->fType->fAttribute & FunTyped::kStatic) {
            *fOut << "static ";
        }

        // Prototype
        *fOut << fTypeManager->generateType(inst->fType->fResult, generateFunName(inst->fName));
        generateFunDefArgs(inst);
        generateFunDefBody(inst);
    }

    virtual void generateFunDefBody(DeclareFunInst* inst)
    {
        if (inst->fCode->fCode.size() == 0) {
            *fOut << ");" << endl;  // Pure prototype
        } else {
            // Function body
            *fOut << ")";
            tab(fTab, *fOut);
            *fOut << "{";
            fTab++;
            tab(fTab, *fOut);
            inst->fCode->accept(this);
            fTab--;
            back(1, *fOut);
            *fOut << "}";
            *fOut << endl;
            tab(fTab, *fOut);
        }
    }

    virtual void visit(LoadVarInst* inst)
    {
        fTypingVisitor.visit(inst);
        TextInstVisitor::visit(inst);
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        // Not implemented in C#
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
            inst->fInst1->accept(&fTypingVisitor);
            Typed::VarType type1 = fTypingVisitor.fCurType;

            inst->fInst2->accept(&fTypingVisitor);
            Typed::VarType type2 = fTypingVisitor.fCurType;

            if ((type1 == Typed::kBool) && (type2 != Typed::kBool)) {
                *fOut << "((";
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << "?1:0) ";
                inst->fInst2->accept(this);
                *fOut << ")";
            } else if ((type2 == Typed::kBool) && (type1 != Typed::kBool)) {
                *fOut << "(";
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " (";
                inst->fInst2->accept(this);
                *fOut << "?1:0))";

            } else {
                *fOut << "(";
                inst->fInst1->accept(this);
                *fOut << " ";
                *fOut << gBinOpTable[inst->fOpcode]->fName;
                *fOut << " ";
                inst->fInst2->accept(this);
                *fOut << ")";
            }

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
                    *fOut << ")?1.0f:0.0f)";
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

    static void cleanup()
    {
        gFunctionSymbolTable.clear();
        gMathLibTable.clear();
    }
};

#endif
