/************************************************************************
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

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
#ifndef __rt_midi__
#define __rt_midi__ 
 
#include <iostream>
#include <cstdlib>
#include "faust/midi/RtMidi.h"
#include "faust/midi/midi.h"

class rt_midi : public midi_handler {

    private:
    
        std::vector<RtMidiIn*> fInput;
        std::vector<RtMidiOut*> fOutput;
        
        static void midiCallback(double time, std::vector<unsigned char>* message, void* arg)
        {
            rt_midi* midi = static_cast<rt_midi*>(arg);
            unsigned int nBytes = message->size();
            
            int cmd = (int)message->at(0) & 0xf0;
            int channel = (int)message->at(0) & 0x0f;
            
            // MIDI sync
            if (nBytes == 1) {
            
                int sync = (int)message->at(0);
                if (sync == MIDI_CLOCK) {
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->clock(time);
                    }
                } else if (sync == MIDI_START) {
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->start(time);
                    }
                } else if (sync == MIDI_STOP) {
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->stop(time);
                    }
                }
                
            } else if (nBytes == 2) {
             
                int data1 = (int)message->at(1);
                
                if (cmd == MIDI_PROGRAM_CHANGE) {
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->progChange(time, channel, data1);
                    }
                } else if (cmd == MIDI_AFTERTOUCH) {
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->chanPress(time, channel, data1);
                    }
                }
            
            } else if (nBytes == 3) {
            
                int data1 = (int)message->at(1);
                int data2 = (int)message->at(2);
                
                if (cmd == MIDI_NOTE_OFF || ((cmd == MIDI_NOTE_ON) && (data2 == 0))) { 
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->keyOff(time, channel, data1, data2);
                    }
                } else if (cmd == MIDI_NOTE_ON) {
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->keyOn(time, channel, data1, data2);
                    }
                } else if (cmd == MIDI_CONTROL_CHANGE) {
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                    }
                } else if (cmd == MIDI_PITCH_BEND) {
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->pitchWheel(time, channel, ((data2 * 128.0 + data1) - 8192) / 8192.0);
                    }
                } else if (cmd == MIDI_POLY_AFTERTOUCH) {
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->keyPress(time, channel, data1, data2);
                    }
                }
            } 
        }
        
        bool openMidiInputPorts()
        {
            // Get number of input ports
            RtMidiIn midi_in;
            unsigned nInPorts = midi_in.getPortCount();
            if (nInPorts == 0) {
                std::cout << "No input ports available!" << std::endl;
                return false;
            }
    
            // Then open all of them
            for (unsigned int i = 0; i < nInPorts; i++) {
                RtMidiIn* midi_in = new RtMidiIn();
                midi_in->ignoreTypes(true, false, true);
                fInput.push_back(midi_in);
                midi_in->openPort(i);
                midi_in->setCallback(&midiCallback, this);
                std::string portName = midi_in->getPortName(i);
                std::cout << "Input port #" << i << ": " << portName << '\n';
            }
            return true;
        }
        
        bool openMidiOutputPorts()
        {
            // Get number of output ports
            RtMidiOut midi_out;
            unsigned nOutPorts = midi_out.getPortCount();
            if (nOutPorts == 0) {
                std::cout << "No output ports available!" << std::endl;
                return false;
            }
    
            // Then open all of them
            for (unsigned int i = 0; i < nOutPorts; i++) {
                RtMidiOut* midi_out = new RtMidiOut();
                fOutput.push_back(midi_out);
                midi_out->openPort(i);
                std::string portName = midi_out->getPortName(i);
                std::cout << "Output port #" << i << ": " << portName << '\n';
            }
            return true;
        }
        
        void chooseMidiInputPort(const std::string& name)
        {
            RtMidiIn* midi_in = new RtMidiIn();
            midi_in->ignoreTypes(true, false, true);
            fInput.push_back(midi_in);
            midi_in->setCallback(&midiCallback, this);
            midi_in->openVirtualPort(name);
        }
        
        void chooseMidiOutPort(const std::string& name)
        {
            RtMidiOut* midi_out = new RtMidiOut();
            fOutput.push_back(midi_out);
            midi_out->openVirtualPort(name);
        }
        
        void sendMessage(std::vector<unsigned char>& message)
        {
            std::vector<RtMidiOut*>::iterator it;
            for (it = fOutput.begin(); it != fOutput.end(); it++) {
                (*it)->sendMessage(&message);
            }
        }
    
    public:
    
        rt_midi(const std::string& name = "RtMidi"):midi_handler(name)
        {}
        
        virtual ~rt_midi()
        {
            stop();
        }
        
        bool start()
        {
            try {
            
            #if TARGET_OS_IPHONE
                if (!openMidiInputPorts())  { stop(); return false; }
                if (!openMidiOutputPorts()) { stop(); return false; }
            #else
                chooseMidiInputPort(fName);
                chooseMidiOutPort(fName);
            #endif
                return true;
                
            } catch (RtMidiError &error) {
                error.printMessage();
                stop();
                return false;
            }
        }
        
        void stop()
        {
            std::vector<RtMidiIn*>::iterator it1;
            for (it1 = fInput.begin(); it1 != fInput.end(); it1++) {
                delete (*it1);
            }
            fInput.clear();
            
            std::vector<RtMidiOut*>::iterator it2;
            for (it2 = fOutput.begin(); it2 != fOutput.end(); it2++) {
                delete (*it2);
            }
            fOutput.clear();
        }
        
        void keyOn(int channel, int pitch, int velocity) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_NOTE_ON + channel);
            message.push_back(pitch);
            message.push_back(velocity);
            sendMessage(message);
        }
        
        void keyOff(int channel, int pitch, int velocity) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_NOTE_OFF + channel);
            message.push_back(pitch);
            message.push_back(velocity);
            sendMessage(message);
        }
        
        void ctrlChange(int channel, int ctrl, int val) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_CONTROL_CHANGE + channel);
            message.push_back(ctrl);
            message.push_back(val);
            sendMessage(message);
        }
        
        void chanPress(int channel, int press) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_AFTERTOUCH + channel);
            message.push_back(press);
            sendMessage(message);
        }
        
        void progChange(int channel, int pgm) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_PROGRAM_CHANGE + channel);
            message.push_back(pgm);
            sendMessage(message);
        }
          
        void keyPress(int channel, int pitch, int press) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_POLY_AFTERTOUCH + channel);
            message.push_back(pitch);
            message.push_back(press);
            sendMessage(message);
        }
   
        void pitchWheel(int channel, int wheel) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_PITCH_BEND + channel);
            message.push_back(wheel & 0x7F);		// lsb 7bit
            message.push_back((wheel >> 7) & 0x7F);	// msb 7bit
            sendMessage(message);
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value) {}
         
        void start(double date) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_START);
            sendMessage(message);
        }
       
        void stop(double date) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_STOP);
            sendMessage(message);
        }
        
        void clock(double date) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_CLOCK);
            sendMessage(message);
        }
        
};

#if __APPLE__
    #if TARGET_OS_IPHONE
    inline double GetCurrentTimeInUsec() { return double(CAHostTimeBase::GetCurrentTimeInNanos()) / 1000.; }
#else
    #include <CoreAudio/HostTime.h>
    inline double GetCurrentTimeInUsec() { return double(AudioConvertHostTimeToNanos(AudioGetCurrentHostTime())) / 1000.; }
#endif
#endif

#if __linux__
#include <sys/time.h>
inline double GetCurrentTimeInUsec() 
{
    struct timeval tv;
    (void)gettimeofday(&tv, (struct timezone *)NULL);
    return double((tv.tv_sec * 1000000) + tv.tv_usec);
}
#endif

#if _WIN32
inline double GetCurrentTimeInUsec(void)
{
    LARGE_INTEGER time;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);
    return double(time.QuadPart) / double(frequency.QuadPart) * 1000000.0;
}
#endif
#endif // __rt_midi__
