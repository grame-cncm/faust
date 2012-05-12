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
#include <unistd.h>

#include "RootNode.h"
#include "Message.h"
#include "OSCStream.h"
#include "OSCControler.h"
#include "OSCIO.h"

#ifdef WIN32
# include "winsock2.h"
#else
# include "ip/NetworkingUtils.h"
#endif

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
// signal data handler
//--------------------------------------------------------------------------
bool RootNode::acceptSignal( const Message* msg )
{
	bool ret = true;
	int n = msg->size();
	if (n) {
		float val, * buff = new float[n];
		for (int i = 0; i < n ; i++) {
			if (msg->param(i, val))			// assumes that it receives float values only
				buff[i] = val;
			else {							// in case not
				ret = false;				// set return code to false
				break;						// and stops reading data
			}
		}
		if (ret) fIO->receive (n, buff);	// call the IO controler receive method with the float data
		delete buff;
	}
	else ret = false;
	return ret;
}

//--------------------------------------------------------------------------
bool RootNode::accept( const Message* msg )
{
	string val;
	// checks for the 'hello' message first
	if ((msg->size() == 1) && (msg->param(0, val)) && (val == kHelloMsg) ) {
		hello (msg->src());
		return true;
	}
	else if (MessageDriven::accept (msg))	// next checks for standard handlers ('get' for example)
		return true;
	else if (fIO)							// when still not handled and if a IO controler is set
		return acceptSignal (msg);			// try to read signal data
	return false;
}

//--------------------------------------------------------------------------
void RootNode::setPorts (int* in, int* out, int* err)
{
	fUPDIn  = in;
	fUDPOut = out;
	fUDPErr = err;
}

//--------------------------------------------------------------------------
void RootNode::hello (unsigned long ipdest ) const
{
	if (fUPDIn && fUDPOut && fUDPErr) {					// on 'hello' request
		unsigned long savedip = oscout.getAddress();	// saves the current dest IP
		oscout.setAddress(ipdest);						// set the destination IP
		// and sends its address + the udp port numbers (in, out and err)
		oscout  << OSCStart(getOSCAddress().c_str()) << getIP() << *fUPDIn << *fUDPOut << *fUDPErr << OSCEnd();
		oscout.setAddress(savedip);						// and restores the dest IP
	}
}

} // end namespoace
