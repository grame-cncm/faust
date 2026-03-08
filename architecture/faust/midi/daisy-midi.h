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
                #ifdef RX_PIN 
                handler_config.transport_config.rx = RX_PIN;
                #endif
                #ifdef TX_PIN 
                handler_config.transport_config.tx = TX_PIN;
                #endif
                midi_handler.Init(handler_config);
            #else // MIDI USB Default 
                #ifdef MIDI_USB_PERIPH
                handler_config.transport_config.periph = MIDI_USB_PERIPH;
                #endif
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
        std::array<uint8_t, NVOICES> generations = {}; 
        std::array<uint8_t, NVOICES> current_notes = {}; 

        int8_t free_voice()
        {
            for(int8_t i = 0; i < NVOICES; ++i)
            {
                if(!locked[i])
                    return i;
            }

            return -1;
        }

        uint8_t oldest_voice()
        {
            uint8_t oldest = 0;
            uint8_t index = 0;
            for(uint8_t i = 0; i < NVOICES; ++i)
            {
                if(generations[i] > oldest)
                {
                    oldest = generations[i];
                    index = i;
                }
            }
            return index;
        }

        void set_voice(uint8_t idx, int chan, uint8_t note, uint8_t velocity)
        {
            #ifdef POLY_KEY 
                poly_inputs[idx].get_key()->m->value = note; 
            #endif
            #ifdef POLY_FREQ
                // TODO Midi to freq, normalized
                poly_inputs[idx].get_freq()->m->value = note; 
            #endif
            #ifdef POLY_VEL
                poly_inputs[idx].get_vel()->m->value = velocity; 
            #endif
            #ifdef POLY_GAIN 
                poly_inputs[idx].get_gain()->m->value = velocity; 

            #endif
            #ifdef POLY_GATE
                poly_inputs[idx].get_gate()->m->value = 127; 
            #endif

            current_notes[idx] = note;
            locked[idx] = true;
        }

        void unset_voice(uint8_t idx, int chan)
        {
            #ifdef POLY_GATE
                poly_inputs[idx].get_gate()->m->value = 0; 
            #endif
            current_notes[idx] = 0;
            locked[idx] = false;
            generations[idx] = 0;
        }
        

        void voice_stealing(int chan, uint8_t note, uint8_t velocity)
        {
            int8_t free = free_voice(); 
            if(free < 0)
            {
                free = oldest_voice(); 
                unset_voice(free, chan);
            }

            set_voice(free, chan, note, velocity);

            // Everybody gets older 
            for(uint8_t i = 0; i < NVOICES; ++i)
            {
                if(i != free)
                    generations[i] += 1;
            }
            generations[free] = 0;
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
            if(on && velocity > 0) 
            {
                #ifdef VOICE_BLOCKING 
                    voice_blocking(chan, note, velocity);

                #elif defined VOICE_STEALING 
                    voice_stealing(chan, note, velocity);
                #endif

            } else 
            {   
                for(uint8_t i = 0; i < NVOICES; ++i)
                {
                    if(locked[i] && current_notes[i] == note) {
                        unset_voice(i, chan);
                    }
                }
            }
        }
#endif

        void handle_note(int chan, uint8_t note, uint8_t velocity, bool on = true)
        {
            midi_t* key = midi_find(midi_key, note);
            if(key)
            {
                if(key->channel == 0 || key->channel == uint8_t(chan) )
                {
                    if(!on)
                        key->value = 0;
                    else 
                        key->value = velocity;
                }
            }
        }

        void handle_note_off(int chan, uint8_t note, uint8_t velocity)
        {
            midi_t *keyoff = midi_find(midi_keyoff, note);
            if(keyoff) 
            {
                if(keyoff->channel == 0 || keyoff->channel == uint8_t(chan) )
                {
                    keyoff->value = velocity;
                }
            }
            handle_note(chan, note, velocity, false);
        }

        void handle_note_on(int chan, uint8_t note, uint8_t velocity)
        {
            midi_t *keyon = midi_find(midi_keyon, note);
            if(keyon) 
            {
                if(keyon->channel == 0 || keyon->channel == uint8_t(chan) )
                {
                    keyon->value = velocity;
                }

            }
            handle_note(chan, note, velocity, true);
        }

        void handle_cc(int chan, uint8_t index, uint8_t value)
        {
            midi_t *cc = midi_find(midi_cc, index);
            if(cc) 
            {
                if(cc->channel == 0 || cc->channel == uint8_t(chan) )
                {
                    cc->value = value;
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
                        handle_poly_key(p.channel + 1, p.note, p.velocity, p.velocity > 0);
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
