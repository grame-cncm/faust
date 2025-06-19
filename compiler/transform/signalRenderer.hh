/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2024 GRAME, Centre National de Creation Musicale
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
#include "ppsig.hh"
#include "prim2.hh"
#include "sigIdentity.hh"
#include "signalVisitor.hh"
#include "sigtyperules.hh"

/**
 * @brief Class to interpret and render signals sample-by-sample in real-time.
 *
 * The `SignalRenderer` class is responsible for traversing the output signal trees,
 * evaluating each node recursively to compute the value of each output sample.
 * It handles delay lines, tables, recursive signals, and user controls, making it
 * the core component for real-time signal interpretation in the non-compilation backend.
 *
 * Key responsibilities:
 * - Recursively evaluate signal trees to compute sample values.
 * - Manage circular delay lines for recursive and time-based signal processing.
 * - Initialize lookup tables by precomputing their contents.
 * - Handle user interface controls (inputs and outputs) during rendering.
 *
 * Usage:
 * 1. Construct a `SignalRenderer` with the output signal tree.
 * 2. Use `initTables()` to precompute all tables before real-time processing.
 * 3. Call `compute(count, inputs, outputs)` each render block to produce audio samples.
 *
 * @tparam REAL The numeric type used for real-valued signals (e.g., float or double).
 */
template <class REAL>
struct SignalRenderer : public SignalVisitor {
    // Utility
    inline bool isZeroDelay(Tree sig)
    {
        Type     ty = getCertifiedSigType(sig);
        interval it = ty->getInterval();
        return (it.hi() == 0.0);
    }

    /**
     * @brief A circular buffer implementing delay lines for signals of a given type.
     *
     * This templated structure is used to store delayed versions of a signal
     * in a circular buffer for efficient sample-accurate delays. Delay lines
     * are essential for implementing feedback, recursive structures, and
     * time-based signal processing in audio DSP (e.g., echoes, filters).
     *
     * @tparam TYPE The numeric type stored in the buffer (e.g., int or float).
     */
    template <class TYPE>
    struct DelayedSig {
        std::vector<TYPE> fBuffer;

        // Default constructor
        DelayedSig() : fBuffer() {}
        DelayedSig(int size) { resize(size); }

        void resize(int size) { fBuffer.resize(size, TYPE(0)); }
        int  size() const { return int(fBuffer.size()); }  // Made const

        TYPE read(int index) { return fBuffer[index & (size() - 1)]; }
        void write(int index, TYPE value) { fBuffer[index & (size() - 1)] = value; }

        // Method to reset fBuffer content to 0
        void reset() { std::fill(fBuffer.begin(), fBuffer.end(), TYPE(0)); }
    };

    /**
     * @brief A table structure to store precomputed data for signal processing.
     *
     * This templated structure implements a buffer of a given type (e.g., int or float)
     * to store lookup tables or precomputed signal values.
     *
     * Each table is associated with a Faust signal generator (`fSigGen`),
     * which can be used to fill the table during initialization.
     *
     * @tparam TYPE The numeric type of the table elements (e.g., int or float).
     */
    template <class TYPE>
    struct TableData {
        std::vector<TYPE> fData;
        Tree              fSigGen = nullptr;

        TableData() : fData() {}
        TableData(Tree sig_gen, int size_val) { fSigGen = sig_gen, resize(size_val); }

        void resize(int size_val) { fData.resize(size_val, TYPE(0)); }
        int  size() const { return int(fData.size()); }  // Made const

        TYPE read(int index)
        {
            // Index is supposed to always be valid
            faustassert(index >= 0 && index < size());
            // Simple wrap-around for positive and negative indices
            return fData[index];
        }

        void write(int index, TYPE value)
        {
            // Index is supposed to always be valid
            faustassert(index >= 0 && index < size());
            fData[index] = value;
        }

        void fill(TYPE val) { std::fill(fData.begin(), fData.end(), val); }
    };

