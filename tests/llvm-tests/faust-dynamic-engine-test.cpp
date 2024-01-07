
#include <assert.h>
#include <unistd.h>

#include "faust/dsp/faust-dynamic-engine.cpp"
#include "faust/dsp/libfaust-box.h"

static void test1()
{
    // Create a DSP engine with a simple sine oscillator
    const char* code = "import(\"stdfaust.lib\"); process = os.osc(500);";
    dsp*        DSP = createDsp("Osc", code, 0, NULL, "", -1);
    assert(DSP);

    // Initialize the DSP engine with JACK as renderer
    // bool res = initDsp(DSP1, kJackRenderer, -1, -1);
    bool res = initDsp(DSP, kRtAudioRenderer, 44100, 512);
    // bool res = initDsp(DSP1, kPortAudioRenderer, 44100, 512);
    assert(res);

    // Start the DSP engine
    startDsp(DSP);

    char c;
    printf("Press 'q' to move to next test\n");
    while ((c = getchar() != 'q')) {
        usleep(100000);
    }

    // Stop the DSP engine and destroy it
    stopDsp(DSP);
    destroyDsp(DSP);
}

static void test2()
{
    // Create a DSP engine with a soundfile player
    const char* code = "process = 0,_~+(1):soundfile(\"sound[url:{'tango.wav'}]\",2):!,!,_,_;";
    dsp*        DSP = createDsp("Player", code, 0, NULL, "", -1);
    assert(DSP);

    // Initialize the DSP engine with JACK as renderer
    bool res = initDsp(DSP, kJackRenderer, -1, -1);
    assert(res);

    // Start the DSP engine
    startDsp(DSP);

    char c;
    printf("Press 'q' to move to next test\n");
    while ((c = getchar() != 'q')) {
        usleep(100000);
    }

    // Stop the DSP engine and destroy it
    stopDsp(DSP);
    destroyDsp(DSP);
}

static void test2bis()
{
    // Create a compilation context
    createLibContext();
    
    // Create a soundfile player box
    int inputs = 0;
    int outputs = 0;
    string error_msg;
    Box player = DSPToBoxes("FaustDSP", "process = 0,_~+(1):soundfile(\"sound[url:{'tango.wav'}]\",2):!,!,_,_;", 0, nullptr, &inputs, &outputs, error_msg);
    
    // Create a DSP engine with the soundfile player box
    dsp* DSP = createDspFromBoxes("Player", player, 0, NULL, "", -1);
    assert(DSP);
    
    // Initialize the DSP engine with JACK as renderer
    bool res = initDsp(DSP, kJackRenderer, -1, -1);
    assert(res);
    
    // Start the DSP engine
    startDsp(DSP);
    
    char c;
    printf("Press 'q' to move to next test\n");
    while ((c = getchar() != 'q')) {
        usleep(100000);
    }
    
    // Stop the DSP engine and destroy it
    stopDsp(DSP);
    destroyDsp(DSP);
    
    // Destroy the compilation context
    destroyLibContext();
}

static void test3()
{
    // Create a DSP engine with a soundfile player
    const char* code1 = "process = 0,_~+(1):soundfile(\"sound[url:{'tango.wav'}]\",2):!,!,_,_;";
    dsp*        DSP1  = createDsp("Player", code1, 0, NULL, "", -1);
    assert(DSP1);

    // Initialize the DSP engine with JACK as renderer
    bool res1 = initDsp(DSP1, kJackRenderer, -1, -1);
    assert(res1);

    // Start the DSP engine
    startDsp(DSP1);

    // Create a DSP engine with a freeverb
    const char* code2 = "import(\"stdfaust.lib\"); process = dm.freeverb_demo;";
    dsp*        DSP2  = createDsp("Reverb", code2, 0, NULL, "", -1);
    assert(DSP2);

    // Initialize the DSP engine with JACK as renderer
    bool res2 = initDsp(DSP2, kJackRenderer, -1, -1);
    assert(res1);

    // Start the DSP engine
    startDsp(DSP2);

    for (int param = 0; param < getParamsCountDsp(DSP2); param++) {
        printf("Param %d: %s\n", param, getParamAddressDsp(DSP2, param));
    }

    // Set the wet parameter of the freeverb to 0.9
    setParamValueDsp(DSP2, getParamIndexDsp(DSP2, "/Freeverb/Wet"), 0.9);

    // Disconnect all connections to JACK
    disconnectDsp(DSP1, NULL, 0, 0);
    disconnectDsp(DSP1, NULL, 1, 1);

    // Connect Player to Reverb
    connectDsp(DSP1, DSP2, 0, 0);
    connectDsp(DSP1, DSP2, 1, 1);

    // Connect Reverb to JACK
    connectDsp(DSP2, NULL, 0, 0);
    connectDsp(DSP2, NULL, 1, 1);

    char c;
    printf("Press 'q' to move to next test\n");
    while ((c = getchar() != 'q')) {
        usleep(100000);
    }

    // Stop the DSP engine and destroy it
    stopDsp(DSP1);
    destroyDsp(DSP1);

    // Stop the DSP engine and destroy it
    stopDsp(DSP2);
    destroyDsp(DSP2);
}

int main()
{
    test1();
    test2();
    test2bis();
    test3();
    return 0;
}
