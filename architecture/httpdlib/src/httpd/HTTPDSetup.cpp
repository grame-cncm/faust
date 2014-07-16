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
#include <stdexcept>

#include "HTTPDSetup.h"
#include "HTTPDServer.h"
#include "MessageProcessor.h"

using namespace std;

namespace httpdfaust
{

#define kPortsScanRange		1000		// scan this number of TCP ports to find a free one (in case of busy port)

//--------------------------------------------------------------------------
HTTPDSetup::~HTTPDSetup()			{ stop(); }
bool HTTPDSetup::running() const	{ return fServer ? true : false; }
//bool HTTPDSetup::running() const	{ return fServer ? fServer->isRunning() : false; }

//--------------------------------------------------------------------------
bool HTTPDSetup::start(MessageProcessor* mp, int& tcpport )
{
	int port = tcpport;
	bool done = false;
	fServer = new HTTPDServer (mp);
	do {
		done = fServer->start(port);
		if (!done) {
			if ( port - tcpport > kPortsScanRange) return false;
			port++;
		}
	} while (!done);
	tcpport = port;
	return true;
}

//--------------------------------------------------------------------------
void HTTPDSetup::stop()
{
	if (fServer) {
		fServer->stop();
		delete fServer;
		fServer = 0;
	}
}

} // end namespoace
