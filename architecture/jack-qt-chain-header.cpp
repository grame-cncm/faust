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

#include <vector>
#include <utility>
#include <string>
#include <libgen.h>

#include "faust/dsp/dsp.h"
#include "faust/gui/GUI.h"
#include "faust/audio/jack-dsp.h"
#include "faust/misc.h"
#include "faust/gui/faustqt.h"
#include "faust/gui/FUI.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif

// DSP chain
std::vector< std::pair<std::string, dsp*> > dsp_chain;

// Combine UIs
static void combineUI(const std::vector< std::pair<std::string, dsp*> >& chain, UI* interface)
{
    interface->openTabBox("Chain");
    for (int i = 0; i < chain.size(); i++) {
        chain[i].second->buildUserInterface(interface);
    }
    interface->closeBox();
}

// Create and init JACK clients
static std::vector<audio*> initJACKClients(const std::vector< std::pair<std::string, dsp*> >& chain)
{
    std::vector<audio*> res;
    
    for (int i = 0; i < chain.size(); i++) {
        jackaudio* audio = new jackaudio();
        audio->init(chain[i].first.c_str(), chain[i].second);
        res.push_back(audio);
    }
    
    return res;
}

// Start JACK clients
static void startJACKClients(std::vector<audio*> chain)
{
    for (int i = 0; i < chain.size(); i++) {
        chain[i]->start();
    }
}

// Close and delete JACK clients
static void stopJACKClients(const std::vector<audio*>& chain)
{
    for (int i = 0; i < chain.size(); i++) {
        chain[i]->stop();
        delete chain[i];
    }
}

// Globals
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;


