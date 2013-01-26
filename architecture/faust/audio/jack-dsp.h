
#ifndef __jack_dsp__
#define __jack_dsp__

#include <stdio.h>
#include <jack/jack.h>
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
    
        jack_port_t**	fInput_ports;       // JACK input ports
        jack_port_t**	fOutput_ports;      // JACK output ports
    
        float**			fInChannel;         // tables of noninterleaved input channels for FAUST
        float**         fOutChannel;		// tables of noninterleaved output channels for FAUST
    
        shutdown_callback fShutdown;        // Shutdown callback to be called by libjack
        void*             fShutdownArg;
    
        static int  _jack_srate(jack_nframes_t nframes, void*);
        static void _jack_shutdown(void *);
        static void _jack_info_shutdown(jack_status_t code, const char* reason, void*);
        static int  _jack_process(jack_nframes_t nframes, void* client);
    #ifdef _OPENMP
        static void* _jack_thread(void* arg);
    #endif
        void shutdown()
        {
            if (fShutdown) {
                fShutdown(fShutdownArg);
            } else {
                exit(1); // By default
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

            jack_set_sample_rate_callback(fClient, _jack_srate, this);
            jack_on_shutdown(fClient, _jack_shutdown, this);
            jack_on_info_shutdown(fClient, _jack_info_shutdown, this);

            fNumInChans  = fDsp->getNumInputs();
            fNumOutChans = fDsp->getNumOutputs();
            
            fInput_ports = new jack_port_t*[fNumInChans];
            fOutput_ports = new jack_port_t*[fNumOutChans];
            
            fInChannel = new float*[fNumInChans];
            fOutChannel = new float*[fNumOutChans];

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

            // Connect to physical input/outputs
            char** physicalOutPorts = (char**)jack_get_ports(fClient, NULL, NULL, JackPortIsPhysical|JackPortIsOutput);
            if (physicalOutPorts != NULL) {
                for (int i = 0; i < fNumInChans && physicalOutPorts[i]; i++) {
                    jack_connect(fClient, physicalOutPorts[i], jack_port_name(fInput_ports[i]));
                }
            }
            
            char** physicalInPorts = (char**)jack_get_ports(fClient, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
            if (physicalInPorts != NULL) {
                for (int i = 0; i < fNumOutChans && physicalInPorts[i]; i++) {
                    jack_connect(fClient, jack_port_name(fOutput_ports[i]), physicalInPorts[i]);
                }
            }
            return true;
        }

        virtual void stop() 
        {
            if (fClient) {
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
                
                delete[] fInChannel;
                delete[] fOutChannel;
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
            // Retrieve JACK input/output audio buffers
            for (int i = 0; i < fNumInChans; i++) {
                fInChannel[i] = (float*)jack_port_get_buffer(fInput_ports[i], nframes);
            }
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

void jackaudio::_jack_shutdown(void* arg)
{
    fprintf(stderr, "JACK server has been closed\n");
    jackaudio* audio = (jackaudio*)arg;
    audio->shutdown();
}

void jackaudio::_jack_info_shutdown(jack_status_t code, const char* reason, void* arg)
{
    fprintf(stderr, "%s\n", reason);
	jackaudio* audio = (jackaudio*)arg;
    audio->shutdown();
}

int jackaudio::_jack_process(jack_nframes_t nframes, void* client)
{
	jackaudio* audio = (jackaudio*)client;
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
