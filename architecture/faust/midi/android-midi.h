/************************************************************************
    FAUST Architecture File
	Copyright (C) 2016 GRAME, Romain Michon, CCRMA - Stanford University
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

#ifndef __android_midi__
#define __android_midi__

#include "faust/midi/midi.h"

class android_midi_handler : public midi_handler{
	public:
		android_midi_handler(const std::string& name = "AndroidHandler")
			:midi_handler(name) {}
		virtual ~android_midi_handler() {}
		void propagateMIDI(double time, int type, int channel, int data1, int data2){
			if(data2 != NULL) handleData2(time,type,channel,data1,data2);
			else if(data1 != NULL) handleData1(time,type,channel,data1);
			else handleSync(time,type);
		}
};

#endif
