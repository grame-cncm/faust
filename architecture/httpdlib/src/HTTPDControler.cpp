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
#include <unistd.h>
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

#define kVersion	 0.70f
#define kVersionStr	"0.70"

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
template<> void HTTPDControler::addnode<float> (const char* type, const char* label, float* zone, float init, float min, float max, float step)
{
	fFactory->addnode (label, zone, init, min, max);
	fJson->addnode<float> (type, label, init, min, max, step, fCurrentMeta);
	fHtml->addnode (type, label, init, min, max, step);
	fCurrentMeta.clear();
}
template<> void HTTPDControler::addnode<float> (const char* type, const char* label, float* zone, float min, float max)
{
	fFactory->addnode (label, zone, min, max);
	fJson->addnode<float> (type, label, min, max, fCurrentMeta);
	fHtml->addnode (type, label, min, max);
	fCurrentMeta.clear();
}
template<> void HTTPDControler::addnode<float> (const char* type, const char* label, float* zone)
{
	fFactory->addnode (label, zone, 0.f, 0.f, 1.f);
	fJson->addnode<float> (type, label, fCurrentMeta);
	fHtml->addnode (type, label);
	fCurrentMeta.clear();
}

template<> void HTTPDControler::addnode<double> (const char* type, const char* label, double* zone, double min, double max)
{
	fFactory->addnode (label, zone, min, max);
	fJson->addnode<double> (type, label, min, max, fCurrentMeta);
	fHtml->addnode (type, label, min, max);
	fCurrentMeta.clear();
}

template<> void HTTPDControler::addnode<double> (const char* type, const char* label, double* zone, double init, double min, double max, double step)
{
	fFactory->addnode (label, zone, init, min, max);
	fJson->addnode<double> (type, label, init, min, max, step, fCurrentMeta);
	fHtml->addnode (type, label, init, min, max, step);
	fCurrentMeta.clear();
}
template<> void HTTPDControler::addnode<double> (const char* type, const char* label, double* zone)
{
	fFactory->addnode (label, zone, 0., 0., 1.);
	fJson->addnode<double> (type, label, fCurrentMeta);
	fHtml->addnode (type, label);
	fCurrentMeta.clear();
}

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
			cout << "Faust httpd server version " << version() <<  " is running on UDP ports " << fTCPPort << endl;
		}
	}
}

//--------------------------------------------------------------------------
void HTTPDControler::quit ()
{
	fHttpd->stop();
}

}
