/*
  Copyright (c) Grame 2009

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr
  
*/

#ifndef __OSCStream__
#define __OSCStream__

#include <string>
#include <vector>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

namespace oscfaust
{

//--------------------------------------------------------------------------
typedef struct OSCStart { 
	const char* fAddress;
	OSCStart() {}
	OSCStart(const char* a) : fAddress(a) {}
} OSCStart;

typedef struct OSCErr : public OSCStart { 
	OSCErr() : OSCStart("error:") {}
} OSCErr;

typedef struct OSCWarn : public OSCStart { 
	OSCWarn() : OSCStart("warning:") {}
} OSCWarn;

typedef struct OSCEnd {} OSCEnd;

#define kLocalhost	0x7f000001

//--------------------------------------------------------------------------
/*!
\brief	OSC output streams
*/
class OSCStream 
{
	enum		{ kOutBufferSize = 16384 };
	enum state	{ kIdle, kInProgress };
	
	state		fState;
	int			fPort;				// the destination UDP port
	unsigned long fAddress;			// the destination IP address
	char		fBuffer[kOutBufferSize];

	osc::OutboundPacketStream	fOutStream;
	UdpSocket*					fSocket;
	
    static int fRefCount; // Since this stream is shared, a counter is needed to know when to delete object.
    
//	void initSocket();
	
	public:
	static void start();
	static void stop();

        OSCStream(UdpSocket* socket) 
            : fState(kIdle), fPort(1024), fAddress(kLocalhost), fOutStream(fBuffer, kOutBufferSize), fSocket(socket) 
        {
            fSocket->allowBroadcast();
        } 
		virtual ~OSCStream() {}
		
		osc::OutboundPacketStream& stream()				{ return fOutStream; }
		int					getPort() const             { return fPort; }
		unsigned long		getAddress() const			{ return fAddress; }
		UdpSocket*			socket()					{ return fSocket; }
		int					state()	const				{ return fState; }
		
		OSCStream&			start(const char * address);
		OSCStream&			end();
		void				send(unsigned long ipdest, int port);

		void setPort(int port)							{ fPort = port; }
		void setAddress(unsigned long address)			{ fAddress = address; }
		void setAddress(const std::string& address);
};

						OSCStream& operator <<(OSCStream& s, OSCEnd val);
						OSCStream& operator <<(OSCStream& s, const OSCStart& val);
						OSCStream& operator <<(OSCStream& s, const OSCErr& val);
						OSCStream& operator <<(OSCStream& s, const OSCWarn& val);
						OSCStream& operator <<(OSCStream& s, const std::string& val);
template <typename T>	OSCStream& operator <<(OSCStream& s, T val)		{ s.stream() << val; return s; }
template <typename T>	OSCStream& operator <<(OSCStream& s, const std::vector<T>& val)
						{ 
							for (unsigned int i =0; i < val.size(); i++) s << val[i];
							return s; 
						}


extern OSCStream* _oscout;		// OSC standard output stream
extern OSCStream* _oscerr;		// OSC standard input stream

#define oscout (*_oscout)
#define oscerr (*_oscerr)

} // end namespace

#endif
