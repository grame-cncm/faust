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

/** @file compiler/generator/mojo/mojo_instructions.cpp */

#ifndef MOJO_INSTRUCTIONS_HH
#define MOJO_INSTRUCTIONS_HH

// faust
#include <memory_resource>
#include "mojo/_mojo_hal.hh"
#include "struct_manager.hh"
#include "text_instructions.hh"

// mojo
#include "_mojo_utils.hh"

inline namespace mojo {

using MathLibTable = std::unordered_map<String, String>;
using FuncSymTable = std::unordered_map<String, bool>;

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
    MojoInstVisitor(OStream* out, String const& structName, s32 tab = 0);
    virtual ~MojoInstVisitor();

    using TextInstVisitor::visit;

    void visit(AddBargraphInst* inst)       override;
    void visit(AddButtonInst* inst)         override;
    void visit(AddMetaDeclareInst* inst)    override;
    void visit(AddSliderInst* inst)         override;
    void visit(AddSoundfileInst* inst)      override;
    void visit(BinopInst* inst)             override;
    void visit(CastInst* inst)              override;
    void visit(CloseboxInst* inst)          override;
    void visit(DeclareFunInst* inst)        override;
    void visit(DeclareStructTypeInst* inst) override;
    void visit(DeclareVarInst* inst)        override;
    void visit(DoubleArrayNumInst* inst)    override;
    void visit(DropInst* inst)              override;
    void visit(FloatArrayNumInst* inst)     override;
    void visit(ForLoopInst* inst)           override;
    void visit(FunCallInst* inst)           override;
    void visit(IfInst* inst)                override;
    void visit(IndexedAddress* inst)        override;
    void visit(Int32NumInst* inst)          override;
    void visit(Int64NumInst* inst)          override;
    void visit(LabelInst* inst)             override;
    void visit(LoadVarAddressInst* inst)    override;
    void visit(NamedAddress* inst)          override;
    void visit(OpenboxInst* inst)           override;
    void visit(Select2Inst* inst)           override;
    void visit(SimpleForLoopInst* inst)     override;
    void visit(StoreVarInst* inst)          override;

    static void cleanup();

protected:
    // `RetInst` helper
    void visitAux(RetInst* inst, bool genEmpty) override;
    // `IfInst` helpers
    // `DeclareFunInst` helpers
    void writeFunDefArgs(DeclareFunInst* inst);
    void writeFunDefBody(DeclareFunInst* inst);
    void writeFunDefHeader(DeclareFunInst* inst);

    // Global operations
    static String       gToFaustFloat(String const& str);
    static MathLibTable gCreateMathLibTable();
        
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
    - `out`: the stream to write to.
    - `tab`: the number of tabs for indentation.
    @glob
    - Allows to generate a `zero initializer` for a given `typed` value.
**/
class MojoInitFieldsVisitor : public DispatchVisitor {
public:
    using DispatchVisitor::visit;
    OStream* fOut;
    s32      fTab;

    MojoInitFieldsVisitor(OStream* out, s32 tab = 0);

    void visit(DeclareVarInst* inst)     override;
    void visit(NamedAddress* inst)       override;
    void visit(Int32ArrayNumInst* inst)  override;
    void visit(FloatArrayNumInst* inst)  override;
    void visit(DoubleArrayNumInst* inst) override;

    static void gZeroInitializer(OStream* out, Typed* typed);
};

// Mapping to mojo DType
using DType = s32;
inline constexpr DType DType_s32 = 0;
inline constexpr DType DType_f32 = 1;
inline constexpr DType DType_f64 = 2;
inline constexpr DType DType_dfaust = 3;
static String dtype_values[4] = {"s32", "f32", "f64", "dfaust"};
static String dtype_widths[4] = {"w32", "w32", "w64", "wfaust"};

/**
    A `MojoVecInstVisitor` is a `MojoInstVisitor` when the `-vec` mode is enabled.
    @desc
    - Produces and writes explicit SIMD expressions.
    - An instance is created with an `output` stream, a `tab` number, 
      and a `struct name`.
    - XXX:
 **/
class MojoVecInstVisitor : public MojoInstVisitor {
    // In the context of the project this class is only used in
    // `MojoVecCodeContainer::writeCompute` while generating the
    // `FaustDsp.compute(...)` method.
public:
    using MojoInstVisitor::visit;

    MojoVecInstVisitor(OStream* out, String const& structName, int tab = 0);

    void visit(CastInst* inst)       override;
    void visit(DoubleNumInst* inst)  override;
    void visit(FloatNumInst* inst)   override;
    void visit(ForLoopInst* inst)    override;
    void visit(IndexedAddress* inst) override;
    void visit(Int32NumInst* inst)   override;
    // void visit(LabelInst* inst)      override;
    void visit(NamedAddress* inst)   override;
    void visit(StoreVarInst* inst)   override;
    void visit(IfInst* inst)         override;

protected:

    // Global state
    static inline b32    gEmitSIMD;
    static inline b32    gEmitJoin;
    // static inline 
    static inline DType  gDRealVal;
    static inline String gLastValueID;

    void writeBargraphUpdate(ForLoopInst* inst, String& idx, String& dwidth);

    void visitStore(StoreVarInst* inst, String& idx);

    // Detect wrapped or non-contiguous indices that need a dedicated SIMD path.
    static b32 hasWrappedIndex(ValueInst* inst);
    static b32 hasWrappedIndex(Address* addr);

    // Detect plain contiguous stores handled by the simple SIMD store path.
    static b32 isUnitStride(Address* addr);

    // Get the dtype of a value.
    // static String getDTypeValue(ValueInst* inst);
    static DType getDType(ValueInst* value);

    static b32 mustEmitJoin(StoreVarInst* inst);

};

}       // namespace mojo
#endif  // MOJO_INSTRUCTIONS_HH
