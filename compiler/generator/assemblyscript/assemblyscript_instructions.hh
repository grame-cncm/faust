/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

#ifndef _ASSEMBLYSCRIPT_INSTRUCTIONS_H
#define _ASSEMBLYSCRIPT_INSTRUCTIONS_H

#include <set>
#include <string>

#include "struct_manager.hh"
#include "text_instructions.hh"

// Visitor used to initialize array fields into the DSP structure
struct AssemblyScriptInitFieldsVisitor : public DispatchVisitor {
    std::ostream* fOut;
    int           fTab;

    AssemblyScriptInitFieldsVisitor(std::ostream* out, int tab = 0) : fOut(out), fTab(tab) {}

    virtual void visit(DeclareVarInst* inst)
    {
        ArrayTyped* array_type = dynamic_cast<ArrayTyped*>(inst->fType);
        if (array_type) {
            tab(fTab, *fOut);
            inst->fAddress->accept(this);
            *fOut << " = ";
            if (inst->fValue) {
                inst->fValue->accept(this);
            } else {
                ZeroInitializer(fOut, inst->fType);
            }
        }
    }

    // Field zero-init is handled by the backend through explicit initializers and generated init
    // methods; keep this visitor hook as a no-op for now.
    static void ZeroInitializer(std::ostream* fOut, Typed* typed) {}
};

/*
    A subclass of TextInstVisitor that implements a lot of generic behaviors.
    Some methods mays have to be redefined in this class, and the exposed list
    of them is given as an example, to be adapted in the real use case.
*/

class AssemblyScriptInstVisitor : public TextInstVisitor {
   private:
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
     */
    static std::map<std::string, bool> gFunctionSymbolTable;
    // Maps FIR/stdlib names to AssemblyScript intrinsics or Math/Mathf helpers.
    // This keeps emission local and avoids sprinkling backend-specific function names.
    static std::map<std::string, std::string> gMathLibTable;
    // True while emitting inside a class declaration (fields + methods). Used to avoid
    // emitting top-level qualifiers such as `export function` for class methods.
    bool fInClassScope;
    // True only while emitting the class field section. Needed in addition to
    // fInClassScope because variable declarations are emitted differently in fields
    // (typed members, optional static) versus method/function bodies (`let ...` locals).
    bool                  fInClassFields;
    std::string           fStructName;
    std::set<std::string> fStaticFieldNames;

    std::string mapMathFunction(const std::string& name) const
    {
        auto it = gMathLibTable.find(name);
        return (it != gMathLibTable.end()) ? it->second : name;
    }

   public:
    using TextInstVisitor::visit;

    AssemblyScriptInstVisitor(std::ostream* out, const std::string& struct_name, int tab = 0)
        : TextInstVisitor(out, ".", new AssemblyScriptStringTypeManager(xfloat(), "", struct_name),
                          tab),
          fInClassScope(false),
          fInClassFields(false),
          fStructName(struct_name)
    {
        if (gMathLibTable.empty()) {
            gMathLibTable["abs"]        = "Math.abs";
            gMathLibTable["max_i"]      = "max<i32>";
            gMathLibTable["min_i"]      = "min<i32>";
            gMathLibTable["fabsf"]      = "Mathf.abs";
            gMathLibTable["acosf"]      = "Mathf.acos";
            gMathLibTable["asinf"]      = "Mathf.asin";
            gMathLibTable["atanf"]      = "Mathf.atan";
            gMathLibTable["atan2f"]     = "Mathf.atan2";
            gMathLibTable["ceilf"]      = "Mathf.ceil";
            gMathLibTable["cosf"]       = "Mathf.cos";
            gMathLibTable["expf"]       = "Mathf.exp";
            gMathLibTable["floorf"]     = "Mathf.floor";
            gMathLibTable["logf"]       = "Mathf.log";
            gMathLibTable["log10f"]     = "Mathf.log10";
            gMathLibTable["max_f"]      = "max<f32>";
            gMathLibTable["min_f"]      = "min<f32>";
            gMathLibTable["powf"]       = "Mathf.pow";
            gMathLibTable["roundf"]     = "Mathf.round";
            gMathLibTable["sinf"]       = "Mathf.sin";
            gMathLibTable["sqrtf"]      = "Mathf.sqrt";
            gMathLibTable["tanf"]       = "Mathf.tan";
            gMathLibTable["acoshf"]     = "Mathf.acosh";
            gMathLibTable["asinhf"]     = "Mathf.asinh";
            gMathLibTable["atanhf"]     = "Mathf.atanh";
            gMathLibTable["coshf"]      = "Mathf.cosh";
            gMathLibTable["sinhf"]      = "Mathf.sinh";
            gMathLibTable["tanhf"]      = "Mathf.tanh";
            gMathLibTable["fmodf"]      = "%";
            gMathLibTable["remainderf"] = "Mathf.rem";
            gMathLibTable["rintf"]      = "Mathf.round";
            gMathLibTable["fabs"]       = "Math.abs";
            gMathLibTable["acos"]       = "Math.acos";
            gMathLibTable["asin"]       = "Math.asin";
            gMathLibTable["atan"]       = "Math.atan";
            gMathLibTable["atan2"]      = "Math.atan2";
            gMathLibTable["ceil"]       = "Math.ceil";
            gMathLibTable["cos"]        = "Math.cos";
            gMathLibTable["exp"]        = "Math.exp";
            gMathLibTable["floor"]      = "Math.floor";
            gMathLibTable["log"]        = "Math.log";
            gMathLibTable["log10"]      = "Math.log10";
            gMathLibTable["max_"]       = "max<f64>";
            gMathLibTable["min_"]       = "min<f64>";
            gMathLibTable["pow"]        = "Math.pow";
            gMathLibTable["round"]      = "Math.round";
            gMathLibTable["sin"]        = "Math.sin";
            gMathLibTable["sqrt"]       = "Math.sqrt";
            gMathLibTable["tan"]        = "Math.tan";
            gMathLibTable["acosh"]      = "Math.acosh";
            gMathLibTable["asinh"]      = "Math.asinh";
            gMathLibTable["atanh"]      = "Math.atanh";
            gMathLibTable["cosh"]       = "Math.cosh";
            gMathLibTable["sinh"]       = "Math.sinh";
            gMathLibTable["tanh"]       = "Math.tanh";
            gMathLibTable["fmod"]       = "%";
            gMathLibTable["remainder"]  = "Math.rem";
            gMathLibTable["rint"]       = "Math.round";
        }
    }

