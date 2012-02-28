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

#include "FaustNode.h"
#include "Message.h"
#include "HTTPDServer.h"

using namespace std;

namespace httpdfaust
{

//--------------------------------------------------------------------------
//bool FaustNode::store( float val )
//{
//	*fZone = fMapping.scale(val);
//	return true;
//}

//--------------------------------------------------------------------------
//bool FaustNode::accept( const Message* msg, vector<Message*>& outMsg )
//{
//	if (msg->size() == 2) {			// checks for the message parameters count
//									// messages with a param count other than 2 are rejected
//		string key;
//		if (msg->param(0, key) &&  (key == "value")) {
//			float val=0;
//			if (msg->param(1, val)) {
//				store (val);			// accepts float values
//			}
//			get (outMsg);
//			return true;
//		}
//	}
//	return MessageDriven::accept(msg, outMsg);
//}


//--------------------------------------------------------------------------
//void FaustNode::get (vector<Message*>& outMsg ) const
//{
//	Message * msg = new Message (getAddress());
//	msg->add (*fZone);
//	outMsg.push_back(msg);
//}

} // end namespoace
