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

#include "htmlui.h"
#include "htmlfactory.h"

htmlui::htmlui(const char *name, const char* address, int port) 
					: fFactory(0) { fFactory = new httpdfaust::htmlfactory(name, address, port); }
htmlui::~htmlui() { delete fFactory; }

void htmlui::openTabBox(const char* label)			{ fFactory->opengroup( "tgroup", label); }
void htmlui::openHorizontalBox(const char* label)	{ fFactory->opengroup( "hgroup", label); }
void htmlui::openVerticalBox(const char* label)		{ fFactory->opengroup( "vgroup", label); }
void htmlui::closeBox()								{ fFactory->closegroup(); }

void htmlui::addButton(const char* label, float*)
					{ fFactory->addnode( "button", label); }
void htmlui::addCheckButton(const char* label, float*)
					{ fFactory->addnode( "checkbox", label); }

void htmlui::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
					{ fFactory->addnode( "vslider", label, init, min, max, step); }
void htmlui::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
					{ fFactory->addnode( "hslider", label, init, min, max, step); }
void htmlui::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
					{ fFactory->addnode( "nentry", label, init, min, max, step); }

void htmlui::addHorizontalBargraph(const char* label, float* zone, float min, float max) {}
void htmlui::addVerticalBargraph(const char* label, float* zone, float min, float max) {}