    /**
     * @brief Structure to represent user input controls.
     *
     * This structure defines the configuration for user interface controls
     * that allow the user to interact with signal parameters during runtime.
     * Typical examples include sliders, buttons, and numerical entries.
     *
     * Each control has an associated type, label, and value range.
     */
    struct inputControl {
        enum type { kButton, kCheckbutton, kVslider, kHslider, kNumEntry } fType;
        std::string fLabel;
        FAUSTFLOAT  fZone;
        double      fInit;
        double      fMin;
        double      fMax;
        double      fStep;
        inputControl() = default;
        inputControl(type type, const std::string& label, double init, double min, double max,
                     double step)
            : fType(type), fLabel(label), fInit(init), fMin(min), fMax(max), fStep(step)
        {
        }

        void init() { fZone = fInit; }
    };

    /**
     * @brief Structure to represent output controls (bargraphs).
     *
     * This structure defines the configuration for output controls that
     * visualize signal levels, such as vertical or horizontal bargraphs.
     */
    struct outputControl {
        enum type { kHbargraph, kVbargraph } fType;
        std::string fLabel;
        FAUSTFLOAT  fZone;
        double      fMin;
        double      fMax;
        outputControl() = default;
        outputControl(type type, const std::string& label, double min, double max)
            : fType(type), fLabel(label), fMin(min), fMax(max)
        {
        }

        void setValue(REAL val) { fZone = static_cast<FAUSTFLOAT>(val); }
    };

    /**
     * @brief Class to traverse and prepare signal trees for rendering.
     *
     * The `SignalBuilder` class is responsible for analyzing the output signal trees,
     * allocating all necessary resources such as delay lines, tables, and input/output controls,
     * and performing preliminary setup before rendering. It ensures that each signal
     * has the correct data structures allocated for real-time sample interpretation.
     *
     * Key responsibilities:
     * - Allocates delay lines for signals that require delays or recursive definitions.
     * - Allocates tables for signals that generate lookup data.
     * - Registers input and output controls such as sliders and bargraphs.
     *
     * @tparam REAL The numeric type used for real-valued signals (e.g., float or double).
     */
    struct SignalBuilder : public SignalVisitor {
        std::map<Tree, DelayedSig<int>>&  fIntDelays;
        std::map<Tree, DelayedSig<REAL>>& fRealDelays;
        std::map<Tree, TableData<int>>&   fIntTables;
        std::map<Tree, TableData<REAL>>&  fRealTables;
        std::map<Tree, inputControl>&     fInputControls;
        std::map<Tree, outputControl>&    fOutputControls;
        int&                              fNumInputs;

        /**
         * @brief Allocates or resizes a delay line for a given signal. All delay lines have a
         * power-of-two size and the IOTA based global index access.
         *
         * This method is responsible for ensuring that a delay line (either integer or REAL-valued)
         * exists and is of sufficient size for the signal `x`. The maximum delay amount is
         * determined by the `y_delay` tree, which represents the signal controlling
         * the delay length.
         *
         * The nature of the signal `x` (integer or real) determines whether an `fIntDelays`
         * or `fRealDelays` entry is used. The size of the delay line buffer is calculated
         * using `pow2limit(max_delay + 1)` to ensure it's a power of two, which is
         * efficient for circular buffer implementations using bitwise AND for indexing.
         *
         * If a delay line for `x` already exists, its size is compared with the newly
         * required size (`N`), and it's resized if `N` is larger. If it doesn't exist,
         * a new `DelayedSig` buffer is created and stored in the appropriate map
         * (`fIntDelays` or `fRealDelays`) with `x` as the key.
         *
         * @param x The signal tree node that identifies the signal requiring the delay line.
         * The type of this signal (int or real) determines the type of the delay buffer.
         * @param y_delay The signal tree node representing the delay amount.
         * The interval analysis of this signal (`it.hi()`) provides the
         * maximum required delay length.
         */
        void allocateDelayLine(Tree x, int delay) { allocateDelayLineAux(x, delay); }

        void allocateDelayLine(Tree x, Tree y)
        {
            Type     ty = getCertifiedSigType(y);
            interval it = ty->getInterval();
            allocateDelayLineAux(x, it.hi());
        }

