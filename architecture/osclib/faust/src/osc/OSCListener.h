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


#ifndef __OSCListener__
#define __OSCListener__

#include "faust/osc/smartpointer.h"
#include "faust/osc/MessageProcessor.h"

// oscpack include files
#include "ip/UdpSocket.h"
#include "osc/OscPacketListener.h"

typedef void (*ErrorCallback)(void*);  

namespace oscfaust
{

//--------------------------------------------------------------------------
/*!
	\brief an OSC listener that converts OSC input to Messages
	
	OSCListener makes the glue between the oscpack library
	and the faust lib osc messages representation
	\see Message in Message.h
*/
class OSCListener : public osc::OscPacketListener, public smartable
{
	UdpListeningReceiveSocket* fSocket;	///< the udp socket listener
	MessageProcessor* fMsgHandler;
	bool	fRunning;
	bool	fSetDest;
	int		fPort;

	public:
		static SMARTP<OSCListener> create(MessageProcessor* mp, int port)
			{ return new OSCListener(mp, port); }

		/*!
			\brief process OSC messages

			\param m the OSC message (pre-processed by the base class)
			\param remoteEndpoint the sender IP address
		*/
		virtual void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint);
		virtual void run();
		virtual void stop()				{ fRunning = false; if (fSocket) fSocket->AsynchronousBreak(); }
		virtual void setPort(int port)	{ fPort = port; }
		virtual void restart(int port)	{ fPort = port; if (fSocket) fSocket->AsynchronousBreak(); }

	protected:
				 OSCListener(MessageProcessor* mp, int port);
		virtual ~OSCListener();

};
typedef class SMARTP<OSCListener> SOSCListener;

} // end namespoace

#endif
