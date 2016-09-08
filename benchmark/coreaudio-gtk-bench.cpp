/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#include <pthread.h>
#include <libgen.h>

#include "faust/audio/coreaudio-dsp.h"
#include "faust/dsp/dsp-bench.h"
#include "faust/misc.h"
#include "faust/gui/faustgtk.h"

using namespace std;

<<includeIntrinsic>>

<<includeclass>>

// Globals
bool running = true;
dsp_bench bench(600, 20);
dsp* DSP;
list<GUI*> GUI::fGuiList;

pthread_t guithread;

static void* run_ui(void* ptr)
{
    GUI* interface = (GUI*)ptr;
    interface->run();
    pthread_exit(0);
    return 0;
}

class measure_dsp : public decorator_dsp {

    public:

        measure_dsp(dsp* dsp):decorator_dsp(dsp) {}
        virtual ~measure_dsp() {}

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
        {
            bench.startMeasure();
            fDSP->compute(count, inputs, outputs);
            bench.stopMeasure();
            running = bench.isRunning();
        }
       
};

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
   char name[256];
	char rcfilename[256];
	char* home = getenv("HOME");
    snprintf(name, 255, "%s", basename(argv[0]));
	snprintf(rcfilename, 255, "%s/.%src", home, basename(argv[0]));
    
	long srate = (long)lopt(argv, "--frequency", 44100);
    int	fpb = lopt(argv, "--buffer", 512);
    
    UI* interface = new GTKUI(argv[0], &argc, &argv);
    DSP = new mydsp();
 	
    DSP->buildUserInterface(interface);
    
    pthread_create(&guithread, NULL, run_ui, interface);
   
    bench.openMeasure();
    
    coreaudio audio(srate, fpb);
    audio.init(name, new measure_dsp(DSP));
    audio.start();
    
    while (running) {
        usleep(100000);
    }
	bench.closeMeasure();

    bench.printStats(argv[0], fpb, DSP->getNumInputs(), DSP->getNumOutputs());

    audio.stop();
  	return 0;
}
