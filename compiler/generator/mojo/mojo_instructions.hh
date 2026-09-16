/*                                                                             *
*   SPDX-FileCopyrightText: 2026 GRAME, Centre National de Creation Musicale   *
*   SPDX-License-Identifier: LGPL-2.1-or-later                                 *
*                                                                             */

/** @file compiler/generator/mojo/mojo_instructions.hh */

#ifndef MOJO_INSTRUCTIONS_HH
#define MOJO_INSTRUCTIONS_HH

// faust
#include "struct_manager.hh"
#include "text_instructions.hh"

// mojo
#include "__mojo_utils.hh"

inline namespace mojo {

using MathLibTable = std::unordered_map<String, String>;
using FuncSymTable = std::unordered_map<String, b32>;

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
class MojoInstVisitor : public TextInstVisitor
{
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
    static inline MathLibTable gMathLibTable;
    static inline FuncSymTable gFuncSymTable;
};

/**
    A `MojoVecInstVisitor` is a `MojoInstVisitor` when the `-vec` mode is enabled.
    @desc
    - Produces and writes explicit SIMD expressions.
    - An instance is created with an `output` stream, a `tab` number, 
      and a `struct name`.
    - XXX:
 **/
class MojoVecInstVisitor : public MojoInstVisitor
{
// In the context of the project this class is only used in
// `MojoVecCodeContainer::writeCompute` while generating the
// `FaustDsp.compute(...)` method.

public:
    // Mapping to mojo DType
    enum MojoDType : s32 {
        MojoDType_none  = -1,
        MojoDType_s32   = 0,
        MojoDType_f32   = 1,
        MojoDType_f64   = 2,
        MojoDType_faust = 3,
        MojoDType_bool  = 4,
    };

    static MojoDType getMojoDType(ValueInst* value);

    // Enable base class operations
    using MojoInstVisitor::visit;

    MojoVecInstVisitor(OStream* out, String const& structName, s32 tab = 0);
    virtual ~MojoVecInstVisitor();

    void visit(IfInst* inst)         override;
    void visit(Int32NumInst* inst)   override;
    void visit(BoolNumInst* inst)    override;
    void visit(FloatNumInst* inst)   override;
    void visit(DoubleNumInst* inst)  override;
    void visit(DeclareVarInst* inst) override;
    void visit(NamedAddress* inst)   override;
    void visit(Select2Inst* inst)    override;
    void visit(LoadVarInst* inst)    override;
    void visit(CastInst* inst)       override;
    void visit(IndexedAddress* inst) override;
    void visit(BinopInst* inst)      override;
    void visit(ForLoopInst* inst)    override;

    // Global state
    static inline b32        gSIMDEmit;
    static inline b32        gSIMDHigh;
    static inline b32        gSIMDHalf;
    static inline MojoDType  gCurLhsDT;
    static inline String     gCurAddrs;
    static inline Address*   gCurIndex;
    static inline String     gCurGraph;

protected:
    // Visitor wrappers
    void visitMain(ForLoopInst* inst);
    void visitScalar(ForLoopInst* inst);
    void visitBargraphUpdate(ForLoopInst* inst);
    void visitBargraphMulti(ForLoopInst* inst);
    void visitBroadcast(StoreVarInst* inst);
    void visitSplit(StoreVarInst* inst);
    void visitJoin(StoreVarInst* inst);
    void visitStore(StoreVarInst* inst);
    void visitBinopOperand(ValueInst* inst);
    b32  visitIndex(ValueInst* inst);

    // Helpers
    void prepareLoop(StoreVarInst* inst);
    void visitLoopStore(ForLoopInst* loop, StoreVarInst* store);
    void finishLoop();
    void resetLoopContext();

    static b32 isBargraphStore(StoreVarInst* inst);
    static b32 isVectorizable(Address* addr);
    static b32 isVectorizable(ValueInst* inst);
    static b32 hasWrappedIndex(Address* addr);
    static b32 hasWrappedIndex(ValueInst* inst);
    static b32 isWrappedIndexExpr(ValueInst* inst);
    static b32 isScalarAddress(Address* addr);
    static b32 isScalarValue(ValueInst* inst);
    static b32 hasF64Value(ValueInst* inst);

    static ValueInst* stripCasts(ValueInst* inst);
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
    - Allows to generate a `zero initializer` for a given `Typed` value.
**/
class MojoInitFieldsVisitor : public DispatchVisitor
{
public:
    using DispatchVisitor::visit;
    OStream*  fOut;
    s32       fTab;

    MojoInitFieldsVisitor(OStream* out, s32 tab = 0);

    void visit(DeclareVarInst* inst)     override;
    void visit(NamedAddress* inst)       override;
    void visit(Int32ArrayNumInst* inst)  override;
    void visit(FloatArrayNumInst* inst)  override;
    void visit(DoubleArrayNumInst* inst) override;

    static void gZeroInitializer(OStream* out, Typed* typed);
};

// GPU visitor aliases
using Work  = std::unordered_map<String, Typed*>;
using Views = std::unordered_map<String, LoadVarAddressInst*>;
using Loops = std::unordered_map<String, String>;

/**
    A `MojoGpuInstVisitor` emits scalar FIR instructions inside GPU tasks.
    @desc
    - Uses device pointers for DSP fields and shared work variables.
    - Preserves scalar loop order, including recursive state updates.
    - Keeps task-local temporaries local to the executing GPU thread.
    - Rejects foreign calls that require an unspecified device implementation.
    @rep
    - fWork: declarations stored in the preallocated device work buffer.
    - fViews: local pointers reconstructed from inline device arrays.
    - fLoops: active loop-index names, unique within the emitted task.
    - fLoopId: suffix used to distinguish sequential FIR loop bindings.
    @note
    - Input and output channel pointers are supplied by the container.
**/
class MojoGpuInstVisitor : public MojoInstVisitor
{

    // NOTE:(Ari) put the fucking state here not on at the end of the scope
    Work const&   fWork;
    Views const&  fViews;
    Loops         fLoops;
    s32           fLoopId = 0;

public:
    using MojoInstVisitor::visit;

    MojoGpuInstVisitor(
        OStream* out, String const& name, Work const& work, Views const& views, s32 tab = 0
    );

    void visit(NamedAddress* inst)   override;
    void visit(DeclareVarInst* inst) override;
    void visit(IndexedAddress* inst) override;
    void visit(FloatNumInst* inst)   override;
    void visit(DoubleNumInst* inst)  override;
    void visit(ForLoopInst* inst)    override;
    void visit(FunCallInst* inst)    override;

    static bool isChannel(String const& name);
};

}       // namespace mojo
#endif  // MOJO_INSTRUCTIONS_HH
