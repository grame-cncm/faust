#ifndef CONTROL_UI_H
#define CONTROL_UI_H

#include "faust/gui/UI.h"
#include <vector>
#include <assert.h>

class ControlUI  : public UI {  

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
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) { fControlIn.push_back(zone);};

        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) { fControlIn.push_back(zone); };

        // -- passive widgets

        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) { fControlOut.push_back(zone); };
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) { fControlOut.push_back(zone); };
        
    public:
       
        void encode_control(float* control_buffer, unsigned int size)
        { 
            assert(fControlOut.size() < size);
            // Encode control values in control_buffer
            
            for (unsigned int i = 0; i < fControlOut.size(); i++) {
                control_buffer[i] = *fControlOut[i];
            }
        }
        
        void decode_control(float* control_buffer, unsigned int size)
        {
            assert(fControlIn.size() < size);
            // Decode control values from control_buffer
            
            for (unsigned int i = 0; i < fControlIn.size(); i++) {
               *fControlIn[i] = control_buffer[i];
            }
        }
};

#endif
