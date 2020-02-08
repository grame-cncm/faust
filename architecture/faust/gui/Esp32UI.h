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
        fRec0[0] = ((0.94f * fRec0[1]) + (0.06f * float(input0)));
        float output0 = FAUSTFLOAT(fRec0[0]);
        fRec0[1] = fRec0[0];
        return output0;
    }
    
};

class Esp32UI : public GenericUI
{
    
    private:
    
        ConverterZoneControl* fGainConverter;
        CtrlFilter fGainFilter;
    
        ConverterZoneControl* fPhotoResConverter;
        CtrlFilter fPhotoResFilter;
    
        ConverterZoneControl* fKnobConverter;
        CtrlFilter fKnobFilter;
    
        FAUSTFLOAT* fButton;
        std::string fValue;
    
        TaskHandle_t fProcessHandle;
    
        void update()
        {
            while (true) {
                
                if (fGainConverter) {
                    int gain = adc1_get_raw(ADC1_CHANNEL_7);
                    FAUSTFLOAT fgain = fGainFilter.compute(FAUSTFLOAT(gain));
                    //std::cout << "gain " << gain << " " << fgain << std::endl;
                    fGainConverter->update(double(fgain));
                }
                if (fPhotoResConverter) {
                    int photores = adc1_get_raw(ADC1_CHANNEL_6);
                    FAUSTFLOAT fphotores = fPhotoResFilter.compute(FAUSTFLOAT(photores));
                    //std::cout << "photores " << photores << " " << fphotores << std::endl;
                    fPhotoResConverter->update(double(fphotores));
                }
                if (fKnobConverter) {
                    int knob = adc1_get_raw(ADC1_CHANNEL_4);
                    FAUSTFLOAT fknob = fKnobFilter.compute(FAUSTFLOAT(knob));
                    //std::cout << "knob " << knob << " " << fknob << std::endl;
                    fKnobConverter->update(double(fknob));
                }
                if (fButton) {
                    int button = gpio_get_level(GPIO_NUM_14);
                    //std::cout << "button " << button << std::endl;
                    *fButton = FAUSTFLOAT(button);
                }
                
                int encoder_dt = gpio_get_level(GPIO_NUM_4);
                int encoder_clk = gpio_get_level(GPIO_NUM_13);
                int encoder_button = gpio_get_level(GPIO_NUM_15);
                
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
                fButton(nullptr),
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
                fButton = zone;
            }
            fValue = "";
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fValue == "button") {
                std::cout << "addCheckButton " << std::endl;
                fButton = zone;
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
                fGainConverter = new ConverterZoneControl(zone, new LinearValueConverter(0., 4095., min, max));
            } else if (fValue == "photores") {
                std::cout << "photores " << min << " " << max << std::endl;
                fPhotoResConverter = new ConverterZoneControl(zone, new LinearValueConverter(0., 4095., min, max));
            } else if (fValue == "knob") {
                std::cout << "knob " << min << " " << max << std::endl;
                fKnobConverter = new ConverterZoneControl(zone, new LinearValueConverter(0., 4095., min, max));
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
