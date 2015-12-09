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
#include "faust/OSCControler.h"
#include "faust/osc/RootNode.h"
#include "OSCStream.h"

namespace oscfaust
{

//--------------------------------------------------------------------------
template<> void FaustNode<float>::sendOSC() const 
{
    if (OSCControler::gXmit && !OSCControler::isPathFiltered(getOSCAddress())) {
        std::vector<std::string> aliases = fRoot->getAliases(getOSCAddress());
        // If aliases are present, used them
        if (aliases.size() > 0) { 
            for (size_t i = 0; i < aliases.size(); i++) {
                oscout << OSCStart(aliases[i].c_str()) << float(*fZone) << OSCEnd();
            }
        // Otherwise send on the address
        } else {    
            oscout << OSCStart(getOSCAddress().c_str()) << float(*fZone) << OSCEnd();
        }
    }
}

//--------------------------------------------------------------------------
template<> void FaustNode<double>::sendOSC() const 
{
    if (OSCControler::gXmit && !OSCControler::isPathFiltered(getOSCAddress())) {
        std::vector<std::string> aliases = fRoot->getAliases(getOSCAddress());
        // If aliases are present, used them
        if (aliases.size() > 0) {
            for (size_t i = 0; i < aliases.size(); i++) {
                oscout << OSCStart(aliases[i].c_str()) << float(*fZone) << OSCEnd();
            }
        // Otherwise send on the address
        } else {
            oscout << OSCStart(getOSCAddress().c_str()) << float(*fZone) << OSCEnd();
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
	oscout << OSCStart(getOSCAddress().c_str()) << float(*fZone) << float(fMapping.fMinOut) << float(fMapping.fMaxOut) << OSCEnd();
	oscout.setAddress(savedip);							// and restores the destination IP
}

} // end namespoace
