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

#include "jsonfactory.h"
#include "jsoncontrol.h"
#include "jsongroup.h"

using namespace std;

namespace httpdfaust
{

/**
 * Add a node to the OSC UI tree in the current group at the top of the stack 
 */
void jsonfactory::addnode(Sjsonnode node, const char* label)
{
	string address;
	if (fNodes.size()) {
		address = fNodes.top()->getAddress();
		fNodes.top()->add(node);
	}
	else fRoot.add(node);
	address += "/";
	address += label;
	node->setAddress(address);
}

/**
 * Open a group in the current group and place it on the top of the stack. 
 * Takes into account that due to alias, a group can been previously created.  
 */
void jsonfactory::opengroup(const char* type, const char* label, const TMetas& m)
{
	Sjsonnode node = jsongroup::create(label, type, m);
	addnode(node, label);
	fNodes.push(node);
}

//--------------------------------------------------------------------------
void jsonfactory::closegroup()
{
	fNodes.pop();
}

} // end namespoace
