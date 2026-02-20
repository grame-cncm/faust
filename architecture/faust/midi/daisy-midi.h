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

/*
    TODO : 
        - Replace Faust MIDIUI with simpler implementation
*/ 

class daisy_midi {
    
    private:
        #ifdef MIDI_UART 
            // For MIDI through Jacks for example (see Pod pinout)
            daisy::MidiUartHandler midi_handler;
            daisy::MidiUartHandler::Config handler_config; 
        #else // MIDI USB Default 
            // Three options (two is enough) : internal USB, or pin USB (external) or Host
            daisy::MidiUsbHandler midi_handler;
            daisy::MidiUsbHandler::Config handler_config; 
        #endif 
    public:

        daisy_midi()
        {
            #ifdef MIDI_UART 
                handler_config.transport_config.periph = daisy::MidiUartTransport::Config::
            #else // MIDI USB Default 
                handler_config.transport_config.periph = daisy::MidiUsbTransport::Config::INTERNAL;
                midi_handler.Init(handler_config);
            #endif 
            
            #ifdef POLY
                for(auto & it : locked)
                    it = false;
            #endif
        }
    
        virtual ~daisy_midi()
        {
            stopMidi();
        }

        bool startMidi()
        {
            return true;
        }

        void stopMidi()
        {}

#ifdef POLY
        uint8_t voice_counter = 0; 
        std::array<bool, NVOICES> locked;
        std::array<uint8_t, NVOICES> generations; 
        std::array<uint8_t, NVOICES> current_notes; 

        enum class poly_mode_t {blocking, stealing};
        const poly_mode_t poly_mode = poly_mode_t::blocking;

        int8_t free_voice()
        {
            for(int8_t i = 0; i < NVOICES; ++i)
                if(!locked[i])
                    return i;

            return -1;
        }

        void set_voice(uint8_t idx, int chan, uint8_t note, uint8_t velocity)
        {
            if(poly_inputs[idx].find("freq") != poly_inputs[idx].end())
                poly_inputs[idx]["freq"].m->value = note; 
            if(poly_inputs[idx].find("gain") != poly_inputs[idx].end())
                poly_inputs[idx]["gain"].m->value = velocity; 
            if(poly_inputs[idx].find("gate") != poly_inputs[idx].end())
                poly_inputs[idx]["gate"].m->value = 127; 
            current_notes[idx] = note;
            locked[idx] = true;
        }

        void voice_stealing()
        {
            int8_t free = free_voice(); 
            if(free >= 0)
            {
                
            } else {
                
            }
        }


        void voice_blocking(int chan, uint8_t note, uint8_t velocity)
        {
            int8_t free = free_voice(); 
            if(free >= 0)
            {
                set_voice(free, chan, note, velocity);
            } else {
                return;
            }

        }

        void handle_poly_key(int chan, uint8_t note, uint8_t velocity, bool on = true)
        {
            if(on) 
            {
                if(poly_mode == poly_mode_t::blocking) 
                {
                    voice_blocking(chan, note, velocity);
                } 
                else if(poly_mode == poly_mode_t::stealing) 
                {

                }

            } else 
            {   
                for(uint8_t i = 0; i < NVOICES; ++i)
                {
                    if(locked[i] && current_notes[i] == note) {
                        if(poly_inputs[i].find("gate") != poly_inputs[i].end())
                        {
                            poly_inputs[i]["gate"].m->value = 0;
                            locked[i] = false;
                            current_notes[i] = 0;
                            break;
                        }
                    }
                }
            }
        }
#endif

        void handle_note(int chan, uint8_t note, uint8_t velocity, bool on = true)
        {
            //hw.PrintLine("Note : %d %d %d", chan, note, velocity);
            if(midi_key.find(note) != midi_key.end()) {
                if(midi_key[note].channel == 0 || midi_key[note].channel == uint8_t(chan) )
                {
                    if(!on)
                        midi_key[note].value = 0;
                    else 
                        midi_key[note].value = velocity;
                }
            }
        }

        void handle_note_off(int chan, uint8_t note, uint8_t velocity)
        {
            //hw.PrintLine("NoteOff : %d %d %d", chan, note, velocity);
            if(midi_keyoff.find(note) != midi_keyoff.end()) {
                if(midi_keyoff[note].channel == 0 || midi_keyoff[note].channel == uint8_t(chan) )
                {
                    midi_keyoff[note].value = velocity;
                }
            }
            handle_note(chan, note, velocity, false);
        }

        void handle_note_on(int chan, uint8_t note, uint8_t velocity)
        {
            //hw.PrintLine("NoteOn : %d %d %d", chan, note, velocity);
            if(midi_keyon.find(note) != midi_keyon.end()) {
                if(midi_keyon[note].channel == 0 || midi_keyon[note].channel == uint8_t(chan) )
                {
                    midi_keyon[note].value = velocity;
                }
            }
            handle_note(chan, note, velocity, true);
        }

        void handle_cc(int chan, uint8_t index, uint8_t value)
        {
            if(midi_cc.find(index) != midi_cc.end()) {
                if(midi_cc[index].channel == 0 || midi_cc[index].channel == uint8_t(chan) )
                {
                    midi_cc[index].value = value;
                }
            }
        }
    
        void processMidi()
        {
            midi_handler.Listen();
            while (midi_handler.HasEvents()) {
                
                double time = 0.;
                daisy::MidiEvent m = midi_handler.PopEvent();
                switch(m.type) {
                        
                    case daisy::MidiMessageType::NoteOff: {
                        daisy::NoteOffEvent p = m.AsNoteOff();
                        #ifdef POLY 
                        handle_poly_key(p.channel + 1, p.note, p.velocity, false);
                        #endif
                        handle_note_off(p.channel + 1, p.note, p.velocity);
                        break;
                    }
                        
                    case daisy::MidiMessageType::NoteOn: {
                        daisy::NoteOnEvent p = m.AsNoteOn();
                        #ifdef POLY 
                        handle_poly_key(p.channel + 1, p.note, p.velocity, true);
                        #endif
                        if(p.velocity == 0) {
                            handle_note_off(p.channel + 1, p.note, p.velocity);
                        } else {
                            handle_note_on(p.channel + 1, p.note, p.velocity);
                        }
                        break;
                    }
                        
                    case daisy::MidiMessageType::PolyphonicKeyPressure: {
                        // TODO
                        //handlePolyAfterTouch(time, m.channel, m.control_number, m.value);
                        break;
                    }
                        
                    case daisy::MidiMessageType::ControlChange: {
                        daisy::ControlChangeEvent p = m.AsControlChange();
                        handle_cc(p.channel + 1, p.control_number, p.value);
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
            //GUI::updateAllGuis();
        }
   
};

#endif
/**************************  END  daisy-midi.h **************************/
