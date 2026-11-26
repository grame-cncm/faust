#include "audio_inputs.h"

namespace AudioInputs
{
    audioInputList getAudioInputList()
    {
        audioInputList myAudioInputList;
        int ctr = 0;
        #define X(ClassName, label) myAudioInputList.emplace_back(ctr++, label);
        AUDIO_INPUT_LIST
        #undef X
        return myAudioInputList;
    }

    dsp* createAudioInputById(int id)
    {
        int ctr = 0;
        #define X(ClassName, label) if (id == ctr++) return new ClassName();    
        AUDIO_INPUT_LIST
        #undef X
    }
}