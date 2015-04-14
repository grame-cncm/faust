#ifndef FAUST_MIDIUI_H
#define FAUST_MIDIUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/GUI.h"
#include "faust/midi/midi.h"
#include "faust/gui/ValueConverter.h"
#include <vector>
#include <string>

/*******************************************************************************
 * MidiUI : Faust User Interface
 * This class decode MIDI meta data and maps incoming MIDI messages to them
 ******************************************************************************/

/*
class uiMidiCtrl : public uiItem
{
    private:
    
        LinearValueConverter fConverter;
 
    public :
    
        uiMidiCtrl(GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            :uiItem(ui, zone), fConverter(0., 127., double(min), double(max))
        {}
        virtul ~uiMidiCtrl()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fSlider->setValue(fConverter->faust2ui(v));
        }
 
};
*/
 
class MidiUI : public GUI, public midi
{

    private:
    
        std::map <int, FAUSTFLOAT*> fKeyOnTable;
        std::map <int, std::pair<FAUSTFLOAT*, LinearValueConverter> > fCtrlChangeTable;
        std::map <int, FAUSTFLOAT*> fProgChangeTable;
        
        std::vector<std::pair <std::string, std::string> > fMetaAux;

    public:

        MidiUI() {}

        virtual ~MidiUI() {}

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
        
        void addGenericZone(FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            if (fMetaAux.size() > 0) {
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    unsigned num;
                    if (fMetaAux[i].first == "midi") {
                        if (sscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num] = std::make_pair(zone, LinearValueConverter(0., 127., double(min), double(max)));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "pgm %u", &num) == 1) {
                            fProgChangeTable[num] = zone;
                        } else if (sscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num] = zone;
                        }
                    }
                }
            }
            fMetaAux.clear();
        }

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, 0, 0, 0, 0);
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, 0, 0, 0, 0);
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, init, min, max, step);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, init, min, max, step);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, init, min, max, step);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericZone(zone, 0, 0, 0, 0);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericZone(zone, 0, 0, 0, 0);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
        
        // -- public API 
        
        void keyOn(int channel, int note, int velocity)
         {
            if (fKeyOnTable.find(note) != fKeyOnTable.end()) {
                *fKeyOnTable[note] = 1.f;
            }
        }
        
        void keyOff(int channel, int note, int velocity)
        {
            if (fKeyOnTable.find(note) != fKeyOnTable.end()) {
                *fKeyOnTable[note] = 0.f;
            } 
        }
        
        void ctrlChange(int channel, int ctrl, int value)
        {
            if (fCtrlChangeTable.find(ctrl) != fCtrlChangeTable.end()) {
               *(fCtrlChangeTable[ctrl].first) = fCtrlChangeTable[ctrl].second.ui2faust(value);
            } 
        }
        
        void progChange(int channel, int pgm)
        {
            if (fProgChangeTable.find(pgm) != fProgChangeTable.end()) {
                *fProgChangeTable[pgm] = 1.f;
            } 
        }
        
        void allNotesOff() {}
        void pitchWheel(int channel, int wheel) {}
        void pitchBend(int channel, int refPitch, float pitch) {}
    
};

#endif
