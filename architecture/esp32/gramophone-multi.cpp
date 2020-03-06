/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale &
 Aalborg University (Copenhagen, Denmark)
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

#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"

#ifdef class_mydsp1
#include "mydsp1.h"
#endif

#ifdef class_mydsp2
#include "mydsp2.h"
#endif

#ifdef class_mydsp3
#include "mydsp3.h"
#endif

#ifdef class_mydsp4
#include "mydsp4.h"
#endif

#ifdef class_mydsp5
#include "mydsp5.h"
#endif

#include <string>
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "driver/adc.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "WM8978.h"

#include "faust/gui/Esp32ControlUI.h"
#include "faust/gui/Esp32SensorUI.h"
#include "faust/audio/esp32-dsp.h"

class GramophoneMulti
{
    private:
    
        esp32audio* fAudio;
        dsp* fDSP;
        Esp32ControlUI* fControlUI;
        Esp32SensorUI* fSensorUI;
        int fCurrent;
    
    public:
    
        GramophoneMulti(int sample_rate, int buffer_size);
        ~GramophoneMulti();
    
        bool start();
        void stop();
        void next();
};

GramophoneMulti::GramophoneMulti(int sample_rate, int buffer_size)
{
    fAudio = new esp32audio(sample_rate, buffer_size);
    fDSP = nullptr;
    fControlUI = nullptr;
    fSensorUI = nullptr;
    fCurrent = 0;
}

GramophoneMulti::~GramophoneMulti()
{
    stop();
    delete fDSP;
    delete fControlUI;
    delete fSensorUI;
    delete fAudio;
}

bool GramophoneMulti::start()
{
    if (!fControlUI->start()) return false;
    if (!fSensorUI->start()) return false;
    return fAudio->start();
}

void GramophoneMulti::stop()
{
    fControlUI->stop();
    fSensorUI->stop();
    fAudio->stop();
}

// Instantiate next DSP (assuming several DSPs are included with this file)
void GramophoneMulti::next()
{
    // Delete current resources
    delete fDSP;
    delete fControlUI;
    delete fSensorUI;
    
    // Allocate DSP
    switch (fCurrent) {
        case 0:
        #ifdef class_mydsp1
            fDSP = new mydsp1();
        #endif
            break;
        case 1:
        #ifdef class_mydsp2
            fDSP = new mydsp2();
        #endif
            break;
        case 2:
        #ifdef class_mydsp3
            fDSP = new mydsp3();
        #endif
            break;
        case 3:
        #ifdef class_mydsp4
            fDSP = new mydsp4();
        #endif
            break;
        case 4:
        #ifdef class_mydsp5
            fDSP = new mydsp5();
        #endif
            break;
    }
    fCurrent = (fCurrent+1) % gMydspCount;
    
    // Allocate control
    fControlUI = new Esp32ControlUI();
    fDSP->buildUserInterface(fControlUI);
    
    fSensorUI = new Esp32SensorUI();
    fDSP->buildUserInterface(fSensorUI);
    
    // Connect with audio
    fAudio->init("esp32", fDSP);
}

extern "C" void app_main()
{
    // Init audio codec
    WM8978 wm8978;
    wm8978.init();
    wm8978.addaCfg(1,1);
    wm8978.inputCfg(1,0,0);
    wm8978.outputCfg(1,0);
    wm8978.micGain(30);
    wm8978.auxGain(0);
    wm8978.lineinGain(0);
    
    // Set gain
    wm8978.spkVolSet(60); // [0-63]
    
    wm8978.hpVolSet(40,40);
    wm8978.i2sCfg(2,0);
    
    // Allocate and start Faust DSP
    GramophoneMulti* phone = new GramophoneMulti(48000, 32);
    phone->next();
    phone->start();
    
    while (true) {
        
        // Instantiate next DSP
        int encoder_button = gpio_get_level(GPIO_NUM_15);
        if (encoder_button == 0) {
            phone->stop();
            phone->next();
            phone->start();
        }
        
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}
