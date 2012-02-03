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

#include "Address.h"
#include "Message.h"
#include "MessageDriven.h"
#include "HTTPDServer.h"

using namespace std;
namespace httpdfaust
{

//--------------------------------------------------------------------------
bool MessageDriven::processMessage( const Message* msg, vector<Message*>& outMsg )
{
	const string addr = msg->address();

	// get the message address head
	string head = Address::addressFirst(addr).c_str();
	// and call propose with this regexp and with the dest osc address tail
	return propose (msg, head.c_str(), Address::addressTail (addr), outMsg);
	
//	if (addr != "/*") {
//		// search for alias root (fixme : could be stored in a field)
//		MessageDriven * aliasroot = 0;
//		for (int i=0; i<size(); i++) {
//			if (subnode(i)->name() == "alias") {
//				aliasroot = subnode(i);
//			}
//		}
//	
//		// if we have aliases in the tree
//		// we need to check if the message if for an alias address
//		if (aliasroot != 0) {
//			OSCRegexp r2 ("alias");
//			
//			if (msg->size() == 1) {
//				aliasroot->propose (msg, &r2, addr);
//			} else if (msg->size() > 1) {
//				// we simulated several messages
//				for (int i=0; i< msg->size(); i++) {
//					ostringstream 	as; as << addr << '/' << i;
//					string 			a(as.str());
//					Message 		m(a);
//					float			v;
//					
//					msg->param(i, v);
//					m.add(v);
//					aliasroot->propose (&m, &r2, a);
//				}
//			}
//		}
//	}
}

//--------------------------------------------------------------------------
// the full address is simply the prefix + '/' + name
string MessageDriven::getAddress() const
{
	string address(fPrefix);
	address += "/";
	address += fName;
	return address;
}

//--------------------------------------------------------------------------
// terminal nodes should override the get method
void MessageDriven::get (vector<Message*>& outMsg) const
{
	// basic get handler propagates the get call to subnodes
	for (vector<SMessageDriven>::const_iterator i = fSubNodes.begin(); i != fSubNodes.end(); i++)
		(*i)->get (outMsg);
}

//--------------------------------------------------------------------------
bool MessageDriven::accept( const Message* msg, vector<Message*>& outMsg )
{
	// the basic accept method only checks for the 'get' message
	if (msg->size() == 0) {
		get (outMsg);
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool MessageDriven::propose( const Message* msg, const char* address, const std::string addrTail, std::vector<Message*>& outMsg)
{
	if (name() == address) {			// try to match address with the object name. 
		if (addrTail.empty() || (addrTail == "/")) {	// it matches and the tail is empty
			return accept(msg, outMsg);	// then call accept()
		}
		else {							// it matches but the tail is not empty
			string head = Address::addressFirst(addrTail).c_str();
			for (vector<SMessageDriven>::iterator i = fSubNodes.begin(); i != fSubNodes.end(); i++) {
				// then propagate propose() to subnodes with a new regexp and a new tail
				if ((*i)->propose (msg, head.c_str(), Address::addressTail(addrTail), outMsg) )
					return true;
			}
		}
	}
	return false;
}

} // end namespoace