    virtual ~AssemblyScriptInstVisitor() {}

    void SetInClassScope(bool in_class_scope) { fInClassScope = in_class_scope; }

    void SetInClassFields(bool in_class_fields) { fInClassFields = in_class_fields; }

    virtual void visit(AddMetaDeclareInst* inst) { *fOut << "// metadata " << inst->fKey; }

    virtual void visit(OpenboxInst* inst) { *fOut << "// ui openbox " << quote(inst->fName); }

    virtual void visit(CloseboxInst* inst) { *fOut << "// ui closebox"; }

    virtual void visit(AddButtonInst* inst) { *fOut << "// ui button " << quote(inst->fLabel); }

    virtual void visit(AddSliderInst* inst) { *fOut << "// ui slider " << quote(inst->fLabel); }

    virtual void visit(AddBargraphInst* inst) { *fOut << "// ui bargraph " << quote(inst->fLabel); }

    virtual void visit(AddSoundfileInst* inst)
    {
        *fOut << "// ui soundfile unsupported in AssemblyScript backend";
    }

    virtual void visit(Int32NumInst* inst)
    {
        *fOut << "<i32>(";
        *fOut << inst->fNum;
        *fOut << ")";
    }

    virtual void visit(Int32ArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << "<i32>(" << inst->fNumTable[i] << ")";
            sep = ',';
        }
        *fOut << ']';
    }

    virtual void visit(Int64NumInst* inst)
    {
        *fOut << "<i64>(";
        *fOut << inst->fNum;
        *fOut << ")";
    }

    virtual void visit(FloatNumInst* inst)
    {
        *fOut << "<f32>(";
        *fOut << checkFloat(inst->fNum);
        *fOut << ")";
    }

    virtual void visit(FloatArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << "<f32>(" << checkFloat(inst->fNumTable[i]) << ")";
            sep = ',';
        }
        *fOut << ']';
    }

    virtual void visit(DoubleNumInst* inst)
    {
        *fOut << "<f64>(";
        *fOut << checkDouble(inst->fNum);
        *fOut << ")";
    }

    virtual void visit(DoubleArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << "<f64>(" << checkDouble(inst->fNumTable[i]) << ")";
            sep = ',';
        }
        *fOut << ']';
    }

    virtual void visit(FixedPointNumInst* inst) { TextInstVisitor::visit(inst); }

    virtual void visit(FixedPointArrayNumInst* inst)
    {
        char sep = '[';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << ']';
    }

    void emitBinopOperand(ValueInst* inst)
    {
        if (isBoolType(TypingVisitor::getType(inst))) {
            *fOut << "<i32>(";
            inst->accept(this);
            *fOut << ")";
        } else {
            inst->accept(this);
        }
    }

    virtual void visit(BinopInst* inst)
    {
        if (!isBoolOpcode(inst->fOpcode)) {
            *fOut << "(";
            emitBinopOperand(inst->fInst1);
            *fOut << " " << gBinOpTable[inst->fOpcode]->fName << " ";
            emitBinopOperand(inst->fInst2);
            *fOut << ")";
        } else {
            TextInstVisitor::visit(inst);
        }
    }

    virtual void visit(DeclareVarInst* inst)
    {
        // Variable emission depends on phase:
        // - class field section: member declarations (optionally static)
        // - inside methods/functions: local `let` declarations
        if (fInClassFields) {
            if (inst->fAddress->isStaticStruct()) {
                fStaticFieldNames.insert(inst->getName());
                *fOut << "static ";
            }
            *fOut << fTypeManager->generateType(inst->fType, inst->getName(), true);
            if (inst->fValue) {
                *fOut << " = ";
                inst->fValue->accept(this);
            } else {
                ArrayTyped* array_type = dynamic_cast<ArrayTyped*>(inst->fType);
                if (array_type && array_type->fSize > 0) {
                    *fOut << " = new StaticArray<" << fTypeManager->generateType(array_type->fType)
                          << ">(" << array_type->fSize << ")";
                }
            }
        } else {
            *fOut << "let " << fTypeManager->generateType(inst->fType, inst->getName());
            if (inst->fValue) {
                *fOut << " = ";
                inst->fValue->accept(this);
            }
        }
        EndLine();
    }

    virtual void visit(DropInst* inst) { TextInstVisitor::visit(inst); }

    virtual void visit(DeclareFunInst* inst)
    {
        if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
            return;
        }
        gFunctionSymbolTable[inst->fName] = true;

        if (gMathLibTable.find(inst->fName) != gMathLibTable.end()) {
            return;
        }

        // AssemblyScript does not support C-style function prototypes; skip declaration-only
        // entries and rely on direct operator/mapped-call handling at call sites.
        if (inst->fCode->fCode.size() == 0) {
            return;
        }

        // Top-level helpers are exported; class methods are never prefixed with `export function`.
        if (!fInClassScope && !(inst->fType->fAttribute & FunTyped::kLocal)) {
            *fOut << "export ";
        }

        if (!fInClassScope) {
            *fOut << "function ";
        }
        *fOut << inst->fName << "(";
        if (inst->fType->fArgsTypes.size() > 0) {
            size_t i = 0;
            for (const auto& arg : inst->fType->fArgsTypes) {
                *fOut << fTypeManager->generateType(arg, arg->fName);
                if (i++ < (inst->fType->fArgsTypes.size() - 1)) {
                    *fOut << ", ";
                }
            }
        }
        *fOut << ")";
        if (inst->fType->fResult) {
            *fOut << ": " << fTypeManager->generateType(inst->fType->fResult);
        }
        generateFunDefBody(inst);
    }

    virtual void generateFunDefBody(DeclareFunInst* inst)
    {
        *fOut << " {";
        tab(fTab + 1, *fOut);
        inst->fCode->accept(this);
        tab(fTab, *fOut);
        *fOut << "}";
        tab(fTab, *fOut);
    }

    virtual void visit(NamedAddress* named)
    {
        // In AssemblyScript, instance state is addressed as `this.<name>`.
        // Static struct fields are emitted as `<ClassName>.<name>`.
        if (named->getAccess() & Address::kStruct) {
            *fOut << "this.";
        } else if (named->getAccess() & Address::kStaticStruct) {
            if (fStaticFieldNames.find(named->fName) != fStaticFieldNames.end()) {
                *fOut << fStructName << ".";
            }
        }
        *fOut << named->fName;
    }

    /*
    Indexed address can actually be values in an array or fields in a struct type
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

    virtual void visit(::CastInst* inst)
    {
        *fOut << "<" << fTypeManager->generateType(inst->fType) << ">(";
        inst->fInst->accept(this);
        *fOut << ")";
    }

    virtual void visit(BitcastInst* inst)
    {
        *fOut << "<" << fTypeManager->generateType(inst->fType) << ">(";
        inst->fInst->accept(this);
        *fOut << ")";
    }

    virtual void visitCond(ValueInst* cond)
    {
        *fOut << "(";
        cond->accept(this);
        *fOut << ")";
    }

    // Generate standard funcall (not 'method' like funcall...)
    virtual void visit(FunCallInst* inst)
    {
        // `%` lowering is required because AssemblyScript's direct fmod symbol handling differs
        // from C/C++-style helper function semantics.
        if (inst->fName == "fmodf" || inst->fName == "fmod") {
            IB::genRem(inst->fArgs.front(), inst->fArgs.back())->accept(this);
            return;
        }
        *fOut << mapMathFunction(inst->fName) << "(";
        size_t i = 0;
        for (const auto& arg : inst->fArgs) {
            arg->accept(this);
            if (i++ < (inst->fArgs.size() - 1)) {
                *fOut << ", ";
            }
        }
        *fOut << ")";
    }

    virtual void visit(IfInst* inst) { TextInstVisitor::visit(inst); }

    virtual void visit(ForLoopInst* inst) { TextInstVisitor::visit(inst); }

    virtual void visit(SimpleForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) {
            return;
        }

        *fOut << "for (let " << inst->getName() << ": i32 = ";
        if (inst->fReverse) {
            inst->fUpperBound->accept(this);
            *fOut << "; " << inst->getName() << " >= ";
            inst->fLowerBound->accept(this);
            *fOut << "; " << inst->getName() << " = " << inst->getName() << " - 1) {";
        } else {
            inst->fLowerBound->accept(this);
            *fOut << "; " << inst->getName() << " < ";
            inst->fUpperBound->accept(this);
            *fOut << "; " << inst->getName() << " = " << inst->getName() << " + 1) {";
        }
        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        fTab--;
        back(1, *fOut);
        *fOut << "}";
        tab(fTab, *fOut);
    }

    static void cleanup()
    {
        gFunctionSymbolTable.clear();
        gMathLibTable.clear();
    }
};

#endif
