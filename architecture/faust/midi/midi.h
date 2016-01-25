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

        // Additional time-stamped API
        virtual void keyOn(int date, int channel, int pitch, int velocity)          { keyOn(-1, channel, pitch, velocity); }
        virtual void keyOff(int date, int channel, int pitch, int velocity)         { keyOff(-1, channel, pitch, velocity); }
        virtual void keyPress(int date, int channel, int pitch, int press)          { keyPress(-1, channel, pitch, press); }
        virtual void chanPress(int date, int channel, int press)                    { chanPress(-1, channel,press); }
        virtual void ctrlChange(int date, int channel, int ctrl, int value)         { ctrlChange(-1, channel, ctrl, value); }
        virtual void ctrlChange14bits(int date, int channel, int ctrl, int value)   { ctrlChange14bits(-1, channel, ctrl, value); }
        virtual void pitchWheel(int date, int channel, int wheel)                   { pitchWheel(-1, channel, wheel); }
        virtual void progChange(int date, int channel, int pgm)                     { progChange(-1, channel, pgm); }
        
        virtual void keyOn(int channel, int pitch, int velocity)        = 0;
        virtual void keyOff(int channel, int pitch, int velocity)       = 0;
        virtual void keyPress(int channel, int pitch, int press)        = 0;
        virtual void chanPress(int channel, int press)                  = 0;
        virtual void ctrlChange(int channel, int ctrl, int value)       = 0;
        virtual void ctrlChange14bits(int channel, int ctrl, int value) = 0;
        virtual void pitchWheel(int channel, int wheel)                 = 0;
        virtual void progChange(int channel, int pgm)                   = 0;
       
};

#endif // __midi__
