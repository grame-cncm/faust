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

#include <cstdlib>
#include <fstream>
#include <iterator>
#include <map>
#include <stack>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
// #define FAUSTFLOAT float
#endif

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"

#include "Text.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "signalVisitor.hh"
#include "sigtyperules.hh"

//-------------------------SignalRenderer-------------------------------
// Render a list of signals.
//----------------------------------------------------------------------

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
    int  size() { return int(fBuffer.size()); }

    TYPE read(int index) { return fBuffer[index & (size() - 1)]; }
    void write(int index, TYPE value) { fBuffer[index & (size() - 1)] = value; }

    // Method to reset fBuffer content to 0
    void reset() { std::fill(fBuffer.begin(), fBuffer.end(), TYPE(0)); }
};

inline bool isZeroDelay(Tree sig)
{
    Type     ty = getCertifiedSigType(sig);
    interval it = ty->getInterval();
    return (it.hi() == 0.0);
}

/**
 * @brief Define a renderer to render a signal.
 *
 * @tparam REAL
 */
template <class REAL>
struct SignalRenderer : public SignalVisitor {
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
    };

    /**
     * @brief Build delay lines.
     *
     * @tparam REAL
     */
    struct SignalBuilder : public SignalVisitor {
        std::map<Tree, DelayedSig<int>>&  fIntDelays;
        std::map<Tree, DelayedSig<REAL>>& fRealDelays;
        std::map<Tree, inputControl>&     fInputControls;
        std::map<Tree, outputControl>&    fOutputControls;
        int&                              fNumInputs;

        void allocateDelayLine(Tree x, Tree y)
        {
            Type     ty     = getCertifiedSigType(y);
            int      nature = getCertifiedSigType(x)->nature();
            interval it     = ty->getInterval();
            int      N      = pow2limit(it.hi() + 1);

            if (nature == kInt) {
                if (fIntDelays.find(x) == fIntDelays.end()) {
                    fIntDelays[x] = DelayedSig<int>(N);
                } else {
                    // Update existing DelayedSig
                    fIntDelays[x].resize(std::max(int(fIntDelays[x].size()), N));
                }
            } else {
                if (fRealDelays.find(x) == fRealDelays.end()) {
                    fRealDelays[x] = DelayedSig<REAL>(N);
                } else {
                    // Update existing DelayedSig
                    fRealDelays[x].resize(std::max(int(fRealDelays[x].size()), N));
                }
            }
        }

        SignalBuilder(std::map<Tree, DelayedSig<int>>&  int_delays,
                      std::map<Tree, DelayedSig<REAL>>& real_delays,
                      std::map<Tree, inputControl>&     inputs_control,
                      std::map<Tree, outputControl>& outputs_control, int& inputs)
            : fIntDelays(int_delays),
              fRealDelays(real_delays),
              fInputControls(inputs_control),
              fOutputControls(outputs_control),
              fNumInputs(inputs)
        {
        }

        void visit(Tree sig)
        {
            Tree path, c, x, y, z;

            if (int input; isSigInput(sig, &input)) {
                fNumInputs++;
            } else if (isSigDelay1(sig, x)) {
                allocateDelayLine(x, tree(1));
                SignalVisitor::visit(sig);
            } else if (isSigDelay(sig, x, y)) {
                allocateDelayLine(x, y);
                SignalVisitor::visit(sig);
            } else if (isSigButton(sig, path)) {  // UI
                fInputControls[sig] =
                    inputControl(inputControl::kButton, tree2str(hd(path)), 0, 0, 1, 1);
            } else if (isSigCheckbox(sig, path)) {
                fInputControls[sig] =
                    inputControl(inputControl::kCheckbutton, tree2str(hd(path)), 0, 0, 1, 1);
            } else if (isSigVSlider(sig, path, c, x, y, z)) {
                fInputControls[sig] =
                    inputControl(inputControl::kVslider, tree2str(hd(path)), tree2double(c),
                                 tree2double(x), tree2double(y), tree2double(z));
            } else if (isSigHSlider(sig, path, c, x, y, z)) {
                fInputControls[sig] =
                    inputControl(inputControl::kHslider, tree2str(hd(path)), tree2double(c),
                                 tree2double(x), tree2double(y), tree2double(z));
            } else if (isSigNumEntry(sig, path, c, x, y, z)) {
                fInputControls[sig] =
                    inputControl(inputControl::kNumEntry, tree2str(hd(path)), tree2double(c),
                                 tree2double(x), tree2double(y), tree2double(z));
            } else if (isSigVBargraph(sig, path, x, y, z)) {
                fOutputControls[sig] = outputControl(outputControl::kVbargraph, tree2str(hd(path)),
                                                     tree2double(x), tree2double(y));
                SignalVisitor::visit(sig);
            } else if (isSigHBargraph(sig, path, x, y, z)) {
                fOutputControls[sig] = outputControl(outputControl::kHbargraph, tree2str(hd(path)),
                                                     tree2double(x), tree2double(y));
                SignalVisitor::visit(sig);
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
        // Build delay lines and inputs/outputs control
        SignalBuilder builder(fIntDelays, fRealDelays, fInputControls, fOutputControls, fNumInputs);
        builder.visitRoot(fOutputSig);
    }

    // Do not check already visited
    void self(Tree sig) override { visit(sig); }

    Node writeReadDelay(Tree x, Node& v1, Node& v2)
    {
        if (fIntDelays.count(x) > 0) {
            fIntDelays[x].write(fIOTA, v1.getInt());
            return Node(fIntDelays[x].read(fIOTA - v2.getInt()));
        } else if (fRealDelays.count(x) > 0) {
            fRealDelays[x].write(fIOTA, v1.getDouble());
            return Node(fRealDelays[x].read(fIOTA - v2.getInt()));
        } else {
            faustassert(false);
            return Node(0);
        }
    }

    Node readDelay(Tree x, Node& v2)
    {
        if (fIntDelays.count(x) > 0) {
            return Node(fIntDelays[x].read(fIOTA - v2.getInt()));
        } else if (fRealDelays.count(x) > 0) {
            return Node(fRealDelays[x].read(fIOTA - v2.getInt()));
        } else {
            faustassert(false);
            return Node(0);
        }
    }

    bool                             fVisitGen{false};  // wether to visit gen signal for tables
    std::stack<Node>                 fValueStack;
    std::map<Tree, DelayedSig<int>>  fIntDelays;
    std::map<Tree, DelayedSig<REAL>> fRealDelays;
    std::map<Tree, inputControl>     fInputControls;
    std::map<Tree, outputControl>    fOutputControls;
    int                              fNumInputs  = 0;
    int                              fSampleRate = -1;
    int                              fSample     = 0;
    int                              fIOTA       = 0;
    FAUSTFLOAT**                     fInputs     = nullptr;
    Tree                             fOutputSig;

    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);

    Node popRes()
    {
        Node val = fValueStack.top();
        fValueStack.pop();
        return val;
    }

    Node topRes() { return fValueStack.top(); }

    void pushRes(Node node) { fValueStack.push(node); }

    virtual void visit(Tree t) override;
};

