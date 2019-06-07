/************************** BEGIN teensy-midi.h **************************/
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

#ifndef __teensy_midi__
#define __teensy_midi__

#include <iostream>
#include <cstdlib>

#include "faust/midi/midi.h"

class teensy_midi : public midi_handler {
    
    public:
        
        void processMidi(usb_midi_class usbMIDI)
        {
            while (usbMIDI.read()) {
                
                byte type, channel, data1, data2, cable;
                type = usbMIDI.getType();       // which MIDI message, 128-255
                channel = usbMIDI.getChannel(); // which MIDI channel, 1-16
                data1 = usbMIDI.getData1();     // first data byte of message, 0-127
                data2 = usbMIDI.getData2();     // second data byte of message, 0-127
                cable = usbMIDI.getCable();     // which virtual cable with MIDIx8, 0-7
                double time = (double)usbMIDI.Clock;
                
                switch(type) {
                    case usbMIDI.Clock:
                        for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                            fMidiInputs[i]->clock(time);
                        }
                        break;
                    case usbMIDI.Start:
                        for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                            fMidiInputs[i]->startSync(time);
                        }
                        break;
                    case usbMIDI.Stop:
                        for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                            fMidiInputs[i]->stopSync(time);
                        }
                        break;
                    case usbMIDI.ProgramChange:
                        for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                            fMidiInputs[i]->progChange(time, channel, data1);
                        }
                        break;
                    case usbMIDI.AfterTouchChannel:
                        for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                            fMidiInputs[i]->chanPress(time, channel, data1);
                        }
                        break;
                    case usbMIDI.NoteOff:
                        for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                            fMidiInputs[i]->keyOff(time, channel, data1, data2);
                        }
                        break;
                    case usbMIDI.NoteOn:
                        for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                            if (data2 == 0) {
                                fMidiInputs[i]->keyOff(time, channel, data1, data2);
                            } else {
                                fMidiInputs[i]->keyOn(time, channel, data1, data2);
                            }
                        }
                        break;
                    case usbMIDI.ControlChange:
                        for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                            fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                        }
                        break;
                    case usbMIDI.PitchBend:
                        for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                            fMidiInputs[i]->pitchWheel(time, channel, (data2 << 7) + data1);
                        }
                        break;
                    case usbMIDI.AfterTouchPoly:
                        for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                            fMidiInputs[i]->keyPress(time, channel, data1, data2);
                        }
                        break;
                }
            }
        }
};

#endif
/**************************  END  teensy-midi.h **************************/
