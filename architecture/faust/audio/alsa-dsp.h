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

#ifndef __alsa_dsp__
#define __alsa_dsp__

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <pwd.h>
#include <limits.h>

#include <alsa/asoundlib.h>
#include "faust/audio/audio.h"
#include "faust/audio/dsp.h"

/**
DEFAULT ALSA PARAMETERS CONTROLLED BY ENVIRONMENT VARIABLES

Some default parameters of Faust's ALSA applications are controlled by the following environment variables :

    FAUST2ALSA_DEVICE   = "hw:0"
    FAUST2ALSA_FREQUENCY= 44100
    FAUST2ALSA_BUFFER   = 512
    FAUST2ALSA_PERIODS  = 2

*/

//using namespace std;

// handle 32/64 bits int size issues

#ifdef __x86_64__

#define uint32	unsigned int
#define uint64	unsigned long int

#define int32	int
#define int64	long int

#else

#define uint32	unsigned int
#define uint64	unsigned long long int

#define int32	int
#define int64	long long int
#endif

// check 32/64 bits issues are correctly handled

#define check_error(err) if (err) { printf("%s:%d, alsa error %d : %s\n", __FILE__, __LINE__, err, snd_strerror(err)); exit(1); }
#define check_error_msg(err,msg) if (err) { fprintf(stderr, "%s:%d, %s : %s(%d)\n", __FILE__, __LINE__, msg, snd_strerror(err), err); exit(1); }
#define display_error_msg(err,msg) if (err) { fprintf(stderr, "%s:%d, %s : %s(%d)\n", __FILE__, __LINE__, msg, snd_strerror(err), err); }


/**
 * Used to set the priority and scheduling of the audi#include <sys/types.h>
       #include <pwd.h>
o thread
 */
static bool setRealtimePriority ()
{
    struct passwd *         pw;
    int                     err;
    uid_t                   uid;
    struct sched_param      param;

    uid = getuid ();
    pw = getpwnam ("root");
    setuid (pw->pw_uid);
    param.sched_priority = 50; /* 0 to 99  */
    err = sched_setscheduler(0, SCHED_RR, &param);
    setuid (uid);
    return (err != -1);
}

/******************************************************************************
*******************************************************************************

								AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/

enum { kRead = 1, kWrite = 2, kReadWrite = 3 };

/**
 * A convenient class to pass parameters to AudioInterface
 */
class AudioParam
{
  public:

	const char*		fCardName;
	unsigned int	fFrequency;
	unsigned int	fBuffering;
	unsigned int	fPeriods;

	unsigned int	fSoftInputs;
	unsigned int	fSoftOutputs;

  public :
	AudioParam() :
		fCardName("hw:0"),
		fFrequency(44100),
		fBuffering(512),
		fPeriods(2),
		fSoftInputs(2),
		fSoftOutputs(2)
	{}

	AudioParam&	cardName(const char* n)	{ fCardName = n; 		return *this; }
	AudioParam&	frequency(int f)		{ fFrequency = f; 		return *this; }
	AudioParam&	buffering(int fpb)		{ fBuffering = fpb; 	return *this; }
	AudioParam&	periods(int p)			{ fPeriods = p; 		return *this; }
	AudioParam&	inputs(int n)			{ fSoftInputs = n; 		return *this; }
	AudioParam&	outputs(int n)			{ fSoftOutputs = n; 	return *this; }
};

/**
 * An ALSA audio interface
 */
class AudioInterface : public AudioParam
{
 public :
	snd_pcm_t*				fOutputDevice ;
	snd_pcm_t*				fInputDevice ;
	snd_pcm_hw_params_t* 	fInputParams;
	snd_pcm_hw_params_t* 	fOutputParams;

	snd_pcm_format_t 		fSampleFormat;
	snd_pcm_access_t 		fSampleAccess;

	unsigned int			fCardInputs;
	unsigned int			fCardOutputs;

	unsigned int			fChanInputs;
	unsigned int			fChanOutputs;

	bool					fDuplexMode;

	// interleaved mode audiocard buffers
	void*		fInputCardBuffer;
	void*		fOutputCardBuffer;

