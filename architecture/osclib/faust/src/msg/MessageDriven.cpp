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

#include "Message.h"
#include "MessageDriven.h"
#include "OSCAddress.h"
#include "OSCFError.h"
#include "OSCRegexp.h"

using namespace std;
namespace oscfaust
{

//--------------------------------------------------------------------------
void MessageDriven::processMessage( const Message* msg )
{
	const string addr = msg->address();
	OSCRegexp r (OSCAddress::addressFirst(addr).c_str());
	return propose (msg, &r, OSCAddress::addressTail (addr));
}

//--------------------------------------------------------------------------
string MessageDriven::getOSCAddress() const
{
	string address(fOSCPrefix);
	address += "/";
	address += fName;
	return address;
}

//--------------------------------------------------------------------------
void MessageDriven::get (unsigned long ipdest) const
{
	for (vector<SMessageDriven>::const_iterator i = fSubNodes.begin(); i != fSubNodes.end(); i++)
		(*i)->get (ipdest);
}

//--------------------------------------------------------------------------
void MessageDriven::accept( const Message* msg )
{
	if (msg->size() != 1) return;
	string val;
	if (msg->param(0, val)) {
		if (val == "get") get (msg->src());
	}
}

//--------------------------------------------------------------------------
void MessageDriven::propose( const Message* msg, const OSCRegexp* r, const std::string addrTail)
{
	if (r->match(getName())) {
		if (addrTail.empty()) {
			accept(msg);
		}
		else {
			OSCRegexp rtail (OSCAddress::addressFirst(addrTail).c_str());
			for (vector<SMessageDriven>::iterator i = fSubNodes.begin(); i != fSubNodes.end(); i++) {
				(*i)->propose (msg, &rtail, OSCAddress::addressTail(addrTail));
			}
		}
	}
}

} // end namespoace
