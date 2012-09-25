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


#ifndef __htmlfactory__
#define __htmlfactory__

#include <stack>
#include <string>

#include "htmlpage.h"

namespace httpdfaust
{

//--------------------------------------------------------------------------
/*!
	\brief a factory to build a OSC UI hierarchy
	
	Actually, makes use of a stack to build the UI hierarchy.
	It includes a pointer to a OSCIO controler, but just to give it to the root node.
*/
class htmlfactory
{
	std::stack<std::string>	fGroups;	///< maintains the current hierarchy level
	htmlpage	fPage;					///< the resulting html page
	int			fSerial;				///< for html UI objects unique ids

	public:
				 htmlfactory(const char *name, const char* address, int port);
		virtual ~htmlfactory() {}

		void addnode (const char* type, const char* label);
		void addnode (const char* type, const char* label, float init, float min, float max, float step);
		void addnode (const char* type, const char* label, float min, float max);
		void opengroup (const char* type, const char* label);
		void closegroup ();

		htmlpage&	root()			{ return fPage; }
};

} // end namespoace

#endif
