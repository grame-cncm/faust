
#ifndef __jack_dsp__
#define __jack_dsp__

#include <stdio.h>
#include <cstdlib>
#include <list>
#include <string.h>
#include <jack/jack.h>
#ifdef JACK_IOS
#include <jack/custom.h>
#endif
#include "faust/audio/audio.h"
#include "faust/audio/dsp.h"

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
    
        jack_port_t**	fInputPorts;       // JACK input ports
        jack_port_t**	fOutputPorts;      // JACK output ports
    
        shutdown_callback fShutdown;        // Shutdown callback to be called by libjack
        void*           fShutdownArg;
        void*           fIconData;
        int             fIconSize;
        bool            fAutoConnect;
        
        std::list<std::pair<std::string, std::string> > fConnections;		// Connections list
    
        static int  _jack_srate(jack_nframes_t nframes, void* arg);
        static void _jack_shutdown(void* arg);
        static void _jack_info_shutdown(jack_status_t code, const char* reason, void* arg);
        static int  _jack_process(jack_nframes_t nframes, void* arg);
        static int  _jack_buffersize(jack_nframes_t nframes, void* arg);
    #ifdef _OPENMP
        static void* _jack_thread(void* arg);
    #endif
        void shutdown(const char* message)
        {
            if (fShutdown) {
                fShutdown(message, fShutdownArg);
            } else {
                exit(1); // By default
            }
        }
        
        // Save client connections
        void save_connections()
        {
            fConnections.clear();
            
             for (int i = 0; i < fNumInChans; i++) {
                const char** connected_port = jack_port_get_all_connections(fClient, fInputPorts[i]);
                if (connected_port != NULL) {
                    for (int port = 0; connected_port[port]; port++) {
                        fConnections.push_back(std::make_pair(connected_port[port], jack_port_name(fInputPorts[i])));
                        printf("INPUT %s ==> %s\n", connected_port[port], jack_port_name(fInputPorts[i]));
                    }
                    jack_free(connected_port);
                }
            }
       
            for (int i = 0; i < fNumOutChans; i++) {
                const char** connected_port = jack_port_get_all_connections(fClient, fOutputPorts[i]);
                if (connected_port != NULL) {
                    for (int port = 0; connected_port[port]; port++) {
                        fConnections.push_back(std::make_pair(jack_port_name(fOutputPorts[i]), connected_port[port]));
                        printf("OUTPUT %s ==> %s\n", jack_port_name(fOutputPorts[i]), connected_port[port]);
                    }
                    jack_free(connected_port);
                }
            }
        }

        // Load previous client connections
        void load_connections()
        {
            std::list<std::pair<std::string, std::string> >::const_iterator it;
            for (it = fConnections.begin(); it != fConnections.end(); it++) {
                std::pair<std::string, std::string> connection = *it;
                jack_connect(fClient, connection.first.c_str(), connection.second.c_str());
            }
        }
        
        // Connect to physical inputs/outputs
        void default_connections()
        {
            char** physicalOutPorts = (char**)jack_get_ports(fClient, NULL, JACK_DEFAULT_AUDIO_TYPE, JackPortIsPhysical|JackPortIsOutput);
            if (physicalOutPorts != NULL) {
                for (int i = 0; i < fNumInChans && physicalOutPorts[i]; i++) {
                    jack_connect(fClient, physicalOutPorts[i], jack_port_name(fInputPorts[i]));
                }
                jack_free(physicalOutPorts);
            }
            
            char** physicalInPorts = (char**)jack_get_ports(fClient, NULL, JACK_DEFAULT_AUDIO_TYPE, JackPortIsPhysical|JackPortIsInput);
            if (physicalInPorts != NULL) {
                for (int i = 0; i < fNumOutChans && physicalInPorts[i]; i++) {
                    jack_connect(fClient, jack_port_name(fOutputPorts[i]), physicalInPorts[i]);
                }
                jack_free(physicalInPorts);
            }
        }

    public:
        jackaudio(const void* icon_data = 0, size_t icon_size = 0, bool auto_connect = true) 
            : fDsp(0), fClient(0), fNumInChans(0), fNumOutChans(0), 
            fInputPorts(0), fOutputPorts(0), 
            fShutdown(0), fShutdownArg(0),
            fAutoConnect(auto_connect)
        {
            if (icon_data) {
                fIconData = malloc(icon_size);
                fIconSize = icon_size;
                memcpy(fIconData, icon_data, icon_size);
            } else {
                fIconData = NULL;
                fIconSize = 0;
            }
        }
        virtual ~jackaudio() 
        { 
            stop(); 
            if (fIconData) {
                free(fIconData);
            }
        }
        
        jack_client_t* getClient() { return fClient; }

        virtual bool init(const char* name, dsp* DSP) 
        {
            fDsp = DSP;
            if ((fClient = jack_client_open(name, JackNullOption, NULL)) == 0) {
                fprintf(stderr, "JACK server not running ?\n");
                return false;
            }
        #ifdef JACK_IOS
            jack_custom_publish_data(fClient, "icon.png", fIconData, fIconSize);
        #endif
            
        #ifdef _OPENMP
            jack_set_process_thread(fClient, _jack_thread, this);
        #else
            jack_set_process_callback(fClient, _jack_process, this);
        #endif

            jack_set_sample_rate_callback(fClient, _jack_srate, this);
            jack_set_buffer_size_callback(fClient, _jack_buffersize, this);
            jack_on_info_shutdown(fClient, _jack_info_shutdown, this);

            fNumInChans  = fDsp->getNumInputs();
            fNumOutChans = fDsp->getNumOutputs();
            
            fInputPorts = new jack_port_t*[fNumInChans];
            fOutputPorts = new jack_port_t*[fNumOutChans];
        
            for (int i = 0; i < fNumInChans; i++) {
                char buf[256];
                snprintf(buf, 256, "in_%d", i);
                fInputPorts[i] = jack_port_register(fClient, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
            }
            for (int i = 0; i < fNumOutChans; i++) {
                char buf[256];
                snprintf(buf, 256, "out_%d", i);
                fOutputPorts[i] = jack_port_register(fClient, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
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
                load_connections();
            } else if (fAutoConnect) {
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
                    jack_port_unregister(fClient, fInputPorts[i]);
                }
                for (int i = 0; i < fNumOutChans; i++) {
                    jack_port_unregister(fClient, fOutputPorts[i]);
                }
                jack_client_close(fClient);
                fClient = 0;
                
                delete[] fInputPorts;
                delete[] fOutputPorts;
            }
        }
    
        virtual void shutdown(shutdown_callback cb, void* arg)
        {
            fShutdown = cb;
            fShutdownArg = arg;
        }

        // jack callbacks
        int	process(jack_nframes_t nframes) 
        {
            AVOIDDENORMALS;
            // Retrieve JACK inputs/output audio buffers
            float* fInChannel[fNumInChans];
            for (int i = 0; i < fNumInChans; i++) {
                fInChannel[i] = (float*)jack_port_get_buffer(fInputPorts[i], nframes);
            }
            float* fOutChannel[fNumOutChans];
            for (int i = 0; i < fNumOutChans; i++) {
                fOutChannel[i] = (float*)jack_port_get_buffer(fOutputPorts[i], nframes);
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
                process(nframes);
                jack_cycle_signal(fClient, 0);
            }
        }
    #endif
};

//----------------------------------------------------------------------------
// Jack Callbacks
//----------------------------------------------------------------------------

int jackaudio::_jack_srate(jack_nframes_t nframes, void* arg)
{
  	fprintf(stdout, "The sample rate is now %u/sec\n", nframes);
	return 0;
}

int jackaudio::_jack_buffersize(jack_nframes_t nframes, void* arg)
{
  	fprintf(stdout, "The buffer size is now %u/sec\n", nframes);
	return 0;
}

void jackaudio::_jack_info_shutdown(jack_status_t code, const char* reason, void* arg)
{
    fprintf(stderr, "%s\n", reason);
	jackaudio* audio = (jackaudio*)arg;
    audio->shutdown(reason);
}

int jackaudio::_jack_process(jack_nframes_t nframes, void* arg)
{
	jackaudio* audio = (jackaudio*)arg;
	return audio->process(nframes);
}

#ifdef _OPENMP
void* jackaudio::_jack_thread(void* arg)
{
	jackaudio* audio = (jackaudio*)arg;
	audio->process_thread();
	return 0;
}
#endif

#endif
