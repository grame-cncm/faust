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
#include <sstream>

#include "faust/OSCControler.h"
#include "faust/osc/FaustFactory.h"
#include "faust/OSCIO.h"
#include "faust/osc/RootNode.h"

#include "OSCSetup.h"
#include "OSCFError.h"
#include "OSCRegexp.h"

#ifdef WIN32
# pragma warning (disable: 4800)
#endif

using namespace std;

namespace oscfaust
{

#define kVersion     1.22f
#define kVersionStr "1.22"

static const char* kUDPPortOpt	= "-port";
static const char* kUDPOutOpt	= "-outport";
static const char* kUDPErrOpt	= "-errport";
static const char* kUDPDestOpt	= "-desthost";
static const char* kBundleOpt	= "-bundle";
static const char* kXmitOpt		= "-xmit";
static const char* kXmitFilterOpt = "-xmitfilter";
static const char* kReuseOpt 	= "-reuse";
static const char* kHelp 		= "-help";

// below is the multicast address use when reuse address and port are on
static const char* kMulticastAddress = "224.0.0.1";

int OSCControler::gXmit = 0;		// a static variable to control the transmission of values
                                    // i.e. the use of the interface as a controler
int OSCControler::gBundle = 0;		// a static variable to control the transmission of values

std::vector<OSCRegexp*> OSCControler::fFilteredPaths;
	
//--------------------------------------------------------------------------
// help and usage
//--------------------------------------------------------------------------
static void osc_usage()
{
	cout << "OSC UI options: " << endl;
	cout << "\t" << kUDPPortOpt 	<< " num \t\t(default: 5510)" << endl;
	cout << "\t" << kUDPOutOpt  	<< " num \t\t(default: 5511)" << endl;
	cout << "\t" << kUDPErrOpt  	<< " num  \t\t(default: 5512)" << endl;
	cout << "\t" << kUDPDestOpt  	<< " [ip|hostname] (default: localhost)" << endl;
	cout << "\t" << kReuseOpt  		<< " [0|1] \t\t(default: 0)" << endl;
	cout << "\t" << kBundleOpt  	<< " [0|1] \t\t(default: 0)" << endl;
	cout << "\t" << kXmitOpt  		<< " [0|1|2] \t\t(default: 0)" << endl;
	cout << "\t" << kXmitFilterOpt  << " <filtered paths list>" << endl;
}

static void checkHelp(int argc, char *argv[], const std::string& option)
{
	for (int i = 1; i < argc; i++)
		if (option == argv[i]) osc_usage();
}

//--------------------------------------------------------------------------
// utilities for command line arguments 
//--------------------------------------------------------------------------
static int getPortOption(int argc, char *argv[], const std::string& option, int defaultValue)
{
	for (int i = 0; i < argc-1; i++) {
		if (option == argv[i]) {
			int val = int(strtol(argv[i+1], 0, 10));
			if (val) return val;
		}
	}
	return defaultValue;
}

static const char* getDestOption(int argc, char* argv[], const std::string& option, const char* defaultValue)
{
	for (int i = 1; i < argc-1; i++) {
		if (option == argv[i])
			return argv[i+1];
	}
	return defaultValue;
}

static int getIntOption(int argc, char* argv[], const std::string& option, bool defaultValue)
{
	for (int i = 1; i < argc-1; i++) {
    	if (option == argv[i]) {
			int val = int(strtol(argv[i+1], 0, 10));
			return val;
		}
	}
	return defaultValue;
}

static void treatXmitFilterOption(int argc, char* argv[], const std::string& option)
{
    for (int i = 1; i < argc-1; i++) {
        if (option == argv[i]) {
            int j = i+1;
            while (j < argc) {
                if (argv[j][0] == '-') {
                    return;
                } else {
                    OSCControler::addFilteredPath(argv[j]);
                }
                j++;
            }
        }
    }
}

//--------------------------------------------------------------------------
OSCControler::OSCControler(int argc, char* argv[], GUI* ui, JSONUI* json, OSCIO* io, ErrorCallback errCallback, void* arg, bool init)
	: fUDPPort(kUDPBasePort), fUDPOut(kUDPBasePort+1), fUPDErr(kUDPBasePort+2), fIO(io), fInit(init)
{
	checkHelp(argc, argv, kHelp);
	fUDPPort = getPortOption(argc, argv, kUDPPortOpt, fUDPPort);
	fUDPOut  = getPortOption(argc, argv, kUDPOutOpt, fUDPOut);
	fUPDErr  = getPortOption(argc, argv, kUDPErrOpt, fUPDErr);
	fDestAddress = getDestOption (argc, argv, kUDPDestOpt, "localhost");
	gXmit   = getIntOption(argc, argv, kXmitOpt, kNoXmit);
	gBundle = getIntOption(argc, argv, kBundleOpt, 0);

	if (getIntOption(argc, argv, kReuseOpt, 0)) {
		fBindAddress = kMulticastAddress;
	}
    treatXmitFilterOption(argc, argv, kXmitFilterOpt);
 
	fFactory = new FaustFactory(ui, json, io);
	fOsc = new OSCSetup(errCallback, arg);
}
    
//--------------------------------------------------------------------------
OSCControler::~OSCControler()
{ 
	stop(); 
	delete fFactory;
	delete fOsc;
}

//--------------------------------------------------------------------------
float OSCControler::version()			{ return kVersion; }
const char* OSCControler::versionstr()	{ return kVersionStr; }

//--------------------------------------------------------------------------
static std::string quote(const char* str)	
{ 
	std::string outstr(str);
	outstr.insert (0, 1, '\'');
	outstr += '\''; 
	return outstr;
}

//--------------------------------------------------------------------------
// start the network services
string OSCControler::getInfos() const
{
    SRootNode rootnode = fFactory->root();		// first get the root node
    if (!rootnode) return "no root node defined";

    stringstream sstr;
    sstr << "Faust OSC version " << versionstr() << " - " << quote(rootnode->getName()) << " is running on UDP ports "
    << fUDPPort << ", " << fUDPOut << ", " << fUPDErr << ", sending on " << fDestAddress;
    if (gXmit > 0) sstr << ", with xmit mode = " << gXmit;
    if (gBundle) sstr << ", with bundle mode ON.";
    if (!fBindAddress.empty())
        sstr << " Listening is bound to " << fBindAddress << ".";
    if (fIO)
        sstr << " Using OSC IO with " << fIO->numInputs() << " input channel(s) and " << fIO->numOutputs() << " output channel(s)" << fIO->numOutputs();
    return sstr.str();
}

//--------------------------------------------------------------------------
// start the network services
void OSCControler::run()
{
	SRootNode rootnode = fFactory->root();		// first get the root node
	if (rootnode) {
		// informs the root node of the udp ports numbers (required to handle the 'hello' message
		rootnode->setPorts(&fUDPPort, &fUDPOut, &fUPDErr);
		
        // starts the network services
		fOsc->start(rootnode, fUDPPort, fUDPOut, fUPDErr, gBundle, getDestAddress(), fBindAddress.empty() ? 0 : fBindAddress.c_str());

		string infos = getInfos();
		// and outputs a message on the osc output port
		oscout << OSCStart("Faust") << infos.substr(5) << OSCEnd();
        // and also on the standard output 
        cout << infos << endl;
    } else {
        cerr << "Cannot start OSC controler\n";
    }
}

//--------------------------------------------------------------------------
void OSCControler::endBundle() { if (gBundle && fOsc) fOsc->endBundle(); }

//--------------------------------------------------------------------------
const char*	OSCControler::getRootName() const { return fFactory->root()->getName(); }

//--------------------------------------------------------------------------    
void OSCControler::addFilteredPath(std::string path) 
{
    OSCRegexp* regexp = new OSCRegexp(path.c_str());
    fFilteredPaths.push_back(regexp);
}
    
//--------------------------------------------------------------------------
bool OSCControler::isPathFiltered(std::string path) 
{
    for (size_t i = 0; i < fFilteredPaths.size(); i++) {
        if (fFilteredPaths[i]->match(path.c_str()))
            return true;
    }
    return false;
}
    
//--------------------------------------------------------------------------
void OSCControler::resetFilteredPaths()
{
    for (int i = int(fFilteredPaths.size()-1); i >= 0; i--) {
        OSCRegexp* reg = fFilteredPaths[i];
        fFilteredPaths.erase(fFilteredPaths.begin()+i);
        delete reg;
    }
}  

//--------------------------------------------------------------------------
void OSCControler::stop()
{
	fOsc->stop();
}

} // namespace
