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


#ifndef __jsoncontrol__
#define __jsoncontrol__

#include <ostream>
#include <string>
#include <map>
#include "jsonnode.h"

namespace httpdfaust
{

//--------------------------------------------------------------------------
/*!
	\brief a faust control is a terminal node and represents a faust parameter controler
*/
template <typename C> class jsoncontrol : public jsonnode
{
	std::string fName;
	std::string fType;
	C fInit, fMin, fMax, fStep;
	TMetas fMeta;
		
	public:
		
	static Sjsonnode create (const char *name, const char* type, C min, C max, const TMetas& m)
			{ return new jsoncontrol (name, type, min, max, m); }
	static Sjsonnode create (const char *name, const char* type, C init, C min, C max, C step, const TMetas& m)
			{ return new jsoncontrol (name, type, init, min, max, step, m); }
	static Sjsonnode create (const char *name, const char* type, const TMetas& m) 
			{ return new jsoncontrol (name, type, m); }

		virtual void	print(std::ostream& out, jsonendl& eol) const
		{
			bool button = (fType == "button") || (fType == "checkbox");
			bool bargraph = (fType == "vbargraph") || (fType == "hbargraph");

			out << eol << "{"; eol++;
			out << eol << "\"type\": \"" << fType << "\",";
			out << eol << "\"label\": \"" << fName << "\",";
			out << eol << "\"address\": \"" << getAddress() << "\"";
			if (fMeta.size()) {
				out << "," << eol << "\"meta\": " << "[ "; eol++;
				TMetas::const_iterator i=fMeta.begin();
				while (true) {
					out << eol << "{ \"" << i->first << "\": \"" << i->second << "\"}";
					if (++i == fMeta.end()) break;
					out << ",";			
				}
				out << --eol << "]";
			}

			if (button) { out << --eol << "}"; return; }		// done for buttons

			if (!bargraph) {
				out << "," << eol << "\"init\": \"" << fInit << "\"";
			}
			out << "," << eol << "\"min\": \"" << fMin << "\",";
			out << eol << "\"max\": \"" << fMax << "\"";
			if (!bargraph) {
				out << "," << eol << "\"step\": \"" << fStep << "\"";
            }
			out << --eol << "}";
		}
	
	protected:

				 jsoncontrol(const char *name, const char* type, const TMetas& m)
					: fName(name), fType(type), fInit(0), fMin(0), fMax(1), fStep(1), fMeta(m) {}

				 jsoncontrol(const char *name, const char* type, C min, C max, const TMetas& m)
					: fName(name), fType(type), fMin(min), fMax(max), fStep(0), fMeta(m) {}

				 jsoncontrol(const char *name, const char* type, C init, C min, C max, C step, const TMetas& m)
					: fName(name), fType(type), fInit(init), fMin(min), fMax(max), fStep(step), fMeta(m) {}

		virtual ~jsoncontrol() {}
};

} // end namespoace

#endif
