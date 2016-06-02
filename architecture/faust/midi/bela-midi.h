/************************************************************************
    FAUST Architecture File
    Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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
                        midi->fMidiInputs[i]->pitchWheel(0, message.getChannel(), ((message.getDataByte(1) * 128.0 + message.getDataByte(0)) - 8192) / 8192.0);
                    }
                    break;
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
            stop_midi();
        }
        
        bool start_midi()
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
        
        void stop_midi()
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
         
        void start_sync(double date) 
        {
            unsigned char buffer[1] = { MIDI_START };
            fBelaMidi.writeOutput(buffer, 1);
        }
       
        void stop_sync(double date) 
        {
            unsigned char buffer[1] = { MIDI_STOP };
            fBelaMidi.writeOutput(buffer, 1);
        }
        
        void clock(double date) 
        {
            unsigned char buffer[1] = { MIDI_CLOCK };
            fBelaMidi.writeOutput(buffer, 1);
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
