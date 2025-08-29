/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2025 GRAME, Centre National de Creation Musicale
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

#pragma once

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <map>
#include <stack>
#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
// #define FAUSTFLOAT float
#endif

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"

#include "Text.hh"
#include "description.hh"
#include "fir_to_fir.hh"
#include "global.hh"
#include "instructions.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "sigIdentity.hh"
#include "signalVisitor.hh"
#include "sigtyperules.hh"

inline BasicTyped* genBasicTyped(Tree sig)
{
    return IB::genBasicTyped(convert2FIRType(getCertifiedSigType(sig)->nature()));
}

/**
 * @brief Compiles a Faust signal graph into the FIR (Faust Intermediate Representation).
 *
 * `SignalFIRCompiler` emits a **static FIR program** that back‑ends (LLVM, Wasm,
 * interpreter…) can further optimise or execute.
 *
 * Several FIR basic blocks are produced:
 * **fGlobalBlock**   — helper function declarations and static data
 * **fDeclareBlock**  — struct fields declaration
 * **fInitBlock**     — code executed in `instanceInit`
 * **fResetBlock**    — code executed in `instanceResetUserInterface`
 * **fClearBlock**    — code executed in `instanceClear`
 * **fMetadataBlock** — code executed in `metadata`
 * **fUIBlock**       — code executed in `buildUserInterface`
 * **fTablesBlock**   — code to build tables
 * **fControlBlock**  — per‑block computations done in `compute` function before the DSP loop
 * **fSampleBlock**   — the per‑sample DSP body done in `compute`function
 *
 * During construction the compiler:
 * 1. Runs a `SignalBuilder` pass that allocates every resource
 * (delay‑lines, tables, UI variables) and assigns unique identifiers.
 * 2. Allows `compileTables()` to emit FIR loops that pre‑fill lookup tables.
 *
 * Then:
 * 3. Generates FIR instructions for each output signal with `compile()`.
 *
 * Delay‑lines, tables and UI zones materialise as FIR load/store operations
 * on arrays or struct fields whose lifetime is guaranteed by the generated
 * DSP class.
 */
struct SignalFIRCompiler : public SignalVisitor {
    // Utility
    inline bool isZeroDelay(Tree sig)
    {
        Type     ty = getCertifiedSigType(sig);
        interval it = ty->getInterval();
        return (it.hi() == 0.0);
    }

    ValueInst* genCastedOutput(int type, ValueInst* value)
    {
        bool need_cast = (type == kInt) || !gGlobal->gFAUSTFLOAT2Internal;
        return (need_cast) ? IB::genCastFloatMacroInst(value) : value;
    }

    /**
     * @brief A circular buffer implementing delay lines for signals of a given type.
     *
     * This templated structure is used to store delayed versions of a signal
     * in a circular buffer for efficient sample-accurate delays. Delay lines
     * are essential for implementing feedback, recursive structures, and
     * time-based signal processing in audio DSP (e.g., echoes, filters).
     */
    struct DelayLine {
        std::string         fName;  ///< Name used for the underlying array variable
        int                 fSize;  ///< Delay line size
        Address::AccessType fAccess = Address::kStruct;  ///< Where the array lives for now

        DelayLine() = default;

        DelayLine(SignalFIRCompiler& compiler, int type, int size, bool rec,
                  Address::AccessType access = Address::kStruct)
            : fSize(size), fAccess(access)
        {
            faustassert((size & (size - 1)) == 0 && "delay‑line size must be a power of two");

            // Create proper name
            if (type == kInt) {
                fName = gGlobal->getFreshID((rec) ? "iRec" : "iVec");
            } else {
                fName = gGlobal->getFreshID((rec) ? "fRec" : "fVec");
            }

            // Declare the delay line as an array in DSP struct
            compiler.fDeclareBlock->pushBackInst(
                IB::genDeclareVarInst(IB::genNamedAddress(fName, fAccess),
                                      IB::genArrayTyped(convert2FIRType(type), size)));

            // Initialize the delay line with 0
            ForLoopInst* loop = IB::genForLoopInst(gGlobal->getFreshID("l"), 0, size, 1);
            loop->pushFrontInst(IB::genStoreArrayVar(fName, fAccess, loop->loadLoopVar(),
                                                     IB::genTypedZero(convert2FIRType(type))));
            compiler.fClearBlock->pushBackInst(loop);
        }

        void resize(int size) { fSize = std::max(fSize, size); }

        /* ------------------------------------------------------------
         * Compile reading a value in the circular buffer
         *
         * This method applies a bitwise mask to the given index to
         * ensure it wraps within the buffer size (power-of-two size
         * assumed). It then returns the value stored at the resulting
         * position.
         *
         * @param index The index from which to read (wrapped by mask).
         * @return A ValueInst* representing the buffer element at the
         * masked index.
         * ---------------------------------------------------------- */
        ValueInst* read(ValueInst* index)
        {
            ValueInst* masked = IB::genAnd(index, IB::genInt32NumInst(fSize - 1));
            return IB::genLoadArrayVar(fName, fAccess, masked);
        }

        /* ------------------------------------------------------------
         * Compile writing a value in the circular buffer
         *
         * This method applies a bitwise mask to the given index to
         * ensure it wraps within the buffer size (power-of-two size
         * assumed). It then generates a store instruction to update
         * the buffer at the masked index.
         *
         * @param index The index at which to write (wrapped by mask).
         * @param value The value to write into the buffer.
         * @return A StatementInst* representing the store operation.
         * ---------------------------------------------------------- */
        StatementInst* write(ValueInst* index, ValueInst* value)
        {
            ValueInst* masked = IB::genAnd(index, IB::genInt32NumInst(fSize - 1));
            return IB::genStoreArrayVar(fName, fAccess, masked, value);
        }