	// non interleaved mode audiocard buffers
	void*		fInputCardChannels[256];
	void*		fOutputCardChannels[256];

	// non interleaved mod, floating point software buffers
	float*		fInputSoftChannels[256];
	float*		fOutputSoftChannels[256];

 public :

	const char*	cardName()				{ return fCardName;  	}
 	int			frequency()				{ return fFrequency; 	}
	int			buffering()				{ return fBuffering;  	}
	int			periods()				{ return fPeriods;  	}

	float**		inputSoftChannels()		{ return fInputSoftChannels;	}
	float**		outputSoftChannels()	{ return fOutputSoftChannels;	}

	bool		duplexMode()			{ return fDuplexMode; }


	AudioInterface(const AudioParam& ap = AudioParam()) : AudioParam(ap)
	{

		fInputDevice 			= 0;
		fOutputDevice 			= 0;
		fInputParams			= 0;
		fOutputParams			= 0;
	}

	/**
	 * Open the audio interface
	 */
	void open()
	{
		int 	err;

		// try to open output device, quit if fail to open output device
		err = snd_pcm_open( &fOutputDevice, fCardName, SND_PCM_STREAM_PLAYBACK, 0 ); check_error(err)

		// setup output device parameters
		err = snd_pcm_hw_params_malloc	( &fOutputParams ); 		check_error(err)
		setAudioParams(fOutputDevice, fOutputParams);

		fCardOutputs = fSoftOutputs;
		snd_pcm_hw_params_set_channels_near(fOutputDevice, fOutputParams, &fCardOutputs);
		err = snd_pcm_hw_params (fOutputDevice, fOutputParams );	check_error (err);

		// allocate alsa output buffers
		if (fSampleAccess == SND_PCM_ACCESS_RW_INTERLEAVED) {
			fOutputCardBuffer = calloc(interleavedBufferSize(fOutputParams), 1);
		} else {
			for (unsigned int i = 0; i < fCardOutputs; i++) {
				fOutputCardChannels[i] = calloc(noninterleavedBufferSize(fOutputParams), 1);
			}

		}

		// check for duplex mode (if we need and have an input device)
		if (fSoftInputs == 0) {
			fDuplexMode = false;
			fCardInputs = 0;
		} else {
			// try to open input device
			err = snd_pcm_open( &fInputDevice,  fCardName, SND_PCM_STREAM_CAPTURE, 0 );
			if (err == 0) {
				fDuplexMode = true;
			} else {
				printf("Warning : no input device");
				fDuplexMode = false;
				fCardInputs = 0;
			}
		}


		if (fDuplexMode) {

			// we have and need an input device
			// set the number of physical inputs close to what we need
			err = snd_pcm_hw_params_malloc	( &fInputParams ); 	check_error(err);
			setAudioParams(fInputDevice, fInputParams);
			fCardInputs 	= fSoftInputs;
			snd_pcm_hw_params_set_channels_near(fInputDevice, fInputParams, &fCardInputs);
			err = snd_pcm_hw_params (fInputDevice,  fInputParams );	 	check_error (err);

			// allocation of alsa buffers
			if (fSampleAccess == SND_PCM_ACCESS_RW_INTERLEAVED) {
				fInputCardBuffer = calloc(interleavedBufferSize(fInputParams), 1);
			} else {
				for (unsigned int i = 0; i < fCardInputs; i++) {
					fInputCardChannels[i] = calloc(noninterleavedBufferSize(fInputParams), 1);
				}
			}

		}

		printf("inputs : %u, outputs : %u\n", fCardInputs, fCardOutputs);

		// allocation of floating point buffers needed by the dsp code

		fChanInputs = max(fSoftInputs, fCardInputs);		assert (fChanInputs < 256);
		fChanOutputs = max(fSoftOutputs, fCardOutputs);		assert (fChanOutputs < 256);

		for (unsigned int i = 0; i < fChanInputs; i++) {
			fInputSoftChannels[i] = (float*) calloc (fBuffering, sizeof(float));
			for (unsigned int j = 0; j < fBuffering; j++) {
				fInputSoftChannels[i][j] = 0.0;
			}
		}

		for (unsigned int i = 0; i < fChanOutputs; i++) {
			fOutputSoftChannels[i] = (float*) calloc (fBuffering, sizeof(float));
			for (unsigned int j = 0; j < fBuffering; j++) {
				fOutputSoftChannels[i][j] = 0.0;
			}
		}
	}

