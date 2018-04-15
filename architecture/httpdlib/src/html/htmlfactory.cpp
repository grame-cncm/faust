/*

  Copyright (C) 2011 Grame

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

#include <iostream>
#include <sstream>

#include "htmlfactory.h"

using namespace std;

namespace httpdfaust
{

//--------------------------------------------------------------------------
htmlfactory::htmlfactory(const char *name, const char* address, int port) 
	: fPage(name, address, port), fSerial(1) 
{
	fGroups.push("");
}

void htmlfactory::addnode(const char* type, const char* label)
{
	string stype (type);
	string url = /*fPage.getUrl() +*/ fGroups.top() + "/";
	url += label;
	stringstream id; id << "button" << fSerial++;	// computes slider id
	if (stype == "button") {
		fPage << "<tr><td class='label'></td>\n";
		fPage << "<td class='control'><button id='"<< id.str() << "' name='" << url
			  << "' onmousedown='fausthandler(\"" << url << "\", 1)'"
			  << " onmouseup='fausthandler(\"" << url << "\", 0)'>play</button></td>\n";
		fPage << "<td class='value'></td>\n";
	}
	else if ((stype == "togglebutton") ||  (stype == "checkbutton")) {
		fPage << "<tr><td class='label'></td>\n";
		fPage << "<td class='control'><input type='checkbox' id='"<< id.str() << "' name='" << url
			  << "'  value=0 onchange='fausthandler(\"" << url << "\", this.value)'\n";
		fPage << "<td class='value'></td>\n";
	}
}

void htmlfactory::addnode(const char* type, const char* label, float init, float min, float max, float step)
{
	string url = /*fPage.getUrl() +*/ fGroups.top() + "/";
	url += label;
	stringstream id; id << "slider" << fSerial++;	// computes slider id
	string vid = "v"; vid += id.str();				// computes text value id
	fPage << "<tr><td class='label'>" << label << "</td>\n";
	fPage << "<td class='control'><input type='range' id='" << id.str() << "' name='" << url
		  << "' min=" << min << " max=" << max << " step=" << step << " value=" << init 
		  << " onchange='sliderhandler(\"" << url << "\", this.value, \"#" << vid << "\")'></td>\n";
	fPage << "<td class='value'><input type='text' id='" << vid << "' name='" << url << "' value=" << init << " size=6 "
		  << "onchange='sliderhandler(\"" << url << "\", this.value, \"#" << id.str() << "\")'></td>\n"
		  << "</tr>\n";
}

void htmlfactory::addnode (const char* type, const char* label, float min, float max)
{
	// don't know what to do with bargraph 
}

/**
 * Open a group in the current group and place it on the top of the stack. 
 * Takes into account that due to alias, a group can been previously created.  
 */
void htmlfactory::opengroup(const char* type, const char* label)
{
	string path = fGroups.top() + "/";
	path += label;
	fGroups.push (path);
	if (fGroups.size() == 2)		// first group: actually the address space root
		fPage.setRoot(fGroups.top());
}

//--------------------------------------------------------------------------
void htmlfactory::closegroup()
{
	fGroups.pop();
}

} // end namespoace
