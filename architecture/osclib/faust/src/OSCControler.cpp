/*

  Faust Project

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

#include <stdlib.h>
#include "OSCControler.h"
#include "FaustFactory.h"
#include "OSCSetup.h"


namespace oscfaust
{

#define kVersion	0.50f
#define kVersionStr	"0.50"

static const char* kUDPPortOpt	= "-port";
static const char* kUDPOutOpt	= "-outport";
static const char* kUDPErrOpt	= "-errport";
static const char* kUDPDestOpt	= "-dest";

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

static const char* getDestOption (int argc, char *argv[], const std::string& option, const char* defaultValue)
{
	for (int i=0; i < argc-1; i++) {
		if (option == argv[i])
			return argv[i+1];
	}
	return defaultValue;
}


//--------------------------------------------------------------------------
OSCControler::OSCControler (int argc, char *argv[])
	:	fUDPPort(kUDPBasePort), fUDPOut(kUDPBasePort+1), fUPDErr(kUDPBasePort+2),
		fDestAddress("localhost")
{
	fUDPPort = getPortOption (argc, argv, kUDPPortOpt, fUDPPort);
	fUDPOut  = getPortOption (argc, argv, kUDPOutOpt, fUDPOut);
	fUPDErr  = getPortOption (argc, argv, kUDPErrOpt, fUPDErr);
	fDestAddress = getDestOption (argc, argv, kUDPDestOpt, fDestAddress.c_str());

	fFactory = new FaustFactory();
	fOsc = new OSCSetup();
}

OSCControler::~OSCControler ()
{ 
	quit(); 
	delete fFactory;
	delete fOsc;
}

//--------------------------------------------------------------------------
float OSCControler::version()				{ return kVersion; }
const char* OSCControler::versionstr()		{ return kVersionStr; }

//--------------------------------------------------------------------------
void OSCControler::addnode (const char* label, float* zone, float init, float min, float max)
{
	fFactory->addnode (label, zone, init, min, max);
}

//--------------------------------------------------------------------------
void OSCControler::opengroup (const char* label)
{
	fFactory->opengroup (label);
}

//--------------------------------------------------------------------------
void OSCControler::closegroup ()
{
	fFactory->closegroup ();
}

//--------------------------------------------------------------------------
void OSCControler::run ()
{
	fOsc->start (fFactory->root(), fUDPPort, fUDPOut, fUPDErr, fDestAddress.c_str());
	oscout << OSCStart("Faust OSC version ") << versionstr() <<  OSCEnd();
}

//--------------------------------------------------------------------------
void OSCControler::quit ()
{
	fOsc->stop();
}

}
