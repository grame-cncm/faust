/************************** BEGIN opensles-android-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

/*
* This is an interface for OpenSL ES to make it easier to use with Android
* devices.  
*/

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <android/log.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct threadLock_ {
	pthread_mutex_t m;
	pthread_cond_t c;
	unsigned char s;
} threadLock;

typedef struct opensl_stream {

	// engine interfaces
	SLObjectItf engineObject;
	SLEngineItf engineEngine;

	// output mix interfaces
	SLObjectItf outputMixObject;

	// buffer queue player interfaces
	SLObjectItf bqPlayerObject;
	SLPlayItf bqPlayerPlay;
	SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
	SLEffectSendItf bqPlayerEffectSend;

	// recorder interfaces
	SLObjectItf recorderObject;
	SLRecordItf recorderRecord;
	SLAndroidSimpleBufferQueueItf recorderBufferQueue;

	// buffer indexes
	int currentInputIndex;
	int currentOutputIndex;

	// current buffer half (0, 1)
	int currentOutputBuffer;
	int currentInputBuffer;

	// buffers
	short *outputBuffer[2];
	short *inputBuffer[2];

	// size of buffers
	int outBufSamples;
	int inBufSamples;

	// locks
	void* inlock;
	void* outlock;

	double time;
	int inchannels;
	int outchannels;
	int sr;

} OPENSL_STREAM;

#define CONV16BIT 32767.f
#define CONVMYFLT (1.f/32767.f)

static void* createThreadLock(void);
static int waitThreadLock(void *lock);
static void notifyThreadLock(void *lock);
static void destroyThreadLock(void *lock);
static void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context);
static void bqRecorderCallback(SLAndroidSimpleBufferQueueItf bq, void *context);

// creates the OpenSL ES audio engine
static SLresult openSLCreateEngine(OPENSL_STREAM *p) {
	SLresult result;
	// create engine
	result = slCreateEngine(&(p->engineObject), 0, NULL, 0, NULL, NULL);
	if (result != SL_RESULT_SUCCESS)
		goto engine_end;

	// realize the engine
	result = (*p->engineObject)->Realize(p->engineObject, SL_BOOLEAN_FALSE);
	if (result != SL_RESULT_SUCCESS)
		goto engine_end;

	// get the engine interface, which is needed in order to create other objects
	result = (*p->engineObject)->GetInterface(p->engineObject, SL_IID_ENGINE,
			&(p->engineEngine));
	if (result != SL_RESULT_SUCCESS)
		goto engine_end;

	engine_end: return result;
}