        // Method to reset fBuffer content to 0
        void reset() {}
    };

    /**
     * @brief Represents a static table for FIR-like load/store operations.
     *
     * The `TableData` structure models a named array in the DSP struct, where
     * each element can be read from or written to using generated FIR
     * instructions. It is primarily used to implement lookup tables, buffers, or other
     * fixed-size memory structures in the DSP context.
     *
     * ## Key Features
     * - Provides FIR-level read and write operations to a named table.
     * - Supports optional initialization using a signal generator (`fSigGen`).
     * - Can be used for constant folding or static initialization.
     */
    struct TableData {
        std::string fName;            ///< Variable name for the table array in the DSP struct.
        int         fSize = 0;        ///< Number of elements in the table (must be > 0).
        Tree fSigGen      = nullptr;  ///< Optional signal generator used for static initialization.
        Address::AccessType fAccess = Address::kStruct;  ///< Memory access mode for the table.

        /**
         * @brief Default constructor. Creates an uninitialized table.
         */
        TableData() = default;

        /**
         * @brief Constructs a new table.
         * @param compiler The compiler containing blocks to fill.
         * @param sig_gen  Signal generator for initializing the table content.
         * @param size     Number of elements in the table (must be strictly positive).
         * @param access   The memory access type for the table (default: `Address::kStruct`).
         */
        TableData(SignalFIRCompiler& compiler, Tree sig_gen, int size,
                  Address::AccessType access = Address::kStruct)
            : fSize(size), fSigGen(sig_gen), fAccess(access)
        {
            int type = getCertifiedSigType(sig_gen)->nature();
            fName    = gGlobal->getFreshID((type == kInt) ? "iTable" : "fTable");

            // Declare the table as an array in DSP struct
            compiler.fDeclareBlock->pushBackInst(
                IB::genDeclareVarInst(IB::genNamedAddress(fName, fAccess),
                                      IB::genArrayTyped(convert2FIRType(type), size)));

            faustassert(size > 0 && "table size must be strictly positive");
        }

        /**
         * @brief Returns the size of the table.
         *
         * @return The number of elements in the table.
         */
        int size() const { return fSize; }

        /**
         * @brief Reads a value from the table.
         *
         * Generates an FIR instruction to load a value from a specific index in the table.
         *
         * @param index A `ValueInst` representing the index to read from.
         * @return A `ValueInst` representing the value stored at the given index.
         */
        ValueInst* read(ValueInst* index) { return IB::genLoadArrayVar(fName, fAccess, index); }

        /**
         * @brief Writes a value into the table.
         *
         * Generates an FIR instruction to store a value at a specific index in the table.
         *
         * @param index A `ValueInst` representing the index to write to.
         * @param value A `ValueInst` representing the value to be stored.
         * @return A `StatementInst` representing the generated store operation.
         */
        StatementInst* write(ValueInst* index, ValueInst* value)
        {
            return IB::genStoreArrayVar(fName, fAccess, index, value);
        }

        /**
         * @brief Fills the table with a given value.
         *
         * Generates FIR store instructions for each table slot, initializing them with
         * the same value. This is a naive implementation that iterates in C++ and
         * emits one store per element. A future optimization could generate a single
         * data segment for initialization.
         *
         * @param val The value to be written to every table slot.
         */
        void fill(ValueInst* val)
        {
            // Currently commented out; left for future optimization.
            /*
             for (int i = 0; i < fSize; ++i) {
             IB::currentBlock()->pushBackInst(IB::genStoreArrayVar(
             fName, fAccess, IB::genInt32NumInst(i), IB::genConst(val)));
             }
             */
        }
    };

    /**
     * @brief Represents a user interface control element (sliders, nentries, buttons).
     *
     * The `inputControl` structure defines the configuration and runtime integration of
     * user interface controls that allow users to interact with signal parameters.
     * These controls are typically generated in DSP struct (e.g., sliders, buttons,
     * and numerical entries) and are automatically linked to the internal DSP state.
     *
     * ## Key Features
     * - Supports different control types (buttons, sliders, and numerical entries).
     * - Maintains control metadata such as label, initial value, range, and step size.
     * - Automatically declares and initializes the control in the DSP struct.
     */
    struct inputControl {
        /**
         * @brief Types of user interface controls.
         */
        enum type {
            kButton,       ///< A binary button (on/off trigger).
            kCheckbutton,  ///< A toggleable checkbox (persistent state).
            kVslider,      ///< A vertical slider for continuous values.
            kHslider,      ///< A horizontal slider for continuous values.
            kNumEntry      ///< A numerical entry field for direct value input.
        };

        /// Human-readable names for control types (used for unique ID generation).
        inline static std::string gTypeName[] = {"fButton", "fCheckbutton", "fVslider", "fHslider",
                                                 "fNumEntry"};

        type        fType;   ///< The type of control.
        std::string fLabel;  ///< Display label shown to the user.
        std::string fName;   ///< Unique identifier for this control in the DSP struct.
        double      fInit;   ///< Initial value of the control.
        double      fMin;    ///< Minimum allowed value.
        double      fMax;    ///< Maximum allowed value.
        double      fStep;   ///< Step size for value changes (e.g. slider increment).

        /**
         * @brief Default constructor. Creates an uninitialized control.
         */
        inputControl() = default;

