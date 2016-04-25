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

#ifndef __poly_dsp__
#define __poly_dsp__

#include <stdio.h>
#include <string>
#include <math.h>
#include <float.h>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>
#include <limits.h>

#include "faust/gui/MidiUI.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"
#include "faust/dsp/proxy-dsp.h"

#define kFreeVoice        -1
#define kReleaseVoice     -2
#define kNoVoice          -3

#define VOICE_STOP_LEVEL  0.001
#define MIX_BUFFER_SIZE   16384

#define FLOAT_MAX(a, b) (((a) < (b)) ? (b) : (a))

// ends_with(<str>,<end>) : returns true if <str> ends with <end>
static bool ends_with(std::string const& str, std::string const& end)
{
	unsigned int l1 = str.length();
	unsigned int l2 = end.length();
    return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
}

class GroupUI : public GUI, public PathBuilder
{
    
    private:
    
        std::map<std::string, uiGroupItem*> fLabelZoneMap;
        
        void insertMap(std::string label, FAUSTFLOAT* zone)
        {   
            if (!ends_with(label, "/gate") 
                && !ends_with(label, "/freq") 
                && !ends_with(label, "/gain")) {
                
                // Groups all controller except 'freq', 'gate', and 'gain'
                if (fLabelZoneMap.find(label) != fLabelZoneMap.end()) {
                    fLabelZoneMap[label]->addZone(zone);
                } else {
                    fLabelZoneMap[label] = new uiGroupItem(this, zone);
                }
            }
        }
        
        uiCallbackItem* fPanic;
           
    public:
        
        GroupUI(FAUSTFLOAT* zone, uiCallback cb, void* arg)
        {
            fPanic = new uiCallbackItem(this, zone, cb, arg);
        };
        virtual ~GroupUI() 
        {
            // 'fPanic' is kept and deleted in GUI, so do not delete here
        };
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
            
};

// One voice of polyphony
struct dsp_voice : public MapUI, public dsp {
       
    int fNote;          // Playing note actual pitch
    int fDate;          // KeyOn date
    bool fTrigger;      // True if stolen note and need for envelop re-trigger
    FAUSTFLOAT fLevel;  // Last audio block level

    dsp_voice()
    {
        fNote = kFreeVoice;
        fLevel = FAUSTFLOAT(0);
        fDate = 0;
        fTrigger = false;
    }
    
    virtual void metadata(Meta* meta) = 0;
 
};

struct voice_factory {

    virtual dsp_voice* create() = 0;
};

struct mydsp_voice : public dsp_voice {

    mydsp fVoice;
     
    mydsp_voice():dsp_voice()
    {
        fVoice.buildUserInterface(this);
    }
    
    virtual int getNumInputs() { return fVoice.getNumInputs(); }
    virtual int getNumOutputs() { return fVoice.getNumOutputs(); }
    virtual void buildUserInterface(UI* ui_interface) { fVoice.buildUserInterface(ui_interface); }
    virtual void init(int samplingRate) { fVoice.init(samplingRate); }
    virtual void instanceInit(int samplingRate) { fVoice.instanceInit(samplingRate); }
    virtual void compute(int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fVoice.compute(len, inputs, outputs); }

    virtual void metadata(Meta* meta) { mydsp::metadata(meta); }

};

struct mydsp_voice_factory : public voice_factory {

    virtual dsp_voice* create() { return new mydsp_voice(); }
};

// Polyphonic DSP
class mydsp_poly : public dsp, public midi {

    private:
  
        std::string fJSON;
        
        std::vector<dsp_voice*> fVoiceTable; // Individual voices
        dsp* fVoiceGroup;                    // Voices group to be used for GUI grouped control
        
        std::string fGateLabel;
        std::string fGainLabel;
        std::string fFreqLabel;
        FAUSTFLOAT fPanic;
        
        int fPolyphony;
        bool fVoiceControl;
        bool fGroupControl;
        
        GroupUI fGroups;
        
        FAUSTFLOAT** fMixBuffer;
        int fNumOutputs;
        int fDate;
        
        std::vector<MidiUI*> fMidiUIList;
        