        void allocateDelayLineAux(Tree x, int delay)
        {
            int nature = getCertifiedSigType(x)->nature();  // Nature of the signal being delayed
            int N      = pow2limit(delay + 1);              // Max delay rounded up to power of 2

            if (nature == kInt) {
                if (fIntDelays.find(x) == fIntDelays.end()) {
                    fIntDelays[x] = DelayedSig<int>(N);
                    /*
                    if (global::isDebug("SIG_RENDERER")) {
                        std::cout << "allocateDelayLineAux NEW INT " << ppsig(x, 8) << std::endl;
                    }
                    */
                } else {
                    fIntDelays[x].resize(std::max(int(fIntDelays[x].size()), N));
                    /*
                    if (global::isDebug("SIG_RENDERER")) {
                        std::cout << "allocateDelayLineAux RESIZE INT " << ppsig(x, 8) << std::endl;
                    }
                    */
                }
            } else {  // kReal or other numeric types default to REAL
                if (fRealDelays.find(x) == fRealDelays.end()) {
                    fRealDelays[x] = DelayedSig<REAL>(N);
                    /*
                    if (global::isDebug("SIG_RENDERER")) {
                        td::cout << "allocateDelayLineAux NEW REAL " << ppsig(x, 8) << std::endl;
                    }
                    */
                } else {
                    fRealDelays[x].resize(std::max(int(fRealDelays[x].size()), N));
                    /*
                    if (global::isDebug("SIG_RENDERER")) {
                        std::cout << "allocateDelayLineAux RESIZE REAL " << ppsig(x, 8) <<
                    std::endl;
                    }
                    */
                }
            }
        }

        SignalBuilder(std::map<Tree, DelayedSig<int>>&  int_delays,
                      std::map<Tree, DelayedSig<REAL>>& real_delays,
                      std::map<Tree, TableData<int>>&   int_tables,
                      std::map<Tree, TableData<REAL>>&  real_tables,
                      std::map<Tree, inputControl>&     inputs_control,
                      std::map<Tree, outputControl>& outputs_control, int& inputs)
            : fIntDelays(int_delays),
              fRealDelays(real_delays),
              fIntTables(int_tables),
              fRealTables(real_tables),
              fInputControls(inputs_control),
              fOutputControls(outputs_control),
              fNumInputs(inputs)
        {
            fVisitGen = true;
        }

        void visit(Tree sig) override
        {
            Tree path, c, x, y, z;
            Tree size_tree, gen_tree, wi_tree, ws_tree;
            Tree rec_expr_tree, rec_vars, rec_exprs;  // For isProj/isRec
            int  proj_idx_val;

            if (int input_idx; isSigInput(sig, &input_idx)) {
                fNumInputs++;
            } else if (isSigDelay1(sig, x)) {
                Tree x_ck, y_ck;
                if (isSigClocked(x, x_ck, y_ck)) {
                    x = y_ck;
                }
                allocateDelayLine(x, 1);  // Delay of 1 sample
                SignalVisitor::visit(sig);
            } else if (isSigDelay(sig, x, y)) {
                Tree x_ck, y_ck;
                if (isSigClocked(x, x_ck, y_ck)) {
                    x = y_ck;
                }
                if (isSigClocked(y, x_ck, y_ck)) {
                    y = y_ck;
                }
                allocateDelayLine(x, y);  // y is the delay amount signal
                SignalVisitor::visit(sig);
            } else if (isProj(sig, &proj_idx_val, rec_expr_tree) &&
                       isRec(rec_expr_tree, rec_vars, rec_exprs)) {
                // This projection 'sig' represents a recursive variable's state.
                // It implicitly requires a 1-sample delay buffer.
                allocateDelayLine(sig, 1);
                SignalVisitor::visit(sig);
            } else if (isSigWRTbl(sig, size_tree, gen_tree, wi_tree, ws_tree)) {
                int size_val = 0;
                isSigInt(size_tree, &size_val);
                Type content_type = getCertifiedSigType(gen_tree);
                if (content_type->nature() == kInt) {
                    fIntTables[sig] = TableData<int>(gen_tree, size_val);
                } else {
                    fRealTables[sig] = TableData<REAL>(gen_tree, size_val);
                }
                SignalVisitor::visit(sig);
            } else if (isSigButton(sig, path)) {  // UI
                fInputControls[sig] = inputControl(inputControl::kButton,
                                                   removeMetadata(tree2str(hd(path))), 0, 0, 1, 1);
            } else if (isSigCheckbox(sig, path)) {
                fInputControls[sig] = inputControl(inputControl::kCheckbutton,
                                                   removeMetadata(tree2str(hd(path))), 0, 0, 1, 1);
            } else if (isSigVSlider(sig, path, c, x, y, z)) {
                fInputControls[sig] =
                    inputControl(inputControl::kVslider, removeMetadata(tree2str(hd(path))),
                                 tree2double(c), tree2double(x), tree2double(y), tree2double(z));
            } else if (isSigHSlider(sig, path, c, x, y, z)) {
                fInputControls[sig] =
                    inputControl(inputControl::kHslider, removeMetadata(tree2str(hd(path))),
                                 tree2double(c), tree2double(x), tree2double(y), tree2double(z));
            } else if (isSigNumEntry(sig, path, c, x, y, z)) {
                fInputControls[sig] =
                    inputControl(inputControl::kNumEntry, removeMetadata(tree2str(hd(path))),
                                 tree2double(c), tree2double(x), tree2double(y), tree2double(z));
            } else if (isSigVBargraph(sig, path, x, y,
                                      z)) {  // z is the input signal to the bargraph
                fOutputControls[sig] =
                    outputControl(outputControl::kVbargraph, removeMetadata(tree2str(hd(path))),
                                  tree2double(x), tree2double(y));
                SignalVisitor::visit(sig);  // Visit children (i.e., the input signal z)
            } else if (isSigHBargraph(sig, path, x, y,
                                      z)) {  // z is the input signal to the bargraph
                fOutputControls[sig] =
                    outputControl(outputControl::kHbargraph, removeMetadata(tree2str(hd(path))),
                                  tree2double(x), tree2double(y));
                SignalVisitor::visit(sig);  // Visit children (i.e., the input signal z)
            } else {
                // Other cases
                SignalVisitor::visit(sig);
            }
        }
    };

