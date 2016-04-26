/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
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

#include "faust/misc.h"
#include "faust/gui/UI.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/jsonfaustui.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"

//**************************************************************
// Intrinsic
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>
	
//**************************************************************
// Polyphony
//**************************************************************

#include "faust/dsp/faust-poly-engine.h"

//**************************************************************
// IOS Coreaudio
//**************************************************************

#include "faust/audio/coreaudio-ios-dsp.h"

//**************************************************************
// Interface
//**************************************************************

#include <stdio.h>
#include <string.h>

using namespace std;

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

class IOSEngine : public FaustPolyEngine {

    public:

        IOSEngine(int srate, int buffer_size):FaustPolyEngine()
        {
            // allocating audio driver
            fDriver = new iosaudio(srate, bsize);
        }
        
        virtual ~IOSEngine()
        {}
    
};
