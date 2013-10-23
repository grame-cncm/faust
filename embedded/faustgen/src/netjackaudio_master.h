/************************************************************************
    FAUST Architecture File
    Copyright (C) 2010-2013 GRAME, Centre National de Creation Musicale
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

#ifndef netjack_llvm_dsp__h
#define netjack_llvm_dsp__h

#include "faust/llvm-dsp.h"
#include "faust/gui/UI.h"
#include "jack/net.h"
#include <vector>

class ControlUI  : public UI {  

    protected:
    
        std::vector<FAUSTFLOAT*> fControlList;
    
        // -- widget's layouts

        void openTabBox(const char* label) {}
        void openHorizontalBox(const char* label) {}
        void openVerticalBox(const char* label) {};
        void closeBox() {}

        // -- active widgets

        void addButton(const char* label, FAUSTFLOAT* zone) { fControlList.push_back(zone); }
        void addCheckButton(const char* label, FAUSTFLOAT* zone) { fControlList.push_back(zone); }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) { fControlList.push_back(zone); };
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) { fControlList.push_back(zone); };
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) { fControlList.push_back(zone); };

        // -- passive widgets

        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) { fControlList.push_back(zone); };
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) { fControlList.push_back(zone); };
        
    public:
       
        void encode_control(float* control_buffer)
        {
            // Encode control values in control_buffer
            int control_index = 0;
            for (int i = 0; i < fControlList.size(); i++) {
                control_buffer[control_index++] = *fControlList[i];
            };
        }

        void decode_control(float* control_buffer)
        {
            // Decode control values from control_buffer
            int control_index = 0;
            for (int i = 0; i < fControlList.size(); i++) {
               *fControlList[i] = control_buffer[control_index++];
            };
        }
};

class netjackaudio_master : public llvm_dsp, public ControlUI {

    private:
    
        llvm_dsp* fDSP;             
        
        jack_net_master_t* fNetJack;
        float** fInputs;
        float** fOutputs;
        
        void compute_float(int count, float** input, float** output);
        void compute_double(int count, double** input, double** output);
        
        void remote_compute(int count, float** input, float** output);
        
        void double2float_input(int count, double** input);
        void float2double_output(int count, double** output);
        
    public: 
    
        netjackaudio_master(llvm_dsp* dsp, int buffer_size, int sample_rate);        
        virtual ~netjackaudio_master();
        
        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }

        virtual void init(int samplingFreq) { fDSP->init(samplingFreq); }

        virtual void buildUserInterface(UI* ui);
    
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
};

#endif
