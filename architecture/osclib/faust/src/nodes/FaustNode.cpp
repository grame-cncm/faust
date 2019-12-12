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

#include "faust/osc/FaustNode.h"
#include "faust/osc/RootNode.h"
#include "faust/OSCControler.h"
#include "OSCStream.h"

using namespace std;

namespace oscfaust
{

static const char* kAliasMsg = "alias";

//--------------------------------------------------------------------------
template<> void FaustNode<float>::sendOSC() const 
{
    if (OSCControler::gXmit != kNoXmit && !OSCControler::isPathFiltered(getOSCAddress())) {
        try {
            vector<pair<string, double> > aliases = fRoot->getAliases(getOSCAddress(), *fZone);
            // If aliases are present
            if (aliases.size() > 0) {  
                for (size_t i = 0; i < aliases.size(); i++) {
                    oscout << OSCStart((aliases[i].first).c_str()) << float(aliases[i].second) << OSCEnd();
                }
            }
            // Also emit regular address
            if (OSCControler::gXmit == kAll) {
                oscout << OSCStart(getOSCAddress().c_str()) << float(*fZone) << OSCEnd();
            } 
        }
        catch(osc::Exception e) {
            cerr << "error while sending OSC: " << e.what() << endl;
            oscout.stream().Clear();
            oscerr.stream().Clear();
            oscerr << OSCStart(getOSCAddress().c_str()) << "error while sending OSC" << e.what() << OSCEnd();
        }
    }
}

//--------------------------------------------------------------------------
template<> void FaustNode<double>::sendOSC() const 
{
    if (OSCControler::gXmit != kNoXmit && !OSCControler::isPathFiltered(getOSCAddress())) {
        try {
            vector<pair<string, double> > aliases = fRoot->getAliases(getOSCAddress(), *fZone);
            // If aliases are present
            if (aliases.size() > 0) { 
                for (size_t i = 0; i < aliases.size(); i++) {
                    oscout << OSCStart((aliases[i].first).c_str()) << double(aliases[i].second) << OSCEnd();
                }
            }
            // Also emit regular address
            if (OSCControler::gXmit == kAll) {
                oscout << OSCStart(getOSCAddress().c_str()) << double(*fZone) << OSCEnd();
            } 
        }
        catch(osc::Exception e) {
            cerr << "error while sending OSC: " << e.what() << endl;
            oscout.stream().Clear();
            oscerr.stream().Clear();
            oscerr << OSCStart(getOSCAddress().c_str()) << "error while sending OSC" << e.what() << OSCEnd();
        }
    }
}

//--------------------------------------------------------------------------
template<> void FaustNode<float>::get(unsigned long ipdest) const		///< handler for the 'get' message
{
	unsigned long savedip = oscout.getAddress();		// saves the current destination IP
	oscout.setAddress(ipdest);							// sets the osc stream dest IP
	// send a state message on 'get' request
	oscout << OSCStart(getOSCAddress().c_str()) << float(*fZone) << float(fMapping.fMinOut) << float(fMapping.fMaxOut) << OSCEnd();
	oscout.setAddress(savedip);							// and restores the destination IP
}

//--------------------------------------------------------------------------
template<> void FaustNode<double>::get(unsigned long ipdest) const		///< handler for the 'get' message
{
	unsigned long savedip = oscout.getAddress();		// saves the current destination IP
	oscout.setAddress(ipdest);							// sets the osc stream dest IP
	// send a state message on 'get' request
	oscout << OSCStart(getOSCAddress().c_str()) << double(*fZone) << double(fMapping.fMinOut) << double(fMapping.fMaxOut) << OSCEnd();
	oscout.setAddress(savedip);							// and restores the destination IP
}

//--------------------------------------------------------------------------
template<> bool FaustNode<float>::accept(const Message* msg)			///< handler for the 'accept' message
{
    string str;						// check for alias message first
    if ((msg->size() >= 1) && msg->param(0, str) && (str == kAliasMsg))
        return fRoot->aliasMsg(msg, fMapping.fMinOut, fMapping.fMaxOut);
    
    if (msg->size() == 1) {			// check the message parameters count
        // messages with a param count other than 1 are rejected
        int ival; float fval; double dval;
        if ((OSCControler::gXmit == kNoXmit) || (OSCControler::gXmit == kAll) || (OSCControler::gXmit == kAlias && msg->alias() != "")) {
            if (msg->param(0, fval)) {
                return store(fval);         // accepts float values
            } else if (msg->param(0, dval)) {
                return store(dval);         // accepts double values
            } else if (msg->param(0, ival)) {
                return store(float(ival));  // but accepts also int value
            }
        }
    }
    return MessageDriven::accept(msg);
}

//--------------------------------------------------------------------------
template<> bool FaustNode<double>::accept(const Message* msg)			///< handler for the 'accept' message
{
    string str;						// check for alias message first
    if ((msg->size() >= 1) && msg->param(0, str) && (str == kAliasMsg))
        return fRoot->aliasMsg(msg, fMapping.fMinOut, fMapping.fMaxOut);
    
    if (msg->size() == 1) {			// check the message parameters count
        // messages with a param count other than 1 are rejected
        int ival; float fval; double dval;
        if ((OSCControler::gXmit == kNoXmit) || (OSCControler::gXmit == kAll) || (OSCControler::gXmit == kAlias && msg->alias() != "")) {
            if (msg->param(0, fval)) {
                return store(fval);         // accepts float values
            } else if (msg->param(0, dval)) {
                return store(dval);         // accepts double values
            } else if (msg->param(0, ival)) {
                return store(float(ival));  // but accepts also int value
            }
        }
    }
    return MessageDriven::accept(msg);
}

} // end namespoace
