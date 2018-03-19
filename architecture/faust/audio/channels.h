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

#ifndef __audio_channels__
#define __audio_channels__

#include <string.h>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class channels
{
    private:
    
        int fNumFrames;
        int fNumChannels;
        FAUSTFLOAT** fBuffers;

    public:

        channels(int nframes, int nchannels)
        {
            fBuffers = new FAUSTFLOAT*[nchannels];
            fNumFrames = nframes;
            fNumChannels = nchannels;

            // allocate audio channels
            for (int chan = 0; chan < fNumChannels; chan++) {
                fBuffers[chan] = new FAUSTFLOAT[fNumFrames];
            }
            
            zero();
        }

        void zero()
        {
            // allocate audio channels
            for (int chan = 0; chan < fNumChannels; chan++) {
                memset(fBuffers[chan], 0, sizeof(FAUSTFLOAT) * fNumFrames);
            }
        }

        void impulse()
        {
            // allocate audio channels
            for (int chan = 0; chan < fNumChannels; chan++) {
                fBuffers[chan][0] = FAUSTFLOAT(1.0);
                for (int frame = 1; frame < fNumFrames; frame++) {
                    fBuffers[chan][frame] = FAUSTFLOAT(0.0);
                }
            }
        }
    
        void display()
        {
            for (int chan = 0; chan < fNumChannels; chan++) {
                for (int frame = 0; frame < fNumFrames; frame++) {
                    std::cout << "chan = " << chan << " frame = " << frame << " value = " << fBuffers[chan][frame] << std::endl;
                }
            }
        }

        virtual ~channels()
        {
            // free separate input channels
            for (int chan = 0; chan < fNumChannels; chan++) {
                delete [] fBuffers[chan];
            }
            delete [] fBuffers;
        }

        FAUSTFLOAT** buffers() { return fBuffers; }
    
};

#endif

