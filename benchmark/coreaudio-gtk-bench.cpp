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
list<GUI*> GUI::fGuiList;
pthread_t gThread;

static void* runUI(void* ptr)
{
    GUI* interface = (GUI*)ptr;
    interface->run();
    pthread_exit(0);
    return 0;
}

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char name[256];
    char* home = getenv("HOME");
    snprintf(name, 255, "%s", basename(argv[0]));

    long srate = (long)lopt(argv, "--frequency", 44100);
    int	fpb = lopt(argv, "--buffer", 512);

    UI* interface = new GTKUI(argv[0], &argc, &argv);
    measure_dsp* dsp = new measure_dsp(new mydsp(), fpb, 600, 20);
    dsp->buildUserInterface(interface);

    pthread_create(&gThread, NULL, runUI, interface);

    // Measuring DSP...
    dsp->openMeasure();

    coreaudio audio(srate, fpb);
    audio.init(name, dsp);
    audio.start();

    while (dsp->isRunning()) {
        usleep(100000);
    }
           
    dsp->closeMeasure();
    dsp->printStats(argv[0]);

    audio.stop();
    return 0;
}