   public:
    SignalRenderer() = default;
    SignalRenderer(Tree lsig) : fOutputSig(lsig)
    {
        // Build delay lines and recursions, tables and inputs/outputs control
        SignalBuilder builder(fIntDelays, fRealDelays, fIntTables, fRealTables, fInputControls,
                              fOutputControls, fNumInputs);
        builder.visitRoot(fOutputSig);
    }

    // Do not check already visited
    void self(Tree sig) override { visit(sig); }

    /**
     * @brief Writes a value to a delay line and reads a delayed value.
     *
     * This function first writes the current input value (`v1`) to the delay line
     * associated with the signal tree `x` at the current time `fIOTA`.
     * Then, it reads a value from the same delay line that was written `v2` samples ago
     * (i.e., at `fIOTA - v2.getInt()`).
     * The type of delay line (integer or REAL) is determined by checking `fIntDelays` and
     * `fRealDelays` maps.
     *
     * @param x The signal tree node representing the delay line's identity.
     * @param v1 The Node containing the current value to write to the delay line.
     * @param v2 The Node containing the delay amount in samples.
     * @return Node The value read from the delay line. Returns Node(0) if delay line not found
     * (should not happen if allocated).
     */
    virtual Node writeReadDelay(Tree x, Node& v1, Node& v2)
    {
        if (fIntDelays.count(x) > 0) {
            fIntDelays[x].write(fIOTA, v1.getInt());
            return Node(fIntDelays[x].read(fIOTA - v2.getInt()));
        } else if (fRealDelays.count(x) > 0) {
            fRealDelays[x].write(fIOTA, v1.getDouble());
            return Node(fRealDelays[x].read(fIOTA - v2.getInt()));
        } else {
            faustassert(false);  // Should have been allocated by SignalBuilder
            return Node(0);
        }
    }

    /**
     * @brief Reads a delayed value from a delay line.
     *
     * This function reads a value from the delay line associated with signal tree `x`.
     * The value read is the one that was written `v2` samples ago (i.e., at `fIOTA - v2.getInt()`).
     * The type of delay line (integer or REAL) is determined by checking `fIntDelays` and
     * `fRealDelays` maps.
     *
     * @param x The signal tree node representing the delay line's identity.
     * @param v2 The Node containing the delay amount in samples.
     * @return Node The value read from the delay line. Returns Node(0) if delay line not found
     * (should not happen if allocated).
     */
    virtual Node readDelay(Tree x, Node& v2)
    {
        if (fIntDelays.count(x) > 0) {
            return Node(fIntDelays[x].read(fIOTA - v2.getInt()));
        } else if (fRealDelays.count(x) > 0) {
            return Node(fRealDelays[x].read(fIOTA - v2.getInt()));
        } else {
            faustassert(false);  // Should have been allocated by SignalBuilder
            return Node(0);
        }
    }

