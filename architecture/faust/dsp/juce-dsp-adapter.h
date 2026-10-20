/************************** BEGIN juce-dsp-adapter.h *************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __juce_dsp_adapter__
#define __juce_dsp_adapter__

#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>

#include "../JuceLibraryCode/JuceHeader.h"

#include "faust/dsp/dsp.h"
#include "faust/dsp/dsp-adapter.h"

/*
    FaustHostAdapter: runs a DSP on the audio buffers of a JUCE host, used by the JUCE plugin
    (juce-plugin.cpp) and standalone (juce-standalone.cpp) architectures.

    The DSP computes samples of type FAUSTFLOAT (float, or double with -double) on its own
    number of inputs and outputs. The host buffers can differ in both respects:

    - sample type: a plugin gets AudioBuffer<float>, or AudioBuffer<double> when the processor
      supports double precision (FAUSTFLOAT is double) and the host asks for it; a standalone
      always gets AudioBuffer<float>;
    - channel counts: the host can use fewer channels than the DSP has (bus layout chosen by the
      plugin host, audio device of the standalone).

    And they can change while the DSP runs: a VST3 host may process in float in real time and
    in double for an offline render (bounce), then in float again; a standalone gets other
    channel counts when the audio device changes. So the configuration is checked at each block,
    on the buffer actually received.

    The DSP is computed through a chain of at most two adapters:

        host buffers -> [dsp_adapter] -> [dsp_sample_adapter] -> DSP

    - dsp_sample_adapter<FAUSTFLOAT, FloatType> converts the host samples to FAUSTFLOAT and back,
      when FloatType is not FAUSTFLOAT;
    - dsp_adapter gives the DSP zeroed inputs and scratch outputs for its channels beyond those of
      the host, when the DSP has more channels than the host (fewer channels need no adapter: the
      DSP only uses the first channels of the buffer).

    The DSP itself is never wrapped: the adapters do not own it (they are created with
    to_delete = false), so when the configuration changes they are simply deleted and rebuilt
    around the same DSP, which is left untouched: its controls, bound to the user interface and
    to the host parameters, stay valid. The DSP is owned by the caller and must outlive this
    object.

    Building the adapters allocates memory, which is not real-time safe. 'prepare' builds them
    ahead, outside the audio thread, for the configuration the caller expects; 'compute' only
    rebuilds them when the block it gets does not match, so never on the following blocks.

    Blocks longer than kMaxSlice frames (offline renders can use large ones) are computed in
    several slices of at most kMaxSlice frames. kMaxSlice is the size of the adapter buffers,
    and must not exceed the buffers of the DSP itself: the mixing buffers of a polyphonic DSP
    (MIX_BUFFER_SIZE in poly-dsp.h) and the buffers of a dsp_sequencer (-effect), 4096 frames.
*/
class FaustHostAdapter {

    private:

        static constexpr int kMaxSlice = 4096;    // size of the adapter buffers, in frames

        // Adapters around the DSP, which they do not delete
        std::unique_ptr<dsp> fSampleAdapter;      // float/double, or null
        std::unique_ptr<dsp> fChannelAdapter;     // channel counts, or null
        dsp* fCompute = nullptr;                  // the DSP, or the last adapter: what compute calls

        // Host configuration the adapters have been built for
        dsp* fBase = nullptr;                     // the DSP
        bool fDouble = false;                     // host samples are double
        int fHWInputs = -1;                       // host input channels
        int fHWOutputs = -1;                      // host output channels

        // Channel pointers of the current slice, for the inputs and outputs of fCompute
        std::vector<void*> fInputs;
        std::vector<void*> fOutputs;

    public:

        /*
            Builds the adapter chain around the DSP 'base' for host samples of type FloatType
            and 'hw_inputs' and 'hw_outputs' host channels, unless it has already been built
            for this configuration. Allocates memory when it builds: call it outside the
            audio thread when the configuration is known in advance.
        */
        template <typename FloatType>
        void prepare(dsp* base, int hw_inputs, int hw_outputs)
        {
            constexpr bool is_double = std::is_same<FloatType, double>::value;
            if (fCompute && fBase == base && fDouble == is_double
                && fHWInputs == hw_inputs && fHWOutputs == hw_outputs) {
                return;
            }

            fChannelAdapter.reset();
            fSampleAdapter.reset();
            fCompute = base;
            if (!std::is_same<FloatType, FAUSTFLOAT>::value) {
                fSampleAdapter = std::make_unique<dsp_sample_adapter<FAUSTFLOAT, FloatType, kMaxSlice>>(fCompute, false);
                fCompute = fSampleAdapter.get();
            }
            if (fCompute->getNumInputs() > hw_inputs || fCompute->getNumOutputs() > hw_outputs) {
                fChannelAdapter = std::make_unique<dsp_adapter>(fCompute, hw_inputs, hw_outputs, kMaxSlice, false);
                fCompute = fChannelAdapter.get();
            }

            fBase = base;
            fDouble = is_double;
            fHWInputs = hw_inputs;
            fHWOutputs = hw_outputs;
            fInputs.assign(fCompute->getNumInputs(), nullptr);
            fOutputs.assign(fCompute->getNumOutputs(), nullptr);
        }

        /*
            Computes the DSP 'base' in place on the 'count' frames of 'buffer' starting at frame
            'start': the inputs are read from the first 'hw_inputs' channels of the buffer, the
            outputs written to its first 'hw_outputs' channels. Builds the adapter chain first
            if 'prepare' has not been called for this configuration.
        */
        template <typename FloatType>
        void compute(dsp* base, juce::AudioBuffer<FloatType>& buffer, int start, int count, int hw_inputs, int hw_outputs)
        {
            prepare<FloatType>(base, hw_inputs, hw_outputs);

            for (int offset = 0; offset < count; offset += kMaxSlice) {
                const int slice = std::min(kMaxSlice, count - offset);
                for (size_t chan = 0; chan < fInputs.size(); chan++) {
                    fInputs[chan] = const_cast<FloatType*>(buffer.getReadPointer(int(chan), start + offset));
                }
                for (size_t chan = 0; chan < fOutputs.size(); chan++) {
                    fOutputs[chan] = buffer.getWritePointer(int(chan), start + offset);
                }
                // MIDI timestamp is expressed in frames
                fCompute->compute(-1, slice, (FAUSTFLOAT**)fInputs.data(), (FAUSTFLOAT**)fOutputs.data());
            }
        }

};

#endif
/**************************  END  juce-dsp-adapter.h **************************/
