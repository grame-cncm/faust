
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2017 GRAME, Centre National de Creation Musicale
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

 ************************************************************************/
 
/******************************************************************************
						Using OpenFramework
*******************************************************************************/

#ifndef __openframework__
#define __openframework__

#include "ofSoundStream.h"
#include "ofBaseTypes.h"

#include "faust/audio/audio.h"
#include "faust/dsp/dsp.h"

class ofaudio : public audio, public ofBaseSoundInput, public ofBaseSoundOutput {
    
    private:
    
        ofSoundStream fStream;
        float* fInBuffer;
        float** fNIInputs;
        float** fNIOutputs;
        int fSampleRate;
        int fBufferSize;
        dsp* fDSP;
    
    public:
    
        ofaudio(int srate, int bsize):fInBuffer(nullptr), fSampleRate(srate), fBufferSize(bsize) {}
        virtual ~ofaudio()
        {
            fStream.stop();
            fStream.close();
            
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                delete [] fNIInputs[i];
            }
            delete [] fNIInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                delete [] fNIOutputs[i];
            }
            delete [] fNIOutputs;
        }
    
        void audioIn(float* input, int bufferSize, int nChannels)
        {
            // Keep the input buffer to be used in 'audioOut' for the same audio cycle
            fInBuffer = input;
        }
    
        void audioOut(float* output, int bufferSize, int nChannels)
        {
            // Deinterleave input (= fInBuffer)
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                for (int frame = 0; frame < bufferSize; frame++) {
                    fNIInputs[chan][frame] = fInBuffer[chan + frame * fDSP->getNumInputs()];
                }
            }
            
            fDSP->compute(bufferSize, fNIInputs, fNIOutputs);
            
            // Interleave output
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                for (int frame = 0; frame < bufferSize; frame++) {
                    output[chan + frame * fDSP->getNumOutputs()] = fNIOutputs[chan][frame];
                }
            }
        }

        bool init(const char* name, dsp* dsp)
        {
            fDSP = dsp;
            
            //fStream.printDeviceList();
            
            fNIInputs = new float*[fDSP->getNumInputs()];
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                fNIInputs[i] = new float[4046];
            }
            fNIOutputs = new float*[fDSP->getNumOutputs()];
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                fNIOutputs[i] = new float[4046];
            }
            
            if (fDSP->getNumInputs() > 0) {
                fStream.setInput(this);
            }
            if (fDSP->getNumOutputs() > 0) {
                fStream.setOutput(this);
            }
            
            fDSP->init(fSampleRate);
            return true;
        }
    
        bool start()
        {
            // 'setup' also starts the stream...
            return fStream.setup(fDSP->getNumOutputs(), fDSP->getNumInputs(), fSampleRate, fBufferSize, 1);
        }
    
        void stop()
        {
            fStream.stop();
        }
    
        void shutdown(shutdown_callback cb, void* arg) {}

        int get_buffer_size()
        {
            return fStream.getBufferSize();
        }
    
        int get_sample_rate()
        {
            return fStream.getSampleRate();
        }

        int get_num_inputs() { return fStream.getNumInputChannels(); }
        int get_num_outputs() { return fStream.getNumOutputChannels(); }

        float get_cpu_load() { return 0.f; }
};
					
#endif
