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

#ifndef __sound_player__
#define __sound_player__

#include <sndfile.h>
#include <string>
#include <iostream>
#include <mutex>

#include "faust/dsp/dsp.h"
#include "faust/gui/ring-buffer.h"

#define BUFFER_SIZE 512
#define RING_BUFFER_SIZE BUFFER_SIZE * 32
#define HALF_RING_BUFFER_SIZE RING_BUFFER_SIZE / 2

/**
 * LibSndfile based player
 */

class sound_base_player : public dsp {
    
    protected:
    
        typedef sf_count_t (* sample_read)(SNDFILE* sndfile, FAUSTFLOAT* ptr, sf_count_t frames);
        
        SF_INFO fInfo;
        SNDFILE* fFile;
        std::string fFileName;
        int fSamplingRate;
    
        // File current frame while playing
        FAUSTFLOAT fCurFrames;
        
        // Zones for UI management
        FAUSTFLOAT fPlayButton;
        FAUSTFLOAT fLoopButton;
        FAUSTFLOAT fSetFrames;
        FAUSTFLOAT fLastSetFrames;
    
        // To protect position change
        std::mutex fMutex;
    
        // Generic reader function
        sample_read fReaderFun;
        
        virtual void playSlice(int count, int src, int dst, FAUSTFLOAT** outputs) {}
    
        virtual void setFrame(int frames) {}
    
        void clearSlice(int count, int dst, FAUSTFLOAT** outputs)
        {
            for (int i = 0; i < fInfo.channels; i++) {
                memset(&(outputs[i])[dst], 0, sizeof(FAUSTFLOAT) * count);
            }
        }
    
    public:
    
        sound_base_player(const std::string& filename)
        {
            fFileName = filename;
            fSamplingRate = -1;
            
            if (sizeof(FAUSTFLOAT) == 4) {
                fReaderFun = reinterpret_cast<sample_read>(sf_readf_float);
            } else {
                fReaderFun = reinterpret_cast<sample_read>(sf_readf_double);
            }
            
            fFile = sf_open(fFileName.c_str(), SFM_READ, &fInfo);
            if (!fFile) {
                std::cerr << sf_strerror(fFile) << std::endl;
                throw std::bad_alloc();
            }
        }
    
        virtual ~sound_base_player()
        {}
    
        virtual int getNumInputs() { return 0; }
        virtual int getNumOutputs() { return fInfo.channels; }
        
        virtual void buildUserInterface(UI* ui_interface)
        {
            ui_interface->openVerticalBox("Transport");
            ui_interface->addCheckButton("Play", &fPlayButton);
            ui_interface->addCheckButton("Loop", &fLoopButton);
            ui_interface->addHorizontalSlider("Set position", &fSetFrames, FAUSTFLOAT(0), FAUSTFLOAT(0), FAUSTFLOAT(fInfo.frames), FAUSTFLOAT(100));
            ui_interface->addHorizontalBargraph("Current position", &fCurFrames, FAUSTFLOAT(0), FAUSTFLOAT(fInfo.frames));
            ui_interface->closeBox();
        }
        
        virtual int getSampleRate() { return fSamplingRate; }
        
        static void classInit(int samplingRate) {}
        
        virtual void init(int samplingRate)
        {
            classInit(samplingRate);
            instanceInit(samplingRate);
        }
        
        virtual void instanceInit(int samplingRate)
        {
            instanceConstants(samplingRate);
            instanceResetUserInterface();
            instanceClear();
        }
        
        virtual void instanceConstants(int samplingRate)
        {
            fSamplingRate = samplingRate;
        }
        
        virtual void instanceResetUserInterface()
        {
            // Play and loop by default
            fPlayButton = FAUSTFLOAT(1);
            fLoopButton = FAUSTFLOAT(1);
            fSetFrames = FAUSTFLOAT(0);
            fLastSetFrames = FAUSTFLOAT(0);
        }
        
        virtual void instanceClear()
        {
            fCurFrames = FAUSTFLOAT(0);
        }
    
        virtual sound_base_player* clone() { return new sound_base_player(fFileName); }
        
