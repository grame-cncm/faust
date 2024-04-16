/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN cvsplot.cpp ****************/

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

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <limits>
#include <string>
#include <iomanip>

#include "faust/audio/channels.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/console.h"
#include "faust/gui/DecoratorUI.h"
#ifdef FIXED_POINT
#include "faust/dsp/fixed-point.h"
#endif
#include "faust/misc.h"

#ifdef SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

using namespace std;

// A class to display Bargraph values
struct DisplayUI : public GenericUI {
    
    map<string, FAUSTFLOAT*> fTable;
    
    // -- passive widgets
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        fTable[label] = zone;
    }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        fTable[label] = zone;
    }
    
    void displayHeaders()
    {
        int c = 0;
        if (fTable.size() > 0)
            printf(",\t");
        for (const auto& it : fTable) {
            if (c > 0)
                printf(",\t");
            printf("bargraph %d", c + 1);
            c++;
        }
    }
    
    void display()
    {
        int c = 0;
        if (fTable.size() > 0)
            printf(",\t");
        for (const auto& it : fTable) {
            if (c > 0)
                printf(",\t");
            cout << *it.second;
            c++;
        }
    }
    
};

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

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

#define kFrames 512

int main(int argc, char* argv[])
{
    FAUSTFLOAT nb_samples, sample_rate, buffer_size, start_at_sample;
    
    DSP = new mydsp();
    
    CMDUI* interface = new CMDUI(argc, argv);
    DSP->buildUserInterface(interface);
    
    interface->addOption("-s", &start_at_sample, 0, 0.0, 100000000.0);
    interface->addOption("-n", &nb_samples, 4096.0, 0.0, 100000000.0);
    interface->addOption("-r", &sample_rate, 44100.0, 0.0, 192000.0);
    interface->addOption("-bs", &buffer_size, kFrames, 0.0, kFrames * 16);
    
    if (DSP->getNumInputs() > 0) {
        cerr << "no inputs allowed " << endl;
        exit(1);
    }
    
    // SR has to be read before DSP init
    interface->process_one_init("-r");
    
    // init signal processor and the user interface values
    DSP->init(sample_rate);
    
    // modify the UI values according to the command line options, after init
    interface->process_init();
    
#ifdef SOUNDFILE
    SoundUI soundinterface;
    DSP->buildUserInterface(&soundinterface);
#endif

    DisplayUI disp;
    DSP->buildUserInterface(&disp);
    
    // init signal processor and the user interface values
    int nouts = DSP->getNumOutputs();
    channels chan(max(kFrames, int(buffer_size)), nouts);
    
    // skip <start> samples
    int start = int(start_at_sample);
    while (start > kFrames) {
        DSP->compute(kFrames, nullptr, chan.buffers());
        start -= kFrames;
    }
    if (start > 0) {
        DSP->compute(start, nullptr, chan.buffers());
    }
    // end skip
    
    // print channel headers
    for (int c = 0; c < nouts; c++) {
        if (c > 0)
            printf(",\t");
        printf("channel %d", c + 1);
    }
    disp.displayHeaders();
    cout << endl;
    
    int nbsamples = int(nb_samples);
    cout << setprecision(numeric_limits<FAUSTFLOAT>::max_digits10);
    
    // print by buffer
    while (nbsamples > buffer_size) {
        DSP->compute(buffer_size, 0, chan.buffers());
        for (int i = 0; i < buffer_size; i++) {
            for (int c = 0; c < nouts; c++) {
                if (c > 0)
                    printf(",\t");
                cout << chan.buffers()[c][i];
            }
            disp.display();
            cout << endl;
        }
        nbsamples -= buffer_size;
    }
    
    // print remaining frames
    if (nbsamples) {
        DSP->compute(nbsamples, 0, chan.buffers());
        for (int i = 0; i < nbsamples; i++) {
            for (int c = 0; c < nouts; c++) {
                if (c > 0)
                    printf(",\t");
                cout << chan.buffers()[c][i];
            }
            disp.display();
            cout << endl;
        }
    }
    
    delete DSP;
    return 0;
}

/******************** END cvsplot.cpp ****************/

