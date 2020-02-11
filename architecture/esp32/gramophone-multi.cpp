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

// we require macro declarations
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)

#include <string>
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "driver/adc.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "WM8978.h"

#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/Esp32UI.h"

// After generated C++ class to that FAUST_INPUTS and FAUST_OUTPUTS are defined
#include "faust/audio/esp32-dsp.h"

class GramophoneMulti
{
    private:
    
        esp32audio* fAudio;
        dsp* fDSP;
        Esp32UI* fControlUI;
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
    fCurrent = 0;
}

GramophoneMulti::~GramophoneMulti()
{
    stop();
    delete fDSP;
    delete fControlUI;
    delete fAudio;
}

bool GramophoneMulti::start()
{
    if (!fControlUI->start()) return false;
    return fAudio->start();
}

// Assuming several DSPs are inlcluded with this file
void GramophoneMulti::next()
{
    // Delete current resources
    delete fDSP;
    delete fControlUI;
    
    // Allocate DSP
    fCurrent = (fCurrent+1) % 5;
    switch (fCurrent) {
        case 0:
            fDSP = new mydsp1();
            break;
        case 1:
            fDSP = new mydsp2();
            break;
        case 2:
            fDSP = new mydsp3();
            break;
        case 3:
            fDSP = new mydsp4();
            break;
        case 4:
            fDSP = new mydsp5();
            break;
    }
    
    // Allocate control
    fControlUI = new Esp32UI();
    fDSP->buildUserInterface(fControlUI);
    
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
    
    // set gain
    wm8978.spkVolSet(63); // [0-63]]
    
    wm8978.hpVolSet(40,40);
    wm8978.i2sCfg(2,0);
    
    // Allocate and start Faust DSP
    GramophoneMulti* phone = new GramophoneMulti(48000, 8);
    phone->next();
    phone->start();
    
    while (true) {
        
        // Switch DSPs
        int encoder_button = gpio_get_level(GPIO_NUM_15);
        if (encoder_button == 0) {
            phone->stop();
            phone->next();
            phone->start();
        }
        
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
