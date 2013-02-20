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

#ifndef __jack_dsp__
#define __jack_dsp__

#include <stdio.h>
#include <cstdlib>
#include <list>
#include <jack/jack.h>
#include "faust/audio/audio.h"
#include "faust/audio/dsp.h"

static int		_jack_srate(jack_nframes_t nframes, void*);
static void		_jack_shutdown(void *);
static void     _jack_info_shutdown(jack_status_t code, const char* reason, void*);
static int		_jack_process(jack_nframes_t nframes, void* client);
#ifdef _OPENMP
static void*	_jack_thread(void* arg);
#endif

/******************************************************************************
*******************************************************************************

							JACK AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/

class jackaudio : public audio {

    private:

        dsp*			fDsp;               // FAUST DSP
        jack_client_t*	fClient;            // JACK client
        int				fNumInChans;		// number of input channels
        int				fNumOutChans;       // number of output channels
        jack_port_t**	fInput_ports;       // JACK input ports
        jack_port_t**	fOutput_ports;      // JACK output ports
        
        std::list<std::pair<std::string, std::string> > fConnections;		// Connections list
        
        // Save client connections
        void save_connections()
        {
            const char** connections;
            fConnections.clear();
            
             for (int i = 0; i < fNumInChans; i++) {
                const char** connected_port = jack_port_get_all_connections(fClient, fInput_ports[i]);
                if (connected_port != NULL) {
                    for (int port = 0; connected_port[port]; port++) {
                        fConnections.push_back(make_pair(connected_port[port], jack_port_name(fInput_ports[i])));
                        printf("INPUT %s ==> %s\n", connected_port[port], jack_port_name(fInput_ports[i]));
                    }
                    jack_free(connected_port);
                }
            }
       
            for (int i = 0; i < fNumOutChans; i++) {
                const char** connected_port = jack_port_get_all_connections(fClient, fOutput_ports[i]);
                if (connected_port != NULL) {
                    for (int port = 0; connected_port[port]; port++) {
                        fConnections.push_back(make_pair(jack_port_name(fOutput_ports[i]), connected_port[port]));
                        printf("OUTPUT %s ==> %s\n", jack_port_name(fOutput_ports[i]), connected_port[port]);
                    }
                    jack_free(connected_port);
                }
            }
        }

        // Restore previous client connections
        void restore_connections()
        {
            list<pair<string, string> >::const_iterator it;
            for (it = fConnections.begin(); it != fConnections.end(); it++) {
                pair<string, string> connection = *it;
                jack_connect(fClient, connection.first.c_str(), connection.second.c_str());
            }
        }
        
        // Connect to physical inputs/outputs
        void default_connections()
        {
            char** physicalOutPorts = (char**)jack_get_ports(fClient, NULL, NULL, JackPortIsPhysical|JackPortIsOutput);
            if (physicalOutPorts != NULL) {
                for (int i = 0; i < fNumInChans && physicalOutPorts[i]; i++) {
                    jack_connect(fClient, physicalOutPorts[i], jack_port_name(fInput_ports[i]));
                }
                jack_free(physicalOutPorts);
            }
            
            char** physicalInPorts = (char**)jack_get_ports(fClient, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
            if (physicalInPorts != NULL) {
                for (int i = 0; i < fNumOutChans && physicalInPorts[i]; i++) {
                    jack_connect(fClient, jack_port_name(fOutput_ports[i]), physicalInPorts[i]);
                }
                jack_free(physicalInPorts);
            }
        }

    public:
                 jackaudio() : fClient(0), fNumInChans(0), fNumOutChans(0) {}
        virtual ~jackaudio() { stop(); }

        virtual bool init(const char* name, dsp* DSP) 
        {
            fDsp = DSP;
            if ((fClient = jack_client_open(name, JackNullOption, NULL)) == 0) {
                fprintf(stderr, "JACK server not running ?\n");
                return false;
            }
        #ifdef _OPENMP
            jack_set_process_thread(fClient, _jack_thread, this);
        #else
            jack_set_process_callback(fClient, _jack_process, this);
        #endif

            jack_set_sample_rate_callback(fClient, _jack_srate, 0);
            jack_on_shutdown(fClient, _jack_shutdown, 0);
            jack_on_info_shutdown(fClient, _jack_info_shutdown, 0);

            fNumInChans  = fDsp->getNumInputs();
            fNumOutChans = fDsp->getNumOutputs();
            
            fInput_ports = new jack_port_t*[fNumInChans];
            fOutput_ports = new jack_port_t*[fNumOutChans];
        
            for (int i = 0; i < fNumInChans; i++) {
                char buf[256];
                snprintf(buf, 256, "in_%d", i);
                fInput_ports[i] = jack_port_register(fClient, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
            }
            for (int i = 0; i < fNumOutChans; i++) {
                char buf[256];
                snprintf(buf, 256, "out_%d", i);
                fOutput_ports[i] = jack_port_register(fClient, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
            }
            fDsp->init(jack_get_sample_rate(fClient));
            return true;
        }

        virtual bool start() 
        {
            if (jack_activate(fClient)) {
                fprintf(stderr, "Cannot activate client");
                return false;
            }
            
            if (fConnections.size() > 0) {
                restore_connections();
            } else {
                default_connections();
            }
            return true;
        }

        virtual void stop() 
        {
            if (fClient) {
                save_connections();
                jack_deactivate(fClient);
                for (int i = 0; i < fNumInChans; i++) {
                    jack_port_unregister(fClient, fInput_ports[i]);
                }
                for (int i = 0; i < fNumOutChans; i++) {
                    jack_port_unregister(fClient, fOutput_ports[i]);
                }
                jack_client_close(fClient);
                fClient = 0;
                
                delete[] fInput_ports;
                delete[] fOutput_ports;
            }
        }

        // jack callbacks
        int	process(jack_nframes_t nframes) 
        {
            AVOIDDENORMALS;
            // Retrieve JACK input/outputs audio buffers
            float* fInChannel[fNumInChans];
            for (int i = 0; i < fNumInChans; i++) {
                fInChannel[i] = (float*)jack_port_get_buffer(fInput_ports[i], nframes);
            }
            float* fOutChannel[fNumOutChans];
            for (int i = 0; i < fNumOutChans; i++) {
                fOutChannel[i] = (float*)jack_port_get_buffer(fOutput_ports[i], nframes);
            }
            fDsp->compute(nframes, fInChannel, fOutChannel);
            return 0;
        }

    #ifdef _OPENMP
        void process_thread() 
        {
            jack_nframes_t nframes;
            while (1) {
                nframes = jack_cycle_wait(fClient);
                process (nframes);
                jack_cycle_signal(fClient, 0);
            }
        }
    #endif
};

//----------------------------------------------------------------------------
// Jack Callbacks
//----------------------------------------------------------------------------
static int _jack_srate(jack_nframes_t nframes, void*)
{
	fprintf(stdout, "The sample rate is now %u/sec\n", nframes);
	return 0;
}

static void _jack_shutdown(void*)
{
    fprintf(stderr, "JACK server has been closed\n");
	exit(1);
}
static void _jack_info_shutdown(jack_status_t code, const char* reason, void*)
{
    fprintf(stderr, "%s\n", reason);
	exit(1);
}

static int _jack_process(jack_nframes_t nframes, void* client)
{
	jackaudio* jackclient = (jackaudio*)client;
	return jackclient->process (nframes);
}

#ifdef _OPENMP
static void* _jack_thread(void* arg)
{
	jackaudio* jackclient = (jackaudio*)arg;
	jackclient->process_thread();
	return 0;
}
#endif

#endif
