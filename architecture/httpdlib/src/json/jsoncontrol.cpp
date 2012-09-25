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

#include "jsoncontrol.h"

using namespace std;

namespace httpdfaust
{

//--------------------------------------------------------------------------
//void jsoncontrol::print(std::ostream& out, jsonendl& eol) const
//{
//	bool button = (fType == "button");
//	bool bargraph = (fType == "vbargraph") || (fType == "hbargraph");
//
//	out << eol << "{"; eol++;
//	out << eol << "\"type\": \"" << fType << "\",";
//	out << eol << "\"label\": \"" << fName << "\",";
//	out << eol << "\"address\": \"" << getAddress() << "\"";
//	if (fMeta.size()) {
//		out << eol << "\"meta\": \"" << "[ "; eol++;
////		for (TMetas::const_iterator i=fMeta.begin(); i!=fMeta.end();) {
//		TMetas::const_iterator i=fMeta.begin();
//		while (true) {
//			out << eol << "{ \"" << i->first << "\": \"" << i->second << "\"}";
//			if (++i == fMeta.end()) break;
//			out << ",";			
//		}
//		out << --eol << "]";
//	}
//
//	if (button) { out << --eol << "}"; return; }		// done for buttons
//
//	if (!bargraph)
//		out << "," << eol << "\"init\": \"" << fInit << "\",";
//	out << eol << "\"min\": \"" << fMin << "\",";
//	out << eol << "\"max\": \"" << fMax << "\",";
//	if (!bargraph)
//		out << eol << "\"step\": \"" << fStep << "\"";
//	out << --eol << "}";
//}

} // end namespoace