        /**
         * @brief Constructs a new user interface control and integrates it into the DSP.
         *
         * This constructor declares the control variable in the DSP struct and
         * initializes it with the given value.
         *
         * @param compiler       The compiler containing blocks to fill.
         * @param sig            The signal tree associated with this control (for DSP binding).
         * @param type           The type of the control (button, slider, etc.).
         * @param label          The label displayed to the user.
         * @param init           The initial value of the control.
         * @param min            The minimum value allowed.
         * @param max            The maximum value allowed.
         * @param step           The increment step for adjusting the control.
         */
        inputControl(SignalFIRCompiler& compiler, Tree sig, type type, const std::string& label,
                     double init, double min, double max, double step)
            : fType(type), fLabel(label), fInit(init), fMin(min), fMax(max), fStep(step)
        {
            // Generate a unique variable name for this control based on its type
            fName = gGlobal->getFreshID(gTypeName[type]);

            // Declare and initialize the control variable in the DSP struct
            compiler.fDeclareBlock->pushBackInst(
                IB::genDecStructVar(fName, IB::genBasicTyped(Typed::kFloatMacro)));
            compiler.fResetBlock->pushBackInst(
                IB::genStoreStructVar(fName, IB::genRealNumInst(Typed::kFloatMacro, init)));

            // Create UI item
            switch (type) {
                case kButton:
                    compiler.fUIBlock->pushBackInst(IB::genAddButtonInst(fLabel, fName));
                    break;
                case kCheckbutton:
                    compiler.fUIBlock->pushBackInst(IB::genAddCheckbuttonInst(fLabel, fName));
                    break;
                case kVslider:
                    compiler.fUIBlock->pushBackInst(
                        IB::genAddVerticalSliderInst(fLabel, fName, init, min, max, step));
                    break;
                case kHslider:
                    compiler.fUIBlock->pushBackInst(
                        IB::genAddHorizontalSliderInst(fLabel, fName, init, min, max, step));
                    break;
                case kNumEntry:
                    compiler.fUIBlock->pushBackInst(
                        IB::genAddNumEntryInst(fLabel, fName, init, min, max, step));
                    break;
                default:
                    faustassert(false);
                    break;
            };
        }

        /**
         * @brief Compiles loading the value.
         *
         * @return A pointer to the value instruction representing this control's value.
         */
        ValueInst* getValue() { return IB::genLoadStructVar(fName); }
    };

    /**
     * @brief Represents a user interface output control (bargraph).
     *
     * The `outputControl` structure defines the configuration and integration of output controls
     * used to visualize signal values in the DSP struct. These controls do not accept user
     * input; instead, they display real-time data such as signal levels or metering information.
     *
     * ## Key Features
     * - Supports horizontal and vertical bargraph types.
     * - Maintains control metadata such as label and value range.
     * - Automatically declares the control in the DSP struct.
     */
    struct outputControl {
        /**
         * @brief Types of output controls.
         */
        enum type {
            kHbargraph,  ///< A horizontal bargraph for signal visualization.
            kVbargraph   ///< A vertical bargraph for signal visualization.
        };

        /// Human-readable names for control types (used for unique ID generation).
        inline static std::string gTypeName[] = {"fHbargraph", "fVbargraph"};

        type        fType;   ///< The type of output control.
        std::string fLabel;  ///< Display label shown to the user.
        std::string fName;   ///< Unique identifier for this control in the DSP struct.
        double      fMin;    ///< Minimum value displayed by the bargraph (e.g. -60 dB).
        double      fMax;    ///< Maximum value displayed by the bargraph (e.g. 0 dB).

        /**
         * @brief Default constructor. Creates an uninitialized output control.
         */
        outputControl() = default;

        /**
         * @brief Constructs a new output control and integrates it into the DSP.
         *
         * This constructor declares the control variable in the DSP struct.
         *
         * @param compiler       The compiler containing blocks to fill.
         * @param sig            The signal tree associated with this control (for DSP binding).
         * @param type           The type of the control (horizontal or vertical bargraph).
         * @param label          The label displayed to the user.
         * @param min            The minimum value displayed by the bargraph.
         * @param max            The maximum value displayed by the bargraph.
         */
        outputControl(SignalFIRCompiler& compiler, Tree sig, type type, const std::string& label,
                      double min, double max)
            : fType(type), fLabel(label), fMin(min), fMax(max)
        {
            // Generate a unique variable name for this control based on its type
            fName = gGlobal->getFreshID(gTypeName[type]);

            // Declare the control variable in the DSP struct
            compiler.fDeclareBlock->pushBackInst(
                IB::genDecStructVar(fName, IB::genBasicTyped(Typed::kFloatMacro)));

            // Create UI item
            switch (type) {
                case kHbargraph:
                    compiler.fUIBlock->pushBackInst(
                        IB::genAddHorizontalBargraphInst(fLabel, fName, min, max));
                    break;
                case kVbargraph:
                    compiler.fUIBlock->pushBackInst(
                        IB::genAddVerticalBargraphInst(fLabel, fName, min, max));
                    break;
                default:
                    faustassert(false);
                    break;
            };
        }

        /**
         * @brief Compiles storing the new value.
         *
         * @param val The value to display.
         * @return A pointer to the generated instruction for updating the bargraph value.
         */
        StatementInst* setValue(ValueInst* val) { return IB::genStoreStructVar(fName, val); }
    };