/**
 * @brief The signal\_dsp class is used to render signals.
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

    virtual void instanceConstants(int sample_rate) { fRenderer.fSampleRate = sample_rate; }

    virtual void instanceResetUserInterface()
    {
        for (auto& it : fRenderer.fInputControls) {
            it.second.init();
        }
    }

    virtual void init(int sample_rate)
    {
        // classInit(sample_rate);
        instanceInit(sample_rate);
    }

    virtual void instanceInit(int sample_rate)
    {
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
    }

    virtual void metadata(Meta* meta) {}

    virtual signal_dsp_aux* clone() { return new signal_dsp_aux<REAL>(fRenderer.fOutputSig); }

    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
};

// External API

struct signal_dsp_factory : public dsp_factory {
    struct SignalChecker : public SignalVisitor {
        void visit(Tree sig)
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
    bool        fIsDouble = false;
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
        std::copy(argv, argv + argc, std::ostream_iterator<std::string>(oss, " "));

        // Get the resulting string and trim the trailing space
        fCompileOptions = oss.str();
        if (!fCompileOptions.empty()) {
            fCompileOptions.pop_back();  // Remove the trailing space
        }
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
            return new signal_dsp_aux<double>(fOutputSig);
        } else {
            return new signal_dsp_aux<float>(fOutputSig);
        }
    }

    /* Static tables initialization, possibly implemened in sub-classes*/
    virtual void classInit(int sample_rate) {};

    /* Set a custom memory manager to be used when creating instances */
    virtual void setMemoryManager(dsp_memory_manager* manager) {}

    /* Return the currently set custom memory manager */
    virtual dsp_memory_manager* getMemoryManager() { return nullptr; }
};
