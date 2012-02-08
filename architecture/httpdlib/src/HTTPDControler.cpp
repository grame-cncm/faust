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
#include <sstream>
#include <netdb.h>

#include "HTTPDControler.h"
#include "FaustFactory.h"
#include "HTTPDSetup.h"
#include "jsonfactory.h"
#include "htmlfactory.h"
#include "RootNode.h"

using namespace std;

namespace httpdfaust
{

#define kVersion	 0.60f
#define kVersionStr	"0.60"

static const char* kPortOpt	= "-port";

//--------------------------------------------------------------------------
// utility for command line arguments 
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
// utility for host name and ip address 
//--------------------------------------------------------------------------
static bool getNetInfos(string& name, string& ip)
{
	char szBuffer[1024];

	if(gethostname(szBuffer, sizeof(szBuffer)))
	return false;
	
	name = szBuffer;
	struct hostent *host = gethostbyname(szBuffer);
	if(!host) return false;

	stringstream s;
	unsigned char * ptr = (unsigned char *)host->h_addr;
	s << int(ptr[0]) << "." << int(ptr[1]) << "." << int(ptr[2]) << "." << int(ptr[3]);
	ip = s.str();
	return true;
}


//--------------------------------------------------------------------------
HTTPDControler::HTTPDControler (int argc, char *argv[], const char* applicationname)
	: fTCPPort(kTCPBasePort), fJson(0)
{
	fTCPPort = getPortOption (argc, argv, kPortOpt, fTCPPort);
	fFactory = new FaustFactory();
	fHttpd = new HTTPDSetup();
	
	string host, ip;
	getNetInfos (host, ip);
	if (host.find('.') == string::npos) host.clear();	// ignore non qualifed domain names and uses IP number
	const char* hostname = host.size() ? host.c_str() : (ip.size() ? ip.c_str() : "localhost");
	fJson = new jsonfactory(applicationname, hostname, fTCPPort);
	fHtml = new htmlfactory(applicationname, hostname, fTCPPort);
}

HTTPDControler::~HTTPDControler ()
{ 
	quit(); 
	delete fFactory;
	delete fHttpd;
	delete fJson;
}

//--------------------------------------------------------------------------
float HTTPDControler::version()				{ return kVersion; }
const char* HTTPDControler::versionstr()	{ return kVersionStr; }

//--------------------------------------------------------------------------
// Add a node in the current group (top of the group stack)
void HTTPDControler::addnode (const char* type, const char* label, float* zone, float init, float min, float max, float step)
{
	fFactory->addnode (label, zone, init, min, max);
	fJson->addnode (type, label, init, min, max, step);
	fHtml->addnode (type, label, init, min, max, step);
}
void HTTPDControler::addnode (const char* type, const char* label, float* zone)
{
	fFactory->addnode (label, zone, 0, 0, 1);
	fJson->addnode (type, label);
	fHtml->addnode (type, label);
}

//--------------------------------------------------------------------------
// Add a node using its fullpath from the root instead of the current group
// This method is used for alias messages. The arguments imin and imax allow
// to map incomming values from the alias input range to the actual range 
//void HTTPDControler::addfullpathnode (const string& fullpath, float* zone, float imin, float imax, float init, float min, float max)
//{
//	fFactory->addfullpathnode (fullpath, zone, imin, imax, init, min, max);
//}

//--------------------------------------------------------------------------
void HTTPDControler::opengroup (const char* type, const char* label)
{
	fFactory->opengroup (label);
	fJson->opengroup (type, label);
	fHtml->opengroup (type, label);
}

//--------------------------------------------------------------------------
void HTTPDControler::closegroup ()
{
	fFactory->closegroup ();
	fJson->closegroup ();
	fHtml->closegroup ();
}

//--------------------------------------------------------------------------
// start the network services
void HTTPDControler::run ()
{
	SMessageDriven root = fFactory->root();		// first get the root node
	if (root) {
		// and cast it to a RootNode
		RootNode * rootnode = dynamic_cast<RootNode*> ((MessageDriven*)root);
		// starts the network services
		if (fHttpd->start (root, fTCPPort)) {
			stringstream strjson;
			fJson->root().setPort (fTCPPort);
			fJson->root().print(strjson);
			if (rootnode) rootnode->setJSON (strjson.str());

			stringstream strhtml;
			fHtml->root().setPort (fTCPPort);
			fHtml->root().print(strhtml);
			if (rootnode) rootnode->setHtml (strhtml.str());
			// and outputs a message
			cout << "Faust httpd server version " << versionstr() <<  " is running on UDP ports " << fTCPPort << endl;
		}
	}
}

//--------------------------------------------------------------------------
void HTTPDControler::quit ()
{
	fHttpd->stop();
}

}