    /**
     * @brief Class to traverse and prepare signal trees for compiling.
     *
     * The `SignalBuilder` class is responsible for analyzing the output signal trees,
     * allocating all necessary resources such as delay lines, tables, and input/output controls,
     * and performing preliminary setup before compiling. It ensures that each signal
     * has the correct data structures allocated for sample compilation.
     *
     * Key responsibilities:
     * - Allocates delay lines for signals that require delays or recursive definitions.
     * - Allocates tables for signals that generate lookup data.
     * - Registers input and output controls such as sliders and bargraphs.
     */
    struct SignalBuilder : public SignalVisitor {
        SignalFIRCompiler& fCompiler;

        /**
         * @brief Allocates or resizes a delay line for a given signal. All delay lines have a
         * power-of-two size and the IOTA based global index access.
         *
         * This method is responsible for ensuring that a delay line
         * exists and is of sufficient size for the signal `x`. The maximum delay amount is
         * determined by the `delay` value, which represents the signal controlling
         * the delay length.
         *
         * The nature of the signal `x` (integer or real) determines whether an `fDelays`
         * entry is used. The size of the delay line buffer is calculated
         * using `pow2limit(max_delay + 1)` to ensure it's a power of two, which is
         * efficient for circular buffer implementations using bitwise AND for indexing.
         *
         * If a delay line for `x` already exists, its size is compared with the newly
         * required size (`N`), and it's resized if `N` is larger. If it doesn't exist,
         * a new `DelayLine` is created and stored in the appropriate `fDelays` map
         * with `x` as the key.
         *
         * @param x The signal tree node that identifies the signal requiring the delay line.
         * The type of this signal (int or real) determines the type of the delay buffer.
         * @param delay The signal tree node representing the delay amount.
         * The interval analysis of this signal (`it.hi()`) provides the
         * maximum required delay length.
         */
        void allocateDelayLine(Tree x, int delay, bool rec = false)
        {
            allocateDelayLineAux(x, delay, rec);
        }

        void allocateDelayLine(Tree x, Tree y, bool rec = false)
        {
            Type     ty = getCertifiedSigType(y);
            interval it = ty->getInterval();
            allocateDelayLineAux(x, it.hi(), rec);
        }

        virtual void allocateDelayLineAux(Tree x, int delay, bool rec = false)
        {
            int nature = getCertifiedSigType(x)->nature();  // Nature of the signal being delayed
            int N      = pow2limit(delay + 1);              // Max delay rounded up to power of 2

            if (fCompiler.fDelays.count(x) == 0) {
                /*
                 if (global::isDebug("SIG_COMPILER")) {
                 std::cout << "allocateDelayLine NEW " << ppsig(x, 8) << std::endl;
                 }
                 */
                fCompiler.fDelays[x] = DelayLine(fCompiler, nature, N, rec);
            } else {
                /*
                 if (global::isDebug("SIG_COMPILER")) {
                 std::cout << "allocateDelayLine RESIZE INT " << ppsig(x, 8) << std::endl;
                 }
                 */
                fCompiler.fDelays[x].resize(N);
            }
        }

        /**
         * @brief SignalBuilder – Traverses a signal tree and allocates required runtime structures.
         *
         * The `SignalBuilder` is a specialized signal visitor that analyzes a Faust signal DAG
         * and generates the runtime data structures required for DSP execution.
         *
         * These structures include:
         * - Delay lines for `@` operations and recursive signals.
         * - Static tables for waveforms or explicit table-write (`wrtbl`) expressions.
         * - Input controls (buttons, sliders, checkboxes, numeric entries).
         * - Output controls (horizontal and vertical bargraphs).
         *
         * It also populates declaration and reset blocks with the instructions needed to
         * initialize these structures in the generated FIR.
         *
         * ## Constructor
         *
         * @param compiler The compiler.
         */
        SignalBuilder(SignalFIRCompiler& compiler) : fCompiler(compiler) { fVisitGen = true; }

