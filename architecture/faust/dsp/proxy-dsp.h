/************************** BEGIN proxy-dsp.h ***************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __proxy_dsp__
#define __proxy_dsp__

#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <cassert>

#include "faust/dsp/dsp.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/JSONUIDecoder.h"
#include "faust/gui/JSONUI.h"

/**
 * proxy_dsp
 *
 * Minimal helper that exposes a DSP described only by its JSON UI. It owns a JSONUIDecoder,
 * reports the number of audio I/O channels, rebuilds the UI, and forwards lifecycle calls
 * (init/instanceInit/instanceConstants/instanceResetUserInterface/instanceClear) to keep the
 * decoder state in sync with a real DSP that may live elsewhere (remote process, different
 * address space, etc.).
 *
 * Ownership:
 * - Owns the JSONUIDecoder created from a JSON string or from an existing dsp instance.
 * - Does NOT own audio/MIDI resources; subclasses are expected to implement compute().
 *
 * Lifecycle expectations:
 * - instanceConstants stores the sample rate locally (for subclasses to query getSampleRate()).
 * - instanceResetUserInterface resets the decoder UI so control defaults match the real DSP.
 * - compute() is left abstract; concrete subclasses implement the transport to the real DSP.
 *
 * Cloning:
 * - clone() duplicates only the decoder JSON; subclasses typically override it to clone their
 *   transport state as well.
 */
class proxy_dsp : public ::dsp {

    protected:
    
        JSONUIDecoder* fDecoder;
        int fSampleRate;
    
        void init(const std::string& json)
        {
            fDecoder = new JSONUIDecoder(json);
            fSampleRate = -1;
        }
        
    public:
    
        proxy_dsp():fDecoder(nullptr), fSampleRate(-1)
        {}
    
        proxy_dsp(const std::string& json)
        {
            init(json);
        }
          
        proxy_dsp(dsp* dsp)
        {
            JSONUI builder(dsp->getNumInputs(), dsp->getNumOutputs());
            dsp->metadata(&builder);
            dsp->buildUserInterface(&builder);
            fSampleRate = dsp->getSampleRate();
            fDecoder = new JSONUIDecoder(builder.JSON());
        }
      
        virtual ~proxy_dsp()
        {
            delete fDecoder;
        }
    
        virtual int getNumInputs() { return fDecoder->fNumInputs; }
        virtual int getNumOutputs() { return fDecoder->fNumOutputs; }
        
        virtual void buildUserInterface(UI* ui) { fDecoder->buildUserInterface(ui); }
        
