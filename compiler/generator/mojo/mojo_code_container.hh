/*                                                                             *
*   SPDX-FileCopyrightText: 2026 GRAME, Centre National de Creation Musicale   *
*   SPDX-License-Identifier: LGPL-2.1-or-later                                 *
*                                                                             */

/** @file compiler/generator/mojo/mojo_code_container.hh **/

#ifndef MOJO_CODE_CONTAINER_HH
#define MOJO_CODE_CONTAINER_HH

// faust
#include "code_container.hh"
#include "dsp_factory.hh"
#include "vec_code_container.hh"

// mojo
#include "mojo_instructions.hh"

inline namespace mojo {

using Factory     = dsp_factory_base;
using TextFactory = text_dsp_factory_aux;

inline MojoInstVisitor*    gScalarProducer;
inline MojoVecInstVisitor* gVectorProducer;

/**
    A `MojoCodeContainer` is an abstract code container for the mojo backend.
    @desc
    - Provides the common code generation structure for mojo DSP classes.
    - An instance is created with a DSP class name, input/output count and
      an `output` stream.
    - Allows to produce a DSP factory, the generated class and the internal
      declarations required by the backend.
    - Allows to create scalar mojo code containers from an existing container.
    - Allows to produce the fundamental `compute` method of the generated DSP.
    @rep
    - Maintains an `out` stream to write the generated mojo code to.
    @glob
    - Maintains a `code producer` visitor used to translate Faust IR
      instructions into mojo code.
    - Allows to create a mojo code container from the DSP name, input/output
      count and output stream.
**/
class MojoCodeContainer : public virtual CodeContainer
{
protected:
    OStream* fOut;
    MojoCodeContainer() = default;

public:
    MojoCodeContainer(String const& name, s32 numInputs, s32 numOutputs, OStream* out);
    virtual ~MojoCodeContainer();

    // Public producers
    Factory* produceFactory()  override;
    void     produceClass()    override;
    void     produceInternal() override;

    // Factories
    CodeContainer*        createScalarContainer(String const& name, s32 subContKind) override;
    static CodeContainer* createContainer(
        String const& name, s32 numInputs, s32 numOutputs, OStream* out = new OString()
    );

protected:
    // Writers
    void writeFaustHeader();
    void writeClassHeaderAndFields(s32 n);
    void writeGlobalVariablesInlined(s32 n);
    void writeDefaultConstructor(s32 n);
    void writeGlobalVariablesInitializations(s32 n);
    void writeGetSampleRate(s32 n);
    void writeGetInputs(s32 n);
    void writeGetOutputs(s32 n);
    void writeClassInit(s32 n);
    void writeInstanceConstants(s32 n);
    void writeInstanceResetUserInterface(s32 n);
    void writeInstanceClear(s32 n);
    void writeInstanceInit(s32 n);
    void writeInit(s32 n);
    void writeInitFunctions(s32 n);
    void writeGetJson(s32 n);
    void writeMetadataFunc(s32 n);
    void writeBuildUserInterface(s32 n);

    virtual void writeCompute(s32 n) = 0;
};

/**
    A `MojoScalarCodeContainer` is a `MojoCodeContainer` for scalar mojo code
    generation.
    @desc
    - Provides the scalar code generation path for mojo DSP classes.
    - An instance is created with a DSP class name, input/output count,
      an `output` stream and a scalar sub-container kind.
    - Allows to produce the scalar version of the generated Faust DSP class.
    - Allows to produce the scalar `compute` method of the generated DSP.
**/
class MojoScalarCodeContainer : public MojoCodeContainer
{
public:
    MojoScalarCodeContainer(
        String const& name, s32 numInputs, s32 numOutputs, OStream* out, s32 subContKind
    );
    virtual ~MojoScalarCodeContainer();
protected:
    void writeCompute(s32 n) override;
};

/**
    A `MojoVecCodeContainer` is both a `VectorCodeContainer` and a
    `MojoCodeContainer` for the mojo backend when the `-vec` option is enabled.
    @desc
    - Provides the vector code generation path for mojo DSP classes.
    - An instance is created with a DSP class name, input/output count and
      an `output` stream.
    - Allows to produce the vectorized version of the generated Faust DSP class.
    - Allows to produce the vector `compute` method of the generated DSP.
**/
class MojoVecCodeContainer : public VectorCodeContainer, public MojoCodeContainer
{
public:
    MojoVecCodeContainer(const String& name, s32 numInputs, s32 numOutputs, OStream* out);
    virtual ~MojoVecCodeContainer();
protected:
    void writeCompute(s32 tab) override;
};

/**
    A `MojoGpuCodeContainer` generates a DSP and its GPU task schedule.
    @desc
    - Consumes the loop DAG produced by `DAGInstructionsCompiler`.
    - Generates initialization, UI and metadata with the Mojo CPU writers.
    - Stores block controls and intermediate arrays in a device work buffer.
    - Runs independent tasks concurrently and orders dependent stages.
    - Divides arbitrary audio blocks into bounded chunks of `-vs` samples.
    - Provides the `gpu_work_size` and `gpu_compute` architecture hooks.
    @rep
    - fWork: scratch declarations shared by device kernels.
    - fViews: local aliases of inline arrays, recreated in each kernel.
    - fAliases: underlying scratch resources referenced by pointer aliases.
    - fStages: ordered batches of independent FIR task bodies.
    @note
    - Select with `-lang mojo -gpu -double` (64-bit internal computation).
    - Each task preserves sample order; `par` exposes independent branches.
    - Uses the same `CodeLoop::sortGraph` levels as `OpenMPCodeContainer`.
      Ordered launches replace the barriers between OpenMP sections.
    - The runtime allocates work before audio starts and synchronizes audio.
    - This first version supports flat DSP state without soundfiles or
      separately allocated tables. It does not distribute a reduction or
      a recurrence over sample threads.
**/
class MojoGpuCodeContainer : public MojoCodeContainer
{
    using Names = std::set<String>;
    using Stage = std::vector<BlockInst*>;
    using Aliases = std::map<String, Names>;
    using Stages = std::vector<Stage>;

    Work    fWork;
    Views   fViews;
    Aliases fAliases;
    Stages  fStages;

public:
    MojoGpuCodeContainer(String const& name, s32 n_ins, s32 n_outs, OStream* out);

    void produceClass() override;

protected:
    void writeCompute(s32 n) override;


private:
    String workName() const { return fKlassName + "Work"; }

    // Collect direct address references used to initialize scratch pointers.
    struct AddressRefs : DispatchVisitor
    {
        Names names;
        using DispatchVisitor::visit;
        void visit(LoadVarAddressInst* inst) override
        {
            names.insert(inst->getName());
            DispatchVisitor::visit(inst);
        }
    };

    // Whole-resource conflicts conservatively protect shared state and aliases.
    struct Accesses : DispatchVisitor
    {
        MojoGpuCodeContainer const& owner;
        Names reads;
        Names writes;
        using DispatchVisitor::visit;

        explicit Accesses(MojoGpuCodeContainer const& container) : owner(container) {}

        void add(Address* address, Names& names)
        {
            String name = address->getName();
            if (address->isStruct()
                || address->isStaticStruct()
                || owner.fWork.count(name)
                || owner.fViews.count(name)
                || MojoGpuInstVisitor::isChannel(name)
            ) {
                owner.resources(name, names);
            }
        }
        void visit(LoadVarInst* inst) override
        {
            add(inst->fAddress, reads);
            DispatchVisitor::visit(inst);
        }
        void visit(StoreVarInst* inst) override
        {
            add(inst->fAddress, writes);
            DispatchVisitor::visit(inst);
        }
        void visit(DeclareVarInst* inst) override
        {
            if (inst->fValue) {
                add(inst->fAddress, writes);
            }
            DispatchVisitor::visit(inst);
        }
        void visit(LoadVarAddressInst* inst) override
        {
            add(inst->fAddress, reads);
            DispatchVisitor::visit(inst);
        }
    };

    void resources(String const& name, Names& result) const;

    static bool intersects(Names const& lhs, Names const& rhs);

    static bool isFlat(Typed* type);

    void checkFields();

    void collectWork(BlockInst* block);

    String taskKey(BlockInst* block);

    void planTasks();

    void writeFields(BlockInst* block, size_t width);

    void writeWork();

    void writeEvidence(s32 n);

    void
    writeLaunch(String const& name, s32 n, size_t tasks, String const& size, String const& offset);

    void writeKernelHeader(String const& name, s32 n, bool single);

    void writeBody(BlockInst* block, s32 n);
};

};      // namespace mojo
#endif  // MOJO_CODE_CONTAINER_HH
