/************************** BEGIN Esp32ControlUI.h **************************/
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

#ifndef FAUST_ESP32CONTROL_H
#define FAUST_ESP32CONTROL_H

#include <string>
#include <iostream>
#include <vector>
#include <string.h>

#include "driver/uart.h"

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/ValueConverter.h"

/*******************************************************************************
 * Esp32ControlUI : Faust User Interface
 * This class handles Gramophone controllers
 ******************************************************************************/

// Value converter using a low-pass filter
class FilteredConverter : public ConverterZoneControl
{
    
    private:
    
        /*
         Generated with:
         
            process = si.smooth(tau2pole(T60))
            with {
                SR = 100;   // Control rate is 100 Hz
                T60 = hslider("T60", 0.2, 0, 1, 0.01);
                tau2pole(tau) = exp(-1.0/(tau*SR));
            };
        */
    
        // Template used to specialize double parameters expressed as NUM/DENOM
        template <int NUM, int DENOM>
        struct Double {
            static constexpr double value() { return double(NUM)/double(DENOM); }
        };

        /*
        // Templated filter with T60 expressed as NUM/DENOM
        template <class fVslider0, typename REAL>
        struct CtrlFilter {
            
            float fRec0[2];
            
            CtrlFilter()
            {
                for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
                    fRec0[l0] = 0.0f;
                }
            }
            
            FAUSTFLOAT compute(FAUSTFLOAT input0)
            {
                // Computed at compile time
                REAL fSlow0 = std::exp((0.0f - (0.00999999978f / REAL(fVslider0::value()))));
                REAL fSlow1 = (1.0f - fSlow0);
                // Computed at runtime
                fRec0[0] = ((fSlow0 * fRec0[1]) + (fSlow1 * REAL(input0)));
                FAUSTFLOAT output0 = FAUSTFLOAT(fRec0[0]);
                fRec0[1] = fRec0[0];
                return output0;
            }
            
        };
    
        // T60 = 2/10 = 0.2s
        CtrlFilter<Double<2,10>, double> fFilter;
        */
    
    
        /*
         Generated with:
         process = _ <: (_,@(delay)) : - : + ~ _ : /(delay);
         */
    
        template <int fHslider0>
        struct CtrlFilter {
            
            int IOTA;
            float fVec0[128];
            float fRec0[2];
            
            CtrlFilter()
            {
                IOTA = 0;
                for (int l0 = 0; (l0 < 128); l0 = (l0 + 1)) {
                    fVec0[l0] = 0.0f;
                }
                for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
                    fRec0[l1] = 0.0f;
                }
            }
            
            FAUSTFLOAT compute(FAUSTFLOAT input0)
            {
                float fSlow0 = float(fHslider0);
                float fSlow1 = (1.0f / fSlow0);
                int iSlow2 = int(fSlow0);
                float fTemp0 = float(input0);
                fVec0[(IOTA & 127)] = fTemp0;
                fRec0[0] = ((fTemp0 + fRec0[1]) - fVec0[((IOTA - iSlow2) & 127)]);
                FAUSTFLOAT output0 = FAUSTFLOAT((fSlow1 * fRec0[0]));
                IOTA = (IOTA + 1);
                fRec0[1] = fRec0[0];
                return output0;
            }
            
        };

        CtrlFilter<10> fFilter;
    
    public:
    
        FilteredConverter(FAUSTFLOAT* zone,
                          ValueConverter* converter)
        : ConverterZoneControl(zone, converter) {}
        virtual ~FilteredConverter() {}
    
        void update(double v)
        {
            *fZone = fValueConverter->ui2faust(fFilter.compute(FAUSTFLOAT(v)));
        }
    
};

// To be used with Gramophone
class Esp32ControlUI : public GenericUI
{
    
    private:
    
        std::vector<FilteredConverter*> fKnob1Converter;
        std::vector<FilteredConverter*> fKnob2Converter;
        std::vector<FilteredConverter*> fKnob3Converter;
    
        std::vector<FAUSTFLOAT*> fPushButton;
        std::vector<FAUSTFLOAT*> fCheckButton;
        int fLastButton;
    
        std::string fKey, fValue;
    
        TaskHandle_t fProcessHandle;
    
