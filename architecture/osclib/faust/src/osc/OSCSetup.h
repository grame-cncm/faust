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

#ifndef __OSCSetup__
#define __OSCSetup__

#include <string>
#include <ostream>
#include "OSCStream.h"

typedef void (*ErrorCallback)(void*);  

namespace oscfaust
{

class OscThread;
class MessageProcessor;
//--------------------------------------------------------------------------
/*!
	\brief network management utility
*/
class OSCSetup
{
    private:
    
        OscThread*fOSCThread;		// a thread that is listening to the osc in socket
        ErrorCallback fErrCallback;
        void* fArg;
    
	public:
    
        OSCSetup(ErrorCallback errCallback = NULL, void* arg = NULL) : fOSCThread(0), fErrCallback(errCallback), fArg(arg) {}
		virtual ~OSCSetup();

		bool start(MessageProcessor* mp, int& inPort, int outPort, int errPort, bool bundlemode, const char* address, const char* bindaddress);
        void stop();
        void endBundle();
        void bundle(bool state);

		bool running() const;
};

} // end namespoace

#endif
