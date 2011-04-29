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

#include "FaustNode.h"
#include "Message.h"
#include "OSCStream.h"

namespace oscfaust
{

//--------------------------------------------------------------------------
bool FaustNode::store( float val )
{
	*fZone = fMapping.scale(val);
	return true;
}

//--------------------------------------------------------------------------
bool FaustNode::accept( const Message* msg )
{
	if (msg->size() == 1) {			// checks for the message parameters count
									// messages with a param count other than 1 are rejected
		int ival; float fval;
		if (msg->param(0, fval)) return store (fval);				// accepts float values
		else if (msg->param(0, ival)) return store (float(ival));	// but accepts also int values
	}
	return MessageDriven::accept(msg);
}


//--------------------------------------------------------------------------
void FaustNode::get (unsigned long ipdest ) const
{
	unsigned long savedip = oscout.getAddress();		// saves the current destination IP
	oscout.setAddress(ipdest);							// sets the osc stream dest IP
	// send a state message on 'get' request
	oscout << OSCStart(getOSCAddress().c_str()) << 	*fZone << fMapping.fMinOut << fMapping.fMaxOut << OSCEnd();
	oscout.setAddress(savedip);							// and restores the destination IP
}

} // end namespoace
