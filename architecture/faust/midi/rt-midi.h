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
#include "faust/midi/RtMidi.cpp"
#include "faust/midi/midi.h"

class rtmidi : public midi {

    private:
    
        enum MidiStatus {
	
            // channel voice messages
            MIDI_NOTE_OFF           = 0x80, 
            MIDI_NOTE_ON            = 0x90, 
            MIDI_CONTROL_CHANGE     = 0xB0,
            MIDI_PROGRAM_CHANGE     = 0xC0,
            MIDI_PITCH_BEND         = 0xE0,
            MIDI_AFTERTOUCH         = 0xD0,	// aka channel pressure
            MIDI_POLY_AFTERTOUCH    = 0xA0	// aka key pressure

        };
  
        RtMidiIn* fInput;
        RtMidiOut* fOutput;
        std::vector<midi*> fMidiInputs;
        std::string fName;
        
        static void midiCallback(double deltatime, std::vector<unsigned char>* message, void* arg)
        {
            rtmidi* midi = static_cast<rtmidi*>(arg);
            unsigned int nBytes = message->size();
            
            int cmd = (int)message->at(0) & 0xf0;
            int channel = (int)message->at(0) & 0x0f;
            
            if (nBytes == 2) {
             
                int data1 = (int)message->at(1);
                if (cmd == MIDI_PROGRAM_CHANGE) {
                    for (int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->progChange(channel, data1);
                    }
                }
            
            } else if (nBytes == 3) {
            
                int data1 = (int)message->at(1);
                int data2 = (int)message->at(2);
                if (channel == 9) {
                    return;
                } else if (cmd == MIDI_NOTE_OFF || ((cmd == MIDI_NOTE_ON) && (data2 == 0))) { 
                    for (int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->keyOff(channel, data1, data2);
                    }
                } else if (cmd == MIDI_NOTE_ON) {
                    for (int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->keyOn(channel, data1, data2);
                    }
                } else if (cmd == MIDI_CONTROL_CHANGE) {
                    for (int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->ctrlChange(channel, data1, data2);
                    }
                } else if (cmd == MIDI_PITCH_BEND) {
                    for (int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->pitchWheel(channel, ((data2 * 128.0 + data1) - 8192) / 8192.0);
                    }
                }
                
            } else {
                 std::cout << "long message : " << nBytes << std::endl;
            }
        }
        
        bool chooseMidiInputPort(const std::string& name)
        {
         #if TARGET_OS_IPHONE
            unsigned int i = 0, nPorts = fInput->getPortCount();
            if (nPorts == 0) {
                std::cout << "No input ports available!" << std::endl;
                return false;
            }
            for (i = 0; i < nPorts; i++) {
                std::string portName = fInput->getPortName(i);
                std::cout << "Input port #" << i << ": " << portName << '\n';
                fInput->openPort(i);
            }
        #else
            // opens a virtual port when available on API
            fInput->openVirtualPort(name);
        #endif   
            return true;
        }
        
        bool chooseMidiOutPort(const std::string& name)
        {
        #if TARGET_OS_IPHONE  
            unsigned int i = 0, nPorts = fOutput->getPortCount();
            if (nPorts == 0) {
                std::cout << "No output ports available!" << std::endl;
                return false;
            }
            for (i = 0; i < nPorts; i++) {
                std::string portName = fOutput->getPortName(i);
                std::cout << "Output port #" << i << ": " << portName << '\n';
                fOutput->openPort(i);
            }
        #else 
            // opens a virtual port when available on API
            fOutput->openVirtualPort(name);
        #endif 
            return true;
        }
    
    public:
    
        rtmidi(const std::string& name = "RtMidi"):fInput(0), fOutput(0), fName(name)
        {}
        
        virtual ~rtmidi()
        {
            stop();
        }
        
        void addMidiIn(midi* midi_dsp) { fMidiInputs.push_back(midi_dsp); }
        
        bool start()
        {
            try {
            
                fInput = new RtMidiIn();
                if (!chooseMidiInputPort(fName)) goto cleanup;
                fInput->setCallback(&midiCallback, this);
                
                fOutput = new RtMidiOut();
                if (!chooseMidiOutPort(fName)) goto cleanup; 
                
                return true;
                
            } catch (RtMidiError &error) {
                error.printMessage();
                return false;
            }
            
        cleanup:

            delete fInput;
            delete fOutput;
            return false;
        }
        
        void stop()
        {
            delete fInput;
            delete fOutput;
            fInput = 0;
            fOutput = 0;
        }
        
        void ctrlChange(int channel, int ctrl, int val) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_CONTROL_CHANGE + channel);
            message.push_back(ctrl);
            message.push_back(val);
            fOutput->sendMessage(&message);
        }
        
        void progChange(int channel, int pgm) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_PROGRAM_CHANGE + channel);
            message.push_back(pgm);
            fOutput->sendMessage(&message);
        }
        
        void keyOn(int channel, int note, int velocity) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_NOTE_ON + channel);
            message.push_back(note);
            message.push_back(velocity);
            fOutput->sendMessage(&message);
        }
        
        void keyOff(int channel, int note, int velocity) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_NOTE_OFF + channel);
            message.push_back(note);
            message.push_back(velocity);
            fOutput->sendMessage(&message);
        }
        
        void pitchWheel(int channel, int wheel) 
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_PITCH_BEND + channel);
            message.push_back(wheel & 0x7F);		// lsb 7bit
            message.push_back((wheel >> 7) & 0x7F);	// msb 7bit
            fOutput->sendMessage(&message);
        }
   
};

#endif // __rt_midi__