/************************** BEGIN Esp32UI.h **************************/
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

#ifndef FAUST_ESP32_H
#define FAUST_ESP32_H

#include <string>
#include <iostream>
#include <string.h>

#include "driver/uart.h"

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/ValueConverter.h"

/*******************************************************************************
 * Esp32UI : Faust User Interface
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
class Esp32UI : public GenericUI
{
    
    private:
    
        FilteredConverter* fGainConverter;
        FilteredConverter* fPhotoResConverter;
        FilteredConverter* fKnobConverter;
    
        FAUSTFLOAT* fPushButton;
        std::string fValue;
    
        TaskHandle_t fProcessHandle;
    
        void update()
        {
            while (true) {
                
                if (fGainConverter) {
                    int gain = adc1_get_raw(ADC1_CHANNEL_7);
                    fGainConverter->update(double(gain));
                }
                if (fPhotoResConverter) {
                    int photores = adc1_get_raw(ADC1_CHANNEL_6);
                    fPhotoResConverter->update(double(photores));
                }
                if (fKnobConverter) {
                    int knob = adc1_get_raw(ADC1_CHANNEL_4);
                    fKnobConverter->update(double(knob));
                }
                if (fPushButton) {
                    int push_button = gpio_get_level(GPIO_NUM_14);
                    //std::cout << "button " << button << std::endl;
                    *fPushButton = FAUSTFLOAT(push_button);
                }
                
                int encoder_dt = gpio_get_level(GPIO_NUM_4);
                int encoder_clk = gpio_get_level(GPIO_NUM_13);
                
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
        }
    
        static void updateHandler(void* arg)
        {
            static_cast<Esp32UI*>(arg)->update();
        }
    
    public:
        
        Esp32UI():fGainConverter(nullptr),
                fPhotoResConverter(nullptr),
                fKnobConverter(nullptr),
                fPushButton(nullptr),
                fProcessHandle(nullptr)
        {
            adc1_config_width(ADC_WIDTH_BIT_12);
            
            gpio_config_t io_conf;
            io_conf.intr_type = (gpio_int_type_t) GPIO_PIN_INTR_POSEDGE;
            io_conf.pin_bit_mask = ((1ULL<<4) | (1ULL<<13) | (1ULL<<14) | (1ULL<<15));
            io_conf.mode = GPIO_MODE_INPUT;
            io_conf.pull_up_en = (gpio_pullup_t)1;
            gpio_config(&io_conf);
        }
    
        virtual ~Esp32UI()
        {
            delete fGainConverter;
            delete fPhotoResConverter;
            delete fKnobConverter;
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
            if (fValue == "button") {
                std::cout << "addButton " << std::endl;
                fPushButton = zone;
            }
            fValue = "";
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fValue == "button") {
                std::cout << "addCheckButton " << std::endl;
                fPushButton = zone;
            }
            fValue = "";
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
            if (fValue == "gain") {
                std::cout << "gain " << min << " " << max << std::endl;
                fGainConverter = new FilteredConverter(zone, new LinearValueConverter(0., 4095., min, max));
            } else if (fValue == "photores") {
                std::cout << "photores " << min << " " << max << std::endl;
                fPhotoResConverter = new FilteredConverter(zone, new LinearValueConverter(0., 4095., min, max));
            } else if (fValue == "knob") {
                std::cout << "knob " << min << " " << max << std::endl;
                fKnobConverter = new FilteredConverter(zone, new LinearValueConverter(0., 4095., min, max));
            }
            fValue = "";
        }
    
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            if (strcmp(key, "esp32") == 0) {
                std::cout << "val " << val << std::endl;
                fValue = val;
            }
        }
    
};

#endif // FAUST_ESP32UI_H
/**************************  END  Esp32UI.h **************************/
