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
#include "faust/audio/poly-dsp.h"

class MidiIO {

    private:
    
        RtMidiIn* fMIDI;
        midi* fDSP;
        
        static void midiCallback(double deltatime, std::vector<unsigned char>* message, void* arg)
        {
            MidiIO* midi = static_cast<MidiIO*>(arg);
            unsigned int nBytes = message->size();
            
            int cmd = (int)message->at(0) >> 4;
            int channel = (int)message->at(0) & 0xf;
            
            if (nBytes == 2) {
             
                int data1 = (int)message->at(1);
                if (cmd == 12) {
                    midi->fDSP->progChange(channel, data1);
                }
            
            } else if (nBytes == 3) {
            
                int data1 = (int)message->at(1);
                int data2 = (int)message->at(2);
                if (channel == 9) {
                    return;
                } else if (cmd == 8 || ((cmd == 9) && (data2 == 0))) { 
                    midi->fDSP->keyOff(channel, data1);
                } else if (cmd == 9) {
                    midi->fDSP->keyOn(channel, data1, data2);
                } else if (cmd == 11) {
                    midi->fDSP->ctrlChange(channel, data1, data2);
                } else if (cmd == 14) {
                    midi->fDSP->pitchWheel(channel, ((data2 * 128.0 + data1) - 8192) / 8192.0);
                }
                
            } else {
                 cout << "long message : " << nBytes << endl;
            }
        }
        
        bool chooseMidiPort()
        {
            // oppen a virtual port when available on API
            fMIDI->openVirtualPort();
            
            unsigned int i = 0, nPorts = fMIDI->getPortCount();
            
            if (nPorts == 0) {
                std::cout << "No input ports available!" << std::endl;
                return false;
            }
            
            for (i = 0; i < nPorts; i++) {
                std::string portName = fMIDI->getPortName(i);
                std::cout << "Input port #" << i << ": " << portName << '\n';
                fMIDI->openPort(i);
            }

            return true;
        }
    
    public:
    
        MidiIO(midi* dsp):fMIDI(0), fDSP(dsp)
        {}
        
        virtual ~MidiIO()
        {}
        
        bool start()
        {
            try {
            
                fMIDI = new RtMidiIn();
                if (!chooseMidiPort()) goto cleanup;
                fMIDI->setCallback(&midiCallback, this);
                return true;
                
            } catch (RtMidiError &error) {
                error.printMessage();
                return false;
            }
            
        cleanup:

            delete fMIDI;
            return false;
        }
        
        void stop()
        {
            delete fMIDI;
            fMIDI = 0;
        }
   
};

