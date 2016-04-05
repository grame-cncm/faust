/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
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

#ifndef CONTROL_UI_H
#define CONTROL_UI_H

#include "faust/gui/UI.h"
#include <jack/midiport.h>
#include <vector>
#include <assert.h>

class ControlUI : public UI {  

    protected:
    
        std::vector<FAUSTFLOAT*> fControlIn;
        std::vector<FAUSTFLOAT*> fControlOut;
     
         // -- widget's layouts

        void openTabBox(const char* label) {}
        void openHorizontalBox(const char* label) {}
        void openVerticalBox(const char* label) {};
        void closeBox() {}

        // -- active widgets

        void addButton(const char* label, FAUSTFLOAT* zone) { fControlIn.push_back(zone); }
        void addCheckButton(const char* label, FAUSTFLOAT* zone) { fControlIn.push_back(zone); }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) { fControlIn.push_back(zone); };
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) { fControlIn.push_back(zone); };

        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) { fControlIn.push_back(zone); };

        // -- passive widgets

        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) { fControlOut.push_back(zone); };
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) { fControlOut.push_back(zone); };
        
    public:
       
        void encode_control(float* control_buffer, unsigned int frames)
        { 
            assert(fControlOut.size() <= frames);
            
            for (unsigned int i = 0; i < fControlOut.size(); i++) {
                control_buffer[i] = *fControlOut[i];
            }
        }
        
        void decode_control(float* control_buffer, unsigned int frames)
        {
            assert(fControlIn.size() <= frames);
            
            for (unsigned int i = 0; i < fControlIn.size(); i++) {
               *fControlIn[i] = control_buffer[i];
            }
        }
        
        void encode_midi_control(void* midi_control_buffer, unsigned int frames)
        { 
            assert(fControlOut.size() <= frames);
            jack_midi_reset_buffer(midi_control_buffer);
          
            for (unsigned int i = 0; i < fControlOut.size(); i++) {
                jack_midi_data_t* buffer = jack_midi_event_reserve(midi_control_buffer, i, 4);
                assert(buffer);
                *((float*)buffer) = *fControlOut[i];
            }
        }
    
        static void encode_midi_control(void* midi_control_buffer, float* control_buffer, int count)
        {
            jack_midi_reset_buffer(midi_control_buffer);
            
            for (unsigned int i = 0; i < count; i++) {
                jack_midi_data_t* buffer = jack_midi_event_reserve(midi_control_buffer, i, 4);
                assert(buffer);
                *((float*)buffer) = control_buffer[i];
            }
        }
        
        void decode_midi_control(void* midi_control_buffer, unsigned int frames)
        {
            assert(jack_midi_get_event_count(midi_control_buffer) <= frames);
            
            for (int i = 0; i < jack_midi_get_event_count(midi_control_buffer); i++) {
                jack_midi_event_t in_event;
                jack_midi_event_get(&in_event, midi_control_buffer, i);
                *fControlIn[i] = *((float*)in_event.buffer);
            }
        }
        
        static void decode_midi_control(void* midi_control_buffer, float* control_buffer, int count)
        {
            assert(jack_midi_get_event_count(midi_control_buffer) <= count);
            
            for (int i = 0; i < jack_midi_get_event_count(midi_control_buffer); i++) {
                jack_midi_event_t in_event;
                jack_midi_event_get(&in_event, midi_control_buffer, i);
                control_buffer[i] = *((float*)(in_event.buffer));
            }
        }
        
};

#endif
