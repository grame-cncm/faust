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

#ifndef FAUST_MIDIUI_H
#define FAUST_MIDIUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/GUI.h"
#include "faust/midi/rt-midi.h"
#include "faust/gui/ValueConverter.h"
#include <vector>
#include <string>

/*******************************************************************************
 * MidiUI : Faust User Interface
 * This class decode MIDI meta data and maps incoming MIDI messages to them.
 ******************************************************************************/

class uiMidiProgChange : public uiItem
{
    private:
        
        midi* fMidiOut;
        int fPgm;
  
    public:
    
        uiMidiProgChange(midi* midi_out, int pgm, GUI* ui, FAUSTFLOAT* zone)
            :uiItem(ui, zone), fMidiOut(midi_out), fPgm(pgm)
        {}
        virtual ~uiMidiProgChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != 0.) {
                fMidiOut->progChange(0, fPgm);
            }
        }
        
};

class uiMidiChanPress : public uiItem
{
    private:
        
        midi* fMidiOut;
        int fPress;
  
    public:
    
        uiMidiChanPress(midi* midi_out, int press, GUI* ui, FAUSTFLOAT* zone)
            :uiItem(ui, zone), fMidiOut(midi_out), fPress(press)
        {}
        virtual ~uiMidiChanPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != 0.) {
                fMidiOut->chanPress(0, fPress);
            }
        }
        
};

class uiMidiCtrlChange : public uiItem
{
    private:
    
        midi* fMidiOut;
        int fCtrl;
        LinearValueConverter fConverter;
 
    public:
    
        uiMidiCtrlChange(midi* midi_out, int ctrl, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            :uiItem(ui, zone), fMidiOut(midi_out), fCtrl(ctrl), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiCtrlChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->ctrlChange(0, fCtrl, fConverter.faust2ui(v));
        }
        
        void modifyZone(int v) 	
        { 
            uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
        }
 
};

class uiMidiPitchWheel : public uiItem
{
    private:
    
        midi* fMidiOut;
        LinearValueConverter fConverter;
 
    public:
    
        uiMidiPitchWheel(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            :uiItem(ui, zone), fMidiOut(midi_out), fConverter(0., 16383, double(min), double(max))
        {}
        virtual ~uiMidiPitchWheel()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->pitchWheel(0, fConverter.faust2ui(v));
        }
        
        void modifyZone(int v) 	
        { 
            uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
        }
 
};

class uiMidiKeyOn : public uiItem
{
    private:
        
        midi* fMidiOut;
        int fKeyOn;
        LinearValueConverter fConverter;
  
    public:
    
        uiMidiKeyOn(midi* midi_out, int key, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            :uiItem(ui, zone), fMidiOut(midi_out), fKeyOn(key), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiKeyOn()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyOn(0, fKeyOn, fConverter.faust2ui(v));
        }
        
        void modifyZone(int v) 	
        { 
            uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
        }
        
};

class uiMidiKeyPress : public uiItem
{
    private:
        
        midi* fMidiOut;
        int fKeyOn;
        LinearValueConverter fConverter;
  
    public:
    
        uiMidiKeyPress(midi* midi_out, int key, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            :uiItem(ui, zone), fMidiOut(midi_out), fKeyOn(key), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiKeyPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyPress(0, fKeyOn, fConverter.faust2ui(v));
        }
        
        void modifyZone(int v) 	
        { 
            uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
        }
        
};

class MidiUI : public GUI, public midi
{

    protected:
    
        std::map <int, std::vector<uiMidiCtrlChange*> > fCtrlChangeTable;
        std::map <int, std::vector<uiMidiProgChange*> > fProgChangeTable;
        std::map <int, std::vector<uiMidiChanPress*> >  fChanPressTable;
        std::map <int, std::vector<uiMidiKeyOn*> >      fKeyOnTable;
        std::map <int, std::vector<uiMidiKeyPress*> >   fKeyPressTable;
        std::vector<uiMidiPitchWheel*>                  fPitchWheelTable;
        
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        
        rtmidi fMIDI;
        midi* fMidiOut;
        
        void addGenericZone(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            if (fMetaAux.size() > 0) {
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    unsigned num;
                    if (fMetaAux[i].first == "midi") {
                        if (sscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiOut, num, this, zone, min, max));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiOut, num, this, zone, min, max));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "keypress %u", &num) == 1) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiOut, num, this, zone, min, max));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "pgm %u", &num) == 1) {
                            fProgChangeTable[num].push_back(new uiMidiProgChange(fMidiOut, num, this, zone));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "chanpress %u", &num) == 1) {
                            fChanPressTable[num].push_back(new uiMidiChanPress(fMidiOut, num, this, zone));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "pitchwheel") == 1) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiOut, this, zone, min, max));
                        }
                    }
                }
            }
            fMetaAux.clear();
        }

    public:

        MidiUI(const std::string& name = "RTMidi"):fMIDI(name), fMidiOut(&fMIDI) { fMIDI.addMidiIn(this); }

        virtual ~MidiUI() {}
        
        void run() { fMIDI.start(); }
        void stop() { fMIDI.stop(); }
        
        void addMidiIn(midi* midi_dsp) { fMIDI.addMidiIn(midi_dsp); }
      
        // -- widget's layouts

        virtual void openTabBox(const char* label)
        {}
        virtual void openHorizontalBox(const char* label)
        {}
        virtual void openVerticalBox(const char* label)
        {}
        virtual void closeBox()
        {}

        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0.0), FAUSTFLOAT(1.0));
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0.0), FAUSTFLOAT(1.0));
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericZone(zone, min, max);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericZone(zone, min, max);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
        
        // -- MIDI API 
        
        void keyOn(int channel, int note, int velocity) 
        {
            if (fKeyOnTable.find(note) != fKeyOnTable.end()) {
                for (int i = 0; i < fKeyOnTable[note].size(); i++) {
                    fKeyOnTable[note][i]->modifyZone(velocity);
                }
            }
        }
        
        void keyOff(int channel, int note, int velocity) {}
           
        void ctrlChange(int channel, int ctrl, int value)
        {
            if (fCtrlChangeTable.find(ctrl) != fCtrlChangeTable.end()) {
                for (int i = 0; i < fCtrlChangeTable[ctrl].size(); i++) {
                    fCtrlChangeTable[ctrl][i]->modifyZone(value);
                }
            } 
        }
        
        void progChange(int channel, int pgm)
        {
            if (fProgChangeTable.find(pgm) != fProgChangeTable.end()) {
                for (int i = 0; i < fProgChangeTable[pgm].size(); i++) {
                    fProgChangeTable[pgm][i]->modifyZone(1.f);
                }
            } 
        }
        
        void pitchWheel(int channel, int wheel) 
        {
            for (int i = 0; i < fPitchWheelTable.size(); i++) {
                fPitchWheelTable[i]->modifyZone(wheel);
            }
        }
        
        void keyPress(int channel, int pitch, int press) 
        {
            if (fKeyPressTable.find(press) != fKeyPressTable.end()) {
                for (int i = 0; i < fKeyPressTable[press].size(); i++) {
                    fKeyPressTable[press][i]->modifyZone(press);
                }
            } 
        }
        
        void chanPress(int channel, int press)
        {
            if (fChanPressTable.find(press) != fChanPressTable.end()) {
                for (int i = 0; i < fChanPressTable[press].size(); i++) {
                    fChanPressTable[press][i]->modifyZone(1.f);
                }
            } 
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value) {}
};

#endif // FAUST_MIDIUI_H
