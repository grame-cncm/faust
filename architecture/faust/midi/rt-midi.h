/************************** BEGIN rt-midi.h **************************/
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
 
#ifndef __rt_midi__
#define __rt_midi__ 
 
#include <iostream>
#include <cstdlib>
#include "faust/midi/RtMidi.h"
#include "faust/midi/midi.h"

class MapUI;

//-------------------------------------------------
// MIDI input/output handling using RtMidi library
//-------------------------------------------------

class rt_midi : public midi_handler {

    private:
    
        std::vector<RtMidiIn*> fInput;
        std::vector<RtMidiOut*> fOutput;
        bool fIsVirtual;
        bool fPolling;
    
        static void midiCallback(double time, std::vector<unsigned char>* message, void* arg)
        {
            rt_midi* midi = static_cast<rt_midi*>(arg);
            size_t nBytes = message->size();
            int type = (int)message->at(0) & 0xf0;
            int channel = (int)message->at(0) & 0x0f;
            
            // MIDI sync
            if (nBytes == 1) {
                midi->handleSync(time, (int)message->at(0));
            // One data byte messages
            } else if (nBytes == 2) {
                midi->handleData1(time, type, channel, (int)message->at(1));
            // Two data bytes messages
            } else if (nBytes == 3) {
                midi->handleData2(time, type, channel, (int)message->at(1), (int)message->at(2));
            } else {
                midi->handleMessage(time, (int)message->at(0), *message);
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
                if (!fPolling) {
                    midi_in->setCallback(&midiCallback, this);
                }
                //std::cout << "Input port #" << i << ": " << midi_in->getPortName(i) << '\n';
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
                //std::cout << "Output port #" << i << ": " << midi_out->getPortName(i) << '\n';
            }
            return true;
        }
        
        void chooseMidiInputPort(const std::string& name)
        {
            RtMidiIn* midi_in = new RtMidiIn();
            midi_in->ignoreTypes(true, false, true);
            fInput.push_back(midi_in);
            if (!fPolling) {
                midi_in->setCallback(&midiCallback, this);
            }
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
            for (auto& it : fOutput) {
                it->sendMessage(&message);
            }
        }
    
    public:
    
        rt_midi(const std::string& name = "RtMidi",
                bool is_virtual = false,
                bool is_polling = false)
        :midi_handler(name), fIsVirtual(is_virtual), fPolling(is_polling)
        {}
        
        virtual ~rt_midi()
        {
            stopMidi();
        }
        
        bool startMidi()
        {
            try {
            
            #if TARGET_OS_IPHONE
                if (!openMidiInputPorts())  { stopMidi(); return false; }
                if (!openMidiOutputPorts()) { stopMidi(); return false; }
            #else
                if (fIsVirtual) {
                    chooseMidiInputPort(fName);
                    chooseMidiOutPort(fName);
                } else {
                    if (!openMidiInputPorts())  { stopMidi(); return false; }
                    std::cerr << "Warning : MIDI outputs are not started in this mode !\n";
                }
            #endif
                return true;
                
            } catch (RtMidiError &error) {
                error.printMessage();
                stopMidi();
                return false;
            }
        }
        
        void stopMidi()
        {
            for (auto& it1 : fInput) {
                delete it1;
            }
            fInput.clear();
            for (auto& it2 : fOutput) {
                delete it2;
            }
            fOutput.clear();
        }
    
        // To be used in polling mode
        int recvMessages(std::vector<MIDIMessage>* messages)
        {
            int count = 0;
            double first_time_stamp = 0.;
            for (auto& it : fInput) {
                std::vector<unsigned char> message;
                double time_stamp = (uint32_t)it->getMessage(&message);
                // Small messages
                if (message.size() > 0) {
                    if (count == 0) first_time_stamp = time_stamp;
                    MIDIMessage& mes = messages->at(count++);
                    mes.frameIndex = (uint32_t)(time_stamp - first_time_stamp);
                    mes.byte0 = message[0];
                    mes.byte1 = message[1];
                    mes.byte2 = message[2];
                }
            }
            return count;
        }
    
        void sendMessages(std::vector<MIDIMessage>* messages, int count)
        {
            for (int i = 0; i < count; ++i) {
                MIDIMessage mes1 = (*messages)[i];
                std::vector<unsigned char> mes2;
                mes2.push_back(mes1.byte0);
                mes2.push_back(mes1.byte1);
                mes2.push_back(mes1.byte2);
                sendMessage(mes2);
            }
        }
    
        // MIDI output API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_NOTE_ON + channel);
            message.push_back(pitch);
            message.push_back(velocity);
            sendMessage(message);
            return 0;
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
         
        void startSync(double date)
        {
            std::vector<unsigned char> message;
            message.push_back(MIDI_START);
            sendMessage(message);
        }
       
        void stopSync(double date)
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
    
        void sysEx(double, std::vector<unsigned char>& message)
        {
            sendMessage(message);
        }
    
};


#endif // __rt_midi__
/**************************  END  rt-midi.h **************************/