    /**
     * @brief Computes a single output sample for an integer-valued signal expression.
     *
     * This method clears the visited nodes map (`fVisited`) to ensure that recursive
     * or shared subtrees are properly evaluated during this sample.
     * It then evaluates the given expression tree by recursively interpreting it.
     * The result is retrieved from the value stack as an integer.
     * Finally, the global sample index counter (`fIOTA`) is incremented to advance
     * the circular buffer indexing and waveform rendering state.
     *
     * @param exp The expression tree representing the signal to compute.
     * @return The computed integer sample value.
     */
    int computeIntSample(Tree exp)
    {
        fVisited.clear();  // Clear visited for each top-level signal evaluation per sample
        self(exp);
        Node res = popRes();
        // Increment the delay lines and waveforms shared index
        fIOTA++;
        return res.getInt();
    }

    /**
     * @brief Computes a single output sample for a real-valued signal expression.
     *
     * This method performs the same logic as `computeIntSample`, but returns
     * a floating-point value instead.
     *
     * @param exp The expression tree representing the signal to compute.
     * @return The computed real-valued sample.
     */
    double computeRealSample(Tree exp)
    {
        fVisited.clear();  // Clear visited for each top-level signal evaluation per sample
        self(exp);
        Node res = popRes();
        // Increment the delay lines and waveforms shared index
        fIOTA++;
        return res.getDouble();
    }

    /**
     * @brief Initializes lookup tables used in the signal graph.
     *
     * This method precomputes all lookup tables (both integer and real-valued)
     * that are defined in the signal expression. It ensures that any table-based
     * signals (e.g., wavetables, precomputed envelopes) are filled with their
     * corresponding precomputed values before real-time rendering begins.
     *
     * Implementation details:
     * - Enables the generator flag (`fVisitGen = true`) to allow recursive
     *   evaluation of table-generating signals.
     * - Iterates over all integer tables (`fIntTables`) and computes their
     *   contents using `computeIntSample`.
     * - Iterates over all real-valued tables (`fRealTables`) and computes their
     *   contents using `computeRealSample`.
     * - Resets the generator flag (`fVisitGen = false`) once table initialization
     *   is complete.
     *
     * This method must be called once before starting real-time processing
     * to ensure that all table-based signals are correctly initialized.
     */
    void initTables()
    {
        // So that sigGen are properly visited
        fVisitGen = true;

        // Generate integer tables
        for (auto& it : fIntTables) {
            fIOTA = 0;
            for (int index = 0; index < it.second.size(); index++) {
                it.second.write(index, computeIntSample(it.second.fSigGen));
            }
        }

        // Generate REAL tables
        for (auto& it : fRealTables) {
            fIOTA = 0;
            for (int index = 0; index < it.second.size(); index++) {
                it.second.write(index, computeRealSample(it.second.fSigGen));
            }
        }

        fVisitGen = false;
    }

    std::stack<Node>                 fValueStack;      // Interpreter stack of values
    std::map<Tree, DelayedSig<int>>  fIntDelays;       // Delay lines for integer signals
    std::map<Tree, DelayedSig<REAL>> fRealDelays;      // Delay lines for REAL signals
    std::map<Tree, TableData<int>>   fIntTables;       // Table for integer signals
    std::map<Tree, TableData<REAL>>  fRealTables;      // Table for REAL signals
    std::map<Tree, inputControl>     fInputControls;   // Inputs controls (sliders, nentry, button)
    std::map<Tree, outputControl>    fOutputControls;  // Output controls (bargraph)
    int                              fNumInputs  = 0;
    int                              fSampleRate = -1;
    int                              fSample     = 0;  // Current sample in a buffer
    int                              fIOTA       = 0;  // Used as index counter for all delay lines
    FAUSTFLOAT**                     fInputs     = nullptr;  // Set at each call of 'compute'
    Tree                             fOutputSig;

    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);

    Node popRes()
    {
        faustassert(fValueStack.size() > 0);
        Node val = fValueStack.top();
        fValueStack.pop();
        return val;
    }

    Node topRes() { return fValueStack.top(); }

    void pushRes(Node val) { fValueStack.push(val); }

    virtual void visit(Tree t) override;
};

