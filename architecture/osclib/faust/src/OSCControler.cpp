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
#include <iostream>

#include "OSCControler.h"
#include "FaustFactory.h"
#include "OSCSetup.h"
#include "OSCFError.h"
#include "RootNode.h"
#include "OSCIO.h"

using namespace std;

namespace oscfaust
{

#define kVersion	 0.91f
#define kVersionStr	"0.91"

static const char* kUDPPortOpt	= "-port";
static const char* kUDPOutOpt	= "-outport";
static const char* kUDPErrOpt	= "-errport";
static const char* kUDPDestOpt	= "-dest";

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

static const char* getDestOption (int argc, char *argv[], const std::string& option, const char* defaultValue)
{
	for (int i=0; i < argc-1; i++) {
		if (option == argv[i])
			return argv[i+1];
	}
	return defaultValue;
}


//--------------------------------------------------------------------------
OSCControler::OSCControler (int argc, char *argv[], OSCIO* io)
	: fUDPPort(kUDPBasePort), fUDPOut(kUDPBasePort+1), fUPDErr(kUDPBasePort+2), fIO(io)
{
	fUDPPort = getPortOption (argc, argv, kUDPPortOpt, fUDPPort);
	fUDPOut  = getPortOption (argc, argv, kUDPOutOpt, fUDPOut);
	fUPDErr  = getPortOption (argc, argv, kUDPErrOpt, fUPDErr);
	fDestAddress = getDestOption (argc, argv, kUDPDestOpt, "localhost");

	fFactory = new FaustFactory(io);
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
template <> void OSCControler::addnode<float> (const char* label, float* zone, float init, float min, float max)
										{ fFactory->addnode (label, zone, init, min, max); }
template <> void OSCControler::addnode<double> (const char* label, double* zone, double init, double min, double max)
										{ fFactory->addnode (label, zone, init, min, max); }
template <> void OSCControler::addfullpathnode<float> (const std::string& fullpath, float* zone, float imin, float imax, float init, float min, float max)
										{ fFactory->addfullpathnode (fullpath, zone, imin, imax, init, min, max); }
template <> void OSCControler::addfullpathnode<double> (const std::string& fullpath, double* zone, double imin, double imax, double init, double min, double max)
										{ fFactory->addfullpathnode (fullpath, zone, imin, imax, init, min, max); }

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
static std::string quote (const char* str)	{ 
	std::string outstr ( str );
	outstr.insert (0, 1, '\'');
	outstr += '\''; 
	return outstr;
}

//--------------------------------------------------------------------------
// start the network services
void OSCControler::run ()
{
	SMessageDriven root = fFactory->root();		// first get the root node
	if (root) {
		// and cast it to a RootNode
		RootNode * rootnode = dynamic_cast<RootNode*> ((MessageDriven*)root);
		// informs the root node of the udp ports numbers (required to handle the 'hello' message
		if (rootnode) rootnode->setPorts (&fUDPPort, &fUDPOut, &fUPDErr);
		// starts the network services
		fOsc->start (root, fUDPPort, fUDPOut, fUPDErr, getDesAddress());

		// and outputs a message on the osc output port
		oscout << OSCStart("Faust OSC version") << versionstr() << "-"
				<< quote(root->getName()).c_str() << "is running on UDP ports "
				<<  fUDPPort << fUDPOut << fUPDErr;
        
        // and also on the standard output 
        cout << "Faust OSC version " << versionstr() << " application "
             << quote(root->getName()).c_str() << " is running on UDP ports "
             <<  fUDPPort << ", " << fUDPOut << ", " << fUPDErr << endl;

		if (fIO) oscout << " using OSC IO - in chans: " << fIO->numInputs() << " out chans: " << fIO->numOutputs();
		oscout << OSCEnd();

		// that should not occur unless a derivative changes the root node type
		if (!rootnode) OSCFErr << root->getName() << ": is not a root node, 'hello' message won't be supported" << OSCFEndl;
	}
}

//--------------------------------------------------------------------------
const char*	OSCControler::getRootName()	{ return fFactory->root()->getName(); }

//--------------------------------------------------------------------------
void OSCControler::quit ()
{
	fOsc->stop();
}

}
