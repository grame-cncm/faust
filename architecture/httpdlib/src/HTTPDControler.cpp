/*

  Faust Project

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

#include <stdlib.h>
#include <iostream>

#include "HTTPDControler.h"
#include "FaustFactory.h"
#include "HTTPDSetup.h"
//#include "OSCFError.h"
#include "RootNode.h"

using namespace std;

namespace httpdfaust
{

#define kVersion	 0.50f
#define kVersionStr	"0.50"

static const char* kPortOpt	= "-port";

//--------------------------------------------------------------------------
// utilities for command line arguments 
//--------------------------------------------------------------------------
static int getPortOption (int argc, char *argv[], const std::string& option, int defaultValue)
{
	for (int i=0; i < argc-1; i++) {
		if (option == argv[i]) {
			int val = strtol( argv[i+1], 0, 10);
			if (val) return val;
		}
	}
	return defaultValue;
}

//--------------------------------------------------------------------------
HTTPDControler::HTTPDControler (int argc, char *argv[])
	: fTCPPort(kTCPBasePort), fJSON(0)
{
	fTCPPort = getPortOption (argc, argv, kPortOpt, fTCPPort);
	fFactory = new FaustFactory();
	fHttpd = new HTTPDSetup();
}

HTTPDControler::~HTTPDControler ()
{ 
	quit(); 
	delete fFactory;
	delete fHttpd;
}

//--------------------------------------------------------------------------
float HTTPDControler::version()				{ return kVersion; }
const char* HTTPDControler::versionstr()	{ return kVersionStr; }

//--------------------------------------------------------------------------
// Add a node in the current group (top of the group stack)
void HTTPDControler::addnode (const char* label, float* zone, float init, float min, float max)
{
	fFactory->addnode (label, zone, init, min, max);
}

//--------------------------------------------------------------------------
// Add a node using its fullpath from the root instead of the current group
// This method is used for alias messages. The arguments imin and imax allow
// to map incomming values from the alias input range to the actual range 
void HTTPDControler::addfullpathnode (const string& fullpath, float* zone, float imin, float imax, float init, float min, float max)
{
//	fFactory->addfullpathnode (fullpath, zone, imin, imax, init, min, max);
}

//--------------------------------------------------------------------------
void HTTPDControler::opengroup (const char* label)
{
	fFactory->opengroup (label);
}

//--------------------------------------------------------------------------
void HTTPDControler::closegroup ()
{
	fFactory->closegroup ();
}

//--------------------------------------------------------------------------
// start the network services
void HTTPDControler::run ()
{
	SMessageDriven root = fFactory->root();		// first get the root node
	if (root) {
		// and cast it to a RootNode
		RootNode * rootnode = dynamic_cast<RootNode*> ((MessageDriven*)root);
		// informs the root node of the udp ports numbers (required to handle the 'hello' message
//		if (rootnode) rootnode->setPorts (&fUDPPort, &fUDPOut, &fUPDErr);
		// starts the network services
		if (fHttpd->start (root, fTCPPort))
			// and outputs a message
			cout << "Faust httpd server version " << versionstr() <<  " is running on UDP ports " << fTCPPort << endl;
	}
}

//--------------------------------------------------------------------------
void HTTPDControler::quit ()
{
	fHttpd->stop();
}

}
