/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2024 GRAME, Centre National de Creation Musicale
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

#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "faust/dsp/libfaust-box-c.h"
#include "faust/dsp/libfaust-signal-c.h"
#include "faust/dsp/faust-dynamic-engine.h"

using namespace std;

void test1()
{
    // Create an osc DSP using a code string
    const char* code = "import(\"stdfaust.lib\"); process = os.osc(500);";
    dsp* DSP = createDsp("Test1", code, 0, NULL, "", -1);
    if (!DSP) {
        printf("ERROR in createDsp : %s", getLastError());
        return;
    }
    initDsp(DSP, kPortAudioRenderer, 44100, 512);
    startDsp(DSP);

    printf("Type 'n' to go to next test\n");
    char c;
    while ((c = getchar()) && (c != 'n')) { usleep(100000); }

    stopDsp(DSP);
    destroyDsp(DSP);
}

void test2()
{
    dsp* DSP;
    
    createLibContext();
    {
        int inputs = 0;
        int outputs = 0;
        char error_msg[4096];
    
        // Create an osc DSP using a code string
        Box osc = CDSPToBoxes("FaustDSP", "import(\"stdfaust.lib\"); process = os.osc(500);", 0, nullptr, &inputs, &outputs, error_msg);
        if (!osc) {
            printf("ERROR in CDSPToBoxes : %s\n", error_msg);
            destroyLibContext();
            return;
        }
    
        // Then multiply by a slider gain
        Box gain = CboxHSlider("gain", CboxReal(0.5), CboxReal(0), CboxReal(1), CboxReal(0.01));
        Box gainOsc = CboxMulAux(gain, osc);
     
        CgetBoxType(gainOsc, &inputs, &outputs);
        std::cout << "getBoxType inputs: " << inputs << " outputs: " << outputs << std::endl;
    
        DSP = createDspFromBoxes("Test2", gainOsc, 0, NULL, "", -1);
    }
    destroyLibContext();
    
    initDsp(DSP, kPortAudioRenderer, 44100, 512);
    startDsp(DSP);
    
    printf("Type 'n' to go to next test\n");
    char c;
    while ((c = getchar()) && (c != 'n')) { usleep(100000); }
    
    stopDsp(DSP);
    destroyDsp(DSP);
}

void test3()
{
    dsp* DSP;
    
    createLibContext();
    {
        int inputs = 0;
        int outputs = 0;
        char error_msg[4096];
        
        // Create an osc DSP using a code string
        Box osc = CDSPToBoxes("FaustDSP", "import(\"stdfaust.lib\"); process = os.osc(500);", 0, nullptr, &inputs, &outputs, error_msg);
        if (!osc) {
            printf("ERROR in CDSPToBoxes : %s\n", error_msg);
            destroyLibContext();
            return;
        }
    
        // Compile to signals
        Signal* signals = CboxesToSignals(osc, error_msg);
        if (!signals) {
            printf("%s", error_msg);
            destroyLibContext();
            return;
        }
    
        // Then multiply by a slider gain
        Signal gain = CsigVSlider("gain", CsigReal(0.2), CsigReal(0), CsigReal(1), CsigReal(0.011));
        signals[0] = CsigMul(gain, signals[0]);
        
        DSP = createDspFromSignals("Test3", signals, 0, NULL, "", -1);
    }
    destroyLibContext();
    
    initDsp(DSP, kPortAudioRenderer, 44100, 512);
    startDsp(DSP);
    
    printf("Type 'n' to go to next test\n");
    char c;
    while ((c = getchar()) && (c != 'n')) { usleep(100000); }
    
    stopDsp(DSP);
    destroyDsp(DSP);
}
int main()
{
    test1();
    test2();
    test3();
    
    return 0;
}
