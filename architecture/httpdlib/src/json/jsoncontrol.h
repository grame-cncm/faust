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
	bool  fButton;
	
	protected:
				 jsoncontrol(const char *name, const char* type) 
					: fName(name), fType(type), fInit(0), fMin(0), fMax(0), fStep(0), fButton(true) {}
				 jsoncontrol(const char *name, const char* type, C init, C min, C max, C step) 
					: fName(name), fType(type), fInit(init), fMin(min), fMax(max), fStep(step), fButton(false) {}
		virtual ~jsoncontrol() {}
		
	public:
	static Sjsonnode create (const char *name, const char* type, C init, C min, C max, C step) 
			{ return new jsoncontrol (name, type, init, min, max, step); }
	static Sjsonnode create (const char *name, const char* type) 
			{ return new jsoncontrol (name, type); }

		virtual void	print(std::ostream& out, jsonendl& eol) const
		{
			out << eol << "{"; eol++;
			out << eol << "\"type\": \"" << fType << "\",";
			out << eol << "\"label\": \"" << fName << "\",";
			out << eol << "\"address\": \"" << getAddress() << "\"";
			if (!fButton) {
				out << "," << eol << "\"init\": \"" << fInit << "\",";
				out << eol << "\"min\": \"" << fMin << "\",";
				out << eol << "\"max\": \"" << fMax << "\",";
				out << eol << "\"step\": \"" << fStep << "\"";
			}
			out << --eol << "}";
		}
};

} // end namespoace

#endif
