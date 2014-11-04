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


#ifndef __jsonnode__
#define __jsonnode__

#include <string>
#include <vector>
#include <map>

#include "smartpointer.h"

namespace httpdfaust
{

class jsonnode;
typedef SMARTP<jsonnode>	Sjsonnode;

typedef std::map<std::string, std::string>	TMetas;

//______________________________________________________________________________
/*!
\internal
\brief to be used in place of std::endl
	to provide indentation of the json output.
*/
class jsonendl {
	private:
		int fIndent;
	public:
				 jsonendl() : fIndent(0) {}
		virtual ~jsonendl() {}

		//! increase the indentation
		jsonendl& operator++ (int)  { fIndent++; return *this; }	// prefix
		jsonendl& operator++ ()		{ fIndent++; return *this; }	// postfix
		//! decrease the indentation
		jsonendl& operator-- (int)  { fIndent--; return *this; }	// prefix
		jsonendl& operator-- ()		{ fIndent--; return *this; }	// postfix
		//! reset the indentation to none
		void print(std::ostream& os) const;
};
std::ostream& operator<< (std::ostream& os, const jsonendl& eol);

//--------------------------------------------------------------------------
/*!
	\brief a faust node is a terminal node and represents a faust parameter controler
*/
class jsonnode : public smartable
{
	std::string fAddress;
	public:
		virtual ~jsonnode() {}

		virtual void	add (const Sjsonnode& node)		{}
		virtual void	print(std::ostream& out, jsonendl& eol) const = 0;
		virtual const std::string&	getAddress() const							{ return fAddress; }
		virtual void				setAddress( const std::string& address) 	{ fAddress = address; }
};

} // end namespoace

#endif
