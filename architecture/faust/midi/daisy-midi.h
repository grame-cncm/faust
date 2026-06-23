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

<<<<<<< HEAD
<<<<<<< HEAD
=======
/*
    TODO : 
        - Replace Faust MIDIUI with simpler implementation
*/ 

>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
                #ifdef RX_PIN 
                handler_config.transport_config.rx = RX_PIN;
                #endif
                #ifdef TX_PIN 
                handler_config.transport_config.tx = TX_PIN;
                #endif
<<<<<<< HEAD
=======
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
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
<<<<<<< HEAD
=======
=======
                handler_config.transport_config.periph = daisy::MidiUartTransport::Config::
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
            #else // MIDI USB Default 
                handler_config.transport_config.periph = daisy::MidiUsbTransport::Config::INTERNAL;
                midi_handler.Init(handler_config);
            #endif 
<<<<<<< HEAD
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
            
            #ifdef POLY
                for(auto & it : locked)
                    it = false;
            #endif
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
=======

>>>>>>> 6482c2631 (fixed bugs (digi output), patch screen is working properly, patchsm is tested for GPIO, CV, audio out, and MIDI (poly and monophonic))
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

<<<<<<< HEAD
<<<<<<< HEAD
#ifdef POLY
        uint8_t voice_counter = 0; 
        std::array<bool, NVOICES> locked;
        std::array<uint8_t, NVOICES> generations = {}; 
        std::array<uint8_t, NVOICES> current_notes = {}; 
=======
#ifdef POLY
        uint8_t voice_counter = 0; 
        std::array<bool, NVOICES> locked;
        std::array<uint8_t, NVOICES> generations = {}; 
        std::array<uint8_t, NVOICES> current_notes = {}; 

<<<<<<< HEAD
        enum class poly_mode_t {blocking, stealing};
<<<<<<< HEAD
        const poly_mode_t poly_mode = poly_mode_t::blocking;
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
=======
        const poly_mode_t poly_mode = poly_mode_t::stealing;
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)

=======
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
        int8_t free_voice()
        {
            for(int8_t i = 0; i < NVOICES; ++i)
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
            {
                if(!locked[i])
                    return i;
            }
<<<<<<< HEAD
=======
                if(!locked[i])
                    return i;
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
=======
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)

            return -1;
        }

<<<<<<< HEAD
<<<<<<< HEAD
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

=======
        void set_voice(uint8_t idx, int chan, uint8_t note, uint8_t velocity)
        {
            if(poly_inputs[idx].find("freq") != poly_inputs[idx].end())
                poly_inputs[idx]["freq"].m->value = note; 
            if(poly_inputs[idx].find("gain") != poly_inputs[idx].end())
                poly_inputs[idx]["gain"].m->value = velocity; 
            if(poly_inputs[idx].find("gate") != poly_inputs[idx].end())
                poly_inputs[idx]["gate"].m->value = 127; 
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
            current_notes[idx] = note;
            locked[idx] = true;
        }

<<<<<<< HEAD
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
=======
        void voice_stealing()
=======
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
        bool ledstate = false;        
        void voice_stealing(int chan, uint8_t note, uint8_t velocity)
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
        {
            int8_t free = free_voice(); 
            if(free < 0)
            {
                free = oldest_voice(); 
                unset_voice(free, chan);
            }
<<<<<<< HEAD
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
=======

            if(free == 0) 
            {
                ledstate = !ledstate;
                hw.SetLed(ledstate);
            }

            set_voice(free, chan, note, velocity);

            // Everybody gets older 
            for(uint8_t i = 0; i < NVOICES; ++i)
            {
                if(i != free)
                    generations[i] += 1;
            }
            generations[free] = 0;
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
            if(on && velocity > 0) 
            {
                #ifdef VOICE_BLOCKING 
                    voice_blocking(chan, note, velocity);

                #elif defined VOICE_STEALING 
                    voice_stealing(chan, note, velocity);
                #endif
=======
            if(on) 
=======
            //hw.PrintLine("poly_key: note=%d vel=%d on=%d", note, velocity, on);
=======
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
            if(on && velocity > 0) 
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
            {
                #ifdef VOICE_BLOCKING 
                    voice_blocking(chan, note, velocity);

                #elif defined VOICE_STEALING 
                    voice_stealing(chan, note, velocity);
<<<<<<< HEAD
                }
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
=======
                #endif
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))

            } else 
            {   
                for(uint8_t i = 0; i < NVOICES; ++i)
                {
                    if(locked[i] && current_notes[i] == note) {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
                        unset_voice(i, chan);
=======
                        if(poly_inputs[i].find("gate") != poly_inputs[i].end())
=======
                        if(poly_inputs[i].has_gate())
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
                        {
                            poly_inputs[i].get_gate()->m->value = 0;
                        }
<<<<<<< HEAD
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
=======
                        if(poly_inputs[i].has_vel())
                        {
                            poly_inputs[i].get_vel()->m->value = 0;
                        }
                        locked[i] = false;
                        current_notes[i] = 0;
                        generations[i] = 0;
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
                        unset_voice(i, chan);
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
                    }
                }
            }
        }
