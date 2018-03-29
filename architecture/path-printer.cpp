/************************************************************************
 ************************************************************************
 FAUST Architecture File for Android
 Copyright (C) 2016 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 
 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.
 
 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#include <math.h>
#include <cmath>

#include "faust/misc.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/UI.h"

#ifdef SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

<<includeIntrinsic>>

<<includeclass>>

#include "faust/dsp/faust-poly-engine.h"
#include "faust/audio/dummy-audio.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, char *argv[])
{
    FaustPolyEngine fPolyEngine(NULL, new dummyaudio());

    std::cout << "## Parameters List\n\n";
    std::cout << "### Main Parameters\n\n";
    for(int i = 0; i < fPolyEngine.getParamsCount(); i++) {
        std::cout << "* **" << i << "**: `" << fPolyEngine.getParamAddress(i) << "`" << "\n";
    }
    std::cout << "\n";

    #if POLY_VOICES
    // kind of funny, but it's the fastest way
    MapUI* idpVoice = fPolyEngine.keyOn(100,100);

    std::cout << "### Independent Voices" << "\n\n";
    for(int i = 0; i < idpVoice->getParamsCount(); i++) {
        std::cout << "* **" << i << "**: `" << idpVoice->getParamAddress(i) << "`" << "\n";
    }

    fPolyEngine.keyOff(100); // just to be really clean...
    #endif

    return 0;
}
