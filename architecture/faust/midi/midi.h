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

#ifndef __midi__
#define __midi__

//----------------------------------------------------------------
//  MIDI processor definition
//----------------------------------------------------------------

// To implement by classes that can receive MIDI messages

class midiIn {
 
    public:

        midiIn() {}
        virtual ~midiIn() {}

        virtual void keyOn(int channel, int note, int velocity)         = 0;
        virtual void keyOff(int channel, int note, int velocity)        = 0;
        virtual void pitchWheel(int channel, int wheel)                 = 0;
        virtual void ctrlChange(int channel, int ctrl, int value)       = 0;
        virtual void progChange(int channel, int pgm)                   = 0;
        
        virtual void pitchBend(int channel, int refPitch, float pitch)  = 0;
        virtual void allNotesOff()                                      = 0;
     
};

// To implement by classes that can send MIDI messages

class midiOut {
 
    public:

        midiOut() {}
        virtual ~midiOut() {}

        virtual void keyOn(int channel, int note, int velocity)         = 0;
        virtual void keyOff(int channel, int note, int velocity)        = 0;
        virtual void pitchWheel(int channel, int wheel)                 = 0;
        virtual void ctrlChange(int channel, int ctrl, int value)       = 0;
        virtual void progChange(int channel, int pgm)                   = 0;
};


#endif