        void update()
        {
            while (true) {
                
                // Knob 1
                if (fKnob1Converter.size() > 0) {
                    int val = adc1_get_raw(ADC1_CHANNEL_7);
                    for (int i = 0; i < fKnob1Converter.size(); i++) {
                        fKnob1Converter[i]->update(double(val));
                    }
                }
                
                // Knob 2
                if (fKnob2Converter.size() > 0) {
                    int val = adc1_get_raw(ADC1_CHANNEL_4);
                    for (int i = 0; i < fKnob2Converter.size(); i++) {
                        fKnob2Converter[i]->update(double(val));
                    }
                }
                
                // Photores
                if (fKnob3Converter.size() > 0) {
                    int val = adc1_get_raw(ADC1_CHANNEL_6);
                    for (int i = 0; i < fKnob3Converter.size(); i++) {
                        fKnob3Converter[i]->update(double(val));
                    }
                }
                
                // Button considered as a push button
                if (fPushButton.size() > 0) {
                    int button = gpio_get_level(GPIO_NUM_14);
                    for (int i = 0; i < fPushButton.size(); i++) {
                        *fPushButton[i] = FAUSTFLOAT(button);
                    }
                }
                
                // Button considered as a checkbox
                if (fCheckButton.size() > 0) {
                    int button = gpio_get_level(GPIO_NUM_14);
                    for (int i = 0; i < fCheckButton.size(); i++) {
                        if (button == 1) {
                            if (fLastButton == 0) {
                                // Upfront detected
                                *fCheckButton[i] = !(*fCheckButton[i]);
                                fLastButton = button;
                            }
                        } else {
                            fLastButton = 0;
                        }
                    }
                }
                
                /*
                int encoder_button = gpio_get_level(GPIO_NUM_15);
                int encoder_dt = gpio_get_level(GPIO_NUM_4);
                int encoder_clk = gpio_get_level(GPIO_NUM_13);
                
                int encoder_status;
                if (encoder_button == 0) {
                    encoder_status = encoder_dt;
                } else {
                    encoder_status = encoder_clk;
                }
                
                std::cout << "encoder_button " << encoder_button << std::endl;
                std::cout << "encoder_dt " << encoder_dt << std::endl;
                std::cout << "encoder_clk " << encoder_clk << std::endl;
                std::cout << "encoder_status " << encoder_status << std::endl;
                */
                
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
        }
    
        static void updateHandler(void* arg)
        {
            static_cast<Esp32ControlUI*>(arg)->update();
        }
    
    public:
        
        Esp32ControlUI():fLastButton(0), fProcessHandle(nullptr)
        {
            adc1_config_width(ADC_WIDTH_BIT_12);
            gpio_config_t io_conf;
            io_conf.intr_type = (gpio_int_type_t) GPIO_PIN_INTR_POSEDGE;
            io_conf.pin_bit_mask = ((1ULL<<4) | (1ULL<<13) | (1ULL<<14) | (1ULL<<15));
            io_conf.mode = GPIO_MODE_INPUT;
            io_conf.pull_up_en = (gpio_pullup_t)1;
            gpio_config(&io_conf);
        }
    
        virtual ~Esp32ControlUI()
        {
            for (auto& it : fKnob1Converter) delete it;
            for (auto& it : fKnob2Converter) delete it;
            for (auto& it : fKnob3Converter) delete it;
            stop();
        }
    
        bool start()
        {
            // Start Controller receive task
            return (xTaskCreatePinnedToCore(updateHandler, "Faust Controller Task", 4096, (void*)this, 5, &fProcessHandle, 1) == pdPASS);
        }
    
        void stop()
        {
            if (fProcessHandle != nullptr) {
                vTaskDelete(fProcessHandle);
                fProcessHandle = nullptr;
            }
        }
    
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fKey == "switch") {
                std::cout << "addButton " << std::endl;
                fPushButton.push_back(zone);
            }
            fValue = fKey = "";
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fKey == "switch") {
                std::cout << "addCheckButton " << std::endl;
                fCheckButton.push_back(zone);
            }
            fValue = fKey = "";
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addNumEntry(label, zone, init, min, max, step);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addNumEntry(label, zone, init, min, max, step);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            if (fKey == "knob") {
                if (fValue == "1") {
                    std::cout << "knob1 " << min << " " << max << std::endl;
                    fKnob1Converter.push_back(new FilteredConverter(zone, new LinearValueConverter(0., 4095., min, max)));
                } else if (fValue == "2") {
                    std::cout << "knob2 " << min << " " << max << std::endl;
                    fKnob2Converter.push_back(new FilteredConverter(zone, new LinearValueConverter(0., 4095., min, max)));
                } else if (fValue == "3") {
                    std::cout << "knob3 " << min << " " << max << std::endl;
                    // This control does not use the full range of [0 4095]
                    fKnob3Converter.push_back(new FilteredConverter(zone, new LinearValueConverter(2400., 4095., min, max)));
                }
            }
            fValue = fKey = "";
        }
    
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            if (strcmp(key, "switch") == 0 || strcmp(key, "knob") == 0) {
                std::cout << "key " << key << " val " << val << std::endl;
                fKey = key;
                fValue = val;
            }
        }
    
};

#endif // FAUST_ESP32CONTROL_H
/**************************  END  Esp32ControlUI.h **************************/
