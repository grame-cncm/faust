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

class uiMidiKey : public uiItem
{
    private:
    
        midiOut* fMidiOut;
  
    public:
    
        uiMidiKey(midiOut* midi_out, GUI* ui, FAUSTFLOAT* zone)
            :uiItem(ui, zone), fMidiOut(midi_out)
        {}
        virtual ~uiMidiKey()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            //printf("uiMidiKey: reflectZone %f\n", v, fCache);
        }
        
        void modifyZone(FAUSTFLOAT v) 	
        { 
            //printf("uiMidiKey: modifyZone %f\n", v);
            uiItem::modifyZone(v);
        }
        
};

class uiMidiPgm : public uiItem
{
    private:
        
        midiOut* fMidiOut;
        int fPgm;
  
    public:
    
        uiMidiPgm(midiOut* midi_out, int pgm, GUI* ui, FAUSTFLOAT* zone)
            :uiItem(ui, zone), fMidiOut(midi_out), fPgm(pgm)
        {}
        virtual ~uiMidiPgm()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            //printf("uiMidiPgm: reflectZone %f\n", v, fCache);
            if (v != 0.) {
                fMidiOut->progChange(0, fPgm);
            }
        }
        
};

class uiMidiCtrl : public uiItem
{
    private:
    
        midiOut* fMidiOut;
        int fCtrl;
        LinearValueConverter fConverter;
 
    public:
    
        uiMidiCtrl(midiOut* midi_out, int ctrl, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            :uiItem(ui, zone), fMidiOut(midi_out), fCtrl(ctrl), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiCtrl()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            //printf("uiMidiCtrl: reflectZone %f\n", v, fCache);
            fMidiOut->ctrlChange(0, fCtrl, fConverter.faust2ui(v));
        }
        
        void modifyZone(int v) 	
        { 
            //printf("uiMidiCtrl: modifyZone %d %f\n", v, fConverter.ui2faust(v));
            uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
        }
 
};

class MidiUI : public GUI, public midiIn
{

    private:
    
        std::map <int, vector<uiMidiKey*> > fKeyOnTable;
        std::map <int, vector<uiMidiCtrl*> > fCtrlChangeTable;
        std::map <int, vector<uiMidiPgm*> > fProgChangeTable;
        
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        
        midiOut* fMidiOut;
        
        inline double midiToFreq(double note) 
        {
            return 440.0 * pow(2.0, (note-69.0)/12.0);
        }

    public:

        MidiUI():fMidiOut(0) {}

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
        
        void addGenericZone(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            if (fMetaAux.size() > 0) {
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    unsigned num;
                    if (fMetaAux[i].first == "midi") {
                        if (sscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrl(fMidiOut, num, this, zone, min, max));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "pgm %u", &num) == 1) {
                            fProgChangeTable[num].push_back(new uiMidiPgm(fMidiOut, num, this, zone));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num].push_back(new uiMidiKey(fMidiOut, this, zone));
                        }
                    }
                }
            }
            fMetaAux.clear();
        }

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, 0, 0);
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, 0, 0);
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
            addGenericZone(zone, 0, 0);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericZone(zone, 0, 0);
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
                for (int i = 0; i < fKeyOnTable[note].size(); i++) {
                    fKeyOnTable[note][i]->modifyZone(1.f);
                    /*
                    fFreqLabel->modifyZone(midiToFreq(note));
                    fGainLabel->modifyZone(float(velocity)/127.f);
                    fGateLabel->modifyZone(1.f);
                    */
                }
            }
        }
        
        void keyOff(int channel, int note, int velocity)
        {
            if (fKeyOnTable.find(note) != fKeyOnTable.end()) {
                for (int i = 0; i < fKeyOnTable[note].size(); i++) {
                    fKeyOnTable[note][i]->modifyZone(0.f);
                    /*
                    fGainLabel->modifyZone(float(velocity)/127.f);
                    fGateLabel->modifyZone(0.f);
                    */
                }
            } 
        }
        
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
        
        void allNotesOff() {}
        void pitchWheel(int channel, int wheel) {}
        void pitchBend(int channel, int refPitch, float pitch) {}
        
        void setMidiOut(midiOut* midi_out) { fMidiOut = midi_out; }
    
};

#endif
