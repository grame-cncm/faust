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
 
 ************************************************************************
 ************************************************************************/

#include "JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "faust/dsp/timed-dsp.h"
#include "faust/gui/MapUI.h"
#include "faust/misc.h"

#include "faust/gui/APIUI.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/JuceGUI.h"
#include "faust/gui/MidiUI.h"

#include <math.h>
#include <algorithm>

using std::max;
using std::min;

#if defined(OSCCTRL)
#include "faust/gui/JuceOSCUI.h"
#endif //OSCCTRL

#if defined(MIDICTRL)
#include "faust/midi/juce-midi.h"
#endif //MIDICTRL

#include "faust/dsp/poly-dsp.h"

#if defined(POLY2)
#include "faust/dsp/dsp-combiner.h"
#include "dsp_effect.cpp"
#endif //POLY POLY2

<<includeIntrinsic>>

<<includeclass>>

struct MyMeta : public Meta, public std::map<std::string, std::string>
{
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
    const std::string get(const char* key, const char* def)
    {
        if (this->find(key) != this->end()) {
            return (*this)[key];
        } else {
            return def;
        }
    }
};

static void analyseMeta(bool& midi_sync, int& nvoices)
{
    mydsp* tmp_dsp = new mydsp();
    
    JSONUI jsonui;
    tmp_dsp->buildUserInterface(&jsonui);
    std::string json = jsonui.JSON();
    midi_sync = ((json.find("midi") != std::string::npos) &&
                 ((json.find("start") != std::string::npos) ||
                  (json.find("stop") != std::string::npos) ||
                  (json.find("clock") != std::string::npos)));
    
#if defined(NVOICES) && NVOICES!=NUM_VOICES
    nvoices = NVOICES;
#else
    MyMeta meta;
    tmp_dsp->metadata(&meta);
    std::string numVoices = meta.get("nvoices", "0");
    nvoices = atoi(numVoices.c_str());
    if (nvoices < 0) nvoices = 0;
#endif
    
    delete tmp_dsp;
}

class FaustPlugInAudioProcessorEditor : public AudioProcessorEditor
{
    public:
    
        FaustPlugInAudioProcessorEditor (FaustPlugInAudioProcessor&);
        ~FaustPlugInAudioProcessorEditor();
        
        void paint (Graphics&) override;
        void resized() override;
        
    private:
    
        // This reference is provided as a quick way for your editor to
        // access the processor object that created it.
        FaustPlugInAudioProcessor& processor;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessorEditor)
       
        JuceGUI juceGUI;
  
};

