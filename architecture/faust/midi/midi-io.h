//*****************************************//
//  cmidiin.cpp
//  by Gary Scavone, 2003-2004.
//
//  Simple program to test MIDI input and
//  use of a user callback function.
//
//*****************************************//

#define __MACOSX_CORE__ 1

#include <iostream>
#include <cstdlib>
#include "faust/midi/RtMidi.h"
#include "faust/midi/RtMidi.cpp"
#include "faust/audio/poly-dsp.h"

class MidiIO {

    private:
    
        RtMidiIn* fMIDI;
        mydsp_poly* fDSP;
        
        static void mycallback(double deltatime, std::vector<unsigned char>* message, void* arg)
        {
            MidiIO* midi = static_cast<MidiIO*>(arg);
            unsigned int nBytes = message->size();
            
            for (unsigned int i = 0; i < nBytes; i++) {
            
                int cmd = (int)message->at(0) >> 4;
                int channel = (int)message->at(0) & 0xf;
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
                    midi->fDSP->pitchWheel(channel, ((data2 * 128.0 + data1)-  8192) / 8192.0);
                }  
            }
        }
        
        bool chooseMidiPort()
        {
            fMIDI->openVirtualPort();
            unsigned int i = 0, nPorts = fMIDI->getPortCount();
            
            if (nPorts == 0) {
                std::cout << "No input ports available!" << std::endl;
                return false;
            }
            
            for (i = 0; i < nPorts; i++) {
                std::string portName = fMIDI->getPortName(i);
                std::cout << "  Input port #" << i << ": " << portName << '\n';
                fMIDI->openPort(i);
            }

            return true;
        }
    
    public:
    
        MidiIO(mydsp_poly* dsp):fMIDI(0), fDSP(dsp)
        {}
        
        virtual ~MidiIO()
        {}
        
        bool start()
        {
            try {
                // RtMidiIn constructor
                fMIDI = new RtMidiIn();
                
                // Call function to select port.
                if (!chooseMidiPort()) goto cleanup;

                // Set our callback function.  This should be done immediately after
                // opening the port to avoid having incoming messages written to the
                // queue instead of sent to the callback function.
                fMIDI->setCallback(&mycallback, this);
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

