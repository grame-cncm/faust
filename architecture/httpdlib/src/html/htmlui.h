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

#ifndef __htmlui__
#define __htmlui__


namespace httpdfaust { class htmlfactory; }

class htmlui
{
	httpdfaust::htmlfactory* fFactory;

	public:
				 htmlui(const char *name, const char* address, int port);
		virtual ~htmlui();

		// -- widget's layouts
		virtual void openTabBox(const char* label);
		virtual void openHorizontalBox(const char* label);
		virtual void openVerticalBox(const char* label);
		virtual void closeBox();

		// -- active widgets
		virtual void addButton(const char* label, float* zone);
		virtual void addCheckButton(const char* label, float* zone);
		virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
		virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
		virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);

		// -- passive widgets
		virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
		virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);

		// -- metadata declarations

		virtual void declare(float*, const char*, const char*) {}
};

#endif
