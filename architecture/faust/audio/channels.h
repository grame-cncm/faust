/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

    ************************************************************************
    ************************************************************************/

#ifndef __audio_channels__
#define __audio_channels__

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
            for (int i = 0; i < fNumChannels; i++) {
                fBuffers[i] =  new FAUSTFLOAT[fNumFrames];
            }
        }

        void zero()
        {
            // allocate audio channels
            for (int i = 0; i < fNumChannels; i++) {
                for (int f = 0; f < fNumFrames; f++) {
                    fBuffers[i][f] = FAUSTFLOAT(0.0);
                }
            }
        }

        void impulse()
        {
            // allocate audio channels
            for (int i = 0; i < fNumChannels; i++) {
                fBuffers[i][0] = FAUSTFLOAT(1.0);
                for (int f = 1; f < fNumFrames; f++) {
                    fBuffers[i][f] = FAUSTFLOAT(0.0);
                }
            }
        }
    
        void display()
        {
            for (int i = 0; i < fNumChannels; i++) {
                for (int f = 0; f < fNumFrames; f++) {
                    std::cout << "chan = " << i << " frame = " << f << " value = " <<  fBuffers[i][f] << std::endl;
                }
            }
        }

        virtual ~channels()
        {
            // free separate input channels
            for (int i = 0; i < fNumChannels; i++) {
                delete [] fBuffers[i];
            }
            delete [] fBuffers;
        }

        FAUSTFLOAT** buffers() { return fBuffers; }
    
};

#endif

