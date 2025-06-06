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

//-------------------------SignalRenderer-------------------------------
// Render a list of signals.
//----------------------------------------------------------------------

/**
 * @brief Define a renderer to interpret a signal.
 *
 * @tparam REAL
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
     * @brief A buffer of a given type to implement delay lines.
     *
     * @tparam TYPE
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
     * @brief A buffer of a given type to implement tables.
     *
     * @tparam TYPE
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

    // Keep input controls
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
    // Keep output controls
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
     * @brief Build delay lines (for real ones and recursions) and tables
     * and keep input and output controls.
     *
     * @tparam REAL
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
                } else {
                    fIntDelays[x].resize(std::max(int(fIntDelays[x].size()), N));
                }
            } else {  // kReal or other numeric types default to REAL
                if (fRealDelays.find(x) == fRealDelays.end()) {
                    fRealDelays[x] = DelayedSig<REAL>(N);
                } else {
                    fRealDelays[x].resize(std::max(int(fRealDelays[x].size()), N));
                }
            }
        }

        SignalBuilder(std::map<Tree, DelayedSig<int>>&  int_delays,
                      std::map<Tree, DelayedSig<REAL>>& real_delays,
                      std::map<Tree, TableData<int>>&   int_tables,
                      std::map<Tree, TableData<REAL>>& real_tables,
                      std::map<Tree, inputControl>&  inputs_control,
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
            Tree rec_expr_tree, rec_var_list, rec_expr_list;  // For isProj/isRec
            int  proj_idx_val;

            if (int input_idx; isSigInput(sig, &input_idx)) {
                fNumInputs++;
            } else if (isSigDelay1(sig, x)) {
                allocateDelayLine(x, 1);  // Delay of 1 sample
                SignalVisitor::visit(sig);
            } else if (isSigDelay(sig, x, y)) {
                allocateDelayLine(x, y);  // y is the delay amount signal
                SignalVisitor::visit(sig);
            } else if (isProj(sig, &proj_idx_val, rec_expr_tree) &&
                       isRec(rec_expr_tree, rec_var_list, rec_expr_list)) {
                // This projection 'sig' represents a recursive variable's state.
                // It implicitly requires a 1-sample delay buffer.
                // The delay amount for recursion is 1 sample.
                allocateDelayLine(sig, 1);  // TO CHECK
                SignalVisitor::visit(sig);  // Continue visiting children of the projection
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
        SignalBuilder builder(fIntDelays, fRealDelays, fIntTables, fRealTables,
                              fInputControls, fOutputControls, fNumInputs);
        builder.visitRoot(fOutputSig);
    }

    // Do not check already visited
    void self(Tree sig) override
    {
        visit(sig);
    }

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
    Node writeReadDelay(Tree x, Node& v1, Node& v2)
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
    Node readDelay(Tree x, Node& v2)
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

    int computeIntSample(Tree exp)
    {
        fVisited.clear();  // Clear visited for each top-level signal evaluation per sample
        self(exp);
        Node res = popRes();
        // Increment the delay lines and waveforms shared index
        fIOTA++;
        return res.getInt();
    }

    double computeRealSample(Tree exp)
    {
        fVisited.clear();  // Clear visited for each top-level signal evaluation per sample
        self(exp);
        Node res = popRes();
        // Increment the delay lines and waveforms shared index
        fIOTA++;
        return res.getDouble();
    }

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

    void pushRes(Node val)
    {
        fValueStack.push(val);
    }

    virtual void visit(Tree t) override;
};

/**
 * @brief The signal_dsp class is used to render signals.
 */

struct signal_dsp : public dsp {
    virtual ~signal_dsp() {}
};

template <class REAL>
struct signal_dsp_aux : public signal_dsp {
    SignalRenderer<REAL> fRenderer;
 
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

struct signal_dsp_factory : public dsp_factory {
    // Check that signal can be interpreted
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
