/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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

#ifndef __dsp_tools__
#define __dsp_tools__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class Deinterleaver
{
    
    private:
    
        int fNumFrames;
        int fNumInputs;
        int fNumOutputs;
        
        FAUSTFLOAT* fInput;
        FAUSTFLOAT* fOutputs[256];
        
    public:
        
        Deinterleaver(int numFrames, int numInputs, int numOutputs)
        {
            fNumFrames = numFrames;
            fNumInputs = numInputs;
            fNumOutputs = max(numInputs, numOutputs);
            
            // allocate interleaved input channel
            fInput = new FAUSTFLOAT[fNumFrames * fNumInputs];
            
            // allocate separate output channels
            for (int i = 0; i < fNumOutputs; i++) {
                fOutputs[i] = new FAUSTFLOAT[fNumFrames];
            }
        }
        
        ~Deinterleaver()
        {
            // free interleaved input channel
            delete [] fInput;
            
            // free separate output channels
            for (int i = 0; i < fNumOutputs; i++) {
                delete [] fOutputs[i];
            }
        }
        
        FAUSTFLOAT* input() { return fInput; }
        
        FAUSTFLOAT** outputs() { return fOutputs; }
        
        void deinterleave()
        {
            for (int s = 0; s < fNumFrames; s++) {
                for (int c = 0; c < fNumInputs; c++) {
                    fOutputs[c][s] = fInput[c + s * fNumInputs];
                }
            }
        }
};

class Interleaver
{
    
    private:
        
        int fNumFrames;
        int fNumChans;
            
        FAUSTFLOAT* fInputs[256];
        FAUSTFLOAT* fOutput;
        
    public:
        
        Interleaver(int numFrames, int numChans)
        {
            fNumFrames = numFrames;
            fNumChans = numChans;
            
            // allocate separate input channels
            for (int i = 0; i < fNumChans; i++) {
                fInputs[i] = new FAUSTFLOAT[fNumFrames];
            }
            
            // allocate interleaved output channel
            fOutput = new FAUSTFLOAT[fNumFrames * fNumChans];
        }
        
        ~Interleaver()
        {
            // free separate input channels
            for (int i = 0; i < fNumChans; i++) {
                delete [] fInputs[i];
            }
            
            // free interleaved output channel
            delete [] fOutput;
        }
        
        FAUSTFLOAT** inputs() { return fInputs; }
        
        FAUSTFLOAT* output() { return fOutput; }
        
        void interleave()
        {
            for (int s = 0; s < fNumFrames; s++) {
                for (int c = 0; c < fNumChans; c++) {
                    fOutput[c + s * fNumChans] = fInputs[c][s];
                }
            }
        }
};

//=============================================================================
// An AudioChannels is a group of non-interleaved buffers that knows how to read
// from or write to an interleaved buffer. The interleaved buffer may have a
// different number of channels than the AudioChannels internal channels.
//=============================================================================

class AudioChannels
{
    
    protected:
        
        const unsigned int  fNumFrames;
        const unsigned int  fNumChannels;
        FAUSTFLOAT**        fChannels;
        
    public:
        
        AudioChannels(int nframes, int nchannels) : fNumFrames(nframes), fNumChannels(nchannels)
        {
            fChannels = new FAUSTFLOAT*[nchannels];
            
            // allocate audio channels
            for (unsigned int i = 0; i < fNumChannels; i++) {
                fChannels[i] = new FAUSTFLOAT[fNumFrames];
                for (unsigned int j = 0; j < fNumFrames; j++) {
                    fChannels[i][j] = 0;
                }
            }
        }
        
        virtual ~AudioChannels()
        {
            // free separate input channels
            for (int i = 0; i < fNumChannels; i++) {
                delete[] fChannels[i];
            }
            delete[] fChannels;
        }
        
        //---------------------------------------------------------------------------------------
        // interleavedRead: read, from the interleaved buffer <inbuffer>, <length> frames on
        // <inchannels> channels. The samples are written to the <fNumChannels> internal
        // <fChannels>.
        void interleavedRead(float* inbuffer, unsigned int length, unsigned int inchannels)
        {
            assert(length <= fNumFrames);
            unsigned int C = std::min(inchannels, fNumChannels);
            unsigned int L = std::min(length, fNumFrames);
            
            for (unsigned int f = 0; f < L; f++) {
                unsigned int p = f * inchannels;
                for (unsigned int c = 0; c < C; c++) {
                    fChannels[c][f] = inbuffer[p++];
                }
                for (unsigned int c = C; c < fNumChannels; c++) {
                    fChannels[c][f] = 0;
                }
            }
        }
        
        //----------------------------------------------------------------------------------------
        // interleavedWrite: write to the interleaved buffer <inbuffer>, <length> frames on
        // <outchannels> channels. The samples are read from <fNumChannels> internal
        // <fChannels>.
        void interleavedWrite(float* outbuffer, unsigned int length, unsigned int outchannels)
        {
            assert(length <= fNumFrames);
            unsigned int C = std::min(outchannels, fNumChannels);
            unsigned int F = std::min(length, fNumFrames);
            
            for (unsigned int f = 0; f < F; f++) {
                unsigned int p = f * outchannels;
                for (unsigned int c = 0; c < C; c++) {
                    outbuffer[p++] = fChannels[c][f];
                }
                for (unsigned int c = C; c < outchannels; c++) {
                    outbuffer[p++] = 0;
                }
            }
        }
        
        //----------------------------------------------------------------------------------------
        // buffers: the internal buffers ready to use in the compute() method of a Faust dsp
        
        FAUSTFLOAT** buffers() { return fChannels; }
};

#endif
