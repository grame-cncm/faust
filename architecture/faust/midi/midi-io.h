//*****************************************//
//  cmidiin.cpp
//  by Gary Scavone, 2003-2004.
//
//  Simple program to test MIDI input and
//  use of a user callback function.
//
//*****************************************//

#include <iostream>
#include <cstdlib>
#include "faust/midi/RtMidi.cpp"
#include "faust/midi/midi.h"

class MidiIO : public midi {

    private:
    
        RtMidiIn* fInput;
        RtMidiOut* fOutput;
        vector<midi*> fMidiInputs;
        
        static void midiCallback(double deltatime, std::vector<unsigned char>* message, void* arg)
        {
            MidiIO* midi = static_cast<MidiIO*>(arg);
            unsigned int nBytes = message->size();
            
            int cmd = (int)message->at(0) >> 4;
            int channel = (int)message->at(0) & 0xf;
            
            if (nBytes == 2) {
             
                int data1 = (int)message->at(1);
                if (cmd == 12) {
                    for (int  i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->progChange(channel, data1);
                    }
                }
            
            } else if (nBytes == 3) {
            
                int data1 = (int)message->at(1);
                int data2 = (int)message->at(2);
                if (channel == 9) {
                    return;
                } else if (cmd == 8 || ((cmd == 9) && (data2 == 0))) { 
                    for (int  i = 0; i < midi->fMidiInputs.size(); i++) {
                         midi->fMidiInputs[i]->keyOff(channel, data1, data2);
                    }
                } else if (cmd == 9) {
                    for (int  i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->keyOn(channel, data1, data2);
                    }
                } else if (cmd == 11) {
                    for (int  i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->ctrlChange(channel, data1, data2);
                    }
                } else if (cmd == 14) {
                    for (int  i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->pitchWheel(channel, ((data2 * 128.0 + data1) - 8192) / 8192.0);
                    }
                }
                
            } else {
                 cout << "long message : " << nBytes << endl;
            }
        }
        
        bool chooseMidiInputPort()
        {
            // opens a virtual port when available on API
            fInput->openVirtualPort();
            
            /*
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
            */

            return true;
        }
        
        bool chooseMidiOutPort()
        {
            // opens a virtual port when available on API
            fOutput->openVirtualPort();
        
            /*
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
            */

            return true;
        }
    
    public:
    
        MidiIO():fInput(0), fOutput(0)
        {}
        
        virtual ~MidiIO()
        {}
        
        void addMidiIn(midi* dsp) { fMidiInputs.push_back(dsp); }
        
        bool start()
        {
            try {
            
                fInput = new RtMidiIn();
                if (!chooseMidiInputPort()) goto cleanup;
                fInput->setCallback(&midiCallback, this);
                
                fOutput = new RtMidiOut();
                if (!chooseMidiOutPort()) goto cleanup; 
                
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
            message.push_back(176);
            message.push_back(ctrl);
            message.push_back(val);
            fOutput->sendMessage(&message);
        }
        
        void progChange(int channel, int pgm) 
        {
            std::vector<unsigned char> message;
            message.push_back(192);
            message.push_back(pgm);
            fOutput->sendMessage(&message);
        }
        
        void keyOn(int channel, int note, int velocity) 
        {
            std::vector<unsigned char> message;
            message.push_back(144);
            message.push_back(note);
            message.push_back(velocity);
            fOutput->sendMessage(&message);
        }
        
        void keyOff(int channel, int note, int velocity) 
        {
            std::vector<unsigned char> message;
            message.push_back(128);
            message.push_back(note);
            message.push_back(velocity);
            fOutput->sendMessage(&message);
        }
        
        void pitchWheel(int channel, int wheel) {}
   
};