// opens the OpenSL ES device for output
static SLresult openSLPlayOpen(OPENSL_STREAM *p) {
	SLresult result;
	SLuint32 sr = p->sr;
	SLuint32 channels = p->outchannels;

	if (channels) {
		// configure audio source
		SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {
				SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };

		switch (sr) {

		case 8000:
			sr = SL_SAMPLINGRATE_8;
			break;
		case 11025:
			sr = SL_SAMPLINGRATE_11_025;
			break;
		case 16000:
			sr = SL_SAMPLINGRATE_16;
			break;
		case 22050:
			sr = SL_SAMPLINGRATE_22_05;
			break;
		case 24000:
			sr = SL_SAMPLINGRATE_24;
			break;
		case 32000:
			sr = SL_SAMPLINGRATE_32;
			break;
		case 44100:
			sr = SL_SAMPLINGRATE_44_1;
			break;
		case 48000:
			sr = SL_SAMPLINGRATE_48;
			break;
		case 64000:
			sr = SL_SAMPLINGRATE_64;
			break;
		case 88200:
			sr = SL_SAMPLINGRATE_88_2;
			break;
		case 96000:
			sr = SL_SAMPLINGRATE_96;
			break;
		case 192000:
			sr = SL_SAMPLINGRATE_192;
			break;
		default:
			return -1;
		}

		const SLInterfaceID ids[] = { SL_IID_VOLUME };
		const SLboolean req[] = { SL_BOOLEAN_FALSE };
		result = (*p->engineEngine)->CreateOutputMix(p->engineEngine,
				&(p->outputMixObject), 1, ids, req);
		//if(result != SL_RESULT_SUCCESS) goto end_openaudio;

		// realize the output mix
		result = (*p->outputMixObject)->Realize(p->outputMixObject,
				SL_BOOLEAN_FALSE);

		int speakers;
		if (channels > 1)
			speakers = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
		else
			speakers = SL_SPEAKER_FRONT_CENTER;
		SLDataFormat_PCM format_pcm = { SL_DATAFORMAT_PCM, channels, sr,
				SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
				speakers, SL_BYTEORDER_LITTLEENDIAN };

		SLDataSource audioSrc = { &loc_bufq, &format_pcm };

		// configure audio sink
		SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX,
				p->outputMixObject };
		SLDataSink audioSnk = { &loc_outmix, NULL };

		// create audio player
		const SLInterfaceID ids1[] = { SL_IID_ANDROIDSIMPLEBUFFERQUEUE };
		const SLboolean req1[] = { SL_BOOLEAN_TRUE };
		result = (*p->engineEngine)->CreateAudioPlayer(p->engineEngine,
				&(p->bqPlayerObject), &audioSrc, &audioSnk, 1, ids1, req1);
		if (result != SL_RESULT_SUCCESS)
			goto end_openaudio;

		// realize the player
		result = (*p->bqPlayerObject)->Realize(p->bqPlayerObject,
				SL_BOOLEAN_FALSE);
		if (result != SL_RESULT_SUCCESS)
			goto end_openaudio;

		// get the play interface
		result = (*p->bqPlayerObject)->GetInterface(p->bqPlayerObject,
				SL_IID_PLAY, &(p->bqPlayerPlay));
		if (result != SL_RESULT_SUCCESS)
			goto end_openaudio;

		// get the buffer queue interface
		result = (*p->bqPlayerObject)->GetInterface(p->bqPlayerObject,
				SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &(p->bqPlayerBufferQueue));
		if (result != SL_RESULT_SUCCESS)
			goto end_openaudio;

		// register callback on the buffer queue
		result = (*p->bqPlayerBufferQueue)->RegisterCallback(
				p->bqPlayerBufferQueue, bqPlayerCallback, p);
		if (result != SL_RESULT_SUCCESS)
			goto end_openaudio;

		// set the player's state to playing
		result = (*p->bqPlayerPlay)->SetPlayState(p->bqPlayerPlay,
				SL_PLAYSTATE_PLAYING);

		end_openaudio: return result;
	}
	return SL_RESULT_SUCCESS;
}

