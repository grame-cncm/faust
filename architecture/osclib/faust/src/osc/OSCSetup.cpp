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

#include <iostream>
#include <stdexcept>

#include "OSCSetup.h"
#include "TThreads.h"
#include "OSCListener.h"

namespace oscfaust
{

//--------------------------------------------------------------------------
/*!
	\brief a specific thread to listen incoming osc packets
*/
class OscThread : public TThreads
{
	public:
		SOSCListener fListener;	
        ErrorCallback fErrCallback;
        void*         fArg;
	
        OscThread(MessageProcessor* mp, int udpport) { fListener = OSCListener::create(mp, udpport); }

        OscThread(MessageProcessor* mp, int udpport, ErrorCallback errCallback, void* arg)
        {
            fListener = OSCListener::create(mp, udpport);
            fErrCallback = errCallback;
            fArg = arg;
        }
		virtual ~OscThread() { stop(); }

		/// \brief starts the osc listener
        void run()				
        { 
            try {
                fListener->run(); 
            }
            catch (osc::Exception& ) {
                if (fErrCallback != NULL) {
                    (*fErrCallback)(fArg);
                }
            }        
            catch (std::runtime_error& ) {
                if (fErrCallback != NULL) {
                    (*fErrCallback)(fArg);
                }
            }
        }
		void stop()	{ fListener->stop(); quit(); }
		SOSCListener& listener() { return fListener; }
};

//--------------------------------------------------------------------------
OSCSetup::~OSCSetup()			{ stop(); }
bool OSCSetup::running() const	{ return fOSCThread ? fOSCThread->isRunning() : false; }

//--------------------------------------------------------------------------
bool OSCSetup::start(MessageProcessor* mp, int& inPort, int outPort, int errPort, const char* address)
{
	int port = inPort;
	bool done = false;
	do {
		try {
			OSCStream::start();
			oscout.setPort(outPort);
			oscerr.setPort (errPort);
			oscout.setAddress(address);
			oscerr.setAddress(address);
			fOSCThread = new OscThread(mp, port, fErrCallback, fArg);
            fOSCThread->start();
			done = true;
		}
        // In case the OSC Listener could not be allocated = PORT IS BUSY
		catch (std::runtime_error e) {
			if (port - inPort > 1000) return false;
			do {
				port++;
			} while ((port == outPort) || (port == errPort));
		}
	} while (!done);
	inPort = port;
	return true;
}

//--------------------------------------------------------------------------
void OSCSetup::stop()
{
	if (fOSCThread) {
		fOSCThread->stop();
		OSCStream::stop();
		delete fOSCThread;
		fOSCThread = 0;
	}
}

} // end namespoace
