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

#include "faust/dsp/dsp.h"
#include "faust/dsp/timed-dsp.h"
#include "faust/midi/midi.h"
#include "faust/gui/GUI.h"
#include "faust/gui/FUI.h"
#include "faust/gui/MapUI.h"
#include "faust/gui/APIUI.h"
#include "faust/gui/SimpleParser.h"
#include "faust/gui/JSONUI.h"
#include "faust/audio/coreaudio-ios-dsp.h"
#include "faust/misc.h"

#if SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

#if OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#if MIDICTRL
#include "faust/gui/MidiUI.h"
#include "faust/midi/rt-midi.h"
#include "faust/midi/RtMidi.cpp"
#endif

#include "faust/dsp/poly-dsp.h"

#if POLY2
#include "faust/dsp/dsp-combiner.h"
#include "effect.h"
#endif

#import "FICocoaUI.h"

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

dsp* DSP;

/********************END ARCHITECTURE SECTION (part 2/2)****************/