// Open the OpenSL ES device for input
static SLresult openSLRecOpen(OPENSL_STREAM *p) {

	SLresult result;
	SLuint32 sr = p->sr;
	SLuint32 channels = p->inchannels;

	if (channels) {

		switch (sr) {

		case 8000:
			sr = SL_SAMPLINGRATE_8;
			break;
		case 11025:
			sr = SL_SAMPLINGRATE_11_025;
			break;
		case 16000:
			sr = SL_SAMPLINGRATE_16;
			break;
		case 22050:
			sr = SL_SAMPLINGRATE_22_05;
			break;
		case 24000:
			sr = SL_SAMPLINGRATE_24;
			break;
		case 32000:
			sr = SL_SAMPLINGRATE_32;
			break;
		case 44100:
			sr = SL_SAMPLINGRATE_44_1;
			break;
		case 48000:
			sr = SL_SAMPLINGRATE_48;
			break;
		case 64000:
			sr = SL_SAMPLINGRATE_64;
			break;
		case 88200:
			sr = SL_SAMPLINGRATE_88_2;
			break;
		case 96000:
			sr = SL_SAMPLINGRATE_96;
			break;
		case 192000:
			sr = SL_SAMPLINGRATE_192;
			break;
		default:
			return -1;
		}

		// configure audio source
		SLDataLocator_IODevice loc_dev = { SL_DATALOCATOR_IODEVICE,
				SL_IODEVICE_AUDIOINPUT, SL_DEFAULTDEVICEID_AUDIOINPUT, NULL };
		SLDataSource audioSrc = { &loc_dev, NULL };

		// configure audio sink
		int speakers;
		if (channels > 1)
			speakers = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
		else
			speakers = SL_SPEAKER_FRONT_CENTER;
		SLDataLocator_AndroidSimpleBufferQueue loc_bq = {
				SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };
		SLDataFormat_PCM format_pcm = { SL_DATAFORMAT_PCM, channels, sr,
				SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
				speakers, SL_BYTEORDER_LITTLEENDIAN };
		SLDataSink audioSnk = { &loc_bq, &format_pcm };

		// create audio recorder
		// (requires the RECORD_AUDIO permission)
		const SLInterfaceID id[1] = { SL_IID_ANDROIDSIMPLEBUFFERQUEUE };
		const SLboolean req[1] = { SL_BOOLEAN_TRUE };
		result = (*p->engineEngine)->CreateAudioRecorder(p->engineEngine,
				&(p->recorderObject), &audioSrc, &audioSnk, 1, id, req);
		if (SL_RESULT_SUCCESS != result)
			goto end_recopen;

		// realize the audio recorder
		result = (*p->recorderObject)->Realize(p->recorderObject,
				SL_BOOLEAN_FALSE);
		if (SL_RESULT_SUCCESS != result)
			goto end_recopen;

		// get the record interface
		result = (*p->recorderObject)->GetInterface(p->recorderObject,
				SL_IID_RECORD, &(p->recorderRecord));
		if (SL_RESULT_SUCCESS != result)
			goto end_recopen;

		// get the buffer queue interface
		result = (*p->recorderObject)->GetInterface(p->recorderObject,
				SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &(p->recorderBufferQueue));
		if (SL_RESULT_SUCCESS != result)
			goto end_recopen;

		// register callback on the buffer queue
		result = (*p->recorderBufferQueue)->RegisterCallback(
				p->recorderBufferQueue, bqRecorderCallback, p);
		if (SL_RESULT_SUCCESS != result)
			goto end_recopen;
		result = (*p->recorderRecord)->SetRecordState(p->recorderRecord,
				SL_RECORDSTATE_RECORDING);

		end_recopen: return result;
	} else
		return SL_RESULT_SUCCESS;

}

// close the OpenSL IO and destroy the audio engine
static void openSLDestroyEngine(OPENSL_STREAM *p) {

	// destroy buffer queue audio player object, and invalidate all associated interfaces
	if (p->bqPlayerObject != NULL) {
		(*p->bqPlayerObject)->Destroy(p->bqPlayerObject);
		p->bqPlayerObject = NULL;
		p->bqPlayerPlay = NULL;
		p->bqPlayerBufferQueue = NULL;
		p->bqPlayerEffectSend = NULL;
	}

	// destroy audio recorder object, and invalidate all associated interfaces
	if (p->recorderObject != NULL) {
		(*p->recorderObject)->Destroy(p->recorderObject);
		p->recorderObject = NULL;
		p->recorderRecord = NULL;
		p->recorderBufferQueue = NULL;
	}

	// destroy output mix object, and invalidate all associated interfaces
	if (p->outputMixObject != NULL) {
		(*p->outputMixObject)->Destroy(p->outputMixObject);
		p->outputMixObject = NULL;
	}

	// destroy engine object, and invalidate all associated interfaces
	if (p->engineObject != NULL) {
		(*p->engineObject)->Destroy(p->engineObject);
		p->engineObject = NULL;
		p->engineEngine = NULL;
	}

}

