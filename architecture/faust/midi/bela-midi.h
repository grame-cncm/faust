/************************** BEGIN bela-midi.h **************************/
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
 
#ifndef __bela_midi__
#define __bela_midi__ 
 
#include <iostream>
#include <cstdlib>
#include "Midi.h"
#include "faust/midi/midi.h"

class MapUI;

class bela_midi : public midi_handler {

    private:
    
        Midi fBelaMidi;
        
        static void midiCallback(MidiChannelMessage message, void* arg)
        {
            bela_midi* midi = static_cast<bela_midi*>(arg);
            
            switch (message.getType()) {
                case kmmNoteOff:
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->keyOff(0, message.getChannel(), message.getDataByte(0), message.getDataByte(1));
                    }
                    break;
                case kmmNoteOn:
                     for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        if (message.getDataByte(1) != 0) {
                            midi->fMidiInputs[i]->keyOn(0, message.getChannel(), message.getDataByte(0), message.getDataByte(1));
                        } else {
                            midi->fMidiInputs[i]->keyOff(0, message.getChannel(), message.getDataByte(0), message.getDataByte(1));
                        }
                    }
                    break;
                case kmmPolyphonicKeyPressure:
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->keyPress(0, message.getChannel(), message.getDataByte(0), message.getDataByte(1));
                    }
                    break;
                case kmmControlChange:
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->ctrlChange(0, message.getChannel(), message.getDataByte(0), message.getDataByte(1));
                    }
                    break;
                case kmmProgramChange:
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->progChange(0, message.getChannel(), message.getDataByte(0));
                    }
                    break;
                case kmmChannelPressure:
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->chanPress(0, message.getChannel(), message.getDataByte(0));
                    }
                    break;
                case kmmPitchBend:
                    for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                        midi->fMidiInputs[i]->pitchWheel(0, message.getChannel(), ((message.getDataByte(1) << 7) + message.getDataByte(0)));
                    }
                case kmmSystem:
                    {
                        // We have to re-build the MIDI message:
                        int channel = message.getChannel();
                        int status = message.getStatusByte();
                        int systemRealtimeByte = channel | status;

                        switch (systemRealtimeByte)
                        {
                            case MIDI_CLOCK:
                                for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                                    midi->fMidiInputs[i]->clock(0);
                                }
                                break;
                            case MIDI_START:
                                for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                                    midi->fMidiInputs[i]->startSync(0);
                                }
                                break;
                            case MIDI_CONT:
                                // We can consider start and continue as identical messages.
                                for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                                    midi->fMidiInputs[i]->startSync(0);
                                }
                                break;
                            case MIDI_STOP:
                                for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                                    midi->fMidiInputs[i]->stopSync(0);
                                }
                                break;
                            case MIDI_SYSEX_START:
#if 0 // this is not implemented on Bela yet
                                std::vector<unsigned char> sysex;
                                for (unsigned int j = 0; j < message.getNumDataBytes(); j++) {
                                    sysex.push_back(message.getDataByte(j));
                                }
                    
                                // Would be nice to do this:
                                // std::vector<unsigned char> sysex(message.getData(), message.getData() + message.getNumDataBytes());
                                
                                for (unsigned int i = 0; i < midi->fMidiInputs.size(); i++) {
                                    midi->fMidiInputs[i]->sysEx(sysex);
                                }
