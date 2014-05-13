/*
 faust2webaudio
 
 Primarily written by Myles Borins
 During the Spring 2013 offering of Music 420b with Julius Smith
 A bit during the Summer of 2013 with the help of Joshua Kit Clayton
 And finally a sprint during the late fall of 2013 to get everything working
 A Special thanks to Yann Orlarey and Stéphane Letz
 
 faust2webaudio is distributed under the terms the MIT or GPL2 Licenses.
 Choose the license that best suits your project. The text of the MIT and GPL
 licenses are at the root directory.
 
 Additional code : GRAME 2014

*/

// Adapted From https://gist.github.com/camupod/5640386
// compile using "C" linkage to avoid name obfuscation

#include <emscripten.h>
#include <vector>
#include <map>
#include <string>
#include <math.h>

#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"
#include "faust/audio/dsp.h"

// "mydsp" part will be replaced by the actual '-cn' parameter

// Usage : faust -i -uim -a webaudio/webaudio-asm.cpp -cn karplus karplus.dsp -o karplus.cpp

inline int max(unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int max(int a, int b)	{ return (a>b) ? a : b; }

inline long max(long a, long b) { return (a>b) ? a : b; }
inline long max(int a, long b) 	{ return (a>b) ? a : b; }
inline long max(long a, int b) 	{ return (a>b) ? a : b; }

inline float max(float a, float b) { return (a>b) ? a : b; }
inline float max(int a, float b) 	{ return (a>b) ? a : b; }
inline float max(float a, int b) 	{ return (a>b) ? a : b; }
inline float max(long a, float b) 	{ return (a>b) ? a : b; }
inline float max(float a, long b) 	{ return (a>b) ? a : b; }

inline double max(double a, double b) 	{ return (a>b) ? a : b; }
inline double max(int a, double b)      { return (a>b) ? a : b; }
inline double max(double a, int b)      { return (a>b) ? a : b; }
inline double max(long a, double b) 	{ return (a>b) ? a : b; }
inline double max(double a, long b) 	{ return (a>b) ? a : b; }
inline double max(float a, double b) 	{ return (a>b) ? a : b; }
inline double max(double a, float b) 	{ return (a>b) ? a : b; }

inline int	min(int a, int b)	{ return (a<b) ? a : b; }

inline long min(long a, long b) { return (a<b) ? a : b; }
inline long min(int a, long b) 	{ return (a<b) ? a : b; }
inline long min(long a, int b) 	{ return (a<b) ? a : b; }

inline float min(float a, float b) { return (a<b) ? a : b; }
inline float min(int a, float b) 	{ return (a<b) ? a : b; }
inline float min(float a, int b) 	{ return (a<b) ? a : b; }
inline float min(long a, float b) 	{ return (a<b) ? a : b; }
inline float min(float a, long b) 	{ return (a<b) ? a : b; }

inline double min(double a, double b) 	{ return (a<b) ? a : b; }
inline double min(int a, double b)      { return (a<b) ? a : b; }
inline double min(double a, int b)      { return (a<b) ? a : b; }
inline double min(long a, double b) 	{ return (a<b) ? a : b; }
inline double min(double a, long b) 	{ return (a<b) ? a : b; }
inline double min(float a, double b) 	{ return (a<b) ? a : b; }
inline double min(double a, float b) 	{ return (a<b) ? a : b; }

<<includeIntrinsic>>

<<includeclass>>

extern "C" {
    
    #define MAX_BUFFER_SIZE 1024
    
    inline float midiToFreq(int note) 
    {
          return 440.0f * powf(2.0f, ((float(note))-69.0f)/12.0f);
    }
    
    struct mydsp_voice : public MapUI {
        mydsp fVoice;
        int fNote;
        
        mydsp_voice(int samplingFreq)
        {
            fVoice.init(samplingFreq);
            fNote = -1;
            fVoice.buildUserInterface(this);
        }
    };
    
    struct mydsp_poly_wrap
    {
        std::string fJSON;
        
        mydsp_voice** fVoiceTable;
        
        std::string fGateLabel;
        std::string fGainLabel;
        std::string fFreqLabel;
        
        int fMaxPolyphony;
        
        FAUSTFLOAT** fNoteOutputs;
        int fNumOutputs;
        
        inline void mixVoice(int count, FAUSTFLOAT** outputBuffer, FAUSTFLOAT** mixBuffer) 
        {
            for (int i = 0; i < fNumOutputs; i++) {
                float* mixChannel = mixBuffer[i];
                float* outChannel = outputBuffer[i];
                for (int j = 0; j < count; j++) {
                    mixChannel[j] += outChannel[j];
                }
            }
        }
        
        inline void clearMix(int count, FAUSTFLOAT** mixBuffer) 
        {
            for (int i = 0; i < fNumOutputs; i++) {
                memset(mixBuffer[i], 0, count * sizeof(FAUSTFLOAT));
            }
        }
        
        inline int getFreeVoice()
        {
            for (int i = 0; i < fMaxPolyphony; i++) {
                if (fVoiceTable[i]->fNote == -1) return i;
            }
            return -1;
        }
        
        inline int getPlayingVoice(int note)
        {
            for (int i = 0; i < fMaxPolyphony; i++) {
                if (fVoiceTable[i]->fNote == note) return i;
            }
            return -1;
        }
        
        mydsp_poly_wrap(int samplingFreq, int max_polyphony)
        {
            fMaxPolyphony = max_polyphony;
            fVoiceTable = new mydsp_voice*[max_polyphony];
            
            // Init it with samplingFreq supplied...
            for (int i = 0; i < fMaxPolyphony; i++) {
                fVoiceTable[i] = new mydsp_voice(samplingFreq);
            }
            
            // Init audio output buffers
            fNumOutputs = fVoiceTable[0]->fVoice.getNumOutputs();
            fNoteOutputs = new FAUSTFLOAT*[fNumOutputs];
            for (int i = 0; i < fNumOutputs; i++) {
                fNoteOutputs[i] = new FAUSTFLOAT[MAX_BUFFER_SIZE];
            }
            
            // Creates JSON
            JSONUI builder(fVoiceTable[0]->fVoice.getNumInputs(), fVoiceTable[0]->fVoice.getNumOutputs());
            mydsp::metadata(&builder);
            fVoiceTable[0]->fVoice.buildUserInterface(&builder);
            fJSON = builder.JSON();
            
            // Keep gain, freq and gate labels
            std::map<std::string, FAUSTFLOAT*>::iterator it;
            
            for (it = fVoiceTable[0]->getMap().begin(); it != fVoiceTable[0]->getMap().end(); it++) {
                std::string label = (*it).first;
                if (label.find("gate") != std::string::npos) {
                    fGateLabel = label;
                } else if (label.find("freq") != std::string::npos) {
                    fFreqLabel = label;
                } else if (label.find("gain") != std::string::npos) {
                    fGainLabel = label;
                }
            }
        }
        
        virtual ~mydsp_poly_wrap()
        {
            for (int i = 0; i < fNumOutputs; i++) {
                delete[] fNoteOutputs[i];
            }
            delete[] fNoteOutputs;
            
            for (int i = 0; i < fMaxPolyphony; i++) {
                delete fVoiceTable[i];
            }
            delete [] fVoiceTable;
        }
        
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
        {
            // First clear the outputs
            clearMix(count, outputs);
              
            // Then mix all voices
            for (int i = 0; i < fMaxPolyphony; i++) {
                fVoiceTable[i]->fVoice.compute(count, inputs, fNoteOutputs);
                mixVoice(count, fNoteOutputs, outputs);
            }
        }
        
        int getNumInputs()
        {
            return fVoiceTable[0]->fVoice.getNumInputs();
        }
        
        int getNumOutputs()
        {
            return fVoiceTable[0]->fVoice.getNumOutputs();
        }
        
        void noteOn(int pitch, int velocity)
        {
            int voice = getFreeVoice();
            if (voice >= 0) {
                fVoiceTable[voice]->setValue(fFreqLabel, midiToFreq(pitch));
                fVoiceTable[voice]->setValue(fGainLabel, float(velocity)/127.f);
                fVoiceTable[voice]->setValue(fGateLabel, 1.0f);
                fVoiceTable[voice]->fNote = pitch;
            } else {
                printf("No more free voice...\n");
            }
        }
        
        void noteOff(int pitch)
        {
            int voice = getPlayingVoice(pitch);
            if (voice >= 0) {
                fVoiceTable[voice]->setValue(fGateLabel, 0.0f);
                fVoiceTable[voice]->fNote = -1;
            } else {
                printf("Playing voice not found...\n");
            }
        }
        
        void getJSON(char* json)
        {
            strcpy(json, fJSON.c_str());
        }
        
        void setValue(const char* path, float value)
        {
            for (int i = 0; i < fMaxPolyphony; i++) {
                fVoiceTable[i]->setValue(path, value);
            }
        }
        
        float getValue(const char* path)
        {
            return fVoiceTable[0]->getValue(path);
        }
        
    };
        
    // C like API
    mydsp_poly_wrap* mydsp_poly_constructor(int samplingFreq, int max_polyphony) 
    {
         return new mydsp_poly_wrap(samplingFreq, max_polyphony);
    }
    
    void mydsp_poly_destructor(mydsp_poly_wrap* n) 
    {
        delete n;
    }
    
    void mydsp_poly_getJSON(mydsp_poly_wrap* n, char* json)
    {
        n->getJSON(json);
    }
    
    void mydsp_poly_compute(mydsp_poly_wrap* n, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
    {
        n->compute(count, inputs, outputs);
    }
    
    int mydsp_poly_getNumInputs(mydsp_poly_wrap* n)
    {
        return n->getNumInputs();
    }
    
    int mydsp_poly_getNumOutputs(mydsp_poly_wrap* n)
    {
        return n->getNumOutputs();
    }
    
    void mydsp_poly_noteOn(mydsp_poly_wrap* n, int channel, int pitch, int velocity)
    {
        n->noteOn(pitch, velocity);
    }
    
    void mydsp_poly_noteOff(mydsp_poly_wrap* n, int channel, int pitch)
    {
        n->noteOff(pitch);
    }
    
    void mydsp_poly_setValue(mydsp_poly_wrap* n, const char* path, float value)
    {
        n->setValue(path, value);
    }
    
    float mydsp_poly_getValue(mydsp_poly_wrap* n, const char* path)
    {
        return n->getValue(path);
    }
    
    
    // Just inherit from both classes...
    struct mydsp_wrap : public mydsp, public MapUI
    {
        std::string fJSON;
        
        mydsp_wrap(int samplingFreq) 
        {
            // Init it with samplingFreq supplied...
            init(samplingFreq);
            buildUserInterface(this);
            
            // Creates JSON
            JSONUI builder(getNumInputs(), getNumOutputs());
            mydsp::metadata(&builder);
            buildUserInterface(&builder);
            fJSON = builder.JSON();
        }
        
        void getJSON(char* json)
        {
            strcpy(json, fJSON.c_str());
        }
    };
    
    
    // C like API
    mydsp_wrap* mydsp_constructor(int samplingFreq) 
    {
        return new mydsp_wrap(samplingFreq);
    }
    
    void mydsp_destructor(mydsp_wrap* n) 
    {
        delete n;
    }

    void mydsp_compute(mydsp_wrap* n, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
    {
        n->compute(count, inputs, outputs);
    }
    
    int mydsp_getNumInputs(mydsp_wrap* n)
    {
        return n->getNumInputs();
    }
    
    int mydsp_getNumOutputs(mydsp_wrap* n)
    {
        return n->getNumOutputs();
    }
    
    void mydsp_getJSON(mydsp_wrap* n, char* json)
    {
        n->getJSON(json);
    }
    
    void mydsp_setValue(mydsp_wrap* n, const char* path, float value)
    {
        n->setValue(path, value);
    }
    
    float mydsp_getValue(mydsp_wrap* n, const char* path)
    {
        return n->getValue(path);
    }
    
}