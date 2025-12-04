/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN minimal-clone.cpp ****************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2025 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>
#include <faust/dsp/dsp.h>

// Example usage (generates a demo showing clone() vs continuous processing):
//   faust -a minimal-clone.cpp noise.dsp -o noise.cpp
//   c++ -std=c++11 noise.cpp -o noise && ./noise
//
// What this architecture demonstrates:
// - Builds two identical DSP runs over a short buffer span.
// - The first run processes continuously.
// - Three transfer models are exercised mid-run, each replacing the active DSP:
//   1) clone(): virtual factory that must copy the current state.
//   2) copy constructor: DSP(const DSP&) should deep-copy the state.
//   3) copy assignment: operator=(const DSP&) should deep-copy the state.
// - Deterministic parameter automation is applied so all runs receive the
//   same control changes, scaled to each control's declared min/max range.
// - Outputs are compared sample-by-sample; any non-zero diff flags a broken
//   state transfer (delay lines, filters, envelopes, etc.).
//
// Expected console output:
// - Lists how many controls were found and how many are automated (up to 4).
// - Prints when each transfer happens (clone / copy-ctor / copy-assign).
// - Reports the maximum absolute difference vs the baseline run and where
//   it occurs. Zero means the transfer preserved state exactly.

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

using namespace std;

// Transfer modes used to validate state preservation.
enum class TransferKind {
    None,
    Clone,
    CopyConstructor,
    CopyAssignment
};

// Tiny event used to drive UI parameters at precise frames.
// Each event targets a single parameter path at a chosen frame with a value
// already expressed in the parameter's native range.
struct ParamEvent {
    size_t frame = 0;
    string path;
    FAUSTFLOAT value = 0;
};

// Render outputs plus meta information used to compare different runs.
struct RenderResult {
    vector<float> samples;
    int outputs = 0;
};

// MapUI that remembers declared ranges so we can normalize automation to [0..1].
struct RangeMapUI : public MapUI {
    struct Range {
        string path;
        FAUSTFLOAT min = 0;
        FAUSTFLOAT max = 0;
        bool hasRange = false;
    };
    
    vector<Range> fRanges;  // parallel to parameter order (index = parameter index)
    
    void addButton(const char* label, FAUSTFLOAT* zone) override
    {
        addZoneWithRange(label, zone, 0, 0, false);
    }
    void addCheckButton(const char* label, FAUSTFLOAT* zone) override
    {
        addZoneWithRange(label, zone, 0, 0, false);
    }
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step) override
    {
        addZoneWithRange(label, zone, fmin, fmax, true);
    }
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step) override
    {
        addZoneWithRange(label, zone, fmin, fmax, true);
    }
    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step) override
    {
        addZoneWithRange(label, zone, fmin, fmax, true);
    }
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax) override
    {
        addZoneWithRange(label, zone, fmin, fmax, true);
    }
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax) override
    {
        addZoneWithRange(label, zone, fmin, fmax, true);
    }
    
    // Retrieve the stored range for the given parameter index.
    Range getRange(size_t index) const
    {
        if (index < fRanges.size()) {
            return fRanges[index];
        }
        return Range();
    }
    
private:
    // Keep MapUI bookkeeping while capturing ranges for later scaling.
    void addZoneWithRange(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax, bool hasRange)
    {
        string path = buildPath(label);
        fFullPaths.push_back(path);
        fPathZoneMap[path] = zone;
        fLabelZoneMap[label] = zone;
        fRanges.push_back({path, fmin, fmax, hasRange});
    }
};

// Build deterministic automation for up to four parameters, scaled to their ranges.
// The goal is to ensure that:
// - We stress-test clone() with non-default control values.
// - Values are valid regardless of the original slider/min/max declaration.
// - The sequence is stable across runs (no randomness).
//
// The automation pattern for each parameter is the same:
//   frame 0   : 10% of range
//   frame 1/4 : 80% of range
//   frame 2/4 : 20% of range
//   frame 3/4 : 60% of range
//
// That makes it easy to see if the clone captured the exact UI state mid-run.
static vector<ParamEvent> createAutomation(const RangeMapUI& ui, size_t totalFrames)
{
    vector<ParamEvent> events;
    const size_t paramCount = static_cast<size_t>(ui.getParamsCount());
    if (paramCount == 0) {
        return events;
    }
    
    size_t quarter = totalFrames / 4;
    const size_t automateCount = std::min(paramCount, static_cast<size_t>(4));
    
    for (size_t i = 0; i < automateCount; ++i) {
        RangeMapUI::Range range = ui.getRange(i);
        string path = !range.path.empty() ? range.path : ui.getParamAddress(static_cast<int>(i));
        
        auto toReal = [&](float normalized) -> FAUSTFLOAT {
            float clamped = std::min(std::max(normalized, 0.0f), 1.0f);
            if (!range.hasRange) {
                return clamped;
            }
            return static_cast<FAUSTFLOAT>(range.min + (range.max - range.min) * clamped);
        };
        
        // Keep it deterministic: four moves spread across the render range.
        events.push_back({0, path, toReal(0.1f)});
        events.push_back({quarter, path, toReal(0.8f)});
        events.push_back({quarter * 2, path, toReal(0.2f)});
        events.push_back({quarter * 3, path, toReal(0.6f)});
    }
    return events;
}