#endif

        void handle_note(int chan, uint8_t note, uint8_t velocity, bool on = true)
<<<<<<< HEAD
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
=======
        void handle_note(int chan, uint8_t note, uint8_t velocity)
=======
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
        {
            //hw.PrintLine("Note : %d %d %d", chan, note, velocity);
            midi_t* key = midi_find(midi_key, note);
            if(key)
            {
                if(key->channel == 0 || key->channel == uint8_t(chan) )
                {
<<<<<<< HEAD
                    midi_key[note].value = velocity;
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
                    if(!on)
                        key->value = 0;
                    else 
<<<<<<< HEAD
                        midi_key[note].value = velocity;
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
=======
                        key->value = velocity;
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
                }
            }
        }

        void handle_note_off(int chan, uint8_t note, uint8_t velocity)
        {
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
            midi_t *keyoff = midi_find(midi_keyoff, note);
            if(keyoff) 
            {
                if(keyoff->channel == 0 || keyoff->channel == uint8_t(chan) )
                {
                    keyoff->value = velocity;
                }
            }
            handle_note(chan, note, velocity, false);
=======
            //hw.PrintLine("NoteOff : %d %d %d", chan, note, velocity);
            midi_t *keyoff = midi_find(midi_keyoff, note);
            if(keyoff) 
            {
                if(keyoff->channel == 0 || keyoff->channel == uint8_t(chan) )
                {
                    keyoff->value = velocity;
                }
            }
<<<<<<< HEAD
            handle_note(chan, note, velocity);
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
            handle_note(chan, note, velocity, false);
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
        }

        void handle_note_on(int chan, uint8_t note, uint8_t velocity)
        {
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
            midi_t *keyon = midi_find(midi_keyon, note);
            if(keyon) 
            {
                if(keyon->channel == 0 || keyon->channel == uint8_t(chan) )
                {
                    keyon->value = velocity;
                }

            }
            handle_note(chan, note, velocity, true);
=======
            //hw.PrintLine("NoteOn : %d %d %d", chan, note, velocity);
            midi_t *keyon = midi_find(midi_keyon, note);
            if(keyon) 
            {
                if(keyon->channel == 0 || keyon->channel == uint8_t(chan) )
                {
                    keyon->value = velocity;
                }

            }
<<<<<<< HEAD
            handle_note(chan, note, velocity);
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
            handle_note(chan, note, velocity, true);
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
        }

        void handle_cc(int chan, uint8_t index, uint8_t value)
        {
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
            midi_t *cc = midi_find(midi_cc, index);
            if(cc) 
            {
                if(cc->channel == 0 || cc->channel == uint8_t(chan) )
<<<<<<< HEAD
                {
                    cc->value = value;
=======
            if(midi_cc.find(index) != midi_cc.end()) {
                if(midi_cc[index].channel == 0 || midi_cc[index].channel == uint8_t(chan) )
                {
                    midi_cc[index].value = value;
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
                {
                    cc->value = value;
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
                }

            }
        }
    
        void processMidi()
        {
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======

>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
            midi_handler.Listen();
            while (midi_handler.HasEvents()) {
                
                double time = 0.;
                daisy::MidiEvent m = midi_handler.PopEvent();
                switch(m.type) {
                        
                    case daisy::MidiMessageType::NoteOff: {
                        daisy::NoteOffEvent p = m.AsNoteOff();
<<<<<<< HEAD
<<<<<<< HEAD
                        #ifdef POLY 
                        handle_poly_key(p.channel + 1, p.note, p.velocity, false);
                        #endif
=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
                        #ifdef POLY 
                        handle_poly_key(p.channel + 1, p.note, p.velocity, false);
                        #endif
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
                        handle_note_off(p.channel + 1, p.note, p.velocity);
                        break;
                    }
                        
                    case daisy::MidiMessageType::NoteOn: {
                        daisy::NoteOnEvent p = m.AsNoteOn();
<<<<<<< HEAD
<<<<<<< HEAD
                        #ifdef POLY 
                        handle_poly_key(p.channel + 1, p.note, p.velocity, p.velocity > 0);
                        #endif
=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
                        #ifdef POLY 
                        handle_poly_key(p.channel + 1, p.note, p.velocity, p.velocity > 0);
                        #endif
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
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
