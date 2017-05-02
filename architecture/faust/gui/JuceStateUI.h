/************************************************************************
    FAUST Architecture File
    Copyright (C) 2017 GRAME, Centre National de Creation Musicale
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

#ifndef JuceStateUI_H
#define JuceStateUI_H

#include <vector>

#include "../JuceLibraryCode/JuceHeader.h"

#include "faust/gui/UI.h"

// A class to save/restore DSP state using JUCE

class JuceStateUI : public UI {

    private:

        std::vector<FAUSTFLOAT*> fZones;

    public:

        void getStateInformation (MemoryBlock& destData)
        {
            MemoryOutputStream stream (destData, true);

            if (sizeof(FAUSTFLOAT) == sizeof(float)) {
                for (int i = 0; i < fZones.size(); i++) {
                    stream.writeFloat(*fZones[i]);
                }
            } else {
                for (int i = 0; i < fZones.size(); i++) {
                    stream.writeDouble(*fZones[i]);
                }
            }
        }

        void setStateInformation (const void* data, int sizeInBytes)
        {
            MemoryInputStream stream (data, static_cast<size_t> (sizeInBytes), false);

            if (sizeof(FAUSTFLOAT) == sizeof(float)) {
                for (int i = 0; i < sizeInBytes / sizeof(float); i++) {
                    *fZones[i] = stream.readFloat();
                }
            } else {
                for (int i = 0; i < sizeInBytes / sizeof(double); i++) {
                    *fZones[i] = stream.readDouble();
                }
            }
        }

        // -- widget's layouts

        virtual void openTabBox(const char* label) {};
        virtual void openHorizontalBox(const char* label) {}
        virtual void openVerticalBox(const char* label) {}
        virtual void closeBox() {}

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) { fZones.push_back(zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) { fZones.push_back(zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) { fZones.push_back(zone); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) { fZones.push_back(zone); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) { fZones.push_back(zone); };
        
        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}


};

#endif