	void setAudioParams(snd_pcm_t* stream, snd_pcm_hw_params_t* params)
	{
		int	err;

		// set params record with initial values
		err = snd_pcm_hw_params_any	( stream, params );
		check_error_msg(err, "unable to init parameters")

		// set alsa access mode (and fSampleAccess field) either to non interleaved or interleaved

		err = snd_pcm_hw_params_set_access (stream, params, SND_PCM_ACCESS_RW_NONINTERLEAVED );
		if (err) {
			err = snd_pcm_hw_params_set_access (stream, params, SND_PCM_ACCESS_RW_INTERLEAVED );
			check_error_msg(err, "unable to set access mode neither to non-interleaved or to interleaved");
		}
		snd_pcm_hw_params_get_access(params, &fSampleAccess);


		// search for 32-bits or 16-bits format
		err = snd_pcm_hw_params_set_format (stream, params, SND_PCM_FORMAT_S32);
		if (err) {
			err = snd_pcm_hw_params_set_format (stream, params, SND_PCM_FORMAT_S16);
		 	check_error_msg(err, "unable to set format to either 32-bits or 16-bits");
		}
		snd_pcm_hw_params_get_format(params, &fSampleFormat);
		// set sample frequency
		snd_pcm_hw_params_set_rate_near (stream, params, &fFrequency, 0);

		// set period and period size (buffering)
		err = snd_pcm_hw_params_set_period_size	(stream, params, fBuffering, 0);
		check_error_msg(err, "period size not available");

		err = snd_pcm_hw_params_set_periods (stream, params, fPeriods, 0);
		check_error_msg(err, "number of periods not available");
	}

	ssize_t interleavedBufferSize (snd_pcm_hw_params_t* params)
	{
		_snd_pcm_format 	format;  	snd_pcm_hw_params_get_format(params, &format);
		snd_pcm_uframes_t 	psize;		snd_pcm_hw_params_get_period_size(params, &psize, NULL);
		unsigned int 		channels; 	snd_pcm_hw_params_get_channels(params, &channels);
		ssize_t bsize = snd_pcm_format_size (format, psize * channels);
		return bsize;
	}

	ssize_t noninterleavedBufferSize (snd_pcm_hw_params_t* params)
	{
		_snd_pcm_format 	format;  	snd_pcm_hw_params_get_format(params, &format);
		snd_pcm_uframes_t 	psize;		snd_pcm_hw_params_get_period_size(params, &psize, NULL);
		ssize_t bsize = snd_pcm_format_size (format, psize);
		return bsize;
	}

	void close()
	{}

