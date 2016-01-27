/*

  Copyright (C) 2012 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include "jsonfaustui.h"
#include "jsonui.h"

namespace httpdfaust
{

jsonfaustui::jsonfaustui(const char *name, const char* address, int port)
{
	fJSON = new jsonui<FAUSTFLOAT>(name, address, port);
}

jsonfaustui::~jsonfaustui()		{ delete fJSON; }

//--------------------------------------------
// UI methods
//--------------------------------------------
// -- widget's layouts
void jsonfaustui::openTabBox(const char* label)				{ fJSON->openTabBox(label); }
void jsonfaustui::openHorizontalBox(const char* label)		{ fJSON->openHorizontalBox(label); }
void jsonfaustui::openVerticalBox(const char* label)		{ fJSON->openVerticalBox(label); }
void jsonfaustui::closeBox()								{ fJSON->closeBox(); }

		// -- active widgets
void jsonfaustui::addButton(const char* label, FAUSTFLOAT* zone)		{ fJSON->addButton(label, zone); }
void jsonfaustui::addCheckButton(const char* label, FAUSTFLOAT* zone)	{ fJSON->addCheckButton(label, zone); }

void jsonfaustui::addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{ fJSON->addVerticalSlider(label, zone, init, min, max, step); }

void jsonfaustui::addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{ fJSON->addHorizontalSlider(label, zone, init, min, max, step); }

void jsonfaustui::addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{ fJSON->addNumEntry(label, zone, init, min, max, step); }

// -- passive widgets
void jsonfaustui::addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
	{ fJSON->addHorizontalBargraph(label, zone, min, max); }
void jsonfaustui::addVerticalBargraph(const char* label, FAUSTFLOAT* zone, float min, float max)
	{ fJSON->addVerticalBargraph(label, zone, min, max); }

// -- metadata declarations
void jsonfaustui::declare(FAUSTFLOAT* zone, const char* key, const char* val)		{ fJSON->declare(zone, key, val); }

//--------------------------------------------
// additionnal methods (not part of UI)
//--------------------------------------------
void jsonfaustui::numInput(int n)							{ fJSON->numInput(n);}
void jsonfaustui::numOutput(int n)                          { fJSON->numOutput(n);}
void jsonfaustui::declare(const char* key, const char* val)	{ fJSON->declare(key, val); }

std::string	jsonfaustui::json(bool flatten)                 { return fJSON->json(flatten); }

} //end namespace