/**
 * @brief A debugging extension of SignalRenderer that prints each signal evaluation.
 *
 * The `SignalPrintRenderer` class inherits from `SignalRenderer` and overrides the
 * `visit(Tree sig)` method to add print statements. It prints the signal node
 * currently being evaluated (via `ppsig`) and the computed value at each step.
 *
 * This is useful for debugging signal evaluation and understanding how each
 * node in the Faust signal tree is processed by the interpreter.
 *
 * @tparam REAL The numeric type used for real-valued signals (e.g., float or double).
 */
template <class REAL>
struct SignalPrintRenderer : public SignalRenderer<REAL> {
    SignalPrintRenderer() = default;

    SignalPrintRenderer(Tree lsig) : SignalRenderer<REAL>(lsig)
    {
        std::cout << "======== Delays and tables ========" << std::endl;
        for (const auto& it : this->fIntDelays) {
            std::cout << "fIntDelays : " << ppsig(it.first, 16) << " " << it.second.size()
                      << std::endl;
        }
        for (const auto& it : this->fRealDelays) {
            std::cout << "fRealDelays : " << ppsig(it.first, 16) << " " << it.second.size()
                      << std::endl;
        }
        for (const auto& it : this->fIntTables) {
            std::cout << "fIntTables : " << ppsig(it.first, 16) << " " << it.second.size()
                      << std::endl;
        }
        for (const auto& it : this->fRealTables) {
            std::cout << "fRealTables : " << ppsig(it.first, 16) << " " << it.second.size()
                      << std::endl;
        }
        std::cout << "===================================" << std::endl;
    }

    virtual Node writeReadDelay(Tree x, Node& v1, Node& v2) override
    {
        std::cout << "========= writeReadDelay : " << ppsig(x, 8) << " =========" << std::endl;
        std::cout << "v1 : " << v1 << ", v2 : " << v2 << std::endl;
        return SignalRenderer<REAL>::writeReadDelay(x, v1, v2);
    }

    virtual Node readDelay(Tree x, Node& v2) override
    {
        std::cout << "========= readDelay : " << ppsig(x, 8) << " =========" << std::endl;
        std::cout << "v2 : " << v2 << std::endl;
        return SignalRenderer<REAL>::readDelay(x, v2);
    }

