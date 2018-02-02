/*

  Copyright (C) 2010  Grame

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

#include "OSCRegexp.h"

namespace oscfaust
{

//--------------------------------------------------------------------------
OSCRegexp::OSCRegexp(const char* oscre) : fRegexp (OSCRe2Re(oscre).c_str()) {}

//--------------------------------------------------------------------------
// translates an OSC regexp into a regexp
// see OSC documentation
std::string OSCRegexp::OSCRe2Re (const char* re)
{
	std::string outstr;
	bool inlist = false;
	while (*re) {
		switch (*re) {
			case '{':	outstr += '('; inlist = true; break;
			case ',':	outstr += (inlist ? '|' : ','); break;
			case '}':	outstr += ')'; inlist = false; break;
			case '*':	outstr += ".*"; break;
			case '?':	outstr += '.'; break;
			default:	outstr += *re;
		}
		re++;
	}
	return outstr;
}

//--------------------------------------------------------------------------
bool OSCRegexp::match (const char* str) const
{
	return fRegexp.MatchExact(str) != 0;
}

}
