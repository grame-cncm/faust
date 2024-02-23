#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "faust/dsp/libfaust-box-c.h"
#include "faust/dsp/faust-dynamic-engine.h"

using namespace std;

void test1()
{
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
    
        Box osc = CDSPToBoxes("FaustDSP", "import(\"stdfaust.lib\"); process = os.osc(500);", 0, nullptr, &inputs, &outputs, error_msg);
   
        if (!osc) {
            printf("ERROR in CDSPToBoxes : %s\n", error_msg);
            destroyLibContext();
            return;
        }
    
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


int main()
{
    test1();
    test2();
    
    return 0;
}
