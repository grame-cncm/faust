//
//  FaustAUEffect.h
//  FaustAU
//
//  Created by Reza Payami on 11/1/13.
//
//

#ifndef FaustAU_FaustAU_h
#define FaustAU_FaustAU_h

#include <string>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/au/AUUI.h"

#define FaustAU _FaustAUClass_

enum
{
    kAudioUnitCustomProperty_dspUI = 65536
};

#define CUSTOM_VIEW_BUNDLE_ID "FaustAUCustomView"
#define CUSTOM_VIEW_BUNDLE_NAME "com.grame.audiounit.FaustAU"

#endif
