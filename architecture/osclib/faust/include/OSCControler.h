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

class OSCControler
{
	int fUDPPort, fUDPOut, fUPDErr;
	std::string		fDestAddress;
	FaustFactory *	fFactory;
	OSCSetup*		fOsc;
	OSCIO*			fIO;

	public:
		/*
			base udp port is chosen in an unassigned range from IANA PORT NUMBERS (last updated 2011-01-24)
			see at http://www.iana.org/assignments/port-numbers
			5507-5552  Unassigned
		*/
		enum { kUDPBasePort = 5510};

				 OSCControler (int argc, char *argv[], OSCIO* io);
		virtual ~OSCControler ();
	
		void addnode (const char* label, float* zone, float init, float min, float max);
		void opengroup (const char* label);
		void closegroup ();
		void run ();
		void quit ();
		
		int	getUDPPort()			{ return fUDPPort; }
		int	getUDPOut()				{ return fUDPOut; }
		int	getUDPErr()				{ return fUPDErr; }
		const char*	getDesAddress() { return fDestAddress.c_str(); }
		const char*	getRootName();

		static float version();
		static const char* versionstr();
};

}

#endif
