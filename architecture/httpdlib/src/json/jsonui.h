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

#ifndef __jsonui__
#define __jsonui__

#include "jsonfactory.h"

namespace httpdfaust
{

class jsonfactory;

template <typename C> class jsonui
{
	jsonfactory* fFactory;

	public:
				 jsonui(const char *name, const char* address, int port) : fFactory(0) { fFactory = new jsonfactory(name, address, port); }
		virtual ~jsonui()		{ delete fFactory; }

		// -- widget's layouts
		virtual void openFrameBox(const char* label)			{ fFactory->opengroup( "framebox", label); }
		virtual void openTabBox(const char* label)				{ fFactory->opengroup( "tabbox", label); }
		virtual void openHorizontalBox(const char* label)		{ fFactory->opengroup( "horizontalbox", label); }
		virtual void openVerticalBox(const char* label)			{ fFactory->opengroup( "verticalbox", label); }
		virtual void closeBox()									{ fFactory->closegroup(); }

		// -- active widgets
		virtual void addButton(const char* label, C* zone)			{ fFactory->addnode<C>( "button", label); }
		virtual void addToggleButton(const char* label, C* zone)	{ fFactory->addnode<C>( "togglebutton", label); }
		virtual void addCheckButton(const char* label, C* zone)		{ fFactory->addnode<C>( "checkbutton", label); }
		virtual void addVerticalSlider(const char* label, C* zone, C init, C min, C max, C step)
					{ fFactory->addnode<C>( "verticalslider", label, init, min, max, step); }
		virtual void addHorizontalSlider(const char* label, C* zone, C init, C min, C max, C step)
					{ fFactory->addnode<C>( "horizontalslider", label, init, min, max, step); }
		virtual void addNumEntry(const char* label, C* zone, C init, C min, C max, C step)
					{ fFactory->addnode<C>( "numentry", label, init, min, max, step); }

		// -- passive widgets
		virtual void addNumDisplay(const char* label, C* zone, int precision)						{}
		virtual void addTextDisplay(const char* label, C* zone, const char* names[], C min, C max)	{}
		virtual void addHorizontalBargraph(const char* label, C* zone, C min, C max)				{}
		virtual void addVerticalBargraph(const char* label, C* zone, float min, float max)			{}

		// -- metadata declarations
		virtual void declare(C* , const char* , const char* ) {}
};

} //end namespace

#endif