// close the android audio device
void android_CloseAudioDevice(OPENSL_STREAM *p) {

	if (p == NULL)
		return;

	openSLDestroyEngine(p);

	if (p->inlock != NULL) {
		notifyThreadLock(p->inlock);
		destroyThreadLock(p->inlock);
		p->inlock = NULL;
	}

	if (p->outlock != NULL) {
		notifyThreadLock(p->outlock);
		destroyThreadLock(p->outlock);
		p->inlock = NULL;
	}

	if (p->outputBuffer[0] != NULL) {
		free(p->outputBuffer[0]);
		p->outputBuffer[0] = NULL;
	}

	if (p->outputBuffer[1] != NULL) {
		free(p->outputBuffer[1]);
		p->outputBuffer[1] = NULL;
	}

	if (p->inputBuffer[0] != NULL) {
		free(p->inputBuffer[0]);
		p->inputBuffer[0] = NULL;
	}

	if (p->inputBuffer[1] != NULL) {
		free(p->inputBuffer[1]);
		p->inputBuffer[1] = NULL;
	}

	free(p);
}

// open the android audio device for input and/or output
OPENSL_STREAM *android_OpenAudioDevice(int sr, int inchannels, int outchannels,
		int bufferframes) {

	OPENSL_STREAM *p;
	p = (OPENSL_STREAM *) calloc(sizeof(OPENSL_STREAM), 1);

	p->inchannels = inchannels;
	p->outchannels = outchannels;
	p->sr = sr;
	p->inlock = createThreadLock();
	p->outlock = createThreadLock();

	if ((p->outBufSamples = bufferframes * outchannels) != 0) {
		if ((p->outputBuffer[0] = (short *) calloc(p->outBufSamples,
				sizeof(short))) == NULL || (p->outputBuffer[1] =
				(short *) calloc(p->outBufSamples, sizeof(short))) == NULL) {
			android_CloseAudioDevice(p);
			return NULL;
		}
	}

	if ((p->inBufSamples = bufferframes * inchannels) != 0) {
		if ((p->inputBuffer[0] = (short *) calloc(p->inBufSamples,
				sizeof(short))) == NULL || (p->inputBuffer[1] =
				(short *) calloc(p->inBufSamples, sizeof(short))) == NULL) {
			android_CloseAudioDevice(p);
			return NULL;
		}
	}

	p->currentInputIndex = 0;
	p->currentOutputBuffer = 0;
	p->currentInputIndex = p->inBufSamples;
	p->currentInputBuffer = 0;

	if (openSLCreateEngine(p) != SL_RESULT_SUCCESS) {
		android_CloseAudioDevice(p);
		return NULL;
	}

	if (openSLRecOpen(p) != SL_RESULT_SUCCESS) {
		android_CloseAudioDevice(p);
		return NULL;
	}

	if (openSLPlayOpen(p) != SL_RESULT_SUCCESS) {
		android_CloseAudioDevice(p);
		return NULL;
	}

	notifyThreadLock(p->outlock);
	notifyThreadLock(p->inlock);

	p->time = 0.;
	return p;
}

// returns timestamp of the processed stream
double android_GetTimestamp(OPENSL_STREAM *p) {
	return p->time;
}

// this callback handler is called every time a buffer finishes recording
void bqRecorderCallback(SLAndroidSimpleBufferQueueItf bq, void *context) {
	OPENSL_STREAM *p = (OPENSL_STREAM *) context;
	notifyThreadLock(p->inlock);
}

// gets a buffer of size samples from the device
int android_AudioIn(OPENSL_STREAM *p, float *buffer, int size) {
	short *inBuffer;
	int i, bufsamps = p->inBufSamples, index = p->currentInputIndex;
	if (p == NULL || bufsamps == 0)
		return 0;

	inBuffer = p->inputBuffer[p->currentInputBuffer];
	for (i = 0; i < size; i++) {
		if (index >= bufsamps) {
			waitThreadLock(p->inlock);
			(*p->recorderBufferQueue)->Enqueue(p->recorderBufferQueue, inBuffer,
					bufsamps * sizeof(short));
			p->currentInputBuffer = (p->currentInputBuffer ? 0 : 1);
			index = 0;
			inBuffer = p->inputBuffer[p->currentInputBuffer];
		}
		buffer[i] = (float) inBuffer[index++] * CONVMYFLT;
		// TODO: the output buffer should be clicked
		//buffer[i] = min(1.f,max(-1.f,buffer[i]));
	}
	p->currentInputIndex = index;
	if (p->outchannels == 0)
		p->time += (double) size / (p->sr * p->inchannels);
	return i;
}

