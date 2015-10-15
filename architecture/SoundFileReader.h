/*

Copyright (C) Grame 2015

This library is free software; you can redistribute it and modify it under
the terms of the GNU Library General Public License as published by the
Free Software Foundation version 2 of the License, or any later version.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
for more details.

You should have received a copy of the GNU Library General Public License
along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
research@grame.fr

*/

#ifndef __SoundFileReader__
#define __SoundFileReader__

#include <assert.h>
#include <sndfile.h>

#define BUFFER_SIZE 1024

struct SoundFileReader {

    float** fBuffer;
    SNDFILE* fSoundFile;
    int fChannels;
    int fFramesNum;
    
    SoundFileReader(const char* name)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        fSoundFile = sf_open(name, SFM_READ, &snd_info);
        
        if (!fSoundFile) {
            printf("soundfile '%s' cannot be opened\n", name);
            throw -1;
        }
        
        fChannels = snd_info.channels;
        fFramesNum = snd_info.frames;
        
        fBuffer = new float*[fChannels];
        assert(fBuffer);
        for (int i = 0; i < fChannels; i++) {
            fBuffer[i] = new float[fFramesNum];
            assert(fBuffer[i]);
        }
        
        // Read file in memory
        int nbf, cur_index = 0;
        float buffer[BUFFER_SIZE * fChannels];
        do {
            nbf = sf_readf_float(fSoundFile, buffer, BUFFER_SIZE);
            for (int i = 0; i < fChannels; i++) {
                for (int j = 0; j < nbf; j++) {
                    fBuffer[i][cur_index + j] = buffer[i * fChannels + j];
                }
            }
            cur_index += nbf;
        } while (nbf == BUFFER_SIZE);
    }
    
    virtual ~SoundFileReader()
    {
        for (int i = 0; i < fChannels; i++) {
            delete [] fBuffer[i];
        }
        delete [] fBuffer;
    }
    
    int Size()
    {
        return fFramesNum; 
    }
    
    float Sample(int channel, int index)
    {   
        assert(channel >= 0 && channel < fChannels);
        assert(index >= 0 && index < fFramesNum);
        return fBuffer[channel][index];
    }
    
};

#endif