        inline FAUSTFLOAT mixVoice(int count, FAUSTFLOAT** outputBuffer, FAUSTFLOAT** mixBuffer) 
        {
            FAUSTFLOAT level = 0;
            // Normalize sample by the max polyphony (as in vst.cpp file)
            FAUSTFLOAT gain_level = 1./sqrt(fPolyphony);
            for (int i = 0; i < fNumOutputs; i++) {
                FAUSTFLOAT* mixChannel = mixBuffer[i];
                FAUSTFLOAT* outChannel = outputBuffer[i];
                for (int j = 0; j < count; j++) {
                    level = FLOAT_MAX(level, (FAUSTFLOAT)fabs(outChannel[j]));
                    mixChannel[j] += outChannel[j] * gain_level;
                }
            }
            return level;
        }
        
        inline double midiToFreq(double note) 
        {
            return 440.0 * pow(2.0, (note-69.0)/12.0);
        }
        
        inline void clearOutput(int count, FAUSTFLOAT** mixBuffer) 
        {
            for (int i = 0; i < fNumOutputs; i++) {
                memset(mixBuffer[i], 0, count * sizeof(FAUSTFLOAT));
            }
        }
          
        inline int getVoice(int note, bool steal = false)
        {
            for (int i = 0; i < fPolyphony; i++) {
                if (fVoiceTable[i]->fNote == note) {
                    if (steal) { fVoiceTable[i]->fDate = fDate++; }
                    return i;
                }
            }
             
            if (steal) {
                int voice = kNoVoice;
                int date = INT_MAX;
                for (int i = 0; i < fPolyphony; i++) {
                    // Try to steal a voice in kReleaseVoice mode...
                    if (fVoiceTable[i]->fNote == kReleaseVoice) {
                        printf("Steal release voice : voice_date = %d cur_date = %d voice = %d\n", fVoiceTable[i]->fDate, fDate, i);
                        fVoiceTable[i]->fDate = fDate++;
                        fVoiceTable[i]->fTrigger = true;
                        return i;
                    // Otherwise steal oldest voice...
                    } else if (fVoiceTable[i]->fDate < date) {
                        date = fVoiceTable[i]->fDate;
                        voice = i;
                    }
                }
                printf("Steal playing voice : voice_date = %d cur_date = %d voice = %d\n", fVoiceTable[voice]->fDate, fDate, voice);
                fVoiceTable[voice]->fDate = fDate++;
                fVoiceTable[voice]->fTrigger = true;
                return voice;
            } else {
                return kNoVoice;
            }
        }
        
        inline void init(int max_polyphony, voice_factory* factory, bool control, bool group)
        {
            fVoiceControl = control;
            fGroupControl = group;
            fPolyphony = max_polyphony;
            fFreqLabel = fGateLabel = fGainLabel = "";
            
            // Create voices
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable.push_back(factory->create());
            }
            
            // Init audio output buffers
            fNumOutputs = fVoiceTable[0]->getNumOutputs();
            fMixBuffer = new FAUSTFLOAT*[fNumOutputs];
            for (int i = 0; i < fNumOutputs; i++) {
                fMixBuffer[i] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
            }
            
