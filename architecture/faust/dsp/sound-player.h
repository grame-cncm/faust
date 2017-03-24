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

 ************************************************************************
 ************************************************************************/

#ifndef __sound_player__
#define __sound_player__

#include <sndfile.h>
#include <string>
#include <iostream>

#include "faust/dsp/dsp.h"

#ifdef FAUSTFLOAT
    #if (FAUSTFLOAT == float)
        #define SND_READ sf_readf_float
    #else
        #define SND_READ sf_readf_double
    #endif
#endif

#define BUFFER_SIZE 512

/**
* LibSndfile based player
*/

class sound_player : public dsp {
    
    private:
    
        SF_INFO fInfo;
        SNDFILE* fFile;
        std::string fFileName;
        int fSamplingFreq;
        int fFrames;            // File current frame while playing (starts at fInfo.frames, ends at 0)
        FAUSTFLOAT** fBuffer;   // Buffer of non-interleased frames
    
        // Zones for UI management
        FAUSTFLOAT fPlayButton;
        FAUSTFLOAT fLoopButton;
        FAUSTFLOAT fSpeedSlider;
    
        void playSlice(int count, int src, int dst, FAUSTFLOAT** outputs)
        {
            for (int i = 0; i < fInfo.channels; i++) {
                memcpy(&(outputs[i])[dst], &(fBuffer[i])[src], sizeof(FAUSTFLOAT) * count);
            }
        }
    
        void clearSlice(int count, int dst, FAUSTFLOAT** outputs)
        {
            for (int i = 0; i < fInfo.channels; i++) {
                memset(&(outputs[i])[dst], 0, sizeof(FAUSTFLOAT) * count);
            }
        }

    public:

        sound_player(const std::string& filename)
        {
            fFileName = filename;
            fSamplingFreq = -1;
            
            fFile = sf_open(fFileName.c_str(), SFM_READ, &fInfo);
            if (!fFile) {
                std::cerr << sf_strerror(fFile) << std::endl;
                throw std::bad_alloc();
            }
            
            fBuffer = new FAUSTFLOAT*[fInfo.channels];
            for (int chan = 0; chan < fInfo.channels; chan++) {
                fBuffer[chan] = new FAUSTFLOAT[fInfo.frames];
            }
            
            FAUSTFLOAT buffer[BUFFER_SIZE * fInfo.channels];
            sf_count_t nbf;
            int dst = 0;

            do {
                // Read buffer
                nbf = SND_READ(fFile, buffer, BUFFER_SIZE);
                // Deinterleave it
                for (int chan = 0; chan < fInfo.channels; chan++) {
                    for (int frame = 0; frame < nbf; frame++) {
                        fBuffer[chan][dst + frame] = buffer[frame * fInfo.channels + chan];
                    }
                }
                // Move write index
                dst += nbf;
            } while (nbf == BUFFER_SIZE);
        }
    
        virtual ~sound_player()
        {
            for (int i = 0; i < fInfo.channels; i++) {
                delete [] fBuffer[i];
            }
            delete [] fBuffer;
            sf_close(fFile);
        }

        int getNumInputs() { return 0; }
        int getNumOutputs() { return fInfo.channels; }
    
        void buildUserInterface(UI* ui_interface)
        {
            ui_interface->openVerticalBox("Transport");
            ui_interface->addCheckButton("Play", &fPlayButton);
            ui_interface->addCheckButton("Loop", &fLoopButton);
            ui_interface->addHorizontalSlider("Speed", &fSpeedSlider, FAUSTFLOAT(1), FAUSTFLOAT(0.5), FAUSTFLOAT(2), FAUSTFLOAT(0.1));
            ui_interface->closeBox();
        }
    
        int getSampleRate() { return fSamplingFreq; }
    
        static void classInit(int samplingFreq) {}
    
        void init(int samplingFreq)
        {
            classInit(samplingFreq);
            instanceInit(samplingFreq);
        }
    
        void instanceInit(int samplingFreq)
        {
            instanceConstants(samplingFreq);
            instanceResetUserInterface();
            instanceClear();
        }
    
        void instanceConstants(int samplingFreq)
        {
            fSamplingFreq = samplingFreq;
        }
    
        void instanceResetUserInterface()
        {
            fPlayButton = FAUSTFLOAT(0);
            fLoopButton = FAUSTFLOAT(0);
            fSpeedSlider = FAUSTFLOAT(1);
        }
    
        void instanceClear()
        {
            fFrames = fInfo.frames;
        }
    
        sound_player* clone() { return new sound_player(fFileName); }
      
        void metadata(Meta* m)
        {
            m->declare("name", fFileName.c_str());
        }
    
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            if (fPlayButton == FAUSTFLOAT(1)) {
                int rcount = std::min(count, fFrames);
                playSlice(rcount, fInfo.frames - fFrames, 0, outputs);
                if (rcount < count) {
                    if (fLoopButton == FAUSTFLOAT(1)) {
                        // Loop buffer
                        playSlice(count - rcount, 0, rcount, outputs);
                        fFrames = fInfo.frames - (count - rcount);
                    } else {
                        // Otherwise clear end of buffer and stops
                        clearSlice(count - rcount, rcount, outputs);
                        fFrames = fInfo.frames;
                        fPlayButton = 0;
                    }
                } else {
                    fFrames -= count;
                }
            } else {
                // Clear output
                clearSlice(count, 0, outputs);
            }
        }
    
};

#endif
