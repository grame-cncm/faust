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

#ifndef __OSCControler__
#define __OSCControler__

#include <string>

namespace oscfaust
{

class OSCIO;
class OSCSetup;
class FaustFactory;

//--------------------------------------------------------------------------
/*!
	\brief the main Faust OSC Lib API
	
	The OSCControler is essentially a glue between the memory representation (in charge of the FaustFactory), 
	and the network services (in charge of OSCSetup).
*/
class OSCControler
{
	int fUDPPort, fUDPOut, fUPDErr;		// the udp ports numbers
	std::string		fDestAddress;		// the osc messages destination address
	FaustFactory *	fFactory;			// a factory to build the memory represetnatin
	OSCSetup*		fOsc;				// the network manager (handles the udp sockets)
	OSCIO*			fIO;				// hack for OSC IO support (actually only relayed to the factory)

	public:
		/*
			base udp port is chosen in an unassigned range from IANA PORT NUMBERS (last updated 2011-01-24)
			see at http://www.iana.org/assignments/port-numbers
			5507-5552  Unassigned
		*/
		enum { kUDPBasePort = 5510};

				 OSCControler (int argc, char *argv[], OSCIO* io=0);
		virtual ~OSCControler ();
	
		//--------------------------------------------------------------------------
		// addnode, opengroup and closegroup are simply relayed to the factory
		//--------------------------------------------------------------------------
		// Add a node in the current group (top of the group stack)
		template <typename C> void addnode (const char* label, C* zone, C init, C min, C max);
		
		//--------------------------------------------------------------------------
		// Add a node using its fullpath from the root instead of the current group
		// This method is used for alias messages. The arguments imin and imax allow
		// to map incomming values from the alias input range to the actual range 
		template <typename C> void addfullpathnode (const std::string& fullpath, C* zone, C imin, C imax, C init, C min, C max);
        	
		void opengroup (const char* label);
		void closegroup ();

		//--------------------------------------------------------------------------
		void run ();				// starts the network services
		void quit ();				// stop the network services
		
		int	getUDPPort()			{ return fUDPPort; }
		int	getUDPOut()				{ return fUDPOut; }
		int	getUDPErr()				{ return fUPDErr; }
		const char*	getDesAddress() { return fDestAddress.c_str(); }
		const char*	getRootName();	// probably useless, introduced for UI extension experiments

		static float version();				// the Faust OSC library version number
		static const char* versionstr();	// the Faust OSC library version number as a string
};

}

#endif