// Apply all UI changes scheduled for the current frame.
// This is intentionally simple (single event list scanned once) because we
// only have a handful of frames and parameters in this demo.
static void applyEvents(size_t frame, const vector<ParamEvent>& events, size_t& nextEventIndex, MapUI& ui)
{
    while (nextEventIndex < events.size() && events[nextEventIndex].frame == frame) {
        ui.setParamValue(events[nextEventIndex].path, events[nextEventIndex].value);
        ++nextEventIndex;
    }
}

// Render a short block, optionally cloning the DSP at a given frame.
// The same automation sequence and input stimulus are applied in all runs so
// any difference in output must come from state handling (clone correctness).
template <typename DSP>
static RenderResult renderScenario(unique_ptr<DSP> processor,
                                   size_t totalFrames,
                                   TransferKind transfer,
                                   size_t transferFrame,
                                   const vector<ParamEvent>& automation,
                                   int sampleRate)
{
    RenderResult result;
    if (!processor) {
        return result;
    }
    
    processor->init(sampleRate);
    
    unique_ptr<RangeMapUI> activeUI(new RangeMapUI());
    processor->buildUserInterface(activeUI.get());
    
    result.outputs = processor->getNumOutputs();
    const int numInputs = processor->getNumInputs();
    const int numOutputs = processor->getNumOutputs();
    
    const float twoPi = 6.28318530717958647692f;
    const float inputFreq = 220.0f;
    
    // One sample per channel per frame; DSP will not see larger block sizes.
    vector<FAUSTFLOAT> inputStorage(static_cast<size_t>(max(1, numInputs)), 0);
    vector<FAUSTFLOAT> outputStorage(static_cast<size_t>(max(1, numOutputs)), 0);
    vector<FAUSTFLOAT*> inputs(static_cast<size_t>(numInputs));
    vector<FAUSTFLOAT*> outputs(static_cast<size_t>(numOutputs));
    
    for (int i = 0; i < numInputs; ++i) {
        inputs[static_cast<size_t>(i)] = &inputStorage[static_cast<size_t>(i)];
    }
    for (int i = 0; i < numOutputs; ++i) {
        outputs[static_cast<size_t>(i)] = &outputStorage[static_cast<size_t>(i)];
    }
    
    size_t automationIndex = 0;
    
    // Reserve space up front to avoid reallocations during the comparison.
    result.samples.reserve(static_cast<size_t>(numOutputs) * totalFrames);
    
    for (size_t frame = 0; frame < totalFrames; ++frame) {
        if (transfer != TransferKind::None && frame == transferFrame) {
            unique_ptr<DSP> swapped;
            
            switch (transfer) {
                case TransferKind::Clone: {
                    // Clone through the virtual interface; cast back to concrete type.
                    swapped.reset(static_cast<DSP*>(processor->clone()));
                    cout << "Cloned DSP at frame " << frame << endl;
                    break;
                }
                case TransferKind::CopyConstructor: {
                    swapped.reset(new DSP(*processor));
                    cout << "Copy-constructed DSP at frame " << frame << endl;
                    break;
                }
                case TransferKind::CopyAssignment: {
                    swapped.reset(new DSP());
                    *swapped = *processor;
                    cout << "Copy-assigned DSP at frame " << frame << endl;
                    break;
                }
                case TransferKind::None:
                default:
                    break;
            }
            
            if (swapped) {
                unique_ptr<RangeMapUI> swappedUI(new RangeMapUI());
                swapped->buildUserInterface(swappedUI.get());
                processor = std::move(swapped);
                activeUI = std::move(swappedUI);
            }
        }
        
        applyEvents(frame, automation, automationIndex, *activeUI);
        
        if (numInputs > 0) {
            for (int channel = 0; channel < numInputs; ++channel) {
                float phase = twoPi * inputFreq * (static_cast<float>(frame) / static_cast<float>(sampleRate));
                inputStorage[static_cast<size_t>(channel)] = 0.2f * std::sinf(phase + static_cast<float>(channel) * 0.1f);
            }
        }
        
        processor->compute(1,
                           numInputs > 0 ? inputs.data() : nullptr,
                           numOutputs > 0 ? outputs.data() : nullptr);
        
        for (int channel = 0; channel < numOutputs; ++channel) {
            result.samples.push_back(static_cast<float>(outputStorage[static_cast<size_t>(channel)]));
        }
    }
    
    return result;
}