	/**
	 * Read audio samples from the audio card. Convert samples to floats and take
	 * care of interleaved buffers
	 */
	void read()
	{
        if (fSampleAccess == SND_PCM_ACCESS_RW_INTERLEAVED) {

			int count = snd_pcm_readi(fInputDevice, fInputCardBuffer, fBuffering);
			if (count<0) {
				 //display_error_msg(count, "reading samples");
				 int err = snd_pcm_prepare(fInputDevice);
				 //check_error_msg(err, "preparing input stream");
			}

			if (fSampleFormat == SND_PCM_FORMAT_S16) {

				short* 	buffer16b = (short*) fInputCardBuffer;
				for (unsigned int s = 0; s < fBuffering; s++) {
					for (unsigned int c = 0; c < fCardInputs; c++) {
						fInputSoftChannels[c][s] = float(buffer16b[c + s*fCardInputs])*(1.0/float(SHRT_MAX));
					}
				}

			} else if (fSampleFormat == SND_PCM_FORMAT_S32) {

				int32* 	buffer32b = (int32*) fInputCardBuffer;
				for (unsigned int s = 0; s < fBuffering; s++) {
					for (unsigned int c = 0; c < fCardInputs; c++) {
						fInputSoftChannels[c][s] = float(buffer32b[c + s*fCardInputs])*(1.0/float(INT_MAX));
					}
				}
			} else {

				printf("unrecognized input sample format : %u\n", fSampleFormat);
				exit(1);
			}

		} else if (fSampleAccess == SND_PCM_ACCESS_RW_NONINTERLEAVED) {

			int count = snd_pcm_readn(fInputDevice, fInputCardChannels, fBuffering);
			if (count<0) {
				 //display_error_msg(count, "reading samples");
				 int err = snd_pcm_prepare(fInputDevice);
				 //check_error_msg(err, "preparing input stream");
			}

			if (fSampleFormat == SND_PCM_FORMAT_S16) {

				for (unsigned int c = 0; c < fCardInputs; c++) {
					short* 	chan16b = (short*) fInputCardChannels[c];
					for (unsigned int s = 0; s < fBuffering; s++) {
						fInputSoftChannels[c][s] = float(chan16b[s])*(1.0/float(SHRT_MAX));
					}
				}

			} else if (fSampleFormat == SND_PCM_FORMAT_S32) {

				for (unsigned int c = 0; c < fCardInputs; c++) {
					int32* 	chan32b = (int32*) fInputCardChannels[c];
					for (unsigned int s = 0; s < fBuffering; s++) {
						fInputSoftChannels[c][s] = float(chan32b[s])*(1.0/float(INT_MAX));
					}
				}
			} else {

				printf("unrecognized input sample format : %u\n", fSampleFormat);
				exit(1);
			}

		} else {
			check_error_msg(-10000, "unknow access mode");
		}
    }

	/**
	 * write the output soft channels to the audio card. Convert sample
	 * format and interleaves buffers when needed
	 */
	void write()
	{
		recovery :

		if (fSampleAccess == SND_PCM_ACCESS_RW_INTERLEAVED) {

			if (fSampleFormat == SND_PCM_FORMAT_S16) {

				short* buffer16b = (short*) fOutputCardBuffer;
				for (unsigned int f = 0; f < fBuffering; f++) {
					for (unsigned int c = 0; c < fCardOutputs; c++) {
						float x = fOutputSoftChannels[c][f];
						buffer16b[c + f*fCardOutputs] = short( max(min(x,1.0f),-1.0f) * float(SHRT_MAX) ) ;
					}
				}

			} else if (fSampleFormat == SND_PCM_FORMAT_S32)  {

				int32* buffer32b = (int32*) fOutputCardBuffer;
				for (unsigned int f = 0; f < fBuffering; f++) {
					for (unsigned int c = 0; c < fCardOutputs; c++) {
						float x = fOutputSoftChannels[c][f];
						buffer32b[c + f*fCardOutputs] = int( max(min(x,1.0f),-1.0f) * float(INT_MAX) ) ;
					}
				}
			} else {

				printf("unrecognized output sample format : %u\n", fSampleFormat);
				exit(1);
			}

			int count = snd_pcm_writei(fOutputDevice, fOutputCardBuffer, fBuffering);
			if (count<0) {
				//display_error_msg(count, "w3");
				int err = snd_pcm_prepare(fOutputDevice);
				//check_error_msg(err, "preparing output stream");
				goto recovery;
			}


		} else if (fSampleAccess == SND_PCM_ACCESS_RW_NONINTERLEAVED) {

			if (fSampleFormat == SND_PCM_FORMAT_S16) {

				for (unsigned int c = 0; c < fCardOutputs; c++) {
					short* chan16b = (short*) fOutputCardChannels[c];
					for (unsigned int f = 0; f < fBuffering; f++) {
						float x = fOutputSoftChannels[c][f];
						chan16b[f] = short( max(min(x,1.0f),-1.0f) * float(SHRT_MAX) ) ;
					}
				}

			} else if (fSampleFormat == SND_PCM_FORMAT_S32) {

				for (unsigned int c = 0; c < fCardOutputs; c++) {
					int32* chan32b = (int32*) fOutputCardChannels[c];
					for (unsigned int f = 0; f < fBuffering; f++) {
						float x = fOutputSoftChannels[c][f];
						chan32b[f] = int( max(min(x,1.0f),-1.0f) * float(INT_MAX) ) ;
					}
				}

			} else {

				printf("unrecognized output sample format : %u\n", fSampleFormat);
				exit(1);
			}

			int count = snd_pcm_writen(fOutputDevice, fOutputCardChannels, fBuffering);
			if (count<0) {
				//display_error_msg(count, "w3");
				int err = snd_pcm_prepare(fOutputDevice);
				//check_error_msg(err, "preparing output stream");
				goto recovery;
			}

		} else {
			check_error_msg(-10000, "unknow access mode");
		}
	}

