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

#include <string>

#include "RootNode.h"
#include "Message.h"

using namespace std;

namespace httpdfaust
{

static const char* kJSONAddr = "/JSON";


//--------------------------------------------------------------------------
bool RootNode::processMessage(const Message* msg, vector<Message*>& outMsg)
{
	const string& addr = msg->address();
	if (addr.empty() || (addr == "/")) {
		return accept(msg, outMsg);
	}
	else if (addr == kJSONAddr) {
		Message* msg = new Message(fJson);
		msg->setMIMEType("application/json");
		outMsg.push_back(msg);
		return true;
	}
	return MessageDriven::processMessage(msg, outMsg);
}

//--------------------------------------------------------------------------
bool RootNode::accept(const Message* msg, vector<Message*>& outMsg)
{
	string val;
	// checks for the 'JSON' message first
	if ((msg->size() == 0) && (msg->address() == "/")) {
		Message* msg = new Message (fHtml);
		msg->setMIMEType("text/html");
		outMsg.push_back(msg);
		return true;
	}
	return MessageDriven::accept(msg, outMsg);
}

} // end namespoace