// this callback handler is called every time a buffer finishes playing
void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context) {
	OPENSL_STREAM *p = (OPENSL_STREAM *) context;
	notifyThreadLock(p->outlock);
}

// puts a buffer of size samples to the device
int android_AudioOut(OPENSL_STREAM *p, float **buffer, int size) {

	short *outBuffer;
	int i, bufsamps = p->outBufSamples, index = p->currentOutputIndex;
	if (p == NULL || bufsamps == 0)
		return 0;
    
    __android_log_write(ANDROID_LOG_INFO, "FaustCPP", "Error");
    
	outBuffer = p->outputBuffer[p->currentOutputBuffer];
    if (p->outchannels == 1) {
        for (i = 0; i < size; i++) {
            outBuffer[index++] = (short) (min(1.f, max(-1.f, buffer[0][i]))
                                          * CONV16BIT);
            if (index >= p->outBufSamples) {
                waitThreadLock(p->outlock);
                (*p->bqPlayerBufferQueue)->Enqueue(p->bqPlayerBufferQueue,
                                                   outBuffer, bufsamps * sizeof(short));
                p->currentOutputBuffer = (p->currentOutputBuffer ? 0 : 1);
                index = 0;
                outBuffer = p->outputBuffer[p->currentOutputBuffer];
            }
        }
    } else {
        for (i = 0; i < size; i++) {
            outBuffer[index++] = (short) (min(1.f, max(-1.f, buffer[0][i]))
                                          * CONV16BIT);
            outBuffer[index++] = (short) (min(1.f, max(-1.f, buffer[1][i]))
                                          * CONV16BIT);
            if (index >= p->outBufSamples) {
                waitThreadLock(p->outlock);
                (*p->bqPlayerBufferQueue)->Enqueue(p->bqPlayerBufferQueue,
                                                   outBuffer, bufsamps * sizeof(short));
                p->currentOutputBuffer = (p->currentOutputBuffer ? 0 : 1);
                index = 0;
                outBuffer = p->outputBuffer[p->currentOutputBuffer];
            }
        }
    }
	p->currentOutputIndex = index;
	p->time += (double) size * p->outchannels/ (p->sr * p->outchannels);
	return i;
}

//----------------------------------------------------------------------
// thread Locks
// to ensure synchronisation between callbacks and processing code
void* createThreadLock(void) {
	threadLock *p;
	p = (threadLock*) malloc(sizeof(threadLock));
	if (p == NULL)
		return NULL;
	memset(p, 0, sizeof(threadLock));
	if (pthread_mutex_init(&(p->m), (pthread_mutexattr_t*) NULL) != 0) {
		free((void*) p);
		return NULL;
	}
	if (pthread_cond_init(&(p->c), (pthread_condattr_t*) NULL) != 0) {
		pthread_mutex_destroy(&(p->m));
		free((void*) p);
		return NULL;
	}
	p->s = (unsigned char) 1;

	return p;
}

int waitThreadLock(void *lock) {
	threadLock *p;
	int retval = 0;
	p = (threadLock*) lock;
	pthread_mutex_lock(&(p->m));
	while (!p->s) {
		pthread_cond_wait(&(p->c), &(p->m));
	}
	p->s = (unsigned char) 0;
	pthread_mutex_unlock(&(p->m));
}

void notifyThreadLock(void *lock) {
	threadLock *p;
	p = (threadLock*) lock;
	pthread_mutex_lock(&(p->m));
	p->s = (unsigned char) 1;
	pthread_cond_signal(&(p->c));
	pthread_mutex_unlock(&(p->m));
}

void destroyThreadLock(void *lock) {
	threadLock *p;
	p = (threadLock*) lock;
	if (p == NULL)
		return;
	notifyThreadLock(p);
	pthread_cond_destroy(&(p->c));
	pthread_mutex_destroy(&(p->m));
	free(p);
}
/**************************  END  opensles-android-dsp.h **************************/