        /**
         * @brief Visits a signal node and generates any required runtime structure.
         *
         * This method overrides `SignalVisitor::visit()` and performs a pattern-matching
         * traversal of the signal tree. For each signal node, it determines whether a
         * delay line, table, input control, or output control needs to be allocated.
         *
         * ### Signal patterns handled:
         * - **Delays**:
         * - `isSigDelay1`: Allocates a 1-sample delay.
         * - `isSigDelay`: Allocates a delay line of variable length (runtime or compile-time).
         * - `isProj` on recursive signals: Allocates implicit single-sample delays for recursion.
         *
         * - **Tables**:
         * - `isSigWRTbl`: Allocates a named table for read/write table operations.
         * - `isSigWaveform`: Prepares waveform tables (currently placeholder logic).
         *
         * - **Input Controls**:
         * - `isSigButton`: Creates a button control.
         * - `isSigCheckbox`: Creates a checkbox control.
         * - `isSigVSlider` / `isSigHSlider`: Creates vertical or horizontal sliders.
         * - `isSigNumEntry`: Creates a numeric entry control.
         *
         * - **Output Controls**:
         * - `isSigVBargraph` / `isSigHBargraph`: Creates vertical or horizontal bargraphs.
         *
         * Any signal node not matching one of the above cases is forwarded to the base
         * `SignalVisitor::visit()` for standard traversal.
         *
         * @param sig The current signal node being visited.
         */
        void visit(Tree sig) override
        {
            Tree path, c, x, y, z;
            Tree size_tree, gen_tree, wi_tree, ws_tree;
            Tree rec_expr_tree, rec_vars, rec_exprs;  // For isProj/isRec
            int  proj_idx_val;

            if (isSigDelay1(sig, x)) {
                allocateDelayLine(x, 1);  // Delay of 1 sample
                SignalVisitor::visit(sig);
            } else if (isSigDelay(sig, x, y)) {
                allocateDelayLine(x, y);  // y is the delay amount signal
                SignalVisitor::visit(sig);
            } else if (isProj(sig, &proj_idx_val, rec_expr_tree) &&
                       isRec(rec_expr_tree, rec_vars, rec_exprs)) {
                // This projection 'sig' represents a recursive variable's state.
                // It implicitly requires a 1-sample delay buffer.
                allocateDelayLine(sig, 1, true);
                SignalVisitor::visit(sig);
            } else if (isSigWRTbl(sig, size_tree, gen_tree, wi_tree, ws_tree)) {
                int size_val;
                isSigInt(size_tree, &size_val);
                fCompiler.fTables[sig] = TableData(fCompiler, gen_tree, size_val);
                SignalVisitor::visit(sig);
            } else if (isSigWaveform(sig)) {
                /*
                 int size = sig->arity();
                 if (fWaveforms.count(sig) == 0) {
                 Type c_type = getCertifiedSigType(sig);
                 if (c_type->nature() == kInt) {
                 fTables[sig] = TableData(gGlobal->getFreshID("iWaveform"), sig, size);
                 } else {
                 fTables[sig] = TableData(gGlobal->getFreshID("fWaveform"), sig, size);
                 }
                 }
                 */
            } else if (isSigButton(sig, path)) {  // UI
                fCompiler.fInputControls[sig] =
                    inputControl(fCompiler, sig, inputControl::kButton,
                                 removeMetadata(tree2str(hd(path))), 0, 0, 1, 1);
            } else if (isSigCheckbox(sig, path)) {
                fCompiler.fInputControls[sig] =
                    inputControl(fCompiler, sig, inputControl::kCheckbutton,
                                 removeMetadata(tree2str(hd(path))), 0, 0, 1, 1);
            } else if (isSigVSlider(sig, path, c, x, y, z)) {
                fCompiler.fInputControls[sig] = inputControl(
                    fCompiler, sig, inputControl::kVslider, removeMetadata(tree2str(hd(path))),
                    tree2double(c), tree2double(x), tree2double(y), tree2double(z));
            } else if (isSigHSlider(sig, path, c, x, y, z)) {
                fCompiler.fInputControls[sig] = inputControl(
                    fCompiler, sig, inputControl::kHslider, removeMetadata(tree2str(hd(path))),
                    tree2double(c), tree2double(x), tree2double(y), tree2double(z));
            } else if (isSigNumEntry(sig, path, c, x, y, z)) {
                fCompiler.fInputControls[sig] = inputControl(
                    fCompiler, sig, inputControl::kNumEntry, removeMetadata(tree2str(hd(path))),
                    tree2double(c), tree2double(x), tree2double(y), tree2double(z));
            } else if (isSigVBargraph(sig, path, x, y,
                                      z)) {  // z is the input signal to the bargraph
                fCompiler.fOutputControls[sig] = outputControl(
                    fCompiler, sig, outputControl::kVbargraph, removeMetadata(tree2str(hd(path))),
                    tree2double(x), tree2double(y));
                SignalVisitor::visit(sig);  // Visit children (i.e., the input signal z)
            } else if (isSigHBargraph(sig, path, x, y,
                                      z)) {  // z is the input signal to the bargraph
                fCompiler.fOutputControls[sig] = outputControl(
                    fCompiler, sig, outputControl::kHbargraph, removeMetadata(tree2str(hd(path))),
                    tree2double(x), tree2double(y));
                SignalVisitor::visit(sig);  // Visit children (i.e., the input signal z)
            } else {
                // Other cases
                SignalVisitor::visit(sig);
            }
        }
    };

    std::string fModuleName;    // Module name
    BlockInst*  fGlobalBlock;   // Holds global declarations shared across the generated DSP
    BlockInst*  fDeclareBlock;  // Holds variable declarations (delays, tables, controls)
    BlockInst*  fInitBlock;     // Code executed once during DSP initialization
    BlockInst*  fResetBlock;    // Code executed to reset DSP state (delays, tables, etc.)
    BlockInst*  fClearBlock;    // Code for clearing memory (if required by certain data structures)
    BlockInst*  fConstantsBlock;  // Code to keep constants computed at init time
    BlockInst*  fMetadataBlock;   // Code for building Metadata
    BlockInst*  fUIBlock;         // Code for building User Interface
    BlockInst*  fTablesBlock;     // Code for tables
    BlockInst*  fControlBlock;    // Code executed to update UI controls (sliders, buttons, etc.)
    BlockInst*  fSampleBlock;     // Main compute block executed at every sample frame

    std::stack<ValueInst*> fValueStack;  // Compiler's value stack used during signal traversal

    std::map<Tree, DelayLine> fDelays;  // Mapping between signals and their delay buffers
    std::map<Tree, TableData> fTables;  // Mapping between signals and their associated tables
                                        // std::map<Tree, TableData> fWaveforms;    // (Commented
                                        // out) Similar to tables but for waveforms
    std::map<Tree, inputControl>  fInputControls;   // UI input controls (buttons, sliders, etc.)
    std::map<Tree, outputControl> fOutputControls;  // UI output controls (bargraphs)
    int                           fNumInputs  = 0;  // Number of DSP input signals
    int                           fNumOutputs = 0;  // Number of DSP output signals
    Tree                          fOutputSig;       // The root signal tree to compile

