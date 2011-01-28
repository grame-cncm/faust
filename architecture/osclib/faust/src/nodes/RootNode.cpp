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
#include <sstream>

#include "RootNode.h"
#include "Message.h"
#include "OSCStream.h"
#include "OSCControler.h"
#include "ip/NetworkingUtils.h"

using namespace std;

namespace oscfaust
{

static const char * kHelloMsg = "hello";


//--------------------------------------------------------------------------
// ip address utility
//--------------------------------------------------------------------------
static string getHostName()
{
	char name[512];
	int ret = gethostname(name, 512);
	if (ret == -1) return "";
	return name;
}

string getIP()
{
	string name = getHostName();
	stringstream ipStr;
	if (name.size()) {
		unsigned long ip = GetHostByName(name.c_str());
		ipStr	<< ((ip >> 24) & 0xff) << '.'
				<< ((ip >> 16) & 0xff) << '.'
				<< ((ip >> 8) & 0xff) << '.'
				<< (ip & 0xff);
	}
	return ipStr.str();
}

//--------------------------------------------------------------------------
void RootNode::accept( const Message* msg )
{
	string val;
	if ((msg->size() == 1) && (msg->param(0, val)) && (val == kHelloMsg) ) {
		hello (msg->src());
	}
	else MessageDriven::accept (msg);
}


//--------------------------------------------------------------------------
void RootNode::hello (unsigned long ipdest ) const
{
	unsigned long savedip = oscout.getAddress();
	oscout.setAddress(ipdest);
	oscout  << OSCStart(getOSCAddress().c_str()) << 	getIP() 
			<< OSCControler::getUDPPort() << OSCControler::getUDPOut() << OSCControler::getUDPErr() << OSCEnd();
	oscout.setAddress(savedip);
}

} // end namespoace
