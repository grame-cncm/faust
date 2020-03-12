/************************** BEGIN daisy-midi.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#ifndef __daisy_midi__
#define __daisy_midi__

#include <iostream>
#include <cstdlib>

#include "faust/midi/midi.h"

class daisy_midi : public midi_handler {
    
    private:
    
        MidiHandler fMidi;
    
    public:
    
        daisy_midi():midi_handler("daisy")
        {}
    
        virtual ~daisy_midi()
        {
            stopMidi();
        }

        bool startMidi()
        {
            fMidi.Init(MidiHandler::INPUT_MODE_UART1, MidiHandler::OUTPUT_MODE_NONE);
            return true;
        }

        void stopMidi()
        {}
    
        void processMidi()
        {
            fMidi.Listen();
            while (fMidi.HasEvents()) {
                
                MidiEvent m = fMidi.PopEvent();
                switch(m.type) {
                        
                    case NoteOff:
                        // TODO
                        //NoteOff p = m.AsNoteOff();
                        //handleKeyOff(time, p.channel, p.note, p.velocity);
                        break;
                        
                    case NoteOn:
                        NoteOn p = m.AsNoteOn();
                        handleKeyOn(time, p.channel, p.note, p.velocity);
                        break;
                        
                    case PolyphonicKeyPressure:
                        // TODO
                        //handlePolyAfterTouch(time, m.channel, m.control_number, m.value);
                        break;
                        
                    case ControlChange:
                        ControlChangeEvent p = m.AsControlChange();
                        handleCtrlChange(time, p.channel, p.control_number, p.value);
                        break;
                        
                    case ProgramChange:
                        // TODO
                        //handleProgChange(time, p.channel, p.control_number, p.value);
                        break;
                        
                    case PitchBend:
                        // TODO
                        //handlePitchWheel(time, p.channel, p.control_number, p.value);
                        break;
                }
            }
            // Synchronize all GUI controllers
            GUI::updateAllGuis();
        }
   
};

#endif
/**************************  END  daisy-midi.h **************************/
