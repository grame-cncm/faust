#ifndef FAUST_MIDIUI_H
#define FAUST_MIDIUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/UI.h"
#include "faust/midi/midi.h"
#include "faust/gui/ValueConverter.h"
#include <vector>
#include <string>

/*******************************************************************************
 * MidiUI : Faust User Interface
 * This class decode MIDI meta data and maps incoming MIDI messages to them
 ******************************************************************************/

class MidiUI : public UI, public midi
{

    map <int, FAUSTFLOAT*> fKeyOnTable;
    map <int, map <int, FAUSTFLOAT*> > fCtrlChangeTable;
    map <int, map <int, FAUSTFLOAT*> > fProgChangeTable;

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

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
        }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
        }
        
        // -- public API 
        
        void keyOn(int channel, int note, int velocity)
         {
            if (fKeyOnTable.find(ctrl) != fKeyOnTable.end()) {
                *fKeyOnTable[note] = 1.f;
            }
        }
        
        void keyOff(int channel, int note, int velocity)
        {
            if (fKeyOnTable.find(ctrl) != fKeyOnTable.end()) {
                *fKeyOnTable[note] = 0.f;
            } 
        }
        
        void ctrlChange(int channel, int ctrl, int value)
        {
            if (fCtrlChangeTable.find(channel) != fCtrlChangeTable.end()) {
                if ((*fCtrlChangeTable[channel]).find(ctrl) != (*fCtrlChangeTable[channel]).end()) {
                    (*fCtrlChangeTable[channel])[ctrl] = value;
                }
            } 
        }
        
        void progChange(int channel, int pgm)
        {
            if (fProgChangeTable.find(channel) != fProgChangeTable.end()) {
                if ((*fProgChangeTable[channel]).find(ctrl) != (*fProgChangeTable[channel]).end()) {
                    (*fProgChangeTable[channel])[prog] = 1.f;
                }
            } 
        }
        
        void allNotesOff() {}
        void void pitchWheel(int channel, int wheel) {}
        void void pitchBend(int channel, int refPitch, float pitch) {}
    
};

#endif
