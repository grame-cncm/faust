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
	std::map<std::string, std::string>	fMeta;	// the current meta declarations

	public:
				 jsonui(const char *name, const char* address, int port) : fFactory(0) { fFactory = new jsonfactory(name, address, port); }
		virtual ~jsonui()				{ delete fFactory; }

		// -- widget's layouts
		virtual void openTabBox(const char* label)					{ fFactory->opengroup( "tgroup", label); }
		virtual void openHorizontalBox(const char* label)			{ fFactory->opengroup( "hgroup", label); }
		virtual void openVerticalBox(const char* label)				{ fFactory->opengroup( "vgroup", label); }
		virtual void closeBox()										{ fFactory->closegroup(); }

		// -- active widgets
		virtual void addButton(const char* label, C* zone)			{ fFactory->addnode<C>( "button", label, fMeta); }
		virtual void addCheckButton(const char* label, C* zone)		{ fFactory->addnode<C>( "checkbox", label, fMeta); }
		virtual void addVerticalSlider(const char* label, C* zone, C init, C min, C max, C step)
							{ fFactory->addnode<C>( "vslider", label, init, min, max, step, fMeta); }
		virtual void addHorizontalSlider(const char* label, C* zone, C init, C min, C max, C step)
							{ fFactory->addnode<C>( "hslider", label, init, min, max, step, fMeta); }
		virtual void addNumEntry(const char* label, C* zone, C init, C min, C max, C step)
							{ fFactory->addnode<C>( "nentry", label, init, min, max, step, fMeta); }

		// -- passive widgets
		virtual void addHorizontalBargraph(const char* label, C* zone, C min, C max)		{ fFactory->addnode<C>( "hbargraph", label, fMeta); }
		virtual void addVerticalBargraph(const char* label, C* zone, float min, float max)	{ fFactory->addnode<C>( "vbargraph", label, fMeta); }

		// -- metadata declarations
		virtual void declare(C* , const char* key, const char* val)		{ fMeta[key] = val; }

		//--------------------------------------------
		// additionnal methods (not part of UI)
		//--------------------------------------------
		void numInput( int n )								{ fFactory->root().setInputs(n); }
		void numOutput( int n )								{ fFactory->root().setOutputs(n); }
		void declare(const char* key, const char* val)		{ fFactory->root().declare(key, val);}

		//--------------------------------------------
		// and eventually how to get the json as a string
		//--------------------------------------------
		const char*	json ()									{ return fFactory->root().json(); }
};

} //end namespace

#endif
