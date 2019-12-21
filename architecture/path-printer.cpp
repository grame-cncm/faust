/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

#include <cmath>
#include <cstring>

#include "faust/misc.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/UI.h"
#include "faust/gui/JSONUIDecoder.h"

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

#include "faust/dsp/faust-poly-engine.h"
#include "faust/audio/dummy-audio.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, char* argv[])
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

/********************END ARCHITECTURE SECTION (part 2/2)****************/