	/**
	 *  print short information on the audio device
	 */
	void shortinfo()
	{
		int						err;
		snd_ctl_card_info_t*	card_info;
    	snd_ctl_t*				ctl_handle;
		err = snd_ctl_open (&ctl_handle, fCardName, 0);		check_error(err);
		snd_ctl_card_info_alloca (&card_info);
		err = snd_ctl_card_info(ctl_handle, card_info);		check_error(err);
		printf("%s|%d|%d|%d|%d|%s\n",
				snd_ctl_card_info_get_driver(card_info),
				fCardInputs, fCardOutputs,
				fFrequency, fBuffering,
				snd_pcm_format_name((_snd_pcm_format)fSampleFormat));
	}

	/**
	 *  print more detailled information on the audio device
	 */
	void longinfo()
	{
		int						err;
		snd_ctl_card_info_t*	card_info;
    	snd_ctl_t*				ctl_handle;

		printf("Audio Interface Description :\n");
		printf("Sampling Frequency : %d, Sample Format : %s, buffering : %d\n",
				fFrequency, snd_pcm_format_name((_snd_pcm_format)fSampleFormat), fBuffering);
		printf("Software inputs : %2d, Software outputs : %2d\n", fSoftInputs, fSoftOutputs);
		printf("Hardware inputs : %2d, Hardware outputs : %2d\n", fCardInputs, fCardOutputs);
		printf("Channel inputs  : %2d, Channel outputs  : %2d\n", fChanInputs, fChanOutputs);

		// affichage des infos de la carte
		err = snd_ctl_open (&ctl_handle, fCardName, 0);		check_error(err);
		snd_ctl_card_info_alloca (&card_info);
		err = snd_ctl_card_info(ctl_handle, card_info);		check_error(err);
		printCardInfo(card_info);

		// affichage des infos liees aux streams d'entree-sortie
		if (fSoftInputs > 0)	printHWParams(fInputParams);
		if (fSoftOutputs > 0)	printHWParams(fOutputParams);
	}

	void printCardInfo(snd_ctl_card_info_t*	ci)
	{
		printf("Card info (address : %p)\n", ci);
		printf("\tID         = %s\n", snd_ctl_card_info_get_id(ci));
		printf("\tDriver     = %s\n", snd_ctl_card_info_get_driver(ci));
		printf("\tName       = %s\n", snd_ctl_card_info_get_name(ci));
		printf("\tLongName   = %s\n", snd_ctl_card_info_get_longname(ci));
		printf("\tMixerName  = %s\n", snd_ctl_card_info_get_mixername(ci));
		printf("\tComponents = %s\n", snd_ctl_card_info_get_components(ci));
		printf("--------------\n");
	}

	void printHWParams( snd_pcm_hw_params_t* params )
	{
		printf("HW Params info (address : %p)\n", params);
#if 0
		printf("\tChannels    = %d\n", snd_pcm_hw_params_get_channels(params));
		printf("\tFormat      = %s\n", snd_pcm_format_name((_snd_pcm_format)snd_pcm_hw_params_get_format(params)));
		printf("\tAccess      = %s\n", snd_pcm_access_name((_snd_pcm_access)snd_pcm_hw_params_get_access(params)));
		printf("\tRate        = %d\n", snd_pcm_hw_params_get_rate(params, NULL));
		printf("\tPeriods     = %d\n", snd_pcm_hw_params_get_periods(params, NULL));
		printf("\tPeriod size = %d\n", (int)snd_pcm_hw_params_get_period_size(params, NULL));
		printf("\tPeriod time = %d\n", snd_pcm_hw_params_get_period_time(params, NULL));
		printf("\tBuffer size = %d\n", (int)snd_pcm_hw_params_get_buffer_size(params));
		printf("\tBuffer time = %d\n", snd_pcm_hw_params_get_buffer_time(params, NULL));
#endif
		printf("--------------\n");
	}

};

