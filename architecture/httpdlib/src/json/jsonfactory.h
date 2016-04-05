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


#ifndef __jsonfactory__
#define __jsonfactory__

#include <stack>
#include <string>

#include "jsonroot.h"
#include "jsoncontrol.h"

namespace httpdfaust
{

class jsonnode;
typedef SMARTP<jsonnode>	Sjsonnode;

//--------------------------------------------------------------------------
/*!
	\brief a factory to build a OSC UI hierarchy
	
	Actually, makes use of a stack to build the UI hierarchy.
	It includes a pointer to a OSCIO controler, but just to give it to the root node.
*/
class jsonfactory
{
	std::stack<Sjsonnode>	fNodes;		///< maintains the current hierarchy level
	jsonroot				fRoot;		///< keep track of the root node

	void addnode(Sjsonnode node, const char* label);

	public:
    
                jsonfactory(const char* name, const char* address, int port) : fRoot(name, address, port) {}
		virtual ~jsonfactory() {}

		template <typename C> void addnode (const char* type, const char* label, C min, C max, const TMetas& m) {
				addnode(jsoncontrol<C>::create (label, type, min, max, m), label);
			}

		template <typename C> void addnode (const char* type, const char* label, C init, C min, C max, C step, const TMetas& m) {
				addnode(jsoncontrol<C>::create (label, type, init, min, max, step, m), label);
			}

		template <typename C> void addnode (const char* type, const char* label, const TMetas& m) {
				addnode(jsoncontrol<C>::create (label, type, m), label);
			}

		void opengroup(const char* type, const char* label, const TMetas& m);
		void closegroup();

		jsonroot&	root()			{ return fRoot; }
};

} // end namespoace

#endif