    SignalFIRCompiler() = default;

    SignalFIRCompiler(int inputs, int outputs, Tree lsig, const std::string& module_name = "mydsp")
        : fModuleName(module_name), fNumInputs(inputs), fNumOutputs(outputs), fOutputSig(lsig)
    {
        // Allocate IR blocks
        fGlobalBlock    = IB::genBlockInst();
        fDeclareBlock   = IB::genBlockInst();
        fInitBlock      = IB::genBlockInst();
        fResetBlock     = IB::genBlockInst();
        fClearBlock     = IB::genBlockInst();
        fConstantsBlock = IB::genBlockInst();
        fMetadataBlock  = IB::genBlockInst();
        fUIBlock        = IB::genBlockInst();
        fTablesBlock    = IB::genBlockInst();
        fControlBlock   = IB::genBlockInst();
        fSampleBlock    = IB::genBlockInst();

        // Declare fIOTA
        fDeclareBlock->pushBackInst(IB::genDecStructVar("fIOTA", IB::genBasicTyped(Typed::kInt32)));
        // Initialize fIOTA
        fClearBlock->pushBackInst(IB::genStoreStructVar("fIOTA", IB::genInt32NumInst(0)));

        // Declare fSampleRate
        fDeclareBlock->pushBackInst(
            IB::genDecStructVar("fSampleRate", IB::genBasicTyped(Typed::kInt32)));

        // Set fSampleRate in `instanceConstants`
        fInitBlock->pushBackInst(
            IB::genStoreStructVar("fSampleRate", IB::genLoadFunArgsVar("sample_rate")));

        // Open UI box
        OpenboxInst::BoxType orient =
            static_cast<OpenboxInst::BoxType>(OpenboxInst::BoxType::kVerticalBox);
        fUIBlock->pushBackInst(IB::genOpenboxInst(fModuleName, orient));

        // Prepare the signal compilation context
        // The SignalBuilder populates:
        //  - Delay lines (fDelays)
        //  - Lookup tables (fTables)
        //  - UI controls (fInputControls, fOutputControls)
        SignalBuilder builder(*this);
        builder.visitRoot(fOutputSig);  // Traverse the DSP signal tree and collect resources
    }

    // Do not check already visited
    void self(Tree sig) override { visit(sig); }

    // Loads the special IOTA variable used for delay line access
    ValueInst* loadIOTA() { return IB::genLoadStructVar("fIOTA"); }

    /**
     * @brief Dispatch a write statement to the appropriate DSP code block.
     *
     * This method routes a generated `StatementInst` (such as an assignment or store)
     * to the correct code block (`fInitBlock`, `fControlBlock`, or `fSampleBlock`)
     * based on the variability (lifetime) of the signal associated with `x`.
     *
     * Variability levels:
     * - `kKonst`  → Initialization-time constants (executed once during DSP init).
     * - `kBlock`  → Control-rate computations (executed once per audio block).
     * - `kSamp`   → Sample-rate computations (executed once per sample).
     *
     * @param x   The signal tree whose variability determines the target block.
     * @param val The statement instruction to append to the appropriate block.
     *
     * @note If the variability is unknown or unsupported, the function triggers an assertion.
     */
    void writeStatement(Tree x, StatementInst* val)
    {
        // Everything in sample loop for now.
        fSampleBlock->pushBackInst(val);
        
        /*
        Type type = getCertifiedSigType(x);
        switch (type->variability()) {
            case kKonst:
                fInitBlock->pushBackInst(val);
                break;
            case kBlock:
                fControlBlock->pushBackInst(val);
                break;
            case kSamp:
                fSampleBlock->pushBackInst(val);
                break;
            default:
                faustassert(false);
                break;
        }
        */
    }

    /**
     * @brief Compiles the store to a delay line and the load of the delayed value.
     *
     * This function first compiles the store of the value (`v1`) to the delay line
     * associated with the signal tree `x` at the current time `fIOTA`.
     * Then, it compiles the load from the same delay line that was written `v2` samples ago
     * (i.e., at `fIOTA - v2.getInt()`).
     * The type of delay line (integer or REAL) is determined by checking `fDelays` maps.
     *
     * @param x The signal tree node representing the delay line's identity.
     * @param v1 The Node containing the current value to write to the delay line.
     * @param v2 The Node containing the delay amount in samples.
     * @return Node The value read from the delay line.
     */
    virtual ValueInst* writeReadDelay(Tree x, ValueInst* v1, ValueInst* v2)
    {
        faustassert(fDelays.count(x) > 0);
        // Store current value: delay[iota] = v1; in the correct block
        writeStatement(x, fDelays[x].write(loadIOTA(), v1));
        // Load delayed value: delay[iota - v2]
        return fDelays[x].read(IB::genSub(loadIOTA(), v2));
    }

    /**
     * @brief Compiles the load of a delayed value from a delay line.
     *
     * This function compiles the load from the delay line associated with signal tree `x`.
     * The value read is the one that was written `v2` samples ago (i.e., at `fIOTA - v2.getInt()`).
     * The type of delay line (integer or real) is determined by checking `fDelays` maps.
     *
     * @param x The signal tree node representing the delay line's identity.
     * @param v2 The Node containing the delay amount in samples.
     * @return Node The value read from the delay line.
     */
    virtual ValueInst* readDelay(Tree x, ValueInst* v2)
    {
        faustassert(fDelays.count(x) > 0);
        return fDelays[x].read(IB::genSub(loadIOTA(), v2));
    }

