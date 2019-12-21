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
#include <stdio.h>
#include <stdlib.h>

#ifndef _WIN32
#include <unistd.h>
#endif

#include "faust/OSCControler.h"
#include "faust/osc/Message.h"
#include "faust/OSCIO.h"
#include "faust/osc/RootNode.h"
#include "OSCStream.h"

#ifdef WIN32
# include "winsock2.h"
# pragma warning (disable: 4800)
#else
# include "ip/NetworkingUtils.h"
#endif

using namespace std;

namespace oscfaust
{

static const char* kHelloMsg		= "hello";
static const char* kDestMsg         = "desthost";
static const char* kJSONMsg         = "json";
static const char* kUdpOutPortMsg	= "outport";
static const char* kUdpErrPortMsg	= "errport";
static const char* kBundleMsg       = "bundle";
static const char* kXmitMsg         = "xmit";
static const char* kXmitFilter      = "xmitfilter";

//--------------------------------------------------------------------------
// ip address utility
//--------------------------------------------------------------------------
static string getHostName()
{
	char name[512];
	return (gethostname(name, 512) == -1) ? "" : name;
}

//--------------------------------------------------------------------------
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
template <typename T>
void RootNode::addAliasAux(const char* alias, const char* address, T imin, T imax, T omin, T omax)
{
    aliastarget target(address, imin, imax, omin, omax);
    fAliases[alias].push_back(target);
}

//--------------------------------------------------------------------------
void RootNode::addAlias(const char* alias, const char* address, float imin, float imax, float omin, float omax)
{
    addAliasAux<float>(alias, address, imin, imax, omin, omax);
}
    
//--------------------------------------------------------------------------
void RootNode::addAlias(const char* alias, const char* address, double imin, double imax, double omin, double omax)
{
    addAliasAux<double>(alias, address, imin, imax, omin, omax);
}

//--------------------------------------------------------------------------
static string ip2string(unsigned long ip)
{
	stringstream str;
	str << ((ip >> 24) & 0xff) << '.' << ((ip >> 16) & 0xff) << '.' << ((ip >> 8) & 0xff) << '.' << (ip & 0xff);
	return str.str();
}

//--------------------------------------------------------------------------
// handler for the get attribute message
//--------------------------------------------------------------------------
void RootNode::get(unsigned long ipdest, const string& what) const		///< handler for the 'get' message
{
 	unsigned long savedip = oscout.getAddress();	// saves the current destination IP
	oscout.setAddress(ipdest);						// sets the osc stream dest IP to the request src IP

	if (what == kXmitMsg)
		oscout << OSCStart(getOSCAddress().c_str()) << kXmitMsg << OSCControler::gXmit << OSCEnd();
	if (what == kBundleMsg)
		oscout << OSCStart(getOSCAddress().c_str()) << kBundleMsg << OSCControler::gBundle << OSCEnd();
	else if (what == kDestMsg)
		oscout << OSCStart(getOSCAddress().c_str()) << kDestMsg << ip2string(savedip) << OSCEnd();
    else if (what == kJSONMsg)
        oscout << OSCStart(getOSCAddress().c_str()) << kJSONMsg << OSCEnd();
	else if (what == kUdpOutPortMsg)
		oscout << OSCStart(getOSCAddress().c_str()) << kUdpOutPortMsg << oscout.getPort() << OSCEnd();
	else if (what == kUdpErrPortMsg)
		oscout << OSCStart(getOSCAddress().c_str()) << kUdpErrPortMsg << oscerr.getPort() << OSCEnd();

	oscout.setAddress(savedip);			// restores the destination IP
	MessageDriven::get(ipdest, what);	// and call the default behavior
}

//--------------------------------------------------------------------------
// handler for the get message
//--------------------------------------------------------------------------
void RootNode::get(unsigned long ipdest) const		///< handler for the 'get' message
{
    unsigned long savedip = oscout.getAddress();	// saves the current destination IP
	oscout.setAddress(ipdest);						// sets the osc stream dest IP to the request src IP

	oscout << OSCStart(getOSCAddress().c_str()) << kXmitMsg << OSCControler::gXmit << OSCEnd();
	oscout << OSCStart(getOSCAddress().c_str()) << kBundleMsg << OSCControler::gBundle << OSCEnd();
	oscout << OSCStart(getOSCAddress().c_str()) << kDestMsg << ip2string(savedip) << OSCEnd();
    oscout << OSCStart(getOSCAddress().c_str()) << kJSONMsg << OSCEnd();
	oscout << OSCStart(getOSCAddress().c_str()) << kUdpOutPortMsg << oscout.getPort() << OSCEnd();
	oscout << OSCStart(getOSCAddress().c_str()) << kUdpErrPortMsg << oscerr.getPort() << OSCEnd();

	map<string, vector<aliastarget> >::const_iterator i = fAliases.begin();
	while (i != fAliases.end()) {
		vector<aliastarget> targets = i->second;
		for (size_t n = 0; n < targets.size(); n++) {
			// send a alias message for each target
			const aliastarget& t = targets[n];
            // oscout << OSCStart(i->first.c_str()) << t.fMinIn << t.fMaxIn << "alias" << targets[n].fTarget.c_str() << t.fMinOut << t.fMaxOut << OSCEnd();
			oscout << OSCStart(targets[n].fTarget.c_str()) << "alias" << i->first.c_str() << t.fMinIn << t.fMaxIn << OSCEnd();
		}
		i++;
	}
	oscout.setAddress(savedip);		// restores the destination IP
	MessageDriven::get(ipdest);		// and call the default behavior
}

//--------------------------------------------------------------------------
// handling aliases
//--------------------------------------------------------------------------
    
template <typename T>
void RootNode::processAliasAux(const string& address, T val)
{
    vector<aliastarget> targets = fAliases[address];    // retrieve the address aliases
    size_t n = targets.size();                          // that could point to an arbitraty number of targets
    for (size_t i = 0; i < n; i++) {                    // for each target
        Message m(targets[i].fTarget, address);         // create a new message with the target address and the alias
        m.add(targets[i].scale(val));                   // add the scaled value of the value
        MessageDriven::processMessage(&m);              // and do a regular processing of the message
    }
}

void RootNode::processAlias(const string& address, float val)
{
    processAliasAux<float>(address, val);
}

void RootNode::processAlias(const string& address, double val)
{
    processAliasAux<double>(address, val);
}

vector<pair<string, double> > RootNode::getAliases(const string& address, double value)
{
    map<string, vector<aliastarget> >::iterator it;
    vector<pair<string, double> > res;
    for (it = fAliases.begin(); it != fAliases.end(); it++) {
        vector<aliastarget> targets = (*it).second;
        for (size_t i = 0; i < targets.size(); i++) {
            if (targets[i].fTarget == address) {
                res.push_back(make_pair((*it).first, targets[i].invscale(float(value))));
            }
        }
    }
    return res;
}

//--------------------------------------------------------------------------
// specific processMessage at RootNode: intended to handle aliases
//--------------------------------------------------------------------------
void RootNode::processMessage(const Message* msg)
{
    const string& addr = msg->address();
    float fv; double dv; int iv;
    if (msg->size() == 1) {             // there is a single parameter
        if (msg->param(0, fv))          // check the parameter float value
            processAlias(addr, fv);		// and try to process as an alias
        if (msg->param(0, dv))          // check the parameter double value
            processAlias(addr, dv);		// and try to process as an alias
        else if (msg->param(0, iv))		// not a float value : try with an int value
            processAlias(addr, float(iv));
    }
    else if (msg->size() > 1) {			// there are several parameters
        // we simulate several messages, one for each value
        for (int i = 0; i < msg->size(); i++) {
            ostringstream as; as << addr << '/' << i;		// compute an address in the form /address/i
            if (msg->param(i, fv))							// get the parameter float value
                processAlias(as.str(), fv);					// and try to process as an alias using the extended address
            if (msg->param(i, dv))							// get the parameter double value
                processAlias(as.str(), dv);					// and try to process as an alias using the extended address
            else if (msg->param(i, iv))						// not a float value : try with an int value
                processAlias(as.str(), float(iv));
        }
    }
    MessageDriven::processMessage(msg);
}

//--------------------------------------------------------------------------
// signal data handler
//--------------------------------------------------------------------------
bool RootNode::acceptSignal(const Message* msg)
{
	bool ret = true;
	int n = msg->size();
	if (n) {
		float val;
        float* buff = (float*)(alloca(sizeof(float) * n));
		for (int i = 0; i < n ; i++) {
			if (msg->param(i, val))	{		// assumes that it receives float values only
				buff[i] = val;
			} else {						// in case not
				ret = false;				// set return code to false
				break;						// and stops reading data
			}
		}
		if (ret) fIO->receive(n, buff);	// call the IO controler receive method with the float data
	}
	else ret = false;
	return ret;
}

//--------------------------------------------------------------------------
void RootNode::eraseAliases(const string& target)
{
	for (TAliasMap::iterator i = fAliases.begin(); i != fAliases.end(); ) {
		vector<aliastarget>::iterator j = i->second.begin();
		while (j != i->second.end()) {
			if (j->fTarget == target) j = i->second.erase(j);
			else j++;
		}
		if (i->second.empty()) i = fAliases.erase(i);
		else i++;
	}
}

//--------------------------------------------------------------------------
void RootNode::eraseAlias(const string& target, const string& alias)
{
	TAliasMap::iterator i = fAliases.find(alias);
	if (i != fAliases.end()) {
		vector<aliastarget>::iterator j = i->second.begin();
		while (j != i->second.end()) {
			if (j->fTarget == target) j = i->second.erase(j);
			else j++;
		}
		if (i->second.empty()) fAliases.erase(i);
	}
}

//--------------------------------------------------------------------------
bool RootNode::aliasError(const Message* msg)
{
	oscerr << msg->address().c_str() << ": incorrect alias message received" << OSCEnd();
	cerr << msg->address().c_str() << ": incorrect alias message received" << endl;
	return false;
}

//--------------------------------------------------------------------------
template <typename T>
bool RootNode::aliasMsgAux(const Message* msg, T omin, T omax)
{
    string addr = msg->address();
    switch (msg->size()) {
        case 1:			// remove all aliases for dest address
            eraseAliases(addr);
            break;
        case 2:			// remove one alias for dest address
        {
            string alias;
            if (msg->param(1, alias)) eraseAlias(addr, alias);
            else return aliasError(msg);
        }
            break;
        case 4:			// create an alias for dest address
        {
            string alias; float min, max; int imin, imax;
            if (msg->param(1, alias)) {
                if (msg->param(2, imin)) min = T(imin);
                else if (!msg->param(2, min)) return aliasError (msg);
                if (msg->param(3, imax)) max = T(imax);
                else if (!msg->param(3, max)) return aliasError (msg);
                addAliasAux<T>(alias.c_str(), addr.c_str(), min, max, omin, omax);
            }
        }
            break;
        default:
            return aliasError(msg);
    }
    return true;
}

//--------------------------------------------------------------------------
bool RootNode::aliasMsg(const Message* msg, float omin, float omax)
{
    return aliasMsgAux<float>(msg, omin, omax);
}
    
//--------------------------------------------------------------------------
bool RootNode::aliasMsg(const Message* msg, double omin, double omax)
{
    return aliasMsgAux<double>(msg, omin, omax);
}

//--------------------------------------------------------------------------
bool RootNode::accept(const Message* msg)
{
 	string val;
    
	// checks for the 'hello' message first
	if ((msg->size() == 1) && (msg->param(0, val)) && (val == kHelloMsg)) {
		hello(msg->src());
		return true;
	}
    
    // checks for the 'json' message
    if ((msg->size() >= 1) && (msg->param(0, val)) && (val == kJSONMsg)) {
        oscout << OSCStart(getOSCAddress().c_str()) << kJSONMsg << fJSON->JSON(true) << OSCEnd();
        return true;
    }

	if (MessageDriven::accept(msg)) {
		return true;
	} else if ((msg->size() >= 2) && (msg->param(0, val))) {
		string str; int num;
		if ((val == kDestMsg) && (msg->param(1, str))) {
			oscout.setAddress(str);
		} else if ((val == kUdpOutPortMsg) && (msg->param(1, num))) {
			*fUDPOut = num;
			oscout.setPort(num);
		} else if ((val == kUdpErrPortMsg) && (msg->param(1, num))) {
			*fUDPErr = num;
			oscerr.setPort(num);
		} else if ((val == kBundleMsg) && (msg->param(1, num))) {
			OSCControler::gBundle = num;
			oscout.setBundle(num);
		} else if ((val == kXmitMsg) && (msg->param(1, num))) {
			OSCControler::gXmit = num;
        } else if (val == kXmitFilter) {
            for (int i = 1; i < msg->size(); i++) {
                msg->param(i, str);
                OSCControler::addFilteredPath(str);
            }
        }
    } else if ((msg->size() == 1) && (msg->param(0, val))) {
        if (val == kXmitFilter) {
            OSCControler::resetFilteredPaths();
        }
        if (val == kBundleMsg) {
            oscout.endBundle();
		}
    } else if (fIO) {						// when still not handled and if a IO controler is set
		return acceptSignal(msg);			// try to read signal data
    }
	return false;
}

//--------------------------------------------------------------------------
void RootNode::setPorts(int* in, int* out, int* err)
{
	fUPDIn  = in;
	fUDPOut = out;
	fUDPErr = err;
}

//--------------------------------------------------------------------------
void RootNode::hello(unsigned long ipdest) const
{
	if (fUPDIn && fUDPOut && fUDPErr) {					// on 'hello' request
		unsigned long savedip = oscout.getAddress();	// saves the current dest IP
		oscout.setAddress(ipdest);						// set the destination IP
		// and sends its address + the udp port numbers (in, out and err)
		oscout << OSCStart(getOSCAddress().c_str()) << getIP() << *fUPDIn << *fUDPOut << *fUDPErr << OSCEnd();
		oscout.setAddress(savedip);						// and restores the dest IP
	}
}

} // end namespoace
