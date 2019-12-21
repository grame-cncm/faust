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

#include <sstream>

#include "faust/osc/Message.h"
#include "faust/osc/MessageDriven.h"

#include "OSCAddress.h"
#include "OSCFError.h"
#include "OSCRegexp.h"

using namespace std;
namespace oscfaust
{

static const char * kGetMsg = "get";

//--------------------------------------------------------------------------
void MessageDriven::processMessage(const Message* msg)
{
	const string addr = msg->address();

	// create a regular expression
	OSCRegexp r(OSCAddress::addressFirst(addr).c_str());
	// and call propose with this regexp and with the dest osc address tail
	propose(msg, &r, OSCAddress::addressTail(addr));
}

//--------------------------------------------------------------------------
// the full OSC address is simply the prefix + '/' + name
string MessageDriven::getOSCAddress() const
{
	string address(fOSCPrefix);
	address += "/";
	address += fName;
	return address;
}

//--------------------------------------------------------------------------
// terminal nodes should override the get method
void MessageDriven::get(unsigned long ipdest) const
{
	// basic get handler propagates the get call to subnodes
	for (vector<SMessageDriven>::const_iterator i = fSubNodes.begin(); i != fSubNodes.end(); i++) {
		(*i)->get(ipdest);
    }
}

//--------------------------------------------------------------------------
bool MessageDriven::accept(const Message* msg)
{
	string val, what;
	int n = msg->size();
	// the basic accept method only checks for the 'get' message
	if ((n >= 1) && (msg->param(0, val)) && (val == kGetMsg)) {
		if (n == 1) {
			get(msg->src());
		} else if ((n == 2) && msg->param(1, what)) {
			get(msg->src(), what);
        }
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
void MessageDriven::propose(const Message* msg, const OSCRegexp* r, const string& addrTail)
{
	if (r->match(getName())) {			// try to match the regular expression with the object name. 
		if (addrTail.empty()) {			// it matches and the tail is empty
			accept(msg);				// then call accept()
		} else {						// it matches but the tail is not empty
			OSCRegexp rtail (OSCAddress::addressFirst(addrTail).c_str());
			for (vector<SMessageDriven>::iterator i = fSubNodes.begin(); i != fSubNodes.end(); i++) {
				// then propagate propose() to subnodes with a new regexp and a new tail
				(*i)->propose(msg, &rtail, OSCAddress::addressTail(addrTail));
			}
		}
	}
}

} // end namespoace