        virtual void metadata(Meta* m)
        {
            m->declare("name", fFileName.c_str());
        }
        
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            if (fPlayButton == FAUSTFLOAT(1) && fMutex.try_lock()) {
                
                int rcount = std::min(count, int(fInfo.frames - fCurFrames));
                playSlice(rcount, fCurFrames, 0, outputs);
                
                if (rcount < count) {
                    if (fLoopButton == FAUSTFLOAT(1)) {
                        // Loop buffer
                        playSlice(count - rcount, 0, rcount, outputs);
                        fCurFrames = count - rcount;
                    } else {
                        // Otherwise clear end of buffer and stops
                        clearSlice(count - rcount, rcount, outputs);
                        fCurFrames =  FAUSTFLOAT(0);
                        fPlayButton = 0;
                    }
                } else {
                    fCurFrames += count;
                }
                
                fMutex.unlock();
                
            } else {
                // Clear output
                clearSlice(count, 0, outputs);
            }
        }
    
        static void setFrame(FAUSTFLOAT val, void* arg)
        {
            static_cast<sound_base_player*>(arg)->setFrame(int(val));
        }
    
        FAUSTFLOAT* getCurFramesZone()
        {
            return &fCurFrames;
        }
    
        FAUSTFLOAT* getSetFramesZone()
        {
            return &fSetFrames;
        }
   
};

/**
* Memory player
*/

class sound_memory_player : public sound_base_player {
    
    private:
    
        FAUSTFLOAT** fBuffer;   // Buffer of non-interleased frames
    
        void playSlice(int count, int src, int dst, FAUSTFLOAT** outputs)
        {
            for (int i = 0; i < fInfo.channels; i++) {
                memcpy(&(outputs[i])[dst], &(fBuffer[i])[src], sizeof(FAUSTFLOAT) * count);
            }
        }
    
        void setFrame(int frames)
        {
            // If position change
            if (fSetFrames != fLastSetFrames
                && std::abs(fSetFrames - fLastSetFrames) > BUFFER_SIZE
                && std::abs(fSetFrames - fCurFrames) > BUFFER_SIZE) {
                fMutex.lock();
                fLastSetFrames = fSetFrames;
                fCurFrames = fSetFrames;
                fMutex.unlock();
            }
        }
 
    public:

        sound_memory_player(const std::string& filename):sound_base_player(filename)
        {
            fBuffer = new FAUSTFLOAT*[fInfo.channels];
            for (int chan = 0; chan < fInfo.channels; chan++) {
                fBuffer[chan] = new FAUSTFLOAT[fInfo.frames];
            }
            
            FAUSTFLOAT buffer[BUFFER_SIZE * fInfo.channels];
            sf_count_t nbf, index = 0;
     
            do {
                // Read buffer
                nbf = fReaderFun(fFile, buffer, BUFFER_SIZE);
                // Deinterleave it
                for (int chan = 0; chan < fInfo.channels; chan++) {
                    for (int frame = 0; frame < nbf; frame++) {
                        fBuffer[chan][index + frame] = buffer[frame * fInfo.channels + chan];
                    }
                }
                // Move write index
                index += nbf;
            } while (nbf == BUFFER_SIZE);
        }
    
        virtual ~sound_memory_player()
        {
            for (int i = 0; i < fInfo.channels; i++) {
                delete [] fBuffer[i];
            }
            delete [] fBuffer;
            sf_close(fFile);
        }

        sound_memory_player* clone() { return new sound_memory_player(fFileName); }

};

/**
 * DirectToDisk player
 */

class sound_dtd_player : public sound_base_player {
    
    private:
        
        ringbuffer_t* fBuffer;  // Ringbuffer written in setFrame and read in playSlice
    
        void playSlice(int count, int src, int dst, FAUSTFLOAT** outputs)
        {
            size_t read_space_frames = convertToFrames(ringbuffer_read_space(fBuffer));
            
            if (read_space_frames >= count) {
                
                // Read from ringbuffer
                FAUSTFLOAT buffer[count * fInfo.channels];
                ringbuffer_read(fBuffer, (char*)buffer, convertFromFrames(count));
                
                // Deinterleave and write to output
                for (int chan = 0; chan < fInfo.channels; chan++) {
                    for (int frame = 0; frame < count; frame++) {
                        outputs[chan][dst + frame] = buffer[frame * fInfo.channels + chan];
                    }
                }
                
            } else {
                std::cerr << "PlaySlice : missing " << (count - read_space_frames) << " frames\n";
            }
        }
    
