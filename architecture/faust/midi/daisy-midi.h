/************************** BEGIN daisy-midi.h ****************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __daisy_midi__
#define __daisy_midi__

#include <cstdlib>

#include "daisysp.h"
#include "faust/midi/midi.h"
#include "faust/gui/GUI.h"

class daisy_midi : public midi_handler {
    
    private:
    
        daisy::MidiHandler<daisy::MidiUartTransport> fMidi;
        daisy::MidiHandler<daisy::MidiUartTransport>::Config fConfig;

    public:
    
        daisy_midi():midi_handler("daisy")
        {}
    
        virtual ~daisy_midi()
        {
            stopMidi();
        }

        bool startMidi()
        {
            fMidi.Init(fConfig);
            return true;
        }

        void stopMidi()
        {}
    
        void processMidi()
        {
            fMidi.Listen();
            while (fMidi.HasEvents()) {
                
                double time = 0.;
                daisy::MidiEvent m = fMidi.PopEvent();
                switch(m.type) {
                        
                    case daisy::MidiMessageType::NoteOff: {
                        // TODO
                        //NoteOff p = m.AsNoteOff();
                        //handleKeyOff(time, p.channel, p.note, p.velocity);
                        break;
                    }
                        
                    case daisy::MidiMessageType::NoteOn: {
                        daisy::NoteOnEvent p = m.AsNoteOn();
                        handleKeyOn(time, p.channel, p.note, p.velocity);
                        break;
                    }
                        
                    case daisy::MidiMessageType::PolyphonicKeyPressure: {
                        // TODO
                        //handlePolyAfterTouch(time, m.channel, m.control_number, m.value);
                        break;
                    }
                        
                    case daisy::MidiMessageType::ControlChange: {
                        daisy::ControlChangeEvent p = m.AsControlChange();
                        handleCtrlChange(time, p.channel, p.control_number, p.value);
                        break;
                    }
                        
                    case daisy::MidiMessageType::ProgramChange: {
                        // TODO
                        //handleProgChange(time, p.channel, p.control_number, p.value);
                        break;
                    }
                        
                    case daisy::MidiMessageType::PitchBend: {
                        // TODO
                        //handlePitchWheel(time, p.channel, p.control_number, p.value);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            // Synchronize all GUI controllers
            GUI::updateAllGuis();
        }
   
};

#endif
/**************************  END  daisy-midi.h **************************/