    /**
     * @brief Compiles the store of a value in a table.
     *
     * This function compiles the store of the value `v1` to the table associated
     * with the signal tree `x` at index `write_idx`
     *
     * @param x The signal tree node representing the delay line's identity.
     * @param write_idx The write index.
     * @param v1 The value.
     */
    virtual void writeTable(Tree x, ValueInst* write_idx, ValueInst* v1)
    {
        faustassert(fTables.count(x) > 0);
        writeStatement(x, fTables[x].write(write_idx, v1));
    }

    /**
     * @brief Compile the load of a value from a table.
     *
     * This function compiles the load of a value from a table
     * associated with the signal tree `x` at index `read_idx`.
     *
     * @param x The table tree.
     * @param read_idx The read index.
     * @return The read value.
     */
    virtual ValueInst* readTable(Tree x, ValueInst* read_idx)
    {
        faustassert(fTables.count(x) > 0);
        return fTables[x].read(read_idx);
    }

    /**
     * @brief Compiles a single output sample for a signal expression.
     *
     * This method clears the visited nodes map (`fVisited`) to ensure that recursive
     * or shared subtrees are properly compiled during this sample.
     * It then compiles the given expression tree by recursively interpreting it.
     * The result is retrieved from the value stack as an `ValueInst*`.
     *
     * @param exp The expression tree representing the signal to compute.
     * @return The compiled `ValueInst*`.
     */
    ValueInst* compileSample(Tree exp)
    {
        fVisited.clear();  // Clear visited for each top-level signal evaluation per sample
        self(exp);
        return popRes();
    }

    /**
     * @brief Compiles lookup tables used in the signal graph.
     *
     * This method compiles all lookup tables (both integer and real-valued)
     * that are defined in the signal expression. It ensures that any table-based
     * signals are filled with their corresponding precomputed values before
     * rendering begins.
     *
     * Implementation details:
     * - Enables the generator flag (`fVisitGen = true`) to allow recursive
     * evaluation of table-generating signals.
     * - Iterates over all integer tables (`fTables`) and computes their
     * contents using `compileSample`.
     * - Resets the generator flag (`fVisitGen = false`) once table initialization
     * is complete.
     *
     * This method must be called once before starting processing
     * to ensure that all table-based signals are correctly initialized.
     */
    void compileTables();

    /**
     * @brief Compile the DSP graph for all output signals.
     *
     * This method traverses the list of DSP output signals (`fOutputSig`),
     * compiles each one into a `ValueInst`, and emits the corresponding
     * store statements into the generated DSP code.
     *
     * Workflow:
     * 1. Clears the `fVisited` set to ensure each signal is compiled only once.
     * 2. Iterates through the list of output signals.
     * 3. For each signal:
     * - Invokes `self(out_sig)` to recursively compile the signal graph.
     * - Retrieves the resulting compiled value from the stack (`popRes()`).
     * - Generates a `StoreVar` instruction to write the computed value to
     * an output slot, applying the appropriate type casting if necessary.
     * 4. Appends the generated statement to the correct DSP block via `writeStatement`.
     *
     * @note Each output is stored in a stack variable named `"output"` with a unique ID.
     * @note This function is responsible for compiling only output signals; inputs and
     * intermediate nodes are compiled as part of the recursive traversal.
     */
    virtual void compile();

    void clear()
    {
        for (auto& it : fDelays) {
            it.second.reset();
        }
    }

    // ------------------------------------------------------------
    // Stack manipulation utilities.
    //
    // These methods provide a simple abstraction over the compiler's
    // internal value stack. The stack is used during signal compilation
    // to store intermediate `ValueInst*` results in a LIFO
    // (last-in, first-out) order.
    // ------------------------------------------------------------

    /**
     * @brief Pop the top value from the stack.
     *
     * Removes and returns the most recently pushed `ValueInst` from the stack.
     * This method asserts that the stack is not empty before popping.
     *
     * @return The top `ValueInst*` from the stack.
     */
    ValueInst* popRes()
    {
        faustassert(fValueStack.size() > 0);
        ValueInst* val = fValueStack.top();
        fValueStack.pop();
        return val;
    }

    /**
     * @brief Access the top value of the stack without removing it.
     *
     * Returns a pointer to the `ValueInst` at the top of the stack.
     * Unlike `popRes()`, this does not modify the stack.
     *
     * @return The top `ValueInst*` from the stack.
     */
    ValueInst* topRes() { return fValueStack.top(); }

    /**
     * @brief Push a value onto the stack.
     *
     * Adds a new `ValueInst` to the top of the stack.
     *
     * @param val The `ValueInst*` to push.
     */
    void pushRes(ValueInst* val)
    {
        // dump2FIR(val);
        fValueStack.push(val);
    }