    virtual void visit(Tree sig) override
    {
        SignalRenderer<REAL>::visit(sig);
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

/**
 * @brief The `signal_dsp` class is used to render signals.
 */
struct signal_dsp : public dsp {
    virtual ~signal_dsp() {}
};

/**
 * @brief Concrete DSP implementation for rendering interpreted signals.
 *
 * The `signal_dsp_aux` class is a specialized implementation of `signal_dsp`
 * that renders signals interpreted at runtime. It integrates the `SignalRenderer`
 * to compute sample values using recursive traversal of the output signal tree.
 *
 * Key responsibilities:
 * - Manages a `SignalRenderer` that performs the core sample-by-sample interpretation.
 * - Implements the standard Faust DSP interface (`dsp`), including:
 *   - User interface construction (`buildUserInterface`)
 *   - Lifecycle management (initialization, reset, clear)
 *   - Sample rendering (`compute`)
 * - Supports real-time control via dynamic input controls (sliders, buttons)
 *   and output controls (bargraphs).
 *
 * Usage:
 * - Instantiated by the `signal_dsp_factory` based on compile options.
 * - Used by Faust applications to render interpreted signals in real-time
 *   without requiring a separate compilation step.
 *
 * @tparam REAL The numeric type used for real-valued signals (e.g., float or double).
 */
template <class REAL>
struct signal_dsp_aux : public signal_dsp {
    SignalRenderer<REAL> fRenderer;
    // SignalPrintRenderer<REAL> fRenderer;

    signal_dsp_aux(Tree lsig) : fRenderer(lsig) {}
    virtual ~signal_dsp_aux() {}

    virtual int getNumInputs();

    virtual int getNumOutputs();

    virtual int getSampleRate() { return fRenderer.fSampleRate; }

    void buildUserInterface(UI* ui_interface)
    {
        ui_interface->openVerticalBox("SignalDSP");
        for (auto& it : fRenderer.fInputControls) {
            switch (it.second.fType) {
                case SignalRenderer<REAL>::inputControl::kButton:
                    ui_interface->addButton(it.second.fLabel.c_str(), &it.second.fZone);
                    break;
                case SignalRenderer<REAL>::inputControl::kCheckbutton:
                    ui_interface->addCheckButton(it.second.fLabel.c_str(), &it.second.fZone);
                    break;
                case SignalRenderer<REAL>::inputControl::kVslider:
                    ui_interface->addVerticalSlider(it.second.fLabel.c_str(), &it.second.fZone,
                                                    it.second.fInit, it.second.fMin, it.second.fMax,
                                                    it.second.fStep);
                    break;
                case SignalRenderer<REAL>::inputControl::kHslider:
                    ui_interface->addHorizontalSlider(it.second.fLabel.c_str(), &it.second.fZone,
                                                      it.second.fInit, it.second.fMin,
                                                      it.second.fMax, it.second.fStep);
                    break;
                case SignalRenderer<REAL>::inputControl::kNumEntry:
                    ui_interface->addNumEntry(it.second.fLabel.c_str(), &it.second.fZone,
                                              it.second.fInit, it.second.fMin, it.second.fMax,
                                              it.second.fStep);
                    break;
            }
        }
        for (auto& it : fRenderer.fOutputControls) {
            switch (it.second.fType) {
                case SignalRenderer<REAL>::outputControl::kVbargraph:
                    ui_interface->addVerticalBargraph(it.second.fLabel.c_str(), &it.second.fZone,
                                                      it.second.fMin, it.second.fMax);
                    break;
                case SignalRenderer<REAL>::outputControl::kHbargraph:
                    ui_interface->addHorizontalBargraph(it.second.fLabel.c_str(), &it.second.fZone,
                                                        it.second.fMin, it.second.fMax);
                    break;
            }
        }
        ui_interface->closeBox();
    }

    virtual void instanceConstants(int sample_rate) {}

    virtual void instanceResetUserInterface()
    {
        for (auto& it : fRenderer.fInputControls) {
            it.second.init();
        }
    }

    // Tables for rdtable and rwtable are generated once at init time
    virtual void classInit(int sample_rate) { fRenderer.initTables(); }

    virtual void init(int sample_rate)
    {
        // classInit(sample_rate);  // Typically for static tables (TODO: handling by factory ?)
        instanceInit(sample_rate);
    }

    virtual void instanceInit(int sample_rate)
    {
        fRenderer.fSampleRate = sample_rate;
        classInit(sample_rate);  // Typically for static tables (TODO: handling by factory ?)
        instanceConstants(sample_rate);
        instanceResetUserInterface();
        instanceClear();
    }

    virtual void instanceClear()
    {
        for (auto& it : fRenderer.fIntDelays) {
            it.second.reset();
        }
        for (auto& it : fRenderer.fRealDelays) {
            it.second.reset();
        }
        fRenderer.fIOTA = 0;
    }

    virtual void metadata(Meta* meta) {}

    virtual signal_dsp_aux* clone() { return new signal_dsp_aux<REAL>(fRenderer.fOutputSig); }

    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
};

// External API

/**
 * @brief Factory class to create and manage `signal_dsp` instances for interpreted signals.
 *
 * The `signal_dsp_factory` encapsulates the output signal tree and any associated
 * compile options needed to create DSP instances. It performs validation of the
 * signal graph to ensure that no unsupported features (e.g., foreign functions or variables)
 * are used in interpreted mode.
 *
 * Responsibilities:
 * - Validates that the signal tree can be interpreted safely.
 * - Stores compile options (e.g., `-double` for double-precision support).
 * - Creates instances of `signal_dsp` (using `signal_dsp_aux`) with the appropriate
 *   numeric type based on compile options.
 * - Integrates seamlessly with the broader Faust DSP ecosystem by implementing
 *   the same factory interface as other backends.
 *
 * Usage:
 * - Construct a `signal_dsp_factory` with the output signal tree and command-line arguments.
 * - Use `createDSPInstance()` to instantiate one or more DSP objects.
 * - Manage lifecycle via `deleteSignalDSPFactory` (for global context management).
 */
struct signal_dsp_factory : public dsp_factory {
    /**
     * @brief Internal class to check for unsupported features in interpreted mode.
     *
     * Traverses the signal tree and throws exceptions if unsupported constructs
     * (e.g., foreign functions or variables) are detected.
     */
    struct SignalChecker : public SignalVisitor {
        void visit(Tree sig) override
        {
            Tree ff, largs, name, type, file;

            if (isSigFFun(sig, ff, largs)) {
                std::stringstream error;
                error << "ERROR : accessing foreign function  '" << ffname(ff) << "'"
                      << " is not allowed in this compilation mode" << std::endl;
                throw faustexception(error.str());
            } else if (isSigFVar(sig, type, name, file)) {
                std::stringstream error;
                error << "ERROR : accessing foreign variable '" << tree2str(name) << "'"
                      << " is not allowed in this compilation mode" << std::endl;
                throw faustexception(error.str());
            } else if (isSigFConst(sig, type, name, file)) {
                if (std::string(tree2str(name)) != "fSamplingFreq") {
                    std::stringstream error;
                    error << "ERROR : accessing foreign constant '" << tree2str(name) << "'"
                          << " is not allowed in this compilation mode" << std::endl;
                    throw faustexception(error.str());
                }
            } else {
                SignalVisitor::visit(sig);
            }
        }
    };

    Tree        fOutputSig;
    std::string fCompileOptions;

    bool hasCompileOption(const std::string& option)
    {
        std::istringstream iss(fCompileOptions);
        std::string        token;
        while (std::getline(iss, token, ' ')) {
            if (token == option) {
                return true;
            }
        }
        return false;
    }

    signal_dsp_factory(Tree lsig, int argc, const char* argv[]) : fOutputSig(lsig)
    {
        SignalChecker checker;
        checker.visitRoot(fOutputSig);

        std::ostringstream oss;
        // Correctly copy argv to oss
        for (int i = 0; i < argc; ++i) {
            oss << argv[i] << (i == argc - 1 ? "" : " ");
        }
        fCompileOptions = oss.str();
    }
    virtual ~signal_dsp_factory() {}

    /* Return factory name */
    virtual std::string getName() { return "SignalFactory"; };

    /* Return factory SHA key */
    virtual std::string getSHAKey() { return ""; };

    /* Return factory expanded DSP code */
    virtual std::string getDSPCode() { return ""; };

    /* Return factory compile options */
    virtual std::string getCompileOptions() { return fCompileOptions; };

    /* Get the Faust DSP factory list of library dependancies */
    virtual std::vector<std::string> getLibraryList() { return {}; }

    /* Get the list of all used includes */
    virtual std::vector<std::string> getIncludePathnames() { return {}; }

    /* Get warning messages list for a given compilation */
    virtual std::vector<std::string> getWarningMessages() { return {}; }

    /* Create a new DSP instance, to be deleted with C++ 'delete' */
    virtual signal_dsp* createDSPInstance()
    {
        if (hasCompileOption("-double")) {
            // std::cerr << "createDSPInstance -double\n";
            // std::cerr << "sizeof(FAUSTFLOAT) " << sizeof(FAUSTFLOAT) << "\n";
            return new signal_dsp_aux<double>(fOutputSig);
        } else {
            // std::cerr << "createDSPInstance -single\n";
            // std::cerr << "sizeof(FAUSTFLOAT) " << sizeof(FAUSTFLOAT) << "\n";
            //  Default to float if -double is not specified or FAUSTFLOAT is float
            //  The #ifndef FAUSTFLOAT block defaults to double, so this logic might need alignment
            //  For now, strictly follow -double flag. If not present, use float.
            return new signal_dsp_aux<float>(fOutputSig);
        }
    }

    /* Static tables initialization, possibly implemened in sub-classes*/
    virtual void classInit(int sample_rate) {};  // This is typically for global/static tables

    /* Set a custom memory manager to be used when creating instances */
    virtual void setMemoryManager(dsp_memory_manager* manager) {}

    /* Return the currently set custom memory manager */
    virtual dsp_memory_manager* getMemoryManager() { return nullptr; }
};
