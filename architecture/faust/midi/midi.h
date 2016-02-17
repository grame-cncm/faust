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

#ifndef __midi__
#define __midi__

#include <vector>
#include <string>
#include <algorithm>

#include "faust/gui/ring-buffer.h"

//----------------------------------------------------------------
//  MIDI processor definition
//----------------------------------------------------------------

class midi {
 
    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual void keyOn(double date, int channel, int pitch, int velocity)          {}
        virtual void keyOff(double date, int channel, int pitch, int velocity)         {}
        virtual void keyPress(double date, int channel, int pitch, int press)          {}
        virtual void chanPress(double date, int channel, int press)                    {}
        virtual void ctrlChange(double date, int channel, int ctrl, int value)         {}
        virtual void ctrlChange14bits(double date, int channel, int ctrl, int value)   {}
        virtual void pitchWheel(double date, int channel, int wheel)                   {}
        virtual void progChange(double date, int channel, int pgm)                     {}
        
        // MIDI sync
        virtual void start(double date)  {}
        virtual void stop(double date)   {}
        virtual void clock(double date)  {}
        
        // Standard MIDI API
        virtual void keyOn(int channel, int pitch, int velocity)        {}
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void pitchWheel(int channel, int wheel)                 {}
        virtual void progChange(int channel, int pgm)                   {}
        
        enum MidiStatus {
	
            // channel voice messages
            MIDI_NOTE_OFF           = 0x80, 
            MIDI_NOTE_ON            = 0x90, 
            MIDI_CONTROL_CHANGE     = 0xB0,
            MIDI_PROGRAM_CHANGE     = 0xC0,
            MIDI_PITCH_BEND         = 0xE0,
            MIDI_AFTERTOUCH         = 0xD0,	// aka channel pressure
            MIDI_POLY_AFTERTOUCH    = 0xA0,	// aka key pressure
            MIDI_CLOCK              = 0xF8,
            MIDI_START              = 0xFA,
            MIDI_STOP               = 0xFC

        };
        
        enum MidiCtrl {
            
            ALL_NOTES_OFF = 123,
            ALL_SOUND_OFF = 120
        
        };
};

//----------------------------------------------------------------
//  Base class for MIDI API handling
//----------------------------------------------------------------

class midi_handler : public midi {

    protected:
    
        std::vector<midi*> fMidiInputs;
        std::string fName;

    public:

        midi_handler(const std::string& name = "MIDIHandler"):fName(name) {}
        virtual ~midi_handler() {}
        
        virtual void addMidiIn(midi* midi_dsp) { fMidiInputs.push_back(midi_dsp); }
        virtual void removeMidiIn(midi* midi_dsp) 
        { 
            std::vector<midi*>::iterator it = std::find(fMidiInputs.begin(), fMidiInputs.end(), midi_dsp);
            if (it != fMidiInputs.end()) {
                fMidiInputs.erase(it); 
            }
        }
        
        virtual bool start() { return false; }
        virtual void stop() {}

};

#endif // __midi__