        size_t readAndwrite(FAUSTFLOAT* buffer, size_t size)
        {
            size_t nbf = fReaderFun(fFile, buffer, size);
            ringbuffer_write(fBuffer, (char*)buffer, convertFromFrames(nbf));
            return nbf;
        }
    
        void setFrame(int frames)
        {
            // If position change
            if (fSetFrames != fLastSetFrames
                && std::abs(fSetFrames - fLastSetFrames) > BUFFER_SIZE
                && std::abs(fSetFrames - fCurFrames) > BUFFER_SIZE) {
                fMutex.lock();
                // Reset ringbuffer
                ringbuffer_reset(fBuffer);
                // Reset fCurFrames and seek in the file
                fLastSetFrames = fSetFrames;
                sf_seek(fFile, fSetFrames, SEEK_SET);
                fCurFrames = fSetFrames;
                fMutex.unlock();
            }
            
            size_t write_space_frames = convertToFrames(ringbuffer_write_space(fBuffer));
            
            // If ringbuffer has to be filled
            if (write_space_frames > HALF_RING_BUFFER_SIZE) {
                FAUSTFLOAT buffer[HALF_RING_BUFFER_SIZE * fInfo.channels];
                // Tries to read and write HALF_RING_BUFFER_SIZE frames
                size_t nbf = readAndwrite(buffer, HALF_RING_BUFFER_SIZE);
                // End of file is reached
                if (nbf < HALF_RING_BUFFER_SIZE) {
                    // Read RING_BUFFER_SIZE/2 - nbf frame from the beginning of file
                    sf_seek(fFile, 0, SEEK_SET);
                    readAndwrite(buffer, HALF_RING_BUFFER_SIZE - nbf);
                }
            }
        }
    
        size_t convertToFrames(size_t bytes) { return bytes / (sizeof(FAUSTFLOAT) * fInfo.channels); }
        size_t convertFromFrames(size_t frames) { return frames * sizeof(FAUSTFLOAT) * fInfo.channels; }
  
    public:
        
        sound_dtd_player(const std::string& filename):sound_base_player(filename)
        {
            // Create ringbuffer
            fBuffer = ringbuffer_create(RING_BUFFER_SIZE * fInfo.channels * sizeof(FAUSTFLOAT));
            
            // Read first buffer
            setFrame(0);
        }
        
        virtual ~sound_dtd_player()
        {
            ringbuffer_free(fBuffer);
            sf_close(fFile);
        }
    
        sound_dtd_player* clone() { return new sound_dtd_player(fFileName); }
    
};

/**
    PositionManager is a GUI : changing the slider position of a sound_base_player
    (sound_memory_player or sound_dtd_player) will be reflected in the internal buffer
    position using the GUI::updateAllGuis mecanism.
 */

class PositionManager : public GUI {
    
    private:
        
        std::map<sound_base_player*, std::pair<uiCallbackItem*, uiCallbackItem*> > fFileReader;
        
    public:
        
        PositionManager()
        {}
        
        ~PositionManager()
        {}
    
        // Add a sound_base_player (sound_memory_player or sound_dtd_player) in the PositionManager
        void addDSP(sound_base_player* dsp)
        {
            fFileReader[dsp] = std::make_pair(new uiCallbackItem(this, dsp->getCurFramesZone(), sound_base_player::setFrame, dsp),
                                              new uiCallbackItem(this, dsp->getSetFramesZone(), sound_base_player::setFrame, dsp));
        }
    
        // Remove a sound_base_player (sound_memory_player or sound_dtd_player) from the PositionManager
        void removeDSP(sound_base_player* dsp)
        {
            fFileReader.erase(dsp);
        }
};

/*
 
 // A unique manager is usually needed
 PositionManager* manager = new PositionManager();
 
 // Create memory or DirectToDisk sound players
 dsp* player1 = new sound_dtd_player("toto.wav");
 dsp* player2 = new sound_memory_player("titi.flac");
 
 // Add sound_plays to the manager, so that position changes are reflected in the internal buffer
 manager->addDSP(player1);
 manager->addDSP(player2);
 
 // When player1 and player2 are no needed anymore, before deleting them:
 manager->removeDSP(player1);
 manager->removeDSP(player2);
 
 // When the application quits...
 delete manager;
 
*/

#endif