// lopt : Scan Command Line long int Arguments
long lopt(int argc, char *argv[], const char* longname, const char* shortname, long def)
{
	for (int i=2; i<argc; i++)
		if ( strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0 )
			return atoi(argv[i]);
	return def;
}

// sopt : Scan Command Line string Arguments
const char* sopt(int argc, char *argv[], const char* longname, const char* shortname, const char* def)
{
	for (int i=2; i<argc; i++)
		if ( strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0 )
			return argv[i];
	return def;
}

// fopt : Scan Command Line flag option (without argument), return true if the flag
bool fopt(int argc, char *argv[], const char* longname, const char* shortname)
{
	for (int i=1; i<argc; i++)
		if ( strcmp(argv[i], shortname) == 0 || strcmp(argv[i], longname) == 0 )
			return true;
	return false;
}

/**
 * Return the value of an environment variable or defval if undefined.
 */
static int getDefaultEnv(const char* name, int defval)
{
    const char* str = getenv(name);
    if (str) {
        return atoi(str);
    } else {
        return defval;
    }
}

/**
 * Return the value of an environment variable or defval if undefined.
 */
static const char* getDefaultEnv(const char* name, const char* defval)
{
    const char* str = getenv(name);
    if (str) {
        return str;
    } else {
        return defval;
    }
}

/******************************************************************************
*******************************************************************************

							   ALSA audio interface

*******************************************************************************
*******************************************************************************/
void* __run(void* ptr);

class alsaaudio : public audio
{
	AudioInterface*	fAudio;
	dsp* 			fDSP;
	pthread_t 		fAudioThread;
	bool 			fRunning;

 public:

	 alsaaudio(int argc, char *argv[], dsp* DSP) : fAudio(0), fDSP(DSP), fRunning(false) {
			fAudio = new AudioInterface (
				AudioParam().cardName( sopt(argc, argv, "--device", "-d",  	getDefaultEnv("FAUST2ALSA_DEVICE", "hw:0")  ) )
				.frequency( lopt(argc, argv, "--frequency", "-f", 			getDefaultEnv("FAUST2ALSA_FREQUENCY",44100) ) )
				.buffering( lopt(argc, argv, "--buffer", "-b",    			getDefaultEnv("FAUST2ALSA_BUFFER",512)     ) )
				.periods( lopt(argc, argv, "--periods", "-p",     			getDefaultEnv("FAUST2ALSA_PERIODS",2)       ) )
				.inputs(DSP->getNumInputs())
				.outputs(DSP->getNumOutputs()));
		}

	virtual ~alsaaudio() { stop(); delete fAudio; }

	virtual bool init(const char */*name*/, dsp* DSP) {
		AVOIDDENORMALS;
		fAudio->open();
	    DSP->init(fAudio->frequency());
 		return true;
	}

	virtual bool start() {
		fRunning = true;
		if (pthread_create( &fAudioThread, 0, __run, this))
			fRunning = false;
		return fRunning;
	}

	virtual void stop() {
		if (fRunning) {
			fRunning = false;
			pthread_join (fAudioThread, 0);
		}
	}

	virtual void run() {
		bool rt = setRealtimePriority();
		printf(rt ? "RT : ":"NRT: "); fAudio->shortinfo();
		if (fAudio->duplexMode()) {

			fAudio->write();
			fAudio->write();
			while(fRunning) {
				fAudio->read();
				fDSP->compute(fAudio->buffering(), fAudio->inputSoftChannels(), fAudio->outputSoftChannels());
				fAudio->write();
			}

		} else {

			fAudio->write();
			while(fRunning) {
				fDSP->compute(fAudio->buffering(), fAudio->inputSoftChannels(), fAudio->outputSoftChannels());
				fAudio->write();
			}
		}
	}

};

void* __run (void* ptr)
{
	alsaaudio * alsa = (alsaaudio*)ptr;
	alsa->run();
	return 0;
}

#endif

/********************END ARCHITECTURE SECTION (part 2/2)****************/

