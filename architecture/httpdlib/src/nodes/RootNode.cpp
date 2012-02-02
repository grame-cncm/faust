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

#include <string>

#include "RootNode.h"
#include "Message.h"

using namespace std;

namespace httpdfaust
{

static const char * kJSONMsg = "JSON";


//--------------------------------------------------------------------------
bool RootNode::accept( const Message* msg )
{
	string val;
	// checks for the 'hello' message first
	if ((msg->size() == 1) && (msg->param(0, val)) && (val == kJSONMsg) ) {

		return true;
	}
	else if (MessageDriven::accept (msg))	// next checks for standard handlers ('get' for example)
		return true;
	return false;
}

} // end namespoace
