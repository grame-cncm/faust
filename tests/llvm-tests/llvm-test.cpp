/************************************************************************
    FAUST Architecture File
    Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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

#include <libgen.h>

#include "faust/dsp/llvm-dsp.h"
#include "faust/audio/dummy-audio.h"
#include "faust/misc.h"

using namespace std;

static void printList(const vector<string>& list)
{
    for (int i = 0; i < list.size(); i++) {
        std::cout << "item: " << list[i] << "\n";
    }
}

int main(int argc, char* argv[])
{
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "llvm-test foo.dsp" << endl;
        exit(EXIT_FAILURE);
    }
    
    string error_msg;
    
    cout << "Libfaust version : " << getCLibFaustVersion () << endl;
    dsp_factory* factory = createDSPFactoryFromFile(argv[argc-1], 0, NULL, "", error_msg, -1);
    
    if (!factory) {
        cerr << "Cannot create factory : " << error_msg;
        exit(EXIT_FAILURE);
    }
    
    cout << "getCompileOptions " << factory->getCompileOptions() << endl;
    printList(factory->getLibraryList());
    printList(factory->getIncludePathnames());    
    
    dsp* DSP = factory->createDSPInstance();
    if (!DSP) {
        cerr << "Cannot create instance "<< endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "getName " << factory->getName() << endl;
    cout << "getSHAKey " << factory->getSHAKey() << endl;
    
    dummyaudio audio(2);
    if (!audio.init("FaustDSP", DSP)) {
        return 0;
    }
    
    audio.start();
    audio.stop();
    
    delete DSP;
    deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
    
    return 0;
}

