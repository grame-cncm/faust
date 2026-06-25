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
#include <memory_resource>
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
    MojoInstVisitor(OStream* out, String const& structName, i32 tab = 0);
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
    void visit(IndexedAddress* indexed)     override;
    void visit(Int32NumInst* inst)          override;
    void visit(Int64NumInst* inst)          override;
    void visit(LabelInst* inst)             override;
    void visit(LoadVarAddressInst* inst)    override;
    void visit(NamedAddress* named)         override;
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
    static MathLibTable gMathLibTable;
    static FuncSymTable gFuncSymTable;
};

/** A `MojoVecInstVisitor` is a `MojoInstVisitor` for the vec mode. **/
class MojoVecInstVisitor : public MojoInstVisitor {
public:
    using MojoInstVisitor::visit;

    MojoVecInstVisitor(OStream* out, String const& structName, int tab = 0);

    void visit(ForLoopInst* inst) override;
    void visit(LabelInst* inst)   override;

protected:

    // `ForLoopInst` help writers.
    void writeBargraphUpdate(ForLoopInst* inst, String const& idx_name, ValueInst* end_val);
    void writeSIMDBroadcastStore(String const& lhs_name, ValueInst* rhs, String const& dtype_name,
                                 String const& width_name, String const& idx_name);
    void writeSIMDIndexedLoadStore(String const& lhs_name, ValueInst* rhs, String const& dtype_name,
                                   String const& width_name, String const& idx_name);
    void writeSIMDIndexedComputationStore(String const& lhs_name, ValueInst* rhs, String const& dtype_name,
                                          String const& width_name, String const& idx_name);

    // `ForLoopInst` helpers to write SIMD loops.
    void writeSIMDLoopHeader(ForLoopInst*  inst, String const& dtype_name, String const& dtype_value,
                             String const& width_name, String const& idx_name, ValueInst* end_val);
    void writeSIMDIndexInc(String const& idx_name, String const& width_name);
    // Detect loops that contain a bargraph update in addition to the normal store.
    static b32 hasBargraphUpdate(ForLoopInst* inst);
    // Detect wrapped or non-contiguous indices that need a dedicated SIMD path.
    static b32 hasWrappedIndex(Address* addr);
    static b32 hasWrappedIndex(ValueInst* value);
    // Detect plain contiguous stores handled by the simple SIMD store path.
    static b32 isUnitStrideStore(Address* addr, String const& idx_name);
    // Detect scalar RHS values that can be expanded to all SIMD lanes.
    static b32 isBroadcastValue(ValueInst* value, String const& idx_name);
    // Detect indexed loads optionally wrapped in casts.
    static b32 isIndexedLoad(ValueInst* value, String const& idx_name);
    // Detect indexed RHS computations handled by the SIMD expression path.
    static b32 isIndexedComputation(ValueInst* value, String const& idx_name);

    static String getDTypeValue(ValueInst* rhs);
    static Tuple<String, String, String> getDTypeProperties(ValueInst* rhs);
    static Tuple<StoreVarInst*, Address*, ValueInst*, String> parseSingleStore(BlockInst* rhs);

    static String getIndexName(ForLoopInst* inst);
    static ValueInst* getEndValue(ForLoopInst* inst);
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

    MojoInitFieldsVisitor(OStream* out, i32 tab = 0);

    void visit(DeclareVarInst* inst)     override;
    void visit(NamedAddress* named)      override;
    void visit(Int32ArrayNumInst* inst)  override;
    void visit(FloatArrayNumInst* inst)  override;
    void visit(DoubleArrayNumInst* inst) override;

    static void gZeroInitializer(OStream* out, Typed* typed);
};

}       // namespace mojo
#endif  // MOJO_INSTRUCTIONS_HH
