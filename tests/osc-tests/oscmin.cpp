/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it 
    and/or modify it under the terms of the GNU General Public License 
    as published by the Free Software Foundation; either version 3 of 
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License 
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work 
    that contains this FAUST architecture section and distribute  
    that work under terms of your choice, so long as this FAUST 
    architecture section is not modified. 

 ************************************************************************
 ************************************************************************/

#include <libgen.h>
#include <unistd.h>
#include <iostream>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "faust/gui/OSCUI.h"
#include "faust/misc.h"


//---------------------------------------------------------------------------
// a dummy audio interface - adapted from faust/audio/dummy-audio.h
//---------------------------------------------------------------------------
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <pthread.h>
			
#include "faust/dsp/dsp.h"
#include "faust/audio/audio.h"


class dummyaudio : public audio {

    private:
        dsp* fDSP;

        long fSampleRate;
        long fBufferSize;
    
        FAUSTFLOAT** fInChannel;
        FAUSTFLOAT** fOutChannel;
    
        int fNumInputs;
        int fNumOutputs;    

    public:

        dummyaudio()
            :fSampleRate(48000), fBufferSize(32),
            fInChannel(0), fOutChannel(0)
        {}
    
        virtual ~dummyaudio()
        {
            for (int i = 0; i < fNumInputs; i++) 
                delete[] fInChannel[i];
            for (int i = 0; i < fNumOutputs; i++)
               delete[] fOutChannel[i];
            
            delete [] fInChannel;
            delete [] fOutChannel;
        }

        virtual bool init(const char* name, dsp* dsp)
        {
            fDSP = dsp;
            
            // To be used in destructor
            fNumInputs = fDSP->getNumInputs();
            fNumOutputs = fDSP->getNumOutputs();            
        	fDSP->init(fSampleRate);
            
            fInChannel  = new FAUSTFLOAT*[fDSP->getNumInputs()];
            fOutChannel = new FAUSTFLOAT*[fDSP->getNumOutputs()];
            
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                fInChannel[i] = new FAUSTFLOAT[fBufferSize];
                memset(fInChannel[i], 0, sizeof(FAUSTFLOAT) * fBufferSize);
            }
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                fOutChannel[i] = new FAUSTFLOAT[fBufferSize];
                memset(fOutChannel[i], 0, sizeof(FAUSTFLOAT) * fBufferSize);
            }
            return true;
        }
    
        virtual bool start() { return true; }
        virtual void stop()  {}

        void render()
        {
            fDSP->compute(fBufferSize, fInChannel, fOutChannel);
            if (fDSP->getNumOutputs() > 0) {
                for (int frame = 0; frame < fBufferSize; frame++) {
                    std::cout << frame << ":\t" << std::fixed << std::setprecision(6) << fOutChannel[0][frame] << std::endl;
                }
            }
        }
    
        virtual int getBufferSize() { return fBufferSize; }
        virtual int getSampleRate() { return fSampleRate; }
        virtual int getNumInputs()  { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
};


/* 
    The code below is intended to send osc messages
*/
#include <libgen.h>
#include <stdlib.h>
#include <unistd.h>

#include <fstream>
#include <sstream>
#include <string>

#include <iostream>
#include <string>
#include <stdexcept>

#include "osc/OscOutboundPacketStream.h"
#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"
#include <libgen.h>

using namespace std;

#define kBuffSize 		1024
#define kUndefinesValue 1111111111.f

typedef struct {
	float	value;
	string	address;
} oscmsg;

static bool readline (ifstream& fs, oscmsg& msg)
{
	char line[kBuffSize];
	fs.getline (line, kBuffSize);
	stringstream s(line);
	string address; float value = kUndefinesValue;
	s >> address >> value;
	if (address.size() && (value != kUndefinesValue)) {
		msg.address = address;
		msg.value = value;
		return true;
	}
	return false;
}


#define ADDRESS "127.0.0.1"
#define OUTPUT_BUFFER_SIZE 4096
#define FAUST_OSC_PORT 5510


template<typename T> bool send(UdpTransmitSocket& socket, const char* oscaddress, T val)
{
	char buffer[OUTPUT_BUFFER_SIZE];
	try {
//		UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, port ) );
		osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
		p << osc::BeginMessage( oscaddress );
		p << val;
		p << osc::EndMessage;
//		transmitSocket.Send( p.Data(), p.Size() );
		socket.Send( p.Data(), p.Size() );
		return true;
	}
	catch (std::runtime_error e) {
		cerr << "error: " << e.what() << endl;
		return false;
	}
}


/**************************BEGIN USER SECTION **************************/

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/
<<includeIntrinsic>>

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					
mydsp DSP;

std::list<GUI*> GUI::fGuiList;

/******************************************************************************
*******************************************************************************

                                MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/
int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "usage " << basename(argv[0]) << " <file>" << endl;
		cerr << "where <file> contains OSC textual messages" << endl;
		exit (1);
	}

	string name = basename(argv[0]);

	OSCUI oscinterface (name.c_str(), argc, argv);
	DSP.buildUserInterface(&oscinterface);

    // Allocate the audio driver to render 10 buffers of 512 frames
    dummyaudio audio;
    audio.init("OSCMin", &DSP);
	
	oscinterface.run();
	UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, FAUST_OSC_PORT ) );

	string file (argv[1]);
	ifstream fs (file);
	if (fs.is_open()) {
		send (transmitSocket, "/*", "get");	
		audio.render();
		while (!fs.eof()) {
			oscmsg msg;
			if (readline (fs, msg)) { 
				cerr << "send: " << msg.address << " " << msg.value << endl;
				send (transmitSocket, msg.address.c_str(), msg.value);
				usleep (100);
				audio.render();
			}
		}
	}
	else {
		cerr << "can't open file " << file << endl;
		exit(1);
	}

	UdpTransmitSocket endSocket( IpEndpointName( ADDRESS, FAUST_OSC_PORT + 1 ) );
	send (endSocket, "/quit", 1);

    oscinterface.stop();    
  	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
					
