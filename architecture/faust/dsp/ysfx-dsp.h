/************************** BEGIN ysfx-dsp.h ****************************
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

#ifndef ysfx_dsp_H
#define ysfx_dsp_H

#include <string>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "ysfx.h"

/**
 * Faust wrapped YSFX DSP
 */
template <class REAL>
class ysfx_dsp : public ::dsp {
    
    private:
    
        struct ControlValue {
            FAUSTFLOAT fValue;
            ControlValue(FAUSTFLOAT value):fValue(value)
            {}
        };
    
        ysfx_config_t* fConfig;
        ysfx_t* fDSP;
        const char* fFileName;
        std::vector<ControlValue*> fInputsValue;
        std::vector<ControlValue*> fOutputsValue;
    
        void updateInputsControl()
        {
            for (int i = 0; i < fInputsValue.size(); i++) {
                ysfx_slider_set_value(fDSP, i, fInputsValue[i]->fValue);
            }
        }
        
        void updateOutputsControl()
        {
            for (int i = 0; i < fOutputsValue.size(); i++) {
                fOutputsValue[i]->fValue = ysfx_slider_get_value(fDSP, i);
            }
        }
    
    public:

        ysfx_dsp(const char* filename)
        {
            fConfig = ysfx_config_new();
            fDSP = ysfx_new(fConfig);
            if (!ysfx_load_file(fDSP, filename, 0)) {
                std::cerr << "File not found:" << filename << endl;
                throw std::bad_alloc();
            }
            if (!ysfx_compile(fDSP, 0)) {
                cout << "Cannot compile:" << filename << endl;
                throw std::bad_alloc();
            }
            fFileName = filename;
        }

        virtual ~ysfx_dsp()
        {
            ysfx_config_free(fConfig);
            ysfx_free(fDSP);
            for (int i = 0; i < fInputsValue.size(); i++) {
                delete fInputsValue[i];
            }
            for (int i = 0; i < fOutputsValue.size(); i++) {
                delete fOutputsValue[i];
            }
        }
 
        int getNumInputs()
        {
            return ysfx_get_num_inputs(fDSP);
        }

        int getNumOutputs()
        {
            return ysfx_get_num_outputs(fDSP);
        }

        void buildUserInterface(UI* ui_interface)
        {
            int i = 0;
            ui_interface->openVerticalBox("JSFX");
            while (ysfx_slider_exists(fDSP, i)) {
                ysfx_slider_range_t ra;
                ysfx_slider_get_range(fDSP, i, &ra);
                fInputsValue.push_back(new ControlValue(ra.def));
                string name = ysfx_slider_get_name(fDSP, i);
                if (startWith(name, "button")) {
                    ui_interface->addButton(ysfx_slider_get_name(fDSP, i), &fInputsValue[i]->fValue);
                } else if (startWith(name, "checkbox")) {
                    ui_interface->addCheckButton(ysfx_slider_get_name(fDSP, i), &fInputsValue[i]->fValue);
                } else if (startWith(name, "hslider")) {
                    ui_interface->addHorizontalSlider(ysfx_slider_get_name(fDSP, i),
                                                      &fInputsValue[i]->fValue,
                                                      ra.def,
                                                      ra.min,
                                                      ra.max,
                                                      ra.inc);
                } else if (startWith(name, "vslider")) {
                    ui_interface->addVerticalSlider(ysfx_slider_get_name(fDSP, i),
                                                      &fInputsValue[i]->fValue,
                                                      ra.def,
                                                      ra.min,
                                                      ra.max,
                                                      ra.inc);
                } else if (startWith(name, "nentry")) {
                    ui_interface->addNumEntry(ysfx_slider_get_name(fDSP, i),
                                              &fInputsValue[i]->fValue,
                                              ra.def,
                                              ra.min,
                                              ra.max,
                                              ra.inc);
                }
                i++;
            }
            ui_interface->closeBox();
        }

        int getSampleRate()
        {
            return ysfx_get_sample_rate(fDSP);
        }

        void init(int sample_rate)
        {
            ysfx_set_sample_rate(fDSP, sample_rate);
            ysfx_init(fDSP);
        }

        void instanceInit(int sample_rate) {}

        void instanceConstants(int sample_rate) {}

        void instanceResetUserInterface() {}

        void instanceClear() {}

        ysfx_dsp* clone()
        {
            return new ysfx_dsp(fFileName);
        }

        void metadata(Meta* m) {}

        void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
        {
            updateInputsControl();
            if (sizeof(REAL) == sizeof(float)) {
                ysfx_process_float(fDSP, (const float **)input, (float **)output, getNumInputs(), getNumOutputs(), count);
            } else {
                ysfx_process_double(fDSP, (const double **)input, (double **)output, getNumInputs(), getNumOutputs(), count);
            }
            updateOutputsControl();
        }
    
};

#endif
/************************** END ysfx-dsp.h **************************/