        // To possibly implement in a concrete proxy dsp 
        virtual void init(int sample_rate)
        {
            instanceInit(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }
        virtual void instanceConstants(int sample_rate) { fSampleRate = sample_rate; }
        virtual void instanceResetUserInterface() { fDecoder->resetUserInterface(); }
        virtual void instanceClear() {}
    
        virtual int getSampleRate() { return fSampleRate; }
    
        virtual proxy_dsp* clone() { return new proxy_dsp(fDecoder->fJSON); }
        virtual void metadata(Meta* m) { fDecoder->metadata(m); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {} 
        
};

/**
 * This class allows a 'decorator' like layer to smooth control changes over a
 * given duration (expressed in seconds) before applying them to the decorated dsp.
 *
 * Design notes
 * - Goal: wraps an existing dsp instance and transparently smooths its input controllers
 *   whenever any control value changes.
 *
 * - Inputs vs outputs: only input controls (sliders, buttons, nentry, checkbox) are smoothed.
 *   Bargraphs and soundfiles are ignored by the smoothing logic but remain exposed via the
 *   JSONUIDecoder UI.
 *
 * - Smoothing model: linear or exponential per control over `fSmoothingSamples` samples.
 *   Linear: per-sample `increment = (target - current) / duration`, exact snap at end.
 *   Exponential: per-sample decay `current = target + (current - target) * alpha` where
 *   `alpha` is chosen so the residual after the duration is ~1e-4 (-80 dB), then snapped exact at end.
 *   If `fSmoothingSamples <= 0`, values jump immediately to targets. Buttons and checkboxes are
 *   treated as toggles and jump directly without smoothing.
 *
 * - Smoothing strategy: supplied as a template parameter (LinearSmoother and ExpSmoother provided).
 *
 * - Smoothing configuration: callers pass a duration in seconds; the class converts it to a
 *   sample count on instanceConstants(), then uses that count for ramp scheduling.
 *
 * - Triggering: the ramp setup occurs at the beginning of each compute() (both variants). If no
 *   control has changed since the previous compute, no new ramp is created and processing runs at
 *   full block size. When a ramp is active, processing falls back to sample-by-sample computation
 *   until the ramp ends, then resumes block processing for the remaining frames.
 *
 * - State/ownership: the class owns its JSONUIDecoder; the wrapped dsp is owned by decorator_dsp.
 *   clone() deep-clones both the decoder JSON and the wrapped dsp and preserves the smoothing
 *   duration.
 *
 * - Reset behaviour: instanceResetUserInterface() resets both the wrapped dsp UI and the decoder
 *   state, then realigns smoothing buffers to the reset control values. instanceClear() stops any
 *   ongoing ramp.
 * - API expectations: smoothing is configured in seconds (not ms). Callers must supply the desired
 *   duration in seconds when constructing the decorator.
 */

// Base class for Smoother
// - finish: snaps to exact targets and clears any stored steps.
struct Smoother {
    
    // Snap to targets at ramp completion and clear step deltas.
    template <typename ControlContainer>
    void finish(ControlContainer& controls)
    {
        size_t count = controls.size();
        for (size_t i = 0; i < count; ++i) {
            controls[i].fCurrent = controls[i].fTarget;
            *controls[i].fDspZone = controls[i].fCurrent;
            controls[i].fStep = FAUSTFLOAT(0);
        }
    }
};

// Linear ramp: distributes the delta evenly across durationSamples.
// - start: computes per-control steps = (target - current) / durationSamples and sets remaining.
// - step: adds one step to each control, writes the zone.
struct LinearSmoother : public Smoother {
    template <typename ControlContainer>
    void start(ControlContainer& controls, int durationSamples, int& remaining)
    {
        size_t count = controls.size();
        remaining = durationSamples;
        if (remaining <= 0) {
            for (size_t i = 0; i < count; ++i) {
                controls[i].fStep = FAUSTFLOAT(0);
            }
            remaining = 0;
        } else {
            for (size_t i = 0; i < count; ++i) {
                controls[i].fStep = (controls[i].fTarget - controls[i].fCurrent) / FAUSTFLOAT(durationSamples);
            }
        }
    }
    
    // Advance one sample worth of linear interpolation and write zones.
    template <typename ControlContainer>
    void step(ControlContainer& controls)
    {
        size_t count = controls.size();
        for (size_t i = 0; i < count; ++i) {
            controls[i].fCurrent += controls[i].fStep;
            *controls[i].fDspZone = controls[i].fCurrent;
        }
    }
    
};

// Exponential approach toward target: current = target + (current - target) * alpha.
// - start: precomputes alpha so the residual after durationSamples is ~1e-4 (-80 dB) and sets remaining
//   (the -80 dB tail is an arbitrary choice; change if you want a different decay depth).
// - step: decays current toward target using alpha, writes the zone.
struct ExpSmoother : public Smoother {
    double fAlpha;
    
    ExpSmoother():fAlpha(0) {}
    
    // Precompute alpha for exponential decay over durationSamples; empty steps vector is kept for API symmetry.
    template <typename ControlContainer>
    void start(ControlContainer& controls, int durationSamples, int& remaining)
    {
        if (durationSamples <= 0) {
            remaining = 0;
            fAlpha = 0;
        } else {
            remaining = durationSamples;
            // Choose alpha so that the residual after 'durationSamples' steps is around -80 dB (~1e-4).
            const double targetResidual = 1e-4;
            fAlpha = std::exp(std::log(targetResidual) / double(durationSamples));
        }
        // Keep step/scratch cleared.
        for (size_t i = 0; i < controls.size(); ++i) {
            controls[i].fStep = FAUSTFLOAT(0);
        }
    }
    
    // Apply exponential decay for one sample and write zones.
    template <typename ControlContainer>
    void step(ControlContainer& controls)
    {
        size_t count = controls.size();
        for (size_t i = 0; i < count; ++i) {
            controls[i].fCurrent = controls[i].fTarget + (controls[i].fCurrent - controls[i].fTarget) * FAUSTFLOAT(fAlpha);
            *controls[i].fDspZone = controls[i].fCurrent;
        }
    }
    
};

template <typename Smoother>
class smoothing_dsp : public decorator_dsp {

    protected:
    
        JSONUIDecoder* fDecoder;
        double fSmoothingSec;    // Smoothing duration in seconds (construction-time parameter)
        int fSmoothingSamples;   // Smoothing duration in samples (derived from samplerate)
        int fRemaining;          // Remaining samples in current smoothing ramp
        using zone_param = JSONUIDecoderReal<FAUSTFLOAT>::ZoneParam;

        struct ControlData {
            FAUSTFLOAT* fDspZone;   // Pointer to wrapped DSP control zone
            bool fIsToggle;         // True for buttons/checkboxes (no smoothing)
            FAUSTFLOAT fCurrent;    // Working value used by smoothing
            FAUSTFLOAT fTarget;     // Desired value from decoder
            FAUSTFLOAT fStep;       // Linear step (or scratch for other smoothers)
        };
        
        // Control data grouped in a single container
        std::vector<ControlData> fControls;
        std::vector<FAUSTFLOAT*> fDecoderZones;    // Fast access to decoder-side control zones
        std::vector<FAUSTFLOAT*> fInputPtrs;
        std::vector<FAUSTFLOAT*> fOutputPtrs;
        
        Smoother fSmoother;
        
        // Helper UI that only collects input control zones from the wrapped dsp.
        struct ControlCollector : public GenericUI {
            
            std::vector<FAUSTFLOAT*> fInputs;
            std::vector<bool> fToggles;
            
            void addButton(const char* /*label*/, FAUSTFLOAT* zone)
            {
                fInputs.push_back(zone);
                fToggles.push_back(true);
            }
            void addCheckButton(const char* /*label*/, FAUSTFLOAT* zone)
            {
                fInputs.push_back(zone);
                fToggles.push_back(true);
            }
            void addVerticalSlider(const char* /*label*/, FAUSTFLOAT* zone, FAUSTFLOAT /*init*/, FAUSTFLOAT /*fmin*/, FAUSTFLOAT /*fmax*/, FAUSTFLOAT /*step*/)
            {
                fInputs.push_back(zone);
                fToggles.push_back(false);
            }
            void addHorizontalSlider(const char* /*label*/, FAUSTFLOAT* zone, FAUSTFLOAT /*init*/, FAUSTFLOAT /*fmin*/, FAUSTFLOAT /*fmax*/, FAUSTFLOAT /*step*/)
            {
                fInputs.push_back(zone);
                fToggles.push_back(false);
            }
            void addNumEntry(const char* /*label*/, FAUSTFLOAT* zone, FAUSTFLOAT /*init*/, FAUSTFLOAT /*fmin*/, FAUSTFLOAT /*fmax*/, FAUSTFLOAT /*step*/)
            {
                fInputs.push_back(zone);
                fToggles.push_back(false);
            }
        };
        
        size_t getControlCount() const
        {
             return fControls.size();
        }

        // Collect raw zones from the wrapped dsp UI for direct writes.
        void collectControlZones(::dsp* dsp)
        {
            ControlCollector collector;
            dsp->buildUserInterface(&collector);
            size_t count = collector.fInputs.size();
            fControls.resize(count);
            for (size_t i = 0; i < count; ++i) {
                fControls[i].fDspZone = collector.fInputs[i];
                fControls[i].fIsToggle = collector.fToggles[i];
                fControls[i].fCurrent = FAUSTFLOAT(0);
                fControls[i].fTarget = FAUSTFLOAT(0);
                fControls[i].fStep = FAUSTFLOAT(0);
            }
        }
        
        // Cache decoder-side control zones for fast access in smoothing.
        void buildDecoderZones()
        {
            auto& inputs = fDecoder->getInputControls();
            fDecoderZones.resize(inputs.size());
            for (size_t i = 0; i < inputs.size(); ++i) {
                fDecoderZones[i] = &static_cast<zone_param*>(inputs[i])->fZone;
            }
        }
        
        // Reinitialize smoothing buffers and push initial values to the wrapped dsp.
        void resetSmoothingState()
        {
            size_t count = getControlCount();
            for (size_t i = 0; i < count; ++i) {
                FAUSTFLOAT value = *fDecoderZones[i];
                fControls[i].fCurrent = value;
                fControls[i].fTarget = value;
                fControls[i].fStep = FAUSTFLOAT(0);
                *fControls[i].fDspZone = value;
            }
            fRemaining = 0;
        }
        
        // Detect controller changes and configure ramp data for the selected smoothing strategy.
        // - Scans decoder inputs; toggles (buttons/checkboxes) are applied immediately.
        // - If smoothing duration is zero, applies new targets instantly.
        // - Otherwise delegates ramp setup to the active smoother.
        void setupSmoothing()
        {
            // Detect control changes, configure ramps, or jump immediately if smoothing is disabled
            bool changed = false;
            size_t count = getControlCount();
            for (size_t i = 0; i < count; ++i) {
                FAUSTFLOAT next = *fDecoderZones[i];
                assert(i < fControls.size());
                ControlData& ctl = fControls[i];
                if (next != ctl.fTarget) {
                    // Scans decoder inputs; toggles (buttons/checkboxes) are applied immediately.
                    if (ctl.fIsToggle) {
                        // Buttons/checkboxes jump directly.
                        ctl.fTarget = next;
                        ctl.fCurrent = next;
                        *ctl.fDspZone = next;
                    } else {
                        // Range controllers will be smoothed
                        ctl.fTarget = next;
                        changed = true;
                    }
                }
            }
    
            if (!changed) {
                return;
            }
    
            // - If smoothing duration is zero, applies new targets instantly.
            if (fSmoothingSamples <= 0) {
                for (size_t i = 0; i < count; ++i) {
                    ControlData& ctl = fControls[i];
                    ctl.fCurrent = ctl.fTarget;
                    ctl.fStep = FAUSTFLOAT(0);
                    *ctl.fDspZone = ctl.fCurrent;
                }
                fRemaining = 0;
                return;
            }
    
            // - Otherwise delegates ramp setup to the active smoother.
            fSmoother.start(fControls, fSmoothingSamples, fRemaining);
            if (fRemaining <= 0) {
                fSmoother.finish(fControls);
                fRemaining = 0;
            }
        }
        
        // Convert seconds-based duration into samples using current samplerate.
        void updateSmoothingSamples()
        {
            fSmoothingSamples = (fSmoothingSec > 0) ? (fSmoothingSec * double(decorator_dsp::getSampleRate())) : 0;
        }
        
        // Initialize decoder and smoothing state using an existing dsp instance.
        void init(const std::string& json, ::dsp* dsp, double smoothing_sec)
        {
            fDecoder = new JSONUIDecoder(json);
            collectControlZones(dsp);
            buildDecoderZones();
            fInputPtrs.assign(getNumInputs(), nullptr);
            fOutputPtrs.assign(getNumOutputs(), nullptr);
            fSmoothingSec = smoothing_sec;
            fSmoothingSamples = 0;
            fRemaining = 0;
            resetSmoothingState();
        }
    
        // Helper to position per-channel input/output pointers at a given frame offset.
        void setIO(std::vector<FAUSTFLOAT*>& input_ptrs,
                   std::vector<FAUSTFLOAT*>& output_ptrs,
                   FAUSTFLOAT** inputs,
                   FAUSTFLOAT** outputs,
                   int frame_offset)
        {
            int num_inputs = getNumInputs();
            int num_outputs = getNumOutputs();
            for (int chan = 0; chan < num_inputs; ++chan) {
                input_ptrs[chan] = inputs ? inputs[chan] + frame_offset : nullptr;
            }
            for (int chan = 0; chan < num_outputs; ++chan) {
                output_ptrs[chan] = outputs ? outputs[chan] + frame_offset : nullptr;
            }
        }
        
    public:
    
        // Build from a concrete dsp, selecting smoothing duration (seconds).
        smoothing_dsp(::dsp* dsp, double smoothing_sec = 0)
        : decorator_dsp(dsp), fDecoder(nullptr), fSmoothingSec(smoothing_sec), fSmoothingSamples(0), fRemaining(0),
          fSmoother()
        {
            // Build JSON description from the wrapped dsp and initialize smoothing
            JSONUI builder(dsp->getNumInputs(), dsp->getNumOutputs());
            dsp->metadata(&builder);
            dsp->buildUserInterface(&builder);
            init(builder.JSON(), dsp, smoothing_sec);
        }
        
        // Build from explicit JSON and a concrete dsp, with smoothing settings.
        smoothing_dsp(const std::string& json, ::dsp* dsp, double smoothing_sec = 0)
        : decorator_dsp(dsp), fDecoder(nullptr), fSmoothingSec(smoothing_sec), fSmoothingSamples(0), fRemaining(0),
          fSmoother()
        {
            init(json, dsp, smoothing_sec);
        }
    
        // Release decoder (wrapped dsp is owned by decorator_dsp).
        virtual ~smoothing_dsp()
        {
            delete fDecoder;
        }
        
        // Expose JSON UI while preserving smoothing indirection.
        virtual void buildUserInterface(UI* ui) { fDecoder->buildUserInterface(ui); }
        
        // Lifecycle mirrors proxy_dsp but keeps smoothing state coherent
        virtual void init(int sample_rate)
        {
            decorator_dsp::init(sample_rate);
            instanceInit(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }
    
        // Store samplerate while forwarding constants to wrapped dsp.
        virtual void instanceConstants(int sample_rate)
        {
            decorator_dsp::instanceConstants(sample_rate);
            updateSmoothingSamples();
        }
        // Reset both decoder UI and wrapped dsp UI, then realign smoothing buffers.
        virtual void instanceResetUserInterface()
        {
            decorator_dsp::instanceResetUserInterface();
            fDecoder->resetUserInterface();
            resetSmoothingState();
        }
        // Clear wrapped dsp state and stop any ongoing ramp.
        virtual void instanceClear()
        {
            decorator_dsp::instanceClear();
            fRemaining = 0;
        }
    
        // Clone decoder JSON, wrapped dsp, and smoothing strategy
        virtual smoothing_dsp* clone()
        {
            return new smoothing_dsp(fDecoder->fJSON, fDSP->clone(), fSmoothingSec);
        }
        // Forward metadata from decoder
        virtual void metadata(Meta* m) { fDecoder->metadata(m); }
    
        // Top-level audio processing: apply pending control ramps sample-by-sample, then finish the block.
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            // Run control smoothing then process audio.
            // If a ramp is active, we switch to per-sample processing to update controls each sample.
            // Once smoothing completes, remaining frames (if any) are processed in a single block.
            
            setupSmoothing();
            
            if (fRemaining <= 0) {
                // No smoothing needed, so regular compute
                decorator_dsp::compute(count, inputs, outputs);
            } else {
                
                // Smoothing
                int offset = 0;
                while (offset < count && fRemaining > 0) {
                    // Update controls for this sample and advance the ramp
                    fSmoother.step(fControls);
                    if (--fRemaining == 0) {
                        // Ensure exact target values when ramp ends
                        fSmoother.finish(fControls);
                    }
                    // Compute one sample with updated controls
                    setIO(fInputPtrs, fOutputPtrs, inputs, outputs, offset);
                    decorator_dsp::compute(1, fInputPtrs.data(), fOutputPtrs.data());
                    offset++;
                }
                
                // No active ramp: process remaining frames in one call
                if (offset < count) {
                    setIO(fInputPtrs, fOutputPtrs, inputs, outputs, offset);
                    decorator_dsp::compute(count - offset, fInputPtrs.data(), fOutputPtrs.data());
                }
            }
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
        
};

using smoothing_dsp_linear = smoothing_dsp<LinearSmoother>;
using smoothing_dsp_exp = smoothing_dsp<ExpSmoother>;

#endif
/************************** END proxy-dsp.h **************************/
        
