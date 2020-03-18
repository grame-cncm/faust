/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2020 GRAME, Centre National de Creation Musicale &
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
#include "faust/gui/Esp32ControlUI.h"
#include "faust/gui/Esp32SensorUI.h"
#include "faust/audio/esp32-dsp.h"

#ifdef SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

class Gramophone
{
    private:
    
        esp32audio* fAudio;
        dsp* fDSP;
        Esp32ControlUI* fControlUI;
        Esp32SensorUI* fSensorUI;
    #ifdef SOUNDFILE
        SoundUI* fSoundUI;
    #endif
    
    public:
    
        Gramophone(int sample_rate, int buffer_size);
        ~Gramophone();
    
        bool start();
        void stop();
};

Gramophone::Gramophone(int sample_rate, int buffer_size)
{
    fDSP = new mydsp();
    
    fControlUI = new Esp32ControlUI();
    fDSP->buildUserInterface(fControlUI);
    
    fSensorUI = new Esp32SensorUI();
    fDSP->buildUserInterface(fSensorUI);
    
#ifdef SOUNDFILE
    fSoundUI = new SoundUI();
    fDSP->buildUserInterface(fSoundUI);
#endif
   
    fAudio = new esp32audio(sample_rate, buffer_size);
    fAudio->init("esp32", fDSP);
}

Gramophone::~Gramophone()
{
    stop();
    delete fDSP;
    delete fControlUI;
    delete fSensorUI;
    delete fAudio;
#ifdef SOUNDFILE
    delete fSoundUI;
#endif
}

bool Gramophone::start()
{
    if (!fControlUI->start()) return false;
    if (!fSensorUI->start()) return false;
    return fAudio->start();
}

void Gramophone::stop()
{
    fControlUI->stop();
    fSensorUI->stop();
    fAudio->stop();
}

// Entry point
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
    Gramophone* phone = new Gramophone(48000, 32);
    phone->start();
    
    // Waiting forever
    vTaskSuspend(nullptr);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
