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
  
        std::vector<RtMidiIn*> fInput;
        std::vector<RtMidiOut*> fOutput;
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
                } else if (cmd == MIDI_AFTERTOUCH) {
                    for (int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->chanPress(channel, data1);
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
                } else if (cmd == MIDI_POLY_AFTERTOUCH) {
                    for (int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->keyPress(channel, data1, data2);
                    }
                }
                
            } else {
                 std::cout << "long message : " << nBytes << std::endl;
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
            for (int i = 0; i < nInPorts; i++) {
                RtMidiIn* midi_in = new RtMidiIn();
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
            for (int i = 0; i < nOutPorts; i++) {
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
    
        rtmidi(const std::string& name = "RtMidi"):fName(name)
        {}
        
        virtual ~rtmidi()
        {
            stop();
        }
        
        void addMidiIn(midi* midi_dsp) { fMidiInputs.push_back(midi_dsp); }
        
        bool start()
        {
            try {
            
            #if TARGET_OS_IPHONE
                if (!openMidiInputPorts()) goto cleanup;
                if (!openMidiOutputPorts()) goto cleanup;
            #else
                chooseMidiInputPort(fName);
                chooseMidiOutPort(fName);
            #endif
                return true;
                
            } catch (RtMidiError &error) {
                error.printMessage();
                return false;
            }
            
        cleanup:
            stop();
            return false;
        }
        
        void stop()
        {
            std::vector<RtMidiIn*>::iterator it1;
            for (it1 = fInput.begin(); it1 != fInput.end(); it1++) {
                delete (*it1);
            }
            std::vector<RtMidiOut*>::iterator it2;
            for (it2 = fOutput.begin(); it2 != fOutput.end(); it2++) {
                delete (*it2);
            }
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
   
};

#endif // __rt_midi__