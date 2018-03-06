
/* 
    The code below is intended to send osc messages
*/

#include <iostream>
#include <string>
#include <stdexcept>

#include "osc/OscOutboundPacketStream.h"
#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscPrintReceivedElements.h"
#include "ip/UdpSocket.h"


#define ADDRESS "127.0.0.1"
#define OUTPUT_BUFFER_SIZE 4096
#define FAUST_OSC_SND_PORT 5511

using namespace std;

class FaustOscPacketListener : public osc::OscPacketListener{
	UdpListeningReceiveSocket* fSocket;
	
	public:
		FaustOscPacketListener () : fSocket(0) {}
		
		void setSocket(UdpListeningReceiveSocket* socket) { fSocket = socket; }

	protected:

    void ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint )
    {
        (void) remoteEndpoint; // suppress unused parameter warning
        try {
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
            osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
            string address (m.AddressPattern());
            if ((address == "/quit") && fSocket)
            	fSocket->Break();
            else {
            	cout << m << endl;
        	}
        } catch( osc::Exception& e ){
            cerr << "error while parsing message: " << m.AddressPattern() << ": " << e.what() << "\n";
        }
    }    
};

static void run( int port )
{
    try {
		FaustOscPacketListener listener;
		UdpListeningReceiveSocket s( IpEndpointName( IpEndpointName::ANY_ADDRESS, port ), &listener );
		listener.setSocket (&s);
		s.Run();
	} catch( osc::Exception& e ){
		std::cerr << "error running osclistener: " <<  e.what() << "\n";
	}
}

/******************************************************************************
                                   MAIN
*******************************************************************************/
int main(int argc, char *argv[])
{
	run (FAUST_OSC_SND_PORT);
  	return 0;
}
					
