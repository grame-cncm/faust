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
       
};

#endif // __midi__
