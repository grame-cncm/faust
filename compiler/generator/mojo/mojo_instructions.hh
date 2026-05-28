/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#ifndef MOJO_INSTRUCTIONS_HH
#define MOJO_INSTRUCTIONS_HH

// faust
#include "struct_manager.hh"
#include "text_instructions.hh"

// mojo
#include "_mojo_utils.hh"

inline namespace mojo {

using MathLibTable = std::unordered_map<String, String>;
using FuncSymTable = std::unordered_map<String, bool>;

//////////////////////////////////////////////////////////////
// Mojo visitors declaration

/**
    A `MojoInstVisitor` is a `TextInstVisitor` for the mojo backend.
    @desc
    - Produces and writes the translation from Faust IR to Mojo code using
      the visit operations.
    - An instance is created with an `output` stream, the `class name`
      of the DSP generated class and a `tab` number for indentation.
    @glob
    - Maintains a `function symbols table` to keep track of the already
      generated functions and allows to clear it as `cleanup`.
    - Maintains a `math library table` to map Faust math functions to
      Mojo standard ones.
    - Allows to generate a textual cast expression `to FaustFloat` type.
**/
class MojoInstVisitor : public TextInstVisitor {
public:
    inline MojoInstVisitor(OStream* out, String const& structName, i32 tab = 0);
    inline virtual ~MojoInstVisitor();

    using TextInstVisitor::visit;

    inline void visit(AddBargraphInst* inst)       override;
    inline void visit(AddButtonInst* inst)         override;
    inline void visit(AddMetaDeclareInst* inst)    override;
    inline void visit(AddSliderInst* inst)         override;
    inline void visit(AddSoundfileInst* inst)      override;
    inline void visit(BinopInst* inst)             override;
    inline void visit(CastInst* inst)              override;
    inline void visit(CloseboxInst* inst)          override;
    inline void visit(DeclareFunInst* inst)        override;
    inline void visit(DeclareStructTypeInst* inst) override;
    inline void visit(DeclareVarInst* inst)        override;
    inline void visit(DoubleArrayNumInst* inst)    override;
    inline void visit(DropInst* inst)              override;
    inline void visit(FloatArrayNumInst* inst)     override;
    inline void visit(ForLoopInst* inst)           override;
    inline void visit(FunCallInst* inst)           override;
    inline void visit(IfInst* inst)                override;
    inline void visit(IndexedAddress* indexed)     override;
    inline void visit(Int32NumInst* inst)          override;
    inline void visit(Int64NumInst* inst)          override;
    inline void visit(LabelInst* inst)             override;
    inline void visit(LoadVarAddressInst* inst)    override;
    inline void visit(NamedAddress* named)         override;
    inline void visit(OpenboxInst* inst)           override;
    inline void visit(Select2Inst* inst)           override;
    inline void visit(SimpleForLoopInst* inst)     override;
    inline void visit(StoreVarInst* inst)          override;

    inline static void cleanup();

protected:
    // `RetInst` helpers
    inline void visitAux(RetInst* inst, bool genEmpty) override;
    // `IfInst` helpers
    // `DeclareFunInst` helpers
    inline void writeFunDefArgs(DeclareFunInst* inst);
    inline void writeFunDefBody(DeclareFunInst* inst);
    inline void writeFunDefHeader(DeclareFunInst* inst);

    // Global operations
    inline static String gToFaustFloat(String const& str);
    inline static MathLibTable gCreateMathLibTable();
        
    // Global state
    inline static MathLibTable gMathLibTable;
    inline static FuncSymTable gFuncSymTable;
};

/**
    A `MojoInitFieldsVisitor` is a `DispatchVisitor` for the mojo backend.
    @desc
    - It is used to generate the fields initialization code in the default
      constructor `__init__(out dsp)` of the generated class.
    - Produces and writes the translation from Faust IR to Mojo code using
      the visit operations.
    - An instance is created with an `output` stream and a `tab` number
      for indentation.
    @rep
    - Maintains an `out` stream to write to.
    - Maintains a `tab` number for indentation.
    @glob
    - Allows to generate a `zero initializer` for a given `typed` value.
**/
class MojoInitFieldsVisitor : public DispatchVisitor {
public:
    using DispatchVisitor::visit;
    OStream* fOut;
    i32      fTab;

    inline MojoInitFieldsVisitor(OStream* out, i32 tab = 0);

    inline void visit(DeclareVarInst* inst)     override;
    inline void visit(NamedAddress* named)      override;
    inline void visit(Int32ArrayNumInst* inst)  override;
    inline void visit(FloatArrayNumInst* inst)  override;
    inline void visit(DoubleArrayNumInst* inst) override;

    static inline void gZeroInitializer(OStream* out, Typed* typed);
};

/**
    A `MojoVecInstVisitor` is a `MojoInstVisitor` for the mojo backend
    when the -vec flag is enabled
    @nota
    - Currently dos not add any logic to `MojoInstVisitor`.
**/
class MojoVecInstVisitor : public MojoInstVisitor {
public:
    using MojoInstVisitor::visit;

    MojoVecInstVisitor(OStream* out, String const& structName, int tab = 0);
};

//////////////////////////////////////////////////////////////
// MojoInstVisitor implementation

MojoInstVisitor::MojoInstVisitor(OStream* out, String const& structName, i32 tab)
    : TextInstVisitor(out, ".", new MojoStringTypeManager(xfloat(), structName, ""), tab)
{
    gMathLibTable = gCreateMathLibTable();
}

MojoInstVisitor::~MojoInstVisitor() {}

void MojoInstVisitor::visit(AddMetaDeclareInst* inst)
{
    String zone = (inst->fZone == "0") ? "null_val" : snakeCase(inst->fZone);
    *fOut << "ui.declare(";
    *fOut << "dsp." << zone << ", " << wlit(inst->fKey) << ", " << wlit(inst->fValue);
    *fOut << ")" << wendl(fFinishLine, fTab);
}

void MojoInstVisitor::visit(AddButtonInst* inst)
{
    String name;
    String zone = snakeCase(inst->fZone);
    if (inst->fType == AddButtonInst::kDefaultButton) {
        name = "add_button";
    } else {
        name = "add_check_button";
    }
    *fOut << "ui." << name << "(" << wlit(inst->fLabel) << ", dsp." << zone << ")";
    *fOut << wendl(fFinishLine, fTab);
}

void MojoInstVisitor::visit(AddSliderInst* inst)
{
    String name;
    switch (inst->fType) {
        case AddSliderInst::kHorizontal:
            name = "add_horizontal_slider";
            break;
        case AddSliderInst::kVertical:
            name = "add_vertical_slider";
            break;
        case AddSliderInst::kNumEntry:
            name = "add_num_entry";
            break;
    }

    *fOut << "ui." << name << "("
          << wlit(inst->fLabel) << ", "
          << "dsp." << snakeCase(inst->fZone) << ", "
          << gToFaustFloat(ensureReal(inst->fInit)) << ", "
          << gToFaustFloat(ensureReal(inst->fMin))  << ", "
          << gToFaustFloat(ensureReal(inst->fMax))  << ", "
          << gToFaustFloat(ensureReal(inst->fStep))
    << ")";
    *fOut << wendl(fFinishLine, fTab);
}

void MojoInstVisitor::visit(AddBargraphInst* inst)
{
    String name;
    switch (inst->fType) {
        case AddBargraphInst::kHorizontal:
            name = "add_horizontal_bargraph";
            break;
        case AddBargraphInst::kVertical:
            name = "add_vertical_bargraph";
            break;
    }
    *fOut << "ui." << name << "(" << wlit(inst->fLabel) << ", "
          << "dsp." << snakeCase(inst->fZone) << ", "
          << gToFaustFloat(ensureReal(inst->fMin)) << ", "
          << gToFaustFloat(ensureReal(inst->fMax)) << ")";
    *fOut << wendl(fFinishLine, fTab);
}

void MojoInstVisitor::visit(AddSoundfileInst* inst)
{
    mj_unused(inst);
    faustassert(false);
}

void MojoInstVisitor::visit(BinopInst* inst)
{
    *fOut << "(";
    inst->fInst1->accept(this);
    *fOut << ") " << gBinOpTable[inst->fOpcode]->fName << " (";
    inst->fInst2->accept(this);
    *fOut << ")";
}

void MojoInstVisitor::visit(CastInst* inst)
{
    if (inst->fType->getType() == Typed::kFloatMacro) {
        *fOut << "SIMD[dreal, 1](";
        inst->fInst->accept(this);
        goto End_Inst;
    }

    *fOut << fTypeManager->generateType(inst->fType) << "(";
    if (auto* float_inst = dycast(FloatNumInst*, inst->fInst)) {
        *fOut << ensureReal(float_inst->fNum);
        goto End_Inst;
    }
    if (auto* double_inst = dycast(DoubleNumInst*, inst->fInst)) {
        *fOut << ensureReal(double_inst->fNum);
        goto End_Inst;
    }

    inst->fInst->accept(this);
End_Inst:
    *fOut << ")";
}

void MojoInstVisitor::visit(CloseboxInst* inst)
{
    mj_unused(inst);
    *fOut << "ui.close_box()";
    *fOut << wendl(fFinishLine, fTab);
}

void MojoInstVisitor::visit(DeclareStructTypeInst* inst)
{
    StructTyped* type = inst->fType;
    *fOut << "struct " << type->fName << ":" << "\n";
    fTab += 1;
    for (NamedTyped* field : type->fFields) {
        *fOut << wtab(fTab) << fTypeManager->generateType(field, field->fName);
        *fOut << "\n";
    }
    fTab -= 1;
}

void MojoInstVisitor::visit(DeclareVarInst* inst)
{
    String name = snakeCase(inst->getName());
    *fOut << "var ";
    if (inst->fAddress->isStruct() || inst->fAddress->isStaticStruct()) {
        *fOut << fTypeManager->generateType(inst->fType, name);
        goto End_Inst;
    }
    if (!inst->fValue) {
        b32 is_arr_typed = dycast(ArrayTyped*, inst->fType) != nullptr;
        if (is_arr_typed) {
            *fOut << name << " = ";
            *fOut << fTypeManager->generateType(inst->fType);
            *fOut << "(uninitialized=True)";
            goto End_Inst;
        }
        *fOut << fTypeManager->generateType(inst->fType);
        goto End_Inst;
    }
    *fOut << name << " = ";
    if (dycast(LoadVarAddressInst*, inst->fValue)) {
        *fOut << "Ptr(to=";
        inst->fValue->accept(this);
        *fOut << ")";
        goto End_Inst;
    }
    inst->fValue->accept(this);
End_Inst:
    *fOut << wendl(fFinishLine, fTab);
}

void MojoInstVisitor::visit(DoubleArrayNumInst* inst)
{
    char sep = '[';
    for (size_t i = 0; i < inst->fNumTable.size(); i++) {
        *fOut << sep << checkDouble(inst->fNumTable[i]);
        sep = ',';
    }
    *fOut << ']';
}

void MojoInstVisitor::visit(DeclareFunInst* inst)
{
    if (gFuncSymTable.find(inst->fName) != gFuncSymTable.end()) {
        return;
    } 
    
    gFuncSymTable[inst->fName] = true;
    if (gMathLibTable.find(inst->fName) == gMathLibTable.end()) {
        writeFunDefHeader(inst);
        writeFunDefBody(inst);
        *fOut << "\n";
    }
}

void MojoInstVisitor::visit(DropInst* inst)
{
    if (inst->fResult) {
        inst->fResult->accept(this);
        *fOut << wendl(fFinishLine, fTab);
    }
}

void MojoInstVisitor::visit(FloatArrayNumInst* inst)
{
    char sep = '[';
    for (size_t i = 0; i < inst->fNumTable.size(); i++) {
        *fOut << sep << checkDouble(inst->fNumTable[i]);
        sep = ',';
    }
    *fOut << ']';
}

void MojoInstVisitor::visit(ForLoopInst* inst)
{
    if (inst->fCode->size() == 0) {
        return;
    }
    inst->fInit->accept(this);
    *fOut << "while (";
    inst->fEnd->accept(this);
    fTab += 1;
    *fOut << "): " << "\n" << wtab(fTab);
    inst->fCode->accept(this);
    inst->fIncrement->accept(this);
    fTab -= 1;
    *fOut << wrewind(fOut);
}

void MojoInstVisitor::visit(FunCallInst* inst)
{
    VString name = (gMathLibTable.find(inst->fName) != gMathLibTable.end())
                            ? gMathLibTable[inst->fName] : inst->fName;

    if (name == "pow") {
        ValueInst* inst_base = inst->fArgs.front();
        ValueInst* inst_exp = inst->fArgs.back();
        double e = 0.0;

        if (!inst_exp->isSimpleValue()) {
            goto MathLib_Call;
        }
        if (auto* float_inst = dycast(FloatNumInst*, inst_exp)) {
            e = float_inst->fNum;
        }
        if (auto* double_inst = dycast(DoubleNumInst*, inst_exp)) {
            e = double_inst->fNum;
        }
        if (e <= 0 || not isWhole(e)) {
            goto MathLib_Call;
        }

        String e_str = toStringTruncNullFraction(e);
        *fOut << "pow_unrolled[" << e_str << "](";
        inst_base->accept(this);
        goto End_Inst;
    }

MathLib_Call:
    *fOut << name << "(";
    generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
End_Inst:
    *fOut << ")";
}

void MojoInstVisitor::visit(IfInst* inst)
{
    *fOut << "if (";
    inst->fCond->accept(this);
    fTab += 1;
    *fOut << " != 0):\n" << wtab(fTab);
    inst->fThen->accept(this);
    *fOut << wrewind(fOut); 
    if (inst->fElse->fCode.size() > 0)
    {
        *fOut << "elif";
        *fOut << wtab(fTab + 1) << "\n";
        inst->fElse->accept(this);
        *fOut << wrewind(fOut);
    }
    fTab -= 1;
    *fOut << "\n" << wtab(fTab);
}

void MojoInstVisitor::visit(IndexedAddress* indexed)
{
    indexed->fAddress->accept(this);
    DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
    if (struct_type) {
        Int32NumInst* idx = dycast(Int32NumInst*, indexed->getIndex());
        faustassert(idx);
        String name = snakeCase(struct_type->fType->getName(idx->fNum));
        *fOut << "." << name;
        return;
    }  
    *fOut << "[";
    indexed->getIndex()->accept(this);
    *fOut << "]";
}

void MojoInstVisitor::visit(Int32NumInst* inst)
{
    *fOut << "S32(" << inst->fNum << ")";
}

inline void MojoInstVisitor::visit(Int64NumInst* inst)
{
    *fOut << "S64(" << inst->fNum << ")";
}

void MojoInstVisitor::visit(LabelInst* inst)
{
    mj_unused(inst);  // do not print any comment
}

void MojoInstVisitor::visit(LoadVarAddressInst* inst)
{
    inst->fAddress->accept(this);  // NOTE:(manu) value semantics (l-value ref)
}

void MojoInstVisitor::visit(NamedAddress* named)
{
    if (named->isStruct() || named->isStaticStruct()) {
        *fOut << "dsp.";
    }
    String name = snakeCase(named->fName);
    *fOut << name;
}

void MojoInstVisitor::visit(OpenboxInst* inst)
{
    String name;
    switch (inst->fOrient) {
        case OpenboxInst::kVerticalBox:
            name = "open_vertical_box";
            break;
        case OpenboxInst::kHorizontalBox:
            name = "open_horizontal_box";
            break;
        case OpenboxInst::kTabBox:
            name = "open_tab_box";
            break;
    }
    *fOut << "ui." << name << "(" << wlit(inst->fName) << ")";
    *fOut << wendl(fFinishLine, fTab);
}

inline void MojoInstVisitor::visit(Select2Inst* inst)
{
    inst->fThen->accept(this);
    *fOut << " if ";
    inst->fCond->accept(this);
    *fOut << " else ";
    inst->fElse->accept(this);
}

void MojoInstVisitor::visit(SimpleForLoopInst* inst)
{
    if (inst->fCode->size() == 0) {
        return;
    }
    *fOut << "for var " << inst->getName() << " in range(";
    Int32NumInst* lo = dycast(Int32NumInst*, inst->fLowerBound);
    Int32NumInst* up = dycast(Int32NumInst*, inst->fUpperBound);
    if (inst->fReverse) {
        faustassert(up);
        if (!lo) {
            *fOut << "S32(" <<up->fNum << "), ";
            inst->fLowerBound->accept(this);
            *fOut << " - 1, -1";
        } else {
            *fOut << "S32(" <<up->fNum << "), " << lo->fNum - 1 << ", -1";
        }
        goto Loop_Body;
    }
    faustassert(lo);
    if (!up) {
        *fOut << "S32(" << lo->fNum << "), ";
        inst->fUpperBound->accept(this);
    } else {
        *fOut << "S32(" <<lo->fNum << "), " << up->fNum;
    }
Loop_Body:
    fTab += 1;
    *fOut << "):\n" << wtab(fTab);
    inst->fCode->accept(this);
    fTab -= 1;
    *fOut << wrewind(fOut);
}

void MojoInstVisitor::visit(StoreVarInst* inst)
{
    inst->fAddress->accept(this);
    *fOut << " = ";
    // Is the lhs a field of the dsp and the rhs a cast to FaustFloat?
    if (auto* cast_inst = dycast(CastInst*, inst->fValue); cast_inst
        && (inst->fAddress->isStruct() || inst->fAddress->isStaticStruct())
        && (cast_inst->fType->getType() == Typed::VarType::kFloatMacro))
    {
        *fOut << "FaustFloat(";
        cast_inst->fInst->accept(this);
        *fOut << ")" << wendl(fFinishLine, fTab);
        return;
    }
    inst->fValue->accept(this);
    *fOut << wendl(fFinishLine, fTab);
}

void MojoInstVisitor::visitAux(RetInst* inst, bool genEmpty)
{

    if (inst->fResult) {
        *fOut << "return ";
        inst->fResult->accept(this);
        *fOut << wendl(fFinishLine, fTab - 1);
    } else if (genEmpty) {
        *fOut << "return";
        *fOut << wendl(fFinishLine, fTab - 1);
    }
}

void MojoInstVisitor::writeFunDefArgs(DeclareFunInst* inst)
{   
    usize size = inst->fType->fArgsTypes.size();
    usize i = 0;
    for (auto const& arg : inst->fType->fArgsTypes) {
        *fOut << fTypeManager->generateType(arg);
        if (i < size - 1) {
            *fOut << ", ";
            i += 1;
        }
    }
}

void MojoInstVisitor::writeFunDefHeader(DeclareFunInst* inst) {
    *fOut << "@always_inline" << "\n";
    *fOut << wtab(fTab) << "def " << inst->fName << "(";
    fTab += 1;
    writeFunDefArgs(inst);
    *fOut << ") -> " << fTypeManager->generateType(inst->fType->fResult) << ": "
          << "\n" << wtab(fTab);
}

void MojoInstVisitor::writeFunDefBody(DeclareFunInst* inst)
{
    if (inst->fCode->fCode.size() == 0) {
        *fOut << wtab(fTab) << "pass" << "\n";
    } else {
        inst->fCode->accept(this);
    }
    fTab -= 1;
}

//////////////////////////////////////////////////////////////
// MojoInitFieldsVisitor implementation

MojoInitFieldsVisitor::MojoInitFieldsVisitor(OStream* out, i32 tab)
    : fOut(out), fTab(tab)
{}

void MojoInitFieldsVisitor::visit(DeclareVarInst* inst)
{
    *fOut << wtab(fTab);
    inst->fAddress->accept(this);
    *fOut << " = ";
    if (inst->fValue) {
        inst->fValue->accept(this);
        *fOut << "\n";
    } else {
        gZeroInitializer(fOut, inst->fType);
    }
}

void MojoInitFieldsVisitor::visit(NamedAddress* named)
{
    if (named->isStruct() || named->isStaticStruct()) {
        *fOut << "dsp.";
    }
    *fOut << snakeCase(named->fName);
}

void MojoInitFieldsVisitor::visit(Int32ArrayNumInst* inst)
{
    char sep = '[';
    for (size_t i = 0; i < inst->fNumTable.size(); i++) {
        *fOut << sep << "S32(" << inst->fNumTable[i] << ")";
        sep = ',';
    }
    *fOut << ']';
}

void MojoInitFieldsVisitor::visit(FloatArrayNumInst* inst)
{
    char sep = '[';
    for (size_t i = 0; i < inst->fNumTable.size(); i++) {
        *fOut << sep << checkFloat(inst->fNumTable[i]);
        sep = ',';
    }
    *fOut << ']';
}

void MojoInitFieldsVisitor::visit(DoubleArrayNumInst* inst)
{
    char sep = '[';
    for (size_t i = 0; i < inst->fNumTable.size(); i++) {
        *fOut << sep << checkDouble(inst->fNumTable[i]);
        sep = ',';
    }
    *fOut << ']';
}

void MojoInitFieldsVisitor::gZeroInitializer(OStream* out, Typed* typed) {
    ArrayTyped* array_type = dycast(ArrayTyped*, typed);
    Typed::VarType type = typed->getType();
    switch (type) {
    case Typed::kInt32_ptr:
        *out << "Arr[S32, " << array_type->fSize << "](fill=0)";
        break;
    case Typed::kInt64_ptr:
        *out << "Arr[S64, " << array_type->fSize << "](fill=0)";
        break;
    case Typed::kFloat_ptr:
        *out << "Arr[F32, " << array_type->fSize << "](fill=0.0)";
        break;
    case Typed::kDouble_ptr:
        *out << "Arr[F64, " << array_type->fSize << "](fill=0.0)";
        break;
    case Typed::kFloatMacro_ptr:
        *out << "Arr[FaustFloat, " << array_type->fSize << "](fill=0.0)";
        break;
    case Typed::kInt32:
        *out << "0";
        break;
    case Typed::kInt64:
        *out << "0";
        break;
    case Typed::kFloat:
        *out << "0.0";
        break;
    case Typed::kDouble:
        *out << "0.0";
        break;
    case Typed::kFloatMacro:
        *out << "0.0";
        break;
    default:
        *out << "Panic - MojoInitFieldsVisitor::gZeroInitializer(...) - `typed` has "
                "unexpected `VarType` " << Typed::gTypeString[type] << "\n";
        faustassert(0);
    }
    *out << "\n";
}

//////////////////////////////////////////////////////////////
// MojoVecInstVisitor implementation

inline MojoVecInstVisitor::MojoVecInstVisitor(
    OStream* out, const String& structName, int tab
)
    : MojoInstVisitor(out, structName, tab)
{}

String MojoInstVisitor::gToFaustFloat(String const& str)
{
    return "FaustFloat(" + str + ")";
}

void MojoInstVisitor::cleanup()
{
    gFuncSymTable.clear();
}

MathLibTable MojoInstVisitor::gCreateMathLibTable()
{
    return MathLibTable{
        { "abs",        "abs"       },
        { "fabs",       "abs"       },
        { "fabsf",      "abs"       },

        { "min_i",      "min"       },
        { "min_f",      "min"       },
        { "min_",       "min"       },
        { "max_i",      "max"       },
        { "max_f",      "max"       },
        { "max_",       "max"       },
        { "minmax",     "NIL"       },

        { "cos",        "cos"       },
        { "cosf",       "cos"       },
        { "acos",       "acos"      },
        { "acosf",      "acos"      },
        { "cosh",       "cosh"      },
        { "coshf",      "cosh"      },
        { "acosh",      "acosh"     },
        { "acoshf",     "acosh"     },

        { "sin",        "sin"       },
        { "sinf",       "sin"       },
        { "asin",       "asin"      },
        { "asinf",      "asin"      },
        { "sinh",       "sinh"      },
        { "sinhf",      "sinh"      },
        { "asinh",      "asinh"     },
        { "asinhf",     "asinh"     },

        { "tan",        "tan"       },
        { "tanf",       "tan"       },
        { "atan",       "atan"      },
        { "atanf",      "atan"      },
        { "atan2",      "atan2"     },
        { "atan2f",     "atan2"     },
        { "tanh",       "tanh"      },
        { "tanhf",      "tanh"      },
        { "atanh",      "atanh"     },
        { "atanhf",     "atanh"     },

        { "exp",        "exp"       },
        { "expf",       "exp"       },
        { "log",        "log"       },
        { "logf",       "log"       },
        { "log10",      "log10"     },
        { "log10f",     "log10"     },
        { "pow",        "pow"       },
        { "powf",       "pow"       },

        { "sqrt",       "sqrt"      },
        { "sqrtf",      "sqrt"      },
        { "cbrt",       "cbrt"      },
        { "cbrtf",      "cbrt"      },

        { "ceil",       "ceil"      },
        { "ceilf",      "ceil"      },
        { "floor",      "floor"     },
        { "floorf",     "floor"     },
        { "round",      "round"     },
        { "roundf",     "round"     },
        { "rint",       "rint"       },
        { "rintf",      "rint"       },

        { "fmod",       "mod"    },
        { "fmodf",      "mod"    },
        { "remainder",  "remainder" },
        { "remainderf", "remainder" },

        { "erf",        "erf"       },
        { "erff",       "erf"       },
        { "erfc",       "erfc"      },
        { "erfcf",      "erfc"      },

        { "copysign",   "copysign"  },
        { "copysignf",  "copysign"  },

        { "isnan",      "isnan"     },
        { "isnanf",     "isnan"     },
        { "isinf",      "isinf"     },
        { "isinff",     "isinf"     },
        { "isfinite",   "isfinite"  },
        { "isfinitef",  "isfinite"  },
    };
}

}       // namespace mojo
#endif  // MOJO_INSTRUCTIONS_HH