int main(int argc, char* argv[])
{
    const int sampleRate = 48000;
    const size_t totalFrames = 48000*5;
    const size_t cloneFrame = totalFrames / 2;
    
    // Probe the UI once to discover parameter addresses and ranges.
    mydsp probe;
    probe.init(sampleRate);
    RangeMapUI probeUI;
    probe.buildUserInterface(&probeUI);
    vector<ParamEvent> automation = createAutomation(probeUI, totalFrames);
    
    cout << "Render total frames " << totalFrames << endl;
    
    cout << "Parameters discovered: " << probeUI.getParamsCount() << endl;
    if (!automation.empty()) {
        cout << "Automating up to " << std::min(probeUI.getParamsCount(), 4) << " controls." << endl;
    } else {
        cout << "No parameters found; running with default state." << endl;
    }
    
    cout << "Running reference render without transfer..." << endl;
    RenderResult reference = renderScenario(unique_ptr<mydsp>(new mydsp()),
                                            totalFrames,
                                            TransferKind::None,
                                            0,
                                            automation,
                                            sampleRate);
    
    cout << "Running render with a clone at frame " << cloneFrame << "..." << endl;
    RenderResult cloned = renderScenario(unique_ptr<mydsp>(new mydsp()),
                                         totalFrames,
                                         TransferKind::Clone,
                                         cloneFrame,
                                         automation,
                                         sampleRate);
    
    cout << "Running render with copy-constructor handoff at frame " << cloneFrame << "..." << endl;
    RenderResult copiedCtor = renderScenario(unique_ptr<mydsp>(new mydsp()),
                                             totalFrames,
                                             TransferKind::CopyConstructor,
                                             cloneFrame,
                                             automation,
                                             sampleRate);
    
    cout << "Running render with copy-assignment handoff at frame " << cloneFrame << "..." << endl;
    RenderResult copiedAssign = renderScenario(unique_ptr<mydsp>(new mydsp()),
                                               totalFrames,
                                               TransferKind::CopyAssignment,
                                               cloneFrame,
                                               automation,
                                               sampleRate);
    
    auto compare = [](const string& label, const RenderResult& ref, const RenderResult& test) -> bool {
        if (ref.outputs != test.outputs) {
            cerr << label << ": output channel mismatch between runs: " << ref.outputs
                 << " vs " << test.outputs << endl;
            return false;
        }
        
        if (ref.samples.size() != test.samples.size()) {
            cerr << label << ": sample count mismatch between runs: " << ref.samples.size()
                 << " vs " << test.samples.size() << endl;
            return false;
        }
        
        double maxDiff = 0.0;
        size_t diffIndex = 0;
        
        for (size_t i = 0; i < ref.samples.size(); ++i) {
            double diff = std::fabs(static_cast<double>(ref.samples[i]) - static_cast<double>(test.samples[i]));
            if (diff > maxDiff) {
                maxDiff = diff;
                diffIndex = i;
            }
        }
        
        cout << fixed << setprecision(9);
        cout << label << ": maximum absolute difference = " << maxDiff << endl;
        if (maxDiff > 0) {
            size_t frame = (ref.outputs > 0) ? diffIndex / static_cast<size_t>(ref.outputs) : diffIndex;
            size_t channel = (ref.outputs > 0) ? diffIndex % static_cast<size_t>(ref.outputs) : 0;
            cout << "  First difference at frame " << frame << ", channel " << channel << endl;
            cout << "    reference: " << ref.samples[diffIndex]
                 << "    test: " << test.samples[diffIndex] << endl;
        } else {
            cout << "  Streams are identical: state transfer preserved DSP state." << endl;
        }
        return maxDiff == 0.0;
    };
    
    bool ok = true;
    ok &= compare("Clone", reference, cloned);
    ok &= compare("Copy constructor", reference, copiedCtor);
    ok &= compare("Copy assignment", reference, copiedAssign);
    
    return ok ? 0 : 1;
}

/******************* END minimal-clone.cpp ****************/
