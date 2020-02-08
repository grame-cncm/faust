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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"

#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/MapUI.h"
#include "faust/gui/Esp32UI.h"

// MIDI support
#if MIDICTRL
#include "faust/gui/MidiUI.h"
#include "faust/midi/esp32-midi.h"
#endif

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "WM8978.h"
#include <driver/adc.h>

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

// After generated C++ class to that FAUST_INPUTS and FAUST_OUTPUTS are defined
#include "faust/audio/esp32-dsp.h"

#define MULT_S32 2147483647
#define DIV_S32 4.6566129e-10
#define clip(sample) std::max(-MULT_S32, std::min(MULT_S32, ((int32_t)(sample * MULT_S32))));

#if MIDICTRL
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
#endif

class Gramophone
{
    private:
    
        esp32audio* fAudio;
        dsp* fDSP;
        MapUI* fUI;
        Esp32UI* fControlUI;
    
    public:
    
        Gramophone(int sample_rate, int buffer_size);
        ~Gramophone();
    
        bool start();
        void stop();
    
        void setParamValue(const std::string& path, float value);
    
};

Gramophone::Gramophone(int sample_rate, int buffer_size)
{
    fDSP = new mydsp();
    
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);
    
    fControlUI = new Esp32UI();
    fDSP->buildUserInterface(fControlUI);
    
    fAudio = new esp32audio(sample_rate, buffer_size);
    fAudio->init("esp32", fDSP);
}

Gramophone::~Gramophone()
{
    delete fDSP;
    delete fUI;
    delete fControlUI;
    delete fAudio;
}

bool Gramophone::start()
{
    if (!fControlUI->start()) return false;
    return fAudio->start();
}

void Gramophone::stop()
{
    fControlUI->stop();
    fAudio->stop();
}

void Gramophone::setParamValue(const std::string& path, float value)
{
    fUI->setParamValue(path, value);
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
    Gramophone* phone = new Gramophone(48000, 8);
    phone->start();
    
    // Waiting forever
    vTaskSuspend(nullptr);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