            // Groups all uiItem for a given path
            fVoiceGroup = new proxy_dsp(fVoiceTable[0], mydsp::metadata);
            fVoiceGroup->buildUserInterface(&fGroups);
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable[i]->buildUserInterface(&fGroups);
            }
            
            // Creates global JSON
            JSONUI builder(fVoiceTable[0]->getNumInputs(), fVoiceTable[0]->getNumOutputs());
            fVoiceTable[0]->metadata(&builder);
            uIBuilder(&builder);
            fJSON = builder.JSON();
            fDate = 0;
            
            // Keep gain, freq and gate labels
            std::map<std::string, FAUSTFLOAT*>::iterator it;
            for (it = fVoiceTable[0]->getMap().begin(); it != fVoiceTable[0]->getMap().end(); it++) {
                std::string label = (*it).first;
                if (ends_with(label, "/gate")) {
                    fGateLabel = label;
                } else if (ends_with(label, "/freq")) {
                    fFreqLabel = label;
                } else if (ends_with(label, "/gain")) {
                    fGainLabel = label;
                }
            }
        }
        
        void uIBuilder(UI* ui_interface)
        {
            ui_interface->openTabBox("Polyphonic");
            
            // Grouped voices UI
            ui_interface->openVerticalBox("All Voices");
            ui_interface->addButton("Panic", &fPanic);
            fVoiceGroup->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            
            // In not group, also add individual voices UI
            if (!fGroupControl) {
                for (int i = 0; i < fPolyphony; i++) {
                    char buffer[32];
                    snprintf(buffer, 31, ((fPolyphony < 8) ? "Voice%d" : "V%d"), i+1);
                    ui_interface->openHorizontalBox(buffer);
                    fVoiceTable[i]->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                }
            }
            
            ui_interface->closeBox();
        }
        
        static void Panic(FAUSTFLOAT val, void* arg)
        {
            if (val == FAUSTFLOAT(1)) {
                static_cast<mydsp_poly*>(arg)->allNotesOff();
            }
        }
        
        inline bool checkPolyphony() 
        {
            if (fFreqLabel == "") {
                printf("DSP is not polyphonic...\n");
                return false;
            } else {
                return true;;
            }
        }
        
        inline void computeSlice(dsp* dsp, int offset, int slice, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
        {
            if (slice > 0) {
                FAUSTFLOAT** inputs_slice = (FAUSTFLOAT**)alloca(dsp->getNumInputs() * sizeof(FAUSTFLOAT*));
                for (int chan = 0; chan < dsp->getNumInputs(); chan++) {
                    inputs_slice[chan] = &(inputs[chan][offset]);
                }
                
                FAUSTFLOAT** outputs_slice = (FAUSTFLOAT**)alloca(dsp->getNumOutputs() * sizeof(FAUSTFLOAT*));
                for (int chan = 0; chan < dsp->getNumOutputs(); chan++) {
                    outputs_slice[chan] = &(outputs[chan][offset]);
                }
                
                dsp->compute(slice, inputs_slice, outputs_slice);
            } 
        }
        
        inline unsigned int isPowerOfTwo(unsigned int n)
        {
            return !(n & (n - 1));
        }
    
    public: 
    
        mydsp_poly(int max_polyphony, 
                bool control = false,   
                bool group = true):fGroups(&fPanic, Panic, this)
        {
            mydsp_voice_factory factory;
            init(max_polyphony, &factory, control, group);
        }
           
        virtual ~mydsp_poly()
        {
            for (int i = 0; i < fNumOutputs; i++) {
                delete[] fMixBuffer[i];
            }
            delete[] fMixBuffer;
            
            for (int i = 0; i < fPolyphony; i++) {
                delete fVoiceTable[i];
            }
            
            delete fVoiceGroup;
            
            // Remove object from all MidiUI interfaces that handle it
            for (int i = 0; i < fMidiUIList.size(); i++) {
                fMidiUIList[i]->removeMidiIn(this); 
            }
        }
        
        void init(int sample_rate)
        {
            // Init voices
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable[i]->init(sample_rate);
            }
        }
    
        void instanceInit(int sample_rate)
        {
            // Init voices
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable[i]->instanceInit(sample_rate);
            }
        }
    
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count < MIX_BUFFER_SIZE);
            
            // First clear the outputs
            clearOutput(count, outputs);
            
            if (fVoiceControl) {
                // Mix all playing voices
                for (int i = 0; i < fPolyphony; i++) {
                    if (fVoiceTable[i]->fNote != kFreeVoice) {
                        if (fVoiceTable[i]->fTrigger) {
                            //If stolen note and need for envelop re-trigger
                            int slice = isPowerOfTwo(count) ? count/2 : 1;
                            fVoiceTable[i]->setParamValue(fGateLabel, 0.0f);
                            computeSlice(fVoiceTable[i], 0, slice, inputs, fMixBuffer);
                            fVoiceTable[i]->setParamValue(fGateLabel, 1.0f);
                            computeSlice(fVoiceTable[i], slice, count - slice, inputs, fMixBuffer);
                            fVoiceTable[i]->fTrigger = false;
                        } else {
                            // Compute regular voice
                            fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                        }
                        // Mix it in result
                        fVoiceTable[i]->fLevel = mixVoice(count, fMixBuffer, outputs);
                        // Check the level to possibly set the voice in kFreeVoice again
                        if ((fVoiceTable[i]->fLevel < VOICE_STOP_LEVEL) && (fVoiceTable[i]->fNote == kReleaseVoice)) {
                            fVoiceTable[i]->fNote = kFreeVoice;
                        }
                    }
                }
            } else {
                // Mix all voices
                for (int i = 0; i < fPolyphony; i++) {
                    fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                    mixVoice(count, fMixBuffer, outputs);
                }
            }
        }
        
        int getNumInputs()
        {
            return fVoiceTable[0]->getNumInputs();
        }
        
        int getNumOutputs()
        {
            return fVoiceTable[0]->getNumOutputs();
        }
        
        void buildUserInterface(UI* ui_interface) 
        {   
            // Add itself to the MidiUI object
            MidiUI* midi_ui = dynamic_cast<MidiUI*>(ui_interface);
            if (midi_ui) { 
                fMidiUIList.push_back(midi_ui);
                midi_ui->addMidiIn(this); 
            }
            
            if (fPolyphony > 1) {
                uIBuilder(ui_interface);
            } else {
                fVoiceTable[0]->buildUserInterface(ui_interface);
            }
        }
        
        // Pure MIDI control
        
        void keyOn(int channel, int pitch, int velocity)
        {
            if (checkPolyphony()) {
                int voice = getVoice(kFreeVoice, true);
                if (voice >= 0) {
                    fVoiceTable[voice]->setParamValue(fFreqLabel, midiToFreq(pitch));
                    fVoiceTable[voice]->setParamValue(fGainLabel, float(velocity)/127.f);
                    fVoiceTable[voice]->setParamValue(fGateLabel, 1.0f);
                    fVoiceTable[voice]->fNote = pitch;
                } else {
                    printf("No more free voice...\n");
                }
            }
        }
        
        void keyOff(int channel, int pitch, int velocity = 127)
        {
            if (checkPolyphony()) {
                int voice = getVoice(pitch);
                if (voice >= 0) {
                    // No use of velocity for now...
                    fVoiceTable[voice]->setParamValue(fGateLabel, 0.0f);
                    fVoiceTable[voice]->fNote = kReleaseVoice;
                } else {
                    printf("Playing pitch = %d not found\n", pitch);
                }
            }
        }
        
        void pitchWheel(int channel, int wheel)
        {}
         
        void ctrlChange(int channel, int ctrl, int value)
        {
            if (ctrl == ALL_NOTES_OFF || ctrl == ALL_SOUND_OFF) {
                allNotesOff();
            }
        }
        
        void progChange(int channel, int pgm)
        {}
        
        void keyPress(int channel, int pitch, int press)
        {}
        
        void chanPress(int channel, int press)
        {}
         
        void ctrlChange14bits(int channel, int ctrl, int value)
        {}
 
        // Additional API
        void pitchBend(int channel, int pitch, float tuned_pitch)
        {
            if (checkPolyphony()) {
                int voice = getVoice(pitch);
                if (voice >= 0) {
                    fVoiceTable[voice]->setParamValue(fFreqLabel, midiToFreq(tuned_pitch));
                } else {
                    printf("Playing voice not found...\n");
                }
            }
        }
        
        void allNotesOff()
        {
            if (checkPolyphony()) {
                for (int i = 0; i < fPolyphony; i++) {
                    fVoiceTable[i]->setParamValue(fGateLabel, 0.0f);
                    fVoiceTable[i]->fNote = kReleaseVoice;
                    fVoiceTable[i]->fTrigger = false;
                }
            }
        }
       
        void setParamValue(const char* path, float value)
        {
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable[i]->setParamValue(path, value);
            }
        }
        
        void setParamValue(const char* path, int pitch, float value)
        {
            int voice = getVoice(pitch);
            if (voice >= 0) {
                fVoiceTable[voice]->setParamValue(path, value);
            }
        }
        
        float getParamValue(const char* path)
        {
            return fVoiceTable[0]->getParamValue(path);
        }
        
        void setVoiceGain(int pitch, float value)
        {   
            int voice = getVoice(pitch);
            if (voice >= 0) {
                fVoiceTable[voice]->setParamValue(fGainLabel, value);
            }
        }
        
        const char* getJSON()
        {
            return fJSON.c_str();
        }
    
};
   
#endif // __poly_dsp__