    // Virtual methods for signal tree node types
    virtual void visit(Tree t) override;
    virtual void compileSigInt(Tree sig, int i_val);
    virtual void compileSigInt64(Tree sig, int64_t i64_val);
    virtual void compileSigReal(Tree sig, double r_val);
    virtual void compileSigInput(Tree sig, int i_val);
    virtual void compileSigOutput(Tree sig, int i_val, Tree x_tree);
    virtual void compileSigDelay1(Tree sig, Tree x_tree);
    virtual void compileSigDelay(Tree sig, Tree x_tree, Tree y_tree);
    virtual void compileSigSelect2(Tree sig, Tree sel, Tree x_tree, Tree y_tree);
    virtual void compileSigPrefix(Tree sig, Tree x_tree, Tree y_tree);
    virtual void compileSigBinOp(Tree sig, int opt_op, Tree x_tree, Tree y_tree);
    virtual void compileSigFConst(Tree sig, Tree type_tree, Tree name_tree, Tree file_tree);
    virtual void compileSigWRTbl(Tree sig, Tree size_tree, Tree gen_tree, Tree wi_tree,
                                 Tree ws_tree);
    virtual void compileSigRDTbl(Tree sig, Tree tbl_tree, Tree ri_tree);
    virtual void compileSigGen(Tree sig, Tree x_tree);
    virtual void compileSigWaveform(Tree sig);
    virtual void compileProjRec(Tree sig, int proj_idx, Tree rec_expr_tree, Tree rec_vars,
                                Tree rec_exprs);
    virtual void compileSigIntCast(Tree sig, Tree x_tree);
    virtual void compileSigBitCast(Tree sig, Tree x_tree);
    virtual void compileSigFloatCast(Tree sig, Tree x_tree);
    virtual void compileSigButton(Tree sig, Tree label_tree);
    virtual void compileSigCheckbox(Tree sig, Tree label_tree);
    virtual void compileSigVSlider(Tree sig, Tree label_tree, Tree c_tree, Tree x_tree, Tree y_tree,
                                   Tree z_tree);
    virtual void compileSigHSlider(Tree sig, Tree label_tree, Tree c_tree, Tree x_tree, Tree y_tree,
                                   Tree z_tree);
    virtual void compileSigNumEntry(Tree sig, Tree label_tree, Tree c_tree, Tree x_tree,
                                    Tree y_tree, Tree z_tree);
    virtual void compileSigVBargraph(Tree sig, Tree label_tree, Tree x_tree, Tree y_tree,
                                     Tree z_tree);
    virtual void compileSigHBargraph(Tree sig, Tree label_tree, Tree x_tree, Tree y_tree,
                                     Tree z_tree);
    virtual void compileSigSoundfile(Tree sig, Tree label_tree);
    virtual void compileSigSoundfileLength(Tree sig, Tree sf_tree, Tree x_tree);
    virtual void compileSigSoundfileRate(Tree sig, Tree sf_tree, Tree x_tree);
    virtual void compileSigSoundfileBuffer(Tree sig, Tree sf_tree, Tree x_tree, Tree y_tree,
                                           Tree z_tree);
    virtual void compileSigAttach(Tree sig, Tree x_tree, Tree y_tree);
    virtual void compileSigEnable(Tree sig, Tree x_tree, Tree y_tree);
    virtual void compileSigControl(Tree sig, Tree x_tree, Tree y_tree);
    virtual void compileXtended(Tree sig, xtended* xt);

    /**
     * @brief Generates a FIR DSP module instance.
     *
     * This function creates and configures a new `ModuleInst` representing
     * a complete DSP module for FIR signal processing. It sets up all the
     * required functions for:
     * - Input/output management
     * - Sample rate access
     * - Initialization and state reset
     * - DSP compute routine
     *
     * The generated module is fully self-contained and ready for integration
     * into the DSP runtime.
     *
     * @return A pointer to the newly created FIR module instance.
     */
    ModuleInst* genFIRModule(const std::string& obj = "");
};

/**
 * @brief A debugging extension of SignalFIRCompiler that prints each signal evaluation.
 *
 * The `SignalPrintFIRCompiler` class inherits from `SignalFIRCompiler` and overrides the
 * `visit(Tree sig)` method to add print statements. It prints the signal node
 * currently being evaluated (via `ppsig`) and the computed value at each step.
 *
 * This is useful for debugging signal evaluation and understanding how each
 * node in the Faust signal tree is processed by the interpreter.
 *
 */
/*
struct SignalPrintFIRCompiler : public SignalFIRCompiler {
    SignalPrintFIRCompiler() = default;

    SignalPrintFIRCompiler(Tree lsig) : SignalFIRCompiler(lsig)
    {
        std::cout << "======== Delays and tables ========" << std::endl;
        for (const auto& it : this->fDelays) {
            std::cout << "fDelays : " << ppsig(it.first, 16) << " " << it.second.size()
                      << std::endl;
        }
        for (const auto& it : this->fTables) {
            std::cout << "fTables : " << ppsig(it.first, 16) << " " << it.second.size()
                      << std::endl;
        }
        std::cout << "===================================" << std::endl;
    }

    virtual Node writeReadDelay(Tree x, Node& v1, Node& v2) override
    {
        std::cout << "========= writeReadDelay : " << ppsig(x, 8) << " =========" << std::endl;
        std::cout << "v1 : " << v1 << ", v2 : " << v2 << std::endl;
        return SignalFIRCompiler<REAL>::writeReadDelay(x, v1, v2);
    }

    virtual Node readDelay(Tree x, Node& v2) override
    {
        std::cout << "========= readDelay : " << ppsig(x, 8) << " =========" << std::endl;
        std::cout << "v2 : " << v2 << std::endl;
        return SignalFIRCompiler<REAL>::readDelay(x, v2);
    }

    virtual void visit(Tree sig) override
    {
        SignalFIRCompiler<REAL>::visit(sig);
        std::cout << "========= SIG : " << ppsig(sig, 40) << " =========" << std::endl;
        if (this->fValueStack.size() > 0) {
            Node res = this->fValueStack.top();
            int  int_val;
            if (isInt(res, &int_val)) {
                std::cout << "value Int : " << res.getInt() << std::endl;
            } else {
                std::cout << "value REAL : " << res.getDouble() << std::endl;
            }
        }
    }
};
*/
