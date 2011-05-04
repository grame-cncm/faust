
#ifndef __jack_dsp__
#define __jack_dsp__

#include <stdio.h>
#include <jack/jack.h>
#include "audio.h"
#include "dsp.h"

static int		_srate(jack_nframes_t nframes, void *);
static void		_jack_shutdown(void *);
static int		_process (jack_nframes_t nframes, void *client);
#ifdef _OPENMP
static void*	_jackthread(void* arg);
#endif

/******************************************************************************
*******************************************************************************

							JACK AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/

class jackaudio : public audio {
	dsp*			fDsp;
	jack_client_t*	fClient;
	int				fNumInChans;			// 	number of input channels
	int				fNumOutChans;			// 	number of output channels
	jack_port_t *	fInput_ports[256];		// Jack input ports
	jack_port_t *	fOutput_ports[256];		// Jack output ports
	float*			fInChannel[256];		// tables of noninterleaved input channels for FAUST
	float*			fOutChannel[256];		// tables of noninterleaved output channels for FAUST

 public:
			 jackaudio() : fClient(0), fNumInChans(0), fNumOutChans(0) {}
	virtual ~jackaudio() { stop(); }

	virtual bool init(const char*name, dsp* DSP) {
		fDsp = DSP;
		if ((fClient = jack_client_open(name, JackNullOption, NULL)) == 0) {
			fprintf(stderr, "jack server not running?\n");
			return false;
		}
	#ifdef _OPENMP
		jack_set_process_thread(fClient, _jackthread, this);
	#else
		jack_set_process_callback(fClient, _process, this);
	#endif

		jack_set_sample_rate_callback(fClient, _srate, 0);
		jack_on_shutdown(fClient, _jack_shutdown, 0);

		fNumInChans  = fDsp->getNumInputs();
		fNumOutChans = fDsp->getNumOutputs();

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

	virtual bool start() {
		if (jack_activate(fClient)) {
			fprintf(stderr, "cannot activate client");
			return false;
		}

		char** physicalInPorts = (char **)jack_get_ports(fClient, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
		char** physicalOutPorts = (char **)jack_get_ports(fClient, NULL, NULL, JackPortIsPhysical|JackPortIsOutput);
		if (physicalOutPorts != NULL) {
			for (int i = 0; i < fNumInChans && physicalOutPorts[i]; i++)
				jack_connect(fClient, physicalOutPorts[i], jack_port_name(fInput_ports[i]));
		}
		if (physicalInPorts != NULL) {
			for (int i = 0; i < fNumOutChans && physicalInPorts[i]; i++)
				jack_connect(fClient, jack_port_name(fOutput_ports[i]), physicalInPorts[i]);
		}
		return true;
	}

	virtual void stop() {
		if (fClient) {
			jack_deactivate(fClient);
			for (int i = 0; i < fNumInChans; i++)
				jack_port_unregister(fClient, fInput_ports[i]);
			for (int i = 0; i < fNumOutChans; i++)
				jack_port_unregister(fClient, fOutput_ports[i]);
			jack_client_close(fClient);
			fClient = 0;
		}
	}

	// jack callbacks
	int	process (jack_nframes_t nframes) {
		AVOIDDENORMALS;
		for (int i = 0; i < fNumInChans; i++)
			fInChannel[i] = (float *)jack_port_get_buffer(fInput_ports[i], nframes);
		for (int i = 0; i < fNumOutChans; i++)
			fOutChannel[i] = (float *)jack_port_get_buffer(fOutput_ports[i], nframes);
		fDsp->compute(nframes, fInChannel, fOutChannel);
		return 0;
	}

#ifdef _OPENMP
	void process_thread () {
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
static int _srate(jack_nframes_t nframes, void *)
{
	printf("the sample rate is now %u/sec\n", nframes);
	return 0;
}

static void _jack_shutdown(void *)
{
	exit(1);
}

static int _process(jack_nframes_t nframes, void *client)
{
	jackaudio* jackclient = (jackaudio*)client;
	return jackclient->process (nframes);
}

#ifdef _OPENMP
static void* _jackthread(void* arg)
{
	jackaudio* jackclient = (jackaudio*)arg;
	jackclient->process_thread();
	return 0;
}
#endif



#endif
