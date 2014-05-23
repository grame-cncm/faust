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
            assert(fControlOut.size() < frames);
            
            for (unsigned int i = 0; i < fControlOut.size(); i++) {
                control_buffer[i] = *fControlOut[i];
            }
        }
        
        void decode_control(float* control_buffer, unsigned int frames)
        {
            assert(fControlIn.size() < frames);
            
            for (unsigned int i = 0; i < fControlIn.size(); i++) {
               *fControlIn[i] = control_buffer[i];
            }
        }
        
        void encode_midi_control(void* midi_control_buffer, unsigned int count)
        { 
            assert(fControlOut.size() < count);
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
        
        void decode_midi_control(void* midi_control_buffer, unsigned int count)
        {
            assert(jack_midi_get_event_count(midi_control_buffer) <= count);
            
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
