/*******************************************************************************
This header file defines the structure for managing different audio input 
generators for a DSP effects. 
The file includes the declaration of available audio inputs and provides the 
mechanism to retrieve and create these audio inputs by ID. 
The list of available audio inputs is defined using macros, and each input 
corresponds to a specific audio generator or effect (e.g., Sine wave, Wind, 
Rain, etc.).
*******************************************************************************/

#ifndef AUDIO_INPUTS_H
#define AUDIO_INPUTS_H

#include "Generators/sine440.cpp"
#include "Generators/wind.cpp"
#include "Generators/complexRain.cpp"
#include "Generators/fmSynthAnalog.cpp"
#include "Generators/insects.cpp"
#include "Generators/windchimes.cpp"
#include "Generators/waveSynthAnalog.cpp"

#define AUDIO_INPUT_LIST \
    X(Sine440, L"Sine wave (440Hz)") \
    X(Wind, L"Wind") \
    X(ComplexRain, L"Complex Rain") \
    X(FMSynthAnalog, L"FMSynthAnalog") \
    X(Insects, L"Insects") \
    X(WaveSynthAnalog, L"WaveSynthAnalog") \
    X(Windchimes, L"Windchimes")

#define DEFAUT_AUDIO_INPUT_FOR_EFFECTS 0

#include <string>
#include <vector>
#include <utility>

typedef std::vector<std::pair<int, const wchar_t*>> audioInputList;

namespace AudioInputs{

    /* Function to retrieve the full list of available audio inputs, typically returning an audioInputList.*/
    audioInputList getAudioInputList();

    /* Function that returns a new dsp instance. The caller is responsible for destroying the dsp object on time. */
    dsp* createAudioInputById(int id);
}

#endif