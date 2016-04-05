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


#ifndef __jsongroup__
#define __jsongroup__

#include <ostream>
#include <string>
#include <vector>

#include "jsonnode.h"

namespace httpdfaust
{

//--------------------------------------------------------------------------
/*!
	\brief a faust group is a terminal node and represents a faust parameter controler
*/
class jsongroup : public jsonnode
{
	std::string fName;
	std::string fType;
    TMetas fMeta;
	std::vector<Sjsonnode> fContent;
	
	protected:
				 jsongroup(const char *name, const char* type, const TMetas& m)  : fName(name), fType(type), fMeta(m) {}
		virtual ~jsongroup() {}
		
	public:
	static Sjsonnode create (const char *name, const char* type, const TMetas& m) { return new jsongroup (name, type, m); }

		virtual void	add (const Sjsonnode& node)		{ fContent.push_back(node); }
		virtual void	print(std::ostream& out, jsonendl& eol) const;
};

} // end namespoace

#endif
