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

//**************************************************************
// DSP class
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>

//**************************************************************
// Audio engine
//**************************************************************

#include "faust/dsp/faust-poly-engine.h"

//**************************************************************
// Android Audio
//**************************************************************

#include "faust/audio/android-dsp.h"

//**************************************************************
// Native Faust API
//**************************************************************

#include <android/log.h>
#include "dsp_faust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

extern "C" void* create(int sample_rate, int buffer_size)
{
    return new FaustPolyEngine(new androidaudio(sample_rate, buffer_size));
}