#endif
                                break;
                            default:
                                break;
                        }
                        break;
                    }
                case kmmNone:
                case kmmAny:
                default:
                    break;
            }
        }
    
    public:
    
        bela_midi()
            :midi_handler("bela")
        {}
    
        virtual ~bela_midi()
        {
            stopMidi();
        }
    
        bool startMidi()
        {
            if (fBelaMidi.readFrom(0) < 0) {
                return false;
            }
            
            if (fBelaMidi.writeTo(0) < 0) {
                return false;
            }
            
            fBelaMidi.enableParser(true);
            fBelaMidi.setParserCallback(midiCallback, this);
            return true;
        }
        
        void stopMidi()
        { 
            // Nothing todo?
        }
        
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            unsigned char buffer[3] 
                = { static_cast<unsigned char>(MIDI_NOTE_ON + channel), 
                    static_cast<unsigned char>(pitch), 
                    static_cast<unsigned char>(velocity) };
            fBelaMidi.writeOutput(buffer, 3);
            return 0;
        }
        
        void keyOff(int channel, int pitch, int velocity) 
        {
            unsigned char buffer[3] 
                = { static_cast<unsigned char>(MIDI_NOTE_OFF + channel), 
                    static_cast<unsigned char>(pitch), 
                    static_cast<unsigned char>(velocity) };
            fBelaMidi.writeOutput(buffer, 3);
        }
        
        void ctrlChange(int channel, int ctrl, int val) 
        {
            unsigned char buffer[3] 
                = { static_cast<unsigned char>(MIDI_CONTROL_CHANGE + channel), 
                    static_cast<unsigned char>(ctrl), 
                    static_cast<unsigned char>(val) };
            fBelaMidi.writeOutput(buffer, 3);
        }
        
        void chanPress(int channel, int press) 
        {
            unsigned char buffer[2] 
                = { static_cast<unsigned char>(MIDI_AFTERTOUCH + channel), 
                    static_cast<unsigned char>(press) };
            fBelaMidi.writeOutput(buffer, 2);
        }
        
        void progChange(int channel, int pgm) 
        {
            unsigned char buffer[2] 
                = { static_cast<unsigned char>(MIDI_PROGRAM_CHANGE + channel), 
                    static_cast<unsigned char>(pgm) };
            fBelaMidi.writeOutput(buffer, 2);
        }
          
        void keyPress(int channel, int pitch, int press) 
        {
            unsigned char buffer[3] 
                = { static_cast<unsigned char>(MIDI_POLY_AFTERTOUCH + channel), 
                    static_cast<unsigned char>(pitch), 
                    static_cast<unsigned char>(press) };
            fBelaMidi.writeOutput(buffer, 3);
        }
   
        void pitchWheel(int channel, int wheel) 
        {
            unsigned char buffer[3] 
                = { static_cast<unsigned char>(MIDI_PITCH_BEND + channel), 
                    static_cast<unsigned char>(wheel & 0x7F), 
                    static_cast<unsigned char>((wheel >> 7) & 0x7F) };
            fBelaMidi.writeOutput(buffer, 3);
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value) {}
         
        void startSync(double date) 
        {
            unsigned char buffer[1] = { MIDI_START };
            fBelaMidi.writeOutput(buffer, 1);
        }
       
        void stopSync(double date)
        {
            unsigned char buffer[1] = { MIDI_STOP };
            fBelaMidi.writeOutput(buffer, 1);
        }
        
        void clock(double date) 
        {
            unsigned char buffer[1] = { MIDI_CLOCK };
            fBelaMidi.writeOutput(buffer, 1);
        }
    
        void sysEx(double date, std::vector<unsigned char>& message)
        {
            fBelaMidi.writeOutput(message.data(), message.size());
        }
    
};

#endif // __bela_midi__

/*
// Use case example 

#include "faust/gui/MidiUI.h"
#include "faust/midi/bela-midi.h"

bela_midi fMIDI;
MidiUI* fMidiUI;

bool setup(BeagleRTContext *context, void *userData)
{
    ....
    
    // Setup a generic MidiUI to use bela_midi MIDI handler
    fMidiUI = new MidiUI(&fMIDI);
    // Add MidiUI control interface to DSP
    fDSP.buildUserInterface(fMidiUI);
    // And run it...
    fMidiUI->run();
    
    ....
}

void cleanup(BeagleRTContext *context, void *userData)
{
    ....
    delete fMidiUI;
}
*/
/**************************  END  bela-midi.h **************************/
