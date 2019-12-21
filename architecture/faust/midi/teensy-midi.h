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
                
                int type = usbMIDI.getType();       // which MIDI message, 128-255
                int channel = usbMIDI.getChannel(); // which MIDI channel, 0-15
                double time = (double)usbMIDI.Clock;
                
                switch(type) {
                    case usbMIDI.Clock:
                        handleClock(time);
                        break;
                    case usbMIDI.Start:
                        handleStart(time);
                        break;
                    case usbMIDI.Stop:
                        handleStop(time);
                        break;
                    case usbMIDI.ProgramChange:
                        handleProgChange(time, channel, usbMIDI.getData1());
                        break;
                    case usbMIDI.AfterTouchChannel:
                        handleAfterTouch(time, channel, usbMIDI.getData1());
                        break;
                    case usbMIDI.NoteOff:
                        handleKeyOff(time, channel, usbMIDI.getData1(), usbMIDI.getData2());
                        break;
                    case usbMIDI.NoteOn:
                        handleKeyOn(time, channel, usbMIDI.getData1(), usbMIDI.getData2());
                        break;
                    case usbMIDI.ControlChange:
                        handleCtrlChange(time, channel, usbMIDI.getData1(), usbMIDI.getData2());
                        break;
                    case usbMIDI.PitchBend:
                        handlePitchWheel(time, channel, usbMIDI.getData1(), usbMIDI.getData2());
                        break;
                    case usbMIDI.AfterTouchPoly:
                        handlePolyAfterTouch(time, channel, usbMIDI.getData1(), usbMIDI.getData2());
                        break;
                }
            }
        }
};

#endif
/**************************  END  teensy-midi.h **************************/
